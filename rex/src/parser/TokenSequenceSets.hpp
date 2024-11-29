/*
 * TokenSequenceSets.hpp
 *
 *  Created on: 03.02.2014
 *      Author: Gunther
 */

#ifndef TOKENSEQUENCESETS_HPP_
#define TOKENSEQUENCESETS_HPP_

#include "TokenSequenceSet.hpp"
#include "../common/Error.hpp"
#include "../common/PtrLess.hpp"

class TokenSequenceSets;

class LazyFollowAccessor : public TokenSequenceSetAccessor
{
public:
  LazyFollowAccessor(TokenSequenceSets *tokenSequenceSets,
                     const TokenSequenceSetAccessor *followAccessor,
                     size_t k,
                     const TokenSequenceSetAccessor *lookaheadAccessor);
  ~LazyFollowAccessor();
  const TokenSequenceSet *get() const;
  const TokenSequenceSet *get(size_t k) const;

private:
  TokenSequenceSets *tokenSequenceSets;
  const TokenSequenceSetAccessor *followAccessor;
  size_t k;
  const TokenSequenceSetAccessor *lookaheadAccessor;
};

class TokenSequenceSets : private std::set<TokenSequenceSet *, PtrLess<TokenSequenceSet>, Alloc<TokenSequenceSet *> >
{                         typedef std::set<TokenSequenceSet *, PtrLess<TokenSequenceSet>, Alloc<TokenSequenceSet *> >
                                  super;
public:
  TokenSequenceSets(TokenSequenceFactory *tokenSequenceFactory, const char *file = __FILE__, int line = __LINE__)
  : super(PtrLess<TokenSequenceSet>(), Alloc<TokenSequenceSet *>(file, line))
  , tokenSequenceFactory(tokenSequenceFactory)
  {}

  ~TokenSequenceSets()
  {
    for (iterator i = begin(); i != end(); ++i)
    {
      delete *i;
    }

    for (AccessorAccessorSizeMemoizer::iterator i = followMemoizer.begin(); i != followMemoizer.end(); ++i)
    {
      delete i->second;
    }
  }

  const TokenSequenceSet *collect(TokenSequenceSet *tss)
  {
#if ASSERTIONS
    if (tss->collected)
    {
      internalerr();
    }
#endif

    iterator found = find(const_cast<TokenSequenceSet *>(tss));
    if (found != end())
    {
      delete tss;
      return *found;
    }
    else
    {
      TokenSequenceSet* tokenSequenceSet = new TokenSequenceSet(tss);
      delete tss;
      tokenSequenceSet->collected = true;
      insert(tokenSequenceSet);
      return tokenSequenceSet;
    }

    std::pair<iterator, bool> inserted = insert(tss);
    if (inserted.second)
    {
      tss->collected = true;
      return tss;
    }
    else
    {
      delete tss;
      return *inserted.first;
    }
  }

  const TokenSequenceSet *resolve(const TokenSequenceSet *tss)
  {
    if (tss->isCollected())
    {
      return tss;
    }
    else
    {
      iterator found = find(const_cast<TokenSequenceSet *>(tss));
      if (found != end())
      {
        return *found;
      }
      else
      {
        return collect(new TokenSequenceSet(*tss));
      }
    }
  }

  const TokenSequenceSet *setUnion(const TokenSequenceSetAccessor *first, const TokenSequenceSetAccessor *second)
  {
    const TokenSequenceSet *&memoized = setUnionMemoizer[SetSetMemoizer::key_type(first, second)];
    if (! memoized)
    {
      TokenSequenceSet *u = new TokenSequenceSet(*first->get());
      u->insertAll(*second->get());
      memoized = collect(u);
    }
    return memoized;
  }

  const TokenSequenceSet *setIntersection(const TokenSequenceSetAccessor *first, const TokenSequenceSetAccessor *second)
  {
    const TokenSequenceSet *&memoized = setIntersectionMemoizer[SetSetMemoizer::key_type(first, second)];
    if (! memoized)
    {
      TokenSequenceSet *i = new TokenSequenceSet();
      i->insertIntersectionOf(*first->get(), *second->get());
      memoized = collect(i);
    }
    return memoized;
  }

  const TokenSequenceSet *setDifference(const TokenSequenceSetAccessor *first, const TokenSequenceSetAccessor *second)
  {
    const TokenSequenceSet *&memoized = setDifferenceMemoizer[SetSetMemoizer::key_type(first, second)];
    if (! memoized)
    {
      TokenSequenceSet *i = new TokenSequenceSet();
      i->insertDifferenceOf(*first->get(), *second->get());
      memoized = collect(i);
    }
    return memoized;
  }

  const TokenSequenceSet *firstK(const TokenSequenceSetAccessor *tss, const size_t k)
  {
    const TokenSequenceSet *&memoized = firstKMemoizer[SetSizeMemoizer::key_type(tss, (int) k)];
    if (! memoized)
    {
      TokenSequenceSet *i = new TokenSequenceSet();
      i->insertFirstKOf(*tss->get(), k);
      memoized = collect(i);
    }
    return memoized;
  }

  const TokenSequenceSet *eraseIfEndsWith(const TokenSequenceSetAccessor *accessor, Token::Code code);
  const TokenSequenceSet *upsize(const TokenSequenceSetAccessor *lhs, size_t k, const TokenSequenceSetAccessor *rhs);
  const TokenSequenceSetAccessor *follow(const TokenSequenceSetAccessor *followAccessor, size_t k, const TokenSequenceSetAccessor *lookaheadAccessor);

private:
  TokenSequenceFactory *tokenSequenceFactory;

  typedef std::map<std::pair<const TokenSequenceSetAccessor *, Token::Code>, const TokenSequenceSet *> SetCodeMemoizer;
  SetCodeMemoizer eraseIfEndsWithMemoizer;

  typedef std::map<std::pair<const TokenSequenceSetAccessor *, const TokenSequenceSetAccessor *>, const TokenSequenceSet *> SetSetMemoizer;
  SetSetMemoizer setUnionMemoizer;
  SetSetMemoizer setIntersectionMemoizer;
  SetSetMemoizer setDifferenceMemoizer;

  typedef std::map<std::pair<const TokenSequenceSetAccessor *, const int>, const TokenSequenceSet *> SetSizeMemoizer;
  SetSizeMemoizer firstKMemoizer;

  typedef std::map<std::pair<std::pair<const TokenSequenceSetAccessor *, const TokenSequenceSetAccessor *>, size_t>, const TokenSequenceSet *> UpsizeMemoizer;
  UpsizeMemoizer upsizeMemoizer;

  typedef std::map<std::pair<std::pair<const TokenSequenceSetAccessor *, const TokenSequenceSetAccessor *>, size_t>, const TokenSequenceSetAccessor *> AccessorAccessorSizeMemoizer;
  AccessorAccessorSizeMemoizer followMemoizer;
};

#endif /* TOKENSEQUENCESETS_HPP_ */
