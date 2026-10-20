// This file was generated on Tue Oct 20, 2026 19:55 (UTC+02) by REx v6.3-SNAPSHOT which is Copyright (c) 1979-2026 by Gunther Rademacher <grd@gmx.net>
// REx command line: PrintCpp.cpp.template
                                                            #line 1 "PrintCpp.cpp.template"
                                                            #include "../common/Memory.hpp"

                                                            #include "PrintCpp.hpp"
                                                            #include "ItemSet.hpp"
                                                            #include <ctype.h>

                                                            void PrintCpp::printIfndef(bool define, const wchar_t *qualifier)
                                                            {
                                                              if (! main && ! performanceTest)
                                                              {
                                                                const wchar_t *directive[] = {L"#ifndef ", L"#define ", 0};
                                                                for (const wchar_t **d = directive; *d; ++d)
                                                                {
                                                            #line 18 "PrintCpp.cpp"
  append(L"\n");
                                                            #line 15 "PrintCpp.cpp.template"
                                                                  print(*d);
                                                                  for (const wchar_t *f = wFileName.c_str(); *f; ++f)
                                                                  {
                                                                    switch (*f)
                                                                    {
                                                                    case L'.':
                                                            #line 27 "PrintCpp.cpp"
  append(L"_");
                                                            #line 21 "PrintCpp.cpp.template"
                                                                      break;
                                                                    default:
                                                                      {
                                                                        wchar_t s[] = {(wchar_t) towupper(*f), 0};
                                                                        print(s);
                                                                      }
                                                                    }
                                                                  }
                                                                  print(qualifier);
                                                                  if (! define)
                                                                  {
                                                                    break;
                                                                  }
                                                                }
                                                                if (main || performanceTest || tree || trace || ! parseChars)
                                                                {
                                                            #line 46 "PrintCpp.cpp"
  append(L"\n");
                                                            #line 38 "PrintCpp.cpp.template"
                                                                }
                                                              }
                                                              if (performanceTest)
                                                              {
                                                            #line 53 "PrintCpp.cpp"
  append(L"\n");
  append(L"#include <time.h>");
                                                            #line 43 "PrintCpp.cpp.template"
                                                              }
                                                              if (main || performanceTest || trace)
                                                              {
                                                            #line 60 "PrintCpp.cpp"
  append(L"\n");
  append(L"#include <string.h>");
                                                            #line 47 "PrintCpp.cpp.template"
                                                              }
                                                              if (main || performanceTest)
                                                              {
                                                            #line 67 "PrintCpp.cpp"
  append(L"\n");
  append(L"#include <stdlib.h>\n");
  append(L"#ifdef _WIN32\n");
  append(L"  #include <fcntl.h>\n");
  append(L"  #include <io.h>");
                                                            #line 54 "PrintCpp.cpp.template"
                                                                if (performanceTest)
                                                                {
                                                            #line 76 "PrintCpp.cpp"
  append(L"\n");
  append(L"#else\n");
  append(L"  #include <sys/types.h>\n");
  append(L"  #include <dirent.h>");
                                                            #line 59 "PrintCpp.cpp.template"
                                                                }
                                                            #line 83 "PrintCpp.cpp"
  append(L"\n");
  append(L"#endif");
                                                            #line 61 "PrintCpp.cpp.template"
                                                              }
                                                              if (main || performanceTest || tree || trace)
                                                              {
                                                            #line 90 "PrintCpp.cpp"
  append(L"\n");
  append(L"#include <vector>");
                                                            #line 65 "PrintCpp.cpp.template"
                                                              }
                                                              if (memoization)
                                                              {
                                                            #line 97 "PrintCpp.cpp"
  append(L"\n");
  append(L"#include <map>");
                                                            #line 69 "PrintCpp.cpp.template"
                                                              }
                                                              if (useGlr)
                                                              {
                                                            #line 104 "PrintCpp.cpp"
  append(L"\n");
  append(L"#include <queue>");
                                                            #line 73 "PrintCpp.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 110 "PrintCpp.cpp"
  append(L"\n");
  append(L"#include <stack>");
                                                            #line 76 "PrintCpp.cpp.template"
                                                                }
                                                              }
                                                            #line 116 "PrintCpp.cpp"
  append(L"\n");
  append(L"#include <stdio.h>\n");
  append(L"#include <string>\n");
  append(L"#include <algorithm>");
                                                            #line 81 "PrintCpp.cpp.template"
                                                            }

                                                            void PrintCpp::printEndif()
                                                            {
                                                              visitEpilog();
                                                              if (! main && ! performanceTest)
                                                              {
                                                            #line 129 "PrintCpp.cpp"
  append(L"\n");
  append(L"#endif\n");
                                                            #line 90 "PrintCpp.cpp.template"
                                                              }
                                                              else
                                                              {
                                                                if (performanceTest)
                                                                {
                                                            #line 138 "PrintCpp.cpp"
  append(L"\n");
  append(L"bool ");
                                                            #line 96 "PrintCpp.cpp.template"
                                                                  print(className.c_str());
                                                            #line 143 "PrintCpp.cpp"
  append(L"::quiet;\n");
  append(L"int ");
                                                            #line 98 "PrintCpp.cpp.template"
                                                                  print(className.c_str());
                                                            #line 148 "PrintCpp.cpp"
  append(L"::errorCount;\n");
  append(L"long long ");
                                                            #line 100 "PrintCpp.cpp.template"
                                                                  print(className.c_str());
                                                            #line 153 "PrintCpp.cpp"
  append(L"::parsed;\n");
                                                            #line 102 "PrintCpp.cpp.template"
                                                                  print(className.c_str());
                                                            #line 157 "PrintCpp.cpp"
  append(L"::ParseJobs ");
                                                            #line 103 "PrintCpp.cpp.template"
                                                                  print(className.c_str());
                                                            #line 161 "PrintCpp.cpp"
  append(L"::parsers;\n");
                                                            #line 105 "PrintCpp.cpp.template"
                                                                }
                                                            #line 165 "PrintCpp.cpp"
  append(L"\n");
  append(L"int main(int argc, char **argv)\n");
  append(L"{\n");
  append(L"  return ");
                                                            #line 109 "PrintCpp.cpp.template"
                                                                print(className.c_str());
                                                            #line 172 "PrintCpp.cpp"
  append(L"::main(argc, argv);\n");
  append(L"}\n");
                                                            #line 112 "PrintCpp.cpp.template"
                                                              }
                                                            }

                                                            void PrintCpp::openFile()
                                                            {
                                                              printIfndef(true, L"");
                                                            }

                                                            void PrintCpp::openClass()
                                                            {
                                                              if (! hasProlog)
                                                              {
                                                            #line 188 "PrintCpp.cpp"
  append(L"\n");
  append(L"\n");
  append(L"class ");
                                                            #line 126 "PrintCpp.cpp.template"
                                                                print(className.c_str());
                                                            #line 194 "PrintCpp.cpp"
  append(L"\n");
  append(L"{\n");
  append(L"public:");
                                                            #line 129 "PrintCpp.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 201 "PrintCpp.cpp"
  append(L"\n");
  append(L"  class ");
                                                            #line 132 "PrintCpp.cpp.template"
                                                                  if (isLrParser)
                                                                  {
                                                            #line 207 "PrintCpp.cpp"
  append(L"BottomUp");
                                                            #line 134 "PrintCpp.cpp.template"
                                                                  }
                                                            #line 211 "PrintCpp.cpp"
  append(L"EventHandler;\n");
                                                            #line 136 "PrintCpp.cpp.template"
                                                                }
                                                                increaseIndent();
                                                                WString args(stringType());
                                                                args += L"string";
                                                                if (tree)
                                                                {
                                                                  args += L", ";
                                                                  if (isLrParser) args += L"BottomUp";
                                                                  args += L"EventHandler *t";
                                                                }
                                                                openMethod (L"", L"", className.c_str(), args.c_str());
                                                                if (useGlr)
                                                                {
                                                            #line 227 "PrintCpp.cpp"
  append(L"\n");
  append(L": thread(0)\n");
                                                            #line 151 "PrintCpp.cpp.template"
                                                                }
                                                            #line 232 "PrintCpp.cpp"
  append(L"\n");
  append(L"{\n");
  append(L"  initialize(string");
                                                            #line 154 "PrintCpp.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 239 "PrintCpp.cpp"
  append(L", t");
                                                            #line 156 "PrintCpp.cpp.template"
                                                                }
                                                            #line 243 "PrintCpp.cpp"
  append(L");\n");
  append(L"}\n");
                                                            #line 159 "PrintCpp.cpp.template"
                                                                openMethod (L"", L"virtual ~", className.c_str(), L"");
                                                            #line 248 "PrintCpp.cpp"
  append(L"\n");
  append(L"{");
                                                            #line 161 "PrintCpp.cpp.template"
                                                                if (useGlr)
                                                                {
                                                            #line 254 "PrintCpp.cpp"
  append(L"\n");
  append(L"  delete thread;");
                                                            #line 164 "PrintCpp.cpp.template"
                                                                }
                                                            #line 259 "PrintCpp.cpp"
  append(L"\n");
  append(L"}\n");
                                                            #line 167 "PrintCpp.cpp.template"
                                                                decreaseIndent();
                                                              }
                                                              else
                                                              {
                                                            #line 267 "PrintCpp.cpp"
  append(L"\n");
  append(L"public:");
                                                            #line 172 "PrintCpp.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                            #line 274 "PrintCpp.cpp"
  append(L"\n");
  append(L"  class EventHandler\n");
  append(L"  {\n");
  append(L"  public:\n");
  append(L"    virtual ");
  append(L"~");
  append(L"EventHandler() {}\n");
  append(L"\n");
  append(L"    virtual void reset(");
                                                            #line 181 "PrintCpp.cpp.template"
                                                                print(stringType());
                                                            #line 286 "PrintCpp.cpp"
  append(L"string) = 0;\n");
  append(L"    virtual void startNonterminal(");
                                                            #line 183 "PrintCpp.cpp.template"
                                                                print(stringType());
                                                            #line 291 "PrintCpp.cpp"
  append(L"name, int begin) = 0;\n");
  append(L"    virtual void endNonterminal(");
                                                            #line 185 "PrintCpp.cpp.template"
                                                                print(stringType());
                                                            #line 296 "PrintCpp.cpp"
  append(L"name, int end) = 0;\n");
  append(L"    virtual void terminal(");
                                                            #line 187 "PrintCpp.cpp.template"
                                                                print(stringType());
                                                            #line 301 "PrintCpp.cpp"
  append(L"name, int begin, int end) = 0;\n");
  append(L"    virtual void whitespace(int begin, int end) = 0;\n");
  append(L"  };\n");
                                                            #line 191 "PrintCpp.cpp.template"
                                                                if (isLrParser)
                                                                {
                                                            #line 308 "PrintCpp.cpp"
  append(L"\n");
  append(L"  class BottomUpEventHandler\n");
  append(L"  {\n");
  append(L"  public:\n");
  append(L"    virtual ");
  append(L"~");
  append(L"BottomUpEventHandler() {}\n");
  append(L"\n");
  append(L"    virtual void reset(");
                                                            #line 199 "PrintCpp.cpp.template"
                                                                  print(stringType());
                                                            #line 320 "PrintCpp.cpp"
  append(L"string) = 0;\n");
  append(L"    virtual void nonterminal(");
                                                            #line 201 "PrintCpp.cpp.template"
                                                                  print(stringType());
                                                            #line 325 "PrintCpp.cpp"
  append(L"name, int begin, int end, int count) = 0;\n");
  append(L"    virtual void terminal(");
                                                            #line 203 "PrintCpp.cpp.template"
                                                                  print(stringType());
                                                            #line 330 "PrintCpp.cpp"
  append(L"name, int begin, int end) = 0;");
                                                            #line 204 "PrintCpp.cpp.template"
                                                                  if (resolvesAmbiguity)
                                                                  {
                                                            #line 335 "PrintCpp.cpp"
  append(L"\n");
  append(L"    virtual void ambiguity(int begin, int end) = 0;");
                                                            #line 207 "PrintCpp.cpp.template"
                                                                  }
                                                            #line 340 "PrintCpp.cpp"
  append(L"\n");
  append(L"  };\n");
                                                            #line 210 "PrintCpp.cpp.template"
                                                                }
                                                              }
                                                              if (main && tree)
                                                              {
                                                            #line 348 "PrintCpp.cpp"
  append(L"\n");
  append(L"  class XmlSerializer : public EventHandler\n");
  append(L"  {\n");
  append(L"  public:\n");
  append(L"    XmlSerializer(bool indent)\n");
  append(L"    : input(0)\n");
  append(L"    , delayedTag(0)\n");
  append(L"    , indent(indent)\n");
  append(L"    , hasChildElement(false)\n");
  append(L"    , depth(0)\n");
  append(L"    {\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    void reset(");
                                                            #line 227 "PrintCpp.cpp.template"
                                                                print(stringType());
                                                            #line 365 "PrintCpp.cpp"
  append(L"input)\n");
  append(L"    {\n");
  append(L"      fputs(\"<?xml version=\\\"1.0\\\" encoding=\\\"UTF-8\\\"?>\", stdout);\n");
  append(L"\n");
  append(L"      this->input = input;\n");
  append(L"      delayedTag = 0;\n");
  append(L"      hasChildElement = false;\n");
  append(L"      depth = 0;\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    void startNonterminal(");
                                                            #line 238 "PrintCpp.cpp.template"
                                                                print(stringType());
                                                            #line 379 "PrintCpp.cpp"
  append(L"tag, int b)\n");
  append(L"    {\n");
  append(L"      if (delayedTag != 0)\n");
  append(L"      {\n");
  append(L"        fputc('<', stdout);\n");
  append(L"        fputs(");
                                                            #line 244 "PrintCpp.cpp.template"
                                                                if (! parseChars)
                                                                {
                                                            #line 389 "PrintCpp.cpp"
  append(L"Utf8Encoder::encode(");
                                                            #line 246 "PrintCpp.cpp.template"
                                                                }
                                                            #line 393 "PrintCpp.cpp"
  append(L"delayedTag");
                                                            #line 247 "PrintCpp.cpp.template"
                                                                if (! parseChars)
                                                                {
                                                            #line 398 "PrintCpp.cpp"
  append(L").c_str()");
                                                            #line 249 "PrintCpp.cpp.template"
                                                                }
                                                            #line 402 "PrintCpp.cpp"
  append(L", stdout);\n");
  append(L"        fputc('>', stdout);\n");
  append(L"      }\n");
  append(L"      delayedTag = tag;\n");
  append(L"      if (indent)\n");
  append(L"      {\n");
  append(L"        fputc('\\n', stdout);\n");
  append(L"        for (int i = 0; i < depth; ++i)\n");
  append(L"        {\n");
  append(L"          fputs(\"  \", stdout);\n");
  append(L"        }\n");
  append(L"      }\n");
  append(L"      hasChildElement = false;\n");
  append(L"      ++depth;\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    void endNonterminal(");
                                                            #line 266 "PrintCpp.cpp.template"
                                                                print(stringType());
                                                            #line 422 "PrintCpp.cpp"
  append(L"tag, int e)\n");
  append(L"    {\n");
  append(L"      --depth;\n");
  append(L"      if (delayedTag != 0)\n");
  append(L"      {\n");
  append(L"        delayedTag = 0;\n");
  append(L"        fputc('<', stdout);\n");
  append(L"        fputs(");
                                                            #line 274 "PrintCpp.cpp.template"
                                                                if (! parseChars)
                                                                {
                                                            #line 434 "PrintCpp.cpp"
  append(L"Utf8Encoder::encode(");
                                                            #line 276 "PrintCpp.cpp.template"
                                                                }
                                                            #line 438 "PrintCpp.cpp"
  append(L"tag");
                                                            #line 277 "PrintCpp.cpp.template"
                                                                if (! parseChars)
                                                                {
                                                            #line 443 "PrintCpp.cpp"
  append(L").c_str()");
                                                            #line 279 "PrintCpp.cpp.template"
                                                                }
                                                            #line 447 "PrintCpp.cpp"
  append(L", stdout);\n");
  append(L"        fputs(\"/>\", stdout);\n");
  append(L"      }\n");
  append(L"      else\n");
  append(L"      {\n");
  append(L"        if (indent)\n");
  append(L"        {\n");
  append(L"          if (hasChildElement)\n");
  append(L"          {\n");
  append(L"            fputc('\\n', stdout);\n");
  append(L"            for (int i = 0; i < depth; ++i)\n");
  append(L"            {\n");
  append(L"              fputs(\"  \", stdout);\n");
  append(L"            }\n");
  append(L"          }\n");
  append(L"        }\n");
  append(L"        fputs(\"</\", stdout);\n");
  append(L"        fputs(");
                                                            #line 297 "PrintCpp.cpp.template"
                                                                if (! parseChars)
                                                                {
                                                            #line 469 "PrintCpp.cpp"
  append(L"Utf8Encoder::encode(");
                                                            #line 299 "PrintCpp.cpp.template"
                                                                }
                                                            #line 473 "PrintCpp.cpp"
  append(L"tag");
                                                            #line 300 "PrintCpp.cpp.template"
                                                                if (! parseChars)
                                                                {
                                                            #line 478 "PrintCpp.cpp"
  append(L").c_str()");
                                                            #line 302 "PrintCpp.cpp.template"
                                                                }
                                                            #line 482 "PrintCpp.cpp"
  append(L", stdout);\n");
  append(L"        fputc('>', stdout);\n");
  append(L"      }\n");
  append(L"      hasChildElement = true;\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    void whitespace(int b, int e)\n");
  append(L"    {\n");
  append(L"      characters(b, e);\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    void characters(int b, int e)\n");
  append(L"    {\n");
  append(L"      if (b < e)\n");
  append(L"      {\n");
  append(L"        if (delayedTag != 0)\n");
  append(L"        {\n");
  append(L"          fputc('<', stdout);\n");
  append(L"          fputs(");
                                                            #line 321 "PrintCpp.cpp.template"
                                                                if (! parseChars)
                                                                {
                                                            #line 505 "PrintCpp.cpp"
  append(L"Utf8Encoder::encode(");
                                                            #line 323 "PrintCpp.cpp.template"
                                                                }
                                                            #line 509 "PrintCpp.cpp"
  append(L"delayedTag");
                                                            #line 324 "PrintCpp.cpp.template"
                                                                if (! parseChars)
                                                                {
                                                            #line 514 "PrintCpp.cpp"
  append(L").c_str()");
                                                            #line 326 "PrintCpp.cpp.template"
                                                                }
                                                            #line 518 "PrintCpp.cpp"
  append(L", stdout);\n");
  append(L"          fputc('>', stdout);\n");
  append(L"          delayedTag = 0;\n");
  append(L"        }\n");
  append(L"        std::string encoded ");
                                                            #line 331 "PrintCpp.cpp.template"
                                                                if (! parseChars)
                                                                {
                                                            #line 527 "PrintCpp.cpp"
  append(L"= Utf8Encoder::encode");
                                                            #line 333 "PrintCpp.cpp.template"
                                                                }
                                                            #line 531 "PrintCpp.cpp"
  append(L"(input + b, e - b);\n");
  append(L"        int size = encoded.size();\n");
  append(L"        for (int i = 0; i < size; ++i)\n");
  append(L"        {\n");
  append(L"          char c = encoded[i];\n");
  append(L"          switch (c)\n");
  append(L"          {\n");
  append(L"          case 0: break;\n");
  append(L"          case L'&': fputs(\"&amp;\", stdout); break;\n");
  append(L"          case L'<': fputs(\"&lt;\", stdout); break;\n");
  append(L"          case L'>': fputs(\"&gt;\", stdout); break;\n");
  append(L"          default: fputc(c, stdout);\n");
  append(L"          }\n");
  append(L"        }\n");
  append(L"      }\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    void terminal(");
                                                            #line 351 "PrintCpp.cpp.template"
                                                                print(stringType());
                                                            #line 552 "PrintCpp.cpp"
  append(L"tag, int b, int e)\n");
  append(L"    {\n");
  append(L"      if (tag[0] == ");
                                                            #line 354 "PrintCpp.cpp.template"
                                                                print(stringIntroducer());
                                                            #line 558 "PrintCpp.cpp"
  append(L"'\\'') tag = ");
                                                            #line 355 "PrintCpp.cpp.template"
                                                                print(stringIntroducer());
                                                            #line 562 "PrintCpp.cpp"
  append(L"\"TOKEN\";\n");
  append(L"      startNonterminal(tag, b);\n");
  append(L"      characters(b, e);\n");
  append(L"      endNonterminal(tag, e);\n");
  append(L"    }\n");
  append(L"\n");
  append(L"  private:\n");
  append(L"    ");
                                                            #line 363 "PrintCpp.cpp.template"
                                                                print(stringType());
                                                            #line 573 "PrintCpp.cpp"
  append(L"input;\n");
  append(L"    ");
                                                            #line 365 "PrintCpp.cpp.template"
                                                                print(stringType());
                                                            #line 578 "PrintCpp.cpp"
  append(L"delayedTag;\n");
  append(L"    bool indent;\n");
  append(L"    bool hasChildElement;\n");
  append(L"    int depth;\n");
  append(L"  };\n");
                                                            #line 371 "PrintCpp.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                            #line 588 "PrintCpp.cpp"
  append(L"\n");
  append(L"  class Symbol\n");
  append(L"  {\n");
  append(L"  public:\n");
  append(L"    virtual ");
  append(L"~");
  append(L"Symbol() {}\n");
  append(L"\n");
  append(L"    ");
                                                            #line 380 "PrintCpp.cpp.template"
                                                                print(stringType());
                                                            #line 600 "PrintCpp.cpp"
  append(L"name;\n");
  append(L"    int begin;\n");
  append(L"    int end;\n");
  append(L"\n");
  append(L"    virtual void send(EventHandler *e) = 0;\n");
  append(L"\n");
  append(L"  protected:\n");
  append(L"    Symbol(");
                                                            #line 388 "PrintCpp.cpp.template"
                                                                print(stringType());
                                                            #line 611 "PrintCpp.cpp"
  append(L"name, int begin, int end)\n");
  append(L"    {\n");
  append(L"      this->name = name;\n");
  append(L"      this->begin = begin;\n");
  append(L"      this->end = end;\n");
  append(L"    }\n");
  append(L"  };\n");
  append(L"\n");
  append(L"  class Terminal : public Symbol\n");
  append(L"  {\n");
  append(L"  public:\n");
  append(L"    Terminal(");
                                                            #line 400 "PrintCpp.cpp.template"
                                                                print(stringType());
                                                            #line 626 "PrintCpp.cpp"
  append(L"name, int begin, int end)\n");
  append(L"    : Symbol(name, begin, end)\n");
  append(L"    {}\n");
  append(L"\n");
  append(L"    void send(EventHandler *e)\n");
  append(L"    {\n");
  append(L"      e->terminal(name, begin, end);\n");
  append(L"    }\n");
  append(L"  };\n");
  append(L"\n");
  append(L"  class Nonterminal : public Symbol\n");
  append(L"  {\n");
  append(L"  public:\n");
  append(L"    std::vector<Symbol *> *children;\n");
  append(L"\n");
  append(L"    Nonterminal(");
                                                            #line 416 "PrintCpp.cpp.template"
                                                                print(stringType());
                                                            #line 645 "PrintCpp.cpp"
  append(L"name, int begin, int end, std::vector<Symbol *> *children)\n");
  append(L"    : Symbol(name, begin, end)\n");
  append(L"    {\n");
  append(L"      this->children = children;\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    ");
  append(L"~");
  append(L"Nonterminal()\n");
  append(L"    {\n");
  append(L"      for (std::vector<Symbol *>::iterator child = children->begin(); child != children->end(); ++child)\n");
  append(L"        delete *child;\n");
  append(L"      delete children;\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    void send(EventHandler *e)\n");
  append(L"    {\n");
  append(L"      e->startNonterminal(name, begin);\n");
  append(L"      int pos = begin;\n");
  append(L"      for (std::vector<Symbol *>::iterator i = children->begin(); i != children->end(); ++i)\n");
  append(L"      {\n");
  append(L"        Symbol *c = *i;\n");
  append(L"        if (pos < c->begin) e->whitespace(pos, c->begin);\n");
  append(L"        c->send(e);\n");
  append(L"        pos = c->end;\n");
  append(L"      }\n");
  append(L"      if (pos < end) e->whitespace(pos, end);\n");
  append(L"      e->endNonterminal(name, end);\n");
  append(L"    }\n");
  append(L"  };\n");
  append(L"\n");
  append(L"  class TopDownTreeBuilder : public EventHandler\n");
  append(L"  {\n");
  append(L"  public:\n");
  append(L"    TopDownTreeBuilder()\n");
  append(L"    {\n");
  append(L"      input = 0;\n");
  append(L"      stack.clear();\n");
  append(L"      top = -1;\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    void reset(");
                                                            #line 456 "PrintCpp.cpp.template"
                                                                print(stringType());
                                                            #line 690 "PrintCpp.cpp"
  append(L"input)\n");
  append(L"    {\n");
  append(L"      this->input = input;\n");
  append(L"      top = -1;\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    void startNonterminal(");
                                                            #line 463 "PrintCpp.cpp.template"
                                                                print(stringType());
                                                            #line 700 "PrintCpp.cpp"
  append(L"name, int begin)\n");
  append(L"    {\n");
  append(L"      Nonterminal *nonterminal = new Nonterminal(name, begin, begin, new std::vector<Symbol *>());\n");
  append(L"      if (top++ >= 0) addChild(nonterminal);\n");
  append(L"      if ((size_t) top >= stack.size())\n");
  append(L"        stack.resize(stack.size() == 0 ? 64 : stack.size() << 1);\n");
  append(L"      stack[top] = nonterminal;\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    void endNonterminal(");
                                                            #line 473 "PrintCpp.cpp.template"
                                                                print(stringType());
                                                            #line 713 "PrintCpp.cpp"
  append(L"name, int end)\n");
  append(L"    {\n");
  append(L"      stack[top]->end = end;\n");
  append(L"      if (top > 0) --top;\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    void terminal(");
                                                            #line 480 "PrintCpp.cpp.template"
                                                                print(stringType());
                                                            #line 723 "PrintCpp.cpp"
  append(L"name, int begin, int end)\n");
  append(L"    {\n");
  append(L"      addChild(new Terminal(name, begin, end));\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    void whitespace(int begin, int end)\n");
  append(L"    {\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    void serialize(EventHandler *e)\n");
  append(L"    {\n");
  append(L"      e->reset(input);\n");
  append(L"      stack[0]->send(e);\n");
  append(L"    }\n");
  append(L"\n");
  append(L"  private:\n");
  append(L"    void addChild(Symbol *s)\n");
  append(L"    {\n");
  append(L"      Nonterminal *current = stack[top];\n");
  append(L"      current->children->push_back(s);\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    ");
                                                            #line 503 "PrintCpp.cpp.template"
                                                                print(stringType());
                                                            #line 749 "PrintCpp.cpp"
  append(L"input;\n");
  append(L"    std::vector<Nonterminal *> stack;\n");
  append(L"    int top;\n");
  append(L"  };\n");
                                                            #line 508 "PrintCpp.cpp.template"
                                                                if (tree && isLrParser)
                                                                {
                                                            #line 757 "PrintCpp.cpp"
  append(L"\n");
  append(L"  class ParseTreeBuilder : public BottomUpEventHandler\n");
  append(L"  {\n");
  append(L"  public:\n");
  append(L"    ParseTreeBuilder()\n");
  append(L"    : input(0), top(-1)\n");
  append(L"    {}\n");
  append(L"\n");
  append(L"    ");
  append(L"~");
  append(L"ParseTreeBuilder()\n");
  append(L"    {\n");
  append(L"      reset(0);\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    void reset(");
                                                            #line 523 "PrintCpp.cpp.template"
                                                                  print(stringType());
                                                            #line 776 "PrintCpp.cpp"
  append(L"input)\n");
  append(L"    {\n");
  append(L"      for (int i = 0; i <= top; ++i)\n");
  append(L"      {\n");
  append(L"        delete stack[i];\n");
  append(L"      }\n");
  append(L"      top = -1;\n");
  append(L"      this->input = input;\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    void nonterminal(");
                                                            #line 534 "PrintCpp.cpp.template"
                                                                  print(stringType());
                                                            #line 790 "PrintCpp.cpp"
  append(L"name, int begin, int end, int count)\n");
  append(L"    {");
                                                            #line 536 "PrintCpp.cpp.template"
                                                                  if (rejectsAmbiguity())
                                                                  {
                                                            #line 796 "PrintCpp.cpp"
  append(L"\n");
  append(L"      if (count > top + 1)\n");
  append(L"      {\n");
  append(L"        std::vector<Symbol *> *content = pop(top + 1);\n");
  append(L"        nonterminal(");
                                                            #line 542 "PrintCpp.cpp.template"
                                                                    print(stringIntroducer());
                                                            #line 804 "PrintCpp.cpp"
  append(L"\"UNAMBIGUOUS\", begin, content->size() == 0 ? end : (*content)[0]->begin, 0);\n");
  append(L"        for (size_t i = 0; i < content->size(); ++i)\n");
  append(L"        {\n");
  append(L"          push((*content)[i]);\n");
  append(L"        }\n");
  append(L"        delete content;\n");
  append(L"        count = top + 1;\n");
  append(L"      }");
                                                            #line 550 "PrintCpp.cpp.template"
                                                                  }
                                                            #line 815 "PrintCpp.cpp"
  append(L"\n");
  append(L"      push(new Nonterminal(name, begin, end, pop(count)));\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    void terminal(");
                                                            #line 555 "PrintCpp.cpp.template"
                                                                  print(stringType());
                                                            #line 823 "PrintCpp.cpp"
  append(L"name, int begin, int end)\n");
  append(L"    {\n");
  append(L"      push(new Terminal(name, begin, end));\n");
  append(L"    }");
                                                            #line 559 "PrintCpp.cpp.template"
                                                                  if (resolvesAmbiguity)
                                                                  {
                                                            #line 831 "PrintCpp.cpp"
  append(L"\n");
  append(L"\n");
  append(L"    void ambiguity(int begin, int end)\n");
  append(L"    {\n");
  append(L"    }");
                                                            #line 565 "PrintCpp.cpp.template"
                                                                  }
                                                            #line 839 "PrintCpp.cpp"
  append(L"\n");
  append(L"\n");
  append(L"    void serialize(EventHandler *e)\n");
  append(L"    {\n");
  append(L"      e->reset(input);\n");
  append(L"      for (int i = 0; i <= top; ++i)\n");
  append(L"      {\n");
  append(L"        stack[i]->send(e);\n");
  append(L"      }\n");
  append(L"    }\n");
                                                            #line 576 "PrintCpp.cpp.template"
                                                                  if (useGlr)
                                                                  {
                                                            #line 853 "PrintCpp.cpp"
  append(L"\n");
  append(L"    const std::vector<Symbol *> &getStack() const {return stack;}\n");
  append(L"    int getTop() const {return top;}\n");
                                                            #line 581 "PrintCpp.cpp.template"
                                                                  }
                                                            #line 859 "PrintCpp.cpp"
  append(L"\n");
  append(L"    void push(Symbol *s)\n");
  append(L"    {\n");
  append(L"      if ((size_t) ++top >= stack.size())\n");
  append(L"        stack.resize(stack.size() == 0 ? 64 : stack.size() << 1);\n");
  append(L"      stack[top] = s;\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    std::vector<Symbol *> *pop(int count)\n");
  append(L"    {\n");
  append(L"      if (count == 0)\n");
  append(L"        return new std::vector<Symbol *>();\n");
  append(L"      top -= count;\n");
  append(L"      std::vector<Symbol *>::iterator first = stack.begin() + (top + 1);\n");
  append(L"      return new std::vector<Symbol *>(first, first + count);\n");
  append(L"    }\n");
  append(L"\n");
  append(L"  private:\n");
  append(L"    ");
                                                            #line 600 "PrintCpp.cpp.template"
                                                                  print(stringType());
                                                            #line 881 "PrintCpp.cpp"
  append(L"input;\n");
  append(L"    std::vector<Symbol *> stack;\n");
  append(L"    int top;\n");
  append(L"  };\n");
                                                            #line 605 "PrintCpp.cpp.template"
                                                                }
                                                              }
                                                              if (main)
                                                              {
                                                                printSimpleMain();
                                                              }
                                                              if (performanceTest)
                                                              {
                                                                printPerformanceMain();
                                                              }
                                                            #line 897 "PrintCpp.cpp"
  append(L"\n");
  append(L"  class ParseException\n");
  append(L"  {\n");
  append(L"  private:\n");
  append(L"    int begin, end, offending, expected, state;");
                                                            #line 619 "PrintCpp.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 906 "PrintCpp.cpp"
  append(L"\n");
  append(L"    bool ambiguousInput;");
                                                            #line 622 "PrintCpp.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 912 "PrintCpp.cpp"
  append(L"\n");
  append(L"    ParseTreeBuilder *ambiguityDescriptor;");
                                                            #line 625 "PrintCpp.cpp.template"
                                                                }
                                                              }
                                                            #line 918 "PrintCpp.cpp"
  append(L"\n");
  append(L"    friend class ");
                                                            #line 628 "PrintCpp.cpp.template"
                                                              print(className.c_str());
                                                            #line 923 "PrintCpp.cpp"
  append(L";\n");
  append(L"\n");
  append(L"  protected:\n");
  append(L"    ParseException(int b, int e, int s, int o, int x)\n");
  append(L"    : begin(b), end(e), offending(o), expected(x), state(s)");
                                                            #line 633 "PrintCpp.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 932 "PrintCpp.cpp"
  append(L",\n");
  append(L"      ambiguousInput(false)");
                                                            #line 636 "PrintCpp.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 938 "PrintCpp.cpp"
  append(L", ambiguityDescriptor(0)");
                                                            #line 638 "PrintCpp.cpp.template"
                                                                }
                                                              }
                                                            #line 943 "PrintCpp.cpp"
  append(L"\n");
  append(L"    {\n");
  append(L"    }\n");
                                                            #line 643 "PrintCpp.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 950 "PrintCpp.cpp"
  append(L"\n");
  append(L"    ParseException(int b, int e");
                                                            #line 646 "PrintCpp.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 956 "PrintCpp.cpp"
  append(L", ParseTreeBuilder *ambiguityDescriptor");
                                                            #line 649 "PrintCpp.cpp.template"
                                                                }
                                                            #line 960 "PrintCpp.cpp"
  append(L")\n");
  append(L"    : begin(b), end(e), offending(-1), expected(-1), state(-1),\n");
  append(L"      ambiguousInput(true)");
                                                            #line 652 "PrintCpp.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 967 "PrintCpp.cpp"
  append(L", ambiguityDescriptor(ambiguityDescriptor)");
                                                            #line 655 "PrintCpp.cpp.template"
                                                                }
                                                            #line 971 "PrintCpp.cpp"
  append(L"\n");
  append(L"    {\n");
  append(L"    }\n");
                                                            #line 659 "PrintCpp.cpp.template"
                                                              }
                                                            #line 977 "PrintCpp.cpp"
  append(L"\n");
  append(L"  public:");
                                                            #line 661 "PrintCpp.cpp.template"
                                                              if (rejectsAmbiguity() && tree)
                                                              {
                                                            #line 983 "PrintCpp.cpp"
  append(L"\n");
  append(L"    ");
  append(L"~");
  append(L"ParseException()\n");
  append(L"    {\n");
  append(L"      delete ambiguityDescriptor;\n");
  append(L"    }\n");
                                                            #line 668 "PrintCpp.cpp.template"
                                                              }
                                                            #line 993 "PrintCpp.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 670 "PrintCpp.cpp.template"
                                                              print(stringType());
                                                            #line 998 "PrintCpp.cpp"
  append(L"getMessage() const\n");
  append(L"    {\n");
  append(L"      return ");
                                                            #line 673 "PrintCpp.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 1005 "PrintCpp.cpp"
  append(L"ambiguousInput\n");
  append(L"           ? ");
                                                            #line 676 "PrintCpp.cpp.template"
                                                                print(stringIntroducer());
                                                            #line 1010 "PrintCpp.cpp"
  append(L"\"ambiguous input\"\n");
  append(L"           : ");
                                                            #line 678 "PrintCpp.cpp.template"
                                                              }
                                                            #line 1015 "PrintCpp.cpp"
  append(L"offending < 0\n");
  append(L"           ? ");
                                                            #line 680 "PrintCpp.cpp.template"
                                                              print(stringIntroducer());
                                                            #line 1020 "PrintCpp.cpp"
  append(L"\"lexical analysis failed\"\n");
  append(L"           : ");
                                                            #line 682 "PrintCpp.cpp.template"
                                                              print(stringIntroducer());
                                                            #line 1025 "PrintCpp.cpp"
  append(L"\"syntax error\";\n");
  append(L"    }\n");
                                                            #line 685 "PrintCpp.cpp.template"
                                                              if (rejectsAmbiguity() && tree)
                                                              {
                                                            #line 1031 "PrintCpp.cpp"
  append(L"\n");
  append(L"    void serialize(EventHandler *eventHandler)\n");
  append(L"    {\n");
  append(L"      ambiguityDescriptor->serialize(eventHandler);\n");
  append(L"    }\n");
                                                            #line 692 "PrintCpp.cpp.template"
                                                              }
                                                            #line 1039 "PrintCpp.cpp"
  append(L"\n");
  append(L"    int getBegin() const {return begin;}\n");
  append(L"    int getEnd() const {return end;}\n");
  append(L"    int getState() const {return state;}\n");
  append(L"    int getOffending() const {return offending;}\n");
  append(L"    int getExpected() const {return expected;}");
                                                            #line 698 "PrintCpp.cpp.template"
                                                              if (useGlr)
                                                              {
                                                            #line 1049 "PrintCpp.cpp"
  append(L"\n");
  append(L"    int isAmbiguousInput() const {return ");
                                                            #line 701 "PrintCpp.cpp.template"
                                                                if (rejectsAmbiguity())
                                                                {
                                                            #line 1055 "PrintCpp.cpp"
  append(L"ambiguousInput");
                                                            #line 703 "PrintCpp.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1061 "PrintCpp.cpp"
  append(L"false");
                                                            #line 706 "PrintCpp.cpp.template"
                                                                }
                                                            #line 1065 "PrintCpp.cpp"
  append(L";}");
                                                            #line 707 "PrintCpp.cpp.template"
                                                              }
                                                            #line 1069 "PrintCpp.cpp"
  append(L"\n");
  append(L"  };\n");
                                                            #line 710 "PrintCpp.cpp.template"
                                                              /*
                                                            #line 1074 "PrintCpp.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 712 "PrintCpp.cpp.template"
                                                              print(stringType());
                                                            #line 1079 "PrintCpp.cpp"
  append(L"getInput() const\n");
  append(L"  {\n");
  append(L"    return input;\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  int getTokenOffset() const\n");
  append(L"  {\n");
  append(L"    return b0;\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  int getTokenEnd() const\n");
  append(L"  {\n");
  append(L"    return e0;\n");
  append(L"  }\n");
                                                            #line 727 "PrintCpp.cpp.template"
                                                              */
                                                            }

                                                            void PrintCpp::beginNonpublic()
                                                            {
                                                            #line 1100 "PrintCpp.cpp"
  append(L"\n");
  append(L"private:\n");
                                                            #line 734 "PrintCpp.cpp.template"
                                                            }

                                                            void PrintCpp::beginPublic()
                                                            {
                                                            #line 1108 "PrintCpp.cpp"
  append(L"\n");
  append(L"public:\n");
                                                            #line 740 "PrintCpp.cpp.template"
                                                            }

                                                            void PrintCpp::openStackNode()
                                                            {
                                                            #line 1116 "PrintCpp.cpp"
  append(L"  template<class T>\n");
  append(L"class TreeStructuredStack\n");
  append(L"{\n");
  append(L"public:\n");
  append(L"  T *link;\n");
  append(L"\n");
  append(L"  TreeStructuredStack(T *link)\n");
  append(L"  : link(link), referenceCount(1)\n");
  append(L"  {}\n");
  append(L"\n");
  append(L"  virtual ");
  append(L"~");
  append(L"TreeStructuredStack() {}\n");
  append(L"\n");
  append(L"  T *share()\n");
  append(L"  {\n");
  append(L"    ++referenceCount;\n");
  append(L"    return static_cast<T *>(this);\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  T *pop(int n)\n");
  append(L"  {\n");
  append(L"    T *node;\n");
  append(L"    T *link;\n");
  append(L"    for (node = static_cast<T *>(this); n-- > 0; node = link)\n");
  append(L"    {\n");
  append(L"      link = node->link;\n");
  append(L"      if (--node->referenceCount)\n");
  append(L"      {\n");
  append(L"        ++link->referenceCount;\n");
  append(L"      }\n");
  append(L"      else\n");
  append(L"      {\n");
  append(L"        delete node;\n");
  append(L"      }\n");
  append(L"    }\n");
  append(L"    return node;\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  void unshare()\n");
  append(L"  {\n");
  append(L"    T *node;\n");
  append(L"    T *link;\n");
  append(L"    for (node = static_cast<T *>(this); node; node = link)\n");
  append(L"    {\n");
  append(L"      link = node->link;\n");
  append(L"      if (--node->referenceCount)\n");
  append(L"      {\n");
  append(L"        break;\n");
  append(L"      }\n");
  append(L"      else\n");
  append(L"      {\n");
  append(L"        delete node;\n");
  append(L"      }\n");
  append(L"    }\n");
  append(L"  }\n");
  append(L"\n");
  append(L"private:\n");
  append(L"  int referenceCount;\n");
  append(L"};\n");
  append(L"\n");
  append(L"class StackNode : public TreeStructuredStack<StackNode>\n");
  append(L"{\n");
  append(L"public:\n");
  append(L"  int state;");
                                                            #line 806 "PrintCpp.cpp.template"
                                                              if (grammar->states->hasLookback)
                                                              {
                                                            #line 1185 "PrintCpp.cpp"
  append(L"\n");
  append(L"  int code;");
                                                            #line 809 "PrintCpp.cpp.template"
                                                              }
                                                            #line 1190 "PrintCpp.cpp"
  append(L"\n");
  append(L"  int pos;\n");
  append(L"\n");
  append(L"  StackNode(int state, ");
                                                            #line 813 "PrintCpp.cpp.template"
                                                              if (grammar->states->hasLookback)
                                                              {
                                                            #line 1198 "PrintCpp.cpp"
  append(L"int code, ");
                                                            #line 815 "PrintCpp.cpp.template"
                                                              }
                                                            #line 1202 "PrintCpp.cpp"
  append(L"int pos, StackNode *link)\n");
  append(L"  : TreeStructuredStack(link), state(state)");
                                                            #line 817 "PrintCpp.cpp.template"
                                                              if (grammar->states->hasLookback)
                                                              {
                                                            #line 1208 "PrintCpp.cpp"
  append(L", code(code)");
                                                            #line 819 "PrintCpp.cpp.template"
                                                              }
                                                            #line 1212 "PrintCpp.cpp"
  append(L", pos(pos)\n");
  append(L"  {}\n");
  append(L"\n");
  append(L"  bool equals(const StackNode *rhs)\n");
  append(L"  {\n");
  append(L"    StackNode *lhs = this;\n");
  append(L"    while (lhs != 0 && rhs != 0)\n");
  append(L"    {\n");
  append(L"      if (lhs == rhs) return true;\n");
  append(L"      if (lhs->state != rhs->state) return false;");
                                                            #line 829 "PrintCpp.cpp.template"
                                                              if (grammar->states->hasLookback)
                                                              {
                                                            #line 1226 "PrintCpp.cpp"
  append(L"\n");
  append(L"      if (lhs->code != rhs->code) return false;");
                                                            #line 832 "PrintCpp.cpp.template"
                                                              }
                                                            #line 1231 "PrintCpp.cpp"
  append(L"\n");
  append(L"      if (lhs->pos != rhs->pos) return false;\n");
  append(L"      lhs = lhs->link;\n");
  append(L"      rhs = rhs->link;\n");
  append(L"    }\n");
  append(L"    return lhs == rhs;\n");
  append(L"  }\n");
                                                            #line 840 "PrintCpp.cpp.template"
                                                              increaseIndent();
                                                            }

                                                            void PrintCpp::closeStackNode()
                                                            {
                                                              decreaseIndent();
                                                            #line 1246 "PrintCpp.cpp"
  append(L"\n");
  append(L"};\n");
                                                            #line 848 "PrintCpp.cpp.template"
                                                              if (hasCustomCode)
                                                              {
                                                            #line 1252 "PrintCpp.cpp"
  append(L"\n");
  append(L"class DeferredCode : public TreeStructuredStack<DeferredCode>\n");
  append(L"{\n");
  append(L"public:\n");
  append(L"  int codeId;\n");
  append(L"  int b0;\n");
  append(L"  int e0;\n");
  append(L"\n");
  append(L"  DeferredCode(DeferredCode *link, int codeId, int b0, int e0)\n");
  append(L"  : TreeStructuredStack(link), codeId(codeId), b0(b0), e0(e0)\n");
  append(L"  {}\n");
  append(L"};\n");
                                                            #line 862 "PrintCpp.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                            #line 1269 "PrintCpp.cpp"
  append(L"\n");
  append(L"class DeferredEvent : public TreeStructuredStack<DeferredEvent>\n");
  append(L"{\n");
  append(L"public:\n");
  append(L"  ");
                                                            #line 869 "PrintCpp.cpp.template"
                                                                print(stringType());
                                                            #line 1277 "PrintCpp.cpp"
  append(L"name;\n");
  append(L"  int begin;\n");
  append(L"  int end;");
                                                            #line 872 "PrintCpp.cpp.template"
                                                                if (shiftAmbiguity)
                                                                {
                                                            #line 1284 "PrintCpp.cpp"
  append(L"\n");
  append(L"  int depth;\n");
  append(L"\n");
  append(L"  virtual bool isTerminal() const {return false;}");
                                                            #line 877 "PrintCpp.cpp.template"
                                                                }
                                                            #line 1291 "PrintCpp.cpp"
  append(L"\n");
  append(L"\n");
  append(L"  DeferredEvent(DeferredEvent *link, ");
                                                            #line 880 "PrintCpp.cpp.template"
                                                                print(stringType());
                                                            #line 1297 "PrintCpp.cpp"
  append(L"name, int begin, int end)\n");
  append(L"  : TreeStructuredStack(link), name(name), begin(begin), end(end)");
                                                            #line 883 "PrintCpp.cpp.template"
                                                                if (shiftAmbiguity)
                                                                {
                                                            #line 1303 "PrintCpp.cpp"
  append(L"\n");
  append(L"  , depth(link == 0 ? 1 : link->depth + 1)");
                                                            #line 886 "PrintCpp.cpp.template"
                                                                }
                                                            #line 1308 "PrintCpp.cpp"
  append(L"\n");
  append(L"  {}\n");
  append(L"\n");
  append(L"  virtual void execute(BottomUpEventHandler *eventHandler) = 0;\n");
  append(L"\n");
  append(L"  void release(BottomUpEventHandler *eventHandler)\n");
  append(L"  {\n");
  append(L"    DeferredEvent *current = this;\n");
  append(L"    DeferredEvent *predecessor = current->link;\n");
  append(L"    current->link = 0;\n");
  append(L"    while (predecessor != 0)\n");
  append(L"    {\n");
  append(L"      DeferredEvent *next = predecessor->link;\n");
  append(L"      predecessor->link = current;\n");
  append(L"      current = predecessor;\n");
  append(L"      predecessor = next;\n");
  append(L"    }\n");
  append(L"    do\n");
  append(L"    {\n");
  append(L"      DeferredEvent *next = current->link;\n");
  append(L"      ");
                                                            #line 907 "PrintCpp.cpp.template"
                                                                if (shiftAmbiguity)
                                                                {
                                                            #line 1333 "PrintCpp.cpp"
  append(L"if (eventHandler != 0)\n");
  append(L"        ");
                                                            #line 910 "PrintCpp.cpp.template"
                                                                }
                                                            #line 1338 "PrintCpp.cpp"
  append(L"current->execute(eventHandler);\n");
  append(L"      delete current;\n");
  append(L"      current = next;\n");
  append(L"    }\n");
  append(L"    while (current != 0);\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  void show(BottomUpEventHandler *eventHandler)\n");
  append(L"  {\n");
  append(L"    std::stack<DeferredEvent *> stack;\n");
  append(L"    for (DeferredEvent *current = this; current != 0; current = current->link)\n");
  append(L"    {\n");
  append(L"      stack.push(current);\n");
  append(L"    }\n");
  append(L"    while (! stack.empty())\n");
  append(L"    {\n");
  append(L"      stack.top()->execute(eventHandler);\n");
  append(L"      stack.pop();\n");
  append(L"    }\n");
  append(L"  }\n");
  append(L"};\n");
  append(L"\n");
  append(L"class TerminalEvent : public DeferredEvent\n");
  append(L"{\n");
  append(L"public:\n");
  append(L"  TerminalEvent(DeferredEvent *link, ");
                                                            #line 936 "PrintCpp.cpp.template"
                                                                print(stringType());
                                                            #line 1367 "PrintCpp.cpp"
  append(L"name, int begin, int end)\n");
  append(L"  : DeferredEvent(link, name, begin, end)\n");
  append(L"  {}\n");
  append(L"\n");
  append(L"  void execute(BottomUpEventHandler *eventHandler)\n");
  append(L"  {\n");
  append(L"    eventHandler->terminal(name, begin, end);\n");
  append(L"  }");
                                                            #line 944 "PrintCpp.cpp.template"
                                                                if (shiftAmbiguity)
                                                                {
                                                            #line 1379 "PrintCpp.cpp"
  append(L"\n");
  append(L"\n");
  append(L"  bool isTerminal() const {return true;}");
                                                            #line 948 "PrintCpp.cpp.template"
                                                                }
                                                            #line 1385 "PrintCpp.cpp"
  append(L"\n");
  append(L"};\n");
  append(L"\n");
  append(L"class NonterminalEvent : public DeferredEvent\n");
  append(L"{\n");
  append(L"public:\n");
  append(L"  int count;\n");
  append(L"\n");
  append(L"  NonterminalEvent(DeferredEvent *link, ");
                                                            #line 957 "PrintCpp.cpp.template"
                                                                print(stringType());
                                                            #line 1397 "PrintCpp.cpp"
  append(L"name, int begin, int end, int count)\n");
  append(L"  : DeferredEvent(link, name, begin, end), count(count)\n");
  append(L"  {}\n");
  append(L"\n");
  append(L"  void execute(BottomUpEventHandler *eventHandler)\n");
  append(L"  {\n");
  append(L"    eventHandler->nonterminal(name, begin, end, count);\n");
  append(L"  }\n");
  append(L"};\n");
                                                            #line 967 "PrintCpp.cpp.template"
                                                                if (resolvesAmbiguity)
                                                                {
                                                            #line 1410 "PrintCpp.cpp"
  append(L"\n");
  append(L"\n");
  append(L"class AmbiguityEvent : public DeferredEvent\n");
  append(L"{\n");
  append(L"public:\n");
  append(L"  AmbiguityEvent(DeferredEvent *link, int begin, int end)\n");
  append(L"  : DeferredEvent(link, 0, begin, end)\n");
  append(L"  {}\n");
  append(L"\n");
  append(L"  void execute(BottomUpEventHandler *eventHandler)\n");
  append(L"  {\n");
  append(L"    eventHandler->ambiguity(begin, end);\n");
  append(L"  }\n");
  append(L"};\n");
                                                            #line 983 "PrintCpp.cpp.template"
                                                                }
                                                              }
                                                            #line 1428 "PrintCpp.cpp"
  append(L"\n");
  append(L"class ParsingThread;\n");
  append(L"\n");
  append(L"class ParsingThreadLess\n");
  append(L"{\n");
  append(L"public:\n");
  append(L"  bool operator()(ParsingThread *lhs, ParsingThread *rhs) const {return *lhs < *rhs;}\n");
  append(L"};\n");
  append(L"\n");
  append(L"class PriorityQueue : public std::priority_queue<ParsingThread *, std::vector<ParsingThread *>, ParsingThreadLess>\n");
  append(L"{\n");
  append(L"public:\n");
  append(L"  ");
  append(L"~");
  append(L"PriorityQueue()\n");
  append(L"  {\n");
  append(L"    while (!empty())\n");
  append(L"    {\n");
  append(L"      delete top();\n");
  append(L"      pop();\n");
  append(L"    }\n");
  append(L"  }\n");
  append(L"};\n");
  append(L"\n");
  append(L"enum Status {PARSING, ACCEPTED, ERROR};\n");
  append(L"\n");
  append(L"void parse(int target, int initialState, ");
                                                            #line 1009 "PrintCpp.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 1459 "PrintCpp.cpp"
  append(L"BottomUpEventHandler *eventHandler, ");
                                                            #line 1012 "PrintCpp.cpp.template"
                                                              }
                                                            #line 1463 "PrintCpp.cpp"
  append(L"ParsingThread *&thread)\n");
  append(L"{\n");
  append(L"  PriorityQueue threads;\n");
  append(L"  thread->open(threads, initialState");
                                                            #line 1016 "PrintCpp.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 1471 "PrintCpp.cpp"
  append(L", eventHandler");
                                                            #line 1018 "PrintCpp.cpp.template"
                                                              }
                                                            #line 1475 "PrintCpp.cpp"
  append(L", target);\n");
  append(L"  for (;;)\n");
  append(L"  {\n");
  append(L"    thread = threads.top();\n");
  append(L"    threads.pop();\n");
  append(L"    if (thread->accepted)\n");
  append(L"    {");
                                                            #line 1025 "PrintCpp.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 1486 "PrintCpp.cpp"
  append(L"\n");
  append(L"      ParsingThread *other = 0;\n");
  append(L"      while (! threads.empty())\n");
  append(L"      {\n");
  append(L"        delete other;\n");
  append(L"        other = threads.top();\n");
  append(L"        threads.pop();\n");
  append(L"        if (thread->e0 < other->e0)\n");
  append(L"        {\n");
  append(L"          delete thread;\n");
  append(L"          thread = other;\n");
  append(L"          other = 0;\n");
  append(L"        }\n");
  append(L"      }\n");
  append(L"      if (other != 0)\n");
  append(L"      {\n");
  append(L"        threads.push(other);\n");
  append(L"        rejectAmbiguity(thread");
                                                            #line 1044 "PrintCpp.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 1508 "PrintCpp.cpp"
  append(L", thread->deferredEvent, other->deferredEvent");
                                                            #line 1047 "PrintCpp.cpp.template"
                                                                }
                                                            #line 1512 "PrintCpp.cpp"
  append(L");\n");
  append(L"      }");
                                                            #line 1049 "PrintCpp.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 1519 "PrintCpp.cpp"
  append(L"\n");
  append(L"      while (! threads.empty())\n");
  append(L"      {\n");
  append(L"        ParsingThread *other = threads.top();\n");
  append(L"        threads.pop();\n");
  append(L"        if (thread->e0 < other->e0)\n");
  append(L"        {\n");
  append(L"          delete thread;\n");
  append(L"          thread = other;\n");
  append(L"        }\n");
  append(L"        else\n");
  append(L"        {\n");
  append(L"          thread = resolve(thread, other);\n");
  append(L"        }\n");
  append(L"      }");
                                                            #line 1066 "PrintCpp.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                            #line 1539 "PrintCpp.cpp"
  append(L"\n");
  append(L"      if (thread->deferredEvent != 0)\n");
  append(L"      {\n");
  append(L"        thread->deferredEvent->release(eventHandler);\n");
  append(L"        thread->deferredEvent = 0;\n");
  append(L"      }");
                                                            #line 1074 "PrintCpp.cpp.template"
                                                              }
                                                              if (hasCustomCode)
                                                              {
                                                            #line 1550 "PrintCpp.cpp"
  append(L"\n");
  append(L"      thread->executeDeferredCode();");
                                                            #line 1078 "PrintCpp.cpp.template"
                                                              }
                                                            #line 1555 "PrintCpp.cpp"
  append(L"\n");
  append(L"      return;\n");
  append(L"    }\n");
  append(L"\n");
                                                            #line 1083 "PrintCpp.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 1563 "PrintCpp.cpp"
  append(L"    if (! threads.empty())\n");
  append(L"    {\n");
  append(L"      if (*threads.top() == *thread)\n");
  append(L"      {\n");
  append(L"        rejectAmbiguity(thread");
                                                            #line 1089 "PrintCpp.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 1572 "PrintCpp.cpp"
  append(L", thread->deferredEvent, threads.top()->deferredEvent");
                                                            #line 1092 "PrintCpp.cpp.template"
                                                                }
                                                            #line 1576 "PrintCpp.cpp"
  append(L");\n");
  append(L"      }\n");
  append(L"    }");
                                                            #line 1095 "PrintCpp.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 1584 "PrintCpp.cpp"
  append(L"    while (! threads.empty() && *threads.top() == *thread)\n");
  append(L"    {\n");
  append(L"      ParsingThread *other = threads.top();\n");
  append(L"      threads.pop();\n");
  append(L"      thread = resolve(thread, other);\n");
  append(L"    }");
                                                            #line 1103 "PrintCpp.cpp.template"
                                                              }
                                                              if (tree || hasCustomCode)
                                                              {
                                                                if (rejectsAmbiguity())
                                                                {
                                                            #line 1597 "PrintCpp.cpp"
  append(L"\n");
  append(L"    else\n");
  append(L"    {");
                                                            #line 1110 "PrintCpp.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1605 "PrintCpp.cpp"
  append(L"\n");
  append(L"    if (threads.empty())\n");
  append(L"    {");
                                                            #line 1115 "PrintCpp.cpp.template"
                                                                }
                                                                if (tree)
                                                                {
                                                            #line 1613 "PrintCpp.cpp"
  append(L"\n");
  append(L"      if (thread->deferredEvent != 0)\n");
  append(L"      {\n");
  append(L"        thread->deferredEvent->release(eventHandler);\n");
  append(L"        thread->deferredEvent = 0;\n");
  append(L"      }");
                                                            #line 1123 "PrintCpp.cpp.template"
                                                                }
                                                                if (hasCustomCode)
                                                                {
                                                            #line 1624 "PrintCpp.cpp"
  append(L"\n");
  append(L"      thread->executeDeferredCode();");
                                                            #line 1127 "PrintCpp.cpp.template"
                                                                }
                                                            #line 1629 "PrintCpp.cpp"
  append(L"\n");
  append(L"    }");
                                                            #line 1129 "PrintCpp.cpp.template"
                                                              }
                                                            #line 1634 "PrintCpp.cpp"
  append(L"\n");
  append(L"\n");
  append(L"    int status;\n");
  append(L"    for (;;)\n");
  append(L"    {\n");
  append(L"      if ((status = thread->parse()) != PARSING) break;\n");
  append(L"      if (! threads.empty()) break;\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    if (status != ERROR)\n");
  append(L"    {\n");
  append(L"      threads.push(thread);\n");
  append(L"    }\n");
  append(L"    else if (threads.empty())\n");
  append(L"    {\n");
  append(L"      thread->cleanup();\n");
  append(L"      throw ParseException(thread->b1,\n");
  append(L"                           thread->e1,\n");
  append(L"                           TOKENSET[thread->state] + 1,\n");
  append(L"                           thread->l1,\n");
  append(L"                           -1\n");
  append(L"                          );\n");
  append(L"    }\n");
  append(L"    else\n");
  append(L"    {\n");
  append(L"      delete thread;\n");
  append(L"    }\n");
  append(L"  }\n");
  append(L"}\n");
                                                            #line 1159 "PrintCpp.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 1667 "PrintCpp.cpp"
  append(L"\n");
  append(L"void rejectAmbiguity(ParsingThread *&thread");
                                                            #line 1162 "PrintCpp.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 1673 "PrintCpp.cpp"
  append(L", DeferredEvent *first, DeferredEvent *second");
                                                            #line 1165 "PrintCpp.cpp.template"
                                                                }
                                                            #line 1677 "PrintCpp.cpp"
  append(L")\n");
  append(L"{");
                                                            #line 1167 "PrintCpp.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 1683 "PrintCpp.cpp"
  append(L"\n");
  append(L"  ParseTreeBuilder *treeBuilder = new ParseTreeBuilder();\n");
  append(L"  treeBuilder->reset(input);\n");
  append(L"  second->show(treeBuilder);\n");
  append(L"  treeBuilder->nonterminal(");
                                                            #line 1173 "PrintCpp.cpp.template"
                                                                  print(stringIntroducer());
                                                            #line 1691 "PrintCpp.cpp"
  append(L"\"ALTERNATIVE\", treeBuilder->getStack()[0]->begin, treeBuilder->getStack()[treeBuilder->getTop()]->end, treeBuilder->getTop() + 1);\n");
  append(L"  std::vector<Symbol *> *secondTree = treeBuilder->pop(1);\n");
  append(L"  first->show(treeBuilder);\n");
  append(L"  treeBuilder->nonterminal(");
                                                            #line 1177 "PrintCpp.cpp.template"
                                                                  print(stringIntroducer());
                                                            #line 1698 "PrintCpp.cpp"
  append(L"\"ALTERNATIVE\", treeBuilder->getStack()[0]->begin, treeBuilder->getStack()[treeBuilder->getTop()]->end, treeBuilder->getTop() + 1);\n");
  append(L"  treeBuilder->push((*secondTree)[0]);\n");
  append(L"  delete secondTree;\n");
  append(L"  treeBuilder->nonterminal(");
                                                            #line 1181 "PrintCpp.cpp.template"
                                                                  print(stringIntroducer());
                                                            #line 1705 "PrintCpp.cpp"
  append(L"\"AMBIGUOUS\", treeBuilder->getStack()[0]->begin, treeBuilder->getStack()[treeBuilder->getTop()]->end, 2);");
                                                            #line 1183 "PrintCpp.cpp.template"
                                                                }
                                                            #line 1709 "PrintCpp.cpp"
  append(L"\n");
  append(L"  int begin = thread->stack->pos;\n");
  append(L"  int end = thread->e0;\n");
  append(L"  thread->cleanup();\n");
  append(L"  throw ParseException(begin, end");
                                                            #line 1188 "PrintCpp.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 1718 "PrintCpp.cpp"
  append(L", treeBuilder");
                                                            #line 1190 "PrintCpp.cpp.template"
                                                                }
                                                            #line 1722 "PrintCpp.cpp"
  append(L");\n");
  append(L"}");
                                                            #line 1192 "PrintCpp.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 1729 "PrintCpp.cpp"
  append(L"\n");
  append(L"ParsingThread *resolve(ParsingThread *thread, ParsingThread *other)\n");
  append(L"{");
                                                            #line 1197 "PrintCpp.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 1736 "PrintCpp.cpp"
  append(L"\n");
  append(L"  int begin = thread->stack->pos;\n");
  append(L"  for (StackNode *a = thread->stack, *b = other->stack; a != b && a != 0 && b != 0; a = a->link, b = b->link)\n");
  append(L"  {\n");
  append(L"    begin = a->pos;\n");
  append(L"  }");
                                                            #line 1204 "PrintCpp.cpp.template"
                                                                }
                                                            #line 1745 "PrintCpp.cpp"
  append(L"\n");
                                                            #line 1206 "PrintCpp.cpp.template"
                                                                if (shiftAmbiguity)
                                                                {
                                                            #line 1750 "PrintCpp.cpp"
  append(L"  DeferredEvent *ea = thread->deferredEvent;\n");
  append(L"  DeferredEvent *eb = other->deferredEvent;\n");
  append(L"  DeferredEvent *ua = 0;\n");
  append(L"  DeferredEvent *ub = 0;\n");
  append(L"  while (ea != eb)\n");
  append(L"  {\n");
  append(L"    if ((ea == 0 ? 0 : ea->depth) >= (eb == 0 ? 0 : eb->depth))\n");
  append(L"    {\n");
  append(L"      ua = ea;\n");
  append(L"      ea = ea->link;\n");
  append(L"    }\n");
  append(L"    else\n");
  append(L"    {\n");
  append(L"      ub = eb;\n");
  append(L"      eb = eb->link;\n");
  append(L"    }\n");
  append(L"  }\n");
  append(L"  bool sa = ua != 0 && ua->isTerminal();\n");
  append(L"  bool sb = ub != 0 && ub->isTerminal();\n");
  append(L"  ParsingThread *winner = sa != sb ? (sb ? other : thread) : (other->eventCount < thread->eventCount ? other : thread);");
                                                            #line 1228 "PrintCpp.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1775 "PrintCpp.cpp"
  append(L"  ParsingThread *winner = other->eventCount < thread->eventCount ? other : thread;");
                                                            #line 1232 "PrintCpp.cpp.template"
                                                                }
                                                            #line 1779 "PrintCpp.cpp"
  append(L"\n");
  append(L"  delete (winner == thread ? other : thread);");
                                                            #line 1234 "PrintCpp.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 1785 "PrintCpp.cpp"
  append(L"\n");
  append(L"  winner->addAmbiguity(begin, winner->e0);");
                                                            #line 1237 "PrintCpp.cpp.template"
                                                                }
                                                            #line 1790 "PrintCpp.cpp"
  append(L"\n");
  append(L"  return winner;\n");
  append(L"}");
                                                            #line 1240 "PrintCpp.cpp.template"
                                                              }
                                                            }

                                                            void PrintCpp::openThread()
                                                            {
                                                            #line 1800 "PrintCpp.cpp"
  append(L"\n");
  append(L"class ParsingThread\n");
  append(L"{\n");
  append(L"public:\n");
  append(L"  ");
                                                            #line 1249 "PrintCpp.cpp.template"
                                                              print(className.c_str());
                                                            #line 1808 "PrintCpp.cpp"
  append(L" *parser;\n");
  append(L"  PriorityQueue *threads;\n");
  append(L"  bool accepted;\n");
  append(L"  StackNode *stack;\n");
  append(L"  int state;\n");
  append(L"  int action;\n");
  append(L"  int target;");
                                                            #line 1256 "PrintCpp.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 1819 "PrintCpp.cpp"
  append(L"\n");
  append(L"  DeferredEvent *deferredEvent;");
                                                            #line 1259 "PrintCpp.cpp.template"
                                                              }
                                                              if (hasCustomCode)
                                                              {
                                                            #line 1826 "PrintCpp.cpp"
  append(L"\n");
  append(L"  DeferredCode *deferredCode;");
                                                            #line 1263 "PrintCpp.cpp.template"
                                                              }
                                                            #line 1831 "PrintCpp.cpp"
  append(L"\n");
  append(L"  int id;");
                                                            #line 1265 "PrintCpp.cpp.template"
                                                              if (resolvesAmbiguity)
                                                              {
                                                            #line 1837 "PrintCpp.cpp"
  append(L"\n");
  append(L"  int eventCount;");
                                                            #line 1268 "PrintCpp.cpp.template"
                                                              }
                                                            #line 1842 "PrintCpp.cpp"
  append(L"\n");
  append(L"\n");
  append(L"  ParsingThread()\n");
  append(L"  : stack(0)\n");
  append(L"  {}\n");
  append(L"\n");
  append(L"  ");
  append(L"~");
  append(L"ParsingThread()\n");
  append(L"  {\n");
  append(L"    cleanup();\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  void open(PriorityQueue &threads, int initialState");
                                                            #line 1280 "PrintCpp.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 1860 "PrintCpp.cpp"
  append(L", BottomUpEventHandler *eventHandler");
                                                            #line 1283 "PrintCpp.cpp.template"
                                                              }
                                                            #line 1864 "PrintCpp.cpp"
  append(L", int target)\n");
  append(L"  {\n");
  append(L"    this->threads = &threads;\n");
  append(L"    this->target = target;");
                                                            #line 1287 "PrintCpp.cpp.template"
                                                              if (resolvesAmbiguity)
                                                              {
                                                            #line 1872 "PrintCpp.cpp"
  append(L"\n");
  append(L"    eventCount = 0;");
                                                            #line 1290 "PrintCpp.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                            #line 1879 "PrintCpp.cpp"
  append(L"\n");
  append(L"    bw = e0;\n");
  append(L"    bs = e0;\n");
  append(L"    es = e0;\n");
  append(L"    this->eventHandler = eventHandler;\n");
  append(L"    if (eventHandler != 0)\n");
  append(L"    {\n");
  append(L"      eventHandler->reset(parser->input);\n");
  append(L"    }\n");
  append(L"    deferredEvent = 0;");
                                                            #line 1302 "PrintCpp.cpp.template"
                                                              }
                                                              if (hasCustomCode && useGlr)
                                                              {
                                                            #line 1894 "PrintCpp.cpp"
  append(L"\n");
  append(L"    deferredCode = 0;");
                                                            #line 1306 "PrintCpp.cpp.template"
                                                              }
                                                            #line 1899 "PrintCpp.cpp"
  append(L"\n");
  append(L"    accepted = false;\n");
  append(L"    stack = new StackNode(-1, ");
                                                            #line 1309 "PrintCpp.cpp.template"
                                                              if (grammar->states->hasLookback)
                                                              {
                                                            #line 1906 "PrintCpp.cpp"
  append(L"0, ");
                                                            #line 1311 "PrintCpp.cpp.template"
                                                              }
                                                            #line 1910 "PrintCpp.cpp"
  append(L"e0, 0);\n");
  append(L"    state = initialState;\n");
  append(L"    action = predict(initialState);\n");
  append(L"    threads.push(this);\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  void cleanup()\n");
  append(L"  {\n");
  append(L"    if (stack != 0)\n");
  append(L"    {\n");
  append(L"      stack->unshare();\n");
  append(L"      stack = 0;\n");
  append(L"    }");
                                                            #line 1324 "PrintCpp.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 1927 "PrintCpp.cpp"
  append(L"\n");
  append(L"    if (deferredEvent != 0)\n");
  append(L"    {\n");
  append(L"      deferredEvent->unshare();\n");
  append(L"      deferredEvent = 0;\n");
  append(L"    }");
                                                            #line 1331 "PrintCpp.cpp.template"
                                                              }
                                                              if (hasCustomCode)
                                                              {
                                                            #line 1938 "PrintCpp.cpp"
  append(L"\n");
  append(L"    if (deferredCode != 0)\n");
  append(L"    {\n");
  append(L"      deferredCode->unshare();\n");
  append(L"      deferredCode = 0;\n");
  append(L"    }");
                                                            #line 1339 "PrintCpp.cpp.template"
                                                              }
                                                            #line 1947 "PrintCpp.cpp"
  append(L"\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  ParsingThread *copy(ParsingThread *other, int action)\n");
  append(L"  {\n");
  append(L"    this->action = action;\n");
  append(L"    accepted = other->accepted;\n");
  append(L"    target = other->target;\n");
  append(L"    parser = other->parser;");
                                                            #line 1348 "PrintCpp.cpp.template"
                                                              if (resolvesAmbiguity)
                                                              {
                                                            #line 1960 "PrintCpp.cpp"
  append(L"\n");
  append(L"    eventCount = other->eventCount;");
                                                            #line 1351 "PrintCpp.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                            #line 1967 "PrintCpp.cpp"
  append(L"\n");
  append(L"    bs = other->bs;\n");
  append(L"    bw = other->bw;\n");
  append(L"    es = other->es;\n");
  append(L"    eventHandler = other->eventHandler;\n");
  append(L"    deferredEvent = other->deferredEvent == 0 ? 0 : other->deferredEvent->share();");
                                                            #line 1360 "PrintCpp.cpp.template"
                                                              }
                                                              if (hasCustomCode)
                                                              {
                                                            #line 1978 "PrintCpp.cpp"
  append(L"\n");
  append(L"    deferredCode = other->deferredCode == 0 ? 0 : other->deferredCode->share();");
                                                            #line 1365 "PrintCpp.cpp.template"
                                                              }
                                                            #line 1983 "PrintCpp.cpp"
  append(L"\n");
  append(L"    id = ++parser->maxId;\n");
  append(L"    threads = other->threads;\n");
  append(L"    state = other->state;\n");
  append(L"    stack = other->stack->share();\n");
  append(L"    b0 = other->b0;\n");
  append(L"    e0 = other->e0;");
                                                            #line 1372 "PrintCpp.cpp.template"
                                                              for (size_t i = 1; i <= grammar->k; ++i)
                                                              {
                                                                const wchar_t *iString = format.toString<wchar_t>(i);
                                                            #line 1995 "PrintCpp.cpp"
  append(L"\n");
  append(L"    l");
                                                            #line 1376 "PrintCpp.cpp.template"
                                                                print(iString);
                                                            #line 2000 "PrintCpp.cpp"
  append(L" = other->l");
                                                            #line 1377 "PrintCpp.cpp.template"
                                                                print(iString);
                                                            #line 2004 "PrintCpp.cpp"
  append(L";\n");
  append(L"    b");
                                                            #line 1379 "PrintCpp.cpp.template"
                                                                print(iString);
                                                            #line 2009 "PrintCpp.cpp"
  append(L" = other->b");
                                                            #line 1380 "PrintCpp.cpp.template"
                                                                print(iString);
                                                            #line 2013 "PrintCpp.cpp"
  append(L";\n");
  append(L"    e");
                                                            #line 1382 "PrintCpp.cpp.template"
                                                                print(iString);
                                                            #line 2018 "PrintCpp.cpp"
  append(L" = other->e");
                                                            #line 1383 "PrintCpp.cpp.template"
                                                                print(iString);
                                                            #line 2022 "PrintCpp.cpp"
  append(L";");
                                                            #line 1384 "PrintCpp.cpp.template"
                                                              }
                                                            #line 2026 "PrintCpp.cpp"
  append(L"\n");
  append(L"    end = other->end;\n");
  append(L"    return this;\n");
  append(L"  }\n");
  append(L"\n");
                                                            #line 1390 "PrintCpp.cpp.template"
                                                              if (resolvesAmbiguity && tree)
                                                              {
                                                            #line 2035 "PrintCpp.cpp"
  append(L"\n");
  append(L"  void addAmbiguity(int begin, int end)\n");
  append(L"  {\n");
  append(L"    if (eventHandler != 0)\n");
  append(L"      deferredEvent = new AmbiguityEvent(deferredEvent, begin, end);\n");
  append(L"  }\n");
  append(L"\n");
                                                            #line 1399 "PrintCpp.cpp.template"
                                                              }
                                                            #line 2045 "PrintCpp.cpp"
  append(L"  bool operator<(const ParsingThread &other)\n");
  append(L"  {\n");
  append(L"    int comp;\n");
  append(L"    if (accepted != other.accepted)\n");
  append(L"    {\n");
  append(L"      comp = accepted ? 1 : -1;\n");
  append(L"    }\n");
  append(L"    else\n");
  append(L"    {\n");
  append(L"      comp = e0 - other.e0;\n");
  append(L"      if (comp == 0)\n");
  append(L"        comp = id - other.id;\n");
  append(L"    }\n");
  append(L"    return comp >= 0;\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  bool operator==(const ParsingThread &other)\n");
  append(L"  {\n");
  append(L"    if (accepted != other.accepted) return false;\n");
  append(L"    if (b1 != other.b1) return false;\n");
  append(L"    if (e1 != other.e1) return false;\n");
  append(L"    if (l1 != other.l1) return false;\n");
  append(L"    if (state != other.state) return false;\n");
  append(L"    if (action != other.action) return false;\n");
  append(L"    if (! stack->equals(other.stack)) return false;\n");
  append(L"    return true;\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  int parse()\n");
  append(L"  {");
                                                            #line 1429 "PrintCpp.cpp.template"
                                                              increaseIndent();
                                                            }

                                                            void PrintCpp::openMethod(const wchar_t *type,
                                                                                      const wchar_t *prefix,
                                                                                      const wchar_t *name,
                                                                                      const wchar_t *args,
                                                                                      bool constant,
                                                                                      const wchar_t *clazz)
                                                            {
                                                            #line 2087 "PrintCpp.cpp"
  append(L"\n");
                                                            #line 1440 "PrintCpp.cpp.template"
                                                              print(prefix);
                                                              print(type);
                                                              print(name);
                                                            #line 2093 "PrintCpp.cpp"
  append(L"(");
                                                            #line 1443 "PrintCpp.cpp.template"
                                                              print(args);
                                                            #line 2097 "PrintCpp.cpp"
  append(L")");
                                                            #line 1444 "PrintCpp.cpp.template"
                                                              if (constant)
                                                              {
                                                            #line 2102 "PrintCpp.cpp"
  append(L" const");
                                                            #line 1446 "PrintCpp.cpp.template"
                                                              }
                                                            }

                                                            void PrintCpp::privateVars()
                                                            {
                                                            #line 2110 "PrintCpp.cpp"
  append(L"\n");
  append(L"  int ");
                                                            #line 1452 "PrintCpp.cpp.template"
                                                              if (! isLrParser && (grammar->k > 1 ||
                                                                                   memoization ||
                                                                                   ! grammar->decisionPoints.empty()))
                                                              {
                                                            #line 2118 "PrintCpp.cpp"
  append(L"lk,");
                                                            #line 1456 "PrintCpp.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 2124 "PrintCpp.cpp"
  append(L"   ");
                                                            #line 1459 "PrintCpp.cpp.template"
                                                              }
                                                            #line 2128 "PrintCpp.cpp"
  append(L" b0, e0;");
                                                            #line 1460 "PrintCpp.cpp.template"
                                                              for (size_t k = 1; k <= grammar->k; ++k)
                                                              {
                                                                wchar_t *asString = format.toString<wchar_t>(k);
                                                            #line 2134 "PrintCpp.cpp"
  append(L"\n");
  append(L"  int l");
                                                            #line 1464 "PrintCpp.cpp.template"
                                                                print(asString);
                                                            #line 2139 "PrintCpp.cpp"
  append(L", b");
                                                            #line 1465 "PrintCpp.cpp.template"
                                                                print(asString);
                                                            #line 2143 "PrintCpp.cpp"
  append(L", e");
                                                            #line 1466 "PrintCpp.cpp.template"
                                                                print(asString);
                                                            #line 2147 "PrintCpp.cpp"
  append(L";");
                                                            #line 1467 "PrintCpp.cpp.template"
                                                              }
                                                              if (hasBacktracking)
                                                              {
                                                            #line 2153 "PrintCpp.cpp"
  append(L"\n");
  append(L"  int bx, ex, sx, lx, tx;");
                                                            #line 1471 "PrintCpp.cpp.template"
                                                              }
                                                              if (isLrParser && ! useGlr)
                                                              {
                                                            #line 2160 "PrintCpp.cpp"
  append(L"\n");
  append(L"  std::vector<int> iStack;\n");
  append(L"  int top;");
                                                            #line 1476 "PrintCpp.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                                if (isLrParser)
                                                                {
                                                                  if (useGlr)
                                                                  {
                                                            #line 2172 "PrintCpp.cpp"
  append(L"\n");
  append(L"  int bw, bs, es;");
                                                            #line 1484 "PrintCpp.cpp.template"
                                                                  }
                                                            #line 2177 "PrintCpp.cpp"
  append(L"\n");
  append(L"  BottomUpEventHandler *eventHandler;");
                                                            #line 1486 "PrintCpp.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 2184 "PrintCpp.cpp"
  append(L"\n");
  append(L"  EventHandler *eventHandler;");
                                                            #line 1490 "PrintCpp.cpp.template"
                                                                }
                                                              }
                                                              if (memoization)
                                                              {
                                                            #line 2192 "PrintCpp.cpp"
  append(L"\n");
  append(L"  std::map<int, int> memo;");
                                                            #line 1495 "PrintCpp.cpp.template"
                                                                if (grammar->noThrow)
                                                                {
                                                            #line 2198 "PrintCpp.cpp"
  append(L"\n");
  append(L"  bool viable;");
                                                            #line 1498 "PrintCpp.cpp.template"
                                                                }
                                                              }
                                                              if (memoization)
                                                              {
                                                                int bits = Math::bits(grammar->conflictCount);
                                                            #line 2207 "PrintCpp.cpp"
  append(L"\n");
  append(L"\n");
  append(L"  void memoize(int i, int e, int v)\n");
  append(L"  {\n");
  append(L"    memo[(e << ");
                                                            #line 1507 "PrintCpp.cpp.template"
                                                                print(format.toString<wchar_t>(bits));
                                                            #line 2215 "PrintCpp.cpp"
  append(L") + i] = v;\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  int memoized(int i, int e)\n");
  append(L"  {\n");
  append(L"    std::map<int, int>::iterator v = memo.find((e << ");
                                                            #line 1513 "PrintCpp.cpp.template"
                                                                print(format.toString<wchar_t>(bits));
                                                            #line 2224 "PrintCpp.cpp"
  append(L") + i);\n");
  append(L"    return v != memo.end() ? v->second : 0;\n");
  append(L"  }");
                                                            #line 1516 "PrintCpp.cpp.template"
                                                              }
                                                            #line 2230 "PrintCpp.cpp"
  append(L"\n");
                                                            #line 1518 "PrintCpp.cpp.template"
                                                            }

                                                            void PrintCpp::printReadMethod()
                                                            {
                                                              if (main || performanceTest)
                                                              {
                                                            #line 2239 "PrintCpp.cpp"
  append(L"\n");
  append(L"class FileNotFound\n");
  append(L"{\n");
  append(L"public:\n");
  append(L"  FileNotFound(std::string name) : filename(name) {}\n");
  append(L"  const std::string &getFilename() const {return filename;}\n");
  append(L"\n");
  append(L"private:\n");
  append(L"  std::string filename;\n");
  append(L"};\n");
                                                            #line 1534 "PrintCpp.cpp.template"
                                                              }
                                                              if (main || performanceTest || tree || trace)
                                                              {
                                                            #line 2254 "PrintCpp.cpp"
  append(L"\n");
  append(L"class MalformedInputException\n");
  append(L"{\n");
  append(L"public:\n");
  append(L"  MalformedInputException(size_t offset) : offset(offset) {}\n");
  append(L"  size_t getOffset() const {return offset;}\n");
  append(L"\n");
  append(L"private:\n");
  append(L"  size_t offset;\n");
  append(L"};\n");
                                                            #line 1547 "PrintCpp.cpp.template"
                                                                if (! parseChars)
                                                                {
                                                            #line 2268 "PrintCpp.cpp"
  append(L"\n");
  append(L"class Utf8Encoder\n");
  append(L"{\n");
  append(L"public:\n");
  append(L"  static std::string encode(const wchar_t *unencoded)\n");
  append(L"  {\n");
  append(L"    return encode(unencoded, wcslen(unencoded));\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  static std::string encode(const wchar_t *unencoded, size_t size)\n");
  append(L"  {\n");
  append(L"    std::string encoded;\n");
  append(L"    encoded.reserve(size + 3);\n");
  append(L"\n");
  append(L"    for (size_t i = 0; i < size; ++i)\n");
  append(L"    {\n");
  append(L"      if (encoded.size() + 4 >= encoded.capacity()) encoded.reserve(encoded.capacity() * 2);\n");
  append(L"\n");
  append(L"      int w = unencoded[i];\n");
  append(L"      if (w < 0x80)\n");
  append(L"      {\n");
  append(L"        encoded += w;\n");
  append(L"      }\n");
  append(L"      else if (w < 0x800)\n");
  append(L"      {\n");
  append(L"        encoded += 0xc0 | (w >> 6);\n");
  append(L"        encoded += 0x80 | (w & 0x3f);\n");
  append(L"      }\n");
  append(L"      else if (w < 0xd800)\n");
  append(L"      {\n");
  append(L"        encoded += 0xe0 | ( w          >> 12);\n");
  append(L"        encoded += 0x80 | ((w & 0xfff) >>  6);\n");
  append(L"        encoded += 0x80 | ( w &  0x3f       );\n");
  append(L"      }\n");
  append(L"      else if (w < 0xe000)\n");
  append(L"      {\n");
  append(L"        if (++i >= size)\n");
  append(L"        {\n");
  append(L"          throw MalformedInputException(i - 1);\n");
  append(L"        }\n");
  append(L"        int w2 = unencoded[i];\n");
  append(L"        if (w2 < 0xdc00 || w2 > 0xdfff)\n");
  append(L"        {\n");
  append(L"          throw MalformedInputException(i - 1);\n");
  append(L"        }\n");
  append(L"        w = (((w  & 0x3ff) << 10) | (w2 & 0x3ff)) + 0x10000;\n");
  append(L"        encoded += 0xf0 | ( w            >> 18);\n");
  append(L"        encoded += 0x80 | ((w & 0x3ffff) >> 12);\n");
  append(L"        encoded += 0x80 | ((w &   0xfff) >>  6);\n");
  append(L"        encoded += 0x80 | ( w &    0x3f       );\n");
  append(L"      }\n");
  append(L"      else if (w < 0x10000)\n");
  append(L"      {\n");
  append(L"        encoded += 0xe0 | ( w          >> 12);\n");
  append(L"        encoded += 0x80 | ((w & 0xfff) >>  6);\n");
  append(L"        encoded += 0x80 | ( w &  0x3f       );\n");
  append(L"      }\n");
  append(L"      else if (w < 0x110000)\n");
  append(L"      {\n");
  append(L"        encoded += 0xf0 | ( w            >> 18);\n");
  append(L"        encoded += 0x80 | ((w & 0x3ffff) >> 12);\n");
  append(L"        encoded += 0x80 | ((w &   0xfff) >>  6);\n");
  append(L"        encoded += 0x80 | ( w &    0x3f       );\n");
  append(L"      }\n");
  append(L"      else\n");
  append(L"      {\n");
  append(L"        throw MalformedInputException(i);\n");
  append(L"      }\n");
  append(L"    }\n");
  append(L"    return encoded;\n");
  append(L"  }\n");
  append(L"};\n");
                                                            #line 1621 "PrintCpp.cpp.template"
                                                                }
                                                              }
                                                              if (main || performanceTest)
                                                              {
                                                                if (! parseChars)
                                                                {
                                                            #line 2348 "PrintCpp.cpp"
  append(L"\n");
  append(L"class Utf8Decoder\n");
  append(L"{\n");
  append(L"public:\n");
  append(L"  static std::wstring decode(const char *string)\n");
  append(L"  {\n");
  append(L"    return decode(string, strlen(string));\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  static std::wstring decode(const char *string, size_t size)\n");
  append(L"  {\n");
  append(L"    std::wstring decoded;\n");
  append(L"    decoded.reserve(size + 1);\n");
  append(L"\n");
  append(L"    for (size_t consumed = 0; consumed < size; )\n");
  append(L"    {\n");
  append(L"      if (decoded.size() + 2 >= decoded.capacity()) decoded.reserve(decoded.capacity() * 2);\n");
  append(L"\n");
  append(L"      size_t bytes;\n");
  append(L"      int codepoint = decodeChar(string + consumed, &bytes);\n");
  append(L"\n");
  append(L"      if (bytes == 0)\n");
  append(L"      {\n");
  append(L"        throw MalformedInputException(consumed);\n");
  append(L"      }\n");
  append(L"\n");
  append(L"      consumed += bytes;\n");
  append(L"\n");
  append(L"      if (codepoint < 0x10000)\n");
  append(L"      {\n");
  append(L"        decoded += codepoint;\n");
  append(L"      }\n");
  append(L"      else\n");
  append(L"      {\n");
  append(L"        codepoint -= 0x10000;\n");
  append(L"        decoded += 0x0d800 | (codepoint >> 10);\n");
  append(L"        decoded += 0x0dc00 | (codepoint & 0x3ff);\n");
  append(L"      }\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    return decoded;\n");
  append(L"  }\n");
  append(L"\n");
  append(L"private:\n");
  append(L"  static int decodeChar(const char *input, size_t *size)\n");
  append(L"  {\n");
  append(L"    int codepoint = input[0];\n");
  append(L"    if ((codepoint & 0x80) == 0)\n");
  append(L"    {\n");
  append(L"      *size = 1;\n");
  append(L"    }\n");
  append(L"    else if (   (codepoint & 0x60) == 0x40\n");
  append(L"             && (input[1]  & 0xc0) == 0x80)\n");
  append(L"    {\n");
  append(L"      codepoint = ((codepoint & 0x1f) << 6)\n");
  append(L"                |  (input[1]  & 0x3f);\n");
  append(L"      *size = codepoint < 0x80 ? 0 : 2;\n");
  append(L"    }\n");
  append(L"    else if (   (codepoint & 0x70) == 0x60\n");
  append(L"             && (input[1]  & 0xc0) == 0x80\n");
  append(L"             && (input[2]  & 0xc0) == 0x80)\n");
  append(L"    {\n");
  append(L"      codepoint = ((codepoint &  0xf) << 12)\n");
  append(L"                | ((input[1]  & 0x3f) <<  6)\n");
  append(L"                |  (input[2]  & 0x3f);\n");
  append(L"      *size = codepoint < 0x800 ? 0 : 3;\n");
  append(L"    }\n");
  append(L"    else if (   (codepoint & 0x78) == 0x70\n");
  append(L"             && (input[1]  & 0xc0) == 0x80\n");
  append(L"             && (input[2]  & 0xc0) == 0x80\n");
  append(L"             && (input[3]  & 0xc0) == 0x80)\n");
  append(L"    {\n");
  append(L"      codepoint  = ((codepoint &  0x7) << 18)\n");
  append(L"                 | ((input[1]  & 0x3f) << 12)\n");
  append(L"                 | ((input[2]  & 0x3f) <<  6)\n");
  append(L"                 | ( input[3]  & 0x3f       );\n");
  append(L"      *size = codepoint < 0x10000 || codepoint > 0x10ffff ? 0 : 4;\n");
  append(L"    }\n");
  append(L"    else\n");
  append(L"    {\n");
  append(L"      *size = 0;\n");
  append(L"    }\n");
  append(L"    return codepoint;\n");
  append(L"  }\n");
  append(L"};\n");
                                                            #line 1712 "PrintCpp.cpp.template"
                                                                }
                                                            #line 2436 "PrintCpp.cpp"
  append(L"\n");
  append(L"static std::");
                                                            #line 1714 "PrintCpp.cpp.template"
                                                                if (! parseChars) append(L"w");
                                                            #line 2441 "PrintCpp.cpp"
  append(L"string read(const char *input)\n");
  append(L"{\n");
  append(L"  size_t l = strlen(input);\n");
  append(L"  if (l > 0 && input[0] == '{' && input[l - 1] == '}')\n");
  append(L"  {\n");
  append(L"    return ");
                                                            #line 1720 "PrintCpp.cpp.template"
                                                                if (parseChars)
                                                                {
                                                            #line 2451 "PrintCpp.cpp"
  append(L"std::string");
                                                            #line 1722 "PrintCpp.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 2457 "PrintCpp.cpp"
  append(L"Utf8Decoder::decode");
                                                            #line 1725 "PrintCpp.cpp.template"
                                                                }
                                                            #line 2461 "PrintCpp.cpp"
  append(L"(input + 1, l - 2);\n");
  append(L"  }\n");
  append(L"  else\n");
  append(L"  {\n");
  append(L"    FILE *file = fopen(input, \"rb\");\n");
  append(L"    if (file == 0)\n");
  append(L"    {\n");
  append(L"      throw FileNotFound(std::string(input));\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    std::string content;\n");
  append(L"    content.reserve(4096);\n");
  append(L"\n");
  append(L"    for (int c = getc(file); c != EOF; c = getc(file))\n");
  append(L"    {\n");
  append(L"      if (content.size() + 1 >= content.capacity()) content.reserve(content.capacity() * 2);\n");
  append(L"      content += c;\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    fclose(file);\n");
  append(L"\n");
  append(L"    if (content.size() >= 3\n");
  append(L"     && (unsigned char) content[0] == 0xef\n");
  append(L"     && (unsigned char) content[1] == 0xbb\n");
  append(L"     && (unsigned char) content[2] == 0xbf)\n");
  append(L"    {\n");
  append(L"      content.erase(0, 3);\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    return ");
                                                            #line 1755 "PrintCpp.cpp.template"
                                                                if (! parseChars)
                                                                {
                                                            #line 2495 "PrintCpp.cpp"
  append(L"Utf8Decoder::decode(");
                                                            #line 1757 "PrintCpp.cpp.template"
                                                                }
                                                            #line 2499 "PrintCpp.cpp"
  append(L"content");
                                                            #line 1758 "PrintCpp.cpp.template"
                                                                if (! parseChars)
                                                                {
                                                            #line 2504 "PrintCpp.cpp"
  append(L".c_str())");
                                                            #line 1760 "PrintCpp.cpp.template"
                                                                }
                                                            #line 2508 "PrintCpp.cpp"
  append(L";\n");
  append(L"  }\n");
  append(L"}\n");
                                                            #line 1764 "PrintCpp.cpp.template"
                                                              }
                                                            }

                                                            void PrintCpp::printFileProcessor()
                                                            {
                                                            }

                                                            void PrintCpp::printSimpleMain()
                                                            {
                                                            #line 2522 "PrintCpp.cpp"
  append(L"\n");
  append(L"  static int main(int argc, char **argv)\n");
  append(L"  {\n");
  append(L"    int returnCode = 0;\n");
  append(L"\n");
  append(L"    if (argc < 2)\n");
  append(L"    {\n");
  append(L"      fprintf(stderr, \"Usage: %s ");
                                                            #line 1780 "PrintCpp.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 2534 "PrintCpp.cpp"
  append(L"[-i] ");
                                                            #line 1782 "PrintCpp.cpp.template"
                                                              }
                                                            #line 2538 "PrintCpp.cpp"
  append(L"INPUT...\\n\", argv[0]);\n");
  append(L"      fprintf(stderr, \"\\n\");\n");
  append(L"      fprintf(stderr, \"  parse INPUT, which is either a filename or literal text enclosed in curly braces\\n\");");
                                                            #line 1786 "PrintCpp.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 2545 "PrintCpp.cpp"
  append(L"\n");
  append(L"      fprintf(stderr, \"\\n\");\n");
  append(L"      fprintf(stderr, \"  Option:\\n\");\n");
  append(L"      fprintf(stderr, \"    -i     indented parse tree\\n\");");
                                                            #line 1791 "PrintCpp.cpp.template"
                                                              }
                                                            #line 2552 "PrintCpp.cpp"
  append(L"\n");
  append(L"    }\n");
  append(L"    else\n");
  append(L"    {\n");
  append(L"#ifdef _WIN32\n");
  append(L"      _setmode(1, O_BINARY);\n");
  append(L"#endif\n");
                                                            #line 1799 "PrintCpp.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 2563 "PrintCpp.cpp"
  append(L"\n");
  append(L"      bool indent = false;");
                                                            #line 1802 "PrintCpp.cpp.template"
                                                              }
                                                            #line 2568 "PrintCpp.cpp"
  append(L"\n");
  append(L"      for (int i = 1; i < argc; ++i)\n");
  append(L"      {");
                                                            #line 1805 "PrintCpp.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 2575 "PrintCpp.cpp"
  append(L"\n");
  append(L"        if (strcmp(argv[i], \"-i\") == 0)\n");
  append(L"        {\n");
  append(L"          indent = true;\n");
  append(L"          continue;\n");
  append(L"        }");
                                                            #line 1812 "PrintCpp.cpp.template"
                                                              }
                                                            #line 2584 "PrintCpp.cpp"
  append(L"\n");
  append(L"        try\n");
  append(L"        {");
                                                            #line 1815 "PrintCpp.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 2591 "PrintCpp.cpp"
  append(L"\n");
  append(L"          XmlSerializer s(indent);");
                                                            #line 1818 "PrintCpp.cpp.template"
                                                              }
                                                            #line 2596 "PrintCpp.cpp"
  append(L"\n");
  append(L"          std::");
                                                            #line 1820 "PrintCpp.cpp.template"
                                                              if (! parseChars) append(L"w");
                                                            #line 2601 "PrintCpp.cpp"
  append(L"string input = read(argv[i]);");
                                                            #line 1821 "PrintCpp.cpp.template"
                                                              if (tree && isLrParser)
                                                              {
                                                            #line 2606 "PrintCpp.cpp"
  append(L"\n");
  append(L"          ParseTreeBuilder t;");
                                                            #line 1824 "PrintCpp.cpp.template"
                                                              }
                                                            #line 2611 "PrintCpp.cpp"
  append(L"\n");
  append(L"          ");
                                                            #line 1826 "PrintCpp.cpp.template"
                                                              print(className.c_str());
                                                            #line 2616 "PrintCpp.cpp"
  append(L" parser(input.c_str()");
                                                            #line 1827 "PrintCpp.cpp.template"
                                                              if (tree)
                                                              {
                                                                if (isLrParser)
                                                                {
                                                            #line 2623 "PrintCpp.cpp"
  append(L", &t");
                                                            #line 1831 "PrintCpp.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 2629 "PrintCpp.cpp"
  append(L", &s");
                                                            #line 1834 "PrintCpp.cpp.template"
                                                                }
                                                              }
                                                            #line 2634 "PrintCpp.cpp"
  append(L");\n");
  append(L"          try\n");
  append(L"          {");
                                                            #line 1838 "PrintCpp.cpp.template"
                                                              if (trace)
                                                              {
                                                            #line 2641 "PrintCpp.cpp"
  append(L"\n");
  append(L"            fprintf(stderr, \"<?xml version=\\\"1.0\\\" encoding=\\\"UTF-8\\\"?>\\n\");\n");
  append(L"            fprintf(stderr, \"<trace>\\n\");");
                                                            #line 1842 "PrintCpp.cpp.template"
                                                              }
                                                            #line 2647 "PrintCpp.cpp"
  append(L"\n");
  append(L"            parser.");
                                                            #line 1844 "PrintCpp.cpp.template"
                                                              print(methodPrefix);
                                                              print(Format::acceptableName<WString>(grammar->startSymbol()->name).c_str());
                                                            #line 2653 "PrintCpp.cpp"
  append(L"();");
                                                            #line 1846 "PrintCpp.cpp.template"
                                                              if (trace)
                                                              {
                                                            #line 2658 "PrintCpp.cpp"
  append(L"\n");
  append(L"            fprintf(stderr, \"</trace>\\n\");");
                                                            #line 1849 "PrintCpp.cpp.template"
                                                              }
                                                              if (tree && isLrParser)
                                                              {
                                                            #line 2665 "PrintCpp.cpp"
  append(L"\n");
  append(L"            t.serialize(&s);");
                                                            #line 1853 "PrintCpp.cpp.template"
                                                              }
                                                            #line 2670 "PrintCpp.cpp"
  append(L"\n");
  append(L"          }\n");
  append(L"          catch (ParseException &pe)\n");
  append(L"          {");
                                                            #line 1857 "PrintCpp.cpp.template"
                                                              if (tree)
                                                              {
                                                                if (rejectsAmbiguity())
                                                                {
                                                            #line 2680 "PrintCpp.cpp"
  append(L"\n");
  append(L"            if (pe.isAmbiguousInput())\n");
  append(L"            {\n");
  append(L"              pe.serialize(&s);\n");
  append(L"              putchar('\\n');\n");
  append(L"              fflush(stdout);\n");
  append(L"            }");
                                                            #line 1867 "PrintCpp.cpp.template"
                                                                }
                                                            #line 2690 "PrintCpp.cpp"
  append(L"\n");
  append(L"            fprintf(stderr, \"\\n\");");
                                                            #line 1869 "PrintCpp.cpp.template"
                                                              }
                                                            #line 2695 "PrintCpp.cpp"
  append(L"\n");
  append(L"            fprintf(stderr, \"%s\\n\", ");
                                                            #line 1871 "PrintCpp.cpp.template"
                                                              if (! parseChars)
                                                              {
                                                            #line 2701 "PrintCpp.cpp"
  append(L"Utf8Encoder::encode(");
                                                            #line 1873 "PrintCpp.cpp.template"
                                                              }
                                                            #line 2705 "PrintCpp.cpp"
  append(L"parser.getErrorMessage(pe).c_str()");
                                                            #line 1875 "PrintCpp.cpp.template"
                                                              if (! parseChars)
                                                              {
                                                            #line 2710 "PrintCpp.cpp"
  append(L").c_str()");
                                                            #line 1878 "PrintCpp.cpp.template"
                                                              }
                                                            #line 2714 "PrintCpp.cpp"
  append(L");\n");
  append(L"            returnCode = 1;\n");
  append(L"            break;\n");
  append(L"          }\n");
  append(L"        }\n");
  append(L"        catch (FileNotFound &fnf)\n");
  append(L"        {\n");
  append(L"          fprintf(stderr, \"error: file not found: %s\\n\", fnf.getFilename().c_str());\n");
  append(L"          returnCode = 1;\n");
  append(L"          break;\n");
  append(L"        }\n");
  append(L"        catch (MalformedInputException &mie)\n");
  append(L"        {\n");
  append(L"          fprintf(stderr, \"error: UTF-8 decoding error in %s at offset %d\\n\",\n");
  append(L"            argv[i], static_cast<int>(mie.getOffset()));\n");
  append(L"          returnCode = 1;\n");
  append(L"          break;\n");
  append(L"        }\n");
  append(L"      }\n");
  append(L"    }\n");
  append(L"    return returnCode;\n");
  append(L"  }\n");
                                                            #line 1901 "PrintCpp.cpp.template"
                                                            }

                                                            void PrintCpp::printPerformanceMain()
                                                            {
                                                            #line 2742 "PrintCpp.cpp"
  append(L"\n");
  append(L"  static int main(int argc, char **argv)\n");
  append(L"  {\n");
  append(L"    errorCount = 0;\n");
  append(L"\n");
  append(L"    if (argc < 2)\n");
  append(L"    {\n");
  append(L"      fprintf(stdout, \"Usage: %s [-q] [-r N] [-t N] ENDING...\\n\", argv[0]);\n");
  append(L"      fprintf(stdout, \"\\n\");\n");
  append(L"      fprintf(stdout, \"  parse all files that have names ending with ENDING, in current dir and below,\\n\");\n");
  append(L"      fprintf(stdout, \"  and display performance summary.\\n\");\n");
  append(L"      fprintf(stdout, \"\\n\");\n");
  append(L"      fprintf(stdout, \"  -q     do not show file names\\n\");\n");
  append(L"      fprintf(stdout, \"  -r N   repeat N times\\n\");\n");
  append(L"      fprintf(stdout, \"  -t N   repeat until N seconds have elapsed\\n\");\n");
  append(L"    }\n");
  append(L"    else\n");
  append(L"    {\n");
  append(L"      quiet = false;\n");
  append(L"      parsed = 0l;\n");
  append(L"\n");
  append(L"      int repeat = 1;\n");
  append(L"      int timeout = 0;\n");
  append(L"      int i;\n");
  append(L"\n");
  append(L"      for (i = 1; i < argc && argv[i][0] == '-'; ++i)\n");
  append(L"      {\n");
  append(L"        switch (strlen(argv[i]) == 2 ? argv[i][1] : ' ')\n");
  append(L"        {\n");
  append(L"        case 'q':\n");
  append(L"          quiet = true;\n");
  append(L"          break;\n");
  append(L"        case 'r':\n");
  append(L"          repeat = strtol(argv[++i], 0, 0);\n");
  append(L"          timeout = 0;\n");
  append(L"          break;\n");
  append(L"        case 't':\n");
  append(L"          repeat = 0;\n");
  append(L"          timeout = CLOCKS_PER_SEC * strtol(argv[++i], 0, 0);\n");
  append(L"          break;\n");
  append(L"        default:\n");
  append(L"          printf(\"invalid option: %s\\n\", argv[i]);\n");
  append(L"          exit(1);\n");
  append(L"        }\n");
  append(L"      }\n");
  append(L"\n");
  append(L"      clock_t start = clock();\n");
  append(L"\n");
  append(L"      for (; i < argc; ++i)\n");
  append(L"      {\n");
  append(L"        FileParser fp(\".\", argv[i]);\n");
  append(L"        if (fp.run() < 1)\n");
  append(L"        {\n");
  append(L"          fprintf(stderr, \"no files found that have names ending with \\\"%s\\\"\\n\", argv[i]);\n");
  append(L"        }\n");
  append(L"      }\n");
  append(L"\n");
  append(L"      if (! parsers.empty())\n");
  append(L"      {\n");
  append(L"        long msec = (long) (1000.0 * (clock() - start) / CLOCKS_PER_SEC);\n");
  append(L"\n");
  append(L"        if (! quiet) fprintf(stdout, \"\\n\");\n");
  append(L"        fprintf(stdout, \"loaded %d file%s in %d msec\\n\",\n");
  append(L"                static_cast<int>(parsers.size()), parsers.size() == 1 ? \"\" : \"s\",\n");
  append(L"                (int) msec);\n");
  append(L"        if (! quiet) fprintf(stdout, \"\\n\");\n");
  append(L"        fflush(stdout);\n");
  append(L"\n");
  append(L"        start = clock();\n");
  append(L"\n");
  append(L"        for (i = 0; ; ++i)\n");
  append(L"        {\n");
  append(L"          if (repeat != 0 && i >= repeat) break;\n");
  append(L"          if (timeout != 0 && clock() - start >= timeout) break;\n");
  append(L"\n");
  append(L"          for (ParseJobs::iterator job = parsers.begin(); job != parsers.end(); ++job)\n");
  append(L"          {\n");
  append(L"            if (job->parser != 0)\n");
  append(L"            {\n");
  append(L"              try\n");
  append(L"              {\n");
  append(L"                if (! quiet) fprintf(stdout, \"parsing %s\", ");
                                                            #line 1986 "PrintCpp.cpp.template"
                                                              if (! parseChars)
                                                              {
                                                            #line 2828 "PrintCpp.cpp"
  append(L"Utf8Encoder::encode(");
                                                            #line 1989 "PrintCpp.cpp.template"
                                                              }
                                                            #line 2832 "PrintCpp.cpp"
  append(L"job->name->c_str()");
                                                            #line 1991 "PrintCpp.cpp.template"
                                                              if (! parseChars)
                                                              {
                                                            #line 2837 "PrintCpp.cpp"
  append(L").c_str()");
                                                            #line 1994 "PrintCpp.cpp.template"
                                                              }
                                                            #line 2841 "PrintCpp.cpp"
  append(L");\n");
  append(L"                job->parser->");
                                                            #line 1996 "PrintCpp.cpp.template"
                                                              if (useGlr)
                                                              {
                                                            #line 2847 "PrintCpp.cpp"
  append(L"thread->");
                                                            #line 1998 "PrintCpp.cpp.template"
                                                              }
                                                            #line 2851 "PrintCpp.cpp"
  append(L"reset(0, 0, 0);\n");
  append(L"                job->parser->");
                                                            #line 2000 "PrintCpp.cpp.template"
                                                              print(methodPrefix);
                                                              print(Format::acceptableName<WString>(grammar->startSymbol()->name).c_str());
                                                            #line 2857 "PrintCpp.cpp"
  append(L"();");
                                                            #line 2002 "PrintCpp.cpp.template"
                                                              if (useGlr)
                                                              {
                                                            #line 2862 "PrintCpp.cpp"
  append(L"\n");
  append(L"                job->parser->thread->cleanup();");
                                                            #line 2005 "PrintCpp.cpp.template"
                                                              }
                                                            #line 2867 "PrintCpp.cpp"
  append(L"\n");
  append(L"                if (! quiet) fprintf(stdout, \"\\n\");");
                                                            #line 2007 "PrintCpp.cpp.template"
                                                              if (tree)
                                                              {
                                                                if (isLrParser)
                                                                {
                                                            #line 2875 "PrintCpp.cpp"
  append(L"\n");
  append(L"                job->parseTreeBuilder->serialize(job->contentCounter);");
                                                            #line 2013 "PrintCpp.cpp.template"
                                                                }
                                                            #line 2880 "PrintCpp.cpp"
  append(L"\n");
  append(L"                if (job->contentCounter->getLength() != job->content->size())\n");
  append(L"                {\n");
  append(L"                  fprintf(stderr, \"content counter saw %d but input length is %d\\n\", job->contentCounter->getLength(), job->content->size());\n");
  append(L"                  exit(1);\n");
  append(L"                }");
                                                            #line 2019 "PrintCpp.cpp.template"
                                                              }
                                                            #line 2889 "PrintCpp.cpp"
  append(L"\n");
  append(L"                parsed += job->content->size();\n");
  append(L"              }\n");
  append(L"              catch (ParseException &pe)\n");
  append(L"              {\n");
  append(L"                ++errorCount;\n");
  append(L"                if (quiet) fprintf(stdout, \"parsing %s\", ");
                                                            #line 2026 "PrintCpp.cpp.template"
                                                              if (! parseChars)
                                                              {
                                                            #line 2900 "PrintCpp.cpp"
  append(L"Utf8Encoder::encode(");
                                                            #line 2029 "PrintCpp.cpp.template"
                                                              }
                                                            #line 2904 "PrintCpp.cpp"
  append(L"job->name->c_str()");
                                                            #line 2031 "PrintCpp.cpp.template"
                                                              if (! parseChars)
                                                              {
                                                            #line 2909 "PrintCpp.cpp"
  append(L").c_str()");
                                                            #line 2034 "PrintCpp.cpp.template"
                                                              }
                                                            #line 2913 "PrintCpp.cpp"
  append(L");\n");
  append(L"                fprintf(stdout, \": error:\\n%s\", ");
                                                            #line 2036 "PrintCpp.cpp.template"
                                                              if (! parseChars)
                                                              {
                                                            #line 2919 "PrintCpp.cpp"
  append(L"Utf8Encoder::encode(");
                                                            #line 2039 "PrintCpp.cpp.template"
                                                              }
                                                            #line 2923 "PrintCpp.cpp"
  append(L"job->parser->getErrorMessage(pe).c_str()");
                                                            #line 2041 "PrintCpp.cpp.template"
                                                              if (! parseChars)
                                                              {
                                                            #line 2928 "PrintCpp.cpp"
  append(L").c_str()");
                                                            #line 2044 "PrintCpp.cpp.template"
                                                              }
                                                            #line 2932 "PrintCpp.cpp"
  append(L");\n");
  append(L"                delete job->parser;\n");
  append(L"                job->parser = 0;\n");
  append(L"              }\n");
  append(L"            }\n");
  append(L"          }\n");
  append(L"        }\n");
  append(L"\n");
  append(L"        msec = (long) (1000.0 * (clock() - start) / CLOCKS_PER_SEC);\n");
  append(L"\n");
  append(L"        double mbPerSec = msec == 0 ? 0e0 : parsed / 1024e0 / 1024e0 * 1000e0 / msec;\n");
  append(L"        if (! quiet) fprintf(stdout, \"\\n\");\n");
  append(L"        const char *format = \"parsed %lld byte%s in %d msec\";\n");
  append(L"        fprintf(stdout, format, parsed, parsed == 1 ? \"\" : \"s\", (int) msec);\n");
  append(L"        if (mbPerSec != 0e0) fprintf(stdout, \" (%0.2f MB/sec)\", mbPerSec);\n");
  append(L"        fprintf(stdout, \"\\n\");\n");
  append(L"        fprintf(stdout, \"%d error%s\\n\", errorCount, errorCount == 1 ? \"\" : \"s\");\n");
  append(L"\n");
  append(L"        for (ParseJobs::iterator job = parsers.begin(); job != parsers.end(); ++job)\n");
  append(L"        {\n");
  append(L"          job->cleanup();\n");
  append(L"        }\n");
  append(L"      }\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    return errorCount == 0 ? 0 : 1;\n");
  append(L"  }\n");
                                                            #line 2072 "PrintCpp.cpp.template"
                                                            }

                                                            void PrintCpp::printPerformanceCode()
                                                            {
                                                              if (tree)
                                                              {
                                                            #line 2967 "PrintCpp.cpp"
  append(L"\n");
  append(L"  class ContentCounter : public EventHandler\n");
  append(L"  {\n");
  append(L"  public:\n");
  append(L"    ContentCounter() : length(0) {}\n");
  append(L"    size_t getLength() const {return length;}\n");
  append(L"\n");
  append(L"    void reset(");
                                                            #line 2085 "PrintCpp.cpp.template"
                                                                print(stringType());
                                                            #line 2978 "PrintCpp.cpp"
  append(L"string) {length = 0;}\n");
  append(L"    void startNonterminal(");
                                                            #line 2087 "PrintCpp.cpp.template"
                                                                print(stringType());
                                                            #line 2983 "PrintCpp.cpp"
  append(L"name, int begin)  {}\n");
  append(L"    void endNonterminal(");
                                                            #line 2089 "PrintCpp.cpp.template"
                                                                print(stringType());
                                                            #line 2988 "PrintCpp.cpp"
  append(L"name, int end)  {}\n");
  append(L"    void terminal(");
                                                            #line 2091 "PrintCpp.cpp.template"
                                                                print(stringType());
                                                            #line 2993 "PrintCpp.cpp"
  append(L"name, int begin, int end)  {length += end - begin;}\n");
  append(L"    void whitespace(int begin, int end) {length += end - begin;}\n");
  append(L"\n");
  append(L"  private:\n");
  append(L"    size_t length;\n");
  append(L"  };\n");
                                                            #line 2098 "PrintCpp.cpp.template"
                                                              }
                                                            #line 3002 "PrintCpp.cpp"
  append(L"\n");
  append(L"  class ParseJob\n");
  append(L"  {\n");
  append(L"  public:\n");
  append(L"    ParseJob(const std::");
                                                            #line 2103 "PrintCpp.cpp.template"
                                                              if (! parseChars) append(L"w");
                                                            #line 3010 "PrintCpp.cpp"
  append(L"string &n, const std::");
                                                            #line 2104 "PrintCpp.cpp.template"
                                                              if (! parseChars) append(L"w");
                                                            #line 3014 "PrintCpp.cpp"
  append(L"string &c)\n");
  append(L"    : name(0), content(0), parser(0)");
                                                            #line 2106 "PrintCpp.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 3020 "PrintCpp.cpp"
  append(L", contentCounter(0)");
                                                            #line 2108 "PrintCpp.cpp.template"
                                                                if (isLrParser)
                                                                {
                                                            #line 3025 "PrintCpp.cpp"
  append(L", parseTreeBuilder(0)");
                                                            #line 2111 "PrintCpp.cpp.template"
                                                                }
                                                              }
                                                            #line 3030 "PrintCpp.cpp"
  append(L"\n");
  append(L"    {\n");
  append(L"      name = new std::");
                                                            #line 2115 "PrintCpp.cpp.template"
                                                              if (! parseChars) append(L"w");
                                                            #line 3036 "PrintCpp.cpp"
  append(L"string(n);\n");
  append(L"      content = new std::");
                                                            #line 2117 "PrintCpp.cpp.template"
                                                              if (! parseChars) append(L"w");
                                                            #line 3041 "PrintCpp.cpp"
  append(L"string(c);");
                                                            #line 2118 "PrintCpp.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 3046 "PrintCpp.cpp"
  append(L"\n");
  append(L"      contentCounter = new ContentCounter();");
                                                            #line 2121 "PrintCpp.cpp.template"
                                                                if (isLrParser)
                                                                {
                                                            #line 3052 "PrintCpp.cpp"
  append(L"\n");
  append(L"      parseTreeBuilder = new ParseTreeBuilder();");
                                                            #line 2124 "PrintCpp.cpp.template"
                                                                }
                                                              }
                                                            #line 3058 "PrintCpp.cpp"
  append(L"\n");
  append(L"      parser = new ");
                                                            #line 2127 "PrintCpp.cpp.template"
                                                              print(className.c_str());
                                                            #line 3063 "PrintCpp.cpp"
  append(L"(content->c_str()");
                                                            #line 2128 "PrintCpp.cpp.template"
                                                              if (tree)
                                                              {
                                                                if (isLrParser)
                                                                {
                                                            #line 3070 "PrintCpp.cpp"
  append(L", parseTreeBuilder");
                                                            #line 2132 "PrintCpp.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 3076 "PrintCpp.cpp"
  append(L", contentCounter");
                                                            #line 2135 "PrintCpp.cpp.template"
                                                                }
                                                              }
                                                            #line 3081 "PrintCpp.cpp"
  append(L");\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    void cleanup()\n");
  append(L"    {\n");
  append(L"      delete name;\n");
  append(L"      delete content;\n");
  append(L"      delete parser;");
                                                            #line 2144 "PrintCpp.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 3093 "PrintCpp.cpp"
  append(L"\n");
  append(L"      delete contentCounter;");
                                                            #line 2147 "PrintCpp.cpp.template"
                                                                if (isLrParser)
                                                                {
                                                            #line 3099 "PrintCpp.cpp"
  append(L"\n");
  append(L"      delete parseTreeBuilder;");
                                                            #line 2150 "PrintCpp.cpp.template"
                                                                }
                                                              }
                                                            #line 3105 "PrintCpp.cpp"
  append(L"\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    std::");
                                                            #line 2155 "PrintCpp.cpp.template"
                                                              if (! parseChars) append(L"w");
                                                            #line 3112 "PrintCpp.cpp"
  append(L"string *name;\n");
  append(L"    std::");
                                                            #line 2157 "PrintCpp.cpp.template"
                                                              if (! parseChars) append(L"w");
                                                            #line 3117 "PrintCpp.cpp"
  append(L"string *content;\n");
  append(L"    ");
                                                            #line 2159 "PrintCpp.cpp.template"
                                                              print(className.c_str());
                                                            #line 3122 "PrintCpp.cpp"
  append(L" *parser;");
                                                            #line 2160 "PrintCpp.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 3127 "PrintCpp.cpp"
  append(L"\n");
  append(L"    ContentCounter *contentCounter;");
                                                            #line 2163 "PrintCpp.cpp.template"
                                                                if (isLrParser)
                                                                {
                                                            #line 3133 "PrintCpp.cpp"
  append(L"\n");
  append(L"    ParseTreeBuilder *parseTreeBuilder;");
                                                            #line 2166 "PrintCpp.cpp.template"
                                                                }
                                                              }
                                                            #line 3139 "PrintCpp.cpp"
  append(L"\n");
  append(L"  };\n");
  append(L"\n");
  append(L"  typedef std::vector<ParseJob> ParseJobs;\n");
  append(L"\n");
  append(L"  static bool quiet;\n");
  append(L"  static int errorCount;\n");
  append(L"  static long long parsed;\n");
  append(L"  static ParseJobs parsers;\n");
  append(L"\n");
  append(L"  class FileProcessor\n");
  append(L"  {\n");
  append(L"  public:\n");
  append(L"    virtual int process(const char *path) = 0;\n");
  append(L"\n");
  append(L"#ifdef _WIN32\n");
  append(L"    bool endsWithI(const char *s1, const char *s2)\n");
  append(L"    {\n");
  append(L"      size_t l1 = strlen(s1);\n");
  append(L"      size_t l2 = strlen(s2);\n");
  append(L"      return l1 >= l2 && (stricmp(s1 + l1 - l2, s2) == 0);\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    int findfiles(const char *path, const char *filter)\n");
  append(L"    {\n");
  append(L"      int count = 0;\n");
  append(L"\n");
  append(L"      const char *pathWithoutDriveLetter = path[0] != 0 && path[1] == ':'\n");
  append(L"                                         ? path + 2\n");
  append(L"                                         : path;\n");
  append(L"      std::string current(path);\n");
  append(L"      if (strcmp(pathWithoutDriveLetter, \".\") == 0\n");
  append(L"       || strcmp(pathWithoutDriveLetter, \"..\") == 0)\n");
  append(L"      {\n");
  append(L"        current += '/';\n");
  append(L"      }\n");
  append(L"      else if (*pathWithoutDriveLetter == 0)\n");
  append(L"      {\n");
  append(L"        current += \"./\";\n");
  append(L"      }\n");
  append(L"\n");
  append(L"      if (current[current.size() - 1] == '/' || current[current.size() - 1] == '\\\\')\n");
  append(L"      {\n");
  append(L"        current += '*';\n");
  append(L"      }\n");
  append(L"\n");
  append(L"      _finddata_t foundfile;\n");
  append(L"\n");
  append(L"      intptr_t f = _findfirst(current.c_str(), &foundfile);\n");
  append(L"      if (-1L != f)\n");
  append(L"      {\n");
  append(L"        current.resize(0);\n");
  append(L"        for (int i = (int) strlen(path); i >= 0; --i)\n");
  append(L"        {\n");
  append(L"          char c = path[i];\n");
  append(L"          if (c == '/' || c == '\\\\' || c == ':')\n");
  append(L"          {\n");
  append(L"            current.append(path, i + 1);\n");
  append(L"            break;\n");
  append(L"          }\n");
  append(L"        }\n");
  append(L"        do\n");
  append(L"        {\n");
  append(L"          std::string foundPath(current);\n");
  append(L"          foundPath += foundfile.name;\n");
  append(L"          if ((foundfile.attrib & _A_SUBDIR) == 0)\n");
  append(L"          {\n");
  append(L"            if (endsWithI(foundfile.name, filter))\n");
  append(L"            {\n");
  append(L"              count += process(foundPath.c_str());\n");
  append(L"            }\n");
  append(L"          }\n");
  append(L"          else if (strcmp(foundfile.name, \".\") && strcmp(foundfile.name, \"..\"))\n");
  append(L"          {\n");
  append(L"            foundPath += \"/*\";\n");
  append(L"            count += findfiles(foundPath.c_str(), filter);\n");
  append(L"          }\n");
  append(L"        }\n");
  append(L"        while (_findnext(f, &foundfile) == 0);\n");
  append(L"      }\n");
  append(L"      _findclose(f);\n");
  append(L"\n");
  append(L"      return count;\n");
  append(L"    }\n");
  append(L"#else\n");
  append(L"    bool endsWithI(const char *s1, const char *s2)\n");
  append(L"    {\n");
  append(L"      size_t l1 = strlen(s1);\n");
  append(L"      size_t l2 = strlen(s2);\n");
  append(L"      return l1 >= l2 && (strcasecmp(s1 + l1 - l2, s2) == 0);\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    int findfiles(const char *path, const char *filter)\n");
  append(L"    {\n");
  append(L"      DIR *dir = opendir(path);\n");
  append(L"      if (dir)\n");
  append(L"      {\n");
  append(L"        int count = 0;\n");
  append(L"        std::string current;\n");
  append(L"        if (strcmp(path, \".\"))\n");
  append(L"        {\n");
  append(L"          current += path;\n");
  append(L"          if (current[current.size() - 1] != '/')\n");
  append(L"          {\n");
  append(L"            current += \"/\";\n");
  append(L"          }\n");
  append(L"        }\n");
  append(L"        for (struct dirent *dp = readdir(dir);\n");
  append(L"             dp;\n");
  append(L"             dp = readdir(dir))\n");
  append(L"        {\n");
  append(L"          if (strcmp(dp->d_name, \".\") && strcmp(dp->d_name, \"..\"))\n");
  append(L"          {\n");
  append(L"            std::string foundPath(current);\n");
  append(L"            foundPath += dp->d_name;\n");
  append(L"            count += findfiles(foundPath.c_str(), filter);\n");
  append(L"          }\n");
  append(L"        }\n");
  append(L"        closedir(dir);\n");
  append(L"        return count;\n");
  append(L"      }\n");
  append(L"      if (endsWithI(path, filter))\n");
  append(L"      {\n");
  append(L"        return process(path);\n");
  append(L"      }\n");
  append(L"      return 0;\n");
  append(L"    }\n");
  append(L"#endif\n");
  append(L"  };\n");
  append(L"\n");
  append(L"  class FileParser : public FileProcessor\n");
  append(L"  {\n");
  append(L"  public:\n");
  append(L"    FileParser(const char *aRoot, const char *aFilter)\n");
  append(L"    : root(aRoot), filter(aFilter)\n");
  append(L"    {}\n");
  append(L"\n");
  append(L"    int run()\n");
  append(L"    {\n");
  append(L"      return findfiles(root, filter);\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    int process(const char *path)\n");
  append(L"    {\n");
  append(L"      try\n");
  append(L"      {\n");
  append(L"        if (! ");
                                                            #line 2314 "PrintCpp.cpp.template"
                                                              print(className.c_str());
                                                            #line 3289 "PrintCpp.cpp"
  append(L"::quiet) fprintf(stdout, \"loading %s\\n\", path);\n");
  append(L"        parsers.push_back(ParseJob(");
                                                            #line 2316 "PrintCpp.cpp.template"
                                                              if (parseChars)
                                                              {
                                                            #line 3295 "PrintCpp.cpp"
  append(L"std::string");
                                                            #line 2318 "PrintCpp.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 3301 "PrintCpp.cpp"
  append(L"Utf8Decoder::decode");
                                                            #line 2321 "PrintCpp.cpp.template"
                                                              }
                                                            #line 3305 "PrintCpp.cpp"
  append(L"(path), read(path)));\n");
  append(L"        return 1;\n");
  append(L"      }\n");
  append(L"      catch (FileNotFound &)\n");
  append(L"      {\n");
  append(L"        fprintf(stderr, \"error: file not found: %s\\n\", path);\n");
  append(L"      }\n");
  append(L"      catch (MalformedInputException &mie)\n");
  append(L"      {\n");
  append(L"        fprintf(stderr, \"error: UTF-8 decoding error in %s at offset %d\\n\",\n");
  append(L"                path, static_cast<int>(mie.getOffset()));\n");
  append(L"      }\n");
  append(L"      return 0;\n");
  append(L"    }\n");
  append(L"\n");
  append(L"  private:\n");
  append(L"    const char* root;\n");
  append(L"    const char* filter;\n");
  append(L"  };\n");
  append(L"\n");
  append(L"  friend class FileParser;\n");
                                                            #line 2343 "PrintCpp.cpp.template"
                                                            }

                                                            void PrintCpp::printInterface()
                                                            {
                                                              printf("...printing interface\n");
                                                            }

                                                            void PrintCpp::close(Grammar *node)
                                                            {
                                                              if (lexerInstanceCode == 0)
                                                              {
                                                                internalerr();
                                                              }

                                                              print(lexerInstanceCode);
                                                              if (trace)
                                                              {
                                                            #line 3345 "PrintCpp.cpp"
  append(L"\n");
  append(L"  std::");
                                                            #line 2361 "PrintCpp.cpp.template"
                                                                print(stringIntroducer()[0] ? L"w" : L"");
                                                            #line 3350 "PrintCpp.cpp"
  append(L"string lookaheadString()\n");
  append(L"  {\n");
  append(L"    std::");
                                                            #line 2364 "PrintCpp.cpp.template"
                                                                print(stringIntroducer()[0] ? L"w" : L"");
                                                            #line 3356 "PrintCpp.cpp"
  append(L"string result;\n");
  append(L"    if (");
                                                            #line 2366 "PrintCpp.cpp.template"
                                                                print(thiz());
                                                            #line 3361 "PrintCpp.cpp"
  append(L"l1 > 0)\n");
  append(L"    {\n");
  append(L"      result += ");
                                                            #line 2369 "PrintCpp.cpp.template"
                                                                print(staticPrefix());
                                                            #line 3367 "PrintCpp.cpp"
  append(L"TOKEN[");
                                                            #line 2370 "PrintCpp.cpp.template"
                                                                print(thiz());
                                                            #line 3371 "PrintCpp.cpp"
  append(L"l1];");
                                                            #line 2371 "PrintCpp.cpp.template"
                                                                for (size_t i = 2; i <= grammar->k; ++i)
                                                                {
                                                            #line 3376 "PrintCpp.cpp"
  append(L"\n");
  append(L"      if (");
                                                            #line 2374 "PrintCpp.cpp.template"
                                                                  print(thiz());
                                                            #line 3381 "PrintCpp.cpp"
  append(L"l");
                                                            #line 2375 "PrintCpp.cpp.template"
                                                                  print(format.toString<wchar_t>(i));
                                                            #line 3385 "PrintCpp.cpp"
  append(L" > 0)\n");
  append(L"      {\n");
  append(L"        result += ");
                                                            #line 2378 "PrintCpp.cpp.template"
                                                                  print(stringIntroducer());
                                                            #line 3391 "PrintCpp.cpp"
  append(L"\" \";\n");
  append(L"        result += ");
                                                            #line 2380 "PrintCpp.cpp.template"
                                                                  print(staticPrefix());
                                                            #line 3396 "PrintCpp.cpp"
  append(L"TOKEN[");
                                                            #line 2381 "PrintCpp.cpp.template"
                                                                  print(thiz());
                                                            #line 3400 "PrintCpp.cpp"
  append(L"l");
                                                            #line 2382 "PrintCpp.cpp.template"
                                                                  print(format.toString<wchar_t>(i));
                                                            #line 3404 "PrintCpp.cpp"
  append(L"];");
                                                            #line 2383 "PrintCpp.cpp.template"
                                                                  increaseIndent();
                                                                }
                                                                for (size_t i = 2; i <= grammar->k; ++i)
                                                                {
                                                                  decreaseIndent();
                                                            #line 3412 "PrintCpp.cpp"
  append(L"\n");
  append(L"      }");
                                                            #line 2389 "PrintCpp.cpp.template"
                                                                }
                                                            #line 3417 "PrintCpp.cpp"
  append(L"\n");
  append(L"    }\n");
  append(L"    return result;\n");
  append(L"  }\n");
                                                            #line 2394 "PrintCpp.cpp.template"
                                                              }
                                                              if (useGlr)
                                                              {
                                                            #line 3426 "PrintCpp.cpp"
  append(L"\n");
  append(L"};\n");
  append(L"\n");
  append(L"ParsingThread *thread;");
                                                            #line 2400 "PrintCpp.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 3434 "PrintCpp.cpp"
  append(L"\n");
  append(L"BottomUpEventHandler *eventHandler;");
                                                            #line 2403 "PrintCpp.cpp.template"
                                                                }
                                                            #line 3439 "PrintCpp.cpp"
  append(L"\n");
  append(L"const ");
                                                            #line 2405 "PrintCpp.cpp.template"
                                                                if (parseChars)
                                                                {
                                                            #line 3445 "PrintCpp.cpp"
  append(L"char");
                                                            #line 2407 "PrintCpp.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 3451 "PrintCpp.cpp"
  append(L"wchar_t");
                                                            #line 2410 "PrintCpp.cpp.template"
                                                                }
                                                            #line 3455 "PrintCpp.cpp"
  append(L" *input;\n");
  append(L"int size;\n");
  append(L"int maxId;\n");
                                                            #line 2414 "PrintCpp.cpp.template"
                                                              }
                                                              if (lexerStaticCode == 0)
                                                              {
                                                                internalerr();
                                                              }

                                                              if (useGlr)
                                                                decreaseIndent();

                                                              increaseIndent();
                                                              printReadMethod();
                                                              decreaseIndent();

                                                              if (performanceTest)
                                                              {
                                                                printPerformanceCode();
                                                              }

                                                              print(lexerStaticCode);
                                                              printEndif();
                                                            }

// End
