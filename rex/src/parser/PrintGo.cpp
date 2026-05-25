// This file was generated on Thu Jul 3, 2025 23:15 (UTC+02) by REx v6.2-SNAPSHOT which is Copyright (c) 1979-2025 by Gunther Rademacher <grd@gmx.net>
// REx command line: PrintGo.cpp.template
                                                            #line 1 "PrintGo.cpp.template"
                                                            #include "../common/Memory.hpp"

                                                            #include "PrintGo.hpp"
                                                            #include "ItemSet.hpp"
                                                            #include "../common/CompressedMap.hpp"

                                                            void PrintGo::openClass()
                                                            {
                                                              if (hasProlog)
                                                              {
                                                            #line 15 "PrintGo.cpp"
  append(L"\n");
                                                            #line 12 "PrintGo.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 21 "PrintGo.cpp"
  append(L"\n");
  append(L"package ");
                                                            #line 16 "PrintGo.cpp.template"
                                                                if (packageName.empty())
                                                                {
                                                            #line 27 "PrintGo.cpp"
  append(L"main");
                                                            #line 18 "PrintGo.cpp.template"
                                                                }
                                                                else
                                                                {
                                                                  print(packageName.c_str());
                                                                }
                                                            #line 35 "PrintGo.cpp"
  append(L"\n");
  append(L"\n");
  append(L"import (\n");
  append(L"  \"strconv\"\n");
  append(L"  \"unicode/utf8\"");
                                                            #line 28 "PrintGo.cpp.template"
                                                                if (main || performanceTest)
                                                                {
                                                            #line 44 "PrintGo.cpp"
  append(L"\n");
  append(L"  \"io/ioutil\"\n");
  append(L"  \"fmt\"");
                                                            #line 32 "PrintGo.cpp.template"
                                                                }
                                                                if (main || performanceTest || trace)
                                                                {
                                                            #line 52 "PrintGo.cpp"
  append(L"\n");
  append(L"  \"os\"\n");
  append(L"  \"strings\"");
                                                            #line 37 "PrintGo.cpp.template"
                                                                }
                                                                if (performanceTest)
                                                                {
                                                            #line 60 "PrintGo.cpp"
  append(L"\n");
  append(L"  \"path/filepath\"\n");
  append(L"  \"time\"");
                                                            #line 42 "PrintGo.cpp.template"
                                                                }
                                                                if (useGlr)
                                                                {
                                                            #line 68 "PrintGo.cpp"
  append(L"\n");
  append(L"  \"container/heap\"");
                                                            #line 46 "PrintGo.cpp.template"
                                                                }
                                                            #line 73 "PrintGo.cpp"
  append(L"\n");
  append(L")\n");
                                                            #line 49 "PrintGo.cpp.template"
                                                              }
                                                              if (main)
                                                              {
                                                            #line 80 "PrintGo.cpp"
  append(L"\n");
  append(L"func ");
                                                            #line 53 "PrintGo.cpp.template"
                                                                if (packageName.empty() || packageName == L"main")
                                                                {
                                                            #line 86 "PrintGo.cpp"
  append(L"m");
                                                            #line 55 "PrintGo.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 92 "PrintGo.cpp"
  append(L"M");
                                                            #line 58 "PrintGo.cpp.template"
                                                                }
                                                            #line 96 "PrintGo.cpp"
  append(L"ain() {\n");
  append(L"  if len(os.Args) < 2 {\n");
  append(L"    os.Stderr.WriteString(\"Usage: ");
                                                            #line 61 "PrintGo.cpp.template"
                                                                print(className.c_str());
                                                                if (tree)
                                                                {
                                                            #line 104 "PrintGo.cpp"
  append(L" [-i]");
                                                            #line 64 "PrintGo.cpp.template"
                                                                }
                                                            #line 108 "PrintGo.cpp"
  append(L" INPUT...\\n\")\n");
  append(L"    os.Stderr.WriteString(\"\\n\")\n");
  append(L"    os.Stderr.WriteString(\"  parse INPUT, which is either a filename or literal text enclosed in curly braces\\n\")");
                                                            #line 68 "PrintGo.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 115 "PrintGo.cpp"
  append(L"\n");
  append(L"    os.Stderr.WriteString(\"\\n\")\n");
  append(L"    os.Stderr.WriteString(\"  Option:\\n\")\n");
  append(L"    os.Stderr.WriteString(\"    -i     indented parse tree\\n\")");
                                                            #line 73 "PrintGo.cpp.template"
                                                                }
                                                            #line 122 "PrintGo.cpp"
  append(L"\n");
  append(L"  } else {");
                                                            #line 75 "PrintGo.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 128 "PrintGo.cpp"
  append(L"\n");
  append(L"    indent := false");
                                                            #line 78 "PrintGo.cpp.template"
                                                                }
                                                            #line 133 "PrintGo.cpp"
  append(L"\n");
  append(L"    for i := 1; i < len(os.Args); i++ {\n");
  append(L"      arg := os.Args[i]");
                                                            #line 81 "PrintGo.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 140 "PrintGo.cpp"
  append(L"\n");
  append(L"      if arg == \"-i\" {\n");
  append(L"        indent = true\n");
  append(L"        continue\n");
  append(L"      }\n");
  append(L"      s := new(XmlSerializer)\n");
  append(L"      s.indent = indent");
                                                            #line 89 "PrintGo.cpp.template"
                                                                  if (isLrParser)
                                                                  {
                                                            #line 151 "PrintGo.cpp"
  append(L"\n");
  append(L"      b := &ParseTreeBuilder{}");
                                                            #line 92 "PrintGo.cpp.template"
                                                                }
                                                                }
                                                            #line 157 "PrintGo.cpp"
  append(L"\n");
  append(L"      input := read(arg)\n");
  append(L"      parser := NewParser(input");
                                                            #line 96 "PrintGo.cpp.template"
                                                                if (noLexer)
                                                                {
                                                            #line 164 "PrintGo.cpp"
  append(L", new ");
                                                            #line 98 "PrintGo.cpp.template"
                                                                  print(className.c_str());
                                                            #line 168 "PrintGo.cpp"
  append(L"Lexer()");
                                                            #line 99 "PrintGo.cpp.template"
                                                                }
                                                                if (tree)
                                                                {
                                                            #line 174 "PrintGo.cpp"
  append(L", ");
                                                            #line 102 "PrintGo.cpp.template"
                                                                if (isLrParser)
                                                                  {
                                                            #line 179 "PrintGo.cpp"
  append(L"b");
                                                            #line 104 "PrintGo.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 185 "PrintGo.cpp"
  append(L"s");
                                                            #line 107 "PrintGo.cpp.template"
                                                                  }
                                                                }
                                                            #line 190 "PrintGo.cpp"
  append(L")");
                                                            #line 109 "PrintGo.cpp.template"
                                                                if (trace)
                                                                {
                                                            #line 195 "PrintGo.cpp"
  append(L"\n");
  append(L"      writeTrace(\"<?xml version=\\\"1.0\\\" encoding=\\\"UTF-8\\\"?\" + \">\\n<trace>\\n\")");
                                                            #line 113 "PrintGo.cpp.template"
                                                                }
                                                            #line 200 "PrintGo.cpp"
  append(L"\n");
  append(L"      pe := parser.");
                                                            #line 115 "PrintGo.cpp.template"
                                                                print(visibilityMethodPrefix());
                                                                print(Format::acceptableName<WString>(grammar->startSymbol()->name).c_str());
                                                            #line 206 "PrintGo.cpp"
  append(L"()");
                                                            #line 117 "PrintGo.cpp.template"
                                                                if (trace)
                                                                {
                                                            #line 211 "PrintGo.cpp"
  append(L"\n");
  append(L"      writeTrace(\"</trace>\\n\")");
                                                            #line 120 "PrintGo.cpp.template"
                                                                }
                                                            #line 216 "PrintGo.cpp"
  append(L"\n");
  append(L"      if pe != nil {");
                                                            #line 122 "PrintGo.cpp.template"
                                                                if (useGlr && tree)
                                                                {
                                                            #line 222 "PrintGo.cpp"
  append(L"\n");
  append(L"        if pe.IsAmbiguousInput() {\n");
  append(L"          pe.Serialize(s)\n");
  append(L"          fmt.Println()\n");
  append(L"        }");
                                                            #line 128 "PrintGo.cpp.template"
                                                                }
                                                            #line 230 "PrintGo.cpp"
  append(L"\n");
  append(L"        panic(fmt.Sprintf(\"ParseError while processing %s:\\n%s\\n\", arg, parser.GetErrorMessage(*pe)))\n");
  append(L"      }");
                                                            #line 131 "PrintGo.cpp.template"
                                                                if (tree && isLrParser)
                                                                {
                                                            #line 237 "PrintGo.cpp"
  append(L" else {\n");
  append(L"        b.Serialize(s)\n");
  append(L"      }");
                                                            #line 135 "PrintGo.cpp.template"
                                                                }
                                                            #line 243 "PrintGo.cpp"
  append(L"\n");
  append(L"    }\n");
  append(L"  }\n");
  append(L"}\n");
                                                            #line 140 "PrintGo.cpp.template"
                                                              }
                                                              if (interfaceName.empty())
                                                              {
                                                                printParseException();
                                                                printEventHandlerImplementation();
                                                              }
                                                              if (performanceTest)
                                                              {
                                                                printFileProcessor();
                                                              }
                                                              if (main || performanceTest)
                                                              {
                                                                printReadMethod();
                                                              }
                                                              if (! hasProlog)
                                                              {
                                                                WString args(L"input string");
                                                                if (noLexer) args += L", lexer Lexer";
                                                                if (tree) args += isLrParser ? L", t BottomUpEventHandler" : L", t EventHandler";
                                                            #line 268 "PrintGo.cpp"
  append(L"\n");
  append(L"func NewParser(");
                                                            #line 160 "PrintGo.cpp.template"
                                                                print(args.c_str());
                                                            #line 273 "PrintGo.cpp"
  append(L") *");
                                                            #line 161 "PrintGo.cpp.template"
                                                                print(className.c_str());
                                                            #line 277 "PrintGo.cpp"
  append(L" {\n");
  append(L"  parser := new(");
                                                            #line 163 "PrintGo.cpp.template"
                                                                print(className.c_str());
                                                            #line 282 "PrintGo.cpp"
  append(L")\n");
  append(L"  parser.Initialize(input");
                                                            #line 165 "PrintGo.cpp.template"
                                                                if (noLexer)
                                                                {
                                                            #line 288 "PrintGo.cpp"
  append(L", lexer");
                                                            #line 167 "PrintGo.cpp.template"
                                                                }
                                                                if (tree)
                                                                {
                                                            #line 294 "PrintGo.cpp"
  append(L", t");
                                                            #line 170 "PrintGo.cpp.template"
                                                                }
                                                            #line 298 "PrintGo.cpp"
  append(L")\n");
  append(L"  return parser\n");
  append(L"}\n");
                                                            #line 174 "PrintGo.cpp.template"
                                                              }
                                                            }

                                                            void PrintGo::openStackNode()
                                                            {
                                                            #line 308 "PrintGo.cpp"
  append(L"\n");
  append(L"type StackNode struct {\n");
  append(L"  state int");
                                                            #line 181 "PrintGo.cpp.template"
                                                              if (grammar->states->hasLookback)
                                                              {
                                                            #line 315 "PrintGo.cpp"
  append(L"\n");
  append(L"  code int");
                                                            #line 184 "PrintGo.cpp.template"
                                                              }
                                                              if (tree || useGlr)
                                                              {
                                                            #line 322 "PrintGo.cpp"
  append(L"\n");
  append(L"  pos int");
                                                            #line 188 "PrintGo.cpp.template"
                                                              }
                                                            #line 327 "PrintGo.cpp"
  append(L"\n");
  append(L"  link *StackNode\n");
  append(L"}\n");
  append(L"\n");
  append(L"func (this *StackNode) equals(rhs *StackNode) bool {\n");
  append(L"  lhs := this\n");
  append(L"  for lhs != nil && rhs != nil {\n");
  append(L"    if lhs == rhs {\n");
  append(L"      return true\n");
  append(L"    }\n");
  append(L"    if lhs.state != rhs.state {\n");
  append(L"      return false\n");
  append(L"    }");
                                                            #line 201 "PrintGo.cpp.template"
                                                              if (grammar->states->hasLookback)
                                                              {
                                                            #line 344 "PrintGo.cpp"
  append(L"\n");
  append(L"    if lhs.code != rhs.code {\n");
  append(L"      return false\n");
  append(L"    }");
                                                            #line 206 "PrintGo.cpp.template"
                                                              }
                                                              if (tree || useGlr)
                                                              {
                                                            #line 353 "PrintGo.cpp"
  append(L"\n");
  append(L"    if lhs.pos != rhs.pos {\n");
  append(L"      return false\n");
  append(L"    }");
                                                            #line 212 "PrintGo.cpp.template"
                                                              }
                                                            #line 360 "PrintGo.cpp"
  append(L"\n");
  append(L"    lhs = lhs.link\n");
  append(L"    rhs = rhs.link\n");
  append(L"  }\n");
  append(L"  return lhs == rhs\n");
  append(L"}\n");
                                                            #line 219 "PrintGo.cpp.template"
                                                              beginPublic();
                                                            }

                                                            void PrintGo::closeStackNode()
                                                            {
                                                              beginNonpublic();
                                                              if (hasCustomCode)
                                                              {
                                                            #line 376 "PrintGo.cpp"
  append(L"\n");
  append(L"type DeferredCode struct {\n");
  append(L"  link *DeferredCode\n");
  append(L"  codeId int\n");
  append(L"  b0 int\n");
  append(L"  e0 int\n");
  append(L"}\n");
                                                            #line 234 "PrintGo.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                            #line 388 "PrintGo.cpp"
  append(L"\n");
  append(L"type DeferredEvent interface {\n");
  append(L"  getLink() DeferredEvent\n");
  append(L"  setLink(d DeferredEvent)\n");
  append(L"  getName() string\n");
  append(L"  setName(s string)\n");
  append(L"  getBegin() int\n");
  append(L"  setBegin(i int)\n");
  append(L"  getEnd() int\n");
  append(L"  setEnd(i int)\n");
  append(L"  execute(eventHandler BottomUpEventHandler)\n");
  append(L"}\n");
  append(L"\n");
  append(L"type AbstractDeferredEvent struct {\n");
  append(L"  link DeferredEvent\n");
  append(L"  name string\n");
  append(L"  begin int\n");
  append(L"  end int\n");
  append(L"}\n");
  append(L"\n");
  append(L"func (this *AbstractDeferredEvent) getLink() DeferredEvent {\n");
  append(L"  d, ok := this.link.(DeferredEvent)\n");
  append(L"  if ok {\n");
  append(L"    return d\n");
  append(L"  } else {\n");
  append(L"    return nil\n");
  append(L"  }\n");
  append(L"}\n");
  append(L"\n");
  append(L"func (this *AbstractDeferredEvent) setLink(d DeferredEvent) {this.link = d}\n");
  append(L"func (this *AbstractDeferredEvent) getName() string {return this.name}\n");
  append(L"func (this *AbstractDeferredEvent) setName(s string) {this.name = s}\n");
  append(L"func (this *AbstractDeferredEvent) getBegin() int {return this.begin}\n");
  append(L"func (this *AbstractDeferredEvent) setBegin(i int) {this.begin = i}\n");
  append(L"func (this *AbstractDeferredEvent) getEnd() int {return this.end}\n");
  append(L"func (this *AbstractDeferredEvent) setEnd(i int) {this.end = i}\n");
  append(L"\n");
  append(L"func release(this DeferredEvent, eventHandler BottomUpEventHandler) {\n");
  append(L"  current := this\n");
  append(L"  predecessor := current.getLink()\n");
  append(L"  current.setLink(nil)\n");
  append(L"  for predecessor != nil {\n");
  append(L"    next := predecessor.getLink()\n");
  append(L"    predecessor.setLink(current)\n");
  append(L"    current = predecessor\n");
  append(L"    predecessor = next\n");
  append(L"  }\n");
  append(L"  for {\n");
  append(L"    current.execute(eventHandler)\n");
  append(L"    current = current.getLink()\n");
  append(L"    if current == nil {\n");
  append(L"      break\n");
  append(L"    }\n");
  append(L"  }\n");
  append(L"}\n");
  append(L"\n");
  append(L"func show(this DeferredEvent, eventHandler BottomUpEventHandler) {\n");
  append(L"  var stack []DeferredEvent\n");
  append(L"  for current := this; current != nil; current = current.getLink() {\n");
  append(L"    stack = append(stack, current)\n");
  append(L"  }\n");
  append(L"  for i := len(stack) - 1; i >= 0; i -= 1 {\n");
  append(L"    stack[i].execute(eventHandler)\n");
  append(L"  }\n");
  append(L"}\n");
  append(L"\n");
  append(L"type TerminalEvent struct {\n");
  append(L"  *AbstractDeferredEvent\n");
  append(L"}\n");
  append(L"\n");
  append(L"func (this *TerminalEvent) execute(eventHandler BottomUpEventHandler) {\n");
  append(L"  eventHandler.Terminal(this.name, this.begin, this.end)\n");
  append(L"}\n");
  append(L"\n");
  append(L"func (this *TerminalEvent) toString() string {\n");
  append(L"  return \"terminal(\" + this.name + \", \" + strconv.Itoa(this.begin) + \", \" + strconv.Itoa(this.end) + \")\"\n");
  append(L"}\n");
  append(L"\n");
  append(L"type NonterminalEvent struct {\n");
  append(L"  *AbstractDeferredEvent\n");
  append(L"  count int\n");
  append(L"}\n");
  append(L"\n");
  append(L"func (this *NonterminalEvent) execute(eventHandler BottomUpEventHandler) {\n");
  append(L"  eventHandler.Nonterminal(this.name, this.begin, this.end, this.count)\n");
  append(L"}\n");
  append(L"\n");
  append(L"func (this *NonterminalEvent) toString() string {\n");
  append(L"  return \"nonterminal(\" + this.name + \", \" + strconv.Itoa(this.begin) + \", \" + strconv.Itoa(this.end) + \", \" + strconv.Itoa(this.count) + \")\"\n");
  append(L"}\n");
                                                            #line 327 "PrintGo.cpp.template"
                                                              }
                                                            #line 481 "PrintGo.cpp"
  append(L"\n");
  append(L"const (\n");
  append(L"  PARSING = 0\n");
  append(L"  ACCEPTED = 1\n");
  append(L"  ERROR = 2\n");
  append(L")\n");
  append(L"\n");
  append(L"func (this *");
                                                            #line 335 "PrintGo.cpp.template"
                                                              print(className.c_str());
                                                            #line 492 "PrintGo.cpp"
  append(L") parse(target int, initialState int, ");
                                                            #line 336 "PrintGo.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 497 "PrintGo.cpp"
  append(L"eventHandler BottomUpEventHandler, ");
                                                            #line 339 "PrintGo.cpp.template"
                                                              }
                                                            #line 501 "PrintGo.cpp"
  append(L"thread *ParsingThread) *ParsingThread {\n");
  append(L"  threads := thread.open(initialState");
                                                            #line 341 "PrintGo.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 507 "PrintGo.cpp"
  append(L", eventHandler");
                                                            #line 343 "PrintGo.cpp.template"
                                                              }
                                                            #line 511 "PrintGo.cpp"
  append(L", target)\n");
  append(L"  for {\n");
  append(L"    thread = heap.Pop(threads).(*ParsingThread)\n");
  append(L"    if (thread.accepted) {\n");
  append(L"      var other *ParsingThread = nil\n");
  append(L"      for ! threads.isEmpty() {\n");
  append(L"        other = heap.Pop(threads).(*ParsingThread)\n");
  append(L"        if thread.e0 < other.e0 {\n");
  append(L"          thread = other\n");
  append(L"          other = nil\n");
  append(L"        }\n");
  append(L"      }\n");
  append(L"      if other != nil {\n");
  append(L"        this.rejectAmbiguity(thread.stack.pos, thread.e0");
                                                            #line 357 "PrintGo.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 529 "PrintGo.cpp"
  append(L", thread.deferredEvent, other.deferredEvent");
                                                            #line 360 "PrintGo.cpp.template"
                                                              }
                                                            #line 533 "PrintGo.cpp"
  append(L")\n");
  append(L"      }");
                                                            #line 363 "PrintGo.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 539 "PrintGo.cpp"
  append(L"\n");
  append(L"      if thread.deferredEvent != nil {\n");
  append(L"        release(thread.deferredEvent, eventHandler)\n");
  append(L"        thread.deferredEvent = nil\n");
  append(L"      }");
                                                            #line 369 "PrintGo.cpp.template"
                                                              }
                                                              if (hasCustomCode)
                                                              {
                                                            #line 549 "PrintGo.cpp"
  append(L"\n");
  append(L"      thread.ExecuteDeferredCode()");
                                                            #line 373 "PrintGo.cpp.template"
                                                              }
                                                            #line 554 "PrintGo.cpp"
  append(L"\n");
  append(L"      return thread\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    if ! threads.isEmpty() {\n");
  append(L"      if threads.peek().equals(thread) {\n");
  append(L"        this.rejectAmbiguity(thread.stack.pos, thread.e0");
                                                            #line 380 "PrintGo.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 565 "PrintGo.cpp"
  append(L", thread.deferredEvent, threads.peek().deferredEvent");
                                                            #line 383 "PrintGo.cpp.template"
                                                              }
                                                            #line 569 "PrintGo.cpp"
  append(L")\n");
  append(L"      }");
                                                            #line 386 "PrintGo.cpp.template"
                                                              if (tree || hasCustomCode)
                                                              {
                                                            #line 575 "PrintGo.cpp"
  append(L"\n");
  append(L"    } else {");
                                                            #line 389 "PrintGo.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 581 "PrintGo.cpp"
  append(L"\n");
  append(L"      if thread.deferredEvent != nil {\n");
  append(L"        release(thread.deferredEvent, eventHandler)\n");
  append(L"        thread.deferredEvent = nil\n");
  append(L"      }");
                                                            #line 395 "PrintGo.cpp.template"
                                                                }
                                                                if (hasCustomCode)
                                                                {
                                                            #line 591 "PrintGo.cpp"
  append(L"\n");
  append(L"      thread.ExecuteDeferredCode()");
                                                            #line 399 "PrintGo.cpp.template"
                                                                }
                                                              }
                                                            #line 597 "PrintGo.cpp"
  append(L"\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    var status int\n");
  append(L"    for {\n");
  append(L"      status = thread.parse()\n");
  append(L"      if status != PARSING {\n");
  append(L"        break\n");
  append(L"      }\n");
  append(L"      if ! threads.isEmpty() {\n");
  append(L"        break\n");
  append(L"      }\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    if status != ERROR {\n");
  append(L"      heap.Push(threads, thread)\n");
  append(L"    } else if threads.isEmpty() {\n");
  append(L"      panic(&ParseError{thread.b1,\n");
  append(L"                        thread.e1,\n");
  append(L"                        tokenset[thread.state] + 1,\n");
  append(L"                        thread.l1,\n");
  append(L"                        -1,\n");
  append(L"                        false");
                                                            #line 423 "PrintGo.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 624 "PrintGo.cpp"
  append(L",\n");
  append(L"                        nil");
                                                            #line 426 "PrintGo.cpp.template"
                                                              }
                                                            #line 629 "PrintGo.cpp"
  append(L"})\n");
  append(L"    }\n");
  append(L"  }\n");
  append(L"}\n");
  append(L"\n");
  append(L"func (this *");
                                                            #line 432 "PrintGo.cpp.template"
                                                              print(className.c_str());
                                                            #line 638 "PrintGo.cpp"
  append(L") rejectAmbiguity(begin int, end int");
                                                            #line 433 "PrintGo.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 643 "PrintGo.cpp"
  append(L", first DeferredEvent, second DeferredEvent");
                                                            #line 436 "PrintGo.cpp.template"
                                                              }
                                                            #line 647 "PrintGo.cpp"
  append(L") {");
                                                            #line 437 "PrintGo.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 652 "PrintGo.cpp"
  append(L"\n");
  append(L"  treeBuilder := new(ParseTreeBuilder)\n");
  append(L"  treeBuilder.Reset(this.input)\n");
  append(L"  show(second, treeBuilder)\n");
  append(L"  treeBuilder.Nonterminal(\"ALTERNATIVE\", treeBuilder.stack[0].GetBegin(), treeBuilder.stack[treeBuilder.top].GetEnd(), treeBuilder.top + 1)\n");
  append(L"  secondTree := treeBuilder.pop(1)[0]\n");
  append(L"  show(first, treeBuilder)\n");
  append(L"  treeBuilder.Nonterminal(\"ALTERNATIVE\", treeBuilder.stack[0].GetBegin(), treeBuilder.stack[treeBuilder.top].GetEnd(), treeBuilder.top + 1)\n");
  append(L"  treeBuilder.push(secondTree)\n");
  append(L"  treeBuilder.Nonterminal(\"AMBIGUOUS\", treeBuilder.stack[0].GetBegin(), treeBuilder.stack[treeBuilder.top].GetEnd(), 2)");
                                                            #line 449 "PrintGo.cpp.template"
                                                              }
                                                            #line 665 "PrintGo.cpp"
  append(L"\n");
  append(L"  panic(&ParseError{begin, end, 1, -1, -1, true");
                                                            #line 451 "PrintGo.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 671 "PrintGo.cpp"
  append(L", treeBuilder");
                                                            #line 453 "PrintGo.cpp.template"
                                                              }
                                                            #line 675 "PrintGo.cpp"
  append(L"})\n");
  append(L"}\n");
                                                            #line 456 "PrintGo.cpp.template"
                                                            }

                                                            void PrintGo::openThread()
                                                            {
                                                            #line 683 "PrintGo.cpp"
  append(L"\n");
  append(L"type PriorityQueue []*ParsingThread\n");
  append(L"\n");
  append(L"func (this PriorityQueue) Len() int {\n");
  append(L"  return len(this)\n");
  append(L"}\n");
  append(L"\n");
  append(L"func (this PriorityQueue) Less(i, j int) bool {\n");
  append(L"  return this[i].compareTo(this[j]) < 0\n");
  append(L"}\n");
  append(L"\n");
  append(L"func (this PriorityQueue) Swap(i, j int) {\n");
  append(L"  this[i], this[j] = this[j], this[i]\n");
  append(L"}\n");
  append(L"\n");
  append(L"func (this *PriorityQueue) Push(x interface{}) {\n");
  append(L"  thread := x.(*ParsingThread)\n");
  append(L"  *this = append(*this, thread)\n");
  append(L"}\n");
  append(L"\n");
  append(L"func (this *PriorityQueue) Pop() interface{} {\n");
  append(L"  pq := *this\n");
  append(L"  n := len(pq) - 1\n");
  append(L"  thread := pq[n]\n");
  append(L"  pq[n] = nil\n");
  append(L"  *this = pq[0:n]\n");
  append(L"  return thread\n");
  append(L"}\n");
  append(L"\n");
  append(L"func (this *PriorityQueue) isEmpty() bool {\n");
  append(L"  return len(*this) == 0\n");
  append(L"}\n");
  append(L"\n");
  append(L"func (this *PriorityQueue) peek() *ParsingThread {\n");
  append(L"  pq := *this\n");
  append(L"  return pq[len(pq) - 1]\n");
  append(L"}\n");
  append(L"\n");
  append(L"type ParsingThread struct {\n");
  append(L"  parser *");
                                                            #line 499 "PrintGo.cpp.template"
                                                              print(className.c_str());
                                                            #line 726 "PrintGo.cpp"
  append(L"\n");
  append(L"  threads *PriorityQueue\n");
  append(L"  accepted bool\n");
  append(L"  stack *StackNode\n");
  append(L"  state int\n");
  append(L"  action int\n");
  append(L"  target int");
                                                            #line 506 "PrintGo.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 737 "PrintGo.cpp"
  append(L"\n");
  append(L"  deferredEvent DeferredEvent");
                                                            #line 509 "PrintGo.cpp.template"
                                                              }
                                                              if (hasCustomCode)
                                                              {
                                                            #line 744 "PrintGo.cpp"
  append(L"\n");
  append(L"  deferredCode *DeferredCode");
                                                            #line 513 "PrintGo.cpp.template"
                                                              }
                                                            #line 749 "PrintGo.cpp"
  append(L"\n");
  append(L"  id int");
                                                            #line 515 "PrintGo.cpp.template"
                                                              printTokenVars();
                                                            #line 754 "PrintGo.cpp"
  append(L"\n");
  append(L"  begin int\n");
  append(L"  end int\n");
  append(L"}\n");
  append(L"\n");
  append(L"func (this *ParsingThread) open(initialState int");
                                                            #line 521 "PrintGo.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 764 "PrintGo.cpp"
  append(L", eh BottomUpEventHandler");
                                                            #line 523 "PrintGo.cpp.template"
                                                              }
                                                            #line 768 "PrintGo.cpp"
  append(L", t int) *PriorityQueue {\n");
  append(L"  this.accepted = false\n");
  append(L"  this.target = t");
                                                            #line 526 "PrintGo.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 775 "PrintGo.cpp"
  append(L"\n");
  append(L"  this.eventHandler = eh\n");
  append(L"  if this.eventHandler != nil {\n");
  append(L"    this.eventHandler.Reset(this.parser.input)\n");
  append(L"  }\n");
  append(L"  this.deferredEvent = nil");
                                                            #line 533 "PrintGo.cpp.template"
                                                              }
                                                              if (hasCustomCode && useGlr)
                                                              {
                                                            #line 786 "PrintGo.cpp"
  append(L"\n");
  append(L"  this.deferredCode = nil");
                                                            #line 537 "PrintGo.cpp.template"
                                                              }
                                                            #line 791 "PrintGo.cpp"
  append(L"\n");
  append(L"  this.stack = &StackNode{-1, ");
                                                            #line 539 "PrintGo.cpp.template"
                                                              if (grammar->states->hasLookback)
                                                              {
                                                            #line 797 "PrintGo.cpp"
  append(L"0, ");
                                                            #line 541 "PrintGo.cpp.template"
                                                              }
                                                            #line 801 "PrintGo.cpp"
  append(L"this.e0, nil}\n");
  append(L"  this.state = initialState\n");
  append(L"  this.action = this.predict(initialState)");
                                                            #line 544 "PrintGo.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 808 "PrintGo.cpp"
  append(L"\n");
  append(L"  this.bw = this.e0\n");
  append(L"  this.bs = this.e0\n");
  append(L"  this.es = this.e0");
                                                            #line 549 "PrintGo.cpp.template"
                                                              }
                                                            #line 815 "PrintGo.cpp"
  append(L"\n");
  append(L"  this.threads = new(PriorityQueue)\n");
  append(L"  heap.Push(this.threads, this)\n");
  append(L"  return this.threads\n");
  append(L"}\n");
  append(L"\n");
  append(L"func (this *ParsingThread) copy(other *ParsingThread, action int) *ParsingThread {\n");
  append(L"  this.action = action\n");
  append(L"  this.accepted = other.accepted\n");
  append(L"  this.target = other.target\n");
  append(L"  this.parser = other.parser");
                                                            #line 560 "PrintGo.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 830 "PrintGo.cpp"
  append(L"\n");
  append(L"  this.bs = other.bs\n");
  append(L"  this.es = other.es\n");
  append(L"  this.bw = other.bw\n");
  append(L"  this.eventHandler = other.eventHandler\n");
  append(L"  this.deferredEvent = other.deferredEvent");
                                                            #line 567 "PrintGo.cpp.template"
                                                              }
                                                              if (hasCustomCode)
                                                              {
                                                            #line 841 "PrintGo.cpp"
  append(L"\n");
  append(L"  this.deferredCode = other.deferredCode");
                                                            #line 571 "PrintGo.cpp.template"
                                                              }
                                                            #line 846 "PrintGo.cpp"
  append(L"\n");
  append(L"  this.parser.maxId++\n");
  append(L"  this.id = this.parser.maxId\n");
  append(L"  this.threads = other.threads\n");
  append(L"  this.state = other.state\n");
  append(L"  this.stack = other.stack\n");
  append(L"  this.b0 = other.b0\n");
  append(L"  this.e0 = other.e0");
                                                            #line 579 "PrintGo.cpp.template"
                                                              for (size_t i = 1; i <= grammar->k; ++i)
                                                              {
                                                                const wchar_t *iString = format.toString<wchar_t>(i);
                                                            #line 859 "PrintGo.cpp"
  append(L"\n");
  append(L"  this.l");
                                                            #line 583 "PrintGo.cpp.template"
                                                                print(iString);
                                                            #line 864 "PrintGo.cpp"
  append(L" = other.l");
                                                            #line 584 "PrintGo.cpp.template"
                                                                print(iString);
                                                            #line 868 "PrintGo.cpp"
  append(L"\n");
  append(L"  this.b");
                                                            #line 586 "PrintGo.cpp.template"
                                                                print(iString);
                                                            #line 873 "PrintGo.cpp"
  append(L" = other.b");
                                                            #line 587 "PrintGo.cpp.template"
                                                                print(iString);
                                                            #line 877 "PrintGo.cpp"
  append(L"\n");
  append(L"  this.e");
                                                            #line 589 "PrintGo.cpp.template"
                                                                print(iString);
                                                            #line 882 "PrintGo.cpp"
  append(L" = other.e");
                                                            #line 590 "PrintGo.cpp.template"
                                                                print(iString);
                                                              }
                                                            #line 887 "PrintGo.cpp"
  append(L"\n");
  append(L"  this.end = other.end\n");
  append(L"  return this\n");
  append(L"}\n");
  append(L"\n");
  append(L"func (this *ParsingThread) compareTo(other *ParsingThread) int {\n");
  append(L"  if this.accepted != other.accepted {\n");
  append(L"    if this.accepted {\n");
  append(L"      return 1\n");
  append(L"    }\n");
  append(L"    return -1\n");
  append(L"  }\n");
  append(L"  comp := this.e0 - other.e0\n");
  append(L"  if comp == 0 {\n");
  append(L"    return this.id - other.id\n");
  append(L"  }\n");
  append(L"  return comp\n");
  append(L"}\n");
  append(L"\n");
  append(L"func (this *ParsingThread) equals(other *ParsingThread) bool {\n");
  append(L"  if this.accepted != other.accepted {\n");
  append(L"    return false\n");
  append(L"  }\n");
  append(L"  if this.b1 != other.b1 {\n");
  append(L"    return false\n");
  append(L"  }\n");
  append(L"  if this.e1 != other.e1 {\n");
  append(L"    return false\n");
  append(L"  }\n");
  append(L"  if this.l1 != other.l1 {\n");
  append(L"    return false\n");
  append(L"  }\n");
  append(L"  if this.state != other.state {\n");
  append(L"    return false\n");
  append(L"  }\n");
  append(L"  if this.action != other.action {\n");
  append(L"    return false\n");
  append(L"  }\n");
  append(L"  if ! this.stack.equals(other.stack) {\n");
  append(L"    return false\n");
  append(L"  }\n");
  append(L"  return true\n");
  append(L"}\n");
  append(L"\n");
  append(L"func (this *ParsingThread) parse() int {");
                                                            #line 636 "PrintGo.cpp.template"
                                                              beginPublic();
                                                            }

                                                            void PrintGo::printFlush(int i, bool withinThread)
                                                            {
                                                              if (trace)
                                                              {
                                                                increaseIndent(i);
                                                            #line 942 "PrintGo.cpp"
  append(L"\n");
  append(L"flushTrace();");
                                                            #line 645 "PrintGo.cpp.template"
                                                                decreaseIndent(i);
                                                              }
                                                            }

                                                            void PrintGo::openMethod(const wchar_t *type,
                                                                                     const wchar_t *prefix,
                                                                                     const wchar_t *name,
                                                                                     const wchar_t *args,
                                                                                     bool constant,
                                                                                     const wchar_t *clazz)
                                                            {
                                                              if (clazz == 0) clazz = className.c_str();
                                                            #line 958 "PrintGo.cpp"
  append(L"\n");
  append(L"func (this *");
                                                            #line 658 "PrintGo.cpp.template"
                                                              print(clazz);
                                                            #line 963 "PrintGo.cpp"
  append(L") ");
                                                            #line 659 "PrintGo.cpp.template"
                                                              wchar_t initial[2] = {name[0], 0};
                                                              if (wcscmp(visibility, publ()) == 0) initial[0] = towupper(initial[0]);
                                                              print(initial);
                                                              print(name + 1);
                                                            #line 970 "PrintGo.cpp"
  append(L"(");
                                                            #line 663 "PrintGo.cpp.template"
                                                              printArgs(args);
                                                            #line 974 "PrintGo.cpp"
  append(L")");
                                                            #line 664 "PrintGo.cpp.template"
                                                              if (wcscmp(type, voidType()))
                                                              {
                                                            #line 979 "PrintGo.cpp"
  append(L" ");
                                                            #line 666 "PrintGo.cpp.template"
                                                                print(WString(type).rtrim().c_str());
                                                              }
                                                            }

                                                            void PrintGo::privateVars()
                                                            {
                                                              if (trace)
                                                              {
                                                            #line 990 "PrintGo.cpp"
  append(L"\n");
  append(L"func (this *");
                                                            #line 675 "PrintGo.cpp.template"
                                                                print(useGlr ? L"ParsingThread" : className.c_str());
                                                            #line 995 "PrintGo.cpp"
  append(L") lookaheadString() string {\n");
  append(L"  result := \"\"");
                                                            #line 677 "PrintGo.cpp.template"
                                                                for (size_t i = 1; i <= grammar->k; ++i)
                                                                {
                                                            #line 1001 "PrintGo.cpp"
  append(L"\n");
  append(L"  if this.l");
                                                            #line 680 "PrintGo.cpp.template"
                                                                  print(format.toString<wchar_t>(i));
                                                            #line 1006 "PrintGo.cpp"
  append(L" > 0 {\n");
  append(L"    result += ");
                                                            #line 682 "PrintGo.cpp.template"
                                                                  if (i != 1)
                                                                  {
                                                            #line 1012 "PrintGo.cpp"
  append(L"\" \" + ");
                                                            #line 684 "PrintGo.cpp.template"
                                                                  }
                                                            #line 1016 "PrintGo.cpp"
  append(L"token[this.l");
                                                            #line 685 "PrintGo.cpp.template"
                                                                  print(format.toString<wchar_t>(i));
                                                            #line 1020 "PrintGo.cpp"
  append(L"]");
                                                            #line 686 "PrintGo.cpp.template"
                                                                  increaseIndent();
                                                                }
                                                                for (size_t i = 1; i <= grammar->k; ++i)
                                                                {
                                                                  decreaseIndent();
                                                            #line 1028 "PrintGo.cpp"
  append(L"\n");
  append(L"  }");
                                                            #line 692 "PrintGo.cpp.template"
                                                                }
                                                            #line 1033 "PrintGo.cpp"
  append(L"\n");
  append(L"  return result\n");
  append(L"}\n");
                                                            #line 696 "PrintGo.cpp.template"
                                                              }
                                                              if (memoization)
                                                              {
                                                                int bits = Math::bits(grammar->conflictCount);
                                                            #line 1042 "PrintGo.cpp"
  append(L"\n");
  append(L"func (this *");
                                                            #line 701 "PrintGo.cpp.template"
                                                                print(className.c_str());
                                                            #line 1047 "PrintGo.cpp"
  append(L") memoize(i int, e int, v int) {\n");
  append(L"  this.memo[(e << ");
                                                            #line 703 "PrintGo.cpp.template"
                                                                print(format.toString<wchar_t>(bits));
                                                            #line 1052 "PrintGo.cpp"
  append(L") + i] = v\n");
  append(L"}\n");
  append(L"\n");
  append(L"func (this *");
                                                            #line 707 "PrintGo.cpp.template"
                                                                print(className.c_str());
                                                            #line 1059 "PrintGo.cpp"
  append(L") memoized(i int, e int) int {\n");
  append(L"  return this.memo[(e << ");
                                                            #line 709 "PrintGo.cpp.template"
                                                                print(format.toString<wchar_t>(bits));
                                                            #line 1064 "PrintGo.cpp"
  append(L") + i]\n");
  append(L"}\n");
                                                            #line 712 "PrintGo.cpp.template"
                                                              }
                                                            #line 1069 "PrintGo.cpp"
  append(L"\n");
  append(L"type ");
                                                            #line 714 "PrintGo.cpp.template"
                                                              print(className.c_str());
                                                            #line 1074 "PrintGo.cpp"
  append(L" struct {");
                                                            #line 715 "PrintGo.cpp.template"
                                                              if (useGlr)
                                                              {
                                                            #line 1079 "PrintGo.cpp"
  append(L"\n");
  append(L"  thread *ParsingThread\n");
  append(L"  input string");
                                                            #line 719 "PrintGo.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 1086 "PrintGo.cpp"
  append(L"\n");
  append(L"  eventHandler BottomUpEventHandler");
                                                            #line 722 "PrintGo.cpp.template"
                                                                }
                                                            #line 1091 "PrintGo.cpp"
  append(L"\n");
  append(L"  size int\n");
  append(L"  maxId int");
                                                            #line 725 "PrintGo.cpp.template"
                                                              }
                                                              else
                                                              {
                                                                printTokenVars();
                                                              }
                                                              if (memoization)
                                                              {
                                                            #line 1103 "PrintGo.cpp"
  append(L"\n");
  append(L"  memo map[int]int");
                                                            #line 733 "PrintGo.cpp.template"
                                                                if (grammar->noThrow)
                                                                {
                                                            #line 1109 "PrintGo.cpp"
  append(L"\n");
  append(L"  viable bool");
                                                            #line 736 "PrintGo.cpp.template"
                                                                }
                                                              }
                                                            }

                                                            void PrintGo::printFileProcessor()
                                                            {
                                                            #line 1119 "PrintGo.cpp"
  append(L"\n");
  append(L"var quiet bool = false\n");
  append(L"var parsed int64 = 0\n");
  append(L"var errorCount int = 0\n");
  append(L"var parsers []*ParseJob\n");
  append(L"\n");
  append(L"type ParseJob struct {\n");
  append(L"  name string\n");
  append(L"  input string\n");
  append(L"  parser *");
                                                            #line 751 "PrintGo.cpp.template"
                                                              print(className.c_str());
                                                              if (tree)
                                                              {
                                                            #line 1134 "PrintGo.cpp"
  append(L"\n");
  append(L"  contentCounter *ContentCounter");
                                                            #line 755 "PrintGo.cpp.template"
                                                                if (isLrParser)
                                                                {
                                                            #line 1140 "PrintGo.cpp"
  append(L"\n");
  append(L"  parseTreeBuilder *ParseTreeBuilder");
                                                            #line 758 "PrintGo.cpp.template"
                                                                }
                                                              }
                                                            #line 1146 "PrintGo.cpp"
  append(L"\n");
  append(L"}\n");
  append(L"\n");
  append(L"func main() {\n");
  append(L"  if len(os.Args) < 2 {\n");
  append(L"    os.Stderr.WriteString(\"Usage: ");
                                                            #line 765 "PrintGo.cpp.template"
                                                              print(className.c_str());
                                                            #line 1155 "PrintGo.cpp"
  append(L" [-q] [-r N] [-t N] ENDING...\\n\")\n");
  append(L"    os.Stderr.WriteString(\"\\n\")\n");
  append(L"    os.Stderr.WriteString(\"  parse all files that have names ending with ENDING, in current dir and below,\\n\")\n");
  append(L"    os.Stderr.WriteString(\"  and display performance summary.\\n\")\n");
  append(L"    os.Stderr.WriteString(\"\\n\")\n");
  append(L"    os.Stderr.WriteString(\"  -q     do not show file names\\n\")\n");
  append(L"    os.Stderr.WriteString(\"  -r N   repeat N times\\n\")\n");
  append(L"    os.Stderr.WriteString(\"  -t N   repeat until N seconds have elapsed\\n\")\n");
  append(L"  } else {\n");
  append(L"    repeat := 1\n");
  append(L"    timeout := 0\n");
  append(L"    var i int\n");
  append(L"    for i = 1; i < len(os.Args) && strings.HasPrefix(os.Args[i], \"-\"); i++ {\n");
  append(L"      var opt byte = ' '\n");
  append(L"      if len(os.Args[i]) == 2 {\n");
  append(L"        opt = os.Args[i][1]\n");
  append(L"      }\n");
  append(L"      switch opt {\n");
  append(L"      case 'q':\n");
  append(L"        quiet = true\n");
  append(L"      case 'r':\n");
  append(L"        i++\n");
  append(L"        repeat, _ = strconv.Atoi(os.Args[i])\n");
  append(L"        timeout = 0\n");
  append(L"      case 't':\n");
  append(L"        repeat = 0\n");
  append(L"        i++\n");
  append(L"        timeout, _ = strconv.Atoi(os.Args[i])\n");
  append(L"        timeout *= 1000\n");
  append(L"      default:\n");
  append(L"        panic(\"invalid option: \" + os.Args[i])\n");
  append(L"      }\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    start := time.Now().UnixNano() / int64(time.Millisecond)\n");
  append(L"\n");
  append(L"    for ; i < len(os.Args); i++ {\n");
  append(L"      err := filepath.Walk(\".\", func (path string, f os.FileInfo, err error) error {\n");
  append(L"        if strings.HasSuffix(path, os.Args[i]) {\n");
  append(L"          collectInput(path, read(path))\n");
  append(L"        }\n");
  append(L"        return nil\n");
  append(L"      })\n");
  append(L"      if err != nil {\n");
  append(L"        panic(err)\n");
  append(L"      }\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    if len(parsers) != 0 {\n");
  append(L"      msec := time.Now().UnixNano() / int64(time.Millisecond) - start\n");
  append(L"\n");
  append(L"      if ! quiet {\n");
  append(L"        fmt.Println()\n");
  append(L"      }\n");
  append(L"      plural := \"s\"\n");
  append(L"      if len(parsers) == 1 {\n");
  append(L"        plural = \"\"\n");
  append(L"      }\n");
  append(L"      fmt.Println(\"loaded \" + strconv.Itoa(len(parsers)) + \" file\" + plural + \" in \" + strconv.FormatInt(msec, 10) + \" msec\")\n");
  append(L"      if ! quiet {\n");
  append(L"        fmt.Println()\n");
  append(L"      }\n");
  append(L"      os.Stdout.Sync()\n");
  append(L"\n");
  append(L"      start = time.Now().UnixNano() / int64(time.Millisecond)\n");
  append(L"      for i = 0; ; i++ {\n");
  append(L"        if repeat != 0 && i >= repeat {\n");
  append(L"          break\n");
  append(L"        }\n");
  append(L"        if timeout != 0 && int(time.Now().UnixNano() / int64(time.Millisecond) - start) >= timeout {\n");
  append(L"          break\n");
  append(L"        }\n");
  append(L"\n");
  append(L"        for _, job := range parsers {\n");
  append(L"          if job.parser != nil {\n");
  append(L"            if ! quiet {\n");
  append(L"              fmt.Print(\"parsing \" + job.name)\n");
  append(L"            }\n");
  append(L"            job.parser");
                                                            #line 844 "PrintGo.cpp.template"
                                                                  if (useGlr)
                                                                  {
                                                            #line 1238 "PrintGo.cpp"
  append(L".thread");
                                                            #line 846 "PrintGo.cpp.template"
                                                                  }
                                                            #line 1242 "PrintGo.cpp"
  append(L".Reset(0, 0, 0)\n");
  append(L"            pe := job.parser.Parse_");
                                                            #line 848 "PrintGo.cpp.template"
                                                                  print(Format::acceptableName<WString>(grammar->startSymbol()->name).c_str());
                                                            #line 1247 "PrintGo.cpp"
  append(L"()\n");
  append(L"            if pe != nil {\n");
  append(L"              errorCount++\n");
  append(L"              if quiet {\n");
  append(L"                fmt.Println(\"parsing \" + job.name)\n");
  append(L"              }\n");
  append(L"              fmt.Println(\": error: \" + job.parser.GetErrorMessage(*pe))\n");
  append(L"              job.parser = nil\n");
  append(L"            }\n");
  append(L"            if ! quiet {\n");
  append(L"              fmt.Println()\n");
  append(L"            }");
                                                            #line 860 "PrintGo.cpp.template"
                                                                  if (tree)
                                                                  {
                                                                    if (isLrParser)
                                                                    {
                                                            #line 1265 "PrintGo.cpp"
  append(L"\n");
  append(L"            job.parseTreeBuilder.Serialize(job.contentCounter)");
                                                            #line 865 "PrintGo.cpp.template"
                                                                    }
                                                            #line 1270 "PrintGo.cpp"
  append(L"\n");
  append(L"            if (job.contentCounter.getLength() != len(job.input)) {\n");
  append(L"              panic(\"content counter saw \" + strconv.Itoa(job.contentCounter.getLength()) + \", but input length is \" + strconv.Itoa(len(job.input)))\n");
  append(L"            }");
                                                            #line 869 "PrintGo.cpp.template"
                                                                  }
                                                            #line 1277 "PrintGo.cpp"
  append(L"\n");
  append(L"            parsed += int64(len(job.input))\n");
  append(L"          }\n");
  append(L"        }\n");
  append(L"      }\n");
  append(L"      msec = time.Now().UnixNano() / int64(time.Millisecond) - start\n");
  append(L"      var mbPerSec string = \"\"\n");
  append(L"      if msec != 0 {\n");
  append(L"        mbPerSec = fmt.Sprintf(\"%.2f\", float64(parsed) / 1024e0 / 1024e0 * 1000e0 / float64(msec))\n");
  append(L"      }\n");
  append(L"\n");
  append(L"      if ! quiet {\n");
  append(L"        fmt.Println()\n");
  append(L"      }\n");
  append(L"      plural = \"s\"\n");
  append(L"      if parsed == 1 {\n");
  append(L"        plural = \"\"\n");
  append(L"      }\n");
  append(L"      fmt.Print(\"parsed \" + strconv.FormatInt(parsed, 10) + \" byte\" + plural +\n");
  append(L"                \" in \" + strconv.FormatInt(msec, 10) + \" msec\")\n");
  append(L"      if mbPerSec != \"\" {\n");
  append(L"        fmt.Print(\" (\" + mbPerSec + \" MB/sec)\")\n");
  append(L"      }\n");
  append(L"      fmt.Println()\n");
  append(L"      plural = \"s\"\n");
  append(L"      if errorCount == 1 {\n");
  append(L"        plural = \"\"\n");
  append(L"      }\n");
  append(L"      fmt.Println(strconv.Itoa(errorCount) + \" error\" + plural)\n");
  append(L"    }\n");
  append(L"  }\n");
  append(L"}\n");
  append(L"\n");
  append(L"func collectInput(name string, content string) {\n");
  append(L"  if ! quiet {\n");
  append(L"    fmt.Println(\"loading \" + name)\n");
  append(L"  }\n");
                                                            #line 907 "PrintGo.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 1318 "PrintGo.cpp"
  append(L"\n");
  append(L"  contentCounter := new(ContentCounter)");
                                                            #line 910 "PrintGo.cpp.template"
                                                                if (isLrParser)
                                                                {
                                                            #line 1324 "PrintGo.cpp"
  append(L"\n");
  append(L"  parseTreeBuilder := new(ParseTreeBuilder)");
                                                            #line 913 "PrintGo.cpp.template"
                                                                }
                                                              }
                                                            #line 1330 "PrintGo.cpp"
  append(L"\n");
  append(L"  parsers = append(parsers, &ParseJob{name, content, NewParser(content");
                                                            #line 917 "PrintGo.cpp.template"
                                                              if (tree)
                                                              {
                                                                if (isLrParser)
                                                                {
                                                            #line 1338 "PrintGo.cpp"
  append(L", parseTreeBuilder");
                                                            #line 921 "PrintGo.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1344 "PrintGo.cpp"
  append(L", contentCounter");
                                                            #line 924 "PrintGo.cpp.template"
                                                                }
                                                              }
                                                            #line 1349 "PrintGo.cpp"
  append(L")");
                                                            #line 926 "PrintGo.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 1354 "PrintGo.cpp"
  append(L", contentCounter");
                                                            #line 928 "PrintGo.cpp.template"
                                                                if (isLrParser)
                                                                {
                                                            #line 1359 "PrintGo.cpp"
  append(L", parseTreeBuilder");
                                                            #line 930 "PrintGo.cpp.template"
                                                                }
                                                              }
                                                            #line 1364 "PrintGo.cpp"
  append(L"})\n");
  append(L"}\n");
                                                            #line 935 "PrintGo.cpp.template"
                                                            }

                                                            void PrintGo::printReadMethod()
                                                            {
                                                            #line 1372 "PrintGo.cpp"
  append(L"\n");
  append(L"func read(arg string) string {\n");
  append(L"  if strings.HasPrefix(arg, \"{\") && strings.HasSuffix(arg, \"}\") {\n");
  append(L"    return arg[1:len(arg) - 1]\n");
  append(L"  } else {\n");
  append(L"    content, err := ioutil.ReadFile(arg)\n");
  append(L"    if err != nil {\n");
  append(L"      panic(err)\n");
  append(L"    }\n");
  append(L"    if len(content) > 0 && content[0] == byte(0xef) && content[1] == byte(0xbb) && content[2] == byte(0xbf) {\n");
  append(L"      content = content[3:]\n");
  append(L"    }\n");
  append(L"    return string(content)\n");
  append(L"  }\n");
  append(L"}\n");
                                                            #line 954 "PrintGo.cpp.template"
                                                            }

                                                            void PrintGo::printInterface()
                                                            {
                                                              if (! packageName.empty())
                                                              {
                                                            #line 1395 "PrintGo.cpp"
  append(L"\n");
  append(L"package ");
                                                            #line 961 "PrintGo.cpp.template"
                                                                print(packageName.c_str());
                                                            #line 1400 "PrintGo.cpp"
  append(L";\n");
                                                            #line 963 "PrintGo.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                                if (main || useGlr)
                                                                {
                                                            #line 1408 "PrintGo.cpp"
  append(L"\n");
  append(L"import java.io.IOException;\n");
  append(L"import java.io.Writer;\n");
                                                            #line 971 "PrintGo.cpp.template"
                                                                }
                                                            #line 1414 "PrintGo.cpp"
  append(L"\n");
  append(L"import java.util.Arrays;");
                                                            #line 973 "PrintGo.cpp.template"
                                                              }
                                                            #line 1419 "PrintGo.cpp"
  append(L"\n");
  append(L"public interface ");
                                                            #line 975 "PrintGo.cpp.template"
                                                              print(className.c_str());
                                                            #line 1424 "PrintGo.cpp"
  append(L"\n");
  append(L"{\n");
  append(L"  public void initialize(CharSequence input");
                                                            #line 978 "PrintGo.cpp.template"
                                                              if (noLexer)
                                                              {
                                                            #line 1431 "PrintGo.cpp"
  append(L", Lexer l");
                                                            #line 980 "PrintGo.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                            #line 1437 "PrintGo.cpp"
  append(L", ");
                                                            #line 983 "PrintGo.cpp.template"
                                                                if (isLrParser)
                                                                {
                                                            #line 1442 "PrintGo.cpp"
  append(L"BottomUp");
                                                            #line 986 "PrintGo.cpp.template"
                                                                }
                                                            #line 1446 "PrintGo.cpp"
  append(L"EventHandler eh");
                                                            #line 988 "PrintGo.cpp.template"
                                                              }
                                                            #line 1450 "PrintGo.cpp"
  append(L");\n");
  append(L"  public void parse();\n");
  append(L"  public void Reset();\n");
  append(L"  public String getErrorMessage(ParseException e);\n");
                                                            #line 993 "PrintGo.cpp.template"
                                                              printParseException();
                                                              printEventHandlerImplementation();
                                                            #line 1458 "PrintGo.cpp"
  append(L"}\n");
                                                            #line 996 "PrintGo.cpp.template"
                                                            }

                                                            void PrintGo::printParseException()
                                                            {
                                                            #line 1465 "PrintGo.cpp"
  append(L"\n");
  append(L"type ParseError struct {\n");
  append(L"  begin int\n");
  append(L"  end int\n");
  append(L"  state int\n");
  append(L"  offending int\n");
  append(L"  expected int");
                                                            #line 1006 "PrintGo.cpp.template"
                                                              if (useGlr)
                                                              {
                                                            #line 1476 "PrintGo.cpp"
  append(L"\n");
  append(L"  ambiguousInput bool");
                                                            #line 1009 "PrintGo.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 1482 "PrintGo.cpp"
  append(L"\n");
  append(L"  ambiguityDescriptor *ParseTreeBuilder");
                                                            #line 1012 "PrintGo.cpp.template"
                                                                }
                                                              }
                                                            #line 1488 "PrintGo.cpp"
  append(L"\n");
  append(L"}\n");
  append(L"\n");
  append(L"func (this ParseError) Error() string {\n");
  append(L"  if ");
                                                            #line 1018 "PrintGo.cpp.template"
                                                              if (useGlr)
                                                              {
                                                            #line 1497 "PrintGo.cpp"
  append(L"this.ambiguousInput {\n");
  append(L"    return \"ambiguous input\"\n");
  append(L"  } else if ");
                                                            #line 1022 "PrintGo.cpp.template"
                                                              }
                                                            #line 1503 "PrintGo.cpp"
  append(L"this.offending < 0 {\n");
  append(L"    return \"lexical analysis failed\"\n");
  append(L"  } else {\n");
  append(L"    return \"syntax error\"\n");
  append(L"  }\n");
  append(L"}\n");
                                                            #line 1029 "PrintGo.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 1513 "PrintGo.cpp"
  append(L"\n");
  append(L"func (this *ParseError) Serialize(eventHandler EventHandler) {");
                                                            #line 1032 "PrintGo.cpp.template"
                                                                if (useGlr)
                                                                {
                                                            #line 1519 "PrintGo.cpp"
  append(L"\n");
  append(L"  this.ambiguityDescriptor.Serialize(eventHandler)");
                                                            #line 1035 "PrintGo.cpp.template"
                                                                }
                                                            #line 1524 "PrintGo.cpp"
  append(L"\n");
  append(L"}\n");
                                                            #line 1038 "PrintGo.cpp.template"
                                                              }
                                                            #line 1529 "PrintGo.cpp"
  append(L"\n");
  append(L"func (this *ParseError) GetBegin() int {return this.begin}\n");
  append(L"func (this *ParseError) GetEnd() int {return this.end}\n");
  append(L"func (this *ParseError) GetState() int {return this.state}\n");
  append(L"func (this *ParseError) GetOffending() int {return this.offending}\n");
  append(L"func (this *ParseError) GetExpected() int {return this.expected}\n");
  append(L"func (this *ParseError) IsAmbiguousInput() bool {return ");
                                                            #line 1045 "PrintGo.cpp.template"
                                                              if (useGlr)
                                                              {
                                                            #line 1540 "PrintGo.cpp"
  append(L"this.ambiguousInput");
                                                            #line 1048 "PrintGo.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 1546 "PrintGo.cpp"
  append(L"false");
                                                            #line 1052 "PrintGo.cpp.template"
                                                              }
                                                            #line 1550 "PrintGo.cpp"
  append(L"}\n");
                                                            #line 1054 "PrintGo.cpp.template"
                                                              if (noLexer)
                                                              {
                                                            #line 1555 "PrintGo.cpp"
  append(L"\n");
  append(L"  public static class Token\n");
  append(L"  {\n");
  append(L"    public int code;\n");
  append(L"    public int begin;\n");
  append(L"    public int end;\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  public interface Lexer\n");
  append(L"  {\n");
  append(L"    void Reset(CharSequence input);\n");
  append(L"    void match(int tokenset, Token token);\n");
  append(L"  }\n");
                                                            #line 1069 "PrintGo.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                            #line 1573 "PrintGo.cpp"
  append(L"\n");
  append(L"type EventHandler interface {\n");
  append(L"  Reset(input string)\n");
  append(L"  StartNonterminal(name string, begin int)\n");
  append(L"  EndNonterminal(name string, end int)\n");
  append(L"  Terminal(name string, begin, end int)\n");
  append(L"  Whitespace(begin, end int)\n");
  append(L"}\n");
  append(L"\n");
  append(L"type TopDownTreeBuilder struct {\n");
  append(L"  input string\n");
  append(L"  stack []*Nonterminal\n");
  append(L"  top int\n");
  append(L"}\n");
  append(L"\n");
  append(L"func (this *TopDownTreeBuilder) Reset(input string) {\n");
  append(L"  this.input = input\n");
  append(L"  this.stack = make([]*Nonterminal, 1)\n");
  append(L"  this.top = -1\n");
  append(L"}\n");
  append(L"\n");
  append(L"func (this *TopDownTreeBuilder) StartNonterminal(name string, begin int) {\n");
  append(L"  nonterminal := &Nonterminal{&AbstractSymbol{name, begin, begin}, []Symbol{}}\n");
  append(L"  if this.top >= 0 {\n");
  append(L"    this.addChild(nonterminal)\n");
  append(L"  }\n");
  append(L"  this.top++\n");
  append(L"  if this.top >= cap(this.stack) {\n");
  append(L"    this.stack = append(this.stack, this.stack...)\n");
  append(L"  }\n");
  append(L"  this.stack[this.top] = nonterminal\n");
  append(L"}\n");
  append(L"\n");
  append(L"func (this *TopDownTreeBuilder) EndNonterminal(name string, end int) {\n");
  append(L"  this.stack[this.top].end = end\n");
  append(L"  if this.top > 0 {\n");
  append(L"    this.top--\n");
  append(L"  }\n");
  append(L"}\n");
  append(L"\n");
  append(L"func (this *TopDownTreeBuilder) Terminal(name string, begin, end int) {\n");
  append(L"  this.addChild(&Terminal{&AbstractSymbol{name, begin, end}})\n");
  append(L"}\n");
  append(L"\n");
  append(L"func (this *TopDownTreeBuilder) Whitespace(begin, end int) {\n");
  append(L"}\n");
  append(L"\n");
  append(L"func (this *TopDownTreeBuilder) addChild(s Symbol) {\n");
  append(L"  current := this.stack[this.top]\n");
  append(L"  current.addChild(s)\n");
  append(L"}\n");
  append(L"\n");
  append(L"func (this *TopDownTreeBuilder) Serialize(e EventHandler) {\n");
  append(L"  e.Reset(this.input)\n");
  append(L"  this.stack[0].send(e)\n");
  append(L"}\n");
  append(L"\n");
  append(L"type Symbol interface {\n");
  append(L"  GetName() string\n");
  append(L"  GetBegin() int\n");
  append(L"  GetEnd() int\n");
  append(L"  send(e EventHandler)\n");
  append(L"}\n");
  append(L"\n");
  append(L"type AbstractSymbol struct {\n");
  append(L"  name string\n");
  append(L"  begin int\n");
  append(L"  end int\n");
  append(L"}\n");
  append(L"\n");
  append(L"func (this *AbstractSymbol) GetName() string {\n");
  append(L"  return this.name\n");
  append(L"}\n");
  append(L"\n");
  append(L"func (this *AbstractSymbol) GetBegin() int {\n");
  append(L"  return this.begin\n");
  append(L"}\n");
  append(L"\n");
  append(L"func (this *AbstractSymbol) GetEnd() int {\n");
  append(L"  return this.end\n");
  append(L"}\n");
  append(L"\n");
  append(L"type Nonterminal struct {\n");
  append(L"  *AbstractSymbol\n");
  append(L"  children []Symbol\n");
  append(L"}\n");
  append(L"\n");
  append(L"func (this *Nonterminal) addChild(s Symbol) {\n");
  append(L"  this.children = append(this.children, s)\n");
  append(L"}\n");
  append(L"\n");
  append(L"func (this *Nonterminal) send(e EventHandler) {\n");
  append(L"  e.StartNonterminal(this.GetName(), this.GetBegin())\n");
  append(L"  pos := this.GetBegin()\n");
  append(L"  for _, c := range this.children {\n");
  append(L"    if pos < c.GetBegin() {\n");
  append(L"     e.Whitespace(pos, c.GetBegin())\n");
  append(L"    }\n");
  append(L"    c.send(e)\n");
  append(L"    pos = c.GetEnd()\n");
  append(L"  }\n");
  append(L"  if pos < this.GetEnd() {\n");
  append(L"    e.Whitespace(pos, this.GetEnd())\n");
  append(L"  }\n");
  append(L"  e.EndNonterminal(this.GetName(), this.GetEnd())\n");
  append(L"}\n");
  append(L"\n");
  append(L"type Terminal struct {\n");
  append(L"  *AbstractSymbol\n");
  append(L"}\n");
  append(L"\n");
  append(L"func (this *Terminal) send(e EventHandler) {\n");
  append(L"  e.Terminal(this.GetName(), this.GetBegin(), this.GetEnd())\n");
  append(L"}\n");
                                                            #line 1186 "PrintGo.cpp.template"
                                                                if (isLrParser)
                                                                {
                                                            #line 1691 "PrintGo.cpp"
  append(L"\n");
  append(L"type BottomUpEventHandler interface {\n");
  append(L"  Reset(input string)\n");
  append(L"  Nonterminal(name string, begin int, end int, count int)\n");
  append(L"  Terminal(name string, begin int, end int)\n");
  append(L"}\n");
                                                            #line 1194 "PrintGo.cpp.template"
                                                                }
                                                              }
                                                            }

                                                            void PrintGo::printEventHandlerImplementation()
                                                            {
                                                              if (tree)
                                                              {
                                                                if (main || useGlr)
                                                                {
                                                            #line 1709 "PrintGo.cpp"
  append(L"\n");
  append(L"type XmlSerializer struct {\n");
  append(L"  indent bool\n");
  append(L"  input string\n");
  append(L"  delayedTag string\n");
  append(L"  hasChildElement bool\n");
  append(L"  depth int\n");
  append(L"}\n");
  append(L"\n");
  append(L"func (this *XmlSerializer) Reset(input string) {\n");
  append(L"  fmt.Print(\"<?xml version=\\\"1.0\\\" encoding=\\\"UTF-8\\\"?>\")\n");
  append(L"\n");
  append(L"  this.input = input\n");
  append(L"  this.delayedTag = \"\"\n");
  append(L"  this.hasChildElement = false\n");
  append(L"  this.depth = 0\n");
  append(L"}\n");
  append(L"\n");
  append(L"func (this *XmlSerializer) StartNonterminal(tag string, b int) {\n");
  append(L"  if this.delayedTag != \"\" {\n");
  append(L"    fmt.Print(\"<\")\n");
  append(L"    fmt.Print(this.delayedTag)\n");
  append(L"    fmt.Print(\">\")\n");
  append(L"  }\n");
  append(L"  this.delayedTag = tag\n");
  append(L"  if this.indent {\n");
  append(L"    fmt.Println()\n");
  append(L"    for i := 0; i < this.depth; i++ {\n");
  append(L"      fmt.Print(\"  \")\n");
  append(L"    }\n");
  append(L"  }\n");
  append(L"  this.hasChildElement = false\n");
  append(L"  this.depth++\n");
  append(L"}\n");
  append(L"\n");
  append(L"func (this *XmlSerializer) EndNonterminal(tag string, e int) {\n");
  append(L"  this.depth--\n");
  append(L"  if this.delayedTag != \"\" {\n");
  append(L"    this.delayedTag = \"\"\n");
  append(L"    fmt.Print(\"<\")\n");
  append(L"    fmt.Print(tag)\n");
  append(L"    fmt.Print(\"/>\")\n");
  append(L"  } else {\n");
  append(L"    if this.indent {\n");
  append(L"      if this.hasChildElement {\n");
  append(L"        fmt.Println()\n");
  append(L"        for i := 0; i < this.depth; i++ {\n");
  append(L"          fmt.Print(\"  \")\n");
  append(L"        }\n");
  append(L"      }\n");
  append(L"    }\n");
  append(L"    fmt.Print(\"</\")\n");
  append(L"    fmt.Print(tag)\n");
  append(L"    fmt.Print(\">\")\n");
  append(L"  }\n");
  append(L"  this.hasChildElement = true\n");
  append(L"}\n");
  append(L"\n");
  append(L"func (this *XmlSerializer) Whitespace(b, e int) {\n");
  append(L"  this.characters(b, e)\n");
  append(L"}\n");
  append(L"\n");
  append(L"func (this *XmlSerializer) characters(b, e int) {\n");
  append(L"  if b < e {\n");
  append(L"    if this.delayedTag != \"\" {\n");
  append(L"      fmt.Print(\"<\")\n");
  append(L"      fmt.Print(this.delayedTag)\n");
  append(L"      fmt.Print(\">\")\n");
  append(L"      this.delayedTag = \"\"\n");
  append(L"    }\n");
  append(L"    for i := b; i < e; {\n");
  append(L"      c, l := utf8.DecodeRuneInString(this.input[i:])\n");
  append(L"      i += l\n");
  append(L"      switch c {\n");
  append(L"      case '&': fmt.Print(\"&amp;\")\n");
  append(L"      case '<': fmt.Print(\"&lt;\")\n");
  append(L"      case '>': fmt.Print(\"&gt;\")\n");
  append(L"      default: fmt.Print(string(c))\n");
  append(L"      }\n");
  append(L"    }\n");
  append(L"  }\n");
  append(L"}\n");
  append(L"\n");
  append(L"func (this *XmlSerializer) Terminal(tag string, b, e int) {\n");
  append(L"  if tag[0] == '\\'' {\n");
  append(L"    tag = \"TOKEN\"\n");
  append(L"  }\n");
  append(L"  this.StartNonterminal(tag, b)\n");
  append(L"  this.characters(b, e)\n");
  append(L"  this.EndNonterminal(tag, e)\n");
  append(L"}\n");
                                                            #line 1295 "PrintGo.cpp.template"
                                                                }
                                                                if (performanceTest)
                                                                {
                                                            #line 1805 "PrintGo.cpp"
  append(L"\n");
  append(L"type ContentCounter struct {\n");
  append(L"  length int\n");
  append(L"}\n");
  append(L"\n");
  append(L"func (this *ContentCounter) getLength() int {\n");
  append(L"  return this.length\n");
  append(L"}\n");
  append(L"\n");
  append(L"func (this *ContentCounter) Reset(input string) {this.length = 0}\n");
  append(L"func (this *ContentCounter) StartNonterminal(name string, begin int) {}\n");
  append(L"func (this *ContentCounter) EndNonterminal(name string, end int) {}\n");
  append(L"func (this *ContentCounter) Terminal(name string, begin, end int) {this.length += end - begin}\n");
  append(L"func (this *ContentCounter) Whitespace(begin, end int) {this.length += end - begin}\n");
                                                            #line 1313 "PrintGo.cpp.template"
                                                                }
                                                                if (isLrParser)
                                                                {
                                                            #line 1824 "PrintGo.cpp"
  append(L"\n");
  append(L"type ParseTreeBuilder struct {\n");
  append(L"  input string\n");
  append(L"  stack []Symbol\n");
  append(L"  top int\n");
  append(L"}\n");
  append(L"\n");
  append(L"func (this *ParseTreeBuilder) Reset(input string) {\n");
  append(L"  this.input = input\n");
  append(L"  this.stack = make([]Symbol, 192)\n");
  append(L"  this.top = -1\n");
  append(L"}\n");
  append(L"\n");
  append(L"func (this *ParseTreeBuilder) Nonterminal(name string, begin int, end int, count int) {");
                                                            #line 1330 "PrintGo.cpp.template"
                                                                if (useGlr)
                                                                {
                                                            #line 1842 "PrintGo.cpp"
  append(L"\n");
  append(L"  if count > this.top + 1 {\n");
  append(L"    content := this.pop(this.top + 1)\n");
  append(L"    e := end\n");
  append(L"    if len(content) != 0 {\n");
  append(L"       e = content[0].GetBegin()\n");
  append(L"    }\n");
  append(L"    this.Nonterminal(\"UNAMBIGUOUS\", begin, e, 0)\n");
  append(L"    for _, symbol := range content {\n");
  append(L"      this.push(symbol)\n");
  append(L"    }\n");
  append(L"    count = this.top + 1\n");
  append(L"  }");
                                                            #line 1344 "PrintGo.cpp.template"
                                                            }
                                                            #line 1858 "PrintGo.cpp"
  append(L"\n");
  append(L"  this.push(&Nonterminal{&AbstractSymbol{name, begin, end}, this.pop(count)})\n");
  append(L"}\n");
  append(L"\n");
  append(L"func (this *ParseTreeBuilder) Terminal(name string, begin int, end int) {\n");
  append(L"  this.push(&Terminal{&AbstractSymbol{name, begin, end}})\n");
  append(L"}\n");
  append(L"\n");
  append(L"func (this *ParseTreeBuilder) Serialize(e EventHandler) {\n");
  append(L"  e.Reset(this.input)\n");
  append(L"  for i := 0; i <= this.top; i++ {\n");
  append(L"    symbol := this.stack[i]\n");
  append(L"    symbol.send(e)\n");
  append(L"  }\n");
  append(L"}\n");
  append(L"\n");
  append(L"func (this *ParseTreeBuilder) push(s Symbol) {\n");
  append(L"  this.top++\n");
  append(L"  if this.top >= cap(this.stack) {\n");
  append(L"    this.stack = append(this.stack, this.stack...)\n");
  append(L"  }\n");
  append(L"  this.stack[this.top] = s\n");
  append(L"}\n");
  append(L"\n");
  append(L"func (this *ParseTreeBuilder) pop(count int) []Symbol {\n");
  append(L"  this.top -= count\n");
  append(L"  return append([]Symbol{}, this.stack[this.top + 1:this.top + count + 1]...)\n");
  append(L"}\n");
                                                            #line 1373 "PrintGo.cpp.template"
                                                                }
                                                              }
                                                            }

                                                            void PrintGo::printTokenVars()
                                                            {
                                                            #line 1894 "PrintGo.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 1380 "PrintGo.cpp.template"
                                                              if (! isLrParser && (grammar->k > 1 ||
                                                                                   memoization ||
                                                                                   ! grammar->decisionPoints.empty()))
                                                              {
                                                            #line 1902 "PrintGo.cpp"
  append(L"lk,");
                                                            #line 1384 "PrintGo.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 1908 "PrintGo.cpp"
  append(L"   ");
                                                            #line 1387 "PrintGo.cpp.template"
                                                              }
                                                            #line 1912 "PrintGo.cpp"
  append(L" b0, e0 int");
                                                            #line 1388 "PrintGo.cpp.template"
                                                              for (size_t k = 1; k <= grammar->k; ++k)
                                                              {
                                                                Format format;
                                                                wchar_t *asString = format.toString<wchar_t>(k);
                                                            #line 1919 "PrintGo.cpp"
  append(L"\n");
  append(L"  l");
                                                            #line 1393 "PrintGo.cpp.template"
                                                                print(asString);
                                                            #line 1924 "PrintGo.cpp"
  append(L", b");
                                                            #line 1394 "PrintGo.cpp.template"
                                                                print(asString);
                                                            #line 1928 "PrintGo.cpp"
  append(L", e");
                                                            #line 1395 "PrintGo.cpp.template"
                                                                print(asString);
                                                            #line 1932 "PrintGo.cpp"
  append(L" int");
                                                            #line 1396 "PrintGo.cpp.template"
                                                              }
                                                              if (hasBacktracking)
                                                              {
                                                            #line 1938 "PrintGo.cpp"
  append(L"\n");
  append(L"  bx, ex, sx, lx, tx int");
                                                            #line 1400 "PrintGo.cpp.template"
                                                              }
                                                              else if (isLrParser && ! useGlr)
                                                              {
                                                            #line 1945 "PrintGo.cpp"
  append(L"\n");
  append(L"  iStack []int\n");
  append(L"  top int");
                                                            #line 1405 "PrintGo.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                                if (isLrParser)
                                                                {
                                                                  if (useGlr)
                                                                  {
                                                            #line 1957 "PrintGo.cpp"
  append(L"\n");
  append(L"  bw, bs, es int");
                                                            #line 1413 "PrintGo.cpp.template"
                                                                  }
                                                            #line 1962 "PrintGo.cpp"
  append(L"\n");
  append(L"  eventHandler BottomUpEventHandler");
                                                            #line 1415 "PrintGo.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1969 "PrintGo.cpp"
  append(L"\n");
  append(L"  eventHandler EventHandler");
                                                            #line 1419 "PrintGo.cpp.template"
                                                                }
                                                              }
                                                              else if (useGlr)
                                                              {
                                                            #line 1977 "PrintGo.cpp"
  append(L"\n");
  append(L"  bw, bs int");
                                                            #line 1424 "PrintGo.cpp.template"
                                                              }
                                                            }

// End
