// This file was generated on Sun Nov 24, 2024 16:09 (UTC+01) by REx v6.0 which is Copyright (c) 1979-2024 by Gunther Rademacher <grd@gmx.net>
// REx command line: RExParser.ebnf -lalr 1 -cpp -char -a rex

#ifndef REXPARSER_HPP
#define REXPARSER_HPP
#include <stdio.h>
#include <string>
#include <algorithm>
                                                            #line 2 "RExParser.ebnf"
                                                            #include "LexerGeneratorImpl.hpp"
                                                            #include <string>

                                                            class RExParser : public LexerGeneratorImpl
                                                            {
                                                            public:
                                                              void parse(std::string input)
                                                              {
                                                                initialize(input.c_str());
                                                                try
                                                                {
                                                                  parse_regular_grammar();
                                                                }
                                                                catch (ParseException &pe)
                                                                {
                                                                  fprintf(stderr, "%s\n", getErrorMessage(pe).c_str());
                                                                  noerrors++;
                                                                  // TODO: continue parsing for reporting more syntax errors
                                                                }
                                                              }

                                                              CString getToken() const
                                                              {
                                                                return CString(input + b0, e0 - b0);
                                                              }
                                                            #line 36 "RExParser.hpp"
public:
  class ParseException
  {
  private:
    int begin, end, offending, expected, state;
    friend class RExParser;

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

  void parse_regular_grammar()
  {
    top = -1;
    parse(0, 0);
  }

private:

  void push(int state, int lookback)
  {
    top += 2;
    if (top >= (int) iStack.size())
      iStack.resize(iStack.size() == 0 ? 128 : iStack.size() << 1);
    iStack[top - 1] = state;
    iStack[top] = lookback;
  }

  void parse(int target, int initialState)
  {
    int state = initialState;
    int action = predict(state);
    int nonterminalId = -1;
    for (;;)
    {
      int argument = action >> 7;
      int lookback = (action >> 3) & 15;
      int shift = -1;
      int reduce = -1;
      int symbols = -1;
      switch (action & 7)
      {
      case 1: // SHIFT
        shift = argument;
        break;

      case 2: // REDUCE
        reduce = argument;
        symbols = lookback;
        break;

      case 4: // SHIFT+REDUCE
        shift = state;
        reduce = argument;
        symbols = lookback + 1;
        break;

      case 6: // ACCEPT
        return;

      default: // ERROR
        throw ParseException(b1, e1, TOKENSET[state] + 1, l1, -1);
      }

      if (shift >= 0)
      {
        if (nonterminalId < 0)
        {
          push(state, lookback);
          consume(l1);
        }
        else
        {
          push(state, lookback);
        }
        state = shift;
      }

      if (reduce < 0)
      {
        action = predict(state);
        nonterminalId = -1;
      }
      else
      {
        nonterminalId = REDUCTION[reduce];
        reduce = REDUCTION[reduce + 1];
        if (reduce >= 0)
        {
          execute(reduce);
        }
        if (symbols > 0)
        {
          top -= symbols << 1;
          state = iStack[top + 1];
        }
        action = goTo(nonterminalId, state);
      }
    }
  }

  void execute(int reduce)
  {
    switch (reduce)
    {
    case 0:
      {
                                                            #line 29 "RExParser.ebnf"
                                                            rbegin();
                                                            #line 288 "RExParser.hpp"
      }
      break;
    case 1:
      {
                                                            #line 30 "RExParser.ebnf"
                                                            finish();
                                                            #line 295 "RExParser.hpp"
      }
      break;
    case 2:
      {
                                                            #line 41 "RExParser.ebnf"
                                                            setnt(0);
                                                            #line 302 "RExParser.hpp"
      }
      break;
    case 3:
      {
                                                            #line 45 "RExParser.ebnf"
                                                            setnt(1);
                                                            #line 309 "RExParser.hpp"
      }
      break;
    case 4:
      {
                                                            #line 50 "RExParser.ebnf"
                                                            assngr();
                                                            #line 316 "RExParser.hpp"
      }
      break;
    case 5:
      {
                                                            #line 51 "RExParser.ebnf"
                                                            assignTokenId(getInteger());
                                                            #line 323 "RExParser.hpp"
      }
      break;
    case 6:
      {
                                                            #line 52 "RExParser.ebnf"
                                                            assact();
                                                            #line 330 "RExParser.hpp"
      }
      break;
    case 7:
      {
                                                            #line 54 "RExParser.ebnf"
                                                            exopen();
                                                            #line 337 "RExParser.hpp"
      }
      break;
    case 8:
      {
                                                            #line 55 "RExParser.ebnf"
                                                            exclos();
                                                            #line 344 "RExParser.hpp"
      }
      break;
    case 9:
      {
                                                            #line 60 "RExParser.ebnf"
                                                            define(slash);
                                                            #line 351 "RExParser.hpp"
      }
      break;
    case 10:
      {
                                                            #line 67 "RExParser.ebnf"
                                                            createExclusion();
                                                            #line 358 "RExParser.hpp"
      }
      break;
    case 11:
      {
                                                            #line 71 "RExParser.ebnf"
                                                            syclos(none);
                                                            #line 365 "RExParser.hpp"
      }
      break;
    case 12:
      {
                                                            #line 72 "RExParser.ebnf"
                                                            syclos(closure);
                                                            #line 372 "RExParser.hpp"
      }
      break;
    case 13:
      {
                                                            #line 73 "RExParser.ebnf"
                                                            syclos(positiveclosure);
                                                            #line 379 "RExParser.hpp"
      }
      break;
    case 14:
      {
                                                            #line 74 "RExParser.ebnf"
                                                            syclos(optional);
                                                            #line 386 "RExParser.hpp"
      }
      break;
    case 15:
      {
                                                            #line 76 "RExParser.ebnf"
                                                            maxquantity = minquantity; syclos(quantity);
                                                            #line 393 "RExParser.hpp"
      }
      break;
    case 16:
      {
                                                            #line 77 "RExParser.ebnf"
                                                            maxquantity = -1; syclos(quantity);
                                                            #line 400 "RExParser.hpp"
      }
      break;
    case 17:
      {
                                                            #line 78 "RExParser.ebnf"
                                                            syclos(quantity);
                                                            #line 407 "RExParser.hpp"
      }
      break;
    case 18:
      {
                                                            #line 79 "RExParser.ebnf"
                                                            minquantity = getInteger();
                                                            #line 414 "RExParser.hpp"
      }
      break;
    case 19:
      {
                                                            #line 80 "RExParser.ebnf"
                                                            maxquantity = getInteger();
                                                            #line 421 "RExParser.hpp"
      }
      break;
    case 20:
      {
                                                            #line 81 "RExParser.ebnf"
                                                            define(nonterminal);
                                                            #line 428 "RExParser.hpp"
      }
      break;
    case 21:
      {
                                                            #line 83 "RExParser.ebnf"
                                                            define(charstring);
                                                            #line 435 "RExParser.hpp"
      }
      break;
    case 22:
      {
                                                            #line 84 "RExParser.ebnf"
                                                            define(charset);
                                                            #line 442 "RExParser.hpp"
      }
      break;
    case 23:
      {
                                                            #line 86 "RExParser.ebnf"
                                                            define(dollar);
                                                            #line 449 "RExParser.hpp"
      }
      break;
    case 24:
      {
                                                            #line 87 "RExParser.ebnf"
                                                            define(compound);
                                                            #line 456 "RExParser.hpp"
      }
      break;
    case 25:
      {
                                                            #line 89 "RExParser.ebnf"
                                                            currentchar = getInteger();
                                                            firstchar = currentchar;
                                                             lastchar = currentchar;
                                                                         addRange();
                                                                          chclos(1);
                                                            #line 467 "RExParser.hpp"
      }
      break;
    case 26:
      {
                                                            #line 94 "RExParser.ebnf"
                                                            chclos(1);
                                                            #line 474 "RExParser.hpp"
      }
      break;
    case 27:
      {
                                                            #line 96 "RExParser.ebnf"
                                                            chclos(-1);
                                                            #line 481 "RExParser.hpp"
      }
      break;
    case 28:
      {
                                                            #line 99 "RExParser.ebnf"
                                                            addRange();
                                                            #line 488 "RExParser.hpp"
      }
      break;
    case 29:
      {
                                                            #line 104 "RExParser.ebnf"
                                                            firstchar = currentchar;
                                                            lastchar = currentchar;
                                                            #line 496 "RExParser.hpp"
      }
      break;
    case 30:
      {
                                                            #line 107 "RExParser.ebnf"
                                                            lastchar = currentchar;
                                                            #line 503 "RExParser.hpp"
      }
      break;
    case 31:
      {
                                                            #line 109 "RExParser.ebnf"
                                                            CString token = getToken();
                                                            currentchar = Decoder::decode_utf8_char(token.c_str() + 1);
                                                            #line 511 "RExParser.hpp"
      }
      break;
    case 32:
      {
                                                            #line 111 "RExParser.ebnf"
                                                            currentchar = getInteger();
                                                            #line 518 "RExParser.hpp"
      }
      break;
    case 33:
      {
                                                            #line 130 "RExParser.ebnf"
                                                            grammar=true;
                                                            #line 525 "RExParser.hpp"
      }
      break;
    case 34:
      {
                                                            #line 131 "RExParser.ebnf"
                                                            grammar=false;
                                                            #line 532 "RExParser.hpp"
      }
      break;
    case 35:
      {
                                                            #line 132 "RExParser.ebnf"
                                                            symbols=true;
                                                            #line 539 "RExParser.hpp"
      }
      break;
    case 36:
      {
                                                            #line 133 "RExParser.ebnf"
                                                            symbols=false;
                                                            #line 546 "RExParser.hpp"
      }
      break;
    case 37:
      {
                                                            #line 134 "RExParser.ebnf"
                                                            showNfa=true;
                                                            #line 553 "RExParser.hpp"
      }
      break;
    case 38:
      {
                                                            #line 135 "RExParser.ebnf"
                                                            showNfa=false;
                                                            #line 560 "RExParser.hpp"
      }
      break;
    case 39:
      {
                                                            #line 136 "RExParser.ebnf"
                                                            showDfa=true;
                                                            #line 567 "RExParser.hpp"
      }
      break;
    case 40:
      {
                                                            #line 137 "RExParser.ebnf"
                                                            showDfa=false;
                                                            #line 574 "RExParser.hpp"
      }
      break;
    case 41:
      {
                                                            #line 138 "RExParser.ebnf"
                                                            targetLanguage = C;
                                                            #line 581 "RExParser.hpp"
      }
      break;
    case 42:
      {
                                                            #line 139 "RExParser.ebnf"
                                                            targetLanguage = CPP;
                                                            #line 588 "RExParser.hpp"
      }
      break;
    case 43:
      {
                                                            #line 140 "RExParser.ebnf"
                                                            targetLanguage = CSHARP;
                                                            #line 595 "RExParser.hpp"
      }
      break;
    case 44:
      {
                                                            #line 141 "RExParser.ebnf"
                                                            targetLanguage = REX;
                                                            #line 602 "RExParser.hpp"
      }
      break;
    case 45:
      {
                                                            #line 142 "RExParser.ebnf"
                                                            targetLanguage = GO;
                                                            #line 609 "RExParser.hpp"
      }
      break;
    case 46:
      {
                                                            #line 143 "RExParser.ebnf"
                                                            targetLanguage = PYTHON;
                                                            #line 616 "RExParser.hpp"
      }
      break;
    case 47:
      {
                                                            #line 144 "RExParser.ebnf"
                                                            targetLanguage = HAXE;
                                                            #line 623 "RExParser.hpp"
      }
      break;
    case 48:
      {
                                                            #line 145 "RExParser.ebnf"
                                                            targetLanguage = JAVA;
                                                            #line 630 "RExParser.hpp"
      }
      break;
    case 49:
      {
                                                            #line 146 "RExParser.ebnf"
                                                            targetLanguage = JAVASCRIPT;
                                                            #line 637 "RExParser.hpp"
      }
      break;
    case 50:
      {
                                                            #line 147 "RExParser.ebnf"
                                                            targetLanguage = TYPESCRIPT;
                                                            #line 644 "RExParser.hpp"
      }
      break;
    case 51:
      {
                                                            #line 148 "RExParser.ebnf"
                                                            targetLanguage = SCALA;
                                                            #line 651 "RExParser.hpp"
      }
      break;
    case 52:
      {
                                                            #line 149 "RExParser.ebnf"
                                                            targetLanguage = XQUERY;
                                                            #line 658 "RExParser.hpp"
      }
      break;
    case 53:
      {
                                                            #line 150 "RExParser.ebnf"
                                                            targetLanguage = XSLT;
                                                            #line 665 "RExParser.hpp"
      }
      break;
    case 54:
      {
                                                            #line 151 "RExParser.ebnf"
                                                            append = true;
                                                            #line 672 "RExParser.hpp"
      }
      break;
    case 55:
      {
                                                            #line 152 "RExParser.ebnf"
                                                            append = false;
                                                            #line 679 "RExParser.hpp"
      }
      break;
    case 56:
      {
                                                            #line 153 "RExParser.ebnf"
                                                            targetFile = getString();
                                                            #line 686 "RExParser.hpp"
      }
      break;
    case 57:
      {
                                                            #line 154 "RExParser.ebnf"
                                                            prefix = getString();
                                                            #line 693 "RExParser.hpp"
      }
      break;
    case 58:
      {
                                                            #line 155 "RExParser.ebnf"
                                                            suffix = getString();
                                                            #line 700 "RExParser.hpp"
      }
      break;
    case 59:
      {
                                                            #line 156 "RExParser.ebnf"
                                                            stringPrefix = getString();
                                                            stringPrefixDefined = true;
                                                            #line 708 "RExParser.hpp"
      }
      break;
    case 60:
      {
                                                            #line 158 "RExParser.ebnf"
                                                            stringSuffix = getString();
                                                            stringSuffixDefined = true;
                                                            #line 716 "RExParser.hpp"
      }
      break;
    case 61:
      {
                                                            #line 161 "RExParser.ebnf"
                                                            tokenDescriptors.setTokenPrefix(getString());
                                                            #line 723 "RExParser.hpp"
      }
      break;
    case 62:
      {
                                                            #line 162 "RExParser.ebnf"
                                                            stringType = getString();
                                                            #line 730 "RExParser.hpp"
      }
      break;
    case 63:
      {
                                                            #line 163 "RExParser.ebnf"
                                                            tokenTableName = getString();
                                                            #line 737 "RExParser.hpp"
      }
      break;
    case 64:
      {
                                                            #line 164 "RExParser.ebnf"
                                                            tableName = getString();
                                                            #line 744 "RExParser.hpp"
      }
      break;
    case 65:
      {
                                                            #line 165 "RExParser.ebnf"
                                                            packageName = getString();
                                                            #line 751 "RExParser.hpp"
      }
      break;
    case 66:
      {
                                                            #line 166 "RExParser.ebnf"
                                                            className = getString();
                                                            #line 758 "RExParser.hpp"
      }
      break;
    case 67:
      {
                                                            #line 167 "RExParser.ebnf"
                                                            abbreviations=true;
                                                            #line 765 "RExParser.hpp"
      }
      break;
    case 68:
      {
                                                            #line 168 "RExParser.ebnf"
                                                            abbreviations=false;
                                                            #line 772 "RExParser.hpp"
      }
      break;
    case 69:
      {
                                                            #line 169 "RExParser.ebnf"
                                                            ambiguities=true;
                                                            #line 779 "RExParser.hpp"
      }
      break;
    case 70:
      {
                                                            #line 170 "RExParser.ebnf"
                                                            ambiguities=false;
                                                            #line 786 "RExParser.hpp"
      }
      break;
    case 71:
      {
                                                            #line 171 "RExParser.ebnf"
                                                            full=true;
                                                            #line 793 "RExParser.hpp"
      }
      break;
    case 72:
      {
                                                            #line 172 "RExParser.ebnf"
                                                            classify=true;
                                                            #line 800 "RExParser.hpp"
      }
      break;
    case 73:
      {
                                                            #line 173 "RExParser.ebnf"
                                                            classify=false;
                                                            #line 807 "RExParser.hpp"
      }
      break;
    case 74:
      {
                                                            #line 174 "RExParser.ebnf"
                                                            minimize=true;
                                                            #line 814 "RExParser.hpp"
      }
      break;
    case 75:
      {
                                                            #line 175 "RExParser.ebnf"
                                                            minimize=false;
                                                            #line 821 "RExParser.hpp"
      }
      break;
    case 76:
      {
                                                            #line 176 "RExParser.ebnf"
                                                            selfTest=true;
                                                            #line 828 "RExParser.hpp"
      }
      break;
    case 77:
      {
                                                            #line 177 "RExParser.ebnf"
                                                            selfTest=false;
                                                            #line 835 "RExParser.hpp"
      }
      break;
    case 78:
      {
                                                            #line 178 "RExParser.ebnf"
                                                            trace=true;
                                                            #line 842 "RExParser.hpp"
      }
      break;
    case 79:
      {
                                                            #line 179 "RExParser.ebnf"
                                                            trace=false;
                                                            #line 849 "RExParser.hpp"
      }
      break;
    case 80:
      {
                                                            #line 180 "RExParser.ebnf"
                                                            faster=true;
                                                            #line 856 "RExParser.hpp"
      }
      break;
    case 81:
      {
                                                            #line 181 "RExParser.ebnf"
                                                            smaller=true;
                                                            #line 863 "RExParser.hpp"
      }
      break;
    case 82:
      {
                                                            #line 182 "RExParser.ebnf"
                                                            tree=true;
                                                            #line 870 "RExParser.hpp"
      }
      break;
    case 83:
      {
                                                            #line 183 "RExParser.ebnf"
                                                            tree=false;
                                                            #line 877 "RExParser.hpp"
      }
      break;
    case 84:
      {
                                                            #line 184 "RExParser.ebnf"
                                                            nolexer=false;
                                                            #line 884 "RExParser.hpp"
      }
      break;
    case 85:
      {
                                                            #line 185 "RExParser.ebnf"
                                                            nolexer=true;
                                                            #line 891 "RExParser.hpp"
      }
      break;
    case 86:
      {
                                                            #line 186 "RExParser.ebnf"
                                                            setCaseSensitive(true);
                                                            #line 898 "RExParser.hpp"
      }
      break;
    case 87:
      {
                                                            #line 187 "RExParser.ebnf"
                                                            setCaseSensitive(false);
                                                            #line 905 "RExParser.hpp"
      }
      break;
    case 88:
      {
                                                            #line 188 "RExParser.ebnf"
                                                            compression = getInteger();
                                                            #line 912 "RExParser.hpp"
      }
      break;
    case 89:
      {
                                                            #line 190 "RExParser.ebnf"
                                                            tokenDescriptors.setErrorCode(getInteger());
                                                            #line 919 "RExParser.hpp"
      }
      break;
    case 90:
      {
                                                            #line 192 "RExParser.ebnf"
                                                            newentry();
                                                            #line 926 "RExParser.hpp"
      }
      break;
    case 91:
      {
                                                            #line 196 "RExParser.ebnf"
                                                            collectentry(tokenref); tokenref = 0;
                                                            #line 933 "RExParser.hpp"
      }
      break;
    case 92:
      {
                                                            #line 198 "RExParser.ebnf"
                                                            currenttoken = getInteger();
                                                            tokenref = ref(tokencode, true);
                                                            #line 941 "RExParser.hpp"
      }
      break;
    case 93:
      {
                                                            #line 200 "RExParser.ebnf"
                                                            tokenref = ref(tokenname, true);
                                                            #line 948 "RExParser.hpp"
      }
      break;
    case 94:
      {
                                                            #line 203 "RExParser.ebnf"
                                                            preference(preferred, tokenref); tokenref = 0;
                                                            #line 955 "RExParser.hpp"
      }
      break;
    case 95:
      {
                                                            #line 204 "RExParser.ebnf"
                                                            preferred = tokenref;
                                                            #line 962 "RExParser.hpp"
      }
      break;
    case 96:
      {
                                                            #line 206 "RExParser.ebnf"
                                                            currenttoken = getInteger();
                                                            tokenref = ref(tokencode, false);
                                                            #line 970 "RExParser.hpp"
      }
      break;
    case 97:
      {
                                                            #line 208 "RExParser.ebnf"
                                                            tokenref = ref(tokenname, false);
                                                            #line 977 "RExParser.hpp"
      }
      break;
    case 98:
      {
                                                            #line 212 "RExParser.ebnf"
                                                            delimited(delimiter, tokenref); tokenref = 0;
                                                            #line 984 "RExParser.hpp"
      }
      break;
    case 99:
      {
                                                            #line 213 "RExParser.ebnf"
                                                            CString token = getToken();
                                                            delimiter = symbolTable->insertSymbol(token.c_str(), token.size());
                                                            #line 992 "RExParser.hpp"
      }
      break;
    case 100:
      {
                                                            #line 217 "RExParser.ebnf"
                                                            firstcharLhs = firstchar; lastcharLhs = lastchar;
                                                            #line 999 "RExParser.hpp"
      }
      break;
    case 101:
      {
                                                            #line 218 "RExParser.ebnf"
                                                            equivalence();
                                                            #line 1006 "RExParser.hpp"
      }
      break;
    default:
      break;
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

  int matchW(int tokenSetId)
  {
    int code;
    for (;;)
    {
      code = match(tokenSetId);
      if (code != 1)                // whitespace
      {
        break;
      }
    }
    return code;
  }

  int error(int b, int e, int s, int l, int t)
  {
    throw ParseException(b, e, s, l, t);
  }

  int     b0, e0;
  int l1, b1, e1;
  std::vector<int> iStack;
  int top;

  const char *input;
  int begin;
  int end;

  int predict(int dpi)
  {
    int d = dpi;
    if (l1 == 0)
    {
      l1 = matchW(TOKENSET[d]);
      b1 = begin;
      e1 = end;
    }
    int j10 = 96 * d + l1;
    int j11 = j10 >> 2;
    int action = CASEID[(j10 & 3) + CASEID[(j11 & 7) + CASEID[j11 >> 3]]];
    return action >> 1;
  }

  int match(int tokenSetId)
  {
    bool nonascii = false;
    begin = end;
    int current = end;
    int result = INITIAL[tokenSetId];
    int state = 0;

    for (int code = result & 511; code != 0; )
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
        nonascii = true;
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
          int c1 = c0 >> 4;
          charclass = MAP1[(c0 & 15) + MAP1[(c1 & 31) + MAP1[c1 >> 5]]];
        }
        else
        {
          int lo = 0, hi = 5;
          for (int m = 3; ; m = (hi + lo) >> 1)
          {
            if (MAP2[m] > c0) hi = m - 1;
            else if (MAP2[6 + m] < c0) lo = m + 1;
            else {charclass = MAP2[12 + m]; break;}
            if (lo > hi) {charclass = 0; break;}
          }
        }
      }

      state = code;
      int i0 = (charclass << 9) + code - 1;
      code = TRANSITION[(i0 & 15) + TRANSITION[i0 >> 4]];
      if (code > 511)
      {
        result = code;
        code &= 511;
        end = current;
      }
    }

    result >>= 9;
    if (result == 0)
    {
      for (end = current - 1; (input[end] & 0xc0) == 0x80; --end) ;
      return error(begin, end, state, -1, -1);
    }

    if (nonascii)
    {
      for (int i = result >> 7; i > 0; --i)
        for (--end; (input[end] & 0xc0) == 0x80; --end) ;
    }
    else
    {
      end -= result >> 7;
    }

    if (input[begin] == 0) end = begin;
    return (result & 127) - 1;
  }

  static int goTo(int nonterminal, int state)
  {
    int i0 = 48 * state + nonterminal;
    int i1 = i0 >> 2;
    return GOTO[(i0 & 3) + GOTO[(i1 & 3) + GOTO[i1 >> 2]]];
  }

  static void getTokenSet(int tokenSetId, const char **set, int size)
  {
    int s = tokenSetId < 0 ? - tokenSetId : INITIAL[tokenSetId] & 511;
    for (int i = 0; i < 91; i += 32)
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
    int i0 = t * 371 + s - 1;
    int i1 = i0 >> 2;
    return EXPECTED[(i0 & 3) + EXPECTED[(i1 & 3) + EXPECTED[i1 >> 2]]];
  }

  static const int MAP0[];
  static const int MAP1[];
  static const int MAP2[];
  static const int INITIAL[];
  static const int TRANSITION[];
  static const int EXPECTED[];
  static const int CASEID[];
  static const int TOKENSET[];
  static const int GOTO[];
  static const int REDUCTION[];
  static const char *TOKEN[];
  static const char *NONTERMINAL[];
};

