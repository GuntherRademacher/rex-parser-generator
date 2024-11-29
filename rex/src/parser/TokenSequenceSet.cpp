/*
 * TokenSet.cpp
 *
 *  Created on: 18.08.2008
 *      Author: Gunther
 */

#include "../common/Memory.hpp"
#include "TokenSequenceSet.hpp"
#include "Naming.hpp"
#include "OrderedTokenSequenceVector.hpp"
#include "../common/Format.hpp"

// class TokenSequenceSet

TokenSequenceSet::TokenSequenceSet(const char *file, int line)
: dynamic(new Set(std::less<TokenSequence>(), Alloc<TokenSequence>(file, line))),
  staticBegin(0), staticEnd(0),
  pass(0), inProgress(false), collected(false)
{}

TokenSequenceSet::TokenSequenceSet(const TokenSequence &cs, const char *file, int line)
: dynamic(new Set(std::less<TokenSequence>(), Alloc<TokenSequence>(file, line))),
  staticBegin(0), staticEnd(0),
  pass(0), inProgress(false), collected(false)
{
  dynamic->insert(cs);
}

TokenSequenceSet::TokenSequenceSet(const TokenSequenceSet &tss, const char *file, int line)
: dynamic(0),
  staticBegin(0), staticEnd(0),
  pass(0), inProgress(false), collected(false)
{
  if (tss.dynamic != 0)
  {
    dynamic = new Set(*tss.dynamic);
  }
  else
  {
    dynamic = new Set(std::less<TokenSequence>(), Alloc<TokenSequence>(file, line));
    for (iterator i = tss.begin(); i != tss.end(); ++i)
    {
      dynamic->insert(*i);
    }
  }
}

// special constructor for going static

TokenSequenceSet::TokenSequenceSet(const TokenSequenceSet *tss, const char *file, int line)
: dynamic(0),
  staticBegin(0), staticEnd(0),
  pass(0), inProgress(false), collected(false)
{
  size_t size = tss->size();
  if (size == 0) size = 1;
  staticBegin = ALLOCATE_ARRAY(TokenSequence, size);
  staticEnd = staticBegin;

  for (iterator i = tss->begin(); i != tss->end(); ++i)
  {
    *staticEnd++ = *i;
  }
}

bool TokenSequenceSet::empty() const
{
  if (dynamic == 0)
    return staticBegin == staticEnd;
  return dynamic->empty();
}

size_t TokenSequenceSet::size() const
{
  if (dynamic == 0)
    return staticEnd - staticBegin;
  return dynamic->size();
}

bool TokenSequenceSet::contains(const TokenSequence &token) const
{
  if (dynamic == 0)
  {
    TokenSequence *lo = staticBegin;
    TokenSequence *hi = staticEnd - 1;
    do
    {
      TokenSequence *m = ((hi - lo) >> 1) + lo;
      if (token < *m)
        hi = m - 1;
      else if (*m < token)
        lo = m + 1;
      else
        return true;
    }
    while (lo <= hi);
    return false;
  }
  return dynamic->find(token) != dynamic->end();
}

void TokenSequenceSet::insertAll(const TokenSequenceSet &ts)
{
  if (ts.dynamic != 0 && dynamic->empty())
    *dynamic = *ts.dynamic;
  else
    dynamic->insert(ts.begin(), ts.end());
}

void TokenSequenceSet::insertIntersectionOf(const TokenSequenceSet &ts1, const TokenSequenceSet &ts2)
{
  std::set_intersection(ts1.begin(), ts1.end(),
                        ts2.begin(), ts2.end(),
                        std::insert_iterator<Set>(*dynamic, dynamic->begin()));
}

void TokenSequenceSet::insertDifferenceOf(const TokenSequenceSet &ts1, const TokenSequenceSet &ts2)
{
  std::set_difference(ts1.begin(), ts1.end(),
                      ts2.begin(), ts2.end(),
                      std::insert_iterator<Set>(*dynamic, dynamic->begin()));
}

void TokenSequenceSet::insertFirstKOf(const TokenSequenceSet &tss, const size_t &k)
{
  for (const_iterator i = tss.begin(); i != tss.end(); ++i)
  {
    insert(i->first(k));
  }
}

void TokenSequenceSet::insertIfNotEndsWith(const TokenSequenceSet &tss, Token::Code code)
{
  for (const_iterator i = tss.begin(); i != tss.end(); ++i)
  {
    if (i->last() != code)
    {
      insert(*i);
    }
  }
}

