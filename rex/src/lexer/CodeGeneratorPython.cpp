// This file was generated on Sun Nov 24, 2024 16:09 (UTC+01) by REx v6.0 which is Copyright (c) 1979-2024 by Gunther Rademacher <grd@gmx.net>
// REx command line: CodeGeneratorPython.cpp.template
                                                            #line 1 "CodeGeneratorPython.cpp.template"
                                                            // generate CodeGeneratorPython.cpp using this command:
                                                            //
                                                            //   REx CodeGeneratorPython.cpp.template

                                                            #include "../common/Memory.hpp"

                                                            #include "CodeGenerator.hpp"

                                                            void CodeGeneratorPython::generateStaticCode()
                                                            {
                                                              isPython = true;

                                                              const char *prefix = variable("useGlr").boolean()
                                                                                 ? "self.parser."
                                                                                 : "self.";
                                                              if (! variable("append").boolean() && ! variable("embedded").boolean())
                                                              {
                                                                if (*variable("package").string())
                                                                {
                                                            #line 24 "CodeGeneratorPython.cpp"
  append(L"package ");
                                                            #line 20 "CodeGeneratorPython.cpp.template"
                                                                  print(variable("package").string());
                                                            #line 28 "CodeGeneratorPython.cpp"
  append(L";\n");
  append(L"\n");
                                                            #line 23 "CodeGeneratorPython.cpp.template"
                                                                }
                                                            #line 33 "CodeGeneratorPython.cpp"
  append(L"public class ");
                                                            #line 24 "CodeGeneratorPython.cpp.template"
                                                                print(variable("classname").string());
                                                            #line 37 "CodeGeneratorPython.cpp"
  append(L"\n");
  append(L"{\n");
                                                            #line 27 "CodeGeneratorPython.cpp.template"
                                                              }
                                                              ++indent;
                                                              if (variable("useGlr").boolean())
                                                              {
                                                                ++indent;
                                                              }
                                                              const char *clazz = /* variable("useGlr").boolean() ? "ParsingThread" : */ variable("classname").string();
                                                              if (! variable("embedded").boolean())
                                                              {
                                                            #line 50 "CodeGeneratorPython.cpp"
  append(L"\n");
  append(L"public void init(String string)\n");
  append(L"{\n");
  append(L"  input = string;\n");
  append(L"  size = string.length();\n");
  append(L"  end = 0;\n");
  append(L"}\n");
  append(L"\n");
  append(L"public int getOffset() {return begin;}\n");
  append(L"public int getSize()   {return end - begin;}\n");
  append(L"public int getState()  {return state;}\n");
  append(L"\n");
  append(L"public int match(int tokenSetId, String string)\n");
  append(L"{\n");
  append(L"  init(string);\n");
  append(L"  return match(tokenSetId);\n");
  append(L"}\n");
  append(L"\n");
  append(L"public");
                                                            #line 54 "CodeGeneratorPython.cpp.template"
                                                              }
                                                              else
                                                              {
                                                                if (variable("lrparser").boolean() ||
                                                                    variable("tables").boolean())
                                                                {
                                                            #line 77 "CodeGeneratorPython.cpp"
  append(L"\n");
  append(L"def predict(self, dpi):");
                                                            #line 61 "CodeGeneratorPython.cpp.template"
                                                                  predict();
                                                                }
                                                              }
                                                            #line 84 "CodeGeneratorPython.cpp"
  append(L"\n");
  append(L"def match(self, tokenSetId):");
                                                            #line 65 "CodeGeneratorPython.cpp.template"
                                                              if (variable("nolexer").boolean())
                                                              {
                                                            #line 90 "CodeGeneratorPython.cpp"
  append(L"\n");
  append(L"  token.begin = end\n");
  append(L"  lexer.match(tokenSetId, token)\n");
  append(L"  begin = token.begin\n");
  append(L"  end = token.end\n");
  append(L"  return token.code >= 0\n");
  append(L"       ? token.code\n");
  append(L"       : error(begin, end, - tokenSetId, -1, -1)\n");
                                                            #line 76 "CodeGeneratorPython.cpp.template"
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
                                                            #line 111 "CodeGeneratorPython.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 88 "CodeGeneratorPython.cpp.template"
                                                                  print(variable("classname").string());
                                                            #line 116 "CodeGeneratorPython.cpp"
  append(L".writeTrace(\"  <tokenize ");
                                                            #line 90 "CodeGeneratorPython.cpp.template"
                                                                  if (variable("useGlr").boolean())
                                                                  {
                                                            #line 121 "CodeGeneratorPython.cpp"
  append(L"thread=\\\"\" + str(self.id) + \"\\\" ");
                                                            #line 92 "CodeGeneratorPython.cpp.template"
                                                                  }
                                                            #line 125 "CodeGeneratorPython.cpp"
  append(L"tokenset=\\\"\" + str(tokenSetId) + \"\\\">\\n\")\n");
                                                            #line 94 "CodeGeneratorPython.cpp.template"
                                                                }
                                                            #line 129 "CodeGeneratorPython.cpp"
  append(L"\n");
  append(L"  self.begin = self.end\n");
  append(L"  current = self.end\n");
  append(L"  result = ");
                                                            #line 98 "CodeGeneratorPython.cpp.template"
                                                                print(clazz);
                                                            #line 136 "CodeGeneratorPython.cpp"
  append(L".INITIAL[tokenSetId]");
                                                            #line 99 "CodeGeneratorPython.cpp.template"
                                                                if (variable("embedded").boolean() && (variable("trace").boolean() || ! variable("useGlr").boolean()))
                                                                {
                                                            #line 141 "CodeGeneratorPython.cpp"
  append(L"\n");
  append(L"  state = 0");
                                                            #line 102 "CodeGeneratorPython.cpp.template"
                                                                }
                                                            #line 146 "CodeGeneratorPython.cpp"
  append(L"\n");
                                                            #line 104 "CodeGeneratorPython.cpp.template"
                                                                if (variable("trace").boolean())
                                                                {
                                                            #line 151 "CodeGeneratorPython.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 107 "CodeGeneratorPython.cpp.template"
                                                                  print(variable("classname").string());
                                                            #line 156 "CodeGeneratorPython.cpp"
  append(L".writeTrace(\"    <next state=\\\"\" + str(result & ");
                                                            #line 108 "CodeGeneratorPython.cpp.template"
                                                                  print(Math::powerof(2, variable("stateCodeBits").integer()) - 1);
                                                            #line 160 "CodeGeneratorPython.cpp"
  append(L") + \"\\\"\")");
                                                            #line 109 "CodeGeneratorPython.cpp.template"
                                                                }
                                                            #line 164 "CodeGeneratorPython.cpp"
  append(L"\n");
  append(L"  code = result & ");
                                                            #line 111 "CodeGeneratorPython.cpp.template"
                                                                print(Math::powerof(2, variable("stateCodeBits").integer()) - 1);
                                                            #line 169 "CodeGeneratorPython.cpp"
  append(L"\n");
  append(L"  while code != 0:");
                                                            #line 113 "CodeGeneratorPython.cpp.template"
                                                                if (variable("trace").boolean())
                                                                {
                                                            #line 175 "CodeGeneratorPython.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 116 "CodeGeneratorPython.cpp.template"
                                                                  print(variable("classname").string());
                                                            #line 180 "CodeGeneratorPython.cpp"
  append(L".writeTrace(\" offset=\\\"\" + str(current) + \"\\\"\")");
                                                            #line 117 "CodeGeneratorPython.cpp.template"
                                                                }
                                                            #line 184 "CodeGeneratorPython.cpp"
  append(L"\n");
  append(L"    if current < ");
                                                            #line 119 "CodeGeneratorPython.cpp.template"
                                                                print(prefix);
                                                            #line 189 "CodeGeneratorPython.cpp"
  append(L"size:\n");
  append(L"      c0 = ord(");
                                                            #line 121 "CodeGeneratorPython.cpp.template"
                                                                print(prefix);
                                                            #line 194 "CodeGeneratorPython.cpp"
  append(L"input[current])\n");
  append(L"    else:\n");
  append(L"      c0 = 0\n");
  append(L"    current += 1");
  append(L"\n");
  append(L"    if c0 < 0x");
                                                            #line 127 "CodeGeneratorPython.cpp.template"
                                                                print(format.toString<char>(variable("simplifiedCodeMap").integer(), 16, 0, 0, 0, "0123456789abcdef"));
                                                            #line 203 "CodeGeneratorPython.cpp"
  append(L":");
                                                            #line 129 "CodeGeneratorPython.cpp.template"
                                                                if (variable("trace").boolean())
                                                                {
                                                            #line 208 "CodeGeneratorPython.cpp"
  append(L"\n");
  append(L"      if c0 >= 32 and c0 <= 126:\n");
  append(L"        ");
                                                            #line 133 "CodeGeneratorPython.cpp.template"
                                                                  print(variable("classname").string());
                                                            #line 214 "CodeGeneratorPython.cpp"
  append(L".writeTrace(\" char=\\\"\" + ");
                                                            #line 134 "CodeGeneratorPython.cpp.template"
                                                                  print(clazz);
                                                            #line 218 "CodeGeneratorPython.cpp"
  append(L".xmlEscape(chr(c0)) + \"\\\"\")");
                                                            #line 135 "CodeGeneratorPython.cpp.template"
                                                                }
                                                            #line 222 "CodeGeneratorPython.cpp"
  append(L"\n");
  append(L"      charclass = ");
                                                            #line 137 "CodeGeneratorPython.cpp.template"
                                                                print(clazz);
                                                            #line 227 "CodeGeneratorPython.cpp"
  append(L".MAP0[c0]\n");
  append(L"    elif c0 < 0x");
                                                            #line 139 "CodeGeneratorPython.cpp.template"
                                                                print(format.toString<char>(variable("uncompressedMapSize").integer(), 16, 0, 0, 0, "0123456789abcdef"));
                                                            #line 232 "CodeGeneratorPython.cpp"
  append(L":\n");
                                                            #line 141 "CodeGeneratorPython.cpp.template"
                                                                compressedMapAccessor(6, "c", "charclass = ", "MAP1", &variable("m1bits").integer());
                                                            #line 236 "CodeGeneratorPython.cpp"
  append(L"\n");
  append(L"    else:");
                                                            #line 143 "CodeGeneratorPython.cpp.template"
                                                                if (variable("m2").size == 0)
                                                                {
                                                            #line 242 "CodeGeneratorPython.cpp"
  append(L"\n");
  append(L"      charclass = 0");
                                                            #line 146 "CodeGeneratorPython.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 249 "CodeGeneratorPython.cpp"
  append(L"\n");
  append(L"      lo = 0\n");
  append(L"      hi = ");
                                                            #line 151 "CodeGeneratorPython.cpp.template"
                                                                  print(variable("m2").size / 3 - 1);
                                                            #line 255 "CodeGeneratorPython.cpp"
  append(L"\n");
  append(L"      m = ");
                                                            #line 153 "CodeGeneratorPython.cpp.template"
                                                                  print((variable("m2").size / 3) >> 1);
                                                            #line 260 "CodeGeneratorPython.cpp"
  append(L"\n");
  append(L"      while True:\n");
  append(L"        if ");
                                                            #line 156 "CodeGeneratorPython.cpp.template"
                                                                  print(clazz);
                                                            #line 266 "CodeGeneratorPython.cpp"
  append(L".MAP2[m] > int(c0):\n");
  append(L"          hi = m - 1\n");
  append(L"        elif ");
                                                            #line 159 "CodeGeneratorPython.cpp.template"
                                                                  print(clazz);
                                                            #line 272 "CodeGeneratorPython.cpp"
  append(L".MAP2[");
                                                            #line 160 "CodeGeneratorPython.cpp.template"
                                                                  print(variable("m2").size / 3);
                                                            #line 276 "CodeGeneratorPython.cpp"
  append(L" + m] < int(c0):\n");
  append(L"          lo = m + 1\n");
  append(L"        else:\n");
  append(L"          charclass = ");
                                                            #line 164 "CodeGeneratorPython.cpp.template"
                                                                  print(clazz);
                                                            #line 283 "CodeGeneratorPython.cpp"
  append(L".MAP2[");
                                                            #line 165 "CodeGeneratorPython.cpp.template"
                                                                  print(variable("m2").size / 3 * 2);
                                                            #line 287 "CodeGeneratorPython.cpp"
  append(L" + m]\n");
  append(L"          break\n");
  append(L"        if lo > hi:\n");
  append(L"          charclass = 0\n");
  append(L"          break\n");
  append(L"        m = (hi + lo) >> 1");
                                                            #line 171 "CodeGeneratorPython.cpp.template"
                                                                }
                                                                if (variable("trace").boolean())
                                                                {
                                                            #line 298 "CodeGeneratorPython.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 175 "CodeGeneratorPython.cpp.template"
                                                                  print(variable("classname").string());
                                                            #line 303 "CodeGeneratorPython.cpp"
  append(L".writeTrace(\" codepoint=\\\"\" + str(c0) + \"\\\" class=\\\"\" + str(charclass) + \"\\\"\")");
                                                            #line 177 "CodeGeneratorPython.cpp.template"
                                                                }
                                                            #line 307 "CodeGeneratorPython.cpp"
  append(L"\n");
                                                            #line 179 "CodeGeneratorPython.cpp.template"
                                                                if (variable("trace").boolean() || ! variable("useGlr").boolean())
                                                                {
                                                            #line 312 "CodeGeneratorPython.cpp"
  append(L"\n");
  append(L"    state = code");
                                                            #line 182 "CodeGeneratorPython.cpp.template"
                                                                }
                                                            #line 317 "CodeGeneratorPython.cpp"
  append(L"\n");
                                                            #line 184 "CodeGeneratorPython.cpp.template"
                                                                compressedMap2dAccessor("code - 1", "charclass", variable("a1cols").integer(),
                                                                                           4, "i", "code = ", "TRANSITION", &variable("a1bits").integer());
                                                            #line 322 "CodeGeneratorPython.cpp"
  append(L"\n");
  append(L"    if code > ");
                                                            #line 187 "CodeGeneratorPython.cpp.template"
                                                                print(Math::powerof(2, variable("stateCodeBits").integer()) - 1);
                                                            #line 327 "CodeGeneratorPython.cpp"
  append(L":\n");
  append(L"      result = code");
                                                            #line 189 "CodeGeneratorPython.cpp.template"
                                                                if (variable("trace").boolean())
                                                                {
                                                            #line 333 "CodeGeneratorPython.cpp"
  append(L"\n");
  append(L"      ");
                                                            #line 192 "CodeGeneratorPython.cpp.template"
                                                                  print(variable("classname").string());
                                                            #line 338 "CodeGeneratorPython.cpp"
  append(L".writeTrace(\" result=\\\"\" + ");
                                                            #line 193 "CodeGeneratorPython.cpp.template"
                                                                  print(clazz);
                                                            #line 342 "CodeGeneratorPython.cpp"
  append(L".xmlEscape(");
                                                            #line 194 "CodeGeneratorPython.cpp.template"
                                                                  print(clazz);
                                                            #line 346 "CodeGeneratorPython.cpp"
  append(L".TOKEN[((result >> ");
                                                            #line 196 "CodeGeneratorPython.cpp.template"
                                                                  print(variable("stateCodeBits").integer());
                                                            #line 350 "CodeGeneratorPython.cpp"
  append(L") & ");
                                                            #line 197 "CodeGeneratorPython.cpp.template"
                                                                  print(Math::powerof(2, variable("tokencodeBits").integer()) - 1);
                                                            #line 354 "CodeGeneratorPython.cpp"
  append(L") - 1]) + \"\\\"\")");
                                                            #line 198 "CodeGeneratorPython.cpp.template"
                                                                  if (lookahead || hasFixedTokenLength)
                                                                  {
                                                                    int contextOffset = variable("stateCodeBits").integer()
                                                                                      + variable("tokencodeBits").integer();
                                                                    int sizeOffset = contextOffset
                                                                                   + (hasFixedTokenLength ? 1 : 0);
                                                                    if (hasFixedTokenLength)
                                                                    {
                                                            #line 365 "CodeGeneratorPython.cpp"
  append(L"\n");
  append(L"      if result & ");
                                                            #line 207 "CodeGeneratorPython.cpp.template"
                                                                      print(Math::powerof(2, contextOffset));
                                                            #line 370 "CodeGeneratorPython.cpp"
  append(L" > 0:\n");
  append(L"        ");
                                                            #line 209 "CodeGeneratorPython.cpp.template"
                                                                      print(variable("classname").string());
                                                            #line 375 "CodeGeneratorPython.cpp"
  append(L".writeTrace(\" token-size=\\\"\" + str(result >> ");
                                                            #line 210 "CodeGeneratorPython.cpp.template"
                                                                      print(sizeOffset);
                                                            #line 379 "CodeGeneratorPython.cpp"
  append(L") + \"\\\"\")\n");
  append(L"      el");
                                                            #line 212 "CodeGeneratorPython.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 386 "CodeGeneratorPython.cpp"
  append(L"\n");
  append(L"      ");
                                                            #line 216 "CodeGeneratorPython.cpp.template"
                                                                    }
                                                            #line 391 "CodeGeneratorPython.cpp"
  append(L"if (result >> ");
                                                            #line 217 "CodeGeneratorPython.cpp.template"
                                                                    print(sizeOffset);
                                                            #line 395 "CodeGeneratorPython.cpp"
  append(L") > 0:\n");
  append(L"        ");
                                                            #line 219 "CodeGeneratorPython.cpp.template"
                                                                    print(variable("classname").string());
                                                            #line 400 "CodeGeneratorPython.cpp"
  append(L".writeTrace(\" trailing-context-size=\\\"\" + str(result >> ");
                                                            #line 220 "CodeGeneratorPython.cpp.template"
                                                                    print(sizeOffset);
                                                            #line 404 "CodeGeneratorPython.cpp"
  append(L") + \"\\\"\")");
                                                            #line 222 "CodeGeneratorPython.cpp.template"
                                                                  }
                                                                }
                                                            #line 409 "CodeGeneratorPython.cpp"
  append(L"\n");
  append(L"      code &= ");
                                                            #line 225 "CodeGeneratorPython.cpp.template"
                                                                print(Math::powerof(2, variable("stateCodeBits").integer()) - 1);
                                                            #line 414 "CodeGeneratorPython.cpp"
  append(L"\n");
  append(L"      self.end = current");
                                                            #line 227 "CodeGeneratorPython.cpp.template"
                                                                if (variable("trace").boolean())
                                                                {
                                                            #line 420 "CodeGeneratorPython.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 230 "CodeGeneratorPython.cpp.template"
                                                                  print(variable("classname").string());
                                                            #line 425 "CodeGeneratorPython.cpp"
  append(L".writeTrace(\"/>\\n\")\n");
  append(L"    if code != 0:\n");
  append(L"      ");
                                                            #line 233 "CodeGeneratorPython.cpp.template"
                                                                  print(variable("classname").string());
                                                            #line 431 "CodeGeneratorPython.cpp"
  append(L".writeTrace(\"    <next state=\\\"\" + str(code) + \"\\\"\") ");
                                                            #line 234 "CodeGeneratorPython.cpp.template"
                                                                }
                                                            #line 435 "CodeGeneratorPython.cpp"
  append(L"\n");
  append(L"\n");
  append(L"  result >>= ");
                                                            #line 237 "CodeGeneratorPython.cpp.template"
                                                                print(variable("stateCodeBits").integer());
                                                            #line 441 "CodeGeneratorPython.cpp"
  append(L"\n");
  append(L"  if result == 0:\n");
  append(L"    self.end = current - 1");
                                                            #line 240 "CodeGeneratorPython.cpp.template"
                                                                if (variable("trace").boolean())
                                                                {
                                                            #line 448 "CodeGeneratorPython.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 243 "CodeGeneratorPython.cpp.template"
                                                                  print(variable("classname").string());
                                                            #line 453 "CodeGeneratorPython.cpp"
  append(L".writeTrace(\"    <fail begin=\\\"\" + str(self.begin) + \"\\\" end=\\\"\" + str(self.end) + \"\\\" state=\\\"\" + str(state) + \"\\\"/>\\n\")\n");
  append(L"    ");
                                                            #line 245 "CodeGeneratorPython.cpp.template"
                                                                  print(variable("classname").string());
                                                            #line 458 "CodeGeneratorPython.cpp"
  append(L".writeTrace(\"  </tokenize>\\n\")");
                                                            #line 246 "CodeGeneratorPython.cpp.template"
                                                                }
                                                                if (variable("embedded").boolean())
                                                                {
                                                                  if (variable("useGlr").boolean())
                                                                  {
                                                            #line 466 "CodeGeneratorPython.cpp"
  append(L"\n");
  append(L"    self.end = self.begin\n");
  append(L"    return -1");
                                                            #line 253 "CodeGeneratorPython.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 474 "CodeGeneratorPython.cpp"
  append(L"\n");
  append(L"    return self.error(self.begin, self.end, state, -1, -1)");
                                                            #line 257 "CodeGeneratorPython.cpp.template"
                                                                  }
                                                                }
                                                                lowBits = variable("tokencodeBits").integer();
                                                                if (hasFixedTokenLength && ! lookahead)
                                                                {
                                                            #line 483 "CodeGeneratorPython.cpp"
  append(L"\n");
  append(L"  elif result & ");
                                                            #line 263 "CodeGeneratorPython.cpp.template"
                                                                  print(Math::powerof(2, lowBits));
                                                                  ++lowBits;
                                                            #line 489 "CodeGeneratorPython.cpp"
  append(L" != 0:\n");
  append(L"    self.end = self.begin");
                                                            #line 266 "CodeGeneratorPython.cpp.template"
                                                                }
                                                                else
                                                                {
                                                                  if (hasFixedTokenLength)
                                                                  {
                                                            #line 498 "CodeGeneratorPython.cpp"
  append(L"\n");
  append(L"  elif result & ");
                                                            #line 272 "CodeGeneratorPython.cpp.template"
                                                                    print(Math::powerof(2, lowBits));
                                                                    ++lowBits;
                                                            #line 504 "CodeGeneratorPython.cpp"
  append(L" != 0:\n");
  append(L"    self.end = self.begin\n");
  append(L"    self.end += (result >> ");
                                                            #line 276 "CodeGeneratorPython.cpp.template"
                                                                    print(lowBits);
                                                            #line 510 "CodeGeneratorPython.cpp"
  append(L")");
                                                            #line 277 "CodeGeneratorPython.cpp.template"
                                                                  }
                                                                  if (lookahead)
                                                                  {
                                                            #line 516 "CodeGeneratorPython.cpp"
  append(L"\n");
  append(L"  else:\n");
  append(L"    self.end -= result >> ");
                                                            #line 282 "CodeGeneratorPython.cpp.template"
                                                                    print(lowBits);
                                                                  }
                                                                }
                                                            #line 524 "CodeGeneratorPython.cpp"
  append(L"\n");
  append(L"\n");
  append(L"  if self.end > ");
                                                            #line 288 "CodeGeneratorPython.cpp.template"
                                                                print(prefix);
                                                            #line 530 "CodeGeneratorPython.cpp"
  append(L"size:\n");
  append(L"    self.end = ");
                                                            #line 290 "CodeGeneratorPython.cpp.template"
                                                                print(prefix);
                                                            #line 535 "CodeGeneratorPython.cpp"
  append(L"size");
                                                            #line 291 "CodeGeneratorPython.cpp.template"
                                                                if (variable("trace").boolean())
                                                                {
                                                            #line 540 "CodeGeneratorPython.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 294 "CodeGeneratorPython.cpp.template"
                                                                  print(variable("classname").string());
                                                            #line 545 "CodeGeneratorPython.cpp"
  append(L".writeTrace(\"    <done result=\\\"\" + ");
                                                            #line 295 "CodeGeneratorPython.cpp.template"
                                                                  print(clazz);
                                                            #line 549 "CodeGeneratorPython.cpp"
  append(L".xmlEscape(");
                                                            #line 296 "CodeGeneratorPython.cpp.template"
                                                                  print(clazz);
                                                            #line 553 "CodeGeneratorPython.cpp"
  append(L".TOKEN[(result & ");
                                                            #line 298 "CodeGeneratorPython.cpp.template"
                                                                  print(Math::powerof(2, variable("tokencodeBits").integer()) - 1);
                                                            #line 557 "CodeGeneratorPython.cpp"
  append(L") - 1]) + \"\\\" begin=\\\"\" + str(self.begin) + \"\\\" end=\\\"\" + str(self.end) + \"\\\"/>\\n\")\n");
  append(L"  ");
                                                            #line 300 "CodeGeneratorPython.cpp.template"
                                                            print(variable("classname").string());
                                                            #line 562 "CodeGeneratorPython.cpp"
  append(L".writeTrace(\"  </tokenize>\\n\")");
                                                            #line 301 "CodeGeneratorPython.cpp.template"
                                                                }
                                                                if (hack)
                                                                {
                                                            #line 568 "CodeGeneratorPython.cpp"
  append(L"\n");
  append(L"  return hack((result & ");
                                                            #line 305 "CodeGeneratorPython.cpp.template"
                                                                  print(Math::powerof(2, variable("tokencodeBits").integer()) - 1);
                                                            #line 573 "CodeGeneratorPython.cpp"
  append(L") - 1)\n");
                                                            #line 307 "CodeGeneratorPython.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 579 "CodeGeneratorPython.cpp"
  append(L"\n");
  append(L"  return (result & ");
                                                            #line 311 "CodeGeneratorPython.cpp.template"
                                                                  print(Math::powerof(2, variable("tokencodeBits").integer()) - 1);
                                                            #line 584 "CodeGeneratorPython.cpp"
  append(L") - 1\n");
                                                            #line 313 "CodeGeneratorPython.cpp.template"
                                                                }

                                                                if (variable("useGlr").boolean())
                                                                {
                                                                  --indent;
                                                                }
                                                              }
                                                              if (defined("gtbits"))
                                                              {
                                                            #line 596 "CodeGeneratorPython.cpp"
  append(L"\n");
  append(L"@staticmethod\n");
  append(L"def goTo(nonterminalId, state):\n");
                                                            #line 325 "CodeGeneratorPython.cpp.template"
                                                                compressedMap2dAccessor("nonterminalId", "state", variable("gtcols").integer(),
                                                                                        2, "i", "return ", "GOTO", &variable("gtbits").integer());
                                                            #line 603 "CodeGeneratorPython.cpp"
  append(L"\n");
                                                            #line 328 "CodeGeneratorPython.cpp.template"
                                                              }

                                                              if (! variable("embedded").boolean())
                                                              {
                                                            #line 610 "CodeGeneratorPython.cpp"
  append(L"\n");
  append(L"  public String[] getExpectedTokenSet()\n");
  append(L"  {\n");
  append(L"    return getTokenSet(- state);\n");
  append(L"  }\n");
                                                            #line 337 "CodeGeneratorPython.cpp.template"
                                                              }
                                                              if (variable("trace").boolean())
                                                              {
                                                            #line 620 "CodeGeneratorPython.cpp"
  append(L"\n");
  append(L"@staticmethod\n");
  append(L"def xmlEscape(s):\n");
  append(L"  sb = \"\"\n");
  append(L"  for i in range(len(s)):\n");
  append(L"    c = s[i]\n");
  append(L"    i += 1\n");
  append(L"    if c == '<':\n");
  append(L"      sb += \"&lt;\"\n");
  append(L"    elif c == '\"':\n");
  append(L"      sb += \"&quot;\"\n");
  append(L"    elif c == '&':\n");
  append(L"      sb += \"&amp;\"\n");
  append(L"    else:\n");
  append(L"      sb += c\n");
  append(L"  return sb\n");
  append(L"\n");
  append(L"@staticmethod\n");
  append(L"def writeTrace(content):\n");
  append(L"  sys.stderr.write(content)\n");
                                                            #line 360 "CodeGeneratorPython.cpp.template"
                                                                if (variable("embedded").boolean())
                                                                {
                                                            #line 644 "CodeGeneratorPython.cpp"
  append(L"\n");
  append(L"@staticmethod\n");
  append(L"def flushTrace():\n");
  append(L"  sys.stderr.flush()\n");
                                                            #line 366 "CodeGeneratorPython.cpp.template"
                                                                }
                                                              }
                                                              if (variable("nolexer").boolean())
                                                              {
                                                            #line 654 "CodeGeneratorPython.cpp"
  append(L"\n");
  append(L"  public static int getTokenCount() {return ");
                                                            #line 371 "CodeGeneratorPython.cpp.template"
                                                                print(variable("t1").size);
                                                            #line 659 "CodeGeneratorPython.cpp"
  append(L";}\n");
  append(L"  public static String getTokenName(int code) {return code >= 0 and code < ");
                                                            #line 374 "CodeGeneratorPython.cpp.template"
                                                                print(variable("t1").size);
                                                            #line 664 "CodeGeneratorPython.cpp"
  append(L" ? ");
                                                            #line 375 "CodeGeneratorPython.cpp.template"
                                                                print(clazz);
                                                            #line 668 "CodeGeneratorPython.cpp"
  append(L".TOKEN[code] : null;}\n");
  append(L"  public static int getTokenSetCount() {return ");
                                                            #line 377 "CodeGeneratorPython.cpp.template"
                                                                print(variable("entrycount").integer());
                                                            #line 673 "CodeGeneratorPython.cpp"
  append(L";}\n");
  append(L"\n");
  append(L"func GetTokenSet(tokenSetId int) []string {");
                                                            #line 380 "CodeGeneratorPython.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 681 "CodeGeneratorPython.cpp"
  append(L"\n");
  append(L"@staticmethod\n");
  append(L"def getTokenSet(tokenSetId):");
                                                            #line 385 "CodeGeneratorPython.cpp.template"
                                                              }
                                                              if (! variable("nolexer").boolean())
                                                              {
                                                            #line 689 "CodeGeneratorPython.cpp"
  append(L"\n");
  append(L"  if tokenSetId < 0:\n");
  append(L"    s = - tokenSetId\n");
  append(L"  else:\n");
  append(L"    s = ");
                                                            #line 392 "CodeGeneratorPython.cpp.template"
                                                                print(variable("classname").string());
                                                            #line 697 "CodeGeneratorPython.cpp"
  append(L".INITIAL[tokenSetId] & ");
                                                            #line 393 "CodeGeneratorPython.cpp.template"
                                                                print(Math::powerof(2, variable("stateCodeBits").integer()) - 1);
                                                              }
                                                            #line 702 "CodeGeneratorPython.cpp"
  append(L"\n");
  append(L"  tokenSet = []\n");
  append(L"  size = 0\n");
  append(L"  for i in range(0, ");
                                                            #line 398 "CodeGeneratorPython.cpp.template"
                                                              print(variable("t1").size);
                                                            #line 709 "CodeGeneratorPython.cpp"
  append(L", 32):\n");
  append(L"    j = i\n");
  append(L"    i0 = (i >> 5) * ");
                                                            #line 401 "CodeGeneratorPython.cpp.template"
                                                              print(variable("transitionStateCount").integer());
                                                            #line 715 "CodeGeneratorPython.cpp"
  append(L" + ");
                                                            #line 402 "CodeGeneratorPython.cpp.template"
                                                              if (variable("nolexer").boolean())
                                                              {
                                                            #line 720 "CodeGeneratorPython.cpp"
  append(L"tokenSetId");
                                                            #line 404 "CodeGeneratorPython.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 726 "CodeGeneratorPython.cpp"
  append(L"s - 1");
                                                            #line 407 "CodeGeneratorPython.cpp.template"
                                                              }
                                                            #line 730 "CodeGeneratorPython.cpp"
  append(L"\n");
                                                            #line 409 "CodeGeneratorPython.cpp.template"
                                                              compressedMapAccessor(4, "i", "f = ", "EXPECTED", &variable("t0bits").integer());
                                                            #line 734 "CodeGeneratorPython.cpp"
  append(L"\n");
  append(L"    while f != 0:\n");
  append(L"      if (f & 1) != 0:\n");
  append(L"        tokenSet.append(");
                                                            #line 413 "CodeGeneratorPython.cpp.template"
                                                              print(variable("classname").string());
                                                            #line 741 "CodeGeneratorPython.cpp"
  append(L".TOKEN[j])\n");
  append(L"        size += 1\n");
  append(L"      j += 1\n");
  append(L"      f >>= 1\n");
  append(L"  return tokenSet");
                                                            #line 418 "CodeGeneratorPython.cpp.template"
                                                              generateData();
                                                              indent--;
                                                              if (! variable("embedded").boolean())
                                                              {
                                                            #line 752 "CodeGeneratorPython.cpp"
  append(L"\n");
  append(L"\n");
  append(L"  public enum Token\n");
  append(L"  {\n");
  append(L"    ");
                                                            #line 426 "CodeGeneratorPython.cpp.template"
                                                                const CGVariable &token = variable("token");
                                                                int w = (int) Format::width(token.size);
                                                                for (size_t i = 0; i < token.size; ++i)
                                                                {
                                                                  if (i)
                                                                  {
                                                            #line 765 "CodeGeneratorPython.cpp"
  append(L",\n");
  append(L"    ");
                                                            #line 433 "CodeGeneratorPython.cpp.template"
                                                                  }
                                                            #line 770 "CodeGeneratorPython.cpp"
  append(L"/* ");
                                                            #line 434 "CodeGeneratorPython.cpp.template"
                                                                  print(format.toString<char>(i, 10, w));
                                                            #line 774 "CodeGeneratorPython.cpp"
  append(L" */ ");
                                                            #line 435 "CodeGeneratorPython.cpp.template"
                                                                  print(token.string(i));
                                                                }
                                                            #line 779 "CodeGeneratorPython.cpp"
  append(L"\n");
  append(L"  };");
                                                            #line 439 "CodeGeneratorPython.cpp.template"
                                                              }
                                                              if (variable("selfTest").boolean())
                                                              {
                                                            #line 786 "CodeGeneratorPython.cpp"
  append(L"\n");
  append(L"\n");
  append(L"  private void selfTest(int set, int tokenId)\n");
  append(L"  {\n");
  append(L"    String tokenString = ");
                                                            #line 446 "CodeGeneratorPython.cpp.template"
                                                                print(clazz);
                                                            #line 794 "CodeGeneratorPython.cpp"
  append(L".TOKEN[tokenId];\n");
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
                                                            #line 478 "CodeGeneratorPython.cpp.template"
                                                              print(variable("classname").string());
                                                            #line 829 "CodeGeneratorPython.cpp"
  append(L" testee = new ");
                                                            #line 479 "CodeGeneratorPython.cpp.template"
                                                              print(variable("classname").string());
                                                            #line 833 "CodeGeneratorPython.cpp"
  append(L"();\n");
  append(L"    for (int e = 0; e < ");
                                                            #line 481 "CodeGeneratorPython.cpp.template"
                                                              print(variable("a0").size);
                                                            #line 838 "CodeGeneratorPython.cpp"
  append(L"; ++e)\n");
  append(L"    {\n");
  append(L"      int s = INITIAL[e] & ");
                                                            #line 484 "CodeGeneratorPython.cpp.template"
                                                              print(Math::powerof(2, variable("stateCodeBits").integer()) - 1);
                                                            #line 844 "CodeGeneratorPython.cpp"
  append(L";\n");
  append(L"      for (int i = 0; i < ");
                                                            #line 486 "CodeGeneratorPython.cpp.template"
                                                              print(variable("t1").size);
                                                            #line 849 "CodeGeneratorPython.cpp"
  append(L"; i += 32)\n");
  append(L"      {\n");
  append(L"        int j = i;\n");
  append(L"        int i0 = (i >> 5) * ");
                                                            #line 490 "CodeGeneratorPython.cpp.template"
                                                              print(variable("transitionStateCount").integer());
                                                            #line 856 "CodeGeneratorPython.cpp"
  append(L" + s - 1;\n");
                                                            #line 492 "CodeGeneratorPython.cpp.template"
                                                              compressedMapAccessor(8, "i", "f = ", "EXPECTED", &variable("t0bits").integer());
                                                            #line 860 "CodeGeneratorPython.cpp"
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
                                                            #line 503 "CodeGeneratorPython.cpp.template"
                                                              }
                                                            #line 874 "CodeGeneratorPython.cpp"
  append(L"\n");
                                                            #line 505 "CodeGeneratorPython.cpp.template"
                                                              if (! variable("embedded").boolean())
                                                              {
                                                            #line 879 "CodeGeneratorPython.cpp"
  append(L"}\n");
                                                            #line 508 "CodeGeneratorPython.cpp.template"
                                                              }
                                                            }

                                                            void CodeGeneratorPython::generateCompressedMap()
                                                            {
                                                            #line 887 "CodeGeneratorPython.cpp"
  append(L"\n");
  append(L"public class ");
                                                            #line 514 "CodeGeneratorPython.cpp.template"
                                                              print(variable("classname").string());
                                                            #line 892 "CodeGeneratorPython.cpp"
  append(L"\n");
  append(L"{\n");
  append(L"  public static int get(int i0)\n");
  append(L"  {\n");
  append(L"    if (i0 < 0x30000)\n");
  append(L"    {\n");
                                                            #line 521 "CodeGeneratorPython.cpp.template"
                                                              compressedMapAccessor(6, "i", "return ", "low", &variable("dtbits").integer());
                                                            #line 901 "CodeGeneratorPython.cpp"
  append(L"\n");
  append(L"    }\n");
  append(L"    else\n");
  append(L"    {");
                                                            #line 525 "CodeGeneratorPython.cpp.template"
                                                              indent += 3;
                                                              generateBinarySearch("i0", "return ", "", "HIGH", variable("rm").size);
                                                              indent -= 3;
                                                            #line 910 "CodeGeneratorPython.cpp"
  append(L"\n");
  append(L"    }\n");
  append(L"  }");
                                                            #line 530 "CodeGeneratorPython.cpp.template"
                                                              generateData();
                                                            #line 916 "CodeGeneratorPython.cpp"
  append(L"\n");
  append(L"}\n");
                                                            #line 533 "CodeGeneratorPython.cpp.template"
                                                            }

                                                            void CodeGeneratorPython::generateData()
                                                            {
                                                              size_t size = 0;
                                                              for (VarsInInsertionOrder::iterator a(varsInInsertionOrder.begin());
                                                                   a != varsInInsertionOrder.end(); ++a)
                                                                if (   a->isArray()
                                                                    && a->size > 0
                                                                    && (a->hasType(CGVariable::INTEGER) || a->hasType(CGVariable::UNSIGNED))
                                                                    && strlen(a->name) == 2)
                                                              {
                                                                size = Math::max(size, Format::width(a->size));
                                                              }
                                                              size_t limit = 120 - size - 4;
                                                              for (VarsInInsertionOrder::iterator a(varsInInsertionOrder.begin());
                                                                   a != varsInInsertionOrder.end(); ++a)
                                                                if (   a->isArray()
                                                                    && a->size > 0
                                                                    && (a->hasType(CGVariable::INTEGER) || a->hasType(CGVariable::UNSIGNED))
                                                                    && strlen(a->name) == 2)
                                                              {
                                                            #line 942 "CodeGeneratorPython.cpp"
  append(L"\n");
  append(L"\n");
                                                            #line 557 "CodeGeneratorPython.cpp.template"
                                                                print(a->longName);
                                                            #line 947 "CodeGeneratorPython.cpp"
  append(L" = [");
                                                            #line 558 "CodeGeneratorPython.cpp.template"
                                                                ++indent;
                                                                for (size_t j = 0; j < a->size; ++j)
                                                                {
                                                                  if (j == 0 || lineLength() + Format::width(a->integer(j)) + 2 > limit)
                                                                  {
                                                                    if (j)
                                                                    {
                                                            #line 957 "CodeGeneratorPython.cpp"
  append(L", ");
                                                            #line 565 "CodeGeneratorPython.cpp.template"
                                                                    }
                                                                    print(limit + 2 - lineLength(), " ");
                                                            #line 962 "CodeGeneratorPython.cpp"
  append(L"# ");
                                                            #line 567 "CodeGeneratorPython.cpp.template"
                                                                    print(format.toString<char>(j, 10, size));
                                                            #line 966 "CodeGeneratorPython.cpp"
  append(L"\n");
                                                            #line 569 "CodeGeneratorPython.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 972 "CodeGeneratorPython.cpp"
  append(L", ");
                                                            #line 572 "CodeGeneratorPython.cpp.template"
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
                                                            #line 985 "CodeGeneratorPython.cpp"
  append(L"]");
                                                            #line 582 "CodeGeneratorPython.cpp.template"
                                                                --indent;
                                                              }
                                                              for (VarsInInsertionOrder::iterator a(varsInInsertionOrder.begin());
                                                                   a != varsInInsertionOrder.end(); ++a)
                                                                if (a->isArray() && a->size > 0 && a->hasType(CGVariable::STRING) && strlen(a->name) == 2)
                                                              {
                                                            #line 994 "CodeGeneratorPython.cpp"
  append(L"\n");
  append(L"\n");
                                                            #line 590 "CodeGeneratorPython.cpp.template"
                                                                print(a->longName);
                                                            #line 999 "CodeGeneratorPython.cpp"
  append(L" = [\n");
                                                            #line 592 "CodeGeneratorPython.cpp.template"
                                                                for (size_t j = 0; j < a->size; ++j)
                                                                {
                                                                  if (j)
                                                                  {
                                                            #line 1006 "CodeGeneratorPython.cpp"
  append(L",\n");
                                                            #line 597 "CodeGeneratorPython.cpp.template"
                                                                  }
                                                            #line 1010 "CodeGeneratorPython.cpp"
  append(L"    \"");
                                                            #line 598 "CodeGeneratorPython.cpp.template"
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
                                                            #line 1025 "CodeGeneratorPython.cpp"
  append(L"\"");
                                                            #line 610 "CodeGeneratorPython.cpp.template"
                                                                }
                                                            #line 1029 "CodeGeneratorPython.cpp"
  append(L"]");
                                                            #line 611 "CodeGeneratorPython.cpp.template"
                                                              }
                                                            }

                                                            void CodeGeneratorPython::generateBinarySearch(const char *input, const char *outputPrefix, const char *outputSuffix, const char *map, size_t size)
                                                            {
                                                            #line 1037 "CodeGeneratorPython.cpp"
  append(L"\n");
  append(L"int lo = 0, hi = ");
                                                            #line 617 "CodeGeneratorPython.cpp.template"
                                                              print(size / 3 - 1);
                                                            #line 1042 "CodeGeneratorPython.cpp"
  append(L";\n");
  append(L"for (int m = ");
                                                            #line 619 "CodeGeneratorPython.cpp.template"
                                                              print((size / 3) >> 1);
                                                            #line 1047 "CodeGeneratorPython.cpp"
  append(L"; ; m = (hi + lo) >> 1)\n");
  append(L"{\n");
  append(L"  if (");
                                                            #line 622 "CodeGeneratorPython.cpp.template"
                                                              print(map);
                                                            #line 1053 "CodeGeneratorPython.cpp"
  append(L"[m] > ");
                                                            #line 623 "CodeGeneratorPython.cpp.template"
                                                              print(input);
                                                            #line 1057 "CodeGeneratorPython.cpp"
  append(L") {hi = m - 1;}\n");
  append(L"  elif ");
                                                            #line 625 "CodeGeneratorPython.cpp.template"
                                                              print(map);
                                                            #line 1062 "CodeGeneratorPython.cpp"
  append(L"[");
                                                            #line 626 "CodeGeneratorPython.cpp.template"
                                                              print(size / 3);
                                                            #line 1066 "CodeGeneratorPython.cpp"
  append(L" + m] < ");
                                                            #line 627 "CodeGeneratorPython.cpp.template"
                                                              print(input);
                                                            #line 1070 "CodeGeneratorPython.cpp"
  append(L":\n");
  append(L"    lo = m + 1\n");
  append(L"  else:");
                                                            #line 630 "CodeGeneratorPython.cpp.template"
                                                              print(outputPrefix);
                                                              print(map);
                                                            #line 1077 "CodeGeneratorPython.cpp"
  append(L"[");
                                                            #line 632 "CodeGeneratorPython.cpp.template"
                                                              print(size / 3 * 2);
                                                            #line 1081 "CodeGeneratorPython.cpp"
  append(L" + m]");
                                                            #line 633 "CodeGeneratorPython.cpp.template"
                                                              print(outputSuffix);
                                                            #line 1085 "CodeGeneratorPython.cpp"
  append(L";}\n");
  append(L"  if (lo > hi) {");
                                                            #line 635 "CodeGeneratorPython.cpp.template"
                                                              print(outputPrefix);
                                                            #line 1090 "CodeGeneratorPython.cpp"
  append(L"0");
                                                            #line 636 "CodeGeneratorPython.cpp.template"
                                                              print(outputSuffix);
                                                            #line 1094 "CodeGeneratorPython.cpp"
  append(L";}\n");
  append(L"}");
                                                            #line 638 "CodeGeneratorPython.cpp.template"
                                                            }

// End
