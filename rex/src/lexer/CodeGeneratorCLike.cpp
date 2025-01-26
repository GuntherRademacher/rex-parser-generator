// This file was generated on Sun Jan 26, 2025 19:55 (UTC+01) by REx v6.1 which is Copyright (c) 1979-2025 by Gunther Rademacher <grd@gmx.net>
// REx command line: CodeGeneratorCLike.cpp.template
                                                            #line 1 "CodeGeneratorCLike.cpp.template"
                                                            #include "../common/Memory.hpp"
                                                            #include "../common/Format.hpp"

                                                            #include "CodeGenerator.hpp"

                                                            void CodeGeneratorCLike::predict()
                                                            {
                                                              const char *thiz = isTypescript || isGo ? "this."
                                                                                           : isPython ? "self."
                                                                                                      : "";
                                                              const char *leftBrace = isPython ? ""
                                                                             : isScala || isGo ? " {"
                                                                                               : "\n{";
                                                              const char *rightBrace = isPython ? ""
                                                                                                : "\n}";
                                                              const char *semicolon = isScala || isGo || isPython ? ""
                                                                                                                  : ";";
                                                              const char *lbracket = isScala ? "(" : "[";
                                                              const char *rbracket = isScala ? ")" : "]";
                                                              const char *returnKeyword = isScala ? "" : "return ";

                                                              if (! isGo && ! isPython)
                                                                indent += 1;
                                                              print(leftBrace);
                                                              indent += 1;
                                                              if (isJavascript || isTypescript || isHaxe || isScala)
                                                              {
                                                            #line 32 "CodeGeneratorCLike.cpp"
  append(L"\n");
  append(L"var ");
                                                            #line 29 "CodeGeneratorCLike.cpp.template"
                                                              }
                                                              else if (isGo || isPython)
                                                              {
                                                            #line 39 "CodeGeneratorCLike.cpp"
  append(L"\n");
                                                            #line 33 "CodeGeneratorCLike.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 45 "CodeGeneratorCLike.cpp"
  append(L"\n");
  append(L"int ");
                                                            #line 37 "CodeGeneratorCLike.cpp.template"
                                                              }
                                                            #line 50 "CodeGeneratorCLike.cpp"
  append(L"d ");
                                                            #line 38 "CodeGeneratorCLike.cpp.template"
                                                              if (isGo)
                                                              {
                                                            #line 55 "CodeGeneratorCLike.cpp"
  append(L":");
                                                            #line 40 "CodeGeneratorCLike.cpp.template"
                                                              }
                                                            #line 59 "CodeGeneratorCLike.cpp"
  append(L"= dpi");
                                                            #line 41 "CodeGeneratorCLike.cpp.template"
                                                              print(semicolon);
                                                              const char* ifLeftParen = isGo || isPython ? "" : "(";
                                                              const char* ifRightParen = isGo ? "" : isPython ? ":" : ")";
                                                              if (variable("lrparser").boolean())
                                                              {
                                                            #line 67 "CodeGeneratorCLike.cpp"
  append(L"\n");
  append(L"if ");
                                                            #line 47 "CodeGeneratorCLike.cpp.template"
                                                                print(ifLeftParen);
                                                                print(thiz);
                                                            #line 73 "CodeGeneratorCLike.cpp"
  append(L"l1 == 0");
                                                            #line 49 "CodeGeneratorCLike.cpp.template"
                                                                print(ifRightParen);
                                                                print(leftBrace);
                                                            #line 78 "CodeGeneratorCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 52 "CodeGeneratorCLike.cpp.template"
                                                                print(thiz);
                                                            #line 83 "CodeGeneratorCLike.cpp"
  append(L"l1 = ");
                                                            #line 53 "CodeGeneratorCLike.cpp.template"
                                                                print(thiz);
                                                            #line 87 "CodeGeneratorCLike.cpp"
  append(L"match");
                                                            #line 54 "CodeGeneratorCLike.cpp.template"
                                                                if (variable("anywhitespace").boolean())
                                                                {
                                                            #line 92 "CodeGeneratorCLike.cpp"
  append(L"W");
                                                            #line 56 "CodeGeneratorCLike.cpp.template"
                                                                }
                                                                else if (isScala)
                                                                {
                                                            #line 98 "CodeGeneratorCLike.cpp"
  append(L"er");
                                                            #line 59 "CodeGeneratorCLike.cpp.template"
                                                                }
                                                            #line 102 "CodeGeneratorCLike.cpp"
  append(L"(");
                                                            #line 60 "CodeGeneratorCLike.cpp.template"
                                                                if (isTypescript)
                                                                {
                                                            #line 107 "CodeGeneratorCLike.cpp"
  append(L"Parser.");
                                                            #line 62 "CodeGeneratorCLike.cpp.template"
                                                                }
                                                                else if (isJavascript || isScala || isPython || (isHaxe && variable("useGlr").boolean()))
                                                                {
                                                                  print(variable("classname").string());
                                                            #line 114 "CodeGeneratorCLike.cpp"
  append(L".");
                                                            #line 66 "CodeGeneratorCLike.cpp.template"
                                                                }
                                                                if (isGo)
                                                                {
                                                            #line 120 "CodeGeneratorCLike.cpp"
  append(L"tokenset");
                                                            #line 69 "CodeGeneratorCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 126 "CodeGeneratorCLike.cpp"
  append(L"TOKENSET");
                                                            #line 72 "CodeGeneratorCLike.cpp.template"
                                                                }
                                                                print(lbracket);
                                                            #line 131 "CodeGeneratorCLike.cpp"
  append(L"d");
                                                            #line 74 "CodeGeneratorCLike.cpp.template"
                                                                print(rbracket);
                                                            #line 135 "CodeGeneratorCLike.cpp"
  append(L")");
                                                            #line 75 "CodeGeneratorCLike.cpp.template"
                                                                print(semicolon);
                                                            #line 139 "CodeGeneratorCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 77 "CodeGeneratorCLike.cpp.template"
                                                                print(thiz);
                                                            #line 144 "CodeGeneratorCLike.cpp"
  append(L"b1 = ");
                                                            #line 78 "CodeGeneratorCLike.cpp.template"
                                                                print(thiz);
                                                            #line 148 "CodeGeneratorCLike.cpp"
  append(L"begin");
                                                            #line 79 "CodeGeneratorCLike.cpp.template"
                                                                print(semicolon);
                                                            #line 152 "CodeGeneratorCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 81 "CodeGeneratorCLike.cpp.template"
                                                                print(thiz);
                                                            #line 157 "CodeGeneratorCLike.cpp"
  append(L"e1 = ");
                                                            #line 82 "CodeGeneratorCLike.cpp.template"
                                                                print(thiz);
                                                            #line 161 "CodeGeneratorCLike.cpp"
  append(L"end");
                                                            #line 83 "CodeGeneratorCLike.cpp.template"
                                                                print(semicolon);
                                                                print(rightBrace);
                                                              }
                                                              if (variable("nothrow").boolean())
                                                              {
                                                                if (isGo)
                                                                {
                                                            #line 171 "CodeGeneratorCLike.cpp"
  append(L"\n");
  append(L"if this.l1 < 0 {\n");
  append(L"  return this.l1\n");
  append(L"}");
                                                            #line 93 "CodeGeneratorCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 180 "CodeGeneratorCLike.cpp"
  append(L"\n");
  append(L"if ");
                                                            #line 97 "CodeGeneratorCLike.cpp.template"
                                                                  print(ifLeftParen);
                                                                  print(thiz);
                                                            #line 186 "CodeGeneratorCLike.cpp"
  append(L"l1 < 0");
                                                            #line 99 "CodeGeneratorCLike.cpp.template"
                                                                  print(ifRightParen);
                                                            #line 190 "CodeGeneratorCLike.cpp"
  append(L"\n");
  append(L"  return ");
                                                            #line 101 "CodeGeneratorCLike.cpp.template"
                                                                  print(thiz);
                                                            #line 195 "CodeGeneratorCLike.cpp"
  append(L"l1");
                                                            #line 102 "CodeGeneratorCLike.cpp.template"
                                                                  print(semicolon);
                                                                }
                                                              }
                                                              if (variable("useGlr").boolean())
                                                              {
                                                                if (isGo)
                                                                {
                                                            #line 205 "CodeGeneratorCLike.cpp"
  append(L"\n");
  append(L"if this.l1 < 0 {\n");
  append(L"  return 0");
                                                            #line 111 "CodeGeneratorCLike.cpp.template"
                                                                  print(rightBrace);
                                                                }
                                                                else
                                                                {
                                                            #line 214 "CodeGeneratorCLike.cpp"
  append(L"\n");
  append(L"if ");
                                                            #line 116 "CodeGeneratorCLike.cpp.template"
                                                                  print(ifLeftParen);
                                                                  print(thiz);
                                                            #line 220 "CodeGeneratorCLike.cpp"
  append(L"l1 < 0");
                                                            #line 118 "CodeGeneratorCLike.cpp.template"
                                                                  print(ifRightParen);
                                                            #line 224 "CodeGeneratorCLike.cpp"
  append(L"\n");
  append(L"  return 0");
                                                            #line 120 "CodeGeneratorCLike.cpp.template"
                                                                  print(semicolon);
                                                                }
                                                              }
                                                              int k = variable("k").integer();
                                                              bool loop = k > 1 && variable("lrparser").boolean();
                                                              if (loop)
                                                              {
                                                                if (isHaxe || isScala)
                                                                {
                                                            #line 237 "CodeGeneratorCLike.cpp"
  append(L"\n");
  append(L"while (true)");
                                                            #line 130 "CodeGeneratorCLike.cpp.template"
                                                                  print(leftBrace);
                                                                }
                                                                else if (isPython)
                                                                {
                                                            #line 245 "CodeGeneratorCLike.cpp"
  append(L"\n");
  append(L"while True:");
                                                            #line 135 "CodeGeneratorCLike.cpp.template"
                                                                }
                                                                else if (isGo)
                                                                {
                                                            #line 252 "CodeGeneratorCLike.cpp"
  append(L"\n");
  append(L"for ;; d++ {");
                                                            #line 139 "CodeGeneratorCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 259 "CodeGeneratorCLike.cpp"
  append(L"\n");
  append(L"for (;; ++d)");
                                                            #line 143 "CodeGeneratorCLike.cpp.template"
                                                                  print(leftBrace);
                                                                }
                                                                indent += 1;
                                                              }
                                                            #line 267 "CodeGeneratorCLike.cpp"
  append(L"\n");
                                                            #line 148 "CodeGeneratorCLike.cpp.template"
                                                              const char *action = isJavascript || isTypescript || isHaxe || isScala ? "var action = "
                                                                                                                                     : isGo ? "action := "
                                                                                                                                            : isPython ? "action = "
                                                                                                                                                       : "int action = ";
                                                              const char *x = isTypescript || isGo ? "this.l1"
                                                                                                   : isPython ? "self.l1"
                                                                                                              : "l1";
                                                              CString caseId;
                                                              if (isScala || (isHaxe && variable("useGlr").boolean()))
                                                              {
                                                                caseId += variable("classname").string();
                                                                caseId += ".";
                                                              }
                                                              caseId += isGo ? "caseid" : "CASEID";
                                                              compressedMap2dAccessor(x, "d", variable("cicols").integer(),
                                                                                         0, "j1", action, caseId.c_str(), &variable("cibits").integer());
                                                              for (int i = 2; i <= k; ++i)
                                                              {
                                                                if (loop && i != 2)
                                                                {
                                                            #line 290 "CodeGeneratorCLike.cpp"
  append(L"\n");
  append(L"if ");
                                                            #line 169 "CodeGeneratorCLike.cpp.template"
                                                                  print(ifLeftParen);
                                                            #line 295 "CodeGeneratorCLike.cpp"
  append(L"action != 0");
                                                            #line 170 "CodeGeneratorCLike.cpp.template"
                                                                  print(ifRightParen);
                                                                  print(leftBrace);
                                                                  indent += 1;
                                                                }
                                                            #line 302 "CodeGeneratorCLike.cpp"
  append(L"\n");
  append(L"if ");
                                                            #line 175 "CodeGeneratorCLike.cpp.template"
                                                                print(ifLeftParen);
                                                            #line 307 "CodeGeneratorCLike.cpp"
  append(L"(action & 1) == 0");
                                                            #line 176 "CodeGeneratorCLike.cpp.template"
                                                                print(ifRightParen);
                                                                if (isGo)
                                                                {
                                                            #line 313 "CodeGeneratorCLike.cpp"
  append(L" {");
                                                            #line 179 "CodeGeneratorCLike.cpp.template"
                                                                }
                                                            #line 317 "CodeGeneratorCLike.cpp"
  append(L"\n");
  append(L"  return action >> 1");
                                                            #line 181 "CodeGeneratorCLike.cpp.template"
                                                                print(semicolon);
                                                                if (isGo)
                                                                {
                                                            #line 324 "CodeGeneratorCLike.cpp"
  append(L"\n");
  append(L"}");
                                                            #line 185 "CodeGeneratorCLike.cpp.template"
                                                                }
                                                            #line 329 "CodeGeneratorCLike.cpp"
  append(L"\n");
  append(L"if ");
                                                            #line 187 "CodeGeneratorCLike.cpp.template"
                                                                print(ifLeftParen);
                                                                print(thiz);
                                                            #line 335 "CodeGeneratorCLike.cpp"
  append(L"l");
                                                            #line 189 "CodeGeneratorCLike.cpp.template"
                                                                print(format.toString<char>(i));
                                                            #line 339 "CodeGeneratorCLike.cpp"
  append(L" == 0");
                                                            #line 190 "CodeGeneratorCLike.cpp.template"
                                                                print(ifRightParen);
                                                                print(leftBrace);
                                                            #line 344 "CodeGeneratorCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 193 "CodeGeneratorCLike.cpp.template"
                                                                print(thiz);
                                                            #line 349 "CodeGeneratorCLike.cpp"
  append(L"l");
                                                            #line 194 "CodeGeneratorCLike.cpp.template"
                                                                print(format.toString<char>(i));
                                                            #line 353 "CodeGeneratorCLike.cpp"
  append(L" = ");
                                                            #line 195 "CodeGeneratorCLike.cpp.template"
                                                                print(thiz);
                                                            #line 357 "CodeGeneratorCLike.cpp"
  append(L"match");
                                                            #line 196 "CodeGeneratorCLike.cpp.template"
                                                                if (variable("anywhitespace").boolean())
                                                                {
                                                            #line 362 "CodeGeneratorCLike.cpp"
  append(L"W");
                                                            #line 198 "CodeGeneratorCLike.cpp.template"
                                                                }
                                                                else if (isScala)
                                                                {
                                                            #line 368 "CodeGeneratorCLike.cpp"
  append(L"er");
                                                            #line 201 "CodeGeneratorCLike.cpp.template"
                                                                }
                                                            #line 372 "CodeGeneratorCLike.cpp"
  append(L"(action >> 1)");
                                                            #line 202 "CodeGeneratorCLike.cpp.template"
                                                                print(semicolon);
                                                            #line 376 "CodeGeneratorCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 204 "CodeGeneratorCLike.cpp.template"
                                                                print(thiz);
                                                            #line 381 "CodeGeneratorCLike.cpp"
  append(L"b");
                                                            #line 205 "CodeGeneratorCLike.cpp.template"
                                                                print(format.toString<char>(i));
                                                            #line 385 "CodeGeneratorCLike.cpp"
  append(L" = ");
                                                            #line 206 "CodeGeneratorCLike.cpp.template"
                                                                print(thiz);
                                                            #line 389 "CodeGeneratorCLike.cpp"
  append(L"begin");
                                                            #line 207 "CodeGeneratorCLike.cpp.template"
                                                                print(semicolon);
                                                            #line 393 "CodeGeneratorCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 209 "CodeGeneratorCLike.cpp.template"
                                                                print(thiz);
                                                            #line 398 "CodeGeneratorCLike.cpp"
  append(L"e");
                                                            #line 210 "CodeGeneratorCLike.cpp.template"
                                                                print(format.toString<char>(i));
                                                            #line 402 "CodeGeneratorCLike.cpp"
  append(L" = ");
                                                            #line 211 "CodeGeneratorCLike.cpp.template"
                                                                print(thiz);
                                                            #line 406 "CodeGeneratorCLike.cpp"
  append(L"end");
                                                            #line 212 "CodeGeneratorCLike.cpp.template"
                                                                print(semicolon);
                                                                print(rightBrace);
                                                                if (variable("nothrow").boolean())
                                                                {
                                                                  if (isGo)
                                                                  {
                                                            #line 415 "CodeGeneratorCLike.cpp"
  append(L"\n");
  append(L"if this.l");
                                                            #line 219 "CodeGeneratorCLike.cpp.template"
                                                                    print(format.toString<char>(i));
                                                            #line 420 "CodeGeneratorCLike.cpp"
  append(L" < 0 {\n");
  append(L"  return this.l");
                                                            #line 221 "CodeGeneratorCLike.cpp.template"
                                                                    print(format.toString<char>(i));
                                                                    print(semicolon);
                                                            #line 426 "CodeGeneratorCLike.cpp"
  append(L"\n");
  append(L"}");
                                                            #line 224 "CodeGeneratorCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 433 "CodeGeneratorCLike.cpp"
  append(L"\n");
  append(L"if ");
                                                            #line 228 "CodeGeneratorCLike.cpp.template"
                                                                    print(ifLeftParen);
                                                                    print(thiz);
                                                            #line 439 "CodeGeneratorCLike.cpp"
  append(L"l");
                                                            #line 230 "CodeGeneratorCLike.cpp.template"
                                                                    print(format.toString<char>(i));
                                                            #line 443 "CodeGeneratorCLike.cpp"
  append(L" < 0");
                                                            #line 231 "CodeGeneratorCLike.cpp.template"
                                                                    print(ifRightParen);
                                                            #line 447 "CodeGeneratorCLike.cpp"
  append(L"\n");
  append(L"  return l");
                                                            #line 233 "CodeGeneratorCLike.cpp.template"
                                                                    print(format.toString<char>(i));
                                                                    print(semicolon);
                                                                  }
                                                                }
                                                                if (variable("useGlr").boolean())
                                                                {
                                                            #line 457 "CodeGeneratorCLike.cpp"
  append(L"\n");
  append(L"if ");
                                                            #line 240 "CodeGeneratorCLike.cpp.template"
                                                                  print(ifLeftParen);
                                                                  print(thiz);
                                                            #line 463 "CodeGeneratorCLike.cpp"
  append(L"l");
                                                            #line 242 "CodeGeneratorCLike.cpp.template"
                                                                  print(format.toString<char>(i));
                                                            #line 467 "CodeGeneratorCLike.cpp"
  append(L" < 0");
                                                            #line 243 "CodeGeneratorCLike.cpp.template"
                                                                  print(ifRightParen);
                                                                  if (isGo)
                                                                  {
                                                            #line 473 "CodeGeneratorCLike.cpp"
  append(L" {");
                                                            #line 246 "CodeGeneratorCLike.cpp.template"
                                                                  }
                                                            #line 477 "CodeGeneratorCLike.cpp"
  append(L"\n");
  append(L"  return 0");
                                                            #line 248 "CodeGeneratorCLike.cpp.template"
                                                                  print(semicolon);
                                                                  if (isGo)
                                                                  {
                                                            #line 484 "CodeGeneratorCLike.cpp"
  append(L"\n");
  append(L"}");
                                                            #line 252 "CodeGeneratorCLike.cpp.template"
                                                                  }
                                                                }
                                                            #line 490 "CodeGeneratorCLike.cpp"
  append(L"\n");
                                                            #line 255 "CodeGeneratorCLike.cpp.template"
                                                                CString li(isTypescript || isGo ? "this.l" : isPython ? "self.l" : "l");
                                                                li += format.toString<char>(i);
                                                                CString ii("i");
                                                                ii += format.toString<char>(i);
                                                                const char *x = isTypescript || isGo ? (i == 2 ? "this.l1" : "matchCode")
                                                                                          : isPython ? (i == 2 ? "self.l1" : "matchCode")
                                                                                                     : (i == 2 ? "l1" : "matchCode");
                                                                const char *result = isTypescript || isJavascript || isHaxe || isScala ? (i == 2 ? "var matchCode = " : "matchCode = ")
                                                                                                                                : isGo ? (i == 2 ? "matchCode := " : "matchCode = ")
                                                                                                                             :isPython ? "matchCode = "
                                                                                                                                       : (i == 2 ? "int matchCode = " : "matchCode = ");
                                                                CString lookahead;
                                                                if (isScala)
                                                                {
                                                                  lookahead += variable("classname").string();
                                                                  lookahead += ".";
                                                                }
                                                                lookahead += isGo ? "lookahead" : "LOOKAHEAD";
                                                                compressedMap2dAccessor(x, li.c_str(), variable("lxcols").integer(),
                                                                                           0, ii.c_str(), result, lookahead.c_str(), &variable("lxbits").integer());
                                                            #line 513 "CodeGeneratorCLike.cpp"
  append(L"\n");
  append(L"if ");
                                                            #line 276 "CodeGeneratorCLike.cpp.template"
                                                                print(ifLeftParen);
                                                            #line 518 "CodeGeneratorCLike.cpp"
  append(L"matchCode != 0");
                                                            #line 277 "CodeGeneratorCLike.cpp.template"
                                                                print(ifRightParen);
                                                                print(leftBrace);
                                                            #line 523 "CodeGeneratorCLike.cpp"
  append(L"\n");
                                                            #line 280 "CodeGeneratorCLike.cpp.template"
                                                                CString ji("j");
                                                                ji += format.toString<char>(i);
                                                                compressedMap2dAccessor("matchCode", "d", variable("cicols").integer(),
                                                                                           2, ji.c_str(), "action = ", caseId.c_str(), &variable("cibits").integer());
                                                                indent += 1;
                                                              }
                                                              if (loop)
                                                              {
                                                            #line 534 "CodeGeneratorCLike.cpp"
  append(L"\n");
  append(L"if ");
                                                            #line 289 "CodeGeneratorCLike.cpp.template"
                                                                print(ifLeftParen);
                                                            #line 539 "CodeGeneratorCLike.cpp"
  append(L"action != 0");
                                                            #line 290 "CodeGeneratorCLike.cpp.template"
                                                                print(ifRightParen);
                                                                print(leftBrace);
                                                                indent += 1;
                                                              }
                                                            #line 546 "CodeGeneratorCLike.cpp"
  append(L"\n");
  append(L"return action >> 1");
                                                            #line 295 "CodeGeneratorCLike.cpp.template"
                                                              print(semicolon);
                                                              for (int i = k; i >= 2; --i)
                                                              {
                                                                indent -= 1;
                                                                print(rightBrace);
                                                                if (loop)
                                                                {
                                                                  indent -= 1;
                                                                  print(rightBrace);
                                                                }
                                                              }
                                                              if (loop)
                                                              {
                                                                if (isHaxe || isScala || isPython)
                                                                {
                                                            #line 565 "CodeGeneratorCLike.cpp"
  append(L"\n");
  append(L"d += 1");
                                                            #line 311 "CodeGeneratorCLike.cpp.template"
                                                                  print(semicolon);
                                                                }
                                                                indent -= 1;
                                                                print(rightBrace);
                                                              }
                                                              if ((k > 1 && ! loop) || isScala)
                                                              {
                                                            #line 576 "CodeGeneratorCLike.cpp"
  append(L"\n");
                                                            #line 319 "CodeGeneratorCLike.cpp.template"
                                                                print(returnKeyword);
                                                            #line 580 "CodeGeneratorCLike.cpp"
  append(L"0");
                                                            #line 320 "CodeGeneratorCLike.cpp.template"
                                                                print(semicolon);
                                                              }
                                                              indent -= 1;
                                                              print(rightBrace);
                                                            #line 587 "CodeGeneratorCLike.cpp"
  append(L"\n");
                                                            #line 325 "CodeGeneratorCLike.cpp.template"
                                                              if (! isGo && ! isPython)
                                                                indent -= 1;
                                                            }

                                                            void CodeGeneratorCLike::compressedMap2dAccessor(const char *x,
                                                                                                           const char *y,
                                                                                                           int xCount,
                                                                                                           size_t indent,
                                                                                                           const char *index,
                                                                                                           const char *result,
                                                                                                           const char *map,
                                                                                                           const int *bits)
                                                            {
                                                              const char *semicolon = isScala || isGo || isPython ? "" : ";";
                                                              print(indent, " ");
                                                              if (isJavascript || isTypescript || isHaxe)
                                                              {
                                                            #line 607 "CodeGeneratorCLike.cpp"
  append(L"var ");
                                                            #line 342 "CodeGeneratorCLike.cpp.template"
                                                              }
                                                              else if (isScala)
                                                              {
                                                            #line 613 "CodeGeneratorCLike.cpp"
  append(L"val ");
                                                            #line 345 "CodeGeneratorCLike.cpp.template"
                                                              }
                                                              else if (! isGo && ! isPython)
                                                              {
                                                            #line 619 "CodeGeneratorCLike.cpp"
  append(L"int ");
                                                            #line 348 "CodeGeneratorCLike.cpp.template"
                                                              }
                                                              print(index);
                                                              if (isGo)
                                                              {
                                                            #line 626 "CodeGeneratorCLike.cpp"
  append(L"0 := ");
                                                            #line 352 "CodeGeneratorCLike.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 632 "CodeGeneratorCLike.cpp"
  append(L"0 = ");
                                                            #line 355 "CodeGeneratorCLike.cpp.template"
                                                              }
                                                              if (Math::isPowerOf2(xCount))
                                                              {
                                                            #line 638 "CodeGeneratorCLike.cpp"
  append(L"(");
                                                            #line 358 "CodeGeneratorCLike.cpp.template"
                                                                print(y);
                                                            #line 642 "CodeGeneratorCLike.cpp"
  append(L" << ");
                                                            #line 360 "CodeGeneratorCLike.cpp.template"
                                                                print(format.toString<char>(Math::log2(xCount)));
                                                            #line 646 "CodeGeneratorCLike.cpp"
  append(L")");
                                                            #line 361 "CodeGeneratorCLike.cpp.template"
                                                              }
                                                              else
                                                              {
                                                                print(format.toString<char>(xCount));
                                                            #line 653 "CodeGeneratorCLike.cpp"
  append(L" * ");
                                                            #line 365 "CodeGeneratorCLike.cpp.template"
                                                                print(y);
                                                              }
                                                            #line 658 "CodeGeneratorCLike.cpp"
  append(L" + ");
                                                            #line 367 "CodeGeneratorCLike.cpp.template"
                                                              print(x);
                                                              print(semicolon);
                                                            #line 663 "CodeGeneratorCLike.cpp"
  append(L"\n");
                                                            #line 370 "CodeGeneratorCLike.cpp.template"
                                                              compressedMapAccessor(indent, index, result, map, bits);
                                                            }

                                                            void CodeGeneratorCLike::compressedMapAccessor(size_t indent, const char *index, const char *result, const char *map, const int *bits)
                                                            {
                                                              const char *lBracket = isScala ? "(" : "[";
                                                              const char *rBracket = isScala ? ")" : "]";
                                                              const char *semicolon = isScala || isGo || isPython ? "" : ";";
                                                              size_t i = 0;
                                                              if (bits[0])
                                                              {
                                                                for (i = 1; bits[i]; ++i)
                                                                {
                                                                  print(indent, " ");
                                                                  if (isJavascript || isTypescript || isHaxe)
                                                                  {
                                                            #line 682 "CodeGeneratorCLike.cpp"
  append(L"var ");
                                                            #line 386 "CodeGeneratorCLike.cpp.template"
                                                                  }
                                                                  else if (isScala)
                                                                  {
                                                            #line 688 "CodeGeneratorCLike.cpp"
  append(L"val ");
                                                            #line 389 "CodeGeneratorCLike.cpp.template"
                                                                  }
                                                                  else if (! isGo && ! isPython)
                                                                  {
                                                            #line 694 "CodeGeneratorCLike.cpp"
  append(L"int ");
                                                            #line 392 "CodeGeneratorCLike.cpp.template"
                                                                  }
                                                                  print(index);
                                                                  print(i);
                                                                  if (isGo)
                                                                  {
                                                            #line 702 "CodeGeneratorCLike.cpp"
  append(L" := ");
                                                            #line 397 "CodeGeneratorCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 708 "CodeGeneratorCLike.cpp"
  append(L" = ");
                                                            #line 400 "CodeGeneratorCLike.cpp.template"
                                                                 }
                                                                  print(index);
                                                                  print(i - 1);
                                                            #line 714 "CodeGeneratorCLike.cpp"
  append(L" >> ");
                                                            #line 403 "CodeGeneratorCLike.cpp.template"
                                                                  print(bits[i - 1]);
                                                                  print(semicolon);
                                                            #line 719 "CodeGeneratorCLike.cpp"
  append(L"\n");
                                                            #line 406 "CodeGeneratorCLike.cpp.template"
                                                                }
                                                              }
                                                              print(indent, " ");
                                                              print(result);
                                                              if (isTypescript)
                                                              {
                                                            #line 728 "CodeGeneratorCLike.cpp"
  append(L"Parser.");
                                                            #line 412 "CodeGeneratorCLike.cpp.template"
                                                              }
                                                              else if (isJavascript || isPython)
                                                              {
                                                                print(variable("classname").string());
                                                            #line 735 "CodeGeneratorCLike.cpp"
  append(L".");
                                                            #line 416 "CodeGeneratorCLike.cpp.template"
                                                              }
                                                              print(map);
                                                              print(lBracket);
                                                              for (i = 0; bits[i]; ++i)
                                                              {
                                                            #line 743 "CodeGeneratorCLike.cpp"
  append(L"(");
                                                            #line 421 "CodeGeneratorCLike.cpp.template"
                                                                print(index);
                                                                print(i);
                                                            #line 748 "CodeGeneratorCLike.cpp"
  append(L" & ");
                                                            #line 423 "CodeGeneratorCLike.cpp.template"
                                                                print(Math::powerof(2, bits[i]) - 1);
                                                            #line 752 "CodeGeneratorCLike.cpp"
  append(L") + ");
                                                            #line 424 "CodeGeneratorCLike.cpp.template"
                                                                if (isTypescript)
                                                                {
                                                            #line 757 "CodeGeneratorCLike.cpp"
  append(L"Parser.");
                                                            #line 426 "CodeGeneratorCLike.cpp.template"
                                                                }
                                                                else if (isJavascript || isPython)
                                                                {
                                                                  print(variable("classname").string());
                                                            #line 764 "CodeGeneratorCLike.cpp"
  append(L".");
                                                            #line 430 "CodeGeneratorCLike.cpp.template"
                                                                }
                                                                print(map);
                                                                print(lBracket);
                                                              }
                                                              print(index);
                                                              if (i > 0)
                                                              {
                                                                print(i - 1);
                                                            #line 775 "CodeGeneratorCLike.cpp"
  append(L" >> ");
                                                            #line 438 "CodeGeneratorCLike.cpp.template"
                                                                print(bits[i - 1]);
                                                              }
                                                              else
                                                              {
                                                                print(i);
                                                              }
                                                              for (i = 0; bits[i]; ++i)
                                                              {
                                                                print(rBracket);
                                                              }
                                                              print(rBracket);
                                                              print(semicolon);
                                                            }

// End
