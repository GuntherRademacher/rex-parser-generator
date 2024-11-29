/*
 * Exceptions.hpp
 *
 *  Created on: 13.09.2008
 *      Author: Gunther
 */

#ifndef EXCEPTIONS_HPP_
#define EXCEPTIONS_HPP_

#include "../common/WString.hpp"
#include <wchar.h>

class Complaint
{
public:
  Complaint() : offset(-1) {}
  Complaint(const wchar_t *aMsg, const wchar_t *aName, int anOffset = -1) : offset(anOffset), msg(aMsg), name(aName) {}
  Complaint(const wchar_t *aMsg, const WString &aName, int anOffset = -1) : offset(anOffset), msg(aMsg), name(aName) {}
  Complaint(const WString &aMsg, const wchar_t *aName, int anOffset = -1) : offset(anOffset), msg(aMsg), name(aName) {}
  Complaint(const WString &aMsg, const WString &aName, int anOffset = -1) : offset(anOffset), msg(aMsg), name(aName) {}

  int offset;
  WString msg;
  WString name;
};

#endif
