// This file was generated on Sun Nov 24, 2024 16:09 (UTC+01) by REx v6.0 which is Copyright (c) 1979-2024 by Gunther Rademacher <grd@gmx.net>
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
                                                                if (trace || (tree && (main || useGlr)))
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
                                                            #line 73 "PrintJava.cpp.template"
                                                                  if (interfaceName.empty())
                                                                  {
                                                            #line 115 "PrintJava.cpp"
  append(L"\n");
  append(L"import net.sf.saxon.expr.parser.ExplicitLocation;\n");
  append(L"import net.sf.saxon.expr.parser.Location;");
                                                            #line 77 "PrintJava.cpp.template"
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
                                                            #line 99 "PrintJava.cpp.template"
                                                                  if (! tree)
                                                                  {
                                                            #line 146 "PrintJava.cpp"
  append(L"\n");
  append(L"import net.sf.saxon.value.EmptySequence;");
                                                            #line 102 "PrintJava.cpp.template"
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
                                                            #line 110 "PrintJava.cpp.template"
                                                                  }
                                                                  if (saxon == 110)
                                                                  {
                                                            #line 164 "PrintJava.cpp"
  append(L"\n");
  append(L"import net.sf.saxon.str.StringView;");
                                                            #line 114 "PrintJava.cpp.template"
                                                                  }
                                                                }
                                                                if (grammar->basex)
                                                                {
                                                            #line 172 "PrintJava.cpp"
  append(L"\n");
  append(L"import org.basex.build.MemBuilder;\n");
  append(L"import org.basex.build.SingleParser;\n");
  append(L"import org.basex.core.MainOptions;\n");
  append(L"import org.basex.io.IOContent;\n");
  append(L"import org.basex.query.value.item.Str;\n");
  append(L"import org.basex.query.value.node.ANode;\n");
  append(L"import org.basex.query.value.node.DBNode;\n");
  append(L"import org.basex.util.Atts;\n");
  append(L"import org.basex.util.Token;");
                                                            #line 127 "PrintJava.cpp.template"
                                                                }
                                                                if (initialOutputSize != size())
                                                                {
                                                            #line 187 "PrintJava.cpp"
  append(L"\n");
                                                            #line 131 "PrintJava.cpp.template"
                                                                }
                                                            #line 191 "PrintJava.cpp"
  append(L"\n");
  append(L"public class ");
                                                            #line 133 "PrintJava.cpp.template"
                                                                print(className.c_str());
                                                                if (! interfaceName.empty())
                                                                {
                                                            #line 198 "PrintJava.cpp"
  append(L" implements ");
                                                            #line 136 "PrintJava.cpp.template"
                                                                  print(interfaceName.c_str());
                                                                }
                                                            #line 203 "PrintJava.cpp"
  append(L"\n");
  append(L"{");
                                                            #line 139 "PrintJava.cpp.template"
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
                                                            #line 147 "PrintJava.cpp.template"
                                                                print(className.c_str());
                                                                if (tree)
                                                                {
                                                            #line 221 "PrintJava.cpp"
  append(L" [-i]");
                                                            #line 150 "PrintJava.cpp.template"
                                                                }
                                                            #line 225 "PrintJava.cpp"
  append(L" INPUT...\");\n");
  append(L"      System.out.println();\n");
  append(L"      System.out.println(\"  parse INPUT, which is either a filename or literal text enclosed in curly braces\");");
                                                            #line 154 "PrintJava.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 232 "PrintJava.cpp"
  append(L"\n");
  append(L"      System.out.println();\n");
  append(L"      System.out.println(\"  Option:\");\n");
  append(L"      System.out.println(\"    -i     indented parse tree\");");
                                                            #line 159 "PrintJava.cpp.template"
                                                                }
                                                            #line 239 "PrintJava.cpp"
  append(L"\n");
  append(L"    }\n");
  append(L"    else\n");
  append(L"    {");
                                                            #line 163 "PrintJava.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 247 "PrintJava.cpp"
  append(L"\n");
  append(L"      boolean indent = false;");
                                                            #line 166 "PrintJava.cpp.template"
                                                                }
                                                            #line 252 "PrintJava.cpp"
  append(L"\n");
  append(L"      for (String arg : args)\n");
  append(L"      {");
                                                            #line 169 "PrintJava.cpp.template"
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
  append(L"        XmlSerializer s = new XmlSerializer(w, indent);");
                                                            #line 178 "PrintJava.cpp.template"
                                                                  if (isLrParser)
                                                                  {
                                                            #line 271 "PrintJava.cpp"
  append(L"\n");
  append(L"        ParseTreeBuilder b = new ParseTreeBuilder();");
                                                            #line 181 "PrintJava.cpp.template"
                                                                  }
                                                                }
                                                            #line 277 "PrintJava.cpp"
  append(L"\n");
  append(L"        String input = read(arg);\n");
  append(L"        ");
                                                            #line 185 "PrintJava.cpp.template"
                                                                print(className.c_str());
                                                            #line 283 "PrintJava.cpp"
  append(L" parser = new ");
                                                            #line 186 "PrintJava.cpp.template"
                                                                print(className.c_str());
                                                            #line 287 "PrintJava.cpp"
  append(L"(input");
                                                            #line 187 "PrintJava.cpp.template"
                                                                if (noLexer)
                                                                {
                                                            #line 292 "PrintJava.cpp"
  append(L", new ");
                                                            #line 189 "PrintJava.cpp.template"
                                                                  print(className.c_str());
                                                            #line 296 "PrintJava.cpp"
  append(L"Lexer()");
                                                            #line 190 "PrintJava.cpp.template"
                                                                }
                                                                if (tree)
                                                                {
                                                            #line 302 "PrintJava.cpp"
  append(L", ");
                                                            #line 193 "PrintJava.cpp.template"
                                                                  if (isLrParser)
                                                                  {
                                                            #line 307 "PrintJava.cpp"
  append(L"b");
                                                            #line 195 "PrintJava.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 313 "PrintJava.cpp"
  append(L"s");
                                                            #line 198 "PrintJava.cpp.template"
                                                                  }
                                                                }
                                                            #line 318 "PrintJava.cpp"
  append(L");\n");
  append(L"        try\n");
  append(L"        {");
                                                            #line 202 "PrintJava.cpp.template"
                                                                #if 0
                                                                if (grammar->tables && grammar->k >= grammar->tables)
                                                                {
                                                            #line 326 "PrintJava.cpp"
  append(L"\n");
  append(L"          parser.begin = -1;\n");
  append(L"//        if (begin >= 0) System.out.println(\"predict(\" + dpi + \")[\" + TOKEN[l1] + \", \" + TOKEN[l2] + \"] = \" + lk);\n");
  append(L"\n");
  append(L"          for (int p = 0; p < ");
                                                            #line 209 "PrintJava.cpp.template"
                                                                  print(format.toString<wchar_t>(grammar->caseidTable->getRows()));
                                                            #line 334 "PrintJava.cpp"
  append(L"; ++p)\n");
  append(L"          {\n");
  append(L"            int count = 0;");
                                                            #line 213 "PrintJava.cpp.template"
                                                                  for (size_t i = 1; i <= grammar->k; ++i)
                                                                  {
                                                            #line 341 "PrintJava.cpp"
  append(L"\n");
  append(L"            for (parser.l");
                                                            #line 216 "PrintJava.cpp.template"
                                                                    print(format.toString<wchar_t>(i));
                                                            #line 346 "PrintJava.cpp"
  append(L" = 1; parser.l");
                                                            #line 217 "PrintJava.cpp.template"
                                                                    print(format.toString<wchar_t>(i));
                                                            #line 350 "PrintJava.cpp"
  append(L" < TOKEN.length; ++parser.l");
                                                            #line 219 "PrintJava.cpp.template"
                                                                    print(format.toString<wchar_t>(i));
                                                            #line 354 "PrintJava.cpp"
  append(L")");
                                                            #line 221 "PrintJava.cpp.template"
                                                                  }
                                                            #line 358 "PrintJava.cpp"
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
                                                            #line 239 "PrintJava.cpp.template"
                                                                }
                                                                #endif

                                                                if (trace)
                                                                {
                                                            #line 381 "PrintJava.cpp"
  append(L"\n");
  append(L"          parser.writeTrace(\"<?xml version=\\\"1.0\\\" encoding=\\\"UTF-8\\\"?\" + \">\\n<trace>\\n\");");
                                                            #line 246 "PrintJava.cpp.template"
                                                                }
                                                            #line 386 "PrintJava.cpp"
  append(L"\n");
  append(L"          parser.");
                                                            #line 248 "PrintJava.cpp.template"
                                                                print(methodPrefixParse);
                                                                print(Format::acceptableName<WString>(grammar->startSymbol()->name).c_str());
                                                            #line 392 "PrintJava.cpp"
  append(L"();");
                                                            #line 250 "PrintJava.cpp.template"
                                                                if (trace)
                                                                {
                                                            #line 397 "PrintJava.cpp"
  append(L"\n");
  append(L"          parser.writeTrace(\"</trace>\\n\");");
                                                            #line 253 "PrintJava.cpp.template"
                                                                }
                                                                if (tree && isLrParser)
                                                                {
                                                            #line 404 "PrintJava.cpp"
  append(L"\n");
  append(L"          b.serialize(s);");
                                                            #line 257 "PrintJava.cpp.template"
                                                                }
                                                            #line 409 "PrintJava.cpp"
  append(L"\n");
  append(L"        }\n");
  append(L"        catch (ParseException pe)\n");
  append(L"        {");
                                                            #line 261 "PrintJava.cpp.template"
                                                                if (useGlr && tree)
                                                                {
                                                            #line 417 "PrintJava.cpp"
  append(L"\n");
  append(L"          if (pe.isAmbiguousInput())\n");
  append(L"          {\n");
  append(L"            pe.serialize(s);\n");
  append(L"            w.write(\"\\n\");\n");
  append(L"            w.flush();\n");
  append(L"          }");
                                                            #line 269 "PrintJava.cpp.template"
                                                                }
                                                            #line 427 "PrintJava.cpp"
  append(L"\n");
  append(L"          throw new RuntimeException(\"ParseException while processing \" + arg + \":\\n\" + parser.getErrorMessage(pe));\n");
  append(L"        }");
                                                            #line 272 "PrintJava.cpp.template"
                                                                if (tree || trace)
                                                                {
                                                            #line 434 "PrintJava.cpp"
  append(L"\n");
  append(L"        finally\n");
  append(L"        {");
                                                            #line 276 "PrintJava.cpp.template"
                                                                }
                                                                if (trace)
                                                                {
                                                            #line 442 "PrintJava.cpp"
  append(L"\n");
  append(L"          parser.flushTrace();");
                                                            #line 280 "PrintJava.cpp.template"
                                                                }
                                                                if (tree)
                                                                {
                                                            #line 449 "PrintJava.cpp"
  append(L"\n");
  append(L"          w.close();");
                                                            #line 284 "PrintJava.cpp.template"
                                                                }
                                                                if (tree || trace)
                                                                {
                                                            #line 456 "PrintJava.cpp"
  append(L"\n");
  append(L"        }");
                                                            #line 288 "PrintJava.cpp.template"
                                                                }
                                                            #line 461 "PrintJava.cpp"
  append(L"\n");
  append(L"      }\n");
  append(L"    }\n");
  append(L"  }\n");
                                                            #line 293 "PrintJava.cpp.template"
                                                              }
                                                              if (interfaceName.empty())
                                                              {
                                                                printParseException();
                                                                printEventHandlerImplementation();
                                                              }
                                                              if (saxon)
                                                              {
                                                            #line 475 "PrintJava.cpp"
  append(L"\n");
  append(L"  public static class SaxonInitializer implements Initializer\n");
  append(L"  {\n");
  append(L"    @Override\n");
  append(L"    public void initialize(Configuration conf)\n");
  append(L"    {");
                                                            #line 307 "PrintJava.cpp.template"
                                                                for (Node *n = grammar->nonTerminals; n; n = n->followingSibling)
                                                                {
                                                                  Production *p = static_cast <Production *> (n);
                                                                  if (p->isStartSymbol())
                                                                  {
                                                            #line 488 "PrintJava.cpp"
  append(L"\n");
  append(L"      conf.registerExtensionFunction(new SaxonDefinition_");
                                                            #line 313 "PrintJava.cpp.template"
                                                                    print(Format::acceptableName<WString>(p->name).c_str());
                                                            #line 493 "PrintJava.cpp"
  append(L"());");
                                                            #line 314 "PrintJava.cpp.template"
                                                                  }
                                                                }
                                                            #line 498 "PrintJava.cpp"
  append(L"\n");
  append(L"    }\n");
  append(L"  }\n");
                                                            #line 320 "PrintJava.cpp.template"
                                                                for (Node *n = grammar->nonTerminals; n; n = n->followingSibling)
                                                                {
                                                                  Production *p = static_cast <Production *> (n);
                                                                  if (p->isStartSymbol())
                                                                  {
                                                            #line 508 "PrintJava.cpp"
  append(L"\n");
  append(L"  public static Sequence");
                                                            #line 326 "PrintJava.cpp.template"
                                                                    if (saxon == 99)
                                                                    {
                                                            #line 514 "PrintJava.cpp"
  append(L"<?>");
                                                            #line 328 "PrintJava.cpp.template"
                                                                    }
                                                            #line 518 "PrintJava.cpp"
  append(L" parse");
                                                            #line 329 "PrintJava.cpp.template"
                                                                    WString acceptableName = Format::acceptableName<WString>(p->name);
                                                                    const wchar_t *name = acceptableName.c_str();
                                                                    wchar_t initial = towupper(*name);
                                                                    print(&initial, 1);
                                                                    print(name + 1);
                                                            #line 526 "PrintJava.cpp"
  append(L"(XPathContext context, String input) throws XPathException\n");
  append(L"  {\n");
  append(L"    Builder builder = context.getController().makeBuilder();");
                                                            #line 336 "PrintJava.cpp.template"
                                                                    if (tree & isLrParser)
                                                                    {
                                                            #line 533 "PrintJava.cpp"
  append(L"\n");
  append(L"    ParseTreeBuilder bottomUpTreeBuilder = new ParseTreeBuilder();");
                                                            #line 339 "PrintJava.cpp.template"
                                                                    }
                                                            #line 538 "PrintJava.cpp"
  append(L"\n");
  append(L"    builder.open();\n");
  append(L"    ");
                                                            #line 342 "PrintJava.cpp.template"
                                                                    print(className.c_str());
                                                            #line 544 "PrintJava.cpp"
  append(L" parser = new ");
                                                            #line 344 "PrintJava.cpp.template"
                                                                    print(className.c_str());
                                                            #line 548 "PrintJava.cpp"
  append(L"(input");
                                                            #line 345 "PrintJava.cpp.template"
                                                                    if (noLexer)
                                                                    {
                                                            #line 553 "PrintJava.cpp"
  append(L", new ");
                                                            #line 347 "PrintJava.cpp.template"
                                                                      print(className.c_str());
                                                            #line 557 "PrintJava.cpp"
  append(L"Lexer()");
                                                            #line 348 "PrintJava.cpp.template"
                                                                    }
                                                                    if (tree)
                                                                    {
                                                                      if (isLrParser)
                                                                      {
                                                            #line 565 "PrintJava.cpp"
  append(L", bottomUpTreeBuilder");
                                                            #line 353 "PrintJava.cpp.template"
                                                                      }
                                                                      else
                                                                      {
                                                            #line 571 "PrintJava.cpp"
  append(L", new SaxonTreeBuilder(builder)");
                                                            #line 356 "PrintJava.cpp.template"
                                                                      }
                                                                    }
                                                            #line 576 "PrintJava.cpp"
  append(L");\n");
  append(L"    try\n");
  append(L"    {\n");
  append(L"      parser.parse_");
                                                            #line 361 "PrintJava.cpp.template"
                                                                    print(Format::acceptableName<WString>(p->name).c_str());
                                                            #line 583 "PrintJava.cpp"
  append(L"();");
                                                            #line 362 "PrintJava.cpp.template"
                                                                    if (! tree)
                                                                    {
                                                            #line 588 "PrintJava.cpp"
  append(L"\n");
  append(L"      return EmptySequence.getInstance();");
                                                            #line 365 "PrintJava.cpp.template"
                                                                    }
                                                                    else if (isLrParser)
                                                                    {
                                                            #line 595 "PrintJava.cpp"
  append(L"\n");
  append(L"      bottomUpTreeBuilder.serialize(new SaxonTreeBuilder(builder));");
                                                            #line 370 "PrintJava.cpp.template"
                                                                    }
                                                            #line 600 "PrintJava.cpp"
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
                                                            #line 380 "PrintJava.cpp.template"
                                                                    print(Format::acceptableName<WString>(p->name).c_str());
                                                            #line 613 "PrintJava.cpp"
  append(L" extends SaxonDefinition\n");
  append(L"  {\n");
  append(L"    @Override\n");
  append(L"    public String functionName() {return \"parse-");
                                                            #line 384 "PrintJava.cpp.template"
                                                                    print(p->name);
                                                            #line 620 "PrintJava.cpp"
  append(L"\";}\n");
  append(L"    @Override\n");
  append(L"    public Sequence");
                                                            #line 387 "PrintJava.cpp.template"
                                                                    if (saxon == 99)
                                                                    {
                                                            #line 627 "PrintJava.cpp"
  append(L"<?>");
                                                            #line 389 "PrintJava.cpp.template"
                                                                    }
                                                            #line 631 "PrintJava.cpp"
  append(L" execute(XPathContext context, String input) throws XPathException\n");
  append(L"    {\n");
  append(L"      return parse");
                                                            #line 392 "PrintJava.cpp.template"
                                                                    print(&initial, 1);
                                                                    print(name + 1);
                                                            #line 638 "PrintJava.cpp"
  append(L"(context, input);\n");
  append(L"    }\n");
  append(L"  }\n");
                                                            #line 397 "PrintJava.cpp.template"
                                                                  }
                                                                }
                                                            #line 645 "PrintJava.cpp"
  append(L"\n");
  append(L"  public static abstract class SaxonDefinition extends ExtensionFunctionDefinition\n");
  append(L"  {\n");
  append(L"    abstract String functionName();\n");
  append(L"    abstract Sequence");
                                                            #line 403 "PrintJava.cpp.template"
                                                                if (saxon == 99)
                                                                {
                                                            #line 654 "PrintJava.cpp"
  append(L"<?>");
                                                            #line 405 "PrintJava.cpp.template"
                                                                }
                                                            #line 658 "PrintJava.cpp"
  append(L" execute(XPathContext context, String input) throws XPathException;\n");
  append(L"\n");
  append(L"    @Override\n");
  append(L"    public StructuredQName getFunctionQName() {return new StructuredQName(\"p\", \"");
                                                            #line 410 "PrintJava.cpp.template"
                                                                if (! packageName.empty())
                                                                {
                                                                  for (size_t i = 0; i < packageName.size(); ++i)
                                                                  {
                                                                    print(packageName[i] == L'.' ? L'/' : packageName[i]);
                                                                  }
                                                            #line 670 "PrintJava.cpp"
  append(L"/");
                                                            #line 417 "PrintJava.cpp.template"
                                                                }
                                                                print(className.c_str());
                                                            #line 675 "PrintJava.cpp"
  append(L"\", functionName());}\n");
  append(L"    @Override\n");
  append(L"    public SequenceType[] getArgumentTypes() {return new SequenceType[] {SequenceType.SINGLE_STRING};}\n");
  append(L"    @Override\n");
  append(L"    public SequenceType getResultType(SequenceType[] suppliedArgumentTypes) {return SequenceType.");
                                                            #line 424 "PrintJava.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 684 "PrintJava.cpp"
  append(L"SINGLE");
                                                            #line 427 "PrintJava.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 690 "PrintJava.cpp"
  append(L"OPTIONAL");
                                                            #line 431 "PrintJava.cpp.template"
                                                                }
                                                            #line 694 "PrintJava.cpp"
  append(L"_NODE;}\n");
  append(L"\n");
  append(L"    @Override\n");
  append(L"    public ExtensionFunctionCall makeCallExpression()\n");
  append(L"    {\n");
  append(L"      return new ExtensionFunctionCall()\n");
  append(L"      {\n");
  append(L"        @Override\n");
  append(L"        public Sequence");
                                                            #line 440 "PrintJava.cpp.template"
                                                                if (saxon == 99)
                                                                {
                                                            #line 707 "PrintJava.cpp"
  append(L"<?>");
                                                            #line 442 "PrintJava.cpp.template"
                                                                }
                                                            #line 711 "PrintJava.cpp"
  append(L" call(XPathContext context, ");
                                                            #line 443 "PrintJava.cpp.template"
                                                                if (saxon == 99)
                                                                {
                                                            #line 716 "PrintJava.cpp"
  append(L"@SuppressWarnings(\"rawtypes\") ");
                                                            #line 446 "PrintJava.cpp.template"
                                                                }
                                                            #line 720 "PrintJava.cpp"
  append(L"Sequence[] arguments) throws XPathException\n");
  append(L"        {\n");
  append(L"          return execute(context, arguments[0].iterate().next().getStringValue());\n");
  append(L"        }\n");
  append(L"      };\n");
  append(L"    }\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  private static void buildError(");
                                                            #line 455 "PrintJava.cpp.template"
                                                                print(className.c_str());
                                                            #line 732 "PrintJava.cpp"
  append(L" parser, ParseException pe, Builder builder) throws XPathException\n");
  append(L"  {\n");
  append(L"    builder.close();\n");
  append(L"    builder.reset();\n");
  append(L"    builder.open();");
                                                            #line 460 "PrintJava.cpp.template"
                                                                if (saxon == 99)
                                                                {
                                                            #line 741 "PrintJava.cpp"
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
                                                            #line 476 "PrintJava.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 760 "PrintJava.cpp"
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
                                                            #line 494 "PrintJava.cpp.template"
                                                                }
                                                            #line 778 "PrintJava.cpp"
  append(L"\n");
  append(L"    builder.characters(");
                                                            #line 496 "PrintJava.cpp.template"
                                                                if (saxon == 110)
                                                                {
                                                            #line 784 "PrintJava.cpp"
  append(L"StringView.of(");
                                                            #line 498 "PrintJava.cpp.template"
                                                                }
                                                            #line 788 "PrintJava.cpp"
  append(L"parser.getErrorMessage(pe)");
                                                            #line 499 "PrintJava.cpp.template"
                                                                if (saxon == 110)
                                                                {
                                                            #line 793 "PrintJava.cpp"
  append(L")");
                                                            #line 501 "PrintJava.cpp.template"
                                                                }
                                                            #line 797 "PrintJava.cpp"
  append(L", LOCATION, 0);\n");
  append(L"    builder.endElement();\n");
  append(L"  }\n");
                                                            #line 505 "PrintJava.cpp.template"
                                                              }
                                                              if (grammar->basex)
                                                              {
                                                                for (Node *n = grammar->nonTerminals; n; n = n->followingSibling)
                                                                {
                                                                  Production *p = static_cast <Production *> (n);
                                                                  if (p->isStartSymbol())
                                                                  {
                                                            #line 810 "PrintJava.cpp"
  append(L"\n");
  append(L"  public static ANode parse");
                                                            #line 514 "PrintJava.cpp.template"
                                                                    WString acceptableName = Format::acceptableName<WString>(p->name).c_str();
                                                                    const wchar_t *name = acceptableName.c_str();
                                                                    wchar_t initial = towupper(*name);
                                                                    print(&initial, 1);
                                                                    print(name + 1);
                                                            #line 819 "PrintJava.cpp"
  append(L"(Str str) throws IOException\n");
  append(L"  {\n");
  append(L"    BaseXFunction baseXFunction = new BaseXFunction()\n");
  append(L"    {\n");
  append(L"      @Override\n");
  append(L"      public void execute(");
                                                            #line 524 "PrintJava.cpp.template"
                                                                    print(className.c_str());
                                                            #line 828 "PrintJava.cpp"
  append(L" p) {p.parse_");
                                                            #line 525 "PrintJava.cpp.template"
                                                                    print(Format::acceptableName<WString>(p->name).c_str());
                                                            #line 832 "PrintJava.cpp"
  append(L"();}\n");
  append(L"    };\n");
  append(L"    return baseXFunction.call(str);\n");
  append(L"  }\n");
                                                            #line 530 "PrintJava.cpp.template"
                                                                  }
                                                                }
                                                            #line 840 "PrintJava.cpp"
  append(L"\n");
  append(L"  public static abstract class BaseXFunction\n");
  append(L"  {\n");
  append(L"    protected abstract void execute(");
                                                            #line 535 "PrintJava.cpp.template"
                                                                print(className.c_str());
                                                            #line 847 "PrintJava.cpp"
  append(L" p);\n");
  append(L"\n");
  append(L"    public ANode call(Str str) throws IOException\n");
  append(L"    {\n");
  append(L"      String input = str.toJava();\n");
  append(L"      SingleParser singleParser = new SingleParser(new IOContent(\"\"), new MainOptions())\n");
  append(L"      {\n");
  append(L"        @Override\n");
  append(L"        protected void parse() throws IOException {}\n");
  append(L"      };\n");
  append(L"      MemBuilder memBuilder = new MemBuilder(input, singleParser);\n");
  append(L"      memBuilder.init();");
                                                            #line 547 "PrintJava.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 863 "PrintJava.cpp"
  append(L"\n");
  append(L"      BaseXTreeBuilder treeBuilder = new BaseXTreeBuilder(memBuilder);");
                                                            #line 551 "PrintJava.cpp.template"
                                                                  if (isLrParser)
                                                                  {
                                                            #line 869 "PrintJava.cpp"
  append(L"\n");
  append(L"      ParseTreeBuilder bottomUpTreeBuilder = new ParseTreeBuilder();");
                                                            #line 555 "PrintJava.cpp.template"
                                                                  }
                                                                }
                                                            #line 875 "PrintJava.cpp"
  append(L"\n");
  append(L"      ");
                                                            #line 558 "PrintJava.cpp.template"
                                                                print(className.c_str());
                                                            #line 880 "PrintJava.cpp"
  append(L" parser = new ");
                                                            #line 559 "PrintJava.cpp.template"
                                                                print(className.c_str());
                                                            #line 884 "PrintJava.cpp"
  append(L"();\n");
  append(L"      parser.initialize(input");
                                                            #line 561 "PrintJava.cpp.template"
                                                                if (noLexer)
                                                                {
                                                            #line 890 "PrintJava.cpp"
  append(L", new ");
                                                            #line 563 "PrintJava.cpp.template"
                                                                   print(className.c_str());
                                                            #line 894 "PrintJava.cpp"
  append(L"Lexer()");
                                                            #line 564 "PrintJava.cpp.template"
                                                                }
                                                                if (tree)
                                                                {
                                                                  if (isLrParser)
                                                                  {
                                                            #line 902 "PrintJava.cpp"
  append(L", bottomUpTreeBuilder");
                                                            #line 569 "PrintJava.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 908 "PrintJava.cpp"
  append(L", treeBuilder");
                                                            #line 572 "PrintJava.cpp.template"
                                                                  }
                                                                }
                                                            #line 913 "PrintJava.cpp"
  append(L");\n");
  append(L"      try\n");
  append(L"      {\n");
  append(L"        execute(parser);");
                                                            #line 577 "PrintJava.cpp.template"
                                                                if (tree)
                                                                {
                                                                  if (isLrParser)
                                                                  {
                                                            #line 923 "PrintJava.cpp"
  append(L"\n");
  append(L"        bottomUpTreeBuilder.serialize(treeBuilder);");
                                                            #line 582 "PrintJava.cpp.template"
                                                                  }
                                                                }
                                                                else
                                                                {
                                                            #line 931 "PrintJava.cpp"
  append(L"\n");
  append(L"        return null;");
                                                            #line 587 "PrintJava.cpp.template"
                                                                }
                                                            #line 936 "PrintJava.cpp"
  append(L"\n");
  append(L"      }\n");
  append(L"      catch (ParseException pe)\n");
  append(L"      {\n");
  append(L"        memBuilder = new MemBuilder(input, singleParser);\n");
  append(L"        memBuilder.init();\n");
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
  append(L"        memBuilder.text(Token.token(parser.getErrorMessage(pe)));\n");
  append(L"        memBuilder.closeElem();\n");
  append(L"      }\n");
  append(L"      return new DBNode(memBuilder.data());\n");
  append(L"    }\n");
  append(L"  }\n");
                                                            #line 614 "PrintJava.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 965 "PrintJava.cpp"
  append(L"\n");
  append(L"  public static class BaseXTreeBuilder implements EventHandler\n");
  append(L"  {\n");
  append(L"    private CharSequence input;\n");
  append(L"    private MemBuilder builder;\n");
  append(L"    private Atts nsp = new Atts();\n");
  append(L"    private Atts atts = new Atts();\n");
  append(L"\n");
  append(L"    public BaseXTreeBuilder(MemBuilder b)\n");
  append(L"    {\n");
  append(L"      input = null;\n");
  append(L"      builder = b;\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    @Override\n");
  append(L"    public void reset(CharSequence string)\n");
  append(L"    {\n");
  append(L"      input = string;\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    @Override\n");
  append(L"    public void startNonterminal(String name, int begin)\n");
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
  append(L"    public void endNonterminal(String name, int end)\n");
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
  append(L"    public void terminal(String name, int begin, int end)\n");
  append(L"    {\n");
  append(L"      if (name.charAt(0) == '\\'')\n");
  append(L"      {\n");
  append(L"        name = \"TOKEN\";\n");
  append(L"      }\n");
  append(L"      startNonterminal(name, begin);\n");
  append(L"      characters(begin, end);\n");
  append(L"      endNonterminal(name, end);\n");
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
  append(L"          builder.text(Token.token(input.subSequence(begin, end).toString()));\n");
  append(L"        }\n");
  append(L"        catch (IOException e)\n");
  append(L"        {\n");
  append(L"          throw new RuntimeException(e);\n");
  append(L"        }\n");
  append(L"      }\n");
  append(L"    }\n");
  append(L"  }\n");
                                                            #line 695 "PrintJava.cpp.template"
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
                                                            #line 1062 "PrintJava.cpp"
  append(L"\n");
  append(L"{\n");
  append(L"}\n");
                                                            #line 714 "PrintJava.cpp.template"
                                                                  decreaseIndent();
                                                                }
                                                                WString args(L"CharSequence string");
                                                                if (noLexer) args += L", Lexer lexer";
                                                                if (tree) args += isLrParser ? L", BottomUpEventHandler t" : L", EventHandler t";
                                                                increaseIndent();
                                                                openMethod(L"", L"", className.c_str(), args.c_str());
                                                            #line 1074 "PrintJava.cpp"
  append(L"\n");
  append(L"{\n");
  append(L"  initialize(string");
                                                            #line 723 "PrintJava.cpp.template"
                                                                if (noLexer)
                                                                {
                                                            #line 1081 "PrintJava.cpp"
  append(L", lexer");
                                                            #line 725 "PrintJava.cpp.template"
                                                                }
                                                                if (tree)
                                                                {
                                                            #line 1087 "PrintJava.cpp"
  append(L", t");
                                                            #line 728 "PrintJava.cpp.template"
                                                                }
                                                            #line 1091 "PrintJava.cpp"
  append(L");\n");
  append(L"}\n");
                                                            #line 731 "PrintJava.cpp.template"
                                                                decreaseIndent();
                                                              }
                                                            }

                                                            void PrintJava::openStackNode()
                                                            {
                                                            #line 1101 "PrintJava.cpp"
  append(L"\n");
  append(L"private static class StackNode\n");
  append(L"{\n");
  append(L"  public int state;");
                                                            #line 741 "PrintJava.cpp.template"
                                                              if (grammar->states->hasLookback)
                                                              {
                                                            #line 1109 "PrintJava.cpp"
  append(L"\n");
  append(L"  public int code;");
                                                            #line 744 "PrintJava.cpp.template"
                                                              }
                                                              if (tree || useGlr)
                                                              {
                                                            #line 1116 "PrintJava.cpp"
  append(L"\n");
  append(L"  public int pos;");
                                                            #line 748 "PrintJava.cpp.template"
                                                              }
                                                            #line 1121 "PrintJava.cpp"
  append(L"\n");
  append(L"  public StackNode link;\n");
  append(L"\n");
  append(L"  public StackNode(int state, ");
                                                            #line 753 "PrintJava.cpp.template"
                                                              if (grammar->states->hasLookback)
                                                              {
                                                            #line 1129 "PrintJava.cpp"
  append(L"int code, ");
                                                            #line 755 "PrintJava.cpp.template"
                                                              }
                                                              if (tree || useGlr)
                                                              {
                                                            #line 1135 "PrintJava.cpp"
  append(L"int pos, ");
                                                            #line 758 "PrintJava.cpp.template"
                                                              }
                                                            #line 1139 "PrintJava.cpp"
  append(L"StackNode link)\n");
  append(L"  {\n");
  append(L"    this.state = state;");
                                                            #line 762 "PrintJava.cpp.template"
                                                              if (grammar->states->hasLookback)
                                                              {
                                                            #line 1146 "PrintJava.cpp"
  append(L"\n");
  append(L"    this.code = code;");
                                                            #line 765 "PrintJava.cpp.template"
                                                              }
                                                              if (tree || useGlr)
                                                              {
                                                            #line 1153 "PrintJava.cpp"
  append(L"\n");
  append(L"    this.pos = pos;");
                                                            #line 769 "PrintJava.cpp.template"
                                                              }
                                                            #line 1158 "PrintJava.cpp"
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
                                                            #line 782 "PrintJava.cpp.template"
                                                              if (grammar->states->hasLookback)
                                                              {
                                                            #line 1175 "PrintJava.cpp"
  append(L"\n");
  append(L"      if (lhs.code != rhs.code) return false;");
                                                            #line 785 "PrintJava.cpp.template"
                                                              }
                                                              if (tree || useGlr)
                                                              {
                                                            #line 1182 "PrintJava.cpp"
  append(L"\n");
  append(L"      if (lhs.pos != rhs.pos) return false;");
                                                            #line 789 "PrintJava.cpp.template"
                                                              }
                                                            #line 1187 "PrintJava.cpp"
  append(L"\n");
  append(L"      lhs = lhs.link;\n");
  append(L"      rhs = rhs.link;\n");
  append(L"    }\n");
  append(L"    return lhs == rhs;\n");
  append(L"  }\n");
                                                            #line 796 "PrintJava.cpp.template"
                                                              increaseIndent();
                                                              beginPublic();
                                                            }

                                                            void PrintJava::closeStackNode()
                                                            {
                                                              beginNonpublic();
                                                              decreaseIndent();
                                                            #line 1203 "PrintJava.cpp"
  append(L"\n");
  append(L"}\n");
                                                            #line 806 "PrintJava.cpp.template"
                                                              if (hasCustomCode)
                                                              {
                                                            #line 1209 "PrintJava.cpp"
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
                                                            #line 824 "PrintJava.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                            #line 1230 "PrintJava.cpp"
  append(L"\n");
  append(L"private abstract static class DeferredEvent\n");
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
  append(L"}\n");
  append(L"\n");
  append(L"public static class TerminalEvent extends DeferredEvent\n");
  append(L"{\n");
  append(L"  public TerminalEvent(DeferredEvent link, String name, int begin, int end)\n");
  append(L"  {\n");
  append(L"    super(link, name, begin, end);\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  @Override\n");
  append(L"  public void execute(BottomUpEventHandler eventHandler)\n");
  append(L"  {\n");
  append(L"    eventHandler.terminal(name, begin, end);\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  @Override\n");
  append(L"  public String toString()\n");
  append(L"  {\n");
  append(L"    return \"terminal(\" + name + \", \" + begin + \", \" + end + \")\";\n");
  append(L"  }\n");
  append(L"}\n");
  append(L"\n");
  append(L"public static class NonterminalEvent extends DeferredEvent\n");
  append(L"{\n");
  append(L"  public int count;\n");
  append(L"\n");
  append(L"  public NonterminalEvent(DeferredEvent link, String name, int begin, int end, int count)\n");
  append(L"  {\n");
  append(L"    super(link, name, begin, end);\n");
  append(L"    this.count = count;\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  @Override\n");
  append(L"  public void execute(BottomUpEventHandler eventHandler)\n");
  append(L"  {\n");
  append(L"    eventHandler.nonterminal(name, begin, end, count);\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  @Override\n");
  append(L"  public String toString()\n");
  append(L"  {\n");
  append(L"    return \"nonterminal(\" + name + \", \" + begin + \", \" + end + \", \" + count + \")\";\n");
  append(L"  }\n");
  append(L"}\n");
                                                            #line 921 "PrintJava.cpp.template"
                                                              }
                                                            #line 1327 "PrintJava.cpp"
  append(L"\n");
  append(L"private static final int PARSING = 0;\n");
  append(L"private static final int ACCEPTED = 1;\n");
  append(L"private static final int ERROR = 2;\n");
  append(L"\n");
  append(L"private ParsingThread parse(int target, int initialState, ");
                                                            #line 927 "PrintJava.cpp.template"
                                                                       if (tree)
                                                              {
                                                            #line 1337 "PrintJava.cpp"
  append(L"BottomUpEventHandler eventHandler, ");
                                                            #line 930 "PrintJava.cpp.template"
                                                              }
                                                            #line 1341 "PrintJava.cpp"
  append(L"ParsingThread thread)\n");
  append(L"{\n");
  append(L"  PriorityQueue<ParsingThread> threads = thread.open(initialState");
                                                            #line 934 "PrintJava.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 1348 "PrintJava.cpp"
  append(L", eventHandler");
                                                            #line 936 "PrintJava.cpp.template"
                                                              }
                                                            #line 1352 "PrintJava.cpp"
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
                                                            #line 955 "PrintJava.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 1375 "PrintJava.cpp"
  append(L", thread.deferredEvent, other.deferredEvent");
                                                            #line 958 "PrintJava.cpp.template"
                                                              }
                                                            #line 1379 "PrintJava.cpp"
  append(L");\n");
  append(L"      }");
                                                            #line 961 "PrintJava.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 1385 "PrintJava.cpp"
  append(L"\n");
  append(L"      if (thread.deferredEvent != null)\n");
  append(L"      {\n");
  append(L"        thread.deferredEvent.release(eventHandler);\n");
  append(L"        thread.deferredEvent = null;\n");
  append(L"      }");
                                                            #line 968 "PrintJava.cpp.template"
                                                              }
                                                              if (hasCustomCode)
                                                              {
                                                            #line 1396 "PrintJava.cpp"
  append(L"\n");
  append(L"      thread.executeDeferredCode();");
                                                            #line 972 "PrintJava.cpp.template"
                                                              }
                                                            #line 1401 "PrintJava.cpp"
  append(L"\n");
  append(L"      return thread;\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    if (! threads.isEmpty())\n");
  append(L"    {\n");
  append(L"      if (threads.peek().equals(thread))\n");
  append(L"      {\n");
  append(L"        rejectAmbiguity(thread.stack.pos, thread.e0");
                                                            #line 981 "PrintJava.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 1414 "PrintJava.cpp"
  append(L", thread.deferredEvent, threads.peek().deferredEvent");
                                                            #line 984 "PrintJava.cpp.template"
                                                              }
                                                            #line 1418 "PrintJava.cpp"
  append(L");\n");
  append(L"      }\n");
  append(L"    }");
                                                            #line 987 "PrintJava.cpp.template"
                                                              if (tree || hasCustomCode)
                                                              {
                                                            #line 1425 "PrintJava.cpp"
  append(L"\n");
  append(L"    else\n");
  append(L"    {");
                                                            #line 991 "PrintJava.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 1432 "PrintJava.cpp"
  append(L"\n");
  append(L"      if (thread.deferredEvent != null)\n");
  append(L"      {\n");
  append(L"        thread.deferredEvent.release(eventHandler);\n");
  append(L"        thread.deferredEvent = null;\n");
  append(L"      }");
                                                            #line 998 "PrintJava.cpp.template"
                                                                }
                                                                if (hasCustomCode)
                                                                {
                                                            #line 1443 "PrintJava.cpp"
  append(L"\n");
  append(L"      thread.executeDeferredCode();");
                                                            #line 1002 "PrintJava.cpp.template"
                                                                }
                                                            #line 1448 "PrintJava.cpp"
  append(L"\n");
  append(L"    }");
                                                            #line 1004 "PrintJava.cpp.template"
                                                              }
                                                            #line 1453 "PrintJava.cpp"
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
                                                            #line 1030 "PrintJava.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 1483 "PrintJava.cpp"
  append(L", DeferredEvent first, DeferredEvent second");
                                                            #line 1033 "PrintJava.cpp.template"
                                                              }
                                                            #line 1487 "PrintJava.cpp"
  append(L")\n");
  append(L"{");
                                                            #line 1035 "PrintJava.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 1493 "PrintJava.cpp"
  append(L"\n");
  append(L"  ParseTreeBuilder treeBuilder = new ParseTreeBuilder();\n");
  append(L"  treeBuilder.reset(input);\n");
  append(L"  second.show(treeBuilder);\n");
  append(L"  treeBuilder.nonterminal(\"ALTERNATIVE\", treeBuilder.stack[0].begin, treeBuilder.stack[treeBuilder.top].end, treeBuilder.top + 1);\n");
  append(L"  Symbol secondTree = treeBuilder.pop(1)[0];\n");
  append(L"  first.show(treeBuilder);\n");
  append(L"  treeBuilder.nonterminal(\"ALTERNATIVE\", treeBuilder.stack[0].begin, treeBuilder.stack[treeBuilder.top].end, treeBuilder.top + 1);\n");
  append(L"  treeBuilder.push(secondTree);\n");
  append(L"  treeBuilder.nonterminal(\"AMBIGUOUS\", treeBuilder.stack[0].begin, treeBuilder.stack[treeBuilder.top].end, 2);");
                                                            #line 1047 "PrintJava.cpp.template"
                                                              }
                                                            #line 1506 "PrintJava.cpp"
  append(L"\n");
  append(L"  throw new ParseException(begin, end");
                                                            #line 1049 "PrintJava.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 1512 "PrintJava.cpp"
  append(L", treeBuilder");
                                                            #line 1051 "PrintJava.cpp.template"
                                                              }
                                                            #line 1516 "PrintJava.cpp"
  append(L");\n");
  append(L"}\n");
  append(L"\n");
  append(L"private ParsingThread thread = new ParsingThread();");
                                                            #line 1055 "PrintJava.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 1524 "PrintJava.cpp"
  append(L"\n");
  append(L"private BottomUpEventHandler eventHandler;");
                                                            #line 1058 "PrintJava.cpp.template"
                                                              }
                                                            #line 1529 "PrintJava.cpp"
  append(L"\n");
  append(L"private CharSequence input = null;\n");
  append(L"private int size = 0;\n");
  append(L"private int maxId = 0;");
                                                            #line 1062 "PrintJava.cpp.template"
                                                              if (trace)
                                                              {
                                                            #line 1537 "PrintJava.cpp"
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
                                                            #line 1073 "PrintJava.cpp.template"
                                                              }
                                                            #line 1550 "PrintJava.cpp"
  append(L"\n");
                                                            #line 1075 "PrintJava.cpp.template"
                                                            }

                                                            void PrintJava::openThread()
                                                            {
                                                            #line 1557 "PrintJava.cpp"
  append(L"\n");
  append(L"private class ParsingThread implements Comparable<ParsingThread>\n");
  append(L"{\n");
  append(L"  public PriorityQueue<ParsingThread> threads;\n");
  append(L"  public boolean accepted;\n");
  append(L"  public StackNode stack;\n");
  append(L"  public int state;\n");
  append(L"  public int action;\n");
  append(L"  public int target;");
                                                            #line 1087 "PrintJava.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 1570 "PrintJava.cpp"
  append(L"\n");
  append(L"  public DeferredEvent deferredEvent;");
                                                            #line 1090 "PrintJava.cpp.template"
                                                              }
                                                              if (hasCustomCode)
                                                              {
                                                            #line 1577 "PrintJava.cpp"
  append(L"\n");
  append(L"  public DeferredCode deferredCode;");
                                                            #line 1094 "PrintJava.cpp.template"
                                                              }
                                                            #line 1582 "PrintJava.cpp"
  append(L"\n");
  append(L"  public int id;\n");
  append(L"\n");
  append(L"  public PriorityQueue<ParsingThread> open(int initialState");
                                                            #line 1098 "PrintJava.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 1590 "PrintJava.cpp"
  append(L", BottomUpEventHandler eh");
                                                            #line 1100 "PrintJava.cpp.template"
                                                              }
                                                            #line 1594 "PrintJava.cpp"
  append(L", int t)\n");
  append(L"  {\n");
  append(L"    accepted = false;\n");
  append(L"    target = t;");
                                                            #line 1104 "PrintJava.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 1602 "PrintJava.cpp"
  append(L"\n");
  append(L"    eventHandler = eh;\n");
  append(L"    if (eventHandler != null)\n");
  append(L"    {\n");
  append(L"      eventHandler.reset(input);\n");
  append(L"    }\n");
  append(L"    deferredEvent = null;");
                                                            #line 1112 "PrintJava.cpp.template"
                                                              }
                                                              if (hasCustomCode && useGlr)
                                                              {
                                                            #line 1614 "PrintJava.cpp"
  append(L"\n");
  append(L"    deferredCode = null;");
                                                            #line 1116 "PrintJava.cpp.template"
                                                         }
                                                            #line 1619 "PrintJava.cpp"
  append(L"\n");
  append(L"    stack = new StackNode(-1, ");
                                                            #line 1119 "PrintJava.cpp.template"
                                                              if (grammar->states->hasLookback)
                                                              {
                                                            #line 1625 "PrintJava.cpp"
  append(L"0, ");
                                                            #line 1121 "PrintJava.cpp.template"
                                                              }
                                                            #line 1629 "PrintJava.cpp"
  append(L"e0, null);\n");
  append(L"    state = initialState;\n");
  append(L"    action = predict(initialState);");
                                                            #line 1124 "PrintJava.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 1636 "PrintJava.cpp"
  append(L"\n");
  append(L"    bw = e0;\n");
  append(L"    bs = e0;\n");
  append(L"    es = e0;");
                                                            #line 1129 "PrintJava.cpp.template"
                                                              }
                                                            #line 1643 "PrintJava.cpp"
  append(L"\n");
  append(L"    threads = new PriorityQueue<>();\n");
  append(L"    threads.offer(this);\n");
  append(L"    return threads;\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  public ParsingThread copy(ParsingThread other, int action)\n");
  append(L"  {\n");
  append(L"    this.action = action;\n");
  append(L"    accepted = other.accepted;\n");
  append(L"    target = other.target;");
                                                            #line 1140 "PrintJava.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 1658 "PrintJava.cpp"
  append(L"\n");
  append(L"    bs = other.bs;\n");
  append(L"    es = other.es;\n");
  append(L"    bw = other.bw;\n");
  append(L"    eventHandler = other.eventHandler;\n");
  append(L"    deferredEvent = other.deferredEvent;");
                                                            #line 1147 "PrintJava.cpp.template"
                                                              }
                                                              if (hasCustomCode)
                                                              {
                                                            #line 1669 "PrintJava.cpp"
  append(L"\n");
  append(L"    deferredCode = other.deferredCode;");
                                                            #line 1151 "PrintJava.cpp.template"
                                                              }
                                                            #line 1674 "PrintJava.cpp"
  append(L"\n");
  append(L"    id = ++maxId;\n");
  append(L"    threads = other.threads;\n");
  append(L"    state = other.state;\n");
  append(L"    stack = other.stack;\n");
  append(L"    b0 = other.b0;\n");
  append(L"    e0 = other.e0;");
                                                            #line 1158 "PrintJava.cpp.template"
                                                              for (size_t i = 1; i <= grammar->k; ++i)
                                                              {
                                                                const wchar_t *iString = format.toString<wchar_t>(i);
                                                            #line 1686 "PrintJava.cpp"
  append(L"\n");
  append(L"    l");
                                                            #line 1162 "PrintJava.cpp.template"
                                                                print(iString);
                                                            #line 1691 "PrintJava.cpp"
  append(L" = other.l");
                                                            #line 1163 "PrintJava.cpp.template"
                                                                print(iString);
                                                            #line 1695 "PrintJava.cpp"
  append(L";\n");
  append(L"    b");
                                                            #line 1165 "PrintJava.cpp.template"
                                                                print(iString);
                                                            #line 1700 "PrintJava.cpp"
  append(L" = other.b");
                                                            #line 1166 "PrintJava.cpp.template"
                                                                print(iString);
                                                            #line 1704 "PrintJava.cpp"
  append(L";\n");
  append(L"    e");
                                                            #line 1168 "PrintJava.cpp.template"
                                                                print(iString);
                                                            #line 1709 "PrintJava.cpp"
  append(L" = other.e");
                                                            #line 1169 "PrintJava.cpp.template"
                                                                print(iString);
                                                            #line 1713 "PrintJava.cpp"
  append(L";");
                                                            #line 1170 "PrintJava.cpp.template"
                                                              }
                                                            #line 1717 "PrintJava.cpp"
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
                                                            #line 1200 "PrintJava.cpp.template"
                                                              increaseIndent();
                                                              beginPublic();
                                                            }

                                                            void PrintJava::printFlush(int i, bool withinThread)
                                                            {
                                                              if (trace)
                                                              {
                                                                increaseIndent(i);
                                                            #line 1758 "PrintJava.cpp"
  append(L"\n");
  append(L"flushTrace();");
                                                            #line 1210 "PrintJava.cpp.template"
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
                                                            #line 1773 "PrintJava.cpp"
  append(L"\n");
                                                            #line 1222 "PrintJava.cpp.template"
                                                              print(visibility);
                                                            #line 1777 "PrintJava.cpp"
  append(L" ");
                                                            #line 1223 "PrintJava.cpp.template"
                                                              print(prefix);
                                                              print(type);
                                                              print(name);
                                                            #line 1783 "PrintJava.cpp"
  append(L"(");
                                                            #line 1226 "PrintJava.cpp.template"
                                                              print(args);
                                                            #line 1787 "PrintJava.cpp"
  append(L")");
                                                            #line 1227 "PrintJava.cpp.template"
                                                            }

                                                            void PrintJava::privateVars()
                                                            {
                                                              if (trace)
                                                              {
                                                            #line 1796 "PrintJava.cpp"
  append(L"\n");
  append(L"  private String lookaheadString()\n");
  append(L"  {\n");
  append(L"    String result = \"\";");
                                                            #line 1236 "PrintJava.cpp.template"
                                                                for (size_t i = 1; i <= grammar->k; ++i)
                                                                {
                                                            #line 1804 "PrintJava.cpp"
  append(L"\n");
  append(L"    if (l");
                                                            #line 1239 "PrintJava.cpp.template"
                                                                  print(format.toString<wchar_t>(i));
                                                            #line 1809 "PrintJava.cpp"
  append(L" > 0)\n");
  append(L"    {\n");
  append(L"      result += ");
                                                            #line 1242 "PrintJava.cpp.template"
                                                                  if (i != 1)
                                                                  {
                                                            #line 1816 "PrintJava.cpp"
  append(L"\" \" + ");
                                                            #line 1244 "PrintJava.cpp.template"
                                                                  }
                                                            #line 1820 "PrintJava.cpp"
  append(L"TOKEN[l");
                                                            #line 1245 "PrintJava.cpp.template"
                                                                  print(format.toString<wchar_t>(i));
                                                            #line 1824 "PrintJava.cpp"
  append(L"];");
                                                            #line 1246 "PrintJava.cpp.template"
                                                                  increaseIndent();
                                                                }
                                                                for (size_t i = 1; i <= grammar->k; ++i)
                                                                {
                                                                  decreaseIndent();
                                                            #line 1832 "PrintJava.cpp"
  append(L"\n");
  append(L"    }");
                                                            #line 1252 "PrintJava.cpp.template"
                                                                }
                                                            #line 1837 "PrintJava.cpp"
  append(L"\n");
  append(L"    return result;\n");
  append(L"  }\n");
                                                            #line 1256 "PrintJava.cpp.template"
                                                              }
                                                              if (memoization)
                                                              {
                                                                int bits = Math::bits(grammar->conflictCount);
                                                            #line 1846 "PrintJava.cpp"
  append(L"\n");
  append(L"  private void memoize(int i, int e, int v)\n");
  append(L"  {\n");
  append(L"    memo.put((e << ");
                                                            #line 1263 "PrintJava.cpp.template"
                                                                print(format.toString<wchar_t>(bits));
                                                            #line 1853 "PrintJava.cpp"
  append(L") + i, v);\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  private int memoized(int i, int e)\n");
  append(L"  {\n");
  append(L"    Integer v = memo.get((e << ");
                                                            #line 1269 "PrintJava.cpp.template"
                                                                print(format.toString<wchar_t>(bits));
                                                            #line 1862 "PrintJava.cpp"
  append(L") + i);\n");
  append(L"    return v == null ? 0 : v;\n");
  append(L"  }\n");
                                                            #line 1273 "PrintJava.cpp.template"
                                                              }
                                                            #line 1868 "PrintJava.cpp"
  append(L"\n");
  append(L"  private int ");
                                                            #line 1275 "PrintJava.cpp.template"
                                                              if (! isLrParser && (grammar->k > 1 ||
                                                                                   memoization ||
                                                                                   ! grammar->decisionPoints.empty()))
                                                              {
                                                            #line 1876 "PrintJava.cpp"
  append(L"lk,");
                                                            #line 1279 "PrintJava.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 1882 "PrintJava.cpp"
  append(L"   ");
                                                            #line 1282 "PrintJava.cpp.template"
                                                              }
                                                            #line 1886 "PrintJava.cpp"
  append(L" b0, e0;");
                                                            #line 1283 "PrintJava.cpp.template"
                                                              for (size_t k = 1; k <= grammar->k; ++k)
                                                              {
                                                                Format format;
                                                                wchar_t *asString = format.toString<wchar_t>(k);
                                                            #line 1893 "PrintJava.cpp"
  append(L"\n");
  append(L"  private int l");
                                                            #line 1288 "PrintJava.cpp.template"
                                                                print(asString);
                                                            #line 1898 "PrintJava.cpp"
  append(L", b");
                                                            #line 1289 "PrintJava.cpp.template"
                                                                print(asString);
                                                            #line 1902 "PrintJava.cpp"
  append(L", e");
                                                            #line 1290 "PrintJava.cpp.template"
                                                                print(asString);
                                                            #line 1906 "PrintJava.cpp"
  append(L";");
                                                            #line 1291 "PrintJava.cpp.template"
                                                              }
                                                              if (hasBacktracking)
                                                              {
                                                            #line 1912 "PrintJava.cpp"
  append(L"\n");
  append(L"  private int bx, ex, sx, lx, tx;");
                                                            #line 1295 "PrintJava.cpp.template"
                                                              }
                                                              else if (isLrParser && ! useGlr)
                                                              {
                                                            #line 1919 "PrintJava.cpp"
  append(L"\n");
  append(L"  private int iStack[] = new int[");
                                                            #line 1299 "PrintJava.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 1925 "PrintJava.cpp"
  append(L"192");
                                                            #line 1301 "PrintJava.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1931 "PrintJava.cpp"
  append(L"128");
                                                            #line 1304 "PrintJava.cpp.template"
                                                                }
                                                            #line 1935 "PrintJava.cpp"
  append(L"];\n");
  append(L"  private int top = -1;");
                                                            #line 1306 "PrintJava.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                                if (isLrParser)
                                                                {
                                                                  if (useGlr)
                                                                  {
                                                            #line 1946 "PrintJava.cpp"
  append(L"\n");
  append(L"  private int bw, bs, es;");
                                                            #line 1314 "PrintJava.cpp.template"
                                                                  }
                                                            #line 1951 "PrintJava.cpp"
  append(L"\n");
  append(L"  private BottomUpEventHandler eventHandler = null;");
                                                            #line 1316 "PrintJava.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1958 "PrintJava.cpp"
  append(L"\n");
  append(L"  private EventHandler eventHandler = null;");
                                                            #line 1320 "PrintJava.cpp.template"
                                                                }
                                                              }
                                                              else if (useGlr)
                                                              {
                                                            #line 1966 "PrintJava.cpp"
  append(L"\n");
  append(L"  private int bw, bs;");
                                                            #line 1325 "PrintJava.cpp.template"
                                                              }
                                                              if (memoization)
                                                              {
                                                            #line 1973 "PrintJava.cpp"
  append(L"\n");
  append(L"  private java.util.Map<Integer, Integer> memo = new java.util.HashMap<Integer, Integer>();");
                                                            #line 1330 "PrintJava.cpp.template"
                                                                if (grammar->noThrow)
                                                                {
                                                            #line 1979 "PrintJava.cpp"
  append(L"\n");
  append(L"  private boolean viable;");
                                                            #line 1333 "PrintJava.cpp.template"
                                                                }
                                                              }
                                                              if (useGlr)
                                                              {
                                                                decreaseIndent();
                                                              }
                                                            }

                                                            void PrintJava::printFileProcessor()
                                                            {
                                                            #line 1993 "PrintJava.cpp"
  append(L"\n");
  append(L"  private static boolean quiet = false;\n");
  append(L"  private static long parsed = 0;\n");
  append(L"  private static int errorCount = 0;\n");
  append(L"  private static java.util.Collection<ParseJob> parsers = new java.util.ArrayList<>();\n");
  append(L"\n");
  append(L"  private static class ParseJob\n");
  append(L"  {\n");
  append(L"    public String name;\n");
  append(L"    public String input;\n");
  append(L"    public ");
                                                            #line 1353 "PrintJava.cpp.template"
                                                              print(className.c_str());
                                                            #line 2007 "PrintJava.cpp"
  append(L" parser;");
                                                            #line 1354 "PrintJava.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 2012 "PrintJava.cpp"
  append(L"\n");
  append(L"    public ContentCounter contentCounter;");
                                                            #line 1357 "PrintJava.cpp.template"
                                                                if (isLrParser)
                                                                {
                                                            #line 2018 "PrintJava.cpp"
  append(L"\n");
  append(L"    public ParseTreeBuilder parseTreeBuilder;");
                                                            #line 1360 "PrintJava.cpp.template"
                                                                }
                                                              }
                                                            #line 2024 "PrintJava.cpp"
  append(L"\n");
  append(L"\n");
  append(L"    public ParseJob(String s, String i)\n");
  append(L"    {\n");
  append(L"      name = s;\n");
  append(L"      input = i;");
                                                            #line 1367 "PrintJava.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 2034 "PrintJava.cpp"
  append(L"\n");
  append(L"      contentCounter = new ContentCounter();");
                                                            #line 1370 "PrintJava.cpp.template"
                                                                if (isLrParser)
                                                                {
                                                            #line 2040 "PrintJava.cpp"
  append(L"\n");
  append(L"      parseTreeBuilder = new ParseTreeBuilder();");
                                                            #line 1373 "PrintJava.cpp.template"
                                                                }
                                                              }
                                                            #line 2046 "PrintJava.cpp"
  append(L"\n");
  append(L"      parser = new ");
                                                            #line 1376 "PrintJava.cpp.template"
                                                              print(className.c_str());
                                                            #line 2051 "PrintJava.cpp"
  append(L"(input");
                                                            #line 1377 "PrintJava.cpp.template"
                                                              if (noLexer)
                                                              {
                                                            #line 2056 "PrintJava.cpp"
  append(L", new ");
                                                            #line 1379 "PrintJava.cpp.template"
                                                                print(className.c_str());
                                                            #line 2060 "PrintJava.cpp"
  append(L"Lexer()");
                                                            #line 1380 "PrintJava.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                                if (isLrParser)
                                                                {
                                                            #line 2068 "PrintJava.cpp"
  append(L", parseTreeBuilder");
                                                            #line 1385 "PrintJava.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 2074 "PrintJava.cpp"
  append(L", contentCounter");
                                                            #line 1388 "PrintJava.cpp.template"
                                                                }
                                                              }
                                                            #line 2079 "PrintJava.cpp"
  append(L");\n");
  append(L"    }\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  public static void main(String[] args) throws Exception\n");
  append(L"  {\n");
  append(L"    if (args.length == 0)\n");
  append(L"    {\n");
  append(L"      System.out.println(\"Usage: java ");
                                                            #line 1398 "PrintJava.cpp.template"
                                                              print(className.c_str());
                                                            #line 2091 "PrintJava.cpp"
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
                                                            #line 1464 "PrintJava.cpp.template"
                                                                  if (useGlr)
                                                                  {
                                                            #line 2161 "PrintJava.cpp"
  append(L".thread");
                                                            #line 1466 "PrintJava.cpp.template"
                                                                  }
                                                            #line 2165 "PrintJava.cpp"
  append(L".reset(0, 0, 0);\n");
  append(L"                job.parser.");
                                                            #line 1468 "PrintJava.cpp.template"
                                                                  print(methodPrefixParse);
                                                                  print(Format::acceptableName<WString>(grammar->startSymbol()->name).c_str());
                                                            #line 2171 "PrintJava.cpp"
  append(L"();\n");
  append(L"                if (! quiet) System.out.println();");
                                                            #line 1471 "PrintJava.cpp.template"
                                                                  if (tree)
                                                                  {
                                                                    if (isLrParser)
                                                                    {
                                                            #line 2179 "PrintJava.cpp"
  append(L"\n");
  append(L"                job.parseTreeBuilder.serialize(job.contentCounter);");
                                                            #line 1477 "PrintJava.cpp.template"
                                                                    }
                                                            #line 2184 "PrintJava.cpp"
  append(L"\n");
  append(L"                if (job.contentCounter.getLength() != job.input.length())\n");
  append(L"                {\n");
  append(L"                  throw new RuntimeException(\"content counter saw \" + job.contentCounter.getLength() + \", but input length is \" + job.input.length());\n");
  append(L"                }");
                                                            #line 1482 "PrintJava.cpp.template"
                                                                  }
                                                            #line 2192 "PrintJava.cpp"
  append(L"\n");
  append(L"                parsed += job.input.length();\n");
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
                                                            #line 1539 "PrintJava.cpp.template"
                                                            }

                                                            void PrintJava::printReadMethod()
                                                            {
                                                            #line 2253 "PrintJava.cpp"
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
                                                            #line 1563 "PrintJava.cpp.template"
//      if (content.length() > 0 && content.charAt(0) == '\uFEFF')
//      {
//        content = content.substring(1);
//      }
//      return content.replace("\r\n", "\n");
                                                            }

                                                            void PrintJava::printInterface()
                                                            {
                                                              if (! packageName.empty())
                                                              {
                                                            #line 2285 "PrintJava.cpp"
  append(L"\n");
  append(L"package ");
                                                            #line 1575 "PrintJava.cpp.template"
                                                                print(packageName.c_str());
                                                            #line 2290 "PrintJava.cpp"
  append(L";\n");
                                                            #line 1577 "PrintJava.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                                if (main || useGlr)
                                                                {
                                                            #line 2298 "PrintJava.cpp"
  append(L"\n");
  append(L"import java.io.IOException;\n");
  append(L"import java.io.Writer;\n");
                                                            #line 1585 "PrintJava.cpp.template"
                                                                }
                                                            #line 2304 "PrintJava.cpp"
  append(L"\n");
  append(L"import java.util.Arrays;");
                                                            #line 1588 "PrintJava.cpp.template"
                                                                if (saxon)
                                                                {
                                                            #line 2310 "PrintJava.cpp"
  append(L"\n");
  append(L"import net.sf.saxon.event.Builder;");
                                                            #line 1591 "PrintJava.cpp.template"
                                                                  if (saxon == 99)
                                                                  {
                                                            #line 2316 "PrintJava.cpp"
  append(L"\n");
  append(L"import net.sf.saxon.expr.parser.ExplicitLocation;\n");
  append(L"import net.sf.saxon.expr.parser.Location;");
                                                            #line 1595 "PrintJava.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 2324 "PrintJava.cpp"
  append(L"\n");
  append(L"import net.sf.saxon.expr.parser.Loc;\n");
  append(L"import net.sf.saxon.om.AttributeMap;\n");
  append(L"import net.sf.saxon.om.EmptyAttributeMap;\n");
  append(L"import net.sf.saxon.om.NamespaceMap;\n");
  append(L"import net.sf.saxon.s9api.Location;");
                                                            #line 1603 "PrintJava.cpp.template"
                                                                  }
                                                            #line 2333 "PrintJava.cpp"
  append(L"\n");
  append(L"import net.sf.saxon.om.NoNamespaceName;\n");
  append(L"import net.sf.saxon.trans.XPathException;\n");
  append(L"import net.sf.saxon.type.AnyType;");
                                                            #line 1607 "PrintJava.cpp.template"
                                                                  if (saxon == 110)
                                                                  {
                                                            #line 2341 "PrintJava.cpp"
  append(L"\n");
  append(L"import net.sf.saxon.str.StringView;");
                                                            #line 1610 "PrintJava.cpp.template"
                                                                  }
                                                            #line 2346 "PrintJava.cpp"
  append(L"\n");
                                                            #line 1612 "PrintJava.cpp.template"
                                                                }
                                                              }
                                                            #line 2351 "PrintJava.cpp"
  append(L"\n");
  append(L"public interface ");
                                                            #line 1615 "PrintJava.cpp.template"
                                                              print(className.c_str());
                                                            #line 2356 "PrintJava.cpp"
  append(L"\n");
  append(L"{\n");
  append(L"  public void initialize(CharSequence input");
                                                            #line 1618 "PrintJava.cpp.template"
                                                              if (noLexer)
                                                              {
                                                            #line 2363 "PrintJava.cpp"
  append(L", Lexer l");
                                                            #line 1620 "PrintJava.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                            #line 2369 "PrintJava.cpp"
  append(L", ");
                                                            #line 1623 "PrintJava.cpp.template"
                                                                if (isLrParser)
                                                                {
                                                            #line 2374 "PrintJava.cpp"
  append(L"BottomUp");
                                                            #line 1626 "PrintJava.cpp.template"
                                                                }
                                                            #line 2378 "PrintJava.cpp"
  append(L"EventHandler eh");
                                                            #line 1628 "PrintJava.cpp.template"
                                                              }
                                                            #line 2382 "PrintJava.cpp"
  append(L");\n");
  append(L"  public void parse();\n");
  append(L"  public void reset();\n");
  append(L"  public String getErrorMessage(ParseException e);\n");
                                                            #line 1633 "PrintJava.cpp.template"
                                                              printParseException();
                                                              printEventHandlerImplementation();
                                                            #line 2390 "PrintJava.cpp"
  append(L"}\n");
                                                            #line 1636 "PrintJava.cpp.template"
                                                            }

                                                            void PrintJava::printParseException()
                                                            {
                                                            #line 2397 "PrintJava.cpp"
  append(L"\n");
  append(L"  public static class ParseException extends RuntimeException\n");
  append(L"  {\n");
  append(L"    private static final long serialVersionUID = 1L;\n");
  append(L"    private int begin, end, offending, expected, state;");
                                                            #line 1644 "PrintJava.cpp.template"
                                                              if (useGlr)
                                                              {
                                                            #line 2406 "PrintJava.cpp"
  append(L"\n");
  append(L"    private boolean ambiguousInput;");
                                                            #line 1647 "PrintJava.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 2412 "PrintJava.cpp"
  append(L"\n");
  append(L"    private ParseTreeBuilder ambiguityDescriptor;");
                                                            #line 1650 "PrintJava.cpp.template"
                                                                }
                                                              }
                                                            #line 2418 "PrintJava.cpp"
  append(L"\n");
  append(L"\n");
  append(L"    public ParseException(int b, int e, int s, int o, int x)\n");
  append(L"    {\n");
  append(L"      begin = b;\n");
  append(L"      end = e;\n");
  append(L"      state = s;\n");
  append(L"      offending = o;\n");
  append(L"      expected = x;");
                                                            #line 1660 "PrintJava.cpp.template"
                                                              if (useGlr)
                                                              {
                                                            #line 2431 "PrintJava.cpp"
  append(L"\n");
  append(L"      ambiguousInput = false;");
                                                            #line 1663 "PrintJava.cpp.template"
                                                              }
                                                            #line 2436 "PrintJava.cpp"
  append(L"\n");
  append(L"    }\n");
                                                            #line 1666 "PrintJava.cpp.template"
                                                              if (useGlr)
                                                              {
                                                            #line 2442 "PrintJava.cpp"
  append(L"\n");
  append(L"    public ParseException(int b, int e");
                                                            #line 1669 "PrintJava.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 2448 "PrintJava.cpp"
  append(L", ParseTreeBuilder ambiguityDescriptor");
                                                            #line 1672 "PrintJava.cpp.template"
                                                                }
                                                            #line 2452 "PrintJava.cpp"
  append(L")\n");
  append(L"    {\n");
  append(L"      this(b, e, 1, -1, -1);\n");
  append(L"      ambiguousInput = true;");
                                                            #line 1676 "PrintJava.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 2460 "PrintJava.cpp"
  append(L"\n");
  append(L"      this.ambiguityDescriptor = ambiguityDescriptor;");
                                                            #line 1679 "PrintJava.cpp.template"
                                                                }
                                                            #line 2465 "PrintJava.cpp"
  append(L"\n");
  append(L"    }\n");
                                                            #line 1682 "PrintJava.cpp.template"
                                                              }
                                                            #line 2470 "PrintJava.cpp"
  append(L"\n");
  append(L"    @Override\n");
  append(L"    public String getMessage()\n");
  append(L"    {\n");
  append(L"      return ");
                                                            #line 1687 "PrintJava.cpp.template"
                                                              if (useGlr)
                                                              {
                                                            #line 2479 "PrintJava.cpp"
  append(L"ambiguousInput\n");
  append(L"           ? \"ambiguous input\"\n");
  append(L"           : ");
                                                            #line 1691 "PrintJava.cpp.template"
                                                              }
                                                            #line 2485 "PrintJava.cpp"
  append(L"offending < 0\n");
  append(L"           ? \"lexical analysis failed\"\n");
  append(L"           : \"syntax error\";\n");
  append(L"    }\n");
                                                            #line 1696 "PrintJava.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 2493 "PrintJava.cpp"
  append(L"\n");
  append(L"    public void serialize(EventHandler eventHandler)\n");
  append(L"    {");
                                                            #line 1700 "PrintJava.cpp.template"
                                                                if (useGlr)
                                                                {
                                                            #line 2500 "PrintJava.cpp"
  append(L"\n");
  append(L"      ambiguityDescriptor.serialize(eventHandler);");
                                                            #line 1703 "PrintJava.cpp.template"
                                                                }
                                                            #line 2505 "PrintJava.cpp"
  append(L"\n");
  append(L"    }\n");
                                                            #line 1706 "PrintJava.cpp.template"
                                                              }
                                                            #line 2510 "PrintJava.cpp"
  append(L"\n");
  append(L"    public int getBegin() {return begin;}\n");
  append(L"    public int getEnd() {return end;}\n");
  append(L"    public int getState() {return state;}\n");
  append(L"    public int getOffending() {return offending;}\n");
  append(L"    public int getExpected() {return expected;}\n");
  append(L"    public boolean isAmbiguousInput() {return ");
                                                            #line 1713 "PrintJava.cpp.template"
                                                              if (useGlr)
                                                              {
                                                            #line 2521 "PrintJava.cpp"
  append(L"ambiguousInput");
                                                            #line 1716 "PrintJava.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 2527 "PrintJava.cpp"
  append(L"false");
                                                            #line 1719 "PrintJava.cpp.template"
                                                              }
                                                            #line 2531 "PrintJava.cpp"
  append(L";}\n");
  append(L"  }\n");
                                                            #line 1722 "PrintJava.cpp.template"
                                                              if (noLexer)
                                                              {
                                                            #line 2537 "PrintJava.cpp"
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
                                                            #line 1737 "PrintJava.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                            #line 2555 "PrintJava.cpp"
  append(L"\n");
  append(L"  public interface EventHandler\n");
  append(L"  {\n");
  append(L"    public void reset(CharSequence string);\n");
  append(L"    public void startNonterminal(String name, int begin);\n");
  append(L"    public void endNonterminal(String name, int end);\n");
  append(L"    public void terminal(String name, int begin, int end);\n");
  append(L"    public void whitespace(int begin, int end);\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  public static class TopDownTreeBuilder implements EventHandler\n");
  append(L"  {\n");
  append(L"    private CharSequence input = null;\n");
  append(L"    private Nonterminal[] stack = new Nonterminal[64];\n");
  append(L"    private int top = -1;\n");
  append(L"\n");
  append(L"    @Override\n");
  append(L"    public void reset(CharSequence input)\n");
  append(L"    {\n");
  append(L"      this.input = input;\n");
  append(L"      top = -1;\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    @Override\n");
  append(L"    public void startNonterminal(String name, int begin)\n");
  append(L"    {\n");
  append(L"      Nonterminal nonterminal = new Nonterminal(name, begin, begin, new Symbol[0]);\n");
  append(L"      if (top >= 0) addChild(nonterminal);\n");
  append(L"      if (++top >= stack.length) stack = Arrays.copyOf(stack, stack.length << 1);\n");
  append(L"      stack[top] = nonterminal;\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    @Override\n");
  append(L"    public void endNonterminal(String name, int end)\n");
  append(L"    {\n");
  append(L"      stack[top].end = end;\n");
  append(L"      if (top > 0) --top;\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    @Override\n");
  append(L"    public void terminal(String name, int begin, int end)\n");
  append(L"    {\n");
  append(L"      addChild(new Terminal(name, begin, end));\n");
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
  append(L"  public static class Terminal extends Symbol\n");
  append(L"  {\n");
  append(L"    public Terminal(String name, int begin, int end)\n");
  append(L"    {\n");
  append(L"      super(name, begin, end);\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    @Override\n");
  append(L"    public void send(EventHandler e)\n");
  append(L"    {\n");
  append(L"      e.terminal(name, begin, end);\n");
  append(L"    }\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  public static class Nonterminal extends Symbol\n");
  append(L"  {\n");
  append(L"    public Symbol[] children;\n");
  append(L"\n");
  append(L"    public Nonterminal(String name, int begin, int end, Symbol[] children)\n");
  append(L"    {\n");
  append(L"      super(name, begin, end);\n");
  append(L"      this.children = children;\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    @Override\n");
  append(L"    public void send(EventHandler e)\n");
  append(L"    {\n");
  append(L"      e.startNonterminal(name, begin);\n");
  append(L"      int pos = begin;\n");
  append(L"      for (Symbol c : children)\n");
  append(L"      {\n");
  append(L"        if (pos < c.begin) e.whitespace(pos, c.begin);\n");
  append(L"        c.send(e);\n");
  append(L"        pos = c.end;\n");
  append(L"      }\n");
  append(L"      if (pos < end) e.whitespace(pos, end);\n");
  append(L"      e.endNonterminal(name, end);\n");
  append(L"    }\n");
  append(L"  }\n");
                                                            #line 1859 "PrintJava.cpp.template"
                                                                if (isLrParser)
                                                                {
                                                            #line 2678 "PrintJava.cpp"
  append(L"\n");
  append(L"  public interface BottomUpEventHandler\n");
  append(L"  {\n");
  append(L"    public void reset(CharSequence string);\n");
  append(L"    public void nonterminal(String name, int begin, int end, int count);\n");
  append(L"    public void terminal(String name, int begin, int end);\n");
  append(L"  }\n");
                                                            #line 1868 "PrintJava.cpp.template"
                                                                }
                                                              }
                                                            }

                                                            void PrintJava::printEventHandlerImplementation()
                                                            {
                                                              if (tree)
                                                              {
                                                                if (main || useGlr)
                                                                {
                                                            #line 2697 "PrintJava.cpp"
  append(L"\n");
  append(L"  public static class XmlSerializer implements EventHandler\n");
  append(L"  {\n");
  append(L"    private CharSequence input;\n");
  append(L"    private String delayedTag;\n");
  append(L"    private Writer out;\n");
  append(L"    private boolean indent;\n");
  append(L"    private boolean hasChildElement;\n");
  append(L"    private int depth;\n");
  append(L"\n");
  append(L"    public XmlSerializer(Writer w, boolean indent)\n");
  append(L"    {\n");
  append(L"      input = null;\n");
  append(L"      delayedTag = null;\n");
  append(L"      out = w;\n");
  append(L"      this.indent = indent;\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    @Override\n");
  append(L"    public void reset(CharSequence string)\n");
  append(L"    {\n");
  append(L"      writeOutput(\"<?xml version=\\\"1.0\\\" encoding=\\\"UTF-8\\\"?\" + \">\");\n");
  append(L"      input = string;\n");
  append(L"      delayedTag = null;\n");
  append(L"      hasChildElement = false;\n");
  append(L"      depth = 0;\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    @Override\n");
  append(L"    public void startNonterminal(String name, int begin)\n");
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
  append(L"    public void endNonterminal(String name, int end)\n");
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
  append(L"    public void terminal(String name, int begin, int end)\n");
  append(L"    {\n");
  append(L"      if (name.charAt(0) == '\\'')\n");
  append(L"      {\n");
  append(L"        name = \"TOKEN\";\n");
  append(L"      }\n");
  append(L"      startNonterminal(name, begin);\n");
  append(L"      characters(begin, end);\n");
  append(L"      endNonterminal(name, end);\n");
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
  append(L"        writeOutput(input.subSequence(begin, end)\n");
  append(L"                         .toString()\n");
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
                                                            #line 2008 "PrintJava.cpp.template"
                                                                }
                                                                if (performanceTest)
                                                                {
                                                            #line 2832 "PrintJava.cpp"
  append(L"\n");
  append(L"  public static class ContentCounter implements EventHandler\n");
  append(L"  {\n");
  append(L"    private int length = 0;\n");
  append(L"    public int getLength() {return length;}\n");
  append(L"    @Override\n");
  append(L"    public void reset(CharSequence string) {length = 0;}\n");
  append(L"    @Override\n");
  append(L"    public void startNonterminal(String name, int begin) {}\n");
  append(L"    @Override\n");
  append(L"    public void endNonterminal(String name, int end) {}\n");
  append(L"    @Override\n");
  append(L"    public void terminal(String name, int begin, int end) {length += end - begin;}\n");
  append(L"    @Override\n");
  append(L"    public void whitespace(int begin, int end) {length += end - begin;}\n");
  append(L"  }\n");
                                                            #line 2028 "PrintJava.cpp.template"
                                                                }
                                                                if (saxon)
                                                                {
                                                            #line 2853 "PrintJava.cpp"
  append(L"\n");
  append(L"  public static class SaxonTreeBuilder implements EventHandler\n");
  append(L"  {\n");
  append(L"    private CharSequence input;\n");
  append(L"    private Builder builder;\n");
  append(L"    private AnyType anyType;\n");
  append(L"\n");
  append(L"    public SaxonTreeBuilder(Builder b)\n");
  append(L"    {\n");
  append(L"      input = null;\n");
  append(L"      builder = b;\n");
  append(L"      anyType = AnyType.getInstance();\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    @Override\n");
  append(L"    public void reset(CharSequence string)\n");
  append(L"    {\n");
  append(L"      input = string;\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    @Override\n");
  append(L"    public void startNonterminal(String name, int begin)\n");
  append(L"    {\n");
  append(L"      try\n");
  append(L"      {\n");
  append(L"        builder.startElement(new NoNamespaceName(name), anyType, ");
                                                            #line 2057 "PrintJava.cpp.template"
                                                                  if (saxon != 99)
                                                                  {
                                                            #line 2883 "PrintJava.cpp"
  append(L"NO_ATTRIBUTES, NO_NAMESPACES, ");
                                                            #line 2059 "PrintJava.cpp.template"
                                                                  }
                                                            #line 2887 "PrintJava.cpp"
  append(L"LOCATION, 0);\n");
  append(L"      }\n");
  append(L"      catch (XPathException e)\n");
  append(L"      {\n");
  append(L"        throw new RuntimeException(e);\n");
  append(L"      }\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    @Override\n");
  append(L"    public void endNonterminal(String name, int end)\n");
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
  append(L"    public void terminal(String name, int begin, int end)\n");
  append(L"    {\n");
  append(L"      if (name.charAt(0) == '\\'')\n");
  append(L"      {\n");
  append(L"        name = \"TOKEN\";\n");
  append(L"      }\n");
  append(L"      startNonterminal(name, begin);\n");
  append(L"      characters(begin, end);\n");
  append(L"      endNonterminal(name, end);\n");
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
                                                            #line 2105 "PrintJava.cpp.template"
                                                                  if (saxon == 110)
                                                                  {
                                                            #line 2937 "PrintJava.cpp"
  append(L"StringView.of(");
                                                            #line 2107 "PrintJava.cpp.template"
                                                                  }
                                                            #line 2941 "PrintJava.cpp"
  append(L"input.subSequence(begin, end)");
                                                            #line 2108 "PrintJava.cpp.template"
                                                                  if (saxon == 110)
                                                                  {
                                                            #line 2946 "PrintJava.cpp"
  append(L".toString())");
                                                            #line 2111 "PrintJava.cpp.template"
                                                                  }
                                                            #line 2950 "PrintJava.cpp"
  append(L", LOCATION, 0);\n");
  append(L"        }\n");
  append(L"        catch (XPathException e)\n");
  append(L"        {\n");
  append(L"          throw new RuntimeException(e);\n");
  append(L"        }\n");
  append(L"      }\n");
  append(L"    }\n");
  append(L"  }\n");
                                                            #line 2121 "PrintJava.cpp.template"
                                                                }
                                                                if (isLrParser)
                                                                {
                                                            #line 2964 "PrintJava.cpp"
  append(L"\n");
  append(L"  public static class ParseTreeBuilder implements BottomUpEventHandler\n");
  append(L"  {\n");
  append(L"    private CharSequence input;\n");
  append(L"    public Symbol[] stack = new Symbol[64];\n");
  append(L"    public int top = -1;\n");
  append(L"\n");
  append(L"    @Override\n");
  append(L"    public void reset(CharSequence input)\n");
  append(L"    {\n");
  append(L"      this.input = input;\n");
  append(L"      top = -1;\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    @Override\n");
  append(L"    public void nonterminal(String name, int begin, int end, int count)\n");
  append(L"    {");
                                                            #line 2140 "PrintJava.cpp.template"
                                                                if (useGlr)
                                                                {
                                                            #line 2985 "PrintJava.cpp"
  append(L"\n");
  append(L"      if (count > top + 1)\n");
  append(L"      {\n");
  append(L"        Symbol[] content = pop(top + 1);\n");
  append(L"        nonterminal(\"UNAMBIGUOUS\", begin, content.length == 0 ? end : content[0].begin, 0);\n");
  append(L"        for (Symbol symbol : content)\n");
  append(L"        {\n");
  append(L"          push(symbol);\n");
  append(L"        }\n");
  append(L"        count = top + 1;\n");
  append(L"      }");
                                                            #line 2152 "PrintJava.cpp.template"
                                                                }
                                                            #line 2999 "PrintJava.cpp"
  append(L"\n");
  append(L"      push(new Nonterminal(name, begin, end, pop(count)));\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    @Override\n");
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
                                                            #line 2188 "PrintJava.cpp.template"
                                                                }
                                                              }
                                                              if (saxon)
                                                              {
                                                                const wchar_t *visibility = interfaceName.empty() ? L"private" : L"public";
                                                                if (saxon == 99)
                                                                {
                                                            #line 3042 "PrintJava.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 2196 "PrintJava.cpp.template"
                                                                  print(visibility);
                                                            #line 3047 "PrintJava.cpp"
  append(L" static final Location LOCATION = ExplicitLocation.UNKNOWN_LOCATION;\n");
                                                            #line 2198 "PrintJava.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 3053 "PrintJava.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 2202 "PrintJava.cpp.template"
                                                                  print(visibility);
                                                            #line 3058 "PrintJava.cpp"
  append(L" static final AttributeMap NO_ATTRIBUTES = EmptyAttributeMap.getInstance();\n");
  append(L"  ");
                                                            #line 2204 "PrintJava.cpp.template"
                                                                  print(visibility);
                                                            #line 3063 "PrintJava.cpp"
  append(L" static final NamespaceMap NO_NAMESPACES = NamespaceMap.emptyMap();\n");
  append(L"  ");
                                                            #line 2206 "PrintJava.cpp.template"
                                                                  print(visibility);
                                                            #line 3068 "PrintJava.cpp"
  append(L" static final Location LOCATION = Loc.NONE;\n");
                                                            #line 2208 "PrintJava.cpp.template"
                                                                }
                                                              }
                                                            }

                                                            /* Saxon extension function definition for match()
                                                             * did not show a performance difference. Strange...
                                                            #line 3077 "PrintJava.cpp"
  append(L"\n");
  append(L"  public static class MatchDefinition extends ExtensionFunctionDefinition implements Initializer\n");
  append(L"  {\n");
  append(L"    private static final long serialVersionUID = 1L;\n");
  append(L"\n");
  append(L"    public void initialize(Configuration conf) {conf.registerExtensionFunction(this);}\n");
  append(L"    public StructuredQName getFunctionQName() {return new StructuredQName(\"p\", \"");
                                                            #line 2221 "PrintJava.cpp.template"
                                                            if (! packageName.empty())
                                                            {
                                                              for (size_t i = 0; i < packageName.size(); ++i)
                                                              {
                                                                print(packageName[i] == L'.' ? L'/' : packageName[i]);
                                                              }
                                                            #line 3092 "PrintJava.cpp"
  append(L"/");
                                                            #line 2228 "PrintJava.cpp.template"
                                                            }
                                                            print(className.c_str());
                                                            #line 3097 "PrintJava.cpp"
  append(L"\", \"match\");}\n");
  append(L"    public SequenceType[] getArgumentTypes() {return new SequenceType[] {SequenceType.SINGLE_STRING, SequenceType.SINGLE_INTEGER, SequenceType.SINGLE_INTEGER};}\n");
  append(L"    public SequenceType getResultType(SequenceType[] suppliedArgumentTypes) {return SequenceType.NUMERIC_SEQUENCE;}\n");
  append(L"\n");
  append(L"    public ExtensionFunctionCall makeCallExpression()\n");
  append(L"    {\n");
  append(L"      return new ExtensionFunctionCall()\n");
  append(L"      {\n");
  append(L"        private ");
                                                            #line 2238 "PrintJava.cpp.template"
                                                            print(className.c_str());
                                                            #line 3109 "PrintJava.cpp"
  append(L" parser = new ");
                                                            #line 2239 "PrintJava.cpp.template"
                                                            print(className.c_str());
                                                            #line 3113 "PrintJava.cpp"
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
                                                            #line 2264 "PrintJava.cpp.template"
                                                            */

// End
