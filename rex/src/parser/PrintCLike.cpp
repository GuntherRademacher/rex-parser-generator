// This file was generated on Fri Oct 30, 2026 09:32 (UTC+01) by REx v6.3-SNAPSHOT which is Copyright (c) 1979-2026 by Gunther Rademacher <grd@gmx.net>
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
                                                                if (useGlr)
                                                                {
                                                            #line 4974 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3172 "PrintCLike.cpp.template"
                                                                  print(intVar());
                                                            #line 4978 "PrintCLike.cpp"
  append(L"pos");
                                                            #line 3173 "PrintCLike.cpp.template"
                                                                  print(assign());
                                                            #line 4982 "PrintCLike.cpp"
  append(L"-1");
                                                            #line 3174 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                                if (isPython())
                                                                {
                                                            #line 4989 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3179 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 4993 "PrintCLike.cpp"
  append(L"action &= ");
                                                            #line 3180 "PrintCLike.cpp.template"
                                                                  print(format.toString<wchar_t>((int) LrStates::actionMask));
                                                                }
                                                                else
                                                                {
                                                            #line 5000 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3185 "PrintCLike.cpp.template"
                                                                  if (! isScala())
                                                                  {
                                                            #line 5005 "PrintCLike.cpp"
  append(L"switch ");
                                                            #line 3187 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(ifLeftParen());
                                                                  if (useGlr) print(thiz());
                                                            #line 5011 "PrintCLike.cpp"
  append(L"action & ");
                                                            #line 3190 "PrintCLike.cpp.template"
                                                                  print(format.toString<wchar_t>((int) LrStates::actionMask));
                                                                  print(ifRightParen());
                                                                  if (isScala())
                                                                  {
                                                            #line 5018 "PrintCLike.cpp"
  append(L" match");
                                                            #line 3194 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(leftBrace());
                                                                }
                                                                if (isPython())
                                                                {
                                                            #line 5026 "PrintCLike.cpp"
  append(L"\n");
  append(L"if ");
                                                            #line 3200 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 5031 "PrintCLike.cpp"
  append(L"action == ");
                                                            #line 3201 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 5037 "PrintCLike.cpp"
  append(L"\n");
  append(L"case ");
                                                            #line 3205 "PrintCLike.cpp.template"
                                                                }
                                                                print(format.toString<wchar_t>((int) LrStates::SHIFT));
                                                                print(caseIntroducer());
                                                            #line 5044 "PrintCLike.cpp"
  append(L" ");
                                                            #line 3208 "PrintCLike.cpp.template"
                                                                print(inlineCommentIntroducer());
                                                            #line 5048 "PrintCLike.cpp"
  append(L"SHIFT\n");
  append(L"  shift = argument");
                                                            #line 3210 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                if (! isHaxe() && ! isScala() && ! isGo() && ! isPython())
                                                                {
                                                            #line 5055 "PrintCLike.cpp"
  append(L"\n");
  append(L"  break");
                                                            #line 3214 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                            #line 5061 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3217 "PrintCLike.cpp.template"
                                                                if (isPython())
                                                                {
                                                            #line 5066 "PrintCLike.cpp"
  append(L"\n");
  append(L"elif ");
                                                            #line 3220 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 5071 "PrintCLike.cpp"
  append(L"action == ");
                                                            #line 3221 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 5077 "PrintCLike.cpp"
  append(L"\n");
  append(L"case ");
                                                            #line 3225 "PrintCLike.cpp.template"
                                                                }
                                                                print(format.toString<wchar_t>((int) LrStates::REDUCE));
                                                                print(caseIntroducer());
                                                            #line 5084 "PrintCLike.cpp"
  append(L" ");
                                                            #line 3228 "PrintCLike.cpp.template"
                                                                print(inlineCommentIntroducer());
                                                            #line 5088 "PrintCLike.cpp"
  append(L"REDUCE\n");
  append(L"  reduce = argument");
                                                            #line 3230 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 5093 "PrintCLike.cpp"
  append(L"\n");
  append(L"  symbols = lookback");
                                                            #line 3232 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                if (! isHaxe() && ! isScala() && ! isGo() && ! isPython())
                                                                {
                                                            #line 5100 "PrintCLike.cpp"
  append(L"\n");
  append(L"  break");
                                                            #line 3236 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                                if (grammar->states->hasLookback)
                                                                {
                                                            #line 5108 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3241 "PrintCLike.cpp.template"
                                                                  if (isPython())
                                                                  {
                                                            #line 5113 "PrintCLike.cpp"
  append(L"\n");
  append(L"elif ");
                                                            #line 3244 "PrintCLike.cpp.template"
                                                                    if (useGlr) print(thiz());
                                                            #line 5118 "PrintCLike.cpp"
  append(L"action == ");
                                                            #line 3245 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 5124 "PrintCLike.cpp"
  append(L"\n");
  append(L"case ");
                                                            #line 3249 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(format.toString<wchar_t>((int) LrStates::REDUCE_LOOKBACK));
                                                                  print(caseIntroducer());
                                                            #line 5131 "PrintCLike.cpp"
  append(L" ");
                                                            #line 3252 "PrintCLike.cpp.template"
                                                                  print(inlineCommentIntroducer());
                                                            #line 5135 "PrintCLike.cpp"
  append(L"REDUCE+LOOKBACK\n");
  append(L"  reduce = argument");
                                                            #line 3254 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                            #line 5140 "PrintCLike.cpp"
  append(L"\n");
  append(L"  symbols = ");
                                                            #line 3256 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                                  if (useGlr)
                                                                  {
                                                            #line 5147 "PrintCLike.cpp"
  append(L"stack");
                                                            #line 3259 "PrintCLike.cpp.template"
                                                                    if (isTypescript()) print(L"!");
                                                                    print(arrow());
                                                                  }
                                                                  if (isGo() && useGlr)
                                                                  {
                                                            #line 5155 "PrintCLike.cpp"
  append(L"Count");
                                                            #line 3264 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 5161 "PrintCLike.cpp"
  append(L"count");
                                                            #line 3267 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 5165 "PrintCLike.cpp"
  append(L"(lookback)");
                                                            #line 3268 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                  if (! isHaxe() && ! isScala() && ! isGo() && ! isPython())
                                                                  {
                                                            #line 5171 "PrintCLike.cpp"
  append(L"\n");
  append(L"  break");
                                                            #line 3272 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                  }
                                                                }
                                                            #line 5178 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3276 "PrintCLike.cpp.template"
                                                                if (isPython())
                                                                {
                                                            #line 5183 "PrintCLike.cpp"
  append(L"\n");
  append(L"elif ");
                                                            #line 3279 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 5188 "PrintCLike.cpp"
  append(L"action == ");
                                                            #line 3280 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 5194 "PrintCLike.cpp"
  append(L"\n");
  append(L"case ");
                                                            #line 3284 "PrintCLike.cpp.template"
                                                                }
                                                                print(format.toString<wchar_t>((int) LrStates::SHIFT_REDUCE));
                                                                print(caseIntroducer());
                                                            #line 5201 "PrintCLike.cpp"
  append(L" ");
                                                            #line 3287 "PrintCLike.cpp.template"
                                                                print(inlineCommentIntroducer());
                                                            #line 5205 "PrintCLike.cpp"
  append(L"SHIFT+REDUCE\n");
  append(L"  shift = ");
                                                            #line 3289 "PrintCLike.cpp.template"
                                                                if (useGlr) print(thiz());
                                                            #line 5210 "PrintCLike.cpp"
  append(L"state");
                                                            #line 3290 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 5214 "PrintCLike.cpp"
  append(L"\n");
  append(L"  reduce = argument");
                                                            #line 3292 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 5219 "PrintCLike.cpp"
  append(L"\n");
  append(L"  symbols = lookback + 1");
                                                            #line 3294 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                if (! isHaxe() && ! isScala() && ! isGo() && ! isPython())
                                                                {
                                                            #line 5226 "PrintCLike.cpp"
  append(L"\n");
  append(L"  break");
                                                            #line 3298 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                                if (grammar->states->hasLookback)
                                                                {
                                                            #line 5234 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3303 "PrintCLike.cpp.template"
                                                                  if (isPython())
                                                                  {
                                                            #line 5239 "PrintCLike.cpp"
  append(L"\n");
  append(L"elif ");
                                                            #line 3306 "PrintCLike.cpp.template"
                                                                    if (useGlr) print(thiz());
                                                            #line 5244 "PrintCLike.cpp"
  append(L"action == ");
                                                            #line 3307 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 5250 "PrintCLike.cpp"
  append(L"\n");
  append(L"case ");
                                                            #line 3311 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(format.toString<wchar_t>((int) LrStates::SHIFT_REDUCE_LOOKBACK));
                                                                  print(caseIntroducer());
                                                            #line 5257 "PrintCLike.cpp"
  append(L" ");
                                                            #line 3314 "PrintCLike.cpp.template"
                                                                  print(inlineCommentIntroducer());
                                                            #line 5261 "PrintCLike.cpp"
  append(L"SHIFT+REDUCE+LOOKBACK\n");
  append(L"  shift = ");
                                                            #line 3316 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 5266 "PrintCLike.cpp"
  append(L"state");
                                                            #line 3317 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                            #line 5270 "PrintCLike.cpp"
  append(L"\n");
  append(L"  reduce = argument");
                                                            #line 3319 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                            #line 5275 "PrintCLike.cpp"
  append(L"\n");
  append(L"  symbols = ");
                                                            #line 3321 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                                  if (useGlr)
                                                                  {
                                                            #line 5282 "PrintCLike.cpp"
  append(L"stack");
                                                            #line 3324 "PrintCLike.cpp.template"
                                                                    if (isTypescript()) print(L"!");
                                                                    print(arrow());
                                                                  }
                                                                  if (isGo() && useGlr)
                                                                  {
                                                            #line 5290 "PrintCLike.cpp"
  append(L"Count");
                                                            #line 3329 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 5296 "PrintCLike.cpp"
  append(L"count");
                                                            #line 3332 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 5300 "PrintCLike.cpp"
  append(L"(lookback) + 1");
                                                            #line 3333 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                  if (! isHaxe() && ! isScala() && ! isGo() && ! isPython())
                                                                  {
                                                            #line 5306 "PrintCLike.cpp"
  append(L"\n");
  append(L"  break");
                                                            #line 3337 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                  }
                                                                }
                                                            #line 5313 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3341 "PrintCLike.cpp.template"
                                                                if (isPython())
                                                                {
                                                            #line 5318 "PrintCLike.cpp"
  append(L"\n");
  append(L"elif ");
                                                            #line 3344 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 5323 "PrintCLike.cpp"
  append(L"action == ");
                                                            #line 3345 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 5329 "PrintCLike.cpp"
  append(L"\n");
  append(L"case ");
                                                            #line 3349 "PrintCLike.cpp.template"
                                                                }
                                                                print(format.toString<wchar_t>((int) LrStates::SHIFT_ACCEPT));
                                                                print(caseIntroducer());
                                                            #line 5336 "PrintCLike.cpp"
  append(L" ");
                                                            #line 3352 "PrintCLike.cpp.template"
                                                                print(inlineCommentIntroducer());
                                                            #line 5340 "PrintCLike.cpp"
  append(L"ACCEPT");
                                                            #line 3353 "PrintCLike.cpp.template"
                                                                if (trace)
                                                                {
                                                                  if (isCpp())
                                                                  {
                                                            #line 5347 "PrintCLike.cpp"
  append(L"\n");
  append(L"  fprintf(stderr, ");
                                                            #line 3358 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 5354 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3362 "PrintCLike.cpp.template"
                                                                    print(writeTrace());
                                                                  }
                                                            #line 5360 "PrintCLike.cpp"
  append(L"\"accept\\\"/>");
                                                            #line 3364 "PrintCLike.cpp.template"
                                                                  if (! isHaxe())
                                                                  {
                                                            #line 5365 "PrintCLike.cpp"
  append(L"\\n");
                                                            #line 3366 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 5369 "PrintCLike.cpp"
  append(L"\"");
                                                            #line 3367 "PrintCLike.cpp.template"
                                                                  print(endWriteTrace());
                                                                  print(semicolon());
                                                                  if (isHaxe())
                                                                  {
                                                            #line 5376 "PrintCLike.cpp"
  append(L"\n");
  append(L"  trace(traceLine);");
                                                            #line 3372 "PrintCLike.cpp.template"
                                                                  }
                                                                }
                                                                if (useGlr)
                                                                {
                                                            #line 5384 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3377 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 5389 "PrintCLike.cpp"
  append(L"accepted = ");
                                                            #line 3378 "PrintCLike.cpp.template"
                                                                  if (isPython())
                                                                  {
                                                            #line 5394 "PrintCLike.cpp"
  append(L"T");
                                                            #line 3380 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 5400 "PrintCLike.cpp"
  append(L"t");
                                                            #line 3383 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 5404 "PrintCLike.cpp"
  append(L"rue");
                                                            #line 3384 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                            #line 5408 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3386 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 5413 "PrintCLike.cpp"
  append(L"action = 0");
                                                            #line 3387 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                            #line 5417 "PrintCLike.cpp"
  append(L"\n");
  append(L"  return ");
                                                            #line 3389 "PrintCLike.cpp.template"
                                                                  if (isHaxe() || isTypescript() || isPython()) print(staticPrefix());
                                                            #line 5422 "PrintCLike.cpp"
  append(L"ACCEPTED");
                                                            #line 3390 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                                else
                                                                {
                                                            #line 5429 "PrintCLike.cpp"
  append(L"\n");
  append(L"  return");
                                                            #line 3395 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }

                                                                if (useGlr)
                                                                {
                                                            #line 5438 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3401 "PrintCLike.cpp.template"
                                                                  if (isPython())
                                                                  {
                                                            #line 5443 "PrintCLike.cpp"
  append(L"\n");
  append(L"elif ");
                                                            #line 3404 "PrintCLike.cpp.template"
                                                                    if (useGlr) print(thiz());
                                                            #line 5448 "PrintCLike.cpp"
  append(L"action == ");
                                                            #line 3405 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 5454 "PrintCLike.cpp"
  append(L"\n");
  append(L"case ");
                                                            #line 3409 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(format.toString<wchar_t>((int) LrStates::FORK));
                                                                  print(caseIntroducer());
                                                            #line 5461 "PrintCLike.cpp"
  append(L" ");
                                                            #line 3412 "PrintCLike.cpp.template"
                                                                  print(inlineCommentIntroducer());
                                                            #line 5465 "PrintCLike.cpp"
  append(L"FORK");
                                                            #line 3413 "PrintCLike.cpp.template"
                                                                  if (trace)
                                                                  {
                                                                    if (isCpp())
                                                                    {
                                                            #line 5472 "PrintCLike.cpp"
  append(L"\n");
  append(L"  fprintf(stderr, \"fork\\\"/>\\n\");");
                                                            #line 3418 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 5479 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3422 "PrintCLike.cpp.template"
                                                                      print(writeTrace());
                                                            #line 5484 "PrintCLike.cpp"
  append(L"\"fork\\\"/>");
                                                            #line 3423 "PrintCLike.cpp.template"
                                                                      if (! isHaxe())
                                                                      {
                                                            #line 5489 "PrintCLike.cpp"
  append(L"\\n\"");
                                                            #line 3425 "PrintCLike.cpp.template"
                                                                        print(endWriteTrace());
                                                                        print(semicolon());
                                                                      }
                                                                      else
                                                                      {
                                                            #line 5497 "PrintCLike.cpp"
  append(L"\";\n");
  append(L"  trace(traceLine);");
                                                            #line 3431 "PrintCLike.cpp.template"
                                                                      }
                                                                    }
                                                                  }
                                                                  if (isGo())
                                                                  {
                                                            #line 5506 "PrintCLike.cpp"
  append(L"\n");
  append(L"  heap.Push(this.threads, new(ParsingThread).copy(this, appendix[argument]))");
                                                            #line 3438 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isPython())
                                                                  {
                                                            #line 5513 "PrintCLike.cpp"
  append(L"\n");
  append(L"  forked = ");
                                                            #line 3442 "PrintCLike.cpp.template"
                                                                    print(staticPrefix());
                                                            #line 5518 "PrintCLike.cpp"
  append(L"ParsingThread().copy(self, ");
                                                            #line 3443 "PrintCLike.cpp.template"
                                                                    print(staticPrefix());
                                                            #line 5522 "PrintCLike.cpp"
  append(L"APPENDIX[argument])\n");
  append(L"  heapq.heappush(self.threads, (False, forked.e0, forked.id, forked))");
                                                            #line 3446 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 5529 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3450 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 5534 "PrintCLike.cpp"
  append(L"threads");
                                                            #line 3451 "PrintCLike.cpp.template"
                                                                    if (isCpp())
                                                                    {
                                                            #line 5539 "PrintCLike.cpp"
  append(L"->push(");
                                                            #line 3453 "PrintCLike.cpp.template"
                                                                    }
                                                                    else if (isScala())
                                                                    {
                                                            #line 5545 "PrintCLike.cpp"
  append(L" += ");
                                                            #line 3456 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 5551 "PrintCLike.cpp"
  append(L".offer(");
                                                            #line 3459 "PrintCLike.cpp.template"
                                                                    }
                                                                    if (isCpp() || isScala()) print(L"(");
                                                            #line 5556 "PrintCLike.cpp"
  append(L"new ParsingThread");
                                                            #line 3461 "PrintCLike.cpp.template"
                                                                    if (! isScala()) print(L"()");
                                                                    if (isCpp() || isScala()) print(L")");
                                                                    print(arrow());
                                                            #line 5562 "PrintCLike.cpp"
  append(L"copy(this");
                                                            #line 3464 "PrintCLike.cpp.template"
                                                                    if (isJavascript())
                                                                    {
                                                            #line 5567 "PrintCLike.cpp"
  append(L"Thread");
                                                            #line 3466 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 5571 "PrintCLike.cpp"
  append(L", ");
                                                            #line 3467 "PrintCLike.cpp.template"
                                                                    print(staticPrefix());
                                                            #line 5575 "PrintCLike.cpp"
  append(L"APPENDIX");
                                                            #line 3468 "PrintCLike.cpp.template"
                                                                    print(leftbracket());
                                                            #line 5579 "PrintCLike.cpp"
  append(L"argument");
                                                            #line 3469 "PrintCLike.cpp.template"
                                                                    print(rightbracket());
                                                            #line 5583 "PrintCLike.cpp"
  append(L")");
                                                            #line 3470 "PrintCLike.cpp.template"
                                                                    if (! isScala()) print(L")");
                                                                    print(semicolon());
                                                                  }
                                                            #line 5589 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3474 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 5594 "PrintCLike.cpp"
  append(L"action = ");
                                                            #line 3475 "PrintCLike.cpp.template"
                                                                  print(staticPrefix());
                                                                  if (isGo())
                                                                  {
                                                            #line 5600 "PrintCLike.cpp"
  append(L"appendix");
                                                            #line 3478 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 5606 "PrintCLike.cpp"
  append(L"APPENDIX");
                                                            #line 3481 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(leftbracket());
                                                            #line 5611 "PrintCLike.cpp"
  append(L"argument + 1");
                                                            #line 3483 "PrintCLike.cpp.template"
                                                                  print(rightbracket());
                                                                  print(semicolon());
                                                            #line 5616 "PrintCLike.cpp"
  append(L"\n");
  append(L"  return ");
                                                            #line 3486 "PrintCLike.cpp.template"
                                                                  if (isHaxe() || isTypescript() || isPython()) print(staticPrefix());
                                                            #line 5621 "PrintCLike.cpp"
  append(L"PARSING");
                                                            #line 3487 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                            #line 5626 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3490 "PrintCLike.cpp.template"
                                                                if (isPython())
                                                                {
                                                            #line 5631 "PrintCLike.cpp"
  append(L"\n");
  append(L"else");
                                                            #line 3493 "PrintCLike.cpp.template"
                                                                }
                                                                else if (isScala())
                                                                {
                                                            #line 5638 "PrintCLike.cpp"
  append(L"\n");
  append(L"case _");
                                                            #line 3497 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 5645 "PrintCLike.cpp"
  append(L"\n");
  append(L"default");
                                                            #line 3501 "PrintCLike.cpp.template"
                                                                }
                                                                print(caseIntroducer());
                                                            #line 5651 "PrintCLike.cpp"
  append(L" ");
                                                            #line 3503 "PrintCLike.cpp.template"
                                                                print(inlineCommentIntroducer());
                                                            #line 5655 "PrintCLike.cpp"
  append(L"ERROR");
                                                            #line 3504 "PrintCLike.cpp.template"
                                                                if (useGlr)
                                                                {
                                                                  if (trace)
                                                                  {
                                                                    if (isCpp())
                                                                    {
                                                            #line 5664 "PrintCLike.cpp"
  append(L"\n");
  append(L"  fprintf(stderr, \"fail\\\"/>\\n\");");
                                                            #line 3511 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 5671 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3515 "PrintCLike.cpp.template"
                                                                      print(writeTrace());
                                                            #line 5676 "PrintCLike.cpp"
  append(L"\"fail\\\"/>");
                                                            #line 3516 "PrintCLike.cpp.template"
                                                                      if (! isHaxe())
                                                                      {
                                                            #line 5681 "PrintCLike.cpp"
  append(L"\\n\"");
                                                            #line 3518 "PrintCLike.cpp.template"
                                                                        print(endWriteTrace());
                                                                        print(semicolon());
                                                                      }
                                                                      else
                                                                      {
                                                            #line 5689 "PrintCLike.cpp"
  append(L"\";\n");
  append(L"  trace(traceLine);");
                                                            #line 3524 "PrintCLike.cpp.template"
                                                                      }
                                                                    }
                                                                  }
                                                            #line 5696 "PrintCLike.cpp"
  append(L"\n");
  append(L"  return ");
                                                            #line 3528 "PrintCLike.cpp.template"
                                                                  if (isHaxe() || isTypescript() || isPython()) print(staticPrefix());
                                                            #line 5701 "PrintCLike.cpp"
  append(L"ERROR");
                                                            #line 3529 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                                else
                                                                {
                                                            #line 5708 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3534 "PrintCLike.cpp.template"
                                                                  print(beginThrowStmt());
                                                                  print(thiz());
                                                            #line 5714 "PrintCLike.cpp"
  append(L"b1, ");
                                                            #line 3536 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 5718 "PrintCLike.cpp"
  append(L"e1, ");
                                                            #line 3537 "PrintCLike.cpp.template"
                                                                  print(staticPrefix());
                                                                  if (isGo())
                                                                  {
                                                            #line 5724 "PrintCLike.cpp"
  append(L"tokenset");
                                                            #line 3540 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 5730 "PrintCLike.cpp"
  append(L"TOKENSET");
                                                            #line 3543 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(leftbracket());
                                                            #line 5735 "PrintCLike.cpp"
  append(L"state");
                                                            #line 3545 "PrintCLike.cpp.template"
                                                                  print(rightbracket());
                                                            #line 5739 "PrintCLike.cpp"
  append(L" + 1, ");
                                                            #line 3546 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 5743 "PrintCLike.cpp"
  append(L"l1, -1");
                                                            #line 3547 "PrintCLike.cpp.template"
                                                                  print(endThrowStmt());
                                                                  print(semicolon());
                                                                }
                                                                print(rightBrace());
                                                            #line 5750 "PrintCLike.cpp"
  append(L"\n");
  append(L"\n");
  append(L"if ");
                                                            #line 3553 "PrintCLike.cpp.template"
                                                                print(ifLeftParen());
                                                            #line 5756 "PrintCLike.cpp"
  append(L"shift >= 0");
                                                            #line 3554 "PrintCLike.cpp.template"
                                                                print(ifRightParen());
                                                                print(leftBrace());
                                                                if (trace)
                                                                {
                                                                  if (isCpp())
                                                                  {
                                                            #line 5765 "PrintCLike.cpp"
  append(L"\n");
  append(L"  fprintf(stderr, ");
                                                            #line 3561 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 5772 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3565 "PrintCLike.cpp.template"
                                                                    print(writeTrace());
                                                                  }
                                                            #line 5778 "PrintCLike.cpp"
  append(L"\"shift\"");
                                                            #line 3567 "PrintCLike.cpp.template"
                                                                  print(endWriteTrace());
                                                                  print(semicolon());
                                                                }
                                                            #line 5784 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if ");
                                                            #line 3571 "PrintCLike.cpp.template"
                                                                print(ifLeftParen());
                                                            #line 5789 "PrintCLike.cpp"
  append(L"nonterminalId < 0");
                                                            #line 3572 "PrintCLike.cpp.template"
                                                                print(ifRightParen());
                                                                printIndented(1, leftBrace());
                                                                if (resolvesAmbiguity)
                                                                {
                                                            #line 5796 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 3577 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 5801 "PrintCLike.cpp"
  append(L"eventCount");
                                                            #line 3578 "PrintCLike.cpp.template"
                                                                  print(incrementOp());
                                                                  print(semicolon());
                                                                }
                                                                if (tree)
                                                                {
                                                            #line 5809 "PrintCLike.cpp"
  append(L"\n");
  append(L"    if ");
                                                            #line 3584 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                                  if (useGlr) print(thiz());
                                                            #line 5815 "PrintCLike.cpp"
  append(L"eventHandler != ");
                                                            #line 3586 "PrintCLike.cpp.template"
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
                                                            #line 5830 "PrintCLike.cpp"
  append(L"\n");
  append(L"      if ");
                                                            #line 3599 "PrintCLike.cpp.template"
                                                                    print(ifLeftParen());
                                                                    print(thiz());
                                                                    if (isGo())
                                                                    {
                                                            #line 5838 "PrintCLike.cpp"
  append(L"IsUnambiguous");
                                                            #line 3603 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 5844 "PrintCLike.cpp"
  append(L"isUnambiguous");
                                                            #line 3606 "PrintCLike.cpp.template"
                                                                    }
                                                                    if (! isScala()) print(L"()");
                                                                    print(ifRightParen());
                                                                    printIndented(3, leftBrace());
                                                                    increaseIndent();
                                                                  }
                                                            #line 5853 "PrintCLike.cpp"
  append(L"\n");
  append(L"      ");
                                                            #line 3613 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 5858 "PrintCLike.cpp"
  append(L"eventHandler");
                                                            #line 3614 "PrintCLike.cpp.template"
                                                                  if (shiftAmbiguity && isTypescript()) print(L"!");
                                                                  print(arrow());
                                                                  if (isGo())
                                                                  {
                                                            #line 5865 "PrintCLike.cpp"
  append(L"T");
                                                            #line 3618 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 5871 "PrintCLike.cpp"
  append(L"t");
                                                            #line 3621 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 5875 "PrintCLike.cpp"
  append(L"erminal(");
                                                            #line 3622 "PrintCLike.cpp.template"
                                                                  print(staticPrefix());
                                                                  print(isGo() ? L"token" : L"TOKEN");
                                                                  print(leftbracket());
                                                                  print(thiz());
                                                            #line 5882 "PrintCLike.cpp"
  append(L"l1");
                                                            #line 3626 "PrintCLike.cpp.template"
                                                                  print(rightbracket());
                                                            #line 5886 "PrintCLike.cpp"
  append(L", ");
                                                            #line 3627 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 5890 "PrintCLike.cpp"
  append(L"b1, ");
                                                            #line 3628 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 5894 "PrintCLike.cpp"
  append(L"e1)");
                                                            #line 3629 "PrintCLike.cpp.template"
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
                                                            #line 5907 "PrintCLike.cpp"
  append(L"\n");
  append(L"      ");
                                                            #line 3640 "PrintCLike.cpp.template"
                                                                    printIndented(3, elseWithBraces());
                                                            #line 5912 "PrintCLike.cpp"
  append(L"\n");
  append(L"        ");
                                                            #line 3642 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 5917 "PrintCLike.cpp"
  append(L"deferredEvent = ");
                                                            #line 3643 "PrintCLike.cpp.template"
                                                                    if (isGo())
                                                                    {
                                                            #line 5922 "PrintCLike.cpp"
  append(L"&TerminalEvent{&AbstractDeferredEvent{");
                                                            #line 3645 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                                      if (! isPython())
                                                                      {
                                                            #line 5930 "PrintCLike.cpp"
  append(L"new ");
                                                            #line 3650 "PrintCLike.cpp.template"
                                                                      }
                                                                      if (! isHaxe() && ! isTypescript()) print(staticPrefix());
                                                                      if (isJavascript() || isTypescript())
                                                                      {
                                                            #line 5937 "PrintCLike.cpp"
  append(L"DeferredEvent");
                                                            #line 3654 "PrintCLike.cpp.template"
                                                                      }
                                                                      else
                                                                      {
                                                            #line 5943 "PrintCLike.cpp"
  append(L"TerminalEvent");
                                                            #line 3657 "PrintCLike.cpp.template"
                                                                      }
                                                            #line 5947 "PrintCLike.cpp"
  append(L"(");
                                                            #line 3658 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(thiz());
                                                            #line 5952 "PrintCLike.cpp"
  append(L"deferredEvent, ");
                                                            #line 3660 "PrintCLike.cpp.template"
                                                                    print(staticPrefix());
                                                                    print(isGo() ? L"token" : L"TOKEN");
                                                                    print(leftbracket());
                                                                    print(thiz());
                                                            #line 5959 "PrintCLike.cpp"
  append(L"l1");
                                                            #line 3664 "PrintCLike.cpp.template"
                                                                    print(rightbracket());
                                                            #line 5963 "PrintCLike.cpp"
  append(L", ");
                                                            #line 3665 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 5967 "PrintCLike.cpp"
  append(L"b1, ");
                                                            #line 3666 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 5971 "PrintCLike.cpp"
  append(L"e1");
                                                            #line 3667 "PrintCLike.cpp.template"
                                                                    if (isTypescript())
                                                                    {
                                                            #line 5976 "PrintCLike.cpp"
  append(L", -1");
                                                            #line 3670 "PrintCLike.cpp.template"
                                                                    }
                                                                    if (isGo())
                                                                    {
                                                            #line 5982 "PrintCLike.cpp"
  append(L"}}");
                                                            #line 3674 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 5988 "PrintCLike.cpp"
  append(L")");
                                                            #line 3678 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                                    }
                                                                    increaseIndent(3);
                                                                    print(rightBrace());
                                                                    decreaseIndent();
                                                                    print(rightBrace());
                                                                    decreaseIndent(2);
                                                                  }
                                                            #line 5999 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 3687 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 6004 "PrintCLike.cpp"
  append(L"es = ");
                                                            #line 3688 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 6008 "PrintCLike.cpp"
  append(L"e1");
                                                            #line 3689 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                                if (useGlr)
                                                                {
                                                            #line 6015 "PrintCLike.cpp"
  append(L"\n");
  append(L"    pos = ");
                                                            #line 3694 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 6020 "PrintCLike.cpp"
  append(L"b1");
                                                            #line 3695 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                                else
                                                                {
                                                            #line 6027 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 3700 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 6032 "PrintCLike.cpp"
  append(L"push(state, lookback");
                                                            #line 3701 "PrintCLike.cpp.template"
                                                                  if (tree)
                                                                  {
                                                            #line 6037 "PrintCLike.cpp"
  append(L", ");
                                                            #line 3703 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 6041 "PrintCLike.cpp"
  append(L"b1");
                                                            #line 3704 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 6045 "PrintCLike.cpp"
  append(L")");
                                                            #line 3705 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                            #line 6050 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 3708 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 6055 "PrintCLike.cpp"
  append(L"consume(");
                                                            #line 3709 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 6059 "PrintCLike.cpp"
  append(L"l1)");
                                                            #line 3710 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 6063 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3712 "PrintCLike.cpp.template"
                                                                printIndented(1, elseWithBraces());
                                                                if (useGlr)
                                                                {
                                                            #line 6070 "PrintCLike.cpp"
  append(L"\n");
  append(L"    pos = ");
                                                            #line 3716 "PrintCLike.cpp.template"
                                                                  if (tree)
                                                                  {
                                                                    print(thiz());
                                                            #line 6077 "PrintCLike.cpp"
  append(L"bs");
                                                            #line 3719 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 6083 "PrintCLike.cpp"
  append(L"0");
                                                            #line 3722 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(semicolon());
                                                                }
                                                                else
                                                                {
                                                            #line 6091 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 3728 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 6096 "PrintCLike.cpp"
  append(L"push(state, lookback");
                                                            #line 3729 "PrintCLike.cpp.template"
                                                                  if (tree)
                                                                  {
                                                            #line 6101 "PrintCLike.cpp"
  append(L", bs");
                                                            #line 3731 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 6105 "PrintCLike.cpp"
  append(L")");
                                                            #line 3732 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                                increaseIndent();
                                                                print(rightBrace());
                                                                decreaseIndent();
                                                                if (! useGlr)
                                                                {
                                                            #line 6115 "PrintCLike.cpp"
  append(L"\n");
  append(L"  state = shift");
                                                            #line 3740 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                                print(rightBrace());
                                                            #line 6122 "PrintCLike.cpp"
  append(L"\n");
  append(L"\n");
  append(L"if ");
                                                            #line 3745 "PrintCLike.cpp.template"
                                                                print(ifLeftParen());
                                                            #line 6128 "PrintCLike.cpp"
  append(L"reduce < 0");
                                                            #line 3746 "PrintCLike.cpp.template"
                                                                print(ifRightParen());
                                                                print(leftBrace());
                                                                if (trace)
                                                                {
                                                                  if (isCpp())
                                                                  {
                                                            #line 6137 "PrintCLike.cpp"
  append(L"\n");
  append(L"  fprintf(stderr, ");
                                                            #line 3753 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 6144 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3757 "PrintCLike.cpp.template"
                                                                    print(writeTrace());
                                                                  }
                                                            #line 6150 "PrintCLike.cpp"
  append(L"\"\\\"/>");
                                                            #line 3759 "PrintCLike.cpp.template"
                                                                  if (! isHaxe())
                                                                  {
                                                            #line 6155 "PrintCLike.cpp"
  append(L"\\n\"");
                                                            #line 3761 "PrintCLike.cpp.template"
                                                                    print(endWriteTrace());
                                                                    print(semicolon());
                                                                  }
                                                                  else
                                                                  {
                                                            #line 6163 "PrintCLike.cpp"
  append(L"\";\n");
  append(L"  trace(traceLine);");
                                                            #line 3767 "PrintCLike.cpp.template"
                                                                  }
                                                                }
                                                                if (useGlr)
                                                                {
                                                                  printStackAllocation();
                                                                }
                                                            #line 6173 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3774 "PrintCLike.cpp.template"
                                                                if (useGlr) print(thiz());
                                                            #line 6178 "PrintCLike.cpp"
  append(L"action = ");
                                                            #line 3775 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 6182 "PrintCLike.cpp"
  append(L"predict(");
                                                            #line 3776 "PrintCLike.cpp.template"
                                                                if (useGlr) print(thiz());
                                                            #line 6186 "PrintCLike.cpp"
  append(L"state)");
                                                            #line 3777 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                if (useGlr)
                                                                {
                                                                  if (isCpp())
                                                                  {
                                                            #line 6194 "PrintCLike.cpp"
  append(L"\n");
  append(L"  break");
                                                            #line 3783 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                  }
                                                                  else
                                                                  {
                                                            #line 6202 "PrintCLike.cpp"
  append(L"\n");
  append(L"  return ");
                                                            #line 3788 "PrintCLike.cpp.template"
                                                                    if (isHaxe() || isTypescript() || isPython()) print(staticPrefix());
                                                            #line 6207 "PrintCLike.cpp"
  append(L"PARSING");
                                                            #line 3789 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                  }
                                                                }
                                                                else
                                                                {
                                                            #line 6215 "PrintCLike.cpp"
  append(L"\n");
  append(L"  nonterminalId = -1");
                                                            #line 3795 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                            #line 6221 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3798 "PrintCLike.cpp.template"
                                                                print(elseWithBraces());
                                                                if (hasCustomCode)
                                                                {
                                                            #line 6227 "PrintCLike.cpp"
  append(L"\n");
  append(L"  nonterminalId = ");
                                                            #line 3802 "PrintCLike.cpp.template"
                                                                  print(staticPrefix());
                                                                  if (isGo())
                                                                  {
                                                            #line 6234 "PrintCLike.cpp"
  append(L"reduction");
                                                            #line 3805 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 6240 "PrintCLike.cpp"
  append(L"REDUCTION");
                                                            #line 3808 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(leftbracket());
                                                            #line 6245 "PrintCLike.cpp"
  append(L"reduce");
                                                            #line 3810 "PrintCLike.cpp.template"
                                                                  print(rightbracket());
                                                                  print(semicolon());
                                                            #line 6250 "PrintCLike.cpp"
  append(L"\n");
  append(L"  reduce = ");
                                                            #line 3813 "PrintCLike.cpp.template"
                                                                  print(staticPrefix());
                                                                  if (isGo())
                                                                  {
                                                            #line 6257 "PrintCLike.cpp"
  append(L"reduction");
                                                            #line 3816 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 6263 "PrintCLike.cpp"
  append(L"REDUCTION");
                                                            #line 3819 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(leftbracket());
                                                            #line 6268 "PrintCLike.cpp"
  append(L"reduce + 1");
                                                            #line 3821 "PrintCLike.cpp.template"
                                                                  print(rightbracket());
                                                                  print(semicolon());
                                                            #line 6273 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if ");
                                                            #line 3824 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                            #line 6278 "PrintCLike.cpp"
  append(L"reduce >= 0");
                                                            #line 3825 "PrintCLike.cpp.template"
                                                                  print(ifRightParen());
                                                                  increaseIndent();
                                                                  print(leftBrace());
                                                                  if (useGlr)
                                                                  {
                                                            #line 6286 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if ");
                                                            #line 3831 "PrintCLike.cpp.template"
                                                                    print(ifLeftParen());
                                                                    print(thiz());
                                                                    if (isGo())
                                                                    {
                                                            #line 6294 "PrintCLike.cpp"
  append(L"IsUnambiguous");
                                                            #line 3835 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 6300 "PrintCLike.cpp"
  append(L"isUnambiguous");
                                                            #line 3838 "PrintCLike.cpp.template"
                                                                    }
                                                                    if (! isScala()) print(L"()");
                                                                    print(ifRightParen());
                                                                    print(leftBrace());
                                                            #line 6307 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 3843 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                                    print(isGo() && useGlr ? L"E" : L"e");
                                                            #line 6313 "PrintCLike.cpp"
  append(L"xecute(reduce)");
                                                            #line 3845 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 6317 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3847 "PrintCLike.cpp.template"
                                                                    print(elseWithBraces());
                                                            #line 6322 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 3849 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 6327 "PrintCLike.cpp"
  append(L"deferredCode = ");
                                                            #line 3850 "PrintCLike.cpp.template"
                                                                    if (isGo())
                                                                    {
                                                            #line 6332 "PrintCLike.cpp"
  append(L"&DeferredCode{");
                                                            #line 3852 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                                      if (! isPython())
                                                                      {
                                                            #line 6340 "PrintCLike.cpp"
  append(L"new ");
                                                            #line 3857 "PrintCLike.cpp.template"
                                                                      }
                                                                      if (! isHaxe() && ! isTypescript()) print(staticPrefix());
                                                            #line 6345 "PrintCLike.cpp"
  append(L"DeferredCode(");
                                                            #line 3859 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(thiz());
                                                            #line 6350 "PrintCLike.cpp"
  append(L"deferredCode, reduce, ");
                                                            #line 3861 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 6354 "PrintCLike.cpp"
  append(L"b0, ");
                                                            #line 3862 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 6358 "PrintCLike.cpp"
  append(L"e0");
                                                            #line 3864 "PrintCLike.cpp.template"
                                                                    if (isGo())
                                                                    {
                                                            #line 6363 "PrintCLike.cpp"
  append(L"}");
                                                            #line 3867 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 6369 "PrintCLike.cpp"
  append(L")");
                                                            #line 3871 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(semicolon());
                                                                    increaseIndent();
                                                                    print(rightBrace());
                                                                    decreaseIndent();
                                                                  }
                                                                  else
                                                                  {
                                                            #line 6380 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3880 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                                    print(isGo() && useGlr ? L"E" : L"e");
                                                            #line 6386 "PrintCLike.cpp"
  append(L"xecute(reduce)");
                                                            #line 3882 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                  }
                                                                  print(rightBrace());
                                                                  decreaseIndent();
                                                                }
                                                                else
                                                                {
                                                            #line 6396 "PrintCLike.cpp"
  append(L"\n");
  append(L"  nonterminalId = reduce");
                                                            #line 3890 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                                if (resolvesAmbiguity)
                                                                {
                                                            #line 6404 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3895 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 6409 "PrintCLike.cpp"
  append(L"eventCount");
                                                            #line 3896 "PrintCLike.cpp.template"
                                                                  print(incrementOp());
                                                                  print(semicolon());
                                                                }
                                                                if (trace)
                                                                {
                                                            #line 6417 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if ");
                                                            #line 3902 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                            #line 6422 "PrintCLike.cpp"
  append(L"shift >= 0");
                                                            #line 3903 "PrintCLike.cpp.template"
                                                                  print(ifRightParen());
                                                                  printIndented(1, leftBrace());
                                                                  if (isCpp())
                                                                  {
                                                            #line 6429 "PrintCLike.cpp"
  append(L"\n");
  append(L"    fprintf(stderr, ");
                                                            #line 3908 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 6436 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 3912 "PrintCLike.cpp.template"
                                                                    print(writeTrace());
                                                                  }
                                                            #line 6442 "PrintCLike.cpp"
  append(L"\" \"");
                                                            #line 3914 "PrintCLike.cpp.template"
                                                                  print(endWriteTrace());
                                                                  print(semicolon());
                                                                  increaseIndent();
                                                                  print(rightBrace());
                                                                  decreaseIndent();
                                                                  if (isCpp())
                                                                  {
                                                            #line 6452 "PrintCLike.cpp"
  append(L"\n");
  append(L"  fprintf(stderr, \"reduce\\\" nonterminal=\\\"%s\\\" count=\\\"%d\\\"/>\\n\", ");
                                                            #line 3922 "PrintCLike.cpp.template"
                                                                    if (stringIntroducer()[0])
                                                                    {
                                                            #line 6458 "PrintCLike.cpp"
  append(L"Utf8Encoder::encode(");
                                                            #line 3924 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 6462 "PrintCLike.cpp"
  append(L"xmlEscape(");
                                                            #line 3925 "PrintCLike.cpp.template"
                                                                    print(isGo() ? L"nonterminal" : L"NONTERMINAL");
                                                            #line 6466 "PrintCLike.cpp"
  append(L"[nonterminalId], 0).c_str()");
                                                            #line 3927 "PrintCLike.cpp.template"
                                                                    if (stringIntroducer()[0])
                                                                    {
                                                            #line 6471 "PrintCLike.cpp"
  append(L").c_str()");
                                                            #line 3929 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 6475 "PrintCLike.cpp"
  append(L", symbols);");
                                                            #line 3930 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 6481 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3934 "PrintCLike.cpp.template"
                                                                    print(writeTrace());
                                                            #line 6486 "PrintCLike.cpp"
  append(L"\"reduce\\\" nonterminal=\\\"\" + ");
                                                            #line 3935 "PrintCLike.cpp.template"
                                                                    print(staticPrefix());
                                                            #line 6490 "PrintCLike.cpp"
  append(L"xmlEscape(");
                                                            #line 3936 "PrintCLike.cpp.template"
                                                                    print(staticPrefix());
                                                                    print(isGo() ? L"nonterminal" : L"NONTERMINAL");
                                                                    print(leftbracket());
                                                            #line 6496 "PrintCLike.cpp"
  append(L"nonterminalId");
                                                            #line 3939 "PrintCLike.cpp.template"
                                                                    print(rightbracket());
                                                            #line 6500 "PrintCLike.cpp"
  append(L") + \"\\\" count=\\\"\" + ");
                                                            #line 3941 "PrintCLike.cpp.template"
                                                                    if (isPython())
                                                                    {
                                                            #line 6505 "PrintCLike.cpp"
  append(L"str(");
                                                            #line 3944 "PrintCLike.cpp.template"
                                                                    }
                                                                    else if (isGo())
                                                                    {
                                                            #line 6511 "PrintCLike.cpp"
  append(L"strconv.Itoa(");
                                                            #line 3948 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 6515 "PrintCLike.cpp"
  append(L"symbols");
                                                            #line 3950 "PrintCLike.cpp.template"
                                                                    if (isGo() || isPython())
                                                                    {
                                                            #line 6520 "PrintCLike.cpp"
  append(L")");
                                                            #line 3953 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 6524 "PrintCLike.cpp"
  append(L" + \"\\\"/>");
                                                            #line 3955 "PrintCLike.cpp.template"
                                                                    if (! isHaxe())
                                                                    {
                                                            #line 6529 "PrintCLike.cpp"
  append(L"\\n\"");
                                                            #line 3957 "PrintCLike.cpp.template"
                                                                      print(endWriteTrace());
                                                                      print(semicolon());
                                                                    }
                                                                    else
                                                                    {
                                                            #line 6537 "PrintCLike.cpp"
  append(L"\";\n");
  append(L"  trace(traceLine);");
                                                            #line 3963 "PrintCLike.cpp.template"
                                                                    }
                                                                  }
                                                                }
                                                                if (tree)
                                                                {
                                                            #line 6546 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if ");
                                                            #line 3969 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                                  print(thiz());
                                                            #line 6552 "PrintCLike.cpp"
  append(L"l1 == 0");
                                                            #line 3971 "PrintCLike.cpp.template"
                                                                  print(ifRightParen());
                                                                  printIndented(1, leftBrace());
                                                            #line 6557 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 3974 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 6562 "PrintCLike.cpp"
  append(L"b1 = ");
                                                            #line 3975 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 6566 "PrintCLike.cpp"
  append(L"e0");
                                                            #line 3976 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                  increaseIndent();
                                                                  print(rightBrace());
                                                                  decreaseIndent();
                                                            #line 6573 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if ");
                                                            #line 3981 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                            #line 6578 "PrintCLike.cpp"
  append(L"symbols > 0");
                                                            #line 3982 "PrintCLike.cpp.template"
                                                                  print(ifRightParen());
                                                                  printIndented(1, leftBrace());
                                                                  if (useGlr)
                                                                  {
                                                                    printStackPop();
                                                                  }
                                                                  else
                                                                  {
                                                            #line 6589 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 3991 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 6594 "PrintCLike.cpp"
  append(L"top -= symbols * 3");
                                                            #line 3992 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 6598 "PrintCLike.cpp"
  append(L"\n");
  append(L"    state = ");
                                                            #line 3994 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 6603 "PrintCLike.cpp"
  append(L"iStack");
                                                            #line 3995 "PrintCLike.cpp.template"
                                                                    print(leftbracket());
                                                                    print(thiz());
                                                            #line 6608 "PrintCLike.cpp"
  append(L"top + 2");
                                                            #line 3997 "PrintCLike.cpp.template"
                                                                    print(rightbracket());
                                                                    print(semicolon());
                                                            #line 6613 "PrintCLike.cpp"
  append(L"\n");
  append(L"    bs = ");
                                                            #line 4000 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 6618 "PrintCLike.cpp"
  append(L"iStack");
                                                            #line 4001 "PrintCLike.cpp.template"
                                                                    print(leftbracket());
                                                                    print(thiz());
                                                            #line 6623 "PrintCLike.cpp"
  append(L"top + 1");
                                                            #line 4003 "PrintCLike.cpp.template"
                                                                    print(rightbracket());
                                                                    print(semicolon());
                                                                  }
                                                            #line 6629 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4007 "PrintCLike.cpp.template"
                                                                  printIndented(1, elseWithBraces());
                                                            #line 6634 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4009 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 6639 "PrintCLike.cpp"
  append(L"bs = ");
                                                            #line 4010 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 6643 "PrintCLike.cpp"
  append(L"b1");
                                                            #line 4011 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                            #line 6647 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4013 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 6652 "PrintCLike.cpp"
  append(L"es = ");
                                                            #line 4014 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 6656 "PrintCLike.cpp"
  append(L"b1");
                                                            #line 4015 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                  increaseIndent();
                                                                  print(rightBrace());
                                                                  decreaseIndent();
                                                            #line 6663 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if ");
                                                            #line 4020 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                            #line 6668 "PrintCLike.cpp"
  append(L"nonterminalId == ");
                                                            #line 4021 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 6672 "PrintCLike.cpp"
  append(L"target ");
                                                            #line 4022 "PrintCLike.cpp.template"
                                                                  if (isPython())
                                                                  {
                                                            #line 6677 "PrintCLike.cpp"
  append(L"and");
                                                            #line 4024 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 6683 "PrintCLike.cpp"
  append(L"&&");
                                                            #line 4027 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 6687 "PrintCLike.cpp"
  append(L" ");
                                                            #line 4028 "PrintCLike.cpp.template"
                                                                  if (useGlr)
                                                                  {
                                                                    print(thiz());
                                                            #line 6693 "PrintCLike.cpp"
  append(L"stack");
                                                            #line 4031 "PrintCLike.cpp.template"
                                                                    print(arrow());
                                                            #line 6697 "PrintCLike.cpp"
  append(L"link == ");
                                                            #line 4032 "PrintCLike.cpp.template"
                                                                    print(nullPtr());
                                                                  }
                                                                  else
                                                                  {
                                                            #line 6704 "PrintCLike.cpp"
  append(L"t == ");
                                                            #line 4036 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 6708 "PrintCLike.cpp"
  append(L"top");
                                                            #line 4037 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(ifRightParen());
                                                                  printIndented(1, leftBrace());
                                                            #line 6714 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4041 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 6719 "PrintCLike.cpp"
  append(L"bs = ");
                                                            #line 4042 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 6723 "PrintCLike.cpp"
  append(L"bw");
                                                            #line 4043 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                            #line 6727 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4045 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 6732 "PrintCLike.cpp"
  append(L"es = ");
                                                            #line 4046 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 6736 "PrintCLike.cpp"
  append(L"b1");
                                                            #line 4047 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                            #line 6740 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4049 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 6745 "PrintCLike.cpp"
  append(L"bw = ");
                                                            #line 4050 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 6749 "PrintCLike.cpp"
  append(L"b1");
                                                            #line 4051 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                  increaseIndent();
                                                                  print(rightBrace());
                                                                  decreaseIndent();
                                                            #line 6756 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if ");
                                                            #line 4056 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                                  if (useGlr) print(thiz());
                                                            #line 6762 "PrintCLike.cpp"
  append(L"eventHandler != ");
                                                            #line 4058 "PrintCLike.cpp.template"
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
                                                            #line 6777 "PrintCLike.cpp"
  append(L"\n");
  append(L"    if ");
                                                            #line 4071 "PrintCLike.cpp.template"
                                                                    print(ifLeftParen());
                                                                    print(thiz());
                                                                    if (isGo())
                                                                    {
                                                            #line 6785 "PrintCLike.cpp"
  append(L"IsUnambiguous");
                                                            #line 4075 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 6791 "PrintCLike.cpp"
  append(L"isUnambiguous");
                                                            #line 4078 "PrintCLike.cpp.template"
                                                                    }
                                                                    if (! isScala()) print(L"()");
                                                                    print(ifRightParen());
                                                                    printIndented(2, leftBrace());
                                                                    increaseIndent();
                                                                  }
                                                            #line 6800 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4085 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 6805 "PrintCLike.cpp"
  append(L"eventHandler");
                                                            #line 4086 "PrintCLike.cpp.template"
                                                                  if (shiftAmbiguity && isTypescript()) print(L"!");
                                                                  print(arrow());
                                                                  if (isGo())
                                                                  {
                                                            #line 6812 "PrintCLike.cpp"
  append(L"N");
                                                            #line 4090 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 6818 "PrintCLike.cpp"
  append(L"n");
                                                            #line 4093 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 6822 "PrintCLike.cpp"
  append(L"onterminal(");
                                                            #line 4094 "PrintCLike.cpp.template"
                                                                  print(staticPrefix());
                                                                  print(isGo() ? L"nonterminal" : L"NONTERMINAL");
                                                                  print(leftbracket());
                                                            #line 6828 "PrintCLike.cpp"
  append(L"nonterminalId");
                                                            #line 4097 "PrintCLike.cpp.template"
                                                                  print(rightbracket());
                                                            #line 6832 "PrintCLike.cpp"
  append(L", ");
                                                            #line 4098 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 6836 "PrintCLike.cpp"
  append(L"bs, ");
                                                            #line 4099 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 6840 "PrintCLike.cpp"
  append(L"es, symbols)");
                                                            #line 4101 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                  if (useGlr)
                                                                  {
                                                                    decreaseIndent();
                                                            #line 6847 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4106 "PrintCLike.cpp.template"
                                                                    printIndented(2, elseWithBraces());
                                                            #line 6852 "PrintCLike.cpp"
  append(L"\n");
  append(L"      ");
                                                            #line 4108 "PrintCLike.cpp.template"
                                                                    if (useGlr) print(thiz());
                                                            #line 6857 "PrintCLike.cpp"
  append(L"deferredEvent = ");
                                                            #line 4109 "PrintCLike.cpp.template"
                                                                    if (isGo())
                                                                    {
                                                            #line 6862 "PrintCLike.cpp"
  append(L"&NonterminalEvent{&AbstractDeferredEvent{this.deferredEvent, nonterminal[nonterminalId], this.bs, this.es}, symbols}");
                                                            #line 4112 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                                      if (! isPython())
                                                                      {
                                                            #line 6870 "PrintCLike.cpp"
  append(L"new ");
                                                            #line 4117 "PrintCLike.cpp.template"
                                                                      }
                                                                      if (! isHaxe() && ! isTypescript()) print(staticPrefix());
                                                                      if (isJavascript() || isTypescript())
                                                                      {
                                                            #line 6877 "PrintCLike.cpp"
  append(L"DeferredEvent");
                                                            #line 4121 "PrintCLike.cpp.template"
                                                                      }
                                                                      else
                                                                      {
                                                            #line 6883 "PrintCLike.cpp"
  append(L"NonterminalEvent");
                                                            #line 4124 "PrintCLike.cpp.template"
                                                                      }
                                                            #line 6887 "PrintCLike.cpp"
  append(L"(");
                                                            #line 4125 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 6891 "PrintCLike.cpp"
  append(L"deferredEvent, ");
                                                            #line 4126 "PrintCLike.cpp.template"
                                                                      print(staticPrefix());
                                                            #line 6895 "PrintCLike.cpp"
  append(L"NONTERMINAL");
                                                            #line 4127 "PrintCLike.cpp.template"
                                                                      print(leftbracket());
                                                            #line 6899 "PrintCLike.cpp"
  append(L"nonterminalId");
                                                            #line 4128 "PrintCLike.cpp.template"
                                                                      print(rightbracket());
                                                            #line 6903 "PrintCLike.cpp"
  append(L", ");
                                                            #line 4129 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 6907 "PrintCLike.cpp"
  append(L"bs, ");
                                                            #line 4130 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 6911 "PrintCLike.cpp"
  append(L"es, symbols)");
                                                            #line 4132 "PrintCLike.cpp.template"
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
                                                            #line 6926 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if ");
                                                            #line 4145 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                            #line 6931 "PrintCLike.cpp"
  append(L"symbols > 0");
                                                            #line 4146 "PrintCLike.cpp.template"
                                                                  print(ifRightParen());
                                                                  printIndented(1, leftBrace());
                                                                  if (useGlr)
                                                                  {
                                                                    printStackPop();
                                                                  }
                                                                  else
                                                                  {
                                                            #line 6942 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4155 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 6947 "PrintCLike.cpp"
  append(L"top -= symbols << 1;\n");
  append(L"    state = ");
                                                            #line 4157 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 6952 "PrintCLike.cpp"
  append(L"iStack");
                                                            #line 4158 "PrintCLike.cpp.template"
                                                                    print(leftbracket());
                                                                    print(thiz());
                                                            #line 6957 "PrintCLike.cpp"
  append(L"top + 1");
                                                            #line 4160 "PrintCLike.cpp.template"
                                                                    print(rightbracket());
                                                                    print(semicolon());
                                                                  }
                                                                  increaseIndent();
                                                                  print(rightBrace());
                                                                  decreaseIndent();
                                                                  if (useGlr && tree)
                                                                  {
                                                            #line 6968 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if ");
                                                            #line 4169 "PrintCLike.cpp.template"
                                                                    print(ifLeftParen());
                                                            #line 6973 "PrintCLike.cpp"
  append(L"nonterminalId == ");
                                                            #line 4170 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 6977 "PrintCLike.cpp"
  append(L"target ");
                                                            #line 4171 "PrintCLike.cpp.template"
                                                                    if (isPython())
                                                                    {
                                                            #line 6982 "PrintCLike.cpp"
  append(L"and");
                                                            #line 4173 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 6988 "PrintCLike.cpp"
  append(L"&&");
                                                            #line 4176 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 6992 "PrintCLike.cpp"
  append(L" ");
                                                            #line 4177 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 6996 "PrintCLike.cpp"
  append(L"stack");
                                                            #line 4178 "PrintCLike.cpp.template"
                                                                    print(arrow());
                                                            #line 7000 "PrintCLike.cpp"
  append(L"link == ");
                                                            #line 4179 "PrintCLike.cpp.template"
                                                                    print(nullPtr());
                                                                    print(ifRightParen());
                                                                    printIndented(1, leftBrace());
                                                            #line 7006 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4183 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7011 "PrintCLike.cpp"
  append(L"bs = ");
                                                            #line 4184 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7015 "PrintCLike.cpp"
  append(L"bw");
                                                            #line 4185 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 7019 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4187 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7024 "PrintCLike.cpp"
  append(L"bw = ");
                                                            #line 4188 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7028 "PrintCLike.cpp"
  append(L"b1");
                                                            #line 4189 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                    increaseIndent();
                                                                    print(rightBrace());
                                                                    decreaseIndent();
                                                                  }
                                                                }
                                                            #line 7037 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4196 "PrintCLike.cpp.template"
                                                                if (useGlr) print(thiz());
                                                            #line 7042 "PrintCLike.cpp"
  append(L"action = ");
                                                            #line 4197 "PrintCLike.cpp.template"
                                                                print(staticPrefix());
                                                                print(isGo() ? L"reduceAction" : L"goTo");
                                                            #line 7047 "PrintCLike.cpp"
  append(L"(nonterminalId, ");
                                                            #line 4199 "PrintCLike.cpp.template"
                                                                if (useGlr) print(thiz());
                                                            #line 7051 "PrintCLike.cpp"
  append(L"state)");
                                                            #line 4200 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                print(rightBrace());
                                                                decreaseIndent();
                                                                print(rightBrace());
                                                                decreaseIndent();
                                                                if (useGlr)
                                                                {
                                                                  if (isScala())
                                                                  {
                                                            #line 7063 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ERROR");
                                                            #line 4210 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isCpp())
                                                                  {
                                                            #line 7070 "PrintCLike.cpp"
  append(L"\n");
  append(L"  return PARSING;");
                                                            #line 4214 "PrintCLike.cpp.template"
                                                                  }
                                                                }
                                                                print(rightBrace());
                                                                if (isJavascript() && useGlr)
                                                                {
                                                            #line 7079 "PrintCLike.cpp"
  append(L";");
                                                            #line 4219 "PrintCLike.cpp.template"
                                                                }
                                                            #line 7083 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4221 "PrintCLike.cpp.template"
                                                                if ((tree || hasCustomCode) && useGlr)
                                                                {
                                                                  openMethod(boolType(), L"", L"isUnambiguous", L"", false, L"ParsingThread");
                                                                  print(leftBrace());
                                                            #line 7090 "PrintCLike.cpp"
  append(L"\n");
  append(L"  return ");
                                                            #line 4226 "PrintCLike.cpp.template"
                                                                  if (isPython())
                                                                  {
                                                            #line 7096 "PrintCLike.cpp"
  append(L"len(self.threads) == 0");
                                                            #line 4228 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                                    print(thiz());
                                                            #line 7103 "PrintCLike.cpp"
  append(L"threads");
                                                            #line 4232 "PrintCLike.cpp.template"
                                                                    print(arrow());
                                                                    if (isCpp())
                                                                    {
                                                            #line 7109 "PrintCLike.cpp"
  append(L"empty();");
                                                            #line 4235 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 7115 "PrintCLike.cpp"
  append(L"isEmpty");
                                                            #line 4238 "PrintCLike.cpp.template"
                                                                      if (! isScala()) print(L"()");
                                                                      print(semicolon());
                                                                    }
                                                                  }
                                                                  print(rightBrace());
                                                            #line 7123 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4244 "PrintCLike.cpp.template"
                                                                }
                                                                if (hasCustomCode)
                                                                {
                                                                  if (useGlr)
                                                                  {
                                                                    if (isJavascript())
                                                                    {
                                                            #line 7133 "PrintCLike.cpp"
  append(L"\n");
  append(L"this.executeDeferredCode = function()\n");
                                                            #line 4253 "PrintCLike.cpp.template"
                                                                    }
                                                                    else if (isTypescript())
                                                                    {
                                                            #line 7140 "PrintCLike.cpp"
  append(L"\n");
  append(L"executeDeferredCode()\n");
                                                            #line 4258 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                                      openMethod(voidType(), L"", L"executeDeferredCode", L"", false, L"ParsingThread");
                                                                    }
                                                                    print(leftBrace());
                                                                    increaseIndent();
                                                            #line 7151 "PrintCLike.cpp"
  append(L"\n");
  append(L"if ");
                                                            #line 4266 "PrintCLike.cpp.template"
                                                                    print(ifLeftParen());
                                                                    print(thiz());
                                                            #line 7157 "PrintCLike.cpp"
  append(L"deferredCode != ");
                                                            #line 4268 "PrintCLike.cpp.template"
                                                                    print(nullPtr());
                                                                    print(ifRightParen());
                                                                    print(leftBrace());
                                                                    increaseIndent();
                                                            #line 7164 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4273 "PrintCLike.cpp.template"
                                                                    if (isJavascript() || isHaxe() || isScala() || isTypescript())
                                                                    {
                                                            #line 7169 "PrintCLike.cpp"
  append(L"var ");
                                                            #line 4275 "PrintCLike.cpp.template"
                                                                    }
                                                                    else if (! isGo() && ! isPython())
                                                                    {
                                                            #line 7175 "PrintCLike.cpp"
  append(L"DeferredCode ");
                                                            #line 4278 "PrintCLike.cpp.template"
                                                                    }
                                                                    if (isCpp()) print(L"*");
                                                            #line 7180 "PrintCLike.cpp"
  append(L"predecessor");
                                                            #line 4280 "PrintCLike.cpp.template"
                                                                    print(assign());
                                                                    print(thiz());
                                                            #line 7185 "PrintCLike.cpp"
  append(L"deferredCode");
                                                            #line 4282 "PrintCLike.cpp.template"
                                                                    print(arrow());
                                                            #line 7189 "PrintCLike.cpp"
  append(L"link");
                                                            #line 4283 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 7193 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4285 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7197 "PrintCLike.cpp"
  append(L"deferredCode");
                                                            #line 4286 "PrintCLike.cpp.template"
                                                                    print(arrow());
                                                            #line 7201 "PrintCLike.cpp"
  append(L"link = ");
                                                            #line 4287 "PrintCLike.cpp.template"
                                                                    print(nullPtr());
                                                                    print(semicolon());
                                                                    if (isGo())
                                                                    {
                                                            #line 7208 "PrintCLike.cpp"
  append(L"\n");
  append(L"for ");
                                                            #line 4292 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 7215 "PrintCLike.cpp"
  append(L"\n");
  append(L"while ");
                                                            #line 4296 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(ifLeftParen());
                                                            #line 7221 "PrintCLike.cpp"
  append(L"predecessor != ");
                                                            #line 4298 "PrintCLike.cpp.template"
                                                                    print(nullPtr());
                                                                    print(ifRightParen());
                                                                    print(leftBrace());
                                                            #line 7227 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4302 "PrintCLike.cpp.template"
                                                                    if (isJavascript() || isHaxe() || isScala() || isTypescript())
                                                                    {
                                                            #line 7233 "PrintCLike.cpp"
  append(L"var ");
                                                            #line 4304 "PrintCLike.cpp.template"
                                                                    }
                                                                    else if (! isGo() && ! isPython())
                                                                    {
                                                            #line 7239 "PrintCLike.cpp"
  append(L"DeferredCode ");
                                                            #line 4307 "PrintCLike.cpp.template"
                                                                    }
                                                                    if (isCpp()) print(L"*");
                                                            #line 7244 "PrintCLike.cpp"
  append(L"nextCode");
                                                            #line 4309 "PrintCLike.cpp.template"
                                                                    print(assign());
                                                            #line 7248 "PrintCLike.cpp"
  append(L"predecessor");
                                                            #line 4310 "PrintCLike.cpp.template"
                                                                    print(arrow());
                                                            #line 7252 "PrintCLike.cpp"
  append(L"link");
                                                            #line 4311 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 7256 "PrintCLike.cpp"
  append(L"\n");
  append(L"  predecessor");
                                                            #line 4313 "PrintCLike.cpp.template"
                                                                    print(arrow());
                                                            #line 7261 "PrintCLike.cpp"
  append(L"link = ");
                                                            #line 4314 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7265 "PrintCLike.cpp"
  append(L"deferredCode");
                                                            #line 4315 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 7269 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4317 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7274 "PrintCLike.cpp"
  append(L"deferredCode = predecessor");
                                                            #line 4318 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 7278 "PrintCLike.cpp"
  append(L"\n");
  append(L"  predecessor = nextCode");
                                                            #line 4320 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                    print(rightBrace());
                                                            #line 7284 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4323 "PrintCLike.cpp.template"
                                                                    print(intVar());
                                                            #line 7288 "PrintCLike.cpp"
  append(L"b0t");
                                                            #line 4324 "PrintCLike.cpp.template"
                                                                    print(assign());
                                                                    print(thiz());
                                                            #line 7293 "PrintCLike.cpp"
  append(L"b0");
                                                            #line 4326 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 7297 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4328 "PrintCLike.cpp.template"
                                                                    print(intVar());
                                                            #line 7301 "PrintCLike.cpp"
  append(L"e0t");
                                                            #line 4329 "PrintCLike.cpp.template"
                                                                    print(assign());
                                                                    print(thiz());
                                                            #line 7306 "PrintCLike.cpp"
  append(L"e0");
                                                            #line 4331 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                    if (isGo())
                                                                    {
                                                            #line 7312 "PrintCLike.cpp"
  append(L"\n");
  append(L"for ");
                                                            #line 4335 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 7319 "PrintCLike.cpp"
  append(L"\n");
  append(L"while ");
                                                            #line 4339 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(ifLeftParen());
                                                                    print(thiz());
                                                            #line 7326 "PrintCLike.cpp"
  append(L"deferredCode != ");
                                                            #line 4342 "PrintCLike.cpp.template"
                                                                    print(nullPtr());
                                                                    print(ifRightParen());
                                                                    print(leftBrace());
                                                            #line 7332 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4346 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7337 "PrintCLike.cpp"
  append(L"b0 = ");
                                                            #line 4347 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7341 "PrintCLike.cpp"
  append(L"deferredCode");
                                                            #line 4348 "PrintCLike.cpp.template"
                                                                    print(arrow());
                                                            #line 7345 "PrintCLike.cpp"
  append(L"b0");
                                                            #line 4349 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 7349 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4351 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7354 "PrintCLike.cpp"
  append(L"e0 = ");
                                                            #line 4352 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7358 "PrintCLike.cpp"
  append(L"deferredCode");
                                                            #line 4353 "PrintCLike.cpp.template"
                                                                    print(arrow());
                                                            #line 7362 "PrintCLike.cpp"
  append(L"e0");
                                                            #line 4354 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 7366 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4356 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                                    print(isGo() ? L"E" : L"e");
                                                            #line 7372 "PrintCLike.cpp"
  append(L"xecute(");
                                                            #line 4358 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7376 "PrintCLike.cpp"
  append(L"deferredCode");
                                                            #line 4359 "PrintCLike.cpp.template"
                                                                    print(arrow());
                                                            #line 7380 "PrintCLike.cpp"
  append(L"codeId)");
                                                            #line 4360 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                    if (isCpp())
                                                                    {
                                                            #line 7386 "PrintCLike.cpp"
  append(L"\n");
  append(L"  DeferredCode *next = deferredCode->link;\n");
  append(L"  delete deferredCode;\n");
  append(L"  deferredCode = next;");
                                                            #line 4366 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 7395 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4370 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 7400 "PrintCLike.cpp"
  append(L"deferredCode = ");
                                                            #line 4371 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 7404 "PrintCLike.cpp"
  append(L"deferredCode");
                                                            #line 4372 "PrintCLike.cpp.template"
                                                                      print(arrow());
                                                            #line 7408 "PrintCLike.cpp"
  append(L"link");
                                                            #line 4373 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                                    }
                                                                    print(rightBrace());
                                                            #line 7414 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4377 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7418 "PrintCLike.cpp"
  append(L"b0 = b0t");
                                                            #line 4378 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 7422 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4380 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7426 "PrintCLike.cpp"
  append(L"e0 = e0t");
                                                            #line 4381 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                    decreaseIndent();
                                                                    print(rightBrace());
                                                                    decreaseIndent();
                                                                    print(rightBrace());
                                                            #line 7434 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4387 "PrintCLike.cpp.template"
                                                                  }
                                                                  openMethod(voidType(), L"", L"execute", L"int reduce", false, useGlr ? L"ParsingThread" : className.c_str());
                                                                  print(leftBrace());
                                                                  increaseIndent();
                                                                  if (! isPython())
                                                                  {
                                                            #line 7443 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4394 "PrintCLike.cpp.template"
                                                                    if (! isScala())
                                                                    {
                                                            #line 7448 "PrintCLike.cpp"
  append(L"switch ");
                                                            #line 4396 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(ifLeftParen());
                                                            #line 7453 "PrintCLike.cpp"
  append(L"reduce");
                                                            #line 4398 "PrintCLike.cpp.template"
                                                                    print(ifRightParen());
                                                                    if (isScala())
                                                                    {
                                                            #line 7459 "PrintCLike.cpp"
  append(L" match");
                                                            #line 4401 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(leftBrace());
                                                                  }
                                                                  int lastContentId = grammar->distinctCodeAnnotations.size() - 1;
                                                                  for (int contentId = 0; contentId <= lastContentId; ++contentId)
                                                                  {
                                                                    ProcessingInstruction *p = grammar->distinctCodeAnnotations[contentId];
                                                                    if (! isPython())
                                                                    {
                                                            #line 7471 "PrintCLike.cpp"
  append(L"\n");
  append(L"case ");
                                                            #line 4411 "PrintCLike.cpp.template"
                                                                    }
                                                                    else if (contentId == 0)
                                                                    {
                                                            #line 7478 "PrintCLike.cpp"
  append(L"\n");
  append(L"if reduce == ");
                                                            #line 4415 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 7485 "PrintCLike.cpp"
  append(L"\n");
  append(L"elif reduce == ");
                                                            #line 4419 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(format.toString<wchar_t>(contentId));
                                                                    print(caseIntroducer());
                                                                    increaseIndent();
                                                                    print(leftBrace());
                                                                    visitProcessingInstruction(p);
                                                                    print(rightBrace());
                                                                    if (! isScala() && ! isHaxe() && ! isGo() && ! isPython())
                                                                    {
                                                            #line 7498 "PrintCLike.cpp"
  append(L"\n");
  append(L"break");
                                                            #line 4429 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                                    }
                                                                    decreaseIndent();
                                                                  }
                                                                  if (isScala())
                                                                  {
                                                            #line 7508 "PrintCLike.cpp"
  append(L"\n");
  append(L"case _");
                                                            #line 4436 "PrintCLike.cpp.template"
                                                                    print(caseIntroducer());
                                                                  }
                                                                  else if (! isPython())
                                                                  {
                                                            #line 7516 "PrintCLike.cpp"
  append(L"\n");
  append(L"default");
                                                            #line 4441 "PrintCLike.cpp.template"
                                                                    print(caseIntroducer());
                                                                  }
                                                                  if (! isScala() && ! isHaxe() && ! isGo() && ! isPython())
                                                                  {
                                                            #line 7524 "PrintCLike.cpp"
  append(L"\n");
  append(L"  break");
                                                            #line 4446 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                  }
                                                                  print(rightBrace());
                                                                  decreaseIndent();
                                                                  print(rightBrace());
                                                            #line 7533 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4452 "PrintCLike.cpp.template"
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
                                                            #line 7559 "PrintCLike.cpp"
  append(L"\n");
  append(L"if ");
                                                            #line 4476 "PrintCLike.cpp.template"
                                                                print(ifLeftParen());
                                                                print(thiz());
                                                            #line 7565 "PrintCLike.cpp"
  append(L"l1 == t");
                                                            #line 4478 "PrintCLike.cpp.template"
                                                                print(ifRightParen());
                                                                print(leftBrace());
                                                                increaseIndent();
                                                                if (tree && i == 0 && ! isLrParser)
                                                                {
                                                                  if (anyWhitespace && ! isLrParser)
                                                                  {
                                                            #line 7575 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4486 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7579 "PrintCLike.cpp"
  append(L"whitespace");
                                                            #line 4487 "PrintCLike.cpp.template"
                                                                    print(isScala() ? L"" : L"()");
                                                                    print(semicolon());
                                                                  }
                                                            #line 7585 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4491 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 7589 "PrintCLike.cpp"
  append(L"eventHandler");
                                                            #line 4492 "PrintCLike.cpp.template"
                                                                  if (shiftAmbiguity && isTypescript()) print(L"!");
                                                                  print(arrow());
                                                                  if (isGo())
                                                                  {
                                                            #line 7596 "PrintCLike.cpp"
  append(L"T");
                                                            #line 4496 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 7602 "PrintCLike.cpp"
  append(L"t");
                                                            #line 4499 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 7606 "PrintCLike.cpp"
  append(L"erminal(");
                                                            #line 4500 "PrintCLike.cpp.template"
                                                                  if (isJava() || isCSharp())
                                                                  {
                                                                    print(staticPrefix());
                                                            #line 7612 "PrintCLike.cpp"
  append(L"TOKEN[");
                                                            #line 4503 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7616 "PrintCLike.cpp"
  append(L"l1]");
                                                            #line 4504 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isTypescript())
                                                                  {
                                                                    print(staticPrefix());
                                                            #line 7623 "PrintCLike.cpp"
  append(L"TOKEN[");
                                                            #line 4508 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7627 "PrintCLike.cpp"
  append(L"l1]");
                                                            #line 4509 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isJavascript() || isHaxe())
                                                                  {
                                                                    print(staticPrefix());
                                                            #line 7634 "PrintCLike.cpp"
  append(L"TOKEN[");
                                                            #line 4513 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7638 "PrintCLike.cpp"
  append(L"l1]");
                                                            #line 4514 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isScala())
                                                                  {
                                                                    print(staticPrefix());
                                                            #line 7645 "PrintCLike.cpp"
  append(L"TOKEN(l1)");
                                                            #line 4518 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isGo())
                                                                  {
                                                            #line 7651 "PrintCLike.cpp"
  append(L"token[this.l1]");
                                                            #line 4521 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                                    print(staticPrefix());
                                                            #line 7658 "PrintCLike.cpp"
  append(L"TOKEN[");
                                                            #line 4525 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7662 "PrintCLike.cpp"
  append(L"l1]");
                                                            #line 4526 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 7666 "PrintCLike.cpp"
  append(L", ");
                                                            #line 4527 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 7670 "PrintCLike.cpp"
  append(L"b1, ");
                                                            #line 4528 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 7674 "PrintCLike.cpp"
  append(L"e1)");
                                                            #line 4529 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                            #line 7679 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4532 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 7683 "PrintCLike.cpp"
  append(L"b0 = ");
                                                            #line 4533 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 7687 "PrintCLike.cpp"
  append(L"b1; ");
                                                            #line 4534 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 7691 "PrintCLike.cpp"
  append(L"e0 = ");
                                                            #line 4535 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 7695 "PrintCLike.cpp"
  append(L"e1;");
                                                            #line 4536 "PrintCLike.cpp.template"
                                                                for (size_t k = 1; k < grammar->k; ++k)
                                                                {
                                                            #line 7700 "PrintCLike.cpp"
  append(L" ");
                                                            #line 4538 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 7704 "PrintCLike.cpp"
  append(L"l");
                                                            #line 4539 "PrintCLike.cpp.template"
                                                                  print(format.toString<wchar_t>(k));
                                                            #line 7708 "PrintCLike.cpp"
  append(L" = ");
                                                            #line 4540 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 7712 "PrintCLike.cpp"
  append(L"l");
                                                            #line 4541 "PrintCLike.cpp.template"
                                                                  print(format.toString<wchar_t>(k + 1));
                                                                  print(isPython() ? L"\n" : L"; ");
                                                            #line 7717 "PrintCLike.cpp"
  append(L"if ");
                                                            #line 4543 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                                  print(thiz());
                                                            #line 7722 "PrintCLike.cpp"
  append(L"l");
                                                            #line 4545 "PrintCLike.cpp.template"
                                                                  print(format.toString<wchar_t>(k));
                                                            #line 7726 "PrintCLike.cpp"
  append(L" != 0");
                                                            #line 4546 "PrintCLike.cpp.template"
                                                                  print(ifRightParen());
                                                                  if (isPython())
                                                                  {
                                                                    increaseIndent();
                                                                  }
                                                                  else
                                                                  {
                                                            #line 7736 "PrintCLike.cpp"
  append(L" {");
                                                            #line 4553 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 7740 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4555 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 7744 "PrintCLike.cpp"
  append(L"b");
                                                            #line 4556 "PrintCLike.cpp.template"
                                                                  print(format.toString<wchar_t>(k));
                                                            #line 7748 "PrintCLike.cpp"
  append(L" = ");
                                                            #line 4557 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 7752 "PrintCLike.cpp"
  append(L"b");
                                                            #line 4558 "PrintCLike.cpp.template"
                                                                  print(format.toString<wchar_t>(k + 1));
                                                            #line 7756 "PrintCLike.cpp"
  append(L"; ");
                                                            #line 4559 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 7760 "PrintCLike.cpp"
  append(L"e");
                                                            #line 4560 "PrintCLike.cpp.template"
                                                                  print(format.toString<wchar_t>(k));
                                                            #line 7764 "PrintCLike.cpp"
  append(L" = ");
                                                            #line 4561 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 7768 "PrintCLike.cpp"
  append(L"e");
                                                            #line 4562 "PrintCLike.cpp.template"
                                                                  print(format.toString<wchar_t>(k + 1));
                                                            #line 7772 "PrintCLike.cpp"
  append(L";");
                                                            #line 4563 "PrintCLike.cpp.template"
                                                                }
                                                            #line 7776 "PrintCLike.cpp"
  append(L" ");
                                                            #line 4564 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 7780 "PrintCLike.cpp"
  append(L"l");
                                                            #line 4565 "PrintCLike.cpp.template"
                                                                print(format.toString<wchar_t>(grammar->k));
                                                            #line 7784 "PrintCLike.cpp"
  append(L" = 0");
                                                            #line 4566 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                if (grammar->k > 1)
                                                                {
                                                            #line 7790 "PrintCLike.cpp"
  append(L" ");
                                                            #line 4569 "PrintCLike.cpp.template"
                                                                  for (size_t k = 1; k < grammar->k; ++k)
                                                                  {
                                                                    if (! isPython())
                                                                    {
                                                            #line 7797 "PrintCLike.cpp"
  append(L"}");
                                                            #line 4573 "PrintCLike.cpp.template"
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
                                                            #line 7812 "PrintCLike.cpp"
  append(L"\n");
  append(L"  fprintf(stderr, \"  <parse terminal=\\\"%s\\\"%s%s%s/>\\n\", ");
                                                            #line 4586 "PrintCLike.cpp.template"
                                                                    if (stringIntroducer()[0])
                                                                    {
                                                            #line 7818 "PrintCLike.cpp"
  append(L"Utf8Encoder::encode(");
                                                            #line 4589 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 7822 "PrintCLike.cpp"
  append(L"xmlEscape(TOKEN[t], 0).c_str()");
                                                            #line 4591 "PrintCLike.cpp.template"
                                                                    if (stringIntroducer()[0])
                                                                    {
                                                            #line 7827 "PrintCLike.cpp"
  append(L").c_str()");
                                                            #line 4593 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 7831 "PrintCLike.cpp"
  append(L", (l1 == 0 ? \"\" : \" input=\\\"\"),  (l1 == 0 ? \"\" : ");
                                                            #line 4595 "PrintCLike.cpp.template"
                                                                    if (stringIntroducer()[0])
                                                                    {
                                                            #line 7836 "PrintCLike.cpp"
  append(L"Utf8Encoder::encode(");
                                                            #line 4598 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 7840 "PrintCLike.cpp"
  append(L"xmlEscape(lookaheadString().c_str(), 0).c_str()");
                                                            #line 4600 "PrintCLike.cpp.template"
                                                                    if (stringIntroducer()[0])
                                                                    {
                                                            #line 7845 "PrintCLike.cpp"
  append(L").c_str()");
                                                            #line 4602 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 7849 "PrintCLike.cpp"
  append(L"), (l1 == 0 ? \"\" : \"\\\"\"));");
                                                            #line 4604 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                                    if (isGo())
                                                                    {
                                                            #line 7857 "PrintCLike.cpp"
  append(L"\n");
  append(L"  var inputAttr string\n");
  append(L"  if (this.l1 == 0) {\n");
  append(L"    inputAttr = \"\"\n");
  append(L"  } else {\n");
  append(L"    inputAttr = \" input=\\\"\" + xmlEscape(this.lookaheadString()) + \"\\\"\"\n");
  append(L"  }");
                                                            #line 4615 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 7867 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4617 "PrintCLike.cpp.template"
                                                                    if (isHaxe())
                                                                    {
                                                            #line 7873 "PrintCLike.cpp"
  append(L"trace(");
                                                            #line 4619 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                                      print(writeTrace());
                                                                    }
                                                            #line 7881 "PrintCLike.cpp"
  append(L"\"  <parse terminal=\\\"\" + ");
                                                            #line 4624 "PrintCLike.cpp.template"
                                                                    print(staticPrefix());
                                                            #line 7885 "PrintCLike.cpp"
  append(L"xmlEscape(");
                                                            #line 4625 "PrintCLike.cpp.template"
                                                                    print(staticPrefix());
                                                                    print(isGo() ? L"token" : L"TOKEN");
                                                                    print(leftbracket());
                                                            #line 7891 "PrintCLike.cpp"
  append(L"t");
                                                            #line 4628 "PrintCLike.cpp.template"
                                                                    print(rightbracket());
                                                            #line 7895 "PrintCLike.cpp"
  append(L") + \"\\\"\" + ");
                                                            #line 4629 "PrintCLike.cpp.template"
                                                                    if (isGo())
                                                                    {
                                                            #line 7900 "PrintCLike.cpp"
  append(L"inputAttr");
                                                            #line 4631 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 7906 "PrintCLike.cpp"
  append(L"(");
                                                            #line 4634 "PrintCLike.cpp.template"
                                                                      if (isScala())
                                                                      {
                                                            #line 7911 "PrintCLike.cpp"
  append(L"if (l1 == 0) \"\" else");
                                                            #line 4636 "PrintCLike.cpp.template"
                                                                      }
                                                                      else if (isPython())
                                                                      {
                                                            #line 7917 "PrintCLike.cpp"
  append(L"\"\" if self.l1 == 0 else");
                                                            #line 4639 "PrintCLike.cpp.template"
                                                                      }
                                                                      else
                                                                      {
                                                                        print(thiz());
                                                            #line 7924 "PrintCLike.cpp"
  append(L"l1 == 0 ? \"\" :");
                                                            #line 4643 "PrintCLike.cpp.template"
                                                                      }
                                                            #line 7928 "PrintCLike.cpp"
  append(L" \" input=\\\"\" + ");
                                                            #line 4644 "PrintCLike.cpp.template"
                                                                      print(staticPrefix());
                                                            #line 7932 "PrintCLike.cpp"
  append(L"xmlEscape(");
                                                            #line 4645 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 7936 "PrintCLike.cpp"
  append(L"lookaheadString");
                                                            #line 4646 "PrintCLike.cpp.template"
                                                                      if (! isScala()) print(L"()");
                                                            #line 7940 "PrintCLike.cpp"
  append(L") + \"\\\"\")");
                                                            #line 4647 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 7944 "PrintCLike.cpp"
  append(L" + \"/>");
                                                            #line 4648 "PrintCLike.cpp.template"
                                                                    if (isHaxe())
                                                                    {
                                                            #line 7949 "PrintCLike.cpp"
  append(L"\")");
                                                            #line 4650 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 7955 "PrintCLike.cpp"
  append(L"\\n\"");
                                                            #line 4653 "PrintCLike.cpp.template"
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
                                                            #line 7969 "PrintCLike.cpp"
  append(L"el");
                                                            #line 4664 "PrintCLike.cpp.template"
                                                                    if (! isPython())
                                                                    {
                                                            #line 7974 "PrintCLike.cpp"
  append(L"se ");
                                                            #line 4666 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 7978 "PrintCLike.cpp"
  append(L"if ");
                                                            #line 4667 "PrintCLike.cpp.template"
                                                                    print(ifLeftParen());
                                                                    print(thiz());
                                                                    print(token());
                                                            #line 7984 "PrintCLike.cpp"
  append(L" < 0");
                                                            #line 4670 "PrintCLike.cpp.template"
                                                                    print(ifRightParen());
                                                                    print(leftBrace());
                                                            #line 7989 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4673 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7994 "PrintCLike.cpp"
  append(L"error(");
                                                            #line 4674 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7998 "PrintCLike.cpp"
  append(L"b1, ");
                                                            #line 4675 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8002 "PrintCLike.cpp"
  append(L"e1, -");
                                                            #line 4676 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8006 "PrintCLike.cpp"
  append(L"l1, 0, 0)");
                                                            #line 4677 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                    if (i == 0)
                                                                    {
                                                            #line 8012 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4681 "PrintCLike.cpp.template"
                                                                      print(beginThrowStmt());
                                                                      print(thiz());
                                                            #line 8018 "PrintCLike.cpp"
  append(L"bx, ");
                                                            #line 4683 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 8022 "PrintCLike.cpp"
  append(L"ex, ");
                                                            #line 4684 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 8026 "PrintCLike.cpp"
  append(L"sx, ");
                                                            #line 4685 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 8030 "PrintCLike.cpp"
  append(L"lx, ");
                                                            #line 4686 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 8034 "PrintCLike.cpp"
  append(L"tx");
                                                            #line 4687 "PrintCLike.cpp.template"
                                                                      print(endThrowStmt());
                                                                      print(semicolon());
                                                                    }
                                                                    print(rightBrace());
                                                                  }
                                                                  print(isGo() ? L" " : L"\n");
                                                            #line 8043 "PrintCLike.cpp"
  append(L"else");
                                                            #line 4693 "PrintCLike.cpp.template"
                                                                  if (isPython()) print(L":");
                                                                  print(leftBrace());
                                                            #line 8048 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4696 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8053 "PrintCLike.cpp"
  append(L"error(");
                                                            #line 4697 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8057 "PrintCLike.cpp"
  append(L"b1, ");
                                                            #line 4698 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8061 "PrintCLike.cpp"
  append(L"e1, 0, ");
                                                            #line 4699 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8065 "PrintCLike.cpp"
  append(L"l1, t)");
                                                            #line 4700 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                  if (i == 0 && grammar->noThrow)
                                                                  {
                                                            #line 8071 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4704 "PrintCLike.cpp.template"
                                                                    print(beginThrowStmt());
                                                                    print(thiz());
                                                            #line 8077 "PrintCLike.cpp"
  append(L"bx, ");
                                                            #line 4706 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8081 "PrintCLike.cpp"
  append(L"ex, ");
                                                            #line 4707 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8085 "PrintCLike.cpp"
  append(L"sx, ");
                                                            #line 4708 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8089 "PrintCLike.cpp"
  append(L"lx, ");
                                                            #line 4709 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8093 "PrintCLike.cpp"
  append(L"tx");
                                                            #line 4710 "PrintCLike.cpp.template"
                                                                    print(endThrowStmt());
                                                                    print(semicolon());
                                                                  }
                                                                  print(rightBrace());
                                                                }
                                                                else
                                                                {
                                                                  print(isGo() ? L" " : L"\n");
                                                            #line 8104 "PrintCLike.cpp"
  append(L"else");
                                                            #line 4718 "PrintCLike.cpp.template"
                                                                  if (isPython()) print(L":");
                                                                  print(leftBrace());
                                                            #line 8109 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4721 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8114 "PrintCLike.cpp"
  append(L"error(");
                                                            #line 4722 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8118 "PrintCLike.cpp"
  append(L"b1, ");
                                                            #line 4723 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8122 "PrintCLike.cpp"
  append(L"e1, 0, ");
                                                            #line 4724 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8126 "PrintCLike.cpp"
  append(L"l1, t)");
                                                            #line 4725 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                  print(rightBrace());
                                                                }
                                                                decreaseIndent();
                                                                print(rightBrace());
                                                            #line 8134 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4731 "PrintCLike.cpp.template"
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
                                                            #line 8153 "PrintCLike.cpp"
  append(L"\n");
  append(L"  var thread = new ParsingThread().copy(thisThread, 0);\n");
  append(L"  thread.setL1(code);\n");
  append(L"  thread.setB1(begin);\n");
  append(L"  thread.setE1(end);");
                                                            #line 4751 "PrintCLike.cpp.template"
                                                                    }
                                                                    else if (isGo())
                                                                    {
                                                            #line 8163 "PrintCLike.cpp"
  append(L"\n");
  append(L"  thread := new(ParsingThread).copy(this, 0)\n");
  append(L"  thread.l1 = code\n");
  append(L"  thread.b1 = this.begin\n");
  append(L"  thread.e1 = this.end");
                                                            #line 4758 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 8173 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4762 "PrintCLike.cpp.template"
                                                                      if (isHaxe() || isScala() || isTypescript())
                                                                      {
                                                            #line 8179 "PrintCLike.cpp"
  append(L"var ");
                                                            #line 4764 "PrintCLike.cpp.template"
                                                                      }
                                                                      else if (! isPython())
                                                                      {
                                                            #line 8185 "PrintCLike.cpp"
  append(L"ParsingThread ");
                                                            #line 4767 "PrintCLike.cpp.template"
                                                                      }
                                                                      if (isCpp()) print(L"*");
                                                            #line 8190 "PrintCLike.cpp"
  append(L"thread = ");
                                                            #line 4769 "PrintCLike.cpp.template"
                                                                      if (isCpp()) print(L"(");
                                                                      if (! isPython())
                                                                      {
                                                            #line 8196 "PrintCLike.cpp"
  append(L"new ");
                                                            #line 4772 "PrintCLike.cpp.template"
                                                                      }
                                                                      if (isScala() || isPython())
                                                                      {
                                                                        print(className.c_str());
                                                            #line 8203 "PrintCLike.cpp"
  append(L".");
                                                            #line 4776 "PrintCLike.cpp.template"
                                                                      }
                                                            #line 8207 "PrintCLike.cpp"
  append(L"ParsingThread()");
                                                            #line 4777 "PrintCLike.cpp.template"
                                                                      if (isCpp()) print(L")");
                                                                      print(arrow());
                                                            #line 8212 "PrintCLike.cpp"
  append(L"copy(");
                                                            #line 4779 "PrintCLike.cpp.template"
                                                                      if (isPython())
                                                                      {
                                                            #line 8217 "PrintCLike.cpp"
  append(L"self");
                                                            #line 4781 "PrintCLike.cpp.template"
                                                                      }
                                                                      else
                                                                      {
                                                            #line 8223 "PrintCLike.cpp"
  append(L"this");
                                                            #line 4784 "PrintCLike.cpp.template"
                                                                      }
                                                            #line 8227 "PrintCLike.cpp"
  append(L", 0)");
                                                            #line 4785 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                                      if (isCpp())
                                                                      {
                                                            #line 8233 "PrintCLike.cpp"
  append(L"\n");
  append(L"  thread->stack->unshare();\n");
  append(L"  thread->stack = 0;");
                                                            #line 4790 "PrintCLike.cpp.template"
                                                                      }
                                                            #line 8239 "PrintCLike.cpp"
  append(L"\n");
  append(L"  thread");
                                                            #line 4792 "PrintCLike.cpp.template"
                                                                      print(arrow());
                                                            #line 8244 "PrintCLike.cpp"
  append(L"l1 = code");
                                                            #line 4793 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                            #line 8248 "PrintCLike.cpp"
  append(L"\n");
  append(L"  thread");
                                                            #line 4795 "PrintCLike.cpp.template"
                                                                      print(arrow());
                                                            #line 8253 "PrintCLike.cpp"
  append(L"b1 = ");
                                                            #line 4796 "PrintCLike.cpp.template"
                                                                      if (useGlr) print(thiz());
                                                            #line 8257 "PrintCLike.cpp"
  append(L"begin");
                                                            #line 4797 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                            #line 8261 "PrintCLike.cpp"
  append(L"\n");
  append(L"  thread");
                                                            #line 4799 "PrintCLike.cpp.template"
                                                                      print(arrow());
                                                            #line 8266 "PrintCLike.cpp"
  append(L"e1 = ");
                                                            #line 4800 "PrintCLike.cpp.template"
                                                                      if (useGlr) print(thiz());
                                                            #line 8270 "PrintCLike.cpp"
  append(L"end");
                                                            #line 4801 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                                    }
                                                                  }
                                                                  else
                                                                  {
                                                            #line 8278 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4807 "PrintCLike.cpp.template"
                                                                    print(intVal());
                                                            #line 8283 "PrintCLike.cpp"
  append(L"b0W");
                                                            #line 4808 "PrintCLike.cpp.template"
                                                                    print(assign());
                                                                    print(thiz());
                                                            #line 8288 "PrintCLike.cpp"
  append(L"b0; ");
                                                            #line 4810 "PrintCLike.cpp.template"
                                                                    print(intVal());
                                                            #line 8292 "PrintCLike.cpp"
  append(L"e0W");
                                                            #line 4811 "PrintCLike.cpp.template"
                                                                    print(assign());
                                                                    print(thiz());
                                                            #line 8297 "PrintCLike.cpp"
  append(L"e0");
                                                            #line 4814 "PrintCLike.cpp.template"
                                                                    for (size_t k = 1; k < grammar->k; ++k)
                                                                    {
                                                            #line 8302 "PrintCLike.cpp"
  append(L"; ");
                                                            #line 4816 "PrintCLike.cpp.template"
                                                                      print(intVal());
                                                            #line 8306 "PrintCLike.cpp"
  append(L"l");
                                                            #line 4817 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(k));
                                                            #line 8310 "PrintCLike.cpp"
  append(L"W");
                                                            #line 4818 "PrintCLike.cpp.template"
                                                                      print(assign());
                                                                      print(thiz());
                                                            #line 8315 "PrintCLike.cpp"
  append(L"l");
                                                            #line 4820 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(k));
                                                                      print(semicolon());
                                                            #line 8320 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4823 "PrintCLike.cpp.template"
                                                                      print(intVal());
                                                            #line 8325 "PrintCLike.cpp"
  append(L"b");
                                                            #line 4824 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(k));
                                                            #line 8329 "PrintCLike.cpp"
  append(L"W");
                                                            #line 4825 "PrintCLike.cpp.template"
                                                                      print(assign());
                                                                      print(thiz());
                                                            #line 8334 "PrintCLike.cpp"
  append(L"b");
                                                            #line 4827 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(k));
                                                            #line 8338 "PrintCLike.cpp"
  append(L"; ");
                                                            #line 4828 "PrintCLike.cpp.template"
                                                                      print(intVal());
                                                            #line 8342 "PrintCLike.cpp"
  append(L"e");
                                                            #line 4829 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(k));
                                                            #line 8346 "PrintCLike.cpp"
  append(L"W");
                                                            #line 4830 "PrintCLike.cpp.template"
                                                                      print(assign());
                                                                      print(thiz());
                                                            #line 8351 "PrintCLike.cpp"
  append(L"e");
                                                            #line 4832 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(k));
                                                                    }
                                                                    print(semicolon());
                                                            #line 8357 "PrintCLike.cpp"
  append(L"\n");
  append(L"\n");
  append(L"  ");
                                                            #line 4837 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8363 "PrintCLike.cpp"
  append(L"l1 = code; ");
                                                            #line 4838 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8367 "PrintCLike.cpp"
  append(L"b1 = ");
                                                            #line 4839 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8371 "PrintCLike.cpp"
  append(L"begin; ");
                                                            #line 4840 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8375 "PrintCLike.cpp"
  append(L"e1 = ");
                                                            #line 4841 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8379 "PrintCLike.cpp"
  append(L"end");
                                                            #line 4842 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                    for (size_t k = 2; k <= grammar->k; ++k)
                                                                    {
                                                            #line 8385 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4846 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 8390 "PrintCLike.cpp"
  append(L"l");
                                                            #line 4847 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(k));
                                                            #line 8394 "PrintCLike.cpp"
  append(L" = 0");
                                                            #line 4848 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                                    }
                                                                  }
                                                                  if (isLrParser)
                                                                  {
                                                            #line 8402 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4854 "PrintCLike.cpp.template"
                                                                    if (useGlr)
                                                                    {
                                                                      if (! isCpp())
                                                                      {
                                                            #line 8410 "PrintCLike.cpp"
  append(L"thread = ");
                                                            #line 4858 "PrintCLike.cpp.template"
                                                                      }
                                                                      if (isJava())
                                                                      {
                                                                        print(className.c_str());
                                                            #line 8417 "PrintCLike.cpp"
  append(L".this.");
                                                            #line 4862 "PrintCLike.cpp.template"
                                                                      }
                                                                      else if (isCSharp() || isCpp() || isHaxe() || isScala() || isTypescript() || isGo() || isPython())
                                                                      {
                                                                        print(thiz());
                                                            #line 8424 "PrintCLike.cpp"
  append(L"parser");
                                                            #line 4866 "PrintCLike.cpp.template"
                                                                        print(arrow());
                                                                      }
                                                                    }
                                                                    else
                                                                    {
                                                                      print(thiz());
                                                                    }
                                                            #line 8434 "PrintCLike.cpp"
  append(L"parse(-1, ");
                                                            #line 4873 "PrintCLike.cpp.template"
                                                                    print(format.toString<wchar_t>(grammar->whitespace->getStateId()));
                                                                    if (tree)
                                                                    {
                                                            #line 8440 "PrintCLike.cpp"
  append(L", ");
                                                            #line 4876 "PrintCLike.cpp.template"
                                                                      print(nullPtr());
                                                                    }
                                                                    if (useGlr)
                                                                    {
                                                            #line 8447 "PrintCLike.cpp"
  append(L", thread");
                                                            #line 4880 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 8451 "PrintCLike.cpp"
  append(L")");
                                                            #line 4881 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                  }
                                                                  else
                                                                  {
                                                            #line 8458 "PrintCLike.cpp"
  append(L"\n");
  append(L"\n");
  append(L"  ");
                                                            #line 4887 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8464 "PrintCLike.cpp"
  append(L"try_");
                                                            #line 4888 "PrintCLike.cpp.template"
                                                                    print(Format::acceptableName<WString>(grammar->whitespace->name).c_str());
                                                                    if (! isScala()) print(L"()");
                                                                    print(semicolon());
                                                                  }
                                                                  if (useGlr)
                                                                  {
                                                                    if (isJavascript())
                                                                    {
                                                            #line 8475 "PrintCLike.cpp"
  append(L"\n");
  append(L"  end = thread.getEnd();");
                                                            #line 4897 "PrintCLike.cpp.template"
                                                                    }
                                                                    else if (isCpp())
                                                                    {
                                                            #line 8482 "PrintCLike.cpp"
  append(L"\n");
  append(L"  end = thread->end;\n");
  append(L"  delete thread;");
                                                            #line 4902 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 8490 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4906 "PrintCLike.cpp.template"
                                                                      if (useGlr) print(thiz());
                                                            #line 8495 "PrintCLike.cpp"
  append(L"end = thread");
                                                            #line 4907 "PrintCLike.cpp.template"
                                                                      print(arrow());
                                                            #line 8499 "PrintCLike.cpp"
  append(L"end");
                                                            #line 4908 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                                    }
                                                                  }
                                                                  else
                                                                  {
                                                            #line 8507 "PrintCLike.cpp"
  append(L"\n");
  append(L"\n");
  append(L"  ");
                                                            #line 4915 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8513 "PrintCLike.cpp"
  append(L"b0 = b0W; ");
                                                            #line 4916 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8517 "PrintCLike.cpp"
  append(L"e0 = e0W");
                                                            #line 4917 "PrintCLike.cpp.template"
                                                                    for (size_t k = 1; k < grammar->k; ++k)
                                                                    {
                                                            #line 8522 "PrintCLike.cpp"
  append(L"; ");
                                                            #line 4919 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 8526 "PrintCLike.cpp"
  append(L"l");
                                                            #line 4920 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(k));
                                                            #line 8530 "PrintCLike.cpp"
  append(L" = l");
                                                            #line 4921 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(k));
                                                            #line 8534 "PrintCLike.cpp"
  append(L"W");
                                                            #line 4922 "PrintCLike.cpp.template"
                                                                      if (isPython())
                                                                      {
                                                            #line 8539 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4925 "PrintCLike.cpp.template"
                                                                      }
                                                                      else
                                                                      {
                                                            #line 8546 "PrintCLike.cpp"
  append(L"; ");
                                                            #line 4928 "PrintCLike.cpp.template"
                                                                      }
                                                            #line 8550 "PrintCLike.cpp"
  append(L"if ");
                                                            #line 4929 "PrintCLike.cpp.template"
                                                                      print(ifLeftParen());
                                                                      print(thiz());
                                                            #line 8555 "PrintCLike.cpp"
  append(L"l");
                                                            #line 4931 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(k));
                                                            #line 8559 "PrintCLike.cpp"
  append(L" != 0");
                                                            #line 4932 "PrintCLike.cpp.template"
                                                                      print(ifRightParen());
                                                                      if (isPython())
                                                                      {
                                                                        increaseIndent();
                                                                      }
                                                                      else
                                                                      {
                                                            #line 8569 "PrintCLike.cpp"
  append(L" {");
                                                            #line 4939 "PrintCLike.cpp.template"
                                                                      }
                                                            #line 8573 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4941 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 8578 "PrintCLike.cpp"
  append(L"b");
                                                            #line 4942 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(k));
                                                            #line 8582 "PrintCLike.cpp"
  append(L" = b");
                                                            #line 4943 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(k));
                                                            #line 8586 "PrintCLike.cpp"
  append(L"W; ");
                                                            #line 4944 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 8590 "PrintCLike.cpp"
  append(L"e");
                                                            #line 4945 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(k));
                                                            #line 8594 "PrintCLike.cpp"
  append(L" = e");
                                                            #line 4946 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(k));
                                                            #line 8598 "PrintCLike.cpp"
  append(L"W");
                                                            #line 4947 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(semicolon());
                                                                    if (isPython())
                                                                    {
                                                                      decreaseIndent(grammar->k - 1);
                                                                    }
                                                                    else
                                                                    {
                                                            #line 8609 "PrintCLike.cpp"
  append(L" ");
                                                            #line 4955 "PrintCLike.cpp.template"
                                                                      for (size_t k = 1; k < grammar->k; ++k)
                                                                      {
                                                            #line 8614 "PrintCLike.cpp"
  append(L"}");
                                                            #line 4957 "PrintCLike.cpp.template"
                                                                      }
                                                                    }
                                                                  }
                                                                  print(rightBrace());
                                                            #line 8621 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4962 "PrintCLike.cpp.template"
                                                                  if (! isGo())
                                                                    decreaseIndent();
                                                                }
                                                                if (tree && ! isLrParser)
                                                                {
                                                                  if (! isGo())
                                                                    increaseIndent();
                                                                  openMethod (voidType(), L"", L"whitespace", L"");
                                                                  print(leftBrace());
                                                            #line 8633 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if ");
                                                            #line 4972 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                                  print(thiz());
                                                            #line 8639 "PrintCLike.cpp"
  append(L"e0 != ");
                                                            #line 4974 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8643 "PrintCLike.cpp"
  append(L"b1");
                                                            #line 4975 "PrintCLike.cpp.template"
                                                                  print(ifRightParen());
                                                                  increaseIndent();
                                                                  print(leftBrace());
                                                                  decreaseIndent();
                                                            #line 8650 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4980 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8655 "PrintCLike.cpp"
  append(L"eventHandler");
                                                            #line 4981 "PrintCLike.cpp.template"
                                                                  if (shiftAmbiguity && isTypescript()) print(L"!");
                                                                  print(arrow());
                                                                  if (isGo())
                                                                  {
                                                            #line 8662 "PrintCLike.cpp"
  append(L"W");
                                                            #line 4985 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 8668 "PrintCLike.cpp"
  append(L"w");
                                                            #line 4988 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 8672 "PrintCLike.cpp"
  append(L"hitespace(");
                                                            #line 4989 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8676 "PrintCLike.cpp"
  append(L"e0, ");
                                                            #line 4990 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8680 "PrintCLike.cpp"
  append(L"b1)");
                                                            #line 4991 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                            #line 8684 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4993 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8689 "PrintCLike.cpp"
  append(L"e0 = ");
                                                            #line 4994 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8693 "PrintCLike.cpp"
  append(L"b1");
                                                            #line 4995 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                  increaseIndent();
                                                                  print(rightBrace());
                                                                  decreaseIndent();
                                                                  print(rightBrace());
                                                                  if (! isGo())
                                                                    decreaseIndent();
                                                            #line 8703 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5003 "PrintCLike.cpp.template"
                                                                }
                                                                if (! isGo())
                                                                  increaseIndent();
                                                                openMethod(intType(), L"", L"matchW", L"int tokenSetId", false, useGlr ? L"ParsingThread" : className.c_str());
                                                                print(leftBrace());
                                                                if (isScala())
                                                                {
                                                            #line 8713 "PrintCLike.cpp"
  append(L"\n");
  append(L"  var continue = true\n");
  append(L"  var code = 0\n");
  append(L"  while (continue) {\n");
  append(L"    code = matcher(tokenSetId)");
                                                            #line 5014 "PrintCLike.cpp.template"
                                                                  increaseIndent(2);
                                                                }
                                                                else
                                                                {
                                                                  if (! isPython())
                                                                  {
                                                            #line 8726 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5021 "PrintCLike.cpp.template"
                                                                    print((isJavascript() || isTypescript() || isHaxe() || isGo()) ? L"var" : L"int");
                                                            #line 8731 "PrintCLike.cpp"
  append(L" code");
                                                            #line 5022 "PrintCLike.cpp.template"
                                                                    if (isTypescript())
                                                                    {
                                                            #line 8736 "PrintCLike.cpp"
  append(L": number");
                                                            #line 5024 "PrintCLike.cpp.template"
                                                                    }
                                                                    else if (isGo())
                                                                    {
                                                            #line 8742 "PrintCLike.cpp"
  append(L" int");
                                                            #line 5027 "PrintCLike.cpp.template"
                                                                    }
                                                                    if (isHaxe())
                                                                    {
                                                            #line 8748 "PrintCLike.cpp"
  append(L" = 0");
                                                            #line 5030 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(semicolon());
                                                                  }
                                                                  if (isHaxe() || isPython())
                                                                  {
                                                            #line 8756 "PrintCLike.cpp"
  append(L"\n");
  append(L"  while ");
                                                            #line 5036 "PrintCLike.cpp.template"
                                                                    print(ifLeftParen());
                                                                    print(isPython() ? L"T" : L"t");
                                                            #line 8762 "PrintCLike.cpp"
  append(L"rue");
                                                            #line 5038 "PrintCLike.cpp.template"
                                                                    print(ifRightParen());
                                                                  }
                                                                  else
                                                                  {
                                                            #line 8769 "PrintCLike.cpp"
  append(L"\n");
  append(L"  for");
                                                            #line 5043 "PrintCLike.cpp.template"
                                                                    if (! isGo())
                                                                    {
                                                            #line 8775 "PrintCLike.cpp"
  append(L" (;;)");
                                                            #line 5045 "PrintCLike.cpp.template"
                                                                    }
                                                                  }
                                                                  increaseIndent();
                                                                  print(leftBrace());
                                                                  increaseIndent();
                                                            #line 8783 "PrintCLike.cpp"
  append(L"\n");
  append(L"code = ");
                                                            #line 5051 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8788 "PrintCLike.cpp"
  append(L"match(tokenSetId)");
                                                            #line 5052 "PrintCLike.cpp.template"
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
                                                            #line 8817 "PrintCLike.cpp"
  append(L"\n");
  append(L"  continue = false\n");
  append(L"}\n");
  append(L"else {\n");
  append(L"  ");
                                                            #line 5082 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8825 "PrintCLike.cpp"
  append(L"skip(code)\n");
  append(L"}");
                                                            #line 5084 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 8832 "PrintCLike.cpp"
  append(L"\n");
  append(L"  break");
                                                            #line 5088 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                    print(rightBrace());
                                                            #line 8838 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5091 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8842 "PrintCLike.cpp"
  append(L"skip(code);");
                                                            #line 5092 "PrintCLike.cpp.template"
                                                                  }
                                                                }
                                                                else if (isScala())
                                                                {
                                                            #line 8849 "PrintCLike.cpp"
  append(L"\n");
  append(L"continue = false");
                                                            #line 5097 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 8856 "PrintCLike.cpp"
  append(L"\n");
  append(L"break");
                                                            #line 5101 "PrintCLike.cpp.template"
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
                                                            #line 8870 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5112 "PrintCLike.cpp.template"
                                                                if (! isScala())
                                                                {
                                                            #line 8876 "PrintCLike.cpp"
  append(L"return ");
                                                            #line 5114 "PrintCLike.cpp.template"
                                                                }
                                                            #line 8880 "PrintCLike.cpp"
  append(L"code");
                                                            #line 5115 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                print(rightBrace());
                                                            #line 8885 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5118 "PrintCLike.cpp.template"
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
                                                            #line 8901 "PrintCLike.cpp"
  append(L"\n");
  append(L"def parse(): Unit = {\n");
  append(L"  parse_");
                                                            #line 5133 "PrintCLike.cpp.template"
                                                                  print(Format::acceptableName<WString>(grammar->startSymbol()->name).c_str());
                                                            #line 8907 "PrintCLike.cpp"
  append(L"()\n");
  append(L"}\n");
                                                            #line 5136 "PrintCLike.cpp.template"
                                                                }
                                                                if (memoization)
                                                                {
                                                                  int bits = Math::bits(grammar->conflictCount);
                                                            #line 8915 "PrintCLike.cpp"
  append(L"\n");
  append(L"private def memoize(i: Int, e: Int, v: Int): Unit = {\n");
  append(L"  memo.put((e << ");
                                                            #line 5142 "PrintCLike.cpp.template"
                                                                  print(format.toString<wchar_t>(bits));
                                                            #line 8921 "PrintCLike.cpp"
  append(L") + i, v)\n");
  append(L"}\n");
  append(L"\n");
  append(L"private def memoized(i: Int, e: Int) = {\n");
  append(L"  memo.getOrElse((e << ");
                                                            #line 5147 "PrintCLike.cpp.template"
                                                                  print(format.toString<wchar_t>(bits));
                                                            #line 8929 "PrintCLike.cpp"
  append(L") + i, 0)\n");
  append(L"}\n");
                                                            #line 5150 "PrintCLike.cpp.template"
                                                                }
                                                            #line 8934 "PrintCLike.cpp"
  append(L"\n");
  append(L"def error(b: Int, e: Int, s: Int, l: Int, t: Int): Int = {");
                                                            #line 5152 "PrintCLike.cpp.template"
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
                                                            #line 8948 "PrintCLike.cpp"
  append(L"\n");
  append(L"if ");
                                                            #line 5163 "PrintCLike.cpp.template"
                                                                print(ifLeftParen());
                                                                if (grammar->noThrow)
                                                                {
                                                                  print(thiz());
                                                            #line 8956 "PrintCLike.cpp"
  append(L"viable ");
                                                            #line 5167 "PrintCLike.cpp.template"
                                                                  if (isPython())
                                                                  {
                                                            #line 8961 "PrintCLike.cpp"
  append(L"and");
                                                            #line 5169 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 8967 "PrintCLike.cpp"
  append(L"&&");
                                                            #line 5172 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 8971 "PrintCLike.cpp"
  append(L" ");
                                                            #line 5173 "PrintCLike.cpp.template"
                                                                }
                                                            #line 8975 "PrintCLike.cpp"
  append(L"e >= ");
                                                            #line 5174 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 8979 "PrintCLike.cpp"
  append(L"ex");
                                                            #line 5175 "PrintCLike.cpp.template"
                                                                print(ifRightParen());
                                                                print(leftBrace());
                                                            #line 8984 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5178 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 8989 "PrintCLike.cpp"
  append(L"bx = b");
                                                            #line 5179 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 8993 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5181 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 8998 "PrintCLike.cpp"
  append(L"ex = e");
                                                            #line 5182 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 9002 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5184 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 9007 "PrintCLike.cpp"
  append(L"sx = s");
                                                            #line 5185 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 9011 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5187 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 9016 "PrintCLike.cpp"
  append(L"lx = l");
                                                            #line 5188 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 9020 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5190 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 9025 "PrintCLike.cpp"
  append(L"tx = t");
                                                            #line 5191 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                print(rightBrace());
                                                                decreaseIndent();
                                                                if (grammar->noThrow)
                                                                {
                                                            #line 9033 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5197 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 9038 "PrintCLike.cpp"
  append(L"viable = ");
                                                            #line 5198 "PrintCLike.cpp.template"
                                                                  if (isPython())
                                                                  {
                                                            #line 9043 "PrintCLike.cpp"
  append(L"F");
                                                            #line 5200 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 9049 "PrintCLike.cpp"
  append(L"f");
                                                            #line 5203 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 9053 "PrintCLike.cpp"
  append(L"alse");
                                                            #line 5204 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                            #line 9057 "PrintCLike.cpp"
  append(L"\n");
  append(L"  return -s");
                                                            #line 5206 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                                else
                                                                {
                                                                  printFlush(1, true);
                                                            #line 9066 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5212 "PrintCLike.cpp.template"
                                                                  print(beginThrowStmt());
                                                                  print(thiz());
                                                            #line 9072 "PrintCLike.cpp"
  append(L"bx, ");
                                                            #line 5214 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 9076 "PrintCLike.cpp"
  append(L"ex, ");
                                                            #line 5215 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 9080 "PrintCLike.cpp"
  append(L"sx, ");
                                                            #line 5216 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 9084 "PrintCLike.cpp"
  append(L"lx, ");
                                                            #line 5217 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 9088 "PrintCLike.cpp"
  append(L"tx");
                                                            #line 5218 "PrintCLike.cpp.template"
                                                                  print(endThrowStmt());
                                                                  print(semicolon());
                                                                }
                                                              }
                                                              else
                                                              {
                                                                printFlush(1, true);
                                                            #line 9098 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5226 "PrintCLike.cpp.template"
                                                                if (isGo())
                                                                {
                                                            #line 9104 "PrintCLike.cpp"
  append(L"panic(&ParseError{b, e, s, l, t");
                                                            #line 5228 "PrintCLike.cpp.template"
                                                                  if (rejectsAmbiguity())
                                                                  {
                                                            #line 9109 "PrintCLike.cpp"
  append(L", false");
                                                            #line 5230 "PrintCLike.cpp.template"
                                                                    if (tree)
                                                                    {
                                                            #line 9114 "PrintCLike.cpp"
  append(L", nil");
                                                            #line 5232 "PrintCLike.cpp.template"
                                                                    }
                                                                  }
                                                            #line 9119 "PrintCLike.cpp"
  append(L"})");
                                                            #line 5234 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                                  print(beginThrowStmt());
                                                            #line 9126 "PrintCLike.cpp"
  append(L"b, e, s, l, t");
                                                            #line 5238 "PrintCLike.cpp.template"
                                                                  print(endThrowStmt());
                                                                  print(semicolon());
                                                                }
                                                              }
                                                              print(rightBrace());
                                                            #line 9134 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5244 "PrintCLike.cpp.template"
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
                                                            #line 9149 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5258 "PrintCLike.cpp.template"
                                                              print(thiz());
                                                            #line 9154 "PrintCLike.cpp"
  append(L"stack = ");
                                                            #line 5259 "PrintCLike.cpp.template"
                                                              if (isGo())
                                                              {
                                                            #line 9159 "PrintCLike.cpp"
  append(L"&StackNode{");
                                                            #line 5261 "PrintCLike.cpp.template"
                                                              }
                                                              else
                                                              {
                                                                if (! isPython())
                                                                {
                                                            #line 9167 "PrintCLike.cpp"
  append(L"new ");
                                                            #line 5266 "PrintCLike.cpp.template"
                                                                }
                                                                if (! isHaxe() && ! isTypescript()) print(staticPrefix());
                                                            #line 9172 "PrintCLike.cpp"
  append(L"StackNode(");
                                                            #line 5268 "PrintCLike.cpp.template"
                                                              }
                                                              print(thiz());
                                                            #line 9177 "PrintCLike.cpp"
  append(L"state, ");
                                                            #line 5270 "PrintCLike.cpp.template"
                                                              if (grammar->states->hasLookback)
                                                              {
                                                            #line 9182 "PrintCLike.cpp"
  append(L"lookback, ");
                                                            #line 5272 "PrintCLike.cpp.template"
                                                              }
                                                            #line 9186 "PrintCLike.cpp"
  append(L"pos, ");
                                                            #line 5273 "PrintCLike.cpp.template"
                                                              print(thiz());
                                                            #line 9190 "PrintCLike.cpp"
  append(L"stack");
                                                            #line 5274 "PrintCLike.cpp.template"
                                                              print(isGo() ? L"}" : L")");
                                                              print(semicolon());
                                                            #line 9195 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5277 "PrintCLike.cpp.template"
                                                              print(thiz());
                                                            #line 9200 "PrintCLike.cpp"
  append(L"state = shift");
                                                            #line 5278 "PrintCLike.cpp.template"
                                                              print(semicolon());
                                                            }

                                                            void PrintCLike::printStackPop()
                                                            {
                                                              Trace("PrintCLike::printStackPop");
                                                            #line 9209 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 5286 "PrintCLike.cpp.template"
                                                              print(intVar());
                                                            #line 9214 "PrintCLike.cpp"
  append(L"n");
                                                            #line 5287 "PrintCLike.cpp.template"
                                                              print(assign());
                                                            #line 9218 "PrintCLike.cpp"
  append(L"symbols");
                                                            #line 5288 "PrintCLike.cpp.template"
                                                              print(semicolon());
                                                            #line 9222 "PrintCLike.cpp"
  append(L"\n");
  append(L"    if ");
                                                            #line 5290 "PrintCLike.cpp.template"
                                                              print(ifLeftParen());
                                                            #line 9227 "PrintCLike.cpp"
  append(L"shift >= 0");
                                                            #line 5291 "PrintCLike.cpp.template"
                                                              print(ifRightParen());
                                                              printIndented(2, leftBrace());
                                                            #line 9232 "PrintCLike.cpp"
  append(L"\n");
  append(L"      n -= 1");
                                                            #line 5294 "PrintCLike.cpp.template"
                                                              print(semicolon());
                                                              printIndented(2, rightBrace());
                                                            #line 9238 "PrintCLike.cpp"
  append(L"\n");
  append(L"    if ");
                                                            #line 5297 "PrintCLike.cpp.template"
                                                              print(ifLeftParen());
                                                            #line 9243 "PrintCLike.cpp"
  append(L"n > 0");
                                                            #line 5298 "PrintCLike.cpp.template"
                                                              print(ifRightParen());
                                                              printIndented(2, leftBrace());
                                                              if (isCpp())
                                                              {
                                                            #line 9250 "PrintCLike.cpp"
  append(L"\n");
  append(L"      stack = stack->pop(n - 1);\n");
  append(L"      state = stack->state;");
                                                            #line 5304 "PrintCLike.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 9257 "PrintCLike.cpp"
  append(L"\n");
  append(L"      bs = stack->pos;");
                                                            #line 5307 "PrintCLike.cpp.template"
                                                                }
                                                            #line 9262 "PrintCLike.cpp"
  append(L"\n");
  append(L"      stack = stack->pop(1);");
                                                            #line 5309 "PrintCLike.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 9269 "PrintCLike.cpp"
  append(L"\n");
  append(L"      ");
                                                            #line 5313 "PrintCLike.cpp.template"
                                                                if (isHaxe())
                                                                {
                                                            #line 9275 "PrintCLike.cpp"
  append(L"for (i in 1...n)");
                                                            #line 5315 "PrintCLike.cpp.template"
                                                                }
                                                                else if (isScala())
                                                                {
                                                            #line 9281 "PrintCLike.cpp"
  append(L"for (i <- 2 to n)");
                                                            #line 5318 "PrintCLike.cpp.template"
                                                                }
                                                                else if (isPython())
                                                                {
                                                            #line 9287 "PrintCLike.cpp"
  append(L"for _ in range(n - 1):");
                                                            #line 5321 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 9293 "PrintCLike.cpp"
  append(L"for ");
                                                            #line 5324 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                                  print(intVar());
                                                            #line 9298 "PrintCLike.cpp"
  append(L"i");
                                                            #line 5326 "PrintCLike.cpp.template"
                                                                  print(assign());
                                                            #line 9302 "PrintCLike.cpp"
  append(L"1; i < n; i++");
                                                            #line 5327 "PrintCLike.cpp.template"
                                                                  print(ifRightParen());
                                                                }
                                                                printIndented(3, leftBrace());
                                                            #line 9308 "PrintCLike.cpp"
  append(L"\n");
  append(L"        ");
                                                            #line 5331 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 9313 "PrintCLike.cpp"
  append(L"stack = ");
                                                            #line 5332 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 9317 "PrintCLike.cpp"
  append(L"stack.link");
                                                            #line 5333 "PrintCLike.cpp.template"
                                                                if (isTypescript()) print(L"!");
                                                                print(semicolon());
                                                                printIndented(3, rightBrace());
                                                            #line 9323 "PrintCLike.cpp"
  append(L"\n");
  append(L"      ");
                                                            #line 5337 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 9328 "PrintCLike.cpp"
  append(L"state = ");
                                                            #line 5338 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 9332 "PrintCLike.cpp"
  append(L"stack");
                                                            #line 5339 "PrintCLike.cpp.template"
                                                                print(arrow());
                                                            #line 9336 "PrintCLike.cpp"
  append(L"state");
                                                            #line 5340 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                if (tree)
                                                                {
                                                            #line 9342 "PrintCLike.cpp"
  append(L"\n");
  append(L"      ");
                                                            #line 5344 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 9347 "PrintCLike.cpp"
  append(L"bs = ");
                                                            #line 5345 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 9351 "PrintCLike.cpp"
  append(L"stack");
                                                            #line 5346 "PrintCLike.cpp.template"
                                                                  print(arrow());
                                                            #line 9355 "PrintCLike.cpp"
  append(L"pos");
                                                            #line 5347 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                            #line 9360 "PrintCLike.cpp"
  append(L"\n");
  append(L"      ");
                                                            #line 5350 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 9365 "PrintCLike.cpp"
  append(L"stack = ");
                                                            #line 5351 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 9369 "PrintCLike.cpp"
  append(L"stack.link");
                                                            #line 5352 "PrintCLike.cpp.template"
                                                                if (isTypescript()) print(L"!");
                                                                print(semicolon());
                                                              }
                                                              if (tree)
                                                              {
                                                            #line 9377 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 5358 "PrintCLike.cpp.template"
                                                                printIndented(2, elseWithBraces());
                                                            #line 9382 "PrintCLike.cpp"
  append(L"\n");
  append(L"      ");
                                                            #line 5360 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 9387 "PrintCLike.cpp"
  append(L"bs = pos");
                                                            #line 5361 "PrintCLike.cpp.template"
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
                                                            #line 9406 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5378 "PrintCLike.cpp.template"
                                                                openMethod(intType(), L"", L"lookback", L"int x, int y", false, clazz);
                                                                const wchar_t *lookback = isGo() ? L"lookback" : L"LOOKBACK";
                                                                print(leftBrace());
                                                                increaseIndent();
                                                                if (isGo())
                                                                {
                                                            #line 9415 "PrintCLike.cpp"
  append(L"\n");
  append(L"i := lookback[y]\n");
  append(L"l := lookback[i]\n");
  append(L"for l > x {");
                                                            #line 5387 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 9424 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5391 "PrintCLike.cpp.template"
                                                                  print(intVar());
                                                            #line 9428 "PrintCLike.cpp"
  append(L"i");
                                                            #line 5392 "PrintCLike.cpp.template"
                                                                  print(assign());
                                                                  print(staticPrefix());
                                                                  print(lookback);
                                                                  print(leftbracket());
                                                            #line 9435 "PrintCLike.cpp"
  append(L"y");
                                                            #line 5396 "PrintCLike.cpp.template"
                                                                  print(rightbracket());
                                                                  print(semicolon());
                                                            #line 9440 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5399 "PrintCLike.cpp.template"
                                                                  print(intVar());
                                                            #line 9444 "PrintCLike.cpp"
  append(L"l");
                                                            #line 5400 "PrintCLike.cpp.template"
                                                                  print(assign());
                                                                  print(staticPrefix());
                                                                  print(lookback);
                                                                  print(leftbracket());
                                                            #line 9451 "PrintCLike.cpp"
  append(L"i");
                                                            #line 5404 "PrintCLike.cpp.template"
                                                                  print(rightbracket());
                                                                  print(semicolon());
                                                            #line 9456 "PrintCLike.cpp"
  append(L"\n");
  append(L"while ");
                                                            #line 5407 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                            #line 9461 "PrintCLike.cpp"
  append(L"l > x");
                                                            #line 5408 "PrintCLike.cpp.template"
                                                                  print(ifRightParen());
                                                                  print(leftBrace());
                                                                }
                                                            #line 9467 "PrintCLike.cpp"
  append(L"\n");
  append(L"  i += 2");
                                                            #line 5412 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 9472 "PrintCLike.cpp"
  append(L"\n");
  append(L"  l = ");
                                                            #line 5414 "PrintCLike.cpp.template"
                                                                print(staticPrefix());
                                                                print(lookback);
                                                                print(leftbracket());
                                                            #line 9479 "PrintCLike.cpp"
  append(L"i");
                                                            #line 5417 "PrintCLike.cpp.template"
                                                                print(rightbracket());
                                                                print(semicolon());
                                                                print(rightBrace());
                                                            #line 9485 "PrintCLike.cpp"
  append(L"\n");
  append(L"if ");
                                                            #line 5421 "PrintCLike.cpp.template"
                                                                print(ifLeftParen());
                                                            #line 9490 "PrintCLike.cpp"
  append(L"l < x");
                                                            #line 5422 "PrintCLike.cpp.template"
                                                                print(ifRightParen());
                                                                print(leftBrace());
                                                            #line 9495 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5425 "PrintCLike.cpp.template"
                                                                print(returnKeyword());
                                                            #line 9500 "PrintCLike.cpp"
  append(L"0");
                                                            #line 5426 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 9504 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5428 "PrintCLike.cpp.template"
                                                                print(elseWithBraces());
                                                            #line 9508 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5430 "PrintCLike.cpp.template"
                                                                print(returnKeyword());
                                                                print(staticPrefix());
                                                                print(lookback);
                                                                print(leftbracket());
                                                            #line 9516 "PrintCLike.cpp"
  append(L"i + 1");
                                                            #line 5434 "PrintCLike.cpp.template"
                                                                print(rightbracket());
                                                                print(semicolon());
                                                                print(rightBrace());
                                                                decreaseIndent();
                                                                print(rightBrace());
                                                            #line 9524 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5440 "PrintCLike.cpp.template"
                                                                if (isJavascript() && useGlr)
                                                                {
                                                            #line 9529 "PrintCLike.cpp"
  append(L"\n");
  append(L"this.count = function(code)\n");
                                                            #line 5444 "PrintCLike.cpp.template"
                                                                }
                                                                else if (isTypescript() && useGlr)
                                                                {
                                                            #line 9536 "PrintCLike.cpp"
  append(L"\n");
  append(L"public count(code: number)\n");
                                                            #line 5449 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                                  openMethod(intType(), L"", L"count", L"int code", false, clazz);
                                                                }
                                                                print(leftBrace());
                                                                increaseIndent();
                                                            #line 9547 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5457 "PrintCLike.cpp.template"
                                                                print(intVar());
                                                            #line 9551 "PrintCLike.cpp"
  append(L"count");
                                                            #line 5458 "PrintCLike.cpp.template"
                                                                print(assign());
                                                            #line 9555 "PrintCLike.cpp"
  append(L"0");
                                                            #line 5459 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                int stackElementSize = tree ? 3 : 2;
                                                                if (isHaxe() || isScala())
                                                                {
                                                                  if (useGlr)
                                                                  {
                                                            #line 9564 "PrintCLike.cpp"
  append(L"\n");
  append(L"var node = this");
                                                            #line 5466 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                    if (isScala())
                                                                    {
                                                            #line 9571 "PrintCLike.cpp"
  append(L"\n");
  append(L"var c = code");
                                                            #line 5470 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 9576 "PrintCLike.cpp"
  append(L"\n");
  append(L"while ");
                                                            #line 5472 "PrintCLike.cpp.template"
                                                                    print(ifLeftParen());
                                                            #line 9581 "PrintCLike.cpp"
  append(L"node.state >= 0");
                                                            #line 5473 "PrintCLike.cpp.template"
                                                                    print(ifRightParen());
                                                                    print(leftBrace());
                                                                    if (isScala())
                                                                    {
                                                            #line 9588 "PrintCLike.cpp"
  append(L"\n");
  append(L"  c = lookback(node.code, c)\n");
  append(L"  if (c == 0) return count\n");
  append(L"  count += 1");
                                                            #line 5480 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 9597 "PrintCLike.cpp"
  append(L"\n");
  append(L"  code = lookback(node.code, code);\n");
  append(L"  if ");
                                                            #line 5485 "PrintCLike.cpp.template"
                                                                      print(ifLeftParen());
                                                            #line 9603 "PrintCLike.cpp"
  append(L"code == 0");
                                                            #line 5486 "PrintCLike.cpp.template"
                                                                      print(ifRightParen());
                                                            #line 9607 "PrintCLike.cpp"
  append(L"\n");
  append(L"    break");
                                                            #line 5489 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                            #line 9612 "PrintCLike.cpp"
  append(L"\n");
  append(L"  count++");
                                                            #line 5491 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                                    }
                                                            #line 9618 "PrintCLike.cpp"
  append(L"\n");
  append(L"  node = node.link");
                                                            #line 5494 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                  }
                                                                  else
                                                                  {
                                                            #line 9626 "PrintCLike.cpp"
  append(L"\n");
  append(L"var t = top");
                                                            #line 5499 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 9631 "PrintCLike.cpp"
  append(L"\n");
  append(L"var c = code");
                                                            #line 5501 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 9636 "PrintCLike.cpp"
  append(L"\n");
  append(L"while (t >= 0)");
                                                            #line 5503 "PrintCLike.cpp.template"
                                                                    print(leftBrace());
                                                            #line 9641 "PrintCLike.cpp"
  append(L"\n");
  append(L"  c = lookback(iStack");
                                                            #line 5505 "PrintCLike.cpp.template"
                                                                    print(leftbracket());
                                                            #line 9646 "PrintCLike.cpp"
  append(L"t");
                                                            #line 5506 "PrintCLike.cpp.template"
                                                                    print(rightbracket());
                                                            #line 9650 "PrintCLike.cpp"
  append(L", c)");
                                                            #line 5507 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 9654 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if ");
                                                            #line 5509 "PrintCLike.cpp.template"
                                                                    print(ifLeftParen());
                                                            #line 9659 "PrintCLike.cpp"
  append(L"c == 0");
                                                            #line 5510 "PrintCLike.cpp.template"
                                                                    print(ifRightParen());
                                                            #line 9663 "PrintCLike.cpp"
  append(L" return count");
                                                            #line 5511 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 9667 "PrintCLike.cpp"
  append(L"\n");
  append(L"  count += 1");
                                                            #line 5513 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 9672 "PrintCLike.cpp"
  append(L"\n");
  append(L"  t -= ");
                                                            #line 5515 "PrintCLike.cpp.template"
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
                                                            #line 9686 "PrintCLike.cpp"
  append(L"\n");
  append(L"node = self\n");
  append(L"while ");
                                                            #line 5527 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 9694 "PrintCLike.cpp"
  append(L"\n");
  append(L"for ");
                                                            #line 5531 "PrintCLike.cpp.template"
                                                                      print(ifLeftParen());
                                                                      if (isJavascript() || isTypescript())
                                                                      {
                                                            #line 9701 "PrintCLike.cpp"
  append(L"var ");
                                                            #line 5534 "PrintCLike.cpp.template"
                                                                      }
                                                                      else if (!isGo())
                                                                      {
                                                            #line 9707 "PrintCLike.cpp"
  append(L"StackNode ");
                                                            #line 5537 "PrintCLike.cpp.template"
                                                                      }
                                                                      if (isCpp()) print(L"*");
                                                            #line 9712 "PrintCLike.cpp"
  append(L"node");
                                                            #line 5539 "PrintCLike.cpp.template"
                                                                      if (isTypescript())
                                                                      {
                                                            #line 9717 "PrintCLike.cpp"
  append(L": StackNode | null");
                                                            #line 5541 "PrintCLike.cpp.template"
                                                                      }
                                                                      print(assign());
                                                            #line 9722 "PrintCLike.cpp"
  append(L"this; ");
                                                            #line 5543 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 9726 "PrintCLike.cpp"
  append(L"node");
                                                            #line 5544 "PrintCLike.cpp.template"
                                                                    if (isTypescript()) print(L"!");
                                                                    print(arrow());
                                                            #line 9731 "PrintCLike.cpp"
  append(L"state >= 0");
                                                            #line 5546 "PrintCLike.cpp.template"
                                                                    if (isPython())
                                                                    {
                                                            #line 9736 "PrintCLike.cpp"
  append(L":");
                                                            #line 5548 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 9742 "PrintCLike.cpp"
  append(L"; node = node");
                                                            #line 5551 "PrintCLike.cpp.template"
                                                                      if (isTypescript()) print(L"!");
                                                                      print(arrow());
                                                            #line 9747 "PrintCLike.cpp"
  append(L"link");
                                                            #line 5553 "PrintCLike.cpp.template"
                                                                      print(ifRightParen());
                                                                    }
                                                                    print(leftBrace());
                                                            #line 9753 "PrintCLike.cpp"
  append(L"\n");
  append(L"  code = ");
                                                            #line 5557 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                                    print(isGo() ? L"L" : L"l");
                                                            #line 9759 "PrintCLike.cpp"
  append(L"ookback(node");
                                                            #line 5559 "PrintCLike.cpp.template"
                                                                    if (isTypescript()) print(L"!");
                                                                    print(arrow());
                                                            #line 9764 "PrintCLike.cpp"
  append(L"code, code)");
                                                            #line 5561 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                  }
                                                                  else
                                                                  {
                                                                    if (isPython())
                                                                    {
                                                            #line 9773 "PrintCLike.cpp"
  append(L"\n");
  append(L"t");
                                                            #line 5568 "PrintCLike.cpp.template"
                                                                      print(assign());
                                                                      print(thiz());
                                                            #line 9779 "PrintCLike.cpp"
  append(L"top");
                                                            #line 5570 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                            #line 9783 "PrintCLike.cpp"
  append(L"\n");
  append(L"while ");
                                                            #line 5572 "PrintCLike.cpp.template"
                                                                      print(ifLeftParen());
                                                                      print(intVar());
                                                            #line 9789 "PrintCLike.cpp"
  append(L"t >= 0");
                                                            #line 5574 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 9795 "PrintCLike.cpp"
  append(L"\n");
  append(L"for ");
                                                            #line 5578 "PrintCLike.cpp.template"
                                                                      print(ifLeftParen());
                                                                      print(intVar());
                                                            #line 9801 "PrintCLike.cpp"
  append(L"t");
                                                            #line 5580 "PrintCLike.cpp.template"
                                                                      print(assign());
                                                                      print(thiz());
                                                            #line 9806 "PrintCLike.cpp"
  append(L"top; t >= 0; t -= ");
                                                            #line 5582 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(stackElementSize));
                                                                    }
                                                                    print(ifRightParen());
                                                                    print(leftBrace());
                                                            #line 9813 "PrintCLike.cpp"
  append(L"\n");
  append(L"  code = ");
                                                            #line 5587 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 9818 "PrintCLike.cpp"
  append(L"lookback(");
                                                            #line 5588 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 9822 "PrintCLike.cpp"
  append(L"iStack[t], code)");
                                                            #line 5589 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                  }
                                                            #line 9827 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if ");
                                                            #line 5592 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                            #line 9832 "PrintCLike.cpp"
  append(L"code == 0");
                                                            #line 5593 "PrintCLike.cpp.template"
                                                                  print(ifRightParen());
                                                                  increaseIndent();
                                                                  print(leftBrace());
                                                            #line 9838 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5597 "PrintCLike.cpp.template"
                                                                  if (! isHaxe() && ! isScala())
                                                                  {
                                                            #line 9844 "PrintCLike.cpp"
  append(L"break");
                                                            #line 5599 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 9850 "PrintCLike.cpp"
  append(L"return count");
                                                            #line 5602 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(semicolon());
                                                                  print(rightBrace());
                                                                  decreaseIndent();
                                                            #line 9857 "PrintCLike.cpp"
  append(L"\n");
  append(L"  count += 1");
                                                            #line 5607 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                  if (isPython())
                                                                  {
                                                                    if (useGlr)
                                                                    {
                                                            #line 9866 "PrintCLike.cpp"
  append(L"\n");
  append(L"  node = node.link");
                                                            #line 5613 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 9873 "PrintCLike.cpp"
  append(L"\n");
  append(L"  t -= ");
                                                            #line 5617 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(stackElementSize));
                                                                    }
                                                                  }
                                                                }
                                                                print(rightBrace());
                                                            #line 9882 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5623 "PrintCLike.cpp.template"
                                                                print(returnKeyword());
                                                            #line 9886 "PrintCLike.cpp"
  append(L"count");
                                                            #line 5624 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                decreaseIndent();
                                                                print(rightBrace());
                                                                if (isJavascript() && useGlr)
                                                                {
                                                            #line 9894 "PrintCLike.cpp"
  append(L";");
                                                            #line 5629 "PrintCLike.cpp.template"
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
                                                            #line 9920 "PrintCLike.cpp"
  append(L"\n");
  append(L"if ");
                                                            #line 5653 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                                  print(thiz());
                                                            #line 9926 "PrintCLike.cpp"
  append(L"l");
                                                            #line 5655 "PrintCLike.cpp.template"
                                                                  print(kAsString);
                                                            #line 9930 "PrintCLike.cpp"
  append(L" == 0");
                                                            #line 5656 "PrintCLike.cpp.template"
                                                                  print(ifRightParen());
                                                                  print(leftBrace());
                                                            #line 9935 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5659 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 9940 "PrintCLike.cpp"
  append(L"l");
                                                            #line 5660 "PrintCLike.cpp.template"
                                                                  print(kAsString);
                                                            #line 9944 "PrintCLike.cpp"
  append(L" = ");
                                                            #line 5661 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 9948 "PrintCLike.cpp"
  append(L"match");
                                                            #line 5662 "PrintCLike.cpp.template"
                                                                  if (withWhitespace)
                                                                  {
                                                            #line 9953 "PrintCLike.cpp"
  append(L"W");
                                                            #line 5664 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isScala())
                                                                  {
                                                            #line 9959 "PrintCLike.cpp"
  append(L"er");
                                                            #line 5667 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 9963 "PrintCLike.cpp"
  append(L"(tokenSetId)");
                                                            #line 5668 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                            #line 9967 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5670 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 9972 "PrintCLike.cpp"
  append(L"b");
                                                            #line 5671 "PrintCLike.cpp.template"
                                                                  print(kAsString);
                                                            #line 9976 "PrintCLike.cpp"
  append(L" = ");
                                                            #line 5672 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 9980 "PrintCLike.cpp"
  append(L"begin");
                                                            #line 5673 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                            #line 9984 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5675 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 9989 "PrintCLike.cpp"
  append(L"e");
                                                            #line 5676 "PrintCLike.cpp.template"
                                                                  print(kAsString);
                                                            #line 9993 "PrintCLike.cpp"
  append(L" = ");
                                                            #line 5677 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 9997 "PrintCLike.cpp"
  append(L"end");
                                                            #line 5678 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                  print(rightBrace());
                                                                  if (unlimitedLookahead)
                                                                  {
                                                                    if (k >= 2)
                                                                    {
                                                            #line 10006 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5685 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 10010 "PrintCLike.cpp"
  append(L"lk = prefix + ");
                                                            #line 5686 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 10014 "PrintCLike.cpp"
  append(L"l");
                                                            #line 5687 "PrintCLike.cpp.template"
                                                                      print(kAsString);
                                                                      print(semicolon());
                                                                    }
                                                                  }
                                                                  else
                                                                  {
                                                                    if (k == 2)
                                                                    {
                                                            #line 10025 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5696 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 10029 "PrintCLike.cpp"
  append(L"lk = (");
                                                            #line 5697 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 10033 "PrintCLike.cpp"
  append(L"l2 << ");
                                                            #line 5698 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(grammar->tokenSequenceFactory->tokenBits()));
                                                            #line 10037 "PrintCLike.cpp"
  append(L") | ");
                                                            #line 5699 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 10041 "PrintCLike.cpp"
  append(L"l1");
                                                            #line 5700 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                                    }
                                                                    else if (k > 2)
                                                                    {
                                                            #line 10048 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5705 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 10052 "PrintCLike.cpp"
  append(L"lk |= ");
                                                            #line 5706 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 10056 "PrintCLike.cpp"
  append(L"l");
                                                            #line 5707 "PrintCLike.cpp.template"
                                                                      print(kAsString);
                                                            #line 10060 "PrintCLike.cpp"
  append(L" << ");
                                                            #line 5708 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>((k - 1) * grammar->tokenSequenceFactory->tokenBits()));
                                                                      print(semicolon());
                                                                    }
                                                                  }
                                                                  decreaseIndent();
                                                                  print(rightBrace());
                                                            #line 10069 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5715 "PrintCLike.cpp.template"
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
                                                            #line 10097 "PrintCLike.cpp"
  append(L"\n");
  append(L"  return ");
                                                            #line 5741 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                                if (useGlr && (isCSharp() || isCpp() || isHaxe() || isScala() || isTypescript()))
                                                                {
                                                            #line 10104 "PrintCLike.cpp"
  append(L"parser");
                                                            #line 5744 "PrintCLike.cpp.template"
                                                                  print(arrow());
                                                                }
                                                            #line 10109 "PrintCLike.cpp"
  append(L"input");
                                                            #line 5746 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                print(rightBrace());
                                                                if (isJavascript())
                                                                {
                                                            #line 10116 "PrintCLike.cpp"
  append(L";");
                                                            #line 5750 "PrintCLike.cpp.template"
                                                                }
                                                            #line 10120 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5752 "PrintCLike.cpp.template"
                                                                openMethod(intType(), L"", L"getTokenOffset", L"", true);
                                                                print(leftBrace());
                                                            #line 10125 "PrintCLike.cpp"
  append(L"\n");
  append(L"  return ");
                                                            #line 5755 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 10130 "PrintCLike.cpp"
  append(L"b0");
                                                            #line 5756 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                print(rightBrace());
                                                                if (isJavascript())
                                                                {
                                                            #line 10137 "PrintCLike.cpp"
  append(L";");
                                                            #line 5760 "PrintCLike.cpp.template"
                                                                }
                                                            #line 10141 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5762 "PrintCLike.cpp.template"
                                                                openMethod(intType(), L"", L"getTokenEnd", L"", true);
                                                                print(leftBrace());
                                                            #line 10146 "PrintCLike.cpp"
  append(L"\n");
  append(L"  return ");
                                                            #line 5765 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 10151 "PrintCLike.cpp"
  append(L"e0");
                                                            #line 5766 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                print(rightBrace());
                                                                if (isJavascript())
                                                                {
                                                            #line 10158 "PrintCLike.cpp"
  append(L";");
                                                            #line 5770 "PrintCLike.cpp.template"
                                                                }
                                                            #line 10162 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5772 "PrintCLike.cpp.template"
                                                              }
                                                              if (isJavascript())
                                                              {
                                                                if (useGlr)
                                                                {
                                                            #line 10170 "PrintCLike.cpp"
  append(L"\n");
  append(L"this.reset = function");
                                                            #line 5778 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 10177 "PrintCLike.cpp"
  append(L"\n");
  append(L"function reset");
                                                            #line 5782 "PrintCLike.cpp.template"
                                                                }
                                                            #line 10182 "PrintCLike.cpp"
  append(L"(l, b, e)\n");
  append(L"{");
                                                            #line 5784 "PrintCLike.cpp.template"
                                                              }
                                                              else if (isTypescript())
                                                              {
                                                            #line 10189 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5788 "PrintCLike.cpp.template"
                                                                if (! performanceTest && ! useGlr)
                                                                {
                                                            #line 10194 "PrintCLike.cpp"
  append(L"private ");
                                                            #line 5790 "PrintCLike.cpp.template"
                                                                }
                                                            #line 10198 "PrintCLike.cpp"
  append(L"reset(l: number, b: number, e: number)\n");
  append(L"{");
                                                            #line 5792 "PrintCLike.cpp.template"
                                                              }
                                                              else if (isHaxe())
                                                              {
                                                            #line 10205 "PrintCLike.cpp"
  append(L"\n");
  append(L"public function reset(l, b, e)\n");
  append(L"{");
                                                            #line 5797 "PrintCLike.cpp.template"
                                                              }
                                                              else
                                                              {
                                                                openMethod(voidType(), isJava() ? L"final " : L"", L"reset", L"int l, int b, int e", false, useGlr ? L"ParsingThread" : className.c_str());
                                                                print(leftBrace());
                                                              }
                                                            #line 10216 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5804 "PrintCLike.cpp.template"
                                                              if (! isPython() && ! isScala())
                                                              {
                                                            #line 10222 "PrintCLike.cpp"
  append(L"        ");
                                                            #line 5806 "PrintCLike.cpp.template"
                                                                print(wcslen(thiz()), L" ");
                                                              }
                                                              print(thiz());
                                                            #line 10228 "PrintCLike.cpp"
  append(L"b0 = b; ");
                                                            #line 5809 "PrintCLike.cpp.template"
                                                              print(thiz());
                                                            #line 10232 "PrintCLike.cpp"
  append(L"e0 = b");
                                                            #line 5810 "PrintCLike.cpp.template"
                                                              print(semicolon());
                                                            #line 10236 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5812 "PrintCLike.cpp.template"
                                                              print(thiz());
                                                            #line 10241 "PrintCLike.cpp"
  append(L"l1 = l; ");
                                                            #line 5813 "PrintCLike.cpp.template"
                                                              print(thiz());
                                                            #line 10245 "PrintCLike.cpp"
  append(L"b1 = b; ");
                                                            #line 5814 "PrintCLike.cpp.template"
                                                              print(thiz());
                                                            #line 10249 "PrintCLike.cpp"
  append(L"e1 = e");
                                                            #line 5815 "PrintCLike.cpp.template"
                                                              print(semicolon());
                                                              for (size_t k = 2; k <= grammar->k; ++k)
                                                              {
                                                            #line 10255 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5819 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 10260 "PrintCLike.cpp"
  append(L"l");
                                                            #line 5820 "PrintCLike.cpp.template"
                                                                print(format.toString<wchar_t>(k));
                                                            #line 10264 "PrintCLike.cpp"
  append(L" = 0; ");
                                                            #line 5821 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 10268 "PrintCLike.cpp"
  append(L"b");
                                                            #line 5822 "PrintCLike.cpp.template"
                                                                print(format.toString<wchar_t>(k));
                                                            #line 10272 "PrintCLike.cpp"
  append(L" = 0; ");
                                                            #line 5823 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 10276 "PrintCLike.cpp"
  append(L"e");
                                                            #line 5824 "PrintCLike.cpp.template"
                                                                print(format.toString<wchar_t>(k));
                                                            #line 10280 "PrintCLike.cpp"
  append(L" = 0");
                                                            #line 5825 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                              }
                                                            #line 10285 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5828 "PrintCLike.cpp.template"
                                                              print(thiz());
                                                            #line 10290 "PrintCLike.cpp"
  append(L"end = e");
                                                            #line 5829 "PrintCLike.cpp.template"
                                                              print(semicolon());
                                                              if (hasBacktracking)
                                                              {
                                                            #line 10296 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5833 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 10301 "PrintCLike.cpp"
  append(L"ex = -1");
                                                            #line 5834 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                if (memoization)
                                                                {
                                                                  if (isJavascript() || isTypescript())
                                                                  {
                                                            #line 10309 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5840 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 10314 "PrintCLike.cpp"
  append(L"memo = {};");
                                                            #line 5841 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isCSharp())
                                                                  {
                                                            #line 10320 "PrintCLike.cpp"
  append(L"\n");
  append(L"  memo.Clear();");
                                                            #line 5845 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isScala())
                                                                  {
                                                            #line 10327 "PrintCLike.cpp"
  append(L"\n");
  append(L"  memo.clear()");
                                                            #line 5849 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isHaxe())
                                                                  {
                                                            #line 10334 "PrintCLike.cpp"
  append(L"\n");
  append(L"  memo = new Map();");
                                                            #line 5853 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isGo())
                                                                  {
                                                            #line 10341 "PrintCLike.cpp"
  append(L"\n");
  append(L"  this.memo = make(map[int]int)");
                                                            #line 5857 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isPython())
                                                                  {
                                                            #line 10348 "PrintCLike.cpp"
  append(L"\n");
  append(L"  self.memo = {}");
                                                            #line 5861 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 10355 "PrintCLike.cpp"
  append(L"\n");
  append(L"  memo.clear();");
                                                            #line 5865 "PrintCLike.cpp.template"
                                                                  }
                                                                }
                                                                if (grammar->noThrow)
                                                                {
                                                            #line 10363 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5870 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 10368 "PrintCLike.cpp"
  append(L"viable = ");
                                                            #line 5871 "PrintCLike.cpp.template"
                                                                  if (isPython())
                                                                  {
                                                            #line 10373 "PrintCLike.cpp"
  append(L"T");
                                                            #line 5873 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 10379 "PrintCLike.cpp"
  append(L"t");
                                                            #line 5876 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 10383 "PrintCLike.cpp"
  append(L"rue");
                                                            #line 5877 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                              }
                                                              if (tree && ! useGlr)
                                                              {
                                                            #line 10391 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5883 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 10396 "PrintCLike.cpp"
  append(L"eventHandler");
                                                            #line 5884 "PrintCLike.cpp.template"
                                                                if (isTypescript() && isLrParser) print(L"!");
                                                                print(arrow());
                                                                if (isGo())
                                                                {
                                                            #line 10403 "PrintCLike.cpp"
  append(L"R");
                                                            #line 5888 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 10409 "PrintCLike.cpp"
  append(L"r");
                                                            #line 5891 "PrintCLike.cpp.template"
                                                                }
                                                            #line 10413 "PrintCLike.cpp"
  append(L"eset(");
                                                            #line 5892 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 10417 "PrintCLike.cpp"
  append(L"input)");
                                                            #line 5893 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                              }
                                                              if (useGlr)
                                                              {
                                                            #line 10424 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5898 "PrintCLike.cpp.template"
                                                                if (isCSharp() || isCpp() || isHaxe() || isScala() || isTypescript() || isGo())
                                                                {
                                                                  print(thiz());
                                                            #line 10431 "PrintCLike.cpp"
  append(L"parser");
                                                            #line 5901 "PrintCLike.cpp.template"
                                                                  print(arrow());
                                                                }
                                                            #line 10436 "PrintCLike.cpp"
  append(L"maxId = 0");
                                                            #line 5903 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 10440 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5905 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 10445 "PrintCLike.cpp"
  append(L"id = ");
                                                            #line 5906 "PrintCLike.cpp.template"
                                                                if (isCSharp() || isCpp() || isHaxe() || isScala() || isTypescript() || isGo())
                                                                {
                                                                  print(thiz());
                                                            #line 10451 "PrintCLike.cpp"
  append(L"parser");
                                                            #line 5909 "PrintCLike.cpp.template"
                                                                  print(arrow());
                                                                }
                                                            #line 10456 "PrintCLike.cpp"
  append(L"maxId");
                                                            #line 5911 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                              }
                                                              print(rightBrace());
                                                              if (isJavascript() && useGlr)
                                                              {
                                                            #line 10464 "PrintCLike.cpp"
  append(L";");
                                                            #line 5916 "PrintCLike.cpp.template"
                                                              }
                                                            #line 10468 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5918 "PrintCLike.cpp.template"
                                                              if (useGlr || isJavascript() || isTypescript() || isHaxe() || isGo() || isPython())
                                                              {
                                                              }
                                                              else
                                                              {
                                                                openMethod(voidType(), L"", L"reset", L"");
                                                                print(leftBrace());
                                                            #line 10478 "PrintCLike.cpp"
  append(L"\n");
  append(L"  reset(0, 0, 0)");
                                                            #line 5926 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                print(rightBrace());
                                                            #line 10484 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5929 "PrintCLike.cpp.template"
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
                                                            #line 10512 "PrintCLike.cpp"
  append(L"\n");
  append(L"if ");
                                                            #line 5955 "PrintCLike.cpp.template"
                                                                    print(ifLeftParen());
                                                            #line 10517 "PrintCLike.cpp"
  append(L"(");
                                                            #line 5956 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                                    print(token());
                                                            #line 10522 "PrintCLike.cpp"
  append(L" == ");
                                                            #line 5958 "PrintCLike.cpp.template"
                                                                    print(format.toString<wchar_t>(grammar->externalTokenCode[plusplus]));
                                                                    if (isPython())
                                                                    {
                                                            #line 10528 "PrintCLike.cpp"
  append(L" or ");
                                                            #line 5961 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 10534 "PrintCLike.cpp"
  append(L" || ");
                                                            #line 5964 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(thiz());
                                                                    print(token());
                                                            #line 10540 "PrintCLike.cpp"
  append(L" == ");
                                                            #line 5967 "PrintCLike.cpp.template"
                                                                    print(format.toString<wchar_t>(grammar->externalTokenCode[minusminus]));
                                                            #line 10544 "PrintCLike.cpp"
  append(L")");
                                                            #line 5968 "PrintCLike.cpp.template"
                                                                    if (isPython())
                                                                    {
                                                            #line 10549 "PrintCLike.cpp"
  append(L" and ");
                                                            #line 5970 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 10555 "PrintCLike.cpp"
  append(L" && ");
                                                            #line 5973 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(thiz());
                                                            #line 10560 "PrintCLike.cpp"
  append(L"followsLineTerminator");
                                                            #line 5975 "PrintCLike.cpp.template"
                                                                    if (! isScala())
                                                                    {
                                                            #line 10565 "PrintCLike.cpp"
  append(L"()");
                                                            #line 5977 "PrintCLike.cpp.template"
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
                                                            #line 10579 "PrintCLike.cpp"
  append(L"\n");
  append(L"if ");
                                                            #line 5989 "PrintCLike.cpp.template"
                                                                    print(ifLeftParen());
                                                                    print(thiz());
                                                                    print(token());
                                                            #line 10586 "PrintCLike.cpp"
  append(L" != ");
                                                            #line 5992 "PrintCLike.cpp.template"
                                                                    print(format.toString<wchar_t>(grammar->externalTokenCode[semicolonToken]));
                                                                    if (isPython())
                                                                    {
                                                            #line 10592 "PrintCLike.cpp"
  append(L" and ");
                                                            #line 5995 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 10598 "PrintCLike.cpp"
  append(L" && ");
                                                            #line 5998 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(thiz());
                                                                    print(token());
                                                            #line 10604 "PrintCLike.cpp"
  append(L" >= 0");
                                                            #line 6001 "PrintCLike.cpp.template"
                                                                    if (isPython())
                                                                    {
                                                            #line 10609 "PrintCLike.cpp"
  append(L" and ");
                                                            #line 6003 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 10615 "PrintCLike.cpp"
  append(L" && ");
                                                            #line 6006 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(thiz());
                                                            #line 10620 "PrintCLike.cpp"
  append(L"followsLineTerminator");
                                                            #line 6008 "PrintCLike.cpp.template"
                                                                    if (! isScala())
                                                                    {
                                                            #line 10625 "PrintCLike.cpp"
  append(L"()");
                                                            #line 6010 "PrintCLike.cpp.template"
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
                                                            #line 10640 "PrintCLike.cpp"
  append(L"\n");
  append(L"if ");
                                                            #line 6023 "PrintCLike.cpp.template"
                                                                    print(isPython() ? L"(" : ifLeftParen());
                                                                    print(thiz());
                                                                    print(token());
                                                            #line 10647 "PrintCLike.cpp"
  append(L" == ");
                                                            #line 6026 "PrintCLike.cpp.template"
                                                                    print(format.toString<wchar_t>(grammar->externalTokenCode[rbrace]));
                                                                    if (isPython())
                                                                    {
                                                            #line 10653 "PrintCLike.cpp"
  append(L" or");
                                                            #line 6029 "PrintCLike.cpp.template"
                                                                    }
                                                                    else if (isGo())
                                                                    {
                                                            #line 10659 "PrintCLike.cpp"
  append(L" ||");
                                                            #line 6032 "PrintCLike.cpp.template"
                                                                    }
                                                                    printCodeSequenceAnnotation(grammar->tokenSequence(rbrace));
                                                                    if (isGo() || isPython())
                                                                    {
                                                            #line 10666 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 6037 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 10673 "PrintCLike.cpp"
  append(L"\n");
  append(L" || ");
                                                            #line 6041 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(thiz());
                                                                    print(token());
                                                            #line 10680 "PrintCLike.cpp"
  append(L" == ");
                                                            #line 6044 "PrintCLike.cpp.template"
                                                                    print(format.toString<wchar_t>(grammar->externalTokenCode[eof]));
                                                                    if (isPython())
                                                                    {
                                                            #line 10686 "PrintCLike.cpp"
  append(L" or");
                                                            #line 6047 "PrintCLike.cpp.template"
                                                                    }
                                                                    else if (isGo())
                                                                    {
                                                            #line 10692 "PrintCLike.cpp"
  append(L" ||");
                                                            #line 6050 "PrintCLike.cpp.template"
                                                                    }
                                                                    printCodeSequenceAnnotation(grammar->tokenSequence(eof));
                                                                    if (isGo() || isPython())
                                                                    {
                                                            #line 10699 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 6055 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 10706 "PrintCLike.cpp"
  append(L"\n");
  append(L" || ");
                                                            #line 6059 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(thiz());
                                                                    print(token());
                                                            #line 10713 "PrintCLike.cpp"
  append(L" != ");
                                                            #line 6062 "PrintCLike.cpp.template"
                                                                    print(format.toString<wchar_t>(grammar->externalTokenCode[semicolonToken]));
                                                                    if (isPython())
                                                                    {
                                                            #line 10719 "PrintCLike.cpp"
  append(L" and ");
                                                            #line 6065 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 10725 "PrintCLike.cpp"
  append(L" && ");
                                                            #line 6068 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(thiz());
                                                                    print(token());
                                                            #line 10731 "PrintCLike.cpp"
  append(L" >= 0");
                                                            #line 6071 "PrintCLike.cpp.template"
                                                                    if (isPython())
                                                                    {
                                                            #line 10736 "PrintCLike.cpp"
  append(L" and ");
                                                            #line 6073 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 10742 "PrintCLike.cpp"
  append(L" && ");
                                                            #line 6076 "PrintCLike.cpp.template"
                                                                    }
                                                                    if (afterRbrace)
                                                                    {
                                                            #line 10748 "PrintCLike.cpp"
  append(L"(");
                                                            #line 6079 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(thiz());
                                                            #line 10753 "PrintCLike.cpp"
  append(L"followsLineTerminator");
                                                            #line 6081 "PrintCLike.cpp.template"
                                                                    if (! isScala())
                                                                    {
                                                            #line 10758 "PrintCLike.cpp"
  append(L"()");
                                                            #line 6083 "PrintCLike.cpp.template"
                                                                    }
                                                                    if (afterRbrace)
                                                                    {
                                                                      if (isPython())
                                                                      {
                                                            #line 10766 "PrintCLike.cpp"
  append(L" || ");
                                                            #line 6088 "PrintCLike.cpp.template"
                                                                      }
                                                                      else
                                                                      {
                                                            #line 10772 "PrintCLike.cpp"
  append(L" or ");
                                                            #line 6091 "PrintCLike.cpp.template"
                                                                      }
                                                                      if (isCpp() || isCSharp() || isPython() || (isJava() && codepoints))
                                                                      {
                                                                        print(thiz());
                                                            #line 10779 "PrintCLike.cpp"
  append(L"input[");
                                                            #line 6095 "PrintCLike.cpp.template"
                                                                        print(thiz());
                                                            #line 10783 "PrintCLike.cpp"
  append(L"b0]");
                                                            #line 6096 "PrintCLike.cpp.template"
                                                                      }
                                                                      else
                                                                      {
                                                                        print(thiz());
                                                            #line 10790 "PrintCLike.cpp"
  append(L"input.char");
                                                            #line 6100 "PrintCLike.cpp.template"
                                                                        if (isTypescript() || isJavascript() || isHaxe())
                                                                        {
                                                            #line 10795 "PrintCLike.cpp"
  append(L"Code");
                                                            #line 6102 "PrintCLike.cpp.template"
                                                                        }
                                                            #line 10799 "PrintCLike.cpp"
  append(L"At(");
                                                            #line 6103 "PrintCLike.cpp.template"
                                                                        print(thiz());
                                                            #line 10803 "PrintCLike.cpp"
  append(L"b0)");
                                                            #line 6105 "PrintCLike.cpp.template"
                                                                      }
                                                            #line 10807 "PrintCLike.cpp"
  append(L" == 0x7D)");
                                                            #line 6106 "PrintCLike.cpp.template"
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
                                                            #line 10820 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 6117 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 10825 "PrintCLike.cpp"
  append(L"l1 = ");
                                                            #line 6118 "PrintCLike.cpp.template"
                                                                print(format.toString<wchar_t>(grammar->externalTokenCode[semicolonToken]));
                                                                print(semicolon());
                                                            #line 10830 "PrintCLike.cpp"
  append(L" ");
                                                            #line 6120 "PrintCLike.cpp.template"
                                                                printCodeSequenceAnnotation(grammar->tokenSequence(semicolonToken));
                                                            #line 10834 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 6122 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 10839 "PrintCLike.cpp"
  append(L"e1 = ");
                                                            #line 6123 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 10843 "PrintCLike.cpp"
  append(L"b1");
                                                            #line 6124 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 10847 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 6126 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 10852 "PrintCLike.cpp"
  append(L"end = ");
                                                            #line 6127 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 10856 "PrintCLike.cpp"
  append(L"e1");
                                                            #line 6128 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                print(rightBrace());
                                                              }
                                                            }

// End
