// This file was generated on Tue Oct 20, 2026 19:55 (UTC+02) by REx v6.3-SNAPSHOT which is Copyright (c) 1979-2026 by Gunther Rademacher <grd@gmx.net>
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
                                                            codepoints=true;
                                                            #line 898 "RExParser.hpp"
      }
      break;
    case 87:
      {
                                                            #line 187 "RExParser.ebnf"
                                                            codepoints=false;
                                                            #line 905 "RExParser.hpp"
      }
      break;
    case 88:
      {
                                                            #line 188 "RExParser.ebnf"
                                                            setCaseSensitive(true);
                                                            #line 912 "RExParser.hpp"
      }
      break;
    case 89:
      {
                                                            #line 189 "RExParser.ebnf"
                                                            setCaseSensitive(false);
                                                            #line 919 "RExParser.hpp"
      }
      break;
    case 90:
      {
                                                            #line 190 "RExParser.ebnf"
                                                            compression = getInteger();
                                                            #line 926 "RExParser.hpp"
      }
      break;
    case 91:
      {
                                                            #line 192 "RExParser.ebnf"
                                                            tokenDescriptors.setErrorCode(getInteger());
                                                            #line 933 "RExParser.hpp"
      }
      break;
    case 92:
      {
                                                            #line 194 "RExParser.ebnf"
                                                            newentry();
                                                            #line 940 "RExParser.hpp"
      }
      break;
    case 93:
      {
                                                            #line 198 "RExParser.ebnf"
                                                            collectentry(tokenref); tokenref = 0;
                                                            #line 947 "RExParser.hpp"
      }
      break;
    case 94:
      {
                                                            #line 200 "RExParser.ebnf"
                                                            currenttoken = getInteger();
                                                            tokenref = ref(tokencode, true);
                                                            #line 955 "RExParser.hpp"
      }
      break;
    case 95:
      {
                                                            #line 202 "RExParser.ebnf"
                                                            tokenref = ref(tokenname, true);
                                                            #line 962 "RExParser.hpp"
      }
      break;
    case 96:
      {
                                                            #line 205 "RExParser.ebnf"
                                                            preference(preferred, tokenref); tokenref = 0;
                                                            #line 969 "RExParser.hpp"
      }
      break;
    case 97:
      {
                                                            #line 206 "RExParser.ebnf"
                                                            preferred = tokenref;
                                                            #line 976 "RExParser.hpp"
      }
      break;
    case 98:
      {
                                                            #line 208 "RExParser.ebnf"
                                                            currenttoken = getInteger();
                                                            tokenref = ref(tokencode, false);
                                                            #line 984 "RExParser.hpp"
      }
      break;
    case 99:
      {
                                                            #line 210 "RExParser.ebnf"
                                                            tokenref = ref(tokenname, false);
                                                            #line 991 "RExParser.hpp"
      }
      break;
    case 100:
      {
                                                            #line 214 "RExParser.ebnf"
                                                            delimited(delimiter, tokenref); tokenref = 0;
                                                            #line 998 "RExParser.hpp"
      }
      break;
    case 101:
      {
                                                            #line 215 "RExParser.ebnf"
                                                            CString token = getToken();
                                                            delimiter = symbolTable->insertSymbol(token.c_str(), token.size());
                                                            #line 1006 "RExParser.hpp"
      }
      break;
    case 102:
      {
                                                            #line 219 "RExParser.ebnf"
                                                            firstcharLhs = firstchar; lastcharLhs = lastchar;
                                                            #line 1013 "RExParser.hpp"
      }
      break;
    case 103:
      {
                                                            #line 220 "RExParser.ebnf"
                                                            equivalence();
                                                            #line 1020 "RExParser.hpp"
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
    for (int i = 0; i < 93; i += 32)
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
    int i0 = t * 391 + s - 1;
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
};

const int RExParser::MAP0[] =
{
/*   0 */ 59, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 4, 5, 6,
/*  36 */ 7, 8, 3, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 19, 19, 19, 19, 19, 19, 19, 19, 20, 21, 22, 23, 24, 25, 3,
/*  65 */ 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52,
/*  92 */ 53, 54, 55, 48, 3, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48,
/* 120 */ 49, 50, 51, 56, 4, 57, 3, 3
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
/* 242 */ 355, 355, 355, 355, 407, 59, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/* 275 */ 0, 0, 1, 4, 5, 6, 7, 8, 3, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 19, 19, 19, 19, 19, 19, 19, 19, 20, 21,
/* 305 */ 22, 23, 24, 25, 3, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48,
/* 333 */ 49, 50, 51, 52, 53, 54, 55, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 3, 48, 48, 48, 48, 48, 48,
/* 361 */ 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 56, 4, 57, 3, 3, 3, 3, 3,
/* 390 */ 3, 3, 3, 3, 3, 3, 3, 48, 48, 3, 3, 3, 3, 3, 3, 3, 58, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 58, 58,
/* 425 */ 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58
};

const int RExParser::MAP2[] =
{
/*  0 */ 57344, 63744, 64976, 65008, 65536, 983040, 63743, 64975, 65007, 65533, 983039, 1114111, 3, 48, 3, 48, 48, 3
};

const int RExParser::INITIAL[] =
{
/*  0 */ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30,
/* 30 */ 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45
};

