/*
 * PredictionBuilder.cpp
 *
 *  Created on: 05.11.2012
 *      Author: Gunther
 */

#include "../common/Memory.hpp"
#include "../common/CompressedMap.hpp"
#include "PredictionBuilder.hpp"

#define DEBUG_TABLES 0

void PredictionBuilder::build()
{
  // make sure all external token codes are represented in matchCode.
  // at this point, non-decisive tokens will be added
  for (Token::Code c = grammar->firstTokenCode; c <= grammar->maxTokenCode; ++c)
  {
    const TokenSequence &ts(grammar->tokenSequenceFactory->tokenSequence(c));
    grammar->matchCode[ts];
  }

  Token::Code maxMatchCode = 0;
  for (MatchCode::iterator i = grammar->matchCode.begin(); i != grammar->matchCode.end(); ++i)
  {
    const TokenSequence &ts(i->first);
    MatchCodeDescriptor &mcd(i->second);
    if (ts.size() == 1 && ! mcd.isMatch() && ! mcd.isPrefix())
    {
      mcd.setCode(++maxMatchCode);
    }
  }

  for (MatchCode::iterator i = grammar->matchCode.begin(); i != grammar->matchCode.end(); ++i)
  {
    const TokenSequence &ts(i->first);
    MatchCodeDescriptor &mcd(i->second);
    if (ts.size() == 1 && mcd.isMatch() && ! mcd.isPrefix())
    {
      mcd.setCode(++maxMatchCode);
    }
  }

//Token::Code firstPrefix = maxMatchCode + 1;

  for (MatchCode::iterator i = grammar->matchCode.begin(); i != grammar->matchCode.end(); ++i)
  {
    const TokenSequence &ts(i->first);
    MatchCodeDescriptor &mcd(i->second);
    if (ts.size() == 1 && mcd.isPrefix())
    {
      mcd.setCode(++maxMatchCode);
    }
  }

  Token::Code lastTokenCode = maxMatchCode;

  for (MatchCode::iterator i = grammar->matchCode.begin(); i != grammar->matchCode.end(); ++i)
  {
    const TokenSequence &ts(i->first);
    MatchCodeDescriptor &mcd(i->second);
    if (ts.size() != 1 && mcd.isPrefix())
    {
      mcd.setCode(++maxMatchCode);
    }
  }

  Token::Code lastPrefix = maxMatchCode;

  for (MatchCode::iterator i = grammar->matchCode.begin(); i != grammar->matchCode.end(); ++i)
  {
    const TokenSequence &ts(i->first);
    MatchCodeDescriptor &mcd(i->second);
    if (ts.size() != 1 && ! mcd.isPrefix())
    {
      mcd.setCode(++maxMatchCode);
    }
  }

  for (MatchCode::iterator i = grammar->matchCode.begin(); i != grammar->matchCode.end(); ++i)
  {
    MatchCodeDescriptor &mcd(i->second);
    int c = mcd.getCode();
    if (c == 0)
    {
      internalerr();
    }
  }

  if (grammar->verbose)
  {
    printf("number of match codes: %d\n", maxMatchCode);
  }

  grammar->matchCode[grammar->tokenSequence(Token::eEPSILON)];

  free(grammar->externalTokenCode);
  grammar->externalTokenCode = ALLOCATE_ARRAY(Token::Code, grammar->maxTokenCode + 1);
  memset(grammar->externalTokenCode, 0, sizeof(Token::Code) * (grammar->maxTokenCode + 1));
  for (int i = grammar->firstTokenCode; i <= grammar->maxTokenCode; ++i)
  {
    // EPSILON(0)
    // error(1)
    // END(2)
    // firstToken(3)
    // ...

    const TokenSequence &ts(grammar->tokenSequenceFactory->tokenSequence(i));

    MatchCode::const_iterator j(grammar->matchCode.find(ts));
    if (j != grammar->matchCode.end())
    {
      const MatchCodeDescriptor &mcd(j->second);
      grammar->externalTokenCode[i] = mcd.getCode();
    }
    else
    {
      internalerr();
    }
  }

#if 0
  int prefixes = 0;
  for (MatchCode::iterator i = grammar->matchCode.begin(); i != grammar->matchCode.end(); ++i)
  {
#if 0
    const TokenSequence &subSequence = i->k;

    printf("%4.4d ", i->lookahead.getCode());
    printf("%ls", i->lookahead.isPrefix() ? L"P " : L"  ");
    printf("%ls", i->lookahead.isMatch() ? L"M " : L"  ");

    size_t sequenceSize = subSequence.size();
    for (size_t j = 0; j < sequenceSize; ++j)
    {
      const Token::Code c(subSequence[(int) j]);
      const wchar_t *name = grammar->naming.getName(grammar, c, false);
      printf("%ls ", name);
    }

    printf(" %ls\n", i->lookahead.isPrefix() ? L"P" : L" ");
#endif
    if (i->lookahead.isPrefix())
    {
      ++prefixes;
    }
  }

  printf("number of relevant lookahead codes: %d\n", (int) grammar->matchCode.size());
  printf("prefixes: %d\n", prefixes);
#endif

  // matchcodeTable: match code (prefix) X token code -> match code

  int matchcodeTableCompression = 2;
  int matchcodeTableAlignment   = 8;
  if (grammar->faster)
  {
    matchcodeTableCompression = 1;
    matchcodeTableAlignment   = 0;
  }
  else if (grammar->smaller)
  {
    matchcodeTableCompression = 3;
    matchcodeTableAlignment   = 1;
  }
  grammar->matchcodeTable = new TiledMap2D(matchcodeTableCompression, matchcodeTableAlignment);

#if 0
  for (Token::Code prefix = firstPrefix; prefix <= lastPrefix; ++prefix)
    for (Token::Code token = 1; token <= lastTokenCode; ++token)
  {
      grammar->matchcodeTable->add(prefix, token, prefix);
  }
#endif

  grammar->matchcodeTable->setMaxIndex(lastPrefix, lastTokenCode);

  for (MatchCode::iterator i = grammar->matchCode.begin(); i != grammar->matchCode.end(); ++i)
  {
    const TokenSequence &ts(i->first);

    size_t k = ts.size();
    if (k > 1)
    {
      int mc0 = grammar->matchCode[grammar->tokenSequenceFactory->tokenSequence(ts, 0, k - 1)].getCode();
      int tc = grammar->matchCode[grammar->tokenSequenceFactory->tokenSequence(ts.last())].getCode();
      int mc1 = grammar->matchCode[ts].getCode();
      grammar->matchcodeTable->set(mc0, tc, mc1);

#if DEBUG_TABLES
      TokenSequenceSet tss(ts);
      wchar_t *string = tss.toString(grammar, L"", L" ", 999, 0, false, 0);
      printf("    LOOKAHEAD(%d, %d) = %d // %ls\n", mc0, tc, mc1, string);
      free(string);
#endif
    }
  }

  grammar->matchcodeTable->getMap();

  // grammar->caseidTable: match code X decision point (k > 1) -> token set

  int caseidTableCompression = 2; // check performance with 1 and 3, too
  int caseidTableAlignment = 16;
  if (grammar->faster)
  {
    caseidTableCompression = 1;
    caseidTableAlignment = 0;
  }
  else if (grammar->smaller)
  {
    caseidTableCompression = 3;
    caseidTableAlignment = 1;
  }
  grammar->caseidTable = new TiledMap2D(caseidTableCompression, caseidTableAlignment);

  int dpi = 0;
  for (DecisionPoints::iterator i = grammar->decisionPoints.begin();
       i != grammar->decisionPoints.end();
       ++i)
  {
    size_t k = i->k;
    const CompressedTokenSet *lookahead(i->lookahead);

    const_cast<CompressedTokenSet *>(lookahead)->setDpiIfAbsent(dpi);
    dpi = lookahead->getDpi();

    if (k > 1)
    {
      setTokensetByDpiAndMatchcode(grammar->caseidTable, dpi, *lookahead, grammar->tokenSequence(Token::eEPSILON));
    }

    ++dpi;
  }
  grammar->caseidTable->setMaxIndex(maxMatchCode, dpi - 1);

  PrepareCaseIdTable pcit(grammar->caseidTable);
  if (grammar->states)
  {
    pcit.process(grammar);
  }
  else
  {
    grammar->accept(pcit);
  }

#if DEBUG_TABLES
  printf("caseidTable: %d rows, %d cols\n", maxMatchCode, dpi - 1);

  for (int d = 0; d <= dpi - 1; ++d)
  {
    printf("dpi %d:", d);
    for (int m = 0; m <= maxMatchCode; ++m)
    {
      printf(" %d", grammar->caseidTable->get(m, d));
    }
    printf("\n");
  }
#endif

//  grammar->caseidTable->getMap();
}

