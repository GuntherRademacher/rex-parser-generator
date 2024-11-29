/*
 * Format.hpp
 *
 *  Created on: 03.10.2008
 *      Author: Gunther
 */

#ifndef FORMAT_HPP_
#define FORMAT_HPP_

#include "Decoder.hpp"
#include "WString.hpp"
#include "Error.hpp"

#include <ctype.h>
#include <string.h>
#include <limits.h>
#include <stdio.h>
#include <algorithm>
#include <chrono>

class Format
{
public:
  static char *wchar2char(const wchar_t *string)
  {
    size_t length = wcslen(string) + 1;
    char *encoded = ALLOCATE_ARRAY(char, length);

    for (size_t i = 0;; i++)
    {
      int c = string[i];
      encoded[i] = c & 0xff;
      if (c == 0)
      {
        break;
      }
    }
    return encoded;
  }

  static wchar_t *char2wchar(const char *encoded)
  {
    return Decoder::decode(encoded);
  }

  static char *xcscpy(char* destination, const char* source) {return strcpy(destination, source);}
  static wchar_t *xcscpy(wchar_t* destination, const wchar_t* source) {return wcscpy(destination, source);}
  static char *xcsncpy(char* destination, const char* source, size_t num) {return strncpy(destination, source, num);}
  static wchar_t *xcsncpy(wchar_t* destination, const wchar_t* source, size_t num) {return wcsncpy(destination, source, num);}
  static const wchar_t* xcsrchr (const wchar_t* ws, wchar_t wc) {return wcsrchr(ws, wc);}
  static const char* xcsrchr (const char* s, char c) {return strrchr(s, c);}
  static wchar_t* xcsrchr(wchar_t* ws, wchar_t wc) {return wcschr(ws, wc);}
  static char* xcsrchr(char* s, char c) {return strrchr(s, c);}
  static size_t xcslen(const wchar_t* wcs) {return wcslen(wcs);}
  static size_t xcslen(const char* cs) {return strlen(cs);}

  template<class CHAR>
  static CHAR *newFileName(const CHAR *fileName, const CHAR *extension)
  {
    const CHAR *lastSlash = xcsrchr(fileName, '/');
    if (lastSlash)
    {
      fileName = lastSlash + 1;
    }
    const CHAR *lastBackSlash = xcsrchr(fileName, '\\');
    if (lastBackSlash)
    {
      fileName = lastBackSlash + 1;
    }
    const CHAR *lastPeriod = xcsrchr(fileName, '.');
    size_t fileNameSize = lastPeriod
                        ? lastPeriod - fileName
                        : xcslen(fileName);
    size_t extensionSize = xcslen(extension);
    CHAR *newFileName = ALLOCATE_ARRAY(CHAR, fileNameSize + extensionSize + 1);
    xcsncpy(newFileName, fileName, fileNameSize);
    xcscpy(newFileName + fileNameSize, extension);
    return newFileName;
  }

  static size_t countOccurrences(const wchar_t *string, wchar_t c)
  {
    int n = 0;
    for (const wchar_t *s = string; *s; s++)
    {
      if (*s == c) n++;
    }
    return n;
  }

  static int indentation(const wchar_t *string);
  static wchar_t *reIndent(const wchar_t *string, size_t indentation, bool incremental = false);
  static WString reIndent(const WString string, size_t indentation, bool incremental = false);

  template<class INT>
  static size_t width(INT value, INT base = 10)
  {
    size_t n = value >= 0 ? 1 : 2;
    while ((value /= base) != 0) n++;
    return n;
  }

