// This file was generated on Sun Jan 26, 2025 19:55 (UTC+01) by REx v6.1 which is Copyright (c) 1979-2025 by Gunther Rademacher <grd@gmx.net>
// REx command line: CodeGeneratorHaxe.cpp.template
                                                            #line 1 "CodeGeneratorHaxe.cpp.template"
                                                            // generate CodeGeneratorHaxe.cpp using this command:
                                                            //
                                                            //   REx CodeGeneratorHaxe.cpp.template

                                                            #include "../common/Memory.hpp"

                                                            #include "CodeGenerator.hpp"

                                                            void CodeGeneratorHaxe::generateInstanceCode()
                                                            {
                                                              isHaxe = true;
                                                              if (! variable("append").boolean() && ! variable("embedded").boolean())
                                                              {
                                                                if (*variable("package").string())
                                                                {
                                                            #line 20 "CodeGeneratorHaxe.cpp"
  append(L"package ");
                                                            #line 16 "CodeGeneratorHaxe.cpp.template"
                                                                  print(variable("package").string());
                                                            #line 24 "CodeGeneratorHaxe.cpp"
  append(L";\n");
  append(L"\n");
                                                            #line 19 "CodeGeneratorHaxe.cpp.template"
                                                                }
                                                            #line 29 "CodeGeneratorHaxe.cpp"
  append(L"public class ");
                                                            #line 20 "CodeGeneratorHaxe.cpp.template"
                                                                print(variable("classname").string());
                                                            #line 33 "CodeGeneratorHaxe.cpp"
  append(L"\n");
  append(L"{\n");
                                                            #line 23 "CodeGeneratorHaxe.cpp.template"
                                                              }
                                                              if (! variable("useGlr").boolean())
                                                              {
                                                            #line 40 "CodeGeneratorHaxe.cpp"
  append(L"  private var input: Bytes = null;");
                                                            #line 26 "CodeGeneratorHaxe.cpp.template"
                                                                if (! variable("nolexer").boolean())
                                                                {
                                                            #line 45 "CodeGeneratorHaxe.cpp"
  append(L"\n");
  append(L"  private var size = 0;");
                                                            #line 29 "CodeGeneratorHaxe.cpp.template"
                                                                }
                                                              }
                                                            #line 51 "CodeGeneratorHaxe.cpp"
  append(L"\n");
  append(L"  private var begin = 0;\n");
  append(L"  private var end = 0;");
                                                            #line 33 "CodeGeneratorHaxe.cpp.template"
                                                              if (variable("nolexer").boolean())
                                                              {
                                                            #line 58 "CodeGeneratorHaxe.cpp"
  append(L"\n");
  append(L"  private var lexer: Lexer = null;\n");
  append(L"  private var token = new Token();");
                                                            #line 37 "CodeGeneratorHaxe.cpp.template"
                                                              }
                                                              if (! variable("embedded").boolean())
                                                              {
                                                            #line 66 "CodeGeneratorHaxe.cpp"
  append(L"\n");
  append(L"  private var state = 0;");
                                                            #line 41 "CodeGeneratorHaxe.cpp.template"
                                                              }
                                                            #line 71 "CodeGeneratorHaxe.cpp"
  append(L"\n");
                                                            #line 44 "CodeGeneratorHaxe.cpp.template"
                                                              if (! variable("embedded").boolean())
                                                              {
                                                            #line 76 "CodeGeneratorHaxe.cpp"
  append(L"\n");
  append(L"  public void init(String string)\n");
  append(L"  {\n");
  append(L"    input = Bytes.ofString(string);\n");
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
                                                            #line 64 "CodeGeneratorHaxe.cpp.template"
                                                              }
                                                              else
                                                              {
                                                                if (variable("lrparser").boolean() ||
                                                                    variable("tables").boolean())
                                                                {
                                                            #line 103 "CodeGeneratorHaxe.cpp"
  append(L"\n");
  append(L"  private function predict(dpi: Int): Int");
                                                            #line 71 "CodeGeneratorHaxe.cpp.template"
                                                                  predict();
                                                                }
                                                            #line 109 "CodeGeneratorHaxe.cpp"
  append(L"\n");
  append(L"  private");
                                                            #line 75 "CodeGeneratorHaxe.cpp.template"
                                                              }
                                                            #line 114 "CodeGeneratorHaxe.cpp"
  append(L" function match(tokenSetId: Int): Int\n");
  append(L"  {");
                                                            #line 77 "CodeGeneratorHaxe.cpp.template"
                                                              if (variable("nolexer").boolean())
                                                              {
                                                            #line 120 "CodeGeneratorHaxe.cpp"
  append(L"\n");
  append(L"    token.begin = end;\n");
  append(L"    lexer.match(tokenSetId, token);\n");
  append(L"    begin = token.begin;\n");
  append(L"    end = token.end;\n");
  append(L"    return token.code >= 0\n");
  append(L"         ? token.code\n");
  append(L"         : error(begin, end, - tokenSetId, -1, -1);\n");
  append(L"  }\n");
                                                            #line 88 "CodeGeneratorHaxe.cpp.template"
                                                              }
                                                              else
                                                              {
                                                                if (variable("trace").boolean())
                                                                {
                                                            #line 136 "CodeGeneratorHaxe.cpp"
  append(L"\n");
  append(L"    trace(\"  <tokenize ");
                                                            #line 94 "CodeGeneratorHaxe.cpp.template"
                                                                  if (variable("useGlr").boolean())
                                                                  {
                                                            #line 142 "CodeGeneratorHaxe.cpp"
  append(L"thread=\\\"\" + id + \"\\\" ");
                                                            #line 96 "CodeGeneratorHaxe.cpp.template"
                                                                  }
                                                            #line 146 "CodeGeneratorHaxe.cpp"
  append(L"tokenset=\\\"\" + tokenSetId + \"\\\">\");\n");
                                                            #line 98 "CodeGeneratorHaxe.cpp.template"
                                                                }
                                                                int lookahead = variable("maxcontextlength").integer();
                                                                bool hasFixedTokenLength = variable("hasfixedtokenlength").boolean();
                                                                if (lookahead)
                                                                {
                                                            #line 154 "CodeGeneratorHaxe.cpp"
  append(L"\n");
  append(L"    var nonascii = false;");
                                                            #line 104 "CodeGeneratorHaxe.cpp.template"
                                                                }
                                                            #line 159 "CodeGeneratorHaxe.cpp"
  append(L"\n");
  append(L"    begin = end;\n");
  append(L"    var current = end;\n");
  append(L"    var result = ");
                                                            #line 108 "CodeGeneratorHaxe.cpp.template"
                                                                CString classNamePrefix;
                                                                CString instancePrefix;
                                                                if (variable("useGlr").boolean())
                                                                {
                                                                  classNamePrefix += variable("classname").string();
                                                                  classNamePrefix += ".";
                                                                  instancePrefix += "parser.";
                                                                }
                                                                print(classNamePrefix.c_str());
                                                            #line 174 "CodeGeneratorHaxe.cpp"
  append(L"INITIAL[tokenSetId];");
                                                            #line 117 "CodeGeneratorHaxe.cpp.template"
                                                                if (variable("embedded").boolean())
                                                                {
                                                            #line 179 "CodeGeneratorHaxe.cpp"
  append(L"\n");
  append(L"    var state = 0;");
                                                            #line 120 "CodeGeneratorHaxe.cpp.template"
                                                                }
                                                            #line 184 "CodeGeneratorHaxe.cpp"
  append(L"\n");
                                                            #line 122 "CodeGeneratorHaxe.cpp.template"
                                                                if (variable("trace").boolean())
                                                                {
                                                            #line 189 "CodeGeneratorHaxe.cpp"
  append(L"\n");
  append(L"    var traceLine = \"    <next state=\\\"\" + (result & ");
                                                            #line 125 "CodeGeneratorHaxe.cpp.template"
                                                                  print(Math::powerof(2, variable("stateCodeBits").integer()) - 1);
                                                            #line 194 "CodeGeneratorHaxe.cpp"
  append(L") + \"\\\"\";");
                                                            #line 127 "CodeGeneratorHaxe.cpp.template"
                                                                }
                                                            #line 198 "CodeGeneratorHaxe.cpp"
  append(L"\n");
  append(L"    var code = result & ");
                                                            #line 129 "CodeGeneratorHaxe.cpp.template"
                                                                print(Math::powerof(2, variable("stateCodeBits").integer()) - 1);
                                                            #line 203 "CodeGeneratorHaxe.cpp"
  append(L";\n");
  append(L"    while (code != 0)\n");
  append(L"    {\n");
  append(L"      var charclass = 0;\n");
  append(L"      var c0 = current < ");
                                                            #line 134 "CodeGeneratorHaxe.cpp.template"
                                                                print(instancePrefix.c_str());
                                                            #line 211 "CodeGeneratorHaxe.cpp"
  append(L"size ? ");
                                                            #line 135 "CodeGeneratorHaxe.cpp.template"
                                                                print(instancePrefix.c_str());
                                                            #line 215 "CodeGeneratorHaxe.cpp"
  append(L"input.get(current) : 0;");
                                                            #line 136 "CodeGeneratorHaxe.cpp.template"
                                                                if (variable("trace").boolean())
                                                                {
                                                            #line 220 "CodeGeneratorHaxe.cpp"
  append(L"\n");
  append(L"      traceLine += \" offset=\\\"\" + current + \"\\\"\";");
                                                            #line 140 "CodeGeneratorHaxe.cpp.template"
                                                                }
                                                            #line 225 "CodeGeneratorHaxe.cpp"
  append(L"\n");
  append(L"      ++current;\n");
  append(L"      if (c0 < 0x");
                                                            #line 143 "CodeGeneratorHaxe.cpp.template"
                                                                print(format.toString<char>(variable("simplifiedCodeMap").integer(), 16, 0, 0, 0, "0123456789abcdef"));
                                                            #line 231 "CodeGeneratorHaxe.cpp"
  append(L")\n");
  append(L"      {");
                                                            #line 145 "CodeGeneratorHaxe.cpp.template"
                                                                if (variable("trace").boolean())
                                                                {
                                                            #line 237 "CodeGeneratorHaxe.cpp"
  append(L"\n");
  append(L"        if (c0 >= 32 && c0 <= 126)\n");
  append(L"        {\n");
  append(L"          traceLine += \" char=\\\"\" + ");
                                                            #line 150 "CodeGeneratorHaxe.cpp.template"
                                                                  print(classNamePrefix.c_str());
                                                            #line 244 "CodeGeneratorHaxe.cpp"
  append(L"xmlEscape(String.fromCharCode(c0)) + \"\\\"\";\n");
  append(L"        }");
                                                            #line 152 "CodeGeneratorHaxe.cpp.template"
                                                                }
                                                            #line 249 "CodeGeneratorHaxe.cpp"
  append(L"\n");
  append(L"        charclass = ");
                                                            #line 154 "CodeGeneratorHaxe.cpp.template"
                                                                print(classNamePrefix.c_str());
                                                            #line 254 "CodeGeneratorHaxe.cpp"
  append(L"MAP0[c0];\n");
  append(L"      }\n");
  append(L"      else\n");
  append(L"      {");
                                                            #line 158 "CodeGeneratorHaxe.cpp.template"
                                                                if (lookahead)
                                                                {
                                                            #line 262 "CodeGeneratorHaxe.cpp"
  append(L"\n");
  append(L"        nonascii = true;");
                                                            #line 161 "CodeGeneratorHaxe.cpp.template"
                                                                }
                                                            #line 267 "CodeGeneratorHaxe.cpp"
  append(L"\n");
  append(L"        if      ((c0");
                                                            #line 163 "CodeGeneratorHaxe.cpp.template"
                                                                print(instancePrefix.size(), " ");
                                                            #line 272 "CodeGeneratorHaxe.cpp"
  append(L"                     & 0xe0) == 0xc0\n");
  append(L"              && (");
                                                            #line 165 "CodeGeneratorHaxe.cpp.template"
                                                                print(instancePrefix.c_str());
                                                            #line 277 "CodeGeneratorHaxe.cpp"
  append(L"input.get(current    ) & 0xc0) == 0x80)\n");
  append(L"        {\n");
  append(L"          c0 = ((c0");
                                                            #line 168 "CodeGeneratorHaxe.cpp.template"
                                                                print(instancePrefix.size(), " ");
                                                            #line 283 "CodeGeneratorHaxe.cpp"
  append(L"                     & 0x1f) << 6)\n");
  append(L"             |  (");
                                                            #line 170 "CodeGeneratorHaxe.cpp.template"
                                                                print(instancePrefix.c_str());
                                                            #line 288 "CodeGeneratorHaxe.cpp"
  append(L"input.get(current    ) & 0x3f);\n");
  append(L"          if (c0 < 0x80) c0 = -1; else ++current;\n");
  append(L"        }\n");
  append(L"        else if ((c0");
                                                            #line 174 "CodeGeneratorHaxe.cpp.template"
                                                                print(instancePrefix.size(), " ");
                                                            #line 295 "CodeGeneratorHaxe.cpp"
  append(L"                     & 0xf0) == 0xe0\n");
  append(L"              && (");
                                                            #line 176 "CodeGeneratorHaxe.cpp.template"
                                                                print(instancePrefix.c_str());
                                                            #line 300 "CodeGeneratorHaxe.cpp"
  append(L"input.get(current    ) & 0xc0) == 0x80\n");
  append(L"              && (");
                                                            #line 178 "CodeGeneratorHaxe.cpp.template"
                                                                print(instancePrefix.c_str());
                                                            #line 305 "CodeGeneratorHaxe.cpp"
  append(L"input.get(current + 1) & 0xc0) == 0x80)\n");
  append(L"        {\n");
  append(L"          c0 = ((c0");
                                                            #line 181 "CodeGeneratorHaxe.cpp.template"
                                                                print(instancePrefix.size(), " ");
                                                            #line 311 "CodeGeneratorHaxe.cpp"
  append(L"                     & 0x0f) << 12)\n");
  append(L"             | ((");
                                                            #line 183 "CodeGeneratorHaxe.cpp.template"
                                                                print(instancePrefix.c_str());
                                                            #line 316 "CodeGeneratorHaxe.cpp"
  append(L"input.get(current    ) & 0x3f) <<  6)\n");
  append(L"             |  (");
                                                            #line 185 "CodeGeneratorHaxe.cpp.template"
                                                                print(instancePrefix.c_str());
                                                            #line 321 "CodeGeneratorHaxe.cpp"
  append(L"input.get(current + 1) & 0x3f);\n");
  append(L"          if (c0 < 0x800) c0 = -1; else current += 2;\n");
  append(L"        }\n");
  append(L"        else if ((c0");
                                                            #line 189 "CodeGeneratorHaxe.cpp.template"
                                                                print(instancePrefix.size(), " ");
                                                            #line 328 "CodeGeneratorHaxe.cpp"
  append(L"                     & 0xf8) == 0xf0\n");
  append(L"              && (");
                                                            #line 191 "CodeGeneratorHaxe.cpp.template"
                                                                print(instancePrefix.c_str());
                                                            #line 333 "CodeGeneratorHaxe.cpp"
  append(L"input.get(current    ) & 0xc0) == 0x80\n");
  append(L"              && (");
                                                            #line 193 "CodeGeneratorHaxe.cpp.template"
                                                                print(instancePrefix.c_str());
                                                            #line 338 "CodeGeneratorHaxe.cpp"
  append(L"input.get(current + 1) & 0xc0) == 0x80\n");
  append(L"              && (");
                                                            #line 195 "CodeGeneratorHaxe.cpp.template"
                                                                print(instancePrefix.c_str());
                                                            #line 343 "CodeGeneratorHaxe.cpp"
  append(L"input.get(current + 2) & 0xc0) == 0x80)\n");
  append(L"        {\n");
  append(L"          c0 = ((c0");
                                                            #line 198 "CodeGeneratorHaxe.cpp.template"
                                                                print(instancePrefix.size(), " ");
                                                            #line 349 "CodeGeneratorHaxe.cpp"
  append(L"                     & 0x07) << 18)\n");
  append(L"             | ((");
                                                            #line 200 "CodeGeneratorHaxe.cpp.template"
                                                                print(instancePrefix.c_str());
                                                            #line 354 "CodeGeneratorHaxe.cpp"
  append(L"input.get(current    ) & 0x3f) << 12)\n");
  append(L"             | ((");
                                                            #line 202 "CodeGeneratorHaxe.cpp.template"
                                                                print(instancePrefix.c_str());
                                                            #line 359 "CodeGeneratorHaxe.cpp"
  append(L"input.get(current + 1) & 0x3f) <<  6)\n");
  append(L"             | ( ");
                                                            #line 204 "CodeGeneratorHaxe.cpp.template"
                                                                print(instancePrefix.c_str());
                                                            #line 364 "CodeGeneratorHaxe.cpp"
  append(L"input.get(current + 2) & 0x3f       );\n");
  append(L"          if (c0 < 0x10000 || c0 > 0x10ffff) c0 = -1; else current += 3;\n");
  append(L"        }\n");
  append(L"\n");
  append(L"        if (c0 < 0x");
                                                            #line 209 "CodeGeneratorHaxe.cpp.template"
                                                                print(format.toString<char>(variable("uncompressedMapSize").integer(), 16, 0, 0, 0, "0123456789abcdef"));
                                                            #line 372 "CodeGeneratorHaxe.cpp"
  append(L")\n");
  append(L"        {\n");
                                                            #line 212 "CodeGeneratorHaxe.cpp.template"
                                                                CString map1(classNamePrefix);
                                                                map1 += "MAP1";
                                                                compressedMapAccessor(10, "c", "charclass = ", map1.c_str(), &variable("m1bits").integer());
                                                            #line 379 "CodeGeneratorHaxe.cpp"
  append(L"\n");
  append(L"        }\n");
  append(L"        else\n");
  append(L"        {");
                                                            #line 218 "CodeGeneratorHaxe.cpp.template"
                                                                if (variable("m2").size == 0)
                                                                {
                                                            #line 387 "CodeGeneratorHaxe.cpp"
  append(L"\n");
  append(L"          charclass = 0;");
                                                            #line 221 "CodeGeneratorHaxe.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 394 "CodeGeneratorHaxe.cpp"
  append(L"\n");
  append(L"          var lo = 0, hi = ");
                                                            #line 225 "CodeGeneratorHaxe.cpp.template"
                                                                  print(variable("m2").size / 3 - 1);
                                                            #line 399 "CodeGeneratorHaxe.cpp"
  append(L";\n");
  append(L"          var m = ");
                                                            #line 227 "CodeGeneratorHaxe.cpp.template"
                                                                  print((variable("m2").size / 3) >> 1);
                                                            #line 404 "CodeGeneratorHaxe.cpp"
  append(L";\n");
  append(L"          while (true)\n");
  append(L"          {\n");
  append(L"            if (");
                                                            #line 231 "CodeGeneratorHaxe.cpp.template"
                                                                  print(classNamePrefix.c_str());
                                                            #line 411 "CodeGeneratorHaxe.cpp"
  append(L"MAP2[m] > c0) {hi = m - 1;}\n");
  append(L"            else if (");
                                                            #line 233 "CodeGeneratorHaxe.cpp.template"
                                                                  print(classNamePrefix.c_str());
                                                            #line 416 "CodeGeneratorHaxe.cpp"
  append(L"MAP2[");
                                                            #line 234 "CodeGeneratorHaxe.cpp.template"
                                                                  print(variable("m2").size / 3);
                                                            #line 420 "CodeGeneratorHaxe.cpp"
  append(L" + m] < c0) {lo = m + 1;}\n");
  append(L"            else {charclass = ");
                                                            #line 236 "CodeGeneratorHaxe.cpp.template"
                                                                  print(classNamePrefix.c_str());
                                                            #line 425 "CodeGeneratorHaxe.cpp"
  append(L"MAP2[");
                                                            #line 237 "CodeGeneratorHaxe.cpp.template"
                                                                  print(variable("m2").size / 3 * 2);
                                                            #line 429 "CodeGeneratorHaxe.cpp"
  append(L" + m]; break;}\n");
  append(L"            if (lo > hi) {charclass = 0; break;}\n");
  append(L"            m = (hi + lo) >> 1;\n");
  append(L"          }");
                                                            #line 241 "CodeGeneratorHaxe.cpp.template"
                                                                }
                                                            #line 436 "CodeGeneratorHaxe.cpp"
  append(L"\n");
  append(L"        }\n");
  append(L"      }");
                                                            #line 244 "CodeGeneratorHaxe.cpp.template"
                                                                if (variable("trace").boolean())
                                                                {
                                                            #line 443 "CodeGeneratorHaxe.cpp"
  append(L"\n");
  append(L"      traceLine += \" codepoint=\\\"\" + c0 + \"\\\" class=\\\"\" + charclass + \"\\\"\";");
                                                            #line 248 "CodeGeneratorHaxe.cpp.template"
                                                                }
                                                            #line 448 "CodeGeneratorHaxe.cpp"
  append(L"\n");
  append(L"\n");
  append(L"      state = code;\n");
                                                            #line 252 "CodeGeneratorHaxe.cpp.template"
                                                                CString transition(classNamePrefix);
                                                                transition += "TRANSITION";
                                                                compressedMap2dAccessor("code - 1", "charclass", variable("a1cols").integer(),
                                                                                           6, "i", "code = ", transition.c_str(), &variable("a1bits").integer());
                                                            #line 457 "CodeGeneratorHaxe.cpp"
  append(L"\n");
  append(L"\n");
  append(L"      if (code > ");
                                                            #line 258 "CodeGeneratorHaxe.cpp.template"
                                                                print(Math::powerof(2, variable("stateCodeBits").integer()) - 1);
                                                            #line 463 "CodeGeneratorHaxe.cpp"
  append(L")\n");
  append(L"      {\n");
  append(L"        result = code;");
                                                            #line 261 "CodeGeneratorHaxe.cpp.template"
                                                                if (variable("trace").boolean())
                                                                {
                                                            #line 470 "CodeGeneratorHaxe.cpp"
  append(L"\n");
  append(L"        traceLine += \" result=\\\"\" + ");
                                                            #line 264 "CodeGeneratorHaxe.cpp.template"
                                                                  print(classNamePrefix.c_str());
                                                            #line 475 "CodeGeneratorHaxe.cpp"
  append(L"xmlEscape(");
                                                            #line 265 "CodeGeneratorHaxe.cpp.template"
                                                                  print(classNamePrefix.c_str());
                                                            #line 479 "CodeGeneratorHaxe.cpp"
  append(L"TOKEN[((result >> ");
                                                            #line 267 "CodeGeneratorHaxe.cpp.template"
                                                                  print(variable("stateCodeBits").integer());
                                                            #line 483 "CodeGeneratorHaxe.cpp"
  append(L") & ");
                                                            #line 269 "CodeGeneratorHaxe.cpp.template"
                                                                  print(Math::powerof(2, variable("tokencodeBits").integer()) - 1);
                                                            #line 487 "CodeGeneratorHaxe.cpp"
  append(L") - 1]) + \"\\\"\";");
                                                            #line 271 "CodeGeneratorHaxe.cpp.template"
                                                                  if (lookahead || hasFixedTokenLength)
                                                                  {
                                                                    int contextOffset = variable("stateCodeBits").integer()
                                                                                      + variable("tokencodeBits").integer();
                                                                    int sizeOffset = contextOffset
                                                                                   + (hasFixedTokenLength ? 1 : 0);
                                                                    if (hasFixedTokenLength)
                                                                    {
                                                            #line 498 "CodeGeneratorHaxe.cpp"
  append(L"\n");
  append(L"        if ((result & ");
                                                            #line 280 "CodeGeneratorHaxe.cpp.template"
                                                                      print(Math::powerof(2, contextOffset));
                                                            #line 503 "CodeGeneratorHaxe.cpp"
  append(L") > 0)\n");
  append(L"        {\n");
  append(L"          traceLine += \" token-size=\\\"\" + (result >> ");
                                                            #line 283 "CodeGeneratorHaxe.cpp.template"
                                                                      print(sizeOffset);
                                                            #line 509 "CodeGeneratorHaxe.cpp"
  append(L") + \"\\\"\";\n");
  append(L"        }\n");
  append(L"        else ");
                                                            #line 286 "CodeGeneratorHaxe.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 517 "CodeGeneratorHaxe.cpp"
  append(L"\n");
  append(L"        ");
                                                            #line 290 "CodeGeneratorHaxe.cpp.template"
                                                                    }
                                                            #line 522 "CodeGeneratorHaxe.cpp"
  append(L"if ((result >> ");
                                                            #line 291 "CodeGeneratorHaxe.cpp.template"
                                                                    print(sizeOffset);
                                                            #line 526 "CodeGeneratorHaxe.cpp"
  append(L") > 0)\n");
  append(L"        {\n");
  append(L"          traceLine += \" trailing-context-size=\\\"\" + (result >> ");
                                                            #line 294 "CodeGeneratorHaxe.cpp.template"
                                                                    print(sizeOffset);
                                                            #line 532 "CodeGeneratorHaxe.cpp"
  append(L") + \"\\\"\";\n");
  append(L"        }");
                                                            #line 296 "CodeGeneratorHaxe.cpp.template"
                                                                  }
                                                                }
                                                            #line 538 "CodeGeneratorHaxe.cpp"
  append(L"\n");
  append(L"        code &= ");
                                                            #line 299 "CodeGeneratorHaxe.cpp.template"
                                                                print(Math::powerof(2, variable("stateCodeBits").integer()) - 1);
                                                            #line 543 "CodeGeneratorHaxe.cpp"
  append(L";\n");
  append(L"        end = current;\n");
  append(L"      }");
                                                            #line 302 "CodeGeneratorHaxe.cpp.template"
                                                                if (variable("trace").boolean())
                                                                {
                                                            #line 550 "CodeGeneratorHaxe.cpp"
  append(L"\n");
  append(L"      traceLine += \"/>\";\n");
  append(L"      trace(traceLine);\n");
  append(L"      if (code != 0)\n");
  append(L"      {\n");
  append(L"        traceLine = \"    <next state=\\\"\" + code + \"\\\"\";\n");
  append(L"      }");
                                                            #line 310 "CodeGeneratorHaxe.cpp.template"
                                                                }
                                                            #line 560 "CodeGeneratorHaxe.cpp"
  append(L"\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    result >>= ");
                                                            #line 314 "CodeGeneratorHaxe.cpp.template"
                                                                print(variable("stateCodeBits").integer());
                                                            #line 567 "CodeGeneratorHaxe.cpp"
  append(L";\n");
  append(L"    if (result == 0)\n");
  append(L"    {\n");
  append(L"      end = current - 1;\n");
  append(L"      var c1 = end < ");
                                                            #line 319 "CodeGeneratorHaxe.cpp.template"
                                                                print(instancePrefix.c_str());
                                                            #line 575 "CodeGeneratorHaxe.cpp"
  append(L"size ? ");
                                                            #line 320 "CodeGeneratorHaxe.cpp.template"
                                                                print(instancePrefix.c_str());
                                                            #line 579 "CodeGeneratorHaxe.cpp"
  append(L"input.get(end) : 0;\n");
  append(L"      if (c1 & 0xc0 == 0x80)\n");
  append(L"      {\n");
  append(L"        --end;\n");
  append(L"      }");
                                                            #line 325 "CodeGeneratorHaxe.cpp.template"
                                                                if (variable("trace").boolean())
                                                                {
                                                            #line 588 "CodeGeneratorHaxe.cpp"
  append(L"\n");
  append(L"      trace(\"    <fail begin=\\\"\" + begin + \"\\\" end=\\\"\" + end + \"\\\" state=\\\"\" + state + \"\\\"/>\");\n");
  append(L"      trace(\"  </tokenize>\");");
                                                            #line 329 "CodeGeneratorHaxe.cpp.template"
                                                                }
                                                                if (variable("embedded").boolean())
                                                                {
                                                                  if (variable("useGlr").boolean())
                                                                  {
                                                            #line 598 "CodeGeneratorHaxe.cpp"
  append(L"\n");
  append(L"      end = begin;\n");
  append(L"      return -1;");
                                                            #line 336 "CodeGeneratorHaxe.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 606 "CodeGeneratorHaxe.cpp"
  append(L"\n");
  append(L"      return error(begin, end, state, -1, -1);");
                                                            #line 340 "CodeGeneratorHaxe.cpp.template"
                                                                  }
                                                                }
                                                            #line 612 "CodeGeneratorHaxe.cpp"
  append(L"\n");
  append(L"    }");
                                                            #line 343 "CodeGeneratorHaxe.cpp.template"
                                                                int lowBits = variable("tokencodeBits").integer();
                                                                if (hasFixedTokenLength && ! lookahead)
                                                                {
                                                            #line 619 "CodeGeneratorHaxe.cpp"
  append(L"\n");
  append(L"    else if ((result & ");
                                                            #line 347 "CodeGeneratorHaxe.cpp.template"
                                                                  print(Math::powerof(2, lowBits));
                                                                  ++lowBits;
                                                            #line 625 "CodeGeneratorHaxe.cpp"
  append(L") != 0)\n");
  append(L"    {\n");
  append(L"      end = begin;\n");
  append(L"    }");
                                                            #line 352 "CodeGeneratorHaxe.cpp.template"
                                                                }
                                                                else
                                                                {
                                                                  if (hasFixedTokenLength)
                                                                  {
                                                            #line 636 "CodeGeneratorHaxe.cpp"
  append(L"\n");
  append(L"    else if ((result & ");
                                                            #line 358 "CodeGeneratorHaxe.cpp.template"
                                                                    print(Math::powerof(2, lowBits));
                                                                    ++lowBits;
                                                            #line 642 "CodeGeneratorHaxe.cpp"
  append(L") != 0)\n");
  append(L"    {\n");
  append(L"      end = begin;\n");
  append(L"      if (nonascii)\n");
  append(L"      {\n");
  append(L"        var i = result >> ");
                                                            #line 365 "CodeGeneratorHaxe.cpp.template"
                                                                    print(lowBits);
                                                            #line 651 "CodeGeneratorHaxe.cpp"
  append(L";\n");
  append(L"        while (i > 0)\n");
  append(L"        {\n");
  append(L"          var c1 = end < ");
                                                            #line 369 "CodeGeneratorHaxe.cpp.template"
                                                                    print(instancePrefix.c_str());
                                                            #line 658 "CodeGeneratorHaxe.cpp"
  append(L"size ? ");
                                                            #line 370 "CodeGeneratorHaxe.cpp.template"
                                                                    print(instancePrefix.c_str());
                                                            #line 662 "CodeGeneratorHaxe.cpp"
  append(L"input.get(end) : 0;\n");
  append(L"          ++end;\n");
  append(L"          if (c1 & 0xc0 == 0x80)\n");
  append(L"          {\n");
  append(L"            ++end;\n");
  append(L"          }\n");
  append(L"          --i;\n");
  append(L"        }\n");
  append(L"      }\n");
  append(L"      else\n");
  append(L"      {\n");
  append(L"        end += (result >> ");
                                                            #line 382 "CodeGeneratorHaxe.cpp.template"
                                                                    print(lowBits);
                                                            #line 677 "CodeGeneratorHaxe.cpp"
  append(L");\n");
  append(L"      }\n");
  append(L"    }");
                                                            #line 385 "CodeGeneratorHaxe.cpp.template"
                                                                  }
                                                                  if (lookahead)
                                                                  {
                                                            #line 685 "CodeGeneratorHaxe.cpp"
  append(L"\n");
  append(L"    else if (nonascii)\n");
  append(L"    {\n");
  append(L"      var i = result >> ");
                                                            #line 391 "CodeGeneratorHaxe.cpp.template"
                                                                    print(lowBits);
                                                            #line 692 "CodeGeneratorHaxe.cpp"
  append(L";\n");
  append(L"      while(i > 0)\n");
  append(L"      {\n");
  append(L"        --end;\n");
  append(L"        var c1 = end < ");
                                                            #line 396 "CodeGeneratorHaxe.cpp.template"
                                                                   print(instancePrefix.c_str());
                                                            #line 700 "CodeGeneratorHaxe.cpp"
  append(L"size ? ");
                                                            #line 397 "CodeGeneratorHaxe.cpp.template"
                                                                   print(instancePrefix.c_str());
                                                            #line 704 "CodeGeneratorHaxe.cpp"
  append(L"input.get(end) : 0;\n");
  append(L"        if (c1  & 0xc0 == 0x80)\n");
  append(L"        {\n");
  append(L"          --end;\n");
  append(L"        }\n");
  append(L"        --i;\n");
  append(L"      }\n");
  append(L"    }\n");
  append(L"    else\n");
  append(L"    {\n");
  append(L"      end -= result >> ");
                                                            #line 408 "CodeGeneratorHaxe.cpp.template"
                                                                    print(lowBits);
                                                            #line 718 "CodeGeneratorHaxe.cpp"
  append(L";\n");
  append(L"    }");
                                                            #line 410 "CodeGeneratorHaxe.cpp.template"
                                                                  }
                                                                }
                                                            #line 724 "CodeGeneratorHaxe.cpp"
  append(L"\n");
  append(L"\n");
  append(L"    if (end > ");
                                                            #line 414 "CodeGeneratorHaxe.cpp.template"
                                                                print(instancePrefix.c_str());
                                                            #line 730 "CodeGeneratorHaxe.cpp"
  append(L"size) end = ");
                                                            #line 415 "CodeGeneratorHaxe.cpp.template"
                                                                print(instancePrefix.c_str());
                                                            #line 734 "CodeGeneratorHaxe.cpp"
  append(L"size;");
                                                            #line 416 "CodeGeneratorHaxe.cpp.template"
                                                                if (variable("trace").boolean())
                                                                {
                                                            #line 739 "CodeGeneratorHaxe.cpp"
  append(L"\n");
  append(L"    trace(\"    <done result=\\\"\" + ");
                                                            #line 419 "CodeGeneratorHaxe.cpp.template"
                                                                  print(classNamePrefix.c_str());
                                                            #line 744 "CodeGeneratorHaxe.cpp"
  append(L"xmlEscape(");
                                                            #line 420 "CodeGeneratorHaxe.cpp.template"
                                                                  print(classNamePrefix.c_str());
                                                            #line 748 "CodeGeneratorHaxe.cpp"
  append(L"TOKEN[(result & ");
                                                            #line 421 "CodeGeneratorHaxe.cpp.template"
                                                                  print(Math::powerof(2, variable("tokencodeBits").integer()) - 1);
                                                            #line 752 "CodeGeneratorHaxe.cpp"
  append(L") - 1]) + \"\\\" begin=\\\"\" + begin + \"\\\" end=\\\"\" + end + \"\\\"/>\");\n");
  append(L"    trace(\"  </tokenize>\");");
                                                            #line 424 "CodeGeneratorHaxe.cpp.template"
                                        }
                                                                const char *flags = getenv("FLAGS");
                                                                bool hack = flags && strchr(flags, 'H');
                                                                if (hack)
                                                                {
                                                            #line 761 "CodeGeneratorHaxe.cpp"
  append(L"\n");
  append(L"    return hack((result & ");
                                                            #line 430 "CodeGeneratorHaxe.cpp.template"
                                                                  print(Math::powerof(2, variable("tokencodeBits").integer()) - 1);
                                                            #line 766 "CodeGeneratorHaxe.cpp"
  append(L") - 1);\n");
  append(L"  }\n");
                                                            #line 433 "CodeGeneratorHaxe.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 773 "CodeGeneratorHaxe.cpp"
  append(L"\n");
  append(L"    return (result & ");
                                                            #line 437 "CodeGeneratorHaxe.cpp.template"
                                                                  print(Math::powerof(2, variable("tokencodeBits").integer()) - 1);
                                                            #line 778 "CodeGeneratorHaxe.cpp"
  append(L") - 1;\n");
  append(L"  }\n");
                                                            #line 440 "CodeGeneratorHaxe.cpp.template"
                                                                }
                                                              }
                                                            }

                                                            void CodeGeneratorHaxe::generateStaticCode()
                                                            {
                                                              isHaxe = true;
                                                              const char *visibility = variable("useGlr").boolean() ? "public" : "private";
                                                              if (defined("gtbits"))
                                                              {
                                                            #line 792 "CodeGeneratorHaxe.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 451 "CodeGeneratorHaxe.cpp.template"
                                                                print(visibility);
                                                            #line 797 "CodeGeneratorHaxe.cpp"
  append(L" static function goTo(nonterminal, state): Int\n");
  append(L"  {\n");
                                                            #line 454 "CodeGeneratorHaxe.cpp.template"
                                                                compressedMap2dAccessor("nonterminal", "state", variable("gtcols").integer(),
                                                                                           4, "i", "return ", "GOTO", &variable("gtbits").integer());
                                                            #line 803 "CodeGeneratorHaxe.cpp"
  append(L"\n");
  append(L"  }\n");
                                                            #line 458 "CodeGeneratorHaxe.cpp.template"
                                                              }
                                                              if (! variable("embedded").boolean())
                                                              {
                                                            #line 810 "CodeGeneratorHaxe.cpp"
  append(L"\n");
  append(L"  public String[] getExpectedTokenSet()\n");
  append(L"  {\n");
  append(L"    return getTokenSet(- state);\n");
  append(L"  }\n");
                                                            #line 466 "CodeGeneratorHaxe.cpp.template"
                                                              }

                                                              if (variable("trace").boolean())
                                                              {
                                                            #line 821 "CodeGeneratorHaxe.cpp"
  append(L"\n");
  append(L"  public static function xmlEscape(s: String): String\n");
  append(L"  {\n");
  append(L"    var sb = new StringBuf();\n");
  append(L"    var i = 0;\n");
  append(L"    while (i < s.length)\n");
  append(L"    {\n");
  append(L"      var c = s.charAt(i++);\n");
  append(L"      switch (c)\n");
  append(L"      {\n");
  append(L"      case '<': sb.add(\"&lt;\");\n");
  append(L"      case '\"': sb.add(\"&quot;\");\n");
  append(L"      case '&': sb.add(\"&amp;\");\n");
  append(L"      default : sb.add(c);\n");
  append(L"      }\n");
  append(L"    }\n");
  append(L"    return sb.toString();\n");
  append(L"  }\n");
                                                            #line 488 "CodeGeneratorHaxe.cpp.template"
                                                              }

                                                              if (variable("nolexer").boolean())
                                                              {
                                                            #line 845 "CodeGeneratorHaxe.cpp"
  append(L"\n");
  append(L"  public static function getTokenCount() {return ");
                                                            #line 493 "CodeGeneratorHaxe.cpp.template"
                                                                print(variable("t1").size);
                                                            #line 850 "CodeGeneratorHaxe.cpp"
  append(L";}\n");
  append(L"  public static function getTokenName(code) {return code >= 0 && code < ");
                                                            #line 496 "CodeGeneratorHaxe.cpp.template"
                                                                print(variable("t1").size);
                                                            #line 855 "CodeGeneratorHaxe.cpp"
  append(L" ? TOKEN[code] : null;}\n");
  append(L"  public static function getTokenSetCount() {return ");
                                                            #line 498 "CodeGeneratorHaxe.cpp.template"
                                                                print(variable("entrycount").integer());
                                                            #line 860 "CodeGeneratorHaxe.cpp"
  append(L";}\n");
  append(L"\n");
  append(L"  public static function getTokenSet(tokenSetId)");
                                                            #line 501 "CodeGeneratorHaxe.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 868 "CodeGeneratorHaxe.cpp"
  append(L"\n");
  append(L"  private static function getTokenSet(tokenSetId)");
                                                            #line 505 "CodeGeneratorHaxe.cpp.template"
                                                              }
                                                            #line 873 "CodeGeneratorHaxe.cpp"
  append(L"\n");
  append(L"  {\n");
  append(L"    var set = [];");
                                                            #line 508 "CodeGeneratorHaxe.cpp.template"
                                                              if (! variable("nolexer").boolean())
                                                              {
                                                            #line 880 "CodeGeneratorHaxe.cpp"
  append(L"\n");
  append(L"    var s = tokenSetId < 0 ? - tokenSetId : INITIAL[tokenSetId] & ");
                                                            #line 512 "CodeGeneratorHaxe.cpp.template"
                                                                print(Math::powerof(2, variable("stateCodeBits").integer()) - 1);
                                                            #line 885 "CodeGeneratorHaxe.cpp"
  append(L";");
                                                            #line 514 "CodeGeneratorHaxe.cpp.template"
                                                              }
                                                            #line 889 "CodeGeneratorHaxe.cpp"
  append(L"\n");
  append(L"    var i = 0;\n");
  append(L"    while (i < ");
                                                            #line 517 "CodeGeneratorHaxe.cpp.template"
                                                              print(variable("t1").size);
                                                            #line 895 "CodeGeneratorHaxe.cpp"
  append(L")\n");
  append(L"    {\n");
  append(L"      var j = i;\n");
  append(L"      var i0 = (i >> 5) * ");
                                                            #line 521 "CodeGeneratorHaxe.cpp.template"
                                                              print(variable("transitionStateCount").integer());
                                                            #line 902 "CodeGeneratorHaxe.cpp"
  append(L" + ");
                                                            #line 522 "CodeGeneratorHaxe.cpp.template"
                                                              if (variable("nolexer").boolean())
                                                              {
                                                            #line 907 "CodeGeneratorHaxe.cpp"
  append(L"tokenSetId");
                                                            #line 524 "CodeGeneratorHaxe.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 913 "CodeGeneratorHaxe.cpp"
  append(L"s - 1");
                                                            #line 527 "CodeGeneratorHaxe.cpp.template"
                                                              }
                                                            #line 917 "CodeGeneratorHaxe.cpp"
  append(L";\n");
                                                            #line 529 "CodeGeneratorHaxe.cpp.template"
                                                              compressedMapAccessor(6, "i", "var f = ", "EXPECTED", &variable("t0bits").integer());
                                                            #line 921 "CodeGeneratorHaxe.cpp"
  append(L"\n");
  append(L"      while (f != 0)\n");
  append(L"      {\n");
  append(L"        if ((f & 1) != 0)\n");
  append(L"        {\n");
  append(L"          set.push(TOKEN[j]);\n");
  append(L"        }\n");
  append(L"        f >>>= 1;\n");
  append(L"        ++j;\n");
  append(L"      }\n");
  append(L"      i += 32;\n");
  append(L"    }\n");
  append(L"    return set;\n");
  append(L"  }");
                                                            #line 543 "CodeGeneratorHaxe.cpp.template"
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
                                                            #line 955 "CodeGeneratorHaxe.cpp"
  append(L"\n");
  append(L"\n");
  append(L"  ");
                                                            #line 563 "CodeGeneratorHaxe.cpp.template"
                                                                print(visibility);
                                                            #line 961 "CodeGeneratorHaxe.cpp"
  append(L" static var ");
                                                            #line 564 "CodeGeneratorHaxe.cpp.template"
                                                                print(a->longName);
                                                            #line 965 "CodeGeneratorHaxe.cpp"
  append(L" =\n");
  append(L"  [");
                                                            #line 566 "CodeGeneratorHaxe.cpp.template"
                                                                if (asString)
                                                                {
                                                            #line 971 "CodeGeneratorHaxe.cpp"
  append(L"\n");
  append(L"    for (s1 in [");
                                                            #line 569 "CodeGeneratorHaxe.cpp.template"
                                                                }
                                                                int w = (int) Format::width(a->size);
                                                                for (size_t j = 0; j < a->size; ++j)
                                                                {
                                                                  if (j == 0 || lineLength() + Format::width(a->integer(j)) + (asString ? 3 : 2) > limit)
                                                                  {
                                                                    if (j) print(asString ? "\"," : ",");
                                                            #line 982 "CodeGeneratorHaxe.cpp"
  append(L"\n");
                                                            #line 577 "CodeGeneratorHaxe.cpp.template"
                                                                    if (asString) print("  ");
                                                            #line 986 "CodeGeneratorHaxe.cpp"
  append(L"    /* ");
                                                            #line 578 "CodeGeneratorHaxe.cpp.template"
                                                                    print(format.toString<char>(j, 10, w));
                                                            #line 990 "CodeGeneratorHaxe.cpp"
  append(L" */ ");
                                                            #line 579 "CodeGeneratorHaxe.cpp.template"
                                                                    if (asString) print("\"");
                                                                  }
                                                                  else
                                                                  {
                                                            #line 997 "CodeGeneratorHaxe.cpp"
  append(L", ");
                                                            #line 583 "CodeGeneratorHaxe.cpp.template"
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
                                                            #line 1012 "CodeGeneratorHaxe.cpp"
  append(L"\"\n");
  append(L"    ])\n");
  append(L"    for (s2 in ");
  append(L"~");
  append(L"/, /g.split(s1)) Std.parseInt(s2)");
                                                            #line 597 "CodeGeneratorHaxe.cpp.template"
                                                                }
                                                            #line 1020 "CodeGeneratorHaxe.cpp"
  append(L"\n");
  append(L"  ];");
                                                            #line 599 "CodeGeneratorHaxe.cpp.template"
                                                              }
                                                              for (VarsInInsertionOrder::iterator a(varsInInsertionOrder.begin());
                                                                   a != varsInInsertionOrder.end(); ++a)
                                                                if (a->isArray() && a->size > 0 && a->hasType(CGVariable::STRING) && strlen(a->name) == 2)
                                                              {
                                                            #line 1029 "CodeGeneratorHaxe.cpp"
  append(L"\n");
  append(L"\n");
  append(L"  ");
                                                            #line 606 "CodeGeneratorHaxe.cpp.template"
                                                                print(visibility);
                                                            #line 1035 "CodeGeneratorHaxe.cpp"
  append(L" static var ");
                                                            #line 607 "CodeGeneratorHaxe.cpp.template"
                                                                print(a->longName);
                                                            #line 1039 "CodeGeneratorHaxe.cpp"
  append(L" =\n");
  append(L"  [\n");
                                                            #line 610 "CodeGeneratorHaxe.cpp.template"
                                                                for (size_t j = 0; j < a->size; ++j)
                                                                {
                                                                  if (j)
                                                                  {
                                                            #line 1047 "CodeGeneratorHaxe.cpp"
  append(L",\n");
                                                            #line 615 "CodeGeneratorHaxe.cpp.template"
                                                                  }
                                                            #line 1051 "CodeGeneratorHaxe.cpp"
  append(L"    \"");
                                                            #line 616 "CodeGeneratorHaxe.cpp.template"
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
                                                            #line 1066 "CodeGeneratorHaxe.cpp"
  append(L"\"");
                                                            #line 628 "CodeGeneratorHaxe.cpp.template"
                                                                }
                                                            #line 1070 "CodeGeneratorHaxe.cpp"
  append(L"\n");
  append(L"  ];");
                                                            #line 630 "CodeGeneratorHaxe.cpp.template"
                                                              }
                                                              if (! variable("embedded").boolean())
                                                              {
                                                            #line 1077 "CodeGeneratorHaxe.cpp"
  append(L"\n");
  append(L"\n");
  append(L"  public enum Token\n");
  append(L"  {\n");
  append(L"    ");
                                                            #line 637 "CodeGeneratorHaxe.cpp.template"
                                                                const CGVariable &token = variable("token");
                                                                int w = (int) Format::width(token.size);
                                                                for (size_t i = 0; i < token.size; ++i)
                                                                {
                                                                  if (i)
                                                                  {
                                                            #line 1090 "CodeGeneratorHaxe.cpp"
  append(L",\n");
  append(L"    ");
                                                            #line 644 "CodeGeneratorHaxe.cpp.template"
                                                                  }
                                                            #line 1095 "CodeGeneratorHaxe.cpp"
  append(L"/* ");
                                                            #line 645 "CodeGeneratorHaxe.cpp.template"
                                                                  print(format.toString<char>(i, 10, w));
                                                            #line 1099 "CodeGeneratorHaxe.cpp"
  append(L" */ ");
                                                            #line 646 "CodeGeneratorHaxe.cpp.template"
                                                                  print(token.string(i));
                                                                }
                                                            #line 1104 "CodeGeneratorHaxe.cpp"
  append(L"\n");
  append(L"  };");
                                                            #line 650 "CodeGeneratorHaxe.cpp.template"
                                                              }
                                                              if (variable("selfTest").boolean())
                                                              {
                                                            #line 1111 "CodeGeneratorHaxe.cpp"
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
                                                            #line 688 "CodeGeneratorHaxe.cpp.template"
                                                              print(variable("classname").string());
                                                            #line 1150 "CodeGeneratorHaxe.cpp"
  append(L" testee = new ");
                                                            #line 689 "CodeGeneratorHaxe.cpp.template"
                                                              print(variable("classname").string());
                                                            #line 1154 "CodeGeneratorHaxe.cpp"
  append(L"();\n");
  append(L"    for (int e = 0; e < ");
                                                            #line 691 "CodeGeneratorHaxe.cpp.template"
                                                              print(variable("a0").size);
                                                            #line 1159 "CodeGeneratorHaxe.cpp"
  append(L"; ++e)\n");
  append(L"    {\n");
  append(L"      int s = INITIAL[e] & ");
                                                            #line 694 "CodeGeneratorHaxe.cpp.template"
                                                              print(Math::powerof(2, variable("stateCodeBits").integer()) - 1);
                                                            #line 1165 "CodeGeneratorHaxe.cpp"
  append(L";\n");
  append(L"      for (int i = 0; i < ");
                                                            #line 696 "CodeGeneratorHaxe.cpp.template"
                                                              print(variable("t1").size);
                                                            #line 1170 "CodeGeneratorHaxe.cpp"
  append(L"; i += 32)\n");
  append(L"      {\n");
  append(L"        int j = i;\n");
  append(L"        int i0 = (i >> 5) * ");
                                                            #line 700 "CodeGeneratorHaxe.cpp.template"
                                                              print(variable("transitionStateCount").integer());
                                                            #line 1177 "CodeGeneratorHaxe.cpp"
  append(L" + s - 1;\n");
                                                            #line 702 "CodeGeneratorHaxe.cpp.template"
                                                              compressedMapAccessor(8, "i", "var f = ", "EXPECTED", &variable("t0bits").integer());
                                                            #line 1181 "CodeGeneratorHaxe.cpp"
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
                                                            #line 713 "CodeGeneratorHaxe.cpp.template"
                                                              }
                                                            #line 1195 "CodeGeneratorHaxe.cpp"
  append(L"\n");
                                                            #line 715 "CodeGeneratorHaxe.cpp.template"
                                                              if (! variable("embedded").boolean())
                                                              {
                                                            #line 1200 "CodeGeneratorHaxe.cpp"
  append(L"}\n");
                                                            #line 718 "CodeGeneratorHaxe.cpp.template"
                                                              }
                                                            }

                                                            void CodeGeneratorHaxe::generateData()
                                                            {
                                                            }

// End
