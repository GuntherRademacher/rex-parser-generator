// This file was generated on Sun Nov 24, 2024 16:09 (UTC+01) by REx v6.0 which is Copyright (c) 1979-2024 by Gunther Rademacher <grd@gmx.net>
// REx command line: CodeGeneratorGo.cpp.template
                                                            #line 1 "CodeGeneratorGo.cpp.template"
                                                            // generate CodeGeneratorGo.cpp using this command:
                                                            //
                                                            //   REx CodeGeneratorGo.cpp.template

                                                            #include "../common/Memory.hpp"

                                                            #include "CodeGenerator.hpp"

                                                            void CodeGeneratorGo::generateStaticCode()
                                                            {
                                                              isGo = true;

                                                              const char *prefix = variable("useGlr").boolean()
                                                                                 ? "this.parser."
                                                                                 : "this.";
                                                              if (! variable("append").boolean() && ! variable("embedded").boolean())
                                                              {
                                                                if (*variable("package").string())
                                                                {
                                                            #line 24 "CodeGeneratorGo.cpp"
  append(L"package ");
                                                            #line 20 "CodeGeneratorGo.cpp.template"
                                                                  print(variable("package").string());
                                                            #line 28 "CodeGeneratorGo.cpp"
  append(L";\n");
  append(L"\n");
                                                            #line 23 "CodeGeneratorGo.cpp.template"
                                                                }
                                                            #line 33 "CodeGeneratorGo.cpp"
  append(L"public class ");
                                                            #line 24 "CodeGeneratorGo.cpp.template"
                                                                print(variable("classname").string());
                                                            #line 37 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"{\n");
                                                            #line 27 "CodeGeneratorGo.cpp.template"
                                                              }
                                                              if (! variable("useGlr").boolean())
                                                              {
                                                            #line 44 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"  input string");
                                                            #line 31 "CodeGeneratorGo.cpp.template"
                                                                if (! variable("nolexer").boolean())
                                                                {
                                                            #line 50 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"  size int");
                                                            #line 34 "CodeGeneratorGo.cpp.template"
                                                                }
                                                            #line 55 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"  begin int\n");
  append(L"  end int");
                                                            #line 37 "CodeGeneratorGo.cpp.template"
                                                              }
                                                              if (variable("nolexer").boolean())
                                                              {
                                                            #line 63 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"  lexer Lexer\n");
  append(L"  token Token");
                                                            #line 42 "CodeGeneratorGo.cpp.template"
                                                              }
                                                              if (! variable("embedded").boolean())
                                                              {
                                                            #line 71 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"  state int");
                                                            #line 46 "CodeGeneratorGo.cpp.template"
                                                              }
                                                            #line 76 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"}\n");
                                                            #line 50 "CodeGeneratorGo.cpp.template"
                                                              const char *clazz = variable("useGlr").boolean() ? "ParsingThread" : variable("classname").string();
                                                              if (! variable("embedded").boolean())
                                                              {
                                                            #line 83 "CodeGeneratorGo.cpp"
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
                                                            #line 71 "CodeGeneratorGo.cpp.template"
                                                              }
                                                              else
                                                              {
                                                                if (variable("lrparser").boolean() ||
                                                                    variable("tables").boolean())
                                                                {
                                                            #line 110 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"func (this *");
                                                            #line 78 "CodeGeneratorGo.cpp.template"
                                                                  print(clazz);
                                                            #line 115 "CodeGeneratorGo.cpp"
  append(L") predict(dpi int) int");
                                                            #line 79 "CodeGeneratorGo.cpp.template"
                                                                  predict();
                                                                }
                                                              }
                                                            #line 121 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"func (this *");
                                                            #line 83 "CodeGeneratorGo.cpp.template"
                                                              print(clazz);
                                                            #line 126 "CodeGeneratorGo.cpp"
  append(L") match(tokenSetId int) int {");
                                                            #line 84 "CodeGeneratorGo.cpp.template"
                                                              if (variable("nolexer").boolean())
                                                              {
                                                            #line 131 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"  token.begin = end;\n");
  append(L"  lexer.match(tokenSetId, token);\n");
  append(L"  begin = token.begin;\n");
  append(L"  end = token.end;\n");
  append(L"  return token.code >= 0\n");
  append(L"       ? token.code\n");
  append(L"       : error(begin, end, - tokenSetId, -1, -1);\n");
  append(L"}\n");
                                                            #line 95 "CodeGeneratorGo.cpp.template"
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
                                                            #line 153 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"  writeTrace(\"  <tokenize ");
                                                            #line 108 "CodeGeneratorGo.cpp.template"
                                                                if (variable("useGlr").boolean())
                                                                {
                                                            #line 159 "CodeGeneratorGo.cpp"
  append(L"thread=\\\"\" + strconv.Itoa(this.id) + \"\\\" ");
                                                            #line 111 "CodeGeneratorGo.cpp.template"
                                                                }
                                                            #line 163 "CodeGeneratorGo.cpp"
  append(L"tokenset=\\\"\" + strconv.Itoa(tokenSetId) + \"\\\">\\n\")\n");
                                                            #line 113 "CodeGeneratorGo.cpp.template"
                                                                }
                                                                if (lookahead)
                                                                {
                                                            #line 169 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"  nonbmp := false");
                                                            #line 117 "CodeGeneratorGo.cpp.template"
                                                                }
                                                            #line 174 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"  this.begin = this.end\n");
  append(L"  current := this.end\n");
  append(L"  result := initial[tokenSetId]");
                                                            #line 121 "CodeGeneratorGo.cpp.template"
                                                                if (variable("embedded").boolean() && (variable("trace").boolean() || ! variable("useGlr").boolean()))
                                                                {
                                                            #line 182 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"  state := 0");
                                                            #line 124 "CodeGeneratorGo.cpp.template"
                                                                }
                                                            #line 187 "CodeGeneratorGo.cpp"
  append(L"\n");
                                                            #line 126 "CodeGeneratorGo.cpp.template"
                                                                if (variable("trace").boolean())
                                                                {
                                                            #line 192 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"  writeTrace(\"    <next state=\\\"\" + strconv.Itoa(result & ");
                                                            #line 129 "CodeGeneratorGo.cpp.template"
                                                                 print(Math::powerof(2, variable("stateCodeBits").integer()) - 1);
                                                            #line 197 "CodeGeneratorGo.cpp"
  append(L") + \"\\\"\")");
                                                            #line 131 "CodeGeneratorGo.cpp.template"
                                                                }
                                                            #line 201 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"  for code := result & ");
                                                            #line 133 "CodeGeneratorGo.cpp.template"
                                                                print(Math::powerof(2, variable("stateCodeBits").integer()) - 1);
                                                            #line 206 "CodeGeneratorGo.cpp"
  append(L"; code != 0; {");
                                                            #line 135 "CodeGeneratorGo.cpp.template"
                                                                if (variable("trace").boolean())
                                                                {
                                                            #line 211 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"    writeTrace(\" offset=\\\"\" + strconv.Itoa(current) + \"\\\"\")");
                                                            #line 138 "CodeGeneratorGo.cpp.template"
                                                                }
                                                            #line 216 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"    var charclass int\n");
  append(L"    var c0 int\n");
  append(L"    if current < ");
                                                            #line 142 "CodeGeneratorGo.cpp.template"
                                                                print(prefix);
                                                            #line 223 "CodeGeneratorGo.cpp"
  append(L"size {\n");
  append(L"      r, s := utf8.DecodeRuneInString(");
                                                            #line 144 "CodeGeneratorGo.cpp.template"
                                                                print(prefix);
                                                            #line 228 "CodeGeneratorGo.cpp"
  append(L"input[current:])\n");
  append(L"      c0 = int(r)\n");
  append(L"      current += s\n");
  append(L"    } else {\n");
  append(L"      c0 = 0\n");
  append(L"      current++\n");
  append(L"    }");
  append(L"\n");
  append(L"    if c0 < 0x");
                                                            #line 153 "CodeGeneratorGo.cpp.template"
                                                                print(format.toString<char>(variable("simplifiedCodeMap").integer(), 16, 0, 0, 0, "0123456789abcdef"));
                                                            #line 240 "CodeGeneratorGo.cpp"
  append(L" {");
                                                            #line 155 "CodeGeneratorGo.cpp.template"
                                                                if (variable("trace").boolean())
                                                                {
                                                            #line 245 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"      if c0 >= 32 && c0 <= 126 {\n");
  append(L"        writeTrace(\" char=\\\"\" + xmlEscape(string(rune(c0))) + \"\\\"\")\n");
  append(L"      }");
                                                            #line 160 "CodeGeneratorGo.cpp.template"
                                                                }
                                                            #line 252 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"      charclass = map0[c0]\n");
  append(L"    } else if c0 < 0x");
                                                            #line 163 "CodeGeneratorGo.cpp.template"
                                                                print(format.toString<char>(variable("uncompressedMapSize").integer(), 16, 0, 0, 0, "0123456789abcdef"));
                                                            #line 258 "CodeGeneratorGo.cpp"
  append(L" {\n");
                                                            #line 165 "CodeGeneratorGo.cpp.template"
                                                                compressedMapAccessor(6, "c", "charclass = ", "map1", &variable("m1bits").integer());
                                                            #line 262 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"    } else {");
                                                            #line 167 "CodeGeneratorGo.cpp.template"
                                                                if (variable("m2").size == 0)
                                                                {
                                                            #line 268 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"      charclass = 0");
                                                            #line 170 "CodeGeneratorGo.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 275 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"      lo := 0\n");
  append(L"      hi := ");
                                                            #line 175 "CodeGeneratorGo.cpp.template"
                                                                  print(variable("m2").size / 3 - 1);
                                                            #line 281 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"      for m := ");
                                                            #line 177 "CodeGeneratorGo.cpp.template"
                                                                  print((variable("m2").size / 3) >> 1);
                                                            #line 286 "CodeGeneratorGo.cpp"
  append(L"; ; m = (hi + lo) >> 1 {\n");
  append(L"        if map2[m] > int(c0) {\n");
  append(L"          hi = m - 1\n");
  append(L"        } else if map2[");
                                                            #line 181 "CodeGeneratorGo.cpp.template"
                                                                  print(variable("m2").size / 3);
                                                            #line 293 "CodeGeneratorGo.cpp"
  append(L" + m] < int(c0) {\n");
  append(L"          lo = m + 1\n");
  append(L"        } else {\n");
  append(L"          charclass = map2[");
                                                            #line 185 "CodeGeneratorGo.cpp.template"
                                                                  print(variable("m2").size / 3 * 2);
                                                            #line 300 "CodeGeneratorGo.cpp"
  append(L" + m]\n");
  append(L"          break\n");
  append(L"        }\n");
  append(L"        if lo > hi {\n");
  append(L"          charclass = 0\n");
  append(L"          break\n");
  append(L"        }\n");
  append(L"      }");
                                                            #line 193 "CodeGeneratorGo.cpp.template"
                                                                }
                                                            #line 311 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"    }");
                                                            #line 195 "CodeGeneratorGo.cpp.template"
                                                                if (variable("trace").boolean())
                                                                {
                                                            #line 317 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"    writeTrace(\" codepoint=\\\"\" + strconv.Itoa(c0) + \"\\\" class=\\\"\" + strconv.Itoa(charclass) + \"\\\"\")");
                                                            #line 199 "CodeGeneratorGo.cpp.template"
                                                                }
                                                            #line 322 "CodeGeneratorGo.cpp"
  append(L"\n");
                                                            #line 201 "CodeGeneratorGo.cpp.template"
                                                                if (variable("trace").boolean() || ! variable("useGlr").boolean())
                                                                {
                                                            #line 327 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"    state = code");
                                                            #line 204 "CodeGeneratorGo.cpp.template"
                                                                }
                                                            #line 332 "CodeGeneratorGo.cpp"
  append(L"\n");
                                                            #line 206 "CodeGeneratorGo.cpp.template"
                                                                compressedMap2dAccessor("code - 1", "charclass", variable("a1cols").integer(),
                                                                                           4, "i", "code = ", "transition", &variable("a1bits").integer());
                                                            #line 337 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"    if code > ");
                                                            #line 209 "CodeGeneratorGo.cpp.template"
                                                                print(Math::powerof(2, variable("stateCodeBits").integer()) - 1);
                                                            #line 342 "CodeGeneratorGo.cpp"
  append(L" {\n");
  append(L"      result = code");
                                                            #line 211 "CodeGeneratorGo.cpp.template"
                                                                if (variable("trace").boolean())
                                                                {
                                                            #line 348 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"      writeTrace(\" result=\\\"\" + xmlEscape(token[((result >> ");
                                                            #line 214 "CodeGeneratorGo.cpp.template"
                                                                 print(variable("stateCodeBits").integer());
                                                            #line 353 "CodeGeneratorGo.cpp"
  append(L") & ");
                                                            #line 216 "CodeGeneratorGo.cpp.template"
                                                                  print(Math::powerof(2, variable("tokencodeBits").integer()) - 1);
                                                            #line 357 "CodeGeneratorGo.cpp"
  append(L") - 1]) + \"\\\"\")");
                                                            #line 218 "CodeGeneratorGo.cpp.template"
                                                                  if (lookahead || hasFixedTokenLength)
                                                                  {
                                                                    int contextOffset = variable("stateCodeBits").integer()
                                                                                      + variable("tokencodeBits").integer();
                                                                    int sizeOffset = contextOffset
                                                                                   + (hasFixedTokenLength ? 1 : 0);
                                                                    if (hasFixedTokenLength)
                                                                    {
                                                            #line 368 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"      if result & ");
                                                            #line 227 "CodeGeneratorGo.cpp.template"
                                                                      print(Math::powerof(2, contextOffset));
                                                            #line 373 "CodeGeneratorGo.cpp"
  append(L" > 0 {\n");
  append(L"        writeTrace(\" token-size=\\\"\" + strconv.Itoa(result >> ");
                                                            #line 229 "CodeGeneratorGo.cpp.template"
                                                                     print(sizeOffset);
                                                            #line 378 "CodeGeneratorGo.cpp"
  append(L") + \"\\\"\")\n");
  append(L"      } else ");
                                                            #line 231 "CodeGeneratorGo.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 385 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"      ");
                                                            #line 235 "CodeGeneratorGo.cpp.template"
                                                                    }
                                                            #line 390 "CodeGeneratorGo.cpp"
  append(L"if (result >> ");
                                                            #line 236 "CodeGeneratorGo.cpp.template"
                                                                    print(sizeOffset);
                                                            #line 394 "CodeGeneratorGo.cpp"
  append(L") > 0 {\n");
  append(L"        writeTrace(\" trailing-context-size=\\\"\" + strconv.Itoa(result >> ");
                                                            #line 239 "CodeGeneratorGo.cpp.template"
                                                                    print(sizeOffset);
                                                            #line 399 "CodeGeneratorGo.cpp"
  append(L") + \"\\\"\")\n");
  append(L"      }");
                                                            #line 241 "CodeGeneratorGo.cpp.template"
                                                                  }
                                                                }
                                                            #line 405 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"      code &= ");
                                                            #line 244 "CodeGeneratorGo.cpp.template"
                                                                print(Math::powerof(2, variable("stateCodeBits").integer()) - 1);
                                                            #line 410 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"      this.end = current\n");
  append(L"    }");
                                                            #line 247 "CodeGeneratorGo.cpp.template"
                                                                if (variable("trace").boolean())
                                                                {
                                                            #line 417 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"    writeTrace(\"/>\\n\")\n");
  append(L"    if code != 0 {\n");
  append(L"      writeTrace(\"    <next state=\\\"\" + strconv.Itoa(code) + \"\\\"\")\n");
  append(L"    }");
                                                            #line 253 "CodeGeneratorGo.cpp.template"
                                                                }
                                                            #line 425 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  result >>= ");
                                                            #line 257 "CodeGeneratorGo.cpp.template"
                                                                print(variable("stateCodeBits").integer());
                                                            #line 432 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"  if result == 0 {\n");
  append(L"    if this.end < ");
                                                            #line 260 "CodeGeneratorGo.cpp.template"
                                                                print(prefix);
                                                            #line 438 "CodeGeneratorGo.cpp"
  append(L"size {\n");
  append(L"      _, s := utf8.DecodeLastRuneInString(");
                                                            #line 262 "CodeGeneratorGo.cpp.template"
                                                                print(prefix);
                                                            #line 443 "CodeGeneratorGo.cpp"
  append(L"input[:current])\n");
  append(L"      this.end = current - s\n");
  append(L"    } else {\n");
  append(L"      this.end = current - 1\n");
  append(L"    }");
                                                            #line 267 "CodeGeneratorGo.cpp.template"
                                                                if (variable("trace").boolean())
                                                                {
                                                            #line 452 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"    writeTrace(\"    <fail begin=\\\"\" + strconv.Itoa(this.begin) + \"\\\" end=\\\"\" + strconv.Itoa(this.end) + \"\\\" state=\\\"\" + strconv.Itoa(state) + \"\\\"/>\\n\")\n");
  append(L"    writeTrace(\"  </tokenize>\\n\")");
                                                            #line 271 "CodeGeneratorGo.cpp.template"
                                                                }
                                                                if (variable("embedded").boolean())
                                                                {
                                                                  if (variable("useGlr").boolean())
                                                                  {
                                                            #line 462 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"    this.end = this.begin\n");
  append(L"    return -1");
                                                            #line 278 "CodeGeneratorGo.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 470 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"    return this.error(this.begin, this.end, state, -1, -1)");
                                                            #line 282 "CodeGeneratorGo.cpp.template"
                                                                  }
                                                                }
                                                            #line 476 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"  }");
                                                            #line 285 "CodeGeneratorGo.cpp.template"
                                                                lowBits = variable("tokencodeBits").integer();
                                                                if (hasFixedTokenLength && ! lookahead)
                                                                {
                                                            #line 483 "CodeGeneratorGo.cpp"
  append(L" else if (result & ");
                                                            #line 288 "CodeGeneratorGo.cpp.template"
                                                                  print(Math::powerof(2, lowBits));
                                                                  ++lowBits;
                                                            #line 488 "CodeGeneratorGo.cpp"
  append(L") != 0 {\n");
  append(L"    this.end = this.begin\n");
  append(L"  }");
                                                            #line 292 "CodeGeneratorGo.cpp.template"
                                                                }
                                                                else
                                                                {
                                                                  if (hasFixedTokenLength)
                                                                  {
                                                            #line 498 "CodeGeneratorGo.cpp"
  append(L" else if (result & ");
                                                            #line 297 "CodeGeneratorGo.cpp.template"
                                                                    print(Math::powerof(2, lowBits));
                                                                    ++lowBits;
                                                            #line 503 "CodeGeneratorGo.cpp"
  append(L") != 0 {\n");
  append(L"    this.end = this.begin\n");
  append(L"    if (nonbmp) {\n");
  append(L"      for i := result >> ");
                                                            #line 302 "CodeGeneratorGo.cpp.template"
                                                                    print(lowBits);
                                                            #line 510 "CodeGeneratorGo.cpp"
  append(L"; i > 0; i-- {\n");
  append(L"        if this.end >= ");
                                                            #line 304 "CodeGeneratorGo.cpp.template"
                                                                    print(prefix);
                                                            #line 515 "CodeGeneratorGo.cpp"
  append(L"size {\n");
  append(L"          this.end++\n");
  append(L"        } else {\n");
  append(L"          _, s := utf8.DecodeRuneInString(");
                                                            #line 308 "CodeGeneratorGo.cpp.template"
                                                                    print(prefix);
                                                            #line 522 "CodeGeneratorGo.cpp"
  append(L"input[this.end:])\n");
  append(L"          this.end += s\n");
  append(L"        }\n");
  append(L"      }\n");
  append(L"    } else {\n");
  append(L"      this.end += (result >> ");
                                                            #line 314 "CodeGeneratorGo.cpp.template"
                                                                    print(lowBits);
                                                            #line 531 "CodeGeneratorGo.cpp"
  append(L");\n");
  append(L"    }\n");
  append(L"  }");
                                                            #line 317 "CodeGeneratorGo.cpp.template"
                                                                  }
                                                                  if (lookahead)
                                                                  {
                                                            #line 539 "CodeGeneratorGo.cpp"
  append(L" else if nonbmp {\n");
  append(L"    for i := result >> ");
                                                            #line 321 "CodeGeneratorGo.cpp.template"
                                                                    print(lowBits);
                                                            #line 544 "CodeGeneratorGo.cpp"
  append(L"; i > 0; i-- {\n");
  append(L"      if this.end >= ");
                                                            #line 323 "CodeGeneratorGo.cpp.template"
                                                                    print(prefix);
                                                            #line 549 "CodeGeneratorGo.cpp"
  append(L"size {\n");
  append(L"        this.end--\n");
  append(L"      } else {\n");
  append(L"        _, s := utf8.DecodeLastRuneInString(");
                                                            #line 327 "CodeGeneratorGo.cpp.template"
                                                                    print(prefix);
                                                            #line 556 "CodeGeneratorGo.cpp"
  append(L"input[:this.end - 1])\n");
  append(L"        this.end -= s\n");
  append(L"      }\n");
  append(L"    }\n");
  append(L"  } else {\n");
  append(L"    this.end -= result >> ");
                                                            #line 333 "CodeGeneratorGo.cpp.template"
                                                                    print(lowBits);
                                                            #line 565 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"  }");
                                                            #line 335 "CodeGeneratorGo.cpp.template"
                                                                  }
                                                                }
                                                            #line 571 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"\n");
  append(L"  if this.end > ");
                                                            #line 340 "CodeGeneratorGo.cpp.template"
                                                                print(prefix);
                                                            #line 577 "CodeGeneratorGo.cpp"
  append(L"size {\n");
  append(L"    this.end = ");
                                                            #line 342 "CodeGeneratorGo.cpp.template"
                                                                print(prefix);
                                                            #line 582 "CodeGeneratorGo.cpp"
  append(L"size\n");
  append(L"  }");
                                                            #line 344 "CodeGeneratorGo.cpp.template"
                                                                if (variable("trace").boolean())
                                                                {
                                                            #line 588 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"  writeTrace(\"    <done result=\\\"\" + xmlEscape(token[(result & ");
                                                            #line 348 "CodeGeneratorGo.cpp.template"
                                                                  print(Math::powerof(2, variable("tokencodeBits").integer()) - 1);
                                                            #line 593 "CodeGeneratorGo.cpp"
  append(L") - 1]) + \"\\\" begin=\\\"\" + strconv.Itoa(this.begin) + \"\\\" end=\\\"\" + strconv.Itoa(this.end) + \"\\\"/>\\n\")\n");
  append(L"  writeTrace(\"  </tokenize>\\n\")");
                                                            #line 350 "CodeGeneratorGo.cpp.template"
                                                                }
                                                                if (hack)
                                                                {
                                                            #line 600 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"  return hack((result & ");
                                                            #line 354 "CodeGeneratorGo.cpp.template"
                                                                  print(Math::powerof(2, variable("tokencodeBits").integer()) - 1);
                                                            #line 605 "CodeGeneratorGo.cpp"
  append(L") - 1);\n");
  append(L"}\n");
                                                            #line 357 "CodeGeneratorGo.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 612 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"  return (result & ");
                                                            #line 361 "CodeGeneratorGo.cpp.template"
                                                                  print(Math::powerof(2, variable("tokencodeBits").integer()) - 1);
                                                            #line 617 "CodeGeneratorGo.cpp"
  append(L") - 1\n");
  append(L"}\n");
                                                            #line 364 "CodeGeneratorGo.cpp.template"
                                                                }
                                                              }
                                                              if (defined("gtbits"))
                                                              {
                                                            #line 625 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"func reduceAction(nonterminalId int, state int) int {\n");
                                                            #line 370 "CodeGeneratorGo.cpp.template"
                                                                compressedMap2dAccessor("nonterminalId", "state", variable("gtcols").integer(),
                                                                                        2, "i", "return ", "goTo", &variable("gtbits").integer());
                                                            #line 631 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"}\n");
                                                            #line 374 "CodeGeneratorGo.cpp.template"
                                                              }

                                                              if (! variable("embedded").boolean())
                                                              {
                                                            #line 639 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"  public String[] getExpectedTokenSet()\n");
  append(L"  {\n");
  append(L"    return getTokenSet(- state);\n");
  append(L"  }\n");
                                                            #line 383 "CodeGeneratorGo.cpp.template"
                                                              }
                                                              if (variable("trace").boolean())
                                                              {
                                                            #line 649 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"func xmlEscape(s string) string {\n");
  append(L"  var sb strings.Builder\n");
  append(L"  for i := 0; i < len(s); {\n");
  append(L"    c, l := utf8.DecodeRuneInString(s[i:])\n");
  append(L"    i += l\n");
  append(L"    switch (c) {\n");
  append(L"    case '<': sb.WriteString(\"&lt;\")\n");
  append(L"    case '\"': sb.WriteString(\"&quot;\")\n");
  append(L"    case '&': sb.WriteString(\"&amp;\")\n");
  append(L"    default : sb.WriteString(string(c))\n");
  append(L"    }\n");
  append(L"  }\n");
  append(L"  return sb.String()\n");
  append(L"}\n");
  append(L"\n");
  append(L"func writeTrace(content string) {\n");
  append(L"  os.Stderr.WriteString(content)\n");
  append(L"}\n");
                                                            #line 405 "CodeGeneratorGo.cpp.template"
                                                                if (variable("embedded").boolean())
                                                                {
                                                            #line 672 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"func flushTrace() {\n");
  append(L"  os.Stderr.Sync()\n");
  append(L"}\n");
                                                            #line 411 "CodeGeneratorGo.cpp.template"
                                                                }
                                                              }
                                                              if (variable("nolexer").boolean())
                                                              {
                                                            #line 682 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"  public static int getTokenCount() {return ");
                                                            #line 416 "CodeGeneratorGo.cpp.template"
                                                                print(variable("t1").size);
                                                            #line 687 "CodeGeneratorGo.cpp"
  append(L";}\n");
  append(L"  public static String getTokenName(int code) {return code >= 0 && code < ");
                                                            #line 419 "CodeGeneratorGo.cpp.template"
                                                                print(variable("t1").size);
                                                            #line 692 "CodeGeneratorGo.cpp"
  append(L" ? token[code] : null;}\n");
  append(L"  public static int getTokenSetCount() {return ");
                                                            #line 421 "CodeGeneratorGo.cpp.template"
                                                                print(variable("entrycount").integer());
                                                            #line 697 "CodeGeneratorGo.cpp"
  append(L";}\n");
  append(L"\n");
  append(L"func GetTokenSet(tokenSetId int) []string {");
                                                            #line 424 "CodeGeneratorGo.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 705 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"func getTokenSet(tokenSetId int) []string {");
                                                            #line 428 "CodeGeneratorGo.cpp.template"
                                                              }
                                                              if (! variable("nolexer").boolean())
                                                              {
                                                            #line 712 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"  var s int\n");
  append(L"  if tokenSetId < 0 {\n");
  append(L"    s = - tokenSetId\n");
  append(L"  } else {\n");
  append(L"    s = initial[tokenSetId] & ");
                                                            #line 436 "CodeGeneratorGo.cpp.template"
                                                                print(Math::powerof(2, variable("stateCodeBits").integer()) - 1);
                                                            #line 721 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"  }");
                                                            #line 439 "CodeGeneratorGo.cpp.template"
                                                              }
                                                            #line 726 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"  set := []string {}\n");
  append(L"  size := 0\n");
  append(L"  for i := 0; i < ");
                                                            #line 443 "CodeGeneratorGo.cpp.template"
                                                              print(variable("t1").size);
                                                            #line 733 "CodeGeneratorGo.cpp"
  append(L"; i += 32 {\n");
  append(L"    j := i\n");
  append(L"    i0 := (i >> 5) * ");
                                                            #line 446 "CodeGeneratorGo.cpp.template"
                                                              print(variable("transitionStateCount").integer());
                                                            #line 739 "CodeGeneratorGo.cpp"
  append(L" + ");
                                                            #line 447 "CodeGeneratorGo.cpp.template"
                                                              if (variable("nolexer").boolean())
                                                              {
                                                            #line 744 "CodeGeneratorGo.cpp"
  append(L"tokenSetId");
                                                            #line 449 "CodeGeneratorGo.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 750 "CodeGeneratorGo.cpp"
  append(L"s - 1");
                                                            #line 452 "CodeGeneratorGo.cpp.template"
                                                              }
                                                            #line 754 "CodeGeneratorGo.cpp"
  append(L"\n");
                                                            #line 454 "CodeGeneratorGo.cpp.template"
                                                              compressedMapAccessor(4, "i", "f := uint32(", "expected", &variable("t0bits").integer());
                                                            #line 758 "CodeGeneratorGo.cpp"
  append(L")\n");
  append(L"    for ; f != 0; f >>= 1 {\n");
  append(L"      if (f & 1) != 0 {\n");
  append(L"        set = append(set, token[j])\n");
  append(L"        size++\n");
  append(L"      }\n");
  append(L"      j++\n");
  append(L"    }\n");
  append(L"  }\n");
  append(L"  return set[:size]\n");
  append(L"}");
                                                            #line 465 "CodeGeneratorGo.cpp.template"
                                                              generateData();
                                                              if (! variable("embedded").boolean())
                                                              {
                                                            #line 774 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"\n");
  append(L"  public enum Token\n");
  append(L"  {\n");
  append(L"    ");
                                                            #line 472 "CodeGeneratorGo.cpp.template"
                                                                const CGVariable &token = variable("token");
                                                                int w = (int) Format::width(token.size);
                                                                for (size_t i = 0; i < token.size; ++i)
                                                                {
                                                                  if (i)
                                                                  {
                                                            #line 787 "CodeGeneratorGo.cpp"
  append(L",\n");
  append(L"    ");
                                                            #line 479 "CodeGeneratorGo.cpp.template"
                                                                  }
                                                            #line 792 "CodeGeneratorGo.cpp"
  append(L"/* ");
                                                            #line 480 "CodeGeneratorGo.cpp.template"
                                                                  print(format.toString<char>(i, 10, w));
                                                            #line 796 "CodeGeneratorGo.cpp"
  append(L" */ ");
                                                            #line 481 "CodeGeneratorGo.cpp.template"
                                                                  print(token.string(i));
                                                                }
                                                            #line 801 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"  };");
                                                            #line 485 "CodeGeneratorGo.cpp.template"
                                                              }
                                                              if (variable("selfTest").boolean())
                                                              {
                                                            #line 808 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"\n");
  append(L"  private void selfTest(int set, int tokenId)\n");
  append(L"  {\n");
  append(L"    String tokenString = token[tokenId];\n");
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
                                                            #line 523 "CodeGeneratorGo.cpp.template"
                                                              print(variable("classname").string());
                                                            #line 847 "CodeGeneratorGo.cpp"
  append(L" testee = new ");
                                                            #line 524 "CodeGeneratorGo.cpp.template"
                                                              print(variable("classname").string());
                                                            #line 851 "CodeGeneratorGo.cpp"
  append(L"();\n");
  append(L"    for (int e = 0; e < ");
                                                            #line 526 "CodeGeneratorGo.cpp.template"
                                                              print(variable("a0").size);
                                                            #line 856 "CodeGeneratorGo.cpp"
  append(L"; ++e)\n");
  append(L"    {\n");
  append(L"      int s = INITIAL[e] & ");
                                                            #line 529 "CodeGeneratorGo.cpp.template"
                                                              print(Math::powerof(2, variable("stateCodeBits").integer()) - 1);
                                                            #line 862 "CodeGeneratorGo.cpp"
  append(L";\n");
  append(L"      for (int i = 0; i < ");
                                                            #line 531 "CodeGeneratorGo.cpp.template"
                                                              print(variable("t1").size);
                                                            #line 867 "CodeGeneratorGo.cpp"
  append(L"; i += 32)\n");
  append(L"      {\n");
  append(L"        int j = i;\n");
  append(L"        int i0 = (i >> 5) * ");
                                                            #line 535 "CodeGeneratorGo.cpp.template"
                                                              print(variable("transitionStateCount").integer());
                                                            #line 874 "CodeGeneratorGo.cpp"
  append(L" + s - 1;\n");
                                                            #line 537 "CodeGeneratorGo.cpp.template"
                                                              compressedMapAccessor(8, "i", "f := ", "expected", &variable("t0bits").integer());
                                                            #line 878 "CodeGeneratorGo.cpp"
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
                                                            #line 548 "CodeGeneratorGo.cpp.template"
                                                              }
                                                            #line 892 "CodeGeneratorGo.cpp"
  append(L"\n");
                                                            #line 550 "CodeGeneratorGo.cpp.template"
                                                              if (! variable("embedded").boolean())
                                                              {
                                                            #line 897 "CodeGeneratorGo.cpp"
  append(L"}\n");
                                                            #line 553 "CodeGeneratorGo.cpp.template"
                                                              }
                                                            }

                                                            void CodeGeneratorGo::generateCompressedMap()
                                                            {
                                                            #line 905 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"public class ");
                                                            #line 559 "CodeGeneratorGo.cpp.template"
                                                              print(variable("classname").string());
                                                            #line 910 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"{\n");
  append(L"  public static int get(int i0)\n");
  append(L"  {\n");
  append(L"    if (i0 < 0x30000)\n");
  append(L"    {\n");
                                                            #line 566 "CodeGeneratorGo.cpp.template"
                                                              compressedMapAccessor(6, "i", "return ", "low", &variable("dtbits").integer());
                                                            #line 919 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"    }\n");
  append(L"    else\n");
  append(L"    {");
                                                            #line 570 "CodeGeneratorGo.cpp.template"
                                                              indent += 3;
                                                              generateBinarySearch("i0", "return ", "", "HIGH", variable("rm").size);
                                                              indent -= 3;
                                                            #line 928 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"    }\n");
  append(L"  }");
                                                            #line 575 "CodeGeneratorGo.cpp.template"
                                                              generateData();
                                                            #line 934 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"}\n");
                                                            #line 578 "CodeGeneratorGo.cpp.template"
                                                            }

                                                            void CodeGeneratorGo::generateData()
                                                            {
                                                              size_t limit = 119;
                                                              for (VarsInInsertionOrder::iterator a(varsInInsertionOrder.begin());
                                                                   a != varsInInsertionOrder.end(); ++a)
                                                                if (   a->isArray()
                                                                    && a->size > 0
                                                                    && (a->hasType(CGVariable::INTEGER) || a->hasType(CGVariable::UNSIGNED))
                                                                    && strlen(a->name) == 2)
                                                              {
                                                            #line 950 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"\n");
  append(L"var ");
                                                            #line 592 "CodeGeneratorGo.cpp.template"
                                                                if (strcmp(a->longName, "GOTO") == 0)
                                                                {
                                                                  print("goTo");
                                                                }
                                                                else
                                                                {
                                                                  char name[] = {0, 0};
                                                                  for (const char *p = a->longName; *p; ++p)
                                                                  {
                                                                    name[0] = tolower(*p);
                                                                    print(name);
                                                                  }
                                                                }
                                                            #line 968 "CodeGeneratorGo.cpp"
  append(L" = [...]");
                                                            #line 605 "CodeGeneratorGo.cpp.template"
                                                                if ( a->hasType(CGVariable::UNSIGNED))
                                                                {
                                                            #line 973 "CodeGeneratorGo.cpp"
  append(L"u");
                                                            #line 607 "CodeGeneratorGo.cpp.template"
                                                                }
                                                            #line 977 "CodeGeneratorGo.cpp"
  append(L"int {");
                                                            #line 608 "CodeGeneratorGo.cpp.template"
                                                                int w = (int) Format::width(a->size);
                                                                for (size_t j = 0; j < a->size; ++j)
                                                                {
                                                                  if (j == 0 || lineLength() + Format::width(a->integer(j)) + 2 > limit)
                                                                  {
                                                                    if (j) print(",");
                                                            #line 986 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"/* ");
                                                            #line 615 "CodeGeneratorGo.cpp.template"
                                                                    print(format.toString<char>(j, 10, w));
                                                            #line 991 "CodeGeneratorGo.cpp"
  append(L" */ ");
                                                            #line 616 "CodeGeneratorGo.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 997 "CodeGeneratorGo.cpp"
  append(L", ");
                                                            #line 619 "CodeGeneratorGo.cpp.template"
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
                                                            #line 1010 "CodeGeneratorGo.cpp"
  append(L"}");
                                                            #line 629 "CodeGeneratorGo.cpp.template"
                                                              }
                                                              for (VarsInInsertionOrder::iterator a(varsInInsertionOrder.begin());
                                                                   a != varsInInsertionOrder.end(); ++a)
                                                                if (a->isArray() && a->size > 0 && a->hasType(CGVariable::STRING) && strlen(a->name) == 2)
                                                              {
                                                            #line 1018 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"\n");
  append(L"var ");
                                                            #line 636 "CodeGeneratorGo.cpp.template"
                                                                char name[] = {0, 0};
                                                                for (const char *p = a->longName; *p; ++p)
                                                                {
                                                                  name[0] = tolower(*p);
                                                                  print(name);
                                                                }
                                                            #line 1029 "CodeGeneratorGo.cpp"
  append(L" = [...]string {\n");
                                                            #line 643 "CodeGeneratorGo.cpp.template"
                                                                for (size_t j = 0; j < a->size; ++j)
                                                                {
                                                                  if (j)
                                                                  {
                                                            #line 1036 "CodeGeneratorGo.cpp"
  append(L",\n");
                                                            #line 648 "CodeGeneratorGo.cpp.template"
                                                                  }
                                                            #line 1040 "CodeGeneratorGo.cpp"
  append(L"    \"");
                                                            #line 649 "CodeGeneratorGo.cpp.template"
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
                                                            #line 1055 "CodeGeneratorGo.cpp"
  append(L"\"");
                                                            #line 661 "CodeGeneratorGo.cpp.template"
                                                                }
                                                            #line 1059 "CodeGeneratorGo.cpp"
  append(L"}");
                                                            #line 662 "CodeGeneratorGo.cpp.template"
                                                              }
                                                            }

                                                            void CodeGeneratorGo::generateBinarySearch(const char *input, const char *outputPrefix, const char *outputSuffix, const char *map, size_t size)
                                                            {
                                                            #line 1067 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"int lo = 0, hi = ");
                                                            #line 668 "CodeGeneratorGo.cpp.template"
                                                              print(size / 3 - 1);
                                                            #line 1072 "CodeGeneratorGo.cpp"
  append(L";\n");
  append(L"for (int m = ");
                                                            #line 670 "CodeGeneratorGo.cpp.template"
                                                              print((size / 3) >> 1);
                                                            #line 1077 "CodeGeneratorGo.cpp"
  append(L"; ; m = (hi + lo) >> 1)\n");
  append(L"{\n");
  append(L"  if (");
                                                            #line 673 "CodeGeneratorGo.cpp.template"
                                                              print(map);
                                                            #line 1083 "CodeGeneratorGo.cpp"
  append(L"[m] > ");
                                                            #line 674 "CodeGeneratorGo.cpp.template"
                                                              print(input);
                                                            #line 1087 "CodeGeneratorGo.cpp"
  append(L") {hi = m - 1;}\n");
  append(L"  else if (");
                                                            #line 676 "CodeGeneratorGo.cpp.template"
                                                              print(map);
                                                            #line 1092 "CodeGeneratorGo.cpp"
  append(L"[");
                                                            #line 677 "CodeGeneratorGo.cpp.template"
                                                              print(size / 3);
                                                            #line 1096 "CodeGeneratorGo.cpp"
  append(L" + m] < ");
                                                            #line 678 "CodeGeneratorGo.cpp.template"
                                                              print(input);
                                                            #line 1100 "CodeGeneratorGo.cpp"
  append(L") {lo = m + 1;}\n");
  append(L"  else {");
                                                            #line 680 "CodeGeneratorGo.cpp.template"
                                                              print(outputPrefix);
                                                              print(map);
                                                            #line 1106 "CodeGeneratorGo.cpp"
  append(L"[");
                                                            #line 682 "CodeGeneratorGo.cpp.template"
                                                              print(size / 3 * 2);
                                                            #line 1110 "CodeGeneratorGo.cpp"
  append(L" + m]");
                                                            #line 683 "CodeGeneratorGo.cpp.template"
                                                              print(outputSuffix);
                                                            #line 1114 "CodeGeneratorGo.cpp"
  append(L";}\n");
  append(L"  if (lo > hi) {");
                                                            #line 685 "CodeGeneratorGo.cpp.template"
                                                              print(outputPrefix);
                                                            #line 1119 "CodeGeneratorGo.cpp"
  append(L"0");
                                                            #line 686 "CodeGeneratorGo.cpp.template"
                                                              print(outputSuffix);
                                                            #line 1123 "CodeGeneratorGo.cpp"
  append(L";}\n");
  append(L"}");
                                                            #line 688 "CodeGeneratorGo.cpp.template"
                                                            }

// End
