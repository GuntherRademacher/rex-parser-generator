// This file was generated on Fri Nov 20, 2026 22:42 (UTC+01) by REx v7.1-SNAPSHOT which is Copyright (c) 1979-2026 by Gunther Rademacher <grd@gmx.net>
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
                                                                if (emitsEventHandler())
                                                                {
                                                            #line 276 "PrintCpp.cpp"
  append(L"\n");
  append(L"  class EventHandler\n");
  append(L"  {\n");
  append(L"  public:\n");
  append(L"    virtual ");
  append(L"~");
  append(L"EventHandler() {}\n");
  append(L"\n");
  append(L"    virtual void reset(");
                                                            #line 183 "PrintCpp.cpp.template"
                                                                  print(stringType());
                                                            #line 288 "PrintCpp.cpp"
  append(L"string) = 0;\n");
  append(L"    virtual void startNonterminal(int id, int begin) = 0;\n");
  append(L"    virtual void endNonterminal(int id, int end) = 0;\n");
  append(L"    virtual void terminal(int id, int begin, int end) = 0;\n");
  append(L"    virtual void whitespace(int begin, int end) = 0;\n");
  append(L"  };\n");
                                                            #line 190 "PrintCpp.cpp.template"
                                                                }
                                                                if (isLrParser)
                                                                {
                                                            #line 299 "PrintCpp.cpp"
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
                                                            #line 311 "PrintCpp.cpp"
  append(L"string) = 0;\n");
  append(L"    virtual void nonterminal(int id, int begin, int end, int count) = 0;\n");
  append(L"    virtual void terminal(int id, int begin, int end) = 0;");
                                                            #line 202 "PrintCpp.cpp.template"
                                                                  if (resolvesAmbiguity)
                                                                  {
                                                            #line 318 "PrintCpp.cpp"
  append(L"\n");
  append(L"    virtual void ambiguity(int begin, int end) = 0;");
                                                            #line 205 "PrintCpp.cpp.template"
                                                                  }
                                                            #line 323 "PrintCpp.cpp"
  append(L"\n");
  append(L"  };\n");
                                                            #line 208 "PrintCpp.cpp.template"
                                                                }
                                                              }
                                                              if (main && tree)
                                                              {
                                                            #line 331 "PrintCpp.cpp"
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
                                                            #line 225 "PrintCpp.cpp.template"
                                                                print(stringType());
                                                            #line 348 "PrintCpp.cpp"
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
  append(L"    void startNonterminal(int id, int b)\n");
  append(L"    {\n");
  append(L"      startElement(getNonterminalName(id));\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    void endNonterminal(int id, int e)\n");
  append(L"    {\n");
  append(L"      endElement(getNonterminalName(id));\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    void terminal(int id, int b, int e)\n");
  append(L"    {\n");
  append(L"      ");
                                                            #line 248 "PrintCpp.cpp.template"
                                                                print(stringType());
                                                            #line 374 "PrintCpp.cpp"
  append(L"tag = getTerminalName(id);\n");
  append(L"      if (tag[0] == ");
                                                            #line 250 "PrintCpp.cpp.template"
                                                                print(stringIntroducer());
                                                            #line 379 "PrintCpp.cpp"
  append(L"'\\'') tag = ");
                                                            #line 251 "PrintCpp.cpp.template"
                                                                print(stringIntroducer());
                                                            #line 383 "PrintCpp.cpp"
  append(L"\"TOKEN\";\n");
  append(L"      startElement(tag);\n");
  append(L"      characters(b, e);\n");
  append(L"      endElement(tag);\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    void startElement(");
                                                            #line 258 "PrintCpp.cpp.template"
                                                                print(stringType());
                                                            #line 393 "PrintCpp.cpp"
  append(L"tag)\n");
  append(L"    {\n");
  append(L"      if (delayedTag != 0)\n");
  append(L"      {\n");
  append(L"        fputc('<', stdout);\n");
  append(L"        fputs(");
                                                            #line 264 "PrintCpp.cpp.template"
                                                                if (! parseChars)
                                                                {
                                                            #line 403 "PrintCpp.cpp"
  append(L"Utf8Encoder::encode(");
                                                            #line 266 "PrintCpp.cpp.template"
                                                                }
                                                            #line 407 "PrintCpp.cpp"
  append(L"delayedTag");
                                                            #line 267 "PrintCpp.cpp.template"
                                                                if (! parseChars)
                                                                {
                                                            #line 412 "PrintCpp.cpp"
  append(L").c_str()");
                                                            #line 269 "PrintCpp.cpp.template"
                                                                }
                                                            #line 416 "PrintCpp.cpp"
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
  append(L"    void endElement(");
                                                            #line 286 "PrintCpp.cpp.template"
                                                                print(stringType());
                                                            #line 436 "PrintCpp.cpp"
  append(L"tag)\n");
  append(L"    {\n");
  append(L"      --depth;\n");
  append(L"      if (delayedTag != 0)\n");
  append(L"      {\n");
  append(L"        delayedTag = 0;\n");
  append(L"        fputc('<', stdout);\n");
  append(L"        fputs(");
                                                            #line 294 "PrintCpp.cpp.template"
                                                                if (! parseChars)
                                                                {
                                                            #line 448 "PrintCpp.cpp"
  append(L"Utf8Encoder::encode(");
                                                            #line 296 "PrintCpp.cpp.template"
                                                                }
                                                            #line 452 "PrintCpp.cpp"
  append(L"tag");
                                                            #line 297 "PrintCpp.cpp.template"
                                                                if (! parseChars)
                                                                {
                                                            #line 457 "PrintCpp.cpp"
  append(L").c_str()");
                                                            #line 299 "PrintCpp.cpp.template"
                                                                }
                                                            #line 461 "PrintCpp.cpp"
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
                                                            #line 317 "PrintCpp.cpp.template"
                                                                if (! parseChars)
                                                                {
                                                            #line 483 "PrintCpp.cpp"
  append(L"Utf8Encoder::encode(");
                                                            #line 319 "PrintCpp.cpp.template"
                                                                }
                                                            #line 487 "PrintCpp.cpp"
  append(L"tag");
                                                            #line 320 "PrintCpp.cpp.template"
                                                                if (! parseChars)
                                                                {
                                                            #line 492 "PrintCpp.cpp"
  append(L").c_str()");
                                                            #line 322 "PrintCpp.cpp.template"
                                                                }
                                                            #line 496 "PrintCpp.cpp"
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
                                                            #line 341 "PrintCpp.cpp.template"
                                                                if (! parseChars)
                                                                {
                                                            #line 519 "PrintCpp.cpp"
  append(L"Utf8Encoder::encode(");
                                                            #line 343 "PrintCpp.cpp.template"
                                                                }
                                                            #line 523 "PrintCpp.cpp"
  append(L"delayedTag");
                                                            #line 344 "PrintCpp.cpp.template"
                                                                if (! parseChars)
                                                                {
                                                            #line 528 "PrintCpp.cpp"
  append(L").c_str()");
                                                            #line 346 "PrintCpp.cpp.template"
                                                                }
                                                            #line 532 "PrintCpp.cpp"
  append(L", stdout);\n");
  append(L"          fputc('>', stdout);\n");
  append(L"          delayedTag = 0;\n");
  append(L"        }\n");
  append(L"        std::string encoded ");
                                                            #line 351 "PrintCpp.cpp.template"
                                                                if (! parseChars)
                                                                {
                                                            #line 541 "PrintCpp.cpp"
  append(L"= Utf8Encoder::encode");
                                                            #line 353 "PrintCpp.cpp.template"
                                                                }
                                                            #line 545 "PrintCpp.cpp"
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
  append(L"  private:\n");
  append(L"    ");
                                                            #line 372 "PrintCpp.cpp.template"
                                                                print(stringType());
                                                            #line 567 "PrintCpp.cpp"
  append(L"input;\n");
  append(L"    ");
                                                            #line 374 "PrintCpp.cpp.template"
                                                                print(stringType());
                                                            #line 572 "PrintCpp.cpp"
  append(L"delayedTag;\n");
  append(L"    bool indent;\n");
  append(L"    bool hasChildElement;\n");
  append(L"    int depth;\n");
  append(L"  };\n");
                                                            #line 380 "PrintCpp.cpp.template"
                                                              }
                                                              if (emitsTreeNodes())
                                                              {
                                                            #line 582 "PrintCpp.cpp"
  append(L"\n");
  append(L"  class Symbol\n");
  append(L"  {\n");
  append(L"  public:\n");
  append(L"    virtual ");
  append(L"~");
  append(L"Symbol() {}\n");
  append(L"\n");
  append(L"    int id;\n");
  append(L"    int begin;\n");
  append(L"    int end;\n");
  append(L"\n");
  append(L"    virtual ");
                                                            #line 393 "PrintCpp.cpp.template"
                                                                print(stringType());
                                                            #line 598 "PrintCpp.cpp"
  append(L"getName() const = 0;\n");
  append(L"    virtual void send(EventHandler *e) = 0;\n");
  append(L"\n");
  append(L"  protected:\n");
  append(L"    Symbol(int id, int begin, int end)\n");
  append(L"    {\n");
  append(L"      this->id = id;\n");
  append(L"      this->begin = begin;\n");
  append(L"      this->end = end;\n");
  append(L"    }\n");
  append(L"  };\n");
  append(L"\n");
  append(L"  class Terminal : public Symbol\n");
  append(L"  {\n");
  append(L"  public:\n");
  append(L"    Terminal(int id, int begin, int end)\n");
  append(L"    : Symbol(id, begin, end)\n");
  append(L"    {}\n");
  append(L"\n");
  append(L"    ");
                                                            #line 413 "PrintCpp.cpp.template"
                                                                print(stringType());
                                                            #line 621 "PrintCpp.cpp"
  append(L"getName() const\n");
  append(L"    {\n");
  append(L"      return TOKEN[id];\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    void send(EventHandler *e)\n");
  append(L"    {\n");
  append(L"      e->terminal(id, begin, end);\n");
  append(L"    }\n");
  append(L"  };\n");
  append(L"\n");
  append(L"  class Nonterminal : public Symbol\n");
  append(L"  {\n");
  append(L"  public:\n");
  append(L"    std::vector<Symbol *> *children;\n");
  append(L"\n");
  append(L"    Nonterminal(int id, int begin, int end, std::vector<Symbol *> *children)\n");
  append(L"    : Symbol(id, begin, end)\n");
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
  append(L"    ");
                                                            #line 443 "PrintCpp.cpp.template"
                                                                print(stringType());
                                                            #line 656 "PrintCpp.cpp"
  append(L"getName() const\n");
  append(L"    {\n");
  append(L"      return ");
                                                            #line 446 "PrintCpp.cpp.template"
                                                                printSyntheticNamePrefix();
                                                            #line 662 "PrintCpp.cpp"
  append(L"NONTERMINAL[id]");
                                                            #line 447 "PrintCpp.cpp.template"
                                                                printSyntheticNameSuffix();
                                                            #line 666 "PrintCpp.cpp"
  append(L";\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    void send(EventHandler *e)\n");
  append(L"    {\n");
  append(L"      e->startNonterminal(id, begin);\n");
  append(L"      int pos = begin;\n");
  append(L"      for (std::vector<Symbol *>::iterator i = children->begin(); i != children->end(); ++i)\n");
  append(L"      {\n");
  append(L"        Symbol *c = *i;\n");
  append(L"        if (pos < c->begin) e->whitespace(pos, c->begin);\n");
  append(L"        c->send(e);\n");
  append(L"        pos = c->end;\n");
  append(L"      }\n");
  append(L"      if (pos < end) e->whitespace(pos, end);\n");
  append(L"      e->endNonterminal(id, end);\n");
  append(L"    }\n");
  append(L"  };\n");
                                                            #line 466 "PrintCpp.cpp.template"
                                                              }
                                                              if (emitsTopDownTreeBuilder())
                                                              {
                                                            #line 689 "PrintCpp.cpp"
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
                                                            #line 480 "PrintCpp.cpp.template"
                                                                print(stringType());
                                                            #line 704 "PrintCpp.cpp"
  append(L"input)\n");
  append(L"    {\n");
  append(L"      this->input = input;\n");
  append(L"      top = -1;\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    void startNonterminal(int id, int begin)\n");
  append(L"    {\n");
  append(L"      Nonterminal *nonterminal = new Nonterminal(id, begin, begin, new std::vector<Symbol *>());\n");
  append(L"      if (top >= 0) addChild(nonterminal);\n");
  append(L"      if ((size_t) ++top >= stack.size())\n");
  append(L"        stack.resize(stack.size() == 0 ? 64 : stack.size() << 1);\n");
  append(L"      stack[top] = nonterminal;\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    void endNonterminal(int id, int end)\n");
  append(L"    {\n");
  append(L"      stack[top]->end = end;\n");
  append(L"      if (top > 0) --top;\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    void terminal(int id, int begin, int end)\n");
  append(L"    {\n");
  append(L"      addChild(new Terminal(id, begin, end));\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    void whitespace(int begin, int end)\n");
  append(L"    {\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    Nonterminal *getRoot() const {return top >= 0 ? stack[0] : 0;}\n");
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
                                                            #line 526 "PrintCpp.cpp.template"
                                                                print(stringType());
                                                            #line 753 "PrintCpp.cpp"
  append(L"input;\n");
  append(L"    std::vector<Nonterminal *> stack;\n");
  append(L"    int top;\n");
  append(L"  };\n");
                                                            #line 531 "PrintCpp.cpp.template"
                                                              }
                                                              if (emitsParseTreeBuilder())
                                                              {
                                                            #line 762 "PrintCpp.cpp"
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
                                                            #line 547 "PrintCpp.cpp.template"
                                                                print(stringType());
                                                            #line 781 "PrintCpp.cpp"
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
  append(L"    void nonterminal(int id, int begin, int end, int count)\n");
  append(L"    {");
                                                            #line 559 "PrintCpp.cpp.template"
                                                                if (rejectsAmbiguity())
                                                                {
                                                            #line 797 "PrintCpp.cpp"
  append(L"\n");
  append(L"      if (count > top + 1)\n");
  append(L"      {\n");
  append(L"        std::vector<Symbol *> *content = pop(top + 1);\n");
  append(L"        nonterminal(");
                                                            #line 565 "PrintCpp.cpp.template"
                                                                  print(format.toString<wchar_t>(Grammar::syntheticNonterminalCode(2)));
                                                            #line 805 "PrintCpp.cpp"
  append(L", begin, content->size() == 0 ? end : (*content)[0]->begin, 0);\n");
  append(L"        for (size_t i = 0; i < content->size(); ++i)\n");
  append(L"        {\n");
  append(L"          push((*content)[i]);\n");
  append(L"        }\n");
  append(L"        delete content;\n");
  append(L"        count = top + 1;\n");
  append(L"      }");
                                                            #line 573 "PrintCpp.cpp.template"
                                                                }
                                                            #line 816 "PrintCpp.cpp"
  append(L"\n");
  append(L"      push(new Nonterminal(id, begin, end, pop(count)));\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    void terminal(int id, int begin, int end)\n");
  append(L"    {\n");
  append(L"      push(new Terminal(id, begin, end));\n");
  append(L"    }");
                                                            #line 581 "PrintCpp.cpp.template"
                                                                if (resolvesAmbiguity)
                                                                {
                                                            #line 828 "PrintCpp.cpp"
  append(L"\n");
  append(L"\n");
  append(L"    void ambiguity(int begin, int end)\n");
  append(L"    {\n");
  append(L"    }");
                                                            #line 587 "PrintCpp.cpp.template"
                                                                }
                                                            #line 836 "PrintCpp.cpp"
  append(L"\n");
  append(L"\n");
  append(L"    Symbol *getRoot() const {return top >= 0 ? stack[0] : 0;}\n");
  append(L"\n");
  append(L"    void serialize(EventHandler *e)\n");
  append(L"    {\n");
  append(L"      e->reset(input);\n");
  append(L"      for (int i = 0; i <= top; ++i)\n");
  append(L"      {\n");
  append(L"        stack[i]->send(e);\n");
  append(L"      }\n");
  append(L"    }\n");
                                                            #line 600 "PrintCpp.cpp.template"
                                                                if (useGlr)
                                                                {
                                                            #line 852 "PrintCpp.cpp"
  append(L"\n");
  append(L"    const std::vector<Symbol *> &getStack() const {return stack;}\n");
  append(L"    int getTop() const {return top;}\n");
                                                            #line 605 "PrintCpp.cpp.template"
                                                                }
                                                            #line 858 "PrintCpp.cpp"
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
                                                            #line 624 "PrintCpp.cpp.template"
                                                                print(stringType());
                                                            #line 880 "PrintCpp.cpp"
  append(L"input;\n");
  append(L"    std::vector<Symbol *> stack;\n");
  append(L"    int top;\n");
  append(L"  };\n");
                                                            #line 629 "PrintCpp.cpp.template"
                                                              }
                                                              if (main)
                                                              {
                                                                printSimpleMain();
                                                              }
                                                              if (performanceTest)
                                                              {
                                                                printPerformanceMain();
                                                              }
                                                            #line 895 "PrintCpp.cpp"
  append(L"\n");
  append(L"  class ParseException\n");
  append(L"  {\n");
  append(L"  private:\n");
  append(L"    int begin, end, offending, expected, state;");
                                                            #line 642 "PrintCpp.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 904 "PrintCpp.cpp"
  append(L"\n");
  append(L"    bool ambiguousInput;");
                                                            #line 645 "PrintCpp.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 910 "PrintCpp.cpp"
  append(L"\n");
  append(L"    ParseTreeBuilder *ambiguityDescriptor;");
                                                            #line 648 "PrintCpp.cpp.template"
                                                                }
                                                              }
                                                            #line 916 "PrintCpp.cpp"
  append(L"\n");
  append(L"    friend class ");
                                                            #line 651 "PrintCpp.cpp.template"
                                                              print(className.c_str());
                                                            #line 921 "PrintCpp.cpp"
  append(L";\n");
  append(L"\n");
  append(L"  protected:\n");
  append(L"    ParseException(int b, int e, int s, int o, int x)\n");
  append(L"    : begin(b), end(e), offending(o), expected(x), state(s)");
                                                            #line 656 "PrintCpp.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 930 "PrintCpp.cpp"
  append(L",\n");
  append(L"      ambiguousInput(false)");
                                                            #line 659 "PrintCpp.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 936 "PrintCpp.cpp"
  append(L", ambiguityDescriptor(0)");
                                                            #line 661 "PrintCpp.cpp.template"
                                                                }
                                                              }
                                                            #line 941 "PrintCpp.cpp"
  append(L"\n");
  append(L"    {\n");
  append(L"    }\n");
                                                            #line 666 "PrintCpp.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 948 "PrintCpp.cpp"
  append(L"\n");
  append(L"    ParseException(int b, int e");
                                                            #line 669 "PrintCpp.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 954 "PrintCpp.cpp"
  append(L", ParseTreeBuilder *ambiguityDescriptor");
                                                            #line 672 "PrintCpp.cpp.template"
                                                                }
                                                            #line 958 "PrintCpp.cpp"
  append(L")\n");
  append(L"    : begin(b), end(e), offending(-1), expected(-1), state(-1),\n");
  append(L"      ambiguousInput(true)");
                                                            #line 675 "PrintCpp.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 965 "PrintCpp.cpp"
  append(L", ambiguityDescriptor(ambiguityDescriptor)");
                                                            #line 678 "PrintCpp.cpp.template"
                                                                }
                                                            #line 969 "PrintCpp.cpp"
  append(L"\n");
  append(L"    {\n");
  append(L"    }\n");
                                                            #line 682 "PrintCpp.cpp.template"
                                                              }
                                                            #line 975 "PrintCpp.cpp"
  append(L"\n");
  append(L"  public:");
                                                            #line 684 "PrintCpp.cpp.template"
                                                              if (rejectsAmbiguity() && tree)
                                                              {
                                                            #line 981 "PrintCpp.cpp"
  append(L"\n");
  append(L"    ");
  append(L"~");
  append(L"ParseException()\n");
  append(L"    {\n");
  append(L"      delete ambiguityDescriptor;\n");
  append(L"    }\n");
                                                            #line 691 "PrintCpp.cpp.template"
                                                              }
                                                            #line 991 "PrintCpp.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 693 "PrintCpp.cpp.template"
                                                              print(stringType());
                                                            #line 996 "PrintCpp.cpp"
  append(L"getMessage() const\n");
  append(L"    {\n");
  append(L"      return ");
                                                            #line 696 "PrintCpp.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 1003 "PrintCpp.cpp"
  append(L"ambiguousInput\n");
  append(L"           ? ");
                                                            #line 699 "PrintCpp.cpp.template"
                                                                print(stringIntroducer());
                                                            #line 1008 "PrintCpp.cpp"
  append(L"\"ambiguous input\"\n");
  append(L"           : ");
                                                            #line 701 "PrintCpp.cpp.template"
                                                              }
                                                            #line 1013 "PrintCpp.cpp"
  append(L"offending < 0\n");
  append(L"           ? ");
                                                            #line 703 "PrintCpp.cpp.template"
                                                              print(stringIntroducer());
                                                            #line 1018 "PrintCpp.cpp"
  append(L"\"lexical analysis failed\"\n");
  append(L"           : ");
                                                            #line 705 "PrintCpp.cpp.template"
                                                              print(stringIntroducer());
                                                            #line 1023 "PrintCpp.cpp"
  append(L"\"syntax error\";\n");
  append(L"    }\n");
                                                            #line 708 "PrintCpp.cpp.template"
                                                              if (rejectsAmbiguity() && tree)
                                                              {
                                                            #line 1029 "PrintCpp.cpp"
  append(L"\n");
  append(L"    void serialize(EventHandler *eventHandler)\n");
  append(L"    {\n");
  append(L"      ambiguityDescriptor->serialize(eventHandler);\n");
  append(L"    }\n");
                                                            #line 715 "PrintCpp.cpp.template"
                                                              }
                                                            #line 1037 "PrintCpp.cpp"
  append(L"\n");
  append(L"    int getBegin() const {return begin;}\n");
  append(L"    int getEnd() const {return end;}\n");
  append(L"    int getState() const {return state;}\n");
  append(L"    int getOffending() const {return offending;}\n");
  append(L"    int getExpected() const {return expected;}");
                                                            #line 721 "PrintCpp.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 1047 "PrintCpp.cpp"
  append(L"\n");
  append(L"    int isAmbiguousInput() const {return ");
                                                            #line 724 "PrintCpp.cpp.template"
                                                                if (rejectsAmbiguity())
                                                                {
                                                            #line 1053 "PrintCpp.cpp"
  append(L"ambiguousInput");
                                                            #line 726 "PrintCpp.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1059 "PrintCpp.cpp"
  append(L"false");
                                                            #line 729 "PrintCpp.cpp.template"
                                                                }
                                                            #line 1063 "PrintCpp.cpp"
  append(L";}");
                                                            #line 730 "PrintCpp.cpp.template"
                                                              }
                                                            #line 1067 "PrintCpp.cpp"
  append(L"\n");
  append(L"  };\n");
                                                            #line 733 "PrintCpp.cpp.template"
                                                              /*
                                                            #line 1072 "PrintCpp.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 735 "PrintCpp.cpp.template"
                                                              print(stringType());
                                                            #line 1077 "PrintCpp.cpp"
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
                                                            #line 750 "PrintCpp.cpp.template"
                                                              */
                                                            }

                                                            void PrintCpp::beginNonpublic()
                                                            {
                                                            #line 1098 "PrintCpp.cpp"
  append(L"\n");
  append(L"private:\n");
                                                            #line 757 "PrintCpp.cpp.template"
                                                            }

                                                            void PrintCpp::beginPublic()
                                                            {
                                                            #line 1106 "PrintCpp.cpp"
  append(L"\n");
  append(L"public:\n");
                                                            #line 763 "PrintCpp.cpp.template"
                                                            }

                                                            void PrintCpp::openStackNode()
                                                            {
                                                            #line 1114 "PrintCpp.cpp"
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
                                                            #line 829 "PrintCpp.cpp.template"
                                                              if (grammar->states->hasLookback)
                                                              {
                                                            #line 1183 "PrintCpp.cpp"
  append(L"\n");
  append(L"  int code;");
                                                            #line 832 "PrintCpp.cpp.template"
                                                              }
                                                            #line 1188 "PrintCpp.cpp"
  append(L"\n");
  append(L"  int pos;\n");
  append(L"\n");
  append(L"  StackNode(int state, ");
                                                            #line 836 "PrintCpp.cpp.template"
                                                              if (grammar->states->hasLookback)
                                                              {
                                                            #line 1196 "PrintCpp.cpp"
  append(L"int code, ");
                                                            #line 838 "PrintCpp.cpp.template"
                                                              }
                                                            #line 1200 "PrintCpp.cpp"
  append(L"int pos, StackNode *link)\n");
  append(L"  : TreeStructuredStack(link), state(state)");
                                                            #line 840 "PrintCpp.cpp.template"
                                                              if (grammar->states->hasLookback)
                                                              {
                                                            #line 1206 "PrintCpp.cpp"
  append(L", code(code)");
                                                            #line 842 "PrintCpp.cpp.template"
                                                              }
                                                            #line 1210 "PrintCpp.cpp"
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
                                                            #line 852 "PrintCpp.cpp.template"
                                                              if (grammar->states->hasLookback)
                                                              {
                                                            #line 1224 "PrintCpp.cpp"
  append(L"\n");
  append(L"      if (lhs->code != rhs->code) return false;");
                                                            #line 855 "PrintCpp.cpp.template"
                                                              }
                                                            #line 1229 "PrintCpp.cpp"
  append(L"\n");
  append(L"      if (lhs->pos != rhs->pos) return false;\n");
  append(L"      lhs = lhs->link;\n");
  append(L"      rhs = rhs->link;\n");
  append(L"    }\n");
  append(L"    return lhs == rhs;\n");
  append(L"  }\n");
                                                            #line 863 "PrintCpp.cpp.template"
                                                              increaseIndent();
                                                            }

                                                            void PrintCpp::closeStackNode()
                                                            {
                                                              decreaseIndent();
                                                            #line 1244 "PrintCpp.cpp"
  append(L"\n");
  append(L"};\n");
                                                            #line 871 "PrintCpp.cpp.template"
                                                              if (hasCustomCode)
                                                              {
                                                            #line 1250 "PrintCpp.cpp"
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
                                                            #line 885 "PrintCpp.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                            #line 1267 "PrintCpp.cpp"
  append(L"\n");
  append(L"class DeferredEvent : public TreeStructuredStack<DeferredEvent>\n");
  append(L"{\n");
  append(L"public:\n");
  append(L"  int id;\n");
  append(L"  int begin;\n");
  append(L"  int end;");
                                                            #line 894 "PrintCpp.cpp.template"
                                                                if (shiftAmbiguity)
                                                                {
                                                            #line 1278 "PrintCpp.cpp"
  append(L"\n");
  append(L"  int depth;\n");
  append(L"\n");
  append(L"  virtual bool isTerminal() const {return false;}");
                                                            #line 899 "PrintCpp.cpp.template"
                                                                }
                                                            #line 1285 "PrintCpp.cpp"
  append(L"\n");
  append(L"\n");
  append(L"  DeferredEvent(DeferredEvent *link, int id, int begin, int end)\n");
  append(L"  : TreeStructuredStack(link), id(id), begin(begin), end(end)");
                                                            #line 903 "PrintCpp.cpp.template"
                                                                if (shiftAmbiguity)
                                                                {
                                                            #line 1293 "PrintCpp.cpp"
  append(L"\n");
  append(L"  , depth(link == 0 ? 1 : link->depth + 1)");
                                                            #line 906 "PrintCpp.cpp.template"
                                                                }
                                                            #line 1298 "PrintCpp.cpp"
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
                                                            #line 927 "PrintCpp.cpp.template"
                                                                if (shiftAmbiguity)
                                                                {
                                                            #line 1323 "PrintCpp.cpp"
  append(L"if (eventHandler != 0)\n");
  append(L"        ");
                                                            #line 930 "PrintCpp.cpp.template"
                                                                }
                                                            #line 1328 "PrintCpp.cpp"
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
  append(L"  TerminalEvent(DeferredEvent *link, int id, int begin, int end)\n");
  append(L"  : DeferredEvent(link, id, begin, end)\n");
  append(L"  {}\n");
  append(L"\n");
  append(L"  void execute(BottomUpEventHandler *eventHandler)\n");
  append(L"  {\n");
  append(L"    eventHandler->terminal(id, begin, end);\n");
  append(L"  }");
                                                            #line 963 "PrintCpp.cpp.template"
                                                                if (shiftAmbiguity)
                                                                {
                                                            #line 1365 "PrintCpp.cpp"
  append(L"\n");
  append(L"\n");
  append(L"  bool isTerminal() const {return true;}");
                                                            #line 967 "PrintCpp.cpp.template"
                                                                }
                                                            #line 1371 "PrintCpp.cpp"
  append(L"\n");
  append(L"};\n");
  append(L"\n");
  append(L"class NonterminalEvent : public DeferredEvent\n");
  append(L"{\n");
  append(L"public:\n");
  append(L"  int count;\n");
  append(L"\n");
  append(L"  NonterminalEvent(DeferredEvent *link, int id, int begin, int end, int count)\n");
  append(L"  : DeferredEvent(link, id, begin, end), count(count)\n");
  append(L"  {}\n");
  append(L"\n");
  append(L"  void execute(BottomUpEventHandler *eventHandler)\n");
  append(L"  {\n");
  append(L"    eventHandler->nonterminal(id, begin, end, count);\n");
  append(L"  }\n");
  append(L"};\n");
                                                            #line 985 "PrintCpp.cpp.template"
                                                                if (resolvesAmbiguity)
                                                                {
                                                            #line 1392 "PrintCpp.cpp"
  append(L"\n");
  append(L"\n");
  append(L"class AmbiguityEvent : public DeferredEvent\n");
  append(L"{\n");
  append(L"public:\n");
  append(L"  AmbiguityEvent(DeferredEvent *link, int begin, int end)\n");
  append(L"  : DeferredEvent(link, -1, begin, end)\n");
  append(L"  {}\n");
  append(L"\n");
  append(L"  void execute(BottomUpEventHandler *eventHandler)\n");
  append(L"  {\n");
  append(L"    eventHandler->ambiguity(begin, end);\n");
  append(L"  }\n");
  append(L"};\n");
                                                            #line 1001 "PrintCpp.cpp.template"
                                                                }
                                                              }
                                                            #line 1410 "PrintCpp.cpp"
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
                                                            #line 1027 "PrintCpp.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 1441 "PrintCpp.cpp"
  append(L"BottomUpEventHandler *eventHandler, ");
                                                            #line 1030 "PrintCpp.cpp.template"
                                                              }
                                                            #line 1445 "PrintCpp.cpp"
  append(L"ParsingThread *&thread)\n");
  append(L"{\n");
  append(L"  PriorityQueue threads;\n");
  append(L"  thread->open(threads, initialState");
                                                            #line 1034 "PrintCpp.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 1453 "PrintCpp.cpp"
  append(L", eventHandler");
                                                            #line 1036 "PrintCpp.cpp.template"
                                                              }
                                                            #line 1457 "PrintCpp.cpp"
  append(L", target);\n");
  append(L"  for (;;)\n");
  append(L"  {\n");
  append(L"    thread = threads.top();\n");
  append(L"    threads.pop();\n");
  append(L"    if (thread->accepted)\n");
  append(L"    {");
                                                            #line 1043 "PrintCpp.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 1468 "PrintCpp.cpp"
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
                                                            #line 1062 "PrintCpp.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 1490 "PrintCpp.cpp"
  append(L", thread->deferredEvent, other->deferredEvent");
                                                            #line 1065 "PrintCpp.cpp.template"
                                                                }
                                                            #line 1494 "PrintCpp.cpp"
  append(L");\n");
  append(L"      }");
                                                            #line 1067 "PrintCpp.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 1501 "PrintCpp.cpp"
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
                                                            #line 1084 "PrintCpp.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                            #line 1521 "PrintCpp.cpp"
  append(L"\n");
  append(L"      if (thread->deferredEvent != 0)\n");
  append(L"      {\n");
  append(L"        thread->deferredEvent->release(eventHandler);\n");
  append(L"        thread->deferredEvent = 0;\n");
  append(L"      }");
                                                            #line 1092 "PrintCpp.cpp.template"
                                                              }
                                                              if (hasCustomCode)
                                                              {
                                                            #line 1532 "PrintCpp.cpp"
  append(L"\n");
  append(L"      thread->executeDeferredCode();");
                                                            #line 1096 "PrintCpp.cpp.template"
                                                              }
                                                            #line 1537 "PrintCpp.cpp"
  append(L"\n");
  append(L"      return;\n");
  append(L"    }\n");
  append(L"\n");
                                                            #line 1101 "PrintCpp.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 1545 "PrintCpp.cpp"
  append(L"    if (! threads.empty())\n");
  append(L"    {\n");
  append(L"      if (*threads.top() == *thread)\n");
  append(L"      {\n");
  append(L"        rejectAmbiguity(thread");
                                                            #line 1107 "PrintCpp.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 1554 "PrintCpp.cpp"
  append(L", thread->deferredEvent, threads.top()->deferredEvent");
                                                            #line 1110 "PrintCpp.cpp.template"
                                                                }
                                                            #line 1558 "PrintCpp.cpp"
  append(L");\n");
  append(L"      }\n");
  append(L"    }");
                                                            #line 1113 "PrintCpp.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 1566 "PrintCpp.cpp"
  append(L"    while (! threads.empty() && *threads.top() == *thread)\n");
  append(L"    {\n");
  append(L"      ParsingThread *other = threads.top();\n");
  append(L"      threads.pop();\n");
  append(L"      thread = resolve(thread, other);\n");
  append(L"    }");
                                                            #line 1121 "PrintCpp.cpp.template"
                                                              }
                                                              if (tree || hasCustomCode)
                                                              {
                                                                if (rejectsAmbiguity())
                                                                {
                                                            #line 1579 "PrintCpp.cpp"
  append(L"\n");
  append(L"    else\n");
  append(L"    {");
                                                            #line 1128 "PrintCpp.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1587 "PrintCpp.cpp"
  append(L"\n");
  append(L"    if (threads.empty())\n");
  append(L"    {");
                                                            #line 1133 "PrintCpp.cpp.template"
                                                                }
                                                                if (tree)
                                                                {
                                                            #line 1595 "PrintCpp.cpp"
  append(L"\n");
  append(L"      if (thread->deferredEvent != 0)\n");
  append(L"      {\n");
  append(L"        thread->deferredEvent->release(eventHandler);\n");
  append(L"        thread->deferredEvent = 0;\n");
  append(L"      }");
                                                            #line 1141 "PrintCpp.cpp.template"
                                                                }
                                                                if (hasCustomCode)
                                                                {
                                                            #line 1606 "PrintCpp.cpp"
  append(L"\n");
  append(L"      thread->executeDeferredCode();");
                                                            #line 1145 "PrintCpp.cpp.template"
                                                                }
                                                            #line 1611 "PrintCpp.cpp"
  append(L"\n");
  append(L"    }");
                                                            #line 1147 "PrintCpp.cpp.template"
                                                              }
                                                            #line 1616 "PrintCpp.cpp"
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
                                                            #line 1177 "PrintCpp.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 1649 "PrintCpp.cpp"
  append(L"\n");
  append(L"void rejectAmbiguity(ParsingThread *&thread");
                                                            #line 1180 "PrintCpp.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 1655 "PrintCpp.cpp"
  append(L", DeferredEvent *first, DeferredEvent *second");
                                                            #line 1183 "PrintCpp.cpp.template"
                                                                }
                                                            #line 1659 "PrintCpp.cpp"
  append(L")\n");
  append(L"{");
                                                            #line 1185 "PrintCpp.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 1665 "PrintCpp.cpp"
  append(L"\n");
  append(L"  ParseTreeBuilder *treeBuilder = new ParseTreeBuilder();\n");
  append(L"  treeBuilder->reset(input);\n");
  append(L"  second->show(treeBuilder);\n");
  append(L"  treeBuilder->nonterminal(");
                                                            #line 1191 "PrintCpp.cpp.template"
                                                                  print(format.toString<wchar_t>(Grammar::syntheticNonterminalCode(0)));
                                                            #line 1673 "PrintCpp.cpp"
  append(L", treeBuilder->getStack()[0]->begin, treeBuilder->getStack()[treeBuilder->getTop()]->end, treeBuilder->getTop() + 1);\n");
  append(L"  std::vector<Symbol *> *secondTree = treeBuilder->pop(1);\n");
  append(L"  first->show(treeBuilder);\n");
  append(L"  treeBuilder->nonterminal(");
                                                            #line 1195 "PrintCpp.cpp.template"
                                                                  print(format.toString<wchar_t>(Grammar::syntheticNonterminalCode(0)));
                                                            #line 1680 "PrintCpp.cpp"
  append(L", treeBuilder->getStack()[0]->begin, treeBuilder->getStack()[treeBuilder->getTop()]->end, treeBuilder->getTop() + 1);\n");
  append(L"  treeBuilder->push((*secondTree)[0]);\n");
  append(L"  delete secondTree;\n");
  append(L"  treeBuilder->nonterminal(");
                                                            #line 1199 "PrintCpp.cpp.template"
                                                                  print(format.toString<wchar_t>(Grammar::syntheticNonterminalCode(1)));
                                                            #line 1687 "PrintCpp.cpp"
  append(L", treeBuilder->getStack()[0]->begin, treeBuilder->getStack()[treeBuilder->getTop()]->end, 2);");
                                                            #line 1201 "PrintCpp.cpp.template"
                                                                }
                                                            #line 1691 "PrintCpp.cpp"
  append(L"\n");
  append(L"  int begin = thread->stack->pos;\n");
  append(L"  int end = thread->e0;\n");
  append(L"  thread->cleanup();\n");
  append(L"  throw ParseException(begin, end");
                                                            #line 1206 "PrintCpp.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 1700 "PrintCpp.cpp"
  append(L", treeBuilder");
                                                            #line 1208 "PrintCpp.cpp.template"
                                                                }
                                                            #line 1704 "PrintCpp.cpp"
  append(L");\n");
  append(L"}");
                                                            #line 1210 "PrintCpp.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 1711 "PrintCpp.cpp"
  append(L"\n");
  append(L"ParsingThread *resolve(ParsingThread *thread, ParsingThread *other)\n");
  append(L"{");
                                                            #line 1215 "PrintCpp.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 1718 "PrintCpp.cpp"
  append(L"\n");
  append(L"  int begin = thread->stack->pos;\n");
  append(L"  for (StackNode *a = thread->stack, *b = other->stack; a != b && a != 0 && b != 0; a = a->link, b = b->link)\n");
  append(L"  {\n");
  append(L"    begin = a->pos;\n");
  append(L"  }");
                                                            #line 1222 "PrintCpp.cpp.template"
                                                                }
                                                            #line 1727 "PrintCpp.cpp"
  append(L"\n");
                                                            #line 1224 "PrintCpp.cpp.template"
                                                                if (shiftAmbiguity)
                                                                {
                                                            #line 1732 "PrintCpp.cpp"
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
                                                            #line 1246 "PrintCpp.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1757 "PrintCpp.cpp"
  append(L"  ParsingThread *winner = other->eventCount < thread->eventCount ? other : thread;");
                                                            #line 1250 "PrintCpp.cpp.template"
                                                                }
                                                            #line 1761 "PrintCpp.cpp"
  append(L"\n");
  append(L"  delete (winner == thread ? other : thread);");
                                                            #line 1252 "PrintCpp.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 1767 "PrintCpp.cpp"
  append(L"\n");
  append(L"  winner->addAmbiguity(begin, winner->e0);");
                                                            #line 1255 "PrintCpp.cpp.template"
                                                                }
                                                            #line 1772 "PrintCpp.cpp"
  append(L"\n");
  append(L"  return winner;\n");
  append(L"}");
                                                            #line 1258 "PrintCpp.cpp.template"
                                                              }
                                                            }

                                                            void PrintCpp::openThread()
                                                            {
                                                            #line 1782 "PrintCpp.cpp"
  append(L"\n");
  append(L"class ParsingThread\n");
  append(L"{\n");
  append(L"public:\n");
  append(L"  ");
                                                            #line 1267 "PrintCpp.cpp.template"
                                                              print(className.c_str());
                                                            #line 1790 "PrintCpp.cpp"
  append(L" *parser;\n");
  append(L"  PriorityQueue *threads;\n");
  append(L"  bool accepted;\n");
  append(L"  StackNode *stack;\n");
  append(L"  int state;\n");
  append(L"  int action;\n");
  append(L"  int target;");
                                                            #line 1274 "PrintCpp.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 1801 "PrintCpp.cpp"
  append(L"\n");
  append(L"  DeferredEvent *deferredEvent;");
                                                            #line 1277 "PrintCpp.cpp.template"
                                                              }
                                                              if (hasCustomCode)
                                                              {
                                                            #line 1808 "PrintCpp.cpp"
  append(L"\n");
  append(L"  DeferredCode *deferredCode;");
                                                            #line 1281 "PrintCpp.cpp.template"
                                                              }
                                                            #line 1813 "PrintCpp.cpp"
  append(L"\n");
  append(L"  int id;");
                                                            #line 1283 "PrintCpp.cpp.template"
                                                              if (resolvesAmbiguity)
                                                              {
                                                            #line 1819 "PrintCpp.cpp"
  append(L"\n");
  append(L"  int eventCount;");
                                                            #line 1286 "PrintCpp.cpp.template"
                                                              }
                                                            #line 1824 "PrintCpp.cpp"
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
                                                            #line 1298 "PrintCpp.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 1842 "PrintCpp.cpp"
  append(L", BottomUpEventHandler *eventHandler");
                                                            #line 1301 "PrintCpp.cpp.template"
                                                              }
                                                            #line 1846 "PrintCpp.cpp"
  append(L", int target)\n");
  append(L"  {\n");
  append(L"    this->threads = &threads;\n");
  append(L"    this->target = target;");
                                                            #line 1305 "PrintCpp.cpp.template"
                                                              if (resolvesAmbiguity)
                                                              {
                                                            #line 1854 "PrintCpp.cpp"
  append(L"\n");
  append(L"    eventCount = 0;");
                                                            #line 1308 "PrintCpp.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                            #line 1861 "PrintCpp.cpp"
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
                                                            #line 1320 "PrintCpp.cpp.template"
                                                              }
                                                              if (hasCustomCode && useGlr)
                                                              {
                                                            #line 1876 "PrintCpp.cpp"
  append(L"\n");
  append(L"    deferredCode = 0;");
                                                            #line 1324 "PrintCpp.cpp.template"
                                                              }
                                                            #line 1881 "PrintCpp.cpp"
  append(L"\n");
  append(L"    accepted = false;\n");
  append(L"    stack = new StackNode(-1, ");
                                                            #line 1327 "PrintCpp.cpp.template"
                                                              if (grammar->states->hasLookback)
                                                              {
                                                            #line 1888 "PrintCpp.cpp"
  append(L"0, ");
                                                            #line 1329 "PrintCpp.cpp.template"
                                                              }
                                                            #line 1892 "PrintCpp.cpp"
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
                                                            #line 1342 "PrintCpp.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 1909 "PrintCpp.cpp"
  append(L"\n");
  append(L"    if (deferredEvent != 0)\n");
  append(L"    {\n");
  append(L"      deferredEvent->unshare();\n");
  append(L"      deferredEvent = 0;\n");
  append(L"    }");
                                                            #line 1349 "PrintCpp.cpp.template"
                                                              }
                                                              if (hasCustomCode)
                                                              {
                                                            #line 1920 "PrintCpp.cpp"
  append(L"\n");
  append(L"    if (deferredCode != 0)\n");
  append(L"    {\n");
  append(L"      deferredCode->unshare();\n");
  append(L"      deferredCode = 0;\n");
  append(L"    }");
                                                            #line 1357 "PrintCpp.cpp.template"
                                                              }
                                                            #line 1929 "PrintCpp.cpp"
  append(L"\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  ParsingThread *copy(ParsingThread *other, int action)\n");
  append(L"  {\n");
  append(L"    this->action = action;\n");
  append(L"    accepted = other->accepted;\n");
  append(L"    target = other->target;\n");
  append(L"    parser = other->parser;");
                                                            #line 1366 "PrintCpp.cpp.template"
                                                              if (resolvesAmbiguity)
                                                              {
                                                            #line 1942 "PrintCpp.cpp"
  append(L"\n");
  append(L"    eventCount = other->eventCount;");
                                                            #line 1369 "PrintCpp.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                            #line 1949 "PrintCpp.cpp"
  append(L"\n");
  append(L"    bs = other->bs;\n");
  append(L"    bw = other->bw;\n");
  append(L"    es = other->es;\n");
  append(L"    eventHandler = other->eventHandler;\n");
  append(L"    deferredEvent = other->deferredEvent == 0 ? 0 : other->deferredEvent->share();");
                                                            #line 1378 "PrintCpp.cpp.template"
                                                              }
                                                              if (hasCustomCode)
                                                              {
                                                            #line 1960 "PrintCpp.cpp"
  append(L"\n");
  append(L"    deferredCode = other->deferredCode == 0 ? 0 : other->deferredCode->share();");
                                                            #line 1383 "PrintCpp.cpp.template"
                                                              }
                                                            #line 1965 "PrintCpp.cpp"
  append(L"\n");
  append(L"    id = ++parser->maxId;\n");
  append(L"    threads = other->threads;\n");
  append(L"    state = other->state;\n");
  append(L"    stack = other->stack->share();\n");
  append(L"    b0 = other->b0;\n");
  append(L"    e0 = other->e0;");
                                                            #line 1390 "PrintCpp.cpp.template"
                                                              for (size_t i = 1; i <= grammar->k; ++i)
                                                              {
                                                                const wchar_t *iString = format.toString<wchar_t>(i);
                                                            #line 1977 "PrintCpp.cpp"
  append(L"\n");
  append(L"    l");
                                                            #line 1394 "PrintCpp.cpp.template"
                                                                print(iString);
                                                            #line 1982 "PrintCpp.cpp"
  append(L" = other->l");
                                                            #line 1395 "PrintCpp.cpp.template"
                                                                print(iString);
                                                            #line 1986 "PrintCpp.cpp"
  append(L";\n");
  append(L"    b");
                                                            #line 1397 "PrintCpp.cpp.template"
                                                                print(iString);
                                                            #line 1991 "PrintCpp.cpp"
  append(L" = other->b");
                                                            #line 1398 "PrintCpp.cpp.template"
                                                                print(iString);
                                                            #line 1995 "PrintCpp.cpp"
  append(L";\n");
  append(L"    e");
                                                            #line 1400 "PrintCpp.cpp.template"
                                                                print(iString);
                                                            #line 2000 "PrintCpp.cpp"
  append(L" = other->e");
                                                            #line 1401 "PrintCpp.cpp.template"
                                                                print(iString);
                                                            #line 2004 "PrintCpp.cpp"
  append(L";");
                                                            #line 1402 "PrintCpp.cpp.template"
                                                              }
                                                            #line 2008 "PrintCpp.cpp"
  append(L"\n");
  append(L"    end = other->end;\n");
  append(L"    return this;\n");
  append(L"  }\n");
  append(L"\n");
                                                            #line 1408 "PrintCpp.cpp.template"
                                                              if (resolvesAmbiguity && tree)
                                                              {
                                                            #line 2017 "PrintCpp.cpp"
  append(L"\n");
  append(L"  void addAmbiguity(int begin, int end)\n");
  append(L"  {\n");
  append(L"    if (eventHandler != 0)\n");
  append(L"      deferredEvent = new AmbiguityEvent(deferredEvent, begin, end);\n");
  append(L"  }\n");
  append(L"\n");
                                                            #line 1417 "PrintCpp.cpp.template"
                                                              }
                                                            #line 2027 "PrintCpp.cpp"
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
                                                            #line 1447 "PrintCpp.cpp.template"
                                                              increaseIndent();
                                                            }

                                                            void PrintCpp::openMethod(const wchar_t *type,
                                                                                      const wchar_t *prefix,
                                                                                      const wchar_t *name,
                                                                                      const wchar_t *args,
                                                                                      bool constant,
                                                                                      const wchar_t *clazz)
                                                            {
                                                            #line 2069 "PrintCpp.cpp"
  append(L"\n");
                                                            #line 1458 "PrintCpp.cpp.template"
                                                              print(prefix);
                                                              print(type);
                                                              print(name);
                                                            #line 2075 "PrintCpp.cpp"
  append(L"(");
                                                            #line 1461 "PrintCpp.cpp.template"
                                                              print(args);
                                                            #line 2079 "PrintCpp.cpp"
  append(L")");
                                                            #line 1462 "PrintCpp.cpp.template"
                                                              if (constant)
                                                              {
                                                            #line 2084 "PrintCpp.cpp"
  append(L" const");
                                                            #line 1464 "PrintCpp.cpp.template"
                                                              }
                                                            }

                                                            void PrintCpp::privateVars()
                                                            {
                                                            #line 2092 "PrintCpp.cpp"
  append(L"\n");
  append(L"  int ");
                                                            #line 1470 "PrintCpp.cpp.template"
                                                              if (! isLrParser && (grammar->k > 1 ||
                                                                                   memoization ||
                                                                                   ! grammar->decisionPoints.empty()))
                                                              {
                                                            #line 2100 "PrintCpp.cpp"
  append(L"lk,");
                                                            #line 1474 "PrintCpp.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 2106 "PrintCpp.cpp"
  append(L"   ");
                                                            #line 1477 "PrintCpp.cpp.template"
                                                              }
                                                            #line 2110 "PrintCpp.cpp"
  append(L" b0, e0;");
                                                            #line 1478 "PrintCpp.cpp.template"
                                                              for (size_t k = 1; k <= grammar->k; ++k)
                                                              {
                                                                wchar_t *asString = format.toString<wchar_t>(k);
                                                            #line 2116 "PrintCpp.cpp"
  append(L"\n");
  append(L"  int l");
                                                            #line 1482 "PrintCpp.cpp.template"
                                                                print(asString);
                                                            #line 2121 "PrintCpp.cpp"
  append(L", b");
                                                            #line 1483 "PrintCpp.cpp.template"
                                                                print(asString);
                                                            #line 2125 "PrintCpp.cpp"
  append(L", e");
                                                            #line 1484 "PrintCpp.cpp.template"
                                                                print(asString);
                                                            #line 2129 "PrintCpp.cpp"
  append(L";");
                                                            #line 1485 "PrintCpp.cpp.template"
                                                              }
                                                              if (hasBacktracking)
                                                              {
                                                            #line 2135 "PrintCpp.cpp"
  append(L"\n");
  append(L"  int bx, ex, sx, lx, tx;");
                                                            #line 1489 "PrintCpp.cpp.template"
                                                              }
                                                              if (isLrParser && ! useGlr)
                                                              {
                                                            #line 2142 "PrintCpp.cpp"
  append(L"\n");
  append(L"  std::vector<int> iStack;\n");
  append(L"  int top;");
                                                            #line 1494 "PrintCpp.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                                if (isLrParser)
                                                                {
                                                                  if (useGlr)
                                                                  {
                                                            #line 2154 "PrintCpp.cpp"
  append(L"\n");
  append(L"  int bw, bs, es;");
                                                            #line 1502 "PrintCpp.cpp.template"
                                                                  }
                                                            #line 2159 "PrintCpp.cpp"
  append(L"\n");
  append(L"  BottomUpEventHandler *eventHandler;");
                                                            #line 1504 "PrintCpp.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 2166 "PrintCpp.cpp"
  append(L"\n");
  append(L"  EventHandler *eventHandler;");
                                                            #line 1508 "PrintCpp.cpp.template"
                                                                }
                                                              }
                                                              if (memoization)
                                                              {
                                                            #line 2174 "PrintCpp.cpp"
  append(L"\n");
  append(L"  std::map<int, int> memo;");
                                                            #line 1513 "PrintCpp.cpp.template"
                                                                if (grammar->noThrow)
                                                                {
                                                            #line 2180 "PrintCpp.cpp"
  append(L"\n");
  append(L"  bool viable;");
                                                            #line 1516 "PrintCpp.cpp.template"
                                                                }
                                                              }
                                                              if (memoization)
                                                              {
                                                                int bits = Math::bits(grammar->conflictCount);
                                                            #line 2189 "PrintCpp.cpp"
  append(L"\n");
  append(L"\n");
  append(L"  void memoize(int i, int e, int v)\n");
  append(L"  {\n");
  append(L"    memo[(e << ");
                                                            #line 1525 "PrintCpp.cpp.template"
                                                                print(format.toString<wchar_t>(bits));
                                                            #line 2197 "PrintCpp.cpp"
  append(L") + i] = v;\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  int memoized(int i, int e)\n");
  append(L"  {\n");
  append(L"    std::map<int, int>::iterator v = memo.find((e << ");
                                                            #line 1531 "PrintCpp.cpp.template"
                                                                print(format.toString<wchar_t>(bits));
                                                            #line 2206 "PrintCpp.cpp"
  append(L") + i);\n");
  append(L"    return v != memo.end() ? v->second : 0;\n");
  append(L"  }");
                                                            #line 1534 "PrintCpp.cpp.template"
                                                              }
                                                            #line 2212 "PrintCpp.cpp"
  append(L"\n");
                                                            #line 1536 "PrintCpp.cpp.template"
                                                            }

                                                            void PrintCpp::printReadMethod()
                                                            {
                                                              if (main || performanceTest)
                                                              {
                                                            #line 2221 "PrintCpp.cpp"
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
                                                            #line 1552 "PrintCpp.cpp.template"
                                                              }
                                                              if (main || performanceTest || tree || trace)
                                                              {
                                                            #line 2236 "PrintCpp.cpp"
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
                                                            #line 1565 "PrintCpp.cpp.template"
                                                                if (! parseChars)
                                                                {
                                                            #line 2250 "PrintCpp.cpp"
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
                                                            #line 1639 "PrintCpp.cpp.template"
                                                                }
                                                              }
                                                              if (main || performanceTest)
                                                              {
                                                                if (! parseChars)
                                                                {
                                                            #line 2330 "PrintCpp.cpp"
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
                                                            #line 1730 "PrintCpp.cpp.template"
                                                                }
                                                            #line 2418 "PrintCpp.cpp"
  append(L"\n");
  append(L"static std::");
                                                            #line 1732 "PrintCpp.cpp.template"
                                                                if (! parseChars) append(L"w");
                                                            #line 2423 "PrintCpp.cpp"
  append(L"string read(const char *input)\n");
  append(L"{\n");
  append(L"  size_t l = strlen(input);\n");
  append(L"  if (l > 0 && input[0] == '{' && input[l - 1] == '}')\n");
  append(L"  {\n");
  append(L"    return ");
                                                            #line 1738 "PrintCpp.cpp.template"
                                                                if (parseChars)
                                                                {
                                                            #line 2433 "PrintCpp.cpp"
  append(L"std::string");
                                                            #line 1740 "PrintCpp.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 2439 "PrintCpp.cpp"
  append(L"Utf8Decoder::decode");
                                                            #line 1743 "PrintCpp.cpp.template"
                                                                }
                                                            #line 2443 "PrintCpp.cpp"
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
                                                            #line 1773 "PrintCpp.cpp.template"
                                                                if (! parseChars)
                                                                {
                                                            #line 2477 "PrintCpp.cpp"
  append(L"Utf8Decoder::decode(");
                                                            #line 1775 "PrintCpp.cpp.template"
                                                                }
                                                            #line 2481 "PrintCpp.cpp"
  append(L"content");
                                                            #line 1776 "PrintCpp.cpp.template"
                                                                if (! parseChars)
                                                                {
                                                            #line 2486 "PrintCpp.cpp"
  append(L".c_str())");
                                                            #line 1778 "PrintCpp.cpp.template"
                                                                }
                                                            #line 2490 "PrintCpp.cpp"
  append(L";\n");
  append(L"  }\n");
  append(L"}\n");
                                                            #line 1782 "PrintCpp.cpp.template"
                                                              }
                                                            }

                                                            void PrintCpp::printFileProcessor()
                                                            {
                                                            }

                                                            void PrintCpp::printSimpleMain()
                                                            {
                                                            #line 2504 "PrintCpp.cpp"
  append(L"\n");
  append(L"  static int main(int argc, char **argv)\n");
  append(L"  {\n");
  append(L"    int returnCode = 0;\n");
  append(L"\n");
  append(L"    if (argc < 2)\n");
  append(L"    {\n");
  append(L"      fprintf(stderr, \"Usage: %s ");
                                                            #line 1798 "PrintCpp.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 2516 "PrintCpp.cpp"
  append(L"[-i] ");
                                                            #line 1800 "PrintCpp.cpp.template"
                                                              }
                                                            #line 2520 "PrintCpp.cpp"
  append(L"INPUT...\\n\", argv[0]);\n");
  append(L"      fprintf(stderr, \"\\n\");\n");
  append(L"      fprintf(stderr, \"  parse INPUT, which is either a filename or literal text enclosed in curly braces\\n\");");
                                                            #line 1804 "PrintCpp.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 2527 "PrintCpp.cpp"
  append(L"\n");
  append(L"      fprintf(stderr, \"\\n\");\n");
  append(L"      fprintf(stderr, \"  Option:\\n\");\n");
  append(L"      fprintf(stderr, \"    -i     indented parse tree\\n\");");
                                                            #line 1809 "PrintCpp.cpp.template"
                                                              }
                                                            #line 2534 "PrintCpp.cpp"
  append(L"\n");
  append(L"    }\n");
  append(L"    else\n");
  append(L"    {\n");
  append(L"#ifdef _WIN32\n");
  append(L"      _setmode(1, O_BINARY);\n");
  append(L"#endif\n");
                                                            #line 1817 "PrintCpp.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 2545 "PrintCpp.cpp"
  append(L"\n");
  append(L"      bool indent = false;");
                                                            #line 1820 "PrintCpp.cpp.template"
                                                              }
                                                            #line 2550 "PrintCpp.cpp"
  append(L"\n");
  append(L"      for (int i = 1; i < argc; ++i)\n");
  append(L"      {");
                                                            #line 1823 "PrintCpp.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 2557 "PrintCpp.cpp"
  append(L"\n");
  append(L"        if (strcmp(argv[i], \"-i\") == 0)\n");
  append(L"        {\n");
  append(L"          indent = true;\n");
  append(L"          continue;\n");
  append(L"        }");
                                                            #line 1830 "PrintCpp.cpp.template"
                                                              }
                                                            #line 2566 "PrintCpp.cpp"
  append(L"\n");
  append(L"        try\n");
  append(L"        {");
                                                            #line 1833 "PrintCpp.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 2573 "PrintCpp.cpp"
  append(L"\n");
  append(L"          XmlSerializer s(indent);");
                                                            #line 1836 "PrintCpp.cpp.template"
                                                              }
                                                            #line 2578 "PrintCpp.cpp"
  append(L"\n");
  append(L"          std::");
                                                            #line 1838 "PrintCpp.cpp.template"
                                                              if (! parseChars) append(L"w");
                                                            #line 2583 "PrintCpp.cpp"
  append(L"string input = read(argv[i]);");
                                                            #line 1839 "PrintCpp.cpp.template"
                                                              if (tree && isLrParser)
                                                              {
                                                            #line 2588 "PrintCpp.cpp"
  append(L"\n");
  append(L"          ParseTreeBuilder t;");
                                                            #line 1842 "PrintCpp.cpp.template"
                                                              }
                                                            #line 2593 "PrintCpp.cpp"
  append(L"\n");
  append(L"          ");
                                                            #line 1844 "PrintCpp.cpp.template"
                                                              print(className.c_str());
                                                            #line 2598 "PrintCpp.cpp"
  append(L" parser(input.c_str()");
                                                            #line 1845 "PrintCpp.cpp.template"
                                                              if (tree)
                                                              {
                                                                if (isLrParser)
                                                                {
                                                            #line 2605 "PrintCpp.cpp"
  append(L", &t");
                                                            #line 1849 "PrintCpp.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 2611 "PrintCpp.cpp"
  append(L", &s");
                                                            #line 1852 "PrintCpp.cpp.template"
                                                                }
                                                              }
                                                            #line 2616 "PrintCpp.cpp"
  append(L");\n");
  append(L"          try\n");
  append(L"          {");
                                                            #line 1856 "PrintCpp.cpp.template"
                                                              if (trace)
                                                              {
                                                            #line 2623 "PrintCpp.cpp"
  append(L"\n");
  append(L"            fprintf(stderr, \"<?xml version=\\\"1.0\\\" encoding=\\\"UTF-8\\\"?>\\n\");\n");
  append(L"            fprintf(stderr, \"<trace>\\n\");");
                                                            #line 1860 "PrintCpp.cpp.template"
                                                              }
                                                            #line 2629 "PrintCpp.cpp"
  append(L"\n");
  append(L"            parser.");
                                                            #line 1862 "PrintCpp.cpp.template"
                                                              print(methodPrefix);
                                                              print(Format::acceptableName<WString>(grammar->startSymbol()->name).c_str());
                                                            #line 2635 "PrintCpp.cpp"
  append(L"();");
                                                            #line 1864 "PrintCpp.cpp.template"
                                                              if (trace)
                                                              {
                                                            #line 2640 "PrintCpp.cpp"
  append(L"\n");
  append(L"            fprintf(stderr, \"</trace>\\n\");");
                                                            #line 1867 "PrintCpp.cpp.template"
                                                              }
                                                              if (tree && isLrParser)
                                                              {
                                                            #line 2647 "PrintCpp.cpp"
  append(L"\n");
  append(L"            t.serialize(&s);");
                                                            #line 1871 "PrintCpp.cpp.template"
                                                              }
                                                            #line 2652 "PrintCpp.cpp"
  append(L"\n");
  append(L"          }\n");
  append(L"          catch (ParseException &pe)\n");
  append(L"          {");
                                                            #line 1875 "PrintCpp.cpp.template"
                                                              if (tree)
                                                              {
                                                                if (rejectsAmbiguity())
                                                                {
                                                            #line 2662 "PrintCpp.cpp"
  append(L"\n");
  append(L"            if (pe.isAmbiguousInput())\n");
  append(L"            {\n");
  append(L"              pe.serialize(&s);\n");
  append(L"              putchar('\\n');\n");
  append(L"              fflush(stdout);\n");
  append(L"            }");
                                                            #line 1885 "PrintCpp.cpp.template"
                                                                }
                                                            #line 2672 "PrintCpp.cpp"
  append(L"\n");
  append(L"            fprintf(stderr, \"\\n\");");
                                                            #line 1887 "PrintCpp.cpp.template"
                                                              }
                                                            #line 2677 "PrintCpp.cpp"
  append(L"\n");
  append(L"            fprintf(stderr, \"%s\\n\", ");
                                                            #line 1889 "PrintCpp.cpp.template"
                                                              if (! parseChars)
                                                              {
                                                            #line 2683 "PrintCpp.cpp"
  append(L"Utf8Encoder::encode(");
                                                            #line 1891 "PrintCpp.cpp.template"
                                                              }
                                                            #line 2687 "PrintCpp.cpp"
  append(L"parser.getErrorMessage(pe).c_str()");
                                                            #line 1893 "PrintCpp.cpp.template"
                                                              if (! parseChars)
                                                              {
                                                            #line 2692 "PrintCpp.cpp"
  append(L").c_str()");
                                                            #line 1896 "PrintCpp.cpp.template"
                                                              }
                                                            #line 2696 "PrintCpp.cpp"
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
                                                            #line 1919 "PrintCpp.cpp.template"
                                                            }

                                                            void PrintCpp::printPerformanceMain()
                                                            {
                                                            #line 2724 "PrintCpp.cpp"
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
                                                            #line 2004 "PrintCpp.cpp.template"
                                                              if (! parseChars)
                                                              {
                                                            #line 2810 "PrintCpp.cpp"
  append(L"Utf8Encoder::encode(");
                                                            #line 2007 "PrintCpp.cpp.template"
                                                              }
                                                            #line 2814 "PrintCpp.cpp"
  append(L"job->name->c_str()");
                                                            #line 2009 "PrintCpp.cpp.template"
                                                              if (! parseChars)
                                                              {
                                                            #line 2819 "PrintCpp.cpp"
  append(L").c_str()");
                                                            #line 2012 "PrintCpp.cpp.template"
                                                              }
                                                            #line 2823 "PrintCpp.cpp"
  append(L");\n");
  append(L"                job->parser->");
                                                            #line 2014 "PrintCpp.cpp.template"
                                                              if (useGlr)
                                                              {
                                                            #line 2829 "PrintCpp.cpp"
  append(L"thread->");
                                                            #line 2016 "PrintCpp.cpp.template"
                                                              }
                                                            #line 2833 "PrintCpp.cpp"
  append(L"reset(0, 0, 0);\n");
  append(L"                job->parser->");
                                                            #line 2018 "PrintCpp.cpp.template"
                                                              print(methodPrefix);
                                                              print(Format::acceptableName<WString>(grammar->startSymbol()->name).c_str());
                                                            #line 2839 "PrintCpp.cpp"
  append(L"();");
                                                            #line 2020 "PrintCpp.cpp.template"
                                                              if (useGlr)
                                                              {
                                                            #line 2844 "PrintCpp.cpp"
  append(L"\n");
  append(L"                job->parser->thread->cleanup();");
                                                            #line 2023 "PrintCpp.cpp.template"
                                                              }
                                                            #line 2849 "PrintCpp.cpp"
  append(L"\n");
  append(L"                if (! quiet) fprintf(stdout, \"\\n\");");
                                                            #line 2025 "PrintCpp.cpp.template"
                                                              if (tree)
                                                              {
                                                                if (isLrParser)
                                                                {
                                                            #line 2857 "PrintCpp.cpp"
  append(L"\n");
  append(L"                job->parseTreeBuilder->serialize(job->contentCounter);");
                                                            #line 2031 "PrintCpp.cpp.template"
                                                                }
                                                            #line 2862 "PrintCpp.cpp"
  append(L"\n");
  append(L"                if (job->contentCounter->getLength() != job->content->size())\n");
  append(L"                {\n");
  append(L"                  fprintf(stderr, \"content counter saw %d but input length is %d\\n\", job->contentCounter->getLength(), job->content->size());\n");
  append(L"                  exit(1);\n");
  append(L"                }");
                                                            #line 2037 "PrintCpp.cpp.template"
                                                              }
                                                            #line 2871 "PrintCpp.cpp"
  append(L"\n");
  append(L"                parsed += job->content->size();\n");
  append(L"              }\n");
  append(L"              catch (ParseException &pe)\n");
  append(L"              {\n");
  append(L"                ++errorCount;\n");
  append(L"                if (quiet) fprintf(stdout, \"parsing %s\", ");
                                                            #line 2044 "PrintCpp.cpp.template"
                                                              if (! parseChars)
                                                              {
                                                            #line 2882 "PrintCpp.cpp"
  append(L"Utf8Encoder::encode(");
                                                            #line 2047 "PrintCpp.cpp.template"
                                                              }
                                                            #line 2886 "PrintCpp.cpp"
  append(L"job->name->c_str()");
                                                            #line 2049 "PrintCpp.cpp.template"
                                                              if (! parseChars)
                                                              {
                                                            #line 2891 "PrintCpp.cpp"
  append(L").c_str()");
                                                            #line 2052 "PrintCpp.cpp.template"
                                                              }
                                                            #line 2895 "PrintCpp.cpp"
  append(L");\n");
  append(L"                fprintf(stdout, \": error:\\n%s\", ");
                                                            #line 2054 "PrintCpp.cpp.template"
                                                              if (! parseChars)
                                                              {
                                                            #line 2901 "PrintCpp.cpp"
  append(L"Utf8Encoder::encode(");
                                                            #line 2057 "PrintCpp.cpp.template"
                                                              }
                                                            #line 2905 "PrintCpp.cpp"
  append(L"job->parser->getErrorMessage(pe).c_str()");
                                                            #line 2059 "PrintCpp.cpp.template"
                                                              if (! parseChars)
                                                              {
                                                            #line 2910 "PrintCpp.cpp"
  append(L").c_str()");
                                                            #line 2062 "PrintCpp.cpp.template"
                                                              }
                                                            #line 2914 "PrintCpp.cpp"
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
                                                            #line 2090 "PrintCpp.cpp.template"
                                                            }

                                                            void PrintCpp::printPerformanceCode()
                                                            {
                                                              if (tree)
                                                              {
                                                            #line 2949 "PrintCpp.cpp"
  append(L"\n");
  append(L"  class ContentCounter : public EventHandler\n");
  append(L"  {\n");
  append(L"  public:\n");
  append(L"    ContentCounter() : length(0) {}\n");
  append(L"    size_t getLength() const {return length;}\n");
  append(L"\n");
  append(L"    void reset(");
                                                            #line 2103 "PrintCpp.cpp.template"
                                                                print(stringType());
                                                            #line 2960 "PrintCpp.cpp"
  append(L"string) {length = 0;}\n");
  append(L"    void startNonterminal(int id, int begin)  {}\n");
  append(L"    void endNonterminal(int id, int end)  {}\n");
  append(L"    void terminal(int id, int begin, int end)  {length += end - begin;}\n");
  append(L"    void whitespace(int begin, int end) {length += end - begin;}\n");
  append(L"\n");
  append(L"  private:\n");
  append(L"    size_t length;\n");
  append(L"  };\n");
                                                            #line 2113 "PrintCpp.cpp.template"
                                                              }
                                                            #line 2972 "PrintCpp.cpp"
  append(L"\n");
  append(L"  class ParseJob\n");
  append(L"  {\n");
  append(L"  public:\n");
  append(L"    ParseJob(const std::");
                                                            #line 2118 "PrintCpp.cpp.template"
                                                              if (! parseChars) append(L"w");
                                                            #line 2980 "PrintCpp.cpp"
  append(L"string &n, const std::");
                                                            #line 2119 "PrintCpp.cpp.template"
                                                              if (! parseChars) append(L"w");
                                                            #line 2984 "PrintCpp.cpp"
  append(L"string &c)\n");
  append(L"    : name(0), content(0), parser(0)");
                                                            #line 2121 "PrintCpp.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 2990 "PrintCpp.cpp"
  append(L", contentCounter(0)");
                                                            #line 2123 "PrintCpp.cpp.template"
                                                                if (isLrParser)
                                                                {
                                                            #line 2995 "PrintCpp.cpp"
  append(L", parseTreeBuilder(0)");
                                                            #line 2126 "PrintCpp.cpp.template"
                                                                }
                                                              }
                                                            #line 3000 "PrintCpp.cpp"
  append(L"\n");
  append(L"    {\n");
  append(L"      name = new std::");
                                                            #line 2130 "PrintCpp.cpp.template"
                                                              if (! parseChars) append(L"w");
                                                            #line 3006 "PrintCpp.cpp"
  append(L"string(n);\n");
  append(L"      content = new std::");
                                                            #line 2132 "PrintCpp.cpp.template"
                                                              if (! parseChars) append(L"w");
                                                            #line 3011 "PrintCpp.cpp"
  append(L"string(c);");
                                                            #line 2133 "PrintCpp.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 3016 "PrintCpp.cpp"
  append(L"\n");
  append(L"      contentCounter = new ContentCounter();");
                                                            #line 2136 "PrintCpp.cpp.template"
                                                                if (isLrParser)
                                                                {
                                                            #line 3022 "PrintCpp.cpp"
  append(L"\n");
  append(L"      parseTreeBuilder = new ParseTreeBuilder();");
                                                            #line 2139 "PrintCpp.cpp.template"
                                                                }
                                                              }
                                                            #line 3028 "PrintCpp.cpp"
  append(L"\n");
  append(L"      parser = new ");
                                                            #line 2142 "PrintCpp.cpp.template"
                                                              print(className.c_str());
                                                            #line 3033 "PrintCpp.cpp"
  append(L"(content->c_str()");
                                                            #line 2143 "PrintCpp.cpp.template"
                                                              if (tree)
                                                              {
                                                                if (isLrParser)
                                                                {
                                                            #line 3040 "PrintCpp.cpp"
  append(L", parseTreeBuilder");
                                                            #line 2147 "PrintCpp.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 3046 "PrintCpp.cpp"
  append(L", contentCounter");
                                                            #line 2150 "PrintCpp.cpp.template"
                                                                }
                                                              }
                                                            #line 3051 "PrintCpp.cpp"
  append(L");\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    void cleanup()\n");
  append(L"    {\n");
  append(L"      delete name;\n");
  append(L"      delete content;\n");
  append(L"      delete parser;");
                                                            #line 2159 "PrintCpp.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 3063 "PrintCpp.cpp"
  append(L"\n");
  append(L"      delete contentCounter;");
                                                            #line 2162 "PrintCpp.cpp.template"
                                                                if (isLrParser)
                                                                {
                                                            #line 3069 "PrintCpp.cpp"
  append(L"\n");
  append(L"      delete parseTreeBuilder;");
                                                            #line 2165 "PrintCpp.cpp.template"
                                                                }
                                                              }
                                                            #line 3075 "PrintCpp.cpp"
  append(L"\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    std::");
                                                            #line 2170 "PrintCpp.cpp.template"
                                                              if (! parseChars) append(L"w");
                                                            #line 3082 "PrintCpp.cpp"
  append(L"string *name;\n");
  append(L"    std::");
                                                            #line 2172 "PrintCpp.cpp.template"
                                                              if (! parseChars) append(L"w");
                                                            #line 3087 "PrintCpp.cpp"
  append(L"string *content;\n");
  append(L"    ");
                                                            #line 2174 "PrintCpp.cpp.template"
                                                              print(className.c_str());
                                                            #line 3092 "PrintCpp.cpp"
  append(L" *parser;");
                                                            #line 2175 "PrintCpp.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 3097 "PrintCpp.cpp"
  append(L"\n");
  append(L"    ContentCounter *contentCounter;");
                                                            #line 2178 "PrintCpp.cpp.template"
                                                                if (isLrParser)
                                                                {
                                                            #line 3103 "PrintCpp.cpp"
  append(L"\n");
  append(L"    ParseTreeBuilder *parseTreeBuilder;");
                                                            #line 2181 "PrintCpp.cpp.template"
                                                                }
                                                              }
                                                            #line 3109 "PrintCpp.cpp"
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
                                                            #line 2329 "PrintCpp.cpp.template"
                                                              print(className.c_str());
                                                            #line 3259 "PrintCpp.cpp"
  append(L"::quiet) fprintf(stdout, \"loading %s\\n\", path);\n");
  append(L"        parsers.push_back(ParseJob(");
                                                            #line 2331 "PrintCpp.cpp.template"
                                                              if (parseChars)
                                                              {
                                                            #line 3265 "PrintCpp.cpp"
  append(L"std::string");
                                                            #line 2333 "PrintCpp.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 3271 "PrintCpp.cpp"
  append(L"Utf8Decoder::decode");
                                                            #line 2336 "PrintCpp.cpp.template"
                                                              }
                                                            #line 3275 "PrintCpp.cpp"
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
                                                            #line 2358 "PrintCpp.cpp.template"
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
                                                            #line 3315 "PrintCpp.cpp"
  append(L"\n");
  append(L"  std::");
                                                            #line 2376 "PrintCpp.cpp.template"
                                                                print(stringIntroducer()[0] ? L"w" : L"");
                                                            #line 3320 "PrintCpp.cpp"
  append(L"string lookaheadString()\n");
  append(L"  {\n");
  append(L"    std::");
                                                            #line 2379 "PrintCpp.cpp.template"
                                                                print(stringIntroducer()[0] ? L"w" : L"");
                                                            #line 3326 "PrintCpp.cpp"
  append(L"string result;\n");
  append(L"    if (");
                                                            #line 2381 "PrintCpp.cpp.template"
                                                                print(thiz());
                                                            #line 3331 "PrintCpp.cpp"
  append(L"l1 > 0)\n");
  append(L"    {\n");
  append(L"      result += ");
                                                            #line 2384 "PrintCpp.cpp.template"
                                                                print(staticPrefix());
                                                            #line 3337 "PrintCpp.cpp"
  append(L"TOKEN[");
                                                            #line 2385 "PrintCpp.cpp.template"
                                                                print(thiz());
                                                            #line 3341 "PrintCpp.cpp"
  append(L"l1];");
                                                            #line 2386 "PrintCpp.cpp.template"
                                                                for (size_t i = 2; i <= grammar->k; ++i)
                                                                {
                                                            #line 3346 "PrintCpp.cpp"
  append(L"\n");
  append(L"      if (");
                                                            #line 2389 "PrintCpp.cpp.template"
                                                                  print(thiz());
                                                            #line 3351 "PrintCpp.cpp"
  append(L"l");
                                                            #line 2390 "PrintCpp.cpp.template"
                                                                  print(format.toString<wchar_t>(i));
                                                            #line 3355 "PrintCpp.cpp"
  append(L" > 0)\n");
  append(L"      {\n");
  append(L"        result += ");
                                                            #line 2393 "PrintCpp.cpp.template"
                                                                  print(stringIntroducer());
                                                            #line 3361 "PrintCpp.cpp"
  append(L"\" \";\n");
  append(L"        result += ");
                                                            #line 2395 "PrintCpp.cpp.template"
                                                                  print(staticPrefix());
                                                            #line 3366 "PrintCpp.cpp"
  append(L"TOKEN[");
                                                            #line 2396 "PrintCpp.cpp.template"
                                                                  print(thiz());
                                                            #line 3370 "PrintCpp.cpp"
  append(L"l");
                                                            #line 2397 "PrintCpp.cpp.template"
                                                                  print(format.toString<wchar_t>(i));
                                                            #line 3374 "PrintCpp.cpp"
  append(L"];");
                                                            #line 2398 "PrintCpp.cpp.template"
                                                                  increaseIndent();
                                                                }
                                                                for (size_t i = 2; i <= grammar->k; ++i)
                                                                {
                                                                  decreaseIndent();
                                                            #line 3382 "PrintCpp.cpp"
  append(L"\n");
  append(L"      }");
                                                            #line 2404 "PrintCpp.cpp.template"
                                                                }
                                                            #line 3387 "PrintCpp.cpp"
  append(L"\n");
  append(L"    }\n");
  append(L"    return result;\n");
  append(L"  }\n");
                                                            #line 2409 "PrintCpp.cpp.template"
                                                              }
                                                              if (useGlr)
                                                              {
                                                            #line 3396 "PrintCpp.cpp"
  append(L"\n");
  append(L"};\n");
  append(L"\n");
  append(L"ParsingThread *thread;");
                                                            #line 2415 "PrintCpp.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 3404 "PrintCpp.cpp"
  append(L"\n");
  append(L"BottomUpEventHandler *eventHandler;");
                                                            #line 2418 "PrintCpp.cpp.template"
                                                                }
                                                            #line 3409 "PrintCpp.cpp"
  append(L"\n");
  append(L"const ");
                                                            #line 2420 "PrintCpp.cpp.template"
                                                                if (parseChars)
                                                                {
                                                            #line 3415 "PrintCpp.cpp"
  append(L"char");
                                                            #line 2422 "PrintCpp.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 3421 "PrintCpp.cpp"
  append(L"wchar_t");
                                                            #line 2425 "PrintCpp.cpp.template"
                                                                }
                                                            #line 3425 "PrintCpp.cpp"
  append(L" *input;\n");
  append(L"int size;\n");
  append(L"int maxId;\n");
                                                            #line 2429 "PrintCpp.cpp.template"
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
