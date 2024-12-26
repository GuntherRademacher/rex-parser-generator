/*
 * CompressedTokenSet.hpp
 *
 *  Created on: 03.02.2014
 *      Author: Gunther
 */

#ifndef COMPRESSEDTOKENSET_HPP_
#define COMPRESSEDTOKENSET_HPP_

#include "../common/Error.hpp"
#include "Lookahead.hpp"
#include "TokenSequenceSet.hpp"
#include "TokenSequenceSets.hpp"

class CompressedTokenSet
{
public:
  typedef std::map<Token::Code, CompressedTokenSet *> HigherOrderLookahead;
  typedef std::map<OrderedTokenSequenceVector, CompressedTokenSet * /*, TokenSequenceSet::Order*/> CompressedTokenSetByTokenSet;

  CompressedTokenSet() : containsImplicitWhitespace(false), sequenceNumber(-1), dpi(-1) {};

  ~CompressedTokenSet()
  {
    matchSet.clear();
    initials.clear();

    for (HigherOrderLookahead::iterator i = higherOrderLookahead.begin();
         i != higherOrderLookahead.end();
         ++i)
    {
      delete i->second;
      i->second = 0;
    }

    higherOrderLookahead.clear();
    combinedHigherOrderLookahead.clear();

    containsImplicitWhitespace = false;
    sequenceNumber = -1;
    dpi = -1;
  }

  bool operator<(const CompressedTokenSet &rhs) const
  {
    if (    initials < rhs.initials) return true;
    if (rhs.initials <     initials) return false;
    HigherOrderLookahead::const_iterator l(    higherOrderLookahead.begin());
    HigherOrderLookahead::const_iterator r(rhs.higherOrderLookahead.begin());
    while (l != higherOrderLookahead.end())
    {
      if (r == rhs.higherOrderLookahead.end()) return false;
      if (l->first < r->first) return true;
      if (r->first < l->first) return false;
      if (*l->second < *r->second) return true;
      if (*r->second < *l->second) return false;
      ++l;
      ++r;
    }
    return r != rhs.higherOrderLookahead.end();
  }

  void populate(const TokenSequenceSet &tokenSet,
                const TokenSequenceSet &whitespaceIntroducers,
                TokenSequenceSet const * const * conflictsByKMinus1,
                bool lookedahead,
                TokenSequenceFactory *tokenSequenceFactory,
                Lookahead &sets);

  static const TokenSequenceSet *compressMatch(TokenSequenceSet const * const * conflictsByKMinus1,
                                               const TokenSequenceSet &uncompressedMatch,
                                               TokenSequenceFactory *tokenSequenceFactory,
                                               TokenSequenceSets *tokenSequenceSets)
  {
    TokenSequenceSet *compressed = new TokenSequenceSet(__FILE__, __LINE__);

    for (TokenSequenceSet::const_iterator j = uncompressedMatch.begin();
         j != uncompressedMatch.end();
         ++j)
    {
      const TokenSequence &tokenSequence(*j);

      TokenSequence prefix(tokenSequenceFactory->emptySequence());
      for (size_t i = 0; ; ++i)
      {
        Token::Code token(tokenSequence[(int) i]);
        if (token == Token::eWS)
        {
          break;
        }

        prefix = tokenSequenceFactory->tokenSequence(prefix, tokenSequenceFactory->tokenSequence(token));
        const TokenSequenceSet* conflicts = conflictsByKMinus1 == 0 ? 0  : conflictsByKMinus1[i];
        if (conflicts == 0 || ! conflictsByKMinus1[i]->contains(prefix))
        {
          compressed->insert(prefix);
          break;
        }
      }
    }
    return tokenSequenceSets->collect(compressed);
  }

  static size_t getSetNo(const TokenSequenceSet *tss, const Lookahead &sets)
  {
    Lookahead::const_iterator i(sets.find(*tss));
    return i != sets.end() ? i->second : 0;
  }

  size_t getSetNo(const Lookahead &sets) const
  {
    return getSetNo(&initials, sets);
  }

  int getDpi() const {return dpi;}
  void setDpiIfAbsent(int d)
  {
    if (dpi < 0) dpi = d;
  }

  const TokenSequenceSet &getInitials() const {return initials;}
  const TokenSequenceSet &getMatchSet() const {return matchSet;}

  const CompressedTokenSetByTokenSet &getCombinedHigherOrderLookahead() const
  {
    return combinedHigherOrderLookahead;
  }

  const HigherOrderLookahead &getHigherOrderLookahead() const
  {
    return higherOrderLookahead;
  }

  bool empty() const
  {
    return initials.empty();
  }

  bool hasImplicitWhitespace() const
  {
    return containsImplicitWhitespace;
  }

  int prefixCode(int bits) const
  {
    return sequenceNumber << bits;
  }

  int localSequenceCode(TokenSequenceFactory *tsf, const TokenSequence &sequence, const Token::Code *externalTokenCode) const;

  static int uniqueSequenceCode(TokenSequenceFactory *tsf, const TokenSequence &sequence, const Token::Code *externalTokenCode);

private:
  CompressedTokenSet(const CompressedTokenSet &) : containsImplicitWhitespace(false), sequenceNumber(-1), dpi(-1)
  {
    internalerr();
  }

  CompressedTokenSet &operator=(const CompressedTokenSet &)
  {
    internalerr();
    return *this;
  }

  int enumerate(int sequenceNumber)
  {
    this->sequenceNumber = sequenceNumber;

    for (HigherOrderLookahead::iterator i = higherOrderLookahead.begin();
         i != higherOrderLookahead.end();
         ++i)
    {
      sequenceNumber = i->second->enumerate(++sequenceNumber);
    }
    return sequenceNumber;
  }

  void insert(const TokenSequence &tokenSequence,
              TokenSequenceFactory *tsf,
              const TokenSequenceSet &whitespaceIntroducers)
  {
    Token::Code prefix = tokenSequence.first();

    if (prefix != Token::eWS)
    {
      if (tokenSequence.last() != Token::eWS)
      {
        matchSet.insert(tokenSequence);
      }
      initials.insert(tsf->tokenSequence(prefix));
    }
    else if (! whitespaceIntroducers.empty())
    {
      containsImplicitWhitespace = true;
      initials.insertAll(whitespaceIntroducers);
    }

    if (tokenSequence.size() > 1)
    {
      HigherOrderLookahead::iterator i(higherOrderLookahead.find(prefix));
      if (i != higherOrderLookahead.end())
      {
        i->second->insert(tsf->tokenSequence(tokenSequence, 1), tsf, whitespaceIntroducers);
      }
      else
      {
        CompressedTokenSet *cts = new CompressedTokenSet();
        cts->insert(tsf->tokenSequence(tokenSequence, 1), tsf, whitespaceIntroducers);
        higherOrderLookahead.insert(HigherOrderLookahead::value_type(prefix, cts));
      }
    }
  }

  void publish(TokenSequenceFactory *tsf, size_t k, bool lookedahead, Lookahead &sets);

  TokenSequenceSet matchSet;
  TokenSequenceSet initials;
  HigherOrderLookahead higherOrderLookahead;
  CompressedTokenSetByTokenSet combinedHigherOrderLookahead;

  bool containsImplicitWhitespace;
  int sequenceNumber;
  int dpi;
};

#endif /* COMPRESSEDTOKENSET_HPP_ */
