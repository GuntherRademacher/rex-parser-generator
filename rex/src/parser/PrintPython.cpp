// This file was generated on Sat Oct 17, 2026 11:26 (UTC+02) by REx v6.3-SNAPSHOT which is Copyright (c) 1979-2026 by Gunther Rademacher <grd@gmx.net>
// REx command line: PrintPython.cpp.template
                                                            #line 1 "PrintPython.cpp.template"
                                                            #include "../common/Memory.hpp"

                                                            #include "PrintPython.hpp"
                                                            #include "ItemSet.hpp"
                                                            #include "../common/CompressedMap.hpp"

                                                            void PrintPython::openClass()
                                                            {
                                                              if (hasProlog)
                                                              {
                                                            #line 15 "PrintPython.cpp"
  append(L"\n");
                                                            #line 12 "PrintPython.cpp.template"
                                                              }
                                                              else
                                                              {
                                                                size_t s = size();
                                                                /*
                                                            #line 23 "PrintPython.cpp"
  append(L"\n");
  append(L"package ");
                                                            #line 18 "PrintPython.cpp.template"
                                                                if (main || packageName.empty())
                                                                {
                                                            #line 29 "PrintPython.cpp"
  append(L"main");
                                                            #line 20 "PrintPython.cpp.template"
                                                                }
                                                                else
                                                                {
                                                                  print(packageName.c_str());
                                                                }
                                                                */
                                                                if (main || performanceTest)
                                                                {
                                                            #line 40 "PrintPython.cpp"
  append(L"\n");
  append(L"import sys");
                                                            #line 29 "PrintPython.cpp.template"
                                                                }
                                                                if (performanceTest)
                                                                {
                                                            #line 47 "PrintPython.cpp"
  append(L"\n");
  append(L"import glob\n");
  append(L"import time");
                                                            #line 34 "PrintPython.cpp.template"
                                                                }
                                                                if (useGlr)
                                                                {
                                                            #line 55 "PrintPython.cpp"
  append(L"\n");
  append(L"import heapq");
                                                            #line 38 "PrintPython.cpp.template"
                                                                }
                                                                if (s != size())
                                                                {
                                                            #line 62 "PrintPython.cpp"
  append(L"\n");
                                                            #line 42 "PrintPython.cpp.template"
                                                                }
                                                            #line 66 "PrintPython.cpp"
  append(L"\n");
  append(L"class ");
                                                            #line 44 "PrintPython.cpp.template"
                                                                print(className.c_str());
                                                            #line 71 "PrintPython.cpp"
  append(L":\n");
                                                            #line 46 "PrintPython.cpp.template"
                                                              }
                                                              increaseIndent();
                                                              if (interfaceName.empty())
                                                              {
                                                                printParseException();
                                                                printEventHandlerImplementation();
                                                              }
                                                              if (! hasProlog)
                                                              {
                                                                WString args;
                                                                if (noLexer) args += L", lexer";
                                                                if (tree) args += L", t";
                                                            #line 86 "PrintPython.cpp"
  append(L"\n");
  append(L"def __init__(self, inputString");
                                                            #line 59 "PrintPython.cpp.template"
                                                                print(args.c_str());
                                                            #line 91 "PrintPython.cpp"
  append(L"):\n");
  append(L"  self.initialize(inputString");
                                                            #line 61 "PrintPython.cpp.template"
                                                                if (noLexer)
                                                                {
                                                            #line 97 "PrintPython.cpp"
  append(L", lexer");
                                                            #line 63 "PrintPython.cpp.template"
                                                                }
                                                                if (tree)
                                                                {
                                                            #line 103 "PrintPython.cpp"
  append(L", t");
                                                            #line 66 "PrintPython.cpp.template"
                                                                }
                                                            #line 107 "PrintPython.cpp"
  append(L")\n");
                                                            #line 68 "PrintPython.cpp.template"
                                                              }
                                                              decreaseIndent();
                                                            }

                                                            void PrintPython::openStackNode()
                                                            {
                                                            #line 116 "PrintPython.cpp"
  append(L"\n");
  append(L"class StackNode:\n");
  append(L"\n");
  append(L"  def __init__(self, state");
                                                            #line 77 "PrintPython.cpp.template"
                                                              if (grammar->states->hasLookback)
                                                              {
                                                            #line 124 "PrintPython.cpp"
  append(L", code");
                                                            #line 79 "PrintPython.cpp.template"
                                                              }
                                                            #line 128 "PrintPython.cpp"
  append(L", pos, link):\n");
  append(L"    self.state = state");
                                                            #line 81 "PrintPython.cpp.template"
                                                              if (grammar->states->hasLookback)
                                                              {
                                                            #line 134 "PrintPython.cpp"
  append(L"\n");
  append(L"    self.code = code");
                                                            #line 84 "PrintPython.cpp.template"
                                                              }
                                                            #line 139 "PrintPython.cpp"
  append(L"\n");
  append(L"    self.pos = pos\n");
  append(L"    self.link = link\n");
  append(L"\n");
  append(L"  def equals(self, rhs):\n");
  append(L"    lhs = self\n");
  append(L"    while lhs != None and rhs != None:\n");
  append(L"      if lhs == rhs:\n");
  append(L"        return True\n");
  append(L"      if lhs.state != rhs.state:\n");
  append(L"        return False");
                                                            #line 95 "PrintPython.cpp.template"
                                                              if (grammar->states->hasLookback)
                                                              {
                                                            #line 154 "PrintPython.cpp"
  append(L"\n");
  append(L"      if lhs.code != rhs.code:\n");
  append(L"        return False");
                                                            #line 99 "PrintPython.cpp.template"
                                                              }
                                                            #line 160 "PrintPython.cpp"
  append(L"\n");
  append(L"      if lhs.pos != rhs.pos:\n");
  append(L"        return False\n");
  append(L"      lhs = lhs.link\n");
  append(L"      rhs = rhs.link\n");
  append(L"    return lhs == rhs\n");
                                                            #line 106 "PrintPython.cpp.template"
                                                              beginPublic();
                                                              increaseIndent();
                                                            }

                                                            void PrintPython::closeStackNode()
                                                            {
                                                              decreaseIndent();
                                                              beginNonpublic();
                                                              if (hasCustomCode)
                                                              {
                                                            #line 178 "PrintPython.cpp"
  append(L"\n");
  append(L"class DeferredCode:\n");
  append(L"\n");
  append(L"  def __init__(self, link, codeId, b0, e0):\n");
  append(L"    self.link = link\n");
  append(L"    self.codeId = codeId\n");
  append(L"    self.b0 = b0\n");
  append(L"    self.e0 = e0\n");
                                                            #line 124 "PrintPython.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                            #line 191 "PrintPython.cpp"
  append(L"\n");
  append(L"class DeferredEvent:\n");
  append(L"\n");
  append(L"  def __init__(self, link, name, begin, end):\n");
  append(L"    self.link = link\n");
  append(L"    self.name = name\n");
  append(L"    self.begin = begin\n");
  append(L"    self.end = end\n");
  append(L"\n");
  append(L"  def release(self, eventHandler):\n");
  append(L"    current = self\n");
  append(L"    predecessor = current.link\n");
  append(L"    current.link = None\n");
  append(L"    while predecessor != None:\n");
  append(L"      nextEvent = predecessor.link\n");
  append(L"      predecessor.link = current\n");
  append(L"      current = predecessor\n");
  append(L"      predecessor = nextEvent\n");
  append(L"    while current != None:\n");
  append(L"      current.execute(eventHandler)\n");
  append(L"      current = current.link\n");
  append(L"\n");
  append(L"  def show(self, eventHandler):\n");
  append(L"    stack = []\n");
  append(L"    current = self\n");
  append(L"    while current != None:\n");
  append(L"      stack.append(current)\n");
  append(L"      current = current.link\n");
  append(L"    i = len(stack) - 1\n");
  append(L"    while i >= 0:\n");
  append(L"      stack[i].execute(eventHandler)\n");
  append(L"      i -= 1\n");
  append(L"\n");
  append(L"class TerminalEvent(DeferredEvent):\n");
  append(L"\n");
  append(L"  def __init__(self, link, name, begin, end):\n");
  append(L"    super().__init__(link, name, begin, end)\n");
  append(L"\n");
  append(L"  def execute(self, eventHandler):\n");
  append(L"    eventHandler.terminal(self.name, self.begin, self.end)\n");
  append(L"\n");
  append(L"  def toString(self):\n");
  append(L"    return \"terminal(\" + self.name + \", \" + str(self.begin) + \", \" + str(self.end) + \")\"\n");
  append(L"\n");
  append(L"class NonterminalEvent(DeferredEvent):\n");
  append(L"\n");
  append(L"  def __init__(self, link, name, begin, end, count):\n");
  append(L"    super().__init__(link, name, begin, end)\n");
  append(L"    self.count = count\n");
  append(L"\n");
  append(L"  def execute(self, eventHandler):\n");
  append(L"    eventHandler.nonterminal(self.name, self.begin, self.end, self.count)\n");
  append(L"\n");
  append(L"  def toString(self):\n");
  append(L"    return \"nonterminal(\" + self.name + \", \" + str(self.begin) + \", \" + str(self.end) + \", \" + str(self.count) + \")\"\n");
                                                            #line 182 "PrintPython.cpp.template"
                                                              if (minimalAmbiguity)
                                                              {
                                                            #line 250 "PrintPython.cpp"
  append(L"\n");
  append(L"\n");
  append(L"class AmbiguityEvent(DeferredEvent):\n");
  append(L"\n");
  append(L"  def __init__(self, link, begin, end):\n");
  append(L"    super().__init__(link, None, begin, end)\n");
  append(L"\n");
  append(L"  def execute(self, eventHandler):\n");
  append(L"    eventHandler.ambiguity(self.begin, self.end)\n");
  append(L"\n");
  append(L"  def toString(self):\n");
  append(L"    return \"ambiguity(\" + str(self.begin) + \", \" + str(self.end) + \")\"\n");
                                                            #line 196 "PrintPython.cpp.template"
                                                              }
                                                              }
                                                            #line 266 "PrintPython.cpp"
  append(L"\n");
  append(L"PARSING = 0\n");
  append(L"ACCEPTED = 1\n");
  append(L"ERROR = 2\n");
  append(L"\n");
  append(L"def parse(self, target, initialState, ");
                                                            #line 203 "PrintPython.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 276 "PrintPython.cpp"
  append(L"eventHandler, ");
                                                            #line 206 "PrintPython.cpp.template"
                                                              }
                                                            #line 280 "PrintPython.cpp"
  append(L"thread):\n");
  append(L"  threads = thread.open(initialState");
                                                            #line 208 "PrintPython.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 286 "PrintPython.cpp"
  append(L", eventHandler");
                                                            #line 210 "PrintPython.cpp.template"
                                                              }
                                                            #line 290 "PrintPython.cpp"
  append(L", target)\n");
  append(L"  while True:\n");
  append(L"    thread = heapq.heappop(threads)[3]\n");
  append(L"    if thread.accepted:");
                                                            #line 214 "PrintPython.cpp.template"
                                                                if (rejectsAmbiguity())
                                                              {
                                                            #line 298 "PrintPython.cpp"
  append(L"\n");
  append(L"      other = None\n");
  append(L"      while len(threads) != 0:\n");
  append(L"        other = heapq.heappop(threads)[3]\n");
  append(L"        if thread.e0 < other.e0:\n");
  append(L"          thread = other\n");
  append(L"          other = None\n");
  append(L"      if other != None:\n");
  append(L"        self.rejectAmbiguity(thread.stack.pos, thread.e0");
                                                            #line 224 "PrintPython.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 311 "PrintPython.cpp"
  append(L", thread.deferredEvent, other.deferredEvent");
                                                            #line 227 "PrintPython.cpp.template"
                                                              }
                                                            #line 315 "PrintPython.cpp"
  append(L")");
                                                            #line 228 "PrintPython.cpp.template"
                                                                 }
                                                              else
                                                              {
                                                            #line 321 "PrintPython.cpp"
  append(L"\n");
  append(L"      while len(threads) != 0:\n");
  append(L"        other = heapq.heappop(threads)[3]\n");
  append(L"        thread = other if thread.e0 < other.e0 else self.resolve(thread, other)");
                                                            #line 234 "PrintPython.cpp.template"
                                                                                          }
                                                              if (tree)
                                                              {
                                                            #line 330 "PrintPython.cpp"
  append(L"\n");
  append(L"      if thread.deferredEvent != None:\n");
  append(L"        thread.deferredEvent.release(eventHandler)\n");
  append(L"        thread.deferredEvent = None");
                                                            #line 240 "PrintPython.cpp.template"
                                                              }
                                                              if (hasCustomCode)
                                                              {
                                                            #line 339 "PrintPython.cpp"
  append(L"\n");
  append(L"      thread.executeDeferredCode()");
                                                            #line 244 "PrintPython.cpp.template"
                                                              }
                                                            #line 344 "PrintPython.cpp"
  append(L"\n");
  append(L"      return thread\n");
  append(L"\n");
                                                            #line 248 "PrintPython.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 351 "PrintPython.cpp"
  append(L"    if len(threads) != 0:\n");
  append(L"      if threads[0][3].equals(thread):\n");
  append(L"        self.rejectAmbiguity(thread.stack.pos, thread.e0");
                                                            #line 252 "PrintPython.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 358 "PrintPython.cpp"
  append(L", thread.deferredEvent, threads[0][3].deferredEvent");
                                                            #line 255 "PrintPython.cpp.template"
                                                              }
                                                            #line 362 "PrintPython.cpp"
  append(L")");
                                                            #line 256 "PrintPython.cpp.template"
                                                                 }
                                                              else
                                                              {
                                                            #line 368 "PrintPython.cpp"
  append(L"    while len(threads) != 0 and threads[0][3].equals(thread):\n");
  append(L"      thread = self.resolve(thread, heapq.heappop(threads)[3])");
                                                            #line 260 "PrintPython.cpp.template"
                                                                         }
                                                              if (tree || hasCustomCode)
                                                              {
                                                                if (rejectsAmbiguity())
                                                                {
                                                            #line 377 "PrintPython.cpp"
  append(L"\n");
  append(L"    else:");
                                                            #line 266 "PrintPython.cpp.template"
                                                                    }
                                                                else
                                                                {
                                                            #line 384 "PrintPython.cpp"
  append(L"\n");
  append(L"    if len(threads) == 0:");
                                                            #line 270 "PrintPython.cpp.template"
                                                                  }
                                                                if (tree)
                                                                {
                                                            #line 391 "PrintPython.cpp"
  append(L"\n");
  append(L"      if thread.deferredEvent != None:\n");
  append(L"        thread.deferredEvent.release(eventHandler)\n");
  append(L"        thread.deferredEvent = None");
                                                            #line 276 "PrintPython.cpp.template"
                                                                }
                                                                if (hasCustomCode)
                                                                {
                                                            #line 400 "PrintPython.cpp"
  append(L"\n");
  append(L"      thread.executeDeferredCode()");
                                                            #line 280 "PrintPython.cpp.template"
                                                                }
                                                              }
                                                            #line 406 "PrintPython.cpp"
  append(L"\n");
  append(L"\n");
  append(L"    while True:\n");
  append(L"      status = thread.parse()\n");
  append(L"      if status != ");
                                                            #line 286 "PrintPython.cpp.template"
                                                              print(className.c_str());
                                                            #line 414 "PrintPython.cpp"
  append(L".PARSING:\n");
  append(L"        break\n");
  append(L"      if len(threads) != 0:\n");
  append(L"        break\n");
  append(L"\n");
  append(L"    if status != ");
                                                            #line 292 "PrintPython.cpp.template"
                                                              print(className.c_str());
                                                            #line 423 "PrintPython.cpp"
  append(L".ERROR:\n");
  append(L"      heapq.heappush(threads, (thread.accepted, thread.e0, thread.id, thread))\n");
  append(L"    elif len(threads) == 0:\n");
  append(L"      raise ");
                                                            #line 296 "PrintPython.cpp.template"
                                                              print(className.c_str());
                                                            #line 430 "PrintPython.cpp"
  append(L".ParseException(");
                                                            #line 297 "PrintPython.cpp.template"
                                                              size_t filler = column();
                                                            #line 434 "PrintPython.cpp"
  append(L"thread.b1,");
                                                            #line 298 "PrintPython.cpp.template"
                                                              print(L"\n");
                                                              filler -= column();
                                                              print(filler, L" ");
                                                            #line 440 "PrintPython.cpp"
  append(L"thread.e1,");
                                                            #line 301 "PrintPython.cpp.template"
                                                              print(L"\n");
                                                              print(filler, L" ");
                                                              print(className.c_str());
                                                            #line 446 "PrintPython.cpp"
  append(L".TOKENSET[thread.state] + 1,");
                                                            #line 304 "PrintPython.cpp.template"
                                                              print(L"\n");
                                                              print(filler, L" ");
                                                            #line 451 "PrintPython.cpp"
  append(L"thread.l1,");
                                                            #line 306 "PrintPython.cpp.template"
                                                              print(L"\n");
                                                              print(filler, L" ");
                                                            #line 456 "PrintPython.cpp"
  append(L"-1)\n");
                                                            #line 309 "PrintPython.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 461 "PrintPython.cpp"
  append(L"\n");
  append(L"def rejectAmbiguity(self, begin, end");
                                                            #line 312 "PrintPython.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 467 "PrintPython.cpp"
  append(L", first, second");
                                                            #line 314 "PrintPython.cpp.template"
                                                              }
                                                            #line 471 "PrintPython.cpp"
  append(L"):");
                                                            #line 315 "PrintPython.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 476 "PrintPython.cpp"
  append(L"\n");
  append(L"  treeBuilder = ");
                                                            #line 318 "PrintPython.cpp.template"
                                                                print(className.c_str());
                                                            #line 481 "PrintPython.cpp"
  append(L".ParseTreeBuilder()\n");
  append(L"  treeBuilder.reset(self.input)\n");
  append(L"  second.show(treeBuilder)\n");
  append(L"  treeBuilder.nonterminal(\"ALTERNATIVE\", treeBuilder.stack[0].begin, treeBuilder.stack[len(treeBuilder.stack) - 1].end, len(treeBuilder.stack))\n");
  append(L"  secondTree = treeBuilder.pop(1)[0]\n");
  append(L"  first.show(treeBuilder)\n");
  append(L"  treeBuilder.nonterminal(\"ALTERNATIVE\", treeBuilder.stack[0].begin, treeBuilder.stack[len(treeBuilder.stack) - 1].end, len(treeBuilder.stack))\n");
  append(L"  treeBuilder.push(secondTree)\n");
  append(L"  treeBuilder.nonterminal(\"AMBIGUOUS\", treeBuilder.stack[0].begin, treeBuilder.stack[len(treeBuilder.stack) - 1].end, 2)");
                                                            #line 328 "PrintPython.cpp.template"
                                                              }
                                                            #line 493 "PrintPython.cpp"
  append(L"\n");
  append(L"  raise ");
                                                            #line 330 "PrintPython.cpp.template"
                                                              print(className.c_str());
                                                            #line 498 "PrintPython.cpp"
  append(L".ParseException(begin, end, 1, -1, -1, True");
                                                            #line 331 "PrintPython.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 503 "PrintPython.cpp"
  append(L", treeBuilder");
                                                            #line 333 "PrintPython.cpp.template"
                                                              }
                                                            #line 507 "PrintPython.cpp"
  append(L")");
                                                            #line 334 "PrintPython.cpp.template"
                                                                    }
                                                              else
                                                              {
                                                            #line 513 "PrintPython.cpp"
  append(L"\n");
  append(L"def resolve(self, thread, other):");
                                                            #line 338 "PrintPython.cpp.template"
                                                                if (tree)
                                                              {
                                                            #line 519 "PrintPython.cpp"
  append(L"\n");
  append(L"  a = thread.stack\n");
  append(L"  b = other.stack\n");
  append(L"  begin = a.pos\n");
  append(L"  while a is not b and a is not None and b is not None:\n");
  append(L"    begin = a.pos\n");
  append(L"    a = a.link\n");
  append(L"    b = b.link");
                                                            #line 347 "PrintPython.cpp.template"
                                             }
                                                            #line 530 "PrintPython.cpp"
  append(L"\n");
  append(L"  if other.eventCount < thread.eventCount:\n");
  append(L"    thread = other");
                                                            #line 350 "PrintPython.cpp.template"
                                                 if (tree)
                                                              {
                                                            #line 537 "PrintPython.cpp"
  append(L"\n");
  append(L"  thread.addAmbiguity(begin, thread.e0)");
                                                            #line 353 "PrintPython.cpp.template"
                                                                      }
                                                            #line 542 "PrintPython.cpp"
  append(L"\n");
  append(L"  return thread");
                                                            #line 355 "PrintPython.cpp.template"
                                              }
                                                              }

                                                            void PrintPython::openThread()
                                                            {
                                                            #line 551 "PrintPython.cpp"
  append(L"\n");
  append(L"class ParsingThread:\n");
  append(L"\n");
  append(L"  def open(self, initialState");
                                                            #line 363 "PrintPython.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 559 "PrintPython.cpp"
  append(L", eh");
                                                            #line 365 "PrintPython.cpp.template"
                                                              }
                                                            #line 563 "PrintPython.cpp"
  append(L", t):\n");
  append(L"    self.accepted = False\n");
  append(L"    self.target = t");
                                                            #line 368 "PrintPython.cpp.template"
                                                                      if (minimalAmbiguity)
                                                              {
                                                            #line 570 "PrintPython.cpp"
  append(L"\n");
  append(L"    self.eventCount = 0");
                                                            #line 371 "PrintPython.cpp.template"
                                                                          }
                                                              if (tree)
                                                              {
                                                            #line 577 "PrintPython.cpp"
  append(L"\n");
  append(L"    self.eventHandler = eh\n");
  append(L"    if self.eventHandler != None:\n");
  append(L"      self.eventHandler.reset(self.parser.input)\n");
  append(L"    self.deferredEvent = None");
                                                            #line 378 "PrintPython.cpp.template"
                                                              }
                                                              if (hasCustomCode && useGlr)
                                                              {
                                                            #line 587 "PrintPython.cpp"
  append(L"\n");
  append(L"    self.deferredCode = None");
                                                            #line 382 "PrintPython.cpp.template"
                                                              }
                                                            #line 592 "PrintPython.cpp"
  append(L"\n");
  append(L"    self.stack = ");
                                                            #line 384 "PrintPython.cpp.template"
                                                              print(className.c_str());
                                                            #line 597 "PrintPython.cpp"
  append(L".StackNode(-1, ");
                                                            #line 385 "PrintPython.cpp.template"
                                                              if (grammar->states->hasLookback)
                                                              {
                                                            #line 602 "PrintPython.cpp"
  append(L"0, ");
                                                            #line 387 "PrintPython.cpp.template"
                                                              }
                                                            #line 606 "PrintPython.cpp"
  append(L"self.e0, None)\n");
  append(L"    self.state = initialState\n");
  append(L"    self.action = self.predict(initialState)");
                                                            #line 390 "PrintPython.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 613 "PrintPython.cpp"
  append(L"\n");
  append(L"    self.bw = self.e0\n");
  append(L"    self.bs = self.e0\n");
  append(L"    self.es = self.e0");
                                                            #line 395 "PrintPython.cpp.template"
                                                              }
                                                            #line 620 "PrintPython.cpp"
  append(L"\n");
  append(L"    self.threads = [(False, self.e0, self.id, self)]\n");
  append(L"    return self.threads\n");
  append(L"\n");
  append(L"  def copy(self, other, action):\n");
  append(L"    self.action = action\n");
  append(L"    self.accepted = other.accepted\n");
  append(L"    self.target = other.target\n");
  append(L"    self.parser = other.parser");
                                                            #line 404 "PrintPython.cpp.template"
                                                                                 if (minimalAmbiguity)
                                                              {
                                                            #line 633 "PrintPython.cpp"
  append(L"\n");
  append(L"    self.eventCount = other.eventCount");
                                                            #line 407 "PrintPython.cpp.template"
                                                                                         }
                                                              if (tree)
                                                              {
                                                            #line 640 "PrintPython.cpp"
  append(L"\n");
  append(L"    self.bs = other.bs\n");
  append(L"    self.es = other.es\n");
  append(L"    self.bw = other.bw\n");
  append(L"    self.eventHandler = other.eventHandler\n");
  append(L"    self.deferredEvent = other.deferredEvent");
                                                            #line 415 "PrintPython.cpp.template"
                                                              }
                                                              if (hasCustomCode)
                                                              {
                                                            #line 651 "PrintPython.cpp"
  append(L"\n");
  append(L"    self.deferredCode = other.deferredCode");
                                                            #line 419 "PrintPython.cpp.template"
                                                              }
                                                            #line 656 "PrintPython.cpp"
  append(L"\n");
  append(L"    self.parser.maxId += 1\n");
  append(L"    self.id = self.parser.maxId\n");
  append(L"    self.threads = other.threads\n");
  append(L"    self.state = other.state\n");
  append(L"    self.stack = other.stack\n");
  append(L"    self.b0 = other.b0\n");
  append(L"    self.e0 = other.e0");
                                                            #line 427 "PrintPython.cpp.template"
                                                              for (size_t i = 1; i <= grammar->k; ++i)
                                                              {
                                                                const wchar_t *iString = format.toString<wchar_t>(i);
                                                            #line 669 "PrintPython.cpp"
  append(L"\n");
  append(L"    self.l");
                                                            #line 431 "PrintPython.cpp.template"
                                                                print(iString);
                                                            #line 674 "PrintPython.cpp"
  append(L" = other.l");
                                                            #line 432 "PrintPython.cpp.template"
                                                                print(iString);
                                                            #line 678 "PrintPython.cpp"
  append(L"\n");
  append(L"    self.b");
                                                            #line 434 "PrintPython.cpp.template"
                                                                print(iString);
                                                            #line 683 "PrintPython.cpp"
  append(L" = other.b");
                                                            #line 435 "PrintPython.cpp.template"
                                                                print(iString);
                                                            #line 687 "PrintPython.cpp"
  append(L"\n");
  append(L"    self.e");
                                                            #line 437 "PrintPython.cpp.template"
                                                                print(iString);
                                                            #line 692 "PrintPython.cpp"
  append(L" = other.e");
                                                            #line 438 "PrintPython.cpp.template"
                                                                print(iString);
                                                              }
                                                            #line 697 "PrintPython.cpp"
  append(L"\n");
  append(L"    self.end = other.end\n");
  append(L"    return self\n");
                                                            #line 443 "PrintPython.cpp.template"
                                                              if (minimalAmbiguity && tree)
                                                              {
                                                            #line 704 "PrintPython.cpp"
  append(L"\n");
  append(L"  def addAmbiguity(self, begin, end):\n");
  append(L"    if self.eventHandler != None:\n");
  append(L"      self.deferredEvent = ");
                                                            #line 448 "PrintPython.cpp.template"
                                                          print(className.c_str());
                                                            #line 711 "PrintPython.cpp"
  append(L".AmbiguityEvent(self.deferredEvent, begin, end)\n");
                                                            #line 450 "PrintPython.cpp.template"
                                                              }
                                                            #line 715 "PrintPython.cpp"
  append(L"\n");
  append(L"  def equals(self, other):\n");
  append(L"    if self.accepted != other.accepted:\n");
  append(L"      return False\n");
  append(L"    if self.b1 != other.b1:\n");
  append(L"      return False\n");
  append(L"    if self.e1 != other.e1:\n");
  append(L"      return False\n");
  append(L"    if self.l1 != other.l1:\n");
  append(L"      return False\n");
  append(L"    if self.state != other.state:\n");
  append(L"      return False\n");
  append(L"    if self.action != other.action:\n");
  append(L"      return False\n");
  append(L"    if not self.stack.equals(other.stack):\n");
  append(L"      return False\n");
  append(L"    return True\n");
  append(L"\n");
  append(L"  def parse(self):");
                                                            #line 469 "PrintPython.cpp.template"
                                                              increaseIndent();
                                                              beginPublic();
                                                            }

                                                            void PrintPython::printFlush(int i, bool withinThread)
                                                            {
                                                              if (trace)
                                                              {
                                                                increaseIndent(i);
                                                            #line 745 "PrintPython.cpp"
  append(L"\n");
                                                            #line 479 "PrintPython.cpp.template"
                                                                print(className.c_str());
                                                            #line 749 "PrintPython.cpp"
  append(L".flushTrace()");
                                                            #line 480 "PrintPython.cpp.template"
                                                                decreaseIndent(i);
                                                              }
                                                             }

                                                            void PrintPython::openMethod(const wchar_t *type,
                                                                                         const wchar_t *prefix,
                                                                                         const wchar_t *name,
                                                                                         const wchar_t *args,
                                                                                         bool constant,
                                                                                         const wchar_t *clazz)
                                                            {
                                                            #line 763 "PrintPython.cpp"
  append(L"\n");
  append(L"def ");
                                                            #line 492 "PrintPython.cpp.template"
                                                              print(name);
                                                            #line 768 "PrintPython.cpp"
  append(L"(self");
                                                            #line 493 "PrintPython.cpp.template"
                                                              if (*args != 0)
                                                              {
                                                            #line 773 "PrintPython.cpp"
  append(L", ");
                                                            #line 495 "PrintPython.cpp.template"
                                                                printArgNamesOnly(args);
                                                              }
                                                            #line 778 "PrintPython.cpp"
  append(L"):");
                                                            #line 497 "PrintPython.cpp.template"
                                                            }

                                                            void PrintPython::privateVars()
                                                            {
                                                              if (trace)
                                                              {
                                                                increaseIndent();
                                                            #line 788 "PrintPython.cpp"
  append(L"\n");
  append(L"def lookaheadString(self):\n");
  append(L"  result = \"\"");
                                                            #line 506 "PrintPython.cpp.template"
                                                                for (size_t i = 1; i <= grammar->k; ++i)
                                                                {
                                                            #line 795 "PrintPython.cpp"
  append(L"\n");
  append(L"  if self.l");
                                                            #line 509 "PrintPython.cpp.template"
                                                                 print(format.toString<wchar_t>(i));
                                                            #line 800 "PrintPython.cpp"
  append(L" > 0:\n");
  append(L"    result += ");
                                                            #line 511 "PrintPython.cpp.template"
                                                                  if (i != 1)
                                                                  {
                                                            #line 806 "PrintPython.cpp"
  append(L"\" \" + ");
                                                            #line 513 "PrintPython.cpp.template"
                                                                  }
                                                                  print(className.c_str());
                                                            #line 811 "PrintPython.cpp"
  append(L".TOKEN[self.l");
                                                            #line 515 "PrintPython.cpp.template"
                                                                  print(format.toString<wchar_t>(i));
                                                            #line 815 "PrintPython.cpp"
  append(L"]");
                                                            #line 516 "PrintPython.cpp.template"
                                                                  increaseIndent();
                                                                }
                                                                for (size_t i = 1; i <= grammar->k; ++i)
                                                                {
                                                                  decreaseIndent();
                                                                }
                                                            #line 824 "PrintPython.cpp"
  append(L"\n");
  append(L"  return result\n");
                                                            #line 524 "PrintPython.cpp.template"
                                                                decreaseIndent();
                                                              }
                                                              if (memoization)
                                                              {
                                                                increaseIndent();
                                                                int bits = Math::bits(grammar->conflictCount);
                                                            #line 834 "PrintPython.cpp"
  append(L"\n");
  append(L"def memoize(self, i, e, v):\n");
  append(L"  self.memo[(e << ");
                                                            #line 532 "PrintPython.cpp.template"
                                                                print(format.toString<wchar_t>(bits));
                                                            #line 840 "PrintPython.cpp"
  append(L") + i] = v\n");
  append(L"\n");
  append(L"def memoized(self, i, e):\n");
  append(L"  return self.memo.get((e << ");
                                                            #line 536 "PrintPython.cpp.template"
                                                                print(format.toString<wchar_t>(bits));
                                                            #line 847 "PrintPython.cpp"
  append(L") + i, 0)\n");
                                                            #line 538 "PrintPython.cpp.template"
                                                                decreaseIndent();
                                                              }
                                                              if (useGlr)
                                                              {
                                                                decreaseIndent();
                                                              }
                                                            }

                                                            void PrintPython::printFileProcessor()
                                                            {
                                                              if (tree)
                                                              {
                                                            #line 862 "PrintPython.cpp"
  append(L"\n");
  append(L"class ContentCounter:\n");
  append(L"  def getLength(self):\n");
  append(L"    return self.length\n");
  append(L"\n");
  append(L"  def reset(self, _):\n");
  append(L"    self.length = 0\n");
  append(L"\n");
  append(L"  def startNonterminal(self, name, begin):\n");
  append(L"    pass\n");
  append(L"\n");
  append(L"  def endNonterminal(self, name, end):\n");
  append(L"    pass\n");
  append(L"\n");
  append(L"  def terminal(self, _, begin, end):\n");
  append(L"    self.length += end - begin\n");
  append(L"\n");
  append(L"  def whitespace(self, begin, end):\n");
  append(L"    self.length += end - begin\n");
                                                            #line 569 "PrintPython.cpp.template"
                                                              }
                                                            #line 884 "PrintPython.cpp"
  append(L"\n");
  append(L"class ParseJob:\n");
  append(L"\n");
  append(L"  def __init__(self, name, parser");
                                                            #line 573 "PrintPython.cpp.template"
                                                              if (tree)
                                                              {
                                                                if (isLrParser)
                                                                {
                                                            #line 894 "PrintPython.cpp"
  append(L", parseTreeBuilder");
                                                            #line 577 "PrintPython.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 900 "PrintPython.cpp"
  append(L", contentCounter");
                                                            #line 580 "PrintPython.cpp.template"
                                                                }
                                                              }
                                                            #line 905 "PrintPython.cpp"
  append(L"):\n");
  append(L"    self.name = name\n");
  append(L"    self.parser = parser");
                                                            #line 584 "PrintPython.cpp.template"
                                                              if (tree)
                                                              {
                                                                if (isLrParser)
                                                                {
                                                            #line 914 "PrintPython.cpp"
  append(L"\n");
  append(L"    self.parseTreeBuilder = parseTreeBuilder\n");
  append(L"    self.contentCounter = ContentCounter()");
                                                            #line 590 "PrintPython.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 922 "PrintPython.cpp"
  append(L"\n");
  append(L"    self.contentCounter = contentCounter");
                                                            #line 594 "PrintPython.cpp.template"
                                                                }
                                                              }
                                                            #line 928 "PrintPython.cpp"
  append(L"\n");
  append(L"\n");
  append(L"def main(args):\n");
  append(L"  if len(args) < 2:\n");
  append(L"    sys.stderr.write(\"Usage: python ");
                                                            #line 600 "PrintPython.cpp.template"
                                                              print(className.c_str());
                                                            #line 936 "PrintPython.cpp"
  append(L".py [-q] [-r N] [-t N] ENDING...\\n\")\n");
  append(L"    sys.stderr.write(\"\\n\")\n");
  append(L"    sys.stderr.write(\"  parse all files that have names ending with ENDING, in current dir and below,\\n\")\n");
  append(L"    sys.stderr.write(\"  and display performance summary.\\n\")\n");
  append(L"    sys.stderr.write(\"\\n\")\n");
  append(L"    sys.stderr.write(\"  -q     do not show file names\\n\")\n");
  append(L"    sys.stderr.write(\"  -r N   repeat N times\\n\")\n");
  append(L"    sys.stderr.write(\"  -t N   repeat until N seconds have elapsed\\n\")\n");
  append(L"  else:\n");
  append(L"    quiet = False\n");
  append(L"    parsed = 0\n");
  append(L"    errorCount = 0\n");
  append(L"    parsers = []\n");
  append(L"    repeat = 1\n");
  append(L"    timeout = 0\n");
  append(L"    i = 1\n");
  append(L"    while i < len(args) and args[i].startswith(\"-\"):\n");
  append(L"      opt = ' '\n");
  append(L"      if len(args[i]) == 2:\n");
  append(L"        opt = args[i][1]\n");
  append(L"      if opt == 'q':\n");
  append(L"        quiet = True\n");
  append(L"      elif opt == 'r':\n");
  append(L"        i += 1\n");
  append(L"        repeat = int(args[i])\n");
  append(L"        timeout = 0\n");
  append(L"      elif opt == 't':\n");
  append(L"        repeat = 0\n");
  append(L"        i += 1\n");
  append(L"        timeout = int(args[i])\n");
  append(L"        timeout *= 1000\n");
  append(L"      else:\n");
  append(L"        raise Exception(\"invalid option: \" + args[i])\n");
  append(L"      i += 1\n");
  append(L"\n");
  append(L"    start = int(round(time.time() * 1000))\n");
  append(L"    while i < len(args):\n");
  append(L"      for path in glob.iglob(\"**/*\", recursive=True):\n");
  append(L"        if path.endswith(args[i]):\n");
  append(L"          if not quiet:\n");
  append(L"            print(\"loading \" + path)");
                                                            #line 641 "PrintPython.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 981 "PrintPython.cpp"
  append(L"\n");
  append(L"          contentCounter = ContentCounter()");
                                                            #line 644 "PrintPython.cpp.template"
                                                                if (isLrParser)
                                                                {
                                                            #line 987 "PrintPython.cpp"
  append(L"\n");
  append(L"          parseTreeBuilder = ");
                                                            #line 647 "PrintPython.cpp.template"
                                                                  print(className.c_str());
                                                            #line 992 "PrintPython.cpp"
  append(L".ParseTreeBuilder()");
                                                            #line 648 "PrintPython.cpp.template"
                                                                }
                                                              }
                                                            #line 997 "PrintPython.cpp"
  append(L"\n");
  append(L"          content = read(path)\n");
  append(L"          parsers.append(ParseJob(path, ");
                                                            #line 652 "PrintPython.cpp.template"
                                                              print(className.c_str());
                                                            #line 1003 "PrintPython.cpp"
  append(L"(content");
                                                            #line 654 "PrintPython.cpp.template"
                                                              if (tree)
                                                              {
                                                                if (isLrParser)
                                                                {
                                                            #line 1010 "PrintPython.cpp"
  append(L", parseTreeBuilder");
                                                            #line 658 "PrintPython.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1016 "PrintPython.cpp"
  append(L", contentCounter");
                                                            #line 661 "PrintPython.cpp.template"
                                                                }
                                                              }
                                                            #line 1021 "PrintPython.cpp"
  append(L")");
                                                            #line 663 "PrintPython.cpp.template"
                                                              if (tree)
                                                              {
                                                                if (isLrParser)
                                                                {
                                                            #line 1028 "PrintPython.cpp"
  append(L", parseTreeBuilder");
                                                            #line 667 "PrintPython.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1034 "PrintPython.cpp"
  append(L", contentCounter");
                                                            #line 670 "PrintPython.cpp.template"
                                                                }
                                                              }
                                                            #line 1039 "PrintPython.cpp"
  append(L"))\n");
  append(L"      i += 1\n");
  append(L"\n");
  append(L"    if len(parsers) != 0:\n");
  append(L"      msec = int(round(time.time() * 1000)) - start\n");
  append(L"\n");
  append(L"      if not quiet:\n");
  append(L"        print()\n");
  append(L"      plural = \"\" if len(parsers) == 1 else \"s\"\n");
  append(L"      print(\"loaded \" + str(len(parsers)) + \" file\" + plural + \" in \" + str(msec) + \" msec\")\n");
  append(L"      if not quiet:\n");
  append(L"        print()\n");
  append(L"      print(\"\", end=\"\", flush=True)\n");
  append(L"\n");
  append(L"      start = int(round(time.time() * 1000))\n");
  append(L"      i = 0\n");
  append(L"      while True:\n");
  append(L"        if repeat != 0 and i >= repeat:\n");
  append(L"          break\n");
  append(L"        if timeout != 0 and int(round(time.time() * 1000)) - start >= timeout:\n");
  append(L"          break\n");
  append(L"\n");
  append(L"        for job in parsers:\n");
  append(L"          if job.parser != None:\n");
  append(L"            if not quiet:\n");
  append(L"              print(\"parsing \" + job.name, end=\"\")\n");
  append(L"            job.parser");
                                                            #line 698 "PrintPython.cpp.template"
                                                                  if (useGlr)
                                                                  {
                                                            #line 1070 "PrintPython.cpp"
  append(L".thread");
                                                            #line 700 "PrintPython.cpp.template"
                                                                  }
                                                            #line 1074 "PrintPython.cpp"
  append(L".reset(0, 0, 0)\n");
  append(L"            try:\n");
  append(L"              pe = job.parser.parse_");
                                                            #line 703 "PrintPython.cpp.template"
                                                                  print(Format::acceptableName<WString>(grammar->startSymbol()->name).c_str());
                                                            #line 1080 "PrintPython.cpp"
  append(L"()\n");
  append(L"            except ");
                                                            #line 705 "PrintPython.cpp.template"
                                                                  print(className.c_str());
                                                            #line 1085 "PrintPython.cpp"
  append(L".ParseException as pe:\n");
  append(L"              errorCount += 1\n");
  append(L"              if quiet:\n");
  append(L"                print(\"parsing \" + job.name)\n");
  append(L"              print(\": error: \" + job.parser.GetErrorMessage(pe))\n");
  append(L"              job.parser = None\n");
  append(L"            if not quiet:\n");
  append(L"              print()");
                                                            #line 713 "PrintPython.cpp.template"
                                                                  if (tree)
                                                                  {
                                                                    if (isLrParser)
                                                                    {
                                                            #line 1099 "PrintPython.cpp"
  append(L"\n");
  append(L"            job.parseTreeBuilder.serialize(job.contentCounter)");
                                                            #line 718 "PrintPython.cpp.template"
                                                                    }
                                                            #line 1104 "PrintPython.cpp"
  append(L"\n");
  append(L"            if job.contentCounter.getLength() != len(job.parser.input):\n");
  append(L"              raise Exception(\"content counter saw \" + str(job.contentCounter.getLength()) + \", but input length is \" + str(len(job.parser.input)))");
                                                            #line 722 "PrintPython.cpp.template"
                                                                  }
                                                            #line 1110 "PrintPython.cpp"
  append(L"\n");
  append(L"            parsed += len(job.parser.input)\n");
  append(L"        i += 1\n");
  append(L"      msec = int(round(time.time() * 1000)) - start\n");
  append(L"      mbPerSec = \"\"\n");
  append(L"      if msec != 0:\n");
  append(L"        mbPerSec = \"%.2f\" % (float(parsed) / 1024e0 / 1024e0 * 1000e0 / float(msec))\n");
  append(L"\n");
  append(L"      if not quiet:\n");
  append(L"        print()\n");
  append(L"      plural = \"\" if parsed == 1 else \"s\"\n");
  append(L"      print(\"parsed \" + str(parsed) + \" byte\" + plural +\n");
  append(L"            \" in \" + str(msec) + \" msec\", end=\"\")\n");
  append(L"      if mbPerSec != \"\":\n");
  append(L"        print(\" (\" + mbPerSec + \" MB/sec)\", end=\"\")\n");
  append(L"      print()\n");
  append(L"      plural = \"\" if errorCount == 1 else \"s\"\n");
  append(L"      print(str(errorCount) + \" error\" + plural)\n");
  append(L"\n");
  append(L"if __name__ == '__main__':\n");
  append(L"  sys.exit(main(sys.argv))\n");
                                                            #line 745 "PrintPython.cpp.template"
                                                            }

                                                            void PrintPython::printReadMethod()
                                                            {
                                                            #line 1137 "PrintPython.cpp"
  append(L"\n");
  append(L"def read(arg):\n");
  append(L"  if arg.startswith(\"{\") and arg.endswith(\"}\"):\n");
  append(L"    return arg[1:len(arg) - 1]\n");
  append(L"  else:\n");
  append(L"    with open(arg, \"r\", encoding=\"utf-8\") as file:\n");
  append(L"      content = file.read()\n");
  append(L"    if len(content) > 0 and content[0] == \"\\ufeff\":\n");
  append(L"      content = content[1:]\n");
  append(L"    return content\n");
                                                            #line 759 "PrintPython.cpp.template"
                                                            }

                                                            void PrintPython::printInterface()
                                                            {
                                                              if (! packageName.empty())
                                                              {
                                                            #line 1155 "PrintPython.cpp"
  append(L"\n");
  append(L"package ");
                                                            #line 766 "PrintPython.cpp.template"
                                                                print(packageName.c_str());
                                                            #line 1160 "PrintPython.cpp"
  append(L";\n");
                                                            #line 768 "PrintPython.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                                if (main || useGlr)
                                                                {
                                                            #line 1168 "PrintPython.cpp"
  append(L"\n");
  append(L"import java.io.IOException;\n");
  append(L"import java.io.Writer;\n");
                                                            #line 776 "PrintPython.cpp.template"
                                                                }
                                                            #line 1174 "PrintPython.cpp"
  append(L"\n");
  append(L"import java.util.Arrays;");
                                                            #line 778 "PrintPython.cpp.template"
                                                              }
                                                            #line 1179 "PrintPython.cpp"
  append(L"\n");
  append(L"public interface ");
                                                            #line 780 "PrintPython.cpp.template"
                                                              print(className.c_str());
                                                            #line 1184 "PrintPython.cpp"
  append(L"\n");
  append(L"{\n");
  append(L"  public void initialize(CharSequence input");
                                                            #line 783 "PrintPython.cpp.template"
                                                              if (noLexer)
                                                              {
                                                            #line 1191 "PrintPython.cpp"
  append(L", Lexer l");
                                                            #line 785 "PrintPython.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                            #line 1197 "PrintPython.cpp"
  append(L", ");
                                                            #line 788 "PrintPython.cpp.template"
                                                                if (isLrParser)
                                                                {
                                                            #line 1202 "PrintPython.cpp"
  append(L"BottomUp");
                                                            #line 791 "PrintPython.cpp.template"
                                                                }
                                                            #line 1206 "PrintPython.cpp"
  append(L"EventHandler eh");
                                                            #line 793 "PrintPython.cpp.template"
                                                              }
                                                            #line 1210 "PrintPython.cpp"
  append(L");\n");
  append(L"  public void parse();\n");
  append(L"  public void Reset();\n");
  append(L"  public String getErrorMessage(ParseException e);\n");
                                                            #line 798 "PrintPython.cpp.template"
                                                              printParseException();
                                                              printEventHandlerImplementation();
                                                            #line 1218 "PrintPython.cpp"
  append(L"}\n");
                                                            #line 801 "PrintPython.cpp.template"
                                                            }

                                                            void PrintPython::printParseException()
                                                            {
                                                            #line 1225 "PrintPython.cpp"
  append(L"\n");
  append(L"class ParseException(Exception):\n");
                                                            #line 807 "PrintPython.cpp.template"
                                                              increaseIndent();
                                                            #line 1230 "PrintPython.cpp"
  append(L"\n");
  append(L"def __init__(self, b, e, s, o, x");
                                                            #line 809 "PrintPython.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 1236 "PrintPython.cpp"
  append(L", ambiguousInput = False");
                                                            #line 811 "PrintPython.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 1241 "PrintPython.cpp"
  append(L", ambiguityDescriptor = None");
                                                            #line 813 "PrintPython.cpp.template"
                                                                }
                                                              }
                                                            #line 1246 "PrintPython.cpp"
  append(L"):\n");
  append(L"  self.begin = b\n");
  append(L"  self.end = e\n");
  append(L"  self.state = s\n");
  append(L"  self.offending = o\n");
  append(L"  self.expected = x");
                                                            #line 820 "PrintPython.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 1256 "PrintPython.cpp"
  append(L"\n");
  append(L"  self.ambiguousInput = ambiguousInput");
                                                            #line 823 "PrintPython.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 1262 "PrintPython.cpp"
  append(L"\n");
  append(L"  self.ambiguityDescriptor = ambiguityDescriptor");
                                                            #line 826 "PrintPython.cpp.template"
                                                                }
                                                              }
                                                            #line 1268 "PrintPython.cpp"
  append(L"\n");
  append(L"\n");
  append(L"def error(self):\n");
  append(L"  if ");
                                                            #line 831 "PrintPython.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 1276 "PrintPython.cpp"
  append(L"self.ambiguousInput:\n");
  append(L"    return \"ambiguous input\"\n");
  append(L"  elif ");
                                                            #line 835 "PrintPython.cpp.template"
                                                              }
                                                            #line 1282 "PrintPython.cpp"
  append(L"self.offending < 0:\n");
  append(L"    return \"lexical analysis failed\"\n");
  append(L"  else:\n");
  append(L"    return \"syntax error\"\n");
                                                            #line 840 "PrintPython.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 1290 "PrintPython.cpp"
  append(L"\n");
  append(L"def serialize(self, eventHandler):");
                                                            #line 843 "PrintPython.cpp.template"
                                                                if (rejectsAmbiguity())
                                                                {
                                                            #line 1296 "PrintPython.cpp"
  append(L"\n");
  append(L"  self.ambiguityDescriptor.serialize(eventHandler)");
                                                            #line 846 "PrintPython.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1303 "PrintPython.cpp"
  append(L"\n");
  append(L"  pass");
                                                            #line 850 "PrintPython.cpp.template"
                                                                }
                                                            #line 1308 "PrintPython.cpp"
  append(L"\n");
                                                            #line 852 "PrintPython.cpp.template"
                                                              }
                                                            #line 1312 "PrintPython.cpp"
  append(L"\n");
  append(L"def getBegin(self):\n");
  append(L"  return self.begin\n");
  append(L"\n");
  append(L"def getEnd(self):\n");
  append(L"  return self.end\n");
  append(L"\n");
  append(L"def getState(self):\n");
  append(L"  return self.state\n");
  append(L"\n");
  append(L"def getOffending(self):\n");
  append(L"  return self.offending\n");
  append(L"\n");
  append(L"def getExpected(self):\n");
  append(L"  return self.expected\n");
  append(L"\n");
  append(L"def isAmbiguousInput(self):\n");
  append(L"  return ");
                                                            #line 870 "PrintPython.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 1334 "PrintPython.cpp"
  append(L"self.ambiguousInput");
                                                            #line 872 "PrintPython.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 1340 "PrintPython.cpp"
  append(L"False");
                                                            #line 875 "PrintPython.cpp.template"
                                                              }
                                                              decreaseIndent();
                                                            #line 1345 "PrintPython.cpp"
  append(L"\n");
                                                            #line 878 "PrintPython.cpp.template"
                                                              if (noLexer)
                                                              {
                                                            #line 1350 "PrintPython.cpp"
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
                                                            #line 893 "PrintPython.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                            #line 1368 "PrintPython.cpp"
  append(L"\n");
  append(L"class TopDownTreeBuilder:\n");
                                                            #line 898 "PrintPython.cpp.template"
                                                                increaseIndent();
                                                            #line 1373 "PrintPython.cpp"
  append(L"\n");
  append(L"def reset(self, inputString):\n");
  append(L"  self.input = inputString\n");
  append(L"  self.stack = []\n");
  append(L"  self.top = -1\n");
  append(L"\n");
  append(L"def startNonterminal(self, name, begin):\n");
  append(L"  nonterminal = ");
                                                            #line 906 "PrintPython.cpp.template"
                                                                print(className.c_str());
                                                            #line 1384 "PrintPython.cpp"
  append(L".Nonterminal(name, begin, begin)\n");
  append(L"  if self.top >= 0:\n");
  append(L"    self.addChild(nonterminal)\n");
  append(L"  self.top += 1\n");
  append(L"  self.stack[self.top] = nonterminal\n");
  append(L"\n");
  append(L"def endNonterminal(self, _, end):\n");
  append(L"  self.stack[self.top].end = end\n");
  append(L"  if self.top > 0:\n");
  append(L"    self.top -= 1\n");
  append(L"\n");
  append(L"def terminal(self, name, begin, end):\n");
  append(L"  self.addChild(");
                                                            #line 919 "PrintPython.cpp.template"
                                                                print(className.c_str());
                                                            #line 1400 "PrintPython.cpp"
  append(L".Terminal(name, begin, end))\n");
  append(L"\n");
  append(L"def whitespace(self, begin, end):\n");
  append(L"  pass\n");
  append(L"\n");
  append(L"def addChild(self, s):\n");
  append(L"  current = self.stack[self.top]\n");
  append(L"  current.addChild(s)\n");
  append(L"\n");
  append(L"def serialize(self, e):\n");
  append(L"  e.reset(self.input)\n");
  append(L"  self.stack[0].send(e)\n");
                                                            #line 932 "PrintPython.cpp.template"
                                                                decreaseIndent();
                                                            #line 1415 "PrintPython.cpp"
  append(L"\n");
  append(L"class Symbol:\n");
                                                            #line 935 "PrintPython.cpp.template"
                                                                increaseIndent();
                                                            #line 1420 "PrintPython.cpp"
  append(L"\n");
  append(L"def __init__(self, name, begin, end):\n");
  append(L"  self.name = name\n");
  append(L"  self.begin = begin\n");
  append(L"  self.end = end\n");
  append(L"\n");
  append(L"def getName(self):\n");
  append(L"  return self.name\n");
  append(L"\n");
  append(L"def getBegin(self):\n");
  append(L"  return self.begin\n");
  append(L"\n");
  append(L"def getEnd(self):\n");
  append(L"  return self.end\n");
                                                            #line 950 "PrintPython.cpp.template"
                                                                decreaseIndent();
                                                            #line 1437 "PrintPython.cpp"
  append(L"\n");
  append(L"class Nonterminal(Symbol):\n");
                                                            #line 953 "PrintPython.cpp.template"
                                                                increaseIndent();
                                                            #line 1442 "PrintPython.cpp"
  append(L"\n");
  append(L"def __init__(self, name, begin, end, children):\n");
  append(L"  super().__init__(name, begin, end)\n");
  append(L"  self.children = children\n");
  append(L"\n");
  append(L"def addChild(self, s):\n");
  append(L"  self.children = self.children.append(s)\n");
  append(L"\n");
  append(L"def send(self, e):\n");
  append(L"  e.startNonterminal(self.getName(), self.getBegin())\n");
  append(L"  pos = self.getBegin()\n");
  append(L"  for c in self.children:\n");
  append(L"    if pos < c.getBegin():\n");
  append(L"      e.whitespace(pos, c.getBegin())\n");
  append(L"    c.send(e)\n");
  append(L"    pos = c.getEnd()\n");
  append(L"  if pos < self.getEnd():\n");
  append(L"    e.whitespace(pos, self.getEnd())\n");
  append(L"  e.endNonterminal(self.getName(), self.getEnd())\n");
                                                            #line 973 "PrintPython.cpp.template"
                                                                decreaseIndent();
                                                            #line 1464 "PrintPython.cpp"
  append(L"\n");
  append(L"class Terminal(Symbol):\n");
                                                            #line 976 "PrintPython.cpp.template"
                                                                increaseIndent();
                                                            #line 1469 "PrintPython.cpp"
  append(L"\n");
  append(L"def __init__(self, name, begin, end):\n");
  append(L"  super().__init__(name, begin, end)\n");
  append(L"\n");
  append(L"def send(self, e):\n");
  append(L"  e.terminal(self.getName(), self.getBegin(), self.getEnd())\n");
                                                            #line 983 "PrintPython.cpp.template"
                                                                decreaseIndent();
                                                              }
                                                            }

                                                            void PrintPython::printEventHandlerImplementation()
                                                            {
                                                              if (tree)
                                                              {
                                                                if (main || useGlr)
                                                                {
                                                            #line 1487 "PrintPython.cpp"
  append(L"\n");
  append(L"class XmlSerializer:\n");
                                                            #line 995 "PrintPython.cpp.template"
                                                                  increaseIndent();
                                                            #line 1492 "PrintPython.cpp"
  append(L"\n");
  append(L"def reset(self, inputString):\n");
  append(L"  sys.stdout.reconfigure(encoding=\"utf-8\")\n");
  append(L"  print(\"<?xml version=\\\"1.0\\\" encoding=\\\"UTF-8\\\"?>\", end=\"\")\n");
  append(L"  self.input = inputString\n");
  append(L"  self.delayedTag = None\n");
  append(L"  self.hasChildElement = False\n");
  append(L"  self.depth = 0\n");
  append(L"\n");
  append(L"def startNonterminal(self, tag, _):\n");
  append(L"  if self.delayedTag != None:\n");
  append(L"    print(\"<\", end=\"\")\n");
  append(L"    print(self.delayedTag, end=\"\")\n");
  append(L"    print(\">\", end=\"\")\n");
  append(L"  self.delayedTag = tag\n");
  append(L"  if self.indent:\n");
  append(L"    print()\n");
  append(L"    for _ in range(self.depth):\n");
  append(L"      print(\"  \", end=\"\")\n");
  append(L"  self.hasChildElement = False\n");
  append(L"  self.depth += 1\n");
  append(L"\n");
  append(L"def endNonterminal(self, tag, _):\n");
  append(L"  self.depth -= 1\n");
  append(L"  if self.delayedTag != None:\n");
  append(L"    self.delayedTag = None\n");
  append(L"    print(\"<\", end=\"\")\n");
  append(L"    print(tag, end=\"\")\n");
  append(L"    print(\"/>\", end=\"\")\n");
  append(L"  else:\n");
  append(L"    if self.indent:\n");
  append(L"      if self.hasChildElement:\n");
  append(L"        print()\n");
  append(L"        for _ in range(self.depth):\n");
  append(L"          print(\"  \", end=\"\")\n");
  append(L"    print(\"</\", end=\"\")\n");
  append(L"    print(tag, end=\"\")\n");
  append(L"    print(\">\", end=\"\")\n");
  append(L"  self.hasChildElement = True\n");
  append(L"\n");
  append(L"def whitespace(self, b, e):\n");
  append(L"  self.characters(b, e)\n");
  append(L"\n");
  append(L"def characters(self, b, e):\n");
  append(L"  if b < e:\n");
  append(L"    if self.delayedTag != None:\n");
  append(L"      print(\"<\", end=\"\")\n");
  append(L"      print(self.delayedTag, end=\"\")\n");
  append(L"      print(\">\", end=\"\")\n");
  append(L"      self.delayedTag = None\n");
  append(L"    i = b\n");
  append(L"    while i < e:\n");
  append(L"      c = self.input[i]\n");
  append(L"      i += 1\n");
  append(L"      if c == '&':\n");
  append(L"        print(\"&amp;\", end=\"\")\n");
  append(L"      elif c == '<':\n");
  append(L"        print(\"&lt;\", end=\"\")\n");
  append(L"      elif c == '>':\n");
  append(L"        print(\"&gt;\", end=\"\")\n");
  append(L"      else:\n");
  append(L"        print(str(c), end=\"\")\n");
  append(L"\n");
  append(L"def terminal(self, tag, b, e):\n");
  append(L"  if tag[0] == '\\'':\n");
  append(L"    tag = \"TOKEN\"\n");
  append(L"  self.startNonterminal(tag, b)\n");
  append(L"  self.characters(b, e)\n");
  append(L"  self.endNonterminal(tag, e)\n");
                                                            #line 1065 "PrintPython.cpp.template"
                                                                  decreaseIndent();
                                                                }
                                                                if (isLrParser)
                                                                {
                                                            #line 1567 "PrintPython.cpp"
  append(L"\n");
  append(L"class ParseTreeBuilder:\n");
                                                            #line 1071 "PrintPython.cpp.template"
                                                                  increaseIndent();
                                                            #line 1572 "PrintPython.cpp"
  append(L"\n");
  append(L"def reset(self, inputString):\n");
  append(L"  self.input = inputString\n");
  append(L"  self.stack = []\n");
  append(L"\n");
  append(L"def nonterminal(self, name, begin, end, count):");
                                                            #line 1078 "PrintPython.cpp.template"
                                                                  if (rejectsAmbiguity())
                                                                  {
                                                            #line 1582 "PrintPython.cpp"
  append(L"\n");
  append(L"  if count > len(self.stack):\n");
  append(L"    content = self.pop(len(self.stack))\n");
  append(L"    e = end\n");
  append(L"    if len(content) != 0:\n");
  append(L"      e = content[0].getBegin()\n");
  append(L"    self.nonterminal(\"UNAMBIGUOUS\", begin, e, 0)\n");
  append(L"    for symbol in content:\n");
  append(L"      self.push(symbol)\n");
  append(L"    count = len(self.stack)");
                                                            #line 1089 "PrintPython.cpp.template"
                                                                  }
                                                            #line 1595 "PrintPython.cpp"
  append(L"\n");
  append(L"  self.push(");
                                                            #line 1091 "PrintPython.cpp.template"
                                                                  print(className.c_str());
                                                            #line 1600 "PrintPython.cpp"
  append(L".Nonterminal(name, begin, end, self.pop(count)))\n");
  append(L"\n");
  append(L"def terminal(self, name, begin, end):\n");
  append(L"  self.push(");
                                                            #line 1095 "PrintPython.cpp.template"
                                                                  print(className.c_str());
                                                            #line 1607 "PrintPython.cpp"
  append(L".Terminal(name, begin, end))\n");
                                                            #line 1097 "PrintPython.cpp.template"
                                                              if (minimalAmbiguity)
                                                              {
                                                            #line 1612 "PrintPython.cpp"
  append(L"\n");
  append(L"\n");
  append(L"def ambiguity(self, begin, end):\n");
  append(L"  pass\n");
                                                            #line 1103 "PrintPython.cpp.template"
                                                              }
                                                            #line 1619 "PrintPython.cpp"
  append(L"\n");
  append(L"def serialize(self, e):\n");
  append(L"  e.reset(self.input)\n");
  append(L"  for symbol in self.stack:\n");
  append(L"    symbol.send(e)\n");
  append(L"\n");
  append(L"def push(self, s):\n");
  append(L"  self.stack.append(s)\n");
  append(L"\n");
  append(L"def pop(self, count):\n");
  append(L"  if count == 0:\n");
  append(L"    result = []\n");
  append(L"  else:\n");
  append(L"    result = self.stack[-count:]\n");
  append(L"    self.stack = self.stack[: -count]\n");
  append(L"  return result\n");
                                                            #line 1120 "PrintPython.cpp.template"
                                                                  decreaseIndent();
                                                                }
                                                              }
                                                            }

                                                            void PrintPython::printTokenVars()
                                                            {
                                                            #line 1644 "PrintPython.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 1128 "PrintPython.cpp.template"
                                                              if (! isLrParser && (grammar->k > 1 ||
                                                                                   memoization ||
                                                                                   ! grammar->decisionPoints.empty()))
                                                              {
                                                            #line 1652 "PrintPython.cpp"
  append(L"lk,");
                                                            #line 1132 "PrintPython.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 1658 "PrintPython.cpp"
  append(L"   ");
                                                            #line 1135 "PrintPython.cpp.template"
                                                              }
                                                            #line 1662 "PrintPython.cpp"
  append(L" b0, e0 int");
                                                            #line 1136 "PrintPython.cpp.template"
                                                              for (size_t k = 1; k <= grammar->k; ++k)
                                                              {
                                                                Format format;
                                                                wchar_t *asString = format.toString<wchar_t>(k);
                                                            #line 1669 "PrintPython.cpp"
  append(L"\n");
  append(L"  l");
                                                            #line 1141 "PrintPython.cpp.template"
                                                                print(asString);
                                                            #line 1674 "PrintPython.cpp"
  append(L", b");
                                                            #line 1142 "PrintPython.cpp.template"
                                                                print(asString);
                                                            #line 1678 "PrintPython.cpp"
  append(L", e");
                                                            #line 1143 "PrintPython.cpp.template"
                                                                print(asString);
                                                            #line 1682 "PrintPython.cpp"
  append(L" int");
                                                            #line 1144 "PrintPython.cpp.template"
                                                              }
                                                              if (hasBacktracking)
                                                              {
                                                            #line 1688 "PrintPython.cpp"
  append(L"\n");
  append(L"  bx, ex, sx, lx, tx int");
                                                            #line 1148 "PrintPython.cpp.template"
                                                              }
                                                              else if (isLrParser && ! useGlr)
                                                              {
                                                            #line 1695 "PrintPython.cpp"
  append(L"\n");
  append(L"  iStack []int\n");
  append(L"  top int");
                                                            #line 1153 "PrintPython.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                                if (isLrParser)
                                                                {
                                                                  if (useGlr)
                                                                  {
                                                            #line 1707 "PrintPython.cpp"
  append(L"\n");
  append(L"  bw, bs, es int");
                                                            #line 1161 "PrintPython.cpp.template"
                                                                  }
                                                            #line 1712 "PrintPython.cpp"
  append(L"\n");
  append(L"  eventHandler BottomUpEventHandler");
                                                            #line 1163 "PrintPython.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1719 "PrintPython.cpp"
  append(L"\n");
  append(L"  eventHandler EventHandler");
                                                            #line 1167 "PrintPython.cpp.template"
                                                                }
                                                              }
                                                            }

                                                            void PrintPython::printSimpleMain()
                                                            {
                                                            #line 1729 "PrintPython.cpp"
  append(L"\n");
  append(L"def main(args):\n");
  append(L"  if len(args) < 2:\n");
  append(L"    sys.stderr.write(\"Usage: python ");
                                                            #line 1176 "PrintPython.cpp.template"
                                                              print(className.c_str());
                                                            #line 1736 "PrintPython.cpp"
  append(L".py ");
                                                            #line 1177 "PrintPython.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 1741 "PrintPython.cpp"
  append(L"[-i] ");
                                                            #line 1179 "PrintPython.cpp.template"
                                                              }
                                                            #line 1745 "PrintPython.cpp"
  append(L"INPUT...\\n\")\n");
  append(L"    sys.stderr.write(\"\\n\")\n");
  append(L"    sys.stderr.write(\"  parse INPUT, which is either a filename or literal text enclosed in curly braces\\n\")");
                                                            #line 1183 "PrintPython.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 1752 "PrintPython.cpp"
  append(L"\n");
  append(L"    sys.stderr.write(\"\\n\")\n");
  append(L"    sys.stderr.write(\"  Option:\\n\")\n");
  append(L"    sys.stderr.write(\"    -i     indented parse tree\\n\")");
                                                            #line 1189 "PrintPython.cpp.template"
                                                              }
                                                            #line 1759 "PrintPython.cpp"
  append(L"\n");
  append(L"  else:");
                                                            #line 1191 "PrintPython.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 1765 "PrintPython.cpp"
  append(L"\n");
  append(L"    indent = False");
                                                            #line 1194 "PrintPython.cpp.template"
                                                              }
                                                            #line 1770 "PrintPython.cpp"
  append(L"\n");
  append(L"    for arg in args[1:]:");
                                                            #line 1196 "PrintPython.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 1776 "PrintPython.cpp"
  append(L"\n");
  append(L"      if arg == \"-i\":\n");
  append(L"        indent = True\n");
  append(L"        continue\n");
  append(L"      s = ");
                                                            #line 1202 "PrintPython.cpp.template"
                                                                print(className.c_str());
                                                            #line 1784 "PrintPython.cpp"
  append(L".XmlSerializer()\n");
  append(L"      s.indent = indent");
                                                            #line 1204 "PrintPython.cpp.template"
                                                                if (isLrParser)
                                                                {
                                                            #line 1790 "PrintPython.cpp"
  append(L"\n");
  append(L"      b = ");
                                                            #line 1207 "PrintPython.cpp.template"
                                                                  print(className.c_str());
                                                            #line 1795 "PrintPython.cpp"
  append(L".ParseTreeBuilder()");
                                                            #line 1208 "PrintPython.cpp.template"
                                                                }
                                                              }
                                                            #line 1800 "PrintPython.cpp"
  append(L"\n");
  append(L"      inputString = read(arg)\n");
  append(L"      parser = ");
                                                            #line 1212 "PrintPython.cpp.template"
                                                              print(className.c_str());
                                                            #line 1806 "PrintPython.cpp"
  append(L"(inputString");
                                                            #line 1213 "PrintPython.cpp.template"
                                                              if (noLexer)
                                                              {
                                                            #line 1811 "PrintPython.cpp"
  append(L", ");
                                                            #line 1215 "PrintPython.cpp.template"
                                                                print(className.c_str());
                                                            #line 1815 "PrintPython.cpp"
  append(L"Lexer()");
                                                            #line 1216 "PrintPython.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                            #line 1821 "PrintPython.cpp"
  append(L", ");
                                                            #line 1219 "PrintPython.cpp.template"
                                                                if (isLrParser)
                                                                {
                                                            #line 1826 "PrintPython.cpp"
  append(L"b");
                                                            #line 1221 "PrintPython.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1832 "PrintPython.cpp"
  append(L"s");
                                                            #line 1224 "PrintPython.cpp.template"
                                                                }
                                                              }
                                                            #line 1837 "PrintPython.cpp"
  append(L")");
                                                            #line 1226 "PrintPython.cpp.template"
                                                              if (trace)
                                                              {
                                                            #line 1842 "PrintPython.cpp"
  append(L"\n");
  append(L"      sys.stderr.reconfigure(encoding=\"utf-8\")\n");
  append(L"      ");
                                                            #line 1230 "PrintPython.cpp.template"
                                                                print(className.c_str());
                                                            #line 1848 "PrintPython.cpp"
  append(L".writeTrace(\"<?xml version=\\\"1.0\\\" encoding=\\\"UTF-8\\\"?\" + \">\\n<trace>\\n\")");
                                                            #line 1232 "PrintPython.cpp.template"
                                                              }
                                                            #line 1852 "PrintPython.cpp"
  append(L"\n");
  append(L"      try:\n");
  append(L"        parser.");
                                                            #line 1235 "PrintPython.cpp.template"
                                                              print(visibilityMethodPrefix());
                                                              print(Format::acceptableName<WString>(grammar->startSymbol()->name).c_str());
                                                            #line 1859 "PrintPython.cpp"
  append(L"()");
                                                            #line 1237 "PrintPython.cpp.template"
                                                              if (trace)
                                                              {
                                                            #line 1864 "PrintPython.cpp"
  append(L"\n");
  append(L"        ");
                                                            #line 1240 "PrintPython.cpp.template"
                                                                print(className.c_str());
                                                            #line 1869 "PrintPython.cpp"
  append(L".writeTrace(\"</trace>\\n\")");
                                                            #line 1241 "PrintPython.cpp.template"
                                                              }
                                                              if (tree && isLrParser)
                                                              {
                                                            #line 1875 "PrintPython.cpp"
  append(L"\n");
  append(L"        b.serialize(s)");
                                                            #line 1245 "PrintPython.cpp.template"
                                                              }
                                                            #line 1880 "PrintPython.cpp"
  append(L"\n");
  append(L"      except ");
                                                            #line 1247 "PrintPython.cpp.template"
                                                              print(className.c_str());
                                                            #line 1885 "PrintPython.cpp"
  append(L".ParseException as pe:");
                                                            #line 1248 "PrintPython.cpp.template"
                                                              if (rejectsAmbiguity() && tree)
                                                              {
                                                            #line 1890 "PrintPython.cpp"
  append(L"\n");
  append(L"        if pe.isAmbiguousInput():\n");
  append(L"          pe.serialize(s)\n");
  append(L"          print()");
                                                            #line 1253 "PrintPython.cpp.template"
                                                              }
                                                            #line 1897 "PrintPython.cpp"
  append(L"\n");
  append(L"        raise Exception (\"ParseException while processing \" + arg + \":\\n\" + parser.getErrorMessage(pe)) from pe\n");
  append(L"\n");
  append(L"if __name__ == '__main__':\n");
  append(L"  sys.exit(main(sys.argv))\n");
                                                            #line 1259 "PrintPython.cpp.template"
                                                            }

// End
