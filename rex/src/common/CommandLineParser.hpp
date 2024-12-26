// This file was generated on Thu Dec 26, 2024 07:44 (UTC+01) by REx v6.1-SNAPSHOT which is Copyright (c) 1979-2024 by Gunther Rademacher <grd@gmx.net>
// REx command line: CommandLineParser.ebnf -ll 1 -cpp -char -a rex

#ifndef COMMANDLINEPARSER_HPP
#define COMMANDLINEPARSER_HPP
#include <stdio.h>
#include <string>
#include <algorithm>
                                                            #line 2 "CommandLineParser.ebnf"
                                                            #include "FileIO.hpp"
                                                            #include "OutputFile.hpp"
                                                            #include "WString.hpp"

                                                            class CommandLineParser
                                                            {
                                                            public:
                                                              typedef std::basic_string<char *> Arguments;

                                                              static void clearArguments(Arguments args)
                                                              {
                                                                for (size_t i = 0; i < args.size(); ++i)
                                                                {
                                                                  free(args[i]);
                                                                }
                                                                args.clear();
                                                              }

                                                              static Arguments rewriteCommandLine(int argc, char *argv[], int &status)
                                                              {
                                                                status = 0;
                                                                char* content = 0;
                                                                Arguments args;
                                                                for (int i = 0; i < argc; ++i)
                                                                {
                                                                  if (i == 0 || strcmp(argv[i], "-remake") != 0)
                                                                  {
                                                                    char *commandLineArgument = strdup(argv[i]);
                                                                    args.append(&commandLineArgument, 1);
                                                                  }
                                                                  else
                                                                  {
                                                                    if (++i >= argc)
                                                                    {
                                                                      fprintf(stdout, "missing -remake argument\n");
                                                                      status = 1;
                                                                      break;
                                                                    }
                                                                    content = FileIO::getContent(argv[i]);
                                                                    if (content == 0)
                                                                    {
                                                                      fprintf(stdout, "file not found: %s\n", argv[i]);
                                                                      status = 1;
                                                                      break;
                                                                    }
                                                                    char* commandLine = strstr(content, OutputFile::commandLineIntroducer());
                                                                    if (commandLine == 0)
                                                                    {
                                                                      fprintf(stdout, "cannot remake %s, command line not found\n", argv[i]);
                                                                      status = 1;
                                                                      break;
                                                                    }
                                                                    commandLine += strlen(OutputFile::commandLineIntroducer());
                                                                    CommandLineParser parser(commandLine);
                                                                    try
                                                                    {
                                                                      parser.parse_CommandLine();
                                                                    }
                                                                    catch (ParseException &)
                                                                    {
                                                                      clearArguments(parser.args);
                                                                    }
                                                                    if (parser.args.empty())
                                                                    {
                                                                      fprintf(stdout, "cannot remake %s, command line arguments not found\n", argv[i]);
                                                                      status = 1;
                                                                      break;
                                                                    }
                                                                    char **remakeArgs = (char **) parser.args.c_str();
                                                                    args.append(remakeArgs);
                                                                  }
                                                                }
                                                                free(content);
                                                                return args;
                                                              }

                                                            private:
                                                              CommandLineParser(const char *string)
                                                              {
                                                                initialize(string);
                                                              }

                                                              virtual ~CommandLineParser()
                                                              {}

                                                              void append(int begin, int end)
                                                              {
                                                                CString arg;
                                                                for (int i = begin; i < end; ++i)
                                                                {
                                                                  if (input[i] == '\\' && i + 1 < end && input[i + 1] == '"')
                                                                    ++i;
                                                                  arg.append(input + i, 1);
                                                                }
                                                                char *copy = strdup(arg.c_str());
                                                                args.append(&copy, 1);
                                                              }

                                                              Arguments args;
                                                            #line 110 "CommandLineParser.hpp"
public:
  class ParseException
  {
  private:
    int begin, end, offending, expected, state;
    friend class CommandLineParser;

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

  void parse_CommandLine()
  {
    for (;;)
    {
      lookahead1W(0);               // WHITESPACE | NONQUOTED | QUOTED | EOL
      if (l1 == 4)                  // EOL
      {
        break;
      }
      switch (l1)
      {
      case 2:                       // NONQUOTED
        {
          consume(2);               // NONQUOTED
                                                            #line 103 "CommandLineParser.ebnf"
                                                            append(b0, e0);
                                                            #line 280 "CommandLineParser.hpp"
        }
        break;
      default:
        {
          consume(3);               // QUOTED
                                                            #line 104 "CommandLineParser.ebnf"
                                                            append(b0 + 1, e0 - 1);
                                                            #line 288 "CommandLineParser.hpp"
        }
        break;
      }
    }
    consume(4);                     // EOL
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
      if (code != 1)                // WHITESPACE
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

    for (int code = result & 15; code != 0; )
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
          int lo = 0, hi = 1;
          for (int m = 1; ; m = (hi + lo) >> 1)
          {
            if (MAP2[m] > c0) hi = m - 1;
            else if (MAP2[2 + m] < c0) lo = m + 1;
            else {charclass = MAP2[4 + m]; break;}
            if (lo > hi) {charclass = 0; break;}
          }
        }
      }

      state = code;
      int i0 = (charclass << 4) + code - 1;
      code = TRANSITION[(i0 & 3) + TRANSITION[i0 >> 2]];
      if (code > 15)
      {
        result = code;
        code &= 15;
        end = current;
      }
    }

    result >>= 4;
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
    int s = tokenSetId < 0 ? - tokenSetId : INITIAL[tokenSetId] & 15;
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
    int i0 = t * 9 + s - 1;
    return EXPECTED[i0];
  }

  static const int MAP0[];
  static const int MAP1[];
  static const int MAP2[];
  static const int INITIAL[];
  static const int TRANSITION[];
  static const int EXPECTED[];
  static const char *TOKEN[];
};