const int RExParser::TRANSITION[] =
{
/*    0 */ 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367,
/*   18 */ 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 1920, 1938, 1922, 1954,
/*   36 */ 4274, 1984, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367,
/*   54 */ 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2006, 2026, 2010, 2367, 2367, 2367, 2367, 2367,
/*   72 */ 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367,
/*   90 */ 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2042, 4274, 1984, 2367, 2367, 2367, 2367, 2367, 2367,
/*  108 */ 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367,
/*  126 */ 2367, 2367, 5467, 5538, 5528, 2042, 4274, 1984, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367,
/*  144 */ 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 4935, 4767,
/*  162 */ 5084, 2070, 4274, 2116, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367,
/*  180 */ 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2163, 2170, 2186, 2042, 4274, 1984,
/*  198 */ 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367,
/*  216 */ 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 3152, 2042, 4274, 1984, 2367, 2367, 2367, 2367,
/*  234 */ 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367,
/*  252 */ 2367, 2367, 2367, 2367, 2367, 2217, 4700, 2042, 4274, 1984, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367,
/*  270 */ 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367,
/*  288 */ 5201, 4851, 2235, 2262, 4274, 2307, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367,
/*  306 */ 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2366, 3419, 2356, 2042,
/*  324 */ 4274, 1984, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367,
/*  342 */ 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 5358, 5599, 2129, 2042, 4274, 1984, 2367, 2367,
/*  360 */ 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367,
/*  378 */ 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 5500, 2042, 4274, 1984, 2367, 2367, 2367, 2367, 2367, 2367,
/*  396 */ 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367,
/*  414 */ 2367, 2367, 2367, 2367, 4873, 2042, 4274, 1984, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367,
/*  432 */ 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 3481,
/*  450 */ 2384, 2042, 4274, 1984, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367,
/*  468 */ 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 5141, 2402, 4274, 1984,
/*  486 */ 2367, 2367, 2367, 2367, 2367, 2094, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367,
/*  504 */ 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2368, 2430, 2457, 4274, 1984, 2367, 2367, 2367, 2367,
/*  522 */ 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367,
/*  540 */ 2367, 2367, 2367, 2367, 2367, 4607, 4191, 2042, 4274, 1984, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367,
/*  558 */ 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367,
/*  576 */ 4378, 2488, 2525, 2557, 4274, 2591, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367,
/*  594 */ 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2537, 2627, 2613, 2557,
/*  612 */ 4274, 2591, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367,
/*  630 */ 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2643, 2646, 2702, 2042, 4274, 1984, 2367, 2367,
/*  648 */ 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367,
/*  666 */ 2367, 2367, 2367, 2367, 2367, 2367, 5232, 2672, 2662, 2042, 4274, 1984, 2367, 2367, 2367, 2367, 2367, 2367,
/*  684 */ 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367,
/*  702 */ 2367, 2367, 2199, 2201, 2367, 2042, 4274, 1984, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367,
/*  720 */ 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2688, 5450,
/*  738 */ 2719, 2737, 4274, 1984, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367,
/*  756 */ 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 4895, 2219, 2773, 2790, 4274, 2818,
/*  774 */ 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367,
/*  792 */ 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 3775, 2509, 2840, 2042, 4274, 1984, 2367, 2367, 2367, 2367,
/*  810 */ 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367,
/*  828 */ 2367, 2367, 2367, 2367, 2367, 2962, 2874, 2921, 2937, 2953, 2887, 2980, 3007, 4024, 2367, 2367, 1968, 3054,
/*  846 */ 2757, 2367, 2367, 2367, 3073, 4412, 2367, 2575, 2367, 4439, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367,
/*  864 */ 2367, 2962, 3095, 3122, 4274, 2953, 3188, 3190, 2367, 2284, 4061, 2367, 3206, 2367, 2367, 2569, 2367, 2367,
/*  882 */ 2367, 3874, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2962, 3224, 2402,
/*  900 */ 4382, 2953, 2367, 3258, 2367, 2367, 3642, 2367, 2367, 2367, 5638, 5631, 3520, 2367, 2367, 2367, 2367, 2367,
/*  918 */ 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2962, 3279, 2402, 4274, 2953, 5444, 3313,
/*  936 */ 2367, 2367, 2367, 2367, 3292, 2367, 3332, 2367, 2367, 2367, 2367, 3350, 2367, 2367, 2367, 2367, 2367, 2367,
/*  954 */ 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2962, 3367, 2402, 4233, 2953, 2367, 5565, 3401, 3435, 2100, 3469,
/*  972 */ 3855, 4257, 2414, 3506, 4653, 3540, 4293, 2802, 3576, 3606, 3637, 3413, 3658, 2367, 2367, 2367, 2367, 2367,
/*  990 */ 2367, 2367, 2367, 2962, 3681, 2402, 3715, 2953, 2367, 4416, 2367, 3739, 3731, 2367, 2367, 2367, 2367, 3804,
/* 1008 */ 2597, 2367, 2367, 2367, 5266, 3755, 3773, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2962,
/* 1026 */ 3791, 2402, 4274, 3825, 2367, 3852, 2367, 2367, 2367, 5170, 2367, 2367, 2367, 3665, 2367, 3871, 2367, 2367,
/* 1044 */ 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2962, 3890, 2402, 4274, 3825,
/* 1062 */ 4053, 2367, 2900, 2367, 3919, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367,
/* 1080 */ 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2962, 3095, 2402, 3490, 3825, 2367, 2367, 4539, 2082,
/* 1098 */ 4646, 3938, 2367, 3957, 3980, 3449, 5095, 2367, 4514, 4009, 4044, 4128, 3137, 4077, 4098, 2367, 2367, 2367,
/* 1116 */ 2367, 2367, 2367, 2367, 2367, 2962, 4115, 2402, 4274, 3825, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367,
/* 1134 */ 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367,
/* 1152 */ 2367, 2962, 3095, 2402, 4274, 3825, 2367, 2703, 2367, 2367, 4152, 2367, 2367, 2367, 2367, 2367, 2367, 2367,
/* 1170 */ 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2962, 4169, 4207,
/* 1188 */ 4274, 3825, 3263, 4223, 5009, 4249, 5124, 2367, 3809, 3380, 2367, 2367, 4273, 2367, 2367, 4711, 2367, 4290,
/* 1206 */ 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2962, 4309, 4363, 2541, 3825, 5494, 4398,
/* 1224 */ 2367, 4432, 2367, 3524, 5174, 2367, 2367, 4455, 2367, 2749, 2367, 4082, 2367, 2367, 2367, 4153, 2367, 2367,
/* 1242 */ 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2962, 4472, 2402, 4274, 3825, 2367, 4510, 2367, 2367, 2367, 3237,
/* 1260 */ 2291, 2274, 2367, 3242, 4530, 4563, 3038, 2367, 2367, 2246, 2367, 4583, 4603, 2367, 2367, 2367, 2367, 2367,
/* 1278 */ 2367, 2367, 2367, 2962, 4623, 4669, 3621, 3825, 2367, 2367, 3208, 5300, 2367, 2367, 2367, 4685, 3694, 2367,
/* 1296 */ 2367, 3964, 2367, 4734, 2367, 2367, 2140, 3922, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2962,
/* 1314 */ 4754, 4783, 4274, 4799, 4815, 2367, 4838, 5417, 2367, 3030, 4867, 2367, 2851, 2367, 4889, 3903, 2367, 2367,
/* 1332 */ 3993, 2503, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2962, 3095, 2402, 2386, 3825,
/* 1350 */ 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367,
/* 1368 */ 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2962, 4911, 2402, 4958, 3825, 4942, 3297, 5134, 5208,
/* 1386 */ 2367, 4547, 2367, 3453, 3172, 2367, 3941, 3106, 4974, 5053, 2858, 2367, 2367, 2367, 2367, 2367, 2367, 2367,
/* 1404 */ 2367, 2367, 2367, 2367, 2367, 2962, 4996, 5029, 2721, 3825, 4924, 5045, 5605, 2367, 2367, 2441, 4136, 2905,
/* 1422 */ 5069, 2367, 5013, 3590, 4335, 2367, 5111, 3560, 5291, 2991, 3552, 2367, 2367, 2367, 2367, 2367, 2367, 2367,
/* 1440 */ 2367, 2962, 5157, 2402, 4028, 5190, 2367, 5224, 2054, 2367, 5375, 2367, 2367, 3021, 2367, 5248, 5282, 5308,
/* 1458 */ 3163, 2340, 2322, 4822, 4347, 3385, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2962, 3095, 2402,
/* 1476 */ 5324, 3825, 2367, 2367, 5340, 2367, 2367, 2367, 3334, 2367, 5374, 2367, 2367, 2367, 4099, 4718, 2367, 2367,
/* 1494 */ 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2962, 3095, 2402, 4274, 3825, 2964, 2367,
/* 1512 */ 2367, 2367, 2367, 2367, 2367, 2774, 2367, 2367, 2367, 2367, 3757, 2367, 2367, 2367, 2367, 4567, 4182, 2367,
/* 1530 */ 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2962, 3095, 2402, 4274, 3825, 2367, 2367, 2367, 2367, 2367, 2367,
/* 1548 */ 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367,
/* 1566 */ 2367, 2367, 2367, 2962, 5391, 2402, 4274, 3825, 3057, 2331, 2367, 2367, 2367, 2367, 5257, 2367, 2367, 5571,
/* 1584 */ 2367, 2367, 2367, 2367, 2367, 2367, 4456, 5349, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2962,
/* 1602 */ 3095, 2402, 1990, 3825, 2367, 2367, 2367, 3316, 2367, 2367, 2367, 2367, 2367, 2367, 4485, 2367, 2147, 2824,
/* 1620 */ 2367, 4587, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2962, 3095, 2402, 4274, 3825,
/* 1638 */ 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 3351, 2367, 2367, 2367, 3079, 2367, 2367, 2367,
/* 1656 */ 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 5407, 3836, 5433, 2042, 4274, 1984, 2367, 2367, 2367, 2367,
/* 1674 */ 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367,
/* 1692 */ 2367, 2367, 2367, 2367, 3699, 2367, 5466, 2042, 4274, 1984, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367,
/* 1710 */ 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367,
/* 1728 */ 2367, 4494, 5483, 2042, 4274, 1984, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367,
/* 1746 */ 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 5516,
/* 1764 */ 4274, 5554, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367,
/* 1782 */ 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2470, 2472, 4980, 2042, 4274, 1984, 2367, 2367,
/* 1800 */ 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367,
/* 1818 */ 2367, 2367, 2367, 2367, 2367, 2367, 4738, 4636, 2367, 5587, 4274, 5621, 2367, 2367, 2367, 2367, 2367, 2367,
/* 1836 */ 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367,
/* 1854 */ 2367, 2367, 2367, 2367, 2367, 2402, 4274, 1984, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367,
/* 1872 */ 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367,
/* 1890 */ 4322, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367,
/* 1908 */ 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 2367, 0, 0, 1070, 1070, 1070, 1070, 1070,
/* 1927 */ 1070, 1070, 1070, 1070, 1070, 1070, 1070, 1070, 1070, 1104, 0, 1070, 1070, 1070, 1070, 1070, 1070, 1070,
/* 1945 */ 1070, 1070, 0, 1070, 1070, 1070, 1070, 1070, 1070, 0, 82, 83, 84, 86, 54, 55, 0, 0, 0, 92, 94, 0, 1104, 0, 0,
/* 1970 */ 0, 239, 0, 23552, 241, 0, 0, 0, 26112, 0, 0, 247, 0, 250, 0, 82, 83, 84, 0, 86, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/* 2000 */ 119, 0, 126, 130, 0, 1104, 0, 0, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024,
/* 2020 */ 1024, 1024, 4608, 0, 0, 0, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 0, 1024, 1024, 1024, 1024,
/* 2040 */ 1024, 1024, 0, 82, 83, 84, 86, 54, 55, 0, 0, 0, 92, 94, 0, 0, 0, 0, 0, 178, 0, 0, 0, 0, 0, 0, 0, 0, 0, 188,
/* 2070 */ 0, 82, 83, 85, 86, 4184, 55, 0, 0, 0, 93, 94, 0, 0, 0, 0, 0, 192, 0, 0, 0, 0, 201, 202, 0, 0, 0, 0, 0, 227,
/* 2100 */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 218, 0, 37376, 220, 221, 0, 0, 82, 83, 3669, 84, 86, 0, 54, 0, 0, 0, 3072, 92,
/* 2129 */ 0, 0, 0, 0, 0, 40960, 0, 0, 40960, 40960, 40960, 0, 0, 0, 0, 0, 0, 370, 0, 0, 0, 0, 0, 0, 0, 0, 0, 12288, 0,
/* 2158 */ 0, 0, 0, 0, 0, 0, 0, 1071, 1071, 1071, 1071, 1071, 1071, 1071, 1071, 1071, 1071, 1071, 1071, 1071, 1071, 0,
/* 2180 */ 1071, 1071, 1071, 1071, 1071, 1071, 1071, 1071, 1086, 1071, 1086, 1071, 1071, 1071, 1071, 1071, 1071, 1071,
/* 2198 */ 70191, 0, 0, 0, 0, 50, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 57, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/* 2232 */ 0, 0, 44544, 0, 0, 60, 53, 60, 53, 53, 53, 53, 53, 53, 0, 0, 0, 0, 0, 0, 361, 0, 0, 0, 0, 0, 0, 365, 0, 0, 0,
/* 2263 */ 82, 83, 84, 87, 54, 4185, 0, 0, 0, 92, 95, 0, 0, 0, 0, 0, 255, 0, 0, 0, 259, 0, 0, 0, 0, 0, 0, 193, 0, 0, 0,
/* 2294 */ 0, 0, 0, 0, 0, 0, 244, 0, 0, 0, 0, 0, 0, 0, 82, 83, 84, 0, 3671, 86, 0, 55, 0, 0, 0, 0, 3072, 94, 0, 0, 0,
/* 2325 */ 345, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 30720, 0, 0, 0, 0, 0, 0, 0, 0, 31744, 0, 0, 0, 0, 0, 0, 0, 341,
/* 2356 */ 40448, 0, 40448, 40448, 40448, 40448, 40448, 40448, 40448, 40448, 40448, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/* 2379 */ 0, 0, 0, 0, 61, 0, 7168, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 131, 1104, 0, 82, 83, 84, 86, 54, 55, 0,
/* 2410 */ 0, 2106, 92, 94, 0, 0, 0, 0, 0, 269, 0, 0, 0, 0, 0, 0, 0, 275, 0, 277, 0, 61, 7680, 7680, 7680, 7680, 7680,
/* 2437 */ 7680, 7680, 7680, 7680, 0, 0, 0, 0, 0, 0, 12004, 0, 0, 0, 0, 0, 0, 234, 0, 0, 0, 82, 83, 84, 86, 54, 55, 0,
/* 2465 */ 0, 2106, 92, 94, 43008, 0, 0, 0, 0, 51, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 39984, 39984, 39984, 39984,
/* 2493 */ 0, 0, 0, 0, 39984, 0, 0, 0, 39984, 39984, 0, 0, 0, 358, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45056, 45056, 0,
/* 2522 */ 0, 0, 0, 0, 0, 39984, 39984, 39984, 39984, 39984, 39984, 39984, 39984, 39984, 0, 0, 0, 0, 39985, 0, 0, 0, 0,
/* 2545 */ 0, 0, 0, 0, 0, 0, 0, 0, 123, 0, 0, 1104, 39985, 82, 83, 84, 86, 54, 55, 0, 0, 2106, 92, 94, 0, 0, 0, 0, 0,
/* 2574 */ 282, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 363, 0, 0, 0, 0, 0, 40017, 82, 83, 84, 0, 86, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/* 2606 */ 0, 298, 0, 0, 0, 0, 0, 0, 0, 39985, 39985, 39985, 39985, 39985, 39985, 39985, 39985, 39985, 0, 0, 0, 0,
/* 2628 */ 39985, 39985, 39985, 39985, 0, 0, 0, 0, 39985, 0, 0, 0, 39985, 39985, 0, 0, 0, 1536, 0, 0, 0, 0, 0, 0, 0, 0,
/* 2654 */ 0, 0, 1536, 1536, 0, 0, 0, 0, 0, 44032, 0, 0, 0, 0, 44032, 44032, 44032, 44032, 44032, 0, 0, 0, 0, 0, 0, 0,
/* 2680 */ 0, 0, 0, 44032, 44032, 0, 0, 0, 0, 0, 1536, 0, 0, 0, 0, 0, 0, 56, 0, 0, 0, 1536, 1536, 0, 0, 0, 0, 0, 0, 0,
/* 2710 */ 0, 0, 0, 0, 0, 0, 0, 0, 171, 1536, 56, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 132, 1104, 0, 82, 83, 84,
/* 2741 */ 86, 54, 55, 8192, 0, 0, 92, 94, 0, 0, 0, 0, 0, 308, 0, 309, 0, 0, 0, 0, 0, 0, 0, 0, 270, 0, 0, 0, 0, 0, 0, 0,
/* 2773 */ 44544, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 263, 0, 0, 83, 84, 86, 54, 55, 0, 0, 0, 92, 94, 0, 0, 0,
/* 2805 */ 0, 0, 332, 0, 0, 0, 0, 0, 0, 338, 0, 0, 0, 0, 2560, 83, 84, 0, 86, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 336, 0, 0,
/* 2837 */ 0, 0, 0, 45056, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45056, 0, 0, 0, 0, 0, 0, 14336, 0, 0, 0, 0, 0, 0, 0, 0, 0, 24064,
/* 2868 */ 0, 0, 0, 0, 0, 0, 0, 0, 2106, 2106, 2106, 2106, 2106, 2106, 2106, 2106, 2106, 63, 63, 0, 0, 0, 0, 139, 0, 0,
/* 2894 */ 0, 14848, 0, 0, 0, 146, 0, 0, 0, 0, 177, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 260, 0, 0, 0, 0, 0, 82, 83, 84, 86,
/* 2926 */ 54, 55, 0, 0, 2106, 92, 94, 0, 0, 0, 100, 0, 0, 107, 0, 110, 111, 0, 0, 0, 0, 117, 0, 0, 127, 0, 1104, 40017,
/* 2954 */ 82, 83, 84, 0, 86, 0, 0, 0, 0, 2106, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 148, 0, 0, 20480, 151, 0, 0,
/* 2985 */ 0, 0, 0, 164, 0, 166, 0, 0, 0, 0, 0, 0, 23040, 0, 0, 0, 8704, 0, 0, 0, 21504, 0, 172, 0, 0, 0, 0, 0, 0, 0, 0,
/* 3016 */ 0, 0, 0, 0, 186, 0, 0, 0, 253, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 229, 0, 0, 0, 0, 0, 0, 0, 0, 323, 0, 324,
/* 3049 */ 0, 0, 0, 0, 0, 0, 0, 31232, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 147, 0, 149, 316, 0, 318, 0, 0, 320, 0, 0,
/* 3081 */ 0, 0, 0, 0, 0, 0, 0, 0, 351, 0, 0, 0, 0, 0, 0, 0, 2106, 2106, 2106, 2106, 2106, 2106, 2106, 2106, 2106, 0, 0,
/* 3108 */ 0, 0, 0, 0, 24576, 0, 0, 0, 0, 0, 0, 32256, 0, 0, 0, 82, 83, 84, 86, 54, 55, 0, 0, 2106, 92, 94, 0, 0, 97, 0,
/* 3138 */ 0, 0, 368, 0, 0, 0, 0, 0, 0, 0, 374, 0, 376, 377, 0, 0, 0, 6656, 0, 6656, 6656, 6656, 6656, 6656, 6656, 0, 0,
/* 3165 */ 0, 0, 0, 0, 321, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15872, 0, 0, 0, 273, 0, 0, 0, 0, 135, 136, 0, 0, 0, 0, 0, 0, 0,
/* 3197 */ 0, 0, 0, 0, 0, 0, 0, 170, 0, 236, 237, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 187, 0, 0, 0, 2106, 2106,
/* 3228 */ 2106, 2106, 2106, 2106, 2106, 2106, 2106, 10304, 10304, 0, 0, 0, 0, 226, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/* 3253 */ 30208, 0, 0, 0, 0, 0, 0, 152, 0, 161, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 145, 0, 0, 0, 0, 0, 0, 2106, 2106,
/* 3283 */ 2106, 2106, 2106, 2106, 2106, 2106, 2106, 65, 65, 0, 0, 0, 0, 240, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 167, 0,
/* 3310 */ 0, 0, 0, 0, 0, 153, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 205, 0, 0, 0, 9728, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/* 3344 */ 0, 0, 0, 0, 249, 0, 22016, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 302, 0, 0, 2106, 2106, 2106, 2106,
/* 3373 */ 2106, 2106, 2106, 2106, 2106, 66, 66, 0, 0, 0, 0, 254, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 385, 0, 0, 0, 0, 173,
/* 3402 */ 0, 0, 0, 0, 0, 0, 0, 181, 182, 0, 184, 0, 0, 0, 0, 0, 383, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 40448, 0, 0, 0, 0,
/* 3434 */ 0, 0, 0, 17920, 0, 191, 0, 0, 0, 0, 0, 200, 0, 0, 204, 0, 0, 0, 280, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 261,
/* 3466 */ 2048, 0, 0, 222, 0, 224, 0, 0, 0, 0, 0, 0, 0, 0, 232, 0, 0, 0, 0, 0, 7168, 7168, 7168, 7168, 0, 0, 0, 0, 0,
/* 3495 */ 0, 0, 113, 0, 0, 0, 0, 0, 0, 0, 1104, 0, 279, 0, 0, 0, 0, 0, 28160, 0, 0, 0, 0, 285, 286, 0, 0, 0, 292, 0, 0,
/* 3526 */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 233, 0, 0, 235, 303, 0, 0, 0, 0, 0, 0, 0, 0, 0, 27648, 29184, 0, 0, 0, 0, 0,
/* 3557 */ 20992, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 12800, 0, 0, 0, 0, 0, 0, 0, 0, 343, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/* 3589 */ 353, 0, 0, 0, 306, 0, 0, 0, 0, 0, 0, 0, 0, 312, 0, 314, 34816, 35328, 0, 0, 0, 0, 360, 0, 0, 0, 0, 0, 0, 0,
/* 3619 */ 0, 25600, 0, 0, 0, 16896, 0, 0, 0, 0, 115, 0, 0, 0, 0, 128, 0, 1104, 0, 0, 33792, 0, 369, 0, 0, 0, 0, 0, 0,
/* 3648 */ 0, 0, 0, 0, 0, 219, 0, 0, 0, 0, 0, 11264, 0, 36352, 0, 0, 10752, 0, 0, 0, 0, 0, 0, 0, 0, 0, 284, 0, 0, 0, 0,
/* 3679 */ 287, 0, 0, 0, 2106, 2106, 2106, 2106, 2106, 2106, 2106, 2106, 2106, 67, 67, 0, 0, 0, 0, 268, 0, 0, 0, 0, 0,
/* 3704 */ 0, 0, 0, 0, 0, 0, 46080, 0, 0, 0, 0, 105, 0, 0, 0, 0, 0, 0, 0, 114, 0, 0, 0, 0, 0, 0, 1104, 0, 209, 0, 0,
/* 3735 */ 212, 0, 0, 215, 0, 0, 0, 0, 0, 0, 0, 0, 198, 0, 0, 0, 203, 0, 0, 0, 0, 356, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/* 3768 */ 0, 0, 0, 326, 0, 366, 367, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45056, 0, 0, 0, 2106, 2106, 2106, 2106,
/* 3797 */ 2106, 2106, 2106, 2106, 2106, 68, 68, 0, 0, 0, 0, 281, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 245, 0, 0, 0, 0, 0,
/* 3826 */ 82, 83, 84, 0, 86, 0, 0, 0, 0, 2106, 0, 0, 0, 0, 0, 0, 45568, 0, 0, 45568, 0, 0, 0, 45568, 0, 0, 0, 0, 154,
/* 3855 */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 248, 0, 0, 0, 304, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 339, 0,
/* 3889 */ 0, 0, 0, 2106, 2106, 2106, 2106, 2106, 2106, 2106, 2106, 2106, 69, 69, 0, 0, 0, 0, 307, 0, 0, 0, 0, 0, 0, 0,
/* 3915 */ 0, 0, 313, 0, 0, 0, 210, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 387, 0, 0, 0, 223, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/* 3949 */ 0, 0, 0, 0, 0, 17408, 301, 0, 251, 0, 0, 0, 0, 0, 256, 0, 0, 0, 0, 0, 0, 0, 0, 0, 311, 0, 0, 0, 0, 0, 0, 0,
/* 3981 */ 0, 265, 267, 0, 0, 0, 0, 0, 0, 272, 0, 274, 0, 0, 0, 0, 346, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 355, 0, 328, 0, 0,
/* 4013 */ 331, 0, 0, 0, 0, 0, 0, 0, 0, 0, 340, 0, 0, 0, 18622, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 124, 0, 0, 1104,
/* 4044 */ 342, 0, 0, 0, 0, 347, 348, 0, 350, 0, 0, 0, 0, 0, 0, 0, 142, 0, 0, 0, 0, 0, 0, 0, 0, 216, 0, 0, 0, 0, 0, 0,
/* 4076 */ 0, 0, 0, 380, 381, 382, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 337, 0, 0, 0, 0, 389, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/* 4109 */ 0, 0, 0, 0, 0, 327, 0, 0, 2106, 2106, 2106, 2106, 2106, 2106, 2106, 2106, 2106, 70, 70, 0, 0, 0, 0, 359, 0,
/* 4134 */ 0, 362, 0, 0, 0, 0, 0, 0, 0, 0, 243, 0, 0, 0, 0, 0, 0, 0, 208, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/* 4168 */ 388, 0, 0, 2106, 2106, 2106, 2106, 2106, 2106, 2106, 2106, 2106, 71, 71, 0, 0, 0, 0, 391, 0, 0, 0, 0, 0, 0,
/* 4193 */ 0, 0, 0, 0, 0, 43520, 43520, 43520, 43520, 0, 0, 0, 0, 0, 0, 82, 83, 84, 86, 54, 55, 0, 0, 2106, 92, 94, 0,
/* 4220 */ 0, 0, 101, 0, 0, 155, 0, 0, 0, 0, 0, 0, 165, 0, 0, 0, 0, 0, 0, 112, 0, 0, 0, 0, 120, 122, 0, 0, 1104, 16384,
/* 4250 */ 0, 0, 0, 0, 0, 0, 196, 0, 0, 0, 0, 0, 0, 0, 0, 258, 0, 36864, 0, 0, 0, 0, 0, 288, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/* 4283 */ 0, 0, 0, 0, 0, 0, 1104, 0, 0, 357, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 19968, 0, 0, 0, 0, 2106, 2106,
/* 4313 */ 2106, 2106, 2106, 2106, 2106, 2106, 2106, 72, 72, 0, 0, 0, 0, 5120, 0, 0, 0, 0, 0, 0, 0, 70144, 0, 0, 0, 0,
/* 4339 */ 6144, 0, 0, 322, 0, 0, 0, 13312, 0, 0, 0, 0, 0, 37888, 0, 0, 0, 372, 373, 0, 375, 0, 0, 0, 0, 82, 83, 84, 86,
/* 4368 */ 54, 55, 0, 0, 2106, 92, 94, 0, 0, 98, 0, 0, 0, 39984, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 121, 0, 0, 1104, 0,
/* 4399 */ 0, 156, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 169, 0, 0, 0, 330, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 168, 0, 0, 0, 0,
/* 4433 */ 189, 0, 0, 0, 0, 194, 0, 0, 0, 0, 0, 0, 0, 0, 0, 384, 0, 0, 0, 0, 0, 0, 278, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/* 4467 */ 0, 0, 0, 0, 35840, 0, 0, 2106, 2106, 2106, 2106, 2106, 2106, 2106, 2106, 2106, 73, 73, 0, 0, 0, 0, 38400, 0,
/* 4491 */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 46592, 0, 46592, 0, 0, 0, 0, 46592, 0, 150, 0, 157, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/* 4522 */ 0, 0, 0, 0, 325, 0, 0, 0, 0, 289, 0, 0, 0, 5925, 0, 0, 296, 0, 0, 0, 0, 0, 0, 0, 180, 0, 0, 0, 0, 0, 0, 0, 0,
/* 4555 */ 230, 231, 15360, 0, 0, 0, 19456, 0, 0, 0, 305, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 386, 0, 0, 0, 378, 379,
/* 4585 */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 22528, 0, 0, 0, 0, 0, 390, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/* 4619 */ 43520, 0, 0, 0, 0, 0, 2106, 2106, 2106, 2106, 2106, 2106, 2106, 2106, 2106, 74, 74, 0, 0, 0, 0, 47616, 0, 0,
/* 4643 */ 0, 47616, 0, 0, 0, 0, 0, 0, 0, 214, 0, 0, 0, 0, 0, 0, 0, 0, 0, 297, 0, 0, 0, 0, 0, 0, 0, 82, 83, 84, 86, 54,
/* 4675 */ 55, 0, 90, 2106, 92, 94, 0, 96, 0, 102, 0, 252, 0, 0, 0, 0, 0, 257, 0, 0, 0, 0, 0, 0, 262, 0, 0, 57, 57, 57,
/* 4705 */ 57, 57, 57, 57, 57, 57, 0, 0, 0, 0, 0, 0, 333, 0, 0, 0, 0, 0, 0, 0, 0, 0, 335, 0, 0, 0, 0, 0, 0, 0, 0, 329,
/* 4737 */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 47616, 0, 0, 0, 0, 0, 2106, 2106, 2106, 2106, 2106, 2106, 2106, 2106,
/* 4764 */ 2106, 75, 75, 0, 0, 0, 59, 0, 0, 0, 0, 0, 0, 0, 0, 0, 59, 59, 0, 0, 82, 83, 84, 86, 54, 55, 0, 0, 2106, 92,
/* 4794 */ 94, 0, 0, 99, 103, 0, 82, 83, 84, 0, 86, 0, 0, 0, 0, 2106, 0, 0, 0, 0, 134, 0, 0, 137, 0, 0, 0, 13824, 0, 0,
/* 4824 */ 0, 0, 0, 0, 0, 0, 0, 18944, 0, 364, 0, 0, 0, 26624, 0, 174, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 185, 0, 0, 0, 60,
/* 4855 */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 60, 60, 0, 0, 0, 238, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 41984, 0, 0, 0, 0, 0,
/* 4889 */ 0, 0, 290, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 44544, 0, 0, 0, 0, 0, 0, 0, 2106, 2106, 2106, 2106, 2106,
/* 4918 */ 2106, 2106, 2106, 2106, 76, 76, 0, 0, 0, 138, 0, 0, 0, 0, 0, 0, 144, 0, 0, 0, 0, 0, 52, 54, 0, 0, 0, 0, 0, 0,
/* 4948 */ 0, 0, 0, 143, 0, 0, 0, 0, 0, 0, 0, 106, 0, 109, 0, 0, 0, 0, 0, 0, 118, 0, 0, 129, 0, 1104, 0, 317, 0, 319, 0,
/* 4979 */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 47104, 0, 0, 0, 0, 0, 0, 0, 2106, 2106, 2106, 2106, 2106, 2106, 2106, 2106,
/* 5006 */ 2106, 77, 77, 0, 0, 0, 176, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 300, 0, 0, 0, 0, 82, 83, 84, 86, 54, 55, 0,
/* 5037 */ 0, 2106, 92, 94, 0, 0, 0, 104, 0, 0, 158, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 334, 0, 0, 0, 0, 0, 0, 0, 0,
/* 5070 */ 0, 266, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 276, 0, 0, 59, 52, 59, 52, 52, 52, 52, 52, 52, 0, 0, 0, 0, 0, 0,
/* 5101 */ 294, 295, 0, 0, 0, 299, 0, 0, 0, 0, 0, 0, 344, 0, 0, 0, 0, 0, 0, 0, 0, 352, 27136, 0, 0, 0, 211, 0, 213, 0,
/* 5131 */ 0, 0, 217, 0, 0, 0, 0, 0, 0, 179, 0, 0, 0, 0, 0, 0, 0, 0, 0, 42496, 42496, 0, 0, 0, 0, 0, 0, 0, 2106, 2106,
/* 5161 */ 2106, 2106, 2106, 2106, 2106, 2106, 2106, 78, 78, 0, 0, 0, 225, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 246, 0,
/* 5188 */ 0, 0, 0, 82, 83, 84, 0, 86, 0, 0, 0, 133, 2106, 0, 0, 0, 0, 0, 53, 55, 0, 0, 0, 0, 0, 0, 0, 0, 0, 199, 0, 0,
/* 5220 */ 0, 0, 206, 0, 0, 0, 159, 160, 0, 0, 163, 0, 0, 0, 0, 0, 0, 0, 0, 0, 44032, 0, 0, 0, 0, 44032, 0, 0, 0, 0,
/* 5250 */ 25088, 0, 0, 0, 0, 0, 28672, 0, 0, 0, 0, 0, 0, 0, 242, 0, 0, 0, 0, 0, 0, 0, 0, 349, 0, 0, 0, 0, 0, 0, 354, 0,
/* 5282 */ 0, 0, 291, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9216, 371, 0, 0, 0, 0, 0, 0, 0, 197, 0, 0, 0, 0, 0, 0, 0,
/* 5315 */ 0, 310, 0, 0, 0, 0, 0, 315, 0, 0, 0, 108, 0, 0, 0, 0, 0, 0, 116, 0, 0, 125, 0, 0, 1104, 0, 0, 175, 0, 0, 0,
/* 5346 */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 32768, 33280, 0, 0, 0, 0, 0, 0, 0, 40960, 0, 0, 0, 0, 0, 0, 0, 40960, 264, 0,
/* 5376 */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 38912, 0, 0, 2106, 2106, 2106, 2106, 2106, 2106, 2106, 2106, 2106,
/* 5402 */ 79, 79, 0, 0, 81, 0, 45568, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 195, 0, 0, 0, 0, 0, 0, 0, 0, 207, 0,
/* 5434 */ 45568, 45568, 45568, 45568, 45568, 45568, 45568, 45568, 45568, 45568, 0, 0, 0, 0, 0, 140, 0, 0, 0, 0, 0, 0,
/* 5456 */ 0, 0, 0, 0, 1536, 1536, 0, 0, 0, 56, 46080, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 39424, 0, 46592, 0,
/* 5486 */ 46592, 0, 46592, 46592, 46592, 46592, 46592, 46592, 0, 0, 0, 0, 0, 141, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 41472,
/* 5511 */ 0, 0, 0, 0, 0, 0, 82, 83, 84, 86, 54, 55, 0, 0, 2139, 92, 94, 0, 0, 0, 0, 0, 39424, 39424, 39424, 39424,
/* 5537 */ 39424, 39424, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 39424, 0, 0, 0, 0, 82, 83, 84, 0, 86, 0, 0, 0, 0, 2139, 0, 0,
/* 5567 */ 0, 0, 0, 162, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 29696, 0, 0, 0, 0, 34304, 0, 82, 0, 84, 86, 54, 55, 0, 0, 0, 92,
/* 5598 */ 94, 0, 0, 0, 0, 0, 40960, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 183, 0, 0, 0, 0, 0, 0, 82, 2560, 84, 0, 86, 0, 0, 0,
/* 5630 */ 0, 0, 0, 0, 0, 0, 0, 283, 0, 0, 0, 0, 0, 0, 0, 0, 0, 271, 0, 0, 0, 0, 0, 0
};

