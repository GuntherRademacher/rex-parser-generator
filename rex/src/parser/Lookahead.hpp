/*
 * Lookahead.hpp
 *
 *  Created on: 03.02.2014
 *      Author: Gunther
 */

#ifndef LOOKAHEAD_HPP_
#define LOOKAHEAD_HPP_

#include <map>
#include "OrderedTokenSequenceVector.hpp"

class Lookahead : public std::map<OrderedTokenSequenceVector, size_t, std::less<OrderedTokenSequenceVector>, Alloc<std::pair<const OrderedTokenSequenceVector, size_t> > >
{                typedef std::map<OrderedTokenSequenceVector, size_t, std::less<OrderedTokenSequenceVector>, Alloc<std::pair<const OrderedTokenSequenceVector, size_t> > >
                 super;
public:
  Lookahead()
  : super(std::less<OrderedTokenSequenceVector>(), Alloc<std::pair<const OrderedTokenSequenceVector, size_t> >(__FILE__, __LINE__)),
    lookaheadCount(0),
    lookaheadWCount(0)
  {}

  size_t lookaheadCount;
  size_t lookaheadWCount;
};

#endif /* LOOKAHEAD_HPP_ */
