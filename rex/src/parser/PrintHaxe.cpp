// This file was generated on Tue Oct 20, 2026 19:55 (UTC+02) by REx v6.3-SNAPSHOT which is Copyright (c) 1979-2026 by Gunther Rademacher <grd@gmx.net>
// REx command line: PrintHaxe.cpp.template
                                                            #line 1 "PrintHaxe.cpp.template"
                                                            #include "../common/Memory.hpp"

                                                            #include "PrintHaxe.hpp"
                                                            #include "ItemSet.hpp"
                                                            #include "../common/CompressedMap.hpp"

                                                            void PrintHaxe::openClass()
                                                            {
                                                              if (hasProlog)
                                                              {
                                                            #line 15 "PrintHaxe.cpp"
  append(L"\n");
                                                            #line 12 "PrintHaxe.cpp.template"
                                                              }
                                                              else
                                                              {
                                                                if (! packageName.empty())
                                                                {
                                                            #line 23 "PrintHaxe.cpp"
  append(L"\n");
  append(L"package ");
                                                            #line 18 "PrintHaxe.cpp.template"
                                                                  print(packageName.c_str());
                                                            #line 28 "PrintHaxe.cpp"
  append(L";\n");
                                                            #line 20 "PrintHaxe.cpp.template"
                                                                }
                                                                if (main || performanceTest)
                                                                {
                                                            #line 34 "PrintHaxe.cpp"
  append(L"\n");
  append(L"import haxe.io.Bytes;\n");
  append(L"import sys.io.File;");
                                                            #line 25 "PrintHaxe.cpp.template"
                                                                  if (performanceTest)
                                                                  {
                                                            #line 41 "PrintHaxe.cpp"
  append(L"\n");
  append(L"import sys.FileSystem;");
                                                            #line 28 "PrintHaxe.cpp.template"
                                                                  }
                                                            #line 46 "PrintHaxe.cpp"
  append(L"\n");
                                                            #line 30 "PrintHaxe.cpp.template"
                                                                }
                                                              }
                                                              if (useGlr)
                                                              {
                                                                openStackNode();
                                                                printCountMethod();
                                                                closeStackNode();
                                                                openThread();
                                                                increaseIndent();
                                                                printThreadBody1();
                                                                print(lexerInstanceCode);
                                                                currentStaticPrefix = L"";
                                                            #line 61 "PrintHaxe.cpp"
  append(L"}\n");
                                                            #line 43 "PrintHaxe.cpp.template"
                                                              }
                                                              if (! hasProlog)
                                                              {
                                                            #line 67 "PrintHaxe.cpp"
  append(L"\n");
  append(L"class ");
                                                            #line 47 "PrintHaxe.cpp.template"
                                                                print(className.c_str());
                                                                if (! interfaceName.empty())
                                                                {
                                                            #line 74 "PrintHaxe.cpp"
  append(L" implements ");
                                                            #line 50 "PrintHaxe.cpp.template"
                                                                  print(interfaceName.c_str());
                                                                }
                                                            #line 79 "PrintHaxe.cpp"
  append(L"\n");
  append(L"{");
                                                            #line 53 "PrintHaxe.cpp.template"
                                                              }
                                                              if (performanceTest)
                                                              {
                                                                printFileProcessor();
                                                              }
                                                              if (main)
                                                              {
                                                            #line 90 "PrintHaxe.cpp"
  append(L"\n");
  append(L"  public static function main()\n");
  append(L"  {\n");
  append(L"    var args = Sys.args();\n");
  append(L"\n");
  append(L"    if (args.length == 0)\n");
  append(L"    {\n");
  append(L"      Sys.println(\"Usage: ");
                                                            #line 67 "PrintHaxe.cpp.template"
                                                                print(className.c_str());
                                                                if (tree)
                                                                {
                                                            #line 103 "PrintHaxe.cpp"
  append(L" [-i]");
                                                            #line 70 "PrintHaxe.cpp.template"
                                                                }
                                                            #line 107 "PrintHaxe.cpp"
  append(L" INPUT...\\n\");\n");
  append(L"      Sys.println(\"  parse INPUT, which is either a filename or literal text enclosed in curly braces\");");
                                                            #line 73 "PrintHaxe.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 113 "PrintHaxe.cpp"
  append(L"\n");
  append(L"      Sys.println(\"\");\n");
  append(L"      Sys.println(\"  Option:\");\n");
  append(L"      Sys.println(\"    -i     indented parse tree\");");
                                                            #line 78 "PrintHaxe.cpp.template"
                                                                }
                                                            #line 120 "PrintHaxe.cpp"
  append(L"\n");
  append(L"    }\n");
  append(L"    else\n");
  append(L"    {\n");
  append(L"      var indent = false;\n");
  append(L"      for (arg in args)\n");
  append(L"      {");
                                                            #line 85 "PrintHaxe.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 131 "PrintHaxe.cpp"
  append(L"\n");
  append(L"        if (arg == \"-i\")\n");
  append(L"        {\n");
  append(L"          indent = true;\n");
  append(L"          continue;\n");
  append(L"        }\n");
                                                            #line 93 "PrintHaxe.cpp.template"
                                                                }
                                                            #line 140 "PrintHaxe.cpp"
  append(L"\n");
  append(L"        var input = read(arg);");
                                                            #line 95 "PrintHaxe.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 146 "PrintHaxe.cpp"
  append(L"\n");
  append(L"        var s = new XmlSerializer(indent);");
                                                            #line 98 "PrintHaxe.cpp.template"
                                                                  if (isLrParser)
                                                                  {
                                                            #line 152 "PrintHaxe.cpp"
  append(L"\n");
  append(L"        var b = new ParseTreeBuilder();");
                                                            #line 101 "PrintHaxe.cpp.template"
                                                                  }
                                                                }
                                                            #line 158 "PrintHaxe.cpp"
  append(L"\n");
  append(L"        var parser = new ");
                                                            #line 104 "PrintHaxe.cpp.template"
                                                                print(className.c_str());
                                                            #line 163 "PrintHaxe.cpp"
  append(L"(input");
                                                            #line 105 "PrintHaxe.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 168 "PrintHaxe.cpp"
  append(L", ");
                                                            #line 107 "PrintHaxe.cpp.template"
                                                                  if (isLrParser)
                                                                  {
                                                            #line 173 "PrintHaxe.cpp"
  append(L"b");
                                                            #line 109 "PrintHaxe.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 179 "PrintHaxe.cpp"
  append(L"s");
                                                            #line 112 "PrintHaxe.cpp.template"
                                                                  }
                                                                }
                                                            #line 184 "PrintHaxe.cpp"
  append(L");\n");
  append(L"        try\n");
  append(L"        {");
                                                            #line 116 "PrintHaxe.cpp.template"
                                                                if (trace)
                                                                {
                                                            #line 191 "PrintHaxe.cpp"
  append(L"\n");
  append(L"          trace(\"<trace>\");");
                                                            #line 119 "PrintHaxe.cpp.template"
                                                                }
                                                            #line 196 "PrintHaxe.cpp"
  append(L"\n");
  append(L"          parser.");
                                                            #line 121 "PrintHaxe.cpp.template"
                                                                print(methodPrefixParse);
                                                                print(Format::acceptableName<WString>(grammar->startSymbol()->name).c_str());
                                                            #line 202 "PrintHaxe.cpp"
  append(L"();");
                                                            #line 123 "PrintHaxe.cpp.template"
                                                                if (trace)
                                                                {
                                                            #line 207 "PrintHaxe.cpp"
  append(L"\n");
  append(L"          trace(\"</trace>\");");
                                                            #line 126 "PrintHaxe.cpp.template"
                                                                }
                                                                if (tree && isLrParser)
                                                                {
                                                            #line 214 "PrintHaxe.cpp"
  append(L"\n");
  append(L"          b.serialize(s);");
                                                            #line 130 "PrintHaxe.cpp.template"
                                                                }
                                                            #line 219 "PrintHaxe.cpp"
  append(L"\n");
  append(L"        }\n");
  append(L"        catch (pe: ParseException)\n");
  append(L"        {");
                                                            #line 134 "PrintHaxe.cpp.template"
                                                                if (rejectsAmbiguity() && tree)
                                                                {
                                                            #line 227 "PrintHaxe.cpp"
  append(L"\n");
  append(L"          if (pe.isAmbiguousInput())\n");
  append(L"          {\n");
  append(L"            pe.serialize(s);\n");
  append(L"            Sys.println(\"\");\n");
  append(L"          }");
                                                            #line 141 "PrintHaxe.cpp.template"
                                                                }
                                                            #line 236 "PrintHaxe.cpp"
  append(L"\n");
  append(L"          throw \"ParseException while processing \" + arg + \":\\n\" + parser.getErrorMessage(pe);\n");
  append(L"        }\n");
  append(L"      }\n");
  append(L"    }\n");
  append(L"  }\n");
                                                            #line 148 "PrintHaxe.cpp.template"
                                                              }
                                                              printReadMethod();
                                                              if (! hasProlog)
                                                              {
                                                            #line 248 "PrintHaxe.cpp"
  append(L"\n");
  append(L"  public function new(string");
                                                            #line 153 "PrintHaxe.cpp.template"
                                                                if (noLexer)
                                                                {
                                                            #line 254 "PrintHaxe.cpp"
  append(L", lexer");
                                                            #line 155 "PrintHaxe.cpp.template"
                                                                }
                                                                if (tree)
                                                                {
                                                            #line 260 "PrintHaxe.cpp"
  append(L", t");
                                                            #line 158 "PrintHaxe.cpp.template"
                                                                }
                                                            #line 264 "PrintHaxe.cpp"
  append(L")\n");
  append(L"  {\n");
  append(L"    initialize(string");
                                                            #line 161 "PrintHaxe.cpp.template"
                                                                if (noLexer)
                                                                {
                                                            #line 271 "PrintHaxe.cpp"
  append(L", lexer");
                                                            #line 163 "PrintHaxe.cpp.template"
                                                                }
                                                                if (tree)
                                                                {
                                                            #line 277 "PrintHaxe.cpp"
  append(L", t");
                                                            #line 166 "PrintHaxe.cpp.template"
                                                                }
                                                            #line 281 "PrintHaxe.cpp"
  append(L");\n");
  append(L"  }\n");
                                                            #line 169 "PrintHaxe.cpp.template"
                                                              }
                                                              /*
                                                            #line 287 "PrintHaxe.cpp"
  append(L"\n");
  append(L"  public function getInput()\n");
  append(L"  {\n");
  append(L"    return input.toString();\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  public function getTokenOffset()\n");
  append(L"  {\n");
  append(L"    return b0;\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  public function getTokenEnd()\n");
  append(L"  {\n");
  append(L"    return e0;\n");
  append(L"  }\n");
                                                            #line 186 "PrintHaxe.cpp.template"
                                                              */
                                                              if (useGlr)
                                                              {
                                                                beginPublic();
                                                              }
                                                            }

                                                            void PrintHaxe::openStackNode()
                                                            {
                                                              currentStaticPrefix = classNamePrefix;
                                                            #line 314 "PrintHaxe.cpp"
  append(L"\n");
  append(L"private class StackNode\n");
  append(L"{\n");
  append(L"  public var state: Int;");
                                                            #line 199 "PrintHaxe.cpp.template"
                                                              if (grammar->states->hasLookback)
                                                              {
                                                            #line 322 "PrintHaxe.cpp"
  append(L"\n");
  append(L"  public var code: Int;");
                                                            #line 202 "PrintHaxe.cpp.template"
                                                              }
                                                            #line 327 "PrintHaxe.cpp"
  append(L"\n");
  append(L"  public var pos: Int;\n");
  append(L"  public var link: StackNode;\n");
  append(L"\n");
  append(L"  public function new(state: Int, ");
                                                            #line 207 "PrintHaxe.cpp.template"
                                                              if (grammar->states->hasLookback)
                                                              {
                                                            #line 336 "PrintHaxe.cpp"
  append(L"code: Int, ");
                                                            #line 209 "PrintHaxe.cpp.template"
                                                              }
                                                            #line 340 "PrintHaxe.cpp"
  append(L"pos: Int, link: StackNode)\n");
  append(L"  {\n");
  append(L"    this.state = state;");
                                                            #line 212 "PrintHaxe.cpp.template"
                                                              if (grammar->states->hasLookback)
                                                              {
                                                            #line 347 "PrintHaxe.cpp"
  append(L"\n");
  append(L"    this.code = code;");
                                                            #line 215 "PrintHaxe.cpp.template"
                                                              }
                                                            #line 352 "PrintHaxe.cpp"
  append(L"\n");
  append(L"    this.pos = pos;\n");
  append(L"    this.link = link;\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  public function equals(rhs: StackNode): Bool\n");
  append(L"  {\n");
  append(L"    var lhs: StackNode = this;\n");
  append(L"    while (lhs != null && rhs != null)\n");
  append(L"    {\n");
  append(L"      if (lhs == rhs) return true;\n");
  append(L"      if (lhs.state != rhs.state) return false;");
                                                            #line 227 "PrintHaxe.cpp.template"
                                                              if (grammar->states->hasLookback)
                                                              {
                                                            #line 368 "PrintHaxe.cpp"
  append(L"\n");
  append(L"      if (lhs.code != rhs.code) return false;");
                                                            #line 230 "PrintHaxe.cpp.template"
                                                              }
                                                            #line 373 "PrintHaxe.cpp"
  append(L"\n");
  append(L"      if (lhs.pos != rhs.pos) return false;\n");
  append(L"      lhs = lhs.link;\n");
  append(L"      rhs = rhs.link;\n");
  append(L"    }\n");
  append(L"    return lhs == rhs;\n");
  append(L"  }");
                                                            #line 237 "PrintHaxe.cpp.template"
                                                              increaseIndent();
                                                              beginPublic();
                                                            }

                                                            void PrintHaxe::closeStackNode()
                                                            {
                                                              decreaseIndent();
                                                            #line 389 "PrintHaxe.cpp"
  append(L"\n");
  append(L"}\n");
  append(L"\n");
  append(L"private class Heap\n");
  append(L"{\n");
  append(L"  private var array: Array<ParsingThread>;\n");
  append(L"  private var size: Int;\n");
  append(L"\n");
  append(L"  public function new()\n");
  append(L"  {\n");
  append(L"    array = [];\n");
  append(L"    size = 0;\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  public function offer(value: ParsingThread): Bool\n");
  append(L"  {\n");
  append(L"    var index = size++;\n");
  append(L"    while (index != 0)\n");
  append(L"    {\n");
  append(L"      var parentIndex = (index - 1) >> 1;\n");
  append(L"      if (array[parentIndex].compareTo(value) <= 0)\n");
  append(L"        break;\n");
  append(L"      array[index] = array[parentIndex];\n");
  append(L"      index = parentIndex;\n");
  append(L"    }\n");
  append(L"    array[index] = value;\n");
  append(L"    return true;\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  public function poll(): ParsingThread\n");
  append(L"  {\n");
  append(L"    if (size == 0)\n");
  append(L"      return null;\n");
  append(L"    var min = array[0];\n");
  append(L"    if (--size > 0)\n");
  append(L"    {\n");
  append(L"      var value = array[size];\n");
  append(L"      var index = 0;\n");
  append(L"      var child: Int;\n");
  append(L"      while (true)\n");
  append(L"      {\n");
  append(L"        child = (index << 1) + 2;\n");
  append(L"        if (child < size)\n");
  append(L"        {\n");
  append(L"          var otherChild = child - 1;\n");
  append(L"          if (otherChild < size && array[child].compareTo(array[otherChild]) > 0)\n");
  append(L"            child = otherChild;\n");
  append(L"        }\n");
  append(L"        else if (--child >= size)\n");
  append(L"        {\n");
  append(L"          break;\n");
  append(L"        }\n");
  append(L"        if (value.compareTo(array[child]) <= 0)\n");
  append(L"        {\n");
  append(L"          break;\n");
  append(L"        }\n");
  append(L"        array[index] = array[child];\n");
  append(L"        index = child;\n");
  append(L"      }\n");
  append(L"      array[index] = value;\n");
  append(L"    }\n");
  append(L"    return min;\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  public function isEmpty(): Bool\n");
  append(L"  {\n");
  append(L"    return size == 0;\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  public function peek(): ParsingThread\n");
  append(L"  {\n");
  append(L"    return size == 0 ? null : array[0];\n");
  append(L"  }\n");
  append(L"}\n");
                                                            #line 318 "PrintHaxe.cpp.template"
                                                              beginNonpublic();
                                                              if (hasCustomCode)
                                                              {
                                                            #line 468 "PrintHaxe.cpp"
  append(L"\n");
  append(L"private class DeferredCode\n");
  append(L"{\n");
  append(L"  public var link: DeferredCode;\n");
  append(L"  public var codeId: Int;\n");
  append(L"  public var b0: Int;\n");
  append(L"  public var e0: Int;\n");
  append(L"\n");
  append(L"  public function new(link: DeferredCode, codeId: Int, b0: Int, e0: Int)\n");
  append(L"  {\n");
  append(L"    this.link = link;\n");
  append(L"    this.codeId = codeId;\n");
  append(L"    this.b0 = b0;\n");
  append(L"    this.e0 = e0;\n");
  append(L"  }\n");
  append(L"}\n");
                                                            #line 337 "PrintHaxe.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                            #line 489 "PrintHaxe.cpp"
  append(L"\n");
  append(L"private class DeferredEvent\n");
  append(L"{\n");
  append(L"  public var link: DeferredEvent;\n");
  append(L"  public var name: String;\n");
  append(L"  public var begin: Int;\n");
  append(L"  public var end: Int;");
                                                            #line 346 "PrintHaxe.cpp.template"
                                                                if (shiftAmbiguity)
                                                                {
                                                            #line 500 "PrintHaxe.cpp"
  append(L"\n");
  append(L"  public var depth: Int;\n");
  append(L"\n");
  append(L"  public function isTerminal(): Bool {return false;}");
                                                            #line 351 "PrintHaxe.cpp.template"
                                                                }
                                                            #line 507 "PrintHaxe.cpp"
  append(L"\n");
  append(L"\n");
  append(L"  public function new(link: DeferredEvent, name: String, begin: Int, end: Int)\n");
  append(L"  {\n");
  append(L"    this.link = link;\n");
  append(L"    this.name = name;\n");
  append(L"    this.begin = begin;\n");
  append(L"    this.end = end;");
                                                            #line 359 "PrintHaxe.cpp.template"
                                                                if (shiftAmbiguity)
                                                                {
                                                            #line 519 "PrintHaxe.cpp"
  append(L"\n");
  append(L"    this.depth = link == null ? 1 : link.depth + 1;");
                                                            #line 362 "PrintHaxe.cpp.template"
                                                                }
                                                            #line 524 "PrintHaxe.cpp"
  append(L"\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  public function execute(eventHandler: BottomUpEventHandler): Void {}\n");
  append(L"\n");
  append(L"  public function release(eventHandler: BottomUpEventHandler): Void\n");
  append(L"  {\n");
  append(L"    var current: DeferredEvent = this;\n");
  append(L"    var predecessor: DeferredEvent = current.link;\n");
  append(L"    current.link = null;\n");
  append(L"    while (predecessor != null)\n");
  append(L"    {\n");
  append(L"      var next: DeferredEvent = predecessor.link;\n");
  append(L"      predecessor.link = current;\n");
  append(L"      current = predecessor;\n");
  append(L"      predecessor = next;\n");
  append(L"    }\n");
  append(L"    do\n");
  append(L"    {\n");
  append(L"      ");
                                                            #line 382 "PrintHaxe.cpp.template"
                                                                if (shiftAmbiguity)
                                                                {
                                                            #line 548 "PrintHaxe.cpp"
  append(L"if (eventHandler != null)\n");
  append(L"        ");
                                                            #line 385 "PrintHaxe.cpp.template"
                                                                }
                                                            #line 553 "PrintHaxe.cpp"
  append(L"current.execute(eventHandler);\n");
  append(L"      current = current.link;\n");
  append(L"    }\n");
  append(L"    while (current != null);\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  public function show(eventHandler: BottomUpEventHandler): Void\n");
  append(L"  {\n");
  append(L"    var stack = new Array<DeferredEvent>();\n");
  append(L"    var current = this;\n");
  append(L"    while (current != null)\n");
  append(L"    {\n");
  append(L"      stack.push(current);\n");
  append(L"      current = current.link;\n");
  append(L"    }\n");
  append(L"    while (stack.length > 0)\n");
  append(L"    {\n");
  append(L"      stack.pop().execute(eventHandler);\n");
  append(L"    }\n");
  append(L"  }\n");
  append(L"}\n");
  append(L"\n");
  append(L"private class TerminalEvent extends DeferredEvent\n");
  append(L"{\n");
  append(L"  public function new(link: DeferredEvent, name: String , begin: Int, end: Int)\n");
  append(L"  {\n");
  append(L"    super(link, name, begin, end);\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  public override function execute(eventHandler: BottomUpEventHandler): Void\n");
  append(L"  {\n");
  append(L"    eventHandler.terminal(name, begin, end);\n");
  append(L"  }");
                                                            #line 418 "PrintHaxe.cpp.template"
                                                                if (shiftAmbiguity)
                                                                {
                                                            #line 590 "PrintHaxe.cpp"
  append(L"\n");
  append(L"\n");
  append(L"  public override function isTerminal(): Bool {return true;}");
                                                            #line 422 "PrintHaxe.cpp.template"
                                                                }
                                                            #line 596 "PrintHaxe.cpp"
  append(L"\n");
  append(L"}\n");
  append(L"\n");
  append(L"private class NonterminalEvent extends DeferredEvent\n");
  append(L"{\n");
  append(L"  public var count: Int;\n");
  append(L"\n");
  append(L"  public function new(link: DeferredEvent, name: String, begin: Int, end: Int, count: Int)\n");
  append(L"  {\n");
  append(L"    super(link, name, begin, end);\n");
  append(L"    this.count = count;\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  public override function execute(eventHandler: BottomUpEventHandler): Void\n");
  append(L"  {\n");
  append(L"    eventHandler.nonterminal(name, begin, end, count);\n");
  append(L"  }\n");
  append(L"}\n");
                                                            #line 441 "PrintHaxe.cpp.template"
                                                                if (resolvesAmbiguity)
                                                                {
                                                            #line 618 "PrintHaxe.cpp"
  append(L"\n");
  append(L"private class AmbiguityEvent extends DeferredEvent\n");
  append(L"{\n");
  append(L"  public function new(link: DeferredEvent, begin: Int, end: Int)\n");
  append(L"  {\n");
  append(L"    super(link, null, begin, end);\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  public override function execute(eventHandler: BottomUpEventHandler): Void\n");
  append(L"  {\n");
  append(L"    eventHandler.ambiguity(begin, end);\n");
  append(L"  }\n");
  append(L"}\n");
                                                            #line 456 "PrintHaxe.cpp.template"
                                                                }
                                                              }
                                                            }

                                                            void PrintHaxe::openThread()
                                                            {
                                                            #line 639 "PrintHaxe.cpp"
  append(L"\n");
  append(L"private class ParsingThread\n");
  append(L"{\n");
  append(L"  public var parser: ");
                                                            #line 465 "PrintHaxe.cpp.template"
                                                              print(className.c_str());
                                                            #line 646 "PrintHaxe.cpp"
  append(L";\n");
  append(L"  public var threads: Heap;\n");
  append(L"  public var accepted: Bool;\n");
  append(L"  public var stack: StackNode ;\n");
  append(L"  public var state: Int;\n");
  append(L"  public var action: Int;\n");
  append(L"  public var target: Int;");
                                                            #line 472 "PrintHaxe.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 657 "PrintHaxe.cpp"
  append(L"\n");
  append(L"  public var deferredEvent: DeferredEvent;");
                                                            #line 475 "PrintHaxe.cpp.template"
                                                              }
                                                              if (hasCustomCode)
                                                              {
                                                            #line 664 "PrintHaxe.cpp"
  append(L"\n");
  append(L"  public var deferredCode: DeferredCode;");
                                                            #line 479 "PrintHaxe.cpp.template"
                                                              }
                                                            #line 669 "PrintHaxe.cpp"
  append(L"\n");
  append(L"  public var id: Int;");
                                                            #line 481 "PrintHaxe.cpp.template"
                                                              if (resolvesAmbiguity)
                                                              {
                                                            #line 675 "PrintHaxe.cpp"
  append(L"\n");
  append(L"  public var eventCount: Int;");
                                                            #line 484 "PrintHaxe.cpp.template"
                                                              }
                                                            #line 680 "PrintHaxe.cpp"
  append(L"\n");
  append(L"\n");
  append(L"  public function new()\n");
  append(L"  {\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  public function open(initialState: Int");
                                                            #line 491 "PrintHaxe.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 691 "PrintHaxe.cpp"
  append(L", eh: BottomUpEventHandler");
                                                            #line 493 "PrintHaxe.cpp.template"
                                                              }
                                                            #line 695 "PrintHaxe.cpp"
  append(L", t: Int): Heap\n");
  append(L"  {\n");
  append(L"    accepted = false;\n");
  append(L"    target = t;");
                                                            #line 497 "PrintHaxe.cpp.template"
                                                              if (resolvesAmbiguity)
                                                              {
                                                            #line 703 "PrintHaxe.cpp"
  append(L"\n");
  append(L"    eventCount = 0;");
                                                            #line 500 "PrintHaxe.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                            #line 710 "PrintHaxe.cpp"
  append(L"\n");
  append(L"    eventHandler = eh;\n");
  append(L"    if (eventHandler != null)\n");
  append(L"    {\n");
  append(L"      eventHandler.reset(parser.input);\n");
  append(L"    }\n");
  append(L"    deferredEvent = null;");
                                                            #line 509 "PrintHaxe.cpp.template"
                                                              }
                                                              if (hasCustomCode && useGlr)
                                                              {
                                                            #line 722 "PrintHaxe.cpp"
  append(L"\n");
  append(L"    deferredCode = null;");
                                                            #line 513 "PrintHaxe.cpp.template"
                                                              }
                                                            #line 727 "PrintHaxe.cpp"
  append(L"\n");
  append(L"    stack = new StackNode(-1, ");
                                                            #line 515 "PrintHaxe.cpp.template"
                                                              if (grammar->states->hasLookback)
                                                              {
                                                            #line 733 "PrintHaxe.cpp"
  append(L"0, ");
                                                            #line 517 "PrintHaxe.cpp.template"
                                                              }
                                                            #line 737 "PrintHaxe.cpp"
  append(L"e0, null);\n");
  append(L"    state = initialState;\n");
  append(L"    action = predict(initialState);");
                                                            #line 520 "PrintHaxe.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 744 "PrintHaxe.cpp"
  append(L"\n");
  append(L"    es = e0;");
                                                            #line 523 "PrintHaxe.cpp.template"
                                                              }
                                                            #line 749 "PrintHaxe.cpp"
  append(L"\n");
  append(L"    bw = e0;\n");
  append(L"    bs = e0;\n");
  append(L"    threads = new Heap();\n");
  append(L"    threads.offer(this);\n");
  append(L"    return threads;\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  public function copy(other: ParsingThread , action: Int): ParsingThread\n");
  append(L"  {\n");
  append(L"    this.parser = other.parser;\n");
  append(L"    accepted = other.accepted;\n");
  append(L"    this.action = action;\n");
  append(L"    target = other.target;\n");
  append(L"    bs = other.bs;\n");
  append(L"    bw = other.bw;");
                                                            #line 539 "PrintHaxe.cpp.template"
                                                              if (resolvesAmbiguity)
                                                              {
                                                            #line 769 "PrintHaxe.cpp"
  append(L"\n");
  append(L"    eventCount = other.eventCount;");
                                                            #line 542 "PrintHaxe.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                            #line 776 "PrintHaxe.cpp"
  append(L"\n");
  append(L"    es = other.es;\n");
  append(L"    eventHandler = other.eventHandler;\n");
  append(L"    deferredEvent = other.deferredEvent;");
                                                            #line 548 "PrintHaxe.cpp.template"
                                                              }
                                                              if (hasCustomCode)
                                                              {
                                                            #line 785 "PrintHaxe.cpp"
  append(L"\n");
  append(L"    deferredCode = other.deferredCode;");
                                                            #line 552 "PrintHaxe.cpp.template"
                                                              }
                                                            #line 790 "PrintHaxe.cpp"
  append(L"\n");
  append(L"    id = ++parser.maxId;\n");
  append(L"    threads = other.threads;\n");
  append(L"    state = other.state;\n");
  append(L"    stack = other.stack;\n");
  append(L"    b0 = other.b0;\n");
  append(L"    e0 = other.e0;");
                                                            #line 559 "PrintHaxe.cpp.template"
                                                              for (size_t i = 1; i <= grammar->k; ++i)
                                                              {
                                                                const wchar_t *iString = format.toString<wchar_t>(i);
                                                            #line 802 "PrintHaxe.cpp"
  append(L"\n");
  append(L"    l");
                                                            #line 563 "PrintHaxe.cpp.template"
                                                                print(iString);
                                                            #line 807 "PrintHaxe.cpp"
  append(L" = other.l");
                                                            #line 564 "PrintHaxe.cpp.template"
                                                                print(iString);
                                                            #line 811 "PrintHaxe.cpp"
  append(L";\n");
  append(L"    b");
                                                            #line 566 "PrintHaxe.cpp.template"
                                                                print(iString);
                                                            #line 816 "PrintHaxe.cpp"
  append(L" = other.b");
                                                            #line 567 "PrintHaxe.cpp.template"
                                                                print(iString);
                                                            #line 820 "PrintHaxe.cpp"
  append(L";\n");
  append(L"    e");
                                                            #line 569 "PrintHaxe.cpp.template"
                                                                print(iString);
                                                            #line 825 "PrintHaxe.cpp"
  append(L" = other.e");
                                                            #line 570 "PrintHaxe.cpp.template"
                                                                print(iString);
                                                            #line 829 "PrintHaxe.cpp"
  append(L";");
                                                            #line 571 "PrintHaxe.cpp.template"
                                                              }
                                                            #line 833 "PrintHaxe.cpp"
  append(L"\n");
  append(L"    end = other.end;\n");
  append(L"    return this;\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  public function compareTo(other: ParsingThread): Int\n");
  append(L"  {\n");
  append(L"    if (accepted != other.accepted)\n");
  append(L"      return accepted ? 1 : -1;\n");
  append(L"    var comp = e0 - other.e0;\n");
  append(L"    return comp == 0 ? id - other.id : comp;\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  public function equals(other: ParsingThread): Bool\n");
  append(L"  {\n");
  append(L"    if (accepted != other.accepted) return false;\n");
  append(L"    if (b1 != other.b1) return false;\n");
  append(L"    if (e1 != other.e1) return false;\n");
  append(L"    if (l1 != other.l1) return false;\n");
  append(L"    if (state != other.state) return false;\n");
  append(L"    if (action != other.action) return false;\n");
  append(L"    if (! stack.equals(other.stack)) return false;\n");
  append(L"    return true;\n");
  append(L"  }\n");
                                                            #line 596 "PrintHaxe.cpp.template"
                                                              if (resolvesAmbiguity && tree)
                                                              {
                                                            #line 861 "PrintHaxe.cpp"
  append(L"\n");
  append(L"  public function addAmbiguity(begin: Int, end: Int): Void\n");
  append(L"  {\n");
  append(L"    if (eventHandler != null)\n");
  append(L"      deferredEvent = new AmbiguityEvent(deferredEvent, begin, end);\n");
  append(L"  }\n");
                                                            #line 604 "PrintHaxe.cpp.template"
                                                              }
                                                            #line 870 "PrintHaxe.cpp"
  append(L"\n");
  append(L"  public function parse(): Int\n");
  append(L"  {");
                                                            #line 607 "PrintHaxe.cpp.template"
                                                              increaseIndent();
                                                              beginPublic();
                                                            }

                                                            void PrintHaxe::printGlrParseMethod()
                                                            {
                                                            #line 881 "PrintHaxe.cpp"
  append(L"\n");
  append(L"public static var PARSING = 0;\n");
  append(L"public static var ACCEPTED = 1;\n");
  append(L"public static var ERROR = 2;\n");
  append(L"\n");
  append(L"public function parse(target: Int, initialState: Int, ");
                                                            #line 618 "PrintHaxe.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 891 "PrintHaxe.cpp"
  append(L"eventHandler: BottomUpEventHandler, ");
                                                            #line 621 "PrintHaxe.cpp.template"
                                                              }
                                                            #line 895 "PrintHaxe.cpp"
  append(L"thread: ParsingThread): ParsingThread\n");
  append(L"{\n");
  append(L"  var threads: Heap = thread.open(initialState");
                                                            #line 624 "PrintHaxe.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 902 "PrintHaxe.cpp"
  append(L", eventHandler");
                                                            #line 627 "PrintHaxe.cpp.template"
                                                              }
                                                            #line 906 "PrintHaxe.cpp"
  append(L", target);\n");
  append(L"  while (true)\n");
  append(L"  {\n");
  append(L"    thread = threads.poll();\n");
  append(L"    if (thread.accepted)\n");
  append(L"    {");
                                                            #line 633 "PrintHaxe.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 916 "PrintHaxe.cpp"
  append(L"\n");
  append(L"      var other: ParsingThread = null;\n");
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
  append(L"        rejectAmbiguity(thread.stack.pos, thread.e0");
                                                            #line 648 "PrintHaxe.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 934 "PrintHaxe.cpp"
  append(L", thread.deferredEvent, other.deferredEvent");
                                                            #line 650 "PrintHaxe.cpp.template"
                                                                }
                                                            #line 938 "PrintHaxe.cpp"
  append(L");\n");
  append(L"      }");
                                                            #line 652 "PrintHaxe.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 945 "PrintHaxe.cpp"
  append(L"\n");
  append(L"      while (! threads.isEmpty())\n");
  append(L"      {\n");
  append(L"        var other: ParsingThread = threads.poll();\n");
  append(L"        thread = thread.e0 < other.e0 ? other : resolve(thread, other);\n");
  append(L"      }");
                                                            #line 660 "PrintHaxe.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                            #line 956 "PrintHaxe.cpp"
  append(L"\n");
  append(L"      if (thread.deferredEvent != null)\n");
  append(L"      {\n");
  append(L"        thread.deferredEvent.release(eventHandler);\n");
  append(L"        thread.deferredEvent = null;\n");
  append(L"      }");
                                                            #line 668 "PrintHaxe.cpp.template"
                                                              }
                                                              if (hasCustomCode)
                                                              {
                                                            #line 967 "PrintHaxe.cpp"
  append(L"\n");
  append(L"      thread.executeDeferredCode();");
                                                            #line 672 "PrintHaxe.cpp.template"
                                                              }
                                                            #line 972 "PrintHaxe.cpp"
  append(L"\n");
  append(L"      return thread;\n");
  append(L"    }\n");
  append(L"\n");
                                                            #line 677 "PrintHaxe.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 980 "PrintHaxe.cpp"
  append(L"    if (! threads.isEmpty())\n");
  append(L"    {\n");
  append(L"      if (threads.peek().equals(thread))\n");
  append(L"      {\n");
  append(L"        rejectAmbiguity(thread.stack.pos, thread.e0");
                                                            #line 683 "PrintHaxe.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 989 "PrintHaxe.cpp"
  append(L", thread.deferredEvent, threads.peek().deferredEvent");
                                                            #line 685 "PrintHaxe.cpp.template"
                                                                }
                                                            #line 993 "PrintHaxe.cpp"
  append(L");\n");
  append(L"      }\n");
  append(L"    }");
                                                            #line 688 "PrintHaxe.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 1001 "PrintHaxe.cpp"
  append(L"    while (! threads.isEmpty() && threads.peek().equals(thread))\n");
  append(L"    {\n");
  append(L"      thread = resolve(thread, threads.poll());\n");
  append(L"    }");
                                                            #line 694 "PrintHaxe.cpp.template"
                                                              }
                                                              if (tree || hasCustomCode)
                                                              {
                                                                if (rejectsAmbiguity())
                                                                {
                                                            #line 1012 "PrintHaxe.cpp"
  append(L"\n");
  append(L"    else\n");
  append(L"    {");
                                                            #line 701 "PrintHaxe.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1020 "PrintHaxe.cpp"
  append(L"\n");
  append(L"    if (threads.isEmpty())\n");
  append(L"    {");
                                                            #line 706 "PrintHaxe.cpp.template"
                                                                }
                                                                if (tree)
                                                                {
                                                            #line 1028 "PrintHaxe.cpp"
  append(L"\n");
  append(L"      if (thread.deferredEvent != null)\n");
  append(L"      {\n");
  append(L"        thread.deferredEvent.release(eventHandler);\n");
  append(L"        thread.deferredEvent = null;\n");
  append(L"      }");
                                                            #line 714 "PrintHaxe.cpp.template"
                                                                }
                                                                if (hasCustomCode)
                                                                {
                                                            #line 1039 "PrintHaxe.cpp"
  append(L"\n");
  append(L"      thread.executeDeferredCode();");
                                                            #line 718 "PrintHaxe.cpp.template"
                                                                }
                                                            #line 1044 "PrintHaxe.cpp"
  append(L"\n");
  append(L"    }");
                                                            #line 720 "PrintHaxe.cpp.template"
                                                              }
                                                            #line 1049 "PrintHaxe.cpp"
  append(L"\n");
  append(L"\n");
  append(L"    var status = PARSING;\n");
  append(L"    while (true)\n");
  append(L"    {\n");
  append(L"      if ((status = thread.parse()) != PARSING) break;\n");
  append(L"      if (! threads.isEmpty()) break;\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    if (status != ERROR)\n");
  append(L"    {\n");
  append(L"      threads.offer(thread);\n");
  append(L"    }\n");
  append(L"    else if (threads.isEmpty())\n");
  append(L"    {\n");
  append(L"      throw new ParseException(thread.b1,\n");
  append(L"                               thread.e1,\n");
  append(L"                               TOKENSET[thread.state] + 1,\n");
  append(L"                               thread.l1,\n");
  append(L"                               -1\n");
  append(L"                              );\n");
  append(L"    }\n");
  append(L"  }\n");
  append(L"}\n");
                                                            #line 745 "PrintHaxe.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 1077 "PrintHaxe.cpp"
  append(L"\n");
  append(L"private function rejectAmbiguity(begin: Int, end: Int");
                                                            #line 748 "PrintHaxe.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 1083 "PrintHaxe.cpp"
  append(L", first: DeferredEvent, second: DeferredEvent");
                                                            #line 750 "PrintHaxe.cpp.template"
                                                                }
                                                            #line 1087 "PrintHaxe.cpp"
  append(L"): Void\n");
  append(L"{");
                                                            #line 752 "PrintHaxe.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 1093 "PrintHaxe.cpp"
  append(L"\n");
  append(L"  var treeBuilder = new ParseTreeBuilder();\n");
  append(L"  treeBuilder.reset(input);\n");
  append(L"  second.show(treeBuilder);\n");
  append(L"  treeBuilder.nonterminal(\"ALTERNATIVE\", treeBuilder.getStack()[0].begin, treeBuilder.getStack()[treeBuilder.getTop()].end, treeBuilder.getTop() + 1);\n");
  append(L"  var secondTree = treeBuilder.pop(1)[0];\n");
  append(L"  first.show(treeBuilder);\n");
  append(L"  treeBuilder.nonterminal(\"ALTERNATIVE\", treeBuilder.getStack()[0].begin, treeBuilder.getStack()[treeBuilder.getTop()].end, treeBuilder.getTop() + 1);\n");
  append(L"  treeBuilder.push(secondTree);\n");
  append(L"  treeBuilder.nonterminal(\"AMBIGUOUS\", treeBuilder.getStack()[0].begin, treeBuilder.getStack()[treeBuilder.getTop()].end, 2);");
                                                            #line 764 "PrintHaxe.cpp.template"
                                                                }
                                                            #line 1106 "PrintHaxe.cpp"
  append(L"\n");
  append(L"  var exception = new ParseException(begin, end, -1, -1, -1);\n");
  append(L"  exception.setAmbiguousInput(");
                                                            #line 767 "PrintHaxe.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 1113 "PrintHaxe.cpp"
  append(L"treeBuilder");
                                                            #line 769 "PrintHaxe.cpp.template"
                                                                }
                                                            #line 1117 "PrintHaxe.cpp"
  append(L");\n");
  append(L"  throw exception;\n");
  append(L"}");
                                                            #line 772 "PrintHaxe.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 1125 "PrintHaxe.cpp"
  append(L"\n");
  append(L"private function resolve(thread: ParsingThread, other: ParsingThread): ParsingThread\n");
  append(L"{");
                                                            #line 777 "PrintHaxe.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 1132 "PrintHaxe.cpp"
  append(L"\n");
  append(L"  var a = thread.stack;\n");
  append(L"  var b = other.stack;\n");
  append(L"  var begin = a.pos;\n");
  append(L"  while (a != b && a != null && b != null)\n");
  append(L"  {\n");
  append(L"    begin = a.pos;\n");
  append(L"    a = a.link;\n");
  append(L"    b = b.link;\n");
  append(L"  }");
                                                            #line 788 "PrintHaxe.cpp.template"
                                                                }
                                                            #line 1145 "PrintHaxe.cpp"
  append(L"\n");
                                                            #line 790 "PrintHaxe.cpp.template"
                                                                if (shiftAmbiguity)
                                                                {
                                                            #line 1150 "PrintHaxe.cpp"
  append(L"\n");
  append(L"  var ea = thread.deferredEvent;\n");
  append(L"  var eb = other.deferredEvent;\n");
  append(L"  var ua: DeferredEvent = null;\n");
  append(L"  var ub: DeferredEvent = null;\n");
  append(L"  while (ea != eb)\n");
  append(L"  {\n");
  append(L"    if ((ea == null ? 0 : ea.depth) >= (eb == null ? 0 : eb.depth))\n");
  append(L"    {\n");
  append(L"      ua = ea;\n");
  append(L"      ea = ea.link;\n");
  append(L"    }\n");
  append(L"    else\n");
  append(L"    {\n");
  append(L"      ub = eb;\n");
  append(L"      eb = eb.link;\n");
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
                                                            #line 818 "PrintHaxe.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1182 "PrintHaxe.cpp"
  append(L"\n");
  append(L"  if (other.eventCount < thread.eventCount)\n");
  append(L"    thread = other;");
                                                            #line 823 "PrintHaxe.cpp.template"
                                                                }
                                                                if (tree)
                                                                {
                                                            #line 1190 "PrintHaxe.cpp"
  append(L"\n");
  append(L"  thread.addAmbiguity(begin, thread.e0);");
                                                            #line 827 "PrintHaxe.cpp.template"
                                                                }
                                                            #line 1195 "PrintHaxe.cpp"
  append(L"\n");
  append(L"  return thread;\n");
  append(L"}");
                                                            #line 830 "PrintHaxe.cpp.template"
                                                              }
                                                            #line 1201 "PrintHaxe.cpp"
  append(L"\n");
  append(L"\n");
  append(L"private var thread: ParsingThread;");
                                                            #line 833 "PrintHaxe.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 1208 "PrintHaxe.cpp"
  append(L"\n");
  append(L"private var eventHandler: BottomUpEventHandler;");
                                                            #line 836 "PrintHaxe.cpp.template"
                                                              }
                                                            #line 1213 "PrintHaxe.cpp"
  append(L"\n");
  append(L"public var input: Bytes = null;\n");
  append(L"public var size = 0;\n");
  append(L"public var maxId = 0;");
                                                            #line 840 "PrintHaxe.cpp.template"
                                                              setIndent(1);
                                                            }

                                                            void PrintHaxe::openMethod(const wchar_t *type,
                                                                                       const wchar_t *prefix,
                                                                                       const wchar_t *name,
                                                                                       const wchar_t *args,
                                                                                       bool constant,
                                                                                       const wchar_t *clazz)
                                                            {
                                                            #line 1229 "PrintHaxe.cpp"
  append(L"\n");
                                                            #line 851 "PrintHaxe.cpp.template"
                                                              print(visibility);
                                                            #line 1233 "PrintHaxe.cpp"
  append(L" ");
                                                            #line 852 "PrintHaxe.cpp.template"
                                                              print(prefix);
                                                            #line 1237 "PrintHaxe.cpp"
  append(L"function ");
                                                            #line 853 "PrintHaxe.cpp.template"
                                                              print(name);
                                                            #line 1241 "PrintHaxe.cpp"
  append(L"(");
                                                            #line 854 "PrintHaxe.cpp.template"
                                                              bool ignore = true;
                                                              for (const wchar_t *a = args; *a; ++a)
                                                              {
                                                                if (! ignore)
                                                                {
                                                                  print(*a);
                                                                }
                                                                if (*a == ' ')
                                                                {
                                                                  ignore = ! ignore;
                                                                }
                                                              }
                                                            #line 1256 "PrintHaxe.cpp"
  append(L")");
                                                            #line 866 "PrintHaxe.cpp.template"
                                                              if (*type) // && wcscmp(type, L"void "))
                                                              {
                                                            #line 1261 "PrintHaxe.cpp"
  append(L": ");
                                                            #line 868 "PrintHaxe.cpp.template"
                                                                print(towupper(*type));
                                                                print(type + 1);
                                                              }
                                                            }

                                                            void PrintHaxe::privateVars()
                                                            {
                                                              if (trace)
                                                              {
                                                            #line 1273 "PrintHaxe.cpp"
  append(L"\n");
  append(L"  private function lookaheadString()\n");
  append(L"  {\n");
  append(L"    var result = \"\";\n");
  append(L"    if (");
                                                            #line 881 "PrintHaxe.cpp.template"
                                                                print(thiz());
                                                            #line 1281 "PrintHaxe.cpp"
  append(L"l1 > 0)\n");
  append(L"    {\n");
  append(L"      result += ");
                                                            #line 884 "PrintHaxe.cpp.template"
                                                                print(staticPrefix());
                                                            #line 1287 "PrintHaxe.cpp"
  append(L"TOKEN[");
                                                            #line 885 "PrintHaxe.cpp.template"
                                                                print(thiz());
                                                            #line 1291 "PrintHaxe.cpp"
  append(L"l1];");
                                                            #line 886 "PrintHaxe.cpp.template"
                                                                for (size_t i = 2; i <= grammar->k; ++i)
                                                                {
                                                            #line 1296 "PrintHaxe.cpp"
  append(L"\n");
  append(L"      if (");
                                                            #line 889 "PrintHaxe.cpp.template"
                                                                  print(thiz());
                                                            #line 1301 "PrintHaxe.cpp"
  append(L"l");
                                                            #line 890 "PrintHaxe.cpp.template"
                                                                  print(format.toString<wchar_t>(i));
                                                            #line 1305 "PrintHaxe.cpp"
  append(L" > 0)\n");
  append(L"      {\n");
  append(L"        result += \" \" + ");
                                                            #line 893 "PrintHaxe.cpp.template"
                                                                  print(staticPrefix());
                                                            #line 1311 "PrintHaxe.cpp"
  append(L"TOKEN[");
                                                            #line 894 "PrintHaxe.cpp.template"
                                                                  print(thiz());
                                                            #line 1315 "PrintHaxe.cpp"
  append(L"l");
                                                            #line 895 "PrintHaxe.cpp.template"
                                                                  print(format.toString<wchar_t>(i));
                                                            #line 1319 "PrintHaxe.cpp"
  append(L"];");
                                                            #line 896 "PrintHaxe.cpp.template"
                                                                  increaseIndent();
                                                                }
                                                                for (size_t i = 2; i <= grammar->k; ++i)
                                                                {
                                                                  decreaseIndent();
                                                            #line 1327 "PrintHaxe.cpp"
  append(L"\n");
  append(L"      }");
                                                            #line 902 "PrintHaxe.cpp.template"
                                                                }
                                                            #line 1332 "PrintHaxe.cpp"
  append(L"\n");
  append(L"    }\n");
  append(L"    return result;\n");
  append(L"  }\n");
                                                            #line 907 "PrintHaxe.cpp.template"
                                                              }

                                                              if (memoization)
                                                              {
                                                                int bits = Math::bits(grammar->conflictCount);
                                                            #line 1343 "PrintHaxe.cpp"
  append(L"\n");
  append(L"  private function memoize(i, e, v)\n");
  append(L"  {\n");
  append(L"    memo.set((e << ");
                                                            #line 915 "PrintHaxe.cpp.template"
                                                                print(format.toString<wchar_t>(bits));
                                                            #line 1350 "PrintHaxe.cpp"
  append(L") + i, v);\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  private function memoized(i, e): Int\n");
  append(L"  {\n");
  append(L"    var v = memo.get((e << ");
                                                            #line 921 "PrintHaxe.cpp.template"
                                                                print(format.toString<wchar_t>(bits));
                                                            #line 1359 "PrintHaxe.cpp"
  append(L") + i);\n");
  append(L"    return v == null ? 0 : v;\n");
  append(L"  }\n");
                                                            #line 925 "PrintHaxe.cpp.template"
                                                              }
                                                            #line 1365 "PrintHaxe.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 927 "PrintHaxe.cpp.template"
                                                              if (! isLrParser && (grammar->k > 1 ||
                                                                                   memoization ||
                                                                                   ! grammar->decisionPoints.empty()))
                                                              {
                                                            #line 1373 "PrintHaxe.cpp"
  append(L"private var lk: Int; ");
                                                            #line 931 "PrintHaxe.cpp.template"
                                                              }
                                                              else if (! useGlr)
                                                              {
                                                            #line 1379 "PrintHaxe.cpp"
  append(L"                     ");
                                                            #line 934 "PrintHaxe.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 1385 "PrintHaxe.cpp"
  append(L"                    ");
                                                            #line 937 "PrintHaxe.cpp.template"
                                                              }
                                                              const wchar_t *visibility = useGlr ? L"public" : L"private";
                                                              print(visibility);
                                                            #line 1391 "PrintHaxe.cpp"
  append(L" var b0: Int; ");
                                                            #line 940 "PrintHaxe.cpp.template"
                                                              print(visibility);
                                                            #line 1395 "PrintHaxe.cpp"
  append(L" var e0: Int;");
                                                            #line 941 "PrintHaxe.cpp.template"
                                                              for (size_t k = 1; k <= grammar->k; ++k)
                                                              {
                                                                Format format;
                                                                wchar_t *asString = format.toString<wchar_t>(k);
                                                            #line 1402 "PrintHaxe.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 946 "PrintHaxe.cpp.template"
                                                                print(visibility);
                                                            #line 1407 "PrintHaxe.cpp"
  append(L" var l");
                                                            #line 947 "PrintHaxe.cpp.template"
                                                                print(asString);
                                                            #line 1411 "PrintHaxe.cpp"
  append(L": Int; ");
                                                            #line 948 "PrintHaxe.cpp.template"
                                                                print(visibility);
                                                            #line 1415 "PrintHaxe.cpp"
  append(L" var b");
                                                            #line 949 "PrintHaxe.cpp.template"
                                                                print(asString);
                                                            #line 1419 "PrintHaxe.cpp"
  append(L": Int; ");
                                                            #line 950 "PrintHaxe.cpp.template"
                                                                print(visibility);
                                                            #line 1423 "PrintHaxe.cpp"
  append(L" var e");
                                                            #line 951 "PrintHaxe.cpp.template"
                                                                print(asString);
                                                            #line 1427 "PrintHaxe.cpp"
  append(L": Int;");
                                                            #line 952 "PrintHaxe.cpp.template"
                                                              }
                                                              if (hasBacktracking)
                                                              {
                                                            #line 1433 "PrintHaxe.cpp"
  append(L"\n");
  append(L"  private var bx: Int;\n");
  append(L"  private var ex: Int;\n");
  append(L"  private var sx: Int;\n");
  append(L"  private var lx: Int;\n");
  append(L"  private var tx: Int;");
                                                            #line 960 "PrintHaxe.cpp.template"
                                                              }
                                                              if (isLrParser && ! useGlr)
                                                              {
                                                            #line 1444 "PrintHaxe.cpp"
  append(L"\n");
  append(L"  private var iStack = [];\n");
  append(L"  private var top = -1;");
                                                            #line 965 "PrintHaxe.cpp.template"
                                                              }
                                                              if (useGlr)
                                                              {
                                                            #line 1452 "PrintHaxe.cpp"
  append(L"\n");
  append(L"  private var bw: Int;\n");
  append(L"  private var bs: Int;");
                                                            #line 970 "PrintHaxe.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                                if (isLrParser)
                                                                {
                                                                  if (useGlr)
                                                                  {
                                                            #line 1464 "PrintHaxe.cpp"
  append(L"\n");
  append(L"  private var es: Int;");
                                                            #line 978 "PrintHaxe.cpp.template"
                                                                  }
                                                            #line 1469 "PrintHaxe.cpp"
  append(L"\n");
  append(L"  private var eventHandler: BottomUpEventHandler = null;");
                                                            #line 980 "PrintHaxe.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1476 "PrintHaxe.cpp"
  append(L"\n");
  append(L"  private var eventHandler: EventHandler = null;");
                                                            #line 984 "PrintHaxe.cpp.template"
                                                                }
                                                              }
                                                              if (memoization)
                                                              {
                                                            #line 1484 "PrintHaxe.cpp"
  append(L"\n");
  append(L"  private var memo: Map<Int, Int>  = new Map();");
                                                            #line 989 "PrintHaxe.cpp.template"
                                                                if (grammar->noThrow)
                                                                {
                                                            #line 1490 "PrintHaxe.cpp"
  append(L"\n");
  append(L"  private var viable: Bool;");
                                                            #line 992 "PrintHaxe.cpp.template"
                                                                }
                                                              }
                                                            }

                                                            void PrintHaxe::printFileProcessor()
                                                            {
                                                            #line 1500 "PrintHaxe.cpp"
  append(L"\n");
  append(L"  private static var quiet = false;\n");
  append(L"  private static var parsed = 0;\n");
  append(L"  private static var errorCount = 0;\n");
  append(L"  private static var parsers = new List<ParseJob>();\n");
  append(L"\n");
  append(L"  public static function main()\n");
  append(L"  {\n");
  append(L"    var args = Sys.args();\n");
  append(L"\n");
  append(L"    if (args.length == 0)\n");
  append(L"    {\n");
  append(L"      Sys.println(\"Usage: ");
                                                            #line 1010 "PrintHaxe.cpp.template"
                                                              print(className.c_str());
                                                            #line 1516 "PrintHaxe.cpp"
  append(L" [-q] [-r N] [-t N] ENDING...\\n\");\n");
  append(L"      Sys.println(\"  parse all files that have names ending with ENDING, in current dir and below,\");\n");
  append(L"      Sys.println(\"  and display performance summary.\\n\");\n");
  append(L"      Sys.println(\"  -q     do not show file names\");\n");
  append(L"      Sys.println(\"  -r N   repeat N times\");\n");
  append(L"      Sys.println(\"  -t N   repeat until N seconds have elapsed\");\n");
  append(L"    }\n");
  append(L"    else\n");
  append(L"    {\n");
  append(L"      var repeat = 1;\n");
  append(L"      var timeout = 0;\n");
  append(L"      var i = 0;\n");
  append(L"      while (i < args.length && StringTools.startsWith(args[i], \"-\"))\n");
  append(L"      {\n");
  append(L"        switch (args[i].length == 2 ? args[i].charAt(1) : ' ')\n");
  append(L"        {\n");
  append(L"        case 'q':\n");
  append(L"          quiet = true;\n");
  append(L"        case 'r':\n");
  append(L"          repeat = Std.parseInt(args[++i]);\n");
  append(L"          timeout = 0;\n");
  append(L"        case 't':\n");
  append(L"          repeat = 0;\n");
  append(L"          timeout = 1000 * Std.parseInt(args[++i]);\n");
  append(L"        default:\n");
  append(L"          throw \"invalid option: \" + args[i];\n");
  append(L"        }\n");
  append(L"        ++i;\n");
  append(L"      }\n");
  append(L"\n");
  append(L"      var start = Date.now().getTime();\n");
  append(L"\n");
  append(L"      while (i < args.length)\n");
  append(L"      {\n");
  append(L"        findFiles(\".\", args[i]);\n");
  append(L"        ++i;\n");
  append(L"      }\n");
  append(L"\n");
  append(L"      if (! parsers.isEmpty())\n");
  append(L"      {\n");
  append(L"        var msec = Date.now().getTime() - start;\n");
  append(L"\n");
  append(L"        if (! quiet) Sys.println(\"\");\n");
  append(L"        Sys.println(\"loaded \" + parsers.length + \" file\" +\n");
  append(L"                    (parsers.length == 1 ? \"\" : \"s\") + \" in \" +\n");
  append(L"                    msec + \" msec\");\n");
  append(L"        if (! quiet) Sys.println(\"\");\n");
  append(L"\n");
  append(L"        start = Date.now().getTime();\n");
  append(L"        i = 0;\n");
  append(L"        while (true)\n");
  append(L"        {\n");
  append(L"          if (repeat != 0 && i >= repeat) break;\n");
  append(L"          if (timeout != 0 && Date.now().getTime() - start >= timeout) break;\n");
  append(L"\n");
  append(L"          for (job in parsers)\n");
  append(L"          {\n");
  append(L"            if (job.parser != null)\n");
  append(L"            {\n");
  append(L"              try\n");
  append(L"              {\n");
  append(L"                if (! quiet) Sys.print(\"parsing \" + job.name);\n");
  append(L"                job.parser");
                                                            #line 1073 "PrintHaxe.cpp.template"
                                                              if (useGlr)
                                                              {
                                                            #line 1583 "PrintHaxe.cpp"
  append(L".thread");
                                                            #line 1075 "PrintHaxe.cpp.template"
                                                              }
                                                            #line 1587 "PrintHaxe.cpp"
  append(L".reset(0, 0, 0);\n");
  append(L"                job.parser.");
                                                            #line 1077 "PrintHaxe.cpp.template"
                                                              print(methodPrefixParse);
                                                              print(Format::acceptableName<WString>(grammar->startSymbol()->name).c_str());
                                                            #line 1593 "PrintHaxe.cpp"
  append(L"();\n");
  append(L"                if (! quiet) Sys.println(\"\");");
                                                            #line 1080 "PrintHaxe.cpp.template"
                                                              if (tree)
                                                              {
                                                                if (isLrParser)
                                                                {
                                                            #line 1601 "PrintHaxe.cpp"
  append(L"\n");
  append(L"                job.parseTreeBuilder.serialize(job.contentCounter);");
                                                            #line 1086 "PrintHaxe.cpp.template"
                                                                }
                                                            #line 1606 "PrintHaxe.cpp"
  append(L"\n");
  append(L"                if (job.contentCounter.getLength() != job.input.length)\n");
  append(L"                {\n");
  append(L"                  throw \"content counter saw \" + job.contentCounter.getLength() + \", but input length is \" + job.input.length;\n");
  append(L"                }");
                                                            #line 1091 "PrintHaxe.cpp.template"
                                                              }
                                                            #line 1614 "PrintHaxe.cpp"
  append(L"\n");
  append(L"                parsed += job.input.length;\n");
  append(L"              }\n");
  append(L"              catch (pe: ParseException)\n");
  append(L"              {\n");
  append(L"                ++errorCount;\n");
  append(L"                if (quiet) Sys.print(\"parsing \" + job.name);\n");
  append(L"                Sys.println(\": error: \" + job.parser.getErrorMessage(pe));\n");
  append(L"                job.parser = null;\n");
  append(L"              }\n");
  append(L"            }\n");
  append(L"          }\n");
  append(L"          ++i;\n");
  append(L"        }\n");
  append(L"        msec = Date.now().getTime() - start;\n");
  append(L"        var mbPerSec = msec == 0\n");
  append(L"                     ? null\n");
  append(L"                     : Math.round(parsed / 1024e0 / 1024e0 * 1000e0 / msec * 100e0) / 100e0;\n");
  append(L"\n");
  append(L"        if (! quiet) Sys.println(\"\");\n");
  append(L"        Sys.print(\"parsed \" + parsed + \" byte\" + (parsed == 1 ? \"\" : \"s\") +\n");
  append(L"                  \" in \" + msec + \" msec\");\n");
  append(L"        if (mbPerSec != null)\n");
  append(L"        {\n");
  append(L"          Sys.print(\" (\" + mbPerSec + \" MB/sec)\");\n");
  append(L"        }\n");
  append(L"        Sys.println(\"\");\n");
  append(L"        Sys.println(errorCount + \" error\" + (errorCount == 1 ? \"\" : \"s\"));\n");
  append(L"      }\n");
  append(L"    }\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  private static function collectInput(name, content)\n");
  append(L"  {\n");
  append(L"    if (! quiet) Sys.println(\"loading \" + name);\n");
  append(L"    parsers.add(new ParseJob(name, content));\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  private static function findFiles(f, filter)\n");
  append(L"  {\n");
  append(L"    if (FileSystem.isDirectory(f))\n");
  append(L"    {\n");
  append(L"      var files = FileSystem.readDirectory(f);\n");
  append(L"      if (files != null)\n");
  append(L"      {\n");
  append(L"        for (file in files)\n");
  append(L"        {\n");
  append(L"          findFiles(f + \"/\" + file, filter);\n");
  append(L"        }\n");
  append(L"      }\n");
  append(L"    }\n");
  append(L"    else if (StringTools.endsWith(f.toLowerCase(), filter.toLowerCase()))\n");
  append(L"    {\n");
  append(L"      collectInput(f, read(f));\n");
  append(L"    }\n");
  append(L"  }\n");
                                                            #line 1148 "PrintHaxe.cpp.template"
                                                            }

                                                            void PrintHaxe::printReadMethod()
                                                            {
                                                              if (main || performanceTest)
                                                              {
                                                            #line 1678 "PrintHaxe.cpp"
  append(L"\n");
  append(L"  private static function read(input)\n");
  append(L"  {\n");
  append(L"    if (");
                                                            #line 1157 "PrintHaxe.cpp.template"
                                                                print(L"~/^");
                                                            #line 1685 "PrintHaxe.cpp"
  append(L"\\{.*\\}$/g.match(input))\n");
  append(L"    {\n");
  append(L"      return input.substring(1, input.length - 1);\n");
  append(L"    }\n");
  append(L"    else\n");
  append(L"    {\n");
  append(L"      var content = File.getContent(input);\n");
  append(L"      return content.length > 0 && content.charCodeAt(0) == 0xFEFF\n");
  append(L"           ? content.substring(1)\n");
  append(L"           : content;\n");
  append(L"    }\n");
  append(L"  }\n");
                                                            #line 1170 "PrintHaxe.cpp.template"
                                                                //      if (content.length() > 0 && content.charAt(0) == '\uFEFF')
                                                                //      {
                                                                //        content = content.substring(1);
                                                                //      }
                                                                //      return content.replace("\r\n", "\n");
                                                              }
                                                            }

                                                            void PrintHaxe::printInterface()
                                                            {
                                                              if (! packageName.empty())
                                                              {
                                                            #line 1711 "PrintHaxe.cpp"
  append(L"\n");
  append(L"package ");
                                                            #line 1183 "PrintHaxe.cpp.template"
                                                                print(packageName.c_str());
                                                            #line 1716 "PrintHaxe.cpp"
  append(L";\n");
                                                            #line 1185 "PrintHaxe.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                                if (main)
                                                                {
                                                            #line 1724 "PrintHaxe.cpp"
  append(L"\n");
  append(L"import java.io.IOException;\n");
  append(L"import java.io.Writer;\n");
                                                            #line 1193 "PrintHaxe.cpp.template"
                                                                }
                                                              }
                                                            #line 1731 "PrintHaxe.cpp"
  append(L"\n");
  append(L"public interface ");
                                                            #line 1196 "PrintHaxe.cpp.template"
                                                              print(className.c_str());
                                                            #line 1736 "PrintHaxe.cpp"
  append(L"\n");
  append(L"{\n");
  append(L"  public void initialize(CharSequence input");
                                                            #line 1199 "PrintHaxe.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 1743 "PrintHaxe.cpp"
  append(L", EventHandler eh");
                                                            #line 1202 "PrintHaxe.cpp.template"
                                                              }
                                                            #line 1747 "PrintHaxe.cpp"
  append(L");\n");
  append(L"  public void parse();\n");
  append(L"  public void reset();\n");
  append(L"  public String getErrorMessage(ParseException e);\n");
                                                            #line 1207 "PrintHaxe.cpp.template"
                                                              printParseException();
                                                            #line 1754 "PrintHaxe.cpp"
  append(L"}\n");
                                                            #line 1209 "PrintHaxe.cpp.template"
                                                            }

                                                            void PrintHaxe::printParseException()
                                                            {
                                                            #line 1761 "PrintHaxe.cpp"
  append(L"\n");
  append(L"class ParseException\n");
  append(L"{\n");
  append(L"  private var begin: Int;\n");
  append(L"  private var end: Int;\n");
  append(L"  private var state: Int;\n");
  append(L"  private var offending: Int;\n");
  append(L"  private var expected: Int;");
                                                            #line 1220 "PrintHaxe.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 1773 "PrintHaxe.cpp"
  append(L"\n");
  append(L"  private var ambiguousInput: Bool;");
                                                            #line 1223 "PrintHaxe.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 1779 "PrintHaxe.cpp"
  append(L"\n");
  append(L"  private var ambiguityDescriptor: ParseTreeBuilder;");
                                                            #line 1226 "PrintHaxe.cpp.template"
                                                                }
                                                              }
                                                            #line 1785 "PrintHaxe.cpp"
  append(L"\n");
  append(L"\n");
  append(L"  public function new(b, e, s, o, x)\n");
  append(L"  {\n");
  append(L"    begin = b;\n");
  append(L"    end = e;\n");
  append(L"    state = s;\n");
  append(L"    offending = o;\n");
  append(L"    expected = x;\n");
  append(L"  }\n");
                                                            #line 1238 "PrintHaxe.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 1799 "PrintHaxe.cpp"
  append(L"\n");
  append(L"  public function setAmbiguousInput(");
                                                            #line 1241 "PrintHaxe.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 1805 "PrintHaxe.cpp"
  append(L"a");
                                                            #line 1243 "PrintHaxe.cpp.template"
                                                                }
                                                            #line 1809 "PrintHaxe.cpp"
  append(L")\n");
  append(L"  {\n");
  append(L"    ambiguousInput = true;");
                                                            #line 1246 "PrintHaxe.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 1816 "PrintHaxe.cpp"
  append(L"\n");
  append(L"    ambiguityDescriptor = a;");
                                                            #line 1249 "PrintHaxe.cpp.template"
                                                                }
                                                            #line 1821 "PrintHaxe.cpp"
  append(L"\n");
  append(L"  }\n");
                                                            #line 1252 "PrintHaxe.cpp.template"
                                                              }
                                                            #line 1826 "PrintHaxe.cpp"
  append(L"\n");
  append(L"  public function getBegin() {return begin;}\n");
  append(L"  public function getEnd() {return end;}\n");
  append(L"  public function getState() {return state;}\n");
  append(L"  public function getExpected() {return expected;}\n");
  append(L"  public function getOffending() {return offending;}\n");
  append(L"  public function isAmbiguousInput() {return ");
                                                            #line 1259 "PrintHaxe.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 1837 "PrintHaxe.cpp"
  append(L"ambiguousInput");
                                                            #line 1261 "PrintHaxe.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 1843 "PrintHaxe.cpp"
  append(L"false");
                                                            #line 1264 "PrintHaxe.cpp.template"
                                                              }
                                                            #line 1847 "PrintHaxe.cpp"
  append(L";}\n");
  append(L"\n");
  append(L"  public function getMessage()\n");
  append(L"  {\n");
  append(L"    return ");
                                                            #line 1269 "PrintHaxe.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 1856 "PrintHaxe.cpp"
  append(L"ambiguousInput\n");
  append(L"         ? \"ambiguous input\"\n");
  append(L"         : ");
                                                            #line 1273 "PrintHaxe.cpp.template"
                                                              }
                                                            #line 1862 "PrintHaxe.cpp"
  append(L"offending < 0\n");
  append(L"         ? \"lexical analysis failed\"\n");
  append(L"         : \"syntax error\";\n");
  append(L"  }");
                                                            #line 1277 "PrintHaxe.cpp.template"
                                                              if (rejectsAmbiguity() && tree)
                                                              {
                                                            #line 1870 "PrintHaxe.cpp"
  append(L"\n");
  append(L"\n");
  append(L"  public function serialize(eventHandler)\n");
  append(L"  {\n");
  append(L"    ambiguityDescriptor.serialize(eventHandler);\n");
  append(L"  }");
                                                            #line 1284 "PrintHaxe.cpp.template"
                                                              }
                                                            #line 1879 "PrintHaxe.cpp"
  append(L"\n");
  append(L"}\n");
                                                            #line 1287 "PrintHaxe.cpp.template"
                                                              if (noLexer)
                                                              {
                                                            #line 1885 "PrintHaxe.cpp"
  append(L"\n");
  append(L"  public class Token\n");
  append(L"  {\n");
  append(L"    public int code;\n");
  append(L"    public int begin;\n");
  append(L"    public int end;\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  public interface Lexer\n");
  append(L"  {\n");
  append(L"    void reset(CharSequence input);\n");
  append(L"    void match(int tokenset, Token token);\n");
  append(L"  }\n");
                                                            #line 1302 "PrintHaxe.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                            #line 1903 "PrintHaxe.cpp"
  append(L"\n");
  append(L"interface EventHandler\n");
  append(L"{\n");
  append(L"  public function reset(input: Bytes): Void;\n");
  append(L"  public function startNonterminal(tag: String, begin: Int): Void;\n");
  append(L"  public function endNonterminal(tag: String, end: Int): Void;\n");
  append(L"  public function terminal(tag: String, begin: Int, end: Int): Void;\n");
  append(L"  public function whitespace(begin: Int, end: Int): Void;\n");
  append(L"}\n");
                                                            #line 1314 "PrintHaxe.cpp.template"
                                                                if (isLrParser)
                                                                {
                                                            #line 1916 "PrintHaxe.cpp"
  append(L"\n");
  append(L"interface BottomUpEventHandler\n");
  append(L"{\n");
  append(L"  public function reset(input: Bytes): Void;\n");
  append(L"  public function nonterminal(name: String, begin: Int, end: Int, count: Int): Void;\n");
  append(L"  public function terminal(name: String , begin: Int, end: Int): Void;");
                                                            #line 1322 "PrintHaxe.cpp.template"
                                                                  if (resolvesAmbiguity)
                                                                  {
                                                            #line 1926 "PrintHaxe.cpp"
  append(L"\n");
  append(L"  public function ambiguity(begin: Int, end: Int): Void;");
                                                            #line 1325 "PrintHaxe.cpp.template"
                                                                  }
                                                            #line 1931 "PrintHaxe.cpp"
  append(L"\n");
  append(L"}\n");
                                                            #line 1328 "PrintHaxe.cpp.template"
                                                                }
                                                                #if EXPATH_EXTENSION_FUNCTION
                                                            #line 1937 "PrintHaxe.cpp"
  append(L"\n");
  append(L"class XmlTreeBuilder implements EventHandler\n");
  append(L"{\n");
  append(L"  var input: Bytes = null;\n");
  append(L"  var node: Xml;\n");
  append(L"\n");
  append(L"  public function new() {}\n");
  append(L"\n");
  append(L"  public function getTree()\n");
  append(L"  {\n");
  append(L"    return node;\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  public function reset(bytes)\n");
  append(L"  {\n");
  append(L"    input = bytes;\n");
  append(L"    node = Xml.createDocument();\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  public function startNonterminal(tag, begin)\n");
  append(L"  {\n");
  append(L"    var element = Xml.createElement(tag);\n");
  append(L"    node.addChild(element);\n");
  append(L"    node = element;\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  public function endNonterminal(tag: String, end: Int): Void\n");
  append(L"  {\n");
  append(L"    node = node.parent;\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  public function terminal(tag: String, begin: Int, end: Int): Void\n");
  append(L"  {\n");
  append(L"    if (tag.charAt(0) == '\\'') tag = \"TOKEN\";\n");
  append(L"    startNonterminal(tag, begin);\n");
  append(L"    characters(begin, end);\n");
  append(L"    endNonterminal(tag, end);\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  public function whitespace(begin: Int, end: Int): Void\n");
  append(L"  {\n");
  append(L"    characters(begin, end);\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  private function characters(begin, end): Void\n");
  append(L"  {\n");
  append(L"    node.addChild(Xml.createPCData(input.getString(begin, end - begin)));\n");
  append(L"  }\n");
  append(L"}\n");
                                                            #line 1379 "PrintHaxe.cpp.template"
                                                                #endif
                                                                if (main)
                                                                {
                                                                }
                                                              }
                                                              if (performanceTest)
                                                              {
                                                            #line 1995 "PrintHaxe.cpp"
  append(L"\n");
  append(L"class ParseJob\n");
  append(L"{\n");
  append(L"  public var name: String;\n");
  append(L"  public var input: String;\n");
  append(L"  public var parser: ");
                                                            #line 1392 "PrintHaxe.cpp.template"
                                                                print(className.c_str());
                                                            #line 2004 "PrintHaxe.cpp"
  append(L";");
                                                            #line 1393 "PrintHaxe.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 2009 "PrintHaxe.cpp"
  append(L"\n");
  append(L"  public var contentCounter: ContentCounter;");
                                                            #line 1396 "PrintHaxe.cpp.template"
                                                                  if (isLrParser)
                                                                  {
                                                            #line 2015 "PrintHaxe.cpp"
  append(L"\n");
  append(L"  public var parseTreeBuilder: ParseTreeBuilder;");
                                                            #line 1399 "PrintHaxe.cpp.template"
                                                                  }
                                                                }
                                                            #line 2021 "PrintHaxe.cpp"
  append(L"\n");
  append(L"  public function new(s: String, i: String)\n");
  append(L"  {\n");
  append(L"    name = s;\n");
  append(L"    input = i;");
                                                            #line 1405 "PrintHaxe.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 2030 "PrintHaxe.cpp"
  append(L"\n");
  append(L"    contentCounter = new ContentCounter();");
                                                            #line 1408 "PrintHaxe.cpp.template"
                                                                  if (isLrParser)
                                                                  {
                                                            #line 2036 "PrintHaxe.cpp"
  append(L"\n");
  append(L"    parseTreeBuilder = new ParseTreeBuilder();");
                                                            #line 1411 "PrintHaxe.cpp.template"
                                                                  }
                                                                }
                                                            #line 2042 "PrintHaxe.cpp"
  append(L"\n");
  append(L"    parser = new ");
                                                            #line 1414 "PrintHaxe.cpp.template"
                                                                print(className.c_str());
                                                            #line 2047 "PrintHaxe.cpp"
  append(L"(input");
                                                            #line 1415 "PrintHaxe.cpp.template"
                                                                if (noLexer)
                                                                {
                                                            #line 2052 "PrintHaxe.cpp"
  append(L", null");
                                                            #line 1417 "PrintHaxe.cpp.template"
                                                                }
                                                                if (tree)
                                                                {
                                                                  if (isLrParser)
                                                                  {
                                                            #line 2060 "PrintHaxe.cpp"
  append(L", parseTreeBuilder");
                                                            #line 1422 "PrintHaxe.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 2066 "PrintHaxe.cpp"
  append(L", contentCounter");
                                                            #line 1425 "PrintHaxe.cpp.template"
                                                                  }
                                                                }
                                                            #line 2071 "PrintHaxe.cpp"
  append(L");\n");
  append(L"  }\n");
  append(L"}\n");
                                                            #line 1430 "PrintHaxe.cpp.template"
                                                              }
                                                            }

                                                            void PrintHaxe::printEventHandlerImplementation()
                                                            {
                                                              if (tree)
                                                              {
                                                                if (main)
                                                                {
                                                            #line 2085 "PrintHaxe.cpp"
  append(L"\n");
  append(L"class XmlSerializer implements EventHandler\n");
  append(L"{\n");
  append(L"  var input: Bytes = null;\n");
  append(L"  var delayedTag: String = null;\n");
  append(L"  var indent = false;\n");
  append(L"  var hasChildElement = false;\n");
  append(L"  var depth = 0;\n");
  append(L"\n");
  append(L"  public function new(indent)\n");
  append(L"  {\n");
  append(L"    this.indent = indent;\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  public function reset(bytes)\n");
  append(L"  {\n");
  append(L"    Sys.print(\"<?xml version=\\\"1.0\\\" encoding=\\\"UTF-8\\\"?\" + \">\");\n");
  append(L"    input = bytes;\n");
  append(L"    delayedTag = null;\n");
  append(L"    hasChildElement = false;\n");
  append(L"    depth = 0;\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  public function startNonterminal(tag, begin)\n");
  append(L"  {\n");
  append(L"    if (delayedTag != null)\n");
  append(L"    {\n");
  append(L"      Sys.print(\"<\");\n");
  append(L"      Sys.print(delayedTag);\n");
  append(L"      Sys.print(\">\");\n");
  append(L"    }\n");
  append(L"    delayedTag = tag;\n");
  append(L"    if (indent)\n");
  append(L"    {\n");
  append(L"      Sys.print(\"\\n\");\n");
  append(L"      for (i in 0...depth)\n");
  append(L"      {\n");
  append(L"        Sys.print(\"  \");\n");
  append(L"      }\n");
  append(L"    }\n");
  append(L"    hasChildElement = false;\n");
  append(L"    ++depth;\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  public function endNonterminal(tag, end)\n");
  append(L"  {\n");
  append(L"    --depth;\n");
  append(L"    if (delayedTag != null)\n");
  append(L"    {\n");
  append(L"      delayedTag = null;\n");
  append(L"      Sys.print(\"<\");\n");
  append(L"      Sys.print(tag);\n");
  append(L"      Sys.print(\"/>\");\n");
  append(L"    }\n");
  append(L"    else\n");
  append(L"    {\n");
  append(L"      if (indent)\n");
  append(L"      {\n");
  append(L"        if (hasChildElement)\n");
  append(L"        {\n");
  append(L"          Sys.print(\"\\n\");\n");
  append(L"          for (i in 0...depth)\n");
  append(L"          {\n");
  append(L"            Sys.print(\"  \");\n");
  append(L"          }\n");
  append(L"        }\n");
  append(L"      }\n");
  append(L"      Sys.print(\"</\");\n");
  append(L"      Sys.print(tag);\n");
  append(L"      Sys.print(\">\");\n");
  append(L"    }\n");
  append(L"    hasChildElement = true;\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  public function terminal(tag: String, begin, end)\n");
  append(L"  {\n");
  append(L"    if (tag.charAt(0) == '\\'') tag = \"TOKEN\";\n");
  append(L"    startNonterminal(tag, begin);\n");
  append(L"    characters(begin, end);\n");
  append(L"    endNonterminal(tag, end);\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  public function whitespace(begin, end)\n");
  append(L"  {\n");
  append(L"    characters(begin, end);\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  private function characters(begin, end)\n");
  append(L"  {\n");
  append(L"    if (begin < end)\n");
  append(L"    {\n");
  append(L"      if (delayedTag != null)\n");
  append(L"      {\n");
  append(L"        Sys.print(\"<\");\n");
  append(L"        Sys.print(delayedTag);\n");
  append(L"        Sys.print(\">\");\n");
  append(L"        delayedTag = null;\n");
  append(L"      }\n");
  append(L"      Sys.print(");
  append(L"~");
  append(L"/>/g.replace(\n");
  append(L"                ");
  append(L"~");
  append(L"/</g.replace(\n");
  append(L"                ");
  append(L"~");
  append(L"/&/g.replace(input.getString(begin, end - begin), \"&amp;\")\n");
  append(L"                                                                  , \"&lt;\")\n");
  append(L"                                                                  , \"&gt;\"));\n");
  append(L"    }\n");
  append(L"  }\n");
  append(L"}\n");
                                                            #line 1545 "PrintHaxe.cpp.template"
                                                                }
                                                                if (performanceTest)
                                                                {
                                                            #line 2202 "PrintHaxe.cpp"
  append(L"\n");
  append(L"class ContentCounter implements EventHandler\n");
  append(L"{\n");
  append(L"  private var length = 0;\n");
  append(L"  public function new() {}\n");
  append(L"  public function getLength() {return length;}\n");
  append(L"  public function reset(string) {length = 0;}\n");
  append(L"  public function startNonterminal(name, begin) {}\n");
  append(L"  public function endNonterminal(name, end) {}\n");
  append(L"  public function terminal(name, begin, end) {length += end - begin;}\n");
  append(L"  public function whitespace(begin, end) {length += end - begin;}\n");
  append(L"}\n");
                                                            #line 1560 "PrintHaxe.cpp.template"
                                                                }
                                                            #line 2217 "PrintHaxe.cpp"
  append(L"\n");
  append(L"class TopDownTreeBuilder implements EventHandler\n");
  append(L"{\n");
  append(L"  private var input: Bytes;\n");
  append(L"  private var stack: Array<Nonterminal>;\n");
  append(L"\n");
  append(L"  public function new()\n");
  append(L"  {\n");
  append(L"    input = null;\n");
  append(L"    stack = null;\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  public function reset(i)\n");
  append(L"  {\n");
  append(L"    input = i;\n");
  append(L"    stack = [];\n");
  append(L"  };\n");
  append(L"\n");
  append(L"  public function startNonterminal(name, begin)\n");
  append(L"  {\n");
  append(L"    var nonterminal = new Nonterminal(name, begin, begin, new Array<Symbol>());\n");
  append(L"    if (stack.length > 0) addChild(nonterminal);\n");
  append(L"    stack.push(nonterminal);\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  public function endNonterminal(name, end)\n");
  append(L"  {\n");
  append(L"    stack[stack.length - 1].end = end;\n");
  append(L"    if (stack.length > 1) stack.pop();\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  public function terminal(name, begin, end)\n");
  append(L"  {\n");
  append(L"    addChild(new Terminal(name, begin, end));\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  public function whitespace(begin, end)\n");
  append(L"  {\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  private function addChild(s)\n");
  append(L"  {\n");
  append(L"    var current = stack[stack.length - 1];\n");
  append(L"    current.children.push(s);\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  public function serialize(e: EventHandler)\n");
  append(L"  {\n");
  append(L"    e.reset(input);\n");
  append(L"    stack[0].send(e);\n");
  append(L"  }\n");
  append(L"}\n");
  append(L"\n");
  append(L"class Symbol\n");
  append(L"{\n");
  append(L"  public var name: String;\n");
  append(L"  public var begin: Int;\n");
  append(L"  public var end: Int;\n");
  append(L"\n");
  append(L"  private function new(name, begin, end)\n");
  append(L"  {\n");
  append(L"    this.name = name;\n");
  append(L"    this.begin = begin;\n");
  append(L"    this.end = end;\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  public function send(e: EventHandler) {}\n");
  append(L"}\n");
  append(L"\n");
  append(L"class Terminal extends Symbol\n");
  append(L"{\n");
  append(L"  public function new(name, begin, end)\n");
  append(L"  {\n");
  append(L"    super(name, begin, end);\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  override\n");
  append(L"  public function send(e: EventHandler)\n");
  append(L"  {\n");
  append(L"    e.terminal(name, begin, end);\n");
  append(L"  }\n");
  append(L"}\n");
  append(L"\n");
  append(L"class Nonterminal extends Symbol\n");
  append(L"{\n");
  append(L"  public var children: Array<Symbol>;\n");
  append(L"\n");
  append(L"  public function new(name, begin, end, children)\n");
  append(L"  {\n");
  append(L"    super(name, begin, end);\n");
  append(L"    this.children = children;\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  override\n");
  append(L"  public function send(e: EventHandler)\n");
  append(L"  {\n");
  append(L"    e.startNonterminal(name, begin);\n");
  append(L"    var pos = begin;\n");
  append(L"    for (c in children)\n");
  append(L"    {\n");
  append(L"      if (pos < c.begin) e.whitespace(pos, c.begin);\n");
  append(L"      c.send(e);\n");
  append(L"      pos = c.end;\n");
  append(L"    }\n");
  append(L"    if (pos < end) e.whitespace(pos, end);\n");
  append(L"    e.endNonterminal(name, end);\n");
  append(L"  }\n");
  append(L"}\n");
                                                            #line 1669 "PrintHaxe.cpp.template"
                                                                if (isLrParser)
                                                                {
                                                            #line 2329 "PrintHaxe.cpp"
  append(L"\n");
  append(L"class ParseTreeBuilder implements BottomUpEventHandler\n");
  append(L"{\n");
  append(L"  var input : Bytes;\n");
  append(L"  var stack = new Array<Symbol>();\n");
  append(L"  var top = -1;\n");
  append(L"\n");
  append(L"  public function new() {}\n");
  append(L"\n");
  append(L"  public function reset(input: Bytes)\n");
  append(L"  {\n");
  append(L"    this.input = input;\n");
  append(L"    top = -1;\n");
  append(L"  }\n");
                                                            #line 1685 "PrintHaxe.cpp.template"
                                                                  if (useGlr)
                                                                  {
                                                            #line 2347 "PrintHaxe.cpp"
  append(L"\n");
  append(L"  public function getStack() {return stack;}\n");
  append(L"  public function getTop() {return top;}\n");
                                                            #line 1690 "PrintHaxe.cpp.template"
                                                                  }
                                                            #line 2353 "PrintHaxe.cpp"
  append(L"\n");
  append(L"  public function nonterminal(name: String, begin: Int, end: Int, count: Int)\n");
  append(L"  {");
                                                            #line 1693 "PrintHaxe.cpp.template"
                                                                  if (rejectsAmbiguity())
                                                                  {
                                                            #line 2360 "PrintHaxe.cpp"
  append(L"\n");
  append(L"    if (count > top + 1)\n");
  append(L"    {\n");
  append(L"      var content = pop(top + 1);\n");
  append(L"      nonterminal(\"UNAMBIGUOUS\", begin, content.length == 0 ? end : content[0].begin, 0);\n");
  append(L"      for (symbol in content)\n");
  append(L"      {\n");
  append(L"        push(symbol);\n");
  append(L"      }\n");
  append(L"      count = top + 1;\n");
  append(L"    }");
                                                            #line 1705 "PrintHaxe.cpp.template"
                                                                  }
                                                            #line 2374 "PrintHaxe.cpp"
  append(L"\n");
  append(L"    push(new Nonterminal(name, begin, end, pop(count)));\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  public function terminal(name: String, begin: Int, end: Int)\n");
  append(L"  {\n");
  append(L"    push(new Terminal(name, begin, end));\n");
  append(L"  }");
                                                            #line 1713 "PrintHaxe.cpp.template"
                                                                  if (resolvesAmbiguity)
                                                                  {
                                                            #line 2386 "PrintHaxe.cpp"
  append(L"\n");
  append(L"\n");
  append(L"  public function ambiguity(begin: Int, end: Int)\n");
  append(L"  {\n");
  append(L"  }");
                                                            #line 1719 "PrintHaxe.cpp.template"
                                                                  }
                                                            #line 2394 "PrintHaxe.cpp"
  append(L"\n");
  append(L"\n");
  append(L"  public function serialize(e: EventHandler)\n");
  append(L"  {\n");
  append(L"    e.reset(input);\n");
  append(L"    var i = 0;\n");
  append(L"    while (i <= top)\n");
  append(L"    {\n");
  append(L"      stack[i].send(e);\n");
  append(L"      ++i;\n");
  append(L"    }\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  public function push(s: Symbol)\n");
  append(L"  {\n");
  append(L"    stack[++top] = s;\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  public function pop(count: Int)\n");
  append(L"  {\n");
  append(L"     top -= count;\n");
  append(L"     return stack.slice(top + 1, top + count + 1);\n");
  append(L"  }\n");
  append(L"}\n");
                                                            #line 1744 "PrintHaxe.cpp.template"
                                                                }
                                                              }
                                                            }

// End
