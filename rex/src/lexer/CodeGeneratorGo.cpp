// This file was generated on Thu Nov 12, 2026 17:53 (UTC+01) by REx v7.0 which is Copyright (c) 1979-2026 by Gunther Rademacher <grd@gmx.net>
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
                                                            #line 49 "CodeGeneratorGo.cpp.template"
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
                                                            #line 70 "CodeGeneratorGo.cpp.template"
                                                              }
                                                              else
                                                              {
                                                                if (variable("lrparser").boolean() ||
                                                                    variable("tables").boolean())
                                                                {
                                                            #line 110 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"func (this *");
                                                            #line 77 "CodeGeneratorGo.cpp.template"
                                                                  print(clazz);
                                                            #line 115 "CodeGeneratorGo.cpp"
  append(L") predict(dpi int) int");
                                                            #line 78 "CodeGeneratorGo.cpp.template"
                                                                  predict();
                                                                }
                                                              }
                                                            #line 121 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"func (this *");
                                                            #line 82 "CodeGeneratorGo.cpp.template"
                                                              print(clazz);
                                                            #line 126 "CodeGeneratorGo.cpp"
  append(L") match(tokenSetId int) int {");
                                                            #line 83 "CodeGeneratorGo.cpp.template"
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
                                                            #line 94 "CodeGeneratorGo.cpp.template"
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
                                                            #line 106 "CodeGeneratorGo.cpp.template"
                                                                  if (variable("useGlr").boolean())
                                                                  {
                                                            #line 159 "CodeGeneratorGo.cpp"
  append(L"thread=\\\"\" + strconv.Itoa(this.id) + \"\\\" ");
                                                            #line 109 "CodeGeneratorGo.cpp.template"
                                                                  }
                                                            #line 163 "CodeGeneratorGo.cpp"
  append(L"tokenset=\\\"\" + strconv.Itoa(tokenSetId) + \"\\\">\\n\")\n");
                                                            #line 111 "CodeGeneratorGo.cpp.template"
                                                                }
                                                                if (lookahead)
                                                                {
                                                            #line 169 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"  nonbmp := false");
                                                            #line 115 "CodeGeneratorGo.cpp.template"
                                                                }
                                                            #line 174 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"  this.begin = this.end\n");
  append(L"  current := this.end\n");
  append(L"  result := initial[tokenSetId]");
                                                            #line 119 "CodeGeneratorGo.cpp.template"
                                                                if (variable("embedded").boolean() && (variable("trace").boolean() || ! variable("useGlr").boolean()))
                                                                {
                                                            #line 182 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"  state := 0");
                                                            #line 122 "CodeGeneratorGo.cpp.template"
                                                                }
                                                            #line 187 "CodeGeneratorGo.cpp"
  append(L"\n");
                                                            #line 124 "CodeGeneratorGo.cpp.template"
                                                                if (variable("trace").boolean())
                                                                {
                                                            #line 192 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"  writeTrace(\"    <next state=\\\"\" + strconv.Itoa(result & ");
                                                            #line 127 "CodeGeneratorGo.cpp.template"
                                                                  print(Math::powerof(2, variable("stateCodeBits").integer()) - 1);
                                                            #line 197 "CodeGeneratorGo.cpp"
  append(L") + \"\\\"\")");
                                                            #line 129 "CodeGeneratorGo.cpp.template"
                                                                }
                                                            #line 201 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"  for code := result & ");
                                                            #line 131 "CodeGeneratorGo.cpp.template"
                                                                print(Math::powerof(2, variable("stateCodeBits").integer()) - 1);
                                                            #line 206 "CodeGeneratorGo.cpp"
  append(L"; code != 0; {");
                                                            #line 132 "CodeGeneratorGo.cpp.template"
                                                                if (variable("trace").boolean())
                                                                {
                                                            #line 211 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"    writeTrace(\" offset=\\\"\" + strconv.Itoa(current) + \"\\\"\")");
                                                            #line 135 "CodeGeneratorGo.cpp.template"
                                                                }
                                                            #line 216 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"    var charclass int\n");
  append(L"    var c0 int\n");
  append(L"    if current < ");
                                                            #line 139 "CodeGeneratorGo.cpp.template"
                                                                print(prefix);
                                                            #line 223 "CodeGeneratorGo.cpp"
  append(L"size {\n");
  append(L"      r, s := utf8.DecodeRuneInString(");
                                                            #line 141 "CodeGeneratorGo.cpp.template"
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
                                                            #line 150 "CodeGeneratorGo.cpp.template"
                                                                print(format.toString<char>(variable("simplifiedCodeMap").integer(), 16, 0, 0, 0, "0123456789abcdef"));
                                                            #line 240 "CodeGeneratorGo.cpp"
  append(L" {");
                                                            #line 151 "CodeGeneratorGo.cpp.template"
                                                                if (variable("trace").boolean())
                                                                {
                                                            #line 245 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"      if c0 >= 32 && c0 <= 126 {\n");
  append(L"        writeTrace(\" char=\\\"\" + xmlEscape(string(rune(c0))) + \"\\\"\")\n");
  append(L"      }");
                                                            #line 156 "CodeGeneratorGo.cpp.template"
                                                                }
                                                            #line 252 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"      charclass = map0[c0]\n");
  append(L"    } else if c0 < 0x");
                                                            #line 159 "CodeGeneratorGo.cpp.template"
                                                                print(format.toString<char>(variable("uncompressedMapSize").integer(), 16, 0, 0, 0, "0123456789abcdef"));
                                                            #line 258 "CodeGeneratorGo.cpp"
  append(L" {\n");
                                                            #line 161 "CodeGeneratorGo.cpp.template"
                                                                compressedMapAccessor(6, "c", "charclass = ", "map1", &variable("m1bits").integer());
                                                            #line 262 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"    } else {");
                                                            #line 163 "CodeGeneratorGo.cpp.template"
                                                                if (variable("m2").size == 0)
                                                                {
                                                            #line 268 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"      charclass = 0");
                                                            #line 166 "CodeGeneratorGo.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 275 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"      lo := 0\n");
  append(L"      hi := ");
                                                            #line 171 "CodeGeneratorGo.cpp.template"
                                                                  print(variable("m2").size / 3 - 1);
                                                            #line 281 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"      for m := ");
                                                            #line 173 "CodeGeneratorGo.cpp.template"
                                                                  print((variable("m2").size / 3) >> 1);
                                                            #line 286 "CodeGeneratorGo.cpp"
  append(L"; ; m = (hi + lo) >> 1 {\n");
  append(L"        if map2[m] > int(c0) {\n");
  append(L"          hi = m - 1\n");
  append(L"        } else if map2[");
                                                            #line 177 "CodeGeneratorGo.cpp.template"
                                                                  print(variable("m2").size / 3);
                                                            #line 293 "CodeGeneratorGo.cpp"
  append(L" + m] < int(c0) {\n");
  append(L"          lo = m + 1\n");
  append(L"        } else {\n");
  append(L"          charclass = map2[");
                                                            #line 181 "CodeGeneratorGo.cpp.template"
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
                                                            #line 189 "CodeGeneratorGo.cpp.template"
                                                                }
                                                            #line 311 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"    }");
                                                            #line 191 "CodeGeneratorGo.cpp.template"
                                                                if (variable("trace").boolean())
                                                                {
                                                            #line 317 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"    writeTrace(\" codepoint=\\\"\" + strconv.Itoa(c0) + \"\\\" class=\\\"\" + strconv.Itoa(charclass) + \"\\\"\")");
                                                            #line 195 "CodeGeneratorGo.cpp.template"
                                                                }
                                                            #line 322 "CodeGeneratorGo.cpp"
  append(L"\n");
                                                            #line 197 "CodeGeneratorGo.cpp.template"
                                                                if (variable("trace").boolean() || ! variable("useGlr").boolean())
                                                                {
                                                            #line 327 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"    state = code");
                                                            #line 200 "CodeGeneratorGo.cpp.template"
                                                                }
                                                            #line 332 "CodeGeneratorGo.cpp"
  append(L"\n");
                                                            #line 202 "CodeGeneratorGo.cpp.template"
                                                                compressedMap2dAccessor("code - 1", "charclass", variable("a1cols").integer(),
                                                                                           4, "i", "code = ", "transition", &variable("a1bits").integer());
                                                            #line 337 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"    if code > ");
                                                            #line 205 "CodeGeneratorGo.cpp.template"
                                                                print(Math::powerof(2, variable("stateCodeBits").integer()) - 1);
                                                            #line 342 "CodeGeneratorGo.cpp"
  append(L" {\n");
  append(L"      result = code");
                                                            #line 207 "CodeGeneratorGo.cpp.template"
                                                                if (variable("trace").boolean())
                                                                {
                                                            #line 348 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"      writeTrace(\" result=\\\"\" + xmlEscape(");
                                                            #line 210 "CodeGeneratorGo.cpp.template"
                                                                  print(variable("tree").boolean() || variable("nolexer").boolean() ? "TOKEN" : "token");
                                                            #line 353 "CodeGeneratorGo.cpp"
  append(L"[((result >> ");
                                                            #line 211 "CodeGeneratorGo.cpp.template"
                                                                  print(variable("stateCodeBits").integer());
                                                            #line 357 "CodeGeneratorGo.cpp"
  append(L") & ");
                                                            #line 212 "CodeGeneratorGo.cpp.template"
                                                                  print(Math::powerof(2, variable("tokencodeBits").integer()) - 1);
                                                            #line 361 "CodeGeneratorGo.cpp"
  append(L") - 1]) + \"\\\"\")");
                                                            #line 214 "CodeGeneratorGo.cpp.template"
                                                                  if (lookahead || hasFixedTokenLength)
                                                                  {
                                                                    int contextOffset = variable("stateCodeBits").integer()
                                                                                      + variable("tokencodeBits").integer();
                                                                    int sizeOffset = contextOffset
                                                                                   + (hasFixedTokenLength ? 1 : 0);
                                                                    if (hasFixedTokenLength)
                                                                    {
                                                            #line 372 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"      if result & ");
                                                            #line 223 "CodeGeneratorGo.cpp.template"
                                                                      print(Math::powerof(2, contextOffset));
                                                            #line 377 "CodeGeneratorGo.cpp"
  append(L" > 0 {\n");
  append(L"        writeTrace(\" token-size=\\\"\" + strconv.Itoa(result >> ");
                                                            #line 225 "CodeGeneratorGo.cpp.template"
                                                                      print(sizeOffset);
                                                            #line 382 "CodeGeneratorGo.cpp"
  append(L") + \"\\\"\")\n");
  append(L"      } else ");
                                                            #line 227 "CodeGeneratorGo.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 389 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"      ");
                                                            #line 231 "CodeGeneratorGo.cpp.template"
                                                                    }
                                                            #line 394 "CodeGeneratorGo.cpp"
  append(L"if (result >> ");
                                                            #line 232 "CodeGeneratorGo.cpp.template"
                                                                    print(sizeOffset);
                                                            #line 398 "CodeGeneratorGo.cpp"
  append(L") > 0 {\n");
  append(L"        writeTrace(\" trailing-context-size=\\\"\" + strconv.Itoa(result >> ");
                                                            #line 235 "CodeGeneratorGo.cpp.template"
                                                                    print(sizeOffset);
                                                            #line 403 "CodeGeneratorGo.cpp"
  append(L") + \"\\\"\")\n");
  append(L"      }");
                                                            #line 237 "CodeGeneratorGo.cpp.template"
                                                                  }
                                                                }
                                                            #line 409 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"      code &= ");
                                                            #line 240 "CodeGeneratorGo.cpp.template"
                                                                print(Math::powerof(2, variable("stateCodeBits").integer()) - 1);
                                                            #line 414 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"      this.end = current\n");
  append(L"    }");
                                                            #line 243 "CodeGeneratorGo.cpp.template"
                                                                if (variable("trace").boolean())
                                                                {
                                                            #line 421 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"    writeTrace(\"/>\\n\")\n");
  append(L"    if code != 0 {\n");
  append(L"      writeTrace(\"    <next state=\\\"\" + strconv.Itoa(code) + \"\\\"\")\n");
  append(L"    }");
                                                            #line 249 "CodeGeneratorGo.cpp.template"
                                                                }
                                                            #line 429 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  result >>= ");
                                                            #line 253 "CodeGeneratorGo.cpp.template"
                                                                print(variable("stateCodeBits").integer());
                                                            #line 436 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"  if result == 0 {\n");
  append(L"    if this.end < ");
                                                            #line 256 "CodeGeneratorGo.cpp.template"
                                                                print(prefix);
                                                            #line 442 "CodeGeneratorGo.cpp"
  append(L"size {\n");
  append(L"      _, s := utf8.DecodeLastRuneInString(");
                                                            #line 258 "CodeGeneratorGo.cpp.template"
                                                                print(prefix);
                                                            #line 447 "CodeGeneratorGo.cpp"
  append(L"input[:current])\n");
  append(L"      this.end = current - s\n");
  append(L"    } else {\n");
  append(L"      this.end = current - 1\n");
  append(L"    }");
                                                            #line 263 "CodeGeneratorGo.cpp.template"
                                                                if (variable("trace").boolean())
                                                                {
                                                            #line 456 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"    writeTrace(\"    <fail begin=\\\"\" + strconv.Itoa(this.begin) + \"\\\" end=\\\"\" + strconv.Itoa(this.end) + \"\\\" state=\\\"\" + strconv.Itoa(state) + \"\\\"/>\\n\")\n");
  append(L"    writeTrace(\"  </tokenize>\\n\")");
                                                            #line 267 "CodeGeneratorGo.cpp.template"
                                                                }
                                                                if (variable("embedded").boolean())
                                                                {
                                                                  if (variable("useGlr").boolean())
                                                                  {
                                                            #line 466 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"    this.end = this.begin\n");
  append(L"    return -1");
                                                            #line 274 "CodeGeneratorGo.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 474 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"    return this.error(this.begin, this.end, state, -1, -1)");
                                                            #line 278 "CodeGeneratorGo.cpp.template"
                                                                  }
                                                                }
                                                            #line 480 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"  }");
                                                            #line 281 "CodeGeneratorGo.cpp.template"
                                                                lowBits = variable("tokencodeBits").integer();
                                                                if (hasFixedTokenLength && ! lookahead)
                                                                {
                                                            #line 487 "CodeGeneratorGo.cpp"
  append(L" else if (result & ");
                                                            #line 284 "CodeGeneratorGo.cpp.template"
                                                                  print(Math::powerof(2, lowBits));
                                                                  ++lowBits;
                                                            #line 492 "CodeGeneratorGo.cpp"
  append(L") != 0 {\n");
  append(L"    this.end = this.begin\n");
  append(L"  }");
                                                            #line 288 "CodeGeneratorGo.cpp.template"
                                                                }
                                                                else
                                                                {
                                                                  if (hasFixedTokenLength)
                                                                  {
                                                            #line 502 "CodeGeneratorGo.cpp"
  append(L" else if (result & ");
                                                            #line 293 "CodeGeneratorGo.cpp.template"
                                                                    print(Math::powerof(2, lowBits));
                                                                    ++lowBits;
                                                            #line 507 "CodeGeneratorGo.cpp"
  append(L") != 0 {\n");
  append(L"    this.end = this.begin\n");
  append(L"    if (nonbmp) {\n");
  append(L"      for i := result >> ");
                                                            #line 298 "CodeGeneratorGo.cpp.template"
                                                                    print(lowBits);
                                                            #line 514 "CodeGeneratorGo.cpp"
  append(L"; i > 0; i-- {\n");
  append(L"        if this.end >= ");
                                                            #line 300 "CodeGeneratorGo.cpp.template"
                                                                    print(prefix);
                                                            #line 519 "CodeGeneratorGo.cpp"
  append(L"size {\n");
  append(L"          this.end++\n");
  append(L"        } else {\n");
  append(L"          _, s := utf8.DecodeRuneInString(");
                                                            #line 304 "CodeGeneratorGo.cpp.template"
                                                                    print(prefix);
                                                            #line 526 "CodeGeneratorGo.cpp"
  append(L"input[this.end:])\n");
  append(L"          this.end += s\n");
  append(L"        }\n");
  append(L"      }\n");
  append(L"    } else {\n");
  append(L"      this.end += (result >> ");
                                                            #line 310 "CodeGeneratorGo.cpp.template"
                                                                    print(lowBits);
                                                            #line 535 "CodeGeneratorGo.cpp"
  append(L");\n");
  append(L"    }\n");
  append(L"  }");
                                                            #line 313 "CodeGeneratorGo.cpp.template"
                                                                  }
                                                                  if (lookahead)
                                                                  {
                                                            #line 543 "CodeGeneratorGo.cpp"
  append(L" else if nonbmp {\n");
  append(L"    for i := result >> ");
                                                            #line 317 "CodeGeneratorGo.cpp.template"
                                                                    print(lowBits);
                                                            #line 548 "CodeGeneratorGo.cpp"
  append(L"; i > 0; i-- {\n");
  append(L"      if this.end >= ");
                                                            #line 319 "CodeGeneratorGo.cpp.template"
                                                                    print(prefix);
                                                            #line 553 "CodeGeneratorGo.cpp"
  append(L"size {\n");
  append(L"        this.end--\n");
  append(L"      } else {\n");
  append(L"        _, s := utf8.DecodeLastRuneInString(");
                                                            #line 323 "CodeGeneratorGo.cpp.template"
                                                                    print(prefix);
                                                            #line 560 "CodeGeneratorGo.cpp"
  append(L"input[:this.end - 1])\n");
  append(L"        this.end -= s\n");
  append(L"      }\n");
  append(L"    }\n");
  append(L"  } else {\n");
  append(L"    this.end -= result >> ");
                                                            #line 329 "CodeGeneratorGo.cpp.template"
                                                                    print(lowBits);
                                                            #line 569 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"  }");
                                                            #line 331 "CodeGeneratorGo.cpp.template"
                                                                  }
                                                                }
                                                            #line 575 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"\n");
  append(L"  if this.end > ");
                                                            #line 336 "CodeGeneratorGo.cpp.template"
                                                                print(prefix);
                                                            #line 581 "CodeGeneratorGo.cpp"
  append(L"size {\n");
  append(L"    this.end = ");
                                                            #line 338 "CodeGeneratorGo.cpp.template"
                                                                print(prefix);
                                                            #line 586 "CodeGeneratorGo.cpp"
  append(L"size\n");
  append(L"  }");
                                                            #line 340 "CodeGeneratorGo.cpp.template"
                                                                if (variable("trace").boolean())
                                                                {
                                                            #line 592 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"  writeTrace(\"    <done result=\\\"\" + xmlEscape(");
                                                            #line 343 "CodeGeneratorGo.cpp.template"
                                                                  print(variable("tree").boolean() || variable("nolexer").boolean() ? "TOKEN" : "token");
                                                            #line 597 "CodeGeneratorGo.cpp"
  append(L"[(result & ");
                                                            #line 344 "CodeGeneratorGo.cpp.template"
                                                                  print(Math::powerof(2, variable("tokencodeBits").integer()) - 1);
                                                            #line 601 "CodeGeneratorGo.cpp"
  append(L") - 1]) + \"\\\" begin=\\\"\" + strconv.Itoa(this.begin) + \"\\\" end=\\\"\" + strconv.Itoa(this.end) + \"\\\"/>\\n\")\n");
  append(L"  writeTrace(\"  </tokenize>\\n\")");
                                                            #line 346 "CodeGeneratorGo.cpp.template"
                                                                }
                                                                if (hack)
                                                                {
                                                            #line 608 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"  return hack((result & ");
                                                            #line 350 "CodeGeneratorGo.cpp.template"
                                                                  print(Math::powerof(2, variable("tokencodeBits").integer()) - 1);
                                                            #line 613 "CodeGeneratorGo.cpp"
  append(L") - 1);\n");
  append(L"}\n");
                                                            #line 353 "CodeGeneratorGo.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 620 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"  return (result & ");
                                                            #line 357 "CodeGeneratorGo.cpp.template"
                                                                  print(Math::powerof(2, variable("tokencodeBits").integer()) - 1);
                                                            #line 625 "CodeGeneratorGo.cpp"
  append(L") - 1\n");
  append(L"}\n");
                                                            #line 360 "CodeGeneratorGo.cpp.template"
                                                                }
                                                              }
                                                              if (defined("gtbits"))
                                                              {
                                                            #line 633 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"func reduceAction(nonterminalId int, state int) int {\n");
                                                            #line 366 "CodeGeneratorGo.cpp.template"
                                                                compressedMap2dAccessor("nonterminalId", "state", variable("gtcols").integer(),
                                                                                        2, "i", "return ", "goTo", &variable("gtbits").integer());
                                                            #line 639 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"}\n");
                                                            #line 370 "CodeGeneratorGo.cpp.template"
                                                              }

                                                              if (! variable("embedded").boolean())
                                                              {
                                                            #line 647 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"  public String[] getExpectedTokenSet()\n");
  append(L"  {\n");
  append(L"    return getTokenSet(- state);\n");
  append(L"  }\n");
                                                            #line 379 "CodeGeneratorGo.cpp.template"
                                                              }
                                                              if (variable("trace").boolean())
                                                              {
                                                            #line 657 "CodeGeneratorGo.cpp"
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
                                                            #line 401 "CodeGeneratorGo.cpp.template"
                                                                if (variable("embedded").boolean())
                                                                {
                                                            #line 680 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"func flushTrace() {\n");
  append(L"  os.Stderr.Sync()\n");
  append(L"}\n");
                                                            #line 407 "CodeGeneratorGo.cpp.template"
                                                                }
                                                              }
                                                              if (variable("nolexer").boolean())
                                                              {
                                                            #line 690 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"  public static int getTokenCount() {return ");
                                                            #line 412 "CodeGeneratorGo.cpp.template"
                                                                print(variable("t1").size);
                                                            #line 695 "CodeGeneratorGo.cpp"
  append(L";}\n");
  append(L"  public static String getTokenName(int code) {return code >= 0 && code < ");
                                                            #line 415 "CodeGeneratorGo.cpp.template"
                                                                print(variable("t1").size);
                                                            #line 700 "CodeGeneratorGo.cpp"
  append(L" ? TOKEN[code] : null;}\n");
  append(L"  public static int getTokenSetCount() {return ");
                                                            #line 417 "CodeGeneratorGo.cpp.template"
                                                                print(variable("entrycount").integer());
                                                            #line 705 "CodeGeneratorGo.cpp"
  append(L";}\n");
  append(L"\n");
  append(L"func GetTokenSet(tokenSetId int) []string {");
                                                            #line 420 "CodeGeneratorGo.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 713 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"func getTokenSet(tokenSetId int) []string {");
                                                            #line 424 "CodeGeneratorGo.cpp.template"
                                                              }
                                                              if (! variable("nolexer").boolean())
                                                              {
                                                            #line 720 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"  var s int\n");
  append(L"  if tokenSetId < 0 {\n");
  append(L"    s = - tokenSetId\n");
  append(L"  } else {\n");
  append(L"    s = initial[tokenSetId] & ");
                                                            #line 432 "CodeGeneratorGo.cpp.template"
                                                                print(Math::powerof(2, variable("stateCodeBits").integer()) - 1);
                                                            #line 729 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"  }");
                                                            #line 434 "CodeGeneratorGo.cpp.template"
                                                              }
                                                            #line 734 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"  set := []string {}\n");
  append(L"  size := 0\n");
  append(L"  for i := 0; i < ");
                                                            #line 438 "CodeGeneratorGo.cpp.template"
                                                              print(variable("t1").size);
                                                            #line 741 "CodeGeneratorGo.cpp"
  append(L"; i += 32 {\n");
  append(L"    j := i\n");
  append(L"    i0 := (i >> 5) * ");
                                                            #line 441 "CodeGeneratorGo.cpp.template"
                                                              print(variable("transitionStateCount").integer());
                                                            #line 747 "CodeGeneratorGo.cpp"
  append(L" + ");
                                                            #line 442 "CodeGeneratorGo.cpp.template"
                                                              if (variable("nolexer").boolean())
                                                              {
                                                            #line 752 "CodeGeneratorGo.cpp"
  append(L"tokenSetId");
                                                            #line 444 "CodeGeneratorGo.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 758 "CodeGeneratorGo.cpp"
  append(L"s - 1");
                                                            #line 447 "CodeGeneratorGo.cpp.template"
                                                              }
                                                            #line 762 "CodeGeneratorGo.cpp"
  append(L"\n");
                                                            #line 449 "CodeGeneratorGo.cpp.template"
                                                              compressedMapAccessor(4, "i", "f := uint32(", "expected", &variable("t0bits").integer());
                                                            #line 766 "CodeGeneratorGo.cpp"
  append(L")\n");
  append(L"    for ; f != 0; f >>= 1 {\n");
  append(L"      if (f & 1) != 0 {\n");
  append(L"        set = append(set, ");
                                                            #line 453 "CodeGeneratorGo.cpp.template"
                                                              print(variable("tree").boolean() || variable("nolexer").boolean() ? "TOKEN" : "token");
                                                            #line 773 "CodeGeneratorGo.cpp"
  append(L"[j])\n");
  append(L"        size++\n");
  append(L"      }\n");
  append(L"      j++\n");
  append(L"    }\n");
  append(L"  }\n");
  append(L"  return set[:size]\n");
  append(L"}");
                                                            #line 461 "CodeGeneratorGo.cpp.template"
                                                              generateData();
                                                              if (! variable("embedded").boolean())
                                                              {
                                                            #line 786 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"\n");
  append(L"  public enum Token\n");
  append(L"  {\n");
  append(L"    ");
                                                            #line 468 "CodeGeneratorGo.cpp.template"
                                                                const CGVariable &token = variable("token");
                                                                int w = (int) Format::width(token.size);
                                                                for (size_t i = 0; i < token.size; ++i)
                                                                {
                                                                  if (i)
                                                                  {
                                                            #line 799 "CodeGeneratorGo.cpp"
  append(L",\n");
  append(L"    ");
                                                            #line 475 "CodeGeneratorGo.cpp.template"
                                                                  }
                                                            #line 804 "CodeGeneratorGo.cpp"
  append(L"/* ");
                                                            #line 476 "CodeGeneratorGo.cpp.template"
                                                                  print(format.toString<char>(i, 10, w));
                                                            #line 808 "CodeGeneratorGo.cpp"
  append(L" */ ");
                                                            #line 477 "CodeGeneratorGo.cpp.template"
                                                                  print(token.string(i));
                                                                }
                                                            #line 813 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"  };");
                                                            #line 480 "CodeGeneratorGo.cpp.template"
                                                              }
                                                              if (variable("selfTest").boolean())
                                                              {
                                                            #line 820 "CodeGeneratorGo.cpp"
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
                                                            #line 518 "CodeGeneratorGo.cpp.template"
                                                                print(variable("classname").string());
                                                            #line 859 "CodeGeneratorGo.cpp"
  append(L" testee = new ");
                                                            #line 519 "CodeGeneratorGo.cpp.template"
                                                                print(variable("classname").string());
                                                            #line 863 "CodeGeneratorGo.cpp"
  append(L"();\n");
  append(L"    for (int e = 0; e < ");
                                                            #line 521 "CodeGeneratorGo.cpp.template"
                                                                print(variable("a0").size);
                                                            #line 868 "CodeGeneratorGo.cpp"
  append(L"; ++e)\n");
  append(L"    {\n");
  append(L"      int s = INITIAL[e] & ");
                                                            #line 524 "CodeGeneratorGo.cpp.template"
                                                                print(Math::powerof(2, variable("stateCodeBits").integer()) - 1);
                                                            #line 874 "CodeGeneratorGo.cpp"
  append(L";\n");
  append(L"      for (int i = 0; i < ");
                                                            #line 526 "CodeGeneratorGo.cpp.template"
                                                                print(variable("t1").size);
                                                            #line 879 "CodeGeneratorGo.cpp"
  append(L"; i += 32)\n");
  append(L"      {\n");
  append(L"        int j = i;\n");
  append(L"        int i0 = (i >> 5) * ");
                                                            #line 530 "CodeGeneratorGo.cpp.template"
                                                                print(variable("transitionStateCount").integer());
                                                            #line 886 "CodeGeneratorGo.cpp"
  append(L" + s - 1;\n");
                                                            #line 532 "CodeGeneratorGo.cpp.template"
                                                                compressedMapAccessor(8, "i", "f := ", "expected", &variable("t0bits").integer());
                                                            #line 890 "CodeGeneratorGo.cpp"
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
                                                            #line 543 "CodeGeneratorGo.cpp.template"
                                                              }
                                                            #line 904 "CodeGeneratorGo.cpp"
  append(L"\n");
                                                            #line 545 "CodeGeneratorGo.cpp.template"
                                                              if (! variable("embedded").boolean())
                                                              {
                                                            #line 909 "CodeGeneratorGo.cpp"
  append(L"}\n");
                                                            #line 548 "CodeGeneratorGo.cpp.template"
                                                              }
                                                            }

                                                            void CodeGeneratorGo::generateCompressedMap()
                                                            {
                                                            #line 917 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"public class ");
                                                            #line 554 "CodeGeneratorGo.cpp.template"
                                                              print(variable("classname").string());
                                                            #line 922 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"{\n");
  append(L"  public static int get(int i0)\n");
  append(L"  {\n");
  append(L"    if (i0 < 0x30000)\n");
  append(L"    {\n");
                                                            #line 561 "CodeGeneratorGo.cpp.template"
                                                              compressedMapAccessor(6, "i", "return ", "low", &variable("dtbits").integer());
                                                            #line 931 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"    }\n");
  append(L"    else\n");
  append(L"    {");
                                                            #line 565 "CodeGeneratorGo.cpp.template"
                                                              indent += 3;
                                                              generateBinarySearch("i0", "return ", "", "HIGH", variable("rm").size);
                                                              indent -= 3;
                                                            #line 940 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"    }\n");
  append(L"  }");
                                                            #line 570 "CodeGeneratorGo.cpp.template"
                                                              generateData();
                                                            #line 946 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"}\n");
                                                            #line 573 "CodeGeneratorGo.cpp.template"
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
                                                            #line 962 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"\n");
  append(L"var ");
                                                            #line 587 "CodeGeneratorGo.cpp.template"
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
                                                            #line 980 "CodeGeneratorGo.cpp"
  append(L" = [...]");
                                                            #line 600 "CodeGeneratorGo.cpp.template"
                                                                if ( a->hasType(CGVariable::UNSIGNED))
                                                                {
                                                            #line 985 "CodeGeneratorGo.cpp"
  append(L"u");
                                                            #line 602 "CodeGeneratorGo.cpp.template"
                                                                }
                                                            #line 989 "CodeGeneratorGo.cpp"
  append(L"int {");
                                                            #line 603 "CodeGeneratorGo.cpp.template"
                                                                int w = (int) Format::width(a->size);
                                                                for (size_t j = 0; j < a->size; ++j)
                                                                {
                                                                  if (j == 0 || lineLength() + Format::width(a->integer(j)) + 2 > limit)
                                                                  {
                                                                    if (j) print(",");
                                                            #line 998 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"/* ");
                                                            #line 610 "CodeGeneratorGo.cpp.template"
                                                                    print(format.toString<char>(j, 10, w));
                                                            #line 1003 "CodeGeneratorGo.cpp"
  append(L" */ ");
                                                            #line 611 "CodeGeneratorGo.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 1009 "CodeGeneratorGo.cpp"
  append(L", ");
                                                            #line 614 "CodeGeneratorGo.cpp.template"
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
                                                            #line 1022 "CodeGeneratorGo.cpp"
  append(L"}");
                                                            #line 624 "CodeGeneratorGo.cpp.template"
                                                              }
                                                              for (VarsInInsertionOrder::iterator a(varsInInsertionOrder.begin());
                                                                   a != varsInInsertionOrder.end(); ++a)
                                                                if (a->isArray() && a->size > 0 && a->hasType(CGVariable::STRING) && strlen(a->name) == 2)
                                                              {
                                                            #line 1030 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"\n");
  append(L"var ");
                                                            #line 631 "CodeGeneratorGo.cpp.template"
                                                                if (strcmp(a->longName, "TOKEN") == 0)
                                                                {
                                                                  print(variable("tree").boolean() || variable("nolexer").boolean() ? "TOKEN" : "token");
                                                                }
                                                                else
                                                                {
                                                                  print(variable("tree").boolean() ? "NONTERMINAL" : "nonterminal");
                                                                }
                                                            #line 1043 "CodeGeneratorGo.cpp"
  append(L" = [...]string {\n");
                                                            #line 640 "CodeGeneratorGo.cpp.template"
                                                                for (size_t j = 0; j < a->size; ++j)
                                                                {
                                                                  if (j)
                                                                  {
                                                            #line 1050 "CodeGeneratorGo.cpp"
  append(L",\n");
                                                            #line 645 "CodeGeneratorGo.cpp.template"
                                                                  }
                                                            #line 1054 "CodeGeneratorGo.cpp"
  append(L"    \"");
                                                            #line 646 "CodeGeneratorGo.cpp.template"
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
                                                            #line 1069 "CodeGeneratorGo.cpp"
  append(L"\"");
                                                            #line 658 "CodeGeneratorGo.cpp.template"
                                                                }
                                                            #line 1073 "CodeGeneratorGo.cpp"
  append(L"}");
                                                            #line 659 "CodeGeneratorGo.cpp.template"
                                                              }
                                                            }

                                                            void CodeGeneratorGo::generateBinarySearch(const char *input, const char *outputPrefix, const char *outputSuffix, const char *map, size_t size)
                                                            {
                                                            #line 1081 "CodeGeneratorGo.cpp"
  append(L"\n");
  append(L"int lo = 0, hi = ");
                                                            #line 665 "CodeGeneratorGo.cpp.template"
                                                              print(size / 3 - 1);
                                                            #line 1086 "CodeGeneratorGo.cpp"
  append(L";\n");
  append(L"for (int m = ");
                                                            #line 667 "CodeGeneratorGo.cpp.template"
                                                              print((size / 3) >> 1);
                                                            #line 1091 "CodeGeneratorGo.cpp"
  append(L"; ; m = (hi + lo) >> 1)\n");
  append(L"{\n");
  append(L"  if (");
                                                            #line 670 "CodeGeneratorGo.cpp.template"
                                                              print(map);
                                                            #line 1097 "CodeGeneratorGo.cpp"
  append(L"[m] > ");
                                                            #line 671 "CodeGeneratorGo.cpp.template"
                                                              print(input);
                                                            #line 1101 "CodeGeneratorGo.cpp"
  append(L") {hi = m - 1;}\n");
  append(L"  else if (");
                                                            #line 673 "CodeGeneratorGo.cpp.template"
                                                              print(map);
                                                            #line 1106 "CodeGeneratorGo.cpp"
  append(L"[");
                                                            #line 674 "CodeGeneratorGo.cpp.template"
                                                              print(size / 3);
                                                            #line 1110 "CodeGeneratorGo.cpp"
  append(L" + m] < ");
                                                            #line 675 "CodeGeneratorGo.cpp.template"
                                                              print(input);
                                                            #line 1114 "CodeGeneratorGo.cpp"
  append(L") {lo = m + 1;}\n");
  append(L"  else {");
                                                            #line 677 "CodeGeneratorGo.cpp.template"
                                                              print(outputPrefix);
                                                              print(map);
                                                            #line 1120 "CodeGeneratorGo.cpp"
  append(L"[");
                                                            #line 679 "CodeGeneratorGo.cpp.template"
                                                              print(size / 3 * 2);
                                                            #line 1124 "CodeGeneratorGo.cpp"
  append(L" + m]");
                                                            #line 680 "CodeGeneratorGo.cpp.template"
                                                              print(outputSuffix);
                                                            #line 1128 "CodeGeneratorGo.cpp"
  append(L";}\n");
  append(L"  if (lo > hi) {");
                                                            #line 682 "CodeGeneratorGo.cpp.template"
                                                              print(outputPrefix);
                                                            #line 1133 "CodeGeneratorGo.cpp"
  append(L"0");
                                                            #line 683 "CodeGeneratorGo.cpp.template"
                                                              print(outputSuffix);
                                                            #line 1137 "CodeGeneratorGo.cpp"
  append(L";}\n");
  append(L"}");
                                                            #line 685 "CodeGeneratorGo.cpp.template"
                                                            }

// End
