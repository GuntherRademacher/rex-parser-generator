// This file was generated on Tue Oct 20, 2026 19:55 (UTC+02) by REx v6.3-SNAPSHOT which is Copyright (c) 1979-2026 by Gunther Rademacher <grd@gmx.net>
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
                                                                  print(stringIntroducer());
                                                            #line 2159 "PrintCLike.cpp"
  append(L"\"");
                                                            #line 1555 "PrintCLike.cpp.template"
                                                                  print(node->name);
                                                            #line 2163 "PrintCLike.cpp"
  append(L"\", ");
                                                            #line 1556 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 2167 "PrintCLike.cpp"
  append(L"e0)");
                                                            #line 1557 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                                visitNodeList(node->firstChild);

                                                                if (tree && methodPrefix != methodPrefixTry)
                                                                {
                                                            #line 2176 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 1564 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 2181 "PrintCLike.cpp"
  append(L"eventHandler");
                                                            #line 1565 "PrintCLike.cpp.template"
                                                                  print(arrow());
                                                                  if (isGo())
                                                                  {
                                                            #line 2187 "PrintCLike.cpp"
  append(L"E");
                                                            #line 1568 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 2193 "PrintCLike.cpp"
  append(L"e");
                                                            #line 1571 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 2197 "PrintCLike.cpp"
  append(L"ndNonterminal(");
                                                            #line 1572 "PrintCLike.cpp.template"
                                                                  print(stringIntroducer());
                                                            #line 2201 "PrintCLike.cpp"
  append(L"\"");
                                                            #line 1573 "PrintCLike.cpp.template"
                                                                  print(node->name);
                                                            #line 2205 "PrintCLike.cpp"
  append(L"\", ");
                                                            #line 1574 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 2209 "PrintCLike.cpp"
  append(L"e0)");
                                                            #line 1575 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                                if (trace)
                                                                {
                                                            #line 2216 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 1580 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 2221 "PrintCLike.cpp"
  append(L"traceNonterminal(");
                                                            #line 1581 "PrintCLike.cpp.template"
                                                                  print(stringIntroducer());
                                                            #line 2225 "PrintCLike.cpp"
  append(L"\"");
                                                            #line 1582 "PrintCLike.cpp.template"
                                                                  print(methodPrefix, wcslen(methodPrefix) - 1);
                                                            #line 2229 "PrintCLike.cpp"
  append(L"\", ");
                                                            #line 1583 "PrintCLike.cpp.template"
                                                                  print(stringIntroducer());
                                                            #line 2233 "PrintCLike.cpp"
  append(L"\"end\", ");
                                                            #line 1584 "PrintCLike.cpp.template"
                                                                  print(stringIntroducer());
                                                            #line 2237 "PrintCLike.cpp"
  append(L"\"");
                                                            #line 1585 "PrintCLike.cpp.template"
                                                                  print(node->name);
                                                            #line 2241 "PrintCLike.cpp"
  append(L"\")");
                                                            #line 1586 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                              }
                                                              if (node->isStartSymbol())
                                                              {
                                                                printFlush(1);
                                                              }
                                                              if (isGo() && node->isStartSymbol())
                                                              {
                                                            #line 2253 "PrintCLike.cpp"
  append(L"\n");
  append(L"  return nil");
                                                            #line 1596 "PrintCLike.cpp.template"
                                                              }
                                                              print(rightBrace());
                                                              if ((isJavascript()  && ! isTypescript()) && node->isStartSymbol())
                                                              {
                                                            #line 2261 "PrintCLike.cpp"
  append(L";");
                                                            #line 1600 "PrintCLike.cpp.template"
                                                              }
                                                            #line 2265 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 1602 "PrintCLike.cpp.template"
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
                                                            #line 2288 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 1623 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 2292 "PrintCLike.cpp"
  append(L"whitespace");
                                                            #line 1624 "PrintCLike.cpp.template"
                                                                  if (! isScala())
                                                                  {
                                                            #line 2297 "PrintCLike.cpp"
  append(L"()");
                                                            #line 1626 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(semicolon());
                                                                }
                                                                if (   hasBacktracking
                                                                    && grammar->noThrow
                                                                    && methodPrefix == methodPrefixTry)
                                                                {
                                                            #line 2307 "PrintCLike.cpp"
  append(L"\n");
  append(L"if ");
                                                            #line 1634 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                                  print(thiz());
                                                            #line 2313 "PrintCLike.cpp"
  append(L"viable");
                                                            #line 1636 "PrintCLike.cpp.template"
                                                                  print(ifRightParen());
                                                                  print(leftBrace());
                                                                  increaseIndent();
                                                                }
                                                            #line 2320 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 1641 "PrintCLike.cpp.template"
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
                                                            #line 2345 "PrintCLike.cpp"
  append(L"()");
                                                            #line 1663 "PrintCLike.cpp.template"
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
                                                            #line 2375 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 1691 "PrintCLike.cpp.template"
                                                                int spaces = isPython() ? 0 : Math::max(0, static_cast<int>(piIndent) - getIndent());
                                                                print(spaces, L" ");
                                                                print(lineCommentPrefix());
                                                            #line 2381 "PrintCLike.cpp"
  append(L"line ");
                                                            #line 1694 "PrintCLike.cpp.template"
                                                                print(format.toString<wchar_t>(node->line));
                                                            #line 2385 "PrintCLike.cpp"
  append(L" \"");
                                                            #line 1695 "PrintCLike.cpp.template"
                                                                print(node->fileName);
                                                            #line 2389 "PrintCLike.cpp"
  append(L"\"\n");
                                                            #line 1697 "PrintCLike.cpp.template"
                                                                print(spaces, L" ");
                                                                wchar_t *reIndented = format.reIndent(node->content, spaces);
                                                                print(reIndented);
                                                            #line 2395 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 1701 "PrintCLike.cpp.template"
                                                                free(reIndented);
                                                                print(spaces, L" ");
                                                                print(lineCommentPrefix());
                                                            #line 2401 "PrintCLike.cpp"
  append(L"line ");
                                                            #line 1704 "PrintCLike.cpp.template"
                                                                print(format.toString<wchar_t>(lineNo + 1));
                                                            #line 2405 "PrintCLike.cpp"
  append(L" \"");
                                                            #line 1705 "PrintCLike.cpp.template"
                                                                print(wFileName.c_str());
                                                            #line 2409 "PrintCLike.cpp"
  append(L"\"");
                                                            #line 1706 "PrintCLike.cpp.template"
                                                              }
                                                            }

                                                            void PrintCLike::printProlog()
                                                            {
                                                              Trace("PrintCLike::printProlog");

                                                              if (! isGo())
                                                                increaseIndent();
                                                              if (isJavascript())
                                                              {
                                                            #line 2423 "PrintCLike.cpp"
  append(L"\n");
  append(L"function init(source");
                                                            #line 1718 "PrintCLike.cpp.template"
                                                                if (noLexer)
                                                                {
                                                            #line 2429 "PrintCLike.cpp"
  append(L", l");
                                                            #line 1720 "PrintCLike.cpp.template"
                                                                }
                                                                if (tree)
                                                                {
                                                            #line 2435 "PrintCLike.cpp"
  append(L", parsingEventHandler");
                                                            #line 1723 "PrintCLike.cpp.template"
                                                                }
                                                            #line 2439 "PrintCLike.cpp"
  append(L")");
                                                            #line 1724 "PrintCLike.cpp.template"
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
                                                            #line 2472 "PrintCLike.cpp"
  append(L"\n");
  append(L"  initialize(source.codePoints().toArray()");
                                                            #line 1755 "PrintCLike.cpp.template"
                                                                  if (tree)
                                                                  {
                                                            #line 2478 "PrintCLike.cpp"
  append(L", parsingEventHandler");
                                                            #line 1757 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 2482 "PrintCLike.cpp"
  append(L");");
                                                            #line 1758 "PrintCLike.cpp.template"
                                                                  print(rightBrace());
                                                            #line 2486 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 1760 "PrintCLike.cpp.template"
                                                                }
                                                                openMethod(voidType(), L"", L"initialize", args.c_str());
                                                              }
                                                              print(leftBrace());
                                                              if (tree)
                                                              {
                                                            #line 2495 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 1767 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 2500 "PrintCLike.cpp"
  append(L"eventHandler = parsingEventHandler");
                                                            #line 1768 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                              }
                                                            #line 2505 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 1771 "PrintCLike.cpp.template"
                                                              print(thiz());
                                                            #line 2510 "PrintCLike.cpp"
  append(L"input = ");
                                                            #line 1772 "PrintCLike.cpp.template"
                                                              if (isHaxe())
                                                              {
                                                            #line 2515 "PrintCLike.cpp"
  append(L"Bytes.ofString(source)");
                                                            #line 1774 "PrintCLike.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 2521 "PrintCLike.cpp"
  append(L"source");
                                                            #line 1777 "PrintCLike.cpp.template"
                                                              }
                                                              print(semicolon());
                                                              if (noLexer)
                                                              {
                                                            #line 2528 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 1782 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 2533 "PrintCLike.cpp"
  append(L"lexer = l");
                                                            #line 1783 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 2537 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 1785 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 2542 "PrintCLike.cpp"
  append(L"lexer.reset(input)");
                                                            #line 1786 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                              }
                                                              else if (isGo() || isPython())
                                                              {
                                                            #line 2549 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 1791 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 2554 "PrintCLike.cpp"
  append(L"size = len(source)");
                                                            #line 1792 "PrintCLike.cpp.template"
                                                              }
                                                              else if (! isCpp())
                                                              {
                                                            #line 2560 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 1796 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 2565 "PrintCLike.cpp"
  append(L"size = source.");
                                                            #line 1797 "PrintCLike.cpp.template"
                                                                print(isCSharp() ? L"L" : L"l");
                                                            #line 2569 "PrintCLike.cpp"
  append(L"ength");
                                                            #line 1798 "PrintCLike.cpp.template"
                                                                if (! isJavascript() && ! isTypescript() && ! isScala() && ! isHaxe() && ! isCSharp() && ! (isJava() && codepoints))
                                                                {
                                                            #line 2574 "PrintCLike.cpp"
  append(L"()");
                                                            #line 1800 "PrintCLike.cpp.template"
                                                                }
                                                                print(semicolon());
                                                              }
                                                              if (! interfaceName.empty() && useGlr)
                                                              {
                                                            #line 2582 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 1806 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                                print(isGo() ? L"R" : L"r");
                                                            #line 2588 "PrintCLike.cpp"
  append(L"eset()");
                                                            #line 1808 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                print(rightBrace());
                                                            #line 2593 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 1811 "PrintCLike.cpp.template"
                                                                openMethod(voidType(), L"", L"reset", L"");
                                                                print(leftBrace());
                                                              }
                                                              if (isLrParser && ! useGlr)
                                                              {
                                                                if (isPython())
                                                                {
                                                            #line 2603 "PrintCLike.cpp"
  append(L"\n");
  append(L"  self.iStack = [0 for _ in range(192)]");
                                                            #line 1819 "PrintCLike.cpp.template"
                                                                }
                                                                else if (isGo())
                                                                {
                                                            #line 2610 "PrintCLike.cpp"
  append(L"\n");
  append(L"  this.iStack = make([]int, 192)\n");
  append(L"  this.top = -1");
                                                            #line 1824 "PrintCLike.cpp.template"
                                                                }
                                                              }
                                                              if (useGlr)
                                                              {
                                                            #line 2619 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 1829 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 2624 "PrintCLike.cpp"
  append(L"maxId = 0");
                                                            #line 1830 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 2628 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 1832 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 2633 "PrintCLike.cpp"
  append(L"thread = ");
                                                            #line 1833 "PrintCLike.cpp.template"
                                                                if (isScala())
                                                                {
                                                            #line 2638 "PrintCLike.cpp"
  append(L"new ");
                                                            #line 1835 "PrintCLike.cpp.template"
                                                                  print(className.c_str());
                                                            #line 2642 "PrintCLike.cpp"
  append(L".ParsingThread");
                                                            #line 1836 "PrintCLike.cpp.template"
                                                                }
                                                                else if (isPython())
                                                                {
                                                                  print(className.c_str());
                                                            #line 2649 "PrintCLike.cpp"
  append(L".ParsingThread()");
                                                            #line 1840 "PrintCLike.cpp.template"
                                                                }
                                                                else if (isGo())
                                                                {
                                                            #line 2655 "PrintCLike.cpp"
  append(L"new(ParsingThread)");
                                                            #line 1843 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 2661 "PrintCLike.cpp"
  append(L"new ParsingThread()");
                                                            #line 1846 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                                if (isCSharp() || isCpp() || isHaxe() || isScala() || isTypescript() || isGo() || isPython())
                                                                {
                                                            #line 2668 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 1851 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 2673 "PrintCLike.cpp"
  append(L"thread");
                                                            #line 1852 "PrintCLike.cpp.template"
                                                                  print(arrow());
                                                            #line 2677 "PrintCLike.cpp"
  append(L"parser = ");
                                                            #line 1853 "PrintCLike.cpp.template"
                                                                  if (isPython())
                                                                  {
                                                            #line 2682 "PrintCLike.cpp"
  append(L"self");
                                                            #line 1855 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 2688 "PrintCLike.cpp"
  append(L"this");
                                                            #line 1858 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(semicolon());
                                                                }
                                                            #line 2694 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 1862 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 2699 "PrintCLike.cpp"
  append(L"thread");
                                                            #line 1863 "PrintCLike.cpp.template"
                                                                print(arrow());
                                                              }
                                                              else
                                                              {
                                                            #line 2706 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 1868 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                              }
                                                              print(isGo() ? L"R" : L"r");
                                                            #line 2713 "PrintCLike.cpp"
  append(L"eset(0, 0, 0)");
                                                            #line 1871 "PrintCLike.cpp.template"
                                                              print(semicolon());
                                                              print(rightBrace());
                                                            #line 2718 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 1874 "PrintCLike.cpp.template"
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
                                                            #line 2731 "PrintCLike.cpp"
  append(L"\n");
  append(L"this.reset = function(l, b, e)\n");
  append(L"{\n");
  append(L"  ");
                                                            #line 1887 "PrintCLike.cpp.template"
                                                                if (useGlr)
                                                                {
                                                            #line 2739 "PrintCLike.cpp"
  append(L"thread.");
                                                            #line 1889 "PrintCLike.cpp.template"
                                                                }
                                                            #line 2743 "PrintCLike.cpp"
  append(L"reset(l, b, e);\n");
  append(L"};\n");
                                                            #line 1892 "PrintCLike.cpp.template"
                                                                openMethod(L"static ", stringType(), L"getOffendingToken", L"ParseException e");
                                                                print(leftBrace());
                                                            #line 2749 "PrintCLike.cpp"
  append(L"\n");
  append(L"  var o = e.getOffending();\n");
  append(L"  return o >= 0 ? ");
                                                            #line 1896 "PrintCLike.cpp.template"
                                                                print(staticPrefix());
                                                            #line 2755 "PrintCLike.cpp"
  append(L"TOKEN[o] : ");
                                                            #line 1897 "PrintCLike.cpp.template"
                                                                print(nullPtr());
                                                            #line 2759 "PrintCLike.cpp"
  append(L";\n");
  append(L"};\n");
                                                            #line 1900 "PrintCLike.cpp.template"
                                                              }
                                                              else if (isTypescript())
                                                              {
                                                                if (useGlr)
                                                                {
                                                            #line 2768 "PrintCLike.cpp"
  append(L"\n");
  append(L"public reset(l: number, b: number, e: number)\n");
  append(L"{\n");
  append(L"  this.thread.reset(l, b, e);\n");
  append(L"}\n");
                                                            #line 1910 "PrintCLike.cpp.template"
                                                                }
                                                            #line 2776 "PrintCLike.cpp"
  append(L"\n");
  append(L"getOffendingToken(e: ParseException)\n");
  append(L"{");
  append(L"\n");
  append(L"  var o = e.getOffending();\n");
  append(L"  return o >= 0 ? Parser.TOKEN[o] : ");
                                                            #line 1916 "PrintCLike.cpp.template"
                                                                print(nullPtr());
                                                            #line 2785 "PrintCLike.cpp"
  append(L";\n");
  append(L"}\n");
                                                            #line 1919 "PrintCLike.cpp.template"
                                                              }
                                                              else if (isScala())
                                                              {
                                                              }
                                                              else if (isGo())
                                                              {
                                                            #line 2795 "PrintCLike.cpp"
  append(L"\n");
  append(L"func GetOffendingToken(e ParseError) string {\n");
  append(L"  if e.GetOffending() < 0 {\n");
  append(L"    return \"\"\n");
  append(L"  } else {\n");
  append(L"    return token[e.GetOffending()]\n");
  append(L"  }\n");
  append(L"}\n");
                                                            #line 1933 "PrintCLike.cpp.template"
                                                              }
                                                              else if (isPython())
                                                              {
                                                            #line 2808 "PrintCLike.cpp"
  append(L"\n");
  append(L"@staticmethod\n");
  append(L"def getOffendingToken(e):\n");
  append(L"  if e.getOffending() < 0:\n");
  append(L"    return \"\"\n");
  append(L"  else:\n");
  append(L"    return ");
                                                            #line 1942 "PrintCLike.cpp.template"
                                                                print(className.c_str());
                                                            #line 2818 "PrintCLike.cpp"
  append(L".TOKEN[e.getOffending()]\n");
                                                            #line 1944 "PrintCLike.cpp.template"
                                                              }
                                                              else
                                                              {
                                                                openMethod(stringType(), L"static ", L"getOffendingToken", L"ParseException e");
                                                                print(leftBrace());
                                                            #line 2826 "PrintCLike.cpp"
  append(L"\n");
  append(L"  return e.getOffending() < 0 ? ");
                                                            #line 1950 "PrintCLike.cpp.template"
                                                                print(nullPtr());
                                                            #line 2831 "PrintCLike.cpp"
  append(L" : TOKEN[e.getOffending()];");
                                                            #line 1951 "PrintCLike.cpp.template"
                                                                print(rightBrace());
                                                            #line 2835 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 1953 "PrintCLike.cpp.template"
                                                              }

                                                              if (isJavascript() || isTypescript() || isHaxe())
                                                              {
                                                                openMethod(L"", L"static ", L"getExpectedTokenSet", L"ParseException e");
                                                                print(leftBrace());
                                                            #line 2844 "PrintCLike.cpp"
  append(L"\n");
  append(L"  var expected");
                                                            #line 1960 "PrintCLike.cpp.template"
                                                                if (isTypescript())
                                                                {
                                                            #line 2850 "PrintCLike.cpp"
  append(L": string[]");
                                                            #line 1962 "PrintCLike.cpp.template"
                                                                }
                                                            #line 2854 "PrintCLike.cpp"
  append(L";\n");
  append(L"  if (e.getExpected() < 0)\n");
  append(L"  {\n");
  append(L"    expected = ");
                                                            #line 1966 "PrintCLike.cpp.template"
                                                                print(staticPrefix());
                                                            #line 2861 "PrintCLike.cpp"
  append(L"getTokenSet(- e.getState());\n");
  append(L"  }\n");
  append(L"  else\n");
  append(L"  {\n");
  append(L"    expected = [");
                                                            #line 1971 "PrintCLike.cpp.template"
                                                                print(staticPrefix());
                                                                print(isGo() ? L"token" : L"TOKEN");
                                                            #line 2870 "PrintCLike.cpp"
  append(L"[e.getExpected()]];\n");
  append(L"  }\n");
  append(L"  return expected;\n");
  append(L"}");
                                                            #line 1976 "PrintCLike.cpp.template"
                                                                if (! isTypescript())
                                                                {
                                                            #line 2878 "PrintCLike.cpp"
  append(L";");
                                                            #line 1978 "PrintCLike.cpp.template"
                                                                }
                                                            #line 2882 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 1980 "PrintCLike.cpp.template"
                                                                if (isHaxe())
                                                                {
                                                            #line 2887 "PrintCLike.cpp"
  append(L"\n");
  append(L"public function getErrorMessage(e: ParseException): String");
                                                            #line 1983 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                                  openMethod(stringType(), L"static ", L"getErrorMessage", L"ParseException e");
                                                                }
                                                                print(leftBrace());
                                                            #line 2897 "PrintCLike.cpp"
  append(L"\n");
  append(L"  var message = e.getMessage();");
                                                            #line 1990 "PrintCLike.cpp.template"
                                                                if (useGlr)
                                                                {
                                                                  increaseIndent();
                                                            #line 2904 "PrintCLike.cpp"
  append(L"\n");
  append(L"if ");
                                                            #line 1994 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                            #line 2909 "PrintCLike.cpp"
  append(L"e.isAmbiguousInput()");
                                                            #line 1995 "PrintCLike.cpp.template"
                                                                  print(ifRightParen());
                                                                  print(leftBrace());
                                                            #line 2914 "PrintCLike.cpp"
  append(L"\n");
  append(L"  message += \"\\n\"");
                                                            #line 1998 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                            #line 2919 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 2000 "PrintCLike.cpp.template"
                                                                  print(elseWithBraces());
                                                                }
                                                            #line 2924 "PrintCLike.cpp"
  append(L"\n");
  append(L"  var found = ");
                                                            #line 2003 "PrintCLike.cpp.template"
                                                                if (! isHaxe())
                                                                {
                                                                  print(L"this.");
                                                                }
                                                            #line 2932 "PrintCLike.cpp"
  append(L"getOffendingToken(e);\n");
  append(L"  var tokenSet = ");
                                                            #line 2008 "PrintCLike.cpp.template"
                                                                if (! isHaxe())
                                                                {
                                                                  print(L"this.");
                                                                }
                                                            #line 2940 "PrintCLike.cpp"
  append(L"getExpectedTokenSet(e);\n");
  append(L"  var size = e.getEnd() - e.getBegin();\n");
  append(L"  message += (found == null ? \"\" : \", found \" + found)\n");
  append(L"          + \"\\nwhile expecting \"\n");
  append(L"          + (tokenSet.length == 1 ? tokenSet[0] : (\"[\" + tokenSet.join(\", \") + \"]\"))\n");
  append(L"          + \"\\n\"\n");
  append(L"          + (size == 0 || found != null ? \"\" : \"after successfully scanning \" + size + \" characters beginning \");");
                                                            #line 2019 "PrintCLike.cpp.template"
                                                                if (useGlr)
                                                                {
                                                                  decreaseIndent();
                                                            #line 2952 "PrintCLike.cpp"
  append(L"\n");
  append(L"  }");
                                                            #line 2023 "PrintCLike.cpp.template"
                                                                }
                                                            #line 2957 "PrintCLike.cpp"
  append(L"\n");
  append(L"  var prefix = ");
                                                            #line 2025 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 2962 "PrintCLike.cpp"
  append(L"input.");
                                                            #line 2026 "PrintCLike.cpp.template"
                                                                if (isHaxe())
                                                                {
                                                            #line 2967 "PrintCLike.cpp"
  append(L"getS");
                                                            #line 2028 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 2973 "PrintCLike.cpp"
  append(L"subs");
                                                            #line 2031 "PrintCLike.cpp.template"
                                                                }
                                                            #line 2977 "PrintCLike.cpp"
  append(L"tring(0, e.getBegin());\n");
  append(L"  var lines = prefix.split(\"\\n\");\n");
  append(L"  var line = lines.length;\n");
  append(L"  var column = lines[line - 1].length + 1;\n");
  append(L"  return message\n");
  append(L"       + \"at line \" + line + \", column \" + column + \":\\n...\"\n");
  append(L"       + ");
                                                            #line 2038 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                                if (isHaxe())
                                                                {
                                                            #line 2989 "PrintCLike.cpp"
  append(L"input.getString(e.getBegin(), input.length < e.getBegin() + 64 ? input.length - e.getBegin() : 64");
                                                            #line 2042 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 2995 "PrintCLike.cpp"
  append(L"input.substring(e.getBegin(), Math.min(");
                                                            #line 2045 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 2999 "PrintCLike.cpp"
  append(L"input.length, e.getBegin() + 64)");
                                                            #line 2047 "PrintCLike.cpp.template"
                                                                }
                                                            #line 3003 "PrintCLike.cpp"
  append(L")\n");
  append(L"       + \"...\";\n");
  append(L"}");
                                                            #line 2050 "PrintCLike.cpp.template"
                                                                if (! isTypescript())
                                                                {
                                                            #line 3010 "PrintCLike.cpp"
  append(L";");
                                                            #line 2052 "PrintCLike.cpp.template"
                                                                }
                                                            #line 3014 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 2054 "PrintCLike.cpp.template"
                                                              }
                                                              else if (isJava())
                                                              {
                                                                openMethod(L"String[] ", L"static ", L"getExpectedTokenSet", L"ParseException e");
                                                                print(leftBrace());
                                                            #line 3022 "PrintCLike.cpp"
  append(L"\n");
  append(L"  String[] expected");
                                                            #line 2060 "PrintCLike.cpp.template"
                                                                if (useGlr)
                                                                {
                                                            #line 3028 "PrintCLike.cpp"
  append(L" = {}");
                                                            #line 2062 "PrintCLike.cpp.template"
                                                                }
                                                            #line 3032 "PrintCLike.cpp"
  append(L";\n");
  append(L"  if (e.getExpected() >= 0)\n");
  append(L"  {\n");
  append(L"    expected = new String[]{TOKEN[e.getExpected()]};\n");
  append(L"  }\n");
  append(L"  else");
                                                            #line 2068 "PrintCLike.cpp.template"
                                                                if (useGlr)
                                                                {
                                                            #line 3042 "PrintCLike.cpp"
  append(L" if (! e.isAmbiguousInput())");
                                                            #line 2070 "PrintCLike.cpp.template"
                                                                }
                                                            #line 3046 "PrintCLike.cpp"
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
                                                            #line 2080 "PrintCLike.cpp.template"
                                                                if (useGlr)
                                                                {
                                                            #line 3060 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if ");
                                                            #line 2083 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                            #line 3065 "PrintCLike.cpp"
  append(L"e.isAmbiguousInput()");
                                                            #line 2084 "PrintCLike.cpp.template"
                                                                  print(ifRightParen());
                                                                  printIndented(1, leftBrace());
                                                            #line 3070 "PrintCLike.cpp"
  append(L"\n");
  append(L"    message += \"\\n\"");
                                                            #line 2087 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                            #line 3075 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 2089 "PrintCLike.cpp.template"
                                                                  printIndented(1, elseWithBraces());
                                                                  increaseIndent();
                                                                }
                                                            #line 3082 "PrintCLike.cpp"
  append(L"\n");
  append(L"  String[] tokenSet = getExpectedTokenSet(e);\n");
  append(L"  String found = getOffendingToken(e);\n");
  append(L"  int size = e.getEnd() - e.getBegin();\n");
  append(L"  message += (found == null ? \"\" : \", found \" + found)\n");
  append(L"          + \"\\nwhile expecting \"\n");
  append(L"          + (tokenSet.length == 1 ? tokenSet[0] : java.util.Arrays.toString(tokenSet))\n");
  append(L"          + \"\\n\"\n");
  append(L"          + (size == 0 || found != null ? \"\" : \"after successfully scanning \" + size + \" characters beginning \");");
                                                            #line 2101 "PrintCLike.cpp.template"
                                                                if (useGlr)
                                                                {
                                                                  decreaseIndent();
                                                            #line 3096 "PrintCLike.cpp"
  append(L"\n");
  append(L"  }");
                                                            #line 2105 "PrintCLike.cpp.template"
                                                                }
                                                                if (codepoints)
                                                                {
                                                            #line 3103 "PrintCLike.cpp"
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
                                                            #line 2117 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 3119 "PrintCLike.cpp"
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
                                                            #line 2129 "PrintCLike.cpp.template"
                                                                }
                                                                if (! interfaceName.empty())
                                                                {
                                                            #line 3135 "PrintCLike.cpp"
  append(L"\n");
  append(L"public void parse()\n");
  append(L"{\n");
  append(L"  parse_");
                                                            #line 2135 "PrintCLike.cpp.template"
                                                                  print(Format::acceptableName<WString>(grammar->startSymbol()->name).c_str());
                                                            #line 3142 "PrintCLike.cpp"
  append(L"();\n");
  append(L"}\n");
                                                            #line 2138 "PrintCLike.cpp.template"
                                                                }
                                                              }
                                                              else if (isCSharp())
                                                              {
                                                                openMethod(L"static String[] ", L"", L"getExpectedTokenSet", L"ParseException e");
                                                                print(leftBrace());
                                                            #line 3152 "PrintCLike.cpp"
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
                                                            #line 2159 "PrintCLike.cpp.template"
                                                                if (useGlr)
                                                                {
                                                            #line 3172 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if (e.isAmbiguousInput())\n");
  append(L"  {\n");
  append(L"    message += \"\\n\";\n");
  append(L"  }\n");
  append(L"  else\n");
  append(L"  {");
                                                            #line 2167 "PrintCLike.cpp.template"
                                                                  increaseIndent();
                                                                }
                                                            #line 3183 "PrintCLike.cpp"
  append(L"\n");
  append(L"  String[] tokenSet = getExpectedTokenSet(e);\n");
  append(L"  String found = getOffendingToken(e);\n");
  append(L"  int size = e.getEnd() - e.getBegin();\n");
  append(L"  message += (found == null ? \"\" : \", found \" + found)\n");
  append(L"          + \"\\nwhile expecting \"\n");
  append(L"          + (tokenSet.Length == 1 ? tokenSet[0] : (\"[\" + String.Join(\", \", tokenSet) + \"]\"))\n");
  append(L"          + \"\\n\"\n");
  append(L"          + (size == 0 || found != null ? \"\" : \"after successfully scanning \" + size + \" characters beginning \");");
                                                            #line 2178 "PrintCLike.cpp.template"
                                                                if (useGlr)
                                                                {
                                                                  decreaseIndent();
                                                            #line 3197 "PrintCLike.cpp"
  append(L"\n");
  append(L"  }");
                                                            #line 2182 "PrintCLike.cpp.template"
                                                                }
                                                            #line 3202 "PrintCLike.cpp"
  append(L"\n");
  append(L"  String prefix = input.Substring(0, e.getBegin());\n");
  append(L"  int line = prefix.Length - prefix.Replace(\"\\n\", \"\").Length + 1;\n");
  append(L"  int column = prefix.Length - prefix.LastIndexOf('\\n');\n");
  append(L"  return message\n");
  append(L"       + \"at line \" + line + \", column \" + column + \":\\n...\"\n");
  append(L"       + input.Substring(e.getBegin(), Math.Min(input.Length, e.getBegin() + 64) - e.getBegin())\n");
  append(L"       + \"...\";\n");
  append(L"}\n");
                                                            #line 2192 "PrintCLike.cpp.template"
                                                                if (! interfaceName.empty())
                                                                {
                                                            #line 3215 "PrintCLike.cpp"
  append(L"\n");
  append(L"public void parse()\n");
  append(L"{\n");
  append(L"  parse_");
                                                            #line 2197 "PrintCLike.cpp.template"
                                                                  print(Format::acceptableName<WString>(grammar->startSymbol()->name).c_str());
                                                            #line 3222 "PrintCLike.cpp"
  append(L"();\n");
  append(L"}\n");
                                                            #line 2200 "PrintCLike.cpp.template"
                                                                }
                                                              }
                                                              else if (isGo())
                                                              {
                                                            #line 3230 "PrintCLike.cpp"
  append(L"\n");
  append(L"func GetExpectedTokenSet(e ParseError) []string {\n");
  append(L"  if e.expected < 0 {\n");
  append(L"    return getTokenSet(- e.state)\n");
  append(L"  } else {\n");
  append(L"    singleton := [...]string {token[e.expected]}\n");
  append(L"    return singleton[:]\n");
  append(L"  }\n");
  append(L"}\n");
  append(L"\n");
  append(L"func (this *");
                                                            #line 2214 "PrintCLike.cpp.template"
                                                                print(className.c_str());
                                                            #line 3244 "PrintCLike.cpp"
  append(L") GetErrorMessage(e ParseError) string {\n");
  append(L"  message := e.Error()");
                                                            #line 2216 "PrintCLike.cpp.template"
                                                                if (useGlr)
                                                                {
                                                            #line 3250 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if e.IsAmbiguousInput() {\n");
  append(L"    message += \"\\n\"\n");
  append(L"  } else {");
                                                            #line 2221 "PrintCLike.cpp.template"
                                                                  increaseIndent();
                                                                }
                                                            #line 3258 "PrintCLike.cpp"
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
                                                            #line 2249 "PrintCLike.cpp.template"
                                                                if (useGlr)
                                                                {
                                                                  decreaseIndent();
                                                            #line 3290 "PrintCLike.cpp"
  append(L"\n");
  append(L"  }");
                                                            #line 2253 "PrintCLike.cpp.template"
                                                                }
                                                            #line 3295 "PrintCLike.cpp"
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
                                                            #line 2278 "PrintCLike.cpp.template"
                                                                if (! interfaceName.empty())
                                                                {
                                                            #line 3323 "PrintCLike.cpp"
  append(L"\n");
  append(L"public void parse()\n");
  append(L"{\n");
  append(L"  parse_");
                                                            #line 2283 "PrintCLike.cpp.template"
                                                                  print(Format::acceptableName<WString>(grammar->startSymbol()->name).c_str());
                                                            #line 3330 "PrintCLike.cpp"
  append(L"();\n");
  append(L"}\n");
                                                            #line 2286 "PrintCLike.cpp.template"
                                                                }
                                                              }
                                                              else if (isPython())
                                                              {
                                                            #line 3338 "PrintCLike.cpp"
  append(L"\n");
  append(L"@staticmethod\n");
  append(L"def getExpectedTokenSet(e):\n");
  append(L"  if e.expected < 0:\n");
  append(L"    return ");
                                                            #line 2294 "PrintCLike.cpp.template"
                                                                print(className.c_str());
                                                            #line 3346 "PrintCLike.cpp"
  append(L".getTokenSet(- e.state)\n");
  append(L"  else:\n");
  append(L"    return [");
                                                            #line 2297 "PrintCLike.cpp.template"
                                                                print(className.c_str());
                                                            #line 3352 "PrintCLike.cpp"
  append(L".TOKEN[e.expected]]\n");
  append(L"\n");
  append(L"def getErrorMessage(self, e):\n");
  append(L"  message = e.error()");
                                                            #line 2301 "PrintCLike.cpp.template"
                                                                if (useGlr)
                                                                {
                                                            #line 3360 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if e.isAmbiguousInput():\n");
  append(L"    message += \"\\n\"\n");
  append(L"  else:");
                                                            #line 2306 "PrintCLike.cpp.template"
                                                                  increaseIndent();
                                                                }
                                                            #line 3368 "PrintCLike.cpp"
  append(L"\n");
  append(L"  found = ");
                                                            #line 2309 "PrintCLike.cpp.template"
                                                                print(className.c_str());
                                                            #line 3373 "PrintCLike.cpp"
  append(L".getOffendingToken(e)\n");
  append(L"  if found != \"\":\n");
  append(L"    message += \", found \"\n");
  append(L"    message += found\n");
  append(L"  expected = ");
                                                            #line 2314 "PrintCLike.cpp.template"
                                                                print(className.c_str());
                                                            #line 3381 "PrintCLike.cpp"
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
                                                            #line 2331 "PrintCLike.cpp.template"
                                                                if (useGlr)
                                                                {
                                                                  decreaseIndent();
                                                                }
                                                            #line 3404 "PrintCLike.cpp"
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
                                                            #line 2355 "PrintCLike.cpp.template"
                                                                if (! interfaceName.empty())
                                                                {
                                                            #line 3428 "PrintCLike.cpp"
  append(L"\n");
  append(L"public void parse()\n");
  append(L"{\n");
  append(L"  parse_");
                                                            #line 2360 "PrintCLike.cpp.template"
                                                                  print(Format::acceptableName<WString>(grammar->startSymbol()->name).c_str());
                                                            #line 3435 "PrintCLike.cpp"
  append(L"();\n");
  append(L"}\n");
                                                            #line 2363 "PrintCLike.cpp.template"
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
                                                            #line 3451 "PrintCLike.cpp"
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
                                                            #line 2386 "PrintCLike.cpp.template"
                                                                print(isGo() ? L"token" : L"TOKEN");
                                                            #line 3466 "PrintCLike.cpp"
  append(L"[e.expected];\n");
  append(L"    set[1] = 0;\n");
  append(L"  }\n");
  append(L"}\n");
  append(L"\n");
  append(L"static std::");
                                                            #line 2392 "PrintCLike.cpp.template"
                                                                if (stringIntroducer()[0]) append(L"w");
                                                            #line 3475 "PrintCLike.cpp"
  append(L"string to_");
                                                            #line 2393 "PrintCLike.cpp.template"
                                                                if (stringIntroducer()[0]) append(L"w");
                                                            #line 3479 "PrintCLike.cpp"
  append(L"string(int i)\n");
  append(L"{\n");
  append(L"  const ");
                                                            #line 2396 "PrintCLike.cpp.template"
                                                                if (stringIntroducer()[0]) append(L"w");
                                                            #line 3485 "PrintCLike.cpp"
  append(L"char");
                                                            #line 2397 "PrintCLike.cpp.template"
                                                                if (stringIntroducer()[0]) append(L"_t");
                                                            #line 3489 "PrintCLike.cpp"
  append(L" *sign = i < 0 ? ");
                                                            #line 2398 "PrintCLike.cpp.template"
                                                                append(stringIntroducer());
                                                            #line 3493 "PrintCLike.cpp"
  append(L"\"-\" : ");
                                                            #line 2399 "PrintCLike.cpp.template"
                                                                append(stringIntroducer());
                                                            #line 3497 "PrintCLike.cpp"
  append(L"\"\";\n");
  append(L"  std::");
                                                            #line 2401 "PrintCLike.cpp.template"
                                                                if (stringIntroducer()[0]) append(L"w");
                                                            #line 3502 "PrintCLike.cpp"
  append(L"string a;\n");
  append(L"  do\n");
  append(L"  {\n");
  append(L"    a += ");
                                                            #line 2405 "PrintCLike.cpp.template"
                                                                append(stringIntroducer());
                                                            #line 3509 "PrintCLike.cpp"
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
                                                            #line 2415 "PrintCLike.cpp.template"
                                                                if (stringIntroducer()[0]) append(L"w");
                                                            #line 3522 "PrintCLike.cpp"
  append(L"string getErrorMessage(const ParseException &e)\n");
  append(L"{\n");
  append(L"  std::");
                                                            #line 2418 "PrintCLike.cpp.template"
                                                                if (stringIntroducer()[0]) append(L"w");
                                                            #line 3528 "PrintCLike.cpp"
  append(L"string message(e.getMessage());");
                                                            #line 2419 "PrintCLike.cpp.template"
                                                                if (useGlr)
                                                                {
                                                            #line 3533 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if (e.isAmbiguousInput())\n");
  append(L"  {\n");
  append(L"    message += ");
                                                            #line 2424 "PrintCLike.cpp.template"
                                                                  print(stringIntroducer());
                                                            #line 3540 "PrintCLike.cpp"
  append(L"\"\\n\";\n");
  append(L"  }\n");
  append(L"  else\n");
  append(L"  {");
                                                            #line 2428 "PrintCLike.cpp.template"
                                                                  increaseIndent();
                                                                }
                                                            #line 3548 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 2431 "PrintCLike.cpp.template"
                                                                print(stringType());
                                                            #line 3553 "PrintCLike.cpp"
  append(L"found = getOffendingToken(e);\n");
  append(L"  if (found != 0)\n");
  append(L"  {\n");
  append(L"    message += ");
                                                            #line 2435 "PrintCLike.cpp.template"
                                                                print(stringIntroducer());
                                                            #line 3560 "PrintCLike.cpp"
  append(L"\", found \";\n");
  append(L"    message += found;\n");
  append(L"  }\n");
  append(L"  ");
                                                            #line 2439 "PrintCLike.cpp.template"
                                                                print(stringType());
                                                            #line 3567 "PrintCLike.cpp"
  append(L"expected[64];\n");
  append(L"  getExpectedTokenSet(e, expected, sizeof expected / sizeof *expected);\n");
  append(L"  message += ");
                                                            #line 2442 "PrintCLike.cpp.template"
                                                                print(stringIntroducer());
                                                            #line 3573 "PrintCLike.cpp"
  append(L"\"\\nwhile expecting \";\n");
  append(L"  ");
                                                            #line 2444 "PrintCLike.cpp.template"
                                                                print(stringType());
                                                            #line 3578 "PrintCLike.cpp"
  append(L"delimiter(expected[1] ? ");
                                                            #line 2445 "PrintCLike.cpp.template"
                                                                print(stringIntroducer());
                                                            #line 3582 "PrintCLike.cpp"
  append(L"\"[\" : ");
                                                            #line 2446 "PrintCLike.cpp.template"
                                                                print(stringIntroducer());
                                                            #line 3586 "PrintCLike.cpp"
  append(L"\"\");\n");
  append(L"  for (");
                                                            #line 2448 "PrintCLike.cpp.template"
                                                                print(stringType());
                                                            #line 3591 "PrintCLike.cpp"
  append(L"*x = expected; *x; ++x)\n");
  append(L"  {\n");
  append(L"    message += delimiter;\n");
  append(L"    message += *x;\n");
  append(L"    delimiter = ");
                                                            #line 2453 "PrintCLike.cpp.template"
                                                                print(stringIntroducer());
                                                            #line 3599 "PrintCLike.cpp"
  append(L"\", \";\n");
  append(L"  }\n");
  append(L"  message += expected[1] ? ");
                                                            #line 2456 "PrintCLike.cpp.template"
                                                                print(stringIntroducer());
                                                            #line 3605 "PrintCLike.cpp"
  append(L"\"]\\n\" : ");
                                                            #line 2457 "PrintCLike.cpp.template"
                                                                print(stringIntroducer());
                                                            #line 3609 "PrintCLike.cpp"
  append(L"\"\\n\";\n");
  append(L"  int size = e.getEnd() - e.getBegin();\n");
  append(L"  if (size != 0 && found == 0)\n");
  append(L"  {\n");
  append(L"    message += ");
                                                            #line 2462 "PrintCLike.cpp.template"
                                                                print(stringIntroducer());
                                                            #line 3617 "PrintCLike.cpp"
  append(L"\"after successfully scanning \";\n");
  append(L"    message += to_");
                                                            #line 2464 "PrintCLike.cpp.template"
                                                                if (stringIntroducer()[0]) append(L"w");
                                                            #line 3622 "PrintCLike.cpp"
  append(L"string(size);\n");
  append(L"    message += ");
                                                            #line 2466 "PrintCLike.cpp.template"
                                                                print(stringIntroducer());
                                                            #line 3627 "PrintCLike.cpp"
  append(L"\" characters beginning \";\n");
  append(L"  }");
                                                            #line 2468 "PrintCLike.cpp.template"
                                                                if (useGlr)
                                                                {
                                                                  decreaseIndent();
                                                            #line 3634 "PrintCLike.cpp"
  append(L"\n");
  append(L"  }");
                                                            #line 2472 "PrintCLike.cpp.template"
                                                                }
                                                            #line 3639 "PrintCLike.cpp"
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
                                                            #line 2488 "PrintCLike.cpp.template"
                                                                print(stringIntroducer());
                                                            #line 3658 "PrintCLike.cpp"
  append(L"\"at line \";\n");
  append(L"  message += to_");
                                                            #line 2490 "PrintCLike.cpp.template"
                                                                if (stringIntroducer()[0]) append(L"w");
                                                            #line 3663 "PrintCLike.cpp"
  append(L"string(line);\n");
  append(L"  message += ");
                                                            #line 2492 "PrintCLike.cpp.template"
                                                                print(stringIntroducer());
                                                            #line 3668 "PrintCLike.cpp"
  append(L"\", column \";\n");
  append(L"  message += to_");
                                                            #line 2494 "PrintCLike.cpp.template"
                                                                if (stringIntroducer()[0]) append(L"w");
                                                            #line 3673 "PrintCLike.cpp"
  append(L"string(column);\n");
  append(L"  message += ");
                                                            #line 2496 "PrintCLike.cpp.template"
                                                                print(stringIntroducer());
                                                            #line 3678 "PrintCLike.cpp"
  append(L"\":\\n...\";\n");
  append(L"  ");
                                                            #line 2498 "PrintCLike.cpp.template"
                                                                print(stringType());
                                                            #line 3683 "PrintCLike.cpp"
  append(L"w = input + e.getBegin();\n");
  append(L"  for (int i = 0; i < 64 && *w; ++i)\n");
  append(L"  {\n");
  append(L"    message += *w++;\n");
  append(L"  }\n");
  append(L"  message += ");
                                                            #line 2504 "PrintCLike.cpp.template"
                                                                print(stringIntroducer());
                                                            #line 3692 "PrintCLike.cpp"
  append(L"\"...\";\n");
  append(L"  return message;\n");
  append(L"}\n");
                                                            #line 2508 "PrintCLike.cpp.template"
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
                                                            #line 3721 "PrintCLike.cpp"
  append(L"\n");
  append(L"  fprintf(stderr, \"  <%s %snonterminal=\\\"%s\\\"\", ");
                                                            #line 2533 "PrintCLike.cpp.template"
                                                                  if (stringIntroducer()[0])
                                                                  {
                                                            #line 3727 "PrintCLike.cpp"
  append(L"Utf8Encoder::encode(");
                                                            #line 2535 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 3731 "PrintCLike.cpp"
  append(L"method");
                                                            #line 2536 "PrintCLike.cpp.template"
                                                                  if (stringIntroducer()[0])
                                                                  {
                                                            #line 3736 "PrintCLike.cpp"
  append(L").c_str()");
                                                            #line 2538 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 3740 "PrintCLike.cpp"
  append(L", ");
                                                            #line 2539 "PrintCLike.cpp.template"
                                                                  if (stringIntroducer()[0])
                                                                  {
                                                            #line 3745 "PrintCLike.cpp"
  append(L"Utf8Encoder::encode(");
                                                            #line 2541 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 3749 "PrintCLike.cpp"
  append(L"occasion");
                                                            #line 2542 "PrintCLike.cpp.template"
                                                                  if (stringIntroducer()[0])
                                                                  {
                                                            #line 3754 "PrintCLike.cpp"
  append(L").c_str()");
                                                            #line 2544 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 3758 "PrintCLike.cpp"
  append(L", ");
                                                            #line 2545 "PrintCLike.cpp.template"
                                                                  if (stringIntroducer()[0])
                                                                  {
                                                            #line 3763 "PrintCLike.cpp"
  append(L"Utf8Encoder::encode(");
                                                            #line 2547 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 3767 "PrintCLike.cpp"
  append(L"name");
                                                            #line 2548 "PrintCLike.cpp.template"
                                                                  if (stringIntroducer()[0])
                                                                  {
                                                            #line 3772 "PrintCLike.cpp"
  append(L").c_str()");
                                                            #line 2550 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 3776 "PrintCLike.cpp"
  append(L");\n");
  append(L"  if (l1 != 0)\n");
  append(L"    fprintf(stderr, \" input=\\\"%s\\\"\", ");
                                                            #line 2553 "PrintCLike.cpp.template"
                                                                  if (stringIntroducer()[0])
                                                                  {
                                                            #line 3783 "PrintCLike.cpp"
  append(L"Utf8Encoder::encode(");
                                                            #line 2555 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 3787 "PrintCLike.cpp"
  append(L"xmlEscape(lookaheadString().c_str(), 0).c_str()");
                                                            #line 2557 "PrintCLike.cpp.template"
                                                                  if (stringIntroducer()[0])
                                                                  {
                                                            #line 3792 "PrintCLike.cpp"
  append(L").c_str()");
                                                            #line 2559 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 3796 "PrintCLike.cpp"
  append(L");\n");
  append(L"  fprintf(stderr, \"/>\\n\");");
                                                            #line 2561 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                                  if (isHaxe())
                                                                  {
                                                            #line 3805 "PrintCLike.cpp"
  append(L"\n");
  append(L"  trace(");
                                                            #line 2567 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                                    if (isGo())
                                                                    {
                                                            #line 3814 "PrintCLike.cpp"
  append(L"\n");
  append(L"  var inputAttr string\n");
  append(L"  if (this.l1 == 0) {\n");
  append(L"    inputAttr = \"\"\n");
  append(L"  } else {\n");
  append(L"    inputAttr = \" input=\\\"\" + xmlEscape(this.lookaheadString()) + \"\\\"\"\n");
  append(L"  }");
                                                            #line 2578 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 3824 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 2580 "PrintCLike.cpp.template"
                                                                    print(writeTrace());
                                                                  }
                                                            #line 3830 "PrintCLike.cpp"
  append(L"\"  <\" + method + \" \" + occasion + \"nonterminal=\\\"\" + name + \"\\\"\" + ");
                                                            #line 2583 "PrintCLike.cpp.template"
                                                                  if (isGo())
                                                                  {
                                                            #line 3835 "PrintCLike.cpp"
  append(L"inputAttr");
                                                            #line 2585 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 3841 "PrintCLike.cpp"
  append(L"(");
                                                            #line 2588 "PrintCLike.cpp.template"
                                                                    if (isScala())
                                                                    {
                                                            #line 3846 "PrintCLike.cpp"
  append(L"if (l1 == 0) \"\" else");
                                                            #line 2590 "PrintCLike.cpp.template"
                                                                    }
                                                                    else if (isPython())
                                                                    {
                                                            #line 3852 "PrintCLike.cpp"
  append(L"\"\" if self.l1 == 0 else");
                                                            #line 2593 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                                      print(thiz());
                                                            #line 3859 "PrintCLike.cpp"
  append(L"l1 == 0 ? \"\" :");
                                                            #line 2597 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 3863 "PrintCLike.cpp"
  append(L" \" input=\\\"\" + ");
                                                            #line 2598 "PrintCLike.cpp.template"
                                                                    print(staticPrefix());
                                                            #line 3867 "PrintCLike.cpp"
  append(L"xmlEscape(");
                                                            #line 2599 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 3871 "PrintCLike.cpp"
  append(L"lookaheadString");
                                                            #line 2600 "PrintCLike.cpp.template"
                                                                    if (! isScala()) print(L"()");
                                                            #line 3875 "PrintCLike.cpp"
  append(L") + \"\\\"\")");
                                                            #line 2601 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 3879 "PrintCLike.cpp"
  append(L" + \"/>");
                                                            #line 2602 "PrintCLike.cpp.template"
                                                                  if (isHaxe()) print(L"\")"); else print(L"\\n\"");
                                                                  print(endWriteTrace());
                                                                  print(semicolon());
                                                                }
                                                                print(rightBrace());
                                                            #line 3887 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 2608 "PrintCLike.cpp.template"
                                                                decreaseIndent();
                                                              }

                                                              if (grammar->automaticSemicolonInsertion)
                                                              {
                                                                if (! isGo())
                                                                  increaseIndent();
                                                                openMethod(boolType(), L"", L"followsLineTerminator", L"");
                                                                print(leftBrace());
                                                                increaseIndent();
                                                            #line 3900 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 2619 "PrintCLike.cpp.template"
                                                                print(intVar());
                                                            #line 3904 "PrintCLike.cpp"
  append(L"i");
                                                            #line 2620 "PrintCLike.cpp.template"
                                                                print(assign());
                                                                print(thiz());
                                                            #line 3909 "PrintCLike.cpp"
  append(L"e0");
                                                            #line 2622 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 3913 "PrintCLike.cpp"
  append(L"\n");
  append(L"if ");
                                                            #line 2624 "PrintCLike.cpp.template"
                                                                print(ifLeftParen());
                                                                print(thiz());
                                                            #line 3919 "PrintCLike.cpp"
  append(L"e0 == ");
                                                            #line 2626 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 3923 "PrintCLike.cpp"
  append(L"b1");
                                                            #line 2627 "PrintCLike.cpp.template"
                                                                print(ifRightParen());
                                                                print(leftBrace());
                                                            #line 3928 "PrintCLike.cpp"
  append(L"\n");
  append(L"  i = ");
                                                            #line 2630 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 3933 "PrintCLike.cpp"
  append(L"b0");
                                                            #line 2631 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                print(rightBrace());
                                                                if (isScala() || isHaxe() || isPython())
                                                                {
                                                            #line 3940 "PrintCLike.cpp"
  append(L"\n");
  append(L"while ");
                                                            #line 2636 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 3947 "PrintCLike.cpp"
  append(L"\n");
  append(L"for ");
                                                            #line 2640 "PrintCLike.cpp.template"
                                                                }
                                                                print(ifLeftParen());
                                                                if (! (isScala() || isHaxe() || isPython()))
                                                                {
                                                            #line 3955 "PrintCLike.cpp"
  append(L"; ");
                                                            #line 2644 "PrintCLike.cpp.template"
                                                                }
                                                            #line 3959 "PrintCLike.cpp"
  append(L"i < ");
                                                            #line 2645 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 3963 "PrintCLike.cpp"
  append(L"b1");
                                                            #line 2646 "PrintCLike.cpp.template"
                                                                if (! (isScala() || isHaxe() || isPython()))
                                                                {
                                                            #line 3968 "PrintCLike.cpp"
  append(L"; i++");
                                                            #line 2648 "PrintCLike.cpp.template"
                                                                }
                                                                print(ifRightParen());
                                                                print(leftBrace());
                                                                increaseIndent();
                                                                if (isGo())
                                                                {
                                                            #line 3977 "PrintCLike.cpp"
  append(L"\n");
  append(L"c, _ := utf8.DecodeRuneInString(this.input[i:])");
                                                            #line 2655 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 3984 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 2659 "PrintCLike.cpp.template"
                                                                  print(intVar());
                                                            #line 3988 "PrintCLike.cpp"
  append(L"c");
                                                            #line 2660 "PrintCLike.cpp.template"
                                                                  print(assign());
                                                                  if (isCpp() || isCSharp() || isPython() || (isJava() && codepoints))
                                                                  {
                                                                    if (isPython())
                                                                    {
                                                            #line 3996 "PrintCLike.cpp"
  append(L"ord(");
                                                            #line 2665 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(thiz());
                                                            #line 4001 "PrintCLike.cpp"
  append(L"input[i]");
                                                            #line 2667 "PrintCLike.cpp.template"
                                                                    if (isPython())
                                                                    {
                                                            #line 4006 "PrintCLike.cpp"
  append(L")");
                                                            #line 2669 "PrintCLike.cpp.template"
                                                                    }
                                                                  }
                                                                  else if (isHaxe())
                                                                  {
                                                            #line 4013 "PrintCLike.cpp"
  append(L"input.get(i)");
                                                            #line 2673 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                                    print(thiz());
                                                            #line 4020 "PrintCLike.cpp"
  append(L"input.char");
                                                            #line 2677 "PrintCLike.cpp.template"
                                                                    if (isTypescript() || isJavascript())
                                                                    {
                                                            #line 4025 "PrintCLike.cpp"
  append(L"Code");
                                                            #line 2679 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 4029 "PrintCLike.cpp"
  append(L"At(i)");
                                                            #line 2680 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(semicolon());
                                                                }
                                                            #line 4035 "PrintCLike.cpp"
  append(L"\n");
  append(L"if ");
                                                            #line 2684 "PrintCLike.cpp.template"
                                                                print(ifLeftParen());
                                                            #line 4040 "PrintCLike.cpp"
  append(L"c == 0xA ");
                                                            #line 2685 "PrintCLike.cpp.template"
                                                                if (isPython())
                                                                {
                                                            #line 4045 "PrintCLike.cpp"
  append(L"or");
                                                            #line 2687 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 4051 "PrintCLike.cpp"
  append(L"||");
                                                            #line 2690 "PrintCLike.cpp.template"
                                                                }
                                                            #line 4055 "PrintCLike.cpp"
  append(L" c == 0xD ");
                                                            #line 2691 "PrintCLike.cpp.template"
                                                                if (isPython())
                                                                {
                                                            #line 4060 "PrintCLike.cpp"
  append(L"or");
                                                            #line 2693 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 4066 "PrintCLike.cpp"
  append(L"||");
                                                            #line 2696 "PrintCLike.cpp.template"
                                                                }
                                                            #line 4070 "PrintCLike.cpp"
  append(L" c == 0x2028 ");
                                                            #line 2697 "PrintCLike.cpp.template"
                                                                if (isPython())
                                                                {
                                                            #line 4075 "PrintCLike.cpp"
  append(L"or");
                                                            #line 2699 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 4081 "PrintCLike.cpp"
  append(L"||");
                                                            #line 2702 "PrintCLike.cpp.template"
                                                                }
                                                            #line 4085 "PrintCLike.cpp"
  append(L" c == 0x2029");
                                                            #line 2703 "PrintCLike.cpp.template"
                                                                print(ifRightParen());
                                                                print(leftBrace());
                                                            #line 4090 "PrintCLike.cpp"
  append(L"\n");
  append(L"  return ");
                                                            #line 2706 "PrintCLike.cpp.template"
                                                                if (isPython())
                                                                {
                                                            #line 4096 "PrintCLike.cpp"
  append(L"T");
                                                            #line 2708 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 4102 "PrintCLike.cpp"
  append(L"t");
                                                            #line 2711 "PrintCLike.cpp.template"
                                                                }
                                                            #line 4106 "PrintCLike.cpp"
  append(L"rue");
                                                            #line 2712 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                print(rightBrace());
                                                                if (isScala() || isPython())
                                                                {
                                                            #line 4113 "PrintCLike.cpp"
  append(L"\n");
  append(L"i += 1");
                                                            #line 2717 "PrintCLike.cpp.template"
                                                                }
                                                                else if (isHaxe())
                                                                {
                                                            #line 4120 "PrintCLike.cpp"
  append(L"\n");
  append(L"++i;");
                                                            #line 2721 "PrintCLike.cpp.template"
                                                                }

                                                                decreaseIndent();
                                                                print(rightBrace());
                                                            #line 4128 "PrintCLike.cpp"
  append(L"\n");
  append(L"return ");
                                                            #line 2726 "PrintCLike.cpp.template"
                                                                if (isPython())
                                                                {
                                                            #line 4134 "PrintCLike.cpp"
  append(L"F");
                                                            #line 2728 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 4140 "PrintCLike.cpp"
  append(L"f");
                                                            #line 2731 "PrintCLike.cpp.template"
                                                                }
                                                            #line 4144 "PrintCLike.cpp"
  append(L"alse");
                                                            #line 2732 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                decreaseIndent();
                                                                print(rightBrace());
                                                            #line 4150 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 2736 "PrintCLike.cpp.template"
                                                                if (! isGo())
                                                                  decreaseIndent();
                                                              }

                                                              if (isScala())
                                                              {
                                                            #line 4159 "PrintCLike.cpp"
  append(L"\n");
  append(L"  def getErrorMessage(e: ");
                                                            #line 2743 "PrintCLike.cpp.template"
                                                                print(className.c_str());
                                                            #line 4164 "PrintCLike.cpp"
  append(L".ParseException) = {\n");
  append(L"    var message = e.getMessage");
                                                            #line 2745 "PrintCLike.cpp.template"
                                                                if (useGlr)
                                                                {
                                                            #line 4170 "PrintCLike.cpp"
  append(L"\n");
  append(L"    if (e.isAmbiguousInput)\n");
  append(L"      message += \"\\n\"\n");
  append(L"    else {");
                                                            #line 2750 "PrintCLike.cpp.template"
                                                                  increaseIndent();
                                                                }
                                                            #line 4178 "PrintCLike.cpp"
  append(L"\n");
  append(L"    val tokenSet = ");
                                                            #line 2753 "PrintCLike.cpp.template"
                                                                print(className.c_str());
                                                            #line 4183 "PrintCLike.cpp"
  append(L".getExpectedTokenSet(e)\n");
  append(L"    val found = ");
                                                            #line 2755 "PrintCLike.cpp.template"
                                                                print(className.c_str());
                                                            #line 4188 "PrintCLike.cpp"
  append(L".getOffendingToken(e)\n");
  append(L"    val size = e.end - e.begin\n");
  append(L"    message += (if (found == null) \"\" else \", found \" + found) + \"\\nwhile expecting \" +\n");
  append(L"      (if (tokenSet.length == 1) tokenSet(0) else \"[\" + (tokenSet mkString \", \") + \"]\") + \"\\n\" +\n");
  append(L"      (if (size == 0 || found != null) \"\" else \"after successfully scanning \" + size + \" characters beginning \")");
                                                            #line 2761 "PrintCLike.cpp.template"
                                                                if (useGlr)
                                                                {
                                                            #line 4197 "PrintCLike.cpp"
  append(L"\n");
  append(L"    }");
                                                            #line 2764 "PrintCLike.cpp.template"
                                                                  decreaseIndent();
                                                                }
                                                            #line 4203 "PrintCLike.cpp"
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
                                                            #line 2774 "PrintCLike.cpp.template"
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
                                                            #line 4251 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 2811 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 4256 "PrintCLike.cpp"
  append(L"top += ");
                                                            #line 2812 "PrintCLike.cpp.template"
                                                                  if (tree)
                                                                  {
                                                            #line 4261 "PrintCLike.cpp"
  append(L"3");
                                                            #line 2814 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 4267 "PrintCLike.cpp"
  append(L"2");
                                                            #line 2817 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(semicolon());
                                                                  if (isJava())
                                                                  {
                                                            #line 4274 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if (top >= iStack.length)\n");
  append(L"  {\n");
  append(L"    iStack = Arrays.copyOf(iStack, iStack.length << 1);\n");
  append(L"  }");
                                                            #line 2825 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isCSharp())
                                                                  {
                                                            #line 4284 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if (top >= iStack.Length)\n");
  append(L"  {\n");
  append(L"    Array.Resize(ref iStack, iStack.Length << 1);\n");
  append(L"  }");
                                                            #line 2832 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isCpp())
                                                                  {
                                                            #line 4294 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if (top >= (int) iStack.size())\n");
  append(L"    iStack.resize(iStack.size() == 0 ? ");
                                                            #line 2837 "PrintCLike.cpp.template"
                                                                    print(tree ? L"192" : L"128");
                                                            #line 4300 "PrintCLike.cpp"
  append(L" : iStack.size() << 1);");
                                                            #line 2838 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isScala())
                                                                  {
                                                            #line 4306 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if (top >= iStack.size) {\n");
  append(L"    val newStack = new Array[Int](iStack.size << 1)\n");
  append(L"    Array.copy(iStack, 0, newStack, 0, iStack.size)\n");
  append(L"    iStack = newStack\n");
  append(L"  }");
                                                            #line 2846 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isGo())
                                                                  {
                                                            #line 4317 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if this.top >= len(this.iStack) {\n");
  append(L"    this.iStack = append(this.iStack, this.iStack...)\n");
  append(L"  }");
                                                            #line 2852 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isPython())
                                                                  {
                                                            #line 4326 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if self.top >= len(self.iStack):\n");
  append(L"    self.iStack.extend([0 for _ in range(len(self.iStack))])");
                                                            #line 2857 "PrintCLike.cpp.template"
                                                                  }
                                                                  if (tree)
                                                                  {
                                                            #line 4334 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 2861 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 4339 "PrintCLike.cpp"
  append(L"iStack");
                                                            #line 2862 "PrintCLike.cpp.template"
                                                                    print(leftbracket());
                                                                    print(thiz());
                                                            #line 4344 "PrintCLike.cpp"
  append(L"top - 2");
                                                            #line 2864 "PrintCLike.cpp.template"
                                                                    print(rightbracket());
                                                            #line 4348 "PrintCLike.cpp"
  append(L" = begin");
                                                            #line 2865 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                  }
                                                            #line 4353 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 2868 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 4358 "PrintCLike.cpp"
  append(L"iStack");
                                                            #line 2869 "PrintCLike.cpp.template"
                                                                  print(leftbracket());
                                                                  print(thiz());
                                                            #line 4363 "PrintCLike.cpp"
  append(L"top - 1");
                                                            #line 2871 "PrintCLike.cpp.template"
                                                                  print(rightbracket());
                                                            #line 4367 "PrintCLike.cpp"
  append(L" = state");
                                                            #line 2872 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                            #line 4371 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 2874 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 4376 "PrintCLike.cpp"
  append(L"iStack");
                                                            #line 2875 "PrintCLike.cpp.template"
                                                                  print(leftbracket());
                                                                  print(thiz());
                                                            #line 4381 "PrintCLike.cpp"
  append(L"top");
                                                            #line 2877 "PrintCLike.cpp.template"
                                                                  print(rightbracket());
                                                            #line 4385 "PrintCLike.cpp"
  append(L" = lookback");
                                                            #line 2878 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                  print(rightBrace());
                                                            #line 4390 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 2881 "PrintCLike.cpp.template"
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
                                                            #line 4409 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 2898 "PrintCLike.cpp.template"
                                                                  print(intVar());
                                                            #line 4413 "PrintCLike.cpp"
  append(L"state");
                                                            #line 2899 "PrintCLike.cpp.template"
                                                                  print(assign());
                                                            #line 4417 "PrintCLike.cpp"
  append(L"initialState");
                                                            #line 2900 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                  if (tree || useGlr)
                                                                  {
                                                            #line 4423 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 2904 "PrintCLike.cpp.template"
                                                                    print(intVar());
                                                            #line 4427 "PrintCLike.cpp"
  append(L"bw");
                                                            #line 2905 "PrintCLike.cpp.template"
                                                                    print(assign());
                                                                    print(thiz());
                                                            #line 4432 "PrintCLike.cpp"
  append(L"e0");
                                                            #line 2907 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 4436 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 2909 "PrintCLike.cpp.template"
                                                                    print(intVar());
                                                            #line 4440 "PrintCLike.cpp"
  append(L"bs");
                                                            #line 2910 "PrintCLike.cpp.template"
                                                                    print(assign());
                                                                    print(thiz());
                                                            #line 4445 "PrintCLike.cpp"
  append(L"e0");
                                                            #line 2912 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                  }
                                                                  if (tree)
                                                                  {
                                                            #line 4452 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 2917 "PrintCLike.cpp.template"
                                                                    print(intVar());
                                                            #line 4456 "PrintCLike.cpp"
  append(L"es");
                                                            #line 2918 "PrintCLike.cpp.template"
                                                                    print(assign());
                                                                    print(thiz());
                                                            #line 4461 "PrintCLike.cpp"
  append(L"e0");
                                                            #line 2920 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 4465 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 2922 "PrintCLike.cpp.template"
                                                                    print(intVar());
                                                            #line 4469 "PrintCLike.cpp"
  append(L"t");
                                                            #line 2923 "PrintCLike.cpp.template"
                                                                    print(assign());
                                                                    print(thiz());
                                                            #line 4474 "PrintCLike.cpp"
  append(L"top");
                                                            #line 2925 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                  }
                                                            #line 4479 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 2928 "PrintCLike.cpp.template"
                                                                  print(intVar());
                                                            #line 4483 "PrintCLike.cpp"
  append(L"action");
                                                            #line 2929 "PrintCLike.cpp.template"
                                                                  print(assign());
                                                                  print(thiz());
                                                            #line 4488 "PrintCLike.cpp"
  append(L"predict(state)");
                                                            #line 2931 "PrintCLike.cpp.template"
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
                                                            #line 4502 "PrintCLike.cpp"
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
                                                            #line 2955 "PrintCLike.cpp.template"
                                                                }
                                                                if (useGlr)
                                                                {
                                                            #line 4519 "PrintCLike.cpp"
  append(L"\n");
  append(L"  var thread: ");
                                                            #line 2959 "PrintCLike.cpp.template"
                                                                  print(className.c_str());
                                                            #line 4524 "PrintCLike.cpp"
  append(L".ParsingThread = null");
                                                            #line 2960 "PrintCLike.cpp.template"
                                                                }
                                                            #line 4528 "PrintCLike.cpp"
  append(L"\n");
  append(L"  var input: String = null");
                                                            #line 2962 "PrintCLike.cpp.template"
                                                                if (! noLexer)
                                                                {
                                                            #line 4534 "PrintCLike.cpp"
  append(L"\n");
  append(L"  var size = 0");
                                                            #line 2965 "PrintCLike.cpp.template"
                                                                }
                                                                if (tree && useGlr)
                                                                {
                                                            #line 4541 "PrintCLike.cpp"
  append(L"\n");
  append(L"  var eventHandler: ");
                                                            #line 2969 "PrintCLike.cpp.template"
                                                                  print(className.c_str());
                                                            #line 4546 "PrintCLike.cpp"
  append(L".BottomUpEventHandler = null");
                                                            #line 2970 "PrintCLike.cpp.template"
                                                                }
                                                                if (noLexer)
                                                                {
                                                            #line 4552 "PrintCLike.cpp"
  append(L"\n");
  append(L"  var lexer: Lexer = null\n");
  append(L"  var token = new Token");
                                                            #line 2975 "PrintCLike.cpp.template"
                                                                }
                                                                if (useGlr)
                                                                {
                                                            #line 4560 "PrintCLike.cpp"
  append(L"\n");
  append(L"  var maxId = 0");
                                                            #line 2979 "PrintCLike.cpp.template"
                                                                }
                                                                if (trace)
                                                                {
                                                            #line 4567 "PrintCLike.cpp"
  append(L"\n");
  append(L"  var err: Writer = new OutputStreamWriter(System.err, \"UTF-8\")");
                                                            #line 2984 "PrintCLike.cpp.template"
                                                                }
                                                            #line 4572 "PrintCLike.cpp"
  append(L"\n");
  append(L"}\n");
  append(L"\n");
  append(L"object ");
                                                            #line 2988 "PrintCLike.cpp.template"
                                                                print(className.c_str());
                                                            #line 4579 "PrintCLike.cpp"
  append(L" {\n");
  append(L"\n");
  append(L"  def getOffendingToken(e: ParseException) = {\n");
  append(L"    if (e.offending < 0) null else TOKEN(e.offending)\n");
  append(L"  }\n");
                                                            #line 2994 "PrintCLike.cpp.template"
                                                              }
                                                            }

                                                            void PrintCLike::printThreadBody1()
                                                            {
                                                              Trace("PrintCLike::printThreadBody1");

                                                              if (isLrParser)
                                                              {
                                                            #line 4595 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3004 "PrintCLike.cpp.template"
                                                                print(intVar());
                                                            #line 4599 "PrintCLike.cpp"
  append(L"nonterminalId");
                                                            #line 3005 "PrintCLike.cpp.template"
                                                                print(assign());
                                                            #line 4603 "PrintCLike.cpp"
  append(L"-1");
                                                            #line 3006 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                if (isHaxe() || isScala() || isPython())
                                                                {
                                                            #line 4609 "PrintCLike.cpp"
  append(L"\n");
  append(L"while ");
                                                            #line 3010 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                                  if (isPython())
                                                                  {
                                                            #line 4616 "PrintCLike.cpp"
  append(L"T");
                                                            #line 3013 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 4622 "PrintCLike.cpp"
  append(L"t");
                                                            #line 3016 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 4626 "PrintCLike.cpp"
  append(L"rue");
                                                            #line 3017 "PrintCLike.cpp.template"
                                                                  print(ifRightParen());
                                                                }
                                                                else if (isGo())
                                                                {
                                                            #line 4633 "PrintCLike.cpp"
  append(L"\n");
  append(L"for");
                                                            #line 3022 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 4640 "PrintCLike.cpp"
  append(L"\n");
  append(L"for (;;)");
                                                            #line 3026 "PrintCLike.cpp.template"
                                                                }
                                                                print(leftBrace());
                                                                increaseIndent();
                                                                if (trace)
                                                                {
                                                                  if (isCpp())
                                                                  {
                                                            #line 4651 "PrintCLike.cpp"
  append(L"\n");
  append(L"fprintf(stderr, \"  <parse ");
                                                            #line 3034 "PrintCLike.cpp.template"
                                                                    if (useGlr)
                                                                    {
                                                            #line 4657 "PrintCLike.cpp"
  append(L"thread=\\\"%d\\\" offset=\\\"%d\\\" ");
                                                            #line 3036 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 4661 "PrintCLike.cpp"
  append(L"state=\\\"%d\\\" input=\\\"%s%s%s\\\" action=\\\"\",");
                                                            #line 3038 "PrintCLike.cpp.template"
                                                                    if (useGlr)
                                                                    {
                                                            #line 4666 "PrintCLike.cpp"
  append(L"\n");
  append(L"  id,\n");
  append(L"  e0,");
                                                            #line 3042 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 4672 "PrintCLike.cpp"
  append(L"\n");
  append(L"  state,\n");
  append(L"  nonterminalId < 0 ? \"\" : ");
                                                            #line 3045 "PrintCLike.cpp.template"
                                                                    if (stringIntroducer()[0])
                                                                    {
                                                            #line 4679 "PrintCLike.cpp"
  append(L"Utf8Encoder::encode(");
                                                            #line 3047 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 4683 "PrintCLike.cpp"
  append(L"xmlEscape(");
                                                            #line 3048 "PrintCLike.cpp.template"
                                                                    print(isGo() ? L"nonterminal" : L"NONTERMINAL");
                                                            #line 4687 "PrintCLike.cpp"
  append(L"[nonterminalId], 0).c_str()");
                                                            #line 3049 "PrintCLike.cpp.template"
                                                                    if (stringIntroducer()[0])
                                                                    {
                                                            #line 4692 "PrintCLike.cpp"
  append(L").c_str()");
                                                            #line 3051 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 4696 "PrintCLike.cpp"
  append(L",\n");
  append(L"  nonterminalId < 0 || l1 <= 0 ? \"\" : \" \",\n");
  append(L"  l1 <= 0 ? \"\" : ");
                                                            #line 3054 "PrintCLike.cpp.template"
                                                                    if (stringIntroducer()[0])
                                                                    {
                                                            #line 4703 "PrintCLike.cpp"
  append(L"Utf8Encoder::encode(");
                                                            #line 3056 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 4707 "PrintCLike.cpp"
  append(L"xmlEscape(lookaheadString().c_str(), 0).c_str()");
                                                            #line 3057 "PrintCLike.cpp.template"
                                                                    if (stringIntroducer()[0])
                                                                    {
                                                            #line 4712 "PrintCLike.cpp"
  append(L").c_str()");
                                                            #line 3059 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 4716 "PrintCLike.cpp"
  append(L");\n");
                                                            #line 3061 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                                    if (isHaxe())
                                                                    {
                                                            #line 4724 "PrintCLike.cpp"
  append(L"\n");
  append(L"var traceLine = ");
                                                            #line 3067 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 4731 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3071 "PrintCLike.cpp.template"
                                                                      print(writeTrace());
                                                                    }
                                                            #line 4736 "PrintCLike.cpp"
  append(L"\"  <parse ");
                                                            #line 3073 "PrintCLike.cpp.template"
                                                                    if (useGlr)
                                                                    {
                                                            #line 4741 "PrintCLike.cpp"
  append(L"thread=\\\"\" + ");
                                                            #line 3075 "PrintCLike.cpp.template"
                                                                      if (isGo())
                                                                      {
                                                            #line 4746 "PrintCLike.cpp"
  append(L"strconv.Itoa(");
                                                            #line 3077 "PrintCLike.cpp.template"
                                                                      }
                                                                      else if (isPython())
                                                                      {
                                                            #line 4752 "PrintCLike.cpp"
  append(L"str(");
                                                            #line 3080 "PrintCLike.cpp.template"
                                                                      }
                                                                      print(thiz());
                                                            #line 4757 "PrintCLike.cpp"
  append(L"id");
                                                            #line 3082 "PrintCLike.cpp.template"
                                                                      if (isGo() || isPython())
                                                                      {
                                                            #line 4762 "PrintCLike.cpp"
  append(L")");
                                                            #line 3084 "PrintCLike.cpp.template"
                                                                      }
                                                            #line 4766 "PrintCLike.cpp"
  append(L" + \"\\\" offset=\\\"\" + ");
                                                            #line 3085 "PrintCLike.cpp.template"
                                                                      if (isGo())
                                                                      {
                                                            #line 4771 "PrintCLike.cpp"
  append(L"strconv.Itoa(");
                                                            #line 3087 "PrintCLike.cpp.template"
                                                                      }
                                                                      else if (isPython())
                                                                      {
                                                            #line 4777 "PrintCLike.cpp"
  append(L"str(");
                                                            #line 3090 "PrintCLike.cpp.template"
                                                                      }
                                                                      print(thiz());
                                                            #line 4782 "PrintCLike.cpp"
  append(L"e0");
                                                            #line 3092 "PrintCLike.cpp.template"
                                                                      if (isGo() || isPython())
                                                                      {
                                                            #line 4787 "PrintCLike.cpp"
  append(L")");
                                                            #line 3094 "PrintCLike.cpp.template"
                                                                      }
                                                            #line 4791 "PrintCLike.cpp"
  append(L" + \"\\\" ");
                                                            #line 3095 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 4795 "PrintCLike.cpp"
  append(L"state=\\\"\" + ");
                                                            #line 3096 "PrintCLike.cpp.template"
                                                                    if (isGo())
                                                                    {
                                                            #line 4800 "PrintCLike.cpp"
  append(L"strconv.Itoa(");
                                                            #line 3098 "PrintCLike.cpp.template"
                                                                    }
                                                                    else if (isPython())
                                                                    {
                                                            #line 4806 "PrintCLike.cpp"
  append(L"str(");
                                                            #line 3101 "PrintCLike.cpp.template"
                                                                    }
                                                                    if (useGlr) print(thiz());
                                                            #line 4811 "PrintCLike.cpp"
  append(L"state");
                                                            #line 3103 "PrintCLike.cpp.template"
                                                                    if (isGo() || isPython())
                                                                    {
                                                            #line 4816 "PrintCLike.cpp"
  append(L")");
                                                            #line 3105 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 4820 "PrintCLike.cpp"
  append(L" + \"\\\" input=\\\"\"");
                                                            #line 3106 "PrintCLike.cpp.template"
                                                                    print(endWriteTrace());
                                                                    print(semicolon());
                                                            #line 4825 "PrintCLike.cpp"
  append(L"\n");
  append(L"if ");
                                                            #line 3110 "PrintCLike.cpp.template"
                                                                    print(ifLeftParen());
                                                            #line 4830 "PrintCLike.cpp"
  append(L"nonterminalId >= 0");
                                                            #line 3111 "PrintCLike.cpp.template"
                                                                    print(ifRightParen());
                                                                    print(leftBrace());
                                                            #line 4835 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3114 "PrintCLike.cpp.template"
                                                                    print(writeTrace());
                                                                    print(staticPrefix());
                                                            #line 4841 "PrintCLike.cpp"
  append(L"xmlEscape(");
                                                            #line 3116 "PrintCLike.cpp.template"
                                                                    print(staticPrefix());
                                                                    print(isGo() ? L"nonterminal" : L"NONTERMINAL");
                                                                    print(leftbracket());
                                                            #line 4847 "PrintCLike.cpp"
  append(L"nonterminalId");
                                                            #line 3119 "PrintCLike.cpp.template"
                                                                    print(rightbracket());
                                                            #line 4851 "PrintCLike.cpp"
  append(L")");
                                                            #line 3120 "PrintCLike.cpp.template"
                                                                    print(endWriteTrace());
                                                                    print(semicolon());
                                                            #line 4856 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if ");
                                                            #line 3123 "PrintCLike.cpp.template"
                                                                    print(ifLeftParen());
                                                                    print(thiz());
                                                            #line 4862 "PrintCLike.cpp"
  append(L"l1 != 0");
                                                            #line 3125 "PrintCLike.cpp.template"
                                                                    print(ifRightParen());
                                                                    printIndented(1, leftBrace());
                                                            #line 4867 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 3128 "PrintCLike.cpp.template"
                                                                    print(writeTrace());
                                                            #line 4872 "PrintCLike.cpp"
  append(L"\" \"");
                                                            #line 3129 "PrintCLike.cpp.template"
                                                                    print(endWriteTrace());
                                                                    print(semicolon());
                                                                    increaseIndent();
                                                                    print(rightBrace());
                                                                    decreaseIndent();
                                                                    print(rightBrace());
                                                            #line 4881 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3136 "PrintCLike.cpp.template"
                                                                    print(writeTrace());
                                                                    print(staticPrefix());
                                                            #line 4886 "PrintCLike.cpp"
  append(L"xmlEscape(");
                                                            #line 3138 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 4890 "PrintCLike.cpp"
  append(L"lookaheadString");
                                                            #line 3139 "PrintCLike.cpp.template"
                                                                    if (! isScala()) print(L"()");
                                                            #line 4894 "PrintCLike.cpp"
  append(L") + \"\\\" action=\\\"\"");
                                                            #line 3140 "PrintCLike.cpp.template"
                                                                    print(endWriteTrace());
                                                                    print(semicolon());
                                                                  }
                                                                }
                                                            #line 4901 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3145 "PrintCLike.cpp.template"
                                                                print(intVal());
                                                            #line 4905 "PrintCLike.cpp"
  append(L"argument");
                                                            #line 3146 "PrintCLike.cpp.template"
                                                                print(assign());
                                                                if (useGlr) print(thiz());
                                                            #line 4910 "PrintCLike.cpp"
  append(L"action >> ");
                                                            #line 3148 "PrintCLike.cpp.template"
                                                                print(format.toString<wchar_t>(grammar->states->dominoBits + LrStates::actionBits));
                                                                print(semicolon());
                                                            #line 4915 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3151 "PrintCLike.cpp.template"
                                                                print(intVal());
                                                            #line 4919 "PrintCLike.cpp"
  append(L"lookback");
                                                            #line 3152 "PrintCLike.cpp.template"
                                                                print(assign());
                                                            #line 4923 "PrintCLike.cpp"
  append(L"(");
                                                            #line 3153 "PrintCLike.cpp.template"
                                                                if (useGlr) print(thiz());
                                                            #line 4927 "PrintCLike.cpp"
  append(L"action >> ");
                                                            #line 3154 "PrintCLike.cpp.template"
                                                                print(format.toString<wchar_t>((int) LrStates::actionBits));
                                                            #line 4931 "PrintCLike.cpp"
  append(L") & ");
                                                            #line 3155 "PrintCLike.cpp.template"
                                                                print(format.toString<wchar_t>((1 << grammar->states->dominoBits) -1));
                                                                print(semicolon());
                                                            #line 4936 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3158 "PrintCLike.cpp.template"
                                                                print(intVar());
                                                            #line 4940 "PrintCLike.cpp"
  append(L"shift");
                                                            #line 3159 "PrintCLike.cpp.template"
                                                                print(assign());
                                                            #line 4944 "PrintCLike.cpp"
  append(L"-1");
                                                            #line 3160 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 4948 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3162 "PrintCLike.cpp.template"
                                                                print(intVar());
                                                            #line 4952 "PrintCLike.cpp"
  append(L"reduce");
                                                            #line 3163 "PrintCLike.cpp.template"
                                                                print(assign());
                                                            #line 4956 "PrintCLike.cpp"
  append(L"-1");
                                                            #line 3164 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 4960 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3166 "PrintCLike.cpp.template"
                                                                print(intVar());
                                                            #line 4964 "PrintCLike.cpp"
  append(L"symbols");
                                                            #line 3167 "PrintCLike.cpp.template"
                                                                print(assign());
                                                            #line 4968 "PrintCLike.cpp"
  append(L"-1");
                                                            #line 3168 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                if (isPython())
                                                                {
                                                            #line 4974 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3172 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 4978 "PrintCLike.cpp"
  append(L"action &= ");
                                                            #line 3173 "PrintCLike.cpp.template"
                                                                  print(format.toString<wchar_t>((int) LrStates::actionMask));
                                                                }
                                                                else
                                                                {
                                                            #line 4985 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3178 "PrintCLike.cpp.template"
                                                                  if (! isScala())
                                                                  {
                                                            #line 4990 "PrintCLike.cpp"
  append(L"switch ");
                                                            #line 3180 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(ifLeftParen());
                                                                  if (useGlr) print(thiz());
                                                            #line 4996 "PrintCLike.cpp"
  append(L"action & ");
                                                            #line 3183 "PrintCLike.cpp.template"
                                                                  print(format.toString<wchar_t>((int) LrStates::actionMask));
                                                                  print(ifRightParen());
                                                                  if (isScala())
                                                                  {
                                                            #line 5003 "PrintCLike.cpp"
  append(L" match");
                                                            #line 3187 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(leftBrace());
                                                                }
                                                                if (isPython())
                                                                {
                                                            #line 5011 "PrintCLike.cpp"
  append(L"\n");
  append(L"if ");
                                                            #line 3193 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 5016 "PrintCLike.cpp"
  append(L"action == ");
                                                            #line 3194 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 5022 "PrintCLike.cpp"
  append(L"\n");
  append(L"case ");
                                                            #line 3198 "PrintCLike.cpp.template"
                                                                }
                                                                print(format.toString<wchar_t>((int) LrStates::SHIFT));
                                                                print(caseIntroducer());
                                                            #line 5029 "PrintCLike.cpp"
  append(L" ");
                                                            #line 3201 "PrintCLike.cpp.template"
                                                                print(inlineCommentIntroducer());
                                                            #line 5033 "PrintCLike.cpp"
  append(L"SHIFT\n");
  append(L"  shift = argument");
                                                            #line 3203 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                if (! isHaxe() && ! isScala() && ! isGo() && ! isPython())
                                                                {
                                                            #line 5040 "PrintCLike.cpp"
  append(L"\n");
  append(L"  break");
                                                            #line 3207 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                            #line 5046 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3210 "PrintCLike.cpp.template"
                                                                if (isPython())
                                                                {
                                                            #line 5051 "PrintCLike.cpp"
  append(L"\n");
  append(L"elif ");
                                                            #line 3213 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 5056 "PrintCLike.cpp"
  append(L"action == ");
                                                            #line 3214 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 5062 "PrintCLike.cpp"
  append(L"\n");
  append(L"case ");
                                                            #line 3218 "PrintCLike.cpp.template"
                                                                }
                                                                print(format.toString<wchar_t>((int) LrStates::REDUCE));
                                                                print(caseIntroducer());
                                                            #line 5069 "PrintCLike.cpp"
  append(L" ");
                                                            #line 3221 "PrintCLike.cpp.template"
                                                                print(inlineCommentIntroducer());
                                                            #line 5073 "PrintCLike.cpp"
  append(L"REDUCE\n");
  append(L"  reduce = argument");
                                                            #line 3223 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 5078 "PrintCLike.cpp"
  append(L"\n");
  append(L"  symbols = lookback");
                                                            #line 3225 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                if (! isHaxe() && ! isScala() && ! isGo() && ! isPython())
                                                                {
                                                            #line 5085 "PrintCLike.cpp"
  append(L"\n");
  append(L"  break");
                                                            #line 3229 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                                if (grammar->states->hasLookback)
                                                                {
                                                            #line 5093 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3234 "PrintCLike.cpp.template"
                                                                  if (isPython())
                                                                  {
                                                            #line 5098 "PrintCLike.cpp"
  append(L"\n");
  append(L"elif ");
                                                            #line 3237 "PrintCLike.cpp.template"
                                                                    if (useGlr) print(thiz());
                                                            #line 5103 "PrintCLike.cpp"
  append(L"action == ");
                                                            #line 3238 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 5109 "PrintCLike.cpp"
  append(L"\n");
  append(L"case ");
                                                            #line 3242 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(format.toString<wchar_t>((int) LrStates::REDUCE_LOOKBACK));
                                                                  print(caseIntroducer());
                                                            #line 5116 "PrintCLike.cpp"
  append(L" ");
                                                            #line 3245 "PrintCLike.cpp.template"
                                                                  print(inlineCommentIntroducer());
                                                            #line 5120 "PrintCLike.cpp"
  append(L"REDUCE+LOOKBACK\n");
  append(L"  reduce = argument");
                                                            #line 3247 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                            #line 5125 "PrintCLike.cpp"
  append(L"\n");
  append(L"  symbols = ");
                                                            #line 3249 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                                  if (useGlr)
                                                                  {
                                                            #line 5132 "PrintCLike.cpp"
  append(L"stack");
                                                            #line 3252 "PrintCLike.cpp.template"
                                                                    if (isTypescript()) print(L"!");
                                                                    print(arrow());
                                                                  }
                                                                  if (isGo() && useGlr)
                                                                  {
                                                            #line 5140 "PrintCLike.cpp"
  append(L"Count");
                                                            #line 3257 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 5146 "PrintCLike.cpp"
  append(L"count");
                                                            #line 3260 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 5150 "PrintCLike.cpp"
  append(L"(lookback)");
                                                            #line 3261 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                  if (! isHaxe() && ! isScala() && ! isGo() && ! isPython())
                                                                  {
                                                            #line 5156 "PrintCLike.cpp"
  append(L"\n");
  append(L"  break");
                                                            #line 3265 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                  }
                                                                }
                                                            #line 5163 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3269 "PrintCLike.cpp.template"
                                                                if (isPython())
                                                                {
                                                            #line 5168 "PrintCLike.cpp"
  append(L"\n");
  append(L"elif ");
                                                            #line 3272 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 5173 "PrintCLike.cpp"
  append(L"action == ");
                                                            #line 3273 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 5179 "PrintCLike.cpp"
  append(L"\n");
  append(L"case ");
                                                            #line 3277 "PrintCLike.cpp.template"
                                                                }
                                                                print(format.toString<wchar_t>((int) LrStates::SHIFT_REDUCE));
                                                                print(caseIntroducer());
                                                            #line 5186 "PrintCLike.cpp"
  append(L" ");
                                                            #line 3280 "PrintCLike.cpp.template"
                                                                print(inlineCommentIntroducer());
                                                            #line 5190 "PrintCLike.cpp"
  append(L"SHIFT+REDUCE\n");
  append(L"  shift = ");
                                                            #line 3282 "PrintCLike.cpp.template"
                                                                if (useGlr) print(thiz());
                                                            #line 5195 "PrintCLike.cpp"
  append(L"state");
                                                            #line 3283 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 5199 "PrintCLike.cpp"
  append(L"\n");
  append(L"  reduce = argument");
                                                            #line 3285 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 5204 "PrintCLike.cpp"
  append(L"\n");
  append(L"  symbols = lookback + 1");
                                                            #line 3287 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                if (! isHaxe() && ! isScala() && ! isGo() && ! isPython())
                                                                {
                                                            #line 5211 "PrintCLike.cpp"
  append(L"\n");
  append(L"  break");
                                                            #line 3291 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                                if (grammar->states->hasLookback)
                                                                {
                                                            #line 5219 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3296 "PrintCLike.cpp.template"
                                                                  if (isPython())
                                                                  {
                                                            #line 5224 "PrintCLike.cpp"
  append(L"\n");
  append(L"elif ");
                                                            #line 3299 "PrintCLike.cpp.template"
                                                                    if (useGlr) print(thiz());
                                                            #line 5229 "PrintCLike.cpp"
  append(L"action == ");
                                                            #line 3300 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 5235 "PrintCLike.cpp"
  append(L"\n");
  append(L"case ");
                                                            #line 3304 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(format.toString<wchar_t>((int) LrStates::SHIFT_REDUCE_LOOKBACK));
                                                                  print(caseIntroducer());
                                                            #line 5242 "PrintCLike.cpp"
  append(L" ");
                                                            #line 3307 "PrintCLike.cpp.template"
                                                                  print(inlineCommentIntroducer());
                                                            #line 5246 "PrintCLike.cpp"
  append(L"SHIFT+REDUCE+LOOKBACK\n");
  append(L"  shift = ");
                                                            #line 3309 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 5251 "PrintCLike.cpp"
  append(L"state");
                                                            #line 3310 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                            #line 5255 "PrintCLike.cpp"
  append(L"\n");
  append(L"  reduce = argument");
                                                            #line 3312 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                            #line 5260 "PrintCLike.cpp"
  append(L"\n");
  append(L"  symbols = ");
                                                            #line 3314 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                                  if (useGlr)
                                                                  {
                                                            #line 5267 "PrintCLike.cpp"
  append(L"stack");
                                                            #line 3317 "PrintCLike.cpp.template"
                                                                    if (isTypescript()) print(L"!");
                                                                    print(arrow());
                                                                  }
                                                                  if (isGo() && useGlr)
                                                                  {
                                                            #line 5275 "PrintCLike.cpp"
  append(L"Count");
                                                            #line 3322 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 5281 "PrintCLike.cpp"
  append(L"count");
                                                            #line 3325 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 5285 "PrintCLike.cpp"
  append(L"(lookback) + 1");
                                                            #line 3326 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                  if (! isHaxe() && ! isScala() && ! isGo() && ! isPython())
                                                                  {
                                                            #line 5291 "PrintCLike.cpp"
  append(L"\n");
  append(L"  break");
                                                            #line 3330 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                  }
                                                                }
                                                            #line 5298 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3334 "PrintCLike.cpp.template"
                                                                if (isPython())
                                                                {
                                                            #line 5303 "PrintCLike.cpp"
  append(L"\n");
  append(L"elif ");
                                                            #line 3337 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 5308 "PrintCLike.cpp"
  append(L"action == ");
                                                            #line 3338 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 5314 "PrintCLike.cpp"
  append(L"\n");
  append(L"case ");
                                                            #line 3342 "PrintCLike.cpp.template"
                                                                }
                                                                print(format.toString<wchar_t>((int) LrStates::SHIFT_ACCEPT));
                                                                print(caseIntroducer());
                                                            #line 5321 "PrintCLike.cpp"
  append(L" ");
                                                            #line 3345 "PrintCLike.cpp.template"
                                                                print(inlineCommentIntroducer());
                                                            #line 5325 "PrintCLike.cpp"
  append(L"ACCEPT");
                                                            #line 3346 "PrintCLike.cpp.template"
                                                                if (trace)
                                                                {
                                                                  if (isCpp())
                                                                  {
                                                            #line 5332 "PrintCLike.cpp"
  append(L"\n");
  append(L"  fprintf(stderr, ");
                                                            #line 3351 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 5339 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3355 "PrintCLike.cpp.template"
                                                                    print(writeTrace());
                                                                  }
                                                            #line 5345 "PrintCLike.cpp"
  append(L"\"accept\\\"/>");
                                                            #line 3357 "PrintCLike.cpp.template"
                                                                  if (! isHaxe())
                                                                  {
                                                            #line 5350 "PrintCLike.cpp"
  append(L"\\n");
                                                            #line 3359 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 5354 "PrintCLike.cpp"
  append(L"\"");
                                                            #line 3360 "PrintCLike.cpp.template"
                                                                  print(endWriteTrace());
                                                                  print(semicolon());
                                                                  if (isHaxe())
                                                                  {
                                                            #line 5361 "PrintCLike.cpp"
  append(L"\n");
  append(L"  trace(traceLine);");
                                                            #line 3365 "PrintCLike.cpp.template"
                                                                  }
                                                                }
                                                                if (useGlr)
                                                                {
                                                            #line 5369 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3370 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 5374 "PrintCLike.cpp"
  append(L"accepted = ");
                                                            #line 3371 "PrintCLike.cpp.template"
                                                                  if (isPython())
                                                                  {
                                                            #line 5379 "PrintCLike.cpp"
  append(L"T");
                                                            #line 3373 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 5385 "PrintCLike.cpp"
  append(L"t");
                                                            #line 3376 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 5389 "PrintCLike.cpp"
  append(L"rue");
                                                            #line 3377 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                            #line 5393 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3379 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 5398 "PrintCLike.cpp"
  append(L"action = 0");
                                                            #line 3380 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                            #line 5402 "PrintCLike.cpp"
  append(L"\n");
  append(L"  return ");
                                                            #line 3382 "PrintCLike.cpp.template"
                                                                  if (isHaxe() || isTypescript() || isPython()) print(staticPrefix());
                                                            #line 5407 "PrintCLike.cpp"
  append(L"ACCEPTED");
                                                            #line 3383 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                                else
                                                                {
                                                            #line 5414 "PrintCLike.cpp"
  append(L"\n");
  append(L"  return");
                                                            #line 3388 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }

                                                                if (useGlr)
                                                                {
                                                            #line 5423 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3394 "PrintCLike.cpp.template"
                                                                  if (isPython())
                                                                  {
                                                            #line 5428 "PrintCLike.cpp"
  append(L"\n");
  append(L"elif ");
                                                            #line 3397 "PrintCLike.cpp.template"
                                                                    if (useGlr) print(thiz());
                                                            #line 5433 "PrintCLike.cpp"
  append(L"action == ");
                                                            #line 3398 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 5439 "PrintCLike.cpp"
  append(L"\n");
  append(L"case ");
                                                            #line 3402 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(format.toString<wchar_t>((int) LrStates::FORK));
                                                                  print(caseIntroducer());
                                                            #line 5446 "PrintCLike.cpp"
  append(L" ");
                                                            #line 3405 "PrintCLike.cpp.template"
                                                                  print(inlineCommentIntroducer());
                                                            #line 5450 "PrintCLike.cpp"
  append(L"FORK");
                                                            #line 3406 "PrintCLike.cpp.template"
                                                                  if (trace)
                                                                  {
                                                                    if (isCpp())
                                                                    {
                                                            #line 5457 "PrintCLike.cpp"
  append(L"\n");
  append(L"  fprintf(stderr, \"fork\\\"/>\\n\");");
                                                            #line 3411 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 5464 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3415 "PrintCLike.cpp.template"
                                                                      print(writeTrace());
                                                            #line 5469 "PrintCLike.cpp"
  append(L"\"fork\\\"/>");
                                                            #line 3416 "PrintCLike.cpp.template"
                                                                      if (! isHaxe())
                                                                      {
                                                            #line 5474 "PrintCLike.cpp"
  append(L"\\n\"");
                                                            #line 3418 "PrintCLike.cpp.template"
                                                                        print(endWriteTrace());
                                                                        print(semicolon());
                                                                      }
                                                                      else
                                                                      {
                                                            #line 5482 "PrintCLike.cpp"
  append(L"\";\n");
  append(L"  trace(traceLine);");
                                                            #line 3424 "PrintCLike.cpp.template"
                                                                      }
                                                                    }
                                                                  }
                                                                  if (isGo())
                                                                  {
                                                            #line 5491 "PrintCLike.cpp"
  append(L"\n");
  append(L"  heap.Push(this.threads, new(ParsingThread).copy(this, appendix[argument]))");
                                                            #line 3431 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isPython())
                                                                  {
                                                            #line 5498 "PrintCLike.cpp"
  append(L"\n");
  append(L"  forked = ");
                                                            #line 3435 "PrintCLike.cpp.template"
                                                                    print(staticPrefix());
                                                            #line 5503 "PrintCLike.cpp"
  append(L"ParsingThread().copy(self, ");
                                                            #line 3436 "PrintCLike.cpp.template"
                                                                    print(staticPrefix());
                                                            #line 5507 "PrintCLike.cpp"
  append(L"APPENDIX[argument])\n");
  append(L"  heapq.heappush(self.threads, (False, forked.e0, forked.id, forked))");
                                                            #line 3439 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 5514 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3443 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 5519 "PrintCLike.cpp"
  append(L"threads");
                                                            #line 3444 "PrintCLike.cpp.template"
                                                                    if (isCpp())
                                                                    {
                                                            #line 5524 "PrintCLike.cpp"
  append(L"->push(");
                                                            #line 3446 "PrintCLike.cpp.template"
                                                                    }
                                                                    else if (isScala())
                                                                    {
                                                            #line 5530 "PrintCLike.cpp"
  append(L" += ");
                                                            #line 3449 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 5536 "PrintCLike.cpp"
  append(L".offer(");
                                                            #line 3452 "PrintCLike.cpp.template"
                                                                    }
                                                                    if (isCpp() || isScala()) print(L"(");
                                                            #line 5541 "PrintCLike.cpp"
  append(L"new ParsingThread");
                                                            #line 3454 "PrintCLike.cpp.template"
                                                                    if (! isScala()) print(L"()");
                                                                    if (isCpp() || isScala()) print(L")");
                                                                    print(arrow());
                                                            #line 5547 "PrintCLike.cpp"
  append(L"copy(this");
                                                            #line 3457 "PrintCLike.cpp.template"
                                                                    if (isJavascript())
                                                                    {
                                                            #line 5552 "PrintCLike.cpp"
  append(L"Thread");
                                                            #line 3459 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 5556 "PrintCLike.cpp"
  append(L", ");
                                                            #line 3460 "PrintCLike.cpp.template"
                                                                    print(staticPrefix());
                                                            #line 5560 "PrintCLike.cpp"
  append(L"APPENDIX");
                                                            #line 3461 "PrintCLike.cpp.template"
                                                                    print(leftbracket());
                                                            #line 5564 "PrintCLike.cpp"
  append(L"argument");
                                                            #line 3462 "PrintCLike.cpp.template"
                                                                    print(rightbracket());
                                                            #line 5568 "PrintCLike.cpp"
  append(L")");
                                                            #line 3463 "PrintCLike.cpp.template"
                                                                    if (! isScala()) print(L")");
                                                                    print(semicolon());
                                                                  }
                                                            #line 5574 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3467 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 5579 "PrintCLike.cpp"
  append(L"action = ");
                                                            #line 3468 "PrintCLike.cpp.template"
                                                                  print(staticPrefix());
                                                                  if (isGo())
                                                                  {
                                                            #line 5585 "PrintCLike.cpp"
  append(L"appendix");
                                                            #line 3471 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 5591 "PrintCLike.cpp"
  append(L"APPENDIX");
                                                            #line 3474 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(leftbracket());
                                                            #line 5596 "PrintCLike.cpp"
  append(L"argument + 1");
                                                            #line 3476 "PrintCLike.cpp.template"
                                                                  print(rightbracket());
                                                                  print(semicolon());
                                                            #line 5601 "PrintCLike.cpp"
  append(L"\n");
  append(L"  return ");
                                                            #line 3479 "PrintCLike.cpp.template"
                                                                  if (isHaxe() || isTypescript() || isPython()) print(staticPrefix());
                                                            #line 5606 "PrintCLike.cpp"
  append(L"PARSING");
                                                            #line 3480 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                            #line 5611 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3483 "PrintCLike.cpp.template"
                                                                if (isPython())
                                                                {
                                                            #line 5616 "PrintCLike.cpp"
  append(L"\n");
  append(L"else");
                                                            #line 3486 "PrintCLike.cpp.template"
                                                                }
                                                                else if (isScala())
                                                                {
                                                            #line 5623 "PrintCLike.cpp"
  append(L"\n");
  append(L"case _");
                                                            #line 3490 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 5630 "PrintCLike.cpp"
  append(L"\n");
  append(L"default");
                                                            #line 3494 "PrintCLike.cpp.template"
                                                                }
                                                                print(caseIntroducer());
                                                            #line 5636 "PrintCLike.cpp"
  append(L" ");
                                                            #line 3496 "PrintCLike.cpp.template"
                                                                print(inlineCommentIntroducer());
                                                            #line 5640 "PrintCLike.cpp"
  append(L"ERROR");
                                                            #line 3497 "PrintCLike.cpp.template"
                                                                if (useGlr)
                                                                {
                                                                  if (trace)
                                                                  {
                                                                    if (isCpp())
                                                                    {
                                                            #line 5649 "PrintCLike.cpp"
  append(L"\n");
  append(L"  fprintf(stderr, \"fail\\\"/>\\n\");");
                                                            #line 3504 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 5656 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3508 "PrintCLike.cpp.template"
                                                                      print(writeTrace());
                                                            #line 5661 "PrintCLike.cpp"
  append(L"\"fail\\\"/>");
                                                            #line 3509 "PrintCLike.cpp.template"
                                                                      if (! isHaxe())
                                                                      {
                                                            #line 5666 "PrintCLike.cpp"
  append(L"\\n\"");
                                                            #line 3511 "PrintCLike.cpp.template"
                                                                        print(endWriteTrace());
                                                                        print(semicolon());
                                                                      }
                                                                      else
                                                                      {
                                                            #line 5674 "PrintCLike.cpp"
  append(L"\";\n");
  append(L"  trace(traceLine);");
                                                            #line 3517 "PrintCLike.cpp.template"
                                                                      }
                                                                    }
                                                                  }
                                                            #line 5681 "PrintCLike.cpp"
  append(L"\n");
  append(L"  return ");
                                                            #line 3521 "PrintCLike.cpp.template"
                                                                  if (isHaxe() || isTypescript() || isPython()) print(staticPrefix());
                                                            #line 5686 "PrintCLike.cpp"
  append(L"ERROR");
                                                            #line 3522 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                                else
                                                                {
                                                            #line 5693 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3527 "PrintCLike.cpp.template"
                                                                  print(beginThrowStmt());
                                                                  print(thiz());
                                                            #line 5699 "PrintCLike.cpp"
  append(L"b1, ");
                                                            #line 3529 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 5703 "PrintCLike.cpp"
  append(L"e1, ");
                                                            #line 3530 "PrintCLike.cpp.template"
                                                                  print(staticPrefix());
                                                                  if (isGo())
                                                                  {
                                                            #line 5709 "PrintCLike.cpp"
  append(L"tokenset");
                                                            #line 3533 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 5715 "PrintCLike.cpp"
  append(L"TOKENSET");
                                                            #line 3536 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(leftbracket());
                                                            #line 5720 "PrintCLike.cpp"
  append(L"state");
                                                            #line 3538 "PrintCLike.cpp.template"
                                                                  print(rightbracket());
                                                            #line 5724 "PrintCLike.cpp"
  append(L" + 1, ");
                                                            #line 3539 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 5728 "PrintCLike.cpp"
  append(L"l1, -1");
                                                            #line 3540 "PrintCLike.cpp.template"
                                                                  print(endThrowStmt());
                                                                  print(semicolon());
                                                                }
                                                                print(rightBrace());
                                                            #line 5735 "PrintCLike.cpp"
  append(L"\n");
  append(L"\n");
  append(L"if ");
                                                            #line 3546 "PrintCLike.cpp.template"
                                                                print(ifLeftParen());
                                                            #line 5741 "PrintCLike.cpp"
  append(L"shift >= 0");
                                                            #line 3547 "PrintCLike.cpp.template"
                                                                print(ifRightParen());
                                                                print(leftBrace());
                                                                if (trace)
                                                                {
                                                                  if (isCpp())
                                                                  {
                                                            #line 5750 "PrintCLike.cpp"
  append(L"\n");
  append(L"  fprintf(stderr, ");
                                                            #line 3554 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 5757 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3558 "PrintCLike.cpp.template"
                                                                    print(writeTrace());
                                                                  }
                                                            #line 5763 "PrintCLike.cpp"
  append(L"\"shift\"");
                                                            #line 3560 "PrintCLike.cpp.template"
                                                                  print(endWriteTrace());
                                                                  print(semicolon());
                                                                }
                                                            #line 5769 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if ");
                                                            #line 3564 "PrintCLike.cpp.template"
                                                                print(ifLeftParen());
                                                            #line 5774 "PrintCLike.cpp"
  append(L"nonterminalId < 0");
                                                            #line 3565 "PrintCLike.cpp.template"
                                                                print(ifRightParen());
                                                                printIndented(1, leftBrace());
                                                                if (resolvesAmbiguity)
                                                                {
                                                            #line 5781 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 3570 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 5786 "PrintCLike.cpp"
  append(L"eventCount");
                                                            #line 3571 "PrintCLike.cpp.template"
                                                                  print(incrementOp());
                                                                  print(semicolon());
                                                                }
                                                                if (tree)
                                                                {
                                                            #line 5794 "PrintCLike.cpp"
  append(L"\n");
  append(L"    if ");
                                                            #line 3577 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                                  if (useGlr) print(thiz());
                                                            #line 5800 "PrintCLike.cpp"
  append(L"eventHandler != ");
                                                            #line 3579 "PrintCLike.cpp.template"
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
                                                            #line 5815 "PrintCLike.cpp"
  append(L"\n");
  append(L"      if ");
                                                            #line 3592 "PrintCLike.cpp.template"
                                                                    print(ifLeftParen());
                                                                    print(thiz());
                                                                    if (isGo())
                                                                    {
                                                            #line 5823 "PrintCLike.cpp"
  append(L"IsUnambiguous");
                                                            #line 3596 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 5829 "PrintCLike.cpp"
  append(L"isUnambiguous");
                                                            #line 3599 "PrintCLike.cpp.template"
                                                                    }
                                                                    if (! isScala()) print(L"()");
                                                                    print(ifRightParen());
                                                                    printIndented(3, leftBrace());
                                                                    increaseIndent();
                                                                  }
                                                            #line 5838 "PrintCLike.cpp"
  append(L"\n");
  append(L"      ");
                                                            #line 3606 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 5843 "PrintCLike.cpp"
  append(L"eventHandler");
                                                            #line 3607 "PrintCLike.cpp.template"
                                                                  if (shiftAmbiguity && isTypescript()) print(L"!");
                                                                  print(arrow());
                                                                  if (isGo())
                                                                  {
                                                            #line 5850 "PrintCLike.cpp"
  append(L"T");
                                                            #line 3611 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 5856 "PrintCLike.cpp"
  append(L"t");
                                                            #line 3614 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 5860 "PrintCLike.cpp"
  append(L"erminal(");
                                                            #line 3615 "PrintCLike.cpp.template"
                                                                  print(staticPrefix());
                                                                  print(isGo() ? L"token" : L"TOKEN");
                                                                  print(leftbracket());
                                                                  print(thiz());
                                                            #line 5867 "PrintCLike.cpp"
  append(L"l1");
                                                            #line 3619 "PrintCLike.cpp.template"
                                                                  print(rightbracket());
                                                            #line 5871 "PrintCLike.cpp"
  append(L", ");
                                                            #line 3620 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 5875 "PrintCLike.cpp"
  append(L"b1, ");
                                                            #line 3621 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 5879 "PrintCLike.cpp"
  append(L"e1)");
                                                            #line 3622 "PrintCLike.cpp.template"
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
                                                            #line 5892 "PrintCLike.cpp"
  append(L"\n");
  append(L"      ");
                                                            #line 3633 "PrintCLike.cpp.template"
                                                                    printIndented(3, elseWithBraces());
                                                            #line 5897 "PrintCLike.cpp"
  append(L"\n");
  append(L"        ");
                                                            #line 3635 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 5902 "PrintCLike.cpp"
  append(L"deferredEvent = ");
                                                            #line 3636 "PrintCLike.cpp.template"
                                                                    if (isGo())
                                                                    {
                                                            #line 5907 "PrintCLike.cpp"
  append(L"&TerminalEvent{&AbstractDeferredEvent{");
                                                            #line 3638 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                                      if (! isPython())
                                                                      {
                                                            #line 5915 "PrintCLike.cpp"
  append(L"new ");
                                                            #line 3643 "PrintCLike.cpp.template"
                                                                      }
                                                                      if (! isHaxe() && ! isTypescript()) print(staticPrefix());
                                                                      if (isJavascript() || isTypescript())
                                                                      {
                                                            #line 5922 "PrintCLike.cpp"
  append(L"DeferredEvent");
                                                            #line 3647 "PrintCLike.cpp.template"
                                                                      }
                                                                      else
                                                                      {
                                                            #line 5928 "PrintCLike.cpp"
  append(L"TerminalEvent");
                                                            #line 3650 "PrintCLike.cpp.template"
                                                                      }
                                                            #line 5932 "PrintCLike.cpp"
  append(L"(");
                                                            #line 3651 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(thiz());
                                                            #line 5937 "PrintCLike.cpp"
  append(L"deferredEvent, ");
                                                            #line 3653 "PrintCLike.cpp.template"
                                                                    print(staticPrefix());
                                                                    print(isGo() ? L"token" : L"TOKEN");
                                                                    print(leftbracket());
                                                                    print(thiz());
                                                            #line 5944 "PrintCLike.cpp"
  append(L"l1");
                                                            #line 3657 "PrintCLike.cpp.template"
                                                                    print(rightbracket());
                                                            #line 5948 "PrintCLike.cpp"
  append(L", ");
                                                            #line 3658 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 5952 "PrintCLike.cpp"
  append(L"b1, ");
                                                            #line 3659 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 5956 "PrintCLike.cpp"
  append(L"e1");
                                                            #line 3660 "PrintCLike.cpp.template"
                                                                    if (isTypescript())
                                                                    {
                                                            #line 5961 "PrintCLike.cpp"
  append(L", -1");
                                                            #line 3663 "PrintCLike.cpp.template"
                                                                    }
                                                                    if (isGo())
                                                                    {
                                                            #line 5967 "PrintCLike.cpp"
  append(L"}}");
                                                            #line 3667 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 5973 "PrintCLike.cpp"
  append(L")");
                                                            #line 3671 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                                    }
                                                                    increaseIndent(3);
                                                                    print(rightBrace());
                                                                    decreaseIndent();
                                                                    print(rightBrace());
                                                                    decreaseIndent(2);
                                                                  }
                                                            #line 5984 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 3680 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 5989 "PrintCLike.cpp"
  append(L"es = ");
                                                            #line 3681 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 5993 "PrintCLike.cpp"
  append(L"e1");
                                                            #line 3682 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                                if (useGlr)
                                                                {
                                                            #line 6000 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 3687 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 6005 "PrintCLike.cpp"
  append(L"stack = ");
                                                            #line 3688 "PrintCLike.cpp.template"
                                                                  if (isGo())
                                                                  {
                                                            #line 6010 "PrintCLike.cpp"
  append(L"&StackNode{");
                                                            #line 3690 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                                    if (! isPython())
                                                                    {
                                                            #line 6018 "PrintCLike.cpp"
  append(L"new ");
                                                            #line 3695 "PrintCLike.cpp.template"
                                                                    }
                                                                    if (! isHaxe() && ! isTypescript()) print(staticPrefix());
                                                            #line 6023 "PrintCLike.cpp"
  append(L"StackNode(");
                                                            #line 3697 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(thiz());
                                                            #line 6028 "PrintCLike.cpp"
  append(L"state, ");
                                                            #line 3699 "PrintCLike.cpp.template"
                                                                  if (grammar->states->hasLookback)
                                                                  {
                                                            #line 6033 "PrintCLike.cpp"
  append(L"lookback, ");
                                                            #line 3701 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(thiz());
                                                            #line 6038 "PrintCLike.cpp"
  append(L"b1, ");
                                                            #line 3703 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 6042 "PrintCLike.cpp"
  append(L"stack");
                                                            #line 3704 "PrintCLike.cpp.template"
                                                                  print(isGo() ? L"}" : L")");
                                                                  print(semicolon());
                                                                }
                                                                else
                                                                {
                                                            #line 6050 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 3710 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 6055 "PrintCLike.cpp"
  append(L"push(state, lookback");
                                                            #line 3711 "PrintCLike.cpp.template"
                                                                  if (tree)
                                                                  {
                                                            #line 6060 "PrintCLike.cpp"
  append(L", ");
                                                            #line 3713 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 6064 "PrintCLike.cpp"
  append(L"b1");
                                                            #line 3714 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 6068 "PrintCLike.cpp"
  append(L")");
                                                            #line 3715 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                            #line 6073 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 3718 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 6078 "PrintCLike.cpp"
  append(L"consume(");
                                                            #line 3719 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 6082 "PrintCLike.cpp"
  append(L"l1)");
                                                            #line 3720 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 6086 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3722 "PrintCLike.cpp.template"
                                                                printIndented(1, elseWithBraces());
                                                                if (useGlr)
                                                                {
                                                            #line 6093 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 3726 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 6098 "PrintCLike.cpp"
  append(L"stack = ");
                                                            #line 3727 "PrintCLike.cpp.template"
                                                                  if (isGo())
                                                                  {
                                                            #line 6103 "PrintCLike.cpp"
  append(L"&StackNode{");
                                                            #line 3729 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                                    if (! isPython())
                                                                    {
                                                            #line 6111 "PrintCLike.cpp"
  append(L"new ");
                                                            #line 3734 "PrintCLike.cpp.template"
                                                                    }
                                                                    if (! isHaxe() && ! isTypescript()) print(staticPrefix());
                                                            #line 6116 "PrintCLike.cpp"
  append(L"StackNode(");
                                                            #line 3736 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(thiz());
                                                            #line 6121 "PrintCLike.cpp"
  append(L"state, ");
                                                            #line 3738 "PrintCLike.cpp.template"
                                                                  if (grammar->states->hasLookback)
                                                                  {
                                                            #line 6126 "PrintCLike.cpp"
  append(L"lookback, ");
                                                            #line 3740 "PrintCLike.cpp.template"
                                                                  }
                                                                  if (tree)
                                                                  {
                                                                    print(thiz());
                                                            #line 6133 "PrintCLike.cpp"
  append(L"bs");
                                                            #line 3744 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 6139 "PrintCLike.cpp"
  append(L"0");
                                                            #line 3747 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 6143 "PrintCLike.cpp"
  append(L", ");
                                                            #line 3748 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 6147 "PrintCLike.cpp"
  append(L"stack");
                                                            #line 3749 "PrintCLike.cpp.template"
                                                                  print(isGo() ? L"}" : L")");
                                                                  print(semicolon());
                                                                }
                                                                else
                                                                {
                                                            #line 6155 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 3755 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 6160 "PrintCLike.cpp"
  append(L"push(state, lookback");
                                                            #line 3756 "PrintCLike.cpp.template"
                                                                  if (tree)
                                                                  {
                                                            #line 6165 "PrintCLike.cpp"
  append(L", bs");
                                                            #line 3758 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 6169 "PrintCLike.cpp"
  append(L")");
                                                            #line 3759 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                                increaseIndent();
                                                                print(rightBrace());
                                                                decreaseIndent();
                                                            #line 6177 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3765 "PrintCLike.cpp.template"
                                                                if (useGlr) print(thiz());
                                                            #line 6182 "PrintCLike.cpp"
  append(L"state = shift");
                                                            #line 3766 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                print(rightBrace());
                                                            #line 6187 "PrintCLike.cpp"
  append(L"\n");
  append(L"\n");
  append(L"if ");
                                                            #line 3770 "PrintCLike.cpp.template"
                                                                print(ifLeftParen());
                                                            #line 6193 "PrintCLike.cpp"
  append(L"reduce < 0");
                                                            #line 3771 "PrintCLike.cpp.template"
                                                                print(ifRightParen());
                                                                print(leftBrace());
                                                                if (trace)
                                                                {
                                                                  if (isCpp())
                                                                  {
                                                            #line 6202 "PrintCLike.cpp"
  append(L"\n");
  append(L"  fprintf(stderr, ");
                                                            #line 3778 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 6209 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3782 "PrintCLike.cpp.template"
                                                                    print(writeTrace());
                                                                  }
                                                            #line 6215 "PrintCLike.cpp"
  append(L"\"\\\"/>");
                                                            #line 3784 "PrintCLike.cpp.template"
                                                                  if (! isHaxe())
                                                                  {
                                                            #line 6220 "PrintCLike.cpp"
  append(L"\\n\"");
                                                            #line 3786 "PrintCLike.cpp.template"
                                                                    print(endWriteTrace());
                                                                    print(semicolon());
                                                                  }
                                                                  else
                                                                  {
                                                            #line 6228 "PrintCLike.cpp"
  append(L"\";\n");
  append(L"  trace(traceLine);");
                                                            #line 3792 "PrintCLike.cpp.template"
                                                                  }
                                                                }
                                                            #line 6234 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3795 "PrintCLike.cpp.template"
                                                                if (useGlr) print(thiz());
                                                            #line 6239 "PrintCLike.cpp"
  append(L"action = ");
                                                            #line 3796 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 6243 "PrintCLike.cpp"
  append(L"predict(");
                                                            #line 3797 "PrintCLike.cpp.template"
                                                                if (useGlr) print(thiz());
                                                            #line 6247 "PrintCLike.cpp"
  append(L"state)");
                                                            #line 3798 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                if (useGlr)
                                                                {
                                                                  if (isCpp())
                                                                  {
                                                            #line 6255 "PrintCLike.cpp"
  append(L"\n");
  append(L"  break");
                                                            #line 3804 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                  }
                                                                  else
                                                                  {
                                                            #line 6263 "PrintCLike.cpp"
  append(L"\n");
  append(L"  return ");
                                                            #line 3809 "PrintCLike.cpp.template"
                                                                    if (isHaxe() || isTypescript() || isPython()) print(staticPrefix());
                                                            #line 6268 "PrintCLike.cpp"
  append(L"PARSING");
                                                            #line 3810 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                  }
                                                                }
                                                                else
                                                                {
                                                            #line 6276 "PrintCLike.cpp"
  append(L"\n");
  append(L"  nonterminalId = -1");
                                                            #line 3816 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                            #line 6282 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3819 "PrintCLike.cpp.template"
                                                                print(elseWithBraces());
                                                                if (hasCustomCode)
                                                                {
                                                            #line 6288 "PrintCLike.cpp"
  append(L"\n");
  append(L"  nonterminalId = ");
                                                            #line 3823 "PrintCLike.cpp.template"
                                                                  print(staticPrefix());
                                                                  if (isGo())
                                                                  {
                                                            #line 6295 "PrintCLike.cpp"
  append(L"reduction");
                                                            #line 3826 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 6301 "PrintCLike.cpp"
  append(L"REDUCTION");
                                                            #line 3829 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(leftbracket());
                                                            #line 6306 "PrintCLike.cpp"
  append(L"reduce");
                                                            #line 3831 "PrintCLike.cpp.template"
                                                                  print(rightbracket());
                                                                  print(semicolon());
                                                            #line 6311 "PrintCLike.cpp"
  append(L"\n");
  append(L"  reduce = ");
                                                            #line 3834 "PrintCLike.cpp.template"
                                                                  print(staticPrefix());
                                                                  if (isGo())
                                                                  {
                                                            #line 6318 "PrintCLike.cpp"
  append(L"reduction");
                                                            #line 3837 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 6324 "PrintCLike.cpp"
  append(L"REDUCTION");
                                                            #line 3840 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(leftbracket());
                                                            #line 6329 "PrintCLike.cpp"
  append(L"reduce + 1");
                                                            #line 3842 "PrintCLike.cpp.template"
                                                                  print(rightbracket());
                                                                  print(semicolon());
                                                            #line 6334 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if ");
                                                            #line 3845 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                            #line 6339 "PrintCLike.cpp"
  append(L"reduce >= 0");
                                                            #line 3846 "PrintCLike.cpp.template"
                                                                  print(ifRightParen());
                                                                  increaseIndent();
                                                                  print(leftBrace());
                                                                  if (useGlr)
                                                                  {
                                                            #line 6347 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if ");
                                                            #line 3852 "PrintCLike.cpp.template"
                                                                    print(ifLeftParen());
                                                                    print(thiz());
                                                                    if (isGo())
                                                                    {
                                                            #line 6355 "PrintCLike.cpp"
  append(L"IsUnambiguous");
                                                            #line 3856 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 6361 "PrintCLike.cpp"
  append(L"isUnambiguous");
                                                            #line 3859 "PrintCLike.cpp.template"
                                                                    }
                                                                    if (! isScala()) print(L"()");
                                                                    print(ifRightParen());
                                                                    print(leftBrace());
                                                            #line 6368 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 3864 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                                    print(isGo() && useGlr ? L"E" : L"e");
                                                            #line 6374 "PrintCLike.cpp"
  append(L"xecute(reduce)");
                                                            #line 3866 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 6378 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3868 "PrintCLike.cpp.template"
                                                                    print(elseWithBraces());
                                                            #line 6383 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 3870 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 6388 "PrintCLike.cpp"
  append(L"deferredCode = ");
                                                            #line 3871 "PrintCLike.cpp.template"
                                                                    if (isGo())
                                                                    {
                                                            #line 6393 "PrintCLike.cpp"
  append(L"&DeferredCode{");
                                                            #line 3873 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                                      if (! isPython())
                                                                      {
                                                            #line 6401 "PrintCLike.cpp"
  append(L"new ");
                                                            #line 3878 "PrintCLike.cpp.template"
                                                                      }
                                                                      if (! isHaxe() && ! isTypescript()) print(staticPrefix());
                                                            #line 6406 "PrintCLike.cpp"
  append(L"DeferredCode(");
                                                            #line 3880 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(thiz());
                                                            #line 6411 "PrintCLike.cpp"
  append(L"deferredCode, reduce, ");
                                                            #line 3882 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 6415 "PrintCLike.cpp"
  append(L"b0, ");
                                                            #line 3883 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 6419 "PrintCLike.cpp"
  append(L"e0");
                                                            #line 3885 "PrintCLike.cpp.template"
                                                                    if (isGo())
                                                                    {
                                                            #line 6424 "PrintCLike.cpp"
  append(L"}");
                                                            #line 3888 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 6430 "PrintCLike.cpp"
  append(L")");
                                                            #line 3892 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(semicolon());
                                                                    increaseIndent();
                                                                    print(rightBrace());
                                                                    decreaseIndent();
                                                                  }
                                                                  else
                                                                  {
                                                            #line 6441 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3901 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                                    print(isGo() && useGlr ? L"E" : L"e");
                                                            #line 6447 "PrintCLike.cpp"
  append(L"xecute(reduce)");
                                                            #line 3903 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                  }
                                                                  print(rightBrace());
                                                                  decreaseIndent();
                                                                }
                                                                else
                                                                {
                                                            #line 6457 "PrintCLike.cpp"
  append(L"\n");
  append(L"  nonterminalId = reduce");
                                                            #line 3911 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                                if (resolvesAmbiguity)
                                                                {
                                                            #line 6465 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3916 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 6470 "PrintCLike.cpp"
  append(L"eventCount");
                                                            #line 3917 "PrintCLike.cpp.template"
                                                                  print(incrementOp());
                                                                  print(semicolon());
                                                                }
                                                                if (trace)
                                                                {
                                                            #line 6478 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if ");
                                                            #line 3923 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                            #line 6483 "PrintCLike.cpp"
  append(L"shift >= 0");
                                                            #line 3924 "PrintCLike.cpp.template"
                                                                  print(ifRightParen());
                                                                  printIndented(1, leftBrace());
                                                                  if (isCpp())
                                                                  {
                                                            #line 6490 "PrintCLike.cpp"
  append(L"\n");
  append(L"    fprintf(stderr, ");
                                                            #line 3929 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 6497 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 3933 "PrintCLike.cpp.template"
                                                                    print(writeTrace());
                                                                  }
                                                            #line 6503 "PrintCLike.cpp"
  append(L"\" \"");
                                                            #line 3935 "PrintCLike.cpp.template"
                                                                  print(endWriteTrace());
                                                                  print(semicolon());
                                                                  increaseIndent();
                                                                  print(rightBrace());
                                                                  decreaseIndent();
                                                                  if (isCpp())
                                                                  {
                                                            #line 6513 "PrintCLike.cpp"
  append(L"\n");
  append(L"  fprintf(stderr, \"reduce\\\" nonterminal=\\\"%s\\\" count=\\\"%d\\\"/>\\n\", ");
                                                            #line 3943 "PrintCLike.cpp.template"
                                                                    if (stringIntroducer()[0])
                                                                    {
                                                            #line 6519 "PrintCLike.cpp"
  append(L"Utf8Encoder::encode(");
                                                            #line 3945 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 6523 "PrintCLike.cpp"
  append(L"xmlEscape(");
                                                            #line 3946 "PrintCLike.cpp.template"
                                                                    print(isGo() ? L"nonterminal" : L"NONTERMINAL");
                                                            #line 6527 "PrintCLike.cpp"
  append(L"[nonterminalId], 0).c_str()");
                                                            #line 3948 "PrintCLike.cpp.template"
                                                                    if (stringIntroducer()[0])
                                                                    {
                                                            #line 6532 "PrintCLike.cpp"
  append(L").c_str()");
                                                            #line 3950 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 6536 "PrintCLike.cpp"
  append(L", symbols);");
                                                            #line 3951 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 6542 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3955 "PrintCLike.cpp.template"
                                                                    print(writeTrace());
                                                            #line 6547 "PrintCLike.cpp"
  append(L"\"reduce\\\" nonterminal=\\\"\" + ");
                                                            #line 3956 "PrintCLike.cpp.template"
                                                                    print(staticPrefix());
                                                            #line 6551 "PrintCLike.cpp"
  append(L"xmlEscape(");
                                                            #line 3957 "PrintCLike.cpp.template"
                                                                    print(staticPrefix());
                                                                    print(isGo() ? L"nonterminal" : L"NONTERMINAL");
                                                                    print(leftbracket());
                                                            #line 6557 "PrintCLike.cpp"
  append(L"nonterminalId");
                                                            #line 3960 "PrintCLike.cpp.template"
                                                                    print(rightbracket());
                                                            #line 6561 "PrintCLike.cpp"
  append(L") + \"\\\" count=\\\"\" + ");
                                                            #line 3962 "PrintCLike.cpp.template"
                                                                    if (isPython())
                                                                    {
                                                            #line 6566 "PrintCLike.cpp"
  append(L"str(");
                                                            #line 3965 "PrintCLike.cpp.template"
                                                                    }
                                                                    else if (isGo())
                                                                    {
                                                            #line 6572 "PrintCLike.cpp"
  append(L"strconv.Itoa(");
                                                            #line 3969 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 6576 "PrintCLike.cpp"
  append(L"symbols");
                                                            #line 3971 "PrintCLike.cpp.template"
                                                                    if (isGo() || isPython())
                                                                    {
                                                            #line 6581 "PrintCLike.cpp"
  append(L")");
                                                            #line 3974 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 6585 "PrintCLike.cpp"
  append(L" + \"\\\"/>");
                                                            #line 3976 "PrintCLike.cpp.template"
                                                                    if (! isHaxe())
                                                                    {
                                                            #line 6590 "PrintCLike.cpp"
  append(L"\\n\"");
                                                            #line 3978 "PrintCLike.cpp.template"
                                                                      print(endWriteTrace());
                                                                      print(semicolon());
                                                                    }
                                                                    else
                                                                    {
                                                            #line 6598 "PrintCLike.cpp"
  append(L"\";\n");
  append(L"  trace(traceLine);");
                                                            #line 3984 "PrintCLike.cpp.template"
                                                                    }
                                                                  }
                                                                }
                                                                if (tree)
                                                                {
                                                            #line 6607 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if ");
                                                            #line 3990 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                                  print(thiz());
                                                            #line 6613 "PrintCLike.cpp"
  append(L"l1 == 0");
                                                            #line 3992 "PrintCLike.cpp.template"
                                                                  print(ifRightParen());
                                                                  printIndented(1, leftBrace());
                                                            #line 6618 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 3995 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 6623 "PrintCLike.cpp"
  append(L"b1 = ");
                                                            #line 3996 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 6627 "PrintCLike.cpp"
  append(L"e0");
                                                            #line 3997 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                  increaseIndent();
                                                                  print(rightBrace());
                                                                  decreaseIndent();
                                                            #line 6634 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if ");
                                                            #line 4002 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                            #line 6639 "PrintCLike.cpp"
  append(L"symbols > 0");
                                                            #line 4003 "PrintCLike.cpp.template"
                                                                  print(ifRightParen());
                                                                  printIndented(1, leftBrace());
                                                                  if (useGlr)
                                                                  {
                                                                    if (isCpp())
                                                                    {
                                                            #line 6648 "PrintCLike.cpp"
  append(L"\n");
  append(L"    stack = stack->pop(symbols - 1);");
                                                            #line 4010 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                                      increaseIndent(2);
                                                                      if (isHaxe())
                                                                      {
                                                            #line 6658 "PrintCLike.cpp"
  append(L"\n");
  append(L"for (i in 1...symbols)");
                                                            #line 4017 "PrintCLike.cpp.template"
                                                                      }
                                                                      else if (isScala())
                                                                      {
                                                            #line 6665 "PrintCLike.cpp"
  append(L"\n");
  append(L"var i = 0\n");
  append(L"for (i <- 2 to symbols)");
                                                            #line 4022 "PrintCLike.cpp.template"
                                                                      }
                                                                      else if (isPython())
                                                                      {
                                                            #line 6673 "PrintCLike.cpp"
  append(L"\n");
  append(L"for _ in range(symbols - 1):");
                                                            #line 4026 "PrintCLike.cpp.template"
                                                                      }
                                                                      else
                                                                      {
                                                            #line 6680 "PrintCLike.cpp"
  append(L"\n");
  append(L"for ");
                                                            #line 4030 "PrintCLike.cpp.template"
                                                                        print(ifLeftParen());
                                                                        print(intVar());
                                                            #line 6686 "PrintCLike.cpp"
  append(L"i");
                                                            #line 4032 "PrintCLike.cpp.template"
                                                                        print(assign());
                                                            #line 6690 "PrintCLike.cpp"
  append(L"1; i < symbols; i++");
                                                            #line 4033 "PrintCLike.cpp.template"
                                                                        print(ifRightParen());
                                                                      }
                                                                      print(leftBrace());
                                                            #line 6696 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4037 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 6701 "PrintCLike.cpp"
  append(L"stack = ");
                                                            #line 4038 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 6705 "PrintCLike.cpp"
  append(L"stack.link");
                                                            #line 4039 "PrintCLike.cpp.template"
                                                                      if (isTypescript()) print(L"!");
                                                                      print(semicolon());
                                                                      print(rightBrace());
                                                                      decreaseIndent(2);
                                                                    }
                                                            #line 6713 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4045 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 6718 "PrintCLike.cpp"
  append(L"state = ");
                                                            #line 4046 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 6722 "PrintCLike.cpp"
  append(L"stack");
                                                            #line 4047 "PrintCLike.cpp.template"
                                                                    print(arrow());
                                                            #line 6726 "PrintCLike.cpp"
  append(L"state");
                                                            #line 4048 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 6730 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4050 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 6735 "PrintCLike.cpp"
  append(L"bs = ");
                                                            #line 4051 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 6739 "PrintCLike.cpp"
  append(L"stack");
                                                            #line 4052 "PrintCLike.cpp.template"
                                                                    print(arrow());
                                                            #line 6743 "PrintCLike.cpp"
  append(L"pos");
                                                            #line 4053 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                    if (isCpp())
                                                                    {
                                                            #line 6749 "PrintCLike.cpp"
  append(L"\n");
  append(L"    stack = stack->pop(1);");
                                                            #line 4057 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 6756 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4061 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 6761 "PrintCLike.cpp"
  append(L"stack = ");
                                                            #line 4062 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 6765 "PrintCLike.cpp"
  append(L"stack.link");
                                                            #line 4063 "PrintCLike.cpp.template"
                                                                      if (isTypescript()) print(L"!");
                                                                      print(semicolon());
                                                                    }
                                                                  }
                                                                  else
                                                                  {
                                                            #line 6774 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4070 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 6779 "PrintCLike.cpp"
  append(L"top -= symbols * 3");
                                                            #line 4071 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 6783 "PrintCLike.cpp"
  append(L"\n");
  append(L"    state = ");
                                                            #line 4073 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 6788 "PrintCLike.cpp"
  append(L"iStack");
                                                            #line 4074 "PrintCLike.cpp.template"
                                                                    print(leftbracket());
                                                                    print(thiz());
                                                            #line 6793 "PrintCLike.cpp"
  append(L"top + 2");
                                                            #line 4076 "PrintCLike.cpp.template"
                                                                    print(rightbracket());
                                                                    print(semicolon());
                                                            #line 6798 "PrintCLike.cpp"
  append(L"\n");
  append(L"    bs = ");
                                                            #line 4079 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 6803 "PrintCLike.cpp"
  append(L"iStack");
                                                            #line 4080 "PrintCLike.cpp.template"
                                                                    print(leftbracket());
                                                                    print(thiz());
                                                            #line 6808 "PrintCLike.cpp"
  append(L"top + 1");
                                                            #line 4082 "PrintCLike.cpp.template"
                                                                    print(rightbracket());
                                                                    print(semicolon());
                                                                  }
                                                            #line 6814 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4086 "PrintCLike.cpp.template"
                                                                  printIndented(1, elseWithBraces());
                                                            #line 6819 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4088 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 6824 "PrintCLike.cpp"
  append(L"bs = ");
                                                            #line 4089 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 6828 "PrintCLike.cpp"
  append(L"b1");
                                                            #line 4090 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                            #line 6832 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4092 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 6837 "PrintCLike.cpp"
  append(L"es = ");
                                                            #line 4093 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 6841 "PrintCLike.cpp"
  append(L"b1");
                                                            #line 4094 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                  increaseIndent();
                                                                  print(rightBrace());
                                                                  decreaseIndent();
                                                            #line 6848 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if ");
                                                            #line 4099 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                            #line 6853 "PrintCLike.cpp"
  append(L"nonterminalId == ");
                                                            #line 4100 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 6857 "PrintCLike.cpp"
  append(L"target ");
                                                            #line 4101 "PrintCLike.cpp.template"
                                                                  if (isPython())
                                                                  {
                                                            #line 6862 "PrintCLike.cpp"
  append(L"and");
                                                            #line 4103 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 6868 "PrintCLike.cpp"
  append(L"&&");
                                                            #line 4106 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 6872 "PrintCLike.cpp"
  append(L" ");
                                                            #line 4107 "PrintCLike.cpp.template"
                                                                  if (useGlr)
                                                                  {
                                                                    print(thiz());
                                                            #line 6878 "PrintCLike.cpp"
  append(L"stack");
                                                            #line 4110 "PrintCLike.cpp.template"
                                                                    print(arrow());
                                                            #line 6882 "PrintCLike.cpp"
  append(L"link == ");
                                                            #line 4111 "PrintCLike.cpp.template"
                                                                    print(nullPtr());
                                                                  }
                                                                  else
                                                                  {
                                                            #line 6889 "PrintCLike.cpp"
  append(L"t == ");
                                                            #line 4115 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 6893 "PrintCLike.cpp"
  append(L"top");
                                                            #line 4116 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(ifRightParen());
                                                                  printIndented(1, leftBrace());
                                                            #line 6899 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4120 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 6904 "PrintCLike.cpp"
  append(L"bs = ");
                                                            #line 4121 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 6908 "PrintCLike.cpp"
  append(L"bw");
                                                            #line 4122 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                            #line 6912 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4124 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 6917 "PrintCLike.cpp"
  append(L"es = ");
                                                            #line 4125 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 6921 "PrintCLike.cpp"
  append(L"b1");
                                                            #line 4126 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                            #line 6925 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4128 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 6930 "PrintCLike.cpp"
  append(L"bw = ");
                                                            #line 4129 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 6934 "PrintCLike.cpp"
  append(L"b1");
                                                            #line 4130 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                  increaseIndent();
                                                                  print(rightBrace());
                                                                  decreaseIndent();
                                                            #line 6941 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if ");
                                                            #line 4135 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                                  if (useGlr) print(thiz());
                                                            #line 6947 "PrintCLike.cpp"
  append(L"eventHandler != ");
                                                            #line 4137 "PrintCLike.cpp.template"
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
                                                            #line 6962 "PrintCLike.cpp"
  append(L"\n");
  append(L"    if ");
                                                            #line 4150 "PrintCLike.cpp.template"
                                                                    print(ifLeftParen());
                                                                    print(thiz());
                                                                    if (isGo())
                                                                    {
                                                            #line 6970 "PrintCLike.cpp"
  append(L"IsUnambiguous");
                                                            #line 4154 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 6976 "PrintCLike.cpp"
  append(L"isUnambiguous");
                                                            #line 4157 "PrintCLike.cpp.template"
                                                                    }
                                                                    if (! isScala()) print(L"()");
                                                                    print(ifRightParen());
                                                                    printIndented(2, leftBrace());
                                                                    increaseIndent();
                                                                  }
                                                            #line 6985 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4164 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 6990 "PrintCLike.cpp"
  append(L"eventHandler");
                                                            #line 4165 "PrintCLike.cpp.template"
                                                                  if (shiftAmbiguity && isTypescript()) print(L"!");
                                                                  print(arrow());
                                                                  if (isGo())
                                                                  {
                                                            #line 6997 "PrintCLike.cpp"
  append(L"N");
                                                            #line 4169 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 7003 "PrintCLike.cpp"
  append(L"n");
                                                            #line 4172 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 7007 "PrintCLike.cpp"
  append(L"onterminal(");
                                                            #line 4173 "PrintCLike.cpp.template"
                                                                  print(staticPrefix());
                                                                  print(isGo() ? L"nonterminal" : L"NONTERMINAL");
                                                                  print(leftbracket());
                                                            #line 7013 "PrintCLike.cpp"
  append(L"nonterminalId");
                                                            #line 4176 "PrintCLike.cpp.template"
                                                                  print(rightbracket());
                                                            #line 7017 "PrintCLike.cpp"
  append(L", ");
                                                            #line 4177 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 7021 "PrintCLike.cpp"
  append(L"bs, ");
                                                            #line 4178 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 7025 "PrintCLike.cpp"
  append(L"es, symbols)");
                                                            #line 4180 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                  if (useGlr)
                                                                  {
                                                                    decreaseIndent();
                                                            #line 7032 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4185 "PrintCLike.cpp.template"
                                                                    printIndented(2, elseWithBraces());
                                                            #line 7037 "PrintCLike.cpp"
  append(L"\n");
  append(L"      ");
                                                            #line 4187 "PrintCLike.cpp.template"
                                                                    if (useGlr) print(thiz());
                                                            #line 7042 "PrintCLike.cpp"
  append(L"deferredEvent = ");
                                                            #line 4188 "PrintCLike.cpp.template"
                                                                    if (isGo())
                                                                    {
                                                            #line 7047 "PrintCLike.cpp"
  append(L"&NonterminalEvent{&AbstractDeferredEvent{this.deferredEvent, nonterminal[nonterminalId], this.bs, this.es}, symbols}");
                                                            #line 4191 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                                      if (! isPython())
                                                                      {
                                                            #line 7055 "PrintCLike.cpp"
  append(L"new ");
                                                            #line 4196 "PrintCLike.cpp.template"
                                                                      }
                                                                      if (! isHaxe() && ! isTypescript()) print(staticPrefix());
                                                                      if (isJavascript() || isTypescript())
                                                                      {
                                                            #line 7062 "PrintCLike.cpp"
  append(L"DeferredEvent");
                                                            #line 4200 "PrintCLike.cpp.template"
                                                                      }
                                                                      else
                                                                      {
                                                            #line 7068 "PrintCLike.cpp"
  append(L"NonterminalEvent");
                                                            #line 4203 "PrintCLike.cpp.template"
                                                                      }
                                                            #line 7072 "PrintCLike.cpp"
  append(L"(");
                                                            #line 4204 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 7076 "PrintCLike.cpp"
  append(L"deferredEvent, ");
                                                            #line 4205 "PrintCLike.cpp.template"
                                                                      print(staticPrefix());
                                                            #line 7080 "PrintCLike.cpp"
  append(L"NONTERMINAL");
                                                            #line 4206 "PrintCLike.cpp.template"
                                                                      print(leftbracket());
                                                            #line 7084 "PrintCLike.cpp"
  append(L"nonterminalId");
                                                            #line 4207 "PrintCLike.cpp.template"
                                                                      print(rightbracket());
                                                            #line 7088 "PrintCLike.cpp"
  append(L", ");
                                                            #line 4208 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 7092 "PrintCLike.cpp"
  append(L"bs, ");
                                                            #line 4209 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 7096 "PrintCLike.cpp"
  append(L"es, symbols)");
                                                            #line 4211 "PrintCLike.cpp.template"
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
                                                            #line 7111 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if ");
                                                            #line 4224 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                            #line 7116 "PrintCLike.cpp"
  append(L"symbols > 0");
                                                            #line 4225 "PrintCLike.cpp.template"
                                                                  print(ifRightParen());
                                                                  printIndented(1, leftBrace());
                                                                  if (useGlr)
                                                                  {
                                                                    if (isCpp())
                                                                    {
                                                            #line 7125 "PrintCLike.cpp"
  append(L"\n");
  append(L"    stack = stack->pop(symbols - 1);");
                                                            #line 4232 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                                      increaseIndent(2);
                                                                      if (isHaxe())
                                                                      {
                                                            #line 7135 "PrintCLike.cpp"
  append(L"\n");
  append(L"for (i in 1...symbols)");
                                                            #line 4239 "PrintCLike.cpp.template"
                                                                      }
                                                                      else if (isScala())
                                                                      {
                                                            #line 7142 "PrintCLike.cpp"
  append(L"\n");
  append(L"var i = 0\n");
  append(L"for (i <- 2 to symbols)");
                                                            #line 4244 "PrintCLike.cpp.template"
                                                                      }
                                                                      else if (isPython())
                                                                      {
                                                            #line 7150 "PrintCLike.cpp"
  append(L"\n");
  append(L"for _ in range(symbols - 1):");
                                                            #line 4248 "PrintCLike.cpp.template"
                                                                      }
                                                                      else
                                                                      {
                                                            #line 7157 "PrintCLike.cpp"
  append(L"\n");
  append(L"for ");
                                                            #line 4252 "PrintCLike.cpp.template"
                                                                        print(ifLeftParen());
                                                                        print(intVar());
                                                            #line 7163 "PrintCLike.cpp"
  append(L"i");
                                                            #line 4254 "PrintCLike.cpp.template"
                                                                        print(assign());
                                                            #line 7167 "PrintCLike.cpp"
  append(L"1; i < symbols; i++");
                                                            #line 4255 "PrintCLike.cpp.template"
                                                                        print(ifRightParen());
                                                                      }
                                                                      print(leftBrace());
                                                            #line 7173 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4259 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 7178 "PrintCLike.cpp"
  append(L"stack = ");
                                                            #line 4260 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 7182 "PrintCLike.cpp"
  append(L"stack.link");
                                                            #line 4261 "PrintCLike.cpp.template"
                                                                      if (isTypescript()) print(L"!");
                                                                      print(semicolon());
                                                                      print(rightBrace());
                                                                      decreaseIndent(2);
                                                                    }
                                                            #line 7190 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4268 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7195 "PrintCLike.cpp"
  append(L"state = ");
                                                            #line 4269 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7199 "PrintCLike.cpp"
  append(L"stack");
                                                            #line 4270 "PrintCLike.cpp.template"
                                                                    print(arrow());
                                                            #line 7203 "PrintCLike.cpp"
  append(L"state");
                                                            #line 4271 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                    if (tree)
                                                                    {
                                                            #line 7209 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4275 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 7214 "PrintCLike.cpp"
  append(L"bs = ");
                                                            #line 4276 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 7218 "PrintCLike.cpp"
  append(L"stack");
                                                            #line 4277 "PrintCLike.cpp.template"
                                                                      print(arrow());
                                                            #line 7222 "PrintCLike.cpp"
  append(L"pos");
                                                            #line 4278 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                                    }
                                                                    if (isCpp())
                                                                    {
                                                            #line 7229 "PrintCLike.cpp"
  append(L"\n");
  append(L"    stack = stack->pop(1);");
                                                            #line 4283 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 7236 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4287 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 7241 "PrintCLike.cpp"
  append(L"stack = ");
                                                            #line 4288 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 7245 "PrintCLike.cpp"
  append(L"stack.link");
                                                            #line 4289 "PrintCLike.cpp.template"
                                                                      if (isTypescript()) print(L"!");
                                                                      print(semicolon());
                                                                    }
                                                                  }
                                                                  else
                                                                  {
                                                            #line 7254 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4296 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7259 "PrintCLike.cpp"
  append(L"top -= symbols << 1;\n");
  append(L"    state = ");
                                                            #line 4298 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7264 "PrintCLike.cpp"
  append(L"iStack");
                                                            #line 4299 "PrintCLike.cpp.template"
                                                                    print(leftbracket());
                                                                    print(thiz());
                                                            #line 7269 "PrintCLike.cpp"
  append(L"top + 1");
                                                            #line 4301 "PrintCLike.cpp.template"
                                                                    print(rightbracket());
                                                                    print(semicolon());
                                                                  }
                                                                  increaseIndent();
                                                                  print(rightBrace());
                                                                  decreaseIndent();
                                                                  if (useGlr && tree)
                                                                  {
                                                            #line 7280 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if ");
                                                            #line 4310 "PrintCLike.cpp.template"
                                                                    print(ifLeftParen());
                                                            #line 7285 "PrintCLike.cpp"
  append(L"nonterminalId == ");
                                                            #line 4311 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7289 "PrintCLike.cpp"
  append(L"target ");
                                                            #line 4312 "PrintCLike.cpp.template"
                                                                    if (isPython())
                                                                    {
                                                            #line 7294 "PrintCLike.cpp"
  append(L"and");
                                                            #line 4314 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 7300 "PrintCLike.cpp"
  append(L"&&");
                                                            #line 4317 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 7304 "PrintCLike.cpp"
  append(L" ");
                                                            #line 4318 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7308 "PrintCLike.cpp"
  append(L"stack");
                                                            #line 4319 "PrintCLike.cpp.template"
                                                                    print(arrow());
                                                            #line 7312 "PrintCLike.cpp"
  append(L"link == ");
                                                            #line 4320 "PrintCLike.cpp.template"
                                                                    print(nullPtr());
                                                                    print(ifRightParen());
                                                                    printIndented(1, leftBrace());
                                                            #line 7318 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4324 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7323 "PrintCLike.cpp"
  append(L"bs = ");
                                                            #line 4325 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7327 "PrintCLike.cpp"
  append(L"bw");
                                                            #line 4326 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 7331 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4328 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7336 "PrintCLike.cpp"
  append(L"bw = ");
                                                            #line 4329 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7340 "PrintCLike.cpp"
  append(L"b1");
                                                            #line 4330 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                    increaseIndent();
                                                                    print(rightBrace());
                                                                    decreaseIndent();
                                                                  }
                                                                }
                                                            #line 7349 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4337 "PrintCLike.cpp.template"
                                                                if (useGlr) print(thiz());
                                                            #line 7354 "PrintCLike.cpp"
  append(L"action = ");
                                                            #line 4338 "PrintCLike.cpp.template"
                                                                print(staticPrefix());
                                                                print(isGo() ? L"reduceAction" : L"goTo");
                                                            #line 7359 "PrintCLike.cpp"
  append(L"(nonterminalId, ");
                                                            #line 4340 "PrintCLike.cpp.template"
                                                                if (useGlr) print(thiz());
                                                            #line 7363 "PrintCLike.cpp"
  append(L"state)");
                                                            #line 4341 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                print(rightBrace());
                                                                decreaseIndent();
                                                                print(rightBrace());
                                                                decreaseIndent();
                                                                if (useGlr)
                                                                {
                                                                  if (isScala())
                                                                  {
                                                            #line 7375 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ERROR");
                                                            #line 4351 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isCpp())
                                                                  {
                                                            #line 7382 "PrintCLike.cpp"
  append(L"\n");
  append(L"  return PARSING;");
                                                            #line 4355 "PrintCLike.cpp.template"
                                                                  }
                                                                }
                                                                print(rightBrace());
                                                                if (isJavascript() && useGlr)
                                                                {
                                                            #line 7391 "PrintCLike.cpp"
  append(L";");
                                                            #line 4360 "PrintCLike.cpp.template"
                                                                }
                                                            #line 7395 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4362 "PrintCLike.cpp.template"
                                                                if ((tree || hasCustomCode) && useGlr)
                                                                {
                                                                  openMethod(boolType(), L"", L"isUnambiguous", L"", false, L"ParsingThread");
                                                                  print(leftBrace());
                                                            #line 7402 "PrintCLike.cpp"
  append(L"\n");
  append(L"  return ");
                                                            #line 4367 "PrintCLike.cpp.template"
                                                                  if (isPython())
                                                                  {
                                                            #line 7408 "PrintCLike.cpp"
  append(L"len(self.threads) == 0");
                                                            #line 4369 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                                    print(thiz());
                                                            #line 7415 "PrintCLike.cpp"
  append(L"threads");
                                                            #line 4373 "PrintCLike.cpp.template"
                                                                    print(arrow());
                                                                    if (isCpp())
                                                                    {
                                                            #line 7421 "PrintCLike.cpp"
  append(L"empty();");
                                                            #line 4376 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 7427 "PrintCLike.cpp"
  append(L"isEmpty");
                                                            #line 4379 "PrintCLike.cpp.template"
                                                                      if (! isScala()) print(L"()");
                                                                      print(semicolon());
                                                                    }
                                                                  }
                                                                  print(rightBrace());
                                                            #line 7435 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4385 "PrintCLike.cpp.template"
                                                                }
                                                                if (hasCustomCode)
                                                                {
                                                                  if (useGlr)
                                                                  {
                                                                    if (isJavascript())
                                                                    {
                                                            #line 7445 "PrintCLike.cpp"
  append(L"\n");
  append(L"this.executeDeferredCode = function()\n");
                                                            #line 4394 "PrintCLike.cpp.template"
                                                                    }
                                                                    else if (isTypescript())
                                                                    {
                                                            #line 7452 "PrintCLike.cpp"
  append(L"\n");
  append(L"executeDeferredCode()\n");
                                                            #line 4399 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                                      openMethod(voidType(), L"", L"executeDeferredCode", L"", false, L"ParsingThread");
                                                                    }
                                                                    print(leftBrace());
                                                                    increaseIndent();
                                                            #line 7463 "PrintCLike.cpp"
  append(L"\n");
  append(L"if ");
                                                            #line 4407 "PrintCLike.cpp.template"
                                                                    print(ifLeftParen());
                                                                    print(thiz());
                                                            #line 7469 "PrintCLike.cpp"
  append(L"deferredCode != ");
                                                            #line 4409 "PrintCLike.cpp.template"
                                                                    print(nullPtr());
                                                                    print(ifRightParen());
                                                                    print(leftBrace());
                                                                    increaseIndent();
                                                            #line 7476 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4414 "PrintCLike.cpp.template"
                                                                    if (isJavascript() || isHaxe() || isScala() || isTypescript())
                                                                    {
                                                            #line 7481 "PrintCLike.cpp"
  append(L"var ");
                                                            #line 4416 "PrintCLike.cpp.template"
                                                                    }
                                                                    else if (! isGo() && ! isPython())
                                                                    {
                                                            #line 7487 "PrintCLike.cpp"
  append(L"DeferredCode ");
                                                            #line 4419 "PrintCLike.cpp.template"
                                                                    }
                                                                    if (isCpp()) print(L"*");
                                                            #line 7492 "PrintCLike.cpp"
  append(L"predecessor");
                                                            #line 4421 "PrintCLike.cpp.template"
                                                                    print(assign());
                                                                    print(thiz());
                                                            #line 7497 "PrintCLike.cpp"
  append(L"deferredCode");
                                                            #line 4423 "PrintCLike.cpp.template"
                                                                    print(arrow());
                                                            #line 7501 "PrintCLike.cpp"
  append(L"link");
                                                            #line 4424 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 7505 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4426 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7509 "PrintCLike.cpp"
  append(L"deferredCode");
                                                            #line 4427 "PrintCLike.cpp.template"
                                                                    print(arrow());
                                                            #line 7513 "PrintCLike.cpp"
  append(L"link = ");
                                                            #line 4428 "PrintCLike.cpp.template"
                                                                    print(nullPtr());
                                                                    print(semicolon());
                                                                    if (isGo())
                                                                    {
                                                            #line 7520 "PrintCLike.cpp"
  append(L"\n");
  append(L"for ");
                                                            #line 4433 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 7527 "PrintCLike.cpp"
  append(L"\n");
  append(L"while ");
                                                            #line 4437 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(ifLeftParen());
                                                            #line 7533 "PrintCLike.cpp"
  append(L"predecessor != ");
                                                            #line 4439 "PrintCLike.cpp.template"
                                                                    print(nullPtr());
                                                                    print(ifRightParen());
                                                                    print(leftBrace());
                                                            #line 7539 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4443 "PrintCLike.cpp.template"
                                                                    if (isJavascript() || isHaxe() || isScala() || isTypescript())
                                                                    {
                                                            #line 7545 "PrintCLike.cpp"
  append(L"var ");
                                                            #line 4445 "PrintCLike.cpp.template"
                                                                    }
                                                                    else if (! isGo() && ! isPython())
                                                                    {
                                                            #line 7551 "PrintCLike.cpp"
  append(L"DeferredCode ");
                                                            #line 4448 "PrintCLike.cpp.template"
                                                                    }
                                                                    if (isCpp()) print(L"*");
                                                            #line 7556 "PrintCLike.cpp"
  append(L"nextCode");
                                                            #line 4450 "PrintCLike.cpp.template"
                                                                    print(assign());
                                                            #line 7560 "PrintCLike.cpp"
  append(L"predecessor");
                                                            #line 4451 "PrintCLike.cpp.template"
                                                                    print(arrow());
                                                            #line 7564 "PrintCLike.cpp"
  append(L"link");
                                                            #line 4452 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 7568 "PrintCLike.cpp"
  append(L"\n");
  append(L"  predecessor");
                                                            #line 4454 "PrintCLike.cpp.template"
                                                                    print(arrow());
                                                            #line 7573 "PrintCLike.cpp"
  append(L"link = ");
                                                            #line 4455 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7577 "PrintCLike.cpp"
  append(L"deferredCode");
                                                            #line 4456 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 7581 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4458 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7586 "PrintCLike.cpp"
  append(L"deferredCode = predecessor");
                                                            #line 4459 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 7590 "PrintCLike.cpp"
  append(L"\n");
  append(L"  predecessor = nextCode");
                                                            #line 4461 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                    print(rightBrace());
                                                            #line 7596 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4464 "PrintCLike.cpp.template"
                                                                    print(intVar());
                                                            #line 7600 "PrintCLike.cpp"
  append(L"b0t");
                                                            #line 4465 "PrintCLike.cpp.template"
                                                                    print(assign());
                                                                    print(thiz());
                                                            #line 7605 "PrintCLike.cpp"
  append(L"b0");
                                                            #line 4467 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 7609 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4469 "PrintCLike.cpp.template"
                                                                    print(intVar());
                                                            #line 7613 "PrintCLike.cpp"
  append(L"e0t");
                                                            #line 4470 "PrintCLike.cpp.template"
                                                                    print(assign());
                                                                    print(thiz());
                                                            #line 7618 "PrintCLike.cpp"
  append(L"e0");
                                                            #line 4472 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                    if (isGo())
                                                                    {
                                                            #line 7624 "PrintCLike.cpp"
  append(L"\n");
  append(L"for ");
                                                            #line 4476 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 7631 "PrintCLike.cpp"
  append(L"\n");
  append(L"while ");
                                                            #line 4480 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(ifLeftParen());
                                                                    print(thiz());
                                                            #line 7638 "PrintCLike.cpp"
  append(L"deferredCode != ");
                                                            #line 4483 "PrintCLike.cpp.template"
                                                                    print(nullPtr());
                                                                    print(ifRightParen());
                                                                    print(leftBrace());
                                                            #line 7644 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4487 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7649 "PrintCLike.cpp"
  append(L"b0 = ");
                                                            #line 4488 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7653 "PrintCLike.cpp"
  append(L"deferredCode");
                                                            #line 4489 "PrintCLike.cpp.template"
                                                                    print(arrow());
                                                            #line 7657 "PrintCLike.cpp"
  append(L"b0");
                                                            #line 4490 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 7661 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4492 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7666 "PrintCLike.cpp"
  append(L"e0 = ");
                                                            #line 4493 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7670 "PrintCLike.cpp"
  append(L"deferredCode");
                                                            #line 4494 "PrintCLike.cpp.template"
                                                                    print(arrow());
                                                            #line 7674 "PrintCLike.cpp"
  append(L"e0");
                                                            #line 4495 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 7678 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4497 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                                    print(isGo() ? L"E" : L"e");
                                                            #line 7684 "PrintCLike.cpp"
  append(L"xecute(");
                                                            #line 4499 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7688 "PrintCLike.cpp"
  append(L"deferredCode");
                                                            #line 4500 "PrintCLike.cpp.template"
                                                                    print(arrow());
                                                            #line 7692 "PrintCLike.cpp"
  append(L"codeId)");
                                                            #line 4501 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                    if (isCpp())
                                                                    {
                                                            #line 7698 "PrintCLike.cpp"
  append(L"\n");
  append(L"  DeferredCode *next = deferredCode->link;\n");
  append(L"  delete deferredCode;\n");
  append(L"  deferredCode = next;");
                                                            #line 4507 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 7707 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4511 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 7712 "PrintCLike.cpp"
  append(L"deferredCode = ");
                                                            #line 4512 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 7716 "PrintCLike.cpp"
  append(L"deferredCode");
                                                            #line 4513 "PrintCLike.cpp.template"
                                                                      print(arrow());
                                                            #line 7720 "PrintCLike.cpp"
  append(L"link");
                                                            #line 4514 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                                    }
                                                                    print(rightBrace());
                                                            #line 7726 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4518 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7730 "PrintCLike.cpp"
  append(L"b0 = b0t");
                                                            #line 4519 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 7734 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4521 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7738 "PrintCLike.cpp"
  append(L"e0 = e0t");
                                                            #line 4522 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                    decreaseIndent();
                                                                    print(rightBrace());
                                                                    decreaseIndent();
                                                                    print(rightBrace());
                                                            #line 7746 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4528 "PrintCLike.cpp.template"
                                                                  }
                                                                  openMethod(voidType(), L"", L"execute", L"int reduce", false, useGlr ? L"ParsingThread" : className.c_str());
                                                                  print(leftBrace());
                                                                  increaseIndent();
                                                                  if (! isPython())
                                                                  {
                                                            #line 7755 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4535 "PrintCLike.cpp.template"
                                                                    if (! isScala())
                                                                    {
                                                            #line 7760 "PrintCLike.cpp"
  append(L"switch ");
                                                            #line 4537 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(ifLeftParen());
                                                            #line 7765 "PrintCLike.cpp"
  append(L"reduce");
                                                            #line 4539 "PrintCLike.cpp.template"
                                                                    print(ifRightParen());
                                                                    if (isScala())
                                                                    {
                                                            #line 7771 "PrintCLike.cpp"
  append(L" match");
                                                            #line 4542 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(leftBrace());
                                                                  }
                                                                  int lastContentId = grammar->distinctCodeAnnotations.size() - 1;
                                                                  for (int contentId = 0; contentId <= lastContentId; ++contentId)
                                                                  {
                                                                    ProcessingInstruction *p = grammar->distinctCodeAnnotations[contentId];
                                                                    if (! isPython())
                                                                    {
                                                            #line 7783 "PrintCLike.cpp"
  append(L"\n");
  append(L"case ");
                                                            #line 4552 "PrintCLike.cpp.template"
                                                                    }
                                                                    else if (contentId == 0)
                                                                    {
                                                            #line 7790 "PrintCLike.cpp"
  append(L"\n");
  append(L"if reduce == ");
                                                            #line 4556 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 7797 "PrintCLike.cpp"
  append(L"\n");
  append(L"elif reduce == ");
                                                            #line 4560 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(format.toString<wchar_t>(contentId));
                                                                    print(caseIntroducer());
                                                                    increaseIndent();
                                                                    print(leftBrace());
                                                                    visitProcessingInstruction(p);
                                                                    print(rightBrace());
                                                                    if (! isScala() && ! isHaxe() && ! isGo() && ! isPython())
                                                                    {
                                                            #line 7810 "PrintCLike.cpp"
  append(L"\n");
  append(L"break");
                                                            #line 4570 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                                    }
                                                                    decreaseIndent();
                                                                  }
                                                                  if (isScala())
                                                                  {
                                                            #line 7820 "PrintCLike.cpp"
  append(L"\n");
  append(L"case _");
                                                            #line 4577 "PrintCLike.cpp.template"
                                                                    print(caseIntroducer());
                                                                  }
                                                                  else if (! isPython())
                                                                  {
                                                            #line 7828 "PrintCLike.cpp"
  append(L"\n");
  append(L"default");
                                                            #line 4582 "PrintCLike.cpp.template"
                                                                    print(caseIntroducer());
                                                                  }
                                                                  if (! isScala() && ! isHaxe() && ! isGo() && ! isPython())
                                                                  {
                                                            #line 7836 "PrintCLike.cpp"
  append(L"\n");
  append(L"  break");
                                                            #line 4587 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                  }
                                                                  print(rightBrace());
                                                                  decreaseIndent();
                                                                  print(rightBrace());
                                                            #line 7845 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4593 "PrintCLike.cpp.template"
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
                                                            #line 7871 "PrintCLike.cpp"
  append(L"\n");
  append(L"if ");
                                                            #line 4617 "PrintCLike.cpp.template"
                                                                print(ifLeftParen());
                                                                print(thiz());
                                                            #line 7877 "PrintCLike.cpp"
  append(L"l1 == t");
                                                            #line 4619 "PrintCLike.cpp.template"
                                                                print(ifRightParen());
                                                                print(leftBrace());
                                                                increaseIndent();
                                                                if (tree && i == 0 && ! isLrParser)
                                                                {
                                                                  if (anyWhitespace && ! isLrParser)
                                                                  {
                                                            #line 7887 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4627 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7891 "PrintCLike.cpp"
  append(L"whitespace");
                                                            #line 4628 "PrintCLike.cpp.template"
                                                                    print(isScala() ? L"" : L"()");
                                                                    print(semicolon());
                                                                  }
                                                            #line 7897 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4632 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 7901 "PrintCLike.cpp"
  append(L"eventHandler");
                                                            #line 4633 "PrintCLike.cpp.template"
                                                                  if (shiftAmbiguity && isTypescript()) print(L"!");
                                                                  print(arrow());
                                                                  if (isGo())
                                                                  {
                                                            #line 7908 "PrintCLike.cpp"
  append(L"T");
                                                            #line 4637 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 7914 "PrintCLike.cpp"
  append(L"t");
                                                            #line 4640 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 7918 "PrintCLike.cpp"
  append(L"erminal(");
                                                            #line 4641 "PrintCLike.cpp.template"
                                                                  if (isJava() || isCSharp())
                                                                  {
                                                                    print(staticPrefix());
                                                            #line 7924 "PrintCLike.cpp"
  append(L"TOKEN[");
                                                            #line 4644 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7928 "PrintCLike.cpp"
  append(L"l1]");
                                                            #line 4645 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isTypescript())
                                                                  {
                                                                    print(staticPrefix());
                                                            #line 7935 "PrintCLike.cpp"
  append(L"TOKEN[");
                                                            #line 4649 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7939 "PrintCLike.cpp"
  append(L"l1]");
                                                            #line 4650 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isJavascript() || isHaxe())
                                                                  {
                                                                    print(staticPrefix());
                                                            #line 7946 "PrintCLike.cpp"
  append(L"TOKEN[");
                                                            #line 4654 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7950 "PrintCLike.cpp"
  append(L"l1]");
                                                            #line 4655 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isScala())
                                                                  {
                                                                    print(staticPrefix());
                                                            #line 7957 "PrintCLike.cpp"
  append(L"TOKEN(l1)");
                                                            #line 4659 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isGo())
                                                                  {
                                                            #line 7963 "PrintCLike.cpp"
  append(L"token[this.l1]");
                                                            #line 4662 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                                    print(staticPrefix());
                                                            #line 7970 "PrintCLike.cpp"
  append(L"TOKEN[");
                                                            #line 4666 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7974 "PrintCLike.cpp"
  append(L"l1]");
                                                            #line 4667 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 7978 "PrintCLike.cpp"
  append(L", ");
                                                            #line 4668 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 7982 "PrintCLike.cpp"
  append(L"b1, ");
                                                            #line 4669 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 7986 "PrintCLike.cpp"
  append(L"e1)");
                                                            #line 4670 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                            #line 7991 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4673 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 7995 "PrintCLike.cpp"
  append(L"b0 = ");
                                                            #line 4674 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 7999 "PrintCLike.cpp"
  append(L"b1; ");
                                                            #line 4675 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 8003 "PrintCLike.cpp"
  append(L"e0 = ");
                                                            #line 4676 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 8007 "PrintCLike.cpp"
  append(L"e1;");
                                                            #line 4677 "PrintCLike.cpp.template"
                                                                for (size_t k = 1; k < grammar->k; ++k)
                                                                {
                                                            #line 8012 "PrintCLike.cpp"
  append(L" ");
                                                            #line 4679 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8016 "PrintCLike.cpp"
  append(L"l");
                                                            #line 4680 "PrintCLike.cpp.template"
                                                                  print(format.toString<wchar_t>(k));
                                                            #line 8020 "PrintCLike.cpp"
  append(L" = ");
                                                            #line 4681 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8024 "PrintCLike.cpp"
  append(L"l");
                                                            #line 4682 "PrintCLike.cpp.template"
                                                                  print(format.toString<wchar_t>(k + 1));
                                                                  print(isPython() ? L"\n" : L"; ");
                                                            #line 8029 "PrintCLike.cpp"
  append(L"if ");
                                                            #line 4684 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                                  print(thiz());
                                                            #line 8034 "PrintCLike.cpp"
  append(L"l");
                                                            #line 4686 "PrintCLike.cpp.template"
                                                                  print(format.toString<wchar_t>(k));
                                                            #line 8038 "PrintCLike.cpp"
  append(L" != 0");
                                                            #line 4687 "PrintCLike.cpp.template"
                                                                  print(ifRightParen());
                                                                  if (isPython())
                                                                  {
                                                                    increaseIndent();
                                                                  }
                                                                  else
                                                                  {
                                                            #line 8048 "PrintCLike.cpp"
  append(L" {");
                                                            #line 4694 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 8052 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4696 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8056 "PrintCLike.cpp"
  append(L"b");
                                                            #line 4697 "PrintCLike.cpp.template"
                                                                  print(format.toString<wchar_t>(k));
                                                            #line 8060 "PrintCLike.cpp"
  append(L" = ");
                                                            #line 4698 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8064 "PrintCLike.cpp"
  append(L"b");
                                                            #line 4699 "PrintCLike.cpp.template"
                                                                  print(format.toString<wchar_t>(k + 1));
                                                            #line 8068 "PrintCLike.cpp"
  append(L"; ");
                                                            #line 4700 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8072 "PrintCLike.cpp"
  append(L"e");
                                                            #line 4701 "PrintCLike.cpp.template"
                                                                  print(format.toString<wchar_t>(k));
                                                            #line 8076 "PrintCLike.cpp"
  append(L" = ");
                                                            #line 4702 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8080 "PrintCLike.cpp"
  append(L"e");
                                                            #line 4703 "PrintCLike.cpp.template"
                                                                  print(format.toString<wchar_t>(k + 1));
                                                            #line 8084 "PrintCLike.cpp"
  append(L";");
                                                            #line 4704 "PrintCLike.cpp.template"
                                                                }
                                                            #line 8088 "PrintCLike.cpp"
  append(L" ");
                                                            #line 4705 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 8092 "PrintCLike.cpp"
  append(L"l");
                                                            #line 4706 "PrintCLike.cpp.template"
                                                                print(format.toString<wchar_t>(grammar->k));
                                                            #line 8096 "PrintCLike.cpp"
  append(L" = 0");
                                                            #line 4707 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                if (grammar->k > 1)
                                                                {
                                                            #line 8102 "PrintCLike.cpp"
  append(L" ");
                                                            #line 4710 "PrintCLike.cpp.template"
                                                                  for (size_t k = 1; k < grammar->k; ++k)
                                                                  {
                                                                    if (! isPython())
                                                                    {
                                                            #line 8109 "PrintCLike.cpp"
  append(L"}");
                                                            #line 4714 "PrintCLike.cpp.template"
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
                                                            #line 8124 "PrintCLike.cpp"
  append(L"\n");
  append(L"  fprintf(stderr, \"  <parse terminal=\\\"%s\\\"%s%s%s/>\\n\", ");
                                                            #line 4727 "PrintCLike.cpp.template"
                                                                    if (stringIntroducer()[0])
                                                                    {
                                                            #line 8130 "PrintCLike.cpp"
  append(L"Utf8Encoder::encode(");
                                                            #line 4730 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 8134 "PrintCLike.cpp"
  append(L"xmlEscape(TOKEN[t], 0).c_str()");
                                                            #line 4732 "PrintCLike.cpp.template"
                                                                    if (stringIntroducer()[0])
                                                                    {
                                                            #line 8139 "PrintCLike.cpp"
  append(L").c_str()");
                                                            #line 4734 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 8143 "PrintCLike.cpp"
  append(L", (l1 == 0 ? \"\" : \" input=\\\"\"),  (l1 == 0 ? \"\" : ");
                                                            #line 4736 "PrintCLike.cpp.template"
                                                                    if (stringIntroducer()[0])
                                                                    {
                                                            #line 8148 "PrintCLike.cpp"
  append(L"Utf8Encoder::encode(");
                                                            #line 4739 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 8152 "PrintCLike.cpp"
  append(L"xmlEscape(lookaheadString().c_str(), 0).c_str()");
                                                            #line 4741 "PrintCLike.cpp.template"
                                                                    if (stringIntroducer()[0])
                                                                    {
                                                            #line 8157 "PrintCLike.cpp"
  append(L").c_str()");
                                                            #line 4743 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 8161 "PrintCLike.cpp"
  append(L"), (l1 == 0 ? \"\" : \"\\\"\"));");
                                                            #line 4745 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                                    if (isGo())
                                                                    {
                                                            #line 8169 "PrintCLike.cpp"
  append(L"\n");
  append(L"  var inputAttr string\n");
  append(L"  if (this.l1 == 0) {\n");
  append(L"    inputAttr = \"\"\n");
  append(L"  } else {\n");
  append(L"    inputAttr = \" input=\\\"\" + xmlEscape(this.lookaheadString()) + \"\\\"\"\n");
  append(L"  }");
                                                            #line 4756 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 8179 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4758 "PrintCLike.cpp.template"
                                                                    if (isHaxe())
                                                                    {
                                                            #line 8185 "PrintCLike.cpp"
  append(L"trace(");
                                                            #line 4760 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                                      print(writeTrace());
                                                                    }
                                                            #line 8193 "PrintCLike.cpp"
  append(L"\"  <parse terminal=\\\"\" + ");
                                                            #line 4765 "PrintCLike.cpp.template"
                                                                    print(staticPrefix());
                                                            #line 8197 "PrintCLike.cpp"
  append(L"xmlEscape(");
                                                            #line 4766 "PrintCLike.cpp.template"
                                                                    print(staticPrefix());
                                                                    print(isGo() ? L"token" : L"TOKEN");
                                                                    print(leftbracket());
                                                            #line 8203 "PrintCLike.cpp"
  append(L"t");
                                                            #line 4769 "PrintCLike.cpp.template"
                                                                    print(rightbracket());
                                                            #line 8207 "PrintCLike.cpp"
  append(L") + \"\\\"\" + ");
                                                            #line 4770 "PrintCLike.cpp.template"
                                                                    if (isGo())
                                                                    {
                                                            #line 8212 "PrintCLike.cpp"
  append(L"inputAttr");
                                                            #line 4772 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 8218 "PrintCLike.cpp"
  append(L"(");
                                                            #line 4775 "PrintCLike.cpp.template"
                                                                      if (isScala())
                                                                      {
                                                            #line 8223 "PrintCLike.cpp"
  append(L"if (l1 == 0) \"\" else");
                                                            #line 4777 "PrintCLike.cpp.template"
                                                                      }
                                                                      else if (isPython())
                                                                      {
                                                            #line 8229 "PrintCLike.cpp"
  append(L"\"\" if self.l1 == 0 else");
                                                            #line 4780 "PrintCLike.cpp.template"
                                                                      }
                                                                      else
                                                                      {
                                                                        print(thiz());
                                                            #line 8236 "PrintCLike.cpp"
  append(L"l1 == 0 ? \"\" :");
                                                            #line 4784 "PrintCLike.cpp.template"
                                                                      }
                                                            #line 8240 "PrintCLike.cpp"
  append(L" \" input=\\\"\" + ");
                                                            #line 4785 "PrintCLike.cpp.template"
                                                                      print(staticPrefix());
                                                            #line 8244 "PrintCLike.cpp"
  append(L"xmlEscape(");
                                                            #line 4786 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 8248 "PrintCLike.cpp"
  append(L"lookaheadString");
                                                            #line 4787 "PrintCLike.cpp.template"
                                                                      if (! isScala()) print(L"()");
                                                            #line 8252 "PrintCLike.cpp"
  append(L") + \"\\\"\")");
                                                            #line 4788 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 8256 "PrintCLike.cpp"
  append(L" + \"/>");
                                                            #line 4789 "PrintCLike.cpp.template"
                                                                    if (isHaxe())
                                                                    {
                                                            #line 8261 "PrintCLike.cpp"
  append(L"\")");
                                                            #line 4791 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 8267 "PrintCLike.cpp"
  append(L"\\n\"");
                                                            #line 4794 "PrintCLike.cpp.template"
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
                                                            #line 8281 "PrintCLike.cpp"
  append(L"el");
                                                            #line 4805 "PrintCLike.cpp.template"
                                                                    if (! isPython())
                                                                    {
                                                            #line 8286 "PrintCLike.cpp"
  append(L"se ");
                                                            #line 4807 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 8290 "PrintCLike.cpp"
  append(L"if ");
                                                            #line 4808 "PrintCLike.cpp.template"
                                                                    print(ifLeftParen());
                                                                    print(thiz());
                                                                    print(token());
                                                            #line 8296 "PrintCLike.cpp"
  append(L" < 0");
                                                            #line 4811 "PrintCLike.cpp.template"
                                                                    print(ifRightParen());
                                                                    print(leftBrace());
                                                            #line 8301 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4814 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8306 "PrintCLike.cpp"
  append(L"error(");
                                                            #line 4815 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8310 "PrintCLike.cpp"
  append(L"b1, ");
                                                            #line 4816 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8314 "PrintCLike.cpp"
  append(L"e1, -");
                                                            #line 4817 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8318 "PrintCLike.cpp"
  append(L"l1, 0, 0)");
                                                            #line 4818 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                    if (i == 0)
                                                                    {
                                                            #line 8324 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4822 "PrintCLike.cpp.template"
                                                                      print(beginThrowStmt());
                                                                      print(thiz());
                                                            #line 8330 "PrintCLike.cpp"
  append(L"bx, ");
                                                            #line 4824 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 8334 "PrintCLike.cpp"
  append(L"ex, ");
                                                            #line 4825 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 8338 "PrintCLike.cpp"
  append(L"sx, ");
                                                            #line 4826 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 8342 "PrintCLike.cpp"
  append(L"lx, ");
                                                            #line 4827 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 8346 "PrintCLike.cpp"
  append(L"tx");
                                                            #line 4828 "PrintCLike.cpp.template"
                                                                      print(endThrowStmt());
                                                                      print(semicolon());
                                                                    }
                                                                    print(rightBrace());
                                                                  }
                                                                  print(isGo() ? L" " : L"\n");
                                                            #line 8355 "PrintCLike.cpp"
  append(L"else");
                                                            #line 4834 "PrintCLike.cpp.template"
                                                                  if (isPython()) print(L":");
                                                                  print(leftBrace());
                                                            #line 8360 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4837 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8365 "PrintCLike.cpp"
  append(L"error(");
                                                            #line 4838 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8369 "PrintCLike.cpp"
  append(L"b1, ");
                                                            #line 4839 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8373 "PrintCLike.cpp"
  append(L"e1, 0, ");
                                                            #line 4840 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8377 "PrintCLike.cpp"
  append(L"l1, t)");
                                                            #line 4841 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                  if (i == 0 && grammar->noThrow)
                                                                  {
                                                            #line 8383 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4845 "PrintCLike.cpp.template"
                                                                    print(beginThrowStmt());
                                                                    print(thiz());
                                                            #line 8389 "PrintCLike.cpp"
  append(L"bx, ");
                                                            #line 4847 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8393 "PrintCLike.cpp"
  append(L"ex, ");
                                                            #line 4848 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8397 "PrintCLike.cpp"
  append(L"sx, ");
                                                            #line 4849 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8401 "PrintCLike.cpp"
  append(L"lx, ");
                                                            #line 4850 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8405 "PrintCLike.cpp"
  append(L"tx");
                                                            #line 4851 "PrintCLike.cpp.template"
                                                                    print(endThrowStmt());
                                                                    print(semicolon());
                                                                  }
                                                                  print(rightBrace());
                                                                }
                                                                else
                                                                {
                                                                  print(isGo() ? L" " : L"\n");
                                                            #line 8416 "PrintCLike.cpp"
  append(L"else");
                                                            #line 4859 "PrintCLike.cpp.template"
                                                                  if (isPython()) print(L":");
                                                                  print(leftBrace());
                                                            #line 8421 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4862 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8426 "PrintCLike.cpp"
  append(L"error(");
                                                            #line 4863 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8430 "PrintCLike.cpp"
  append(L"b1, ");
                                                            #line 4864 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8434 "PrintCLike.cpp"
  append(L"e1, 0, ");
                                                            #line 4865 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8438 "PrintCLike.cpp"
  append(L"l1, t)");
                                                            #line 4866 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                  print(rightBrace());
                                                                }
                                                                decreaseIndent();
                                                                print(rightBrace());
                                                            #line 8446 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4872 "PrintCLike.cpp.template"
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
                                                            #line 8465 "PrintCLike.cpp"
  append(L"\n");
  append(L"  var thread = new ParsingThread().copy(thisThread, 0);\n");
  append(L"  thread.setL1(code);\n");
  append(L"  thread.setB1(begin);\n");
  append(L"  thread.setE1(end);");
                                                            #line 4892 "PrintCLike.cpp.template"
                                                                    }
                                                                    else if (isGo())
                                                                    {
                                                            #line 8475 "PrintCLike.cpp"
  append(L"\n");
  append(L"  thread := new(ParsingThread).copy(this, 0)\n");
  append(L"  thread.l1 = code\n");
  append(L"  thread.b1 = this.begin\n");
  append(L"  thread.e1 = this.end");
                                                            #line 4899 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 8485 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4903 "PrintCLike.cpp.template"
                                                                      if (isHaxe() || isScala() || isTypescript())
                                                                      {
                                                            #line 8491 "PrintCLike.cpp"
  append(L"var ");
                                                            #line 4905 "PrintCLike.cpp.template"
                                                                      }
                                                                      else if (! isPython())
                                                                      {
                                                            #line 8497 "PrintCLike.cpp"
  append(L"ParsingThread ");
                                                            #line 4908 "PrintCLike.cpp.template"
                                                                      }
                                                                      if (isCpp()) print(L"*");
                                                            #line 8502 "PrintCLike.cpp"
  append(L"thread = ");
                                                            #line 4910 "PrintCLike.cpp.template"
                                                                      if (isCpp()) print(L"(");
                                                                      if (! isPython())
                                                                      {
                                                            #line 8508 "PrintCLike.cpp"
  append(L"new ");
                                                            #line 4913 "PrintCLike.cpp.template"
                                                                      }
                                                                      if (isScala() || isPython())
                                                                      {
                                                                        print(className.c_str());
                                                            #line 8515 "PrintCLike.cpp"
  append(L".");
                                                            #line 4917 "PrintCLike.cpp.template"
                                                                      }
                                                            #line 8519 "PrintCLike.cpp"
  append(L"ParsingThread()");
                                                            #line 4918 "PrintCLike.cpp.template"
                                                                      if (isCpp()) print(L")");
                                                                      print(arrow());
                                                            #line 8524 "PrintCLike.cpp"
  append(L"copy(");
                                                            #line 4920 "PrintCLike.cpp.template"
                                                                      if (isPython())
                                                                      {
                                                            #line 8529 "PrintCLike.cpp"
  append(L"self");
                                                            #line 4922 "PrintCLike.cpp.template"
                                                                      }
                                                                      else
                                                                      {
                                                            #line 8535 "PrintCLike.cpp"
  append(L"this");
                                                            #line 4925 "PrintCLike.cpp.template"
                                                                      }
                                                            #line 8539 "PrintCLike.cpp"
  append(L", 0)");
                                                            #line 4926 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                                      if (isCpp())
                                                                      {
                                                            #line 8545 "PrintCLike.cpp"
  append(L"\n");
  append(L"  thread->stack->unshare();\n");
  append(L"  thread->stack = 0;");
                                                            #line 4931 "PrintCLike.cpp.template"
                                                                      }
                                                            #line 8551 "PrintCLike.cpp"
  append(L"\n");
  append(L"  thread");
                                                            #line 4933 "PrintCLike.cpp.template"
                                                                      print(arrow());
                                                            #line 8556 "PrintCLike.cpp"
  append(L"l1 = code");
                                                            #line 4934 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                            #line 8560 "PrintCLike.cpp"
  append(L"\n");
  append(L"  thread");
                                                            #line 4936 "PrintCLike.cpp.template"
                                                                      print(arrow());
                                                            #line 8565 "PrintCLike.cpp"
  append(L"b1 = ");
                                                            #line 4937 "PrintCLike.cpp.template"
                                                                      if (useGlr) print(thiz());
                                                            #line 8569 "PrintCLike.cpp"
  append(L"begin");
                                                            #line 4938 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                            #line 8573 "PrintCLike.cpp"
  append(L"\n");
  append(L"  thread");
                                                            #line 4940 "PrintCLike.cpp.template"
                                                                      print(arrow());
                                                            #line 8578 "PrintCLike.cpp"
  append(L"e1 = ");
                                                            #line 4941 "PrintCLike.cpp.template"
                                                                      if (useGlr) print(thiz());
                                                            #line 8582 "PrintCLike.cpp"
  append(L"end");
                                                            #line 4942 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                                    }
                                                                  }
                                                                  else
                                                                  {
                                                            #line 8590 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4948 "PrintCLike.cpp.template"
                                                                    print(intVal());
                                                            #line 8595 "PrintCLike.cpp"
  append(L"b0W");
                                                            #line 4949 "PrintCLike.cpp.template"
                                                                    print(assign());
                                                                    print(thiz());
                                                            #line 8600 "PrintCLike.cpp"
  append(L"b0; ");
                                                            #line 4951 "PrintCLike.cpp.template"
                                                                    print(intVal());
                                                            #line 8604 "PrintCLike.cpp"
  append(L"e0W");
                                                            #line 4952 "PrintCLike.cpp.template"
                                                                    print(assign());
                                                                    print(thiz());
                                                            #line 8609 "PrintCLike.cpp"
  append(L"e0");
                                                            #line 4955 "PrintCLike.cpp.template"
                                                                    for (size_t k = 1; k < grammar->k; ++k)
                                                                    {
                                                            #line 8614 "PrintCLike.cpp"
  append(L"; ");
                                                            #line 4957 "PrintCLike.cpp.template"
                                                                      print(intVal());
                                                            #line 8618 "PrintCLike.cpp"
  append(L"l");
                                                            #line 4958 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(k));
                                                            #line 8622 "PrintCLike.cpp"
  append(L"W");
                                                            #line 4959 "PrintCLike.cpp.template"
                                                                      print(assign());
                                                                      print(thiz());
                                                            #line 8627 "PrintCLike.cpp"
  append(L"l");
                                                            #line 4961 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(k));
                                                                      print(semicolon());
                                                            #line 8632 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4964 "PrintCLike.cpp.template"
                                                                      print(intVal());
                                                            #line 8637 "PrintCLike.cpp"
  append(L"b");
                                                            #line 4965 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(k));
                                                            #line 8641 "PrintCLike.cpp"
  append(L"W");
                                                            #line 4966 "PrintCLike.cpp.template"
                                                                      print(assign());
                                                                      print(thiz());
                                                            #line 8646 "PrintCLike.cpp"
  append(L"b");
                                                            #line 4968 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(k));
                                                            #line 8650 "PrintCLike.cpp"
  append(L"; ");
                                                            #line 4969 "PrintCLike.cpp.template"
                                                                      print(intVal());
                                                            #line 8654 "PrintCLike.cpp"
  append(L"e");
                                                            #line 4970 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(k));
                                                            #line 8658 "PrintCLike.cpp"
  append(L"W");
                                                            #line 4971 "PrintCLike.cpp.template"
                                                                      print(assign());
                                                                      print(thiz());
                                                            #line 8663 "PrintCLike.cpp"
  append(L"e");
                                                            #line 4973 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(k));
                                                                    }
                                                                    print(semicolon());
                                                            #line 8669 "PrintCLike.cpp"
  append(L"\n");
  append(L"\n");
  append(L"  ");
                                                            #line 4978 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8675 "PrintCLike.cpp"
  append(L"l1 = code; ");
                                                            #line 4979 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8679 "PrintCLike.cpp"
  append(L"b1 = ");
                                                            #line 4980 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8683 "PrintCLike.cpp"
  append(L"begin; ");
                                                            #line 4981 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8687 "PrintCLike.cpp"
  append(L"e1 = ");
                                                            #line 4982 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8691 "PrintCLike.cpp"
  append(L"end");
                                                            #line 4983 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                    for (size_t k = 2; k <= grammar->k; ++k)
                                                                    {
                                                            #line 8697 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4987 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 8702 "PrintCLike.cpp"
  append(L"l");
                                                            #line 4988 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(k));
                                                            #line 8706 "PrintCLike.cpp"
  append(L" = 0");
                                                            #line 4989 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                                    }
                                                                  }
                                                                  if (isLrParser)
                                                                  {
                                                            #line 8714 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4995 "PrintCLike.cpp.template"
                                                                    if (useGlr)
                                                                    {
                                                                      if (! isCpp())
                                                                      {
                                                            #line 8722 "PrintCLike.cpp"
  append(L"thread = ");
                                                            #line 4999 "PrintCLike.cpp.template"
                                                                      }
                                                                      if (isJava())
                                                                      {
                                                                        print(className.c_str());
                                                            #line 8729 "PrintCLike.cpp"
  append(L".this.");
                                                            #line 5003 "PrintCLike.cpp.template"
                                                                      }
                                                                      else if (isCSharp() || isCpp() || isHaxe() || isScala() || isTypescript() || isGo() || isPython())
                                                                      {
                                                                        print(thiz());
                                                            #line 8736 "PrintCLike.cpp"
  append(L"parser");
                                                            #line 5007 "PrintCLike.cpp.template"
                                                                        print(arrow());
                                                                      }
                                                                    }
                                                                    else
                                                                    {
                                                                      print(thiz());
                                                                    }
                                                            #line 8746 "PrintCLike.cpp"
  append(L"parse(-1, ");
                                                            #line 5014 "PrintCLike.cpp.template"
                                                                    print(format.toString<wchar_t>(grammar->whitespace->getStateId()));
                                                                    if (tree)
                                                                    {
                                                            #line 8752 "PrintCLike.cpp"
  append(L", ");
                                                            #line 5017 "PrintCLike.cpp.template"
                                                                      print(nullPtr());
                                                                    }
                                                                    if (useGlr)
                                                                    {
                                                            #line 8759 "PrintCLike.cpp"
  append(L", thread");
                                                            #line 5021 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 8763 "PrintCLike.cpp"
  append(L")");
                                                            #line 5022 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                  }
                                                                  else
                                                                  {
                                                            #line 8770 "PrintCLike.cpp"
  append(L"\n");
  append(L"\n");
  append(L"  ");
                                                            #line 5028 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8776 "PrintCLike.cpp"
  append(L"try_");
                                                            #line 5029 "PrintCLike.cpp.template"
                                                                    print(Format::acceptableName<WString>(grammar->whitespace->name).c_str());
                                                                    if (! isScala()) print(L"()");
                                                                    print(semicolon());
                                                                  }
                                                                  if (useGlr)
                                                                  {
                                                                    if (isJavascript())
                                                                    {
                                                            #line 8787 "PrintCLike.cpp"
  append(L"\n");
  append(L"  end = thread.getEnd();");
                                                            #line 5038 "PrintCLike.cpp.template"
                                                                    }
                                                                    else if (isCpp())
                                                                    {
                                                            #line 8794 "PrintCLike.cpp"
  append(L"\n");
  append(L"  end = thread->end;\n");
  append(L"  delete thread;");
                                                            #line 5043 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 8802 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5047 "PrintCLike.cpp.template"
                                                                      if (useGlr) print(thiz());
                                                            #line 8807 "PrintCLike.cpp"
  append(L"end = thread");
                                                            #line 5048 "PrintCLike.cpp.template"
                                                                      print(arrow());
                                                            #line 8811 "PrintCLike.cpp"
  append(L"end");
                                                            #line 5049 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                                    }
                                                                  }
                                                                  else
                                                                  {
                                                            #line 8819 "PrintCLike.cpp"
  append(L"\n");
  append(L"\n");
  append(L"  ");
                                                            #line 5056 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8825 "PrintCLike.cpp"
  append(L"b0 = b0W; ");
                                                            #line 5057 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8829 "PrintCLike.cpp"
  append(L"e0 = e0W");
                                                            #line 5058 "PrintCLike.cpp.template"
                                                                    for (size_t k = 1; k < grammar->k; ++k)
                                                                    {
                                                            #line 8834 "PrintCLike.cpp"
  append(L"; ");
                                                            #line 5060 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 8838 "PrintCLike.cpp"
  append(L"l");
                                                            #line 5061 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(k));
                                                            #line 8842 "PrintCLike.cpp"
  append(L" = l");
                                                            #line 5062 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(k));
                                                            #line 8846 "PrintCLike.cpp"
  append(L"W");
                                                            #line 5063 "PrintCLike.cpp.template"
                                                                      if (isPython())
                                                                      {
                                                            #line 8851 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5066 "PrintCLike.cpp.template"
                                                                      }
                                                                      else
                                                                      {
                                                            #line 8858 "PrintCLike.cpp"
  append(L"; ");
                                                            #line 5069 "PrintCLike.cpp.template"
                                                                      }
                                                            #line 8862 "PrintCLike.cpp"
  append(L"if ");
                                                            #line 5070 "PrintCLike.cpp.template"
                                                                      print(ifLeftParen());
                                                                      print(thiz());
                                                            #line 8867 "PrintCLike.cpp"
  append(L"l");
                                                            #line 5072 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(k));
                                                            #line 8871 "PrintCLike.cpp"
  append(L" != 0");
                                                            #line 5073 "PrintCLike.cpp.template"
                                                                      print(ifRightParen());
                                                                      if (isPython())
                                                                      {
                                                                        increaseIndent();
                                                                      }
                                                                      else
                                                                      {
                                                            #line 8881 "PrintCLike.cpp"
  append(L" {");
                                                            #line 5080 "PrintCLike.cpp.template"
                                                                      }
                                                            #line 8885 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5082 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 8890 "PrintCLike.cpp"
  append(L"b");
                                                            #line 5083 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(k));
                                                            #line 8894 "PrintCLike.cpp"
  append(L" = b");
                                                            #line 5084 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(k));
                                                            #line 8898 "PrintCLike.cpp"
  append(L"W; ");
                                                            #line 5085 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 8902 "PrintCLike.cpp"
  append(L"e");
                                                            #line 5086 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(k));
                                                            #line 8906 "PrintCLike.cpp"
  append(L" = e");
                                                            #line 5087 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(k));
                                                            #line 8910 "PrintCLike.cpp"
  append(L"W");
                                                            #line 5088 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(semicolon());
                                                                    if (isPython())
                                                                    {
                                                                      decreaseIndent(grammar->k - 1);
                                                                    }
                                                                    else
                                                                    {
                                                            #line 8921 "PrintCLike.cpp"
  append(L" ");
                                                            #line 5096 "PrintCLike.cpp.template"
                                                                      for (size_t k = 1; k < grammar->k; ++k)
                                                                      {
                                                            #line 8926 "PrintCLike.cpp"
  append(L"}");
                                                            #line 5098 "PrintCLike.cpp.template"
                                                                      }
                                                                    }
                                                                  }
                                                                  print(rightBrace());
                                                            #line 8933 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5103 "PrintCLike.cpp.template"
                                                                  if (! isGo())
                                                                    decreaseIndent();
                                                                }
                                                                if (tree && ! isLrParser)
                                                                {
                                                                  if (! isGo())
                                                                    increaseIndent();
                                                                  openMethod (voidType(), L"", L"whitespace", L"");
                                                                  print(leftBrace());
                                                            #line 8945 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if ");
                                                            #line 5113 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                                  print(thiz());
                                                            #line 8951 "PrintCLike.cpp"
  append(L"e0 != ");
                                                            #line 5115 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8955 "PrintCLike.cpp"
  append(L"b1");
                                                            #line 5116 "PrintCLike.cpp.template"
                                                                  print(ifRightParen());
                                                                  increaseIndent();
                                                                  print(leftBrace());
                                                                  decreaseIndent();
                                                            #line 8962 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 5121 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8967 "PrintCLike.cpp"
  append(L"eventHandler");
                                                            #line 5122 "PrintCLike.cpp.template"
                                                                  if (shiftAmbiguity && isTypescript()) print(L"!");
                                                                  print(arrow());
                                                                  if (isGo())
                                                                  {
                                                            #line 8974 "PrintCLike.cpp"
  append(L"W");
                                                            #line 5126 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 8980 "PrintCLike.cpp"
  append(L"w");
                                                            #line 5129 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 8984 "PrintCLike.cpp"
  append(L"hitespace(");
                                                            #line 5130 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8988 "PrintCLike.cpp"
  append(L"e0, ");
                                                            #line 5131 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8992 "PrintCLike.cpp"
  append(L"b1)");
                                                            #line 5132 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                            #line 8996 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 5134 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 9001 "PrintCLike.cpp"
  append(L"e0 = ");
                                                            #line 5135 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 9005 "PrintCLike.cpp"
  append(L"b1");
                                                            #line 5136 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                  increaseIndent();
                                                                  print(rightBrace());
                                                                  decreaseIndent();
                                                                  print(rightBrace());
                                                                  if (! isGo())
                                                                    decreaseIndent();
                                                            #line 9015 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5144 "PrintCLike.cpp.template"
                                                                }
                                                                if (! isGo())
                                                                  increaseIndent();
                                                                openMethod(intType(), L"", L"matchW", L"int tokenSetId", false, useGlr ? L"ParsingThread" : className.c_str());
                                                                print(leftBrace());
                                                                if (isScala())
                                                                {
                                                            #line 9025 "PrintCLike.cpp"
  append(L"\n");
  append(L"  var continue = true\n");
  append(L"  var code = 0\n");
  append(L"  while (continue) {\n");
  append(L"    code = matcher(tokenSetId)");
                                                            #line 5155 "PrintCLike.cpp.template"
                                                                  increaseIndent(2);
                                                                }
                                                                else
                                                                {
                                                                  if (! isPython())
                                                                  {
                                                            #line 9038 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5162 "PrintCLike.cpp.template"
                                                                    print((isJavascript() || isTypescript() || isHaxe() || isGo()) ? L"var" : L"int");
                                                            #line 9043 "PrintCLike.cpp"
  append(L" code");
                                                            #line 5163 "PrintCLike.cpp.template"
                                                                    if (isTypescript())
                                                                    {
                                                            #line 9048 "PrintCLike.cpp"
  append(L": number");
                                                            #line 5165 "PrintCLike.cpp.template"
                                                                    }
                                                                    else if (isGo())
                                                                    {
                                                            #line 9054 "PrintCLike.cpp"
  append(L" int");
                                                            #line 5168 "PrintCLike.cpp.template"
                                                                    }
                                                                    if (isHaxe())
                                                                    {
                                                            #line 9060 "PrintCLike.cpp"
  append(L" = 0");
                                                            #line 5171 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(semicolon());
                                                                  }
                                                                  if (isHaxe() || isPython())
                                                                  {
                                                            #line 9068 "PrintCLike.cpp"
  append(L"\n");
  append(L"  while ");
                                                            #line 5177 "PrintCLike.cpp.template"
                                                                    print(ifLeftParen());
                                                                    print(isPython() ? L"T" : L"t");
                                                            #line 9074 "PrintCLike.cpp"
  append(L"rue");
                                                            #line 5179 "PrintCLike.cpp.template"
                                                                    print(ifRightParen());
                                                                  }
                                                                  else
                                                                  {
                                                            #line 9081 "PrintCLike.cpp"
  append(L"\n");
  append(L"  for");
                                                            #line 5184 "PrintCLike.cpp.template"
                                                                    if (! isGo())
                                                                    {
                                                            #line 9087 "PrintCLike.cpp"
  append(L" (;;)");
                                                            #line 5186 "PrintCLike.cpp.template"
                                                                    }
                                                                  }
                                                                  increaseIndent();
                                                                  print(leftBrace());
                                                                  increaseIndent();
                                                            #line 9095 "PrintCLike.cpp"
  append(L"\n");
  append(L"code = ");
                                                            #line 5192 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 9100 "PrintCLike.cpp"
  append(L"match(tokenSetId)");
                                                            #line 5193 "PrintCLike.cpp.template"
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
                                                            #line 9129 "PrintCLike.cpp"
  append(L"\n");
  append(L"  continue = false\n");
  append(L"}\n");
  append(L"else {\n");
  append(L"  ");
                                                            #line 5223 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 9137 "PrintCLike.cpp"
  append(L"skip(code)\n");
  append(L"}");
                                                            #line 5225 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 9144 "PrintCLike.cpp"
  append(L"\n");
  append(L"  break");
                                                            #line 5229 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                    print(rightBrace());
                                                            #line 9150 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5232 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 9154 "PrintCLike.cpp"
  append(L"skip(code);");
                                                            #line 5233 "PrintCLike.cpp.template"
                                                                  }
                                                                }
                                                                else if (isScala())
                                                                {
                                                            #line 9161 "PrintCLike.cpp"
  append(L"\n");
  append(L"continue = false");
                                                            #line 5238 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 9168 "PrintCLike.cpp"
  append(L"\n");
  append(L"break");
                                                            #line 5242 "PrintCLike.cpp.template"
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
                                                            #line 9182 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5253 "PrintCLike.cpp.template"
                                                                if (! isScala())
                                                                {
                                                            #line 9188 "PrintCLike.cpp"
  append(L"return ");
                                                            #line 5255 "PrintCLike.cpp.template"
                                                                }
                                                            #line 9192 "PrintCLike.cpp"
  append(L"code");
                                                            #line 5256 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                print(rightBrace());
                                                            #line 9197 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5259 "PrintCLike.cpp.template"
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
                                                            #line 9213 "PrintCLike.cpp"
  append(L"\n");
  append(L"def parse(): Unit = {\n");
  append(L"  parse_");
                                                            #line 5274 "PrintCLike.cpp.template"
                                                                  print(Format::acceptableName<WString>(grammar->startSymbol()->name).c_str());
                                                            #line 9219 "PrintCLike.cpp"
  append(L"()\n");
  append(L"}\n");
                                                            #line 5277 "PrintCLike.cpp.template"
                                                                }
                                                                if (memoization)
                                                                {
                                                                  int bits = Math::bits(grammar->conflictCount);
                                                            #line 9227 "PrintCLike.cpp"
  append(L"\n");
  append(L"private def memoize(i: Int, e: Int, v: Int): Unit = {\n");
  append(L"  memo.put((e << ");
                                                            #line 5283 "PrintCLike.cpp.template"
                                                                  print(format.toString<wchar_t>(bits));
                                                            #line 9233 "PrintCLike.cpp"
  append(L") + i, v)\n");
  append(L"}\n");
  append(L"\n");
  append(L"private def memoized(i: Int, e: Int) = {\n");
  append(L"  memo.getOrElse((e << ");
                                                            #line 5288 "PrintCLike.cpp.template"
                                                                  print(format.toString<wchar_t>(bits));
                                                            #line 9241 "PrintCLike.cpp"
  append(L") + i, 0)\n");
  append(L"}\n");
                                                            #line 5291 "PrintCLike.cpp.template"
                                                                }
                                                            #line 9246 "PrintCLike.cpp"
  append(L"\n");
  append(L"def error(b: Int, e: Int, s: Int, l: Int, t: Int): Int = {");
                                                            #line 5293 "PrintCLike.cpp.template"
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
                                                            #line 9260 "PrintCLike.cpp"
  append(L"\n");
  append(L"if ");
                                                            #line 5304 "PrintCLike.cpp.template"
                                                                print(ifLeftParen());
                                                                if (grammar->noThrow)
                                                                {
                                                                  print(thiz());
                                                            #line 9268 "PrintCLike.cpp"
  append(L"viable ");
                                                            #line 5308 "PrintCLike.cpp.template"
                                                                  if (isPython())
                                                                  {
                                                            #line 9273 "PrintCLike.cpp"
  append(L"and");
                                                            #line 5310 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 9279 "PrintCLike.cpp"
  append(L"&&");
                                                            #line 5313 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 9283 "PrintCLike.cpp"
  append(L" ");
                                                            #line 5314 "PrintCLike.cpp.template"
                                                                }
                                                            #line 9287 "PrintCLike.cpp"
  append(L"e >= ");
                                                            #line 5315 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 9291 "PrintCLike.cpp"
  append(L"ex");
                                                            #line 5316 "PrintCLike.cpp.template"
                                                                print(ifRightParen());
                                                                print(leftBrace());
                                                            #line 9296 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5319 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 9301 "PrintCLike.cpp"
  append(L"bx = b");
                                                            #line 5320 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 9305 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5322 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 9310 "PrintCLike.cpp"
  append(L"ex = e");
                                                            #line 5323 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 9314 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5325 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 9319 "PrintCLike.cpp"
  append(L"sx = s");
                                                            #line 5326 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 9323 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5328 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 9328 "PrintCLike.cpp"
  append(L"lx = l");
                                                            #line 5329 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 9332 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5331 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 9337 "PrintCLike.cpp"
  append(L"tx = t");
                                                            #line 5332 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                print(rightBrace());
                                                                decreaseIndent();
                                                                if (grammar->noThrow)
                                                                {
                                                            #line 9345 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5338 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 9350 "PrintCLike.cpp"
  append(L"viable = ");
                                                            #line 5339 "PrintCLike.cpp.template"
                                                                  if (isPython())
                                                                  {
                                                            #line 9355 "PrintCLike.cpp"
  append(L"F");
                                                            #line 5341 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 9361 "PrintCLike.cpp"
  append(L"f");
                                                            #line 5344 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 9365 "PrintCLike.cpp"
  append(L"alse");
                                                            #line 5345 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                            #line 9369 "PrintCLike.cpp"
  append(L"\n");
  append(L"  return -s");
                                                            #line 5347 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                                else
                                                                {
                                                                  printFlush(1, true);
                                                            #line 9378 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5353 "PrintCLike.cpp.template"
                                                                  print(beginThrowStmt());
                                                                  print(thiz());
                                                            #line 9384 "PrintCLike.cpp"
  append(L"bx, ");
                                                            #line 5355 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 9388 "PrintCLike.cpp"
  append(L"ex, ");
                                                            #line 5356 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 9392 "PrintCLike.cpp"
  append(L"sx, ");
                                                            #line 5357 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 9396 "PrintCLike.cpp"
  append(L"lx, ");
                                                            #line 5358 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 9400 "PrintCLike.cpp"
  append(L"tx");
                                                            #line 5359 "PrintCLike.cpp.template"
                                                                  print(endThrowStmt());
                                                                  print(semicolon());
                                                                }
                                                              }
                                                              else
                                                              {
                                                                printFlush(1, true);
                                                            #line 9410 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5367 "PrintCLike.cpp.template"
                                                                if (isGo())
                                                                {
                                                            #line 9416 "PrintCLike.cpp"
  append(L"panic(&ParseError{b, e, s, l, t");
                                                            #line 5369 "PrintCLike.cpp.template"
                                                                  if (rejectsAmbiguity())
                                                                  {
                                                            #line 9421 "PrintCLike.cpp"
  append(L", false");
                                                            #line 5371 "PrintCLike.cpp.template"
                                                                    if (tree)
                                                                    {
                                                            #line 9426 "PrintCLike.cpp"
  append(L", nil");
                                                            #line 5373 "PrintCLike.cpp.template"
                                                                    }
                                                                  }
                                                            #line 9431 "PrintCLike.cpp"
  append(L"})");
                                                            #line 5375 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                                  print(beginThrowStmt());
                                                            #line 9438 "PrintCLike.cpp"
  append(L"b, e, s, l, t");
                                                            #line 5379 "PrintCLike.cpp.template"
                                                                  print(endThrowStmt());
                                                                  print(semicolon());
                                                                }
                                                              }
                                                              print(rightBrace());
                                                            #line 9446 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5385 "PrintCLike.cpp.template"
                                                              if (! isGo())
                                                                decreaseIndent();
                                                              if (isScala())
                                                              {
                                                                printInstanceCode();
                                                              }
                                                              privateVars();
                                                            }

                                                            void PrintCLike::printCountMethod()
                                                            {
                                                              Trace("PrintCLike::printCountMethod");

                                                              const wchar_t *clazz = useGlr ? L"StackNode" : className.c_str();
                                                              if (grammar->states->hasLookback)
                                                              {
                                                            #line 9465 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5402 "PrintCLike.cpp.template"
                                                                openMethod(intType(), L"", L"lookback", L"int x, int y", false, clazz);
                                                                const wchar_t *lookback = isGo() ? L"lookback" : L"LOOKBACK";
                                                                print(leftBrace());
                                                                increaseIndent();
                                                                if (isGo())
                                                                {
                                                            #line 9474 "PrintCLike.cpp"
  append(L"\n");
  append(L"i := lookback[y]\n");
  append(L"l := lookback[i]\n");
  append(L"for l > x {");
                                                            #line 5411 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 9483 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5415 "PrintCLike.cpp.template"
                                                                  print(intVar());
                                                            #line 9487 "PrintCLike.cpp"
  append(L"i");
                                                            #line 5416 "PrintCLike.cpp.template"
                                                                  print(assign());
                                                                  print(staticPrefix());
                                                                  print(lookback);
                                                                  print(leftbracket());
                                                            #line 9494 "PrintCLike.cpp"
  append(L"y");
                                                            #line 5420 "PrintCLike.cpp.template"
                                                                  print(rightbracket());
                                                                  print(semicolon());
                                                            #line 9499 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5423 "PrintCLike.cpp.template"
                                                                  print(intVar());
                                                            #line 9503 "PrintCLike.cpp"
  append(L"l");
                                                            #line 5424 "PrintCLike.cpp.template"
                                                                  print(assign());
                                                                  print(staticPrefix());
                                                                  print(lookback);
                                                                  print(leftbracket());
                                                            #line 9510 "PrintCLike.cpp"
  append(L"i");
                                                            #line 5428 "PrintCLike.cpp.template"
                                                                  print(rightbracket());
                                                                  print(semicolon());
                                                            #line 9515 "PrintCLike.cpp"
  append(L"\n");
  append(L"while ");
                                                            #line 5431 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                            #line 9520 "PrintCLike.cpp"
  append(L"l > x");
                                                            #line 5432 "PrintCLike.cpp.template"
                                                                  print(ifRightParen());
                                                                  print(leftBrace());
                                                                }
                                                            #line 9526 "PrintCLike.cpp"
  append(L"\n");
  append(L"  i += 2");
                                                            #line 5436 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 9531 "PrintCLike.cpp"
  append(L"\n");
  append(L"  l = ");
                                                            #line 5438 "PrintCLike.cpp.template"
                                                                print(staticPrefix());
                                                                print(lookback);
                                                                print(leftbracket());
                                                            #line 9538 "PrintCLike.cpp"
  append(L"i");
                                                            #line 5441 "PrintCLike.cpp.template"
                                                                print(rightbracket());
                                                                print(semicolon());
                                                                print(rightBrace());
                                                            #line 9544 "PrintCLike.cpp"
  append(L"\n");
  append(L"if ");
                                                            #line 5445 "PrintCLike.cpp.template"
                                                                print(ifLeftParen());
                                                            #line 9549 "PrintCLike.cpp"
  append(L"l < x");
                                                            #line 5446 "PrintCLike.cpp.template"
                                                                print(ifRightParen());
                                                                print(leftBrace());
                                                            #line 9554 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5449 "PrintCLike.cpp.template"
                                                                print(returnKeyword());
                                                            #line 9559 "PrintCLike.cpp"
  append(L"0");
                                                            #line 5450 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 9563 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5452 "PrintCLike.cpp.template"
                                                                print(elseWithBraces());
                                                            #line 9567 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5454 "PrintCLike.cpp.template"
                                                                print(returnKeyword());
                                                                print(staticPrefix());
                                                                print(lookback);
                                                                print(leftbracket());
                                                            #line 9575 "PrintCLike.cpp"
  append(L"i + 1");
                                                            #line 5458 "PrintCLike.cpp.template"
                                                                print(rightbracket());
                                                                print(semicolon());
                                                                print(rightBrace());
                                                                decreaseIndent();
                                                                print(rightBrace());
                                                            #line 9583 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5464 "PrintCLike.cpp.template"
                                                                if (isJavascript() && useGlr)
                                                                {
                                                            #line 9588 "PrintCLike.cpp"
  append(L"\n");
  append(L"this.count = function(code)\n");
                                                            #line 5468 "PrintCLike.cpp.template"
                                                                }
                                                                else if (isTypescript() && useGlr)
                                                                {
                                                            #line 9595 "PrintCLike.cpp"
  append(L"\n");
  append(L"public count(code: number)\n");
                                                            #line 5473 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                                  openMethod(intType(), L"", L"count", L"int code", false, clazz);
                                                                }
                                                                print(leftBrace());
                                                                increaseIndent();
                                                            #line 9606 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5481 "PrintCLike.cpp.template"
                                                                print(intVar());
                                                            #line 9610 "PrintCLike.cpp"
  append(L"count");
                                                            #line 5482 "PrintCLike.cpp.template"
                                                                print(assign());
                                                            #line 9614 "PrintCLike.cpp"
  append(L"0");
                                                            #line 5483 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                int stackElementSize = tree ? 3 : 2;
                                                                if (isHaxe() || isScala())
                                                                {
                                                                  if (useGlr)
                                                                  {
                                                            #line 9623 "PrintCLike.cpp"
  append(L"\n");
  append(L"var node = this");
                                                            #line 5490 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                    if (isScala())
                                                                    {
                                                            #line 9630 "PrintCLike.cpp"
  append(L"\n");
  append(L"var c = code");
                                                            #line 5494 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 9635 "PrintCLike.cpp"
  append(L"\n");
  append(L"while ");
                                                            #line 5496 "PrintCLike.cpp.template"
                                                                    print(ifLeftParen());
                                                            #line 9640 "PrintCLike.cpp"
  append(L"node.state >= 0");
                                                            #line 5497 "PrintCLike.cpp.template"
                                                                    print(ifRightParen());
                                                                    print(leftBrace());
                                                                    if (isScala())
                                                                    {
                                                            #line 9647 "PrintCLike.cpp"
  append(L"\n");
  append(L"  c = lookback(node.code, c)\n");
  append(L"  if (c == 0) return count\n");
  append(L"  count += 1");
                                                            #line 5504 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 9656 "PrintCLike.cpp"
  append(L"\n");
  append(L"  code = lookback(node.code, code);\n");
  append(L"  if ");
                                                            #line 5509 "PrintCLike.cpp.template"
                                                                      print(ifLeftParen());
                                                            #line 9662 "PrintCLike.cpp"
  append(L"code == 0");
                                                            #line 5510 "PrintCLike.cpp.template"
                                                                      print(ifRightParen());
                                                            #line 9666 "PrintCLike.cpp"
  append(L"\n");
  append(L"    break");
                                                            #line 5513 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                            #line 9671 "PrintCLike.cpp"
  append(L"\n");
  append(L"  count++");
                                                            #line 5515 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                                    }
                                                            #line 9677 "PrintCLike.cpp"
  append(L"\n");
  append(L"  node = node.link");
                                                            #line 5518 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                  }
                                                                  else
                                                                  {
                                                            #line 9685 "PrintCLike.cpp"
  append(L"\n");
  append(L"var t = top");
                                                            #line 5523 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 9690 "PrintCLike.cpp"
  append(L"\n");
  append(L"var c = code");
                                                            #line 5525 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 9695 "PrintCLike.cpp"
  append(L"\n");
  append(L"while (t >= 0)");
                                                            #line 5527 "PrintCLike.cpp.template"
                                                                    print(leftBrace());
                                                            #line 9700 "PrintCLike.cpp"
  append(L"\n");
  append(L"  c = lookback(iStack");
                                                            #line 5529 "PrintCLike.cpp.template"
                                                                    print(leftbracket());
                                                            #line 9705 "PrintCLike.cpp"
  append(L"t");
                                                            #line 5530 "PrintCLike.cpp.template"
                                                                    print(rightbracket());
                                                            #line 9709 "PrintCLike.cpp"
  append(L", c)");
                                                            #line 5531 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 9713 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if ");
                                                            #line 5533 "PrintCLike.cpp.template"
                                                                    print(ifLeftParen());
                                                            #line 9718 "PrintCLike.cpp"
  append(L"c == 0");
                                                            #line 5534 "PrintCLike.cpp.template"
                                                                    print(ifRightParen());
                                                            #line 9722 "PrintCLike.cpp"
  append(L" return count");
                                                            #line 5535 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 9726 "PrintCLike.cpp"
  append(L"\n");
  append(L"  count += 1");
                                                            #line 5537 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 9731 "PrintCLike.cpp"
  append(L"\n");
  append(L"  t -= ");
                                                            #line 5539 "PrintCLike.cpp.template"
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
                                                            #line 9745 "PrintCLike.cpp"
  append(L"\n");
  append(L"node = self\n");
  append(L"while ");
                                                            #line 5551 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 9753 "PrintCLike.cpp"
  append(L"\n");
  append(L"for ");
                                                            #line 5555 "PrintCLike.cpp.template"
                                                                      print(ifLeftParen());
                                                                      if (isJavascript() || isTypescript())
                                                                      {
                                                            #line 9760 "PrintCLike.cpp"
  append(L"var ");
                                                            #line 5558 "PrintCLike.cpp.template"
                                                                      }
                                                                      else if (!isGo())
                                                                      {
                                                            #line 9766 "PrintCLike.cpp"
  append(L"StackNode ");
                                                            #line 5561 "PrintCLike.cpp.template"
                                                                      }
                                                                      if (isCpp()) print(L"*");
                                                            #line 9771 "PrintCLike.cpp"
  append(L"node");
                                                            #line 5563 "PrintCLike.cpp.template"
                                                                      if (isTypescript())
                                                                      {
                                                            #line 9776 "PrintCLike.cpp"
  append(L": StackNode | null");
                                                            #line 5565 "PrintCLike.cpp.template"
                                                                      }
                                                                      print(assign());
                                                            #line 9781 "PrintCLike.cpp"
  append(L"this; ");
                                                            #line 5567 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 9785 "PrintCLike.cpp"
  append(L"node");
                                                            #line 5568 "PrintCLike.cpp.template"
                                                                    if (isTypescript()) print(L"!");
                                                                    print(arrow());
                                                            #line 9790 "PrintCLike.cpp"
  append(L"state >= 0");
                                                            #line 5570 "PrintCLike.cpp.template"
                                                                    if (isPython())
                                                                    {
                                                            #line 9795 "PrintCLike.cpp"
  append(L":");
                                                            #line 5572 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 9801 "PrintCLike.cpp"
  append(L"; node = node");
                                                            #line 5575 "PrintCLike.cpp.template"
                                                                      if (isTypescript()) print(L"!");
                                                                      print(arrow());
                                                            #line 9806 "PrintCLike.cpp"
  append(L"link");
                                                            #line 5577 "PrintCLike.cpp.template"
                                                                      print(ifRightParen());
                                                                    }
                                                                    print(leftBrace());
                                                            #line 9812 "PrintCLike.cpp"
  append(L"\n");
  append(L"  code = ");
                                                            #line 5581 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                                    print(isGo() ? L"L" : L"l");
                                                            #line 9818 "PrintCLike.cpp"
  append(L"ookback(node");
                                                            #line 5583 "PrintCLike.cpp.template"
                                                                    if (isTypescript()) print(L"!");
                                                                    print(arrow());
                                                            #line 9823 "PrintCLike.cpp"
  append(L"code, code)");
                                                            #line 5585 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                  }
                                                                  else
                                                                  {
                                                                    if (isPython())
                                                                    {
                                                            #line 9832 "PrintCLike.cpp"
  append(L"\n");
  append(L"t");
                                                            #line 5592 "PrintCLike.cpp.template"
                                                                      print(assign());
                                                                      print(thiz());
                                                            #line 9838 "PrintCLike.cpp"
  append(L"top");
                                                            #line 5594 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                            #line 9842 "PrintCLike.cpp"
  append(L"\n");
  append(L"while ");
                                                            #line 5596 "PrintCLike.cpp.template"
                                                                      print(ifLeftParen());
                                                                      print(intVar());
                                                            #line 9848 "PrintCLike.cpp"
  append(L"t >= 0");
                                                            #line 5598 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 9854 "PrintCLike.cpp"
  append(L"\n");
  append(L"for ");
                                                            #line 5602 "PrintCLike.cpp.template"
                                                                      print(ifLeftParen());
                                                                      print(intVar());
                                                            #line 9860 "PrintCLike.cpp"
  append(L"t");
                                                            #line 5604 "PrintCLike.cpp.template"
                                                                      print(assign());
                                                                      print(thiz());
                                                            #line 9865 "PrintCLike.cpp"
  append(L"top; t >= 0; t -= ");
                                                            #line 5606 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(stackElementSize));
                                                                    }
                                                                    print(ifRightParen());
                                                                    print(leftBrace());
                                                            #line 9872 "PrintCLike.cpp"
  append(L"\n");
  append(L"  code = ");
                                                            #line 5611 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 9877 "PrintCLike.cpp"
  append(L"lookback(");
                                                            #line 5612 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 9881 "PrintCLike.cpp"
  append(L"iStack[t], code)");
                                                            #line 5613 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                  }
                                                            #line 9886 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if ");
                                                            #line 5616 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                            #line 9891 "PrintCLike.cpp"
  append(L"code == 0");
                                                            #line 5617 "PrintCLike.cpp.template"
                                                                  print(ifRightParen());
                                                                  increaseIndent();
                                                                  print(leftBrace());
                                                            #line 9897 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5621 "PrintCLike.cpp.template"
                                                                  if (! isHaxe() && ! isScala())
                                                                  {
                                                            #line 9903 "PrintCLike.cpp"
  append(L"break");
                                                            #line 5623 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 9909 "PrintCLike.cpp"
  append(L"return count");
                                                            #line 5626 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(semicolon());
                                                                  print(rightBrace());
                                                                  decreaseIndent();
                                                            #line 9916 "PrintCLike.cpp"
  append(L"\n");
  append(L"  count += 1");
                                                            #line 5631 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                  if (isPython())
                                                                  {
                                                                    if (useGlr)
                                                                    {
                                                            #line 9925 "PrintCLike.cpp"
  append(L"\n");
  append(L"  node = node.link");
                                                            #line 5637 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 9932 "PrintCLike.cpp"
  append(L"\n");
  append(L"  t -= ");
                                                            #line 5641 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(stackElementSize));
                                                                    }
                                                                  }
                                                                }
                                                                print(rightBrace());
                                                            #line 9941 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5647 "PrintCLike.cpp.template"
                                                                print(returnKeyword());
                                                            #line 9945 "PrintCLike.cpp"
  append(L"count");
                                                            #line 5648 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                decreaseIndent();
                                                                print(rightBrace());
                                                                if (isJavascript() && useGlr)
                                                                {
                                                            #line 9953 "PrintCLike.cpp"
  append(L";");
                                                            #line 5653 "PrintCLike.cpp.template"
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
                                                            #line 9979 "PrintCLike.cpp"
  append(L"\n");
  append(L"if ");
                                                            #line 5677 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                                  print(thiz());
                                                            #line 9985 "PrintCLike.cpp"
  append(L"l");
                                                            #line 5679 "PrintCLike.cpp.template"
                                                                  print(kAsString);
                                                            #line 9989 "PrintCLike.cpp"
  append(L" == 0");
                                                            #line 5680 "PrintCLike.cpp.template"
                                                                  print(ifRightParen());
                                                                  print(leftBrace());
                                                            #line 9994 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5683 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 9999 "PrintCLike.cpp"
  append(L"l");
                                                            #line 5684 "PrintCLike.cpp.template"
                                                                  print(kAsString);
                                                            #line 10003 "PrintCLike.cpp"
  append(L" = ");
                                                            #line 5685 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 10007 "PrintCLike.cpp"
  append(L"match");
                                                            #line 5686 "PrintCLike.cpp.template"
                                                                  if (withWhitespace)
                                                                  {
                                                            #line 10012 "PrintCLike.cpp"
  append(L"W");
                                                            #line 5688 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isScala())
                                                                  {
                                                            #line 10018 "PrintCLike.cpp"
  append(L"er");
                                                            #line 5691 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 10022 "PrintCLike.cpp"
  append(L"(tokenSetId)");
                                                            #line 5692 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                            #line 10026 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5694 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 10031 "PrintCLike.cpp"
  append(L"b");
                                                            #line 5695 "PrintCLike.cpp.template"
                                                                  print(kAsString);
                                                            #line 10035 "PrintCLike.cpp"
  append(L" = ");
                                                            #line 5696 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 10039 "PrintCLike.cpp"
  append(L"begin");
                                                            #line 5697 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                            #line 10043 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5699 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 10048 "PrintCLike.cpp"
  append(L"e");
                                                            #line 5700 "PrintCLike.cpp.template"
                                                                  print(kAsString);
                                                            #line 10052 "PrintCLike.cpp"
  append(L" = ");
                                                            #line 5701 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 10056 "PrintCLike.cpp"
  append(L"end");
                                                            #line 5702 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                  print(rightBrace());
                                                                  if (unlimitedLookahead)
                                                                  {
                                                                    if (k >= 2)
                                                                    {
                                                            #line 10065 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5709 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 10069 "PrintCLike.cpp"
  append(L"lk = prefix + ");
                                                            #line 5710 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 10073 "PrintCLike.cpp"
  append(L"l");
                                                            #line 5711 "PrintCLike.cpp.template"
                                                                      print(kAsString);
                                                                      print(semicolon());
                                                                    }
                                                                  }
                                                                  else
                                                                  {
                                                                    if (k == 2)
                                                                    {
                                                            #line 10084 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5720 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 10088 "PrintCLike.cpp"
  append(L"lk = (");
                                                            #line 5721 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 10092 "PrintCLike.cpp"
  append(L"l2 << ");
                                                            #line 5722 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(grammar->tokenSequenceFactory->tokenBits()));
                                                            #line 10096 "PrintCLike.cpp"
  append(L") | ");
                                                            #line 5723 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 10100 "PrintCLike.cpp"
  append(L"l1");
                                                            #line 5724 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                                    }
                                                                    else if (k > 2)
                                                                    {
                                                            #line 10107 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5729 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 10111 "PrintCLike.cpp"
  append(L"lk |= ");
                                                            #line 5730 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 10115 "PrintCLike.cpp"
  append(L"l");
                                                            #line 5731 "PrintCLike.cpp.template"
                                                                      print(kAsString);
                                                            #line 10119 "PrintCLike.cpp"
  append(L" << ");
                                                            #line 5732 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>((k - 1) * grammar->tokenSequenceFactory->tokenBits()));
                                                                      print(semicolon());
                                                                    }
                                                                  }
                                                                  decreaseIndent();
                                                                  print(rightBrace());
                                                            #line 10128 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5739 "PrintCLike.cpp.template"
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
                                                            #line 10156 "PrintCLike.cpp"
  append(L"\n");
  append(L"  return ");
                                                            #line 5765 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                                if (useGlr && (isCSharp() || isCpp() || isHaxe() || isScala() || isTypescript()))
                                                                {
                                                            #line 10163 "PrintCLike.cpp"
  append(L"parser");
                                                            #line 5768 "PrintCLike.cpp.template"
                                                                  print(arrow());
                                                                }
                                                            #line 10168 "PrintCLike.cpp"
  append(L"input");
                                                            #line 5770 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                print(rightBrace());
                                                                if (isJavascript())
                                                                {
                                                            #line 10175 "PrintCLike.cpp"
  append(L";");
                                                            #line 5774 "PrintCLike.cpp.template"
                                                                }
                                                            #line 10179 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5776 "PrintCLike.cpp.template"
                                                                openMethod(intType(), L"", L"getTokenOffset", L"", true);
                                                                print(leftBrace());
                                                            #line 10184 "PrintCLike.cpp"
  append(L"\n");
  append(L"  return ");
                                                            #line 5779 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 10189 "PrintCLike.cpp"
  append(L"b0");
                                                            #line 5780 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                print(rightBrace());
                                                                if (isJavascript())
                                                                {
                                                            #line 10196 "PrintCLike.cpp"
  append(L";");
                                                            #line 5784 "PrintCLike.cpp.template"
                                                                }
                                                            #line 10200 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5786 "PrintCLike.cpp.template"
                                                                openMethod(intType(), L"", L"getTokenEnd", L"", true);
                                                                print(leftBrace());
                                                            #line 10205 "PrintCLike.cpp"
  append(L"\n");
  append(L"  return ");
                                                            #line 5789 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 10210 "PrintCLike.cpp"
  append(L"e0");
                                                            #line 5790 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                print(rightBrace());
                                                                if (isJavascript())
                                                                {
                                                            #line 10217 "PrintCLike.cpp"
  append(L";");
                                                            #line 5794 "PrintCLike.cpp.template"
                                                                }
                                                            #line 10221 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5796 "PrintCLike.cpp.template"
                                                              }
                                                              if (isJavascript())
                                                              {
                                                                if (useGlr)
                                                                {
                                                            #line 10229 "PrintCLike.cpp"
  append(L"\n");
  append(L"this.reset = function");
                                                            #line 5802 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 10236 "PrintCLike.cpp"
  append(L"\n");
  append(L"function reset");
                                                            #line 5806 "PrintCLike.cpp.template"
                                                                }
                                                            #line 10241 "PrintCLike.cpp"
  append(L"(l, b, e)\n");
  append(L"{");
                                                            #line 5808 "PrintCLike.cpp.template"
                                                              }
                                                              else if (isTypescript())
                                                              {
                                                            #line 10248 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5812 "PrintCLike.cpp.template"
                                                                if (! performanceTest && ! useGlr)
                                                                {
                                                            #line 10253 "PrintCLike.cpp"
  append(L"private ");
                                                            #line 5814 "PrintCLike.cpp.template"
                                                                }
                                                            #line 10257 "PrintCLike.cpp"
  append(L"reset(l: number, b: number, e: number)\n");
  append(L"{");
                                                            #line 5816 "PrintCLike.cpp.template"
                                                              }
                                                              else if (isHaxe())
                                                              {
                                                            #line 10264 "PrintCLike.cpp"
  append(L"\n");
  append(L"public function reset(l, b, e)\n");
  append(L"{");
                                                            #line 5821 "PrintCLike.cpp.template"
                                                              }
                                                              else
                                                              {
                                                                openMethod(voidType(), isJava() ? L"final " : L"", L"reset", L"int l, int b, int e", false, useGlr ? L"ParsingThread" : className.c_str());
                                                                print(leftBrace());
                                                              }
                                                            #line 10275 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5828 "PrintCLike.cpp.template"
                                                              if (! isPython() && ! isScala())
                                                              {
                                                            #line 10281 "PrintCLike.cpp"
  append(L"        ");
                                                            #line 5830 "PrintCLike.cpp.template"
                                                                print(wcslen(thiz()), L" ");
                                                              }
                                                              print(thiz());
                                                            #line 10287 "PrintCLike.cpp"
  append(L"b0 = b; ");
                                                            #line 5833 "PrintCLike.cpp.template"
                                                              print(thiz());
                                                            #line 10291 "PrintCLike.cpp"
  append(L"e0 = b");
                                                            #line 5834 "PrintCLike.cpp.template"
                                                              print(semicolon());
                                                            #line 10295 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5836 "PrintCLike.cpp.template"
                                                              print(thiz());
                                                            #line 10300 "PrintCLike.cpp"
  append(L"l1 = l; ");
                                                            #line 5837 "PrintCLike.cpp.template"
                                                              print(thiz());
                                                            #line 10304 "PrintCLike.cpp"
  append(L"b1 = b; ");
                                                            #line 5838 "PrintCLike.cpp.template"
                                                              print(thiz());
                                                            #line 10308 "PrintCLike.cpp"
  append(L"e1 = e");
                                                            #line 5839 "PrintCLike.cpp.template"
                                                              print(semicolon());
                                                              for (size_t k = 2; k <= grammar->k; ++k)
                                                              {
                                                            #line 10314 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5843 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 10319 "PrintCLike.cpp"
  append(L"l");
                                                            #line 5844 "PrintCLike.cpp.template"
                                                                print(format.toString<wchar_t>(k));
                                                            #line 10323 "PrintCLike.cpp"
  append(L" = 0; ");
                                                            #line 5845 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 10327 "PrintCLike.cpp"
  append(L"b");
                                                            #line 5846 "PrintCLike.cpp.template"
                                                                print(format.toString<wchar_t>(k));
                                                            #line 10331 "PrintCLike.cpp"
  append(L" = 0; ");
                                                            #line 5847 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 10335 "PrintCLike.cpp"
  append(L"e");
                                                            #line 5848 "PrintCLike.cpp.template"
                                                                print(format.toString<wchar_t>(k));
                                                            #line 10339 "PrintCLike.cpp"
  append(L" = 0");
                                                            #line 5849 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                              }
                                                            #line 10344 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5852 "PrintCLike.cpp.template"
                                                              print(thiz());
                                                            #line 10349 "PrintCLike.cpp"
  append(L"end = e");
                                                            #line 5853 "PrintCLike.cpp.template"
                                                              print(semicolon());
                                                              if (hasBacktracking)
                                                              {
                                                            #line 10355 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5857 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 10360 "PrintCLike.cpp"
  append(L"ex = -1");
                                                            #line 5858 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                if (memoization)
                                                                {
                                                                  if (isJavascript() || isTypescript())
                                                                  {
                                                            #line 10368 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5864 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 10373 "PrintCLike.cpp"
  append(L"memo = {};");
                                                            #line 5865 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isCSharp())
                                                                  {
                                                            #line 10379 "PrintCLike.cpp"
  append(L"\n");
  append(L"  memo.Clear();");
                                                            #line 5869 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isScala())
                                                                  {
                                                            #line 10386 "PrintCLike.cpp"
  append(L"\n");
  append(L"  memo.clear()");
                                                            #line 5873 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isHaxe())
                                                                  {
                                                            #line 10393 "PrintCLike.cpp"
  append(L"\n");
  append(L"  memo = new Map();");
                                                            #line 5877 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isGo())
                                                                  {
                                                            #line 10400 "PrintCLike.cpp"
  append(L"\n");
  append(L"  this.memo = make(map[int]int)");
                                                            #line 5881 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isPython())
                                                                  {
                                                            #line 10407 "PrintCLike.cpp"
  append(L"\n");
  append(L"  self.memo = {}");
                                                            #line 5885 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 10414 "PrintCLike.cpp"
  append(L"\n");
  append(L"  memo.clear();");
                                                            #line 5889 "PrintCLike.cpp.template"
                                                                  }
                                                                }
                                                                if (grammar->noThrow)
                                                                {
                                                            #line 10422 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5894 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 10427 "PrintCLike.cpp"
  append(L"viable = ");
                                                            #line 5895 "PrintCLike.cpp.template"
                                                                  if (isPython())
                                                                  {
                                                            #line 10432 "PrintCLike.cpp"
  append(L"T");
                                                            #line 5897 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 10438 "PrintCLike.cpp"
  append(L"t");
                                                            #line 5900 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 10442 "PrintCLike.cpp"
  append(L"rue");
                                                            #line 5901 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                              }
                                                              if (tree && ! useGlr)
                                                              {
                                                            #line 10450 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5907 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 10455 "PrintCLike.cpp"
  append(L"eventHandler");
                                                            #line 5908 "PrintCLike.cpp.template"
                                                                if (isTypescript() && isLrParser) print(L"!");
                                                                print(arrow());
                                                                if (isGo())
                                                                {
                                                            #line 10462 "PrintCLike.cpp"
  append(L"R");
                                                            #line 5912 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 10468 "PrintCLike.cpp"
  append(L"r");
                                                            #line 5915 "PrintCLike.cpp.template"
                                                                }
                                                            #line 10472 "PrintCLike.cpp"
  append(L"eset(");
                                                            #line 5916 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 10476 "PrintCLike.cpp"
  append(L"input)");
                                                            #line 5917 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                              }
                                                              if (useGlr)
                                                              {
                                                            #line 10483 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5922 "PrintCLike.cpp.template"
                                                                if (isCSharp() || isCpp() || isHaxe() || isScala() || isTypescript() || isGo())
                                                                {
                                                                  print(thiz());
                                                            #line 10490 "PrintCLike.cpp"
  append(L"parser");
                                                            #line 5925 "PrintCLike.cpp.template"
                                                                  print(arrow());
                                                                }
                                                            #line 10495 "PrintCLike.cpp"
  append(L"maxId = 0");
                                                            #line 5927 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 10499 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5929 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 10504 "PrintCLike.cpp"
  append(L"id = ");
                                                            #line 5930 "PrintCLike.cpp.template"
                                                                if (isCSharp() || isCpp() || isHaxe() || isScala() || isTypescript() || isGo())
                                                                {
                                                                  print(thiz());
                                                            #line 10510 "PrintCLike.cpp"
  append(L"parser");
                                                            #line 5933 "PrintCLike.cpp.template"
                                                                  print(arrow());
                                                                }
                                                            #line 10515 "PrintCLike.cpp"
  append(L"maxId");
                                                            #line 5935 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                              }
                                                              print(rightBrace());
                                                              if (isJavascript() && useGlr)
                                                              {
                                                            #line 10523 "PrintCLike.cpp"
  append(L";");
                                                            #line 5940 "PrintCLike.cpp.template"
                                                              }
                                                            #line 10527 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5942 "PrintCLike.cpp.template"
                                                              if (useGlr || isJavascript() || isTypescript() || isHaxe() || isGo() || isPython())
                                                              {
                                                              }
                                                              else
                                                              {
                                                                openMethod(voidType(), L"", L"reset", L"");
                                                                print(leftBrace());
                                                            #line 10537 "PrintCLike.cpp"
  append(L"\n");
  append(L"  reset(0, 0, 0)");
                                                            #line 5950 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                print(rightBrace());
                                                            #line 10543 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5953 "PrintCLike.cpp.template"
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
                                                            #line 10571 "PrintCLike.cpp"
  append(L"\n");
  append(L"if ");
                                                            #line 5979 "PrintCLike.cpp.template"
                                                                    print(ifLeftParen());
                                                            #line 10576 "PrintCLike.cpp"
  append(L"(");
                                                            #line 5980 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                                    print(token());
                                                            #line 10581 "PrintCLike.cpp"
  append(L" == ");
                                                            #line 5982 "PrintCLike.cpp.template"
                                                                    print(format.toString<wchar_t>(grammar->externalTokenCode[plusplus]));
                                                                    if (isPython())
                                                                    {
                                                            #line 10587 "PrintCLike.cpp"
  append(L" or ");
                                                            #line 5985 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 10593 "PrintCLike.cpp"
  append(L" || ");
                                                            #line 5988 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(thiz());
                                                                    print(token());
                                                            #line 10599 "PrintCLike.cpp"
  append(L" == ");
                                                            #line 5991 "PrintCLike.cpp.template"
                                                                    print(format.toString<wchar_t>(grammar->externalTokenCode[minusminus]));
                                                            #line 10603 "PrintCLike.cpp"
  append(L")");
                                                            #line 5992 "PrintCLike.cpp.template"
                                                                    if (isPython())
                                                                    {
                                                            #line 10608 "PrintCLike.cpp"
  append(L" and ");
                                                            #line 5994 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 10614 "PrintCLike.cpp"
  append(L" && ");
                                                            #line 5997 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(thiz());
                                                            #line 10619 "PrintCLike.cpp"
  append(L"followsLineTerminator");
                                                            #line 5999 "PrintCLike.cpp.template"
                                                                    if (! isScala())
                                                                    {
                                                            #line 10624 "PrintCLike.cpp"
  append(L"()");
                                                            #line 6001 "PrintCLike.cpp.template"
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
                                                            #line 10638 "PrintCLike.cpp"
  append(L"\n");
  append(L"if ");
                                                            #line 6013 "PrintCLike.cpp.template"
                                                                    print(ifLeftParen());
                                                                    print(thiz());
                                                                    print(token());
                                                            #line 10645 "PrintCLike.cpp"
  append(L" != ");
                                                            #line 6016 "PrintCLike.cpp.template"
                                                                    print(format.toString<wchar_t>(grammar->externalTokenCode[semicolonToken]));
                                                                    if (isPython())
                                                                    {
                                                            #line 10651 "PrintCLike.cpp"
  append(L" and ");
                                                            #line 6019 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 10657 "PrintCLike.cpp"
  append(L" && ");
                                                            #line 6022 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(thiz());
                                                                    print(token());
                                                            #line 10663 "PrintCLike.cpp"
  append(L" >= 0");
                                                            #line 6025 "PrintCLike.cpp.template"
                                                                    if (isPython())
                                                                    {
                                                            #line 10668 "PrintCLike.cpp"
  append(L" and ");
                                                            #line 6027 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 10674 "PrintCLike.cpp"
  append(L" && ");
                                                            #line 6030 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(thiz());
                                                            #line 10679 "PrintCLike.cpp"
  append(L"followsLineTerminator");
                                                            #line 6032 "PrintCLike.cpp.template"
                                                                    if (! isScala())
                                                                    {
                                                            #line 10684 "PrintCLike.cpp"
  append(L"()");
                                                            #line 6034 "PrintCLike.cpp.template"
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
                                                            #line 10699 "PrintCLike.cpp"
  append(L"\n");
  append(L"if ");
                                                            #line 6047 "PrintCLike.cpp.template"
                                                                    print(isPython() ? L"(" : ifLeftParen());
                                                                    print(thiz());
                                                                    print(token());
                                                            #line 10706 "PrintCLike.cpp"
  append(L" == ");
                                                            #line 6050 "PrintCLike.cpp.template"
                                                                    print(format.toString<wchar_t>(grammar->externalTokenCode[rbrace]));
                                                                    if (isPython())
                                                                    {
                                                            #line 10712 "PrintCLike.cpp"
  append(L" or");
                                                            #line 6053 "PrintCLike.cpp.template"
                                                                    }
                                                                    else if (isGo())
                                                                    {
                                                            #line 10718 "PrintCLike.cpp"
  append(L" ||");
                                                            #line 6056 "PrintCLike.cpp.template"
                                                                    }
                                                                    printCodeSequenceAnnotation(grammar->tokenSequence(rbrace));
                                                                    if (isGo() || isPython())
                                                                    {
                                                            #line 10725 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 6061 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 10732 "PrintCLike.cpp"
  append(L"\n");
  append(L" || ");
                                                            #line 6065 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(thiz());
                                                                    print(token());
                                                            #line 10739 "PrintCLike.cpp"
  append(L" == ");
                                                            #line 6068 "PrintCLike.cpp.template"
                                                                    print(format.toString<wchar_t>(grammar->externalTokenCode[eof]));
                                                                    if (isPython())
                                                                    {
                                                            #line 10745 "PrintCLike.cpp"
  append(L" or");
                                                            #line 6071 "PrintCLike.cpp.template"
                                                                    }
                                                                    else if (isGo())
                                                                    {
                                                            #line 10751 "PrintCLike.cpp"
  append(L" ||");
                                                            #line 6074 "PrintCLike.cpp.template"
                                                                    }
                                                                    printCodeSequenceAnnotation(grammar->tokenSequence(eof));
                                                                    if (isGo() || isPython())
                                                                    {
                                                            #line 10758 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 6079 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 10765 "PrintCLike.cpp"
  append(L"\n");
  append(L" || ");
                                                            #line 6083 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(thiz());
                                                                    print(token());
                                                            #line 10772 "PrintCLike.cpp"
  append(L" != ");
                                                            #line 6086 "PrintCLike.cpp.template"
                                                                    print(format.toString<wchar_t>(grammar->externalTokenCode[semicolonToken]));
                                                                    if (isPython())
                                                                    {
                                                            #line 10778 "PrintCLike.cpp"
  append(L" and ");
                                                            #line 6089 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 10784 "PrintCLike.cpp"
  append(L" && ");
                                                            #line 6092 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(thiz());
                                                                    print(token());
                                                            #line 10790 "PrintCLike.cpp"
  append(L" >= 0");
                                                            #line 6095 "PrintCLike.cpp.template"
                                                                    if (isPython())
                                                                    {
                                                            #line 10795 "PrintCLike.cpp"
  append(L" and ");
                                                            #line 6097 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 10801 "PrintCLike.cpp"
  append(L" && ");
                                                            #line 6100 "PrintCLike.cpp.template"
                                                                    }
                                                                    if (afterRbrace)
                                                                    {
                                                            #line 10807 "PrintCLike.cpp"
  append(L"(");
                                                            #line 6103 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(thiz());
                                                            #line 10812 "PrintCLike.cpp"
  append(L"followsLineTerminator");
                                                            #line 6105 "PrintCLike.cpp.template"
                                                                    if (! isScala())
                                                                    {
                                                            #line 10817 "PrintCLike.cpp"
  append(L"()");
                                                            #line 6107 "PrintCLike.cpp.template"
                                                                    }
                                                                    if (afterRbrace)
                                                                    {
                                                                      if (isPython())
                                                                      {
                                                            #line 10825 "PrintCLike.cpp"
  append(L" || ");
                                                            #line 6112 "PrintCLike.cpp.template"
                                                                      }
                                                                      else
                                                                      {
                                                            #line 10831 "PrintCLike.cpp"
  append(L" or ");
                                                            #line 6115 "PrintCLike.cpp.template"
                                                                      }
                                                                      if (isCpp() || isCSharp() || isPython() || (isJava() && codepoints))
                                                                      {
                                                                        print(thiz());
                                                            #line 10838 "PrintCLike.cpp"
  append(L"input[");
                                                            #line 6119 "PrintCLike.cpp.template"
                                                                        print(thiz());
                                                            #line 10842 "PrintCLike.cpp"
  append(L"b0]");
                                                            #line 6120 "PrintCLike.cpp.template"
                                                                      }
                                                                      else
                                                                      {
                                                                        print(thiz());
                                                            #line 10849 "PrintCLike.cpp"
  append(L"input.char");
                                                            #line 6124 "PrintCLike.cpp.template"
                                                                        if (isTypescript() || isJavascript() || isHaxe())
                                                                        {
                                                            #line 10854 "PrintCLike.cpp"
  append(L"Code");
                                                            #line 6126 "PrintCLike.cpp.template"
                                                                        }
                                                            #line 10858 "PrintCLike.cpp"
  append(L"At(");
                                                            #line 6127 "PrintCLike.cpp.template"
                                                                        print(thiz());
                                                            #line 10862 "PrintCLike.cpp"
  append(L"b0)");
                                                            #line 6129 "PrintCLike.cpp.template"
                                                                      }
                                                            #line 10866 "PrintCLike.cpp"
  append(L" == 0x7D)");
                                                            #line 6130 "PrintCLike.cpp.template"
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
                                                            #line 10879 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 6141 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 10884 "PrintCLike.cpp"
  append(L"l1 = ");
                                                            #line 6142 "PrintCLike.cpp.template"
                                                                print(format.toString<wchar_t>(grammar->externalTokenCode[semicolonToken]));
                                                                print(semicolon());
                                                            #line 10889 "PrintCLike.cpp"
  append(L" ");
                                                            #line 6144 "PrintCLike.cpp.template"
                                                                printCodeSequenceAnnotation(grammar->tokenSequence(semicolonToken));
                                                            #line 10893 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 6146 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 10898 "PrintCLike.cpp"
  append(L"e1 = ");
                                                            #line 6147 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 10902 "PrintCLike.cpp"
  append(L"b1");
                                                            #line 6148 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 10906 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 6150 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 10911 "PrintCLike.cpp"
  append(L"end = ");
                                                            #line 6151 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 10915 "PrintCLike.cpp"
  append(L"e1");
                                                            #line 6152 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                print(rightBrace());
                                                              }
                                                            }

// End