void TokenSequenceSet::insertUpsized(const TokenSequenceSet &lhs, const TokenSequenceSetAccessor &rhs, size_t k, TokenSequenceFactory *tokenSequenceFactory)
{
  for (TokenSequenceSet::const_iterator i = lhs.begin(); i != lhs.end(); ++i)
  {
    const TokenSequence &ts(*i);
    size_t s = ts.size();
    if (s == k ||
        ts.last() == Token::eIMPLICIT ||
        ts.last() == Token::eCYCLIC)
    {
      insert(ts);
    }
    else
    {
      const TokenSequenceSet *lookahead = rhs.get(k - s);

      // TODO: eliminate  double restriction to k-s, by Accessor argument and explicit test

      for (TokenSequenceSet::const_iterator l = lookahead->begin(); l != lookahead->end(); ++l)
      {
        const TokenSequence lookaheadPrefix = *l;
        if (lookaheadPrefix.last() == Token::eCYCLIC)
        {
          insert(lookaheadPrefix);
        }
        else
        {
          insert(tokenSequenceFactory->tokenSequence(ts, lookaheadPrefix.first(k - s)));
        }
      }
    }
  }
}

bool TokenSequenceSet::operator!=(const TokenSequenceSet &rhs) const
{
  if (dynamic == 0 || rhs.dynamic == 0)
    return this != &rhs;

  const_iterator lhsI = begin();
  const_iterator lhsE = end();
  const_iterator rhsI = rhs.begin();
  const_iterator rhsE = rhs.end();
  while (lhsI != lhsE)
  {
    if (! (rhsI != rhsE)) return true;
    const TokenSequence lhsT = *lhsI;
    const TokenSequence rhsT = *rhsI;
    if (lhsT < rhsT) return true;
    if (rhsT < lhsT) return true;
    ++lhsI;
    ++rhsI;
  }
  return rhsI != rhsE;
}

bool TokenSequenceSet::operator<(const TokenSequenceSet &rhs) const
{
  if (dynamic == 0 && rhs.dynamic == 0)
  {
    if (this == &rhs)
      return false;

    const TokenSequence *lhsI = staticBegin;
    const TokenSequence *lhsE = staticEnd;
    const TokenSequence *rhsI = rhs.staticBegin;
    const TokenSequence *rhsE = rhs.staticEnd;
    while (lhsI != lhsE)
    {
      if (! (rhsI != rhsE)) return false;
      const TokenSequence lhsT = *lhsI;
      const TokenSequence rhsT = *rhsI;
      if (lhsT < rhsT) return true;
      if (rhsT < lhsT) return false;
      ++lhsI;
      ++rhsI;
    }
    return rhsI != rhsE;
  }

  const_iterator lhsI = begin();
  const_iterator lhsE = end();
  const_iterator rhsI = rhs.begin();
  const_iterator rhsE = rhs.end();
  while (lhsI != lhsE)
  {
    if (! (rhsI != rhsE)) return false;
    const TokenSequence lhsT = *lhsI;
    const TokenSequence rhsT = *rhsI;
    if (lhsT < rhsT) return true;
    if (rhsT < lhsT) return false;
    ++lhsI;
    ++rhsI;
  }
  return rhsI != rhsE;
}

TokenSequenceSet::iterator TokenSequenceSet::begin() const
{
  if (dynamic == 0)
    return iterator(staticBegin);
  return iterator(dynamic->begin());
}

TokenSequenceSet::iterator TokenSequenceSet::end() const
{
  if (dynamic == 0)
    return iterator(staticEnd);
  return iterator(dynamic->end());
}

std::pair<TokenSequenceSet::iterator, bool> TokenSequenceSet::insert(const TokenSequence &ts)
{
  std::pair<Set::iterator, bool> i = dynamic->insert(ts);
  return std::pair<iterator, bool>(iterator(i.first), i.second);
}

WString TokenSequenceSet::toString(Grammar *grammar,
                                   const wchar_t *linePrefix,
                                   const wchar_t *setSeparator,
                                   size_t width,
                                   size_t trailerWidth,
                                   bool showCodes,
                                   WcsSet *toBeEscaped) const
{
  OrderedTokenSequenceVector v(*this, __FILE__, __LINE__);
  return v.toString(grammar, linePrefix, setSeparator, width, trailerWidth, showCodes, toBeEscaped);
}

// class TokenSequenceSet::iterator

bool TokenSequenceSet::iterator::operator==(const TokenSequenceSet::iterator& rhs) const
{
  if (staticI)
    return staticI == rhs.staticI;
  else
    return dynamicI == rhs.dynamicI;
}

bool TokenSequenceSet::iterator::operator!=(const TokenSequenceSet::iterator& rhs) const
{
  if (staticI)
    return staticI != rhs.staticI;
  else
    return dynamicI != rhs.dynamicI;
}

const TokenSequence &TokenSequenceSet::iterator::operator*() const
{
  if (staticI)
    return *staticI;
  else
    return *dynamicI;
}

const TokenSequence *TokenSequenceSet::iterator::operator->() const
{
  if (staticI)
    return staticI;
  else
    return &*dynamicI;
}

TokenSequenceSet::iterator &TokenSequenceSet::iterator::operator++()
{
  if (staticI)
    ++staticI;
  else
    ++dynamicI;
  return *this;
}

TokenSequenceSet::iterator TokenSequenceSet::iterator::operator++(int)
{
  iterator before(*this);
  if (staticI)
    ++staticI;
  else
    ++dynamicI;
  return before;
}
