// This file was generated on Fri Nov 20, 2026 22:42 (UTC+01) by REx v7.1-SNAPSHOT which is Copyright (c) 1979-2026 by Gunther Rademacher <grd@gmx.net>
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
  append(L"    self.threads = None");
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
  append(L"    self.action = self.predict(initialState)\n");
  append(L"    self.threads = [(False, self.e0, self.id, self)]\n");
  append(L"    return self.threads\n");
  append(L"\n");
  append(L"  def copy(self, other, action):\n");
  append(L"    self.action = action\n");
  append(L"    self.accepted = other.accepted\n");
  append(L"    self.target = other.target\n");
  append(L"    self.parser = other.parser");
                                                            #line 455 "PrintPython.cpp.template"
                                                              if (resolvesAmbiguity)
                                                              {
                                                            #line 724 "PrintPython.cpp"
  append(L"\n");
  append(L"    self.eventCount = other.eventCount");
                                                            #line 458 "PrintPython.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                            #line 731 "PrintPython.cpp"
  append(L"\n");
  append(L"    self.bs = other.bs\n");
  append(L"    self.es = other.es\n");
  append(L"    self.bw = other.bw\n");
  append(L"    self.eventHandler = other.eventHandler\n");
  append(L"    self.deferredEvent = other.deferredEvent");
                                                            #line 466 "PrintPython.cpp.template"
                                                              }
                                                              if (hasCustomCode)
                                                              {
                                                            #line 742 "PrintPython.cpp"
  append(L"\n");
  append(L"    self.deferredCode = other.deferredCode");
                                                            #line 470 "PrintPython.cpp.template"
                                                              }
                                                            #line 747 "PrintPython.cpp"
  append(L"\n");
  append(L"    self.parser.maxId += 1\n");
  append(L"    self.id = self.parser.maxId\n");
  append(L"    self.threads = other.threads\n");
  append(L"    self.state = other.state\n");
  append(L"    self.stack = other.stack\n");
  append(L"    self.b0 = other.b0\n");
  append(L"    self.e0 = other.e0");
                                                            #line 478 "PrintPython.cpp.template"
                                                              for (size_t i = 1; i <= grammar->k; ++i)
                                                              {
                                                                const wchar_t *iString = format.toString<wchar_t>(i);
                                                            #line 760 "PrintPython.cpp"
  append(L"\n");
  append(L"    self.l");
                                                            #line 482 "PrintPython.cpp.template"
                                                                print(iString);
                                                            #line 765 "PrintPython.cpp"
  append(L" = other.l");
                                                            #line 483 "PrintPython.cpp.template"
                                                                print(iString);
                                                            #line 769 "PrintPython.cpp"
  append(L"\n");
  append(L"    self.b");
                                                            #line 485 "PrintPython.cpp.template"
                                                                print(iString);
                                                            #line 774 "PrintPython.cpp"
  append(L" = other.b");
                                                            #line 486 "PrintPython.cpp.template"
                                                                print(iString);
                                                            #line 778 "PrintPython.cpp"
  append(L"\n");
  append(L"    self.e");
                                                            #line 488 "PrintPython.cpp.template"
                                                                print(iString);
                                                            #line 783 "PrintPython.cpp"
  append(L" = other.e");
                                                            #line 489 "PrintPython.cpp.template"
                                                                print(iString);
                                                              }
                                                            #line 788 "PrintPython.cpp"
  append(L"\n");
  append(L"    self.end = other.end\n");
  append(L"    return self\n");
                                                            #line 494 "PrintPython.cpp.template"
                                                              if (resolvesAmbiguity && tree)
                                                              {
                                                            #line 795 "PrintPython.cpp"
  append(L"\n");
  append(L"  def addAmbiguity(self, begin, end):\n");
  append(L"    if self.eventHandler != None:\n");
  append(L"      self.deferredEvent = ");
                                                            #line 499 "PrintPython.cpp.template"
                                                                print(className.c_str());
                                                            #line 802 "PrintPython.cpp"
  append(L".AmbiguityEvent(self.deferredEvent, begin, end)\n");
                                                            #line 501 "PrintPython.cpp.template"
                                                              }
                                                            #line 806 "PrintPython.cpp"
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
                                                            #line 520 "PrintPython.cpp.template"
                                                              increaseIndent();
                                                              beginPublic();
                                                            }

                                                            void PrintPython::printFlush(int i, bool withinThread)
                                                            {
                                                              if (trace)
                                                              {
                                                                increaseIndent(i);
                                                            #line 836 "PrintPython.cpp"
  append(L"\n");
                                                            #line 530 "PrintPython.cpp.template"
                                                                print(className.c_str());
                                                            #line 840 "PrintPython.cpp"
  append(L".flushTrace()");
                                                            #line 531 "PrintPython.cpp.template"
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
                                                            #line 854 "PrintPython.cpp"
  append(L"\n");
  append(L"def ");
                                                            #line 543 "PrintPython.cpp.template"
                                                              print(name);
                                                            #line 859 "PrintPython.cpp"
  append(L"(self");
                                                            #line 544 "PrintPython.cpp.template"
                                                              if (*args != 0)
                                                              {
                                                            #line 864 "PrintPython.cpp"
  append(L", ");
                                                            #line 546 "PrintPython.cpp.template"
                                                                printArgNamesOnly(args);
                                                              }
                                                            #line 869 "PrintPython.cpp"
  append(L"):");
                                                            #line 548 "PrintPython.cpp.template"
                                                            }

                                                            void PrintPython::privateVars()
                                                            {
                                                              if (trace)
                                                              {
                                                                increaseIndent();
                                                            #line 879 "PrintPython.cpp"
  append(L"\n");
  append(L"def lookaheadString(self):\n");
  append(L"  result = \"\"");
                                                            #line 557 "PrintPython.cpp.template"
                                                                for (size_t i = 1; i <= grammar->k; ++i)
                                                                {
                                                            #line 886 "PrintPython.cpp"
  append(L"\n");
  append(L"  if self.l");
                                                            #line 560 "PrintPython.cpp.template"
                                                                  print(format.toString<wchar_t>(i));
                                                            #line 891 "PrintPython.cpp"
  append(L" > 0:\n");
  append(L"    result += ");
                                                            #line 562 "PrintPython.cpp.template"
                                                                  if (i != 1)
                                                                  {
                                                            #line 897 "PrintPython.cpp"
  append(L"\" \" + ");
                                                            #line 564 "PrintPython.cpp.template"
                                                                  }
                                                                  print(className.c_str());
                                                            #line 902 "PrintPython.cpp"
  append(L".TOKEN[self.l");
                                                            #line 566 "PrintPython.cpp.template"
                                                                  print(format.toString<wchar_t>(i));
                                                            #line 906 "PrintPython.cpp"
  append(L"]");
                                                            #line 567 "PrintPython.cpp.template"
                                                                  increaseIndent();
                                                                }
                                                                for (size_t i = 1; i <= grammar->k; ++i)
                                                                {
                                                                  decreaseIndent();
                                                                }
                                                            #line 915 "PrintPython.cpp"
  append(L"\n");
  append(L"  return result\n");
                                                            #line 575 "PrintPython.cpp.template"
                                                                decreaseIndent();
                                                              }
                                                              if (memoization)
                                                              {
                                                                increaseIndent();
                                                                int bits = Math::bits(grammar->conflictCount);
                                                            #line 925 "PrintPython.cpp"
  append(L"\n");
  append(L"def memoize(self, i, e, v):\n");
  append(L"  self.memo[(e << ");
                                                            #line 583 "PrintPython.cpp.template"
                                                                print(format.toString<wchar_t>(bits));
                                                            #line 931 "PrintPython.cpp"
  append(L") + i] = v\n");
  append(L"\n");
  append(L"def memoized(self, i, e):\n");
  append(L"  return self.memo.get((e << ");
                                                            #line 587 "PrintPython.cpp.template"
                                                                print(format.toString<wchar_t>(bits));
                                                            #line 938 "PrintPython.cpp"
  append(L") + i, 0)\n");
                                                            #line 589 "PrintPython.cpp.template"
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
                                                            #line 953 "PrintPython.cpp"
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
                                                            #line 620 "PrintPython.cpp.template"
                                                              }
                                                            #line 975 "PrintPython.cpp"
  append(L"\n");
  append(L"class ParseJob:\n");
  append(L"\n");
  append(L"  def __init__(self, name, parser");
                                                            #line 624 "PrintPython.cpp.template"
                                                              if (tree)
                                                              {
                                                                if (isLrParser)
                                                                {
                                                            #line 985 "PrintPython.cpp"
  append(L", parseTreeBuilder");
                                                            #line 628 "PrintPython.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 991 "PrintPython.cpp"
  append(L", contentCounter");
                                                            #line 631 "PrintPython.cpp.template"
                                                                }
                                                              }
                                                            #line 996 "PrintPython.cpp"
  append(L"):\n");
  append(L"    self.name = name\n");
  append(L"    self.parser = parser");
                                                            #line 635 "PrintPython.cpp.template"
                                                              if (tree)
                                                              {
                                                                if (isLrParser)
                                                                {
                                                            #line 1005 "PrintPython.cpp"
  append(L"\n");
  append(L"    self.parseTreeBuilder = parseTreeBuilder\n");
  append(L"    self.contentCounter = ContentCounter()");
                                                            #line 641 "PrintPython.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1013 "PrintPython.cpp"
  append(L"\n");
  append(L"    self.contentCounter = contentCounter");
                                                            #line 645 "PrintPython.cpp.template"
                                                                }
                                                              }
                                                            #line 1019 "PrintPython.cpp"
  append(L"\n");
  append(L"\n");
  append(L"def main(args):\n");
  append(L"  if len(args) < 2:\n");
  append(L"    sys.stderr.write(\"Usage: python ");
                                                            #line 651 "PrintPython.cpp.template"
                                                              print(className.c_str());
                                                            #line 1027 "PrintPython.cpp"
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
                                                            #line 692 "PrintPython.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 1072 "PrintPython.cpp"
  append(L"\n");
  append(L"          contentCounter = ContentCounter()");
                                                            #line 695 "PrintPython.cpp.template"
                                                                if (isLrParser)
                                                                {
                                                            #line 1078 "PrintPython.cpp"
  append(L"\n");
  append(L"          parseTreeBuilder = ");
                                                            #line 698 "PrintPython.cpp.template"
                                                                  print(className.c_str());
                                                            #line 1083 "PrintPython.cpp"
  append(L".ParseTreeBuilder()");
                                                            #line 699 "PrintPython.cpp.template"
                                                                }
                                                              }
                                                            #line 1088 "PrintPython.cpp"
  append(L"\n");
  append(L"          content = read(path)\n");
  append(L"          parsers.append(ParseJob(path, ");
                                                            #line 703 "PrintPython.cpp.template"
                                                              print(className.c_str());
                                                            #line 1094 "PrintPython.cpp"
  append(L"(content");
                                                            #line 704 "PrintPython.cpp.template"
                                                              if (tree)
                                                              {
                                                                if (isLrParser)
                                                                {
                                                            #line 1101 "PrintPython.cpp"
  append(L", parseTreeBuilder");
                                                            #line 708 "PrintPython.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1107 "PrintPython.cpp"
  append(L", contentCounter");
                                                            #line 711 "PrintPython.cpp.template"
                                                                }
                                                              }
                                                            #line 1112 "PrintPython.cpp"
  append(L")");
                                                            #line 713 "PrintPython.cpp.template"
                                                              if (tree)
                                                              {
                                                                if (isLrParser)
                                                                {
                                                            #line 1119 "PrintPython.cpp"
  append(L", parseTreeBuilder");
                                                            #line 717 "PrintPython.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1125 "PrintPython.cpp"
  append(L", contentCounter");
                                                            #line 720 "PrintPython.cpp.template"
                                                                }
                                                              }
                                                            #line 1130 "PrintPython.cpp"
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
                                                            #line 748 "PrintPython.cpp.template"
                                                              if (useGlr)
                                                              {
                                                            #line 1161 "PrintPython.cpp"
  append(L".thread");
                                                            #line 750 "PrintPython.cpp.template"
                                                              }
                                                            #line 1165 "PrintPython.cpp"
  append(L".reset(0, 0, 0)\n");
  append(L"            try:\n");
  append(L"              pe = job.parser.parse_");
                                                            #line 753 "PrintPython.cpp.template"
                                                              print(Format::acceptableName<WString>(grammar->startSymbol()->name).c_str());
                                                            #line 1171 "PrintPython.cpp"
  append(L"()\n");
  append(L"            except ");
                                                            #line 755 "PrintPython.cpp.template"
                                                              print(className.c_str());
                                                            #line 1176 "PrintPython.cpp"
  append(L".ParseException as pe:\n");
  append(L"              errorCount += 1\n");
  append(L"              if quiet:\n");
  append(L"                print(\"parsing \" + job.name)\n");
  append(L"              print(\": error: \" + job.parser.GetErrorMessage(pe))\n");
  append(L"              job.parser = None\n");
  append(L"            if not quiet:\n");
  append(L"              print()");
                                                            #line 763 "PrintPython.cpp.template"
                                                              if (tree)
                                                              {
                                                                if (isLrParser)
                                                                {
                                                            #line 1190 "PrintPython.cpp"
  append(L"\n");
  append(L"            job.parseTreeBuilder.serialize(job.contentCounter)");
                                                            #line 768 "PrintPython.cpp.template"
                                                                }
                                                            #line 1195 "PrintPython.cpp"
  append(L"\n");
  append(L"            if job.contentCounter.getLength() != len(job.parser.input):\n");
  append(L"              raise Exception(\"content counter saw \" + str(job.contentCounter.getLength()) + \", but input length is \" + str(len(job.parser.input)))");
                                                            #line 772 "PrintPython.cpp.template"
                                                              }
                                                            #line 1201 "PrintPython.cpp"
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
                                                            #line 794 "PrintPython.cpp.template"
                                                            }

                                                            void PrintPython::printReadMethod()
                                                            {
                                                            #line 1228 "PrintPython.cpp"
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
                                                            #line 808 "PrintPython.cpp.template"
                                                            }

                                                            void PrintPython::printInterface()
                                                            {
                                                              if (! packageName.empty())
                                                              {
                                                            #line 1246 "PrintPython.cpp"
  append(L"\n");
  append(L"package ");
                                                            #line 815 "PrintPython.cpp.template"
                                                                print(packageName.c_str());
                                                            #line 1251 "PrintPython.cpp"
  append(L";\n");
                                                            #line 817 "PrintPython.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                                if (main || useGlr)
                                                                {
                                                            #line 1259 "PrintPython.cpp"
  append(L"\n");
  append(L"import java.io.IOException;\n");
  append(L"import java.io.Writer;\n");
                                                            #line 825 "PrintPython.cpp.template"
                                                                }
                                                            #line 1265 "PrintPython.cpp"
  append(L"\n");
  append(L"import java.util.Arrays;");
                                                            #line 827 "PrintPython.cpp.template"
                                                              }
                                                            #line 1270 "PrintPython.cpp"
  append(L"\n");
  append(L"public interface ");
                                                            #line 829 "PrintPython.cpp.template"
                                                              print(className.c_str());
                                                            #line 1275 "PrintPython.cpp"
  append(L"\n");
  append(L"{\n");
  append(L"  public void initialize(CharSequence input");
                                                            #line 832 "PrintPython.cpp.template"
                                                              if (noLexer)
                                                              {
                                                            #line 1282 "PrintPython.cpp"
  append(L", Lexer l");
                                                            #line 834 "PrintPython.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                            #line 1288 "PrintPython.cpp"
  append(L", ");
                                                            #line 837 "PrintPython.cpp.template"
                                                                if (isLrParser)
                                                                {
                                                            #line 1293 "PrintPython.cpp"
  append(L"BottomUp");
                                                            #line 839 "PrintPython.cpp.template"
                                                                }
                                                            #line 1297 "PrintPython.cpp"
  append(L"EventHandler eh");
                                                            #line 841 "PrintPython.cpp.template"
                                                              }
                                                            #line 1301 "PrintPython.cpp"
  append(L");\n");
  append(L"  public void parse();\n");
  append(L"  public void Reset();\n");
  append(L"  public String getErrorMessage(ParseException e);\n");
                                                            #line 846 "PrintPython.cpp.template"
                                                              printParseException();
                                                              printEventHandlerImplementation();
                                                            #line 1309 "PrintPython.cpp"
  append(L"}\n");
                                                            #line 849 "PrintPython.cpp.template"
                                                            }

                                                            void PrintPython::printParseException()
                                                            {
                                                            #line 1316 "PrintPython.cpp"
  append(L"\n");
  append(L"class ParseException(Exception):\n");
                                                            #line 855 "PrintPython.cpp.template"
                                                              increaseIndent();
                                                            #line 1321 "PrintPython.cpp"
  append(L"\n");
  append(L"def __init__(self, b, e, s, o, x");
                                                            #line 857 "PrintPython.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 1327 "PrintPython.cpp"
  append(L", ambiguousInput = False");
                                                            #line 859 "PrintPython.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 1332 "PrintPython.cpp"
  append(L", ambiguityDescriptor = None");
                                                            #line 861 "PrintPython.cpp.template"
                                                                }
                                                              }
                                                            #line 1337 "PrintPython.cpp"
  append(L"):\n");
  append(L"  self.begin = b\n");
  append(L"  self.end = e\n");
  append(L"  self.state = s\n");
  append(L"  self.offending = o\n");
  append(L"  self.expected = x");
                                                            #line 868 "PrintPython.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 1347 "PrintPython.cpp"
  append(L"\n");
  append(L"  self.ambiguousInput = ambiguousInput");
                                                            #line 871 "PrintPython.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 1353 "PrintPython.cpp"
  append(L"\n");
  append(L"  self.ambiguityDescriptor = ambiguityDescriptor");
                                                            #line 874 "PrintPython.cpp.template"
                                                                }
                                                              }
                                                            #line 1359 "PrintPython.cpp"
  append(L"\n");
  append(L"\n");
  append(L"def error(self):\n");
  append(L"  if ");
                                                            #line 879 "PrintPython.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 1367 "PrintPython.cpp"
  append(L"self.ambiguousInput:\n");
  append(L"    return \"ambiguous input\"\n");
  append(L"  elif ");
                                                            #line 883 "PrintPython.cpp.template"
                                                              }
                                                            #line 1373 "PrintPython.cpp"
  append(L"self.offending < 0:\n");
  append(L"    return \"lexical analysis failed\"\n");
  append(L"  else:\n");
  append(L"    return \"syntax error\"\n");
                                                            #line 888 "PrintPython.cpp.template"
                                                              if (tree && rejectsAmbiguity())
                                                              {
                                                            #line 1381 "PrintPython.cpp"
  append(L"\n");
  append(L"def serialize(self, eventHandler):");
                                                            #line 891 "PrintPython.cpp.template"
                                                                if (rejectsAmbiguity())
                                                                {
                                                            #line 1387 "PrintPython.cpp"
  append(L"\n");
  append(L"  self.ambiguityDescriptor.serialize(eventHandler)");
                                                            #line 894 "PrintPython.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1394 "PrintPython.cpp"
  append(L"\n");
  append(L"  pass");
                                                            #line 898 "PrintPython.cpp.template"
                                                                }
                                                            #line 1399 "PrintPython.cpp"
  append(L"\n");
                                                            #line 900 "PrintPython.cpp.template"
                                                              }
                                                            #line 1403 "PrintPython.cpp"
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
                                                            #line 916 "PrintPython.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 1422 "PrintPython.cpp"
  append(L"\n");
  append(L"def isAmbiguousInput(self):\n");
  append(L"  return ");
                                                            #line 920 "PrintPython.cpp.template"
                                                                if (rejectsAmbiguity())
                                                                {
                                                            #line 1429 "PrintPython.cpp"
  append(L"self.ambiguousInput");
                                                            #line 922 "PrintPython.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1435 "PrintPython.cpp"
  append(L"False");
                                                            #line 925 "PrintPython.cpp.template"
                                                                }
                                                              }
                                                              decreaseIndent();
                                                            #line 1441 "PrintPython.cpp"
  append(L"\n");
                                                            #line 929 "PrintPython.cpp.template"
                                                              if (noLexer)
                                                              {
                                                            #line 1446 "PrintPython.cpp"
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
                                                            #line 944 "PrintPython.cpp.template"
                                                              }
                                                              if (emitsTopDownTreeBuilder())
                                                              {
                                                            #line 1464 "PrintPython.cpp"
  append(L"\n");
  append(L"class TopDownTreeBuilder:\n");
                                                            #line 949 "PrintPython.cpp.template"
                                                                increaseIndent();
                                                            #line 1469 "PrintPython.cpp"
  append(L"\n");
  append(L"def reset(self, inputString):\n");
  append(L"  self.input = inputString\n");
  append(L"  self.stack = []\n");
  append(L"  self.top = -1\n");
  append(L"\n");
  append(L"def startNonterminal(self, id, begin):\n");
  append(L"  nonterminal = ");
                                                            #line 957 "PrintPython.cpp.template"
                                                                print(className.c_str());
                                                            #line 1480 "PrintPython.cpp"
  append(L".Nonterminal(id, begin, begin, [])\n");
  append(L"  if self.top >= 0:\n");
  append(L"    self.addChild(nonterminal)\n");
  append(L"  self.top += 1\n");
  append(L"  if self.top < len(self.stack):\n");
  append(L"    self.stack[self.top] = nonterminal\n");
  append(L"  else:\n");
  append(L"    self.stack.append(nonterminal)\n");
  append(L"\n");
  append(L"def endNonterminal(self, _, end):\n");
  append(L"  self.stack[self.top].end = end\n");
  append(L"  if self.top > 0:\n");
  append(L"    self.top -= 1\n");
  append(L"\n");
  append(L"def terminal(self, id, begin, end):\n");
  append(L"  self.addChild(");
                                                            #line 973 "PrintPython.cpp.template"
                                                                print(className.c_str());
                                                            #line 1499 "PrintPython.cpp"
  append(L".Terminal(id, begin, end))\n");
  append(L"\n");
  append(L"def whitespace(self, begin, end):\n");
  append(L"  pass\n");
  append(L"\n");
  append(L"def addChild(self, s):\n");
  append(L"  current = self.stack[self.top]\n");
  append(L"  current.addChild(s)\n");
  append(L"\n");
  append(L"def getRoot(self):\n");
  append(L"  return self.stack[0] if getattr(self, \"top\", -1) >= 0 else None\n");
  append(L"\n");
  append(L"def serialize(self, e):\n");
  append(L"  e.reset(self.input)\n");
  append(L"  self.stack[0].send(e)\n");
                                                            #line 989 "PrintPython.cpp.template"
                                                                decreaseIndent();
                                                              }
                                                              if (emitsTreeNodes())
                                                              {
                                                            #line 1520 "PrintPython.cpp"
  append(L"\n");
  append(L"class Symbol:\n");
                                                            #line 995 "PrintPython.cpp.template"
                                                                increaseIndent();
                                                            #line 1525 "PrintPython.cpp"
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
                                                            #line 1010 "PrintPython.cpp.template"
                                                                decreaseIndent();
                                                            #line 1542 "PrintPython.cpp"
  append(L"\n");
  append(L"class Nonterminal(Symbol):\n");
                                                            #line 1013 "PrintPython.cpp.template"
                                                                increaseIndent();
                                                            #line 1547 "PrintPython.cpp"
  append(L"\n");
  append(L"def __init__(self, id, begin, end, children):\n");
  append(L"  super().__init__(id, begin, end)\n");
  append(L"  self.children = children\n");
  append(L"\n");
  append(L"def getName(self):\n");
  append(L"  return ");
                                                            #line 1020 "PrintPython.cpp.template"
                                                                printSyntheticNamePrefix(false, L"self.id");
                                                                print(className.c_str());
                                                            #line 1558 "PrintPython.cpp"
  append(L".NONTERMINAL[self.id]");
                                                            #line 1022 "PrintPython.cpp.template"
                                                                printSyntheticNameSuffix(false, L"self.id");
                                                            #line 1562 "PrintPython.cpp"
  append(L"\n");
  append(L"\n");
  append(L"def addChild(self, s):\n");
  append(L"  self.children.append(s)\n");
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
                                                            #line 1039 "PrintPython.cpp.template"
                                                                decreaseIndent();
                                                            #line 1581 "PrintPython.cpp"
  append(L"\n");
  append(L"class Terminal(Symbol):\n");
                                                            #line 1042 "PrintPython.cpp.template"
                                                                increaseIndent();
                                                            #line 1586 "PrintPython.cpp"
  append(L"\n");
  append(L"def __init__(self, id, begin, end):\n");
  append(L"  super().__init__(id, begin, end)\n");
  append(L"\n");
  append(L"def getName(self):\n");
  append(L"  return ");
                                                            #line 1048 "PrintPython.cpp.template"
                                                                print(className.c_str());
                                                            #line 1595 "PrintPython.cpp"
  append(L".TOKEN[self.id]\n");
  append(L"\n");
  append(L"def send(self, e):\n");
  append(L"  e.terminal(self.id, self.getBegin(), self.getEnd())\n");
                                                            #line 1053 "PrintPython.cpp.template"
                                                                decreaseIndent();
                                                              }
                                                            }

                                                            void PrintPython::printEventHandlerImplementation()
                                                            {
                                                              if (tree)
                                                              {
                                                                if (emitsXmlSerializer())
                                                                {
                                                            #line 1611 "PrintPython.cpp"
  append(L"\n");
  append(L"class XmlSerializer:\n");
                                                            #line 1065 "PrintPython.cpp.template"
                                                                  increaseIndent();
                                                            #line 1616 "PrintPython.cpp"
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
                                                            #line 1076 "PrintPython.cpp.template"
                                                                  print(className.c_str());
                                                            #line 1630 "PrintPython.cpp"
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
                                                            #line 1093 "PrintPython.cpp.template"
                                                                  print(className.c_str());
                                                            #line 1650 "PrintPython.cpp"
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
                                                            #line 1138 "PrintPython.cpp.template"
                                                                  print(className.c_str());
                                                            #line 1698 "PrintPython.cpp"
  append(L".getTerminalName(id)\n");
  append(L"  if tag[0] == '\\'':\n");
  append(L"    tag = \"TOKEN\"\n");
  append(L"  self.startElement(tag)\n");
  append(L"  self.characters(b, e)\n");
  append(L"  self.endElement(tag)\n");
                                                            #line 1145 "PrintPython.cpp.template"
                                                                  decreaseIndent();
                                                                }
                                                                if (emitsParseTreeBuilder())
                                                                {
                                                            #line 1710 "PrintPython.cpp"
  append(L"\n");
  append(L"class ParseTreeBuilder:\n");
                                                            #line 1151 "PrintPython.cpp.template"
                                                                  increaseIndent();
                                                            #line 1715 "PrintPython.cpp"
  append(L"\n");
  append(L"def reset(self, inputString):\n");
  append(L"  self.input = inputString\n");
  append(L"  self.stack = []\n");
  append(L"\n");
  append(L"def nonterminal(self, id, begin, end, count):");
                                                            #line 1157 "PrintPython.cpp.template"
                                                                  if (rejectsAmbiguity())
                                                                  {
                                                            #line 1725 "PrintPython.cpp"
  append(L"\n");
  append(L"  if count > len(self.stack):\n");
  append(L"    content = self.pop(len(self.stack))\n");
  append(L"    e = end\n");
  append(L"    if len(content) != 0:\n");
  append(L"      e = content[0].getBegin()\n");
  append(L"    self.nonterminal(");
                                                            #line 1165 "PrintPython.cpp.template"
                                                                    print(format.toString<wchar_t>(Grammar::syntheticNonterminalCode(2)));
                                                            #line 1735 "PrintPython.cpp"
  append(L", begin, e, 0)\n");
  append(L"    for symbol in content:\n");
  append(L"      self.push(symbol)\n");
  append(L"    count = len(self.stack)");
                                                            #line 1169 "PrintPython.cpp.template"
                                                                  }
                                                            #line 1742 "PrintPython.cpp"
  append(L"\n");
  append(L"  self.push(");
                                                            #line 1171 "PrintPython.cpp.template"
                                                                  print(className.c_str());
                                                            #line 1747 "PrintPython.cpp"
  append(L".Nonterminal(id, begin, end, self.pop(count)))\n");
  append(L"\n");
  append(L"def terminal(self, id, begin, end):\n");
  append(L"  self.push(");
                                                            #line 1175 "PrintPython.cpp.template"
                                                                  print(className.c_str());
                                                            #line 1754 "PrintPython.cpp"
  append(L".Terminal(id, begin, end))\n");
                                                            #line 1177 "PrintPython.cpp.template"
                                                                  if (resolvesAmbiguity)
                                                                  {
                                                            #line 1759 "PrintPython.cpp"
  append(L"\n");
  append(L"\n");
  append(L"def ambiguity(self, begin, end):\n");
  append(L"  pass\n");
                                                            #line 1183 "PrintPython.cpp.template"
                                                                  }
                                                            #line 1766 "PrintPython.cpp"
  append(L"\n");
  append(L"def getRoot(self):\n");
  append(L"  return self.stack[0] if len(getattr(self, \"stack\", [])) > 0 else None\n");
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
                                                            #line 1203 "PrintPython.cpp.template"
                                                                  decreaseIndent();
                                                                }
                                                              }
                                                            }

                                                            void PrintPython::printTokenVars()
                                                            {
                                                            #line 1794 "PrintPython.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 1211 "PrintPython.cpp.template"
                                                              if (! isLrParser && (grammar->k > 1 ||
                                                                                   memoization ||
                                                                                   ! grammar->decisionPoints.empty()))
                                                              {
                                                            #line 1802 "PrintPython.cpp"
  append(L"lk,");
                                                            #line 1215 "PrintPython.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 1808 "PrintPython.cpp"
  append(L"   ");
                                                            #line 1218 "PrintPython.cpp.template"
                                                              }
                                                            #line 1812 "PrintPython.cpp"
  append(L" b0, e0 int");
                                                            #line 1219 "PrintPython.cpp.template"
                                                              for (size_t k = 1; k <= grammar->k; ++k)
                                                              {
                                                                Format format;
                                                                wchar_t *asString = format.toString<wchar_t>(k);
                                                            #line 1819 "PrintPython.cpp"
  append(L"\n");
  append(L"  l");
                                                            #line 1224 "PrintPython.cpp.template"
                                                                print(asString);
                                                            #line 1824 "PrintPython.cpp"
  append(L", b");
                                                            #line 1225 "PrintPython.cpp.template"
                                                                print(asString);
                                                            #line 1828 "PrintPython.cpp"
  append(L", e");
                                                            #line 1226 "PrintPython.cpp.template"
                                                                print(asString);
                                                            #line 1832 "PrintPython.cpp"
  append(L" int");
                                                            #line 1227 "PrintPython.cpp.template"
                                                              }
                                                              if (hasBacktracking)
                                                              {
                                                            #line 1838 "PrintPython.cpp"
  append(L"\n");
  append(L"  bx, ex, sx, lx, tx int");
                                                            #line 1231 "PrintPython.cpp.template"
                                                              }
                                                              else if (isLrParser && ! useGlr)
                                                              {
                                                            #line 1845 "PrintPython.cpp"
  append(L"\n");
  append(L"  iStack []int\n");
  append(L"  top int");
                                                            #line 1236 "PrintPython.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                                if (isLrParser)
                                                                {
                                                                  if (useGlr)
                                                                  {
                                                            #line 1857 "PrintPython.cpp"
  append(L"\n");
  append(L"  bw, bs, es int");
                                                            #line 1244 "PrintPython.cpp.template"
                                                                  }
                                                            #line 1862 "PrintPython.cpp"
  append(L"\n");
  append(L"  eventHandler BottomUpEventHandler");
                                                            #line 1246 "PrintPython.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1869 "PrintPython.cpp"
  append(L"\n");
  append(L"  eventHandler EventHandler");
                                                            #line 1250 "PrintPython.cpp.template"
                                                                }
                                                              }
                                                            }

                                                            void PrintPython::printSimpleMain()
                                                            {
                                                            #line 1879 "PrintPython.cpp"
  append(L"\n");
  append(L"def main(args):\n");
  append(L"  if len(args) < 2:\n");
  append(L"    sys.stderr.write(\"Usage: python ");
                                                            #line 1259 "PrintPython.cpp.template"
                                                              print(className.c_str());
                                                            #line 1886 "PrintPython.cpp"
  append(L".py ");
                                                            #line 1260 "PrintPython.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 1891 "PrintPython.cpp"
  append(L"[-i] ");
                                                            #line 1262 "PrintPython.cpp.template"
                                                              }
                                                            #line 1895 "PrintPython.cpp"
  append(L"INPUT...\\n\")\n");
  append(L"    sys.stderr.write(\"\\n\")\n");
  append(L"    sys.stderr.write(\"  parse INPUT, which is either a filename or literal text enclosed in curly braces\\n\")");
                                                            #line 1266 "PrintPython.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 1902 "PrintPython.cpp"
  append(L"\n");
  append(L"    sys.stderr.write(\"\\n\")\n");
  append(L"    sys.stderr.write(\"  Option:\\n\")\n");
  append(L"    sys.stderr.write(\"    -i     indented parse tree\\n\")");
                                                            #line 1271 "PrintPython.cpp.template"
                                                              }
                                                            #line 1909 "PrintPython.cpp"
  append(L"\n");
  append(L"  else:");
                                                            #line 1273 "PrintPython.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 1915 "PrintPython.cpp"
  append(L"\n");
  append(L"    indent = False");
                                                            #line 1276 "PrintPython.cpp.template"
                                                              }
                                                            #line 1920 "PrintPython.cpp"
  append(L"\n");
  append(L"    for arg in args[1:]:");
                                                            #line 1278 "PrintPython.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 1926 "PrintPython.cpp"
  append(L"\n");
  append(L"      if arg == \"-i\":\n");
  append(L"        indent = True\n");
  append(L"        continue\n");
  append(L"      s = ");
                                                            #line 1284 "PrintPython.cpp.template"
                                                                print(className.c_str());
                                                            #line 1934 "PrintPython.cpp"
  append(L".XmlSerializer()\n");
  append(L"      s.indent = indent");
                                                            #line 1286 "PrintPython.cpp.template"
                                                                if (isLrParser)
                                                                {
                                                            #line 1940 "PrintPython.cpp"
  append(L"\n");
  append(L"      b = ");
                                                            #line 1289 "PrintPython.cpp.template"
                                                                  print(className.c_str());
                                                            #line 1945 "PrintPython.cpp"
  append(L".ParseTreeBuilder()");
                                                            #line 1290 "PrintPython.cpp.template"
                                                                }
                                                              }
                                                            #line 1950 "PrintPython.cpp"
  append(L"\n");
  append(L"      inputString = read(arg)\n");
  append(L"      parser = ");
                                                            #line 1294 "PrintPython.cpp.template"
                                                              print(className.c_str());
                                                            #line 1956 "PrintPython.cpp"
  append(L"(inputString");
                                                            #line 1295 "PrintPython.cpp.template"
                                                              if (noLexer)
                                                              {
                                                            #line 1961 "PrintPython.cpp"
  append(L", ");
                                                            #line 1297 "PrintPython.cpp.template"
                                                                print(className.c_str());
                                                            #line 1965 "PrintPython.cpp"
  append(L"Lexer()");
                                                            #line 1298 "PrintPython.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                            #line 1971 "PrintPython.cpp"
  append(L", ");
                                                            #line 1301 "PrintPython.cpp.template"
                                                                if (isLrParser)
                                                                {
                                                            #line 1976 "PrintPython.cpp"
  append(L"b");
                                                            #line 1303 "PrintPython.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1982 "PrintPython.cpp"
  append(L"s");
                                                            #line 1306 "PrintPython.cpp.template"
                                                                }
                                                              }
                                                            #line 1987 "PrintPython.cpp"
  append(L")");
                                                            #line 1308 "PrintPython.cpp.template"
                                                              if (trace)
                                                              {
                                                            #line 1992 "PrintPython.cpp"
  append(L"\n");
  append(L"      sys.stderr.reconfigure(encoding=\"utf-8\")\n");
  append(L"      ");
                                                            #line 1312 "PrintPython.cpp.template"
                                                                print(className.c_str());
                                                            #line 1998 "PrintPython.cpp"
  append(L".writeTrace(\"<?xml version=\\\"1.0\\\" encoding=\\\"UTF-8\\\"?\" + \">\\n<trace>\\n\")");
                                                            #line 1314 "PrintPython.cpp.template"
                                                              }
                                                            #line 2002 "PrintPython.cpp"
  append(L"\n");
  append(L"      try:\n");
  append(L"        parser.");
                                                            #line 1317 "PrintPython.cpp.template"
                                                              print(visibilityMethodPrefix());
                                                              print(Format::acceptableName<WString>(grammar->startSymbol()->name).c_str());
                                                            #line 2009 "PrintPython.cpp"
  append(L"()");
                                                            #line 1319 "PrintPython.cpp.template"
                                                              if (trace)
                                                              {
                                                            #line 2014 "PrintPython.cpp"
  append(L"\n");
  append(L"        ");
                                                            #line 1322 "PrintPython.cpp.template"
                                                                print(className.c_str());
                                                            #line 2019 "PrintPython.cpp"
  append(L".writeTrace(\"</trace>\\n\")");
                                                            #line 1323 "PrintPython.cpp.template"
                                                              }
                                                              if (tree && isLrParser)
                                                              {
                                                            #line 2025 "PrintPython.cpp"
  append(L"\n");
  append(L"        b.serialize(s)");
                                                            #line 1327 "PrintPython.cpp.template"
                                                              }
                                                            #line 2030 "PrintPython.cpp"
  append(L"\n");
  append(L"      except ");
                                                            #line 1329 "PrintPython.cpp.template"
                                                              print(className.c_str());
                                                            #line 2035 "PrintPython.cpp"
  append(L".ParseException as pe:");
                                                            #line 1330 "PrintPython.cpp.template"
                                                              if (rejectsAmbiguity() && tree)
                                                              {
                                                            #line 2040 "PrintPython.cpp"
  append(L"\n");
  append(L"        if pe.isAmbiguousInput():\n");
  append(L"          pe.serialize(s)\n");
  append(L"          print()");
                                                            #line 1335 "PrintPython.cpp.template"
                                                              }
                                                            #line 2047 "PrintPython.cpp"
  append(L"\n");
  append(L"        raise Exception (\"ParseException while processing \" + arg + \":\\n\" + parser.getErrorMessage(pe)) from pe\n");
  append(L"\n");
  append(L"if __name__ == '__main__':\n");
  append(L"  sys.exit(main(sys.argv))\n");
                                                            #line 1341 "PrintPython.cpp.template"
                                                            }

// End