const int RExParser::EXPECTED[] =
{
/*   0 */ 74, 78, 82, 86, 90, 97, 101, 233, 136, 194, 233, 137, 233, 123, 112, 233, 118, 233, 130, 152, 122, 133, 127,
/*  23 */ 141, 145, 233, 233, 232, 147, 151, 233, 93, 156, 114, 161, 233, 165, 169, 195, 173, 177, 247, 183, 189, 185,
/*  45 */ 193, 199, 205, 209, 213, 217, 221, 201, 240, 233, 233, 179, 107, 233, 104, 233, 233, 225, 233, 234, 238, 157,
/*  67 */ 244, 253, 108, 251, 257, 228, 231, 569, 261, 270, 273, 276, 280, 283, 290, 286, 294, 295, 299, 440, 445, 308,
/*  89 */ 544, 369, 406, 406, 338, 265, 359, 366, 440, 443, 307, 551, 536, 312, 402, 406, 323, 523, 516, 406, 406, 406,
/* 111 */ 559, 537, 461, 406, 406, 264, 380, 406, 534, 332, 337, 344, 406, 406, 406, 375, 406, 519, 349, 406, 342, 333,
/* 133 */ 406, 343, 319, 406, 376, 316, 328, 406, 303, 406, 302, 350, 349, 437, 406, 406, 321, 266, 355, 406, 406, 406,
/* 155 */ 518, 403, 406, 406, 406, 548, 387, 395, 400, 404, 338, 561, 510, 418, 389, 396, 401, 405, 425, 511, 420, 412,
/* 177 */ 362, 404, 406, 406, 322, 507, 345, 404, 406, 406, 351, 450, 351, 426, 512, 391, 434, 405, 406, 406, 406, 338,
/* 199 */ 449, 454, 406, 406, 372, 406, 579, 405, 527, 581, 406, 525, 501, 458, 555, 465, 474, 415, 383, 478, 482, 486,
/* 221 */ 490, 494, 498, 576, 320, 324, 531, 406, 408, 406, 468, 503, 406, 406, 406, 406, 323, 541, 406, 406, 406, 470,
/* 243 */ 554, 567, 406, 406, 406, 424, 510, 430, 567, 406, 406, 407, 560, 526, 565, 406, 406, 573, 18, 66, 130, 2, 4,
/* 266 */ 24, 32, 64, 8388480, 2, 32770, 2, 2, 6, 6, 2, 10, 18, 34, 2, 8194, 8194, 8194, 0, 6, 6, 40962, 19498, 20554,
/* 290 */ 2, 34, 34, 32770, 20010, 20554, 20554, 20554, -65534, -65278, 2, 2, 0, 0, 65536, 1048576, 2097152, 128, 8, 8,
/* 310 */ 32, 32, 12582912, 50331648, 67108864, 134217728, 262144, 3145728, 12582912, 16777216, 0, 0, 0, 3, 4, 8, 16,
/* 327 */ 96, 33554432, 134217728, 536870912, 1073741824, 1048576, 2097152, 8388608, 16777216, 33554432, 33554432, 0, 0,
/* 340 */ 0, 2, 2048, 65536, 131072, 1048576, 2097152, 16777216, 536870912, 1048576, 2097152, 0, 0, 0, 16, 8388608,
/* 356 */ 117440512, 134217728, -268435456, 128, 8388352, 8388608, 16777216, 33554432, 67108864, 536870912, 33554432,
/* 367 */ 67108864, 134217728, 268435456, 536870912, -1073741824, 0, 0, 524288, 0, 8, 3072, 65536, 131072, 64, 1792,
/* 382 */ 6144, 8192, 8192, 268443648, 32768, 16384, 98304, 131072, 262144, 524288, 1048576, 536870912, (int) 0x80000000,
/* 395 */ 1572864, 6291456, 8388608, 16777216, 33554432, 33554432, 67108864, 268435456, 536870912, 1073741824,
/* 405 */ (int) 0x80000000, 0, 0, 0, 0, 1, 64, 1048576, 2097152, 4194304, 8388608, 36864, 2101248, 8192, 16384, 32768,
/* 421 */ 65536, 131072, 524288, 2, 16, 64, 256, 512, 1024, 16384, 32768, 131072, 524288, 16384, 131072, 524288,
/* 437 */ 1048576, 0, 1048576, 0, 16, 16, 64, 64, 64, 128, 128, 32768, 16, 256, 512, 2048, 4096, 4096, 131072, 524288,
/* 457 */ (int) 0x80000000, 256, 0, 16384, 16777216, 33554432, 134217728, 1073741824, 0, 32768, 2097152, 0, 64, 0, 0,
/* 472 */ 15, 1008, 4194304, 33554432, 268435456, 2097152, 16777216, 67108864, 268435456, 83894272, 8404992, 10485760,
/* 484 */ 3149824, 16785408, 67117056, 4718592, 46153728, 86507520, 16801792, 83910656, 16801792, 83947520, 86011904,
/* 495 */ 87060480, 87093248, 87355392, 230158336, 4095, 4095, 0, 256, 0, 0, -1, -1, 16, 96, 384, 512, 1024, 2048, 4096,
/* 514 */ 16384, 131072, 1024, 2048, 0, 0, 0, 65536, 131072, 96, 128, 256, 512, 0, 0, 0, 256, 128, 512, 1024, 0, 3072,
/* 536 */ 65536, 131072, 262144, 3145728, 8388608, 96, 512, 1024, 0, 3074, 458752, 267386880, 3, 8, 16, 32, 32, 32,
/* 554 */ 3072, 0, 8192, 0, 0, 1, 2, 16, 32, 64, 256, 2, 32, 64, 512, 0, 0, 6, 2, 1, 32, 64, 0, 8192, 8192, 0, 256, 512,
/* 582 */ 4096, (int) 0x80000000, 0
};

