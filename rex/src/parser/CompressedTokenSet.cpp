/*
 * CompressedTokenSet.cpp
 *
 *  Created on: 03.02.2014
 *      Author: Gunther
 */

#include "../common/Memory.hpp"
#include "../common/PtrLess.hpp"
#include "CompressedTokenSet.hpp"

void CompressedTokenSet::populate(const TokenSequenceSet &tokenSet,
                                  const TokenSequenceSet &whitespaceIntroducers,
                                  TokenSequenceSet const * const * conflictsByKMinus1,
                                  bool lookedahead,
                                  TokenSequenceFactory *tokenSequenceFactory,
                                  Lookahead &sets)
{
  for (TokenSequenceSet::const_iterator j = tokenSet.begin();
       j != tokenSet.end();
       ++j)
  {
    const TokenSequence &tokenSequence(*j);
    TokenSequence prefix(tokenSequenceFactory->emptySequence());
    for (size_t runningK = 0; ; ++runningK)
    {
      prefix = tokenSequenceFactory->tokenSequence(prefix, tokenSequenceFactory->tokenSequence(tokenSequence[(int) runningK]));
      const TokenSequenceSet* const conflictsK = conflictsByKMinus1 == 0 ? 0 : conflictsByKMinus1[runningK];
      if (conflictsK == 0 || ! conflictsK->contains(prefix))
      {
        insert(prefix, tokenSequenceFactory, whitespaceIntroducers);
        break;
      }
    }
  }

  publish(tokenSequenceFactory, 1, lookedahead, sets);
}

void CompressedTokenSet::publish(TokenSequenceFactory *tsf, size_t k, bool lookedahead, Lookahead &sets)
{
  if (k > 1 || ! lookedahead)
  {
    sets[initials] = 0;

    if (containsImplicitWhitespace)
    {
      if (sets.lookaheadWCount < k) sets.lookaheadWCount = k;
    }
    else
    {
      if (sets.lookaheadCount < k) sets.lookaheadCount = k;
    }
  }

  // group lookahead chars by higher order lookahead

  typedef std::map<CompressedTokenSet *, TokenSequenceSet, PtrLess<CompressedTokenSet> > TokenSetByCompressedTokenSet;
  TokenSetByCompressedTokenSet tokenSetByCompressedTokenSet;
  for (HigherOrderLookahead::iterator i = higherOrderLookahead.begin();
       i != higherOrderLookahead.end();
       ++i)
  {
    Token::Code code(i->first);
    CompressedTokenSet *compressedTokenSet(i->second);

    TokenSetByCompressedTokenSet::iterator j(tokenSetByCompressedTokenSet.find(compressedTokenSet));
    if (j == tokenSetByCompressedTokenSet.end())
    {
      TokenSequenceSet tss(tsf->tokenSequence(code), __FILE__, __LINE__);
      std::pair<CompressedTokenSet *, TokenSequenceSet> value(compressedTokenSet, tss);
      tokenSetByCompressedTokenSet.insert(value);
    }
    else
    {
      j->second.insert(tsf->tokenSequence(code));
    }
  }

  for (TokenSetByCompressedTokenSet::iterator i = tokenSetByCompressedTokenSet.begin();
       i != tokenSetByCompressedTokenSet.end();
       ++i)
  {
    CompressedTokenSet *compressedTokenSet(i->first);
    TokenSequenceSet &tokenSequenceSet(i->second);
    combinedHigherOrderLookahead[tokenSequenceSet] = compressedTokenSet;
  }

  for (CompressedTokenSetByTokenSet::iterator i = combinedHigherOrderLookahead.begin();
       i != combinedHigherOrderLookahead.end();
       ++i)
  {
    i->second->publish(tsf, k + 1, lookedahead, sets);
  }

  if (k == 1)
    enumerate(0);
}

int CompressedTokenSet::localSequenceCode(TokenSequenceFactory *tsf, const TokenSequence &sequence, const Token::Code *externalTokenCode) const
{
  switch (sequence.size())
  {
  case 0:
    return 0;
  case 1:
    {
      return (sequenceNumber << tsf->tokenBits()) + externalTokenCode[sequence.first()];
    }
  default:
    {
      return higherOrderLookahead.find(sequence.first())->second->localSequenceCode(tsf, tsf->tokenSequence(sequence, 1), externalTokenCode);
    }
  }
}

int CompressedTokenSet::uniqueSequenceCode(TokenSequenceFactory *tsf, const TokenSequence &sequence, const Token::Code *externalTokenCode)
{
  int result = 0;
  int i = 0;
  for (size_t left = 0; ; left += tsf->tokenBits())
  {
    Token::Code c = sequence[i++];
    if (c == Token::eEPSILON)
    {
      break;
    }
    result += externalTokenCode[c] << left;
  }
  return result;
}
