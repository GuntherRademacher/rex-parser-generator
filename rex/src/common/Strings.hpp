/*
 * Strings.hpp
 *
 *  Created on: 18.10.2016
 *      Author: Gunther
 */

#ifndef STRINGS_HPP
#define STRINGS_HPP

#include "../common/WString.hpp"
#include "../common/Decoder.hpp"

class Strings
{
public:
  static size_t lineLength(const wchar_t *source)
  {
    const wchar_t *lf = wcschr(source, L'\n');
    return lf == 0 ? wcslen(source) : lf - source;
  }

  static size_t lineLength(const char *source)
  {
    const char *lf = strchr(source, '\n');
    return lf == 0 ? strlen(source) : lf - source;
  }

  static WString string(const wchar_t *string, int length)
  {
    return WString(string, length);
  }

  static WString string(const char *string, int length)
  {
    wchar_t *decoded = Decoder::decode(string, length);
    WString wstring = WString(decoded);
    free(decoded);
    return wstring;
  }

  template<class CHAR>
  static void getLineAndColumn(const CHAR *source, int position, int *line, int *column)
  {
    int l, c, p;

    for (p = 0, l = 1, c = 1; p < position; p++)
    {
      if (source[p] == '\n')
      {
        l++;
        c = 1;
      }
      else
      {
        c++;
      }
    }
    *line = l;
    *column = c;
  }

  static wchar_t eof()
  {
    return 0x1a;
  }

  template<class CHAR>
  static WString getLine(const CHAR *source, int line)
  {
    if (line < 1)
    {
      return WString();
    }
    else if (line > 1)
    {
      int l = 1;
      for (int p = 0; ; ++p)
      {
        CHAR c = source[p];
        if (c == 0)
        {
          return WString(L"\x1A");
        }
        else if (c == '\n')
        {
          if (++l == line)
          {
            source = source + p + 1;
            break;
          }
        }
      }
    }
    return string(source, lineLength(source));
  }
};

#endif
