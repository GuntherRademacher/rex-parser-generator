// This file was generated on Sun Jan 26, 2025 19:55 (UTC+01) by REx v6.1 which is Copyright (c) 1979-2025 by Gunther Rademacher <grd@gmx.net>
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
    int i0 = t * 376 + s - 1;
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
/*    0 */ 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300,
/*   18 */ 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 1920, 1938, 1922, 1954,
/*   36 */ 4375, 1988, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300,
/*   54 */ 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2010, 2030, 2014, 2300, 2300, 2300, 2300, 2300,
/*   72 */ 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300,
/*   90 */ 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2046, 4375, 1988, 2300, 2300, 2300, 2300, 2300, 2300,
/*  108 */ 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300,
/*  126 */ 2300, 2300, 5029, 4720, 4710, 2046, 4375, 1988, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300,
/*  144 */ 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 3522, 4074,
/*  162 */ 3914, 2082, 4375, 2116, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300,
/*  180 */ 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2147, 2154, 2170, 2046, 4375, 1988,
/*  198 */ 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300,
/*  216 */ 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 4282, 2046, 4375, 1988, 2300, 2300, 2300, 2300,
/*  234 */ 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300,
/*  252 */ 2300, 2300, 2300, 2300, 2300, 2201, 3209, 2046, 4375, 1988, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300,
/*  270 */ 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300,
/*  288 */ 3730, 4203, 4234, 2219, 4375, 2253, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300,
/*  306 */ 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2299, 5464, 2289, 2046,
/*  324 */ 4375, 1988, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300,
/*  342 */ 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 4045, 5357, 5424, 2046, 4375, 1988, 2300, 2300,
/*  360 */ 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300,
/*  378 */ 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 3529, 2046, 4375, 1988, 2300, 2300, 2300, 2300, 2300, 2300,
/*  396 */ 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300,
/*  414 */ 2300, 2300, 2300, 2300, 3737, 2046, 4375, 1988, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300,
/*  432 */ 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2760,
/*  450 */ 2317, 2046, 4375, 1988, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300,
/*  468 */ 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 4156, 2335, 4375, 1988,
/*  486 */ 2300, 2300, 2300, 2300, 2300, 2986, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300,
/*  504 */ 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2301, 2363, 2390, 4375, 1988, 2300, 2300, 2300, 2300,
/*  522 */ 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300,
/*  540 */ 2300, 2300, 2300, 2300, 2300, 5197, 3357, 2046, 4375, 1988, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300,
/*  558 */ 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300,
/*  576 */ 3084, 2437, 2491, 2523, 4375, 2551, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300,
/*  594 */ 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2503, 2587, 2573, 2523,
/*  612 */ 4375, 2551, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300,
/*  630 */ 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2603, 2606, 2662, 2046, 4375, 1988, 2300, 2300,
/*  648 */ 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300,
/*  666 */ 2300, 2300, 2300, 2300, 2300, 2300, 3495, 2632, 2622, 2046, 4375, 1988, 2300, 2300, 2300, 2300, 2300, 2300,
/*  684 */ 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300,
/*  702 */ 2300, 2300, 2129, 2131, 2300, 2046, 4375, 1988, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300,
/*  720 */ 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2648, 5396,
/*  738 */ 2679, 2697, 4375, 1988, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300,
/*  756 */ 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 3669, 5128, 2731, 2748, 4375, 2785,
/*  774 */ 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300,
/*  792 */ 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 5296, 4855, 2807, 2046, 4375, 1988, 2300, 2300, 2300, 2300,
/*  810 */ 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300,
/*  828 */ 2300, 2300, 2300, 2300, 2300, 2928, 2841, 2887, 2903, 2919, 2403, 2946, 2973, 3007, 2300, 2300, 3026, 2300,
/*  846 */ 3326, 2300, 2300, 2825, 5329, 2300, 4174, 2300, 4322, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300,
/*  864 */ 2300, 2928, 3042, 3069, 4375, 2919, 3104, 2930, 2300, 3272, 4148, 3106, 2300, 2300, 2300, 3122, 2300, 2300,
/*  882 */ 2300, 3698, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2928, 3139, 2335,
/*  900 */ 3088, 2919, 2300, 3173, 2300, 2300, 3278, 2300, 2300, 2300, 2094, 3194, 2300, 2300, 2300, 2300, 2300, 2300,
/*  918 */ 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2928, 3236, 2335, 4375, 2919, 2300, 3294,
/*  936 */ 2300, 2300, 2300, 2300, 2300, 4928, 2300, 2300, 2300, 2300, 3577, 2300, 2300, 2300, 2300, 2300, 2300, 2300,
/*  954 */ 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2928, 3313, 2335, 3396, 2919, 2300, 4415, 3347, 3373, 4300, 3412,
/*  972 */ 4421, 2058, 3438, 3478, 3451, 2268, 3630, 4785, 3511, 3545, 3840, 3569, 2300, 2300, 2300, 2300, 2300, 2300,
/*  990 */ 2300, 2300, 2300, 2928, 3593, 2335, 3646, 2919, 2300, 4530, 2300, 4803, 3662, 2300, 2300, 2300, 3123, 2300,
/* 1008 */ 2231, 2300, 2300, 4440, 4848, 4957, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2928,
/* 1026 */ 3685, 2335, 4375, 3719, 2300, 3753, 2300, 2300, 2300, 3772, 2300, 2300, 2300, 3386, 2421, 2300, 2300, 2300,
/* 1044 */ 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2928, 3791, 2335, 4375, 3719,
/* 1062 */ 3487, 2300, 2416, 2300, 3864, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300,
/* 1080 */ 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2928, 3042, 2335, 2769, 3719, 2300, 2300, 4794, 2854,
/* 1098 */ 5323, 3882, 3756, 4627, 3899, 2300, 3941, 2300, 3606, 2535, 5442, 2374, 3960, 3983, 2300, 2300, 2300, 2300,
/* 1116 */ 2300, 2300, 2300, 2300, 2300, 2928, 4001, 2335, 4375, 3719, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300,
/* 1134 */ 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300,
/* 1152 */ 2300, 2928, 3042, 2335, 4375, 3719, 2300, 2663, 2300, 2732, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300,
/* 1170 */ 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2928, 4061, 4090,
/* 1188 */ 4375, 3719, 3331, 4106, 4492, 5170, 4139, 2300, 3553, 4172, 2300, 4962, 2300, 2300, 4358, 2300, 3813, 2300,
/* 1206 */ 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2928, 4190, 4219, 2507, 3719, 2865, 4268,
/* 1224 */ 2300, 4316, 2300, 2100, 4463, 2300, 2273, 2300, 3985, 4338, 2300, 4355, 2300, 2300, 2300, 4374, 2300, 2300,
/* 1242 */ 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2928, 4391, 2335, 4375, 3719, 2300, 4437, 2300, 2300, 2300, 4559,
/* 1260 */ 4293, 4456, 2300, 2957, 4479, 2300, 4508, 2300, 3157, 2300, 4526, 1968, 2300, 2300, 2300, 2300, 2300, 2300,
/* 1278 */ 2300, 2300, 2300, 2928, 4546, 4579, 5075, 3719, 2300, 2300, 3297, 2300, 2300, 2300, 3866, 3249, 2300, 2300,
/* 1296 */ 2300, 4595, 2300, 2300, 2300, 4252, 4510, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2928,
/* 1314 */ 4614, 4643, 4375, 4659, 4675, 2300, 4698, 5278, 2300, 2300, 4736, 2300, 4753, 3944, 2300, 3822, 2300, 2871,
/* 1332 */ 3804, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2928, 3042, 2335, 2203, 3719,
/* 1350 */ 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300,
/* 1368 */ 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2928, 4772, 2335, 4819, 3719, 5177, 3703, 4116, 2066,
/* 1386 */ 2300, 3925, 2300, 4682, 2466, 2300, 2475, 3053, 3883, 5215, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300,
/* 1404 */ 2300, 2300, 2300, 2300, 2300, 2928, 4835, 4871, 2319, 3719, 4404, 4887, 2791, 2300, 2300, 3618, 5390, 3848,
/* 1422 */ 2237, 2300, 3220, 2347, 4906, 5012, 4926, 2715, 1994, 2818, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300,
/* 1440 */ 2300, 2928, 4944, 2335, 4563, 4978, 2300, 5005, 4989, 2300, 5251, 2300, 2300, 5028, 4890, 2452, 2300, 5045,
/* 1458 */ 5233, 5435, 4756, 5061, 5111, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2928, 3042, 2335,
/* 1476 */ 5091, 3719, 2300, 2300, 5107, 2300, 2300, 2300, 3178, 3775, 2300, 2300, 2300, 2300, 3831, 5127, 2300, 2300,
/* 1494 */ 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2928, 3042, 2335, 4375, 3719, 2681, 2300,
/* 1512 */ 2300, 2300, 2300, 2300, 2300, 4910, 2300, 2300, 2300, 2300, 4245, 2300, 2300, 2300, 4598, 2709, 2300, 2300,
/* 1530 */ 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2928, 3042, 2335, 4375, 3719, 2300, 2300, 2300, 2300, 2300, 2300,
/* 1548 */ 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300,
/* 1566 */ 2300, 2300, 2300, 2928, 5144, 2335, 4375, 3719, 3010, 4036, 2300, 2300, 2300, 2300, 3152, 2300, 2300, 3261,
/* 1584 */ 2300, 2300, 2300, 2300, 2300, 2300, 5160, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2928,
/* 1602 */ 3042, 2335, 2557, 3719, 2300, 2300, 2300, 1972, 2300, 2300, 2300, 2300, 2300, 4737, 2300, 2300, 5193, 5213,
/* 1620 */ 2300, 5231, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2928, 3042, 2335, 4375, 3719,
/* 1638 */ 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 4123, 2300, 2300, 4339, 2300, 2300, 2300, 2300,
/* 1656 */ 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 5249, 3462, 5267, 2046, 4375, 1988, 2300, 2300, 2300, 2300,
/* 1674 */ 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300,
/* 1692 */ 2300, 2300, 2300, 2300, 5363, 2300, 5294, 2046, 4375, 1988, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300,
/* 1710 */ 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300,
/* 1728 */ 2300, 3422, 5312, 2046, 4375, 1988, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300,
/* 1746 */ 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 5345,
/* 1764 */ 4375, 5379, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300,
/* 1782 */ 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2183, 2185, 3967, 2046, 4375, 1988, 2300, 2300,
/* 1800 */ 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300,
/* 1818 */ 2300, 2300, 2300, 2300, 2300, 2300, 2991, 4027, 2300, 5412, 4375, 5458, 2300, 2300, 2300, 2300, 2300, 2300,
/* 1836 */ 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300,
/* 1854 */ 2300, 2300, 2300, 2300, 2300, 2335, 4375, 1988, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300,
/* 1872 */ 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300,
/* 1890 */ 4014, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300,
/* 1908 */ 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 2300, 0, 0, 1070, 1070, 1070, 1070, 1070,
/* 1927 */ 1070, 1070, 1070, 1070, 1070, 1070, 1070, 1070, 1070, 1104, 0, 1070, 1070, 1070, 1070, 1070, 1070, 1070,
/* 1945 */ 1070, 1070, 0, 1070, 1070, 1070, 1070, 1070, 1070, 0, 82, 83, 84, 86, 54, 55, 0, 0, 0, 92, 94, 0, 1104, 0, 0,
/* 1970 */ 0, 375, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 202, 0, 0, 0, 0, 82, 83, 84, 0, 86, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/* 2004 */ 0, 8704, 0, 0, 0, 20992, 0, 0, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024,
/* 2025 */ 1024, 4608, 0, 0, 0, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 0, 1024, 1024, 1024, 1024, 1024,
/* 2045 */ 1024, 0, 82, 83, 84, 86, 54, 55, 0, 0, 0, 92, 94, 0, 0, 0, 0, 0, 253, 0, 35840, 0, 0, 0, 0, 0, 0, 0, 0, 196,
/* 2075 */ 0, 0, 0, 0, 203, 0, 0, 0, 82, 83, 85, 86, 4184, 55, 0, 0, 0, 93, 94, 0, 0, 0, 0, 0, 265, 0, 0, 0, 0, 0, 0, 0,
/* 2107 */ 0, 0, 0, 229, 0, 0, 231, 0, 0, 0, 82, 83, 3669, 84, 86, 0, 54, 0, 0, 0, 3072, 92, 0, 0, 0, 0, 50, 0, 0, 0, 0,
/* 2138 */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1071, 1071, 1071, 1071, 1071, 1071, 1071, 1071, 1071, 1071, 1071, 1071,
/* 2161 */ 1071, 1071, 0, 1071, 1071, 1071, 1071, 1071, 1071, 1071, 1071, 1086, 1071, 1086, 1071, 1071, 1071, 1071,
/* 2179 */ 1071, 1071, 1071, 70191, 0, 0, 0, 0, 51, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 57, 0, 0, 0, 0, 0, 0, 0,
/* 2210 */ 0, 0, 0, 0, 0, 0, 0, 131, 1104, 0, 82, 83, 84, 87, 54, 4185, 0, 0, 0, 92, 95, 0, 0, 0, 0, 0, 291, 0, 0, 0, 0,
/* 2241 */ 0, 0, 0, 0, 0, 0, 270, 0, 0, 0, 0, 0, 0, 82, 83, 84, 0, 3671, 86, 0, 55, 0, 0, 0, 0, 3072, 94, 0, 0, 0,
/* 2271 */ 26624, 28160, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 271, 0, 0, 0, 0, 39424, 0, 39424, 39424, 39424, 39424, 39424,
/* 2296 */ 39424, 39424, 39424, 39424, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 61, 0, 7168, 0, 0, 0, 0, 0, 0, 0,
/* 2326 */ 0, 0, 0, 0, 0, 0, 0, 132, 1104, 0, 82, 83, 84, 86, 54, 55, 0, 0, 2106, 92, 94, 0, 0, 0, 0, 0, 303, 0, 305,
/* 2355 */ 33792, 0, 0, 0, 0, 6144, 0, 0, 0, 61, 7680, 7680, 7680, 7680, 7680, 7680, 7680, 7680, 7680, 0, 0, 0, 0, 0, 0,
/* 2380 */ 354, 0, 0, 0, 0, 0, 0, 0, 360, 361, 0, 82, 83, 84, 86, 54, 55, 0, 0, 2106, 92, 94, 41984, 0, 0, 0, 0, 139, 0,
/* 2409 */ 0, 0, 14336, 0, 0, 0, 145, 0, 0, 0, 0, 176, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 296, 0, 0, 0, 0, 0, 38960,
/* 2439 */ 38960, 38960, 38960, 0, 0, 0, 0, 38960, 0, 0, 0, 38960, 38960, 0, 0, 0, 27648, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/* 2465 */ 284, 0, 0, 0, 15360, 0, 0, 0, 267, 0, 0, 0, 0, 0, 0, 0, 0, 16896, 293, 0, 0, 0, 0, 0, 0, 23552, 0, 0, 38960,
/* 2494 */ 38960, 38960, 38960, 38960, 38960, 38960, 38960, 38960, 0, 0, 0, 0, 38961, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/* 2518 */ 0, 123, 0, 0, 1104, 38961, 82, 83, 84, 86, 54, 55, 0, 0, 2106, 92, 94, 0, 0, 0, 0, 0, 329, 0, 331, 0, 0, 0,
/* 2546 */ 335, 336, 0, 0, 0, 38993, 82, 83, 84, 0, 86, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 119, 0, 126, 130, 0, 1104, 0, 0,
/* 2575 */ 38961, 38961, 38961, 38961, 38961, 38961, 38961, 38961, 38961, 0, 0, 0, 0, 38961, 38961, 38961, 38961, 0, 0,
/* 2594 */ 0, 0, 38961, 0, 0, 0, 38961, 38961, 0, 0, 0, 1536, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1536, 1536, 0, 0, 0, 0, 0,
/* 2623 */ 43008, 0, 0, 0, 0, 43008, 43008, 43008, 43008, 43008, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 43008, 43008, 0, 0, 0, 0,
/* 2649 */ 0, 1536, 0, 0, 0, 0, 0, 0, 56, 0, 0, 0, 1536, 1536, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 170, 1536,
/* 2680 */ 56, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 147, 0, 0, 82, 83, 84, 86, 54, 55, 8192, 0, 0, 92, 94, 0, 0, 0,
/* 2712 */ 0, 0, 376, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9216, 357, 0, 0, 0, 0, 43520, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/* 2745 */ 0, 0, 205, 0, 0, 83, 84, 86, 54, 55, 0, 0, 0, 92, 94, 0, 0, 0, 0, 0, 7168, 7168, 7168, 7168, 0, 0, 0, 0, 0,
/* 2774 */ 0, 0, 113, 0, 0, 0, 0, 0, 0, 0, 1104, 0, 2560, 83, 84, 0, 86, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 182, 0, 0, 0, 0,
/* 2806 */ 0, 44032, 0, 0, 0, 0, 0, 0, 0, 0, 0, 44032, 0, 0, 0, 0, 0, 0, 20480, 0, 0, 0, 0, 0, 0, 0, 0, 0, 307, 0, 309,
/* 2837 */ 0, 0, 311, 0, 0, 0, 2106, 2106, 2106, 2106, 2106, 2106, 2106, 2106, 2106, 63, 63, 0, 0, 0, 0, 190, 0, 0, 0,
/* 2862 */ 0, 198, 199, 0, 0, 0, 0, 0, 140, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 334, 0, 0, 0, 0, 0, 0, 82, 83, 84, 86, 54, 55,
/* 2894 */ 0, 0, 2106, 92, 94, 0, 0, 0, 100, 0, 0, 107, 0, 110, 111, 0, 0, 0, 0, 117, 0, 0, 127, 0, 1104, 38993, 82, 83,
/* 2922 */ 84, 0, 86, 0, 0, 0, 0, 2106, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 169, 0, 0, 19968, 150, 0, 0, 0, 0, 0,
/* 2954 */ 163, 0, 165, 0, 0, 0, 0, 0, 0, 29184, 0, 0, 0, 0, 0, 282, 0, 0, 0, 171, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 184,
/* 2986 */ 0, 0, 0, 0, 224, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 46592, 0, 0, 0, 0, 0, 18108, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/* 3019 */ 0, 0, 0, 0, 146, 0, 148, 0, 235, 22528, 236, 0, 0, 0, 25088, 0, 0, 242, 0, 245, 0, 0, 30208, 0, 0, 2106,
/* 3045 */ 2106, 2106, 2106, 2106, 2106, 2106, 2106, 2106, 0, 0, 0, 0, 0, 0, 31232, 0, 0, 0, 308, 0, 310, 0, 0, 0, 0,
/* 3070 */ 82, 83, 84, 86, 54, 55, 0, 0, 2106, 92, 94, 0, 0, 97, 0, 0, 0, 38960, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/* 3100 */ 121, 0, 0, 1104, 135, 136, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 232, 233, 275, 0, 0, 0, 0, 0, 0, 0, 0,
/* 3131 */ 0, 0, 0, 0, 0, 0, 0, 274, 0, 0, 2106, 2106, 2106, 2106, 2106, 2106, 2106, 2106, 2106, 10304, 10304, 0, 0, 0,
/* 3155 */ 0, 237, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 348, 0, 0, 0, 0, 0, 0, 151, 0, 160, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/* 3189 */ 244, 0, 0, 0, 0, 0, 276, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 285, 0, 0, 57, 57, 57, 57, 57, 57, 57, 57, 57,
/* 3220 */ 0, 0, 0, 0, 0, 0, 292, 0, 0, 0, 0, 0, 0, 298, 0, 0, 0, 0, 2106, 2106, 2106, 2106, 2106, 2106, 2106, 2106,
/* 3246 */ 2106, 65, 65, 0, 0, 0, 0, 252, 0, 0, 0, 0, 0, 0, 257, 0, 0, 0, 0, 0, 28672, 0, 0, 0, 0, 33280, 0, 0, 0, 0, 0,
/* 3277 */ 191, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 216, 0, 0, 0, 0, 0, 0, 0, 152, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 185,
/* 3311 */ 0, 0, 0, 0, 2106, 2106, 2106, 2106, 2106, 2106, 2106, 2106, 2106, 66, 66, 0, 0, 0, 0, 264, 0, 0, 0, 0, 0, 0,
/* 3337 */ 0, 0, 0, 0, 0, 144, 0, 0, 0, 0, 172, 0, 0, 0, 0, 0, 0, 0, 180, 181, 0, 0, 0, 0, 0, 0, 0, 42496, 42496, 42496,
/* 3367 */ 42496, 0, 0, 0, 0, 0, 0, 17408, 0, 189, 0, 0, 0, 0, 0, 197, 0, 0, 201, 0, 0, 0, 0, 277, 0, 0, 0, 0, 280, 0,
/* 3397 */ 0, 0, 0, 0, 0, 112, 0, 0, 0, 0, 120, 122, 0, 0, 1104, 0, 221, 0, 0, 0, 0, 0, 0, 0, 228, 0, 0, 0, 0, 0, 0, 0,
/* 3429 */ 45568, 0, 45568, 0, 0, 0, 0, 45568, 0, 0, 263, 0, 0, 0, 0, 0, 0, 0, 269, 0, 0, 272, 0, 0, 0, 0, 290, 0, 0, 0,
/* 3459 */ 0, 0, 295, 0, 0, 0, 0, 0, 0, 44544, 0, 0, 44544, 0, 0, 0, 44544, 0, 0, 0, 0, 27136, 0, 0, 0, 0, 278, 279, 0,
/* 3488 */ 0, 0, 0, 0, 0, 0, 141, 0, 0, 0, 0, 0, 0, 0, 0, 43008, 0, 0, 0, 0, 43008, 0, 0, 0, 0, 340, 0, 0, 34304, 0, 0,
/* 3519 */ 0, 0, 347, 0, 0, 0, 0, 0, 52, 54, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 40448, 0, 0, 0, 0, 0, 0, 24576, 0, 0, 0,
/* 3550 */ 32768, 0, 355, 0, 0, 0, 0, 0, 0, 0, 0, 240, 0, 0, 0, 0, 0, 0, 0, 0, 0, 11264, 0, 35328, 0, 0, 10752, 0, 0, 0,
/* 3580 */ 0, 0, 0, 0, 0, 21504, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2106, 2106, 2106, 2106, 2106, 2106, 2106, 2106, 2106, 67,
/* 3605 */ 67, 0, 0, 0, 0, 315, 0, 0, 0, 0, 318, 0, 320, 0, 0, 0, 0, 0, 12001, 0, 0, 0, 0, 0, 230, 0, 0, 0, 0, 0, 19456,
/* 3636 */ 0, 0, 0, 0, 0, 0, 321, 0, 0, 0, 105, 0, 0, 0, 0, 0, 0, 0, 114, 0, 0, 0, 0, 0, 0, 1104, 206, 0, 0, 209, 0, 0,
/* 3668 */ 212, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 43520, 0, 0, 0, 0, 0, 0, 0, 2106, 2106, 2106, 2106, 2106, 2106, 2106,
/* 3694 */ 2106, 2106, 68, 68, 0, 0, 0, 0, 328, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 166, 0, 0, 0, 0, 0, 82, 83, 84, 0, 86,
/* 3725 */ 0, 0, 0, 0, 2106, 0, 0, 0, 0, 0, 53, 55, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 40960, 0, 0, 0, 0, 0, 0, 0, 153, 0, 0,
/* 3758 */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 246, 0, 0, 0, 0, 222, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 259, 0, 0, 0,
/* 3792 */ 0, 2106, 2106, 2106, 2106, 2106, 2106, 2106, 2106, 2106, 69, 69, 0, 0, 0, 0, 342, 0, 0, 0, 345, 0, 0, 0, 0,
/* 3817 */ 0, 0, 0, 344, 0, 0, 0, 0, 0, 0, 0, 0, 304, 0, 0, 0, 0, 0, 0, 0, 0, 317, 0, 0, 0, 0, 0, 0, 0, 0, 368, 0, 0, 0,
/* 3851 */ 0, 0, 0, 0, 0, 255, 0, 0, 0, 0, 0, 0, 261, 0, 207, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 247, 0, 220, 0,
/* 3884 */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 323, 262, 0, 0, 0, 0, 0, 266, 0, 268, 0, 0, 0, 0, 0, 273, 0, 0, 59,
/* 3917 */ 52, 59, 52, 52, 52, 52, 52, 52, 0, 0, 0, 0, 0, 0, 226, 227, 14848, 0, 0, 0, 18944, 0, 0, 0, 0, 287, 288, 0,
/* 3945 */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 283, 0, 0, 362, 0, 0, 0, 365, 366, 367, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/* 3977 */ 46080, 0, 0, 0, 0, 0, 0, 374, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 299, 0, 0, 0, 2106, 2106, 2106, 2106,
/* 4007 */ 2106, 2106, 2106, 2106, 2106, 70, 70, 0, 0, 0, 0, 5120, 0, 0, 0, 0, 0, 0, 0, 70144, 0, 0, 0, 0, 46592, 0, 0,
/* 4034 */ 0, 46592, 0, 0, 0, 0, 0, 0, 0, 29696, 0, 0, 0, 0, 0, 0, 0, 0, 39936, 0, 0, 0, 0, 0, 0, 0, 39936, 0, 0, 2106,
/* 4064 */ 2106, 2106, 2106, 2106, 2106, 2106, 2106, 2106, 71, 71, 0, 0, 0, 59, 0, 0, 0, 0, 0, 0, 0, 0, 0, 59, 59, 0, 0,
/* 4091 */ 82, 83, 84, 86, 54, 55, 0, 0, 2106, 92, 94, 0, 0, 0, 101, 0, 0, 154, 0, 0, 0, 0, 0, 0, 164, 0, 0, 0, 0, 0, 0,
/* 4122 */ 178, 0, 0, 0, 0, 0, 0, 0, 0, 0, 294, 0, 0, 0, 0, 0, 0, 0, 0, 208, 0, 210, 0, 0, 0, 214, 0, 0, 0, 0, 0, 0, 0,
/* 4155 */ 213, 0, 0, 0, 0, 0, 0, 0, 0, 0, 41472, 41472, 0, 0, 0, 0, 0, 0, 249, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/* 4187 */ 0, 350, 0, 0, 0, 2106, 2106, 2106, 2106, 2106, 2106, 2106, 2106, 2106, 72, 72, 0, 0, 0, 60, 0, 0, 0, 0, 0, 0,
/* 4213 */ 0, 0, 0, 60, 60, 0, 0, 82, 83, 84, 86, 54, 55, 0, 0, 2106, 92, 94, 0, 0, 98, 0, 0, 60, 53, 60, 53, 53, 53,
/* 4242 */ 53, 53, 53, 0, 0, 0, 0, 0, 0, 316, 0, 0, 0, 0, 0, 0, 0, 0, 0, 356, 0, 0, 0, 0, 0, 0, 0, 0, 155, 0, 0, 0, 0,
/* 4275 */ 0, 0, 0, 0, 0, 0, 168, 0, 0, 0, 6656, 0, 6656, 6656, 6656, 6656, 6656, 6656, 0, 0, 0, 0, 0, 0, 239, 0, 0, 0,
/* 4303 */ 0, 0, 0, 0, 0, 0, 215, 0, 36352, 217, 218, 0, 219, 187, 0, 0, 0, 0, 192, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 369,
/* 4333 */ 0, 0, 0, 0, 0, 300, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 338, 0, 0, 326, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/* 4367 */ 0, 0, 0, 0, 322, 0, 0, 373, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1104, 0, 0, 2106, 2106, 2106, 2106,
/* 4397 */ 2106, 2106, 2106, 2106, 2106, 73, 73, 0, 0, 0, 138, 0, 0, 0, 0, 0, 0, 143, 0, 0, 0, 0, 0, 161, 0, 0, 0, 0, 0,
/* 4426 */ 0, 0, 0, 0, 0, 243, 0, 0, 0, 0, 0, 149, 0, 156, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 337, 0, 0, 0, 0, 250,
/* 4459 */ 0, 0, 0, 254, 0, 0, 0, 0, 0, 0, 0, 0, 0, 241, 0, 0, 0, 0, 0, 0, 5918, 0, 0, 289, 0, 0, 0, 0, 0, 0, 0, 0, 297,
/* 4492 */ 0, 0, 0, 175, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15872, 0, 314, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 372,
/* 4525 */ 0, 0, 0, 363, 364, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 167, 0, 0, 0, 0, 0, 2106, 2106, 2106, 2106, 2106,
/* 4553 */ 2106, 2106, 2106, 2106, 74, 74, 0, 0, 0, 223, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 124, 0, 0, 1104, 0, 82, 83,
/* 4582 */ 84, 86, 54, 55, 0, 90, 2106, 92, 94, 0, 96, 0, 102, 0, 0, 302, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 371, 0,
/* 4613 */ 0, 0, 0, 2106, 2106, 2106, 2106, 2106, 2106, 2106, 2106, 2106, 75, 75, 0, 0, 0, 251, 0, 0, 0, 0, 0, 0, 0, 0,
/* 4639 */ 0, 0, 0, 260, 0, 82, 83, 84, 86, 54, 55, 0, 0, 2106, 92, 94, 0, 0, 99, 103, 0, 82, 83, 84, 0, 86, 0, 0, 0, 0,
/* 4669 */ 2106, 0, 0, 0, 0, 134, 0, 0, 137, 0, 0, 0, 13312, 0, 0, 0, 0, 0, 0, 0, 0, 0, 256, 2048, 0, 0, 0, 0, 0, 0,
/* 4699 */ 173, 0, 0, 0, 0, 0, 0, 0, 0, 0, 183, 0, 0, 0, 0, 0, 38400, 38400, 38400, 38400, 38400, 38400, 0, 0, 0, 0, 0,
/* 4726 */ 0, 0, 0, 0, 0, 0, 38400, 0, 0, 0, 234, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 37376, 0, 0, 13824, 0, 0,
/* 4758 */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 18432, 0, 351, 0, 0, 2106, 2106, 2106, 2106, 2106, 2106, 2106, 2106, 2106,
/* 4783 */ 76, 76, 0, 0, 0, 327, 0, 0, 0, 0, 332, 0, 0, 0, 0, 0, 0, 0, 179, 0, 0, 0, 0, 0, 0, 0, 0, 195, 0, 0, 0, 200,
/* 4815 */ 0, 0, 0, 0, 0, 106, 0, 109, 0, 0, 0, 0, 0, 0, 118, 0, 0, 129, 0, 1104, 0, 0, 2106, 2106, 2106, 2106, 2106,
/* 4842 */ 2106, 2106, 2106, 2106, 77, 77, 0, 0, 0, 341, 0, 0, 343, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 44032, 44032, 0, 0, 0,
/* 4870 */ 0, 0, 82, 83, 84, 86, 54, 55, 0, 0, 2106, 92, 94, 0, 0, 0, 104, 0, 0, 157, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/* 4901 */ 0, 0, 24064, 0, 0, 313, 0, 0, 12800, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 258, 0, 0, 0, 339, 26112, 0, 0, 0,
/* 4931 */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9728, 0, 0, 0, 2106, 2106, 2106, 2106, 2106, 2106, 2106, 2106, 2106, 78, 78,
/* 4957 */ 0, 0, 0, 352, 353, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 281, 0, 0, 0, 0, 0, 82, 83, 84, 0, 86, 0, 0, 0, 133,
/* 4988 */ 2106, 0, 0, 0, 0, 0, 177, 0, 0, 0, 0, 0, 0, 0, 0, 186, 0, 0, 0, 158, 159, 0, 0, 162, 0, 0, 0, 0, 0, 0, 0, 0,
/* 5020 */ 0, 333, 0, 0, 0, 0, 0, 0, 248, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 38400, 0, 301, 0, 0, 0, 0, 0,
/* 5052 */ 306, 0, 0, 0, 0, 0, 0, 0, 312, 0, 0, 25600, 0, 0, 0, 0, 0, 36864, 0, 0, 0, 358, 359, 0, 0, 0, 16384, 0, 0, 0,
/* 5082 */ 0, 115, 0, 0, 0, 0, 128, 0, 1104, 0, 0, 108, 0, 0, 0, 0, 0, 0, 116, 0, 0, 125, 0, 0, 1104, 0, 0, 174, 0, 0,
/* 5112 */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 370, 0, 0, 0, 324, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 43520, 0, 0,
/* 5146 */ 2106, 2106, 2106, 2106, 2106, 2106, 2106, 2106, 2106, 79, 79, 0, 0, 81, 0, 34816, 0, 0, 0, 0, 0, 0, 31744,
/* 5169 */ 32256, 0, 0, 0, 0, 0, 0, 194, 0, 0, 0, 0, 0, 0, 0, 0, 0, 142, 0, 0, 0, 0, 0, 0, 0, 0, 12288, 0, 0, 0, 0, 0,
/* 5201 */ 0, 0, 0, 0, 0, 0, 0, 0, 42496, 0, 0, 0, 0, 325, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 23040, 0, 22016, 0,
/* 5233 */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 30720, 0, 0, 44544, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/* 5265 */ 37888, 0, 0, 44544, 44544, 44544, 44544, 44544, 44544, 44544, 44544, 44544, 44544, 0, 0, 0, 0, 0, 193, 0, 0,
/* 5286 */ 0, 0, 0, 0, 0, 0, 204, 0, 45056, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 44032, 0, 0, 45568, 0, 45568,
/* 5316 */ 0, 45568, 45568, 45568, 45568, 45568, 45568, 0, 0, 0, 0, 0, 211, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 319, 0, 0, 0,
/* 5343 */ 0, 0, 0, 82, 83, 84, 86, 54, 55, 0, 0, 2139, 92, 94, 0, 0, 0, 0, 0, 39936, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/* 5374 */ 45056, 0, 0, 0, 0, 0, 82, 83, 84, 0, 86, 0, 0, 0, 0, 2139, 0, 0, 0, 0, 0, 238, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/* 5406 */ 1536, 1536, 0, 0, 0, 56, 0, 82, 0, 84, 86, 54, 55, 0, 0, 0, 92, 94, 0, 0, 0, 0, 0, 39936, 0, 0, 39936, 39936,
/* 5434 */ 39936, 0, 0, 0, 0, 0, 0, 330, 0, 0, 0, 0, 0, 0, 0, 0, 0, 346, 0, 0, 349, 0, 0, 0, 0, 82, 2560, 84, 0, 86, 0,
/* 5465 */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 39424, 0, 0, 0, 0, 0
};

