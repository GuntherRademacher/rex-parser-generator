/*
 * Math.hpp
 *
 *  Created on: 17.09.2009
 *      Author: Gunther
 */

#ifndef MATH_HPP
#define MATH_HPP

class Math
{
public:
  static int powerof(int base, int exponent)
  {
    int result = 1;
    for (int e = 0; e < exponent; ++e)
    {
      result *= base;
    }
    return result;
  }

  static int log2(int value)
  {
    // value  0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 ...
    // log2   0  0  1  1  2  2  2  2  3  3  3  3  3  3  3  3  4  4

    int exponent;
    for (exponent = 0; value > 1; ++exponent)
    {
      value >>= 1;
    }
    return exponent;
  }

  static bool isPowerOf2(int value)
  {
    return value == powerof(2, log2(value));
  }

  static int bits(int valueCount)
  {
    // valuecount 0 1 2 3 4 5 6 7 8 9 15 16 17 31 32 33 63 64 65 127 128 129
    // bits       0 0 1 2 2 3 3 3 3 4  4  4  5  5  5  6  6  6  7   7   7   8

    return valueCount < 2 ? 0 : (1 + log2(valueCount - 1));
  }

  static size_t bitSum(unsigned int value)
  {
    size_t sum = 0;
    while (value != 0)
    {
      if (value & 1) ++sum;
      value >>= 1;
    }
    return sum;
  }

  template<class INT>
  static INT min(INT a, INT b)
  {
    return a <= b ? a : b;
  }

  template<class INT>
  static INT max(INT a, INT b)
  {
    return a >= b ? a : b;
  }
};

#endif
