// This file was generated on Sat Oct 17, 2026 11:26 (UTC+02) by REx v6.3-SNAPSHOT which is Copyright (c) 1979-2026 by Gunther Rademacher <grd@gmx.net>
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
                                                                if (rejectsAmbiguity() && tree)
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
                                                              if (minimalAmbiguity)
                                                              {
                                                            #line 482 "PrintGo.cpp"
  append(L"\n");
  append(L"\n");
  append(L"type AmbiguityEvent struct {\n");
  append(L"  *AbstractDeferredEvent\n");
  append(L"}\n");
  append(L"\n");
  append(L"func (this *AmbiguityEvent) execute(eventHandler BottomUpEventHandler) {\n");
  append(L"  eventHandler.Ambiguity(this.begin, this.end)\n");
  append(L"}\n");
  append(L"\n");
  append(L"func (this *AmbiguityEvent) toString() string {\n");
  append(L"  return \"ambiguity(\" + strconv.Itoa(this.begin) + \", \" + strconv.Itoa(this.end) + \")\"\n");
  append(L"}\n");
                                                            #line 342 "PrintGo.cpp.template"
                                                              }
                                                              }
                                                            #line 499 "PrintGo.cpp"
  append(L"\n");
  append(L"const (\n");
  append(L"  PARSING = 0\n");
  append(L"  ACCEPTED = 1\n");
  append(L"  ERROR = 2\n");
  append(L")\n");
  append(L"\n");
  append(L"func (this *");
                                                            #line 351 "PrintGo.cpp.template"
                                                              print(className.c_str());
                                                            #line 510 "PrintGo.cpp"
  append(L") parse(target int, initialState int, ");
                                                            #line 352 "PrintGo.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 515 "PrintGo.cpp"
  append(L"eventHandler BottomUpEventHandler, ");
                                                            #line 355 "PrintGo.cpp.template"
                                                              }
                                                            #line 519 "PrintGo.cpp"
  append(L"thread *ParsingThread) *ParsingThread {\n");
  append(L"  threads := thread.open(initialState");
                                                            #line 357 "PrintGo.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 525 "PrintGo.cpp"
  append(L", eventHandler");
                                                            #line 359 "PrintGo.cpp.template"
                                                              }
                                                            #line 529 "PrintGo.cpp"
  append(L", target)\n");
  append(L"  for {\n");
  append(L"    thread = heap.Pop(threads).(*ParsingThread)\n");
  append(L"    if (thread.accepted) {");
                                                            #line 363 "PrintGo.cpp.template"
                                                                             if (rejectsAmbiguity())
                                                              {
                                                            #line 537 "PrintGo.cpp"
  append(L"\n");
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
                                                            #line 375 "PrintGo.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 552 "PrintGo.cpp"
  append(L", thread.deferredEvent, other.deferredEvent");
                                                            #line 378 "PrintGo.cpp.template"
                                                              }
                                                            #line 556 "PrintGo.cpp"
  append(L")\n");
  append(L"      }");
                                                            #line 380 "PrintGo.cpp.template"
                                                          }
                                                              else
                                                              {
                                                            #line 563 "PrintGo.cpp"
  append(L"\n");
  append(L"      for ! threads.isEmpty() {\n");
  append(L"        other := heap.Pop(threads).(*ParsingThread)\n");
  append(L"        if thread.e0 < other.e0 {\n");
  append(L"          thread = other\n");
  append(L"        } else {\n");
  append(L"          thread = this.resolve(thread, other)\n");
  append(L"        }\n");
  append(L"      }");
                                                            #line 391 "PrintGo.cpp.template"
                                                          }
                                                              if (tree)
                                                              {
                                                            #line 577 "PrintGo.cpp"
  append(L"\n");
  append(L"      if thread.deferredEvent != nil {\n");
  append(L"        release(thread.deferredEvent, eventHandler)\n");
  append(L"        thread.deferredEvent = nil\n");
  append(L"      }");
                                                            #line 398 "PrintGo.cpp.template"
                                                              }
                                                              if (hasCustomCode)
                                                              {
                                                            #line 587 "PrintGo.cpp"
  append(L"\n");
  append(L"      thread.ExecuteDeferredCode()");
                                                            #line 402 "PrintGo.cpp.template"
                                                              }
                                                            #line 592 "PrintGo.cpp"
  append(L"\n");
  append(L"      return thread\n");
  append(L"    }\n");
  append(L"\n");
                                                            #line 407 "PrintGo.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 600 "PrintGo.cpp"
  append(L"    if ! threads.isEmpty() {\n");
  append(L"      if threads.peek().equals(thread) {\n");
  append(L"        this.rejectAmbiguity(thread.stack.pos, thread.e0");
                                                            #line 411 "PrintGo.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 607 "PrintGo.cpp"
  append(L", thread.deferredEvent, threads.peek().deferredEvent");
                                                            #line 414 "PrintGo.cpp.template"
                                                              }
                                                            #line 611 "PrintGo.cpp"
  append(L")\n");
  append(L"      }");
                                                            #line 416 "PrintGo.cpp.template"
                                                          }
                                                              else
                                                              {
                                                            #line 618 "PrintGo.cpp"
  append(L"    for ! threads.isEmpty() && threads.peek().equals(thread) {\n");
  append(L"      thread = this.resolve(thread, heap.Pop(threads).(*ParsingThread))\n");
  append(L"    }\n");
  append(L"    if threads.isEmpty() {");
                                                            #line 422 "PrintGo.cpp.template"
                                                         }
                                                              if (tree || hasCustomCode)
                                                              {
                                                                if (rejectsAmbiguity())
                                                                {
                                                            #line 629 "PrintGo.cpp"
  append(L"\n");
  append(L"    } else {");
                                                            #line 428 "PrintGo.cpp.template"
                                                     }
                                                                if (tree)
                                                                {
                                                            #line 636 "PrintGo.cpp"
  append(L"\n");
  append(L"      if thread.deferredEvent != nil {\n");
  append(L"        release(thread.deferredEvent, eventHandler)\n");
  append(L"        thread.deferredEvent = nil\n");
  append(L"      }");
                                                            #line 435 "PrintGo.cpp.template"
                                                                }
                                                                if (hasCustomCode)
                                                                {
                                                            #line 646 "PrintGo.cpp"
  append(L"\n");
  append(L"      thread.ExecuteDeferredCode()");
                                                            #line 439 "PrintGo.cpp.template"
                                                                }
                                                              }
                                                            #line 652 "PrintGo.cpp"
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
  append(L"                        -1");
                                                            #line 462 "PrintGo.cpp.template"
                                                             if (rejectsAmbiguity())
                                                              {
                                                            #line 678 "PrintGo.cpp"
  append(L",\n");
  append(L"                        false");
                                                            #line 465 "PrintGo.cpp.template"
                                                            if (tree)
                                                              {
                                                            #line 684 "PrintGo.cpp"
  append(L",\n");
  append(L"                        nil");
                                                            #line 468 "PrintGo.cpp.template"
                                                              }
                                                              }
                                                            #line 690 "PrintGo.cpp"
  append(L"})\n");
  append(L"    }\n");
  append(L"  }\n");
  append(L"}\n");
  append(L"\n");
                                                            #line 475 "PrintGo.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 699 "PrintGo.cpp"
  append(L"\n");
  append(L"func (this *");
                                                            #line 478 "PrintGo.cpp.template"
                                                              print(className.c_str());
                                                            #line 704 "PrintGo.cpp"
  append(L") rejectAmbiguity(begin int, end int");
                                                            #line 479 "PrintGo.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 709 "PrintGo.cpp"
  append(L", first DeferredEvent, second DeferredEvent");
                                                            #line 482 "PrintGo.cpp.template"
                                                              }
                                                            #line 713 "PrintGo.cpp"
  append(L") {");
                                                            #line 483 "PrintGo.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 718 "PrintGo.cpp"
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
                                                            #line 495 "PrintGo.cpp.template"
                                                              }
                                                            #line 731 "PrintGo.cpp"
  append(L"\n");
  append(L"  panic(&ParseError{begin, end, 1, -1, -1, true");
                                                            #line 497 "PrintGo.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 737 "PrintGo.cpp"
  append(L", treeBuilder");
                                                            #line 499 "PrintGo.cpp.template"
                                                              }
                                                            #line 741 "PrintGo.cpp"
  append(L"})\n");
  append(L"}");
                                                            #line 501 "PrintGo.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 748 "PrintGo.cpp"
  append(L"\n");
  append(L"func (this *");
                                                            #line 505 "PrintGo.cpp.template"
                                                     print(className.c_str());
                                                            #line 753 "PrintGo.cpp"
  append(L") resolve(thread *ParsingThread, other *ParsingThread) *ParsingThread {");
                                                            #line 506 "PrintGo.cpp.template"
                                                                                               if (tree)
                                                              {
                                                            #line 758 "PrintGo.cpp"
  append(L"\n");
  append(L"  a := thread.stack\n");
  append(L"  b := other.stack\n");
  append(L"  begin := a.pos\n");
  append(L"  for a != b && a != nil && b != nil {\n");
  append(L"    begin = a.pos\n");
  append(L"    a = a.link\n");
  append(L"    b = b.link\n");
  append(L"  }");
                                                            #line 516 "PrintGo.cpp.template"
                                  }
                                                            #line 770 "PrintGo.cpp"
  append(L"\n");
  append(L"  if other.eventCount < thread.eventCount {\n");
  append(L"    thread = other\n");
  append(L"  }");
                                                            #line 520 "PrintGo.cpp.template"
                                  if (tree)
                                                              {
                                                            #line 778 "PrintGo.cpp"
  append(L"\n");
  append(L"  thread.addAmbiguity(begin, thread.e0)");
                                                            #line 523 "PrintGo.cpp.template"
                                                                      }
                                                            #line 783 "PrintGo.cpp"
  append(L"\n");
  append(L"  return thread\n");
  append(L"}");
                                                            #line 526 "PrintGo.cpp.template"
                                                              }
                                                              }

                                                            void PrintGo::openThread()
                                                            {
                                                            #line 793 "PrintGo.cpp"
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
  append(L"  return pq[0]\n");
  append(L"}\n");
  append(L"\n");
  append(L"type ParsingThread struct {\n");
  append(L"  parser *");
                                                            #line 570 "PrintGo.cpp.template"
                                                              print(className.c_str());
                                                            #line 836 "PrintGo.cpp"
  append(L"\n");
  append(L"  threads *PriorityQueue\n");
  append(L"  accepted bool\n");
  append(L"  stack *StackNode\n");
  append(L"  state int\n");
  append(L"  action int\n");
  append(L"  target int");
                                                            #line 577 "PrintGo.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 847 "PrintGo.cpp"
  append(L"\n");
  append(L"  deferredEvent DeferredEvent");
                                                            #line 580 "PrintGo.cpp.template"
                                                              }
                                                              if (hasCustomCode)
                                                              {
                                                            #line 854 "PrintGo.cpp"
  append(L"\n");
  append(L"  deferredCode *DeferredCode");
                                                            #line 584 "PrintGo.cpp.template"
                                                              }
                                                            #line 859 "PrintGo.cpp"
  append(L"\n");
  append(L"  id int");
                                                            #line 586 "PrintGo.cpp.template"
                                                           if (minimalAmbiguity)
                                                              {
                                                            #line 865 "PrintGo.cpp"
  append(L"\n");
  append(L"  eventCount int");
                                                            #line 589 "PrintGo.cpp.template"
                                                                   }
                                                              printTokenVars();
                                                            #line 871 "PrintGo.cpp"
  append(L"\n");
  append(L"  begin int\n");
  append(L"  end int\n");
  append(L"}\n");
  append(L"\n");
  append(L"func (this *ParsingThread) open(initialState int");
                                                            #line 596 "PrintGo.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 881 "PrintGo.cpp"
  append(L", eh BottomUpEventHandler");
                                                            #line 598 "PrintGo.cpp.template"
                                                              }
                                                            #line 885 "PrintGo.cpp"
  append(L", t int) *PriorityQueue {\n");
  append(L"  this.accepted = false\n");
  append(L"  this.target = t");
                                                            #line 601 "PrintGo.cpp.template"
                                                                    if (minimalAmbiguity)
                                                              {
                                                            #line 892 "PrintGo.cpp"
  append(L"\n");
  append(L"  this.eventCount = 0");
                                                            #line 604 "PrintGo.cpp.template"
                                                                        }
                                                              if (tree)
                                                              {
                                                            #line 899 "PrintGo.cpp"
  append(L"\n");
  append(L"  this.eventHandler = eh\n");
  append(L"  if this.eventHandler != nil {\n");
  append(L"    this.eventHandler.Reset(this.parser.input)\n");
  append(L"  }\n");
  append(L"  this.deferredEvent = nil");
                                                            #line 612 "PrintGo.cpp.template"
                                                              }
                                                              if (hasCustomCode && useGlr)
                                                              {
                                                            #line 910 "PrintGo.cpp"
  append(L"\n");
  append(L"  this.deferredCode = nil");
                                                            #line 616 "PrintGo.cpp.template"
                                                              }
                                                            #line 915 "PrintGo.cpp"
  append(L"\n");
  append(L"  this.stack = &StackNode{-1, ");
                                                            #line 618 "PrintGo.cpp.template"
                                                              if (grammar->states->hasLookback)
                                                              {
                                                            #line 921 "PrintGo.cpp"
  append(L"0, ");
                                                            #line 620 "PrintGo.cpp.template"
                                                              }
                                                            #line 925 "PrintGo.cpp"
  append(L"this.e0, nil}\n");
  append(L"  this.state = initialState\n");
  append(L"  this.action = this.predict(initialState)");
                                                            #line 623 "PrintGo.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 932 "PrintGo.cpp"
  append(L"\n");
  append(L"  this.bw = this.e0\n");
  append(L"  this.bs = this.e0\n");
  append(L"  this.es = this.e0");
                                                            #line 628 "PrintGo.cpp.template"
                                                              }
                                                            #line 939 "PrintGo.cpp"
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
                                                            #line 639 "PrintGo.cpp.template"
                                                                               if (minimalAmbiguity)
                                                              {
                                                            #line 954 "PrintGo.cpp"
  append(L"\n");
  append(L"  this.eventCount = other.eventCount");
                                                            #line 642 "PrintGo.cpp.template"
                                                                                       }
                                                              if (tree)
                                                              {
                                                            #line 961 "PrintGo.cpp"
  append(L"\n");
  append(L"  this.bs = other.bs\n");
  append(L"  this.es = other.es\n");
  append(L"  this.bw = other.bw\n");
  append(L"  this.eventHandler = other.eventHandler\n");
  append(L"  this.deferredEvent = other.deferredEvent");
                                                            #line 650 "PrintGo.cpp.template"
                                                              }
                                                              if (hasCustomCode)
                                                              {
                                                            #line 972 "PrintGo.cpp"
  append(L"\n");
  append(L"  this.deferredCode = other.deferredCode");
                                                            #line 654 "PrintGo.cpp.template"
                                                              }
                                                            #line 977 "PrintGo.cpp"
  append(L"\n");
  append(L"  this.parser.maxId++\n");
  append(L"  this.id = this.parser.maxId\n");
  append(L"  this.threads = other.threads\n");
  append(L"  this.state = other.state\n");
  append(L"  this.stack = other.stack\n");
  append(L"  this.b0 = other.b0\n");
  append(L"  this.e0 = other.e0");
                                                            #line 662 "PrintGo.cpp.template"
                                                              for (size_t i = 1; i <= grammar->k; ++i)
                                                              {
                                                                const wchar_t *iString = format.toString<wchar_t>(i);
                                                            #line 990 "PrintGo.cpp"
  append(L"\n");
  append(L"  this.l");
                                                            #line 666 "PrintGo.cpp.template"
                                                                print(iString);
                                                            #line 995 "PrintGo.cpp"
  append(L" = other.l");
                                                            #line 667 "PrintGo.cpp.template"
                                                                print(iString);
                                                            #line 999 "PrintGo.cpp"
  append(L"\n");
  append(L"  this.b");
                                                            #line 669 "PrintGo.cpp.template"
                                                                print(iString);
                                                            #line 1004 "PrintGo.cpp"
  append(L" = other.b");
                                                            #line 670 "PrintGo.cpp.template"
                                                                print(iString);
                                                            #line 1008 "PrintGo.cpp"
  append(L"\n");
  append(L"  this.e");
                                                            #line 672 "PrintGo.cpp.template"
                                                                print(iString);
                                                            #line 1013 "PrintGo.cpp"
  append(L" = other.e");
                                                            #line 673 "PrintGo.cpp.template"
                                                                print(iString);
                                                              }
                                                            #line 1018 "PrintGo.cpp"
  append(L"\n");
  append(L"  this.end = other.end\n");
  append(L"  return this\n");
  append(L"}\n");
  append(L"\n");
                                                            #line 680 "PrintGo.cpp.template"
                                                              if (minimalAmbiguity && tree)
                                                              {
                                                            #line 1027 "PrintGo.cpp"
  append(L"\n");
  append(L"func (this *ParsingThread) addAmbiguity(begin int, end int) {\n");
  append(L"  if this.eventHandler != nil {\n");
  append(L"    this.deferredEvent = &AmbiguityEvent{&AbstractDeferredEvent{this.deferredEvent, \"\", begin, end}}\n");
  append(L"  }\n");
  append(L"}\n");
  append(L"\n");
                                                            #line 689 "PrintGo.cpp.template"
                                                              }
                                                            #line 1037 "PrintGo.cpp"
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
                                                            #line 729 "PrintGo.cpp.template"
                                                              beginPublic();
                                                            }

                                                            void PrintGo::printFlush(int i, bool withinThread)
                                                            {
                                                              if (trace)
                                                              {
                                                                increaseIndent(i);
                                                            #line 1087 "PrintGo.cpp"
  append(L"\n");
  append(L"flushTrace();");
                                                            #line 738 "PrintGo.cpp.template"
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
                                                            #line 1103 "PrintGo.cpp"
  append(L"\n");
  append(L"func (this *");
                                                            #line 751 "PrintGo.cpp.template"
                                                              print(clazz);
                                                            #line 1108 "PrintGo.cpp"
  append(L") ");
                                                            #line 752 "PrintGo.cpp.template"
                                                              wchar_t initial[2] = {name[0], 0};
                                                              if (wcscmp(visibility, publ()) == 0) initial[0] = towupper(initial[0]);
                                                              print(initial);
                                                              print(name + 1);
                                                            #line 1115 "PrintGo.cpp"
  append(L"(");
                                                            #line 756 "PrintGo.cpp.template"
                                                              printArgs(args);
                                                            #line 1119 "PrintGo.cpp"
  append(L")");
                                                            #line 757 "PrintGo.cpp.template"
                                                              if (wcscmp(type, voidType()))
                                                              {
                                                            #line 1124 "PrintGo.cpp"
  append(L" ");
                                                            #line 759 "PrintGo.cpp.template"
                                                                print(WString(type).rtrim().c_str());
                                                              }
                                                            }

                                                            void PrintGo::privateVars()
                                                            {
                                                              if (trace)
                                                              {
                                                            #line 1135 "PrintGo.cpp"
  append(L"\n");
  append(L"func (this *");
                                                            #line 768 "PrintGo.cpp.template"
                                                                print(useGlr ? L"ParsingThread" : className.c_str());
                                                            #line 1140 "PrintGo.cpp"
  append(L") lookaheadString() string {\n");
  append(L"  result := \"\"");
                                                            #line 770 "PrintGo.cpp.template"
                                                                for (size_t i = 1; i <= grammar->k; ++i)
                                                                {
                                                            #line 1146 "PrintGo.cpp"
  append(L"\n");
  append(L"  if this.l");
                                                            #line 773 "PrintGo.cpp.template"
                                                                  print(format.toString<wchar_t>(i));
                                                            #line 1151 "PrintGo.cpp"
  append(L" > 0 {\n");
  append(L"    result += ");
                                                            #line 775 "PrintGo.cpp.template"
                                                                  if (i != 1)
                                                                  {
                                                            #line 1157 "PrintGo.cpp"
  append(L"\" \" + ");
                                                            #line 777 "PrintGo.cpp.template"
                                                                  }
                                                            #line 1161 "PrintGo.cpp"
  append(L"token[this.l");
                                                            #line 778 "PrintGo.cpp.template"
                                                                  print(format.toString<wchar_t>(i));
                                                            #line 1165 "PrintGo.cpp"
  append(L"]");
                                                            #line 779 "PrintGo.cpp.template"
                                                                  increaseIndent();
                                                                }
                                                                for (size_t i = 1; i <= grammar->k; ++i)
                                                                {
                                                                  decreaseIndent();
                                                            #line 1173 "PrintGo.cpp"
  append(L"\n");
  append(L"  }");
                                                            #line 785 "PrintGo.cpp.template"
                                                                }
                                                            #line 1178 "PrintGo.cpp"
  append(L"\n");
  append(L"  return result\n");
  append(L"}\n");
                                                            #line 789 "PrintGo.cpp.template"
                                                              }
                                                              if (memoization)
                                                              {
                                                                int bits = Math::bits(grammar->conflictCount);
                                                            #line 1187 "PrintGo.cpp"
  append(L"\n");
  append(L"func (this *");
                                                            #line 794 "PrintGo.cpp.template"
                                                                print(className.c_str());
                                                            #line 1192 "PrintGo.cpp"
  append(L") memoize(i int, e int, v int) {\n");
  append(L"  this.memo[(e << ");
                                                            #line 796 "PrintGo.cpp.template"
                                                                print(format.toString<wchar_t>(bits));
                                                            #line 1197 "PrintGo.cpp"
  append(L") + i] = v\n");
  append(L"}\n");
  append(L"\n");
  append(L"func (this *");
                                                            #line 800 "PrintGo.cpp.template"
                                                                print(className.c_str());
                                                            #line 1204 "PrintGo.cpp"
  append(L") memoized(i int, e int) int {\n");
  append(L"  return this.memo[(e << ");
                                                            #line 802 "PrintGo.cpp.template"
                                                                print(format.toString<wchar_t>(bits));
                                                            #line 1209 "PrintGo.cpp"
  append(L") + i]\n");
  append(L"}\n");
                                                            #line 805 "PrintGo.cpp.template"
                                                              }
                                                            #line 1214 "PrintGo.cpp"
  append(L"\n");
  append(L"type ");
                                                            #line 807 "PrintGo.cpp.template"
                                                              print(className.c_str());
                                                            #line 1219 "PrintGo.cpp"
  append(L" struct {");
                                                            #line 808 "PrintGo.cpp.template"
                                                              if (useGlr)
                                                              {
                                                            #line 1224 "PrintGo.cpp"
  append(L"\n");
  append(L"  thread *ParsingThread\n");
  append(L"  input string");
                                                            #line 812 "PrintGo.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 1231 "PrintGo.cpp"
  append(L"\n");
  append(L"  eventHandler BottomUpEventHandler");
                                                            #line 815 "PrintGo.cpp.template"
                                                                }
                                                            #line 1236 "PrintGo.cpp"
  append(L"\n");
  append(L"  size int\n");
  append(L"  maxId int");
                                                            #line 818 "PrintGo.cpp.template"
                                                              }
                                                              else
                                                              {
                                                                printTokenVars();
                                                              }
                                                              if (memoization)
                                                              {
                                                            #line 1248 "PrintGo.cpp"
  append(L"\n");
  append(L"  memo map[int]int");
                                                            #line 826 "PrintGo.cpp.template"
                                                                if (grammar->noThrow)
                                                                {
                                                            #line 1254 "PrintGo.cpp"
  append(L"\n");
  append(L"  viable bool");
                                                            #line 829 "PrintGo.cpp.template"
                                                                }
                                                              }
                                                            }

                                                            void PrintGo::printFileProcessor()
                                                            {
                                                            #line 1264 "PrintGo.cpp"
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
                                                            #line 844 "PrintGo.cpp.template"
                                                              print(className.c_str());
                                                              if (tree)
                                                              {
                                                            #line 1279 "PrintGo.cpp"
  append(L"\n");
  append(L"  contentCounter *ContentCounter");
                                                            #line 848 "PrintGo.cpp.template"
                                                                if (isLrParser)
                                                                {
                                                            #line 1285 "PrintGo.cpp"
  append(L"\n");
  append(L"  parseTreeBuilder *ParseTreeBuilder");
                                                            #line 851 "PrintGo.cpp.template"
                                                                }
                                                              }
                                                            #line 1291 "PrintGo.cpp"
  append(L"\n");
  append(L"}\n");
  append(L"\n");
  append(L"func main() {\n");
  append(L"  if len(os.Args) < 2 {\n");
  append(L"    os.Stderr.WriteString(\"Usage: ");
                                                            #line 858 "PrintGo.cpp.template"
                                                              print(className.c_str());
                                                            #line 1300 "PrintGo.cpp"
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
                                                            #line 937 "PrintGo.cpp.template"
                                                                  if (useGlr)
                                                                  {
                                                            #line 1383 "PrintGo.cpp"
  append(L".thread");
                                                            #line 939 "PrintGo.cpp.template"
                                                                  }
                                                            #line 1387 "PrintGo.cpp"
  append(L".Reset(0, 0, 0)\n");
  append(L"            pe := job.parser.Parse_");
                                                            #line 941 "PrintGo.cpp.template"
                                                                  print(Format::acceptableName<WString>(grammar->startSymbol()->name).c_str());
                                                            #line 1392 "PrintGo.cpp"
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
                                                            #line 953 "PrintGo.cpp.template"
                                                                  if (tree)
                                                                  {
                                                                    if (isLrParser)
                                                                    {
                                                            #line 1410 "PrintGo.cpp"
  append(L"\n");
  append(L"            job.parseTreeBuilder.Serialize(job.contentCounter)");
                                                            #line 958 "PrintGo.cpp.template"
                                                                    }
                                                            #line 1415 "PrintGo.cpp"
  append(L"\n");
  append(L"            if (job.contentCounter.getLength() != len(job.input)) {\n");
  append(L"              panic(\"content counter saw \" + strconv.Itoa(job.contentCounter.getLength()) + \", but input length is \" + strconv.Itoa(len(job.input)))\n");
  append(L"            }");
                                                            #line 962 "PrintGo.cpp.template"
                                                                  }
                                                            #line 1422 "PrintGo.cpp"
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
                                                            #line 1000 "PrintGo.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 1463 "PrintGo.cpp"
  append(L"\n");
  append(L"  contentCounter := new(ContentCounter)");
                                                            #line 1003 "PrintGo.cpp.template"
                                                                if (isLrParser)
                                                                {
                                                            #line 1469 "PrintGo.cpp"
  append(L"\n");
  append(L"  parseTreeBuilder := new(ParseTreeBuilder)");
                                                            #line 1006 "PrintGo.cpp.template"
                                                                }
                                                              }
                                                            #line 1475 "PrintGo.cpp"
  append(L"\n");
  append(L"  parsers = append(parsers, &ParseJob{name, content, NewParser(content");
                                                            #line 1010 "PrintGo.cpp.template"
                                                              if (tree)
                                                              {
                                                                if (isLrParser)
                                                                {
                                                            #line 1483 "PrintGo.cpp"
  append(L", parseTreeBuilder");
                                                            #line 1014 "PrintGo.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1489 "PrintGo.cpp"
  append(L", contentCounter");
                                                            #line 1017 "PrintGo.cpp.template"
                                                                }
                                                              }
                                                            #line 1494 "PrintGo.cpp"
  append(L")");
                                                            #line 1019 "PrintGo.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 1499 "PrintGo.cpp"
  append(L", contentCounter");
                                                            #line 1021 "PrintGo.cpp.template"
                                                                if (isLrParser)
                                                                {
                                                            #line 1504 "PrintGo.cpp"
  append(L", parseTreeBuilder");
                                                            #line 1023 "PrintGo.cpp.template"
                                                                }
                                                              }
                                                            #line 1509 "PrintGo.cpp"
  append(L"})\n");
  append(L"}\n");
                                                            #line 1028 "PrintGo.cpp.template"
                                                            }

                                                            void PrintGo::printReadMethod()
                                                            {
                                                            #line 1517 "PrintGo.cpp"
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
                                                            #line 1047 "PrintGo.cpp.template"
                                                            }

                                                            void PrintGo::printInterface()
                                                            {
                                                              if (! packageName.empty())
                                                              {
                                                            #line 1540 "PrintGo.cpp"
  append(L"\n");
  append(L"package ");
                                                            #line 1054 "PrintGo.cpp.template"
                                                                print(packageName.c_str());
                                                            #line 1545 "PrintGo.cpp"
  append(L";\n");
                                                            #line 1056 "PrintGo.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                                if (main || useGlr)
                                                                {
                                                            #line 1553 "PrintGo.cpp"
  append(L"\n");
  append(L"import java.io.IOException;\n");
  append(L"import java.io.Writer;\n");
                                                            #line 1064 "PrintGo.cpp.template"
                                                                }
                                                            #line 1559 "PrintGo.cpp"
  append(L"\n");
  append(L"import java.util.Arrays;");
                                                            #line 1066 "PrintGo.cpp.template"
                                                              }
                                                            #line 1564 "PrintGo.cpp"
  append(L"\n");
  append(L"public interface ");
                                                            #line 1068 "PrintGo.cpp.template"
                                                              print(className.c_str());
                                                            #line 1569 "PrintGo.cpp"
  append(L"\n");
  append(L"{\n");
  append(L"  public void initialize(CharSequence input");
                                                            #line 1071 "PrintGo.cpp.template"
                                                              if (noLexer)
                                                              {
                                                            #line 1576 "PrintGo.cpp"
  append(L", Lexer l");
                                                            #line 1073 "PrintGo.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                            #line 1582 "PrintGo.cpp"
  append(L", ");
                                                            #line 1076 "PrintGo.cpp.template"
                                                                if (isLrParser)
                                                                {
                                                            #line 1587 "PrintGo.cpp"
  append(L"BottomUp");
                                                            #line 1079 "PrintGo.cpp.template"
                                                                }
                                                            #line 1591 "PrintGo.cpp"
  append(L"EventHandler eh");
                                                            #line 1081 "PrintGo.cpp.template"
                                                              }
                                                            #line 1595 "PrintGo.cpp"
  append(L");\n");
  append(L"  public void parse();\n");
  append(L"  public void Reset();\n");
  append(L"  public String getErrorMessage(ParseException e);\n");
                                                            #line 1086 "PrintGo.cpp.template"
                                                              printParseException();
                                                              printEventHandlerImplementation();
                                                            #line 1603 "PrintGo.cpp"
  append(L"}\n");
                                                            #line 1089 "PrintGo.cpp.template"
                                                            }

                                                            void PrintGo::printParseException()
                                                            {
                                                            #line 1610 "PrintGo.cpp"
  append(L"\n");
  append(L"type ParseError struct {\n");
  append(L"  begin int\n");
  append(L"  end int\n");
  append(L"  state int\n");
  append(L"  offending int\n");
  append(L"  expected int");
                                                            #line 1099 "PrintGo.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 1621 "PrintGo.cpp"
  append(L"\n");
  append(L"  ambiguousInput bool");
                                                            #line 1102 "PrintGo.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 1627 "PrintGo.cpp"
  append(L"\n");
  append(L"  ambiguityDescriptor *ParseTreeBuilder");
                                                            #line 1105 "PrintGo.cpp.template"
                                                                }
                                                              }
                                                            #line 1633 "PrintGo.cpp"
  append(L"\n");
  append(L"}\n");
  append(L"\n");
  append(L"func (this ParseError) Error() string {\n");
  append(L"  if ");
                                                            #line 1111 "PrintGo.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 1642 "PrintGo.cpp"
  append(L"this.ambiguousInput {\n");
  append(L"    return \"ambiguous input\"\n");
  append(L"  } else if ");
                                                            #line 1115 "PrintGo.cpp.template"
                                                              }
                                                            #line 1648 "PrintGo.cpp"
  append(L"this.offending < 0 {\n");
  append(L"    return \"lexical analysis failed\"\n");
  append(L"  } else {\n");
  append(L"    return \"syntax error\"\n");
  append(L"  }\n");
  append(L"}\n");
                                                            #line 1122 "PrintGo.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 1658 "PrintGo.cpp"
  append(L"\n");
  append(L"func (this *ParseError) Serialize(eventHandler EventHandler) {");
                                                            #line 1125 "PrintGo.cpp.template"
                                                                if (rejectsAmbiguity())
                                                                {
                                                            #line 1664 "PrintGo.cpp"
  append(L"\n");
  append(L"  this.ambiguityDescriptor.Serialize(eventHandler)");
                                                            #line 1128 "PrintGo.cpp.template"
                                                                }
                                                            #line 1669 "PrintGo.cpp"
  append(L"\n");
  append(L"}\n");
                                                            #line 1131 "PrintGo.cpp.template"
                                                              }
                                                            #line 1674 "PrintGo.cpp"
  append(L"\n");
  append(L"func (this *ParseError) GetBegin() int {return this.begin}\n");
  append(L"func (this *ParseError) GetEnd() int {return this.end}\n");
  append(L"func (this *ParseError) GetState() int {return this.state}\n");
  append(L"func (this *ParseError) GetOffending() int {return this.offending}\n");
  append(L"func (this *ParseError) GetExpected() int {return this.expected}\n");
  append(L"func (this *ParseError) IsAmbiguousInput() bool {return ");
                                                            #line 1138 "PrintGo.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 1685 "PrintGo.cpp"
  append(L"this.ambiguousInput");
                                                            #line 1141 "PrintGo.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 1691 "PrintGo.cpp"
  append(L"false");
                                                            #line 1145 "PrintGo.cpp.template"
                                                              }
                                                            #line 1695 "PrintGo.cpp"
  append(L"}\n");
                                                            #line 1147 "PrintGo.cpp.template"
                                                              if (noLexer)
                                                              {
                                                            #line 1700 "PrintGo.cpp"
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
                                                            #line 1162 "PrintGo.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                            #line 1718 "PrintGo.cpp"
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
                                                            #line 1279 "PrintGo.cpp.template"
                                                                if (isLrParser)
                                                                {
                                                            #line 1836 "PrintGo.cpp"
  append(L"\n");
  append(L"type BottomUpEventHandler interface {\n");
  append(L"  Reset(input string)\n");
  append(L"  Nonterminal(name string, begin int, end int, count int)\n");
  append(L"  Terminal(name string, begin int, end int)");
                                                            #line 1285 "PrintGo.cpp.template"
                                                      if (minimalAmbiguity)
                                                              {
                                                            #line 1845 "PrintGo.cpp"
  append(L"\n");
  append(L"  Ambiguity(begin int, end int)");
                                                            #line 1288 "PrintGo.cpp.template"
                                          }
                                                            #line 1850 "PrintGo.cpp"
  append(L"\n");
  append(L"}\n");
                                                            #line 1291 "PrintGo.cpp.template"
                                                                }
                                                              }
                                                            }

                                                            void PrintGo::printEventHandlerImplementation()
                                                            {
                                                              if (tree)
                                                              {
                                                                if (main || useGlr)
                                                                {
                                                            #line 1864 "PrintGo.cpp"
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
                                                            #line 1392 "PrintGo.cpp.template"
                                                                }
                                                                if (performanceTest)
                                                                {
                                                            #line 1960 "PrintGo.cpp"
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
                                                            #line 1410 "PrintGo.cpp.template"
                                                                }
                                                                if (isLrParser)
                                                                {
                                                            #line 1979 "PrintGo.cpp"
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
                                                            #line 1427 "PrintGo.cpp.template"
                                                                if (rejectsAmbiguity())
                                                                {
                                                            #line 1997 "PrintGo.cpp"
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
                                                            #line 1441 "PrintGo.cpp.template"
                                                            }
                                                            #line 2013 "PrintGo.cpp"
  append(L"\n");
  append(L"  this.push(&Nonterminal{&AbstractSymbol{name, begin, end}, this.pop(count)})\n");
  append(L"}\n");
  append(L"\n");
  append(L"func (this *ParseTreeBuilder) Terminal(name string, begin int, end int) {\n");
  append(L"  this.push(&Terminal{&AbstractSymbol{name, begin, end}})\n");
  append(L"}\n");
                                                            #line 1449 "PrintGo.cpp.template"
                                                              if (minimalAmbiguity)
                                                              {
                                                            #line 2024 "PrintGo.cpp"
  append(L"\n");
  append(L"func (this *ParseTreeBuilder) Ambiguity(begin int, end int) {\n");
  append(L"}\n");
                                                            #line 1454 "PrintGo.cpp.template"
                                                              }
                                                            #line 2030 "PrintGo.cpp"
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
                                                            #line 1476 "PrintGo.cpp.template"
                                                                }
                                                              }
                                                            }

                                                            void PrintGo::printTokenVars()
                                                            {
                                                            #line 2059 "PrintGo.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 1483 "PrintGo.cpp.template"
                                                              if (! isLrParser && (grammar->k > 1 ||
                                                                                   memoization ||
                                                                                   ! grammar->decisionPoints.empty()))
                                                              {
                                                            #line 2067 "PrintGo.cpp"
  append(L"lk,");
                                                            #line 1487 "PrintGo.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 2073 "PrintGo.cpp"
  append(L"   ");
                                                            #line 1490 "PrintGo.cpp.template"
                                                              }
                                                            #line 2077 "PrintGo.cpp"
  append(L" b0, e0 int");
                                                            #line 1491 "PrintGo.cpp.template"
                                                              for (size_t k = 1; k <= grammar->k; ++k)
                                                              {
                                                                Format format;
                                                                wchar_t *asString = format.toString<wchar_t>(k);
                                                            #line 2084 "PrintGo.cpp"
  append(L"\n");
  append(L"  l");
                                                            #line 1496 "PrintGo.cpp.template"
                                                                print(asString);
                                                            #line 2089 "PrintGo.cpp"
  append(L", b");
                                                            #line 1497 "PrintGo.cpp.template"
                                                                print(asString);
                                                            #line 2093 "PrintGo.cpp"
  append(L", e");
                                                            #line 1498 "PrintGo.cpp.template"
                                                                print(asString);
                                                            #line 2097 "PrintGo.cpp"
  append(L" int");
                                                            #line 1499 "PrintGo.cpp.template"
                                                              }
                                                              if (hasBacktracking)
                                                              {
                                                            #line 2103 "PrintGo.cpp"
  append(L"\n");
  append(L"  bx, ex, sx, lx, tx int");
                                                            #line 1503 "PrintGo.cpp.template"
                                                              }
                                                              else if (isLrParser && ! useGlr)
                                                              {
                                                            #line 2110 "PrintGo.cpp"
  append(L"\n");
  append(L"  iStack []int\n");
  append(L"  top int");
                                                            #line 1508 "PrintGo.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                                if (isLrParser)
                                                                {
                                                                  if (useGlr)
                                                                  {
                                                            #line 2122 "PrintGo.cpp"
  append(L"\n");
  append(L"  bw, bs, es int");
                                                            #line 1516 "PrintGo.cpp.template"
                                                                  }
                                                            #line 2127 "PrintGo.cpp"
  append(L"\n");
  append(L"  eventHandler BottomUpEventHandler");
                                                            #line 1518 "PrintGo.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 2134 "PrintGo.cpp"
  append(L"\n");
  append(L"  eventHandler EventHandler");
                                                            #line 1522 "PrintGo.cpp.template"
                                                                }
                                                              }
                                                            }

// End
