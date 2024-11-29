/*
 * itoa.hpp
 *
 *  Created on: Apr 8, 2009
 *      Author: Gunther
 */

#ifndef ITOA_HPP
#define ITOA_HPP

#include <stddef.h>

template<class I, class A>
size_t ItoA(I n, int base, A *buffer, size_t length)
{
  int sign = n < 0 ? -1 : 1;
  size_t l = 0;
  do
  {
    if (l < length) buffer[l] = L'0' + (int) n % base * sign;
    l++;
    n /= base;
  }
  while (n);

  if (sign < 0)
  {
    if (l < length) buffer[l] = L'-';
    l++;
  }
  if (l < length) buffer[l] = 0;

  if (l <= length)
  {
    for (size_t j = 0; j < (l >> 1); ++j)
    {
      A c = buffer[j];
      buffer[j] = buffer[l - j - 1];
      buffer[l - j - 1] = c;
    }
  }
  return l;
}

template<class A>
int Atoi(const A *a, size_t size)
{
  bool negative = false;
  int result = 0;
  for (size_t i = 0; i < size; ++i)
  {
    A c = a[i];
    switch (c)
    {
    case '-':
      negative = true;
      if (i) return 0;
      break;
    case '+':
      if (i) return 0;
      break;
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
      result = result * 10 + (c - '0');
      break;
    default:
      return 0;
    }
  }
  return negative
       ? - result
       : result;
}

#endif
