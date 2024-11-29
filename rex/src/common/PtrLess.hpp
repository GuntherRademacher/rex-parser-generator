/*
 * PtrLess.hpp
 *
 *  Created on: 23.09.2009
 *      Author: Gunther
 */

#ifndef PTRLESS_HPP
#define PTRLESS_HPP

#include <string.h>

template <class T>
struct PtrLess
{
  bool operator()(const T *lhs, const T *rhs) const
  {
    return *lhs < *rhs;
  }
};

template <>
struct PtrLess<char>
{
  bool operator()(const char *lhs, const char *rhs) const
  {
    return strcmp(lhs, rhs) < 0;
  }
};

template <>
struct PtrLess<wchar_t>
{
  bool operator()(const wchar_t *lhs, const wchar_t *rhs) const
  {
    return wcscmp(lhs, rhs) < 0;
  }
};

#endif
