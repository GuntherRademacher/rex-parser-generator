// This file was generated on Sat Oct 17, 2026 11:26 (UTC+02) by REx v6.3-SNAPSHOT which is Copyright (c) 1979-2026 by Gunther Rademacher <grd@gmx.net>
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
                                                            #line 98 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"  private Lexer lexer = null;\n");
  append(L"  private Token token = new Token();");
                                                            #line 64 "CodeGeneratorJava.cpp.template"
                                                              }
                                                              if (! variable("embedded").boolean())
                                                              {
                                                            #line 106 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"  private int state = 0;");
                                                            #line 68 "CodeGeneratorJava.cpp.template"
                                                              }
                                                              if (variable("trace").boolean() && ! variable("useGlr").boolean())
                                                              {
                                                                if (targetLanguage == JAVA)
                                                                {
                                                            #line 115 "CodeGeneratorJava.cpp"
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
                                                            #line 82 "CodeGeneratorJava.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 130 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"  private TextWriter err = Console.Error;");
                                                            #line 86 "CodeGeneratorJava.cpp.template"
                                                                }
                                                              }
                                                            #line 136 "CodeGeneratorJava.cpp"
  append(L"\n");
                                                            #line 90 "CodeGeneratorJava.cpp.template"
                                                              if (! variable("embedded").boolean())
                                                              {
                                                                if (codepoints)
                                                                {
                                                            #line 143 "CodeGeneratorJava.cpp"
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
                                                            #line 105 "CodeGeneratorJava.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 160 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"  public void init(String string)\n");
  append(L"  {\n");
  append(L"    input = string;\n");
  append(L"    size = string.length();\n");
  append(L"    end = 0;\n");
  append(L"  }");
                                                            #line 114 "CodeGeneratorJava.cpp.template"
                                                                }
                                                            #line 170 "CodeGeneratorJava.cpp"
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
                                                            #line 125 "CodeGeneratorJava.cpp.template"
                                                                if (codepoints)
                                                                {
                                                            #line 185 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"  public int match(int tokenSetId, int[] codepoints)\n");
  append(L"  {\n");
  append(L"    init(codepoints);\n");
  append(L"    return match(tokenSetId);\n");
  append(L"  }");
                                                            #line 132 "CodeGeneratorJava.cpp.template"
                                                                }
                                                            #line 194 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"\n");
  append(L"  public");
                                                            #line 135 "CodeGeneratorJava.cpp.template"
                                                              }
                                                              else
                                                              {
                                                                if (variable("lrparser").boolean() ||
                                                                    variable("tables").boolean())
                                                                {
                                                            #line 205 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 142 "CodeGeneratorJava.cpp.template"
                                                                  print(variable("useGlr").boolean() ? "public" : "private");
                                                            #line 210 "CodeGeneratorJava.cpp"
  append(L" int predict(int dpi)");
                                                            #line 143 "CodeGeneratorJava.cpp.template"
                                                                  predict();
                                                                }
                                                            #line 215 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"  private");
                                                            #line 147 "CodeGeneratorJava.cpp.template"
                                                              }
                                                            #line 220 "CodeGeneratorJava.cpp"
  append(L" int match(int tokenSetId)\n");
  append(L"  {");
                                                            #line 149 "CodeGeneratorJava.cpp.template"
                                                              if (variable("nolexer").boolean())
                                                              {
                                                            #line 226 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"    token.begin = end;\n");
  append(L"    lexer.match(tokenSetId, token);\n");
  append(L"    begin = token.begin;\n");
  append(L"    end = token.end;\n");
  append(L"    return token.code >= 0\n");
  append(L"         ? token.code\n");
  append(L"         : error(begin, end, - tokenSetId, -1, -1);\n");
  append(L"  }\n");
                                                            #line 160 "CodeGeneratorJava.cpp.template"
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
                                                            #line 248 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 172 "CodeGeneratorJava.cpp.template"
                                                                  if (variable("useGlr").boolean() && targetLanguage != JAVA)
                                                                  {
                                                            #line 254 "CodeGeneratorJava.cpp"
  append(L"parser.");
                                                            #line 174 "CodeGeneratorJava.cpp.template"
                                                                  }
                                                            #line 258 "CodeGeneratorJava.cpp"
  append(L"writeTrace(\"  <tokenize ");
                                                            #line 176 "CodeGeneratorJava.cpp.template"
                                                                  if (variable("useGlr").boolean())
                                                                  {
                                                            #line 263 "CodeGeneratorJava.cpp"
  append(L"thread=\\\"\" + id + \"\\\" ");
                                                            #line 178 "CodeGeneratorJava.cpp.template"
                                                                  }
                                                            #line 267 "CodeGeneratorJava.cpp"
  append(L"tokenset=\\\"\" + tokenSetId + \"\\\">\\n\");\n");
                                                            #line 180 "CodeGeneratorJava.cpp.template"
                                                                }
                                                                if (lookahead && ! codepoints)
                                                                {
                                                                  if (targetLanguage == JAVA)
                                                                  {
                                                            #line 275 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"    boolean nonbmp = false;");
                                                            #line 186 "CodeGeneratorJava.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 282 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"    bool nonbmp = false;");
                                                            #line 190 "CodeGeneratorJava.cpp.template"
                                                                  }
                                                                }
                                                            #line 288 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"    begin = end;\n");
  append(L"    int current = end;\n");
  append(L"    int result = INITIAL[tokenSetId];");
                                                            #line 195 "CodeGeneratorJava.cpp.template"
                                                                if (variable("embedded").boolean() && (variable("trace").boolean() || ! variable("useGlr").boolean()))
                                                                {
                                                            #line 296 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"    int state = 0;");
                                                            #line 198 "CodeGeneratorJava.cpp.template"
                                                                }
                                                            #line 301 "CodeGeneratorJava.cpp"
  append(L"\n");
                                                            #line 200 "CodeGeneratorJava.cpp.template"
                                                                if (variable("trace").boolean())
                                                                {
                                                            #line 306 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 203 "CodeGeneratorJava.cpp.template"
                                                                  if (variable("useGlr").boolean() && targetLanguage != JAVA)
                                                                  {
                                                            #line 312 "CodeGeneratorJava.cpp"
  append(L"parser.");
                                                            #line 205 "CodeGeneratorJava.cpp.template"
                                                                  }
                                                            #line 316 "CodeGeneratorJava.cpp"
  append(L"writeTrace(\"    <next state=\\\"\" + (result & ");
                                                            #line 206 "CodeGeneratorJava.cpp.template"
                                                                  print(Math::powerof(2, variable("stateCodeBits").integer()) - 1);
                                                            #line 320 "CodeGeneratorJava.cpp"
  append(L") + \"\\\"\");");
                                                            #line 207 "CodeGeneratorJava.cpp.template"
                                                                }
                                                            #line 324 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"    for (int code = result & ");
                                                            #line 209 "CodeGeneratorJava.cpp.template"
                                                                print(Math::powerof(2, variable("stateCodeBits").integer()) - 1);
                                                            #line 329 "CodeGeneratorJava.cpp"
  append(L"; code != 0; )\n");
  append(L"    {\n");
  append(L"      int charclass;\n");
  append(L"      int c0 = current < ");
                                                            #line 213 "CodeGeneratorJava.cpp.template"
                                                                print(prefix);
                                                            #line 336 "CodeGeneratorJava.cpp"
  append(L"size ? ");
                                                            #line 214 "CodeGeneratorJava.cpp.template"
                                                                        print(prefix);
                                                            #line 340 "CodeGeneratorJava.cpp"
  append(L"input");
                                                            #line 215 "CodeGeneratorJava.cpp.template"
                                                                if (targetLanguage == JAVA && ! codepoints)
                                                                {
                                                            #line 345 "CodeGeneratorJava.cpp"
  append(L".charAt(current)");
                                                            #line 217 "CodeGeneratorJava.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 351 "CodeGeneratorJava.cpp"
  append(L"[current]");
                                                            #line 220 "CodeGeneratorJava.cpp.template"
                                                                }
                                                            #line 355 "CodeGeneratorJava.cpp"
  append(L" : 0;");
                                                            #line 221 "CodeGeneratorJava.cpp.template"
                                                                if (variable("trace").boolean())
                                                                {
                                                            #line 360 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"      ");
                                                            #line 224 "CodeGeneratorJava.cpp.template"
                                                                  if (variable("useGlr").boolean() && targetLanguage != JAVA)
                                                                  {
                                                            #line 366 "CodeGeneratorJava.cpp"
  append(L"parser.");
                                                            #line 226 "CodeGeneratorJava.cpp.template"
                                                                  }
                                                            #line 370 "CodeGeneratorJava.cpp"
  append(L"writeTrace(\" offset=\\\"\" + current + \"\\\"\");");
                                                            #line 227 "CodeGeneratorJava.cpp.template"
                                                                }
                                                            #line 374 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"      ++current;\n");
  append(L"      if (c0 < 0x");
                                                            #line 230 "CodeGeneratorJava.cpp.template"
                                                                print(format.toString<char>(variable("simplifiedCodeMap").integer(), 16, 0, 0, 0, "0123456789abcdef"));
                                                            #line 380 "CodeGeneratorJava.cpp"
  append(L")\n");
  append(L"      {");
                                                            #line 233 "CodeGeneratorJava.cpp.template"
                                                                if (variable("trace").boolean())
                                                                {
                                                            #line 386 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"        if (c0 >= 32 && c0 <= 126)\n");
  append(L"        {\n");
  append(L"          ");
                                                            #line 238 "CodeGeneratorJava.cpp.template"
                                                                  if (variable("useGlr").boolean() && targetLanguage != JAVA)
                                                                  {
                                                            #line 394 "CodeGeneratorJava.cpp"
  append(L"parser.");
                                                            #line 240 "CodeGeneratorJava.cpp.template"
                                                                  }
                                                            #line 398 "CodeGeneratorJava.cpp"
  append(L"writeTrace(\" char=\\\"\" + xmlEscape(");
                                                            #line 241 "CodeGeneratorJava.cpp.template"
                                                                  if (targetLanguage == JAVA)
                                                                  {
                                                            #line 403 "CodeGeneratorJava.cpp"
  append(L"String.valueOf((char) c0)");
                                                            #line 244 "CodeGeneratorJava.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 409 "CodeGeneratorJava.cpp"
  append(L"((char) c0).ToString()");
                                                            #line 248 "CodeGeneratorJava.cpp.template"
                                                                  }
                                                            #line 413 "CodeGeneratorJava.cpp"
  append(L") + \"\\\"\");\n");
  append(L"        }");
                                                            #line 250 "CodeGeneratorJava.cpp.template"
                                                                }
                                                            #line 418 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"        charclass = MAP0[c0];\n");
  append(L"      }\n");
  append(L"      else if (c0 < 0x");
                                                            #line 254 "CodeGeneratorJava.cpp.template"
                                                                print(format.toString<char>(variable("uncompressedMapSize").integer(), 16, 0, 0, 0, "0123456789abcdef"));
                                                            #line 425 "CodeGeneratorJava.cpp"
  append(L")\n");
  append(L"      {\n");
                                                            #line 257 "CodeGeneratorJava.cpp.template"
                                                                compressedMapAccessor(8, "c", "charclass = ", "MAP1", &variable("m1bits").integer());
                                                            #line 430 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"      }\n");
  append(L"      else\n");
  append(L"      {");
                                                            #line 261 "CodeGeneratorJava.cpp.template"
                                                                if (variable("m2").size == 0)
                                                                {
                                                            #line 438 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"        charclass = 0;");
                                                            #line 264 "CodeGeneratorJava.cpp.template"
                                                                }
                                                                else
                                                                {
                                                                  if (! codepoints)
                                                                  {
                                                            #line 447 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"        if (");
                                                            #line 270 "CodeGeneratorJava.cpp.template"
                                                                    if (variable("uncompressedMapSize").integer() != 0xd800)
                                                                    {
                                                            #line 453 "CodeGeneratorJava.cpp"
  append(L"c0 >= 0xd800 && ");
                                                            #line 272 "CodeGeneratorJava.cpp.template"
                                                                    }
                                                            #line 457 "CodeGeneratorJava.cpp"
  append(L"c0 < 0xdc00)\n");
  append(L"        {\n");
  append(L"          int c1 = current < ");
                                                            #line 275 "CodeGeneratorJava.cpp.template"
                                                                    print(prefix);
                                                            #line 463 "CodeGeneratorJava.cpp"
  append(L"size ? ");
                                                            #line 276 "CodeGeneratorJava.cpp.template"
                                                                    print(prefix);
                                                            #line 467 "CodeGeneratorJava.cpp"
  append(L"input");
                                                            #line 277 "CodeGeneratorJava.cpp.template"
                                                                    if (targetLanguage == JAVA)
                                                                    {
                                                            #line 472 "CodeGeneratorJava.cpp"
  append(L".charAt(current)");
                                                            #line 279 "CodeGeneratorJava.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 478 "CodeGeneratorJava.cpp"
  append(L"[current]");
                                                            #line 282 "CodeGeneratorJava.cpp.template"
                                                                    }
                                                            #line 482 "CodeGeneratorJava.cpp"
  append(L" : 0;\n");
  append(L"          if (c1 >= 0xdc00 && c1 < 0xe000)\n");
  append(L"          {");
                                                            #line 285 "CodeGeneratorJava.cpp.template"
                                                                    if (lookahead)
                                                                    {
                                                            #line 489 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"            nonbmp = true;");
                                                            #line 288 "CodeGeneratorJava.cpp.template"
                                                                    }
                                                            #line 494 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"            ++current;\n");
  append(L"            c0 = ((c0 & 0x3ff) << 10) + (c1 & 0x3ff) + 0x10000;\n");
  append(L"          }\n");
  append(L"        }\n");
                                                            #line 294 "CodeGeneratorJava.cpp.template"
                                                                  }
                                                            #line 502 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"        int lo = 0, hi = ");
                                                            #line 296 "CodeGeneratorJava.cpp.template"
                                                                  print(variable("m2").size / 3 - 1);
                                                            #line 507 "CodeGeneratorJava.cpp"
  append(L";\n");
  append(L"        for (int m = ");
                                                            #line 298 "CodeGeneratorJava.cpp.template"
                                                                  print((variable("m2").size / 3) >> 1);
                                                            #line 512 "CodeGeneratorJava.cpp"
  append(L"; ; m = (hi + lo) >> 1)\n");
  append(L"        {\n");
  append(L"          if (MAP2[m] > c0) {hi = m - 1;}\n");
  append(L"          else if (MAP2[");
                                                            #line 302 "CodeGeneratorJava.cpp.template"
                                                                  print(variable("m2").size / 3);
                                                            #line 519 "CodeGeneratorJava.cpp"
  append(L" + m] < c0) {lo = m + 1;}\n");
  append(L"          else {charclass = MAP2[");
                                                            #line 304 "CodeGeneratorJava.cpp.template"
                                                                  print(variable("m2").size / 3 * 2);
                                                            #line 524 "CodeGeneratorJava.cpp"
  append(L" + m]; break;}\n");
  append(L"          if (lo > hi) {charclass = 0; break;}\n");
  append(L"        }");
                                                            #line 307 "CodeGeneratorJava.cpp.template"
                                                                }
                                                            #line 530 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"      }");
                                                            #line 309 "CodeGeneratorJava.cpp.template"
                                                                if (variable("trace").boolean())
                                                                {
                                                            #line 536 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"      ");
                                                            #line 312 "CodeGeneratorJava.cpp.template"
                                                                  if (variable("useGlr").boolean() && targetLanguage != JAVA)
                                                                  {
                                                            #line 542 "CodeGeneratorJava.cpp"
  append(L"parser.");
                                                            #line 314 "CodeGeneratorJava.cpp.template"
                                                                  }
                                                            #line 546 "CodeGeneratorJava.cpp"
  append(L"writeTrace(\" codepoint=\\\"\" + c0 + \"\\\" class=\\\"\" + charclass + \"\\\"\");");
                                                            #line 316 "CodeGeneratorJava.cpp.template"
                                                                }
                                                            #line 550 "CodeGeneratorJava.cpp"
  append(L"\n");
                                                            #line 318 "CodeGeneratorJava.cpp.template"
                                                                if (variable("trace").boolean() || ! variable("useGlr").boolean())
                                                                {
                                                            #line 555 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"      state = code;");
                                                            #line 321 "CodeGeneratorJava.cpp.template"
                                                                }
                                                            #line 560 "CodeGeneratorJava.cpp"
  append(L"\n");
                                                            #line 323 "CodeGeneratorJava.cpp.template"
                                                                compressedMap2dAccessor("code - 1", "charclass", variable("a1cols").integer(),
                                                                                           6, "i", "code = ", "TRANSITION", &variable("a1bits").integer());
                                                            #line 565 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"\n");
  append(L"      if (code > ");
                                                            #line 327 "CodeGeneratorJava.cpp.template"
                                                                print(Math::powerof(2, variable("stateCodeBits").integer()) - 1);
                                                            #line 571 "CodeGeneratorJava.cpp"
  append(L")\n");
  append(L"      {\n");
  append(L"        result = code;");
                                                            #line 330 "CodeGeneratorJava.cpp.template"
                                                                if (variable("trace").boolean())
                                                                {
                                                            #line 578 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"        ");
                                                            #line 333 "CodeGeneratorJava.cpp.template"
                                                                  if (variable("useGlr").boolean() && targetLanguage != JAVA)
                                                                  {
                                                            #line 584 "CodeGeneratorJava.cpp"
  append(L"parser.");
                                                            #line 335 "CodeGeneratorJava.cpp.template"
                                                                  }
                                                            #line 588 "CodeGeneratorJava.cpp"
  append(L"writeTrace(\" result=\\\"\" + xmlEscape(TOKEN[((result >> ");
                                                            #line 336 "CodeGeneratorJava.cpp.template"
                                                                   print(variable("stateCodeBits").integer());
                                                            #line 592 "CodeGeneratorJava.cpp"
  append(L") & ");
                                                            #line 338 "CodeGeneratorJava.cpp.template"
                                                                  print(Math::powerof(2, variable("tokencodeBits").integer()) - 1);
                                                            #line 596 "CodeGeneratorJava.cpp"
  append(L") - 1]) + \"\\\"\");");
                                                            #line 340 "CodeGeneratorJava.cpp.template"
                                                                  if (lookahead || hasFixedTokenLength)
                                                                  {
                                                                    int contextOffset = variable("stateCodeBits").integer()
                                                                                      + variable("tokencodeBits").integer();
                                                                    int sizeOffset = contextOffset
                                                                                   + (hasFixedTokenLength ? 1 : 0);
                                                                    if (hasFixedTokenLength)
                                                                    {
                                                            #line 607 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"        if ((result & ");
                                                            #line 349 "CodeGeneratorJava.cpp.template"
                                                                      print(Math::powerof(2, contextOffset));
                                                            #line 612 "CodeGeneratorJava.cpp"
  append(L") > 0)\n");
  append(L"        {\n");
  append(L"          ");
                                                            #line 352 "CodeGeneratorJava.cpp.template"
                                                                      if (variable("useGlr").boolean() && targetLanguage != JAVA)
                                                                      {
                                                            #line 619 "CodeGeneratorJava.cpp"
  append(L"parser.");
                                                            #line 354 "CodeGeneratorJava.cpp.template"
                                                                      }
                                                            #line 623 "CodeGeneratorJava.cpp"
  append(L"writeTrace(\" token-size=\\\"\" + (result >> ");
                                                            #line 355 "CodeGeneratorJava.cpp.template"
                                                                      print(sizeOffset);
                                                            #line 627 "CodeGeneratorJava.cpp"
  append(L") + \"\\\"\");\n");
  append(L"        }\n");
  append(L"        else ");
                                                            #line 358 "CodeGeneratorJava.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 635 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"        ");
                                                            #line 362 "CodeGeneratorJava.cpp.template"
                                                                    }
                                                            #line 640 "CodeGeneratorJava.cpp"
  append(L"if ((result >> ");
                                                            #line 363 "CodeGeneratorJava.cpp.template"
                                                                    print(sizeOffset);
                                                            #line 644 "CodeGeneratorJava.cpp"
  append(L") > 0)\n");
  append(L"        {\n");
  append(L"          ");
                                                            #line 366 "CodeGeneratorJava.cpp.template"
                                                                    if (variable("useGlr").boolean() && targetLanguage != JAVA)
                                                                    {
                                                            #line 651 "CodeGeneratorJava.cpp"
  append(L"parser.");
                                                            #line 368 "CodeGeneratorJava.cpp.template"
                                                                    }
                                                            #line 655 "CodeGeneratorJava.cpp"
  append(L"writeTrace(\" trailing-context-size=\\\"\" + (result >> ");
                                                            #line 369 "CodeGeneratorJava.cpp.template"
                                                                    print(sizeOffset);
                                                            #line 659 "CodeGeneratorJava.cpp"
  append(L") + \"\\\"\");\n");
  append(L"        }");
                                                            #line 371 "CodeGeneratorJava.cpp.template"
                                                                  }
                                                                }
                                                            #line 665 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"        code &= ");
                                                            #line 374 "CodeGeneratorJava.cpp.template"
                                                                print(Math::powerof(2, variable("stateCodeBits").integer()) - 1);
                                                            #line 670 "CodeGeneratorJava.cpp"
  append(L";\n");
  append(L"        end = current;\n");
  append(L"      }");
                                                            #line 377 "CodeGeneratorJava.cpp.template"
                                                                if (variable("trace").boolean())
                                                                {
                                                            #line 677 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"      ");
                                                            #line 380 "CodeGeneratorJava.cpp.template"
                                                                  if (variable("useGlr").boolean() && targetLanguage != JAVA)
                                                                  {
                                                            #line 683 "CodeGeneratorJava.cpp"
  append(L"parser.");
                                                            #line 382 "CodeGeneratorJava.cpp.template"
                                                                  }
                                                            #line 687 "CodeGeneratorJava.cpp"
  append(L"writeTrace(\"/>\\n\");\n");
  append(L"      if (code != 0)\n");
  append(L"      {\n");
  append(L"        ");
                                                            #line 386 "CodeGeneratorJava.cpp.template"
                                                                  if (variable("useGlr").boolean() && targetLanguage != JAVA)
                                                                  {
                                                            #line 695 "CodeGeneratorJava.cpp"
  append(L"parser.");
                                                            #line 388 "CodeGeneratorJava.cpp.template"
                                                                  }
                                                            #line 699 "CodeGeneratorJava.cpp"
  append(L"writeTrace(\"    <next state=\\\"\" + code + \"\\\"\");\n");
  append(L"      }");
                                                            #line 390 "CodeGeneratorJava.cpp.template"
                                                                }
                                                            #line 704 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    result >>= ");
                                                            #line 394 "CodeGeneratorJava.cpp.template"
                                                                print(variable("stateCodeBits").integer());
                                                            #line 711 "CodeGeneratorJava.cpp"
  append(L";\n");
  append(L"    if (result == 0)\n");
  append(L"    {\n");
  append(L"      end = current - 1;");
                                                            #line 398 "CodeGeneratorJava.cpp.template"
                                                                if (! codepoints)
                                                                {
                                                            #line 719 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"      int c1 = end < ");
                                                            #line 401 "CodeGeneratorJava.cpp.template"
                                                                  print(prefix);
                                                            #line 724 "CodeGeneratorJava.cpp"
  append(L"size ? ");
                                                            #line 402 "CodeGeneratorJava.cpp.template"
                                                                  print(prefix);
                                                            #line 728 "CodeGeneratorJava.cpp"
  append(L"input");
                                                            #line 403 "CodeGeneratorJava.cpp.template"
                                                                  if (targetLanguage == JAVA)
                                                                  {
                                                            #line 733 "CodeGeneratorJava.cpp"
  append(L".charAt(end)");
                                                            #line 405 "CodeGeneratorJava.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 739 "CodeGeneratorJava.cpp"
  append(L"[end]");
                                                            #line 408 "CodeGeneratorJava.cpp.template"
                                                                  }
                                                            #line 743 "CodeGeneratorJava.cpp"
  append(L" : 0;\n");
  append(L"      if (c1 >= 0xdc00 && c1 < 0xe000)\n");
  append(L"      {\n");
  append(L"        --end;\n");
  append(L"      }");
                                                            #line 413 "CodeGeneratorJava.cpp.template"
                                                                }
                                                                if (variable("trace").boolean())
                                                                {
                                                            #line 753 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"      ");
                                                            #line 417 "CodeGeneratorJava.cpp.template"
                                                                  if (variable("useGlr").boolean() && targetLanguage != JAVA)
                                                                  {
                                                            #line 759 "CodeGeneratorJava.cpp"
  append(L"parser.");
                                                            #line 419 "CodeGeneratorJava.cpp.template"
                                                                  }
                                                            #line 763 "CodeGeneratorJava.cpp"
  append(L"writeTrace(\"    <fail begin=\\\"\" + begin + \"\\\" end=\\\"\" + end + \"\\\" state=\\\"\" + state + \"\\\"/>\\n\");\n");
  append(L"      ");
                                                            #line 421 "CodeGeneratorJava.cpp.template"
                                                                  if (variable("useGlr").boolean() && targetLanguage != JAVA)
                                                                  {
                                                            #line 769 "CodeGeneratorJava.cpp"
  append(L"parser.");
                                                            #line 423 "CodeGeneratorJava.cpp.template"
                                                                  }
                                                            #line 773 "CodeGeneratorJava.cpp"
  append(L"writeTrace(\"  </tokenize>\\n\");");
                                                            #line 424 "CodeGeneratorJava.cpp.template"
                                                                }
                                                                if (variable("embedded").boolean())
                                                                {
                                                                  if (variable("useGlr").boolean())
                                                                  {
                                                            #line 781 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"      end = begin;\n");
  append(L"      return -1;");
                                                            #line 431 "CodeGeneratorJava.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 789 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"      return error(begin, end, state, -1, -1);");
                                                            #line 435 "CodeGeneratorJava.cpp.template"
                                                                  }
                                                                }
                                                            #line 795 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"    }");
                                                            #line 438 "CodeGeneratorJava.cpp.template"
                                                                lowBits = variable("tokencodeBits").integer();
                                                                if (hasFixedTokenLength && ! lookahead)
                                                                {
                                                            #line 802 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"    else if ((result & ");
                                                            #line 442 "CodeGeneratorJava.cpp.template"
                                                                  print(Math::powerof(2, lowBits));
                                                                  ++lowBits;
                                                            #line 808 "CodeGeneratorJava.cpp"
  append(L") != 0)\n");
  append(L"    {\n");
  append(L"      end = begin;\n");
  append(L"    }");
                                                            #line 447 "CodeGeneratorJava.cpp.template"
                                                                }
                                                                else
                                                                {
                                                                  if (hasFixedTokenLength)
                                                                  {
                                                            #line 819 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"    else if ((result & ");
                                                            #line 453 "CodeGeneratorJava.cpp.template"
                                                                    print(Math::powerof(2, lowBits));
                                                                    ++lowBits;
                                                            #line 825 "CodeGeneratorJava.cpp"
  append(L") != 0)\n");
  append(L"    {\n");
  append(L"      end = begin;");
                                                            #line 457 "CodeGeneratorJava.cpp.template"
                                                                    if (codepoints)
                                                                    {
                                                            #line 832 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"      end += (result >> ");
                                                            #line 460 "CodeGeneratorJava.cpp.template"
                                                                      print(lowBits);
                                                            #line 837 "CodeGeneratorJava.cpp"
  append(L");");
                                                            #line 461 "CodeGeneratorJava.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 843 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"      if (nonbmp)\n");
  append(L"      {\n");
  append(L"        for (int i = result >> ");
                                                            #line 467 "CodeGeneratorJava.cpp.template"
                                                                      print(lowBits);
                                                            #line 850 "CodeGeneratorJava.cpp"
  append(L"; i > 0; --i)\n");
  append(L"        {\n");
  append(L"          int c1 = end < ");
                                                            #line 470 "CodeGeneratorJava.cpp.template"
                                                                      print(prefix);
                                                            #line 856 "CodeGeneratorJava.cpp"
  append(L"size ? ");
                                                            #line 471 "CodeGeneratorJava.cpp.template"
                                                                      print(prefix);
                                                            #line 860 "CodeGeneratorJava.cpp"
  append(L"input");
                                                            #line 472 "CodeGeneratorJava.cpp.template"
                                                                      if (targetLanguage == JAVA)
                                                                      {
                                                            #line 865 "CodeGeneratorJava.cpp"
  append(L".charAt(end)");
                                                            #line 474 "CodeGeneratorJava.cpp.template"
                                                                      }
                                                                      else
                                                                      {
                                                            #line 871 "CodeGeneratorJava.cpp"
  append(L"[end]");
                                                            #line 477 "CodeGeneratorJava.cpp.template"
                                                                      }
                                                            #line 875 "CodeGeneratorJava.cpp"
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
                                                            #line 488 "CodeGeneratorJava.cpp.template"
                                                                      print(lowBits);
                                                            #line 889 "CodeGeneratorJava.cpp"
  append(L");\n");
  append(L"      }");
                                                            #line 490 "CodeGeneratorJava.cpp.template"
                                                                    }
                                                            #line 894 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"    }");
                                                            #line 492 "CodeGeneratorJava.cpp.template"
                                                                  }
                                                                  if (lookahead)
                                                                  {
                                                                    if (! codepoints)
                                                                    {
                                                            #line 903 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"    else if (nonbmp)\n");
  append(L"    {\n");
  append(L"      for (int i = result >> ");
                                                            #line 500 "CodeGeneratorJava.cpp.template"
                                                                      print(lowBits);
                                                            #line 910 "CodeGeneratorJava.cpp"
  append(L"; i > 0; --i)\n");
  append(L"      {\n");
  append(L"        --end;\n");
  append(L"        int c1 = end < ");
                                                            #line 504 "CodeGeneratorJava.cpp.template"
                                                                      print(prefix);
                                                            #line 917 "CodeGeneratorJava.cpp"
  append(L"size ? ");
                                                            #line 505 "CodeGeneratorJava.cpp.template"
                                                                      print(prefix);
                                                            #line 921 "CodeGeneratorJava.cpp"
  append(L"input");
                                                            #line 506 "CodeGeneratorJava.cpp.template"
                                                                      if (targetLanguage == JAVA)
                                                                      {
                                                            #line 926 "CodeGeneratorJava.cpp"
  append(L".charAt(end)");
                                                            #line 508 "CodeGeneratorJava.cpp.template"
                                                                      }
                                                                      else
                                                                      {
                                                            #line 932 "CodeGeneratorJava.cpp"
  append(L"[end]");
                                                            #line 511 "CodeGeneratorJava.cpp.template"
                                                                      }
                                                            #line 936 "CodeGeneratorJava.cpp"
  append(L" : 0;\n");
  append(L"        if (c1 >= 0xdc00 && c1 < 0xe000)\n");
  append(L"        {\n");
  append(L"          --end;\n");
  append(L"        }\n");
  append(L"      }\n");
  append(L"    }");
                                                            #line 518 "CodeGeneratorJava.cpp.template"
                                                                    }
                                                            #line 946 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"    else\n");
  append(L"    {\n");
  append(L"      end -= result >> ");
                                                            #line 522 "CodeGeneratorJava.cpp.template"
                                                                    print(lowBits);
                                                            #line 953 "CodeGeneratorJava.cpp"
  append(L";\n");
  append(L"    }");
                                                            #line 524 "CodeGeneratorJava.cpp.template"
                                                                  }
                                                                }
                                                            #line 959 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"\n");
  append(L"    if (end > ");
                                                            #line 529 "CodeGeneratorJava.cpp.template"
                                                                print(prefix);
                                                            #line 965 "CodeGeneratorJava.cpp"
  append(L"size) end = ");
                                                            #line 530 "CodeGeneratorJava.cpp.template"
                                                                print(prefix);
                                                            #line 969 "CodeGeneratorJava.cpp"
  append(L"size;");
                                                            #line 531 "CodeGeneratorJava.cpp.template"
                                                                if (variable("trace").boolean())
                                                                {
                                                            #line 974 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 534 "CodeGeneratorJava.cpp.template"
                                                                  if (variable("useGlr").boolean() && targetLanguage != JAVA)
                                                                  {
                                                            #line 980 "CodeGeneratorJava.cpp"
  append(L"parser.");
                                                            #line 536 "CodeGeneratorJava.cpp.template"
                                                                  }
                                                            #line 984 "CodeGeneratorJava.cpp"
  append(L"writeTrace(\"    <done result=\\\"\" + xmlEscape(TOKEN[(result & ");
                                                            #line 538 "CodeGeneratorJava.cpp.template"
                                                                  print(Math::powerof(2, variable("tokencodeBits").integer()) - 1);
                                                            #line 988 "CodeGeneratorJava.cpp"
  append(L") - 1]) + \"\\\" begin=\\\"\" + begin + \"\\\" end=\\\"\" + end + \"\\\"/>\\n\");\n");
  append(L"    ");
                                                            #line 540 "CodeGeneratorJava.cpp.template"
                                                                  if (variable("useGlr").boolean() && targetLanguage != JAVA)
                                                                  {
                                                            #line 994 "CodeGeneratorJava.cpp"
  append(L"parser.");
                                                            #line 542 "CodeGeneratorJava.cpp.template"
                                                                  }
                                                            #line 998 "CodeGeneratorJava.cpp"
  append(L"writeTrace(\"  </tokenize>\\n\");");
                                                            #line 543 "CodeGeneratorJava.cpp.template"
                                                                }
                                                                if (hack)
                                                                {
                                                            #line 1004 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"    return hack((result & ");
                                                            #line 547 "CodeGeneratorJava.cpp.template"
                                                                  print(Math::powerof(2, variable("tokencodeBits").integer()) - 1);
                                                            #line 1009 "CodeGeneratorJava.cpp"
  append(L") - 1);\n");
  append(L"  }\n");
                                                            #line 550 "CodeGeneratorJava.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1016 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"    return (result & ");
                                                            #line 554 "CodeGeneratorJava.cpp.template"
                                                                  print(Math::powerof(2, variable("tokencodeBits").integer()) - 1);
                                                            #line 1021 "CodeGeneratorJava.cpp"
  append(L") - 1;\n");
  append(L"  }\n");
                                                            #line 557 "CodeGeneratorJava.cpp.template"
                                                                }
                                                              }

                                                              if (variable("useGlr").boolean())
                                                              {
                                                            #line 1030 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"}\n");
                                                            #line 564 "CodeGeneratorJava.cpp.template"
                                                                --indent;
                                                                if (targetLanguage != JAVA)
                                                                {
                                                            #line 1037 "CodeGeneratorJava.cpp"
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
                                                            #line 636 "CodeGeneratorJava.cpp.template"
                                                                }
                                                              }

                                                              if (defined("gtbits"))
                                                              {
                                                            #line 1113 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"  private static int goTo(int nonterminal, int state)\n");
  append(L"  {\n");
                                                            #line 644 "CodeGeneratorJava.cpp.template"
                                                                compressedMap2dAccessor("nonterminal", "state", variable("gtcols").integer(),
                                                                                           4, "i", "return ", "GOTO", &variable("gtbits").integer());
                                                            #line 1120 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"  }\n");
                                                            #line 648 "CodeGeneratorJava.cpp.template"
                                                              }

                                                              if (! variable("embedded").boolean())
                                                              {
                                                            #line 1128 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"  public String[] getExpectedTokenSet()\n");
  append(L"  {\n");
  append(L"    return getTokenSet(- state);\n");
  append(L"  }\n");
                                                            #line 657 "CodeGeneratorJava.cpp.template"
                                                              }
                                                              if (variable("trace").boolean())
                                                              {
                                                            #line 1138 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"  private static String xmlEscape(String s)\n");
  append(L"  {\n");
  append(L"    StringBuilder sb = new StringBuilder();\n");
  append(L"    for (int i = 0; i < s.");
                                                            #line 664 "CodeGeneratorJava.cpp.template"
                                                                if (targetLanguage == JAVA)
                                                                {
                                                            #line 1147 "CodeGeneratorJava.cpp"
  append(L"length()");
                                                            #line 666 "CodeGeneratorJava.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1153 "CodeGeneratorJava.cpp"
  append(L"Length");
                                                            #line 669 "CodeGeneratorJava.cpp.template"
                                                                }
                                                            #line 1157 "CodeGeneratorJava.cpp"
  append(L"; ++i)\n");
  append(L"    {");
                                                            #line 672 "CodeGeneratorJava.cpp.template"
                                                                if (targetLanguage == JAVA)
                                                                {
                                                            #line 1163 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"      char c = s.charAt(i);");
                                                            #line 675 "CodeGeneratorJava.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1170 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"      char c = s[i];");
                                                            #line 679 "CodeGeneratorJava.cpp.template"
                                                                }
                                                            #line 1175 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"      switch (c)\n");
  append(L"      {\n");
  append(L"      case '<': sb.");
                                                            #line 683 "CodeGeneratorJava.cpp.template"
                                                                print(targetLanguage == JAVA ? "a" : "A");
                                                            #line 1182 "CodeGeneratorJava.cpp"
  append(L"ppend(\"&lt;\"); break;\n");
  append(L"      case '\"': sb.");
                                                            #line 685 "CodeGeneratorJava.cpp.template"
                                                                print(targetLanguage == JAVA ? "a" : "A");
                                                            #line 1187 "CodeGeneratorJava.cpp"
  append(L"ppend(\"&quot;\"); break;\n");
  append(L"      case '&': sb.");
                                                            #line 687 "CodeGeneratorJava.cpp.template"
                                                                print(targetLanguage == JAVA ? "a" : "A");
                                                            #line 1192 "CodeGeneratorJava.cpp"
  append(L"ppend(\"&amp;\"); break;");
                                                            #line 689 "CodeGeneratorJava.cpp.template"
                                                                if (targetLanguage == JAVA)
                                                                {
                                                            #line 1197 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"      default : sb.append(c); break;");
                                                            #line 692 "CodeGeneratorJava.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1204 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"      default : sb.Append(c.ToString()); break;");
                                                            #line 696 "CodeGeneratorJava.cpp.template"
                                                                }
                                                            #line 1209 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"      }\n");
  append(L"    }");
                                                            #line 700 "CodeGeneratorJava.cpp.template"
                                                                if (targetLanguage == JAVA)
                                                                {
                                                            #line 1216 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"    return sb.toString();");
                                                            #line 703 "CodeGeneratorJava.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1223 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"    return sb.ToString();");
                                                            #line 707 "CodeGeneratorJava.cpp.template"
                                                                }
                                                            #line 1228 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"  }\n");
                                                            #line 710 "CodeGeneratorJava.cpp.template"
                                                                if (targetLanguage == JAVA)
                                                                {
                                                            #line 1234 "CodeGeneratorJava.cpp"
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
                                                            #line 729 "CodeGeneratorJava.cpp.template"
                                                                  if (variable("embedded").boolean())
                                                                  {
                                                            #line 1255 "CodeGeneratorJava.cpp"
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
                                                            #line 743 "CodeGeneratorJava.cpp.template"
                                                                  }
                                                                }
                                                                else
                                                                {
                                                            #line 1273 "CodeGeneratorJava.cpp"
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
                                                            #line 757 "CodeGeneratorJava.cpp.template"
                                                                  if (variable("embedded").boolean())
                                                                  {
                                                            #line 1287 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"  private void flushTrace()\n");
  append(L"  {\n");
  append(L"    err.Flush();\n");
  append(L"  }\n");
                                                            #line 764 "CodeGeneratorJava.cpp.template"
                                                                  }
                                                                }
                                                              }
                                                              if (variable("nolexer").boolean())
                                                              {
                                                            #line 1299 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"  public static int getTokenCount() {return ");
                                                            #line 770 "CodeGeneratorJava.cpp.template"
                                                                print(variable("t1").size);
                                                            #line 1304 "CodeGeneratorJava.cpp"
  append(L";}\n");
  append(L"  public static String getTokenName(int code) {return code >= 0 && code < ");
                                                            #line 773 "CodeGeneratorJava.cpp.template"
                                                                print(variable("t1").size);
                                                            #line 1309 "CodeGeneratorJava.cpp"
  append(L" ? TOKEN[code] : null;}\n");
  append(L"  public static int getTokenSetCount() {return ");
                                                            #line 775 "CodeGeneratorJava.cpp.template"
                                                                print(variable("entrycount").integer());
                                                            #line 1314 "CodeGeneratorJava.cpp"
  append(L";}\n");
  append(L"\n");
  append(L"  public static String[] getTokenSet(int tokenSetId)");
                                                            #line 778 "CodeGeneratorJava.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 1322 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"  private static String[] getTokenSet(int tokenSetId)");
                                                            #line 782 "CodeGeneratorJava.cpp.template"
                                                              }
                                                            #line 1327 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"  {");
                                                            #line 785 "CodeGeneratorJava.cpp.template"
                                                              if (targetLanguage == JAVA)
                                                              {
                                                            #line 1333 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"    java.util.ArrayList<String> expected = new java.util.ArrayList<>();");
                                                            #line 789 "CodeGeneratorJava.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 1340 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"    List<String> expected = new List<String>();");
                                                            #line 793 "CodeGeneratorJava.cpp.template"
                                                              }

                                                              if (! variable("nolexer").boolean())
                                                              {
                                                            #line 1348 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"    int s = tokenSetId < 0 ? - tokenSetId : INITIAL[tokenSetId] & ");
                                                            #line 799 "CodeGeneratorJava.cpp.template"
                                                              print(Math::powerof(2, variable("stateCodeBits").integer()) - 1);
                                                            #line 1353 "CodeGeneratorJava.cpp"
  append(L";");
                                                            #line 801 "CodeGeneratorJava.cpp.template"
                                                              }
                                                            #line 1357 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"    for (int i = 0; i < ");
                                                            #line 803 "CodeGeneratorJava.cpp.template"
                                                              print(variable("t1").size);
                                                            #line 1362 "CodeGeneratorJava.cpp"
  append(L"; i += 32)\n");
  append(L"    {\n");
  append(L"      int j = i;\n");
  append(L"      int i0 = (i >> 5) * ");
                                                            #line 807 "CodeGeneratorJava.cpp.template"
                                                              print(variable("transitionStateCount").integer());
                                                            #line 1369 "CodeGeneratorJava.cpp"
  append(L" + ");
                                                            #line 808 "CodeGeneratorJava.cpp.template"
                                                              if (variable("nolexer").boolean())
                                                              {
                                                            #line 1374 "CodeGeneratorJava.cpp"
  append(L"tokenSetId");
                                                            #line 810 "CodeGeneratorJava.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 1380 "CodeGeneratorJava.cpp"
  append(L"s - 1");
                                                            #line 813 "CodeGeneratorJava.cpp.template"
                                                              }
                                                            #line 1384 "CodeGeneratorJava.cpp"
  append(L";\n");
                                                            #line 815 "CodeGeneratorJava.cpp.template"
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
                                                            #line 1406 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"      for ( ; f != 0; f ");
                                                            #line 835 "CodeGeneratorJava.cpp.template"
                                                              print(shift);
                                                            #line 1411 "CodeGeneratorJava.cpp"
  append(L" 1, ++j)\n");
  append(L"      {\n");
  append(L"        if ((f & 1) != 0)\n");
  append(L"        {\n");
  append(L"          expected.");
                                                            #line 840 "CodeGeneratorJava.cpp.template"
                                                              print(add);
                                                            #line 1419 "CodeGeneratorJava.cpp"
  append(L"(TOKEN[j]);\n");
  append(L"        }\n");
  append(L"      }\n");
  append(L"    }\n");
  append(L"    return expected.");
                                                            #line 845 "CodeGeneratorJava.cpp.template"
                                                              print(toArray);
                                                            #line 1427 "CodeGeneratorJava.cpp"
  append(L";\n");
  append(L"  }");
                                                            #line 847 "CodeGeneratorJava.cpp.template"
                                                              generateData();
                                                              if (! variable("embedded").boolean())
                                                              {
                                                            #line 1434 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"\n");
  append(L"  public enum Token\n");
  append(L"  {\n");
  append(L"    ");
                                                            #line 854 "CodeGeneratorJava.cpp.template"
                                                                const CGVariable &token = variable("token");
                                                                int w = (int) Format::width(token.size);
                                                                for (size_t i = 0; i < token.size; ++i)
                                                                {
                                                                  if (i)
                                                                  {
                                                            #line 1447 "CodeGeneratorJava.cpp"
  append(L",\n");
  append(L"    ");
                                                            #line 861 "CodeGeneratorJava.cpp.template"
                                                                  }
                                                            #line 1452 "CodeGeneratorJava.cpp"
  append(L"/* ");
                                                            #line 862 "CodeGeneratorJava.cpp.template"
                                                                  print(format.toString<char>(i, 10, w));
                                                            #line 1456 "CodeGeneratorJava.cpp"
  append(L" */ ");
                                                            #line 863 "CodeGeneratorJava.cpp.template"
                                                                  print(token.string(i));
                                                                }
                                                            #line 1461 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"  };");
                                                            #line 867 "CodeGeneratorJava.cpp.template"
                                                              }
                                                              if (variable("selfTest").boolean())
                                                              {
                                                            #line 1468 "CodeGeneratorJava.cpp"
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
                                                            #line 888 "CodeGeneratorJava.cpp.template"
                                                                if (codepoints)
                                                                {
                                                            #line 1490 "CodeGeneratorJava.cpp"
  append(L"codePointCount(0, tokenString.length())");
                                                            #line 891 "CodeGeneratorJava.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1496 "CodeGeneratorJava.cpp"
  append(L"length()");
                                                            #line 895 "CodeGeneratorJava.cpp.template"
                                                                }
                                                            #line 1500 "CodeGeneratorJava.cpp"
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
                                                            #line 914 "CodeGeneratorJava.cpp.template"
                                                              print(variable("classname").string());
                                                            #line 1522 "CodeGeneratorJava.cpp"
  append(L" testee = new ");
                                                            #line 915 "CodeGeneratorJava.cpp.template"
                                                              print(variable("classname").string());
                                                            #line 1526 "CodeGeneratorJava.cpp"
  append(L"();\n");
  append(L"    for (int e = 0; e < ");
                                                            #line 917 "CodeGeneratorJava.cpp.template"
                                                              print(variable("a0").size);
                                                            #line 1531 "CodeGeneratorJava.cpp"
  append(L"; ++e)\n");
  append(L"    {\n");
  append(L"      int s = INITIAL[e] & ");
                                                            #line 920 "CodeGeneratorJava.cpp.template"
                                                              print(Math::powerof(2, variable("stateCodeBits").integer()) - 1);
                                                            #line 1537 "CodeGeneratorJava.cpp"
  append(L";\n");
  append(L"      for (int i = 0; i < ");
                                                            #line 922 "CodeGeneratorJava.cpp.template"
                                                              print(variable("t1").size);
                                                            #line 1542 "CodeGeneratorJava.cpp"
  append(L"; i += 32)\n");
  append(L"      {\n");
  append(L"        int j = i;\n");
  append(L"        int i0 = (i >> 5) * ");
                                                            #line 926 "CodeGeneratorJava.cpp.template"
                                                              print(variable("transitionStateCount").integer());
                                                            #line 1549 "CodeGeneratorJava.cpp"
  append(L" + s - 1;\n");
                                                            #line 928 "CodeGeneratorJava.cpp.template"
                                                              compressedMapAccessor(8, "i", "int f = ", "EXPECTED", &variable("t0bits").integer());
                                                            #line 1553 "CodeGeneratorJava.cpp"
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
                                                            #line 939 "CodeGeneratorJava.cpp.template"
                                                              }
                                                            #line 1567 "CodeGeneratorJava.cpp"
  append(L"\n");
                                                            #line 941 "CodeGeneratorJava.cpp.template"
                                                              if (! variable("embedded").boolean())
                                                              {
                                                            #line 1572 "CodeGeneratorJava.cpp"
  append(L"}\n");
                                                            #line 944 "CodeGeneratorJava.cpp.template"
                                                              }
                                                            }

                                                            void CodeGeneratorJava::generateCompressedMap()
                                                            {
                                                            #line 1580 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"public class ");
                                                            #line 950 "CodeGeneratorJava.cpp.template"
                                                              print(variable("classname").string());
                                                            #line 1585 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"{\n");
  append(L"  public static int get(int i0)\n");
  append(L"  {\n");
  append(L"    if (i0 < 0 || i0 >= ");
                                                            #line 955 "CodeGeneratorJava.cpp.template"
                                                              print(variable("size").integer());
                                                            #line 1593 "CodeGeneratorJava.cpp"
  append(L")\n");
  append(L"      return 0;");
                                                            #line 958 "CodeGeneratorJava.cpp.template"
                                                              size_t i = 4;
                                                              if (variable("rm").size > 0)
                                                              {
                                                                i += 2;
                                                            #line 1601 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"    if (i0 < 0x30000)\n");
  append(L"    {");
                                                            #line 964 "CodeGeneratorJava.cpp.template"
                                                              }
                                                            #line 1607 "CodeGeneratorJava.cpp"
  append(L"\n");
                                                            #line 966 "CodeGeneratorJava.cpp.template"
                                                              compressedMapAccessor(i, "i", "return ", "LOW", &variable("dtbits").integer());
                                                              if (variable("rm").size > 0)
                                                              {
                                                            #line 1613 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"    }\n");
  append(L"    else\n");
  append(L"    {");
                                                            #line 972 "CodeGeneratorJava.cpp.template"
                                                                indent += 3;
                                                                generateBinarySearch("i0", "return ", "", "HIGH", variable("rm").size);
                                                                indent -= 3;
                                                            #line 1622 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"    }");
                                                            #line 976 "CodeGeneratorJava.cpp.template"
                                                              }
                                                            #line 1627 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"  }");
                                                            #line 978 "CodeGeneratorJava.cpp.template"
                                                              generateData();
                                                            #line 1632 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"}\n");
                                                            #line 981 "CodeGeneratorJava.cpp.template"
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
                                                              for (VarsInInsertionOrder::iterator a(varsInInsertionOrder.begin());
                                                                   a != varsInInsertionOrder.end(); ++a)
                                                                if (   a->isArray()
                                                                    && a->size > 0
                                                                    && (a->hasType(CGVariable::INTEGER) || a->hasType(CGVariable::UNSIGNED))
                                                                    && strlen(a->name) == 2)
                                                              {
                                                            #line 1661 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"\n");
  append(L"  private static ");
                                                            #line 1008 "CodeGeneratorJava.cpp.template"
                                                                if (targetLanguage == JAVA)
                                                                {
                                                            #line 1668 "CodeGeneratorJava.cpp"
  append(L"final");
                                                            #line 1010 "CodeGeneratorJava.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1674 "CodeGeneratorJava.cpp"
  append(L"readonly");
                                                            #line 1013 "CodeGeneratorJava.cpp.template"
                                                                }
                                                            #line 1678 "CodeGeneratorJava.cpp"
  append(L" ");
                                                            #line 1014 "CodeGeneratorJava.cpp.template"
                                                                if (a->hasType(CGVariable::UNSIGNED))
                                                                {
                                                            #line 1683 "CodeGeneratorJava.cpp"
  append(L"u");
                                                            #line 1016 "CodeGeneratorJava.cpp.template"
                                                                }
                                                            #line 1687 "CodeGeneratorJava.cpp"
  append(L"int[] ");
                                                            #line 1017 "CodeGeneratorJava.cpp.template"
                                                                print(a->longName);
                                                            #line 1691 "CodeGeneratorJava.cpp"
  append(L" =");
                                                            #line 1018 "CodeGeneratorJava.cpp.template"
                                                                if (asString)
                                                                {
                                                            #line 1696 "CodeGeneratorJava.cpp"
  append(L" new int[");
                                                            #line 1020 "CodeGeneratorJava.cpp.template"
                                                                  print(a->size);
                                                            #line 1700 "CodeGeneratorJava.cpp"
  append(L"];\n");
  append(L"  static\n");
  append(L"  {\n");
  append(L"    final String s1[] =\n");
  append(L"    {");
                                                            #line 1025 "CodeGeneratorJava.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1710 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"  {");
                                                            #line 1029 "CodeGeneratorJava.cpp.template"
                                                                }
                                                                int w = (int) Format::width(a->size);
                                                                for (size_t j = 0; j < a->size; ++j)
                                                                {
                                                                  if (j == 0 || lineLength() + Format::width(a->integer(j)) + (asString ? 3 : 2) > limit)
                                                                  {
                                                                    if (j) print(asString ? "\"," : ",");
                                                            #line 1721 "CodeGeneratorJava.cpp"
  append(L"\n");
                                                            #line 1037 "CodeGeneratorJava.cpp.template"
                                                                    if (asString) print("  ");
                                                            #line 1725 "CodeGeneratorJava.cpp"
  append(L"    /* ");
                                                            #line 1038 "CodeGeneratorJava.cpp.template"
                                                                    print(format.toString<char>(j, 10, w));
                                                            #line 1729 "CodeGeneratorJava.cpp"
  append(L" */ ");
                                                            #line 1039 "CodeGeneratorJava.cpp.template"
                                                                    if (asString) print("\"");
                                                                  }
                                                                  else
                                                                  {
                                                            #line 1736 "CodeGeneratorJava.cpp"
  append(L", ");
                                                            #line 1043 "CodeGeneratorJava.cpp.template"
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
                                                            #line 1751 "CodeGeneratorJava.cpp"
  append(L"\"\n");
  append(L"    };\n");
  append(L"    String[] s2 = java.util.Arrays.toString(s1).replaceAll(\"[ \\\\[\\\\]]\", \"\").split(\",\");\n");
  append(L"    for (int i = 0; i < ");
                                                            #line 1058 "CodeGeneratorJava.cpp.template"
                                                                  print(a->size);
                                                            #line 1758 "CodeGeneratorJava.cpp"
  append(L"; ++i) {");
                                                            #line 1059 "CodeGeneratorJava.cpp.template"
                                                                  print(a->longName);
                                                            #line 1762 "CodeGeneratorJava.cpp"
  append(L"[i] = Integer.parseInt(s2[i]);}\n");
  append(L"  }");
                                                            #line 1061 "CodeGeneratorJava.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1769 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"  };");
                                                            #line 1065 "CodeGeneratorJava.cpp.template"
                                                                }
                                                              }
                                                              for (VarsInInsertionOrder::iterator a(varsInInsertionOrder.begin());
                                                                   a != varsInInsertionOrder.end(); ++a)
                                                                if (a->isArray() && a->size > 0 && a->hasType(CGVariable::STRING) && strlen(a->name) == 2)
                                                              {
                                                            #line 1779 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"\n");
  append(L"  private static ");
                                                            #line 1073 "CodeGeneratorJava.cpp.template"
                                                                if (targetLanguage == JAVA)
                                                                {
                                                            #line 1786 "CodeGeneratorJava.cpp"
  append(L"final");
                                                            #line 1075 "CodeGeneratorJava.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1792 "CodeGeneratorJava.cpp"
  append(L"readonly");
                                                            #line 1078 "CodeGeneratorJava.cpp.template"
                                                                }
                                                            #line 1796 "CodeGeneratorJava.cpp"
  append(L" String[] ");
                                                            #line 1079 "CodeGeneratorJava.cpp.template"
                                                                print(a->longName);
                                                            #line 1800 "CodeGeneratorJava.cpp"
  append(L" =\n");
  append(L"  {\n");
                                                            #line 1082 "CodeGeneratorJava.cpp.template"
                                                                for (size_t j = 0; j < a->size; ++j)
                                                                {
                                                                  if (j)
                                                                  {
                                                            #line 1808 "CodeGeneratorJava.cpp"
  append(L",\n");
                                                            #line 1087 "CodeGeneratorJava.cpp.template"
                                                                  }
                                                            #line 1812 "CodeGeneratorJava.cpp"
  append(L"    \"");
                                                            #line 1088 "CodeGeneratorJava.cpp.template"
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
                                                            #line 1827 "CodeGeneratorJava.cpp"
  append(L"\"");
                                                            #line 1100 "CodeGeneratorJava.cpp.template"
                                                                }
                                                            #line 1831 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"  };");
                                                            #line 1102 "CodeGeneratorJava.cpp.template"
                                                              }
                                                            }

                                                            void CodeGeneratorJava::generateBinarySearch(const char *input, const char *outputPrefix, const char *outputSuffix, const char *map, size_t size)
                                                            {
                                                            #line 1840 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"int lo = 0, hi = ");
                                                            #line 1108 "CodeGeneratorJava.cpp.template"
                                                              print(size / 3 - 1);
                                                            #line 1845 "CodeGeneratorJava.cpp"
  append(L";\n");
  append(L"for (int m = ");
                                                            #line 1110 "CodeGeneratorJava.cpp.template"
                                                              print((size / 3) >> 1);
                                                            #line 1850 "CodeGeneratorJava.cpp"
  append(L"; ; m = (hi + lo) >> 1)\n");
  append(L"{\n");
  append(L"  if (");
                                                            #line 1113 "CodeGeneratorJava.cpp.template"
                                                              print(map);
                                                            #line 1856 "CodeGeneratorJava.cpp"
  append(L"[m] > ");
                                                            #line 1114 "CodeGeneratorJava.cpp.template"
                                                              print(input);
                                                            #line 1860 "CodeGeneratorJava.cpp"
  append(L") {hi = m - 1;}\n");
  append(L"  else if (");
                                                            #line 1116 "CodeGeneratorJava.cpp.template"
                                                              print(map);
                                                            #line 1865 "CodeGeneratorJava.cpp"
  append(L"[");
                                                            #line 1117 "CodeGeneratorJava.cpp.template"
                                                              print(size / 3);
                                                            #line 1869 "CodeGeneratorJava.cpp"
  append(L" + m] < ");
                                                            #line 1118 "CodeGeneratorJava.cpp.template"
                                                              print(input);
                                                            #line 1873 "CodeGeneratorJava.cpp"
  append(L") {lo = m + 1;}\n");
  append(L"  else {");
                                                            #line 1120 "CodeGeneratorJava.cpp.template"
                                                              print(outputPrefix);
                                                              print(map);
                                                            #line 1879 "CodeGeneratorJava.cpp"
  append(L"[");
                                                            #line 1122 "CodeGeneratorJava.cpp.template"
                                                              print(size / 3 * 2);
                                                            #line 1883 "CodeGeneratorJava.cpp"
  append(L" + m]");
                                                            #line 1123 "CodeGeneratorJava.cpp.template"
                                                              print(outputSuffix);
                                                            #line 1887 "CodeGeneratorJava.cpp"
  append(L";}\n");
  append(L"  if (lo > hi) {");
                                                            #line 1125 "CodeGeneratorJava.cpp.template"
                                                              print(outputPrefix);
                                                            #line 1892 "CodeGeneratorJava.cpp"
  append(L"0");
                                                            #line 1126 "CodeGeneratorJava.cpp.template"
                                                              print(outputSuffix);
                                                            #line 1896 "CodeGeneratorJava.cpp"
  append(L";}\n");
  append(L"}");
                                                            #line 1128 "CodeGeneratorJava.cpp.template"
                                                            }

// End
