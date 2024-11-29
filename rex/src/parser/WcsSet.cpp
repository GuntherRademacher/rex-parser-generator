/*
 * WcsSet.cpp
 *
 *  Created on: 10.11.2014
 *      Author: Gunther
 */

#ifndef WCSSET_HPP_
#define WCSSET_HPP_

#include "../common/Memory.hpp"
#include "WcsSet.hpp"

WcsSet::~WcsSet()
{
  iterator next = begin();
  for (iterator i = next; i != end(); i = next)
  {
    ++next;
    free(static_cast<void *>(*i));
  }
}

#endif
