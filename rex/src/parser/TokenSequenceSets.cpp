/*
 * TokenSequenceSets.cpp
 *
 *  Created on: 03.04.2015
 *      Author: Gunther
 */

#include "../common/Memory.hpp"
#include "TokenSequenceSets.hpp"
#include "Grammar.hpp"

LazyFollowAccessor::LazyFollowAccessor(TokenSequenceSets *tokenSequenceSets,
                                       const TokenSequenceSetAccessor *followAccessor,
                                       size_t k,
                                       const TokenSequenceSetAccessor *lookaheadAccessor)
: tokenSequenceSets(tokenSequenceSets)
, followAccessor(followAccessor)
, k(k)
, lookaheadAccessor(lookaheadAccessor)
{}

LazyFollowAccessor::~LazyFollowAccessor()
{
}

const TokenSequenceSet *LazyFollowAccessor::get() const
{
  return tokenSequenceSets->upsize(followAccessor, k, lookaheadAccessor);
}

const TokenSequenceSet *LazyFollowAccessor::get(size_t k) const
{
  return get();
}

const TokenSequenceSet *TokenSequenceSets::eraseIfEndsWith(const TokenSequenceSetAccessor *accessor, Token::Code code)
{
  const TokenSequenceSet *&memoized = eraseIfEndsWithMemoizer[SetCodeMemoizer::key_type(accessor, code)];
  if (! memoized)
  {
    TokenSequenceSet *stripped = new TokenSequenceSet();
    stripped->insertIfNotEndsWith(*accessor->get(), code);
    memoized = collect(stripped);
  }
  return memoized;
}

const TokenSequenceSet *TokenSequenceSets::upsize(const TokenSequenceSetAccessor *lhs, size_t k, const TokenSequenceSetAccessor *rhs)
{
  const TokenSequenceSet *&memoized = upsizeMemoizer[UpsizeMemoizer::key_type(std::pair<const TokenSequenceSetAccessor *, const TokenSequenceSetAccessor *>(lhs, rhs), k)];
  if (! memoized)
  {
    TokenSequenceSet *result = new TokenSequenceSet();
    result->insertUpsized(*lhs->get(), *rhs, k, tokenSequenceFactory);
    memoized = collect(result);
  }
  return memoized;
}

const TokenSequenceSetAccessor *TokenSequenceSets::follow(const TokenSequenceSetAccessor *followAccessor, size_t k, const TokenSequenceSetAccessor *lookaheadAccessor)
{
  const TokenSequenceSetAccessor *&memoized = followMemoizer[AccessorAccessorSizeMemoizer::key_type(std::pair<const TokenSequenceSetAccessor *, const TokenSequenceSetAccessor *>(followAccessor, lookaheadAccessor), k)];
  if (! memoized)
  {
    memoized = new LazyFollowAccessor(this, followAccessor, k, lookaheadAccessor);
  }
  return memoized;
}