const int CommandLineParser::MAP0[] =
{
/*   0 */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 1, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 3, 4, 3,
/*  36 */ 3, 3, 3, 3, 3, 5, 3, 3, 3, 6, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 7, 3, 3, 3, 8, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
/*  73 */ 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 9, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
/* 110 */ 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3
};

const int CommandLineParser::MAP1[] =
{
/*   0 */ 54, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57,
/*  27 */ 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57,
/*  54 */ 89, 121, 156, 152, 152, 152, 152, 152, 152, 152, 152, 152, 152, 152, 152, 152, 152, 152, 152, 152, 152, 152,
/*  76 */ 152, 152, 152, 152, 152, 152, 152, 152, 152, 152, 152, 152, 152, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 1, 0, 0, 2, 0,
/* 104 */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 3, 4, 3, 3, 3, 3, 3, 3, 5, 3, 3, 3, 6, 3, 3, 3, 3, 3,
/* 140 */ 3, 3, 3, 3, 3, 3, 3, 7, 3, 3, 3, 8, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
/* 177 */ 3, 3, 3, 3, 3, 3, 3, 9, 3, 3, 3
};

const int CommandLineParser::MAP2[] =
{
/* 0 */ 57344, 65536, 65533, 1114111, 3, 3
};

const int CommandLineParser::INITIAL[] =
{
/* 0 */ 1
};

const int CommandLineParser::TRANSITION[] =
{
/*   0 */ 66, 66, 66, 66, 44, 66, 66, 66, 50, 66, 66, 66, 54, 61, 65, 66, 57, 67, 66, 66, 54, 71, 65, 66, 75, 79, 65,
/*  27 */ 66, 83, 61, 65, 66, 54, 61, 87, 66, 91, 95, 65, 66, 99, 46, 66, 66, 80, 80, 0, 0, 39, 4, 2, 2, 0, 0, 51, 0,
/*  56 */ 51, 4, 0, 0, 64, 51, 51, 0, 4, 51, 0, 0, 0, 0, 68, 51, 83, 0, 4, 53, 0, 51, 4, 57, 51, 0, 4, 54, 0, 51, 4, 83,
/*  88 */ 0, 0, 0, 51, 0, 51, 8, 51, 51, 0, 8, 39, 0, 0, 4
};

const int CommandLineParser::EXPECTED[] =
{
/* 0 */ 30, 16, 4, 8, 20, 20, 2, 8, 20
};

const char *CommandLineParser::TOKEN[] =
{
  "%ERROR",
  "WHITESPACE",
  "NONQUOTED",
  "QUOTED",
  "EOL"
};

                                                            #line 119 "CommandLineParser.ebnf"
                                                            /* hi there */
                                                            #line 525 "CommandLineParser.hpp"
#endif

// End
