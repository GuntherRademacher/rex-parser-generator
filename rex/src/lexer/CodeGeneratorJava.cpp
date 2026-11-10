// This file was generated on Mon Nov 9, 2026 21:32 (UTC+01) by REx v6.2-SNAPSHOT which is Copyright (c) 1979-2025 by Gunther Rademacher <grd@gmx.net>
// REx command line: CodeGeneratorJava.cpp.template
                                                            #line 1 "CodeGeneratorJava.cpp.template"
                                                            // generate CodeGeneratorJava.cpp using this command:
                                                            //
                                                            //   REx CodeGeneratorJava.cpp.template

                                                            #include "../common/Memory.hpp"

                                                            #include "CodeGenerator.hpp"

                                                            void CodeGeneratorJava::generateStaticCode()
                                                            {
                                                              const char *prefix = variable("useGlr").boolean() && targetLanguage != JAVA
                                                                                 ? "parser."
                                                                                 : "";
                                                              bool codepoints = targetLanguage == JAVA
                                                                             && variable("codepoints").boolean();
                                                              if (! variable("append").boolean() && ! variable("embedded").boolean())
                                                              {
                                                                if (*variable("package").string())
                                                                {
                                                            #line 24 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"package ");
                                                            #line 21 "CodeGeneratorJava.cpp.template"
                                                                  print(variable("package").string());
                                                            #line 29 "CodeGeneratorJava.cpp"
  append(L";\n");
                                                            #line 23 "CodeGeneratorJava.cpp.template"
                                                                }
                                                                if (variable("trace").boolean())
                                                                {
                                                            #line 35 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"import java.io.IOException;\n");
  append(L"import java.io.OutputStreamWriter;\n");
  append(L"import java.io.UnsupportedEncodingException;\n");
  append(L"import java.io.Writer;\n");
                                                            #line 31 "CodeGeneratorJava.cpp.template"
                                                                }
                                                            #line 43 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"public class ");
                                                            #line 33 "CodeGeneratorJava.cpp.template"
                                                                print(variable("classname").string());
                                                            #line 48 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"{\n");
                                                            #line 36 "CodeGeneratorJava.cpp.template"
                                                              }
                                                              if (variable("useGlr").boolean())
                                                              {
                                                                ++indent;
                                                              }
                                                              else
                                                              {
                                                            #line 59 "CodeGeneratorJava.cpp"
  append(L"  private ");
                                                            #line 43 "CodeGeneratorJava.cpp.template"
                                                                if (codepoints)
                                                                {
                                                            #line 64 "CodeGeneratorJava.cpp"
  append(L"int[]");
                                                            #line 45 "CodeGeneratorJava.cpp.template"
                                                                }
                                                                else if (targetLanguage == JAVA)
                                                                {
                                                            #line 70 "CodeGeneratorJava.cpp"
  append(L"CharSequence");
                                                            #line 48 "CodeGeneratorJava.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 76 "CodeGeneratorJava.cpp"
  append(L"String");
                                                            #line 51 "CodeGeneratorJava.cpp.template"
                                                                }
                                                            #line 80 "CodeGeneratorJava.cpp"
  append(L" input = null;");
                                                            #line 53 "CodeGeneratorJava.cpp.template"
                                                                if (! variable("nolexer").boolean())
                                                                {
                                                            #line 85 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"  private int size = 0;");
                                                            #line 56 "CodeGeneratorJava.cpp.template"
                                                                }
                                                              }
                                                            #line 91 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"  private int begin = 0;\n");
  append(L"  private int end = 0;");
                                                            #line 60 "CodeGeneratorJava.cpp.template"
                                                              if (variable("nolexer").boolean())
                                                              {
                                                                if (! variable("useGlr").boolean())
                                                                {
                                                            #line 100 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"  private Lexer lexer = null;");
                                                            #line 65 "CodeGeneratorJava.cpp.template"
                                                                }
                                                            #line 105 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"  private Token token = new Token();");
                                                            #line 67 "CodeGeneratorJava.cpp.template"
                                                              }
                                                              if (! variable("embedded").boolean())
                                                              {
                                                            #line 112 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"  private int state = 0;");
                                                            #line 71 "CodeGeneratorJava.cpp.template"
                                                              }
                                                              if (variable("trace").boolean() && ! variable("useGlr").boolean())
                                                              {
                                                                if (targetLanguage == JAVA)
                                                                {
                                                            #line 121 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"  private Writer err;\n");
  append(L"  {\n");
  append(L"    try\n");
  append(L"    {\n");
  append(L"      err = new OutputStreamWriter(System.err, \"UTF-8\");\n");
  append(L"    }\n");
  append(L"    catch (UnsupportedEncodingException uee)\n");
  append(L"    {}\n");
  append(L"  }");
                                                            #line 85 "CodeGeneratorJava.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 136 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"  private TextWriter err = Console.Error;");
                                                            #line 89 "CodeGeneratorJava.cpp.template"
                                                                }
                                                              }
                                                            #line 142 "CodeGeneratorJava.cpp"
  append(L"\n");
                                                            #line 92 "CodeGeneratorJava.cpp.template"
                                                              if (! variable("embedded").boolean())
                                                              {
                                                                if (codepoints)
                                                                {
                                                            #line 149 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"  public void init(int[] codepoints)\n");
  append(L"  {\n");
  append(L"    input = codepoints;\n");
  append(L"    size = codepoints.length;\n");
  append(L"    end = 0;\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  public void init(String string)\n");
  append(L"  {\n");
  append(L"    init(string.codePoints().toArray());\n");
  append(L"  }");
                                                            #line 107 "CodeGeneratorJava.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 166 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"  public void init(String string)\n");
  append(L"  {\n");
  append(L"    input = string;\n");
  append(L"    size = string.length();\n");
  append(L"    end = 0;\n");
  append(L"  }");
                                                            #line 116 "CodeGeneratorJava.cpp.template"
                                                                }
                                                            #line 176 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"\n");
  append(L"  public int getOffset() {return begin;}\n");
  append(L"  public int getSize()   {return end - begin;}\n");
  append(L"  public int getState()  {return state;}\n");
  append(L"\n");
  append(L"  public int match(int tokenSetId, String string)\n");
  append(L"  {\n");
  append(L"    init(string);\n");
  append(L"    return match(tokenSetId);\n");
  append(L"  }");
                                                            #line 127 "CodeGeneratorJava.cpp.template"
                                                                if (codepoints)
                                                                {
                                                            #line 191 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"  public int match(int tokenSetId, int[] codepoints)\n");
  append(L"  {\n");
  append(L"    init(codepoints);\n");
  append(L"    return match(tokenSetId);\n");
  append(L"  }");
                                                            #line 134 "CodeGeneratorJava.cpp.template"
                                                                }
                                                            #line 200 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"\n");
  append(L"  public");
                                                            #line 137 "CodeGeneratorJava.cpp.template"
                                                              }
                                                              else
                                                              {
                                                                if (variable("lrparser").boolean() ||
                                                                    variable("tables").boolean())
                                                                {
                                                            #line 211 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 144 "CodeGeneratorJava.cpp.template"
                                                                  print(variable("useGlr").boolean() ? "public" : "private");
                                                            #line 216 "CodeGeneratorJava.cpp"
  append(L" int predict(int dpi)");
                                                            #line 145 "CodeGeneratorJava.cpp.template"
                                                                  predict();
                                                                }
                                                            #line 221 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"  private");
                                                            #line 148 "CodeGeneratorJava.cpp.template"
                                                              }
                                                            #line 226 "CodeGeneratorJava.cpp"
  append(L" int match(int tokenSetId)\n");
  append(L"  {");
                                                            #line 150 "CodeGeneratorJava.cpp.template"
                                                              if (variable("nolexer").boolean())
                                                              {
                                                            #line 232 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"    token.begin = end;\n");
  append(L"    lexer.match(tokenSetId, token);\n");
  append(L"    begin = token.begin;\n");
  append(L"    end = token.end;\n");
  append(L"    return token.code >= 0\n");
  append(L"         ? token.code\n");
  append(L"         : error(begin, end, - tokenSetId, -1, -1);\n");
  append(L"  }\n");
                                                            #line 161 "CodeGeneratorJava.cpp.template"
                                                              }
                                                              else
                                                              {
                                                                int lookahead = variable("maxcontextlength").integer();
                                                                bool hasFixedTokenLength = variable("hasfixedtokenlength").boolean();
                                                                int lowBits;
                                                                const char *flags = getenv("FLAGS");
                                                                bool hack = flags && strchr(flags, 'H');

                                                                if (variable("trace").boolean())
                                                                {
                                                            #line 254 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 173 "CodeGeneratorJava.cpp.template"
                                                                  if (variable("useGlr").boolean() && targetLanguage != JAVA)
                                                                  {
                                                            #line 260 "CodeGeneratorJava.cpp"
  append(L"parser.");
                                                            #line 175 "CodeGeneratorJava.cpp.template"
                                                                  }
                                                            #line 264 "CodeGeneratorJava.cpp"
  append(L"writeTrace(\"  <tokenize ");
                                                            #line 176 "CodeGeneratorJava.cpp.template"
                                                                  if (variable("useGlr").boolean())
                                                                  {
                                                            #line 269 "CodeGeneratorJava.cpp"
  append(L"thread=\\\"\" + id + \"\\\" ");
                                                            #line 178 "CodeGeneratorJava.cpp.template"
                                                                  }
                                                            #line 273 "CodeGeneratorJava.cpp"
  append(L"tokenset=\\\"\" + tokenSetId + \"\\\">\\n\");\n");
                                                            #line 180 "CodeGeneratorJava.cpp.template"
                                                                }
                                                                if (lookahead && ! codepoints)
                                                                {
                                                                  if (targetLanguage == JAVA)
                                                                  {
                                                            #line 281 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"    boolean nonbmp = false;");
                                                            #line 186 "CodeGeneratorJava.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 288 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"    bool nonbmp = false;");
                                                            #line 190 "CodeGeneratorJava.cpp.template"
                                                                  }
                                                                }
                                                            #line 294 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"    begin = end;\n");
  append(L"    int current = end;\n");
  append(L"    int result = INITIAL[tokenSetId];");
                                                            #line 195 "CodeGeneratorJava.cpp.template"
                                                                if (variable("embedded").boolean() && (variable("trace").boolean() || ! variable("useGlr").boolean()))
                                                                {
                                                            #line 302 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"    int state = 0;");
                                                            #line 198 "CodeGeneratorJava.cpp.template"
                                                                }
                                                            #line 307 "CodeGeneratorJava.cpp"
  append(L"\n");
                                                            #line 200 "CodeGeneratorJava.cpp.template"
                                                                if (variable("trace").boolean())
                                                                {
                                                            #line 312 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 203 "CodeGeneratorJava.cpp.template"
                                                                  if (variable("useGlr").boolean() && targetLanguage != JAVA)
                                                                  {
                                                            #line 318 "CodeGeneratorJava.cpp"
  append(L"parser.");
                                                            #line 205 "CodeGeneratorJava.cpp.template"
                                                                  }
                                                            #line 322 "CodeGeneratorJava.cpp"
  append(L"writeTrace(\"    <next state=\\\"\" + (result & ");
                                                            #line 206 "CodeGeneratorJava.cpp.template"
                                                                  print(Math::powerof(2, variable("stateCodeBits").integer()) - 1);
                                                            #line 326 "CodeGeneratorJava.cpp"
  append(L") + \"\\\"\");");
                                                            #line 207 "CodeGeneratorJava.cpp.template"
                                                                }
                                                            #line 330 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"    for (int code = result & ");
                                                            #line 209 "CodeGeneratorJava.cpp.template"
                                                                print(Math::powerof(2, variable("stateCodeBits").integer()) - 1);
                                                            #line 335 "CodeGeneratorJava.cpp"
  append(L"; code != 0; )\n");
  append(L"    {\n");
  append(L"      int charclass;\n");
  append(L"      int c0 = current < ");
                                                            #line 213 "CodeGeneratorJava.cpp.template"
                                                                print(prefix);
                                                            #line 342 "CodeGeneratorJava.cpp"
  append(L"size ? ");
                                                            #line 214 "CodeGeneratorJava.cpp.template"
                                                                print(prefix);
                                                            #line 346 "CodeGeneratorJava.cpp"
  append(L"input");
                                                            #line 215 "CodeGeneratorJava.cpp.template"
                                                                if (targetLanguage == JAVA && ! codepoints)
                                                                {
                                                            #line 351 "CodeGeneratorJava.cpp"
  append(L".charAt(current)");
                                                            #line 217 "CodeGeneratorJava.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 357 "CodeGeneratorJava.cpp"
  append(L"[current]");
                                                            #line 220 "CodeGeneratorJava.cpp.template"
                                                                }
                                                            #line 361 "CodeGeneratorJava.cpp"
  append(L" : 0;");
                                                            #line 221 "CodeGeneratorJava.cpp.template"
                                                                if (variable("trace").boolean())
                                                                {
                                                            #line 366 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"      ");
                                                            #line 224 "CodeGeneratorJava.cpp.template"
                                                                  if (variable("useGlr").boolean() && targetLanguage != JAVA)
                                                                  {
                                                            #line 372 "CodeGeneratorJava.cpp"
  append(L"parser.");
                                                            #line 226 "CodeGeneratorJava.cpp.template"
                                                                  }
                                                            #line 376 "CodeGeneratorJava.cpp"
  append(L"writeTrace(\" offset=\\\"\" + current + \"\\\"\");");
                                                            #line 227 "CodeGeneratorJava.cpp.template"
                                                                }
                                                            #line 380 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"      ++current;\n");
  append(L"      if (c0 < 0x");
                                                            #line 230 "CodeGeneratorJava.cpp.template"
                                                                print(format.toString<char>(variable("simplifiedCodeMap").integer(), 16, 0, 0, 0, "0123456789abcdef"));
                                                            #line 386 "CodeGeneratorJava.cpp"
  append(L")\n");
  append(L"      {");
                                                            #line 232 "CodeGeneratorJava.cpp.template"
                                                                if (variable("trace").boolean())
                                                                {
                                                            #line 392 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"        if (c0 >= 32 && c0 <= 126)\n");
  append(L"        {\n");
  append(L"          ");
                                                            #line 237 "CodeGeneratorJava.cpp.template"
                                                                  if (variable("useGlr").boolean() && targetLanguage != JAVA)
                                                                  {
                                                            #line 400 "CodeGeneratorJava.cpp"
  append(L"parser.");
                                                            #line 239 "CodeGeneratorJava.cpp.template"
                                                                  }
                                                            #line 404 "CodeGeneratorJava.cpp"
  append(L"writeTrace(\" char=\\\"\" + xmlEscape(");
                                                            #line 240 "CodeGeneratorJava.cpp.template"
                                                                  if (targetLanguage == JAVA)
                                                                  {
                                                            #line 409 "CodeGeneratorJava.cpp"
  append(L"String.valueOf((char) c0)");
                                                            #line 243 "CodeGeneratorJava.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 415 "CodeGeneratorJava.cpp"
  append(L"((char) c0).ToString()");
                                                            #line 247 "CodeGeneratorJava.cpp.template"
                                                                  }
                                                            #line 419 "CodeGeneratorJava.cpp"
  append(L") + \"\\\"\");\n");
  append(L"        }");
                                                            #line 249 "CodeGeneratorJava.cpp.template"
                                                                }
                                                            #line 424 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"        charclass = MAP0[c0];\n");
  append(L"      }\n");
  append(L"      else if (c0 < 0x");
                                                            #line 253 "CodeGeneratorJava.cpp.template"
                                                                print(format.toString<char>(variable("uncompressedMapSize").integer(), 16, 0, 0, 0, "0123456789abcdef"));
                                                            #line 431 "CodeGeneratorJava.cpp"
  append(L")\n");
  append(L"      {\n");
                                                            #line 256 "CodeGeneratorJava.cpp.template"
                                                                compressedMapAccessor(8, "c", "charclass = ", "MAP1", &variable("m1bits").integer());
                                                            #line 436 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"      }\n");
  append(L"      else\n");
  append(L"      {");
                                                            #line 260 "CodeGeneratorJava.cpp.template"
                                                                if (variable("m2").size == 0)
                                                                {
                                                            #line 444 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"        charclass = 0;");
                                                            #line 263 "CodeGeneratorJava.cpp.template"
                                                                }
                                                                else
                                                                {
                                                                  if (! codepoints)
                                                                  {
                                                            #line 453 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"        if (");
                                                            #line 269 "CodeGeneratorJava.cpp.template"
                                                                    if (variable("uncompressedMapSize").integer() != 0xd800)
                                                                    {
                                                            #line 459 "CodeGeneratorJava.cpp"
  append(L"c0 >= 0xd800 && ");
                                                            #line 271 "CodeGeneratorJava.cpp.template"
                                                                    }
                                                            #line 463 "CodeGeneratorJava.cpp"
  append(L"c0 < 0xdc00)\n");
  append(L"        {\n");
  append(L"          int c1 = current < ");
                                                            #line 274 "CodeGeneratorJava.cpp.template"
                                                                    print(prefix);
                                                            #line 469 "CodeGeneratorJava.cpp"
  append(L"size ? ");
                                                            #line 275 "CodeGeneratorJava.cpp.template"
                                                                    print(prefix);
                                                            #line 473 "CodeGeneratorJava.cpp"
  append(L"input");
                                                            #line 276 "CodeGeneratorJava.cpp.template"
                                                                    if (targetLanguage == JAVA)
                                                                    {
                                                            #line 478 "CodeGeneratorJava.cpp"
  append(L".charAt(current)");
                                                            #line 278 "CodeGeneratorJava.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 484 "CodeGeneratorJava.cpp"
  append(L"[current]");
                                                            #line 281 "CodeGeneratorJava.cpp.template"
                                                                    }
                                                            #line 488 "CodeGeneratorJava.cpp"
  append(L" : 0;\n");
  append(L"          if (c1 >= 0xdc00 && c1 < 0xe000)\n");
  append(L"          {");
                                                            #line 284 "CodeGeneratorJava.cpp.template"
                                                                    if (lookahead)
                                                                    {
                                                            #line 495 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"            nonbmp = true;");
                                                            #line 287 "CodeGeneratorJava.cpp.template"
                                                                    }
                                                            #line 500 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"            ++current;\n");
  append(L"            c0 = ((c0 & 0x3ff) << 10) + (c1 & 0x3ff) + 0x10000;\n");
  append(L"          }\n");
  append(L"        }\n");
                                                            #line 293 "CodeGeneratorJava.cpp.template"
                                                                  }
                                                            #line 508 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"        int lo = 0, hi = ");
                                                            #line 295 "CodeGeneratorJava.cpp.template"
                                                                  print(variable("m2").size / 3 - 1);
                                                            #line 513 "CodeGeneratorJava.cpp"
  append(L";\n");
  append(L"        for (int m = ");
                                                            #line 297 "CodeGeneratorJava.cpp.template"
                                                                  print((variable("m2").size / 3) >> 1);
                                                            #line 518 "CodeGeneratorJava.cpp"
  append(L"; ; m = (hi + lo) >> 1)\n");
  append(L"        {\n");
  append(L"          if (MAP2[m] > c0) {hi = m - 1;}\n");
  append(L"          else if (MAP2[");
                                                            #line 301 "CodeGeneratorJava.cpp.template"
                                                                  print(variable("m2").size / 3);
                                                            #line 525 "CodeGeneratorJava.cpp"
  append(L" + m] < c0) {lo = m + 1;}\n");
  append(L"          else {charclass = MAP2[");
                                                            #line 303 "CodeGeneratorJava.cpp.template"
                                                                  print(variable("m2").size / 3 * 2);
                                                            #line 530 "CodeGeneratorJava.cpp"
  append(L" + m]; break;}\n");
  append(L"          if (lo > hi) {charclass = 0; break;}\n");
  append(L"        }");
                                                            #line 306 "CodeGeneratorJava.cpp.template"
                                                                }
                                                            #line 536 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"      }");
                                                            #line 308 "CodeGeneratorJava.cpp.template"
                                                                if (variable("trace").boolean())
                                                                {
                                                            #line 542 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"      ");
                                                            #line 311 "CodeGeneratorJava.cpp.template"
                                                                  if (variable("useGlr").boolean() && targetLanguage != JAVA)
                                                                  {
                                                            #line 548 "CodeGeneratorJava.cpp"
  append(L"parser.");
                                                            #line 313 "CodeGeneratorJava.cpp.template"
                                                                  }
                                                            #line 552 "CodeGeneratorJava.cpp"
  append(L"writeTrace(\" codepoint=\\\"\" + c0 + \"\\\" class=\\\"\" + charclass + \"\\\"\");");
                                                            #line 315 "CodeGeneratorJava.cpp.template"
                                                                }
                                                            #line 556 "CodeGeneratorJava.cpp"
  append(L"\n");
                                                            #line 317 "CodeGeneratorJava.cpp.template"
                                                                if (variable("trace").boolean() || ! variable("useGlr").boolean())
                                                                {
                                                            #line 561 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"      state = code;");
                                                            #line 320 "CodeGeneratorJava.cpp.template"
                                                                }
                                                            #line 566 "CodeGeneratorJava.cpp"
  append(L"\n");
                                                            #line 322 "CodeGeneratorJava.cpp.template"
                                                                compressedMap2dAccessor("code - 1", "charclass", variable("a1cols").integer(),
                                                                                           6, "i", "code = ", "TRANSITION", &variable("a1bits").integer());
                                                            #line 571 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"\n");
  append(L"      if (code > ");
                                                            #line 326 "CodeGeneratorJava.cpp.template"
                                                                print(Math::powerof(2, variable("stateCodeBits").integer()) - 1);
                                                            #line 577 "CodeGeneratorJava.cpp"
  append(L")\n");
  append(L"      {\n");
  append(L"        result = code;");
                                                            #line 329 "CodeGeneratorJava.cpp.template"
                                                                if (variable("trace").boolean())
                                                                {
                                                            #line 584 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"        ");
                                                            #line 332 "CodeGeneratorJava.cpp.template"
                                                                  if (variable("useGlr").boolean() && targetLanguage != JAVA)
                                                                  {
                                                            #line 590 "CodeGeneratorJava.cpp"
  append(L"parser.");
                                                            #line 334 "CodeGeneratorJava.cpp.template"
                                                                  }
                                                            #line 594 "CodeGeneratorJava.cpp"
  append(L"writeTrace(\" result=\\\"\" + xmlEscape(TOKEN[((result >> ");
                                                            #line 335 "CodeGeneratorJava.cpp.template"
                                                                  print(variable("stateCodeBits").integer());
                                                            #line 598 "CodeGeneratorJava.cpp"
  append(L") & ");
                                                            #line 337 "CodeGeneratorJava.cpp.template"
                                                                  print(Math::powerof(2, variable("tokencodeBits").integer()) - 1);
                                                            #line 602 "CodeGeneratorJava.cpp"
  append(L") - 1]) + \"\\\"\");");
                                                            #line 339 "CodeGeneratorJava.cpp.template"
                                                                  if (lookahead || hasFixedTokenLength)
                                                                  {
                                                                    int contextOffset = variable("stateCodeBits").integer()
                                                                                      + variable("tokencodeBits").integer();
                                                                    int sizeOffset = contextOffset
                                                                                   + (hasFixedTokenLength ? 1 : 0);
                                                                    if (hasFixedTokenLength)
                                                                    {
                                                            #line 613 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"        if ((result & ");
                                                            #line 348 "CodeGeneratorJava.cpp.template"
                                                                      print(Math::powerof(2, contextOffset));
                                                            #line 618 "CodeGeneratorJava.cpp"
  append(L") > 0)\n");
  append(L"        {\n");
  append(L"          ");
                                                            #line 351 "CodeGeneratorJava.cpp.template"
                                                                      if (variable("useGlr").boolean() && targetLanguage != JAVA)
                                                                      {
                                                            #line 625 "CodeGeneratorJava.cpp"
  append(L"parser.");
                                                            #line 353 "CodeGeneratorJava.cpp.template"
                                                                      }
                                                            #line 629 "CodeGeneratorJava.cpp"
  append(L"writeTrace(\" token-size=\\\"\" + (result >> ");
                                                            #line 354 "CodeGeneratorJava.cpp.template"
                                                                      print(sizeOffset);
                                                            #line 633 "CodeGeneratorJava.cpp"
  append(L") + \"\\\"\");\n");
  append(L"        }\n");
  append(L"        else ");
                                                            #line 357 "CodeGeneratorJava.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 641 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"        ");
                                                            #line 361 "CodeGeneratorJava.cpp.template"
                                                                    }
                                                            #line 646 "CodeGeneratorJava.cpp"
  append(L"if ((result >> ");
                                                            #line 362 "CodeGeneratorJava.cpp.template"
                                                                    print(sizeOffset);
                                                            #line 650 "CodeGeneratorJava.cpp"
  append(L") > 0)\n");
  append(L"        {\n");
  append(L"          ");
                                                            #line 365 "CodeGeneratorJava.cpp.template"
                                                                    if (variable("useGlr").boolean() && targetLanguage != JAVA)
                                                                    {
                                                            #line 657 "CodeGeneratorJava.cpp"
  append(L"parser.");
                                                            #line 367 "CodeGeneratorJava.cpp.template"
                                                                    }
                                                            #line 661 "CodeGeneratorJava.cpp"
  append(L"writeTrace(\" trailing-context-size=\\\"\" + (result >> ");
                                                            #line 368 "CodeGeneratorJava.cpp.template"
                                                                    print(sizeOffset);
                                                            #line 665 "CodeGeneratorJava.cpp"
  append(L") + \"\\\"\");\n");
  append(L"        }");
                                                            #line 370 "CodeGeneratorJava.cpp.template"
                                                                  }
                                                                }
                                                            #line 671 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"        code &= ");
                                                            #line 373 "CodeGeneratorJava.cpp.template"
                                                                print(Math::powerof(2, variable("stateCodeBits").integer()) - 1);
                                                            #line 676 "CodeGeneratorJava.cpp"
  append(L";\n");
  append(L"        end = current;\n");
  append(L"      }");
                                                            #line 376 "CodeGeneratorJava.cpp.template"
                                                                if (variable("trace").boolean())
                                                                {
                                                            #line 683 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"      ");
                                                            #line 379 "CodeGeneratorJava.cpp.template"
                                                                  if (variable("useGlr").boolean() && targetLanguage != JAVA)
                                                                  {
                                                            #line 689 "CodeGeneratorJava.cpp"
  append(L"parser.");
                                                            #line 381 "CodeGeneratorJava.cpp.template"
                                                                  }
                                                            #line 693 "CodeGeneratorJava.cpp"
  append(L"writeTrace(\"/>\\n\");\n");
  append(L"      if (code != 0)\n");
  append(L"      {\n");
  append(L"        ");
                                                            #line 385 "CodeGeneratorJava.cpp.template"
                                                                  if (variable("useGlr").boolean() && targetLanguage != JAVA)
                                                                  {
                                                            #line 701 "CodeGeneratorJava.cpp"
  append(L"parser.");
                                                            #line 387 "CodeGeneratorJava.cpp.template"
                                                                  }
                                                            #line 705 "CodeGeneratorJava.cpp"
  append(L"writeTrace(\"    <next state=\\\"\" + code + \"\\\"\");\n");
  append(L"      }");
                                                            #line 389 "CodeGeneratorJava.cpp.template"
                                                                }
                                                            #line 710 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    result >>= ");
                                                            #line 393 "CodeGeneratorJava.cpp.template"
                                                                print(variable("stateCodeBits").integer());
                                                            #line 717 "CodeGeneratorJava.cpp"
  append(L";\n");
  append(L"    if (result == 0)\n");
  append(L"    {\n");
  append(L"      end = current - 1;");
                                                            #line 397 "CodeGeneratorJava.cpp.template"
                                                                if (! codepoints)
                                                                {
                                                            #line 725 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"      int c1 = end < ");
                                                            #line 400 "CodeGeneratorJava.cpp.template"
                                                                  print(prefix);
                                                            #line 730 "CodeGeneratorJava.cpp"
  append(L"size ? ");
                                                            #line 401 "CodeGeneratorJava.cpp.template"
                                                                  print(prefix);
                                                            #line 734 "CodeGeneratorJava.cpp"
  append(L"input");
                                                            #line 402 "CodeGeneratorJava.cpp.template"
                                                                  if (targetLanguage == JAVA)
                                                                  {
                                                            #line 739 "CodeGeneratorJava.cpp"
  append(L".charAt(end)");
                                                            #line 404 "CodeGeneratorJava.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 745 "CodeGeneratorJava.cpp"
  append(L"[end]");
                                                            #line 407 "CodeGeneratorJava.cpp.template"
                                                                  }
                                                            #line 749 "CodeGeneratorJava.cpp"
  append(L" : 0;\n");
  append(L"      if (c1 >= 0xdc00 && c1 < 0xe000)\n");
  append(L"      {\n");
  append(L"        --end;\n");
  append(L"      }");
                                                            #line 412 "CodeGeneratorJava.cpp.template"
                                                                }
                                                                if (variable("trace").boolean())
                                                                {
                                                            #line 759 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"      ");
                                                            #line 416 "CodeGeneratorJava.cpp.template"
                                                                  if (variable("useGlr").boolean() && targetLanguage != JAVA)
                                                                  {
                                                            #line 765 "CodeGeneratorJava.cpp"
  append(L"parser.");
                                                            #line 418 "CodeGeneratorJava.cpp.template"
                                                                  }
                                                            #line 769 "CodeGeneratorJava.cpp"
  append(L"writeTrace(\"    <fail begin=\\\"\" + begin + \"\\\" end=\\\"\" + end + \"\\\" state=\\\"\" + state + \"\\\"/>\\n\");\n");
  append(L"      ");
                                                            #line 420 "CodeGeneratorJava.cpp.template"
                                                                  if (variable("useGlr").boolean() && targetLanguage != JAVA)
                                                                  {
                                                            #line 775 "CodeGeneratorJava.cpp"
  append(L"parser.");
                                                            #line 422 "CodeGeneratorJava.cpp.template"
                                                                  }
                                                            #line 779 "CodeGeneratorJava.cpp"
  append(L"writeTrace(\"  </tokenize>\\n\");");
                                                            #line 423 "CodeGeneratorJava.cpp.template"
                                                                }
                                                                if (variable("embedded").boolean())
                                                                {
                                                                  if (variable("useGlr").boolean())
                                                                  {
                                                            #line 787 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"      end = begin;\n");
  append(L"      return -1;");
                                                            #line 430 "CodeGeneratorJava.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 795 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"      return error(begin, end, state, -1, -1);");
                                                            #line 434 "CodeGeneratorJava.cpp.template"
                                                                  }
                                                                }
                                                            #line 801 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"    }");
                                                            #line 437 "CodeGeneratorJava.cpp.template"
                                                                lowBits = variable("tokencodeBits").integer();
                                                                if (hasFixedTokenLength && ! lookahead)
                                                                {
                                                            #line 808 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"    else if ((result & ");
                                                            #line 441 "CodeGeneratorJava.cpp.template"
                                                                  print(Math::powerof(2, lowBits));
                                                                  ++lowBits;
                                                            #line 814 "CodeGeneratorJava.cpp"
  append(L") != 0)\n");
  append(L"    {\n");
  append(L"      end = begin;\n");
  append(L"    }");
                                                            #line 446 "CodeGeneratorJava.cpp.template"
                                                                }
                                                                else
                                                                {
                                                                  if (hasFixedTokenLength)
                                                                  {
                                                            #line 825 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"    else if ((result & ");
                                                            #line 452 "CodeGeneratorJava.cpp.template"
                                                                    print(Math::powerof(2, lowBits));
                                                                    ++lowBits;
                                                            #line 831 "CodeGeneratorJava.cpp"
  append(L") != 0)\n");
  append(L"    {\n");
  append(L"      end = begin;");
                                                            #line 456 "CodeGeneratorJava.cpp.template"
                                                                    if (codepoints)
                                                                    {
                                                            #line 838 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"      end += (result >> ");
                                                            #line 459 "CodeGeneratorJava.cpp.template"
                                                                      print(lowBits);
                                                            #line 843 "CodeGeneratorJava.cpp"
  append(L");");
                                                            #line 460 "CodeGeneratorJava.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 849 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"      if (nonbmp)\n");
  append(L"      {\n");
  append(L"        for (int i = result >> ");
                                                            #line 466 "CodeGeneratorJava.cpp.template"
                                                                      print(lowBits);
                                                            #line 856 "CodeGeneratorJava.cpp"
  append(L"; i > 0; --i)\n");
  append(L"        {\n");
  append(L"          int c1 = end < ");
                                                            #line 469 "CodeGeneratorJava.cpp.template"
                                                                      print(prefix);
                                                            #line 862 "CodeGeneratorJava.cpp"
  append(L"size ? ");
                                                            #line 470 "CodeGeneratorJava.cpp.template"
                                                                      print(prefix);
                                                            #line 866 "CodeGeneratorJava.cpp"
  append(L"input");
                                                            #line 471 "CodeGeneratorJava.cpp.template"
                                                                      if (targetLanguage == JAVA)
                                                                      {
                                                            #line 871 "CodeGeneratorJava.cpp"
  append(L".charAt(end)");
                                                            #line 473 "CodeGeneratorJava.cpp.template"
                                                                      }
                                                                      else
                                                                      {
                                                            #line 877 "CodeGeneratorJava.cpp"
  append(L"[end]");
                                                            #line 476 "CodeGeneratorJava.cpp.template"
                                                                      }
                                                            #line 881 "CodeGeneratorJava.cpp"
  append(L" : 0;\n");
  append(L"          ++end;\n");
  append(L"          if (c1 >= 0xd800 && c1 < 0xdc00)\n");
  append(L"          {\n");
  append(L"            ++end;\n");
  append(L"          }\n");
  append(L"        }\n");
  append(L"      }\n");
  append(L"      else\n");
  append(L"      {\n");
  append(L"        end += (result >> ");
                                                            #line 487 "CodeGeneratorJava.cpp.template"
                                                                      print(lowBits);
                                                            #line 895 "CodeGeneratorJava.cpp"
  append(L");\n");
  append(L"      }");
                                                            #line 489 "CodeGeneratorJava.cpp.template"
                                                                    }
                                                            #line 900 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"    }");
                                                            #line 491 "CodeGeneratorJava.cpp.template"
                                                                  }
                                                                  if (lookahead)
                                                                  {
                                                                    if (! codepoints)
                                                                    {
                                                            #line 909 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"    else if (nonbmp)\n");
  append(L"    {\n");
  append(L"      for (int i = result >> ");
                                                            #line 499 "CodeGeneratorJava.cpp.template"
                                                                      print(lowBits);
                                                            #line 916 "CodeGeneratorJava.cpp"
  append(L"; i > 0; --i)\n");
  append(L"      {\n");
  append(L"        --end;\n");
  append(L"        int c1 = end < ");
                                                            #line 503 "CodeGeneratorJava.cpp.template"
                                                                      print(prefix);
                                                            #line 923 "CodeGeneratorJava.cpp"
  append(L"size ? ");
                                                            #line 504 "CodeGeneratorJava.cpp.template"
                                                                      print(prefix);
                                                            #line 927 "CodeGeneratorJava.cpp"
  append(L"input");
                                                            #line 505 "CodeGeneratorJava.cpp.template"
                                                                      if (targetLanguage == JAVA)
                                                                      {
                                                            #line 932 "CodeGeneratorJava.cpp"
  append(L".charAt(end)");
                                                            #line 507 "CodeGeneratorJava.cpp.template"
                                                                      }
                                                                      else
                                                                      {
                                                            #line 938 "CodeGeneratorJava.cpp"
  append(L"[end]");
                                                            #line 510 "CodeGeneratorJava.cpp.template"
                                                                      }
                                                            #line 942 "CodeGeneratorJava.cpp"
  append(L" : 0;\n");
  append(L"        if (c1 >= 0xdc00 && c1 < 0xe000)\n");
  append(L"        {\n");
  append(L"          --end;\n");
  append(L"        }\n");
  append(L"      }\n");
  append(L"    }");
                                                            #line 517 "CodeGeneratorJava.cpp.template"
                                                                    }
                                                            #line 952 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"    else\n");
  append(L"    {\n");
  append(L"      end -= result >> ");
                                                            #line 521 "CodeGeneratorJava.cpp.template"
                                                                    print(lowBits);
                                                            #line 959 "CodeGeneratorJava.cpp"
  append(L";\n");
  append(L"    }");
                                                            #line 523 "CodeGeneratorJava.cpp.template"
                                                                  }
                                                                }
                                                            #line 965 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"\n");
  append(L"    if (end > ");
                                                            #line 528 "CodeGeneratorJava.cpp.template"
                                                                print(prefix);
                                                            #line 971 "CodeGeneratorJava.cpp"
  append(L"size) end = ");
                                                            #line 529 "CodeGeneratorJava.cpp.template"
                                                                print(prefix);
                                                            #line 975 "CodeGeneratorJava.cpp"
  append(L"size;");
                                                            #line 530 "CodeGeneratorJava.cpp.template"
                                                                if (variable("trace").boolean())
                                                                {
                                                            #line 980 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 533 "CodeGeneratorJava.cpp.template"
                                                                  if (variable("useGlr").boolean() && targetLanguage != JAVA)
                                                                  {
                                                            #line 986 "CodeGeneratorJava.cpp"
  append(L"parser.");
                                                            #line 535 "CodeGeneratorJava.cpp.template"
                                                                  }
                                                            #line 990 "CodeGeneratorJava.cpp"
  append(L"writeTrace(\"    <done result=\\\"\" + xmlEscape(TOKEN[(result & ");
                                                            #line 537 "CodeGeneratorJava.cpp.template"
                                                                  print(Math::powerof(2, variable("tokencodeBits").integer()) - 1);
                                                            #line 994 "CodeGeneratorJava.cpp"
  append(L") - 1]) + \"\\\" begin=\\\"\" + begin + \"\\\" end=\\\"\" + end + \"\\\"/>\\n\");\n");
  append(L"    ");
                                                            #line 539 "CodeGeneratorJava.cpp.template"
                                                                  if (variable("useGlr").boolean() && targetLanguage != JAVA)
                                                                  {
                                                            #line 1000 "CodeGeneratorJava.cpp"
  append(L"parser.");
                                                            #line 541 "CodeGeneratorJava.cpp.template"
                                                                  }
                                                            #line 1004 "CodeGeneratorJava.cpp"
  append(L"writeTrace(\"  </tokenize>\\n\");");
                                                            #line 542 "CodeGeneratorJava.cpp.template"
                                                                }
                                                                if (hack)
                                                                {
                                                            #line 1010 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"    return hack((result & ");
                                                            #line 546 "CodeGeneratorJava.cpp.template"
                                                                  print(Math::powerof(2, variable("tokencodeBits").integer()) - 1);
                                                            #line 1015 "CodeGeneratorJava.cpp"
  append(L") - 1);\n");
  append(L"  }\n");
                                                            #line 549 "CodeGeneratorJava.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1022 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"    return (result & ");
                                                            #line 553 "CodeGeneratorJava.cpp.template"
                                                                  print(Math::powerof(2, variable("tokencodeBits").integer()) - 1);
                                                            #line 1027 "CodeGeneratorJava.cpp"
  append(L") - 1;\n");
  append(L"  }\n");
                                                            #line 556 "CodeGeneratorJava.cpp.template"
                                                                }
                                                              }

                                                              if (variable("useGlr").boolean())
                                                              {
                                                            #line 1036 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"}\n");
                                                            #line 563 "CodeGeneratorJava.cpp.template"
                                                                --indent;
                                                                if (targetLanguage != JAVA)
                                                                {
                                                            #line 1043 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"  private class Heap<T> where T : IComparable<T>\n");
  append(L"  {\n");
  append(L"    private Object[] array = new Object[16];\n");
  append(L"    private int size = 0;\n");
  append(L"\n");
  append(L"    public bool offer(T value)\n");
  append(L"    {\n");
  append(L"      int index = size;\n");
  append(L"      if (++size >= array.Length)\n");
  append(L"      {\n");
  append(L"        Array.Resize(ref array, array.Length << 1);\n");
  append(L"      }\n");
  append(L"      while (index != 0)\n");
  append(L"      {\n");
  append(L"        int parentIndex = (index - 1) >> 1;\n");
  append(L"        if (((T) array[parentIndex]).CompareTo(value) <= 0)\n");
  append(L"          break;\n");
  append(L"        array[index] = (T) array[parentIndex];\n");
  append(L"        index = parentIndex;\n");
  append(L"      }\n");
  append(L"      array[index] = value;\n");
  append(L"      return true;\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    public T poll()\n");
  append(L"    {\n");
  append(L"      if (size == 0)\n");
  append(L"        return default (T);\n");
  append(L"      T min = (T) array[0];\n");
  append(L"      if (--size > 0)\n");
  append(L"      {\n");
  append(L"        T value = (T) array[size];\n");
  append(L"        int index = 0;\n");
  append(L"        for (int child;;)\n");
  append(L"        {\n");
  append(L"          child = (index << 1) + 2;\n");
  append(L"          if (child < size)\n");
  append(L"          {\n");
  append(L"            int otherChild = child - 1;\n");
  append(L"            if (otherChild < size && ((T) array[child]).CompareTo((T) array[otherChild]) > 0)\n");
  append(L"                child = otherChild;\n");
  append(L"          }\n");
  append(L"          else if (--child >= size)\n");
  append(L"          {\n");
  append(L"            break;\n");
  append(L"          }\n");
  append(L"          if (value.CompareTo((T) array[child]) <= 0)\n");
  append(L"          {\n");
  append(L"            break;\n");
  append(L"          }\n");
  append(L"          array[index] = (T) array[child];\n");
  append(L"          index = child;\n");
  append(L"        }\n");
  append(L"        array[index] = value;\n");
  append(L"      }\n");
  append(L"      return min;\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    public bool isEmpty()\n");
  append(L"    {\n");
  append(L"      return size == 0;\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    public T peek()\n");
  append(L"    {\n");
  append(L"      return (T) (size == 0 ? null : array[0]);\n");
  append(L"    }\n");
  append(L"  }\n");
                                                            #line 635 "CodeGeneratorJava.cpp.template"
                                                                }
                                                              }

                                                              if (defined("gtbits"))
                                                              {
                                                            #line 1119 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"  private static int goTo(int nonterminal, int state)\n");
  append(L"  {\n");
                                                            #line 643 "CodeGeneratorJava.cpp.template"
                                                                compressedMap2dAccessor("nonterminal", "state", variable("gtcols").integer(),
                                                                                           4, "i", "return ", "GOTO", &variable("gtbits").integer());
                                                            #line 1126 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"  }\n");
                                                            #line 647 "CodeGeneratorJava.cpp.template"
                                                              }

                                                              if (! variable("embedded").boolean())
                                                              {
                                                            #line 1134 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"  public String[] getExpectedTokenSet()\n");
  append(L"  {\n");
  append(L"    return getTokenSet(- state);\n");
  append(L"  }\n");
                                                            #line 656 "CodeGeneratorJava.cpp.template"
                                                              }
                                                              if (variable("trace").boolean())
                                                              {
                                                            #line 1144 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"  private static String xmlEscape(String s)\n");
  append(L"  {\n");
  append(L"    StringBuilder sb = new StringBuilder();\n");
  append(L"    for (int i = 0; i < s.");
                                                            #line 663 "CodeGeneratorJava.cpp.template"
                                                                if (targetLanguage == JAVA)
                                                                {
                                                            #line 1153 "CodeGeneratorJava.cpp"
  append(L"length()");
                                                            #line 665 "CodeGeneratorJava.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1159 "CodeGeneratorJava.cpp"
  append(L"Length");
                                                            #line 668 "CodeGeneratorJava.cpp.template"
                                                                }
                                                            #line 1163 "CodeGeneratorJava.cpp"
  append(L"; ++i)\n");
  append(L"    {");
                                                            #line 670 "CodeGeneratorJava.cpp.template"
                                                                if (targetLanguage == JAVA)
                                                                {
                                                            #line 1169 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"      char c = s.charAt(i);");
                                                            #line 673 "CodeGeneratorJava.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1176 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"      char c = s[i];");
                                                            #line 677 "CodeGeneratorJava.cpp.template"
                                                                }
                                                            #line 1181 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"      switch (c)\n");
  append(L"      {\n");
  append(L"      case '<': sb.");
                                                            #line 681 "CodeGeneratorJava.cpp.template"
                                                                print(targetLanguage == JAVA ? "a" : "A");
                                                            #line 1188 "CodeGeneratorJava.cpp"
  append(L"ppend(\"&lt;\"); break;\n");
  append(L"      case '\"': sb.");
                                                            #line 683 "CodeGeneratorJava.cpp.template"
                                                                print(targetLanguage == JAVA ? "a" : "A");
                                                            #line 1193 "CodeGeneratorJava.cpp"
  append(L"ppend(\"&quot;\"); break;\n");
  append(L"      case '&': sb.");
                                                            #line 685 "CodeGeneratorJava.cpp.template"
                                                                print(targetLanguage == JAVA ? "a" : "A");
                                                            #line 1198 "CodeGeneratorJava.cpp"
  append(L"ppend(\"&amp;\"); break;");
                                                            #line 686 "CodeGeneratorJava.cpp.template"
                                                                if (targetLanguage == JAVA)
                                                                {
                                                            #line 1203 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"      default : sb.append(c); break;");
                                                            #line 689 "CodeGeneratorJava.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1210 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"      default : sb.Append(c.ToString()); break;");
                                                            #line 693 "CodeGeneratorJava.cpp.template"
                                                                }
                                                            #line 1215 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"      }\n");
  append(L"    }");
                                                            #line 696 "CodeGeneratorJava.cpp.template"
                                                                if (targetLanguage == JAVA)
                                                                {
                                                            #line 1222 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"    return sb.toString();");
                                                            #line 699 "CodeGeneratorJava.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1229 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"    return sb.ToString();");
                                                            #line 703 "CodeGeneratorJava.cpp.template"
                                                                }
                                                            #line 1234 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"  }\n");
                                                            #line 706 "CodeGeneratorJava.cpp.template"
                                                                if (targetLanguage == JAVA)
                                                                {
                                                            #line 1240 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"  public void setTraceWriter(Writer w)\n");
  append(L"  {\n");
  append(L"    err = w;\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  private void writeTrace(String content)\n");
  append(L"  {\n");
  append(L"    try\n");
  append(L"    {\n");
  append(L"      err.write(content);\n");
  append(L"    }\n");
  append(L"    catch (IOException e)\n");
  append(L"    {\n");
  append(L"      throw new RuntimeException(e);\n");
  append(L"    }\n");
  append(L"  }\n");
                                                            #line 725 "CodeGeneratorJava.cpp.template"
                                                                  if (variable("embedded").boolean())
                                                                  {
                                                            #line 1261 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"  private void flushTrace()\n");
  append(L"  {\n");
  append(L"    try\n");
  append(L"    {\n");
  append(L"      err.flush();\n");
  append(L"    }\n");
  append(L"    catch (IOException e)\n");
  append(L"    {\n");
  append(L"      throw new RuntimeException(e);\n");
  append(L"    }\n");
  append(L"  }\n");
                                                            #line 739 "CodeGeneratorJava.cpp.template"
                                                                  }
                                                                }
                                                                else
                                                                {
                                                            #line 1279 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"  public void setTraceWriter(TextWriter w)\n");
  append(L"  {\n");
  append(L"    err = w;\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  private void writeTrace(String content)\n");
  append(L"  {\n");
  append(L"    err.Write(content);\n");
  append(L"  }\n");
                                                            #line 753 "CodeGeneratorJava.cpp.template"
                                                                  if (variable("embedded").boolean())
                                                                  {
                                                            #line 1293 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"  private void flushTrace()\n");
  append(L"  {\n");
  append(L"    err.Flush();\n");
  append(L"  }\n");
                                                            #line 760 "CodeGeneratorJava.cpp.template"
                                                                  }
                                                                }
                                                              }
                                                              if (variable("nolexer").boolean())
                                                              {
                                                            #line 1305 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"  public static int getTokenCount() {return ");
                                                            #line 766 "CodeGeneratorJava.cpp.template"
                                                                print(variable("t1").size);
                                                            #line 1310 "CodeGeneratorJava.cpp"
  append(L";}\n");
  append(L"  public static String getTokenName(int code) {return code >= 0 && code < ");
                                                            #line 769 "CodeGeneratorJava.cpp.template"
                                                                print(variable("t1").size);
                                                            #line 1315 "CodeGeneratorJava.cpp"
  append(L" ? TOKEN[code] : null;}\n");
  append(L"  public static int getTokenSetCount() {return ");
                                                            #line 771 "CodeGeneratorJava.cpp.template"
                                                                print(variable("entrycount").integer());
                                                            #line 1320 "CodeGeneratorJava.cpp"
  append(L";}\n");
  append(L"\n");
  append(L"  public static String[] getTokenSet(int tokenSetId)");
                                                            #line 774 "CodeGeneratorJava.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 1328 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"  private static String[] getTokenSet(int tokenSetId)");
                                                            #line 778 "CodeGeneratorJava.cpp.template"
                                                              }
                                                            #line 1333 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"  {");
                                                            #line 780 "CodeGeneratorJava.cpp.template"
                                                              if (targetLanguage == JAVA)
                                                              {
                                                            #line 1339 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"    java.util.ArrayList<String> expected = new java.util.ArrayList<>();");
                                                            #line 784 "CodeGeneratorJava.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 1346 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"    List<String> expected = new List<String>();");
                                                            #line 788 "CodeGeneratorJava.cpp.template"
                                                              }

                                                              if (! variable("nolexer").boolean())
                                                              {
                                                            #line 1354 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"    int s = tokenSetId < 0 ? - tokenSetId : INITIAL[tokenSetId] & ");
                                                            #line 794 "CodeGeneratorJava.cpp.template"
                                                                print(Math::powerof(2, variable("stateCodeBits").integer()) - 1);
                                                            #line 1359 "CodeGeneratorJava.cpp"
  append(L";");
                                                            #line 796 "CodeGeneratorJava.cpp.template"
                                                              }
                                                            #line 1363 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"    for (int i = 0; i < ");
                                                            #line 798 "CodeGeneratorJava.cpp.template"
                                                              print(variable("t1").size);
                                                            #line 1368 "CodeGeneratorJava.cpp"
  append(L"; i += 32)\n");
  append(L"    {\n");
  append(L"      int j = i;\n");
  append(L"      int i0 = (i >> 5) * ");
                                                            #line 802 "CodeGeneratorJava.cpp.template"
                                                              print(variable("transitionStateCount").integer());
                                                            #line 1375 "CodeGeneratorJava.cpp"
  append(L" + ");
                                                            #line 803 "CodeGeneratorJava.cpp.template"
                                                              if (variable("nolexer").boolean())
                                                              {
                                                            #line 1380 "CodeGeneratorJava.cpp"
  append(L"tokenSetId");
                                                            #line 805 "CodeGeneratorJava.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 1386 "CodeGeneratorJava.cpp"
  append(L"s - 1");
                                                            #line 808 "CodeGeneratorJava.cpp.template"
                                                              }
                                                            #line 1390 "CodeGeneratorJava.cpp"
  append(L";\n");
                                                            #line 810 "CodeGeneratorJava.cpp.template"
                                                              const char *varName;
                                                              const char *shift;
                                                              const char *add;
                                                              const char *toArray;
                                                              if (targetLanguage == JAVA)
                                                              {
                                                                varName = "int f = ";
                                                                shift = ">>>=";
                                                                add = "add";
                                                                toArray = "toArray(new String[]{})";
                                                              }
                                                              else
                                                              {
                                                                varName = "uint f = ";
                                                                shift = ">>=";
                                                                add = "Add";
                                                                toArray = "ToArray()";
                                                              }
                                                              compressedMapAccessor(6, "i", varName, "EXPECTED", &variable("t0bits").integer());
                                                            #line 1412 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"      for ( ; f != 0; f ");
                                                            #line 830 "CodeGeneratorJava.cpp.template"
                                                              print(shift);
                                                            #line 1417 "CodeGeneratorJava.cpp"
  append(L" 1, ++j)\n");
  append(L"      {\n");
  append(L"        if ((f & 1) != 0)\n");
  append(L"        {\n");
  append(L"          expected.");
                                                            #line 835 "CodeGeneratorJava.cpp.template"
                                                              print(add);
                                                            #line 1425 "CodeGeneratorJava.cpp"
  append(L"(TOKEN[j]);\n");
  append(L"        }\n");
  append(L"      }\n");
  append(L"    }\n");
  append(L"    return expected.");
                                                            #line 840 "CodeGeneratorJava.cpp.template"
                                                              print(toArray);
                                                            #line 1433 "CodeGeneratorJava.cpp"
  append(L";\n");
  append(L"  }");
                                                            #line 842 "CodeGeneratorJava.cpp.template"
                                                              generateData();
                                                              if (! variable("embedded").boolean())
                                                              {
                                                            #line 1440 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"\n");
  append(L"  public enum Token\n");
  append(L"  {\n");
  append(L"    ");
                                                            #line 849 "CodeGeneratorJava.cpp.template"
                                                                const CGVariable &token = variable("token");
                                                                int w = (int) Format::width(token.size);
                                                                for (size_t i = 0; i < token.size; ++i)
                                                                {
                                                                  if (i)
                                                                  {
                                                            #line 1453 "CodeGeneratorJava.cpp"
  append(L",\n");
  append(L"    ");
                                                            #line 856 "CodeGeneratorJava.cpp.template"
                                                                  }
                                                            #line 1458 "CodeGeneratorJava.cpp"
  append(L"/* ");
                                                            #line 857 "CodeGeneratorJava.cpp.template"
                                                                  print(format.toString<char>(i, 10, w));
                                                            #line 1462 "CodeGeneratorJava.cpp"
  append(L" */ ");
                                                            #line 858 "CodeGeneratorJava.cpp.template"
                                                                  print(token.string(i));
                                                                }
                                                            #line 1467 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"  };");
                                                            #line 861 "CodeGeneratorJava.cpp.template"
                                                              }
                                                              if (variable("selfTest").boolean())
                                                              {
                                                            #line 1474 "CodeGeneratorJava.cpp"
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
  append(L"        if (result != tokenId || resultSize != tokenString.");
                                                            #line 881 "CodeGeneratorJava.cpp.template"
                                                                if (codepoints)
                                                                {
                                                            #line 1496 "CodeGeneratorJava.cpp"
  append(L"codePointCount(0, tokenString.length())");
                                                            #line 884 "CodeGeneratorJava.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1502 "CodeGeneratorJava.cpp"
  append(L"length()");
                                                            #line 888 "CodeGeneratorJava.cpp.template"
                                                                }
                                                            #line 1506 "CodeGeneratorJava.cpp"
  append(L")\n");
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
                                                            #line 907 "CodeGeneratorJava.cpp.template"
                                                                print(variable("classname").string());
                                                            #line 1528 "CodeGeneratorJava.cpp"
  append(L" testee = new ");
                                                            #line 908 "CodeGeneratorJava.cpp.template"
                                                                print(variable("classname").string());
                                                            #line 1532 "CodeGeneratorJava.cpp"
  append(L"();\n");
  append(L"    for (int e = 0; e < ");
                                                            #line 910 "CodeGeneratorJava.cpp.template"
                                                                print(variable("a0").size);
                                                            #line 1537 "CodeGeneratorJava.cpp"
  append(L"; ++e)\n");
  append(L"    {\n");
  append(L"      int s = INITIAL[e] & ");
                                                            #line 913 "CodeGeneratorJava.cpp.template"
                                                                print(Math::powerof(2, variable("stateCodeBits").integer()) - 1);
                                                            #line 1543 "CodeGeneratorJava.cpp"
  append(L";\n");
  append(L"      for (int i = 0; i < ");
                                                            #line 915 "CodeGeneratorJava.cpp.template"
                                                                print(variable("t1").size);
                                                            #line 1548 "CodeGeneratorJava.cpp"
  append(L"; i += 32)\n");
  append(L"      {\n");
  append(L"        int j = i;\n");
  append(L"        int i0 = (i >> 5) * ");
                                                            #line 919 "CodeGeneratorJava.cpp.template"
                                                                print(variable("transitionStateCount").integer());
                                                            #line 1555 "CodeGeneratorJava.cpp"
  append(L" + s - 1;\n");
                                                            #line 921 "CodeGeneratorJava.cpp.template"
                                                                compressedMapAccessor(8, "i", "int f = ", "EXPECTED", &variable("t0bits").integer());
                                                            #line 1559 "CodeGeneratorJava.cpp"
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
                                                            #line 932 "CodeGeneratorJava.cpp.template"
                                                              }
                                                            #line 1573 "CodeGeneratorJava.cpp"
  append(L"\n");
                                                            #line 934 "CodeGeneratorJava.cpp.template"
                                                              if (! variable("embedded").boolean())
                                                              {
                                                            #line 1578 "CodeGeneratorJava.cpp"
  append(L"}\n");
                                                            #line 937 "CodeGeneratorJava.cpp.template"
                                                              }
                                                            }

                                                            void CodeGeneratorJava::generateCompressedMap()
                                                            {
                                                            #line 1586 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"public class ");
                                                            #line 943 "CodeGeneratorJava.cpp.template"
                                                              print(variable("classname").string());
                                                            #line 1591 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"{\n");
  append(L"  public static int get(int i0)\n");
  append(L"  {\n");
  append(L"    if (i0 < 0 || i0 >= ");
                                                            #line 948 "CodeGeneratorJava.cpp.template"
                                                              print(variable("size").integer());
                                                            #line 1599 "CodeGeneratorJava.cpp"
  append(L")\n");
  append(L"      return 0;");
                                                            #line 950 "CodeGeneratorJava.cpp.template"
                                                              size_t i = 4;
                                                              if (variable("rm").size > 0)
                                                              {
                                                                i += 2;
                                                            #line 1607 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"    if (i0 < 0x30000)\n");
  append(L"    {");
                                                            #line 956 "CodeGeneratorJava.cpp.template"
                                                              }
                                                            #line 1613 "CodeGeneratorJava.cpp"
  append(L"\n");
                                                            #line 958 "CodeGeneratorJava.cpp.template"
                                                              compressedMapAccessor(i, "i", "return ", "LOW", &variable("dtbits").integer());
                                                              if (variable("rm").size > 0)
                                                              {
                                                            #line 1619 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"    }\n");
  append(L"    else\n");
  append(L"    {");
                                                            #line 964 "CodeGeneratorJava.cpp.template"
                                                                indent += 3;
                                                                generateBinarySearch("i0", "return ", "", "HIGH", variable("rm").size);
                                                                indent -= 3;
                                                            #line 1628 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"    }");
                                                            #line 968 "CodeGeneratorJava.cpp.template"
                                                              }
                                                            #line 1633 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"  }");
                                                            #line 970 "CodeGeneratorJava.cpp.template"
                                                              generateData();
                                                            #line 1638 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"}\n");
                                                            #line 973 "CodeGeneratorJava.cpp.template"
                                                            }

                                                            void CodeGeneratorJava::generateData()
                                                            {
                                                              size_t total = 0;
                                                              for (VarsInInsertionOrder::iterator a(varsInInsertionOrder.begin());
                                                                   a != varsInInsertionOrder.end(); ++a)
                                                                if (   a->isArray()
                                                                    && strlen(a->name) == 2
                                                                    && (a->hasType(CGVariable::INTEGER) || a->hasType(CGVariable::UNSIGNED)))
                                                              {
                                                                total += a->size;
                                                              }
                                                              bool asString = targetLanguage == JAVA
                                                                           && total > 8192;
                                                              size_t limit = total <= 99821
                                                                           ? 119
                                                                           : 4095;
                                                              if (asString)
                                                              {
                                                            #line 1662 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"\n");
  append(L"  private static void decode(String[] chunks, int[] target)\n");
  append(L"  {\n");
  append(L"    int n = 0;\n");
  append(L"    for (String chunk : chunks)\n");
  append(L"    {\n");
  append(L"      int value = 0;\n");
  append(L"      boolean negative = false;\n");
  append(L"      for (int i = 0, length = chunk.length(); i < length; ++i)\n");
  append(L"      {\n");
  append(L"        char c = chunk.charAt(i);\n");
  append(L"        if (c >= '0' && c <= '9')\n");
  append(L"        {\n");
  append(L"          value = value * 10 + (c - '0');\n");
  append(L"        }\n");
  append(L"        else if (c == '-')\n");
  append(L"        {\n");
  append(L"          negative = true;\n");
  append(L"        }\n");
  append(L"        else if (c == ',')\n");
  append(L"        {\n");
  append(L"          target[n++] = negative ? - value : value;\n");
  append(L"          value = 0;\n");
  append(L"          negative = false;\n");
  append(L"        }\n");
  append(L"      }\n");
  append(L"      target[n++] = negative ? - value : value;\n");
  append(L"    }\n");
  append(L"  }");
                                                            #line 1022 "CodeGeneratorJava.cpp.template"
                                                              }
                                                              for (VarsInInsertionOrder::iterator a(varsInInsertionOrder.begin());
                                                                   a != varsInInsertionOrder.end(); ++a)
                                                                if (   a->isArray()
                                                                    && a->size > 0
                                                                    && (a->hasType(CGVariable::INTEGER) || a->hasType(CGVariable::UNSIGNED))
                                                                    && strlen(a->name) == 2)
                                                              {
                                                            #line 1702 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"\n");
  append(L"  private static ");
                                                            #line 1032 "CodeGeneratorJava.cpp.template"
                                                                if (targetLanguage == JAVA)
                                                                {
                                                            #line 1709 "CodeGeneratorJava.cpp"
  append(L"final");
                                                            #line 1034 "CodeGeneratorJava.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1715 "CodeGeneratorJava.cpp"
  append(L"readonly");
                                                            #line 1037 "CodeGeneratorJava.cpp.template"
                                                                }
                                                            #line 1719 "CodeGeneratorJava.cpp"
  append(L" ");
                                                            #line 1038 "CodeGeneratorJava.cpp.template"
                                                                if (a->hasType(CGVariable::UNSIGNED))
                                                                {
                                                            #line 1724 "CodeGeneratorJava.cpp"
  append(L"u");
                                                            #line 1040 "CodeGeneratorJava.cpp.template"
                                                                }
                                                            #line 1728 "CodeGeneratorJava.cpp"
  append(L"int[] ");
                                                            #line 1041 "CodeGeneratorJava.cpp.template"
                                                                print(a->longName);
                                                            #line 1732 "CodeGeneratorJava.cpp"
  append(L" =");
                                                            #line 1042 "CodeGeneratorJava.cpp.template"
                                                                if (asString)
                                                                {
                                                            #line 1737 "CodeGeneratorJava.cpp"
  append(L" new int[");
                                                            #line 1044 "CodeGeneratorJava.cpp.template"
                                                                  print(a->size);
                                                            #line 1741 "CodeGeneratorJava.cpp"
  append(L"];\n");
  append(L"  static\n");
  append(L"  {\n");
  append(L"    final String s1[] =\n");
  append(L"    {");
                                                            #line 1049 "CodeGeneratorJava.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1751 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"  {");
                                                            #line 1053 "CodeGeneratorJava.cpp.template"
                                                                }
                                                                int w = (int) Format::width(a->size);
                                                                for (size_t j = 0; j < a->size; ++j)
                                                                {
                                                                  if (j == 0 || lineLength() + Format::width(a->integer(j)) + (asString ? 3 : 2) > limit)
                                                                  {
                                                                    if (j) print(asString ? "\"," : ",");
                                                            #line 1762 "CodeGeneratorJava.cpp"
  append(L"\n");
                                                            #line 1061 "CodeGeneratorJava.cpp.template"
                                                                    if (asString) print("  ");
                                                            #line 1766 "CodeGeneratorJava.cpp"
  append(L"    /* ");
                                                            #line 1062 "CodeGeneratorJava.cpp.template"
                                                                    print(format.toString<char>(j, 10, w));
                                                            #line 1770 "CodeGeneratorJava.cpp"
  append(L" */ ");
                                                            #line 1063 "CodeGeneratorJava.cpp.template"
                                                                    if (asString) print("\"");
                                                                  }
                                                                  else
                                                                  {
                                                            #line 1777 "CodeGeneratorJava.cpp"
  append(L", ");
                                                            #line 1067 "CodeGeneratorJava.cpp.template"
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
                                                            #line 1792 "CodeGeneratorJava.cpp"
  append(L"\"\n");
  append(L"    };\n");
  append(L"    decode(s1, ");
                                                            #line 1081 "CodeGeneratorJava.cpp.template"
                                                                  print(a->longName);
                                                            #line 1798 "CodeGeneratorJava.cpp"
  append(L");\n");
  append(L"  }");
                                                            #line 1083 "CodeGeneratorJava.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1805 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"  };");
                                                            #line 1087 "CodeGeneratorJava.cpp.template"
                                                                }
                                                              }
                                                              for (VarsInInsertionOrder::iterator a(varsInInsertionOrder.begin());
                                                                   a != varsInInsertionOrder.end(); ++a)
                                                                if (a->isArray() && a->size > 0 && a->hasType(CGVariable::STRING) && strlen(a->name) == 2)
                                                              {
                                                                bool isPublic = (variable("tree").boolean() && variable("embedded").boolean())
                                                                             || (variable("nolexer").boolean() && strcmp(a->longName, "TOKEN") == 0);
                                                            #line 1817 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"\n");
  append(L"  ");
                                                            #line 1097 "CodeGeneratorJava.cpp.template"
                                                                print(isPublic ? "public" : "private");
                                                            #line 1823 "CodeGeneratorJava.cpp"
  append(L" static ");
                                                            #line 1098 "CodeGeneratorJava.cpp.template"
                                                                if (targetLanguage == JAVA)
                                                                {
                                                            #line 1828 "CodeGeneratorJava.cpp"
  append(L"final");
                                                            #line 1100 "CodeGeneratorJava.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1834 "CodeGeneratorJava.cpp"
  append(L"readonly");
                                                            #line 1103 "CodeGeneratorJava.cpp.template"
                                                                }
                                                            #line 1838 "CodeGeneratorJava.cpp"
  append(L" String[] ");
                                                            #line 1104 "CodeGeneratorJava.cpp.template"
                                                                print(a->longName);
                                                            #line 1842 "CodeGeneratorJava.cpp"
  append(L" =\n");
  append(L"  {\n");
                                                            #line 1107 "CodeGeneratorJava.cpp.template"
                                                                for (size_t j = 0; j < a->size; ++j)
                                                                {
                                                                  if (j)
                                                                  {
                                                            #line 1850 "CodeGeneratorJava.cpp"
  append(L",\n");
                                                            #line 1112 "CodeGeneratorJava.cpp.template"
                                                                  }
                                                            #line 1854 "CodeGeneratorJava.cpp"
  append(L"    \"");
                                                            #line 1113 "CodeGeneratorJava.cpp.template"
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
                                                            #line 1869 "CodeGeneratorJava.cpp"
  append(L"\"");
                                                            #line 1125 "CodeGeneratorJava.cpp.template"
                                                                }
                                                            #line 1873 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"  };");
                                                            #line 1127 "CodeGeneratorJava.cpp.template"
                                                              }
                                                            }

                                                            void CodeGeneratorJava::generateBinarySearch(const char *input, const char *outputPrefix, const char *outputSuffix, const char *map, size_t size)
                                                            {
                                                            #line 1882 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"int lo = 0, hi = ");
                                                            #line 1133 "CodeGeneratorJava.cpp.template"
                                                              print(size / 3 - 1);
                                                            #line 1887 "CodeGeneratorJava.cpp"
  append(L";\n");
  append(L"for (int m = ");
                                                            #line 1135 "CodeGeneratorJava.cpp.template"
                                                              print((size / 3) >> 1);
                                                            #line 1892 "CodeGeneratorJava.cpp"
  append(L"; ; m = (hi + lo) >> 1)\n");
  append(L"{\n");
  append(L"  if (");
                                                            #line 1138 "CodeGeneratorJava.cpp.template"
                                                              print(map);
                                                            #line 1898 "CodeGeneratorJava.cpp"
  append(L"[m] > ");
                                                            #line 1139 "CodeGeneratorJava.cpp.template"
                                                              print(input);
                                                            #line 1902 "CodeGeneratorJava.cpp"
  append(L") {hi = m - 1;}\n");
  append(L"  else if (");
                                                            #line 1141 "CodeGeneratorJava.cpp.template"
                                                              print(map);
                                                            #line 1907 "CodeGeneratorJava.cpp"
  append(L"[");
                                                            #line 1142 "CodeGeneratorJava.cpp.template"
                                                              print(size / 3);
                                                            #line 1911 "CodeGeneratorJava.cpp"
  append(L" + m] < ");
                                                            #line 1143 "CodeGeneratorJava.cpp.template"
                                                              print(input);
                                                            #line 1915 "CodeGeneratorJava.cpp"
  append(L") {lo = m + 1;}\n");
  append(L"  else {");
                                                            #line 1145 "CodeGeneratorJava.cpp.template"
                                                              print(outputPrefix);
                                                              print(map);
                                                            #line 1921 "CodeGeneratorJava.cpp"
  append(L"[");
                                                            #line 1147 "CodeGeneratorJava.cpp.template"
                                                              print(size / 3 * 2);
                                                            #line 1925 "CodeGeneratorJava.cpp"
  append(L" + m]");
                                                            #line 1148 "CodeGeneratorJava.cpp.template"
                                                              print(outputSuffix);
                                                            #line 1929 "CodeGeneratorJava.cpp"
  append(L";}\n");
  append(L"  if (lo > hi) {");
                                                            #line 1150 "CodeGeneratorJava.cpp.template"
                                                              print(outputPrefix);
                                                            #line 1934 "CodeGeneratorJava.cpp"
  append(L"0");
                                                            #line 1151 "CodeGeneratorJava.cpp.template"
                                                              print(outputSuffix);
                                                            #line 1938 "CodeGeneratorJava.cpp"
  append(L";}\n");
  append(L"}");
                                                            #line 1153 "CodeGeneratorJava.cpp.template"
                                                            }

// End