const int RExParser::CASEID[] =
{
/*    0 */ 300, 350, 702, 312, 350, 730, 324, 350, 341, 336, 350, 341, 350, 350, 725, 349, 350, 537, 646, 350, 350, 316,
/*   22 */ 359, 367, 378, 350, 370, 882, 350, 661, 387, 350, 502, 397, 350, 607, 865, 350, 666, 850, 359, 367, 410, 350,
/*   44 */ 435, 420, 350, 440, 420, 350, 440, 397, 350, 607, 397, 350, 607, 397, 350, 607, 430, 350, 458, 865, 350, 666,
/*   66 */ 397, 350, 607, 882, 350, 350, 397, 350, 607, 397, 350, 607, 430, 350, 581, 350, 350, 823, 410, 350, 435, 430,
/*   88 */ 350, 458, 453, 350, 550, 430, 350, 563, 350, 350, 576, 865, 350, 671, 865, 350, 402, 397, 350, 594, 430, 350,
/*  110 */ 445, 430, 350, 633, 350, 350, 684, 865, 350, 666, 397, 350, 594, 430, 350, 633, 350, 350, 469, 697, 350, 304,
/*  132 */ 350, 350, 513, 350, 350, 389, 350, 350, 513, 350, 350, 480, 350, 350, 513, 350, 350, 867, 350, 350, 513, 466,
/*  154 */ 350, 620, 818, 350, 328, 350, 350, 469, 477, 350, 491, 720, 350, 350, 488, 350, 350, 499, 350, 350, 510, 350,
/*  176 */ 350, 521, 350, 350, 532, 350, 350, 545, 350, 350, 558, 350, 350, 571, 350, 350, 589, 350, 350, 602, 350, 350,
/*  198 */ 615, 350, 350, 628, 350, 350, 641, 350, 350, 679, 350, 350, 715, 350, 651, 350, 350, 651, 692, 350, 524, 350,
/*  220 */ 350, 756, 710, 350, 350, 738, 350, 350, 751, 350, 350, 764, 350, 350, 899, 350, 350, 777, 350, 350, 790, 350,
/*  242 */ 350, 803, 350, 350, 831, 350, 350, 844, 350, 350, 858, 350, 350, 350, 350, 904, 350, 350, 914, 919, 350, 884,
/*  264 */ 350, 350, 743, 350, 350, 924, 875, 350, 782, 892, 350, 795, 350, 350, 909, 350, 350, 769, 350, 350, 656, 350,
/*  286 */ 350, 351, 808, 350, 379, 813, 350, 412, 813, 350, 422, 350, 350, 836, 938, 940, 1149, 939, 942, 942, 942,
/*  307 */ 942, 943, 1228, 1227, 942, 934, 936, 977, 935, 942, 942, 942, 942, 987, 991, 995, 999, 1338, 932, 1131, 1184,
/*  328 */ 942, 942, 942, 942, 1360, 1128, 942, 942, 1338, 932, 1061, 1184, 942, 942, 942, 942, 947, 942, 942, 982, 942,
/*  349 */ 1217, 942, 942, 942, 942, 942, 942, 942, 942, 1337, 1003, 1007, 1011, 1015, 1019, 1023, 1027, 1031, 1035,
/*  368 */ 1039, 1043, 942, 942, 942, 942, 942, 1072, 942, 942, 1234, 942, 942, 942, 942, 942, 942, 942, 1348, 1247,
/*  388 */ 942, 942, 942, 942, 942, 942, 942, 1238, 942, 1189, 1190, 942, 1058, 942, 942, 942, 942, 1065, 942, 942,
/*  408 */ 1188, 942, 1078, 942, 942, 942, 942, 942, 942, 942, 1289, 942, 1084, 942, 942, 942, 942, 942, 942, 942, 1359,
/*  429 */ 942, 1349, 1277, 942, 1088, 942, 942, 942, 942, 1076, 942, 942, 942, 942, 1082, 942, 942, 942, 942, 1125,
/*  449 */ 942, 1200, 1135, 942, 1239, 1240, 942, 1171, 942, 942, 942, 942, 1125, 942, 1209, 1135, 942, 1202, 942, 942,
/*  469 */ 942, 942, 942, 942, 942, 1138, 942, 942, 1253, 942, 942, 942, 942, 942, 942, 942, 1140, 942, 942, 1283, 942,
/*  490 */ 942, 942, 942, 942, 942, 942, 1163, 942, 942, 1313, 942, 942, 942, 942, 942, 942, 942, 1178, 942, 942, 1333,
/*  511 */ 942, 942, 942, 942, 942, 942, 942, 1232, 942, 942, 1344, 942, 942, 942, 942, 942, 942, 942, 1303, 942, 942,
/*  532 */ 1355, 942, 942, 942, 942, 942, 942, 942, 1156, 942, 1072, 942, 942, 953, 942, 942, 942, 942, 942, 942, 942,
/*  553 */ 1169, 942, 1241, 1171, 942, 956, 942, 942, 942, 942, 942, 942, 942, 1175, 942, 942, 1135, 942, 959, 942, 942,
/*  574 */ 942, 942, 942, 942, 942, 1182, 942, 942, 942, 942, 1144, 942, 1147, 1135, 942, 962, 942, 942, 942, 942, 942,
/*  595 */ 942, 942, 1194, 942, 942, 1058, 942, 965, 942, 942, 942, 942, 942, 942, 942, 1195, 942, 1196, 1058, 942, 968,
/*  616 */ 942, 942, 942, 942, 942, 942, 942, 1202, 942, 1121, 1251, 942, 971, 942, 942, 942, 942, 942, 942, 942, 1206,
/*  637 */ 942, 942, 1135, 942, 974, 942, 942, 942, 942, 942, 942, 942, 1211, 942, 942, 942, 942, 983, 942, 942, 942,
/*  658 */ 942, 1048, 942, 942, 942, 942, 1052, 942, 942, 942, 942, 1065, 942, 942, 942, 942, 1065, 942, 942, 950, 942,
/*  679 */ 1165, 942, 942, 942, 942, 942, 942, 942, 1215, 942, 942, 942, 1221, 1259, 942, 942, 942, 942, 942, 942, 942,
/*  700 */ 1226, 942, 942, 942, 942, 1150, 942, 942, 941, 942, 942, 1115, 942, 942, 942, 942, 942, 942, 1257, 942, 942,
/*  721 */ 942, 942, 1222, 942, 942, 942, 942, 1156, 942, 942, 942, 942, 978, 942, 942, 937, 942, 942, 1112, 942, 942,
/*  742 */ 942, 942, 942, 942, 1263, 942, 1287, 942, 942, 942, 1109, 942, 942, 942, 942, 942, 942, 1263, 942, 1303, 942,
/*  763 */ 942, 942, 1067, 942, 942, 942, 942, 942, 942, 1263, 942, 1331, 942, 942, 942, 1106, 942, 942, 942, 942, 942,
/*  784 */ 942, 1309, 1305, 1311, 1300, 942, 942, 1103, 942, 942, 942, 942, 942, 942, 1317, 1323, 1319, 1327, 942, 942,
/*  804 */ 1100, 942, 942, 942, 942, 942, 942, 1342, 942, 942, 942, 942, 1353, 942, 942, 942, 942, 1360, 942, 942, 942,
/*  825 */ 942, 1154, 942, 942, 1160, 942, 942, 1097, 942, 942, 942, 942, 942, 942, 1364, 942, 942, 942, 942, 942, 1094,
/*  846 */ 942, 942, 942, 942, 942, 942, 1071, 942, 987, 991, 995, 999, 942, 1091, 942, 942, 942, 942, 942, 942, 932,
/*  867 */ 942, 942, 942, 942, 942, 942, 1245, 942, 1264, 1265, 942, 1300, 942, 942, 942, 942, 1047, 942, 942, 942, 942,
/*  888 */ 942, 942, 1118, 942, 1295, 1296, 942, 1325, 942, 942, 942, 942, 1054, 942, 942, 942, 942, 942, 942, 1269,
/*  908 */ 942, 942, 942, 942, 1271, 942, 942, 942, 942, 1275, 942, 942, 942, 942, 1281, 942, 942, 942, 942, 1294, 942,
/*  929 */ 1293, 942, 942, 0, 24072, 0, 0, 0, 24580, 0, 0, 0, 4, 0, 0, 0, 0, 3090, 0, 13330, 1540, 0, 0, 19992, 0, 0,
/*  955 */ 20242, 0, 0, 20498, 0, 0, 20754, 0, 0, 21010, 0, 0, 21266, 0, 0, 21522, 0, 0, 21778, 0, 0, 22034, 0, 0,
/*  979 */ 24580, 24580, 0, 57348, 0, 0, 0, 3112, 44552, 43528, 45576, 52232, 33288, 33800, 16914, 41992, 34824, 17170,
/*  997 */ 51720, 51208, 53256, 17426, 37896, 42504, 50184, 56328, 49160, 48648, 48136, 35848, 40968, 54280, 44040,
/* 1012 */ 43016, 45064, 41480, 34312, 52744, 55816, 35336, 56840, 40456, 53768, 39432, 54792, 38408, 36360, 14354,
/* 1027 */ 16658, 14610, 49672, 50696, 47112, 39944, 37384, 15122, 15378, 15890, 14866, 55304, 16402, 15634, 16146,
/* 1042 */ 38920, 36872, 47624, 46600, 46088, 4616, 0, 0, 0, 3144, 0, 4104, 0, 0, 0, 30760, 5124, 0, 5124, 0, 0, 25608,
/* 1064 */ 25608, 0, 23560, 0, 0, 0, 31272, 25128, 0, 0, 0, 3592, 0, 59912, 0, 0, 0, 59400, 0, 61960, 0, 0, 0, 61448,
/* 1088 */ 16904, 0, 17928, 0, 0, 27688, 0, 0, 28200, 0, 0, 28712, 0, 0, 29224, 0, 0, 29736, 0, 0, 30248, 0, 0, 31784,
/* 1112 */ 0, 0, 32296, 0, 0, 32808, 0, 0, 57912, 0, 0, 61460, 2580, 9220, 15876, 15364, 0, 0, 61972, 0, 552, 25608,
/* 1134 */ 25608, 15876, 0, 15876, 0, 1064, 0, 0, 3858, 0, 9236, 15876, 15364, 9236, 9236, 0, 0, 4, 4, 0, 0, 20488, 0,
/* 1157 */ 0, 2322, 0, 8466, 0, 8722, 0, 2084, 0, 0, 5650, 0, 6660, 6660, 6660, 0, 6660, 0, 0, 15876, 15364, 0, 2084, 0,
/* 1181 */ 3592, 0, 14344, 0, 0, 2568, 0, 19480, 0, 0, 0, 5124, 0, 5124, 5124, 5124, 5124, 0, 0, 0, 9220, 0, 0, 2580, 0,
/* 1206 */ 9220, 15876, 15364, 9220, 9220, 0, 0, 0, 63492, 0, 14856, 0, 0, 2834, 0, 13348, 0, 0, 0, 5394, 0, 22036, 0,
/* 1229 */ 22036, 0, 0, 0, 25112, 0, 0, 4370, 0, 3602, 0, 0, 0, 6660, 0, 0, 0, 4114, 0, 0, 4626, 0, 0, 62996, 0, 0,
/* 1255 */ 4882, 0, 0, 5906, 0, 0, 6162, 0, 6418, 0, 0, 0, 9748, 0, 0, 27176, 0, 0, 8978, 0, 0, 26664, 0, 0, 17416, 0,
/* 1281 */ 0, 7186, 0, 0, 18962, 0, 0, 2116, 0, 0, 18984, 0, 7698, 7188, 0, 0, 0, 12308, 0, 9748, 0, 9748, 0, 2100, 0,
/* 1306 */ 0, 7954, 0, 9748, 9748, 9748, 9748, 0, 0, 19218, 0, 12308, 12308, 12308, 12308, 0, 10776, 11800, 11288,
/* 1325 */ 12308, 0, 12308, 0, 12308, 8210, 0, 2132, 0, 0, 19474, 0, 10296, 0, 0, 0, 13074, 0, 9746, 0, 0, 19730, 0,
/* 1348 */ 13844, 0, 0, 0, 17928, 0, 10002, 0, 0, 19986, 0, 18472, 0, 0, 0, 23572, 10258, 0, 0, 16440
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
/* 290 */ 5385, 649, 0, 5897, 6025, 30468, 6153, 6281, 6409, 0, 524, 905, 0, 265, 0, 0, 4617, 0, 521, 0, 0, 0, 3465, 0,
/* 314 */ 5769, 0, 0, 6793, 649, 0, 12300, 905, 0, 2569, 0, 0, 11028, 11524, 1033, 0, 0, 0, 3612, 1289, 6921, 0, 0,
/* 337 */ 7049, 0, 13060, 0, 0, 0, 3868, 0, 8841, 0, 0, 8204, 0, 0, 9225, 0, 0, 8969, 9097, 9353, 0, 0, 0, 4108, 13068,
/* 362 */ 0, 0, 0, 12041, 29444, 0, 0, 0, 12425, 11273, 0, 0, 0, 12553, 3337, 11529, 0, 0, 11145, 29188, 0, 11657, 0, 0,
/* 386 */ 12169, 12297, 11785, 0, 0, 0, 29204, 32028, 5513, 0, 11268, 11913, 0, 0, 0, 30228, 0, 4876, 0, 0, 2844, 0,
/* 408 */ 11401, 10756, 5513, 0, 11268, 0, 4745, 0, 0, 3721, 0, 0, 12681, 0, 6420, 0, 0, 0, 31252, 10516, 5513, 0,
/* 430 */ 11268, 0, 5257, 0, 0, 4372, 0, 0, 3084, 0, 11401
};

