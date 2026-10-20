// This file was generated on Tue Oct 20, 2026 19:55 (UTC+02) by REx v6.3-SNAPSHOT which is Copyright (c) 1979-2026 by Gunther Rademacher <grd@gmx.net>
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
                                                              if (! hasProlog)
                                                              {
                                                            #line 43 "PrintCSharp.cpp"
  append(L"\n");
  append(L"using System;\n");
  append(L"using System.IO;\n");
  append(L"using System.Text;\n");
  append(L"using System.Collections.Generic;\n");
                                                            #line 42 "PrintCSharp.cpp.template"
                                                                if (! packageName.empty())
                                                                {
                                                            #line 52 "PrintCSharp.cpp"
  append(L"\n");
  append(L"namespace ");
                                                            #line 45 "PrintCSharp.cpp.template"
                                                                  print(packageName.c_str());
                                                            #line 57 "PrintCSharp.cpp"
  append(L"\n");
  append(L"{");
                                                            #line 47 "PrintCSharp.cpp.template"
                                                                  increaseIndent();
                                                                }
                                                            #line 63 "PrintCSharp.cpp"
  append(L"\n");
  append(L"public class ");
                                                            #line 50 "PrintCSharp.cpp.template"
                                                                print(className.c_str());
                                                                if (! interfaceName.empty())
                                                                {
                                                            #line 70 "PrintCSharp.cpp"
  append(L" : ");
                                                            #line 53 "PrintCSharp.cpp.template"
                                                                  print(interfaceName.c_str());
                                                                }
                                                            #line 75 "PrintCSharp.cpp"
  append(L"\n");
  append(L"{");
                                                            #line 56 "PrintCSharp.cpp.template"
                                                              }
                                                              if (main)
                                                              {
                                                            #line 82 "PrintCSharp.cpp"
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
                                                            #line 95 "PrintCSharp.cpp"
  append(L" [-i]");
                                                            #line 69 "PrintCSharp.cpp.template"
                                                                }
                                                            #line 99 "PrintCSharp.cpp"
  append(L" INPUT...\");\n");
  append(L"      Console.Error.WriteLine();\n");
  append(L"      Console.Error.WriteLine(\"  parse INPUT, which is either a filename or literal text enclosed in curly braces\");");
                                                            #line 73 "PrintCSharp.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 106 "PrintCSharp.cpp"
  append(L"\n");
  append(L"      Console.Error.WriteLine();\n");
  append(L"      Console.Error.WriteLine(\"  Option:\");\n");
  append(L"      Console.Error.WriteLine(\"    -i     indented parse tree\");");
                                                            #line 79 "PrintCSharp.cpp.template"
                                                                }
                                                            #line 113 "PrintCSharp.cpp"
  append(L"\n");
  append(L"    }\n");
  append(L"    else\n");
  append(L"    {");
                                                            #line 83 "PrintCSharp.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 121 "PrintCSharp.cpp"
  append(L"\n");
  append(L"      bool indent = false;");
                                                            #line 87 "PrintCSharp.cpp.template"
                                                                }
                                                            #line 126 "PrintCSharp.cpp"
  append(L"\n");
  append(L"      for (int i = 0; i < args.Length; ++i)\n");
  append(L"      {\n");
  append(L"        string arg = args[i];");
                                                            #line 91 "PrintCSharp.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 134 "PrintCSharp.cpp"
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
                                                            #line 146 "PrintCSharp.cpp"
  append(L"\n");
  append(L"        ParseTreeBuilder b = new ParseTreeBuilder();");
                                                            #line 103 "PrintCSharp.cpp.template"
                                                                  }
                                                                }
                                                            #line 152 "PrintCSharp.cpp"
  append(L"\n");
  append(L"        String input = read(arg);\n");
  append(L"        ");
                                                            #line 107 "PrintCSharp.cpp.template"
                                                                print(className.c_str());
                                                            #line 158 "PrintCSharp.cpp"
  append(L" parser = new ");
                                                            #line 108 "PrintCSharp.cpp.template"
                                                                print(className.c_str());
                                                            #line 162 "PrintCSharp.cpp"
  append(L"(input");
                                                            #line 109 "PrintCSharp.cpp.template"
                                                                if (noLexer)
                                                                {
                                                            #line 167 "PrintCSharp.cpp"
  append(L", new ");
                                                            #line 111 "PrintCSharp.cpp.template"
                                                                  print(className.c_str());
                                                            #line 171 "PrintCSharp.cpp"
  append(L"Lexer()");
                                                            #line 112 "PrintCSharp.cpp.template"
                                                                }
                                                                if (tree)
                                                                {
                                                            #line 177 "PrintCSharp.cpp"
  append(L", ");
                                                            #line 115 "PrintCSharp.cpp.template"
                                                                  if (isLrParser)
                                                                  {
                                                            #line 182 "PrintCSharp.cpp"
  append(L"b");
                                                            #line 117 "PrintCSharp.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 188 "PrintCSharp.cpp"
  append(L"s");
                                                            #line 120 "PrintCSharp.cpp.template"
                                                                  }
                                                                }
                                                            #line 193 "PrintCSharp.cpp"
  append(L");\n");
  append(L"        try\n");
  append(L"        {");
                                                            #line 124 "PrintCSharp.cpp.template"
                                                                if (trace)
                                                                {
                                                            #line 200 "PrintCSharp.cpp"
  append(L"\n");
  append(L"          parser.writeTrace(\"<?xml version=\\\"1.0\\\" encoding=\\\"UTF-8\\\"?\" + \">\\n<trace>\\n\");");
                                                            #line 128 "PrintCSharp.cpp.template"
                                                                }
                                                            #line 205 "PrintCSharp.cpp"
  append(L"\n");
  append(L"          parser.");
                                                            #line 130 "PrintCSharp.cpp.template"
                                                                print(methodPrefixParse);
                                                                print(Format::acceptableName<WString>(grammar->startSymbol()->name).c_str());
                                                            #line 211 "PrintCSharp.cpp"
  append(L"();");
                                                            #line 132 "PrintCSharp.cpp.template"
                                                                if (trace)
                                                                {
                                                            #line 216 "PrintCSharp.cpp"
  append(L"\n");
  append(L"          parser.writeTrace(\"</trace>\\n\");");
                                                            #line 135 "PrintCSharp.cpp.template"
                                                                }
                                                                if (tree && isLrParser)
                                                                {
                                                            #line 223 "PrintCSharp.cpp"
  append(L"\n");
  append(L"          b.serialize(s);");
                                                            #line 139 "PrintCSharp.cpp.template"
                                                                }
                                                            #line 228 "PrintCSharp.cpp"
  append(L"\n");
  append(L"        }\n");
  append(L"        catch (ParseException pe)\n");
  append(L"        {");
                                                            #line 143 "PrintCSharp.cpp.template"
                                                                if (rejectsAmbiguity() && tree)
                                                                {
                                                            #line 236 "PrintCSharp.cpp"
  append(L"\n");
  append(L"          if (pe.isAmbiguousInput())\n");
  append(L"          {\n");
  append(L"            pe.serialize(s);\n");
  append(L"            w.Write(\"\\n\");\n");
  append(L"            w.Flush();\n");
  append(L"          }");
                                                            #line 151 "PrintCSharp.cpp.template"
                                                                }
                                                            #line 246 "PrintCSharp.cpp"
  append(L"\n");
  append(L"          Console.Error.WriteLine(\"ParseException while processing \" + arg + \":\\n\" + parser.getErrorMessage(pe));\n");
  append(L"          return 1;\n");
  append(L"        }");
                                                            #line 155 "PrintCSharp.cpp.template"
                                                                if (tree || trace)
                                                                {
                                                            #line 254 "PrintCSharp.cpp"
  append(L"\n");
  append(L"        finally\n");
  append(L"        {");
                                                            #line 159 "PrintCSharp.cpp.template"
                                                                }
                                                                if (trace)
                                                                {
                                                            #line 262 "PrintCSharp.cpp"
  append(L"\n");
  append(L"          parser.flushTrace();");
                                                            #line 163 "PrintCSharp.cpp.template"
                                                                }
                                                                if (tree)
                                                                {
                                                            #line 269 "PrintCSharp.cpp"
  append(L"\n");
  append(L"          w.Close();");
                                                            #line 167 "PrintCSharp.cpp.template"
                                                                }
                                                                if (tree || trace)
                                                                {
                                                            #line 276 "PrintCSharp.cpp"
  append(L"\n");
  append(L"        }");
                                                            #line 171 "PrintCSharp.cpp.template"
                                                                }
                                                            #line 281 "PrintCSharp.cpp"
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
                                                            #line 308 "PrintCSharp.cpp"
  append(L"\n");
  append(L"{\n");
  append(L"  initialize(s");
                                                            #line 199 "PrintCSharp.cpp.template"
                                                                if (noLexer)
                                                                {
                                                            #line 315 "PrintCSharp.cpp"
  append(L", lexer");
                                                            #line 201 "PrintCSharp.cpp.template"
                                                                }
                                                                if (tree)
                                                                {
                                                            #line 321 "PrintCSharp.cpp"
  append(L", t");
                                                            #line 204 "PrintCSharp.cpp.template"
                                                                }
                                                            #line 325 "PrintCSharp.cpp"
  append(L");\n");
  append(L"}\n");
                                                            #line 207 "PrintCSharp.cpp.template"
                                                                decreaseIndent();
                                                              }
                                                              /*
                                                              increaseIndent()
                                                              openMethod(L"String ", L"", L"getInput", L"");
                                                            #line 334 "PrintCSharp.cpp"
  append(L"\n");
  append(L"{\n");
  append(L"  return ");
                                                            #line 214 "PrintCSharp.cpp.template"
                                                              if (useGlr)
                                                              {
                                                            #line 341 "PrintCSharp.cpp"
  append(L"parser.");
                                                            #line 216 "PrintCSharp.cpp.template"
                                                              }
                                                            #line 345 "PrintCSharp.cpp"
  append(L"input;\n");
  append(L"}\n");
                                                            #line 219 "PrintCSharp.cpp.template"
                                                              openMethod(L"int ", L"", L"getTokenOffset", L"");
                                                            #line 350 "PrintCSharp.cpp"
  append(L"\n");
  append(L"{\n");
  append(L"  return b0;\n");
  append(L"}\n");
                                                            #line 224 "PrintCSharp.cpp.template"
                                                              openMethod(L"int ", L"", L"getTokenEnd", L"");
                                                            #line 357 "PrintCSharp.cpp"
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
                                                            #line 369 "PrintCSharp.cpp"
  append(L"\n");
  append(L"private class StackNode\n");
  append(L"{\n");
  append(L"  public int state;");
                                                            #line 238 "PrintCSharp.cpp.template"
                                                              if (grammar->states->hasLookback)
                                                              {
                                                            #line 377 "PrintCSharp.cpp"
  append(L"\n");
  append(L"  public int code;");
                                                            #line 241 "PrintCSharp.cpp.template"
                                                              }
                                                            #line 382 "PrintCSharp.cpp"
  append(L"\n");
  append(L"  public int pos;\n");
  append(L"  public StackNode link;\n");
  append(L"\n");
  append(L"  public StackNode(int state, ");
                                                            #line 246 "PrintCSharp.cpp.template"
                                                              if (grammar->states->hasLookback)
                                                              {
                                                            #line 391 "PrintCSharp.cpp"
  append(L"int code, ");
                                                            #line 248 "PrintCSharp.cpp.template"
                                                              }
                                                            #line 395 "PrintCSharp.cpp"
  append(L"int pos, StackNode link)\n");
  append(L"  {\n");
  append(L"    this.state = state;");
                                                            #line 251 "PrintCSharp.cpp.template"
                                                              if (grammar->states->hasLookback)
                                                              {
                                                            #line 402 "PrintCSharp.cpp"
  append(L"\n");
  append(L"    this.code = code;");
                                                            #line 254 "PrintCSharp.cpp.template"
                                                              }
                                                            #line 407 "PrintCSharp.cpp"
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
                                                            #line 267 "PrintCSharp.cpp.template"
                                                              if (grammar->states->hasLookback)
                                                              {
                                                            #line 424 "PrintCSharp.cpp"
  append(L"\n");
  append(L"      if (lhs.code != rhs.code) return false;");
                                                            #line 270 "PrintCSharp.cpp.template"
                                                              }
                                                            #line 429 "PrintCSharp.cpp"
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
                                                            #line 283 "PrintCSharp.cpp.template"
                                                              increaseIndent();
                                                              beginPublic();
                                                            }

                                                            void PrintCSharp::closeStackNode()
                                                            {
                                                              beginNonpublic();
                                                              decreaseIndent();
                                                            #line 451 "PrintCSharp.cpp"
  append(L"\n");
  append(L"}\n");
                                                            #line 293 "PrintCSharp.cpp.template"
                                                              if (hasCustomCode)
                                                              {
                                                            #line 457 "PrintCSharp.cpp"
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
                                                            #line 311 "PrintCSharp.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                            #line 478 "PrintCSharp.cpp"
  append(L"\n");
  append(L"private abstract class DeferredEvent\n");
  append(L"{\n");
  append(L"  public DeferredEvent link;\n");
  append(L"  public String name;\n");
  append(L"  public int begin;\n");
  append(L"  public int end;");
                                                            #line 320 "PrintCSharp.cpp.template"
                                                                if (shiftAmbiguity)
                                                                {
                                                            #line 489 "PrintCSharp.cpp"
  append(L"\n");
  append(L"  public int depth;");
                                                            #line 323 "PrintCSharp.cpp.template"
                                                                }
                                                            #line 494 "PrintCSharp.cpp"
  append(L"\n");
  append(L"\n");
  append(L"  public DeferredEvent(DeferredEvent link, String name, int begin, int end)\n");
  append(L"  {\n");
  append(L"    this.link = link;\n");
  append(L"    this.name = name;\n");
  append(L"    this.begin = begin;\n");
  append(L"    this.end = end;");
                                                            #line 331 "PrintCSharp.cpp.template"
                                                                if (shiftAmbiguity)
                                                                {
                                                            #line 506 "PrintCSharp.cpp"
  append(L"\n");
  append(L"    this.depth = link == null ? 1 : link.depth + 1;");
                                                            #line 334 "PrintCSharp.cpp.template"
                                                                }
                                                            #line 511 "PrintCSharp.cpp"
  append(L"\n");
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
  append(L"      ");
                                                            #line 354 "PrintCSharp.cpp.template"
                                                                if (shiftAmbiguity)
                                                                {
                                                            #line 535 "PrintCSharp.cpp"
  append(L"if (eventHandler != null)\n");
  append(L"        ");
                                                            #line 357 "PrintCSharp.cpp.template"
                                                                }
                                                            #line 540 "PrintCSharp.cpp"
  append(L"current.execute(eventHandler);\n");
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
                                                            #line 416 "PrintCSharp.cpp.template"
                                                                if (resolvesAmbiguity)
                                                                {
                                                            #line 602 "PrintCSharp.cpp"
  append(L"\n");
  append(L"\n");
  append(L"private class AmbiguityEvent : DeferredEvent\n");
  append(L"{\n");
  append(L"  public AmbiguityEvent(DeferredEvent link, int begin, int end)\n");
  append(L"  : base(link, null, begin, end)\n");
  append(L"  {\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  public override void execute(BottomUpEventHandler eventHandler)\n");
  append(L"  {\n");
  append(L"    eventHandler.ambiguity(begin, end);\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  public override String ToString()\n");
  append(L"  {\n");
  append(L"    return \"ambiguity(\" + begin + \", \" + end + \")\";\n");
  append(L"  }\n");
  append(L"}\n");
                                                            #line 437 "PrintCSharp.cpp.template"
                                                                }
                                                              }
                                                            #line 625 "PrintCSharp.cpp"
  append(L"\n");
  append(L"private static int PARSING = 0;\n");
  append(L"private static int ACCEPTED = 1;\n");
  append(L"private static int ERROR = 2;\n");
  append(L"\n");
  append(L"private ParsingThread parse(int target, int initialState, ");
                                                            #line 444 "PrintCSharp.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 635 "PrintCSharp.cpp"
  append(L"BottomUpEventHandler eventHandler, ");
                                                            #line 447 "PrintCSharp.cpp.template"
                                                              }
                                                            #line 639 "PrintCSharp.cpp"
  append(L"ParsingThread thread)\n");
  append(L"{\n");
  append(L"  Heap<ParsingThread> threads = thread.open(initialState");
                                                            #line 450 "PrintCSharp.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 646 "PrintCSharp.cpp"
  append(L", eventHandler");
                                                            #line 452 "PrintCSharp.cpp.template"
                                                              }
                                                            #line 650 "PrintCSharp.cpp"
  append(L", target);\n");
  append(L"  for (;;)\n");
  append(L"  {\n");
  append(L"    thread = threads.poll();\n");
  append(L"    if (thread.accepted)\n");
  append(L"    {");
                                                            #line 458 "PrintCSharp.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 660 "PrintCSharp.cpp"
  append(L"\n");
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
                                                            #line 473 "PrintCSharp.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 678 "PrintCSharp.cpp"
  append(L", thread.deferredEvent, other.deferredEvent");
                                                            #line 476 "PrintCSharp.cpp.template"
                                                                }
                                                            #line 682 "PrintCSharp.cpp"
  append(L");\n");
  append(L"      }");
                                                            #line 478 "PrintCSharp.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 689 "PrintCSharp.cpp"
  append(L"\n");
  append(L"      while (! threads.isEmpty())\n");
  append(L"      {\n");
  append(L"        ParsingThread other = threads.poll();\n");
  append(L"        thread = thread.e0 < other.e0 ? other : resolve(thread, other);\n");
  append(L"      }");
                                                            #line 486 "PrintCSharp.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                            #line 700 "PrintCSharp.cpp"
  append(L"\n");
  append(L"      if (thread.deferredEvent != null)\n");
  append(L"      {\n");
  append(L"        thread.deferredEvent.release(eventHandler);\n");
  append(L"        thread.deferredEvent = null;\n");
  append(L"      }");
                                                            #line 494 "PrintCSharp.cpp.template"
                                                              }
                                                              if (hasCustomCode)
                                                              {
                                                            #line 711 "PrintCSharp.cpp"
  append(L"\n");
  append(L"      thread.executeDeferredCode();");
                                                            #line 498 "PrintCSharp.cpp.template"
                                                              }
                                                            #line 716 "PrintCSharp.cpp"
  append(L"\n");
  append(L"      return thread;\n");
  append(L"    }\n");
  append(L"\n");
                                                            #line 503 "PrintCSharp.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 724 "PrintCSharp.cpp"
  append(L"    if (! threads.isEmpty())\n");
  append(L"    {\n");
  append(L"      if (threads.peek().Equals(thread))\n");
  append(L"      {\n");
  append(L"        rejectAmbiguity(thread.stack.pos, thread.e0");
                                                            #line 509 "PrintCSharp.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 733 "PrintCSharp.cpp"
  append(L", thread.deferredEvent, threads.peek().deferredEvent");
                                                            #line 512 "PrintCSharp.cpp.template"
                                                                }
                                                            #line 737 "PrintCSharp.cpp"
  append(L");\n");
  append(L"      }\n");
  append(L"    }");
                                                            #line 515 "PrintCSharp.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 745 "PrintCSharp.cpp"
  append(L"    while (! threads.isEmpty() && threads.peek().Equals(thread))\n");
  append(L"    {\n");
  append(L"      thread = resolve(thread, threads.poll());\n");
  append(L"    }");
                                                            #line 521 "PrintCSharp.cpp.template"
                                                              }
                                                              if (tree || hasCustomCode)
                                                              {
                                                                if (rejectsAmbiguity())
                                                                {
                                                            #line 756 "PrintCSharp.cpp"
  append(L"\n");
  append(L"    else\n");
  append(L"    {");
                                                            #line 528 "PrintCSharp.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 764 "PrintCSharp.cpp"
  append(L"\n");
  append(L"    if (threads.isEmpty())\n");
  append(L"    {");
                                                            #line 533 "PrintCSharp.cpp.template"
                                                                }
                                                                if (tree)
                                                                {
                                                            #line 772 "PrintCSharp.cpp"
  append(L"\n");
  append(L"      if (thread.deferredEvent != null)\n");
  append(L"      {\n");
  append(L"        thread.deferredEvent.release(eventHandler);\n");
  append(L"        thread.deferredEvent = null;\n");
  append(L"      }");
                                                            #line 541 "PrintCSharp.cpp.template"
                                                                }
                                                                if (hasCustomCode)
                                                                {
                                                            #line 783 "PrintCSharp.cpp"
  append(L"\n");
  append(L"      thread.executeDeferredCode();");
                                                            #line 545 "PrintCSharp.cpp.template"
                                                                }
                                                            #line 788 "PrintCSharp.cpp"
  append(L"\n");
  append(L"    }");
                                                            #line 547 "PrintCSharp.cpp.template"
                                                              }
                                                            #line 793 "PrintCSharp.cpp"
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
                                                            #line 572 "PrintCSharp.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 821 "PrintCSharp.cpp"
  append(L"\n");
  append(L"private void rejectAmbiguity(int begin, int end");
                                                            #line 575 "PrintCSharp.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 827 "PrintCSharp.cpp"
  append(L", DeferredEvent first, DeferredEvent second");
                                                            #line 578 "PrintCSharp.cpp.template"
                                                                }
                                                            #line 831 "PrintCSharp.cpp"
  append(L")\n");
  append(L"{");
                                                            #line 580 "PrintCSharp.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 837 "PrintCSharp.cpp"
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
                                                            #line 592 "PrintCSharp.cpp.template"
                                                                }
                                                            #line 850 "PrintCSharp.cpp"
  append(L"\n");
  append(L"  throw new ParseException(begin, end");
                                                            #line 594 "PrintCSharp.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 856 "PrintCSharp.cpp"
  append(L", treeBuilder");
                                                            #line 596 "PrintCSharp.cpp.template"
                                                                }
                                                            #line 860 "PrintCSharp.cpp"
  append(L");\n");
  append(L"}");
                                                            #line 598 "PrintCSharp.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 867 "PrintCSharp.cpp"
  append(L"\n");
  append(L"private ParsingThread resolve(ParsingThread thread, ParsingThread other)\n");
  append(L"{");
                                                            #line 603 "PrintCSharp.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 874 "PrintCSharp.cpp"
  append(L"\n");
  append(L"  StackNode a = thread.stack;\n");
  append(L"  StackNode b = other.stack;\n");
  append(L"  int begin = a.pos;\n");
  append(L"  while (a != b && a != null && b != null)\n");
  append(L"  {\n");
  append(L"    begin = a.pos;\n");
  append(L"    a = a.link;\n");
  append(L"    b = b.link;\n");
  append(L"  }");
                                                            #line 614 "PrintCSharp.cpp.template"
                                                                }
                                                            #line 887 "PrintCSharp.cpp"
  append(L"\n");
                                                            #line 616 "PrintCSharp.cpp.template"
                                                                if (shiftAmbiguity)
                                                                {
                                                            #line 892 "PrintCSharp.cpp"
  append(L"\n");
  append(L"  DeferredEvent ea = thread.deferredEvent;\n");
  append(L"  DeferredEvent eb = other.deferredEvent;\n");
  append(L"  DeferredEvent ua = null;\n");
  append(L"  DeferredEvent ub = null;\n");
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
  append(L"  if ((ua is TerminalEvent) != (ub is TerminalEvent))\n");
  append(L"  {\n");
  append(L"    if (ub is TerminalEvent)\n");
  append(L"      thread = other;\n");
  append(L"  }\n");
  append(L"  else if (other.eventCount < thread.eventCount)\n");
  append(L"    thread = other;");
                                                            #line 642 "PrintCSharp.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 922 "PrintCSharp.cpp"
  append(L"\n");
  append(L"  if (other.eventCount < thread.eventCount)\n");
  append(L"    thread = other;");
                                                            #line 647 "PrintCSharp.cpp.template"
                                                                }
                                                                if (tree)
                                                                {
                                                            #line 930 "PrintCSharp.cpp"
  append(L"\n");
  append(L"  thread.addAmbiguity(begin, thread.e0);");
                                                            #line 651 "PrintCSharp.cpp.template"
                                                                }
                                                            #line 935 "PrintCSharp.cpp"
  append(L"\n");
  append(L"  return thread;\n");
  append(L"}");
                                                            #line 654 "PrintCSharp.cpp.template"
                                                              }
                                                            #line 941 "PrintCSharp.cpp"
  append(L"\n");
  append(L"private ParsingThread thread = null;");
                                                            #line 656 "PrintCSharp.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 947 "PrintCSharp.cpp"
  append(L"\n");
  append(L"private BottomUpEventHandler eventHandler;");
                                                            #line 659 "PrintCSharp.cpp.template"
                                                              }
                                                            #line 952 "PrintCSharp.cpp"
  append(L"\n");
  append(L"private String input = null;\n");
  append(L"private int size = 0;");
                                                            #line 662 "PrintCSharp.cpp.template"
                                                              if (trace)
                                                              {
                                                            #line 959 "PrintCSharp.cpp"
  append(L"\n");
  append(L"private TextWriter err = Console.Error;");
                                                            #line 665 "PrintCSharp.cpp.template"
                                                              }
                                                            #line 964 "PrintCSharp.cpp"
  append(L"\n");
  append(L"private int maxId = 0;\n");
                                                            #line 668 "PrintCSharp.cpp.template"
                                                            }

                                                            void PrintCSharp::openThread()
                                                            {
                                                            #line 972 "PrintCSharp.cpp"
  append(L"\n");
  append(L"private class ParsingThread : IComparable<ParsingThread>\n");
  append(L"{\n");
  append(L"  public ");
                                                            #line 675 "PrintCSharp.cpp.template"
                                                              print(className.c_str());
                                                            #line 979 "PrintCSharp.cpp"
  append(L" parser;\n");
  append(L"  public Heap<ParsingThread> threads;\n");
  append(L"  public bool accepted;\n");
  append(L"  public StackNode stack;\n");
  append(L"  public int state;\n");
  append(L"  public int action;\n");
  append(L"  public int target;");
                                                            #line 682 "PrintCSharp.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 990 "PrintCSharp.cpp"
  append(L"\n");
  append(L"  public DeferredEvent deferredEvent;");
                                                            #line 685 "PrintCSharp.cpp.template"
                                                              }
                                                              if (hasCustomCode)
                                                              {
                                                            #line 997 "PrintCSharp.cpp"
  append(L"\n");
  append(L"  public DeferredCode deferredCode;");
                                                            #line 689 "PrintCSharp.cpp.template"
                                                              }
                                                            #line 1002 "PrintCSharp.cpp"
  append(L"\n");
  append(L"  public int id;");
                                                            #line 691 "PrintCSharp.cpp.template"
                                                              if (resolvesAmbiguity)
                                                              {
                                                            #line 1008 "PrintCSharp.cpp"
  append(L"\n");
  append(L"  public int eventCount;");
                                                            #line 694 "PrintCSharp.cpp.template"
                                                              }
                                                            #line 1013 "PrintCSharp.cpp"
  append(L"\n");
  append(L"\n");
  append(L"  public Heap<ParsingThread> open(int initialState");
                                                            #line 697 "PrintCSharp.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 1020 "PrintCSharp.cpp"
  append(L", BottomUpEventHandler eh");
                                                            #line 699 "PrintCSharp.cpp.template"
                                                              }
                                                            #line 1024 "PrintCSharp.cpp"
  append(L", int t)\n");
  append(L"  {\n");
  append(L"    accepted = false;\n");
  append(L"    target = t;");
                                                            #line 703 "PrintCSharp.cpp.template"
                                                              if (resolvesAmbiguity)
                                                              {
                                                            #line 1032 "PrintCSharp.cpp"
  append(L"\n");
  append(L"    eventCount = 0;");
                                                            #line 706 "PrintCSharp.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                            #line 1039 "PrintCSharp.cpp"
  append(L"\n");
  append(L"    eventHandler = eh;\n");
  append(L"    if (eventHandler != null)\n");
  append(L"    {\n");
  append(L"      eventHandler.reset(parser.input);\n");
  append(L"    }\n");
  append(L"    deferredEvent = null;");
                                                            #line 715 "PrintCSharp.cpp.template"
                                                              }
                                                              if (hasCustomCode && useGlr)
                                                              {
                                                            #line 1051 "PrintCSharp.cpp"
  append(L"\n");
  append(L"    deferredCode = null;");
                                                            #line 719 "PrintCSharp.cpp.template"
                                                              }
                                                            #line 1056 "PrintCSharp.cpp"
  append(L"\n");
  append(L"    stack = new StackNode(-1, ");
                                                            #line 721 "PrintCSharp.cpp.template"
                                                              if (grammar->states->hasLookback)
                                                              {
                                                            #line 1062 "PrintCSharp.cpp"
  append(L"0, ");
                                                            #line 723 "PrintCSharp.cpp.template"
                                                              }
                                                            #line 1066 "PrintCSharp.cpp"
  append(L"e0, null);\n");
  append(L"    state = initialState;\n");
  append(L"    action = predict(initialState);");
                                                            #line 726 "PrintCSharp.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 1073 "PrintCSharp.cpp"
  append(L"\n");
  append(L"    bw = e0;\n");
  append(L"    bs = e0;\n");
  append(L"    es = e0;");
                                                            #line 731 "PrintCSharp.cpp.template"
                                                              }
                                                            #line 1080 "PrintCSharp.cpp"
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
  append(L"    parser = other.parser;");
                                                            #line 743 "PrintCSharp.cpp.template"
                                                              if (resolvesAmbiguity)
                                                              {
                                                            #line 1096 "PrintCSharp.cpp"
  append(L"\n");
  append(L"    eventCount = other.eventCount;");
                                                            #line 746 "PrintCSharp.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                            #line 1103 "PrintCSharp.cpp"
  append(L"\n");
  append(L"    bs = other.bs;\n");
  append(L"    bw = other.bw;\n");
  append(L"    es = other.es;\n");
  append(L"    eventHandler = other.eventHandler;\n");
  append(L"    deferredEvent = other.deferredEvent;");
                                                            #line 754 "PrintCSharp.cpp.template"
                                                              }
                                                              if (hasCustomCode)
                                                              {
                                                            #line 1114 "PrintCSharp.cpp"
  append(L"\n");
  append(L"    deferredCode = other.deferredCode;");
                                                            #line 758 "PrintCSharp.cpp.template"
                                                              }
                                                            #line 1119 "PrintCSharp.cpp"
  append(L"\n");
  append(L"    id = ++parser.maxId;\n");
  append(L"    threads = other.threads;\n");
  append(L"    state = other.state;\n");
  append(L"    stack = other.stack;\n");
  append(L"    b0 = other.b0;\n");
  append(L"    e0 = other.e0;");
                                                            #line 765 "PrintCSharp.cpp.template"
                                                              for (size_t i = 1; i <= grammar->k; ++i)
                                                              {
                                                                const wchar_t *iString = format.toString<wchar_t>(i);
                                                            #line 1131 "PrintCSharp.cpp"
  append(L"\n");
  append(L"    l");
                                                            #line 769 "PrintCSharp.cpp.template"
                                                                print(iString);
                                                            #line 1136 "PrintCSharp.cpp"
  append(L" = other.l");
                                                            #line 770 "PrintCSharp.cpp.template"
                                                                print(iString);
                                                            #line 1140 "PrintCSharp.cpp"
  append(L";\n");
  append(L"    b");
                                                            #line 772 "PrintCSharp.cpp.template"
                                                                print(iString);
                                                            #line 1145 "PrintCSharp.cpp"
  append(L" = other.b");
                                                            #line 773 "PrintCSharp.cpp.template"
                                                                print(iString);
                                                            #line 1149 "PrintCSharp.cpp"
  append(L";\n");
  append(L"    e");
                                                            #line 775 "PrintCSharp.cpp.template"
                                                                print(iString);
                                                            #line 1154 "PrintCSharp.cpp"
  append(L" = other.e");
                                                            #line 776 "PrintCSharp.cpp.template"
                                                                print(iString);
                                                            #line 1158 "PrintCSharp.cpp"
  append(L";");
                                                            #line 777 "PrintCSharp.cpp.template"
                                                              }
                                                            #line 1162 "PrintCSharp.cpp"
  append(L"\n");
  append(L"    end = other.end;\n");
  append(L"    return this;\n");
  append(L"  }\n");
  append(L"\n");
                                                            #line 783 "PrintCSharp.cpp.template"
                                                              if (resolvesAmbiguity && tree)
                                                              {
                                                            #line 1171 "PrintCSharp.cpp"
  append(L"\n");
  append(L"  public void addAmbiguity(int begin, int end)\n");
  append(L"  {\n");
  append(L"    if (eventHandler != null)\n");
  append(L"      deferredEvent = new AmbiguityEvent(deferredEvent, begin, end);\n");
  append(L"  }\n");
  append(L"\n");
                                                            #line 792 "PrintCSharp.cpp.template"
                                                              }
                                                            #line 1181 "PrintCSharp.cpp"
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
                                                            #line 820 "PrintCSharp.cpp.template"
                                                              increaseIndent();
                                                              beginPublic();
                                                            }

                                                            void PrintCSharp::printFlush(int i, bool withinThread)
                                                            {
                                                              if (trace)
                                                              {
                                                                increaseIndent(i);
                                                            #line 1220 "PrintCSharp.cpp"
  append(L"\n");
                                                            #line 830 "PrintCSharp.cpp.template"
                                                                if (useGlr && withinThread)
                                                                {
                                                            #line 1225 "PrintCSharp.cpp"
  append(L"parser.");
                                                            #line 832 "PrintCSharp.cpp.template"
                                                                }
                                                            #line 1229 "PrintCSharp.cpp"
  append(L"flushTrace();");
                                                            #line 833 "PrintCSharp.cpp.template"
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
                                                            #line 1243 "PrintCSharp.cpp"
  append(L"\n");
                                                            #line 845 "PrintCSharp.cpp.template"
                                                              print(visibility);
                                                            #line 1247 "PrintCSharp.cpp"
  append(L" ");
                                                            #line 846 "PrintCSharp.cpp.template"
                                                              print(prefix);
                                                              print(type);
                                                              print(name);
                                                            #line 1253 "PrintCSharp.cpp"
  append(L"(");
                                                            #line 849 "PrintCSharp.cpp.template"
                                                              print(args);
                                                            #line 1257 "PrintCSharp.cpp"
  append(L")");
                                                            #line 850 "PrintCSharp.cpp.template"
                                                            }

                                                            void PrintCSharp::privateVars()
                                                            {
                                                              if (trace)
                                                              {
                                                            #line 1266 "PrintCSharp.cpp"
  append(L"\n");
  append(L"  private String lookaheadString()\n");
  append(L"  {\n");
  append(L"    String result = \"\";\n");
  append(L"    if (l1 > 0)\n");
  append(L"    {\n");
  append(L"      result += TOKEN[l1];");
                                                            #line 862 "PrintCSharp.cpp.template"
                                                                for (size_t i = 2; i <= grammar->k; ++i)
                                                                {
                                                            #line 1277 "PrintCSharp.cpp"
  append(L"\n");
  append(L"      if (l");
                                                            #line 865 "PrintCSharp.cpp.template"
                                                                  print(format.toString<wchar_t>(i));
                                                            #line 1282 "PrintCSharp.cpp"
  append(L" > 0)\n");
  append(L"      {\n");
  append(L"        result += \" \" + TOKEN[l");
                                                            #line 868 "PrintCSharp.cpp.template"
                                                                  print(format.toString<wchar_t>(i));
                                                            #line 1288 "PrintCSharp.cpp"
  append(L"];");
                                                            #line 869 "PrintCSharp.cpp.template"
                                                                  increaseIndent();
                                                                }
                                                                for (size_t i = 2; i <= grammar->k; ++i)
                                                                {
                                                                  decreaseIndent();
                                                            #line 1296 "PrintCSharp.cpp"
  append(L"\n");
  append(L"      }");
                                                            #line 875 "PrintCSharp.cpp.template"
                                                                }
                                                            #line 1301 "PrintCSharp.cpp"
  append(L"\n");
  append(L"    }\n");
  append(L"    return result;\n");
  append(L"  }\n");
                                                            #line 880 "PrintCSharp.cpp.template"
                                                              }
                                                            #line 1308 "PrintCSharp.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 882 "PrintCSharp.cpp.template"
                                                              print(useGlr ? L"public" : L"private");
                                                            #line 1313 "PrintCSharp.cpp"
  append(L" int ");
                                                            #line 883 "PrintCSharp.cpp.template"
                                                              if (! isLrParser && (grammar->k > 1 ||
                                                                                   memoization ||
                                                                                   ! grammar->decisionPoints.empty()))
                                                              {
                                                            #line 1320 "PrintCSharp.cpp"
  append(L"lk,");
                                                            #line 887 "PrintCSharp.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 1326 "PrintCSharp.cpp"
  append(L"   ");
                                                            #line 891 "PrintCSharp.cpp.template"
                                                              }
                                                            #line 1330 "PrintCSharp.cpp"
  append(L" b0, e0;");
                                                            #line 892 "PrintCSharp.cpp.template"
                                                              for (size_t k = 1; k <= grammar->k; ++k)
                                                              {
                                                                Format format;
                                                                wchar_t *asString = format.toString<wchar_t>(k);
                                                            #line 1337 "PrintCSharp.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 897 "PrintCSharp.cpp.template"
                                                                print(useGlr ? L"public" : L"private");
                                                            #line 1342 "PrintCSharp.cpp"
  append(L" int l");
                                                            #line 898 "PrintCSharp.cpp.template"
                                                                print(asString);
                                                            #line 1346 "PrintCSharp.cpp"
  append(L", b");
                                                            #line 899 "PrintCSharp.cpp.template"
                                                                print(asString);
                                                            #line 1350 "PrintCSharp.cpp"
  append(L", e");
                                                            #line 900 "PrintCSharp.cpp.template"
                                                                print(asString);
                                                            #line 1354 "PrintCSharp.cpp"
  append(L";");
                                                            #line 901 "PrintCSharp.cpp.template"
                                                              }
                                                              if (hasBacktracking)
                                                              {
                                                            #line 1360 "PrintCSharp.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 905 "PrintCSharp.cpp.template"
                                                                print(useGlr ? L"public" : L"private");
                                                            #line 1365 "PrintCSharp.cpp"
  append(L" int bx, ex, sx, lx, tx;");
                                                            #line 906 "PrintCSharp.cpp.template"
                                                              }
                                                              if (isLrParser && ! useGlr)
                                                              {
                                                            #line 1371 "PrintCSharp.cpp"
  append(L"\n");
  append(L"  private int[] iStack = new int[");
                                                            #line 910 "PrintCSharp.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 1377 "PrintCSharp.cpp"
  append(L"192");
                                                            #line 912 "PrintCSharp.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1383 "PrintCSharp.cpp"
  append(L"128");
                                                            #line 915 "PrintCSharp.cpp.template"
                                                                }
                                                            #line 1387 "PrintCSharp.cpp"
  append(L"];\n");
  append(L"  private int top = -1;");
                                                            #line 917 "PrintCSharp.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                                if (useGlr)
                                                                {
                                                            #line 1396 "PrintCSharp.cpp"
  append(L"\n");
  append(L"  public int bw, bs, es;");
                                                            #line 923 "PrintCSharp.cpp.template"
                                                                }
                                                                if (isLrParser)
                                                                {
                                                            #line 1403 "PrintCSharp.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 927 "PrintCSharp.cpp.template"
                                                                  print(useGlr ? L"public" : L"private");
                                                            #line 1408 "PrintCSharp.cpp"
  append(L" BottomUpEventHandler eventHandler = null;");
                                                            #line 928 "PrintCSharp.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1414 "PrintCSharp.cpp"
  append(L"\n");
  append(L"  private EventHandler eventHandler = null;");
                                                            #line 932 "PrintCSharp.cpp.template"
                                                                }
                                                              }
                                                              if (memoization)
                                                              {
                                                                int bits = Math::bits(grammar->conflictCount);
                                                            #line 1423 "PrintCSharp.cpp"
  append(L"\n");
  append(L"  private IDictionary<int, int> memo = new Dictionary<int, int>();");
                                                            #line 939 "PrintCSharp.cpp.template"
                                                                if (grammar->noThrow)
                                                                {
                                                            #line 1429 "PrintCSharp.cpp"
  append(L"\n");
  append(L"  private bool viable;");
                                                            #line 942 "PrintCSharp.cpp.template"
                                                                }
                                                            #line 1434 "PrintCSharp.cpp"
  append(L"\n");
  append(L"\n");
  append(L"  private void memoize(int i, int e, int v)\n");
  append(L"  {\n");
  append(L"    memo.Add((e << ");
                                                            #line 947 "PrintCSharp.cpp.template"
                                                                print(format.toString<wchar_t>(bits));
                                                            #line 1442 "PrintCSharp.cpp"
  append(L") + i, v);\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  private int memoized(int i, int e)\n");
  append(L"  {\n");
  append(L"    int value = 0;\n");
  append(L"    memo.TryGetValue((e << ");
                                                            #line 954 "PrintCSharp.cpp.template"
                                                                print(format.toString<wchar_t>(bits));
                                                            #line 1452 "PrintCSharp.cpp"
  append(L") + i, out value);\n");
  append(L"    return value;\n");
  append(L"  }");
                                                            #line 957 "PrintCSharp.cpp.template"
                                                              }
                                                            }

                                                            void PrintCSharp::printFileProcessor()
                                                            {
                                                            #line 1462 "PrintCSharp.cpp"
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
                                                            #line 972 "PrintCSharp.cpp.template"
                                                              print(className.c_str());
                                                            #line 1476 "PrintCSharp.cpp"
  append(L" parser;");
                                                            #line 973 "PrintCSharp.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 1481 "PrintCSharp.cpp"
  append(L"\n");
  append(L"    public ContentCounter contentCounter;");
                                                            #line 976 "PrintCSharp.cpp.template"
                                                                if (isLrParser)
                                                                {
                                                            #line 1487 "PrintCSharp.cpp"
  append(L"\n");
  append(L"    public ParseTreeBuilder parseTreeBuilder;");
                                                            #line 979 "PrintCSharp.cpp.template"
                                                                }
                                                              }
                                                            #line 1493 "PrintCSharp.cpp"
  append(L"\n");
  append(L"\n");
  append(L"    public ParseJob(String s, String i)\n");
  append(L"    {\n");
  append(L"      name = s;\n");
  append(L"      input = i;");
                                                            #line 986 "PrintCSharp.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 1503 "PrintCSharp.cpp"
  append(L"\n");
  append(L"      contentCounter = new ContentCounter();");
                                                            #line 989 "PrintCSharp.cpp.template"
                                                                if (isLrParser)
                                                                {
                                                            #line 1509 "PrintCSharp.cpp"
  append(L"\n");
  append(L"      parseTreeBuilder = new ParseTreeBuilder();");
                                                            #line 992 "PrintCSharp.cpp.template"
                                                                }
                                                              }
                                                            #line 1515 "PrintCSharp.cpp"
  append(L"\n");
  append(L"      parser = new ");
                                                            #line 995 "PrintCSharp.cpp.template"
                                                              print(className.c_str());
                                                            #line 1520 "PrintCSharp.cpp"
  append(L"(input");
                                                            #line 996 "PrintCSharp.cpp.template"
                                                              if (noLexer)
                                                              {
                                                            #line 1525 "PrintCSharp.cpp"
  append(L", new ");
                                                            #line 998 "PrintCSharp.cpp.template"
                                                                print(className.c_str());
                                                            #line 1529 "PrintCSharp.cpp"
  append(L"Lexer()");
                                                            #line 999 "PrintCSharp.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                                if (isLrParser)
                                                                {
                                                            #line 1537 "PrintCSharp.cpp"
  append(L", parseTreeBuilder");
                                                            #line 1004 "PrintCSharp.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1543 "PrintCSharp.cpp"
  append(L", contentCounter");
                                                            #line 1007 "PrintCSharp.cpp.template"
                                                                }
                                                              }
                                                            #line 1548 "PrintCSharp.cpp"
  append(L");\n");
  append(L"    }\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  public static int Main(String[] args)\n");
  append(L"  {\n");
  append(L"    if (args.Length == 0)\n");
  append(L"    {\n");
  append(L"      Console.Out.WriteLine(\"Usage: ");
                                                            #line 1017 "PrintCSharp.cpp.template"
                                                              print(className.c_str());
                                                            #line 1560 "PrintCSharp.cpp"
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
                                                            #line 1085 "PrintCSharp.cpp.template"
                                                              if (useGlr)
                                                              {
                                                            #line 1632 "PrintCSharp.cpp"
  append(L".thread");
                                                            #line 1087 "PrintCSharp.cpp.template"
                                                              }
                                                            #line 1636 "PrintCSharp.cpp"
  append(L".reset(0, 0, 0);\n");
  append(L"                job.parser.");
                                                            #line 1089 "PrintCSharp.cpp.template"
                                                              print(methodPrefixParse);
                                                              print(Format::acceptableName<WString>(grammar->startSymbol()->name).c_str());
                                                            #line 1642 "PrintCSharp.cpp"
  append(L"();\n");
  append(L"                if (! quiet) Console.Out.WriteLine();");
                                                            #line 1092 "PrintCSharp.cpp.template"
                                                              if (tree)
                                                              {
                                                                if (isLrParser)
                                                                {
                                                            #line 1650 "PrintCSharp.cpp"
  append(L"\n");
  append(L"                job.parseTreeBuilder.serialize(job.contentCounter);");
                                                            #line 1098 "PrintCSharp.cpp.template"
                                                                }
                                                            #line 1655 "PrintCSharp.cpp"
  append(L"\n");
  append(L"                if (job.contentCounter.getLength() != job.input.Length)\n");
  append(L"                {\n");
  append(L"                  Console.Error.WriteLine(\"content counter saw \" + job.contentCounter.getLength() + \", but input length is \" + job.input.Length);\n");
  append(L"                  Environment.Exit(1);\n");
  append(L"                }");
                                                            #line 1104 "PrintCSharp.cpp.template"
                                                              }
                                                            #line 1664 "PrintCSharp.cpp"
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
                                                            #line 1163 "PrintCSharp.cpp.template"
                                                            }

                                                            void PrintCSharp::printReadMethod()
                                                            {
                                                            #line 1728 "PrintCSharp.cpp"
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
                                                            #line 1179 "PrintCSharp.cpp.template"
                                                            }

                                                            void PrintCSharp::printInterface()
                                                            {
                                                              if (! packageName.empty())
                                                              {
                                                            #line 1748 "PrintCSharp.cpp"
  append(L"\n");
  append(L"package ");
                                                            #line 1186 "PrintCSharp.cpp.template"
                                                                print(packageName.c_str());
                                                            #line 1753 "PrintCSharp.cpp"
  append(L";\n");
                                                            #line 1188 "PrintCSharp.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                                if (main)
                                                                {
                                                            #line 1761 "PrintCSharp.cpp"
  append(L"\n");
  append(L"import java.io.IOException;\n");
  append(L"import java.io.Writer;\n");
                                                            #line 1196 "PrintCSharp.cpp.template"
                                                                }
                                                              }
                                                            #line 1768 "PrintCSharp.cpp"
  append(L"\n");
  append(L"public interface ");
                                                            #line 1199 "PrintCSharp.cpp.template"
                                                              print(className.c_str());
                                                            #line 1773 "PrintCSharp.cpp"
  append(L"\n");
  append(L"{\n");
  append(L"  void initialize(String input");
                                                            #line 1202 "PrintCSharp.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 1780 "PrintCSharp.cpp"
  append(L", EventHandler eh");
                                                            #line 1204 "PrintCSharp.cpp.template"
                                                              }
                                                            #line 1784 "PrintCSharp.cpp"
  append(L");\n");
  append(L"  void parse();\n");
  append(L"  void reset();\n");
  append(L"  String getErrorMessage(ParseException e);\n");
                                                            #line 1209 "PrintCSharp.cpp.template"
                                                              printParseException();
                                                            #line 1791 "PrintCSharp.cpp"
  append(L"}\n");
                                                            #line 1211 "PrintCSharp.cpp.template"
                                                            }

                                                            void PrintCSharp::printParseException()
                                                            {
                                                            #line 1798 "PrintCSharp.cpp"
  append(L"\n");
  append(L"  public class ParseException : Exception\n");
  append(L"  {\n");
  append(L"    private int begin, end, offending, expected, state;");
                                                            #line 1218 "PrintCSharp.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 1806 "PrintCSharp.cpp"
  append(L"\n");
  append(L"    private bool ambiguousInput;");
                                                            #line 1221 "PrintCSharp.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 1812 "PrintCSharp.cpp"
  append(L"\n");
  append(L"    private ParseTreeBuilder ambiguityDescriptor;");
                                                            #line 1224 "PrintCSharp.cpp.template"
                                                                }
                                                              }
                                                            #line 1818 "PrintCSharp.cpp"
  append(L"\n");
  append(L"\n");
  append(L"    public ParseException(int b, int e, int s, int o, int x)\n");
  append(L"    {\n");
  append(L"      begin = b;\n");
  append(L"      end = e;\n");
  append(L"      state = s;\n");
  append(L"      offending = o;\n");
  append(L"      expected = x;");
                                                            #line 1234 "PrintCSharp.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 1831 "PrintCSharp.cpp"
  append(L"\n");
  append(L"      ambiguousInput = false;");
                                                            #line 1237 "PrintCSharp.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 1837 "PrintCSharp.cpp"
  append(L"\n");
  append(L"      ambiguityDescriptor = null;");
                                                            #line 1240 "PrintCSharp.cpp.template"
                                                                }
                                                              }
                                                            #line 1843 "PrintCSharp.cpp"
  append(L"\n");
  append(L"    }\n");
                                                            #line 1244 "PrintCSharp.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 1849 "PrintCSharp.cpp"
  append(L"\n");
  append(L"    public ParseException(int b, int e");
                                                            #line 1247 "PrintCSharp.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 1855 "PrintCSharp.cpp"
  append(L", ParseTreeBuilder a");
                                                            #line 1249 "PrintCSharp.cpp.template"
                                                                }
                                                            #line 1859 "PrintCSharp.cpp"
  append(L") : this(b, e, -1, -1, -1)\n");
  append(L"    {\n");
  append(L"      ambiguousInput = true;");
                                                            #line 1252 "PrintCSharp.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 1866 "PrintCSharp.cpp"
  append(L"\n");
  append(L"      ambiguityDescriptor = a;");
                                                            #line 1255 "PrintCSharp.cpp.template"
                                                                }
                                                            #line 1871 "PrintCSharp.cpp"
  append(L"\n");
  append(L"    }\n");
                                                            #line 1258 "PrintCSharp.cpp.template"
                                                              }
                                                            #line 1876 "PrintCSharp.cpp"
  append(L"\n");
  append(L"    public String getMessage()\n");
  append(L"    {\n");
  append(L"      return ");
                                                            #line 1262 "PrintCSharp.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 1884 "PrintCSharp.cpp"
  append(L"ambiguousInput\n");
  append(L"           ? \"ambiguous input\"\n");
  append(L"           : ");
                                                            #line 1266 "PrintCSharp.cpp.template"
                                                              }
                                                            #line 1890 "PrintCSharp.cpp"
  append(L"offending < 0\n");
  append(L"           ? \"lexical analysis failed\"\n");
  append(L"           : \"syntax error\";\n");
  append(L"    }\n");
                                                            #line 1271 "PrintCSharp.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 1898 "PrintCSharp.cpp"
  append(L"\n");
  append(L"    public void serialize(EventHandler eventHandler)\n");
  append(L"    {");
                                                            #line 1275 "PrintCSharp.cpp.template"
                                                                if (rejectsAmbiguity())
                                                                {
                                                            #line 1905 "PrintCSharp.cpp"
  append(L"\n");
  append(L"      ambiguityDescriptor.serialize(eventHandler);");
                                                            #line 1278 "PrintCSharp.cpp.template"
                                                                }
                                                            #line 1910 "PrintCSharp.cpp"
  append(L"\n");
  append(L"    }\n");
                                                            #line 1281 "PrintCSharp.cpp.template"
                                                              }
                                                            #line 1915 "PrintCSharp.cpp"
  append(L"\n");
  append(L"    public int getBegin() {return begin;}\n");
  append(L"    public int getEnd() {return end;}\n");
  append(L"    public int getState() {return state;}\n");
  append(L"    public int getOffending() {return offending;}\n");
  append(L"    public int getExpected() {return expected;}\n");
  append(L"    public bool isAmbiguousInput() {return ");
                                                            #line 1288 "PrintCSharp.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 1926 "PrintCSharp.cpp"
  append(L"ambiguousInput");
                                                            #line 1290 "PrintCSharp.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 1932 "PrintCSharp.cpp"
  append(L"false");
                                                            #line 1293 "PrintCSharp.cpp.template"
                                                              }
                                                            #line 1936 "PrintCSharp.cpp"
  append(L";}\n");
  append(L"  }\n");
                                                            #line 1296 "PrintCSharp.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 1942 "PrintCSharp.cpp"
  append(L"\n");
  append(L"  public interface EventHandler\n");
  append(L"  {\n");
  append(L"    void reset(String s);\n");
  append(L"    void startNonterminal(String name");
                                                            #line 1302 "PrintCSharp.cpp.template"
                                                                if (! noPosition)
                                                                {
                                                            #line 1951 "PrintCSharp.cpp"
  append(L", int begin");
                                                            #line 1304 "PrintCSharp.cpp.template"
                                                                }
                                                            #line 1955 "PrintCSharp.cpp"
  append(L");\n");
  append(L"    void endNonterminal(String name");
                                                            #line 1306 "PrintCSharp.cpp.template"
                                                                if (! noPosition)
                                                                {
                                                            #line 1961 "PrintCSharp.cpp"
  append(L", int end");
                                                            #line 1308 "PrintCSharp.cpp.template"
                                                                }
                                                            #line 1965 "PrintCSharp.cpp"
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
                                                            #line 1416 "PrintCSharp.cpp.template"
                                                                if (isLrParser)
                                                                {
                                                            #line 2076 "PrintCSharp.cpp"
  append(L"\n");
  append(L"  public interface BottomUpEventHandler\n");
  append(L"  {\n");
  append(L"    void reset(String input);\n");
  append(L"    void nonterminal(String name, int begin, int end, int count);\n");
  append(L"    void terminal(String name, int begin, int end);");
                                                            #line 1423 "PrintCSharp.cpp.template"
                                                                  if (resolvesAmbiguity)
                                                                  {
                                                            #line 2086 "PrintCSharp.cpp"
  append(L"\n");
  append(L"    void ambiguity(int begin, int end);");
                                                            #line 1426 "PrintCSharp.cpp.template"
                                                                  }
                                                            #line 2091 "PrintCSharp.cpp"
  append(L"\n");
  append(L"  }\n");
                                                            #line 1429 "PrintCSharp.cpp.template"
                                                                }
                                                                if (main)
                                                                {
                                                            #line 2098 "PrintCSharp.cpp"
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
                                                            #line 1458 "PrintCSharp.cpp.template"
                                                                  if (! noPosition)
                                                                  {
                                                            #line 2129 "PrintCSharp.cpp"
  append(L", int begin");
                                                            #line 1460 "PrintCSharp.cpp.template"
                                                                  }
                                                            #line 2133 "PrintCSharp.cpp"
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
                                                            #line 1482 "PrintCSharp.cpp.template"
                                                                  if (! noPosition)
                                                                  {
                                                            #line 2159 "PrintCSharp.cpp"
  append(L", int end");
                                                            #line 1484 "PrintCSharp.cpp.template"
                                                                  }
                                                            #line 2163 "PrintCSharp.cpp"
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
                                                            #line 1521 "PrintCSharp.cpp.template"
                                                                  if (! noPosition)
                                                                  {
                                                            #line 2204 "PrintCSharp.cpp"
  append(L", begin");
                                                            #line 1523 "PrintCSharp.cpp.template"
                                                                  }
                                                            #line 2208 "PrintCSharp.cpp"
  append(L");\n");
  append(L"      characters(begin, end);\n");
  append(L"      endNonterminal(name");
                                                            #line 1526 "PrintCSharp.cpp.template"
                                                                  if (! noPosition)
                                                                  {
                                                            #line 2215 "PrintCSharp.cpp"
  append(L", end");
                                                            #line 1528 "PrintCSharp.cpp.template"
                                                                  }
                                                            #line 2219 "PrintCSharp.cpp"
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
                                                            #line 1560 "PrintCSharp.cpp.template"
                                                                }
                                                                if (performanceTest)
                                                                {
                                                            #line 2255 "PrintCSharp.cpp"
  append(L"\n");
  append(L"  public class ContentCounter : EventHandler\n");
  append(L"  {\n");
  append(L"    private int length = 0;\n");
  append(L"    public int getLength() {return length;}\n");
  append(L"    public void reset(String s) {length = 0;}\n");
  append(L"    public void startNonterminal(String name");
                                                            #line 1569 "PrintCSharp.cpp.template"
                                                                  if (! noPosition)
                                                                  {
                                                            #line 2266 "PrintCSharp.cpp"
  append(L", int begin");
                                                            #line 1571 "PrintCSharp.cpp.template"
                                                                  }
                                                            #line 2270 "PrintCSharp.cpp"
  append(L") {}\n");
  append(L"    public void endNonterminal(String name");
                                                            #line 1573 "PrintCSharp.cpp.template"
                                                                  if (! noPosition)
                                                                  {
                                                            #line 2276 "PrintCSharp.cpp"
  append(L", int end");
                                                            #line 1575 "PrintCSharp.cpp.template"
                                                                  }
                                                            #line 2280 "PrintCSharp.cpp"
  append(L") {}\n");
  append(L"    public void terminal(String name, int begin, int end) {length += end - begin;}\n");
  append(L"    public void whitespace(int begin, int end) {length += end - begin;}\n");
  append(L"  }\n");
                                                            #line 1580 "PrintCSharp.cpp.template"
                                                                }
                                                                if (isLrParser)
                                                                {
                                                            #line 2289 "PrintCSharp.cpp"
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
                                                            #line 1600 "PrintCSharp.cpp.template"
                                                                  if (rejectsAmbiguity())
                                                                  {
                                                            #line 2311 "PrintCSharp.cpp"
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
                                                            #line 1612 "PrintCSharp.cpp.template"
                                                                  }
                                                            #line 2325 "PrintCSharp.cpp"
  append(L"\n");
  append(L"      push(new Nonterminal(name, begin, end, pop(count)));\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    public void terminal(String name, int begin, int end)\n");
  append(L"    {\n");
  append(L"      push(new Terminal(name, begin, end));\n");
  append(L"    }");
                                                            #line 1620 "PrintCSharp.cpp.template"
                                                                  if (resolvesAmbiguity)
                                                                  {
                                                            #line 2337 "PrintCSharp.cpp"
  append(L"\n");
  append(L"\n");
  append(L"    public void ambiguity(int begin, int end)\n");
  append(L"    {\n");
  append(L"    }");
                                                            #line 1626 "PrintCSharp.cpp.template"
                                                                  }
                                                            #line 2345 "PrintCSharp.cpp"
  append(L"\n");
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
                                                            #line 1652 "PrintCSharp.cpp.template"
                                                                }
                                                              }
                                                            }

// End
