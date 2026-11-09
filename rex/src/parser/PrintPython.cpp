// This file was generated on Sun Nov 8, 2026 22:38 (UTC+01) by REx v7.0-SNAPSHOT which is Copyright (c) 1979-2026 by Gunther Rademacher <grd@gmx.net>
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
  append(L"  def __init__(self, link, id, begin, end):\n");
  append(L"    self.link = link\n");
  append(L"    self.id = id\n");
  append(L"    self.begin = begin\n");
  append(L"    self.end = end");
                                                            #line 134 "PrintPython.cpp.template"
                                                                if (shiftAmbiguity)
                                                                {
                                                            #line 203 "PrintPython.cpp"
  append(L"\n");
  append(L"    self.depth = 1 if link is None else link.depth + 1\n");
  append(L"\n");
  append(L"  def isTerminal(self):\n");
  append(L"    return False");
                                                            #line 140 "PrintPython.cpp.template"
                                                                }
                                                            #line 211 "PrintPython.cpp"
  append(L"\n");
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
  append(L"      ");
                                                            #line 153 "PrintPython.cpp.template"
                                                                if (shiftAmbiguity)
                                                                {
                                                            #line 228 "PrintPython.cpp"
  append(L"if eventHandler != None:\n");
  append(L"        ");
                                                            #line 156 "PrintPython.cpp.template"
                                                                }
                                                            #line 233 "PrintPython.cpp"
  append(L"current.execute(eventHandler)\n");
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
  append(L"  def __init__(self, link, id, begin, end):\n");
  append(L"    super().__init__(link, id, begin, end)\n");
  append(L"\n");
  append(L"  def execute(self, eventHandler):\n");
  append(L"    eventHandler.terminal(self.id, self.begin, self.end)");
                                                            #line 177 "PrintPython.cpp.template"
                                                                if (shiftAmbiguity)
                                                                {
                                                            #line 258 "PrintPython.cpp"
  append(L"\n");
  append(L"\n");
  append(L"  def isTerminal(self):\n");
  append(L"    return True");
                                                            #line 182 "PrintPython.cpp.template"
                                                                }
                                                            #line 265 "PrintPython.cpp"
  append(L"\n");
  append(L"\n");
  append(L"  def toString(self):\n");
  append(L"    return \"terminal(\" + ");
                                                            #line 186 "PrintPython.cpp.template"
                                                                print(className.c_str());
                                                            #line 272 "PrintPython.cpp"
  append(L".TOKEN[self.id] + \", \" + str(self.begin) + \", \" + str(self.end) + \")\"\n");
  append(L"\n");
  append(L"class NonterminalEvent(DeferredEvent):\n");
  append(L"\n");
  append(L"  def __init__(self, link, id, begin, end, count):\n");
  append(L"    super().__init__(link, id, begin, end)\n");
  append(L"    self.count = count\n");
  append(L"\n");
  append(L"  def execute(self, eventHandler):\n");
  append(L"    eventHandler.nonterminal(self.id, self.begin, self.end, self.count)\n");
  append(L"\n");
  append(L"  def toString(self):\n");
  append(L"    return \"nonterminal(\" + ");
                                                            #line 199 "PrintPython.cpp.template"
                                                                printSyntheticNamePrefix(true, L"self.id");
                                                                print(className.c_str());
                                                            #line 289 "PrintPython.cpp"
  append(L".NONTERMINAL[self.id]");
                                                            #line 201 "PrintPython.cpp.template"
                                                                printSyntheticNameSuffix(true, L"self.id");
                                                            #line 293 "PrintPython.cpp"
  append(L" + \", \" + str(self.begin) + \", \" + str(self.end) + \", \" + str(self.count) + \")\"\n");
                                                            #line 203 "PrintPython.cpp.template"
                                                                if (resolvesAmbiguity)
                                                                {
                                                            #line 298 "PrintPython.cpp"
  append(L"\n");
  append(L"\n");
  append(L"class AmbiguityEvent(DeferredEvent):\n");
  append(L"\n");
  append(L"  def __init__(self, link, begin, end):\n");
  append(L"    super().__init__(link, -1, begin, end)\n");
  append(L"\n");
  append(L"  def execute(self, eventHandler):\n");
  append(L"    eventHandler.ambiguity(self.begin, self.end)\n");
  append(L"\n");
  append(L"  def toString(self):\n");
  append(L"    return \"ambiguity(\" + str(self.begin) + \", \" + str(self.end) + \")\"\n");
                                                            #line 217 "PrintPython.cpp.template"
                                                                }
                                                              }
                                                            #line 314 "PrintPython.cpp"
  append(L"\n");
  append(L"PARSING = 0\n");
  append(L"ACCEPTED = 1\n");
  append(L"ERROR = 2\n");
  append(L"\n");
  append(L"def parse(self, target, initialState, ");
                                                            #line 224 "PrintPython.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 324 "PrintPython.cpp"
  append(L"eventHandler, ");
                                                            #line 226 "PrintPython.cpp.template"
                                                              }
                                                            #line 328 "PrintPython.cpp"
  append(L"thread):\n");
  append(L"  threads = thread.open(initialState");
                                                            #line 228 "PrintPython.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 334 "PrintPython.cpp"
  append(L", eventHandler");
                                                            #line 230 "PrintPython.cpp.template"
                                                              }
                                                            #line 338 "PrintPython.cpp"
  append(L", target)\n");
  append(L"  while True:\n");
  append(L"    thread = heapq.heappop(threads)[3]\n");
  append(L"    if thread.accepted:");
                                                            #line 234 "PrintPython.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 346 "PrintPython.cpp"
  append(L"\n");
  append(L"      other = None\n");
  append(L"      while len(threads) != 0:\n");
  append(L"        other = heapq.heappop(threads)[3]\n");
  append(L"        if thread.e0 < other.e0:\n");
  append(L"          thread = other\n");
  append(L"          other = None\n");
  append(L"      if other != None:\n");
  append(L"        self.rejectAmbiguity(thread.stack.pos, thread.e0");
                                                            #line 244 "PrintPython.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 359 "PrintPython.cpp"
  append(L", thread.deferredEvent, other.deferredEvent");
                                                            #line 247 "PrintPython.cpp.template"
                                                                }
                                                            #line 363 "PrintPython.cpp"
  append(L")");
                                                            #line 248 "PrintPython.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 369 "PrintPython.cpp"
  append(L"\n");
  append(L"      while len(threads) != 0:\n");
  append(L"        other = heapq.heappop(threads)[3]\n");
  append(L"        thread = other if thread.e0 < other.e0 else self.resolve(thread, other)");
                                                            #line 255 "PrintPython.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                            #line 378 "PrintPython.cpp"
  append(L"\n");
  append(L"      if thread.deferredEvent != None:\n");
  append(L"        thread.deferredEvent.release(eventHandler)\n");
  append(L"        thread.deferredEvent = None");
                                                            #line 261 "PrintPython.cpp.template"
                                                              }
                                                              if (hasCustomCode)
                                                              {
                                                            #line 387 "PrintPython.cpp"
  append(L"\n");
  append(L"      thread.executeDeferredCode()");
                                                            #line 265 "PrintPython.cpp.template"
                                                              }
                                                            #line 392 "PrintPython.cpp"
  append(L"\n");
  append(L"      return thread\n");
  append(L"\n");
                                                            #line 269 "PrintPython.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 399 "PrintPython.cpp"
  append(L"    if len(threads) != 0:\n");
  append(L"      if threads[0][3].equals(thread):\n");
  append(L"        self.rejectAmbiguity(thread.stack.pos, thread.e0");
                                                            #line 273 "PrintPython.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 406 "PrintPython.cpp"
  append(L", thread.deferredEvent, threads[0][3].deferredEvent");
                                                            #line 276 "PrintPython.cpp.template"
                                                                }
                                                            #line 410 "PrintPython.cpp"
  append(L")");
                                                            #line 277 "PrintPython.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 416 "PrintPython.cpp"
  append(L"    while len(threads) != 0 and threads[0][3].equals(thread):\n");
  append(L"      thread = self.resolve(thread, heapq.heappop(threads)[3])");
                                                            #line 282 "PrintPython.cpp.template"
                                                              }
                                                              if (tree || hasCustomCode)
                                                              {
                                                                if (rejectsAmbiguity())
                                                                {
                                                            #line 425 "PrintPython.cpp"
  append(L"\n");
  append(L"    else:");
                                                            #line 288 "PrintPython.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 432 "PrintPython.cpp"
  append(L"\n");
  append(L"    if len(threads) == 0:");
                                                            #line 292 "PrintPython.cpp.template"
                                                                }
                                                                if (tree)
                                                                {
                                                            #line 439 "PrintPython.cpp"
  append(L"\n");
  append(L"      if thread.deferredEvent != None:\n");
  append(L"        thread.deferredEvent.release(eventHandler)\n");
  append(L"        thread.deferredEvent = None");
                                                            #line 298 "PrintPython.cpp.template"
                                                                }
                                                                if (hasCustomCode)
                                                                {
                                                            #line 448 "PrintPython.cpp"
  append(L"\n");
  append(L"      thread.executeDeferredCode()");
                                                            #line 302 "PrintPython.cpp.template"
                                                                }
                                                              }
                                                            #line 454 "PrintPython.cpp"
  append(L"\n");
  append(L"\n");
  append(L"    while True:\n");
  append(L"      status = thread.parse()\n");
  append(L"      if status != ");
                                                            #line 308 "PrintPython.cpp.template"
                                                              print(className.c_str());
                                                            #line 462 "PrintPython.cpp"
  append(L".PARSING:\n");
  append(L"        break\n");
  append(L"      if len(threads) != 0:\n");
  append(L"        break\n");
  append(L"\n");
  append(L"    if status != ");
                                                            #line 314 "PrintPython.cpp.template"
                                                              print(className.c_str());
                                                            #line 471 "PrintPython.cpp"
  append(L".ERROR:\n");
  append(L"      heapq.heappush(threads, (thread.accepted, thread.e0, thread.id, thread))\n");
  append(L"    elif len(threads) == 0:\n");
  append(L"      raise ");
                                                            #line 318 "PrintPython.cpp.template"
                                                              print(className.c_str());
                                                            #line 478 "PrintPython.cpp"
  append(L".ParseException(");
                                                            #line 319 "PrintPython.cpp.template"
                                                              size_t filler = column();
                                                            #line 482 "PrintPython.cpp"
  append(L"thread.b1,");
                                                            #line 320 "PrintPython.cpp.template"
                                                              print(L"\n");
                                                              filler -= column();
                                                              print(filler, L" ");
                                                            #line 488 "PrintPython.cpp"
  append(L"thread.e1,");
                                                            #line 323 "PrintPython.cpp.template"
                                                              print(L"\n");
                                                              print(filler, L" ");
                                                              print(className.c_str());
                                                            #line 494 "PrintPython.cpp"
  append(L".TOKENSET[thread.state] + 1,");
                                                            #line 326 "PrintPython.cpp.template"
                                                              print(L"\n");
                                                              print(filler, L" ");
                                                            #line 499 "PrintPython.cpp"
  append(L"thread.l1,");
                                                            #line 328 "PrintPython.cpp.template"
                                                              print(L"\n");
                                                              print(filler, L" ");
                                                            #line 504 "PrintPython.cpp"
  append(L"-1)\n");
                                                            #line 331 "PrintPython.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 509 "PrintPython.cpp"
  append(L"\n");
  append(L"def rejectAmbiguity(self, begin, end");
                                                            #line 334 "PrintPython.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 515 "PrintPython.cpp"
  append(L", first, second");
                                                            #line 336 "PrintPython.cpp.template"
                                                                }
                                                            #line 519 "PrintPython.cpp"
  append(L"):");
                                                            #line 337 "PrintPython.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 524 "PrintPython.cpp"
  append(L"\n");
  append(L"  treeBuilder = ");
                                                            #line 340 "PrintPython.cpp.template"
                                                                  print(className.c_str());
                                                            #line 529 "PrintPython.cpp"
  append(L".ParseTreeBuilder()\n");
  append(L"  treeBuilder.reset(self.input)\n");
  append(L"  second.show(treeBuilder)\n");
  append(L"  treeBuilder.nonterminal(");
                                                            #line 344 "PrintPython.cpp.template"
                                                                  print(format.toString<wchar_t>(Grammar::syntheticNonterminalCode(0)));
                                                            #line 536 "PrintPython.cpp"
  append(L", treeBuilder.stack[0].begin, treeBuilder.stack[len(treeBuilder.stack) - 1].end, len(treeBuilder.stack))\n");
  append(L"  secondTree = treeBuilder.pop(1)[0]\n");
  append(L"  first.show(treeBuilder)\n");
  append(L"  treeBuilder.nonterminal(");
                                                            #line 348 "PrintPython.cpp.template"
                                                                  print(format.toString<wchar_t>(Grammar::syntheticNonterminalCode(0)));
                                                            #line 543 "PrintPython.cpp"
  append(L", treeBuilder.stack[0].begin, treeBuilder.stack[len(treeBuilder.stack) - 1].end, len(treeBuilder.stack))\n");
  append(L"  treeBuilder.push(secondTree)\n");
  append(L"  treeBuilder.nonterminal(");
                                                            #line 351 "PrintPython.cpp.template"
                                                                  print(format.toString<wchar_t>(Grammar::syntheticNonterminalCode(1)));
                                                            #line 549 "PrintPython.cpp"
  append(L", treeBuilder.stack[0].begin, treeBuilder.stack[len(treeBuilder.stack) - 1].end, 2)");
                                                            #line 353 "PrintPython.cpp.template"
                                                                }
                                                            #line 553 "PrintPython.cpp"
  append(L"\n");
  append(L"  raise ");
                                                            #line 355 "PrintPython.cpp.template"
                                                                print(className.c_str());
                                                            #line 558 "PrintPython.cpp"
  append(L".ParseException(begin, end, 1, -1, -1, True");
                                                            #line 356 "PrintPython.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 563 "PrintPython.cpp"
  append(L", treeBuilder");
                                                            #line 358 "PrintPython.cpp.template"
                                                                }
                                                            #line 567 "PrintPython.cpp"
  append(L")");
                                                            #line 359 "PrintPython.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 573 "PrintPython.cpp"
  append(L"\n");
  append(L"def resolve(self, thread, other):");
                                                            #line 363 "PrintPython.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 579 "PrintPython.cpp"
  append(L"\n");
  append(L"  a = thread.stack\n");
  append(L"  b = other.stack\n");
  append(L"  begin = a.pos\n");
  append(L"  while a is not b and a is not None and b is not None:\n");
  append(L"    begin = a.pos\n");
  append(L"    a = a.link\n");
  append(L"    b = b.link");
                                                            #line 372 "PrintPython.cpp.template"
                                                                }
                                                            #line 590 "PrintPython.cpp"
  append(L"\n");
                                                            #line 374 "PrintPython.cpp.template"
                                                                if (shiftAmbiguity)
                                                                {
                                                            #line 595 "PrintPython.cpp"
  append(L"\n");
  append(L"  ea = thread.deferredEvent\n");
  append(L"  eb = other.deferredEvent\n");
  append(L"  ua = None\n");
  append(L"  ub = None\n");
  append(L"  while ea is not eb:\n");
  append(L"    if (0 if ea is None else ea.depth) >= (0 if eb is None else eb.depth):\n");
  append(L"      ua = ea\n");
  append(L"      ea = ea.link\n");
  append(L"    else:\n");
  append(L"      ub = eb\n");
  append(L"      eb = eb.link\n");
  append(L"  sa = ua is not None and ua.isTerminal()\n");
  append(L"  sb = ub is not None and ub.isTerminal()\n");
  append(L"  if sa != sb:\n");
  append(L"    if sb:\n");
  append(L"      thread = other\n");
  append(L"  elif other.eventCount < thread.eventCount:\n");
  append(L"    thread = other");
                                                            #line 394 "PrintPython.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 619 "PrintPython.cpp"
  append(L"\n");
  append(L"  if other.eventCount < thread.eventCount:\n");
  append(L"    thread = other");
                                                            #line 399 "PrintPython.cpp.template"
                                                                }
                                                                if (tree)
                                                                {
                                                            #line 627 "PrintPython.cpp"
  append(L"\n");
  append(L"  thread.addAmbiguity(begin, thread.e0)");
                                                            #line 403 "PrintPython.cpp.template"
                                                                }
                                                            #line 632 "PrintPython.cpp"
  append(L"\n");
  append(L"  return thread");
                                                            #line 405 "PrintPython.cpp.template"
                                                              }
                                                            }

                                                            void PrintPython::openThread()
                                                            {
                                                            #line 641 "PrintPython.cpp"
  append(L"\n");
  append(L"class ParsingThread:\n");
  append(L"\n");
  append(L"  def open(self, initialState");
                                                            #line 413 "PrintPython.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 649 "PrintPython.cpp"
  append(L", eh");
                                                            #line 415 "PrintPython.cpp.template"
                                                              }
                                                            #line 653 "PrintPython.cpp"
  append(L", t):\n");
  append(L"    self.accepted = False\n");
  append(L"    self.target = t");
                                                            #line 418 "PrintPython.cpp.template"
                                                              if (resolvesAmbiguity)
                                                              {
                                                            #line 660 "PrintPython.cpp"
  append(L"\n");
  append(L"    self.eventCount = 0");
                                                            #line 421 "PrintPython.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                            #line 667 "PrintPython.cpp"
  append(L"\n");
  append(L"    self.eventHandler = eh\n");
  append(L"    if self.eventHandler != None:\n");
  append(L"      self.eventHandler.reset(self.parser.input)\n");
  append(L"    self.deferredEvent = None");
                                                            #line 428 "PrintPython.cpp.template"
                                                              }
                                                              if (hasCustomCode && useGlr)
                                                              {
                                                            #line 677 "PrintPython.cpp"
  append(L"\n");
  append(L"    self.deferredCode = None");
                                                            #line 432 "PrintPython.cpp.template"
                                                              }
                                                            #line 682 "PrintPython.cpp"
  append(L"\n");
  append(L"    self.stack = ");
                                                            #line 434 "PrintPython.cpp.template"
                                                              print(className.c_str());
                                                            #line 687 "PrintPython.cpp"
  append(L".StackNode(-1, ");
                                                            #line 435 "PrintPython.cpp.template"
                                                              if (grammar->states->hasLookback)
                                                              {
                                                            #line 692 "PrintPython.cpp"
  append(L"0, ");
                                                            #line 437 "PrintPython.cpp.template"
                                                              }
                                                            #line 696 "PrintPython.cpp"
  append(L"self.e0, None)\n");
  append(L"    self.state = initialState\n");
  append(L"    self.action = self.predict(initialState)");
                                                            #line 440 "PrintPython.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 703 "PrintPython.cpp"
  append(L"\n");
  append(L"    self.bw = self.e0\n");
  append(L"    self.bs = self.e0\n");
  append(L"    self.es = self.e0");
                                                            #line 445 "PrintPython.cpp.template"
                                                              }
                                                            #line 710 "PrintPython.cpp"
  append(L"\n");
  append(L"    self.threads = [(False, self.e0, self.id, self)]\n");
  append(L"    return self.threads\n");
  append(L"\n");
  append(L"  def copy(self, other, action):\n");
  append(L"    self.action = action\n");
  append(L"    self.accepted = other.accepted\n");
  append(L"    self.target = other.target\n");
  append(L"    self.parser = other.parser");
                                                            #line 454 "PrintPython.cpp.template"
                                                              if (resolvesAmbiguity)
                                                              {
                                                            #line 723 "PrintPython.cpp"
  append(L"\n");
  append(L"    self.eventCount = other.eventCount");
                                                            #line 457 "PrintPython.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                            #line 730 "PrintPython.cpp"
  append(L"\n");
  append(L"    self.bs = other.bs\n");
  append(L"    self.es = other.es\n");
  append(L"    self.bw = other.bw\n");
  append(L"    self.eventHandler = other.eventHandler\n");
  append(L"    self.deferredEvent = other.deferredEvent");
                                                            #line 465 "PrintPython.cpp.template"
                                                              }
                                                              if (hasCustomCode)
                                                              {
                                                            #line 741 "PrintPython.cpp"
  append(L"\n");
  append(L"    self.deferredCode = other.deferredCode");
                                                            #line 469 "PrintPython.cpp.template"
                                                              }
                                                            #line 746 "PrintPython.cpp"
  append(L"\n");
  append(L"    self.parser.maxId += 1\n");
  append(L"    self.id = self.parser.maxId\n");
  append(L"    self.threads = other.threads\n");
  append(L"    self.state = other.state\n");
  append(L"    self.stack = other.stack\n");
  append(L"    self.b0 = other.b0\n");
  append(L"    self.e0 = other.e0");
                                                            #line 477 "PrintPython.cpp.template"
                                                              for (size_t i = 1; i <= grammar->k; ++i)
                                                              {
                                                                const wchar_t *iString = format.toString<wchar_t>(i);
                                                            #line 759 "PrintPython.cpp"
  append(L"\n");
  append(L"    self.l");
                                                            #line 481 "PrintPython.cpp.template"
                                                                print(iString);
                                                            #line 764 "PrintPython.cpp"
  append(L" = other.l");
                                                            #line 482 "PrintPython.cpp.template"
                                                                print(iString);
                                                            #line 768 "PrintPython.cpp"
  append(L"\n");
  append(L"    self.b");
                                                            #line 484 "PrintPython.cpp.template"
                                                                print(iString);
                                                            #line 773 "PrintPython.cpp"
  append(L" = other.b");
                                                            #line 485 "PrintPython.cpp.template"
                                                                print(iString);
                                                            #line 777 "PrintPython.cpp"
  append(L"\n");
  append(L"    self.e");
                                                            #line 487 "PrintPython.cpp.template"
                                                                print(iString);
                                                            #line 782 "PrintPython.cpp"
  append(L" = other.e");
                                                            #line 488 "PrintPython.cpp.template"
                                                                print(iString);
                                                              }
                                                            #line 787 "PrintPython.cpp"
  append(L"\n");
  append(L"    self.end = other.end\n");
  append(L"    return self\n");
                                                            #line 493 "PrintPython.cpp.template"
                                                              if (resolvesAmbiguity && tree)
                                                              {
                                                            #line 794 "PrintPython.cpp"
  append(L"\n");
  append(L"  def addAmbiguity(self, begin, end):\n");
  append(L"    if self.eventHandler != None:\n");
  append(L"      self.deferredEvent = ");
                                                            #line 498 "PrintPython.cpp.template"
                                                                print(className.c_str());
                                                            #line 801 "PrintPython.cpp"
  append(L".AmbiguityEvent(self.deferredEvent, begin, end)\n");
                                                            #line 500 "PrintPython.cpp.template"
                                                              }
                                                            #line 805 "PrintPython.cpp"
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
                                                            #line 519 "PrintPython.cpp.template"
                                                              increaseIndent();
                                                              beginPublic();
                                                            }

                                                            void PrintPython::printFlush(int i, bool withinThread)
                                                            {
                                                              if (trace)
                                                              {
                                                                increaseIndent(i);
                                                            #line 835 "PrintPython.cpp"
  append(L"\n");
                                                            #line 529 "PrintPython.cpp.template"
                                                                print(className.c_str());
                                                            #line 839 "PrintPython.cpp"
  append(L".flushTrace()");
                                                            #line 530 "PrintPython.cpp.template"
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
                                                            #line 853 "PrintPython.cpp"
  append(L"\n");
  append(L"def ");
                                                            #line 542 "PrintPython.cpp.template"
                                                              print(name);
                                                            #line 858 "PrintPython.cpp"
  append(L"(self");
                                                            #line 543 "PrintPython.cpp.template"
                                                              if (*args != 0)
                                                              {
                                                            #line 863 "PrintPython.cpp"
  append(L", ");
                                                            #line 545 "PrintPython.cpp.template"
                                                                printArgNamesOnly(args);
                                                              }
                                                            #line 868 "PrintPython.cpp"
  append(L"):");
                                                            #line 547 "PrintPython.cpp.template"
                                                            }

                                                            void PrintPython::privateVars()
                                                            {
                                                              if (trace)
                                                              {
                                                                increaseIndent();
                                                            #line 878 "PrintPython.cpp"
  append(L"\n");
  append(L"def lookaheadString(self):\n");
  append(L"  result = \"\"");
                                                            #line 556 "PrintPython.cpp.template"
                                                                for (size_t i = 1; i <= grammar->k; ++i)
                                                                {
                                                            #line 885 "PrintPython.cpp"
  append(L"\n");
  append(L"  if self.l");
                                                            #line 559 "PrintPython.cpp.template"
                                                                  print(format.toString<wchar_t>(i));
                                                            #line 890 "PrintPython.cpp"
  append(L" > 0:\n");
  append(L"    result += ");
                                                            #line 561 "PrintPython.cpp.template"
                                                                  if (i != 1)
                                                                  {
                                                            #line 896 "PrintPython.cpp"
  append(L"\" \" + ");
                                                            #line 563 "PrintPython.cpp.template"
                                                                  }
                                                                  print(className.c_str());
                                                            #line 901 "PrintPython.cpp"
  append(L".TOKEN[self.l");
                                                            #line 565 "PrintPython.cpp.template"
                                                                  print(format.toString<wchar_t>(i));
                                                            #line 905 "PrintPython.cpp"
  append(L"]");
                                                            #line 566 "PrintPython.cpp.template"
                                                                  increaseIndent();
                                                                }
                                                                for (size_t i = 1; i <= grammar->k; ++i)
                                                                {
                                                                  decreaseIndent();
                                                                }
                                                            #line 914 "PrintPython.cpp"
  append(L"\n");
  append(L"  return result\n");
                                                            #line 574 "PrintPython.cpp.template"
                                                                decreaseIndent();
                                                              }
                                                              if (memoization)
                                                              {
                                                                increaseIndent();
                                                                int bits = Math::bits(grammar->conflictCount);
                                                            #line 924 "PrintPython.cpp"
  append(L"\n");
  append(L"def memoize(self, i, e, v):\n");
  append(L"  self.memo[(e << ");
                                                            #line 582 "PrintPython.cpp.template"
                                                                print(format.toString<wchar_t>(bits));
                                                            #line 930 "PrintPython.cpp"
  append(L") + i] = v\n");
  append(L"\n");
  append(L"def memoized(self, i, e):\n");
  append(L"  return self.memo.get((e << ");
                                                            #line 586 "PrintPython.cpp.template"
                                                                print(format.toString<wchar_t>(bits));
                                                            #line 937 "PrintPython.cpp"
  append(L") + i, 0)\n");
                                                            #line 588 "PrintPython.cpp.template"
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
                                                            #line 952 "PrintPython.cpp"
  append(L"\n");
  append(L"class ContentCounter:\n");
  append(L"  def getLength(self):\n");
  append(L"    return self.length\n");
  append(L"\n");
  append(L"  def reset(self, _):\n");
  append(L"    self.length = 0\n");
  append(L"\n");
  append(L"  def startNonterminal(self, id, begin):\n");
  append(L"    pass\n");
  append(L"\n");
  append(L"  def endNonterminal(self, id, end):\n");
  append(L"    pass\n");
  append(L"\n");
  append(L"  def terminal(self, id, begin, end):\n");
  append(L"    self.length += end - begin\n");
  append(L"\n");
  append(L"  def whitespace(self, begin, end):\n");
  append(L"    self.length += end - begin\n");
                                                            #line 619 "PrintPython.cpp.template"
                                                              }
                                                            #line 974 "PrintPython.cpp"
  append(L"\n");
  append(L"class ParseJob:\n");
  append(L"\n");
  append(L"  def __init__(self, name, parser");
                                                            #line 623 "PrintPython.cpp.template"
                                                              if (tree)
                                                              {
                                                                if (isLrParser)
                                                                {
                                                            #line 984 "PrintPython.cpp"
  append(L", parseTreeBuilder");
                                                            #line 627 "PrintPython.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 990 "PrintPython.cpp"
  append(L", contentCounter");
                                                            #line 630 "PrintPython.cpp.template"
                                                                }
                                                              }
                                                            #line 995 "PrintPython.cpp"
  append(L"):\n");
  append(L"    self.name = name\n");
  append(L"    self.parser = parser");
                                                            #line 634 "PrintPython.cpp.template"
                                                              if (tree)
                                                              {
                                                                if (isLrParser)
                                                                {
                                                            #line 1004 "PrintPython.cpp"
  append(L"\n");
  append(L"    self.parseTreeBuilder = parseTreeBuilder\n");
  append(L"    self.contentCounter = ContentCounter()");
                                                            #line 640 "PrintPython.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1012 "PrintPython.cpp"
  append(L"\n");
  append(L"    self.contentCounter = contentCounter");
                                                            #line 644 "PrintPython.cpp.template"
                                                                }
                                                              }
                                                            #line 1018 "PrintPython.cpp"
  append(L"\n");
  append(L"\n");
  append(L"def main(args):\n");
  append(L"  if len(args) < 2:\n");
  append(L"    sys.stderr.write(\"Usage: python ");
                                                            #line 650 "PrintPython.cpp.template"
                                                              print(className.c_str());
                                                            #line 1026 "PrintPython.cpp"
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
                                                            #line 691 "PrintPython.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 1071 "PrintPython.cpp"
  append(L"\n");
  append(L"          contentCounter = ContentCounter()");
                                                            #line 694 "PrintPython.cpp.template"
                                                                if (isLrParser)
                                                                {
                                                            #line 1077 "PrintPython.cpp"
  append(L"\n");
  append(L"          parseTreeBuilder = ");
                                                            #line 697 "PrintPython.cpp.template"
                                                                  print(className.c_str());
                                                            #line 1082 "PrintPython.cpp"
  append(L".ParseTreeBuilder()");
                                                            #line 698 "PrintPython.cpp.template"
                                                                }
                                                              }
                                                            #line 1087 "PrintPython.cpp"
  append(L"\n");
  append(L"          content = read(path)\n");
  append(L"          parsers.append(ParseJob(path, ");
                                                            #line 702 "PrintPython.cpp.template"
                                                              print(className.c_str());
                                                            #line 1093 "PrintPython.cpp"
  append(L"(content");
                                                            #line 703 "PrintPython.cpp.template"
                                                              if (tree)
                                                              {
                                                                if (isLrParser)
                                                                {
                                                            #line 1100 "PrintPython.cpp"
  append(L", parseTreeBuilder");
                                                            #line 707 "PrintPython.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1106 "PrintPython.cpp"
  append(L", contentCounter");
                                                            #line 710 "PrintPython.cpp.template"
                                                                }
                                                              }
                                                            #line 1111 "PrintPython.cpp"
  append(L")");
                                                            #line 712 "PrintPython.cpp.template"
                                                              if (tree)
                                                              {
                                                                if (isLrParser)
                                                                {
                                                            #line 1118 "PrintPython.cpp"
  append(L", parseTreeBuilder");
                                                            #line 716 "PrintPython.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1124 "PrintPython.cpp"
  append(L", contentCounter");
                                                            #line 719 "PrintPython.cpp.template"
                                                                }
                                                              }
                                                            #line 1129 "PrintPython.cpp"
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
                                                            #line 747 "PrintPython.cpp.template"
                                                              if (useGlr)
                                                              {
                                                            #line 1160 "PrintPython.cpp"
  append(L".thread");
                                                            #line 749 "PrintPython.cpp.template"
                                                              }
                                                            #line 1164 "PrintPython.cpp"
  append(L".reset(0, 0, 0)\n");
  append(L"            try:\n");
  append(L"              pe = job.parser.parse_");
                                                            #line 752 "PrintPython.cpp.template"
                                                              print(Format::acceptableName<WString>(grammar->startSymbol()->name).c_str());
                                                            #line 1170 "PrintPython.cpp"
  append(L"()\n");
  append(L"            except ");
                                                            #line 754 "PrintPython.cpp.template"
                                                              print(className.c_str());
                                                            #line 1175 "PrintPython.cpp"
  append(L".ParseException as pe:\n");
  append(L"              errorCount += 1\n");
  append(L"              if quiet:\n");
  append(L"                print(\"parsing \" + job.name)\n");
  append(L"              print(\": error: \" + job.parser.GetErrorMessage(pe))\n");
  append(L"              job.parser = None\n");
  append(L"            if not quiet:\n");
  append(L"              print()");
                                                            #line 762 "PrintPython.cpp.template"
                                                              if (tree)
                                                              {
                                                                if (isLrParser)
                                                                {
                                                            #line 1189 "PrintPython.cpp"
  append(L"\n");
  append(L"            job.parseTreeBuilder.serialize(job.contentCounter)");
                                                            #line 767 "PrintPython.cpp.template"
                                                                }
                                                            #line 1194 "PrintPython.cpp"
  append(L"\n");
  append(L"            if job.contentCounter.getLength() != len(job.parser.input):\n");
  append(L"              raise Exception(\"content counter saw \" + str(job.contentCounter.getLength()) + \", but input length is \" + str(len(job.parser.input)))");
                                                            #line 771 "PrintPython.cpp.template"
                                                              }
                                                            #line 1200 "PrintPython.cpp"
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
                                                            #line 793 "PrintPython.cpp.template"
                                                            }

                                                            void PrintPython::printReadMethod()
                                                            {
                                                            #line 1227 "PrintPython.cpp"
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
                                                            #line 807 "PrintPython.cpp.template"
                                                            }

                                                            void PrintPython::printInterface()
                                                            {
                                                              if (! packageName.empty())
                                                              {
                                                            #line 1245 "PrintPython.cpp"
  append(L"\n");
  append(L"package ");
                                                            #line 814 "PrintPython.cpp.template"
                                                                print(packageName.c_str());
                                                            #line 1250 "PrintPython.cpp"
  append(L";\n");
                                                            #line 816 "PrintPython.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                                if (main || useGlr)
                                                                {
                                                            #line 1258 "PrintPython.cpp"
  append(L"\n");
  append(L"import java.io.IOException;\n");
  append(L"import java.io.Writer;\n");
                                                            #line 824 "PrintPython.cpp.template"
                                                                }
                                                            #line 1264 "PrintPython.cpp"
  append(L"\n");
  append(L"import java.util.Arrays;");
                                                            #line 826 "PrintPython.cpp.template"
                                                              }
                                                            #line 1269 "PrintPython.cpp"
  append(L"\n");
  append(L"public interface ");
                                                            #line 828 "PrintPython.cpp.template"
                                                              print(className.c_str());
                                                            #line 1274 "PrintPython.cpp"
  append(L"\n");
  append(L"{\n");
  append(L"  public void initialize(CharSequence input");
                                                            #line 831 "PrintPython.cpp.template"
                                                              if (noLexer)
                                                              {
                                                            #line 1281 "PrintPython.cpp"
  append(L", Lexer l");
                                                            #line 833 "PrintPython.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                            #line 1287 "PrintPython.cpp"
  append(L", ");
                                                            #line 836 "PrintPython.cpp.template"
                                                                if (isLrParser)
                                                                {
                                                            #line 1292 "PrintPython.cpp"
  append(L"BottomUp");
                                                            #line 838 "PrintPython.cpp.template"
                                                                }
                                                            #line 1296 "PrintPython.cpp"
  append(L"EventHandler eh");
                                                            #line 840 "PrintPython.cpp.template"
                                                              }
                                                            #line 1300 "PrintPython.cpp"
  append(L");\n");
  append(L"  public void parse();\n");
  append(L"  public void Reset();\n");
  append(L"  public String getErrorMessage(ParseException e);\n");
                                                            #line 845 "PrintPython.cpp.template"
                                                              printParseException();
                                                              printEventHandlerImplementation();
                                                            #line 1308 "PrintPython.cpp"
  append(L"}\n");
                                                            #line 848 "PrintPython.cpp.template"
                                                            }

                                                            void PrintPython::printParseException()
                                                            {
                                                            #line 1315 "PrintPython.cpp"
  append(L"\n");
  append(L"class ParseException(Exception):\n");
                                                            #line 854 "PrintPython.cpp.template"
                                                              increaseIndent();
                                                            #line 1320 "PrintPython.cpp"
  append(L"\n");
  append(L"def __init__(self, b, e, s, o, x");
                                                            #line 856 "PrintPython.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 1326 "PrintPython.cpp"
  append(L", ambiguousInput = False");
                                                            #line 858 "PrintPython.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 1331 "PrintPython.cpp"
  append(L", ambiguityDescriptor = None");
                                                            #line 860 "PrintPython.cpp.template"
                                                                }
                                                              }
                                                            #line 1336 "PrintPython.cpp"
  append(L"):\n");
  append(L"  self.begin = b\n");
  append(L"  self.end = e\n");
  append(L"  self.state = s\n");
  append(L"  self.offending = o\n");
  append(L"  self.expected = x");
                                                            #line 867 "PrintPython.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 1346 "PrintPython.cpp"
  append(L"\n");
  append(L"  self.ambiguousInput = ambiguousInput");
                                                            #line 870 "PrintPython.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 1352 "PrintPython.cpp"
  append(L"\n");
  append(L"  self.ambiguityDescriptor = ambiguityDescriptor");
                                                            #line 873 "PrintPython.cpp.template"
                                                                }
                                                              }
                                                            #line 1358 "PrintPython.cpp"
  append(L"\n");
  append(L"\n");
  append(L"def error(self):\n");
  append(L"  if ");
                                                            #line 878 "PrintPython.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 1366 "PrintPython.cpp"
  append(L"self.ambiguousInput:\n");
  append(L"    return \"ambiguous input\"\n");
  append(L"  elif ");
                                                            #line 882 "PrintPython.cpp.template"
                                                              }
                                                            #line 1372 "PrintPython.cpp"
  append(L"self.offending < 0:\n");
  append(L"    return \"lexical analysis failed\"\n");
  append(L"  else:\n");
  append(L"    return \"syntax error\"\n");
                                                            #line 887 "PrintPython.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 1380 "PrintPython.cpp"
  append(L"\n");
  append(L"def serialize(self, eventHandler):");
                                                            #line 890 "PrintPython.cpp.template"
                                                                if (rejectsAmbiguity())
                                                                {
                                                            #line 1386 "PrintPython.cpp"
  append(L"\n");
  append(L"  self.ambiguityDescriptor.serialize(eventHandler)");
                                                            #line 893 "PrintPython.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1393 "PrintPython.cpp"
  append(L"\n");
  append(L"  pass");
                                                            #line 897 "PrintPython.cpp.template"
                                                                }
                                                            #line 1398 "PrintPython.cpp"
  append(L"\n");
                                                            #line 899 "PrintPython.cpp.template"
                                                              }
                                                            #line 1402 "PrintPython.cpp"
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
                                                            #line 917 "PrintPython.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 1424 "PrintPython.cpp"
  append(L"self.ambiguousInput");
                                                            #line 919 "PrintPython.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 1430 "PrintPython.cpp"
  append(L"False");
                                                            #line 922 "PrintPython.cpp.template"
                                                              }
                                                              decreaseIndent();
                                                            #line 1435 "PrintPython.cpp"
  append(L"\n");
                                                            #line 925 "PrintPython.cpp.template"
                                                              if (noLexer)
                                                              {
                                                            #line 1440 "PrintPython.cpp"
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
                                                            #line 940 "PrintPython.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                            #line 1458 "PrintPython.cpp"
  append(L"\n");
  append(L"class TopDownTreeBuilder:\n");
                                                            #line 945 "PrintPython.cpp.template"
                                                                increaseIndent();
                                                            #line 1463 "PrintPython.cpp"
  append(L"\n");
  append(L"def reset(self, inputString):\n");
  append(L"  self.input = inputString\n");
  append(L"  self.stack = []\n");
  append(L"  self.top = -1\n");
  append(L"\n");
  append(L"def startNonterminal(self, id, begin):\n");
  append(L"  nonterminal = ");
                                                            #line 953 "PrintPython.cpp.template"
                                                                print(className.c_str());
                                                            #line 1474 "PrintPython.cpp"
  append(L".Nonterminal(id, begin, begin)\n");
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
  append(L"def terminal(self, id, begin, end):\n");
  append(L"  self.addChild(");
                                                            #line 966 "PrintPython.cpp.template"
                                                                print(className.c_str());
                                                            #line 1490 "PrintPython.cpp"
  append(L".Terminal(id, begin, end))\n");
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
                                                            #line 979 "PrintPython.cpp.template"
                                                                decreaseIndent();
                                                            #line 1505 "PrintPython.cpp"
  append(L"\n");
  append(L"class Symbol:\n");
                                                            #line 982 "PrintPython.cpp.template"
                                                                increaseIndent();
                                                            #line 1510 "PrintPython.cpp"
  append(L"\n");
  append(L"def __init__(self, id, begin, end):\n");
  append(L"  self.id = id\n");
  append(L"  self.begin = begin\n");
  append(L"  self.end = end\n");
  append(L"\n");
  append(L"def getId(self):\n");
  append(L"  return self.id\n");
  append(L"\n");
  append(L"def getBegin(self):\n");
  append(L"  return self.begin\n");
  append(L"\n");
  append(L"def getEnd(self):\n");
  append(L"  return self.end\n");
                                                            #line 997 "PrintPython.cpp.template"
                                                                decreaseIndent();
                                                            #line 1527 "PrintPython.cpp"
  append(L"\n");
  append(L"class Nonterminal(Symbol):\n");
                                                            #line 1000 "PrintPython.cpp.template"
                                                                increaseIndent();
                                                            #line 1532 "PrintPython.cpp"
  append(L"\n");
  append(L"def __init__(self, id, begin, end, children):\n");
  append(L"  super().__init__(id, begin, end)\n");
  append(L"  self.children = children\n");
  append(L"\n");
  append(L"def getName(self):\n");
  append(L"  return ");
                                                            #line 1007 "PrintPython.cpp.template"
                                                                printSyntheticNamePrefix(false, L"self.id");
                                                                print(className.c_str());
                                                            #line 1543 "PrintPython.cpp"
  append(L".NONTERMINAL[self.id]");
                                                            #line 1009 "PrintPython.cpp.template"
                                                                printSyntheticNameSuffix(false, L"self.id");
                                                            #line 1547 "PrintPython.cpp"
  append(L"\n");
  append(L"\n");
  append(L"def addChild(self, s):\n");
  append(L"  self.children = self.children.append(s)\n");
  append(L"\n");
  append(L"def send(self, e):\n");
  append(L"  e.startNonterminal(self.id, self.getBegin())\n");
  append(L"  pos = self.getBegin()\n");
  append(L"  for c in self.children:\n");
  append(L"    if pos < c.getBegin():\n");
  append(L"      e.whitespace(pos, c.getBegin())\n");
  append(L"    c.send(e)\n");
  append(L"    pos = c.getEnd()\n");
  append(L"  if pos < self.getEnd():\n");
  append(L"    e.whitespace(pos, self.getEnd())\n");
  append(L"  e.endNonterminal(self.id, self.getEnd())\n");
                                                            #line 1026 "PrintPython.cpp.template"
                                                                decreaseIndent();
                                                            #line 1566 "PrintPython.cpp"
  append(L"\n");
  append(L"class Terminal(Symbol):\n");
                                                            #line 1029 "PrintPython.cpp.template"
                                                                increaseIndent();
                                                            #line 1571 "PrintPython.cpp"
  append(L"\n");
  append(L"def __init__(self, id, begin, end):\n");
  append(L"  super().__init__(id, begin, end)\n");
  append(L"\n");
  append(L"def getName(self):\n");
  append(L"  return ");
                                                            #line 1035 "PrintPython.cpp.template"
                                                                print(className.c_str());
                                                            #line 1580 "PrintPython.cpp"
  append(L".TOKEN[self.id]\n");
  append(L"\n");
  append(L"def send(self, e):\n");
  append(L"  e.terminal(self.id, self.getBegin(), self.getEnd())\n");
                                                            #line 1040 "PrintPython.cpp.template"
                                                                decreaseIndent();
                                                              }
                                                            }

                                                            void PrintPython::printEventHandlerImplementation()
                                                            {
                                                              if (tree)
                                                              {
                                                                if (main || useGlr)
                                                                {
                                                            #line 1596 "PrintPython.cpp"
  append(L"\n");
  append(L"class XmlSerializer:\n");
                                                            #line 1052 "PrintPython.cpp.template"
                                                                  increaseIndent();
                                                            #line 1601 "PrintPython.cpp"
  append(L"\n");
  append(L"def reset(self, inputString):\n");
  append(L"  sys.stdout.reconfigure(encoding=\"utf-8\")\n");
  append(L"  print(\"<?xml version=\\\"1.0\\\" encoding=\\\"UTF-8\\\"?>\", end=\"\")\n");
  append(L"  self.input = inputString\n");
  append(L"  self.delayedTag = None\n");
  append(L"  self.hasChildElement = False\n");
  append(L"  self.depth = 0\n");
  append(L"\n");
  append(L"def startNonterminal(self, id, _):\n");
  append(L"  self.startElement(");
                                                            #line 1063 "PrintPython.cpp.template"
                                                                  print(className.c_str());
                                                            #line 1615 "PrintPython.cpp"
  append(L".getNonterminalName(id))\n");
  append(L"\n");
  append(L"def startElement(self, tag):\n");
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
  append(L"def endNonterminal(self, id, _):\n");
  append(L"  self.endElement(");
                                                            #line 1080 "PrintPython.cpp.template"
                                                                  print(className.c_str());
                                                            #line 1635 "PrintPython.cpp"
  append(L".getNonterminalName(id))\n");
  append(L"\n");
  append(L"def endElement(self, tag):\n");
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
  append(L"def terminal(self, id, b, e):\n");
  append(L"  tag = ");
                                                            #line 1125 "PrintPython.cpp.template"
                                                                  print(className.c_str());
                                                            #line 1683 "PrintPython.cpp"
  append(L".getTerminalName(id)\n");
  append(L"  if tag[0] == '\\'':\n");
  append(L"    tag = \"TOKEN\"\n");
  append(L"  self.startElement(tag)\n");
  append(L"  self.characters(b, e)\n");
  append(L"  self.endElement(tag)\n");
                                                            #line 1132 "PrintPython.cpp.template"
                                                                  decreaseIndent();
                                                                }
                                                                if (isLrParser)
                                                                {
                                                            #line 1695 "PrintPython.cpp"
  append(L"\n");
  append(L"class ParseTreeBuilder:\n");
                                                            #line 1138 "PrintPython.cpp.template"
                                                                  increaseIndent();
                                                            #line 1700 "PrintPython.cpp"
  append(L"\n");
  append(L"def reset(self, inputString):\n");
  append(L"  self.input = inputString\n");
  append(L"  self.stack = []\n");
  append(L"\n");
  append(L"def nonterminal(self, id, begin, end, count):");
                                                            #line 1144 "PrintPython.cpp.template"
                                                                  if (rejectsAmbiguity())
                                                                  {
                                                            #line 1710 "PrintPython.cpp"
  append(L"\n");
  append(L"  if count > len(self.stack):\n");
  append(L"    content = self.pop(len(self.stack))\n");
  append(L"    e = end\n");
  append(L"    if len(content) != 0:\n");
  append(L"      e = content[0].getBegin()\n");
  append(L"    self.nonterminal(");
                                                            #line 1152 "PrintPython.cpp.template"
                                                                    print(format.toString<wchar_t>(Grammar::syntheticNonterminalCode(2)));
                                                            #line 1720 "PrintPython.cpp"
  append(L", begin, e, 0)\n");
  append(L"    for symbol in content:\n");
  append(L"      self.push(symbol)\n");
  append(L"    count = len(self.stack)");
                                                            #line 1156 "PrintPython.cpp.template"
                                                                  }
                                                            #line 1727 "PrintPython.cpp"
  append(L"\n");
  append(L"  self.push(");
                                                            #line 1158 "PrintPython.cpp.template"
                                                                  print(className.c_str());
                                                            #line 1732 "PrintPython.cpp"
  append(L".Nonterminal(id, begin, end, self.pop(count)))\n");
  append(L"\n");
  append(L"def terminal(self, id, begin, end):\n");
  append(L"  self.push(");
                                                            #line 1162 "PrintPython.cpp.template"
                                                                  print(className.c_str());
                                                            #line 1739 "PrintPython.cpp"
  append(L".Terminal(id, begin, end))\n");
                                                            #line 1164 "PrintPython.cpp.template"
                                                                  if (resolvesAmbiguity)
                                                                  {
                                                            #line 1744 "PrintPython.cpp"
  append(L"\n");
  append(L"\n");
  append(L"def ambiguity(self, begin, end):\n");
  append(L"  pass\n");
                                                            #line 1170 "PrintPython.cpp.template"
                                                                  }
                                                            #line 1751 "PrintPython.cpp"
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
                                                            #line 1187 "PrintPython.cpp.template"
                                                                  decreaseIndent();
                                                                }
                                                              }
                                                            }

                                                            void PrintPython::printTokenVars()
                                                            {
                                                            #line 1776 "PrintPython.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 1195 "PrintPython.cpp.template"
                                                              if (! isLrParser && (grammar->k > 1 ||
                                                                                   memoization ||
                                                                                   ! grammar->decisionPoints.empty()))
                                                              {
                                                            #line 1784 "PrintPython.cpp"
  append(L"lk,");
                                                            #line 1199 "PrintPython.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 1790 "PrintPython.cpp"
  append(L"   ");
                                                            #line 1202 "PrintPython.cpp.template"
                                                              }
                                                            #line 1794 "PrintPython.cpp"
  append(L" b0, e0 int");
                                                            #line 1203 "PrintPython.cpp.template"
                                                              for (size_t k = 1; k <= grammar->k; ++k)
                                                              {
                                                                Format format;
                                                                wchar_t *asString = format.toString<wchar_t>(k);
                                                            #line 1801 "PrintPython.cpp"
  append(L"\n");
  append(L"  l");
                                                            #line 1208 "PrintPython.cpp.template"
                                                                print(asString);
                                                            #line 1806 "PrintPython.cpp"
  append(L", b");
                                                            #line 1209 "PrintPython.cpp.template"
                                                                print(asString);
                                                            #line 1810 "PrintPython.cpp"
  append(L", e");
                                                            #line 1210 "PrintPython.cpp.template"
                                                                print(asString);
                                                            #line 1814 "PrintPython.cpp"
  append(L" int");
                                                            #line 1211 "PrintPython.cpp.template"
                                                              }
                                                              if (hasBacktracking)
                                                              {
                                                            #line 1820 "PrintPython.cpp"
  append(L"\n");
  append(L"  bx, ex, sx, lx, tx int");
                                                            #line 1215 "PrintPython.cpp.template"
                                                              }
                                                              else if (isLrParser && ! useGlr)
                                                              {
                                                            #line 1827 "PrintPython.cpp"
  append(L"\n");
  append(L"  iStack []int\n");
  append(L"  top int");
                                                            #line 1220 "PrintPython.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                                if (isLrParser)
                                                                {
                                                                  if (useGlr)
                                                                  {
                                                            #line 1839 "PrintPython.cpp"
  append(L"\n");
  append(L"  bw, bs, es int");
                                                            #line 1228 "PrintPython.cpp.template"
                                                                  }
                                                            #line 1844 "PrintPython.cpp"
  append(L"\n");
  append(L"  eventHandler BottomUpEventHandler");
                                                            #line 1230 "PrintPython.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1851 "PrintPython.cpp"
  append(L"\n");
  append(L"  eventHandler EventHandler");
                                                            #line 1234 "PrintPython.cpp.template"
                                                                }
                                                              }
                                                            }

                                                            void PrintPython::printSimpleMain()
                                                            {
                                                            #line 1861 "PrintPython.cpp"
  append(L"\n");
  append(L"def main(args):\n");
  append(L"  if len(args) < 2:\n");
  append(L"    sys.stderr.write(\"Usage: python ");
                                                            #line 1243 "PrintPython.cpp.template"
                                                              print(className.c_str());
                                                            #line 1868 "PrintPython.cpp"
  append(L".py ");
                                                            #line 1244 "PrintPython.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 1873 "PrintPython.cpp"
  append(L"[-i] ");
                                                            #line 1246 "PrintPython.cpp.template"
                                                              }
                                                            #line 1877 "PrintPython.cpp"
  append(L"INPUT...\\n\")\n");
  append(L"    sys.stderr.write(\"\\n\")\n");
  append(L"    sys.stderr.write(\"  parse INPUT, which is either a filename or literal text enclosed in curly braces\\n\")");
                                                            #line 1250 "PrintPython.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 1884 "PrintPython.cpp"
  append(L"\n");
  append(L"    sys.stderr.write(\"\\n\")\n");
  append(L"    sys.stderr.write(\"  Option:\\n\")\n");
  append(L"    sys.stderr.write(\"    -i     indented parse tree\\n\")");
                                                            #line 1255 "PrintPython.cpp.template"
                                                              }
                                                            #line 1891 "PrintPython.cpp"
  append(L"\n");
  append(L"  else:");
                                                            #line 1257 "PrintPython.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 1897 "PrintPython.cpp"
  append(L"\n");
  append(L"    indent = False");
                                                            #line 1260 "PrintPython.cpp.template"
                                                              }
                                                            #line 1902 "PrintPython.cpp"
  append(L"\n");
  append(L"    for arg in args[1:]:");
                                                            #line 1262 "PrintPython.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 1908 "PrintPython.cpp"
  append(L"\n");
  append(L"      if arg == \"-i\":\n");
  append(L"        indent = True\n");
  append(L"        continue\n");
  append(L"      s = ");
                                                            #line 1268 "PrintPython.cpp.template"
                                                                print(className.c_str());
                                                            #line 1916 "PrintPython.cpp"
  append(L".XmlSerializer()\n");
  append(L"      s.indent = indent");
                                                            #line 1270 "PrintPython.cpp.template"
                                                                if (isLrParser)
                                                                {
                                                            #line 1922 "PrintPython.cpp"
  append(L"\n");
  append(L"      b = ");
                                                            #line 1273 "PrintPython.cpp.template"
                                                                  print(className.c_str());
                                                            #line 1927 "PrintPython.cpp"
  append(L".ParseTreeBuilder()");
                                                            #line 1274 "PrintPython.cpp.template"
                                                                }
                                                              }
                                                            #line 1932 "PrintPython.cpp"
  append(L"\n");
  append(L"      inputString = read(arg)\n");
  append(L"      parser = ");
                                                            #line 1278 "PrintPython.cpp.template"
                                                              print(className.c_str());
                                                            #line 1938 "PrintPython.cpp"
  append(L"(inputString");
                                                            #line 1279 "PrintPython.cpp.template"
                                                              if (noLexer)
                                                              {
                                                            #line 1943 "PrintPython.cpp"
  append(L", ");
                                                            #line 1281 "PrintPython.cpp.template"
                                                                print(className.c_str());
                                                            #line 1947 "PrintPython.cpp"
  append(L"Lexer()");
                                                            #line 1282 "PrintPython.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                            #line 1953 "PrintPython.cpp"
  append(L", ");
                                                            #line 1285 "PrintPython.cpp.template"
                                                                if (isLrParser)
                                                                {
                                                            #line 1958 "PrintPython.cpp"
  append(L"b");
                                                            #line 1287 "PrintPython.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1964 "PrintPython.cpp"
  append(L"s");
                                                            #line 1290 "PrintPython.cpp.template"
                                                                }
                                                              }
                                                            #line 1969 "PrintPython.cpp"
  append(L")");
                                                            #line 1292 "PrintPython.cpp.template"
                                                              if (trace)
                                                              {
                                                            #line 1974 "PrintPython.cpp"
  append(L"\n");
  append(L"      sys.stderr.reconfigure(encoding=\"utf-8\")\n");
  append(L"      ");
                                                            #line 1296 "PrintPython.cpp.template"
                                                                print(className.c_str());
                                                            #line 1980 "PrintPython.cpp"
  append(L".writeTrace(\"<?xml version=\\\"1.0\\\" encoding=\\\"UTF-8\\\"?\" + \">\\n<trace>\\n\")");
                                                            #line 1298 "PrintPython.cpp.template"
                                                              }
                                                            #line 1984 "PrintPython.cpp"
  append(L"\n");
  append(L"      try:\n");
  append(L"        parser.");
                                                            #line 1301 "PrintPython.cpp.template"
                                                              print(visibilityMethodPrefix());
                                                              print(Format::acceptableName<WString>(grammar->startSymbol()->name).c_str());
                                                            #line 1991 "PrintPython.cpp"
  append(L"()");
                                                            #line 1303 "PrintPython.cpp.template"
                                                              if (trace)
                                                              {
                                                            #line 1996 "PrintPython.cpp"
  append(L"\n");
  append(L"        ");
                                                            #line 1306 "PrintPython.cpp.template"
                                                                print(className.c_str());
                                                            #line 2001 "PrintPython.cpp"
  append(L".writeTrace(\"</trace>\\n\")");
                                                            #line 1307 "PrintPython.cpp.template"
                                                              }
                                                              if (tree && isLrParser)
                                                              {
                                                            #line 2007 "PrintPython.cpp"
  append(L"\n");
  append(L"        b.serialize(s)");
                                                            #line 1311 "PrintPython.cpp.template"
                                                              }
                                                            #line 2012 "PrintPython.cpp"
  append(L"\n");
  append(L"      except ");
                                                            #line 1313 "PrintPython.cpp.template"
                                                              print(className.c_str());
                                                            #line 2017 "PrintPython.cpp"
  append(L".ParseException as pe:");
                                                            #line 1314 "PrintPython.cpp.template"
                                                              if (rejectsAmbiguity() && tree)
                                                              {
                                                            #line 2022 "PrintPython.cpp"
  append(L"\n");
  append(L"        if pe.isAmbiguousInput():\n");
  append(L"          pe.serialize(s)\n");
  append(L"          print()");
                                                            #line 1319 "PrintPython.cpp.template"
                                                              }
                                                            #line 2029 "PrintPython.cpp"
  append(L"\n");
  append(L"        raise Exception (\"ParseException while processing \" + arg + \":\\n\" + parser.getErrorMessage(pe)) from pe\n");
  append(L"\n");
  append(L"if __name__ == '__main__':\n");
  append(L"  sys.exit(main(sys.argv))\n");
                                                            #line 1325 "PrintPython.cpp.template"
                                                            }

// End
