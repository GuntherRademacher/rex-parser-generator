// This file was generated on Tue Oct 20, 2026 19:55 (UTC+02) by REx v6.3-SNAPSHOT which is Copyright (c) 1979-2026 by Gunther Rademacher <grd@gmx.net>
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
                                                            #line 27 "PrintGo.cpp.template"
                                                                if (main || performanceTest)
                                                                {
                                                            #line 44 "PrintGo.cpp"
  append(L"\n");
  append(L"  \"io/ioutil\"\n");
  append(L"  \"fmt\"");
                                                            #line 31 "PrintGo.cpp.template"
                                                                }
                                                                if (main || performanceTest || trace)
                                                                {
                                                            #line 52 "PrintGo.cpp"
  append(L"\n");
  append(L"  \"os\"\n");
  append(L"  \"strings\"");
                                                            #line 36 "PrintGo.cpp.template"
                                                                }
                                                                if (performanceTest)
                                                                {
                                                            #line 60 "PrintGo.cpp"
  append(L"\n");
  append(L"  \"path/filepath\"\n");
  append(L"  \"time\"");
                                                            #line 41 "PrintGo.cpp.template"
                                                                }
                                                                if (useGlr)
                                                                {
                                                            #line 68 "PrintGo.cpp"
  append(L"\n");
  append(L"  \"container/heap\"");
                                                            #line 45 "PrintGo.cpp.template"
                                                                }
                                                            #line 73 "PrintGo.cpp"
  append(L"\n");
  append(L")\n");
                                                            #line 48 "PrintGo.cpp.template"
                                                              }
                                                              if (main)
                                                              {
                                                            #line 80 "PrintGo.cpp"
  append(L"\n");
  append(L"func ");
                                                            #line 52 "PrintGo.cpp.template"
                                                                if (packageName.empty() || packageName == L"main")
                                                                {
                                                            #line 86 "PrintGo.cpp"
  append(L"m");
                                                            #line 54 "PrintGo.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 92 "PrintGo.cpp"
  append(L"M");
                                                            #line 57 "PrintGo.cpp.template"
                                                                }
                                                            #line 96 "PrintGo.cpp"
  append(L"ain() {\n");
  append(L"  if len(os.Args) < 2 {\n");
  append(L"    os.Stderr.WriteString(\"Usage: ");
                                                            #line 60 "PrintGo.cpp.template"
                                                                print(className.c_str());
                                                                if (tree)
                                                                {
                                                            #line 104 "PrintGo.cpp"
  append(L" [-i]");
                                                            #line 63 "PrintGo.cpp.template"
                                                                }
                                                            #line 108 "PrintGo.cpp"
  append(L" INPUT...\\n\")\n");
  append(L"    os.Stderr.WriteString(\"\\n\")\n");
  append(L"    os.Stderr.WriteString(\"  parse INPUT, which is either a filename or literal text enclosed in curly braces\\n\")");
                                                            #line 67 "PrintGo.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 115 "PrintGo.cpp"
  append(L"\n");
  append(L"    os.Stderr.WriteString(\"\\n\")\n");
  append(L"    os.Stderr.WriteString(\"  Option:\\n\")\n");
  append(L"    os.Stderr.WriteString(\"    -i     indented parse tree\\n\")");
                                                            #line 72 "PrintGo.cpp.template"
                                                                }
                                                            #line 122 "PrintGo.cpp"
  append(L"\n");
  append(L"  } else {");
                                                            #line 74 "PrintGo.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 128 "PrintGo.cpp"
  append(L"\n");
  append(L"    indent := false");
                                                            #line 77 "PrintGo.cpp.template"
                                                                }
                                                            #line 133 "PrintGo.cpp"
  append(L"\n");
  append(L"    for i := 1; i < len(os.Args); i++ {\n");
  append(L"      arg := os.Args[i]");
                                                            #line 80 "PrintGo.cpp.template"
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
                                                            #line 88 "PrintGo.cpp.template"
                                                                  if (isLrParser)
                                                                  {
                                                            #line 151 "PrintGo.cpp"
  append(L"\n");
  append(L"      b := &ParseTreeBuilder{}");
                                                            #line 91 "PrintGo.cpp.template"
                                                                  }
                                                                }
                                                            #line 157 "PrintGo.cpp"
  append(L"\n");
  append(L"      input := read(arg)\n");
  append(L"      parser := NewParser(input");
                                                            #line 95 "PrintGo.cpp.template"
                                                                if (noLexer)
                                                                {
                                                            #line 164 "PrintGo.cpp"
  append(L", new ");
                                                            #line 97 "PrintGo.cpp.template"
                                                                  print(className.c_str());
                                                            #line 168 "PrintGo.cpp"
  append(L"Lexer()");
                                                            #line 98 "PrintGo.cpp.template"
                                                                }
                                                                if (tree)
                                                                {
                                                            #line 174 "PrintGo.cpp"
  append(L", ");
                                                            #line 101 "PrintGo.cpp.template"
                                                                  if (isLrParser)
                                                                  {
                                                            #line 179 "PrintGo.cpp"
  append(L"b");
                                                            #line 103 "PrintGo.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 185 "PrintGo.cpp"
  append(L"s");
                                                            #line 106 "PrintGo.cpp.template"
                                                                  }
                                                                }
                                                            #line 190 "PrintGo.cpp"
  append(L")");
                                                            #line 108 "PrintGo.cpp.template"
                                                                if (trace)
                                                                {
                                                            #line 195 "PrintGo.cpp"
  append(L"\n");
  append(L"      writeTrace(\"<?xml version=\\\"1.0\\\" encoding=\\\"UTF-8\\\"?\" + \">\\n<trace>\\n\")");
                                                            #line 112 "PrintGo.cpp.template"
                                                                }
                                                            #line 200 "PrintGo.cpp"
  append(L"\n");
  append(L"      pe := parser.");
                                                            #line 114 "PrintGo.cpp.template"
                                                                print(visibilityMethodPrefix());
                                                                print(Format::acceptableName<WString>(grammar->startSymbol()->name).c_str());
                                                            #line 206 "PrintGo.cpp"
  append(L"()");
                                                            #line 116 "PrintGo.cpp.template"
                                                                if (trace)
                                                                {
                                                            #line 211 "PrintGo.cpp"
  append(L"\n");
  append(L"      writeTrace(\"</trace>\\n\")");
                                                            #line 119 "PrintGo.cpp.template"
                                                                }
                                                            #line 216 "PrintGo.cpp"
  append(L"\n");
  append(L"      if pe != nil {");
                                                            #line 121 "PrintGo.cpp.template"
                                                                if (rejectsAmbiguity() && tree)
                                                                {
                                                            #line 222 "PrintGo.cpp"
  append(L"\n");
  append(L"        if pe.IsAmbiguousInput() {\n");
  append(L"          pe.Serialize(s)\n");
  append(L"          fmt.Println()\n");
  append(L"        }");
                                                            #line 127 "PrintGo.cpp.template"
                                                                }
                                                            #line 230 "PrintGo.cpp"
  append(L"\n");
  append(L"        panic(fmt.Sprintf(\"ParseError while processing %s:\\n%s\\n\", arg, parser.GetErrorMessage(*pe)))\n");
  append(L"      }");
                                                            #line 130 "PrintGo.cpp.template"
                                                                if (tree && isLrParser)
                                                                {
                                                            #line 237 "PrintGo.cpp"
  append(L" else {\n");
  append(L"        b.Serialize(s)\n");
  append(L"      }");
                                                            #line 134 "PrintGo.cpp.template"
                                                                }
                                                            #line 243 "PrintGo.cpp"
  append(L"\n");
  append(L"    }\n");
  append(L"  }\n");
  append(L"}\n");
                                                            #line 139 "PrintGo.cpp.template"
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
                                                            #line 159 "PrintGo.cpp.template"
                                                                print(args.c_str());
                                                            #line 273 "PrintGo.cpp"
  append(L") *");
                                                            #line 160 "PrintGo.cpp.template"
                                                                print(className.c_str());
                                                            #line 277 "PrintGo.cpp"
  append(L" {\n");
  append(L"  parser := new(");
                                                            #line 162 "PrintGo.cpp.template"
                                                                print(className.c_str());
                                                            #line 282 "PrintGo.cpp"
  append(L")\n");
  append(L"  parser.Initialize(input");
                                                            #line 164 "PrintGo.cpp.template"
                                                                if (noLexer)
                                                                {
                                                            #line 288 "PrintGo.cpp"
  append(L", lexer");
                                                            #line 166 "PrintGo.cpp.template"
                                                                }
                                                                if (tree)
                                                                {
                                                            #line 294 "PrintGo.cpp"
  append(L", t");
                                                            #line 169 "PrintGo.cpp.template"
                                                                }
                                                            #line 298 "PrintGo.cpp"
  append(L")\n");
  append(L"  return parser\n");
  append(L"}\n");
                                                            #line 173 "PrintGo.cpp.template"
                                                              }
                                                            }

                                                            void PrintGo::openStackNode()
                                                            {
                                                            #line 308 "PrintGo.cpp"
  append(L"\n");
  append(L"type StackNode struct {\n");
  append(L"  state int");
                                                            #line 180 "PrintGo.cpp.template"
                                                              if (grammar->states->hasLookback)
                                                              {
                                                            #line 315 "PrintGo.cpp"
  append(L"\n");
  append(L"  code int");
                                                            #line 183 "PrintGo.cpp.template"
                                                              }
                                                              if (tree || useGlr)
                                                              {
                                                            #line 322 "PrintGo.cpp"
  append(L"\n");
  append(L"  pos int");
                                                            #line 187 "PrintGo.cpp.template"
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
                                                            #line 200 "PrintGo.cpp.template"
                                                              if (grammar->states->hasLookback)
                                                              {
                                                            #line 344 "PrintGo.cpp"
  append(L"\n");
  append(L"    if lhs.code != rhs.code {\n");
  append(L"      return false\n");
  append(L"    }");
                                                            #line 205 "PrintGo.cpp.template"
                                                              }
                                                              if (tree || useGlr)
                                                              {
                                                            #line 353 "PrintGo.cpp"
  append(L"\n");
  append(L"    if lhs.pos != rhs.pos {\n");
  append(L"      return false\n");
  append(L"    }");
                                                            #line 211 "PrintGo.cpp.template"
                                                              }
                                                            #line 360 "PrintGo.cpp"
  append(L"\n");
  append(L"    lhs = lhs.link\n");
  append(L"    rhs = rhs.link\n");
  append(L"  }\n");
  append(L"  return lhs == rhs\n");
  append(L"}\n");
                                                            #line 218 "PrintGo.cpp.template"
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
                                                            #line 233 "PrintGo.cpp.template"
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
  append(L"    ");
                                                            #line 284 "PrintGo.cpp.template"
                                                                if (shiftAmbiguity)
                                                                {
                                                            #line 441 "PrintGo.cpp"
  append(L"if eventHandler != nil {\n");
  append(L"      ");
                                                            #line 287 "PrintGo.cpp.template"
                                                                }
                                                            #line 446 "PrintGo.cpp"
  append(L"current.execute(eventHandler)");
                                                            #line 288 "PrintGo.cpp.template"
                                                                if (shiftAmbiguity)
                                                                {
                                                            #line 451 "PrintGo.cpp"
  append(L"\n");
  append(L"    }");
                                                            #line 291 "PrintGo.cpp.template"
                                                                }
                                                            #line 456 "PrintGo.cpp"
  append(L"\n");
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
                                                            #line 334 "PrintGo.cpp.template"
                                                                if (resolvesAmbiguity)
                                                                {
                                                            #line 502 "PrintGo.cpp"
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
                                                            #line 349 "PrintGo.cpp.template"
                                                                }
                                                              }
                                                            #line 519 "PrintGo.cpp"
  append(L"\n");
  append(L"const (\n");
  append(L"  PARSING = 0\n");
  append(L"  ACCEPTED = 1\n");
  append(L"  ERROR = 2\n");
  append(L")\n");
  append(L"\n");
  append(L"func (this *");
                                                            #line 358 "PrintGo.cpp.template"
                                                              print(className.c_str());
                                                            #line 530 "PrintGo.cpp"
  append(L") parse(target int, initialState int, ");
                                                            #line 359 "PrintGo.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 535 "PrintGo.cpp"
  append(L"eventHandler BottomUpEventHandler, ");
                                                            #line 362 "PrintGo.cpp.template"
                                                              }
                                                            #line 539 "PrintGo.cpp"
  append(L"thread *ParsingThread) *ParsingThread {\n");
  append(L"  threads := thread.open(initialState");
                                                            #line 364 "PrintGo.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 545 "PrintGo.cpp"
  append(L", eventHandler");
                                                            #line 366 "PrintGo.cpp.template"
                                                              }
                                                            #line 549 "PrintGo.cpp"
  append(L", target)\n");
  append(L"  for {\n");
  append(L"    thread = heap.Pop(threads).(*ParsingThread)\n");
  append(L"    if (thread.accepted) {");
                                                            #line 370 "PrintGo.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 557 "PrintGo.cpp"
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
                                                            #line 382 "PrintGo.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 572 "PrintGo.cpp"
  append(L", thread.deferredEvent, other.deferredEvent");
                                                            #line 385 "PrintGo.cpp.template"
                                                                }
                                                            #line 576 "PrintGo.cpp"
  append(L")\n");
  append(L"      }");
                                                            #line 387 "PrintGo.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 583 "PrintGo.cpp"
  append(L"\n");
  append(L"      for ! threads.isEmpty() {\n");
  append(L"        other := heap.Pop(threads).(*ParsingThread)\n");
  append(L"        if thread.e0 < other.e0 {\n");
  append(L"          thread = other\n");
  append(L"        } else {\n");
  append(L"          thread = this.resolve(thread, other)\n");
  append(L"        }\n");
  append(L"      }");
                                                            #line 398 "PrintGo.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                            #line 597 "PrintGo.cpp"
  append(L"\n");
  append(L"      if thread.deferredEvent != nil {\n");
  append(L"        release(thread.deferredEvent, eventHandler)\n");
  append(L"        thread.deferredEvent = nil\n");
  append(L"      }");
                                                            #line 405 "PrintGo.cpp.template"
                                                              }
                                                              if (hasCustomCode)
                                                              {
                                                            #line 607 "PrintGo.cpp"
  append(L"\n");
  append(L"      thread.ExecuteDeferredCode()");
                                                            #line 409 "PrintGo.cpp.template"
                                                              }
                                                            #line 612 "PrintGo.cpp"
  append(L"\n");
  append(L"      return thread\n");
  append(L"    }\n");
  append(L"\n");
                                                            #line 414 "PrintGo.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 620 "PrintGo.cpp"
  append(L"    if ! threads.isEmpty() {\n");
  append(L"      if threads.peek().equals(thread) {\n");
  append(L"        this.rejectAmbiguity(thread.stack.pos, thread.e0");
                                                            #line 418 "PrintGo.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 627 "PrintGo.cpp"
  append(L", thread.deferredEvent, threads.peek().deferredEvent");
                                                            #line 421 "PrintGo.cpp.template"
                                                                }
                                                            #line 631 "PrintGo.cpp"
  append(L")\n");
  append(L"      }");
                                                            #line 423 "PrintGo.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 638 "PrintGo.cpp"
  append(L"    for ! threads.isEmpty() && threads.peek().equals(thread) {\n");
  append(L"      thread = this.resolve(thread, heap.Pop(threads).(*ParsingThread))\n");
  append(L"    }\n");
  append(L"    if threads.isEmpty() {");
                                                            #line 429 "PrintGo.cpp.template"
                                                              }
                                                              if (tree || hasCustomCode)
                                                              {
                                                                if (rejectsAmbiguity())
                                                                {
                                                            #line 649 "PrintGo.cpp"
  append(L"\n");
  append(L"    } else {");
                                                            #line 435 "PrintGo.cpp.template"
                                                                }
                                                                if (tree)
                                                                {
                                                            #line 656 "PrintGo.cpp"
  append(L"\n");
  append(L"      if thread.deferredEvent != nil {\n");
  append(L"        release(thread.deferredEvent, eventHandler)\n");
  append(L"        thread.deferredEvent = nil\n");
  append(L"      }");
                                                            #line 442 "PrintGo.cpp.template"
                                                                }
                                                                if (hasCustomCode)
                                                                {
                                                            #line 666 "PrintGo.cpp"
  append(L"\n");
  append(L"      thread.ExecuteDeferredCode()");
                                                            #line 446 "PrintGo.cpp.template"
                                                                }
                                                              }
                                                            #line 672 "PrintGo.cpp"
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
                                                            #line 469 "PrintGo.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 698 "PrintGo.cpp"
  append(L",\n");
  append(L"                        false");
                                                            #line 472 "PrintGo.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 704 "PrintGo.cpp"
  append(L",\n");
  append(L"                        nil");
                                                            #line 475 "PrintGo.cpp.template"
                                                                }
                                                              }
                                                            #line 710 "PrintGo.cpp"
  append(L"})\n");
  append(L"    }\n");
  append(L"  }\n");
  append(L"}\n");
  append(L"\n");
                                                            #line 482 "PrintGo.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 719 "PrintGo.cpp"
  append(L"\n");
  append(L"func (this *");
                                                            #line 485 "PrintGo.cpp.template"
                                                                print(className.c_str());
                                                            #line 724 "PrintGo.cpp"
  append(L") rejectAmbiguity(begin int, end int");
                                                            #line 486 "PrintGo.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 729 "PrintGo.cpp"
  append(L", first DeferredEvent, second DeferredEvent");
                                                            #line 489 "PrintGo.cpp.template"
                                                                }
                                                            #line 733 "PrintGo.cpp"
  append(L") {");
                                                            #line 490 "PrintGo.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 738 "PrintGo.cpp"
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
                                                            #line 502 "PrintGo.cpp.template"
                                                                }
                                                            #line 751 "PrintGo.cpp"
  append(L"\n");
  append(L"  panic(&ParseError{begin, end, 1, -1, -1, true");
                                                            #line 504 "PrintGo.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 757 "PrintGo.cpp"
  append(L", treeBuilder");
                                                            #line 506 "PrintGo.cpp.template"
                                                                }
                                                            #line 761 "PrintGo.cpp"
  append(L"})\n");
  append(L"}");
                                                            #line 508 "PrintGo.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 768 "PrintGo.cpp"
  append(L"\n");
  append(L"func (this *");
                                                            #line 512 "PrintGo.cpp.template"
                                                                print(className.c_str());
                                                            #line 773 "PrintGo.cpp"
  append(L") resolve(thread *ParsingThread, other *ParsingThread) *ParsingThread {");
                                                            #line 514 "PrintGo.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 778 "PrintGo.cpp"
  append(L"\n");
  append(L"  a := thread.stack\n");
  append(L"  b := other.stack\n");
  append(L"  begin := a.pos\n");
  append(L"  for a != b && a != nil && b != nil {\n");
  append(L"    begin = a.pos\n");
  append(L"    a = a.link\n");
  append(L"    b = b.link\n");
  append(L"  }");
                                                            #line 524 "PrintGo.cpp.template"
                                                                }
                                                            #line 790 "PrintGo.cpp"
  append(L"\n");
                                                            #line 526 "PrintGo.cpp.template"
                                                                if (shiftAmbiguity)
                                                                {
                                                            #line 795 "PrintGo.cpp"
  append(L"\n");
  append(L"  ea := thread.deferredEvent\n");
  append(L"  eb := other.deferredEvent\n");
  append(L"  lengthA := 0\n");
  append(L"  for e := ea; e != nil; e = e.getLink() {\n");
  append(L"    lengthA++\n");
  append(L"  }\n");
  append(L"  lengthB := 0\n");
  append(L"  for e := eb; e != nil; e = e.getLink() {\n");
  append(L"    lengthB++\n");
  append(L"  }\n");
  append(L"  var ua DeferredEvent\n");
  append(L"  var ub DeferredEvent\n");
  append(L"  for ea != eb {\n");
  append(L"    if lengthA >= lengthB {\n");
  append(L"      ua = ea\n");
  append(L"      ea = ea.getLink()\n");
  append(L"      lengthA--\n");
  append(L"    } else {\n");
  append(L"      ub = eb\n");
  append(L"      eb = eb.getLink()\n");
  append(L"      lengthB--\n");
  append(L"    }\n");
  append(L"  }\n");
  append(L"  _, sa := ua.(*TerminalEvent)\n");
  append(L"  _, sb := ub.(*TerminalEvent)\n");
  append(L"  if sa != sb {\n");
  append(L"    if sb {\n");
  append(L"      thread = other\n");
  append(L"    }\n");
  append(L"  } else if other.eventCount < thread.eventCount {\n");
  append(L"    thread = other\n");
  append(L"  }");
                                                            #line 560 "PrintGo.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 833 "PrintGo.cpp"
  append(L"\n");
  append(L"  if other.eventCount < thread.eventCount {\n");
  append(L"    thread = other\n");
  append(L"  }");
                                                            #line 566 "PrintGo.cpp.template"
                                                                }
                                                                if (tree)
                                                                {
                                                            #line 842 "PrintGo.cpp"
  append(L"\n");
  append(L"  thread.addAmbiguity(begin, thread.e0)");
                                                            #line 570 "PrintGo.cpp.template"
                                                                }
                                                            #line 847 "PrintGo.cpp"
  append(L"\n");
  append(L"  return thread\n");
  append(L"}");
                                                            #line 573 "PrintGo.cpp.template"
                                                              }
                                                            }

                                                            void PrintGo::openThread()
                                                            {
                                                            #line 857 "PrintGo.cpp"
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
                                                            #line 617 "PrintGo.cpp.template"
                                                              print(className.c_str());
                                                            #line 900 "PrintGo.cpp"
  append(L"\n");
  append(L"  threads *PriorityQueue\n");
  append(L"  accepted bool\n");
  append(L"  stack *StackNode\n");
  append(L"  state int\n");
  append(L"  action int\n");
  append(L"  target int");
                                                            #line 624 "PrintGo.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 911 "PrintGo.cpp"
  append(L"\n");
  append(L"  deferredEvent DeferredEvent");
                                                            #line 627 "PrintGo.cpp.template"
                                                              }
                                                              if (hasCustomCode)
                                                              {
                                                            #line 918 "PrintGo.cpp"
  append(L"\n");
  append(L"  deferredCode *DeferredCode");
                                                            #line 631 "PrintGo.cpp.template"
                                                              }
                                                            #line 923 "PrintGo.cpp"
  append(L"\n");
  append(L"  id int");
                                                            #line 633 "PrintGo.cpp.template"
                                                              if (resolvesAmbiguity)
                                                              {
                                                            #line 929 "PrintGo.cpp"
  append(L"\n");
  append(L"  eventCount int");
                                                            #line 636 "PrintGo.cpp.template"
                                                              }
                                                              printTokenVars();
                                                            #line 935 "PrintGo.cpp"
  append(L"\n");
  append(L"  begin int\n");
  append(L"  end int\n");
  append(L"}\n");
  append(L"\n");
  append(L"func (this *ParsingThread) open(initialState int");
                                                            #line 643 "PrintGo.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 945 "PrintGo.cpp"
  append(L", eh BottomUpEventHandler");
                                                            #line 645 "PrintGo.cpp.template"
                                                              }
                                                            #line 949 "PrintGo.cpp"
  append(L", t int) *PriorityQueue {\n");
  append(L"  this.accepted = false\n");
  append(L"  this.target = t");
                                                            #line 648 "PrintGo.cpp.template"
                                                              if (resolvesAmbiguity)
                                                              {
                                                            #line 956 "PrintGo.cpp"
  append(L"\n");
  append(L"  this.eventCount = 0");
                                                            #line 651 "PrintGo.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                            #line 963 "PrintGo.cpp"
  append(L"\n");
  append(L"  this.eventHandler = eh\n");
  append(L"  if this.eventHandler != nil {\n");
  append(L"    this.eventHandler.Reset(this.parser.input)\n");
  append(L"  }\n");
  append(L"  this.deferredEvent = nil");
                                                            #line 659 "PrintGo.cpp.template"
                                                              }
                                                              if (hasCustomCode && useGlr)
                                                              {
                                                            #line 974 "PrintGo.cpp"
  append(L"\n");
  append(L"  this.deferredCode = nil");
                                                            #line 663 "PrintGo.cpp.template"
                                                              }
                                                            #line 979 "PrintGo.cpp"
  append(L"\n");
  append(L"  this.stack = &StackNode{-1, ");
                                                            #line 665 "PrintGo.cpp.template"
                                                              if (grammar->states->hasLookback)
                                                              {
                                                            #line 985 "PrintGo.cpp"
  append(L"0, ");
                                                            #line 667 "PrintGo.cpp.template"
                                                              }
                                                            #line 989 "PrintGo.cpp"
  append(L"this.e0, nil}\n");
  append(L"  this.state = initialState\n");
  append(L"  this.action = this.predict(initialState)");
                                                            #line 670 "PrintGo.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 996 "PrintGo.cpp"
  append(L"\n");
  append(L"  this.bw = this.e0\n");
  append(L"  this.bs = this.e0\n");
  append(L"  this.es = this.e0");
                                                            #line 675 "PrintGo.cpp.template"
                                                              }
                                                            #line 1003 "PrintGo.cpp"
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
                                                            #line 686 "PrintGo.cpp.template"
                                                              if (resolvesAmbiguity)
                                                              {
                                                            #line 1018 "PrintGo.cpp"
  append(L"\n");
  append(L"  this.eventCount = other.eventCount");
                                                            #line 689 "PrintGo.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                            #line 1025 "PrintGo.cpp"
  append(L"\n");
  append(L"  this.bs = other.bs\n");
  append(L"  this.es = other.es\n");
  append(L"  this.bw = other.bw\n");
  append(L"  this.eventHandler = other.eventHandler\n");
  append(L"  this.deferredEvent = other.deferredEvent");
                                                            #line 697 "PrintGo.cpp.template"
                                                              }
                                                              if (hasCustomCode)
                                                              {
                                                            #line 1036 "PrintGo.cpp"
  append(L"\n");
  append(L"  this.deferredCode = other.deferredCode");
                                                            #line 701 "PrintGo.cpp.template"
                                                              }
                                                            #line 1041 "PrintGo.cpp"
  append(L"\n");
  append(L"  this.parser.maxId++\n");
  append(L"  this.id = this.parser.maxId\n");
  append(L"  this.threads = other.threads\n");
  append(L"  this.state = other.state\n");
  append(L"  this.stack = other.stack\n");
  append(L"  this.b0 = other.b0\n");
  append(L"  this.e0 = other.e0");
                                                            #line 709 "PrintGo.cpp.template"
                                                              for (size_t i = 1; i <= grammar->k; ++i)
                                                              {
                                                                const wchar_t *iString = format.toString<wchar_t>(i);
                                                            #line 1054 "PrintGo.cpp"
  append(L"\n");
  append(L"  this.l");
                                                            #line 713 "PrintGo.cpp.template"
                                                                print(iString);
                                                            #line 1059 "PrintGo.cpp"
  append(L" = other.l");
                                                            #line 714 "PrintGo.cpp.template"
                                                                print(iString);
                                                            #line 1063 "PrintGo.cpp"
  append(L"\n");
  append(L"  this.b");
                                                            #line 716 "PrintGo.cpp.template"
                                                                print(iString);
                                                            #line 1068 "PrintGo.cpp"
  append(L" = other.b");
                                                            #line 717 "PrintGo.cpp.template"
                                                                print(iString);
                                                            #line 1072 "PrintGo.cpp"
  append(L"\n");
  append(L"  this.e");
                                                            #line 719 "PrintGo.cpp.template"
                                                                print(iString);
                                                            #line 1077 "PrintGo.cpp"
  append(L" = other.e");
                                                            #line 720 "PrintGo.cpp.template"
                                                                print(iString);
                                                              }
                                                            #line 1082 "PrintGo.cpp"
  append(L"\n");
  append(L"  this.end = other.end\n");
  append(L"  return this\n");
  append(L"}\n");
  append(L"\n");
                                                            #line 727 "PrintGo.cpp.template"
                                                              if (resolvesAmbiguity && tree)
                                                              {
                                                            #line 1091 "PrintGo.cpp"
  append(L"\n");
  append(L"func (this *ParsingThread) addAmbiguity(begin int, end int) {\n");
  append(L"  if this.eventHandler != nil {\n");
  append(L"    this.deferredEvent = &AmbiguityEvent{&AbstractDeferredEvent{this.deferredEvent, \"\", begin, end}}\n");
  append(L"  }\n");
  append(L"}\n");
  append(L"\n");
                                                            #line 736 "PrintGo.cpp.template"
                                                              }
                                                            #line 1101 "PrintGo.cpp"
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
                                                            #line 776 "PrintGo.cpp.template"
                                                              beginPublic();
                                                            }

                                                            void PrintGo::printFlush(int i, bool withinThread)
                                                            {
                                                              if (trace)
                                                              {
                                                                increaseIndent(i);
                                                            #line 1151 "PrintGo.cpp"
  append(L"\n");
  append(L"flushTrace();");
                                                            #line 785 "PrintGo.cpp.template"
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
                                                            #line 1167 "PrintGo.cpp"
  append(L"\n");
  append(L"func (this *");
                                                            #line 798 "PrintGo.cpp.template"
                                                              print(clazz);
                                                            #line 1172 "PrintGo.cpp"
  append(L") ");
                                                            #line 799 "PrintGo.cpp.template"
                                                              wchar_t initial[2] = {name[0], 0};
                                                              if (wcscmp(visibility, publ()) == 0) initial[0] = towupper(initial[0]);
                                                              print(initial);
                                                              print(name + 1);
                                                            #line 1179 "PrintGo.cpp"
  append(L"(");
                                                            #line 803 "PrintGo.cpp.template"
                                                              printArgs(args);
                                                            #line 1183 "PrintGo.cpp"
  append(L")");
                                                            #line 804 "PrintGo.cpp.template"
                                                              if (wcscmp(type, voidType()))
                                                              {
                                                            #line 1188 "PrintGo.cpp"
  append(L" ");
                                                            #line 806 "PrintGo.cpp.template"
                                                                print(WString(type).rtrim().c_str());
                                                              }
                                                            }

                                                            void PrintGo::privateVars()
                                                            {
                                                              if (trace)
                                                              {
                                                            #line 1199 "PrintGo.cpp"
  append(L"\n");
  append(L"func (this *");
                                                            #line 815 "PrintGo.cpp.template"
                                                                print(useGlr ? L"ParsingThread" : className.c_str());
                                                            #line 1204 "PrintGo.cpp"
  append(L") lookaheadString() string {\n");
  append(L"  result := \"\"");
                                                            #line 817 "PrintGo.cpp.template"
                                                                for (size_t i = 1; i <= grammar->k; ++i)
                                                                {
                                                            #line 1210 "PrintGo.cpp"
  append(L"\n");
  append(L"  if this.l");
                                                            #line 820 "PrintGo.cpp.template"
                                                                  print(format.toString<wchar_t>(i));
                                                            #line 1215 "PrintGo.cpp"
  append(L" > 0 {\n");
  append(L"    result += ");
                                                            #line 822 "PrintGo.cpp.template"
                                                                  if (i != 1)
                                                                  {
                                                            #line 1221 "PrintGo.cpp"
  append(L"\" \" + ");
                                                            #line 824 "PrintGo.cpp.template"
                                                                  }
                                                            #line 1225 "PrintGo.cpp"
  append(L"token[this.l");
                                                            #line 825 "PrintGo.cpp.template"
                                                                  print(format.toString<wchar_t>(i));
                                                            #line 1229 "PrintGo.cpp"
  append(L"]");
                                                            #line 826 "PrintGo.cpp.template"
                                                                  increaseIndent();
                                                                }
                                                                for (size_t i = 1; i <= grammar->k; ++i)
                                                                {
                                                                  decreaseIndent();
                                                            #line 1237 "PrintGo.cpp"
  append(L"\n");
  append(L"  }");
                                                            #line 832 "PrintGo.cpp.template"
                                                                }
                                                            #line 1242 "PrintGo.cpp"
  append(L"\n");
  append(L"  return result\n");
  append(L"}\n");
                                                            #line 836 "PrintGo.cpp.template"
                                                              }
                                                              if (memoization)
                                                              {
                                                                int bits = Math::bits(grammar->conflictCount);
                                                            #line 1251 "PrintGo.cpp"
  append(L"\n");
  append(L"func (this *");
                                                            #line 841 "PrintGo.cpp.template"
                                                                print(className.c_str());
                                                            #line 1256 "PrintGo.cpp"
  append(L") memoize(i int, e int, v int) {\n");
  append(L"  this.memo[(e << ");
                                                            #line 843 "PrintGo.cpp.template"
                                                                print(format.toString<wchar_t>(bits));
                                                            #line 1261 "PrintGo.cpp"
  append(L") + i] = v\n");
  append(L"}\n");
  append(L"\n");
  append(L"func (this *");
                                                            #line 847 "PrintGo.cpp.template"
                                                                print(className.c_str());
                                                            #line 1268 "PrintGo.cpp"
  append(L") memoized(i int, e int) int {\n");
  append(L"  return this.memo[(e << ");
                                                            #line 849 "PrintGo.cpp.template"
                                                                print(format.toString<wchar_t>(bits));
                                                            #line 1273 "PrintGo.cpp"
  append(L") + i]\n");
  append(L"}\n");
                                                            #line 852 "PrintGo.cpp.template"
                                                              }
                                                            #line 1278 "PrintGo.cpp"
  append(L"\n");
  append(L"type ");
                                                            #line 854 "PrintGo.cpp.template"
                                                              print(className.c_str());
                                                            #line 1283 "PrintGo.cpp"
  append(L" struct {");
                                                            #line 855 "PrintGo.cpp.template"
                                                              if (useGlr)
                                                              {
                                                            #line 1288 "PrintGo.cpp"
  append(L"\n");
  append(L"  thread *ParsingThread\n");
  append(L"  input string");
                                                            #line 859 "PrintGo.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 1295 "PrintGo.cpp"
  append(L"\n");
  append(L"  eventHandler BottomUpEventHandler");
                                                            #line 862 "PrintGo.cpp.template"
                                                                }
                                                            #line 1300 "PrintGo.cpp"
  append(L"\n");
  append(L"  size int\n");
  append(L"  maxId int");
                                                            #line 865 "PrintGo.cpp.template"
                                                              }
                                                              else
                                                              {
                                                                printTokenVars();
                                                              }
                                                              if (memoization)
                                                              {
                                                            #line 1312 "PrintGo.cpp"
  append(L"\n");
  append(L"  memo map[int]int");
                                                            #line 873 "PrintGo.cpp.template"
                                                                if (grammar->noThrow)
                                                                {
                                                            #line 1318 "PrintGo.cpp"
  append(L"\n");
  append(L"  viable bool");
                                                            #line 876 "PrintGo.cpp.template"
                                                                }
                                                              }
                                                            }

                                                            void PrintGo::printFileProcessor()
                                                            {
                                                            #line 1328 "PrintGo.cpp"
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
                                                            #line 891 "PrintGo.cpp.template"
                                                              print(className.c_str());
                                                              if (tree)
                                                              {
                                                            #line 1343 "PrintGo.cpp"
  append(L"\n");
  append(L"  contentCounter *ContentCounter");
                                                            #line 895 "PrintGo.cpp.template"
                                                                if (isLrParser)
                                                                {
                                                            #line 1349 "PrintGo.cpp"
  append(L"\n");
  append(L"  parseTreeBuilder *ParseTreeBuilder");
                                                            #line 898 "PrintGo.cpp.template"
                                                                }
                                                              }
                                                            #line 1355 "PrintGo.cpp"
  append(L"\n");
  append(L"}\n");
  append(L"\n");
  append(L"func main() {\n");
  append(L"  if len(os.Args) < 2 {\n");
  append(L"    os.Stderr.WriteString(\"Usage: ");
                                                            #line 905 "PrintGo.cpp.template"
                                                              print(className.c_str());
                                                            #line 1364 "PrintGo.cpp"
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
                                                            #line 984 "PrintGo.cpp.template"
                                                              if (useGlr)
                                                              {
                                                            #line 1447 "PrintGo.cpp"
  append(L".thread");
                                                            #line 986 "PrintGo.cpp.template"
                                                              }
                                                            #line 1451 "PrintGo.cpp"
  append(L".Reset(0, 0, 0)\n");
  append(L"            pe := job.parser.Parse_");
                                                            #line 988 "PrintGo.cpp.template"
                                                              print(Format::acceptableName<WString>(grammar->startSymbol()->name).c_str());
                                                            #line 1456 "PrintGo.cpp"
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
                                                            #line 1000 "PrintGo.cpp.template"
                                                              if (tree)
                                                              {
                                                                if (isLrParser)
                                                                {
                                                            #line 1474 "PrintGo.cpp"
  append(L"\n");
  append(L"            job.parseTreeBuilder.Serialize(job.contentCounter)");
                                                            #line 1005 "PrintGo.cpp.template"
                                                                }
                                                            #line 1479 "PrintGo.cpp"
  append(L"\n");
  append(L"            if (job.contentCounter.getLength() != len(job.input)) {\n");
  append(L"              panic(\"content counter saw \" + strconv.Itoa(job.contentCounter.getLength()) + \", but input length is \" + strconv.Itoa(len(job.input)))\n");
  append(L"            }");
                                                            #line 1009 "PrintGo.cpp.template"
                                                              }
                                                            #line 1486 "PrintGo.cpp"
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
                                                            #line 1047 "PrintGo.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 1527 "PrintGo.cpp"
  append(L"\n");
  append(L"  contentCounter := new(ContentCounter)");
                                                            #line 1050 "PrintGo.cpp.template"
                                                                if (isLrParser)
                                                                {
                                                            #line 1533 "PrintGo.cpp"
  append(L"\n");
  append(L"  parseTreeBuilder := new(ParseTreeBuilder)");
                                                            #line 1053 "PrintGo.cpp.template"
                                                                }
                                                              }
                                                            #line 1539 "PrintGo.cpp"
  append(L"\n");
  append(L"  parsers = append(parsers, &ParseJob{name, content, NewParser(content");
                                                            #line 1057 "PrintGo.cpp.template"
                                                              if (tree)
                                                              {
                                                                if (isLrParser)
                                                                {
                                                            #line 1547 "PrintGo.cpp"
  append(L", parseTreeBuilder");
                                                            #line 1061 "PrintGo.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1553 "PrintGo.cpp"
  append(L", contentCounter");
                                                            #line 1064 "PrintGo.cpp.template"
                                                                }
                                                              }
                                                            #line 1558 "PrintGo.cpp"
  append(L")");
                                                            #line 1066 "PrintGo.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 1563 "PrintGo.cpp"
  append(L", contentCounter");
                                                            #line 1068 "PrintGo.cpp.template"
                                                                if (isLrParser)
                                                                {
                                                            #line 1568 "PrintGo.cpp"
  append(L", parseTreeBuilder");
                                                            #line 1070 "PrintGo.cpp.template"
                                                                }
                                                              }
                                                            #line 1573 "PrintGo.cpp"
  append(L"})\n");
  append(L"}\n");
                                                            #line 1074 "PrintGo.cpp.template"
                                                            }

                                                            void PrintGo::printReadMethod()
                                                            {
                                                            #line 1581 "PrintGo.cpp"
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
                                                            #line 1093 "PrintGo.cpp.template"
                                                            }

                                                            void PrintGo::printInterface()
                                                            {
                                                              if (! packageName.empty())
                                                              {
                                                            #line 1604 "PrintGo.cpp"
  append(L"\n");
  append(L"package ");
                                                            #line 1100 "PrintGo.cpp.template"
                                                                print(packageName.c_str());
                                                            #line 1609 "PrintGo.cpp"
  append(L";\n");
                                                            #line 1102 "PrintGo.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                                if (main || useGlr)
                                                                {
                                                            #line 1617 "PrintGo.cpp"
  append(L"\n");
  append(L"import java.io.IOException;\n");
  append(L"import java.io.Writer;\n");
                                                            #line 1110 "PrintGo.cpp.template"
                                                                }
                                                            #line 1623 "PrintGo.cpp"
  append(L"\n");
  append(L"import java.util.Arrays;");
                                                            #line 1112 "PrintGo.cpp.template"
                                                              }
                                                            #line 1628 "PrintGo.cpp"
  append(L"\n");
  append(L"public interface ");
                                                            #line 1114 "PrintGo.cpp.template"
                                                              print(className.c_str());
                                                            #line 1633 "PrintGo.cpp"
  append(L"\n");
  append(L"{\n");
  append(L"  public void initialize(CharSequence input");
                                                            #line 1117 "PrintGo.cpp.template"
                                                              if (noLexer)
                                                              {
                                                            #line 1640 "PrintGo.cpp"
  append(L", Lexer l");
                                                            #line 1119 "PrintGo.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                            #line 1646 "PrintGo.cpp"
  append(L", ");
                                                            #line 1122 "PrintGo.cpp.template"
                                                                if (isLrParser)
                                                                {
                                                            #line 1651 "PrintGo.cpp"
  append(L"BottomUp");
                                                            #line 1124 "PrintGo.cpp.template"
                                                                }
                                                            #line 1655 "PrintGo.cpp"
  append(L"EventHandler eh");
                                                            #line 1126 "PrintGo.cpp.template"
                                                              }
                                                            #line 1659 "PrintGo.cpp"
  append(L");\n");
  append(L"  public void parse();\n");
  append(L"  public void Reset();\n");
  append(L"  public String getErrorMessage(ParseException e);\n");
                                                            #line 1131 "PrintGo.cpp.template"
                                                              printParseException();
                                                              printEventHandlerImplementation();
                                                            #line 1667 "PrintGo.cpp"
  append(L"}\n");
                                                            #line 1134 "PrintGo.cpp.template"
                                                            }

                                                            void PrintGo::printParseException()
                                                            {
                                                            #line 1674 "PrintGo.cpp"
  append(L"\n");
  append(L"type ParseError struct {\n");
  append(L"  begin int\n");
  append(L"  end int\n");
  append(L"  state int\n");
  append(L"  offending int\n");
  append(L"  expected int");
                                                            #line 1144 "PrintGo.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 1685 "PrintGo.cpp"
  append(L"\n");
  append(L"  ambiguousInput bool");
                                                            #line 1147 "PrintGo.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 1691 "PrintGo.cpp"
  append(L"\n");
  append(L"  ambiguityDescriptor *ParseTreeBuilder");
                                                            #line 1150 "PrintGo.cpp.template"
                                                                }
                                                              }
                                                            #line 1697 "PrintGo.cpp"
  append(L"\n");
  append(L"}\n");
  append(L"\n");
  append(L"func (this ParseError) Error() string {\n");
  append(L"  if ");
                                                            #line 1156 "PrintGo.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 1706 "PrintGo.cpp"
  append(L"this.ambiguousInput {\n");
  append(L"    return \"ambiguous input\"\n");
  append(L"  } else if ");
                                                            #line 1160 "PrintGo.cpp.template"
                                                              }
                                                            #line 1712 "PrintGo.cpp"
  append(L"this.offending < 0 {\n");
  append(L"    return \"lexical analysis failed\"\n");
  append(L"  } else {\n");
  append(L"    return \"syntax error\"\n");
  append(L"  }\n");
  append(L"}\n");
                                                            #line 1167 "PrintGo.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 1722 "PrintGo.cpp"
  append(L"\n");
  append(L"func (this *ParseError) Serialize(eventHandler EventHandler) {");
                                                            #line 1170 "PrintGo.cpp.template"
                                                                if (rejectsAmbiguity())
                                                                {
                                                            #line 1728 "PrintGo.cpp"
  append(L"\n");
  append(L"  this.ambiguityDescriptor.Serialize(eventHandler)");
                                                            #line 1173 "PrintGo.cpp.template"
                                                                }
                                                            #line 1733 "PrintGo.cpp"
  append(L"\n");
  append(L"}\n");
                                                            #line 1176 "PrintGo.cpp.template"
                                                              }
                                                            #line 1738 "PrintGo.cpp"
  append(L"\n");
  append(L"func (this *ParseError) GetBegin() int {return this.begin}\n");
  append(L"func (this *ParseError) GetEnd() int {return this.end}\n");
  append(L"func (this *ParseError) GetState() int {return this.state}\n");
  append(L"func (this *ParseError) GetOffending() int {return this.offending}\n");
  append(L"func (this *ParseError) GetExpected() int {return this.expected}\n");
  append(L"func (this *ParseError) IsAmbiguousInput() bool {return ");
                                                            #line 1183 "PrintGo.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 1749 "PrintGo.cpp"
  append(L"this.ambiguousInput");
                                                            #line 1186 "PrintGo.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 1755 "PrintGo.cpp"
  append(L"false");
                                                            #line 1190 "PrintGo.cpp.template"
                                                              }
                                                            #line 1759 "PrintGo.cpp"
  append(L"}\n");
                                                            #line 1192 "PrintGo.cpp.template"
                                                              if (noLexer)
                                                              {
                                                            #line 1764 "PrintGo.cpp"
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
                                                            #line 1207 "PrintGo.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                            #line 1782 "PrintGo.cpp"
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
                                                            #line 1324 "PrintGo.cpp.template"
                                                                if (isLrParser)
                                                                {
                                                            #line 1900 "PrintGo.cpp"
  append(L"\n");
  append(L"type BottomUpEventHandler interface {\n");
  append(L"  Reset(input string)\n");
  append(L"  Nonterminal(name string, begin int, end int, count int)\n");
  append(L"  Terminal(name string, begin int, end int)");
                                                            #line 1330 "PrintGo.cpp.template"
                                                                  if (resolvesAmbiguity)
                                                                  {
                                                            #line 1909 "PrintGo.cpp"
  append(L"\n");
  append(L"  Ambiguity(begin int, end int)");
                                                            #line 1333 "PrintGo.cpp.template"
                                                                  }
                                                            #line 1914 "PrintGo.cpp"
  append(L"\n");
  append(L"}\n");
                                                            #line 1336 "PrintGo.cpp.template"
                                                                }
                                                              }
                                                            }

                                                            void PrintGo::printEventHandlerImplementation()
                                                            {
                                                              if (tree)
                                                              {
                                                                if (main || useGlr)
                                                                {
                                                            #line 1928 "PrintGo.cpp"
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
                                                            #line 1437 "PrintGo.cpp.template"
                                                                }
                                                                if (performanceTest)
                                                                {
                                                            #line 2024 "PrintGo.cpp"
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
                                                            #line 1454 "PrintGo.cpp.template"
                                                                }
                                                                if (isLrParser)
                                                                {
                                                            #line 2043 "PrintGo.cpp"
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
                                                            #line 1471 "PrintGo.cpp.template"
                                                                  if (rejectsAmbiguity())
                                                                  {
                                                            #line 2061 "PrintGo.cpp"
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
                                                            #line 1485 "PrintGo.cpp.template"
                                                                  }
                                                            #line 2077 "PrintGo.cpp"
  append(L"\n");
  append(L"  this.push(&Nonterminal{&AbstractSymbol{name, begin, end}, this.pop(count)})\n");
  append(L"}\n");
  append(L"\n");
  append(L"func (this *ParseTreeBuilder) Terminal(name string, begin int, end int) {\n");
  append(L"  this.push(&Terminal{&AbstractSymbol{name, begin, end}})\n");
  append(L"}\n");
                                                            #line 1493 "PrintGo.cpp.template"
                                                                  if (resolvesAmbiguity)
                                                                  {
                                                            #line 2088 "PrintGo.cpp"
  append(L"\n");
  append(L"func (this *ParseTreeBuilder) Ambiguity(begin int, end int) {\n");
  append(L"}\n");
                                                            #line 1498 "PrintGo.cpp.template"
                                                                  }
                                                            #line 2094 "PrintGo.cpp"
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
                                                            #line 1520 "PrintGo.cpp.template"
                                                                }
                                                              }
                                                            }

                                                            void PrintGo::printTokenVars()
                                                            {
                                                            #line 2123 "PrintGo.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 1527 "PrintGo.cpp.template"
                                                              if (! isLrParser && (grammar->k > 1 ||
                                                                                   memoization ||
                                                                                   ! grammar->decisionPoints.empty()))
                                                              {
                                                            #line 2131 "PrintGo.cpp"
  append(L"lk,");
                                                            #line 1531 "PrintGo.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 2137 "PrintGo.cpp"
  append(L"   ");
                                                            #line 1534 "PrintGo.cpp.template"
                                                              }
                                                            #line 2141 "PrintGo.cpp"
  append(L" b0, e0 int");
                                                            #line 1535 "PrintGo.cpp.template"
                                                              for (size_t k = 1; k <= grammar->k; ++k)
                                                              {
                                                                Format format;
                                                                wchar_t *asString = format.toString<wchar_t>(k);
                                                            #line 2148 "PrintGo.cpp"
  append(L"\n");
  append(L"  l");
                                                            #line 1540 "PrintGo.cpp.template"
                                                                print(asString);
                                                            #line 2153 "PrintGo.cpp"
  append(L", b");
                                                            #line 1541 "PrintGo.cpp.template"
                                                                print(asString);
                                                            #line 2157 "PrintGo.cpp"
  append(L", e");
                                                            #line 1542 "PrintGo.cpp.template"
                                                                print(asString);
                                                            #line 2161 "PrintGo.cpp"
  append(L" int");
                                                            #line 1543 "PrintGo.cpp.template"
                                                              }
                                                              if (hasBacktracking)
                                                              {
                                                            #line 2167 "PrintGo.cpp"
  append(L"\n");
  append(L"  bx, ex, sx, lx, tx int");
                                                            #line 1547 "PrintGo.cpp.template"
                                                              }
                                                              else if (isLrParser && ! useGlr)
                                                              {
                                                            #line 2174 "PrintGo.cpp"
  append(L"\n");
  append(L"  iStack []int\n");
  append(L"  top int");
                                                            #line 1552 "PrintGo.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                                if (isLrParser)
                                                                {
                                                                  if (useGlr)
                                                                  {
                                                            #line 2186 "PrintGo.cpp"
  append(L"\n");
  append(L"  bw, bs, es int");
                                                            #line 1560 "PrintGo.cpp.template"
                                                                  }
                                                            #line 2191 "PrintGo.cpp"
  append(L"\n");
  append(L"  eventHandler BottomUpEventHandler");
                                                            #line 1562 "PrintGo.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 2198 "PrintGo.cpp"
  append(L"\n");
  append(L"  eventHandler EventHandler");
                                                            #line 1566 "PrintGo.cpp.template"
                                                                }
                                                              }
                                                            }

// End