void PredictionBuilder::setTokensetByDpiAndMatchcode(TiledMap2D *caseidTable, int dpi, const CompressedTokenSet &cts, const TokenSequence &prefix)
{
  const CompressedTokenSet::HigherOrderLookahead &hol(cts.getHigherOrderLookahead());
  for (CompressedTokenSet::HigherOrderLookahead::const_iterator i = hol.begin();
       i != hol.end();
       ++i)
  {
    Token::Code token = i->first;
    const CompressedTokenSet *next = i->second;
    const TokenSequence &ts(grammar->tokenSequenceFactory->tokenSequence(prefix, grammar->tokenSequence(token)));

    const MatchCode::const_iterator j(grammar->matchCode.find(ts));
    if (j == grammar->matchCode.end())
    {
      // TODO: this happens when there are downgradable conflicts. Ignoring helps,
      // but does it possibly produce lookahead sets that will not be used?
    }
    else
    {
      const MatchCodeDescriptor &mcd(j->second);

#if DEBUG_TABLES
      printf("    dpi %d, matchcode %d, tokenset %d more %d ",
             dpi, mcd.getCode(),
             cts.getSetNo(grammar->lookaheadSets),
             ! next->getHigherOrderLookahead().empty());

      printf("%4.4d ", mcd.getCode());
      printf("%ls", mcd.isPrefix() ? L"P " : L"  ");
      printf("%ls", mcd.isMatch() ? L"M " : L"  ");
      size_t sequenceSize = ts.size();
      for (size_t j = 0; j < sequenceSize; ++j)
      {
        const Token::Code c(ts[(int) j]);
        const wchar_t *name = grammar->naming.getName(grammar, c, false);
        printf("%ls ", name);
      }
      printf("\n");

      printf("    CASEID(%d, %d) = (%d << 1) + 1\n", mcd.getCode(), dpi, next->getSetNo(grammar->lookaheadSets));
#endif

//      fprintf(stderr, "P: grammar->caseidTable->set(%d, %d, %d)\n", mcd.getCode(), dpi, (next->getSetNo(grammar->lookaheadSets) << 1) + 1);
//      fflush(stderr);

      caseidTable->set(mcd.getCode(), dpi, (next->getSetNo(grammar->lookaheadSets) << 1) + 1);
    }

    setTokensetByDpiAndMatchcode(caseidTable, dpi, *next, ts);
  }
}
