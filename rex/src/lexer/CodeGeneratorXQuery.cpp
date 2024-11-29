// This file was generated on Sun Nov 24, 2024 16:09 (UTC+01) by REx v6.0 which is Copyright (c) 1979-2024 by Gunther Rademacher <grd@gmx.net>
// REx command line: CodeGeneratorXQuery.cpp.template
                                                            #line 1 "CodeGeneratorXQuery.cpp.template"
                                                            #include "../common/Memory.hpp"

                                                            #include "CodeGenerator.hpp"

                                                            void CodeGeneratorXQuery::compressedMap2dAccessor(const char *x,
                                                                                                              const char *y,
                                                                                                              int xCount,
                                                                                                              size_t indent,
                                                                                                              const char *index,
                                                                                                              const char *result,
                                                                                                              const char *map,
                                                                                                              const int *bits)
                                                            {
                                                              print(indent, " ");
                                                            #line 19 "CodeGeneratorXQuery.cpp"
  append(L"let ");
                                                            #line 15 "CodeGeneratorXQuery.cpp.template"
                                                              print(index);
                                                            #line 23 "CodeGeneratorXQuery.cpp"
  append(L"0 := ");
                                                            #line 16 "CodeGeneratorXQuery.cpp.template"
                                                              print(format.toString<char>(xCount));
                                                            #line 27 "CodeGeneratorXQuery.cpp"
  append(L" * ");
                                                            #line 17 "CodeGeneratorXQuery.cpp.template"
                                                              print(y);
                                                            #line 31 "CodeGeneratorXQuery.cpp"
  append(L" + ");
                                                            #line 18 "CodeGeneratorXQuery.cpp.template"
                                                              print(x);
                                                            #line 35 "CodeGeneratorXQuery.cpp"
  append(L"\n");
                                                            #line 20 "CodeGeneratorXQuery.cpp.template"
                                                              compressedMapAccessor(indent, index, result, map, bits);
                                                            }

                                                            void CodeGeneratorXQuery::compressedMapAccessor(size_t indent, const char *index, const char *result, const char *map, const int *bits)
                                                            {
                                                              size_t i = 0;
                                                              for (i = 0; bits[i]; ++i)
                                                              {
                                                                print(indent, " ");
                                                            #line 47 "CodeGeneratorXQuery.cpp"
  append(L"let ");
                                                            #line 29 "CodeGeneratorXQuery.cpp.template"
                                                                print(index);
                                                                print(i + 1);
                                                            #line 52 "CodeGeneratorXQuery.cpp"
  append(L" := ");
                                                            #line 31 "CodeGeneratorXQuery.cpp.template"
                                                                print(index);
                                                                print(i);
                                                            #line 57 "CodeGeneratorXQuery.cpp"
  append(L" idiv ");
                                                            #line 33 "CodeGeneratorXQuery.cpp.template"
                                                                print(Math::powerof(2, bits[i]));
                                                            #line 61 "CodeGeneratorXQuery.cpp"
  append(L"\n");
                                                            #line 35 "CodeGeneratorXQuery.cpp.template"
                                                              }
                                                              print(indent, " ");
                                                              print(result);
                                                              print(map);
                                                            #line 68 "CodeGeneratorXQuery.cpp"
  append(L"[");
                                                            #line 39 "CodeGeneratorXQuery.cpp.template"
                                                              for (i = 0; bits[i]; ++i)
                                                              {
                                                                print(index);
                                                                print(i);
                                                            #line 75 "CodeGeneratorXQuery.cpp"
  append(L" mod ");
                                                            #line 43 "CodeGeneratorXQuery.cpp.template"
                                                                print(Math::powerof(2, bits[i]));
                                                            #line 79 "CodeGeneratorXQuery.cpp"
  append(L" + ");
                                                            #line 44 "CodeGeneratorXQuery.cpp.template"
                                                                print(map);
                                                            #line 83 "CodeGeneratorXQuery.cpp"
  append(L"[");
                                                            #line 45 "CodeGeneratorXQuery.cpp.template"
                                                              }
                                                              print(index);
                                                              print(i);
                                                              for (i = 0; bits[i]; ++i)
                                                              {
                                                            #line 91 "CodeGeneratorXQuery.cpp"
  append(L" + 1]");
                                                            #line 50 "CodeGeneratorXQuery.cpp.template"
                                                              }
                                                            #line 95 "CodeGeneratorXQuery.cpp"
  append(L" + 1]");
                                                            #line 51 "CodeGeneratorXQuery.cpp.template"
                                                            }

                                                            void CodeGeneratorXQuery::generateStaticCode()
                                                            {
                                                              if (! variable("embedded").boolean())
                                                              {
                                                            #line 104 "CodeGeneratorXQuery.cpp"
  append(L"(:");
  append(L"~");
  append(L"\n");
  append(L" : The tokenizer that was generated for the ");
                                                            #line 58 "CodeGeneratorXQuery.cpp.template"
                                                                print(variable("classname").string());
                                                            #line 111 "CodeGeneratorXQuery.cpp"
  append(L" grammar.\n");
  append(L" :)\n");
  append(L"module namespace p=\"");
                                                            #line 61 "CodeGeneratorXQuery.cpp.template"
                                                                print(variable("classname").string());
                                                            #line 117 "CodeGeneratorXQuery.cpp"
  append(L"\";");
                                                            #line 62 "CodeGeneratorXQuery.cpp.template"
                                                              }
                                                              for (VarsInInsertionOrder::iterator a(varsInInsertionOrder.begin());
                                                                   a != varsInInsertionOrder.end(); ++a)
                                                                if (a->isArray() && a->size > 0 && a->hasType(CGVariable::INTEGER) && strlen(a->name) == 2)
                                                              {
                                                            #line 125 "CodeGeneratorXQuery.cpp"
  append(L"\n");
  append(L"\n");
  append(L"(:");
  append(L"~");
  append(L"\n");
  append(L" : ");
                                                            #line 70 "CodeGeneratorXQuery.cpp.template"
                                                                print(a->getDescription());
                                                            #line 134 "CodeGeneratorXQuery.cpp"
  append(L"\n");
  append(L" :)\n");
  append(L"declare variable $p:");
                                                            #line 73 "CodeGeneratorXQuery.cpp.template"
                                                                print(a->getLongName());
                                                            #line 140 "CodeGeneratorXQuery.cpp"
  append(L" as xs:integer+ :=\n");
  append(L"(\n");
  append(L" ");
                                                            #line 76 "CodeGeneratorXQuery.cpp.template"
                                                                for (size_t j = 0; j < a->size; ++j)
                                                                {
                                                                  if (j)
                                                                  {
                                                            #line 149 "CodeGeneratorXQuery.cpp"
  append(L",");
                                                            #line 80 "CodeGeneratorXQuery.cpp.template"
                                                                  }
                                                                  if (lineLength() + Format::width(a->integer(j)) + 2 > 120)
                                                                  {
                                                            #line 155 "CodeGeneratorXQuery.cpp"
  append(L"\n");
  append(L" ");
                                                            #line 84 "CodeGeneratorXQuery.cpp.template"
                                                                  }
                                                            #line 160 "CodeGeneratorXQuery.cpp"
  append(L" ");
                                                            #line 85 "CodeGeneratorXQuery.cpp.template"
                                                                  print(a->integer(j));
                                                                }
                                                            #line 165 "CodeGeneratorXQuery.cpp"
  append(L"\n");
  append(L");");
                                                            #line 88 "CodeGeneratorXQuery.cpp.template"
                                                              }
                                                              for (VarsInInsertionOrder::iterator a(varsInInsertionOrder.begin());
                                                                   a != varsInInsertionOrder.end(); ++a)
                                                                if (a->isArray() && a->hasType(CGVariable::STRING) && strlen(a->name) == 2)
                                                              {
                                                            #line 174 "CodeGeneratorXQuery.cpp"
  append(L"\n");
  append(L"\n");
  append(L"(:");
  append(L"~");
  append(L"\n");
  append(L" : ");
                                                            #line 96 "CodeGeneratorXQuery.cpp.template"
                                                                print(a->getDescription());
                                                            #line 183 "CodeGeneratorXQuery.cpp"
  append(L"\n");
  append(L" :)\n");
  append(L"declare variable $p:");
                                                            #line 99 "CodeGeneratorXQuery.cpp.template"
                                                                print(a->getLongName());
                                                            #line 189 "CodeGeneratorXQuery.cpp"
  append(L" as xs:string+ :=\n");
  append(L"(\n");
  append(L"  ");
                                                            #line 102 "CodeGeneratorXQuery.cpp.template"
                                                                for (size_t j = 0; j < a->size; ++j)
                                                                {
                                                                  if (j)
                                                                  {
                                                            #line 198 "CodeGeneratorXQuery.cpp"
  append(L",\n");
  append(L"  ");
                                                            #line 108 "CodeGeneratorXQuery.cpp.template"
                                                                  }
                                                            #line 203 "CodeGeneratorXQuery.cpp"
  append(L"\"");
                                                            #line 109 "CodeGeneratorXQuery.cpp.template"
                                                                  const char *s = a->string(j);
                                                                  const char *c = s;
                                                                  for (; *c; ++c)
                                                                  {
                                                                    if (*c == '"')
                                                                    {
                                                                      print(s, c - s);
                                                                      print("\"\"");
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
                                                            #line 224 "CodeGeneratorXQuery.cpp"
  append(L"\"");
                                                            #line 127 "CodeGeneratorXQuery.cpp.template"
                                                                }
                                                            #line 228 "CodeGeneratorXQuery.cpp"
  append(L"\n");
  append(L");");
                                                            #line 129 "CodeGeneratorXQuery.cpp.template"
                                                              }
                                                            #line 233 "CodeGeneratorXQuery.cpp"
  append(L"\n");
                                                            #line 131 "CodeGeneratorXQuery.cpp.template"
                                                              if (variable("trace").boolean())
                                                              {
                                                            #line 238 "CodeGeneratorXQuery.cpp"
  append(L"\n");
  append(L"(:");
  append(L"~");
  append(L"\n");
  append(L" : Pass a line to fn:trace, without generating a result. Actually,\n");
  append(L" : create an empty result, but make it somehow dependent on trace,\n");
  append(L" : so the optimizer does not eliminate the trace call.\n");
  append(L" :\n");
  append(L" : @param $line the line to be traced.\n");
  append(L" : @return the empty sequence.\n");
  append(L" :)\n");
  append(L"declare function p:trace($line as xs:string) as empty-sequence()\n");
  append(L"{\n");
  append(L"  if (trace($line, \"trace\")) then () else \"\"[.]\n");
  append(L"};\n");
  append(L"\n");
  append(L"(:");
  append(L"~");
  append(L"\n");
  append(L" : Add escaping to a string for being placed in serialized\n");
  append(L" : XML attribute or element content.\n");
  append(L" :\n");
  append(L" : @param $s the string to be escaped.\n");
  append(L" : @return the escaped string.\n");
  append(L" :)\n");
  append(L"declare function p:xml-escape($s as xs:string) as xs:string\n");
  append(L"{\n");
  append(L"  replace(\n");
  append(L"  replace(\n");
  append(L"  replace($s, \"&amp;\", \"&amp;amp;\"),\n");
  append(L"              \"<\", \"&amp;lt;\"),\n");
  append(L"              '\"', \"&amp;quot;\")\n");
  append(L"};\n");
                                                            #line 162 "CodeGeneratorXQuery.cpp.template"
                                                              }
                                                              if (   variable("embedded").boolean()
                                                                  && variable("tables").boolean())
                                                              {
                                                            #line 277 "CodeGeneratorXQuery.cpp"
  append(L"\n");
  append(L"(:");
  append(L"~");
  append(L"\n");
  append(L" : Predict the decision for a given decision point based on current\n");
  append(L" : lookahead.\n");
  append(L" :\n");
  append(L" : @param $input the input string.\n");
  append(L" : @param $state the parser state.\n");
  append(L" : @param $dpi the decision point index.");
                                                            #line 173 "CodeGeneratorXQuery.cpp.template"
                                                                if (variable("useGlr").boolean())
                                                                {
                                                            #line 291 "CodeGeneratorXQuery.cpp"
  append(L"\n");
  append(L" : @param $id the parsing thread id.");
                                                            #line 176 "CodeGeneratorXQuery.cpp.template"
                                                                }
                                                            #line 296 "CodeGeneratorXQuery.cpp"
  append(L"\n");
  append(L" : @return the updated parser state.\n");
  append(L" :)\n");
  append(L"declare function p:predict($input as xs:string,\n");
  append(L"                           $state as item()+,\n");
  append(L"                           $dpi as xs:integer");
                                                            #line 182 "CodeGeneratorXQuery.cpp.template"
                                                                if (variable("useGlr").boolean())
                                                                {
                                                            #line 306 "CodeGeneratorXQuery.cpp"
  append(L",\n");
  append(L"                           $id as xs:integer");
                                                            #line 185 "CodeGeneratorXQuery.cpp.template"
                                                                }
                                                            #line 311 "CodeGeneratorXQuery.cpp"
  append(L") as item()+\n");
  append(L"{");
                                                            #line 187 "CodeGeneratorXQuery.cpp.template"
                                                                if (variable("lrparser").boolean())
                                                                {
                                                            #line 317 "CodeGeneratorXQuery.cpp"
  append(L"\n");
  append(L"  let $state := p:lookahead1");
                                                            #line 190 "CodeGeneratorXQuery.cpp.template"
                                                                  if (variable("anyWhitespace").boolean())
                                                                  {
                                                            #line 323 "CodeGeneratorXQuery.cpp"
  append(L"W");
                                                            #line 192 "CodeGeneratorXQuery.cpp.template"
                                                                  }
                                                            #line 327 "CodeGeneratorXQuery.cpp"
  append(L"($p:TOKENSET[$dpi + 1], $input, $state");
                                                            #line 194 "CodeGeneratorXQuery.cpp.template"
                                                                if (variable("useGlr").boolean())
                                                                {
                                                            #line 332 "CodeGeneratorXQuery.cpp"
  append(L", $id");
                                                            #line 196 "CodeGeneratorXQuery.cpp.template"
                                                                }
                                                            #line 336 "CodeGeneratorXQuery.cpp"
  append(L")\n");
  append(L"  return");
                                                            #line 198 "CodeGeneratorXQuery.cpp.template"
                                                                  indent += 1;
                                                                }
                                                            #line 342 "CodeGeneratorXQuery.cpp"
  append(L"\n");
  append(L"  if ($state[$p:l1] lt 0) then\n");
  append(L"  (\n");
  append(L"    0,\n");
  append(L"    subsequence($state, $p:lk + 1");
                                                            #line 204 "CodeGeneratorXQuery.cpp.template"
                                                                if (variable("useGlr").boolean())
                                                                {
                                                            #line 351 "CodeGeneratorXQuery.cpp"
  append(L")");
                                                            #line 206 "CodeGeneratorXQuery.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 357 "CodeGeneratorXQuery.cpp"
  append(L", $p:error - $p:lk - 1),\n");
  append(L"    element error\n");
  append(L"    {\n");
  append(L"      attribute b {$state[$p:b1]},\n");
  append(L"      attribute e {$state[$p:e1]},\n");
  append(L"      attribute s {- $state[$p:l1]}\n");
  append(L"    },\n");
  append(L"    subsequence($state, $p:error + 1)");
                                                            #line 216 "CodeGeneratorXQuery.cpp.template"
                                                                }
                                                            #line 368 "CodeGeneratorXQuery.cpp"
  append(L"\n");
  append(L"  )\n");
  append(L"  else");
                                                            #line 219 "CodeGeneratorXQuery.cpp.template"
                                                                indent += 1;
                                                            #line 374 "CodeGeneratorXQuery.cpp"
  append(L"\n");
                                                            #line 221 "CodeGeneratorXQuery.cpp.template"
                                                                int k = variable("k").integer();
                                                                const char *action = "let $action := ";
                                                                compressedMap2dAccessor("$state[$p:l1]", "$dpi", variable("cicols").integer(),
                                                                                              2, "$j1", action, "$p:CASEID", &variable("cibits").integer());
                                                                bool loop = k > 1 && variable("lrparser").boolean();
                                                                for (int i = 2; i <= k; ++i)
                                                                {
                                                            #line 384 "CodeGeneratorXQuery.cpp"
  append(L"\n");
  append(L"  return\n");
  append(L"    if ($action mod 2 eq 0) then\n");
  append(L"      ($action idiv 2, subsequence($state, $p:lk + 1))\n");
  append(L"    else\n");
  append(L"      let $state := p:lookahead");
                                                            #line 233 "CodeGeneratorXQuery.cpp.template"
                                                                  print(format.toString<char>(i));
                                                                  if (variable("anyWhitespace").boolean())
                                                                  {
                                                            #line 395 "CodeGeneratorXQuery.cpp"
  append(L"W");
                                                            #line 236 "CodeGeneratorXQuery.cpp.template"
                                                                  }
                                                            #line 399 "CodeGeneratorXQuery.cpp"
  append(L"(");
                                                            #line 237 "CodeGeneratorXQuery.cpp.template"
                                                                  if (variable("unlimitedLookahead").boolean())
                                                                  {
                                                            #line 404 "CodeGeneratorXQuery.cpp"
  append(L"0, ");
                                                            #line 239 "CodeGeneratorXQuery.cpp.template"
                                                                  }
                                                            #line 408 "CodeGeneratorXQuery.cpp"
  append(L"$action idiv 2, $input, $state)\n");
  append(L"      return\n");
  append(L"        if ($state[$p:l");
                                                            #line 242 "CodeGeneratorXQuery.cpp.template"
                                                                  print(format.toString<char>(i));
                                                            #line 414 "CodeGeneratorXQuery.cpp"
  append(L"] lt 0) then\n");
  append(L"          (0, subsequence($state, $p:lk + 1))\n");
  append(L"        else");
                                                            #line 245 "CodeGeneratorXQuery.cpp.template"
                                                                  indent += 2;
                                                            #line 420 "CodeGeneratorXQuery.cpp"
  append(L"\n");
                                                            #line 247 "CodeGeneratorXQuery.cpp.template"
                                                                  CString li("$state[$p:l");
                                                                  li += format.toString<char>(i);
                                                                  li += "]";
                                                                  CString ii("$i");
                                                                  ii += format.toString<char>(i);
                                                                  compressedMap2dAccessor(i == 2 ? "$state[$p:l1]" : "$lk", li.c_str(), variable("lxcols").integer(),
                                                                                                6, ii.c_str(), "let $lk := ", "$p:LOOKAHEAD", &variable("lxbits").integer());
                                                            #line 430 "CodeGeneratorXQuery.cpp"
  append(L"\n");
  append(L"      return\n");
  append(L"        if ($lk eq 0) then");
                                                            #line 256 "CodeGeneratorXQuery.cpp.template"
                                                                  if (loop)
                                                                  {
                                                            #line 437 "CodeGeneratorXQuery.cpp"
  append(L"\n");
  append(L"          p:predict($input, $state, $dpi + 1)");
                                                            #line 259 "CodeGeneratorXQuery.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 444 "CodeGeneratorXQuery.cpp"
  append(L"\n");
  append(L"          (0, subsequence($state, $p:lk + 1))");
                                                            #line 263 "CodeGeneratorXQuery.cpp.template"
                                                                  }
                                                            #line 449 "CodeGeneratorXQuery.cpp"
  append(L"\n");
  append(L"        else");
                                                            #line 265 "CodeGeneratorXQuery.cpp.template"
                                                                  indent += 1;
                                                            #line 454 "CodeGeneratorXQuery.cpp"
  append(L"\n");
                                                            #line 267 "CodeGeneratorXQuery.cpp.template"
                                                                  CString ji("$j");
                                                                  ji += format.toString<char>(i);
                                                                  compressedMap2dAccessor("$lk", "$dpi", variable("cicols").integer(),
                                                                                                8, ji.c_str(), "let $action := ", "$p:CASEID", &variable("cibits").integer());
                                                                  indent += 3;
                                                                }
                                                                if (loop)
                                                                {
                                                            #line 465 "CodeGeneratorXQuery.cpp"
  append(L"\n");
  append(L"  return\n");
  append(L"    if ($action ne 0) then\n");
  append(L"      ($action idiv 2, subsequence($state, $p:lk + 1))\n");
  append(L"    else\n");
  append(L"      p:predict($input, $state, $dpi + 1)");
                                                            #line 280 "CodeGeneratorXQuery.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 476 "CodeGeneratorXQuery.cpp"
  append(L"\n");
  append(L"  return ($action idiv 2, subsequence($state, $p:lk + 1))");
                                                            #line 284 "CodeGeneratorXQuery.cpp.template"
                                                                }
                                                                indent = 0;
                                                            #line 482 "CodeGeneratorXQuery.cpp"
  append(L"\n");
  append(L"};\n");
                                                            #line 288 "CodeGeneratorXQuery.cpp.template"
                                                              }
                                                            #line 487 "CodeGeneratorXQuery.cpp"
  append(L"\n");
  append(L"(:");
  append(L"~");
  append(L"\n");
  append(L" : Match next token in input string, starting at given index, using\n");
  append(L" : the DFA entry state for the set of tokens that are expected in\n");
  append(L" : the current context.\n");
  append(L" :\n");
  append(L" : @param $input the input string.\n");
  append(L" : @param $begin the index where to start in input string.\n");
  append(L" : @param $token-set the expected token set id.");
                                                            #line 297 "CodeGeneratorXQuery.cpp.template"
                                                                if (variable("useGlr").boolean())
                                                                {
                                                            #line 502 "CodeGeneratorXQuery.cpp"
  append(L"\n");
  append(L" : @param $id the parsing thread id.");
                                                            #line 300 "CodeGeneratorXQuery.cpp.template"
                                                                }
                                                            #line 507 "CodeGeneratorXQuery.cpp"
  append(L"\n");
  append(L" : @return a sequence of three: the token code of the result token,\n");
  append(L" : with input string begin and end positions. If there is no valid\n");
  append(L" : token, return the negative id of the DFA state that failed, along\n");
  append(L" : with begin and end positions of the longest viable prefix.\n");
  append(L" :)\n");
  append(L"declare function p:match($input as xs:string,\n");
  append(L"                         $begin as xs:integer,\n");
  append(L"                         $token-set as xs:integer");
                                                            #line 309 "CodeGeneratorXQuery.cpp.template"
                                                                if (variable("useGlr").boolean())
                                                                {
                                                            #line 520 "CodeGeneratorXQuery.cpp"
  append(L",\n");
  append(L"                         $id as xs:integer");
                                                            #line 312 "CodeGeneratorXQuery.cpp.template"
                                                                }
                                                            #line 525 "CodeGeneratorXQuery.cpp"
  append(L") as xs:integer+\n");
  append(L"{");
                                                            #line 314 "CodeGeneratorXQuery.cpp.template"
                                                              if (variable("trace").boolean())
                                                              {
                                                            #line 531 "CodeGeneratorXQuery.cpp"
  append(L"\n");
  append(L"  p:trace(concat(\"  <tokenize ");
                                                            #line 317 "CodeGeneratorXQuery.cpp.template"
                                                                if (variable("useGlr").boolean())
                                                                {
                                                            #line 537 "CodeGeneratorXQuery.cpp"
  append(L"thread=\"\"\", $id, \"\"\" ");
                                                            #line 319 "CodeGeneratorXQuery.cpp.template"
                                                                }
                                                            #line 541 "CodeGeneratorXQuery.cpp"
  append(L"tokenset=\"\"\", $token-set, \"\"\">\")),");
                                                            #line 321 "CodeGeneratorXQuery.cpp.template"
                                                              }
                                                            #line 545 "CodeGeneratorXQuery.cpp"
  append(L"\n");
  append(L"  let $result := $p:INITIAL[1 + $token-set]\n");
  append(L"  return p:transition($input,\n");
  append(L"                      $begin,\n");
  append(L"                      $begin,\n");
  append(L"                      $begin,\n");
  append(L"                      $result,\n");
  append(L"                      $result mod ");
                                                            #line 329 "CodeGeneratorXQuery.cpp.template"
                                                          print(Math::powerof(2, variable("stateCodeBits").integer()));
                                                            #line 556 "CodeGeneratorXQuery.cpp"
  append(L",\n");
  append(L"                      0)\n");
  append(L"};\n");
  append(L"\n");
  append(L"(:");
  append(L"~");
  append(L"\n");
  append(L" : The DFA state transition function. If we are in a valid DFA state, save\n");
  append(L" : it's result annotation, consume one input codepoint, calculate the next\n");
  append(L" : state, and use tail recursion to do the same again. Otherwise, return\n");
  append(L" : any valid result or a negative DFA state id in case of an error.\n");
  append(L" :\n");
  append(L" : @param $input the input string.\n");
  append(L" : @param $begin the begin index of the current token in the input string.\n");
  append(L" : @param $current the index of the current position in the input string.\n");
  append(L" : @param $end the end index of the result in the input string.\n");
  append(L" : @param $result the result code.\n");
  append(L" : @param $current-state the current DFA state.\n");
  append(L" : @param $previous-state the  previous DFA state.\n");
  append(L" : @return a sequence of three: the token code of the result token,\n");
  append(L" : with input string begin and end positions. If there is no valid\n");
  append(L" : token, return the negative id of the DFA state that failed, along\n");
  append(L" : with begin and end positions of the longest viable prefix.\n");
  append(L" :)\n");
  append(L"declare function p:transition($input as xs:string,\n");
  append(L"                              $begin as xs:integer,\n");
  append(L"                              $current as xs:integer,\n");
  append(L"                              $end as xs:integer,\n");
  append(L"                              $result as xs:integer,\n");
  append(L"                              $current-state as xs:integer,\n");
  append(L"                              $previous-state as xs:integer)\n");
  append(L"{\n");
  append(L"  if ($current-state eq 0) then\n");
  append(L"    let $result := $result idiv ");
                                                            #line 361 "CodeGeneratorXQuery.cpp.template"
                                                              print(Math::powerof(2, variable("stateCodeBits").integer()));
                                                              if (0 == variable("maxcontextlength").integer())
                                                              {
                                                                if (variable("hasfixedtokenlength").boolean())
                                                                {
                                                            #line 597 "CodeGeneratorXQuery.cpp"
  append(L"\n");
  append(L"    let $end := if ($result idiv ");
                                                            #line 367 "CodeGeneratorXQuery.cpp.template"
                                                                  print(Math::powerof(2, variable("tokencodeBits").integer()));
                                                            #line 602 "CodeGeneratorXQuery.cpp"
  append(L" ne 0) then $begin else $end");
                                                            #line 369 "CodeGeneratorXQuery.cpp.template"
                                                                }
                                                              }
                                                              else if (! variable("hasfixedtokenlength").boolean())
                                                              {
                                                            #line 609 "CodeGeneratorXQuery.cpp"
  append(L"\n");
  append(L"    let $end := $end - $result idiv ");
                                                            #line 374 "CodeGeneratorXQuery.cpp.template"
                                                                print(Math::powerof(2, variable("tokencodeBits").integer()));
                                                              }
                                                              else
                                                              {
                                                            #line 617 "CodeGeneratorXQuery.cpp"
  append(L"\n");
  append(L"    let $end :=\n");
  append(L"      if ($result idiv ");
                                                            #line 380 "CodeGeneratorXQuery.cpp.template"
                                                                print(Math::powerof(2, variable("tokencodeBits").integer()));
                                                            #line 623 "CodeGeneratorXQuery.cpp"
  append(L" mod 2 eq 1) then\n");
  append(L"        $begin + $result idiv ");
                                                            #line 382 "CodeGeneratorXQuery.cpp.template"
                                                                print(Math::powerof(2, 1 + variable("tokencodeBits").integer()));
                                                            #line 628 "CodeGeneratorXQuery.cpp"
  append(L"\n");
  append(L"      else\n");
  append(L"        $end - $result idiv ");
                                                            #line 385 "CodeGeneratorXQuery.cpp.template"
                                                                print(Math::powerof(2, 1 + variable("tokencodeBits").integer()));
                                                              }
                                                            #line 635 "CodeGeneratorXQuery.cpp"
  append(L"\n");
  append(L"    let $end := if ($end gt string-length($input)) then string-length($input) + 1 else $end\n");
  append(L"    return\n");
  append(L"      if ($result ne 0) then\n");
  append(L"      (");
                                                            #line 391 "CodeGeneratorXQuery.cpp.template"
                                                              if (variable("trace").boolean())
                                                              {
                                                            #line 644 "CodeGeneratorXQuery.cpp"
  append(L"\n");
  append(L"        p:trace(concat(\"    <done result=\"\"\", p:xml-escape($p:TOKEN[$result");
                                                            #line 395 "CodeGeneratorXQuery.cpp.template"
                                                                if (   0 != variable("maxcontextlength").integer()
                                                                    || variable("hasfixedtokenlength").boolean())
                                                                {
                                                            #line 651 "CodeGeneratorXQuery.cpp"
  append(L" mod ");
                                                            #line 398 "CodeGeneratorXQuery.cpp.template"
                                                                  print(Math::powerof(2, variable("tokencodeBits").integer()));
                                                                }
                                                            #line 656 "CodeGeneratorXQuery.cpp"
  append(L"]), \"\"\" begin=\"\"\", $begin, \"\"\" end=\"\"\", $end, \"\"\"/>\")),\n");
  append(L"        p:trace(\"  </tokenize>\"),");
                                                            #line 402 "CodeGeneratorXQuery.cpp.template"
                                                              }
                                                              if (0 == variable("maxcontextlength").integer() && ! variable("hasfixedtokenlength").boolean())
                                                              {
                                                            #line 663 "CodeGeneratorXQuery.cpp"
  append(L"\n");
  append(L"        $result - 1,");
                                                            #line 406 "CodeGeneratorXQuery.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 670 "CodeGeneratorXQuery.cpp"
  append(L"\n");
  append(L"        $result mod ");
                                                            #line 410 "CodeGeneratorXQuery.cpp.template"
                                                                print(Math::powerof(2, variable("tokencodeBits").integer()));
                                                            #line 675 "CodeGeneratorXQuery.cpp"
  append(L" - 1,");
                                                            #line 411 "CodeGeneratorXQuery.cpp.template"
                                                              }
                                                            #line 679 "CodeGeneratorXQuery.cpp"
  append(L"\n");
  append(L"        $begin,\n");
  append(L"        $end\n");
  append(L"      )\n");
  append(L"      else\n");
  append(L"      (");
                                                            #line 417 "CodeGeneratorXQuery.cpp.template"
                                                              if (variable("trace").boolean())
                                                              {
                                                            #line 689 "CodeGeneratorXQuery.cpp"
  append(L"\n");
  append(L"        p:trace(concat(\"    <fail begin=\"\"\", $begin, \"\"\" end=\"\"\", $current - 1, \"\"\" state=\"\"\", $previous-state, \"\"\"/>\")),\n");
  append(L"        p:trace(\"  </tokenize>\"),");
                                                            #line 421 "CodeGeneratorXQuery.cpp.template"
                                                              }
                                                            #line 695 "CodeGeneratorXQuery.cpp"
  append(L"\n");
  append(L"        - $previous-state,\n");
  append(L"        $begin,\n");
  append(L"        $current - 1\n");
  append(L"      )");
  append(L"\n");
  append(L"  else\n");
  append(L"    let $c0 := (string-to-codepoints(substring($input, $current, 1)), 0)[1]\n");
  append(L"    let $c1 :=\n");
  append(L"      if ($c0 < ");
                                                            #line 431 "CodeGeneratorXQuery.cpp.template"
                                                              print(variable("simplifiedCodeMap").integer());
                                                            #line 708 "CodeGeneratorXQuery.cpp"
  append(L") then\n");
  append(L"        $p:MAP0[1 + $c0]\n");
  append(L"      else if ($c0 < ");
                                                            #line 434 "CodeGeneratorXQuery.cpp.template"
                                                              print(variable("uncompressedMapSize").integer());
                                                            #line 714 "CodeGeneratorXQuery.cpp"
  append(L") then");
                                                            #line 435 "CodeGeneratorXQuery.cpp.template"
                                                              const int *m1bits = &variable("m1bits").integer();
                                                              for (size_t i = 0; m1bits[i]; ++i)
                                                              {
                                                            #line 720 "CodeGeneratorXQuery.cpp"
  append(L"\n");
  append(L"        let $c");
                                                            #line 439 "CodeGeneratorXQuery.cpp.template"
                                                                print(i + 1);
                                                            #line 725 "CodeGeneratorXQuery.cpp"
  append(L" := $c");
                                                            #line 440 "CodeGeneratorXQuery.cpp.template"
                                                                print(i);
                                                            #line 729 "CodeGeneratorXQuery.cpp"
  append(L" idiv ");
                                                            #line 441 "CodeGeneratorXQuery.cpp.template"
                                                                print(Math::powerof(2, m1bits[i]));
                                                              }
                                                            #line 734 "CodeGeneratorXQuery.cpp"
  append(L"\n");
  append(L"        return $p:MAP1[1 + $c0");
                                                            #line 444 "CodeGeneratorXQuery.cpp.template"
                                                         for (size_t i = 0; m1bits[i]; ++i)
                                                              {
                                                            #line 740 "CodeGeneratorXQuery.cpp"
  append(L" mod ");
                                                            #line 446 "CodeGeneratorXQuery.cpp.template"
                                                                print(Math::powerof(2, m1bits[i]));
                                                            #line 744 "CodeGeneratorXQuery.cpp"
  append(L" + $p:MAP1[1 + $c");
                                                            #line 447 "CodeGeneratorXQuery.cpp.template"
                                                           print(i + 1);
                                                              }
                                                              for (size_t i = 0; m1bits[i]; ++i)
                                                              {
                                                            #line 751 "CodeGeneratorXQuery.cpp"
  append(L"]");
                                                            #line 452 "CodeGeneratorXQuery.cpp.template"
                                                              }
                                                            #line 755 "CodeGeneratorXQuery.cpp"
  append(L"]\n");
  append(L"      else");
                                                            #line 454 "CodeGeneratorXQuery.cpp.template"
                                                              if (variable("m2").size == 0)
                                                              {
                                                            #line 761 "CodeGeneratorXQuery.cpp"
  append(L"\n");
  append(L"        0");
                                                            #line 457 "CodeGeneratorXQuery.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 768 "CodeGeneratorXQuery.cpp"
  append(L"\n");
  append(L"        p:map2($c0, 1, ");
                                                            #line 461 "CodeGeneratorXQuery.cpp.template"
                                                                print(variable("m2").size / 3);
                                                            #line 773 "CodeGeneratorXQuery.cpp"
  append(L")");
                                                            #line 462 "CodeGeneratorXQuery.cpp.template"
                                                              }
                                                            #line 777 "CodeGeneratorXQuery.cpp"
  append(L"\n");
  append(L"    let $current := $current + 1\n");
                                                            #line 465 "CodeGeneratorXQuery.cpp.template"
                                                              const int *a1bits = &variable("a1bits").integer();
                                                              compressedMap2dAccessor("$current-state - 1", "$c1", variable("a1cols").integer(),
                                                                                            4, "$i", "let $next-state := ", "$p:TRANSITION", a1bits);
                                                            #line 784 "CodeGeneratorXQuery.cpp"
  append(L"\n");
  append(L"    return");
                                                            #line 469 "CodeGeneratorXQuery.cpp.template"
                                                              if (variable("trace").boolean())
                                                              {
                                                            #line 790 "CodeGeneratorXQuery.cpp"
  append(L"\n");
  append(L"    (\n");
  append(L"      p:trace\n");
  append(L"      (\n");
  append(L"        string-join\n");
  append(L"        (\n");
  append(L"          (\n");
  append(L"            \"    <next state=\"\"\", string($current-state), \"\"\"\",\n");
  append(L"            \" offset=\"\"\", string($current - 1), \"\"\"\",\n");
  append(L"            if ($c0 lt 32 or $c0 gt 126) then\n");
  append(L"              ()\n");
  append(L"            else\n");
  append(L"              (\" char=\"\"\", p:xml-escape(substring($input, $current - 1, 1)), \"\"\"\"),\n");
  append(L"            \" codepoint=\"\"\", string($c0), \"\"\"\",\n");
  append(L"            \" class=\"\"\", string($c1), \"\"\"\",\n");
  append(L"            if ($next-state lt ");
                                                            #line 486 "CodeGeneratorXQuery.cpp.template"
                                                                print(Math::powerof(2, variable("stateCodeBits").integer()));
                                                            #line 809 "CodeGeneratorXQuery.cpp"
  append(L") then\n");
  append(L"              ()\n");
  append(L"            else\n");
  append(L"            (\n");
  append(L"              \" result=\"\"\",\n");
  append(L"              p:xml-escape($p:TOKEN[$next-state idiv ");
                                                            #line 492 "CodeGeneratorXQuery.cpp.template"
                                                                print(Math::powerof(2, variable("stateCodeBits").integer()));
                                                            #line 818 "CodeGeneratorXQuery.cpp"
  append(L" mod ");
                                                            #line 493 "CodeGeneratorXQuery.cpp.template"
                                                                print(Math::powerof(2, variable("tokencodeBits").integer()));
                                                            #line 822 "CodeGeneratorXQuery.cpp"
  append(L"]),\n");
  append(L"              if ($next-state lt ");
                                                            #line 495 "CodeGeneratorXQuery.cpp.template"
                                                                int contextOffset = variable("stateCodeBits").integer()
                                                                                  + variable("tokencodeBits").integer();
                                                                int sizeOffset = contextOffset
                                                                               + (variable("hasfixedtokenlength").boolean() ? 1 : 0);
                                                                print(Math::powerof(2, sizeOffset));
                                                            #line 831 "CodeGeneratorXQuery.cpp"
  append(L") then\n");
  append(L"                ()\n");
  append(L"              else\n");
  append(L"                (\"\"\" trailing-context-size=\"\"\", string($next-state idiv ");
                                                            #line 504 "CodeGeneratorXQuery.cpp.template"
                                                                print(Math::powerof(2, sizeOffset));
                                                            #line 838 "CodeGeneratorXQuery.cpp"
  append(L")),\n");
  append(L"              \"\"\"\"\n");
  append(L"            ),\n");
  append(L"            \"/>\"\n");
  append(L"          ),\n");
  append(L"          \"\"\n");
  append(L"        )\n");
  append(L"      ),");
                                                            #line 512 "CodeGeneratorXQuery.cpp.template"
                                                              }
                                                            #line 849 "CodeGeneratorXQuery.cpp"
  append(L"\n");
  append(L"      if ($next-state > ");
                                                            #line 514 "CodeGeneratorXQuery.cpp.template"
                                                                   print(Math::powerof(2, variable("stateCodeBits").integer()) - 1);
                                                            #line 854 "CodeGeneratorXQuery.cpp"
  append(L") then\n");
  append(L"        p:transition($input, $begin, $current, $current, $next-state, $next-state mod ");
                                                            #line 517 "CodeGeneratorXQuery.cpp.template"
                                                              print(Math::powerof(2, variable("stateCodeBits").integer()));
                                                            #line 859 "CodeGeneratorXQuery.cpp"
  append(L", $current-state)\n");
  append(L"      else\n");
  append(L"        p:transition($input, $begin, $current, $end, $result, $next-state, $current-state)");
                                                            #line 521 "CodeGeneratorXQuery.cpp.template"
                                                              if (variable("trace").boolean())
                                                              {
                                                            #line 866 "CodeGeneratorXQuery.cpp"
  append(L"\n");
  append(L"    )");
                                                            #line 524 "CodeGeneratorXQuery.cpp.template"
                                                              }
                                                            #line 871 "CodeGeneratorXQuery.cpp"
  append(L"\n");
  append(L"};\n");
  append(L"\n");
  append(L"(:");
  append(L"~");
  append(L"\n");
  append(L" : Recursively translate one 32-bit chunk of an expected token bitset\n");
  append(L" : to the corresponding sequence of token strings.\n");
  append(L" :\n");
  append(L" : @param $result the result of previous recursion levels.\n");
  append(L" : @param $chunk the 32-bit chunk of the expected token bitset.\n");
  append(L" : @param $base-token-code the token code of bit 0 in the current chunk.\n");
  append(L" : @return the set of token strings.\n");
  append(L" :)\n");
  append(L"declare function p:token($result as xs:string*,\n");
  append(L"                         $chunk as xs:integer,\n");
  append(L"                         $base-token-code as xs:integer)\n");
  append(L"{\n");
  append(L"  if ($chunk = 0) then\n");
  append(L"    $result\n");
  append(L"  else\n");
  append(L"    p:token\n");
  append(L"    (\n");
  append(L"      ($result, if ($chunk mod 2 != 0) then $p:TOKEN[$base-token-code] else ()),\n");
  append(L"      if ($chunk < 0) then $chunk idiv 2 + 2147483648 else $chunk idiv 2,\n");
  append(L"      $base-token-code + 1\n");
  append(L"    )\n");
  append(L"};\n");
                                                            #line 551 "CodeGeneratorXQuery.cpp.template"
                                                              if (defined("gtbits"))
                                                              {
                                                            #line 903 "CodeGeneratorXQuery.cpp"
  append(L"\n");
  append(L"(:");
  append(L"~");
  append(L"\n");
  append(L" : Get GOTO table entry for given nonterminal and parser state.\n");
  append(L" :\n");
  append(L" : @param $nonterminal the nonterminal.\n");
  append(L" : @param $state the LR parser state.\n");
  append(L" : @return the GOTO table entry.\n");
  append(L" :)\n");
  append(L"declare function p:goto($nonterminal as xs:integer, $state as xs:integer) as xs:integer\n");
  append(L"{\n");
                                                            #line 563 "CodeGeneratorXQuery.cpp.template"
                                                                compressedMap2dAccessor("$nonterminal",
                                                                                              "$state",
                                                                                              variable("gtcols").integer(),
                                                                                              2,
                                                                                              "$i",
                                                                                              "return ",
                                                                                              "$p:GOTO",
                                                                                              &variable("gtbits").integer());
                                                            #line 925 "CodeGeneratorXQuery.cpp"
  append(L"\n");
  append(L"};\n");
                                                            #line 573 "CodeGeneratorXQuery.cpp.template"
                                                              }
                                                            #line 930 "CodeGeneratorXQuery.cpp"
  append(L"\n");
  append(L"(:");
  append(L"~");
  append(L"\n");
  append(L" : Calculate expected token set for a given DFA state as a sequence\n");
  append(L" : of strings.\n");
  append(L" :\n");
  append(L" : @param $state the DFA state.\n");
  append(L" : @return the set of token strings.\n");
  append(L" :)\n");
  append(L"declare function p:expected-token-set($state as xs:integer) as xs:string*\n");
  append(L"{\n");
  append(L"  if ($state > 0) then\n");
  append(L"    for $t in 0 to ");
                                                            #line 585 "CodeGeneratorXQuery.cpp.template"
                                                              print((variable("t1").size - 1) / 32);
                                                            #line 947 "CodeGeneratorXQuery.cpp"
  append(L"\n");
  append(L"    let $i0 := $t * ");
                                                            #line 587 "CodeGeneratorXQuery.cpp.template"
                                                              print(variable("transitionStateCount").integer());
                                                            #line 952 "CodeGeneratorXQuery.cpp"
  append(L" + $state - 1\n");
                                                            #line 589 "CodeGeneratorXQuery.cpp.template"
                                                              compressedMapAccessor(4, "$i", "return p:token((), ", "$p:EXPECTED", &variable("t0bits").integer());
                                                            #line 956 "CodeGeneratorXQuery.cpp"
  append(L", $t * 32 + 1)\n");
  append(L"  else\n");
  append(L"    ()\n");
  append(L"};\n");
                                                            #line 594 "CodeGeneratorXQuery.cpp.template"
                                                              if (variable("m2").size != 0)
                                                              {
                                                            #line 964 "CodeGeneratorXQuery.cpp"
  append(L"\n");
  append(L"(:");
  append(L"~");
  append(L"\n");
  append(L" : Classify codepoint by doing a tail recursive binary search for a\n");
  append(L" : matching codepoint range entry in MAP2, the codepoint to charclass\n");
  append(L" : map for codepoints above the surrogate block.\n");
  append(L" :\n");
  append(L" : @param $c the codepoint.\n");
  append(L" : @param $lo the binary search lower bound map index.\n");
  append(L" : @param $hi the binary search upper bound map index.\n");
  append(L" : @return the character class.\n");
  append(L" :)\n");
  append(L"declare function p:map2($c as xs:integer, $lo as xs:integer, $hi as xs:integer) as xs:integer\n");
  append(L"{\n");
  append(L"  if ($lo > $hi) then\n");
  append(L"    0\n");
  append(L"  else\n");
  append(L"    let $m := ($hi + $lo) idiv 2\n");
  append(L"    return\n");
  append(L"      if ($p:MAP2[$m] > $c) then\n");
  append(L"        p:map2($c, $lo, $m - 1)\n");
  append(L"      else if ($p:MAP2[");
                                                            #line 616 "CodeGeneratorXQuery.cpp.template"
                                                                print(variable("m2").size / 3);
                                                            #line 990 "CodeGeneratorXQuery.cpp"
  append(L" + $m] < $c) then\n");
  append(L"        p:map2($c, $m + 1, $hi)\n");
  append(L"      else\n");
  append(L"        $p:MAP2[");
                                                            #line 620 "CodeGeneratorXQuery.cpp.template"
                                                                print(variable("m2").size / 3 * 2);
                                                            #line 997 "CodeGeneratorXQuery.cpp"
  append(L" + $m]\n");
  append(L"};\n");
                                                            #line 623 "CodeGeneratorXQuery.cpp.template"
                                                              }
                                                            }

                                                            void CodeGeneratorXQuery::generateData()
                                                            {
                                                            }

// End
