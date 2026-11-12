// This file was generated on Thu Nov 12, 2026 17:53 (UTC+01) by REx v7.0 which is Copyright (c) 1979-2026 by Gunther Rademacher <grd@gmx.net>
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
  append(L"  public int id;\n");
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
  append(L"  public DeferredEvent(DeferredEvent link, int id, int begin, int end)\n");
  append(L"  {\n");
  append(L"    this.link = link;\n");
  append(L"    this.id = id;\n");
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
  append(L"  public TerminalEvent(DeferredEvent link, int id, int begin, int end)\n");
  append(L"  : base(link, id, begin, end)\n");
  append(L"  {\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  public override void execute(BottomUpEventHandler eventHandler)\n");
  append(L"  {\n");
  append(L"    eventHandler.terminal(id, begin, end);\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  public override String ToString()\n");
  append(L"  {\n");
  append(L"    return \"terminal(\" + TOKEN[id] + \", \" + begin + \", \" + end + \")\";\n");
  append(L"  }\n");
  append(L"}\n");
  append(L"\n");
  append(L"private class NonterminalEvent : DeferredEvent\n");
  append(L"{\n");
  append(L"  public int count;\n");
  append(L"\n");
  append(L"  public NonterminalEvent(DeferredEvent link, int id, int begin, int end, int count)\n");
  append(L"  : base(link, id, begin, end)\n");
  append(L"  {\n");
  append(L"    this.count = count;\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  public override void execute(BottomUpEventHandler eventHandler)\n");
  append(L"  {\n");
  append(L"    eventHandler.nonterminal(id, begin, end, count);\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  public override String ToString()\n");
  append(L"  {\n");
  append(L"    return \"nonterminal(\" + ");
                                                            #line 413 "PrintCSharp.cpp.template"
                                                                printSyntheticNamePrefix(true);
                                                            #line 599 "PrintCSharp.cpp"
  append(L"NONTERMINAL[id]");
                                                            #line 414 "PrintCSharp.cpp.template"
                                                                printSyntheticNameSuffix(true);
                                                            #line 603 "PrintCSharp.cpp"
  append(L" + \", \" + begin + \", \" + end + \", \" + count + \")\";\n");
  append(L"  }\n");
  append(L"}\n");
                                                            #line 418 "PrintCSharp.cpp.template"
                                                                if (resolvesAmbiguity)
                                                                {
                                                            #line 610 "PrintCSharp.cpp"
  append(L"\n");
  append(L"\n");
  append(L"private class AmbiguityEvent : DeferredEvent\n");
  append(L"{\n");
  append(L"  public AmbiguityEvent(DeferredEvent link, int begin, int end)\n");
  append(L"  : base(link, -1, begin, end)\n");
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
                                                            #line 439 "PrintCSharp.cpp.template"
                                                                }
                                                              }
                                                            #line 633 "PrintCSharp.cpp"
  append(L"\n");
  append(L"private static int PARSING = 0;\n");
  append(L"private static int ACCEPTED = 1;\n");
  append(L"private static int ERROR = 2;\n");
  append(L"\n");
  append(L"private ParsingThread parse(int target, int initialState, ");
                                                            #line 446 "PrintCSharp.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 643 "PrintCSharp.cpp"
  append(L"BottomUpEventHandler eventHandler, ");
                                                            #line 449 "PrintCSharp.cpp.template"
                                                              }
                                                            #line 647 "PrintCSharp.cpp"
  append(L"ParsingThread thread)\n");
  append(L"{\n");
  append(L"  Heap<ParsingThread> threads = thread.open(initialState");
                                                            #line 452 "PrintCSharp.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 654 "PrintCSharp.cpp"
  append(L", eventHandler");
                                                            #line 454 "PrintCSharp.cpp.template"
                                                              }
                                                            #line 658 "PrintCSharp.cpp"
  append(L", target);\n");
  append(L"  for (;;)\n");
  append(L"  {\n");
  append(L"    thread = threads.poll();\n");
  append(L"    if (thread.accepted)\n");
  append(L"    {");
                                                            #line 460 "PrintCSharp.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 668 "PrintCSharp.cpp"
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
                                                            #line 475 "PrintCSharp.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 686 "PrintCSharp.cpp"
  append(L", thread.deferredEvent, other.deferredEvent");
                                                            #line 478 "PrintCSharp.cpp.template"
                                                                }
                                                            #line 690 "PrintCSharp.cpp"
  append(L");\n");
  append(L"      }");
                                                            #line 480 "PrintCSharp.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 697 "PrintCSharp.cpp"
  append(L"\n");
  append(L"      while (! threads.isEmpty())\n");
  append(L"      {\n");
  append(L"        ParsingThread other = threads.poll();\n");
  append(L"        thread = thread.e0 < other.e0 ? other : resolve(thread, other);\n");
  append(L"      }");
                                                            #line 488 "PrintCSharp.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                            #line 708 "PrintCSharp.cpp"
  append(L"\n");
  append(L"      if (thread.deferredEvent != null)\n");
  append(L"      {\n");
  append(L"        thread.deferredEvent.release(eventHandler);\n");
  append(L"        thread.deferredEvent = null;\n");
  append(L"      }");
                                                            #line 496 "PrintCSharp.cpp.template"
                                                              }
                                                              if (hasCustomCode)
                                                              {
                                                            #line 719 "PrintCSharp.cpp"
  append(L"\n");
  append(L"      thread.executeDeferredCode();");
                                                            #line 500 "PrintCSharp.cpp.template"
                                                              }
                                                            #line 724 "PrintCSharp.cpp"
  append(L"\n");
  append(L"      return thread;\n");
  append(L"    }\n");
  append(L"\n");
                                                            #line 505 "PrintCSharp.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 732 "PrintCSharp.cpp"
  append(L"    if (! threads.isEmpty())\n");
  append(L"    {\n");
  append(L"      if (threads.peek().Equals(thread))\n");
  append(L"      {\n");
  append(L"        rejectAmbiguity(thread.stack.pos, thread.e0");
                                                            #line 511 "PrintCSharp.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 741 "PrintCSharp.cpp"
  append(L", thread.deferredEvent, threads.peek().deferredEvent");
                                                            #line 514 "PrintCSharp.cpp.template"
                                                                }
                                                            #line 745 "PrintCSharp.cpp"
  append(L");\n");
  append(L"      }\n");
  append(L"    }");
                                                            #line 517 "PrintCSharp.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 753 "PrintCSharp.cpp"
  append(L"    while (! threads.isEmpty() && threads.peek().Equals(thread))\n");
  append(L"    {\n");
  append(L"      thread = resolve(thread, threads.poll());\n");
  append(L"    }");
                                                            #line 523 "PrintCSharp.cpp.template"
                                                              }
                                                              if (tree || hasCustomCode)
                                                              {
                                                                if (rejectsAmbiguity())
                                                                {
                                                            #line 764 "PrintCSharp.cpp"
  append(L"\n");
  append(L"    else\n");
  append(L"    {");
                                                            #line 530 "PrintCSharp.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 772 "PrintCSharp.cpp"
  append(L"\n");
  append(L"    if (threads.isEmpty())\n");
  append(L"    {");
                                                            #line 535 "PrintCSharp.cpp.template"
                                                                }
                                                                if (tree)
                                                                {
                                                            #line 780 "PrintCSharp.cpp"
  append(L"\n");
  append(L"      if (thread.deferredEvent != null)\n");
  append(L"      {\n");
  append(L"        thread.deferredEvent.release(eventHandler);\n");
  append(L"        thread.deferredEvent = null;\n");
  append(L"      }");
                                                            #line 543 "PrintCSharp.cpp.template"
                                                                }
                                                                if (hasCustomCode)
                                                                {
                                                            #line 791 "PrintCSharp.cpp"
  append(L"\n");
  append(L"      thread.executeDeferredCode();");
                                                            #line 547 "PrintCSharp.cpp.template"
                                                                }
                                                            #line 796 "PrintCSharp.cpp"
  append(L"\n");
  append(L"    }");
                                                            #line 549 "PrintCSharp.cpp.template"
                                                              }
                                                            #line 801 "PrintCSharp.cpp"
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
                                                            #line 574 "PrintCSharp.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 829 "PrintCSharp.cpp"
  append(L"\n");
  append(L"private void rejectAmbiguity(int begin, int end");
                                                            #line 577 "PrintCSharp.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 835 "PrintCSharp.cpp"
  append(L", DeferredEvent first, DeferredEvent second");
                                                            #line 580 "PrintCSharp.cpp.template"
                                                                }
                                                            #line 839 "PrintCSharp.cpp"
  append(L")\n");
  append(L"{");
                                                            #line 582 "PrintCSharp.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 845 "PrintCSharp.cpp"
  append(L"\n");
  append(L"  ParseTreeBuilder treeBuilder = new ParseTreeBuilder();\n");
  append(L"  treeBuilder.reset(input);\n");
  append(L"  second.show(treeBuilder);\n");
  append(L"  treeBuilder.nonterminal(");
                                                            #line 588 "PrintCSharp.cpp.template"
                                                                  print(format.toString<wchar_t>(Grammar::syntheticNonterminalCode(0)));
                                                            #line 853 "PrintCSharp.cpp"
  append(L", treeBuilder.getStack()[0].begin, treeBuilder.getStack()[treeBuilder.getTop()].end, treeBuilder.getTop() + 1);\n");
  append(L"  Symbol secondTree = treeBuilder.pop(1)[0];\n");
  append(L"  first.show(treeBuilder);\n");
  append(L"  treeBuilder.nonterminal(");
                                                            #line 592 "PrintCSharp.cpp.template"
                                                                  print(format.toString<wchar_t>(Grammar::syntheticNonterminalCode(0)));
                                                            #line 860 "PrintCSharp.cpp"
  append(L", treeBuilder.getStack()[0].begin, treeBuilder.getStack()[treeBuilder.getTop()].end, treeBuilder.getTop() + 1);\n");
  append(L"  treeBuilder.push(secondTree);\n");
  append(L"  treeBuilder.nonterminal(");
                                                            #line 595 "PrintCSharp.cpp.template"
                                                                  print(format.toString<wchar_t>(Grammar::syntheticNonterminalCode(1)));
                                                            #line 866 "PrintCSharp.cpp"
  append(L", treeBuilder.getStack()[0].begin, treeBuilder.getStack()[treeBuilder.getTop()].end, 2);");
                                                            #line 597 "PrintCSharp.cpp.template"
                                                                }
                                                            #line 870 "PrintCSharp.cpp"
  append(L"\n");
  append(L"  throw new ParseException(begin, end");
                                                            #line 599 "PrintCSharp.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 876 "PrintCSharp.cpp"
  append(L", treeBuilder");
                                                            #line 601 "PrintCSharp.cpp.template"
                                                                }
                                                            #line 880 "PrintCSharp.cpp"
  append(L");\n");
  append(L"}");
                                                            #line 603 "PrintCSharp.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 887 "PrintCSharp.cpp"
  append(L"\n");
  append(L"private ParsingThread resolve(ParsingThread thread, ParsingThread other)\n");
  append(L"{");
                                                            #line 608 "PrintCSharp.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 894 "PrintCSharp.cpp"
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
                                                            #line 619 "PrintCSharp.cpp.template"
                                                                }
                                                            #line 907 "PrintCSharp.cpp"
  append(L"\n");
                                                            #line 621 "PrintCSharp.cpp.template"
                                                                if (shiftAmbiguity)
                                                                {
                                                            #line 912 "PrintCSharp.cpp"
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
                                                            #line 647 "PrintCSharp.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 942 "PrintCSharp.cpp"
  append(L"\n");
  append(L"  if (other.eventCount < thread.eventCount)\n");
  append(L"    thread = other;");
                                                            #line 652 "PrintCSharp.cpp.template"
                                                                }
                                                                if (tree)
                                                                {
                                                            #line 950 "PrintCSharp.cpp"
  append(L"\n");
  append(L"  thread.addAmbiguity(begin, thread.e0);");
                                                            #line 656 "PrintCSharp.cpp.template"
                                                                }
                                                            #line 955 "PrintCSharp.cpp"
  append(L"\n");
  append(L"  return thread;\n");
  append(L"}");
                                                            #line 659 "PrintCSharp.cpp.template"
                                                              }
                                                            #line 961 "PrintCSharp.cpp"
  append(L"\n");
  append(L"private ParsingThread thread = null;");
                                                            #line 661 "PrintCSharp.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 967 "PrintCSharp.cpp"
  append(L"\n");
  append(L"private BottomUpEventHandler eventHandler;");
                                                            #line 664 "PrintCSharp.cpp.template"
                                                              }
                                                            #line 972 "PrintCSharp.cpp"
  append(L"\n");
  append(L"private String input = null;\n");
  append(L"private int size = 0;");
                                                            #line 667 "PrintCSharp.cpp.template"
                                                              if (trace)
                                                              {
                                                            #line 979 "PrintCSharp.cpp"
  append(L"\n");
  append(L"private TextWriter err = Console.Error;");
                                                            #line 670 "PrintCSharp.cpp.template"
                                                              }
                                                            #line 984 "PrintCSharp.cpp"
  append(L"\n");
  append(L"private int maxId = 0;\n");
                                                            #line 673 "PrintCSharp.cpp.template"
                                                            }

                                                            void PrintCSharp::openThread()
                                                            {
                                                            #line 992 "PrintCSharp.cpp"
  append(L"\n");
  append(L"private class ParsingThread : IComparable<ParsingThread>\n");
  append(L"{\n");
  append(L"  public ");
                                                            #line 680 "PrintCSharp.cpp.template"
                                                              print(className.c_str());
                                                            #line 999 "PrintCSharp.cpp"
  append(L" parser;\n");
  append(L"  public Heap<ParsingThread> threads;\n");
  append(L"  public bool accepted;\n");
  append(L"  public StackNode stack;\n");
  append(L"  public int state;\n");
  append(L"  public int action;\n");
  append(L"  public int target;");
                                                            #line 687 "PrintCSharp.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 1010 "PrintCSharp.cpp"
  append(L"\n");
  append(L"  public DeferredEvent deferredEvent;");
                                                            #line 690 "PrintCSharp.cpp.template"
                                                              }
                                                              if (hasCustomCode)
                                                              {
                                                            #line 1017 "PrintCSharp.cpp"
  append(L"\n");
  append(L"  public DeferredCode deferredCode;");
                                                            #line 694 "PrintCSharp.cpp.template"
                                                              }
                                                            #line 1022 "PrintCSharp.cpp"
  append(L"\n");
  append(L"  public int id;");
                                                            #line 696 "PrintCSharp.cpp.template"
                                                              if (resolvesAmbiguity)
                                                              {
                                                            #line 1028 "PrintCSharp.cpp"
  append(L"\n");
  append(L"  public int eventCount;");
                                                            #line 699 "PrintCSharp.cpp.template"
                                                              }
                                                            #line 1033 "PrintCSharp.cpp"
  append(L"\n");
  append(L"\n");
  append(L"  public Heap<ParsingThread> open(int initialState");
                                                            #line 702 "PrintCSharp.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 1040 "PrintCSharp.cpp"
  append(L", BottomUpEventHandler eh");
                                                            #line 704 "PrintCSharp.cpp.template"
                                                              }
                                                            #line 1044 "PrintCSharp.cpp"
  append(L", int t)\n");
  append(L"  {\n");
  append(L"    accepted = false;\n");
  append(L"    target = t;");
                                                            #line 708 "PrintCSharp.cpp.template"
                                                              if (resolvesAmbiguity)
                                                              {
                                                            #line 1052 "PrintCSharp.cpp"
  append(L"\n");
  append(L"    eventCount = 0;");
                                                            #line 711 "PrintCSharp.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                            #line 1059 "PrintCSharp.cpp"
  append(L"\n");
  append(L"    eventHandler = eh;\n");
  append(L"    if (eventHandler != null)\n");
  append(L"    {\n");
  append(L"      eventHandler.reset(parser.input);\n");
  append(L"    }\n");
  append(L"    deferredEvent = null;");
                                                            #line 720 "PrintCSharp.cpp.template"
                                                              }
                                                              if (hasCustomCode && useGlr)
                                                              {
                                                            #line 1071 "PrintCSharp.cpp"
  append(L"\n");
  append(L"    deferredCode = null;");
                                                            #line 724 "PrintCSharp.cpp.template"
                                                              }
                                                            #line 1076 "PrintCSharp.cpp"
  append(L"\n");
  append(L"    stack = new StackNode(-1, ");
                                                            #line 726 "PrintCSharp.cpp.template"
                                                              if (grammar->states->hasLookback)
                                                              {
                                                            #line 1082 "PrintCSharp.cpp"
  append(L"0, ");
                                                            #line 728 "PrintCSharp.cpp.template"
                                                              }
                                                            #line 1086 "PrintCSharp.cpp"
  append(L"e0, null);\n");
  append(L"    state = initialState;\n");
  append(L"    action = predict(initialState);");
                                                            #line 731 "PrintCSharp.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 1093 "PrintCSharp.cpp"
  append(L"\n");
  append(L"    bw = e0;\n");
  append(L"    bs = e0;\n");
  append(L"    es = e0;");
                                                            #line 736 "PrintCSharp.cpp.template"
                                                              }
                                                            #line 1100 "PrintCSharp.cpp"
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
                                                            #line 748 "PrintCSharp.cpp.template"
                                                              if (resolvesAmbiguity)
                                                              {
                                                            #line 1116 "PrintCSharp.cpp"
  append(L"\n");
  append(L"    eventCount = other.eventCount;");
                                                            #line 751 "PrintCSharp.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                            #line 1123 "PrintCSharp.cpp"
  append(L"\n");
  append(L"    bs = other.bs;\n");
  append(L"    bw = other.bw;\n");
  append(L"    es = other.es;\n");
  append(L"    eventHandler = other.eventHandler;\n");
  append(L"    deferredEvent = other.deferredEvent;");
                                                            #line 759 "PrintCSharp.cpp.template"
                                                              }
                                                              if (hasCustomCode)
                                                              {
                                                            #line 1134 "PrintCSharp.cpp"
  append(L"\n");
  append(L"    deferredCode = other.deferredCode;");
                                                            #line 763 "PrintCSharp.cpp.template"
                                                              }
                                                            #line 1139 "PrintCSharp.cpp"
  append(L"\n");
  append(L"    id = ++parser.maxId;\n");
  append(L"    threads = other.threads;\n");
  append(L"    state = other.state;\n");
  append(L"    stack = other.stack;\n");
  append(L"    b0 = other.b0;\n");
  append(L"    e0 = other.e0;");
                                                            #line 770 "PrintCSharp.cpp.template"
                                                              for (size_t i = 1; i <= grammar->k; ++i)
                                                              {
                                                                const wchar_t *iString = format.toString<wchar_t>(i);
                                                            #line 1151 "PrintCSharp.cpp"
  append(L"\n");
  append(L"    l");
                                                            #line 774 "PrintCSharp.cpp.template"
                                                                print(iString);
                                                            #line 1156 "PrintCSharp.cpp"
  append(L" = other.l");
                                                            #line 775 "PrintCSharp.cpp.template"
                                                                print(iString);
                                                            #line 1160 "PrintCSharp.cpp"
  append(L";\n");
  append(L"    b");
                                                            #line 777 "PrintCSharp.cpp.template"
                                                                print(iString);
                                                            #line 1165 "PrintCSharp.cpp"
  append(L" = other.b");
                                                            #line 778 "PrintCSharp.cpp.template"
                                                                print(iString);
                                                            #line 1169 "PrintCSharp.cpp"
  append(L";\n");
  append(L"    e");
                                                            #line 780 "PrintCSharp.cpp.template"
                                                                print(iString);
                                                            #line 1174 "PrintCSharp.cpp"
  append(L" = other.e");
                                                            #line 781 "PrintCSharp.cpp.template"
                                                                print(iString);
                                                            #line 1178 "PrintCSharp.cpp"
  append(L";");
                                                            #line 782 "PrintCSharp.cpp.template"
                                                              }
                                                            #line 1182 "PrintCSharp.cpp"
  append(L"\n");
  append(L"    end = other.end;\n");
  append(L"    return this;\n");
  append(L"  }\n");
  append(L"\n");
                                                            #line 788 "PrintCSharp.cpp.template"
                                                              if (resolvesAmbiguity && tree)
                                                              {
                                                            #line 1191 "PrintCSharp.cpp"
  append(L"\n");
  append(L"  public void addAmbiguity(int begin, int end)\n");
  append(L"  {\n");
  append(L"    if (eventHandler != null)\n");
  append(L"      deferredEvent = new AmbiguityEvent(deferredEvent, begin, end);\n");
  append(L"  }\n");
  append(L"\n");
                                                            #line 797 "PrintCSharp.cpp.template"
                                                              }
                                                            #line 1201 "PrintCSharp.cpp"
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
                                                            #line 825 "PrintCSharp.cpp.template"
                                                              increaseIndent();
                                                              beginPublic();
                                                            }

                                                            void PrintCSharp::printFlush(int i, bool withinThread)
                                                            {
                                                              if (trace)
                                                              {
                                                                increaseIndent(i);
                                                            #line 1240 "PrintCSharp.cpp"
  append(L"\n");
                                                            #line 835 "PrintCSharp.cpp.template"
                                                                if (useGlr && withinThread)
                                                                {
                                                            #line 1245 "PrintCSharp.cpp"
  append(L"parser.");
                                                            #line 837 "PrintCSharp.cpp.template"
                                                                }
                                                            #line 1249 "PrintCSharp.cpp"
  append(L"flushTrace();");
                                                            #line 838 "PrintCSharp.cpp.template"
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
                                                            #line 1263 "PrintCSharp.cpp"
  append(L"\n");
                                                            #line 850 "PrintCSharp.cpp.template"
                                                              print(visibility);
                                                            #line 1267 "PrintCSharp.cpp"
  append(L" ");
                                                            #line 851 "PrintCSharp.cpp.template"
                                                              print(prefix);
                                                              print(type);
                                                              print(name);
                                                            #line 1273 "PrintCSharp.cpp"
  append(L"(");
                                                            #line 854 "PrintCSharp.cpp.template"
                                                              print(args);
                                                            #line 1277 "PrintCSharp.cpp"
  append(L")");
                                                            #line 855 "PrintCSharp.cpp.template"
                                                            }

                                                            void PrintCSharp::privateVars()
                                                            {
                                                              if (trace)
                                                              {
                                                            #line 1286 "PrintCSharp.cpp"
  append(L"\n");
  append(L"  private String lookaheadString()\n");
  append(L"  {\n");
  append(L"    String result = \"\";\n");
  append(L"    if (l1 > 0)\n");
  append(L"    {\n");
  append(L"      result += TOKEN[l1];");
                                                            #line 867 "PrintCSharp.cpp.template"
                                                                for (size_t i = 2; i <= grammar->k; ++i)
                                                                {
                                                            #line 1297 "PrintCSharp.cpp"
  append(L"\n");
  append(L"      if (l");
                                                            #line 870 "PrintCSharp.cpp.template"
                                                                  print(format.toString<wchar_t>(i));
                                                            #line 1302 "PrintCSharp.cpp"
  append(L" > 0)\n");
  append(L"      {\n");
  append(L"        result += \" \" + TOKEN[l");
                                                            #line 873 "PrintCSharp.cpp.template"
                                                                  print(format.toString<wchar_t>(i));
                                                            #line 1308 "PrintCSharp.cpp"
  append(L"];");
                                                            #line 874 "PrintCSharp.cpp.template"
                                                                  increaseIndent();
                                                                }
                                                                for (size_t i = 2; i <= grammar->k; ++i)
                                                                {
                                                                  decreaseIndent();
                                                            #line 1316 "PrintCSharp.cpp"
  append(L"\n");
  append(L"      }");
                                                            #line 880 "PrintCSharp.cpp.template"
                                                                }
                                                            #line 1321 "PrintCSharp.cpp"
  append(L"\n");
  append(L"    }\n");
  append(L"    return result;\n");
  append(L"  }\n");
                                                            #line 885 "PrintCSharp.cpp.template"
                                                              }
                                                            #line 1328 "PrintCSharp.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 887 "PrintCSharp.cpp.template"
                                                              print(useGlr ? L"public" : L"private");
                                                            #line 1333 "PrintCSharp.cpp"
  append(L" int ");
                                                            #line 888 "PrintCSharp.cpp.template"
                                                              if (! isLrParser && (grammar->k > 1 ||
                                                                                   memoization ||
                                                                                   ! grammar->decisionPoints.empty()))
                                                              {
                                                            #line 1340 "PrintCSharp.cpp"
  append(L"lk,");
                                                            #line 892 "PrintCSharp.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 1346 "PrintCSharp.cpp"
  append(L"   ");
                                                            #line 896 "PrintCSharp.cpp.template"
                                                              }
                                                            #line 1350 "PrintCSharp.cpp"
  append(L" b0, e0;");
                                                            #line 897 "PrintCSharp.cpp.template"
                                                              for (size_t k = 1; k <= grammar->k; ++k)
                                                              {
                                                                Format format;
                                                                wchar_t *asString = format.toString<wchar_t>(k);
                                                            #line 1357 "PrintCSharp.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 902 "PrintCSharp.cpp.template"
                                                                print(useGlr ? L"public" : L"private");
                                                            #line 1362 "PrintCSharp.cpp"
  append(L" int l");
                                                            #line 903 "PrintCSharp.cpp.template"
                                                                print(asString);
                                                            #line 1366 "PrintCSharp.cpp"
  append(L", b");
                                                            #line 904 "PrintCSharp.cpp.template"
                                                                print(asString);
                                                            #line 1370 "PrintCSharp.cpp"
  append(L", e");
                                                            #line 905 "PrintCSharp.cpp.template"
                                                                print(asString);
                                                            #line 1374 "PrintCSharp.cpp"
  append(L";");
                                                            #line 906 "PrintCSharp.cpp.template"
                                                              }
                                                              if (hasBacktracking)
                                                              {
                                                            #line 1380 "PrintCSharp.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 910 "PrintCSharp.cpp.template"
                                                                print(useGlr ? L"public" : L"private");
                                                            #line 1385 "PrintCSharp.cpp"
  append(L" int bx, ex, sx, lx, tx;");
                                                            #line 911 "PrintCSharp.cpp.template"
                                                              }
                                                              if (isLrParser && ! useGlr)
                                                              {
                                                            #line 1391 "PrintCSharp.cpp"
  append(L"\n");
  append(L"  private int[] iStack = new int[");
                                                            #line 915 "PrintCSharp.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 1397 "PrintCSharp.cpp"
  append(L"192");
                                                            #line 917 "PrintCSharp.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1403 "PrintCSharp.cpp"
  append(L"128");
                                                            #line 920 "PrintCSharp.cpp.template"
                                                                }
                                                            #line 1407 "PrintCSharp.cpp"
  append(L"];\n");
  append(L"  private int top = -1;");
                                                            #line 922 "PrintCSharp.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                                if (useGlr)
                                                                {
                                                            #line 1416 "PrintCSharp.cpp"
  append(L"\n");
  append(L"  public int bw, bs, es;");
                                                            #line 928 "PrintCSharp.cpp.template"
                                                                }
                                                                if (isLrParser)
                                                                {
                                                            #line 1423 "PrintCSharp.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 932 "PrintCSharp.cpp.template"
                                                                  print(useGlr ? L"public" : L"private");
                                                            #line 1428 "PrintCSharp.cpp"
  append(L" BottomUpEventHandler eventHandler = null;");
                                                            #line 933 "PrintCSharp.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1434 "PrintCSharp.cpp"
  append(L"\n");
  append(L"  private EventHandler eventHandler = null;");
                                                            #line 937 "PrintCSharp.cpp.template"
                                                                }
                                                              }
                                                              if (memoization)
                                                              {
                                                                int bits = Math::bits(grammar->conflictCount);
                                                            #line 1443 "PrintCSharp.cpp"
  append(L"\n");
  append(L"  private IDictionary<int, int> memo = new Dictionary<int, int>();");
                                                            #line 944 "PrintCSharp.cpp.template"
                                                                if (grammar->noThrow)
                                                                {
                                                            #line 1449 "PrintCSharp.cpp"
  append(L"\n");
  append(L"  private bool viable;");
                                                            #line 947 "PrintCSharp.cpp.template"
                                                                }
                                                            #line 1454 "PrintCSharp.cpp"
  append(L"\n");
  append(L"\n");
  append(L"  private void memoize(int i, int e, int v)\n");
  append(L"  {\n");
  append(L"    memo.Add((e << ");
                                                            #line 952 "PrintCSharp.cpp.template"
                                                                print(format.toString<wchar_t>(bits));
                                                            #line 1462 "PrintCSharp.cpp"
  append(L") + i, v);\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  private int memoized(int i, int e)\n");
  append(L"  {\n");
  append(L"    int value = 0;\n");
  append(L"    memo.TryGetValue((e << ");
                                                            #line 959 "PrintCSharp.cpp.template"
                                                                print(format.toString<wchar_t>(bits));
                                                            #line 1472 "PrintCSharp.cpp"
  append(L") + i, out value);\n");
  append(L"    return value;\n");
  append(L"  }");
                                                            #line 962 "PrintCSharp.cpp.template"
                                                              }
                                                            }

                                                            void PrintCSharp::printFileProcessor()
                                                            {
                                                            #line 1482 "PrintCSharp.cpp"
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
                                                            #line 977 "PrintCSharp.cpp.template"
                                                              print(className.c_str());
                                                            #line 1496 "PrintCSharp.cpp"
  append(L" parser;");
                                                            #line 978 "PrintCSharp.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 1501 "PrintCSharp.cpp"
  append(L"\n");
  append(L"    public ContentCounter contentCounter;");
                                                            #line 981 "PrintCSharp.cpp.template"
                                                                if (isLrParser)
                                                                {
                                                            #line 1507 "PrintCSharp.cpp"
  append(L"\n");
  append(L"    public ParseTreeBuilder parseTreeBuilder;");
                                                            #line 984 "PrintCSharp.cpp.template"
                                                                }
                                                              }
                                                            #line 1513 "PrintCSharp.cpp"
  append(L"\n");
  append(L"\n");
  append(L"    public ParseJob(String s, String i)\n");
  append(L"    {\n");
  append(L"      name = s;\n");
  append(L"      input = i;");
                                                            #line 991 "PrintCSharp.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 1523 "PrintCSharp.cpp"
  append(L"\n");
  append(L"      contentCounter = new ContentCounter();");
                                                            #line 994 "PrintCSharp.cpp.template"
                                                                if (isLrParser)
                                                                {
                                                            #line 1529 "PrintCSharp.cpp"
  append(L"\n");
  append(L"      parseTreeBuilder = new ParseTreeBuilder();");
                                                            #line 997 "PrintCSharp.cpp.template"
                                                                }
                                                              }
                                                            #line 1535 "PrintCSharp.cpp"
  append(L"\n");
  append(L"      parser = new ");
                                                            #line 1000 "PrintCSharp.cpp.template"
                                                              print(className.c_str());
                                                            #line 1540 "PrintCSharp.cpp"
  append(L"(input");
                                                            #line 1001 "PrintCSharp.cpp.template"
                                                              if (noLexer)
                                                              {
                                                            #line 1545 "PrintCSharp.cpp"
  append(L", new ");
                                                            #line 1003 "PrintCSharp.cpp.template"
                                                                print(className.c_str());
                                                            #line 1549 "PrintCSharp.cpp"
  append(L"Lexer()");
                                                            #line 1004 "PrintCSharp.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                                if (isLrParser)
                                                                {
                                                            #line 1557 "PrintCSharp.cpp"
  append(L", parseTreeBuilder");
                                                            #line 1009 "PrintCSharp.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1563 "PrintCSharp.cpp"
  append(L", contentCounter");
                                                            #line 1012 "PrintCSharp.cpp.template"
                                                                }
                                                              }
                                                            #line 1568 "PrintCSharp.cpp"
  append(L");\n");
  append(L"    }\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  public static int Main(String[] args)\n");
  append(L"  {\n");
  append(L"    if (args.Length == 0)\n");
  append(L"    {\n");
  append(L"      Console.Out.WriteLine(\"Usage: ");
                                                            #line 1022 "PrintCSharp.cpp.template"
                                                              print(className.c_str());
                                                            #line 1580 "PrintCSharp.cpp"
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
                                                            #line 1090 "PrintCSharp.cpp.template"
                                                              if (useGlr)
                                                              {
                                                            #line 1652 "PrintCSharp.cpp"
  append(L".thread");
                                                            #line 1092 "PrintCSharp.cpp.template"
                                                              }
                                                            #line 1656 "PrintCSharp.cpp"
  append(L".reset(0, 0, 0);\n");
  append(L"                job.parser.");
                                                            #line 1094 "PrintCSharp.cpp.template"
                                                              print(methodPrefixParse);
                                                              print(Format::acceptableName<WString>(grammar->startSymbol()->name).c_str());
                                                            #line 1662 "PrintCSharp.cpp"
  append(L"();\n");
  append(L"                if (! quiet) Console.Out.WriteLine();");
                                                            #line 1097 "PrintCSharp.cpp.template"
                                                              if (tree)
                                                              {
                                                                if (isLrParser)
                                                                {
                                                            #line 1670 "PrintCSharp.cpp"
  append(L"\n");
  append(L"                job.parseTreeBuilder.serialize(job.contentCounter);");
                                                            #line 1103 "PrintCSharp.cpp.template"
                                                                }
                                                            #line 1675 "PrintCSharp.cpp"
  append(L"\n");
  append(L"                if (job.contentCounter.getLength() != job.input.Length)\n");
  append(L"                {\n");
  append(L"                  Console.Error.WriteLine(\"content counter saw \" + job.contentCounter.getLength() + \", but input length is \" + job.input.Length);\n");
  append(L"                  Environment.Exit(1);\n");
  append(L"                }");
                                                            #line 1109 "PrintCSharp.cpp.template"
                                                              }
                                                            #line 1684 "PrintCSharp.cpp"
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
                                                            #line 1168 "PrintCSharp.cpp.template"
                                                            }

                                                            void PrintCSharp::printReadMethod()
                                                            {
                                                            #line 1748 "PrintCSharp.cpp"
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
                                                            #line 1184 "PrintCSharp.cpp.template"
                                                            }

                                                            void PrintCSharp::printInterface()
                                                            {
                                                              if (! packageName.empty())
                                                              {
                                                            #line 1768 "PrintCSharp.cpp"
  append(L"\n");
  append(L"package ");
                                                            #line 1191 "PrintCSharp.cpp.template"
                                                                print(packageName.c_str());
                                                            #line 1773 "PrintCSharp.cpp"
  append(L";\n");
                                                            #line 1193 "PrintCSharp.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                                if (main)
                                                                {
                                                            #line 1781 "PrintCSharp.cpp"
  append(L"\n");
  append(L"import java.io.IOException;\n");
  append(L"import java.io.Writer;\n");
                                                            #line 1201 "PrintCSharp.cpp.template"
                                                                }
                                                              }
                                                            #line 1788 "PrintCSharp.cpp"
  append(L"\n");
  append(L"public interface ");
                                                            #line 1204 "PrintCSharp.cpp.template"
                                                              print(className.c_str());
                                                            #line 1793 "PrintCSharp.cpp"
  append(L"\n");
  append(L"{\n");
  append(L"  void initialize(String input");
                                                            #line 1207 "PrintCSharp.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 1800 "PrintCSharp.cpp"
  append(L", EventHandler eh");
                                                            #line 1209 "PrintCSharp.cpp.template"
                                                              }
                                                            #line 1804 "PrintCSharp.cpp"
  append(L");\n");
  append(L"  void parse();\n");
  append(L"  void reset();\n");
  append(L"  String getErrorMessage(ParseException e);\n");
                                                            #line 1214 "PrintCSharp.cpp.template"
                                                              printParseException();
                                                            #line 1811 "PrintCSharp.cpp"
  append(L"}\n");
                                                            #line 1216 "PrintCSharp.cpp.template"
                                                            }

                                                            void PrintCSharp::printParseException()
                                                            {
                                                            #line 1818 "PrintCSharp.cpp"
  append(L"\n");
  append(L"  public class ParseException : Exception\n");
  append(L"  {\n");
  append(L"    private int begin, end, offending, expected, state;");
                                                            #line 1223 "PrintCSharp.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 1826 "PrintCSharp.cpp"
  append(L"\n");
  append(L"    private bool ambiguousInput;");
                                                            #line 1226 "PrintCSharp.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 1832 "PrintCSharp.cpp"
  append(L"\n");
  append(L"    private ParseTreeBuilder ambiguityDescriptor;");
                                                            #line 1229 "PrintCSharp.cpp.template"
                                                                }
                                                              }
                                                            #line 1838 "PrintCSharp.cpp"
  append(L"\n");
  append(L"\n");
  append(L"    public ParseException(int b, int e, int s, int o, int x)\n");
  append(L"    {\n");
  append(L"      begin = b;\n");
  append(L"      end = e;\n");
  append(L"      state = s;\n");
  append(L"      offending = o;\n");
  append(L"      expected = x;");
                                                            #line 1239 "PrintCSharp.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 1851 "PrintCSharp.cpp"
  append(L"\n");
  append(L"      ambiguousInput = false;");
                                                            #line 1242 "PrintCSharp.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 1857 "PrintCSharp.cpp"
  append(L"\n");
  append(L"      ambiguityDescriptor = null;");
                                                            #line 1245 "PrintCSharp.cpp.template"
                                                                }
                                                              }
                                                            #line 1863 "PrintCSharp.cpp"
  append(L"\n");
  append(L"    }\n");
                                                            #line 1249 "PrintCSharp.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 1869 "PrintCSharp.cpp"
  append(L"\n");
  append(L"    public ParseException(int b, int e");
                                                            #line 1252 "PrintCSharp.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 1875 "PrintCSharp.cpp"
  append(L", ParseTreeBuilder a");
                                                            #line 1254 "PrintCSharp.cpp.template"
                                                                }
                                                            #line 1879 "PrintCSharp.cpp"
  append(L") : this(b, e, -1, -1, -1)\n");
  append(L"    {\n");
  append(L"      ambiguousInput = true;");
                                                            #line 1257 "PrintCSharp.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 1886 "PrintCSharp.cpp"
  append(L"\n");
  append(L"      ambiguityDescriptor = a;");
                                                            #line 1260 "PrintCSharp.cpp.template"
                                                                }
                                                            #line 1891 "PrintCSharp.cpp"
  append(L"\n");
  append(L"    }\n");
                                                            #line 1263 "PrintCSharp.cpp.template"
                                                              }
                                                            #line 1896 "PrintCSharp.cpp"
  append(L"\n");
  append(L"    public String getMessage()\n");
  append(L"    {\n");
  append(L"      return ");
                                                            #line 1267 "PrintCSharp.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 1904 "PrintCSharp.cpp"
  append(L"ambiguousInput\n");
  append(L"           ? \"ambiguous input\"\n");
  append(L"           : ");
                                                            #line 1271 "PrintCSharp.cpp.template"
                                                              }
                                                            #line 1910 "PrintCSharp.cpp"
  append(L"offending < 0\n");
  append(L"           ? \"lexical analysis failed\"\n");
  append(L"           : \"syntax error\";\n");
  append(L"    }\n");
                                                            #line 1276 "PrintCSharp.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 1918 "PrintCSharp.cpp"
  append(L"\n");
  append(L"    public void serialize(EventHandler eventHandler)\n");
  append(L"    {");
                                                            #line 1280 "PrintCSharp.cpp.template"
                                                                if (rejectsAmbiguity())
                                                                {
                                                            #line 1925 "PrintCSharp.cpp"
  append(L"\n");
  append(L"      ambiguityDescriptor.serialize(eventHandler);");
                                                            #line 1283 "PrintCSharp.cpp.template"
                                                                }
                                                            #line 1930 "PrintCSharp.cpp"
  append(L"\n");
  append(L"    }\n");
                                                            #line 1286 "PrintCSharp.cpp.template"
                                                              }
                                                            #line 1935 "PrintCSharp.cpp"
  append(L"\n");
  append(L"    public int getBegin() {return begin;}\n");
  append(L"    public int getEnd() {return end;}\n");
  append(L"    public int getState() {return state;}\n");
  append(L"    public int getOffending() {return offending;}\n");
  append(L"    public int getExpected() {return expected;}\n");
  append(L"    public bool isAmbiguousInput() {return ");
                                                            #line 1293 "PrintCSharp.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 1946 "PrintCSharp.cpp"
  append(L"ambiguousInput");
                                                            #line 1295 "PrintCSharp.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 1952 "PrintCSharp.cpp"
  append(L"false");
                                                            #line 1298 "PrintCSharp.cpp.template"
                                                              }
                                                            #line 1956 "PrintCSharp.cpp"
  append(L";}\n");
  append(L"  }\n");
                                                            #line 1301 "PrintCSharp.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 1962 "PrintCSharp.cpp"
  append(L"\n");
  append(L"  public interface EventHandler\n");
  append(L"  {\n");
  append(L"    void reset(String s);\n");
  append(L"    void startNonterminal(int id");
                                                            #line 1307 "PrintCSharp.cpp.template"
                                                                if (! noPosition)
                                                                {
                                                            #line 1971 "PrintCSharp.cpp"
  append(L", int begin");
                                                            #line 1309 "PrintCSharp.cpp.template"
                                                                }
                                                            #line 1975 "PrintCSharp.cpp"
  append(L");\n");
  append(L"    void endNonterminal(int id");
                                                            #line 1311 "PrintCSharp.cpp.template"
                                                                if (! noPosition)
                                                                {
                                                            #line 1981 "PrintCSharp.cpp"
  append(L", int end");
                                                            #line 1313 "PrintCSharp.cpp.template"
                                                                }
                                                            #line 1985 "PrintCSharp.cpp"
  append(L");\n");
  append(L"    void terminal(int id, int begin, int end);\n");
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
  append(L"    public void startNonterminal(int id, int begin)\n");
  append(L"    {\n");
  append(L"      Nonterminal nonterminal = new Nonterminal(id, begin, begin, new Symbol[0]);\n");
  append(L"      if (top >= 0) addChild(nonterminal);\n");
  append(L"      if (++top >= stack.Length) Array.Resize(ref stack, stack.Length << 1);\n");
  append(L"      stack[top] = nonterminal;\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    public void endNonterminal(int id, int end)\n");
  append(L"    {\n");
  append(L"      stack[top].end = end;\n");
  append(L"      if (top > 0) --top;\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    public void terminal(int id, int begin, int end)\n");
  append(L"    {\n");
  append(L"      addChild(new Terminal(id, begin, end));\n");
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
  append(L"    public int id;\n");
  append(L"    public int begin;\n");
  append(L"    public int end;\n");
  append(L"\n");
  append(L"    protected Symbol(int id, int begin, int end)\n");
  append(L"    {\n");
  append(L"      this.id = id;\n");
  append(L"      this.begin = begin;\n");
  append(L"      this.end = end;\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    public abstract String getName();\n");
  append(L"\n");
  append(L"    public abstract void send(EventHandler e);\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  public class Terminal : Symbol\n");
  append(L"  {\n");
  append(L"    public Terminal(int id, int begin, int end)\n");
  append(L"    : base(id, begin, end)\n");
  append(L"    {\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    public override String getName()\n");
  append(L"    {\n");
  append(L"      return TOKEN[id];\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    public override void send(EventHandler e)\n");
  append(L"    {\n");
  append(L"      e.terminal(id, begin, end);\n");
  append(L"    }\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  public class Nonterminal : Symbol\n");
  append(L"  {\n");
  append(L"    public Symbol[] children;\n");
  append(L"\n");
  append(L"    public Nonterminal(int id, int begin, int end, Symbol[] children)\n");
  append(L"    : base(id, begin, end)\n");
  append(L"    {\n");
  append(L"      this.children = children;\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    public override String getName()\n");
  append(L"    {\n");
  append(L"      return ");
                                                            #line 1416 "PrintCSharp.cpp.template"
                                                                printSyntheticNamePrefix();
                                                            #line 2091 "PrintCSharp.cpp"
  append(L"NONTERMINAL[id]");
                                                            #line 1417 "PrintCSharp.cpp.template"
                                                                printSyntheticNameSuffix();
                                                            #line 2095 "PrintCSharp.cpp"
  append(L";\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    public override void send(EventHandler e)\n");
  append(L"    {\n");
  append(L"      e.startNonterminal(id, begin);\n");
  append(L"      int pos = begin;\n");
  append(L"      foreach (Symbol c in children)\n");
  append(L"      {\n");
  append(L"        if (pos < c.begin) e.whitespace(pos, c.begin);\n");
  append(L"        c.send(e);\n");
  append(L"        pos = c.end;\n");
  append(L"      }\n");
  append(L"      if (pos < end) e.whitespace(pos, end);\n");
  append(L"      e.endNonterminal(id, end);\n");
  append(L"    }\n");
  append(L"  }\n");
                                                            #line 1435 "PrintCSharp.cpp.template"
                                                                if (isLrParser)
                                                                {
                                                            #line 2116 "PrintCSharp.cpp"
  append(L"\n");
  append(L"  public interface BottomUpEventHandler\n");
  append(L"  {\n");
  append(L"    void reset(String input);\n");
  append(L"    void nonterminal(int id, int begin, int end, int count);\n");
  append(L"    void terminal(int id, int begin, int end);");
                                                            #line 1442 "PrintCSharp.cpp.template"
                                                                  if (resolvesAmbiguity)
                                                                  {
                                                            #line 2126 "PrintCSharp.cpp"
  append(L"\n");
  append(L"    void ambiguity(int begin, int end);");
                                                            #line 1445 "PrintCSharp.cpp.template"
                                                                  }
                                                            #line 2131 "PrintCSharp.cpp"
  append(L"\n");
  append(L"  }\n");
                                                            #line 1448 "PrintCSharp.cpp.template"
                                                                }
                                                                if (main)
                                                                {
                                                            #line 2138 "PrintCSharp.cpp"
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
  append(L"    public void startNonterminal(int id");
                                                            #line 1477 "PrintCSharp.cpp.template"
                                                                  if (! noPosition)
                                                                  {
                                                            #line 2169 "PrintCSharp.cpp"
  append(L", int begin");
                                                            #line 1479 "PrintCSharp.cpp.template"
                                                                  }
                                                            #line 2173 "PrintCSharp.cpp"
  append(L")\n");
  append(L"    {\n");
  append(L"      startElement(getNonterminalName(id));\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    private void startElement(String name)\n");
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
  append(L"    public void endNonterminal(int id");
                                                            #line 1506 "PrintCSharp.cpp.template"
                                                                  if (! noPosition)
                                                                  {
                                                            #line 2204 "PrintCSharp.cpp"
  append(L", int end");
                                                            #line 1508 "PrintCSharp.cpp.template"
                                                                  }
                                                            #line 2208 "PrintCSharp.cpp"
  append(L")\n");
  append(L"    {\n");
  append(L"      endElement(getNonterminalName(id));\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    private void endElement(String name)\n");
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
  append(L"    public void terminal(int id, int begin, int end)\n");
  append(L"    {\n");
  append(L"      String name = getTerminalName(id);\n");
  append(L"      if (name[0] == '\\'')\n");
  append(L"      {\n");
  append(L"        name = \"TOKEN\";\n");
  append(L"      }\n");
  append(L"      startElement(name);\n");
  append(L"      characters(begin, end);\n");
  append(L"      endElement(name);\n");
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
                                                            #line 1584 "PrintCSharp.cpp.template"
                                                                }
                                                                if (performanceTest)
                                                                {
                                                            #line 2288 "PrintCSharp.cpp"
  append(L"\n");
  append(L"  public class ContentCounter : EventHandler\n");
  append(L"  {\n");
  append(L"    private int length = 0;\n");
  append(L"    public int getLength() {return length;}\n");
  append(L"    public void reset(String s) {length = 0;}\n");
  append(L"    public void startNonterminal(int id");
                                                            #line 1593 "PrintCSharp.cpp.template"
                                                                  if (! noPosition)
                                                                  {
                                                            #line 2299 "PrintCSharp.cpp"
  append(L", int begin");
                                                            #line 1595 "PrintCSharp.cpp.template"
                                                                  }
                                                            #line 2303 "PrintCSharp.cpp"
  append(L") {}\n");
  append(L"    public void endNonterminal(int id");
                                                            #line 1597 "PrintCSharp.cpp.template"
                                                                  if (! noPosition)
                                                                  {
                                                            #line 2309 "PrintCSharp.cpp"
  append(L", int end");
                                                            #line 1599 "PrintCSharp.cpp.template"
                                                                  }
                                                            #line 2313 "PrintCSharp.cpp"
  append(L") {}\n");
  append(L"    public void terminal(int id, int begin, int end) {length += end - begin;}\n");
  append(L"    public void whitespace(int begin, int end) {length += end - begin;}\n");
  append(L"  }\n");
                                                            #line 1604 "PrintCSharp.cpp.template"
                                                                }
                                                                if (isLrParser)
                                                                {
                                                            #line 2322 "PrintCSharp.cpp"
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
  append(L"    public void nonterminal(int id, int begin, int end, int count)\n");
  append(L"    {");
                                                            #line 1624 "PrintCSharp.cpp.template"
                                                                  if (rejectsAmbiguity())
                                                                  {
                                                            #line 2344 "PrintCSharp.cpp"
  append(L"\n");
  append(L"      if (count > top + 1)\n");
  append(L"      {\n");
  append(L"        Symbol[] content = pop(top + 1);\n");
  append(L"        nonterminal(");
                                                            #line 1630 "PrintCSharp.cpp.template"
                                                                    print(format.toString<wchar_t>(Grammar::syntheticNonterminalCode(2)));
                                                            #line 2352 "PrintCSharp.cpp"
  append(L", begin, content.Length == 0 ? end : content[0].begin, 0);\n");
  append(L"        foreach (Symbol symbol in content)\n");
  append(L"        {\n");
  append(L"          push(symbol);\n");
  append(L"        }\n");
  append(L"        count = top + 1;\n");
  append(L"      }");
                                                            #line 1637 "PrintCSharp.cpp.template"
                                                                  }
                                                            #line 2362 "PrintCSharp.cpp"
  append(L"\n");
  append(L"      push(new Nonterminal(id, begin, end, pop(count)));\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    public void terminal(int id, int begin, int end)\n");
  append(L"    {\n");
  append(L"      push(new Terminal(id, begin, end));\n");
  append(L"    }");
                                                            #line 1645 "PrintCSharp.cpp.template"
                                                                  if (resolvesAmbiguity)
                                                                  {
                                                            #line 2374 "PrintCSharp.cpp"
  append(L"\n");
  append(L"\n");
  append(L"    public void ambiguity(int begin, int end)\n");
  append(L"    {\n");
  append(L"    }");
                                                            #line 1651 "PrintCSharp.cpp.template"
                                                                  }
                                                            #line 2382 "PrintCSharp.cpp"
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
                                                            #line 1677 "PrintCSharp.cpp.template"
                                                                }
                                                              }
                                                            }

// End