const int RExParser::REDUCTION[] =
{
/*   0 */ 39, 0, 0, 1, 1, -1, 40, 2, 2, -1, 3, 3, 4, -1, 5, 4, 6, 5, 7, 6, 41, 7, 8, 8, 8, 8, 42, 9, 9, -1, 10, 8, 10,
/*  33 */ 8, 11, 10, 11, -1, 12, -1, 13, -1, 13, 14, 13, 13, 13, 12, 13, 11, 14, 17, 14, 16, 14, 15, 15, 18, 16, 19, 44,
/*  61 */ 24, 43, 22, 17, -1, 17, 23, 17, 21, 17, 20, 18, 27, 18, 26, 18, 27, 18, 26, 18, 25, 19, 28, 19, 28, 20, -1,
/*  88 */ 21, 29, 22, 30, 23, 32, 23, 31, 24, -1, 25, -1, 26, -1, 27, -1, 28, 91, 28, 90, 28, 66, 28, 65, 28, 64, 28,
/* 115 */ 63, 28, 62, 28, 61, 28, 60, 28, 59, 28, 58, 28, 57, 28, 56, 28, 89, 28, 88, 28, 87, 28, 86, 28, 85, 28, 84,
/* 142 */ 28, 83, 28, 82, 28, 81, 28, 80, 28, 79, 28, 78, 28, 77, 28, 76, 28, 75, 28, 74, 28, 73, 28, 72, 28, 71, 28,
/* 169 */ 70, 28, 69, 28, 68, 28, 67, 28, 55, 28, 54, 28, 53, 28, 52, 28, 51, 28, 50, 28, 49, 28, 48, 28, 47, 28, 46,
/* 196 */ 28, 45, 28, 44, 28, 43, 28, 42, 28, 41, 28, 40, 28, 39, 28, 38, 28, 37, 28, 36, 28, 35, 28, 34, 28, 33, 28,
/* 223 */ -1, 45, 92, 29, -1, 30, -1, 31, 93, 32, 95, 32, 94, 33, 96, 34, 97, 35, 99, 35, 98, 36, 100, 37, 101, 46, 102,
/* 250 */ 38, 103
};

const char *RExParser::TOKEN[] =
{
  "%ERROR",
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
  "'CODEPOINTS'",
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
  "'NOCODEPOINTS'",
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

#endif

// End
