// This file was generated on Tue Oct 20, 2026 19:55 (UTC+02) by REx v6.3-SNAPSHOT which is Copyright (c) 1979-2026 by Gunther Rademacher <grd@gmx.net>
// REx command line: CodeGeneratorJavascript.cpp.template
                                                            #line 1 "CodeGeneratorJavascript.cpp.template"
                                                            #include "../common/Memory.hpp"

                                                            #include "CodeGenerator.hpp"

                                                            void CodeGeneratorJavascript::generateInstanceCode()
                                                            {
                                                              isJavascript = true;
                                                              if (! variable("append").boolean() && ! variable("embedded").boolean())
                                                              {
                                                                if (*variable("package").string())
                                                                {
                                                            #line 16 "CodeGeneratorJavascript.cpp"
  append(L"package ");
                                                            #line 12 "CodeGeneratorJavascript.cpp.template"
                                                                  print(variable("package").string());
                                                            #line 20 "CodeGeneratorJavascript.cpp"
  append(L";\n");
  append(L"\n");
                                                            #line 15 "CodeGeneratorJavascript.cpp.template"
                                                                }
                                                            #line 25 "CodeGeneratorJavascript.cpp"
  append(L"function ");
                                                            #line 16 "CodeGeneratorJavascript.cpp.template"
                                                                print(variable("classname").string());
                                                            #line 29 "CodeGeneratorJavascript.cpp"
  append(L"()\n");
  append(L"{\n");
                                                            #line 19 "CodeGeneratorJavascript.cpp.template"
                                                              }
                                                              if (variable("tree").boolean())
                                                              {
                                                              }
                                                              if (variable("trace").boolean())
                                                              {
                                                              }
                                                              if (! variable("embedded").boolean())
                                                              {
                                                            #line 42 "CodeGeneratorJavascript.cpp"
  append(L"\n");
  append(L"  this.init = function(string)\n");
  append(L"  {\n");
  append(L"    input = string;\n");
  append(L"    size = string.length;\n");
  append(L"    end = 0;\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  match = function(tokenSetId, string)\n");
  append(L"  {\n");
  append(L"    init(string);\n");
  append(L"    return match(tokenSetId);\n");
  append(L"  }\n");
                                                            #line 41 "CodeGeneratorJavascript.cpp.template"
                                                              }
                                                              if (variable("useGlr").boolean())
                                                              {
                                                                ++indent;
                                                              }
                                                              else
                                                              {
                                                            #line 64 "CodeGeneratorJavascript.cpp"
  append(L"\n");
  append(L"  var input;");
                                                            #line 49 "CodeGeneratorJavascript.cpp.template"
                                                                if (! variable("nolexer").boolean())
                                                                {
                                                            #line 70 "CodeGeneratorJavascript.cpp"
  append(L"\n");
  append(L"  var size;");
                                                            #line 52 "CodeGeneratorJavascript.cpp.template"
                                                                }
                                                            #line 75 "CodeGeneratorJavascript.cpp"
  append(L"\n");
                                                            #line 54 "CodeGeneratorJavascript.cpp.template"
                                                              }
                                                            #line 79 "CodeGeneratorJavascript.cpp"
  append(L"\n");
  append(L"  var begin;\n");
  append(L"  var end;");
                                                            #line 57 "CodeGeneratorJavascript.cpp.template"
                                                              if (variable("nolexer").boolean())
                                                              {
                                                            #line 86 "CodeGeneratorJavascript.cpp"
  append(L"\n");
  append(L"  var lexer;\n");
  append(L"  var token = {};");
                                                            #line 61 "CodeGeneratorJavascript.cpp.template"
                                                              }
                                                              if (! variable("embedded").boolean())
                                                              {
                                                            #line 94 "CodeGeneratorJavascript.cpp"
  append(L"\n");
  append(L"  var state;");
                                                            #line 65 "CodeGeneratorJavascript.cpp.template"
                                                              }
                                                            #line 99 "CodeGeneratorJavascript.cpp"
  append(L"\n");
                                                            #line 67 "CodeGeneratorJavascript.cpp.template"
                                                              if (variable("tables").boolean())
                                                              {
                                                            #line 104 "CodeGeneratorJavascript.cpp"
  append(L"\n");
  append(L"  function predict(dpi)");
                                                            #line 70 "CodeGeneratorJavascript.cpp.template"
                                                                predict();
                                                              }
                                                            #line 110 "CodeGeneratorJavascript.cpp"
  append(L"\n");
  append(L"  function match(tokenSetId)\n");
  append(L"  {");
                                                            #line 74 "CodeGeneratorJavascript.cpp.template"
                                                              if (variable("nolexer").boolean())
                                                              {
                                                            #line 117 "CodeGeneratorJavascript.cpp"
  append(L"\n");
  append(L"    token.begin = end;\n");
  append(L"    lexer.match(tokenSetId, token);\n");
  append(L"    begin = token.begin;\n");
  append(L"    end = token.end;\n");
  append(L"    return token.code >= 0\n");
  append(L"         ? token.code\n");
  append(L"         : error(begin, end, - tokenSetId, -1, -1);");
                                                            #line 83 "CodeGeneratorJavascript.cpp.template"
                                                              }
                                                              else
                                                              {
                                                                if (variable("trace").boolean())
                                                                {
                                                            #line 132 "CodeGeneratorJavascript.cpp"
  append(L"\n");
  append(L"    writeTrace(\"  <tokenize ");
                                                            #line 89 "CodeGeneratorJavascript.cpp.template"
                                                                  if (variable("useGlr").boolean())
                                                                  {
                                                            #line 138 "CodeGeneratorJavascript.cpp"
  append(L"thread=\\\"\" + id + \"\\\" ");
                                                            #line 91 "CodeGeneratorJavascript.cpp.template"
                                                                  }
                                                            #line 142 "CodeGeneratorJavascript.cpp"
  append(L"tokenset=\\\"\" + tokenSetId + \"\\\">\\n\");\n");
                                                            #line 93 "CodeGeneratorJavascript.cpp.template"
                                                                }
                                                                int lookahead = variable("maxcontextlength").integer();
                                                                bool hasFixedTokenLength = variable("hasfixedtokenlength").boolean();
                                                                if (lookahead)
                                                                {
                                                            #line 150 "CodeGeneratorJavascript.cpp"
  append(L"\n");
  append(L"    var nonbmp = false;");
                                                            #line 99 "CodeGeneratorJavascript.cpp.template"
                                                                }
                                                            #line 155 "CodeGeneratorJavascript.cpp"
  append(L"\n");
  append(L"    begin = end;\n");
  append(L"    var current = end;\n");
  append(L"    var result = ");
                                                            #line 103 "CodeGeneratorJavascript.cpp.template"
                                                                print(variable("classname").string());
                                                            #line 162 "CodeGeneratorJavascript.cpp"
  append(L".INITIAL[tokenSetId];");
                                                            #line 104 "CodeGeneratorJavascript.cpp.template"
                                                                if (variable("embedded").boolean())
                                                                {
                                                            #line 167 "CodeGeneratorJavascript.cpp"
  append(L"\n");
  append(L"    var state = 0;");
                                                            #line 107 "CodeGeneratorJavascript.cpp.template"
                                                                }
                                                            #line 172 "CodeGeneratorJavascript.cpp"
  append(L"\n");
                                                            #line 109 "CodeGeneratorJavascript.cpp.template"
                                                                if (variable("trace").boolean())
                                                                {
                                                            #line 177 "CodeGeneratorJavascript.cpp"
  append(L"\n");
  append(L"    writeTrace(\"    <next state=\\\"\" + (result & ");
                                                            #line 112 "CodeGeneratorJavascript.cpp.template"
                                                                  print(Math::powerof(2, variable("stateCodeBits").integer()) - 1);
                                                            #line 182 "CodeGeneratorJavascript.cpp"
  append(L") + \"\\\"\");");
                                                            #line 113 "CodeGeneratorJavascript.cpp.template"
                                                                }
                                                            #line 186 "CodeGeneratorJavascript.cpp"
  append(L"\n");
  append(L"    for (var code = result & ");
                                                            #line 115 "CodeGeneratorJavascript.cpp.template"
                                                                print(Math::powerof(2, variable("stateCodeBits").integer()) - 1);
                                                            #line 191 "CodeGeneratorJavascript.cpp"
  append(L"; code != 0; )\n");
  append(L"    {\n");
  append(L"      var charclass;\n");
  append(L"      var c0 = current < size ? input.charCodeAt(current) : 0;");
                                                            #line 119 "CodeGeneratorJavascript.cpp.template"
                                                                if (variable("trace").boolean())
                                                                {
                                                            #line 199 "CodeGeneratorJavascript.cpp"
  append(L"\n");
  append(L"      writeTrace(\" offset=\\\"\" + current + \"\\\"\");");
                                                            #line 122 "CodeGeneratorJavascript.cpp.template"
                                                                }
                                                            #line 204 "CodeGeneratorJavascript.cpp"
  append(L"\n");
  append(L"      ++current;\n");
  append(L"      if (c0 < ");
                                                            #line 125 "CodeGeneratorJavascript.cpp.template"
                                                                print(format.toString<char>(variable("simplifiedCodeMap").integer(), 16, 0, 0, "0x", "0123456789abcdef"));
                                                            #line 210 "CodeGeneratorJavascript.cpp"
  append(L")\n");
  append(L"      {");
                                                            #line 127 "CodeGeneratorJavascript.cpp.template"
                                                                if (variable("trace").boolean())
                                                                {
                                                            #line 216 "CodeGeneratorJavascript.cpp"
  append(L"\n");
  append(L"        if (c0 >= 32 && c0 <= 126)\n");
  append(L"          writeTrace(\" char=\\\"\" + ");
                                                            #line 131 "CodeGeneratorJavascript.cpp.template"
                                                                  print(variable("classname").string());
                                                            #line 222 "CodeGeneratorJavascript.cpp"
  append(L".xmlEscape(input.charAt(current - 1)) + \"\\\"\");");
                                                            #line 133 "CodeGeneratorJavascript.cpp.template"
                                                                }
                                                            #line 226 "CodeGeneratorJavascript.cpp"
  append(L"\n");
  append(L"        charclass = ");
                                                            #line 135 "CodeGeneratorJavascript.cpp.template"
                                                                print(variable("classname").string());
                                                            #line 231 "CodeGeneratorJavascript.cpp"
  append(L".MAP0[c0];\n");
  append(L"      }\n");
  append(L"      else if (c0 < ");
                                                            #line 138 "CodeGeneratorJavascript.cpp.template"
                                                                print(format.toString<char>(variable("uncompressedMapSize").integer(), 16, 0, 0, "0x", "0123456789abcdef"));
                                                            #line 237 "CodeGeneratorJavascript.cpp"
  append(L")\n");
  append(L"      {\n");
                                                            #line 141 "CodeGeneratorJavascript.cpp.template"
                                                                compressedMapAccessor(8, "c", "charclass = ", "MAP1", &variable("m1bits").integer());
                                                            #line 242 "CodeGeneratorJavascript.cpp"
  append(L"\n");
  append(L"      }\n");
  append(L"      else\n");
  append(L"      {");
                                                            #line 145 "CodeGeneratorJavascript.cpp.template"
                                                                if (variable("m2").size == 0)
                                                                {
                                                            #line 250 "CodeGeneratorJavascript.cpp"
  append(L"\n");
  append(L"        charclass = 0;");
                                                            #line 148 "CodeGeneratorJavascript.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 257 "CodeGeneratorJavascript.cpp"
  append(L"\n");
  append(L"        if (");
                                                            #line 152 "CodeGeneratorJavascript.cpp.template"
                                                                  if (variable("uncompressedMapSize").integer() != 0xd800)
                                                                  {
                                                            #line 263 "CodeGeneratorJavascript.cpp"
  append(L"c0 >= 0xd800 && ");
                                                            #line 154 "CodeGeneratorJavascript.cpp.template"
                                                                  }
                                                            #line 267 "CodeGeneratorJavascript.cpp"
  append(L"c0 < 0xdc00)\n");
  append(L"        {\n");
  append(L"          var c1 = current < size ? input.charCodeAt(current) : 0;\n");
  append(L"          if (c1 >= 0xdc00 && c1 < 0xe000)\n");
  append(L"          {\n");
  append(L"            ++current;\n");
  append(L"            c0 = ((c0 & 0x3ff) << 10) + (c1 & 0x3ff) + 0x10000;");
                                                            #line 161 "CodeGeneratorJavascript.cpp.template"
                                                                  if (lookahead)
                                                                  {
                                                            #line 278 "CodeGeneratorJavascript.cpp"
  append(L"\n");
  append(L"            nonbmp = true;");
                                                            #line 164 "CodeGeneratorJavascript.cpp.template"
                                                                  }
                                                            #line 283 "CodeGeneratorJavascript.cpp"
  append(L"\n");
  append(L"          }\n");
  append(L"        }\n");
  append(L"\n");
  append(L"        var lo = 0, hi = ");
                                                            #line 169 "CodeGeneratorJavascript.cpp.template"
                                                                  print(variable("m2").size / 3 - 1);
                                                            #line 291 "CodeGeneratorJavascript.cpp"
  append(L";\n");
  append(L"        for (var m = ");
                                                            #line 171 "CodeGeneratorJavascript.cpp.template"
                                                                  print((variable("m2").size / 3) >> 1);
                                                            #line 296 "CodeGeneratorJavascript.cpp"
  append(L"; ; m = (hi + lo) >> 1)\n");
  append(L"        {\n");
  append(L"          if (");
                                                            #line 174 "CodeGeneratorJavascript.cpp.template"
                                                                  print(variable("classname").string());
                                                            #line 302 "CodeGeneratorJavascript.cpp"
  append(L".MAP2[m] > c0) hi = m - 1;\n");
  append(L"          else if (");
                                                            #line 176 "CodeGeneratorJavascript.cpp.template"
                                                                  print(variable("classname").string());
                                                            #line 307 "CodeGeneratorJavascript.cpp"
  append(L".MAP2[");
                                                            #line 177 "CodeGeneratorJavascript.cpp.template"
                                                                  print(variable("m2").size / 3);
                                                            #line 311 "CodeGeneratorJavascript.cpp"
  append(L" + m] < c0) lo = m + 1;\n");
  append(L"          else {charclass = ");
                                                            #line 179 "CodeGeneratorJavascript.cpp.template"
                                                                  print(variable("classname").string());
                                                            #line 316 "CodeGeneratorJavascript.cpp"
  append(L".MAP2[");
                                                            #line 180 "CodeGeneratorJavascript.cpp.template"
                                                                  print(variable("m2").size / 3 * 2);
                                                            #line 320 "CodeGeneratorJavascript.cpp"
  append(L" + m]; break;}\n");
  append(L"          if (lo > hi) {charclass = 0; break;}\n");
  append(L"        }");
                                                            #line 183 "CodeGeneratorJavascript.cpp.template"
                                                                }
                                                            #line 326 "CodeGeneratorJavascript.cpp"
  append(L"\n");
  append(L"      }");
                                                            #line 185 "CodeGeneratorJavascript.cpp.template"
                                                                if (variable("trace").boolean())
                                                                {
                                                            #line 332 "CodeGeneratorJavascript.cpp"
  append(L"\n");
  append(L"      writeTrace(\" codepoint=\\\"\" + c0 + \"\\\" class=\\\"\" + charclass + \"\\\"\");");
                                                            #line 189 "CodeGeneratorJavascript.cpp.template"
                                                                }
                                                            #line 337 "CodeGeneratorJavascript.cpp"
  append(L"\n");
  append(L"\n");
  append(L"      state = code;\n");
                                                            #line 193 "CodeGeneratorJavascript.cpp.template"
                                                                compressedMap2dAccessor("code - 1", "charclass", variable("a1cols").integer(),
                                                                                           6, "i", "code = ", "TRANSITION", &variable("a1bits").integer());
                                                            #line 344 "CodeGeneratorJavascript.cpp"
  append(L"\n");
  append(L"\n");
  append(L"      if (code > ");
                                                            #line 197 "CodeGeneratorJavascript.cpp.template"
                                                                print(Math::powerof(2, variable("stateCodeBits").integer()) - 1);
                                                            #line 350 "CodeGeneratorJavascript.cpp"
  append(L")\n");
  append(L"      {\n");
  append(L"        result = code;");
                                                            #line 200 "CodeGeneratorJavascript.cpp.template"
                                                                if (variable("trace").boolean())
                                                                {
                                                            #line 357 "CodeGeneratorJavascript.cpp"
  append(L"\n");
  append(L"        writeTrace(\" result=\\\"\" + ");
                                                            #line 203 "CodeGeneratorJavascript.cpp.template"
                                                                  print(variable("classname").string());
                                                            #line 362 "CodeGeneratorJavascript.cpp"
  append(L".xmlEscape(");
                                                            #line 204 "CodeGeneratorJavascript.cpp.template"
                                                                  print(variable("classname").string());
                                                            #line 366 "CodeGeneratorJavascript.cpp"
  append(L".TOKEN[((result >> ");
                                                            #line 205 "CodeGeneratorJavascript.cpp.template"
                                                                  print(variable("stateCodeBits").integer());
                                                            #line 370 "CodeGeneratorJavascript.cpp"
  append(L") & ");
                                                            #line 206 "CodeGeneratorJavascript.cpp.template"
                                                                  print(Math::powerof(2, variable("tokencodeBits").integer()) - 1);
                                                            #line 374 "CodeGeneratorJavascript.cpp"
  append(L") - 1]) + \"\\\"\");");
                                                            #line 208 "CodeGeneratorJavascript.cpp.template"
                                                                  if (lookahead || hasFixedTokenLength)
                                                                  {
                                                                    int contextOffset = variable("stateCodeBits").integer()
                                                                                      + variable("tokencodeBits").integer();
                                                                    int sizeOffset = contextOffset
                                                                                   + (hasFixedTokenLength ? 1 : 0);
                                                                    if (hasFixedTokenLength)
                                                                    {
                                                            #line 385 "CodeGeneratorJavascript.cpp"
  append(L"\n");
  append(L"        if ((result & ");
                                                            #line 217 "CodeGeneratorJavascript.cpp.template"
                                                                      print(Math::powerof(2, contextOffset));
                                                            #line 390 "CodeGeneratorJavascript.cpp"
  append(L") > 0)\n");
  append(L"        {\n");
  append(L"          writeTrace(\" token-size=\\\"\" + (result >> ");
                                                            #line 220 "CodeGeneratorJavascript.cpp.template"
                                                                      print(sizeOffset);
                                                            #line 396 "CodeGeneratorJavascript.cpp"
  append(L") + \"\\\"\");\n");
  append(L"        }\n");
  append(L"        else ");
                                                            #line 223 "CodeGeneratorJavascript.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 404 "CodeGeneratorJavascript.cpp"
  append(L"\n");
  append(L"        ");
                                                            #line 227 "CodeGeneratorJavascript.cpp.template"
                                                                    }
                                                            #line 409 "CodeGeneratorJavascript.cpp"
  append(L"if ((result >> ");
                                                            #line 228 "CodeGeneratorJavascript.cpp.template"
                                                                    print(sizeOffset);
                                                            #line 413 "CodeGeneratorJavascript.cpp"
  append(L") > 0)\n");
  append(L"        {\n");
  append(L"          writeTrace(\" trailing-context-size=\\\"\" + (result >> ");
                                                            #line 231 "CodeGeneratorJavascript.cpp.template"
                                                                    print(sizeOffset);
                                                            #line 419 "CodeGeneratorJavascript.cpp"
  append(L") + \"\\\"\");\n");
  append(L"        }");
                                                            #line 233 "CodeGeneratorJavascript.cpp.template"
                                                                  }
                                                                }
                                                            #line 425 "CodeGeneratorJavascript.cpp"
  append(L"\n");
  append(L"        code &= ");
                                                            #line 236 "CodeGeneratorJavascript.cpp.template"
                                                                print(Math::powerof(2, variable("stateCodeBits").integer()) - 1);
                                                            #line 430 "CodeGeneratorJavascript.cpp"
  append(L";\n");
  append(L"        end = current;\n");
  append(L"      }");
                                                            #line 239 "CodeGeneratorJavascript.cpp.template"
                                                                if (variable("trace").boolean())
                                                                {
                                                            #line 437 "CodeGeneratorJavascript.cpp"
  append(L"\n");
  append(L"      writeTrace(\"/>\\n\");\n");
  append(L"      if (code != 0)\n");
  append(L"      {\n");
  append(L"        writeTrace(\"    <next state=\\\"\" + code + \"\\\"\");\n");
  append(L"      }");
                                                            #line 246 "CodeGeneratorJavascript.cpp.template"
                                                                }
                                                            #line 446 "CodeGeneratorJavascript.cpp"
  append(L"\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    result >>= ");
                                                            #line 250 "CodeGeneratorJavascript.cpp.template"
                                                                print(variable("stateCodeBits").integer());
                                                            #line 453 "CodeGeneratorJavascript.cpp"
  append(L";\n");
  append(L"    if (result == 0)\n");
  append(L"    {\n");
  append(L"      end = current - 1;\n");
  append(L"      var c1 = end < size ? input.charCodeAt(end) : 0;\n");
  append(L"      if (c1 >= 0xdc00 && c1 < 0xe000) --end;");
                                                            #line 256 "CodeGeneratorJavascript.cpp.template"
                                                                if (variable("trace").boolean())
                                                                {
                                                            #line 463 "CodeGeneratorJavascript.cpp"
  append(L"\n");
  append(L"      writeTrace(\"    <fail begin=\\\"\" + begin + \"\\\" end=\\\"\" + end + \"\\\" state=\\\"\" + state + \"\\\"/>\\n\");\n");
  append(L"      writeTrace(\"  </tokenize>\\n\");");
                                                            #line 260 "CodeGeneratorJavascript.cpp.template"
                                                                }
                                                                if (! variable("embedded").boolean())
                                                                {
                                                            #line 471 "CodeGeneratorJavascript.cpp"
  append(L"\n");
  append(L"      return -1;");
                                                            #line 264 "CodeGeneratorJavascript.cpp.template"
                                                                }
                                                                else
                                                                {
                                                                  if (variable("useGlr").boolean())
                                                                  {
                                                            #line 480 "CodeGeneratorJavascript.cpp"
  append(L"\n");
  append(L"      end = begin;\n");
  append(L"      return -1;");
                                                            #line 271 "CodeGeneratorJavascript.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 488 "CodeGeneratorJavascript.cpp"
  append(L"\n");
  append(L"      return error(begin, end, state, -1, -1);");
                                                            #line 275 "CodeGeneratorJavascript.cpp.template"
                                                                  }
                                                                }
                                                            #line 494 "CodeGeneratorJavascript.cpp"
  append(L"\n");
  append(L"    }\n");
                                                            #line 279 "CodeGeneratorJavascript.cpp.template"
                                                                int lowBits = variable("tokencodeBits").integer();
                                                                if (hasFixedTokenLength && ! lookahead)
                                                                {
                                                            #line 501 "CodeGeneratorJavascript.cpp"
  append(L"\n");
  append(L"    if ((result & ");
                                                            #line 283 "CodeGeneratorJavascript.cpp.template"
                                                                  print(Math::powerof(2, lowBits));
                                                                  ++lowBits;
                                                            #line 507 "CodeGeneratorJavascript.cpp"
  append(L") != 0)\n");
  append(L"    {\n");
  append(L"      end = begin;\n");
  append(L"    }\n");
                                                            #line 289 "CodeGeneratorJavascript.cpp.template"
                                                                }
                                                                else
                                                                {
                                                                  if (hasFixedTokenLength)
                                                                  {
                                                            #line 518 "CodeGeneratorJavascript.cpp"
  append(L"\n");
  append(L"    if ((result & ");
                                                            #line 295 "CodeGeneratorJavascript.cpp.template"
                                                                    print(Math::powerof(2, lowBits));
                                                                    ++lowBits;
                                                            #line 524 "CodeGeneratorJavascript.cpp"
  append(L") != 0)\n");
  append(L"    {\n");
  append(L"      end = begin;\n");
  append(L"      if (nonbmp)\n");
  append(L"      {\n");
  append(L"        for (var i = result >> ");
                                                            #line 302 "CodeGeneratorJavascript.cpp.template"
                                                                    print(lowBits);
                                                            #line 533 "CodeGeneratorJavascript.cpp"
  append(L"; i > 0; --i)\n");
  append(L"        {\n");
  append(L"          var c1 = end < size ? input.charCodeAt(end++) : 0;\n");
  append(L"          if (c1 >= 0xd800 && c1 < 0xdc00) ++end;\n");
  append(L"        }\n");
  append(L"      }\n");
  append(L"      else\n");
  append(L"      {\n");
  append(L"        end += (result >> ");
                                                            #line 311 "CodeGeneratorJavascript.cpp.template"
                                                                    print(lowBits);
                                                            #line 545 "CodeGeneratorJavascript.cpp"
  append(L");\n");
  append(L"      }\n");
  append(L"    }\n");
  append(L"    else\n");
  append(L"    {");
                                                            #line 316 "CodeGeneratorJavascript.cpp.template"
                                                                    ++indent;
                                                                  }
                                                                  if (lookahead)
                                                                  {
                                                            #line 556 "CodeGeneratorJavascript.cpp"
  append(L"\n");
  append(L"    if (nonbmp)\n");
  append(L"    {\n");
  append(L"      for (var i = result >> ");
                                                            #line 323 "CodeGeneratorJavascript.cpp.template"
                                                                    print(lowBits);
                                                            #line 563 "CodeGeneratorJavascript.cpp"
  append(L"; i > 0; --i)\n");
  append(L"      {\n");
  append(L"        --end;\n");
  append(L"        var c1 = end < size ? input.charCodeAt(end) : 0;\n");
  append(L"        if (c1 >= 0xdc00 && c1 < 0xe000) --end;\n");
  append(L"      }\n");
  append(L"    }\n");
  append(L"    else\n");
  append(L"    {\n");
  append(L"      end -= result >> ");
                                                            #line 333 "CodeGeneratorJavascript.cpp.template"
                                                                    print(lowBits);
                                                            #line 576 "CodeGeneratorJavascript.cpp"
  append(L";\n");
  append(L"    }\n");
                                                            #line 336 "CodeGeneratorJavascript.cpp.template"
                                                                  }
                                                                  if (hasFixedTokenLength)
                                                                  {
                                                                    --indent;
                                                            #line 584 "CodeGeneratorJavascript.cpp"
  append(L"  }\n");
                                                            #line 341 "CodeGeneratorJavascript.cpp.template"
                                                                  }
                                                                }
                                                            #line 589 "CodeGeneratorJavascript.cpp"
  append(L"\n");
  append(L"    if (end > size) end = size;");
                                                            #line 344 "CodeGeneratorJavascript.cpp.template"
                                                                if (variable("trace").boolean())
                                                                {
                                                            #line 595 "CodeGeneratorJavascript.cpp"
  append(L"\n");
  append(L"\n");
  append(L"    writeTrace(\"    <done result=\\\"\" + ");
                                                            #line 348 "CodeGeneratorJavascript.cpp.template"
                                                                  print(variable("classname").string());
                                                            #line 601 "CodeGeneratorJavascript.cpp"
  append(L".xmlEscape(");
                                                            #line 349 "CodeGeneratorJavascript.cpp.template"
                                                                  print(variable("classname").string());
                                                            #line 605 "CodeGeneratorJavascript.cpp"
  append(L".TOKEN[(result & ");
                                                            #line 350 "CodeGeneratorJavascript.cpp.template"
                                                                  print(Math::powerof(2, variable("tokencodeBits").integer()) - 1);
                                                            #line 609 "CodeGeneratorJavascript.cpp"
  append(L") - 1]) + \"\\\" begin=\\\"\" + begin + \"\\\" end=\\\"\" + end + \"\\\"/>\\n\");\n");
  append(L"    writeTrace(\"  </tokenize>\\n\");");
                                                            #line 352 "CodeGeneratorJavascript.cpp.template"
                                                                }
                                                            #line 614 "CodeGeneratorJavascript.cpp"
  append(L"\n");
  append(L"    return (result & ");
                                                            #line 354 "CodeGeneratorJavascript.cpp.template"
                                                                print(Math::powerof(2, variable("tokencodeBits").integer()) - 1);
                                                            #line 619 "CodeGeneratorJavascript.cpp"
  append(L") - 1;");
                                                            #line 355 "CodeGeneratorJavascript.cpp.template"
                                                              }
                                                            #line 623 "CodeGeneratorJavascript.cpp"
  append(L"\n");
  append(L"  }\n");
                                                            #line 358 "CodeGeneratorJavascript.cpp.template"
                                                              if (variable("useGlr").boolean())
                                                              {
                                                            #line 629 "CodeGeneratorJavascript.cpp"
  append(L"\n");
  append(L"}\n");
                                                            #line 362 "CodeGeneratorJavascript.cpp.template"
                                                                --indent;
                                                              }
                                                              if (! variable("embedded").boolean())
                                                              {
                                                            #line 637 "CodeGeneratorJavascript.cpp"
  append(L"\n");
  append(L"  function getExpectedTokenSet()\n");
  append(L"  {\n");
  append(L"    return getTokenSet(- state);\n");
  append(L"  }\n");
                                                            #line 371 "CodeGeneratorJavascript.cpp.template"
                                                              }
                                                              if (variable("trace").boolean())
                                                              {
                                                            #line 647 "CodeGeneratorJavascript.cpp"
  append(L"\n");
  append(L"  var writeTrace = typeof process  != \"undefined\" ? function(string) {process.stderr.write(string);}\n");
  append(L"                 : typeof WScript  != \"undefined\" ? WScript.StdErr.write\n");
  append(L"                 : typeof err      != \"undefined\" ? function(string) {err.print(string);}\n");
  append(L"                 :                                  function(string) {java.lang.System.err.write(java.lang.String(string).getBytes(\"utf-8\"));};\n");
  append(L"  this.writeTrace = writeTrace;\n");
                                                            #line 380 "CodeGeneratorJavascript.cpp.template"
                                                                if (variable("embedded").boolean())
                                                                {
                                                            #line 657 "CodeGeneratorJavascript.cpp"
  append(L"\n");
  append(L"  var flushTrace = typeof err != \"undefined\" ? function() {err.flush();} : function() {}\n");
  append(L"  this.flushTrace = flushTrace;\n");
                                                            #line 385 "CodeGeneratorJavascript.cpp.template"
                                                                }
                                                              }
                                                            }

                                                            void CodeGeneratorJavascript::generateStaticCode()
                                                            {
                                                              if (defined("gtbits"))
                                                              {
                                                            #line 670 "CodeGeneratorJavascript.cpp"
  append(L"\n");
                                                            #line 394 "CodeGeneratorJavascript.cpp.template"
                                                                print(variable("classname").string());
                                                            #line 674 "CodeGeneratorJavascript.cpp"
  append(L".goTo = function(nonterminal, state)\n");
  append(L"{\n");
                                                            #line 397 "CodeGeneratorJavascript.cpp.template"
                                                                compressedMap2dAccessor("nonterminal", "state", variable("gtcols").integer(),
                                                                                        2, "i", "return ", "GOTO", &variable("gtbits").integer());
                                                            #line 680 "CodeGeneratorJavascript.cpp"
  append(L"\n");
  append(L"};\n");
                                                            #line 401 "CodeGeneratorJavascript.cpp.template"
                                                              }
                                                              if (variable("trace").boolean())
                                                              {
                                                            #line 687 "CodeGeneratorJavascript.cpp"
  append(L"\n");
                                                            #line 405 "CodeGeneratorJavascript.cpp.template"
                                                                print(variable("classname").string());
                                                            #line 691 "CodeGeneratorJavascript.cpp"
  append(L".xmlEscape = function(s)\n");
  append(L"{\n");
  append(L"  var result = \"\";\n");
  append(L"  for (var i = 0; i < s.length; ++i)\n");
  append(L"  {\n");
  append(L"    var c = s.charAt(i);\n");
  append(L"    switch (c)\n");
  append(L"    {\n");
  append(L"    case '<': result += \"&lt;\"; break;\n");
  append(L"    case '\"': result += \"&quot;\"; break;\n");
  append(L"    case '&': result += \"&amp;\"; break;\n");
  append(L"\n");
  append(L"    default : result += c;\n");
  append(L"    }\n");
  append(L"  }\n");
  append(L"  return result;\n");
  append(L"};\n");
                                                            #line 423 "CodeGeneratorJavascript.cpp.template"
                                                              }
                                                              if (variable("nolexer").boolean())
                                                              {
                                                            #line 713 "CodeGeneratorJavascript.cpp"
  append(L"\n");
  append(L"\n");
                                                            #line 428 "CodeGeneratorJavascript.cpp.template"
                                                                print(variable("classname").string());
                                                            #line 718 "CodeGeneratorJavascript.cpp"
  append(L".getTokenSetCount = function() {return ");
                                                            #line 429 "CodeGeneratorJavascript.cpp.template"
                                                                print(variable("entrycount").integer());
                                                            #line 722 "CodeGeneratorJavascript.cpp"
  append(L";};\n");
                                                            #line 431 "CodeGeneratorJavascript.cpp.template"
                                                                print(variable("classname").string());
                                                            #line 726 "CodeGeneratorJavascript.cpp"
  append(L".getTokenName = function(code) {return code >= 0 && code < ");
                                                            #line 432 "CodeGeneratorJavascript.cpp.template"
                                                                print(variable("classname").string());
                                                            #line 730 "CodeGeneratorJavascript.cpp"
  append(L".TOKEN.length ? ");
                                                            #line 434 "CodeGeneratorJavascript.cpp.template"
                                                                print(variable("classname").string());
                                                            #line 734 "CodeGeneratorJavascript.cpp"
  append(L".TOKEN[code] : null;};\n");
                                                            #line 436 "CodeGeneratorJavascript.cpp.template"
                                                              }
                                                            #line 738 "CodeGeneratorJavascript.cpp"
  append(L"\n");
                                                            #line 438 "CodeGeneratorJavascript.cpp.template"
                                                              print(variable("classname").string());
                                                            #line 742 "CodeGeneratorJavascript.cpp"
  append(L".getTokenSet = function(tokenSetId)\n");
  append(L"{\n");
  append(L"  var set = [];");
                                                            #line 441 "CodeGeneratorJavascript.cpp.template"
                                                              if (! variable("nolexer").boolean())
                                                              {
                                                            #line 749 "CodeGeneratorJavascript.cpp"
  append(L"\n");
  append(L"  var s = tokenSetId < 0 ? - tokenSetId : ");
                                                            #line 444 "CodeGeneratorJavascript.cpp.template"
                                                                print(variable("classname").string());
                                                            #line 754 "CodeGeneratorJavascript.cpp"
  append(L".INITIAL[tokenSetId] & ");
                                                            #line 446 "CodeGeneratorJavascript.cpp.template"
                                                                print(Math::powerof(2, variable("stateCodeBits").integer()) - 1);
                                                            #line 758 "CodeGeneratorJavascript.cpp"
  append(L";");
                                                            #line 448 "CodeGeneratorJavascript.cpp.template"
                                                              }
                                                            #line 762 "CodeGeneratorJavascript.cpp"
  append(L"\n");
  append(L"  for (var i = 0; i < ");
                                                            #line 450 "CodeGeneratorJavascript.cpp.template"
                                                              print(variable("t1").size);
                                                            #line 767 "CodeGeneratorJavascript.cpp"
  append(L"; i += 32)\n");
  append(L"  {\n");
  append(L"    var j = i;\n");
  append(L"    var i0 = (i >> 5) * ");
                                                            #line 454 "CodeGeneratorJavascript.cpp.template"
                                                              print(variable("transitionStateCount").integer());
                                                            #line 774 "CodeGeneratorJavascript.cpp"
  append(L" + ");
                                                            #line 455 "CodeGeneratorJavascript.cpp.template"
                                                              if (variable("nolexer").boolean())
                                                              {
                                                            #line 779 "CodeGeneratorJavascript.cpp"
  append(L"tokenSetId");
                                                            #line 457 "CodeGeneratorJavascript.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 785 "CodeGeneratorJavascript.cpp"
  append(L"s - 1");
                                                            #line 460 "CodeGeneratorJavascript.cpp.template"
                                                              }
                                                            #line 789 "CodeGeneratorJavascript.cpp"
  append(L";\n");
                                                            #line 462 "CodeGeneratorJavascript.cpp.template"
                                                              compressedMapAccessor(4, "i", "var f = ", "EXPECTED", &variable("t0bits").integer());
                                                            #line 793 "CodeGeneratorJavascript.cpp"
  append(L"\n");
  append(L"    for ( ; f != 0; f >>>= 1, ++j)\n");
  append(L"    {\n");
  append(L"      if ((f & 1) != 0)\n");
  append(L"      {\n");
  append(L"        set.push(");
                                                            #line 468 "CodeGeneratorJavascript.cpp.template"
                                                              print(variable("classname").string());
                                                            #line 802 "CodeGeneratorJavascript.cpp"
  append(L".TOKEN[j]);\n");
  append(L"      }\n");
  append(L"    }\n");
  append(L"  }\n");
  append(L"  return set;\n");
  append(L"};\n");
                                                            #line 475 "CodeGeneratorJavascript.cpp.template"
                                                              if (variable("tree").boolean())
                                                              {
                                                                if (variable("lrparser").boolean())
                                                                {
                                                            #line 814 "CodeGeneratorJavascript.cpp"
  append(L"\n");
                                                            #line 480 "CodeGeneratorJavascript.cpp.template"
                                                                  print(variable("classname").string());
                                                            #line 818 "CodeGeneratorJavascript.cpp"
  append(L".ParseTreeBuilder = function()\n");
  append(L"{\n");
  append(L"  var input;\n");
  append(L"  var stack;\n");
  append(L"  var top;\n");
                                                            #line 486 "CodeGeneratorJavascript.cpp.template"
                                                                  if (variable("useGlr").boolean() && ! variable("resolvesAmbiguity").boolean())
                                                                  {
                                                            #line 827 "CodeGeneratorJavascript.cpp"
  append(L"\n");
  append(L"  this.getStack = function() {return stack;}\n");
  append(L"  this.getTop = function() {return top;}\n");
                                                            #line 491 "CodeGeneratorJavascript.cpp.template"
                                                                  }
                                                            #line 833 "CodeGeneratorJavascript.cpp"
  append(L"\n");
  append(L"  this.reset = function(string)\n");
  append(L"  {\n");
  append(L"    input = string;\n");
  append(L"    stack = [];\n");
  append(L"    top = -1;\n");
  append(L"  };\n");
  append(L"\n");
  append(L"  this.nonterminal = function(name, begin, end, count)\n");
  append(L"  {");
                                                            #line 501 "CodeGeneratorJavascript.cpp.template"
                                                                  if (variable("useGlr").boolean() && ! variable("resolvesAmbiguity").boolean())
                                                                  {
                                                            #line 847 "CodeGeneratorJavascript.cpp"
  append(L"\n");
  append(L"    if (count > top + 1)\n");
  append(L"    {\n");
  append(L"      var content = this.pop(top + 1);\n");
  append(L"      this.nonterminal(\"UNAMBIGUOUS\", begin, content.length == 0 ? end : content[0].begin, 0);\n");
  append(L"      for (var i = 0; i < content.length; ++i)\n");
  append(L"      {\n");
  append(L"        this.push(content[i]);\n");
  append(L"      }\n");
  append(L"      count = top + 1;\n");
  append(L"    }");
                                                            #line 513 "CodeGeneratorJavascript.cpp.template"
                                                                  }
                                                            #line 861 "CodeGeneratorJavascript.cpp"
  append(L"\n");
  append(L"    this.push(new ");
                                                            #line 515 "CodeGeneratorJavascript.cpp.template"
                                                                  print(variable("classname").string());
                                                            #line 866 "CodeGeneratorJavascript.cpp"
  append(L".Nonterminal(name, begin, end, this.pop(count)));\n");
  append(L"  };\n");
                                                            #line 518 "CodeGeneratorJavascript.cpp.template"
                                                                  if (variable("useGlr").boolean() && variable("resolvesAmbiguity").boolean())
                                                                  {
                                                            #line 872 "CodeGeneratorJavascript.cpp"
  append(L"\n");
  append(L"  this.ambiguity = function(begin, end)\n");
  append(L"  {\n");
  append(L"  };\n");
                                                            #line 524 "CodeGeneratorJavascript.cpp.template"
                                                                  }
                                                            #line 879 "CodeGeneratorJavascript.cpp"
  append(L"\n");
  append(L"  this.terminal = function(name, begin, end)\n");
  append(L"  {\n");
  append(L"    this.push(new ");
                                                            #line 528 "CodeGeneratorJavascript.cpp.template"
                                                                  print(variable("classname").string());
                                                            #line 886 "CodeGeneratorJavascript.cpp"
  append(L".Terminal(name, begin, end));\n");
  append(L"  };\n");
  append(L"\n");
  append(L"  this.serialize = function(e)\n");
  append(L"  {\n");
  append(L"    e.reset(input);\n");
  append(L"    for (var i = 0; i <= top; ++i)\n");
  append(L"    {\n");
  append(L"      stack[i].send(e);\n");
  append(L"    }\n");
  append(L"  };\n");
  append(L"\n");
  append(L"  this.push = function(s)\n");
  append(L"  {\n");
  append(L"    stack[++top] = s;\n");
  append(L"  };\n");
  append(L"\n");
  append(L"  this.pop = function(count)\n");
  append(L"  {\n");
  append(L"    top -= count;\n");
  append(L"    return stack.slice(top + 1, top + 1 + count);\n");
  append(L"  };\n");
  append(L"};\n");
                                                            #line 552 "CodeGeneratorJavascript.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 914 "CodeGeneratorJavascript.cpp"
  append(L"\n");
                                                            #line 556 "CodeGeneratorJavascript.cpp.template"
                                                                  print(variable("classname").string());
                                                            #line 918 "CodeGeneratorJavascript.cpp"
  append(L".TopDownTreeBuilder = function()\n");
  append(L"{\n");
  append(L"  var input = null;\n");
  append(L"  var stack = null;\n");
  append(L"\n");
  append(L"  this.reset = function(i)\n");
  append(L"  {\n");
  append(L"    input = i;\n");
  append(L"    stack = [];\n");
  append(L"  };\n");
  append(L"\n");
  append(L"  this.startNonterminal = function(name, begin)\n");
  append(L"  {\n");
  append(L"    var nonterminal = new ");
                                                            #line 570 "CodeGeneratorJavascript.cpp.template"
                                                                  print(variable("classname").string());
                                                            #line 935 "CodeGeneratorJavascript.cpp"
  append(L".Nonterminal(name, begin, begin, []);\n");
  append(L"    if (stack.length > 0) addChild(nonterminal);\n");
  append(L"    stack.push(nonterminal);\n");
  append(L"  };\n");
  append(L"\n");
  append(L"  this.endNonterminal = function(name, end)\n");
  append(L"  {\n");
  append(L"    stack[stack.length - 1].end = end;\n");
  append(L"    if (stack.length > 1) stack.pop();\n");
  append(L"  };\n");
  append(L"\n");
  append(L"  this.terminal = function(name, begin, end)\n");
  append(L"  {\n");
  append(L"    addChild(new ");
                                                            #line 584 "CodeGeneratorJavascript.cpp.template"
                                                                  print(variable("classname").string());
                                                            #line 952 "CodeGeneratorJavascript.cpp"
  append(L".Terminal(name, begin, end));\n");
  append(L"  };\n");
  append(L"\n");
  append(L"  this.whitespace = function(begin, end)\n");
  append(L"  {\n");
  append(L"  };\n");
  append(L"\n");
  append(L"  function addChild(s)\n");
  append(L"  {\n");
  append(L"    var current = stack[stack.length - 1];\n");
  append(L"    current.children.push(s);\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  this.serialize = function(e)\n");
  append(L"  {\n");
  append(L"    e.reset(input);\n");
  append(L"    stack[0].send(e);\n");
  append(L"  };\n");
  append(L"};\n");
                                                            #line 604 "CodeGeneratorJavascript.cpp.template"
                                                                }
                                                            #line 974 "CodeGeneratorJavascript.cpp"
  append(L"\n");
                                                            #line 606 "CodeGeneratorJavascript.cpp.template"
                                                                print(variable("classname").string());
                                                            #line 978 "CodeGeneratorJavascript.cpp"
  append(L".Terminal = function(name, begin, end)\n");
  append(L"{\n");
  append(L"  this.begin = begin;\n");
  append(L"  this.end = end;\n");
  append(L"\n");
  append(L"  this.send = function(e)\n");
  append(L"  {\n");
  append(L"    e.terminal(name, begin, end);\n");
  append(L"  };\n");
  append(L"};\n");
  append(L"\n");
                                                            #line 618 "CodeGeneratorJavascript.cpp.template"
                                                                print(variable("classname").string());
                                                            #line 992 "CodeGeneratorJavascript.cpp"
  append(L".Nonterminal = function(name, begin, end, children)\n");
  append(L"{\n");
  append(L"  this.begin = begin;\n");
  append(L"  this.end = end;\n");
  append(L"\n");
  append(L"  this.send = function(e)\n");
  append(L"  {\n");
  append(L"    e.startNonterminal(name, begin);\n");
  append(L"    var pos = begin;\n");
  append(L"    children.forEach\n");
  append(L"    (\n");
  append(L"      function(c)\n");
  append(L"      {\n");
  append(L"        if (pos < c.begin) e.whitespace(pos, c.begin);\n");
  append(L"        c.send(e);\n");
  append(L"        pos = c.end;\n");
  append(L"      }\n");
  append(L"    );\n");
  append(L"    if (pos < end) e.whitespace(pos, end);\n");
  append(L"    e.endNonterminal(name, end);\n");
  append(L"  };\n");
  append(L"};\n");
                                                            #line 641 "CodeGeneratorJavascript.cpp.template"
                                                              }
                                                              for (VarsInInsertionOrder::iterator a(varsInInsertionOrder.begin());
                                                                   a != varsInInsertionOrder.end(); ++a)
                                                                if (a->isArray() && a->size > 0 && a->hasType(CGVariable::INTEGER) && strlen(a->name) == 2)
                                                              {
                                                            #line 1021 "CodeGeneratorJavascript.cpp"
  append(L"\n");
                                                            #line 647 "CodeGeneratorJavascript.cpp.template"
                                                                print(variable("classname").string());
                                                            #line 1025 "CodeGeneratorJavascript.cpp"
  append(L".");
                                                            #line 648 "CodeGeneratorJavascript.cpp.template"
                                                                print(a->getLongName());
                                                            #line 1029 "CodeGeneratorJavascript.cpp"
  append(L" =\n");
  append(L"[");
                                                            #line 650 "CodeGeneratorJavascript.cpp.template"
                                                                int w = (int) Format::width(a->size);
                                                                for (size_t j = 0; j < a->size; ++j)
                                                                {
                                                                  if (j == 0 || lineLength() + Format::width(a->integer(j)) + 2 > 119)
                                                                  {
                                                                    if (j) print(",");
                                                            #line 1039 "CodeGeneratorJavascript.cpp"
  append(L"\n");
  append(L"  /* ");
                                                            #line 657 "CodeGeneratorJavascript.cpp.template"
                                                                    print(format.toString<char>(j, 10, w));
                                                            #line 1044 "CodeGeneratorJavascript.cpp"
  append(L" */ ");
                                                            #line 658 "CodeGeneratorJavascript.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 1050 "CodeGeneratorJavascript.cpp"
  append(L", ");
                                                            #line 661 "CodeGeneratorJavascript.cpp.template"
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
                                                            #line 1063 "CodeGeneratorJavascript.cpp"
  append(L"\n");
  append(L"];\n");
                                                            #line 673 "CodeGeneratorJavascript.cpp.template"
                                                              }
                                                              for (VarsInInsertionOrder::iterator a(varsInInsertionOrder.begin());
                                                                   a != varsInInsertionOrder.end(); ++a)
                                                                if (a->isArray() && a->size > 0 && a->hasType(CGVariable::STRING) && strlen(a->name) == 2)
                                                              {
                                                            #line 1072 "CodeGeneratorJavascript.cpp"
  append(L"\n");
                                                            #line 679 "CodeGeneratorJavascript.cpp.template"
                                                                print(variable("classname").string());
                                                            #line 1076 "CodeGeneratorJavascript.cpp"
  append(L".");
                                                            #line 680 "CodeGeneratorJavascript.cpp.template"
                                                                print(a->getLongName());
                                                            #line 1080 "CodeGeneratorJavascript.cpp"
  append(L" =\n");
  append(L"[\n");
                                                            #line 683 "CodeGeneratorJavascript.cpp.template"
                                                                for (size_t j = 0; j < a->size; ++j)
                                                                {
                                                                  if (j)
                                                                  {
                                                            #line 1088 "CodeGeneratorJavascript.cpp"
  append(L",\n");
                                                            #line 688 "CodeGeneratorJavascript.cpp.template"
                                                                  }
                                                            #line 1092 "CodeGeneratorJavascript.cpp"
  append(L"  ");
                                                            #line 689 "CodeGeneratorJavascript.cpp.template"
                                                                  print(variable("stringPrefix").string());
                                                            #line 1096 "CodeGeneratorJavascript.cpp"
  append(L"\"");
                                                            #line 690 "CodeGeneratorJavascript.cpp.template"
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
                                                            #line 1111 "CodeGeneratorJavascript.cpp"
  append(L"\"");
                                                            #line 702 "CodeGeneratorJavascript.cpp.template"
                                                                  print(variable("stringSuffix").string());
                                                                }
                                                            #line 1116 "CodeGeneratorJavascript.cpp"
  append(L"\n");
  append(L"];\n");
                                                            #line 706 "CodeGeneratorJavascript.cpp.template"
                                                              }
                                                              if (! variable("embedded").boolean())
                                                              {
                                                            #line 1123 "CodeGeneratorJavascript.cpp"
  append(L"\n");
  append(L"var ");
                                                            #line 710 "CodeGeneratorJavascript.cpp.template"
                                                                print(variable("classname").string());
                                                            #line 1128 "CodeGeneratorJavascript.cpp"
  append(L".Token =\n");
  append(L"{\n");
  append(L"  ");
                                                            #line 713 "CodeGeneratorJavascript.cpp.template"
                                                                const CGVariable &token = variable("token");
                                                                int w = (int) Format::width(token.size);
                                                                for (size_t i = 0; i < token.size; ++i)
                                                                {
                                                                  if (i)
                                                                  {
                                                            #line 1139 "CodeGeneratorJavascript.cpp"
  append(L",\n");
  append(L"  ");
                                                            #line 720 "CodeGeneratorJavascript.cpp.template"
                                                                  }
                                                                  print(token.string(i));
                                                            #line 1145 "CodeGeneratorJavascript.cpp"
  append(L":");
                                                            #line 722 "CodeGeneratorJavascript.cpp.template"
                                                                  print(format.toString<char>(i, 10, w));
                                                                }
                                                            #line 1150 "CodeGeneratorJavascript.cpp"
  append(L"\n");
  append(L"};\n");
                                                            #line 726 "CodeGeneratorJavascript.cpp.template"
                                                              }
                                                            }

                                                            void CodeGeneratorJavascript::generateData()
                                                            {
                                                            }

// End