const int RExParser::MAP0[] =
{
/*   0 */ 58, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 4, 5, 6,
/*  36 */ 7, 3, 3, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 18, 18, 18, 18, 18, 18, 18, 18, 19, 20, 21, 22, 23, 24, 3,
/*  65 */ 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51,
/*  92 */ 52, 53, 54, 47, 3, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47,
/* 120 */ 48, 49, 50, 55, 4, 56, 3, 3
};

const int RExParser::MAP1[] =
{
/*   0 */ 108, 124, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 156, 181, 181, 181, 181, 181,
/*  22 */ 214, 215, 213, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214,
/*  44 */ 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214,
/*  66 */ 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214,
/*  88 */ 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 247, 261,
/* 110 */ 277, 293, 309, 325, 309, 371, 407, 407, 407, 399, 355, 347, 355, 347, 355, 355, 355, 355, 355, 355, 355, 355,
/* 132 */ 355, 355, 355, 355, 355, 355, 355, 355, 424, 424, 424, 424, 424, 424, 424, 340, 355, 355, 355, 355, 355, 355,
/* 154 */ 355, 355, 385, 407, 407, 408, 406, 407, 407, 355, 355, 355, 355, 355, 355, 355, 355, 355, 355, 355, 355, 355,
/* 176 */ 355, 355, 355, 355, 355, 407, 407, 407, 407, 407, 407, 407, 407, 407, 407, 407, 407, 407, 407, 407, 407, 407,
/* 198 */ 407, 407, 407, 407, 407, 407, 407, 407, 407, 407, 407, 407, 407, 407, 407, 354, 355, 355, 355, 355, 355, 355,
/* 220 */ 355, 355, 355, 355, 355, 355, 355, 355, 355, 355, 355, 355, 355, 355, 355, 355, 355, 355, 355, 355, 355, 355,
/* 242 */ 355, 355, 355, 355, 407, 58, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/* 275 */ 0, 0, 1, 4, 5, 6, 7, 3, 3, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 18, 18, 18, 18, 18, 18, 18, 18, 19, 20,
/* 305 */ 21, 22, 23, 24, 3, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47,
/* 333 */ 48, 49, 50, 51, 52, 53, 54, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 3, 47, 47, 47, 47, 47, 47,
/* 361 */ 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 55, 4, 56, 3, 3, 3, 3, 3,
/* 390 */ 3, 3, 3, 3, 3, 3, 3, 47, 47, 3, 3, 3, 3, 3, 3, 3, 57, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 57, 57,
/* 425 */ 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57
};

