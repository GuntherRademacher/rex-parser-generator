// This file was generated on Sun Nov 24, 2024 16:09 (UTC+01) by REx v6.0 which is Copyright (c) 1979-2024 by Gunther Rademacher <grd@gmx.net>
// REx command line: CodeGeneratorCpp.cpp.template
                                                            #line 1 "CodeGeneratorCpp.cpp.template"
                                                            #include "../common/Memory.hpp"
                                                            #include "../common/Format.hpp"

                                                            #include "CodeGenerator.hpp"

                                                            void CodeGeneratorCpp::generateInstanceCode()
                                                            {
                                                              if (! variable("append").boolean() && ! variable("embedded").boolean())
                                                              {
                                                                if (*variable("package").string())
                                                                {
                                                            #line 16 "CodeGeneratorCpp.cpp"
  append(L"package ");
                                                            #line 12 "CodeGeneratorCpp.cpp.template"
                                                                  print(variable("package").string());
                                                            #line 20 "CodeGeneratorCpp.cpp"
  append(L";\n");
  append(L"\n");
                                                            #line 15 "CodeGeneratorCpp.cpp.template"
                                                                }
                                                            #line 25 "CodeGeneratorCpp.cpp"
  append(L"class ");
                                                            #line 16 "CodeGeneratorCpp.cpp.template"
                                                                print(Format::acceptableName<CString>(variable("classname").string()).c_str());
                                                            #line 29 "CodeGeneratorCpp.cpp"
  append(L"\n");
  append(L"{");
                                                            #line 18 "CodeGeneratorCpp.cpp.template"
                                                              }
                                                              if (! variable("useGlr").boolean())
                                                              {
                                                            #line 36 "CodeGeneratorCpp.cpp"
  append(L"\n");
  append(L"  const ");
                                                            #line 22 "CodeGeneratorCpp.cpp.template"
                                                                print(variable("stringType").string());
                                                            #line 41 "CodeGeneratorCpp.cpp"
  append(L"input;");
                                                            #line 23 "CodeGeneratorCpp.cpp.template"
                                                              }
                                                            #line 45 "CodeGeneratorCpp.cpp"
  append(L"\n");
  append(L"  int begin;\n");
  append(L"  int end;");
                                                            #line 26 "CodeGeneratorCpp.cpp.template"
                                                              if (! variable("embedded").boolean())
                                                              {
                                                            #line 52 "CodeGeneratorCpp.cpp"
  append(L"\n");
  append(L"  int state;");
                                                            #line 29 "CodeGeneratorCpp.cpp.template"
                                                              }
                                                            #line 57 "CodeGeneratorCpp.cpp"
  append(L"\n");
                                                            #line 31 "CodeGeneratorCpp.cpp.template"
                                                              if (! variable("embedded").boolean())
                                                              {
                                                            #line 62 "CodeGeneratorCpp.cpp"
  append(L"\n");
  append(L"  void init(String string)\n");
  append(L"  {\n");
  append(L"    input = string;\n");
  append(L"    end = 0;\n");
  append(L"    current = 0;\n");
  append(L"    charclass = -1;\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  int getOffset() {return begin;}\n");
  append(L"  int getSize()   {return end - begin;}\n");
  append(L"  int getState()  {return state;}\n");
  append(L"\n");
  append(L"  int match(int tokenSetId, String string)\n");
  append(L"  {\n");
  append(L"    init(string);\n");
  append(L"    return match(tokenSetId);\n");
  append(L"  }\n");
                                                            #line 51 "CodeGeneratorCpp.cpp.template"
                                                              }
                                                              else if (variable("tables").boolean())
                                                              {
                                                            #line 85 "CodeGeneratorCpp.cpp"
  append(L"\n");
  append(L"  int predict(int dpi)");
                                                            #line 55 "CodeGeneratorCpp.cpp.template"
                                                                predict();
                                                              }
                                                            #line 91 "CodeGeneratorCpp.cpp"
  append(L"\n");
  append(L"  int match(int tokenSetId)\n");
  append(L"  {");
                                                            #line 59 "CodeGeneratorCpp.cpp.template"
                                                              if (variable("trace").boolean())
                                                              {
                                                            #line 98 "CodeGeneratorCpp.cpp"
  append(L"\n");
  append(L"    fprintf(stderr, \"  <tokenize ");
                                                            #line 62 "CodeGeneratorCpp.cpp.template"
                                                                if (variable("useGlr").boolean())
                                                                {
                                                            #line 104 "CodeGeneratorCpp.cpp"
  append(L"thread=\\\"%d\\\" ");
                                                            #line 64 "CodeGeneratorCpp.cpp.template"
                                                                }
                                                            #line 108 "CodeGeneratorCpp.cpp"
  append(L"tokenset=\\\"%d\\\">\\n\", ");
                                                            #line 65 "CodeGeneratorCpp.cpp.template"
                                                                if (variable("useGlr").boolean())
                                                                {
                                                            #line 113 "CodeGeneratorCpp.cpp"
  append(L"id, ");
                                                            #line 67 "CodeGeneratorCpp.cpp.template"
                                                                }
                                                            #line 117 "CodeGeneratorCpp.cpp"
  append(L"tokenSetId);\n");
                                                            #line 69 "CodeGeneratorCpp.cpp.template"
                                                              }
                                                              int lookahead = variable("maxcontextlength").integer();
                                                              bool hasFixedTokenLength = variable("hasfixedtokenlength").boolean();
                                                              bool utf8 = 0 == strcmp("char *", variable("stringType").string());
                                                              const wchar_t *multiItem = utf8 ? L"nonascii" : L"nonbmp";
                                                              if (lookahead)
                                                              {
                                                            #line 127 "CodeGeneratorCpp.cpp"
  append(L"\n");
  append(L"    bool ");
                                                            #line 77 "CodeGeneratorCpp.cpp.template"
                                                                append(multiItem);
                                                            #line 132 "CodeGeneratorCpp.cpp"
  append(L" = false;");
                                                            #line 78 "CodeGeneratorCpp.cpp.template"
                                                              }
                                                            #line 136 "CodeGeneratorCpp.cpp"
  append(L"\n");
  append(L"    begin = end;\n");
  append(L"    int current = end;\n");
  append(L"    int result = INITIAL[tokenSetId];");
                                                            #line 82 "CodeGeneratorCpp.cpp.template"
                                                              if (variable("embedded").boolean() && (variable("trace").boolean() || ! variable("useGlr").boolean()))
                                                              {
                                                            #line 144 "CodeGeneratorCpp.cpp"
  append(L"\n");
  append(L"    int state = 0;");
                                                            #line 85 "CodeGeneratorCpp.cpp.template"
                                                              }
                                                            #line 149 "CodeGeneratorCpp.cpp"
  append(L"\n");
                                                            #line 87 "CodeGeneratorCpp.cpp.template"
                                                              if (variable("trace").boolean())
                                                              {
                                                            #line 154 "CodeGeneratorCpp.cpp"
  append(L"\n");
  append(L"    fprintf(stderr, \"    <next state=\\\"%d\\\"\", result & ");
                                                            #line 90 "CodeGeneratorCpp.cpp.template"
                                                                print(Math::powerof(2, variable("stateCodeBits").integer()) - 1);
                                                            #line 159 "CodeGeneratorCpp.cpp"
  append(L");");
                                                            #line 91 "CodeGeneratorCpp.cpp.template"
                                                              }
                                                            #line 163 "CodeGeneratorCpp.cpp"
  append(L"\n");
  append(L"    for (int code = result & ");
                                                            #line 93 "CodeGeneratorCpp.cpp.template"
                                                              print(Math::powerof(2, variable("stateCodeBits").integer()) - 1);
                                                            #line 168 "CodeGeneratorCpp.cpp"
  append(L"; code != 0; )\n");
  append(L"    {\n");
  append(L"      int charclass;\n");
  append(L"      int c0 = ");
                                                            #line 97 "CodeGeneratorCpp.cpp.template"
                                                              if (utf8)
                                                              {
                                                            #line 176 "CodeGeneratorCpp.cpp"
  append(L"(unsigned char) ");
                                                            #line 99 "CodeGeneratorCpp.cpp.template"
                                                              }
                                                              if (variable("useGlr").boolean())
                                                              {
                                                            #line 182 "CodeGeneratorCpp.cpp"
  append(L"parser->");
                                                            #line 102 "CodeGeneratorCpp.cpp.template"
                                                              }
                                                            #line 186 "CodeGeneratorCpp.cpp"
  append(L"input[current];");
                                                            #line 104 "CodeGeneratorCpp.cpp.template"
                                                              if (variable("trace").boolean())
                                                              {
                                                            #line 191 "CodeGeneratorCpp.cpp"
  append(L"\n");
  append(L"      fprintf(stderr, \" offset=\\\"%d\\\"\", current);");
                                                            #line 107 "CodeGeneratorCpp.cpp.template"
                                                              }
                                                            #line 196 "CodeGeneratorCpp.cpp"
  append(L"\n");
  append(L"      ++current;\n");
  append(L"      if (c0 < ");
                                                            #line 110 "CodeGeneratorCpp.cpp.template"
                                                              print(format.toString<char>(variable("simplifiedCodeMap").integer(), 16, 0, 0, "0x", "0123456789abcdef"));
                                                            #line 202 "CodeGeneratorCpp.cpp"
  append(L")\n");
  append(L"      {");
                                                            #line 112 "CodeGeneratorCpp.cpp.template"
                                                              if (variable("trace").boolean())
                                                              {
                                                            #line 208 "CodeGeneratorCpp.cpp"
  append(L"\n");
  append(L"        if (c0 >= 32 && c0 <= 126)\n");
  append(L"        {\n");
  append(L"          ");
                                                            #line 117 "CodeGeneratorCpp.cpp.template"
                                                                print(utf8 ? "char" : "wchar_t");
                                                            #line 215 "CodeGeneratorCpp.cpp"
  append(L" c = (");
                                                            #line 118 "CodeGeneratorCpp.cpp.template"
                                                                print(utf8 ? "char" : "wchar_t");
                                                            #line 219 "CodeGeneratorCpp.cpp"
  append(L") c0;\n");
  append(L"          fprintf(stderr, \" char=\\\"%s\\\"\", ");
                                                            #line 120 "CodeGeneratorCpp.cpp.template"
                                                                if (! utf8)
                                                                {
                                                            #line 225 "CodeGeneratorCpp.cpp"
  append(L"Utf8Encoder::encode(");
                                                            #line 123 "CodeGeneratorCpp.cpp.template"
                                                                }
                                                            #line 229 "CodeGeneratorCpp.cpp"
  append(L"xmlEscape(&c, 1).c_str()");
                                                            #line 125 "CodeGeneratorCpp.cpp.template"
                                                                if (! utf8)
                                                                {
                                                            #line 234 "CodeGeneratorCpp.cpp"
  append(L").c_str()");
                                                            #line 127 "CodeGeneratorCpp.cpp.template"
                                                                }
                                                            #line 238 "CodeGeneratorCpp.cpp"
  append(L");\n");
  append(L"        }");
                                                            #line 129 "CodeGeneratorCpp.cpp.template"
                                                              }
                                                            #line 243 "CodeGeneratorCpp.cpp"
  append(L"\n");
  append(L"        charclass = MAP0[c0];\n");
  append(L"      }\n");
  append(L"      else");
                                                            #line 133 "CodeGeneratorCpp.cpp.template"
                                                              if (! utf8)
                                                              {
                                                            #line 251 "CodeGeneratorCpp.cpp"
  append(L" ");
                                                            #line 135 "CodeGeneratorCpp.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 257 "CodeGeneratorCpp.cpp"
  append(L"\n");
  append(L"      {");
                                                            #line 139 "CodeGeneratorCpp.cpp.template"
                                                                if (lookahead)
                                                                {
                                                            #line 263 "CodeGeneratorCpp.cpp"
  append(L"\n");
  append(L"        ");
                                                            #line 142 "CodeGeneratorCpp.cpp.template"
                                                                  append(multiItem);
                                                            #line 268 "CodeGeneratorCpp.cpp"
  append(L" = true;");
                                                            #line 143 "CodeGeneratorCpp.cpp.template"
                                                                }
                                                            #line 272 "CodeGeneratorCpp.cpp"
  append(L"\n");
  append(L"        if      ((c0");
                                                            #line 146 "CodeGeneratorCpp.cpp.template"
                                                                if (variable("useGlr").boolean())
                                                                {
                                                            #line 278 "CodeGeneratorCpp.cpp"
  append(L"        ");
                                                            #line 148 "CodeGeneratorCpp.cpp.template"
                                                                }
                                                            #line 282 "CodeGeneratorCpp.cpp"
  append(L"                 & 0xe0) == 0xc0\n");
  append(L"              && (");
                                                            #line 151 "CodeGeneratorCpp.cpp.template"
                                                                if (variable("useGlr").boolean())
                                                                {
                                                            #line 288 "CodeGeneratorCpp.cpp"
  append(L"parser->");
                                                            #line 153 "CodeGeneratorCpp.cpp.template"
                                                                }
                                                            #line 292 "CodeGeneratorCpp.cpp"
  append(L"input[current    ] & 0xc0) == 0x80)\n");
  append(L"        {\n");
  append(L"          c0 = ((c0");
                                                            #line 157 "CodeGeneratorCpp.cpp.template"
                                                                if (variable("useGlr").boolean())
                                                                {
                                                            #line 299 "CodeGeneratorCpp.cpp"
  append(L"        ");
                                                            #line 159 "CodeGeneratorCpp.cpp.template"
                                                                }
                                                            #line 303 "CodeGeneratorCpp.cpp"
  append(L"                 & 0x1f) << 6)\n");
  append(L"             |  (");
                                                            #line 162 "CodeGeneratorCpp.cpp.template"
                                                                if (variable("useGlr").boolean())
                                                                {
                                                            #line 309 "CodeGeneratorCpp.cpp"
  append(L"parser->");
                                                            #line 164 "CodeGeneratorCpp.cpp.template"
                                                                }
                                                            #line 313 "CodeGeneratorCpp.cpp"
  append(L"input[current    ] & 0x3f);\n");
  append(L"          if (c0 < 0x80) c0 = -1; else ++current;\n");
  append(L"        }\n");
  append(L"        else if ((c0");
                                                            #line 169 "CodeGeneratorCpp.cpp.template"
                                                                if (variable("useGlr").boolean())
                                                                {
                                                            #line 321 "CodeGeneratorCpp.cpp"
  append(L"        ");
                                                            #line 171 "CodeGeneratorCpp.cpp.template"
                                                                }
                                                            #line 325 "CodeGeneratorCpp.cpp"
  append(L"                 & 0xf0) == 0xe0\n");
  append(L"              && (");
                                                            #line 174 "CodeGeneratorCpp.cpp.template"
                                                                if (variable("useGlr").boolean())
                                                                {
                                                            #line 331 "CodeGeneratorCpp.cpp"
  append(L"parser->");
                                                            #line 176 "CodeGeneratorCpp.cpp.template"
                                                                }
                                                            #line 335 "CodeGeneratorCpp.cpp"
  append(L"input[current    ] & 0xc0) == 0x80\n");
  append(L"              && (");
                                                            #line 179 "CodeGeneratorCpp.cpp.template"
                                                                if (variable("useGlr").boolean())
                                                                {
                                                            #line 341 "CodeGeneratorCpp.cpp"
  append(L"parser->");
                                                            #line 181 "CodeGeneratorCpp.cpp.template"
                                                                }
                                                            #line 345 "CodeGeneratorCpp.cpp"
  append(L"input[current + 1] & 0xc0) == 0x80)\n");
  append(L"        {\n");
  append(L"          c0 = ((c0");
                                                            #line 185 "CodeGeneratorCpp.cpp.template"
                                                                if (variable("useGlr").boolean())
                                                                {
                                                            #line 352 "CodeGeneratorCpp.cpp"
  append(L"        ");
                                                            #line 187 "CodeGeneratorCpp.cpp.template"
                                                                }
                                                            #line 356 "CodeGeneratorCpp.cpp"
  append(L"                 & 0x0f) << 12)\n");
  append(L"             | ((");
                                                            #line 190 "CodeGeneratorCpp.cpp.template"
                                                                if (variable("useGlr").boolean())
                                                                {
                                                            #line 362 "CodeGeneratorCpp.cpp"
  append(L"parser->");
                                                            #line 192 "CodeGeneratorCpp.cpp.template"
                                                                }
                                                            #line 366 "CodeGeneratorCpp.cpp"
  append(L"input[current    ] & 0x3f) <<  6)\n");
  append(L"             |  (");
                                                            #line 195 "CodeGeneratorCpp.cpp.template"
                                                                if (variable("useGlr").boolean())
                                                                {
                                                            #line 372 "CodeGeneratorCpp.cpp"
  append(L"parser->");
                                                            #line 197 "CodeGeneratorCpp.cpp.template"
                                                                }
                                                            #line 376 "CodeGeneratorCpp.cpp"
  append(L"input[current + 1] & 0x3f);\n");
  append(L"          if (c0 < 0x800) c0 = -1; else current += 2;\n");
  append(L"        }\n");
  append(L"        else if ((c0");
                                                            #line 202 "CodeGeneratorCpp.cpp.template"
                                                                if (variable("useGlr").boolean())
                                                                {
                                                            #line 384 "CodeGeneratorCpp.cpp"
  append(L"        ");
                                                            #line 204 "CodeGeneratorCpp.cpp.template"
                                                                }
                                                            #line 388 "CodeGeneratorCpp.cpp"
  append(L"                 & 0xf8) == 0xf0\n");
  append(L"              && (");
                                                            #line 207 "CodeGeneratorCpp.cpp.template"
                                                                if (variable("useGlr").boolean())
                                                                {
                                                            #line 394 "CodeGeneratorCpp.cpp"
  append(L"parser->");
                                                            #line 209 "CodeGeneratorCpp.cpp.template"
                                                                }
                                                            #line 398 "CodeGeneratorCpp.cpp"
  append(L"input[current    ] & 0xc0) == 0x80\n");
  append(L"              && (");
                                                            #line 212 "CodeGeneratorCpp.cpp.template"
                                                                if (variable("useGlr").boolean())
                                                                {
                                                            #line 404 "CodeGeneratorCpp.cpp"
  append(L"parser->");
                                                            #line 214 "CodeGeneratorCpp.cpp.template"
                                                                }
                                                            #line 408 "CodeGeneratorCpp.cpp"
  append(L"input[current + 1] & 0xc0) == 0x80\n");
  append(L"              && (");
                                                            #line 217 "CodeGeneratorCpp.cpp.template"
                                                                if (variable("useGlr").boolean())
                                                                {
                                                            #line 414 "CodeGeneratorCpp.cpp"
  append(L"parser->");
                                                            #line 219 "CodeGeneratorCpp.cpp.template"
                                                                }
                                                            #line 418 "CodeGeneratorCpp.cpp"
  append(L"input[current + 2] & 0xc0) == 0x80)\n");
  append(L"        {\n");
  append(L"          c0 = ((c0");
                                                            #line 223 "CodeGeneratorCpp.cpp.template"
                                                                if (variable("useGlr").boolean())
                                                                {
                                                            #line 425 "CodeGeneratorCpp.cpp"
  append(L"        ");
                                                            #line 225 "CodeGeneratorCpp.cpp.template"
                                                                }
                                                            #line 429 "CodeGeneratorCpp.cpp"
  append(L"                 & 0x07) << 18)\n");
  append(L"             | ((");
                                                            #line 228 "CodeGeneratorCpp.cpp.template"
                                                                if (variable("useGlr").boolean())
                                                                {
                                                            #line 435 "CodeGeneratorCpp.cpp"
  append(L"parser->");
                                                            #line 230 "CodeGeneratorCpp.cpp.template"
                                                                }
                                                            #line 439 "CodeGeneratorCpp.cpp"
  append(L"input[current    ] & 0x3f) << 12)\n");
  append(L"             | ((");
                                                            #line 233 "CodeGeneratorCpp.cpp.template"
                                                                if (variable("useGlr").boolean())
                                                                {
                                                            #line 445 "CodeGeneratorCpp.cpp"
  append(L"parser->");
                                                            #line 235 "CodeGeneratorCpp.cpp.template"
                                                                }
                                                            #line 449 "CodeGeneratorCpp.cpp"
  append(L"input[current + 1] & 0x3f) <<  6)\n");
  append(L"             | ( ");
                                                            #line 238 "CodeGeneratorCpp.cpp.template"
                                                                if (variable("useGlr").boolean())
                                                                {
                                                            #line 455 "CodeGeneratorCpp.cpp"
  append(L"parser->");
                                                            #line 240 "CodeGeneratorCpp.cpp.template"
                                                                }
                                                            #line 459 "CodeGeneratorCpp.cpp"
  append(L"input[current + 2] & 0x3f       );\n");
  append(L"          if (c0 < 0x10000 || c0 > 0x10ffff) c0 = -1; else current += 3;\n");
  append(L"        }\n");
  append(L"\n");
  append(L"        ");
                                                            #line 245 "CodeGeneratorCpp.cpp.template"
                                                                indent++;
                                                              }
                                                            #line 468 "CodeGeneratorCpp.cpp"
  append(L"if (c0 < ");
                                                            #line 247 "CodeGeneratorCpp.cpp.template"
                                                              print(format.toString<char>(variable("uncompressedMapSize").integer(), 16, 0, 0, "0x", "0123456789abcdef"));
                                                            #line 472 "CodeGeneratorCpp.cpp"
  append(L")\n");
  append(L"      {\n");
                                                            #line 250 "CodeGeneratorCpp.cpp.template"
                                                              compressedMapAccessor(8, "c", "charclass = ", "MAP1", &variable("m1bits").integer());
                                                            #line 477 "CodeGeneratorCpp.cpp"
  append(L"\n");
  append(L"      }\n");
  append(L"      else\n");
  append(L"      {");
                                                            #line 254 "CodeGeneratorCpp.cpp.template"
                                                              if (variable("m2").size == 0)
                                                              {
                                                            #line 485 "CodeGeneratorCpp.cpp"
  append(L"\n");
  append(L"        charclass = 0;");
                                                            #line 257 "CodeGeneratorCpp.cpp.template"
                                                              }
                                                              else
                                                              {
                                                                if (! utf8)
                                                                {
                                                            #line 494 "CodeGeneratorCpp.cpp"
  append(L"\n");
  append(L"        if (");
                                                            #line 263 "CodeGeneratorCpp.cpp.template"
                                                                  if (variable("uncompressedMapSize").integer() != 0xd800)
                                                                  {
                                                            #line 500 "CodeGeneratorCpp.cpp"
  append(L"c0 >= 0xd800 && ");
                                                            #line 265 "CodeGeneratorCpp.cpp.template"
                                                                  }
                                                            #line 504 "CodeGeneratorCpp.cpp"
  append(L"c0 < 0xdc00)\n");
  append(L"        {\n");
  append(L"          int c1 = ");
                                                            #line 269 "CodeGeneratorCpp.cpp.template"
                                                                  if (variable("useGlr").boolean())
                                                                  {
                                                            #line 511 "CodeGeneratorCpp.cpp"
  append(L"parser->");
                                                            #line 271 "CodeGeneratorCpp.cpp.template"
                                                                  }
                                                            #line 515 "CodeGeneratorCpp.cpp"
  append(L"input[current];\n");
  append(L"          if (c1 >= 0xdc00 && c1 < 0xe000)\n");
  append(L"          {");
                                                            #line 274 "CodeGeneratorCpp.cpp.template"
                                                                  if (lookahead)
                                                                  {
                                                            #line 522 "CodeGeneratorCpp.cpp"
  append(L"\n");
  append(L"            ");
                                                            #line 277 "CodeGeneratorCpp.cpp.template"
                                                                    append(multiItem);
                                                            #line 527 "CodeGeneratorCpp.cpp"
  append(L" = true;");
                                                            #line 278 "CodeGeneratorCpp.cpp.template"
                                                                  }
                                                            #line 531 "CodeGeneratorCpp.cpp"
  append(L"\n");
  append(L"            ++current;\n");
  append(L"            c0 = ((c0 & 0x3ff) << 10) + (c1 & 0x3ff) + 0x10000;\n");
  append(L"          }\n");
  append(L"        }");
                                                            #line 283 "CodeGeneratorCpp.cpp.template"
                                                                }
                                                            #line 539 "CodeGeneratorCpp.cpp"
  append(L"\n");
  append(L"        int lo = 0, hi = ");
                                                            #line 285 "CodeGeneratorCpp.cpp.template"
                                                                print(variable("m2").size / 3 - 1);
                                                            #line 544 "CodeGeneratorCpp.cpp"
  append(L";\n");
  append(L"        for (int m = ");
                                                            #line 287 "CodeGeneratorCpp.cpp.template"
                                                                print((variable("m2").size / 3) >> 1);
                                                            #line 549 "CodeGeneratorCpp.cpp"
  append(L"; ; m = (hi + lo) >> 1)\n");
  append(L"        {\n");
  append(L"          if (MAP2[m] > c0) hi = m - 1;\n");
  append(L"          else if (MAP2[");
                                                            #line 291 "CodeGeneratorCpp.cpp.template"
                                                                print(variable("m2").size / 3);
                                                            #line 556 "CodeGeneratorCpp.cpp"
  append(L" + m] < c0) lo = m + 1;\n");
  append(L"          else {charclass = MAP2[");
                                                            #line 293 "CodeGeneratorCpp.cpp.template"
                                                                print(variable("m2").size / 3 * 2);
                                                            #line 561 "CodeGeneratorCpp.cpp"
  append(L" + m]; break;}\n");
  append(L"          if (lo > hi) {charclass = 0; break;}\n");
  append(L"        }");
                                                            #line 296 "CodeGeneratorCpp.cpp.template"
                                                              }
                                                              if (utf8)
                                                              {
                                                                indent--;
                                                            #line 570 "CodeGeneratorCpp.cpp"
  append(L"\n");
  append(L"        }");
                                                            #line 301 "CodeGeneratorCpp.cpp.template"
                                                              }
                                                            #line 575 "CodeGeneratorCpp.cpp"
  append(L"\n");
  append(L"      }");
                                                            #line 303 "CodeGeneratorCpp.cpp.template"
                                                              if (variable("trace").boolean())
                                                              {
                                                            #line 581 "CodeGeneratorCpp.cpp"
  append(L"\n");
  append(L"      fprintf(stderr, \" codepoint=\\\"%d\\\" class=\\\"%d\\\"\", c0, charclass);");
                                                            #line 307 "CodeGeneratorCpp.cpp.template"
                                                              }
                                                            #line 586 "CodeGeneratorCpp.cpp"
  append(L"\n");
                                                            #line 309 "CodeGeneratorCpp.cpp.template"
                                                              if (variable("trace").boolean() || ! variable("useGlr").boolean())
                                                              {
                                                            #line 591 "CodeGeneratorCpp.cpp"
  append(L"\n");
  append(L"      state = code;");
                                                            #line 312 "CodeGeneratorCpp.cpp.template"
                                                              }
                                                            #line 596 "CodeGeneratorCpp.cpp"
  append(L"\n");
                                                            #line 314 "CodeGeneratorCpp.cpp.template"
                                                              compressedMap2dAccessor("code - 1", "charclass", variable("a1cols").integer(),
                                                                                         6, "i", "code = ", "TRANSITION", &variable("a1bits").integer());
                                                            #line 601 "CodeGeneratorCpp.cpp"
  append(L"\n");
  append(L"      if (code > ");
                                                            #line 317 "CodeGeneratorCpp.cpp.template"
                                                              print(Math::powerof(2, variable("stateCodeBits").integer()) - 1);
                                                            #line 606 "CodeGeneratorCpp.cpp"
  append(L")\n");
  append(L"      {\n");
  append(L"        result = code;");
                                                            #line 320 "CodeGeneratorCpp.cpp.template"
                                                              if (variable("trace").boolean())
                                                              {
                                                            #line 613 "CodeGeneratorCpp.cpp"
  append(L"\n");
  append(L"        fprintf(stderr, \" result=\\\"%s\\\"\", ");
                                                            #line 324 "CodeGeneratorCpp.cpp.template"
                                                                if (! utf8)
                                                                {
                                                            #line 619 "CodeGeneratorCpp.cpp"
  append(L"Utf8Encoder::encode(");
                                                            #line 327 "CodeGeneratorCpp.cpp.template"
                                                                }
                                                            #line 623 "CodeGeneratorCpp.cpp"
  append(L"xmlEscape(TOKEN[((result >> ");
                                                            #line 329 "CodeGeneratorCpp.cpp.template"
                                                                print(variable("stateCodeBits").integer());
                                                            #line 627 "CodeGeneratorCpp.cpp"
  append(L") & ");
                                                            #line 330 "CodeGeneratorCpp.cpp.template"
                                                 print(Math::powerof(2, variable("tokencodeBits").integer()) - 1);
                                                            #line 631 "CodeGeneratorCpp.cpp"
  append(L") - 1], 0).c_str()");
                                                            #line 331 "CodeGeneratorCpp.cpp.template"
                                                                if (! utf8)
                                                                {
                                                            #line 636 "CodeGeneratorCpp.cpp"
  append(L").c_str()");
                                                            #line 333 "CodeGeneratorCpp.cpp.template"
                                                                }
                                                            #line 640 "CodeGeneratorCpp.cpp"
  append(L");");
                                                            #line 334 "CodeGeneratorCpp.cpp.template"
                                                                if (lookahead || hasFixedTokenLength)
                                                                {
                                                                  int contextOffset = variable("stateCodeBits").integer()
                                                                                    + variable("tokencodeBits").integer();
                                                                  int sizeOffset = contextOffset
                                                                                 + (hasFixedTokenLength ? 1 : 0);
                                                                  if (hasFixedTokenLength)
                                                                  {
                                                            #line 651 "CodeGeneratorCpp.cpp"
  append(L"\n");
  append(L"        if ((result & ");
                                                            #line 343 "CodeGeneratorCpp.cpp.template"
                                                                    print(Math::powerof(2, contextOffset));
                                                            #line 656 "CodeGeneratorCpp.cpp"
  append(L") > 0)\n");
  append(L"        {\n");
  append(L"          fprintf(stderr, \" token-size=\\\"%d\\\"\", result >> ");
                                                            #line 346 "CodeGeneratorCpp.cpp.template"
                                                                    print(sizeOffset);
                                                            #line 662 "CodeGeneratorCpp.cpp"
  append(L");\n");
  append(L"        }\n");
  append(L"        else ");
                                                            #line 349 "CodeGeneratorCpp.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 670 "CodeGeneratorCpp.cpp"
  append(L"\n");
  append(L"        ");
                                                            #line 353 "CodeGeneratorCpp.cpp.template"
                                                                  }
                                                            #line 675 "CodeGeneratorCpp.cpp"
  append(L"if ((result >> ");
                                                            #line 354 "CodeGeneratorCpp.cpp.template"
                                                                  print(sizeOffset);
                                                            #line 679 "CodeGeneratorCpp.cpp"
  append(L") > 0)\n");
  append(L"        {\n");
  append(L"          fprintf(stderr, \" trailing-context-size=\\\"%d\\\"\", result >> ");
                                                            #line 358 "CodeGeneratorCpp.cpp.template"
                                                                  print(sizeOffset);
                                                            #line 685 "CodeGeneratorCpp.cpp"
  append(L");\n");
  append(L"        }");
                                                            #line 360 "CodeGeneratorCpp.cpp.template"
                                                                }
                                                              }
                                                            #line 691 "CodeGeneratorCpp.cpp"
  append(L"\n");
  append(L"        code &= ");
                                                            #line 363 "CodeGeneratorCpp.cpp.template"
                                                              print(Math::powerof(2, variable("stateCodeBits").integer()) - 1);
                                                            #line 696 "CodeGeneratorCpp.cpp"
  append(L";\n");
  append(L"        end = current;\n");
  append(L"      }");
                                                            #line 366 "CodeGeneratorCpp.cpp.template"
                                                              if (variable("trace").boolean())
                                                              {
                                                            #line 703 "CodeGeneratorCpp.cpp"
  append(L"\n");
  append(L"      fprintf(stderr, \"/>\\n\");\n");
  append(L"      if (code != 0)\n");
  append(L"      {\n");
  append(L"        fprintf(stderr, \"    <next state=\\\"%d\\\"\", code);\n");
  append(L"      }");
                                                            #line 373 "CodeGeneratorCpp.cpp.template"
                                                              }
                                                            #line 712 "CodeGeneratorCpp.cpp"
  append(L"\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    result >>= ");
                                                            #line 377 "CodeGeneratorCpp.cpp.template"
                                                              print(variable("stateCodeBits").integer());
                                                            #line 719 "CodeGeneratorCpp.cpp"
  append(L";\n");
  append(L"    if (result == 0)\n");
  append(L"    {");
                                                            #line 380 "CodeGeneratorCpp.cpp.template"
                                                              if (utf8)
                                                              {
                                                            #line 726 "CodeGeneratorCpp.cpp"
  append(L"\n");
  append(L"      for (end = current - 1; (");
                                                            #line 384 "CodeGeneratorCpp.cpp.template"
                                                                if (variable("useGlr").boolean())
                                                                {
                                                            #line 732 "CodeGeneratorCpp.cpp"
  append(L"parser->");
                                                            #line 386 "CodeGeneratorCpp.cpp.template"
                                                                }
                                                            #line 736 "CodeGeneratorCpp.cpp"
  append(L"input[end] & 0xc0) == 0x80; --end) ;");
                                                            #line 388 "CodeGeneratorCpp.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 742 "CodeGeneratorCpp.cpp"
  append(L"\n");
  append(L"      end = current - 1;\n");
  append(L"      int c1 = ");
                                                            #line 394 "CodeGeneratorCpp.cpp.template"
                                                                if (variable("useGlr").boolean())
                                                                {
                                                            #line 749 "CodeGeneratorCpp.cpp"
  append(L"parser->");
                                                            #line 396 "CodeGeneratorCpp.cpp.template"
                                                                }
                                                            #line 753 "CodeGeneratorCpp.cpp"
  append(L"input[end];\n");
  append(L"      if (c1 >= 0xdc00 && c1 < 0xe000) --end;");
                                                            #line 398 "CodeGeneratorCpp.cpp.template"
                                                              }
                                                              if (variable("trace").boolean())
                                                              {
                                                            #line 760 "CodeGeneratorCpp.cpp"
  append(L"\n");
  append(L"      fprintf(stderr, \"    <fail begin=\\\"%d\\\" end=\\\"%d\\\" state=\\\"%d\\\"/>\\n\", begin, end, state);\n");
  append(L"      fprintf(stderr, \"  </tokenize>\\n\");");
                                                            #line 403 "CodeGeneratorCpp.cpp.template"
                                                              }
                                                              if (! variable("embedded").boolean())
                                                              {
                                                            #line 768 "CodeGeneratorCpp.cpp"
  append(L"\n");
  append(L"      return -1;");
                                                            #line 407 "CodeGeneratorCpp.cpp.template"
                                                              }
                                                              else if (variable("useGlr").boolean())
                                                              {
                                                            #line 775 "CodeGeneratorCpp.cpp"
  append(L"\n");
  append(L"      end = begin;\n");
  append(L"      return -1;");
                                                            #line 412 "CodeGeneratorCpp.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 783 "CodeGeneratorCpp.cpp"
  append(L"\n");
  append(L"      return error(begin, end, state, -1, -1);");
                                                            #line 416 "CodeGeneratorCpp.cpp.template"
                                                              }
                                                            #line 788 "CodeGeneratorCpp.cpp"
  append(L"\n");
  append(L"    }\n");
                                                            #line 419 "CodeGeneratorCpp.cpp.template"
                                                              int lowBits = variable("tokencodeBits").integer();
                                                              if (hasFixedTokenLength && ! lookahead)
                                                              {
                                                            #line 795 "CodeGeneratorCpp.cpp"
  append(L"\n");
  append(L"    if ((result & ");
                                                            #line 423 "CodeGeneratorCpp.cpp.template"
                                                                  print(Math::powerof(2, lowBits));
                                                                  ++lowBits;
                                                            #line 801 "CodeGeneratorCpp.cpp"
  append(L") != 0)\n");
  append(L"    {\n");
  append(L"      end = begin;\n");
  append(L"    }\n");
                                                            #line 429 "CodeGeneratorCpp.cpp.template"
                                                              }
                                                              else
                                                              {
                                                                if (hasFixedTokenLength)
                                                                {
                                                            #line 812 "CodeGeneratorCpp.cpp"
  append(L"\n");
  append(L"    if ((result & ");
                                                            #line 435 "CodeGeneratorCpp.cpp.template"
                                                                  print(Math::powerof(2, lowBits));
                                                                  ++lowBits;
                                                            #line 818 "CodeGeneratorCpp.cpp"
  append(L") != 0)\n");
  append(L"    {\n");
  append(L"      end = begin;\n");
  append(L"      if (");
                                                            #line 440 "CodeGeneratorCpp.cpp.template"
                                                                  append(multiItem);
                                                            #line 825 "CodeGeneratorCpp.cpp"
  append(L")\n");
  append(L"      {\n");
  append(L"        for (int i = result >> ");
                                                            #line 443 "CodeGeneratorCpp.cpp.template"
                                                                  print(lowBits);
                                                            #line 831 "CodeGeneratorCpp.cpp"
  append(L"; i > 0; --i)");
                                                            #line 444 "CodeGeneratorCpp.cpp.template"
                                                                  if (utf8)
                                                                  {
                                                            #line 836 "CodeGeneratorCpp.cpp"
  append(L"\n");
  append(L"          for (++end; (");
                                                            #line 448 "CodeGeneratorCpp.cpp.template"
                                                                    if (variable("useGlr").boolean())
                                                                    {
                                                            #line 842 "CodeGeneratorCpp.cpp"
  append(L"parser->");
                                                            #line 450 "CodeGeneratorCpp.cpp.template"
                                                                    }
                                                            #line 846 "CodeGeneratorCpp.cpp"
  append(L"input[end] & 0xc0) == 0x80 && end <= current; ++end) ;");
                                                            #line 452 "CodeGeneratorCpp.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 852 "CodeGeneratorCpp.cpp"
  append(L"\n");
  append(L"        {\n");
  append(L"          int c1 = ");
                                                            #line 458 "CodeGeneratorCpp.cpp.template"
                                                                    if (variable("useGlr").boolean())
                                                                    {
                                                            #line 859 "CodeGeneratorCpp.cpp"
  append(L"parser->");
                                                            #line 460 "CodeGeneratorCpp.cpp.template"
                                                                    }
                                                            #line 863 "CodeGeneratorCpp.cpp"
  append(L"input[end++];\n");
  append(L"          if (c1 >= 0xd800 && c1 < 0xdc00) ++end;\n");
  append(L"        }");
                                                            #line 463 "CodeGeneratorCpp.cpp.template"
                                                                  }
                                                            #line 869 "CodeGeneratorCpp.cpp"
  append(L"\n");
  append(L"      }\n");
  append(L"      else\n");
  append(L"      {\n");
  append(L"        end += (result >> ");
                                                            #line 468 "CodeGeneratorCpp.cpp.template"
                                                                  print(lowBits);
                                                            #line 877 "CodeGeneratorCpp.cpp"
  append(L");\n");
  append(L"      }\n");
  append(L"    }\n");
  append(L"    else\n");
  append(L"    {");
                                                            #line 473 "CodeGeneratorCpp.cpp.template"
                                                                  ++indent;
                                                                }
                                                                if (lookahead)
                                                                {
                                                            #line 888 "CodeGeneratorCpp.cpp"
  append(L"\n");
  append(L"    if (");
                                                            #line 478 "CodeGeneratorCpp.cpp.template"
                                                                  append(multiItem);
                                                            #line 893 "CodeGeneratorCpp.cpp"
  append(L")\n");
  append(L"    {\n");
  append(L"      for (int i = result >> ");
                                                            #line 481 "CodeGeneratorCpp.cpp.template"
                                                                  print(lowBits);
                                                            #line 899 "CodeGeneratorCpp.cpp"
  append(L"; i > 0; --i)");
                                                            #line 482 "CodeGeneratorCpp.cpp.template"
                                                                  if (utf8)
                                                                  {
                                                            #line 904 "CodeGeneratorCpp.cpp"
  append(L"\n");
  append(L"        for (--end; (");
                                                            #line 486 "CodeGeneratorCpp.cpp.template"
                                                                    if (variable("useGlr").boolean())
                                                                    {
                                                            #line 910 "CodeGeneratorCpp.cpp"
  append(L"parser->");
                                                            #line 488 "CodeGeneratorCpp.cpp.template"
                                                                    }
                                                            #line 914 "CodeGeneratorCpp.cpp"
  append(L"input[end] & 0xc0) == 0x80; --end) ;");
                                                            #line 489 "CodeGeneratorCpp.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 920 "CodeGeneratorCpp.cpp"
  append(L"\n");
  append(L"      {\n");
  append(L"        int c1 = ");
                                                            #line 495 "CodeGeneratorCpp.cpp.template"
                                                                    if (variable("useGlr").boolean())
                                                                    {
                                                            #line 927 "CodeGeneratorCpp.cpp"
  append(L"parser->");
                                                            #line 497 "CodeGeneratorCpp.cpp.template"
                                                                    }
                                                            #line 931 "CodeGeneratorCpp.cpp"
  append(L"input[--end];\n");
  append(L"        if (c1 >= 0xdc00 && c1 < 0xe000) --end;\n");
  append(L"      }");
                                                            #line 500 "CodeGeneratorCpp.cpp.template"
                                                                  }
                                                            #line 937 "CodeGeneratorCpp.cpp"
  append(L"\n");
  append(L"    }\n");
  append(L"    else\n");
  append(L"    {\n");
  append(L"      end -= result >> ");
                                                            #line 505 "CodeGeneratorCpp.cpp.template"
                                                                  print(lowBits);
                                                            #line 945 "CodeGeneratorCpp.cpp"
  append(L";\n");
  append(L"    }\n");
                                                            #line 508 "CodeGeneratorCpp.cpp.template"
                                                                }
                                                                if (hasFixedTokenLength)
                                                                {
                                                                  --indent;
                                                            #line 953 "CodeGeneratorCpp.cpp"
  append(L"  }\n");
                                                            #line 513 "CodeGeneratorCpp.cpp.template"
                                                                }
                                                              }
                                                            #line 958 "CodeGeneratorCpp.cpp"
  append(L"\n");
  append(L"    if (");
                                                            #line 517 "CodeGeneratorCpp.cpp.template"
                                                              if (variable("useGlr").boolean())
                                                              {
                                                            #line 964 "CodeGeneratorCpp.cpp"
  append(L"parser->");
                                                            #line 519 "CodeGeneratorCpp.cpp.template"
                                                              }
                                                            #line 968 "CodeGeneratorCpp.cpp"
  append(L"input[begin] == 0) end = begin;");
                                                            #line 520 "CodeGeneratorCpp.cpp.template"
                                                              if (variable("trace").boolean())
                                                              {
                                                            #line 973 "CodeGeneratorCpp.cpp"
  append(L"\n");
  append(L"    fprintf(stderr, \"    <done result=\\\"%s\\\" begin=\\\"%d\\\" end=\\\"%d\\\"/>\\n\", ");
                                                            #line 524 "CodeGeneratorCpp.cpp.template"
                                                                if (! utf8)
                                                                {
                                                            #line 979 "CodeGeneratorCpp.cpp"
  append(L"Utf8Encoder::encode(");
                                                            #line 526 "CodeGeneratorCpp.cpp.template"
                                                                }
                                                            #line 983 "CodeGeneratorCpp.cpp"
  append(L"xmlEscape(TOKEN[(result & ");
                                                            #line 527 "CodeGeneratorCpp.cpp.template"
                                                                print(Math::powerof(2, variable("tokencodeBits").integer()) - 1);
                                                            #line 987 "CodeGeneratorCpp.cpp"
  append(L") - 1], 0).c_str()");
                                                            #line 528 "CodeGeneratorCpp.cpp.template"
                                                                if (! utf8)
                                                                {
                                                            #line 992 "CodeGeneratorCpp.cpp"
  append(L").c_str()");
                                                            #line 530 "CodeGeneratorCpp.cpp.template"
                                                                }
                                                            #line 996 "CodeGeneratorCpp.cpp"
  append(L", begin, end);\n");
  append(L"    fprintf(stderr, \"  </tokenize>\\n\");");
                                                            #line 532 "CodeGeneratorCpp.cpp.template"
                                                              }
                                                            #line 1001 "CodeGeneratorCpp.cpp"
  append(L"\n");
  append(L"    return (result & ");
                                                            #line 534 "CodeGeneratorCpp.cpp.template"
                                                              print(Math::powerof(2, variable("tokencodeBits").integer()) - 1);
                                                            #line 1006 "CodeGeneratorCpp.cpp"
  append(L") - 1;\n");
  append(L"  }\n");
                                                            #line 538 "CodeGeneratorCpp.cpp.template"
                                                              if (! variable("embedded").boolean())
                                                              {
                                                            #line 1012 "CodeGeneratorCpp.cpp"
  append(L"\n");
  append(L"  String[] getExpectedTokenSet()\n");
  append(L"  {\n");
  append(L"    return getTokenSet(- state);\n");
  append(L"  }\n");
                                                            #line 545 "CodeGeneratorCpp.cpp.template"
                                                              }
                                                            }

                                                            void CodeGeneratorCpp::generateStaticCode()
                                                            {
                                                              bool utf8 = 0 == strcmp("char *", variable("stringType").string());
                                                              if (defined("gtbits"))
                                                              {
                                                            #line 1027 "CodeGeneratorCpp.cpp"
  append(L"\n");
  append(L"  static int goTo(int nonterminal, int state)\n");
  append(L"  {\n");
                                                            #line 556 "CodeGeneratorCpp.cpp.template"
                                                                compressedMap2dAccessor("nonterminal", "state", variable("gtcols").integer(),
                                                                                           4, "i", "return ", "GOTO", &variable("gtbits").integer());
                                                            #line 1034 "CodeGeneratorCpp.cpp"
  append(L"\n");
  append(L"  }\n");
                                                            #line 560 "CodeGeneratorCpp.cpp.template"
                                                              }
                                                              if (variable("trace").boolean())
                                                              {
                                                            #line 1041 "CodeGeneratorCpp.cpp"
  append(L"\n");
  append(L"  static std::");
                                                            #line 564 "CodeGeneratorCpp.cpp.template"
                                                                print(utf8 ? "" : "w");
                                                            #line 1046 "CodeGeneratorCpp.cpp"
  append(L"string xmlEscape(const ");
                                                            #line 565 "CodeGeneratorCpp.cpp.template"
                                                                print(utf8 ? "char" : "wchar_t");
                                                            #line 1050 "CodeGeneratorCpp.cpp"
  append(L" *string, size_t size)\n");
  append(L"  {\n");
  append(L"    std::");
                                                            #line 568 "CodeGeneratorCpp.cpp.template"
                                                                print(utf8 ? "" : "w");
                                                            #line 1056 "CodeGeneratorCpp.cpp"
  append(L"string result;\n");
  append(L"    if (size == 0) size = ");
                                                            #line 570 "CodeGeneratorCpp.cpp.template"
                                                                print(utf8 ? L"str" : L"wcs");
                                                            #line 1061 "CodeGeneratorCpp.cpp"
  append(L"len(string);\n");
  append(L"    for (size_t i = 0; i < size; ++i)\n");
  append(L"    {\n");
  append(L"      const ");
                                                            #line 574 "CodeGeneratorCpp.cpp.template"
                                                                print(utf8 ? "char" : "wchar_t");
                                                            #line 1068 "CodeGeneratorCpp.cpp"
  append(L" c = string[i];\n");
  append(L"      switch (c)\n");
  append(L"      {\n");
  append(L"      case 0: break;\n");
  append(L"      case '&': result += ");
                                                            #line 579 "CodeGeneratorCpp.cpp.template"
                                                                print(utf8 ? "" : "L");
                                                            #line 1076 "CodeGeneratorCpp.cpp"
  append(L"\"&amp;\"; break;\n");
  append(L"      case '<': result += ");
                                                            #line 581 "CodeGeneratorCpp.cpp.template"
                                                                print(utf8 ? "" : "L");
                                                            #line 1081 "CodeGeneratorCpp.cpp"
  append(L"\"&lt;\"; break;\n");
  append(L"      case '\"': result += ");
                                                            #line 583 "CodeGeneratorCpp.cpp.template"
                                                                print(utf8 ? "" : "L");
                                                            #line 1086 "CodeGeneratorCpp.cpp"
  append(L"\"&quot;\"; break;\n");
  append(L"      default: result += c;\n");
  append(L"      }\n");
  append(L"    }\n");
  append(L"    return result;\n");
  append(L"  }\n");
                                                            #line 590 "CodeGeneratorCpp.cpp.template"
                                                              }
                                                            #line 1095 "CodeGeneratorCpp.cpp"
  append(L"\n");
  append(L"  static void getTokenSet(int tokenSetId, const ");
                                                            #line 592 "CodeGeneratorCpp.cpp.template"
                                                              print(variable("stringType").string());
                                                            #line 1100 "CodeGeneratorCpp.cpp"
  append(L"*set, int size)\n");
  append(L"  {\n");
  append(L"    int s = tokenSetId < 0 ? - tokenSetId : INITIAL[tokenSetId] & ");
                                                            #line 596 "CodeGeneratorCpp.cpp.template"
                                                              print(Math::powerof(2, variable("stateCodeBits").integer()) - 1);
                                                            #line 1106 "CodeGeneratorCpp.cpp"
  append(L";\n");
  append(L"    for (int i = 0; i < ");
                                                            #line 598 "CodeGeneratorCpp.cpp.template"
                                                              print(variable("t1").size);
                                                            #line 1111 "CodeGeneratorCpp.cpp"
  append(L"; i += 32)\n");
  append(L"    {\n");
  append(L"      int j = i;\n");
  append(L"      for (unsigned int f = ec(i >> 5, s); f != 0; f >>= 1, ++j)\n");
  append(L"      {\n");
  append(L"        if ((f & 1) != 0)\n");
  append(L"        {\n");
  append(L"          if (size > 1)\n");
  append(L"          {\n");
  append(L"            set[0] = TOKEN[j];\n");
  append(L"            ++set;\n");
  append(L"            --size;\n");
  append(L"          }\n");
  append(L"        }\n");
  append(L"      }\n");
  append(L"    }\n");
  append(L"    if (size > 0)\n");
  append(L"    {\n");
  append(L"      set[0] = 0;\n");
  append(L"    }\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  static int ec(int t, int s)\n");
  append(L"  {\n");
  append(L"    int i0 = t * ");
                                                            #line 623 "CodeGeneratorCpp.cpp.template"
                                                              print(variable("transitionStateCount").integer());
                                                            #line 1139 "CodeGeneratorCpp.cpp"
  append(L" + s - 1;\n");
                                                            #line 625 "CodeGeneratorCpp.cpp.template"
                                                              compressedMapAccessor(4, "i", "return ", "EXPECTED", &variable("t0bits").integer());
                                                            #line 1143 "CodeGeneratorCpp.cpp"
  append(L"\n");
  append(L"  }\n");
                                                            #line 628 "CodeGeneratorCpp.cpp.template"
                                                              for (VarsInInsertionOrder::iterator a(varsInInsertionOrder.begin());
                                                                   a != varsInInsertionOrder.end(); ++a)
                                                                if (a->isArray() && a->size > 0 && a->hasType(CGVariable::INTEGER) && strlen(a->name) == 2)
                                                              {
                                                            #line 1151 "CodeGeneratorCpp.cpp"
  append(L"\n");
  append(L"  static const int ");
                                                            #line 633 "CodeGeneratorCpp.cpp.template"
                                                                print(a->longName);
                                                            #line 1156 "CodeGeneratorCpp.cpp"
  append(L"[];");
                                                            #line 634 "CodeGeneratorCpp.cpp.template"
                                                              }
                                                              for (VarsInInsertionOrder::iterator a(varsInInsertionOrder.begin());
                                                                   a != varsInInsertionOrder.end(); ++a)
                                                                if (a->isArray() && a->size > 0 && a->hasType(CGVariable::STRING) && strlen(a->name) == 2)
                                                              {
                                                            #line 1164 "CodeGeneratorCpp.cpp"
  append(L"\n");
  append(L"  static const ");
                                                            #line 640 "CodeGeneratorCpp.cpp.template"
                                                                print(variable("stringType").string());
                                                                print(a->longName);
                                                            #line 1170 "CodeGeneratorCpp.cpp"
  append(L"[];");
                                                            #line 642 "CodeGeneratorCpp.cpp.template"
                                                              }
                                                              if (! variable("embedded").boolean())
                                                              {
                                                            #line 1176 "CodeGeneratorCpp.cpp"
  append(L"\n");
  append(L"\n");
  append(L"  enum Token\n");
  append(L"  {\n");
  append(L"    ");
                                                            #line 649 "CodeGeneratorCpp.cpp.template"
                                                                const CGVariable &token = variable("token");
                                                                int w = (int) Format::width(token.size);
                                                                for (size_t i = 0; i < token.size; ++i)
                                                                {
                                                                  if (i)
                                                                  {
                                                            #line 1189 "CodeGeneratorCpp.cpp"
  append(L",\n");
  append(L"    ");
                                                            #line 656 "CodeGeneratorCpp.cpp.template"
                                                                  }
                                                            #line 1194 "CodeGeneratorCpp.cpp"
  append(L"/* ");
                                                            #line 657 "CodeGeneratorCpp.cpp.template"
                                                                  print(format.toString<char>(i, 10, w));
                                                            #line 1198 "CodeGeneratorCpp.cpp"
  append(L" */ ");
                                                            #line 658 "CodeGeneratorCpp.cpp.template"
                                                                  print(token.string(i));
                                                                }
                                                            #line 1203 "CodeGeneratorCpp.cpp"
  append(L"\n");
  append(L"  };");
                                                            #line 662 "CodeGeneratorCpp.cpp.template"
                                                              }
                                                            #line 1208 "CodeGeneratorCpp.cpp"
  append(L"\n");
  append(L"};\n");
                                                            #line 666 "CodeGeneratorCpp.cpp.template"
                                                              generateData();
                                                              if (variable("selfTest").boolean())
                                                              {
                                                            #line 1215 "CodeGeneratorCpp.cpp"
  append(L"\n");
  append(L"  void selfTest(int set, int tokenId)\n");
  append(L"  {\n");
  append(L"    String tokenString = TOKEN[tokenId];\n");
  append(L"    if (tokenString.startsWith(\"'\"))\n");
  append(L"    {\n");
  append(L"      System.out.print(\"testing(\" + set + \", \" + tokenId + \")...\");\n");
  append(L"      tokenString = tokenString.substring(1, tokenString.length() - 1);\n");
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
  append(L"  static void main(String[] args)\n");
  append(L"  {\n");
  append(L"    ");
                                                            #line 703 "CodeGeneratorCpp.cpp.template"
                                                              print(Format::acceptableName<CString>(variable("classname").string()).c_str());
                                                            #line 1253 "CodeGeneratorCpp.cpp"
  append(L" testee();\n");
  append(L"    for (int e = 0; e < ");
                                                            #line 705 "CodeGeneratorCpp.cpp.template"
                                                              print(variable("a0").size);
                                                            #line 1258 "CodeGeneratorCpp.cpp"
  append(L"; ++e)\n");
  append(L"    {\n");
  append(L"      int s = INITIAL[e] & ");
                                                            #line 708 "CodeGeneratorCpp.cpp.template"
                                                              print(Math::powerof(2, variable("stateCodeBits").integer()) - 1);
                                                            #line 1264 "CodeGeneratorCpp.cpp"
  append(L";\n");
  append(L"      for (int i = 0; i < ");
                                                            #line 710 "CodeGeneratorCpp.cpp.template"
                                                              print(variable("t1").size);
                                                            #line 1269 "CodeGeneratorCpp.cpp"
  append(L"; i += 32)\n");
  append(L"      {\n");
  append(L"        int j = i;\n");
  append(L"        for (int f = ec(i >> 5, s); f != 0; f >>>= 1, ++j)\n");
  append(L"        {\n");
  append(L"          if ((f & 1) != 0)\n");
  append(L"          {\n");
  append(L"            testee.selfTest(e, t);\n");
  append(L"          }\n");
  append(L"        }\n");
  append(L"      }\n");
  append(L"    }\n");
  append(L"  }\n");
                                                            #line 724 "CodeGeneratorCpp.cpp.template"
                                                              }
                                                            }

                                                            void CodeGeneratorCpp::generateData()
                                                            {
                                                              for (VarsInInsertionOrder::iterator a(varsInInsertionOrder.begin());
                                                                   a != varsInInsertionOrder.end(); ++a)
                                                                if (a->isArray() && a->size > 0 && a->hasType(CGVariable::INTEGER) && strlen(a->name) == 2)
                                                              {
                                                            #line 1293 "CodeGeneratorCpp.cpp"
  append(L"\n");
  append(L"const int ");
                                                            #line 734 "CodeGeneratorCpp.cpp.template"
                                                                print(Format::acceptableName<CString>(variable("classname").string()).c_str());
                                                            #line 1298 "CodeGeneratorCpp.cpp"
  append(L"::");
                                                            #line 735 "CodeGeneratorCpp.cpp.template"
                                                                print(a->longName);
                                                            #line 1302 "CodeGeneratorCpp.cpp"
  append(L"[] =\n");
  append(L"{");
                                                            #line 737 "CodeGeneratorCpp.cpp.template"
                                                                int w = (int) Format::width(a->size);
                                                                for (size_t j = 0; j < a->size; ++j)
                                                                {
                                                                  if (j == 0 || lineLength() + Format::width(a->integer(j)) + 2 > 119)
                                                                  {
                                                                    if (j) print(",");
                                                            #line 1312 "CodeGeneratorCpp.cpp"
  append(L"\n");
  append(L"/* ");
                                                            #line 744 "CodeGeneratorCpp.cpp.template"
                                                                    print(format.toString<char>(j, 10, w));
                                                            #line 1317 "CodeGeneratorCpp.cpp"
  append(L" */ ");
                                                            #line 745 "CodeGeneratorCpp.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 1323 "CodeGeneratorCpp.cpp"
  append(L", ");
                                                            #line 748 "CodeGeneratorCpp.cpp.template"
                                                                  }
                                                                  if (a->integer(j) != (int) 0x80000000)
                                                                  {
                                                                    print(a->integer(j));
                                                                  }
                                                                  else
                                                                  {
                                                            #line 1333 "CodeGeneratorCpp.cpp"
  append(L"(int) ");
                                                            #line 755 "CodeGeneratorCpp.cpp.template"
                                                                    print(format.toString<char>(a->integer(j), 16, 0, 0, "0x", "0123456789abcdef"));
                                                                  }
                                                                }
                                                            #line 1339 "CodeGeneratorCpp.cpp"
  append(L"\n");
  append(L"};\n");
                                                            #line 760 "CodeGeneratorCpp.cpp.template"
                                                              }
                                                              for (VarsInInsertionOrder::iterator a(varsInInsertionOrder.begin());
                                                                   a != varsInInsertionOrder.end(); ++a)
                                                                if (a->isArray() && a->size > 0 && a->hasType(CGVariable::STRING) && strlen(a->name) == 2)
                                                              {
                                                            #line 1348 "CodeGeneratorCpp.cpp"
  append(L"\n");
  append(L"const ");
                                                            #line 766 "CodeGeneratorCpp.cpp.template"
                                                                print(variable("stringType").string());
                                                                print(Format::acceptableName<CString>(variable("classname").string()).c_str());
                                                            #line 1354 "CodeGeneratorCpp.cpp"
  append(L"::");
                                                            #line 768 "CodeGeneratorCpp.cpp.template"
                                                                print(a->longName);
                                                            #line 1358 "CodeGeneratorCpp.cpp"
  append(L"[] =\n");
  append(L"{\n");
                                                            #line 771 "CodeGeneratorCpp.cpp.template"
                                                                for (size_t j = 0; j < a->size; ++j)
                                                                {
                                                                  if (j)
                                                                  {
                                                            #line 1366 "CodeGeneratorCpp.cpp"
  append(L",\n");
                                                            #line 776 "CodeGeneratorCpp.cpp.template"
                                                                  }
                                                            #line 1370 "CodeGeneratorCpp.cpp"
  append(L"  ");
                                                            #line 777 "CodeGeneratorCpp.cpp.template"
                                                                  print(variable("stringPrefix").string());
                                                            #line 1374 "CodeGeneratorCpp.cpp"
  append(L"\"");
                                                            #line 778 "CodeGeneratorCpp.cpp.template"
                                                                  const char *s = a->string(j);
                                                                  const char *c = s;
                                                                  for (; *c; ++c)
                                                                  {
                                                                    if (*c == '"' || *c == '\\')
                                                                    {
                                                                      print(s, c - s);
                                                                      print("\\");
                                                                      s = c;
                                                                    }
                                                                  }
                                                                  print(s, c - s);
                                                            #line 1389 "CodeGeneratorCpp.cpp"
  append(L"\"");
                                                            #line 790 "CodeGeneratorCpp.cpp.template"
                                                                  print(variable("stringSuffix").string());
                                                                }
                                                            #line 1394 "CodeGeneratorCpp.cpp"
  append(L"\n");
  append(L"};\n");
                                                            #line 794 "CodeGeneratorCpp.cpp.template"
                                                              }
                                                            }

// End
