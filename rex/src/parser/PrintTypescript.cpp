// This file was generated on Sun Nov 24, 2024 16:09 (UTC+01) by REx v6.0 which is Copyright (c) 1979-2024 by Gunther Rademacher <grd@gmx.net>
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
  append(L"module ");
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
  append(L"    startNonterminal(name: string, begin: number): void;\n");
  append(L"    endNonterminal(name: string, end: number): void;\n");
  append(L"    terminal(name: string, begin: number, end: number): void;\n");
  append(L"    whitespace(begin: number, end: number): void;\n");
  append(L"  }\n");
                                                            #line 24 "PrintTypescript.cpp.template"
                                                              if (isLrParser)
                                                              {
                                                            #line 37 "PrintTypescript.cpp"
  append(L"\n");
  append(L"  export interface BottomUpEventHandler\n");
  append(L"  {\n");
  append(L"    reset(input: string): void;\n");
  append(L"    nonterminal(name: string, begin: number, end: number, count: number): void;\n");
  append(L"    terminal(name: string, begin: number, end: number): void;\n");
  append(L"  }\n");
                                                            #line 33 "PrintTypescript.cpp.template"
                                                              }
                                                            #line 47 "PrintTypescript.cpp"
  append(L"\n");
  append(L"  export class ParseException\n");
  append(L"  {\n");
  append(L"    private begin: number;\n");
  append(L"    private end: number;\n");
  append(L"    private state: number;\n");
  append(L"    private offending: number;\n");
  append(L"    private expected: number;");
                                                            #line 41 "PrintTypescript.cpp.template"
                                                              if (useGlr)
                                                              {
                                                            #line 59 "PrintTypescript.cpp"
  append(L"\n");
  append(L"    private ambiguousInput: boolean;");
                                                            #line 44 "PrintTypescript.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 65 "PrintTypescript.cpp"
  append(L"\n");
  append(L"    private ambiguityDescriptor: ParseTreeBuilder;");
                                                            #line 47 "PrintTypescript.cpp.template"
                                                                }
                                                              }
                                                            #line 71 "PrintTypescript.cpp"
  append(L"\n");
  append(L"\n");
  append(L"    constructor(b: number, e: number, s: number, o: number, x: number)\n");
  append(L"    {\n");
  append(L"      this.begin = b;\n");
  append(L"      this.end = e;\n");
  append(L"      this.state = s;\n");
  append(L"      this.offending = o;\n");
  append(L"      this.expected = x;");
                                                            #line 57 "PrintTypescript.cpp.template"
                                                              if (useGlr)
                                                              {
                                                            #line 84 "PrintTypescript.cpp"
  append(L"\n");
  append(L"      this.ambiguousInput = false;");
                                                            #line 60 "PrintTypescript.cpp.template"
                                                                if (tree)
                                                                {
                                                                }
                                                              }
                                                            #line 92 "PrintTypescript.cpp"
  append(L"\n");
  append(L"    }\n");
                                                            #line 66 "PrintTypescript.cpp.template"
                                                              if (useGlr)
                                                              {
                                                            #line 98 "PrintTypescript.cpp"
  append(L"\n");
  append(L"    setAmbiguousInput(");
                                                            #line 69 "PrintTypescript.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 104 "PrintTypescript.cpp"
  append(L"a: ParseTreeBuilder");
                                                            #line 71 "PrintTypescript.cpp.template"
                                                                }
                                                            #line 108 "PrintTypescript.cpp"
  append(L")\n");
  append(L"    {\n");
  append(L"      this.ambiguousInput = true;");
                                                            #line 74 "PrintTypescript.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 115 "PrintTypescript.cpp"
  append(L"\n");
  append(L"      this.ambiguityDescriptor = a;");
                                                            #line 77 "PrintTypescript.cpp.template"
                                                                }
                                                            #line 120 "PrintTypescript.cpp"
  append(L"\n");
  append(L"    }\n");
                                                            #line 80 "PrintTypescript.cpp.template"
                                                              }
                                                            #line 125 "PrintTypescript.cpp"
  append(L"\n");
  append(L"    getBegin() {return this.begin;}\n");
  append(L"    getEnd() {return this.end;}\n");
  append(L"    getState() {return this.state;}\n");
  append(L"    getExpected() {return this.expected;}\n");
  append(L"    getOffending() {return this.offending;}\n");
  append(L"    isAmbiguousInput() {return ");
                                                            #line 87 "PrintTypescript.cpp.template"
                                                              if (useGlr)
                                                              {
                                                            #line 136 "PrintTypescript.cpp"
  append(L"this.ambiguousInput");
                                                            #line 89 "PrintTypescript.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 142 "PrintTypescript.cpp"
  append(L"false");
                                                            #line 92 "PrintTypescript.cpp.template"
                                                              }
                                                            #line 146 "PrintTypescript.cpp"
  append(L";}\n");
  append(L"\n");
  append(L"    getMessage()\n");
  append(L"    {\n");
  append(L"      return ");
                                                            #line 97 "PrintTypescript.cpp.template"
                                                              if (useGlr)
                                                              {
                                                            #line 155 "PrintTypescript.cpp"
  append(L"this.ambiguousInput\n");
  append(L"           ? \"ambiguous input\"\n");
  append(L"           : ");
                                                            #line 101 "PrintTypescript.cpp.template"
                                                              }
                                                            #line 161 "PrintTypescript.cpp"
  append(L"this.offending < 0\n");
  append(L"           ? \"lexical analysis failed\"\n");
  append(L"           : \"syntax error\";\n");
  append(L"    }");
                                                            #line 105 "PrintTypescript.cpp.template"
                                                              if (useGlr && tree)
                                                              {
                                                            #line 169 "PrintTypescript.cpp"
  append(L"\n");
  append(L"\n");
  append(L"    serialize(eventHandler: ParsingEventHandler)\n");
  append(L"    {\n");
  append(L"      this.ambiguityDescriptor.serialize(eventHandler);\n");
  append(L"    }");
                                                            #line 112 "PrintTypescript.cpp.template"
                                                               }
                                                            #line 178 "PrintTypescript.cpp"
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
                                                            #line 123 "PrintTypescript.cpp.template"
                                                              if (noLexer)
                                                              {
                                                            #line 193 "PrintTypescript.cpp"
  append(L", l: Lexer");
                                                            #line 125 "PrintTypescript.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                            #line 199 "PrintTypescript.cpp"
  append(L", parsingEventHandler: ");
                                                            #line 129 "PrintTypescript.cpp.template"
                                                                if (isLrParser)
                                                                {
                                                            #line 204 "PrintTypescript.cpp"
  append(L"BottomUp");
                                                            #line 132 "PrintTypescript.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 210 "PrintTypescript.cpp"
  append(L"Parsing");
                                                            #line 135 "PrintTypescript.cpp.template"
                                                                }
                                                            #line 214 "PrintTypescript.cpp"
  append(L"EventHandler");
                                                            #line 137 "PrintTypescript.cpp.template"
                                                              }
                                                            #line 218 "PrintTypescript.cpp"
  append(L")\n");
  append(L"    {\n");
  append(L"      this.initialize(source");
                                                            #line 140 "PrintTypescript.cpp.template"
                                                              if (noLexer)
                                                              {
                                                            #line 225 "PrintTypescript.cpp"
  append(L", l");
                                                            #line 142 "PrintTypescript.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                            #line 231 "PrintTypescript.cpp"
  append(L", parsingEventHandler");
                                                            #line 146 "PrintTypescript.cpp.template"
                                                              }
                                                            #line 235 "PrintTypescript.cpp"
  append(L");\n");
  append(L"    }\n");
                                                            #line 149 "PrintTypescript.cpp.template"
                                                              increaseIndent();
                                                            }

                                                            void PrintTypescript::printFlush(int i, bool withinThread)
                                                            {
                                                              increaseIndent(i);
                                                              if (trace)
                                                              {
                                                            #line 247 "PrintTypescript.cpp"
  append(L"\n");
  append(L"parser.flushTrace();");
                                                            #line 158 "PrintTypescript.cpp.template"
                                                              }
                                                              decreaseIndent(i);
                                                            }

                                                            void PrintTypescript::printGlrParseMethod()
                                                            {
                                                            #line 257 "PrintTypescript.cpp"
  append(L"\n");
  append(L"public static PARSING = 0;\n");
  append(L"public static ACCEPTED = 1;\n");
  append(L"public static ERROR = 2;\n");
  append(L"\n");
  append(L"public parse(target: number, initialState: number, ");
                                                            #line 169 "PrintTypescript.cpp.template"
                                                          if (tree)
                                                              {
                                                            #line 267 "PrintTypescript.cpp"
  append(L"eventHandler: BottomUpEventHandler, ");
                                                            #line 172 "PrintTypescript.cpp.template"
                                                              }
                                                            #line 271 "PrintTypescript.cpp"
  append(L"thread: ParsingThread): ParsingThread\n");
  append(L"{\n");
  append(L"  var threads: Heap = thread.open(initialState");
                                                            #line 176 "PrintTypescript.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 278 "PrintTypescript.cpp"
  append(L", eventHandler, target");
                                                            #line 179 "PrintTypescript.cpp.template"
                                                              }
                                                            #line 282 "PrintTypescript.cpp"
  append(L");\n");
  append(L"  while (true)\n");
  append(L"  {\n");
  append(L"    thread = threads.poll();\n");
  append(L"    if (thread.accepted)\n");
  append(L"    {\n");
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
                                                            #line 198 "PrintTypescript.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 305 "PrintTypescript.cpp"
  append(L", thread.deferredEvent, other.deferredEvent");
                                                            #line 200 "PrintTypescript.cpp.template"
                                                              }
                                                            #line 309 "PrintTypescript.cpp"
  append(L");\n");
  append(L"      }");
                                                            #line 203 "PrintTypescript.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 315 "PrintTypescript.cpp"
  append(L"\n");
  append(L"      if (thread.deferredEvent != null)\n");
  append(L"      {\n");
  append(L"        thread.deferredEvent.release(eventHandler);\n");
  append(L"        thread.deferredEvent = null;\n");
  append(L"      }");
                                                            #line 210 "PrintTypescript.cpp.template"
                                                              }
                                                              if (hasCustomCode)
                                                              {
                                                            #line 326 "PrintTypescript.cpp"
  append(L"\n");
  append(L"      thread.executeDeferredCode();");
                                                            #line 214 "PrintTypescript.cpp.template"
                                                              }
                                                            #line 331 "PrintTypescript.cpp"
  append(L"\n");
  append(L"      return thread;\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    if (! threads.isEmpty())\n");
  append(L"    {\n");
  append(L"      if (threads.peek().equals(thread))\n");
  append(L"      {\n");
  append(L"        this.rejectAmbiguity(thread.stack.pos, thread.e0");
                                                            #line 223 "PrintTypescript.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 344 "PrintTypescript.cpp"
  append(L", thread.deferredEvent, threads.peek().deferredEvent");
                                                            #line 225 "PrintTypescript.cpp.template"
                                                              }
                                                            #line 348 "PrintTypescript.cpp"
  append(L");\n");
  append(L"      }\n");
  append(L"    }");
                                                            #line 228 "PrintTypescript.cpp.template"
                                                              if (tree || hasCustomCode)
                                                              {
                                                            #line 355 "PrintTypescript.cpp"
  append(L"\n");
  append(L"    else\n");
  append(L"    {");
                                                            #line 232 "PrintTypescript.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 362 "PrintTypescript.cpp"
  append(L"\n");
  append(L"      if (thread.deferredEvent != null)\n");
  append(L"      {\n");
  append(L"        thread.deferredEvent.release(eventHandler);\n");
  append(L"        thread.deferredEvent = null;\n");
  append(L"      }");
                                                            #line 239 "PrintTypescript.cpp.template"
                                                                }
                                                                if (hasCustomCode)
                                                                {
                                                            #line 373 "PrintTypescript.cpp"
  append(L"\n");
  append(L"      thread.executeDeferredCode();");
                                                            #line 243 "PrintTypescript.cpp.template"
                                                                }
                                                            #line 378 "PrintTypescript.cpp"
  append(L"\n");
  append(L"    }");
                                                            #line 245 "PrintTypescript.cpp.template"
                                                              }
                                                            #line 383 "PrintTypescript.cpp"
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
  append(L"\n");
  append(L"private rejectAmbiguity(begin: number, end: number");
                                                            #line 271 "PrintTypescript.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 413 "PrintTypescript.cpp"
  append(L", first: DeferredEvent, second: DeferredEvent");
                                                            #line 273 "PrintTypescript.cpp.template"
                                                              }
                                                            #line 417 "PrintTypescript.cpp"
  append(L"): void\n");
  append(L"{");
                                                            #line 275 "PrintTypescript.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 423 "PrintTypescript.cpp"
  append(L"\n");
  append(L"  var treeBuilder = new ParseTreeBuilder();\n");
  append(L"  treeBuilder.reset(this.input);\n");
  append(L"  second.show(treeBuilder);\n");
  append(L"  treeBuilder.nonterminal(\"ALTERNATIVE\", treeBuilder.getStack()[0].begin, treeBuilder.getStack()[treeBuilder.getTop()].end, treeBuilder.getTop() + 1);\n");
  append(L"  var secondTree = treeBuilder.pop(1)[0];\n");
  append(L"  first.show(treeBuilder);\n");
  append(L"  treeBuilder.nonterminal(\"ALTERNATIVE\", treeBuilder.getStack()[0].begin, treeBuilder.getStack()[treeBuilder.getTop()].end, treeBuilder.getTop() + 1);\n");
  append(L"  treeBuilder.push(secondTree);\n");
  append(L"  treeBuilder.nonterminal(\"AMBIGUOUS\", treeBuilder.getStack()[0].begin, treeBuilder.getStack()[treeBuilder.getTop()].end, 2);");
                                                            #line 287 "PrintTypescript.cpp.template"
                                                              }
                                                            #line 436 "PrintTypescript.cpp"
  append(L"\n");
  append(L"  var exception = new ParseException(begin, end, -1, -1, -1);\n");
  append(L"  exception.setAmbiguousInput(");
                                                            #line 290 "PrintTypescript.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 443 "PrintTypescript.cpp"
  append(L"treeBuilder");
                                                            #line 292 "PrintTypescript.cpp.template"
                                                              }
                                                            #line 447 "PrintTypescript.cpp"
  append(L");\n");
  append(L"  throw exception;\n");
  append(L"}\n");
  append(L"\n");
  append(L"private thread: ParsingThread;");
                                                            #line 297 "PrintTypescript.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 456 "PrintTypescript.cpp"
  append(L"\n");
  append(L"private eventHandler: BottomUpEventHandler;");
                                                            #line 300 "PrintTypescript.cpp.template"
                                                              }
                                                            #line 461 "PrintTypescript.cpp"
  append(L"\n");
  append(L"public input: string;\n");
  append(L"public size: number;\n");
  append(L"public maxId: number;");
                                                            #line 304 "PrintTypescript.cpp.template"
                                                            }

                                                            void PrintTypescript::openStackNode()
                                                            {
                                                            #line 471 "PrintTypescript.cpp"
  append(L"\n");
  append(L"class StackNode\n");
  append(L"{\n");
  append(L"  public state: number;");
                                                            #line 311 "PrintTypescript.cpp.template"
                                                              if (grammar->states->hasLookback)
                                                              {
                                                            #line 479 "PrintTypescript.cpp"
  append(L"\n");
  append(L"  private code: number;");
                                                            #line 314 "PrintTypescript.cpp.template"
                                                              }
                                                            #line 484 "PrintTypescript.cpp"
  append(L"\n");
  append(L"  public pos: number;\n");
  append(L"  public link: StackNode;\n");
  append(L"\n");
  append(L"  constructor(state: number, ");
                                                            #line 319 "PrintTypescript.cpp.template"
                                                              if (grammar->states->hasLookback)
                                                              {
                                                            #line 493 "PrintTypescript.cpp"
  append(L"code: number, ");
                                                            #line 321 "PrintTypescript.cpp.template"
                                                              }
                                                            #line 497 "PrintTypescript.cpp"
  append(L"pos: number, link: StackNode)\n");
  append(L"  {\n");
  append(L"    this.state = state;");
                                                            #line 324 "PrintTypescript.cpp.template"
                                                              if (grammar->states->hasLookback)
                                                              {
                                                            #line 504 "PrintTypescript.cpp"
  append(L"\n");
  append(L"    this.code = code;");
                                                            #line 327 "PrintTypescript.cpp.template"
                                                              }
                                                            #line 509 "PrintTypescript.cpp"
  append(L"\n");
  append(L"    this.pos = pos;\n");
  append(L"    this.link = link;\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  equals(obj: StackNode)\n");
  append(L"  {\n");
  append(L"    var lhs: StackNode = this;\n");
  append(L"    var rhs: StackNode = obj;\n");
  append(L"    while (lhs != null && rhs != null)\n");
  append(L"    {\n");
  append(L"      if (lhs == rhs) return true;\n");
  append(L"      if (lhs.state != rhs.state) return false;");
                                                            #line 340 "PrintTypescript.cpp.template"
                                                              if (grammar->states->hasLookback)
                                                              {
                                                            #line 526 "PrintTypescript.cpp"
  append(L"\n");
  append(L"      if (lhs.code != rhs.code) return false;");
                                                            #line 343 "PrintTypescript.cpp.template"
                                                              }
                                                            #line 531 "PrintTypescript.cpp"
  append(L"\n");
  append(L"      if (lhs.pos != rhs.pos) return false;\n");
  append(L"      lhs = lhs.link;\n");
  append(L"      rhs = rhs.link;\n");
  append(L"    }\n");
  append(L"    return lhs == rhs;\n");
  append(L"  }\n");
                                                            #line 351 "PrintTypescript.cpp.template"
                                                              increaseIndent();
                                                            }

                                                            void PrintTypescript::closeStackNode()
                                                            {
                                                              decreaseIndent();
                                                            #line 546 "PrintTypescript.cpp"
  append(L"\n");
  append(L"}\n");
                                                            #line 359 "PrintTypescript.cpp.template"
                                                              if (hasCustomCode)
                                                              {
                                                            #line 552 "PrintTypescript.cpp"
  append(L"\n");
  append(L"class DeferredCode\n");
  append(L"{\n");
  append(L"  public link: DeferredCode;\n");
  append(L"  public codeId: number;\n");
  append(L"  public b0: number;\n");
  append(L"  public e0: number;\n");
  append(L"\n");
  append(L"  constructor(link, codeId, b0, e0)\n");
  append(L"  {\n");
  append(L"    this.link = link;\n");
  append(L"    this.codeId = codeId;\n");
  append(L"    this.b0 = b0;\n");
  append(L"    this.e0 = e0;\n");
  append(L"  }\n");
  append(L"}\n");
                                                            #line 377 "PrintTypescript.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                            #line 573 "PrintTypescript.cpp"
  append(L"\n");
  append(L"class DeferredEvent\n");
  append(L"{\n");
  append(L"  private link: DeferredEvent;\n");
  append(L"  private name: string;\n");
  append(L"  private begin: number;\n");
  append(L"  private end: number;\n");
  append(L"  private count: number;\n");
  append(L"\n");
  append(L"  constructor(link: DeferredEvent, name: string, begin: number, end: number, count: number)\n");
  append(L"  {\n");
  append(L"    this.link = link;\n");
  append(L"    this.name = name;\n");
  append(L"    this.link = link;\n");
  append(L"    this.begin = begin;\n");
  append(L"    this.end = end;\n");
  append(L"    this.count = count;\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  execute(eventHandler: BottomUpEventHandler)\n");
  append(L"  {\n");
  append(L"    if (this.count == null)\n");
  append(L"    {\n");
  append(L"      eventHandler.terminal(this.name, this.begin, this.end);\n");
  append(L"    }\n");
  append(L"    else\n");
  append(L"    {\n");
  append(L"      eventHandler.nonterminal(this.name, this.begin, this.end, this.count);\n");
  append(L"    }\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  release(eventHandler: BottomUpEventHandler)\n");
  append(L"  {\n");
  append(L"    var current: DeferredEvent = this;\n");
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
  append(L"      current.execute(eventHandler);\n");
  append(L"      current = current.link;\n");
  append(L"    }\n");
  append(L"    while (current != null);\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  show(eventHandler: BottomUpEventHandler)\n");
  append(L"  {\n");
  append(L"    var stack = [];\n");
  append(L"    for (var current: DeferredEvent = this; current != null; current = current.link)\n");
  append(L"    {\n");
  append(L"      stack.push(current);\n");
  append(L"    }\n");
  append(L"    while (stack.length > 0)\n");
  append(L"    {\n");
  append(L"      stack.pop().execute(eventHandler);\n");
  append(L"    }\n");
  append(L"  }\n");
  append(L"}\n");
                                                            #line 444 "PrintTypescript.cpp.template"
                                                              }
                                                            #line 640 "PrintTypescript.cpp"
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
  append(L"    if (this.size == 0)\n");
  append(L"      return null;\n");
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
  append(L"    return this.size == 0 ? null : this.array[0];\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  isEmpty(): boolean\n");
  append(L"  {\n");
  append(L"    return this.size == 0;\n");
  append(L"  }\n");
  append(L"}\n");
                                                            #line 511 "PrintTypescript.cpp.template"
                                                            }

                                                            void PrintTypescript::openThread()
                                                            {
                                                            #line 712 "PrintTypescript.cpp"
  append(L"\n");
  append(L"class ParsingThread\n");
  append(L"{\n");
  append(L"  public parser: Parser;\n");
  append(L"  private threads: Heap;\n");
  append(L"  public accepted: boolean;\n");
  append(L"  public stack: StackNode;\n");
  append(L"  public state: number;\n");
  append(L"  private action: number;\n");
  append(L"  private target: number;");
                                                            #line 524 "PrintTypescript.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 726 "PrintTypescript.cpp"
  append(L"\n");
  append(L"  public deferredEvent: DeferredEvent;\n");
  append(L"  private es: number;");
                                                            #line 528 "PrintTypescript.cpp.template"
                                                              }
                                                            #line 732 "PrintTypescript.cpp"
  append(L"\n");
  append(L"  private bw: number;\n");
  append(L"  private bs: number;");
                                                            #line 531 "PrintTypescript.cpp.template"
                                                              if (hasCustomCode)
                                                              {
                                                            #line 739 "PrintTypescript.cpp"
  append(L"\n");
  append(L"  public deferredCode: DeferredCode;");
                                                            #line 534 "PrintTypescript.cpp.template"
                                                              }
                                                            #line 744 "PrintTypescript.cpp"
  append(L"\n");
  append(L"  private id: number;\n");
  append(L"\n");
  append(L"  open(initialState: number");
                                                            #line 538 "PrintTypescript.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 752 "PrintTypescript.cpp"
  append(L", eventHandler: BottomUpEventHandler, target: number");
                                                            #line 541 "PrintTypescript.cpp.template"
                                                              }
                                                            #line 756 "PrintTypescript.cpp"
  append(L"): Heap\n");
  append(L"  {\n");
  append(L"    this.accepted = false;");
                                                            #line 544 "PrintTypescript.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 763 "PrintTypescript.cpp"
  append(L"\n");
  append(L"    if (eventHandler != null)\n");
  append(L"    {\n");
  append(L"      eventHandler.reset(this.parser.input);\n");
  append(L"    }\n");
  append(L"    this.eventHandler = eventHandler;\n");
  append(L"    this.target = target;\n");
  append(L"    this.deferredEvent = null;");
                                                            #line 553 "PrintTypescript.cpp.template"
                                                              }
                                                              if (hasCustomCode)
                                                              {
                                                            #line 776 "PrintTypescript.cpp"
  append(L"\n");
  append(L"    this.deferredCode = null;");
                                                            #line 557 "PrintTypescript.cpp.template"
                                                              }
                                                            #line 781 "PrintTypescript.cpp"
  append(L"\n");
  append(L"    this.stack = new StackNode(-1, ");
                                                            #line 559 "PrintTypescript.cpp.template"
                                                              if (grammar->states->hasLookback)
                                                              {
                                                            #line 787 "PrintTypescript.cpp"
  append(L"0, ");
                                                            #line 561 "PrintTypescript.cpp.template"
                                                              }
                                                            #line 791 "PrintTypescript.cpp"
  append(L"this.e0, null);\n");
  append(L"    this.state = initialState;\n");
  append(L"    this.action = this.predict(initialState);");
                                                            #line 564 "PrintTypescript.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 798 "PrintTypescript.cpp"
  append(L"\n");
  append(L"    this.bw = this.e0;\n");
  append(L"    this.bs = this.e0;\n");
  append(L"    this.es = this.e0;");
                                                            #line 569 "PrintTypescript.cpp.template"
                                                              }
                                                            #line 805 "PrintTypescript.cpp"
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
                                                            #line 584 "PrintTypescript.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 824 "PrintTypescript.cpp"
  append(L"\n");
  append(L"    this.bs = other.bs;\n");
  append(L"    this.es = other.es;\n");
  append(L"    this.bw = other.bw;\n");
  append(L"    this.eventHandler = other.eventHandler;\n");
  append(L"    this.target = other.target;\n");
  append(L"    this.deferredEvent = other.deferredEvent;");
                                                            #line 592 "PrintTypescript.cpp.template"
                                                              }
                                                              if (hasCustomCode)
                                                              {
                                                            #line 836 "PrintTypescript.cpp"
  append(L"\n");
  append(L"    this.deferredCode = other.deferredCode;");
                                                            #line 596 "PrintTypescript.cpp.template"
                                                              }
                                                            #line 841 "PrintTypescript.cpp"
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
                                                            #line 626 "PrintTypescript.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 874 "PrintTypescript.cpp"
  append(L"\n");
  append(L"  release()\n");
  append(L"  {\n");
  append(L"    if (this.deferredEvent != null)\n");
  append(L"    {\n");
  append(L"      this.deferredEvent.release(this.eventHandler);\n");
  append(L"      this.deferredEvent = null;\n");
  append(L"    }\n");
  append(L"  }\n");
                                                            #line 637 "PrintTypescript.cpp.template"
                                                              }
                                                            #line 886 "PrintTypescript.cpp"
  append(L"\n");
  append(L"  parse()\n");
  append(L"  {");
                                                            #line 640 "PrintTypescript.cpp.template"
                                                              increaseIndent();
                                                            }

                                                            void PrintTypescript::openMethod(const wchar_t *type,
                                                                                             const wchar_t *prefix,
                                                                                             const wchar_t *name,
                                                                                             const wchar_t *args,
                                                                                             bool constant,
                                                                                             const wchar_t *clazz)
                                                            {
                                                            #line 901 "PrintTypescript.cpp"
  append(L"\n");
                                                            #line 651 "PrintTypescript.cpp.template"
                                                              if (isPublic)
                                                              {
                                                                print(name);
                                                              }
                                                              else
                                                              {
                                                            #line 910 "PrintTypescript.cpp"
  append(L"private ");
                                                            #line 657 "PrintTypescript.cpp.template"
                                                                print(name);
                                                              }
                                                            #line 915 "PrintTypescript.cpp"
  append(L"(");
                                                            #line 659 "PrintTypescript.cpp.template"
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
                                                                    print(typeBegin, typeEnd - typeBegin);
                                                                }
                                                              }
                                                            #line 946 "PrintTypescript.cpp"
  append(L")");
                                                            #line 687 "PrintTypescript.cpp.template"
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
                                                            #line 960 "PrintTypescript.cpp"
  append(L"\n");
  append(L"  private lookaheadString(): string\n");
  append(L"  {\n");
  append(L"    var result = \"\";\n");
  append(L"    if (");
                                                            #line 702 "PrintTypescript.cpp.template"
                                                                print(thiz());
                                                            #line 968 "PrintTypescript.cpp"
  append(L"l1 > 0)\n");
  append(L"    {\n");
  append(L"      result += ");
                                                            #line 705 "PrintTypescript.cpp.template"
                                                                print(staticPrefix());
                                                            #line 974 "PrintTypescript.cpp"
  append(L"TOKEN[");
                                                            #line 706 "PrintTypescript.cpp.template"
                                                                print(thiz());
                                                            #line 978 "PrintTypescript.cpp"
  append(L"l1];");
                                                            #line 707 "PrintTypescript.cpp.template"
                                                                for (size_t i = 2; i <= grammar->k; ++i)
                                                                {
                                                            #line 983 "PrintTypescript.cpp"
  append(L"\n");
  append(L"      if (");
                                                            #line 710 "PrintTypescript.cpp.template"
                                                                  print(thiz());
                                                            #line 988 "PrintTypescript.cpp"
  append(L"l");
                                                            #line 711 "PrintTypescript.cpp.template"
                                                                  print(format.toString<wchar_t>(i));
                                                            #line 992 "PrintTypescript.cpp"
  append(L" > 0)\n");
  append(L"      {\n");
  append(L"        result += \" \" + ");
                                                            #line 714 "PrintTypescript.cpp.template"
                                                                  print(staticPrefix());
                                                            #line 998 "PrintTypescript.cpp"
  append(L"TOKEN[");
                                                            #line 715 "PrintTypescript.cpp.template"
                                                                  print(thiz());
                                                            #line 1002 "PrintTypescript.cpp"
  append(L"l");
                                                            #line 716 "PrintTypescript.cpp.template"
                                                                  print(format.toString<wchar_t>(i));
                                                            #line 1006 "PrintTypescript.cpp"
  append(L"];");
                                                            #line 717 "PrintTypescript.cpp.template"
                                                                  increaseIndent();
                                                                }
                                                                for (size_t i = 2; i <= grammar->k; ++i)
                                                                {
                                                                  decreaseIndent();
                                                            #line 1014 "PrintTypescript.cpp"
  append(L"\n");
  append(L"      }");
                                                            #line 723 "PrintTypescript.cpp.template"
                                                                }
                                                            #line 1019 "PrintTypescript.cpp"
  append(L"\n");
  append(L"    }\n");
  append(L"    return result;\n");
  append(L"  }\n");
                                                            #line 728 "PrintTypescript.cpp.template"
                                                              }
                                                              if (needTokenFunction)
                                                              {
                                                            #line 1028 "PrintTypescript.cpp"
  append(L"\n");
  append(L"  private token(): number\n");
  append(L"  {\n");
  append(L"    return this.l1;\n");
  append(L"  }\n");
                                                            #line 736 "PrintTypescript.cpp.template"
                                                              }
                                                              if (needTokenSequenceFunction)
                                                              {
                                                            #line 1038 "PrintTypescript.cpp"
  append(L"\n");
  append(L"  private tokenSequence(): number\n");
  append(L"  {\n");
  append(L"    return this.lk;\n");
  append(L"  }\n");
                                                            #line 744 "PrintTypescript.cpp.template"
                                                              }
                                                              const wchar_t *visibility = useGlr ? L"public" : L"private";
                                                            #line 1047 "PrintTypescript.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 747 "PrintTypescript.cpp.template"
                                                              if (! isLrParser && (grammar->k > 1 || memoization || ! grammar->decisionPoints.empty()))
                                                              {
                                                            #line 1053 "PrintTypescript.cpp"
  append(L"private lk: number; ");
                                                            #line 749 "PrintTypescript.cpp.template"
                                                              }
                                                              else
                                                              {
                                                                print(wcslen(visibility), L" ");
                                                            #line 1060 "PrintTypescript.cpp"
  append(L"             ");
                                                            #line 753 "PrintTypescript.cpp.template"
                                                              }
                                                              print(visibility);
                                                            #line 1065 "PrintTypescript.cpp"
  append(L" b0: number; ");
                                                            #line 755 "PrintTypescript.cpp.template"
                                                              print(visibility);
                                                            #line 1069 "PrintTypescript.cpp"
  append(L" e0: number;");
                                                            #line 756 "PrintTypescript.cpp.template"
                                                              for (size_t k = 1; k <= grammar->k; ++k)
                                                              {
                                                                Format format;
                                                                wchar_t *asString = format.toString<wchar_t>(k);
                                                            #line 1076 "PrintTypescript.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 761 "PrintTypescript.cpp.template"
                                                                print(visibility);
                                                            #line 1081 "PrintTypescript.cpp"
  append(L" l");
                                                            #line 762 "PrintTypescript.cpp.template"
                                                                print(asString);
                                                            #line 1085 "PrintTypescript.cpp"
  append(L": number; ");
                                                            #line 763 "PrintTypescript.cpp.template"
                                                                print(visibility);
                                                            #line 1089 "PrintTypescript.cpp"
  append(L" b");
                                                            #line 764 "PrintTypescript.cpp.template"
                                                                print(asString);
                                                            #line 1093 "PrintTypescript.cpp"
  append(L": number; ");
                                                            #line 765 "PrintTypescript.cpp.template"
                                                                print(visibility);
                                                            #line 1097 "PrintTypescript.cpp"
  append(L" e");
                                                            #line 766 "PrintTypescript.cpp.template"
                                                                print(asString);
                                                            #line 1101 "PrintTypescript.cpp"
  append(L": number;");
                                                            #line 767 "PrintTypescript.cpp.template"
                                                              }
                                                              if (hasBacktracking)
                                                              {
                                                            #line 1107 "PrintTypescript.cpp"
  append(L"\n");
  append(L"  private bx: number; private ex: number; private sx: number; private lx: number; private tx: number;");
                                                            #line 772 "PrintTypescript.cpp.template"
                                                              }
                                                              if (isLrParser && ! useGlr)
                                                              {
                                                            #line 1114 "PrintTypescript.cpp"
  append(L"\n");
  append(L"  private iStack: number[] = [];\n");
  append(L"  private top: number = -1;");
                                                            #line 777 "PrintTypescript.cpp.template"
                                                              }

                                                              if (tree)
                                                              {
                                                            #line 1123 "PrintTypescript.cpp"
  append(L"\n");
  append(L"  private eventHandler: ");
                                                            #line 782 "PrintTypescript.cpp.template"
                                                                if (isLrParser)
                                                                {
                                                            #line 1129 "PrintTypescript.cpp"
  append(L"BottomUp");
                                                            #line 784 "PrintTypescript.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1135 "PrintTypescript.cpp"
  append(L"Parsing");
                                                            #line 787 "PrintTypescript.cpp.template"
                                                                }
                                                            #line 1139 "PrintTypescript.cpp"
  append(L"EventHandler;");
                                                            #line 788 "PrintTypescript.cpp.template"
                                                              }
                                                              if (memoization)
                                                              {
                                                                int bits = Math::bits(grammar->conflictCount);
                                                            #line 1146 "PrintTypescript.cpp"
  append(L"\n");
  append(L"  private memo: Memoizer;");
                                                            #line 793 "PrintTypescript.cpp.template"
                                                                if (grammar->noThrow)
                                                                {
                                                            #line 1152 "PrintTypescript.cpp"
  append(L"\n");
  append(L"  private viable: boolean;");
                                                            #line 796 "PrintTypescript.cpp.template"
                                                                }
                                                            #line 1157 "PrintTypescript.cpp"
  append(L"\n");
  append(L"\n");
  append(L"  private memoize(i: number, e: number, v: number)\n");
  append(L"  {\n");
  append(L"    ");
                                                            #line 801 "PrintTypescript.cpp.template"
                                                                print(thiz());
                                                            #line 1165 "PrintTypescript.cpp"
  append(L"memo[(e << ");
                                                            #line 802 "PrintTypescript.cpp.template"
                                                                print(format.toString<wchar_t>(bits));
                                                            #line 1169 "PrintTypescript.cpp"
  append(L") + i] = v;\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  private memoized(i: number, e: number): number\n");
  append(L"  {\n");
  append(L"    var v = ");
                                                            #line 808 "PrintTypescript.cpp.template"
                                                                print(thiz());
                                                            #line 1178 "PrintTypescript.cpp"
  append(L"memo[(e << ");
                                                            #line 809 "PrintTypescript.cpp.template"
                                                                print(format.toString<wchar_t>(bits));
                                                            #line 1182 "PrintTypescript.cpp"
  append(L") + i];\n");
  append(L"    return typeof v != \"undefined\" ? v : 0;\n");
  append(L"  }");
                                                            #line 812 "PrintTypescript.cpp.template"
                                                              }
                                                            #line 1188 "PrintTypescript.cpp"
  append(L"\n");
                                                            #line 814 "PrintTypescript.cpp.template"
                                                            }

                                                            void PrintTypescript::printPlatformSpecific()
                                                            {
                                                            #line 1195 "PrintTypescript.cpp"
  append(L"\n");
  append(L"  var command = \"node\";\n");
  append(L"  var log = function(string) {process.stdout.write(string);};\n");
  append(L"  var fs = require('fs');\n");
  append(L"  var readTextFile = fs.readFileSync;");
                                                            #line 822 "PrintTypescript.cpp.template"
                                                              if (performanceTest)
                                                              {
                                                            #line 1204 "PrintTypescript.cpp"
  append(L"\n");
  append(L"  var readDir = fs.readdirSync;\n");
  append(L"  var isDirectory = function(filename) {return fs.statSync(filename).isDirectory();};");
                                                            #line 827 "PrintTypescript.cpp.template"
                                                              }
                                                            #line 1210 "PrintTypescript.cpp"
  append(L"\n");
                                                            #line 829 "PrintTypescript.cpp.template"
                                                            }

                                                            void PrintTypescript::printFileProcessor()
                                                            {
                                                              if (tree)
                                                              {
                                                            #line 1219 "PrintTypescript.cpp"
  append(L"\n");
  append(L"class ContentCounter implements ");
                                                            #line 837 "PrintTypescript.cpp.template"
                                                                print(className.c_str());
                                                            #line 1224 "PrintTypescript.cpp"
  append(L".ParsingEventHandler\n");
  append(L"{\n");
  append(L"  private length = 0;\n");
  append(L"\n");
  append(L"  getLength() {return this.length;}\n");
  append(L"  reset(s: string) {this.length = 0}\n");
  append(L"  startNonterminal(name: string, begin: number) {}\n");
  append(L"  endNonterminal(name: string, end: number) {}\n");
  append(L"  terminal(name: string, begin: number, end: number) {this.length += end - begin;}\n");
  append(L"  whitespace(begin: number, end: number) {this.length += end - begin;}\n");
  append(L"}\n");
                                                            #line 849 "PrintTypescript.cpp.template"
                                                              }
                                                            #line 1238 "PrintTypescript.cpp"
  append(L"\n");
  append(L"class ParseJob\n");
  append(L"{\n");
  append(L"  name: string;\n");
  append(L"  input: string;");
                                                            #line 854 "PrintTypescript.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 1247 "PrintTypescript.cpp"
  append(L"\n");
  append(L"  contentCounter: ContentCounter;");
                                                            #line 857 "PrintTypescript.cpp.template"
                                                                if (isLrParser)
                                                                {
                                                            #line 1253 "PrintTypescript.cpp"
  append(L"\n");
  append(L"  parseTreeBuilder: ");
                                                            #line 860 "PrintTypescript.cpp.template"
                                                                  print(className.c_str());
                                                            #line 1258 "PrintTypescript.cpp"
  append(L".ParseTreeBuilder;");
                                                            #line 861 "PrintTypescript.cpp.template"
                                                                }
                                                              }
                                                            #line 1263 "PrintTypescript.cpp"
  append(L"\n");
  append(L"  parser: ");
                                                            #line 864 "PrintTypescript.cpp.template"
                                                              print(className.c_str());
                                                            #line 1268 "PrintTypescript.cpp"
  append(L".Parser;\n");
  append(L"\n");
  append(L"  constructor(s: string, i: string)\n");
  append(L"  {\n");
  append(L"    this.name = s;\n");
  append(L"    this.input = i;");
                                                            #line 870 "PrintTypescript.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 1278 "PrintTypescript.cpp"
  append(L"\n");
  append(L"    this.contentCounter = new ContentCounter();");
                                                            #line 873 "PrintTypescript.cpp.template"
                                                                if (isLrParser)
                                                                {
                                                            #line 1284 "PrintTypescript.cpp"
  append(L"\n");
  append(L"    this.parseTreeBuilder = new ");
                                                            #line 876 "PrintTypescript.cpp.template"
                                                                  print(className.c_str());
                                                            #line 1289 "PrintTypescript.cpp"
  append(L".ParseTreeBuilder();");
                                                            #line 877 "PrintTypescript.cpp.template"
                                                                }
                                                              }
                                                            #line 1294 "PrintTypescript.cpp"
  append(L"\n");
  append(L"    this.parser = new ");
                                                            #line 880 "PrintTypescript.cpp.template"
                                                              print(className.c_str());
                                                            #line 1299 "PrintTypescript.cpp"
  append(L".Parser(i");
                                                            #line 881 "PrintTypescript.cpp.template"
                                                              if (noLexer)
                                                              {
                                                            #line 1304 "PrintTypescript.cpp"
  append(L", null");
                                                            #line 883 "PrintTypescript.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                                if (isLrParser)
                                                                {
                                                            #line 1312 "PrintTypescript.cpp"
  append(L", this.parseTreeBuilder");
                                                            #line 888 "PrintTypescript.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1318 "PrintTypescript.cpp"
  append(L", this.contentCounter");
                                                            #line 891 "PrintTypescript.cpp.template"
                                                                }
                                                              }
                                                            #line 1323 "PrintTypescript.cpp"
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
  append(L"    if (! quiet) process.stdout.write(\"loading \" + f + \"\\n\");\n");
  append(L"    parsers[parsers.length] = new ParseJob(f, input);\n");
  append(L"  }\n");
  append(L"}\n");
  append(L"\n");
  append(L"// performance test main program for use with node.js\n");
  append(L"\n");
  append(L"var fs = require('fs');\n");
  append(L"\n");
  append(L"var quiet = false;\n");
  append(L"var parsed = 0;\n");
  append(L"var errorCount = 0;\n");
  append(L"var parsers: ParseJob[] = [];\n");
  append(L"\n");
  append(L"if (process.argv.length < 3)\n");
  append(L"{\n");
  append(L"  process.stderr.write(\"Usage: node ");
                                                            #line 929 "PrintTypescript.cpp.template"
                                                              print(className.c_str());
                                                            #line 1363 "PrintTypescript.cpp"
  append(L".js [-q] [-r N] [-t N] ENDING...\\n\");\n");
  append(L"  process.stderr.write(\"\\n\");\n");
  append(L"  process.stderr.write(\"  parse all files that have names ending with ENDING, in current dir and below,\\n\");\n");
  append(L"  process.stderr.write(\"  and display performance summary.\\n\");\n");
  append(L"  process.stderr.write(\"\\n\");\n");
  append(L"  process.stderr.write(\"  -q     do not show file names\\n\");\n");
  append(L"  process.stderr.write(\"  -r N   repeat N times\\n\");\n");
  append(L"  process.stderr.write(\"  -t N   repeat until N seconds have elapsed\\n\");\n");
  append(L"}\n");
  append(L"else\n");
  append(L"{\n");
  append(L"  var repeat = 1;\n");
  append(L"  var timeout = 0;\n");
  append(L"  var i = 1;\n");
  append(L"  while (++i < process.argv.length)\n");
  append(L"  {\n");
  append(L"    if (process.argv[i] == \"-q\")\n");
  append(L"    {\n");
  append(L"      quiet = true;\n");
  append(L"    }\n");
  append(L"    else if (process.argv[i] == \"-r\")\n");
  append(L"    {\n");
  append(L"      repeat = parseInt(process.argv[++i]);\n");
  append(L"      timeout = 0;\n");
  append(L"    }\n");
  append(L"    else if (process.argv[i] == \"-t\")\n");
  append(L"    {\n");
  append(L"      repeat = 0;\n");
  append(L"      timeout = 1000 * parseInt(process.argv[++i]);\n");
  append(L"    }\n");
  append(L"    else if (process.argv[i].substring(0, 1) !== \"-\")\n");
  append(L"    {\n");
  append(L"      break;\n");
  append(L"    }\n");
  append(L"    else\n");
  append(L"    {\n");
  append(L"      throw \"invalid option: \" + process.argv[i];\n");
  append(L"    }\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  var start = Date.now();\n");
  append(L"\n");
  append(L"  for (; i < process.argv.length; ++i)\n");
  append(L"  {\n");
  append(L"    findFiles(\".\", process.argv[i], parsers, quiet);\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  if (parsers.length != 0)\n");
  append(L"  {\n");
  append(L"    var msec = Date.now() - start;\n");
  append(L"\n");
  append(L"    if (! quiet) process.stdout.write(\"\\n\");\n");
  append(L"    process.stdout.write(\"loaded \" + parsers.length + \" file\" +\n");
  append(L"        (parsers.length == 1 ? \"\" : \"s\") + \" in \" +\n");
  append(L"        msec + \" msec\\n\");\n");
  append(L"    if (! quiet) process.stdout.write(\"\\n\");\n");
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
  append(L"            if (! quiet) process.stdout.write(\"parsing \" + job.name);\n");
  append(L"            job.parser.reset(0, 0, 0);\n");
  append(L"            job.parser.");
                                                            #line 1002 "PrintTypescript.cpp.template"
                                                              print(methodPrefixParse);
                                                              print(Format::acceptableName<WString>(grammar->startSymbol()->name).c_str());
                                                            #line 1440 "PrintTypescript.cpp"
  append(L"();\n");
  append(L"            if (! quiet) process.stdout.write(\"\\n\");");
                                                            #line 1005 "PrintTypescript.cpp.template"
                                                              if (tree)
                                                              {
                                                                if (isLrParser)
                                                                {
                                                            #line 1448 "PrintTypescript.cpp"
  append(L"\n");
  append(L"            job.parseTreeBuilder.serialize(job.contentCounter);");
                                                            #line 1011 "PrintTypescript.cpp.template"
                                                                }
                                                            #line 1453 "PrintTypescript.cpp"
  append(L"\n");
  append(L"            if (job.contentCounter.getLength() != job.input.length)\n");
  append(L"            {\n");
  append(L"              throw \"content counter saw \" + job.contentCounter.getLength() +\n");
  append(L"                    \", but input length is \" + job.input.length;\n");
  append(L"            }");
                                                            #line 1017 "PrintTypescript.cpp.template"
                                                              }
                                                            #line 1462 "PrintTypescript.cpp"
  append(L"\n");
  append(L"            parsed += job.input.length;\n");
  append(L"          }\n");
  append(L"          catch (pe)\n");
  append(L"          {\n");
  append(L"            if (pe instanceof ");
                                                            #line 1023 "PrintTypescript.cpp.template"
                                                              print(className.c_str());
                                                            #line 1471 "PrintTypescript.cpp"
  append(L".ParseException)\n");
  append(L"            {\n");
  append(L"              ++errorCount;\n");
  append(L"              process.stdout.write((quiet ? (\"parsing \" + job.name) : \"\") +\n");
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
  append(L"    if (! quiet) process.stdout.write(\"\\n\");\n");
  append(L"    process.stdout.write(\"parsed \" + parsed + \" byte\" + (parsed == 1 ? \"\" : \"s\") +\n");
  append(L"        \" in \" + msec + \" msec\" + perSec + \"\\n\");\n");
  append(L"    process.stdout.write(errorCount + \" error\" + (errorCount == 1 ? \"\" : \"s\") + \"\\n\");\n");
  append(L"  }\n");
  append(L"}\n");
                                                            #line 1054 "PrintTypescript.cpp.template"
                                                            }

                                                            void PrintTypescript::printReadMethod()
                                                            {
                                                            #line 1507 "PrintTypescript.cpp"
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
                                                            #line 1073 "PrintTypescript.cpp.template"
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
                                                            #line 1542 "PrintTypescript.cpp"
  append(L"}\n");
                                                            #line 1090 "PrintTypescript.cpp.template"
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
                                                            #line 1556 "PrintTypescript.cpp"
  append(L"}\n");
                                                            #line 1102 "PrintTypescript.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                            #line 1562 "PrintTypescript.cpp"
  append(L"\n");
  append(L"  export class TopDownTreeBuilder implements ParsingEventHandler\n");
  append(L"  {\n");
  append(L"    private input: string = null;\n");
  append(L"    private stack: Nonterminal[] = null;\n");
  append(L"\n");
  append(L"    public reset(input: string): void\n");
  append(L"    {\n");
  append(L"      this.input = input;\n");
  append(L"      this.stack = [];\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    public startNonterminal(name: string, begin: number): void\n");
  append(L"    {\n");
  append(L"      var nonterminal = new Nonterminal(name, begin, begin, []);\n");
  append(L"      if (this.stack.length > 0) this.addChild(nonterminal);\n");
  append(L"      this.stack.push(nonterminal);\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    public endNonterminal(name: string, end: number): void\n");
  append(L"    {\n");
  append(L"      this.stack[this.stack.length - 1].end = end;\n");
  append(L"      if (this.stack.length > 1) this.stack.pop();\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    public terminal(name: string, begin: number, end: number): void\n");
  append(L"    {\n");
  append(L"      this.addChild(new Terminal(name, begin, end));\n");
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
  append(L"    public name: string;\n");
  append(L"    public begin: number;\n");
  append(L"    public end: number;\n");
  append(L"\n");
  append(L"    constructor(name: string, begin: number, end: number)\n");
  append(L"    {\n");
  append(L"      this.name = name;\n");
  append(L"      this.begin = begin;\n");
  append(L"      this.end = end;\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    public abstract send(e: ParsingEventHandler): void;\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  export class Terminal extends Symbol\n");
  append(L"  {\n");
  append(L"    constructor(name: string, begin: number, end: number)\n");
  append(L"    {\n");
  append(L"      super(name, begin, end);\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    public send(e: ParsingEventHandler): void\n");
  append(L"    {\n");
  append(L"      e.terminal(this.name, this.begin, this.end);\n");
  append(L"    }\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  export class Nonterminal extends Symbol\n");
  append(L"  {\n");
  append(L"    public children: Symbol[];\n");
  append(L"\n");
  append(L"    constructor(name: string, begin: number, end: number, children: Symbol[])\n");
  append(L"    {\n");
  append(L"      super(name, begin, end);\n");
  append(L"      this.children = children;\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    public send(e: ParsingEventHandler): void\n");
  append(L"    {\n");
  append(L"      e.startNonterminal(this.name, this.begin);\n");
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
  append(L"      e.endNonterminal(this.name, this.end);\n");
  append(L"    }\n");
  append(L"  }\n");
                                                            #line 1208 "PrintTypescript.cpp.template"
                                                                if (isLrParser)
                                                                {
                                                            #line 1669 "PrintTypescript.cpp"
  append(L"\n");
  append(L"  export class ParseTreeBuilder implements BottomUpEventHandler\n");
  append(L"  {\n");
  append(L"    private input: string = null;\n");
  append(L"    private stack: Symbol[] = [];\n");
  append(L"    private top: number = -1;\n");
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
  append(L"    public nonterminal(name: string, begin: number, end: number, count: number): void\n");
  append(L"    {");
                                                            #line 1227 "PrintTypescript.cpp.template"
                                                                  if (useGlr)
                                                                  {
                                                            #line 1691 "PrintTypescript.cpp"
  append(L"\n");
  append(L"      if (count > this.top + 1)\n");
  append(L"      {\n");
  append(L"        var content = this.pop(this.top + 1);\n");
  append(L"        this.nonterminal(\"UNAMBIGUOUS\", begin, content.length == 0 ? end : content[0].begin, 0);\n");
  append(L"        for (let symbol of content)\n");
  append(L"        {\n");
  append(L"          this.push(symbol);\n");
  append(L"        }\n");
  append(L"        count = this.top + 1;\n");
  append(L"      }");
                                                            #line 1239 "PrintTypescript.cpp.template"
                                                                  }
                                                            #line 1705 "PrintTypescript.cpp"
  append(L"\n");
  append(L"      this.push(new Nonterminal(name, begin, end, this.pop(count)));\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    public terminal(name: string, begin: number, end: number): void\n");
  append(L"    {\n");
  append(L"      this.push(new Terminal(name, begin, end));\n");
  append(L"    }\n");
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
                                                            #line 1270 "PrintTypescript.cpp.template"
                                                                }
                                                              }
                                                              if (! visitEpilog())
                                                              {
                                                            #line 1740 "PrintTypescript.cpp"
  append(L"}\n");
                                                            #line 1275 "PrintTypescript.cpp.template"
                                                              }

                                                              if (main)
                                                              {
                                                                if (tree)
                                                                {
                                                            #line 1749 "PrintTypescript.cpp"
  append(L"\n");
  append(L"class XmlSerializer implements ");
                                                            #line 1282 "PrintTypescript.cpp.template"
                                                                  print(className.c_str());
                                                            #line 1754 "PrintTypescript.cpp"
  append(L".ParsingEventHandler\n");
  append(L"{\n");
  append(L"  private input: string = null;\n");
  append(L"  private delayedTag: string = null;\n");
  append(L"  private indent: boolean;\n");
  append(L"  private hasChildElement = false;\n");
  append(L"  private depth = 0;\n");
  append(L"\n");
  append(L"  constructor(indent: boolean)\n");
  append(L"  {\n");
  append(L"    this.indent = indent;\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  reset(source: string)\n");
  append(L"  {\n");
  append(L"    process.stdout.write(\"<?xml version=\\\"1.0\\\" encoding=\\\"UTF-8\\\"?\" + \">\");\n");
  append(L"    this.input = source;\n");
  append(L"    this.hasChildElement = false;\n");
  append(L"    this.depth = 0;\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  startNonterminal(tag: string, begin: number)\n");
  append(L"  {\n");
  append(L"    if (this.delayedTag != null)\n");
  append(L"    {\n");
  append(L"      process.stdout.write(\"<\");\n");
  append(L"      process.stdout.write(this.delayedTag);\n");
  append(L"      process.stdout.write(\">\");\n");
  append(L"    }\n");
  append(L"    this.delayedTag = tag;\n");
  append(L"    if (this.indent)\n");
  append(L"    {\n");
  append(L"      process.stdout.write(\"\\n\");\n");
  append(L"      for (var i = 0; i < this.depth; ++i)\n");
  append(L"      {\n");
  append(L"        process.stdout.write(\"  \");\n");
  append(L"      }\n");
  append(L"    }\n");
  append(L"    this.hasChildElement = false;\n");
  append(L"    ++this.depth;\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  endNonterminal(tag: string, end: number)\n");
  append(L"  {\n");
  append(L"    --this.depth;\n");
  append(L"    if (this.delayedTag != null)\n");
  append(L"    {\n");
  append(L"      this.delayedTag = null;\n");
  append(L"      process.stdout.write(\"<\");\n");
  append(L"      process.stdout.write(tag);\n");
  append(L"      process.stdout.write(\"/>\");\n");
  append(L"    }\n");
  append(L"    else\n");
  append(L"    {\n");
  append(L"      if (this.indent)\n");
  append(L"      {\n");
  append(L"        if (this.hasChildElement)\n");
  append(L"        {\n");
  append(L"          process.stdout.write(\"\\n\");\n");
  append(L"          for (var i = 0; i < this.depth; ++i)\n");
  append(L"          {\n");
  append(L"            process.stdout.write(\"  \");\n");
  append(L"          }\n");
  append(L"        }\n");
  append(L"      }\n");
  append(L"      process.stdout.write(\"</\");\n");
  append(L"      process.stdout.write(tag);\n");
  append(L"      process.stdout.write(\">\");\n");
  append(L"    }\n");
  append(L"    this.hasChildElement = true;\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  terminal(tag: string, begin: number, end: number)\n");
  append(L"  {\n");
  append(L"    if (tag.charAt(0) == '\\'') tag = \"TOKEN\";\n");
  append(L"    this.startNonterminal(tag, begin);\n");
  append(L"    this.characters(begin, end);\n");
  append(L"    this.endNonterminal(tag, end);\n");
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
  append(L"        process.stdout.write(\"<\");\n");
  append(L"        process.stdout.write(this.delayedTag);\n");
  append(L"        process.stdout.write(\">\");\n");
  append(L"        this.delayedTag = null;\n");
  append(L"      }\n");
  append(L"      process.stdout.write(this.input.substring(begin, end)\n");
  append(L"                   .replace(/&/g, \"&amp;\")\n");
  append(L"                   .replace(/</g, \"&lt;\")\n");
  append(L"                   .replace(/>/g, \"&gt;\"));\n");
  append(L"    }\n");
  append(L"  }\n");
  append(L"}\n");
                                                            #line 1386 "PrintTypescript.cpp.template"
                                                                }
                                                            #line 1860 "PrintTypescript.cpp"
  append(L"\n");
  append(L"// main program for use with node.js\n");
  append(L"\n");
  append(L"var fs = require('fs');\n");
  append(L"\n");
  append(L"if (process.argv.length < 3)\n");
  append(L"{\n");
  append(L"  process.stderr.write(\"Usage: node ");
                                                            #line 1394 "PrintTypescript.cpp.template"
                                                                print(className.c_str());
                                                            #line 1871 "PrintTypescript.cpp"
  append(L".js ");
                                                            #line 1395 "PrintTypescript.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 1876 "PrintTypescript.cpp"
  append(L"[-i] ");
                                                            #line 1397 "PrintTypescript.cpp.template"
                                                                }
                                                            #line 1880 "PrintTypescript.cpp"
  append(L"INPUT...\\n\");\n");
  append(L"  process.stderr.write(\"\\n\");\n");
  append(L"  process.stderr.write(\"  parse INPUT, which is either a filename or literal text enclosed in curly braces\\n\");");
                                                            #line 1401 "PrintTypescript.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 1887 "PrintTypescript.cpp"
  append(L"\n");
  append(L"  process.stderr.write(\"\\n\");\n");
  append(L"  process.stderr.write(\"  Option:\\n\");\n");
  append(L"  process.stderr.write(\"    -i     indented parse tree\\n\");");
                                                            #line 1406 "PrintTypescript.cpp.template"
                                                                }
                                                            #line 1894 "PrintTypescript.cpp"
  append(L"\n");
  append(L"}\n");
  append(L"else\n");
  append(L"{\n");
  append(L"  var indent = false;\n");
  append(L"  for (var i = 2; i < process.argv.length; ++i)\n");
  append(L"  {\n");
  append(L"    var arg = process.argv[i];");
                                                            #line 1415 "PrintTypescript.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 1906 "PrintTypescript.cpp"
  append(L"\n");
  append(L"    if (arg === \"-i\")\n");
  append(L"    {\n");
  append(L"      indent = true;\n");
  append(L"      continue;\n");
  append(L"    }");
                                                            #line 1422 "PrintTypescript.cpp.template"
                                                                }
                                                            #line 1915 "PrintTypescript.cpp"
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
                                                            #line 1435 "PrintTypescript.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 1934 "PrintTypescript.cpp"
  append(L"\n");
  append(L"    var s = new XmlSerializer(indent);");
                                                            #line 1438 "PrintTypescript.cpp.template"
                                                                  if (isLrParser)
                                                                  {
                                                            #line 1940 "PrintTypescript.cpp"
  append(L"\n");
  append(L"    var t = new ");
                                                            #line 1441 "PrintTypescript.cpp.template"
                                                                    print(className.c_str());
                                                            #line 1945 "PrintTypescript.cpp"
  append(L".ParseTreeBuilder();");
                                                            #line 1442 "PrintTypescript.cpp.template"
                                                                  }
                                                                }
                                                            #line 1950 "PrintTypescript.cpp"
  append(L"\n");
  append(L"    var parser = new ");
                                                            #line 1445 "PrintTypescript.cpp.template"
                                                                print(className.c_str());
                                                            #line 1955 "PrintTypescript.cpp"
  append(L".Parser(input");
                                                            #line 1446 "PrintTypescript.cpp.template"
                                                                if (tree)
                                                                {
                                                                  if (isLrParser)
                                                                  {
                                                            #line 1962 "PrintTypescript.cpp"
  append(L", t");
                                                            #line 1450 "PrintTypescript.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 1968 "PrintTypescript.cpp"
  append(L", s");
                                                            #line 1453 "PrintTypescript.cpp.template"
                                                                  }
                                                                }
                                                            #line 1973 "PrintTypescript.cpp"
  append(L");\n");
  append(L"    try\n");
  append(L"    {");
                                                            #line 1457 "PrintTypescript.cpp.template"
                                                                if (trace)
                                                                {
                                                            #line 1980 "PrintTypescript.cpp"
  append(L"\n");
  append(L"      parser.writeTrace(\"<?xml version=\\\"1.0\\\" encoding=\\\"UTF-8\\\"?\" + \">\\n<trace>\\n\");");
                                                            #line 1461 "PrintTypescript.cpp.template"
                                                                }
                                                            #line 1985 "PrintTypescript.cpp"
  append(L"\n");
  append(L"      parser.");
                                                            #line 1463 "PrintTypescript.cpp.template"
                                                                print(methodPrefixParse);
                                                                print(Format::acceptableName<WString>(grammar->startSymbol()->name).c_str());
                                                            #line 1991 "PrintTypescript.cpp"
  append(L"();");
                                                            #line 1465 "PrintTypescript.cpp.template"
                                                                if (trace)
                                                                {
                                                            #line 1996 "PrintTypescript.cpp"
  append(L"\n");
  append(L"      parser.writeTrace(\"</trace>\\n\");\n");
  append(L"      parser.flushTrace();");
                                                            #line 1469 "PrintTypescript.cpp.template"
                                                                }
                                                                if (tree && isLrParser)
                                                                {
                                                            #line 2004 "PrintTypescript.cpp"
  append(L"\n");
  append(L"      t.serialize(s);");
                                                            #line 1473 "PrintTypescript.cpp.template"
                                                                }
                                                            #line 2009 "PrintTypescript.cpp"
  append(L"\n");
  append(L"    }\n");
  append(L"    catch (pe)\n");
  append(L"    {\n");
  append(L"      if (! (pe instanceof ");
                                                            #line 1478 "PrintTypescript.cpp.template"
                                                                print(className.c_str());
                                                            #line 2017 "PrintTypescript.cpp"
  append(L".ParseException))\n");
  append(L"      {\n");
  append(L"        throw pe;\n");
  append(L"      }\n");
  append(L"      else\n");
  append(L"      {");
                                                            #line 1484 "PrintTypescript.cpp.template"
                                                                if (useGlr && tree)
                                                                {
                                                            #line 2027 "PrintTypescript.cpp"
  append(L"\n");
  append(L"        if (pe.isAmbiguousInput())\n");
  append(L"        {\n");
  append(L"          pe.serialize(s);\n");
  append(L"          process.stdout.write(\"\\n\");\n");
  append(L"        }");
                                                            #line 1491 "PrintTypescript.cpp.template"
                                                                }
                                                            #line 2036 "PrintTypescript.cpp"
  append(L"\n");
  append(L"        throw parser.getErrorMessage(pe);\n");
  append(L"      }\n");
  append(L"    }\n");
  append(L"  }\n");
  append(L"}\n");
                                                            #line 1499 "PrintTypescript.cpp.template"
                                                              }
                                                              if (performanceTest)
                                                              {
                                                                printFileProcessor();
                                                              }
                                                            }

// End
