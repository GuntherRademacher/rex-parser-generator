#ifndef ENCODER_HPP_
#define ENCODER_HPP_
#include "Encoder.hpp"
#include "Decoder.hpp"
#include "Error.hpp"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <wchar.h>
#include <new>

class Encoder
{
public:
  static char *encode(const wchar_t *unencoded)
  {
#if SELFTEST
    wchar_t test[3] = {0x396, 0, 0};
    for (int i = 0; unencoded[i]; ++i)
    {
      test[0] = unencoded[i];
      test[1] = 0;
      if (test[0] >= 0xd800 && test[0] < 0xe000)
      {
        test[1] = unencoded[++i];
      }
      char *e = encode_utf8(test);
      if (e == 0)
      {
        printf("e == 0\n");
        printf("wcslen(test) %d\n", wcslen(test));
        printf("i = %d, test = %x %x %x\n", i, test[0], test[1], test[2]);
        exit(1);
      }
      wchar_t *d = Decoder::decode(e, L"UTF-8");
      if (d == 0)
      {
        printf("d == 0\n");
        printf("wcslen(test) %d\n", wcslen(test));
        printf("i = %d, test = %x %x %x\n", i, test[0], test[1], test[2]);
        printf("strlen(e) %d\n", strlen(e));
        printf("i = %d, test = %x %x %x %x\n", i, e[0] & 255, e[1] & 255, e[2] & 255, e[3] & 255);
        exit(1);
      }
      if (wcscmp(d, test))
      {
        printf("strcmp != 0\n");
        printf("wcslen(test) %d\n", wcslen(test));
        printf("strlen(e) %d\n", strlen(e));
        printf("wcslen(d) %d\n", wcslen(d));
        printf("i = %d, u = %x, d = %x, test = %x\n", i, unencoded[i], d[0], test[0]);
        for (int j = 0; e[j]; ++j)
          printf("   e[%d] = %x\n", j, e[j] & 0xff);
        exit(1);
      }
      free(e);
      free(d);
    }
#endif

    return encode_utf8(unencoded);
  }

  static size_t encode_utf8(int codepoint, char *encoded)
  {
    size_t size = 0;

    if (codepoint < 0x80)
    {
      encoded[size++] = codepoint;
    }
    else if (codepoint < 0x800)
    {
      encoded[size++] = 0xc0 | (codepoint >> 6);
      encoded[size++] = 0x80 | (codepoint & 0x3f);
    }
    else if (codepoint < 0xd800)
    {
      encoded[size++] = 0xe0 | ( codepoint          >> 12);
      encoded[size++] = 0x80 | ((codepoint & 0xfff) >>  6);
      encoded[size++] = 0x80 | ( codepoint &  0x3f       );
    }
    else if (codepoint < 0xe000)
    {
      return -1;
    }
    else if (codepoint < 0x10000)
    {
      encoded[size++] = 0xe0 | ( codepoint          >> 12);
      encoded[size++] = 0x80 | ((codepoint & 0xfff) >>  6);
      encoded[size++] = 0x80 | ( codepoint &  0x3f       );
    }
    else if (codepoint < 0x110000)
    {
      encoded[size++] = 0xf0 | ( codepoint            >> 18);
      encoded[size++] = 0x80 | ((codepoint & 0x3ffff) >> 12);
      encoded[size++] = 0x80 | ((codepoint &   0xfff) >>  6);
      encoded[size++] = 0x80 | ( codepoint &    0x3f       );
    }
    else
    {
      return -1;
    }

    return size;
  }

private:
  static char *encode_utf8(const wchar_t *unencoded)
  {
    size_t length = 1;
    const wchar_t *u = unencoded;
    for (wchar_t w = *u++; w; w = *u++)
    {
           if (w <   0x80              ) length++;
      else if (w <  0x800              ) length += 2;
      else if (w > 0xd7ff && w < 0xe000) length += 2;
      else if (w < 0x8000              ) length += 3;
      else                               length += 4;
    }

    char *encoded = ALLOCATE_ARRAY(char, length);

    int w = -1;
    for (size_t used = 0; w != 0;)
    {
      w = *unencoded++;
      if (w >= 0xd800 && w < 0xe000)
      {
        int w2 = *unencoded++;
        if (w2 < 0xdc00 || w2 > 0xdfff) break;
        w = (((w & 0x3ff) << 10) | (w2 & 0x3ff)) + 0x10000;
      }
      size_t size = encode_utf8(w, encoded + used);
      if (size <= 0)
      {
        free(encoded);
        return 0;
      }
      used += size;
    }
    return encoded;
  }
};

#endif