  template<class CHAR, class INT>
  CHAR *toString(INT v, int base = 0, int minWidth = 0, int maxWidth = 0, const CHAR *prefix = 0, const char *digits = 0, bool suffix = false)
  {
    base = base ? base : 10;
    digits = digits ? digits : "0123456789ABCDEF";
    INT value = v;
    CHAR *buffer = (CHAR *) toStringBuffer;
    CHAR *c0 = buffer;
    if (prefix)
    {
      for (size_t i = 0; prefix[i]; ++i)
      {
        *c0++ = prefix[i];
      }
    }
    if (value < 0 && base == 10)
    {
      *c0++ = (CHAR) '-';
    }
    CHAR *c = c0;
    do
    {
      *c++ = (CHAR) digits[abs((int) (value % base))];
      value /= base;
    }
    while (value);

    while (c - buffer < minWidth)
    {
      *c++ = base == 10 ? ' ' : '0';
    }
    std::reverse(c0, c);
    if (suffix)
    {
      INT d = abs((int) v) % 100;
      if (d / 10 == 1) d = 0;
      switch (d % 10)
      {
      case 1:  *c++ = 's'; *c++ = 't'; break;
      case 2:  *c++ = 'n'; *c++ = 'd'; break;
      case 3:  *c++ = 'r'; *c++ = 'd'; break;
      default: *c++ = 't'; *c++ = 'h'; break;
      }
    }
    *c = 0;
    c0 = (CHAR *) toStringBuffer;
    if (maxWidth && c - c0 > maxWidth)
    {
      c0 = c - maxWidth;
    }
    return c0;
  }

  static wchar_t *camelCase(const wchar_t *hyphenSeparated)
  {
    wchar_t *result = ALLOCATE_ARRAY(wchar_t, wcslen(hyphenSeparated) + 1);
    wchar_t *r = result;
    wchar_t h1;
    for (wchar_t h0 = 0; ; h0 = h1)
    {
      h1 = *hyphenSeparated++;
      if (h1 != L'-')
      {
        if (h0 == L'-')
        {
          h1 = (wchar_t) towupper((int) h1);
        }
        *r++ = h1;
        if (h1 == 0) break;
      }
    }
    return result;
  }

  static void dateString(char *date, size_t size)
  {
    const char *days = "SunMonTueWedThuFriSat";
    const char *months = "JanFebMarAprMayJunJulAugSepOctNovDec";

    auto now = std::chrono::system_clock::now();
    auto now_c = std::chrono::system_clock::to_time_t(now);
    std::tm localTime = *std::localtime(&now_c);
    std::tm utcTime = *std::gmtime(&now_c);
    int timezoneOffset = static_cast<int>(std::difftime(std::mktime(&utcTime), std::mktime(&localTime)));
    int dtime = timezoneOffset - (localTime.tm_isdst == 1 ? 3600 : 0);

    char tz[16] = {dtime == 0 ? (char) 0 : dtime > 0 ? '-' : '+'};
    if (dtime < 0) dtime = - dtime;

    sprintf(tz + 1, "%02d%c%02d", dtime / 3600, dtime % 3600 == 0 ? 0 : ':', dtime % 3600 / 60);

    char s[64];
    sprintf(s, "%.3s %.3s %d, %4d %02d:%02d (UTC%s)",
      &days[localTime.tm_wday * 3],
      &months[localTime.tm_mon * 3],
      localTime.tm_mday,
      localTime.tm_year + 1900,
      localTime.tm_hour,
      localTime.tm_min,
      tz);

    strncpy(date, s, size);
  }

  static char *commandLine(char** argv)
  {
    CString commandLine;
    const char *delimiter = "";
    for (int i = 0; argv[i]; ++i)
    {
      commandLine += delimiter;
      delimiter = " ";
      bool hasSpaces = strstr(argv[i], " ") != 0;
      if (hasSpaces) commandLine += '"';
      for (char *c = argv[i]; *c; ++c)
      {
        if (*c == '"') commandLine += '\\';
        commandLine += *c;
      }
      if (hasSpaces) commandLine += '"';
    }
    return strdup(commandLine.c_str());
  }

  template<class STRING, class CHAR>
  static STRING acceptableName(const CHAR *name, bool allowPeriod = false)
  {
    if (name == 0)
    {
      return STRING();
    }

    for (const CHAR *i = name; *i; ++i)
    {
      if (*i == '-' || (! allowPeriod && *i == '.'))
      {
        STRING modifiedName;
        for (const CHAR *i = name; *i; ++i)
        {
          modifiedName.push_back(*i == '-' || (! allowPeriod && *i == '.') ? '_' : *i);
        }
        return modifiedName;
      }
    }

    return STRING(name);
  }

private:
  wchar_t toStringBuffer[64];
};

#endif /* FORMAT_HPP_ */