const int RExParser::MAP2[] =
{
/*  0 */ 57344, 63744, 64976, 65008, 65536, 983040, 63743, 64975, 65007, 65533, 983039, 1114111, 3, 47, 3, 47, 47, 3
};

const int RExParser::INITIAL[] =
{
/*  0 */ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30,
/* 30 */ 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45
};

const int RExParser::TRANSITION[] =
{
/*    0 */ 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264,
/*   18 */ 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 1888, 1906, 1890, 1922,
/*   36 */ 4873, 1961, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264,
/*   54 */ 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 1982, 2002, 1986, 2264, 2264, 2264, 2264, 2264,
/*   72 */ 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264,
/*   90 */ 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2018, 4873, 1961, 2264, 2264, 2264, 2264, 2264, 2264,
/*  108 */ 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264,
/*  126 */ 2264, 2264, 4122, 1945, 1935, 2018, 4873, 1961, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264,
/*  144 */ 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 5035, 3934,
/*  162 */ 3269, 2053, 4873, 2091, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264,
/*  180 */ 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2118, 2125, 2141, 2018, 4873, 1961,
/*  198 */ 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264,
/*  216 */ 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2942, 2018, 4873, 1961, 2264, 2264, 2264, 2264,
/*  234 */ 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264,
/*  252 */ 2264, 2264, 2264, 2264, 2731, 4004, 3852, 2188, 4873, 2222, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264,
/*  270 */ 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264,
/*  288 */ 2263, 5406, 2253, 2018, 4873, 1961, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264,
/*  306 */ 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 3280, 3290, 2154, 2018,
/*  324 */ 4873, 1961, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264,
/*  342 */ 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 5042, 2018, 4873, 1961, 2264, 2264,
/*  360 */ 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264,
/*  378 */ 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2738, 2018, 4873, 1961, 2264, 2264, 2264, 2264, 2264, 2264,
/*  396 */ 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264,
/*  414 */ 2264, 2264, 2264, 4529, 2281, 2018, 4873, 1961, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264,
/*  432 */ 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264,
/*  450 */ 3821, 2299, 4873, 1961, 2264, 2264, 2264, 2264, 2264, 2333, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264,
/*  468 */ 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2265, 2350, 2384, 4873, 1961,
/*  486 */ 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264,
/*  504 */ 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 5264, 2064, 2018, 4873, 1961, 2264, 2264, 2264, 2264,
/*  522 */ 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264,
/*  540 */ 2264, 2264, 2264, 2264, 2881, 2418, 2454, 2486, 4978, 1961, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264,
/*  558 */ 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264,
/*  576 */ 2466, 2534, 2520, 2486, 4978, 1961, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264,
/*  594 */ 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2550, 2553, 2609, 2018,
/*  612 */ 4873, 1961, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264,
/*  630 */ 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 4806, 2579, 2569, 2018, 4873, 1961, 2264, 2264,
/*  648 */ 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264,
/*  666 */ 2264, 2264, 2264, 2264, 2264, 2264, 2235, 2237, 2264, 2018, 4873, 1961, 2264, 2264, 2264, 2264, 2264, 2264,
/*  684 */ 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264,
/*  702 */ 2264, 2264, 2595, 5094, 2626, 2644, 4873, 1961, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264,
/*  720 */ 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2206, 4739,
/*  738 */ 2682, 5024, 4873, 2699, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264,
/*  756 */ 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 5060, 2368, 2720, 2018, 4873, 1961,
/*  774 */ 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264,
/*  792 */ 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2848, 2754, 2785, 2825, 2841, 4172, 2866, 4308, 2264,
/*  810 */ 2264, 3975, 4405, 2683, 2264, 2264, 2264, 3562, 2396, 2264, 3728, 2264, 4066, 2264, 2264, 2264, 2264, 2264,
/*  828 */ 2264, 2264, 2264, 2264, 2264, 2848, 2901, 2928, 4978, 2969, 2264, 2470, 2264, 4282, 3080, 4072, 2264, 2264,
/*  846 */ 3762, 2264, 2264, 2264, 3533, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264,
/*  864 */ 2264, 2848, 2985, 2299, 2704, 2841, 2264, 3019, 2264, 2264, 3572, 2264, 2264, 2264, 3038, 3604, 2264, 2264,
/*  882 */ 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2848, 3067, 2299,
/*  900 */ 4978, 2841, 2264, 3101, 2264, 2264, 2264, 2264, 2264, 3881, 2264, 2264, 2264, 2264, 4034, 2264, 2264, 2264,
/*  918 */ 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2848, 3118, 2299, 2912, 2841, 2264, 4201,
/*  936 */ 4593, 3147, 2953, 4954, 2199, 3181, 3325, 3238, 5384, 2264, 3254, 4646, 3312, 3341, 3360, 3376, 2264, 2264,
/*  954 */ 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2848, 3395, 3429, 2809, 2841, 2264, 3296, 2264, 3051, 3445, 2264,
/*  972 */ 2264, 2264, 3956, 2264, 3465, 2264, 2264, 4547, 3482, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264,
/*  990 */ 2264, 2264, 2264, 2848, 3498, 2299, 4873, 2841, 2264, 3532, 2264, 2264, 2850, 2264, 2264, 2264, 3102, 3408,
/* 1008 */ 2361, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2848,
/* 1026 */ 3549, 2299, 4873, 2841, 3216, 2264, 2264, 2628, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264,
/* 1044 */ 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2848, 2901, 2299, 2102, 2841,
/* 1062 */ 2264, 2264, 2998, 3596, 4677, 2264, 3580, 3222, 3620, 4906, 2264, 3466, 4690, 3654, 3720, 3678, 3694, 2264,
/* 1080 */ 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2848, 3744, 2299, 4873, 2841, 2264, 2264, 2264, 2264,
/* 1098 */ 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264,
/* 1116 */ 2264, 2264, 2264, 2264, 2264, 2848, 2901, 2299, 4873, 2841, 2264, 3344, 2264, 4038, 2264, 2264, 2264, 2264,
/* 1134 */ 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264,
/* 1152 */ 2264, 2848, 3778, 3837, 4873, 2841, 2172, 3897, 3921, 4486, 3950, 2264, 3131, 2264, 2264, 2310, 2264, 2264,
/* 1170 */ 4538, 2264, 3972, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2848, 3991, 4020,
/* 1188 */ 3085, 2841, 4101, 4054, 3379, 4372, 2264, 3863, 5238, 2264, 2165, 2264, 3662, 2264, 4141, 2264, 2264, 2264,
/* 1206 */ 4438, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2848, 4088, 2299, 4873, 2841, 2283, 4121,
/* 1224 */ 2264, 2264, 2610, 2264, 5009, 4138, 2264, 4157, 3873, 5133, 2264, 2264, 2497, 4457, 4781, 2264, 2264, 2264,
/* 1242 */ 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2848, 4188, 4217, 4267, 2841, 2264, 2264, 2402, 2264, 2264, 2264,
/* 1260 */ 4960, 4301, 2264, 2264, 4375, 2264, 2264, 2264, 2264, 3757, 3905, 2264, 2264, 2264, 2264, 2264, 2264, 2264,
/* 1278 */ 2264, 2264, 2264, 2848, 4324, 4357, 4873, 4391, 4433, 2334, 4763, 4517, 2264, 3449, 2264, 5113, 2264, 3165,
/* 1296 */ 2264, 4454, 2264, 4417, 4902, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2848,
/* 1314 */ 2901, 2299, 4285, 2841, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264,
/* 1332 */ 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2848, 4473, 2299, 4502, 2841,
/* 1350 */ 5349, 2504, 4337, 3205, 2264, 4837, 2264, 5291, 4563, 2264, 4582, 4609, 5244, 5357, 2264, 2264, 2264, 2264,
/* 1368 */ 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2848, 4633, 4662, 3022, 2841, 4713, 4738, 3813, 2264,
/* 1386 */ 2264, 4755, 4779, 3194, 5318, 2264, 4797, 4822, 2264, 3707, 2264, 4244, 2655, 4871, 2264, 2264, 2264, 2264,
/* 1404 */ 2264, 2264, 2264, 2264, 2264, 2848, 4889, 2299, 3413, 2841, 2264, 4922, 4232, 2264, 2438, 2264, 4105, 2264,
/* 1422 */ 4722, 3638, 4341, 4943, 4617, 4976, 4855, 2800, 2029, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264,
/* 1440 */ 2264, 2848, 2901, 2299, 4994, 2841, 2264, 2264, 5058, 2264, 2264, 2264, 3157, 2037, 2264, 2264, 2264, 2264,
/* 1458 */ 5076, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2848, 2901, 2299,
/* 1476 */ 4873, 2841, 2885, 2264, 2264, 2264, 2264, 2264, 2264, 3630, 2264, 2264, 2264, 2264, 5110, 2264, 2264, 2264,
/* 1494 */ 4846, 5129, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2848, 2901, 2299, 4873, 2841, 2264, 2264,
/* 1512 */ 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264,
/* 1530 */ 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2848, 5149, 2299, 4873, 2841, 3003, 5088, 2264, 2264, 2264, 2264,
/* 1548 */ 5165, 2264, 2264, 5185, 2264, 2264, 2264, 2264, 2264, 5211, 2433, 2264, 2264, 2264, 2264, 2264, 2264, 2264,
/* 1566 */ 2264, 2264, 2264, 2848, 2901, 2299, 2317, 2841, 2264, 2264, 2264, 4251, 2264, 2264, 2264, 2264, 2264, 5191,
/* 1584 */ 2264, 4566, 5169, 2264, 4927, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2848,
/* 1602 */ 2901, 2299, 4873, 2841, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 3511, 2264, 2264, 5324,
/* 1620 */ 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 5207, 2666, 5227, 2018, 4873, 1961,
/* 1638 */ 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264,
/* 1656 */ 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 3516, 2264, 5260, 2018, 4873, 1961, 2264, 2264, 2264, 2264,
/* 1674 */ 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264,
/* 1692 */ 2264, 2264, 2264, 2264, 2264, 2075, 5280, 2018, 4873, 1961, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264,
/* 1710 */ 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264,
/* 1728 */ 2264, 2264, 2264, 5307, 4873, 5340, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264,
/* 1746 */ 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2767, 2769, 4697, 2018,
/* 1764 */ 4873, 1961, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264,
/* 1782 */ 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 1966, 3804, 2264, 5373, 4873, 5400, 2264, 2264,
/* 1800 */ 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264,
/* 1818 */ 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2299, 4873, 1961, 2264, 2264, 2264, 2264, 2264, 2264,
/* 1836 */ 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264,
/* 1854 */ 2264, 2264, 2264, 2264, 3791, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264,
/* 1872 */ 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 2264, 0, 0, 1070,
/* 1891 */ 1070, 1070, 1070, 1070, 1070, 1070, 1070, 1070, 1070, 1070, 1070, 1070, 1070, 1103, 0, 1070, 1070, 1070,
/* 1909 */ 1070, 1070, 1070, 1070, 1070, 1070, 0, 1070, 1070, 1070, 1070, 1070, 1070, 0, 81, 82, 83, 85, 54, 55, 0, 0,
/* 1931 */ 90, 92, 0, 1103, 0, 0, 0, 0, 0, 38400, 38400, 38400, 38400, 38400, 38400, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/* 1957 */ 38400, 0, 0, 0, 81, 82, 83, 0, 85, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 46592, 0, 0, 0, 0, 0, 1024, 1024,
/* 1986 */ 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 4608, 0, 0, 0, 1024, 1024, 1024,
/* 2005 */ 1024, 1024, 1024, 1024, 1024, 1024, 0, 1024, 1024, 1024, 1024, 1024, 1024, 0, 81, 82, 83, 85, 54, 55, 0, 0,
/* 2027 */ 90, 92, 0, 0, 0, 0, 0, 0, 0, 365, 0, 0, 0, 0, 0, 0, 0, 0, 254, 0, 0, 0, 0, 0, 0, 0, 0, 81, 82, 84, 85, 4183,
/* 2059 */ 55, 0, 0, 91, 92, 0, 0, 0, 0, 0, 0, 0, 42496, 42496, 42496, 42496, 0, 0, 0, 0, 0, 0, 0, 45568, 0, 45568, 0,
/* 2086 */ 0, 0, 0, 45568, 0, 81, 82, 3668, 83, 85, 0, 54, 0, 0, 3072, 90, 0, 0, 0, 0, 0, 0, 111, 0, 0, 0, 0, 0, 0, 0,
/* 2116 */ 1103, 0, 0, 0, 1071, 1071, 1071, 1071, 1071, 1071, 1071, 1071, 1071, 1071, 1071, 1071, 1071, 1071, 0, 1071,
/* 2136 */ 1071, 1071, 1071, 1071, 1071, 1071, 1071, 1085, 1071, 1085, 1071, 1071, 1071, 1071, 1071, 1071, 1071, 70191,
/* 2154 */ 0, 0, 0, 0, 0, 39936, 0, 0, 39936, 39936, 39936, 0, 0, 0, 0, 0, 0, 266, 0, 0, 0, 0, 0, 0, 0, 0, 0, 141, 0, 0,
/* 2184 */ 0, 0, 0, 0, 0, 81, 82, 83, 86, 54, 4184, 0, 0, 90, 93, 0, 0, 0, 0, 0, 0, 238, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/* 2216 */ 43520, 0, 0, 0, 0, 0, 81, 82, 83, 0, 3670, 85, 0, 55, 0, 0, 0, 3072, 92, 0, 0, 0, 0, 50, 0, 0, 0, 0, 0, 0, 0,
/* 2247 */ 0, 0, 0, 0, 0, 0, 39424, 0, 39424, 39424, 39424, 39424, 39424, 39424, 39424, 39424, 39424, 0, 0, 0, 0, 0, 0,
/* 2270 */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 60, 0, 7168, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 146, 0, 0, 81, 82, 83,
/* 2303 */ 85, 54, 55, 0, 2105, 90, 92, 0, 0, 0, 0, 0, 0, 276, 0, 0, 0, 0, 0, 0, 0, 0, 0, 117, 0, 124, 128, 0, 1103, 0,
/* 2333 */ 219, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 170, 0, 60, 7680, 7680, 7680, 7680, 7680, 7680, 7680, 7680,
/* 2360 */ 7680, 0, 0, 0, 0, 0, 0, 291, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 44032, 44032, 0, 0, 0, 0, 0, 81, 82, 83, 85, 54,
/* 2390 */ 55, 0, 2105, 90, 92, 41984, 0, 0, 0, 0, 0, 314, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 181, 0, 0, 0, 0, 0, 0, 38960,
/* 2420 */ 38960, 38960, 38960, 0, 0, 0, 0, 38960, 0, 0, 0, 38960, 38960, 0, 0, 0, 31744, 32256, 0, 0, 0, 0, 0, 0, 0, 0,
/* 2446 */ 0, 0, 0, 37888, 0, 0, 0, 0, 0, 0, 38960, 38960, 38960, 38960, 38960, 38960, 38960, 38960, 38960, 0, 0, 0, 0,
/* 2469 */ 38961, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 166, 0, 0, 0, 38961, 81, 82, 83, 85, 54, 55, 0, 2105, 90, 92, 0,
/* 2498 */ 0, 0, 0, 0, 0, 343, 0, 0, 0, 0, 0, 0, 0, 0, 0, 163, 0, 0, 0, 0, 0, 0, 0, 0, 38961, 38961, 38961, 38961,
/* 2526 */ 38961, 38961, 38961, 38961, 38961, 0, 0, 0, 0, 38961, 38961, 38961, 38961, 0, 0, 0, 0, 38961, 0, 0, 0, 38961,
/* 2548 */ 38961, 0, 0, 0, 1536, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1536, 1536, 0, 0, 0, 0, 0, 43008, 0, 0, 0, 0, 43008,
/* 2576 */ 43008, 43008, 43008, 43008, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 43008, 43008, 0, 0, 0, 0, 0, 1536, 0, 0, 0, 0, 0,
/* 2603 */ 0, 56, 0, 0, 0, 1536, 1536, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 218, 1536, 56, 0, 0, 0, 0, 0, 0, 0,
/* 2635 */ 0, 0, 0, 0, 0, 0, 0, 203, 0, 0, 81, 82, 83, 85, 54, 55, 8192, 0, 90, 92, 0, 0, 0, 0, 0, 0, 8704, 0, 0, 0,
/* 2665 */ 20992, 0, 0, 0, 0, 0, 0, 44544, 0, 0, 44544, 0, 0, 0, 44544, 0, 0, 43520, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/* 2695 */ 0, 0, 0, 259, 2560, 82, 83, 0, 85, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 119, 0, 0, 1103, 38992, 44032, 0, 0, 0,
/* 2724 */ 0, 0, 0, 0, 0, 0, 44032, 0, 0, 0, 0, 0, 53, 55, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 40960, 0, 0, 0, 0, 0, 0, 0,
/* 2756 */ 2105, 2105, 2105, 2105, 2105, 2105, 2105, 2105, 2105, 62, 62, 0, 0, 0, 0, 51, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/* 2782 */ 0, 0, 0, 0, 81, 82, 83, 85, 54, 55, 0, 2105, 90, 92, 0, 0, 0, 98, 0, 0, 0, 36864, 0, 0, 0, 353, 354, 0, 0, 0,
/* 2812 */ 0, 0, 0, 0, 112, 0, 0, 0, 0, 0, 0, 1103, 38992, 0, 105, 0, 108, 109, 0, 0, 0, 0, 115, 0, 0, 125, 0, 1103,
/* 2840 */ 38992, 81, 82, 83, 0, 85, 0, 0, 0, 2105, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 217, 0, 147, 0, 0, 0, 0,
/* 2871 */ 0, 160, 0, 162, 0, 0, 0, 0, 0, 168, 0, 0, 0, 38960, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 144, 0, 0, 0, 0, 0,
/* 2903 */ 2105, 2105, 2105, 2105, 2105, 2105, 2105, 2105, 2105, 0, 0, 0, 0, 0, 110, 0, 0, 0, 0, 118, 120, 0, 0, 1103,
/* 2927 */ 38992, 0, 81, 82, 83, 85, 54, 55, 0, 2105, 90, 92, 0, 0, 95, 0, 0, 0, 6656, 0, 6656, 6656, 6656, 6656, 6656,
/* 2952 */ 6656, 0, 0, 0, 0, 0, 0, 211, 0, 36352, 213, 214, 0, 0, 216, 0, 0, 81, 82, 83, 0, 85, 0, 0, 0, 2105, 0, 0, 0,
/* 2981 */ 0, 0, 132, 133, 0, 0, 2105, 2105, 2105, 2105, 2105, 2105, 2105, 2105, 2105, 10303, 10303, 0, 0, 0, 0, 175, 0,
/* 3004 */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 143, 0, 145, 0, 0, 148, 0, 157, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 130,
/* 3036 */ 1103, 0, 260, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 271, 0, 0, 0, 0, 191, 0, 0, 0, 196, 0, 0, 0, 0, 202, 0, 0, 0,
/* 3068 */ 0, 2105, 2105, 2105, 2105, 2105, 2105, 2105, 2105, 2105, 64, 64, 0, 0, 0, 0, 209, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/* 3094 */ 0, 0, 121, 0, 0, 1103, 0, 149, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 272, 0, 0, 2105, 2105, 2105,
/* 3123 */ 2105, 2105, 2105, 2105, 2105, 2105, 65, 65, 0, 0, 0, 0, 235, 0, 0, 0, 0, 0, 0, 0, 0, 244, 0, 0, 185, 0, 0, 0,
/* 3151 */ 0, 0, 193, 0, 0, 197, 0, 0, 0, 0, 0, 0, 0, 239, 0, 0, 0, 0, 0, 0, 0, 0, 278, 0, 0, 0, 0, 0, 0, 0, 0, 248, 0,
/* 3184 */ 35840, 0, 0, 0, 0, 0, 0, 0, 0, 258, 0, 0, 0, 0, 250, 0, 0, 0, 0, 0, 256, 0, 0, 0, 0, 0, 192, 0, 0, 0, 0, 199,
/* 3216 */ 0, 0, 0, 0, 0, 138, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 255, 257, 0, 0, 0, 0, 0, 0, 273, 274, 0, 0, 0, 0, 0, 0, 0,
/* 3249 */ 0, 0, 0, 0, 285, 19456, 0, 0, 0, 0, 0, 0, 316, 0, 0, 0, 0, 0, 0, 322, 0, 0, 58, 52, 58, 52, 52, 52, 52, 52,
/* 3279 */ 52, 0, 0, 0, 0, 0, 0, 0, 39936, 0, 0, 0, 0, 0, 0, 0, 39936, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 164, 0, 0, 0, 0, 0,
/* 3312 */ 34304, 0, 0, 0, 0, 342, 0, 0, 0, 0, 0, 0, 24576, 0, 0, 0, 0, 264, 0, 0, 267, 0, 0, 0, 0, 0, 27136, 0, 0,
/* 3341 */ 32768, 0, 350, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 167, 0, 0, 0, 0, 363, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/* 3373 */ 11264, 0, 35328, 0, 0, 10752, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 183, 0, 0, 0, 0, 2105, 2105, 2105, 2105,
/* 3401 */ 2105, 2105, 2105, 2105, 2105, 66, 66, 0, 0, 0, 0, 275, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 122, 0, 0, 1103, 0,
/* 3429 */ 0, 81, 82, 83, 85, 54, 55, 0, 2105, 90, 92, 0, 0, 0, 0, 103, 205, 0, 0, 208, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/* 3460 */ 0, 229, 0, 0, 0, 286, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 310, 0, 338, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/* 3494 */ 0, 0, 347, 348, 0, 0, 2105, 2105, 2105, 2105, 2105, 2105, 2105, 2105, 2105, 67, 67, 0, 0, 0, 0, 289, 0, 0, 0,
/* 3519 */ 0, 0, 0, 0, 0, 0, 0, 0, 45056, 0, 0, 0, 0, 150, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 323, 0, 0, 2105,
/* 3552 */ 2105, 2105, 2105, 2105, 2105, 2105, 2105, 2105, 68, 68, 0, 0, 0, 0, 302, 0, 304, 0, 0, 306, 0, 0, 0, 0, 0, 0,
/* 3578 */ 0, 212, 0, 0, 0, 0, 0, 0, 0, 0, 0, 241, 0, 0, 0, 0, 0, 246, 0, 186, 0, 0, 0, 0, 194, 195, 0, 0, 0, 0, 0, 0,
/* 3610 */ 0, 0, 0, 280, 0, 0, 0, 0, 0, 0, 0, 261, 0, 263, 0, 0, 0, 0, 0, 268, 0, 0, 0, 0, 0, 0, 0, 253, 0, 0, 0, 0, 0,
/* 3643 */ 0, 0, 0, 279, 0, 0, 0, 0, 0, 0, 0, 324, 0, 326, 0, 0, 0, 330, 331, 0, 0, 0, 0, 0, 0, 0, 0, 0, 294, 0, 295, 0,
/* 3675 */ 0, 0, 0, 0, 349, 0, 0, 0, 0, 0, 0, 0, 355, 356, 357, 0, 0, 0, 360, 361, 362, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/* 3706 */ 369, 0, 0, 0, 0, 328, 0, 0, 0, 0, 0, 0, 334, 26112, 0, 0, 0, 0, 341, 0, 0, 344, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/* 3737 */ 345, 0, 0, 0, 0, 0, 0, 0, 0, 2105, 2105, 2105, 2105, 2105, 2105, 2105, 2105, 2105, 69, 69, 0, 0, 0, 0, 351,
/* 3762 */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 270, 0, 0, 0, 0, 0, 0, 2105, 2105, 2105, 2105, 2105, 2105, 2105, 2105, 2105,
/* 3789 */ 70, 70, 0, 0, 0, 0, 5120, 0, 0, 0, 0, 0, 0, 0, 70144, 0, 0, 0, 0, 46592, 0, 0, 0, 46592, 0, 0, 0, 0, 0, 0, 0,
/* 3820 */ 178, 0, 0, 0, 0, 0, 0, 0, 0, 0, 41472, 41472, 0, 0, 0, 0, 0, 0, 81, 82, 83, 85, 54, 55, 0, 2105, 90, 92, 0,
/* 3849 */ 0, 0, 99, 0, 0, 59, 53, 59, 53, 53, 53, 53, 53, 53, 0, 0, 0, 0, 0, 0, 224, 0, 0, 226, 0, 0, 0, 0, 0, 0, 0,
/* 3880 */ 292, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9728, 0, 0, 0, 0, 0, 0, 151, 0, 0, 0, 0, 0, 0, 161, 0, 0, 0, 0, 0, 0, 0, 0,
/* 3913 */ 0, 367, 0, 0, 0, 0, 0, 0, 0, 172, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15872, 0, 0, 0, 58, 0, 0, 0, 0, 0, 0, 0, 0,
/* 3946 */ 0, 58, 58, 0, 0, 206, 0, 0, 0, 210, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 269, 0, 0, 0, 0, 0, 0, 0, 339, 0, 0, 0, 0,
/* 3979 */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 230, 22528, 231, 0, 0, 2105, 2105, 2105, 2105, 2105, 2105, 2105, 2105, 2105, 71,
/* 4003 */ 71, 0, 0, 0, 59, 0, 0, 0, 0, 0, 0, 0, 0, 0, 59, 59, 0, 0, 81, 82, 83, 85, 54, 55, 0, 2105, 90, 92, 0, 0, 96,
/* 4034 */ 0, 0, 0, 21504, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 201, 0, 0, 0, 152, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 165, 0,
/* 4067 */ 0, 0, 0, 0, 364, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 227, 228, 0, 0, 0, 0, 0, 0, 2105, 2105, 2105, 2105, 2105,
/* 4095 */ 2105, 2105, 2105, 2105, 72, 72, 0, 0, 0, 137, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 243, 0, 0, 0, 153, 0, 0, 0,
/* 4125 */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 38400, 0, 0, 249, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 321, 0, 0, 0,
/* 4158 */ 29184, 0, 0, 0, 0, 0, 277, 0, 0, 0, 5913, 0, 0, 284, 0, 0, 136, 0, 0, 0, 14336, 0, 0, 0, 142, 0, 0, 0, 0,
/* 4187 */ 19968, 0, 0, 2105, 2105, 2105, 2105, 2105, 2105, 2105, 2105, 2105, 73, 73, 0, 0, 0, 158, 0, 0, 0, 0, 0, 0, 0,
/* 4212 */ 0, 0, 0, 169, 0, 0, 81, 82, 83, 85, 54, 55, 0, 2105, 90, 92, 0, 94, 0, 100, 0, 0, 173, 0, 0, 0, 0, 0, 0, 0,
/* 4242 */ 0, 182, 0, 0, 0, 0, 0, 9216, 352, 0, 0, 0, 0, 0, 0, 0, 0, 0, 198, 0, 0, 0, 0, 0, 0, 0, 0, 16384, 0, 0, 0, 0,
/* 4274 */ 113, 0, 0, 0, 0, 126, 0, 1103, 0, 0, 187, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 129, 1103, 0, 247, 0, 0, 0,
/* 4305 */ 0, 0, 252, 0, 0, 0, 0, 0, 0, 0, 0, 0, 180, 0, 0, 0, 0, 0, 18104, 0, 0, 2105, 2105, 2105, 2105, 2105, 2105,
/* 4332 */ 2105, 2105, 2105, 74, 74, 0, 0, 0, 174, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 296, 0, 0, 0, 0, 81, 82, 83, 85,
/* 4362 */ 54, 55, 0, 2105, 90, 92, 0, 0, 97, 101, 0, 0, 188, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 297, 0, 0, 81, 82,
/* 4393 */ 83, 0, 85, 0, 0, 0, 2105, 0, 0, 0, 0, 131, 0, 0, 0, 25088, 0, 0, 237, 0, 240, 0, 0, 30208, 0, 0, 0, 0, 0,
/* 4422 */ 329, 0, 0, 0, 0, 0, 0, 0, 0, 0, 337, 134, 0, 0, 0, 13312, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 368, 0, 0, 0, 0,
/* 4454 */ 0, 0, 299, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 358, 359, 0, 0, 0, 2105, 2105, 2105, 2105, 2105, 2105,
/* 4481 */ 2105, 2105, 2105, 75, 75, 0, 0, 0, 190, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 204, 104, 0, 107, 0, 0, 0, 0, 0, 0,
/* 4511 */ 116, 0, 0, 127, 0, 1103, 0, 0, 189, 0, 0, 0, 0, 0, 0, 0, 0, 200, 0, 0, 0, 0, 0, 7168, 7168, 7168, 7168, 0, 0,
/* 4540 */ 0, 0, 0, 0, 0, 0, 317, 0, 0, 0, 0, 0, 0, 0, 0, 332, 0, 0, 0, 0, 0, 336, 0, 0, 0, 262, 0, 0, 0, 0, 0, 0, 0, 0,
/* 4574 */ 0, 0, 0, 0, 0, 12288, 0, 0, 0, 0, 16896, 288, 0, 0, 0, 0, 0, 0, 23552, 0, 0, 0, 0, 0, 176, 177, 0, 0, 0, 0,
/* 4604 */ 0, 0, 0, 17408, 0, 0, 31232, 0, 0, 0, 303, 0, 305, 0, 0, 0, 0, 0, 0, 0, 0, 0, 30720, 0, 0, 0, 0, 0, 0, 0, 0,
/* 4635 */ 2105, 2105, 2105, 2105, 2105, 2105, 2105, 2105, 2105, 76, 76, 0, 0, 0, 327, 0, 0, 0, 0, 0, 0, 0, 0, 0, 335,
/* 4660 */ 0, 0, 0, 81, 82, 83, 85, 54, 55, 0, 2105, 90, 92, 0, 0, 0, 102, 0, 0, 207, 0, 0, 0, 0, 0, 0, 0, 0, 0, 215, 0,
/* 4691 */ 0, 0, 0, 313, 0, 315, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 46080, 0, 0, 0, 0, 0, 0, 135, 0, 0, 0, 0, 0, 0, 140, 0,
/* 4723 */ 0, 0, 0, 0, 0, 0, 0, 24064, 0, 0, 0, 0, 0, 27648, 0, 154, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 43520,
/* 4755 */ 0, 11996, 0, 0, 0, 0, 0, 225, 0, 0, 0, 0, 0, 0, 0, 0, 179, 0, 0, 0, 0, 0, 0, 0, 0, 233, 0, 0, 0, 0, 0, 0, 0,
/* 4788 */ 0, 0, 0, 0, 0, 0, 0, 370, 0, 0, 287, 0, 0, 0, 0, 0, 0, 293, 0, 0, 0, 0, 0, 0, 0, 0, 43008, 0, 0, 0, 0, 43008,
/* 4820 */ 0, 0, 298, 0, 300, 33792, 0, 0, 0, 0, 6144, 0, 0, 308, 0, 0, 12800, 0, 0, 221, 222, 14848, 0, 0, 0, 18944, 0,
/* 4847 */ 0, 0, 0, 0, 0, 0, 0, 366, 0, 0, 0, 0, 0, 0, 0, 0, 18432, 0, 346, 0, 0, 25600, 0, 0, 0, 20480, 0, 0, 0, 0, 0,
/* 4878 */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 1103, 0, 0, 0, 2105, 2105, 2105, 2105, 2105, 2105, 2105, 2105, 2105, 77, 77, 0, 0,
/* 4904 */ 0, 340, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 282, 283, 0, 0, 155, 156, 0, 0, 159, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/* 4936 */ 0, 0, 22016, 0, 0, 0, 0, 0, 0, 301, 0, 0, 0, 0, 0, 0, 0, 307, 0, 0, 0, 0, 0, 223, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/* 4969 */ 0, 242, 0, 0, 0, 0, 0, 0, 325, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1103, 38992, 0, 106, 0, 0, 0, 0, 0,
/* 5001 */ 0, 114, 0, 0, 123, 0, 0, 1103, 0, 0, 234, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 245, 0, 0, 82, 83, 85, 54, 55, 0,
/* 5032 */ 0, 90, 92, 0, 0, 0, 0, 0, 52, 54, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 40448, 0, 0, 0, 0, 0, 171, 0, 0, 0, 0, 0, 0,
/* 5065 */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 44032, 0, 0, 0, 312, 0, 0, 0, 0, 0, 0, 0, 0, 319, 0, 0, 0, 0, 0, 29696, 0, 0, 0,
/* 5097 */ 0, 0, 0, 0, 0, 0, 0, 1536, 1536, 0, 0, 0, 56, 0, 311, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13824, 0, 0,
/* 5129 */ 371, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 309, 0, 0, 0, 0, 0, 2105, 2105, 2105, 2105, 2105, 2105,
/* 5157 */ 2105, 2105, 2105, 78, 78, 0, 0, 80, 232, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 320, 0, 0, 0, 28672, 0,
/* 5187 */ 0, 0, 0, 33280, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 37376, 0, 0, 0, 0, 0, 0, 44544, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/* 5219 */ 0, 0, 0, 0, 34816, 0, 0, 0, 0, 44544, 44544, 44544, 44544, 44544, 44544, 44544, 44544, 44544, 44544, 0, 0, 0,
/* 5241 */ 0, 0, 236, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 318, 0, 0, 0, 0, 0, 45056, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/* 5275 */ 0, 42496, 0, 0, 0, 0, 45568, 0, 45568, 0, 45568, 45568, 45568, 45568, 45568, 45568, 0, 0, 0, 0, 0, 251, 0, 0,
/* 5299 */ 0, 0, 0, 0, 0, 0, 15360, 0, 0, 81, 82, 83, 85, 54, 55, 0, 2137, 90, 92, 0, 0, 0, 0, 0, 265, 0, 0, 0, 0, 0, 0,
/* 5330 */ 0, 0, 0, 0, 333, 0, 0, 0, 0, 0, 81, 82, 83, 0, 85, 0, 0, 0, 2137, 0, 0, 0, 0, 0, 0, 0, 139, 0, 0, 0, 0, 0, 0,
/* 5363 */ 0, 0, 0, 23040, 0, 0, 0, 0, 0, 0, 0, 81, 0, 83, 85, 54, 55, 0, 0, 90, 92, 0, 0, 0, 0, 0, 290, 0, 0, 0, 0, 0,
/* 5395 */ 0, 0, 0, 26624, 28160, 81, 2560, 83, 0, 85, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 39424, 0, 0, 0, 0, 0
};

