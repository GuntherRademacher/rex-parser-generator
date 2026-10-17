// This file was generated on Sat Oct 17, 2026 11:26 (UTC+02) by REx v6.3-SNAPSHOT which is Copyright (c) 1979-2026 by Gunther Rademacher <grd@gmx.net>
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
                                                            #line 120 "PrintHaxe.cpp.template"
                                                                }
                                                            #line 196 "PrintHaxe.cpp"
  append(L"\n");
  append(L"          parser.");
                                                            #line 122 "PrintHaxe.cpp.template"
                                                                print(methodPrefixParse);
                                                                print(Format::acceptableName<WString>(grammar->startSymbol()->name).c_str());
                                                            #line 202 "PrintHaxe.cpp"
  append(L"();");
                                                            #line 124 "PrintHaxe.cpp.template"
                                                                if (trace)
                                                                {
                                                            #line 207 "PrintHaxe.cpp"
  append(L"\n");
  append(L"          trace(\"</trace>\");");
                                                            #line 127 "PrintHaxe.cpp.template"
                                                                }
                                                                if (tree && isLrParser)
                                                                {
                                                            #line 214 "PrintHaxe.cpp"
  append(L"\n");
  append(L"          b.serialize(s);");
                                                            #line 131 "PrintHaxe.cpp.template"
                                                                }
                                                            #line 219 "PrintHaxe.cpp"
  append(L"\n");
  append(L"        }\n");
  append(L"        catch (pe: ParseException)\n");
  append(L"        {");
                                                            #line 135 "PrintHaxe.cpp.template"
                                                                if (rejectsAmbiguity() && tree)
                                                                {
                                                            #line 227 "PrintHaxe.cpp"
  append(L"\n");
  append(L"          if (pe.isAmbiguousInput())\n");
  append(L"          {\n");
  append(L"            pe.serialize(s);\n");
  append(L"            Sys.println(\"\");\n");
  append(L"          }");
                                                            #line 142 "PrintHaxe.cpp.template"
                                                                }
                                                            #line 236 "PrintHaxe.cpp"
  append(L"\n");
  append(L"          throw \"ParseException while processing \" + arg + \":\\n\" + parser.getErrorMessage(pe);\n");
  append(L"        }\n");
  append(L"      }\n");
  append(L"    }\n");
  append(L"  }\n");
                                                            #line 149 "PrintHaxe.cpp.template"
                                                              }
                                                              printReadMethod();
                                                              if (! hasProlog)
                                                              {
                                                            #line 248 "PrintHaxe.cpp"
  append(L"\n");
  append(L"  public function new(string");
                                                            #line 154 "PrintHaxe.cpp.template"
                                                                if (noLexer)
                                                                {
                                                            #line 254 "PrintHaxe.cpp"
  append(L", lexer");
                                                            #line 156 "PrintHaxe.cpp.template"
                                                                }
                                                                if (tree)
                                                                {
                                                            #line 260 "PrintHaxe.cpp"
  append(L", t");
                                                            #line 159 "PrintHaxe.cpp.template"
                                                                }
                                                            #line 264 "PrintHaxe.cpp"
  append(L")\n");
  append(L"  {\n");
  append(L"    initialize(string");
                                                            #line 162 "PrintHaxe.cpp.template"
                                                                if (noLexer)
                                                                {
                                                            #line 271 "PrintHaxe.cpp"
  append(L", lexer");
                                                            #line 164 "PrintHaxe.cpp.template"
                                                                }
                                                                if (tree)
                                                                {
                                                            #line 277 "PrintHaxe.cpp"
  append(L", t");
                                                            #line 167 "PrintHaxe.cpp.template"
                                                                }
                                                            #line 281 "PrintHaxe.cpp"
  append(L");\n");
  append(L"  }\n");
                                                            #line 170 "PrintHaxe.cpp.template"
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
                                                            #line 187 "PrintHaxe.cpp.template"
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
                                                            #line 200 "PrintHaxe.cpp.template"
                                                              if (grammar->states->hasLookback)
                                                              {
                                                            #line 322 "PrintHaxe.cpp"
  append(L"\n");
  append(L"  public var code: Int;");
                                                            #line 203 "PrintHaxe.cpp.template"
                                                              }
                                                            #line 327 "PrintHaxe.cpp"
  append(L"\n");
  append(L"  public var pos: Int;\n");
  append(L"  public var link: StackNode;\n");
  append(L"\n");
  append(L"  public function new(state: Int, ");
                                                            #line 209 "PrintHaxe.cpp.template"
                                                              if (grammar->states->hasLookback)
                                                              {
                                                            #line 336 "PrintHaxe.cpp"
  append(L"code: Int, ");
                                                            #line 211 "PrintHaxe.cpp.template"
                                                              }
                                                            #line 340 "PrintHaxe.cpp"
  append(L"pos: Int, link: StackNode)\n");
  append(L"  {\n");
  append(L"    this.state = state;");
                                                            #line 215 "PrintHaxe.cpp.template"
                                                              if (grammar->states->hasLookback)
                                                              {
                                                            #line 347 "PrintHaxe.cpp"
  append(L"\n");
  append(L"    this.code = code;");
                                                            #line 218 "PrintHaxe.cpp.template"
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
                                                            #line 230 "PrintHaxe.cpp.template"
                                                              if (grammar->states->hasLookback)
                                                              {
                                                            #line 368 "PrintHaxe.cpp"
  append(L"\n");
  append(L"      if (lhs.code != rhs.code) return false;");
                                                            #line 233 "PrintHaxe.cpp.template"
                                                              }
                                                            #line 373 "PrintHaxe.cpp"
  append(L"\n");
  append(L"      if (lhs.pos != rhs.pos) return false;\n");
  append(L"      lhs = lhs.link;\n");
  append(L"      rhs = rhs.link;\n");
  append(L"    }\n");
  append(L"    return lhs == rhs;\n");
  append(L"  }");
                                                            #line 240 "PrintHaxe.cpp.template"
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
                                                            #line 321 "PrintHaxe.cpp.template"
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
                                                            #line 340 "PrintHaxe.cpp.template"
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
  append(L"  public var end: Int;\n");
  append(L"\n");
  append(L"  public function new(link: DeferredEvent, name: String, begin: Int, end: Int)\n");
  append(L"  {\n");
  append(L"    this.link = link;\n");
  append(L"    this.name = name;\n");
  append(L"    this.begin = begin;\n");
  append(L"    this.end = end;\n");
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
  append(L"      current.execute(eventHandler);\n");
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
  append(L"  }\n");
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
                                                            #line 425 "PrintHaxe.cpp.template"
                                                              if (minimalAmbiguity)
                                                              {
                                                            #line 575 "PrintHaxe.cpp"
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
                                                            #line 440 "PrintHaxe.cpp.template"
                                                              }
                                                              }
                                                            }

                                                            void PrintHaxe::openThread()
                                                            {
                                                            #line 596 "PrintHaxe.cpp"
  append(L"\n");
  append(L"private class ParsingThread\n");
  append(L"{\n");
  append(L"  public var parser: ");
                                                            #line 449 "PrintHaxe.cpp.template"
                                                              print(className.c_str());
                                                            #line 603 "PrintHaxe.cpp"
  append(L";\n");
  append(L"  public var threads: Heap;\n");
  append(L"  public var accepted: Bool;\n");
  append(L"  public var stack: StackNode ;\n");
  append(L"  public var state: Int;\n");
  append(L"  public var action: Int;\n");
  append(L"  public var target: Int;");
                                                            #line 456 "PrintHaxe.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 614 "PrintHaxe.cpp"
  append(L"\n");
  append(L"  public var deferredEvent: DeferredEvent;");
                                                            #line 459 "PrintHaxe.cpp.template"
                                                              }
                                                              if (hasCustomCode)
                                                              {
                                                            #line 621 "PrintHaxe.cpp"
  append(L"\n");
  append(L"  public var deferredCode: DeferredCode;");
                                                            #line 463 "PrintHaxe.cpp.template"
                                                              }
                                                            #line 626 "PrintHaxe.cpp"
  append(L"\n");
  append(L"  public var id: Int;");
                                                            #line 465 "PrintHaxe.cpp.template"
                                                              if (minimalAmbiguity)
                                                              {
                                                            #line 632 "PrintHaxe.cpp"
  append(L"\n");
  append(L"  public var eventCount: Int;");
                                                            #line 468 "PrintHaxe.cpp.template"
                                                                      }
                                                            #line 637 "PrintHaxe.cpp"
  append(L"\n");
  append(L"\n");
  append(L"  public function new()\n");
  append(L"  {\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  public function open(initialState: Int");
                                                            #line 475 "PrintHaxe.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 648 "PrintHaxe.cpp"
  append(L", eh: BottomUpEventHandler");
                                                            #line 477 "PrintHaxe.cpp.template"
                                                              }
                                                            #line 652 "PrintHaxe.cpp"
  append(L", t: Int): Heap\n");
  append(L"  {\n");
  append(L"    accepted = false;\n");
  append(L"    target = t;");
                                                            #line 481 "PrintHaxe.cpp.template"
                                                                  if (minimalAmbiguity)
                                                              {
                                                            #line 660 "PrintHaxe.cpp"
  append(L"\n");
  append(L"    eventCount = 0;");
                                                            #line 484 "PrintHaxe.cpp.template"
                                                                      }
                                                              if (tree)
                                                              {
                                                            #line 667 "PrintHaxe.cpp"
  append(L"\n");
  append(L"    eventHandler = eh;\n");
  append(L"    if (eventHandler != null)\n");
  append(L"    {\n");
  append(L"      eventHandler.reset(parser.input);\n");
  append(L"    }\n");
  append(L"    deferredEvent = null;");
                                                            #line 493 "PrintHaxe.cpp.template"
                                                              }
                                                              if (hasCustomCode && useGlr)
                                                              {
                                                            #line 679 "PrintHaxe.cpp"
  append(L"\n");
  append(L"    deferredCode = null;");
                                                            #line 497 "PrintHaxe.cpp.template"
                                                              }
                                                            #line 684 "PrintHaxe.cpp"
  append(L"\n");
  append(L"    stack = new StackNode(-1, ");
                                                            #line 500 "PrintHaxe.cpp.template"
                                                              if (grammar->states->hasLookback)
                                                              {
                                                            #line 690 "PrintHaxe.cpp"
  append(L"0, ");
                                                            #line 502 "PrintHaxe.cpp.template"
                                                              }
                                                            #line 694 "PrintHaxe.cpp"
  append(L"e0, null);\n");
  append(L"    state = initialState;\n");
  append(L"    action = predict(initialState);");
                                                            #line 505 "PrintHaxe.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 701 "PrintHaxe.cpp"
  append(L"\n");
  append(L"    es = e0;");
                                                            #line 508 "PrintHaxe.cpp.template"
                                                              }
                                                            #line 706 "PrintHaxe.cpp"
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
                                                            #line 524 "PrintHaxe.cpp.template"
                                                                     if (minimalAmbiguity)
                                                              {
                                                            #line 726 "PrintHaxe.cpp"
  append(L"\n");
  append(L"    eventCount = other.eventCount;");
                                                            #line 527 "PrintHaxe.cpp.template"
                                                                                     }
                                                              if (tree)
                                                              {
                                                            #line 733 "PrintHaxe.cpp"
  append(L"\n");
  append(L"    es = other.es;\n");
  append(L"    eventHandler = other.eventHandler;\n");
  append(L"    deferredEvent = other.deferredEvent;");
                                                            #line 533 "PrintHaxe.cpp.template"
                                                              }
                                                              if (hasCustomCode)
                                                              {
                                                            #line 742 "PrintHaxe.cpp"
  append(L"\n");
  append(L"    deferredCode = other.deferredCode;");
                                                            #line 537 "PrintHaxe.cpp.template"
                                                              }
                                                            #line 747 "PrintHaxe.cpp"
  append(L"\n");
  append(L"    id = ++parser.maxId;\n");
  append(L"    threads = other.threads;\n");
  append(L"    state = other.state;\n");
  append(L"    stack = other.stack;\n");
  append(L"    b0 = other.b0;\n");
  append(L"    e0 = other.e0;");
                                                            #line 544 "PrintHaxe.cpp.template"
                                                              for (size_t i = 1; i <= grammar->k; ++i)
                                                              {
                                                                const wchar_t *iString = format.toString<wchar_t>(i);
                                                            #line 759 "PrintHaxe.cpp"
  append(L"\n");
  append(L"    l");
                                                            #line 548 "PrintHaxe.cpp.template"
                                                                print(iString);
                                                            #line 764 "PrintHaxe.cpp"
  append(L" = other.l");
                                                            #line 549 "PrintHaxe.cpp.template"
                                                                print(iString);
                                                            #line 768 "PrintHaxe.cpp"
  append(L";\n");
  append(L"    b");
                                                            #line 551 "PrintHaxe.cpp.template"
                                                                print(iString);
                                                            #line 773 "PrintHaxe.cpp"
  append(L" = other.b");
                                                            #line 552 "PrintHaxe.cpp.template"
                                                                print(iString);
                                                            #line 777 "PrintHaxe.cpp"
  append(L";\n");
  append(L"    e");
                                                            #line 554 "PrintHaxe.cpp.template"
                                                                print(iString);
                                                            #line 782 "PrintHaxe.cpp"
  append(L" = other.e");
                                                            #line 555 "PrintHaxe.cpp.template"
                                                                print(iString);
                                                            #line 786 "PrintHaxe.cpp"
  append(L";");
                                                            #line 556 "PrintHaxe.cpp.template"
                                                              }
                                                            #line 790 "PrintHaxe.cpp"
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
                                                            #line 581 "PrintHaxe.cpp.template"
                                                              if (minimalAmbiguity && tree)
                                                              {
                                                            #line 818 "PrintHaxe.cpp"
  append(L"\n");
  append(L"  public function addAmbiguity(begin: Int, end: Int): Void\n");
  append(L"  {\n");
  append(L"    if (eventHandler != null)\n");
  append(L"      deferredEvent = new AmbiguityEvent(deferredEvent, begin, end);\n");
  append(L"  }\n");
                                                            #line 589 "PrintHaxe.cpp.template"
                                                              }
                                                            #line 827 "PrintHaxe.cpp"
  append(L"\n");
  append(L"  public function parse(): Int\n");
  append(L"  {");
                                                            #line 592 "PrintHaxe.cpp.template"
                                                              increaseIndent();
                                                              beginPublic();
                                                            }

                                                            void PrintHaxe::printGlrParseMethod()
                                                            {
                                                            #line 838 "PrintHaxe.cpp"
  append(L"\n");
  append(L"public static var PARSING = 0;\n");
  append(L"public static var ACCEPTED = 1;\n");
  append(L"public static var ERROR = 2;\n");
  append(L"\n");
  append(L"public function parse(target: Int, initialState: Int, ");
                                                            #line 603 "PrintHaxe.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 848 "PrintHaxe.cpp"
  append(L"eventHandler: BottomUpEventHandler, ");
                                                            #line 606 "PrintHaxe.cpp.template"
                                                              }
                                                            #line 852 "PrintHaxe.cpp"
  append(L"thread: ParsingThread): ParsingThread\n");
  append(L"{\n");
  append(L"  var threads: Heap = thread.open(initialState");
                                                            #line 610 "PrintHaxe.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 859 "PrintHaxe.cpp"
  append(L", eventHandler");
                                                            #line 613 "PrintHaxe.cpp.template"
                                                              }
                                                            #line 863 "PrintHaxe.cpp"
  append(L", target);\n");
  append(L"  while (true)\n");
  append(L"  {\n");
  append(L"    thread = threads.poll();\n");
  append(L"    if (thread.accepted)\n");
  append(L"    {");
                                                            #line 619 "PrintHaxe.cpp.template"
                                                            if (rejectsAmbiguity())
                                                              {
                                                            #line 873 "PrintHaxe.cpp"
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
                                                            #line 634 "PrintHaxe.cpp.template"
                                                                                                          if (tree)
                                                              {
                                                            #line 891 "PrintHaxe.cpp"
  append(L", thread.deferredEvent, other.deferredEvent");
                                                            #line 636 "PrintHaxe.cpp.template"
                                                              }
                                                            #line 895 "PrintHaxe.cpp"
  append(L");\n");
  append(L"      }");
                                                            #line 638 "PrintHaxe.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 902 "PrintHaxe.cpp"
  append(L"\n");
  append(L"      while (! threads.isEmpty())\n");
  append(L"      {\n");
  append(L"        var other: ParsingThread = threads.poll();\n");
  append(L"        thread = thread.e0 < other.e0 ? other : resolve(thread, other);\n");
  append(L"      }");
                                                            #line 646 "PrintHaxe.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                            #line 913 "PrintHaxe.cpp"
  append(L"\n");
  append(L"      if (thread.deferredEvent != null)\n");
  append(L"      {\n");
  append(L"        thread.deferredEvent.release(eventHandler);\n");
  append(L"        thread.deferredEvent = null;\n");
  append(L"      }");
                                                            #line 654 "PrintHaxe.cpp.template"
                                                              }
                                                              if (hasCustomCode)
                                                              {
                                                            #line 924 "PrintHaxe.cpp"
  append(L"\n");
  append(L"      thread.executeDeferredCode();");
                                                            #line 658 "PrintHaxe.cpp.template"
                                                              }
                                                            #line 929 "PrintHaxe.cpp"
  append(L"\n");
  append(L"      return thread;\n");
  append(L"    }\n");
  append(L"\n");
                                                            #line 663 "PrintHaxe.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 937 "PrintHaxe.cpp"
  append(L"    if (! threads.isEmpty())\n");
  append(L"    {\n");
  append(L"      if (threads.peek().equals(thread))\n");
  append(L"      {\n");
  append(L"        rejectAmbiguity(thread.stack.pos, thread.e0");
                                                            #line 669 "PrintHaxe.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 946 "PrintHaxe.cpp"
  append(L", thread.deferredEvent, threads.peek().deferredEvent");
                                                            #line 671 "PrintHaxe.cpp.template"
                                                              }
                                                            #line 950 "PrintHaxe.cpp"
  append(L");\n");
  append(L"      }\n");
  append(L"    }");
                                                            #line 674 "PrintHaxe.cpp.template"
                                                            }
                                                              else
                                                              {
                                                            #line 958 "PrintHaxe.cpp"
  append(L"    while (! threads.isEmpty() && threads.peek().equals(thread))\n");
  append(L"    {\n");
  append(L"      thread = resolve(thread, threads.poll());\n");
  append(L"    }");
                                                            #line 680 "PrintHaxe.cpp.template"
                                                            }
                                                              if (tree || hasCustomCode)
                                                              {
                                                                if (rejectsAmbiguity())
                                                                {
                                                            #line 969 "PrintHaxe.cpp"
  append(L"\n");
  append(L"    else\n");
  append(L"    {");
                                                            #line 687 "PrintHaxe.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 977 "PrintHaxe.cpp"
  append(L"\n");
  append(L"    if (threads.isEmpty())\n");
  append(L"    {");
                                                            #line 692 "PrintHaxe.cpp.template"
                                                                }
                                                                if (tree)
                                                                {
                                                            #line 985 "PrintHaxe.cpp"
  append(L"\n");
  append(L"      if (thread.deferredEvent != null)\n");
  append(L"      {\n");
  append(L"        thread.deferredEvent.release(eventHandler);\n");
  append(L"        thread.deferredEvent = null;\n");
  append(L"      }");
                                                            #line 700 "PrintHaxe.cpp.template"
                                                                }
                                                                if (hasCustomCode)
                                                                {
                                                            #line 996 "PrintHaxe.cpp"
  append(L"\n");
  append(L"      thread.executeDeferredCode();");
                                                            #line 704 "PrintHaxe.cpp.template"
                                                                }
                                                            #line 1001 "PrintHaxe.cpp"
  append(L"\n");
  append(L"    }");
                                                            #line 706 "PrintHaxe.cpp.template"
                                                              }
                                                            #line 1006 "PrintHaxe.cpp"
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
                                                            #line 731 "PrintHaxe.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 1034 "PrintHaxe.cpp"
  append(L"\n");
  append(L"private function rejectAmbiguity(begin: Int, end: Int");
                                                            #line 734 "PrintHaxe.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 1040 "PrintHaxe.cpp"
  append(L", first: DeferredEvent, second: DeferredEvent");
                                                            #line 736 "PrintHaxe.cpp.template"
                                                              }
                                                            #line 1044 "PrintHaxe.cpp"
  append(L"): Void\n");
  append(L"{");
                                                            #line 738 "PrintHaxe.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 1050 "PrintHaxe.cpp"
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
                                                            #line 750 "PrintHaxe.cpp.template"
                                                              }
                                                            #line 1063 "PrintHaxe.cpp"
  append(L"\n");
  append(L"  var exception = new ParseException(begin, end, -1, -1, -1);\n");
  append(L"  exception.setAmbiguousInput(");
                                                            #line 753 "PrintHaxe.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 1070 "PrintHaxe.cpp"
  append(L"treeBuilder");
                                                            #line 755 "PrintHaxe.cpp.template"
                                                              }
                                                            #line 1074 "PrintHaxe.cpp"
  append(L");\n");
  append(L"  throw exception;\n");
  append(L"}");
                                                            #line 758 "PrintHaxe.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 1082 "PrintHaxe.cpp"
  append(L"\n");
  append(L"private function resolve(thread: ParsingThread, other: ParsingThread): ParsingThread\n");
  append(L"{");
                                                            #line 763 "PrintHaxe.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 1089 "PrintHaxe.cpp"
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
                                                            #line 774 "PrintHaxe.cpp.template"
                                                              }
                                                            #line 1102 "PrintHaxe.cpp"
  append(L"\n");
  append(L"  if (other.eventCount < thread.eventCount)\n");
  append(L"    thread = other;");
                                                            #line 777 "PrintHaxe.cpp.template"
                                                                   if (tree)
                                                              {
                                                            #line 1109 "PrintHaxe.cpp"
  append(L"\n");
  append(L"  thread.addAmbiguity(begin, thread.e0);");
                                                            #line 780 "PrintHaxe.cpp.template"
                                                                                      }
                                                            #line 1114 "PrintHaxe.cpp"
  append(L"\n");
  append(L"  return thread;\n");
  append(L"}");
                                                            #line 783 "PrintHaxe.cpp.template"
                                                              }
                                                            #line 1120 "PrintHaxe.cpp"
  append(L"\n");
  append(L"\n");
  append(L"private var thread: ParsingThread;");
                                                            #line 786 "PrintHaxe.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 1127 "PrintHaxe.cpp"
  append(L"\n");
  append(L"private var eventHandler: BottomUpEventHandler;");
                                                            #line 789 "PrintHaxe.cpp.template"
                                                              }
                                                            #line 1132 "PrintHaxe.cpp"
  append(L"\n");
  append(L"public var input: Bytes = null;\n");
  append(L"public var size = 0;\n");
  append(L"public var maxId = 0;");
                                                            #line 793 "PrintHaxe.cpp.template"
                                                              setIndent(1);
                                                            }

                                                            void PrintHaxe::openMethod(const wchar_t *type,
                                                                                       const wchar_t *prefix,
                                                                                       const wchar_t *name,
                                                                                       const wchar_t *args,
                                                                                       bool constant,
                                                                                       const wchar_t *clazz)
                                                            {
                                                            #line 1148 "PrintHaxe.cpp"
  append(L"\n");
                                                            #line 804 "PrintHaxe.cpp.template"
                                                              print(visibility);
                                                            #line 1152 "PrintHaxe.cpp"
  append(L" ");
                                                            #line 805 "PrintHaxe.cpp.template"
                                                              print(prefix);
                                                            #line 1156 "PrintHaxe.cpp"
  append(L"function ");
                                                            #line 806 "PrintHaxe.cpp.template"
                                                              print(name);
                                                            #line 1160 "PrintHaxe.cpp"
  append(L"(");
                                                            #line 807 "PrintHaxe.cpp.template"
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
                                                            #line 1175 "PrintHaxe.cpp"
  append(L")");
                                                            #line 819 "PrintHaxe.cpp.template"
                                                              if (*type) // && wcscmp(type, L"void "))
                                                              {
                                                            #line 1180 "PrintHaxe.cpp"
  append(L": ");
                                                            #line 821 "PrintHaxe.cpp.template"
                                                                print(towupper(*type));
                                                                print(type + 1);
                                                              }
                                                            }

                                                            void PrintHaxe::privateVars()
                                                            {
                                                              if (trace)
                                                              {
                                                            #line 1192 "PrintHaxe.cpp"
  append(L"\n");
  append(L"  private function lookaheadString()\n");
  append(L"  {\n");
  append(L"    var result = \"\";\n");
  append(L"    if (");
                                                            #line 834 "PrintHaxe.cpp.template"
                                                                print(thiz());
                                                            #line 1200 "PrintHaxe.cpp"
  append(L"l1 > 0)\n");
  append(L"    {\n");
  append(L"      result += ");
                                                            #line 837 "PrintHaxe.cpp.template"
                                                                print(staticPrefix());
                                                            #line 1206 "PrintHaxe.cpp"
  append(L"TOKEN[");
                                                            #line 838 "PrintHaxe.cpp.template"
                                                                print(thiz());
                                                            #line 1210 "PrintHaxe.cpp"
  append(L"l1];");
                                                            #line 839 "PrintHaxe.cpp.template"
                                                                for (size_t i = 2; i <= grammar->k; ++i)
                                                                {
                                                            #line 1215 "PrintHaxe.cpp"
  append(L"\n");
  append(L"      if (");
                                                            #line 842 "PrintHaxe.cpp.template"
                                                                  print(thiz());
                                                            #line 1220 "PrintHaxe.cpp"
  append(L"l");
                                                            #line 843 "PrintHaxe.cpp.template"
                                                                  print(format.toString<wchar_t>(i));
                                                            #line 1224 "PrintHaxe.cpp"
  append(L" > 0)\n");
  append(L"      {\n");
  append(L"        result += \" \" + ");
                                                            #line 846 "PrintHaxe.cpp.template"
                                                                  print(staticPrefix());
                                                            #line 1230 "PrintHaxe.cpp"
  append(L"TOKEN[");
                                                            #line 847 "PrintHaxe.cpp.template"
                                                                  print(thiz());
                                                            #line 1234 "PrintHaxe.cpp"
  append(L"l");
                                                            #line 848 "PrintHaxe.cpp.template"
                                                                  print(format.toString<wchar_t>(i));
                                                            #line 1238 "PrintHaxe.cpp"
  append(L"];");
                                                            #line 849 "PrintHaxe.cpp.template"
                                                                  increaseIndent();
                                                                }
                                                                for (size_t i = 2; i <= grammar->k; ++i)
                                                                {
                                                                  decreaseIndent();
                                                            #line 1246 "PrintHaxe.cpp"
  append(L"\n");
  append(L"      }");
                                                            #line 855 "PrintHaxe.cpp.template"
                                                                }
                                                            #line 1251 "PrintHaxe.cpp"
  append(L"\n");
  append(L"    }\n");
  append(L"    return result;\n");
  append(L"  }\n");
                                                            #line 860 "PrintHaxe.cpp.template"
                                                              }

                                                              if (memoization)
                                                              {
                                                                int bits = Math::bits(grammar->conflictCount);
                                                            #line 1262 "PrintHaxe.cpp"
  append(L"\n");
  append(L"  private function memoize(i, e, v)\n");
  append(L"  {\n");
  append(L"    memo.set((e << ");
                                                            #line 868 "PrintHaxe.cpp.template"
                                                                print(format.toString<wchar_t>(bits));
                                                            #line 1269 "PrintHaxe.cpp"
  append(L") + i, v);\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  private function memoized(i, e): Int\n");
  append(L"  {\n");
  append(L"    var v = memo.get((e << ");
                                                            #line 874 "PrintHaxe.cpp.template"
                                                                print(format.toString<wchar_t>(bits));
                                                            #line 1278 "PrintHaxe.cpp"
  append(L") + i);\n");
  append(L"    return v == null ? 0 : v;\n");
  append(L"  }\n");
                                                            #line 878 "PrintHaxe.cpp.template"
                                                              }
                                                            #line 1284 "PrintHaxe.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 880 "PrintHaxe.cpp.template"
                                                              if (! isLrParser && (grammar->k > 1 ||
                                                                                   memoization ||
                                                                                   ! grammar->decisionPoints.empty()))
                                                              {
                                                            #line 1292 "PrintHaxe.cpp"
  append(L"private var lk: Int; ");
                                                            #line 884 "PrintHaxe.cpp.template"
                                                              }
                                                              else if (! useGlr)
                                                              {
                                                            #line 1298 "PrintHaxe.cpp"
  append(L"                     ");
                                                            #line 887 "PrintHaxe.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 1304 "PrintHaxe.cpp"
  append(L"                    ");
                                                            #line 890 "PrintHaxe.cpp.template"
                                                              }
                                                              const wchar_t *visibility = useGlr ? L"public" : L"private";
                                                              print(visibility);
                                                            #line 1310 "PrintHaxe.cpp"
  append(L" var b0: Int; ");
                                                            #line 893 "PrintHaxe.cpp.template"
                                                              print(visibility);
                                                            #line 1314 "PrintHaxe.cpp"
  append(L" var e0: Int;");
                                                            #line 894 "PrintHaxe.cpp.template"
                                                              for (size_t k = 1; k <= grammar->k; ++k)
                                                              {
                                                                Format format;
                                                                wchar_t *asString = format.toString<wchar_t>(k);
                                                            #line 1321 "PrintHaxe.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 899 "PrintHaxe.cpp.template"
                                                                print(visibility);
                                                            #line 1326 "PrintHaxe.cpp"
  append(L" var l");
                                                            #line 900 "PrintHaxe.cpp.template"
                                                                print(asString);
                                                            #line 1330 "PrintHaxe.cpp"
  append(L": Int; ");
                                                            #line 901 "PrintHaxe.cpp.template"
                                                                print(visibility);
                                                            #line 1334 "PrintHaxe.cpp"
  append(L" var b");
                                                            #line 902 "PrintHaxe.cpp.template"
                                                                print(asString);
                                                            #line 1338 "PrintHaxe.cpp"
  append(L": Int; ");
                                                            #line 903 "PrintHaxe.cpp.template"
                                                                print(visibility);
                                                            #line 1342 "PrintHaxe.cpp"
  append(L" var e");
                                                            #line 904 "PrintHaxe.cpp.template"
                                                                print(asString);
                                                            #line 1346 "PrintHaxe.cpp"
  append(L": Int;");
                                                            #line 905 "PrintHaxe.cpp.template"
                                                              }
                                                              if (hasBacktracking)
                                                              {
                                                            #line 1352 "PrintHaxe.cpp"
  append(L"\n");
  append(L"  private var bx: Int;\n");
  append(L"  private var ex: Int;\n");
  append(L"  private var sx: Int;\n");
  append(L"  private var lx: Int;\n");
  append(L"  private var tx: Int;");
                                                            #line 913 "PrintHaxe.cpp.template"
                                                              }
                                                              if (isLrParser && ! useGlr)
                                                              {
                                                            #line 1363 "PrintHaxe.cpp"
  append(L"\n");
  append(L"  private var iStack = [];\n");
  append(L"  private var top = -1;");
                                                            #line 918 "PrintHaxe.cpp.template"
                                                              }
                                                              if (useGlr)
                                                              {
                                                            #line 1371 "PrintHaxe.cpp"
  append(L"\n");
  append(L"  private var bw: Int;\n");
  append(L"  private var bs: Int;");
                                                            #line 923 "PrintHaxe.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                                if (isLrParser)
                                                                {
                                                                  if (useGlr)
                                                                  {
                                                            #line 1383 "PrintHaxe.cpp"
  append(L"\n");
  append(L"  private var es: Int;");
                                                            #line 931 "PrintHaxe.cpp.template"
                                                                  }
                                                            #line 1388 "PrintHaxe.cpp"
  append(L"\n");
  append(L"  private var eventHandler: BottomUpEventHandler = null;");
                                                            #line 933 "PrintHaxe.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1395 "PrintHaxe.cpp"
  append(L"\n");
  append(L"  private var eventHandler: EventHandler = null;");
                                                            #line 937 "PrintHaxe.cpp.template"
                                                                }
                                                              }
                                                              if (memoization)
                                                              {
                                                            #line 1403 "PrintHaxe.cpp"
  append(L"\n");
  append(L"  private var memo: Map<Int, Int>  = new Map();");
                                                            #line 943 "PrintHaxe.cpp.template"
                                                                if (grammar->noThrow)
                                                                {
                                                            #line 1409 "PrintHaxe.cpp"
  append(L"\n");
  append(L"  private var viable: Bool;");
                                                            #line 946 "PrintHaxe.cpp.template"
                                                                }
                                                              }
                                                            }

                                                            void PrintHaxe::printFileProcessor()
                                                            {
                                                            #line 1419 "PrintHaxe.cpp"
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
                                                            #line 964 "PrintHaxe.cpp.template"
                                                              print(className.c_str());
                                                            #line 1435 "PrintHaxe.cpp"
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
                                                            #line 1027 "PrintHaxe.cpp.template"
                                                                  if (useGlr)
                                                                  {
                                                            #line 1502 "PrintHaxe.cpp"
  append(L".thread");
                                                            #line 1029 "PrintHaxe.cpp.template"
                                                                  }
                                                            #line 1506 "PrintHaxe.cpp"
  append(L".reset(0, 0, 0);\n");
  append(L"                job.parser.");
                                                            #line 1031 "PrintHaxe.cpp.template"
                                                                  print(methodPrefixParse);
                                                                  print(Format::acceptableName<WString>(grammar->startSymbol()->name).c_str());
                                                            #line 1512 "PrintHaxe.cpp"
  append(L"();\n");
  append(L"                if (! quiet) Sys.println(\"\");");
                                                            #line 1034 "PrintHaxe.cpp.template"
                                                                  if (tree)
                                                                  {
                                                                    if (isLrParser)
                                                                    {
                                                            #line 1520 "PrintHaxe.cpp"
  append(L"\n");
  append(L"                job.parseTreeBuilder.serialize(job.contentCounter);");
                                                            #line 1040 "PrintHaxe.cpp.template"
                                                                    }
                                                            #line 1525 "PrintHaxe.cpp"
  append(L"\n");
  append(L"                if (job.contentCounter.getLength() != job.input.length)\n");
  append(L"                {\n");
  append(L"                  throw \"content counter saw \" + job.contentCounter.getLength() + \", but input length is \" + job.input.length;\n");
  append(L"                }");
                                                            #line 1045 "PrintHaxe.cpp.template"
                                                                  }
                                                            #line 1533 "PrintHaxe.cpp"
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
                                                            #line 1103 "PrintHaxe.cpp.template"
                                                            }

                                                            void PrintHaxe::printReadMethod()
                                                            {
                                                              if (main || performanceTest)
                                                              {
                                                            #line 1597 "PrintHaxe.cpp"
  append(L"\n");
  append(L"  private static function read(input)\n");
  append(L"  {\n");
  append(L"    if (");
                                                            #line 1112 "PrintHaxe.cpp.template"
                                                                print(L"~/^");
                                                            #line 1604 "PrintHaxe.cpp"
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
                                                            #line 1126 "PrintHaxe.cpp.template"
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
                                                            #line 1630 "PrintHaxe.cpp"
  append(L"\n");
  append(L"package ");
                                                            #line 1139 "PrintHaxe.cpp.template"
                                                                print(packageName.c_str());
                                                            #line 1635 "PrintHaxe.cpp"
  append(L";\n");
                                                            #line 1141 "PrintHaxe.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                                if (main)
                                                                {
                                                            #line 1643 "PrintHaxe.cpp"
  append(L"\n");
  append(L"import java.io.IOException;\n");
  append(L"import java.io.Writer;\n");
                                                            #line 1149 "PrintHaxe.cpp.template"
                                                                }
                                                              }
                                                            #line 1650 "PrintHaxe.cpp"
  append(L"\n");
  append(L"public interface ");
                                                            #line 1152 "PrintHaxe.cpp.template"
                                                              print(className.c_str());
                                                            #line 1655 "PrintHaxe.cpp"
  append(L"\n");
  append(L"{\n");
  append(L"  public void initialize(CharSequence input");
                                                            #line 1155 "PrintHaxe.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 1662 "PrintHaxe.cpp"
  append(L", EventHandler eh");
                                                            #line 1157 "PrintHaxe.cpp.template"
                                                              }
                                                            #line 1666 "PrintHaxe.cpp"
  append(L");\n");
  append(L"  public void parse();\n");
  append(L"  public void reset();\n");
  append(L"  public String getErrorMessage(ParseException e);\n");
                                                            #line 1162 "PrintHaxe.cpp.template"
                                                              printParseException();
                                                            #line 1673 "PrintHaxe.cpp"
  append(L"}\n");
                                                            #line 1164 "PrintHaxe.cpp.template"
                                                            }

                                                            void PrintHaxe::printParseException()
                                                            {
                                                            #line 1680 "PrintHaxe.cpp"
  append(L"\n");
  append(L"class ParseException\n");
  append(L"{\n");
  append(L"  private var begin: Int;\n");
  append(L"  private var end: Int;\n");
  append(L"  private var state: Int;\n");
  append(L"  private var offending: Int;\n");
  append(L"  private var expected: Int;");
                                                            #line 1175 "PrintHaxe.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 1692 "PrintHaxe.cpp"
  append(L"\n");
  append(L"  private var ambiguousInput: Bool;");
                                                            #line 1178 "PrintHaxe.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 1698 "PrintHaxe.cpp"
  append(L"\n");
  append(L"  private var ambiguityDescriptor: ParseTreeBuilder;");
                                                            #line 1181 "PrintHaxe.cpp.template"
                                                                }
                                                              }
                                                            #line 1704 "PrintHaxe.cpp"
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
                                                            #line 1193 "PrintHaxe.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 1718 "PrintHaxe.cpp"
  append(L"\n");
  append(L"  public function setAmbiguousInput(");
                                                            #line 1196 "PrintHaxe.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 1724 "PrintHaxe.cpp"
  append(L"a");
                                                            #line 1198 "PrintHaxe.cpp.template"
                                                                }
                                                            #line 1728 "PrintHaxe.cpp"
  append(L")\n");
  append(L"  {\n");
  append(L"    ambiguousInput = true;");
                                                            #line 1201 "PrintHaxe.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 1735 "PrintHaxe.cpp"
  append(L"\n");
  append(L"    ambiguityDescriptor = a;");
                                                            #line 1204 "PrintHaxe.cpp.template"
                                                                }
                                                            #line 1740 "PrintHaxe.cpp"
  append(L"\n");
  append(L"  }\n");
                                                            #line 1207 "PrintHaxe.cpp.template"
                                                              }
                                                            #line 1745 "PrintHaxe.cpp"
  append(L"\n");
  append(L"  public function getBegin() {return begin;}\n");
  append(L"  public function getEnd() {return end;}\n");
  append(L"  public function getState() {return state;}\n");
  append(L"  public function getExpected() {return expected;}\n");
  append(L"  public function getOffending() {return offending;}\n");
  append(L"  public function isAmbiguousInput() {return ");
                                                            #line 1214 "PrintHaxe.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 1756 "PrintHaxe.cpp"
  append(L"ambiguousInput");
                                                            #line 1216 "PrintHaxe.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 1762 "PrintHaxe.cpp"
  append(L"false");
                                                            #line 1220 "PrintHaxe.cpp.template"
                                                              }
                                                            #line 1766 "PrintHaxe.cpp"
  append(L";}\n");
  append(L"\n");
  append(L"  public function getMessage()\n");
  append(L"  {\n");
  append(L"    return ");
                                                            #line 1225 "PrintHaxe.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 1775 "PrintHaxe.cpp"
  append(L"ambiguousInput\n");
  append(L"         ? \"ambiguous input\"\n");
  append(L"         : ");
                                                            #line 1229 "PrintHaxe.cpp.template"
                                                              }
                                                            #line 1781 "PrintHaxe.cpp"
  append(L"offending < 0\n");
  append(L"         ? \"lexical analysis failed\"\n");
  append(L"         : \"syntax error\";\n");
  append(L"  }");
                                                            #line 1233 "PrintHaxe.cpp.template"
                                                              if (rejectsAmbiguity() && tree)
                                                              {
                                                            #line 1789 "PrintHaxe.cpp"
  append(L"\n");
  append(L"\n");
  append(L"  public function serialize(eventHandler)\n");
  append(L"  {\n");
  append(L"    ambiguityDescriptor.serialize(eventHandler);\n");
  append(L"  }");
                                                            #line 1240 "PrintHaxe.cpp.template"
                                                              }
                                                            #line 1798 "PrintHaxe.cpp"
  append(L"\n");
  append(L"}\n");
                                                            #line 1243 "PrintHaxe.cpp.template"
                                                              if (noLexer)
                                                              {
                                                            #line 1804 "PrintHaxe.cpp"
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
                                                            #line 1258 "PrintHaxe.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                            #line 1822 "PrintHaxe.cpp"
  append(L"\n");
  append(L"interface EventHandler\n");
  append(L"{\n");
  append(L"  public function reset(input: Bytes): Void;\n");
  append(L"  public function startNonterminal(tag: String, begin: Int): Void;\n");
  append(L"  public function endNonterminal(tag: String, end: Int): Void;\n");
  append(L"  public function terminal(tag: String, begin: Int, end: Int): Void;\n");
  append(L"  public function whitespace(begin: Int, end: Int): Void;\n");
  append(L"}\n");
                                                            #line 1271 "PrintHaxe.cpp.template"
                                                                if (isLrParser)
                                                                {
                                                            #line 1835 "PrintHaxe.cpp"
  append(L"\n");
  append(L"interface BottomUpEventHandler\n");
  append(L"{\n");
  append(L"  public function reset(input: Bytes): Void;\n");
  append(L"  public function nonterminal(name: String, begin: Int, end: Int, count: Int): Void;\n");
  append(L"  public function terminal(name: String , begin: Int, end: Int): Void;");
                                                            #line 1278 "PrintHaxe.cpp.template"
                                                                                                  if (minimalAmbiguity)
                                                              {
                                                            #line 1845 "PrintHaxe.cpp"
  append(L"\n");
  append(L"  public function ambiguity(begin: Int, end: Int): Void;");
                                                            #line 1281 "PrintHaxe.cpp.template"
                                                                }
                                                            #line 1850 "PrintHaxe.cpp"
  append(L"\n");
  append(L"}\n");
                                                            #line 1284 "PrintHaxe.cpp.template"
                                                                }
                                                                #if EXPATH_EXTENSION_FUNCTION
                                                            #line 1856 "PrintHaxe.cpp"
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
                                                            #line 1336 "PrintHaxe.cpp.template"
                                                                #endif
                                                                if (main)
                                                                {
                                                                }
                                                              }
                                                              if (performanceTest)
                                                              {
                                                            #line 1914 "PrintHaxe.cpp"
  append(L"\n");
  append(L"class ParseJob\n");
  append(L"{\n");
  append(L"  public var name: String;\n");
  append(L"  public var input: String;\n");
  append(L"  public var parser: ");
                                                            #line 1349 "PrintHaxe.cpp.template"
                                                                print(className.c_str());
                                                            #line 1923 "PrintHaxe.cpp"
  append(L";");
                                                            #line 1350 "PrintHaxe.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 1928 "PrintHaxe.cpp"
  append(L"\n");
  append(L"  public var contentCounter: ContentCounter;");
                                                            #line 1353 "PrintHaxe.cpp.template"
                                                                  if (isLrParser)
                                                                  {
                                                            #line 1934 "PrintHaxe.cpp"
  append(L"\n");
  append(L"  public var parseTreeBuilder: ParseTreeBuilder;");
                                                            #line 1356 "PrintHaxe.cpp.template"
                                                                  }
                                                                }
                                                            #line 1940 "PrintHaxe.cpp"
  append(L"\n");
  append(L"  public function new(s: String, i: String)\n");
  append(L"  {\n");
  append(L"    name = s;\n");
  append(L"    input = i;");
                                                            #line 1362 "PrintHaxe.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 1949 "PrintHaxe.cpp"
  append(L"\n");
  append(L"    contentCounter = new ContentCounter();");
                                                            #line 1365 "PrintHaxe.cpp.template"
                                                                  if (isLrParser)
                                                                  {
                                                            #line 1955 "PrintHaxe.cpp"
  append(L"\n");
  append(L"    parseTreeBuilder = new ParseTreeBuilder();");
                                                            #line 1368 "PrintHaxe.cpp.template"
                                                                  }
                                                                }
                                                            #line 1961 "PrintHaxe.cpp"
  append(L"\n");
  append(L"    parser = new ");
                                                            #line 1371 "PrintHaxe.cpp.template"
                                                                print(className.c_str());
                                                            #line 1966 "PrintHaxe.cpp"
  append(L"(input");
                                                            #line 1372 "PrintHaxe.cpp.template"
                                                                if (noLexer)
                                                                {
                                                            #line 1971 "PrintHaxe.cpp"
  append(L", null");
                                                            #line 1374 "PrintHaxe.cpp.template"
                                                                }
                                                                if (tree)
                                                                {
                                                                  if (isLrParser)
                                                                  {
                                                            #line 1979 "PrintHaxe.cpp"
  append(L", parseTreeBuilder");
                                                            #line 1379 "PrintHaxe.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 1985 "PrintHaxe.cpp"
  append(L", contentCounter");
                                                            #line 1382 "PrintHaxe.cpp.template"
                                                                  }
                                                                }
                                                            #line 1990 "PrintHaxe.cpp"
  append(L");\n");
  append(L"  }\n");
  append(L"}\n");
                                                            #line 1388 "PrintHaxe.cpp.template"
                                                              }
                                                            }

                                                            void PrintHaxe::printEventHandlerImplementation()
                                                            {
                                                              if (tree)
                                                              {
                                                                if (main)
                                                                {
                                                            #line 2004 "PrintHaxe.cpp"
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
                                                            #line 1504 "PrintHaxe.cpp.template"
                                                                }
                                                                if (performanceTest)
                                                                {
                                                            #line 2121 "PrintHaxe.cpp"
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
                                                            #line 1519 "PrintHaxe.cpp.template"
                                                                }
                                                            #line 2136 "PrintHaxe.cpp"
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
                                                            #line 1628 "PrintHaxe.cpp.template"
                                                                if (isLrParser)
                                                                {
                                                            #line 2248 "PrintHaxe.cpp"
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
                                                            #line 1644 "PrintHaxe.cpp.template"
                                                                  if (useGlr)
                                                                  {
                                                            #line 2266 "PrintHaxe.cpp"
  append(L"\n");
  append(L"  public function getStack() {return stack;}\n");
  append(L"  public function getTop() {return top;}\n");
                                                            #line 1649 "PrintHaxe.cpp.template"
                                                                  }
                                                            #line 2272 "PrintHaxe.cpp"
  append(L"\n");
  append(L"  public function nonterminal(name: String, begin: Int, end: Int, count: Int)\n");
  append(L"  {");
                                                            #line 1652 "PrintHaxe.cpp.template"
                                                                  if (rejectsAmbiguity())
                                                                  {
                                                            #line 2279 "PrintHaxe.cpp"
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
                                                            #line 1665 "PrintHaxe.cpp.template"
                                                                  }
                                                            #line 2293 "PrintHaxe.cpp"
  append(L"\n");
  append(L"    push(new Nonterminal(name, begin, end, pop(count)));\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  public function terminal(name: String, begin: Int, end: Int)\n");
  append(L"  {\n");
  append(L"    push(new Terminal(name, begin, end));\n");
  append(L"  }");
                                                            #line 1673 "PrintHaxe.cpp.template"
                                            if (minimalAmbiguity)
                                                              {
                                                            #line 2305 "PrintHaxe.cpp"
  append(L"\n");
  append(L"\n");
  append(L"  public function ambiguity(begin: Int, end: Int)\n");
  append(L"  {\n");
  append(L"  }");
                                                            #line 1679 "PrintHaxe.cpp.template"
                                            }
                                                            #line 2313 "PrintHaxe.cpp"
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
                                                            #line 1704 "PrintHaxe.cpp.template"
                                                                }
                                                              }
                                                            }

// End
