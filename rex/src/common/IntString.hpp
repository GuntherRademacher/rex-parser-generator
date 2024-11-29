/*
 * IntString.hpp
 *
 *  Created on: 23.08.2015
 *      Author: Gunther
 */

#ifndef INTSTRING_HPP
#define INTSTRING_HPP

class IntString : public std::basic_string<int> {
public:
  IntString() = default;
};

class IntStringLess
{
public:
  bool operator()(const int *lhs, const int *rhs) const
  {
    for (; *lhs != 0 && *rhs != 0; ++lhs, ++rhs)
    {
      if (*lhs < *rhs) return true;
      if (*lhs > *rhs) return false;
    }
    return *lhs == 0 && *rhs != 0;
  }
};

#endif /* INTSTRING_HPP */