const int RExParser::EXPECTED[] =
{
/*   0 */ 70, 74, 78, 82, 86, 90, 94, 147, 104, 147, 148, 108, 147, 243, 147, 200, 114, 121, 147, 119, 221, 214, 125,
/*  23 */ 129, 147, 130, 147, 100, 147, 115, 134, 147, 138, 145, 194, 142, 146, 152, 156, 207, 162, 168, 158, 172, 176,
/*  45 */ 236, 180, 184, 188, 192, 198, 204, 147, 147, 211, 147, 110, 218, 147, 97, 147, 164, 227, 223, 147, 240, 230,
/*  67 */ 233, 247, 251, 550, 254, 264, 257, 260, 271, 274, 267, 277, 281, 282, 286, 535, 310, 349, 301, 322, 470, 470,
/*  89 */ 542, 536, 309, 528, 314, 331, 319, 468, 470, 295, 561, 470, 325, 373, 383, 490, 330, 336, 469, 332, 338, 470,
/* 111 */ 470, 295, 554, 359, 470, 470, 470, 325, 363, 367, 470, 470, 353, 358, 367, 289, 367, 366, 292, 470, 470, 470,
/* 133 */ 340, 394, 435, 319, 442, 326, 398, 406, 410, 400, 424, 417, 430, 441, 470, 470, 470, 470, 315, 472, 562, 421,
/* 155 */ 453, 434, 439, 470, 470, 457, 452, 448, 441, 470, 470, 471, 297, 526, 563, 452, 304, 305, 470, 443, 458, 462,
/* 177 */ 470, 485, 467, 487, 557, 483, 494, 501, 376, 379, 413, 505, 509, 513, 517, 521, 532, 470, 470, 473, 562, 540,
/* 199 */ 470, 470, 470, 489, 354, 497, 483, 470, 470, 347, 563, 402, 296, 546, 470, 470, 354, 470, 289, 548, 470, 470,
/* 221 */ 470, 354, 470, 470, 386, 390, 478, 470, 470, 470, 369, 390, 470, 443, 390, 470, 466, 470, 477, 368, 389, 470,
/* 243 */ 470, 490, 427, 344, 444, 470, 479, 470, 524, 524, 340, 18, 66, 130, 2, 6, 6, 2, 10, 18, 34, 2, 32770, 2, 2,
/* 268 */ 34, 34, 32770, 2, 8194, 8194, 8194, 0, 6, 6, 40962, 19498, 20554, 20010, 20554, 20554, 20554, -65534, -65278,
/* 287 */ 2, 2, 0, 0, 65536, 1048576, 0, 1048576, 0, 1, 2, 4, 24, 128, 3074, 458752, 133169152, 134217728, 536870912,
/* 306 */ 1073741824, (int) 0x80000000, 0, 64, 64, 128, 128, 32768, 32, 3072, 65536, 131072, 262144, 33554432, 67108864,
/* 321 */ 134217728, 268435456, 1610612736, (int) 0x80000000, 0, 1, 2, 12, 16, 131072, 262144, 3145728, 12582912,
/* 334 */ 16777216, 67108864, 16777216, 67108864, 268435456, 536870912, 0, 0, -1, -1, 16777216, 67108864, 536870912, 0,
/* 348 */ 1, 8, 32, 32, 0, 2048, 65536, 131072, 1048576, 2097152, 2097152, 8388608, 16777216, 0, 0, 0, 65536, 131072,
/* 366 */ 1048576, 2097152, 0, 0, 0, 4, 8, 16, 32, 2097088, 2097152, 9216, 525312, 2048, 2048, 67110912, 8192, 29360128,
/* 384 */ 33554432, -67108864, 0, 2, 4, 8, 16, 128, 0, 0, 16, 32, 64, 2097024, 32, 896, 1024, 2048, 4096, 8192, 32768,
/* 405 */ 131072, 4096, 24576, 32768, 65536, 393216, 1572864, 2097152, 4194304, 16777216, 67108864, 20973568, 262144,
/* 418 */ 1572864, 2097152, 4194304, 1024, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 3145728, 8388608, 16777216,
/* 432 */ 67108864, 134217728, 1048576, 2097152, 4194304, 8388608, 16777216, 16777216, 134217728, 268435456, -536870912,
/* 443 */ 0, 0, 0, 8, 16, 262144, 524288, 4194304, 134217728, 4096, 32768, 131072, 262144, 524288, 8, 128, 256, 1024,
/* 461 */ 32768, 131072, 536870912, 1073741824, (int) 0x80000000, 128, 256, 536870912, 1073741824, 0, 0, 0, 0, 1, 8, 16,
/* 477 */ 128, 256, 0, 0, 0, 16, 0, 2048, 0, 0, 0, 128, 0, 0, 0, 3072, 65536, 0, 8192, 524288, 0, 3, 252, 768, 1048576,
/* 502 */ 8388608, 67108864, 524288, 2101248, 2621440, 787456, 4196352, 16779264, 1179648, 11538432, 21626880, 4200448,
/* 514 */ 20977664, 4200448, 20986880, 21502976, 21765120, 21773312, 21838848, 57539584, 1023, 1023, 0, 16, 0, 0, 8, 32,
/* 530 */ 32, 32, 0, 2048, 2048, 0, 16, 16, 64, 64, 0, 131072, 0, 0, 2, 0, 96, 128, 256, 512, 0, 0, 6, 2, 24, 32, 64,
/* 557 */ 128, 0, 4096, 4194304, 24, 32, 128, 256, 512, 1024
};

