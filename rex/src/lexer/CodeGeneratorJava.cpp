// This file was generated on Sun Nov 24, 2024 16:09 (UTC+01) by REx v6.0 which is Copyright (c) 1979-2024 by Gunther Rademacher <grd@gmx.net>
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
                                                              if (! variable("append").boolean() && ! variable("embedded").boolean())
                                                              {
                                                                if (*variable("package").string())
                                                                {
                                                            #line 22 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"package ");
                                                            #line 19 "CodeGeneratorJava.cpp.template"
                                                                  print(variable("package").string());
                                                            #line 27 "CodeGeneratorJava.cpp"
  append(L";\n");
                                                            #line 21 "CodeGeneratorJava.cpp.template"
                                                                }
                                                                if (variable("trace").boolean())
                                                                {
                                                            #line 33 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"import java.io.IOException;\n");
  append(L"import java.io.OutputStreamWriter;\n");
  append(L"import java.io.UnsupportedEncodingException;\n");
  append(L"import java.io.Writer;\n");
                                                            #line 29 "CodeGeneratorJava.cpp.template"
                                                                }
                                                            #line 41 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"public class ");
                                                            #line 31 "CodeGeneratorJava.cpp.template"
                                                                print(variable("classname").string());
                                                            #line 46 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"{\n");
                                                            #line 34 "CodeGeneratorJava.cpp.template"
                                                              }
                                                              if (variable("useGlr").boolean())
                                                              {
                                                                ++indent;
                                                              }
                                                              else
                                                              {
                                                            #line 57 "CodeGeneratorJava.cpp"
  append(L"  private ");
                                                            #line 41 "CodeGeneratorJava.cpp.template"
                                                                if (targetLanguage == JAVA)
                                                                {
                                                            #line 62 "CodeGeneratorJava.cpp"
  append(L"CharSequence");
                                                            #line 43 "CodeGeneratorJava.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 68 "CodeGeneratorJava.cpp"
  append(L"String");
                                                            #line 46 "CodeGeneratorJava.cpp.template"
                                                                }
                                                            #line 72 "CodeGeneratorJava.cpp"
  append(L" input = null;");
                                                            #line 48 "CodeGeneratorJava.cpp.template"
                                                                if (! variable("nolexer").boolean())
                                                                {
                                                            #line 77 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"  private int size = 0;");
                                                            #line 51 "CodeGeneratorJava.cpp.template"
                                                                }
                                                              }
                                                            #line 83 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"  private int begin = 0;\n");
  append(L"  private int end = 0;");
                                                            #line 55 "CodeGeneratorJava.cpp.template"
                                                              if (variable("nolexer").boolean())
                                                              {
                                                            #line 90 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"  private Lexer lexer = null;\n");
  append(L"  private Token token = new Token();");
                                                            #line 59 "CodeGeneratorJava.cpp.template"
                                                              }
                                                              if (! variable("embedded").boolean())
                                                              {
                                                            #line 98 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"  private int state = 0;");
                                                            #line 63 "CodeGeneratorJava.cpp.template"
                                                              }
                                                              if (variable("trace").boolean() && ! variable("useGlr").boolean())
                                                              {
                                                                if (targetLanguage == JAVA)
                                                                {
                                                            #line 107 "CodeGeneratorJava.cpp"
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
                                                            #line 77 "CodeGeneratorJava.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 122 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"  private TextWriter err = Console.Error;");
                                                            #line 81 "CodeGeneratorJava.cpp.template"
                                                                }
                                                              }
                                                            #line 128 "CodeGeneratorJava.cpp"
  append(L"\n");
                                                            #line 85 "CodeGeneratorJava.cpp.template"
                                                              if (! variable("embedded").boolean())
                                                              {
                                                            #line 133 "CodeGeneratorJava.cpp"
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
                                                            #line 105 "CodeGeneratorJava.cpp.template"
                                                              }
                                                              else
                                                              {
                                                                if (variable("lrparser").boolean() ||
                                                                    variable("tables").boolean())
                                                                {
                                                            #line 160 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 112 "CodeGeneratorJava.cpp.template"
                                                                  print(variable("useGlr").boolean() ? "public" : "private");
                                                            #line 165 "CodeGeneratorJava.cpp"
  append(L" int predict(int dpi)");
                                                            #line 113 "CodeGeneratorJava.cpp.template"
                                                                  predict();
                                                                }
                                                            #line 170 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"  private");
                                                            #line 117 "CodeGeneratorJava.cpp.template"
                                                              }
                                                            #line 175 "CodeGeneratorJava.cpp"
  append(L" int match(int tokenSetId)\n");
  append(L"  {");
                                                            #line 119 "CodeGeneratorJava.cpp.template"
                                                              if (variable("nolexer").boolean())
                                                              {
                                                            #line 181 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"    token.begin = end;\n");
  append(L"    lexer.match(tokenSetId, token);\n");
  append(L"    begin = token.begin;\n");
  append(L"    end = token.end;\n");
  append(L"    return token.code >= 0\n");
  append(L"         ? token.code\n");
  append(L"         : error(begin, end, - tokenSetId, -1, -1);\n");
  append(L"  }\n");
                                                            #line 130 "CodeGeneratorJava.cpp.template"
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
                                                            #line 203 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 142 "CodeGeneratorJava.cpp.template"
                                                                  if (variable("useGlr").boolean() && targetLanguage != JAVA)
                                                                  {
                                                            #line 209 "CodeGeneratorJava.cpp"
  append(L"parser.");
                                                            #line 144 "CodeGeneratorJava.cpp.template"
                                                                  }
                                                            #line 213 "CodeGeneratorJava.cpp"
  append(L"writeTrace(\"  <tokenize ");
                                                            #line 146 "CodeGeneratorJava.cpp.template"
                                                                  if (variable("useGlr").boolean())
                                                                  {
                                                            #line 218 "CodeGeneratorJava.cpp"
  append(L"thread=\\\"\" + id + \"\\\" ");
                                                            #line 148 "CodeGeneratorJava.cpp.template"
                                                                  }
                                                            #line 222 "CodeGeneratorJava.cpp"
  append(L"tokenset=\\\"\" + tokenSetId + \"\\\">\\n\");\n");
                                                            #line 150 "CodeGeneratorJava.cpp.template"
                                                                }
                                                                if (lookahead)
                                                                {
                                                                  if (targetLanguage == JAVA)
                                                                  {
                                                            #line 230 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"    boolean nonbmp = false;");
                                                            #line 156 "CodeGeneratorJava.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 237 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"    bool nonbmp = false;");
                                                            #line 160 "CodeGeneratorJava.cpp.template"
                                                                  }
                                                                }
                                                            #line 243 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"    begin = end;\n");
  append(L"    int current = end;\n");
  append(L"    int result = INITIAL[tokenSetId];");
                                                            #line 165 "CodeGeneratorJava.cpp.template"
                                                                if (variable("embedded").boolean() && (variable("trace").boolean() || ! variable("useGlr").boolean()))
                                                                {
                                                            #line 251 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"    int state = 0;");
                                                            #line 168 "CodeGeneratorJava.cpp.template"
                                                                }
                                                            #line 256 "CodeGeneratorJava.cpp"
  append(L"\n");
                                                            #line 170 "CodeGeneratorJava.cpp.template"
                                                                if (variable("trace").boolean())
                                                                {
                                                            #line 261 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 173 "CodeGeneratorJava.cpp.template"
                                                                  if (variable("useGlr").boolean() && targetLanguage != JAVA)
                                                                  {
                                                            #line 267 "CodeGeneratorJava.cpp"
  append(L"parser.");
                                                            #line 175 "CodeGeneratorJava.cpp.template"
                                                                  }
                                                            #line 271 "CodeGeneratorJava.cpp"
  append(L"writeTrace(\"    <next state=\\\"\" + (result & ");
                                                            #line 176 "CodeGeneratorJava.cpp.template"
                                                                  print(Math::powerof(2, variable("stateCodeBits").integer()) - 1);
                                                            #line 275 "CodeGeneratorJava.cpp"
  append(L") + \"\\\"\");");
                                                            #line 177 "CodeGeneratorJava.cpp.template"
                                                                }
                                                            #line 279 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"    for (int code = result & ");
                                                            #line 179 "CodeGeneratorJava.cpp.template"
                                                                print(Math::powerof(2, variable("stateCodeBits").integer()) - 1);
                                                            #line 284 "CodeGeneratorJava.cpp"
  append(L"; code != 0; )\n");
  append(L"    {\n");
  append(L"      int charclass;\n");
  append(L"      int c0 = current < ");
                                                            #line 183 "CodeGeneratorJava.cpp.template"
                                                                print(prefix);
                                                            #line 291 "CodeGeneratorJava.cpp"
  append(L"size ? ");
                                                            #line 184 "CodeGeneratorJava.cpp.template"
                                                                        print(prefix);
                                                            #line 295 "CodeGeneratorJava.cpp"
  append(L"input");
                                                            #line 185 "CodeGeneratorJava.cpp.template"
                                                                if (targetLanguage == JAVA)
                                                                {
                                                            #line 300 "CodeGeneratorJava.cpp"
  append(L".charAt(current)");
                                                            #line 187 "CodeGeneratorJava.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 306 "CodeGeneratorJava.cpp"
  append(L"[current]");
                                                            #line 190 "CodeGeneratorJava.cpp.template"
                                                                }
                                                            #line 310 "CodeGeneratorJava.cpp"
  append(L" : 0;");
                                                            #line 191 "CodeGeneratorJava.cpp.template"
                                                                if (variable("trace").boolean())
                                                                {
                                                            #line 315 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"      ");
                                                            #line 194 "CodeGeneratorJava.cpp.template"
                                                                  if (variable("useGlr").boolean() && targetLanguage != JAVA)
                                                                  {
                                                            #line 321 "CodeGeneratorJava.cpp"
  append(L"parser.");
                                                            #line 196 "CodeGeneratorJava.cpp.template"
                                                                  }
                                                            #line 325 "CodeGeneratorJava.cpp"
  append(L"writeTrace(\" offset=\\\"\" + current + \"\\\"\");");
                                                            #line 197 "CodeGeneratorJava.cpp.template"
                                                                }
                                                            #line 329 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"      ++current;\n");
  append(L"      if (c0 < 0x");
                                                            #line 200 "CodeGeneratorJava.cpp.template"
                                                                print(format.toString<char>(variable("simplifiedCodeMap").integer(), 16, 0, 0, 0, "0123456789abcdef"));
                                                            #line 335 "CodeGeneratorJava.cpp"
  append(L")\n");
  append(L"      {");
                                                            #line 203 "CodeGeneratorJava.cpp.template"
                                                                if (variable("trace").boolean())
                                                                {
                                                            #line 341 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"        if (c0 >= 32 && c0 <= 126)\n");
  append(L"        {\n");
  append(L"          ");
                                                            #line 208 "CodeGeneratorJava.cpp.template"
                                                                  if (variable("useGlr").boolean() && targetLanguage != JAVA)
                                                                  {
                                                            #line 349 "CodeGeneratorJava.cpp"
  append(L"parser.");
                                                            #line 210 "CodeGeneratorJava.cpp.template"
                                                                  }
                                                            #line 353 "CodeGeneratorJava.cpp"
  append(L"writeTrace(\" char=\\\"\" + xmlEscape(");
                                                            #line 211 "CodeGeneratorJava.cpp.template"
                                                                  if (targetLanguage == JAVA)
                                                                  {
                                                            #line 358 "CodeGeneratorJava.cpp"
  append(L"String.valueOf((char) c0)");
                                                            #line 214 "CodeGeneratorJava.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 364 "CodeGeneratorJava.cpp"
  append(L"((char) c0).ToString()");
                                                            #line 218 "CodeGeneratorJava.cpp.template"
                                                                  }
                                                            #line 368 "CodeGeneratorJava.cpp"
  append(L") + \"\\\"\");\n");
  append(L"        }");
                                                            #line 220 "CodeGeneratorJava.cpp.template"
                                                                }
                                                            #line 373 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"        charclass = MAP0[c0];\n");
  append(L"      }\n");
  append(L"      else if (c0 < 0x");
                                                            #line 224 "CodeGeneratorJava.cpp.template"
                                                                print(format.toString<char>(variable("uncompressedMapSize").integer(), 16, 0, 0, 0, "0123456789abcdef"));
                                                            #line 380 "CodeGeneratorJava.cpp"
  append(L")\n");
  append(L"      {\n");
                                                            #line 227 "CodeGeneratorJava.cpp.template"
                                                                compressedMapAccessor(8, "c", "charclass = ", "MAP1", &variable("m1bits").integer());
                                                            #line 385 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"      }\n");
  append(L"      else\n");
  append(L"      {");
                                                            #line 231 "CodeGeneratorJava.cpp.template"
                                                                if (variable("m2").size == 0)
                                                                {
                                                            #line 393 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"        charclass = 0;");
                                                            #line 234 "CodeGeneratorJava.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 400 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"        if (");
                                                            #line 238 "CodeGeneratorJava.cpp.template"
                                                                  if (variable("uncompressedMapSize").integer() != 0xd800)
                                                                  {
                                                            #line 406 "CodeGeneratorJava.cpp"
  append(L"c0 >= 0xd800 && ");
                                                            #line 240 "CodeGeneratorJava.cpp.template"
                                                                  }
                                                            #line 410 "CodeGeneratorJava.cpp"
  append(L"c0 < 0xdc00)\n");
  append(L"        {\n");
  append(L"          int c1 = current < ");
                                                            #line 243 "CodeGeneratorJava.cpp.template"
                                                                  print(prefix);
                                                            #line 416 "CodeGeneratorJava.cpp"
  append(L"size ? ");
                                                            #line 244 "CodeGeneratorJava.cpp.template"
                                                                  print(prefix);
                                                            #line 420 "CodeGeneratorJava.cpp"
  append(L"input");
                                                            #line 245 "CodeGeneratorJava.cpp.template"
                                                                  if (targetLanguage == JAVA)
                                                                  {
                                                            #line 425 "CodeGeneratorJava.cpp"
  append(L".charAt(current)");
                                                            #line 247 "CodeGeneratorJava.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 431 "CodeGeneratorJava.cpp"
  append(L"[current]");
                                                            #line 250 "CodeGeneratorJava.cpp.template"
                                                                  }
                                                            #line 435 "CodeGeneratorJava.cpp"
  append(L" : 0;\n");
  append(L"          if (c1 >= 0xdc00 && c1 < 0xe000)\n");
  append(L"          {");
                                                            #line 253 "CodeGeneratorJava.cpp.template"
                                                                  if (lookahead)
                                                                  {
                                                            #line 442 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"            nonbmp = true;");
                                                            #line 256 "CodeGeneratorJava.cpp.template"
                                                                  }
                                                            #line 447 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"            ++current;\n");
  append(L"            c0 = ((c0 & 0x3ff) << 10) + (c1 & 0x3ff) + 0x10000;\n");
  append(L"          }\n");
  append(L"        }\n");
  append(L"\n");
  append(L"        int lo = 0, hi = ");
                                                            #line 263 "CodeGeneratorJava.cpp.template"
                                                                  print(variable("m2").size / 3 - 1);
                                                            #line 457 "CodeGeneratorJava.cpp"
  append(L";\n");
  append(L"        for (int m = ");
                                                            #line 265 "CodeGeneratorJava.cpp.template"
                                                                  print((variable("m2").size / 3) >> 1);
                                                            #line 462 "CodeGeneratorJava.cpp"
  append(L"; ; m = (hi + lo) >> 1)\n");
  append(L"        {\n");
  append(L"          if (MAP2[m] > c0) {hi = m - 1;}\n");
  append(L"          else if (MAP2[");
                                                            #line 269 "CodeGeneratorJava.cpp.template"
                                                                  print(variable("m2").size / 3);
                                                            #line 469 "CodeGeneratorJava.cpp"
  append(L" + m] < c0) {lo = m + 1;}\n");
  append(L"          else {charclass = MAP2[");
                                                            #line 271 "CodeGeneratorJava.cpp.template"
                                                                  print(variable("m2").size / 3 * 2);
                                                            #line 474 "CodeGeneratorJava.cpp"
  append(L" + m]; break;}\n");
  append(L"          if (lo > hi) {charclass = 0; break;}\n");
  append(L"        }");
                                                            #line 274 "CodeGeneratorJava.cpp.template"
                                                                }
                                                            #line 480 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"      }");
                                                            #line 276 "CodeGeneratorJava.cpp.template"
                                                                if (variable("trace").boolean())
                                                                {
                                                            #line 486 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"      ");
                                                            #line 279 "CodeGeneratorJava.cpp.template"
                                                                  if (variable("useGlr").boolean() && targetLanguage != JAVA)
                                                                  {
                                                            #line 492 "CodeGeneratorJava.cpp"
  append(L"parser.");
                                                            #line 281 "CodeGeneratorJava.cpp.template"
                                                                  }
                                                            #line 496 "CodeGeneratorJava.cpp"
  append(L"writeTrace(\" codepoint=\\\"\" + c0 + \"\\\" class=\\\"\" + charclass + \"\\\"\");");
                                                            #line 283 "CodeGeneratorJava.cpp.template"
                                                                }
                                                            #line 500 "CodeGeneratorJava.cpp"
  append(L"\n");
                                                            #line 285 "CodeGeneratorJava.cpp.template"
                                                                if (variable("trace").boolean() || ! variable("useGlr").boolean())
                                                                {
                                                            #line 505 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"      state = code;");
                                                            #line 288 "CodeGeneratorJava.cpp.template"
                                                                }
                                                            #line 510 "CodeGeneratorJava.cpp"
  append(L"\n");
                                                            #line 290 "CodeGeneratorJava.cpp.template"
                                                                compressedMap2dAccessor("code - 1", "charclass", variable("a1cols").integer(),
                                                                                           6, "i", "code = ", "TRANSITION", &variable("a1bits").integer());
                                                            #line 515 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"\n");
  append(L"      if (code > ");
                                                            #line 294 "CodeGeneratorJava.cpp.template"
                                                                print(Math::powerof(2, variable("stateCodeBits").integer()) - 1);
                                                            #line 521 "CodeGeneratorJava.cpp"
  append(L")\n");
  append(L"      {\n");
  append(L"        result = code;");
                                                            #line 297 "CodeGeneratorJava.cpp.template"
                                                                if (variable("trace").boolean())
                                                                {
                                                            #line 528 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"        ");
                                                            #line 300 "CodeGeneratorJava.cpp.template"
                                                                  if (variable("useGlr").boolean() && targetLanguage != JAVA)
                                                                  {
                                                            #line 534 "CodeGeneratorJava.cpp"
  append(L"parser.");
                                                            #line 302 "CodeGeneratorJava.cpp.template"
                                                                  }
                                                            #line 538 "CodeGeneratorJava.cpp"
  append(L"writeTrace(\" result=\\\"\" + xmlEscape(TOKEN[((result >> ");
                                                            #line 303 "CodeGeneratorJava.cpp.template"
                                                                   print(variable("stateCodeBits").integer());
                                                            #line 542 "CodeGeneratorJava.cpp"
  append(L") & ");
                                                            #line 305 "CodeGeneratorJava.cpp.template"
                                                                  print(Math::powerof(2, variable("tokencodeBits").integer()) - 1);
                                                            #line 546 "CodeGeneratorJava.cpp"
  append(L") - 1]) + \"\\\"\");");
                                                            #line 307 "CodeGeneratorJava.cpp.template"
                                                                  if (lookahead || hasFixedTokenLength)
                                                                  {
                                                                    int contextOffset = variable("stateCodeBits").integer()
                                                                                      + variable("tokencodeBits").integer();
                                                                    int sizeOffset = contextOffset
                                                                                   + (hasFixedTokenLength ? 1 : 0);
                                                                    if (hasFixedTokenLength)
                                                                    {
                                                            #line 557 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"        if ((result & ");
                                                            #line 316 "CodeGeneratorJava.cpp.template"
                                                                      print(Math::powerof(2, contextOffset));
                                                            #line 562 "CodeGeneratorJava.cpp"
  append(L") > 0)\n");
  append(L"        {\n");
  append(L"          ");
                                                            #line 319 "CodeGeneratorJava.cpp.template"
                                                                      if (variable("useGlr").boolean() && targetLanguage != JAVA)
                                                                      {
                                                            #line 569 "CodeGeneratorJava.cpp"
  append(L"parser.");
                                                            #line 321 "CodeGeneratorJava.cpp.template"
                                                                      }
                                                            #line 573 "CodeGeneratorJava.cpp"
  append(L"writeTrace(\" token-size=\\\"\" + (result >> ");
                                                            #line 322 "CodeGeneratorJava.cpp.template"
                                                                      print(sizeOffset);
                                                            #line 577 "CodeGeneratorJava.cpp"
  append(L") + \"\\\"\");\n");
  append(L"        }\n");
  append(L"        else ");
                                                            #line 325 "CodeGeneratorJava.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 585 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"        ");
                                                            #line 329 "CodeGeneratorJava.cpp.template"
                                                                    }
                                                            #line 590 "CodeGeneratorJava.cpp"
  append(L"if ((result >> ");
                                                            #line 330 "CodeGeneratorJava.cpp.template"
                                                                    print(sizeOffset);
                                                            #line 594 "CodeGeneratorJava.cpp"
  append(L") > 0)\n");
  append(L"        {\n");
  append(L"          ");
                                                            #line 333 "CodeGeneratorJava.cpp.template"
                                                                    if (variable("useGlr").boolean() && targetLanguage != JAVA)
                                                                    {
                                                            #line 601 "CodeGeneratorJava.cpp"
  append(L"parser.");
                                                            #line 335 "CodeGeneratorJava.cpp.template"
                                                                    }
                                                            #line 605 "CodeGeneratorJava.cpp"
  append(L"writeTrace(\" trailing-context-size=\\\"\" + (result >> ");
                                                            #line 336 "CodeGeneratorJava.cpp.template"
                                                                    print(sizeOffset);
                                                            #line 609 "CodeGeneratorJava.cpp"
  append(L") + \"\\\"\");\n");
  append(L"        }");
                                                            #line 338 "CodeGeneratorJava.cpp.template"
                                                                  }
                                                                }
                                                            #line 615 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"        code &= ");
                                                            #line 341 "CodeGeneratorJava.cpp.template"
                                                                print(Math::powerof(2, variable("stateCodeBits").integer()) - 1);
                                                            #line 620 "CodeGeneratorJava.cpp"
  append(L";\n");
  append(L"        end = current;\n");
  append(L"      }");
                                                            #line 344 "CodeGeneratorJava.cpp.template"
                                                                if (variable("trace").boolean())
                                                                {
                                                            #line 627 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"      ");
                                                            #line 347 "CodeGeneratorJava.cpp.template"
                                                                  if (variable("useGlr").boolean() && targetLanguage != JAVA)
                                                                  {
                                                            #line 633 "CodeGeneratorJava.cpp"
  append(L"parser.");
                                                            #line 349 "CodeGeneratorJava.cpp.template"
                                                                  }
                                                            #line 637 "CodeGeneratorJava.cpp"
  append(L"writeTrace(\"/>\\n\");\n");
  append(L"      if (code != 0)\n");
  append(L"      {\n");
  append(L"        ");
                                                            #line 353 "CodeGeneratorJava.cpp.template"
                                                                  if (variable("useGlr").boolean() && targetLanguage != JAVA)
                                                                  {
                                                            #line 645 "CodeGeneratorJava.cpp"
  append(L"parser.");
                                                            #line 355 "CodeGeneratorJava.cpp.template"
                                                                  }
                                                            #line 649 "CodeGeneratorJava.cpp"
  append(L"writeTrace(\"    <next state=\\\"\" + code + \"\\\"\");\n");
  append(L"      }");
                                                            #line 357 "CodeGeneratorJava.cpp.template"
                                                                }
                                                            #line 654 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    result >>= ");
                                                            #line 361 "CodeGeneratorJava.cpp.template"
                                                                print(variable("stateCodeBits").integer());
                                                            #line 661 "CodeGeneratorJava.cpp"
  append(L";\n");
  append(L"    if (result == 0)\n");
  append(L"    {\n");
  append(L"      end = current - 1;\n");
  append(L"      int c1 = end < ");
                                                            #line 366 "CodeGeneratorJava.cpp.template"
                                                                print(prefix);
                                                            #line 669 "CodeGeneratorJava.cpp"
  append(L"size ? ");
                                                            #line 367 "CodeGeneratorJava.cpp.template"
                                                                print(prefix);
                                                            #line 673 "CodeGeneratorJava.cpp"
  append(L"input");
                                                            #line 368 "CodeGeneratorJava.cpp.template"
                                                                if (targetLanguage == JAVA)
                                                                {
                                                            #line 678 "CodeGeneratorJava.cpp"
  append(L".charAt(end)");
                                                            #line 370 "CodeGeneratorJava.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 684 "CodeGeneratorJava.cpp"
  append(L"[end]");
                                                            #line 373 "CodeGeneratorJava.cpp.template"
                                                                }
                                                            #line 688 "CodeGeneratorJava.cpp"
  append(L" : 0;\n");
  append(L"      if (c1 >= 0xdc00 && c1 < 0xe000)\n");
  append(L"      {\n");
  append(L"        --end;\n");
  append(L"      }");
                                                            #line 378 "CodeGeneratorJava.cpp.template"
                                                                if (variable("trace").boolean())
                                                                {
                                                            #line 697 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"      ");
                                                            #line 381 "CodeGeneratorJava.cpp.template"
                                                                  if (variable("useGlr").boolean() && targetLanguage != JAVA)
                                                                  {
                                                            #line 703 "CodeGeneratorJava.cpp"
  append(L"parser.");
                                                            #line 383 "CodeGeneratorJava.cpp.template"
                                                                  }
                                                            #line 707 "CodeGeneratorJava.cpp"
  append(L"writeTrace(\"    <fail begin=\\\"\" + begin + \"\\\" end=\\\"\" + end + \"\\\" state=\\\"\" + state + \"\\\"/>\\n\");\n");
  append(L"      ");
                                                            #line 385 "CodeGeneratorJava.cpp.template"
                                                                  if (variable("useGlr").boolean() && targetLanguage != JAVA)
                                                                  {
                                                            #line 713 "CodeGeneratorJava.cpp"
  append(L"parser.");
                                                            #line 387 "CodeGeneratorJava.cpp.template"
                                                                  }
                                                            #line 717 "CodeGeneratorJava.cpp"
  append(L"writeTrace(\"  </tokenize>\\n\");");
                                                            #line 388 "CodeGeneratorJava.cpp.template"
                                                                }
                                                                if (variable("embedded").boolean())
                                                                {
                                                                  if (variable("useGlr").boolean())
                                                                  {
                                                            #line 725 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"      end = begin;\n");
  append(L"      return -1;");
                                                            #line 395 "CodeGeneratorJava.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 733 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"      return error(begin, end, state, -1, -1);");
                                                            #line 399 "CodeGeneratorJava.cpp.template"
                                                                  }
                                                                }
                                                            #line 739 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"    }");
                                                            #line 402 "CodeGeneratorJava.cpp.template"
                                                                lowBits = variable("tokencodeBits").integer();
                                                                if (hasFixedTokenLength && ! lookahead)
                                                                {
                                                            #line 746 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"    else if ((result & ");
                                                            #line 406 "CodeGeneratorJava.cpp.template"
                                                                  print(Math::powerof(2, lowBits));
                                                                  ++lowBits;
                                                            #line 752 "CodeGeneratorJava.cpp"
  append(L") != 0)\n");
  append(L"    {\n");
  append(L"      end = begin;\n");
  append(L"    }");
                                                            #line 411 "CodeGeneratorJava.cpp.template"
                                                                }
                                                                else
                                                                {
                                                                  if (hasFixedTokenLength)
                                                                  {
                                                            #line 763 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"    else if ((result & ");
                                                            #line 417 "CodeGeneratorJava.cpp.template"
                                                                    print(Math::powerof(2, lowBits));
                                                                    ++lowBits;
                                                            #line 769 "CodeGeneratorJava.cpp"
  append(L") != 0)\n");
  append(L"    {\n");
  append(L"      end = begin;\n");
  append(L"      if (nonbmp)\n");
  append(L"      {\n");
  append(L"        for (int i = result >> ");
                                                            #line 424 "CodeGeneratorJava.cpp.template"
                                                                    print(lowBits);
                                                            #line 778 "CodeGeneratorJava.cpp"
  append(L"; i > 0; --i)\n");
  append(L"        {\n");
  append(L"          int c1 = end < ");
                                                            #line 427 "CodeGeneratorJava.cpp.template"
                                                                    print(prefix);
                                                            #line 784 "CodeGeneratorJava.cpp"
  append(L"size ? ");
                                                            #line 428 "CodeGeneratorJava.cpp.template"
                                                                    print(prefix);
                                                            #line 788 "CodeGeneratorJava.cpp"
  append(L"input");
                                                            #line 429 "CodeGeneratorJava.cpp.template"
                                                                    if (targetLanguage == JAVA)
                                                                    {
                                                            #line 793 "CodeGeneratorJava.cpp"
  append(L".charAt(end)");
                                                            #line 431 "CodeGeneratorJava.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 799 "CodeGeneratorJava.cpp"
  append(L"[end]");
                                                            #line 434 "CodeGeneratorJava.cpp.template"
                                                                    }
                                                            #line 803 "CodeGeneratorJava.cpp"
  append(L" : 0;\n");
  append(L"          ++end;\n");
  append(L"          if (c1 >= 0xd800 && c1 < 0xdc000)\n");
  append(L"          {\n");
  append(L"            ++end;\n");
  append(L"          }\n");
  append(L"        }\n");
  append(L"      }\n");
  append(L"      else\n");
  append(L"      {\n");
  append(L"        end += (result >> ");
                                                            #line 445 "CodeGeneratorJava.cpp.template"
                                                                    print(lowBits);
                                                            #line 817 "CodeGeneratorJava.cpp"
  append(L");\n");
  append(L"      }\n");
  append(L"    }");
                                                            #line 448 "CodeGeneratorJava.cpp.template"
                                                                  }
                                                                  if (lookahead)
                                                                  {
                                                            #line 825 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"    else if (nonbmp)\n");
  append(L"    {\n");
  append(L"      for (int i = result >> ");
                                                            #line 454 "CodeGeneratorJava.cpp.template"
                                                                    print(lowBits);
                                                            #line 832 "CodeGeneratorJava.cpp"
  append(L"; i > 0; --i)\n");
  append(L"      {\n");
  append(L"        --end;\n");
  append(L"        int c1 = end < ");
                                                            #line 458 "CodeGeneratorJava.cpp.template"
                                                                    print(prefix);
                                                            #line 839 "CodeGeneratorJava.cpp"
  append(L"size ? ");
                                                            #line 459 "CodeGeneratorJava.cpp.template"
                                                                    print(prefix);
                                                            #line 843 "CodeGeneratorJava.cpp"
  append(L"input");
                                                            #line 460 "CodeGeneratorJava.cpp.template"
                                                                    if (targetLanguage == JAVA)
                                                                    {
                                                            #line 848 "CodeGeneratorJava.cpp"
  append(L".charAt(end)");
                                                            #line 462 "CodeGeneratorJava.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 854 "CodeGeneratorJava.cpp"
  append(L"[end]");
                                                            #line 465 "CodeGeneratorJava.cpp.template"
                                                                    }
                                                            #line 858 "CodeGeneratorJava.cpp"
  append(L" : 0;\n");
  append(L"        if (c1 >= 0xdc00 && c1 < 0xe000)\n");
  append(L"        {\n");
  append(L"          --end;\n");
  append(L"        }\n");
  append(L"      }\n");
  append(L"    }\n");
  append(L"    else\n");
  append(L"    {\n");
  append(L"      end -= result >> ");
                                                            #line 475 "CodeGeneratorJava.cpp.template"
                                                                    print(lowBits);
                                                            #line 871 "CodeGeneratorJava.cpp"
  append(L";\n");
  append(L"    }");
                                                            #line 477 "CodeGeneratorJava.cpp.template"
                                                                  }
                                                                }
                                                            #line 877 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"\n");
  append(L"    if (end > ");
                                                            #line 482 "CodeGeneratorJava.cpp.template"
                                                                print(prefix);
                                                            #line 883 "CodeGeneratorJava.cpp"
  append(L"size) end = ");
                                                            #line 483 "CodeGeneratorJava.cpp.template"
                                                                print(prefix);
                                                            #line 887 "CodeGeneratorJava.cpp"
  append(L"size;");
                                                            #line 484 "CodeGeneratorJava.cpp.template"
                                                                if (variable("trace").boolean())
                                                                {
                                                            #line 892 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 487 "CodeGeneratorJava.cpp.template"
                                                                  if (variable("useGlr").boolean() && targetLanguage != JAVA)
                                                                  {
                                                            #line 898 "CodeGeneratorJava.cpp"
  append(L"parser.");
                                                            #line 489 "CodeGeneratorJava.cpp.template"
                                                                  }
                                                            #line 902 "CodeGeneratorJava.cpp"
  append(L"writeTrace(\"    <done result=\\\"\" + xmlEscape(TOKEN[(result & ");
                                                            #line 491 "CodeGeneratorJava.cpp.template"
                                                                  print(Math::powerof(2, variable("tokencodeBits").integer()) - 1);
                                                            #line 906 "CodeGeneratorJava.cpp"
  append(L") - 1]) + \"\\\" begin=\\\"\" + begin + \"\\\" end=\\\"\" + end + \"\\\"/>\\n\");\n");
  append(L"    ");
                                                            #line 493 "CodeGeneratorJava.cpp.template"
                                                                  if (variable("useGlr").boolean() && targetLanguage != JAVA)
                                                                  {
                                                            #line 912 "CodeGeneratorJava.cpp"
  append(L"parser.");
                                                            #line 495 "CodeGeneratorJava.cpp.template"
                                                                  }
                                                            #line 916 "CodeGeneratorJava.cpp"
  append(L"writeTrace(\"  </tokenize>\\n\");");
                                                            #line 496 "CodeGeneratorJava.cpp.template"
                                                                }
                                                                if (hack)
                                                                {
                                                            #line 922 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"    return hack((result & ");
                                                            #line 500 "CodeGeneratorJava.cpp.template"
                                                                  print(Math::powerof(2, variable("tokencodeBits").integer()) - 1);
                                                            #line 927 "CodeGeneratorJava.cpp"
  append(L") - 1);\n");
  append(L"  }\n");
                                                            #line 503 "CodeGeneratorJava.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 934 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"    return (result & ");
                                                            #line 507 "CodeGeneratorJava.cpp.template"
                                                                  print(Math::powerof(2, variable("tokencodeBits").integer()) - 1);
                                                            #line 939 "CodeGeneratorJava.cpp"
  append(L") - 1;\n");
  append(L"  }\n");
                                                            #line 510 "CodeGeneratorJava.cpp.template"
                                                                }
                                                              }

                                                              if (variable("useGlr").boolean())
                                                              {
                                                            #line 948 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"}\n");
                                                            #line 517 "CodeGeneratorJava.cpp.template"
                                                                --indent;
                                                                if (targetLanguage != JAVA)
                                                                {
                                                            #line 955 "CodeGeneratorJava.cpp"
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
                                                            #line 589 "CodeGeneratorJava.cpp.template"
                                                                }
                                                              }

                                                              if (defined("gtbits"))
                                                              {
                                                            #line 1031 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"  private static int goTo(int nonterminal, int state)\n");
  append(L"  {\n");
                                                            #line 597 "CodeGeneratorJava.cpp.template"
                                                                compressedMap2dAccessor("nonterminal", "state", variable("gtcols").integer(),
                                                                                           4, "i", "return ", "GOTO", &variable("gtbits").integer());
                                                            #line 1038 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"  }\n");
                                                            #line 601 "CodeGeneratorJava.cpp.template"
                                                              }

                                                              if (! variable("embedded").boolean())
                                                              {
                                                            #line 1046 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"  public String[] getExpectedTokenSet()\n");
  append(L"  {\n");
  append(L"    return getTokenSet(- state);\n");
  append(L"  }\n");
                                                            #line 610 "CodeGeneratorJava.cpp.template"
                                                              }
                                                              if (variable("trace").boolean())
                                                              {
                                                            #line 1056 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"  private static String xmlEscape(String s)\n");
  append(L"  {\n");
  append(L"    StringBuilder sb = new StringBuilder();\n");
  append(L"    for (int i = 0; i < s.");
                                                            #line 617 "CodeGeneratorJava.cpp.template"
                                                                if (targetLanguage == JAVA)
                                                                {
                                                            #line 1065 "CodeGeneratorJava.cpp"
  append(L"length()");
                                                            #line 619 "CodeGeneratorJava.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1071 "CodeGeneratorJava.cpp"
  append(L"Length");
                                                            #line 622 "CodeGeneratorJava.cpp.template"
                                                                }
                                                            #line 1075 "CodeGeneratorJava.cpp"
  append(L"; ++i)\n");
  append(L"    {");
                                                            #line 625 "CodeGeneratorJava.cpp.template"
                                                                if (targetLanguage == JAVA)
                                                                {
                                                            #line 1081 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"      char c = s.charAt(i);");
                                                            #line 628 "CodeGeneratorJava.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1088 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"      char c = s[i];");
                                                            #line 632 "CodeGeneratorJava.cpp.template"
                                                                }
                                                            #line 1093 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"      switch (c)\n");
  append(L"      {\n");
  append(L"      case '<': sb.");
                                                            #line 636 "CodeGeneratorJava.cpp.template"
                                                                print(targetLanguage == JAVA ? "a" : "A");
                                                            #line 1100 "CodeGeneratorJava.cpp"
  append(L"ppend(\"&lt;\"); break;\n");
  append(L"      case '\"': sb.");
                                                            #line 638 "CodeGeneratorJava.cpp.template"
                                                                print(targetLanguage == JAVA ? "a" : "A");
                                                            #line 1105 "CodeGeneratorJava.cpp"
  append(L"ppend(\"&quot;\"); break;\n");
  append(L"      case '&': sb.");
                                                            #line 640 "CodeGeneratorJava.cpp.template"
                                                                print(targetLanguage == JAVA ? "a" : "A");
                                                            #line 1110 "CodeGeneratorJava.cpp"
  append(L"ppend(\"&amp;\"); break;");
                                                            #line 642 "CodeGeneratorJava.cpp.template"
                                                                if (targetLanguage == JAVA)
                                                                {
                                                            #line 1115 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"      default : sb.append(c); break;");
                                                            #line 645 "CodeGeneratorJava.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1122 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"      default : sb.Append(c.ToString()); break;");
                                                            #line 649 "CodeGeneratorJava.cpp.template"
                                                                }
                                                            #line 1127 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"      }\n");
  append(L"    }");
                                                            #line 653 "CodeGeneratorJava.cpp.template"
                                                                if (targetLanguage == JAVA)
                                                                {
                                                            #line 1134 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"    return sb.toString();");
                                                            #line 656 "CodeGeneratorJava.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1141 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"    return sb.ToString();");
                                                            #line 660 "CodeGeneratorJava.cpp.template"
                                                                }
                                                            #line 1146 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"  }\n");
                                                            #line 663 "CodeGeneratorJava.cpp.template"
                                                                if (targetLanguage == JAVA)
                                                                {
                                                            #line 1152 "CodeGeneratorJava.cpp"
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
                                                            #line 682 "CodeGeneratorJava.cpp.template"
                                                                  if (variable("embedded").boolean())
                                                                  {
                                                            #line 1173 "CodeGeneratorJava.cpp"
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
                                                            #line 696 "CodeGeneratorJava.cpp.template"
                                                                  }
                                                                }
                                                                else
                                                                {
                                                            #line 1191 "CodeGeneratorJava.cpp"
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
                                                            #line 710 "CodeGeneratorJava.cpp.template"
                                                                  if (variable("embedded").boolean())
                                                                  {
                                                            #line 1205 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"  private void flushTrace()\n");
  append(L"  {\n");
  append(L"    err.Flush();\n");
  append(L"  }\n");
                                                            #line 717 "CodeGeneratorJava.cpp.template"
                                                                  }
                                                                }
                                                              }
                                                              if (variable("nolexer").boolean())
                                                              {
                                                            #line 1217 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"  public static int getTokenCount() {return ");
                                                            #line 723 "CodeGeneratorJava.cpp.template"
                                                                print(variable("t1").size);
                                                            #line 1222 "CodeGeneratorJava.cpp"
  append(L";}\n");
  append(L"  public static String getTokenName(int code) {return code >= 0 && code < ");
                                                            #line 726 "CodeGeneratorJava.cpp.template"
                                                                print(variable("t1").size);
                                                            #line 1227 "CodeGeneratorJava.cpp"
  append(L" ? TOKEN[code] : null;}\n");
  append(L"  public static int getTokenSetCount() {return ");
                                                            #line 728 "CodeGeneratorJava.cpp.template"
                                                                print(variable("entrycount").integer());
                                                            #line 1232 "CodeGeneratorJava.cpp"
  append(L";}\n");
  append(L"\n");
  append(L"  public static String[] getTokenSet(int tokenSetId)");
                                                            #line 731 "CodeGeneratorJava.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 1240 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"  private static String[] getTokenSet(int tokenSetId)");
                                                            #line 735 "CodeGeneratorJava.cpp.template"
                                                              }
                                                            #line 1245 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"  {");
                                                            #line 738 "CodeGeneratorJava.cpp.template"
                                                              if (targetLanguage == JAVA)
                                                              {
                                                            #line 1251 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"    java.util.ArrayList<String> expected = new java.util.ArrayList<>();");
                                                            #line 742 "CodeGeneratorJava.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 1258 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"    List<String> expected = new List<String>();");
                                                            #line 746 "CodeGeneratorJava.cpp.template"
                                                              }

                                                              if (! variable("nolexer").boolean())
                                                              {
                                                            #line 1266 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"    int s = tokenSetId < 0 ? - tokenSetId : INITIAL[tokenSetId] & ");
                                                            #line 752 "CodeGeneratorJava.cpp.template"
                                                              print(Math::powerof(2, variable("stateCodeBits").integer()) - 1);
                                                            #line 1271 "CodeGeneratorJava.cpp"
  append(L";");
                                                            #line 754 "CodeGeneratorJava.cpp.template"
                                                              }
                                                            #line 1275 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"    for (int i = 0; i < ");
                                                            #line 756 "CodeGeneratorJava.cpp.template"
                                                              print(variable("t1").size);
                                                            #line 1280 "CodeGeneratorJava.cpp"
  append(L"; i += 32)\n");
  append(L"    {\n");
  append(L"      int j = i;\n");
  append(L"      int i0 = (i >> 5) * ");
                                                            #line 760 "CodeGeneratorJava.cpp.template"
                                                              print(variable("transitionStateCount").integer());
                                                            #line 1287 "CodeGeneratorJava.cpp"
  append(L" + ");
                                                            #line 761 "CodeGeneratorJava.cpp.template"
                                                              if (variable("nolexer").boolean())
                                                              {
                                                            #line 1292 "CodeGeneratorJava.cpp"
  append(L"tokenSetId");
                                                            #line 763 "CodeGeneratorJava.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 1298 "CodeGeneratorJava.cpp"
  append(L"s - 1");
                                                            #line 766 "CodeGeneratorJava.cpp.template"
                                                              }
                                                            #line 1302 "CodeGeneratorJava.cpp"
  append(L";\n");
                                                            #line 768 "CodeGeneratorJava.cpp.template"
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
                                                            #line 1324 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"      for ( ; f != 0; f ");
                                                            #line 788 "CodeGeneratorJava.cpp.template"
                                                              print(shift);
                                                            #line 1329 "CodeGeneratorJava.cpp"
  append(L" 1, ++j)\n");
  append(L"      {\n");
  append(L"        if ((f & 1) != 0)\n");
  append(L"        {\n");
  append(L"          expected.");
                                                            #line 793 "CodeGeneratorJava.cpp.template"
                                                              print(add);
                                                            #line 1337 "CodeGeneratorJava.cpp"
  append(L"(TOKEN[j]);\n");
  append(L"        }\n");
  append(L"      }\n");
  append(L"    }\n");
  append(L"    return expected.");
                                                            #line 798 "CodeGeneratorJava.cpp.template"
                                                              print(toArray);
                                                            #line 1345 "CodeGeneratorJava.cpp"
  append(L";\n");
  append(L"  }");
                                                            #line 800 "CodeGeneratorJava.cpp.template"
                                                              generateData();
                                                              if (! variable("embedded").boolean())
                                                              {
                                                            #line 1352 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"\n");
  append(L"  public enum Token\n");
  append(L"  {\n");
  append(L"    ");
                                                            #line 807 "CodeGeneratorJava.cpp.template"
                                                                const CGVariable &token = variable("token");
                                                                int w = (int) Format::width(token.size);
                                                                for (size_t i = 0; i < token.size; ++i)
                                                                {
                                                                  if (i)
                                                                  {
                                                            #line 1365 "CodeGeneratorJava.cpp"
  append(L",\n");
  append(L"    ");
                                                            #line 814 "CodeGeneratorJava.cpp.template"
                                                                  }
                                                            #line 1370 "CodeGeneratorJava.cpp"
  append(L"/* ");
                                                            #line 815 "CodeGeneratorJava.cpp.template"
                                                                  print(format.toString<char>(i, 10, w));
                                                            #line 1374 "CodeGeneratorJava.cpp"
  append(L" */ ");
                                                            #line 816 "CodeGeneratorJava.cpp.template"
                                                                  print(token.string(i));
                                                                }
                                                            #line 1379 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"  };");
                                                            #line 820 "CodeGeneratorJava.cpp.template"
                                                              }
                                                              if (variable("selfTest").boolean())
                                                              {
                                                            #line 1386 "CodeGeneratorJava.cpp"
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
                                                            #line 858 "CodeGeneratorJava.cpp.template"
                                                              print(variable("classname").string());
                                                            #line 1425 "CodeGeneratorJava.cpp"
  append(L" testee = new ");
                                                            #line 859 "CodeGeneratorJava.cpp.template"
                                                              print(variable("classname").string());
                                                            #line 1429 "CodeGeneratorJava.cpp"
  append(L"();\n");
  append(L"    for (int e = 0; e < ");
                                                            #line 861 "CodeGeneratorJava.cpp.template"
                                                              print(variable("a0").size);
                                                            #line 1434 "CodeGeneratorJava.cpp"
  append(L"; ++e)\n");
  append(L"    {\n");
  append(L"      int s = INITIAL[e] & ");
                                                            #line 864 "CodeGeneratorJava.cpp.template"
                                                              print(Math::powerof(2, variable("stateCodeBits").integer()) - 1);
                                                            #line 1440 "CodeGeneratorJava.cpp"
  append(L";\n");
  append(L"      for (int i = 0; i < ");
                                                            #line 866 "CodeGeneratorJava.cpp.template"
                                                              print(variable("t1").size);
                                                            #line 1445 "CodeGeneratorJava.cpp"
  append(L"; i += 32)\n");
  append(L"      {\n");
  append(L"        int j = i;\n");
  append(L"        int i0 = (i >> 5) * ");
                                                            #line 870 "CodeGeneratorJava.cpp.template"
                                                              print(variable("transitionStateCount").integer());
                                                            #line 1452 "CodeGeneratorJava.cpp"
  append(L" + s - 1;\n");
                                                            #line 872 "CodeGeneratorJava.cpp.template"
                                                              compressedMapAccessor(8, "i", "int f = ", "EXPECTED", &variable("t0bits").integer());
                                                            #line 1456 "CodeGeneratorJava.cpp"
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
                                                            #line 883 "CodeGeneratorJava.cpp.template"
                                                              }
                                                            #line 1470 "CodeGeneratorJava.cpp"
  append(L"\n");
                                                            #line 885 "CodeGeneratorJava.cpp.template"
                                                              if (! variable("embedded").boolean())
                                                              {
                                                            #line 1475 "CodeGeneratorJava.cpp"
  append(L"}\n");
                                                            #line 888 "CodeGeneratorJava.cpp.template"
                                                              }
                                                            }

                                                            void CodeGeneratorJava::generateCompressedMap()
                                                            {
                                                            #line 1483 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"public class ");
                                                            #line 894 "CodeGeneratorJava.cpp.template"
                                                              print(variable("classname").string());
                                                            #line 1488 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"{\n");
  append(L"  public static int get(int i0)\n");
  append(L"  {\n");
  append(L"    if (i0 < 0 || i0 >= ");
                                                            #line 899 "CodeGeneratorJava.cpp.template"
                                                              print(variable("size").integer());
                                                            #line 1496 "CodeGeneratorJava.cpp"
  append(L")\n");
  append(L"      return 0;");
                                                            #line 902 "CodeGeneratorJava.cpp.template"
                                                              size_t i = 4;
                                                              if (variable("rm").size > 0)
                                                              {
                                                                i += 2;
                                                            #line 1504 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"    if (i0 < 0x30000)\n");
  append(L"    {");
                                                            #line 908 "CodeGeneratorJava.cpp.template"
                                                              }
                                                            #line 1510 "CodeGeneratorJava.cpp"
  append(L"\n");
                                                            #line 910 "CodeGeneratorJava.cpp.template"
                                                              compressedMapAccessor(i, "i", "return ", "LOW", &variable("dtbits").integer());
                                                              if (variable("rm").size > 0)
                                                              {
                                                            #line 1516 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"    }\n");
  append(L"    else\n");
  append(L"    {");
                                                            #line 916 "CodeGeneratorJava.cpp.template"
                                                                indent += 3;
                                                                generateBinarySearch("i0", "return ", "", "HIGH", variable("rm").size);
                                                                indent -= 3;
                                                            #line 1525 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"    }");
                                                            #line 920 "CodeGeneratorJava.cpp.template"
                                                              }
                                                            #line 1530 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"  }");
                                                            #line 922 "CodeGeneratorJava.cpp.template"
                                                              generateData();
                                                            #line 1535 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"}\n");
                                                            #line 925 "CodeGeneratorJava.cpp.template"
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
                                                            #line 1564 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"\n");
  append(L"  private static ");
                                                            #line 952 "CodeGeneratorJava.cpp.template"
                                                                if (targetLanguage == JAVA)
                                                                {
                                                            #line 1571 "CodeGeneratorJava.cpp"
  append(L"final");
                                                            #line 954 "CodeGeneratorJava.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1577 "CodeGeneratorJava.cpp"
  append(L"readonly");
                                                            #line 957 "CodeGeneratorJava.cpp.template"
                                                                }
                                                            #line 1581 "CodeGeneratorJava.cpp"
  append(L" ");
                                                            #line 958 "CodeGeneratorJava.cpp.template"
                                                                if (a->hasType(CGVariable::UNSIGNED))
                                                                {
                                                            #line 1586 "CodeGeneratorJava.cpp"
  append(L"u");
                                                            #line 960 "CodeGeneratorJava.cpp.template"
                                                                }
                                                            #line 1590 "CodeGeneratorJava.cpp"
  append(L"int[] ");
                                                            #line 961 "CodeGeneratorJava.cpp.template"
                                                                print(a->longName);
                                                            #line 1594 "CodeGeneratorJava.cpp"
  append(L" =");
                                                            #line 962 "CodeGeneratorJava.cpp.template"
                                                                if (asString)
                                                                {
                                                            #line 1599 "CodeGeneratorJava.cpp"
  append(L" new int[");
                                                            #line 964 "CodeGeneratorJava.cpp.template"
                                                                  print(a->size);
                                                            #line 1603 "CodeGeneratorJava.cpp"
  append(L"];\n");
  append(L"  static\n");
  append(L"  {\n");
  append(L"    final String s1[] =\n");
  append(L"    {");
                                                            #line 969 "CodeGeneratorJava.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1613 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"  {");
                                                            #line 973 "CodeGeneratorJava.cpp.template"
                                                                }
                                                                int w = (int) Format::width(a->size);
                                                                for (size_t j = 0; j < a->size; ++j)
                                                                {
                                                                  if (j == 0 || lineLength() + Format::width(a->integer(j)) + (asString ? 3 : 2) > limit)
                                                                  {
                                                                    if (j) print(asString ? "\"," : ",");
                                                            #line 1624 "CodeGeneratorJava.cpp"
  append(L"\n");
                                                            #line 981 "CodeGeneratorJava.cpp.template"
                                                                    if (asString) print("  ");
                                                            #line 1628 "CodeGeneratorJava.cpp"
  append(L"    /* ");
                                                            #line 982 "CodeGeneratorJava.cpp.template"
                                                                    print(format.toString<char>(j, 10, w));
                                                            #line 1632 "CodeGeneratorJava.cpp"
  append(L" */ ");
                                                            #line 983 "CodeGeneratorJava.cpp.template"
                                                                    if (asString) print("\"");
                                                                  }
                                                                  else
                                                                  {
                                                            #line 1639 "CodeGeneratorJava.cpp"
  append(L", ");
                                                            #line 987 "CodeGeneratorJava.cpp.template"
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
                                                            #line 1654 "CodeGeneratorJava.cpp"
  append(L"\"\n");
  append(L"    };\n");
  append(L"    String[] s2 = java.util.Arrays.toString(s1).replaceAll(\"[ \\\\[\\\\]]\", \"\").split(\",\");\n");
  append(L"    for (int i = 0; i < ");
                                                            #line 1002 "CodeGeneratorJava.cpp.template"
                                                                  print(a->size);
                                                            #line 1661 "CodeGeneratorJava.cpp"
  append(L"; ++i) {");
                                                            #line 1003 "CodeGeneratorJava.cpp.template"
                                                                  print(a->longName);
                                                            #line 1665 "CodeGeneratorJava.cpp"
  append(L"[i] = Integer.parseInt(s2[i]);}\n");
  append(L"  }");
                                                            #line 1005 "CodeGeneratorJava.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1672 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"  };");
                                                            #line 1009 "CodeGeneratorJava.cpp.template"
                                                                }
                                                              }
                                                              for (VarsInInsertionOrder::iterator a(varsInInsertionOrder.begin());
                                                                   a != varsInInsertionOrder.end(); ++a)
                                                                if (a->isArray() && a->size > 0 && a->hasType(CGVariable::STRING) && strlen(a->name) == 2)
                                                              {
                                                            #line 1682 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"\n");
  append(L"  private static ");
                                                            #line 1017 "CodeGeneratorJava.cpp.template"
                                                                if (targetLanguage == JAVA)
                                                                {
                                                            #line 1689 "CodeGeneratorJava.cpp"
  append(L"final");
                                                            #line 1019 "CodeGeneratorJava.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1695 "CodeGeneratorJava.cpp"
  append(L"readonly");
                                                            #line 1022 "CodeGeneratorJava.cpp.template"
                                                                }
                                                            #line 1699 "CodeGeneratorJava.cpp"
  append(L" String[] ");
                                                            #line 1023 "CodeGeneratorJava.cpp.template"
                                                                print(a->longName);
                                                            #line 1703 "CodeGeneratorJava.cpp"
  append(L" =\n");
  append(L"  {\n");
                                                            #line 1026 "CodeGeneratorJava.cpp.template"
                                                                for (size_t j = 0; j < a->size; ++j)
                                                                {
                                                                  if (j)
                                                                  {
                                                            #line 1711 "CodeGeneratorJava.cpp"
  append(L",\n");
                                                            #line 1031 "CodeGeneratorJava.cpp.template"
                                                                  }
                                                            #line 1715 "CodeGeneratorJava.cpp"
  append(L"    \"");
                                                            #line 1032 "CodeGeneratorJava.cpp.template"
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
                                                            #line 1730 "CodeGeneratorJava.cpp"
  append(L"\"");
                                                            #line 1044 "CodeGeneratorJava.cpp.template"
                                                                }
                                                            #line 1734 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"  };");
                                                            #line 1046 "CodeGeneratorJava.cpp.template"
                                                              }
                                                            }

                                                            void CodeGeneratorJava::generateBinarySearch(const char *input, const char *outputPrefix, const char *outputSuffix, const char *map, size_t size)
                                                            {
                                                            #line 1743 "CodeGeneratorJava.cpp"
  append(L"\n");
  append(L"int lo = 0, hi = ");
                                                            #line 1052 "CodeGeneratorJava.cpp.template"
                                                              print(size / 3 - 1);
                                                            #line 1748 "CodeGeneratorJava.cpp"
  append(L";\n");
  append(L"for (int m = ");
                                                            #line 1054 "CodeGeneratorJava.cpp.template"
                                                              print((size / 3) >> 1);
                                                            #line 1753 "CodeGeneratorJava.cpp"
  append(L"; ; m = (hi + lo) >> 1)\n");
  append(L"{\n");
  append(L"  if (");
                                                            #line 1057 "CodeGeneratorJava.cpp.template"
                                                              print(map);
                                                            #line 1759 "CodeGeneratorJava.cpp"
  append(L"[m] > ");
                                                            #line 1058 "CodeGeneratorJava.cpp.template"
                                                              print(input);
                                                            #line 1763 "CodeGeneratorJava.cpp"
  append(L") {hi = m - 1;}\n");
  append(L"  else if (");
                                                            #line 1060 "CodeGeneratorJava.cpp.template"
                                                              print(map);
                                                            #line 1768 "CodeGeneratorJava.cpp"
  append(L"[");
                                                            #line 1061 "CodeGeneratorJava.cpp.template"
                                                              print(size / 3);
                                                            #line 1772 "CodeGeneratorJava.cpp"
  append(L" + m] < ");
                                                            #line 1062 "CodeGeneratorJava.cpp.template"
                                                              print(input);
                                                            #line 1776 "CodeGeneratorJava.cpp"
  append(L") {lo = m + 1;}\n");
  append(L"  else {");
                                                            #line 1064 "CodeGeneratorJava.cpp.template"
                                                              print(outputPrefix);
                                                              print(map);
                                                            #line 1782 "CodeGeneratorJava.cpp"
  append(L"[");
                                                            #line 1066 "CodeGeneratorJava.cpp.template"
                                                              print(size / 3 * 2);
                                                            #line 1786 "CodeGeneratorJava.cpp"
  append(L" + m]");
                                                            #line 1067 "CodeGeneratorJava.cpp.template"
                                                              print(outputSuffix);
                                                            #line 1790 "CodeGeneratorJava.cpp"
  append(L";}\n");
  append(L"  if (lo > hi) {");
                                                            #line 1069 "CodeGeneratorJava.cpp.template"
                                                              print(outputPrefix);
                                                            #line 1795 "CodeGeneratorJava.cpp"
  append(L"0");
                                                            #line 1070 "CodeGeneratorJava.cpp.template"
                                                              print(outputSuffix);
                                                            #line 1799 "CodeGeneratorJava.cpp"
  append(L";}\n");
  append(L"}");
                                                            #line 1072 "CodeGeneratorJava.cpp.template"
                                                            }

// End
