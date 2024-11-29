/*
 * WString.hpp
 *
 *  Created on: Sep 17, 2009
 *      Author: Gunther
 */

#ifndef WSTRING_HPP
#define WSTRING_HPP

#include <string>

class WStringRef
{
public:
  WStringRef(const wchar_t *p, size_t s) : pointer(p), size(s) {}

  wchar_t *copy() const
  {
    wchar_t *result = ALLOCATE_ARRAY(wchar_t, size + 1);
    wcsncpy(result, pointer, size);
    result[size] = 0;
    return result;
  }

  bool operator==(const wchar_t *rhs) const
  {
    if (wcsncmp(pointer, rhs, size)) return false;
    return rhs[size] == 0;
  }

  bool operator!=(const wchar_t *rhs) const {return ! (*this == rhs);}

  const wchar_t *pointer;
  const size_t size;
};

typedef std::basic_string<char> CString;

class WString : public std::basic_string<wchar_t>
{              typedef std::basic_string<wchar_t>
               super;
public:
  WString() {}
  WString(const wchar_t *p) : super(p) {}
  WString(const wchar_t *p, size_t s) : super(p, s) {}
  WString(const WStringRef &w) : super(w.pointer, w.size) {}
  WString(size_t n, wchar_t c) : super(n, c) {}

  WString &rtrim() {
    // trim from end
    erase(find_last_not_of(L" ") + 1);
    return *this;
  }
};

template<class CHAR>
bool isWhiteSpace(CHAR c)
{
  return c == ' ' || c == '\t' || c == '\r' || c == '\n';
}

template<class CHAR>
const CHAR *STRnCHR(const CHAR *s, size_t count, CHAR c)
{
  for (size_t i = 0; i < count; ++i)
  {
    if (s[i] == c) return s + i;
  }
  return 0;
}

#endif