const int RExParser::CASEID[] =
{
/*    0 */ 300, 349, 501, 312, 349, 478, 324, 349, 590, 336, 349, 590, 349, 349, 436, 348, 349, 955, 804, 349, 349, 340,
/*   22 */ 357, 365, 376, 349, 368, 837, 349, 535, 386, 349, 304, 396, 349, 740, 868, 349, 484, 521, 357, 365, 408, 349,
/*   44 */ 912, 419, 349, 950, 419, 349, 950, 396, 349, 740, 396, 349, 740, 396, 349, 740, 431, 349, 698, 868, 349, 484,
/*   66 */ 396, 349, 740, 837, 349, 349, 396, 349, 740, 396, 349, 740, 431, 349, 616, 349, 349, 507, 408, 349, 912, 431,
/*   88 */ 349, 698, 448, 349, 570, 431, 349, 822, 349, 349, 754, 868, 349, 596, 868, 349, 472, 396, 349, 726, 431, 349,
/*  110 */ 684, 431, 349, 712, 349, 349, 644, 868, 349, 484, 396, 349, 726, 431, 349, 712, 349, 349, 808, 774, 349, 423,
/*  132 */ 349, 349, 400, 349, 349, 538, 349, 349, 400, 349, 349, 411, 349, 349, 400, 349, 349, 487, 349, 349, 400, 466,
/*  154 */ 349, 458, 453, 349, 440, 349, 349, 808, 495, 349, 316, 759, 349, 349, 515, 349, 349, 529, 349, 349, 546, 349,
/*  176 */ 349, 578, 349, 349, 604, 349, 349, 624, 349, 349, 638, 349, 349, 652, 349, 349, 678, 349, 349, 692, 349, 349,
/*  198 */ 706, 349, 349, 720, 349, 349, 734, 349, 349, 748, 349, 349, 764, 349, 769, 349, 349, 769, 816, 349, 328, 349,
/*  220 */ 349, 552, 906, 349, 349, 944, 349, 349, 861, 349, 349, 830, 349, 349, 899, 349, 349, 892, 349, 349, 937, 349,
/*  242 */ 349, 854, 349, 349, 885, 349, 349, 930, 349, 349, 847, 349, 349, 349, 349, 610, 349, 349, 584, 779, 349, 388,
/*  264 */ 349, 349, 558, 349, 349, 658, 878, 349, 630, 923, 349, 670, 349, 349, 784, 349, 349, 564, 349, 349, 789, 349,
/*  286 */ 349, 378, 794, 349, 839, 799, 349, 870, 799, 349, 915, 349, 349, 664, 1065, 1067, 984, 1066, 1069, 1069,
/*  306 */ 1069, 1069, 974, 993, 1069, 1069, 1061, 1063, 1340, 1062, 1069, 1069, 1069, 1069, 974, 1069, 1069, 1069,
/*  324 */ 1097, 963, 969, 981, 1069, 1069, 1069, 1069, 989, 1069, 1069, 1069, 1097, 963, 1361, 981, 1069, 1069, 1069,
/*  343 */ 1069, 999, 1003, 1007, 1011, 1091, 1069, 1069, 1069, 1069, 1069, 1069, 1069, 1069, 1015, 1019, 1023, 1027,
/*  361 */ 1031, 1035, 1039, 1043, 1047, 1051, 1055, 1069, 1069, 1069, 1069, 1069, 993, 1069, 1069, 1088, 1069, 1069,
/*  379 */ 1069, 1069, 1069, 1069, 1069, 1270, 1069, 1082, 1069, 1069, 1069, 1069, 1069, 1069, 1069, 1350, 1069, 1298,
/*  397 */ 1299, 1069, 1079, 1069, 1069, 1069, 1069, 1136, 1069, 1069, 1069, 1278, 1069, 1069, 1069, 1069, 1069, 1069,
/*  415 */ 1069, 1166, 1069, 1069, 1389, 1069, 1069, 1069, 1069, 1069, 1069, 1069, 1157, 1332, 1160, 1069, 1400, 1315,
/*  433 */ 1069, 1106, 1069, 1069, 1069, 1069, 988, 1069, 1069, 1069, 1069, 1059, 1176, 1069, 1069, 1124, 1125, 1069,
/*  451 */ 1121, 1069, 1069, 1069, 1069, 1057, 1069, 1069, 1069, 1069, 1096, 1069, 1172, 1069, 1069, 1094, 1069, 1069,
/*  469 */ 1069, 1069, 1069, 1069, 1069, 995, 1069, 1069, 1245, 1069, 1069, 1061, 1064, 1069, 1062, 1069, 1069, 995,
/*  487 */ 1069, 1069, 1069, 1069, 1069, 1130, 1069, 1069, 1318, 1069, 1069, 1069, 1069, 1069, 1069, 1069, 1065, 1068,
/*  505 */ 1069, 1066, 1069, 1069, 965, 1069, 1069, 1248, 1140, 1069, 1202, 1069, 1069, 1069, 1069, 1069, 1069, 1069,
/*  523 */ 1101, 1069, 999, 1003, 1007, 1011, 1215, 1069, 1069, 1069, 1069, 1069, 1069, 1069, 1102, 1069, 1069, 1069,
/*  541 */ 1069, 1069, 1085, 1069, 1069, 1228, 1069, 1069, 1069, 1069, 1069, 1069, 1069, 1115, 1069, 989, 1069, 1069,
/*  559 */ 1069, 1115, 1069, 1075, 1069, 1069, 1069, 1115, 1069, 1325, 1069, 1069, 1069, 1118, 1123, 1124, 1125, 1123,
/*  577 */ 1069, 1264, 1069, 1069, 1069, 1069, 1069, 1069, 1069, 1153, 1069, 1069, 1069, 1069, 1069, 1177, 973, 1069,
/*  595 */ 978, 1069, 1069, 995, 1069, 1069, 1069, 1145, 1069, 1288, 1069, 1069, 1069, 1069, 1069, 1069, 1069, 1183,
/*  613 */ 1069, 1069, 1069, 1069, 1069, 1218, 1134, 1205, 1377, 1297, 1069, 1309, 1069, 1069, 1069, 1069, 1069, 1069,
/*  631 */ 1069, 1231, 1233, 1355, 1162, 1234, 1069, 1196, 1069, 1069, 1069, 1069, 1069, 1069, 1069, 1235, 1069, 1069,
/*  649 */ 1069, 1291, 1069, 1212, 1069, 1069, 1069, 1069, 1069, 1069, 1069, 1251, 1069, 1254, 1069, 1069, 1069, 1267,
/*  667 */ 1404, 1069, 1069, 1069, 1069, 1273, 1371, 1369, 1365, 1276, 1069, 1225, 1069, 1069, 1069, 1069, 1069, 1069,
/*  685 */ 1069, 1294, 1129, 1146, 1377, 1297, 1069, 1242, 1069, 1069, 1069, 1069, 1069, 1069, 1069, 1294, 1129, 1147,
/*  703 */ 1377, 1297, 1069, 1261, 1069, 1069, 1069, 1069, 1069, 1069, 1069, 1294, 1151, 1069, 1377, 1297, 1069, 1285,
/*  721 */ 1069, 1069, 1069, 1069, 1069, 1069, 1069, 1321, 1323, 1069, 1299, 1324, 1069, 1306, 1069, 1069, 1069, 1069,
/*  739 */ 1069, 1069, 1069, 1321, 1324, 1321, 1299, 1324, 1069, 1109, 1069, 1069, 1069, 1069, 1069, 1069, 1069, 1351,
/*  757 */ 1069, 1069, 1069, 1069, 1069, 1141, 1069, 1069, 1069, 1069, 1181, 1069, 1069, 1069, 1069, 1187, 1069, 1069,
/*  775 */ 1069, 1069, 1333, 1069, 1069, 1069, 1069, 1344, 1069, 1069, 1069, 1069, 1375, 1069, 1069, 1069, 1069, 1381,
/*  793 */ 1069, 1069, 1069, 1069, 1387, 1069, 1069, 1069, 1069, 1393, 1069, 1069, 1069, 1069, 1406, 1069, 1069, 1069,
/*  811 */ 1069, 1070, 1069, 1069, 1069, 1112, 1069, 1069, 1069, 1069, 1069, 1069, 1069, 1376, 1129, 1069, 1377, 1297,
/*  829 */ 1069, 1069, 1346, 1069, 1069, 1069, 1069, 1069, 1069, 1074, 1069, 1069, 1069, 1069, 1069, 1069, 1312, 1069,
/*  847 */ 1069, 1337, 1069, 1069, 1069, 1069, 1069, 1069, 1282, 1069, 1069, 1069, 1069, 1069, 1069, 1222, 1069, 1069,
/*  865 */ 1069, 1069, 1069, 1069, 963, 1069, 1069, 1069, 1069, 1069, 1069, 1399, 1069, 1161, 1162, 1069, 1358, 1069,
/*  883 */ 1069, 1069, 1069, 1303, 1069, 1069, 1069, 1069, 1069, 1069, 1239, 1069, 1069, 1069, 1069, 1069, 1069, 1189,
/*  901 */ 1069, 1069, 1069, 1069, 1069, 1069, 1193, 1069, 1069, 1069, 1069, 1069, 1069, 1383, 1069, 1069, 1069, 1069,
/*  919 */ 1069, 1199, 1069, 1069, 1167, 1168, 1069, 1367, 1069, 1069, 1069, 1069, 1329, 1069, 1069, 1069, 1069, 1069,
/*  937 */ 1069, 1258, 1069, 1069, 1069, 1069, 1069, 1069, 1209, 1069, 1069, 1069, 1069, 1069, 1069, 1395, 1069, 1069,
/*  955 */ 1069, 1069, 1069, 988, 1069, 993, 1069, 1069, 0, 24072, 0, 0, 0, 20488, 0, 552, 25608, 25608, 1540, 0, 0, 0,
/*  977 */ 2084, 0, 0, 56324, 0, 0, 2568, 0, 0, 4, 4, 2322, 0, 0, 0, 2100, 0, 3592, 0, 0, 0, 23560, 43528, 42504, 44552,
/* 1002 */ 51208, 33288, 33800, 16914, 40968, 17170, 50696, 50184, 52232, 17426, 36872, 41480, 49160, 55304, 48136,
/* 1017 */ 47624, 47112, 34824, 39944, 53256, 43016, 41992, 44040, 40456, 51720, 54792, 34312, 55816, 39432, 52744,
/* 1032 */ 38408, 53768, 37384, 35336, 14354, 16658, 14610, 48648, 49672, 46088, 38920, 36360, 15122, 15378, 15890,
/* 1047 */ 14866, 54280, 16402, 15634, 16146, 37896, 35848, 46600, 45576, 45064, 0, 0, 0, 23572, 0, 0, 0, 24580, 0, 0,
/* 1067 */ 0, 4, 0, 0, 0, 0, 1064, 4616, 0, 0, 0, 2116, 5124, 0, 5124, 0, 0, 4626, 0, 0, 3602, 0, 0, 4370, 0, 0, 2834,
/* 1094 */ 0, 0, 2580, 0, 0, 0, 13074, 25128, 0, 0, 0, 4104, 16904, 0, 17928, 0, 0, 5650, 0, 0, 6162, 0, 0, 6418, 0, 0,
/* 1120 */ 6660, 6660, 0, 6660, 0, 0, 0, 6660, 0, 15364, 0, 0, 0, 4114, 15364, 9236, 0, 0, 0, 25112, 8722, 0, 0, 0,
/* 1144 */ 5394, 19992, 0, 0, 0, 9220, 9220, 15364, 9220, 0, 0, 0, 26664, 0, 3090, 0, 22036, 0, 0, 0, 9748, 0, 3858, 0,
/* 1168 */ 0, 0, 12308, 0, 60436, 2580, 0, 61972, 60948, 0, 0, 0, 13330, 0, 5906, 0, 0, 0, 27176, 0, 3112, 0, 0, 0,
/* 1192 */ 30760, 0, 0, 32808, 0, 0, 20498, 0, 0, 18472, 0, 0, 18962, 0, 0, 9236, 9236, 0, 0, 32296, 0, 0, 20754, 0, 0,
/* 1217 */ 19218, 0, 0, 9236, 15876, 0, 0, 31784, 0, 0, 21010, 0, 0, 19474, 0, 0, 9748, 9748, 0, 0, 0, 14856, 0, 0,
/* 1241 */ 30248, 0, 0, 21266, 0, 0, 19480, 0, 0, 8466, 0, 0, 7188, 0, 0, 7698, 7188, 0, 0, 29736, 0, 0, 21522, 0, 0,
/* 1266 */ 19730, 0, 0, 10258, 0, 0, 10296, 0, 0, 12308, 12308, 8210, 0, 0, 0, 58376, 0, 0, 29224, 0, 0, 21778, 0, 0,
/* 1290 */ 19986, 0, 0, 13348, 0, 0, 9220, 15876, 0, 0, 0, 5124, 0, 0, 0, 28712, 0, 0, 22034, 0, 0, 20242, 0, 0, 13844,
/* 1315 */ 0, 0, 17416, 0, 0, 4882, 0, 0, 5124, 5124, 0, 0, 0, 2132, 0, 0, 28200, 0, 0, 22036, 0, 22036, 0, 0, 27688, 0,
/* 1341 */ 0, 24580, 24580, 0, 7186, 0, 0, 0, 31272, 56888, 0, 0, 0, 14344, 7954, 0, 9748, 9748, 0, 9748, 0, 0, 25608,
/* 1364 */ 25608, 0, 10776, 12308, 0, 12308, 0, 12308, 12308, 11800, 11288, 8978, 0, 0, 0, 15876, 0, 0, 3144, 0, 0, 0,
/* 1386 */ 58888, 0, 9746, 0, 0, 0, 60424, 0, 10002, 0, 0, 0, 60936, 18984, 0, 0, 0, 17928, 0, 16440, 0, 0, 0, 62468
};