const int RExParser::EXPECTED[] =
{
/*   0 */ 71, 75, 79, 83, 87, 91, 104, 153, 245, 153, 154, 95, 153, 101, 114, 153, 119, 217, 125, 229, 238, 238, 130,
/*  23 */ 134, 153, 153, 140, 162, 146, 153, 173, 152, 148, 158, 153, 166, 170, 115, 177, 161, 181, 126, 185, 192, 110,
/*  45 */ 188, 196, 200, 204, 208, 212, 222, 216, 153, 136, 221, 153, 232, 153, 153, 226, 153, 142, 153, 121, 153, 236,
/*  67 */ 107, 98, 242, 249, 581, 251, 266, 269, 272, 276, 279, 286, 282, 290, 291, 295, 303, 308, 321, 312, 316, 369,
/*  89 */ 369, 385, 303, 306, 320, 325, 548, 340, 355, 369, 350, 573, 369, 369, 545, 549, 332, 453, 369, 262, 573, 369,
/* 111 */ 299, 482, 347, 500, 369, 369, 369, 359, 328, 446, 369, 369, 254, 573, 445, 369, 369, 369, 360, 536, 367, 536,
/* 133 */ 367, 366, 364, 369, 369, 369, 553, 370, 374, 369, 369, 376, 564, 380, 384, 369, 369, 389, 404, 398, 369, 369,
/* 155 */ 369, 369, 349, 422, 412, 435, 400, 369, 369, 375, 390, 357, 257, 419, 426, 430, 434, 399, 369, 389, 394, 415,
/* 177 */ 567, 439, 443, 450, 360, 568, 441, 462, 466, 470, 347, 369, 487, 456, 486, 298, 474, 478, 348, 455, 486, 457,
/* 199 */ 458, 491, 408, 497, 335, 504, 508, 512, 516, 520, 524, 528, 531, 407, 369, 369, 535, 407, 369, 369, 369, 493,
/* 221 */ 559, 369, 369, 369, 542, 375, 554, 259, 369, 537, 367, 369, 376, 555, 560, 261, 572, 369, 369, 538, 368, 351,
/* 243 */ 369, 577, 369, 547, 339, 344, 579, 579, 18, 66, 130, 2, 4, 8, 16, 32, 128, 256, 0, 0, 4, 8, 16, 2, 32770, 2,
/* 269 */ 2, 6, 6, 2, 10, 18, 34, 2, 8194, 8194, 8194, 0, 6, 6, 40962, 19498, 20554, 2, 34, 34, 32770, 20010, 20554,
/* 292 */ 20554, 20554, -65534, -65278, 2, 2, 0, 0, 8, 128, 256, 0, 16, 16, 64, 64, 64, 128, 128, 32768, 0, 3074,
/* 314 */ 458752, 133169152, 134217728, 268435456, 1610612736, (int) 0x80000000, 128, 8, 8, 32, 32, 32, 32, 32, 3072,
/* 329 */ 65536, 131072, 1048576, 12582912, 16777216, 33554432, 67108864, 524288, 2097152, 9216, 262144, 3145728,
/* 341 */ 12582912, 16777216, 67108864, 67108864, 268435456, 536870912, 1073741824, (int) 0x80000000, 0, 0, 0, 8, 16, 0,
/* 355 */ 268435456, 536870912, 0, 0, 1, 8, 32, 128, 256, 0, 1048576, 0, 1048576, 2097152, 0, 0, 0, 0, -1, -1, 0, 0, 0,
/* 378 */ 1, 2, 2097088, 2097152, 29360128, 33554432, -67108864, 0, 0, 0, 2, 1, 2, 12, 16, 32, 32, 64, 2097024, 2097152,
/* 398 */ 67108864, 134217728, 268435456, -536870912, 0, 0, 32, 896, 1024, 2048, 0, 0, 0, 8192, 393216, 1572864,
/* 414 */ 2097152, 4194304, 8388608, 16777216, 33554432, 512, 1024, 2048, 4096, 24576, 32768, 65536, 8192, 16384, 32768,
/* 429 */ 65536, 131072, 262144, 1572864, 2097152, 4194304, 8388608, 16777216, 67108864, 134217728, 8192, 16384, 32768,
/* 442 */ 131072, 262144, 524288, 1048576, 2097152, 8388608, 16777216, 0, 4194304, 8388608, 16777216, 134217728,
/* 454 */ 268435456, 536870912, 1073741824, 0, 0, 0, 128, 0, 4194304, 134217728, 268435456, -536870912, 512, 1024, 4096,
/* 469 */ 32768, 131072, 262144, 134217728, 536870912, 256, 1024, 4096, 32768, 131072, 262144, 536870912, 1073741824,
/* 482 */ 1024, 32768, 131072, 536870912, 0, 0, 128, 256, 536870912, 4096, 4194304, 0, 2048, 65536, 131072, 524288, 0,
/* 499 */ 1048576, 8388608, 16777216, 67108864, 536870912, 525312, 2048, 2048, 2048, 67110912, 8192, 4194304, 16777216,
/* 512 */ 67108864, 20973568, 2101248, 2621440, 787456, 4196352, 16779264, 1179648, 11538432, 21626880, 4200448,
/* 523 */ 20977664, 4200448, 20986880, 21502976, 21765120, 21773312, 21838848, 57539584, 1023, 0, 0, 2048, 131072, 0, 0,
/* 538 */ 0, 65536, 131072, 1048576, 3, 252, 768, 0, 0, 8, 3072, 65536, 131072, 262144, 3145728, 1, 2, 4, 24, 32, 64,
/* 559 */ 96, 128, 256, 512, 0, 4, 24, 128, 256, 512, 1024, 4096, 8192, 16, 128, 0, 0, 0, 0, 0, 16, 0, 0, 0, 6, 2
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
