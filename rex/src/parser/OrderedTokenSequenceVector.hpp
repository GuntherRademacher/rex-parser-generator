/*
 * OrderedTokenSequenceVector.hpp
 *
 *  Created on: 03.02.2014
 *      Author: Gunther
 */

#ifndef ORDEREDTOKENSEQUENCEVECTOR_HPP_
#define ORDEREDTOKENSEQUENCEVECTOR_HPP_

#include "TokenSequenceSet.hpp"
#include <vector>

class Grammar;

class OrderedTokenSequenceVector : private std::vector<TokenSequence, Alloc<TokenSequence> >
{                                  typedef std::vector<TokenSequence, Alloc<TokenSequence> >
                                   super;
public:
  OrderedTokenSequenceVector(const TokenSequenceSet &tss, const char *file = __FILE__, int line = __LINE__)
  : super(Alloc<TokenSequence>(file, line))
  {
    for (TokenSequenceSet::const_iterator i = tss.begin(); i != tss.end(); ++i)
    {
      push_back(*i);
    }

    std::sort(super::begin(), super::end(), TokenSequence::Order());
  }

  typedef super::const_iterator const_iterator;
  const_iterator begin() const {return super::begin();}
  const_iterator end() const {return super::end();}
  size_t size() const {return super::size();}

  bool operator<(const OrderedTokenSequenceVector &rhs) const
  {
    const OrderedTokenSequenceVector &lhs(*this);

    size_t lhsSize = lhs.size();
    size_t rhsSize = rhs.size();
    if (lhsSize < rhsSize) return true;
    if (rhsSize < lhsSize) return false;

    OrderedTokenSequenceVector::const_iterator l = lhs.begin();
    OrderedTokenSequenceVector::const_iterator r = rhs.begin();
    while (l != lhs.end())
    {
      const TokenSequence &lhsCode(*l);
      const TokenSequence &rhsCode(*r);
      if (tokenSequenceOrder(lhsCode, rhsCode)) return true;
      if (tokenSequenceOrder(rhsCode, lhsCode)) return false;
      ++l;
      ++r;
    }
    return false;
  }

  WString toString(Grammar *grammar,
                   const wchar_t *linePrefix,
                   const wchar_t *separator,
                   size_t width,
                   size_t trailerWidth,
                   bool showCodes,
                   WcsSet *toBeEscaped = 0) const;

private:
  TokenSequence::Order tokenSequenceOrder;
};

#endif /* ORDEREDTOKENSEQUENCEVECTOR_HPP_ */