const int RExParser::TOKENSET[] =
{
/*   0 */ 34, 34, 36, 34, 0, 26, 9, 43, 14, 18, 27, 39, 19, 44, 17, 17, 17, 39, 39, 39, 39, 19, 39, 4, 39, 39, 40, 25,
/*  28 */ 17, 39, 38, 35, 3, 30, 29, 37, 38, 37, 20, 19, 37, 37, 8, 33, 8, 1, 8, 10, 8, 11, 8, 32, 31, 8, 13, 9, 2, 2,
/*  58 */ 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 21, 7, 13, 16, 5, 5, 5, 6, 6, 5, 5, 5, 5, 5, 5, 3, 3, 23, 16, 28, 41, 42,
/*  92 */ 0, 16, 7, 12, 24, 23, 22, 15
};

const int RExParser::GOTO[] =
{
/*   0 */ 126, 127, 132, 138, 134, 127, 143, 148, 152, 156, 161, 152, 165, 127, 127, 171, 127, 127, 127, 127, 128, 127,
/*  22 */ 167, 127, 177, 127, 127, 183, 127, 127, 189, 127, 127, 218, 127, 185, 127, 195, 127, 127, 139, 127, 127, 144,
/*  44 */ 201, 127, 127, 206, 127, 127, 211, 230, 127, 185, 230, 127, 185, 230, 127, 185, 267, 216, 179, 127, 222, 127,
/*  66 */ 236, 127, 185, 228, 127, 127, 236, 127, 185, 127, 127, 254, 207, 216, 179, 127, 234, 127, 127, 202, 201, 242,
/*  88 */ 216, 179, 127, 127, 173, 212, 216, 179, 157, 127, 127, 127, 240, 127, 127, 246, 127, 260, 127, 248, 191, 216,
/* 110 */ 179, 224, 216, 179, 127, 252, 127, 127, 258, 127, 127, 127, 264, 197, 216, 179, 271, 272, 272, 272, 272, 335,
/* 132 */ 272, 273, 272, 272, 277, 272, 302, 272, 272, 272, 361, 288, 272, 272, 272, 378, 272, 282, 299, 286, 292, 296,
/* 154 */ 308, 313, 315, 272, 272, 272, 384, 272, 282, 319, 286, 272, 328, 272, 272, 278, 339, 272, 333, 272, 272, 304,
/* 176 */ 272, 272, 344, 272, 272, 309, 388, 272, 352, 272, 272, 322, 272, 272, 350, 272, 272, 329, 376, 272, 324, 272,
/* 198 */ 272, 340, 376, 366, 272, 272, 272, 389, 398, 272, 272, 272, 402, 423, 272, 272, 272, 434, 382, 272, 272, 272,
/* 220 */ 356, 272, 272, 393, 272, 272, 357, 376, 272, 362, 272, 272, 371, 272, 346, 272, 272, 272, 397, 272, 367, 409,
/* 242 */ 272, 272, 405, 376, 372, 409, 272, 272, 413, 272, 422, 272, 272, 272, 416, 272, 272, 427, 272, 272, 418, 272,
/* 264 */ 272, 272, 431, 272, 272, 437, 376, 6, 0, 0, 0, 0, 137, 393, 0, 0, 0, 1673, 777, 5513, 0, 11268, 0, 5641, 0, 0,
/* 290 */ 5385, 649, 0, 5897, 6025, 29956, 6153, 6281, 6409, 0, 524, 905, 0, 265, 0, 0, 4617, 0, 521, 0, 0, 0, 3465, 0,
/* 314 */ 5769, 0, 0, 6793, 649, 0, 12300, 905, 0, 2569, 0, 0, 11028, 11524, 1033, 0, 0, 0, 3612, 1289, 6921, 0, 0,
/* 337 */ 7049, 0, 13060, 0, 0, 0, 3868, 0, 8841, 0, 0, 8204, 0, 0, 9225, 0, 0, 8969, 9097, 9353, 0, 0, 0, 4108, 13068,
/* 362 */ 0, 0, 0, 12041, 28932, 0, 0, 0, 12425, 11273, 0, 0, 0, 12553, 3337, 11529, 0, 0, 11145, 28676, 0, 11657, 0, 0,
/* 386 */ 12169, 12297, 11785, 0, 0, 0, 28692, 31516, 5513, 0, 11268, 11913, 0, 0, 0, 29716, 0, 4876, 0, 0, 2844, 0,
/* 408 */ 11401, 10756, 5513, 0, 11268, 0, 4745, 0, 0, 3721, 0, 0, 12681, 0, 6420, 0, 0, 0, 30740, 10516, 5513, 0,
/* 430 */ 11268, 0, 5257, 0, 0, 4372, 0, 0, 3084, 0, 11401
};

