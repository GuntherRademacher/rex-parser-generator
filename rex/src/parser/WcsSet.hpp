/*
 * WcsSet.hpp
 *
 *  Created on: 10.11.2014
 *      Author: Gunther
 */

#include <set>

class LtWcs
{
public:
  bool operator() (const wchar_t *s1, const wchar_t *s2) const {return wcscmp(s1, s2) < 0;}
};

class WcsSet : public std::set<wchar_t *, LtWcs>
{
public:
  ~WcsSet();
};
