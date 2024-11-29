/*
 * CharacterRange.hpp
 *
 *  Created on: 10.04.2009
 *      Author: Gunther
 */

#ifndef CHARRANGE_HPP
#define CHARRANGE_HPP

#include "Character.hpp"
#include "../common/Error.hpp"

class CharacterRange
{
public:
  CharacterRange(Character l) : low(l), high(l) {}

  CharacterRange(Character l, Character h)
    : low(l), high(h)
  {
#if ASSERTIONS
    if (-1 > low  || low > high)
    {
      internalerr();
    }
#endif
  }

  bool operator<(const CharacterRange &rhs) const
  {
    if (low < rhs.low) return true;
    if (rhs.low < low) return false;
    if (high < rhs.high) return true;
    return false;
  }

  bool operator==(const CharacterRange &rhs) const
  {
    return low == rhs.low && high == rhs.high;
  }

  bool operator!=(const CharacterRange &rhs) const
  {
    return low != rhs.low || high != rhs.high;
  }

  bool overlaps(const CharacterRange &rhs) const
  {
    return ! (low < rhs.low ? high < rhs.low : rhs.high < low);
  }

  bool adjacent(const CharacterRange &rhs) const
  {
    return low < rhs.low
         ? high + 1 == rhs.low
         : low + 1 == rhs.high;
  }

  size_t size() const
  {
    return high - low + 1;
  }

  const Character &getLow() const {return low;}
  const Character &getHigh() const {return high;}

private:
  Character low;
  Character high;
};

#endif
