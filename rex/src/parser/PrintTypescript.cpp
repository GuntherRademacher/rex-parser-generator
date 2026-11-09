// This file was generated on Sun Nov 8, 2026 22:38 (UTC+01) by REx v7.0-SNAPSHOT which is Copyright (c) 1979-2026 by Gunther Rademacher <grd@gmx.net>
// REx command line: PrintTypescript.cpp.template
                                                            #line 1 "PrintTypescript.cpp.template"
                                                            #include "../common/Memory.hpp"

                                                            #include "PrintTypescript.hpp"
                                                            #include "ItemSet.hpp"

                                                            void PrintTypescript::openClass()
                                                            {
                                                              if (! hasProlog)
                                                              {
                                                            #line 14 "PrintTypescript.cpp"
  append(L"\n");
  append(L"export namespace ");
                                                            #line 11 "PrintTypescript.cpp.template"
                                                                print(className.c_str());
                                                            #line 19 "PrintTypescript.cpp"
  append(L"\n");
  append(L"{");
                                                            #line 13 "PrintTypescript.cpp.template"
                                                              }
                                                            #line 24 "PrintTypescript.cpp"
  append(L"\n");
  append(L"  export interface ParsingEventHandler\n");
  append(L"  {\n");
  append(L"    reset(source: string): void;\n");
  append(L"    startNonterminal(id: number, begin: number): void;\n");
  append(L"    endNonterminal(id: number, end: number): void;\n");
  append(L"    terminal(id: number, begin: number, end: number): void;\n");
  append(L"    whitespace(begin: number, end: number): void;\n");
  append(L"  }\n");
                                                            #line 23 "PrintTypescript.cpp.template"
                                                              if (isLrParser)
                                                              {
                                                            #line 37 "PrintTypescript.cpp"
  append(L"\n");
  append(L"  export interface BottomUpEventHandler\n");
  append(L"  {\n");
  append(L"    reset(input: string): void;\n");
  append(L"    nonterminal(id: number, begin: number, end: number, count: number): void;\n");
  append(L"    terminal(id: number, begin: number, end: number): void;");
                                                            #line 30 "PrintTypescript.cpp.template"
                                                                if (resolvesAmbiguity)
                                                                {
                                                            #line 47 "PrintTypescript.cpp"
  append(L"\n");
  append(L"    ambiguity(begin: number, end: number): void;");
                                                            #line 33 "PrintTypescript.cpp.template"
                                                                }
                                                            #line 52 "PrintTypescript.cpp"
  append(L"\n");
  append(L"  }\n");
                                                            #line 36 "PrintTypescript.cpp.template"
                                                              }
                                                            #line 57 "PrintTypescript.cpp"
  append(L"\n");
  append(L"  export class ParseException\n");
  append(L"  {\n");
  append(L"    private begin: number;\n");
  append(L"    private end: number;\n");
  append(L"    private state: number;\n");
  append(L"    private offending: number;\n");
  append(L"    private expected: number;");
                                                            #line 44 "PrintTypescript.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 69 "PrintTypescript.cpp"
  append(L"\n");
  append(L"    private ambiguousInput: boolean;");
                                                            #line 47 "PrintTypescript.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 75 "PrintTypescript.cpp"
  append(L"\n");
  append(L"    private ambiguityDescriptor: ParseTreeBuilder | null = null;");
                                                            #line 51 "PrintTypescript.cpp.template"
                                                                }
                                                              }
                                                            #line 81 "PrintTypescript.cpp"
  append(L"\n");
  append(L"\n");
  append(L"    constructor(b: number, e: number, s: number, o: number, x: number)\n");
  append(L"    {\n");
  append(L"      this.begin = b;\n");
  append(L"      this.end = e;\n");
  append(L"      this.state = s;\n");
  append(L"      this.offending = o;\n");
  append(L"      this.expected = x;");
                                                            #line 61 "PrintTypescript.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 94 "PrintTypescript.cpp"
  append(L"\n");
  append(L"      this.ambiguousInput = false;");
                                                            #line 64 "PrintTypescript.cpp.template"
                                                                if (tree)
                                                                {
                                                                }
                                                              }
                                                            #line 102 "PrintTypescript.cpp"
  append(L"\n");
  append(L"    }\n");
                                                            #line 70 "PrintTypescript.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 108 "PrintTypescript.cpp"
  append(L"\n");
  append(L"    setAmbiguousInput(");
                                                            #line 73 "PrintTypescript.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 114 "PrintTypescript.cpp"
  append(L"a: ParseTreeBuilder");
                                                            #line 75 "PrintTypescript.cpp.template"
                                                                }
                                                            #line 118 "PrintTypescript.cpp"
  append(L")\n");
  append(L"    {\n");
  append(L"      this.ambiguousInput = true;");
                                                            #line 78 "PrintTypescript.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 125 "PrintTypescript.cpp"
  append(L"\n");
  append(L"      this.ambiguityDescriptor = a;");
                                                            #line 81 "PrintTypescript.cpp.template"
                                                                }
                                                            #line 130 "PrintTypescript.cpp"
  append(L"\n");
  append(L"    }\n");
                                                            #line 84 "PrintTypescript.cpp.template"
                                                              }
                                                            #line 135 "PrintTypescript.cpp"
  append(L"\n");
  append(L"    getBegin() {return this.begin;}\n");
  append(L"    getEnd() {return this.end;}\n");
  append(L"    getState() {return this.state;}\n");
  append(L"    getExpected() {return this.expected;}\n");
  append(L"    getOffending() {return this.offending;}\n");
  append(L"    isAmbiguousInput() {return ");
                                                            #line 91 "PrintTypescript.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 146 "PrintTypescript.cpp"
  append(L"this.ambiguousInput");
                                                            #line 93 "PrintTypescript.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 152 "PrintTypescript.cpp"
  append(L"false");
                                                            #line 96 "PrintTypescript.cpp.template"
                                                              }
                                                            #line 156 "PrintTypescript.cpp"
  append(L";}\n");
  append(L"\n");
  append(L"    getMessage()\n");
  append(L"    {\n");
  append(L"      return ");
                                                            #line 101 "PrintTypescript.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 165 "PrintTypescript.cpp"
  append(L"this.ambiguousInput\n");
  append(L"           ? \"ambiguous input\"\n");
  append(L"           : ");
                                                            #line 105 "PrintTypescript.cpp.template"
                                                              }
                                                            #line 171 "PrintTypescript.cpp"
  append(L"this.offending < 0\n");
  append(L"           ? \"lexical analysis failed\"\n");
  append(L"           : \"syntax error\";\n");
  append(L"    }");
                                                            #line 109 "PrintTypescript.cpp.template"
                                                              if (rejectsAmbiguity() && tree)
                                                              {
                                                            #line 179 "PrintTypescript.cpp"
  append(L"\n");
  append(L"\n");
  append(L"    serialize(eventHandler: ParsingEventHandler)\n");
  append(L"    {\n");
  append(L"      this.ambiguityDescriptor!.serialize(eventHandler);\n");
  append(L"    }");
                                                            #line 116 "PrintTypescript.cpp.template"
                                                              }
                                                            #line 188 "PrintTypescript.cpp"
  append(L"\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  interface Memoizer\n");
  append(L"  {\n");
  append(L"    [index: number]: number;\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  export class Parser\n");
  append(L"  {\n");
  append(L"    constructor(source: string");
                                                            #line 127 "PrintTypescript.cpp.template"
                                                              if (noLexer)
                                                              {
                                                            #line 203 "PrintTypescript.cpp"
  append(L", l: Lexer");
                                                            #line 129 "PrintTypescript.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                            #line 209 "PrintTypescript.cpp"
  append(L", parsingEventHandler: ");
                                                            #line 132 "PrintTypescript.cpp.template"
                                                                if (isLrParser)
                                                                {
                                                            #line 214 "PrintTypescript.cpp"
  append(L"BottomUp");
                                                            #line 135 "PrintTypescript.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 220 "PrintTypescript.cpp"
  append(L"Parsing");
                                                            #line 138 "PrintTypescript.cpp.template"
                                                                }
                                                            #line 224 "PrintTypescript.cpp"
  append(L"EventHandler");
                                                            #line 140 "PrintTypescript.cpp.template"
                                                              }
                                                            #line 228 "PrintTypescript.cpp"
  append(L")\n");
  append(L"    {\n");
  append(L"      this.initialize(source");
                                                            #line 143 "PrintTypescript.cpp.template"
                                                              if (noLexer)
                                                              {
                                                            #line 235 "PrintTypescript.cpp"
  append(L", l");
                                                            #line 145 "PrintTypescript.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                            #line 241 "PrintTypescript.cpp"
  append(L", parsingEventHandler");
                                                            #line 148 "PrintTypescript.cpp.template"
                                                              }
                                                            #line 245 "PrintTypescript.cpp"
  append(L");\n");
  append(L"    }\n");
                                                            #line 151 "PrintTypescript.cpp.template"
                                                              increaseIndent();
                                                            }

                                                            void PrintTypescript::printFlush(int i, bool withinThread)
                                                            {
                                                              increaseIndent(i);
                                                              if (trace)
                                                              {
                                                            #line 257 "PrintTypescript.cpp"
  append(L"\n");
  append(L"parser.flushTrace();");
                                                            #line 160 "PrintTypescript.cpp.template"
                                                              }
                                                              decreaseIndent(i);
                                                            }

                                                            void PrintTypescript::printGlrParseMethod()
                                                            {
                                                            #line 267 "PrintTypescript.cpp"
  append(L"\n");
  append(L"public static PARSING = 0;\n");
  append(L"public static ACCEPTED = 1;\n");
  append(L"public static ERROR = 2;\n");
  append(L"\n");
  append(L"public parse(target: number, initialState: number, ");
                                                            #line 171 "PrintTypescript.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 277 "PrintTypescript.cpp"
  append(L"eventHandler: BottomUpEventHandler | null, ");
                                                            #line 174 "PrintTypescript.cpp.template"
                                                              }
                                                            #line 281 "PrintTypescript.cpp"
  append(L"thread: ParsingThread): ParsingThread\n");
  append(L"{\n");
  append(L"  var threads: Heap = thread.open(initialState");
                                                            #line 177 "PrintTypescript.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 288 "PrintTypescript.cpp"
  append(L", eventHandler, target");
                                                            #line 180 "PrintTypescript.cpp.template"
                                                              }
                                                            #line 292 "PrintTypescript.cpp"
  append(L");\n");
  append(L"  while (true)\n");
  append(L"  {\n");
  append(L"    thread = threads.poll();\n");
  append(L"    if (thread.accepted)\n");
  append(L"    {");
                                                            #line 186 "PrintTypescript.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 302 "PrintTypescript.cpp"
  append(L"\n");
  append(L"      var other = null;\n");
  append(L"      while (! threads.isEmpty())\n");
  append(L"      {\n");
  append(L"        other = threads.poll();\n");
  append(L"        if (thread.e0 < other.e0)\n");
  append(L"        {\n");
  append(L"          thread = other;\n");
  append(L"          other = null;\n");
  append(L"        }\n");
  append(L"      }\n");
  append(L"      if (other != null)\n");
  append(L"      {\n");
  append(L"        this.rejectAmbiguity(thread.stack.pos, thread.e0");
                                                            #line 201 "PrintTypescript.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 320 "PrintTypescript.cpp"
  append(L", thread.deferredEvent!, other.deferredEvent!");
                                                            #line 203 "PrintTypescript.cpp.template"
                                                                }
                                                            #line 324 "PrintTypescript.cpp"
  append(L");\n");
  append(L"      }");
                                                            #line 205 "PrintTypescript.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 331 "PrintTypescript.cpp"
  append(L"\n");
  append(L"      while (! threads.isEmpty())\n");
  append(L"      {\n");
  append(L"        var other = threads.poll();\n");
  append(L"        thread = thread.e0 < other.e0 ? other : this.resolve(thread, other);\n");
  append(L"      }");
                                                            #line 213 "PrintTypescript.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                            #line 342 "PrintTypescript.cpp"
  append(L"\n");
  append(L"      if (thread.deferredEvent != null)\n");
  append(L"      {\n");
  append(L"        thread.deferredEvent.release(eventHandler!);\n");
  append(L"        thread.deferredEvent = null;\n");
  append(L"      }");
                                                            #line 221 "PrintTypescript.cpp.template"
                                                              }
                                                              if (hasCustomCode)
                                                              {
                                                            #line 353 "PrintTypescript.cpp"
  append(L"\n");
  append(L"      thread.executeDeferredCode();");
                                                            #line 225 "PrintTypescript.cpp.template"
                                                              }
                                                            #line 358 "PrintTypescript.cpp"
  append(L"\n");
  append(L"      return thread;\n");
  append(L"    }\n");
  append(L"\n");
                                                            #line 230 "PrintTypescript.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 366 "PrintTypescript.cpp"
  append(L"    if (! threads.isEmpty())\n");
  append(L"    {\n");
  append(L"      if (threads.peek().equals(thread))\n");
  append(L"      {\n");
  append(L"        this.rejectAmbiguity(thread.stack.pos, thread.e0");
                                                            #line 236 "PrintTypescript.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 375 "PrintTypescript.cpp"
  append(L", thread.deferredEvent!, threads.peek().deferredEvent!");
                                                            #line 238 "PrintTypescript.cpp.template"
                                                                }
                                                            #line 379 "PrintTypescript.cpp"
  append(L");\n");
  append(L"      }\n");
  append(L"    }");
                                                            #line 241 "PrintTypescript.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 387 "PrintTypescript.cpp"
  append(L"    while (! threads.isEmpty() && threads.peek().equals(thread))\n");
  append(L"    {\n");
  append(L"      thread = this.resolve(thread, threads.poll());\n");
  append(L"    }");
                                                            #line 247 "PrintTypescript.cpp.template"
                                                              }
                                                              if (tree || hasCustomCode)
                                                              {
                                                                if (rejectsAmbiguity())
                                                                {
                                                            #line 398 "PrintTypescript.cpp"
  append(L"\n");
  append(L"    else\n");
  append(L"    {");
                                                            #line 254 "PrintTypescript.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 406 "PrintTypescript.cpp"
  append(L"\n");
  append(L"    if (threads.isEmpty())\n");
  append(L"    {");
                                                            #line 259 "PrintTypescript.cpp.template"
                                                                }
                                                                if (tree)
                                                                {
                                                            #line 414 "PrintTypescript.cpp"
  append(L"\n");
  append(L"      if (thread.deferredEvent != null)\n");
  append(L"      {\n");
  append(L"        thread.deferredEvent.release(eventHandler!);\n");
  append(L"        thread.deferredEvent = null;\n");
  append(L"      }");
                                                            #line 267 "PrintTypescript.cpp.template"
                                                                }
                                                                if (hasCustomCode)
                                                                {
                                                            #line 425 "PrintTypescript.cpp"
  append(L"\n");
  append(L"      thread.executeDeferredCode();");
                                                            #line 271 "PrintTypescript.cpp.template"
                                                                }
                                                            #line 430 "PrintTypescript.cpp"
  append(L"\n");
  append(L"    }");
                                                            #line 273 "PrintTypescript.cpp.template"
                                                              }
                                                            #line 435 "PrintTypescript.cpp"
  append(L"\n");
  append(L"\n");
  append(L"    var status = Parser.PARSING;\n");
  append(L"    while (true)\n");
  append(L"    {\n");
  append(L"      if ((status = thread.parse()) != Parser.PARSING) break;\n");
  append(L"      if (! threads.isEmpty()) break;\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    if (status != Parser.ERROR)\n");
  append(L"    {\n");
  append(L"      threads.offer(thread);\n");
  append(L"    }\n");
  append(L"    else if (threads.isEmpty())\n");
  append(L"    {\n");
  append(L"      throw new ParseException(thread.b1,\n");
  append(L"                               thread.e1,\n");
  append(L"                               Parser.TOKENSET[thread.state] + 1,\n");
  append(L"                               thread.l1,\n");
  append(L"                               -1\n");
  append(L"                              );\n");
  append(L"    }\n");
  append(L"  }\n");
  append(L"}\n");
                                                            #line 298 "PrintTypescript.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 463 "PrintTypescript.cpp"
  append(L"\n");
  append(L"private rejectAmbiguity(begin: number, end: number");
                                                            #line 301 "PrintTypescript.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 469 "PrintTypescript.cpp"
  append(L", first: DeferredEvent, second: DeferredEvent");
                                                            #line 303 "PrintTypescript.cpp.template"
                                                                }
                                                            #line 473 "PrintTypescript.cpp"
  append(L"): void\n");
  append(L"{");
                                                            #line 305 "PrintTypescript.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 479 "PrintTypescript.cpp"
  append(L"\n");
  append(L"  var treeBuilder = new ParseTreeBuilder();\n");
  append(L"  treeBuilder.reset(this.input);\n");
  append(L"  second.show(treeBuilder);\n");
  append(L"  treeBuilder.nonterminal(");
                                                            #line 311 "PrintTypescript.cpp.template"
                                                                  print(format.toString<wchar_t>(Grammar::syntheticNonterminalCode(0)));
                                                            #line 487 "PrintTypescript.cpp"
  append(L", treeBuilder.getStack()[0].begin, treeBuilder.getStack()[treeBuilder.getTop()].end, treeBuilder.getTop() + 1);\n");
  append(L"  var secondTree = treeBuilder.pop(1)[0];\n");
  append(L"  first.show(treeBuilder);\n");
  append(L"  treeBuilder.nonterminal(");
                                                            #line 315 "PrintTypescript.cpp.template"
                                                                  print(format.toString<wchar_t>(Grammar::syntheticNonterminalCode(0)));
                                                            #line 494 "PrintTypescript.cpp"
  append(L", treeBuilder.getStack()[0].begin, treeBuilder.getStack()[treeBuilder.getTop()].end, treeBuilder.getTop() + 1);\n");
  append(L"  treeBuilder.push(secondTree);\n");
  append(L"  treeBuilder.nonterminal(");
                                                            #line 318 "PrintTypescript.cpp.template"
                                                                  print(format.toString<wchar_t>(Grammar::syntheticNonterminalCode(1)));
                                                            #line 500 "PrintTypescript.cpp"
  append(L", treeBuilder.getStack()[0].begin, treeBuilder.getStack()[treeBuilder.getTop()].end, 2);");
                                                            #line 320 "PrintTypescript.cpp.template"
                                                                }
                                                            #line 504 "PrintTypescript.cpp"
  append(L"\n");
  append(L"  var exception = new ParseException(begin, end, -1, -1, -1);\n");
  append(L"  exception.setAmbiguousInput(");
                                                            #line 323 "PrintTypescript.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 511 "PrintTypescript.cpp"
  append(L"treeBuilder");
                                                            #line 325 "PrintTypescript.cpp.template"
                                                                }
                                                            #line 515 "PrintTypescript.cpp"
  append(L");\n");
  append(L"  throw exception;\n");
  append(L"}");
                                                            #line 328 "PrintTypescript.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 523 "PrintTypescript.cpp"
  append(L"\n");
  append(L"private resolve(thread: ParsingThread, other: ParsingThread): ParsingThread\n");
  append(L"{");
                                                            #line 333 "PrintTypescript.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 530 "PrintTypescript.cpp"
  append(L"\n");
  append(L"  var a: StackNode | null = thread.stack;\n");
  append(L"  var b: StackNode | null = other.stack;\n");
  append(L"  var begin = thread.stack.pos;\n");
  append(L"  while (a != b && a != null && b != null)\n");
  append(L"  {\n");
  append(L"    begin = a.pos;\n");
  append(L"    a = a.link;\n");
  append(L"    b = b.link;\n");
  append(L"  }");
                                                            #line 344 "PrintTypescript.cpp.template"
                                                                }
                                                            #line 543 "PrintTypescript.cpp"
  append(L"\n");
                                                            #line 346 "PrintTypescript.cpp.template"
                                                                if (shiftAmbiguity)
                                                                {
                                                            #line 548 "PrintTypescript.cpp"
  append(L"\n");
  append(L"  var ea: DeferredEvent | null = thread.deferredEvent;\n");
  append(L"  var eb: DeferredEvent | null = other.deferredEvent;\n");
  append(L"  var ua: DeferredEvent | null = null;\n");
  append(L"  var ub: DeferredEvent | null = null;\n");
  append(L"  while (ea != eb)\n");
  append(L"  {\n");
  append(L"    if ((ea == null ? 0 : ea.getDepth()) >= (eb == null ? 0 : eb.getDepth()))\n");
  append(L"    {\n");
  append(L"      ua = ea;\n");
  append(L"      ea = ea!.getLink();\n");
  append(L"    }\n");
  append(L"    else\n");
  append(L"    {\n");
  append(L"      ub = eb;\n");
  append(L"      eb = eb!.getLink();\n");
  append(L"    }\n");
  append(L"  }\n");
  append(L"  var sa = ua != null && ua.isTerminal();\n");
  append(L"  var sb = ub != null && ub.isTerminal();\n");
  append(L"  if (sa != sb)\n");
  append(L"  {\n");
  append(L"    if (sb)\n");
  append(L"      thread = other;\n");
  append(L"  }\n");
  append(L"  else if (other.eventCount < thread.eventCount)\n");
  append(L"    thread = other;");
                                                            #line 374 "PrintTypescript.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 580 "PrintTypescript.cpp"
  append(L"\n");
  append(L"  if (other.eventCount < thread.eventCount)\n");
  append(L"    thread = other;");
                                                            #line 379 "PrintTypescript.cpp.template"
                                                                }
                                                                if (tree)
                                                                {
                                                            #line 588 "PrintTypescript.cpp"
  append(L"\n");
  append(L"  thread.addAmbiguity(begin, thread.e0);");
                                                            #line 383 "PrintTypescript.cpp.template"
                                                                }
                                                            #line 593 "PrintTypescript.cpp"
  append(L"\n");
  append(L"  return thread;\n");
  append(L"}");
                                                            #line 386 "PrintTypescript.cpp.template"
                                                              }
                                                            #line 599 "PrintTypescript.cpp"
  append(L"\n");
  append(L"\n");
  append(L"private thread!: ParsingThread;");
                                                            #line 389 "PrintTypescript.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 606 "PrintTypescript.cpp"
  append(L"\n");
  append(L"private eventHandler!: BottomUpEventHandler | null;");
                                                            #line 392 "PrintTypescript.cpp.template"
                                                              }
                                                            #line 611 "PrintTypescript.cpp"
  append(L"\n");
  append(L"public input!: string;\n");
  append(L"public size!: number;\n");
  append(L"public maxId!: number;");
                                                            #line 396 "PrintTypescript.cpp.template"
                                                            }

                                                            void PrintTypescript::openStackNode()
                                                            {
                                                            #line 621 "PrintTypescript.cpp"
  append(L"\n");
  append(L"class StackNode\n");
  append(L"{\n");
  append(L"  public state: number;");
                                                            #line 403 "PrintTypescript.cpp.template"
                                                              if (grammar->states->hasLookback)
                                                              {
                                                            #line 629 "PrintTypescript.cpp"
  append(L"\n");
  append(L"  private code: number;");
                                                            #line 406 "PrintTypescript.cpp.template"
                                                              }
                                                            #line 634 "PrintTypescript.cpp"
  append(L"\n");
  append(L"  public pos: number;\n");
  append(L"  public link: StackNode | null;\n");
  append(L"\n");
  append(L"  constructor(state: number, ");
                                                            #line 411 "PrintTypescript.cpp.template"
                                                              if (grammar->states->hasLookback)
                                                              {
                                                            #line 643 "PrintTypescript.cpp"
  append(L"code: number, ");
                                                            #line 413 "PrintTypescript.cpp.template"
                                                              }
                                                            #line 647 "PrintTypescript.cpp"
  append(L"pos: number, link: StackNode | null)\n");
  append(L"  {\n");
  append(L"    this.state = state;");
                                                            #line 416 "PrintTypescript.cpp.template"
                                                              if (grammar->states->hasLookback)
                                                              {
                                                            #line 654 "PrintTypescript.cpp"
  append(L"\n");
  append(L"    this.code = code;");
                                                            #line 419 "PrintTypescript.cpp.template"
                                                              }
                                                            #line 659 "PrintTypescript.cpp"
  append(L"\n");
  append(L"    this.pos = pos;\n");
  append(L"    this.link = link;\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  equals(obj: StackNode)\n");
  append(L"  {\n");
  append(L"    var lhs: StackNode | null = this;\n");
  append(L"    var rhs: StackNode | null = obj;\n");
  append(L"    while (lhs != null && rhs != null)\n");
  append(L"    {\n");
  append(L"      if (lhs == rhs) return true;\n");
  append(L"      if (lhs.state != rhs.state) return false;");
                                                            #line 432 "PrintTypescript.cpp.template"
                                                              if (grammar->states->hasLookback)
                                                              {
                                                            #line 676 "PrintTypescript.cpp"
  append(L"\n");
  append(L"      if (lhs.code != rhs.code) return false;");
                                                            #line 435 "PrintTypescript.cpp.template"
                                                              }
                                                            #line 681 "PrintTypescript.cpp"
  append(L"\n");
  append(L"      if (lhs.pos != rhs.pos) return false;\n");
  append(L"      lhs = lhs.link;\n");
  append(L"      rhs = rhs.link;\n");
  append(L"    }\n");
  append(L"    return lhs == rhs;\n");
  append(L"  }\n");
                                                            #line 443 "PrintTypescript.cpp.template"
                                                              increaseIndent();
                                                            }

                                                            void PrintTypescript::closeStackNode()
                                                            {
                                                              decreaseIndent();
                                                            #line 696 "PrintTypescript.cpp"
  append(L"\n");
  append(L"}\n");
                                                            #line 451 "PrintTypescript.cpp.template"
                                                              if (hasCustomCode)
                                                              {
                                                            #line 702 "PrintTypescript.cpp"
  append(L"\n");
  append(L"class DeferredCode\n");
  append(L"{\n");
  append(L"  public link: DeferredCode | null;\n");
  append(L"  public codeId: number;\n");
  append(L"  public b0: number;\n");
  append(L"  public e0: number;\n");
  append(L"\n");
  append(L"  constructor(link: DeferredCode | null, codeId: number, b0: number, e0: number)\n");
  append(L"  {\n");
  append(L"    this.link = link;\n");
  append(L"    this.codeId = codeId;\n");
  append(L"    this.b0 = b0;\n");
  append(L"    this.e0 = e0;\n");
  append(L"  }\n");
  append(L"}\n");
                                                            #line 469 "PrintTypescript.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                            #line 723 "PrintTypescript.cpp"
  append(L"\n");
  append(L"class DeferredEvent\n");
  append(L"{\n");
  append(L"  private link: DeferredEvent | null;\n");
  append(L"  private id: number;\n");
  append(L"  private begin: number;\n");
  append(L"  private end: number;\n");
  append(L"  private count: number;");
                                                            #line 479 "PrintTypescript.cpp.template"
                                                                if (shiftAmbiguity)
                                                                {
                                                            #line 735 "PrintTypescript.cpp"
  append(L"\n");
  append(L"  private depth: number;\n");
  append(L"\n");
  append(L"  getDepth(): number {return this.depth;}\n");
  append(L"  getLink(): DeferredEvent | null {return this.link;}\n");
  append(L"  isTerminal(): boolean {return this.count == -1;}");
                                                            #line 486 "PrintTypescript.cpp.template"
                                                                }
                                                            #line 744 "PrintTypescript.cpp"
  append(L"\n");
  append(L"\n");
  append(L"  constructor(link: DeferredEvent | null, id: number, begin: number, end: number, count: number)\n");
  append(L"  {\n");
  append(L"    this.link = link;\n");
  append(L"    this.id = id;\n");
  append(L"    this.link = link;\n");
  append(L"    this.begin = begin;\n");
  append(L"    this.end = end;\n");
  append(L"    this.count = count;");
                                                            #line 496 "PrintTypescript.cpp.template"
                                                                if (shiftAmbiguity)
                                                                {
                                                            #line 758 "PrintTypescript.cpp"
  append(L"\n");
  append(L"    this.depth = link == null ? 1 : link.depth + 1;");
                                                            #line 499 "PrintTypescript.cpp.template"
                                                                }
                                                            #line 763 "PrintTypescript.cpp"
  append(L"\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  execute(eventHandler: BottomUpEventHandler)\n");
  append(L"  {\n");
  append(L"    ");
                                                            #line 505 "PrintTypescript.cpp.template"
                                                                if (resolvesAmbiguity)
                                                                {
                                                            #line 773 "PrintTypescript.cpp"
  append(L"if (this.count == -2)\n");
  append(L"    {\n");
  append(L"      eventHandler.ambiguity(this.begin, this.end);\n");
  append(L"    }\n");
  append(L"    else ");
                                                            #line 511 "PrintTypescript.cpp.template"
                                                                }
                                                            #line 781 "PrintTypescript.cpp"
  append(L"if (this.count < 0)\n");
  append(L"    {\n");
  append(L"      eventHandler.terminal(this.id, this.begin, this.end);\n");
  append(L"    }\n");
  append(L"    else\n");
  append(L"    {\n");
  append(L"      eventHandler.nonterminal(this.id, this.begin, this.end, this.count);\n");
  append(L"    }\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  release(eventHandler: BottomUpEventHandler)\n");
  append(L"  {\n");
  append(L"    var current: DeferredEvent | null = this;\n");
  append(L"    var predecessor = current.link;\n");
  append(L"    current.link = null;\n");
  append(L"    while (predecessor != null)\n");
  append(L"    {\n");
  append(L"      var next = predecessor.link;\n");
  append(L"      predecessor.link = current;\n");
  append(L"      current = predecessor;\n");
  append(L"      predecessor = next;\n");
  append(L"    }\n");
  append(L"    do\n");
  append(L"    {\n");
  append(L"      ");
                                                            #line 536 "PrintTypescript.cpp.template"
                                                                if (shiftAmbiguity)
                                                                {
                                                            #line 810 "PrintTypescript.cpp"
  append(L"if (eventHandler != null)\n");
  append(L"        ");
                                                            #line 539 "PrintTypescript.cpp.template"
                                                                }
                                                            #line 815 "PrintTypescript.cpp"
  append(L"current.execute(eventHandler);\n");
  append(L"      current = current.link;\n");
  append(L"    }\n");
  append(L"    while (current != null);\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  show(eventHandler: BottomUpEventHandler)\n");
  append(L"  {\n");
  append(L"    var stack = [];\n");
  append(L"    for (var current: DeferredEvent | null = this; current != null; current = current.link)\n");
  append(L"    {\n");
  append(L"      stack.push(current);\n");
  append(L"    }\n");
  append(L"    while (stack.length > 0)\n");
  append(L"    {\n");
  append(L"      stack.pop()!.execute(eventHandler);\n");
  append(L"    }\n");
  append(L"  }\n");
  append(L"}\n");
                                                            #line 559 "PrintTypescript.cpp.template"
                                                              }
                                                            #line 837 "PrintTypescript.cpp"
  append(L"\n");
  append(L"class Heap\n");
  append(L"{\n");
  append(L"  private array: ParsingThread[] = [];\n");
  append(L"  private size = 0;\n");
  append(L"\n");
  append(L"  constructor() {}\n");
  append(L"\n");
  append(L"  offer(value: ParsingThread)\n");
  append(L"  {\n");
  append(L"    var index = this.size++;\n");
  append(L"    while (index != 0)\n");
  append(L"    {\n");
  append(L"      var parentIndex = (index - 1) >> 1;\n");
  append(L"      if (this.array[parentIndex].compareTo(value) <= 0)\n");
  append(L"        break;\n");
  append(L"      this.array[index] = this.array[parentIndex];\n");
  append(L"      index = parentIndex;\n");
  append(L"    }\n");
  append(L"    this.array[index] = value;\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  poll()\n");
  append(L"  {\n");
  append(L"    var min = this.array[0];\n");
  append(L"    if (--this.size > 0)\n");
  append(L"    {\n");
  append(L"      var value = this.array[this.size];\n");
  append(L"      var index = 0;\n");
  append(L"      for (var child;;)\n");
  append(L"      {\n");
  append(L"        child = (index << 1) + 2;\n");
  append(L"        if (child < this.size)\n");
  append(L"        {\n");
  append(L"          var otherChild = child - 1;\n");
  append(L"          if (otherChild < this.size && this.array[child].compareTo(this.array[otherChild]) > 0)\n");
  append(L"            child = otherChild;\n");
  append(L"        }\n");
  append(L"        else if (--child >= this.size)\n");
  append(L"        {\n");
  append(L"          break;\n");
  append(L"        }\n");
  append(L"        if (value.compareTo(this.array[child]) <= 0)\n");
  append(L"        {\n");
  append(L"          break;\n");
  append(L"        }\n");
  append(L"        this.array[index] = this.array[child];\n");
  append(L"        index = child;\n");
  append(L"      }\n");
  append(L"      this.array[index] = value;\n");
  append(L"    }\n");
  append(L"    return min;\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  peek()\n");
  append(L"  {\n");
  append(L"    return this.array[0];\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  isEmpty(): boolean\n");
  append(L"  {\n");
  append(L"    return this.size == 0;\n");
  append(L"  }\n");
  append(L"}\n");
                                                            #line 624 "PrintTypescript.cpp.template"
                                                            }

                                                            void PrintTypescript::openThread()
                                                            {
                                                            #line 907 "PrintTypescript.cpp"
  append(L"\n");
  append(L"class ParsingThread\n");
  append(L"{\n");
  append(L"  public parser!: Parser;\n");
  append(L"  private threads!: Heap;\n");
  append(L"  public accepted!: boolean;\n");
  append(L"  public stack!: StackNode;\n");
  append(L"  public state!: number;\n");
  append(L"  private action!: number;\n");
  append(L"  private target!: number;");
                                                            #line 637 "PrintTypescript.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 921 "PrintTypescript.cpp"
  append(L"\n");
  append(L"  public deferredEvent!: DeferredEvent | null;\n");
  append(L"  private es!: number;");
                                                            #line 641 "PrintTypescript.cpp.template"
                                                              }
                                                            #line 927 "PrintTypescript.cpp"
  append(L"\n");
  append(L"  private bw!: number;\n");
  append(L"  private bs!: number;");
                                                            #line 644 "PrintTypescript.cpp.template"
                                                              if (hasCustomCode)
                                                              {
                                                            #line 934 "PrintTypescript.cpp"
  append(L"\n");
  append(L"  public deferredCode!: DeferredCode | null;");
                                                            #line 647 "PrintTypescript.cpp.template"
                                                              }
                                                            #line 939 "PrintTypescript.cpp"
  append(L"\n");
  append(L"  private id!: number;");
                                                            #line 649 "PrintTypescript.cpp.template"
                                                              if (resolvesAmbiguity)
                                                              {
                                                            #line 945 "PrintTypescript.cpp"
  append(L"\n");
  append(L"  public eventCount!: number;");
                                                            #line 652 "PrintTypescript.cpp.template"
                                                              }
                                                            #line 950 "PrintTypescript.cpp"
  append(L"\n");
  append(L"\n");
  append(L"  open(initialState: number");
                                                            #line 655 "PrintTypescript.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 957 "PrintTypescript.cpp"
  append(L", eventHandler: BottomUpEventHandler | null, target: number");
                                                            #line 658 "PrintTypescript.cpp.template"
                                                              }
                                                            #line 961 "PrintTypescript.cpp"
  append(L"): Heap\n");
  append(L"  {\n");
  append(L"    this.accepted = false;");
                                                            #line 661 "PrintTypescript.cpp.template"
                                                              if (resolvesAmbiguity)
                                                              {
                                                            #line 968 "PrintTypescript.cpp"
  append(L"\n");
  append(L"    this.eventCount = 0;");
                                                            #line 664 "PrintTypescript.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                            #line 975 "PrintTypescript.cpp"
  append(L"\n");
  append(L"    if (eventHandler != null)\n");
  append(L"    {\n");
  append(L"      eventHandler.reset(this.parser.input);\n");
  append(L"    }\n");
  append(L"    this.eventHandler = eventHandler;\n");
  append(L"    this.target = target;\n");
  append(L"    this.deferredEvent = null;");
                                                            #line 674 "PrintTypescript.cpp.template"
                                                              }
                                                              if (hasCustomCode)
                                                              {
                                                            #line 988 "PrintTypescript.cpp"
  append(L"\n");
  append(L"    this.deferredCode = null;");
                                                            #line 678 "PrintTypescript.cpp.template"
                                                              }
                                                            #line 993 "PrintTypescript.cpp"
  append(L"\n");
  append(L"    this.stack = new StackNode(-1, ");
                                                            #line 680 "PrintTypescript.cpp.template"
                                                              if (grammar->states->hasLookback)
                                                              {
                                                            #line 999 "PrintTypescript.cpp"
  append(L"0, ");
                                                            #line 682 "PrintTypescript.cpp.template"
                                                              }
                                                            #line 1003 "PrintTypescript.cpp"
  append(L"this.e0, null);\n");
  append(L"    this.state = initialState;\n");
  append(L"    this.action = this.predict(initialState);");
                                                            #line 685 "PrintTypescript.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 1010 "PrintTypescript.cpp"
  append(L"\n");
  append(L"    this.bw = this.e0;\n");
  append(L"    this.bs = this.e0;\n");
  append(L"    this.es = this.e0;");
                                                            #line 690 "PrintTypescript.cpp.template"
                                                              }
                                                            #line 1017 "PrintTypescript.cpp"
  append(L"\n");
  append(L"    this.threads = new Heap();\n");
  append(L"    this.threads.offer(this);\n");
  append(L"    return this.threads;\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  copy(other: ParsingThread, a: number)\n");
  append(L"  {\n");
  append(L"    this.action = a;\n");
  append(L"    this.accepted = other.accepted;\n");
  append(L"    this.parser = other.parser;\n");
  append(L"    this.threads = other.threads;\n");
  append(L"    this.state = other.state;\n");
  append(L"    this.stack = other.stack;\n");
  append(L"    this.end = other.end;");
                                                            #line 705 "PrintTypescript.cpp.template"
                                                              if (resolvesAmbiguity)
                                                              {
                                                            #line 1036 "PrintTypescript.cpp"
  append(L"\n");
  append(L"    this.eventCount = other.eventCount;");
                                                            #line 708 "PrintTypescript.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                            #line 1043 "PrintTypescript.cpp"
  append(L"\n");
  append(L"    this.bs = other.bs;\n");
  append(L"    this.es = other.es;\n");
  append(L"    this.bw = other.bw;\n");
  append(L"    this.eventHandler = other.eventHandler;\n");
  append(L"    this.target = other.target;\n");
  append(L"    this.deferredEvent = other.deferredEvent;");
                                                            #line 717 "PrintTypescript.cpp.template"
                                                              }
                                                              if (hasCustomCode)
                                                              {
                                                            #line 1055 "PrintTypescript.cpp"
  append(L"\n");
  append(L"    this.deferredCode = other.deferredCode;");
                                                            #line 721 "PrintTypescript.cpp.template"
                                                              }
                                                            #line 1060 "PrintTypescript.cpp"
  append(L"\n");
  append(L"    this.id = ++this.parser.maxId;\n");
  append(L"    this.b0 = other.b0;\n");
  append(L"    this.e0 = other.e0;\n");
  append(L"    this.l1 = other.l1;\n");
  append(L"    this.b1 = other.b1;\n");
  append(L"    this.e1 = other.e1;\n");
  append(L"    return this;\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  compareTo(other: ParsingThread)\n");
  append(L"  {\n");
  append(L"    if (this.accepted != other.accepted)\n");
  append(L"      return this.accepted ? 1 : -1;\n");
  append(L"    var comp = this.e0 - other.e0;\n");
  append(L"    return comp == 0 ? this.id - other.id : comp;\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  equals(other: ParsingThread)\n");
  append(L"  {\n");
  append(L"    if (this.accepted != other.accepted) return false;\n");
  append(L"    if (this.b1 != other.b1) return false;\n");
  append(L"    if (this.e1 != other.e1) return false;\n");
  append(L"    if (this.l1 != other.l1) return false;\n");
  append(L"    if (this.state != other.state) return false;\n");
  append(L"    if (this.action != other.action) return false;\n");
  append(L"    if (! this.stack.equals(other.stack)) return false;\n");
  append(L"    return true;\n");
  append(L"  }\n");
                                                            #line 751 "PrintTypescript.cpp.template"
                                                              if (resolvesAmbiguity && tree)
                                                              {
                                                            #line 1093 "PrintTypescript.cpp"
  append(L"\n");
  append(L"  addAmbiguity(begin: number, end: number)\n");
  append(L"  {\n");
  append(L"    if (this.eventHandler != null)\n");
  append(L"      this.deferredEvent = new DeferredEvent(this.deferredEvent, -1, begin, end, -2);\n");
  append(L"  }\n");
                                                            #line 759 "PrintTypescript.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                            #line 1104 "PrintTypescript.cpp"
  append(L"\n");
  append(L"  release()\n");
  append(L"  {\n");
  append(L"    if (this.deferredEvent != null)\n");
  append(L"    {\n");
  append(L"      this.deferredEvent.release(this.eventHandler!);\n");
  append(L"      this.deferredEvent = null;\n");
  append(L"    }\n");
  append(L"  }\n");
                                                            #line 771 "PrintTypescript.cpp.template"
                                                              }
                                                            #line 1116 "PrintTypescript.cpp"
  append(L"\n");
  append(L"  parse()\n");
  append(L"  {");
                                                            #line 774 "PrintTypescript.cpp.template"
                                                              increaseIndent();
                                                            }

                                                            void PrintTypescript::openMethod(const wchar_t *type,
                                                                                             const wchar_t *prefix,
                                                                                             const wchar_t *name,
                                                                                             const wchar_t *args,
                                                                                             bool constant,
                                                                                             const wchar_t *clazz)
                                                            {
                                                            #line 1131 "PrintTypescript.cpp"
  append(L"\n");
                                                            #line 785 "PrintTypescript.cpp.template"
                                                              if (isPublic)
                                                              {
                                                                print(name);
                                                              }
                                                              else
                                                              {
                                                            #line 1140 "PrintTypescript.cpp"
  append(L"private ");
                                                            #line 791 "PrintTypescript.cpp.template"
                                                                print(name);
                                                              }
                                                            #line 1145 "PrintTypescript.cpp"
  append(L"(");
                                                            #line 793 "PrintTypescript.cpp.template"
                                                              bool ignore = true;
                                                              const wchar_t *typeBegin = args;
                                                              const wchar_t *typeEnd = 0;
                                                              for (const wchar_t *a = args; *a; ++a)
                                                              {
                                                                if (! ignore)
                                                                {
                                                                  print(*a);
                                                                }
                                                                if (*a == ' ')
                                                                {
                                                                  ignore = ! ignore;
                                                                  if (ignore)
                                                                    typeBegin = a + 1;
                                                                  else
                                                                    typeEnd = a;
                                                                }
                                                                if (*(a + 1) == ',' || *(a + 1) == 0)
                                                                {
                                                                  print(L": ");
                                                                  if (typeEnd == typeBegin)
                                                                    print(L"string");
                                                                  else if (wcsncmp(typeBegin, L"int", typeEnd - typeBegin) == 0)
                                                                    print(L"number");
                                                                  else
                                                                    for (const wchar_t *t = typeBegin; t < typeEnd; ++t)
                                                                      if (*t == L'|') print(L" | "); else print(*t);
                                                                }
                                                              }
                                                            #line 1177 "PrintTypescript.cpp"
  append(L")");
                                                            #line 822 "PrintTypescript.cpp.template"
                                                              if (*type)
                                                              {
                                                                if (wcscmp(type, L"int ") == 0)
                                                                  print(L": number");
                                                              }
                                                            }

                                                            void PrintTypescript::privateVars()
                                                            {
                                                              if (trace)
                                                              {
                                                            #line 1191 "PrintTypescript.cpp"
  append(L"\n");
  append(L"  private lookaheadString(): string\n");
  append(L"  {\n");
  append(L"    var result = \"\";\n");
  append(L"    if (");
                                                            #line 837 "PrintTypescript.cpp.template"
                                                                print(thiz());
                                                            #line 1199 "PrintTypescript.cpp"
  append(L"l1 > 0)\n");
  append(L"    {\n");
  append(L"      result += ");
                                                            #line 840 "PrintTypescript.cpp.template"
                                                                print(staticPrefix());
                                                            #line 1205 "PrintTypescript.cpp"
  append(L"TOKEN[");
                                                            #line 841 "PrintTypescript.cpp.template"
                                                                print(thiz());
                                                            #line 1209 "PrintTypescript.cpp"
  append(L"l1];");
                                                            #line 842 "PrintTypescript.cpp.template"
                                                                for (size_t i = 2; i <= grammar->k; ++i)
                                                                {
                                                            #line 1214 "PrintTypescript.cpp"
  append(L"\n");
  append(L"      if (");
                                                            #line 845 "PrintTypescript.cpp.template"
                                                                  print(thiz());
                                                            #line 1219 "PrintTypescript.cpp"
  append(L"l");
                                                            #line 846 "PrintTypescript.cpp.template"
                                                                  print(format.toString<wchar_t>(i));
                                                            #line 1223 "PrintTypescript.cpp"
  append(L" > 0)\n");
  append(L"      {\n");
  append(L"        result += \" \" + ");
                                                            #line 849 "PrintTypescript.cpp.template"
                                                                  print(staticPrefix());
                                                            #line 1229 "PrintTypescript.cpp"
  append(L"TOKEN[");
                                                            #line 850 "PrintTypescript.cpp.template"
                                                                  print(thiz());
                                                            #line 1233 "PrintTypescript.cpp"
  append(L"l");
                                                            #line 851 "PrintTypescript.cpp.template"
                                                                  print(format.toString<wchar_t>(i));
                                                            #line 1237 "PrintTypescript.cpp"
  append(L"];");
                                                            #line 852 "PrintTypescript.cpp.template"
                                                                  increaseIndent();
                                                                }
                                                                for (size_t i = 2; i <= grammar->k; ++i)
                                                                {
                                                                  decreaseIndent();
                                                            #line 1245 "PrintTypescript.cpp"
  append(L"\n");
  append(L"      }");
                                                            #line 858 "PrintTypescript.cpp.template"
                                                                }
                                                            #line 1250 "PrintTypescript.cpp"
  append(L"\n");
  append(L"    }\n");
  append(L"    return result;\n");
  append(L"  }\n");
                                                            #line 863 "PrintTypescript.cpp.template"
                                                              }
                                                              if (needTokenFunction)
                                                              {
                                                            #line 1259 "PrintTypescript.cpp"
  append(L"\n");
  append(L"  private token(): number\n");
  append(L"  {\n");
  append(L"    return this.l1;\n");
  append(L"  }\n");
                                                            #line 871 "PrintTypescript.cpp.template"
                                                              }
                                                              if (needTokenSequenceFunction)
                                                              {
                                                            #line 1269 "PrintTypescript.cpp"
  append(L"\n");
  append(L"  private tokenSequence(): number\n");
  append(L"  {\n");
  append(L"    return this.lk;\n");
  append(L"  }\n");
                                                            #line 879 "PrintTypescript.cpp.template"
                                                              }
                                                              const wchar_t *visibility = useGlr ? L"public" : L"private";
                                                            #line 1278 "PrintTypescript.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 882 "PrintTypescript.cpp.template"
                                                              if (! isLrParser && (grammar->k > 1 || memoization || ! grammar->decisionPoints.empty()))
                                                              {
                                                            #line 1284 "PrintTypescript.cpp"
  append(L"private lk!: number; ");
                                                            #line 884 "PrintTypescript.cpp.template"
                                                              }
                                                              else
                                                              {
                                                                print(wcslen(visibility), L" ");
                                                            #line 1291 "PrintTypescript.cpp"
  append(L"              ");
                                                            #line 888 "PrintTypescript.cpp.template"
                                                              }
                                                              print(visibility);
                                                            #line 1296 "PrintTypescript.cpp"
  append(L" b0!: number; ");
                                                            #line 890 "PrintTypescript.cpp.template"
                                                              print(visibility);
                                                            #line 1300 "PrintTypescript.cpp"
  append(L" e0!: number;");
                                                            #line 891 "PrintTypescript.cpp.template"
                                                              for (size_t k = 1; k <= grammar->k; ++k)
                                                              {
                                                                Format format;
                                                                wchar_t *asString = format.toString<wchar_t>(k);
                                                            #line 1307 "PrintTypescript.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 896 "PrintTypescript.cpp.template"
                                                                print(visibility);
                                                            #line 1312 "PrintTypescript.cpp"
  append(L" l");
                                                            #line 897 "PrintTypescript.cpp.template"
                                                                print(asString);
                                                            #line 1316 "PrintTypescript.cpp"
  append(L"!: number; ");
                                                            #line 898 "PrintTypescript.cpp.template"
                                                                print(visibility);
                                                            #line 1320 "PrintTypescript.cpp"
  append(L" b");
                                                            #line 899 "PrintTypescript.cpp.template"
                                                                print(asString);
                                                            #line 1324 "PrintTypescript.cpp"
  append(L"!: number; ");
                                                            #line 900 "PrintTypescript.cpp.template"
                                                                print(visibility);
                                                            #line 1328 "PrintTypescript.cpp"
  append(L" e");
                                                            #line 901 "PrintTypescript.cpp.template"
                                                                print(asString);
                                                            #line 1332 "PrintTypescript.cpp"
  append(L"!: number;");
                                                            #line 902 "PrintTypescript.cpp.template"
                                                              }
                                                              if (hasBacktracking)
                                                              {
                                                            #line 1338 "PrintTypescript.cpp"
  append(L"\n");
  append(L"  private bx!: number; private ex!: number; private sx!: number; private lx!: number; private tx!: number;");
                                                            #line 907 "PrintTypescript.cpp.template"
                                                              }
                                                              if (isLrParser && ! useGlr)
                                                              {
                                                            #line 1345 "PrintTypescript.cpp"
  append(L"\n");
  append(L"  private iStack: number[] = [];\n");
  append(L"  private top: number = -1;");
                                                            #line 912 "PrintTypescript.cpp.template"
                                                              }

                                                              if (tree)
                                                              {
                                                            #line 1354 "PrintTypescript.cpp"
  append(L"\n");
  append(L"  private eventHandler!: ");
                                                            #line 917 "PrintTypescript.cpp.template"
                                                                if (isLrParser)
                                                                {
                                                            #line 1360 "PrintTypescript.cpp"
  append(L"BottomUpEventHandler | null;");
                                                            #line 919 "PrintTypescript.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1366 "PrintTypescript.cpp"
  append(L"ParsingEventHandler;");
                                                            #line 922 "PrintTypescript.cpp.template"
                                                                }
                                                              }
                                                              if (memoization)
                                                              {
                                                                int bits = Math::bits(grammar->conflictCount);
                                                            #line 1374 "PrintTypescript.cpp"
  append(L"\n");
  append(L"  private memo!: Memoizer;");
                                                            #line 928 "PrintTypescript.cpp.template"
                                                                if (grammar->noThrow)
                                                                {
                                                            #line 1380 "PrintTypescript.cpp"
  append(L"\n");
  append(L"  private viable!: boolean;");
                                                            #line 931 "PrintTypescript.cpp.template"
                                                                }
                                                            #line 1385 "PrintTypescript.cpp"
  append(L"\n");
  append(L"\n");
  append(L"  private memoize(i: number, e: number, v: number)\n");
  append(L"  {\n");
  append(L"    ");
                                                            #line 936 "PrintTypescript.cpp.template"
                                                                print(thiz());
                                                            #line 1393 "PrintTypescript.cpp"
  append(L"memo[(e << ");
                                                            #line 937 "PrintTypescript.cpp.template"
                                                                print(format.toString<wchar_t>(bits));
                                                            #line 1397 "PrintTypescript.cpp"
  append(L") + i] = v;\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  private memoized(i: number, e: number): number\n");
  append(L"  {\n");
  append(L"    var v = ");
                                                            #line 943 "PrintTypescript.cpp.template"
                                                                print(thiz());
                                                            #line 1406 "PrintTypescript.cpp"
  append(L"memo[(e << ");
                                                            #line 944 "PrintTypescript.cpp.template"
                                                                print(format.toString<wchar_t>(bits));
                                                            #line 1410 "PrintTypescript.cpp"
  append(L") + i];\n");
  append(L"    return typeof v != \"undefined\" ? v : 0;\n");
  append(L"  }");
                                                            #line 947 "PrintTypescript.cpp.template"
                                                              }
                                                            #line 1416 "PrintTypescript.cpp"
  append(L"\n");
                                                            #line 949 "PrintTypescript.cpp.template"
                                                            }

                                                            void PrintTypescript::printPlatformSpecific()
                                                            {
                                                            #line 1423 "PrintTypescript.cpp"
  append(L"\n");
  append(L"  var command = \"node\";\n");
  append(L"  var log = function(string) {proc.stdout.write(string);};\n");
  append(L"  var fs = requ('fs');\n");
  append(L"  var readTextFile = fs.readFileSync;");
                                                            #line 957 "PrintTypescript.cpp.template"
                                                              if (performanceTest)
                                                              {
                                                            #line 1432 "PrintTypescript.cpp"
  append(L"\n");
  append(L"  var readDir = fs.readdirSync;\n");
  append(L"  var isDirectory = function(filename) {return fs.statSync(filename).isDirectory();};");
                                                            #line 962 "PrintTypescript.cpp.template"
                                                              }
                                                            #line 1438 "PrintTypescript.cpp"
  append(L"\n");
                                                            #line 964 "PrintTypescript.cpp.template"
                                                            }

                                                            void PrintTypescript::printFileProcessor()
                                                            {
                                                              if (tree)
                                                              {
                                                            #line 1447 "PrintTypescript.cpp"
  append(L"\n");
  append(L"class ContentCounter implements ");
                                                            #line 972 "PrintTypescript.cpp.template"
                                                                print(className.c_str());
                                                            #line 1452 "PrintTypescript.cpp"
  append(L".ParsingEventHandler\n");
  append(L"{\n");
  append(L"  private length = 0;\n");
  append(L"\n");
  append(L"  getLength() {return this.length;}\n");
  append(L"  reset(s: string) {this.length = 0}\n");
  append(L"  startNonterminal(id: number, begin: number) {}\n");
  append(L"  endNonterminal(id: number, end: number) {}\n");
  append(L"  terminal(id: number, begin: number, end: number) {this.length += end - begin;}\n");
  append(L"  whitespace(begin: number, end: number) {this.length += end - begin;}\n");
  append(L"}\n");
                                                            #line 984 "PrintTypescript.cpp.template"
                                                              }
                                                            #line 1466 "PrintTypescript.cpp"
  append(L"\n");
  append(L"class ParseJob\n");
  append(L"{\n");
  append(L"  name: string;\n");
  append(L"  input: string;");
                                                            #line 989 "PrintTypescript.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 1475 "PrintTypescript.cpp"
  append(L"\n");
  append(L"  contentCounter: ContentCounter;");
                                                            #line 992 "PrintTypescript.cpp.template"
                                                                if (isLrParser)
                                                                {
                                                            #line 1481 "PrintTypescript.cpp"
  append(L"\n");
  append(L"  parseTreeBuilder: ");
                                                            #line 995 "PrintTypescript.cpp.template"
                                                                  print(className.c_str());
                                                            #line 1486 "PrintTypescript.cpp"
  append(L".ParseTreeBuilder;");
                                                            #line 996 "PrintTypescript.cpp.template"
                                                                }
                                                              }
                                                            #line 1491 "PrintTypescript.cpp"
  append(L"\n");
  append(L"  parser: ");
                                                            #line 999 "PrintTypescript.cpp.template"
                                                              print(className.c_str());
                                                            #line 1496 "PrintTypescript.cpp"
  append(L".Parser | null;\n");
  append(L"\n");
  append(L"  constructor(s: string, i: string)\n");
  append(L"  {\n");
  append(L"    this.name = s;\n");
  append(L"    this.input = i;");
                                                            #line 1005 "PrintTypescript.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 1506 "PrintTypescript.cpp"
  append(L"\n");
  append(L"    this.contentCounter = new ContentCounter();");
                                                            #line 1008 "PrintTypescript.cpp.template"
                                                                if (isLrParser)
                                                                {
                                                            #line 1512 "PrintTypescript.cpp"
  append(L"\n");
  append(L"    this.parseTreeBuilder = new ");
                                                            #line 1011 "PrintTypescript.cpp.template"
                                                                  print(className.c_str());
                                                            #line 1517 "PrintTypescript.cpp"
  append(L".ParseTreeBuilder();");
                                                            #line 1012 "PrintTypescript.cpp.template"
                                                                }
                                                              }
                                                            #line 1522 "PrintTypescript.cpp"
  append(L"\n");
  append(L"    this.parser = new ");
                                                            #line 1015 "PrintTypescript.cpp.template"
                                                              print(className.c_str());
                                                            #line 1527 "PrintTypescript.cpp"
  append(L".Parser(i");
                                                            #line 1016 "PrintTypescript.cpp.template"
                                                              if (noLexer)
                                                              {
                                                            #line 1532 "PrintTypescript.cpp"
  append(L", null");
                                                            #line 1018 "PrintTypescript.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                                if (isLrParser)
                                                                {
                                                            #line 1540 "PrintTypescript.cpp"
  append(L", this.parseTreeBuilder");
                                                            #line 1023 "PrintTypescript.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1546 "PrintTypescript.cpp"
  append(L", this.contentCounter");
                                                            #line 1026 "PrintTypescript.cpp.template"
                                                                }
                                                              }
                                                            #line 1551 "PrintTypescript.cpp"
  append(L");\n");
  append(L"  }\n");
  append(L"}\n");
  append(L"\n");
  append(L"function findFiles(f: string, filter: string, parsers: ParseJob[], quiet: boolean)\n");
  append(L"{\n");
  append(L"  if (fs.statSync(f).isDirectory())\n");
  append(L"  {\n");
  append(L"    var files = fs.readdirSync(f);\n");
  append(L"    for (var i = 0; i < files.length; ++i)\n");
  append(L"    {\n");
  append(L"      findFiles(f + \"/\" + files[i], filter, parsers, quiet);\n");
  append(L"    }\n");
  append(L"  }\n");
  append(L"  else if (f.substring(f.length - filter.length).toLowerCase() == filter.toLowerCase())\n");
  append(L"  {\n");
  append(L"    var content = fs.readFileSync(f, \"utf-8\");\n");
  append(L"    var input = content.length > 0 && content.charCodeAt(0) == 0xFEFF\n");
  append(L"              ? content.substring(1)\n");
  append(L"              : content;\n");
  append(L"    if (! quiet) proc.stdout.write(\"loading \" + f + \"\\n\");\n");
  append(L"    parsers[parsers.length] = new ParseJob(f, input);\n");
  append(L"  }\n");
  append(L"}\n");
  append(L"\n");
  append(L"// performance test main program for use with node.js\n");
  append(L"\n");
  append(L"const proc: any = (globalThis as any).process;\n");
  append(L"const requ: any = eval(\"require\");\n");
  append(L"const fs: any = requ(\"fs\");\n");
  append(L"\n");
  append(L"var quiet = false;\n");
  append(L"var parsed = 0;\n");
  append(L"var errorCount = 0;\n");
  append(L"var parsers: ParseJob[] = [];\n");
  append(L"\n");
  append(L"if (proc.argv.length < 3)\n");
  append(L"{\n");
  append(L"  proc.stderr.write(\"Usage: node ");
                                                            #line 1066 "PrintTypescript.cpp.template"
                                                              print(className.c_str());
                                                            #line 1593 "PrintTypescript.cpp"
  append(L".js [-q] [-r N] [-t N] ENDING...\\n\");\n");
  append(L"  proc.stderr.write(\"\\n\");\n");
  append(L"  proc.stderr.write(\"  parse all files that have names ending with ENDING, in current dir and below,\\n\");\n");
  append(L"  proc.stderr.write(\"  and display performance summary.\\n\");\n");
  append(L"  proc.stderr.write(\"\\n\");\n");
  append(L"  proc.stderr.write(\"  -q     do not show file names\\n\");\n");
  append(L"  proc.stderr.write(\"  -r N   repeat N times\\n\");\n");
  append(L"  proc.stderr.write(\"  -t N   repeat until N seconds have elapsed\\n\");\n");
  append(L"}\n");
  append(L"else\n");
  append(L"{\n");
  append(L"  var repeat = 1;\n");
  append(L"  var timeout = 0;\n");
  append(L"  var i = 1;\n");
  append(L"  while (++i < proc.argv.length)\n");
  append(L"  {\n");
  append(L"    if (proc.argv[i] == \"-q\")\n");
  append(L"    {\n");
  append(L"      quiet = true;\n");
  append(L"    }\n");
  append(L"    else if (proc.argv[i] == \"-r\")\n");
  append(L"    {\n");
  append(L"      repeat = parseInt(proc.argv[++i]);\n");
  append(L"      timeout = 0;\n");
  append(L"    }\n");
  append(L"    else if (proc.argv[i] == \"-t\")\n");
  append(L"    {\n");
  append(L"      repeat = 0;\n");
  append(L"      timeout = 1000 * parseInt(proc.argv[++i]);\n");
  append(L"    }\n");
  append(L"    else if (proc.argv[i].substring(0, 1) !== \"-\")\n");
  append(L"    {\n");
  append(L"      break;\n");
  append(L"    }\n");
  append(L"    else\n");
  append(L"    {\n");
  append(L"      throw \"invalid option: \" + proc.argv[i];\n");
  append(L"    }\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  var start = Date.now();\n");
  append(L"\n");
  append(L"  for (; i < proc.argv.length; ++i)\n");
  append(L"  {\n");
  append(L"    findFiles(\".\", proc.argv[i], parsers, quiet);\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  if (parsers.length != 0)\n");
  append(L"  {\n");
  append(L"    var msec = Date.now() - start;\n");
  append(L"\n");
  append(L"    if (! quiet) proc.stdout.write(\"\\n\");\n");
  append(L"    proc.stdout.write(\"loaded \" + parsers.length + \" file\" +\n");
  append(L"        (parsers.length == 1 ? \"\" : \"s\") + \" in \" +\n");
  append(L"        msec + \" msec\\n\");\n");
  append(L"    if (! quiet) proc.stdout.write(\"\\n\");\n");
  append(L"\n");
  append(L"    start = Date.now();\n");
  append(L"    for (i = 0; ; ++i)\n");
  append(L"    {\n");
  append(L"      if (repeat != 0 && i >= repeat) break;\n");
  append(L"      if (timeout != 0 && Date.now() - start >= timeout) break;\n");
  append(L"\n");
  append(L"      for (var j = 0; j < parsers.length; ++j)\n");
  append(L"      {\n");
  append(L"        var job: ParseJob = parsers[j];\n");
  append(L"        if (job.parser != null)\n");
  append(L"        {\n");
  append(L"          try\n");
  append(L"          {\n");
  append(L"            if (! quiet) proc.stdout.write(\"parsing \" + job.name);\n");
  append(L"            job.parser.reset(0, 0, 0);\n");
  append(L"            job.parser.");
                                                            #line 1139 "PrintTypescript.cpp.template"
                                                              print(methodPrefixParse);
                                                              print(Format::acceptableName<WString>(grammar->startSymbol()->name).c_str());
                                                            #line 1670 "PrintTypescript.cpp"
  append(L"();\n");
  append(L"            if (! quiet) proc.stdout.write(\"\\n\");");
                                                            #line 1142 "PrintTypescript.cpp.template"
                                                              if (tree)
                                                              {
                                                                if (isLrParser)
                                                                {
                                                            #line 1678 "PrintTypescript.cpp"
  append(L"\n");
  append(L"            job.parseTreeBuilder.serialize(job.contentCounter);");
                                                            #line 1148 "PrintTypescript.cpp.template"
                                                                }
                                                            #line 1683 "PrintTypescript.cpp"
  append(L"\n");
  append(L"            if (job.contentCounter.getLength() != job.input.length)\n");
  append(L"            {\n");
  append(L"              throw \"content counter saw \" + job.contentCounter.getLength() +\n");
  append(L"                    \", but input length is \" + job.input.length;\n");
  append(L"            }");
                                                            #line 1154 "PrintTypescript.cpp.template"
                                                              }
                                                            #line 1692 "PrintTypescript.cpp"
  append(L"\n");
  append(L"            parsed += job.input.length;\n");
  append(L"          }\n");
  append(L"          catch (pe)\n");
  append(L"          {\n");
  append(L"            if (pe instanceof ");
                                                            #line 1160 "PrintTypescript.cpp.template"
                                                              print(className.c_str());
                                                            #line 1701 "PrintTypescript.cpp"
  append(L".ParseException)\n");
  append(L"            {\n");
  append(L"              ++errorCount;\n");
  append(L"              proc.stdout.write((quiet ? (\"parsing \" + job.name) : \"\") +\n");
  append(L"                  \": error: \" + job.parser.getErrorMessage(pe) + \"\\n\");\n");
  append(L"              job.parser = null;\n");
  append(L"            }\n");
  append(L"            else\n");
  append(L"            {\n");
  append(L"              throw pe;\n");
  append(L"            }\n");
  append(L"          }\n");
  append(L"        }\n");
  append(L"      }\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    msec = Date.now() - start;\n");
  append(L"    var sec = msec / 1000e0;\n");
  append(L"    var perSec = msec == 0\n");
  append(L"                 ? \"\"\n");
  append(L"                 : parsed / sec > 1024 * 1024\n");
  append(L"                 ? (\" (\"  + (parsed / 1024 / 1024 /sec).toFixed(2) + \" MB/sec)\")\n");
  append(L"                 : (\" (\"  + (parsed / 1024        /sec).toFixed(2) + \" KB/sec)\");\n");
  append(L"\n");
  append(L"    if (! quiet) proc.stdout.write(\"\\n\");\n");
  append(L"    proc.stdout.write(\"parsed \" + parsed + \" byte\" + (parsed == 1 ? \"\" : \"s\") +\n");
  append(L"        \" in \" + msec + \" msec\" + perSec + \"\\n\");\n");
  append(L"    proc.stdout.write(errorCount + \" error\" + (errorCount == 1 ? \"\" : \"s\") + \"\\n\");\n");
  append(L"  }\n");
  append(L"}\n");
                                                            #line 1191 "PrintTypescript.cpp.template"
                                                            }

                                                            void PrintTypescript::printReadMethod()
                                                            {
                                                            #line 1737 "PrintTypescript.cpp"
  append(L"\n");
  append(L"  function read(input)\n");
  append(L"  {\n");
  append(L"    if (/");
  append(L"^");
  append(L"{.*}$/.test(input))\n");
  append(L"    {\n");
  append(L"      return input.substring(1, input.length - 1);\n");
  append(L"    }\n");
  append(L"    else\n");
  append(L"    {\n");
  append(L"      var content = readTextFile(input, \"utf-8\");\n");
  append(L"      return content.length > 0 && content.charCodeAt(0) == 0xFEFF\n");
  append(L"           ? content.substring(1)\n");
  append(L"           : content;\n");
  append(L"    }\n");
  append(L"  }\n");
                                                            #line 1210 "PrintTypescript.cpp.template"
                                                            }

                                                            void PrintTypescript::close(Grammar *node)
                                                            {
                                                              print(L"\n");
                                                              if (! useGlr)
                                                              {
                                                                print(lexerInstanceCode);
                                                              }
                                                              else
                                                              {
                                                                decreaseIndent(2);
                                                              }
                                                              print(lexerStaticCode);

                                                              decreaseIndent();
                                                            #line 1772 "PrintTypescript.cpp"
  append(L"}\n");
                                                            #line 1227 "PrintTypescript.cpp.template"
                                                              if (useGlr)
                                                              {
                                                                increaseIndent();
                                                                openStackNode();
                                                                printCountMethod();
                                                                closeStackNode();
                                                                openThread();
                                                                increaseIndent();
                                                                printThreadBody1();
                                                                print(lexerInstanceCode);
                                                                decreaseIndent();
                                                            #line 1786 "PrintTypescript.cpp"
  append(L"}\n");
                                                            #line 1239 "PrintTypescript.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                            #line 1792 "PrintTypescript.cpp"
  append(L"\n");
  append(L"  export class TopDownTreeBuilder implements ParsingEventHandler\n");
  append(L"  {\n");
  append(L"    private input!: string;\n");
  append(L"    private stack!: Nonterminal[];\n");
  append(L"\n");
  append(L"    public reset(input: string): void\n");
  append(L"    {\n");
  append(L"      this.input = input;\n");
  append(L"      this.stack = [];\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    public startNonterminal(id: number, begin: number): void\n");
  append(L"    {\n");
  append(L"      var nonterminal = new Nonterminal(id, begin, begin, []);\n");
  append(L"      if (this.stack.length > 0) this.addChild(nonterminal);\n");
  append(L"      this.stack.push(nonterminal);\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    public endNonterminal(id: number, end: number): void\n");
  append(L"    {\n");
  append(L"      this.stack[this.stack.length - 1].end = end;\n");
  append(L"      if (this.stack.length > 1) this.stack.pop();\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    public terminal(id: number, begin: number, end: number): void\n");
  append(L"    {\n");
  append(L"      this.addChild(new Terminal(id, begin, end));\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    public whitespace(begin: number, end: number): void\n");
  append(L"    {\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    private addChild(s: Symbol): void\n");
  append(L"    {\n");
  append(L"      var current = this.stack[this.stack.length - 1];\n");
  append(L"      current.children.push(s);\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    public serialize(e: ParsingEventHandler): void\n");
  append(L"    {\n");
  append(L"      e.reset(this.input);\n");
  append(L"      this.stack[0].send(e);\n");
  append(L"    }\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  export abstract class Symbol\n");
  append(L"  {\n");
  append(L"    public id: number;\n");
  append(L"    public begin: number;\n");
  append(L"    public end: number;\n");
  append(L"\n");
  append(L"    constructor(id: number, begin: number, end: number)\n");
  append(L"    {\n");
  append(L"      this.id = id;\n");
  append(L"      this.begin = begin;\n");
  append(L"      this.end = end;\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    public abstract getName(): string;\n");
  append(L"\n");
  append(L"    public abstract send(e: ParsingEventHandler): void;\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  export class Terminal extends Symbol\n");
  append(L"  {\n");
  append(L"    constructor(id: number, begin: number, end: number)\n");
  append(L"    {\n");
  append(L"      super(id, begin, end);\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    public getName(): string\n");
  append(L"    {\n");
  append(L"      return Parser.TOKEN[this.id];\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    public send(e: ParsingEventHandler): void\n");
  append(L"    {\n");
  append(L"      e.terminal(this.id, this.begin, this.end);\n");
  append(L"    }\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  export class Nonterminal extends Symbol\n");
  append(L"  {\n");
  append(L"    public children: Symbol[];\n");
  append(L"\n");
  append(L"    constructor(id: number, begin: number, end: number, children: Symbol[])\n");
  append(L"    {\n");
  append(L"      super(id, begin, end);\n");
  append(L"      this.children = children;\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    public getName(): string\n");
  append(L"    {\n");
  append(L"      return ");
                                                            #line 1337 "PrintTypescript.cpp.template"
                                                                printSyntheticNamePrefix(false, L"this.id");
                                                            #line 1891 "PrintTypescript.cpp"
  append(L"Parser.NONTERMINAL[this.id]");
                                                            #line 1339 "PrintTypescript.cpp.template"
                                                                printSyntheticNameSuffix(false, L"this.id");
                                                            #line 1895 "PrintTypescript.cpp"
  append(L";\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    public send(e: ParsingEventHandler): void\n");
  append(L"    {\n");
  append(L"      e.startNonterminal(this.id, this.begin);\n");
  append(L"      var pos = this.begin;\n");
  append(L"      this.children.forEach\n");
  append(L"      (\n");
  append(L"        function(c): void\n");
  append(L"        {\n");
  append(L"          if (pos < c.begin) e.whitespace(pos, c.begin);\n");
  append(L"          c.send(e);\n");
  append(L"          pos = c.end;\n");
  append(L"        }\n");
  append(L"      );\n");
  append(L"      if (pos < this.end) e.whitespace(pos, this.end);\n");
  append(L"      e.endNonterminal(this.id, this.end);\n");
  append(L"    }\n");
  append(L"  }\n");
                                                            #line 1360 "PrintTypescript.cpp.template"
                                                                if (isLrParser)
                                                                {
                                                            #line 1919 "PrintTypescript.cpp"
  append(L"\n");
  append(L"  export class ParseTreeBuilder implements BottomUpEventHandler\n");
  append(L"  {\n");
  append(L"    private input!: string;\n");
  append(L"    private stack: Symbol[] = [];\n");
  append(L"    private top!: number;\n");
  append(L"\n");
  append(L"    public reset(input: string): void\n");
  append(L"    {\n");
  append(L"      this.input = input;\n");
  append(L"      this.top = -1;\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    public getStack(): Symbol[] {return this.stack;}\n");
  append(L"    public getTop(): number {return this.top;}\n");
  append(L"\n");
  append(L"    public nonterminal(id: number, begin: number, end: number, count: number): void\n");
  append(L"    {");
                                                            #line 1379 "PrintTypescript.cpp.template"
                                                                  if (rejectsAmbiguity())
                                                                  {
                                                            #line 1941 "PrintTypescript.cpp"
  append(L"\n");
  append(L"      if (count > this.top + 1)\n");
  append(L"      {\n");
  append(L"        var content = this.pop(this.top + 1);\n");
  append(L"        this.nonterminal(");
                                                            #line 1385 "PrintTypescript.cpp.template"
                                                                    print(format.toString<wchar_t>(Grammar::syntheticNonterminalCode(2)));
                                                            #line 1949 "PrintTypescript.cpp"
  append(L", begin, content.length == 0 ? end : content[0].begin, 0);\n");
  append(L"        for (let symbol of content)\n");
  append(L"        {\n");
  append(L"          this.push(symbol);\n");
  append(L"        }\n");
  append(L"        count = this.top + 1;\n");
  append(L"      }");
                                                            #line 1392 "PrintTypescript.cpp.template"
                                                                  }
                                                            #line 1959 "PrintTypescript.cpp"
  append(L"\n");
  append(L"      this.push(new Nonterminal(id, begin, end, this.pop(count)));\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    public terminal(id: number, begin: number, end: number): void\n");
  append(L"    {\n");
  append(L"      this.push(new Terminal(id, begin, end));\n");
  append(L"    }");
                                                            #line 1400 "PrintTypescript.cpp.template"
                                                                  if (resolvesAmbiguity)
                                                                  {
                                                            #line 1971 "PrintTypescript.cpp"
  append(L"\n");
  append(L"\n");
  append(L"    public ambiguity(begin: number, end: number): void\n");
  append(L"    {\n");
  append(L"    }");
                                                            #line 1406 "PrintTypescript.cpp.template"
                                                                  }
                                                            #line 1979 "PrintTypescript.cpp"
  append(L"\n");
  append(L"\n");
  append(L"    public serialize(e: ParsingEventHandler): void\n");
  append(L"    {\n");
  append(L"      e.reset(this.input);\n");
  append(L"      for (var i = 0; i <= this.top; ++i)\n");
  append(L"      {\n");
  append(L"        this.stack[i].send(e);\n");
  append(L"      }\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    public push(s: Symbol): void\n");
  append(L"    {\n");
  append(L"      this.stack[++this.top] = s;\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    public pop(count: number): Symbol[]\n");
  append(L"    {\n");
  append(L"      this.top -= count;\n");
  append(L"      return this.stack.slice(this.top + 1, this.top + 1 + count);\n");
  append(L"    }\n");
  append(L"  }\n");
                                                            #line 1429 "PrintTypescript.cpp.template"
                                                                }
                                                              }
                                                              if (! visitEpilog())
                                                              {
                                                            #line 2007 "PrintTypescript.cpp"
  append(L"}\n");
                                                            #line 1434 "PrintTypescript.cpp.template"
                                                              }

                                                              if (main)
                                                              {
                                                                if (tree)
                                                                {
                                                            #line 2016 "PrintTypescript.cpp"
  append(L"\n");
  append(L"class XmlSerializer implements ");
                                                            #line 1441 "PrintTypescript.cpp.template"
                                                                  print(className.c_str());
                                                            #line 2021 "PrintTypescript.cpp"
  append(L".ParsingEventHandler\n");
  append(L"{\n");
  append(L"  private input!: string;\n");
  append(L"  private delayedTag: string | null = null;\n");
  append(L"  private indent: boolean;\n");
  append(L"  private hasChildElement!: boolean;\n");
  append(L"  private depth!: number;\n");
  append(L"\n");
  append(L"  constructor(indent: boolean)\n");
  append(L"  {\n");
  append(L"    this.indent = indent;\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  reset(source: string)\n");
  append(L"  {\n");
  append(L"    proc.stdout.write(\"<?xml version=\\\"1.0\\\" encoding=\\\"UTF-8\\\"?\" + \">\");\n");
  append(L"    this.input = source;\n");
  append(L"    this.hasChildElement = false;\n");
  append(L"    this.depth = 0;\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  startNonterminal(id: number, begin: number)\n");
  append(L"  {\n");
  append(L"    this.startElement(");
                                                            #line 1465 "PrintTypescript.cpp.template"
                                                                  print(className.c_str());
                                                            #line 2048 "PrintTypescript.cpp"
  append(L".Parser.getNonterminalName(id));\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  private startElement(tag: string)\n");
  append(L"  {\n");
  append(L"    if (this.delayedTag != null)\n");
  append(L"    {\n");
  append(L"      proc.stdout.write(\"<\");\n");
  append(L"      proc.stdout.write(this.delayedTag);\n");
  append(L"      proc.stdout.write(\">\");\n");
  append(L"    }\n");
  append(L"    this.delayedTag = tag;\n");
  append(L"    if (this.indent)\n");
  append(L"    {\n");
  append(L"      proc.stdout.write(\"\\n\");\n");
  append(L"      for (var i = 0; i < this.depth; ++i)\n");
  append(L"      {\n");
  append(L"        proc.stdout.write(\"  \");\n");
  append(L"      }\n");
  append(L"    }\n");
  append(L"    this.hasChildElement = false;\n");
  append(L"    ++this.depth;\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  endNonterminal(id: number, end: number)\n");
  append(L"  {\n");
  append(L"    this.endElement(");
                                                            #line 1492 "PrintTypescript.cpp.template"
                                                                  print(className.c_str());
                                                            #line 2078 "PrintTypescript.cpp"
  append(L".Parser.getNonterminalName(id));\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  private endElement(tag: string)\n");
  append(L"  {\n");
  append(L"    --this.depth;\n");
  append(L"    if (this.delayedTag != null)\n");
  append(L"    {\n");
  append(L"      this.delayedTag = null;\n");
  append(L"      proc.stdout.write(\"<\");\n");
  append(L"      proc.stdout.write(tag);\n");
  append(L"      proc.stdout.write(\"/>\");\n");
  append(L"    }\n");
  append(L"    else\n");
  append(L"    {\n");
  append(L"      if (this.indent)\n");
  append(L"      {\n");
  append(L"        if (this.hasChildElement)\n");
  append(L"        {\n");
  append(L"          proc.stdout.write(\"\\n\");\n");
  append(L"          for (var i = 0; i < this.depth; ++i)\n");
  append(L"          {\n");
  append(L"            proc.stdout.write(\"  \");\n");
  append(L"          }\n");
  append(L"        }\n");
  append(L"      }\n");
  append(L"      proc.stdout.write(\"</\");\n");
  append(L"      proc.stdout.write(tag);\n");
  append(L"      proc.stdout.write(\">\");\n");
  append(L"    }\n");
  append(L"    this.hasChildElement = true;\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  terminal(id: number, begin: number, end: number)\n");
  append(L"  {\n");
  append(L"    var tag = ");
                                                            #line 1528 "PrintTypescript.cpp.template"
                                                                  print(className.c_str());
                                                            #line 2117 "PrintTypescript.cpp"
  append(L".Parser.getTerminalName(id);\n");
  append(L"    if (tag.charAt(0) == '\\'') tag = \"TOKEN\";\n");
  append(L"    this.startElement(tag);\n");
  append(L"    this.characters(begin, end);\n");
  append(L"    this.endElement(tag);\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  whitespace(begin: number, end: number)\n");
  append(L"  {\n");
  append(L"    this.characters(begin, end);\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  private characters(begin: number, end: number)\n");
  append(L"  {\n");
  append(L"    if (begin < end)\n");
  append(L"    {\n");
  append(L"      if (this.delayedTag != null)\n");
  append(L"      {\n");
  append(L"        proc.stdout.write(\"<\");\n");
  append(L"        proc.stdout.write(this.delayedTag);\n");
  append(L"        proc.stdout.write(\">\");\n");
  append(L"        this.delayedTag = null;\n");
  append(L"      }\n");
  append(L"      proc.stdout.write(this.input.substring(begin, end)\n");
  append(L"                 .replace(/&/g, \"&amp;\")\n");
  append(L"                 .replace(/</g, \"&lt;\")\n");
  append(L"                 .replace(/>/g, \"&gt;\"));\n");
  append(L"    }\n");
  append(L"  }\n");
  append(L"}\n");
                                                            #line 1559 "PrintTypescript.cpp.template"
                                                                }
                                                            #line 2150 "PrintTypescript.cpp"
  append(L"\n");
  append(L"// main program for use with node.js\n");
  append(L"\n");
  append(L"const proc: any = (globalThis as any).process;\n");
  append(L"const requ: any = eval(\"require\");\n");
  append(L"const fs: any = requ(\"fs\");\n");
  append(L"\n");
  append(L"if (proc.argv.length < 3)\n");
  append(L"{\n");
  append(L"  proc.stderr.write(\"Usage: node ");
                                                            #line 1569 "PrintTypescript.cpp.template"
                                                                print(className.c_str());
                                                            #line 2163 "PrintTypescript.cpp"
  append(L".js ");
                                                            #line 1570 "PrintTypescript.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 2168 "PrintTypescript.cpp"
  append(L"[-i] ");
                                                            #line 1572 "PrintTypescript.cpp.template"
                                                                }
                                                            #line 2172 "PrintTypescript.cpp"
  append(L"INPUT...\\n\");\n");
  append(L"  proc.stderr.write(\"\\n\");\n");
  append(L"  proc.stderr.write(\"  parse INPUT, which is either a filename or literal text enclosed in curly braces\\n\");");
                                                            #line 1576 "PrintTypescript.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 2179 "PrintTypescript.cpp"
  append(L"\n");
  append(L"  proc.stderr.write(\"\\n\");\n");
  append(L"  proc.stderr.write(\"  Option:\\n\");\n");
  append(L"  proc.stderr.write(\"    -i     indented parse tree\\n\");");
                                                            #line 1581 "PrintTypescript.cpp.template"
                                                                }
                                                            #line 2186 "PrintTypescript.cpp"
  append(L"\n");
  append(L"}\n");
  append(L"else\n");
  append(L"{\n");
  append(L"  var indent = false;\n");
  append(L"  for (var i = 2; i < proc.argv.length; ++i)\n");
  append(L"  {\n");
  append(L"    var arg = proc.argv[i];");
                                                            #line 1589 "PrintTypescript.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 2198 "PrintTypescript.cpp"
  append(L"\n");
  append(L"    if (arg === \"-i\")\n");
  append(L"    {\n");
  append(L"      indent = true;\n");
  append(L"      continue;\n");
  append(L"    }");
                                                            #line 1596 "PrintTypescript.cpp.template"
                                                                }
                                                            #line 2207 "PrintTypescript.cpp"
  append(L"\n");
  append(L"    var input: string;\n");
  append(L"    if (/");
  append(L"^");
  append(L"{.*}$/.test(arg))\n");
  append(L"    {\n");
  append(L"      input = arg.substring(1, arg.length - 1);\n");
  append(L"    }\n");
  append(L"    else\n");
  append(L"    {\n");
  append(L"      var content = fs.readFileSync(arg, \"utf-8\");\n");
  append(L"      input = content.length > 0 && content.charCodeAt(0) == 0xFEFF\n");
  append(L"            ? content.substring(1)\n");
  append(L"            : content;\n");
  append(L"    }");
                                                            #line 1609 "PrintTypescript.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 2226 "PrintTypescript.cpp"
  append(L"\n");
  append(L"    var s = new XmlSerializer(indent);");
                                                            #line 1612 "PrintTypescript.cpp.template"
                                                                  if (isLrParser)
                                                                  {
                                                            #line 2232 "PrintTypescript.cpp"
  append(L"\n");
  append(L"    var t = new ");
                                                            #line 1615 "PrintTypescript.cpp.template"
                                                                    print(className.c_str());
                                                            #line 2237 "PrintTypescript.cpp"
  append(L".ParseTreeBuilder();");
                                                            #line 1616 "PrintTypescript.cpp.template"
                                                                  }
                                                                }
                                                            #line 2242 "PrintTypescript.cpp"
  append(L"\n");
  append(L"    var parser = new ");
                                                            #line 1619 "PrintTypescript.cpp.template"
                                                                print(className.c_str());
                                                            #line 2247 "PrintTypescript.cpp"
  append(L".Parser(input");
                                                            #line 1620 "PrintTypescript.cpp.template"
                                                                if (tree)
                                                                {
                                                                  if (isLrParser)
                                                                  {
                                                            #line 2254 "PrintTypescript.cpp"
  append(L", t");
                                                            #line 1624 "PrintTypescript.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 2260 "PrintTypescript.cpp"
  append(L", s");
                                                            #line 1627 "PrintTypescript.cpp.template"
                                                                  }
                                                                }
                                                            #line 2265 "PrintTypescript.cpp"
  append(L");\n");
  append(L"    try\n");
  append(L"    {");
                                                            #line 1631 "PrintTypescript.cpp.template"
                                                                if (trace)
                                                                {
                                                            #line 2272 "PrintTypescript.cpp"
  append(L"\n");
  append(L"      parser.writeTrace(\"<?xml version=\\\"1.0\\\" encoding=\\\"UTF-8\\\"?\" + \">\\n<trace>\\n\");");
                                                            #line 1635 "PrintTypescript.cpp.template"
                                                                }
                                                            #line 2277 "PrintTypescript.cpp"
  append(L"\n");
  append(L"      parser.");
                                                            #line 1637 "PrintTypescript.cpp.template"
                                                                print(methodPrefixParse);
                                                                print(Format::acceptableName<WString>(grammar->startSymbol()->name).c_str());
                                                            #line 2283 "PrintTypescript.cpp"
  append(L"();");
                                                            #line 1639 "PrintTypescript.cpp.template"
                                                                if (trace)
                                                                {
                                                            #line 2288 "PrintTypescript.cpp"
  append(L"\n");
  append(L"      parser.writeTrace(\"</trace>\\n\");\n");
  append(L"      parser.flushTrace();");
                                                            #line 1643 "PrintTypescript.cpp.template"
                                                                }
                                                                if (tree && isLrParser)
                                                                {
                                                            #line 2296 "PrintTypescript.cpp"
  append(L"\n");
  append(L"      t.serialize(s);");
                                                            #line 1647 "PrintTypescript.cpp.template"
                                                                }
                                                            #line 2301 "PrintTypescript.cpp"
  append(L"\n");
  append(L"    }\n");
  append(L"    catch (pe)\n");
  append(L"    {\n");
  append(L"      if (! (pe instanceof ");
                                                            #line 1652 "PrintTypescript.cpp.template"
                                                                print(className.c_str());
                                                            #line 2309 "PrintTypescript.cpp"
  append(L".ParseException))\n");
  append(L"      {\n");
  append(L"        throw pe;\n");
  append(L"      }\n");
  append(L"      else\n");
  append(L"      {");
                                                            #line 1658 "PrintTypescript.cpp.template"
                                                                if (rejectsAmbiguity() && tree)
                                                                {
                                                            #line 2319 "PrintTypescript.cpp"
  append(L"\n");
  append(L"        if (pe.isAmbiguousInput())\n");
  append(L"        {\n");
  append(L"          pe.serialize(s);\n");
  append(L"          proc.stdout.write(\"\\n\");\n");
  append(L"        }");
                                                            #line 1665 "PrintTypescript.cpp.template"
                                                                }
                                                            #line 2328 "PrintTypescript.cpp"
  append(L"\n");
  append(L"        throw parser.getErrorMessage(pe);\n");
  append(L"      }\n");
  append(L"    }\n");
  append(L"  }\n");
  append(L"}\n");
                                                            #line 1672 "PrintTypescript.cpp.template"
                                                              }
                                                              if (performanceTest)
                                                              {
                                                                printFileProcessor();
                                                              }
                                                            }

// End
