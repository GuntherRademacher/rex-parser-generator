// This file was generated on Sun Nov 24, 2024 16:09 (UTC+01) by REx v6.0 which is Copyright (c) 1979-2024 by Gunther Rademacher <grd@gmx.net>
// REx command line: PrintCSharp.cpp.template
                                                            #line 1 "PrintCSharp.cpp.template"
                                                            #include "../common/Memory.hpp"

                                                            #include "PrintCSharp.hpp"
                                                            #include "ItemSet.hpp"
                                                            #include "../common/CompressedMap.hpp"

                                                            void PrintCSharp::close(Grammar *node)
                                                            {
                                                              if (embeddedOutputString == 0)
                                                              {
                                                                internalerr();
                                                              }

                                                              if (useGlr)
                                                              {
                                                                decreaseIndent();
                                                              }
                                                              print(L"\n");
                                                              print(embeddedOutputString);
                                                              if (! visitEpilog())
                                                              {
                                                                print(endClass());
                                                              }
                                                              if (! packageName.empty())
                                                              {
                                                                decreaseIndent();
                                                            #line 31 "PrintCSharp.cpp"
  append(L"\n");
  append(L"}\n");
                                                            #line 29 "PrintCSharp.cpp.template"
                                                              }
                                                              print(L"\n");
                                                            }

                                                            void PrintCSharp::openClass()
                                                            {
                                                              if (! hasProlog) {
                                                            #line 42 "PrintCSharp.cpp"
  append(L"\n");
  append(L"using System;\n");
  append(L"using System.IO;\n");
  append(L"using System.Text;\n");
  append(L"using System.Collections.Generic;\n");
                                                            #line 42 "PrintCSharp.cpp.template"
                                                                if (! packageName.empty())
                                                                {
                                                            #line 51 "PrintCSharp.cpp"
  append(L"\n");
  append(L"namespace ");
                                                            #line 45 "PrintCSharp.cpp.template"
                                                                  print(packageName.c_str());
                                                            #line 56 "PrintCSharp.cpp"
  append(L"\n");
  append(L"{");
                                                            #line 47 "PrintCSharp.cpp.template"
                                                                  increaseIndent();
                                                                }
                                                            #line 62 "PrintCSharp.cpp"
  append(L"\n");
  append(L"public class ");
                                                            #line 50 "PrintCSharp.cpp.template"
                                                                print(className.c_str());
                                                                if (! interfaceName.empty())
                                                                {
                                                            #line 69 "PrintCSharp.cpp"
  append(L" : ");
                                                            #line 53 "PrintCSharp.cpp.template"
                                                                  print(interfaceName.c_str());
                                                                }
                                                            #line 74 "PrintCSharp.cpp"
  append(L"\n");
  append(L"{");
                                                            #line 56 "PrintCSharp.cpp.template"
                                                              }
                                                              if (main)
                                                              {
                                                            #line 81 "PrintCSharp.cpp"
  append(L"\n");
  append(L"  public static int Main(string[] args)\n");
  append(L"  {\n");
  append(L"    if (args.Length == 0)\n");
  append(L"    {\n");
  append(L"      Console.Error.WriteLine(\"Usage: ");
                                                            #line 64 "PrintCSharp.cpp.template"
                                                                wchar_t *executable = Format::newFileName(wFileName.c_str(), L"");
                                                                print(executable);
                                                                free(executable);
                                                                if (tree)
                                                                {
                                                            #line 94 "PrintCSharp.cpp"
  append(L" [-i]");
                                                            #line 69 "PrintCSharp.cpp.template"
                                                                }
                                                            #line 98 "PrintCSharp.cpp"
  append(L" INPUT...\");\n");
  append(L"      Console.Error.WriteLine();\n");
  append(L"      Console.Error.WriteLine(\"  parse INPUT, which is either a filename or literal text enclosed in curly braces\");");
                                                            #line 73 "PrintCSharp.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 105 "PrintCSharp.cpp"
  append(L"\n");
  append(L"      Console.Error.WriteLine();\n");
  append(L"      Console.Error.WriteLine(\"  Option:\");\n");
  append(L"      Console.Error.WriteLine(\"    -i     indented parse tree\");");
                                                            #line 79 "PrintCSharp.cpp.template"
                                                                }
                                                            #line 112 "PrintCSharp.cpp"
  append(L"\n");
  append(L"    }\n");
  append(L"    else\n");
  append(L"    {");
                                                            #line 83 "PrintCSharp.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 120 "PrintCSharp.cpp"
  append(L"\n");
  append(L"      bool indent = false;");
                                                            #line 87 "PrintCSharp.cpp.template"
                                                                }
                                                            #line 125 "PrintCSharp.cpp"
  append(L"\n");
  append(L"      for (int i = 0; i < args.Length; ++i)\n");
  append(L"      {\n");
  append(L"        string arg = args[i];");
                                                            #line 91 "PrintCSharp.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 133 "PrintCSharp.cpp"
  append(L"\n");
  append(L"        if (arg.Equals(\"-i\"))\n");
  append(L"        {\n");
  append(L"          indent = true;\n");
  append(L"          continue;\n");
  append(L"        }\n");
  append(L"        TextWriter w = Console.Out;\n");
  append(L"        XmlSerializer s = new XmlSerializer(w, indent);");
                                                            #line 100 "PrintCSharp.cpp.template"
                                                                  if (isLrParser)
                                                                  {
                                                            #line 145 "PrintCSharp.cpp"
  append(L"\n");
  append(L"        ParseTreeBuilder b = new ParseTreeBuilder();");
                                                            #line 103 "PrintCSharp.cpp.template"
                                                                  }
                                                                }
                                                            #line 151 "PrintCSharp.cpp"
  append(L"\n");
  append(L"        String input = read(arg);\n");
  append(L"        ");
                                                            #line 107 "PrintCSharp.cpp.template"
                                                                print(className.c_str());
                                                            #line 157 "PrintCSharp.cpp"
  append(L" parser = new ");
                                                            #line 108 "PrintCSharp.cpp.template"
                                                                print(className.c_str());
                                                            #line 161 "PrintCSharp.cpp"
  append(L"(input");
                                                            #line 109 "PrintCSharp.cpp.template"
                                                                if (noLexer)
                                                                {
                                                            #line 166 "PrintCSharp.cpp"
  append(L", new ");
                                                            #line 111 "PrintCSharp.cpp.template"
                                                                  print(className.c_str());
                                                            #line 170 "PrintCSharp.cpp"
  append(L"Lexer()");
                                                            #line 112 "PrintCSharp.cpp.template"
                                                                }
                                                                if (tree)
                                                                {
                                                            #line 176 "PrintCSharp.cpp"
  append(L", ");
                                                            #line 115 "PrintCSharp.cpp.template"
                                                                  if (isLrParser)
                                                                  {
                                                            #line 181 "PrintCSharp.cpp"
  append(L"b");
                                                            #line 117 "PrintCSharp.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 187 "PrintCSharp.cpp"
  append(L"s");
                                                            #line 120 "PrintCSharp.cpp.template"
                                                                  }
                                                                }
                                                            #line 192 "PrintCSharp.cpp"
  append(L");\n");
  append(L"        try\n");
  append(L"        {");
                                                            #line 124 "PrintCSharp.cpp.template"
                                                                if (trace)
                                                                {
                                                            #line 199 "PrintCSharp.cpp"
  append(L"\n");
  append(L"          parser.writeTrace(\"<?xml version=\\\"1.0\\\" encoding=\\\"UTF-8\\\"?\" + \">\\n<trace>\\n\");");
                                                            #line 128 "PrintCSharp.cpp.template"
                                                                }
                                                            #line 204 "PrintCSharp.cpp"
  append(L"\n");
  append(L"          parser.");
                                                            #line 130 "PrintCSharp.cpp.template"
                                                                print(methodPrefixParse);
                                                                print(Format::acceptableName<WString>(grammar->startSymbol()->name).c_str());
                                                            #line 210 "PrintCSharp.cpp"
  append(L"();");
                                                            #line 132 "PrintCSharp.cpp.template"
                                                                if (trace)
                                                                {
                                                            #line 215 "PrintCSharp.cpp"
  append(L"\n");
  append(L"          parser.writeTrace(\"</trace>\\n\");");
                                                            #line 135 "PrintCSharp.cpp.template"
                                                                }
                                                                if (tree && isLrParser)
                                                                {
                                                            #line 222 "PrintCSharp.cpp"
  append(L"\n");
  append(L"          b.serialize(s);");
                                                            #line 139 "PrintCSharp.cpp.template"
                                                                }
                                                            #line 227 "PrintCSharp.cpp"
  append(L"\n");
  append(L"        }\n");
  append(L"        catch (ParseException pe)\n");
  append(L"        {");
                                                            #line 143 "PrintCSharp.cpp.template"
                                                                if (useGlr && tree)
                                                                {
                                                            #line 235 "PrintCSharp.cpp"
  append(L"\n");
  append(L"          if (pe.isAmbiguousInput())\n");
  append(L"          {\n");
  append(L"            pe.serialize(s);\n");
  append(L"            w.Write(\"\\n\");\n");
  append(L"            w.Flush();\n");
  append(L"          }");
                                                            #line 151 "PrintCSharp.cpp.template"
                                                                }
                                                            #line 245 "PrintCSharp.cpp"
  append(L"\n");
  append(L"          Console.Error.WriteLine(\"ParseException while processing \" + arg + \":\\n\" + parser.getErrorMessage(pe));\n");
  append(L"          return 1;\n");
  append(L"        }");
                                                            #line 155 "PrintCSharp.cpp.template"
                                                                if (tree || trace)
                                                                {
                                                            #line 253 "PrintCSharp.cpp"
  append(L"\n");
  append(L"        finally\n");
  append(L"        {");
                                                            #line 159 "PrintCSharp.cpp.template"
                                                                }
                                                                if (trace)
                                                                {
                                                            #line 261 "PrintCSharp.cpp"
  append(L"\n");
  append(L"          parser.flushTrace();");
                                                            #line 163 "PrintCSharp.cpp.template"
                                                                }
                                                                if (tree)
                                                                {
                                                            #line 268 "PrintCSharp.cpp"
  append(L"\n");
  append(L"          w.Close();");
                                                            #line 167 "PrintCSharp.cpp.template"
                                                                }
                                                                if (tree || trace)
                                                                {
                                                            #line 275 "PrintCSharp.cpp"
  append(L"\n");
  append(L"        }");
                                                            #line 171 "PrintCSharp.cpp.template"
                                                                }
                                                            #line 280 "PrintCSharp.cpp"
  append(L"\n");
  append(L"      }\n");
  append(L"    }\n");
  append(L"    return 0;\n");
  append(L"  }\n");
                                                            #line 177 "PrintCSharp.cpp.template"
                                                              }
                                                              if (interfaceName.empty())
                                                              {
                                                                printParseException();
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
                                                                increaseIndent();
                                                                WString args(L"String s");
                                                                if (noLexer) args += L", Lexer lexer";
                                                                if (tree) args += isLrParser ? L", BottomUpEventHandler t" : L", EventHandler t";
                                                                openMethod(L"", L"", className.c_str(), args.c_str());
                                                            #line 307 "PrintCSharp.cpp"
  append(L"\n");
  append(L"{\n");
  append(L"  initialize(s");
                                                            #line 199 "PrintCSharp.cpp.template"
                                                                if (noLexer)
                                                                {
                                                            #line 314 "PrintCSharp.cpp"
  append(L", lexer");
                                                            #line 201 "PrintCSharp.cpp.template"
                                                                }
                                                                if (tree)
                                                                {
                                                            #line 320 "PrintCSharp.cpp"
  append(L", t");
                                                            #line 204 "PrintCSharp.cpp.template"
                                                                }
                                                            #line 324 "PrintCSharp.cpp"
  append(L");\n");
  append(L"}\n");
                                                            #line 207 "PrintCSharp.cpp.template"
                                                                decreaseIndent();
                                                              }
                                                              /*
                                                              increaseIndent()
                                                              openMethod(L"String ", L"", L"getInput", L"");
                                                            #line 333 "PrintCSharp.cpp"
  append(L"\n");
  append(L"{\n");
  append(L"  return ");
                                                            #line 214 "PrintCSharp.cpp.template"
                                                              if (useGlr)
                                                              {
                                                            #line 340 "PrintCSharp.cpp"
  append(L"parser.");
                                                            #line 216 "PrintCSharp.cpp.template"
                                                              }
                                                            #line 344 "PrintCSharp.cpp"
  append(L"input;\n");
  append(L"}\n");
                                                            #line 219 "PrintCSharp.cpp.template"
                                                              openMethod(L"int ", L"", L"getTokenOffset", L"");
                                                            #line 349 "PrintCSharp.cpp"
  append(L"\n");
  append(L"{\n");
  append(L"  return b0;\n");
  append(L"}\n");
                                                            #line 224 "PrintCSharp.cpp.template"
                                                              openMethod(L"int ", L"", L"getTokenEnd", L"");
                                                            #line 356 "PrintCSharp.cpp"
  append(L"\n");
  append(L"{\n");
  append(L"  return e0;\n");
  append(L"}\n");
                                                            #line 229 "PrintCSharp.cpp.template"
                                                              decreaseIndent();
                                                              */
                                                            }

                                                            void PrintCSharp::openStackNode()
                                                            {
                                                            #line 368 "PrintCSharp.cpp"
  append(L"\n");
  append(L"private class StackNode\n");
  append(L"{\n");
  append(L"  public int state;");
                                                            #line 239 "PrintCSharp.cpp.template"
                                                              if (grammar->states->hasLookback)
                                                              {
                                                            #line 376 "PrintCSharp.cpp"
  append(L"\n");
  append(L"  public int code;");
                                                            #line 242 "PrintCSharp.cpp.template"
                                                              }
                                                            #line 381 "PrintCSharp.cpp"
  append(L"\n");
  append(L"  public int pos;\n");
  append(L"  public StackNode link;\n");
  append(L"\n");
  append(L"  public StackNode(int state, ");
                                                            #line 248 "PrintCSharp.cpp.template"
                                                              if (grammar->states->hasLookback)
                                                              {
                                                            #line 390 "PrintCSharp.cpp"
  append(L"int code, ");
                                                            #line 250 "PrintCSharp.cpp.template"
                                                              }
                                                            #line 394 "PrintCSharp.cpp"
  append(L"int pos, StackNode link)\n");
  append(L"  {\n");
  append(L"    this.state = state;");
                                                            #line 254 "PrintCSharp.cpp.template"
                                                              if (grammar->states->hasLookback)
                                                              {
                                                            #line 401 "PrintCSharp.cpp"
  append(L"\n");
  append(L"    this.code = code;");
                                                            #line 257 "PrintCSharp.cpp.template"
                                                              }
                                                            #line 406 "PrintCSharp.cpp"
  append(L"\n");
  append(L"    this.pos = pos;\n");
  append(L"    this.link = link;\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  public override bool Equals(Object obj)\n");
  append(L"  {\n");
  append(L"    StackNode lhs = this;\n");
  append(L"    StackNode rhs = (StackNode) obj;\n");
  append(L"    while (lhs != null && rhs != null)\n");
  append(L"    {\n");
  append(L"      if (lhs == rhs) return true;\n");
  append(L"      if (lhs.state != rhs.state) return false;");
                                                            #line 270 "PrintCSharp.cpp.template"
                                                              if (grammar->states->hasLookback)
                                                              {
                                                            #line 423 "PrintCSharp.cpp"
  append(L"\n");
  append(L"      if (lhs.code != rhs.code) return false;");
                                                            #line 273 "PrintCSharp.cpp.template"
                                                              }
                                                            #line 428 "PrintCSharp.cpp"
  append(L"\n");
  append(L"      if (lhs.pos != rhs.pos) return false;\n");
  append(L"      lhs = lhs.link;\n");
  append(L"      rhs = rhs.link;\n");
  append(L"    }\n");
  append(L"    return lhs == rhs;\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  public override int GetHashCode()\n");
  append(L"  {\n");
  append(L"    return 0;\n");
  append(L"  }\n");
                                                            #line 286 "PrintCSharp.cpp.template"
                                                              increaseIndent();
                                                              beginPublic();
                                                            }

                                                            void PrintCSharp::closeStackNode()
                                                            {
                                                              beginNonpublic();
                                                              decreaseIndent();
                                                            #line 450 "PrintCSharp.cpp"
  append(L"\n");
  append(L"}\n");
                                                            #line 296 "PrintCSharp.cpp.template"
                                                              if (hasCustomCode)
                                                              {
                                                            #line 456 "PrintCSharp.cpp"
  append(L"\n");
  append(L"private class DeferredCode\n");
  append(L"{\n");
  append(L"  public DeferredCode link;\n");
  append(L"  public int codeId;\n");
  append(L"  public int b0;\n");
  append(L"  public int e0;\n");
  append(L"\n");
  append(L"  public DeferredCode(DeferredCode link, int codeId, int b0, int e0)\n");
  append(L"  {\n");
  append(L"    this.link = link;\n");
  append(L"    this.codeId = codeId;\n");
  append(L"    this.b0 = b0;\n");
  append(L"    this.e0 = e0;\n");
  append(L"  }\n");
  append(L"}\n");
                                                            #line 314 "PrintCSharp.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                            #line 477 "PrintCSharp.cpp"
  append(L"\n");
  append(L"private abstract class DeferredEvent\n");
  append(L"{\n");
  append(L"  public DeferredEvent link;\n");
  append(L"  public String name;\n");
  append(L"  public int begin;\n");
  append(L"  public int end;\n");
  append(L"\n");
  append(L"  public DeferredEvent(DeferredEvent link, String name, int begin, int end)\n");
  append(L"  {\n");
  append(L"    this.link = link;\n");
  append(L"    this.name = name;\n");
  append(L"    this.begin = begin;\n");
  append(L"    this.end = end;\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  public abstract void execute(BottomUpEventHandler eventHandler);\n");
  append(L"\n");
  append(L"  public void release(BottomUpEventHandler eventHandler)\n");
  append(L"  {\n");
  append(L"    DeferredEvent current = this;\n");
  append(L"    DeferredEvent predecessor = current.link;\n");
  append(L"    current.link = null;\n");
  append(L"    while (predecessor != null)\n");
  append(L"    {\n");
  append(L"      DeferredEvent next = predecessor.link;\n");
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
  append(L"  public void show(BottomUpEventHandler eventHandler)\n");
  append(L"  {\n");
  append(L"    Stack<DeferredEvent> stack = new Stack<DeferredEvent>();\n");
  append(L"    for (DeferredEvent current = this; current != null; current = current.link)\n");
  append(L"    {\n");
  append(L"      stack.Push(current);\n");
  append(L"    }\n");
  append(L"    while (stack.Count != 0)\n");
  append(L"    {\n");
  append(L"      stack.Pop().execute(eventHandler);\n");
  append(L"    }\n");
  append(L"  }\n");
  append(L"}\n");
  append(L"\n");
  append(L"private class TerminalEvent : DeferredEvent\n");
  append(L"{\n");
  append(L"  public TerminalEvent(DeferredEvent link, String name, int begin, int end)\n");
  append(L"  : base(link, name, begin, end)\n");
  append(L"  {\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  public override void execute(BottomUpEventHandler eventHandler)\n");
  append(L"  {\n");
  append(L"    eventHandler.terminal(name, begin, end);\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  public override String ToString()\n");
  append(L"  {\n");
  append(L"    return \"terminal(\" + name + \", \" + begin + \", \" + end + \")\";\n");
  append(L"  }\n");
  append(L"}\n");
  append(L"\n");
  append(L"private class NonterminalEvent : DeferredEvent\n");
  append(L"{\n");
  append(L"  public int count;\n");
  append(L"\n");
  append(L"  public NonterminalEvent(DeferredEvent link, String name, int begin, int end, int count)\n");
  append(L"  : base(link, name, begin, end)\n");
  append(L"  {\n");
  append(L"    this.count = count;\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  public override void execute(BottomUpEventHandler eventHandler)\n");
  append(L"  {\n");
  append(L"    eventHandler.nonterminal(name, begin, end, count);\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  public override String ToString()\n");
  append(L"  {\n");
  append(L"    return \"nonterminal(\" + name + \", \" + begin + \", \" + end + \", \" + count + \")\";\n");
  append(L"  }\n");
  append(L"}\n");
                                                            #line 407 "PrintCSharp.cpp.template"
                                                              }
                                                            #line 570 "PrintCSharp.cpp"
  append(L"\n");
  append(L"private static int PARSING = 0;\n");
  append(L"private static int ACCEPTED = 1;\n");
  append(L"private static int ERROR = 2;\n");
  append(L"\n");
  append(L"private ParsingThread parse(int target, int initialState, ");
                                                            #line 413 "PrintCSharp.cpp.template"
                                                                       if (tree)
                                                              {
                                                            #line 580 "PrintCSharp.cpp"
  append(L"BottomUpEventHandler eventHandler, ");
                                                            #line 416 "PrintCSharp.cpp.template"
                                                              }
                                                            #line 584 "PrintCSharp.cpp"
  append(L"ParsingThread thread)\n");
  append(L"{\n");
  append(L"  Heap<ParsingThread> threads = thread.open(initialState");
                                                            #line 419 "PrintCSharp.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 591 "PrintCSharp.cpp"
  append(L", eventHandler");
                                                            #line 421 "PrintCSharp.cpp.template"
                                                              }
                                                            #line 595 "PrintCSharp.cpp"
  append(L", target);\n");
  append(L"  for (;;)\n");
  append(L"  {\n");
  append(L"    thread = threads.poll();\n");
  append(L"    if (thread.accepted)\n");
  append(L"    {\n");
  append(L"      ParsingThread other = null;\n");
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
                                                            #line 440 "PrintCSharp.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 618 "PrintCSharp.cpp"
  append(L", thread.deferredEvent, other.deferredEvent");
                                                            #line 443 "PrintCSharp.cpp.template"
                                                              }
                                                            #line 622 "PrintCSharp.cpp"
  append(L");\n");
  append(L"      }");
                                                            #line 446 "PrintCSharp.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 628 "PrintCSharp.cpp"
  append(L"\n");
  append(L"      if (thread.deferredEvent != null)\n");
  append(L"      {\n");
  append(L"        thread.deferredEvent.release(eventHandler);\n");
  append(L"        thread.deferredEvent = null;\n");
  append(L"      }");
                                                            #line 453 "PrintCSharp.cpp.template"
                                                              }
                                                              if (hasCustomCode)
                                                              {
                                                            #line 639 "PrintCSharp.cpp"
  append(L"\n");
  append(L"      thread.executeDeferredCode();");
                                                            #line 457 "PrintCSharp.cpp.template"
                                                              }
                                                            #line 644 "PrintCSharp.cpp"
  append(L"\n");
  append(L"      return thread;\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    if (! threads.isEmpty())\n");
  append(L"    {\n");
  append(L"      if (threads.peek().Equals(thread))\n");
  append(L"      {\n");
  append(L"        rejectAmbiguity(thread.stack.pos, thread.e0");
                                                            #line 466 "PrintCSharp.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 657 "PrintCSharp.cpp"
  append(L", thread.deferredEvent, threads.peek().deferredEvent");
                                                            #line 469 "PrintCSharp.cpp.template"
                                                              }
                                                            #line 661 "PrintCSharp.cpp"
  append(L");\n");
  append(L"      }\n");
  append(L"    }");
                                                            #line 472 "PrintCSharp.cpp.template"
                                                              if (tree || hasCustomCode)
                                                              {
                                                            #line 668 "PrintCSharp.cpp"
  append(L"\n");
  append(L"    else\n");
  append(L"    {");
                                                            #line 476 "PrintCSharp.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 675 "PrintCSharp.cpp"
  append(L"\n");
  append(L"      if (thread.deferredEvent != null)\n");
  append(L"      {\n");
  append(L"        thread.deferredEvent.release(eventHandler);\n");
  append(L"        thread.deferredEvent = null;\n");
  append(L"      }");
                                                            #line 483 "PrintCSharp.cpp.template"
                                                                }
                                                                if (hasCustomCode)
                                                                {
                                                            #line 686 "PrintCSharp.cpp"
  append(L"\n");
  append(L"      thread.executeDeferredCode();");
                                                            #line 487 "PrintCSharp.cpp.template"
                                                                }
                                                            #line 691 "PrintCSharp.cpp"
  append(L"\n");
  append(L"    }");
                                                            #line 489 "PrintCSharp.cpp.template"
                                                              }
                                                            #line 696 "PrintCSharp.cpp"
  append(L"\n");
  append(L"\n");
  append(L"    int status;\n");
  append(L"    for (;;)\n");
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
  append(L"\n");
  append(L"private void rejectAmbiguity(int begin, int end");
                                                            #line 515 "PrintCSharp.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 726 "PrintCSharp.cpp"
  append(L", DeferredEvent first, DeferredEvent second");
                                                            #line 518 "PrintCSharp.cpp.template"
                                                              }
                                                            #line 730 "PrintCSharp.cpp"
  append(L")\n");
  append(L"{");
                                                            #line 520 "PrintCSharp.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 736 "PrintCSharp.cpp"
  append(L"\n");
  append(L"  ParseTreeBuilder treeBuilder = new ParseTreeBuilder();\n");
  append(L"  treeBuilder.reset(input);\n");
  append(L"  second.show(treeBuilder);\n");
  append(L"  treeBuilder.nonterminal(\"ALTERNATIVE\", treeBuilder.getStack()[0].begin, treeBuilder.getStack()[treeBuilder.getTop()].end, treeBuilder.getTop() + 1);\n");
  append(L"  Symbol secondTree = treeBuilder.pop(1)[0];\n");
  append(L"  first.show(treeBuilder);\n");
  append(L"  treeBuilder.nonterminal(\"ALTERNATIVE\", treeBuilder.getStack()[0].begin, treeBuilder.getStack()[treeBuilder.getTop()].end, treeBuilder.getTop() + 1);\n");
  append(L"  treeBuilder.push(secondTree);\n");
  append(L"  treeBuilder.nonterminal(\"AMBIGUOUS\", treeBuilder.getStack()[0].begin, treeBuilder.getStack()[treeBuilder.getTop()].end, 2);");
                                                            #line 532 "PrintCSharp.cpp.template"
                                                              }
                                                            #line 749 "PrintCSharp.cpp"
  append(L"\n");
  append(L"  throw new ParseException(begin, end");
                                                            #line 534 "PrintCSharp.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 755 "PrintCSharp.cpp"
  append(L", treeBuilder");
                                                            #line 536 "PrintCSharp.cpp.template"
                                                              }
                                                            #line 759 "PrintCSharp.cpp"
  append(L");\n");
  append(L"}\n");
  append(L"\n");
  append(L"private ParsingThread thread = null;");
                                                            #line 540 "PrintCSharp.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 767 "PrintCSharp.cpp"
  append(L"\n");
  append(L"private BottomUpEventHandler eventHandler;");
                                                            #line 543 "PrintCSharp.cpp.template"
                                                              }
                                                            #line 772 "PrintCSharp.cpp"
  append(L"\n");
  append(L"private String input = null;\n");
  append(L"private int size = 0;");
                                                            #line 546 "PrintCSharp.cpp.template"
                                                              if (trace)
                                                              {
                                                            #line 779 "PrintCSharp.cpp"
  append(L"\n");
  append(L"private TextWriter err = Console.Error;");
                                                            #line 549 "PrintCSharp.cpp.template"
                                                              }
                                                            #line 784 "PrintCSharp.cpp"
  append(L"\n");
  append(L"private int maxId = 0;\n");
                                                            #line 552 "PrintCSharp.cpp.template"
                                                            }

                                                            void PrintCSharp::openThread()
                                                            {
                                                            #line 792 "PrintCSharp.cpp"
  append(L"\n");
  append(L"private class ParsingThread : IComparable<ParsingThread>\n");
  append(L"{\n");
  append(L"  public ");
                                                            #line 559 "PrintCSharp.cpp.template"
                                                              print(className.c_str());
                                                            #line 799 "PrintCSharp.cpp"
  append(L" parser;\n");
  append(L"  public Heap<ParsingThread> threads;\n");
  append(L"  public bool accepted;\n");
  append(L"  public StackNode stack;\n");
  append(L"  public int state;\n");
  append(L"  public int action;\n");
  append(L"  public int target;");
                                                            #line 566 "PrintCSharp.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 810 "PrintCSharp.cpp"
  append(L"\n");
  append(L"  public DeferredEvent deferredEvent;");
                                                            #line 569 "PrintCSharp.cpp.template"
                                                              }
                                                              if (hasCustomCode)
                                                              {
                                                            #line 817 "PrintCSharp.cpp"
  append(L"\n");
  append(L"  public DeferredCode deferredCode;");
                                                            #line 573 "PrintCSharp.cpp.template"
                                                              }
                                                            #line 822 "PrintCSharp.cpp"
  append(L"\n");
  append(L"  public int id;\n");
  append(L"\n");
  append(L"  public Heap<ParsingThread> open(int initialState");
                                                            #line 577 "PrintCSharp.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 830 "PrintCSharp.cpp"
  append(L", BottomUpEventHandler eh");
                                                            #line 579 "PrintCSharp.cpp.template"
                                                              }
                                                            #line 834 "PrintCSharp.cpp"
  append(L", int t)\n");
  append(L"  {\n");
  append(L"    accepted = false;\n");
  append(L"    target = t;");
                                                            #line 583 "PrintCSharp.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 842 "PrintCSharp.cpp"
  append(L"\n");
  append(L"    eventHandler = eh;\n");
  append(L"    if (eventHandler != null)\n");
  append(L"    {\n");
  append(L"      eventHandler.reset(parser.input);\n");
  append(L"    }\n");
  append(L"    deferredEvent = null;");
                                                            #line 591 "PrintCSharp.cpp.template"
                                                              }
                                                              if (hasCustomCode && useGlr)
                                                              {
                                                            #line 854 "PrintCSharp.cpp"
  append(L"\n");
  append(L"    deferredCode = null;");
                                                            #line 595 "PrintCSharp.cpp.template"
                                                         }
                                                            #line 859 "PrintCSharp.cpp"
  append(L"\n");
  append(L"    stack = new StackNode(-1, ");
                                                            #line 598 "PrintCSharp.cpp.template"
                                                              if (grammar->states->hasLookback)
                                                              {
                                                            #line 865 "PrintCSharp.cpp"
  append(L"0, ");
                                                            #line 600 "PrintCSharp.cpp.template"
                                                              }
                                                            #line 869 "PrintCSharp.cpp"
  append(L"e0, null);\n");
  append(L"    state = initialState;\n");
  append(L"    action = predict(initialState);\n");
  append(L"    bw = e0;\n");
  append(L"    bs = e0;");
                                                            #line 605 "PrintCSharp.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 878 "PrintCSharp.cpp"
  append(L"\n");
  append(L"    es = e0;");
                                                            #line 608 "PrintCSharp.cpp.template"
                                                              }
                                                            #line 883 "PrintCSharp.cpp"
  append(L"\n");
  append(L"    threads = new Heap<ParsingThread>();\n");
  append(L"    threads.offer(this);\n");
  append(L"    return threads;\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  public ParsingThread copy(ParsingThread other, int action)\n");
  append(L"  {\n");
  append(L"    this.action = action;\n");
  append(L"    accepted = other.accepted;\n");
  append(L"    target = other.target;\n");
  append(L"    parser = other.parser;\n");
  append(L"    bs = other.bs;\n");
  append(L"    bw = other.bw;");
                                                            #line 622 "PrintCSharp.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 901 "PrintCSharp.cpp"
  append(L"\n");
  append(L"    es = other.es;\n");
  append(L"    eventHandler = other.eventHandler;\n");
  append(L"    deferredEvent = other.deferredEvent;");
                                                            #line 627 "PrintCSharp.cpp.template"
                                                              }
                                                              if (hasCustomCode)
                                                              {
                                                            #line 910 "PrintCSharp.cpp"
  append(L"\n");
  append(L"    deferredCode = other.deferredCode;");
                                                            #line 631 "PrintCSharp.cpp.template"
                                                              }
                                                            #line 915 "PrintCSharp.cpp"
  append(L"\n");
  append(L"    id = ++parser.maxId;\n");
  append(L"    threads = other.threads;\n");
  append(L"    state = other.state;\n");
  append(L"    stack = other.stack;\n");
  append(L"    b0 = other.b0;\n");
  append(L"    e0 = other.e0;");
                                                            #line 638 "PrintCSharp.cpp.template"
                                                              for (size_t i = 1; i <= grammar->k; ++i)
                                                              {
                                                                const wchar_t *iString = format.toString<wchar_t>(i);
                                                            #line 927 "PrintCSharp.cpp"
  append(L"\n");
  append(L"    l");
                                                            #line 642 "PrintCSharp.cpp.template"
                                                                print(iString);
                                                            #line 932 "PrintCSharp.cpp"
  append(L" = other.l");
                                                            #line 643 "PrintCSharp.cpp.template"
                                                                print(iString);
                                                            #line 936 "PrintCSharp.cpp"
  append(L";\n");
  append(L"    b");
                                                            #line 645 "PrintCSharp.cpp.template"
                                                                print(iString);
                                                            #line 941 "PrintCSharp.cpp"
  append(L" = other.b");
                                                            #line 646 "PrintCSharp.cpp.template"
                                                                print(iString);
                                                            #line 945 "PrintCSharp.cpp"
  append(L";\n");
  append(L"    e");
                                                            #line 648 "PrintCSharp.cpp.template"
                                                                print(iString);
                                                            #line 950 "PrintCSharp.cpp"
  append(L" = other.e");
                                                            #line 649 "PrintCSharp.cpp.template"
                                                                print(iString);
                                                            #line 954 "PrintCSharp.cpp"
  append(L";");
                                                            #line 650 "PrintCSharp.cpp.template"
                                                              }
                                                            #line 958 "PrintCSharp.cpp"
  append(L"\n");
  append(L"    end = other.end;\n");
  append(L"    return this;\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  public int CompareTo(ParsingThread other)\n");
  append(L"  {\n");
  append(L"    if (accepted != other.accepted)\n");
  append(L"      return accepted ? 1 : -1;\n");
  append(L"    int comp = e0 - other.e0;\n");
  append(L"    return comp == 0 ? id - other.id : comp;\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  public override bool Equals(Object obj)\n");
  append(L"  {\n");
  append(L"    ParsingThread other = (ParsingThread) obj;\n");
  append(L"    if (accepted != other.accepted) return false;\n");
  append(L"    if (b1 != other.b1) return false;\n");
  append(L"    if (e1 != other.e1) return false;\n");
  append(L"    if (l1 != other.l1) return false;\n");
  append(L"    if (state != other.state) return false;\n");
  append(L"    if (action != other.action) return false;\n");
  append(L"    if (! stack.Equals(other.stack)) return false;\n");
  append(L"    return true;\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  public override int GetHashCode()\n");
  append(L"  {\n");
  append(L"    return 0;\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  public int parse()\n");
  append(L"  {");
                                                            #line 683 "PrintCSharp.cpp.template"
                                                              increaseIndent();
                                                              beginPublic();
                                                            }

                                                            void PrintCSharp::printFlush(int i, bool withinThread)
                                                            {
                                                              if (trace)
                                                              {
                                                                increaseIndent(i);
                                                            #line 1002 "PrintCSharp.cpp"
  append(L"\n");
                                                            #line 693 "PrintCSharp.cpp.template"
                                                                if (useGlr && withinThread)
                                                                {
                                                            #line 1007 "PrintCSharp.cpp"
  append(L"parser.");
                                                            #line 695 "PrintCSharp.cpp.template"
                                                                }
                                                            #line 1011 "PrintCSharp.cpp"
  append(L"flushTrace();");
                                                            #line 696 "PrintCSharp.cpp.template"
                                                                decreaseIndent(i);
                                                              }
                                                            }

                                                            void PrintCSharp::openMethod(const wchar_t *type,
                                                                                         const wchar_t *prefix,
                                                                                         const wchar_t *name,
                                                                                         const wchar_t *args,
                                                                                         bool constant,
                                                                                         const wchar_t *clazz)
                                                            {
                                                            #line 1025 "PrintCSharp.cpp"
  append(L"\n");
                                                            #line 708 "PrintCSharp.cpp.template"
                                                              print(visibility);
                                                            #line 1029 "PrintCSharp.cpp"
  append(L" ");
                                                            #line 709 "PrintCSharp.cpp.template"
                                                              print(prefix);
                                                              print(type);
                                                              print(name);
                                                            #line 1035 "PrintCSharp.cpp"
  append(L"(");
                                                            #line 712 "PrintCSharp.cpp.template"
                                                              print(args);
                                                            #line 1039 "PrintCSharp.cpp"
  append(L")");
                                                            #line 713 "PrintCSharp.cpp.template"
                                                            }

                                                            void PrintCSharp::privateVars()
                                                            {
                                                              if (trace)
                                                              {
                                                            #line 1048 "PrintCSharp.cpp"
  append(L"\n");
  append(L"  private String lookaheadString()\n");
  append(L"  {\n");
  append(L"    String result = \"\";\n");
  append(L"    if (l1 > 0)\n");
  append(L"    {\n");
  append(L"      result += TOKEN[l1];");
                                                            #line 725 "PrintCSharp.cpp.template"
                                                              for (size_t i = 2; i <= grammar->k; ++i)
                                                              {
                                                            #line 1059 "PrintCSharp.cpp"
  append(L"\n");
  append(L"      if (l");
                                                            #line 728 "PrintCSharp.cpp.template"
                                                                print(format.toString<wchar_t>(i));
                                                            #line 1064 "PrintCSharp.cpp"
  append(L" > 0)\n");
  append(L"      {\n");
  append(L"        result += \" \" + TOKEN[l");
                                                            #line 731 "PrintCSharp.cpp.template"
                                                                print(format.toString<wchar_t>(i));
                                                            #line 1070 "PrintCSharp.cpp"
  append(L"];");
                                                            #line 732 "PrintCSharp.cpp.template"
                                                                increaseIndent();
                                                              }
                                                              for (size_t i = 2; i <= grammar->k; ++i)
                                                              {
                                                                decreaseIndent();
                                                            #line 1078 "PrintCSharp.cpp"
  append(L"\n");
  append(L"      }");
                                                            #line 738 "PrintCSharp.cpp.template"
                                                              }
                                                            #line 1083 "PrintCSharp.cpp"
  append(L"\n");
  append(L"    }\n");
  append(L"    return result;\n");
  append(L"  }\n");
                                                            #line 743 "PrintCSharp.cpp.template"
                                                              }
                                                            #line 1090 "PrintCSharp.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 745 "PrintCSharp.cpp.template"
                                                              print(useGlr ? L"public" : L"private");
                                                            #line 1095 "PrintCSharp.cpp"
  append(L" int ");
                                                            #line 746 "PrintCSharp.cpp.template"
                                                              if (! isLrParser && (grammar->k > 1 ||
                                                                                   memoization ||
                                                                                   ! grammar->decisionPoints.empty()))
                                                              {
                                                            #line 1102 "PrintCSharp.cpp"
  append(L"lk,");
                                                            #line 750 "PrintCSharp.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 1108 "PrintCSharp.cpp"
  append(L"   ");
                                                            #line 754 "PrintCSharp.cpp.template"
                                                              }
                                                            #line 1112 "PrintCSharp.cpp"
  append(L" b0, e0;");
                                                            #line 755 "PrintCSharp.cpp.template"
                                                              for (size_t k = 1; k <= grammar->k; ++k)
                                                              {
                                                                Format format;
                                                                wchar_t *asString = format.toString<wchar_t>(k);
                                                            #line 1119 "PrintCSharp.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 760 "PrintCSharp.cpp.template"
                                                                print(useGlr ? L"public" : L"private");
                                                            #line 1124 "PrintCSharp.cpp"
  append(L" int l");
                                                            #line 761 "PrintCSharp.cpp.template"
                                                                print(asString);
                                                            #line 1128 "PrintCSharp.cpp"
  append(L", b");
                                                            #line 762 "PrintCSharp.cpp.template"
                                                                print(asString);
                                                            #line 1132 "PrintCSharp.cpp"
  append(L", e");
                                                            #line 763 "PrintCSharp.cpp.template"
                                                                print(asString);
                                                            #line 1136 "PrintCSharp.cpp"
  append(L";");
                                                            #line 764 "PrintCSharp.cpp.template"
                                                              }
                                                              if (hasBacktracking)
                                                              {
                                                            #line 1142 "PrintCSharp.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 768 "PrintCSharp.cpp.template"
                                                                print(useGlr ? L"public" : L"private");
                                                            #line 1147 "PrintCSharp.cpp"
  append(L" int bx, ex, sx, lx, tx;");
                                                            #line 769 "PrintCSharp.cpp.template"
                                                              }
                                                              if (isLrParser && ! useGlr)
                                                              {
                                                            #line 1153 "PrintCSharp.cpp"
  append(L"\n");
  append(L"  private int[] iStack = new int[");
                                                            #line 773 "PrintCSharp.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 1159 "PrintCSharp.cpp"
  append(L"192");
                                                            #line 775 "PrintCSharp.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1165 "PrintCSharp.cpp"
  append(L"128");
                                                            #line 778 "PrintCSharp.cpp.template"
                                                                }
                                                            #line 1169 "PrintCSharp.cpp"
  append(L"];\n");
  append(L"  private int top = -1;");
                                                            #line 780 "PrintCSharp.cpp.template"
                                                              }
                                                              if (useGlr)
                                                              {
                                                            #line 1176 "PrintCSharp.cpp"
  append(L"\n");
  append(L"  public int bw, bs;");
                                                            #line 784 "PrintCSharp.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                                if (isLrParser)
                                                                {
                                                                  if (useGlr)
                                                                  {
                                                            #line 1187 "PrintCSharp.cpp"
  append(L"\n");
  append(L"  public int es;");
                                                            #line 792 "PrintCSharp.cpp.template"
                                                                  }
                                                            #line 1192 "PrintCSharp.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 794 "PrintCSharp.cpp.template"
                                                                  print(useGlr ? L"public" : L"private");
                                                            #line 1197 "PrintCSharp.cpp"
  append(L" BottomUpEventHandler eventHandler = null;");
                                                            #line 795 "PrintCSharp.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1203 "PrintCSharp.cpp"
  append(L"\n");
  append(L"  private EventHandler eventHandler = null;");
                                                            #line 799 "PrintCSharp.cpp.template"
                                                                }
                                                              }
                                                              if (memoization)
                                                              {
                                                                int bits = Math::bits(grammar->conflictCount);
                                                            #line 1212 "PrintCSharp.cpp"
  append(L"\n");
  append(L"  private IDictionary<int, int> memo = new Dictionary<int, int>();");
                                                            #line 806 "PrintCSharp.cpp.template"
                                                                if (grammar->noThrow)
                                                                {
                                                            #line 1218 "PrintCSharp.cpp"
  append(L"\n");
  append(L"  private bool viable;");
                                                            #line 809 "PrintCSharp.cpp.template"
                                                                }
                                                            #line 1223 "PrintCSharp.cpp"
  append(L"\n");
  append(L"\n");
  append(L"  private void memoize(int i, int e, int v)\n");
  append(L"  {\n");
  append(L"    memo.Add((e << ");
                                                            #line 814 "PrintCSharp.cpp.template"
                                                                print(format.toString<wchar_t>(bits));
                                                            #line 1231 "PrintCSharp.cpp"
  append(L") + i, v);\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  private int memoized(int i, int e)\n");
  append(L"  {\n");
  append(L"    int value = 0;\n");
  append(L"    memo.TryGetValue((e << ");
                                                            #line 821 "PrintCSharp.cpp.template"
                                                                print(format.toString<wchar_t>(bits));
                                                            #line 1241 "PrintCSharp.cpp"
  append(L") + i, out value);\n");
  append(L"    return value;\n");
  append(L"  }");
                                                            #line 824 "PrintCSharp.cpp.template"
                                                              }
                                                            }

                                                            void PrintCSharp::printFileProcessor()
                                                            {
                                                            #line 1251 "PrintCSharp.cpp"
  append(L"\n");
  append(L"  private static bool quiet = false;\n");
  append(L"  private static long parsed = 0;\n");
  append(L"  private static int errorCount = 0;\n");
  append(L"  private static List<ParseJob> parsers = new List<ParseJob>();\n");
  append(L"\n");
  append(L"  private class ParseJob\n");
  append(L"  {\n");
  append(L"    public String name;\n");
  append(L"    public String input;\n");
  append(L"    public ");
                                                            #line 839 "PrintCSharp.cpp.template"
                                                              print(className.c_str());
                                                            #line 1265 "PrintCSharp.cpp"
  append(L" parser;");
                                                            #line 840 "PrintCSharp.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 1270 "PrintCSharp.cpp"
  append(L"\n");
  append(L"    public ContentCounter contentCounter;");
                                                            #line 843 "PrintCSharp.cpp.template"
                                                                if (isLrParser)
                                                                {
                                                            #line 1276 "PrintCSharp.cpp"
  append(L"\n");
  append(L"    public ParseTreeBuilder parseTreeBuilder;");
                                                            #line 846 "PrintCSharp.cpp.template"
                                                                }
                                                              }
                                                            #line 1282 "PrintCSharp.cpp"
  append(L"\n");
  append(L"\n");
  append(L"    public ParseJob(String s, String i)\n");
  append(L"    {\n");
  append(L"      name = s;\n");
  append(L"      input = i;");
                                                            #line 853 "PrintCSharp.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 1292 "PrintCSharp.cpp"
  append(L"\n");
  append(L"      contentCounter = new ContentCounter();");
                                                            #line 856 "PrintCSharp.cpp.template"
                                                                if (isLrParser)
                                                                {
                                                            #line 1298 "PrintCSharp.cpp"
  append(L"\n");
  append(L"      parseTreeBuilder = new ParseTreeBuilder();");
                                                            #line 859 "PrintCSharp.cpp.template"
                                                                }
                                                              }
                                                            #line 1304 "PrintCSharp.cpp"
  append(L"\n");
  append(L"      parser = new ");
                                                            #line 862 "PrintCSharp.cpp.template"
                                                              print(className.c_str());
                                                            #line 1309 "PrintCSharp.cpp"
  append(L"(input");
                                                            #line 863 "PrintCSharp.cpp.template"
                                                              if (noLexer)
                                                              {
                                                            #line 1314 "PrintCSharp.cpp"
  append(L", new ");
                                                            #line 865 "PrintCSharp.cpp.template"
                                                                print(className.c_str());
                                                            #line 1318 "PrintCSharp.cpp"
  append(L"Lexer()");
                                                            #line 866 "PrintCSharp.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                                if (isLrParser)
                                                                {
                                                            #line 1326 "PrintCSharp.cpp"
  append(L", parseTreeBuilder");
                                                            #line 871 "PrintCSharp.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1332 "PrintCSharp.cpp"
  append(L", contentCounter");
                                                            #line 874 "PrintCSharp.cpp.template"
                                                                }
                                                              }
                                                            #line 1337 "PrintCSharp.cpp"
  append(L");\n");
  append(L"    }\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  public static int Main(String[] args)\n");
  append(L"  {\n");
  append(L"    if (args.Length == 0)\n");
  append(L"    {\n");
  append(L"      Console.Out.WriteLine(\"Usage: ");
                                                            #line 884 "PrintCSharp.cpp.template"
                                                              print(className.c_str());
                                                            #line 1349 "PrintCSharp.cpp"
  append(L" [-q] [-r N] [-t N] ENDING...\");\n");
  append(L"      Console.Out.WriteLine();\n");
  append(L"      Console.Out.WriteLine(\"  parse all files that have names ending with ENDING, in current dir and below,\");\n");
  append(L"      Console.Out.WriteLine(\"  and display performance summary.\");\n");
  append(L"      Console.Out.WriteLine();\n");
  append(L"      Console.Out.WriteLine(\"  -q     do not show file names\");\n");
  append(L"      Console.Out.WriteLine(\"  -r N   repeat N times\");\n");
  append(L"      Console.Out.WriteLine(\"  -t N   repeat until N seconds have elapsed\");\n");
  append(L"    }\n");
  append(L"    else\n");
  append(L"    {\n");
  append(L"      int repeat = 1;\n");
  append(L"      int timeout = 0;\n");
  append(L"      int i;\n");
  append(L"      for (i = 0; i < args.Length && args[i].StartsWith(\"-\"); ++i)\n");
  append(L"      {\n");
  append(L"        switch (args[i].Length == 2 ? args[i][1] : ' ')\n");
  append(L"        {\n");
  append(L"        case 'q':\n");
  append(L"          quiet = true;\n");
  append(L"          break;\n");
  append(L"        case 'r':\n");
  append(L"          repeat = int.Parse(args[++i]);\n");
  append(L"          timeout = 0;\n");
  append(L"          break;\n");
  append(L"        case 't':\n");
  append(L"          repeat = 0;\n");
  append(L"          timeout = 1000 * int.Parse(args[++i]);\n");
  append(L"          break;\n");
  append(L"        default:\n");
  append(L"          Console.Error.WriteLine(\"invalid option: \" + args[i]);\n");
  append(L"          Environment.Exit(1);\n");
  append(L"          break;\n");
  append(L"        }\n");
  append(L"      }\n");
  append(L"\n");
  append(L"      long start = Environment.TickCount;\n");
  append(L"\n");
  append(L"      for (; i < args.Length; ++i)\n");
  append(L"      {\n");
  append(L"        findFiles(\".\", args[i]);\n");
  append(L"      }\n");
  append(L"\n");
  append(L"      if (parsers.Count > 0)\n");
  append(L"      {\n");
  append(L"        long msec = Environment.TickCount - start;\n");
  append(L"\n");
  append(L"        if (! quiet) Console.Out.WriteLine();\n");
  append(L"        Console.Out.WriteLine(\"loaded \" + parsers.Count + \" file\" +\n");
  append(L"                              (parsers.Count == 1 ? \"\" : \"s\") + \" in \" +\n");
  append(L"                              msec + \" msec\");\n");
  append(L"        if (! quiet) Console.Out.WriteLine();\n");
  append(L"        Console.Out.Flush();\n");
  append(L"\n");
  append(L"        start = Environment.TickCount;\n");
  append(L"        for (i = 0; ; ++i)\n");
  append(L"        {\n");
  append(L"          if (repeat != 0 && i >= repeat) break;\n");
  append(L"          if (timeout != 0 && Environment.TickCount - start >= timeout) break;\n");
  append(L"\n");
  append(L"          foreach (ParseJob job in parsers)\n");
  append(L"          {\n");
  append(L"            if (job.parser != null)\n");
  append(L"            {\n");
  append(L"              try\n");
  append(L"              {\n");
  append(L"                if (! quiet) Console.Out.Write(\"parsing \" + job.name);\n");
  append(L"                job.parser");
                                                            #line 952 "PrintCSharp.cpp.template"
                                                                  if (useGlr)
                                                                  {
                                                            #line 1421 "PrintCSharp.cpp"
  append(L".thread");
                                                            #line 954 "PrintCSharp.cpp.template"
                                                                  }
                                                            #line 1425 "PrintCSharp.cpp"
  append(L".reset(0, 0, 0);\n");
  append(L"                job.parser.");
                                                            #line 956 "PrintCSharp.cpp.template"
                                                              print(methodPrefixParse);
                                                              print(Format::acceptableName<WString>(grammar->startSymbol()->name).c_str());
                                                            #line 1431 "PrintCSharp.cpp"
  append(L"();\n");
  append(L"                if (! quiet) Console.Out.WriteLine();");
                                                            #line 959 "PrintCSharp.cpp.template"
                                                              if (tree)
                                                              {
                                                                if (isLrParser)
                                                                {
                                                            #line 1439 "PrintCSharp.cpp"
  append(L"\n");
  append(L"                job.parseTreeBuilder.serialize(job.contentCounter);");
                                                            #line 965 "PrintCSharp.cpp.template"
                                                                }
                                                            #line 1444 "PrintCSharp.cpp"
  append(L"\n");
  append(L"                if (job.contentCounter.getLength() != job.input.Length)\n");
  append(L"                {\n");
  append(L"                  Console.Error.WriteLine(\"content counter saw \" + job.contentCounter.getLength() + \", but input length is \" + job.input.Length);\n");
  append(L"                  Environment.Exit(1);\n");
  append(L"                }");
                                                            #line 971 "PrintCSharp.cpp.template"
                                                              }
                                                            #line 1453 "PrintCSharp.cpp"
  append(L"\n");
  append(L"                parsed += job.input.Length;\n");
  append(L"              }\n");
  append(L"              catch (ParseException pe)\n");
  append(L"              {\n");
  append(L"                ++errorCount;\n");
  append(L"                if (quiet) Console.Out.Write(\"parsing \" + job.name);\n");
  append(L"                Console.Out.WriteLine(\": error: \" + job.parser.getErrorMessage(pe));\n");
  append(L"                job.parser = null;\n");
  append(L"              }\n");
  append(L"            }\n");
  append(L"          }\n");
  append(L"        }\n");
  append(L"        msec = Environment.TickCount - start;\n");
  append(L"        String mbPerSec = msec == 0\n");
  append(L"                        ? null\n");
  append(L"                        : (parsed / 1024e0 / 1024e0 * 1000e0 / msec).ToString(\"N2\");\n");
  append(L"\n");
  append(L"        if (! quiet) Console.Out.WriteLine();\n");
  append(L"        Console.Out.Write(\"parsed \" + parsed + \" byte\" + (parsed == 1 ? \"\" : \"s\") +\n");
  append(L"                          \" in \" + msec + \" msec\");\n");
  append(L"        if (mbPerSec != null)\n");
  append(L"        {\n");
  append(L"          Console.Out.Write(\" (\" + mbPerSec + \" MB/sec)\");\n");
  append(L"        }\n");
  append(L"        Console.Out.WriteLine();\n");
  append(L"        Console.Out.WriteLine(errorCount + \" error\" + (errorCount == 1 ? \"\" : \"s\"));\n");
  append(L"      }\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    return 0;\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  private static void collectInput(String name, String content)\n");
  append(L"  {\n");
  append(L"    if (! quiet) Console.Out.WriteLine(\"loading \" + name);\n");
  append(L"    parsers.Add(new ParseJob(name, content));\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  private static void findFiles(String f, String filter)\n");
  append(L"  {\n");
  append(L"    if (Directory.Exists(f))\n");
  append(L"    {\n");
  append(L"      DirectoryInfo di = new DirectoryInfo(f);\n");
  append(L"      foreach (DirectoryInfo fi in di.GetDirectories())\n");
  append(L"      {\n");
  append(L"        findFiles(f + \"/\" + fi.Name, filter);\n");
  append(L"      }\n");
  append(L"      foreach (FileInfo fi in di.GetFiles())\n");
  append(L"      {\n");
  append(L"        findFiles(f + \"/\" + fi.Name, filter);\n");
  append(L"      }\n");
  append(L"    }\n");
  append(L"    else if (f.ToLower().EndsWith(filter.ToLower()))\n");
  append(L"    {\n");
  append(L"      collectInput(f, read(f));\n");
  append(L"    }\n");
  append(L"  }\n");
                                                            #line 1031 "PrintCSharp.cpp.template"
                                                            }

                                                            void PrintCSharp::printReadMethod()
                                                            {
                                                            #line 1517 "PrintCSharp.cpp"
  append(L"\n");
  append(L"  private static String read(String input)\n");
  append(L"  {\n");
  append(L"    if (input.StartsWith(\"{\") && input.EndsWith(\"}\"))\n");
  append(L"    {\n");
  append(L"      return input.Substring(1, input.Length - 2);\n");
  append(L"    }\n");
  append(L"    else\n");
  append(L"    {\n");
  append(L"      return File.ReadAllText(input, Encoding.UTF8);\n");
  append(L"    }\n");
  append(L"  }\n");
                                                            #line 1047 "PrintCSharp.cpp.template"
                                                            }

                                                            void PrintCSharp::printInterface()
                                                            {
                                                              if (! packageName.empty())
                                                              {
                                                            #line 1537 "PrintCSharp.cpp"
  append(L"\n");
  append(L"package ");
                                                            #line 1054 "PrintCSharp.cpp.template"
                                                                print(packageName.c_str());
                                                            #line 1542 "PrintCSharp.cpp"
  append(L";\n");
                                                            #line 1056 "PrintCSharp.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                                if (main)
                                                                {
                                                            #line 1550 "PrintCSharp.cpp"
  append(L"\n");
  append(L"import java.io.IOException;\n");
  append(L"import java.io.Writer;\n");
                                                            #line 1064 "PrintCSharp.cpp.template"
                                                                }
                                                              }
                                                            #line 1557 "PrintCSharp.cpp"
  append(L"\n");
  append(L"public interface ");
                                                            #line 1067 "PrintCSharp.cpp.template"
                                                              print(className.c_str());
                                                            #line 1562 "PrintCSharp.cpp"
  append(L"\n");
  append(L"{\n");
  append(L"  void initialize(String input");
                                                            #line 1070 "PrintCSharp.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 1569 "PrintCSharp.cpp"
  append(L", EventHandler eh");
                                                            #line 1072 "PrintCSharp.cpp.template"
                                                              }
                                                            #line 1573 "PrintCSharp.cpp"
  append(L");\n");
  append(L"  void parse();\n");
  append(L"  void reset();\n");
  append(L"  String getErrorMessage(ParseException e);\n");
                                                            #line 1077 "PrintCSharp.cpp.template"
                                                              printParseException();
                                                            #line 1580 "PrintCSharp.cpp"
  append(L"}\n");
                                                            #line 1079 "PrintCSharp.cpp.template"
                                                            }

                                                            void PrintCSharp::printParseException()
                                                            {
                                                            #line 1587 "PrintCSharp.cpp"
  append(L"\n");
  append(L"  public class ParseException : Exception\n");
  append(L"  {\n");
  append(L"    private int begin, end, offending, expected, state;");
                                                            #line 1086 "PrintCSharp.cpp.template"
                                                              if (useGlr)
                                                              {
                                                            #line 1595 "PrintCSharp.cpp"
  append(L"\n");
  append(L"    private bool ambiguousInput;");
                                                            #line 1089 "PrintCSharp.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 1601 "PrintCSharp.cpp"
  append(L"\n");
  append(L"    private ParseTreeBuilder ambiguityDescriptor;");
                                                            #line 1092 "PrintCSharp.cpp.template"
                                                                }
                                                              }
                                                            #line 1607 "PrintCSharp.cpp"
  append(L"\n");
  append(L"\n");
  append(L"    public ParseException(int b, int e, int s, int o, int x)\n");
  append(L"    {\n");
  append(L"      begin = b;\n");
  append(L"      end = e;\n");
  append(L"      state = s;\n");
  append(L"      offending = o;\n");
  append(L"      expected = x;");
                                                            #line 1102 "PrintCSharp.cpp.template"
                                                              if (useGlr)
                                                              {
                                                            #line 1620 "PrintCSharp.cpp"
  append(L"\n");
  append(L"      ambiguousInput = false;");
                                                            #line 1105 "PrintCSharp.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 1626 "PrintCSharp.cpp"
  append(L"\n");
  append(L"      ambiguityDescriptor = null;");
                                                            #line 1108 "PrintCSharp.cpp.template"
                                                                }
                                                              }
                                                            #line 1632 "PrintCSharp.cpp"
  append(L"\n");
  append(L"    }\n");
                                                            #line 1112 "PrintCSharp.cpp.template"
                                                              if (useGlr)
                                                              {
                                                            #line 1638 "PrintCSharp.cpp"
  append(L"\n");
  append(L"    public ParseException(int b, int e");
                                                            #line 1115 "PrintCSharp.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 1644 "PrintCSharp.cpp"
  append(L", ParseTreeBuilder a");
                                                            #line 1117 "PrintCSharp.cpp.template"
                                                                }
                                                            #line 1648 "PrintCSharp.cpp"
  append(L") : this(b, e, -1, -1, -1)\n");
  append(L"    {\n");
  append(L"      ambiguousInput = true;");
                                                            #line 1120 "PrintCSharp.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 1655 "PrintCSharp.cpp"
  append(L"\n");
  append(L"      ambiguityDescriptor = a;");
                                                            #line 1123 "PrintCSharp.cpp.template"
                                                                }
                                                            #line 1660 "PrintCSharp.cpp"
  append(L"\n");
  append(L"    }\n");
                                                            #line 1126 "PrintCSharp.cpp.template"
                                                              }
                                                            #line 1665 "PrintCSharp.cpp"
  append(L"\n");
  append(L"    public String getMessage()\n");
  append(L"    {\n");
  append(L"      return ");
                                                            #line 1130 "PrintCSharp.cpp.template"
                                                              if (useGlr)
                                                              {
                                                            #line 1673 "PrintCSharp.cpp"
  append(L"ambiguousInput\n");
  append(L"           ? \"ambiguous input\"\n");
  append(L"           : ");
                                                            #line 1134 "PrintCSharp.cpp.template"
                                                              }
                                                            #line 1679 "PrintCSharp.cpp"
  append(L"offending < 0\n");
  append(L"           ? \"lexical analysis failed\"\n");
  append(L"           : \"syntax error\";\n");
  append(L"    }\n");
                                                            #line 1139 "PrintCSharp.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 1687 "PrintCSharp.cpp"
  append(L"\n");
  append(L"    public void serialize(EventHandler eventHandler)\n");
  append(L"    {");
                                                            #line 1143 "PrintCSharp.cpp.template"
                                                                if (useGlr)
                                                                {
                                                            #line 1694 "PrintCSharp.cpp"
  append(L"\n");
  append(L"      ambiguityDescriptor.serialize(eventHandler);");
                                                            #line 1146 "PrintCSharp.cpp.template"
                                                                }
                                                            #line 1699 "PrintCSharp.cpp"
  append(L"\n");
  append(L"    }\n");
                                                            #line 1149 "PrintCSharp.cpp.template"
                                                              }
                                                            #line 1704 "PrintCSharp.cpp"
  append(L"\n");
  append(L"    public int getBegin() {return begin;}\n");
  append(L"    public int getEnd() {return end;}\n");
  append(L"    public int getState() {return state;}\n");
  append(L"    public int getOffending() {return offending;}\n");
  append(L"    public int getExpected() {return expected;}\n");
  append(L"    public bool isAmbiguousInput() {return ");
                                                            #line 1156 "PrintCSharp.cpp.template"
                                                              if (useGlr)
                                                              {
                                                            #line 1715 "PrintCSharp.cpp"
  append(L"ambiguousInput");
                                                            #line 1158 "PrintCSharp.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 1721 "PrintCSharp.cpp"
  append(L"false");
                                                            #line 1161 "PrintCSharp.cpp.template"
                                                              }
                                                            #line 1725 "PrintCSharp.cpp"
  append(L";}\n");
  append(L"  }\n");
                                                            #line 1164 "PrintCSharp.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 1731 "PrintCSharp.cpp"
  append(L"\n");
  append(L"  public interface EventHandler\n");
  append(L"  {\n");
  append(L"    void reset(String s);\n");
  append(L"    void startNonterminal(String name");
                                                            #line 1170 "PrintCSharp.cpp.template"
                                                                if (! noPosition)
                                                                {
                                                            #line 1740 "PrintCSharp.cpp"
  append(L", int begin");
                                                            #line 1172 "PrintCSharp.cpp.template"
                                                                }
                                                            #line 1744 "PrintCSharp.cpp"
  append(L");\n");
  append(L"    void endNonterminal(String name");
                                                            #line 1174 "PrintCSharp.cpp.template"
                                                                if (! noPosition)
                                                                {
                                                            #line 1750 "PrintCSharp.cpp"
  append(L", int end");
                                                            #line 1176 "PrintCSharp.cpp.template"
                                                                }
                                                            #line 1754 "PrintCSharp.cpp"
  append(L");\n");
  append(L"    void terminal(String name, int begin, int end);\n");
  append(L"    void whitespace(int begin, int end);\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  public class TopDownTreeBuilder : EventHandler\n");
  append(L"  {\n");
  append(L"    private String input = null;\n");
  append(L"    private Nonterminal[] stack = new Nonterminal[64];\n");
  append(L"    private int top = -1;\n");
  append(L"\n");
  append(L"    public void reset(String input)\n");
  append(L"    {\n");
  append(L"      this.input = input;\n");
  append(L"      top = -1;\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    public void startNonterminal(String name, int begin)\n");
  append(L"    {\n");
  append(L"      Nonterminal nonterminal = new Nonterminal(name, begin, begin, new Symbol[0]);\n");
  append(L"      if (top >= 0) addChild(nonterminal);\n");
  append(L"      if (++top >= stack.Length) Array.Resize(ref stack, stack.Length << 1);\n");
  append(L"      stack[top] = nonterminal;\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    public void endNonterminal(String name, int end)\n");
  append(L"    {\n");
  append(L"      stack[top].end = end;\n");
  append(L"      if (top > 0) --top;\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    public void terminal(String name, int begin, int end)\n");
  append(L"    {\n");
  append(L"      addChild(new Terminal(name, begin, end));\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    public void whitespace(int begin, int end)\n");
  append(L"    {\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    private void addChild(Symbol s)\n");
  append(L"    {\n");
  append(L"      Nonterminal current = stack[top];\n");
  append(L"      Array.Resize(ref current.children, current.children.Length + 1);\n");
  append(L"      current.children[current.children.Length - 1] = s;\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    public void serialize(EventHandler e)\n");
  append(L"    {\n");
  append(L"      e.reset(input);\n");
  append(L"      stack[0].send(e);\n");
  append(L"    }\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  public abstract class Symbol\n");
  append(L"  {\n");
  append(L"    public String name;\n");
  append(L"    public int begin;\n");
  append(L"    public int end;\n");
  append(L"\n");
  append(L"    protected Symbol(String name, int begin, int end)\n");
  append(L"    {\n");
  append(L"      this.name = name;\n");
  append(L"      this.begin = begin;\n");
  append(L"      this.end = end;\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    public abstract void send(EventHandler e);\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  public class Terminal : Symbol\n");
  append(L"  {\n");
  append(L"    public Terminal(String name, int begin, int end)\n");
  append(L"    : base(name, begin, end)\n");
  append(L"    {\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    public override void send(EventHandler e)\n");
  append(L"    {\n");
  append(L"      e.terminal(name, begin, end);\n");
  append(L"    }\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  public class Nonterminal : Symbol\n");
  append(L"  {\n");
  append(L"    public Symbol[] children;\n");
  append(L"\n");
  append(L"    public Nonterminal(String name, int begin, int end, Symbol[] children)\n");
  append(L"    : base(name, begin, end)\n");
  append(L"    {\n");
  append(L"      this.children = children;\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    public override void send(EventHandler e)\n");
  append(L"    {\n");
  append(L"      e.startNonterminal(name, begin);\n");
  append(L"      int pos = begin;\n");
  append(L"      foreach (Symbol c in children)\n");
  append(L"      {\n");
  append(L"        if (pos < c.begin) e.whitespace(pos, c.begin);\n");
  append(L"        c.send(e);\n");
  append(L"        pos = c.end;\n");
  append(L"      }\n");
  append(L"      if (pos < end) e.whitespace(pos, end);\n");
  append(L"      e.endNonterminal(name, end);\n");
  append(L"    }\n");
  append(L"  }\n");
                                                            #line 1284 "PrintCSharp.cpp.template"
                                                                if (isLrParser)
                                                                {
                                                            #line 1865 "PrintCSharp.cpp"
  append(L"\n");
  append(L"  public interface BottomUpEventHandler\n");
  append(L"  {\n");
  append(L"    void reset(String input);\n");
  append(L"    void nonterminal(String name, int begin, int end, int count);\n");
  append(L"    void terminal(String name, int begin, int end);\n");
  append(L"  }\n");
                                                            #line 1293 "PrintCSharp.cpp.template"
                                                                }
                                                                if (main)
                                                                {
                                                            #line 1877 "PrintCSharp.cpp"
  append(L"\n");
  append(L"  public class XmlSerializer : EventHandler\n");
  append(L"  {\n");
  append(L"    private String input;\n");
  append(L"    private String delayedTag;\n");
  append(L"    private TextWriter output;\n");
  append(L"    private bool indent;\n");
  append(L"    private bool hasChildElement;\n");
  append(L"    private int depth;\n");
  append(L"\n");
  append(L"    public XmlSerializer(TextWriter w, bool indent)\n");
  append(L"    {\n");
  append(L"      input = null;\n");
  append(L"      delayedTag = null;\n");
  append(L"      output = w;\n");
  append(L"      this.indent = indent;\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    public void reset(String s)\n");
  append(L"    {\n");
  append(L"      writeOutput(\"<?xml version=\\\"1.0\\\" encoding=\\\"UTF-8\\\"?\" + \">\");\n");
  append(L"      input = s;\n");
  append(L"      hasChildElement = false;\n");
  append(L"      depth = 0;\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    public void startNonterminal(String name");
                                                            #line 1322 "PrintCSharp.cpp.template"
                                                                if (! noPosition)
                                                                {
                                                            #line 1908 "PrintCSharp.cpp"
  append(L", int begin");
                                                            #line 1324 "PrintCSharp.cpp.template"
                                                                }
                                                            #line 1912 "PrintCSharp.cpp"
  append(L")\n");
  append(L"    {\n");
  append(L"      if (delayedTag != null)\n");
  append(L"      {\n");
  append(L"        writeOutput(\"<\");\n");
  append(L"        writeOutput(delayedTag);\n");
  append(L"        writeOutput(\">\");\n");
  append(L"      }\n");
  append(L"      delayedTag = name;\n");
  append(L"      if (indent)\n");
  append(L"      {\n");
  append(L"        writeOutput(\"\\n\");\n");
  append(L"        for (int i = 0; i < depth; ++i)\n");
  append(L"        {\n");
  append(L"          writeOutput(\"  \");\n");
  append(L"        }\n");
  append(L"      }\n");
  append(L"      hasChildElement = false;\n");
  append(L"      ++depth;\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    public void endNonterminal(String name");
                                                            #line 1346 "PrintCSharp.cpp.template"
                                                                if (! noPosition)
                                                                {
                                                            #line 1938 "PrintCSharp.cpp"
  append(L", int end");
                                                            #line 1348 "PrintCSharp.cpp.template"
                                                                }
                                                            #line 1942 "PrintCSharp.cpp"
  append(L")\n");
  append(L"    {\n");
  append(L"      --depth;\n");
  append(L"      if (delayedTag != null)\n");
  append(L"      {\n");
  append(L"        delayedTag = null;\n");
  append(L"        writeOutput(\"<\");\n");
  append(L"        writeOutput(name);\n");
  append(L"        writeOutput(\"/>\");\n");
  append(L"      }\n");
  append(L"      else\n");
  append(L"      {\n");
  append(L"        if (indent)\n");
  append(L"        {\n");
  append(L"          if (hasChildElement)\n");
  append(L"          {\n");
  append(L"            writeOutput(\"\\n\");\n");
  append(L"            for (int i = 0; i < depth; ++i)\n");
  append(L"            {\n");
  append(L"              writeOutput(\"  \");\n");
  append(L"            }\n");
  append(L"          }\n");
  append(L"        }\n");
  append(L"        writeOutput(\"</\");\n");
  append(L"        writeOutput(name);\n");
  append(L"        writeOutput(\">\");\n");
  append(L"      }\n");
  append(L"      hasChildElement = true;\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    public void terminal(String name, int begin, int end)\n");
  append(L"    {\n");
  append(L"      if (name[0] == '\\'')\n");
  append(L"      {\n");
  append(L"        name = \"TOKEN\";\n");
  append(L"      }\n");
  append(L"      startNonterminal(name");
                                                            #line 1385 "PrintCSharp.cpp.template"
                                                                if (! noPosition)
                                                                {
                                                            #line 1983 "PrintCSharp.cpp"
  append(L", begin");
                                                            #line 1387 "PrintCSharp.cpp.template"
                                                                }
                                                            #line 1987 "PrintCSharp.cpp"
  append(L");\n");
  append(L"      characters(begin, end);\n");
  append(L"      endNonterminal(name");
                                                            #line 1390 "PrintCSharp.cpp.template"
                                                                if (! noPosition)
                                                                {
                                                            #line 1994 "PrintCSharp.cpp"
  append(L", end");
                                                            #line 1392 "PrintCSharp.cpp.template"
                                                                }
                                                            #line 1998 "PrintCSharp.cpp"
  append(L");\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    public void whitespace(int begin, int end)\n");
  append(L"    {\n");
  append(L"      characters(begin, end);\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    private void characters(int begin, int end)\n");
  append(L"    {\n");
  append(L"      if (begin < end)\n");
  append(L"      {\n");
  append(L"        if (delayedTag != null)\n");
  append(L"        {\n");
  append(L"          writeOutput(\"<\");\n");
  append(L"          writeOutput(delayedTag);\n");
  append(L"          writeOutput(\">\");\n");
  append(L"          delayedTag = null;\n");
  append(L"        }\n");
  append(L"        writeOutput(input.Substring(begin, end - begin)\n");
  append(L"                         .Replace(\"&\", \"&amp;\")\n");
  append(L"                         .Replace(\"<\", \"&lt;\")\n");
  append(L"                         .Replace(\">\", \"&gt;\"));\n");
  append(L"      }\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    public void writeOutput(String content)\n");
  append(L"    {\n");
  append(L"      output.Write(content);\n");
  append(L"    }\n");
  append(L"  }\n");
                                                            #line 1424 "PrintCSharp.cpp.template"
                                                                }
                                                                if (performanceTest)
                                                                {
                                                            #line 2034 "PrintCSharp.cpp"
  append(L"\n");
  append(L"  public class ContentCounter : EventHandler\n");
  append(L"  {\n");
  append(L"    private int length = 0;\n");
  append(L"    public int getLength() {return length;}\n");
  append(L"    public void reset(String s) {length = 0;}\n");
  append(L"    public void startNonterminal(String name");
                                                            #line 1433 "PrintCSharp.cpp.template"
                                                                  if (! noPosition)
                                                                  {
                                                            #line 2045 "PrintCSharp.cpp"
  append(L", int begin");
                                                            #line 1435 "PrintCSharp.cpp.template"
                                                                  }
                                                            #line 2049 "PrintCSharp.cpp"
  append(L") {}\n");
  append(L"    public void endNonterminal(String name");
                                                            #line 1437 "PrintCSharp.cpp.template"
                                                                  if (! noPosition)
                                                                  {
                                                            #line 2055 "PrintCSharp.cpp"
  append(L", int end");
                                                            #line 1439 "PrintCSharp.cpp.template"
                                                                  }
                                                            #line 2059 "PrintCSharp.cpp"
  append(L") {}\n");
  append(L"    public void terminal(String name, int begin, int end) {length += end - begin;}\n");
  append(L"    public void whitespace(int begin, int end) {length += end - begin;}\n");
  append(L"  }\n");
                                                            #line 1445 "PrintCSharp.cpp.template"
                                                                }
                                                                if (isLrParser)
                                                                {
                                                            #line 2068 "PrintCSharp.cpp"
  append(L"\n");
  append(L"  public class ParseTreeBuilder : BottomUpEventHandler\n");
  append(L"  {\n");
  append(L"    private String input;\n");
  append(L"    private Symbol[] stack = new Symbol[64];\n");
  append(L"    private int top = -1;\n");
  append(L"\n");
  append(L"    public void reset(String input)\n");
  append(L"    {\n");
  append(L"      this.input = input;\n");
  append(L"      top = -1;\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    public Symbol[] getStack() {return stack;}\n");
  append(L"    public int getTop() {return top;}\n");
  append(L"\n");
  append(L"    public void nonterminal(String name, int begin, int end, int count)\n");
  append(L"    {");
                                                            #line 1465 "PrintCSharp.cpp.template"
                                                                if (useGlr)
                                                                {
                                                            #line 2090 "PrintCSharp.cpp"
  append(L"\n");
  append(L"      if (count > top + 1)\n");
  append(L"      {\n");
  append(L"        Symbol[] content = pop(top + 1);\n");
  append(L"        nonterminal(\"UNAMBIGUOUS\", begin, content.Length == 0 ? end : content[0].begin, 0);\n");
  append(L"        foreach (Symbol symbol in content)\n");
  append(L"        {\n");
  append(L"          push(symbol);\n");
  append(L"        }\n");
  append(L"        count = top + 1;\n");
  append(L"      }");
                                                            #line 1477 "PrintCSharp.cpp.template"
                                                                }
                                                            #line 2104 "PrintCSharp.cpp"
  append(L"\n");
  append(L"      push(new Nonterminal(name, begin, end, pop(count)));\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    public void terminal(String name, int begin, int end)\n");
  append(L"    {\n");
  append(L"      push(new Terminal(name, begin, end));\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    public void serialize(EventHandler e)\n");
  append(L"    {\n");
  append(L"      e.reset(input);\n");
  append(L"      for (int i = 0; i <= top; ++i)\n");
  append(L"      {\n");
  append(L"        stack[i].send(e);\n");
  append(L"      }\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    public void push(Symbol s)\n");
  append(L"    {\n");
  append(L"      if (++top >= stack.Length) Array.Resize(ref stack, stack.Length << 1);\n");
  append(L"      stack[top] = s;\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    public Symbol[] pop(int count)\n");
  append(L"    {\n");
  append(L"      top -= count;\n");
  append(L"      Symbol[] result = new Symbol[count];\n");
  append(L"      Array.Copy(stack, top + 1, result, 0, count);\n");
  append(L"      return result;\n");
  append(L"    }\n");
  append(L"  }\n");
                                                            #line 1511 "PrintCSharp.cpp.template"
                                                                }
                                                              }
                                                            }

// End
