// This file was generated on Sun Nov 24, 2024 16:09 (UTC+01) by REx v6.0 which is Copyright (c) 1979-2024 by Gunther Rademacher <grd@gmx.net>
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
                                                            #line 127 "CodeGeneratorScala.cpp.template"
                                                              }
                                                            #line 190 "CodeGeneratorScala.cpp"
  append(L" def matcher(tokenSetId: Int) = {");
                                                            #line 129 "CodeGeneratorScala.cpp.template"
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
                                                            #line 141 "CodeGeneratorScala.cpp.template"
                                                              }
                                                              else
                                                              {
                                                                if (variable("trace").boolean())
                                                                {
                                                            #line 211 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 147 "CodeGeneratorScala.cpp.template"
                                                                  if (variable("useGlr").boolean())
                                                                  {
                                                            #line 217 "CodeGeneratorScala.cpp"
  append(L"parser.");
                                                            #line 149 "CodeGeneratorScala.cpp.template"
                                                                  }
                                                            #line 221 "CodeGeneratorScala.cpp"
  append(L"writeTrace(\"  <tokenize ");
                                                            #line 150 "CodeGeneratorScala.cpp.template"
                                                                  if (variable("useGlr").boolean())
                                                                  {
                                                            #line 226 "CodeGeneratorScala.cpp"
  append(L"thread=\\\"\" + id + \"\\\" ");
                                                            #line 152 "CodeGeneratorScala.cpp.template"
                                                                  }
                                                            #line 230 "CodeGeneratorScala.cpp"
  append(L"tokenset=\\\"\" + tokenSetId + \"\\\">\\n\")\n");
                                                            #line 154 "CodeGeneratorScala.cpp.template"
                                                                }
                                                                int lookahead = variable("maxcontextlength").integer();
                                                                bool hasFixedTokenLength = variable("hasfixedtokenlength").boolean();
                                                                if (lookahead)
                                                                {
                                                            #line 238 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"    var nonbmp = false");
                                                            #line 160 "CodeGeneratorScala.cpp.template"
                                                                }
                                                            #line 243 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"    begin = end\n");
  append(L"    var current = end\n");
  append(L"    var result = ");
                                                            #line 164 "CodeGeneratorScala.cpp.template"
                                                                print(variable("classname").string());
                                                            #line 250 "CodeGeneratorScala.cpp"
  append(L".INITIAL(tokenSetId)");
                                                            #line 165 "CodeGeneratorScala.cpp.template"
                                                                if (variable("embedded").boolean())
                                                                {
                                                            #line 255 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"    var state = 0");
                                                            #line 168 "CodeGeneratorScala.cpp.template"
                                                                }
                                                            #line 260 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"    var code = result & ");
                                                            #line 170 "CodeGeneratorScala.cpp.template"
                                                                print(Math::powerof(2, variable("stateCodeBits").integer()) - 1);
                                                                if (variable("trace").boolean())
                                                                {
                                                            #line 267 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"\n");
  append(L"    ");
                                                            #line 175 "CodeGeneratorScala.cpp.template"
                                                                  if (variable("useGlr").boolean())
                                                                  {
                                                            #line 274 "CodeGeneratorScala.cpp"
  append(L"parser.");
                                                            #line 177 "CodeGeneratorScala.cpp.template"
                                                                  }
                                                            #line 278 "CodeGeneratorScala.cpp"
  append(L"writeTrace(\"    <next state=\\\"\" + (result & ");
                                                            #line 178 "CodeGeneratorScala.cpp.template"
                                                                  print(Math::powerof(2, variable("stateCodeBits").integer()) - 1);
                                                            #line 282 "CodeGeneratorScala.cpp"
  append(L") + \"\\\"\")");
                                                            #line 179 "CodeGeneratorScala.cpp.template"
                                                                }
                                                            #line 286 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"\n");
  append(L"    while (code != 0) {\n");
  append(L"      var charclass = -1\n");
  append(L"      var c0: Int = if (current < ");
                                                            #line 184 "CodeGeneratorScala.cpp.template"
                                                                if (variable("useGlr").boolean())
                                                                {
                                                            #line 295 "CodeGeneratorScala.cpp"
  append(L"parser.");
                                                            #line 186 "CodeGeneratorScala.cpp.template"
                                                                }
                                                            #line 299 "CodeGeneratorScala.cpp"
  append(L"size) ");
                                                            #line 187 "CodeGeneratorScala.cpp.template"
                                                                if (variable("useGlr").boolean())
                                                                {
                                                            #line 304 "CodeGeneratorScala.cpp"
  append(L"parser.");
                                                            #line 189 "CodeGeneratorScala.cpp.template"
                                                                }
                                                            #line 308 "CodeGeneratorScala.cpp"
  append(L"input(current) else 0");
                                                            #line 191 "CodeGeneratorScala.cpp.template"
                                                                if (variable("trace").boolean())
                                                                {
                                                            #line 313 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"      ");
                                                            #line 194 "CodeGeneratorScala.cpp.template"
                                                                    if (variable("useGlr").boolean())
                                                                  {
                                                            #line 319 "CodeGeneratorScala.cpp"
  append(L"parser.");
                                                            #line 196 "CodeGeneratorScala.cpp.template"
                                                                  }
                                                            #line 323 "CodeGeneratorScala.cpp"
  append(L"writeTrace(\" offset=\\\"\" + current + \"\\\"\")");
                                                            #line 197 "CodeGeneratorScala.cpp.template"
                                                                }
                                                            #line 327 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"      current += 1\n");
  append(L"      if (c0 < 0x");
                                                            #line 200 "CodeGeneratorScala.cpp.template"
                                                                print(format.toString<char>(variable("simplifiedCodeMap").integer(), 16, 0, 0, 0, "0123456789abcdef"));
                                                            #line 333 "CodeGeneratorScala.cpp"
  append(L") {");
                                                            #line 201 "CodeGeneratorScala.cpp.template"
                                                                if (variable("trace").boolean())
                                                                {
                                                            #line 338 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"        if (c0 >= 32 && c0 <= 126)\n");
  append(L"          ");
                                                            #line 205 "CodeGeneratorScala.cpp.template"
                                                                  if (variable("useGlr").boolean())
                                                                  {
                                                            #line 345 "CodeGeneratorScala.cpp"
  append(L"parser.");
                                                            #line 207 "CodeGeneratorScala.cpp.template"
                                                                  }
                                                            #line 349 "CodeGeneratorScala.cpp"
  append(L"writeTrace(\" char=\\\"\" + ");
                                                            #line 208 "CodeGeneratorScala.cpp.template"
                                                                  print(variable("classname").string());
                                                            #line 353 "CodeGeneratorScala.cpp"
  append(L".xmlEscape(");
                                                            #line 209 "CodeGeneratorScala.cpp.template"
                                                                  if (variable("useGlr").boolean())
                                                                  {
                                                            #line 358 "CodeGeneratorScala.cpp"
  append(L"parser.");
                                                            #line 211 "CodeGeneratorScala.cpp.template"
                                                                  }
                                                            #line 362 "CodeGeneratorScala.cpp"
  append(L"input.substring(current - 1, current)) + \"\\\"\")");
                                                            #line 213 "CodeGeneratorScala.cpp.template"
                                                                }
                                                            #line 366 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"        charclass = ");
                                                            #line 215 "CodeGeneratorScala.cpp.template"
                                                                print(variable("classname").string());
                                                            #line 371 "CodeGeneratorScala.cpp"
  append(L".MAP0(c0)\n");
  append(L"      }\n");
  append(L"      else if (c0 < 0x");
                                                            #line 218 "CodeGeneratorScala.cpp.template"
                                                                print(format.toString<char>(variable("uncompressedMapSize").integer(), 16, 0, 0, 0, "0123456789abcdef"));
                                                            #line 377 "CodeGeneratorScala.cpp"
  append(L") {\n");
                                                            #line 220 "CodeGeneratorScala.cpp.template"
                                                                CString map1(variable("classname").string());
                                                                map1 += ".MAP1";
                                                                compressedMapAccessor(8, "c", "charclass = ", map1.c_str(), &variable("m1bits").integer());
                                                            #line 383 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"      }\n");
  append(L"      else {");
                                                            #line 225 "CodeGeneratorScala.cpp.template"
                                                                if (variable("m2").size == 0)
                                                                {
                                                            #line 390 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"        charclass = 0");
                                                            #line 228 "CodeGeneratorScala.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 397 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"        if (");
                                                            #line 232 "CodeGeneratorScala.cpp.template"
                                                                  if (variable("uncompressedMapSize").integer() != 0xd800)
                                                                  {
                                                            #line 403 "CodeGeneratorScala.cpp"
  append(L"c0 >= 0xd800 && ");
                                                            #line 234 "CodeGeneratorScala.cpp.template"
                                                                  }
                                                            #line 407 "CodeGeneratorScala.cpp"
  append(L"c0 < 0xdc00) {\n");
  append(L"          val c1 = if (current < ");
                                                            #line 236 "CodeGeneratorScala.cpp.template"
                                                                  if (variable("useGlr").boolean())
                                                                  {
                                                            #line 413 "CodeGeneratorScala.cpp"
  append(L"parser.");
                                                            #line 238 "CodeGeneratorScala.cpp.template"
                                                                  }
                                                            #line 417 "CodeGeneratorScala.cpp"
  append(L"size) ");
                                                            #line 239 "CodeGeneratorScala.cpp.template"
                                                                  if (variable("useGlr").boolean())
                                                                  {
                                                            #line 422 "CodeGeneratorScala.cpp"
  append(L"parser.");
                                                            #line 241 "CodeGeneratorScala.cpp.template"
                                                                  }
                                                            #line 426 "CodeGeneratorScala.cpp"
  append(L"input(current) else 0\n");
  append(L"          if (c1 >= 0xdc00 && c1 < 0xe000) {");
                                                            #line 243 "CodeGeneratorScala.cpp.template"
                                                                  if (lookahead)
                                                                  {
                                                            #line 432 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"            nonbmp = true");
                                                            #line 246 "CodeGeneratorScala.cpp.template"
                                                                  }
                                                            #line 437 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"            current += 1\n");
  append(L"            c0 = ((c0 & 0x3ff) << 10) + (c1 & 0x3ff) + 0x10000\n");
  append(L"          }\n");
  append(L"        }\n");
                                                            #line 253 "CodeGeneratorScala.cpp.template"
/*
 * tail recursive variant of MAP2 access
 *
        def binarySearch(lo: Int, hi: Int): Int = {
          if (lo > hi)
            0
          else {
            val m = (hi + lo) >> 1
            if (
                                                            #line 453 "CodeGeneratorScala.cpp"
  append(L"                                                 print(variable(\"classname\").string());\n");
  append(L"                ");
                                                            #line 262 "CodeGeneratorScala.cpp.template"
                 .MAP2(m) > c0) binarySearch(lo, m - 1)
            else if (
                                                            #line 459 "CodeGeneratorScala.cpp"
  append(L"                                            print(variable(\"classname\").string());\n");
  append(L"                     ");
                                                            #line 264 "CodeGeneratorScala.cpp.template"
                      .MAP2(2 + m) < c0) binarySearch(m + 1, hi)
            else
                                                            #line 465 "CodeGeneratorScala.cpp"
  append(L"                                                print(variable(\"classname\").string());\n");
  append(L"                 ");
                                                            #line 266 "CodeGeneratorScala.cpp.template"
                  .MAP2(4 + m)
          }
        }

        charclass = binarySearch(0,
                                                            #line 474 "CodeGeneratorScala.cpp"
  append(L"                             print(variable(\"classname\").string());\n");
  append(L"                                    ");
                                                            #line 271 "CodeGeneratorScala.cpp.template"
                                     .MAP2.length)
 */
                                                            #line 480 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"        var lo = 0\n");
  append(L"        var hi = ");
                                                            #line 275 "CodeGeneratorScala.cpp.template"
                                                                  print(variable("m2").size / 3 - 1);
                                                            #line 486 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"        var m = ");
                                                            #line 277 "CodeGeneratorScala.cpp.template"
                                                                  print((variable("m2").size / 3) >> 1);
                                                            #line 491 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"        while (charclass < 0) {\n");
  append(L"          if (");
                                                            #line 280 "CodeGeneratorScala.cpp.template"
                                                                  print(variable("classname").string());
                                                            #line 497 "CodeGeneratorScala.cpp"
  append(L".MAP2(m) > c0) hi = m - 1\n");
  append(L"          else if (");
                                                            #line 282 "CodeGeneratorScala.cpp.template"
                                                                  print(variable("classname").string());
                                                            #line 502 "CodeGeneratorScala.cpp"
  append(L".MAP2(");
                                                            #line 283 "CodeGeneratorScala.cpp.template"
                                                                  print(variable("m2").size / 3);
                                                            #line 506 "CodeGeneratorScala.cpp"
  append(L" + m) < c0) lo = m + 1\n");
  append(L"          else charclass = ");
                                                            #line 285 "CodeGeneratorScala.cpp.template"
                                                                  print(variable("classname").string());
                                                            #line 511 "CodeGeneratorScala.cpp"
  append(L".MAP2(");
                                                            #line 286 "CodeGeneratorScala.cpp.template"
                                                                  print(variable("m2").size / 3 * 2);
                                                            #line 515 "CodeGeneratorScala.cpp"
  append(L" + m)\n");
  append(L"          if (lo > hi) charclass = 0 else m = (hi + lo) >> 1\n");
  append(L"        }");
                                                            #line 289 "CodeGeneratorScala.cpp.template"
                                                                }
                                                            #line 521 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"      }");
                                                            #line 291 "CodeGeneratorScala.cpp.template"
                                                                if (variable("trace").boolean())
                                                                {
                                                            #line 527 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"      ");
                                                            #line 294 "CodeGeneratorScala.cpp.template"
                                                                    if (variable("useGlr").boolean())
                                                                  {
                                                            #line 533 "CodeGeneratorScala.cpp"
  append(L"parser.");
                                                            #line 296 "CodeGeneratorScala.cpp.template"
                                                                  }
                                                            #line 537 "CodeGeneratorScala.cpp"
  append(L"writeTrace(\" codepoint=\\\"\" + c0 + \"\\\" class=\\\"\" + charclass + \"\\\"\")");
                                                            #line 298 "CodeGeneratorScala.cpp.template"
                                                                }
                                                            #line 541 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"\n");
  append(L"      state = code\n");
                                                            #line 302 "CodeGeneratorScala.cpp.template"
                                                                CString transition(variable("classname").string());
                                                                transition += ".TRANSITION";
                                                                compressedMap2dAccessor("code - 1", "charclass", variable("a1cols").integer(),
                                                                                           6, "i", "code = ", transition.c_str(), &variable("a1bits").integer());
                                                            #line 550 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"\n");
  append(L"      if (code > ");
                                                            #line 308 "CodeGeneratorScala.cpp.template"
                                                                print(Math::powerof(2, variable("stateCodeBits").integer()) - 1);
                                                            #line 556 "CodeGeneratorScala.cpp"
  append(L") {\n");
  append(L"        result = code");
                                                            #line 310 "CodeGeneratorScala.cpp.template"
                                                                if (variable("trace").boolean())
                                                                {
                                                            #line 562 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"        ");
                                                            #line 313 "CodeGeneratorScala.cpp.template"
                                                                      if (variable("useGlr").boolean())
                                                                  {
                                                            #line 568 "CodeGeneratorScala.cpp"
  append(L"parser.");
                                                            #line 315 "CodeGeneratorScala.cpp.template"
                                                                  }
                                                            #line 572 "CodeGeneratorScala.cpp"
  append(L"writeTrace(\" result=\\\"\" + ");
                                                            #line 316 "CodeGeneratorScala.cpp.template"
                                                                  print(variable("classname").string());
                                                            #line 576 "CodeGeneratorScala.cpp"
  append(L".xmlEscape(");
                                                            #line 317 "CodeGeneratorScala.cpp.template"
                                                                  print(variable("classname").string());
                                                            #line 580 "CodeGeneratorScala.cpp"
  append(L".TOKEN(((result >> ");
                                                            #line 318 "CodeGeneratorScala.cpp.template"
                                                                  print(variable("stateCodeBits").integer());
                                                            #line 584 "CodeGeneratorScala.cpp"
  append(L") & ");
                                                            #line 319 "CodeGeneratorScala.cpp.template"
                                                                  print(Math::powerof(2, variable("tokencodeBits").integer()) - 1);
                                                            #line 588 "CodeGeneratorScala.cpp"
  append(L") - 1)) + \"\\\"\")");
                                                            #line 321 "CodeGeneratorScala.cpp.template"
                                                                  if (lookahead || hasFixedTokenLength)
                                                                  {
                                                                    int contextOffset = variable("stateCodeBits").integer()
                                                                                      + variable("tokencodeBits").integer();
                                                                    int sizeOffset = contextOffset
                                                                                   + (hasFixedTokenLength ? 1 : 0);
                                                                    if (hasFixedTokenLength)
                                                                    {
                                                            #line 599 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"        if ((result & ");
                                                            #line 330 "CodeGeneratorScala.cpp.template"
                                                                      print(Math::powerof(2, contextOffset));
                                                            #line 604 "CodeGeneratorScala.cpp"
  append(L") > 0) {\n");
  append(L"          ");
                                                            #line 332 "CodeGeneratorScala.cpp.template"
                                                                      if (variable("useGlr").boolean())
                                                                      {
                                                            #line 610 "CodeGeneratorScala.cpp"
  append(L"parser.");
                                                            #line 334 "CodeGeneratorScala.cpp.template"
                                                                      }
                                                            #line 614 "CodeGeneratorScala.cpp"
  append(L"writeTrace(\" token-size=\\\"\" + (result >> ");
                                                            #line 335 "CodeGeneratorScala.cpp.template"
                                                                      print(sizeOffset);
                                                            #line 618 "CodeGeneratorScala.cpp"
  append(L") + \"\\\"\")\n");
  append(L"        }\n");
  append(L"        else ");
                                                            #line 338 "CodeGeneratorScala.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 626 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"        ");
                                                            #line 342 "CodeGeneratorScala.cpp.template"
                                                                    }
                                                            #line 631 "CodeGeneratorScala.cpp"
  append(L"if ((result >> ");
                                                            #line 343 "CodeGeneratorScala.cpp.template"
                                                                    print(sizeOffset);
                                                            #line 635 "CodeGeneratorScala.cpp"
  append(L") > 0) {\n");
  append(L"          ");
                                                            #line 345 "CodeGeneratorScala.cpp.template"
                                                                    if (variable("useGlr").boolean())
                                                                    {
                                                            #line 641 "CodeGeneratorScala.cpp"
  append(L"parser.");
                                                            #line 347 "CodeGeneratorScala.cpp.template"
                                                                    }
                                                            #line 645 "CodeGeneratorScala.cpp"
  append(L"writeTrace(\" trailing-context-size=\\\"\" + (result >> ");
                                                            #line 348 "CodeGeneratorScala.cpp.template"
                                                                     print(sizeOffset);
                                                            #line 649 "CodeGeneratorScala.cpp"
  append(L") + \"\\\"\")\n");
  append(L"        }");
                                                            #line 350 "CodeGeneratorScala.cpp.template"
                                                                  }
                                                                }
                                                            #line 655 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"        code &= ");
                                                            #line 353 "CodeGeneratorScala.cpp.template"
                                                                print(Math::powerof(2, variable("stateCodeBits").integer()) - 1);
                                                            #line 660 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"        end = current\n");
  append(L"      }");
                                                            #line 356 "CodeGeneratorScala.cpp.template"
                                                                if (variable("trace").boolean())
                                                                {
                                                            #line 667 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"      ");
                                                            #line 359 "CodeGeneratorScala.cpp.template"
                                                                  if (variable("useGlr").boolean())
                                                                  {
                                                            #line 673 "CodeGeneratorScala.cpp"
  append(L"parser.");
                                                            #line 361 "CodeGeneratorScala.cpp.template"
                                                                  }
                                                            #line 677 "CodeGeneratorScala.cpp"
  append(L"writeTrace(\"/>\\n\")\n");
  append(L"      if (code != 0) {\n");
  append(L"        ");
                                                            #line 364 "CodeGeneratorScala.cpp.template"
                                                                  if (variable("useGlr").boolean())
                                                                  {
                                                            #line 684 "CodeGeneratorScala.cpp"
  append(L"parser.");
                                                            #line 366 "CodeGeneratorScala.cpp.template"
                                                                  }
                                                            #line 688 "CodeGeneratorScala.cpp"
  append(L"writeTrace(\"    <next state=\\\"\" + code + \"\\\"\")\n");
  append(L"      }");
                                                            #line 368 "CodeGeneratorScala.cpp.template"
                                                                }
                                                            #line 693 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    result >>= ");
                                                            #line 372 "CodeGeneratorScala.cpp.template"
                                                                print(variable("stateCodeBits").integer());
                                                            #line 700 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"    if (result == 0) {\n");
  append(L"      end = current - 1\n");
  append(L"      val c1 = if (end < ");
                                                            #line 376 "CodeGeneratorScala.cpp.template"
                                                                if (variable("useGlr").boolean())
                                                                {
                                                            #line 708 "CodeGeneratorScala.cpp"
  append(L"parser.");
                                                            #line 378 "CodeGeneratorScala.cpp.template"
                                                                }
                                                            #line 712 "CodeGeneratorScala.cpp"
  append(L"size) ");
                                                            #line 379 "CodeGeneratorScala.cpp.template"
                                                                if (variable("useGlr").boolean())
                                                                {
                                                            #line 717 "CodeGeneratorScala.cpp"
  append(L"parser.");
                                                            #line 381 "CodeGeneratorScala.cpp.template"
                                                                }
                                                            #line 721 "CodeGeneratorScala.cpp"
  append(L"input(end) else 0\n");
  append(L"      if (c1 >= 0xdc00 && c1 < 0xe000) {\n");
  append(L"        end -= 1\n");
  append(L"      }");
                                                            #line 385 "CodeGeneratorScala.cpp.template"
                                                                if (variable("trace").boolean())
                                                                {
                                                            #line 729 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"      ");
                                                            #line 388 "CodeGeneratorScala.cpp.template"
                                                                  if (variable("useGlr").boolean())
                                                                  {
                                                            #line 735 "CodeGeneratorScala.cpp"
  append(L"parser.");
                                                            #line 390 "CodeGeneratorScala.cpp.template"
                                                                  }
                                                            #line 739 "CodeGeneratorScala.cpp"
  append(L"writeTrace(\"    <fail begin=\\\"\" + begin + \"\\\" end=\\\"\" + end + \"\\\" state=\\\"\" + state + \"\\\"/>\\n\")\n");
  append(L"      ");
                                                            #line 392 "CodeGeneratorScala.cpp.template"
                                                                  if (variable("useGlr").boolean())
                                                                  {
                                                            #line 745 "CodeGeneratorScala.cpp"
  append(L"parser.");
                                                            #line 394 "CodeGeneratorScala.cpp.template"
                                                                  }
                                                            #line 749 "CodeGeneratorScala.cpp"
  append(L"writeTrace(\"  </tokenize>\\n\")");
                                                            #line 395 "CodeGeneratorScala.cpp.template"
                                                                }
                                                                if (variable("embedded").boolean())
                                                                {
                                                                  if (variable("useGlr").boolean())
                                                                  {
                                                            #line 757 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"      end = begin\n");
  append(L"      -1");
                                                            #line 402 "CodeGeneratorScala.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 765 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"      error(begin, end, state, -1, -1)");
                                                            #line 406 "CodeGeneratorScala.cpp.template"
                                                                  }
                                                                }
                                                            #line 771 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"    }\n");
  append(L"    else {");
                                                            #line 410 "CodeGeneratorScala.cpp.template"
                                                                int lowBits = variable("tokencodeBits").integer();
                                                                if (hasFixedTokenLength && ! lookahead)
                                                                {
                                                            #line 779 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"      if ((result & ");
                                                            #line 414 "CodeGeneratorScala.cpp.template"
                                                                  print(Math::powerof(2, lowBits));
                                                                  ++lowBits;
                                                            #line 785 "CodeGeneratorScala.cpp"
  append(L") != 0) {\n");
  append(L"        end = begin\n");
  append(L"      }");
                                                            #line 418 "CodeGeneratorScala.cpp.template"
                                                                }
                                                                else
                                                                {
                                                                  if (hasFixedTokenLength)
                                                                  {
                                                            #line 795 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"      if ((result & ");
                                                            #line 424 "CodeGeneratorScala.cpp.template"
                                                                    print(Math::powerof(2, lowBits));
                                                                    ++lowBits;
                                                            #line 801 "CodeGeneratorScala.cpp"
  append(L") != 0) {\n");
  append(L"        end = begin\n");
  append(L"        if (nonbmp) {\n");
  append(L"          var i = result >> ");
                                                            #line 429 "CodeGeneratorScala.cpp.template"
                                                                    print(lowBits);
                                                            #line 808 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"          while (i > 0) {\n");
  append(L"            val c1 = if (end < ");
                                                            #line 432 "CodeGeneratorScala.cpp.template"
                                                                    if (variable("useGlr").boolean())
                                                                    {
                                                            #line 815 "CodeGeneratorScala.cpp"
  append(L"parser.");
                                                            #line 434 "CodeGeneratorScala.cpp.template"
                                                                    }
                                                            #line 819 "CodeGeneratorScala.cpp"
  append(L"size) ");
                                                            #line 435 "CodeGeneratorScala.cpp.template"
                                                                    if (variable("useGlr").boolean())
                                                                    {
                                                            #line 824 "CodeGeneratorScala.cpp"
  append(L"parser.");
                                                            #line 437 "CodeGeneratorScala.cpp.template"
                                                                    }
                                                            #line 828 "CodeGeneratorScala.cpp"
  append(L"input(end) else 0\n");
  append(L"            end += 1\n");
  append(L"            if (c1 >= 0xd800 && c1 < 0xdc000) {\n");
  append(L"              end += 1\n");
  append(L"            }\n");
  append(L"            i -= 1\n");
  append(L"          }\n");
  append(L"        }\n");
  append(L"        else {\n");
  append(L"          end += (result >> ");
                                                            #line 447 "CodeGeneratorScala.cpp.template"
                                                                    print(lowBits);
                                                            #line 841 "CodeGeneratorScala.cpp"
  append(L")\n");
  append(L"        }\n");
  append(L"      }");
                                                            #line 450 "CodeGeneratorScala.cpp.template"
                                                                  }
                                                                  if (lookahead)
                                                                  {
                                                            #line 849 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"      if (nonbmp) {\n");
  append(L"        var i = result >> ");
                                                            #line 455 "CodeGeneratorScala.cpp.template"
                                                                    print(lowBits);
                                                            #line 855 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"        while (i > 0) {\n");
  append(L"          end -= 1\n");
  append(L"          val c1 = if (end < ");
                                                            #line 459 "CodeGeneratorScala.cpp.template"
                                                                    if (variable("useGlr").boolean())
                                                                    {
                                                            #line 863 "CodeGeneratorScala.cpp"
  append(L"parser.");
                                                            #line 461 "CodeGeneratorScala.cpp.template"
                                                                    }
                                                            #line 867 "CodeGeneratorScala.cpp"
  append(L"size) ");
                                                            #line 462 "CodeGeneratorScala.cpp.template"
                                                                    if (variable("useGlr").boolean())
                                                                    {
                                                            #line 872 "CodeGeneratorScala.cpp"
  append(L"parser.");
                                                            #line 464 "CodeGeneratorScala.cpp.template"
                                                                    }
                                                            #line 876 "CodeGeneratorScala.cpp"
  append(L"input(end) else 0\n");
  append(L"          if (c1 >= 0xdc00 && c1 < 0xe000) {\n");
  append(L"            end -= 1\n");
  append(L"          }\n");
  append(L"          i -= 1\n");
  append(L"        }\n");
  append(L"      }\n");
  append(L"      else {\n");
  append(L"        end -= result >> ");
                                                            #line 473 "CodeGeneratorScala.cpp.template"
                                                                    print(lowBits);
                                                            #line 888 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"      }");
                                                            #line 475 "CodeGeneratorScala.cpp.template"
                                                                  }
                                                                }
                                                            #line 894 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"      if (end > ");
                                                            #line 478 "CodeGeneratorScala.cpp.template"
                                                                if (variable("useGlr").boolean())
                                                                {
                                                            #line 900 "CodeGeneratorScala.cpp"
  append(L"parser.");
                                                            #line 480 "CodeGeneratorScala.cpp.template"
                                                                }
                                                            #line 904 "CodeGeneratorScala.cpp"
  append(L"size) end = ");
                                                            #line 481 "CodeGeneratorScala.cpp.template"
                                                                if (variable("useGlr").boolean())
                                                                {
                                                            #line 909 "CodeGeneratorScala.cpp"
  append(L"parser.");
                                                            #line 483 "CodeGeneratorScala.cpp.template"
                                                                }
                                                            #line 913 "CodeGeneratorScala.cpp"
  append(L"size");
                                                            #line 484 "CodeGeneratorScala.cpp.template"
                                                                if (variable("trace").boolean())
                                                                {
                                                            #line 918 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"      ");
                                                            #line 487 "CodeGeneratorScala.cpp.template"
                                                                  if (variable("useGlr").boolean())
                                                                  {
                                                            #line 924 "CodeGeneratorScala.cpp"
  append(L"parser.");
                                                            #line 489 "CodeGeneratorScala.cpp.template"
                                                                  }
                                                            #line 928 "CodeGeneratorScala.cpp"
  append(L"writeTrace(\"    <done result=\\\"\" + ");
                                                            #line 490 "CodeGeneratorScala.cpp.template"
                                                                   print(variable("classname").string());
                                                            #line 932 "CodeGeneratorScala.cpp"
  append(L".xmlEscape(");
                                                            #line 491 "CodeGeneratorScala.cpp.template"
                                                                  print(variable("classname").string());
                                                            #line 936 "CodeGeneratorScala.cpp"
  append(L".TOKEN((result & ");
                                                            #line 492 "CodeGeneratorScala.cpp.template"
                                                                  print(Math::powerof(2, variable("tokencodeBits").integer()) - 1);
                                                            #line 940 "CodeGeneratorScala.cpp"
  append(L") - 1)) + \"\\\" begin=\\\"\" + begin + \"\\\" end=\\\"\" + end + \"\\\"/>\\n\")\n");
  append(L"      ");
                                                            #line 494 "CodeGeneratorScala.cpp.template"
                                                                  if (variable("useGlr").boolean())
                                                                  {
                                                            #line 946 "CodeGeneratorScala.cpp"
  append(L"parser.");
                                                            #line 496 "CodeGeneratorScala.cpp.template"
                                                                  }
                                                            #line 950 "CodeGeneratorScala.cpp"
  append(L"writeTrace(\"  </tokenize>\\n\")");
                                                            #line 497 "CodeGeneratorScala.cpp.template"
                                                                }
                                                                const char *flags = getenv("FLAGS");
                                                                bool hack = flags && strchr(flags, 'H');
                                                                if (hack)
                                                                {
                                                            #line 958 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"      hack((result & ");
                                                            #line 503 "CodeGeneratorScala.cpp.template"
                                                                  print(Math::powerof(2, variable("tokencodeBits").integer()) - 1);
                                                            #line 963 "CodeGeneratorScala.cpp"
  append(L") - 1)\n");
  append(L"    }\n");
                                                            #line 506 "CodeGeneratorScala.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 970 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"      (result & ");
                                                            #line 510 "CodeGeneratorScala.cpp.template"
                                                                  print(Math::powerof(2, variable("tokencodeBits").integer()) - 1);
                                                            #line 975 "CodeGeneratorScala.cpp"
  append(L") - 1\n");
  append(L"    }\n");
  append(L"  }\n");
                                                            #line 514 "CodeGeneratorScala.cpp.template"
                                                                }
                                                              }
                                                              if (! variable("embedded").boolean())
                                                              {
                                                            #line 984 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"  public String[] getExpectedTokenSet()\n");
  append(L"  {\n");
  append(L"    return getTokenSet(- state);\n");
  append(L"  }\n");
                                                            #line 523 "CodeGeneratorScala.cpp.template"
                                                              }
                                                            #line 992 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"  var begin = 0\n");
  append(L"  var end = 0\n");
                                                            #line 527 "CodeGeneratorScala.cpp.template"
                                                            }

                                                            void CodeGeneratorScala::generateStaticCode()
                                                            {
                                                              isScala = true;
                                                              if (defined("gtbits"))
                                                              {
                                                            #line 1004 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"  private def goTo(nonterminal: Int, state: Int): Int = {\n");
                                                            #line 537 "CodeGeneratorScala.cpp.template"
                                                                CString goTo(variable("classname").string());
                                                                goTo += ".GOTO";
                                                                compressedMap2dAccessor("nonterminal", "state", variable("gtcols").integer(),
                                                                                           4, "i", "", goTo.c_str(), &variable("gtbits").integer());
                                                            #line 1012 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"  }\n");
                                                            #line 543 "CodeGeneratorScala.cpp.template"
                                                              }
                                                              if (variable("trace").boolean())
                                                              {
                                                            #line 1019 "CodeGeneratorScala.cpp"
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
                                                            #line 560 "CodeGeneratorScala.cpp.template"
                                                              }
                                                              if (variable("nolexer").boolean())
                                                              {
                                                            #line 1038 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"  public static int getTokenCount() {return ");
                                                            #line 564 "CodeGeneratorScala.cpp.template"
                                                                print(variable("t1").size);
                                                            #line 1043 "CodeGeneratorScala.cpp"
  append(L";}\n");
  append(L"  public static String getTokenName(int code) {return code >= 0 && code < ");
                                                            #line 567 "CodeGeneratorScala.cpp.template"
                                                                print(variable("t1").size);
                                                            #line 1048 "CodeGeneratorScala.cpp"
  append(L" ? TOKEN[code] : null;}\n");
  append(L"  public static int getTokenSetCount() {return ");
                                                            #line 569 "CodeGeneratorScala.cpp.template"
                                                                print(variable("entrycount").integer());
                                                            #line 1053 "CodeGeneratorScala.cpp"
  append(L";}\n");
  append(L"\n");
  append(L"  public static String[] getTokenSet(int tokenSetId) {");
                                                            #line 572 "CodeGeneratorScala.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 1061 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"  private def getTokenSet(tokenSetId: Int) = {");
                                                            #line 576 "CodeGeneratorScala.cpp.template"
                                                              }
                                                            #line 1066 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"    var expected = ArrayBuffer[String]()");
                                                            #line 578 "CodeGeneratorScala.cpp.template"
                                                              if (! variable("nolexer").boolean())
                                                              {
                                                            #line 1072 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"    val s = if (tokenSetId < 0) - tokenSetId else INITIAL(tokenSetId) & ");
                                                            #line 582 "CodeGeneratorScala.cpp.template"
                                                                print(Math::powerof(2, variable("stateCodeBits").integer()) - 1);
                                                              }
                                                            #line 1078 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"    var i = 0\n");
  append(L"    while (i < ");
                                                            #line 586 "CodeGeneratorScala.cpp.template"
                                                              print(variable("t1").size);
                                                            #line 1084 "CodeGeneratorScala.cpp"
  append(L") {\n");
  append(L"      var j = i\n");
  append(L"      val i0 = (i >> 5) * ");
                                                            #line 589 "CodeGeneratorScala.cpp.template"
                                                              print(variable("transitionStateCount").integer());
                                                            #line 1090 "CodeGeneratorScala.cpp"
  append(L" + ");
                                                            #line 590 "CodeGeneratorScala.cpp.template"
                                                              if (variable("nolexer").boolean())
                                                              {
                                                            #line 1095 "CodeGeneratorScala.cpp"
  append(L"tokenSetId");
                                                            #line 592 "CodeGeneratorScala.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 1101 "CodeGeneratorScala.cpp"
  append(L"s - 1");
                                                            #line 595 "CodeGeneratorScala.cpp.template"
                                                              }
                                                            #line 1105 "CodeGeneratorScala.cpp"
  append(L"\n");
                                                            #line 598 "CodeGeneratorScala.cpp.template"
                                                              compressedMapAccessor(6, "i", "var f = ", "EXPECTED", &variable("t0bits").integer());
                                                            #line 1109 "CodeGeneratorScala.cpp"
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
                                                            #line 610 "CodeGeneratorScala.cpp.template"
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
                                                            #line 1141 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"\n");
  append(L"  private final val ");
                                                            #line 630 "CodeGeneratorScala.cpp.template"
                                                                print(a->longName);
                                                            #line 1147 "CodeGeneratorScala.cpp"
  append(L" = Array(");
                                                            #line 632 "CodeGeneratorScala.cpp.template"
                                                                int w = (int) Format::width(a->size);
                                                                for (size_t j = 0; j < a->size; ++j)
                                                                {
                                                                  if (j == 0 || lineLength() + Format::width(a->integer(j)) + (asString ? 3 : 2) > limit)
                                                                  {
                                                                    if (j) print(asString ? "\"," : ",");
                                                            #line 1156 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"    /* ");
                                                            #line 639 "CodeGeneratorScala.cpp.template"
                                                                    print(format.toString<char>(j, 10, w));
                                                            #line 1161 "CodeGeneratorScala.cpp"
  append(L" */ ");
                                                            #line 640 "CodeGeneratorScala.cpp.template"
                                                                    if (asString) print("\"");
                                                                  }
                                                                  else
                                                                  {
                                                            #line 1168 "CodeGeneratorScala.cpp"
  append(L", ");
                                                            #line 644 "CodeGeneratorScala.cpp.template"
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
                                                            #line 1183 "CodeGeneratorScala.cpp"
  append(L"\"\n");
  append(L"  ).flatMap(_.split(\", \").map(_.toInt))");
                                                            #line 657 "CodeGeneratorScala.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1190 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"  )");
                                                            #line 661 "CodeGeneratorScala.cpp.template"
                                                                }
                                                              }
                                                              for (VarsInInsertionOrder::iterator a(varsInInsertionOrder.begin());
                                                                   a != varsInInsertionOrder.end(); ++a)
                                                                if (a->isArray() && a->size > 0 && a->hasType(CGVariable::STRING) && strlen(a->name) == 2)
                                                              {
                                                            #line 1200 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"\n");
  append(L"  private final val ");
                                                            #line 669 "CodeGeneratorScala.cpp.template"
                                                                print(a->longName);
                                                            #line 1206 "CodeGeneratorScala.cpp"
  append(L" = Array(\n");
                                                            #line 671 "CodeGeneratorScala.cpp.template"
                                                                for (size_t j = 0; j < a->size; ++j)
                                                                {
                                                                  if (j)
                                                                  {
                                                            #line 1213 "CodeGeneratorScala.cpp"
  append(L",\n");
                                                            #line 676 "CodeGeneratorScala.cpp.template"
                                                                  }
                                                            #line 1217 "CodeGeneratorScala.cpp"
  append(L"    \"");
                                                            #line 677 "CodeGeneratorScala.cpp.template"
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
                                                            #line 1232 "CodeGeneratorScala.cpp"
  append(L"\"");
                                                            #line 689 "CodeGeneratorScala.cpp.template"
                                                                }
                                                            #line 1236 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"  )");
                                                            #line 691 "CodeGeneratorScala.cpp.template"
                                                             }
                                                              if (! variable("embedded").boolean())
                                                              {
                                                            #line 1243 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"\n");
  append(L"  public enum Token\n");
  append(L"  {\n");
  append(L"    ");
                                                            #line 698 "CodeGeneratorScala.cpp.template"
                                                                const CGVariable &token = variable("token");
                                                                int w = (int) Format::width(token.size);
                                                                for (size_t i = 0; i < token.size; ++i)
                                                                {
                                                                  if (i)
                                                                  {
                                                            #line 1256 "CodeGeneratorScala.cpp"
  append(L",\n");
  append(L"    ");
                                                            #line 705 "CodeGeneratorScala.cpp.template"
                                                                  }
                                                            #line 1261 "CodeGeneratorScala.cpp"
  append(L"/* ");
                                                            #line 706 "CodeGeneratorScala.cpp.template"
                                                                  print(format.toString<char>(i, 10, w));
                                                            #line 1265 "CodeGeneratorScala.cpp"
  append(L" */ ");
                                                            #line 707 "CodeGeneratorScala.cpp.template"
                                                                  print(token.string(i));
                                                                }
                                                            #line 1270 "CodeGeneratorScala.cpp"
  append(L"\n");
  append(L"  };");
                                                            #line 711 "CodeGeneratorScala.cpp.template"
                                                              }
                                                              if (variable("selfTest").boolean())
                                                              {
                                                            #line 1277 "CodeGeneratorScala.cpp"
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
                                                            #line 749 "CodeGeneratorScala.cpp.template"
                                                              print(variable("classname").string());
                                                            #line 1316 "CodeGeneratorScala.cpp"
  append(L" testee = new ");
                                                            #line 750 "CodeGeneratorScala.cpp.template"
                                                              print(variable("classname").string());
                                                            #line 1320 "CodeGeneratorScala.cpp"
  append(L"();\n");
  append(L"    for (int e = 0; e < ");
                                                            #line 752 "CodeGeneratorScala.cpp.template"
                                                              print(variable("a0").size);
                                                            #line 1325 "CodeGeneratorScala.cpp"
  append(L"; ++e)\n");
  append(L"    {\n");
  append(L"      int s = INITIAL[e] & ");
                                                            #line 755 "CodeGeneratorScala.cpp.template"
                                                              print(Math::powerof(2, variable("stateCodeBits").integer()) - 1);
                                                            #line 1331 "CodeGeneratorScala.cpp"
  append(L";\n");
  append(L"      for (int i = 0; i < ");
                                                            #line 757 "CodeGeneratorScala.cpp.template"
                                                              print(variable("t1").size);
                                                            #line 1336 "CodeGeneratorScala.cpp"
  append(L"; i += 32)\n");
  append(L"      {\n");
  append(L"        int j = i;\n");
  append(L"        int i0 = (i >> 5) * ");
                                                            #line 761 "CodeGeneratorScala.cpp.template"
                                                              print(variable("transitionStateCount").integer());
                                                            #line 1343 "CodeGeneratorScala.cpp"
  append(L" + s - 1;\n");
                                                            #line 763 "CodeGeneratorScala.cpp.template"
                                                              compressedMapAccessor(8, "i", "int f = ", "EXPECTED", &variable("t0bits").integer());
                                                            #line 1347 "CodeGeneratorScala.cpp"
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
                                                            #line 774 "CodeGeneratorScala.cpp.template"
                                                              }
                                                            #line 1361 "CodeGeneratorScala.cpp"
  append(L"\n");
                                                            #line 776 "CodeGeneratorScala.cpp.template"
                                                              if (! variable("embedded").boolean())
                                                              {
                                                            #line 1366 "CodeGeneratorScala.cpp"
  append(L"}\n");
                                                            #line 779 "CodeGeneratorScala.cpp.template"
                                                              }
                                                            }

                                                            void CodeGeneratorScala::generateData()
                                                            {
                                                            }

// End
