// This file was generated on Thu Nov 12, 2026 17:53 (UTC+01) by REx v7.0 which is Copyright (c) 1979-2026 by Gunther Rademacher <grd@gmx.net>
// REx command line: PrintJava.cpp.template
                                                            #line 1 "PrintJava.cpp.template"
                                                            #include "../common/Memory.hpp"

                                                            #include "PrintJava.hpp"
                                                            #include "ItemSet.hpp"
                                                            #include "../common/CompressedMap.hpp"

                                                            void PrintJava::openClass()
                                                            {
                                                              if (hasProlog)
                                                              {
                                                            #line 15 "PrintJava.cpp"
  append(L"\n");
                                                            #line 12 "PrintJava.cpp.template"
                                                              }
                                                              else
                                                              {
                                                                size_t initialOutputSize = size();
                                                                if (! packageName.empty())
                                                                {
                                                            #line 24 "PrintJava.cpp"
  append(L"\n");
  append(L"package ");
                                                            #line 19 "PrintJava.cpp.template"
                                                                  print(packageName.c_str());
                                                            #line 29 "PrintJava.cpp"
  append(L";\n");
                                                            #line 21 "PrintJava.cpp.template"
                                                                }
                                                                if ((tree && (main || useGlr) && interfaceName.empty()) || grammar->basex || trace)
                                                                {
                                                            #line 35 "PrintJava.cpp"
  append(L"\n");
  append(L"import java.io.IOException;");
                                                            #line 25 "PrintJava.cpp.template"
                                                                }
                                                                if (trace)
                                                                {
                                                            #line 42 "PrintJava.cpp"
  append(L"\n");
  append(L"import java.io.UnsupportedEncodingException;");
                                                            #line 29 "PrintJava.cpp.template"
                                                                }
                                                                if (trace || (tree && main))
                                                                {
                                                            #line 49 "PrintJava.cpp"
  append(L"\n");
  append(L"import java.io.OutputStreamWriter;");
                                                            #line 33 "PrintJava.cpp.template"
                                                                }
                                                                if (trace || (tree && main) || (tree && useGlr && interfaceName.empty()))
                                                                {
                                                            #line 56 "PrintJava.cpp"
  append(L"\n");
  append(L"import java.io.Writer;");
                                                            #line 37 "PrintJava.cpp.template"
                                                                }
                                                                if ((tree && interfaceName.empty()) || isLrParser)
                                                                {
                                                                  if (useGlr)
                                                                  {
                                                                    if (tree && interfaceName.empty())
                                                                    {
                                                            #line 67 "PrintJava.cpp"
  append(L"\n");
  append(L"import java.util.Arrays;");
                                                            #line 45 "PrintJava.cpp.template"
                                                                    }
                                                            #line 72 "PrintJava.cpp"
  append(L"\n");
  append(L"import java.util.PriorityQueue;");
                                                            #line 47 "PrintJava.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 79 "PrintJava.cpp"
  append(L"\n");
  append(L"import java.util.Arrays;");
                                                            #line 51 "PrintJava.cpp.template"
                                                                  }
                                                                }
                                                                if (saxon == 99)
                                                                {
                                                            #line 87 "PrintJava.cpp"
  append(L"\n");
  append(L"import net.sf.saxon.Configuration;\n");
  append(L"import net.sf.saxon.event.Builder;\n");
  append(L"import net.sf.saxon.expr.XPathContext;\n");
  append(L"import net.sf.saxon.lib.ExtensionFunctionCall;\n");
  append(L"import net.sf.saxon.lib.ExtensionFunctionDefinition;\n");
  append(L"import net.sf.saxon.lib.Initializer;\n");
  append(L"import net.sf.saxon.om.NoNamespaceName;\n");
  append(L"import net.sf.saxon.om.Sequence;\n");
  append(L"import net.sf.saxon.om.StructuredQName;\n");
  append(L"import net.sf.saxon.trans.XPathException;\n");
  append(L"import net.sf.saxon.type.AnySimpleType;\n");
  append(L"import net.sf.saxon.type.AnyType;");
                                                            #line 67 "PrintJava.cpp.template"
                                                                  if (! tree)
                                                                  {
                                                            #line 104 "PrintJava.cpp"
  append(L"\n");
  append(L"import net.sf.saxon.value.EmptySequence;");
                                                            #line 70 "PrintJava.cpp.template"
                                                                  }
                                                            #line 109 "PrintJava.cpp"
  append(L"\n");
  append(L"import net.sf.saxon.value.SequenceType;");
                                                            #line 72 "PrintJava.cpp.template"
                                                                  if (interfaceName.empty())
                                                                  {
                                                            #line 115 "PrintJava.cpp"
  append(L"\n");
  append(L"import net.sf.saxon.expr.parser.ExplicitLocation;\n");
  append(L"import net.sf.saxon.expr.parser.Location;");
                                                            #line 76 "PrintJava.cpp.template"
                                                                  }
                                                                }
                                                                else if (saxon)
                                                                {
                                                            #line 124 "PrintJava.cpp"
  append(L"\n");
  append(L"import java.util.ArrayList;\n");
  append(L"import java.util.List;\n");
  append(L"import net.sf.saxon.Configuration;\n");
  append(L"import net.sf.saxon.event.Builder;\n");
  append(L"import net.sf.saxon.expr.XPathContext;\n");
  append(L"import net.sf.saxon.lib.ExtensionFunctionCall;\n");
  append(L"import net.sf.saxon.lib.ExtensionFunctionDefinition;\n");
  append(L"import net.sf.saxon.lib.Initializer;\n");
  append(L"import net.sf.saxon.om.AttributeInfo;\n");
  append(L"import net.sf.saxon.om.NoNamespaceName;\n");
  append(L"import net.sf.saxon.om.Sequence;\n");
  append(L"import net.sf.saxon.om.SmallAttributeMap;\n");
  append(L"import net.sf.saxon.om.StructuredQName;\n");
  append(L"import net.sf.saxon.trans.XPathException;\n");
  append(L"import net.sf.saxon.type.AnySimpleType;\n");
  append(L"import net.sf.saxon.type.AnyType;\n");
  append(L"import net.sf.saxon.value.SequenceType;");
                                                            #line 97 "PrintJava.cpp.template"
                                                                  if (! tree)
                                                                  {
                                                            #line 146 "PrintJava.cpp"
  append(L"\n");
  append(L"import net.sf.saxon.value.EmptySequence;");
                                                            #line 100 "PrintJava.cpp.template"
                                                                  }
                                                                  if (interfaceName.empty())
                                                                  {
                                                            #line 153 "PrintJava.cpp"
  append(L"\n");
  append(L"import net.sf.saxon.expr.parser.Loc;\n");
  append(L"import net.sf.saxon.om.AttributeMap;\n");
  append(L"import net.sf.saxon.om.EmptyAttributeMap;\n");
  append(L"import net.sf.saxon.om.NamespaceMap;\n");
  append(L"import net.sf.saxon.s9api.Location;");
                                                            #line 108 "PrintJava.cpp.template"
                                                                  }
                                                                  if (saxon == 110)
                                                                  {
                                                            #line 164 "PrintJava.cpp"
  append(L"\n");
  append(L"import net.sf.saxon.str.StringView;");
                                                            #line 112 "PrintJava.cpp.template"
                                                                  }
                                                                }
                                                                if (grammar->basex)
                                                                {
                                                            #line 172 "PrintJava.cpp"
  append(L"\n");
  append(L"import org.basex.build.MemBuilder;\n");
  append(L"import org.basex.build.Parser;\n");
  append(L"import org.basex.core.MainOptions;\n");
  append(L"import org.basex.query.value.item.Str;\n");
  append(L"import org.basex.query.value.node.XNode;\n");
  append(L"import org.basex.query.value.node.DBNode;\n");
  append(L"import org.basex.util.Atts;\n");
  append(L"import org.basex.util.Token;");
                                                            #line 124 "PrintJava.cpp.template"
                                                                }
                                                                if (initialOutputSize != size())
                                                                {
                                                            #line 186 "PrintJava.cpp"
  append(L"\n");
                                                            #line 128 "PrintJava.cpp.template"
                                                                }
                                                            #line 190 "PrintJava.cpp"
  append(L"\n");
  append(L"@SuppressWarnings(\"all\")\n");
  append(L"public class ");
                                                            #line 131 "PrintJava.cpp.template"
                                                                print(className.c_str());
                                                                if (! interfaceName.empty())
                                                                {
                                                            #line 198 "PrintJava.cpp"
  append(L" implements ");
                                                            #line 134 "PrintJava.cpp.template"
                                                                  print(interfaceName.c_str());
                                                                }
                                                            #line 203 "PrintJava.cpp"
  append(L"\n");
  append(L"{");
                                                            #line 137 "PrintJava.cpp.template"
                                                              }
                                                              if (main)
                                                              {
                                                            #line 210 "PrintJava.cpp"
  append(L"\n");
  append(L"  public static void main(String args[]) throws Exception\n");
  append(L"  {\n");
  append(L"    if (args.length == 0)\n");
  append(L"    {\n");
  append(L"      System.out.println(\"Usage: java ");
                                                            #line 145 "PrintJava.cpp.template"
                                                                print(className.c_str());
                                                                if (tree)
                                                                {
                                                            #line 221 "PrintJava.cpp"
  append(L" [-i]");
                                                            #line 148 "PrintJava.cpp.template"
                                                                }
                                                            #line 225 "PrintJava.cpp"
  append(L" INPUT...\");\n");
  append(L"      System.out.println();\n");
  append(L"      System.out.println(\"  parse INPUT, which is either a filename or literal text enclosed in curly braces\");");
                                                            #line 152 "PrintJava.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 232 "PrintJava.cpp"
  append(L"\n");
  append(L"      System.out.println();\n");
  append(L"      System.out.println(\"  Option:\");\n");
  append(L"      System.out.println(\"    -i     indented parse tree\");");
                                                            #line 157 "PrintJava.cpp.template"
                                                                }
                                                            #line 239 "PrintJava.cpp"
  append(L"\n");
  append(L"    }\n");
  append(L"    else\n");
  append(L"    {");
                                                            #line 161 "PrintJava.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 247 "PrintJava.cpp"
  append(L"\n");
  append(L"      boolean indent = false;");
                                                            #line 164 "PrintJava.cpp.template"
                                                                }
                                                            #line 252 "PrintJava.cpp"
  append(L"\n");
  append(L"      for (String arg : args)\n");
  append(L"      {");
                                                            #line 167 "PrintJava.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 259 "PrintJava.cpp"
  append(L"\n");
  append(L"        if (arg.equals(\"-i\"))\n");
  append(L"        {\n");
  append(L"          indent = true;\n");
  append(L"          continue;\n");
  append(L"        }\n");
  append(L"        Writer w = new OutputStreamWriter(System.out, \"UTF-8\");\n");
  append(L"        XmlSerializer s = new XmlSerializer(w, indent");
                                                            #line 176 "PrintJava.cpp.template"
                                                                  printNamesArgument();
                                                            #line 270 "PrintJava.cpp"
  append(L");");
                                                            #line 177 "PrintJava.cpp.template"
                                                                  if (isLrParser)
                                                                  {
                                                            #line 275 "PrintJava.cpp"
  append(L"\n");
  append(L"        ParseTreeBuilder b = new ParseTreeBuilder();");
                                                            #line 180 "PrintJava.cpp.template"
                                                                  }
                                                                }
                                                            #line 281 "PrintJava.cpp"
  append(L"\n");
  append(L"        String input = read(arg);\n");
  append(L"        ");
                                                            #line 184 "PrintJava.cpp.template"
                                                                print(className.c_str());
                                                            #line 287 "PrintJava.cpp"
  append(L" parser = new ");
                                                            #line 185 "PrintJava.cpp.template"
                                                                print(className.c_str());
                                                            #line 291 "PrintJava.cpp"
  append(L"(input");
                                                            #line 186 "PrintJava.cpp.template"
                                                                if (noLexer)
                                                                {
                                                            #line 296 "PrintJava.cpp"
  append(L", new ");
                                                            #line 188 "PrintJava.cpp.template"
                                                                  print(className.c_str());
                                                            #line 300 "PrintJava.cpp"
  append(L"Lexer()");
                                                            #line 189 "PrintJava.cpp.template"
                                                                }
                                                                if (tree)
                                                                {
                                                            #line 306 "PrintJava.cpp"
  append(L", ");
                                                            #line 192 "PrintJava.cpp.template"
                                                                  if (isLrParser)
                                                                  {
                                                            #line 311 "PrintJava.cpp"
  append(L"b");
                                                            #line 194 "PrintJava.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 317 "PrintJava.cpp"
  append(L"s");
                                                            #line 197 "PrintJava.cpp.template"
                                                                  }
                                                                }
                                                            #line 322 "PrintJava.cpp"
  append(L");\n");
  append(L"        try\n");
  append(L"        {");
                                                            #line 201 "PrintJava.cpp.template"
                                                                #if 0
                                                                if (grammar->tables && grammar->k >= grammar->tables)
                                                                {
                                                            #line 330 "PrintJava.cpp"
  append(L"\n");
  append(L"          parser.begin = -1;\n");
  append(L"//        if (begin >= 0) System.out.println(\"predict(\" + dpi + \")[\" + TOKEN[l1] + \", \" + TOKEN[l2] + \"] = \" + lk);\n");
  append(L"\n");
  append(L"          for (int p = 0; p < ");
                                                            #line 208 "PrintJava.cpp.template"
                                                                  print(format.toString<wchar_t>(grammar->caseidTable->getRows()));
                                                            #line 338 "PrintJava.cpp"
  append(L"; ++p)\n");
  append(L"          {\n");
  append(L"            int count = 0;");
                                                            #line 211 "PrintJava.cpp.template"
                                                                  for (size_t i = 1; i <= grammar->k; ++i)
                                                                  {
                                                            #line 345 "PrintJava.cpp"
  append(L"\n");
  append(L"            for (parser.l");
                                                            #line 214 "PrintJava.cpp.template"
                                                                    print(format.toString<wchar_t>(i));
                                                            #line 350 "PrintJava.cpp"
  append(L" = 1; parser.l");
                                                            #line 215 "PrintJava.cpp.template"
                                                                    print(format.toString<wchar_t>(i));
                                                            #line 354 "PrintJava.cpp"
  append(L" < TOKEN.length; ++parser.l");
                                                            #line 217 "PrintJava.cpp.template"
                                                                    print(format.toString<wchar_t>(i));
                                                            #line 358 "PrintJava.cpp"
  append(L")");
                                                            #line 219 "PrintJava.cpp.template"
                                                                  }
                                                            #line 362 "PrintJava.cpp"
  append(L"\n");
  append(L"            {\n");
  append(L"              parser.predict(p);\n");
  append(L"              if (parser.lk != 0)\n");
  append(L"              {\n");
  append(L"                ++count;\n");
  append(L"              }\n");
  append(L"            }\n");
  append(L"            if (count == 0)\n");
  append(L"            {\n");
  append(L"              System.out.println(\"predict(\" + p + \") has \" + count + \" matches\");\n");
  append(L"            }\n");
  append(L"          }\n");
  append(L"          System.out.println(\"predictions checked\");\n");
  append(L"          parser.reset(0, 0, 0);\n");
  append(L"\n");
                                                            #line 236 "PrintJava.cpp.template"
                                                                }
                                                                #endif

                                                                if (trace)
                                                                {
                                                            #line 385 "PrintJava.cpp"
  append(L"\n");
  append(L"          parser.writeTrace(\"<?xml version=\\\"1.0\\\" encoding=\\\"UTF-8\\\"?\" + \">\\n<trace>\\n\");");
                                                            #line 243 "PrintJava.cpp.template"
                                                                }
                                                            #line 390 "PrintJava.cpp"
  append(L"\n");
  append(L"          parser.");
                                                            #line 245 "PrintJava.cpp.template"
                                                                print(methodPrefixParse);
                                                                print(Format::acceptableName<WString>(grammar->startSymbol()->name).c_str());
                                                            #line 396 "PrintJava.cpp"
  append(L"();");
                                                            #line 247 "PrintJava.cpp.template"
                                                                if (trace)
                                                                {
                                                            #line 401 "PrintJava.cpp"
  append(L"\n");
  append(L"          parser.writeTrace(\"</trace>\\n\");");
                                                            #line 250 "PrintJava.cpp.template"
                                                                }
                                                                if (tree && isLrParser)
                                                                {
                                                            #line 408 "PrintJava.cpp"
  append(L"\n");
  append(L"          b.serialize(s);");
                                                            #line 254 "PrintJava.cpp.template"
                                                                }
                                                            #line 413 "PrintJava.cpp"
  append(L"\n");
  append(L"        }\n");
  append(L"        catch (ParseException pe)\n");
  append(L"        {");
                                                            #line 258 "PrintJava.cpp.template"
                                                                if (rejectsAmbiguity() && tree)
                                                                {
                                                            #line 421 "PrintJava.cpp"
  append(L"\n");
  append(L"          if (pe.isAmbiguousInput())\n");
  append(L"          {\n");
  append(L"            pe.serialize(s);\n");
  append(L"            w.write(\"\\n\");\n");
  append(L"            w.flush();\n");
  append(L"          }");
                                                            #line 266 "PrintJava.cpp.template"
                                                                }
                                                            #line 431 "PrintJava.cpp"
  append(L"\n");
  append(L"          throw new RuntimeException(\"ParseException while processing \" + arg + \":\\n\" + parser.getErrorMessage(pe));\n");
  append(L"        }");
                                                            #line 269 "PrintJava.cpp.template"
                                                                if (tree || trace)
                                                                {
                                                            #line 438 "PrintJava.cpp"
  append(L"\n");
  append(L"        finally\n");
  append(L"        {");
                                                            #line 273 "PrintJava.cpp.template"
                                                                }
                                                                if (trace)
                                                                {
                                                            #line 446 "PrintJava.cpp"
  append(L"\n");
  append(L"          parser.flushTrace();");
                                                            #line 277 "PrintJava.cpp.template"
                                                                }
                                                                if (tree)
                                                                {
                                                            #line 453 "PrintJava.cpp"
  append(L"\n");
  append(L"          w.close();");
                                                            #line 281 "PrintJava.cpp.template"
                                                                }
                                                                if (tree || trace)
                                                                {
                                                            #line 460 "PrintJava.cpp"
  append(L"\n");
  append(L"        }");
                                                            #line 285 "PrintJava.cpp.template"
                                                                }
                                                            #line 465 "PrintJava.cpp"
  append(L"\n");
  append(L"      }\n");
  append(L"    }\n");
  append(L"  }\n");
                                                            #line 290 "PrintJava.cpp.template"
                                                              }
                                                              if (interfaceName.empty())
                                                              {
                                                                printParseException();
                                                                printEventHandlerImplementation();
                                                              }
                                                              if (saxon)
                                                              {
                                                            #line 479 "PrintJava.cpp"
  append(L"\n");
  append(L"  public static class SaxonInitializer implements Initializer\n");
  append(L"  {\n");
  append(L"    @Override\n");
  append(L"    public void initialize(Configuration conf)\n");
  append(L"    {");
                                                            #line 303 "PrintJava.cpp.template"
                                                                for (Node *n = grammar->nonTerminals; n; n = n->followingSibling)
                                                                {
                                                                  Production *p = static_cast <Production *> (n);
                                                                  if (p->isStartSymbol())
                                                                  {
                                                            #line 492 "PrintJava.cpp"
  append(L"\n");
  append(L"      conf.registerExtensionFunction(new SaxonDefinition_");
                                                            #line 309 "PrintJava.cpp.template"
                                                                    print(Format::acceptableName<WString>(p->name).c_str());
                                                            #line 497 "PrintJava.cpp"
  append(L"());");
                                                            #line 310 "PrintJava.cpp.template"
                                                                  }
                                                                }
                                                            #line 502 "PrintJava.cpp"
  append(L"\n");
  append(L"    }\n");
  append(L"  }\n");
                                                            #line 315 "PrintJava.cpp.template"
                                                                for (Node *n = grammar->nonTerminals; n; n = n->followingSibling)
                                                                {
                                                                  Production *p = static_cast <Production *> (n);
                                                                  if (p->isStartSymbol())
                                                                  {
                                                            #line 512 "PrintJava.cpp"
  append(L"\n");
  append(L"  public static Sequence");
                                                            #line 321 "PrintJava.cpp.template"
                                                                    if (saxon == 99)
                                                                    {
                                                            #line 518 "PrintJava.cpp"
  append(L"<?>");
                                                            #line 323 "PrintJava.cpp.template"
                                                                    }
                                                            #line 522 "PrintJava.cpp"
  append(L" parse");
                                                            #line 324 "PrintJava.cpp.template"
                                                                    WString acceptableName = Format::acceptableName<WString>(p->name);
                                                                    const wchar_t *name = acceptableName.c_str();
                                                                    wchar_t initial = towupper(*name);
                                                                    print(&initial, 1);
                                                                    print(name + 1);
                                                            #line 530 "PrintJava.cpp"
  append(L"(XPathContext context, String input) throws XPathException\n");
  append(L"  {\n");
  append(L"    Builder builder = context.getController().makeBuilder();");
                                                            #line 331 "PrintJava.cpp.template"
                                                                    if (tree & isLrParser)
                                                                    {
                                                            #line 537 "PrintJava.cpp"
  append(L"\n");
  append(L"    ParseTreeBuilder bottomUpTreeBuilder = new ParseTreeBuilder();");
                                                            #line 334 "PrintJava.cpp.template"
                                                                    }
                                                            #line 542 "PrintJava.cpp"
  append(L"\n");
  append(L"    builder.open();\n");
  append(L"    ");
                                                            #line 337 "PrintJava.cpp.template"
                                                                    print(className.c_str());
                                                            #line 548 "PrintJava.cpp"
  append(L" parser = new ");
                                                            #line 338 "PrintJava.cpp.template"
                                                                    print(className.c_str());
                                                            #line 552 "PrintJava.cpp"
  append(L"(input");
                                                            #line 339 "PrintJava.cpp.template"
                                                                    if (noLexer)
                                                                    {
                                                            #line 557 "PrintJava.cpp"
  append(L", new ");
                                                            #line 341 "PrintJava.cpp.template"
                                                                      print(className.c_str());
                                                            #line 561 "PrintJava.cpp"
  append(L"Lexer()");
                                                            #line 342 "PrintJava.cpp.template"
                                                                    }
                                                                    if (tree)
                                                                    {
                                                                      if (isLrParser)
                                                                      {
                                                            #line 569 "PrintJava.cpp"
  append(L", bottomUpTreeBuilder");
                                                            #line 347 "PrintJava.cpp.template"
                                                                      }
                                                                      else
                                                                      {
                                                            #line 575 "PrintJava.cpp"
  append(L", new SaxonTreeBuilder(builder");
                                                            #line 350 "PrintJava.cpp.template"
                                                                        printNamesArgument();
                                                            #line 579 "PrintJava.cpp"
  append(L")");
                                                            #line 351 "PrintJava.cpp.template"
                                                                      }
                                                                    }
                                                            #line 584 "PrintJava.cpp"
  append(L");\n");
  append(L"    try\n");
  append(L"    {\n");
  append(L"      parser.parse_");
                                                            #line 356 "PrintJava.cpp.template"
                                                                    print(Format::acceptableName<WString>(p->name).c_str());
                                                            #line 591 "PrintJava.cpp"
  append(L"();");
                                                            #line 357 "PrintJava.cpp.template"
                                                                    if (! tree)
                                                                    {
                                                            #line 596 "PrintJava.cpp"
  append(L"\n");
  append(L"      return EmptySequence.getInstance();");
                                                            #line 360 "PrintJava.cpp.template"
                                                                    }
                                                                    else if (isLrParser)
                                                                    {
                                                            #line 603 "PrintJava.cpp"
  append(L"\n");
  append(L"      bottomUpTreeBuilder.serialize(new SaxonTreeBuilder(builder");
                                                            #line 364 "PrintJava.cpp.template"
                                                                      printNamesArgument();
                                                            #line 608 "PrintJava.cpp"
  append(L"));");
                                                            #line 366 "PrintJava.cpp.template"
                                                                    }
                                                            #line 612 "PrintJava.cpp"
  append(L"\n");
  append(L"    }\n");
  append(L"    catch (ParseException pe)\n");
  append(L"    {\n");
  append(L"      buildError(parser, pe, builder);\n");
  append(L"    }\n");
  append(L"    return builder.getCurrentRoot();\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  public static class SaxonDefinition_");
                                                            #line 376 "PrintJava.cpp.template"
                                                                    print(Format::acceptableName<WString>(p->name).c_str());
                                                            #line 625 "PrintJava.cpp"
  append(L" extends SaxonDefinition\n");
  append(L"  {\n");
  append(L"    @Override\n");
  append(L"    public String functionName() {return \"parse-");
                                                            #line 380 "PrintJava.cpp.template"
                                                                    print(p->name);
                                                            #line 632 "PrintJava.cpp"
  append(L"\";}\n");
  append(L"    @Override\n");
  append(L"    public Sequence");
                                                            #line 383 "PrintJava.cpp.template"
                                                                    if (saxon == 99)
                                                                    {
                                                            #line 639 "PrintJava.cpp"
  append(L"<?>");
                                                            #line 385 "PrintJava.cpp.template"
                                                                    }
                                                            #line 643 "PrintJava.cpp"
  append(L" execute(XPathContext context, String input) throws XPathException\n");
  append(L"    {\n");
  append(L"      return parse");
                                                            #line 388 "PrintJava.cpp.template"
                                                                    print(&initial, 1);
                                                                    print(name + 1);
                                                            #line 650 "PrintJava.cpp"
  append(L"(context, input);\n");
  append(L"    }\n");
  append(L"  }\n");
                                                            #line 393 "PrintJava.cpp.template"
                                                                  }
                                                                }
                                                            #line 657 "PrintJava.cpp"
  append(L"\n");
  append(L"  public static abstract class SaxonDefinition extends ExtensionFunctionDefinition\n");
  append(L"  {\n");
  append(L"    abstract String functionName();\n");
  append(L"    abstract Sequence");
                                                            #line 399 "PrintJava.cpp.template"
                                                                if (saxon == 99)
                                                                {
                                                            #line 666 "PrintJava.cpp"
  append(L"<?>");
                                                            #line 401 "PrintJava.cpp.template"
                                                                }
                                                            #line 670 "PrintJava.cpp"
  append(L" execute(XPathContext context, String input) throws XPathException;\n");
  append(L"\n");
  append(L"    @Override\n");
  append(L"    public StructuredQName getFunctionQName() {return new StructuredQName(\"p\", \"");
                                                            #line 406 "PrintJava.cpp.template"
                                                                if (! packageName.empty())
                                                                {
                                                                  for (size_t i = 0; i < packageName.size(); ++i)
                                                                  {
                                                                    print(packageName[i] == L'.' ? L'/' : packageName[i]);
                                                                  }
                                                            #line 682 "PrintJava.cpp"
  append(L"/");
                                                            #line 413 "PrintJava.cpp.template"
                                                                }
                                                                print(className.c_str());
                                                            #line 687 "PrintJava.cpp"
  append(L"\", functionName());}\n");
  append(L"    @Override\n");
  append(L"    public SequenceType[] getArgumentTypes() {return new SequenceType[] {SequenceType.SINGLE_STRING};}\n");
  append(L"    @Override\n");
  append(L"    public SequenceType getResultType(SequenceType[] suppliedArgumentTypes) {return SequenceType.");
                                                            #line 420 "PrintJava.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 696 "PrintJava.cpp"
  append(L"SINGLE");
                                                            #line 423 "PrintJava.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 702 "PrintJava.cpp"
  append(L"OPTIONAL");
                                                            #line 427 "PrintJava.cpp.template"
                                                                }
                                                            #line 706 "PrintJava.cpp"
  append(L"_NODE;}\n");
  append(L"\n");
  append(L"    @Override\n");
  append(L"    public ExtensionFunctionCall makeCallExpression()\n");
  append(L"    {\n");
  append(L"      return new ExtensionFunctionCall()\n");
  append(L"      {\n");
  append(L"        @Override\n");
  append(L"        public Sequence");
                                                            #line 436 "PrintJava.cpp.template"
                                                                if (saxon == 99)
                                                                {
                                                            #line 719 "PrintJava.cpp"
  append(L"<?>");
                                                            #line 438 "PrintJava.cpp.template"
                                                                }
                                                            #line 723 "PrintJava.cpp"
  append(L" call(XPathContext context, ");
                                                            #line 439 "PrintJava.cpp.template"
                                                                if (saxon == 99)
                                                                {
                                                            #line 728 "PrintJava.cpp"
  append(L"@SuppressWarnings(\"rawtypes\") ");
                                                            #line 442 "PrintJava.cpp.template"
                                                                }
                                                            #line 732 "PrintJava.cpp"
  append(L"Sequence[] arguments) throws XPathException\n");
  append(L"        {\n");
  append(L"          return execute(context, arguments[0].iterate().next().getStringValue());\n");
  append(L"        }\n");
  append(L"      };\n");
  append(L"    }\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  private static void buildError(");
                                                            #line 451 "PrintJava.cpp.template"
                                                                print(className.c_str());
                                                            #line 744 "PrintJava.cpp"
  append(L" parser, ParseException pe, Builder builder) throws XPathException\n");
  append(L"  {\n");
  append(L"    builder.close();\n");
  append(L"    builder.reset();\n");
  append(L"    builder.open();");
                                                            #line 456 "PrintJava.cpp.template"
                                                                if (saxon == 99)
                                                                {
                                                            #line 753 "PrintJava.cpp"
  append(L"\n");
  append(L"    builder.startElement(new NoNamespaceName(\"ERROR\"), AnyType.getInstance(), LOCATION, 0);\n");
  append(L"    AnySimpleType anySimpleType = AnySimpleType.getInstance();\n");
  append(L"    builder.attribute(new NoNamespaceName(\"b\"), anySimpleType, Integer.toString(pe.getBegin() + 1), LOCATION, 0);\n");
  append(L"    builder.attribute(new NoNamespaceName(\"e\"), anySimpleType, Integer.toString(pe.getEnd() + 1), LOCATION, 0);\n");
  append(L"    if (pe.getOffending() < 0)\n");
  append(L"    {\n");
  append(L"      builder.attribute(new NoNamespaceName(\"s\"), anySimpleType, Integer.toString(pe.getState()), LOCATION, 0);\n");
  append(L"    }\n");
  append(L"    else\n");
  append(L"    {\n");
  append(L"      builder.attribute(new NoNamespaceName(\"o\"), anySimpleType, Integer.toString(pe.getOffending()), LOCATION, 0);\n");
  append(L"      builder.attribute(new NoNamespaceName(\"x\"), anySimpleType, Integer.toString(pe.getExpected()), LOCATION, 0);\n");
  append(L"    }");
                                                            #line 471 "PrintJava.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 772 "PrintJava.cpp"
  append(L"\n");
  append(L"    List<AttributeInfo> attributes = new ArrayList<>();\n");
  append(L"    AnySimpleType anySimpleType = AnySimpleType.getInstance();\n");
  append(L"    attributes.add(new AttributeInfo(new NoNamespaceName(\"b\"), anySimpleType, Integer.toString(pe.getBegin() + 1), LOCATION, 0));\n");
  append(L"    attributes.add(new AttributeInfo(new NoNamespaceName(\"e\"), anySimpleType, Integer.toString(pe.getEnd() + 1), LOCATION, 0));\n");
  append(L"    if (pe.getOffending() < 0)\n");
  append(L"    {\n");
  append(L"      attributes.add(new AttributeInfo(new NoNamespaceName(\"s\"), anySimpleType, Integer.toString(pe.getState()), LOCATION, 0));\n");
  append(L"    }\n");
  append(L"    else\n");
  append(L"    {\n");
  append(L"      attributes.add(new AttributeInfo(new NoNamespaceName(\"o\"), anySimpleType, Integer.toString(pe.getOffending()), LOCATION, 0));\n");
  append(L"      attributes.add(new AttributeInfo(new NoNamespaceName(\"x\"), anySimpleType, Integer.toString(pe.getExpected()), LOCATION, 0));\n");
  append(L"    }\n");
  append(L"    builder.startElement(new NoNamespaceName(\"ERROR\"), AnyType.getInstance(), new SmallAttributeMap(attributes), NO_NAMESPACES, LOCATION, 0);");
                                                            #line 489 "PrintJava.cpp.template"
                                                                }
                                                            #line 790 "PrintJava.cpp"
  append(L"\n");
  append(L"    builder.characters(");
                                                            #line 491 "PrintJava.cpp.template"
                                                                if (saxon == 110)
                                                                {
                                                            #line 796 "PrintJava.cpp"
  append(L"StringView.of(");
                                                            #line 493 "PrintJava.cpp.template"
                                                                }
                                                            #line 800 "PrintJava.cpp"
  append(L"parser.getErrorMessage(pe)");
                                                            #line 494 "PrintJava.cpp.template"
                                                                if (saxon == 110)
                                                                {
                                                            #line 805 "PrintJava.cpp"
  append(L")");
                                                            #line 496 "PrintJava.cpp.template"
                                                                }
                                                            #line 809 "PrintJava.cpp"
  append(L", LOCATION, 0);");
                                                            #line 498 "PrintJava.cpp.template"
                                                                if (tree && useGlr)
                                                                {
                                                            #line 814 "PrintJava.cpp"
  append(L"\n");
  append(L"    if (pe.isAmbiguousInput())\n");
  append(L"    {\n");
  append(L"      pe.serialize(new SaxonTreeBuilder(builder");
                                                            #line 503 "PrintJava.cpp.template"
                                                                  printNamesArgument();
                                                            #line 821 "PrintJava.cpp"
  append(L"));\n");
  append(L"    }");
                                                            #line 505 "PrintJava.cpp.template"
                                                                }
                                                            #line 826 "PrintJava.cpp"
  append(L"\n");
  append(L"    builder.endElement();\n");
  append(L"  }\n");
                                                            #line 509 "PrintJava.cpp.template"
                                                              }
                                                              if (grammar->basex)
                                                              {
                                                                for (Node *n = grammar->nonTerminals; n; n = n->followingSibling)
                                                                {
                                                                  Production *p = static_cast <Production *> (n);
                                                                  if (p->isStartSymbol())
                                                                  {
                                                            #line 839 "PrintJava.cpp"
  append(L"\n");
  append(L"  public static XNode parse");
                                                            #line 518 "PrintJava.cpp.template"
                                                                    WString acceptableName = Format::acceptableName<WString>(p->name).c_str();
                                                                    const wchar_t *name = acceptableName.c_str();
                                                                    wchar_t initial = towupper(*name);
                                                                    print(&initial, 1);
                                                                    print(name + 1);
                                                            #line 848 "PrintJava.cpp"
  append(L"(Str str) throws IOException\n");
  append(L"  {\n");
  append(L"    BaseXFunction baseXFunction = new BaseXFunction()\n");
  append(L"    {\n");
  append(L"      @Override\n");
  append(L"      public void execute(");
                                                            #line 528 "PrintJava.cpp.template"
                                                                    print(className.c_str());
                                                            #line 857 "PrintJava.cpp"
  append(L" p) {p.parse_");
                                                            #line 529 "PrintJava.cpp.template"
                                                                    print(Format::acceptableName<WString>(p->name).c_str());
                                                            #line 861 "PrintJava.cpp"
  append(L"();}\n");
  append(L"    };\n");
  append(L"    return baseXFunction.call(str);\n");
  append(L"  }\n");
                                                            #line 534 "PrintJava.cpp.template"
                                                                  }
                                                                }
                                                            #line 869 "PrintJava.cpp"
  append(L"\n");
  append(L"  public static abstract class BaseXFunction\n");
  append(L"  {\n");
  append(L"    private static final MainOptions OPTIONS = new MainOptions();\n");
  append(L"    protected abstract void execute(");
                                                            #line 540 "PrintJava.cpp.template"
                                                                print(className.c_str());
                                                            #line 877 "PrintJava.cpp"
  append(L" p);\n");
  append(L"\n");
  append(L"    public XNode call(Str str) throws IOException\n");
  append(L"    {\n");
  append(L"      String input = str.toJava();\n");
  append(L"      Parser emptyParser = Parser.emptyParser(OPTIONS);\n");
  append(L"      MemBuilder memBuilder = new MemBuilder(input, emptyParser).init();");
                                                            #line 548 "PrintJava.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 888 "PrintJava.cpp"
  append(L"\n");
  append(L"      BaseXTreeBuilder treeBuilder = new BaseXTreeBuilder(memBuilder");
                                                            #line 552 "PrintJava.cpp.template"
                                                                  printNamesArgument();
                                                            #line 893 "PrintJava.cpp"
  append(L");");
                                                            #line 553 "PrintJava.cpp.template"
                                                                  if (isLrParser)
                                                                  {
                                                            #line 898 "PrintJava.cpp"
  append(L"\n");
  append(L"      ParseTreeBuilder bottomUpTreeBuilder = new ParseTreeBuilder();");
                                                            #line 557 "PrintJava.cpp.template"
                                                                  }
                                                                }
                                                            #line 904 "PrintJava.cpp"
  append(L"\n");
  append(L"      ");
                                                            #line 560 "PrintJava.cpp.template"
                                                                print(className.c_str());
                                                            #line 909 "PrintJava.cpp"
  append(L" parser = new ");
                                                            #line 561 "PrintJava.cpp.template"
                                                                print(className.c_str());
                                                            #line 913 "PrintJava.cpp"
  append(L"();\n");
  append(L"      parser.initialize(input");
                                                            #line 563 "PrintJava.cpp.template"
                                                                if (noLexer)
                                                                {
                                                            #line 919 "PrintJava.cpp"
  append(L", new ");
                                                            #line 565 "PrintJava.cpp.template"
                                                                  print(className.c_str());
                                                            #line 923 "PrintJava.cpp"
  append(L"Lexer()");
                                                            #line 566 "PrintJava.cpp.template"
                                                                }
                                                                if (tree)
                                                                {
                                                                  if (isLrParser)
                                                                  {
                                                            #line 931 "PrintJava.cpp"
  append(L", bottomUpTreeBuilder");
                                                            #line 571 "PrintJava.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 937 "PrintJava.cpp"
  append(L", treeBuilder");
                                                            #line 574 "PrintJava.cpp.template"
                                                                  }
                                                                }
                                                            #line 942 "PrintJava.cpp"
  append(L");\n");
  append(L"      try\n");
  append(L"      {\n");
  append(L"        execute(parser);");
                                                            #line 579 "PrintJava.cpp.template"
                                                                if (tree)
                                                                {
                                                                  if (isLrParser)
                                                                  {
                                                            #line 952 "PrintJava.cpp"
  append(L"\n");
  append(L"        bottomUpTreeBuilder.serialize(treeBuilder);");
                                                            #line 584 "PrintJava.cpp.template"
                                                                  }
                                                                }
                                                                else
                                                                {
                                                            #line 960 "PrintJava.cpp"
  append(L"\n");
  append(L"        return null;");
                                                            #line 589 "PrintJava.cpp.template"
                                                                }
                                                            #line 965 "PrintJava.cpp"
  append(L"\n");
  append(L"      }\n");
  append(L"      catch (ParseException pe)\n");
  append(L"      {\n");
  append(L"        memBuilder = new MemBuilder(input, emptyParser).init();\n");
  append(L"        Atts atts = new Atts();\n");
  append(L"        atts.add(Token.token(\"b\"), Token.token(pe.getBegin() + 1));\n");
  append(L"        atts.add(Token.token(\"e\"), Token.token(pe.getEnd() + 1));\n");
  append(L"        if (pe.getOffending() < 0)\n");
  append(L"        {\n");
  append(L"          atts.add(Token.token(\"s\"), Token.token(pe.getState()));\n");
  append(L"        }\n");
  append(L"        else\n");
  append(L"        {\n");
  append(L"          atts.add(Token.token(\"o\"), Token.token(pe.getOffending()));\n");
  append(L"          atts.add(Token.token(\"x\"), Token.token(pe.getExpected()));\n");
  append(L"        }\n");
  append(L"        memBuilder.openElem(Token.token(\"ERROR\"), atts, new Atts());\n");
  append(L"        memBuilder.text(Token.token(parser.getErrorMessage(pe)));");
                                                            #line 609 "PrintJava.cpp.template"
                                                                if (tree && useGlr)
                                                                {
                                                            #line 988 "PrintJava.cpp"
  append(L"\n");
  append(L"        if (pe.isAmbiguousInput())\n");
  append(L"        {\n");
  append(L"          pe.serialize(new BaseXTreeBuilder(memBuilder");
                                                            #line 614 "PrintJava.cpp.template"
                                                                  printNamesArgument();
                                                            #line 995 "PrintJava.cpp"
  append(L"));\n");
  append(L"        }");
                                                            #line 616 "PrintJava.cpp.template"
                                                                }
                                                            #line 1000 "PrintJava.cpp"
  append(L"\n");
  append(L"        memBuilder.closeElem();\n");
  append(L"      }\n");
  append(L"      catch (RuntimeException e)\n");
  append(L"      {\n");
  append(L"        if (e.getCause() instanceof IOException) throw (IOException) e.getCause();\n");
  append(L"        throw e;\n");
  append(L"      }\n");
  append(L"      return new DBNode(memBuilder.data());\n");
  append(L"    }\n");
  append(L"  }\n");
                                                            #line 628 "PrintJava.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 1015 "PrintJava.cpp"
  append(L"\n");
  append(L"  public static class BaseXTreeBuilder implements EventHandler\n");
  append(L"  {\n");
  append(L"    private ");
                                                            #line 633 "PrintJava.cpp.template"
                                                                  print(inputType());
                                                            #line 1022 "PrintJava.cpp"
  append(L" input;\n");
  append(L"    private MemBuilder builder;\n");
  append(L"    private Atts nsp = new Atts();\n");
  append(L"    private Atts atts = new Atts();");
                                                            #line 637 "PrintJava.cpp.template"
                                                                  printNameSupport();
                                                            #line 1029 "PrintJava.cpp"
  append(L"\n");
  append(L"\n");
  append(L"    public BaseXTreeBuilder(MemBuilder b");
                                                            #line 640 "PrintJava.cpp.template"
                                                                  if (! interfaceName.empty())
                                                                  {
                                                            #line 1036 "PrintJava.cpp"
  append(L", ");
                                                            #line 642 "PrintJava.cpp.template"
                                                                    print(className.c_str());
                                                            #line 1040 "PrintJava.cpp"
  append(L" names");
                                                            #line 643 "PrintJava.cpp.template"
                                                                  }
                                                            #line 1044 "PrintJava.cpp"
  append(L")\n");
  append(L"    {");
                                                            #line 645 "PrintJava.cpp.template"
                                                                  if (! interfaceName.empty())
                                                                  {
                                                            #line 1050 "PrintJava.cpp"
  append(L"\n");
  append(L"      this.names = names;");
                                                            #line 648 "PrintJava.cpp.template"
                                                                  }
                                                            #line 1055 "PrintJava.cpp"
  append(L"\n");
  append(L"      input = null;\n");
  append(L"      builder = b;\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    @Override\n");
  append(L"    public void reset(");
                                                            #line 655 "PrintJava.cpp.template"
                                                                  print(inputType());
                                                            #line 1065 "PrintJava.cpp"
  append(L" string)\n");
  append(L"    {\n");
  append(L"      input = string;\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    @Override\n");
  append(L"    public void startNonterminal(int id, int begin)\n");
  append(L"    {\n");
  append(L"      startElement(");
                                                            #line 664 "PrintJava.cpp.template"
                                                                  printNamesPrefix();
                                                            #line 1077 "PrintJava.cpp"
  append(L"getNonterminalName(id));\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    private void startElement(String name)\n");
  append(L"    {\n");
  append(L"      try\n");
  append(L"      {\n");
  append(L"        builder.openElem(Token.token(name), atts, nsp);\n");
  append(L"      }\n");
  append(L"      catch (IOException e)\n");
  append(L"      {\n");
  append(L"        throw new RuntimeException(e);\n");
  append(L"      }\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    @Override\n");
  append(L"    public void endNonterminal(int id, int end)\n");
  append(L"    {\n");
  append(L"      endElement();\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    private void endElement()\n");
  append(L"    {\n");
  append(L"      try\n");
  append(L"      {\n");
  append(L"        builder.closeElem();\n");
  append(L"      }\n");
  append(L"      catch (IOException e)\n");
  append(L"      {\n");
  append(L"        throw new RuntimeException(e);\n");
  append(L"      }\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    @Override\n");
  append(L"    public void terminal(int id, int begin, int end)\n");
  append(L"    {\n");
  append(L"      String name = ");
                                                            #line 701 "PrintJava.cpp.template"
                                                                  printNamesPrefix();
                                                            #line 1117 "PrintJava.cpp"
  append(L"getTerminalName(id);\n");
  append(L"      if (name.charAt(0) == '\\'')\n");
  append(L"      {\n");
  append(L"        name = \"TOKEN\";\n");
  append(L"      }\n");
  append(L"      startElement(name);\n");
  append(L"      characters(begin, end);\n");
  append(L"      endElement();\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    @Override\n");
  append(L"    public void whitespace(int begin, int end)\n");
  append(L"    {\n");
  append(L"      characters(begin, end);\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    private void characters(int begin, int end)\n");
  append(L"    {\n");
  append(L"      if (begin < end)\n");
  append(L"      {\n");
  append(L"        try\n");
  append(L"        {\n");
  append(L"          builder.text(Token.token(");
                                                            #line 724 "PrintJava.cpp.template"
                                                                  print(substring());
                                                            #line 1143 "PrintJava.cpp"
  append(L"));\n");
  append(L"        }\n");
  append(L"        catch (IOException e)\n");
  append(L"        {\n");
  append(L"          throw new RuntimeException(e);\n");
  append(L"        }\n");
  append(L"      }\n");
  append(L"    }\n");
  append(L"  }\n");
                                                            #line 734 "PrintJava.cpp.template"
                                                                }
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
                                                                if (grammar->basex)
                                                                {
                                                                  increaseIndent();
                                                                  openMethod(L"", L"", className.c_str(), L"");
                                                            #line 1170 "PrintJava.cpp"
  append(L"\n");
  append(L"{\n");
  append(L"}\n");
                                                            #line 753 "PrintJava.cpp.template"
                                                                  decreaseIndent();
                                                                }
                                                                WString tail;
                                                                if (noLexer) tail += L", Lexer lexer";
                                                                if (tree) tail += isLrParser ? L", BottomUpEventHandler t" : L", EventHandler t";
                                                                increaseIndent();
                                                                if (codepoints)
                                                                {
                                                                  WString args(L"int[] codepoints");
                                                                  args += tail;
                                                                  openMethod(L"", L"", className.c_str(), args.c_str());
                                                            #line 1186 "PrintJava.cpp"
  append(L"\n");
  append(L"{\n");
  append(L"  initialize(codepoints");
                                                            #line 766 "PrintJava.cpp.template"
                                                                  if (tree)
                                                                  {
                                                            #line 1193 "PrintJava.cpp"
  append(L", t");
                                                            #line 768 "PrintJava.cpp.template"
                                                                  }
                                                            #line 1197 "PrintJava.cpp"
  append(L");\n");
  append(L"}\n");
                                                            #line 771 "PrintJava.cpp.template"
                                                                }
                                                                WString args(L"CharSequence string");
                                                                args += tail;
                                                                openMethod(L"", L"", className.c_str(), args.c_str());
                                                            #line 1205 "PrintJava.cpp"
  append(L"\n");
  append(L"{\n");
  append(L"  initialize(string");
                                                            #line 777 "PrintJava.cpp.template"
                                                                if (noLexer)
                                                                {
                                                            #line 1212 "PrintJava.cpp"
  append(L", lexer");
                                                            #line 779 "PrintJava.cpp.template"
                                                                }
                                                                if (tree)
                                                                {
                                                            #line 1218 "PrintJava.cpp"
  append(L", t");
                                                            #line 782 "PrintJava.cpp.template"
                                                                }
                                                            #line 1222 "PrintJava.cpp"
  append(L");\n");
  append(L"}\n");
                                                            #line 785 "PrintJava.cpp.template"
                                                                decreaseIndent();
                                                              }
                                                            }

                                                            void PrintJava::openStackNode()
                                                            {
                                                            #line 1232 "PrintJava.cpp"
  append(L"\n");
  append(L"private static class StackNode\n");
  append(L"{\n");
  append(L"  public int state;");
                                                            #line 794 "PrintJava.cpp.template"
                                                              if (grammar->states->hasLookback)
                                                              {
                                                            #line 1240 "PrintJava.cpp"
  append(L"\n");
  append(L"  public int code;");
                                                            #line 797 "PrintJava.cpp.template"
                                                              }
                                                              if (tree || useGlr)
                                                              {
                                                            #line 1247 "PrintJava.cpp"
  append(L"\n");
  append(L"  public int pos;");
                                                            #line 801 "PrintJava.cpp.template"
                                                              }
                                                            #line 1252 "PrintJava.cpp"
  append(L"\n");
  append(L"  public StackNode link;\n");
  append(L"\n");
  append(L"  public StackNode(int state, ");
                                                            #line 805 "PrintJava.cpp.template"
                                                              if (grammar->states->hasLookback)
                                                              {
                                                            #line 1260 "PrintJava.cpp"
  append(L"int code, ");
                                                            #line 807 "PrintJava.cpp.template"
                                                              }
                                                              if (tree || useGlr)
                                                              {
                                                            #line 1266 "PrintJava.cpp"
  append(L"int pos, ");
                                                            #line 810 "PrintJava.cpp.template"
                                                              }
                                                            #line 1270 "PrintJava.cpp"
  append(L"StackNode link)\n");
  append(L"  {\n");
  append(L"    this.state = state;");
                                                            #line 813 "PrintJava.cpp.template"
                                                              if (grammar->states->hasLookback)
                                                              {
                                                            #line 1277 "PrintJava.cpp"
  append(L"\n");
  append(L"    this.code = code;");
                                                            #line 816 "PrintJava.cpp.template"
                                                              }
                                                              if (tree || useGlr)
                                                              {
                                                            #line 1284 "PrintJava.cpp"
  append(L"\n");
  append(L"    this.pos = pos;");
                                                            #line 820 "PrintJava.cpp.template"
                                                              }
                                                            #line 1289 "PrintJava.cpp"
  append(L"\n");
  append(L"    this.link = link;\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  @Override\n");
  append(L"  public boolean equals(Object obj)\n");
  append(L"  {\n");
  append(L"    StackNode lhs = this;\n");
  append(L"    StackNode rhs = (StackNode) obj;\n");
  append(L"    while (lhs != null && rhs != null)\n");
  append(L"    {\n");
  append(L"      if (lhs == rhs) return true;\n");
  append(L"      if (lhs.state != rhs.state) return false;");
                                                            #line 833 "PrintJava.cpp.template"
                                                              if (grammar->states->hasLookback)
                                                              {
                                                            #line 1306 "PrintJava.cpp"
  append(L"\n");
  append(L"      if (lhs.code != rhs.code) return false;");
                                                            #line 836 "PrintJava.cpp.template"
                                                              }
                                                              if (tree || useGlr)
                                                              {
                                                            #line 1313 "PrintJava.cpp"
  append(L"\n");
  append(L"      if (lhs.pos != rhs.pos) return false;");
                                                            #line 840 "PrintJava.cpp.template"
                                                              }
                                                            #line 1318 "PrintJava.cpp"
  append(L"\n");
  append(L"      lhs = lhs.link;\n");
  append(L"      rhs = rhs.link;\n");
  append(L"    }\n");
  append(L"    return lhs == rhs;\n");
  append(L"  }\n");
                                                            #line 847 "PrintJava.cpp.template"
                                                              increaseIndent();
                                                              beginPublic();
                                                            }

                                                            void PrintJava::closeStackNode()
                                                            {
                                                              beginNonpublic();
                                                              decreaseIndent();
                                                            #line 1334 "PrintJava.cpp"
  append(L"\n");
  append(L"}\n");
                                                            #line 857 "PrintJava.cpp.template"
                                                              if (hasCustomCode)
                                                              {
                                                            #line 1340 "PrintJava.cpp"
  append(L"\n");
  append(L"private static class DeferredCode\n");
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
                                                            #line 875 "PrintJava.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                            #line 1361 "PrintJava.cpp"
  append(L"\n");
  append(L"private abstract static class DeferredEvent\n");
  append(L"{\n");
  append(L"  public DeferredEvent link;\n");
  append(L"  public int id;\n");
  append(L"  public int begin;\n");
  append(L"  public int end;");
                                                            #line 884 "PrintJava.cpp.template"
                                                                if (shiftAmbiguity)
                                                                {
                                                            #line 1372 "PrintJava.cpp"
  append(L"\n");
  append(L"  public int depth;");
                                                            #line 887 "PrintJava.cpp.template"
                                                                }
                                                            #line 1377 "PrintJava.cpp"
  append(L"\n");
  append(L"\n");
  append(L"  public DeferredEvent(DeferredEvent link, int id, int begin, int end)\n");
  append(L"  {\n");
  append(L"    this.link = link;\n");
  append(L"    this.id = id;\n");
  append(L"    this.begin = begin;\n");
  append(L"    this.end = end;");
                                                            #line 895 "PrintJava.cpp.template"
                                                                if (shiftAmbiguity)
                                                                {
                                                            #line 1389 "PrintJava.cpp"
  append(L"\n");
  append(L"    this.depth = link == null ? 1 : link.depth + 1;");
                                                            #line 898 "PrintJava.cpp.template"
                                                                }
                                                            #line 1394 "PrintJava.cpp"
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
                                                            #line 918 "PrintJava.cpp.template"
                                                                if (shiftAmbiguity)
                                                                {
                                                            #line 1418 "PrintJava.cpp"
  append(L"if (eventHandler != null)\n");
  append(L"        ");
                                                            #line 921 "PrintJava.cpp.template"
                                                                }
                                                            #line 1423 "PrintJava.cpp"
  append(L"current.execute(eventHandler);\n");
  append(L"      current = current.link;\n");
  append(L"    }\n");
  append(L"    while (current != null);\n");
  append(L"  }\n");
  append(L"\n");
                                                            #line 928 "PrintJava.cpp.template"
                                                                if (rejectsAmbiguity())
                                                                {
                                                            #line 1433 "PrintJava.cpp"
  append(L"  public void show(BottomUpEventHandler eventHandler)\n");
  append(L"  {\n");
  append(L"    java.util.Stack<DeferredEvent> stack = new java.util.Stack<>();\n");
  append(L"    for (DeferredEvent current = this; current != null; current = current.link)\n");
  append(L"    {\n");
  append(L"      stack.push(current);\n");
  append(L"    }\n");
  append(L"    while (! stack.isEmpty())\n");
  append(L"    {\n");
  append(L"      stack.pop().execute(eventHandler);\n");
  append(L"    }\n");
  append(L"  }\n");
                                                            #line 942 "PrintJava.cpp.template"
                                                                }
                                                            #line 1448 "PrintJava.cpp"
  append(L"}\n");
  append(L"\n");
                                                            #line 945 "PrintJava.cpp.template"
                                                                if (resolvesAmbiguity)
                                                                {
                                                            #line 1454 "PrintJava.cpp"
  append(L"public static class AmbiguityEvent extends DeferredEvent\n");
  append(L"{\n");
  append(L"  public AmbiguityEvent(DeferredEvent link, int begin, int end)\n");
  append(L"  {\n");
  append(L"    super(link, -1, begin, end);\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  @Override\n");
  append(L"  public void execute(BottomUpEventHandler eventHandler)\n");
  append(L"  {\n");
  append(L"    eventHandler.ambiguity(begin, end);\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  @Override\n");
  append(L"  public String toString()\n");
  append(L"  {\n");
  append(L"    return \"ambiguity(\" + begin + \", \" + end + \")\";\n");
  append(L"  }\n");
  append(L"}\n");
  append(L"\n");
                                                            #line 967 "PrintJava.cpp.template"
                                                                }
                                                            #line 1477 "PrintJava.cpp"
  append(L"public static class TerminalEvent extends DeferredEvent\n");
  append(L"{\n");
  append(L"  public TerminalEvent(DeferredEvent link, int id, int begin, int end)\n");
  append(L"  {\n");
  append(L"    super(link, id, begin, end);\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  @Override\n");
  append(L"  public void execute(BottomUpEventHandler eventHandler)\n");
  append(L"  {\n");
  append(L"    eventHandler.terminal(id, begin, end);\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  @Override\n");
  append(L"  public String toString()\n");
  append(L"  {\n");
  append(L"    return \"terminal(\" + TOKEN[id] + \", \" + begin + \", \" + end + \")\";\n");
  append(L"  }\n");
  append(L"}\n");
  append(L"\n");
  append(L"public static class NonterminalEvent extends DeferredEvent\n");
  append(L"{\n");
  append(L"  public int count;\n");
  append(L"\n");
  append(L"  public NonterminalEvent(DeferredEvent link, int id, int begin, int end, int count)\n");
  append(L"  {\n");
  append(L"    super(link, id, begin, end);\n");
  append(L"    this.count = count;\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  @Override\n");
  append(L"  public void execute(BottomUpEventHandler eventHandler)\n");
  append(L"  {\n");
  append(L"    eventHandler.nonterminal(id, begin, end, count);\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  @Override\n");
  append(L"  public String toString()\n");
  append(L"  {\n");
  append(L"    return \"nonterminal(\" + ");
                                                            #line 1007 "PrintJava.cpp.template"
                                                                printSyntheticNamePrefix(true);
                                                            #line 1520 "PrintJava.cpp"
  append(L"NONTERMINAL[id]");
                                                            #line 1008 "PrintJava.cpp.template"
                                                                printSyntheticNameSuffix(true);
                                                            #line 1524 "PrintJava.cpp"
  append(L" + \", \" + begin + \", \" + end + \", \" + count + \")\";\n");
  append(L"  }\n");
  append(L"}\n");
                                                            #line 1012 "PrintJava.cpp.template"
                                                              }
                                                            #line 1530 "PrintJava.cpp"
  append(L"\n");
  append(L"private static final int PARSING = 0;\n");
  append(L"private static final int ACCEPTED = 1;\n");
  append(L"private static final int ERROR = 2;\n");
  append(L"\n");
  append(L"private ParsingThread parse(int target, int initialState, ");
                                                            #line 1018 "PrintJava.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 1540 "PrintJava.cpp"
  append(L"BottomUpEventHandler eventHandler, ");
                                                            #line 1021 "PrintJava.cpp.template"
                                                              }
                                                            #line 1544 "PrintJava.cpp"
  append(L"ParsingThread thread)\n");
  append(L"{\n");
  append(L"  PriorityQueue<ParsingThread> threads = thread.open(initialState");
                                                            #line 1025 "PrintJava.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 1551 "PrintJava.cpp"
  append(L", eventHandler");
                                                            #line 1027 "PrintJava.cpp.template"
                                                              }
                                                            #line 1555 "PrintJava.cpp"
  append(L", target);\n");
  append(L"  for (;;)\n");
  append(L"  {\n");
  append(L"    thread = threads.poll();\n");
  append(L"    if (thread.accepted)\n");
  append(L"    {");
                                                            #line 1033 "PrintJava.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 1565 "PrintJava.cpp"
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
                                                            #line 1048 "PrintJava.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 1583 "PrintJava.cpp"
  append(L", thread.deferredEvent, other.deferredEvent");
                                                            #line 1051 "PrintJava.cpp.template"
                                                                }
                                                            #line 1587 "PrintJava.cpp"
  append(L");\n");
  append(L"      }");
                                                            #line 1053 "PrintJava.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 1594 "PrintJava.cpp"
  append(L"\n");
  append(L"      while (! threads.isEmpty())\n");
  append(L"      {\n");
  append(L"        ParsingThread other = threads.poll();\n");
  append(L"        thread = thread.e0 < other.e0 ? other : resolve(thread, other);\n");
  append(L"      }");
                                                            #line 1061 "PrintJava.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                            #line 1605 "PrintJava.cpp"
  append(L"\n");
  append(L"      if (thread.deferredEvent != null)\n");
  append(L"      {\n");
  append(L"        thread.deferredEvent.release(eventHandler);\n");
  append(L"        thread.deferredEvent = null;\n");
  append(L"      }");
                                                            #line 1069 "PrintJava.cpp.template"
                                                              }
                                                              if (hasCustomCode)
                                                              {
                                                            #line 1616 "PrintJava.cpp"
  append(L"\n");
  append(L"      thread.executeDeferredCode();");
                                                            #line 1073 "PrintJava.cpp.template"
                                                              }
                                                            #line 1621 "PrintJava.cpp"
  append(L"\n");
  append(L"      return thread;\n");
  append(L"    }\n");
  append(L"\n");
                                                            #line 1078 "PrintJava.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 1629 "PrintJava.cpp"
  append(L"    if (! threads.isEmpty())\n");
  append(L"    {\n");
  append(L"      if (threads.peek().equals(thread))\n");
  append(L"      {\n");
  append(L"        rejectAmbiguity(thread.stack.pos, thread.e0");
                                                            #line 1084 "PrintJava.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 1638 "PrintJava.cpp"
  append(L", thread.deferredEvent, threads.peek().deferredEvent");
                                                            #line 1087 "PrintJava.cpp.template"
                                                                }
                                                            #line 1642 "PrintJava.cpp"
  append(L");\n");
  append(L"      }\n");
  append(L"    }");
                                                            #line 1090 "PrintJava.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 1650 "PrintJava.cpp"
  append(L"    while (! threads.isEmpty() && threads.peek().equals(thread))\n");
  append(L"    {\n");
  append(L"      thread = resolve(thread, threads.poll());\n");
  append(L"    }");
                                                            #line 1096 "PrintJava.cpp.template"
                                                              }
                                                              if (tree || hasCustomCode)
                                                              {
                                                                if (rejectsAmbiguity())
                                                                {
                                                            #line 1661 "PrintJava.cpp"
  append(L"\n");
  append(L"    else\n");
  append(L"    {");
                                                            #line 1103 "PrintJava.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1669 "PrintJava.cpp"
  append(L"\n");
  append(L"    if (threads.isEmpty())\n");
  append(L"    {");
                                                            #line 1108 "PrintJava.cpp.template"
                                                                }
                                                                if (tree)
                                                                {
                                                            #line 1677 "PrintJava.cpp"
  append(L"\n");
  append(L"      if (thread.deferredEvent != null)\n");
  append(L"      {\n");
  append(L"        thread.deferredEvent.release(eventHandler);\n");
  append(L"        thread.deferredEvent = null;\n");
  append(L"      }");
                                                            #line 1116 "PrintJava.cpp.template"
                                                                }
                                                                if (hasCustomCode)
                                                                {
                                                            #line 1688 "PrintJava.cpp"
  append(L"\n");
  append(L"      thread.executeDeferredCode();");
                                                            #line 1120 "PrintJava.cpp.template"
                                                                }
                                                            #line 1693 "PrintJava.cpp"
  append(L"\n");
  append(L"    }");
                                                            #line 1122 "PrintJava.cpp.template"
                                                              }
                                                            #line 1698 "PrintJava.cpp"
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
                                                            #line 1147 "PrintJava.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 1726 "PrintJava.cpp"
  append(L"\n");
  append(L"private void rejectAmbiguity(int begin, int end");
                                                            #line 1150 "PrintJava.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 1732 "PrintJava.cpp"
  append(L", DeferredEvent first, DeferredEvent second");
                                                            #line 1153 "PrintJava.cpp.template"
                                                                }
                                                            #line 1736 "PrintJava.cpp"
  append(L")\n");
  append(L"{");
                                                            #line 1155 "PrintJava.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 1742 "PrintJava.cpp"
  append(L"\n");
  append(L"  ParseTreeBuilder treeBuilder = new ParseTreeBuilder();\n");
  append(L"  treeBuilder.reset(input);\n");
  append(L"  second.show(treeBuilder);\n");
  append(L"  treeBuilder.nonterminal(");
                                                            #line 1161 "PrintJava.cpp.template"
                                                                  print(format.toString<wchar_t>(Grammar::syntheticNonterminalCode(0)));
                                                            #line 1750 "PrintJava.cpp"
  append(L", treeBuilder.stack[0].begin, treeBuilder.stack[treeBuilder.top].end, treeBuilder.top + 1);\n");
  append(L"  Symbol secondTree = treeBuilder.pop(1)[0];\n");
  append(L"  first.show(treeBuilder);\n");
  append(L"  treeBuilder.nonterminal(");
                                                            #line 1165 "PrintJava.cpp.template"
                                                                  print(format.toString<wchar_t>(Grammar::syntheticNonterminalCode(0)));
                                                            #line 1757 "PrintJava.cpp"
  append(L", treeBuilder.stack[0].begin, treeBuilder.stack[treeBuilder.top].end, treeBuilder.top + 1);\n");
  append(L"  treeBuilder.push(secondTree);\n");
  append(L"  treeBuilder.nonterminal(");
                                                            #line 1168 "PrintJava.cpp.template"
                                                                  print(format.toString<wchar_t>(Grammar::syntheticNonterminalCode(1)));
                                                            #line 1763 "PrintJava.cpp"
  append(L", treeBuilder.stack[0].begin, treeBuilder.stack[treeBuilder.top].end, 2);");
                                                            #line 1170 "PrintJava.cpp.template"
                                                                }
                                                            #line 1767 "PrintJava.cpp"
  append(L"\n");
  append(L"  throw new ParseException(begin, end");
                                                            #line 1172 "PrintJava.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 1773 "PrintJava.cpp"
  append(L", treeBuilder");
                                                            #line 1174 "PrintJava.cpp.template"
                                                                }
                                                            #line 1777 "PrintJava.cpp"
  append(L");\n");
  append(L"}");
                                                            #line 1176 "PrintJava.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 1784 "PrintJava.cpp"
  append(L"\n");
  append(L"private ParsingThread resolve(ParsingThread thread, ParsingThread other)\n");
  append(L"{");
                                                            #line 1181 "PrintJava.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 1791 "PrintJava.cpp"
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
                                                            #line 1192 "PrintJava.cpp.template"
                                                                }
                                                            #line 1804 "PrintJava.cpp"
  append(L"\n");
                                                            #line 1194 "PrintJava.cpp.template"
                                                                if (shiftAmbiguity)
                                                                {
                                                            #line 1809 "PrintJava.cpp"
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
  append(L"  if ((ua instanceof TerminalEvent) != (ub instanceof TerminalEvent))\n");
  append(L"  {\n");
  append(L"    if (ub instanceof TerminalEvent)\n");
  append(L"      thread = other;\n");
  append(L"  }\n");
  append(L"  else if (other.eventCount < thread.eventCount)\n");
  append(L"    thread = other;");
                                                            #line 1220 "PrintJava.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1839 "PrintJava.cpp"
  append(L"\n");
  append(L"  if (other.eventCount < thread.eventCount)\n");
  append(L"    thread = other;");
                                                            #line 1225 "PrintJava.cpp.template"
                                                                }
                                                                if (tree)
                                                                {
                                                            #line 1847 "PrintJava.cpp"
  append(L"\n");
  append(L"  thread.addAmbiguity(begin, thread.e0);");
                                                            #line 1229 "PrintJava.cpp.template"
                                                                }
                                                            #line 1852 "PrintJava.cpp"
  append(L"\n");
  append(L"  return thread;\n");
  append(L"}");
                                                            #line 1232 "PrintJava.cpp.template"
                                                              }
                                                            #line 1858 "PrintJava.cpp"
  append(L"\n");
  append(L"\n");
  append(L"private ParsingThread thread = new ParsingThread();");
                                                            #line 1235 "PrintJava.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 1865 "PrintJava.cpp"
  append(L"\n");
  append(L"private BottomUpEventHandler eventHandler;");
                                                            #line 1238 "PrintJava.cpp.template"
                                                              }
                                                            #line 1870 "PrintJava.cpp"
  append(L"\n");
  append(L"private ");
                                                            #line 1240 "PrintJava.cpp.template"
                                                              print(inputType());
                                                            #line 1875 "PrintJava.cpp"
  append(L" input = null;");
                                                            #line 1241 "PrintJava.cpp.template"
                                                              if (noLexer)
                                                              {
                                                            #line 1880 "PrintJava.cpp"
  append(L"\n");
  append(L"private Lexer lexer = null;");
                                                            #line 1244 "PrintJava.cpp.template"
                                                              }
                                                            #line 1885 "PrintJava.cpp"
  append(L"\n");
  append(L"private int size = 0;\n");
  append(L"private int maxId = 0;");
                                                            #line 1247 "PrintJava.cpp.template"
                                                              if (trace)
                                                              {
                                                            #line 1892 "PrintJava.cpp"
  append(L"\n");
  append(L"private Writer err;\n");
  append(L"{\n");
  append(L"  try\n");
  append(L"  {\n");
  append(L"    err = new OutputStreamWriter(System.err, \"UTF-8\");\n");
  append(L"  }\n");
  append(L"  catch (UnsupportedEncodingException uee)\n");
  append(L"  {}\n");
  append(L"}");
                                                            #line 1258 "PrintJava.cpp.template"
                                                              }
                                                            #line 1905 "PrintJava.cpp"
  append(L"\n");
                                                            #line 1260 "PrintJava.cpp.template"
                                                            }

                                                            void PrintJava::openThread()
                                                            {
                                                            #line 1912 "PrintJava.cpp"
  append(L"\n");
  append(L"private class ParsingThread implements Comparable<ParsingThread>\n");
  append(L"{\n");
  append(L"  public PriorityQueue<ParsingThread> threads;\n");
  append(L"  public boolean accepted;\n");
  append(L"  public StackNode stack;\n");
  append(L"  public int state;\n");
  append(L"  public int action;\n");
  append(L"  public int target;");
                                                            #line 1272 "PrintJava.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 1925 "PrintJava.cpp"
  append(L"\n");
  append(L"  public DeferredEvent deferredEvent;");
                                                            #line 1275 "PrintJava.cpp.template"
                                                              }
                                                              if (hasCustomCode)
                                                              {
                                                            #line 1932 "PrintJava.cpp"
  append(L"\n");
  append(L"  public DeferredCode deferredCode;");
                                                            #line 1279 "PrintJava.cpp.template"
                                                              }
                                                            #line 1937 "PrintJava.cpp"
  append(L"\n");
  append(L"  public int id;");
                                                            #line 1281 "PrintJava.cpp.template"
                                                              if (resolvesAmbiguity)
                                                              {
                                                            #line 1943 "PrintJava.cpp"
  append(L"\n");
  append(L"  public int eventCount;");
                                                            #line 1284 "PrintJava.cpp.template"
                                                              }
                                                            #line 1948 "PrintJava.cpp"
  append(L"\n");
  append(L"\n");
  append(L"  public PriorityQueue<ParsingThread> open(int initialState");
                                                            #line 1287 "PrintJava.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 1955 "PrintJava.cpp"
  append(L", BottomUpEventHandler eh");
                                                            #line 1289 "PrintJava.cpp.template"
                                                              }
                                                            #line 1959 "PrintJava.cpp"
  append(L", int t)\n");
  append(L"  {\n");
  append(L"    accepted = false;\n");
  append(L"    target = t;");
                                                            #line 1293 "PrintJava.cpp.template"
                                                              if (resolvesAmbiguity)
                                                              {
                                                            #line 1967 "PrintJava.cpp"
  append(L"\n");
  append(L"    eventCount = 0;");
                                                            #line 1296 "PrintJava.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                            #line 1974 "PrintJava.cpp"
  append(L"\n");
  append(L"    eventHandler = eh;\n");
  append(L"    if (eventHandler != null)\n");
  append(L"    {\n");
  append(L"      eventHandler.reset(input);\n");
  append(L"    }\n");
  append(L"    deferredEvent = null;");
                                                            #line 1305 "PrintJava.cpp.template"
                                                              }
                                                              if (hasCustomCode && useGlr)
                                                              {
                                                            #line 1986 "PrintJava.cpp"
  append(L"\n");
  append(L"    deferredCode = null;");
                                                            #line 1309 "PrintJava.cpp.template"
                                                              }
                                                            #line 1991 "PrintJava.cpp"
  append(L"\n");
  append(L"    stack = new StackNode(-1, ");
                                                            #line 1311 "PrintJava.cpp.template"
                                                              if (grammar->states->hasLookback)
                                                              {
                                                            #line 1997 "PrintJava.cpp"
  append(L"0, ");
                                                            #line 1313 "PrintJava.cpp.template"
                                                              }
                                                            #line 2001 "PrintJava.cpp"
  append(L"e0, null);\n");
  append(L"    state = initialState;\n");
  append(L"    action = predict(initialState);");
                                                            #line 1316 "PrintJava.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 2008 "PrintJava.cpp"
  append(L"\n");
  append(L"    bw = e0;\n");
  append(L"    bs = e0;\n");
  append(L"    es = e0;");
                                                            #line 1321 "PrintJava.cpp.template"
                                                              }
                                                            #line 2015 "PrintJava.cpp"
  append(L"\n");
  append(L"    threads = new PriorityQueue<>();\n");
  append(L"    threads.offer(this);\n");
  append(L"    return threads;\n");
  append(L"  }\n");
  append(L"\n");
                                                            #line 1328 "PrintJava.cpp.template"
                                                              if (resolvesAmbiguity && tree)
                                                              {
                                                            #line 2025 "PrintJava.cpp"
  append(L"  public void addAmbiguity(int begin, int end)\n");
  append(L"  {\n");
  append(L"    if (eventHandler != null)\n");
  append(L"      deferredEvent = new AmbiguityEvent(deferredEvent, begin, end);\n");
  append(L"  }\n");
  append(L"\n");
                                                            #line 1336 "PrintJava.cpp.template"
                                                              }
                                                            #line 2034 "PrintJava.cpp"
  append(L"  public ParsingThread copy(ParsingThread other, int action)\n");
  append(L"  {\n");
  append(L"    this.action = action;\n");
  append(L"    accepted = other.accepted;\n");
  append(L"    target = other.target;");
                                                            #line 1341 "PrintJava.cpp.template"
                                                              if (resolvesAmbiguity)
                                                              {
                                                            #line 2043 "PrintJava.cpp"
  append(L"\n");
  append(L"    eventCount = other.eventCount;");
                                                            #line 1344 "PrintJava.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                            #line 2050 "PrintJava.cpp"
  append(L"\n");
  append(L"    bs = other.bs;\n");
  append(L"    es = other.es;\n");
  append(L"    bw = other.bw;\n");
  append(L"    eventHandler = other.eventHandler;\n");
  append(L"    deferredEvent = other.deferredEvent;");
                                                            #line 1352 "PrintJava.cpp.template"
                                                              }
                                                              if (hasCustomCode)
                                                              {
                                                            #line 2061 "PrintJava.cpp"
  append(L"\n");
  append(L"    deferredCode = other.deferredCode;");
                                                            #line 1356 "PrintJava.cpp.template"
                                                              }
                                                            #line 2066 "PrintJava.cpp"
  append(L"\n");
  append(L"    id = ++maxId;\n");
  append(L"    threads = other.threads;\n");
  append(L"    state = other.state;\n");
  append(L"    stack = other.stack;\n");
  append(L"    b0 = other.b0;\n");
  append(L"    e0 = other.e0;");
                                                            #line 1363 "PrintJava.cpp.template"
                                                              for (size_t i = 1; i <= grammar->k; ++i)
                                                              {
                                                                const wchar_t *iString = format.toString<wchar_t>(i);
                                                            #line 2078 "PrintJava.cpp"
  append(L"\n");
  append(L"    l");
                                                            #line 1367 "PrintJava.cpp.template"
                                                                print(iString);
                                                            #line 2083 "PrintJava.cpp"
  append(L" = other.l");
                                                            #line 1368 "PrintJava.cpp.template"
                                                                print(iString);
                                                            #line 2087 "PrintJava.cpp"
  append(L";\n");
  append(L"    b");
                                                            #line 1370 "PrintJava.cpp.template"
                                                                print(iString);
                                                            #line 2092 "PrintJava.cpp"
  append(L" = other.b");
                                                            #line 1371 "PrintJava.cpp.template"
                                                                print(iString);
                                                            #line 2096 "PrintJava.cpp"
  append(L";\n");
  append(L"    e");
                                                            #line 1373 "PrintJava.cpp.template"
                                                                print(iString);
                                                            #line 2101 "PrintJava.cpp"
  append(L" = other.e");
                                                            #line 1374 "PrintJava.cpp.template"
                                                                print(iString);
                                                            #line 2105 "PrintJava.cpp"
  append(L";");
                                                            #line 1375 "PrintJava.cpp.template"
                                                              }
                                                            #line 2109 "PrintJava.cpp"
  append(L"\n");
  append(L"    end = other.end;\n");
  append(L"    return this;\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  @Override\n");
  append(L"  public int compareTo(ParsingThread other)\n");
  append(L"  {\n");
  append(L"    if (accepted != other.accepted)\n");
  append(L"      return accepted ? 1 : -1;\n");
  append(L"    int comp = e0 - other.e0;\n");
  append(L"    return comp == 0 ? id - other.id : comp;\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  @Override\n");
  append(L"  public boolean equals(Object obj)\n");
  append(L"  {\n");
  append(L"    ParsingThread other = (ParsingThread) obj;\n");
  append(L"    if (accepted != other.accepted) return false;\n");
  append(L"    if (b1 != other.b1) return false;\n");
  append(L"    if (e1 != other.e1) return false;\n");
  append(L"    if (l1 != other.l1) return false;\n");
  append(L"    if (state != other.state) return false;\n");
  append(L"    if (action != other.action) return false;\n");
  append(L"    if (! stack.equals(other.stack)) return false;\n");
  append(L"    return true;\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  public int parse()\n");
  append(L"  {");
                                                            #line 1405 "PrintJava.cpp.template"
                                                              increaseIndent();
                                                              beginPublic();
                                                            }

                                                            void PrintJava::printFlush(int i, bool withinThread)
                                                            {
                                                              if (trace)
                                                              {
                                                                increaseIndent(i);
                                                            #line 2150 "PrintJava.cpp"
  append(L"\n");
  append(L"flushTrace();");
                                                            #line 1415 "PrintJava.cpp.template"
                                                                decreaseIndent(i);
                                                              }
                                                            }

                                                            void PrintJava::openMethod(const wchar_t *type,
                                                                                       const wchar_t *prefix,
                                                                                       const wchar_t *name,
                                                                                       const wchar_t *args,
                                                                                       bool constant,
                                                                                       const wchar_t *clazz)
                                                            {
                                                            #line 2165 "PrintJava.cpp"
  append(L"\n");
                                                            #line 1427 "PrintJava.cpp.template"
                                                              print(visibility);
                                                            #line 2169 "PrintJava.cpp"
  append(L" ");
                                                            #line 1428 "PrintJava.cpp.template"
                                                              print(prefix);
                                                              print(type);
                                                              print(name);
                                                            #line 2175 "PrintJava.cpp"
  append(L"(");
                                                            #line 1431 "PrintJava.cpp.template"
                                                              print(args);
                                                            #line 2179 "PrintJava.cpp"
  append(L")");
                                                            #line 1432 "PrintJava.cpp.template"
                                                            }

                                                            void PrintJava::privateVars()
                                                            {
                                                              if (trace)
                                                              {
                                                            #line 2188 "PrintJava.cpp"
  append(L"\n");
  append(L"  private String lookaheadString()\n");
  append(L"  {\n");
  append(L"    String result = \"\";");
                                                            #line 1441 "PrintJava.cpp.template"
                                                                for (size_t i = 1; i <= grammar->k; ++i)
                                                                {
                                                            #line 2196 "PrintJava.cpp"
  append(L"\n");
  append(L"    if (l");
                                                            #line 1444 "PrintJava.cpp.template"
                                                                  print(format.toString<wchar_t>(i));
                                                            #line 2201 "PrintJava.cpp"
  append(L" > 0)\n");
  append(L"    {\n");
  append(L"      result += ");
                                                            #line 1447 "PrintJava.cpp.template"
                                                                  if (i != 1)
                                                                  {
                                                            #line 2208 "PrintJava.cpp"
  append(L"\" \" + ");
                                                            #line 1449 "PrintJava.cpp.template"
                                                                  }
                                                            #line 2212 "PrintJava.cpp"
  append(L"TOKEN[l");
                                                            #line 1450 "PrintJava.cpp.template"
                                                                  print(format.toString<wchar_t>(i));
                                                            #line 2216 "PrintJava.cpp"
  append(L"];");
                                                            #line 1451 "PrintJava.cpp.template"
                                                                  increaseIndent();
                                                                }
                                                                for (size_t i = 1; i <= grammar->k; ++i)
                                                                {
                                                                  decreaseIndent();
                                                            #line 2224 "PrintJava.cpp"
  append(L"\n");
  append(L"    }");
                                                            #line 1457 "PrintJava.cpp.template"
                                                                }
                                                            #line 2229 "PrintJava.cpp"
  append(L"\n");
  append(L"    return result;\n");
  append(L"  }\n");
                                                            #line 1461 "PrintJava.cpp.template"
                                                              }
                                                              if (memoization)
                                                              {
                                                                int bits = Math::bits(grammar->conflictCount);
                                                            #line 2238 "PrintJava.cpp"
  append(L"\n");
  append(L"  private void memoize(int i, int e, int v)\n");
  append(L"  {\n");
  append(L"    memo.put((e << ");
                                                            #line 1468 "PrintJava.cpp.template"
                                                                print(format.toString<wchar_t>(bits));
                                                            #line 2245 "PrintJava.cpp"
  append(L") + i, v);\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  private int memoized(int i, int e)\n");
  append(L"  {\n");
  append(L"    Integer v = memo.get((e << ");
                                                            #line 1474 "PrintJava.cpp.template"
                                                                print(format.toString<wchar_t>(bits));
                                                            #line 2254 "PrintJava.cpp"
  append(L") + i);\n");
  append(L"    return v == null ? 0 : v;\n");
  append(L"  }\n");
                                                            #line 1478 "PrintJava.cpp.template"
                                                              }
                                                            #line 2260 "PrintJava.cpp"
  append(L"\n");
  append(L"  private int ");
                                                            #line 1480 "PrintJava.cpp.template"
                                                              if (! isLrParser && (grammar->k > 1 ||
                                                                                   memoization ||
                                                                                   ! grammar->decisionPoints.empty()))
                                                              {
                                                            #line 2268 "PrintJava.cpp"
  append(L"lk,");
                                                            #line 1484 "PrintJava.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 2274 "PrintJava.cpp"
  append(L"   ");
                                                            #line 1487 "PrintJava.cpp.template"
                                                              }
                                                            #line 2278 "PrintJava.cpp"
  append(L" b0, e0;");
                                                            #line 1488 "PrintJava.cpp.template"
                                                              for (size_t k = 1; k <= grammar->k; ++k)
                                                              {
                                                                Format format;
                                                                wchar_t *asString = format.toString<wchar_t>(k);
                                                            #line 2285 "PrintJava.cpp"
  append(L"\n");
  append(L"  private int l");
                                                            #line 1493 "PrintJava.cpp.template"
                                                                print(asString);
                                                            #line 2290 "PrintJava.cpp"
  append(L", b");
                                                            #line 1494 "PrintJava.cpp.template"
                                                                print(asString);
                                                            #line 2294 "PrintJava.cpp"
  append(L", e");
                                                            #line 1495 "PrintJava.cpp.template"
                                                                print(asString);
                                                            #line 2298 "PrintJava.cpp"
  append(L";");
                                                            #line 1496 "PrintJava.cpp.template"
                                                              }
                                                              if (hasBacktracking)
                                                              {
                                                            #line 2304 "PrintJava.cpp"
  append(L"\n");
  append(L"  private int bx, ex, sx, lx, tx;");
                                                            #line 1500 "PrintJava.cpp.template"
                                                              }
                                                              else if (isLrParser && ! useGlr)
                                                              {
                                                            #line 2311 "PrintJava.cpp"
  append(L"\n");
  append(L"  private int iStack[] = new int[");
                                                            #line 1504 "PrintJava.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 2317 "PrintJava.cpp"
  append(L"192");
                                                            #line 1506 "PrintJava.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 2323 "PrintJava.cpp"
  append(L"128");
                                                            #line 1509 "PrintJava.cpp.template"
                                                                }
                                                            #line 2327 "PrintJava.cpp"
  append(L"];\n");
  append(L"  private int top = -1;");
                                                            #line 1511 "PrintJava.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                                if (isLrParser)
                                                                {
                                                                  if (useGlr)
                                                                  {
                                                            #line 2338 "PrintJava.cpp"
  append(L"\n");
  append(L"  private int bw, bs, es;");
                                                            #line 1519 "PrintJava.cpp.template"
                                                                  }
                                                            #line 2343 "PrintJava.cpp"
  append(L"\n");
  append(L"  private BottomUpEventHandler eventHandler = null;");
                                                            #line 1521 "PrintJava.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 2350 "PrintJava.cpp"
  append(L"\n");
  append(L"  private EventHandler eventHandler = null;");
                                                            #line 1525 "PrintJava.cpp.template"
                                                                }
                                                              }
                                                              if (memoization)
                                                              {
                                                            #line 2358 "PrintJava.cpp"
  append(L"\n");
  append(L"  private java.util.Map<Integer, Integer> memo = new java.util.HashMap<Integer, Integer>();");
                                                            #line 1531 "PrintJava.cpp.template"
                                                                if (grammar->noThrow)
                                                                {
                                                            #line 2364 "PrintJava.cpp"
  append(L"\n");
  append(L"  private boolean viable;");
                                                            #line 1534 "PrintJava.cpp.template"
                                                                }
                                                              }
                                                              if (useGlr)
                                                              {
                                                                decreaseIndent();
                                                              }
                                                            }

                                                            void PrintJava::printFileProcessor()
                                                            {
                                                            #line 2378 "PrintJava.cpp"
  append(L"\n");
  append(L"  private static boolean quiet = false;\n");
  append(L"  private static long parsed = 0;\n");
  append(L"  private static int errorCount = 0;\n");
  append(L"  private static java.util.Collection<ParseJob> parsers = new java.util.ArrayList<>();\n");
  append(L"\n");
  append(L"  private static class ParseJob\n");
  append(L"  {\n");
  append(L"    public String name;\n");
  append(L"    public ");
                                                            #line 1553 "PrintJava.cpp.template"
                                                              print(codepoints ? L"int[]" : L"String");
                                                            #line 2391 "PrintJava.cpp"
  append(L" input;\n");
  append(L"    public ");
                                                            #line 1555 "PrintJava.cpp.template"
                                                              print(className.c_str());
                                                            #line 2396 "PrintJava.cpp"
  append(L" parser;");
                                                            #line 1556 "PrintJava.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 2401 "PrintJava.cpp"
  append(L"\n");
  append(L"    public ContentCounter contentCounter;");
                                                            #line 1559 "PrintJava.cpp.template"
                                                                if (isLrParser)
                                                                {
                                                            #line 2407 "PrintJava.cpp"
  append(L"\n");
  append(L"    public ParseTreeBuilder parseTreeBuilder;");
                                                            #line 1562 "PrintJava.cpp.template"
                                                                }
                                                              }
                                                            #line 2413 "PrintJava.cpp"
  append(L"\n");
  append(L"\n");
  append(L"    public ParseJob(String s, String i)\n");
  append(L"    {\n");
  append(L"      name = s;\n");
  append(L"      input = i");
                                                            #line 1569 "PrintJava.cpp.template"
                                                              if (codepoints)
                                                              {
                                                            #line 2423 "PrintJava.cpp"
  append(L".codePoints().toArray()");
                                                            #line 1571 "PrintJava.cpp.template"
                                                              }
                                                            #line 2427 "PrintJava.cpp"
  append(L";");
                                                            #line 1572 "PrintJava.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 2432 "PrintJava.cpp"
  append(L"\n");
  append(L"      contentCounter = new ContentCounter();");
                                                            #line 1575 "PrintJava.cpp.template"
                                                                if (isLrParser)
                                                                {
                                                            #line 2438 "PrintJava.cpp"
  append(L"\n");
  append(L"      parseTreeBuilder = new ParseTreeBuilder();");
                                                            #line 1578 "PrintJava.cpp.template"
                                                                }
                                                              }
                                                            #line 2444 "PrintJava.cpp"
  append(L"\n");
  append(L"      parser = new ");
                                                            #line 1581 "PrintJava.cpp.template"
                                                              print(className.c_str());
                                                            #line 2449 "PrintJava.cpp"
  append(L"(input");
                                                            #line 1582 "PrintJava.cpp.template"
                                                              if (noLexer)
                                                              {
                                                            #line 2454 "PrintJava.cpp"
  append(L", new ");
                                                            #line 1584 "PrintJava.cpp.template"
                                                                print(className.c_str());
                                                            #line 2458 "PrintJava.cpp"
  append(L"Lexer()");
                                                            #line 1585 "PrintJava.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                                if (isLrParser)
                                                                {
                                                            #line 2466 "PrintJava.cpp"
  append(L", parseTreeBuilder");
                                                            #line 1590 "PrintJava.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 2472 "PrintJava.cpp"
  append(L", contentCounter");
                                                            #line 1593 "PrintJava.cpp.template"
                                                                }
                                                              }
                                                            #line 2477 "PrintJava.cpp"
  append(L");\n");
  append(L"    }\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  public static void main(String[] args) throws Exception\n");
  append(L"  {\n");
  append(L"    if (args.length == 0)\n");
  append(L"    {\n");
  append(L"      System.out.println(\"Usage: java ");
                                                            #line 1603 "PrintJava.cpp.template"
                                                              print(className.c_str());
                                                            #line 2489 "PrintJava.cpp"
  append(L" [-q] [-r N] [-t N] ENDING...\");\n");
  append(L"      System.out.println();\n");
  append(L"      System.out.println(\"  parse all files that have names ending with ENDING, in current dir and below,\");\n");
  append(L"      System.out.println(\"  and display performance summary.\");\n");
  append(L"      System.out.println();\n");
  append(L"      System.out.println(\"  -q     do not show file names\");\n");
  append(L"      System.out.println(\"  -r N   repeat N times\");\n");
  append(L"      System.out.println(\"  -t N   repeat until N seconds have elapsed\");\n");
  append(L"    }\n");
  append(L"    else\n");
  append(L"    {\n");
  append(L"      int repeat = 1;\n");
  append(L"      int timeout = 0;\n");
  append(L"      int i;\n");
  append(L"      for (i = 0; i < args.length && args[i].startsWith(\"-\"); ++i)\n");
  append(L"      {\n");
  append(L"        switch (args[i].length() == 2 ? args[i].charAt(1) : ' ')\n");
  append(L"        {\n");
  append(L"        case 'q':\n");
  append(L"          quiet = true;\n");
  append(L"          break;\n");
  append(L"        case 'r':\n");
  append(L"          repeat = Integer.parseInt(args[++i]);\n");
  append(L"          timeout = 0;\n");
  append(L"          break;\n");
  append(L"        case 't':\n");
  append(L"          repeat = 0;\n");
  append(L"          timeout = 1000 * Integer.parseInt(args[++i]);\n");
  append(L"          break;\n");
  append(L"        default:\n");
  append(L"          throw new RuntimeException(\"invalid option: \" + args[i]);\n");
  append(L"        }\n");
  append(L"      }\n");
  append(L"\n");
  append(L"      long start = System.currentTimeMillis();\n");
  append(L"\n");
  append(L"      for (; i < args.length; ++i)\n");
  append(L"      {\n");
  append(L"        findFiles(new java.io.File(\".\"), args[i]);\n");
  append(L"      }\n");
  append(L"\n");
  append(L"      if (! parsers.isEmpty())\n");
  append(L"      {\n");
  append(L"        long msec = System.currentTimeMillis() - start;\n");
  append(L"\n");
  append(L"        if (! quiet) System.out.println();\n");
  append(L"        System.out.println(\"loaded \" + parsers.size() + \" file\" +\n");
  append(L"                           (parsers.size() == 1 ? \"\" : \"s\") + \" in \" +\n");
  append(L"                           msec + \" msec\");\n");
  append(L"        if (! quiet) System.out.println();\n");
  append(L"        System.out.flush();\n");
  append(L"\n");
  append(L"        start = System.currentTimeMillis();\n");
  append(L"        for (i = 0; ; ++i)\n");
  append(L"        {\n");
  append(L"          if (repeat != 0 && i >= repeat) break;\n");
  append(L"          if (timeout != 0 && System.currentTimeMillis() - start >= timeout) break;\n");
  append(L"\n");
  append(L"          for (ParseJob job : parsers)\n");
  append(L"          {\n");
  append(L"            if (job.parser != null)\n");
  append(L"            {\n");
  append(L"              try\n");
  append(L"              {\n");
  append(L"                if (! quiet) System.out.print(\"parsing \" + job.name);\n");
  append(L"                job.parser");
                                                            #line 1669 "PrintJava.cpp.template"
                                                              if (useGlr)
                                                              {
                                                            #line 2559 "PrintJava.cpp"
  append(L".thread");
                                                            #line 1671 "PrintJava.cpp.template"
                                                              }
                                                            #line 2563 "PrintJava.cpp"
  append(L".reset(0, 0, 0);\n");
  append(L"                job.parser.");
                                                            #line 1673 "PrintJava.cpp.template"
                                                              print(methodPrefixParse);
                                                              print(Format::acceptableName<WString>(grammar->startSymbol()->name).c_str());
                                                            #line 2569 "PrintJava.cpp"
  append(L"();\n");
  append(L"                if (! quiet) System.out.println();");
                                                            #line 1676 "PrintJava.cpp.template"
                                                              if (tree)
                                                              {
                                                                if (isLrParser)
                                                                {
                                                            #line 2577 "PrintJava.cpp"
  append(L"\n");
  append(L"                job.parseTreeBuilder.serialize(job.contentCounter);");
                                                            #line 1682 "PrintJava.cpp.template"
                                                                }
                                                            #line 2582 "PrintJava.cpp"
  append(L"\n");
  append(L"                if (job.contentCounter.getLength() != job.input.length");
                                                            #line 1685 "PrintJava.cpp.template"
                                                                if (! codepoints)
                                                                {
                                                            #line 2588 "PrintJava.cpp"
  append(L"()");
                                                            #line 1687 "PrintJava.cpp.template"
                                                                }
                                                            #line 2592 "PrintJava.cpp"
  append(L")\n");
  append(L"                {\n");
  append(L"                  throw new RuntimeException(\"content counter saw \" + job.contentCounter.getLength() + \", but input length is \" + job.input.length");
                                                            #line 1691 "PrintJava.cpp.template"
                                                                if (! codepoints)
                                                                {
                                                            #line 2599 "PrintJava.cpp"
  append(L"()");
                                                            #line 1693 "PrintJava.cpp.template"
                                                                }
                                                            #line 2603 "PrintJava.cpp"
  append(L");\n");
  append(L"                }");
                                                            #line 1695 "PrintJava.cpp.template"
                                                              }
                                                            #line 2608 "PrintJava.cpp"
  append(L"\n");
  append(L"                parsed += job.input.length");
                                                            #line 1697 "PrintJava.cpp.template"
                                                              if (! codepoints)
                                                              {
                                                            #line 2614 "PrintJava.cpp"
  append(L"()");
                                                            #line 1699 "PrintJava.cpp.template"
                                                              }
                                                            #line 2618 "PrintJava.cpp"
  append(L";\n");
  append(L"              }\n");
  append(L"              catch (ParseException pe)\n");
  append(L"              {\n");
  append(L"                ++errorCount;\n");
  append(L"                if (quiet) System.out.print(\"parsing \" + job.name);\n");
  append(L"                System.out.println(\": error: \" + job.parser.getErrorMessage(pe));\n");
  append(L"                job.parser = null;\n");
  append(L"              }\n");
  append(L"            }\n");
  append(L"          }\n");
  append(L"        }\n");
  append(L"        msec = System.currentTimeMillis() - start;\n");
  append(L"        String mbPerSec = msec == 0\n");
  append(L"                        ? null\n");
  append(L"                        : new java.text.DecimalFormat(\"0.##\").format(Double.valueOf(parsed / 1024e0 / 1024e0 * 1000e0 / msec));\n");
  append(L"\n");
  append(L"        if (! quiet) System.out.println();\n");
  append(L"        System.out.print(\"parsed \" + parsed + \" byte\" + (parsed == 1 ? \"\" : \"s\") +\n");
  append(L"                         \" in \" + msec + \" msec\");\n");
  append(L"        if (mbPerSec != null)\n");
  append(L"        {\n");
  append(L"          System.out.print(\" (\" + mbPerSec + \" MB/sec)\");\n");
  append(L"        }\n");
  append(L"        System.out.println();\n");
  append(L"        System.out.println(errorCount + \" error\" + (errorCount == 1 ? \"\" : \"s\"));\n");
  append(L"      }\n");
  append(L"    }\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  private static void collectInput(String name, String content) throws Exception\n");
  append(L"  {\n");
  append(L"    if (! quiet) System.out.println(\"loading \" + name);\n");
  append(L"    parsers.add(new ParseJob(name, content));\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  private static void findFiles(java.io.File f, String filter) throws Exception\n");
  append(L"  {\n");
  append(L"    if (f.isDirectory())\n");
  append(L"    {\n");
  append(L"      java.io.File files[] = f.listFiles();\n");
  append(L"      if (files != null)\n");
  append(L"      {\n");
  append(L"        for (java.io.File file : files)\n");
  append(L"        {\n");
  append(L"          findFiles(file, filter);\n");
  append(L"        }\n");
  append(L"      }\n");
  append(L"    }\n");
  append(L"    else if (f.getName().toLowerCase().endsWith(filter.toLowerCase()))\n");
  append(L"    {\n");
  append(L"      collectInput(f.getPath(), read(f.getPath()));\n");
  append(L"    }\n");
  append(L"  }\n");
                                                            #line 1754 "PrintJava.cpp.template"
                                                            }

                                                            void PrintJava::printReadMethod()
                                                            {
                                                            #line 2678 "PrintJava.cpp"
  append(L"\n");
  append(L"  private static String read(String input) throws Exception\n");
  append(L"  {\n");
  append(L"    if (input.startsWith(\"{\") && input.endsWith(\"}\"))\n");
  append(L"    {\n");
  append(L"      return input.substring(1, input.length() - 1);\n");
  append(L"    }\n");
  append(L"    else\n");
  append(L"    {\n");
  append(L"      byte buffer[] = new byte[(int) new java.io.File(input).length()];\n");
  append(L"      java.io.FileInputStream stream = new java.io.FileInputStream(input);\n");
  append(L"      stream.read(buffer);\n");
  append(L"      stream.close();\n");
  append(L"      String content = new String(buffer, System.getProperty(\"file.encoding\"));\n");
  append(L"      return content.length() > 0 && content.charAt(0) == '\\uFEFF'\n");
  append(L"           ? content.substring(1)\n");
  append(L"           : content;\n");
  append(L"    }\n");
  append(L"  }\n");
                                                            #line 1777 "PrintJava.cpp.template"
                                                            }

                                                            void PrintJava::printInterface()
                                                            {
                                                              if (! packageName.empty())
                                                              {
                                                            #line 2705 "PrintJava.cpp"
  append(L"\n");
  append(L"package ");
                                                            #line 1784 "PrintJava.cpp.template"
                                                                print(packageName.c_str());
                                                            #line 2710 "PrintJava.cpp"
  append(L";\n");
                                                            #line 1786 "PrintJava.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                                if (main || useGlr)
                                                                {
                                                            #line 2718 "PrintJava.cpp"
  append(L"\n");
  append(L"import java.io.IOException;\n");
  append(L"import java.io.Writer;\n");
                                                            #line 1794 "PrintJava.cpp.template"
                                                                }
                                                            #line 2724 "PrintJava.cpp"
  append(L"\n");
  append(L"import java.util.Arrays;");
                                                            #line 1796 "PrintJava.cpp.template"
                                                                if (saxon)
                                                                {
                                                            #line 2730 "PrintJava.cpp"
  append(L"\n");
  append(L"import net.sf.saxon.event.Builder;");
                                                            #line 1799 "PrintJava.cpp.template"
                                                                  if (saxon == 99)
                                                                  {
                                                            #line 2736 "PrintJava.cpp"
  append(L"\n");
  append(L"import net.sf.saxon.expr.parser.ExplicitLocation;\n");
  append(L"import net.sf.saxon.expr.parser.Location;");
                                                            #line 1803 "PrintJava.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 2744 "PrintJava.cpp"
  append(L"\n");
  append(L"import net.sf.saxon.expr.parser.Loc;\n");
  append(L"import net.sf.saxon.om.AttributeMap;\n");
  append(L"import net.sf.saxon.om.EmptyAttributeMap;\n");
  append(L"import net.sf.saxon.om.NamespaceMap;\n");
  append(L"import net.sf.saxon.s9api.Location;");
                                                            #line 1811 "PrintJava.cpp.template"
                                                                  }
                                                            #line 2753 "PrintJava.cpp"
  append(L"\n");
  append(L"import net.sf.saxon.om.NoNamespaceName;\n");
  append(L"import net.sf.saxon.trans.XPathException;\n");
  append(L"import net.sf.saxon.type.AnyType;");
                                                            #line 1815 "PrintJava.cpp.template"
                                                                  if (saxon == 110)
                                                                  {
                                                            #line 2761 "PrintJava.cpp"
  append(L"\n");
  append(L"import net.sf.saxon.str.StringView;");
                                                            #line 1818 "PrintJava.cpp.template"
                                                                  }
                                                            #line 2766 "PrintJava.cpp"
  append(L"\n");
                                                            #line 1820 "PrintJava.cpp.template"
                                                                }
                                                              }
                                                            #line 2771 "PrintJava.cpp"
  append(L"\n");
  append(L"public interface ");
                                                            #line 1823 "PrintJava.cpp.template"
                                                              print(className.c_str());
                                                            #line 2776 "PrintJava.cpp"
  append(L"\n");
  append(L"{\n");
  append(L"  public void initialize(");
                                                            #line 1826 "PrintJava.cpp.template"
                                                              print(inputType());
                                                            #line 2782 "PrintJava.cpp"
  append(L" input");
                                                            #line 1827 "PrintJava.cpp.template"
                                                              if (noLexer)
                                                              {
                                                            #line 2787 "PrintJava.cpp"
  append(L", Lexer l");
                                                            #line 1829 "PrintJava.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                            #line 2793 "PrintJava.cpp"
  append(L", ");
                                                            #line 1832 "PrintJava.cpp.template"
                                                                if (isLrParser)
                                                                {
                                                            #line 2798 "PrintJava.cpp"
  append(L"BottomUp");
                                                            #line 1834 "PrintJava.cpp.template"
                                                                }
                                                            #line 2802 "PrintJava.cpp"
  append(L"EventHandler eh");
                                                            #line 1836 "PrintJava.cpp.template"
                                                              }
                                                            #line 2806 "PrintJava.cpp"
  append(L");\n");
  append(L"  public void parse();\n");
  append(L"  public void reset();\n");
  append(L"  public String getErrorMessage(ParseException e);");
                                                            #line 1840 "PrintJava.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 2814 "PrintJava.cpp"
  append(L"\n");
  append(L"  public String getTerminalName(int id);\n");
  append(L"  public String getNonterminalName(int id);");
                                                            #line 1844 "PrintJava.cpp.template"
                                                              }
                                                            #line 2820 "PrintJava.cpp"
  append(L"\n");
                                                            #line 1846 "PrintJava.cpp.template"
                                                              printParseException();
                                                              printEventHandlerImplementation();
                                                            #line 2825 "PrintJava.cpp"
  append(L"}\n");
                                                            #line 1849 "PrintJava.cpp.template"
                                                            }

                                                            void PrintJava::printParseException()
                                                            {
                                                            #line 2832 "PrintJava.cpp"
  append(L"\n");
  append(L"  public static class ParseException extends RuntimeException\n");
  append(L"  {\n");
  append(L"    private static final long serialVersionUID = 1L;\n");
  append(L"    private int begin, end, offending, expected, state;");
                                                            #line 1857 "PrintJava.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 2841 "PrintJava.cpp"
  append(L"\n");
  append(L"    private boolean ambiguousInput;");
                                                            #line 1860 "PrintJava.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 2847 "PrintJava.cpp"
  append(L"\n");
  append(L"    private ParseTreeBuilder ambiguityDescriptor;");
                                                            #line 1863 "PrintJava.cpp.template"
                                                                }
                                                              }
                                                            #line 2853 "PrintJava.cpp"
  append(L"\n");
  append(L"\n");
  append(L"    public ParseException(int b, int e, int s, int o, int x)\n");
  append(L"    {\n");
  append(L"      begin = b;\n");
  append(L"      end = e;\n");
  append(L"      state = s;\n");
  append(L"      offending = o;\n");
  append(L"      expected = x;");
                                                            #line 1873 "PrintJava.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 2866 "PrintJava.cpp"
  append(L"\n");
  append(L"      ambiguousInput = false;");
                                                            #line 1876 "PrintJava.cpp.template"
                                                              }
                                                            #line 2871 "PrintJava.cpp"
  append(L"\n");
  append(L"    }\n");
                                                            #line 1879 "PrintJava.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 2877 "PrintJava.cpp"
  append(L"\n");
  append(L"    public ParseException(int b, int e");
                                                            #line 1882 "PrintJava.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 2883 "PrintJava.cpp"
  append(L", ParseTreeBuilder ambiguityDescriptor");
                                                            #line 1885 "PrintJava.cpp.template"
                                                                }
                                                            #line 2887 "PrintJava.cpp"
  append(L")\n");
  append(L"    {\n");
  append(L"      this(b, e, 1, -1, -1);\n");
  append(L"      ambiguousInput = true;");
                                                            #line 1889 "PrintJava.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 2895 "PrintJava.cpp"
  append(L"\n");
  append(L"      this.ambiguityDescriptor = ambiguityDescriptor;");
                                                            #line 1892 "PrintJava.cpp.template"
                                                                }
                                                            #line 2900 "PrintJava.cpp"
  append(L"\n");
  append(L"    }\n");
                                                            #line 1895 "PrintJava.cpp.template"
                                                              }
                                                            #line 2905 "PrintJava.cpp"
  append(L"\n");
  append(L"    @Override\n");
  append(L"    public String getMessage()\n");
  append(L"    {\n");
  append(L"      return ");
                                                            #line 1900 "PrintJava.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 2914 "PrintJava.cpp"
  append(L"ambiguousInput\n");
  append(L"           ? \"ambiguous input\"\n");
  append(L"           : ");
                                                            #line 1904 "PrintJava.cpp.template"
                                                              }
                                                            #line 2920 "PrintJava.cpp"
  append(L"offending < 0\n");
  append(L"           ? \"lexical analysis failed\"\n");
  append(L"           : \"syntax error\";\n");
  append(L"    }\n");
                                                            #line 1909 "PrintJava.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 2928 "PrintJava.cpp"
  append(L"\n");
  append(L"    public void serialize(EventHandler eventHandler)\n");
  append(L"    {");
                                                            #line 1913 "PrintJava.cpp.template"
                                                                if (rejectsAmbiguity())
                                                                {
                                                            #line 2935 "PrintJava.cpp"
  append(L"\n");
  append(L"      ambiguityDescriptor.serialize(eventHandler);");
                                                            #line 1916 "PrintJava.cpp.template"
                                                                }
                                                            #line 2940 "PrintJava.cpp"
  append(L"\n");
  append(L"    }\n");
                                                            #line 1919 "PrintJava.cpp.template"
                                                              }
                                                            #line 2945 "PrintJava.cpp"
  append(L"\n");
  append(L"    public int getBegin() {return begin;}\n");
  append(L"    public int getEnd() {return end;}\n");
  append(L"    public int getState() {return state;}\n");
  append(L"    public int getOffending() {return offending;}\n");
  append(L"    public int getExpected() {return expected;}\n");
  append(L"    public boolean isAmbiguousInput() {return ");
                                                            #line 1926 "PrintJava.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 2956 "PrintJava.cpp"
  append(L"ambiguousInput");
                                                            #line 1929 "PrintJava.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 2962 "PrintJava.cpp"
  append(L"false");
                                                            #line 1932 "PrintJava.cpp.template"
                                                              }
                                                            #line 2966 "PrintJava.cpp"
  append(L";}\n");
  append(L"  }\n");
                                                            #line 1935 "PrintJava.cpp.template"
                                                              if (noLexer)
                                                              {
                                                            #line 2972 "PrintJava.cpp"
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
  append(L"    void reset(CharSequence input);\n");
  append(L"    void match(int tokenset, Token token);\n");
  append(L"  }\n");
                                                            #line 1950 "PrintJava.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                            #line 2990 "PrintJava.cpp"
  append(L"\n");
  append(L"  public interface EventHandler\n");
  append(L"  {\n");
  append(L"    public void reset(");
                                                            #line 1956 "PrintJava.cpp.template"
                                                                print(inputType());
                                                            #line 2997 "PrintJava.cpp"
  append(L" string);\n");
  append(L"    public void startNonterminal(int id, int begin);\n");
  append(L"    public void endNonterminal(int id, int end);\n");
  append(L"    public void terminal(int id, int begin, int end);\n");
  append(L"    public void whitespace(int begin, int end);\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  public static class TopDownTreeBuilder implements EventHandler\n");
  append(L"  {\n");
  append(L"    private ");
                                                            #line 1966 "PrintJava.cpp.template"
                                                                print(inputType());
                                                            #line 3010 "PrintJava.cpp"
  append(L" input = null;\n");
  append(L"    private Nonterminal[] stack = new Nonterminal[64];\n");
  append(L"    private int top = -1;\n");
  append(L"\n");
  append(L"    @Override\n");
  append(L"    public void reset(");
                                                            #line 1972 "PrintJava.cpp.template"
                                                                print(inputType());
                                                            #line 3019 "PrintJava.cpp"
  append(L" input)\n");
  append(L"    {\n");
  append(L"      this.input = input;\n");
  append(L"      top = -1;\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    @Override\n");
  append(L"    public void startNonterminal(int id, int begin)\n");
  append(L"    {\n");
  append(L"      Nonterminal nonterminal = new Nonterminal(id, begin, begin, new Symbol[0]);\n");
  append(L"      if (top >= 0) addChild(nonterminal);\n");
  append(L"      if (++top >= stack.length) stack = Arrays.copyOf(stack, stack.length << 1);\n");
  append(L"      stack[top] = nonterminal;\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    @Override\n");
  append(L"    public void endNonterminal(int id, int end)\n");
  append(L"    {\n");
  append(L"      stack[top].end = end;\n");
  append(L"      if (top > 0) --top;\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    @Override\n");
  append(L"    public void terminal(int id, int begin, int end)\n");
  append(L"    {\n");
  append(L"      addChild(new Terminal(id, begin, end));\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    @Override\n");
  append(L"    public void whitespace(int begin, int end)\n");
  append(L"    {\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    private void addChild(Symbol s)\n");
  append(L"    {\n");
  append(L"      Nonterminal current = stack[top];\n");
  append(L"      current.children = Arrays.copyOf(current.children, current.children.length + 1);\n");
  append(L"      current.children[current.children.length - 1] = s;\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    public void serialize(EventHandler e)\n");
  append(L"    {\n");
  append(L"      e.reset(input);\n");
  append(L"      stack[0].send(e);\n");
  append(L"    }\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  public static abstract class Symbol\n");
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
  append(L"    public abstract String getName(");
                                                            #line 2033 "PrintJava.cpp.template"
                                                                if (! interfaceName.empty())
                                                                {
                                                                  print(className.c_str());
                                                            #line 3085 "PrintJava.cpp"
  append(L" names");
                                                            #line 2036 "PrintJava.cpp.template"
                                                                }
                                                            #line 3089 "PrintJava.cpp"
  append(L");\n");
  append(L"\n");
  append(L"    public abstract void send(EventHandler e);\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  public static class Terminal extends Symbol\n");
  append(L"  {\n");
  append(L"    public Terminal(int id, int begin, int end)\n");
  append(L"    {\n");
  append(L"      super(id, begin, end);\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    @Override\n");
  append(L"    public String getName(");
                                                            #line 2050 "PrintJava.cpp.template"
                                                                if (! interfaceName.empty())
                                                                {
                                                                  print(className.c_str());
                                                            #line 3108 "PrintJava.cpp"
  append(L" names");
                                                            #line 2053 "PrintJava.cpp.template"
                                                                }
                                                            #line 3112 "PrintJava.cpp"
  append(L")\n");
  append(L"    {\n");
  append(L"      return ");
                                                            #line 2056 "PrintJava.cpp.template"
                                                                if (interfaceName.empty())
                                                                {
                                                            #line 3119 "PrintJava.cpp"
  append(L"TOKEN[id]");
                                                            #line 2058 "PrintJava.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 3125 "PrintJava.cpp"
  append(L"names.getTerminalName(id)");
                                                            #line 2061 "PrintJava.cpp.template"
                                                                }
                                                            #line 3129 "PrintJava.cpp"
  append(L";\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    @Override\n");
  append(L"    public void send(EventHandler e)\n");
  append(L"    {\n");
  append(L"      e.terminal(id, begin, end);\n");
  append(L"    }\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  public static class Nonterminal extends Symbol\n");
  append(L"  {\n");
  append(L"    public Symbol[] children;\n");
  append(L"\n");
  append(L"    public Nonterminal(int id, int begin, int end, Symbol[] children)\n");
  append(L"    {\n");
  append(L"      super(id, begin, end);\n");
  append(L"      this.children = children;\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    @Override\n");
  append(L"    public String getName(");
                                                            #line 2083 "PrintJava.cpp.template"
                                                                if (! interfaceName.empty())
                                                                {
                                                                  print(className.c_str());
                                                            #line 3156 "PrintJava.cpp"
  append(L" names");
                                                            #line 2086 "PrintJava.cpp.template"
                                                                }
                                                            #line 3160 "PrintJava.cpp"
  append(L")\n");
  append(L"    {\n");
  append(L"      return ");
                                                            #line 2089 "PrintJava.cpp.template"
                                                                if (interfaceName.empty())
                                                                {
                                                                  printSyntheticNamePrefix();
                                                            #line 3168 "PrintJava.cpp"
  append(L"NONTERMINAL[id]");
                                                            #line 2092 "PrintJava.cpp.template"
                                                                  printSyntheticNameSuffix();
                                                                }
                                                                else
                                                                {
                                                            #line 3175 "PrintJava.cpp"
  append(L"names.getNonterminalName(id)");
                                                            #line 2096 "PrintJava.cpp.template"
                                                                }
                                                            #line 3179 "PrintJava.cpp"
  append(L";\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    @Override\n");
  append(L"    public void send(EventHandler e)\n");
  append(L"    {\n");
  append(L"      e.startNonterminal(id, begin);\n");
  append(L"      int pos = begin;\n");
  append(L"      for (Symbol c : children)\n");
  append(L"      {\n");
  append(L"        if (pos < c.begin) e.whitespace(pos, c.begin);\n");
  append(L"        c.send(e);\n");
  append(L"        pos = c.end;\n");
  append(L"      }\n");
  append(L"      if (pos < end) e.whitespace(pos, end);\n");
  append(L"      e.endNonterminal(id, end);\n");
  append(L"    }\n");
  append(L"  }\n");
                                                            #line 2115 "PrintJava.cpp.template"
                                                                if (isLrParser)
                                                                {
                                                            #line 3201 "PrintJava.cpp"
  append(L"\n");
  append(L"  public interface BottomUpEventHandler\n");
  append(L"  {\n");
  append(L"    public void reset(");
                                                            #line 2120 "PrintJava.cpp.template"
                                                                  print(inputType());
                                                            #line 3208 "PrintJava.cpp"
  append(L" string);\n");
  append(L"    public void nonterminal(int id, int begin, int end, int count);\n");
  append(L"    public void terminal(int id, int begin, int end);");
                                                            #line 2123 "PrintJava.cpp.template"
                                                                  if (resolvesAmbiguity)
                                                                  {
                                                            #line 3215 "PrintJava.cpp"
  append(L"\n");
  append(L"    public void ambiguity(int begin, int end);");
                                                            #line 2126 "PrintJava.cpp.template"
                                                                  }
                                                            #line 3220 "PrintJava.cpp"
  append(L"\n");
  append(L"  }\n");
                                                            #line 2129 "PrintJava.cpp.template"
                                                                }
                                                              }
                                                            }

                                                            void PrintJava::printNamesArgument()
                                                            {
                                                              if (! interfaceName.empty())
                                                              {
                                                            #line 3232 "PrintJava.cpp"
  append(L", new ");
                                                            #line 2137 "PrintJava.cpp.template"
                                                                print(className.c_str());
                                                            #line 3236 "PrintJava.cpp"
  append(L"()");
                                                            #line 2138 "PrintJava.cpp.template"
                                                              }
                                                            }

                                                            void PrintJava::printNamesPrefix()
                                                            {
                                                              if (! interfaceName.empty())
                                                              {
                                                            #line 3246 "PrintJava.cpp"
  append(L"names.");
                                                            #line 2145 "PrintJava.cpp.template"
                                                              }
                                                            }

                                                            void PrintJava::printNameSupport()
                                                            {
                                                              if (! interfaceName.empty())
                                                              {
                                                            #line 3256 "PrintJava.cpp"
  append(L"\n");
  append(L"\n");
  append(L"    private ");
                                                            #line 2154 "PrintJava.cpp.template"
                                                                print(className.c_str());
                                                            #line 3262 "PrintJava.cpp"
  append(L" names;");
                                                            #line 2155 "PrintJava.cpp.template"
                                                              }
                                                            }

                                                            void PrintJava::printEventHandlerImplementation()
                                                            {
                                                              if (tree)
                                                              {
                                                                if (main || useGlr)
                                                                {
                                                            #line 3274 "PrintJava.cpp"
  append(L"\n");
  append(L"  public static class XmlSerializer implements EventHandler\n");
  append(L"  {\n");
  append(L"    private ");
                                                            #line 2167 "PrintJava.cpp.template"
                                                                  print(inputType());
                                                            #line 3281 "PrintJava.cpp"
  append(L" input;\n");
  append(L"    private String delayedTag;\n");
  append(L"    private Writer out;\n");
  append(L"    private boolean indent;\n");
  append(L"    private boolean hasChildElement;\n");
  append(L"    private int depth;");
                                                            #line 2173 "PrintJava.cpp.template"
                                                                  printNameSupport();
                                                            #line 3290 "PrintJava.cpp"
  append(L"\n");
  append(L"\n");
  append(L"    public XmlSerializer(Writer w, boolean indent");
                                                            #line 2176 "PrintJava.cpp.template"
                                                                  if (! interfaceName.empty())
                                                                  {
                                                            #line 3297 "PrintJava.cpp"
  append(L", ");
                                                            #line 2178 "PrintJava.cpp.template"
                                                                    print(className.c_str());
                                                            #line 3301 "PrintJava.cpp"
  append(L" names");
                                                            #line 2179 "PrintJava.cpp.template"
                                                                  }
                                                            #line 3305 "PrintJava.cpp"
  append(L")\n");
  append(L"    {");
                                                            #line 2181 "PrintJava.cpp.template"
                                                                  if (! interfaceName.empty())
                                                                  {
                                                            #line 3311 "PrintJava.cpp"
  append(L"\n");
  append(L"      this.names = names;");
                                                            #line 2184 "PrintJava.cpp.template"
                                                                  }
                                                            #line 3316 "PrintJava.cpp"
  append(L"\n");
  append(L"      input = null;\n");
  append(L"      delayedTag = null;\n");
  append(L"      out = w;\n");
  append(L"      this.indent = indent;\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    @Override\n");
  append(L"    public void reset(");
                                                            #line 2193 "PrintJava.cpp.template"
                                                                  print(inputType());
                                                            #line 3328 "PrintJava.cpp"
  append(L" string)\n");
  append(L"    {\n");
  append(L"      writeOutput(\"<?xml version=\\\"1.0\\\" encoding=\\\"UTF-8\\\"?\" + \">\");\n");
  append(L"      input = string;\n");
  append(L"      delayedTag = null;\n");
  append(L"      hasChildElement = false;\n");
  append(L"      depth = 0;\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    @Override\n");
  append(L"    public void startNonterminal(int id, int begin)\n");
  append(L"    {\n");
  append(L"      startElement(");
                                                            #line 2206 "PrintJava.cpp.template"
                                                                  printNamesPrefix();
                                                            #line 3344 "PrintJava.cpp"
  append(L"getNonterminalName(id));\n");
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
  append(L"    @Override\n");
  append(L"    public void endNonterminal(int id, int end)\n");
  append(L"    {\n");
  append(L"      endElement(");
                                                            #line 2234 "PrintJava.cpp.template"
                                                                  printNamesPrefix();
                                                            #line 3375 "PrintJava.cpp"
  append(L"getNonterminalName(id));\n");
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
  append(L"    @Override\n");
  append(L"    public void terminal(int id, int begin, int end)\n");
  append(L"    {\n");
  append(L"      String name = ");
                                                            #line 2271 "PrintJava.cpp.template"
                                                                  printNamesPrefix();
                                                            #line 3415 "PrintJava.cpp"
  append(L"getTerminalName(id);\n");
  append(L"      if (name.charAt(0) == '\\'')\n");
  append(L"      {\n");
  append(L"        name = \"TOKEN\";\n");
  append(L"      }\n");
  append(L"      startElement(name);\n");
  append(L"      characters(begin, end);\n");
  append(L"      endElement(name);\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    @Override\n");
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
  append(L"        writeOutput(");
                                                            #line 2299 "PrintJava.cpp.template"
                                                                  if (codepoints)
                                                                  {
                                                            #line 3447 "PrintJava.cpp"
  append(L"new String(input, begin, end - begin)");
                                                            #line 2301 "PrintJava.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 3453 "PrintJava.cpp"
  append(L"input.subSequence(begin, end)\n");
  append(L"                         .toString()");
                                                            #line 2305 "PrintJava.cpp.template"
                                                                  }
                                                            #line 3458 "PrintJava.cpp"
  append(L"\n");
  append(L"                         .replace(\"&\", \"&amp;\")\n");
  append(L"                         .replace(\"<\", \"&lt;\")\n");
  append(L"                         .replace(\">\", \"&gt;\"));\n");
  append(L"      }\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    public void writeOutput(String content)\n");
  append(L"    {\n");
  append(L"      try\n");
  append(L"      {\n");
  append(L"        out.write(content);\n");
  append(L"      }\n");
  append(L"      catch (IOException e)\n");
  append(L"      {\n");
  append(L"        throw new RuntimeException(e);\n");
  append(L"      }\n");
  append(L"    }\n");
  append(L"  }\n");
                                                            #line 2325 "PrintJava.cpp.template"
                                                                }
                                                                if (performanceTest)
                                                                {
                                                            #line 3482 "PrintJava.cpp"
  append(L"\n");
  append(L"  public static class ContentCounter implements EventHandler\n");
  append(L"  {\n");
  append(L"    private int length = 0;\n");
  append(L"    public int getLength() {return length;}\n");
  append(L"    @Override\n");
  append(L"    public void reset(");
                                                            #line 2334 "PrintJava.cpp.template"
                                                                  print(inputType());
                                                            #line 3492 "PrintJava.cpp"
  append(L" string) {length = 0;}\n");
  append(L"    @Override\n");
  append(L"    public void startNonterminal(int id, int begin) {}\n");
  append(L"    @Override\n");
  append(L"    public void endNonterminal(int id, int end) {}\n");
  append(L"    @Override\n");
  append(L"    public void terminal(int id, int begin, int end) {length += end - begin;}\n");
  append(L"    @Override\n");
  append(L"    public void whitespace(int begin, int end) {length += end - begin;}\n");
  append(L"  }\n");
                                                            #line 2345 "PrintJava.cpp.template"
                                                                }
                                                                if (saxon)
                                                                {
                                                            #line 3507 "PrintJava.cpp"
  append(L"\n");
  append(L"  public static class SaxonTreeBuilder implements EventHandler\n");
  append(L"  {\n");
  append(L"    private ");
                                                            #line 2351 "PrintJava.cpp.template"
                                                                  print(inputType());
                                                            #line 3514 "PrintJava.cpp"
  append(L" input;\n");
  append(L"    private Builder builder;\n");
  append(L"    private AnyType anyType;");
                                                            #line 2354 "PrintJava.cpp.template"
                                                                  printNameSupport();
                                                            #line 3520 "PrintJava.cpp"
  append(L"\n");
  append(L"\n");
  append(L"    public SaxonTreeBuilder(Builder b");
                                                            #line 2357 "PrintJava.cpp.template"
                                                                  if (! interfaceName.empty())
                                                                  {
                                                            #line 3527 "PrintJava.cpp"
  append(L", ");
                                                            #line 2359 "PrintJava.cpp.template"
                                                                    print(className.c_str());
                                                            #line 3531 "PrintJava.cpp"
  append(L" names");
                                                            #line 2360 "PrintJava.cpp.template"
                                                                  }
                                                            #line 3535 "PrintJava.cpp"
  append(L")\n");
  append(L"    {");
                                                            #line 2362 "PrintJava.cpp.template"
                                                                  if (! interfaceName.empty())
                                                                  {
                                                            #line 3541 "PrintJava.cpp"
  append(L"\n");
  append(L"      this.names = names;");
                                                            #line 2365 "PrintJava.cpp.template"
                                                                  }
                                                            #line 3546 "PrintJava.cpp"
  append(L"\n");
  append(L"      input = null;\n");
  append(L"      builder = b;\n");
  append(L"      anyType = AnyType.getInstance();\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    @Override\n");
  append(L"    public void reset(");
                                                            #line 2373 "PrintJava.cpp.template"
                                                                  print(inputType());
                                                            #line 3557 "PrintJava.cpp"
  append(L" string)\n");
  append(L"    {\n");
  append(L"      input = string;\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    @Override\n");
  append(L"    public void startNonterminal(int id, int begin)\n");
  append(L"    {\n");
  append(L"      startElement(");
                                                            #line 2382 "PrintJava.cpp.template"
                                                                  printNamesPrefix();
                                                            #line 3569 "PrintJava.cpp"
  append(L"getNonterminalName(id));\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    private void startElement(String name)\n");
  append(L"    {\n");
  append(L"      try\n");
  append(L"      {\n");
  append(L"        builder.startElement(new NoNamespaceName(name), anyType, ");
                                                            #line 2391 "PrintJava.cpp.template"
                                                                  if (saxon != 99)
                                                                  {
                                                            #line 3581 "PrintJava.cpp"
  append(L"NO_ATTRIBUTES, NO_NAMESPACES, ");
                                                            #line 2393 "PrintJava.cpp.template"
                                                                  }
                                                            #line 3585 "PrintJava.cpp"
  append(L"LOCATION, 0);\n");
  append(L"      }\n");
  append(L"      catch (XPathException e)\n");
  append(L"      {\n");
  append(L"        throw new RuntimeException(e);\n");
  append(L"      }\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    @Override\n");
  append(L"    public void endNonterminal(int id, int end)\n");
  append(L"    {\n");
  append(L"      endElement();\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    private void endElement()\n");
  append(L"    {\n");
  append(L"      try\n");
  append(L"      {\n");
  append(L"        builder.endElement();\n");
  append(L"      }\n");
  append(L"      catch (XPathException e)\n");
  append(L"      {\n");
  append(L"        throw new RuntimeException(e);\n");
  append(L"      }\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    @Override\n");
  append(L"    public void terminal(int id, int begin, int end)\n");
  append(L"    {\n");
  append(L"      String name = ");
                                                            #line 2423 "PrintJava.cpp.template"
                                                                  printNamesPrefix();
                                                            #line 3618 "PrintJava.cpp"
  append(L"getTerminalName(id);\n");
  append(L"      if (name.charAt(0) == '\\'')\n");
  append(L"      {\n");
  append(L"        name = \"TOKEN\";\n");
  append(L"      }\n");
  append(L"      startElement(name);\n");
  append(L"      characters(begin, end);\n");
  append(L"      endElement();\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    @Override\n");
  append(L"    public void whitespace(int begin, int end)\n");
  append(L"    {\n");
  append(L"      characters(begin, end);\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    private void characters(int begin, int end)\n");
  append(L"    {\n");
  append(L"      if (begin < end)\n");
  append(L"      {\n");
  append(L"        try\n");
  append(L"        {\n");
  append(L"          builder.characters(");
                                                            #line 2446 "PrintJava.cpp.template"
                                                                  if (saxon == 110)
                                                                  {
                                                            #line 3645 "PrintJava.cpp"
  append(L"StringView.of(");
                                                            #line 2448 "PrintJava.cpp.template"
                                                                  }
                                                                  if (codepoints)
                                                                  {
                                                                    print(substring());
                                                                    if (saxon == 110)
                                                                    {
                                                            #line 3654 "PrintJava.cpp"
  append(L")");
                                                            #line 2454 "PrintJava.cpp.template"
                                                                    }
                                                                  }
                                                                  else
                                                                  {
                                                            #line 3661 "PrintJava.cpp"
  append(L"input.subSequence(begin, end)");
                                                            #line 2458 "PrintJava.cpp.template"
                                                                    if (saxon == 110)
                                                                    {
                                                            #line 3666 "PrintJava.cpp"
  append(L".toString())");
                                                            #line 2461 "PrintJava.cpp.template"
                                                                    }
                                                                  }
                                                            #line 3671 "PrintJava.cpp"
  append(L", LOCATION, 0);\n");
  append(L"        }\n");
  append(L"        catch (XPathException e)\n");
  append(L"        {\n");
  append(L"          throw new RuntimeException(e);\n");
  append(L"        }\n");
  append(L"      }\n");
  append(L"    }\n");
  append(L"  }\n");
                                                            #line 2472 "PrintJava.cpp.template"
                                                                }
                                                                if (isLrParser)
                                                                {
                                                            #line 3685 "PrintJava.cpp"
  append(L"\n");
  append(L"  public static class ParseTreeBuilder implements BottomUpEventHandler\n");
  append(L"  {\n");
  append(L"    private ");
                                                            #line 2478 "PrintJava.cpp.template"
                                                                  print(inputType());
                                                            #line 3692 "PrintJava.cpp"
  append(L" input;\n");
  append(L"    public Symbol[] stack = new Symbol[64];\n");
  append(L"    public int top = -1;\n");
  append(L"\n");
  append(L"    @Override\n");
  append(L"    public void reset(");
                                                            #line 2484 "PrintJava.cpp.template"
                                                                  print(inputType());
                                                            #line 3701 "PrintJava.cpp"
  append(L" input)\n");
  append(L"    {\n");
  append(L"      this.input = input;\n");
  append(L"      top = -1;\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    @Override\n");
  append(L"    public void nonterminal(int id, int begin, int end, int count)\n");
  append(L"    {");
                                                            #line 2493 "PrintJava.cpp.template"
                                                                  if (rejectsAmbiguity())
                                                                  {
                                                            #line 3714 "PrintJava.cpp"
  append(L"\n");
  append(L"      if (count > top + 1)\n");
  append(L"      {\n");
  append(L"        Symbol[] content = pop(top + 1);\n");
  append(L"        nonterminal(");
                                                            #line 2499 "PrintJava.cpp.template"
                                                                    print(format.toString<wchar_t>(Grammar::syntheticNonterminalCode(2)));
                                                            #line 3722 "PrintJava.cpp"
  append(L", begin, content.length == 0 ? end : content[0].begin, 0);\n");
  append(L"        for (Symbol symbol : content)\n");
  append(L"        {\n");
  append(L"          push(symbol);\n");
  append(L"        }\n");
  append(L"        count = top + 1;\n");
  append(L"      }");
                                                            #line 2506 "PrintJava.cpp.template"
                                                                  }
                                                            #line 3732 "PrintJava.cpp"
  append(L"\n");
  append(L"      push(new Nonterminal(id, begin, end, pop(count)));\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    @Override\n");
  append(L"    public void terminal(int id, int begin, int end)\n");
  append(L"    {\n");
  append(L"      push(new Terminal(id, begin, end));\n");
  append(L"    }");
                                                            #line 2515 "PrintJava.cpp.template"
                                                                  if (resolvesAmbiguity)
                                                                  {
                                                            #line 3745 "PrintJava.cpp"
  append(L"\n");
  append(L"\n");
  append(L"    @Override\n");
  append(L"    public void ambiguity(int begin, int end)\n");
  append(L"    {\n");
  append(L"    }");
                                                            #line 2522 "PrintJava.cpp.template"
                                                                  }
                                                            #line 3754 "PrintJava.cpp"
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
  append(L"      if (++top >= stack.length)\n");
  append(L"      {\n");
  append(L"        stack = Arrays.copyOf(stack, stack.length << 1);\n");
  append(L"      }\n");
  append(L"      stack[top] = s;\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    public Symbol[] pop(int count)\n");
  append(L"    {\n");
  append(L"      top -= count;\n");
  append(L"      return Arrays.copyOfRange(stack, top + 1, top + count + 1);\n");
  append(L"    }\n");
  append(L"  }\n");
                                                            #line 2549 "PrintJava.cpp.template"
                                                                }
                                                              }
                                                              if (saxon)
                                                              {
                                                                const wchar_t *visibility = interfaceName.empty() ? L"private" : L"public";
                                                                if (saxon == 99)
                                                                {
                                                            #line 3789 "PrintJava.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 2557 "PrintJava.cpp.template"
                                                                  print(visibility);
                                                            #line 3794 "PrintJava.cpp"
  append(L" static final Location LOCATION = ExplicitLocation.UNKNOWN_LOCATION;\n");
                                                            #line 2559 "PrintJava.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 3800 "PrintJava.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 2563 "PrintJava.cpp.template"
                                                                  print(visibility);
                                                            #line 3805 "PrintJava.cpp"
  append(L" static final AttributeMap NO_ATTRIBUTES = EmptyAttributeMap.getInstance();\n");
  append(L"  ");
                                                            #line 2565 "PrintJava.cpp.template"
                                                                  print(visibility);
                                                            #line 3810 "PrintJava.cpp"
  append(L" static final NamespaceMap NO_NAMESPACES = NamespaceMap.emptyMap();\n");
  append(L"  ");
                                                            #line 2567 "PrintJava.cpp.template"
                                                                  print(visibility);
                                                            #line 3815 "PrintJava.cpp"
  append(L" static final Location LOCATION = Loc.NONE;\n");
                                                            #line 2569 "PrintJava.cpp.template"
                                                                }
                                                              }
                                                            }

                                                            /* Saxon extension function definition for match()
                                                             * did not show a performance difference. Strange...
                                                            #line 3824 "PrintJava.cpp"
  append(L"\n");
  append(L"  public static class MatchDefinition extends ExtensionFunctionDefinition implements Initializer\n");
  append(L"  {\n");
  append(L"    private static final long serialVersionUID = 1L;\n");
  append(L"\n");
  append(L"    public void initialize(Configuration conf) {conf.registerExtensionFunction(this);}\n");
  append(L"    public StructuredQName getFunctionQName() {return new StructuredQName(\"p\", \"");
                                                            #line 2582 "PrintJava.cpp.template"
                                                            if (! packageName.empty())
                                                            {
                                                              for (size_t i = 0; i < packageName.size(); ++i)
                                                              {
                                                                print(packageName[i] == L'.' ? L'/' : packageName[i]);
                                                              }
                                                            #line 3839 "PrintJava.cpp"
  append(L"/");
                                                            #line 2589 "PrintJava.cpp.template"
                                                            }
                                                            print(className.c_str());
                                                            #line 3844 "PrintJava.cpp"
  append(L"\", \"match\");}\n");
  append(L"    public SequenceType[] getArgumentTypes() {return new SequenceType[] {SequenceType.SINGLE_STRING, SequenceType.SINGLE_INTEGER, SequenceType.SINGLE_INTEGER};}\n");
  append(L"    public SequenceType getResultType(SequenceType[] suppliedArgumentTypes) {return SequenceType.NUMERIC_SEQUENCE;}\n");
  append(L"\n");
  append(L"    public ExtensionFunctionCall makeCallExpression()\n");
  append(L"    {\n");
  append(L"      return new ExtensionFunctionCall()\n");
  append(L"      {\n");
  append(L"        private ");
                                                            #line 2599 "PrintJava.cpp.template"
                                                            print(className.c_str());
                                                            #line 3856 "PrintJava.cpp"
  append(L" parser = new ");
                                                            #line 2600 "PrintJava.cpp.template"
                                                            print(className.c_str());
                                                            #line 3860 "PrintJava.cpp"
  append(L"();\n");
  append(L"        Item[] result = new Item[3];\n");
  append(L"\n");
  append(L"        @SuppressWarnings(\"rawtypes\")\n");
  append(L"        public SequenceIterator<? extends Item> call(SequenceIterator<? extends Item>[] arguments, XPathContext context) throws XPathException\n");
  append(L"        {\n");
  append(L"          String input = ((StringValue) arguments[0].next()).getStringValue();\n");
  append(L"          int begin = (int) ((IntegerValue) arguments[1].next()).longValue() - 1;\n");
  append(L"          int set = (int) ((IntegerValue) arguments[2].next()).longValue();\n");
  append(L"\n");
  append(L"          parser.input = input;\n");
  append(L"          parser.size = input.length();\n");
  append(L"          parser.end = begin;\n");
  append(L"          int token = parser.match(set);\n");
  append(L"\n");
  append(L"          result[0] = IntegerValue.makeIntegerValue((double) token).asAtomic();\n");
  append(L"          result[1] = IntegerValue.makeIntegerValue((double) parser.begin + 1).asAtomic();\n");
  append(L"          result[2] = IntegerValue.makeIntegerValue((double) parser.end + 1).asAtomic();\n");
  append(L"          return new ArrayIterator<Item>(result);\n");
  append(L"        }\n");
  append(L"      };\n");
  append(L"    }\n");
  append(L"  }\n");
                                                            #line 2624 "PrintJava.cpp.template"
                                                            */

// End