const int RExParser::REDUCTION[] =
{
/*   0 */ 39, 0, 0, 1, 1, -1, 40, 2, 2, -1, 3, 3, 4, -1, 5, 4, 6, 5, 7, 6, 41, 7, 8, 8, 8, 8, 42, 9, 9, -1, 10, 8, 10,
/*  33 */ 8, 11, 10, 11, -1, 12, -1, 13, -1, 13, 14, 13, 13, 13, 12, 13, 11, 14, 17, 14, 16, 14, 15, 15, 18, 16, 19, 44,
/*  61 */ 24, 43, 22, 17, -1, 17, 23, 17, 21, 17, 20, 18, 27, 18, 26, 18, 27, 18, 26, 18, 25, 19, 28, 19, 28, 20, -1,
/*  88 */ 21, 29, 22, 30, 23, 32, 23, 31, 24, -1, 25, -1, 26, -1, 27, -1, 28, 89, 28, 88, 28, 66, 28, 65, 28, 64, 28,
/* 115 */ 63, 28, 62, 28, 61, 28, 60, 28, 59, 28, 58, 28, 57, 28, 56, 28, 87, 28, 86, 28, 85, 28, 84, 28, 83, 28, 82,
/* 142 */ 28, 81, 28, 80, 28, 79, 28, 78, 28, 77, 28, 76, 28, 75, 28, 74, 28, 73, 28, 72, 28, 71, 28, 70, 28, 69, 28,
/* 169 */ 68, 28, 67, 28, 55, 28, 54, 28, 53, 28, 52, 28, 51, 28, 50, 28, 49, 28, 48, 28, 47, 28, 46, 28, 45, 28, 44,
/* 196 */ 28, 43, 28, 42, 28, 41, 28, 40, 28, 39, 28, 38, 28, 37, 28, 36, 28, 35, 28, 34, 28, 33, 28, -1, 45, 90, 29,
/* 223 */ -1, 30, -1, 31, 91, 32, 93, 32, 92, 33, 94, 34, 95, 35, 97, 35, 96, 36, 98, 37, 99, 46, 100, 38, 101
};

