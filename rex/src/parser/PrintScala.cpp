// This file was generated on Tue Oct 20, 2026 19:55 (UTC+02) by REx v6.3-SNAPSHOT which is Copyright (c) 1979-2026 by Gunther Rademacher <grd@gmx.net>
// REx command line: PrintScala.cpp.template
                                                            #line 1 "PrintScala.cpp.template"
                                                            #include "../common/Memory.hpp"

                                                            #include "PrintScala.hpp"
                                                            #include "ItemSet.hpp"
                                                            #include "../common/CompressedMap.hpp"

                                                            void PrintScala::openClass()
                                                            {
                                                              if (! hasProlog)
                                                              {
                                                                if (! packageName.empty())
                                                                {
                                                            #line 17 "PrintScala.cpp"
  append(L"\n");
  append(L"package ");
                                                            #line 14 "PrintScala.cpp.template"
                                                                  print(packageName.c_str());
                                                            #line 22 "PrintScala.cpp"
  append(L"\n");
                                                            #line 16 "PrintScala.cpp.template"
                                                                }
                                                                if (performanceTest)
                                                                {
                                                            #line 28 "PrintScala.cpp"
  append(L"\n");
  append(L"import java.io.File");
                                                            #line 20 "PrintScala.cpp.template"
                                                                }
                                                                if (trace || (tree && main))
                                                                {
                                                            #line 35 "PrintScala.cpp"
  append(L"\n");
  append(L"import java.io.OutputStreamWriter\n");
  append(L"import java.io.Writer");
                                                            #line 25 "PrintScala.cpp.template"
                                                                }
                                                            #line 41 "PrintScala.cpp"
  append(L"\n");
  append(L"import collection.mutable.ArrayBuffer");
                                                            #line 27 "PrintScala.cpp.template"
                                                                if (useGlr)
                                                                {
                                                            #line 47 "PrintScala.cpp"
  append(L"\n");
  append(L"import collection.mutable.PriorityQueue");
                                                            #line 30 "PrintScala.cpp.template"
                                                                  if (tree)
                                                                  {
                                                            #line 53 "PrintScala.cpp"
  append(L"\n");
  append(L"import collection.mutable.Stack");
                                                            #line 33 "PrintScala.cpp.template"
                                                                  }
                                                                }
                                                                if (hasBacktracking)
                                                                {
                                                            #line 61 "PrintScala.cpp"
  append(L"\n");
  append(L"import collection.mutable.HashMap");
                                                            #line 38 "PrintScala.cpp.template"
                                                                }
                                                            #line 66 "PrintScala.cpp"
  append(L"\n");
  append(L"\n");
  append(L"class ");
                                                            #line 41 "PrintScala.cpp.template"
                                                                print(className.c_str());
                                                                if (! interfaceName.empty())
                                                                {
                                                            #line 74 "PrintScala.cpp"
  append(L" implements ");
                                                            #line 44 "PrintScala.cpp.template"
                                                                  print(interfaceName.c_str());
                                                                }
                                                            #line 79 "PrintScala.cpp"
  append(L" {\n");
                                                            #line 47 "PrintScala.cpp.template"
                                                              }
                                                              if (! hasProlog)
                                                              {
                                                            #line 85 "PrintScala.cpp"
  append(L"\n");
  append(L"  def this(string: String");
                                                            #line 51 "PrintScala.cpp.template"
                                                                if (noLexer)
                                                                {
                                                            #line 91 "PrintScala.cpp"
  append(L", l: ");
                                                            #line 53 "PrintScala.cpp.template"
                                                                  print(className.c_str());
                                                            #line 95 "PrintScala.cpp"
  append(L".Lexer");
                                                            #line 54 "PrintScala.cpp.template"
                                                                }
                                                                if (tree)
                                                                {
                                                            #line 101 "PrintScala.cpp"
  append(L", eh: ");
                                                            #line 57 "PrintScala.cpp.template"
                                                                  print(className.c_str());
                                                            #line 105 "PrintScala.cpp"
  append(L".");
                                                            #line 58 "PrintScala.cpp.template"
                                                                  if (isLrParser)
                                                                  {
                                                            #line 110 "PrintScala.cpp"
  append(L"BottomUp");
                                                            #line 60 "PrintScala.cpp.template"
                                                                  }
                                                            #line 114 "PrintScala.cpp"
  append(L"EventHandler");
                                                            #line 61 "PrintScala.cpp.template"
                                                                }
                                                            #line 118 "PrintScala.cpp"
  append(L") = {\n");
  append(L"    this()\n");
  append(L"    initialize(string");
                                                            #line 64 "PrintScala.cpp.template"
                                                                if (noLexer)
                                                                {
                                                            #line 125 "PrintScala.cpp"
  append(L", l");
                                                            #line 66 "PrintScala.cpp.template"
                                                                }
                                                                if (tree)
                                                                {
                                                            #line 131 "PrintScala.cpp"
  append(L", eh");
                                                            #line 69 "PrintScala.cpp.template"
                                                                }
                                                            #line 135 "PrintScala.cpp"
  append(L")\n");
  append(L"  }\n");
                                                            #line 72 "PrintScala.cpp.template"
                                                              }
                                                            }

                                                            void PrintScala::openStackNode()
                                                            {
                                                              increaseIndent();
                                                            #line 145 "PrintScala.cpp"
  append(L"\n");
  append(L"class StackNode(val state: Int, ");
                                                            #line 79 "PrintScala.cpp.template"
                                                              if (grammar->states->hasLookback)
                                                              {
                                                            #line 151 "PrintScala.cpp"
  append(L"val code: Int, ");
                                                            #line 81 "PrintScala.cpp.template"
                                                              }
                                                            #line 155 "PrintScala.cpp"
  append(L"val pos: Int, val link: StackNode) {\n");
  append(L"\n");
  append(L"  override def equals(other: Any): Boolean =\n");
  append(L"    other match {\n");
  append(L"      case other: StackNode =>\n");
  append(L"        var lhs = this\n");
  append(L"        var rhs = other\n");
  append(L"        while (lhs != null && rhs != null) {\n");
  append(L"          if (lhs eq rhs) return true\n");
  append(L"          if (lhs.state != rhs.state) return false");
                                                            #line 91 "PrintScala.cpp.template"
                                                              if (grammar->states->hasLookback)
                                                              {
                                                            #line 169 "PrintScala.cpp"
  append(L"\n");
  append(L"          if (lhs.code != rhs.code) return false");
                                                            #line 94 "PrintScala.cpp.template"
                                                              }
                                                            #line 174 "PrintScala.cpp"
  append(L"\n");
  append(L"          if (lhs.pos != rhs.pos) return false\n");
  append(L"          lhs = lhs.link\n");
  append(L"          rhs = rhs.link\n");
  append(L"        }\n");
  append(L"        lhs == rhs\n");
  append(L"      case _ => false\n");
  append(L"    }\n");
                                                            #line 103 "PrintScala.cpp.template"
                                                              increaseIndent();
                                                              beginPublic();
                                                            }

                                                            void PrintScala::closeStackNode()
                                                            {
                                                              beginNonpublic();
                                                              decreaseIndent();
                                                            #line 192 "PrintScala.cpp"
  append(L"\n");
  append(L"}\n");
                                                            #line 113 "PrintScala.cpp.template"
                                                              if (hasCustomCode)
                                                              {
                                                            #line 198 "PrintScala.cpp"
  append(L"\n");
  append(L"class DeferredCode(var link: DeferredCode, val codeId: Int, val b0: Int, val e0: Int) {\n");
  append(L"}\n");
                                                            #line 118 "PrintScala.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                            #line 206 "PrintScala.cpp"
  append(L"\n");
  append(L"abstract class DeferredEvent(var link: DeferredEvent, val name: String, val begin: Int, val end: Int) {");
                                                            #line 123 "PrintScala.cpp.template"
                                                                if (shiftAmbiguity)
                                                                {
                                                            #line 212 "PrintScala.cpp"
  append(L"\n");
  append(L"  val depth: Int = if (link == null) 1 else link.depth + 1");
                                                            #line 126 "PrintScala.cpp.template"
                                                                }
                                                            #line 217 "PrintScala.cpp"
  append(L"\n");
  append(L"\n");
  append(L"  def execute(eventHandler: BottomUpEventHandler): Unit\n");
  append(L"\n");
  append(L"  def release(eventHandler: BottomUpEventHandler): Unit = {\n");
  append(L"    var current = this\n");
  append(L"    var predecessor = current.link\n");
  append(L"    current.link = null\n");
  append(L"    while (predecessor != null) {\n");
  append(L"      var next = predecessor.link\n");
  append(L"      predecessor.link = current\n");
  append(L"      current = predecessor\n");
  append(L"      predecessor = next\n");
  append(L"    }\n");
  append(L"    while (current != null) {\n");
  append(L"      ");
                                                            #line 142 "PrintScala.cpp.template"
                                                                if (shiftAmbiguity)
                                                                {
                                                            #line 237 "PrintScala.cpp"
  append(L"if (eventHandler != null)\n");
  append(L"        ");
                                                            #line 145 "PrintScala.cpp.template"
                                                                }
                                                            #line 242 "PrintScala.cpp"
  append(L"current.execute(eventHandler)\n");
  append(L"      current = current.link\n");
  append(L"    }\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  def show(eventHandler: BottomUpEventHandler): Unit = {\n");
  append(L"    var stack = Stack[DeferredEvent]()\n");
  append(L"    var current = this\n");
  append(L"    while (current != null) {\n");
  append(L"      stack.push(current)\n");
  append(L"      current = current.link\n");
  append(L"    }\n");
  append(L"    while (! stack.isEmpty) {\n");
  append(L"      stack.pop().execute(eventHandler)\n");
  append(L"    }\n");
  append(L"  }\n");
  append(L"}\n");
  append(L"\n");
  append(L"private class TerminalEvent(link: DeferredEvent, name: String, begin: Int, end: Int) extends DeferredEvent(link, name, begin, end) {\n");
  append(L"  override def execute(eventHandler: BottomUpEventHandler): Unit = {\n");
  append(L"    eventHandler.terminal(name, begin, end)\n");
  append(L"  }\n");
  append(L"}\n");
  append(L"\n");
  append(L"private class NonterminalEvent(link: DeferredEvent, name: String, begin: Int, end: Int, count: Int) extends DeferredEvent(link, name, begin, end) {\n");
  append(L"  override def execute(eventHandler: BottomUpEventHandler): Unit = {\n");
  append(L"    eventHandler.nonterminal(name, begin, end, count)\n");
  append(L"  }\n");
  append(L"}\n");
                                                            #line 175 "PrintScala.cpp.template"
                                                                if (resolvesAmbiguity)
                                                                {
                                                            #line 275 "PrintScala.cpp"
  append(L"\n");
  append(L"\n");
  append(L"private class AmbiguityEvent(link: DeferredEvent, begin: Int, end: Int) extends DeferredEvent(link, null, begin, end) {\n");
  append(L"  override def execute(eventHandler: BottomUpEventHandler): Unit = {\n");
  append(L"    eventHandler.ambiguity(begin, end)\n");
  append(L"  }\n");
  append(L"}\n");
                                                            #line 184 "PrintScala.cpp.template"
                                                                }
                                                              }
                                                            #line 286 "PrintScala.cpp"
  append(L"\n");
  append(L"private val PARSING = 0\n");
  append(L"private val ACCEPTED = 1\n");
  append(L"private val ERROR = 2\n");
                                                            #line 190 "PrintScala.cpp.template"
                                                            }

                                                            void PrintScala::printGlrParseMethod()
                                                            {
                                                            #line 296 "PrintScala.cpp"
  append(L"\n");
  append(L"private def parse(target: Int, initialState: Int, ");
                                                            #line 195 "PrintScala.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 302 "PrintScala.cpp"
  append(L"eventHandler: ");
                                                            #line 198 "PrintScala.cpp.template"
                                                                print(className.c_str());
                                                            #line 306 "PrintScala.cpp"
  append(L".BottomUpEventHandler, ");
                                                            #line 200 "PrintScala.cpp.template"
                                                              }
                                                            #line 310 "PrintScala.cpp"
  append(L"t: ");
                                                            #line 201 "PrintScala.cpp.template"
                                                              print(className.c_str());
                                                            #line 314 "PrintScala.cpp"
  append(L".ParsingThread): ");
                                                            #line 203 "PrintScala.cpp.template"
                                                              print(className.c_str());
                                                            #line 318 "PrintScala.cpp"
  append(L".ParsingThread = {\n");
  append(L"  var thread = t\n");
  append(L"  val threads = thread.open(initialState");
                                                            #line 206 "PrintScala.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 325 "PrintScala.cpp"
  append(L", eventHandler");
                                                            #line 208 "PrintScala.cpp.template"
                                                              }
                                                            #line 329 "PrintScala.cpp"
  append(L", target)\n");
  append(L"  while (true) {\n");
  append(L"    thread = threads.dequeue()\n");
  append(L"    if (thread.accepted) {");
                                                            #line 212 "PrintScala.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 337 "PrintScala.cpp"
  append(L"\n");
  append(L"      var other: ");
                                                            #line 215 "PrintScala.cpp.template"
                                                                print(className.c_str());
                                                            #line 342 "PrintScala.cpp"
  append(L".ParsingThread = null\n");
  append(L"      while (! threads.isEmpty) {\n");
  append(L"        other = threads.dequeue()\n");
  append(L"        if (thread.e0 < other.e0) {\n");
  append(L"          thread = other\n");
  append(L"          other = null\n");
  append(L"        }\n");
  append(L"      }\n");
  append(L"      if (other != null)\n");
  append(L"        rejectAmbiguity(thread.stack.pos, thread.e0");
                                                            #line 225 "PrintScala.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 356 "PrintScala.cpp"
  append(L", thread.deferredEvent, other.deferredEvent");
                                                            #line 227 "PrintScala.cpp.template"
                                                                }
                                                            #line 360 "PrintScala.cpp"
  append(L")");
                                                            #line 228 "PrintScala.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 366 "PrintScala.cpp"
  append(L"\n");
  append(L"      while (! threads.isEmpty) {\n");
  append(L"        val other = threads.dequeue()\n");
  append(L"        thread = if (thread.e0 < other.e0) other else resolve(thread, other)\n");
  append(L"      }");
                                                            #line 235 "PrintScala.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                            #line 376 "PrintScala.cpp"
  append(L"\n");
  append(L"      if (thread.deferredEvent != null) {\n");
  append(L"        thread.deferredEvent.release(eventHandler)\n");
  append(L"        thread.deferredEvent = null\n");
  append(L"      }");
                                                            #line 242 "PrintScala.cpp.template"
                                                              }
                                                              if (hasCustomCode)
                                                              {
                                                            #line 386 "PrintScala.cpp"
  append(L"\n");
  append(L"      thread.executeDeferredCode");
                                                            #line 246 "PrintScala.cpp.template"
                                                              }
                                                            #line 391 "PrintScala.cpp"
  append(L"\n");
  append(L"      return thread\n");
  append(L"    }\n");
  append(L"\n");
                                                            #line 251 "PrintScala.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 399 "PrintScala.cpp"
  append(L"    if (! threads.isEmpty) {\n");
  append(L"      if (threads.head == thread)\n");
  append(L"        rejectAmbiguity(thread.stack.pos, thread.e0");
                                                            #line 255 "PrintScala.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 406 "PrintScala.cpp"
  append(L", thread.deferredEvent, threads.head.deferredEvent");
                                                            #line 257 "PrintScala.cpp.template"
                                                                }
                                                            #line 410 "PrintScala.cpp"
  append(L")\n");
  append(L"    }");
                                                            #line 259 "PrintScala.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 417 "PrintScala.cpp"
  append(L"    while (! threads.isEmpty && threads.head == thread)\n");
  append(L"      thread = resolve(thread, threads.dequeue())");
                                                            #line 263 "PrintScala.cpp.template"
                                                              }
                                                              if (tree || hasCustomCode)
                                                              {
                                                                if (rejectsAmbiguity())
                                                                {
                                                            #line 426 "PrintScala.cpp"
  append(L"\n");
  append(L"    else {");
                                                            #line 269 "PrintScala.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 433 "PrintScala.cpp"
  append(L"\n");
  append(L"    if (threads.isEmpty) {");
                                                            #line 273 "PrintScala.cpp.template"
                                                                }
                                                                if (tree)
                                                                {
                                                            #line 440 "PrintScala.cpp"
  append(L"\n");
  append(L"      if (thread.deferredEvent != null) {\n");
  append(L"        thread.deferredEvent.release(eventHandler)\n");
  append(L"        thread.deferredEvent = null\n");
  append(L"      }");
                                                            #line 280 "PrintScala.cpp.template"
                                                                }
                                                                if (hasCustomCode)
                                                                {
                                                            #line 450 "PrintScala.cpp"
  append(L"\n");
  append(L"      thread.executeDeferredCode");
                                                            #line 284 "PrintScala.cpp.template"
                                                                }
                                                            #line 455 "PrintScala.cpp"
  append(L"\n");
  append(L"    }");
                                                            #line 286 "PrintScala.cpp.template"
                                                              }
                                                            #line 460 "PrintScala.cpp"
  append(L"\n");
  append(L"\n");
  append(L"    var status = ");
                                                            #line 289 "PrintScala.cpp.template"
                                                              print(className.c_str());
                                                            #line 466 "PrintScala.cpp"
  append(L".PARSING\n");
  append(L"    var continue = true\n");
  append(L"    while (continue) {\n");
  append(L"      status = thread.parse\n");
  append(L"      continue = status == ");
                                                            #line 294 "PrintScala.cpp.template"
                                                              print(className.c_str());
                                                            #line 474 "PrintScala.cpp"
  append(L".PARSING && threads.isEmpty\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    if (status != ");
                                                            #line 298 "PrintScala.cpp.template"
                                                              print(className.c_str());
                                                            #line 481 "PrintScala.cpp"
  append(L".ERROR) {\n");
  append(L"      threads += thread\n");
  append(L"    }\n");
  append(L"    else if (threads.isEmpty) {\n");
  append(L"      throw new ");
                                                            #line 303 "PrintScala.cpp.template"
                                                              print(className.c_str());
                                                            #line 489 "PrintScala.cpp"
  append(L".ParseException(thread.b1,\n");
  append(L"                ");
                                                            #line 305 "PrintScala.cpp.template"
                                                              print(className.size(), L" ");
                                                            #line 494 "PrintScala.cpp"
  append(L"                thread.e1,\n");
  append(L"                ");
                                                            #line 307 "PrintScala.cpp.template"
                                                              print(className.size(), L" ");
                                                            #line 499 "PrintScala.cpp"
  append(L"                ");
                                                            #line 308 "PrintScala.cpp.template"
                                                              print(className.c_str());
                                                            #line 503 "PrintScala.cpp"
  append(L".TOKENSET(thread.state) + 1,\n");
  append(L"                ");
                                                            #line 310 "PrintScala.cpp.template"
                                                              print(className.size(), L" ");
                                                            #line 508 "PrintScala.cpp"
  append(L"                thread.l1,\n");
  append(L"                ");
                                                            #line 312 "PrintScala.cpp.template"
                                                              print(className.size(), L" ");
                                                            #line 513 "PrintScala.cpp"
  append(L"                -1\n");
  append(L"                ");
                                                            #line 314 "PrintScala.cpp.template"
                                                              print(className.size(), L" ");
                                                            #line 518 "PrintScala.cpp"
  append(L"               )\n");
  append(L"    }\n");
  append(L"  }\n");
  append(L"  thread\n");
  append(L"}\n");
                                                            #line 320 "PrintScala.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 527 "PrintScala.cpp"
  append(L"\n");
  append(L"def rejectAmbiguity(begin: Int, end: Int");
                                                            #line 323 "PrintScala.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 533 "PrintScala.cpp"
  append(L", first: ");
                                                            #line 325 "PrintScala.cpp.template"
                                                                  print(className.c_str());
                                                            #line 537 "PrintScala.cpp"
  append(L".DeferredEvent, second: ");
                                                            #line 326 "PrintScala.cpp.template"
                                                                  print(className.c_str());
                                                            #line 541 "PrintScala.cpp"
  append(L".DeferredEvent");
                                                            #line 327 "PrintScala.cpp.template"
                                                                }
                                                            #line 545 "PrintScala.cpp"
  append(L"): Unit = {");
                                                            #line 328 "PrintScala.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 550 "PrintScala.cpp"
  append(L"\n");
  append(L"  val treeBuilder = new ");
                                                            #line 331 "PrintScala.cpp.template"
                                                                  print(className.c_str());
                                                            #line 555 "PrintScala.cpp"
  append(L".ParseTreeBuilder\n");
  append(L"  treeBuilder.reset(input)\n");
  append(L"  second.show(treeBuilder)\n");
  append(L"  treeBuilder.nonterminal(\"ALTERNATIVE\", treeBuilder.stack(0).begin, treeBuilder.stack(treeBuilder.top).end, treeBuilder.top + 1)\n");
  append(L"  val secondTree = treeBuilder.pop(1)(0)\n");
  append(L"  first.show(treeBuilder)\n");
  append(L"  treeBuilder.nonterminal(\"ALTERNATIVE\", treeBuilder.stack(0).begin, treeBuilder.stack(treeBuilder.top).end, treeBuilder.top + 1)\n");
  append(L"  treeBuilder.push(secondTree)\n");
  append(L"  treeBuilder.nonterminal(\"AMBIGUOUS\", treeBuilder.stack(0).begin, treeBuilder.stack(treeBuilder.top).end, 2)");
                                                            #line 341 "PrintScala.cpp.template"
                                                                }
                                                            #line 567 "PrintScala.cpp"
  append(L"\n");
  append(L"  val exception = new ");
                                                            #line 343 "PrintScala.cpp.template"
                                                                print(className.c_str());
                                                            #line 572 "PrintScala.cpp"
  append(L".ParseException(begin, end, -1, -1, -1)\n");
  append(L"  exception.setAmbiguousInput(");
                                                            #line 345 "PrintScala.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 578 "PrintScala.cpp"
  append(L"treeBuilder");
                                                            #line 347 "PrintScala.cpp.template"
                                                                }
                                                            #line 582 "PrintScala.cpp"
  append(L")\n");
  append(L"  throw exception\n");
  append(L"}");
                                                            #line 350 "PrintScala.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 590 "PrintScala.cpp"
  append(L"\n");
  append(L"def resolve(thread: ");
                                                            #line 354 "PrintScala.cpp.template"
                                                                print(className.c_str());
                                                            #line 595 "PrintScala.cpp"
  append(L".ParsingThread, other: ");
                                                            #line 355 "PrintScala.cpp.template"
                                                                print(className.c_str());
                                                            #line 599 "PrintScala.cpp"
  append(L".ParsingThread): ");
                                                            #line 356 "PrintScala.cpp.template"
                                                                print(className.c_str());
                                                            #line 603 "PrintScala.cpp"
  append(L".ParsingThread = {");
                                                            #line 358 "PrintScala.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 608 "PrintScala.cpp"
  append(L"\n");
  append(L"  var a = thread.stack\n");
  append(L"  var b = other.stack\n");
  append(L"  var begin = a.pos\n");
  append(L"  while ((a ne b) && a != null && b != null) {\n");
  append(L"    begin = a.pos\n");
  append(L"    a = a.link\n");
  append(L"    b = b.link\n");
  append(L"  }");
                                                            #line 368 "PrintScala.cpp.template"
                                                                }
                                                            #line 620 "PrintScala.cpp"
  append(L"\n");
                                                            #line 370 "PrintScala.cpp.template"
                                                                if (shiftAmbiguity)
                                                                {
                                                            #line 625 "PrintScala.cpp"
  append(L"\n");
  append(L"  var ea = thread.deferredEvent\n");
  append(L"  var eb = other.deferredEvent\n");
  append(L"  var ua: ");
                                                            #line 375 "PrintScala.cpp.template"
                                                                  print(className.c_str());
                                                            #line 632 "PrintScala.cpp"
  append(L".DeferredEvent = null\n");
  append(L"  var ub: ");
                                                            #line 377 "PrintScala.cpp.template"
                                                                  print(className.c_str());
                                                            #line 637 "PrintScala.cpp"
  append(L".DeferredEvent = null\n");
  append(L"  while (ea != eb) {\n");
  append(L"    if ((if (ea == null) 0 else ea.depth) >= (if (eb == null) 0 else eb.depth)) {\n");
  append(L"      ua = ea\n");
  append(L"      ea = ea.link\n");
  append(L"    }\n");
  append(L"    else {\n");
  append(L"      ub = eb\n");
  append(L"      eb = eb.link\n");
  append(L"    }\n");
  append(L"  }\n");
  append(L"  val sa = ua != null && ua.isInstanceOf[");
                                                            #line 389 "PrintScala.cpp.template"
                                                                  print(className.c_str());
                                                            #line 652 "PrintScala.cpp"
  append(L".TerminalEvent]\n");
  append(L"  val sb = ub != null && ub.isInstanceOf[");
                                                            #line 391 "PrintScala.cpp.template"
                                                                  print(className.c_str());
                                                            #line 657 "PrintScala.cpp"
  append(L".TerminalEvent]\n");
  append(L"  val result = if (sa != sb) (if (sb) other else thread) else if (other.eventCount < thread.eventCount) other else thread");
                                                            #line 394 "PrintScala.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 664 "PrintScala.cpp"
  append(L"\n");
  append(L"  val result = if (other.eventCount < thread.eventCount) other else thread");
                                                            #line 399 "PrintScala.cpp.template"
                                                                }
                                                                if (tree)
                                                                {
                                                            #line 671 "PrintScala.cpp"
  append(L"\n");
  append(L"  result.addAmbiguity(begin, result.e0)");
                                                            #line 403 "PrintScala.cpp.template"
                                                                }
                                                            #line 676 "PrintScala.cpp"
  append(L"\n");
  append(L"  result\n");
  append(L"}");
                                                            #line 406 "PrintScala.cpp.template"
                                                              }
                                                            }

                                                            void PrintScala::openThread()
                                                            {
                                                            #line 686 "PrintScala.cpp"
  append(L"\n");
  append(L"class ParsingThread extends Ordered[ParsingThread] {\n");
  append(L"  var parser: ");
                                                            #line 413 "PrintScala.cpp.template"
                                                              print(className.c_str());
                                                            #line 692 "PrintScala.cpp"
  append(L" = null\n");
  append(L"  var threads: PriorityQueue[ParsingThread] = null\n");
  append(L"  var accepted: Boolean = false\n");
  append(L"  var stack: StackNode = null\n");
  append(L"  var state = 0\n");
  append(L"  var action = 0\n");
  append(L"  var target = 0");
                                                            #line 420 "PrintScala.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 703 "PrintScala.cpp"
  append(L"\n");
  append(L"  var deferredEvent: DeferredEvent = null");
                                                            #line 423 "PrintScala.cpp.template"
                                                              }
                                                              if (hasCustomCode)
                                                              {
                                                            #line 710 "PrintScala.cpp"
  append(L"\n");
  append(L"  var deferredCode: DeferredCode = null");
                                                            #line 427 "PrintScala.cpp.template"
                                                              }
                                                            #line 715 "PrintScala.cpp"
  append(L"\n");
  append(L"  var id = 0");
                                                            #line 429 "PrintScala.cpp.template"
                                                              if (resolvesAmbiguity)
                                                              {
                                                            #line 721 "PrintScala.cpp"
  append(L"\n");
  append(L"  var eventCount = 0");
                                                            #line 432 "PrintScala.cpp.template"
                                                              }
                                                            #line 726 "PrintScala.cpp"
  append(L"\n");
  append(L"\n");
  append(L"  def open(initialState: Int");
                                                            #line 435 "PrintScala.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 733 "PrintScala.cpp"
  append(L", eh: BottomUpEventHandler");
                                                            #line 437 "PrintScala.cpp.template"
                                                              }
                                                            #line 737 "PrintScala.cpp"
  append(L", t: Int): PriorityQueue[ParsingThread] = {\n");
  append(L"    accepted = false");
                                                            #line 439 "PrintScala.cpp.template"
                                                              if (resolvesAmbiguity)
                                                              {
                                                            #line 743 "PrintScala.cpp"
  append(L"\n");
  append(L"    eventCount = 0");
                                                            #line 442 "PrintScala.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                            #line 750 "PrintScala.cpp"
  append(L"\n");
  append(L"    eventHandler = eh\n");
  append(L"    if (eventHandler != null) {\n");
  append(L"      eventHandler.reset(parser.input)\n");
  append(L"    }\n");
  append(L"    deferredEvent = null");
                                                            #line 450 "PrintScala.cpp.template"
                                                              }
                                                            #line 759 "PrintScala.cpp"
  append(L"\n");
  append(L"    target = t");
                                                            #line 452 "PrintScala.cpp.template"
                                                              if (hasCustomCode && useGlr)
                                                              {
                                                            #line 765 "PrintScala.cpp"
  append(L"\n");
  append(L"    deferredCode = null");
                                                            #line 455 "PrintScala.cpp.template"
                                                              }
                                                            #line 770 "PrintScala.cpp"
  append(L"\n");
  append(L"    stack = new StackNode(-1, ");
                                                            #line 457 "PrintScala.cpp.template"
                                                              if (grammar->states->hasLookback)
                                                              {
                                                            #line 776 "PrintScala.cpp"
  append(L"0, ");
                                                            #line 459 "PrintScala.cpp.template"
                                                              }
                                                            #line 780 "PrintScala.cpp"
  append(L"e0, null)\n");
  append(L"    state = initialState\n");
  append(L"    action = predict(initialState)");
                                                            #line 462 "PrintScala.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 787 "PrintScala.cpp"
  append(L"\n");
  append(L"    bw = e0\n");
  append(L"    bs = e0\n");
  append(L"    es = e0");
                                                            #line 467 "PrintScala.cpp.template"
                                                              }
                                                            #line 794 "PrintScala.cpp"
  append(L"\n");
  append(L"    threads = PriorityQueue()\n");
  append(L"    threads += this\n");
  append(L"    threads\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  def copy(other: ParsingThread, action: Int): ParsingThread = {\n");
  append(L"    this.action = action\n");
  append(L"    accepted = other.accepted\n");
  append(L"    parser = other.parser");
                                                            #line 477 "PrintScala.cpp.template"
                                                              if (resolvesAmbiguity)
                                                              {
                                                            #line 808 "PrintScala.cpp"
  append(L"\n");
  append(L"    eventCount = other.eventCount");
                                                            #line 480 "PrintScala.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                            #line 815 "PrintScala.cpp"
  append(L"\n");
  append(L"    bs = other.bs\n");
  append(L"    bw = other.bw\n");
  append(L"    es = other.es\n");
  append(L"    eventHandler = other.eventHandler\n");
  append(L"    deferredEvent = other.deferredEvent");
                                                            #line 488 "PrintScala.cpp.template"
                                                              }
                                                            #line 824 "PrintScala.cpp"
  append(L"\n");
  append(L"    target = other.target");
                                                            #line 490 "PrintScala.cpp.template"
                                                              if (hasCustomCode)
                                                              {
                                                            #line 830 "PrintScala.cpp"
  append(L"\n");
  append(L"    deferredCode = other.deferredCode");
                                                            #line 493 "PrintScala.cpp.template"
                                                              }
                                                            #line 835 "PrintScala.cpp"
  append(L"\n");
  append(L"    parser.maxId += 1\n");
  append(L"    id = parser.maxId\n");
  append(L"    threads = other.threads\n");
  append(L"    state = other.state\n");
  append(L"    stack = other.stack\n");
  append(L"    b0 = other.b0\n");
  append(L"    e0 = other.e0");
                                                            #line 501 "PrintScala.cpp.template"
                                                              for (size_t i = 1; i <= grammar->k; ++i)
                                                              {
                                                                const wchar_t *iString = format.toString<wchar_t>(i);
                                                            #line 848 "PrintScala.cpp"
  append(L"\n");
  append(L"    l");
                                                            #line 505 "PrintScala.cpp.template"
                                                                print(iString);
                                                            #line 853 "PrintScala.cpp"
  append(L" = other.l");
                                                            #line 506 "PrintScala.cpp.template"
                                                                print(iString);
                                                            #line 857 "PrintScala.cpp"
  append(L"\n");
  append(L"    b");
                                                            #line 508 "PrintScala.cpp.template"
                                                                print(iString);
                                                            #line 862 "PrintScala.cpp"
  append(L" = other.b");
                                                            #line 509 "PrintScala.cpp.template"
                                                                print(iString);
                                                            #line 866 "PrintScala.cpp"
  append(L"\n");
  append(L"    e");
                                                            #line 511 "PrintScala.cpp.template"
                                                                print(iString);
                                                            #line 871 "PrintScala.cpp"
  append(L" = other.e");
                                                            #line 512 "PrintScala.cpp.template"
                                                                print(iString);
                                                              }
                                                            #line 876 "PrintScala.cpp"
  append(L"\n");
  append(L"    end = other.end\n");
  append(L"    this\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  override def compare(other: ParsingThread): Int = {\n");
  append(L"    var comp = 0\n");
  append(L"    if (accepted != other.accepted) {\n");
  append(L"      comp = if (accepted) -1 else 1\n");
  append(L"    }\n");
  append(L"    else {\n");
  append(L"      comp = other.e0 - e0\n");
  append(L"      if (comp == 0)\n");
  append(L"        comp = other.id - id\n");
  append(L"    }\n");
  append(L"    comp\n");
  append(L"  }\n");
  append(L"\n");
                                                            #line 532 "PrintScala.cpp.template"
                                                              if (resolvesAmbiguity && tree)
                                                              {
                                                            #line 898 "PrintScala.cpp"
  append(L"\n");
  append(L"  def addAmbiguity(begin: Int, end: Int): Unit = {\n");
  append(L"    if (eventHandler != null)\n");
  append(L"      deferredEvent = new AmbiguityEvent(deferredEvent, begin, end)\n");
  append(L"  }\n");
  append(L"\n");
                                                            #line 540 "PrintScala.cpp.template"
                                                              }
                                                            #line 907 "PrintScala.cpp"
  append(L"  override def equals(other: Any): Boolean =\n");
  append(L"    other match {\n");
  append(L"      case other: ParsingThread =>\n");
  append(L"        if (accepted != other.accepted) false\n");
  append(L"        else if (b1 != other.b1) false\n");
  append(L"        else if (e1 != other.e1) false\n");
  append(L"        else if (l1 != other.l1) false\n");
  append(L"        else if (state != other.state) false\n");
  append(L"        else if (action != other.action) false\n");
  append(L"        else if (stack != other.stack) false\n");
  append(L"        else true\n");
  append(L"      case _ => false\n");
  append(L"    }\n");
  append(L"\n");
  append(L"  def parse : Int = {");
                                                            #line 555 "PrintScala.cpp.template"
                                                              increaseIndent();
                                                              beginPublic();
                                                            }

                                                            void PrintScala::printFlush(int i, bool withinThread)
                                                            {
                                                              increaseIndent(i);
                                                              if (trace)
                                                              {
                                                            #line 933 "PrintScala.cpp"
  append(L"\n");
                                                            #line 565 "PrintScala.cpp.template"
                                                                if (useGlr && withinThread)
                                                                {
                                                            #line 938 "PrintScala.cpp"
  append(L"parser.");
                                                            #line 567 "PrintScala.cpp.template"
                                                                }
                                                            #line 942 "PrintScala.cpp"
  append(L"flushTrace");
                                                            #line 568 "PrintScala.cpp.template"
                                                              }
                                                              decreaseIndent(i);
                                                            }

                                                            void PrintScala::openMethod(const wchar_t *type,
                                                                                        const wchar_t *prefix,
                                                                                        const wchar_t *name,
                                                                                        const wchar_t *args,
                                                                                        bool constant,
                                                                                        const wchar_t *clazz)
                                                            {
                                                            #line 956 "PrintScala.cpp"
  append(L"\n");
                                                            #line 580 "PrintScala.cpp.template"
                                                              print(visibility);
                                                            #line 960 "PrintScala.cpp"
  append(L"def ");
                                                            #line 581 "PrintScala.cpp.template"
                                                              print(name);
                                                              if (args[0])
                                                              {
                                                            #line 966 "PrintScala.cpp"
  append(L"(");
                                                            #line 584 "PrintScala.cpp.template"
                                                                printArgs(args);
                                                            #line 970 "PrintScala.cpp"
  append(L")");
                                                            #line 586 "PrintScala.cpp.template"
                                                              }
                                                              if (wcscmp(type, voidType()) == 0)
                                                              {
                                                                type = L"Unit ";
                                                              }
                                                            #line 978 "PrintScala.cpp"
  append(L": ");
                                                            #line 591 "PrintScala.cpp.template"
                                                              print(type);
                                                            #line 982 "PrintScala.cpp"
  append(L"=");
                                                            #line 592 "PrintScala.cpp.template"
                                                            }

                                                            void PrintScala::privateVars()
                                                            {
                                                              if (trace)
                                                              {
                                                            #line 991 "PrintScala.cpp"
  append(L"\n");
  append(L"  def lookaheadString: String = {\n");
  append(L"    var result = \"\"\n");
  append(L"    if (l1 > 0) {\n");
  append(L"      result += ");
                                                            #line 602 "PrintScala.cpp.template"
                                                                print(staticPrefix());
                                                            #line 999 "PrintScala.cpp"
  append(L"TOKEN(l1)");
                                                            #line 603 "PrintScala.cpp.template"
                                                                for (size_t i = 2; i <= grammar->k; ++i)
                                                                {
                                                            #line 1004 "PrintScala.cpp"
  append(L"\n");
  append(L"      if (l");
                                                            #line 606 "PrintScala.cpp.template"
                                                                  print(format.toString<wchar_t>(i));
                                                            #line 1009 "PrintScala.cpp"
  append(L" > 0) {\n");
  append(L"        result += \" \" + ");
                                                            #line 608 "PrintScala.cpp.template"
                                                                  print(staticPrefix());
                                                            #line 1014 "PrintScala.cpp"
  append(L"TOKEN(l");
                                                            #line 609 "PrintScala.cpp.template"
                                                                  print(format.toString<wchar_t>(i));
                                                            #line 1018 "PrintScala.cpp"
  append(L")");
                                                            #line 610 "PrintScala.cpp.template"
                                                                  increaseIndent();
                                                                }
                                                                for (size_t i = 2; i <= grammar->k; ++i)
                                                                {
                                                                  decreaseIndent();
                                                            #line 1026 "PrintScala.cpp"
  append(L"\n");
  append(L"      }");
                                                            #line 616 "PrintScala.cpp.template"
                                                                }
                                                            #line 1031 "PrintScala.cpp"
  append(L"\n");
  append(L"    }\n");
  append(L"    result\n");
  append(L"  }\n");
                                                            #line 621 "PrintScala.cpp.template"
                                                              }

                                                              if (grammar->k > 1 || memoization || ! grammar->decisionPoints.empty())
                                                              {
                                                            #line 1041 "PrintScala.cpp"
  append(L"\n");
  append(L"  var lk = 0");
                                                            #line 626 "PrintScala.cpp.template"
                                                              }
                                                            #line 1046 "PrintScala.cpp"
  append(L"\n");
  append(L"  var b0 = 0\n");
  append(L"  var e0 = 0");
                                                            #line 629 "PrintScala.cpp.template"
                                                              for (size_t k = 1; k <= grammar->k; ++k)
                                                              {
                                                                Format format;
                                                                wchar_t *asString = format.toString<wchar_t>(k);
                                                            #line 1055 "PrintScala.cpp"
  append(L"\n");
  append(L"  var l");
                                                            #line 634 "PrintScala.cpp.template"
                                                                print(asString);
                                                            #line 1060 "PrintScala.cpp"
  append(L" = 0\n");
  append(L"  var b");
                                                            #line 636 "PrintScala.cpp.template"
                                                                print(asString);
                                                            #line 1065 "PrintScala.cpp"
  append(L" = 0\n");
  append(L"  var e");
                                                            #line 638 "PrintScala.cpp.template"
                                                                print(asString);
                                                            #line 1070 "PrintScala.cpp"
  append(L" = 0");
                                                            #line 639 "PrintScala.cpp.template"
                                                              }
                                                              if (tree && useGlr)
                                                              {
                                                            #line 1076 "PrintScala.cpp"
  append(L"\n");
  append(L"  var bw = 0\n");
  append(L"  var bs = 0\n");
  append(L"  var es = 0");
                                                            #line 645 "PrintScala.cpp.template"
                                                              }
                                                              if (hasBacktracking)
                                                              {
                                                            #line 1085 "PrintScala.cpp"
  append(L"\n");
  append(L"  var bx = 0\n");
  append(L"  var ex = 0\n");
  append(L"  var sx = 0\n");
  append(L"  var lx = 0\n");
  append(L"  var tx = 0");
                                                            #line 653 "PrintScala.cpp.template"
                                                              }
                                                              if (isLrParser && ! useGlr)
                                                              {
                                                            #line 1096 "PrintScala.cpp"
  append(L"\n");
  append(L"  var iStack = new Array[Int](");
                                                            #line 657 "PrintScala.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 1102 "PrintScala.cpp"
  append(L"192");
                                                            #line 659 "PrintScala.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1108 "PrintScala.cpp"
  append(L"128");
                                                            #line 662 "PrintScala.cpp.template"
                                                                }
                                                            #line 1112 "PrintScala.cpp"
  append(L")\n");
  append(L"  var top = -1");
                                                            #line 664 "PrintScala.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                            #line 1119 "PrintScala.cpp"
  append(L"\n");
  append(L"  var eventHandler: ");
                                                            #line 668 "PrintScala.cpp.template"
                                                                print(className.c_str());
                                                            #line 1124 "PrintScala.cpp"
  append(L".");
                                                            #line 669 "PrintScala.cpp.template"
                                                                if (isLrParser)
                                                                {
                                                            #line 1129 "PrintScala.cpp"
  append(L"BottomUp");
                                                            #line 671 "PrintScala.cpp.template"
                                                                }
                                                            #line 1133 "PrintScala.cpp"
  append(L"EventHandler = null");
                                                            #line 672 "PrintScala.cpp.template"
                                                              }
                                                              if (memoization)
                                                              {
                                                            #line 1139 "PrintScala.cpp"
  append(L"\n");
  append(L"  val memo = new HashMap[Int, Int]");
                                                            #line 676 "PrintScala.cpp.template"
                                                                if (grammar->noThrow)
                                                                {
                                                            #line 1145 "PrintScala.cpp"
  append(L"\n");
  append(L"  var viable = false");
                                                            #line 679 "PrintScala.cpp.template"
                                                                }
                                                              }
                                                              if (useGlr)
                                                              {
                                                            #line 1153 "PrintScala.cpp"
  append(L"\n");
  append(L"}\n");
                                                            #line 685 "PrintScala.cpp.template"
                                                              }
                                                            }

                                                            void PrintScala::printSimpleMain()
                                                            {
                                                            #line 1162 "PrintScala.cpp"
  append(L"\n");
  append(L"  def main(args: Array[String]): Unit = {\n");
  append(L"    if (args.length == 0) {\n");
  append(L"      println(\"Usage: scala ");
                                                            #line 693 "PrintScala.cpp.template"
                                                              print(className.c_str());
                                                              if (tree)
                                                              {
                                                            #line 1171 "PrintScala.cpp"
  append(L" [-i]");
                                                            #line 696 "PrintScala.cpp.template"
                                                              }
                                                            #line 1175 "PrintScala.cpp"
  append(L" INPUT...\")\n");
  append(L"      println()\n");
  append(L"      println(\"  parse INPUT, which is either a filename or literal text enclosed in curly braces\\n\")");
                                                            #line 700 "PrintScala.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 1182 "PrintScala.cpp"
  append(L"\n");
  append(L"      println()\n");
  append(L"      println(\"  Option:\")\n");
  append(L"      println(\"    -i     indented parse tree\")");
                                                            #line 705 "PrintScala.cpp.template"
                                                              }
                                                            #line 1189 "PrintScala.cpp"
  append(L"\n");
  append(L"    }\n");
  append(L"    else {\n");
  append(L"      var indent = false\n");
  append(L"      for (arg <- args) {");
                                                            #line 710 "PrintScala.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 1198 "PrintScala.cpp"
  append(L"\n");
  append(L"        if (arg == \"-i\") {\n");
  append(L"          indent = true\n");
  append(L"        }\n");
  append(L"        else {\n");
  append(L"          val w = new OutputStreamWriter(System.out, \"utf-8\")\n");
  append(L"          val s = new XmlSerializer(w, indent)");
                                                            #line 718 "PrintScala.cpp.template"
                                                                if (isLrParser)
                                                                {
                                                            #line 1209 "PrintScala.cpp"
  append(L"\n");
  append(L"          val b = new ParseTreeBuilder");
                                                            #line 721 "PrintScala.cpp.template"
                                                                }
                                                                increaseIndent();
                                                              }
                                                            #line 1216 "PrintScala.cpp"
  append(L"\n");
  append(L"        val parser = new ");
                                                            #line 725 "PrintScala.cpp.template"
                                                              print(className.c_str());
                                                            #line 1221 "PrintScala.cpp"
  append(L"(read(arg)");
                                                            #line 726 "PrintScala.cpp.template"
                                                              if (tree)
                                                              {
                                                                if (isLrParser)
                                                                {
                                                            #line 1228 "PrintScala.cpp"
  append(L", b");
                                                            #line 730 "PrintScala.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1234 "PrintScala.cpp"
  append(L", s");
                                                            #line 733 "PrintScala.cpp.template"
                                                                }
                                                              }
                                                            #line 1239 "PrintScala.cpp"
  append(L")\n");
  append(L"        try {");
                                                            #line 736 "PrintScala.cpp.template"
                                                              if (trace)
                                                              {
                                                            #line 1245 "PrintScala.cpp"
  append(L"\n");
  append(L"          parser.writeTrace(\"<?xml version=\\\"1.0\\\" encoding=\\\"UTF-8\\\"?\" + \">\\n<trace>\\n\")");
                                                            #line 740 "PrintScala.cpp.template"
                                                              }
                                                            #line 1250 "PrintScala.cpp"
  append(L"\n");
  append(L"          parser.");
                                                            #line 742 "PrintScala.cpp.template"
                                                              print(methodPrefixParse);
                                                              print(Format::acceptableName<WString>(grammar->startSymbol()->name).c_str());
                                                              if (trace)
                                                              {
                                                            #line 1258 "PrintScala.cpp"
  append(L"\n");
  append(L"          parser.writeTrace(\"</trace>\\n\")");
                                                            #line 747 "PrintScala.cpp.template"
                                                              }
                                                              if (tree && isLrParser)
                                                              {
                                                            #line 1265 "PrintScala.cpp"
  append(L"\n");
  append(L"          b.serialize(s)");
                                                            #line 751 "PrintScala.cpp.template"
                                                              }
                                                            #line 1270 "PrintScala.cpp"
  append(L"\n");
  append(L"        }\n");
  append(L"        catch {\n");
  append(L"          case pe: ParseException =>");
                                                            #line 755 "PrintScala.cpp.template"
                                                              if (rejectsAmbiguity() && tree)
                                                              {
                                                            #line 1278 "PrintScala.cpp"
  append(L"\n");
  append(L"            if (pe.isAmbiguousInput) {\n");
  append(L"              pe.serialize(s)\n");
  append(L"              w.write(\"\\n\")\n");
  append(L"              w.flush()\n");
  append(L"            }");
                                                            #line 762 "PrintScala.cpp.template"
                                                              }
                                                            #line 1287 "PrintScala.cpp"
  append(L"\n");
  append(L"            throw new RuntimeException(\"ParseException while processing \" + arg + \":\\n\" + parser.getErrorMessage(pe))\n");
  append(L"        }");
                                                            #line 765 "PrintScala.cpp.template"
                                                              if (tree || trace)
                                                              {
                                                            #line 1294 "PrintScala.cpp"
  append(L"\n");
  append(L"        finally {");
                                                            #line 768 "PrintScala.cpp.template"
                                                              }
                                                              if (trace)
                                                              {
                                                            #line 1301 "PrintScala.cpp"
  append(L"\n");
  append(L"          parser.flushTrace");
                                                            #line 772 "PrintScala.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                            #line 1308 "PrintScala.cpp"
  append(L"\n");
  append(L"          w.close");
                                                            #line 776 "PrintScala.cpp.template"
                                                              }
                                                              if (tree || trace)
                                                              {
                                                            #line 1315 "PrintScala.cpp"
  append(L"\n");
  append(L"        }");
                                                            #line 780 "PrintScala.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                            #line 1322 "PrintScala.cpp"
  append(L"\n");
  append(L"      }");
                                                            #line 784 "PrintScala.cpp.template"
                                                                decreaseIndent();
                                                              }
                                                            #line 1328 "PrintScala.cpp"
  append(L"\n");
  append(L"      }\n");
  append(L"    }\n");
  append(L"  }\n");
                                                            #line 790 "PrintScala.cpp.template"
                                                            }

                                                            void PrintScala::printFileProcessor()
                                                            {
                                                            #line 1338 "PrintScala.cpp"
  append(L"\n");
  append(L"  private class ParseJob(val name: String, val input: String) {");
                                                            #line 796 "PrintScala.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 1344 "PrintScala.cpp"
  append(L"\n");
  append(L"    var contentCounter = new ContentCounter");
                                                            #line 799 "PrintScala.cpp.template"
                                                              }
                                                              if (isLrParser)
                                                              {
                                                            #line 1351 "PrintScala.cpp"
  append(L"\n");
  append(L"    var parseTreeBuilder = new ParseTreeBuilder");
                                                            #line 803 "PrintScala.cpp.template"
                                                              }
                                                            #line 1356 "PrintScala.cpp"
  append(L"\n");
  append(L"    var parser = new ");
                                                            #line 805 "PrintScala.cpp.template"
                                                              print(className.c_str());
                                                            #line 1361 "PrintScala.cpp"
  append(L"(input");
                                                            #line 806 "PrintScala.cpp.template"
                                                              if (noLexer)
                                                              {
                                                            #line 1366 "PrintScala.cpp"
  append(L", null");
                                                            #line 808 "PrintScala.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                                if (isLrParser)
                                                                {
                                                            #line 1374 "PrintScala.cpp"
  append(L", parseTreeBuilder");
                                                            #line 813 "PrintScala.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1380 "PrintScala.cpp"
  append(L", contentCounter");
                                                            #line 816 "PrintScala.cpp.template"
                                                                }
                                                              }
                                                            #line 1385 "PrintScala.cpp"
  append(L")\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  private def collectInput(name: String, content: String): Unit = {\n");
  append(L"    if (! quiet) println(\"loading \" + name)\n");
  append(L"    parsers += new ParseJob(name, content)\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  private def findFiles(ending: String)(f: File): List[File] = {\n");
  append(L"    val files = f.listFiles.toList\n");
  append(L"    files.filter(_.getName.endsWith(ending)) ++\n");
  append(L"    files.filter(_.isDirectory).flatMap(findFiles(ending))\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  private var quiet = false\n");
  append(L"  private var parsed: Long = 0\n");
  append(L"  private var errorCount = 0\n");
  append(L"  private var parsers = ArrayBuffer[ParseJob]()\n");
  append(L"\n");
  append(L"  def main(args: Array[String]): Unit = {\n");
  append(L"    if (args.length == 0) {\n");
  append(L"      println(\"Usage: scala ");
                                                            #line 839 "PrintScala.cpp.template"
                                                              print(className.c_str());
                                                            #line 1410 "PrintScala.cpp"
  append(L" [-q] [-r N] [-t N] ENDING...\")\n");
  append(L"      println()\n");
  append(L"      println(\"  parse all files that have names ending with ENDING, in current dir and below,\")\n");
  append(L"      println(\"  and display performance summary.\")\n");
  append(L"      println()\n");
  append(L"      println(\"  -q     do not show file names\")\n");
  append(L"      println(\"  -r N   repeat N times\")\n");
  append(L"      println(\"  -t N   repeat until N seconds have elapsed\")\n");
  append(L"    }\n");
  append(L"    else {\n");
  append(L"      var repeat = 1\n");
  append(L"      var timeout = 0\n");
  append(L"      var i = 0\n");
  append(L"      while (i < args.length && args(i).startsWith(\"-\")) {\n");
  append(L"        val option = if (args(i).length == 2) args(i)(1) else ' '\n");
  append(L"        option match {\n");
  append(L"        case 'q' =>\n");
  append(L"          quiet = true\n");
  append(L"        case 'r' =>\n");
  append(L"          i += 1\n");
  append(L"          repeat = args(i).toInt\n");
  append(L"          timeout = 0\n");
  append(L"        case 't' =>\n");
  append(L"          repeat = 0\n");
  append(L"          i += 1\n");
  append(L"          timeout = 1000 * args(i).toInt\n");
  append(L"        case _ =>\n");
  append(L"          throw new IllegalArgumentException(\"invalid option: \" + args(i))\n");
  append(L"        }\n");
  append(L"        i += 1\n");
  append(L"      }\n");
  append(L"\n");
  append(L"      var start = System.currentTimeMillis\n");
  append(L"\n");
  append(L"      while (i < args.length) {\n");
  append(L"        findFiles(args(i))(new File(\".\")) foreach (f => collectInput(f.getPath, read(f.getPath)))\n");
  append(L"        i += 1\n");
  append(L"      }\n");
  append(L"\n");
  append(L"      if (! parsers.isEmpty) {\n");
  append(L"\n");
  append(L"        var msec = System.currentTimeMillis - start\n");
  append(L"\n");
  append(L"        if (! quiet) println()\n");
  append(L"        println(\"loaded \" + parsers.size + \" file\" +\n");
  append(L"                (if (parsers.size == 1) \"\" else \"s\") +\n");
  append(L"                \" in \" + msec + \" msec\")\n");
  append(L"        if (! quiet) println()\n");
  append(L"        Console.flush()\n");
  append(L"\n");
  append(L"        start = System.currentTimeMillis\n");
  append(L"        i = 0\n");
  append(L"        var continue = true\n");
  append(L"        while (continue) {\n");
  append(L"          if (repeat != 0 && i >= repeat) {\n");
  append(L"            continue = false\n");
  append(L"          }\n");
  append(L"          else if (timeout != 0 && System.currentTimeMillis - start >= timeout) {\n");
  append(L"            continue = false\n");
  append(L"          }\n");
  append(L"          else {\n");
  append(L"            for (job <- parsers) {\n");
  append(L"              if (job.parser != null) {\n");
  append(L"                try {\n");
  append(L"                  if (! quiet) print(\"parsing \" + job.name)\n");
  append(L"                  job.parser");
                                                            #line 905 "PrintScala.cpp.template"
                                                              if (useGlr)
                                                              {
                                                            #line 1480 "PrintScala.cpp"
  append(L".thread");
                                                            #line 907 "PrintScala.cpp.template"
                                                              }
                                                            #line 1484 "PrintScala.cpp"
  append(L".reset(0, 0, 0)\n");
  append(L"                  job.parser.");
                                                            #line 909 "PrintScala.cpp.template"
                                                              print(methodPrefixParse);
                                                              print(Format::acceptableName<WString>(grammar->startSymbol()->name).c_str());
                                                            #line 1490 "PrintScala.cpp"
  append(L"\n");
  append(L"                  if (! quiet) println()");
                                                            #line 912 "PrintScala.cpp.template"
                                                              if (tree)
                                                              {
                                                                if (isLrParser)
                                                                {
                                                            #line 1498 "PrintScala.cpp"
  append(L"\n");
  append(L"                  job.parseTreeBuilder.serialize(job.contentCounter)");
                                                            #line 918 "PrintScala.cpp.template"
                                                                }
                                                            #line 1503 "PrintScala.cpp"
  append(L"\n");
  append(L"                  if (job.contentCounter.length != job.input.length) {\n");
  append(L"                    throw new RuntimeException(\"content counter saw \" + job.contentCounter.length + \", but input length is \" + job.input.length);\n");
  append(L"                  }");
                                                            #line 922 "PrintScala.cpp.template"
                                                              }
                                                            #line 1510 "PrintScala.cpp"
  append(L"\n");
  append(L"                  parsed += job.input.length\n");
  append(L"                }\n");
  append(L"                catch {\n");
  append(L"                  case pe: ParseException =>\n");
  append(L"                    errorCount += 1\n");
  append(L"                    if (quiet) print(\"parsing \" + job.name)\n");
  append(L"                    println(\": error: \" + job.parser.getErrorMessage(pe))\n");
  append(L"                    job.parser = null\n");
  append(L"                }\n");
  append(L"              }\n");
  append(L"            }\n");
  append(L"            i += 1\n");
  append(L"          }\n");
  append(L"        }\n");
  append(L"\n");
  append(L"        msec = System.currentTimeMillis - start\n");
  append(L"        val mbPerSec = if (msec != 0) new java.text.DecimalFormat(\"0.##\").format(parsed / 1024e0 / 1024e0 * 1000e0 / msec) else null\n");
  append(L"\n");
  append(L"        if (! quiet) println()\n");
  append(L"        print(\"parsed \" + parsed + \" byte\" + (if (parsed == 1) \"\" else \"s\") +\n");
  append(L"              \" in \" + msec + \" msec\")\n");
  append(L"        if (mbPerSec != null) {\n");
  append(L"          print(\" (\" + mbPerSec + \" MB/sec)\")\n");
  append(L"        }\n");
  append(L"        println()\n");
  append(L"        println(\"\" + errorCount + \" error\" + (if (errorCount == 1) \"\" else \"s\"))\n");
  append(L"      }\n");
  append(L"    }\n");
  append(L"  }\n");
                                                            #line 953 "PrintScala.cpp.template"
                                                            }

                                                            void PrintScala::printReadMethod()
                                                            {
                                                            #line 1546 "PrintScala.cpp"
  append(L"\n");
  append(L"  private def read(fileName: String) = {\n");
  append(L"    if (fileName(0) == '{' && fileName(fileName.length - 1) == '}') {\n");
  append(L"      fileName.substring(1, fileName.length - 1)\n");
  append(L"    }\n");
  append(L"    else {\n");
  append(L"      val file = io.Source.fromFile(fileName, \"utf-8\")\n");
  append(L"      val content = file.mkString\n");
  append(L"      file.close\n");
  append(L"      if (content(0) == '\\ufeff') content.substring(1) else content\n");
  append(L"    }\n");
  append(L"  }\n");
                                                            #line 969 "PrintScala.cpp.template"
                                                            }

                                                            void PrintScala::printInterface()
                                                            {
                                                              if (! packageName.empty())
                                                              {
                                                            #line 1566 "PrintScala.cpp"
  append(L"\n");
  append(L"package ");
                                                            #line 976 "PrintScala.cpp.template"
                                                                print(packageName.c_str());
                                                            #line 1571 "PrintScala.cpp"
  append(L";\n");
                                                            #line 978 "PrintScala.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                                if (main)
                                                                {
                                                            #line 1579 "PrintScala.cpp"
  append(L"\n");
  append(L"import java.io.IOException;\n");
  append(L"import java.io.Writer;\n");
                                                            #line 986 "PrintScala.cpp.template"
                                                                }
                                                              }
                                                            #line 1586 "PrintScala.cpp"
  append(L"\n");
  append(L"public interface ");
                                                            #line 989 "PrintScala.cpp.template"
                                                              print(className.c_str());
                                                            #line 1591 "PrintScala.cpp"
  append(L"\n");
  append(L"{\n");
  append(L"  def initialize(CharSequence input");
                                                            #line 992 "PrintScala.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 1598 "PrintScala.cpp"
  append(L", EventHandler eh");
                                                            #line 995 "PrintScala.cpp.template"
                                                              }
                                                            #line 1602 "PrintScala.cpp"
  append(L"): Unit\n");
  append(L"  def parse: Unit\n");
  append(L"  def reset: Unit\n");
  append(L"  public String getErrorMessage(ParseException e): Unit\n");
                                                            #line 1000 "PrintScala.cpp.template"
                                                              printParseException();
                                                            #line 1609 "PrintScala.cpp"
  append(L"}\n");
                                                            #line 1002 "PrintScala.cpp.template"
                                                            }

                                                            void PrintScala::printParseException()
                                                            {
                                                            #line 1616 "PrintScala.cpp"
  append(L"\n");
  append(L"  class ParseException(val begin: Int, val end: Int, val state: Int, val offending: Int, val expected: Int) extends RuntimeException {\n");
                                                            #line 1008 "PrintScala.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 1622 "PrintScala.cpp"
  append(L"\n");
  append(L"    private var ambiguousInput = false");
                                                            #line 1011 "PrintScala.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 1628 "PrintScala.cpp"
  append(L"\n");
  append(L"    private var ambiguityDescriptor: ParseTreeBuilder = null");
                                                            #line 1014 "PrintScala.cpp.template"
                                                                }
                                                            #line 1633 "PrintScala.cpp"
  append(L"\n");
  append(L"\n");
  append(L"    def setAmbiguousInput(");
                                                            #line 1017 "PrintScala.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 1640 "PrintScala.cpp"
  append(L"ambiguityDescriptor: ParseTreeBuilder");
                                                            #line 1020 "PrintScala.cpp.template"
                                                                }
                                                            #line 1644 "PrintScala.cpp"
  append(L"): Unit = {\n");
  append(L"      ambiguousInput = true");
                                                            #line 1022 "PrintScala.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 1650 "PrintScala.cpp"
  append(L"\n");
  append(L"      this.ambiguityDescriptor = ambiguityDescriptor");
                                                            #line 1025 "PrintScala.cpp.template"
                                                                }
                                                            #line 1655 "PrintScala.cpp"
  append(L"\n");
  append(L"    }\n");
                                                            #line 1028 "PrintScala.cpp.template"
                                                              }
                                                            #line 1660 "PrintScala.cpp"
  append(L"\n");
  append(L"    override def getMessage = {\n");
  append(L"      ");
                                                            #line 1031 "PrintScala.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 1667 "PrintScala.cpp"
  append(L"if (ambiguousInput) \"ambiguous input\" else ");
                                                            #line 1033 "PrintScala.cpp.template"
                                                              }
                                                            #line 1671 "PrintScala.cpp"
  append(L"if (offending < 0) \"lexical analysis failed\" else \"syntax error\"\n");
  append(L"    }");
                                                            #line 1035 "PrintScala.cpp.template"
                                                              if (useGlr)
                                                              {
                                                            #line 1677 "PrintScala.cpp"
  append(L"\n");
  append(L"\n");
  append(L"    def isAmbiguousInput: Boolean =\n");
  append(L"      ");
                                                            #line 1040 "PrintScala.cpp.template"
                                                                if (rejectsAmbiguity())
                                                                {
                                                            #line 1685 "PrintScala.cpp"
  append(L"ambiguousInput");
                                                            #line 1042 "PrintScala.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1691 "PrintScala.cpp"
  append(L"false");
                                                            #line 1045 "PrintScala.cpp.template"
                                                                }
                                                                if (rejectsAmbiguity() && tree)
                                                                {
                                                            #line 1697 "PrintScala.cpp"
  append(L"\n");
  append(L"\n");
  append(L"    def serialize(eventHandler: EventHandler): Unit = {\n");
  append(L"      ambiguityDescriptor.serialize(eventHandler)\n");
  append(L"    }");
                                                            #line 1052 "PrintScala.cpp.template"
                                                                }
                                                              }
                                                            #line 1706 "PrintScala.cpp"
  append(L"\n");
  append(L"  }\n");
                                                            #line 1056 "PrintScala.cpp.template"
                                                              if (useGlr)
                                                              {
                                                                openStackNode();
                                                                printCountMethod();
                                                                closeStackNode();
                                                                openThread();
                                                                increaseIndent();
                                                                printThreadBody1();
                                                                decreaseIndent();
                                                              }
                                                            #line 1720 "PrintScala.cpp"
  append(L"\n");
  append(L"  def getExpectedTokenSet(e: ParseException) = {\n");
  append(L"    if (e.expected < 0) {\n");
  append(L"      getTokenSet(- e.state)\n");
  append(L"    }\n");
  append(L"    else {\n");
  append(L"      Array(TOKEN(e.expected))\n");
  append(L"    }\n");
  append(L"  }\n");
                                                            #line 1075 "PrintScala.cpp.template"
                                                              if (noLexer)
                                                              {
                                                            #line 1733 "PrintScala.cpp"
  append(L"\n");
  append(L"  class Token(var code = 0, var begin = 0, var end = 0) {\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  trait Lexer {\n");
  append(L"    def reset(input: String): Unit\n");
  append(L"    def matcher(tokenset: Int, token: Token)\n");
  append(L"  }\n");
                                                            #line 1085 "PrintScala.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                            #line 1746 "PrintScala.cpp"
  append(L"\n");
  append(L"  trait EventHandler {\n");
  append(L"    def reset(string: String): Unit\n");
  append(L"    def startNonterminal(name: String, begin: Int): Unit\n");
  append(L"    def endNonterminal(name: String, end: Int): Unit\n");
  append(L"    def terminal(name: String, begin: Int, end: Int): Unit\n");
  append(L"    def whitespace(begin: Int, end: Int): Unit\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  class TopDownTreeBuilder extends EventHandler {\n");
  append(L"    private var input: String = null\n");
  append(L"    private var stack = new ArrayBuffer[Nonterminal](64)\n");
  append(L"    private var top = -1\n");
  append(L"\n");
  append(L"    override def reset(input: String): Unit = {\n");
  append(L"      this.input = input\n");
  append(L"      top = -1\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    override def startNonterminal(name: String, begin: Int): Unit = {\n");
  append(L"      val nonterminal = new Nonterminal(name, begin, begin, ArrayBuffer[Symbol]())\n");
  append(L"      if (top >= 0) addChild(nonterminal)\n");
  append(L"      top += 1\n");
  append(L"      if (top == stack.length) stack += nonterminal else stack(top) = nonterminal\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    override def endNonterminal(name: String, end: Int): Unit = {\n");
  append(L"      var nonterminal = stack(top)\n");
  append(L"      nonterminal.end = end\n");
  append(L"      if (top > 0) top -= 1\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    override def terminal(name: String, begin: Int, end: Int): Unit = {\n");
  append(L"      addChild(new Terminal(name, begin, end))\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    override def whitespace(begin: Int, end: Int): Unit = {\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    private def addChild(s: Symbol): Unit = {\n");
  append(L"      var current = stack(top)\n");
  append(L"      current.children += s\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    def serialize(e: EventHandler): Unit = {\n");
  append(L"      e.reset(input)\n");
  append(L"      stack(0).send(e)\n");
  append(L"    }\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  abstract class Symbol(n: String, b: Int, e: Int) {\n");
  append(L"    var name = n\n");
  append(L"    var begin = b\n");
  append(L"    var end = e\n");
  append(L"\n");
  append(L"    def send(e: EventHandler): Unit\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  class Terminal(name: String, begin: Int, end: Int) extends Symbol(name, begin, end) {\n");
  append(L"    override def send(e: EventHandler): Unit = {\n");
  append(L"      e.terminal(name, begin, end)\n");
  append(L"    }\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  class Nonterminal(name: String, begin: Int, end: Int, c: ArrayBuffer[Symbol]) extends Symbol(name, begin, end) {\n");
  append(L"    var children = c\n");
  append(L"\n");
  append(L"    override def send(e: EventHandler): Unit = {\n");
  append(L"      e.startNonterminal(name, begin)\n");
  append(L"      var pos = begin\n");
  append(L"      for (c <- children) {\n");
  append(L"        if (pos < c.begin) e.whitespace(pos, c.begin)\n");
  append(L"        c.send(e)\n");
  append(L"        pos = c.end\n");
  append(L"      }\n");
  append(L"      if (pos < end) e.whitespace(pos, end)\n");
  append(L"      e.endNonterminal(name, end)\n");
  append(L"    }\n");
  append(L"  }\n");
                                                            #line 1167 "PrintScala.cpp.template"
                                                                if (isLrParser)
                                                                {
                                                            #line 1829 "PrintScala.cpp"
  append(L"\n");
  append(L"  trait BottomUpEventHandler {\n");
  append(L"    def reset(string: String): Unit\n");
  append(L"    def nonterminal(name: String, begin: Int, end: Int, count: Int): Unit\n");
  append(L"    def terminal(name: String, begin: Int, end: Int): Unit");
                                                            #line 1173 "PrintScala.cpp.template"
                                                                  if (resolvesAmbiguity)
                                                                  {
                                                            #line 1838 "PrintScala.cpp"
  append(L"\n");
  append(L"    def ambiguity(begin: Int, end: Int): Unit");
                                                            #line 1176 "PrintScala.cpp.template"
                                                                  }
                                                            #line 1843 "PrintScala.cpp"
  append(L"\n");
  append(L"  }\n");
                                                            #line 1179 "PrintScala.cpp.template"
                                                                }

                                                                if (main)
                                                                {
                                                            #line 1851 "PrintScala.cpp"
  append(L"\n");
  append(L"  class XmlSerializer(val out: Writer, val indent: Boolean) extends EventHandler {\n");
  append(L"    private var input: String = null\n");
  append(L"    private var delayedTag: String = null\n");
  append(L"    private var hasChildElement = false\n");
  append(L"    private var depth = 0\n");
  append(L"\n");
  append(L"    def reset(string: String): Unit = {\n");
  append(L"      writeOutput(\"<?xml version=\\\"1.0\\\" encoding=\\\"UTF-8\\\"?\" + \">\")\n");
  append(L"      input = string\n");
  append(L"      delayedTag = null\n");
  append(L"      hasChildElement = false\n");
  append(L"      depth = 0\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    def startNonterminal(name: String, begin: Int): Unit = {\n");
  append(L"      if (delayedTag != null) {\n");
  append(L"        writeOutput(\"<\")\n");
  append(L"        writeOutput(delayedTag)\n");
  append(L"        writeOutput(\">\")\n");
  append(L"      }\n");
  append(L"      delayedTag = name\n");
  append(L"      if (indent) {\n");
  append(L"        writeOutput(\"\\n\")\n");
  append(L"        var i = 0\n");
  append(L"        for (i <- 1 to depth) {\n");
  append(L"          writeOutput(\"  \")\n");
  append(L"        }\n");
  append(L"      }\n");
  append(L"      hasChildElement = false\n");
  append(L"      depth += 1\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    def endNonterminal(name: String, end: Int): Unit = {\n");
  append(L"      depth -= 1\n");
  append(L"      if (delayedTag != null) {\n");
  append(L"        delayedTag = null\n");
  append(L"        writeOutput(\"<\")\n");
  append(L"        writeOutput(name)\n");
  append(L"        writeOutput(\"/>\")\n");
  append(L"      }\n");
  append(L"      else {\n");
  append(L"        if (indent) {\n");
  append(L"          if (hasChildElement) {\n");
  append(L"            writeOutput(\"\\n\")\n");
  append(L"            var i = 0\n");
  append(L"            for (i <- 1 to depth) {\n");
  append(L"              writeOutput(\"  \")\n");
  append(L"            }\n");
  append(L"          }\n");
  append(L"        }\n");
  append(L"        writeOutput(\"</\")\n");
  append(L"        writeOutput(name)\n");
  append(L"        writeOutput(\">\")\n");
  append(L"      }\n");
  append(L"      hasChildElement = true\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    def terminal(name: String, begin: Int, end: Int): Unit = {\n");
  append(L"      val tag = if (name(0) == '\\'') \"TOKEN\" else name\n");
  append(L"      startNonterminal(tag, begin)\n");
  append(L"      characters(begin, end)\n");
  append(L"      endNonterminal(tag, end)\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    def whitespace(begin: Int, end: Int): Unit = {\n");
  append(L"      characters(begin, end)\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    private def characters(begin: Int, end: Int): Unit = {\n");
  append(L"      if (begin < end) {\n");
  append(L"        if (delayedTag != null) {\n");
  append(L"          writeOutput(\"<\")\n");
  append(L"          writeOutput(delayedTag)\n");
  append(L"          writeOutput(\">\")\n");
  append(L"          delayedTag = null\n");
  append(L"        }\n");
  append(L"        writeOutput(input.substring(begin, end)\n");
  append(L"                         .replace(\"&\", \"&amp;\")\n");
  append(L"                         .replace(\"<\", \"&lt;\")\n");
  append(L"                         .replace(\">\", \"&gt;\"))\n");
  append(L"      }\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    def writeOutput(content: String): Unit = {\n");
  append(L"      out.write(content)\n");
  append(L"    }\n");
  append(L"  }\n");
                                                            #line 1271 "PrintScala.cpp.template"
                                                                }
                                                                if (tree && isLrParser)
                                                                {
                                                            #line 1944 "PrintScala.cpp"
  append(L"\n");
  append(L"  class ParseTreeBuilder extends BottomUpEventHandler {\n");
  append(L"    var input: String = null\n");
  append(L"    var stack = new ArrayBuffer[Symbol](64)\n");
  append(L"    var top = -1\n");
  append(L"\n");
  append(L"    override def reset(input: String): Unit = {\n");
  append(L"      this.input = input\n");
  append(L"      top = -1\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    override def nonterminal(name: String, begin: Int, end: Int, count: Int): Unit = {");
                                                            #line 1286 "PrintScala.cpp.template"
                                                                  if (rejectsAmbiguity())
                                                                  {
                                                            #line 1960 "PrintScala.cpp"
  append(L"\n");
  append(L"      if (count > top + 1) {\n");
  append(L"        val content: ArrayBuffer[Symbol] = pop(top + 1)\n");
  append(L"        nonterminal(\"UNAMBIGUOUS\", begin, if (content.length == 0) end else content(0).begin, 0)\n");
  append(L"        for (symbol <- content)\n");
  append(L"          push(symbol)\n");
  append(L"        push(new Nonterminal(name, begin, end, pop(top + 1)))\n");
  append(L"      }\n");
  append(L"      else {\n");
  append(L"        push(new Nonterminal(name, begin, end, pop(count)))\n");
  append(L"      }");
                                                            #line 1298 "PrintScala.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 1976 "PrintScala.cpp"
  append(L"\n");
  append(L"      push(new Nonterminal(name, begin, end, pop(count)))");
                                                            #line 1302 "PrintScala.cpp.template"
                                                                  }
                                                            #line 1981 "PrintScala.cpp"
  append(L"\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    override def terminal(name: String, begin: Int, end: Int): Unit = {\n");
  append(L"      push(new Terminal(name, begin, end))\n");
  append(L"    }\n");
                                                            #line 1309 "PrintScala.cpp.template"
                                                                  if (resolvesAmbiguity)
                                                                  {
                                                            #line 1991 "PrintScala.cpp"
  append(L"\n");
  append(L"    override def ambiguity(begin: Int, end: Int): Unit = {\n");
  append(L"    }\n");
                                                            #line 1314 "PrintScala.cpp.template"
                                                                  }
                                                            #line 1997 "PrintScala.cpp"
  append(L"\n");
  append(L"    def serialize(e: EventHandler): Unit = {\n");
  append(L"      e.reset(input)\n");
  append(L"      var i = 0\n");
  append(L"      for (i <- 0 to top)\n");
  append(L"        stack(i).send(e)\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    def push(s: Symbol): Unit = {\n");
  append(L"      top += 1\n");
  append(L"      if (top == stack.length) stack += s else stack(top) = s\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    def pop(count: Int): ArrayBuffer[Symbol] = {\n");
  append(L"      top -= count\n");
  append(L"      stack.slice(top + 1, top + count + 1)\n");
  append(L"    }\n");
  append(L"  }\n");
                                                            #line 1333 "PrintScala.cpp.template"
                                                                }
                                                                if (performanceTest)
                                                                {
                                                            #line 2020 "PrintScala.cpp"
  append(L"\n");
  append(L"  private class ContentCounter extends EventHandler {\n");
  append(L"    var length = 0\n");
  append(L"    def reset(string: String): Unit = {length = 0}\n");
  append(L"    def startNonterminal(name: String, begin: Int): Unit = {}\n");
  append(L"    def endNonterminal(name: String, end: Int): Unit = {}\n");
  append(L"    def terminal(name: String, begin: Int, end: Int): Unit = {length += end - begin}\n");
  append(L"    def whitespace(begin: Int, end: Int): Unit = {length += end - begin}\n");
  append(L"  }\n");
                                                            #line 1345 "PrintScala.cpp.template"
                                                                }
                                                              }
                                                            }

// End
