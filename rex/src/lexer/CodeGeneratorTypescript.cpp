// This file was generated on Tue Oct 20, 2026 19:55 (UTC+02) by REx v6.3-SNAPSHOT which is Copyright (c) 1979-2026 by Gunther Rademacher <grd@gmx.net>
// REx command line: CodeGeneratorTypescript.cpp.template
                                                            #line 1 "CodeGeneratorTypescript.cpp.template"
                                                            #include "../common/Memory.hpp"

                                                            #include "CodeGenerator.hpp"

                                                            void CodeGeneratorTypescript::generateInstanceCode()
                                                            {
                                                              isTypescript = true;
                                                              if (! variable("append").boolean() && ! variable("embedded").boolean())
                                                              {
                                                                if (*variable("package").string())
                                                                {
                                                            #line 16 "CodeGeneratorTypescript.cpp"
  append(L"package ");
                                                            #line 12 "CodeGeneratorTypescript.cpp.template"
                                                                  print(variable("package").string());
                                                            #line 20 "CodeGeneratorTypescript.cpp"
  append(L";\n");
  append(L"\n");
                                                            #line 15 "CodeGeneratorTypescript.cpp.template"
                                                                }
                                                            #line 25 "CodeGeneratorTypescript.cpp"
  append(L"function ");
                                                            #line 16 "CodeGeneratorTypescript.cpp.template"
                                                                print(variable("classname").string());
                                                            #line 29 "CodeGeneratorTypescript.cpp"
  append(L"()\n");
  append(L"{\n");
                                                            #line 19 "CodeGeneratorTypescript.cpp.template"
                                                              }
                                                              if (variable("tree").boolean())
                                                              {
                                                              }
                                                              if (variable("trace").boolean())
                                                              {
                                                              }
                                                              if (! variable("embedded").boolean())
                                                              {
                                                            #line 42 "CodeGeneratorTypescript.cpp"
  append(L"\n");
  append(L"  init(string)\n");
  append(L"  {\n");
  append(L"    input = string;\n");
  append(L"    size = string.length;\n");
  append(L"    end = 0;\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  match(tokenSetId, string)\n");
  append(L"  {\n");
  append(L"    init(string);\n");
  append(L"    return match(tokenSetId);\n");
  append(L"  }\n");
  append(L"\n");
                                                            #line 42 "CodeGeneratorTypescript.cpp.template"
                                                              }
                                                              if (! variable("useGlr").boolean())
                                                              {
                                                            #line 61 "CodeGeneratorTypescript.cpp"
  append(L"  private input!: string;");
                                                            #line 45 "CodeGeneratorTypescript.cpp.template"
                                                                if (! variable("nolexer").boolean())
                                                                {
                                                            #line 66 "CodeGeneratorTypescript.cpp"
  append(L"\n");
  append(L"  private size!: number;");
                                                            #line 48 "CodeGeneratorTypescript.cpp.template"
                                                                }
                                                              }
                                                            #line 72 "CodeGeneratorTypescript.cpp"
  append(L"\n");
  append(L"  private begin!: number;\n");
  append(L"  private end!: number;");
                                                            #line 52 "CodeGeneratorTypescript.cpp.template"
                                                              if (variable("nolexer").boolean())
                                                              {
                                                            #line 79 "CodeGeneratorTypescript.cpp"
  append(L"\n");
  append(L"  private lexer;\n");
  append(L"  private token = {};");
                                                            #line 56 "CodeGeneratorTypescript.cpp.template"
                                                              }
                                                              if (! variable("embedded").boolean())
                                                              {
                                                            #line 87 "CodeGeneratorTypescript.cpp"
  append(L"\n");
  append(L"  private state!: number;");
                                                            #line 60 "CodeGeneratorTypescript.cpp.template"
                                                              }
                                                            #line 92 "CodeGeneratorTypescript.cpp"
  append(L"\n");
                                                            #line 62 "CodeGeneratorTypescript.cpp.template"
                                                              if (variable("tables").boolean())
                                                              {
                                                            #line 97 "CodeGeneratorTypescript.cpp"
  append(L"\n");
  append(L"  private predict(dpi: number): number");
                                                            #line 65 "CodeGeneratorTypescript.cpp.template"
                                                                predict();
                                                              }
                                                              const char *instancePrefix = variable("useGlr").boolean() ? "this.parser." : "this.";
                                                            #line 104 "CodeGeneratorTypescript.cpp"
  append(L"\n");
  append(L"  private match(tokenSetId: number): number\n");
  append(L"  {");
                                                            #line 70 "CodeGeneratorTypescript.cpp.template"
                                                              if (variable("nolexer").boolean())
                                                              {
                                                            #line 111 "CodeGeneratorTypescript.cpp"
  append(L"\n");
  append(L"    token.begin = this.end;\n");
  append(L"    this.lexer.match(tokenSetId, token);\n");
  append(L"    this.begin = token.begin;\n");
  append(L"    this.end = token.end;\n");
  append(L"    return token.code >= 0\n");
  append(L"         ? token.code\n");
  append(L"         : error(begin, end, - tokenSetId, -1, -1);");
                                                            #line 79 "CodeGeneratorTypescript.cpp.template"
                                                              }
                                                              else
                                                              {
                                                                if (variable("trace").boolean())
                                                                {
                                                            #line 126 "CodeGeneratorTypescript.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 85 "CodeGeneratorTypescript.cpp.template"
                                                                  print(instancePrefix);
                                                            #line 131 "CodeGeneratorTypescript.cpp"
  append(L"writeTrace(\"  <tokenize ");
                                                            #line 86 "CodeGeneratorTypescript.cpp.template"
                                                                  if (variable("useGlr").boolean())
                                                                  {
                                                            #line 136 "CodeGeneratorTypescript.cpp"
  append(L"thread=\\\"\" + this.id + \"\\\" ");
                                                            #line 88 "CodeGeneratorTypescript.cpp.template"
                                                                  }
                                                            #line 140 "CodeGeneratorTypescript.cpp"
  append(L"tokenset=\\\"\" + tokenSetId + \"\\\">\\n\");\n");
                                                            #line 90 "CodeGeneratorTypescript.cpp.template"
                                                                }
                                                                int lookahead = variable("maxcontextlength").integer();
                                                                bool hasFixedTokenLength = variable("hasfixedtokenlength").boolean();
                                                                if (lookahead)
                                                                {
                                                            #line 148 "CodeGeneratorTypescript.cpp"
  append(L"\n");
  append(L"    var nonbmp = false;");
                                                            #line 96 "CodeGeneratorTypescript.cpp.template"
                                                                }
                                                            #line 153 "CodeGeneratorTypescript.cpp"
  append(L"\n");
  append(L"    this.begin = this.end;\n");
  append(L"    var current = this.end;\n");
  append(L"    var result = Parser.INITIAL[tokenSetId];");
                                                            #line 100 "CodeGeneratorTypescript.cpp.template"
                                                                if (variable("embedded").boolean())
                                                                {
                                                            #line 161 "CodeGeneratorTypescript.cpp"
  append(L"\n");
  append(L"    var state = 0;");
                                                            #line 103 "CodeGeneratorTypescript.cpp.template"
                                                                }
                                                                if (variable("trace").boolean())
                                                                {
                                                            #line 168 "CodeGeneratorTypescript.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 107 "CodeGeneratorTypescript.cpp.template"
                                                                  print(instancePrefix);
                                                            #line 173 "CodeGeneratorTypescript.cpp"
  append(L"writeTrace(\"    <next state=\\\"\" + (result & ");
                                                            #line 108 "CodeGeneratorTypescript.cpp.template"
                                                                  print(Math::powerof(2, variable("stateCodeBits").integer()) - 1);
                                                            #line 177 "CodeGeneratorTypescript.cpp"
  append(L") + \"\\\"\");");
                                                            #line 109 "CodeGeneratorTypescript.cpp.template"
                                                                }
                                                            #line 181 "CodeGeneratorTypescript.cpp"
  append(L"\n");
  append(L"    for (var code = result & ");
                                                            #line 111 "CodeGeneratorTypescript.cpp.template"
                                                                print(Math::powerof(2, variable("stateCodeBits").integer()) - 1);
                                                            #line 186 "CodeGeneratorTypescript.cpp"
  append(L"; code != 0; )\n");
  append(L"    {\n");
  append(L"      var charclass: number;\n");
  append(L"      var c0 = current < ");
                                                            #line 115 "CodeGeneratorTypescript.cpp.template"
                                                                print(instancePrefix);
                                                            #line 193 "CodeGeneratorTypescript.cpp"
  append(L"size ? ");
                                                            #line 116 "CodeGeneratorTypescript.cpp.template"
                                                                print(instancePrefix);
                                                            #line 197 "CodeGeneratorTypescript.cpp"
  append(L"input.charCodeAt(current) : 0;");
                                                            #line 118 "CodeGeneratorTypescript.cpp.template"
                                                                if (variable("trace").boolean())
                                                                {
                                                            #line 202 "CodeGeneratorTypescript.cpp"
  append(L"\n");
  append(L"      ");
                                                            #line 121 "CodeGeneratorTypescript.cpp.template"
                                                                  print(instancePrefix);
                                                            #line 207 "CodeGeneratorTypescript.cpp"
  append(L"writeTrace(\" offset=\\\"\" + current + \"\\\"\");");
                                                            #line 122 "CodeGeneratorTypescript.cpp.template"
                                                                }
                                                            #line 211 "CodeGeneratorTypescript.cpp"
  append(L"\n");
  append(L"      ++current;\n");
  append(L"      if (c0 < ");
                                                            #line 125 "CodeGeneratorTypescript.cpp.template"
                                                                print(format.toString<char>(variable("simplifiedCodeMap").integer(), 16, 0, 0, "0x", "0123456789abcdef"));
                                                            #line 217 "CodeGeneratorTypescript.cpp"
  append(L")\n");
  append(L"      {");
                                                            #line 127 "CodeGeneratorTypescript.cpp.template"
                                                                if (variable("trace").boolean())
                                                                {
                                                            #line 223 "CodeGeneratorTypescript.cpp"
  append(L"\n");
  append(L"        if (c0 >= 32 && c0 <= 126)\n");
  append(L"          ");
                                                            #line 131 "CodeGeneratorTypescript.cpp.template"
                                                                  print(instancePrefix);
                                                            #line 229 "CodeGeneratorTypescript.cpp"
  append(L"writeTrace(\" char=\\\"\" + Parser.xmlEscape(");
                                                            #line 132 "CodeGeneratorTypescript.cpp.template"
                                                                  print(instancePrefix);
                                                            #line 233 "CodeGeneratorTypescript.cpp"
  append(L"input.charAt(current - 1)) + \"\\\"\");");
                                                            #line 134 "CodeGeneratorTypescript.cpp.template"
                                                                }
                                                            #line 237 "CodeGeneratorTypescript.cpp"
  append(L"\n");
  append(L"        charclass = Parser.MAP0[c0];\n");
  append(L"      }\n");
  append(L"      else if (c0 < ");
                                                            #line 138 "CodeGeneratorTypescript.cpp.template"
                                                                print(format.toString<char>(variable("uncompressedMapSize").integer(), 16, 0, 0, "0x", "0123456789abcdef"));
                                                            #line 244 "CodeGeneratorTypescript.cpp"
  append(L")\n");
  append(L"      {\n");
                                                            #line 141 "CodeGeneratorTypescript.cpp.template"
                                                                compressedMapAccessor(8, "c", "charclass = ", "MAP1", &variable("m1bits").integer());
                                                            #line 249 "CodeGeneratorTypescript.cpp"
  append(L"\n");
  append(L"      }\n");
  append(L"      else\n");
  append(L"      {");
                                                            #line 145 "CodeGeneratorTypescript.cpp.template"
                                                                if (variable("m2").size == 0)
                                                                {
                                                            #line 257 "CodeGeneratorTypescript.cpp"
  append(L"\n");
  append(L"        charclass = 0;");
                                                            #line 148 "CodeGeneratorTypescript.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 264 "CodeGeneratorTypescript.cpp"
  append(L"\n");
  append(L"        if (");
                                                            #line 152 "CodeGeneratorTypescript.cpp.template"
                                                                  if (variable("uncompressedMapSize").integer() != 0xd800)
                                                                  {
                                                            #line 270 "CodeGeneratorTypescript.cpp"
  append(L"c0 >= 0xd800 && ");
                                                            #line 154 "CodeGeneratorTypescript.cpp.template"
                                                                  }
                                                            #line 274 "CodeGeneratorTypescript.cpp"
  append(L"c0 < 0xdc00)\n");
  append(L"        {\n");
  append(L"          var c1: number = current < ");
                                                            #line 157 "CodeGeneratorTypescript.cpp.template"
                                                                  print(instancePrefix);
                                                            #line 280 "CodeGeneratorTypescript.cpp"
  append(L"size ? ");
                                                            #line 158 "CodeGeneratorTypescript.cpp.template"
                                                                  print(instancePrefix);
                                                            #line 284 "CodeGeneratorTypescript.cpp"
  append(L"input.charCodeAt(current) : 0;\n");
  append(L"          if (c1 >= 0xdc00 && c1 < 0xe000)\n");
  append(L"          {\n");
  append(L"            ++current;\n");
  append(L"            c0 = ((c0 & 0x3ff) << 10) + (c1 & 0x3ff) + 0x10000;");
                                                            #line 163 "CodeGeneratorTypescript.cpp.template"
                                                                  if (lookahead)
                                                                  {
                                                            #line 293 "CodeGeneratorTypescript.cpp"
  append(L"\n");
  append(L"            nonbmp = true;");
                                                            #line 166 "CodeGeneratorTypescript.cpp.template"
                                                                  }
                                                            #line 298 "CodeGeneratorTypescript.cpp"
  append(L"\n");
  append(L"          }\n");
  append(L"        }\n");
  append(L"\n");
  append(L"        var lo = 0, hi = ");
                                                            #line 171 "CodeGeneratorTypescript.cpp.template"
                                                                  print(variable("m2").size / 3 - 1);
                                                            #line 306 "CodeGeneratorTypescript.cpp"
  append(L";\n");
  append(L"        for (var m = ");
                                                            #line 173 "CodeGeneratorTypescript.cpp.template"
                                                                  print((variable("m2").size / 3) >> 1);
                                                            #line 311 "CodeGeneratorTypescript.cpp"
  append(L"; ; m = (hi + lo) >> 1)\n");
  append(L"        {\n");
  append(L"          if (Parser.MAP2[m] > c0) hi = m - 1;\n");
  append(L"          else if (Parser.MAP2[");
                                                            #line 177 "CodeGeneratorTypescript.cpp.template"
                                                                  print(variable("m2").size / 3);
                                                            #line 318 "CodeGeneratorTypescript.cpp"
  append(L" + m] < c0) lo = m + 1;\n");
  append(L"          else {charclass = Parser.MAP2[");
                                                            #line 179 "CodeGeneratorTypescript.cpp.template"
                                                                  print(variable("m2").size / 3 * 2);
                                                            #line 323 "CodeGeneratorTypescript.cpp"
  append(L" + m]; break;}\n");
  append(L"          if (lo > hi) {charclass = 0; break;}\n");
  append(L"        }");
                                                            #line 182 "CodeGeneratorTypescript.cpp.template"
                                                                }
                                                            #line 329 "CodeGeneratorTypescript.cpp"
  append(L"\n");
  append(L"      }");
                                                            #line 184 "CodeGeneratorTypescript.cpp.template"
                                                                if (variable("trace").boolean())
                                                                {
                                                            #line 335 "CodeGeneratorTypescript.cpp"
  append(L"\n");
  append(L"      ");
                                                            #line 187 "CodeGeneratorTypescript.cpp.template"
                                                                  print(instancePrefix);
                                                            #line 340 "CodeGeneratorTypescript.cpp"
  append(L"writeTrace(\" codepoint=\\\"\" + c0 + \"\\\" class=\\\"\" + charclass + \"\\\"\");");
                                                            #line 189 "CodeGeneratorTypescript.cpp.template"
                                                                }
                                                            #line 344 "CodeGeneratorTypescript.cpp"
  append(L"\n");
  append(L"\n");
  append(L"      state = code;\n");
                                                            #line 193 "CodeGeneratorTypescript.cpp.template"
                                                                compressedMap2dAccessor("code - 1", "charclass", variable("a1cols").integer(),
                                                                                           6, "i", "code = ", "TRANSITION", &variable("a1bits").integer());
                                                            #line 351 "CodeGeneratorTypescript.cpp"
  append(L"\n");
  append(L"\n");
  append(L"      if (code > ");
                                                            #line 197 "CodeGeneratorTypescript.cpp.template"
                                                                print(Math::powerof(2, variable("stateCodeBits").integer()) - 1);
                                                            #line 357 "CodeGeneratorTypescript.cpp"
  append(L")\n");
  append(L"      {\n");
  append(L"        result = code;");
                                                            #line 200 "CodeGeneratorTypescript.cpp.template"
                                                                if (variable("trace").boolean())
                                                                {
                                                            #line 364 "CodeGeneratorTypescript.cpp"
  append(L"\n");
  append(L"        ");
                                                            #line 203 "CodeGeneratorTypescript.cpp.template"
                                                                  print(instancePrefix);
                                                            #line 369 "CodeGeneratorTypescript.cpp"
  append(L"writeTrace(\" result=\\\"\" + Parser.xmlEscape(Parser.TOKEN[((result >> ");
                                                            #line 205 "CodeGeneratorTypescript.cpp.template"
                                                                  print(variable("stateCodeBits").integer());
                                                            #line 373 "CodeGeneratorTypescript.cpp"
  append(L") & ");
                                                            #line 206 "CodeGeneratorTypescript.cpp.template"
                                                                  print(Math::powerof(2, variable("tokencodeBits").integer()) - 1);
                                                            #line 377 "CodeGeneratorTypescript.cpp"
  append(L") - 1]) + \"\\\"\");");
                                                            #line 207 "CodeGeneratorTypescript.cpp.template"
                                                                  if (lookahead || hasFixedTokenLength)
                                                                  {
                                                                    int contextOffset = variable("stateCodeBits").integer()
                                                                                      + variable("tokencodeBits").integer();
                                                                    int sizeOffset = contextOffset
                                                                                   + (hasFixedTokenLength ? 1 : 0);
                                                                    if (hasFixedTokenLength)
                                                                    {
                                                            #line 388 "CodeGeneratorTypescript.cpp"
  append(L"\n");
  append(L"        if ((result & ");
                                                            #line 216 "CodeGeneratorTypescript.cpp.template"
                                                                      print(Math::powerof(2, contextOffset));
                                                            #line 393 "CodeGeneratorTypescript.cpp"
  append(L") > 0)\n");
  append(L"        {\n");
  append(L"          ");
                                                            #line 219 "CodeGeneratorTypescript.cpp.template"
                                                                      print(instancePrefix);
                                                            #line 399 "CodeGeneratorTypescript.cpp"
  append(L"writeTrace(\" token-size=\\\"\" + (result >> ");
                                                            #line 220 "CodeGeneratorTypescript.cpp.template"
                                                                      print(sizeOffset);
                                                            #line 403 "CodeGeneratorTypescript.cpp"
  append(L") + \"\\\"\");\n");
  append(L"        }\n");
  append(L"        else ");
                                                            #line 223 "CodeGeneratorTypescript.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 411 "CodeGeneratorTypescript.cpp"
  append(L"\n");
  append(L"        ");
                                                            #line 227 "CodeGeneratorTypescript.cpp.template"
                                                                    }
                                                            #line 416 "CodeGeneratorTypescript.cpp"
  append(L"if ((result >> ");
                                                            #line 228 "CodeGeneratorTypescript.cpp.template"
                                                                    print(sizeOffset);
                                                            #line 420 "CodeGeneratorTypescript.cpp"
  append(L") > 0)\n");
  append(L"        {\n");
  append(L"          ");
                                                            #line 231 "CodeGeneratorTypescript.cpp.template"
                                                                    print(instancePrefix);
                                                            #line 426 "CodeGeneratorTypescript.cpp"
  append(L"writeTrace(\" trailing-context-size=\\\"\" + (result >> ");
                                                            #line 232 "CodeGeneratorTypescript.cpp.template"
                                                                    print(sizeOffset);
                                                            #line 430 "CodeGeneratorTypescript.cpp"
  append(L") + \"\\\"\");\n");
  append(L"        }");
                                                            #line 234 "CodeGeneratorTypescript.cpp.template"
                                                                  }
                                                                }
                                                            #line 436 "CodeGeneratorTypescript.cpp"
  append(L"\n");
  append(L"        code &= ");
                                                            #line 237 "CodeGeneratorTypescript.cpp.template"
                                                                print(Math::powerof(2, variable("stateCodeBits").integer()) - 1);
                                                            #line 441 "CodeGeneratorTypescript.cpp"
  append(L";\n");
  append(L"        this.end = current;\n");
  append(L"      }");
                                                            #line 240 "CodeGeneratorTypescript.cpp.template"
                                                                if (variable("trace").boolean())
                                                                {
                                                            #line 448 "CodeGeneratorTypescript.cpp"
  append(L"\n");
  append(L"      ");
                                                            #line 243 "CodeGeneratorTypescript.cpp.template"
                                                                  print(instancePrefix);
                                                            #line 453 "CodeGeneratorTypescript.cpp"
  append(L"writeTrace(\"/>\\n\");\n");
  append(L"      if (code != 0)\n");
  append(L"      {\n");
  append(L"        ");
                                                            #line 247 "CodeGeneratorTypescript.cpp.template"
                                                                  print(instancePrefix);
                                                            #line 460 "CodeGeneratorTypescript.cpp"
  append(L"writeTrace(\"    <next state=\\\"\" + code + \"\\\"\");\n");
  append(L"      }");
                                                            #line 249 "CodeGeneratorTypescript.cpp.template"
                                                                }
                                                            #line 465 "CodeGeneratorTypescript.cpp"
  append(L"\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    result >>= ");
                                                            #line 253 "CodeGeneratorTypescript.cpp.template"
                                                                print(variable("stateCodeBits").integer());
                                                            #line 472 "CodeGeneratorTypescript.cpp"
  append(L";\n");
  append(L"    if (result == 0)\n");
  append(L"    {\n");
  append(L"      this.end = current - 1;\n");
  append(L"      var c1: number = this.end < ");
                                                            #line 258 "CodeGeneratorTypescript.cpp.template"
                                                                print(instancePrefix);
                                                            #line 480 "CodeGeneratorTypescript.cpp"
  append(L"size ? ");
                                                            #line 259 "CodeGeneratorTypescript.cpp.template"
                                                                print(instancePrefix);
                                                            #line 484 "CodeGeneratorTypescript.cpp"
  append(L"input.charCodeAt(this.end) : 0;\n");
  append(L"      if (c1 >= 0xdc00 && c1 < 0xe000) --this.end;");
                                                            #line 261 "CodeGeneratorTypescript.cpp.template"
                                                                if (variable("trace").boolean())
                                                                {
                                                            #line 490 "CodeGeneratorTypescript.cpp"
  append(L"\n");
  append(L"      ");
                                                            #line 264 "CodeGeneratorTypescript.cpp.template"
                                                                  print(instancePrefix);
                                                            #line 495 "CodeGeneratorTypescript.cpp"
  append(L"writeTrace(\"    <fail begin=\\\"\" + this.begin + \"\\\" end=\\\"\" + this.end + \"\\\" state=\\\"\" + state + \"\\\"/>\\n\");\n");
  append(L"      ");
                                                            #line 266 "CodeGeneratorTypescript.cpp.template"
                                                                  print(instancePrefix);
                                                            #line 500 "CodeGeneratorTypescript.cpp"
  append(L"writeTrace(\"  </tokenize>\\n\");");
                                                            #line 267 "CodeGeneratorTypescript.cpp.template"
                                                                }
                                                                if (! variable("embedded").boolean())
                                                                {
                                                            #line 506 "CodeGeneratorTypescript.cpp"
  append(L"\n");
  append(L"      return -1;");
                                                            #line 271 "CodeGeneratorTypescript.cpp.template"
                                                                }
                                                                else if (variable("useGlr").boolean())
                                                                {
                                                            #line 513 "CodeGeneratorTypescript.cpp"
  append(L"\n");
  append(L"      this.end = this.begin;\n");
  append(L"      return -1;");
                                                            #line 276 "CodeGeneratorTypescript.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 521 "CodeGeneratorTypescript.cpp"
  append(L"\n");
  append(L"      ");
                                                            #line 280 "CodeGeneratorTypescript.cpp.template"
                                                                  if (variable("nothrow").boolean())
                                                                  {
                                                            #line 527 "CodeGeneratorTypescript.cpp"
  append(L"return ");
                                                            #line 282 "CodeGeneratorTypescript.cpp.template"
                                                                  }
                                                            #line 531 "CodeGeneratorTypescript.cpp"
  append(L"this.error(this.begin, this.end, state, -1, -1);");
                                                            #line 283 "CodeGeneratorTypescript.cpp.template"
                                                                }
                                                            #line 535 "CodeGeneratorTypescript.cpp"
  append(L"\n");
  append(L"    }\n");
                                                            #line 286 "CodeGeneratorTypescript.cpp.template"
                                                                int lowBits = variable("tokencodeBits").integer();
                                                                if (hasFixedTokenLength && ! lookahead)
                                                                {
                                                            #line 542 "CodeGeneratorTypescript.cpp"
  append(L"\n");
  append(L"    if ((result & ");
                                                            #line 290 "CodeGeneratorTypescript.cpp.template"
                                                                  print(Math::powerof(2, lowBits));
                                                                  ++lowBits;
                                                            #line 548 "CodeGeneratorTypescript.cpp"
  append(L") != 0)\n");
  append(L"    {\n");
  append(L"      this.end = this.begin;\n");
  append(L"    }\n");
                                                            #line 296 "CodeGeneratorTypescript.cpp.template"
                                                                }
                                                                else
                                                                {
                                                                  if (hasFixedTokenLength)
                                                                  {
                                                            #line 559 "CodeGeneratorTypescript.cpp"
  append(L"\n");
  append(L"    if ((result & ");
                                                            #line 302 "CodeGeneratorTypescript.cpp.template"
                                                                    print(Math::powerof(2, lowBits));
                                                                    ++lowBits;
                                                            #line 565 "CodeGeneratorTypescript.cpp"
  append(L") != 0)\n");
  append(L"    {\n");
  append(L"      this.end = this.begin;\n");
  append(L"      if (nonbmp)\n");
  append(L"      {\n");
  append(L"        for (var i = result >> ");
                                                            #line 309 "CodeGeneratorTypescript.cpp.template"
                                                                    print(lowBits);
                                                            #line 574 "CodeGeneratorTypescript.cpp"
  append(L"; i > 0; --i)\n");
  append(L"        {\n");
  append(L"          var c1: number = this.end < ");
                                                            #line 312 "CodeGeneratorTypescript.cpp.template"
                                                                    print(instancePrefix);
                                                            #line 580 "CodeGeneratorTypescript.cpp"
  append(L"size ? ");
                                                            #line 313 "CodeGeneratorTypescript.cpp.template"
                                                                    print(instancePrefix);
                                                            #line 584 "CodeGeneratorTypescript.cpp"
  append(L"input.charCodeAt(this.end++) : 0;\n");
  append(L"          if (c1 >= 0xd800 && c1 < 0xdc00) ++this.end;\n");
  append(L"        }\n");
  append(L"      }\n");
  append(L"      else\n");
  append(L"      {\n");
  append(L"        this.end += (result >> ");
                                                            #line 320 "CodeGeneratorTypescript.cpp.template"
                                                                    print(lowBits);
                                                            #line 594 "CodeGeneratorTypescript.cpp"
  append(L");\n");
  append(L"      }\n");
  append(L"    }\n");
  append(L"    else\n");
  append(L"    {");
                                                            #line 325 "CodeGeneratorTypescript.cpp.template"
                                                                    ++indent;
                                                                  }
                                                                  if (lookahead)
                                                                  {
                                                            #line 605 "CodeGeneratorTypescript.cpp"
  append(L"\n");
  append(L"    if (nonbmp)\n");
  append(L"    {\n");
  append(L"      for (var i = result >> ");
                                                            #line 332 "CodeGeneratorTypescript.cpp.template"
                                                                    print(lowBits);
                                                            #line 612 "CodeGeneratorTypescript.cpp"
  append(L"; i > 0; --i)\n");
  append(L"      {\n");
  append(L"        --this.end;\n");
  append(L"        var c1: number = this.end < ");
                                                            #line 336 "CodeGeneratorTypescript.cpp.template"
                                                                    print(instancePrefix);
                                                            #line 619 "CodeGeneratorTypescript.cpp"
  append(L"size ? ");
                                                            #line 337 "CodeGeneratorTypescript.cpp.template"
                                                                    print(instancePrefix);
                                                            #line 623 "CodeGeneratorTypescript.cpp"
  append(L"input.charCodeAt(this.end) : 0;\n");
  append(L"        if (c1 >= 0xdc00 && c1 < 0xe000) --this.end;\n");
  append(L"      }\n");
  append(L"    }\n");
  append(L"    else\n");
  append(L"    {\n");
  append(L"      this.end -= result >> ");
                                                            #line 344 "CodeGeneratorTypescript.cpp.template"
                                                                    print(lowBits);
                                                            #line 633 "CodeGeneratorTypescript.cpp"
  append(L";\n");
  append(L"    }\n");
                                                            #line 347 "CodeGeneratorTypescript.cpp.template"
                                                                  }
                                                                  if (hasFixedTokenLength)
                                                                  {
                                                                    --indent;
                                                            #line 641 "CodeGeneratorTypescript.cpp"
  append(L"  }\n");
                                                            #line 352 "CodeGeneratorTypescript.cpp.template"
                                                                  }
                                                                }
                                                            #line 646 "CodeGeneratorTypescript.cpp"
  append(L"\n");
  append(L"    if (this.end > ");
                                                            #line 355 "CodeGeneratorTypescript.cpp.template"
                                                                print(instancePrefix);
                                                            #line 651 "CodeGeneratorTypescript.cpp"
  append(L"size) this.end = ");
                                                            #line 356 "CodeGeneratorTypescript.cpp.template"
                                                                print(instancePrefix);
                                                            #line 655 "CodeGeneratorTypescript.cpp"
  append(L"size;");
                                                            #line 357 "CodeGeneratorTypescript.cpp.template"
                                                                if (variable("trace").boolean())
                                                                {
                                                            #line 660 "CodeGeneratorTypescript.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 360 "CodeGeneratorTypescript.cpp.template"
                                                                  print(instancePrefix);
                                                            #line 665 "CodeGeneratorTypescript.cpp"
  append(L"writeTrace(\"    <done result=\\\"\" + Parser.xmlEscape(Parser.TOKEN[(result & ");
                                                            #line 362 "CodeGeneratorTypescript.cpp.template"
                                                                  print(Math::powerof(2, variable("tokencodeBits").integer()) - 1);
                                                            #line 669 "CodeGeneratorTypescript.cpp"
  append(L") - 1]) + \"\\\" begin=\\\"\" + this.begin + \"\\\" end=\\\"\" + this.end + \"\\\"/>\\n\");\n");
  append(L"    ");
                                                            #line 364 "CodeGeneratorTypescript.cpp.template"
                                                                  print(instancePrefix);
                                                            #line 674 "CodeGeneratorTypescript.cpp"
  append(L"writeTrace(\"  </tokenize>\\n\");");
                                                            #line 365 "CodeGeneratorTypescript.cpp.template"
                                                                }
                                                            #line 678 "CodeGeneratorTypescript.cpp"
  append(L"\n");
  append(L"    return (result & ");
                                                            #line 367 "CodeGeneratorTypescript.cpp.template"
                                                                print(Math::powerof(2, variable("tokencodeBits").integer()) - 1);
                                                            #line 683 "CodeGeneratorTypescript.cpp"
  append(L") - 1;");
                                                            #line 368 "CodeGeneratorTypescript.cpp.template"
                                                              }
                                                            #line 687 "CodeGeneratorTypescript.cpp"
  append(L"\n");
  append(L"  }\n");
                                                            #line 371 "CodeGeneratorTypescript.cpp.template"
                                                            }

                                                            void CodeGeneratorTypescript::generateStaticCode()
                                                            {
                                                              if (defined("gtbits"))
                                                              {
                                                            #line 697 "CodeGeneratorTypescript.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 378 "CodeGeneratorTypescript.cpp.template"
                                                                if (variable("useGlr").boolean())
                                                                {
                                                            #line 703 "CodeGeneratorTypescript.cpp"
  append(L"public");
                                                            #line 380 "CodeGeneratorTypescript.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 709 "CodeGeneratorTypescript.cpp"
  append(L"private");
                                                            #line 383 "CodeGeneratorTypescript.cpp.template"
                                                                }
                                                            #line 713 "CodeGeneratorTypescript.cpp"
  append(L" static goTo(nonterminal: number, state: number): number\n");
  append(L"  {\n");
                                                            #line 386 "CodeGeneratorTypescript.cpp.template"
                                                                compressedMap2dAccessor("nonterminal", "state", variable("gtcols").integer(),
                                                                                           4, "i", "return ", "GOTO", &variable("gtbits").integer());
                                                            #line 719 "CodeGeneratorTypescript.cpp"
  append(L"\n");
  append(L"  }\n");
                                                            #line 390 "CodeGeneratorTypescript.cpp.template"
                                                              }
                                                              if (! variable("embedded").boolean())
                                                              {
                                                            #line 726 "CodeGeneratorTypescript.cpp"
  append(L"\n");
  append(L"  getExpectedTokenSet()\n");
  append(L"  {\n");
  append(L"    return getTokenSet(- state);\n");
  append(L"  }\n");
                                                            #line 398 "CodeGeneratorTypescript.cpp.template"
                                                              }
                                                              if (variable("trace").boolean())
                                                              {
                                                            #line 736 "CodeGeneratorTypescript.cpp"
  append(L"\n");
  append(L"  static xmlEscape(s: string): string\n");
  append(L"  {\n");
  append(L"    var result = \"\";\n");
  append(L"    for (var i = 0; i < s.length; ++i)\n");
  append(L"    {\n");
  append(L"      var c = s.charAt(i);\n");
  append(L"      switch (c)\n");
  append(L"      {\n");
  append(L"      case '<': result += \"&lt;\"; break;\n");
  append(L"      case '\"': result += \"&quot;\"; break;\n");
  append(L"      case '&': result += \"&amp;\"; break;\n");
  append(L"      default : result += c;\n");
  append(L"      }\n");
  append(L"    }\n");
  append(L"    return result;\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  public writeTrace(trace: string)\n");
  append(L"  {\n");
  append(L"    proc.stderr.write(trace);\n");
  append(L"  }\n");
                                                            #line 423 "CodeGeneratorTypescript.cpp.template"
                                                                if (variable("embedded").boolean())
                                                                {
                                                            #line 762 "CodeGeneratorTypescript.cpp"
  append(L"\n");
  append(L"  flushTrace()\n");
  append(L"  {\n");
  append(L"  }\n");
                                                            #line 429 "CodeGeneratorTypescript.cpp.template"
                                                                }
                                                              }
                                                              if (variable("nolexer").boolean())
                                                              {
                                                            #line 772 "CodeGeneratorTypescript.cpp"
  append(L"\n");
  append(L"\n");
  append(L"  getTokenSetCount() {return ");
                                                            #line 435 "CodeGeneratorTypescript.cpp.template"
                                                                print(variable("entrycount").integer());
                                                            #line 778 "CodeGeneratorTypescript.cpp"
  append(L";}\n");
  append(L"  getTokenName(code) {return code >= 0 && code < Parser.TOKEN.length ? Parser.TOKEN[code] : null;}\n");
                                                            #line 438 "CodeGeneratorTypescript.cpp.template"
                                                              }
                                                            #line 783 "CodeGeneratorTypescript.cpp"
  append(L"\n");
  append(L"  private static getTokenSet(tokenSetId: number)\n");
  append(L"  {\n");
  append(L"    var set: string[] = [];");
                                                            #line 442 "CodeGeneratorTypescript.cpp.template"
                                                              if (! variable("nolexer").boolean())
                                                              {
                                                            #line 791 "CodeGeneratorTypescript.cpp"
  append(L"\n");
  append(L"    var s = tokenSetId < 0 ? - tokenSetId : Parser.INITIAL[tokenSetId] & ");
                                                            #line 446 "CodeGeneratorTypescript.cpp.template"
                                                                print(Math::powerof(2, variable("stateCodeBits").integer()) - 1);
                                                            #line 796 "CodeGeneratorTypescript.cpp"
  append(L";");
                                                            #line 448 "CodeGeneratorTypescript.cpp.template"
                                                              }
                                                            #line 800 "CodeGeneratorTypescript.cpp"
  append(L"\n");
  append(L"    for (var i = 0; i < ");
                                                            #line 450 "CodeGeneratorTypescript.cpp.template"
                                                              print(variable("t1").size);
                                                            #line 805 "CodeGeneratorTypescript.cpp"
  append(L"; i += 32)\n");
  append(L"    {\n");
  append(L"      var j = i;\n");
  append(L"      var i0 = (i >> 5) * ");
                                                            #line 454 "CodeGeneratorTypescript.cpp.template"
                                                              print(variable("transitionStateCount").integer());
                                                            #line 812 "CodeGeneratorTypescript.cpp"
  append(L" + ");
                                                            #line 455 "CodeGeneratorTypescript.cpp.template"
                                                              if (variable("nolexer").boolean())
                                                              {
                                                            #line 817 "CodeGeneratorTypescript.cpp"
  append(L"tokenSetId");
                                                            #line 457 "CodeGeneratorTypescript.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 823 "CodeGeneratorTypescript.cpp"
  append(L"s - 1");
                                                            #line 460 "CodeGeneratorTypescript.cpp.template"
                                                              }
                                                            #line 827 "CodeGeneratorTypescript.cpp"
  append(L";\n");
                                                            #line 462 "CodeGeneratorTypescript.cpp.template"
                                                              compressedMapAccessor(6, "i", "var f = ", "EXPECTED", &variable("t0bits").integer());
                                                            #line 831 "CodeGeneratorTypescript.cpp"
  append(L"\n");
  append(L"      for ( ; f != 0; f >>>= 1, ++j)\n");
  append(L"      {\n");
  append(L"        if ((f & 1) != 0)\n");
  append(L"        {\n");
  append(L"          set.push(Parser.TOKEN[j]);\n");
  append(L"        }\n");
  append(L"      }\n");
  append(L"    }\n");
  append(L"    return set;\n");
  append(L"  }\n");
                                                            #line 474 "CodeGeneratorTypescript.cpp.template"
                                                              for (VarsInInsertionOrder::iterator a(varsInInsertionOrder.begin());
                                                                   a != varsInInsertionOrder.end(); ++a)
                                                                if (a->isArray() && a->size > 0 && a->hasType(CGVariable::INTEGER) && strlen(a->name) == 2)
                                                              {
                                                            #line 848 "CodeGeneratorTypescript.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 479 "CodeGeneratorTypescript.cpp.template"
                                                                if (variable("useGlr").boolean())
                                                                {
                                                            #line 854 "CodeGeneratorTypescript.cpp"
  append(L"public");
                                                            #line 481 "CodeGeneratorTypescript.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 860 "CodeGeneratorTypescript.cpp"
  append(L"private");
                                                            #line 484 "CodeGeneratorTypescript.cpp.template"
                                                                }
                                                            #line 864 "CodeGeneratorTypescript.cpp"
  append(L" static ");
                                                            #line 485 "CodeGeneratorTypescript.cpp.template"
                                                                print(a->getLongName());
                                                            #line 868 "CodeGeneratorTypescript.cpp"
  append(L": number[] =\n");
  append(L"  [");
                                                            #line 487 "CodeGeneratorTypescript.cpp.template"
                                                                int w = (int) Format::width(a->size);
                                                                for (size_t j = 0; j < a->size; ++j)
                                                                {
                                                                  if (j == 0 || lineLength() + Format::width(a->integer(j)) + 2 > 119)
                                                                  {
                                                                    if (j) print(",");
                                                            #line 878 "CodeGeneratorTypescript.cpp"
  append(L"\n");
  append(L"    /* ");
                                                            #line 494 "CodeGeneratorTypescript.cpp.template"
                                                                    print(format.toString<char>(j, 10, w));
                                                            #line 883 "CodeGeneratorTypescript.cpp"
  append(L" */ ");
                                                            #line 495 "CodeGeneratorTypescript.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 889 "CodeGeneratorTypescript.cpp"
  append(L", ");
                                                            #line 498 "CodeGeneratorTypescript.cpp.template"
                                                                  }
                                                                  if (a->integer(j) != (int) 0x80000000)
                                                                  {
                                                                    print(a->integer(j));
                                                                  }
                                                                  else
                                                                  {
                                                                    print(format.toString<char>(a->integer(j), 16, 0, 0, "0x", "0123456789abcdef"));
                                                                  }
                                                                }
                                                            #line 902 "CodeGeneratorTypescript.cpp"
  append(L"\n");
  append(L"  ];\n");
                                                            #line 510 "CodeGeneratorTypescript.cpp.template"
                                                              }
                                                              for (VarsInInsertionOrder::iterator a(varsInInsertionOrder.begin());
                                                                   a != varsInInsertionOrder.end(); ++a)
                                                                if (a->isArray() && a->size > 0 && a->hasType(CGVariable::STRING) && strlen(a->name) == 2)
                                                              {
                                                            #line 911 "CodeGeneratorTypescript.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 516 "CodeGeneratorTypescript.cpp.template"
                                                                if (variable("useGlr").boolean())
                                                                {
                                                            #line 917 "CodeGeneratorTypescript.cpp"
  append(L"public");
                                                            #line 518 "CodeGeneratorTypescript.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 923 "CodeGeneratorTypescript.cpp"
  append(L"private");
                                                            #line 521 "CodeGeneratorTypescript.cpp.template"
                                                                }
                                                            #line 927 "CodeGeneratorTypescript.cpp"
  append(L" static ");
                                                            #line 522 "CodeGeneratorTypescript.cpp.template"
                                                                print(a->getLongName());
                                                            #line 931 "CodeGeneratorTypescript.cpp"
  append(L": string [] =\n");
  append(L"  [\n");
                                                            #line 525 "CodeGeneratorTypescript.cpp.template"
                                                                for (size_t j = 0; j < a->size; ++j)
                                                                {
                                                                  if (j)
                                                                  {
                                                            #line 939 "CodeGeneratorTypescript.cpp"
  append(L",\n");
                                                            #line 530 "CodeGeneratorTypescript.cpp.template"
                                                                  }
                                                            #line 943 "CodeGeneratorTypescript.cpp"
  append(L"    ");
                                                            #line 531 "CodeGeneratorTypescript.cpp.template"
                                                                  print(variable("stringPrefix").string());
                                                            #line 947 "CodeGeneratorTypescript.cpp"
  append(L"\"");
                                                            #line 532 "CodeGeneratorTypescript.cpp.template"
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
                                                            #line 962 "CodeGeneratorTypescript.cpp"
  append(L"\"");
                                                            #line 544 "CodeGeneratorTypescript.cpp.template"
                                                                  print(variable("stringSuffix").string());
                                                                }
                                                            #line 967 "CodeGeneratorTypescript.cpp"
  append(L"\n");
  append(L"  ];\n");
                                                            #line 548 "CodeGeneratorTypescript.cpp.template"
                                                              }
                                                              if (! variable("embedded").boolean())
                                                              {
                                                            #line 974 "CodeGeneratorTypescript.cpp"
  append(L"\n");
  append(L"  var ");
                                                            #line 552 "CodeGeneratorTypescript.cpp.template"
                                                                print(variable("classname").string());
                                                            #line 979 "CodeGeneratorTypescript.cpp"
  append(L".Token =\n");
  append(L"  {\n");
  append(L"    ");
                                                            #line 555 "CodeGeneratorTypescript.cpp.template"
                                                                const CGVariable &token = variable("token");
                                                                int w = (int) Format::width(token.size);
                                                                for (size_t i = 0; i < token.size; ++i)
                                                                {
                                                                  if (i)
                                                                  {
                                                            #line 990 "CodeGeneratorTypescript.cpp"
  append(L",\n");
  append(L"    ");
                                                            #line 562 "CodeGeneratorTypescript.cpp.template"
                                                                  }
                                                                  print(token.string(i));
                                                            #line 996 "CodeGeneratorTypescript.cpp"
  append(L":");
                                                            #line 564 "CodeGeneratorTypescript.cpp.template"
                                                                  print(format.toString<char>(i, 10, w));
                                                                }
                                                            #line 1001 "CodeGeneratorTypescript.cpp"
  append(L"\n");
  append(L"  };\n");
                                                            #line 568 "CodeGeneratorTypescript.cpp.template"
                                                              }
                                                            }

                                                            void CodeGeneratorTypescript::generateData()
                                                            {
                                                            }

// End
