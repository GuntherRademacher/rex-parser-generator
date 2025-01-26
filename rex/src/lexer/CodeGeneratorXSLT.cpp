// This file was generated on Sun Jan 26, 2025 19:55 (UTC+01) by REx v6.1 which is Copyright (c) 1979-2025 by Gunther Rademacher <grd@gmx.net>
// REx command line: CodeGeneratorXSLT.cpp.template
                                                            #line 1 "CodeGeneratorXSLT.cpp.template"
                                                            #include "../common/Memory.hpp"

                                                            #include "CodeGenerator.hpp"

                                                            void CodeGeneratorXSLT::compressedMap2dAccessor(const char *x,
                                                                                                            const char *y,
                                                                                                            int xCount,
                                                                                                            size_t indent, const char *index, const char *result, const char *map, const int *bits)
                                                            {
                                                              print(indent, " ");
                                                            #line 15 "CodeGeneratorXSLT.cpp"
  append(L"<xsl:variable name=\"");
                                                            #line 11 "CodeGeneratorXSLT.cpp.template"
                                                              print(index);
                                                            #line 19 "CodeGeneratorXSLT.cpp"
  append(L"0\" select=\"");
                                                            #line 12 "CodeGeneratorXSLT.cpp.template"
                                                              print(format.toString<char>(xCount));
                                                            #line 23 "CodeGeneratorXSLT.cpp"
  append(L" * ");
                                                            #line 13 "CodeGeneratorXSLT.cpp.template"
                                                                                    print(y);
                                                            #line 27 "CodeGeneratorXSLT.cpp"
  append(L" + ");
                                                            #line 14 "CodeGeneratorXSLT.cpp.template"
                                                                                    print(x);
                                                            #line 31 "CodeGeneratorXSLT.cpp"
  append(L"\"/>\n");
                                                            #line 16 "CodeGeneratorXSLT.cpp.template"
                                                              compressedMapAccessor(indent, index, result, map, bits);
                                                            #line 35 "CodeGeneratorXSLT.cpp"
  append(L"\"/>");
                                                            #line 18 "CodeGeneratorXSLT.cpp.template"
                                                            }

                                                            void CodeGeneratorXSLT::compressedMapAccessor(size_t indent, const char *index, const char *result, const char *map, const int *bits)
                                                            {
                                                              size_t i = 0;
                                                              for (i = 0; bits[i]; ++i)
                                                              {
                                                                print(indent, " ");
                                                            #line 46 "CodeGeneratorXSLT.cpp"
  append(L"<xsl:variable name=\"");
                                                            #line 26 "CodeGeneratorXSLT.cpp.template"
                                                                print(index);
                                                                print(i + 1);
                                                            #line 51 "CodeGeneratorXSLT.cpp"
  append(L"\" select=\"$");
                                                            #line 28 "CodeGeneratorXSLT.cpp.template"
                                                                print(index);
                                                                print(i);
                                                            #line 56 "CodeGeneratorXSLT.cpp"
  append(L" idiv ");
                                                            #line 30 "CodeGeneratorXSLT.cpp.template"
                                                                print(Math::powerof(2, bits[i]));
                                                            #line 60 "CodeGeneratorXSLT.cpp"
  append(L"\"/>\n");
                                                            #line 32 "CodeGeneratorXSLT.cpp.template"
                                                              }
                                                              print(indent, " ");
                                                              print(result);
                                                              print(map);
                                                            #line 67 "CodeGeneratorXSLT.cpp"
  append(L"[$");
                                                            #line 36 "CodeGeneratorXSLT.cpp.template"
                                                              for (i = 0; bits[i]; ++i)
                                                              {
                                                                print(index);
                                                                print(i);
                                                            #line 74 "CodeGeneratorXSLT.cpp"
  append(L" mod ");
                                                            #line 40 "CodeGeneratorXSLT.cpp.template"
                                                                print(Math::powerof(2, bits[i]));
                                                            #line 78 "CodeGeneratorXSLT.cpp"
  append(L" + ");
                                                            #line 41 "CodeGeneratorXSLT.cpp.template"
                                                                print(map);
                                                            #line 82 "CodeGeneratorXSLT.cpp"
  append(L"[$");
                                                            #line 42 "CodeGeneratorXSLT.cpp.template"
                                                              }
                                                              print(index);
                                                              print(i);
                                                              for (i = 0; bits[i]; ++i)
                                                              {
                                                            #line 90 "CodeGeneratorXSLT.cpp"
  append(L" + 1]");
                                                            #line 47 "CodeGeneratorXSLT.cpp.template"
                                                              }
                                                            #line 94 "CodeGeneratorXSLT.cpp"
  append(L" + 1]");
                                                            #line 48 "CodeGeneratorXSLT.cpp.template"
                                                            }

                                                            void CodeGeneratorXSLT::generateStaticCode()
                                                            {
                                                              indent += 1;
                                                              if (! variable("embedded").boolean())
                                                              {
                                                            #line 104 "CodeGeneratorXSLT.cpp"
  append(L"<!--");
  append(L"~");
  append(L"\n");
  append(L"  ! The tokenizer that was generated for the ");
                                                            #line 56 "CodeGeneratorXSLT.cpp.template"
                                                                print(variable("classname").string());
                                                            #line 111 "CodeGeneratorXSLT.cpp"
  append(L" grammar.\n");
  append(L" -->\n");
  append(L"<xsl:stylesheet version=\"2.0\"\n");
  append(L"                xmlns:xs=\"http://www.w3.org/2001/XMLSchema\"\n");
  append(L"                xmlns:xsl=\"http://www.w3.org/1999/XSL/Transform\"\n");
  append(L"                xmlns:p=\"");
                                                            #line 62 "CodeGeneratorXSLT.cpp.template"
                                                                print(variable("classname").string());
                                                            #line 120 "CodeGeneratorXSLT.cpp"
  append(L"\">");
                                                            #line 63 "CodeGeneratorXSLT.cpp.template"
                                                              }

                                                              for (VarsInInsertionOrder::iterator a(varsInInsertionOrder.begin());
                                                                   a != varsInInsertionOrder.end(); ++a)
                                                                if (a->isArray() && a->size > 0 && a->hasType(CGVariable::INTEGER) && strlen(a->name) == 2)
                                                              {
                                                            #line 129 "CodeGeneratorXSLT.cpp"
  append(L"\n");
  append(L"\n");
  append(L"<!--");
  append(L"~");
  append(L"\n");
  append(L" ! ");
                                                            #line 72 "CodeGeneratorXSLT.cpp.template"
                                                                print(a->getDescription());
                                                            #line 138 "CodeGeneratorXSLT.cpp"
  append(L"\n");
  append(L"-->\n");
  append(L"<xsl:variable name=\"p:");
                                                            #line 75 "CodeGeneratorXSLT.cpp.template"
                                                                print(a->getLongName());
                                                            #line 144 "CodeGeneratorXSLT.cpp"
  append(L"\" as=\"xs:integer+\" select=\"\n");
  append(L" ");
                                                            #line 77 "CodeGeneratorXSLT.cpp.template"
                                                                for (size_t j = 0; j < a->size; ++j)
                                                                {
                                                                  if (j)
                                                                  {
                                                            #line 152 "CodeGeneratorXSLT.cpp"
  append(L",");
                                                            #line 81 "CodeGeneratorXSLT.cpp.template"
                                                                  }
                                                                  if (lineLength() + Format::width(a->integer(j)) + 2 > 160)
                                                                  {
                                                            #line 158 "CodeGeneratorXSLT.cpp"
  append(L"\n");
  append(L" ");
                                                            #line 85 "CodeGeneratorXSLT.cpp.template"
                                                                  }
                                                            #line 163 "CodeGeneratorXSLT.cpp"
  append(L" ");
                                                            #line 86 "CodeGeneratorXSLT.cpp.template"
                                                                  print(a->integer(j));
                                                                }
                                                            #line 168 "CodeGeneratorXSLT.cpp"
  append(L"\n");
  append(L"\"/>");
                                                            #line 89 "CodeGeneratorXSLT.cpp.template"
                                                              }
                                                              for (VarsInInsertionOrder::iterator a(varsInInsertionOrder.begin());
                                                                   a != varsInInsertionOrder.end(); ++a)
                                                                if (a->isArray() && a->hasType(CGVariable::STRING) && strlen(a->name) == 2)
                                                              {
                                                            #line 177 "CodeGeneratorXSLT.cpp"
  append(L"\n");
  append(L"\n");
  append(L"<!--");
  append(L"~");
  append(L"\n");
  append(L" ! ");
                                                            #line 97 "CodeGeneratorXSLT.cpp.template"
                                                                print(a->getDescription());
                                                            #line 186 "CodeGeneratorXSLT.cpp"
  append(L"\n");
  append(L"-->\n");
  append(L"<xsl:variable name=\"p:");
                                                            #line 100 "CodeGeneratorXSLT.cpp.template"
                                                                print(a->getLongName());
                                                            #line 192 "CodeGeneratorXSLT.cpp"
  append(L"\" as=\"xs:string+\" select=\"\n");
  append(L"  ");
                                                            #line 102 "CodeGeneratorXSLT.cpp.template"
                                                                for (size_t j = 0; j < a->size; ++j)
                                                                {
                                                                  if (j)
                                                                  {
                                                            #line 200 "CodeGeneratorXSLT.cpp"
  append(L",\n");
  append(L"  ");
                                                            #line 108 "CodeGeneratorXSLT.cpp.template"
                                                                  }
                                                                  const char *s = a->string(j);
                                                                  bool literal = *s == '\'';
                                                                  if (literal)
                                                                  {
                                                            #line 209 "CodeGeneratorXSLT.cpp"
  append(L"&quot;");
                                                            #line 113 "CodeGeneratorXSLT.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 215 "CodeGeneratorXSLT.cpp"
  append(L"'");
                                                            #line 116 "CodeGeneratorXSLT.cpp.template"
                                                                  }
                                                                  const char *c = s;
                                                                  for (; *c; ++c)
                                                                  {
                                                                    if (*c == '"')
                                                                    {
                                                                      print(s, c - s);
                                                                      print("&quot;&quot;");
                                                                      s = c + 1;
                                                                    }
                                                                    else if (*c == '<')
                                                                    {
                                                                      print(s, c - s);
                                                                      print("&lt;");
                                                                      s = c + 1;
                                                                    }
                                                                    else if (*c == '>')
                                                                    {
                                                                      print(s, c - s);
                                                                      print("&gt;");
                                                                      s = c + 1;
                                                                    }
                                                                    else if (*c == '&')
                                                                    {
                                                                      print(s, c - s);
                                                                      print("&amp;");
                                                                      s = c + 1;
                                                                    }
                                                                  }
                                                                  if (c != s) print(s, c - s);
                                                                  if (literal)
                                                                  {
                                                            #line 250 "CodeGeneratorXSLT.cpp"
  append(L"&quot;");
                                                            #line 148 "CodeGeneratorXSLT.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 256 "CodeGeneratorXSLT.cpp"
  append(L"'");
                                                            #line 151 "CodeGeneratorXSLT.cpp.template"
                                                                  }
                                                                }
                                                            #line 261 "CodeGeneratorXSLT.cpp"
  append(L"\n");
  append(L"\"/>");
                                                            #line 154 "CodeGeneratorXSLT.cpp.template"
                                                              }
                                                            #line 266 "CodeGeneratorXSLT.cpp"
  append(L"\n");
                                                            #line 156 "CodeGeneratorXSLT.cpp.template"
                                                              if (variable("trace").boolean())
                                                              {
                                                            #line 271 "CodeGeneratorXSLT.cpp"
  append(L"\n");
  append(L"<!--");
  append(L"~");
  append(L"\n");
  append(L" ! Pass a line to fn:trace, without generating a result. Actually,\n");
  append(L" ! create an empty result, but make it somehow dependent on trace,\n");
  append(L" ! so the optimizer does not eliminate the trace call.\n");
  append(L" !\n");
  append(L" ! @param $line the line to be traced.\n");
  append(L" ! @return the empty sequence.\n");
  append(L"-->\n");
  append(L"<xsl:function name=\"p:trace\" as=\"empty-sequence()\">\n");
  append(L"  <xsl:param name=\"line\" as=\"xs:string\"/>\n");
  append(L"\n");
  append(L"  <xsl:sequence select=\"if (trace($line, 'trace')) then () else ''[.]\"/>\n");
  append(L"</xsl:function>\n");
  append(L"\n");
  append(L"<!--");
  append(L"~");
  append(L"\n");
  append(L" ! Add escaping to a string for being placed in XML attribute or\n");
  append(L" ! element content.\n");
  append(L" !\n");
  append(L" ! @param $s the string to be escaped.\n");
  append(L" ! @return the escaped string.\n");
  append(L"-->\n");
  append(L"<xsl:function name=\"p:xml-escape\" as=\"xs:string\">\n");
  append(L"  <xsl:param name=\"s\" as=\"xs:string\"/>\n");
  append(L"\n");
  append(L"  <xsl:sequence select=\"\n");
  append(L"    replace(\n");
  append(L"    replace(\n");
  append(L"    replace($s, '&amp;', '&amp;amp;'),\n");
  append(L"                '&lt;', '&amp;lt;'),\n");
  append(L"                '&quot;', '&amp;quot;')\n");
  append(L"  \"/>\n");
  append(L"</xsl:function>\n");
                                                            #line 191 "CodeGeneratorXSLT.cpp.template"
                                                              }
                                                              if (   variable("embedded").boolean()
                                                                  && variable("tables").boolean())
                                                              {
                                                            #line 314 "CodeGeneratorXSLT.cpp"
  append(L"\n");
  append(L"<!--");
  append(L"~");
  append(L"\n");
  append(L" ! Predict the decision for a given decision point based on current\n");
  append(L" ! lookahead.\n");
  append(L" !\n");
  append(L" ! @param $input the input string.\n");
  append(L" ! @param $state the parser state.\n");
  append(L" ! @param $dpi the decision point index.");
                                                            #line 202 "CodeGeneratorXSLT.cpp.template"
                                                                if (variable("useGlr").boolean())
                                                                {
                                                            #line 328 "CodeGeneratorXSLT.cpp"
  append(L"\n");
  append(L" : @param $id the parsing thread id.");
                                                            #line 205 "CodeGeneratorXSLT.cpp.template"
                                                                }
                                                            #line 333 "CodeGeneratorXSLT.cpp"
  append(L"\n");
  append(L" ! @return the updated parser state.\n");
  append(L"-->\n");
  append(L"<xsl:function name=\"p:predict\" as=\"item()+\">\n");
  append(L"  <xsl:param name=\"input\" as=\"xs:string\"/>\n");
  append(L"  <xsl:param name=\"state\" as=\"item()+\"/>\n");
  append(L"  <xsl:param name=\"dpi\" as=\"xs:integer\"/>");
                                                            #line 212 "CodeGeneratorXSLT.cpp.template"
                                                                if (variable("useGlr").boolean())
                                                                {
                                                            #line 344 "CodeGeneratorXSLT.cpp"
  append(L"\n");
  append(L"  <xsl:param name=\"id\" as=\"xs:integer\"/>");
                                                            #line 215 "CodeGeneratorXSLT.cpp.template"
                                                                }
                                                            #line 349 "CodeGeneratorXSLT.cpp"
  append(L"\n");
                                                            #line 217 "CodeGeneratorXSLT.cpp.template"
                                                                if (variable("lrparser").boolean())
                                                                {
                                                            #line 354 "CodeGeneratorXSLT.cpp"
  append(L"\n");
  append(L"  <xsl:variable name=\"state\" select=\"p:lookahead1");
                                                            #line 220 "CodeGeneratorXSLT.cpp.template"
                                                                  if (variable("anyWhitespace").boolean())
                                                                  {
                                                            #line 360 "CodeGeneratorXSLT.cpp"
  append(L"W");
                                                            #line 222 "CodeGeneratorXSLT.cpp.template"
                                                                  }
                                                            #line 364 "CodeGeneratorXSLT.cpp"
  append(L"($p:TOKENSET[$dpi + 1], $input, $state");
                                                            #line 224 "CodeGeneratorXSLT.cpp.template"
                                                                  if (variable("useGlr").boolean())
                                                                  {
                                                            #line 369 "CodeGeneratorXSLT.cpp"
  append(L", $id");
                                                            #line 226 "CodeGeneratorXSLT.cpp.template"
                                                                  }
                                                            #line 373 "CodeGeneratorXSLT.cpp"
  append(L")\"/>");
                                                            #line 228 "CodeGeneratorXSLT.cpp.template"
                                                                }
                                                            #line 377 "CodeGeneratorXSLT.cpp"
  append(L"\n");
  append(L"  <xsl:choose>\n");
  append(L"    <xsl:when test=\"$state[$p:l1] lt 0\">\n");
  append(L"      <xsl:variable name=\"node\">\n");
  append(L"        <xsl:element name=\"error\">\n");
  append(L"          <xsl:attribute name=\"b\" select=\"$state[$p:b1]\"/>\n");
  append(L"          <xsl:attribute name=\"e\" select=\"$state[$p:e1]\"/>\n");
  append(L"          <xsl:attribute name=\"s\" select=\"- $state[$p:l1]\"/>\n");
  append(L"        </xsl:element>\n");
  append(L"      </xsl:variable>\n");
  append(L"      <xsl:sequence select=\"\n");
  append(L"        0,\n");
  append(L"        subsequence($state, $p:lk + 1");
                                                            #line 241 "CodeGeneratorXSLT.cpp.template"
                                                                if (variable("useGlr").boolean())
                                                                {
                                                            #line 394 "CodeGeneratorXSLT.cpp"
  append(L")");
                                                            #line 243 "CodeGeneratorXSLT.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 400 "CodeGeneratorXSLT.cpp"
  append(L", $p:error - $p:lk - 1),\n");
  append(L"        $node/node(),\n");
  append(L"        subsequence($state, $p:error + 1)");
                                                            #line 248 "CodeGeneratorXSLT.cpp.template"
                                                                }
                                                            #line 406 "CodeGeneratorXSLT.cpp"
  append(L"\n");
  append(L"      \"/>\n");
  append(L"    </xsl:when>\n");
  append(L"    <xsl:otherwise>");
                                                            #line 253 "CodeGeneratorXSLT.cpp.template"
                                                                indent += 2;
                                                            #line 413 "CodeGeneratorXSLT.cpp"
  append(L"\n");
                                                            #line 255 "CodeGeneratorXSLT.cpp.template"
                                                                int k = variable("k").integer();
                                                                const char *action = "<xsl:variable name=\"action\" select=\"";
                                                                compressedMap2dAccessor("$state[$p:l1]", "$dpi", variable("cicols").integer(),
                                                                                            2, "j1", action, "$p:CASEID", &variable("cibits").integer());
                                                                bool loop = k > 1 && variable("lrparser").boolean();
                                                                for (int i = 2; i <= k; ++i)
                                                                {
                                                            #line 423 "CodeGeneratorXSLT.cpp"
  append(L"\n");
  append(L"  <xsl:choose>\n");
  append(L"    <xsl:when test=\"$action mod 2 eq 0\">\n");
  append(L"      <xsl:sequence select=\"$action idiv 2, subsequence($state, $p:lk + 1)\"/>\n");
  append(L"    </xsl:when>\n");
  append(L"    <xsl:otherwise>\n");
  append(L"      <xsl:variable name=\"state\" select=\"p:lookahead");
                                                            #line 268 "CodeGeneratorXSLT.cpp.template"
                                                                  print(format.toString<char>(i));
                                                                  if (variable("anyWhitespace").boolean())
                                                                  {
                                                            #line 435 "CodeGeneratorXSLT.cpp"
  append(L"W");
                                                            #line 271 "CodeGeneratorXSLT.cpp.template"
                                                                  }
                                                            #line 439 "CodeGeneratorXSLT.cpp"
  append(L"(");
                                                            #line 272 "CodeGeneratorXSLT.cpp.template"
                                                                  if (variable("unlimitedLookahead").boolean())
                                                                  {
                                                            #line 444 "CodeGeneratorXSLT.cpp"
  append(L"0, ");
                                                            #line 274 "CodeGeneratorXSLT.cpp.template"
                                                                  }
                                                            #line 448 "CodeGeneratorXSLT.cpp"
  append(L"$action idiv 2, $input, $state)\"/>\n");
  append(L"      <xsl:choose>\n");
  append(L"        <xsl:when test=\"$state[$p:l");
                                                            #line 277 "CodeGeneratorXSLT.cpp.template"
                                                                  print(format.toString<char>(i));
                                                            #line 454 "CodeGeneratorXSLT.cpp"
  append(L"] lt 0\">\n");
  append(L"          <xsl:sequence select=\"0, subsequence($state, $p:lk + 1)\"/>\n");
  append(L"        </xsl:when>\n");
  append(L"        <xsl:otherwise>");
                                                            #line 281 "CodeGeneratorXSLT.cpp.template"
                                                                  indent += 2;
                                                            #line 461 "CodeGeneratorXSLT.cpp"
  append(L"\n");
                                                            #line 283 "CodeGeneratorXSLT.cpp.template"
                                                                  CString li("$state[$p:l");
                                                                  li += format.toString<char>(i);
                                                                  li += "]";
                                                                  CString ii("i");
                                                                  ii += format.toString<char>(i);
                                                                  compressedMap2dAccessor(i == 2 ? "$state[$p:l1]" : "$lk", li.c_str(), variable("lxcols").integer(),
                                                                                              6, ii.c_str(), "<xsl:variable name=\"lk\" select=\"", "$p:LOOKAHEAD", &variable("lxbits").integer());
                                                            #line 471 "CodeGeneratorXSLT.cpp"
  append(L"\n");
  append(L"      <xsl:choose>\n");
  append(L"        <xsl:when test=\"$lk eq 0\">");
                                                            #line 292 "CodeGeneratorXSLT.cpp.template"
                                                                  if (loop)
                                                                  {
                                                            #line 478 "CodeGeneratorXSLT.cpp"
  append(L"\n");
  append(L"          <xsl:sequence select=\"p:predict($input, $state, $dpi + 1)\"/>");
                                                            #line 296 "CodeGeneratorXSLT.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 485 "CodeGeneratorXSLT.cpp"
  append(L"\n");
  append(L"          <xsl:sequence select=\"0, subsequence($state, $p:lk + 1)\"/>");
                                                            #line 301 "CodeGeneratorXSLT.cpp.template"
                                                                  }
                                                            #line 490 "CodeGeneratorXSLT.cpp"
  append(L"\n");
  append(L"        </xsl:when>\n");
  append(L"        <xsl:otherwise>");
                                                            #line 304 "CodeGeneratorXSLT.cpp.template"
                                                                  indent += 1;
                                                            #line 496 "CodeGeneratorXSLT.cpp"
  append(L"\n");
                                                            #line 306 "CodeGeneratorXSLT.cpp.template"
                                                                  CString ji("j");
                                                                  ji += format.toString<char>(i);
                                                                  compressedMap2dAccessor("$lk", "$dpi", variable("cicols").integer(),
                                                                                              8, ji.c_str(), "<xsl:variable name=\"action\" select=\"", "$p:CASEID", &variable("cibits").integer());
                                                                  indent += 3;
                                                                }
                                                                if (loop)
                                                                {
                                                            #line 507 "CodeGeneratorXSLT.cpp"
  append(L"\n");
  append(L"  <xsl:sequence select=\"\n");
  append(L"    if ($action ne 0) then\n");
  append(L"      ($action idiv 2, subsequence($state, $p:lk + 1))\n");
  append(L"    else\n");
  append(L"      p:predict($input, $state, $dpi + 1)\n");
  append(L"  \"/>");
                                                            #line 320 "CodeGeneratorXSLT.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 519 "CodeGeneratorXSLT.cpp"
  append(L"\n");
  append(L"  <xsl:sequence select=\"$action idiv 2, subsequence($state, $p:lk + 1)\"/>");
                                                            #line 325 "CodeGeneratorXSLT.cpp.template"
                                                                }
                                                                indent -= 5;
                                                                for (int i = 2; i <= k; ++i)
                                                                {
                                                            #line 527 "CodeGeneratorXSLT.cpp"
  append(L"\n");
  append(L"          </xsl:otherwise>\n");
  append(L"        </xsl:choose>\n");
  append(L"      </xsl:otherwise>\n");
  append(L"    </xsl:choose>\n");
  append(L"  </xsl:otherwise>\n");
  append(L"</xsl:choose>");
                                                            #line 335 "CodeGeneratorXSLT.cpp.template"
                                                                  indent -= 6;
                                                                }
                                                                indent += 3;
                                                            #line 539 "CodeGeneratorXSLT.cpp"
  append(L"\n");
  append(L"    </xsl:otherwise>\n");
  append(L"  </xsl:choose>\n");
  append(L"</xsl:function>\n");
                                                            #line 342 "CodeGeneratorXSLT.cpp.template"
                                                              }
                                                            #line 546 "CodeGeneratorXSLT.cpp"
  append(L"\n");
  append(L"<!--");
  append(L"~");
  append(L"\n");
  append(L" ! Match next token in input string, starting at given index, using\n");
  append(L" ! the DFA entry state for the set of tokens that are expected in\n");
  append(L" ! the current context.\n");
  append(L" !\n");
  append(L" ! @param $input the input string.\n");
  append(L" ! @param $begin the index where to start in input string.\n");
  append(L" ! @param $token-set the expected token set id.");
                                                            #line 351 "CodeGeneratorXSLT.cpp.template"
                                                              if (variable("useGlr").boolean())
                                                              {
                                                            #line 561 "CodeGeneratorXSLT.cpp"
  append(L"\n");
  append(L" : @param $id the parsing thread id.");
                                                            #line 354 "CodeGeneratorXSLT.cpp.template"
                                                              }
                                                            #line 566 "CodeGeneratorXSLT.cpp"
  append(L"\n");
  append(L" ! @return a sequence of three: the token code of the result token,\n");
  append(L" ! with input string begin and end positions. If there is no valid\n");
  append(L" ! token, return the negative id of the DFA state that failed, along\n");
  append(L" ! with begin and end positions of the longest viable prefix.\n");
  append(L"-->\n");
  append(L"<xsl:function name=\"p:match\" as=\"xs:integer+\">\n");
  append(L"  <xsl:param name=\"input\" as=\"xs:string\"/>\n");
  append(L"  <xsl:param name=\"begin\" as=\"xs:integer\"/>\n");
  append(L"  <xsl:param name=\"token-set\" as=\"xs:integer\"/>");
                                                            #line 364 "CodeGeneratorXSLT.cpp.template"
                                                              if (variable("useGlr").boolean())
                                                              {
                                                            #line 580 "CodeGeneratorXSLT.cpp"
  append(L"\n");
  append(L"  <xsl:param name=\"id\" as=\"xs:integer\"/>");
                                                            #line 367 "CodeGeneratorXSLT.cpp.template"
                                                              }
                                                            #line 585 "CodeGeneratorXSLT.cpp"
  append(L"\n");
                                                            #line 369 "CodeGeneratorXSLT.cpp.template"
                                                              if (variable("trace").boolean())
                                                              {
                                                            #line 590 "CodeGeneratorXSLT.cpp"
  append(L"\n");
  append(L"  <xsl:sequence select=\"p:trace(concat('  &lt;tokenize ");
                                                            #line 372 "CodeGeneratorXSLT.cpp.template"
                                                                if (variable("useGlr").boolean())
                                                                {
                                                            #line 596 "CodeGeneratorXSLT.cpp"
  append(L"thread=&quot;', $id, '&quot; ");
                                                            #line 374 "CodeGeneratorXSLT.cpp.template"
                                                                }
                                                            #line 600 "CodeGeneratorXSLT.cpp"
  append(L"tokenset=&quot;', $token-set, '&quot;&gt;'))\"/>");
                                                            #line 376 "CodeGeneratorXSLT.cpp.template"
                                                              }
                                                            #line 604 "CodeGeneratorXSLT.cpp"
  append(L"\n");
  append(L"  <xsl:variable name=\"result\" select=\"$p:INITIAL[1 + $token-set]\"/>\n");
  append(L"  <xsl:sequence select=\"p:transition($input, $begin, $begin, $begin, $result, $result mod ");
                                                            #line 380 "CodeGeneratorXSLT.cpp.template"
                                                              print(Math::powerof(2, variable("stateCodeBits").integer()));
                                                            #line 610 "CodeGeneratorXSLT.cpp"
  append(L", 0)\"/>\n");
  append(L"</xsl:function>\n");
  append(L"\n");
  append(L"<!--");
  append(L"~");
  append(L"\n");
  append(L" ! The DFA state transition function. If we are in a valid DFA state, save\n");
  append(L" ! it's result annotation, consume one input codepoint, calculate the next\n");
  append(L" ! state, and use tail recursion to do the same again. Otherwise, return\n");
  append(L" ! any valid result or a negative DFA state id in case of an error.\n");
  append(L" !\n");
  append(L" ! @param $input the input string.\n");
  append(L" ! @param $begin the begin index of the current token in the input string.\n");
  append(L" ! @param $current the index of the current position in the input string.\n");
  append(L" ! @param $end the end index of the result in the input string.\n");
  append(L" ! @param $result the result code.\n");
  append(L" ! @param $current-state the current DFA state.\n");
  append(L" ! @param $previous-state the  previous DFA state.\n");
  append(L" ! @return a sequence of three: the token code of the result token,\n");
  append(L" ! with input string begin and end positions. If there is no valid\n");
  append(L" ! token, return the negative id of the DFA state that failed, along\n");
  append(L" ! with begin and end positions of the longest viable prefix.\n");
  append(L"-->\n");
  append(L"<xsl:function name=\"p:transition\">\n");
  append(L"  <xsl:param name=\"input\" as=\"xs:string\"/>\n");
  append(L"  <xsl:param name=\"begin\" as=\"xs:integer\"/>\n");
  append(L"  <xsl:param name=\"current\" as=\"xs:integer\"/>\n");
  append(L"  <xsl:param name=\"end\" as=\"xs:integer\"/>\n");
  append(L"  <xsl:param name=\"result\" as=\"xs:integer\"/>\n");
  append(L"  <xsl:param name=\"current-state\" as=\"xs:integer\"/>\n");
  append(L"  <xsl:param name=\"previous-state\" as=\"xs:integer\"/>\n");
  append(L"\n");
  append(L"  <xsl:choose>\n");
  append(L"    <xsl:when test=\"$current-state eq 0\">\n");
  append(L"      <xsl:variable name=\"result\" select=\"$result idiv ");
                                                            #line 413 "CodeGeneratorXSLT.cpp.template"
                                                              print(Math::powerof(2, variable("stateCodeBits").integer()));
                                                            #line 648 "CodeGeneratorXSLT.cpp"
  append(L"\"/>");
                                                            #line 414 "CodeGeneratorXSLT.cpp.template"
                                                              if (0 == variable("maxcontextlength").integer())
                                                              {
                                                                if (variable("hasfixedtokenlength").boolean())
                                                                {
                                                            #line 655 "CodeGeneratorXSLT.cpp"
  append(L"\n");
  append(L"      <xsl:variable name=\"end\" select=\"if ($result idiv ");
                                                            #line 419 "CodeGeneratorXSLT.cpp.template"
                                                                  print(Math::powerof(2, variable("tokencodeBits").integer()));
                                                            #line 660 "CodeGeneratorXSLT.cpp"
  append(L" ne 0) then $begin else $end\"/>");
                                                            #line 421 "CodeGeneratorXSLT.cpp.template"
                                                                }
                                                              }
                                                              else if (! variable("hasfixedtokenlength").boolean())
                                                              {
                                                            #line 667 "CodeGeneratorXSLT.cpp"
  append(L"\n");
  append(L"      <xsl:variable name=\"end\" select=\"$end - $result idiv ");
                                                            #line 426 "CodeGeneratorXSLT.cpp.template"
                                                                print(Math::powerof(2, variable("tokencodeBits").integer()));
                                                            #line 672 "CodeGeneratorXSLT.cpp"
  append(L"\"/>");
                                                            #line 428 "CodeGeneratorXSLT.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 678 "CodeGeneratorXSLT.cpp"
  append(L"\n");
  append(L"      <xsl:variable name=\"end\" select=\"\n");
  append(L"        if ($result idiv ");
                                                            #line 433 "CodeGeneratorXSLT.cpp.template"
                                                                  print(Math::powerof(2, variable("tokencodeBits").integer()));
                                                            #line 684 "CodeGeneratorXSLT.cpp"
  append(L" mod 2 eq 1) then\n");
  append(L"          $begin + $result idiv ");
                                                            #line 435 "CodeGeneratorXSLT.cpp.template"
                                                                  print(Math::powerof(2, 1 + variable("tokencodeBits").integer()));
                                                            #line 689 "CodeGeneratorXSLT.cpp"
  append(L"\n");
  append(L"        else\n");
  append(L"          $end - $result idiv ");
                                                            #line 438 "CodeGeneratorXSLT.cpp.template"
                                                                  print(Math::powerof(2, 1 + variable("tokencodeBits").integer()));
                                                            #line 695 "CodeGeneratorXSLT.cpp"
  append(L"\n");
  append(L"      \"/>");
                                                            #line 440 "CodeGeneratorXSLT.cpp.template"
                                                              }
                                                            #line 700 "CodeGeneratorXSLT.cpp"
  append(L"\n");
  append(L"      <xsl:variable name=\"end\" select=\"if ($end gt string-length($input)) then string-length($input) + 1 else $end\"/>\n");
  append(L"      <xsl:sequence select=\"\n");
  append(L"        if ($result ne 0) then\n");
  append(L"        (");
                                                            #line 445 "CodeGeneratorXSLT.cpp.template"
                                                              if (variable("trace").boolean())
                                                              {
                                                            #line 709 "CodeGeneratorXSLT.cpp"
  append(L"\n");
  append(L"          p:trace(concat('    &lt;done result=&quot;', p:xml-escape($p:TOKEN[$result");
                                                            #line 449 "CodeGeneratorXSLT.cpp.template"
                                                                if (   0 != variable("maxcontextlength").integer()
                                                                    || variable("hasfixedtokenlength").boolean())
                                                                {
                                                            #line 716 "CodeGeneratorXSLT.cpp"
  append(L" mod ");
                                                            #line 452 "CodeGeneratorXSLT.cpp.template"
                                                                  print(Math::powerof(2, variable("tokencodeBits").integer()));
                                                                }
                                                            #line 721 "CodeGeneratorXSLT.cpp"
  append(L"]), '&quot; begin=&quot;', $begin, '&quot; end=&quot;', $end, '&quot;/&gt;')),\n");
  append(L"          p:trace('  &lt;/tokenize&gt;'),");
                                                            #line 456 "CodeGeneratorXSLT.cpp.template"
                                                              }
                                                              if (0 == variable("maxcontextlength").integer() && ! variable("hasfixedtokenlength").boolean())
                                                              {
                                                            #line 728 "CodeGeneratorXSLT.cpp"
  append(L"\n");
  append(L"          $result - 1,");
                                                            #line 460 "CodeGeneratorXSLT.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 735 "CodeGeneratorXSLT.cpp"
  append(L"\n");
  append(L"          $result mod ");
                                                            #line 464 "CodeGeneratorXSLT.cpp.template"
                                                                print(Math::powerof(2, variable("tokencodeBits").integer()));
                                                            #line 740 "CodeGeneratorXSLT.cpp"
  append(L" - 1,");
                                                            #line 465 "CodeGeneratorXSLT.cpp.template"
                                                              }
                                                            #line 744 "CodeGeneratorXSLT.cpp"
  append(L"\n");
  append(L"          $begin,\n");
  append(L"          $end\n");
  append(L"        )\n");
  append(L"        else\n");
  append(L"        (");
                                                            #line 471 "CodeGeneratorXSLT.cpp.template"
                                                              if (variable("trace").boolean())
                                                              {
                                                            #line 754 "CodeGeneratorXSLT.cpp"
  append(L"\n");
  append(L"          p:trace(concat('    &lt;fail begin=&quot;', $begin, '&quot; end=&quot;', $current - 1, '&quot; state=&quot;', $previous-state, '&quot;/&gt;')),\n");
  append(L"          p:trace('  &lt;/tokenize&gt;'),");
                                                            #line 476 "CodeGeneratorXSLT.cpp.template"
                                                              }
                                                            #line 760 "CodeGeneratorXSLT.cpp"
  append(L"\n");
  append(L"          - $previous-state,\n");
  append(L"          $begin,\n");
  append(L"          $current - 1\n");
  append(L"        )\n");
  append(L"      \"/>\n");
  append(L"    </xsl:when>\n");
  append(L"    <xsl:otherwise>\n");
  append(L"      <xsl:variable name=\"c0\" select=\"(string-to-codepoints(substring($input, $current, 1)), 0)[1]\"/>\n");
  append(L"      <xsl:variable name=\"c1\" as=\"xs:integer\">\n");
  append(L"        <xsl:choose>\n");
  append(L"          <xsl:when test=\"$c0 &lt; ");
                                                            #line 488 "CodeGeneratorXSLT.cpp.template"
                                                              print(variable("simplifiedCodeMap").integer());
                                                            #line 775 "CodeGeneratorXSLT.cpp"
  append(L"\">\n");
  append(L"            <xsl:sequence select=\"$p:MAP0[1 + $c0]\"/>\n");
  append(L"          </xsl:when>\n");
  append(L"          <xsl:when test=\"$c0 &lt; ");
                                                            #line 492 "CodeGeneratorXSLT.cpp.template"
                                                              print(variable("uncompressedMapSize").integer());
                                                            #line 782 "CodeGeneratorXSLT.cpp"
  append(L"\">");
                                                            #line 493 "CodeGeneratorXSLT.cpp.template"
                                                                        const int *m1bits = &variable("m1bits").integer();
                                                              for (size_t i = 0; m1bits[i]; ++i)
                                                              {
                                                            #line 788 "CodeGeneratorXSLT.cpp"
  append(L"\n");
  append(L"            <xsl:variable name=\"c");
                                                            #line 497 "CodeGeneratorXSLT.cpp.template"
                                                                print(i + 1);
                                                            #line 793 "CodeGeneratorXSLT.cpp"
  append(L"\" select=\"$c");
                                                            #line 498 "CodeGeneratorXSLT.cpp.template"
                                                                print(i);
                                                            #line 797 "CodeGeneratorXSLT.cpp"
  append(L" idiv ");
                                                            #line 499 "CodeGeneratorXSLT.cpp.template"
                                                                print(Math::powerof(2, m1bits[i]));
                                                            #line 801 "CodeGeneratorXSLT.cpp"
  append(L"\"/>");
                                                            #line 500 "CodeGeneratorXSLT.cpp.template"
                                                              }
                                                            #line 805 "CodeGeneratorXSLT.cpp"
  append(L"\n");
  append(L"            <xsl:sequence select=\"$p:MAP1[1 + $c0");
                                                            #line 502 "CodeGeneratorXSLT.cpp.template"
                                                              for (size_t i = 0; m1bits[i]; ++i)
                                                              {
                                                            #line 811 "CodeGeneratorXSLT.cpp"
  append(L" mod ");
                                                            #line 504 "CodeGeneratorXSLT.cpp.template"
                                                                print(Math::powerof(2, m1bits[i]));
                                                            #line 815 "CodeGeneratorXSLT.cpp"
  append(L" + $p:MAP1[1 + $c");
                                                            #line 506 "CodeGeneratorXSLT.cpp.template"
                                                                print(i + 1);
                                                              }
                                                              for (size_t i = 0; m1bits[i]; ++i)
                                                              {
                                                            #line 822 "CodeGeneratorXSLT.cpp"
  append(L"]");
                                                            #line 511 "CodeGeneratorXSLT.cpp.template"
                                                              }
                                                            #line 826 "CodeGeneratorXSLT.cpp"
  append(L"]\"/>\n");
  append(L"          </xsl:when>\n");
  append(L"          <xsl:otherwise>\n");
  append(L"            <xsl:sequence select=\"");
                                                            #line 515 "CodeGeneratorXSLT.cpp.template"
                                                              if (variable("m2").size == 0)
                                                              {
                                                            #line 834 "CodeGeneratorXSLT.cpp"
  append(L"0");
                                                            #line 517 "CodeGeneratorXSLT.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 840 "CodeGeneratorXSLT.cpp"
  append(L"p:map2($c0, 1, ");
                                                            #line 520 "CodeGeneratorXSLT.cpp.template"
                                                                print(variable("m2").size / 3);
                                                            #line 844 "CodeGeneratorXSLT.cpp"
  append(L")");
                                                            #line 521 "CodeGeneratorXSLT.cpp.template"
                                                              }
                                                            #line 848 "CodeGeneratorXSLT.cpp"
  append(L"\"/>\n");
  append(L"          </xsl:otherwise>\n");
  append(L"        </xsl:choose>\n");
  append(L"      </xsl:variable>\n");
  append(L"      <xsl:variable name=\"current\" select=\"$current + 1\"/>\n");
                                                            #line 527 "CodeGeneratorXSLT.cpp.template"
                                                              const int *a1bits = &variable("a1bits").integer();
                                                              compressedMap2dAccessor("$current-state - 1", "$c1", variable("a1cols").integer(),
                                                                                          6, "i", "<xsl:variable name=\"next-state\" select=\"", "$p:TRANSITION", a1bits);
                                                            #line 858 "CodeGeneratorXSLT.cpp"
  append(L"\n");
  append(L"      <xsl:sequence select=\"");
                                                            #line 531 "CodeGeneratorXSLT.cpp.template"
                                                              if (variable("trace").boolean())
                                                              {
                                                            #line 864 "CodeGeneratorXSLT.cpp"
  append(L"\n");
  append(L"        p:trace\n");
  append(L"        (\n");
  append(L"          string-join\n");
  append(L"          (\n");
  append(L"            (\n");
  append(L"              '    &lt;next state=&quot;', string($current-state), '&quot;',\n");
  append(L"              ' offset=&quot;', string($current - 1), '&quot;',\n");
  append(L"              if ($c0 lt 32 or $c0 gt 126) then\n");
  append(L"                ()\n");
  append(L"              else\n");
  append(L"                (' char=&quot;', p:xml-escape(substring($input, $current - 1, 1)), '&quot;'),\n");
  append(L"              ' codepoint=&quot;', string($c0), '&quot;',\n");
  append(L"              ' class=&quot;', string($c1), '&quot;',\n");
  append(L"              if ($next-state lt ");
                                                            #line 547 "CodeGeneratorXSLT.cpp.template"
                                                                print(Math::powerof(2, variable("stateCodeBits").integer()));
                                                            #line 882 "CodeGeneratorXSLT.cpp"
  append(L") then\n");
  append(L"                ()\n");
  append(L"              else\n");
  append(L"              (\n");
  append(L"                ' result=&quot;',\n");
  append(L"                p:xml-escape($p:TOKEN[$next-state idiv ");
                                                            #line 553 "CodeGeneratorXSLT.cpp.template"
                                                                print(Math::powerof(2, variable("stateCodeBits").integer()));
                                                            #line 891 "CodeGeneratorXSLT.cpp"
  append(L" mod ");
                                                            #line 554 "CodeGeneratorXSLT.cpp.template"
                                                                print(Math::powerof(2, variable("tokencodeBits").integer()));
                                                            #line 895 "CodeGeneratorXSLT.cpp"
  append(L"]), '&quot;',\n");
  append(L"                if ($next-state lt ");
                                                            #line 556 "CodeGeneratorXSLT.cpp.template"
                                                                int contextOffset = variable("stateCodeBits").integer()
                                                                                  + variable("tokencodeBits").integer();
                                                                int sizeOffset = contextOffset
                                                                               + (variable("hasfixedtokenlength").boolean() ? 1 : 0);
                                                                print(Math::powerof(2, sizeOffset));
                                                            #line 904 "CodeGeneratorXSLT.cpp"
  append(L") then\n");
  append(L"                  ''\n");
  append(L"                else\n");
  append(L"                  (' trailing-context-size=&quot;', string($next-state idiv ");
                                                            #line 565 "CodeGeneratorXSLT.cpp.template"
                                                                print(Math::powerof(2, sizeOffset));
                                                            #line 911 "CodeGeneratorXSLT.cpp"
  append(L"), '&quot;')\n");
  append(L"              ),\n");
  append(L"              '/&gt;'\n");
  append(L"            ),\n");
  append(L"            ''\n");
  append(L"          )\n");
  append(L"        ),");
                                                            #line 572 "CodeGeneratorXSLT.cpp.template"
                                                              }
                                                            #line 921 "CodeGeneratorXSLT.cpp"
  append(L"\n");
  append(L"        if ($next-state &gt; ");
                                                            #line 574 "CodeGeneratorXSLT.cpp.template"
                                                              print(Math::powerof(2, variable("stateCodeBits").integer()) - 1);
                                                            #line 926 "CodeGeneratorXSLT.cpp"
  append(L") then\n");
  append(L"          p:transition($input, $begin, $current, $current, $next-state, $next-state mod ");
                                                            #line 577 "CodeGeneratorXSLT.cpp.template"
                                                              print(Math::powerof(2, variable("stateCodeBits").integer()));
                                                            #line 931 "CodeGeneratorXSLT.cpp"
  append(L", $current-state)\n");
  append(L"        else\n");
  append(L"          p:transition($input, $begin, $current, $end, $result, $next-state, $current-state)");
  append(L"\n");
  append(L"      \"/>\n");
  append(L"    </xsl:otherwise>\n");
  append(L"  </xsl:choose>\n");
  append(L"</xsl:function>\n");
  append(L"\n");
  append(L"<!--");
  append(L"~");
  append(L"\n");
  append(L" ! Recursively translate one 32-bit chunk of an expected token bitset\n");
  append(L" ! to the corresponding sequence of token strings.\n");
  append(L" !\n");
  append(L" ! @param $result the result of previous recursion levels.\n");
  append(L" ! @param $chunk the 32-bit chunk of the expected token bitset.\n");
  append(L" ! @param $base-token-code the token code of bit 0 in the current chunk.\n");
  append(L" ! @return the set of token strings.\n");
  append(L"-->\n");
  append(L"<xsl:function name=\"p:token\">\n");
  append(L"  <xsl:param name=\"result\" as=\"xs:string*\"/>\n");
  append(L"  <xsl:param name=\"chunk\" as=\"xs:integer\"/>\n");
  append(L"  <xsl:param name=\"base-token-code\" as=\"xs:integer\"/>\n");
  append(L"\n");
  append(L"  <xsl:sequence select=\"\n");
  append(L"    if ($chunk = 0) then\n");
  append(L"      $result\n");
  append(L"    else\n");
  append(L"      p:token\n");
  append(L"      (\n");
  append(L"        ($result, if ($chunk mod 2 != 0) then $p:TOKEN[$base-token-code] else ()),\n");
  append(L"        if ($chunk &lt; 0) then $chunk idiv 2 + 2147483648 else $chunk idiv 2,\n");
  append(L"        $base-token-code + 1\n");
  append(L"      )\n");
  append(L"  \"/>\n");
  append(L"</xsl:function>\n");
                                                            #line 613 "CodeGeneratorXSLT.cpp.template"
                                                              if (defined("gtbits"))
                                                              {
                                                            #line 972 "CodeGeneratorXSLT.cpp"
  append(L"\n");
  append(L"<!--");
  append(L"~");
  append(L"\n");
  append(L" ! Get GOTO table entry for given nonterminal and parser state.\n");
  append(L" !\n");
  append(L" ! @param $nonterminal the nonterminal.\n");
  append(L" ! @param $state the LR parser state.\n");
  append(L" ! @return the GOTO table entry.\n");
  append(L"-->\n");
  append(L"<xsl:function name=\"p:goto\" as=\"xs:integer\">\n");
  append(L"  <xsl:param name=\"nonterminal\" as=\"xs:integer\"/>\n");
  append(L"  <xsl:param name=\"state\" as=\"xs:integer\"/>\n");
  append(L"\n");
                                                            #line 627 "CodeGeneratorXSLT.cpp.template"
                                                                compressedMap2dAccessor("$nonterminal",
                                                                                            "$state",
                                                                                            variable("gtcols").integer(),
                                                                                            2,
                                                                                            "i",
                                                                                            "<xsl:sequence select=\"",
                                                                                            "$p:GOTO",
                                                                                            &variable("gtbits").integer());
                                                            #line 996 "CodeGeneratorXSLT.cpp"
  append(L"\n");
  append(L"</xsl:function>\n");
                                                            #line 637 "CodeGeneratorXSLT.cpp.template"
                                                              }
                                                            #line 1001 "CodeGeneratorXSLT.cpp"
  append(L"\n");
  append(L"<!--");
  append(L"~");
  append(L"\n");
  append(L" ! Calculate expected token set for a given DFA state as a sequence\n");
  append(L" ! of strings.\n");
  append(L" !\n");
  append(L" ! @param $state the DFA state.\n");
  append(L" ! @return the set of token strings\n");
  append(L"-->\n");
  append(L"<xsl:function name=\"p:expected-token-set\" as=\"xs:string*\">\n");
  append(L"  <xsl:param name=\"state\" as=\"xs:integer\"/>\n");
  append(L"\n");
  append(L"  <xsl:if test=\"$state > 0\">\n");
  append(L"    <xsl:for-each select=\"0 to ");
                                                            #line 650 "CodeGeneratorXSLT.cpp.template"
                                                              print((variable("t1").size - 1) / 32);
                                                            #line 1019 "CodeGeneratorXSLT.cpp"
  append(L"\">\n");
  append(L"      <xsl:variable name=\"i0\" select=\". * ");
                                                            #line 652 "CodeGeneratorXSLT.cpp.template"
                                                              print(variable("transitionStateCount").integer());
                                                            #line 1024 "CodeGeneratorXSLT.cpp"
  append(L" + $state - 1\"/>\n");
                                                            #line 654 "CodeGeneratorXSLT.cpp.template"
                                                              compressedMapAccessor(6, "i", "<xsl:sequence select=\"p:token((), ", "$p:EXPECTED", &variable("t0bits").integer());
                                                            #line 1028 "CodeGeneratorXSLT.cpp"
  append(L", . * 32 + 1)\"/>\n");
  append(L"    </xsl:for-each>\n");
  append(L"  </xsl:if>\n");
  append(L"</xsl:function>\n");
                                                            #line 659 "CodeGeneratorXSLT.cpp.template"
                                                              if (variable("m2").size != 0)
                                                              {
                                                            #line 1036 "CodeGeneratorXSLT.cpp"
  append(L"\n");
  append(L"<!--");
  append(L"~");
  append(L"\n");
  append(L" ! Classify codepoint by doing a tail recursive binary search for a\n");
  append(L" ! matching codepoint range entry in MAP2, the codepoint to charclass\n");
  append(L" ! map for codepoints above the surrogate block.\n");
  append(L" !\n");
  append(L" ! @param $c the codepoint.\n");
  append(L" ! @param $lo the binary search lower bound map index.\n");
  append(L" ! @param $hi the binary search upper bound map index.\n");
  append(L" ! @return the character class.\n");
  append(L"-->\n");
  append(L"<xsl:function name=\"p:map2\" as=\"xs:integer\">\n");
  append(L"  <xsl:param name=\"c\" as=\"xs:integer\"/>\n");
  append(L"  <xsl:param name=\"lo\" as=\"xs:integer\"/>\n");
  append(L"  <xsl:param name=\"hi\" as=\"xs:integer\"/>\n");
  append(L"\n");
  append(L"  <xsl:variable name=\"m\" select=\"($hi + $lo) idiv 2\"/>\n");
  append(L"  <xsl:choose>\n");
  append(L"    <xsl:when test=\"$lo &gt; $hi\">\n");
  append(L"      <xsl:sequence select=\"0\"/>\n");
  append(L"    </xsl:when>\n");
  append(L"    <xsl:when test=\"$p:MAP2[$m] &gt; $c\">\n");
  append(L"      <xsl:sequence select=\"p:map2($c, $lo, $m - 1)\"/>\n");
  append(L"    </xsl:when>\n");
  append(L"    <xsl:when test=\"$p:MAP2[");
                                                            #line 685 "CodeGeneratorXSLT.cpp.template"
                                                                print(variable("m2").size / 3);
                                                            #line 1066 "CodeGeneratorXSLT.cpp"
  append(L" + $m] &lt; $c\">\n");
  append(L"      <xsl:sequence select=\"p:map2($c, $m + 1, $hi)\"/>\n");
  append(L"    </xsl:when>\n");
  append(L"    <xsl:otherwise>\n");
  append(L"      <xsl:sequence select=\"$p:MAP2[");
                                                            #line 690 "CodeGeneratorXSLT.cpp.template"
                                                                print(variable("m2").size / 3 * 2);
                                                            #line 1074 "CodeGeneratorXSLT.cpp"
  append(L" + $m]\"/>\n");
  append(L"    </xsl:otherwise>\n");
  append(L"  </xsl:choose>\n");
  append(L"</xsl:function>\n");
                                                            #line 695 "CodeGeneratorXSLT.cpp.template"
                                                              }
                                                              indent -= 1;
                                                            }

                                                            void CodeGeneratorXSLT::generateData()
                                                            {
                                                            }

// End