const char *RExParser::TOKEN[] =
{
  "(0)",
  "whitespace",
  "equ",
  "identifier",
  "action",
  "character",
  "string",
  "string_e",
  "option_terminator",
  "EOF",
  "'#OPTION'",
  "'#OPTIONS'",
  "'$'",
  "','",
  "'.'",
  "'=='",
  "'ABBREVIATIONS'",
  "'AMBIGUITIES'",
  "'APPEND'",
  "'C'",
  "'CASE-INSENSITIVE'",
  "'CASE-SENSITIVE'",
  "'CLASS'",
  "'CLASSIFY'",
  "'COMPRESS'",
  "'CPP'",
  "'CSHARP'",
  "'DFA'",
  "'ERROR'",
  "'FASTER'",
  "'FULL'",
  "'GO'",
  "'GRAMMAR'",
  "'HAXE'",
  "'JAVA'",
  "'JAVASCRIPT'",
  "'LEXER'",
  "'MINIMIZE'",
  "'NFA'",
  "'NOABBREVIATIONS'",
  "'NOAMBIGUITIES'",
  "'NOAPPEND'",
  "'NOCLASSIFY'",
  "'NODFA'",
  "'NOGRAMMAR'",
  "'NOLEXER'",
  "'NOLIST'",
  "'NOMINIMIZE'",
  "'NONFA'",
  "'NOSELFTEST'",
  "'NOSYMBOLS'",
  "'NOTRACE'",
  "'NOTREE'",
  "'OUTPUT'",
  "'PACKAGE'",
  "'PREFIX'",
  "'PYTHON'",
  "'REX'",
  "'SCALA'",
  "'SELFTEST'",
  "'SMALLER'",
  "'STRINGPREFIX'",
  "'STRINGSUFFIX'",
  "'STRINGTYPE'",
  "'SUFFIX'",
  "'SYMBOLS'",
  "'TABLENAME'",
  "'TOKENPREFIX'",
  "'TOKENTABLENAME'",
  "'TRACE'",
  "'TREE'",
  "'TYPESCRIPT'",
  "'XQUERY'",
  "'XSLT'",
  "or",
  "integer",
  "'('",
  "')'",
  "'*'",
  "'+'",
  "'-'",
  "'..'",
  "'/'",
  "';'",
  "'>'",
  "'?'",
  "'['",
  "'\\'",
  "']'",
  "'{'",
  "'}'"
};

const char *RExParser::NONTERMINAL[] =
{
  "regular_grammar",
  "rule_list",
  "rule",
  "nonterminal",
  "semantic_part",
  "nongreedy",
  "token_code",
  "action_string",
  "top_level_expression",
  "context_expression",
  "expression",
  "sequence",
  "item_sequence",
  "closed_item",
  "quantity",
  "min",
  "max",
  "item",
  "character_set",
  "character_range_list",
  "character_range",
  "low_character",
  "high_character",
  "range_character",
  "option_stmt_list",
  "option_stmt",
  "option_introducer",
  "option_list",
  "option_specifier",
  "entry_stmt",
  "entry_list",
  "entry",
  "used_token_ref",
  "preference_stmt",
  "preferred",
  "unused_token_ref",
  "delimiter_stmt",
  "delimiter",
  "equivalence_stmt",
  "IMPLICIT-39",
  "IMPLICIT-40",
  "IMPLICIT-41",
  "IMPLICIT-42",
  "IMPLICIT-43",
  "IMPLICIT-44",
  "IMPLICIT-45",
  "IMPLICIT-46"
};

#endif

// End
