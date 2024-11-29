// This file was generated on Sun Nov 24, 2024 16:09 (UTC+01) by REx v6.0 which is Copyright (c) 1979-2024 by Gunther Rademacher <grd@gmx.net>
// REx command line: Compress.ebnf -cpp -char -a rex

#ifndef COMPRESS_HPP
#define COMPRESS_HPP
#include <stdio.h>
#include <string>
#include <algorithm>
                                                            #line 3 "Compress.ebnf"
                                                            #include "../common/WString.hpp"
                                                            #include "../common/IntString.hpp"
                                                            #include <stdlib.h>

                                                            class Compress
                                                            {
                                                            public:
                                                              Compress(const char *input)
                                                              {
                                                                initialize(input);
                                                              }

                                                              ~Compress()
                                                              {
                                                              }

                                                              IntString &getIntegers()
                                                              {
                                                                return integers;
                                                              }

                                                            private:
                                                              void add()
                                                              {
                                                                CString value(input + b0, e0 - b0);
                                                                integers.push_back(atoi(value.c_str()));
                                                              }

                                                              IntString integers;
                                                            #line 40 "Compress.hpp"
public:
  class ParseException
  {
  private:
    int begin, end, offending, expected, state;
    friend class Compress;

  protected:
    ParseException(int b, int e, int s, int o, int x)
    : begin(b), end(e), offending(o), expected(x), state(s)
    {
    }

  public:
    const char *getMessage() const
    {
      return offending < 0
           ? "lexical analysis failed"
           : "syntax error";
    }

    int getBegin() const {return begin;}
    int getEnd() const {return end;}
    int getState() const {return state;}
    int getOffending() const {return offending;}
    int getExpected() const {return expected;}
  };

  void initialize(const char *source)
  {
    input = source;
    reset(0, 0, 0);
  }

  const char *getInput() const
  {
    return input;
  }

  int getTokenOffset() const
  {
    return b0;
  }

  int getTokenEnd() const
  {
    return e0;
  }

  void reset(int l, int b, int e)
  {
            b0 = b; e0 = b;
    l1 = l; b1 = b; e1 = e;
    end = e;
  }

  void reset()
  {
    reset(0, 0, 0);
  }

  static const char *getOffendingToken(ParseException e)
  {
    return e.getOffending() < 0 ? 0 : TOKEN[e.getOffending()];
  }

  static void getExpectedTokenSet(const ParseException &e, const char **set, int size)
  {
    if (e.expected < 0)
    {
      getTokenSet(- e.state, set, size);
    }
    else if (size == 1)
    {
      set[0] = 0;
    }
    else if (size > 1)
    {
      set[0] = TOKEN[e.expected];
      set[1] = 0;
    }
  }

  static std::string to_string(int i)
  {
    const char *sign = i < 0 ? "-" : "";
    std::string a;
    do
    {
      a += '0' + abs(i % 10);
      i /= 10;
    }
    while (i != 0);
    a += sign;
    std::reverse(a.begin(), a.end());
    return a;
  }

  std::string getErrorMessage(const ParseException &e)
  {
    std::string message(e.getMessage());
    const char *found = getOffendingToken(e);
    if (found != 0)
    {
      message += ", found ";
      message += found;
    }
    const char *expected[64];
    getExpectedTokenSet(e, expected, sizeof expected / sizeof *expected);
    message += "\nwhile expecting ";
    const char *delimiter(expected[1] ? "[" : "");
    for (const char **x = expected; *x; ++x)
    {
      message += delimiter;
      message += *x;
      delimiter = ", ";
    }
    message += expected[1] ? "]\n" : "\n";
    int size = e.getEnd() - e.getBegin();
    if (size != 0 && found == 0)
    {
      message += "after successfully scanning ";
      message += to_string(size);
      message += " characters beginning ";
    }
    int line = 1;
    int column = 1;
    for (int i = 0; i < e.getBegin(); ++i)
    {
      if (input[i] == L'\n')
      {
        ++line;
        column = 1;
      }
      else
      {
        ++column;
      }
    }
    message += "at line ";
    message += to_string(line);
    message += ", column ";
    message += to_string(column);
    message += ":\n...";
    const char *w = input + e.getBegin();
    for (int i = 0; i < 64 && *w; ++i)
    {
      message += *w++;
    }
    message += "...";
    return message;
  }

  void parse_IntegerList()
  {
    lookahead1W(0);                 // Whitespace | Integer
    consume(2);                     // Integer
                                                            #line 33 "Compress.ebnf"
                                                            add();
                                                            #line 200 "Compress.hpp"
    for (;;)
    {
      lookahead1W(1);               // Whitespace | Integer | ','
      if (l1 == 4)                  // ','
      {
        consume(4);                 // ','
      }
      lookahead1W(0);               // Whitespace | Integer
      consume(2);                   // Integer
                                                            #line 36 "Compress.ebnf"
                                                            add();
                                                            #line 212 "Compress.hpp"
      lookahead1W(2);               // Whitespace | Integer | EOF | ','
      if (l1 == 3)                  // EOF
      {
        break;
      }
    }
    consume(3);                     // EOF
  }

private:

  void consume(int t)
  {
    if (l1 == t)
    {
      b0 = b1; e0 = e1; l1 = 0;
    }
    else
    {
      error(b1, e1, 0, l1, t);
    }
  }

  int matchW(int tokenSetId)
  {
    int code;
    for (;;)
    {
      code = match(tokenSetId);
      if (code != 1)                // Whitespace
      {
        break;
      }
    }
    return code;
  }

  void lookahead1W(int tokenSetId)
  {
    if (l1 == 0)
    {
      l1 = matchW(tokenSetId);
      b1 = begin;
      e1 = end;
    }
  }

  int error(int b, int e, int s, int l, int t)
  {
    throw ParseException(b, e, s, l, t);
  }

  int     b0, e0;
  int l1, b1, e1;

  const char *input;
  int begin;
  int end;

  int match(int tokenSetId)
  {
    begin = end;
    int current = end;
    int result = INITIAL[tokenSetId];
    int state = 0;

    for (int code = result & 7; code != 0; )
    {
      int charclass;
      int c0 = (unsigned char) input[current];
      ++current;
      if (c0 < 0x80)
      {
        charclass = MAP0[c0];
      }
      else
      {
        if      ((c0                 & 0xe0) == 0xc0
              && (input[current    ] & 0xc0) == 0x80)
        {
          c0 = ((c0                 & 0x1f) << 6)
             |  (input[current    ] & 0x3f);
          if (c0 < 0x80) c0 = -1; else ++current;
        }
        else if ((c0                 & 0xf0) == 0xe0
              && (input[current    ] & 0xc0) == 0x80
              && (input[current + 1] & 0xc0) == 0x80)
        {
          c0 = ((c0                 & 0x0f) << 12)
             | ((input[current    ] & 0x3f) <<  6)
             |  (input[current + 1] & 0x3f);
          if (c0 < 0x800) c0 = -1; else current += 2;
        }
        else if ((c0                 & 0xf8) == 0xf0
              && (input[current    ] & 0xc0) == 0x80
              && (input[current + 1] & 0xc0) == 0x80
              && (input[current + 2] & 0xc0) == 0x80)
        {
          c0 = ((c0                 & 0x07) << 18)
             | ((input[current    ] & 0x3f) << 12)
             | ((input[current + 1] & 0x3f) <<  6)
             | ( input[current + 2] & 0x3f       );
          if (c0 < 0x10000 || c0 > 0x10ffff) c0 = -1; else current += 3;
        }

        if (c0 < 0xd800)
        {
          int c1 = c0 >> 5;
          charclass = MAP1[(c0 & 31) + MAP1[(c1 & 31) + MAP1[c1 >> 5]]];
        }
        else
        {
          charclass = 0;
        }
      }

      state = code;
      int i0 = (charclass << 3) + code - 1;
      code = TRANSITION[(i0 & 3) + TRANSITION[i0 >> 2]];
      if (code > 7)
      {
        result = code;
        code &= 7;
        end = current;
      }
    }

    result >>= 3;
    if (result == 0)
    {
      for (end = current - 1; (input[end] & 0xc0) == 0x80; --end) ;
      return error(begin, end, state, -1, -1);
    }

    if (input[begin] == 0) end = begin;
    return (result & 7) - 1;
  }

  static void getTokenSet(int tokenSetId, const char **set, int size)
  {
    int s = tokenSetId < 0 ? - tokenSetId : INITIAL[tokenSetId] & 7;
    for (int i = 0; i < 5; i += 32)
    {
      int j = i;
      for (unsigned int f = ec(i >> 5, s); f != 0; f >>= 1, ++j)
      {
        if ((f & 1) != 0)
        {
          if (size > 1)
          {
            set[0] = TOKEN[j];
            ++set;
            --size;
          }
        }
      }
    }
    if (size > 0)
    {
      set[0] = 0;
    }
  }

  static int ec(int t, int s)
  {
    int i0 = t * 5 + s - 1;
    return EXPECTED[i0];
  }

  static const int MAP0[];
  static const int MAP1[];
  static const int INITIAL[];
  static const int TRANSITION[];
  static const int EXPECTED[];
  static const char *TOKEN[];
};

const int Compress::MAP0[] =
{
/*   0 */ 5, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
/*  37 */ 0, 0, 0, 0, 0, 0, 0, 2, 3, 0, 0, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/*  74 */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/* 111 */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

const int Compress::MAP1[] =
{
/*   0 */ 54, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56,
/*  27 */ 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56,
/*  54 */ 88, 134, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102,
/*  76 */ 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 5, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0,
/* 105 */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
/* 142 */ 0, 0, 0, 0, 2, 3, 0, 0, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0
};

const int Compress::INITIAL[] =
{
/* 0 */ 1, 2, 3
};

const int Compress::TRANSITION[] =
{
/*  0 */ 29, 29, 12, 29, 19, 29, 16, 29, 26, 28, 22, 29, 20, 20, 20, 20, 5, 5, 5, 0, 40, 40, 0, 0, 32, 0, 29, 29, 29, 0,
/* 30 */ 0, 0, 0
};

const int Compress::EXPECTED[] =
{
/* 0 */ 6, 22, 30, 2, 4
};

const char *Compress::TOKEN[] =
{
  "(0)",
  "Whitespace",
  "Integer",
  "EOF",
  "','"
};

#endif

// End
