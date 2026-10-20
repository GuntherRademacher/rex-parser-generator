// This file was generated on Tue Oct 20, 2026 19:55 (UTC+02) by REx v6.3-SNAPSHOT which is Copyright (c) 1979-2026 by Gunther Rademacher <grd@gmx.net>
// REx command line: CodeGeneratorScala.cpp.template
                                                            #line 1 "CodeGeneratorScala.cpp.template"
                                                            // generate CodeGeneratorScala.cpp using this command:
                                                            //
                                                            //   REx CodeGeneratorScala.cpp.template

                                                            #include "../common/Memory.hpp"
                                                            #include "../common/WString.hpp"

                                                            #include "CodeGenerator.hpp"

                                                            void CodeGeneratorScala::generateInstanceCode()
                                                            {
                                                              isScala = true;
                                                              if (! variable("append").boolean() && ! variable("embedded").boolean())
                                                              {
                                                                if (*variable("package").string())
                                                                {
                                                            #line 21 "CodeGeneratorScala.cpp"
  append(L"package ");
                                                            #line 17 "CodeGeneratorScala.cpp.template"
                                                                  print(variable("package").string());
                                                            #line 25 "CodeGeneratorScala.cpp"
  append(L";\n");
  append(L"\n");
                                                            #line 20 "CodeGeneratorScala.cpp.template"
                                                                }
                                                            #line 30 "CodeGeneratorScala.cpp"
  append(L"public class ");
                                                            #line 21 "CodeGeneratorScala.cpp.template"
                                                                print(variable("classname").string());
                                                            #line 34 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"{\n");
                                                            #line 24 "CodeGeneratorScala.cpp.template"
                                                              }
                                                              if (! variable("embedded").boolean())
                                                              {
                                                            #line 41 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"  public void init(String string)\n");
  append(L"  {\n");
  append(L"    input = string;\n");
  append(L"    size = string.length();\n");
  append(L"    end = 0;\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  public int getOffset() {return begin;}\n");
  append(L"  public int getSize()   {return end - begin;}\n");
  append(L"  public int getState()  {return state;}\n");
  append(L"\n");
  append(L"  public int match(int tokenSetId, String string)\n");
  append(L"  {\n");
  append(L"    init(string);\n");
  append(L"    return match(tokenSetId);\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  public");
                                                            #line 45 "CodeGeneratorScala.cpp.template"
                                                              }
                                                              else
                                                              {
                                                                if (variable("tables").boolean())
                                                                {
                                                            #line 67 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"  private def predict(dpi: Int): Int =");
                                                            #line 51 "CodeGeneratorScala.cpp.template"
                                                                  predict();
                                                                  /*
                                                            #line 73 "CodeGeneratorScala.cpp"
  append(L" {\n");
  append(L"    if (l1 < 0) {\n");
  append(L"      lk = l1\n");
  append(L"    }\n");
  append(L"    else {\n");
                                                            #line 58 "CodeGeneratorScala.cpp.template"
                                                                  indent += 1;
                                                                  int k = variable("k").integer();
                                                                  CString caseId(variable("classname").string());
                                                                  caseId += ".CASEID";
                                                                  compressedMap2dAccessor("l1", "dpi", variable("cicols").integer(),
                                                                                             4, "j1", "var action = ", caseId.c_str(), &variable("cibits").integer());
                                                                  for (int i = 2; i <= k; ++i)
                                                                  {
                                                            #line 88 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"    if ((action & 1) == 0) {\n");
  append(L"      lk = action >> 1\n");
  append(L"    }\n");
  append(L"    else {\n");
  append(L"      if (l");
                                                            #line 71 "CodeGeneratorScala.cpp.template"
                                                                    print(format.toString<char>(i));
                                                            #line 97 "CodeGeneratorScala.cpp"
  append(L" == 0) {\n");
  append(L"        l");
                                                            #line 73 "CodeGeneratorScala.cpp.template"
                                                                    print(format.toString<char>(i));
                                                            #line 102 "CodeGeneratorScala.cpp"
  append(L" = match");
                                                            #line 74 "CodeGeneratorScala.cpp.template"
                                                                    if (variable("anyWhitespace").boolean())
                                                                    {
                                                            #line 107 "CodeGeneratorScala.cpp"
  append(L"W");
                                                            #line 76 "CodeGeneratorScala.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 113 "CodeGeneratorScala.cpp"
  append(L"er");
                                                            #line 79 "CodeGeneratorScala.cpp.template"
                                                                    }
                                                            #line 117 "CodeGeneratorScala.cpp"
  append(L"(action >> 1)\n");
  append(L"        b");
                                                            #line 81 "CodeGeneratorScala.cpp.template"
                                                                    print(format.toString<char>(i));
                                                            #line 122 "CodeGeneratorScala.cpp"
  append(L" = begin\n");
  append(L"        e");
                                                            #line 83 "CodeGeneratorScala.cpp.template"
                                                                    print(format.toString<char>(i));
                                                            #line 127 "CodeGeneratorScala.cpp"
  append(L" = end\n");
  append(L"      }\n");
  append(L"      if (l");
                                                            #line 86 "CodeGeneratorScala.cpp.template"
                                                                    print(format.toString<char>(i));
                                                            #line 133 "CodeGeneratorScala.cpp"
  append(L" < 0) {\n");
  append(L"        lk = 0\n");
  append(L"      }\n");
  append(L"      else {");
                                                            #line 90 "CodeGeneratorScala.cpp.template"
                                                                    indent += 1;
                                                            #line 140 "CodeGeneratorScala.cpp"
  append(L"\n");
                                                            #line 92 "CodeGeneratorScala.cpp.template"
                                                                    CString li("l");
                                                                    li += format.toString<char>(i);
                                                                    CString ii("i");
                                                                    ii += format.toString<char>(i);
                                                                    CString lookahead(variable("classname").string());
                                                                    lookahead += ".LOOKAHEAD";
                                                                    compressedMap2dAccessor(i == 2 ? "l1" : "lk", li.c_str(), variable("lxcols").integer(),
                                                                                               6, ii.c_str(), "lk = ", lookahead.c_str(), &variable("lxbits").integer());
                                                                    indent -= 1;
                                                            #line 152 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"      }\n");
  append(L"      if (lk != 0) {\n");
                                                            #line 104 "CodeGeneratorScala.cpp.template"
                                                                    CString ji("j");
                                                                    ji += format.toString<char>(i);
                                                                    compressedMap2dAccessor("lk", "dpi", variable("cicols").integer(),
                                                                                               8, ji.c_str(), "action = ", caseId.c_str(), &variable("cibits").integer());
                                                                    indent += 2;
                                                                  }
                                                            #line 163 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"    lk = action >> 1");
                                                            #line 111 "CodeGeneratorScala.cpp.template"
                                                                  for (int i = k; i >= 2; --i)
                                                                  {
                                                                    indent = 2 * i - 4;
                                                            #line 170 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"      }\n");
  append(L"    }");
                                                            #line 116 "CodeGeneratorScala.cpp.template"
                                                                  }
                                                                  indent = 0;
                                                            #line 177 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"    }\n");
  append(L"    lk\n");
  append(L"  }\n");
                                                            #line 122 "CodeGeneratorScala.cpp.template"
                                                                  */
                                                                }
                                                            #line 185 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"  private");
                                                            #line 126 "CodeGeneratorScala.cpp.template"
                                                              }
                                                            #line 190 "CodeGeneratorScala.cpp"
  append(L" def matcher(tokenSetId: Int) = {");
                                                            #line 127 "CodeGeneratorScala.cpp.template"
                                                              if (variable("nolexer").boolean())
                                                              {
                                                            #line 195 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"    token.begin = end;\n");
  append(L"    lexer.match(tokenSetId, token);\n");
  append(L"    begin = token.begin;\n");
  append(L"    end = token.end;\n");
  append(L"    return token.code >= 0\n");
  append(L"         ? token.code\n");
  append(L"         : error(begin, end, - tokenSetId, -1, -1);\n");
  append(L"  }\n");
                                                            #line 138 "CodeGeneratorScala.cpp.template"
                                                              }
                                                              else
                                                              {
                                                                if (variable("trace").boolean())
                                                                {
                                                            #line 211 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 144 "CodeGeneratorScala.cpp.template"
                                                                  if (variable("useGlr").boolean())
                                                                  {
                                                            #line 217 "CodeGeneratorScala.cpp"
  append(L"parser.");
                                                            #line 146 "CodeGeneratorScala.cpp.template"
                                                                  }
                                                            #line 221 "CodeGeneratorScala.cpp"
  append(L"writeTrace(\"  <tokenize ");
                                                            #line 147 "CodeGeneratorScala.cpp.template"
                                                                  if (variable("useGlr").boolean())
                                                                  {
                                                            #line 226 "CodeGeneratorScala.cpp"
  append(L"thread=\\\"\" + id + \"\\\" ");
                                                            #line 149 "CodeGeneratorScala.cpp.template"
                                                                  }
                                                            #line 230 "CodeGeneratorScala.cpp"
  append(L"tokenset=\\\"\" + tokenSetId + \"\\\">\\n\")\n");
                                                            #line 151 "CodeGeneratorScala.cpp.template"
                                                                }
                                                                int lookahead = variable("maxcontextlength").integer();
                                                                bool hasFixedTokenLength = variable("hasfixedtokenlength").boolean();
                                                                if (lookahead)
                                                                {
                                                            #line 238 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"    var nonbmp = false");
                                                            #line 157 "CodeGeneratorScala.cpp.template"
                                                                }
                                                            #line 243 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"    begin = end\n");
  append(L"    var current = end\n");
  append(L"    var result = ");
                                                            #line 161 "CodeGeneratorScala.cpp.template"
                                                                print(variable("classname").string());
                                                            #line 250 "CodeGeneratorScala.cpp"
  append(L".INITIAL(tokenSetId)");
                                                            #line 162 "CodeGeneratorScala.cpp.template"
                                                                if (variable("embedded").boolean())
                                                                {
                                                            #line 255 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"    var state = 0");
                                                            #line 165 "CodeGeneratorScala.cpp.template"
                                                                }
                                                            #line 260 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"    var code = result & ");
                                                            #line 167 "CodeGeneratorScala.cpp.template"
                                                                print(Math::powerof(2, variable("stateCodeBits").integer()) - 1);
                                                                if (variable("trace").boolean())
                                                                {
                                                            #line 267 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"\n");
  append(L"    ");
                                                            #line 172 "CodeGeneratorScala.cpp.template"
                                                                  if (variable("useGlr").boolean())
                                                                  {
                                                            #line 274 "CodeGeneratorScala.cpp"
  append(L"parser.");
                                                            #line 174 "CodeGeneratorScala.cpp.template"
                                                                  }
                                                            #line 278 "CodeGeneratorScala.cpp"
  append(L"writeTrace(\"    <next state=\\\"\" + (result & ");
                                                            #line 175 "CodeGeneratorScala.cpp.template"
                                                                  print(Math::powerof(2, variable("stateCodeBits").integer()) - 1);
                                                            #line 282 "CodeGeneratorScala.cpp"
  append(L") + \"\\\"\")");
                                                            #line 176 "CodeGeneratorScala.cpp.template"
                                                                }
                                                            #line 286 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"\n");
  append(L"    while (code != 0) {\n");
  append(L"      var charclass = -1\n");
  append(L"      var c0: Int = if (current < ");
                                                            #line 181 "CodeGeneratorScala.cpp.template"
                                                                if (variable("useGlr").boolean())
                                                                {
                                                            #line 295 "CodeGeneratorScala.cpp"
  append(L"parser.");
                                                            #line 183 "CodeGeneratorScala.cpp.template"
                                                                }
                                                            #line 299 "CodeGeneratorScala.cpp"
  append(L"size) ");
                                                            #line 184 "CodeGeneratorScala.cpp.template"
                                                                if (variable("useGlr").boolean())
                                                                {
                                                            #line 304 "CodeGeneratorScala.cpp"
  append(L"parser.");
                                                            #line 186 "CodeGeneratorScala.cpp.template"
                                                                }
                                                            #line 308 "CodeGeneratorScala.cpp"
  append(L"input(current) else 0");
                                                            #line 188 "CodeGeneratorScala.cpp.template"
                                                                if (variable("trace").boolean())
                                                                {
                                                            #line 313 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"      ");
                                                            #line 191 "CodeGeneratorScala.cpp.template"
                                                                  if (variable("useGlr").boolean())
                                                                  {
                                                            #line 319 "CodeGeneratorScala.cpp"
  append(L"parser.");
                                                            #line 193 "CodeGeneratorScala.cpp.template"
                                                                  }
                                                            #line 323 "CodeGeneratorScala.cpp"
  append(L"writeTrace(\" offset=\\\"\" + current + \"\\\"\")");
                                                            #line 194 "CodeGeneratorScala.cpp.template"
                                                                }
                                                            #line 327 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"      current += 1\n");
  append(L"      if (c0 < 0x");
                                                            #line 197 "CodeGeneratorScala.cpp.template"
                                                                print(format.toString<char>(variable("simplifiedCodeMap").integer(), 16, 0, 0, 0, "0123456789abcdef"));
                                                            #line 333 "CodeGeneratorScala.cpp"
  append(L") {");
                                                            #line 198 "CodeGeneratorScala.cpp.template"
                                                                if (variable("trace").boolean())
                                                                {
                                                            #line 338 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"        if (c0 >= 32 && c0 <= 126)\n");
  append(L"          ");
                                                            #line 202 "CodeGeneratorScala.cpp.template"
                                                                  if (variable("useGlr").boolean())
                                                                  {
                                                            #line 345 "CodeGeneratorScala.cpp"
  append(L"parser.");
                                                            #line 204 "CodeGeneratorScala.cpp.template"
                                                                  }
                                                            #line 349 "CodeGeneratorScala.cpp"
  append(L"writeTrace(\" char=\\\"\" + ");
                                                            #line 205 "CodeGeneratorScala.cpp.template"
                                                                  print(variable("classname").string());
                                                            #line 353 "CodeGeneratorScala.cpp"
  append(L".xmlEscape(");
                                                            #line 206 "CodeGeneratorScala.cpp.template"
                                                                  if (variable("useGlr").boolean())
                                                                  {
                                                            #line 358 "CodeGeneratorScala.cpp"
  append(L"parser.");
                                                            #line 208 "CodeGeneratorScala.cpp.template"
                                                                  }
                                                            #line 362 "CodeGeneratorScala.cpp"
  append(L"input.substring(current - 1, current)) + \"\\\"\")");
                                                            #line 210 "CodeGeneratorScala.cpp.template"
                                                                }
                                                            #line 366 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"        charclass = ");
                                                            #line 212 "CodeGeneratorScala.cpp.template"
                                                                print(variable("classname").string());
                                                            #line 371 "CodeGeneratorScala.cpp"
  append(L".MAP0(c0)\n");
  append(L"      }\n");
  append(L"      else if (c0 < 0x");
                                                            #line 215 "CodeGeneratorScala.cpp.template"
                                                                print(format.toString<char>(variable("uncompressedMapSize").integer(), 16, 0, 0, 0, "0123456789abcdef"));
                                                            #line 377 "CodeGeneratorScala.cpp"
  append(L") {\n");
                                                            #line 217 "CodeGeneratorScala.cpp.template"
                                                                CString map1(variable("classname").string());
                                                                map1 += ".MAP1";
                                                                compressedMapAccessor(8, "c", "charclass = ", map1.c_str(), &variable("m1bits").integer());
                                                            #line 383 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"      }\n");
  append(L"      else {");
                                                            #line 222 "CodeGeneratorScala.cpp.template"
                                                                if (variable("m2").size == 0)
                                                                {
                                                            #line 390 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"        charclass = 0");
                                                            #line 225 "CodeGeneratorScala.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 397 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"        if (");
                                                            #line 229 "CodeGeneratorScala.cpp.template"
                                                                  if (variable("uncompressedMapSize").integer() != 0xd800)
                                                                  {
                                                            #line 403 "CodeGeneratorScala.cpp"
  append(L"c0 >= 0xd800 && ");
                                                            #line 231 "CodeGeneratorScala.cpp.template"
                                                                  }
                                                            #line 407 "CodeGeneratorScala.cpp"
  append(L"c0 < 0xdc00) {\n");
  append(L"          val c1 = if (current < ");
                                                            #line 233 "CodeGeneratorScala.cpp.template"
                                                                  if (variable("useGlr").boolean())
                                                                  {
                                                            #line 413 "CodeGeneratorScala.cpp"
  append(L"parser.");
                                                            #line 235 "CodeGeneratorScala.cpp.template"
                                                                  }
                                                            #line 417 "CodeGeneratorScala.cpp"
  append(L"size) ");
                                                            #line 236 "CodeGeneratorScala.cpp.template"
                                                                  if (variable("useGlr").boolean())
                                                                  {
                                                            #line 422 "CodeGeneratorScala.cpp"
  append(L"parser.");
                                                            #line 238 "CodeGeneratorScala.cpp.template"
                                                                  }
                                                            #line 426 "CodeGeneratorScala.cpp"
  append(L"input(current) else 0\n");
  append(L"          if (c1 >= 0xdc00 && c1 < 0xe000) {");
                                                            #line 240 "CodeGeneratorScala.cpp.template"
                                                                  if (lookahead)
                                                                  {
                                                            #line 432 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"            nonbmp = true");
                                                            #line 243 "CodeGeneratorScala.cpp.template"
                                                                  }
                                                            #line 437 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"            current += 1\n");
  append(L"            c0 = ((c0 & 0x3ff) << 10) + (c1 & 0x3ff) + 0x10000\n");
  append(L"          }\n");
  append(L"        }\n");
  append(L"\n");
  append(L"        var lo = 0\n");
  append(L"        var hi = ");
                                                            #line 251 "CodeGeneratorScala.cpp.template"
                                                                  print(variable("m2").size / 3 - 1);
                                                            #line 448 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"        var m = ");
                                                            #line 253 "CodeGeneratorScala.cpp.template"
                                                                  print((variable("m2").size / 3) >> 1);
                                                            #line 453 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"        while (charclass < 0) {\n");
  append(L"          if (");
                                                            #line 256 "CodeGeneratorScala.cpp.template"
                                                                  print(variable("classname").string());
                                                            #line 459 "CodeGeneratorScala.cpp"
  append(L".MAP2(m) > c0) hi = m - 1\n");
  append(L"          else if (");
                                                            #line 258 "CodeGeneratorScala.cpp.template"
                                                                  print(variable("classname").string());
                                                            #line 464 "CodeGeneratorScala.cpp"
  append(L".MAP2(");
                                                            #line 259 "CodeGeneratorScala.cpp.template"
                                                                  print(variable("m2").size / 3);
                                                            #line 468 "CodeGeneratorScala.cpp"
  append(L" + m) < c0) lo = m + 1\n");
  append(L"          else charclass = ");
                                                            #line 261 "CodeGeneratorScala.cpp.template"
                                                                  print(variable("classname").string());
                                                            #line 473 "CodeGeneratorScala.cpp"
  append(L".MAP2(");
                                                            #line 262 "CodeGeneratorScala.cpp.template"
                                                                  print(variable("m2").size / 3 * 2);
                                                            #line 477 "CodeGeneratorScala.cpp"
  append(L" + m)\n");
  append(L"          if (lo > hi) charclass = 0 else m = (hi + lo) >> 1\n");
  append(L"        }");
                                                            #line 265 "CodeGeneratorScala.cpp.template"
                                                                }
                                                            #line 483 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"      }");
                                                            #line 267 "CodeGeneratorScala.cpp.template"
                                                                if (variable("trace").boolean())
                                                                {
                                                            #line 489 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"      ");
                                                            #line 270 "CodeGeneratorScala.cpp.template"
                                                                  if (variable("useGlr").boolean())
                                                                  {
                                                            #line 495 "CodeGeneratorScala.cpp"
  append(L"parser.");
                                                            #line 272 "CodeGeneratorScala.cpp.template"
                                                                  }
                                                            #line 499 "CodeGeneratorScala.cpp"
  append(L"writeTrace(\" codepoint=\\\"\" + c0 + \"\\\" class=\\\"\" + charclass + \"\\\"\")");
                                                            #line 274 "CodeGeneratorScala.cpp.template"
                                                                }
                                                            #line 503 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"\n");
  append(L"      state = code\n");
                                                            #line 278 "CodeGeneratorScala.cpp.template"
                                                                CString transition(variable("classname").string());
                                                                transition += ".TRANSITION";
                                                                compressedMap2dAccessor("code - 1", "charclass", variable("a1cols").integer(),
                                                                                           6, "i", "code = ", transition.c_str(), &variable("a1bits").integer());
                                                            #line 512 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"\n");
  append(L"      if (code > ");
                                                            #line 284 "CodeGeneratorScala.cpp.template"
                                                                print(Math::powerof(2, variable("stateCodeBits").integer()) - 1);
                                                            #line 518 "CodeGeneratorScala.cpp"
  append(L") {\n");
  append(L"        result = code");
                                                            #line 286 "CodeGeneratorScala.cpp.template"
                                                                if (variable("trace").boolean())
                                                                {
                                                            #line 524 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"        ");
                                                            #line 289 "CodeGeneratorScala.cpp.template"
                                                                  if (variable("useGlr").boolean())
                                                                  {
                                                            #line 530 "CodeGeneratorScala.cpp"
  append(L"parser.");
                                                            #line 291 "CodeGeneratorScala.cpp.template"
                                                                  }
                                                            #line 534 "CodeGeneratorScala.cpp"
  append(L"writeTrace(\" result=\\\"\" + ");
                                                            #line 292 "CodeGeneratorScala.cpp.template"
                                                                  print(variable("classname").string());
                                                            #line 538 "CodeGeneratorScala.cpp"
  append(L".xmlEscape(");
                                                            #line 293 "CodeGeneratorScala.cpp.template"
                                                                  print(variable("classname").string());
                                                            #line 542 "CodeGeneratorScala.cpp"
  append(L".TOKEN(((result >> ");
                                                            #line 294 "CodeGeneratorScala.cpp.template"
                                                                  print(variable("stateCodeBits").integer());
                                                            #line 546 "CodeGeneratorScala.cpp"
  append(L") & ");
                                                            #line 295 "CodeGeneratorScala.cpp.template"
                                                                  print(Math::powerof(2, variable("tokencodeBits").integer()) - 1);
                                                            #line 550 "CodeGeneratorScala.cpp"
  append(L") - 1)) + \"\\\"\")");
                                                            #line 297 "CodeGeneratorScala.cpp.template"
                                                                  if (lookahead || hasFixedTokenLength)
                                                                  {
                                                                    int contextOffset = variable("stateCodeBits").integer()
                                                                                      + variable("tokencodeBits").integer();
                                                                    int sizeOffset = contextOffset
                                                                                   + (hasFixedTokenLength ? 1 : 0);
                                                                    if (hasFixedTokenLength)
                                                                    {
                                                            #line 561 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"        if ((result & ");
                                                            #line 306 "CodeGeneratorScala.cpp.template"
                                                                      print(Math::powerof(2, contextOffset));
                                                            #line 566 "CodeGeneratorScala.cpp"
  append(L") > 0) {\n");
  append(L"          ");
                                                            #line 308 "CodeGeneratorScala.cpp.template"
                                                                      if (variable("useGlr").boolean())
                                                                      {
                                                            #line 572 "CodeGeneratorScala.cpp"
  append(L"parser.");
                                                            #line 310 "CodeGeneratorScala.cpp.template"
                                                                      }
                                                            #line 576 "CodeGeneratorScala.cpp"
  append(L"writeTrace(\" token-size=\\\"\" + (result >> ");
                                                            #line 311 "CodeGeneratorScala.cpp.template"
                                                                      print(sizeOffset);
                                                            #line 580 "CodeGeneratorScala.cpp"
  append(L") + \"\\\"\")\n");
  append(L"        }\n");
  append(L"        else ");
                                                            #line 314 "CodeGeneratorScala.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 588 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"        ");
                                                            #line 318 "CodeGeneratorScala.cpp.template"
                                                                    }
                                                            #line 593 "CodeGeneratorScala.cpp"
  append(L"if ((result >> ");
                                                            #line 319 "CodeGeneratorScala.cpp.template"
                                                                    print(sizeOffset);
                                                            #line 597 "CodeGeneratorScala.cpp"
  append(L") > 0) {\n");
  append(L"          ");
                                                            #line 321 "CodeGeneratorScala.cpp.template"
                                                                    if (variable("useGlr").boolean())
                                                                    {
                                                            #line 603 "CodeGeneratorScala.cpp"
  append(L"parser.");
                                                            #line 323 "CodeGeneratorScala.cpp.template"
                                                                    }
                                                            #line 607 "CodeGeneratorScala.cpp"
  append(L"writeTrace(\" trailing-context-size=\\\"\" + (result >> ");
                                                            #line 324 "CodeGeneratorScala.cpp.template"
                                                                    print(sizeOffset);
                                                            #line 611 "CodeGeneratorScala.cpp"
  append(L") + \"\\\"\")\n");
  append(L"        }");
                                                            #line 326 "CodeGeneratorScala.cpp.template"
                                                                  }
                                                                }
                                                            #line 617 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"        code &= ");
                                                            #line 329 "CodeGeneratorScala.cpp.template"
                                                                print(Math::powerof(2, variable("stateCodeBits").integer()) - 1);
                                                            #line 622 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"        end = current\n");
  append(L"      }");
                                                            #line 332 "CodeGeneratorScala.cpp.template"
                                                                if (variable("trace").boolean())
                                                                {
                                                            #line 629 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"      ");
                                                            #line 335 "CodeGeneratorScala.cpp.template"
                                                                  if (variable("useGlr").boolean())
                                                                  {
                                                            #line 635 "CodeGeneratorScala.cpp"
  append(L"parser.");
                                                            #line 337 "CodeGeneratorScala.cpp.template"
                                                                  }
                                                            #line 639 "CodeGeneratorScala.cpp"
  append(L"writeTrace(\"/>\\n\")\n");
  append(L"      if (code != 0) {\n");
  append(L"        ");
                                                            #line 340 "CodeGeneratorScala.cpp.template"
                                                                  if (variable("useGlr").boolean())
                                                                  {
                                                            #line 646 "CodeGeneratorScala.cpp"
  append(L"parser.");
                                                            #line 342 "CodeGeneratorScala.cpp.template"
                                                                  }
                                                            #line 650 "CodeGeneratorScala.cpp"
  append(L"writeTrace(\"    <next state=\\\"\" + code + \"\\\"\")\n");
  append(L"      }");
                                                            #line 344 "CodeGeneratorScala.cpp.template"
                                                                }
                                                            #line 655 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    result >>= ");
                                                            #line 348 "CodeGeneratorScala.cpp.template"
                                                                print(variable("stateCodeBits").integer());
                                                            #line 662 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"    if (result == 0) {\n");
  append(L"      end = current - 1\n");
  append(L"      val c1 = if (end < ");
                                                            #line 352 "CodeGeneratorScala.cpp.template"
                                                                if (variable("useGlr").boolean())
                                                                {
                                                            #line 670 "CodeGeneratorScala.cpp"
  append(L"parser.");
                                                            #line 354 "CodeGeneratorScala.cpp.template"
                                                                }
                                                            #line 674 "CodeGeneratorScala.cpp"
  append(L"size) ");
                                                            #line 355 "CodeGeneratorScala.cpp.template"
                                                                if (variable("useGlr").boolean())
                                                                {
                                                            #line 679 "CodeGeneratorScala.cpp"
  append(L"parser.");
                                                            #line 357 "CodeGeneratorScala.cpp.template"
                                                                }
                                                            #line 683 "CodeGeneratorScala.cpp"
  append(L"input(end) else 0\n");
  append(L"      if (c1 >= 0xdc00 && c1 < 0xe000) {\n");
  append(L"        end -= 1\n");
  append(L"      }");
                                                            #line 361 "CodeGeneratorScala.cpp.template"
                                                                if (variable("trace").boolean())
                                                                {
                                                            #line 691 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"      ");
                                                            #line 364 "CodeGeneratorScala.cpp.template"
                                                                  if (variable("useGlr").boolean())
                                                                  {
                                                            #line 697 "CodeGeneratorScala.cpp"
  append(L"parser.");
                                                            #line 366 "CodeGeneratorScala.cpp.template"
                                                                  }
                                                            #line 701 "CodeGeneratorScala.cpp"
  append(L"writeTrace(\"    <fail begin=\\\"\" + begin + \"\\\" end=\\\"\" + end + \"\\\" state=\\\"\" + state + \"\\\"/>\\n\")\n");
  append(L"      ");
                                                            #line 368 "CodeGeneratorScala.cpp.template"
                                                                  if (variable("useGlr").boolean())
                                                                  {
                                                            #line 707 "CodeGeneratorScala.cpp"
  append(L"parser.");
                                                            #line 370 "CodeGeneratorScala.cpp.template"
                                                                  }
                                                            #line 711 "CodeGeneratorScala.cpp"
  append(L"writeTrace(\"  </tokenize>\\n\")");
                                                            #line 371 "CodeGeneratorScala.cpp.template"
                                                                }
                                                                if (variable("embedded").boolean())
                                                                {
                                                                  if (variable("useGlr").boolean())
                                                                  {
                                                            #line 719 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"      end = begin\n");
  append(L"      -1");
                                                            #line 378 "CodeGeneratorScala.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 727 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"      error(begin, end, state, -1, -1)");
                                                            #line 382 "CodeGeneratorScala.cpp.template"
                                                                  }
                                                                }
                                                            #line 733 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"    }\n");
  append(L"    else {");
                                                            #line 386 "CodeGeneratorScala.cpp.template"
                                                                int lowBits = variable("tokencodeBits").integer();
                                                                if (hasFixedTokenLength && ! lookahead)
                                                                {
                                                            #line 741 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"      if ((result & ");
                                                            #line 390 "CodeGeneratorScala.cpp.template"
                                                                  print(Math::powerof(2, lowBits));
                                                                  ++lowBits;
                                                            #line 747 "CodeGeneratorScala.cpp"
  append(L") != 0) {\n");
  append(L"        end = begin\n");
  append(L"      }");
                                                            #line 394 "CodeGeneratorScala.cpp.template"
                                                                }
                                                                else
                                                                {
                                                                  if (hasFixedTokenLength)
                                                                  {
                                                            #line 757 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"      if ((result & ");
                                                            #line 400 "CodeGeneratorScala.cpp.template"
                                                                    print(Math::powerof(2, lowBits));
                                                                    ++lowBits;
                                                            #line 763 "CodeGeneratorScala.cpp"
  append(L") != 0) {\n");
  append(L"        end = begin\n");
  append(L"        if (nonbmp) {\n");
  append(L"          var i = result >> ");
                                                            #line 405 "CodeGeneratorScala.cpp.template"
                                                                    print(lowBits);
                                                            #line 770 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"          while (i > 0) {\n");
  append(L"            val c1 = if (end < ");
                                                            #line 408 "CodeGeneratorScala.cpp.template"
                                                                    if (variable("useGlr").boolean())
                                                                    {
                                                            #line 777 "CodeGeneratorScala.cpp"
  append(L"parser.");
                                                            #line 410 "CodeGeneratorScala.cpp.template"
                                                                    }
                                                            #line 781 "CodeGeneratorScala.cpp"
  append(L"size) ");
                                                            #line 411 "CodeGeneratorScala.cpp.template"
                                                                    if (variable("useGlr").boolean())
                                                                    {
                                                            #line 786 "CodeGeneratorScala.cpp"
  append(L"parser.");
                                                            #line 413 "CodeGeneratorScala.cpp.template"
                                                                    }
                                                            #line 790 "CodeGeneratorScala.cpp"
  append(L"input(end) else 0\n");
  append(L"            end += 1\n");
  append(L"            if (c1 >= 0xd800 && c1 < 0xdc00) {\n");
  append(L"              end += 1\n");
  append(L"            }\n");
  append(L"            i -= 1\n");
  append(L"          }\n");
  append(L"        }\n");
  append(L"        else {\n");
  append(L"          end += (result >> ");
                                                            #line 423 "CodeGeneratorScala.cpp.template"
                                                                    print(lowBits);
                                                            #line 803 "CodeGeneratorScala.cpp"
  append(L")\n");
  append(L"        }\n");
  append(L"      }");
                                                            #line 426 "CodeGeneratorScala.cpp.template"
                                                                  }
                                                                  if (lookahead)
                                                                  {
                                                            #line 811 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"      if (nonbmp) {\n");
  append(L"        var i = result >> ");
                                                            #line 431 "CodeGeneratorScala.cpp.template"
                                                                    print(lowBits);
                                                            #line 817 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"        while (i > 0) {\n");
  append(L"          end -= 1\n");
  append(L"          val c1 = if (end < ");
                                                            #line 435 "CodeGeneratorScala.cpp.template"
                                                                    if (variable("useGlr").boolean())
                                                                    {
                                                            #line 825 "CodeGeneratorScala.cpp"
  append(L"parser.");
                                                            #line 437 "CodeGeneratorScala.cpp.template"
                                                                    }
                                                            #line 829 "CodeGeneratorScala.cpp"
  append(L"size) ");
                                                            #line 438 "CodeGeneratorScala.cpp.template"
                                                                    if (variable("useGlr").boolean())
                                                                    {
                                                            #line 834 "CodeGeneratorScala.cpp"
  append(L"parser.");
                                                            #line 440 "CodeGeneratorScala.cpp.template"
                                                                    }
                                                            #line 838 "CodeGeneratorScala.cpp"
  append(L"input(end) else 0\n");
  append(L"          if (c1 >= 0xdc00 && c1 < 0xe000) {\n");
  append(L"            end -= 1\n");
  append(L"          }\n");
  append(L"          i -= 1\n");
  append(L"        }\n");
  append(L"      }\n");
  append(L"      else {\n");
  append(L"        end -= result >> ");
                                                            #line 449 "CodeGeneratorScala.cpp.template"
                                                                    print(lowBits);
                                                            #line 850 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"      }");
                                                            #line 451 "CodeGeneratorScala.cpp.template"
                                                                  }
                                                                }
                                                            #line 856 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"      if (end > ");
                                                            #line 454 "CodeGeneratorScala.cpp.template"
                                                                if (variable("useGlr").boolean())
                                                                {
                                                            #line 862 "CodeGeneratorScala.cpp"
  append(L"parser.");
                                                            #line 456 "CodeGeneratorScala.cpp.template"
                                                                }
                                                            #line 866 "CodeGeneratorScala.cpp"
  append(L"size) end = ");
                                                            #line 457 "CodeGeneratorScala.cpp.template"
                                                                if (variable("useGlr").boolean())
                                                                {
                                                            #line 871 "CodeGeneratorScala.cpp"
  append(L"parser.");
                                                            #line 459 "CodeGeneratorScala.cpp.template"
                                                                }
                                                            #line 875 "CodeGeneratorScala.cpp"
  append(L"size");
                                                            #line 460 "CodeGeneratorScala.cpp.template"
                                                                if (variable("trace").boolean())
                                                                {
                                                            #line 880 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"      ");
                                                            #line 463 "CodeGeneratorScala.cpp.template"
                                                                  if (variable("useGlr").boolean())
                                                                  {
                                                            #line 886 "CodeGeneratorScala.cpp"
  append(L"parser.");
                                                            #line 465 "CodeGeneratorScala.cpp.template"
                                                                  }
                                                            #line 890 "CodeGeneratorScala.cpp"
  append(L"writeTrace(\"    <done result=\\\"\" + ");
                                                            #line 466 "CodeGeneratorScala.cpp.template"
                                                                  print(variable("classname").string());
                                                            #line 894 "CodeGeneratorScala.cpp"
  append(L".xmlEscape(");
                                                            #line 467 "CodeGeneratorScala.cpp.template"
                                                                  print(variable("classname").string());
                                                            #line 898 "CodeGeneratorScala.cpp"
  append(L".TOKEN((result & ");
                                                            #line 468 "CodeGeneratorScala.cpp.template"
                                                                  print(Math::powerof(2, variable("tokencodeBits").integer()) - 1);
                                                            #line 902 "CodeGeneratorScala.cpp"
  append(L") - 1)) + \"\\\" begin=\\\"\" + begin + \"\\\" end=\\\"\" + end + \"\\\"/>\\n\")\n");
  append(L"      ");
                                                            #line 470 "CodeGeneratorScala.cpp.template"
                                                                  if (variable("useGlr").boolean())
                                                                  {
                                                            #line 908 "CodeGeneratorScala.cpp"
  append(L"parser.");
                                                            #line 472 "CodeGeneratorScala.cpp.template"
                                                                  }
                                                            #line 912 "CodeGeneratorScala.cpp"
  append(L"writeTrace(\"  </tokenize>\\n\")");
                                                            #line 473 "CodeGeneratorScala.cpp.template"
                                                                }
                                                                const char *flags = getenv("FLAGS");
                                                                bool hack = flags && strchr(flags, 'H');
                                                                if (hack)
                                                                {
                                                            #line 920 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"      hack((result & ");
                                                            #line 479 "CodeGeneratorScala.cpp.template"
                                                                  print(Math::powerof(2, variable("tokencodeBits").integer()) - 1);
                                                            #line 925 "CodeGeneratorScala.cpp"
  append(L") - 1)\n");
  append(L"    }\n");
                                                            #line 482 "CodeGeneratorScala.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 932 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"      (result & ");
                                                            #line 486 "CodeGeneratorScala.cpp.template"
                                                                  print(Math::powerof(2, variable("tokencodeBits").integer()) - 1);
                                                            #line 937 "CodeGeneratorScala.cpp"
  append(L") - 1\n");
  append(L"    }\n");
  append(L"  }\n");
                                                            #line 490 "CodeGeneratorScala.cpp.template"
                                                                }
                                                              }
                                                              if (! variable("embedded").boolean())
                                                              {
                                                            #line 946 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"  public String[] getExpectedTokenSet()\n");
  append(L"  {\n");
  append(L"    return getTokenSet(- state);\n");
  append(L"  }\n");
                                                            #line 499 "CodeGeneratorScala.cpp.template"
                                                              }
                                                            #line 954 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"  var begin = 0\n");
  append(L"  var end = 0\n");
                                                            #line 503 "CodeGeneratorScala.cpp.template"
                                                            }

                                                            void CodeGeneratorScala::generateStaticCode()
                                                            {
                                                              isScala = true;
                                                              if (defined("gtbits"))
                                                              {
                                                            #line 966 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"  private def goTo(nonterminal: Int, state: Int): Int = {\n");
                                                            #line 512 "CodeGeneratorScala.cpp.template"
                                                                CString goTo(variable("classname").string());
                                                                goTo += ".GOTO";
                                                                compressedMap2dAccessor("nonterminal", "state", variable("gtcols").integer(),
                                                                                           4, "i", "", goTo.c_str(), &variable("gtbits").integer());
                                                            #line 974 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"  }\n");
                                                            #line 518 "CodeGeneratorScala.cpp.template"
                                                              }
                                                              if (variable("trace").boolean())
                                                              {
                                                            #line 981 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"  private def xmlEscape(s: String) = {\n");
  append(L"    var result = \"\"\n");
  append(L"    for (i <- 0 to s.length - 1) {\n");
  append(L"      var c = s.charAt(i)\n");
  append(L"      c match {\n");
  append(L"      case '<' => result += \"&lt;\"\n");
  append(L"      case '\"' => result += \"&quot;\"\n");
  append(L"      case '&' => result += \"&amp;\"\n");
  append(L"      case _ => result += c\n");
  append(L"      }\n");
  append(L"    }\n");
  append(L"    result\n");
  append(L"  }\n");
                                                            #line 535 "CodeGeneratorScala.cpp.template"
                                                              }
                                                              if (variable("nolexer").boolean())
                                                              {
                                                            #line 1000 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"  public static int getTokenCount() {return ");
                                                            #line 539 "CodeGeneratorScala.cpp.template"
                                                                print(variable("t1").size);
                                                            #line 1005 "CodeGeneratorScala.cpp"
  append(L";}\n");
  append(L"  public static String getTokenName(int code) {return code >= 0 && code < ");
                                                            #line 542 "CodeGeneratorScala.cpp.template"
                                                                print(variable("t1").size);
                                                            #line 1010 "CodeGeneratorScala.cpp"
  append(L" ? TOKEN[code] : null;}\n");
  append(L"  public static int getTokenSetCount() {return ");
                                                            #line 544 "CodeGeneratorScala.cpp.template"
                                                                print(variable("entrycount").integer());
                                                            #line 1015 "CodeGeneratorScala.cpp"
  append(L";}\n");
  append(L"\n");
  append(L"  public static String[] getTokenSet(int tokenSetId) {");
                                                            #line 547 "CodeGeneratorScala.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 1023 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"  private def getTokenSet(tokenSetId: Int) = {");
                                                            #line 551 "CodeGeneratorScala.cpp.template"
                                                              }
                                                            #line 1028 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"    var expected = ArrayBuffer[String]()");
                                                            #line 553 "CodeGeneratorScala.cpp.template"
                                                              if (! variable("nolexer").boolean())
                                                              {
                                                            #line 1034 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"    val s = if (tokenSetId < 0) - tokenSetId else INITIAL(tokenSetId) & ");
                                                            #line 557 "CodeGeneratorScala.cpp.template"
                                                                print(Math::powerof(2, variable("stateCodeBits").integer()) - 1);
                                                              }
                                                            #line 1040 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"    var i = 0\n");
  append(L"    while (i < ");
                                                            #line 561 "CodeGeneratorScala.cpp.template"
                                                              print(variable("t1").size);
                                                            #line 1046 "CodeGeneratorScala.cpp"
  append(L") {\n");
  append(L"      var j = i\n");
  append(L"      val i0 = (i >> 5) * ");
                                                            #line 564 "CodeGeneratorScala.cpp.template"
                                                              print(variable("transitionStateCount").integer());
                                                            #line 1052 "CodeGeneratorScala.cpp"
  append(L" + ");
                                                            #line 565 "CodeGeneratorScala.cpp.template"
                                                              if (variable("nolexer").boolean())
                                                              {
                                                            #line 1057 "CodeGeneratorScala.cpp"
  append(L"tokenSetId");
                                                            #line 567 "CodeGeneratorScala.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 1063 "CodeGeneratorScala.cpp"
  append(L"s - 1");
                                                            #line 570 "CodeGeneratorScala.cpp.template"
                                                              }
                                                            #line 1067 "CodeGeneratorScala.cpp"
  append(L"\n");
                                                            #line 572 "CodeGeneratorScala.cpp.template"
                                                              compressedMapAccessor(6, "i", "var f = ", "EXPECTED", &variable("t0bits").integer());
                                                            #line 1071 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"      while (f != 0) {\n");
  append(L"        if ((f & 1) != 0) {\n");
  append(L"          expected += TOKEN(j)\n");
  append(L"        }\n");
  append(L"        f >>>= 1\n");
  append(L"        j += 1\n");
  append(L"      }\n");
  append(L"      i += 32\n");
  append(L"    }\n");
  append(L"    expected.toArray\n");
  append(L"  }");
                                                            #line 584 "CodeGeneratorScala.cpp.template"
                                                              size_t total = 0;
                                                              for (VarsInInsertionOrder::iterator a(varsInInsertionOrder.begin());
                                                                   a != varsInInsertionOrder.end(); ++a)
                                                                if (   a->isArray()
                                                                    && strlen(a->name) == 2
                                                                    && (a->hasType(CGVariable::INTEGER) || a->hasType(CGVariable::UNSIGNED)))
                                                              {
                                                                total += a->size;
                                                              }
                                                              bool asString = total > 4096;
                                                              size_t limit = asString ? 119 : 119;
                                                              for (VarsInInsertionOrder::iterator a(varsInInsertionOrder.begin());
                                                                   a != varsInInsertionOrder.end(); ++a)
                                                                if (   a->isArray()
                                                                    && a->size > 0
                                                                    && (a->hasType(CGVariable::INTEGER) || a->hasType(CGVariable::UNSIGNED))
                                                                    && strlen(a->name) == 2)
                                                              {
                                                            #line 1103 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"\n");
  append(L"  private final val ");
                                                            #line 604 "CodeGeneratorScala.cpp.template"
                                                                print(a->longName);
                                                            #line 1109 "CodeGeneratorScala.cpp"
  append(L" = Array(");
                                                            #line 605 "CodeGeneratorScala.cpp.template"
                                                                int w = (int) Format::width(a->size);
                                                                for (size_t j = 0; j < a->size; ++j)
                                                                {
                                                                  if (j == 0 || lineLength() + Format::width(a->integer(j)) + (asString ? 3 : 2) > limit)
                                                                  {
                                                                    if (j) print(asString ? "\"," : ",");
                                                            #line 1118 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"    /* ");
                                                            #line 612 "CodeGeneratorScala.cpp.template"
                                                                    print(format.toString<char>(j, 10, w));
                                                            #line 1123 "CodeGeneratorScala.cpp"
  append(L" */ ");
                                                            #line 613 "CodeGeneratorScala.cpp.template"
                                                                    if (asString) print("\"");
                                                                  }
                                                                  else
                                                                  {
                                                            #line 1130 "CodeGeneratorScala.cpp"
  append(L", ");
                                                            #line 617 "CodeGeneratorScala.cpp.template"
                                                                  }
                                                                  if (a->hasType(CGVariable::UNSIGNED))
                                                                  {
                                                                    print(format.toString<char>((unsigned) a->integer(j)));
                                                                  }
                                                                  else
                                                                  {
                                                                    print(a->integer(j));
                                                                  }
                                                                }
                                                                if (asString)
                                                                {
                                                            #line 1145 "CodeGeneratorScala.cpp"
  append(L"\"\n");
  append(L"  ).flatMap(_.split(\", \").map(_.toInt))");
                                                            #line 630 "CodeGeneratorScala.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1152 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"  )");
                                                            #line 634 "CodeGeneratorScala.cpp.template"
                                                                }
                                                              }
                                                              for (VarsInInsertionOrder::iterator a(varsInInsertionOrder.begin());
                                                                   a != varsInInsertionOrder.end(); ++a)
                                                                if (a->isArray() && a->size > 0 && a->hasType(CGVariable::STRING) && strlen(a->name) == 2)
                                                              {
                                                            #line 1162 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"\n");
  append(L"  private final val ");
                                                            #line 642 "CodeGeneratorScala.cpp.template"
                                                                print(a->longName);
                                                            #line 1168 "CodeGeneratorScala.cpp"
  append(L" = Array(\n");
                                                            #line 644 "CodeGeneratorScala.cpp.template"
                                                                for (size_t j = 0; j < a->size; ++j)
                                                                {
                                                                  if (j)
                                                                  {
                                                            #line 1175 "CodeGeneratorScala.cpp"
  append(L",\n");
                                                            #line 649 "CodeGeneratorScala.cpp.template"
                                                                  }
                                                            #line 1179 "CodeGeneratorScala.cpp"
  append(L"    \"");
                                                            #line 650 "CodeGeneratorScala.cpp.template"
                                                                  const char *s = a->string(j);
                                                                  const char *c = s;
                                                                  for (; *c; ++c)
                                                                  {
                                                                    if (*c == '"' || *c == '\\')
                                                                    {
                                                                      print(s, c - s);
                                                                      s = c;
                                                                      print("\\");
                                                                    }
                                                                  }
                                                                  print(s, c - s);
                                                            #line 1194 "CodeGeneratorScala.cpp"
  append(L"\"");
                                                            #line 662 "CodeGeneratorScala.cpp.template"
                                                                }
                                                            #line 1198 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"  )");
                                                            #line 664 "CodeGeneratorScala.cpp.template"
                                                              }
                                                              if (! variable("embedded").boolean())
                                                              {
                                                            #line 1205 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"\n");
  append(L"  public enum Token\n");
  append(L"  {\n");
  append(L"    ");
                                                            #line 671 "CodeGeneratorScala.cpp.template"
                                                                const CGVariable &token = variable("token");
                                                                int w = (int) Format::width(token.size);
                                                                for (size_t i = 0; i < token.size; ++i)
                                                                {
                                                                  if (i)
                                                                  {
                                                            #line 1218 "CodeGeneratorScala.cpp"
  append(L",\n");
  append(L"    ");
                                                            #line 678 "CodeGeneratorScala.cpp.template"
                                                                  }
                                                            #line 1223 "CodeGeneratorScala.cpp"
  append(L"/* ");
                                                            #line 679 "CodeGeneratorScala.cpp.template"
                                                                  print(format.toString<char>(i, 10, w));
                                                            #line 1227 "CodeGeneratorScala.cpp"
  append(L" */ ");
                                                            #line 680 "CodeGeneratorScala.cpp.template"
                                                                  print(token.string(i));
                                                                }
                                                            #line 1232 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"  };");
                                                            #line 683 "CodeGeneratorScala.cpp.template"
                                                              }
                                                              if (variable("selfTest").boolean())
                                                              {
                                                            #line 1239 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"\n");
  append(L"  private void selfTest(int set, int tokenId)\n");
  append(L"  {\n");
  append(L"    String tokenString = TOKEN[tokenId];\n");
  append(L"    if (tokenString.startsWith(\"'\"))\n");
  append(L"    {\n");
  append(L"      System.out.print(\"testing(\" + set + \", \" + tokenId + \")...\");\n");
  append(L"      tokenString = tokenString.substring(1, tokenString.length() - 1).replace(\"''\", \"'\");\n");
  append(L"      if (tokenString.trim().equals(\"\"))\n");
  append(L"      {\n");
  append(L"        System.out.println(\"  skipped\");\n");
  append(L"      }\n");
  append(L"      else\n");
  append(L"      {\n");
  append(L"        int result = match(set, tokenString + \" \");\n");
  append(L"        int resultSize = getSize();\n");
  append(L"        if (result != tokenId || resultSize != tokenString.length())\n");
  append(L"        {\n");
  append(L"          System.out.println();\n");
  append(L"          System.out.println(\"  tested: \" + tokenString);\n");
  append(L"          System.out.println(\"  result: \" + result);\n");
  append(L"          System.out.println(\"    size: \" + resultSize);\n");
  append(L"          System.exit(1);\n");
  append(L"        }\n");
  append(L"        else\n");
  append(L"        {\n");
  append(L"          System.out.println(\"  OK\");\n");
  append(L"        }\n");
  append(L"      }\n");
  append(L"    }\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  public static void main(String[] args)\n");
  append(L"  {\n");
  append(L"    ");
                                                            #line 721 "CodeGeneratorScala.cpp.template"
                                                                print(variable("classname").string());
                                                            #line 1278 "CodeGeneratorScala.cpp"
  append(L" testee = new ");
                                                            #line 722 "CodeGeneratorScala.cpp.template"
                                                                print(variable("classname").string());
                                                            #line 1282 "CodeGeneratorScala.cpp"
  append(L"();\n");
  append(L"    for (int e = 0; e < ");
                                                            #line 724 "CodeGeneratorScala.cpp.template"
                                                                print(variable("a0").size);
                                                            #line 1287 "CodeGeneratorScala.cpp"
  append(L"; ++e)\n");
  append(L"    {\n");
  append(L"      int s = INITIAL[e] & ");
                                                            #line 727 "CodeGeneratorScala.cpp.template"
                                                                print(Math::powerof(2, variable("stateCodeBits").integer()) - 1);
                                                            #line 1293 "CodeGeneratorScala.cpp"
  append(L";\n");
  append(L"      for (int i = 0; i < ");
                                                            #line 729 "CodeGeneratorScala.cpp.template"
                                                                print(variable("t1").size);
                                                            #line 1298 "CodeGeneratorScala.cpp"
  append(L"; i += 32)\n");
  append(L"      {\n");
  append(L"        int j = i;\n");
  append(L"        int i0 = (i >> 5) * ");
                                                            #line 733 "CodeGeneratorScala.cpp.template"
                                                                print(variable("transitionStateCount").integer());
                                                            #line 1305 "CodeGeneratorScala.cpp"
  append(L" + s - 1;\n");
                                                            #line 735 "CodeGeneratorScala.cpp.template"
                                                                compressedMapAccessor(8, "i", "int f = ", "EXPECTED", &variable("t0bits").integer());
                                                            #line 1309 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"        for ( ; f != 0; f >>>= 1, ++j)\n");
  append(L"        {\n");
  append(L"          if ((f & 1) != 0)\n");
  append(L"          {\n");
  append(L"            testee.selfTest(e, j);\n");
  append(L"          }\n");
  append(L"        }\n");
  append(L"      }\n");
  append(L"    }\n");
  append(L"  }");
                                                            #line 746 "CodeGeneratorScala.cpp.template"
                                                              }
                                                            #line 1323 "CodeGeneratorScala.cpp"
  append(L"\n");
                                                            #line 748 "CodeGeneratorScala.cpp.template"
                                                              if (! variable("embedded").boolean())
                                                              {
                                                            #line 1328 "CodeGeneratorScala.cpp"
  append(L"}\n");
                                                            #line 751 "CodeGeneratorScala.cpp.template"
                                                              }
                                                            }

                                                            void CodeGeneratorScala::generateData()
                                                            {
                                                            }

// End
