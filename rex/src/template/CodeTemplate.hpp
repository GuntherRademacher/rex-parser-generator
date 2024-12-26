// This file was generated on Thu Dec 26, 2024 07:44 (UTC+01) by REx v6.1-SNAPSHOT which is Copyright (c) 1979-2024 by Gunther Rademacher <grd@gmx.net>
// REx command line: CodeTemplate.ebnf -cpp -a rex

#ifndef CODETEMPLATE_HPP
#define CODETEMPLATE_HPP

#include <stdio.h>
#include <string>
#include <algorithm>
                                                            #line 3 "CodeTemplate.ebnf"
                                                            #include <vector>
                                                            class CodeFragment
                                                            {
                                                            public:
                                                              typedef enum {TARGET = 0, HOST = 1, VARIABLE = 2} FragmentType;

                                                              CodeFragment(FragmentType t, int b, int e)
                                                              : type(t), begin(b), end(e), next(0)
                                                              {}

                                                              FragmentType type;
                                                              int begin;
                                                              int end;
                                                              CodeFragment *next;
                                                            };

                                                            class CodeTemplate
                                                            {
                                                            public:
                                                              CodeTemplate() : fragmentList(0)
                                                              {
                                                                initialize(0);
                                                              }

                                                              ~CodeTemplate()
                                                              {
                                                                clear();
                                                              }

                                                              CodeFragment *parse(const wchar_t *templat)
                                                              {
                                                                initialize(templat);
                                                                parse_Template();
                                                                return fragmentList;
                                                              }

                                                              int lineNo(int lf)
                                                              {
                                                                int lo = 0, hi = (int) lfLocation.size() - 1;
                                                                for (int m = hi >> 1; lo <= hi; m = (hi + lo) >> 1)
                                                                {
                                                                                 if (lfLocation[m] > lf) hi = m - 1;
                                                                  else           if (lfLocation[m] < lf) lo = m + 1;
                                                                  else         {return m + 1;  break;}
                                                                }
                                                                return lo + 1;
                                                              }

                                                            private:
                                                              void clear()
                                                              {
                                                                CodeFragment *f = fragmentList;
                                                                for (CodeFragment *next; f; f = next == fragmentList ? 0 : next)
                                                                {
                                                                  next = f->next;
                                                                  delete f;
                                                                }
                                                                fragmentList = 0;
                                                                fragmentType = CodeFragment::TARGET;
                                                              }

                                                              void enqueue(int b, int e)
                                                              {
                                                                if (b != e)
                                                                {
                                                                  CodeFragment *f = new CodeFragment(fragmentType, b, e);
                                                                  if (fragmentList == 0)
                                                                  {
                                                                    f->next = f;
                                                                  }
                                                                  else
                                                                  {
                                                                    f->next = fragmentList->next;
                                                                    fragmentList->next = f;
                                                                  }
                                                                  fragmentList = f;
                                                                }
                                                              }

                                                              CodeFragment *fragmentList;
                                                              CodeFragment::FragmentType fragmentType;
                                                              std::vector<int> lfLocation;
                                                            #line 94 "CodeTemplate.hpp"
public:
  class ParseException
  {
  private:
    int begin, end, offending, expected, state;
    friend class CodeTemplate;

  protected:
    ParseException(int b, int e, int s, int o, int x)
    : begin(b), end(e), offending(o), expected(x), state(s)
    {
    }

  public:
    const wchar_t *getMessage() const
    {
      return offending < 0
           ? L"lexical analysis failed"
           : L"syntax error";
    }

    int getBegin() const {return begin;}
    int getEnd() const {return end;}
    int getState() const {return state;}
    int getOffending() const {return offending;}
    int getExpected() const {return expected;}
  };

  void initialize(const wchar_t *source)
  {
    input = source;
    reset(0, 0, 0);
  }

  const wchar_t *getInput() const
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

  static const wchar_t *getOffendingToken(ParseException e)
  {
    return e.getOffending() < 0 ? 0 : TOKEN[e.getOffending()];
  }

  static void getExpectedTokenSet(const ParseException &e, const wchar_t **set, int size)
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

  static std::wstring to_wstring(int i)
  {
    const wchar_t *sign = i < 0 ? L"-" : L"";
    std::wstring a;
    do
    {
      a += L'0' + abs(i % 10);
      i /= 10;
    }
    while (i != 0);
    a += sign;
    std::reverse(a.begin(), a.end());
    return a;
  }

  std::wstring getErrorMessage(const ParseException &e)
  {
    std::wstring message(e.getMessage());
    const wchar_t *found = getOffendingToken(e);
    if (found != 0)
    {
      message += L", found ";
      message += found;
    }
    const wchar_t *expected[64];
    getExpectedTokenSet(e, expected, sizeof expected / sizeof *expected);
    message += L"\nwhile expecting ";
    const wchar_t *delimiter(expected[1] ? L"[" : L"");
    for (const wchar_t **x = expected; *x; ++x)
    {
      message += delimiter;
      message += *x;
      delimiter = L", ";
    }
    message += expected[1] ? L"]\n" : L"\n";
    int size = e.getEnd() - e.getBegin();
    if (size != 0 && found == 0)
    {
      message += L"after successfully scanning ";
      message += to_wstring(size);
      message += L" characters beginning ";
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
    message += L"at line ";
    message += to_wstring(line);
    message += L", column ";
    message += to_wstring(column);
    message += L":\n...";
    const wchar_t *w = input + e.getBegin();
    for (int i = 0; i < 64 && *w; ++i)
    {
      message += *w++;
    }
    message += L"...";
    return message;
  }

  void parse_Template()
  {
                                                            #line 86 "CodeTemplate.ebnf"
                                                            clear();
                                                            #line 252 "CodeTemplate.hpp"
    lookahead1(5);                  // FragmentWithoutLF | FragmentWithLF | BeginVariable | EOF | '^' | '^^' | '~' |
                                    // '~~'
    if (l1 != 7                     // EOF
     && l1 != 9                     // '^'
     && l1 != 11)                   // '~'
    {
      parse_CodeFragment();
    }
    for (;;)
    {
      if (l1 == 7)                  // EOF
      {
        break;
      }
      switch (l1)
      {
      case 11:                      // '~'
        consume(11);                // '~'
        break;
      default:
        consume(9);                 // '^'
        break;
      }
                                                            #line 88 "CodeTemplate.ebnf"
                                                            fragmentType = (CodeFragment::FragmentType) (1 - fragmentType);
                                                            #line 278 "CodeTemplate.hpp"
      lookahead1(5);                // FragmentWithoutLF | FragmentWithLF | BeginVariable | EOF | '^' | '^^' | '~' |
                                    // '~~'
      if (l1 != 7                   // EOF
       && l1 != 9                   // '^'
       && l1 != 11)                 // '~'
      {
        parse_CodeFragment();
      }
    }
    consume(7);                     // EOF
                                                            #line 92 "CodeTemplate.ebnf"
                                                            CodeFragment *f = fragmentList->next;
                                                            fragmentList->next = 0;
                                                            fragmentList = f;
                                                            #line 293 "CodeTemplate.hpp"
  }

private:

  void parse_CodeFragment()
  {
    for (;;)
    {
      switch (l1)
      {
      case 12:                      // '~~'
        {
          consume(12);              // '~~'
                                                            #line 96 "CodeTemplate.ebnf"
                                                            enqueue(b0, e0 - 1);
                                                            #line 309 "CodeTemplate.hpp"
        }
        break;
      case 10:                      // '^^'
        {
          consume(10);              // '^^'
                                                            #line 97 "CodeTemplate.ebnf"
                                                            enqueue(b0, e0 - 1);
                                                            #line 317 "CodeTemplate.hpp"
        }
        break;
      case 1:                       // FragmentWithoutLF
        {
          consume(1);               // FragmentWithoutLF
                                                            #line 98 "CodeTemplate.ebnf"
                                                            enqueue(b0, e0);
                                                            #line 325 "CodeTemplate.hpp"
        }
        break;
      case 2:                       // FragmentWithLF
        {
          consume(2);               // FragmentWithLF
                                                            #line 100 "CodeTemplate.ebnf"
                                                            enqueue(b0, e0);
                                                            lfLocation.push_back(e0 - 1);
                                                            #line 334 "CodeTemplate.hpp"
        }
        break;
      default:
        {
          consume(3);               // BeginVariable
          lookahead1(4);            // Whitespace | '$'
          if (l1 == 4)              // Whitespace
          {
            consume(4);             // Whitespace
          }
          lookahead1(2);            // '$'
          consume(8);               // '$'
          lookahead1(0);            // VariableName
          consume(5);               // VariableName
                                                            #line 105 "CodeTemplate.ebnf"
                                                            fragmentType = CodeFragment::VARIABLE;
                                                            enqueue(b0, e0);
                                                            fragmentType = CodeFragment::HOST;
                                                            #line 353 "CodeTemplate.hpp"
          lookahead1(3);            // Whitespace | EndVariable
          if (l1 == 4)              // Whitespace
          {
            consume(4);             // Whitespace
          }
          lookahead1(1);            // EndVariable
          consume(6);               // EndVariable
        }
        break;
      }
      lookahead1(5);                // FragmentWithoutLF | FragmentWithLF | BeginVariable | EOF | '^' | '^^' | '~' |
                                    // '~~'
      if (l1 == 7                   // EOF
       || l1 == 9                   // '^'
       || l1 == 11)                 // '~'
      {
        break;
      }
    }
  }

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

  void lookahead1(int tokenSetId)
  {
    if (l1 == 0)
    {
      l1 = match(tokenSetId);
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

  const wchar_t *input;
  int begin;
  int end;

  int match(int tokenSetId)
  {
    begin = end;
    int current = end;
    int result = INITIAL[tokenSetId];
    int state = 0;

    for (int code = result & 63; code != 0; )
    {
      int charclass;
      int c0 = input[current];
      ++current;
      if (c0 < 0x80)
      {
        charclass = MAP0[c0];
      }
      else if (c0 < 0xd800)
      {
        int c1 = c0 >> 5;
        charclass = MAP1[(c0 & 31) + MAP1[(c1 & 31) + MAP1[c1 >> 5]]];
      }
      else
      {
        if (c0 < 0xdc00)
        {
          int c1 = input[current];
          if (c1 >= 0xdc00 && c1 < 0xe000)
          {
            ++current;
            c0 = ((c0 & 0x3ff) << 10) + (c1 & 0x3ff) + 0x10000;
          }
        }
        int lo = 0, hi = 1;
        for (int m = 1; ; m = (hi + lo) >> 1)
        {
          if (MAP2[m] > c0) hi = m - 1;
          else if (MAP2[2 + m] < c0) lo = m + 1;
          else {charclass = MAP2[4 + m]; break;}
          if (lo > hi) {charclass = 0; break;}
        }
      }

      state = code;
      int i0 = (charclass << 6) + code - 1;
      code = TRANSITION[(i0 & 7) + TRANSITION[i0 >> 3]];
      if (code > 63)
      {
        result = code;
        code &= 63;
        end = current;
      }
    }

    result >>= 6;
    if (result == 0)
    {
      end = current - 1;
      int c1 = input[end];
      if (c1 >= 0xdc00 && c1 < 0xe000) --end;
      return error(begin, end, state, -1, -1);
    }

    if ((result & 16) != 0)
    {
      end = begin;
    }

    if (input[begin] == 0) end = begin;
    return (result & 15) - 1;
  }

  static void getTokenSet(int tokenSetId, const wchar_t **set, int size)
  {
    int s = tokenSetId < 0 ? - tokenSetId : INITIAL[tokenSetId] & 63;
    for (int i = 0; i < 13; i += 32)
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
    int i0 = t * 35 + s - 1;
    return EXPECTED[(i0 & 3) + EXPECTED[i0 >> 2]];
  }

  static const int MAP0[];
  static const int MAP1[];
  static const int MAP2[];
  static const int INITIAL[];
  static const int TRANSITION[];
  static const int EXPECTED[];
  static const wchar_t *TOKEN[];
};

const int CodeTemplate::MAP0[] =
{
/*   0 */ 13, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 3, 3,
/*  36 */ 4, 3, 3, 3, 3, 3, 3, 3, 3, 5, 3, 3, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 3, 3, 3, 3, 3, 3, 3, 6, 6, 6, 6, 7, 6, 6, 6,
/*  73 */ 6, 6, 6, 6, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 6, 9, 6, 6, 3, 3, 3, 10, 11, 3, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
/* 109 */ 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 3, 3, 3, 12, 3
};

const int CodeTemplate::MAP1[] =
{
/*   0 */ 54, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58,
/*  27 */ 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58,
/*  54 */ 90, 122, 211, 180, 148, 148, 148, 148, 148, 148, 148, 148, 148, 148, 148, 148, 148, 148, 148, 148, 148, 148,
/*  76 */ 148, 148, 148, 148, 148, 148, 148, 148, 148, 148, 148, 148, 148, 148, 13, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 0, 0,
/* 103 */ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 3, 3, 4, 3, 3, 3, 3, 3, 3, 3, 3, 5, 3, 3, 5, 5,
/* 140 */ 5, 5, 5, 5, 5, 5, 5, 5, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
/* 177 */ 3, 3, 3, 3, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 3, 3, 3, 12, 3, 6,
/* 213 */ 6, 6, 6, 7, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 6, 9, 6, 6, 3, 3, 3, 10, 11
};

const int CodeTemplate::MAP2[] =
{
/* 0 */ 57344, 65536, 65533, 1114111, 3, 3
};

const int CodeTemplate::INITIAL[] =
{
/* 0 */ 1, 2, 3, 4, 5, 6
};

const int CodeTemplate::TRANSITION[] =
{
/*   0 */ 168, 168, 168, 168, 168, 168, 168, 168, 211, 112, 231, 319, 125, 168, 168, 168, 183, 136, 205, 141, 125, 168,
/*  22 */ 168, 168, 291, 314, 231, 117, 149, 168, 168, 168, 160, 177, 231, 117, 149, 168, 168, 168, 291, 314, 231, 280,
/*  44 */ 149, 168, 168, 168, 291, 314, 234, 247, 149, 168, 168, 168, 330, 314, 275, 247, 149, 168, 168, 168, 191, 225,
/*  66 */ 242, 247, 149, 168, 168, 168, 291, 314, 255, 247, 149, 168, 168, 168, 263, 198, 168, 128, 288, 168, 168, 168,
/*  88 */ 291, 314, 269, 299, 149, 168, 168, 168, 307, 169, 168, 152, 327, 168, 168, 168, 217, 167, 168, 341, 338, 168,
/* 110 */ 168, 168, 1472, 330, 139, 12, 141, 141, 0, 0, 141, 0, 141, 0, 141, 33, 1280, 1280, 0, 0, 0, 0, 0, 34, 34, 34,
/* 136 */ 1472, 330, 204, 12, 192, 192, 0, 0, 192, 0, 225, 33, 225, 0, 1280, 1280, 0, 0, 0, 0, 0, 35, 35, 35, 0, 0, 576,
/* 163 */ 0, 576, 142, 0, 1472, 0, 0, 0, 0, 0, 0, 0, 0, 832, 1472, 0, 142, 18, 141, 141, 0, 0, 0, 330, 330, 204, 0,
/* 190 */ 1472, 7, 0, 0, 0, 0, 141, 0, 1472, 0, 0, 0, 0, 0, 704, 0, 0, 192, 0, 0, 192, 0, 0, 0, 330, 330, 139, 0, 1472,
/* 219 */ 0, 1472, 0, 512, 0, 1472, 1472, 0, 141, 0, 141, 147, 0, 0, 141, 0, 0, 141, 0, 0, 141, 410, 0, 0, 21, 141, 0,
/* 246 */ 0, 141, 410, 0, 158, 31, 158, 31, 141, 20, 0, 141, 0, 0, 153, 410, 27, 0, 8, 0, 8, 0, 655, 0, 0, 141, 23, 0,
/* 274 */ 141, 0, 0, 150, 0, 24, 141, 410, 0, 141, 0, 158, 31, 141, 34, 0, 1280, 0, 0, 0, 0, 0, 141, 0, 1472, 156, 410,
/* 301 */ 29, 141, 0, 158, 31, 141, 0, 9, 0, 9, 0, 784, 0, 1472, 0, 141, 0, 141, 141, 0, 0, 141, 0, 160, 33, 160, 35,
/* 328 */ 1280, 0, 0, 0, 0, 0, 0, 141, 17, 1472, 1280, 1280, 1280, 0, 0, 0, 0, 0, 1280, 1280, 1280
};

const int CodeTemplate::EXPECTED[] =
{
/*  0 */ 11, 9, 15, 24, 28, 29, 30, 20, 18, 272, 7822, 32, 64, 256, 80, 64, 16, 14, 8, 8, 8, 14, 8, 14, 6, 14, 1024,
/* 27 */ 4096, 32, 8, 14, 32, 8, 14
};

const wchar_t *CodeTemplate::TOKEN[] =
{
  L"%ERROR",
  L"FragmentWithoutLF",
  L"FragmentWithLF",
  L"BeginVariable",
  L"Whitespace",
  L"VariableName",
  L"EndVariable",
  L"EOF",
  L"'$'",
  L"'^'",
  L"'^^'",
  L"'~'",
  L"'~~'"
};

#endif

// End
