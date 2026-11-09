// This file was generated on Sun Nov 8, 2026 22:38 (UTC+01) by REx v7.0-SNAPSHOT which is Copyright (c) 1979-2026 by Gunther Rademacher <grd@gmx.net>
// REx command line: PrintCLike.cpp.template
                                                            #line 1 "PrintCLike.cpp.template"
                                                            /*
                                                             * PrintCLike.hpp
                                                             *
                                                             *  Created on: 31.07.2008
                                                             *      Author: Gunther
                                                             */

                                                            #include "../common/Memory.hpp"

                                                            #include "PrintCLike.hpp"
                                                            #include "OrderedTokenSequenceVector.hpp"
                                                            #include "ItemSet.hpp"

                                                            #include "../common/PtrLess.hpp"
                                                            #include "../common/Format.hpp"
                                                            #include "../common/Encoder.hpp"

                                                            #ifdef TRACE
                                                            int Tracer::level = 0;
                                                            #endif

                                                            void PrintCLike::printCodeSequenceAnnotation(const TokenSequenceSet &t)
                                                            {
                                                              Trace("PrintCLike::printCodeSequenceAnnotation");

                                                              const size_t align = 36;
                                                              print(lineBuffer.c_str());
                                                              size_t lsize = column();
                                                              size_t filler = lsize <= align ? align - lsize : lsize % 2;
                                                              int spaces = lsize + filler;
                                                              size_t width = spaces > 120 ? 0 : 120 - spaces;
                                                              if (width < (120 - align) / 2) width = (120 - align) / 2;
                                                              WString commentContinuation(L"\n");
                                                              commentContinuation += inlineCommentIntroducer();
                                                              WString annotation(t.toString(grammar, commentContinuation.c_str(), L" |", width - 3, 0, false, toBeEscaped));
                                                              wchar_t *indentedAnnotation = Format::reIndent(annotation.c_str(), Math::max(0, static_cast<int>(spaces) - getIndent()));
                                                              print(filler, L" ");
                                                              print(inlineCommentIntroducer());
                                                              print(indentedAnnotation);
                                                              free(indentedAnnotation);
                                                            }

                                                            void PrintCLike::printLookahead(size_t k,
                                                                                            const TokenSequenceSet &prefix,
                                                                                            size_t level,
                                                                                            const CompressedTokenSet *lookahead,
                                                                                            bool findsLookahead)
                                                            {
                                                              Trace("PrintCLike::printLookahead");

                                                              if (lookahead != 0 && ! lookahead->empty())
                                                              {
                                                                if (level > 1 || ! findsLookahead)
                                                                {
                                                            #line 59 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 56 "PrintCLike.cpp.template"
                                                                  const wchar_t *lookaheadType;
                                                                  if (anyWhitespace && lookahead->hasImplicitWhitespace())
                                                                  {
                                                                    lookaheadType = L"W";
                                                                  }
                                                                  else
                                                                  {
                                                                    lookaheadType = L"";
                                                                  }

                                                                  lineBuffer.clear();
                                                                  lineBuffer += thiz();
                                                                  lineBuffer += L"lookahead";
                                                                  lineBuffer += format.toString<wchar_t>(level);
                                                                  lineBuffer += lookaheadType;
                                                                  lineBuffer += L"(";
                                                                  lineBuffer += level == 1 || ! unlimitedLookahead ? L"" : format.toString<wchar_t>(lookahead->prefixCode(grammar->tokenSequenceFactory->tokenBits()));
                                                                  lineBuffer += level == 1 || ! unlimitedLookahead ? L"" : L", ";
                                                                  lineBuffer += grammar->singleLexer ? L"0" : format.toString<wchar_t>(lookahead->getSetNo(grammar->lookaheadSets));
                                                                  lineBuffer += L")";
                                                                  lineBuffer += semicolon();
                                                                  lineBuffer += L" ";

                                                                  printCodeSequenceAnnotation(lookahead->getInitials());
                                                                }

                                                                if (lookahead->getDpi() >= 0)
                                                                {
                                                            #line 90 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 85 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 94 "PrintCLike.cpp"
  append(L"lk = ");
                                                            #line 86 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 98 "PrintCLike.cpp"
  append(L"predict(");
                                                            #line 87 "PrintCLike.cpp.template"
                                                                  print(format.toString<wchar_t>(lookahead->getDpi()));
                                                            #line 102 "PrintCLike.cpp"
  append(L")");
                                                            #line 88 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                                else if (level < k)
                                                                {
                                                                  // this block will be obsolete when "tables" proves to be successful

                                                                  const CompressedTokenSet::CompressedTokenSetByTokenSet &chol(lookahead->getCombinedHigherOrderLookahead());
                                                                  if (! chol.empty())
                                                                  {
                                                                    const wchar_t *switchVar = (level == 1 && lookahead->getDpi() < 0) ? token() : tokenSequence();
                                                                    if (isScala())
                                                                    {
                                                            #line 117 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 101 "PrintCLike.cpp.template"
                                                                      print(switchVar);
                                                            #line 121 "PrintCLike.cpp"
  append(L" match");
                                                            #line 102 "PrintCLike.cpp.template"
                                                                    }
                                                                    else if (! isPython())
                                                                    {
                                                            #line 127 "PrintCLike.cpp"
  append(L"\n");
  append(L"switch ");
                                                            #line 106 "PrintCLike.cpp.template"
                                                                      print(ifLeftParen());
                                                                      print(thiz());
                                                                      print(switchVar);
                                                                      print(ifRightParen());
                                                                    }
                                                                    print(leftBrace());
                                                                    ++level;
                                                                    OrderedTokenSequenceVector orderedPrefix(prefix, __FILE__, __LINE__);
                                                                    if (unlimitedLookahead)
                                                                    {
                                                                      const CompressedTokenSet::HigherOrderLookahead &hol(lookahead->getHigherOrderLookahead());
                                                                      for (CompressedTokenSet::HigherOrderLookahead::const_iterator i(hol.begin());
                                                                           i != hol.end();
                                                                           ++i)
                                                                      {
                                                                        Token::Code token = i->first;

                                                                        for (OrderedTokenSequenceVector::const_iterator p = orderedPrefix.begin(); p != orderedPrefix.end(); ++p)
                                                                        {
                                                                          TokenSequence nextPrefix(grammar->tokenSequenceFactory->tokenSequence(*p, grammar->tokenSequence(token)));
                                                            #line 151 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 127 "PrintCLike.cpp.template"
                                                                          lineBuffer.clear();
                                                                          if (isPython())
                                                                          {
                                                                            lineBuffer += L"if ";
                                                                            lineBuffer += L"self.";
                                                                            lineBuffer += switchVar;
                                                                            lineBuffer += L" == ";
                                                                          }
                                                                          else
                                                                          {
                                                                            lineBuffer += L"case ";
                                                                          }
                                                                          lineBuffer += format.toString<wchar_t>(lookahead->localSequenceCode(grammar->tokenSequenceFactory, grammar->tokenSequence(token), grammar->externalTokenCode));
                                                                          lineBuffer += isScala() ? L" => " : L": ";

                                                                          printCodeSequenceAnnotation(nextPrefix);
                                                                          increaseIndent();
                                                                          TokenSequenceSet singleNextPrefixSet;
                                                                          singleNextPrefixSet.insert(nextPrefix);
                                                                          printLookahead(k, singleNextPrefixSet, level, i->second, findsLookahead);
                                                                          if (! isScala() && ! isHaxe() && ! isGo() && ! isPython())
                                                                          {
                                                            #line 176 "PrintCLike.cpp"
  append(L"\n");
  append(L"break");
                                                            #line 150 "PrintCLike.cpp.template"
                                                                            print(semicolon());
                                                                          }
                                                                          decreaseIndent();
                                                                        }
                                                                      }
                                                                    }
                                                                    else
                                                                    {
                                                                      const CompressedTokenSet::CompressedTokenSetByTokenSet &chol = lookahead->getCombinedHigherOrderLookahead();
                                                                      for (CompressedTokenSet::CompressedTokenSetByTokenSet::const_iterator i = chol.begin();
                                                                           i != chol.end();
                                                                           ++i)
                                                                      {
                                                                        const CompressedTokenSet *cts = i->second;
                                                                        const OrderedTokenSequenceVector &ots(i->first);
                                                                        TokenSequenceSet nextPrefixSet;
                                                                        bool firstJ = true;
                                                                        size_t cases = orderedPrefix.size() * ots.size();
                                                                        for (OrderedTokenSequenceVector::const_iterator p = orderedPrefix.begin(); p != orderedPrefix.end(); )
                                                                        {
                                                                          const TokenSequence &otsv(*p);
                                                                          ++p;
                                                                          bool lastP = p == orderedPrefix.end();
                                                                          for (OrderedTokenSequenceVector::const_iterator j = ots.begin(); j != ots.end(); )
                                                                          {
                                                                            TokenSequence nextPrefix(grammar->tokenSequenceFactory->tokenSequence(otsv, *j));
                                                                            ++j;
                                                                            bool lastJ = lastP && j == ots.end();
                                                                            nextPrefixSet.insert(nextPrefix);
                                                            #line 209 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 180 "PrintCLike.cpp.template"
                                                                            lineBuffer.clear();
                                                                            if (isPython())
                                                                            {
                                                                              if (i == chol.begin())
                                                                              {
                                                                                lineBuffer += firstJ ? L"if " : L"   ";
                                                                              }
                                                                              else
                                                                              {
                                                                                lineBuffer += firstJ ? L"elif " : L"     ";
                                                                              }
                                                                              if (cases > 1)
                                                                                lineBuffer += firstJ ? L"(" : L" ";
                                                                              lineBuffer += L"self.";
                                                                              lineBuffer += switchVar;
                                                                              lineBuffer += L" == ";
                                                                              lineBuffer += format.toString<wchar_t>(CompressedTokenSet::uniqueSequenceCode(grammar->tokenSequenceFactory, nextPrefix, grammar->externalTokenCode));
                                                                              if (lastJ)
                                                                              {
                                                                                if (cases > 1)
                                                                                  lineBuffer += L")";
                                                                                lineBuffer += L":";
                                                                              }
                                                                              else
                                                                              {
                                                                                lineBuffer += L" or";
                                                                              }
                                                                            }
                                                                            else
                                                                            {
                                                                              lineBuffer += (! isScala() && ! isHaxe() && ! isGo()) || firstJ ? L"case "
                                                                                                                                     : isGo() ? L"     "
                                                                                                                                              : L"   | ";
                                                                              lineBuffer += format.toString<wchar_t>(CompressedTokenSet::uniqueSequenceCode(grammar->tokenSequenceFactory, nextPrefix, grammar->externalTokenCode));
                                                                              lineBuffer += ! isScala() && ! isHaxe() && ! isGo() && ! isPython() ? L": "
                                                                                                                                        : ! lastJ ? (isGo() ? L", " : L" ")
                                                                                                                                     : (isScala() ? L" => " : L": ");
                                                                            }
                                                                            printCodeSequenceAnnotation(nextPrefix);
                                                                            firstJ = false;
                                                                          }
                                                                        }
                                                                        increaseIndent();
                                                                        printLookahead(k, nextPrefixSet, level, cts, findsLookahead);
                                                                        if (! isScala() && ! isHaxe() && ! isGo() && ! isPython())
                                                                        {
                                                            #line 258 "PrintCLike.cpp"
  append(L"\n");
  append(L"break");
                                                            #line 227 "PrintCLike.cpp.template"
                                                                          print(semicolon());
                                                                        }
                                                                        decreaseIndent();
                                                                      }
                                                                    }

                                                                    --level;
                                                                    if (isScala())
                                                                    {
                                                            #line 271 "PrintCLike.cpp"
  append(L"\n");
  append(L"case _ =>");
                                                            #line 237 "PrintCLike.cpp.template"
                                                                    }

                                                                    if (level == 1)
                                                                    {
                                                                      if (isPython())
                                                                      {
                                                            #line 281 "PrintCLike.cpp"
  append(L"\n");
  append(L"else:");
                                                            #line 244 "PrintCLike.cpp.template"
                                                                      }
                                                                      else if (! isScala())
                                                                      {
                                                            #line 288 "PrintCLike.cpp"
  append(L"\n");
  append(L"default:");
                                                            #line 248 "PrintCLike.cpp.template"
                                                                      }
                                                                      increaseIndent();
                                                            #line 294 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 251 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 298 "PrintCLike.cpp"
  append(L"lk = ");
                                                            #line 252 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 302 "PrintCLike.cpp"
  append(L"l1");
                                                            #line 253 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                                      if (isCpp() || isCSharp())
                                                                      {
                                                            #line 308 "PrintCLike.cpp"
  append(L"\n");
  append(L"break");
                                                            #line 257 "PrintCLike.cpp.template"
                                                                        print(semicolon());
                                                                      }
                                                                      decreaseIndent();
                                                                    }
                                                                    print(rightBrace());
                                                                  }
                                                                }
                                                              }
                                                            }

                                                            void PrintCLike::printMatch(const CompressedTokenSet *lookahead,
                                                                                        size_t k,
                                                                                        int backtrackedCaseId,
                                                                                        const TokenSequenceSet &ts,
                                                                                        MatchType matchType,
                                                                                        bool invert,
                                                                                        int caseId,
                                                                                        const wchar_t *prefix)
                                                            {
                                                              Trace("PrintCLike::printMatch");

                                                              const wchar_t *logicalAnd = isPython() ? L" and " : L" && ";
                                                              const wchar_t *logicalOr  = isPython() ? L" or " : L" || ";

                                                              matchType = (! invert) ? matchType : matchType == IF ? IFNOT : IF;
                                                              const wchar_t *comparison = matchType == IFNOT ? L" != "    : L" == "  ;
                                                              const wchar_t *connector  = matchType == IFNOT ? logicalAnd : logicalOr;

                                                              bool multipleMatchCodes = (backtrackedCaseId && ! ts.empty())
                                                                                     || ((lookahead == 0 || lookahead->getDpi() < 0) && ts.size() > 1);
                                                              const wchar_t *healthCheckConnector  = invert ? logicalOr : logicalAnd;
                                                              bool needParenthesis = multipleMatchCodes
                                                                                  && healthCheckConnector != connector
                                                                                  && (isCpp() || connector == logicalOr);
                                                              bool trying = false;

                                                              if (*prefix)
                                                              {
                                                                trying = hasBacktracking
                                                                      && grammar->noThrow
                                                                      && methodPrefix == methodPrefixTry;
                                                                lineBuffer = prefix;
                                                                lineBuffer += L" ";
                                                                lineBuffer += isPython() && multipleMatchCodes ? L"(" : ifLeftParen();
                                                                if (trying)
                                                                {
                                                                  if (invert) lineBuffer += isPython() ? L"not " : L"! ";
                                                                  lineBuffer += thiz();
                                                                  lineBuffer += L"viable";
                                                                  lineBuffer += healthCheckConnector;
                                                                  if (needParenthesis)
                                                                  {
                                                                    lineBuffer += L"(";
                                                                  }
                                                                }
                                                              }
                                                              size_t prefixSize = lineBuffer.size();

                                                              const TokenSequence *previousCodeSequence = 0;
                                                              const TokenSequence *codeSequence = 0;

                                                              const wchar_t *matchVariable = k == 0
                                                                                           ? L"code"
                                                                                           : k == 1 && backtrackedCaseId == 0 && (lookahead == 0 || lookahead->getDpi() < 0)
                                                                                           ? token()
                                                                                           : tokenSequence();
                                                              bool first = true;

                                                              OrderedTokenSequenceVector v(ts, __FILE__, __LINE__);
                                                              for (OrderedTokenSequenceVector::const_iterator i = v.begin(); ; )
                                                              {
                                                                const wchar_t *matchCode;
                                                                bool forBacktrack = false;
                                                                if (backtrackedCaseId)
                                                                {
                                                                  matchCode = format.toString<wchar_t>(- backtrackedCaseId);
                                                                  forBacktrack = true;
                                                                  backtrackedCaseId = 0;
                                                                }
                                                                else if (lookahead && lookahead->getDpi() >= 0 && i != v.end())
                                                                {
                                                                  matchCode = format.toString<wchar_t>(caseId);
                                                                  i = v.end();
                                                                }
                                                                else if (! (i != v.end()))
                                                                {
                                                                  break;
                                                                }
                                                                else
                                                                {
                                                                  codeSequence = &*i;
                                                                  ++i;
                                                                  matchCode = ! unlimitedLookahead
                                                                            ? format.toString<wchar_t>(CompressedTokenSet::uniqueSequenceCode(grammar->tokenSequenceFactory, *codeSequence, grammar->externalTokenCode))
                                                                            : lookahead
                                                                            ? format.toString<wchar_t>(lookahead->localSequenceCode(grammar->tokenSequenceFactory, *codeSequence, grammar->externalTokenCode))
                                                                            : format.toString<wchar_t>(grammar->externalTokenCode[codeSequence->first()]);
                                                                }

                                                                switch (matchType)
                                                                {
                                                                case IF:
                                                                case IFNOT:
                                                                  if (! first)
                                                                  {
                                                                    if (isGo() || isPython())
                                                                    {
                                                                      lineBuffer.append(connector, wcslen(connector) - 1);
                                                                    }
                                                                    if (previousCodeSequence)
                                                                    {
                                                                      lineBuffer += L" ";
                                                                      printCodeSequenceAnnotation(*previousCodeSequence);
                                                                    }
                                                                    else
                                                                    {
                                                                      print(lineBuffer.c_str());
                                                                    }

                                                                    if (isGo() || isPython())
                                                                    {
                                                                      lineBuffer.assign(prefixSize, L' ');
                                                                    }
                                                                    else
                                                                    {
                                                                      if (prefixSize < 4)
                                                                      {
                                                                        internalerr();
                                                                      }
                                                                      lineBuffer.assign(prefixSize - 4, L' ');
                                                                      lineBuffer += connector;
                                                                    }
                                                                  }
                                                            #line 445 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 391 "PrintCLike.cpp.template"
                                                                  if (k) lineBuffer += thiz();
                                                                  lineBuffer += matchVariable;
                                                                  lineBuffer += comparison;
                                                                  lineBuffer += matchCode;
                                                                  break;

                                                                case CASE:
                                                            #line 455 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 399 "PrintCLike.cpp.template"
                                                                  lineBuffer.clear();
                                                                  if (isScala())
                                                                  {
                                                                    lineBuffer += first ? L"case " : L"   | ";
                                                                    lineBuffer += matchCode;
                                                                    lineBuffer += i == v.end() ? L" =>" : L"";
                                                                  }
                                                                  else if (isHaxe())
                                                                  {
                                                                    lineBuffer += first ? L"case " : L"   | ";
                                                                    lineBuffer += forBacktrack && i != v.end() ? L"(" : L"";
                                                                    lineBuffer += matchCode;
                                                                    lineBuffer += forBacktrack && i != v.end() ? L")" : L"";
                                                                    lineBuffer += i == v.end() ? L":" : L"";
                                                                  }
                                                                  else if (isGo())
                                                                  {
                                                                    lineBuffer += first ? L"case " : L"     ";
                                                                    lineBuffer += matchCode;
                                                                    lineBuffer += i == v.end() ? L":" : L",";
                                                                  }
                                                                  else if (isPython())
                                                                  {
                                                                    if (first)
                                                                    {
                                                                      lineBuffer += caseId == 1 ? L"if " : L"elif ";
                                                                      if (multipleMatchCodes)
                                                                      {
                                                                        lineBuffer += L"(";
                                                                      }
                                                                    }
                                                                    else
                                                                    {
                                                                      lineBuffer += caseId == 1 ? L"   " : L"     ";
                                                                      if (multipleMatchCodes)
                                                                      {
                                                                        lineBuffer += L" ";
                                                                      }
                                                                    }
                                                                    lineBuffer += L"self.";
                                                                    lineBuffer += matchVariable;
                                                                    lineBuffer += L" == ";
                                                                    lineBuffer += matchCode;
                                                                    if (i == v.end())
                                                                    {
                                                                      if (multipleMatchCodes)
                                                                      {
                                                                        lineBuffer += L"):";
                                                                      }
                                                                      else
                                                                      {
                                                                        lineBuffer += L":";
                                                                      }
                                                                    }
                                                                    else
                                                                    {
                                                                      lineBuffer += L" or ";
                                                                    }
                                                                  }
                                                                  else // not Scala, not Haxe, not Go, not Python
                                                                  {
                                                                    lineBuffer += L"case ";
                                                                    lineBuffer += matchCode;
                                                                    lineBuffer += L":";
                                                                  }
                                                                  if (codeSequence)
                                                                  {
                                                                    lineBuffer += L" ";
                                                                    printCodeSequenceAnnotation(*codeSequence);
                                                                  }
                                                                  else
                                                                  {
                                                                    print(lineBuffer.c_str());
                                                                  }
                                                                  break;

                                                                default:
                                                                  internalerr();
                                                                  break;
                                                                }
                                                                previousCodeSequence = codeSequence;
                                                                first = false;
                                                              }

                                                              if (! first && *prefix)
                                                              {
                                                                if (trying && needParenthesis)
                                                                {
                                                                  lineBuffer += L")";
                                                                }
                                                                if (isPython() && multipleMatchCodes)
                                                                {
                                                                  lineBuffer += L")";
                                                                }
                                                                lineBuffer += ifRightParen();
                                                                lineBuffer += wcsstr(leftBrace(), L"\n") ? L"" : leftBrace();

                                                                if (previousCodeSequence)
                                                                {
                                                                  lineBuffer += L" ";
                                                                  printCodeSequenceAnnotation(*previousCodeSequence);
                                                                }
                                                                else
                                                                {
                                                                  print(lineBuffer.c_str());
                                                                }
                                                                print(wcsstr(leftBrace(), L"\n") ? leftBrace() : L"");
                                                              }
                                                            }

                                                            void PrintCLike::printConsume(Token::Code code)
                                                            {
                                                              Trace("PrintCLike::printConsume");
                                                            #line 571 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 513 "PrintCLike.cpp.template"
                                                              lineBuffer.clear();
                                                              lineBuffer += thiz();
                                                              lineBuffer += L"consume";
                                                              if ((tree || hasBacktracking) && methodPrefix == methodPrefixTry)
                                                              {
                                                                lineBuffer += L"T";
                                                                consumeMethods = 2;
                                                              }
                                                              lineBuffer += L"(";
                                                              lineBuffer += format.toString<wchar_t>(grammar->externalTokenCode[code]);
                                                              lineBuffer += L")";
                                                              lineBuffer += semicolon();
                                                              lineBuffer += L" ";
                                                              printCodeSequenceAnnotation(grammar->tokenSequence(code));
                                                            }

                                                            void PrintCLike::visitNodeList(Node *firstNode)
                                                            {
                                                              Trace("PrintCLike::visitNodeList");

                                                              if (firstNode)
                                                              {
                                                                bool doIndent = firstNode->getParent()
                                                                             && firstNode->getParent() != grammar
                                                                             && ! firstNode->getParent()->isSequence();
                                                                if (doIndent)
                                                                {
                                                                  increaseIndent();
                                                                }
                                                                for (Node *node = firstNode; node; node = node->followingSibling)
                                                                {
                                                                  node->accept(*this);
                                                                }
                                                                if (doIndent) decreaseIndent();
                                                              }
                                                            }

                                                            void PrintCLike::visitOptional(Optional *node)
                                                            {
                                                              Trace("PrintCLike::visitOptional");

                                                              printLookahead(node->k, *grammar->epsilon, 1, node->getLookahead(), node->findsLookahead);
                                                              printASICall(node);
                                                              printBacktracking(node,
                                                                                node->getLookahead(),
                                                                                node->conflictCaseId,
                                                                                node->conflictId,
                                                                                node->firstElementChild);

                                                              MatchType matchType;
                                                              const TokenSequenceSet &match = node->firstElementChild->getMatch(matchType);
                                                              printMatch(node->getLookahead(),
                                                                         node->k,
                                                                         node->conflicts(node->k) == 0 ? 0 : matchType == IF ? 1 : 2,
                                                                         match,
                                                                         matchType,
                                                                         false,
                                                                         1,
                                                                         L"if");
                                                              Visitor::visitNodeWithChildren(node);
                                                              print(rightBrace());
                                                            }

                                                            void PrintCLike::visitZeroOrMore(ZeroOrMore *node)
                                                            {
                                                              Trace("PrintCLike::visitZeroOrMore");

                                                              if (isScala() || isHaxe())
                                                              {
                                                                if (node->loopId == 0)
                                                                  node->loopId = ++loopId;
                                                            #line 645 "PrintCLike.cpp"
  append(L"\n");
  append(L"var c");
                                                            #line 585 "PrintCLike.cpp.template"
                                                                print(format.toString<wchar_t>(node->loopId));
                                                            #line 650 "PrintCLike.cpp"
  append(L" = true");
                                                            #line 586 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 654 "PrintCLike.cpp"
  append(L"\n");
  append(L"while (c");
                                                            #line 588 "PrintCLike.cpp.template"
                                                                print(format.toString<wchar_t>(node->loopId));
                                                                if (hasBacktracking && grammar->noThrow)
                                                                {
                                                            #line 661 "PrintCLike.cpp"
  append(L" && ");
                                                            #line 591 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 665 "PrintCLike.cpp"
  append(L"viable");
                                                            #line 592 "PrintCLike.cpp.template"
                                                                }
                                                            #line 669 "PrintCLike.cpp"
  append(L")");
                                                            #line 593 "PrintCLike.cpp.template"
                                                              }
                                                              else if (isGo())
                                                              {
                                                            #line 675 "PrintCLike.cpp"
  append(L"\n");
  append(L"for");
                                                            #line 597 "PrintCLike.cpp.template"
                                                                if (hasBacktracking && grammar->noThrow)
                                                                {
                                                            #line 681 "PrintCLike.cpp"
  append(L" this.viable");
                                                            #line 599 "PrintCLike.cpp.template"
                                                                }
                                                              }
                                                              else if (isPython())
                                                              {
                                                            #line 688 "PrintCLike.cpp"
  append(L"\n");
  append(L"while ");
                                                            #line 604 "PrintCLike.cpp.template"
                                                                if (hasBacktracking && grammar->noThrow)
                                                                {
                                                            #line 694 "PrintCLike.cpp"
  append(L"self.viable");
                                                            #line 606 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 700 "PrintCLike.cpp"
  append(L"True");
                                                            #line 609 "PrintCLike.cpp.template"
                                                                }
                                                            #line 704 "PrintCLike.cpp"
  append(L":");
                                                            #line 610 "PrintCLike.cpp.template"
                                                              }
                                                              else if (hasBacktracking && grammar->noThrow)
                                                              {
                                                            #line 710 "PrintCLike.cpp"
  append(L"\n");
  append(L"while (");
                                                            #line 614 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 715 "PrintCLike.cpp"
  append(L"viable)");
                                                            #line 615 "PrintCLike.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 721 "PrintCLike.cpp"
  append(L"\n");
  append(L"for (;;)");
                                                            #line 619 "PrintCLike.cpp.template"
                                                              }
                                                              print(leftBrace());
                                                              increaseIndent();

                                                              printLookahead(node->k, *grammar->epsilon, 1, node->getLookahead(), node->findsLookahead);
                                                              printASICall(node);
                                                              printBacktracking(node,
                                                                                node->getLookahead(),
                                                                                node->conflictCaseId,
                                                                                node->conflictId,
                                                                                node->firstElementChild);

                                                              MatchType matchType;
                                                              const TokenSequenceSet &match = node->firstElementChild->getMatch(matchType);
                                                              int backtrackedCaseId = node->conflicts(node->k) == 0 ? 0 : matchType == IF ? 1 : 2;
                                                              const wchar_t *prefix = L"if";
                                                              if (backtrackedCaseId && isScala())
                                                              {
                                                            #line 743 "PrintCLike.cpp"
  append(L"\n");
  append(L"if (lk == -3) {\n");
  append(L"}");
                                                            #line 639 "PrintCLike.cpp.template"
                                                                prefix = L"else if";
                                                              }
                                                              printMatch(node->getLookahead(),
                                                                         node->k,
                                                                         backtrackedCaseId,
                                                                         match,
                                                                         matchType,
                                                                         true,
                                                                         1,
                                                                         prefix);
                                                              if (isScala())
                                                              {
                                                            #line 760 "PrintCLike.cpp"
  append(L"\n");
  append(L"  c");
                                                            #line 652 "PrintCLike.cpp.template"
                                                                print(format.toString<wchar_t>(node->loopId));
                                                            #line 765 "PrintCLike.cpp"
  append(L" = false\n");
  append(L"}\n");
  append(L"else {");
                                                            #line 655 "PrintCLike.cpp.template"
                                                                increaseIndent();
                                                              }
                                                              else
                                                              {
                                                            #line 774 "PrintCLike.cpp"
  append(L"\n");
  append(L"  break");
                                                            #line 660 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                print(rightBrace());
                                                              }
                                                              decreaseIndent();
                                                              Visitor::visitNodeWithChildren(node);
                                                              if (isScala())
                                                              {
                                                            #line 785 "PrintCLike.cpp"
  append(L"\n");
  append(L"}");
                                                            #line 668 "PrintCLike.cpp.template"
                                                                decreaseIndent();
                                                              }
                                                              print(rightBrace());
                                                            }

                                                            void PrintCLike::visitOneOrMore(OneOrMore *node)
                                                            {
                                                              Trace("PrintCLike::visitOneOrMore");

                                                              bool nestedTry = methodPrefix == methodPrefixTry
                                                                            && node->conflicts(node->k);
                                                              if (nestedTry)
                                                              {
                                                                decreaseIndent();
                                                                Visitor::visitNodeWithChildren(node);
                                                                increaseIndent();
                                                              }
                                                              if (isScala() || isHaxe())
                                                              {
                                                                if (node->loopId == 0)
                                                                  node->loopId = ++loopId;
                                                            #line 810 "PrintCLike.cpp"
  append(L"\n");
  append(L"var c");
                                                            #line 690 "PrintCLike.cpp.template"
                                                                print(format.toString<wchar_t>(node->loopId));
                                                            #line 815 "PrintCLike.cpp"
  append(L" = true");
                                                            #line 691 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 819 "PrintCLike.cpp"
  append(L"\n");
  append(L"while (c");
                                                            #line 693 "PrintCLike.cpp.template"
                                                                print(format.toString<wchar_t>(node->loopId));
                                                                if (hasBacktracking && grammar->noThrow)
                                                                {
                                                            #line 826 "PrintCLike.cpp"
  append(L" && ");
                                                            #line 696 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 830 "PrintCLike.cpp"
  append(L"viable");
                                                            #line 697 "PrintCLike.cpp.template"
                                                                }
                                                            #line 834 "PrintCLike.cpp"
  append(L")");
                                                            #line 698 "PrintCLike.cpp.template"
                                                              }
                                                              else if (isGo())
                                                              {
                                                            #line 840 "PrintCLike.cpp"
  append(L"\n");
  append(L"for");
                                                            #line 702 "PrintCLike.cpp.template"
                                                                if (hasBacktracking && grammar->noThrow)
                                                                {
                                                            #line 846 "PrintCLike.cpp"
  append(L" this.viable");
                                                            #line 704 "PrintCLike.cpp.template"
                                                                }
                                                              }
                                                              else if (hasBacktracking && grammar->noThrow)
                                                              {
                                                            #line 853 "PrintCLike.cpp"
  append(L"\n");
  append(L"while ");
                                                            #line 709 "PrintCLike.cpp.template"
                                                                print(ifLeftParen());
                                                                print(thiz());
                                                            #line 859 "PrintCLike.cpp"
  append(L"viable");
                                                            #line 711 "PrintCLike.cpp.template"
                                                                print(ifRightParen());
                                                              }
                                                              else if (isPython())
                                                              {
                                                            #line 866 "PrintCLike.cpp"
  append(L"\n");
  append(L"while True:");
                                                            #line 716 "PrintCLike.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 873 "PrintCLike.cpp"
  append(L"\n");
  append(L"for (;;)");
                                                            #line 720 "PrintCLike.cpp.template"
                                                              }
                                                              print(leftBrace());
                                                              if (! nestedTry)
                                                              {
                                                                Visitor::visitNodeWithChildren(node);
                                                              }

                                                              increaseIndent();
                                                              printLookahead(node->k, *grammar->epsilon, 1, node->getLookahead(), node->findsLookahead);
                                                              printASICall(node);
                                                              printBacktracking(node,
                                                                                node->getLookahead(),
                                                                                node->conflictCaseId,
                                                                                node->conflictId,
                                                                                node->firstElementChild);

                                                              MatchType matchType;
                                                              const TokenSequenceSet &match = node->firstElementChild->getMatch(matchType);
                                                              int backtrackedCaseId = node->conflicts(node->k) == 0 ? 0 : matchType == IF ? 1 : 2;
                                                              const wchar_t *prefix = L"if";
                                                              if (backtrackedCaseId && isScala())
                                                              {
                                                            #line 899 "PrintCLike.cpp"
  append(L"\n");
  append(L"if (lk == -3) {\n");
  append(L"}");
                                                            #line 744 "PrintCLike.cpp.template"
                                                                prefix = L"else if";
                                                              }
                                                              printMatch(node->getLookahead(),
                                                                         node->k,
                                                                         backtrackedCaseId,
                                                                         match,
                                                                         matchType,
                                                                         true,
                                                                         1,
                                                                         prefix);
                                                              if (! isScala())
                                                              {
                                                            #line 916 "PrintCLike.cpp"
  append(L"\n");
  append(L"  break");
                                                            #line 757 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                              }
                                                              else
                                                              {
                                                            #line 924 "PrintCLike.cpp"
  append(L"\n");
  append(L"  c");
                                                            #line 762 "PrintCLike.cpp.template"
                                                                print(format.toString<wchar_t>(node->loopId));
                                                            #line 929 "PrintCLike.cpp"
  append(L" = false");
                                                            #line 763 "PrintCLike.cpp.template"
                                                              }
                                                              print(rightBrace());
                                                              if (nestedTry)
                                                              {
                                                                if (isScala())
                                                                {
                                                            #line 938 "PrintCLike.cpp"
  append(L"\n");
  append(L"else {");
                                                            #line 770 "PrintCLike.cpp.template"
                                                                }
                                                                decreaseIndent();
                                                                Visitor::visitNodeWithChildren(node);
                                                                increaseIndent();

                                                                if (isScala())
                                                                {
                                                            #line 949 "PrintCLike.cpp"
  append(L"\n");
  append(L"}");
                                                            #line 778 "PrintCLike.cpp.template"
                                                                }
                                                              }
                                                              decreaseIndent();
                                                              print(rightBrace());
                                                            }

                                                            void PrintCLike::printCase(const CompressedTokenSet *lookahead, size_t k, Node *c, int backtrackedCaseId)
                                                            {
                                                              Trace("PrintCLike::printCase");

                                                              Node *e = c->element();
                                                              MatchType matchType;
                                                              const TokenSequenceSet &match = e->getMatch(matchType);

                                                              size_t s = 0;

                                                              if (matchType == DEFAULT)
                                                              {
                                                                if (isScala())
                                                                {
                                                            #line 973 "PrintCLike.cpp"
  append(L"\n");
  append(L"case _ =>");
                                                            #line 799 "PrintCLike.cpp.template"
                                                                }
                                                                else if (! isPython())
                                                                {
                                                            #line 980 "PrintCLike.cpp"
  append(L"\n");
  append(L"default:");
                                                            #line 803 "PrintCLike.cpp.template"
                                                                }
                                                                s = size();
                                                                if (   hasBacktracking
                                                                    && grammar->noThrow
                                                                    && c->getParent()->conflicts(k))
                                                                {
                                                                  increaseIndent();
                                                            #line 991 "PrintCLike.cpp"
  append(L"\n");
  append(L"if ");
                                                            #line 811 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                                  print(thiz());
                                                            #line 997 "PrintCLike.cpp"
  append(L"viable");
                                                            #line 813 "PrintCLike.cpp.template"
                                                                  print(ifRightParen());
                                                                  print(leftBrace());
                                                                }
                                                              }
                                                              else
                                                              {
                                                                if (match.empty() && backtrackedCaseId == 0)
                                                                  return;
                                                                printMatch(lookahead,
                                                                           k,
                                                                           backtrackedCaseId,
                                                                           match,
                                                                           matchType,
                                                                           false,
                                                                           e->caseId,
                                                                           L"");
                                                              }
                                                              increaseIndent();
                                                              if (c->hasActiveProcessingInstruction())
                                                              {
                                                                if (*leftBrace() != 0 && *leftBrace() != L'\n')
                                                                {
                                                                  print(L"\n");
                                                                  print(leftBrace() + (*leftBrace() == L' ' ? 1 : 0));
                                                                }
                                                                else
                                                                {
                                                                  print(leftBrace());
                                                                }
                                                                if (! isPython())
                                                                  increaseIndent();

                                                                c->accept(*this);

                                                                if (! isPython())
                                                                  decreaseIndent();
                                                                print(rightBrace());
                                                              }
                                                              else
                                                              {
                                                                size_t s = size();
                                                                c->accept(*this);
                                                                if (isPython() && s == size())
                                                                {
                                                            #line 1044 "PrintCLike.cpp"
  append(L"\n");
  append(L"pass");
                                                            #line 858 "PrintCLike.cpp.template"
                                                                }
                                                              }
                                                              decreaseIndent();
                                                              if (matchType == DEFAULT
                                                               && hasBacktracking
                                                               && grammar->noThrow
                                                               && c->getParent()->conflicts(k))
                                                              {
                                                                decreaseIndent(2);
                                                                print(rightBrace());
                                                                increaseIndent();
                                                              }
                                                              if (   ((matchType != DEFAULT || s == size()) && ! isScala() && ! isHaxe() && ! isGo() && ! isPython())
                                                                  || isCpp()
                                                                  || isCSharp())
                                                              {
                                                            #line 1064 "PrintCLike.cpp"
  append(L"\n");
  append(L"  break");
                                                            #line 875 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                              }
                                                              if (isPython() && s == size())
                                                              {
                                                                unprint(column() + 1);
                                                              }
                                                            }

                                                            int PrintCLike::nestedConflictLevel(Node *node)
                                                            {
                                                              Trace("PrintCLike::nestedConflictLevel");

                                                              int level = 0;
                                                              for (node = node->getParent(); node; node = node->getParent())
                                                              {
                                                                if (node->k > 0 && node->conflicts(node->k))
                                                                {
                                                                  ++level;
                                                                }
                                                              }
                                                              return level;
                                                            }

                                                            void PrintCLike::saveContext(int ncl)
                                                            {
                                                              Trace("PrintCLike::saveContext");
                                                            #line 1094 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 902 "PrintCLike.cpp.template"
                                                              print(intVal());
                                                            #line 1098 "PrintCLike.cpp"
  append(L"b0");
                                                            #line 903 "PrintCLike.cpp.template"
                                                              print(L'A' + ncl);
                                                              print(assign());
                                                              print(thiz());
                                                            #line 1104 "PrintCLike.cpp"
  append(L"b0; ");
                                                            #line 906 "PrintCLike.cpp.template"
                                                              print(intVal());
                                                            #line 1108 "PrintCLike.cpp"
  append(L"e0");
                                                            #line 907 "PrintCLike.cpp.template"
                                                              print(L'A' + ncl);
                                                              print(assign());
                                                              print(thiz());
                                                            #line 1114 "PrintCLike.cpp"
  append(L"e0");
                                                            #line 910 "PrintCLike.cpp.template"
                                                              for (size_t k = 1; k <= grammar->k; ++k)
                                                              {
                                                            #line 1119 "PrintCLike.cpp"
  append(L"; ");
                                                            #line 912 "PrintCLike.cpp.template"
                                                                print(intVal());
                                                            #line 1123 "PrintCLike.cpp"
  append(L"l");
                                                            #line 913 "PrintCLike.cpp.template"
                                                                print(format.toString<wchar_t>(k));
                                                                print(L'A' + ncl);
                                                                print(assign());
                                                                print(thiz());
                                                            #line 1130 "PrintCLike.cpp"
  append(L"l");
                                                            #line 917 "PrintCLike.cpp.template"
                                                                print(format.toString<wchar_t>(k));
                                                                print(semicolon());
                                                            #line 1135 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 920 "PrintCLike.cpp.template"
                                                                print(intVal());
                                                            #line 1139 "PrintCLike.cpp"
  append(L"b");
                                                            #line 921 "PrintCLike.cpp.template"
                                                                print(format.toString<wchar_t>(k));
                                                                print(L'A' + ncl);
                                                                print(assign());
                                                                print(thiz());
                                                            #line 1146 "PrintCLike.cpp"
  append(L"b");
                                                            #line 925 "PrintCLike.cpp.template"
                                                                print(format.toString<wchar_t>(k));
                                                            #line 1150 "PrintCLike.cpp"
  append(L"; ");
                                                            #line 926 "PrintCLike.cpp.template"
                                                                print(intVal());
                                                            #line 1154 "PrintCLike.cpp"
  append(L"e");
                                                            #line 927 "PrintCLike.cpp.template"
                                                                print(format.toString<wchar_t>(k));
                                                                print(L'A' + ncl);
                                                                print(assign());
                                                                print(thiz());
                                                            #line 1161 "PrintCLike.cpp"
  append(L"e");
                                                            #line 931 "PrintCLike.cpp.template"
                                                                print(format.toString<wchar_t>(k));
                                                              }
                                                              print(semicolon());
                                                            }

                                                            void PrintCLike::restoreContext(int ncl)
                                                            {
                                                              Trace("PrintCLike::restoreContext");
                                                            #line 1172 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 940 "PrintCLike.cpp.template"
                                                              print(thiz());
                                                            #line 1176 "PrintCLike.cpp"
  append(L"b0 = b0");
                                                            #line 941 "PrintCLike.cpp.template"
                                                              print(L'A' + ncl);
                                                            #line 1180 "PrintCLike.cpp"
  append(L"; ");
                                                            #line 942 "PrintCLike.cpp.template"
                                                              print(thiz());
                                                            #line 1184 "PrintCLike.cpp"
  append(L"e0 = e0");
                                                            #line 943 "PrintCLike.cpp.template"
                                                              print(L'A' + ncl);
                                                            #line 1188 "PrintCLike.cpp"
  append(L";");
                                                            #line 944 "PrintCLike.cpp.template"
                                                              for (size_t k = 1; k <= grammar->k; ++k)
                                                              {
                                                            #line 1193 "PrintCLike.cpp"
  append(L" ");
                                                            #line 946 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 1197 "PrintCLike.cpp"
  append(L"l");
                                                            #line 947 "PrintCLike.cpp.template"
                                                                print(format.toString<wchar_t>(k));
                                                            #line 1201 "PrintCLike.cpp"
  append(L" = l");
                                                            #line 948 "PrintCLike.cpp.template"
                                                                print(format.toString<wchar_t>(k));
                                                                print(L'A' + ncl);
                                                                if (isPython())
                                                                {
                                                            #line 1208 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 953 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1214 "PrintCLike.cpp"
  append(L"; ");
                                                            #line 956 "PrintCLike.cpp.template"
                                                                }
                                                            #line 1218 "PrintCLike.cpp"
  append(L"if ");
                                                            #line 957 "PrintCLike.cpp.template"
                                                                print(ifLeftParen());
                                                                print(thiz());
                                                            #line 1223 "PrintCLike.cpp"
  append(L"l");
                                                            #line 959 "PrintCLike.cpp.template"
                                                                print(format.toString<wchar_t>(k));
                                                            #line 1227 "PrintCLike.cpp"
  append(L" == 0");
                                                            #line 960 "PrintCLike.cpp.template"
                                                                print(ifRightParen());
                                                                if (isPython())
                                                                {
                                                                  increaseIndent();
                                                            #line 1234 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 965 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1240 "PrintCLike.cpp"
  append(L" {");
                                                            #line 968 "PrintCLike.cpp.template"
                                                                }
                                                                print(thiz());
                                                            #line 1245 "PrintCLike.cpp"
  append(L"end = e");
                                                            #line 970 "PrintCLike.cpp.template"
                                                                print(format.toString<wchar_t>(k - 1));
                                                                print(L'A' + ncl);
                                                                print(semicolon());
                                                                if (isPython())
                                                                {
                                                                  decreaseIndent();
                                                            #line 1254 "PrintCLike.cpp"
  append(L"\n");
  append(L"else:");
                                                            #line 977 "PrintCLike.cpp.template"
                                                                  increaseIndent();
                                                                }
                                                                else
                                                                {
                                                            #line 1262 "PrintCLike.cpp"
  append(L"} else {");
                                                            #line 981 "PrintCLike.cpp.template"
                                                                }
                                                            #line 1266 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 983 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 1270 "PrintCLike.cpp"
  append(L"b");
                                                            #line 984 "PrintCLike.cpp.template"
                                                                print(format.toString<wchar_t>(k));
                                                            #line 1274 "PrintCLike.cpp"
  append(L" = b");
                                                            #line 985 "PrintCLike.cpp.template"
                                                                print(format.toString<wchar_t>(k));
                                                                print(L'A' + ncl);
                                                            #line 1279 "PrintCLike.cpp"
  append(L"; ");
                                                            #line 987 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 1283 "PrintCLike.cpp"
  append(L"e");
                                                            #line 988 "PrintCLike.cpp.template"
                                                                print(format.toString<wchar_t>(k));
                                                            #line 1287 "PrintCLike.cpp"
  append(L" = e");
                                                            #line 989 "PrintCLike.cpp.template"
                                                                print(format.toString<wchar_t>(k));
                                                                print(L'A' + ncl);
                                                            #line 1292 "PrintCLike.cpp"
  append(L";");
                                                            #line 991 "PrintCLike.cpp.template"
                                                              }
                                                            #line 1296 "PrintCLike.cpp"
  append(L" ");
                                                            #line 992 "PrintCLike.cpp.template"
                                                              print(thiz());
                                                            #line 1300 "PrintCLike.cpp"
  append(L"end = e");
                                                            #line 993 "PrintCLike.cpp.template"
                                                              print(format.toString<wchar_t>(grammar->k));
                                                              print(L'A' + ncl);
                                                              print(semicolon());
                                                            #line 1306 "PrintCLike.cpp"
  append(L" ");
                                                            #line 996 "PrintCLike.cpp.template"
                                                              for (size_t k = 1; k <= grammar->k; ++k)
                                                              {
                                                                if (isPython())
                                                                {
                                                                  decreaseIndent();
                                                                }
                                                                else
                                                                {
                                                            #line 1317 "PrintCLike.cpp"
  append(L"}");
                                                            #line 1004 "PrintCLike.cpp.template"
                                                                }
                                                              }
                                                              if (grammar->noThrow)
                                                              {
                                                            #line 1324 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 1009 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 1328 "PrintCLike.cpp"
  append(L"viable = ");
                                                            #line 1010 "PrintCLike.cpp.template"
                                                                if (isPython())
                                                                {
                                                            #line 1333 "PrintCLike.cpp"
  append(L"T");
                                                            #line 1012 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1339 "PrintCLike.cpp"
  append(L"t");
                                                            #line 1015 "PrintCLike.cpp.template"
                                                                }
                                                            #line 1343 "PrintCLike.cpp"
  append(L"rue");
                                                            #line 1016 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                              }
                                                            }

                                                            void PrintCLike::printBacktracking(Node *node,
                                                                                               const CompressedTokenSet *lookahead,
                                                                                               int conflictCaseId,
                                                                                               int conflictId,
                                                                                               Node *predicate)
                                                            {
                                                              Trace("PrintCLike::printBacktracking");

                                                              if (node->conflicts(node->k))
                                                              {
                                                                NodeList cases(false);
                                                                cases.push_back(predicate);
                                                                cases.push_back(predicate);
                                                                printBacktracking(node,
                                                                                  lookahead,
                                                                                  conflictCaseId,
                                                                                  conflictId,
                                                                                  cases);

                                                              }
                                                            }

                                                            void PrintCLike::printBacktracking(Node *node,
                                                                                               const CompressedTokenSet *lookahead,
                                                                                               int conflictCaseId,
                                                                                               int conflictId,
                                                                                               const NodeList &cases)
                                                            {
                                                              Trace("PrintCLike::printBacktracking");

                                                              if (node->conflicts(node->k))
                                                              {
                                                                // printf("grammar->k %d node->k %d\n", grammar->k, node->k);

                                                                MatchType conflictMatchType;
                                                                const TokenSequenceSet &conflictMatch = node->getConflictMatch(conflictMatchType);
                                                                if (! conflictMatch.empty())
                                                                {
                                                                  if (lookahead && lookahead->getDpi() >= 0 && conflictMatchType == IFNOT)
                                                                  {
                                                                    conflictMatchType = IF;
                                                                    conflictCaseId = 0;
                                                                  }
                                                                  printMatch(lookahead,
                                                                             node->k,
                                                                             0,
                                                                             conflictMatch,
                                                                             conflictMatchType,
                                                                             false,
                                                                             conflictCaseId,
                                                                             L"if");
                                                                  increaseIndent();
                                                                }
                                                                if (memoization)
                                                                {
                                                            #line 1405 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 1076 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 1409 "PrintCLike.cpp"
  append(L"lk = ");
                                                            #line 1077 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 1413 "PrintCLike.cpp"
  append(L"memoized(");
                                                            #line 1078 "PrintCLike.cpp.template"
                                                                  print(format.toString<wchar_t>(conflictId));
                                                            #line 1417 "PrintCLike.cpp"
  append(L", ");
                                                            #line 1079 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 1421 "PrintCLike.cpp"
  append(L"e0)");
                                                            #line 1080 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                            #line 1425 "PrintCLike.cpp"
  append(L"\n");
  append(L"if ");
                                                            #line 1082 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                                  print(thiz());
                                                            #line 1431 "PrintCLike.cpp"
  append(L"lk == 0");
                                                            #line 1084 "PrintCLike.cpp.template"
                                                                  print(ifRightParen());
                                                                  print(leftBrace());
                                                                  increaseIndent();
                                                                }
                                                                size_t caseId = 0;
                                                                size_t firstConflictCaseId = 0;
                                                                size_t lastConflictCaseId = 0;
                                                                for (NodeList::const_iterator i = cases.begin(); i != cases.end(); ++i)
                                                                {
                                                                  Node *c = *i;
                                                                  ++caseId;
                                                                  if (c->involvedInConflict)
                                                                  {
                                                                    lastConflictCaseId = caseId;
                                                                    if (firstConflictCaseId == 0)
                                                                    {
                                                                      firstConflictCaseId = caseId;
                                                                    }
                                                                  }
                                                                }

                                                                bool nestedTry = methodPrefix == methodPrefixTry;
                                                                int ncl = nestedConflictLevel(node);
                                                                caseId = 0;
                                                                for (NodeList::const_iterator i = cases.begin(); i != cases.end(); ++i)
                                                                {
                                                                  Node *c = *i;
                                                                  ++caseId;
                                                                  if (caseId == lastConflictCaseId)
                                                                  {
                                                                    if (nestedTry)
                                                                    {
                                                                      if (node->isChoice())
                                                                      {
                                                            #line 1468 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 1119 "PrintCLike.cpp.template"
                                                                        print(thiz());
                                                            #line 1472 "PrintCLike.cpp"
  append(L"lk = -");
                                                            #line 1120 "PrintCLike.cpp.template"
                                                                        print(format.toString<wchar_t>(caseId));
                                                                        print(semicolon());
                                                                      }
                                                                      restoreContext(ncl);
                                                                      if (memoization)
                                                                      {
                                                            #line 1481 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 1127 "PrintCLike.cpp.template"
                                                                        print(thiz());
                                                            #line 1485 "PrintCLike.cpp"
  append(L"memoize(");
                                                            #line 1128 "PrintCLike.cpp.template"
                                                                        print(format.toString<wchar_t>(conflictId));
                                                            #line 1489 "PrintCLike.cpp"
  append(L", e0");
                                                            #line 1129 "PrintCLike.cpp.template"
                                                                        print(L'A' + ncl);
                                                            #line 1493 "PrintCLike.cpp"
  append(L", -");
                                                            #line 1130 "PrintCLike.cpp.template"
                                                                        print(format.toString<wchar_t>(caseId));
                                                            #line 1497 "PrintCLike.cpp"
  append(L")");
                                                            #line 1131 "PrintCLike.cpp.template"
                                                                        print(semicolon());
                                                                      }
                                                                      if (node->isZeroOrMore() || node->isOneOrMore())
                                                                      {
                                                                        if (isScala())
                                                                        {
                                                            #line 1506 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 1138 "PrintCLike.cpp.template"
                                                                          print(thiz());
                                                            #line 1510 "PrintCLike.cpp"
  append(L"lk = -");
                                                            #line 1139 "PrintCLike.cpp.template"
                                                                          print(format.toString<wchar_t>(caseId));
                                                                        }
                                                                        else
                                                                        {
                                                            #line 1517 "PrintCLike.cpp"
  append(L"\n");
  append(L"break");
                                                            #line 1144 "PrintCLike.cpp.template"
                                                                          print(semicolon());
                                                                        }
                                                                      }
                                                                    }
                                                                    else
                                                                    {
                                                            #line 1527 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 1151 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 1531 "PrintCLike.cpp"
  append(L"lk = -");
                                                            #line 1152 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(caseId));
                                                                      print(semicolon());
                                                                    }
                                                                  }
                                                                  else if (c->involvedInConflict)
                                                                  {
                                                                    if (caseId == firstConflictCaseId)
                                                                    {
                                                                      saveContext(ncl);
                                                                    }
                                                                    if (! grammar->noThrow)
                                                                    {
                                                            #line 1546 "PrintCLike.cpp"
  append(L"\n");
  append(L"try");
                                                            #line 1165 "PrintCLike.cpp.template"
                                                                      if (isPython())
                                                                      {
                                                            #line 1552 "PrintCLike.cpp"
  append(L":");
                                                            #line 1167 "PrintCLike.cpp.template"
                                                                      }
                                                                      print(leftBrace());
                                                                      increaseIndent();
                                                                    }
                                                                    if (caseId != firstConflictCaseId)
                                                                    {
                                                                      restoreContext(ncl);
                                                                    }

                                                                    const wchar_t *m = methodPrefix;
                                                                    const wchar_t *v = variant;

                                                                    methodPrefix = methodPrefixTry;

                                                                    const char *flags = getenv("FLAGS");
                                                                    bool hack = flags && strchr(flags, 'H');

                                                                    if (! hack)
                                                                    {
                                                                      variant = L"";
                                                                    }

                                                                    int defaultLk;
                                                                    if (node->isChoice())
                                                                    {
                                                                      c->accept(*this);
                                                                      defaultLk = static_cast<Choice *>(node)->cases.size() + 1;
                                                                    }
                                                                    else
                                                                    {
                                                                      decreaseIndent();
                                                                      visitNodeList(c);
                                                                      increaseIndent();
                                                                      defaultLk = 2;
                                                                    }
                                                                    variant = v;
                                                                    methodPrefix = m;
                                                                    if (grammar->noThrow)
                                                                    {
                                                            #line 1594 "PrintCLike.cpp"
  append(L"\n");
  append(L"if ");
                                                            #line 1207 "PrintCLike.cpp.template"
                                                                      print(ifLeftParen());
                                                                      print(thiz());
                                                            #line 1600 "PrintCLike.cpp"
  append(L"viable");
                                                            #line 1209 "PrintCLike.cpp.template"
                                                                      print(ifRightParen());
                                                                      print(leftBrace());
                                                                      increaseIndent();
                                                                    }

                                                                    if (nestedTry)
                                                                    {
                                                                      if (memoization)
                                                                      {
                                                            #line 1612 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 1219 "PrintCLike.cpp.template"
                                                                        print(thiz());
                                                            #line 1616 "PrintCLike.cpp"
  append(L"memoize(");
                                                            #line 1220 "PrintCLike.cpp.template"
                                                                        print(format.toString<wchar_t>(conflictId));
                                                            #line 1620 "PrintCLike.cpp"
  append(L", e0");
                                                            #line 1221 "PrintCLike.cpp.template"
                                                                        print(L'A' + ncl);
                                                            #line 1624 "PrintCLike.cpp"
  append(L", -");
                                                            #line 1222 "PrintCLike.cpp.template"
                                                                        print(format.toString<wchar_t>(caseId));
                                                            #line 1628 "PrintCLike.cpp"
  append(L")");
                                                            #line 1223 "PrintCLike.cpp.template"
                                                                        print(semicolon());
                                                                      }
                                                                      if (node->isChoice())
                                                                      {
                                                            #line 1635 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 1228 "PrintCLike.cpp.template"
                                                                        print(thiz());
                                                            #line 1639 "PrintCLike.cpp"
  append(L"lk = -");
                                                            #line 1229 "PrintCLike.cpp.template"
                                                                        print(format.toString<wchar_t>(defaultLk));
                                                                        print(semicolon());
                                                                      }
                                                                      else if (node->isZeroOrMore() || node->isOneOrMore())
                                                                      {
                                                                        if (isScala())
                                                                        {
                                                            #line 1649 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 1237 "PrintCLike.cpp.template"
                                                                          print(thiz());
                                                            #line 1653 "PrintCLike.cpp"
  append(L"lk = -3");
                                                            #line 1238 "PrintCLike.cpp.template"
                                                                        }
                                                                        else
                                                                        {
                                                            #line 1659 "PrintCLike.cpp"
  append(L"\n");
  append(L"continue;");
                                                            #line 1242 "PrintCLike.cpp.template"
                                                                        }
                                                                      }
                                                                    }
                                                                    else
                                                                    {
                                                            #line 1668 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 1248 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 1672 "PrintCLike.cpp"
  append(L"lk = -");
                                                            #line 1249 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(caseId));
                                                                      print(semicolon());
                                                                    }

                                                                    decreaseIndent();
                                                                    if (grammar->noThrow)
                                                                    {
                                                            #line 1682 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 1257 "PrintCLike.cpp.template"
                                                                      print(elseWithBraces());
                                                                    }
                                                                    else
                                                                    {
                                                                      print(rightBrace());
                                                                      if (isPython())
                                                                      {
                                                            #line 1692 "PrintCLike.cpp"
  append(L"\n");
  append(L"except ");
                                                            #line 1265 "PrintCLike.cpp.template"
                                                                        print(className.c_str());
                                                            #line 1697 "PrintCLike.cpp"
  append(L".ParseException:");
                                                            #line 1266 "PrintCLike.cpp.template"
                                                                      }
                                                                      else
                                                                      {
                                                            #line 1703 "PrintCLike.cpp"
  append(L"\n");
  append(L"catch ");
                                                            #line 1270 "PrintCLike.cpp.template"
                                                                        if (isScala())
                                                                        {
                                                            #line 1709 "PrintCLike.cpp"
  append(L"{\n");
  append(L"case _: ");
                                                            #line 1273 "PrintCLike.cpp.template"
                                                                          print(className.c_str());
                                                            #line 1714 "PrintCLike.cpp"
  append(L".ParseException =>");
                                                            #line 1274 "PrintCLike.cpp.template"
                                                                        }
                                                                        else
                                                                        {
                                                            #line 1720 "PrintCLike.cpp"
  append(L"(");
                                                            #line 1277 "PrintCLike.cpp.template"
                                                                          if (! isJavascript() && ! isTypescript() && ! isHaxe())
                                                                          {
                                                            #line 1725 "PrintCLike.cpp"
  append(L"ParseException");
                                                            #line 1279 "PrintCLike.cpp.template"
                                                                          }
                                                                          if (! isCSharp() && ! isJavascript() && ! isTypescript() && ! isHaxe())
                                                                          {
                                                            #line 1731 "PrintCLike.cpp"
  append(L" ");
                                                            #line 1282 "PrintCLike.cpp.template"
                                                                          }
                                                                          if (isJava() || isJavascript() || isTypescript() || isHaxe())
                                                                          {
                                                                            print(L"p");
                                                                            print(format.toString<wchar_t>(caseId));
                                                                            print(L'A' + ncl);
                                                                            if (isHaxe())
                                                                            {
                                                            #line 1742 "PrintCLike.cpp"
  append(L": ParseException");
                                                            #line 1290 "PrintCLike.cpp.template"
                                                                            }
                                                                          }
                                                                          else if (isCpp())
                                                                          {
                                                            #line 1749 "PrintCLike.cpp"
  append(L"&");
                                                            #line 1294 "PrintCLike.cpp.template"
                                                                          }
                                                            #line 1753 "PrintCLike.cpp"
  append(L")");
                                                            #line 1295 "PrintCLike.cpp.template"
                                                                          print(leftBrace());
                                                                        }
                                                                      }
                                                                    }
                                                                    increaseIndent();
                                                                  }
                                                                }

                                                                caseId = 0;
                                                                for (NodeList::const_iterator i = cases.begin(); i != cases.end(); ++i)
                                                                {
                                                                  Node *c = *i;
                                                                  ++caseId;
                                                                  if (c->involvedInConflict && caseId != lastConflictCaseId)
                                                                  {
                                                                    decreaseIndent();
                                                                    print(rightBrace());
                                                                  }
                                                                }
                                                                if (! nestedTry)
                                                                {
                                                                  restoreContext(ncl);
                                                                  if (memoization)
                                                                  {
                                                            #line 1780 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 1320 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 1784 "PrintCLike.cpp"
  append(L"memoize(");
                                                            #line 1321 "PrintCLike.cpp.template"
                                                                    print(format.toString<wchar_t>(conflictId));
                                                            #line 1788 "PrintCLike.cpp"
  append(L", ");
                                                            #line 1322 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 1792 "PrintCLike.cpp"
  append(L"e0, ");
                                                            #line 1323 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 1796 "PrintCLike.cpp"
  append(L"lk)");
                                                            #line 1324 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                  }
                                                                }
                                                                else if (node->isOptional())
                                                                {
                                                            #line 1804 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 1330 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 1808 "PrintCLike.cpp"
  append(L"lk = -2");
                                                            #line 1331 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                                if (memoization)
                                                                {
                                                                  decreaseIndent();
                                                                  print(rightBrace());
                                                                }
                                                                if (! conflictMatch.empty())
                                                                {
                                                                  decreaseIndent();
                                                                  if (! (node->k == 1 && (lookahead == 0 || lookahead->getDpi() < 0)))
                                                                  {
                                                                    print(rightBrace());
                                                                  }
                                                                  else
                                                                  {
                                                            #line 1827 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 1348 "PrintCLike.cpp.template"
                                                                    print(elseWithBraces());
                                                            #line 1831 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 1350 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 1836 "PrintCLike.cpp"
  append(L"lk = ");
                                                            #line 1351 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 1840 "PrintCLike.cpp"
  append(L"l1");
                                                            #line 1352 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                    print(rightBrace());
                                                                  }
                                                                }
                                                              }
                                                            }

                                                            void PrintCLike::visitChoice(Choice *node)
                                                            {
                                                              Trace("PrintCLike::visitChoice");

                                                              printLookahead(node->k, *grammar->epsilon, 1, node->getLookahead(), node->findsLookahead);
                                                              printASICall(node);
                                                              printBacktracking(node,
                                                                                node->getLookahead(),
                                                                                node->conflictCaseId,
                                                                                node->conflictId,
                                                                                node->cases);
                                                              size_t s = size();
                                                              if (isScala())
                                                              {
                                                                if (node->k == 1 && node->conflicts(node->k) == 0 && node->getLookahead()->getDpi() < 0)
                                                                {
                                                            #line 1866 "PrintCLike.cpp"
  append(L"\n");
  append(L"l1 match");
                                                            #line 1376 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1873 "PrintCLike.cpp"
  append(L"\n");
  append(L"lk match");
                                                            #line 1380 "PrintCLike.cpp.template"
                                                                }
                                                              }
                                                              else if (! isPython())
                                                              {
                                                            #line 1881 "PrintCLike.cpp"
  append(L"\n");
  append(L"switch ");
                                                            #line 1385 "PrintCLike.cpp.template"
                                                                print(ifLeftParen());
                                                                print(thiz());
                                                                if (node->k == 1 && node->conflicts(node->k) == 0 && node->getLookahead()->getDpi() < 0)
                                                                {
                                                                  print(token());
                                                                }
                                                                else
                                                                {
                                                                  print(tokenSequence());
                                                                }
                                                                print(ifRightParen());
                                                              }
                                                              print(leftBrace());

                                                              Node *defaultCase = 0;
                                                              size_t caseId = 0;
                                                              for (NodeList::iterator i = node->cases.begin(); i != node->cases.end(); ++i)
                                                              {
                                                                Node *c = *i;
                                                                ++caseId;
                                                                MatchType matchType;
                                                                c->getMatch(matchType);
                                                                if (matchType == DEFAULT)
                                                                {
                                                                  defaultCase = c;
                                                                }
                                                                else
                                                                {
                                                                  int backtrackedCaseId = c->involvedInConflict ? caseId : 0;
                                                                  printCase(node->getLookahead(), node->k, c, backtrackedCaseId);
                                                                }
                                                              }
                                                              bool nestedTry = node->conflicts(node->k)
                                                                            && methodPrefix == methodPrefixTry;
                                                              if (nestedTry)
                                                              {
                                                                if (isPython())
                                                                {
                                                            #line 1923 "PrintCLike.cpp"
  append(L"\n");
  append(L"elif self.");
                                                            #line 1424 "PrintCLike.cpp.template"
                                                                  if (node->k == 1 && node->conflicts(node->k) == 0 && node->getLookahead()->getDpi() < 0)
                                                                  {
                                                                    print(token());
                                                                  }
                                                                  else
                                                                  {
                                                                    print(tokenSequence());
                                                                  }
                                                            #line 1935 "PrintCLike.cpp"
  append(L" == -");
                                                            #line 1432 "PrintCLike.cpp.template"
                                                                  print(format.toString<wchar_t>(node->cases.size() + 1));
                                                            #line 1939 "PrintCLike.cpp"
  append(L":\n");
  append(L"  pass");
                                                            #line 1434 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1946 "PrintCLike.cpp"
  append(L"\n");
  append(L"case -");
                                                            #line 1438 "PrintCLike.cpp.template"
                                                                  print(format.toString<wchar_t>(node->cases.size() + 1));
                                                                  if (isScala())
                                                                  {
                                                            #line 1953 "PrintCLike.cpp"
  append(L" =>");
                                                            #line 1441 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isHaxe())
                                                                  {
                                                            #line 1959 "PrintCLike.cpp"
  append(L":");
                                                            #line 1444 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 1965 "PrintCLike.cpp"
  append(L":");
                                                            #line 1447 "PrintCLike.cpp.template"
                                                                    if (! isGo())
                                                                    {
                                                            #line 1970 "PrintCLike.cpp"
  append(L"\n");
  append(L"  break");
                                                            #line 1450 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                                    }
                                                                  }
                                                                }
                                                              }
                                                              if (! isPython())
                                                              {
                                                                printCase(node->getLookahead(), node->k, defaultCase, 0);
                                                                print(rightBrace());
                                                              }
                                                              else if (s != size())
                                                              {
                                                            #line 1986 "PrintCLike.cpp"
  append(L"\n");
  append(L"else:");
                                                            #line 1463 "PrintCLike.cpp.template"
                                                                printCase(node->getLookahead(), node->k, defaultCase, 0);
                                                              }
                                                              else
                                                              {
                                                                decreaseIndent();
                                                                printCase(node->getLookahead(), node->k, defaultCase, 0);
                                                                increaseIndent();
                                                              }
                                                            }

                                                            void PrintCLike::visitProduction(Production *node)
                                                            {
                                                              Trace("PrintCLike::visitProduction");

                                                              if (! isGo())
                                                                increaseIndent();
                                                              loopId = 0;
                                                              WString functionName(methodPrefix);
                                                              functionName.append(Format::acceptableName<WString>(node->name));
                                                              if (isGo() && node->isStartSymbol())
                                                              {
                                                            #line 2011 "PrintCLike.cpp"
  append(L"\n");
  append(L"func (this *");
                                                            #line 1485 "PrintCLike.cpp.template"
                                                                print(className.c_str());
                                                            #line 2016 "PrintCLike.cpp"
  append(L") ");
                                                            #line 1486 "PrintCLike.cpp.template"
                                                                functionName[0] = towupper(functionName[0]);
                                                                print(functionName.c_str());
                                                            #line 2021 "PrintCLike.cpp"
  append(L"() (pe *ParseError) {\n");
  append(L"  defer func() {\n");
  append(L"    r := recover()\n");
  append(L"    if r != nil {\n");
  append(L"      e, isParseError := r.(*ParseError)\n");
  append(L"      if isParseError {\n");
  append(L"        pe = e\n");
  append(L"      }\n");
  append(L"    }\n");
  append(L"  }()\n");
                                                            #line 1498 "PrintCLike.cpp.template"
                                                              }
                                                              else
                                                              {
                                                                openMethod(voidType(), L"", functionName.c_str(), L"");
                                                                print(leftBrace());
                                                              }
                                                              if (isLrParser)
                                                              {
                                                                if (! useGlr)
                                                                {
                                                            #line 2043 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 1509 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 2048 "PrintCLike.cpp"
  append(L"top = -1");
                                                            #line 1510 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                            #line 2053 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 1513 "PrintCLike.cpp.template"
                                                                if (useGlr && ! isCpp())
                                                                {
                                                                  print(thiz());
                                                            #line 2060 "PrintCLike.cpp"
  append(L"thread = ");
                                                            #line 1516 "PrintCLike.cpp.template"
                                                                }
                                                                print(thiz());
                                                            #line 2065 "PrintCLike.cpp"
  append(L"parse(");
                                                            #line 1518 "PrintCLike.cpp.template"
                                                                print(format.toString<wchar_t>(node->nonterminalCode));
                                                            #line 2069 "PrintCLike.cpp"
  append(L", ");
                                                            #line 1519 "PrintCLike.cpp.template"
                                                                print(format.toString<wchar_t>((*grammar->states)[node->state]->getStateId()));
                                                                if (tree)
                                                                {
                                                            #line 2075 "PrintCLike.cpp"
  append(L", ");
                                                            #line 1522 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 2079 "PrintCLike.cpp"
  append(L"eventHandler");
                                                            #line 1523 "PrintCLike.cpp.template"
                                                                }
                                                                if (useGlr)
                                                                {
                                                            #line 2085 "PrintCLike.cpp"
  append(L", ");
                                                            #line 1526 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 2089 "PrintCLike.cpp"
  append(L"thread");
                                                            #line 1527 "PrintCLike.cpp.template"
                                                                }
                                                            #line 2093 "PrintCLike.cpp"
  append(L")");
                                                            #line 1528 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                              }
                                                              else
                                                              {
                                                                if (trace)
                                                                {
                                                            #line 2102 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 1535 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 2107 "PrintCLike.cpp"
  append(L"traceNonterminal(");
                                                            #line 1536 "PrintCLike.cpp.template"
                                                                  print(stringIntroducer());
                                                            #line 2111 "PrintCLike.cpp"
  append(L"\"");
                                                            #line 1537 "PrintCLike.cpp.template"
                                                                  print(methodPrefix, wcslen(methodPrefix) - 1);
                                                            #line 2115 "PrintCLike.cpp"
  append(L"\", ");
                                                            #line 1538 "PrintCLike.cpp.template"
                                                                  print(stringIntroducer());
                                                            #line 2119 "PrintCLike.cpp"
  append(L"\"start\", ");
                                                            #line 1539 "PrintCLike.cpp.template"
                                                                  print(stringIntroducer());
                                                            #line 2123 "PrintCLike.cpp"
  append(L"\"");
                                                            #line 1540 "PrintCLike.cpp.template"
                                                                  print(node->name);
                                                            #line 2127 "PrintCLike.cpp"
  append(L"\")");
                                                            #line 1541 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                                if (tree && methodPrefix != methodPrefixTry)
                                                                {
                                                            #line 2134 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 1546 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 2139 "PrintCLike.cpp"
  append(L"eventHandler");
                                                            #line 1547 "PrintCLike.cpp.template"
                                                                  print(arrow());
                                                                  if (isGo())
                                                                  {
                                                            #line 2145 "PrintCLike.cpp"
  append(L"S");
                                                            #line 1550 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 2151 "PrintCLike.cpp"
  append(L"s");
                                                            #line 1553 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 2155 "PrintCLike.cpp"
  append(L"tartNonterminal(");
                                                            #line 1554 "PrintCLike.cpp.template"
                                                                  print(format.toString<wchar_t>(node->nonterminalCode));
                                                            #line 2159 "PrintCLike.cpp"
  append(L", ");
                                                            #line 1555 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 2163 "PrintCLike.cpp"
  append(L"e0)");
                                                            #line 1556 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                                visitNodeList(node->firstChild);

                                                                if (tree && methodPrefix != methodPrefixTry)
                                                                {
                                                            #line 2172 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 1563 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 2177 "PrintCLike.cpp"
  append(L"eventHandler");
                                                            #line 1564 "PrintCLike.cpp.template"
                                                                  print(arrow());
                                                                  if (isGo())
                                                                  {
                                                            #line 2183 "PrintCLike.cpp"
  append(L"E");
                                                            #line 1567 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 2189 "PrintCLike.cpp"
  append(L"e");
                                                            #line 1570 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 2193 "PrintCLike.cpp"
  append(L"ndNonterminal(");
                                                            #line 1571 "PrintCLike.cpp.template"
                                                                  print(format.toString<wchar_t>(node->nonterminalCode));
                                                            #line 2197 "PrintCLike.cpp"
  append(L", ");
                                                            #line 1572 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 2201 "PrintCLike.cpp"
  append(L"e0)");
                                                            #line 1573 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                                if (trace)
                                                                {
                                                            #line 2208 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 1578 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 2213 "PrintCLike.cpp"
  append(L"traceNonterminal(");
                                                            #line 1579 "PrintCLike.cpp.template"
                                                                  print(stringIntroducer());
                                                            #line 2217 "PrintCLike.cpp"
  append(L"\"");
                                                            #line 1580 "PrintCLike.cpp.template"
                                                                  print(methodPrefix, wcslen(methodPrefix) - 1);
                                                            #line 2221 "PrintCLike.cpp"
  append(L"\", ");
                                                            #line 1581 "PrintCLike.cpp.template"
                                                                  print(stringIntroducer());
                                                            #line 2225 "PrintCLike.cpp"
  append(L"\"end\", ");
                                                            #line 1582 "PrintCLike.cpp.template"
                                                                  print(stringIntroducer());
                                                            #line 2229 "PrintCLike.cpp"
  append(L"\"");
                                                            #line 1583 "PrintCLike.cpp.template"
                                                                  print(node->name);
                                                            #line 2233 "PrintCLike.cpp"
  append(L"\")");
                                                            #line 1584 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                              }
                                                              if (node->isStartSymbol())
                                                              {
                                                                printFlush(1);
                                                              }
                                                              if (isGo() && node->isStartSymbol())
                                                              {
                                                            #line 2245 "PrintCLike.cpp"
  append(L"\n");
  append(L"  return nil");
                                                            #line 1594 "PrintCLike.cpp.template"
                                                              }
                                                              print(rightBrace());
                                                              if ((isJavascript()  && ! isTypescript()) && node->isStartSymbol())
                                                              {
                                                            #line 2253 "PrintCLike.cpp"
  append(L";");
                                                            #line 1598 "PrintCLike.cpp.template"
                                                              }
                                                            #line 2257 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 1600 "PrintCLike.cpp.template"
                                                              if (! isGo())
                                                                decreaseIndent();
                                                            }

                                                            void PrintCLike::visitRef(Ref *node)
                                                            {
                                                              Trace("PrintCLike::visitRef");

                                                              printLookahead(1, *grammar->epsilon, 1, node->getLookahead(), node->findsLookahead);
                                                              printASICall(node);
                                                              if (node->lexical)
                                                              {
                                                                printConsume(node->lexical->tokenCode);
                                                              }
                                                              else
                                                              {
                                                                if (   node->whitespaceAllowance == IMPLICIT
                                                                    && methodPrefix != methodPrefixTry
                                                                    && tree)
                                                                {
                                                            #line 2280 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 1621 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 2284 "PrintCLike.cpp"
  append(L"whitespace");
                                                            #line 1622 "PrintCLike.cpp.template"
                                                                  if (! isScala())
                                                                  {
                                                            #line 2289 "PrintCLike.cpp"
  append(L"()");
                                                            #line 1624 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(semicolon());
                                                                }
                                                                if (   hasBacktracking
                                                                    && grammar->noThrow
                                                                    && methodPrefix == methodPrefixTry)
                                                                {
                                                            #line 2299 "PrintCLike.cpp"
  append(L"\n");
  append(L"if ");
                                                            #line 1632 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                                  print(thiz());
                                                            #line 2305 "PrintCLike.cpp"
  append(L"viable");
                                                            #line 1634 "PrintCLike.cpp.template"
                                                                  print(ifRightParen());
                                                                  print(leftBrace());
                                                                  increaseIndent();
                                                                }
                                                            #line 2312 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 1639 "PrintCLike.cpp.template"
                                                                if (isJavascript()
                                                                 && methodPrefix != methodPrefixTry
                                                                 && node->nonTerminal->isStartSymbol())
                                                                {
                                                                  print(L"thisParser.");
                                                                }
                                                                else
                                                                {
                                                                  print(thiz());
                                                                }
                                                                if (isGo() && node->nonTerminal->isStartSymbol())
                                                                {
                                                                  print(towupper(methodPrefix[0]));
                                                                }
                                                                else
                                                                {
                                                                  print(methodPrefix[0]);
                                                                }
                                                                print(methodPrefix + 1);
                                                                print(Format::acceptableName<WString>(node->name).c_str());
                                                                if (! isScala())
                                                                {
                                                            #line 2337 "PrintCLike.cpp"
  append(L"()");
                                                            #line 1661 "PrintCLike.cpp.template"
                                                                }
                                                                print(semicolon());
                                                                if (   hasBacktracking
                                                                    && grammar->noThrow
                                                                    && methodPrefix == methodPrefixTry)
                                                                {
                                                                  decreaseIndent();
                                                                  print(rightBrace());
                                                                }
                                                              }
                                                            }

                                                            void PrintCLike::visitString(String *node)
                                                            {
                                                              Trace("PrintCLike::visitString");

                                                              printLookahead(1, *grammar->epsilon, 1, node->getLookahead(), node->findsLookahead);
                                                              printASICall(node);
                                                              printConsume(node->lexical->tokenCode);
                                                            }

                                                            void PrintCLike::visitProcessingInstruction(ProcessingInstruction *node)
                                                            {
                                                              Trace("PrintCLike::visitProcessingInstruction");

                                                              if (variant != 0 && wcscmp(node->target, variant) == 0)
                                                              {
                                                            #line 2367 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 1689 "PrintCLike.cpp.template"
                                                                int spaces = isPython() ? 0 : Math::max(0, static_cast<int>(piIndent) - getIndent());
                                                                print(spaces, L" ");
                                                                print(lineCommentPrefix());
                                                            #line 2373 "PrintCLike.cpp"
  append(L"line ");
                                                            #line 1692 "PrintCLike.cpp.template"
                                                                print(format.toString<wchar_t>(node->line));
                                                            #line 2377 "PrintCLike.cpp"
  append(L" \"");
                                                            #line 1693 "PrintCLike.cpp.template"
                                                                print(node->fileName);
                                                            #line 2381 "PrintCLike.cpp"
  append(L"\"\n");
                                                            #line 1695 "PrintCLike.cpp.template"
                                                                print(spaces, L" ");
                                                                wchar_t *reIndented = format.reIndent(node->content, spaces);
                                                                print(reIndented);
                                                            #line 2387 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 1699 "PrintCLike.cpp.template"
                                                                free(reIndented);
                                                                print(spaces, L" ");
                                                                print(lineCommentPrefix());
                                                            #line 2393 "PrintCLike.cpp"
  append(L"line ");
                                                            #line 1702 "PrintCLike.cpp.template"
                                                                print(format.toString<wchar_t>(lineNo + 1));
                                                            #line 2397 "PrintCLike.cpp"
  append(L" \"");
                                                            #line 1703 "PrintCLike.cpp.template"
                                                                print(wFileName.c_str());
                                                            #line 2401 "PrintCLike.cpp"
  append(L"\"");
                                                            #line 1704 "PrintCLike.cpp.template"
                                                              }
                                                            }

                                                            void PrintCLike::printProlog()
                                                            {
                                                              Trace("PrintCLike::printProlog");

                                                              if (! isGo())
                                                                increaseIndent();
                                                              if (isJavascript())
                                                              {
                                                            #line 2415 "PrintCLike.cpp"
  append(L"\n");
  append(L"function init(source");
                                                            #line 1716 "PrintCLike.cpp.template"
                                                                if (noLexer)
                                                                {
                                                            #line 2421 "PrintCLike.cpp"
  append(L", l");
                                                            #line 1718 "PrintCLike.cpp.template"
                                                                }
                                                                if (tree)
                                                                {
                                                            #line 2427 "PrintCLike.cpp"
  append(L", parsingEventHandler");
                                                            #line 1721 "PrintCLike.cpp.template"
                                                                }
                                                            #line 2431 "PrintCLike.cpp"
  append(L")");
                                                            #line 1722 "PrintCLike.cpp.template"
                                                              }
                                                              else
                                                              {
                                                                WString args(isJava() ? (codepoints ? L"int[] " : L"CharSequence ") : isTypescript() ? L"string " : stringType());
                                                                args += L"source";
                                                                if (noLexer) args += L", Lexer l";
                                                                if (tree)
                                                                {
                                                                  args += L", ";
                                                                  if (isScala()) args += staticPrefix();
                                                                  args += isLrParser
                                                                        ? L"BottomUpEventHandler"
                                                                        : isTypescript()
                                                                        ? L"ParsingEventHandler"
                                                                        : L"EventHandler";
                                                                  args += L" ";
                                                                  if (isCpp()) args += L"*";
                                                                  args += L"parsingEventHandler";
                                                                }
                                                                if (isJava() && codepoints)
                                                                {
                                                                  WString charSequenceArgs(L"CharSequence source");
                                                                  if (tree)
                                                                  {
                                                                    charSequenceArgs += isLrParser
                                                                                      ? L", BottomUpEventHandler parsingEventHandler"
                                                                                      : L", EventHandler parsingEventHandler";
                                                                  }
                                                                  openMethod(voidType(), L"", L"initialize", charSequenceArgs.c_str());
                                                                  print(leftBrace());
                                                            #line 2464 "PrintCLike.cpp"
  append(L"\n");
  append(L"  initialize(source.codePoints().toArray()");
                                                            #line 1753 "PrintCLike.cpp.template"
                                                                  if (tree)
                                                                  {
                                                            #line 2470 "PrintCLike.cpp"
  append(L", parsingEventHandler");
                                                            #line 1755 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 2474 "PrintCLike.cpp"
  append(L");");
                                                            #line 1756 "PrintCLike.cpp.template"
                                                                  print(rightBrace());
                                                            #line 2478 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 1758 "PrintCLike.cpp.template"
                                                                }
                                                                openMethod(voidType(), L"", L"initialize", args.c_str());
                                                              }
                                                              print(leftBrace());
                                                              if (tree)
                                                              {
                                                            #line 2487 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 1765 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 2492 "PrintCLike.cpp"
  append(L"eventHandler = parsingEventHandler");
                                                            #line 1766 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                              }
                                                            #line 2497 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 1769 "PrintCLike.cpp.template"
                                                              print(thiz());
                                                            #line 2502 "PrintCLike.cpp"
  append(L"input = ");
                                                            #line 1770 "PrintCLike.cpp.template"
                                                              if (isHaxe())
                                                              {
                                                            #line 2507 "PrintCLike.cpp"
  append(L"Bytes.ofString(source)");
                                                            #line 1772 "PrintCLike.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 2513 "PrintCLike.cpp"
  append(L"source");
                                                            #line 1775 "PrintCLike.cpp.template"
                                                              }
                                                              print(semicolon());
                                                              if (noLexer)
                                                              {
                                                            #line 2520 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 1780 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 2525 "PrintCLike.cpp"
  append(L"lexer = l");
                                                            #line 1781 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 2529 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 1783 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 2534 "PrintCLike.cpp"
  append(L"lexer.reset(input)");
                                                            #line 1784 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                              }
                                                              else if (isGo() || isPython())
                                                              {
                                                            #line 2541 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 1789 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 2546 "PrintCLike.cpp"
  append(L"size = len(source)");
                                                            #line 1790 "PrintCLike.cpp.template"
                                                              }
                                                              else if (! isCpp())
                                                              {
                                                            #line 2552 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 1794 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 2557 "PrintCLike.cpp"
  append(L"size = source.");
                                                            #line 1795 "PrintCLike.cpp.template"
                                                                print(isCSharp() ? L"L" : L"l");
                                                            #line 2561 "PrintCLike.cpp"
  append(L"ength");
                                                            #line 1796 "PrintCLike.cpp.template"
                                                                if (! isJavascript() && ! isTypescript() && ! isScala() && ! isHaxe() && ! isCSharp() && ! (isJava() && codepoints))
                                                                {
                                                            #line 2566 "PrintCLike.cpp"
  append(L"()");
                                                            #line 1798 "PrintCLike.cpp.template"
                                                                }
                                                                print(semicolon());
                                                              }
                                                              if (! interfaceName.empty() && useGlr)
                                                              {
                                                            #line 2574 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 1804 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                                print(isGo() ? L"R" : L"r");
                                                            #line 2580 "PrintCLike.cpp"
  append(L"eset()");
                                                            #line 1806 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                print(rightBrace());
                                                            #line 2585 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 1809 "PrintCLike.cpp.template"
                                                                openMethod(voidType(), L"", L"reset", L"");
                                                                print(leftBrace());
                                                              }
                                                              if (isLrParser && ! useGlr)
                                                              {
                                                                if (isPython())
                                                                {
                                                            #line 2595 "PrintCLike.cpp"
  append(L"\n");
  append(L"  self.iStack = [0 for _ in range(192)]");
                                                            #line 1817 "PrintCLike.cpp.template"
                                                                }
                                                                else if (isGo())
                                                                {
                                                            #line 2602 "PrintCLike.cpp"
  append(L"\n");
  append(L"  this.iStack = make([]int, 192)\n");
  append(L"  this.top = -1");
                                                            #line 1822 "PrintCLike.cpp.template"
                                                                }
                                                              }
                                                              if (useGlr)
                                                              {
                                                            #line 2611 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 1827 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 2616 "PrintCLike.cpp"
  append(L"maxId = 0");
                                                            #line 1828 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 2620 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 1830 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 2625 "PrintCLike.cpp"
  append(L"thread = ");
                                                            #line 1831 "PrintCLike.cpp.template"
                                                                if (isScala())
                                                                {
                                                            #line 2630 "PrintCLike.cpp"
  append(L"new ");
                                                            #line 1833 "PrintCLike.cpp.template"
                                                                  print(className.c_str());
                                                            #line 2634 "PrintCLike.cpp"
  append(L".ParsingThread");
                                                            #line 1834 "PrintCLike.cpp.template"
                                                                }
                                                                else if (isPython())
                                                                {
                                                                  print(className.c_str());
                                                            #line 2641 "PrintCLike.cpp"
  append(L".ParsingThread()");
                                                            #line 1838 "PrintCLike.cpp.template"
                                                                }
                                                                else if (isGo())
                                                                {
                                                            #line 2647 "PrintCLike.cpp"
  append(L"new(ParsingThread)");
                                                            #line 1841 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 2653 "PrintCLike.cpp"
  append(L"new ParsingThread()");
                                                            #line 1844 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                                if (isCSharp() || isCpp() || isHaxe() || isScala() || isTypescript() || isGo() || isPython())
                                                                {
                                                            #line 2660 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 1849 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 2665 "PrintCLike.cpp"
  append(L"thread");
                                                            #line 1850 "PrintCLike.cpp.template"
                                                                  print(arrow());
                                                            #line 2669 "PrintCLike.cpp"
  append(L"parser = ");
                                                            #line 1851 "PrintCLike.cpp.template"
                                                                  if (isPython())
                                                                  {
                                                            #line 2674 "PrintCLike.cpp"
  append(L"self");
                                                            #line 1853 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 2680 "PrintCLike.cpp"
  append(L"this");
                                                            #line 1856 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(semicolon());
                                                                }
                                                            #line 2686 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 1860 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 2691 "PrintCLike.cpp"
  append(L"thread");
                                                            #line 1861 "PrintCLike.cpp.template"
                                                                print(arrow());
                                                              }
                                                              else
                                                              {
                                                            #line 2698 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 1866 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                              }
                                                              print(isGo() ? L"R" : L"r");
                                                            #line 2705 "PrintCLike.cpp"
  append(L"eset(0, 0, 0)");
                                                            #line 1869 "PrintCLike.cpp.template"
                                                              print(semicolon());
                                                              print(rightBrace());
                                                            #line 2710 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 1872 "PrintCLike.cpp.template"
                                                              if (! isGo())
                                                                decreaseIndent();
                                                              if (! useGlr)
                                                              {
                                                                printInitializer();
                                                              }
                                                              if (! isGo())
                                                                increaseIndent();
                                                              if (isJavascript())
                                                              {
                                                            #line 2723 "PrintCLike.cpp"
  append(L"\n");
  append(L"this.reset = function(l, b, e)\n");
  append(L"{\n");
  append(L"  ");
                                                            #line 1885 "PrintCLike.cpp.template"
                                                                if (useGlr)
                                                                {
                                                            #line 2731 "PrintCLike.cpp"
  append(L"thread.");
                                                            #line 1887 "PrintCLike.cpp.template"
                                                                }
                                                            #line 2735 "PrintCLike.cpp"
  append(L"reset(l, b, e);\n");
  append(L"};\n");
                                                            #line 1890 "PrintCLike.cpp.template"
                                                                openMethod(L"static ", stringType(), L"getOffendingToken", L"ParseException e");
                                                                print(leftBrace());
                                                            #line 2741 "PrintCLike.cpp"
  append(L"\n");
  append(L"  var o = e.getOffending();\n");
  append(L"  return o >= 0 ? ");
                                                            #line 1894 "PrintCLike.cpp.template"
                                                                print(staticPrefix());
                                                            #line 2747 "PrintCLike.cpp"
  append(L"TOKEN[o] : ");
                                                            #line 1895 "PrintCLike.cpp.template"
                                                                print(nullPtr());
                                                            #line 2751 "PrintCLike.cpp"
  append(L";\n");
  append(L"};\n");
                                                            #line 1898 "PrintCLike.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 2757 "PrintCLike.cpp"
  append(L"\n");
  append(L"this.getTerminalName = function(id)\n");
  append(L"{\n");
  append(L"  return ");
                                                            #line 1903 "PrintCLike.cpp.template"
                                                                  print(staticPrefix());
                                                            #line 2764 "PrintCLike.cpp"
  append(L"TOKEN[id];\n");
  append(L"};\n");
  append(L"\n");
  append(L"this.getNonterminalName = function(id)\n");
  append(L"{\n");
  append(L"  return ");
                                                            #line 1909 "PrintCLike.cpp.template"
                                                                  printSyntheticNamePrefix();
                                                                  print(staticPrefix());
                                                            #line 2774 "PrintCLike.cpp"
  append(L"NONTERMINAL[id]");
                                                            #line 1911 "PrintCLike.cpp.template"
                                                                  printSyntheticNameSuffix();
                                                            #line 2778 "PrintCLike.cpp"
  append(L";\n");
  append(L"};\n");
                                                            #line 1914 "PrintCLike.cpp.template"
                                                                }
                                                              }
                                                              else if (isTypescript())
                                                              {
                                                                if (useGlr)
                                                                {
                                                            #line 2788 "PrintCLike.cpp"
  append(L"\n");
  append(L"public reset(l: number, b: number, e: number)\n");
  append(L"{\n");
  append(L"  this.thread.reset(l, b, e);\n");
  append(L"}\n");
                                                            #line 1925 "PrintCLike.cpp.template"
                                                                }
                                                            #line 2796 "PrintCLike.cpp"
  append(L"\n");
  append(L"getOffendingToken(e: ParseException)\n");
  append(L"{");
  append(L"\n");
  append(L"  var o = e.getOffending();\n");
  append(L"  return o >= 0 ? Parser.TOKEN[o] : ");
                                                            #line 1931 "PrintCLike.cpp.template"
                                                                print(nullPtr());
                                                            #line 2805 "PrintCLike.cpp"
  append(L";\n");
  append(L"}\n");
                                                            #line 1934 "PrintCLike.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 2811 "PrintCLike.cpp"
  append(L"\n");
  append(L"public static getTerminalName(id: number): string\n");
  append(L"{\n");
  append(L"  return Parser.TOKEN[id];\n");
  append(L"}\n");
  append(L"\n");
  append(L"public static getNonterminalName(id: number): string\n");
  append(L"{\n");
  append(L"  return ");
                                                            #line 1944 "PrintCLike.cpp.template"
                                                                  printSyntheticNamePrefix();
                                                            #line 2823 "PrintCLike.cpp"
  append(L"Parser.NONTERMINAL[id]");
                                                            #line 1945 "PrintCLike.cpp.template"
                                                                  printSyntheticNameSuffix();
                                                            #line 2827 "PrintCLike.cpp"
  append(L";\n");
  append(L"}\n");
                                                            #line 1948 "PrintCLike.cpp.template"
                                                                }
                                                              }
                                                              else if (isScala())
                                                              {
                                                              }
                                                              else if (isGo())
                                                              {
                                                            #line 2838 "PrintCLike.cpp"
  append(L"\n");
  append(L"func GetOffendingToken(e ParseError) string {\n");
  append(L"  if e.GetOffending() < 0 {\n");
  append(L"    return \"\"\n");
  append(L"  } else {\n");
  append(L"    return ");
                                                            #line 1960 "PrintCLike.cpp.template"
                                                                print(tokenTableName());
                                                            #line 2847 "PrintCLike.cpp"
  append(L"[e.GetOffending()]\n");
  append(L"  }\n");
  append(L"}\n");
                                                            #line 1964 "PrintCLike.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 2854 "PrintCLike.cpp"
  append(L"\n");
  append(L"func GetTerminalName(id int) string {\n");
  append(L"  return TOKEN[id]\n");
  append(L"}\n");
  append(L"\n");
  append(L"func GetNonterminalName(id int) string {");
                                                            #line 1971 "PrintCLike.cpp.template"
                                                                  if (rejectsAmbiguity())
                                                                  {
                                                            #line 2864 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if id < 0 {\n");
  append(L"    return [...]string{\"ALTERNATIVE\", \"AMBIGUOUS\", \"UNAMBIGUOUS\"}[-2 - id]\n");
  append(L"  }");
                                                            #line 1976 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 2871 "PrintCLike.cpp"
  append(L"\n");
  append(L"  return NONTERMINAL[id]\n");
  append(L"}\n");
                                                            #line 1980 "PrintCLike.cpp.template"
                                                                }
                                                              }
                                                              else if (isPython())
                                                              {
                                                            #line 2880 "PrintCLike.cpp"
  append(L"\n");
  append(L"@staticmethod\n");
  append(L"def getOffendingToken(e):\n");
  append(L"  if e.getOffending() < 0:\n");
  append(L"    return \"\"\n");
  append(L"  else:\n");
  append(L"    return ");
                                                            #line 1990 "PrintCLike.cpp.template"
                                                                print(className.c_str());
                                                            #line 2890 "PrintCLike.cpp"
  append(L".TOKEN[e.getOffending()]\n");
                                                            #line 1992 "PrintCLike.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 2895 "PrintCLike.cpp"
  append(L"\n");
  append(L"@staticmethod\n");
  append(L"def getTerminalName(id):\n");
  append(L"  return ");
                                                            #line 1997 "PrintCLike.cpp.template"
                                                                  print(className.c_str());
                                                            #line 2902 "PrintCLike.cpp"
  append(L".TOKEN[id]\n");
  append(L"\n");
  append(L"@staticmethod\n");
  append(L"def getNonterminalName(id):\n");
  append(L"  return ");
                                                            #line 2002 "PrintCLike.cpp.template"
                                                                  printSyntheticNamePrefix();
                                                                  print(className.c_str());
                                                            #line 2911 "PrintCLike.cpp"
  append(L".NONTERMINAL[id]");
                                                            #line 2004 "PrintCLike.cpp.template"
                                                                  printSyntheticNameSuffix();
                                                            #line 2915 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 2006 "PrintCLike.cpp.template"
                                                                }
                                                              }
                                                              else
                                                              {
                                                                openMethod(stringType(), L"static ", L"getOffendingToken", L"ParseException e");
                                                                print(leftBrace());
                                                            #line 2924 "PrintCLike.cpp"
  append(L"\n");
  append(L"  return e.getOffending() < 0 ? ");
                                                            #line 2013 "PrintCLike.cpp.template"
                                                                print(nullPtr());
                                                            #line 2929 "PrintCLike.cpp"
  append(L" : TOKEN[e.getOffending()];");
                                                            #line 2014 "PrintCLike.cpp.template"
                                                                print(rightBrace());
                                                            #line 2933 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 2016 "PrintCLike.cpp.template"
                                                                if (tree)
                                                                {
                                                                  bool sharedNames = isJava() && ! interfaceName.empty();
                                                                  if (sharedNames && ! (grammar->basex && ! hasProlog))
                                                                  {
                                                            #line 2941 "PrintCLike.cpp"
  append(L"\n");
  append(L"private ");
                                                            #line 2022 "PrintCLike.cpp.template"
                                                                    print(className.c_str());
                                                            #line 2946 "PrintCLike.cpp"
  append(L"()\n");
  append(L"{\n");
  append(L"  // used for obtaining the names, when the parser is not instantiated yet\n");
  append(L"}\n");
                                                            #line 2027 "PrintCLike.cpp.template"
                                                                  }
                                                                  openMethod(stringType(), sharedNames ? L"" : L"static ", L"getTerminalName", L"int id");
                                                                  print(leftBrace());
                                                            #line 2955 "PrintCLike.cpp"
  append(L"\n");
  append(L"  return TOKEN[id];");
                                                            #line 2031 "PrintCLike.cpp.template"
                                                                  print(rightBrace());
                                                            #line 2960 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 2033 "PrintCLike.cpp.template"
                                                                  openMethod(stringType(), sharedNames ? L"" : L"static ", L"getNonterminalName", L"int id");
                                                                  print(leftBrace());
                                                            #line 2965 "PrintCLike.cpp"
  append(L"\n");
  append(L"  return ");
                                                            #line 2036 "PrintCLike.cpp.template"
                                                                  printSyntheticNamePrefix();
                                                            #line 2970 "PrintCLike.cpp"
  append(L"NONTERMINAL[id]");
                                                            #line 2037 "PrintCLike.cpp.template"
                                                                  printSyntheticNameSuffix();
                                                            #line 2974 "PrintCLike.cpp"
  append(L";");
                                                            #line 2038 "PrintCLike.cpp.template"
                                                                  print(rightBrace());
                                                            #line 2978 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 2040 "PrintCLike.cpp.template"
                                                                }
                                                              }

                                                              if (isJavascript() || isTypescript() || isHaxe())
                                                              {
                                                                openMethod(L"", L"static ", L"getExpectedTokenSet", L"ParseException e");
                                                                print(leftBrace());
                                                            #line 2988 "PrintCLike.cpp"
  append(L"\n");
  append(L"  var expected");
                                                            #line 2048 "PrintCLike.cpp.template"
                                                                if (isTypescript())
                                                                {
                                                            #line 2994 "PrintCLike.cpp"
  append(L": string[]");
                                                            #line 2050 "PrintCLike.cpp.template"
                                                                }
                                                            #line 2998 "PrintCLike.cpp"
  append(L";\n");
  append(L"  if (e.getExpected() < 0)\n");
  append(L"  {\n");
  append(L"    expected = ");
                                                            #line 2054 "PrintCLike.cpp.template"
                                                                print(staticPrefix());
                                                            #line 3005 "PrintCLike.cpp"
  append(L"getTokenSet(- e.getState());\n");
  append(L"  }\n");
  append(L"  else\n");
  append(L"  {\n");
  append(L"    expected = [");
                                                            #line 2059 "PrintCLike.cpp.template"
                                                                print(staticPrefix());
                                                                print(tokenTableName());
                                                            #line 3014 "PrintCLike.cpp"
  append(L"[e.getExpected()]];\n");
  append(L"  }\n");
  append(L"  return expected;\n");
  append(L"}");
                                                            #line 2064 "PrintCLike.cpp.template"
                                                                if (! isTypescript())
                                                                {
                                                            #line 3022 "PrintCLike.cpp"
  append(L";");
                                                            #line 2066 "PrintCLike.cpp.template"
                                                                }
                                                            #line 3026 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 2068 "PrintCLike.cpp.template"
                                                                if (isHaxe())
                                                                {
                                                            #line 3031 "PrintCLike.cpp"
  append(L"\n");
  append(L"public function getErrorMessage(e: ParseException): String");
                                                            #line 2071 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                                  openMethod(stringType(), L"static ", L"getErrorMessage", L"ParseException e");
                                                                }
                                                                print(leftBrace());
                                                            #line 3041 "PrintCLike.cpp"
  append(L"\n");
  append(L"  var message = e.getMessage();");
                                                            #line 2078 "PrintCLike.cpp.template"
                                                                if (useGlr)
                                                                {
                                                                  increaseIndent();
                                                            #line 3048 "PrintCLike.cpp"
  append(L"\n");
  append(L"if ");
                                                            #line 2082 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                            #line 3053 "PrintCLike.cpp"
  append(L"e.isAmbiguousInput()");
                                                            #line 2083 "PrintCLike.cpp.template"
                                                                  print(ifRightParen());
                                                                  print(leftBrace());
                                                            #line 3058 "PrintCLike.cpp"
  append(L"\n");
  append(L"  message += \"\\n\"");
                                                            #line 2086 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                            #line 3063 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 2088 "PrintCLike.cpp.template"
                                                                  print(elseWithBraces());
                                                                }
                                                            #line 3068 "PrintCLike.cpp"
  append(L"\n");
  append(L"  var found = ");
                                                            #line 2091 "PrintCLike.cpp.template"
                                                                if (! isHaxe())
                                                                {
                                                                  print(L"this.");
                                                                }
                                                            #line 3076 "PrintCLike.cpp"
  append(L"getOffendingToken(e);\n");
  append(L"  var tokenSet = ");
                                                            #line 2096 "PrintCLike.cpp.template"
                                                                if (! isHaxe())
                                                                {
                                                                  print(L"this.");
                                                                }
                                                            #line 3084 "PrintCLike.cpp"
  append(L"getExpectedTokenSet(e);\n");
  append(L"  var size = e.getEnd() - e.getBegin();\n");
  append(L"  message += (found == null ? \"\" : \", found \" + found)\n");
  append(L"          + \"\\nwhile expecting \"\n");
  append(L"          + (tokenSet.length == 1 ? tokenSet[0] : (\"[\" + tokenSet.join(\", \") + \"]\"))\n");
  append(L"          + \"\\n\"\n");
  append(L"          + (size == 0 || found != null ? \"\" : \"after successfully scanning \" + size + \" characters beginning \");");
                                                            #line 2107 "PrintCLike.cpp.template"
                                                                if (useGlr)
                                                                {
                                                                  decreaseIndent();
                                                            #line 3096 "PrintCLike.cpp"
  append(L"\n");
  append(L"  }");
                                                            #line 2111 "PrintCLike.cpp.template"
                                                                }
                                                            #line 3101 "PrintCLike.cpp"
  append(L"\n");
  append(L"  var prefix = ");
                                                            #line 2113 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 3106 "PrintCLike.cpp"
  append(L"input.");
                                                            #line 2114 "PrintCLike.cpp.template"
                                                                if (isHaxe())
                                                                {
                                                            #line 3111 "PrintCLike.cpp"
  append(L"getS");
                                                            #line 2116 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 3117 "PrintCLike.cpp"
  append(L"subs");
                                                            #line 2119 "PrintCLike.cpp.template"
                                                                }
                                                            #line 3121 "PrintCLike.cpp"
  append(L"tring(0, e.getBegin());\n");
  append(L"  var lines = prefix.split(\"\\n\");\n");
  append(L"  var line = lines.length;\n");
  append(L"  var column = lines[line - 1].length + 1;\n");
  append(L"  return message\n");
  append(L"       + \"at line \" + line + \", column \" + column + \":\\n...\"\n");
  append(L"       + ");
                                                            #line 2126 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                                if (isHaxe())
                                                                {
                                                            #line 3133 "PrintCLike.cpp"
  append(L"input.getString(e.getBegin(), input.length < e.getBegin() + 64 ? input.length - e.getBegin() : 64");
                                                            #line 2130 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 3139 "PrintCLike.cpp"
  append(L"input.substring(e.getBegin(), Math.min(");
                                                            #line 2133 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 3143 "PrintCLike.cpp"
  append(L"input.length, e.getBegin() + 64)");
                                                            #line 2135 "PrintCLike.cpp.template"
                                                                }
                                                            #line 3147 "PrintCLike.cpp"
  append(L")\n");
  append(L"       + \"...\";\n");
  append(L"}");
                                                            #line 2138 "PrintCLike.cpp.template"
                                                                if (! isTypescript())
                                                                {
                                                            #line 3154 "PrintCLike.cpp"
  append(L";");
                                                            #line 2140 "PrintCLike.cpp.template"
                                                                }
                                                            #line 3158 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 2142 "PrintCLike.cpp.template"
                                                              }
                                                              else if (isJava())
                                                              {
                                                                openMethod(L"String[] ", L"static ", L"getExpectedTokenSet", L"ParseException e");
                                                                print(leftBrace());
                                                            #line 3166 "PrintCLike.cpp"
  append(L"\n");
  append(L"  String[] expected");
                                                            #line 2148 "PrintCLike.cpp.template"
                                                                if (useGlr)
                                                                {
                                                            #line 3172 "PrintCLike.cpp"
  append(L" = {}");
                                                            #line 2150 "PrintCLike.cpp.template"
                                                                }
                                                            #line 3176 "PrintCLike.cpp"
  append(L";\n");
  append(L"  if (e.getExpected() >= 0)\n");
  append(L"  {\n");
  append(L"    expected = new String[]{TOKEN[e.getExpected()]};\n");
  append(L"  }\n");
  append(L"  else");
                                                            #line 2156 "PrintCLike.cpp.template"
                                                                if (useGlr)
                                                                {
                                                            #line 3186 "PrintCLike.cpp"
  append(L" if (! e.isAmbiguousInput())");
                                                            #line 2158 "PrintCLike.cpp.template"
                                                                }
                                                            #line 3190 "PrintCLike.cpp"
  append(L"\n");
  append(L"  {\n");
  append(L"    expected = getTokenSet(- e.getState());\n");
  append(L"  }\n");
  append(L"  return expected;\n");
  append(L"}\n");
  append(L"\n");
  append(L"public String getErrorMessage(ParseException e)\n");
  append(L"{\n");
  append(L"  String message = e.getMessage();");
                                                            #line 2168 "PrintCLike.cpp.template"
                                                                if (useGlr)
                                                                {
                                                            #line 3204 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if ");
                                                            #line 2171 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                            #line 3209 "PrintCLike.cpp"
  append(L"e.isAmbiguousInput()");
                                                            #line 2172 "PrintCLike.cpp.template"
                                                                  print(ifRightParen());
                                                                  printIndented(1, leftBrace());
                                                            #line 3214 "PrintCLike.cpp"
  append(L"\n");
  append(L"    message += \"\\n\"");
                                                            #line 2175 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                            #line 3219 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 2177 "PrintCLike.cpp.template"
                                                                  printIndented(1, elseWithBraces());
                                                                  increaseIndent();
                                                                }
                                                            #line 3226 "PrintCLike.cpp"
  append(L"\n");
  append(L"  String[] tokenSet = getExpectedTokenSet(e);\n");
  append(L"  String found = getOffendingToken(e);\n");
  append(L"  int size = e.getEnd() - e.getBegin();\n");
  append(L"  message += (found == null ? \"\" : \", found \" + found)\n");
  append(L"          + \"\\nwhile expecting \"\n");
  append(L"          + (tokenSet.length == 1 ? tokenSet[0] : java.util.Arrays.toString(tokenSet))\n");
  append(L"          + \"\\n\"\n");
  append(L"          + (size == 0 || found != null ? \"\" : \"after successfully scanning \" + size + \" characters beginning \");");
                                                            #line 2189 "PrintCLike.cpp.template"
                                                                if (useGlr)
                                                                {
                                                                  decreaseIndent();
                                                            #line 3240 "PrintCLike.cpp"
  append(L"\n");
  append(L"  }");
                                                            #line 2193 "PrintCLike.cpp.template"
                                                                }
                                                                if (codepoints)
                                                                {
                                                            #line 3247 "PrintCLike.cpp"
  append(L"\n");
  append(L"  String prefix = new String(input, 0, e.getBegin());\n");
  append(L"  int line = prefix.replaceAll(\"[");
  append(L"^");
  append(L"\\n]\", \"\").length() + 1;\n");
  append(L"  int column = prefix.codePointCount(prefix.lastIndexOf('\\n') + 1, prefix.length()) + 1;\n");
  append(L"  return message\n");
  append(L"       + \"at line \" + line + \", column \" + column + \":\\n...\"\n");
  append(L"       + new String(input, e.getBegin(), Math.min(input.length, e.getBegin() + 64) - e.getBegin())\n");
  append(L"       + \"...\";\n");
  append(L"}\n");
                                                            #line 2205 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 3263 "PrintCLike.cpp"
  append(L"\n");
  append(L"  String prefix = input.subSequence(0, e.getBegin()).toString();\n");
  append(L"  int line = prefix.replaceAll(\"[");
  append(L"^");
  append(L"\\n]\", \"\").length() + 1;\n");
  append(L"  int column = prefix.length() - prefix.lastIndexOf('\\n');\n");
  append(L"  return message\n");
  append(L"       + \"at line \" + line + \", column \" + column + \":\\n...\"\n");
  append(L"       + input.subSequence(e.getBegin(), Math.min(input.length(), e.getBegin() + 64))\n");
  append(L"       + \"...\";\n");
  append(L"}\n");
                                                            #line 2217 "PrintCLike.cpp.template"
                                                                }
                                                                if (! interfaceName.empty())
                                                                {
                                                            #line 3279 "PrintCLike.cpp"
  append(L"\n");
  append(L"public void parse()\n");
  append(L"{\n");
  append(L"  parse_");
                                                            #line 2223 "PrintCLike.cpp.template"
                                                                  print(Format::acceptableName<WString>(grammar->startSymbol()->name).c_str());
                                                            #line 3286 "PrintCLike.cpp"
  append(L"();\n");
  append(L"}\n");
                                                            #line 2226 "PrintCLike.cpp.template"
                                                                }
                                                              }
                                                              else if (isCSharp())
                                                              {
                                                                openMethod(L"static String[] ", L"", L"getExpectedTokenSet", L"ParseException e");
                                                                print(leftBrace());
                                                            #line 3296 "PrintCLike.cpp"
  append(L"\n");
  append(L"  String[] expected;\n");
  append(L"  if (e.getExpected() < 0)\n");
  append(L"  {\n");
  append(L"    expected = getTokenSet(- e.getState());\n");
  append(L"  }\n");
  append(L"  else\n");
  append(L"  {\n");
  append(L"    expected = new String[]{TOKEN[e.getExpected()]};\n");
  append(L"  }\n");
  append(L"  return expected;\n");
  append(L"}\n");
  append(L"\n");
  append(L"public String getErrorMessage(ParseException e)\n");
  append(L"{\n");
  append(L"  String message = e.getMessage();");
                                                            #line 2247 "PrintCLike.cpp.template"
                                                                if (useGlr)
                                                                {
                                                            #line 3316 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if (e.isAmbiguousInput())\n");
  append(L"  {\n");
  append(L"    message += \"\\n\";\n");
  append(L"  }\n");
  append(L"  else\n");
  append(L"  {");
                                                            #line 2255 "PrintCLike.cpp.template"
                                                                  increaseIndent();
                                                                }
                                                            #line 3327 "PrintCLike.cpp"
  append(L"\n");
  append(L"  String[] tokenSet = getExpectedTokenSet(e);\n");
  append(L"  String found = getOffendingToken(e);\n");
  append(L"  int size = e.getEnd() - e.getBegin();\n");
  append(L"  message += (found == null ? \"\" : \", found \" + found)\n");
  append(L"          + \"\\nwhile expecting \"\n");
  append(L"          + (tokenSet.Length == 1 ? tokenSet[0] : (\"[\" + String.Join(\", \", tokenSet) + \"]\"))\n");
  append(L"          + \"\\n\"\n");
  append(L"          + (size == 0 || found != null ? \"\" : \"after successfully scanning \" + size + \" characters beginning \");");
                                                            #line 2266 "PrintCLike.cpp.template"
                                                                if (useGlr)
                                                                {
                                                                  decreaseIndent();
                                                            #line 3341 "PrintCLike.cpp"
  append(L"\n");
  append(L"  }");
                                                            #line 2270 "PrintCLike.cpp.template"
                                                                }
                                                            #line 3346 "PrintCLike.cpp"
  append(L"\n");
  append(L"  String prefix = input.Substring(0, e.getBegin());\n");
  append(L"  int line = prefix.Length - prefix.Replace(\"\\n\", \"\").Length + 1;\n");
  append(L"  int column = prefix.Length - prefix.LastIndexOf('\\n');\n");
  append(L"  return message\n");
  append(L"       + \"at line \" + line + \", column \" + column + \":\\n...\"\n");
  append(L"       + input.Substring(e.getBegin(), Math.Min(input.Length, e.getBegin() + 64) - e.getBegin())\n");
  append(L"       + \"...\";\n");
  append(L"}\n");
                                                            #line 2280 "PrintCLike.cpp.template"
                                                                if (! interfaceName.empty())
                                                                {
                                                            #line 3359 "PrintCLike.cpp"
  append(L"\n");
  append(L"public void parse()\n");
  append(L"{\n");
  append(L"  parse_");
                                                            #line 2285 "PrintCLike.cpp.template"
                                                                  print(Format::acceptableName<WString>(grammar->startSymbol()->name).c_str());
                                                            #line 3366 "PrintCLike.cpp"
  append(L"();\n");
  append(L"}\n");
                                                            #line 2288 "PrintCLike.cpp.template"
                                                                }
                                                              }
                                                              else if (isGo())
                                                              {
                                                            #line 3374 "PrintCLike.cpp"
  append(L"\n");
  append(L"func GetExpectedTokenSet(e ParseError) []string {\n");
  append(L"  if e.expected < 0 {\n");
  append(L"    return getTokenSet(- e.state)\n");
  append(L"  } else {\n");
  append(L"    singleton := [...]string {");
                                                            #line 2297 "PrintCLike.cpp.template"
                                                                print(tokenTableName());
                                                            #line 3383 "PrintCLike.cpp"
  append(L"[e.expected]}\n");
  append(L"    return singleton[:]\n");
  append(L"  }\n");
  append(L"}\n");
  append(L"\n");
  append(L"func (this *");
                                                            #line 2303 "PrintCLike.cpp.template"
                                                                print(className.c_str());
                                                            #line 3392 "PrintCLike.cpp"
  append(L") GetErrorMessage(e ParseError) string {\n");
  append(L"  message := e.Error()");
                                                            #line 2305 "PrintCLike.cpp.template"
                                                                if (useGlr)
                                                                {
                                                            #line 3398 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if e.IsAmbiguousInput() {\n");
  append(L"    message += \"\\n\"\n");
  append(L"  } else {");
                                                            #line 2310 "PrintCLike.cpp.template"
                                                                  increaseIndent();
                                                                }
                                                            #line 3406 "PrintCLike.cpp"
  append(L"\n");
  append(L"  found := GetOffendingToken(e)\n");
  append(L"  if found != \"\" {\n");
  append(L"    message += \", found \"\n");
  append(L"    message += found\n");
  append(L"  }\n");
  append(L"  expected := GetExpectedTokenSet(e)\n");
  append(L"  message += \"\\nwhile expecting \"\n");
  append(L"  delimiter := \"\"\n");
  append(L"  if len(expected) != 1 {\n");
  append(L"    delimiter = \"[\"\n");
  append(L"  }\n");
  append(L"  for _, token := range expected {\n");
  append(L"    message += delimiter\n");
  append(L"    message += token\n");
  append(L"    delimiter = \", \"\n");
  append(L"  }\n");
  append(L"  if len(expected) != 1 {\n");
  append(L"    message += \"]\"\n");
  append(L"  }\n");
  append(L"  message += \"\\n\"\n");
  append(L"  size := e.GetEnd() - e.GetBegin()\n");
  append(L"  if size != 0 && found == \"\" {\n");
  append(L"    message += \"after successfully scanning \"\n");
  append(L"    message += strconv.Itoa(size)\n");
  append(L"    message += \" characters beginning \"\n");
  append(L"  }");
                                                            #line 2338 "PrintCLike.cpp.template"
                                                                if (useGlr)
                                                                {
                                                                  decreaseIndent();
                                                            #line 3438 "PrintCLike.cpp"
  append(L"\n");
  append(L"  }");
                                                            #line 2342 "PrintCLike.cpp.template"
                                                                }
                                                            #line 3443 "PrintCLike.cpp"
  append(L"\n");
  append(L"  line := 1\n");
  append(L"  column := 1\n");
  append(L"  for i := 0; i < e.GetBegin(); i++ {\n");
  append(L"    if this.input[i] == '\\n' {\n");
  append(L"      line++\n");
  append(L"      column = 1\n");
  append(L"    } else {\n");
  append(L"      column++\n");
  append(L"    }\n");
  append(L"  }\n");
  append(L"  message += \"at line \"\n");
  append(L"  message += strconv.Itoa(line)\n");
  append(L"  message += \", column \"\n");
  append(L"  message += strconv.Itoa(column)\n");
  append(L"  message += \":\\n...\"\n");
  append(L"  end := e.GetBegin() + 64\n");
  append(L"  if end > len(this.input) {\n");
  append(L"    end = len(this.input)\n");
  append(L"  }\n");
  append(L"  message += this.input[e.GetBegin() : end]\n");
  append(L"  message += \"...\"\n");
  append(L"  return message\n");
  append(L"}\n");
                                                            #line 2367 "PrintCLike.cpp.template"
                                                                if (! interfaceName.empty())
                                                                {
                                                            #line 3471 "PrintCLike.cpp"
  append(L"\n");
  append(L"public void parse()\n");
  append(L"{\n");
  append(L"  parse_");
                                                            #line 2372 "PrintCLike.cpp.template"
                                                                  print(Format::acceptableName<WString>(grammar->startSymbol()->name).c_str());
                                                            #line 3478 "PrintCLike.cpp"
  append(L"();\n");
  append(L"}\n");
                                                            #line 2375 "PrintCLike.cpp.template"
                                                                }
                                                              }
                                                              else if (isPython())
                                                              {
                                                            #line 3486 "PrintCLike.cpp"
  append(L"\n");
  append(L"@staticmethod\n");
  append(L"def getExpectedTokenSet(e):\n");
  append(L"  if e.expected < 0:\n");
  append(L"    return ");
                                                            #line 2383 "PrintCLike.cpp.template"
                                                                print(className.c_str());
                                                            #line 3494 "PrintCLike.cpp"
  append(L".getTokenSet(- e.state)\n");
  append(L"  else:\n");
  append(L"    return [");
                                                            #line 2386 "PrintCLike.cpp.template"
                                                                print(className.c_str());
                                                            #line 3500 "PrintCLike.cpp"
  append(L".TOKEN[e.expected]]\n");
  append(L"\n");
  append(L"def getErrorMessage(self, e):\n");
  append(L"  message = e.error()");
                                                            #line 2390 "PrintCLike.cpp.template"
                                                                if (useGlr)
                                                                {
                                                            #line 3508 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if e.isAmbiguousInput():\n");
  append(L"    message += \"\\n\"\n");
  append(L"  else:");
                                                            #line 2395 "PrintCLike.cpp.template"
                                                                  increaseIndent();
                                                                }
                                                            #line 3516 "PrintCLike.cpp"
  append(L"\n");
  append(L"  found = ");
                                                            #line 2398 "PrintCLike.cpp.template"
                                                                print(className.c_str());
                                                            #line 3521 "PrintCLike.cpp"
  append(L".getOffendingToken(e)\n");
  append(L"  if found != \"\":\n");
  append(L"    message += \", found \"\n");
  append(L"    message += found\n");
  append(L"  expected = ");
                                                            #line 2403 "PrintCLike.cpp.template"
                                                                print(className.c_str());
                                                            #line 3529 "PrintCLike.cpp"
  append(L".getExpectedTokenSet(e)\n");
  append(L"  message += \"\\nwhile expecting \"\n");
  append(L"  delimiter = \"\"\n");
  append(L"  if len(expected) != 1:\n");
  append(L"    delimiter = \"[\"\n");
  append(L"  for token in expected:\n");
  append(L"    message += delimiter\n");
  append(L"    message += token\n");
  append(L"    delimiter = \", \"\n");
  append(L"  if len(expected) != 1:\n");
  append(L"    message += \"]\"\n");
  append(L"  message += \"\\n\"\n");
  append(L"  size = e.getEnd() - e.getBegin()\n");
  append(L"  if size != 0 and found == \"\":\n");
  append(L"    message += \"after successfully scanning \"\n");
  append(L"    message += str(size)\n");
  append(L"    message += \" characters beginning \" ");
                                                            #line 2420 "PrintCLike.cpp.template"
                                                                if (useGlr)
                                                                {
                                                                  decreaseIndent();
                                                                }
                                                            #line 3552 "PrintCLike.cpp"
  append(L"\n");
  append(L"  line = 1\n");
  append(L"  column = 1\n");
  append(L"  for i in range(e.getBegin()):\n");
  append(L"    if self.input[i] == '\\n':\n");
  append(L"      line += 1\n");
  append(L"      column = 1\n");
  append(L"    else:\n");
  append(L"      column += 1\n");
  append(L"  message += \"at line \"\n");
  append(L"  message += str(line)\n");
  append(L"  message += \", column \"\n");
  append(L"  message += str(column)\n");
  append(L"  message += \":\\n...\"\n");
  append(L"  end = e.getBegin() + 64\n");
  append(L"  if end > len(self.input):\n");
  append(L"    end = len(self.input)\n");
  append(L"  message += self.input[e.getBegin() : end]\n");
  append(L"  message += \"...\"\n");
  append(L"  return message\n");
                                                            #line 2444 "PrintCLike.cpp.template"
                                                                if (! interfaceName.empty())
                                                                {
                                                            #line 3576 "PrintCLike.cpp"
  append(L"\n");
  append(L"public void parse()\n");
  append(L"{\n");
  append(L"  parse_");
                                                            #line 2449 "PrintCLike.cpp.template"
                                                                  print(Format::acceptableName<WString>(grammar->startSymbol()->name).c_str());
                                                            #line 3583 "PrintCLike.cpp"
  append(L"();\n");
  append(L"}\n");
                                                            #line 2452 "PrintCLike.cpp.template"
                                                                }
                                                              }
                                                              else if (isScala())
                                                              {
                                                              }
                                                              else
                                                              {
                                                                WString args(L"const ParseException &e, ");
                                                                args += stringType();
                                                                args += L"*set, int size";
                                                                openMethod(L"static void ", L"", L"getExpectedTokenSet", args.c_str());
                                                                print(leftBrace());
                                                            #line 3599 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if (e.expected < 0)\n");
  append(L"  {\n");
  append(L"    getTokenSet(- e.state, set, size);\n");
  append(L"  }\n");
  append(L"  else if (size == 1)\n");
  append(L"  {\n");
  append(L"    set[0] = 0;\n");
  append(L"  }\n");
  append(L"  else if (size > 1)\n");
  append(L"  {\n");
  append(L"    set[0] = ");
                                                            #line 2475 "PrintCLike.cpp.template"
                                                                print(tokenTableName());
                                                            #line 3614 "PrintCLike.cpp"
  append(L"[e.expected];\n");
  append(L"    set[1] = 0;\n");
  append(L"  }\n");
  append(L"}\n");
  append(L"\n");
  append(L"static std::");
                                                            #line 2481 "PrintCLike.cpp.template"
                                                                if (stringIntroducer()[0]) append(L"w");
                                                            #line 3623 "PrintCLike.cpp"
  append(L"string to_");
                                                            #line 2482 "PrintCLike.cpp.template"
                                                                if (stringIntroducer()[0]) append(L"w");
                                                            #line 3627 "PrintCLike.cpp"
  append(L"string(int i)\n");
  append(L"{\n");
  append(L"  const ");
                                                            #line 2485 "PrintCLike.cpp.template"
                                                                if (stringIntroducer()[0]) append(L"w");
                                                            #line 3633 "PrintCLike.cpp"
  append(L"char");
                                                            #line 2486 "PrintCLike.cpp.template"
                                                                if (stringIntroducer()[0]) append(L"_t");
                                                            #line 3637 "PrintCLike.cpp"
  append(L" *sign = i < 0 ? ");
                                                            #line 2487 "PrintCLike.cpp.template"
                                                                append(stringIntroducer());
                                                            #line 3641 "PrintCLike.cpp"
  append(L"\"-\" : ");
                                                            #line 2488 "PrintCLike.cpp.template"
                                                                append(stringIntroducer());
                                                            #line 3645 "PrintCLike.cpp"
  append(L"\"\";\n");
  append(L"  std::");
                                                            #line 2490 "PrintCLike.cpp.template"
                                                                if (stringIntroducer()[0]) append(L"w");
                                                            #line 3650 "PrintCLike.cpp"
  append(L"string a;\n");
  append(L"  do\n");
  append(L"  {\n");
  append(L"    a += ");
                                                            #line 2494 "PrintCLike.cpp.template"
                                                                append(stringIntroducer());
                                                            #line 3657 "PrintCLike.cpp"
  append(L"'0' + abs(i % 10);\n");
  append(L"    i /= 10;\n");
  append(L"  }\n");
  append(L"  while (i != 0);\n");
  append(L"  a += sign;\n");
  append(L"  std::reverse(a.begin(), a.end());\n");
  append(L"  return a;\n");
  append(L"}\n");
  append(L"\n");
  append(L"std::");
                                                            #line 2504 "PrintCLike.cpp.template"
                                                                if (stringIntroducer()[0]) append(L"w");
                                                            #line 3670 "PrintCLike.cpp"
  append(L"string getErrorMessage(const ParseException &e)\n");
  append(L"{\n");
  append(L"  std::");
                                                            #line 2507 "PrintCLike.cpp.template"
                                                                if (stringIntroducer()[0]) append(L"w");
                                                            #line 3676 "PrintCLike.cpp"
  append(L"string message(e.getMessage());");
                                                            #line 2508 "PrintCLike.cpp.template"
                                                                if (useGlr)
                                                                {
                                                            #line 3681 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if (e.isAmbiguousInput())\n");
  append(L"  {\n");
  append(L"    message += ");
                                                            #line 2513 "PrintCLike.cpp.template"
                                                                  print(stringIntroducer());
                                                            #line 3688 "PrintCLike.cpp"
  append(L"\"\\n\";\n");
  append(L"  }\n");
  append(L"  else\n");
  append(L"  {");
                                                            #line 2517 "PrintCLike.cpp.template"
                                                                  increaseIndent();
                                                                }
                                                            #line 3696 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 2520 "PrintCLike.cpp.template"
                                                                print(stringType());
                                                            #line 3701 "PrintCLike.cpp"
  append(L"found = getOffendingToken(e);\n");
  append(L"  if (found != 0)\n");
  append(L"  {\n");
  append(L"    message += ");
                                                            #line 2524 "PrintCLike.cpp.template"
                                                                print(stringIntroducer());
                                                            #line 3708 "PrintCLike.cpp"
  append(L"\", found \";\n");
  append(L"    message += found;\n");
  append(L"  }\n");
  append(L"  ");
                                                            #line 2528 "PrintCLike.cpp.template"
                                                                print(stringType());
                                                            #line 3715 "PrintCLike.cpp"
  append(L"expected[64];\n");
  append(L"  getExpectedTokenSet(e, expected, sizeof expected / sizeof *expected);\n");
  append(L"  message += ");
                                                            #line 2531 "PrintCLike.cpp.template"
                                                                print(stringIntroducer());
                                                            #line 3721 "PrintCLike.cpp"
  append(L"\"\\nwhile expecting \";\n");
  append(L"  ");
                                                            #line 2533 "PrintCLike.cpp.template"
                                                                print(stringType());
                                                            #line 3726 "PrintCLike.cpp"
  append(L"delimiter(expected[1] ? ");
                                                            #line 2534 "PrintCLike.cpp.template"
                                                                print(stringIntroducer());
                                                            #line 3730 "PrintCLike.cpp"
  append(L"\"[\" : ");
                                                            #line 2535 "PrintCLike.cpp.template"
                                                                print(stringIntroducer());
                                                            #line 3734 "PrintCLike.cpp"
  append(L"\"\");\n");
  append(L"  for (");
                                                            #line 2537 "PrintCLike.cpp.template"
                                                                print(stringType());
                                                            #line 3739 "PrintCLike.cpp"
  append(L"*x = expected; *x; ++x)\n");
  append(L"  {\n");
  append(L"    message += delimiter;\n");
  append(L"    message += *x;\n");
  append(L"    delimiter = ");
                                                            #line 2542 "PrintCLike.cpp.template"
                                                                print(stringIntroducer());
                                                            #line 3747 "PrintCLike.cpp"
  append(L"\", \";\n");
  append(L"  }\n");
  append(L"  message += expected[1] ? ");
                                                            #line 2545 "PrintCLike.cpp.template"
                                                                print(stringIntroducer());
                                                            #line 3753 "PrintCLike.cpp"
  append(L"\"]\\n\" : ");
                                                            #line 2546 "PrintCLike.cpp.template"
                                                                print(stringIntroducer());
                                                            #line 3757 "PrintCLike.cpp"
  append(L"\"\\n\";\n");
  append(L"  int size = e.getEnd() - e.getBegin();\n");
  append(L"  if (size != 0 && found == 0)\n");
  append(L"  {\n");
  append(L"    message += ");
                                                            #line 2551 "PrintCLike.cpp.template"
                                                                print(stringIntroducer());
                                                            #line 3765 "PrintCLike.cpp"
  append(L"\"after successfully scanning \";\n");
  append(L"    message += to_");
                                                            #line 2553 "PrintCLike.cpp.template"
                                                                if (stringIntroducer()[0]) append(L"w");
                                                            #line 3770 "PrintCLike.cpp"
  append(L"string(size);\n");
  append(L"    message += ");
                                                            #line 2555 "PrintCLike.cpp.template"
                                                                print(stringIntroducer());
                                                            #line 3775 "PrintCLike.cpp"
  append(L"\" characters beginning \";\n");
  append(L"  }");
                                                            #line 2557 "PrintCLike.cpp.template"
                                                                if (useGlr)
                                                                {
                                                                  decreaseIndent();
                                                            #line 3782 "PrintCLike.cpp"
  append(L"\n");
  append(L"  }");
                                                            #line 2561 "PrintCLike.cpp.template"
                                                                }
                                                            #line 3787 "PrintCLike.cpp"
  append(L"\n");
  append(L"  int line = 1;\n");
  append(L"  int column = 1;\n");
  append(L"  for (int i = 0; i < e.getBegin(); ++i)\n");
  append(L"  {\n");
  append(L"    if (input[i] == L'\\n')\n");
  append(L"    {\n");
  append(L"      ++line;\n");
  append(L"      column = 1;\n");
  append(L"    }\n");
  append(L"    else\n");
  append(L"    {\n");
  append(L"      ++column;\n");
  append(L"    }\n");
  append(L"  }\n");
  append(L"  message += ");
                                                            #line 2577 "PrintCLike.cpp.template"
                                                                print(stringIntroducer());
                                                            #line 3806 "PrintCLike.cpp"
  append(L"\"at line \";\n");
  append(L"  message += to_");
                                                            #line 2579 "PrintCLike.cpp.template"
                                                                if (stringIntroducer()[0]) append(L"w");
                                                            #line 3811 "PrintCLike.cpp"
  append(L"string(line);\n");
  append(L"  message += ");
                                                            #line 2581 "PrintCLike.cpp.template"
                                                                print(stringIntroducer());
                                                            #line 3816 "PrintCLike.cpp"
  append(L"\", column \";\n");
  append(L"  message += to_");
                                                            #line 2583 "PrintCLike.cpp.template"
                                                                if (stringIntroducer()[0]) append(L"w");
                                                            #line 3821 "PrintCLike.cpp"
  append(L"string(column);\n");
  append(L"  message += ");
                                                            #line 2585 "PrintCLike.cpp.template"
                                                                print(stringIntroducer());
                                                            #line 3826 "PrintCLike.cpp"
  append(L"\":\\n...\";\n");
  append(L"  ");
                                                            #line 2587 "PrintCLike.cpp.template"
                                                                print(stringType());
                                                            #line 3831 "PrintCLike.cpp"
  append(L"w = input + e.getBegin();\n");
  append(L"  for (int i = 0; i < 64 && *w; ++i)\n");
  append(L"  {\n");
  append(L"    message += *w++;\n");
  append(L"  }\n");
  append(L"  message += ");
                                                            #line 2593 "PrintCLike.cpp.template"
                                                                print(stringIntroducer());
                                                            #line 3840 "PrintCLike.cpp"
  append(L"\"...\";\n");
  append(L"  return message;\n");
  append(L"}\n");
                                                            #line 2597 "PrintCLike.cpp.template"
                                                              }
                                                              if (! isGo())
                                                                decreaseIndent();
                                                            }

                                                            void PrintCLike::printEpilog()
                                                            {
                                                              Trace("PrintCLike::printEpilog");

                                                              if (trace && ! isLrParser)
                                                              {
                                                                increaseIndent();
                                                                WString type(stringType());
                                                                if (type.size() == 0) type = L"String ";
                                                                WString args(type);
                                                                args += L"method, ";
                                                                args += type;
                                                                args += L"occasion, ";
                                                                args += type;
                                                                args += L"name";
                                                                openMethod(voidType(), L"", L"traceNonterminal", args.c_str());
                                                                print(leftBrace());
                                                                if (isCpp())
                                                                {
                                                            #line 3869 "PrintCLike.cpp"
  append(L"\n");
  append(L"  fprintf(stderr, \"  <%s %snonterminal=\\\"%s\\\"\", ");
                                                            #line 2622 "PrintCLike.cpp.template"
                                                                  if (stringIntroducer()[0])
                                                                  {
                                                            #line 3875 "PrintCLike.cpp"
  append(L"Utf8Encoder::encode(");
                                                            #line 2624 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 3879 "PrintCLike.cpp"
  append(L"method");
                                                            #line 2625 "PrintCLike.cpp.template"
                                                                  if (stringIntroducer()[0])
                                                                  {
                                                            #line 3884 "PrintCLike.cpp"
  append(L").c_str()");
                                                            #line 2627 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 3888 "PrintCLike.cpp"
  append(L", ");
                                                            #line 2628 "PrintCLike.cpp.template"
                                                                  if (stringIntroducer()[0])
                                                                  {
                                                            #line 3893 "PrintCLike.cpp"
  append(L"Utf8Encoder::encode(");
                                                            #line 2630 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 3897 "PrintCLike.cpp"
  append(L"occasion");
                                                            #line 2631 "PrintCLike.cpp.template"
                                                                  if (stringIntroducer()[0])
                                                                  {
                                                            #line 3902 "PrintCLike.cpp"
  append(L").c_str()");
                                                            #line 2633 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 3906 "PrintCLike.cpp"
  append(L", ");
                                                            #line 2634 "PrintCLike.cpp.template"
                                                                  if (stringIntroducer()[0])
                                                                  {
                                                            #line 3911 "PrintCLike.cpp"
  append(L"Utf8Encoder::encode(");
                                                            #line 2636 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 3915 "PrintCLike.cpp"
  append(L"name");
                                                            #line 2637 "PrintCLike.cpp.template"
                                                                  if (stringIntroducer()[0])
                                                                  {
                                                            #line 3920 "PrintCLike.cpp"
  append(L").c_str()");
                                                            #line 2639 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 3924 "PrintCLike.cpp"
  append(L");\n");
  append(L"  if (l1 != 0)\n");
  append(L"    fprintf(stderr, \" input=\\\"%s\\\"\", ");
                                                            #line 2642 "PrintCLike.cpp.template"
                                                                  if (stringIntroducer()[0])
                                                                  {
                                                            #line 3931 "PrintCLike.cpp"
  append(L"Utf8Encoder::encode(");
                                                            #line 2644 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 3935 "PrintCLike.cpp"
  append(L"xmlEscape(lookaheadString().c_str(), 0).c_str()");
                                                            #line 2646 "PrintCLike.cpp.template"
                                                                  if (stringIntroducer()[0])
                                                                  {
                                                            #line 3940 "PrintCLike.cpp"
  append(L").c_str()");
                                                            #line 2648 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 3944 "PrintCLike.cpp"
  append(L");\n");
  append(L"  fprintf(stderr, \"/>\\n\");");
                                                            #line 2650 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                                  if (isHaxe())
                                                                  {
                                                            #line 3953 "PrintCLike.cpp"
  append(L"\n");
  append(L"  trace(");
                                                            #line 2656 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                                    if (isGo())
                                                                    {
                                                            #line 3962 "PrintCLike.cpp"
  append(L"\n");
  append(L"  var inputAttr string\n");
  append(L"  if (this.l1 == 0) {\n");
  append(L"    inputAttr = \"\"\n");
  append(L"  } else {\n");
  append(L"    inputAttr = \" input=\\\"\" + xmlEscape(this.lookaheadString()) + \"\\\"\"\n");
  append(L"  }");
                                                            #line 2667 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 3972 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 2669 "PrintCLike.cpp.template"
                                                                    print(writeTrace());
                                                                  }
                                                            #line 3978 "PrintCLike.cpp"
  append(L"\"  <\" + method + \" \" + occasion + \"nonterminal=\\\"\" + name + \"\\\"\" + ");
                                                            #line 2672 "PrintCLike.cpp.template"
                                                                  if (isGo())
                                                                  {
                                                            #line 3983 "PrintCLike.cpp"
  append(L"inputAttr");
                                                            #line 2674 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 3989 "PrintCLike.cpp"
  append(L"(");
                                                            #line 2677 "PrintCLike.cpp.template"
                                                                    if (isScala())
                                                                    {
                                                            #line 3994 "PrintCLike.cpp"
  append(L"if (l1 == 0) \"\" else");
                                                            #line 2679 "PrintCLike.cpp.template"
                                                                    }
                                                                    else if (isPython())
                                                                    {
                                                            #line 4000 "PrintCLike.cpp"
  append(L"\"\" if self.l1 == 0 else");
                                                            #line 2682 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                                      print(thiz());
                                                            #line 4007 "PrintCLike.cpp"
  append(L"l1 == 0 ? \"\" :");
                                                            #line 2686 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 4011 "PrintCLike.cpp"
  append(L" \" input=\\\"\" + ");
                                                            #line 2687 "PrintCLike.cpp.template"
                                                                    print(staticPrefix());
                                                            #line 4015 "PrintCLike.cpp"
  append(L"xmlEscape(");
                                                            #line 2688 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 4019 "PrintCLike.cpp"
  append(L"lookaheadString");
                                                            #line 2689 "PrintCLike.cpp.template"
                                                                    if (! isScala()) print(L"()");
                                                            #line 4023 "PrintCLike.cpp"
  append(L") + \"\\\"\")");
                                                            #line 2690 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 4027 "PrintCLike.cpp"
  append(L" + \"/>");
                                                            #line 2691 "PrintCLike.cpp.template"
                                                                  if (isHaxe()) print(L"\")"); else print(L"\\n\"");
                                                                  print(endWriteTrace());
                                                                  print(semicolon());
                                                                }
                                                                print(rightBrace());
                                                            #line 4035 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 2697 "PrintCLike.cpp.template"
                                                                decreaseIndent();
                                                              }

                                                              if (grammar->automaticSemicolonInsertion)
                                                              {
                                                                if (! isGo())
                                                                  increaseIndent();
                                                                openMethod(boolType(), L"", L"followsLineTerminator", L"");
                                                                print(leftBrace());
                                                                increaseIndent();
                                                            #line 4048 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 2708 "PrintCLike.cpp.template"
                                                                print(intVar());
                                                            #line 4052 "PrintCLike.cpp"
  append(L"i");
                                                            #line 2709 "PrintCLike.cpp.template"
                                                                print(assign());
                                                                print(thiz());
                                                            #line 4057 "PrintCLike.cpp"
  append(L"e0");
                                                            #line 2711 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 4061 "PrintCLike.cpp"
  append(L"\n");
  append(L"if ");
                                                            #line 2713 "PrintCLike.cpp.template"
                                                                print(ifLeftParen());
                                                                print(thiz());
                                                            #line 4067 "PrintCLike.cpp"
  append(L"e0 == ");
                                                            #line 2715 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 4071 "PrintCLike.cpp"
  append(L"b1");
                                                            #line 2716 "PrintCLike.cpp.template"
                                                                print(ifRightParen());
                                                                print(leftBrace());
                                                            #line 4076 "PrintCLike.cpp"
  append(L"\n");
  append(L"  i = ");
                                                            #line 2719 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 4081 "PrintCLike.cpp"
  append(L"b0");
                                                            #line 2720 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                print(rightBrace());
                                                                if (isScala() || isHaxe() || isPython())
                                                                {
                                                            #line 4088 "PrintCLike.cpp"
  append(L"\n");
  append(L"while ");
                                                            #line 2725 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 4095 "PrintCLike.cpp"
  append(L"\n");
  append(L"for ");
                                                            #line 2729 "PrintCLike.cpp.template"
                                                                }
                                                                print(ifLeftParen());
                                                                if (! (isScala() || isHaxe() || isPython()))
                                                                {
                                                            #line 4103 "PrintCLike.cpp"
  append(L"; ");
                                                            #line 2733 "PrintCLike.cpp.template"
                                                                }
                                                            #line 4107 "PrintCLike.cpp"
  append(L"i < ");
                                                            #line 2734 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 4111 "PrintCLike.cpp"
  append(L"b1");
                                                            #line 2735 "PrintCLike.cpp.template"
                                                                if (! (isScala() || isHaxe() || isPython()))
                                                                {
                                                            #line 4116 "PrintCLike.cpp"
  append(L"; i++");
                                                            #line 2737 "PrintCLike.cpp.template"
                                                                }
                                                                print(ifRightParen());
                                                                print(leftBrace());
                                                                increaseIndent();
                                                                if (isGo())
                                                                {
                                                            #line 4125 "PrintCLike.cpp"
  append(L"\n");
  append(L"c, _ := utf8.DecodeRuneInString(this.input[i:])");
                                                            #line 2744 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 4132 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 2748 "PrintCLike.cpp.template"
                                                                  print(intVar());
                                                            #line 4136 "PrintCLike.cpp"
  append(L"c");
                                                            #line 2749 "PrintCLike.cpp.template"
                                                                  print(assign());
                                                                  if (isCpp() || isCSharp() || isPython() || (isJava() && codepoints))
                                                                  {
                                                                    if (isPython())
                                                                    {
                                                            #line 4144 "PrintCLike.cpp"
  append(L"ord(");
                                                            #line 2754 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(thiz());
                                                            #line 4149 "PrintCLike.cpp"
  append(L"input[i]");
                                                            #line 2756 "PrintCLike.cpp.template"
                                                                    if (isPython())
                                                                    {
                                                            #line 4154 "PrintCLike.cpp"
  append(L")");
                                                            #line 2758 "PrintCLike.cpp.template"
                                                                    }
                                                                  }
                                                                  else if (isHaxe())
                                                                  {
                                                            #line 4161 "PrintCLike.cpp"
  append(L"input.get(i)");
                                                            #line 2762 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                                    print(thiz());
                                                            #line 4168 "PrintCLike.cpp"
  append(L"input.char");
                                                            #line 2766 "PrintCLike.cpp.template"
                                                                    if (isTypescript() || isJavascript())
                                                                    {
                                                            #line 4173 "PrintCLike.cpp"
  append(L"Code");
                                                            #line 2768 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 4177 "PrintCLike.cpp"
  append(L"At(i)");
                                                            #line 2769 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(semicolon());
                                                                }
                                                            #line 4183 "PrintCLike.cpp"
  append(L"\n");
  append(L"if ");
                                                            #line 2773 "PrintCLike.cpp.template"
                                                                print(ifLeftParen());
                                                            #line 4188 "PrintCLike.cpp"
  append(L"c == 0xA ");
                                                            #line 2774 "PrintCLike.cpp.template"
                                                                if (isPython())
                                                                {
                                                            #line 4193 "PrintCLike.cpp"
  append(L"or");
                                                            #line 2776 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 4199 "PrintCLike.cpp"
  append(L"||");
                                                            #line 2779 "PrintCLike.cpp.template"
                                                                }
                                                            #line 4203 "PrintCLike.cpp"
  append(L" c == 0xD ");
                                                            #line 2780 "PrintCLike.cpp.template"
                                                                if (isPython())
                                                                {
                                                            #line 4208 "PrintCLike.cpp"
  append(L"or");
                                                            #line 2782 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 4214 "PrintCLike.cpp"
  append(L"||");
                                                            #line 2785 "PrintCLike.cpp.template"
                                                                }
                                                            #line 4218 "PrintCLike.cpp"
  append(L" c == 0x2028 ");
                                                            #line 2786 "PrintCLike.cpp.template"
                                                                if (isPython())
                                                                {
                                                            #line 4223 "PrintCLike.cpp"
  append(L"or");
                                                            #line 2788 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 4229 "PrintCLike.cpp"
  append(L"||");
                                                            #line 2791 "PrintCLike.cpp.template"
                                                                }
                                                            #line 4233 "PrintCLike.cpp"
  append(L" c == 0x2029");
                                                            #line 2792 "PrintCLike.cpp.template"
                                                                print(ifRightParen());
                                                                print(leftBrace());
                                                            #line 4238 "PrintCLike.cpp"
  append(L"\n");
  append(L"  return ");
                                                            #line 2795 "PrintCLike.cpp.template"
                                                                if (isPython())
                                                                {
                                                            #line 4244 "PrintCLike.cpp"
  append(L"T");
                                                            #line 2797 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 4250 "PrintCLike.cpp"
  append(L"t");
                                                            #line 2800 "PrintCLike.cpp.template"
                                                                }
                                                            #line 4254 "PrintCLike.cpp"
  append(L"rue");
                                                            #line 2801 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                print(rightBrace());
                                                                if (isScala() || isPython())
                                                                {
                                                            #line 4261 "PrintCLike.cpp"
  append(L"\n");
  append(L"i += 1");
                                                            #line 2806 "PrintCLike.cpp.template"
                                                                }
                                                                else if (isHaxe())
                                                                {
                                                            #line 4268 "PrintCLike.cpp"
  append(L"\n");
  append(L"++i;");
                                                            #line 2810 "PrintCLike.cpp.template"
                                                                }

                                                                decreaseIndent();
                                                                print(rightBrace());
                                                            #line 4276 "PrintCLike.cpp"
  append(L"\n");
  append(L"return ");
                                                            #line 2815 "PrintCLike.cpp.template"
                                                                if (isPython())
                                                                {
                                                            #line 4282 "PrintCLike.cpp"
  append(L"F");
                                                            #line 2817 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 4288 "PrintCLike.cpp"
  append(L"f");
                                                            #line 2820 "PrintCLike.cpp.template"
                                                                }
                                                            #line 4292 "PrintCLike.cpp"
  append(L"alse");
                                                            #line 2821 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                decreaseIndent();
                                                                print(rightBrace());
                                                            #line 4298 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 2825 "PrintCLike.cpp.template"
                                                                if (! isGo())
                                                                  decreaseIndent();
                                                              }

                                                              if (isScala())
                                                              {
                                                            #line 4307 "PrintCLike.cpp"
  append(L"\n");
  append(L"  def getErrorMessage(e: ");
                                                            #line 2832 "PrintCLike.cpp.template"
                                                                print(className.c_str());
                                                            #line 4312 "PrintCLike.cpp"
  append(L".ParseException) = {\n");
  append(L"    var message = e.getMessage");
                                                            #line 2834 "PrintCLike.cpp.template"
                                                                if (useGlr)
                                                                {
                                                            #line 4318 "PrintCLike.cpp"
  append(L"\n");
  append(L"    if (e.isAmbiguousInput)\n");
  append(L"      message += \"\\n\"\n");
  append(L"    else {");
                                                            #line 2839 "PrintCLike.cpp.template"
                                                                  increaseIndent();
                                                                }
                                                            #line 4326 "PrintCLike.cpp"
  append(L"\n");
  append(L"    val tokenSet = ");
                                                            #line 2842 "PrintCLike.cpp.template"
                                                                print(className.c_str());
                                                            #line 4331 "PrintCLike.cpp"
  append(L".getExpectedTokenSet(e)\n");
  append(L"    val found = ");
                                                            #line 2844 "PrintCLike.cpp.template"
                                                                print(className.c_str());
                                                            #line 4336 "PrintCLike.cpp"
  append(L".getOffendingToken(e)\n");
  append(L"    val size = e.end - e.begin\n");
  append(L"    message += (if (found == null) \"\" else \", found \" + found) + \"\\nwhile expecting \" +\n");
  append(L"      (if (tokenSet.length == 1) tokenSet(0) else \"[\" + (tokenSet mkString \", \") + \"]\") + \"\\n\" +\n");
  append(L"      (if (size == 0 || found != null) \"\" else \"after successfully scanning \" + size + \" characters beginning \")");
                                                            #line 2850 "PrintCLike.cpp.template"
                                                                if (useGlr)
                                                                {
                                                            #line 4345 "PrintCLike.cpp"
  append(L"\n");
  append(L"    }");
                                                            #line 2853 "PrintCLike.cpp.template"
                                                                  decreaseIndent();
                                                                }
                                                            #line 4351 "PrintCLike.cpp"
  append(L"\n");
  append(L"    val prefix = input.substring(0, e.begin)\n");
  append(L"    val line = prefix.replaceAll(\"[");
  append(L"^");
  append(L"\\n]\", \"\").length + 1\n");
  append(L"    val column = prefix.length - prefix.lastIndexOf('\\n')\n");
  append(L"    message +\n");
  append(L"      \"at line \" + line + \", column \" + column + \":\\n...\" +\n");
  append(L"      input.substring(e.begin, math.min(input.length, e.begin + 64)) + \"...\"\n");
  append(L"  }\n");
                                                            #line 2863 "PrintCLike.cpp.template"
                                                              }

                                                              if (isLrParser)
                                                              {
                                                                if (! isGo())
                                                                  increaseIndent();
                                                                if (useGlr)
                                                                {
                                                                  if (isTypescript())
                                                                  {
                                                                    printGlrParseMethod();
                                                                    increaseIndent();
                                                                  }
                                                                  else if (isHaxe() || isScala())
                                                                  {
                                                                    printGlrParseMethod();
                                                                    decreaseIndent();
                                                                  }
                                                                  else
                                                                  {
                                                                    if (! isJavascript())
                                                                    {
                                                                      openStackNode();
                                                                      printCountMethod();
                                                                      closeStackNode();
                                                                    }
                                                                    openThread();
                                                                    increaseIndent();
                                                                  }
                                                                }
                                                                else
                                                                {
                                                                  WString pushArgs = L"int state, int lookback";
                                                                  pushArgs += tree ? L", int begin" : L"";
                                                                  openMethod(voidType(), L"", L"push", pushArgs.c_str());
                                                                  print(leftBrace());
                                                            #line 4399 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 2900 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 4404 "PrintCLike.cpp"
  append(L"top += ");
                                                            #line 2901 "PrintCLike.cpp.template"
                                                                  if (tree)
                                                                  {
                                                            #line 4409 "PrintCLike.cpp"
  append(L"3");
                                                            #line 2903 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 4415 "PrintCLike.cpp"
  append(L"2");
                                                            #line 2906 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(semicolon());
                                                                  if (isJava())
                                                                  {
                                                            #line 4422 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if (top >= iStack.length)\n");
  append(L"  {\n");
  append(L"    iStack = Arrays.copyOf(iStack, iStack.length << 1);\n");
  append(L"  }");
                                                            #line 2914 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isCSharp())
                                                                  {
                                                            #line 4432 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if (top >= iStack.Length)\n");
  append(L"  {\n");
  append(L"    Array.Resize(ref iStack, iStack.Length << 1);\n");
  append(L"  }");
                                                            #line 2921 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isCpp())
                                                                  {
                                                            #line 4442 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if (top >= (int) iStack.size())\n");
  append(L"    iStack.resize(iStack.size() == 0 ? ");
                                                            #line 2926 "PrintCLike.cpp.template"
                                                                    print(tree ? L"192" : L"128");
                                                            #line 4448 "PrintCLike.cpp"
  append(L" : iStack.size() << 1);");
                                                            #line 2927 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isScala())
                                                                  {
                                                            #line 4454 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if (top >= iStack.size) {\n");
  append(L"    val newStack = new Array[Int](iStack.size << 1)\n");
  append(L"    Array.copy(iStack, 0, newStack, 0, iStack.size)\n");
  append(L"    iStack = newStack\n");
  append(L"  }");
                                                            #line 2935 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isGo())
                                                                  {
                                                            #line 4465 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if this.top >= len(this.iStack) {\n");
  append(L"    this.iStack = append(this.iStack, this.iStack...)\n");
  append(L"  }");
                                                            #line 2941 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isPython())
                                                                  {
                                                            #line 4474 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if self.top >= len(self.iStack):\n");
  append(L"    self.iStack.extend([0 for _ in range(len(self.iStack))])");
                                                            #line 2946 "PrintCLike.cpp.template"
                                                                  }
                                                                  if (tree)
                                                                  {
                                                            #line 4482 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 2950 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 4487 "PrintCLike.cpp"
  append(L"iStack");
                                                            #line 2951 "PrintCLike.cpp.template"
                                                                    print(leftbracket());
                                                                    print(thiz());
                                                            #line 4492 "PrintCLike.cpp"
  append(L"top - 2");
                                                            #line 2953 "PrintCLike.cpp.template"
                                                                    print(rightbracket());
                                                            #line 4496 "PrintCLike.cpp"
  append(L" = begin");
                                                            #line 2954 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                  }
                                                            #line 4501 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 2957 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 4506 "PrintCLike.cpp"
  append(L"iStack");
                                                            #line 2958 "PrintCLike.cpp.template"
                                                                  print(leftbracket());
                                                                  print(thiz());
                                                            #line 4511 "PrintCLike.cpp"
  append(L"top - 1");
                                                            #line 2960 "PrintCLike.cpp.template"
                                                                  print(rightbracket());
                                                            #line 4515 "PrintCLike.cpp"
  append(L" = state");
                                                            #line 2961 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                            #line 4519 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 2963 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 4524 "PrintCLike.cpp"
  append(L"iStack");
                                                            #line 2964 "PrintCLike.cpp.template"
                                                                  print(leftbracket());
                                                                  print(thiz());
                                                            #line 4529 "PrintCLike.cpp"
  append(L"top");
                                                            #line 2966 "PrintCLike.cpp.template"
                                                                  print(rightbracket());
                                                            #line 4533 "PrintCLike.cpp"
  append(L" = lookback");
                                                            #line 2967 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                  print(rightBrace());
                                                            #line 4538 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 2970 "PrintCLike.cpp.template"
                                                                  printCountMethod();

                                                                  WString args(L"int target, int initialState");
                                                                  if (tree)
                                                                  {
                                                                    args += L", ";
                                                                    if (! isTypescript()) args += staticPrefix();
                                                                    args += L"BottomUpEventHandler";
                                                                    if (isTypescript()) args += L"|null";
                                                                    args += L" ";
                                                                    if (isCpp()) args += L"*";
                                                                    args += L"eventHandler";
                                                                  }
                                                                  openMethod(voidType(), L"", L"parse", args.c_str());
                                                                  print(leftBrace());
                                                                  increaseIndent();
                                                            #line 4557 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 2987 "PrintCLike.cpp.template"
                                                                  print(intVar());
                                                            #line 4561 "PrintCLike.cpp"
  append(L"state");
                                                            #line 2988 "PrintCLike.cpp.template"
                                                                  print(assign());
                                                            #line 4565 "PrintCLike.cpp"
  append(L"initialState");
                                                            #line 2989 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                  if (tree || useGlr)
                                                                  {
                                                            #line 4571 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 2993 "PrintCLike.cpp.template"
                                                                    print(intVar());
                                                            #line 4575 "PrintCLike.cpp"
  append(L"bw");
                                                            #line 2994 "PrintCLike.cpp.template"
                                                                    print(assign());
                                                                    print(thiz());
                                                            #line 4580 "PrintCLike.cpp"
  append(L"e0");
                                                            #line 2996 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 4584 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 2998 "PrintCLike.cpp.template"
                                                                    print(intVar());
                                                            #line 4588 "PrintCLike.cpp"
  append(L"bs");
                                                            #line 2999 "PrintCLike.cpp.template"
                                                                    print(assign());
                                                                    print(thiz());
                                                            #line 4593 "PrintCLike.cpp"
  append(L"e0");
                                                            #line 3001 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                  }
                                                                  if (tree)
                                                                  {
                                                            #line 4600 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3006 "PrintCLike.cpp.template"
                                                                    print(intVar());
                                                            #line 4604 "PrintCLike.cpp"
  append(L"es");
                                                            #line 3007 "PrintCLike.cpp.template"
                                                                    print(assign());
                                                                    print(thiz());
                                                            #line 4609 "PrintCLike.cpp"
  append(L"e0");
                                                            #line 3009 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 4613 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3011 "PrintCLike.cpp.template"
                                                                    print(intVar());
                                                            #line 4617 "PrintCLike.cpp"
  append(L"t");
                                                            #line 3012 "PrintCLike.cpp.template"
                                                                    print(assign());
                                                                    print(thiz());
                                                            #line 4622 "PrintCLike.cpp"
  append(L"top");
                                                            #line 3014 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                  }
                                                            #line 4627 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3017 "PrintCLike.cpp.template"
                                                                  print(intVar());
                                                            #line 4631 "PrintCLike.cpp"
  append(L"action");
                                                            #line 3018 "PrintCLike.cpp.template"
                                                                  print(assign());
                                                                  print(thiz());
                                                            #line 4636 "PrintCLike.cpp"
  append(L"predict(state)");
                                                            #line 3020 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                              }
                                                              if (! (isHaxe() || isScala() || isTypescript()) || ! useGlr)
                                                              {
                                                                printThreadBody1();
                                                              }
                                                              if (isScala())
                                                              {
                                                                if (trace)
                                                                {
                                                            #line 4650 "PrintCLike.cpp"
  append(L"\n");
  append(L"  def setTraceWriter(w: Writer): Unit = {\n");
  append(L"    err = w\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  def writeTrace(content: String): Unit = {\n");
  append(L"    err.write(content)\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  def flushTrace: Unit = {\n");
  append(L"    err.flush\n");
  append(L"  }\n");
                                                            #line 3044 "PrintCLike.cpp.template"
                                                                }
                                                                if (useGlr)
                                                                {
                                                            #line 4667 "PrintCLike.cpp"
  append(L"\n");
  append(L"  var thread: ");
                                                            #line 3048 "PrintCLike.cpp.template"
                                                                  print(className.c_str());
                                                            #line 4672 "PrintCLike.cpp"
  append(L".ParsingThread = null");
                                                            #line 3049 "PrintCLike.cpp.template"
                                                                }
                                                            #line 4676 "PrintCLike.cpp"
  append(L"\n");
  append(L"  var input: String = null");
                                                            #line 3051 "PrintCLike.cpp.template"
                                                                if (! noLexer)
                                                                {
                                                            #line 4682 "PrintCLike.cpp"
  append(L"\n");
  append(L"  var size = 0");
                                                            #line 3054 "PrintCLike.cpp.template"
                                                                }
                                                                if (tree && useGlr)
                                                                {
                                                            #line 4689 "PrintCLike.cpp"
  append(L"\n");
  append(L"  var eventHandler: ");
                                                            #line 3058 "PrintCLike.cpp.template"
                                                                  print(className.c_str());
                                                            #line 4694 "PrintCLike.cpp"
  append(L".BottomUpEventHandler = null");
                                                            #line 3059 "PrintCLike.cpp.template"
                                                                }
                                                                if (noLexer)
                                                                {
                                                            #line 4700 "PrintCLike.cpp"
  append(L"\n");
  append(L"  var lexer: Lexer = null\n");
  append(L"  var token = new Token");
                                                            #line 3064 "PrintCLike.cpp.template"
                                                                }
                                                                if (useGlr)
                                                                {
                                                            #line 4708 "PrintCLike.cpp"
  append(L"\n");
  append(L"  var maxId = 0");
                                                            #line 3068 "PrintCLike.cpp.template"
                                                                }
                                                                if (trace)
                                                                {
                                                            #line 4715 "PrintCLike.cpp"
  append(L"\n");
  append(L"  var err: Writer = new OutputStreamWriter(System.err, \"UTF-8\")");
                                                            #line 3073 "PrintCLike.cpp.template"
                                                                }
                                                            #line 4720 "PrintCLike.cpp"
  append(L"\n");
  append(L"}\n");
  append(L"\n");
  append(L"object ");
                                                            #line 3077 "PrintCLike.cpp.template"
                                                                print(className.c_str());
                                                            #line 4727 "PrintCLike.cpp"
  append(L" {\n");
  append(L"\n");
  append(L"  def getOffendingToken(e: ParseException) = {\n");
  append(L"    if (e.offending < 0) null else TOKEN(e.offending)\n");
  append(L"  }\n");
                                                            #line 3083 "PrintCLike.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 4736 "PrintCLike.cpp"
  append(L"\n");
  append(L"  def getTerminalName(id: Int) = {\n");
  append(L"    TOKEN(id)\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  def getNonterminalName(id: Int) = {\n");
  append(L"    ");
                                                            #line 3091 "PrintCLike.cpp.template"
                                                                  printSyntheticNamePrefix();
                                                            #line 4746 "PrintCLike.cpp"
  append(L"NONTERMINAL(id)");
                                                            #line 3092 "PrintCLike.cpp.template"
                                                                  printSyntheticNameSuffix();
                                                            #line 4750 "PrintCLike.cpp"
  append(L"\n");
  append(L"  }\n");
                                                            #line 3095 "PrintCLike.cpp.template"
                                                                }
                                                              }
                                                            }

                                                            void PrintCLike::printThreadBody1()
                                                            {
                                                              Trace("PrintCLike::printThreadBody1");

                                                              if (isLrParser)
                                                              {
                                                            #line 4764 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3106 "PrintCLike.cpp.template"
                                                                print(intVar());
                                                            #line 4768 "PrintCLike.cpp"
  append(L"nonterminalId");
                                                            #line 3107 "PrintCLike.cpp.template"
                                                                print(assign());
                                                            #line 4772 "PrintCLike.cpp"
  append(L"-1");
                                                            #line 3108 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                if (isHaxe() || isScala() || isPython())
                                                                {
                                                            #line 4778 "PrintCLike.cpp"
  append(L"\n");
  append(L"while ");
                                                            #line 3112 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                                  if (isPython())
                                                                  {
                                                            #line 4785 "PrintCLike.cpp"
  append(L"T");
                                                            #line 3115 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 4791 "PrintCLike.cpp"
  append(L"t");
                                                            #line 3118 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 4795 "PrintCLike.cpp"
  append(L"rue");
                                                            #line 3119 "PrintCLike.cpp.template"
                                                                  print(ifRightParen());
                                                                }
                                                                else if (isGo())
                                                                {
                                                            #line 4802 "PrintCLike.cpp"
  append(L"\n");
  append(L"for");
                                                            #line 3124 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 4809 "PrintCLike.cpp"
  append(L"\n");
  append(L"for (;;)");
                                                            #line 3128 "PrintCLike.cpp.template"
                                                                }
                                                                print(leftBrace());
                                                                increaseIndent();
                                                                if (trace)
                                                                {
                                                                  if (isCpp())
                                                                  {
                                                            #line 4820 "PrintCLike.cpp"
  append(L"\n");
  append(L"fprintf(stderr, \"  <parse ");
                                                            #line 3136 "PrintCLike.cpp.template"
                                                                    if (useGlr)
                                                                    {
                                                            #line 4826 "PrintCLike.cpp"
  append(L"thread=\\\"%d\\\" offset=\\\"%d\\\" ");
                                                            #line 3138 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 4830 "PrintCLike.cpp"
  append(L"state=\\\"%d\\\" input=\\\"%s%s%s\\\" action=\\\"\",");
                                                            #line 3140 "PrintCLike.cpp.template"
                                                                    if (useGlr)
                                                                    {
                                                            #line 4835 "PrintCLike.cpp"
  append(L"\n");
  append(L"  id,\n");
  append(L"  e0,");
                                                            #line 3144 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 4841 "PrintCLike.cpp"
  append(L"\n");
  append(L"  state,\n");
  append(L"  nonterminalId < 0 ? \"\" : ");
                                                            #line 3147 "PrintCLike.cpp.template"
                                                                    if (stringIntroducer()[0])
                                                                    {
                                                            #line 4848 "PrintCLike.cpp"
  append(L"Utf8Encoder::encode(");
                                                            #line 3149 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 4852 "PrintCLike.cpp"
  append(L"xmlEscape(");
                                                            #line 3150 "PrintCLike.cpp.template"
                                                                    print(nonterminalTableName());
                                                            #line 4856 "PrintCLike.cpp"
  append(L"[nonterminalId], 0).c_str()");
                                                            #line 3151 "PrintCLike.cpp.template"
                                                                    if (stringIntroducer()[0])
                                                                    {
                                                            #line 4861 "PrintCLike.cpp"
  append(L").c_str()");
                                                            #line 3153 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 4865 "PrintCLike.cpp"
  append(L",\n");
  append(L"  nonterminalId < 0 || l1 <= 0 ? \"\" : \" \",\n");
  append(L"  l1 <= 0 ? \"\" : ");
                                                            #line 3156 "PrintCLike.cpp.template"
                                                                    if (stringIntroducer()[0])
                                                                    {
                                                            #line 4872 "PrintCLike.cpp"
  append(L"Utf8Encoder::encode(");
                                                            #line 3158 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 4876 "PrintCLike.cpp"
  append(L"xmlEscape(lookaheadString().c_str(), 0).c_str()");
                                                            #line 3159 "PrintCLike.cpp.template"
                                                                    if (stringIntroducer()[0])
                                                                    {
                                                            #line 4881 "PrintCLike.cpp"
  append(L").c_str()");
                                                            #line 3161 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 4885 "PrintCLike.cpp"
  append(L");\n");
                                                            #line 3163 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                                    if (isHaxe())
                                                                    {
                                                            #line 4893 "PrintCLike.cpp"
  append(L"\n");
  append(L"var traceLine = ");
                                                            #line 3169 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 4900 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3173 "PrintCLike.cpp.template"
                                                                      print(writeTrace());
                                                                    }
                                                            #line 4905 "PrintCLike.cpp"
  append(L"\"  <parse ");
                                                            #line 3175 "PrintCLike.cpp.template"
                                                                    if (useGlr)
                                                                    {
                                                            #line 4910 "PrintCLike.cpp"
  append(L"thread=\\\"\" + ");
                                                            #line 3177 "PrintCLike.cpp.template"
                                                                      if (isGo())
                                                                      {
                                                            #line 4915 "PrintCLike.cpp"
  append(L"strconv.Itoa(");
                                                            #line 3179 "PrintCLike.cpp.template"
                                                                      }
                                                                      else if (isPython())
                                                                      {
                                                            #line 4921 "PrintCLike.cpp"
  append(L"str(");
                                                            #line 3182 "PrintCLike.cpp.template"
                                                                      }
                                                                      print(thiz());
                                                            #line 4926 "PrintCLike.cpp"
  append(L"id");
                                                            #line 3184 "PrintCLike.cpp.template"
                                                                      if (isGo() || isPython())
                                                                      {
                                                            #line 4931 "PrintCLike.cpp"
  append(L")");
                                                            #line 3186 "PrintCLike.cpp.template"
                                                                      }
                                                            #line 4935 "PrintCLike.cpp"
  append(L" + \"\\\" offset=\\\"\" + ");
                                                            #line 3187 "PrintCLike.cpp.template"
                                                                      if (isGo())
                                                                      {
                                                            #line 4940 "PrintCLike.cpp"
  append(L"strconv.Itoa(");
                                                            #line 3189 "PrintCLike.cpp.template"
                                                                      }
                                                                      else if (isPython())
                                                                      {
                                                            #line 4946 "PrintCLike.cpp"
  append(L"str(");
                                                            #line 3192 "PrintCLike.cpp.template"
                                                                      }
                                                                      print(thiz());
                                                            #line 4951 "PrintCLike.cpp"
  append(L"e0");
                                                            #line 3194 "PrintCLike.cpp.template"
                                                                      if (isGo() || isPython())
                                                                      {
                                                            #line 4956 "PrintCLike.cpp"
  append(L")");
                                                            #line 3196 "PrintCLike.cpp.template"
                                                                      }
                                                            #line 4960 "PrintCLike.cpp"
  append(L" + \"\\\" ");
                                                            #line 3197 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 4964 "PrintCLike.cpp"
  append(L"state=\\\"\" + ");
                                                            #line 3198 "PrintCLike.cpp.template"
                                                                    if (isGo())
                                                                    {
                                                            #line 4969 "PrintCLike.cpp"
  append(L"strconv.Itoa(");
                                                            #line 3200 "PrintCLike.cpp.template"
                                                                    }
                                                                    else if (isPython())
                                                                    {
                                                            #line 4975 "PrintCLike.cpp"
  append(L"str(");
                                                            #line 3203 "PrintCLike.cpp.template"
                                                                    }
                                                                    if (useGlr) print(thiz());
                                                            #line 4980 "PrintCLike.cpp"
  append(L"state");
                                                            #line 3205 "PrintCLike.cpp.template"
                                                                    if (isGo() || isPython())
                                                                    {
                                                            #line 4985 "PrintCLike.cpp"
  append(L")");
                                                            #line 3207 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 4989 "PrintCLike.cpp"
  append(L" + \"\\\" input=\\\"\"");
                                                            #line 3208 "PrintCLike.cpp.template"
                                                                    print(endWriteTrace());
                                                                    print(semicolon());
                                                            #line 4994 "PrintCLike.cpp"
  append(L"\n");
  append(L"if ");
                                                            #line 3212 "PrintCLike.cpp.template"
                                                                    print(ifLeftParen());
                                                            #line 4999 "PrintCLike.cpp"
  append(L"nonterminalId >= 0");
                                                            #line 3213 "PrintCLike.cpp.template"
                                                                    print(ifRightParen());
                                                                    print(leftBrace());
                                                            #line 5004 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3216 "PrintCLike.cpp.template"
                                                                    print(writeTrace());
                                                                    print(staticPrefix());
                                                            #line 5010 "PrintCLike.cpp"
  append(L"xmlEscape(");
                                                            #line 3218 "PrintCLike.cpp.template"
                                                                    print(staticPrefix());
                                                                    print(nonterminalTableName());
                                                                    print(leftbracket());
                                                            #line 5016 "PrintCLike.cpp"
  append(L"nonterminalId");
                                                            #line 3221 "PrintCLike.cpp.template"
                                                                    print(rightbracket());
                                                            #line 5020 "PrintCLike.cpp"
  append(L")");
                                                            #line 3222 "PrintCLike.cpp.template"
                                                                    print(endWriteTrace());
                                                                    print(semicolon());
                                                            #line 5025 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if ");
                                                            #line 3225 "PrintCLike.cpp.template"
                                                                    print(ifLeftParen());
                                                                    print(thiz());
                                                            #line 5031 "PrintCLike.cpp"
  append(L"l1 != 0");
                                                            #line 3227 "PrintCLike.cpp.template"
                                                                    print(ifRightParen());
                                                                    printIndented(1, leftBrace());
                                                            #line 5036 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 3230 "PrintCLike.cpp.template"
                                                                    print(writeTrace());
                                                            #line 5041 "PrintCLike.cpp"
  append(L"\" \"");
                                                            #line 3231 "PrintCLike.cpp.template"
                                                                    print(endWriteTrace());
                                                                    print(semicolon());
                                                                    increaseIndent();
                                                                    print(rightBrace());
                                                                    decreaseIndent();
                                                                    print(rightBrace());
                                                            #line 5050 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3238 "PrintCLike.cpp.template"
                                                                    print(writeTrace());
                                                                    print(staticPrefix());
                                                            #line 5055 "PrintCLike.cpp"
  append(L"xmlEscape(");
                                                            #line 3240 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 5059 "PrintCLike.cpp"
  append(L"lookaheadString");
                                                            #line 3241 "PrintCLike.cpp.template"
                                                                    if (! isScala()) print(L"()");
                                                            #line 5063 "PrintCLike.cpp"
  append(L") + \"\\\" action=\\\"\"");
                                                            #line 3242 "PrintCLike.cpp.template"
                                                                    print(endWriteTrace());
                                                                    print(semicolon());
                                                                  }
                                                                }
                                                            #line 5070 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3247 "PrintCLike.cpp.template"
                                                                print(intVal());
                                                            #line 5074 "PrintCLike.cpp"
  append(L"argument");
                                                            #line 3248 "PrintCLike.cpp.template"
                                                                print(assign());
                                                                if (useGlr) print(thiz());
                                                            #line 5079 "PrintCLike.cpp"
  append(L"action >> ");
                                                            #line 3250 "PrintCLike.cpp.template"
                                                                print(format.toString<wchar_t>(grammar->states->dominoBits + LrStates::actionBits));
                                                                print(semicolon());
                                                            #line 5084 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3253 "PrintCLike.cpp.template"
                                                                print(intVal());
                                                            #line 5088 "PrintCLike.cpp"
  append(L"lookback");
                                                            #line 3254 "PrintCLike.cpp.template"
                                                                print(assign());
                                                            #line 5092 "PrintCLike.cpp"
  append(L"(");
                                                            #line 3255 "PrintCLike.cpp.template"
                                                                if (useGlr) print(thiz());
                                                            #line 5096 "PrintCLike.cpp"
  append(L"action >> ");
                                                            #line 3256 "PrintCLike.cpp.template"
                                                                print(format.toString<wchar_t>((int) LrStates::actionBits));
                                                            #line 5100 "PrintCLike.cpp"
  append(L") & ");
                                                            #line 3257 "PrintCLike.cpp.template"
                                                                print(format.toString<wchar_t>((1 << grammar->states->dominoBits) -1));
                                                                print(semicolon());
                                                            #line 5105 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3260 "PrintCLike.cpp.template"
                                                                print(intVar());
                                                            #line 5109 "PrintCLike.cpp"
  append(L"shift");
                                                            #line 3261 "PrintCLike.cpp.template"
                                                                print(assign());
                                                            #line 5113 "PrintCLike.cpp"
  append(L"-1");
                                                            #line 3262 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 5117 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3264 "PrintCLike.cpp.template"
                                                                print(intVar());
                                                            #line 5121 "PrintCLike.cpp"
  append(L"reduce");
                                                            #line 3265 "PrintCLike.cpp.template"
                                                                print(assign());
                                                            #line 5125 "PrintCLike.cpp"
  append(L"-1");
                                                            #line 3266 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 5129 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3268 "PrintCLike.cpp.template"
                                                                print(intVar());
                                                            #line 5133 "PrintCLike.cpp"
  append(L"symbols");
                                                            #line 3269 "PrintCLike.cpp.template"
                                                                print(assign());
                                                            #line 5137 "PrintCLike.cpp"
  append(L"-1");
                                                            #line 3270 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                if (useGlr)
                                                                {
                                                            #line 5143 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3274 "PrintCLike.cpp.template"
                                                                  print(intVar());
                                                            #line 5147 "PrintCLike.cpp"
  append(L"pos");
                                                            #line 3275 "PrintCLike.cpp.template"
                                                                  print(assign());
                                                            #line 5151 "PrintCLike.cpp"
  append(L"-1");
                                                            #line 3276 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                                if (isPython())
                                                                {
                                                            #line 5158 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3281 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 5162 "PrintCLike.cpp"
  append(L"action &= ");
                                                            #line 3282 "PrintCLike.cpp.template"
                                                                  print(format.toString<wchar_t>((int) LrStates::actionMask));
                                                                }
                                                                else
                                                                {
                                                            #line 5169 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3287 "PrintCLike.cpp.template"
                                                                  if (! isScala())
                                                                  {
                                                            #line 5174 "PrintCLike.cpp"
  append(L"switch ");
                                                            #line 3289 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(ifLeftParen());
                                                                  if (useGlr) print(thiz());
                                                            #line 5180 "PrintCLike.cpp"
  append(L"action & ");
                                                            #line 3292 "PrintCLike.cpp.template"
                                                                  print(format.toString<wchar_t>((int) LrStates::actionMask));
                                                                  print(ifRightParen());
                                                                  if (isScala())
                                                                  {
                                                            #line 5187 "PrintCLike.cpp"
  append(L" match");
                                                            #line 3296 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(leftBrace());
                                                                }
                                                                if (isPython())
                                                                {
                                                            #line 5195 "PrintCLike.cpp"
  append(L"\n");
  append(L"if ");
                                                            #line 3302 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 5200 "PrintCLike.cpp"
  append(L"action == ");
                                                            #line 3303 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 5206 "PrintCLike.cpp"
  append(L"\n");
  append(L"case ");
                                                            #line 3307 "PrintCLike.cpp.template"
                                                                }
                                                                print(format.toString<wchar_t>((int) LrStates::SHIFT));
                                                                print(caseIntroducer());
                                                            #line 5213 "PrintCLike.cpp"
  append(L" ");
                                                            #line 3310 "PrintCLike.cpp.template"
                                                                print(inlineCommentIntroducer());
                                                            #line 5217 "PrintCLike.cpp"
  append(L"SHIFT\n");
  append(L"  shift = argument");
                                                            #line 3312 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                if (! isHaxe() && ! isScala() && ! isGo() && ! isPython())
                                                                {
                                                            #line 5224 "PrintCLike.cpp"
  append(L"\n");
  append(L"  break");
                                                            #line 3316 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                            #line 5230 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3319 "PrintCLike.cpp.template"
                                                                if (isPython())
                                                                {
                                                            #line 5235 "PrintCLike.cpp"
  append(L"\n");
  append(L"elif ");
                                                            #line 3322 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 5240 "PrintCLike.cpp"
  append(L"action == ");
                                                            #line 3323 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 5246 "PrintCLike.cpp"
  append(L"\n");
  append(L"case ");
                                                            #line 3327 "PrintCLike.cpp.template"
                                                                }
                                                                print(format.toString<wchar_t>((int) LrStates::REDUCE));
                                                                print(caseIntroducer());
                                                            #line 5253 "PrintCLike.cpp"
  append(L" ");
                                                            #line 3330 "PrintCLike.cpp.template"
                                                                print(inlineCommentIntroducer());
                                                            #line 5257 "PrintCLike.cpp"
  append(L"REDUCE\n");
  append(L"  reduce = argument");
                                                            #line 3332 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 5262 "PrintCLike.cpp"
  append(L"\n");
  append(L"  symbols = lookback");
                                                            #line 3334 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                if (! isHaxe() && ! isScala() && ! isGo() && ! isPython())
                                                                {
                                                            #line 5269 "PrintCLike.cpp"
  append(L"\n");
  append(L"  break");
                                                            #line 3338 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                                if (grammar->states->hasLookback)
                                                                {
                                                            #line 5277 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3343 "PrintCLike.cpp.template"
                                                                  if (isPython())
                                                                  {
                                                            #line 5282 "PrintCLike.cpp"
  append(L"\n");
  append(L"elif ");
                                                            #line 3346 "PrintCLike.cpp.template"
                                                                    if (useGlr) print(thiz());
                                                            #line 5287 "PrintCLike.cpp"
  append(L"action == ");
                                                            #line 3347 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 5293 "PrintCLike.cpp"
  append(L"\n");
  append(L"case ");
                                                            #line 3351 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(format.toString<wchar_t>((int) LrStates::REDUCE_LOOKBACK));
                                                                  print(caseIntroducer());
                                                            #line 5300 "PrintCLike.cpp"
  append(L" ");
                                                            #line 3354 "PrintCLike.cpp.template"
                                                                  print(inlineCommentIntroducer());
                                                            #line 5304 "PrintCLike.cpp"
  append(L"REDUCE+LOOKBACK\n");
  append(L"  reduce = argument");
                                                            #line 3356 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                            #line 5309 "PrintCLike.cpp"
  append(L"\n");
  append(L"  symbols = ");
                                                            #line 3358 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                                  if (useGlr)
                                                                  {
                                                            #line 5316 "PrintCLike.cpp"
  append(L"stack");
                                                            #line 3361 "PrintCLike.cpp.template"
                                                                    if (isTypescript()) print(L"!");
                                                                    print(arrow());
                                                                  }
                                                                  if (isGo() && useGlr)
                                                                  {
                                                            #line 5324 "PrintCLike.cpp"
  append(L"Count");
                                                            #line 3366 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 5330 "PrintCLike.cpp"
  append(L"count");
                                                            #line 3369 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 5334 "PrintCLike.cpp"
  append(L"(lookback)");
                                                            #line 3370 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                  if (! isHaxe() && ! isScala() && ! isGo() && ! isPython())
                                                                  {
                                                            #line 5340 "PrintCLike.cpp"
  append(L"\n");
  append(L"  break");
                                                            #line 3374 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                  }
                                                                }
                                                            #line 5347 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3378 "PrintCLike.cpp.template"
                                                                if (isPython())
                                                                {
                                                            #line 5352 "PrintCLike.cpp"
  append(L"\n");
  append(L"elif ");
                                                            #line 3381 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 5357 "PrintCLike.cpp"
  append(L"action == ");
                                                            #line 3382 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 5363 "PrintCLike.cpp"
  append(L"\n");
  append(L"case ");
                                                            #line 3386 "PrintCLike.cpp.template"
                                                                }
                                                                print(format.toString<wchar_t>((int) LrStates::SHIFT_REDUCE));
                                                                print(caseIntroducer());
                                                            #line 5370 "PrintCLike.cpp"
  append(L" ");
                                                            #line 3389 "PrintCLike.cpp.template"
                                                                print(inlineCommentIntroducer());
                                                            #line 5374 "PrintCLike.cpp"
  append(L"SHIFT+REDUCE\n");
  append(L"  shift = ");
                                                            #line 3391 "PrintCLike.cpp.template"
                                                                if (useGlr) print(thiz());
                                                            #line 5379 "PrintCLike.cpp"
  append(L"state");
                                                            #line 3392 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 5383 "PrintCLike.cpp"
  append(L"\n");
  append(L"  reduce = argument");
                                                            #line 3394 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 5388 "PrintCLike.cpp"
  append(L"\n");
  append(L"  symbols = lookback + 1");
                                                            #line 3396 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                if (! isHaxe() && ! isScala() && ! isGo() && ! isPython())
                                                                {
                                                            #line 5395 "PrintCLike.cpp"
  append(L"\n");
  append(L"  break");
                                                            #line 3400 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                                if (grammar->states->hasLookback)
                                                                {
                                                            #line 5403 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3405 "PrintCLike.cpp.template"
                                                                  if (isPython())
                                                                  {
                                                            #line 5408 "PrintCLike.cpp"
  append(L"\n");
  append(L"elif ");
                                                            #line 3408 "PrintCLike.cpp.template"
                                                                    if (useGlr) print(thiz());
                                                            #line 5413 "PrintCLike.cpp"
  append(L"action == ");
                                                            #line 3409 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 5419 "PrintCLike.cpp"
  append(L"\n");
  append(L"case ");
                                                            #line 3413 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(format.toString<wchar_t>((int) LrStates::SHIFT_REDUCE_LOOKBACK));
                                                                  print(caseIntroducer());
                                                            #line 5426 "PrintCLike.cpp"
  append(L" ");
                                                            #line 3416 "PrintCLike.cpp.template"
                                                                  print(inlineCommentIntroducer());
                                                            #line 5430 "PrintCLike.cpp"
  append(L"SHIFT+REDUCE+LOOKBACK\n");
  append(L"  shift = ");
                                                            #line 3418 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 5435 "PrintCLike.cpp"
  append(L"state");
                                                            #line 3419 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                            #line 5439 "PrintCLike.cpp"
  append(L"\n");
  append(L"  reduce = argument");
                                                            #line 3421 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                            #line 5444 "PrintCLike.cpp"
  append(L"\n");
  append(L"  symbols = ");
                                                            #line 3423 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                                  if (useGlr)
                                                                  {
                                                            #line 5451 "PrintCLike.cpp"
  append(L"stack");
                                                            #line 3426 "PrintCLike.cpp.template"
                                                                    if (isTypescript()) print(L"!");
                                                                    print(arrow());
                                                                  }
                                                                  if (isGo() && useGlr)
                                                                  {
                                                            #line 5459 "PrintCLike.cpp"
  append(L"Count");
                                                            #line 3431 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 5465 "PrintCLike.cpp"
  append(L"count");
                                                            #line 3434 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 5469 "PrintCLike.cpp"
  append(L"(lookback) + 1");
                                                            #line 3435 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                  if (! isHaxe() && ! isScala() && ! isGo() && ! isPython())
                                                                  {
                                                            #line 5475 "PrintCLike.cpp"
  append(L"\n");
  append(L"  break");
                                                            #line 3439 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                  }
                                                                }
                                                            #line 5482 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3443 "PrintCLike.cpp.template"
                                                                if (isPython())
                                                                {
                                                            #line 5487 "PrintCLike.cpp"
  append(L"\n");
  append(L"elif ");
                                                            #line 3446 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 5492 "PrintCLike.cpp"
  append(L"action == ");
                                                            #line 3447 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 5498 "PrintCLike.cpp"
  append(L"\n");
  append(L"case ");
                                                            #line 3451 "PrintCLike.cpp.template"
                                                                }
                                                                print(format.toString<wchar_t>((int) LrStates::SHIFT_ACCEPT));
                                                                print(caseIntroducer());
                                                            #line 5505 "PrintCLike.cpp"
  append(L" ");
                                                            #line 3454 "PrintCLike.cpp.template"
                                                                print(inlineCommentIntroducer());
                                                            #line 5509 "PrintCLike.cpp"
  append(L"ACCEPT");
                                                            #line 3455 "PrintCLike.cpp.template"
                                                                if (trace)
                                                                {
                                                                  if (isCpp())
                                                                  {
                                                            #line 5516 "PrintCLike.cpp"
  append(L"\n");
  append(L"  fprintf(stderr, ");
                                                            #line 3460 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 5523 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3464 "PrintCLike.cpp.template"
                                                                    print(writeTrace());
                                                                  }
                                                            #line 5529 "PrintCLike.cpp"
  append(L"\"accept\\\"/>");
                                                            #line 3466 "PrintCLike.cpp.template"
                                                                  if (! isHaxe())
                                                                  {
                                                            #line 5534 "PrintCLike.cpp"
  append(L"\\n");
                                                            #line 3468 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 5538 "PrintCLike.cpp"
  append(L"\"");
                                                            #line 3469 "PrintCLike.cpp.template"
                                                                  print(endWriteTrace());
                                                                  print(semicolon());
                                                                  if (isHaxe())
                                                                  {
                                                            #line 5545 "PrintCLike.cpp"
  append(L"\n");
  append(L"  trace(traceLine);");
                                                            #line 3474 "PrintCLike.cpp.template"
                                                                  }
                                                                }
                                                                if (useGlr)
                                                                {
                                                            #line 5553 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3479 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 5558 "PrintCLike.cpp"
  append(L"accepted = ");
                                                            #line 3480 "PrintCLike.cpp.template"
                                                                  if (isPython())
                                                                  {
                                                            #line 5563 "PrintCLike.cpp"
  append(L"T");
                                                            #line 3482 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 5569 "PrintCLike.cpp"
  append(L"t");
                                                            #line 3485 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 5573 "PrintCLike.cpp"
  append(L"rue");
                                                            #line 3486 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                            #line 5577 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3488 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 5582 "PrintCLike.cpp"
  append(L"action = 0");
                                                            #line 3489 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                            #line 5586 "PrintCLike.cpp"
  append(L"\n");
  append(L"  return ");
                                                            #line 3491 "PrintCLike.cpp.template"
                                                                  if (isHaxe() || isTypescript() || isPython()) print(staticPrefix());
                                                            #line 5591 "PrintCLike.cpp"
  append(L"ACCEPTED");
                                                            #line 3492 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                                else
                                                                {
                                                            #line 5598 "PrintCLike.cpp"
  append(L"\n");
  append(L"  return");
                                                            #line 3497 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }

                                                                if (useGlr)
                                                                {
                                                            #line 5607 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3503 "PrintCLike.cpp.template"
                                                                  if (isPython())
                                                                  {
                                                            #line 5612 "PrintCLike.cpp"
  append(L"\n");
  append(L"elif ");
                                                            #line 3506 "PrintCLike.cpp.template"
                                                                    if (useGlr) print(thiz());
                                                            #line 5617 "PrintCLike.cpp"
  append(L"action == ");
                                                            #line 3507 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 5623 "PrintCLike.cpp"
  append(L"\n");
  append(L"case ");
                                                            #line 3511 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(format.toString<wchar_t>((int) LrStates::FORK));
                                                                  print(caseIntroducer());
                                                            #line 5630 "PrintCLike.cpp"
  append(L" ");
                                                            #line 3514 "PrintCLike.cpp.template"
                                                                  print(inlineCommentIntroducer());
                                                            #line 5634 "PrintCLike.cpp"
  append(L"FORK");
                                                            #line 3515 "PrintCLike.cpp.template"
                                                                  if (trace)
                                                                  {
                                                                    if (isCpp())
                                                                    {
                                                            #line 5641 "PrintCLike.cpp"
  append(L"\n");
  append(L"  fprintf(stderr, \"fork\\\"/>\\n\");");
                                                            #line 3520 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 5648 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3524 "PrintCLike.cpp.template"
                                                                      print(writeTrace());
                                                            #line 5653 "PrintCLike.cpp"
  append(L"\"fork\\\"/>");
                                                            #line 3525 "PrintCLike.cpp.template"
                                                                      if (! isHaxe())
                                                                      {
                                                            #line 5658 "PrintCLike.cpp"
  append(L"\\n\"");
                                                            #line 3527 "PrintCLike.cpp.template"
                                                                        print(endWriteTrace());
                                                                        print(semicolon());
                                                                      }
                                                                      else
                                                                      {
                                                            #line 5666 "PrintCLike.cpp"
  append(L"\";\n");
  append(L"  trace(traceLine);");
                                                            #line 3533 "PrintCLike.cpp.template"
                                                                      }
                                                                    }
                                                                  }
                                                                  if (isGo())
                                                                  {
                                                            #line 5675 "PrintCLike.cpp"
  append(L"\n");
  append(L"  heap.Push(this.threads, new(ParsingThread).copy(this, appendix[argument]))");
                                                            #line 3540 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isPython())
                                                                  {
                                                            #line 5682 "PrintCLike.cpp"
  append(L"\n");
  append(L"  forked = ");
                                                            #line 3544 "PrintCLike.cpp.template"
                                                                    print(staticPrefix());
                                                            #line 5687 "PrintCLike.cpp"
  append(L"ParsingThread().copy(self, ");
                                                            #line 3545 "PrintCLike.cpp.template"
                                                                    print(staticPrefix());
                                                            #line 5691 "PrintCLike.cpp"
  append(L"APPENDIX[argument])\n");
  append(L"  heapq.heappush(self.threads, (False, forked.e0, forked.id, forked))");
                                                            #line 3548 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 5698 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3552 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 5703 "PrintCLike.cpp"
  append(L"threads");
                                                            #line 3553 "PrintCLike.cpp.template"
                                                                    if (isCpp())
                                                                    {
                                                            #line 5708 "PrintCLike.cpp"
  append(L"->push(");
                                                            #line 3555 "PrintCLike.cpp.template"
                                                                    }
                                                                    else if (isScala())
                                                                    {
                                                            #line 5714 "PrintCLike.cpp"
  append(L" += ");
                                                            #line 3558 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 5720 "PrintCLike.cpp"
  append(L".offer(");
                                                            #line 3561 "PrintCLike.cpp.template"
                                                                    }
                                                                    if (isCpp() || isScala()) print(L"(");
                                                            #line 5725 "PrintCLike.cpp"
  append(L"new ParsingThread");
                                                            #line 3563 "PrintCLike.cpp.template"
                                                                    if (! isScala()) print(L"()");
                                                                    if (isCpp() || isScala()) print(L")");
                                                                    print(arrow());
                                                            #line 5731 "PrintCLike.cpp"
  append(L"copy(this");
                                                            #line 3566 "PrintCLike.cpp.template"
                                                                    if (isJavascript())
                                                                    {
                                                            #line 5736 "PrintCLike.cpp"
  append(L"Thread");
                                                            #line 3568 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 5740 "PrintCLike.cpp"
  append(L", ");
                                                            #line 3569 "PrintCLike.cpp.template"
                                                                    print(staticPrefix());
                                                            #line 5744 "PrintCLike.cpp"
  append(L"APPENDIX");
                                                            #line 3570 "PrintCLike.cpp.template"
                                                                    print(leftbracket());
                                                            #line 5748 "PrintCLike.cpp"
  append(L"argument");
                                                            #line 3571 "PrintCLike.cpp.template"
                                                                    print(rightbracket());
                                                            #line 5752 "PrintCLike.cpp"
  append(L")");
                                                            #line 3572 "PrintCLike.cpp.template"
                                                                    if (! isScala()) print(L")");
                                                                    print(semicolon());
                                                                  }
                                                            #line 5758 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3576 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 5763 "PrintCLike.cpp"
  append(L"action = ");
                                                            #line 3577 "PrintCLike.cpp.template"
                                                                  print(staticPrefix());
                                                                  if (isGo())
                                                                  {
                                                            #line 5769 "PrintCLike.cpp"
  append(L"appendix");
                                                            #line 3580 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 5775 "PrintCLike.cpp"
  append(L"APPENDIX");
                                                            #line 3583 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(leftbracket());
                                                            #line 5780 "PrintCLike.cpp"
  append(L"argument + 1");
                                                            #line 3585 "PrintCLike.cpp.template"
                                                                  print(rightbracket());
                                                                  print(semicolon());
                                                            #line 5785 "PrintCLike.cpp"
  append(L"\n");
  append(L"  return ");
                                                            #line 3588 "PrintCLike.cpp.template"
                                                                  if (isHaxe() || isTypescript() || isPython()) print(staticPrefix());
                                                            #line 5790 "PrintCLike.cpp"
  append(L"PARSING");
                                                            #line 3589 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                            #line 5795 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3592 "PrintCLike.cpp.template"
                                                                if (isPython())
                                                                {
                                                            #line 5800 "PrintCLike.cpp"
  append(L"\n");
  append(L"else");
                                                            #line 3595 "PrintCLike.cpp.template"
                                                                }
                                                                else if (isScala())
                                                                {
                                                            #line 5807 "PrintCLike.cpp"
  append(L"\n");
  append(L"case _");
                                                            #line 3599 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 5814 "PrintCLike.cpp"
  append(L"\n");
  append(L"default");
                                                            #line 3603 "PrintCLike.cpp.template"
                                                                }
                                                                print(caseIntroducer());
                                                            #line 5820 "PrintCLike.cpp"
  append(L" ");
                                                            #line 3605 "PrintCLike.cpp.template"
                                                                print(inlineCommentIntroducer());
                                                            #line 5824 "PrintCLike.cpp"
  append(L"ERROR");
                                                            #line 3606 "PrintCLike.cpp.template"
                                                                if (useGlr)
                                                                {
                                                                  if (trace)
                                                                  {
                                                                    if (isCpp())
                                                                    {
                                                            #line 5833 "PrintCLike.cpp"
  append(L"\n");
  append(L"  fprintf(stderr, \"fail\\\"/>\\n\");");
                                                            #line 3613 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 5840 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3617 "PrintCLike.cpp.template"
                                                                      print(writeTrace());
                                                            #line 5845 "PrintCLike.cpp"
  append(L"\"fail\\\"/>");
                                                            #line 3618 "PrintCLike.cpp.template"
                                                                      if (! isHaxe())
                                                                      {
                                                            #line 5850 "PrintCLike.cpp"
  append(L"\\n\"");
                                                            #line 3620 "PrintCLike.cpp.template"
                                                                        print(endWriteTrace());
                                                                        print(semicolon());
                                                                      }
                                                                      else
                                                                      {
                                                            #line 5858 "PrintCLike.cpp"
  append(L"\";\n");
  append(L"  trace(traceLine);");
                                                            #line 3626 "PrintCLike.cpp.template"
                                                                      }
                                                                    }
                                                                  }
                                                            #line 5865 "PrintCLike.cpp"
  append(L"\n");
  append(L"  return ");
                                                            #line 3630 "PrintCLike.cpp.template"
                                                                  if (isHaxe() || isTypescript() || isPython()) print(staticPrefix());
                                                            #line 5870 "PrintCLike.cpp"
  append(L"ERROR");
                                                            #line 3631 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                                else
                                                                {
                                                            #line 5877 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3636 "PrintCLike.cpp.template"
                                                                  print(beginThrowStmt());
                                                                  print(thiz());
                                                            #line 5883 "PrintCLike.cpp"
  append(L"b1, ");
                                                            #line 3638 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 5887 "PrintCLike.cpp"
  append(L"e1, ");
                                                            #line 3639 "PrintCLike.cpp.template"
                                                                  print(staticPrefix());
                                                                  if (isGo())
                                                                  {
                                                            #line 5893 "PrintCLike.cpp"
  append(L"tokenset");
                                                            #line 3642 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 5899 "PrintCLike.cpp"
  append(L"TOKENSET");
                                                            #line 3645 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(leftbracket());
                                                            #line 5904 "PrintCLike.cpp"
  append(L"state");
                                                            #line 3647 "PrintCLike.cpp.template"
                                                                  print(rightbracket());
                                                            #line 5908 "PrintCLike.cpp"
  append(L" + 1, ");
                                                            #line 3648 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 5912 "PrintCLike.cpp"
  append(L"l1, -1");
                                                            #line 3649 "PrintCLike.cpp.template"
                                                                  print(endThrowStmt());
                                                                  print(semicolon());
                                                                }
                                                                print(rightBrace());
                                                            #line 5919 "PrintCLike.cpp"
  append(L"\n");
  append(L"\n");
  append(L"if ");
                                                            #line 3655 "PrintCLike.cpp.template"
                                                                print(ifLeftParen());
                                                            #line 5925 "PrintCLike.cpp"
  append(L"shift >= 0");
                                                            #line 3656 "PrintCLike.cpp.template"
                                                                print(ifRightParen());
                                                                print(leftBrace());
                                                                if (trace)
                                                                {
                                                                  if (isCpp())
                                                                  {
                                                            #line 5934 "PrintCLike.cpp"
  append(L"\n");
  append(L"  fprintf(stderr, ");
                                                            #line 3663 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 5941 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3667 "PrintCLike.cpp.template"
                                                                    print(writeTrace());
                                                                  }
                                                            #line 5947 "PrintCLike.cpp"
  append(L"\"shift\"");
                                                            #line 3669 "PrintCLike.cpp.template"
                                                                  print(endWriteTrace());
                                                                  print(semicolon());
                                                                }
                                                            #line 5953 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if ");
                                                            #line 3673 "PrintCLike.cpp.template"
                                                                print(ifLeftParen());
                                                            #line 5958 "PrintCLike.cpp"
  append(L"nonterminalId < 0");
                                                            #line 3674 "PrintCLike.cpp.template"
                                                                print(ifRightParen());
                                                                printIndented(1, leftBrace());
                                                                if (resolvesAmbiguity)
                                                                {
                                                            #line 5965 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 3679 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 5970 "PrintCLike.cpp"
  append(L"eventCount");
                                                            #line 3680 "PrintCLike.cpp.template"
                                                                  print(incrementOp());
                                                                  print(semicolon());
                                                                }
                                                                if (tree)
                                                                {
                                                            #line 5978 "PrintCLike.cpp"
  append(L"\n");
  append(L"    if ");
                                                            #line 3686 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                                  if (useGlr) print(thiz());
                                                            #line 5984 "PrintCLike.cpp"
  append(L"eventHandler != ");
                                                            #line 3688 "PrintCLike.cpp.template"
                                                                  print(nullPtr());
                                                                  if (shiftAmbiguity)
                                                                  {
                                                                    print(isPython() ? L" or not " : L" || ! ");
                                                                    print(thiz());
                                                                    print(isGo() ? L"IsUnambiguous" : L"isUnambiguous");
                                                                    if (! isScala()) print(L"()");
                                                                  }
                                                                  print(ifRightParen());
                                                                  printIndented(2, leftBrace());
                                                                  if (useGlr)
                                                                  {
                                                            #line 5999 "PrintCLike.cpp"
  append(L"\n");
  append(L"      if ");
                                                            #line 3701 "PrintCLike.cpp.template"
                                                                    print(ifLeftParen());
                                                                    print(thiz());
                                                                    if (isGo())
                                                                    {
                                                            #line 6007 "PrintCLike.cpp"
  append(L"IsUnambiguous");
                                                            #line 3705 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 6013 "PrintCLike.cpp"
  append(L"isUnambiguous");
                                                            #line 3708 "PrintCLike.cpp.template"
                                                                    }
                                                                    if (! isScala()) print(L"()");
                                                                    print(ifRightParen());
                                                                    printIndented(3, leftBrace());
                                                                    increaseIndent();
                                                                  }
                                                            #line 6022 "PrintCLike.cpp"
  append(L"\n");
  append(L"      ");
                                                            #line 3715 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 6027 "PrintCLike.cpp"
  append(L"eventHandler");
                                                            #line 3716 "PrintCLike.cpp.template"
                                                                  if (shiftAmbiguity && isTypescript()) print(L"!");
                                                                  print(arrow());
                                                                  if (isGo())
                                                                  {
                                                            #line 6034 "PrintCLike.cpp"
  append(L"T");
                                                            #line 3720 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 6040 "PrintCLike.cpp"
  append(L"t");
                                                            #line 3723 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 6044 "PrintCLike.cpp"
  append(L"erminal(");
                                                            #line 3724 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 6048 "PrintCLike.cpp"
  append(L"l1, ");
                                                            #line 3725 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 6052 "PrintCLike.cpp"
  append(L"b1, ");
                                                            #line 3726 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 6056 "PrintCLike.cpp"
  append(L"e1)");
                                                            #line 3727 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                  if (! useGlr)
                                                                  {
                                                                    increaseIndent(2);
                                                                    print(rightBrace());
                                                                    decreaseIndent(2);
                                                                  }
                                                                  else
                                                                  {
                                                                    decreaseIndent();
                                                            #line 6069 "PrintCLike.cpp"
  append(L"\n");
  append(L"      ");
                                                            #line 3738 "PrintCLike.cpp.template"
                                                                    printIndented(3, elseWithBraces());
                                                            #line 6074 "PrintCLike.cpp"
  append(L"\n");
  append(L"        ");
                                                            #line 3740 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 6079 "PrintCLike.cpp"
  append(L"deferredEvent = ");
                                                            #line 3741 "PrintCLike.cpp.template"
                                                                    if (isGo())
                                                                    {
                                                            #line 6084 "PrintCLike.cpp"
  append(L"&TerminalEvent{&AbstractDeferredEvent{");
                                                            #line 3743 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                                      if (! isPython())
                                                                      {
                                                            #line 6092 "PrintCLike.cpp"
  append(L"new ");
                                                            #line 3748 "PrintCLike.cpp.template"
                                                                      }
                                                                      if (! isHaxe() && ! isTypescript()) print(staticPrefix());
                                                                      if (isJavascript() || isTypescript())
                                                                      {
                                                            #line 6099 "PrintCLike.cpp"
  append(L"DeferredEvent");
                                                            #line 3752 "PrintCLike.cpp.template"
                                                                      }
                                                                      else
                                                                      {
                                                            #line 6105 "PrintCLike.cpp"
  append(L"TerminalEvent");
                                                            #line 3755 "PrintCLike.cpp.template"
                                                                      }
                                                            #line 6109 "PrintCLike.cpp"
  append(L"(");
                                                            #line 3756 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(thiz());
                                                            #line 6114 "PrintCLike.cpp"
  append(L"deferredEvent, ");
                                                            #line 3758 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 6118 "PrintCLike.cpp"
  append(L"l1, ");
                                                            #line 3759 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 6122 "PrintCLike.cpp"
  append(L"b1, ");
                                                            #line 3760 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 6126 "PrintCLike.cpp"
  append(L"e1");
                                                            #line 3761 "PrintCLike.cpp.template"
                                                                    if (isTypescript())
                                                                    {
                                                            #line 6131 "PrintCLike.cpp"
  append(L", -1");
                                                            #line 3763 "PrintCLike.cpp.template"
                                                                    }
                                                                    if (isGo())
                                                                    {
                                                            #line 6137 "PrintCLike.cpp"
  append(L"}}");
                                                            #line 3767 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 6143 "PrintCLike.cpp"
  append(L")");
                                                            #line 3771 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                                    }
                                                                    increaseIndent(3);
                                                                    print(rightBrace());
                                                                    decreaseIndent();
                                                                    print(rightBrace());
                                                                    decreaseIndent(2);
                                                                  }
                                                            #line 6154 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 3780 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 6159 "PrintCLike.cpp"
  append(L"es = ");
                                                            #line 3781 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 6163 "PrintCLike.cpp"
  append(L"e1");
                                                            #line 3782 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                                if (useGlr)
                                                                {
                                                            #line 6170 "PrintCLike.cpp"
  append(L"\n");
  append(L"    pos = ");
                                                            #line 3787 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 6175 "PrintCLike.cpp"
  append(L"b1");
                                                            #line 3788 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                                else
                                                                {
                                                            #line 6182 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 3793 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 6187 "PrintCLike.cpp"
  append(L"push(state, lookback");
                                                            #line 3794 "PrintCLike.cpp.template"
                                                                  if (tree)
                                                                  {
                                                            #line 6192 "PrintCLike.cpp"
  append(L", ");
                                                            #line 3796 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 6196 "PrintCLike.cpp"
  append(L"b1");
                                                            #line 3797 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 6200 "PrintCLike.cpp"
  append(L")");
                                                            #line 3798 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                            #line 6205 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 3801 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 6210 "PrintCLike.cpp"
  append(L"consume(");
                                                            #line 3802 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 6214 "PrintCLike.cpp"
  append(L"l1)");
                                                            #line 3803 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 6218 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3805 "PrintCLike.cpp.template"
                                                                printIndented(1, elseWithBraces());
                                                                if (useGlr)
                                                                {
                                                            #line 6225 "PrintCLike.cpp"
  append(L"\n");
  append(L"    pos = ");
                                                            #line 3809 "PrintCLike.cpp.template"
                                                                  if (tree)
                                                                  {
                                                                    print(thiz());
                                                            #line 6232 "PrintCLike.cpp"
  append(L"bs");
                                                            #line 3812 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 6238 "PrintCLike.cpp"
  append(L"0");
                                                            #line 3815 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(semicolon());
                                                                }
                                                                else
                                                                {
                                                            #line 6246 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 3821 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 6251 "PrintCLike.cpp"
  append(L"push(state, lookback");
                                                            #line 3822 "PrintCLike.cpp.template"
                                                                  if (tree)
                                                                  {
                                                            #line 6256 "PrintCLike.cpp"
  append(L", bs");
                                                            #line 3824 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 6260 "PrintCLike.cpp"
  append(L")");
                                                            #line 3825 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                                increaseIndent();
                                                                print(rightBrace());
                                                                decreaseIndent();
                                                                if (! useGlr)
                                                                {
                                                            #line 6270 "PrintCLike.cpp"
  append(L"\n");
  append(L"  state = shift");
                                                            #line 3833 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                                print(rightBrace());
                                                            #line 6277 "PrintCLike.cpp"
  append(L"\n");
  append(L"\n");
  append(L"if ");
                                                            #line 3838 "PrintCLike.cpp.template"
                                                                print(ifLeftParen());
                                                            #line 6283 "PrintCLike.cpp"
  append(L"reduce < 0");
                                                            #line 3839 "PrintCLike.cpp.template"
                                                                print(ifRightParen());
                                                                print(leftBrace());
                                                                if (trace)
                                                                {
                                                                  if (isCpp())
                                                                  {
                                                            #line 6292 "PrintCLike.cpp"
  append(L"\n");
  append(L"  fprintf(stderr, ");
                                                            #line 3846 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 6299 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3850 "PrintCLike.cpp.template"
                                                                    print(writeTrace());
                                                                  }
                                                            #line 6305 "PrintCLike.cpp"
  append(L"\"\\\"/>");
                                                            #line 3852 "PrintCLike.cpp.template"
                                                                  if (! isHaxe())
                                                                  {
                                                            #line 6310 "PrintCLike.cpp"
  append(L"\\n\"");
                                                            #line 3854 "PrintCLike.cpp.template"
                                                                    print(endWriteTrace());
                                                                    print(semicolon());
                                                                  }
                                                                  else
                                                                  {
                                                            #line 6318 "PrintCLike.cpp"
  append(L"\";\n");
  append(L"  trace(traceLine);");
                                                            #line 3860 "PrintCLike.cpp.template"
                                                                  }
                                                                }
                                                                if (useGlr)
                                                                {
                                                                  printStackAllocation();
                                                                }
                                                            #line 6328 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3867 "PrintCLike.cpp.template"
                                                                if (useGlr) print(thiz());
                                                            #line 6333 "PrintCLike.cpp"
  append(L"action = ");
                                                            #line 3868 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 6337 "PrintCLike.cpp"
  append(L"predict(");
                                                            #line 3869 "PrintCLike.cpp.template"
                                                                if (useGlr) print(thiz());
                                                            #line 6341 "PrintCLike.cpp"
  append(L"state)");
                                                            #line 3870 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                if (useGlr)
                                                                {
                                                                  if (isCpp())
                                                                  {
                                                            #line 6349 "PrintCLike.cpp"
  append(L"\n");
  append(L"  break");
                                                            #line 3876 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                  }
                                                                  else
                                                                  {
                                                            #line 6357 "PrintCLike.cpp"
  append(L"\n");
  append(L"  return ");
                                                            #line 3881 "PrintCLike.cpp.template"
                                                                    if (isHaxe() || isTypescript() || isPython()) print(staticPrefix());
                                                            #line 6362 "PrintCLike.cpp"
  append(L"PARSING");
                                                            #line 3882 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                  }
                                                                }
                                                                else
                                                                {
                                                            #line 6370 "PrintCLike.cpp"
  append(L"\n");
  append(L"  nonterminalId = -1");
                                                            #line 3888 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                            #line 6376 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3891 "PrintCLike.cpp.template"
                                                                print(elseWithBraces());
                                                                if (hasCustomCode)
                                                                {
                                                            #line 6382 "PrintCLike.cpp"
  append(L"\n");
  append(L"  nonterminalId = ");
                                                            #line 3895 "PrintCLike.cpp.template"
                                                                  print(staticPrefix());
                                                                  if (isGo())
                                                                  {
                                                            #line 6389 "PrintCLike.cpp"
  append(L"reduction");
                                                            #line 3898 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 6395 "PrintCLike.cpp"
  append(L"REDUCTION");
                                                            #line 3901 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(leftbracket());
                                                            #line 6400 "PrintCLike.cpp"
  append(L"reduce");
                                                            #line 3903 "PrintCLike.cpp.template"
                                                                  print(rightbracket());
                                                                  print(semicolon());
                                                            #line 6405 "PrintCLike.cpp"
  append(L"\n");
  append(L"  reduce = ");
                                                            #line 3906 "PrintCLike.cpp.template"
                                                                  print(staticPrefix());
                                                                  if (isGo())
                                                                  {
                                                            #line 6412 "PrintCLike.cpp"
  append(L"reduction");
                                                            #line 3909 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 6418 "PrintCLike.cpp"
  append(L"REDUCTION");
                                                            #line 3912 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(leftbracket());
                                                            #line 6423 "PrintCLike.cpp"
  append(L"reduce + 1");
                                                            #line 3914 "PrintCLike.cpp.template"
                                                                  print(rightbracket());
                                                                  print(semicolon());
                                                            #line 6428 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if ");
                                                            #line 3917 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                            #line 6433 "PrintCLike.cpp"
  append(L"reduce >= 0");
                                                            #line 3918 "PrintCLike.cpp.template"
                                                                  print(ifRightParen());
                                                                  increaseIndent();
                                                                  print(leftBrace());
                                                                  if (useGlr)
                                                                  {
                                                            #line 6441 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if ");
                                                            #line 3924 "PrintCLike.cpp.template"
                                                                    print(ifLeftParen());
                                                                    print(thiz());
                                                                    if (isGo())
                                                                    {
                                                            #line 6449 "PrintCLike.cpp"
  append(L"IsUnambiguous");
                                                            #line 3928 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 6455 "PrintCLike.cpp"
  append(L"isUnambiguous");
                                                            #line 3931 "PrintCLike.cpp.template"
                                                                    }
                                                                    if (! isScala()) print(L"()");
                                                                    print(ifRightParen());
                                                                    print(leftBrace());
                                                            #line 6462 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 3936 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                                    print(isGo() && useGlr ? L"E" : L"e");
                                                            #line 6468 "PrintCLike.cpp"
  append(L"xecute(reduce)");
                                                            #line 3938 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 6472 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3940 "PrintCLike.cpp.template"
                                                                    print(elseWithBraces());
                                                            #line 6477 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 3942 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 6482 "PrintCLike.cpp"
  append(L"deferredCode = ");
                                                            #line 3943 "PrintCLike.cpp.template"
                                                                    if (isGo())
                                                                    {
                                                            #line 6487 "PrintCLike.cpp"
  append(L"&DeferredCode{");
                                                            #line 3945 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                                      if (! isPython())
                                                                      {
                                                            #line 6495 "PrintCLike.cpp"
  append(L"new ");
                                                            #line 3950 "PrintCLike.cpp.template"
                                                                      }
                                                                      if (! isHaxe() && ! isTypescript()) print(staticPrefix());
                                                            #line 6500 "PrintCLike.cpp"
  append(L"DeferredCode(");
                                                            #line 3952 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(thiz());
                                                            #line 6505 "PrintCLike.cpp"
  append(L"deferredCode, reduce, ");
                                                            #line 3954 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 6509 "PrintCLike.cpp"
  append(L"b0, ");
                                                            #line 3955 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 6513 "PrintCLike.cpp"
  append(L"e0");
                                                            #line 3957 "PrintCLike.cpp.template"
                                                                    if (isGo())
                                                                    {
                                                            #line 6518 "PrintCLike.cpp"
  append(L"}");
                                                            #line 3960 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 6524 "PrintCLike.cpp"
  append(L")");
                                                            #line 3964 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(semicolon());
                                                                    increaseIndent();
                                                                    print(rightBrace());
                                                                    decreaseIndent();
                                                                  }
                                                                  else
                                                                  {
                                                            #line 6535 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3973 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                                    print(isGo() && useGlr ? L"E" : L"e");
                                                            #line 6541 "PrintCLike.cpp"
  append(L"xecute(reduce)");
                                                            #line 3975 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                  }
                                                                  print(rightBrace());
                                                                  decreaseIndent();
                                                                }
                                                                else
                                                                {
                                                            #line 6551 "PrintCLike.cpp"
  append(L"\n");
  append(L"  nonterminalId = reduce");
                                                            #line 3983 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                                if (resolvesAmbiguity)
                                                                {
                                                            #line 6559 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3988 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 6564 "PrintCLike.cpp"
  append(L"eventCount");
                                                            #line 3989 "PrintCLike.cpp.template"
                                                                  print(incrementOp());
                                                                  print(semicolon());
                                                                }
                                                                if (trace)
                                                                {
                                                            #line 6572 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if ");
                                                            #line 3995 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                            #line 6577 "PrintCLike.cpp"
  append(L"shift >= 0");
                                                            #line 3996 "PrintCLike.cpp.template"
                                                                  print(ifRightParen());
                                                                  printIndented(1, leftBrace());
                                                                  if (isCpp())
                                                                  {
                                                            #line 6584 "PrintCLike.cpp"
  append(L"\n");
  append(L"    fprintf(stderr, ");
                                                            #line 4001 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 6591 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4005 "PrintCLike.cpp.template"
                                                                    print(writeTrace());
                                                                  }
                                                            #line 6597 "PrintCLike.cpp"
  append(L"\" \"");
                                                            #line 4007 "PrintCLike.cpp.template"
                                                                  print(endWriteTrace());
                                                                  print(semicolon());
                                                                  increaseIndent();
                                                                  print(rightBrace());
                                                                  decreaseIndent();
                                                                  if (isCpp())
                                                                  {
                                                            #line 6607 "PrintCLike.cpp"
  append(L"\n");
  append(L"  fprintf(stderr, \"reduce\\\" nonterminal=\\\"%s\\\" count=\\\"%d\\\"/>\\n\", ");
                                                            #line 4015 "PrintCLike.cpp.template"
                                                                    if (stringIntroducer()[0])
                                                                    {
                                                            #line 6613 "PrintCLike.cpp"
  append(L"Utf8Encoder::encode(");
                                                            #line 4017 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 6617 "PrintCLike.cpp"
  append(L"xmlEscape(");
                                                            #line 4018 "PrintCLike.cpp.template"
                                                                    print(nonterminalTableName());
                                                            #line 6621 "PrintCLike.cpp"
  append(L"[nonterminalId], 0).c_str()");
                                                            #line 4019 "PrintCLike.cpp.template"
                                                                    if (stringIntroducer()[0])
                                                                    {
                                                            #line 6626 "PrintCLike.cpp"
  append(L").c_str()");
                                                            #line 4021 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 6630 "PrintCLike.cpp"
  append(L", symbols);");
                                                            #line 4022 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 6636 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4026 "PrintCLike.cpp.template"
                                                                    print(writeTrace());
                                                            #line 6641 "PrintCLike.cpp"
  append(L"\"reduce\\\" nonterminal=\\\"\" + ");
                                                            #line 4027 "PrintCLike.cpp.template"
                                                                    print(staticPrefix());
                                                            #line 6645 "PrintCLike.cpp"
  append(L"xmlEscape(");
                                                            #line 4028 "PrintCLike.cpp.template"
                                                                    print(staticPrefix());
                                                                    print(nonterminalTableName());
                                                                    print(leftbracket());
                                                            #line 6651 "PrintCLike.cpp"
  append(L"nonterminalId");
                                                            #line 4031 "PrintCLike.cpp.template"
                                                                    print(rightbracket());
                                                            #line 6655 "PrintCLike.cpp"
  append(L") + \"\\\" count=\\\"\" + ");
                                                            #line 4033 "PrintCLike.cpp.template"
                                                                    if (isPython())
                                                                    {
                                                            #line 6660 "PrintCLike.cpp"
  append(L"str(");
                                                            #line 4036 "PrintCLike.cpp.template"
                                                                    }
                                                                    else if (isGo())
                                                                    {
                                                            #line 6666 "PrintCLike.cpp"
  append(L"strconv.Itoa(");
                                                            #line 4040 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 6670 "PrintCLike.cpp"
  append(L"symbols");
                                                            #line 4042 "PrintCLike.cpp.template"
                                                                    if (isGo() || isPython())
                                                                    {
                                                            #line 6675 "PrintCLike.cpp"
  append(L")");
                                                            #line 4045 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 6679 "PrintCLike.cpp"
  append(L" + \"\\\"/>");
                                                            #line 4047 "PrintCLike.cpp.template"
                                                                    if (! isHaxe())
                                                                    {
                                                            #line 6684 "PrintCLike.cpp"
  append(L"\\n\"");
                                                            #line 4049 "PrintCLike.cpp.template"
                                                                      print(endWriteTrace());
                                                                      print(semicolon());
                                                                    }
                                                                    else
                                                                    {
                                                            #line 6692 "PrintCLike.cpp"
  append(L"\";\n");
  append(L"  trace(traceLine);");
                                                            #line 4055 "PrintCLike.cpp.template"
                                                                    }
                                                                  }
                                                                }
                                                                if (tree)
                                                                {
                                                            #line 6701 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if ");
                                                            #line 4061 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                                  print(thiz());
                                                            #line 6707 "PrintCLike.cpp"
  append(L"l1 == 0");
                                                            #line 4063 "PrintCLike.cpp.template"
                                                                  print(ifRightParen());
                                                                  printIndented(1, leftBrace());
                                                            #line 6712 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4066 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 6717 "PrintCLike.cpp"
  append(L"b1 = ");
                                                            #line 4067 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 6721 "PrintCLike.cpp"
  append(L"e0");
                                                            #line 4068 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                  increaseIndent();
                                                                  print(rightBrace());
                                                                  decreaseIndent();
                                                            #line 6728 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if ");
                                                            #line 4073 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                            #line 6733 "PrintCLike.cpp"
  append(L"symbols > 0");
                                                            #line 4074 "PrintCLike.cpp.template"
                                                                  print(ifRightParen());
                                                                  printIndented(1, leftBrace());
                                                                  if (useGlr)
                                                                  {
                                                                    printStackPop();
                                                                  }
                                                                  else
                                                                  {
                                                            #line 6744 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4083 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 6749 "PrintCLike.cpp"
  append(L"top -= symbols * 3");
                                                            #line 4084 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 6753 "PrintCLike.cpp"
  append(L"\n");
  append(L"    state = ");
                                                            #line 4086 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 6758 "PrintCLike.cpp"
  append(L"iStack");
                                                            #line 4087 "PrintCLike.cpp.template"
                                                                    print(leftbracket());
                                                                    print(thiz());
                                                            #line 6763 "PrintCLike.cpp"
  append(L"top + 2");
                                                            #line 4089 "PrintCLike.cpp.template"
                                                                    print(rightbracket());
                                                                    print(semicolon());
                                                            #line 6768 "PrintCLike.cpp"
  append(L"\n");
  append(L"    bs = ");
                                                            #line 4092 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 6773 "PrintCLike.cpp"
  append(L"iStack");
                                                            #line 4093 "PrintCLike.cpp.template"
                                                                    print(leftbracket());
                                                                    print(thiz());
                                                            #line 6778 "PrintCLike.cpp"
  append(L"top + 1");
                                                            #line 4095 "PrintCLike.cpp.template"
                                                                    print(rightbracket());
                                                                    print(semicolon());
                                                                  }
                                                            #line 6784 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4099 "PrintCLike.cpp.template"
                                                                  printIndented(1, elseWithBraces());
                                                            #line 6789 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4101 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 6794 "PrintCLike.cpp"
  append(L"bs = ");
                                                            #line 4102 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 6798 "PrintCLike.cpp"
  append(L"b1");
                                                            #line 4103 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                            #line 6802 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4105 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 6807 "PrintCLike.cpp"
  append(L"es = ");
                                                            #line 4106 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 6811 "PrintCLike.cpp"
  append(L"b1");
                                                            #line 4107 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                  increaseIndent();
                                                                  print(rightBrace());
                                                                  decreaseIndent();
                                                            #line 6818 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if ");
                                                            #line 4112 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                            #line 6823 "PrintCLike.cpp"
  append(L"nonterminalId == ");
                                                            #line 4113 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 6827 "PrintCLike.cpp"
  append(L"target ");
                                                            #line 4114 "PrintCLike.cpp.template"
                                                                  if (isPython())
                                                                  {
                                                            #line 6832 "PrintCLike.cpp"
  append(L"and");
                                                            #line 4116 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 6838 "PrintCLike.cpp"
  append(L"&&");
                                                            #line 4119 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 6842 "PrintCLike.cpp"
  append(L" ");
                                                            #line 4120 "PrintCLike.cpp.template"
                                                                  if (useGlr)
                                                                  {
                                                                    print(thiz());
                                                            #line 6848 "PrintCLike.cpp"
  append(L"stack");
                                                            #line 4123 "PrintCLike.cpp.template"
                                                                    print(arrow());
                                                            #line 6852 "PrintCLike.cpp"
  append(L"link == ");
                                                            #line 4124 "PrintCLike.cpp.template"
                                                                    print(nullPtr());
                                                                  }
                                                                  else
                                                                  {
                                                            #line 6859 "PrintCLike.cpp"
  append(L"t == ");
                                                            #line 4128 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 6863 "PrintCLike.cpp"
  append(L"top");
                                                            #line 4129 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(ifRightParen());
                                                                  printIndented(1, leftBrace());
                                                            #line 6869 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4133 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 6874 "PrintCLike.cpp"
  append(L"bs = ");
                                                            #line 4134 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 6878 "PrintCLike.cpp"
  append(L"bw");
                                                            #line 4135 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                            #line 6882 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4137 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 6887 "PrintCLike.cpp"
  append(L"es = ");
                                                            #line 4138 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 6891 "PrintCLike.cpp"
  append(L"b1");
                                                            #line 4139 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                            #line 6895 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4141 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 6900 "PrintCLike.cpp"
  append(L"bw = ");
                                                            #line 4142 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 6904 "PrintCLike.cpp"
  append(L"b1");
                                                            #line 4143 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                  increaseIndent();
                                                                  print(rightBrace());
                                                                  decreaseIndent();
                                                            #line 6911 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if ");
                                                            #line 4148 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                                  if (useGlr) print(thiz());
                                                            #line 6917 "PrintCLike.cpp"
  append(L"eventHandler != ");
                                                            #line 4150 "PrintCLike.cpp.template"
                                                                  print(nullPtr());
                                                                  if (shiftAmbiguity)
                                                                  {
                                                                    print(isPython() ? L" or not " : L" || ! ");
                                                                    print(thiz());
                                                                    print(isGo() ? L"IsUnambiguous" : L"isUnambiguous");
                                                                    if (! isScala()) print(L"()");
                                                                  }
                                                                  print(ifRightParen());
                                                                  printIndented(1, leftBrace());
                                                                  if (useGlr)
                                                                  {
                                                            #line 6932 "PrintCLike.cpp"
  append(L"\n");
  append(L"    if ");
                                                            #line 4163 "PrintCLike.cpp.template"
                                                                    print(ifLeftParen());
                                                                    print(thiz());
                                                                    if (isGo())
                                                                    {
                                                            #line 6940 "PrintCLike.cpp"
  append(L"IsUnambiguous");
                                                            #line 4167 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 6946 "PrintCLike.cpp"
  append(L"isUnambiguous");
                                                            #line 4170 "PrintCLike.cpp.template"
                                                                    }
                                                                    if (! isScala()) print(L"()");
                                                                    print(ifRightParen());
                                                                    printIndented(2, leftBrace());
                                                                    increaseIndent();
                                                                  }
                                                            #line 6955 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4177 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 6960 "PrintCLike.cpp"
  append(L"eventHandler");
                                                            #line 4178 "PrintCLike.cpp.template"
                                                                  if (shiftAmbiguity && isTypescript()) print(L"!");
                                                                  print(arrow());
                                                                  if (isGo())
                                                                  {
                                                            #line 6967 "PrintCLike.cpp"
  append(L"N");
                                                            #line 4182 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 6973 "PrintCLike.cpp"
  append(L"n");
                                                            #line 4185 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 6977 "PrintCLike.cpp"
  append(L"onterminal(nonterminalId, ");
                                                            #line 4186 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 6981 "PrintCLike.cpp"
  append(L"bs, ");
                                                            #line 4187 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 6985 "PrintCLike.cpp"
  append(L"es, symbols)");
                                                            #line 4188 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                  if (useGlr)
                                                                  {
                                                                    decreaseIndent();
                                                            #line 6992 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4193 "PrintCLike.cpp.template"
                                                                    printIndented(2, elseWithBraces());
                                                            #line 6997 "PrintCLike.cpp"
  append(L"\n");
  append(L"      ");
                                                            #line 4195 "PrintCLike.cpp.template"
                                                                    if (useGlr) print(thiz());
                                                            #line 7002 "PrintCLike.cpp"
  append(L"deferredEvent = ");
                                                            #line 4196 "PrintCLike.cpp.template"
                                                                    if (isGo())
                                                                    {
                                                            #line 7007 "PrintCLike.cpp"
  append(L"&NonterminalEvent{&AbstractDeferredEvent{this.deferredEvent, nonterminalId, this.bs, this.es}, symbols}");
                                                            #line 4199 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                                      if (! isPython())
                                                                      {
                                                            #line 7015 "PrintCLike.cpp"
  append(L"new ");
                                                            #line 4204 "PrintCLike.cpp.template"
                                                                      }
                                                                      if (! isHaxe() && ! isTypescript()) print(staticPrefix());
                                                                      if (isJavascript() || isTypescript())
                                                                      {
                                                            #line 7022 "PrintCLike.cpp"
  append(L"DeferredEvent");
                                                            #line 4208 "PrintCLike.cpp.template"
                                                                      }
                                                                      else
                                                                      {
                                                            #line 7028 "PrintCLike.cpp"
  append(L"NonterminalEvent");
                                                            #line 4211 "PrintCLike.cpp.template"
                                                                      }
                                                            #line 7032 "PrintCLike.cpp"
  append(L"(");
                                                            #line 4212 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 7036 "PrintCLike.cpp"
  append(L"deferredEvent, nonterminalId, ");
                                                            #line 4213 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 7040 "PrintCLike.cpp"
  append(L"bs, ");
                                                            #line 4214 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 7044 "PrintCLike.cpp"
  append(L"es, symbols)");
                                                            #line 4216 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                                    }
                                                                    increaseIndent(2);
                                                                    print(rightBrace());
                                                                    decreaseIndent(2);
                                                                  }
                                                                  increaseIndent();
                                                                  print(rightBrace());
                                                                  decreaseIndent();
                                                                }
                                                                else
                                                                {
                                                            #line 7059 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if ");
                                                            #line 4229 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                            #line 7064 "PrintCLike.cpp"
  append(L"symbols > 0");
                                                            #line 4230 "PrintCLike.cpp.template"
                                                                  print(ifRightParen());
                                                                  printIndented(1, leftBrace());
                                                                  if (useGlr)
                                                                  {
                                                                    printStackPop();
                                                                  }
                                                                  else
                                                                  {
                                                            #line 7075 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4239 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7080 "PrintCLike.cpp"
  append(L"top -= symbols << 1;\n");
  append(L"    state = ");
                                                            #line 4241 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7085 "PrintCLike.cpp"
  append(L"iStack");
                                                            #line 4242 "PrintCLike.cpp.template"
                                                                    print(leftbracket());
                                                                    print(thiz());
                                                            #line 7090 "PrintCLike.cpp"
  append(L"top + 1");
                                                            #line 4244 "PrintCLike.cpp.template"
                                                                    print(rightbracket());
                                                                    print(semicolon());
                                                                  }
                                                                  increaseIndent();
                                                                  print(rightBrace());
                                                                  decreaseIndent();
                                                                  if (useGlr && tree)
                                                                  {
                                                            #line 7101 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if ");
                                                            #line 4253 "PrintCLike.cpp.template"
                                                                    print(ifLeftParen());
                                                            #line 7106 "PrintCLike.cpp"
  append(L"nonterminalId == ");
                                                            #line 4254 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7110 "PrintCLike.cpp"
  append(L"target ");
                                                            #line 4255 "PrintCLike.cpp.template"
                                                                    if (isPython())
                                                                    {
                                                            #line 7115 "PrintCLike.cpp"
  append(L"and");
                                                            #line 4257 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 7121 "PrintCLike.cpp"
  append(L"&&");
                                                            #line 4260 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 7125 "PrintCLike.cpp"
  append(L" ");
                                                            #line 4261 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7129 "PrintCLike.cpp"
  append(L"stack");
                                                            #line 4262 "PrintCLike.cpp.template"
                                                                    print(arrow());
                                                            #line 7133 "PrintCLike.cpp"
  append(L"link == ");
                                                            #line 4263 "PrintCLike.cpp.template"
                                                                    print(nullPtr());
                                                                    print(ifRightParen());
                                                                    printIndented(1, leftBrace());
                                                            #line 7139 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4267 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7144 "PrintCLike.cpp"
  append(L"bs = ");
                                                            #line 4268 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7148 "PrintCLike.cpp"
  append(L"bw");
                                                            #line 4269 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 7152 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4271 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7157 "PrintCLike.cpp"
  append(L"bw = ");
                                                            #line 4272 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7161 "PrintCLike.cpp"
  append(L"b1");
                                                            #line 4273 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                    increaseIndent();
                                                                    print(rightBrace());
                                                                    decreaseIndent();
                                                                  }
                                                                }
                                                            #line 7170 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4280 "PrintCLike.cpp.template"
                                                                if (useGlr) print(thiz());
                                                            #line 7175 "PrintCLike.cpp"
  append(L"action = ");
                                                            #line 4281 "PrintCLike.cpp.template"
                                                                print(staticPrefix());
                                                                print(isGo() ? L"reduceAction" : L"goTo");
                                                            #line 7180 "PrintCLike.cpp"
  append(L"(nonterminalId, ");
                                                            #line 4283 "PrintCLike.cpp.template"
                                                                if (useGlr) print(thiz());
                                                            #line 7184 "PrintCLike.cpp"
  append(L"state)");
                                                            #line 4284 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                print(rightBrace());
                                                                decreaseIndent();
                                                                print(rightBrace());
                                                                decreaseIndent();
                                                                if (useGlr)
                                                                {
                                                                  if (isScala())
                                                                  {
                                                            #line 7196 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ERROR");
                                                            #line 4294 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isCpp())
                                                                  {
                                                            #line 7203 "PrintCLike.cpp"
  append(L"\n");
  append(L"  return PARSING;");
                                                            #line 4298 "PrintCLike.cpp.template"
                                                                  }
                                                                }
                                                                print(rightBrace());
                                                                if (isJavascript() && useGlr)
                                                                {
                                                            #line 7212 "PrintCLike.cpp"
  append(L";");
                                                            #line 4303 "PrintCLike.cpp.template"
                                                                }
                                                            #line 7216 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4305 "PrintCLike.cpp.template"
                                                                if ((tree || hasCustomCode) && useGlr)
                                                                {
                                                                  openMethod(boolType(), L"", L"isUnambiguous", L"", false, L"ParsingThread");
                                                                  print(leftBrace());
                                                            #line 7223 "PrintCLike.cpp"
  append(L"\n");
  append(L"  return ");
                                                            #line 4310 "PrintCLike.cpp.template"
                                                                  if (isPython())
                                                                  {
                                                            #line 7229 "PrintCLike.cpp"
  append(L"len(self.threads) == 0");
                                                            #line 4312 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                                    print(thiz());
                                                            #line 7236 "PrintCLike.cpp"
  append(L"threads");
                                                            #line 4316 "PrintCLike.cpp.template"
                                                                    print(arrow());
                                                                    if (isCpp())
                                                                    {
                                                            #line 7242 "PrintCLike.cpp"
  append(L"empty();");
                                                            #line 4319 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 7248 "PrintCLike.cpp"
  append(L"isEmpty");
                                                            #line 4322 "PrintCLike.cpp.template"
                                                                      if (! isScala()) print(L"()");
                                                                      print(semicolon());
                                                                    }
                                                                  }
                                                                  print(rightBrace());
                                                            #line 7256 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4328 "PrintCLike.cpp.template"
                                                                }
                                                                if (hasCustomCode)
                                                                {
                                                                  if (useGlr)
                                                                  {
                                                                    if (isJavascript())
                                                                    {
                                                            #line 7266 "PrintCLike.cpp"
  append(L"\n");
  append(L"this.executeDeferredCode = function()\n");
                                                            #line 4337 "PrintCLike.cpp.template"
                                                                    }
                                                                    else if (isTypescript())
                                                                    {
                                                            #line 7273 "PrintCLike.cpp"
  append(L"\n");
  append(L"executeDeferredCode()\n");
                                                            #line 4342 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                                      openMethod(voidType(), L"", L"executeDeferredCode", L"", false, L"ParsingThread");
                                                                    }
                                                                    print(leftBrace());
                                                                    increaseIndent();
                                                            #line 7284 "PrintCLike.cpp"
  append(L"\n");
  append(L"if ");
                                                            #line 4350 "PrintCLike.cpp.template"
                                                                    print(ifLeftParen());
                                                                    print(thiz());
                                                            #line 7290 "PrintCLike.cpp"
  append(L"deferredCode != ");
                                                            #line 4352 "PrintCLike.cpp.template"
                                                                    print(nullPtr());
                                                                    print(ifRightParen());
                                                                    print(leftBrace());
                                                                    increaseIndent();
                                                            #line 7297 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4357 "PrintCLike.cpp.template"
                                                                    if (isJavascript() || isHaxe() || isScala() || isTypescript())
                                                                    {
                                                            #line 7302 "PrintCLike.cpp"
  append(L"var ");
                                                            #line 4359 "PrintCLike.cpp.template"
                                                                    }
                                                                    else if (! isGo() && ! isPython())
                                                                    {
                                                            #line 7308 "PrintCLike.cpp"
  append(L"DeferredCode ");
                                                            #line 4362 "PrintCLike.cpp.template"
                                                                    }
                                                                    if (isCpp()) print(L"*");
                                                            #line 7313 "PrintCLike.cpp"
  append(L"predecessor");
                                                            #line 4364 "PrintCLike.cpp.template"
                                                                    print(assign());
                                                                    print(thiz());
                                                            #line 7318 "PrintCLike.cpp"
  append(L"deferredCode");
                                                            #line 4366 "PrintCLike.cpp.template"
                                                                    print(arrow());
                                                            #line 7322 "PrintCLike.cpp"
  append(L"link");
                                                            #line 4367 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 7326 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4369 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7330 "PrintCLike.cpp"
  append(L"deferredCode");
                                                            #line 4370 "PrintCLike.cpp.template"
                                                                    print(arrow());
                                                            #line 7334 "PrintCLike.cpp"
  append(L"link = ");
                                                            #line 4371 "PrintCLike.cpp.template"
                                                                    print(nullPtr());
                                                                    print(semicolon());
                                                                    if (isGo())
                                                                    {
                                                            #line 7341 "PrintCLike.cpp"
  append(L"\n");
  append(L"for ");
                                                            #line 4376 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 7348 "PrintCLike.cpp"
  append(L"\n");
  append(L"while ");
                                                            #line 4380 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(ifLeftParen());
                                                            #line 7354 "PrintCLike.cpp"
  append(L"predecessor != ");
                                                            #line 4382 "PrintCLike.cpp.template"
                                                                    print(nullPtr());
                                                                    print(ifRightParen());
                                                                    print(leftBrace());
                                                            #line 7360 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4386 "PrintCLike.cpp.template"
                                                                    if (isJavascript() || isHaxe() || isScala() || isTypescript())
                                                                    {
                                                            #line 7366 "PrintCLike.cpp"
  append(L"var ");
                                                            #line 4388 "PrintCLike.cpp.template"
                                                                    }
                                                                    else if (! isGo() && ! isPython())
                                                                    {
                                                            #line 7372 "PrintCLike.cpp"
  append(L"DeferredCode ");
                                                            #line 4391 "PrintCLike.cpp.template"
                                                                    }
                                                                    if (isCpp()) print(L"*");
                                                            #line 7377 "PrintCLike.cpp"
  append(L"nextCode");
                                                            #line 4393 "PrintCLike.cpp.template"
                                                                    print(assign());
                                                            #line 7381 "PrintCLike.cpp"
  append(L"predecessor");
                                                            #line 4394 "PrintCLike.cpp.template"
                                                                    print(arrow());
                                                            #line 7385 "PrintCLike.cpp"
  append(L"link");
                                                            #line 4395 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 7389 "PrintCLike.cpp"
  append(L"\n");
  append(L"  predecessor");
                                                            #line 4397 "PrintCLike.cpp.template"
                                                                    print(arrow());
                                                            #line 7394 "PrintCLike.cpp"
  append(L"link = ");
                                                            #line 4398 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7398 "PrintCLike.cpp"
  append(L"deferredCode");
                                                            #line 4399 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 7402 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4401 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7407 "PrintCLike.cpp"
  append(L"deferredCode = predecessor");
                                                            #line 4402 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 7411 "PrintCLike.cpp"
  append(L"\n");
  append(L"  predecessor = nextCode");
                                                            #line 4404 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                    print(rightBrace());
                                                            #line 7417 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4407 "PrintCLike.cpp.template"
                                                                    print(intVar());
                                                            #line 7421 "PrintCLike.cpp"
  append(L"b0t");
                                                            #line 4408 "PrintCLike.cpp.template"
                                                                    print(assign());
                                                                    print(thiz());
                                                            #line 7426 "PrintCLike.cpp"
  append(L"b0");
                                                            #line 4410 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 7430 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4412 "PrintCLike.cpp.template"
                                                                    print(intVar());
                                                            #line 7434 "PrintCLike.cpp"
  append(L"e0t");
                                                            #line 4413 "PrintCLike.cpp.template"
                                                                    print(assign());
                                                                    print(thiz());
                                                            #line 7439 "PrintCLike.cpp"
  append(L"e0");
                                                            #line 4415 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                    if (isGo())
                                                                    {
                                                            #line 7445 "PrintCLike.cpp"
  append(L"\n");
  append(L"for ");
                                                            #line 4419 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 7452 "PrintCLike.cpp"
  append(L"\n");
  append(L"while ");
                                                            #line 4423 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(ifLeftParen());
                                                                    print(thiz());
                                                            #line 7459 "PrintCLike.cpp"
  append(L"deferredCode != ");
                                                            #line 4426 "PrintCLike.cpp.template"
                                                                    print(nullPtr());
                                                                    print(ifRightParen());
                                                                    print(leftBrace());
                                                            #line 7465 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4430 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7470 "PrintCLike.cpp"
  append(L"b0 = ");
                                                            #line 4431 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7474 "PrintCLike.cpp"
  append(L"deferredCode");
                                                            #line 4432 "PrintCLike.cpp.template"
                                                                    print(arrow());
                                                            #line 7478 "PrintCLike.cpp"
  append(L"b0");
                                                            #line 4433 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 7482 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4435 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7487 "PrintCLike.cpp"
  append(L"e0 = ");
                                                            #line 4436 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7491 "PrintCLike.cpp"
  append(L"deferredCode");
                                                            #line 4437 "PrintCLike.cpp.template"
                                                                    print(arrow());
                                                            #line 7495 "PrintCLike.cpp"
  append(L"e0");
                                                            #line 4438 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 7499 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4440 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                                    print(isGo() ? L"E" : L"e");
                                                            #line 7505 "PrintCLike.cpp"
  append(L"xecute(");
                                                            #line 4442 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7509 "PrintCLike.cpp"
  append(L"deferredCode");
                                                            #line 4443 "PrintCLike.cpp.template"
                                                                    print(arrow());
                                                            #line 7513 "PrintCLike.cpp"
  append(L"codeId)");
                                                            #line 4444 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                    if (isCpp())
                                                                    {
                                                            #line 7519 "PrintCLike.cpp"
  append(L"\n");
  append(L"  DeferredCode *next = deferredCode->link;\n");
  append(L"  delete deferredCode;\n");
  append(L"  deferredCode = next;");
                                                            #line 4450 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 7528 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4454 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 7533 "PrintCLike.cpp"
  append(L"deferredCode = ");
                                                            #line 4455 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 7537 "PrintCLike.cpp"
  append(L"deferredCode");
                                                            #line 4456 "PrintCLike.cpp.template"
                                                                      print(arrow());
                                                            #line 7541 "PrintCLike.cpp"
  append(L"link");
                                                            #line 4457 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                                    }
                                                                    print(rightBrace());
                                                            #line 7547 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4461 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7551 "PrintCLike.cpp"
  append(L"b0 = b0t");
                                                            #line 4462 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 7555 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4464 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7559 "PrintCLike.cpp"
  append(L"e0 = e0t");
                                                            #line 4465 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                    decreaseIndent();
                                                                    print(rightBrace());
                                                                    decreaseIndent();
                                                                    print(rightBrace());
                                                            #line 7567 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4471 "PrintCLike.cpp.template"
                                                                  }
                                                                  openMethod(voidType(), L"", L"execute", L"int reduce", false, useGlr ? L"ParsingThread" : className.c_str());
                                                                  print(leftBrace());
                                                                  increaseIndent();
                                                                  if (! isPython())
                                                                  {
                                                            #line 7576 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4478 "PrintCLike.cpp.template"
                                                                    if (! isScala())
                                                                    {
                                                            #line 7581 "PrintCLike.cpp"
  append(L"switch ");
                                                            #line 4480 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(ifLeftParen());
                                                            #line 7586 "PrintCLike.cpp"
  append(L"reduce");
                                                            #line 4482 "PrintCLike.cpp.template"
                                                                    print(ifRightParen());
                                                                    if (isScala())
                                                                    {
                                                            #line 7592 "PrintCLike.cpp"
  append(L" match");
                                                            #line 4485 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(leftBrace());
                                                                  }
                                                                  int lastContentId = grammar->distinctCodeAnnotations.size() - 1;
                                                                  for (int contentId = 0; contentId <= lastContentId; ++contentId)
                                                                  {
                                                                    ProcessingInstruction *p = grammar->distinctCodeAnnotations[contentId];
                                                                    if (! isPython())
                                                                    {
                                                            #line 7604 "PrintCLike.cpp"
  append(L"\n");
  append(L"case ");
                                                            #line 4495 "PrintCLike.cpp.template"
                                                                    }
                                                                    else if (contentId == 0)
                                                                    {
                                                            #line 7611 "PrintCLike.cpp"
  append(L"\n");
  append(L"if reduce == ");
                                                            #line 4499 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 7618 "PrintCLike.cpp"
  append(L"\n");
  append(L"elif reduce == ");
                                                            #line 4503 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(format.toString<wchar_t>(contentId));
                                                                    print(caseIntroducer());
                                                                    increaseIndent();
                                                                    print(leftBrace());
                                                                    visitProcessingInstruction(p);
                                                                    print(rightBrace());
                                                                    if (! isScala() && ! isHaxe() && ! isGo() && ! isPython())
                                                                    {
                                                            #line 7631 "PrintCLike.cpp"
  append(L"\n");
  append(L"break");
                                                            #line 4513 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                                    }
                                                                    decreaseIndent();
                                                                  }
                                                                  if (isScala())
                                                                  {
                                                            #line 7641 "PrintCLike.cpp"
  append(L"\n");
  append(L"case _");
                                                            #line 4520 "PrintCLike.cpp.template"
                                                                    print(caseIntroducer());
                                                                  }
                                                                  else if (! isPython())
                                                                  {
                                                            #line 7649 "PrintCLike.cpp"
  append(L"\n");
  append(L"default");
                                                            #line 4525 "PrintCLike.cpp.template"
                                                                    print(caseIntroducer());
                                                                  }
                                                                  if (! isScala() && ! isHaxe() && ! isGo() && ! isPython())
                                                                  {
                                                            #line 7657 "PrintCLike.cpp"
  append(L"\n");
  append(L"  break");
                                                            #line 4530 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                  }
                                                                  print(rightBrace());
                                                                  decreaseIndent();
                                                                  print(rightBrace());
                                                            #line 7666 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4536 "PrintCLike.cpp.template"
                                                                }
                                                                if (! isGo())
                                                                  decreaseIndent();
                                                              }

                                                              if (useGlr)
                                                              {
                                                                beginPublic();
                                                                printInitializer();
                                                                if (! isCpp())
                                                                  beginNonpublic();
                                                              }

                                                              WString name;
                                                              for (int i = 0; i < consumeMethods; ++i)
                                                              {
                                                                if (! isGo())
                                                                  increaseIndent();
                                                                name = L"consume";
                                                                if (i == 1) name += L"T";
                                                                openMethod(voidType(), L"", name.c_str(), L"int t", false, useGlr ? L"ParsingThread" : className.c_str());
                                                                print(leftBrace());
                                                                increaseIndent();
                                                            #line 7692 "PrintCLike.cpp"
  append(L"\n");
  append(L"if ");
                                                            #line 4560 "PrintCLike.cpp.template"
                                                                print(ifLeftParen());
                                                                print(thiz());
                                                            #line 7698 "PrintCLike.cpp"
  append(L"l1 == t");
                                                            #line 4562 "PrintCLike.cpp.template"
                                                                print(ifRightParen());
                                                                print(leftBrace());
                                                                increaseIndent();
                                                                if (tree && i == 0 && ! isLrParser)
                                                                {
                                                                  if (anyWhitespace && ! isLrParser)
                                                                  {
                                                            #line 7708 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4570 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7712 "PrintCLike.cpp"
  append(L"whitespace");
                                                            #line 4571 "PrintCLike.cpp.template"
                                                                    print(isScala() ? L"" : L"()");
                                                                    print(semicolon());
                                                                  }
                                                            #line 7718 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4575 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 7722 "PrintCLike.cpp"
  append(L"eventHandler");
                                                            #line 4576 "PrintCLike.cpp.template"
                                                                  if (shiftAmbiguity && isTypescript()) print(L"!");
                                                                  print(arrow());
                                                                  if (isGo())
                                                                  {
                                                            #line 7729 "PrintCLike.cpp"
  append(L"T");
                                                            #line 4580 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 7735 "PrintCLike.cpp"
  append(L"t");
                                                            #line 4583 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 7739 "PrintCLike.cpp"
  append(L"erminal(");
                                                            #line 4584 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 7743 "PrintCLike.cpp"
  append(L"l1, ");
                                                            #line 4585 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 7747 "PrintCLike.cpp"
  append(L"b1, ");
                                                            #line 4586 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 7751 "PrintCLike.cpp"
  append(L"e1)");
                                                            #line 4587 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                            #line 7756 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4590 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 7760 "PrintCLike.cpp"
  append(L"b0 = ");
                                                            #line 4591 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 7764 "PrintCLike.cpp"
  append(L"b1; ");
                                                            #line 4592 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 7768 "PrintCLike.cpp"
  append(L"e0 = ");
                                                            #line 4593 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 7772 "PrintCLike.cpp"
  append(L"e1;");
                                                            #line 4594 "PrintCLike.cpp.template"
                                                                for (size_t k = 1; k < grammar->k; ++k)
                                                                {
                                                            #line 7777 "PrintCLike.cpp"
  append(L" ");
                                                            #line 4596 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 7781 "PrintCLike.cpp"
  append(L"l");
                                                            #line 4597 "PrintCLike.cpp.template"
                                                                  print(format.toString<wchar_t>(k));
                                                            #line 7785 "PrintCLike.cpp"
  append(L" = ");
                                                            #line 4598 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 7789 "PrintCLike.cpp"
  append(L"l");
                                                            #line 4599 "PrintCLike.cpp.template"
                                                                  print(format.toString<wchar_t>(k + 1));
                                                                  print(isPython() ? L"\n" : L"; ");
                                                            #line 7794 "PrintCLike.cpp"
  append(L"if ");
                                                            #line 4601 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                                  print(thiz());
                                                            #line 7799 "PrintCLike.cpp"
  append(L"l");
                                                            #line 4603 "PrintCLike.cpp.template"
                                                                  print(format.toString<wchar_t>(k));
                                                            #line 7803 "PrintCLike.cpp"
  append(L" != 0");
                                                            #line 4604 "PrintCLike.cpp.template"
                                                                  print(ifRightParen());
                                                                  if (isPython())
                                                                  {
                                                                    increaseIndent();
                                                                  }
                                                                  else
                                                                  {
                                                            #line 7813 "PrintCLike.cpp"
  append(L" {");
                                                            #line 4611 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 7817 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4613 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 7821 "PrintCLike.cpp"
  append(L"b");
                                                            #line 4614 "PrintCLike.cpp.template"
                                                                  print(format.toString<wchar_t>(k));
                                                            #line 7825 "PrintCLike.cpp"
  append(L" = ");
                                                            #line 4615 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 7829 "PrintCLike.cpp"
  append(L"b");
                                                            #line 4616 "PrintCLike.cpp.template"
                                                                  print(format.toString<wchar_t>(k + 1));
                                                            #line 7833 "PrintCLike.cpp"
  append(L"; ");
                                                            #line 4617 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 7837 "PrintCLike.cpp"
  append(L"e");
                                                            #line 4618 "PrintCLike.cpp.template"
                                                                  print(format.toString<wchar_t>(k));
                                                            #line 7841 "PrintCLike.cpp"
  append(L" = ");
                                                            #line 4619 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 7845 "PrintCLike.cpp"
  append(L"e");
                                                            #line 4620 "PrintCLike.cpp.template"
                                                                  print(format.toString<wchar_t>(k + 1));
                                                            #line 7849 "PrintCLike.cpp"
  append(L";");
                                                            #line 4621 "PrintCLike.cpp.template"
                                                                }
                                                            #line 7853 "PrintCLike.cpp"
  append(L" ");
                                                            #line 4622 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 7857 "PrintCLike.cpp"
  append(L"l");
                                                            #line 4623 "PrintCLike.cpp.template"
                                                                print(format.toString<wchar_t>(grammar->k));
                                                            #line 7861 "PrintCLike.cpp"
  append(L" = 0");
                                                            #line 4624 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                if (grammar->k > 1)
                                                                {
                                                            #line 7867 "PrintCLike.cpp"
  append(L" ");
                                                            #line 4627 "PrintCLike.cpp.template"
                                                                  for (size_t k = 1; k < grammar->k; ++k)
                                                                  {
                                                                    if (! isPython())
                                                                    {
                                                            #line 7874 "PrintCLike.cpp"
  append(L"}");
                                                            #line 4631 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                                      decreaseIndent();
                                                                    }
                                                                  }
                                                                }
                                                                decreaseIndent();
                                                                if (trace && ! isLrParser)
                                                                {
                                                                  if (isCpp())
                                                                  {
                                                            #line 7889 "PrintCLike.cpp"
  append(L"\n");
  append(L"  fprintf(stderr, \"  <parse terminal=\\\"%s\\\"%s%s%s/>\\n\", ");
                                                            #line 4644 "PrintCLike.cpp.template"
                                                                    if (stringIntroducer()[0])
                                                                    {
                                                            #line 7895 "PrintCLike.cpp"
  append(L"Utf8Encoder::encode(");
                                                            #line 4647 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 7899 "PrintCLike.cpp"
  append(L"xmlEscape(TOKEN[t], 0).c_str()");
                                                            #line 4649 "PrintCLike.cpp.template"
                                                                    if (stringIntroducer()[0])
                                                                    {
                                                            #line 7904 "PrintCLike.cpp"
  append(L").c_str()");
                                                            #line 4651 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 7908 "PrintCLike.cpp"
  append(L", (l1 == 0 ? \"\" : \" input=\\\"\"),  (l1 == 0 ? \"\" : ");
                                                            #line 4653 "PrintCLike.cpp.template"
                                                                    if (stringIntroducer()[0])
                                                                    {
                                                            #line 7913 "PrintCLike.cpp"
  append(L"Utf8Encoder::encode(");
                                                            #line 4656 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 7917 "PrintCLike.cpp"
  append(L"xmlEscape(lookaheadString().c_str(), 0).c_str()");
                                                            #line 4658 "PrintCLike.cpp.template"
                                                                    if (stringIntroducer()[0])
                                                                    {
                                                            #line 7922 "PrintCLike.cpp"
  append(L").c_str()");
                                                            #line 4660 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 7926 "PrintCLike.cpp"
  append(L"), (l1 == 0 ? \"\" : \"\\\"\"));");
                                                            #line 4662 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                                    if (isGo())
                                                                    {
                                                            #line 7934 "PrintCLike.cpp"
  append(L"\n");
  append(L"  var inputAttr string\n");
  append(L"  if (this.l1 == 0) {\n");
  append(L"    inputAttr = \"\"\n");
  append(L"  } else {\n");
  append(L"    inputAttr = \" input=\\\"\" + xmlEscape(this.lookaheadString()) + \"\\\"\"\n");
  append(L"  }");
                                                            #line 4673 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 7944 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4675 "PrintCLike.cpp.template"
                                                                    if (isHaxe())
                                                                    {
                                                            #line 7950 "PrintCLike.cpp"
  append(L"trace(");
                                                            #line 4677 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                                      print(writeTrace());
                                                                    }
                                                            #line 7958 "PrintCLike.cpp"
  append(L"\"  <parse terminal=\\\"\" + ");
                                                            #line 4682 "PrintCLike.cpp.template"
                                                                    print(staticPrefix());
                                                            #line 7962 "PrintCLike.cpp"
  append(L"xmlEscape(");
                                                            #line 4683 "PrintCLike.cpp.template"
                                                                    print(staticPrefix());
                                                                    print(tokenTableName());
                                                                    print(leftbracket());
                                                            #line 7968 "PrintCLike.cpp"
  append(L"t");
                                                            #line 4686 "PrintCLike.cpp.template"
                                                                    print(rightbracket());
                                                            #line 7972 "PrintCLike.cpp"
  append(L") + \"\\\"\" + ");
                                                            #line 4687 "PrintCLike.cpp.template"
                                                                    if (isGo())
                                                                    {
                                                            #line 7977 "PrintCLike.cpp"
  append(L"inputAttr");
                                                            #line 4689 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 7983 "PrintCLike.cpp"
  append(L"(");
                                                            #line 4692 "PrintCLike.cpp.template"
                                                                      if (isScala())
                                                                      {
                                                            #line 7988 "PrintCLike.cpp"
  append(L"if (l1 == 0) \"\" else");
                                                            #line 4694 "PrintCLike.cpp.template"
                                                                      }
                                                                      else if (isPython())
                                                                      {
                                                            #line 7994 "PrintCLike.cpp"
  append(L"\"\" if self.l1 == 0 else");
                                                            #line 4697 "PrintCLike.cpp.template"
                                                                      }
                                                                      else
                                                                      {
                                                                        print(thiz());
                                                            #line 8001 "PrintCLike.cpp"
  append(L"l1 == 0 ? \"\" :");
                                                            #line 4701 "PrintCLike.cpp.template"
                                                                      }
                                                            #line 8005 "PrintCLike.cpp"
  append(L" \" input=\\\"\" + ");
                                                            #line 4702 "PrintCLike.cpp.template"
                                                                      print(staticPrefix());
                                                            #line 8009 "PrintCLike.cpp"
  append(L"xmlEscape(");
                                                            #line 4703 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 8013 "PrintCLike.cpp"
  append(L"lookaheadString");
                                                            #line 4704 "PrintCLike.cpp.template"
                                                                      if (! isScala()) print(L"()");
                                                            #line 8017 "PrintCLike.cpp"
  append(L") + \"\\\"\")");
                                                            #line 4705 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 8021 "PrintCLike.cpp"
  append(L" + \"/>");
                                                            #line 4706 "PrintCLike.cpp.template"
                                                                    if (isHaxe())
                                                                    {
                                                            #line 8026 "PrintCLike.cpp"
  append(L"\")");
                                                            #line 4708 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 8032 "PrintCLike.cpp"
  append(L"\\n\"");
                                                            #line 4711 "PrintCLike.cpp.template"
                                                                      print(endWriteTrace());
                                                                    }
                                                                    print(semicolon());
                                                                  }
                                                                }
                                                                print(rightBrace());
                                                                if (hasBacktracking)
                                                                {
                                                                  if (grammar->noThrow)
                                                                  {
                                                                    print(isGo() ? L" " : L"\n");
                                                            #line 8046 "PrintCLike.cpp"
  append(L"el");
                                                            #line 4722 "PrintCLike.cpp.template"
                                                                    if (! isPython())
                                                                    {
                                                            #line 8051 "PrintCLike.cpp"
  append(L"se ");
                                                            #line 4724 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 8055 "PrintCLike.cpp"
  append(L"if ");
                                                            #line 4725 "PrintCLike.cpp.template"
                                                                    print(ifLeftParen());
                                                                    print(thiz());
                                                                    print(token());
                                                            #line 8061 "PrintCLike.cpp"
  append(L" < 0");
                                                            #line 4728 "PrintCLike.cpp.template"
                                                                    print(ifRightParen());
                                                                    print(leftBrace());
                                                            #line 8066 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4731 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8071 "PrintCLike.cpp"
  append(L"error(");
                                                            #line 4732 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8075 "PrintCLike.cpp"
  append(L"b1, ");
                                                            #line 4733 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8079 "PrintCLike.cpp"
  append(L"e1, -");
                                                            #line 4734 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8083 "PrintCLike.cpp"
  append(L"l1, 0, 0)");
                                                            #line 4735 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                    if (i == 0)
                                                                    {
                                                            #line 8089 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4739 "PrintCLike.cpp.template"
                                                                      print(beginThrowStmt());
                                                                      print(thiz());
                                                            #line 8095 "PrintCLike.cpp"
  append(L"bx, ");
                                                            #line 4741 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 8099 "PrintCLike.cpp"
  append(L"ex, ");
                                                            #line 4742 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 8103 "PrintCLike.cpp"
  append(L"sx, ");
                                                            #line 4743 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 8107 "PrintCLike.cpp"
  append(L"lx, ");
                                                            #line 4744 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 8111 "PrintCLike.cpp"
  append(L"tx");
                                                            #line 4745 "PrintCLike.cpp.template"
                                                                      print(endThrowStmt());
                                                                      print(semicolon());
                                                                    }
                                                                    print(rightBrace());
                                                                  }
                                                                  print(isGo() ? L" " : L"\n");
                                                            #line 8120 "PrintCLike.cpp"
  append(L"else");
                                                            #line 4751 "PrintCLike.cpp.template"
                                                                  if (isPython()) print(L":");
                                                                  print(leftBrace());
                                                            #line 8125 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4754 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8130 "PrintCLike.cpp"
  append(L"error(");
                                                            #line 4755 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8134 "PrintCLike.cpp"
  append(L"b1, ");
                                                            #line 4756 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8138 "PrintCLike.cpp"
  append(L"e1, 0, ");
                                                            #line 4757 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8142 "PrintCLike.cpp"
  append(L"l1, t)");
                                                            #line 4758 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                  if (i == 0 && grammar->noThrow)
                                                                  {
                                                            #line 8148 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4762 "PrintCLike.cpp.template"
                                                                    print(beginThrowStmt());
                                                                    print(thiz());
                                                            #line 8154 "PrintCLike.cpp"
  append(L"bx, ");
                                                            #line 4764 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8158 "PrintCLike.cpp"
  append(L"ex, ");
                                                            #line 4765 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8162 "PrintCLike.cpp"
  append(L"sx, ");
                                                            #line 4766 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8166 "PrintCLike.cpp"
  append(L"lx, ");
                                                            #line 4767 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8170 "PrintCLike.cpp"
  append(L"tx");
                                                            #line 4768 "PrintCLike.cpp.template"
                                                                    print(endThrowStmt());
                                                                    print(semicolon());
                                                                  }
                                                                  print(rightBrace());
                                                                }
                                                                else
                                                                {
                                                                  print(isGo() ? L" " : L"\n");
                                                            #line 8181 "PrintCLike.cpp"
  append(L"else");
                                                            #line 4776 "PrintCLike.cpp.template"
                                                                  if (isPython()) print(L":");
                                                                  print(leftBrace());
                                                            #line 8186 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4779 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8191 "PrintCLike.cpp"
  append(L"error(");
                                                            #line 4780 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8195 "PrintCLike.cpp"
  append(L"b1, ");
                                                            #line 4781 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8199 "PrintCLike.cpp"
  append(L"e1, 0, ");
                                                            #line 4782 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8203 "PrintCLike.cpp"
  append(L"l1, t)");
                                                            #line 4783 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                  print(rightBrace());
                                                                }
                                                                decreaseIndent();
                                                                print(rightBrace());
                                                            #line 8211 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4789 "PrintCLike.cpp.template"
                                                                if (! isGo())
                                                                  decreaseIndent();
                                                              }

                                                              if (anyWhitespace)
                                                              {
                                                                if (complexWhitespace)
                                                                {
                                                                  if (! isGo())
                                                                    increaseIndent();
                                                                  openMethod (voidType(), L"", L"skip", L"int code", false, useGlr ? L"ParsingThread" : className.c_str());
                                                                  print(leftBrace());
                                                                  if (useGlr)
                                                                  {
                                                                    if (isJavascript())
                                                                    {
                                                            #line 8230 "PrintCLike.cpp"
  append(L"\n");
  append(L"  var thread = new ParsingThread().copy(thisThread, 0);\n");
  append(L"  thread.setL1(code);\n");
  append(L"  thread.setB1(begin);\n");
  append(L"  thread.setE1(end);");
                                                            #line 4809 "PrintCLike.cpp.template"
                                                                    }
                                                                    else if (isGo())
                                                                    {
                                                            #line 8240 "PrintCLike.cpp"
  append(L"\n");
  append(L"  thread := new(ParsingThread).copy(this, 0)\n");
  append(L"  thread.l1 = code\n");
  append(L"  thread.b1 = this.begin\n");
  append(L"  thread.e1 = this.end");
                                                            #line 4816 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 8250 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4820 "PrintCLike.cpp.template"
                                                                      if (isHaxe() || isScala() || isTypescript())
                                                                      {
                                                            #line 8256 "PrintCLike.cpp"
  append(L"var ");
                                                            #line 4822 "PrintCLike.cpp.template"
                                                                      }
                                                                      else if (! isPython())
                                                                      {
                                                            #line 8262 "PrintCLike.cpp"
  append(L"ParsingThread ");
                                                            #line 4825 "PrintCLike.cpp.template"
                                                                      }
                                                                      if (isCpp()) print(L"*");
                                                            #line 8267 "PrintCLike.cpp"
  append(L"thread = ");
                                                            #line 4827 "PrintCLike.cpp.template"
                                                                      if (isCpp()) print(L"(");
                                                                      if (! isPython())
                                                                      {
                                                            #line 8273 "PrintCLike.cpp"
  append(L"new ");
                                                            #line 4830 "PrintCLike.cpp.template"
                                                                      }
                                                                      if (isScala() || isPython())
                                                                      {
                                                                        print(className.c_str());
                                                            #line 8280 "PrintCLike.cpp"
  append(L".");
                                                            #line 4834 "PrintCLike.cpp.template"
                                                                      }
                                                            #line 8284 "PrintCLike.cpp"
  append(L"ParsingThread()");
                                                            #line 4835 "PrintCLike.cpp.template"
                                                                      if (isCpp()) print(L")");
                                                                      print(arrow());
                                                            #line 8289 "PrintCLike.cpp"
  append(L"copy(");
                                                            #line 4837 "PrintCLike.cpp.template"
                                                                      if (isPython())
                                                                      {
                                                            #line 8294 "PrintCLike.cpp"
  append(L"self");
                                                            #line 4839 "PrintCLike.cpp.template"
                                                                      }
                                                                      else
                                                                      {
                                                            #line 8300 "PrintCLike.cpp"
  append(L"this");
                                                            #line 4842 "PrintCLike.cpp.template"
                                                                      }
                                                            #line 8304 "PrintCLike.cpp"
  append(L", 0)");
                                                            #line 4843 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                                      if (isCpp())
                                                                      {
                                                            #line 8310 "PrintCLike.cpp"
  append(L"\n");
  append(L"  thread->stack->unshare();\n");
  append(L"  thread->stack = 0;");
                                                            #line 4848 "PrintCLike.cpp.template"
                                                                      }
                                                            #line 8316 "PrintCLike.cpp"
  append(L"\n");
  append(L"  thread");
                                                            #line 4850 "PrintCLike.cpp.template"
                                                                      print(arrow());
                                                            #line 8321 "PrintCLike.cpp"
  append(L"l1 = code");
                                                            #line 4851 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                            #line 8325 "PrintCLike.cpp"
  append(L"\n");
  append(L"  thread");
                                                            #line 4853 "PrintCLike.cpp.template"
                                                                      print(arrow());
                                                            #line 8330 "PrintCLike.cpp"
  append(L"b1 = ");
                                                            #line 4854 "PrintCLike.cpp.template"
                                                                      if (useGlr) print(thiz());
                                                            #line 8334 "PrintCLike.cpp"
  append(L"begin");
                                                            #line 4855 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                            #line 8338 "PrintCLike.cpp"
  append(L"\n");
  append(L"  thread");
                                                            #line 4857 "PrintCLike.cpp.template"
                                                                      print(arrow());
                                                            #line 8343 "PrintCLike.cpp"
  append(L"e1 = ");
                                                            #line 4858 "PrintCLike.cpp.template"
                                                                      if (useGlr) print(thiz());
                                                            #line 8347 "PrintCLike.cpp"
  append(L"end");
                                                            #line 4859 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                                    }
                                                                  }
                                                                  else
                                                                  {
                                                            #line 8355 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4865 "PrintCLike.cpp.template"
                                                                    print(intVal());
                                                            #line 8360 "PrintCLike.cpp"
  append(L"b0W");
                                                            #line 4866 "PrintCLike.cpp.template"
                                                                    print(assign());
                                                                    print(thiz());
                                                            #line 8365 "PrintCLike.cpp"
  append(L"b0; ");
                                                            #line 4868 "PrintCLike.cpp.template"
                                                                    print(intVal());
                                                            #line 8369 "PrintCLike.cpp"
  append(L"e0W");
                                                            #line 4869 "PrintCLike.cpp.template"
                                                                    print(assign());
                                                                    print(thiz());
                                                            #line 8374 "PrintCLike.cpp"
  append(L"e0");
                                                            #line 4872 "PrintCLike.cpp.template"
                                                                    for (size_t k = 1; k < grammar->k; ++k)
                                                                    {
                                                            #line 8379 "PrintCLike.cpp"
  append(L"; ");
                                                            #line 4874 "PrintCLike.cpp.template"
                                                                      print(intVal());
                                                            #line 8383 "PrintCLike.cpp"
  append(L"l");
                                                            #line 4875 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(k));
                                                            #line 8387 "PrintCLike.cpp"
  append(L"W");
                                                            #line 4876 "PrintCLike.cpp.template"
                                                                      print(assign());
                                                                      print(thiz());
                                                            #line 8392 "PrintCLike.cpp"
  append(L"l");
                                                            #line 4878 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(k));
                                                                      print(semicolon());
                                                            #line 8397 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4881 "PrintCLike.cpp.template"
                                                                      print(intVal());
                                                            #line 8402 "PrintCLike.cpp"
  append(L"b");
                                                            #line 4882 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(k));
                                                            #line 8406 "PrintCLike.cpp"
  append(L"W");
                                                            #line 4883 "PrintCLike.cpp.template"
                                                                      print(assign());
                                                                      print(thiz());
                                                            #line 8411 "PrintCLike.cpp"
  append(L"b");
                                                            #line 4885 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(k));
                                                            #line 8415 "PrintCLike.cpp"
  append(L"; ");
                                                            #line 4886 "PrintCLike.cpp.template"
                                                                      print(intVal());
                                                            #line 8419 "PrintCLike.cpp"
  append(L"e");
                                                            #line 4887 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(k));
                                                            #line 8423 "PrintCLike.cpp"
  append(L"W");
                                                            #line 4888 "PrintCLike.cpp.template"
                                                                      print(assign());
                                                                      print(thiz());
                                                            #line 8428 "PrintCLike.cpp"
  append(L"e");
                                                            #line 4890 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(k));
                                                                    }
                                                                    print(semicolon());
                                                            #line 8434 "PrintCLike.cpp"
  append(L"\n");
  append(L"\n");
  append(L"  ");
                                                            #line 4895 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8440 "PrintCLike.cpp"
  append(L"l1 = code; ");
                                                            #line 4896 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8444 "PrintCLike.cpp"
  append(L"b1 = ");
                                                            #line 4897 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8448 "PrintCLike.cpp"
  append(L"begin; ");
                                                            #line 4898 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8452 "PrintCLike.cpp"
  append(L"e1 = ");
                                                            #line 4899 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8456 "PrintCLike.cpp"
  append(L"end");
                                                            #line 4900 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                    for (size_t k = 2; k <= grammar->k; ++k)
                                                                    {
                                                            #line 8462 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4904 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 8467 "PrintCLike.cpp"
  append(L"l");
                                                            #line 4905 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(k));
                                                            #line 8471 "PrintCLike.cpp"
  append(L" = 0");
                                                            #line 4906 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                                    }
                                                                  }
                                                                  if (isLrParser)
                                                                  {
                                                            #line 8479 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4912 "PrintCLike.cpp.template"
                                                                    if (useGlr)
                                                                    {
                                                                      if (! isCpp())
                                                                      {
                                                            #line 8487 "PrintCLike.cpp"
  append(L"thread = ");
                                                            #line 4916 "PrintCLike.cpp.template"
                                                                      }
                                                                      if (isJava())
                                                                      {
                                                                        print(className.c_str());
                                                            #line 8494 "PrintCLike.cpp"
  append(L".this.");
                                                            #line 4920 "PrintCLike.cpp.template"
                                                                      }
                                                                      else if (isCSharp() || isCpp() || isHaxe() || isScala() || isTypescript() || isGo() || isPython())
                                                                      {
                                                                        print(thiz());
                                                            #line 8501 "PrintCLike.cpp"
  append(L"parser");
                                                            #line 4924 "PrintCLike.cpp.template"
                                                                        print(arrow());
                                                                      }
                                                                    }
                                                                    else
                                                                    {
                                                                      print(thiz());
                                                                    }
                                                            #line 8511 "PrintCLike.cpp"
  append(L"parse(-1, ");
                                                            #line 4931 "PrintCLike.cpp.template"
                                                                    print(format.toString<wchar_t>(grammar->whitespace->getStateId()));
                                                                    if (tree)
                                                                    {
                                                            #line 8517 "PrintCLike.cpp"
  append(L", ");
                                                            #line 4934 "PrintCLike.cpp.template"
                                                                      print(nullPtr());
                                                                    }
                                                                    if (useGlr)
                                                                    {
                                                            #line 8524 "PrintCLike.cpp"
  append(L", thread");
                                                            #line 4938 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 8528 "PrintCLike.cpp"
  append(L")");
                                                            #line 4939 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                  }
                                                                  else
                                                                  {
                                                            #line 8535 "PrintCLike.cpp"
  append(L"\n");
  append(L"\n");
  append(L"  ");
                                                            #line 4945 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8541 "PrintCLike.cpp"
  append(L"try_");
                                                            #line 4946 "PrintCLike.cpp.template"
                                                                    print(Format::acceptableName<WString>(grammar->whitespace->name).c_str());
                                                                    if (! isScala()) print(L"()");
                                                                    print(semicolon());
                                                                  }
                                                                  if (useGlr)
                                                                  {
                                                                    if (isJavascript())
                                                                    {
                                                            #line 8552 "PrintCLike.cpp"
  append(L"\n");
  append(L"  end = thread.getEnd();");
                                                            #line 4955 "PrintCLike.cpp.template"
                                                                    }
                                                                    else if (isCpp())
                                                                    {
                                                            #line 8559 "PrintCLike.cpp"
  append(L"\n");
  append(L"  end = thread->end;\n");
  append(L"  delete thread;");
                                                            #line 4960 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 8567 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4964 "PrintCLike.cpp.template"
                                                                      if (useGlr) print(thiz());
                                                            #line 8572 "PrintCLike.cpp"
  append(L"end = thread");
                                                            #line 4965 "PrintCLike.cpp.template"
                                                                      print(arrow());
                                                            #line 8576 "PrintCLike.cpp"
  append(L"end");
                                                            #line 4966 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                                    }
                                                                  }
                                                                  else
                                                                  {
                                                            #line 8584 "PrintCLike.cpp"
  append(L"\n");
  append(L"\n");
  append(L"  ");
                                                            #line 4973 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8590 "PrintCLike.cpp"
  append(L"b0 = b0W; ");
                                                            #line 4974 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8594 "PrintCLike.cpp"
  append(L"e0 = e0W");
                                                            #line 4975 "PrintCLike.cpp.template"
                                                                    for (size_t k = 1; k < grammar->k; ++k)
                                                                    {
                                                            #line 8599 "PrintCLike.cpp"
  append(L"; ");
                                                            #line 4977 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 8603 "PrintCLike.cpp"
  append(L"l");
                                                            #line 4978 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(k));
                                                            #line 8607 "PrintCLike.cpp"
  append(L" = l");
                                                            #line 4979 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(k));
                                                            #line 8611 "PrintCLike.cpp"
  append(L"W");
                                                            #line 4980 "PrintCLike.cpp.template"
                                                                      if (isPython())
                                                                      {
                                                            #line 8616 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4983 "PrintCLike.cpp.template"
                                                                      }
                                                                      else
                                                                      {
                                                            #line 8623 "PrintCLike.cpp"
  append(L"; ");
                                                            #line 4986 "PrintCLike.cpp.template"
                                                                      }
                                                            #line 8627 "PrintCLike.cpp"
  append(L"if ");
                                                            #line 4987 "PrintCLike.cpp.template"
                                                                      print(ifLeftParen());
                                                                      print(thiz());
                                                            #line 8632 "PrintCLike.cpp"
  append(L"l");
                                                            #line 4989 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(k));
                                                            #line 8636 "PrintCLike.cpp"
  append(L" != 0");
                                                            #line 4990 "PrintCLike.cpp.template"
                                                                      print(ifRightParen());
                                                                      if (isPython())
                                                                      {
                                                                        increaseIndent();
                                                                      }
                                                                      else
                                                                      {
                                                            #line 8646 "PrintCLike.cpp"
  append(L" {");
                                                            #line 4997 "PrintCLike.cpp.template"
                                                                      }
                                                            #line 8650 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4999 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 8655 "PrintCLike.cpp"
  append(L"b");
                                                            #line 5000 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(k));
                                                            #line 8659 "PrintCLike.cpp"
  append(L" = b");
                                                            #line 5001 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(k));
                                                            #line 8663 "PrintCLike.cpp"
  append(L"W; ");
                                                            #line 5002 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 8667 "PrintCLike.cpp"
  append(L"e");
                                                            #line 5003 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(k));
                                                            #line 8671 "PrintCLike.cpp"
  append(L" = e");
                                                            #line 5004 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(k));
                                                            #line 8675 "PrintCLike.cpp"
  append(L"W");
                                                            #line 5005 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(semicolon());
                                                                    if (isPython())
                                                                    {
                                                                      decreaseIndent(grammar->k - 1);
                                                                    }
                                                                    else
                                                                    {
                                                            #line 8686 "PrintCLike.cpp"
  append(L" ");
                                                            #line 5013 "PrintCLike.cpp.template"
                                                                      for (size_t k = 1; k < grammar->k; ++k)
                                                                      {
                                                            #line 8691 "PrintCLike.cpp"
  append(L"}");
                                                            #line 5015 "PrintCLike.cpp.template"
                                                                      }
                                                                    }
                                                                  }
                                                                  print(rightBrace());
                                                            #line 8698 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5020 "PrintCLike.cpp.template"
                                                                  if (! isGo())
                                                                    decreaseIndent();
                                                                }
                                                                if (tree && ! isLrParser)
                                                                {
                                                                  if (! isGo())
                                                                    increaseIndent();
                                                                  openMethod (voidType(), L"", L"whitespace", L"");
                                                                  print(leftBrace());
                                                            #line 8710 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if ");
                                                            #line 5030 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                                  print(thiz());
                                                            #line 8716 "PrintCLike.cpp"
  append(L"e0 != ");
                                                            #line 5032 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8720 "PrintCLike.cpp"
  append(L"b1");
                                                            #line 5033 "PrintCLike.cpp.template"
                                                                  print(ifRightParen());
                                                                  increaseIndent();
                                                                  print(leftBrace());
                                                                  decreaseIndent();
                                                            #line 8727 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 5038 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8732 "PrintCLike.cpp"
  append(L"eventHandler");
                                                            #line 5039 "PrintCLike.cpp.template"
                                                                  if (shiftAmbiguity && isTypescript()) print(L"!");
                                                                  print(arrow());
                                                                  if (isGo())
                                                                  {
                                                            #line 8739 "PrintCLike.cpp"
  append(L"W");
                                                            #line 5043 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 8745 "PrintCLike.cpp"
  append(L"w");
                                                            #line 5046 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 8749 "PrintCLike.cpp"
  append(L"hitespace(");
                                                            #line 5047 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8753 "PrintCLike.cpp"
  append(L"e0, ");
                                                            #line 5048 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8757 "PrintCLike.cpp"
  append(L"b1)");
                                                            #line 5049 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                            #line 8761 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 5051 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8766 "PrintCLike.cpp"
  append(L"e0 = ");
                                                            #line 5052 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8770 "PrintCLike.cpp"
  append(L"b1");
                                                            #line 5053 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                  increaseIndent();
                                                                  print(rightBrace());
                                                                  decreaseIndent();
                                                                  print(rightBrace());
                                                                  if (! isGo())
                                                                    decreaseIndent();
                                                            #line 8780 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5061 "PrintCLike.cpp.template"
                                                                }
                                                                if (! isGo())
                                                                  increaseIndent();
                                                                openMethod(intType(), L"", L"matchW", L"int tokenSetId", false, useGlr ? L"ParsingThread" : className.c_str());
                                                                print(leftBrace());
                                                                if (isScala())
                                                                {
                                                            #line 8790 "PrintCLike.cpp"
  append(L"\n");
  append(L"  var continue = true\n");
  append(L"  var code = 0\n");
  append(L"  while (continue) {\n");
  append(L"    code = matcher(tokenSetId)");
                                                            #line 5072 "PrintCLike.cpp.template"
                                                                  increaseIndent(2);
                                                                }
                                                                else
                                                                {
                                                                  if (! isPython())
                                                                  {
                                                            #line 8803 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5079 "PrintCLike.cpp.template"
                                                                    print((isJavascript() || isTypescript() || isHaxe() || isGo()) ? L"var" : L"int");
                                                            #line 8808 "PrintCLike.cpp"
  append(L" code");
                                                            #line 5080 "PrintCLike.cpp.template"
                                                                    if (isTypescript())
                                                                    {
                                                            #line 8813 "PrintCLike.cpp"
  append(L": number");
                                                            #line 5082 "PrintCLike.cpp.template"
                                                                    }
                                                                    else if (isGo())
                                                                    {
                                                            #line 8819 "PrintCLike.cpp"
  append(L" int");
                                                            #line 5085 "PrintCLike.cpp.template"
                                                                    }
                                                                    if (isHaxe())
                                                                    {
                                                            #line 8825 "PrintCLike.cpp"
  append(L" = 0");
                                                            #line 5088 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(semicolon());
                                                                  }
                                                                  if (isHaxe() || isPython())
                                                                  {
                                                            #line 8833 "PrintCLike.cpp"
  append(L"\n");
  append(L"  while ");
                                                            #line 5094 "PrintCLike.cpp.template"
                                                                    print(ifLeftParen());
                                                                    print(isPython() ? L"T" : L"t");
                                                            #line 8839 "PrintCLike.cpp"
  append(L"rue");
                                                            #line 5096 "PrintCLike.cpp.template"
                                                                    print(ifRightParen());
                                                                  }
                                                                  else
                                                                  {
                                                            #line 8846 "PrintCLike.cpp"
  append(L"\n");
  append(L"  for");
                                                            #line 5101 "PrintCLike.cpp.template"
                                                                    if (! isGo())
                                                                    {
                                                            #line 8852 "PrintCLike.cpp"
  append(L" (;;)");
                                                            #line 5103 "PrintCLike.cpp.template"
                                                                    }
                                                                  }
                                                                  increaseIndent();
                                                                  print(leftBrace());
                                                                  increaseIndent();
                                                            #line 8860 "PrintCLike.cpp"
  append(L"\n");
  append(L"code = ");
                                                            #line 5109 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8865 "PrintCLike.cpp"
  append(L"match(tokenSetId)");
                                                            #line 5110 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                                if (simpleWhitespace)
                                                                {
                                                                  printMatch(0,
                                                                             0,
                                                                             0,
                                                                             grammar->simpleWhitespaceIntroducers,
                                                                             IFNOT,
                                                                             false,
                                                                             0,
                                                                             L"if");
                                                                  increaseIndent();
                                                                }
                                                                if (complexWhitespace)
                                                                {
                                                                  printMatch(0,
                                                                             0,
                                                                             0,
                                                                             grammar->complexWhitespaceIntroducers,
                                                                             IFNOT,
                                                                             false,
                                                                             0,
                                                                             L"if");
                                                                  if (isScala())
                                                                  {
                                                            #line 8894 "PrintCLike.cpp"
  append(L"\n");
  append(L"  continue = false\n");
  append(L"}\n");
  append(L"else {\n");
  append(L"  ");
                                                            #line 5140 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8902 "PrintCLike.cpp"
  append(L"skip(code)\n");
  append(L"}");
                                                            #line 5142 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 8909 "PrintCLike.cpp"
  append(L"\n");
  append(L"  break");
                                                            #line 5146 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                    print(rightBrace());
                                                            #line 8915 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5149 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8919 "PrintCLike.cpp"
  append(L"skip(code);");
                                                            #line 5150 "PrintCLike.cpp.template"
                                                                  }
                                                                }
                                                                else if (isScala())
                                                                {
                                                            #line 8926 "PrintCLike.cpp"
  append(L"\n");
  append(L"continue = false");
                                                            #line 5155 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 8933 "PrintCLike.cpp"
  append(L"\n");
  append(L"break");
                                                            #line 5159 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                                if (simpleWhitespace)
                                                                {
                                                                  decreaseIndent();
                                                                  print(rightBrace());
                                                                }
                                                                decreaseIndent();
                                                                print(rightBrace());
                                                                decreaseIndent();
                                                            #line 8947 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5170 "PrintCLike.cpp.template"
                                                                if (! isScala())
                                                                {
                                                            #line 8953 "PrintCLike.cpp"
  append(L"return ");
                                                            #line 5172 "PrintCLike.cpp.template"
                                                                }
                                                            #line 8957 "PrintCLike.cpp"
  append(L"code");
                                                            #line 5173 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                print(rightBrace());
                                                            #line 8962 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5176 "PrintCLike.cpp.template"
                                                                if (! isGo())
                                                                  decreaseIndent();
                                                                printLookaheadMethods(grammar->lookaheadSets.lookaheadWCount, true);
                                                              }
                                                              printLookaheadMethods(grammar->lookaheadSets.lookaheadCount, false);

                                                              if (! isGo())
                                                                increaseIndent();

                                                              if (isScala())
                                                              {
                                                                if (! interfaceName.empty())
                                                                {
                                                            #line 8978 "PrintCLike.cpp"
  append(L"\n");
  append(L"def parse(): Unit = {\n");
  append(L"  parse_");
                                                            #line 5191 "PrintCLike.cpp.template"
                                                                  print(Format::acceptableName<WString>(grammar->startSymbol()->name).c_str());
                                                            #line 8984 "PrintCLike.cpp"
  append(L"()\n");
  append(L"}\n");
                                                            #line 5194 "PrintCLike.cpp.template"
                                                                }
                                                                if (memoization)
                                                                {
                                                                  int bits = Math::bits(grammar->conflictCount);
                                                            #line 8992 "PrintCLike.cpp"
  append(L"\n");
  append(L"private def memoize(i: Int, e: Int, v: Int): Unit = {\n");
  append(L"  memo.put((e << ");
                                                            #line 5200 "PrintCLike.cpp.template"
                                                                  print(format.toString<wchar_t>(bits));
                                                            #line 8998 "PrintCLike.cpp"
  append(L") + i, v)\n");
  append(L"}\n");
  append(L"\n");
  append(L"private def memoized(i: Int, e: Int) = {\n");
  append(L"  memo.getOrElse((e << ");
                                                            #line 5205 "PrintCLike.cpp.template"
                                                                  print(format.toString<wchar_t>(bits));
                                                            #line 9006 "PrintCLike.cpp"
  append(L") + i, 0)\n");
  append(L"}\n");
                                                            #line 5208 "PrintCLike.cpp.template"
                                                                }
                                                            #line 9011 "PrintCLike.cpp"
  append(L"\n");
  append(L"def error(b: Int, e: Int, s: Int, l: Int, t: Int): Int = {");
                                                            #line 5210 "PrintCLike.cpp.template"
                                                              }
                                                              else
                                                              {
                                                                const wchar_t *returnType = isTypescript() && ! grammar->noThrow ? voidType() : L"int ";
                                                                openMethod (returnType, L"", L"error", L"int b, int e, int s, int l, int t", false, useGlr ? L"ParsingThread" : className.c_str());
                                                                print(leftBrace());
                                                              }
                                                              if (hasBacktracking)
                                                              {
                                                                increaseIndent();
                                                            #line 9025 "PrintCLike.cpp"
  append(L"\n");
  append(L"if ");
                                                            #line 5221 "PrintCLike.cpp.template"
                                                                print(ifLeftParen());
                                                                if (grammar->noThrow)
                                                                {
                                                                  print(thiz());
                                                            #line 9033 "PrintCLike.cpp"
  append(L"viable ");
                                                            #line 5225 "PrintCLike.cpp.template"
                                                                  if (isPython())
                                                                  {
                                                            #line 9038 "PrintCLike.cpp"
  append(L"and");
                                                            #line 5227 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 9044 "PrintCLike.cpp"
  append(L"&&");
                                                            #line 5230 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 9048 "PrintCLike.cpp"
  append(L" ");
                                                            #line 5231 "PrintCLike.cpp.template"
                                                                }
                                                            #line 9052 "PrintCLike.cpp"
  append(L"e >= ");
                                                            #line 5232 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 9056 "PrintCLike.cpp"
  append(L"ex");
                                                            #line 5233 "PrintCLike.cpp.template"
                                                                print(ifRightParen());
                                                                print(leftBrace());
                                                            #line 9061 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5236 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 9066 "PrintCLike.cpp"
  append(L"bx = b");
                                                            #line 5237 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 9070 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5239 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 9075 "PrintCLike.cpp"
  append(L"ex = e");
                                                            #line 5240 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 9079 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5242 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 9084 "PrintCLike.cpp"
  append(L"sx = s");
                                                            #line 5243 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 9088 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5245 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 9093 "PrintCLike.cpp"
  append(L"lx = l");
                                                            #line 5246 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 9097 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5248 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 9102 "PrintCLike.cpp"
  append(L"tx = t");
                                                            #line 5249 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                print(rightBrace());
                                                                decreaseIndent();
                                                                if (grammar->noThrow)
                                                                {
                                                            #line 9110 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5255 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 9115 "PrintCLike.cpp"
  append(L"viable = ");
                                                            #line 5256 "PrintCLike.cpp.template"
                                                                  if (isPython())
                                                                  {
                                                            #line 9120 "PrintCLike.cpp"
  append(L"F");
                                                            #line 5258 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 9126 "PrintCLike.cpp"
  append(L"f");
                                                            #line 5261 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 9130 "PrintCLike.cpp"
  append(L"alse");
                                                            #line 5262 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                            #line 9134 "PrintCLike.cpp"
  append(L"\n");
  append(L"  return -s");
                                                            #line 5264 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                                else
                                                                {
                                                                  printFlush(1, true);
                                                            #line 9143 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5270 "PrintCLike.cpp.template"
                                                                  print(beginThrowStmt());
                                                                  print(thiz());
                                                            #line 9149 "PrintCLike.cpp"
  append(L"bx, ");
                                                            #line 5272 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 9153 "PrintCLike.cpp"
  append(L"ex, ");
                                                            #line 5273 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 9157 "PrintCLike.cpp"
  append(L"sx, ");
                                                            #line 5274 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 9161 "PrintCLike.cpp"
  append(L"lx, ");
                                                            #line 5275 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 9165 "PrintCLike.cpp"
  append(L"tx");
                                                            #line 5276 "PrintCLike.cpp.template"
                                                                  print(endThrowStmt());
                                                                  print(semicolon());
                                                                }
                                                              }
                                                              else
                                                              {
                                                                printFlush(1, true);
                                                            #line 9175 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5284 "PrintCLike.cpp.template"
                                                                if (isGo())
                                                                {
                                                            #line 9181 "PrintCLike.cpp"
  append(L"panic(&ParseError{b, e, s, l, t");
                                                            #line 5286 "PrintCLike.cpp.template"
                                                                  if (rejectsAmbiguity())
                                                                  {
                                                            #line 9186 "PrintCLike.cpp"
  append(L", false");
                                                            #line 5288 "PrintCLike.cpp.template"
                                                                    if (tree)
                                                                    {
                                                            #line 9191 "PrintCLike.cpp"
  append(L", nil");
                                                            #line 5290 "PrintCLike.cpp.template"
                                                                    }
                                                                  }
                                                            #line 9196 "PrintCLike.cpp"
  append(L"})");
                                                            #line 5292 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                                  print(beginThrowStmt());
                                                            #line 9203 "PrintCLike.cpp"
  append(L"b, e, s, l, t");
                                                            #line 5296 "PrintCLike.cpp.template"
                                                                  print(endThrowStmt());
                                                                  print(semicolon());
                                                                }
                                                              }
                                                              print(rightBrace());
                                                            #line 9211 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5302 "PrintCLike.cpp.template"
                                                              if (! isGo())
                                                                decreaseIndent();
                                                              if (isScala())
                                                              {
                                                                printInstanceCode();
                                                              }
                                                              privateVars();
                                                            }

                                                            void PrintCLike::printStackAllocation()
                                                            {
                                                              Trace("PrintCLike::printStackAllocation");
                                                            #line 9226 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5316 "PrintCLike.cpp.template"
                                                              print(thiz());
                                                            #line 9231 "PrintCLike.cpp"
  append(L"stack = ");
                                                            #line 5317 "PrintCLike.cpp.template"
                                                              if (isGo())
                                                              {
                                                            #line 9236 "PrintCLike.cpp"
  append(L"&StackNode{");
                                                            #line 5319 "PrintCLike.cpp.template"
                                                              }
                                                              else
                                                              {
                                                                if (! isPython())
                                                                {
                                                            #line 9244 "PrintCLike.cpp"
  append(L"new ");
                                                            #line 5324 "PrintCLike.cpp.template"
                                                                }
                                                                if (! isHaxe() && ! isTypescript()) print(staticPrefix());
                                                            #line 9249 "PrintCLike.cpp"
  append(L"StackNode(");
                                                            #line 5326 "PrintCLike.cpp.template"
                                                              }
                                                              print(thiz());
                                                            #line 9254 "PrintCLike.cpp"
  append(L"state, ");
                                                            #line 5328 "PrintCLike.cpp.template"
                                                              if (grammar->states->hasLookback)
                                                              {
                                                            #line 9259 "PrintCLike.cpp"
  append(L"lookback, ");
                                                            #line 5330 "PrintCLike.cpp.template"
                                                              }
                                                            #line 9263 "PrintCLike.cpp"
  append(L"pos, ");
                                                            #line 5331 "PrintCLike.cpp.template"
                                                              print(thiz());
                                                            #line 9267 "PrintCLike.cpp"
  append(L"stack");
                                                            #line 5332 "PrintCLike.cpp.template"
                                                              print(isGo() ? L"}" : L")");
                                                              print(semicolon());
                                                            #line 9272 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5335 "PrintCLike.cpp.template"
                                                              print(thiz());
                                                            #line 9277 "PrintCLike.cpp"
  append(L"state = shift");
                                                            #line 5336 "PrintCLike.cpp.template"
                                                              print(semicolon());
                                                            }

                                                            void PrintCLike::printStackPop()
                                                            {
                                                              Trace("PrintCLike::printStackPop");
                                                            #line 9286 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 5344 "PrintCLike.cpp.template"
                                                              print(intVar());
                                                            #line 9291 "PrintCLike.cpp"
  append(L"n");
                                                            #line 5345 "PrintCLike.cpp.template"
                                                              print(assign());
                                                            #line 9295 "PrintCLike.cpp"
  append(L"symbols");
                                                            #line 5346 "PrintCLike.cpp.template"
                                                              print(semicolon());
                                                            #line 9299 "PrintCLike.cpp"
  append(L"\n");
  append(L"    if ");
                                                            #line 5348 "PrintCLike.cpp.template"
                                                              print(ifLeftParen());
                                                            #line 9304 "PrintCLike.cpp"
  append(L"shift >= 0");
                                                            #line 5349 "PrintCLike.cpp.template"
                                                              print(ifRightParen());
                                                              printIndented(2, leftBrace());
                                                            #line 9309 "PrintCLike.cpp"
  append(L"\n");
  append(L"      n -= 1");
                                                            #line 5352 "PrintCLike.cpp.template"
                                                              print(semicolon());
                                                              printIndented(2, rightBrace());
                                                            #line 9315 "PrintCLike.cpp"
  append(L"\n");
  append(L"    if ");
                                                            #line 5355 "PrintCLike.cpp.template"
                                                              print(ifLeftParen());
                                                            #line 9320 "PrintCLike.cpp"
  append(L"n > 0");
                                                            #line 5356 "PrintCLike.cpp.template"
                                                              print(ifRightParen());
                                                              printIndented(2, leftBrace());
                                                              if (isCpp())
                                                              {
                                                            #line 9327 "PrintCLike.cpp"
  append(L"\n");
  append(L"      stack = stack->pop(n - 1);\n");
  append(L"      state = stack->state;");
                                                            #line 5362 "PrintCLike.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 9334 "PrintCLike.cpp"
  append(L"\n");
  append(L"      bs = stack->pos;");
                                                            #line 5365 "PrintCLike.cpp.template"
                                                                }
                                                            #line 9339 "PrintCLike.cpp"
  append(L"\n");
  append(L"      stack = stack->pop(1);");
                                                            #line 5367 "PrintCLike.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 9346 "PrintCLike.cpp"
  append(L"\n");
  append(L"      ");
                                                            #line 5371 "PrintCLike.cpp.template"
                                                                if (isHaxe())
                                                                {
                                                            #line 9352 "PrintCLike.cpp"
  append(L"for (i in 1...n)");
                                                            #line 5373 "PrintCLike.cpp.template"
                                                                }
                                                                else if (isScala())
                                                                {
                                                            #line 9358 "PrintCLike.cpp"
  append(L"for (i <- 2 to n)");
                                                            #line 5376 "PrintCLike.cpp.template"
                                                                }
                                                                else if (isPython())
                                                                {
                                                            #line 9364 "PrintCLike.cpp"
  append(L"for _ in range(n - 1):");
                                                            #line 5379 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 9370 "PrintCLike.cpp"
  append(L"for ");
                                                            #line 5382 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                                  print(intVar());
                                                            #line 9375 "PrintCLike.cpp"
  append(L"i");
                                                            #line 5384 "PrintCLike.cpp.template"
                                                                  print(assign());
                                                            #line 9379 "PrintCLike.cpp"
  append(L"1; i < n; i++");
                                                            #line 5385 "PrintCLike.cpp.template"
                                                                  print(ifRightParen());
                                                                }
                                                                printIndented(3, leftBrace());
                                                            #line 9385 "PrintCLike.cpp"
  append(L"\n");
  append(L"        ");
                                                            #line 5389 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 9390 "PrintCLike.cpp"
  append(L"stack = ");
                                                            #line 5390 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 9394 "PrintCLike.cpp"
  append(L"stack.link");
                                                            #line 5391 "PrintCLike.cpp.template"
                                                                if (isTypescript()) print(L"!");
                                                                print(semicolon());
                                                                printIndented(3, rightBrace());
                                                            #line 9400 "PrintCLike.cpp"
  append(L"\n");
  append(L"      ");
                                                            #line 5395 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 9405 "PrintCLike.cpp"
  append(L"state = ");
                                                            #line 5396 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 9409 "PrintCLike.cpp"
  append(L"stack");
                                                            #line 5397 "PrintCLike.cpp.template"
                                                                print(arrow());
                                                            #line 9413 "PrintCLike.cpp"
  append(L"state");
                                                            #line 5398 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                if (tree)
                                                                {
                                                            #line 9419 "PrintCLike.cpp"
  append(L"\n");
  append(L"      ");
                                                            #line 5402 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 9424 "PrintCLike.cpp"
  append(L"bs = ");
                                                            #line 5403 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 9428 "PrintCLike.cpp"
  append(L"stack");
                                                            #line 5404 "PrintCLike.cpp.template"
                                                                  print(arrow());
                                                            #line 9432 "PrintCLike.cpp"
  append(L"pos");
                                                            #line 5405 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                            #line 9437 "PrintCLike.cpp"
  append(L"\n");
  append(L"      ");
                                                            #line 5408 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 9442 "PrintCLike.cpp"
  append(L"stack = ");
                                                            #line 5409 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 9446 "PrintCLike.cpp"
  append(L"stack.link");
                                                            #line 5410 "PrintCLike.cpp.template"
                                                                if (isTypescript()) print(L"!");
                                                                print(semicolon());
                                                              }
                                                              if (tree)
                                                              {
                                                            #line 9454 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 5416 "PrintCLike.cpp.template"
                                                                printIndented(2, elseWithBraces());
                                                            #line 9459 "PrintCLike.cpp"
  append(L"\n");
  append(L"      ");
                                                            #line 5418 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 9464 "PrintCLike.cpp"
  append(L"bs = pos");
                                                            #line 5419 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                printIndented(2, rightBrace());
                                                              }
                                                              else
                                                              {
                                                                printIndented(2, rightBrace());
                                                              }
                                                            }

                                                            void PrintCLike::printCountMethod()
                                                            {
                                                              Trace("PrintCLike::printCountMethod");

                                                              const wchar_t *clazz = useGlr ? L"StackNode" : className.c_str();
                                                              if (grammar->states->hasLookback)
                                                              {
                                                            #line 9483 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5436 "PrintCLike.cpp.template"
                                                                openMethod(intType(), L"", L"lookback", L"int x, int y", false, clazz);
                                                                const wchar_t *lookback = isGo() ? L"lookback" : L"LOOKBACK";
                                                                print(leftBrace());
                                                                increaseIndent();
                                                                if (isGo())
                                                                {
                                                            #line 9492 "PrintCLike.cpp"
  append(L"\n");
  append(L"i := lookback[y]\n");
  append(L"l := lookback[i]\n");
  append(L"for l > x {");
                                                            #line 5445 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 9501 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5449 "PrintCLike.cpp.template"
                                                                  print(intVar());
                                                            #line 9505 "PrintCLike.cpp"
  append(L"i");
                                                            #line 5450 "PrintCLike.cpp.template"
                                                                  print(assign());
                                                                  print(staticPrefix());
                                                                  print(lookback);
                                                                  print(leftbracket());
                                                            #line 9512 "PrintCLike.cpp"
  append(L"y");
                                                            #line 5454 "PrintCLike.cpp.template"
                                                                  print(rightbracket());
                                                                  print(semicolon());
                                                            #line 9517 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5457 "PrintCLike.cpp.template"
                                                                  print(intVar());
                                                            #line 9521 "PrintCLike.cpp"
  append(L"l");
                                                            #line 5458 "PrintCLike.cpp.template"
                                                                  print(assign());
                                                                  print(staticPrefix());
                                                                  print(lookback);
                                                                  print(leftbracket());
                                                            #line 9528 "PrintCLike.cpp"
  append(L"i");
                                                            #line 5462 "PrintCLike.cpp.template"
                                                                  print(rightbracket());
                                                                  print(semicolon());
                                                            #line 9533 "PrintCLike.cpp"
  append(L"\n");
  append(L"while ");
                                                            #line 5465 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                            #line 9538 "PrintCLike.cpp"
  append(L"l > x");
                                                            #line 5466 "PrintCLike.cpp.template"
                                                                  print(ifRightParen());
                                                                  print(leftBrace());
                                                                }
                                                            #line 9544 "PrintCLike.cpp"
  append(L"\n");
  append(L"  i += 2");
                                                            #line 5470 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 9549 "PrintCLike.cpp"
  append(L"\n");
  append(L"  l = ");
                                                            #line 5472 "PrintCLike.cpp.template"
                                                                print(staticPrefix());
                                                                print(lookback);
                                                                print(leftbracket());
                                                            #line 9556 "PrintCLike.cpp"
  append(L"i");
                                                            #line 5475 "PrintCLike.cpp.template"
                                                                print(rightbracket());
                                                                print(semicolon());
                                                                print(rightBrace());
                                                            #line 9562 "PrintCLike.cpp"
  append(L"\n");
  append(L"if ");
                                                            #line 5479 "PrintCLike.cpp.template"
                                                                print(ifLeftParen());
                                                            #line 9567 "PrintCLike.cpp"
  append(L"l < x");
                                                            #line 5480 "PrintCLike.cpp.template"
                                                                print(ifRightParen());
                                                                print(leftBrace());
                                                            #line 9572 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5483 "PrintCLike.cpp.template"
                                                                print(returnKeyword());
                                                            #line 9577 "PrintCLike.cpp"
  append(L"0");
                                                            #line 5484 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 9581 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5486 "PrintCLike.cpp.template"
                                                                print(elseWithBraces());
                                                            #line 9585 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5488 "PrintCLike.cpp.template"
                                                                print(returnKeyword());
                                                                print(staticPrefix());
                                                                print(lookback);
                                                                print(leftbracket());
                                                            #line 9593 "PrintCLike.cpp"
  append(L"i + 1");
                                                            #line 5492 "PrintCLike.cpp.template"
                                                                print(rightbracket());
                                                                print(semicolon());
                                                                print(rightBrace());
                                                                decreaseIndent();
                                                                print(rightBrace());
                                                            #line 9601 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5498 "PrintCLike.cpp.template"
                                                                if (isJavascript() && useGlr)
                                                                {
                                                            #line 9606 "PrintCLike.cpp"
  append(L"\n");
  append(L"this.count = function(code)\n");
                                                            #line 5502 "PrintCLike.cpp.template"
                                                                }
                                                                else if (isTypescript() && useGlr)
                                                                {
                                                            #line 9613 "PrintCLike.cpp"
  append(L"\n");
  append(L"public count(code: number)\n");
                                                            #line 5507 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                                  openMethod(intType(), L"", L"count", L"int code", false, clazz);
                                                                }
                                                                print(leftBrace());
                                                                increaseIndent();
                                                            #line 9624 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5515 "PrintCLike.cpp.template"
                                                                print(intVar());
                                                            #line 9628 "PrintCLike.cpp"
  append(L"count");
                                                            #line 5516 "PrintCLike.cpp.template"
                                                                print(assign());
                                                            #line 9632 "PrintCLike.cpp"
  append(L"0");
                                                            #line 5517 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                int stackElementSize = tree ? 3 : 2;
                                                                if (isHaxe() || isScala())
                                                                {
                                                                  if (useGlr)
                                                                  {
                                                            #line 9641 "PrintCLike.cpp"
  append(L"\n");
  append(L"var node = this");
                                                            #line 5524 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                    if (isScala())
                                                                    {
                                                            #line 9648 "PrintCLike.cpp"
  append(L"\n");
  append(L"var c = code");
                                                            #line 5528 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 9653 "PrintCLike.cpp"
  append(L"\n");
  append(L"while ");
                                                            #line 5530 "PrintCLike.cpp.template"
                                                                    print(ifLeftParen());
                                                            #line 9658 "PrintCLike.cpp"
  append(L"node.state >= 0");
                                                            #line 5531 "PrintCLike.cpp.template"
                                                                    print(ifRightParen());
                                                                    print(leftBrace());
                                                                    if (isScala())
                                                                    {
                                                            #line 9665 "PrintCLike.cpp"
  append(L"\n");
  append(L"  c = lookback(node.code, c)\n");
  append(L"  if (c == 0) return count\n");
  append(L"  count += 1");
                                                            #line 5538 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 9674 "PrintCLike.cpp"
  append(L"\n");
  append(L"  code = lookback(node.code, code);\n");
  append(L"  if ");
                                                            #line 5543 "PrintCLike.cpp.template"
                                                                      print(ifLeftParen());
                                                            #line 9680 "PrintCLike.cpp"
  append(L"code == 0");
                                                            #line 5544 "PrintCLike.cpp.template"
                                                                      print(ifRightParen());
                                                            #line 9684 "PrintCLike.cpp"
  append(L"\n");
  append(L"    break");
                                                            #line 5547 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                            #line 9689 "PrintCLike.cpp"
  append(L"\n");
  append(L"  count++");
                                                            #line 5549 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                                    }
                                                            #line 9695 "PrintCLike.cpp"
  append(L"\n");
  append(L"  node = node.link");
                                                            #line 5552 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                  }
                                                                  else
                                                                  {
                                                            #line 9703 "PrintCLike.cpp"
  append(L"\n");
  append(L"var t = top");
                                                            #line 5557 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 9708 "PrintCLike.cpp"
  append(L"\n");
  append(L"var c = code");
                                                            #line 5559 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 9713 "PrintCLike.cpp"
  append(L"\n");
  append(L"while (t >= 0)");
                                                            #line 5561 "PrintCLike.cpp.template"
                                                                    print(leftBrace());
                                                            #line 9718 "PrintCLike.cpp"
  append(L"\n");
  append(L"  c = lookback(iStack");
                                                            #line 5563 "PrintCLike.cpp.template"
                                                                    print(leftbracket());
                                                            #line 9723 "PrintCLike.cpp"
  append(L"t");
                                                            #line 5564 "PrintCLike.cpp.template"
                                                                    print(rightbracket());
                                                            #line 9727 "PrintCLike.cpp"
  append(L", c)");
                                                            #line 5565 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 9731 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if ");
                                                            #line 5567 "PrintCLike.cpp.template"
                                                                    print(ifLeftParen());
                                                            #line 9736 "PrintCLike.cpp"
  append(L"c == 0");
                                                            #line 5568 "PrintCLike.cpp.template"
                                                                    print(ifRightParen());
                                                            #line 9740 "PrintCLike.cpp"
  append(L" return count");
                                                            #line 5569 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 9744 "PrintCLike.cpp"
  append(L"\n");
  append(L"  count += 1");
                                                            #line 5571 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 9749 "PrintCLike.cpp"
  append(L"\n");
  append(L"  t -= ");
                                                            #line 5573 "PrintCLike.cpp.template"
                                                                    print(format.toString<wchar_t>(stackElementSize));
                                                                    print(semicolon());
                                                                  }
                                                                }
                                                                else
                                                                {
                                                                  if (useGlr)
                                                                  {
                                                                    if (isPython())
                                                                    {
                                                            #line 9763 "PrintCLike.cpp"
  append(L"\n");
  append(L"node = self\n");
  append(L"while ");
                                                            #line 5585 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 9771 "PrintCLike.cpp"
  append(L"\n");
  append(L"for ");
                                                            #line 5589 "PrintCLike.cpp.template"
                                                                      print(ifLeftParen());
                                                                      if (isJavascript() || isTypescript())
                                                                      {
                                                            #line 9778 "PrintCLike.cpp"
  append(L"var ");
                                                            #line 5592 "PrintCLike.cpp.template"
                                                                      }
                                                                      else if (!isGo())
                                                                      {
                                                            #line 9784 "PrintCLike.cpp"
  append(L"StackNode ");
                                                            #line 5595 "PrintCLike.cpp.template"
                                                                      }
                                                                      if (isCpp()) print(L"*");
                                                            #line 9789 "PrintCLike.cpp"
  append(L"node");
                                                            #line 5597 "PrintCLike.cpp.template"
                                                                      if (isTypescript())
                                                                      {
                                                            #line 9794 "PrintCLike.cpp"
  append(L": StackNode | null");
                                                            #line 5599 "PrintCLike.cpp.template"
                                                                      }
                                                                      print(assign());
                                                            #line 9799 "PrintCLike.cpp"
  append(L"this; ");
                                                            #line 5601 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 9803 "PrintCLike.cpp"
  append(L"node");
                                                            #line 5602 "PrintCLike.cpp.template"
                                                                    if (isTypescript()) print(L"!");
                                                                    print(arrow());
                                                            #line 9808 "PrintCLike.cpp"
  append(L"state >= 0");
                                                            #line 5604 "PrintCLike.cpp.template"
                                                                    if (isPython())
                                                                    {
                                                            #line 9813 "PrintCLike.cpp"
  append(L":");
                                                            #line 5606 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 9819 "PrintCLike.cpp"
  append(L"; node = node");
                                                            #line 5609 "PrintCLike.cpp.template"
                                                                      if (isTypescript()) print(L"!");
                                                                      print(arrow());
                                                            #line 9824 "PrintCLike.cpp"
  append(L"link");
                                                            #line 5611 "PrintCLike.cpp.template"
                                                                      print(ifRightParen());
                                                                    }
                                                                    print(leftBrace());
                                                            #line 9830 "PrintCLike.cpp"
  append(L"\n");
  append(L"  code = ");
                                                            #line 5615 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                                    print(isGo() ? L"L" : L"l");
                                                            #line 9836 "PrintCLike.cpp"
  append(L"ookback(node");
                                                            #line 5617 "PrintCLike.cpp.template"
                                                                    if (isTypescript()) print(L"!");
                                                                    print(arrow());
                                                            #line 9841 "PrintCLike.cpp"
  append(L"code, code)");
                                                            #line 5619 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                  }
                                                                  else
                                                                  {
                                                                    if (isPython())
                                                                    {
                                                            #line 9850 "PrintCLike.cpp"
  append(L"\n");
  append(L"t");
                                                            #line 5626 "PrintCLike.cpp.template"
                                                                      print(assign());
                                                                      print(thiz());
                                                            #line 9856 "PrintCLike.cpp"
  append(L"top");
                                                            #line 5628 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                            #line 9860 "PrintCLike.cpp"
  append(L"\n");
  append(L"while ");
                                                            #line 5630 "PrintCLike.cpp.template"
                                                                      print(ifLeftParen());
                                                                      print(intVar());
                                                            #line 9866 "PrintCLike.cpp"
  append(L"t >= 0");
                                                            #line 5632 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 9872 "PrintCLike.cpp"
  append(L"\n");
  append(L"for ");
                                                            #line 5636 "PrintCLike.cpp.template"
                                                                      print(ifLeftParen());
                                                                      print(intVar());
                                                            #line 9878 "PrintCLike.cpp"
  append(L"t");
                                                            #line 5638 "PrintCLike.cpp.template"
                                                                      print(assign());
                                                                      print(thiz());
                                                            #line 9883 "PrintCLike.cpp"
  append(L"top; t >= 0; t -= ");
                                                            #line 5640 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(stackElementSize));
                                                                    }
                                                                    print(ifRightParen());
                                                                    print(leftBrace());
                                                            #line 9890 "PrintCLike.cpp"
  append(L"\n");
  append(L"  code = ");
                                                            #line 5645 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 9895 "PrintCLike.cpp"
  append(L"lookback(");
                                                            #line 5646 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 9899 "PrintCLike.cpp"
  append(L"iStack[t], code)");
                                                            #line 5647 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                  }
                                                            #line 9904 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if ");
                                                            #line 5650 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                            #line 9909 "PrintCLike.cpp"
  append(L"code == 0");
                                                            #line 5651 "PrintCLike.cpp.template"
                                                                  print(ifRightParen());
                                                                  increaseIndent();
                                                                  print(leftBrace());
                                                            #line 9915 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5655 "PrintCLike.cpp.template"
                                                                  if (! isHaxe() && ! isScala())
                                                                  {
                                                            #line 9921 "PrintCLike.cpp"
  append(L"break");
                                                            #line 5657 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 9927 "PrintCLike.cpp"
  append(L"return count");
                                                            #line 5660 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(semicolon());
                                                                  print(rightBrace());
                                                                  decreaseIndent();
                                                            #line 9934 "PrintCLike.cpp"
  append(L"\n");
  append(L"  count += 1");
                                                            #line 5665 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                  if (isPython())
                                                                  {
                                                                    if (useGlr)
                                                                    {
                                                            #line 9943 "PrintCLike.cpp"
  append(L"\n");
  append(L"  node = node.link");
                                                            #line 5671 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 9950 "PrintCLike.cpp"
  append(L"\n");
  append(L"  t -= ");
                                                            #line 5675 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(stackElementSize));
                                                                    }
                                                                  }
                                                                }
                                                                print(rightBrace());
                                                            #line 9959 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5681 "PrintCLike.cpp.template"
                                                                print(returnKeyword());
                                                            #line 9963 "PrintCLike.cpp"
  append(L"count");
                                                            #line 5682 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                decreaseIndent();
                                                                print(rightBrace());
                                                                if (isJavascript() && useGlr)
                                                                {
                                                            #line 9971 "PrintCLike.cpp"
  append(L";");
                                                            #line 5687 "PrintCLike.cpp.template"
                                                                }
                                                              }
                                                            }

                                                            void PrintCLike::printLookaheadMethods(size_t lookaheadMethods, bool withWhitespace)
                                                            {
                                                              Trace("PrintCLike::printLookaheadMethods");

                                                              if (! isLrParser)
                                                              {
                                                                for (size_t k = 1; k <= lookaheadMethods; ++k)
                                                                {
                                                                  if (! isGo())
                                                                    increaseIndent();
                                                                  WString name(L"lookahead");
                                                                  name += format.toString<wchar_t>(k);
                                                                  name += withWhitespace ? L"W" : L"";
                                                                  WString args(k == 1 || ! unlimitedLookahead ? L"" : L"int prefix, ");
                                                                  args += L"int tokenSetId";
                                                                  openMethod(voidType(), L"", name.c_str(), args.c_str());
                                                                  print(leftBrace());
                                                                  wchar_t *kAsString = format.toString<wchar_t>(k);
                                                                  increaseIndent();
                                                            #line 9997 "PrintCLike.cpp"
  append(L"\n");
  append(L"if ");
                                                            #line 5711 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                                  print(thiz());
                                                            #line 10003 "PrintCLike.cpp"
  append(L"l");
                                                            #line 5713 "PrintCLike.cpp.template"
                                                                  print(kAsString);
                                                            #line 10007 "PrintCLike.cpp"
  append(L" == 0");
                                                            #line 5714 "PrintCLike.cpp.template"
                                                                  print(ifRightParen());
                                                                  print(leftBrace());
                                                            #line 10012 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5717 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 10017 "PrintCLike.cpp"
  append(L"l");
                                                            #line 5718 "PrintCLike.cpp.template"
                                                                  print(kAsString);
                                                            #line 10021 "PrintCLike.cpp"
  append(L" = ");
                                                            #line 5719 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 10025 "PrintCLike.cpp"
  append(L"match");
                                                            #line 5720 "PrintCLike.cpp.template"
                                                                  if (withWhitespace)
                                                                  {
                                                            #line 10030 "PrintCLike.cpp"
  append(L"W");
                                                            #line 5722 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isScala())
                                                                  {
                                                            #line 10036 "PrintCLike.cpp"
  append(L"er");
                                                            #line 5725 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 10040 "PrintCLike.cpp"
  append(L"(tokenSetId)");
                                                            #line 5726 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                            #line 10044 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5728 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 10049 "PrintCLike.cpp"
  append(L"b");
                                                            #line 5729 "PrintCLike.cpp.template"
                                                                  print(kAsString);
                                                            #line 10053 "PrintCLike.cpp"
  append(L" = ");
                                                            #line 5730 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 10057 "PrintCLike.cpp"
  append(L"begin");
                                                            #line 5731 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                            #line 10061 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5733 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 10066 "PrintCLike.cpp"
  append(L"e");
                                                            #line 5734 "PrintCLike.cpp.template"
                                                                  print(kAsString);
                                                            #line 10070 "PrintCLike.cpp"
  append(L" = ");
                                                            #line 5735 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 10074 "PrintCLike.cpp"
  append(L"end");
                                                            #line 5736 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                  print(rightBrace());
                                                                  if (unlimitedLookahead)
                                                                  {
                                                                    if (k >= 2)
                                                                    {
                                                            #line 10083 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5743 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 10087 "PrintCLike.cpp"
  append(L"lk = prefix + ");
                                                            #line 5744 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 10091 "PrintCLike.cpp"
  append(L"l");
                                                            #line 5745 "PrintCLike.cpp.template"
                                                                      print(kAsString);
                                                                      print(semicolon());
                                                                    }
                                                                  }
                                                                  else
                                                                  {
                                                                    if (k == 2)
                                                                    {
                                                            #line 10102 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5754 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 10106 "PrintCLike.cpp"
  append(L"lk = (");
                                                            #line 5755 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 10110 "PrintCLike.cpp"
  append(L"l2 << ");
                                                            #line 5756 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(grammar->tokenSequenceFactory->tokenBits()));
                                                            #line 10114 "PrintCLike.cpp"
  append(L") | ");
                                                            #line 5757 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 10118 "PrintCLike.cpp"
  append(L"l1");
                                                            #line 5758 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                                    }
                                                                    else if (k > 2)
                                                                    {
                                                            #line 10125 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5763 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 10129 "PrintCLike.cpp"
  append(L"lk |= ");
                                                            #line 5764 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 10133 "PrintCLike.cpp"
  append(L"l");
                                                            #line 5765 "PrintCLike.cpp.template"
                                                                      print(kAsString);
                                                            #line 10137 "PrintCLike.cpp"
  append(L" << ");
                                                            #line 5766 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>((k - 1) * grammar->tokenSequenceFactory->tokenBits()));
                                                                      print(semicolon());
                                                                    }
                                                                  }
                                                                  decreaseIndent();
                                                                  print(rightBrace());
                                                            #line 10146 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5773 "PrintCLike.cpp.template"
                                                                  if (! isGo())
                                                                    decreaseIndent();
                                                                  if (grammar->tables && k + 1 >= grammar->tables)
                                                                  {
                                                                    break;
                                                                  }
                                                                }
                                                              }
                                                            }

                                                            void PrintCLike::printInitializer()
                                                            {
                                                              Trace("PrintCLike::printInitializer");

                                                              if (! isGo())
                                                                increaseIndent();
                                                              if (! useGlr)
                                                              {
                                                                const wchar_t *type = isJava()
                                                                                    ? (codepoints ? L"int[] " : L"CharSequence ")
                                                                                    : isHaxe()
                                                                                    ? L"Bytes "
                                                                                    : stringType();
                                                                openMethod(type, L"", L"getInput", L"", true);
                                                                print(leftBrace());
                                                            #line 10174 "PrintCLike.cpp"
  append(L"\n");
  append(L"  return ");
                                                            #line 5799 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                                if (useGlr && (isCSharp() || isCpp() || isHaxe() || isScala() || isTypescript()))
                                                                {
                                                            #line 10181 "PrintCLike.cpp"
  append(L"parser");
                                                            #line 5802 "PrintCLike.cpp.template"
                                                                  print(arrow());
                                                                }
                                                            #line 10186 "PrintCLike.cpp"
  append(L"input");
                                                            #line 5804 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                print(rightBrace());
                                                                if (isJavascript())
                                                                {
                                                            #line 10193 "PrintCLike.cpp"
  append(L";");
                                                            #line 5808 "PrintCLike.cpp.template"
                                                                }
                                                            #line 10197 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5810 "PrintCLike.cpp.template"
                                                                openMethod(intType(), L"", L"getTokenOffset", L"", true);
                                                                print(leftBrace());
                                                            #line 10202 "PrintCLike.cpp"
  append(L"\n");
  append(L"  return ");
                                                            #line 5813 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 10207 "PrintCLike.cpp"
  append(L"b0");
                                                            #line 5814 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                print(rightBrace());
                                                                if (isJavascript())
                                                                {
                                                            #line 10214 "PrintCLike.cpp"
  append(L";");
                                                            #line 5818 "PrintCLike.cpp.template"
                                                                }
                                                            #line 10218 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5820 "PrintCLike.cpp.template"
                                                                openMethod(intType(), L"", L"getTokenEnd", L"", true);
                                                                print(leftBrace());
                                                            #line 10223 "PrintCLike.cpp"
  append(L"\n");
  append(L"  return ");
                                                            #line 5823 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 10228 "PrintCLike.cpp"
  append(L"e0");
                                                            #line 5824 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                print(rightBrace());
                                                                if (isJavascript())
                                                                {
                                                            #line 10235 "PrintCLike.cpp"
  append(L";");
                                                            #line 5828 "PrintCLike.cpp.template"
                                                                }
                                                            #line 10239 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5830 "PrintCLike.cpp.template"
                                                              }
                                                              if (isJavascript())
                                                              {
                                                                if (useGlr)
                                                                {
                                                            #line 10247 "PrintCLike.cpp"
  append(L"\n");
  append(L"this.reset = function");
                                                            #line 5836 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 10254 "PrintCLike.cpp"
  append(L"\n");
  append(L"function reset");
                                                            #line 5840 "PrintCLike.cpp.template"
                                                                }
                                                            #line 10259 "PrintCLike.cpp"
  append(L"(l, b, e)\n");
  append(L"{");
                                                            #line 5842 "PrintCLike.cpp.template"
                                                              }
                                                              else if (isTypescript())
                                                              {
                                                            #line 10266 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5846 "PrintCLike.cpp.template"
                                                                if (! performanceTest && ! useGlr)
                                                                {
                                                            #line 10271 "PrintCLike.cpp"
  append(L"private ");
                                                            #line 5848 "PrintCLike.cpp.template"
                                                                }
                                                            #line 10275 "PrintCLike.cpp"
  append(L"reset(l: number, b: number, e: number)\n");
  append(L"{");
                                                            #line 5850 "PrintCLike.cpp.template"
                                                              }
                                                              else if (isHaxe())
                                                              {
                                                            #line 10282 "PrintCLike.cpp"
  append(L"\n");
  append(L"public function reset(l, b, e)\n");
  append(L"{");
                                                            #line 5855 "PrintCLike.cpp.template"
                                                              }
                                                              else
                                                              {
                                                                openMethod(voidType(), isJava() ? L"final " : L"", L"reset", L"int l, int b, int e", false, useGlr ? L"ParsingThread" : className.c_str());
                                                                print(leftBrace());
                                                              }
                                                            #line 10293 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5862 "PrintCLike.cpp.template"
                                                              if (! isPython() && ! isScala())
                                                              {
                                                            #line 10299 "PrintCLike.cpp"
  append(L"        ");
                                                            #line 5864 "PrintCLike.cpp.template"
                                                                print(wcslen(thiz()), L" ");
                                                              }
                                                              print(thiz());
                                                            #line 10305 "PrintCLike.cpp"
  append(L"b0 = b; ");
                                                            #line 5867 "PrintCLike.cpp.template"
                                                              print(thiz());
                                                            #line 10309 "PrintCLike.cpp"
  append(L"e0 = b");
                                                            #line 5868 "PrintCLike.cpp.template"
                                                              print(semicolon());
                                                            #line 10313 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5870 "PrintCLike.cpp.template"
                                                              print(thiz());
                                                            #line 10318 "PrintCLike.cpp"
  append(L"l1 = l; ");
                                                            #line 5871 "PrintCLike.cpp.template"
                                                              print(thiz());
                                                            #line 10322 "PrintCLike.cpp"
  append(L"b1 = b; ");
                                                            #line 5872 "PrintCLike.cpp.template"
                                                              print(thiz());
                                                            #line 10326 "PrintCLike.cpp"
  append(L"e1 = e");
                                                            #line 5873 "PrintCLike.cpp.template"
                                                              print(semicolon());
                                                              for (size_t k = 2; k <= grammar->k; ++k)
                                                              {
                                                            #line 10332 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5877 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 10337 "PrintCLike.cpp"
  append(L"l");
                                                            #line 5878 "PrintCLike.cpp.template"
                                                                print(format.toString<wchar_t>(k));
                                                            #line 10341 "PrintCLike.cpp"
  append(L" = 0; ");
                                                            #line 5879 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 10345 "PrintCLike.cpp"
  append(L"b");
                                                            #line 5880 "PrintCLike.cpp.template"
                                                                print(format.toString<wchar_t>(k));
                                                            #line 10349 "PrintCLike.cpp"
  append(L" = 0; ");
                                                            #line 5881 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 10353 "PrintCLike.cpp"
  append(L"e");
                                                            #line 5882 "PrintCLike.cpp.template"
                                                                print(format.toString<wchar_t>(k));
                                                            #line 10357 "PrintCLike.cpp"
  append(L" = 0");
                                                            #line 5883 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                              }
                                                            #line 10362 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5886 "PrintCLike.cpp.template"
                                                              print(thiz());
                                                            #line 10367 "PrintCLike.cpp"
  append(L"end = e");
                                                            #line 5887 "PrintCLike.cpp.template"
                                                              print(semicolon());
                                                              if (hasBacktracking)
                                                              {
                                                            #line 10373 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5891 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 10378 "PrintCLike.cpp"
  append(L"ex = -1");
                                                            #line 5892 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                if (memoization)
                                                                {
                                                                  if (isJavascript() || isTypescript())
                                                                  {
                                                            #line 10386 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5898 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 10391 "PrintCLike.cpp"
  append(L"memo = {};");
                                                            #line 5899 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isCSharp())
                                                                  {
                                                            #line 10397 "PrintCLike.cpp"
  append(L"\n");
  append(L"  memo.Clear();");
                                                            #line 5903 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isScala())
                                                                  {
                                                            #line 10404 "PrintCLike.cpp"
  append(L"\n");
  append(L"  memo.clear()");
                                                            #line 5907 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isHaxe())
                                                                  {
                                                            #line 10411 "PrintCLike.cpp"
  append(L"\n");
  append(L"  memo = new Map();");
                                                            #line 5911 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isGo())
                                                                  {
                                                            #line 10418 "PrintCLike.cpp"
  append(L"\n");
  append(L"  this.memo = make(map[int]int)");
                                                            #line 5915 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isPython())
                                                                  {
                                                            #line 10425 "PrintCLike.cpp"
  append(L"\n");
  append(L"  self.memo = {}");
                                                            #line 5919 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 10432 "PrintCLike.cpp"
  append(L"\n");
  append(L"  memo.clear();");
                                                            #line 5923 "PrintCLike.cpp.template"
                                                                  }
                                                                }
                                                                if (grammar->noThrow)
                                                                {
                                                            #line 10440 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5928 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 10445 "PrintCLike.cpp"
  append(L"viable = ");
                                                            #line 5929 "PrintCLike.cpp.template"
                                                                  if (isPython())
                                                                  {
                                                            #line 10450 "PrintCLike.cpp"
  append(L"T");
                                                            #line 5931 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 10456 "PrintCLike.cpp"
  append(L"t");
                                                            #line 5934 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 10460 "PrintCLike.cpp"
  append(L"rue");
                                                            #line 5935 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                              }
                                                              if (tree && ! useGlr)
                                                              {
                                                            #line 10468 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5941 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 10473 "PrintCLike.cpp"
  append(L"eventHandler");
                                                            #line 5942 "PrintCLike.cpp.template"
                                                                if (isTypescript() && isLrParser) print(L"!");
                                                                print(arrow());
                                                                if (isGo())
                                                                {
                                                            #line 10480 "PrintCLike.cpp"
  append(L"R");
                                                            #line 5946 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 10486 "PrintCLike.cpp"
  append(L"r");
                                                            #line 5949 "PrintCLike.cpp.template"
                                                                }
                                                            #line 10490 "PrintCLike.cpp"
  append(L"eset(");
                                                            #line 5950 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 10494 "PrintCLike.cpp"
  append(L"input)");
                                                            #line 5951 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                              }
                                                              if (useGlr)
                                                              {
                                                            #line 10501 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5956 "PrintCLike.cpp.template"
                                                                if (isCSharp() || isCpp() || isHaxe() || isScala() || isTypescript() || isGo())
                                                                {
                                                                  print(thiz());
                                                            #line 10508 "PrintCLike.cpp"
  append(L"parser");
                                                            #line 5959 "PrintCLike.cpp.template"
                                                                  print(arrow());
                                                                }
                                                            #line 10513 "PrintCLike.cpp"
  append(L"maxId = 0");
                                                            #line 5961 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 10517 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5963 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 10522 "PrintCLike.cpp"
  append(L"id = ");
                                                            #line 5964 "PrintCLike.cpp.template"
                                                                if (isCSharp() || isCpp() || isHaxe() || isScala() || isTypescript() || isGo())
                                                                {
                                                                  print(thiz());
                                                            #line 10528 "PrintCLike.cpp"
  append(L"parser");
                                                            #line 5967 "PrintCLike.cpp.template"
                                                                  print(arrow());
                                                                }
                                                            #line 10533 "PrintCLike.cpp"
  append(L"maxId");
                                                            #line 5969 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                              }
                                                              print(rightBrace());
                                                              if (isJavascript() && useGlr)
                                                              {
                                                            #line 10541 "PrintCLike.cpp"
  append(L";");
                                                            #line 5974 "PrintCLike.cpp.template"
                                                              }
                                                            #line 10545 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5976 "PrintCLike.cpp.template"
                                                              if (useGlr || isJavascript() || isTypescript() || isHaxe() || isGo() || isPython())
                                                              {
                                                              }
                                                              else
                                                              {
                                                                openMethod(voidType(), L"", L"reset", L"");
                                                                print(leftBrace());
                                                            #line 10555 "PrintCLike.cpp"
  append(L"\n");
  append(L"  reset(0, 0, 0)");
                                                            #line 5984 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                print(rightBrace());
                                                            #line 10561 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5987 "PrintCLike.cpp.template"
                                                              }
                                                              if (! isGo())
                                                                decreaseIndent();
                                                              // end of reset()
                                                            }

                                                            void PrintCLike::printASICall(Node *node)
                                                            {
                                                              Trace("PrintCLike::printASICall");

                                                              if (node->automaticSemicolonInsertion)
                                                              {
                                                                lineBuffer.clear();
                                                                Production *p = grammar->stringByName.byStringValue(L";");
                                                                Token::Code semicolonToken = p == 0 ? -1 : p->tokenCode;
                                                                TokenSequenceSet tss;
                                                                switch (node->automaticSemicolonInsertion)
                                                                {
                                                                case PLUSPLUS:
                                                                case MINUSMINUS:
                                                                  {
                                                                    p = grammar->stringByName.byStringValue(L"++");
                                                                    Token::Code plusplus = p == 0 ? -1 : p->tokenCode;
                                                                    p = grammar->stringByName.byStringValue(L"--");
                                                                    Token::Code minusminus = p == 0 ? -1 : p->tokenCode;
                                                            #line 10589 "PrintCLike.cpp"
  append(L"\n");
  append(L"if ");
                                                            #line 6013 "PrintCLike.cpp.template"
                                                                    print(ifLeftParen());
                                                            #line 10594 "PrintCLike.cpp"
  append(L"(");
                                                            #line 6014 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                                    print(token());
                                                            #line 10599 "PrintCLike.cpp"
  append(L" == ");
                                                            #line 6016 "PrintCLike.cpp.template"
                                                                    print(format.toString<wchar_t>(grammar->externalTokenCode[plusplus]));
                                                                    if (isPython())
                                                                    {
                                                            #line 10605 "PrintCLike.cpp"
  append(L" or ");
                                                            #line 6019 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 10611 "PrintCLike.cpp"
  append(L" || ");
                                                            #line 6022 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(thiz());
                                                                    print(token());
                                                            #line 10617 "PrintCLike.cpp"
  append(L" == ");
                                                            #line 6025 "PrintCLike.cpp.template"
                                                                    print(format.toString<wchar_t>(grammar->externalTokenCode[minusminus]));
                                                            #line 10621 "PrintCLike.cpp"
  append(L")");
                                                            #line 6026 "PrintCLike.cpp.template"
                                                                    if (isPython())
                                                                    {
                                                            #line 10626 "PrintCLike.cpp"
  append(L" and ");
                                                            #line 6028 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 10632 "PrintCLike.cpp"
  append(L" && ");
                                                            #line 6031 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(thiz());
                                                            #line 10637 "PrintCLike.cpp"
  append(L"followsLineTerminator");
                                                            #line 6033 "PrintCLike.cpp.template"
                                                                    if (! isScala())
                                                                    {
                                                            #line 10642 "PrintCLike.cpp"
  append(L"()");
                                                            #line 6035 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(ifRightParen());
                                                                    tss.insert(grammar->tokenSequence(plusplus));
                                                                    tss.insert(grammar->tokenSequence(minusminus));
                                                                  }
                                                                  break;
                                                                case CONTINUE:
                                                                case BREAK:
                                                                case RETURN:
                                                                case THROW:
                                                                  {
                                                            #line 10656 "PrintCLike.cpp"
  append(L"\n");
  append(L"if ");
                                                            #line 6047 "PrintCLike.cpp.template"
                                                                    print(ifLeftParen());
                                                                    print(thiz());
                                                                    print(token());
                                                            #line 10663 "PrintCLike.cpp"
  append(L" != ");
                                                            #line 6050 "PrintCLike.cpp.template"
                                                                    print(format.toString<wchar_t>(grammar->externalTokenCode[semicolonToken]));
                                                                    if (isPython())
                                                                    {
                                                            #line 10669 "PrintCLike.cpp"
  append(L" and ");
                                                            #line 6053 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 10675 "PrintCLike.cpp"
  append(L" && ");
                                                            #line 6056 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(thiz());
                                                                    print(token());
                                                            #line 10681 "PrintCLike.cpp"
  append(L" >= 0");
                                                            #line 6059 "PrintCLike.cpp.template"
                                                                    if (isPython())
                                                                    {
                                                            #line 10686 "PrintCLike.cpp"
  append(L" and ");
                                                            #line 6061 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 10692 "PrintCLike.cpp"
  append(L" && ");
                                                            #line 6064 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(thiz());
                                                            #line 10697 "PrintCLike.cpp"
  append(L"followsLineTerminator");
                                                            #line 6066 "PrintCLike.cpp.template"
                                                                    if (! isScala())
                                                                    {
                                                            #line 10702 "PrintCLike.cpp"
  append(L"()");
                                                            #line 6068 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(ifRightParen());
                                                                    tss.insert(grammar->tokenSequence(semicolonToken));
                                                                  }
                                                                  break;
                                                                case SEMICOLON:
                                                                  {
                                                                    const bool afterRbrace = false;
                                                                    p = grammar->terminalByName.byNodeType(EndOfFile().getNodeType());
                                                                    Token::Code eof = p == 0 ? -1 : p->tokenCode;
                                                                    p = grammar->stringByName.byStringValue(L"}");
                                                                    Token::Code rbrace = p == 0 ? -1 : p->tokenCode;
                                                            #line 10717 "PrintCLike.cpp"
  append(L"\n");
  append(L"if ");
                                                            #line 6081 "PrintCLike.cpp.template"
                                                                    print(isPython() ? L"(" : ifLeftParen());
                                                                    print(thiz());
                                                                    print(token());
                                                            #line 10724 "PrintCLike.cpp"
  append(L" == ");
                                                            #line 6084 "PrintCLike.cpp.template"
                                                                    print(format.toString<wchar_t>(grammar->externalTokenCode[rbrace]));
                                                                    if (isPython())
                                                                    {
                                                            #line 10730 "PrintCLike.cpp"
  append(L" or");
                                                            #line 6087 "PrintCLike.cpp.template"
                                                                    }
                                                                    else if (isGo())
                                                                    {
                                                            #line 10736 "PrintCLike.cpp"
  append(L" ||");
                                                            #line 6090 "PrintCLike.cpp.template"
                                                                    }
                                                                    printCodeSequenceAnnotation(grammar->tokenSequence(rbrace));
                                                                    if (isGo() || isPython())
                                                                    {
                                                            #line 10743 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 6095 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 10750 "PrintCLike.cpp"
  append(L"\n");
  append(L" || ");
                                                            #line 6099 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(thiz());
                                                                    print(token());
                                                            #line 10757 "PrintCLike.cpp"
  append(L" == ");
                                                            #line 6102 "PrintCLike.cpp.template"
                                                                    print(format.toString<wchar_t>(grammar->externalTokenCode[eof]));
                                                                    if (isPython())
                                                                    {
                                                            #line 10763 "PrintCLike.cpp"
  append(L" or");
                                                            #line 6105 "PrintCLike.cpp.template"
                                                                    }
                                                                    else if (isGo())
                                                                    {
                                                            #line 10769 "PrintCLike.cpp"
  append(L" ||");
                                                            #line 6108 "PrintCLike.cpp.template"
                                                                    }
                                                                    printCodeSequenceAnnotation(grammar->tokenSequence(eof));
                                                                    if (isGo() || isPython())
                                                                    {
                                                            #line 10776 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 6113 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 10783 "PrintCLike.cpp"
  append(L"\n");
  append(L" || ");
                                                            #line 6117 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(thiz());
                                                                    print(token());
                                                            #line 10790 "PrintCLike.cpp"
  append(L" != ");
                                                            #line 6120 "PrintCLike.cpp.template"
                                                                    print(format.toString<wchar_t>(grammar->externalTokenCode[semicolonToken]));
                                                                    if (isPython())
                                                                    {
                                                            #line 10796 "PrintCLike.cpp"
  append(L" and ");
                                                            #line 6123 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 10802 "PrintCLike.cpp"
  append(L" && ");
                                                            #line 6126 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(thiz());
                                                                    print(token());
                                                            #line 10808 "PrintCLike.cpp"
  append(L" >= 0");
                                                            #line 6129 "PrintCLike.cpp.template"
                                                                    if (isPython())
                                                                    {
                                                            #line 10813 "PrintCLike.cpp"
  append(L" and ");
                                                            #line 6131 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 10819 "PrintCLike.cpp"
  append(L" && ");
                                                            #line 6134 "PrintCLike.cpp.template"
                                                                    }
                                                                    if (afterRbrace)
                                                                    {
                                                            #line 10825 "PrintCLike.cpp"
  append(L"(");
                                                            #line 6137 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(thiz());
                                                            #line 10830 "PrintCLike.cpp"
  append(L"followsLineTerminator");
                                                            #line 6139 "PrintCLike.cpp.template"
                                                                    if (! isScala())
                                                                    {
                                                            #line 10835 "PrintCLike.cpp"
  append(L"()");
                                                            #line 6141 "PrintCLike.cpp.template"
                                                                    }
                                                                    if (afterRbrace)
                                                                    {
                                                                      if (isPython())
                                                                      {
                                                            #line 10843 "PrintCLike.cpp"
  append(L" || ");
                                                            #line 6146 "PrintCLike.cpp.template"
                                                                      }
                                                                      else
                                                                      {
                                                            #line 10849 "PrintCLike.cpp"
  append(L" or ");
                                                            #line 6149 "PrintCLike.cpp.template"
                                                                      }
                                                                      if (isCpp() || isCSharp() || isPython() || (isJava() && codepoints))
                                                                      {
                                                                        print(thiz());
                                                            #line 10856 "PrintCLike.cpp"
  append(L"input[");
                                                            #line 6153 "PrintCLike.cpp.template"
                                                                        print(thiz());
                                                            #line 10860 "PrintCLike.cpp"
  append(L"b0]");
                                                            #line 6154 "PrintCLike.cpp.template"
                                                                      }
                                                                      else
                                                                      {
                                                                        print(thiz());
                                                            #line 10867 "PrintCLike.cpp"
  append(L"input.char");
                                                            #line 6158 "PrintCLike.cpp.template"
                                                                        if (isTypescript() || isJavascript() || isHaxe())
                                                                        {
                                                            #line 10872 "PrintCLike.cpp"
  append(L"Code");
                                                            #line 6160 "PrintCLike.cpp.template"
                                                                        }
                                                            #line 10876 "PrintCLike.cpp"
  append(L"At(");
                                                            #line 6161 "PrintCLike.cpp.template"
                                                                        print(thiz());
                                                            #line 10880 "PrintCLike.cpp"
  append(L"b0)");
                                                            #line 6163 "PrintCLike.cpp.template"
                                                                      }
                                                            #line 10884 "PrintCLike.cpp"
  append(L" == 0x7D)");
                                                            #line 6164 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(isPython() ? L"):" : ifRightParen());
                                                                  }
                                                                  break;
                                                                default:
                                                                  internalerr();
                                                                }
                                                                print(isScala() || isGo() ? L" { ": L" ");
                                                                if (! tss.empty()) printCodeSequenceAnnotation(tss);
                                                                print(isScala() || isGo() || isPython() ? L"": L"\n{");
                                                            #line 10897 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 6175 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 10902 "PrintCLike.cpp"
  append(L"l1 = ");
                                                            #line 6176 "PrintCLike.cpp.template"
                                                                print(format.toString<wchar_t>(grammar->externalTokenCode[semicolonToken]));
                                                                print(semicolon());
                                                            #line 10907 "PrintCLike.cpp"
  append(L" ");
                                                            #line 6178 "PrintCLike.cpp.template"
                                                                printCodeSequenceAnnotation(grammar->tokenSequence(semicolonToken));
                                                            #line 10911 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 6180 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 10916 "PrintCLike.cpp"
  append(L"e1 = ");
                                                            #line 6181 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 10920 "PrintCLike.cpp"
  append(L"b1");
                                                            #line 6182 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 10924 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 6184 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 10929 "PrintCLike.cpp"
  append(L"end = ");
                                                            #line 6185 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 10933 "PrintCLike.cpp"
  append(L"e1");
                                                            #line 6186 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                print(rightBrace());
                                                              }
                                                            }

// End
