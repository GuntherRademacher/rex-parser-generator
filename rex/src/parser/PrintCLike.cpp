// This file was generated on Sat Oct 17, 2026 11:26 (UTC+02) by REx v6.3-SNAPSHOT which is Copyright (c) 1979-2026 by Gunther Rademacher <grd@gmx.net>
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
                                                            #line 245 "PrintCLike.cpp.template"
                                                                      }
                                                                      else if (! isScala())
                                                                      {
                                                            #line 288 "PrintCLike.cpp"
  append(L"\n");
  append(L"default:");
                                                            #line 249 "PrintCLike.cpp.template"
                                                                      }
                                                                      increaseIndent();
                                                            #line 294 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 252 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 298 "PrintCLike.cpp"
  append(L"lk = ");
                                                            #line 253 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 302 "PrintCLike.cpp"
  append(L"l1");
                                                            #line 254 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                                      if (isCpp() || isCSharp())
                                                                      {
                                                            #line 308 "PrintCLike.cpp"
  append(L"\n");
  append(L"break");
                                                            #line 258 "PrintCLike.cpp.template"
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
                                                            #line 392 "PrintCLike.cpp.template"
                                                                  if (k) lineBuffer += thiz();
                                                                  lineBuffer += matchVariable;
                                                                  lineBuffer += comparison;
                                                                  lineBuffer += matchCode;
                                                                  break;

                                                                case CASE:
                                                            #line 455 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 400 "PrintCLike.cpp.template"
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
                                                            #line 514 "PrintCLike.cpp.template"
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
                                                            #line 586 "PrintCLike.cpp.template"
                                                                print(format.toString<wchar_t>(node->loopId));
                                                            #line 650 "PrintCLike.cpp"
  append(L" = true");
                                                            #line 587 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 654 "PrintCLike.cpp"
  append(L"\n");
  append(L"while (c");
                                                            #line 589 "PrintCLike.cpp.template"
                                                                print(format.toString<wchar_t>(node->loopId));
                                                                if (hasBacktracking && grammar->noThrow)
                                                                {
                                                            #line 661 "PrintCLike.cpp"
  append(L" && ");
                                                            #line 592 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 665 "PrintCLike.cpp"
  append(L"viable");
                                                            #line 593 "PrintCLike.cpp.template"
                                                                }
                                                            #line 669 "PrintCLike.cpp"
  append(L")");
                                                            #line 594 "PrintCLike.cpp.template"
                                                              }
                                                              else if (isGo())
                                                              {
                                                            #line 675 "PrintCLike.cpp"
  append(L"\n");
  append(L"for");
                                                            #line 598 "PrintCLike.cpp.template"
                                                                if (hasBacktracking && grammar->noThrow)
                                                                {
                                                            #line 681 "PrintCLike.cpp"
  append(L" this.viable");
                                                            #line 600 "PrintCLike.cpp.template"
                                                                }
                                                              }
                                                              else if (isPython())
                                                              {
                                                            #line 688 "PrintCLike.cpp"
  append(L"\n");
  append(L"while ");
                                                            #line 605 "PrintCLike.cpp.template"
                                                                if (hasBacktracking && grammar->noThrow)
                                                                {
                                                            #line 694 "PrintCLike.cpp"
  append(L"self.viable");
                                                            #line 607 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 700 "PrintCLike.cpp"
  append(L"True");
                                                            #line 610 "PrintCLike.cpp.template"
                                                                }
                                                            #line 704 "PrintCLike.cpp"
  append(L":");
                                                            #line 611 "PrintCLike.cpp.template"
                                                              }
                                                              else if (hasBacktracking && grammar->noThrow)
                                                              {
                                                            #line 710 "PrintCLike.cpp"
  append(L"\n");
  append(L"while (");
                                                            #line 615 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 715 "PrintCLike.cpp"
  append(L"viable)");
                                                            #line 616 "PrintCLike.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 721 "PrintCLike.cpp"
  append(L"\n");
  append(L"for (;;)");
                                                            #line 620 "PrintCLike.cpp.template"
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
                                                            #line 640 "PrintCLike.cpp.template"
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
                                                            #line 653 "PrintCLike.cpp.template"
                                                                print(format.toString<wchar_t>(node->loopId));
                                                            #line 765 "PrintCLike.cpp"
  append(L" = false\n");
  append(L"}\n");
  append(L"else {");
                                                            #line 656 "PrintCLike.cpp.template"
                                                                increaseIndent();
                                                              }
                                                              else
                                                              {
                                                            #line 774 "PrintCLike.cpp"
  append(L"\n");
  append(L"  break");
                                                            #line 661 "PrintCLike.cpp.template"
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
                                                            #line 669 "PrintCLike.cpp.template"
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
                                                            #line 691 "PrintCLike.cpp.template"
                                                                print(format.toString<wchar_t>(node->loopId));
                                                            #line 815 "PrintCLike.cpp"
  append(L" = true");
                                                            #line 692 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 819 "PrintCLike.cpp"
  append(L"\n");
  append(L"while (c");
                                                            #line 694 "PrintCLike.cpp.template"
                                                                print(format.toString<wchar_t>(node->loopId));
                                                                if (hasBacktracking && grammar->noThrow)
                                                                {
                                                            #line 826 "PrintCLike.cpp"
  append(L" && ");
                                                            #line 697 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 830 "PrintCLike.cpp"
  append(L"viable");
                                                            #line 698 "PrintCLike.cpp.template"
                                                                }
                                                            #line 834 "PrintCLike.cpp"
  append(L")");
                                                            #line 699 "PrintCLike.cpp.template"
                                                              }
                                                              else if (isGo())
                                                              {
                                                            #line 840 "PrintCLike.cpp"
  append(L"\n");
  append(L"for");
                                                            #line 703 "PrintCLike.cpp.template"
                                                                if (hasBacktracking && grammar->noThrow)
                                                                {
                                                            #line 846 "PrintCLike.cpp"
  append(L" this.viable");
                                                            #line 705 "PrintCLike.cpp.template"
                                                                }
                                                              }
                                                              else if (hasBacktracking && grammar->noThrow)
                                                              {
                                                            #line 853 "PrintCLike.cpp"
  append(L"\n");
  append(L"while ");
                                                            #line 710 "PrintCLike.cpp.template"
                                                                print(ifLeftParen());
                                                                print(thiz());
                                                            #line 859 "PrintCLike.cpp"
  append(L"viable");
                                                            #line 712 "PrintCLike.cpp.template"
                                                                print(ifRightParen());
                                                              }
                                                              else if (isPython())
                                                              {
                                                            #line 866 "PrintCLike.cpp"
  append(L"\n");
  append(L"while True:");
                                                            #line 717 "PrintCLike.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 873 "PrintCLike.cpp"
  append(L"\n");
  append(L"for (;;)");
                                                            #line 721 "PrintCLike.cpp.template"
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
                                                            #line 745 "PrintCLike.cpp.template"
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
                                                            #line 758 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                              }
                                                              else
                                                              {
                                                            #line 924 "PrintCLike.cpp"
  append(L"\n");
  append(L"  c");
                                                            #line 763 "PrintCLike.cpp.template"
                                                                print(format.toString<wchar_t>(node->loopId));
                                                            #line 929 "PrintCLike.cpp"
  append(L" = false");
                                                            #line 765 "PrintCLike.cpp.template"
                                                              }
                                                              print(rightBrace());
                                                              if (nestedTry)
                                                              {
                                                                if (isScala())
                                                                {
                                                            #line 938 "PrintCLike.cpp"
  append(L"\n");
  append(L"else {");
                                                            #line 772 "PrintCLike.cpp.template"
                                                                }
                                                                decreaseIndent();
                                                                Visitor::visitNodeWithChildren(node);
                                                                increaseIndent();

                                                                if (isScala())
                                                                {
                                                            #line 949 "PrintCLike.cpp"
  append(L"\n");
  append(L"}");
                                                            #line 780 "PrintCLike.cpp.template"
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
                                                            #line 801 "PrintCLike.cpp.template"
                                                                }
                                                                else if (! isPython())
                                                                {
                                                            #line 980 "PrintCLike.cpp"
  append(L"\n");
  append(L"default:");
                                                            #line 805 "PrintCLike.cpp.template"
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
                                                            #line 813 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                                  print(thiz());
                                                            #line 997 "PrintCLike.cpp"
  append(L"viable");
                                                            #line 815 "PrintCLike.cpp.template"
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
                                                            #line 860 "PrintCLike.cpp.template"
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
                                                            #line 877 "PrintCLike.cpp.template"
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
                                                            #line 904 "PrintCLike.cpp.template"
                                                              print(intVal());
                                                            #line 1098 "PrintCLike.cpp"
  append(L"b0");
                                                            #line 905 "PrintCLike.cpp.template"
                                                              print(L'A' + ncl);
                                                              print(assign());
                                                              print(thiz());
                                                            #line 1104 "PrintCLike.cpp"
  append(L"b0; ");
                                                            #line 909 "PrintCLike.cpp.template"
                                                              print(intVal());
                                                            #line 1108 "PrintCLike.cpp"
  append(L"e0");
                                                            #line 910 "PrintCLike.cpp.template"
                                                              print(L'A' + ncl);
                                                              print(assign());
                                                              print(thiz());
                                                            #line 1114 "PrintCLike.cpp"
  append(L"e0");
                                                            #line 913 "PrintCLike.cpp.template"
                                                              for (size_t k = 1; k <= grammar->k; ++k)
                                                              {
                                                            #line 1119 "PrintCLike.cpp"
  append(L"; ");
                                                            #line 915 "PrintCLike.cpp.template"
                                                                print(intVal());
                                                            #line 1123 "PrintCLike.cpp"
  append(L"l");
                                                            #line 916 "PrintCLike.cpp.template"
                                                                print(format.toString<wchar_t>(k));
                                                                print(L'A' + ncl);
                                                                print(assign());
                                                                print(thiz());
                                                            #line 1130 "PrintCLike.cpp"
  append(L"l");
                                                            #line 920 "PrintCLike.cpp.template"
                                                                print(format.toString<wchar_t>(k));
                                                                print(semicolon());
                                                            #line 1135 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 923 "PrintCLike.cpp.template"
                                                                print(intVal());
                                                            #line 1139 "PrintCLike.cpp"
  append(L"b");
                                                            #line 924 "PrintCLike.cpp.template"
                                                                print(format.toString<wchar_t>(k));
                                                                print(L'A' + ncl);
                                                                print(assign());
                                                                print(thiz());
                                                            #line 1146 "PrintCLike.cpp"
  append(L"b");
                                                            #line 928 "PrintCLike.cpp.template"
                                                                print(format.toString<wchar_t>(k));
                                                            #line 1150 "PrintCLike.cpp"
  append(L"; ");
                                                            #line 929 "PrintCLike.cpp.template"
                                                                print(intVal());
                                                            #line 1154 "PrintCLike.cpp"
  append(L"e");
                                                            #line 930 "PrintCLike.cpp.template"
                                                                print(format.toString<wchar_t>(k));
                                                                print(L'A' + ncl);
                                                                print(assign());
                                                                print(thiz());
                                                            #line 1161 "PrintCLike.cpp"
  append(L"e");
                                                            #line 934 "PrintCLike.cpp.template"
                                                                print(format.toString<wchar_t>(k));
                                                              }
                                                              print(semicolon());
                                                            }

                                                            void PrintCLike::restoreContext(int ncl)
                                                            {
                                                              Trace("PrintCLike::restoreContext");
                                                            #line 1172 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 943 "PrintCLike.cpp.template"
                                                              print(thiz());
                                                            #line 1176 "PrintCLike.cpp"
  append(L"b0 = b0");
                                                            #line 944 "PrintCLike.cpp.template"
                                                              print(L'A' + ncl);
                                                            #line 1180 "PrintCLike.cpp"
  append(L"; ");
                                                            #line 945 "PrintCLike.cpp.template"
                                                              print(thiz());
                                                            #line 1184 "PrintCLike.cpp"
  append(L"e0 = e0");
                                                            #line 946 "PrintCLike.cpp.template"
                                                              print(L'A' + ncl);
                                                            #line 1188 "PrintCLike.cpp"
  append(L";");
                                                            #line 947 "PrintCLike.cpp.template"
                                                              for (size_t k = 1; k <= grammar->k; ++k)
                                                              {
                                                            #line 1193 "PrintCLike.cpp"
  append(L" ");
                                                            #line 949 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 1197 "PrintCLike.cpp"
  append(L"l");
                                                            #line 950 "PrintCLike.cpp.template"
                                                                print(format.toString<wchar_t>(k));
                                                            #line 1201 "PrintCLike.cpp"
  append(L" = l");
                                                            #line 951 "PrintCLike.cpp.template"
                                                                print(format.toString<wchar_t>(k));
                                                                print(L'A' + ncl);
                                                                if (isPython())
                                                                {
                                                            #line 1208 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 956 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1214 "PrintCLike.cpp"
  append(L"; ");
                                                            #line 959 "PrintCLike.cpp.template"
                                                                }
                                                            #line 1218 "PrintCLike.cpp"
  append(L"if ");
                                                            #line 960 "PrintCLike.cpp.template"
                                                                print(ifLeftParen());
                                                                print(thiz());
                                                            #line 1223 "PrintCLike.cpp"
  append(L"l");
                                                            #line 962 "PrintCLike.cpp.template"
                                                                print(format.toString<wchar_t>(k));
                                                            #line 1227 "PrintCLike.cpp"
  append(L" == 0");
                                                            #line 963 "PrintCLike.cpp.template"
                                                                print(ifRightParen());
                                                                if (isPython())
                                                                {
                                                                  increaseIndent();
                                                            #line 1234 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 968 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1240 "PrintCLike.cpp"
  append(L" {");
                                                            #line 971 "PrintCLike.cpp.template"
                                                                }
                                                                print(thiz());
                                                            #line 1245 "PrintCLike.cpp"
  append(L"end = e");
                                                            #line 973 "PrintCLike.cpp.template"
                                                                print(format.toString<wchar_t>(k - 1));
                                                                print(L'A' + ncl);
                                                                print(semicolon());
                                                                if (isPython())
                                                                {
                                                                  decreaseIndent();
                                                            #line 1254 "PrintCLike.cpp"
  append(L"\n");
  append(L"else:");
                                                            #line 980 "PrintCLike.cpp.template"
                                                                  increaseIndent();
                                                                }
                                                                else
                                                                {
                                                            #line 1262 "PrintCLike.cpp"
  append(L"} else {");
                                                            #line 984 "PrintCLike.cpp.template"
                                                                }
                                                            #line 1266 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 986 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 1270 "PrintCLike.cpp"
  append(L"b");
                                                            #line 987 "PrintCLike.cpp.template"
                                                                print(format.toString<wchar_t>(k));
                                                            #line 1274 "PrintCLike.cpp"
  append(L" = b");
                                                            #line 988 "PrintCLike.cpp.template"
                                                                print(format.toString<wchar_t>(k));
                                                                print(L'A' + ncl);
                                                            #line 1279 "PrintCLike.cpp"
  append(L"; ");
                                                            #line 990 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 1283 "PrintCLike.cpp"
  append(L"e");
                                                            #line 991 "PrintCLike.cpp.template"
                                                                print(format.toString<wchar_t>(k));
                                                            #line 1287 "PrintCLike.cpp"
  append(L" = e");
                                                            #line 992 "PrintCLike.cpp.template"
                                                                print(format.toString<wchar_t>(k));
                                                                print(L'A' + ncl);
                                                            #line 1292 "PrintCLike.cpp"
  append(L";");
                                                            #line 994 "PrintCLike.cpp.template"
                                                              }
                                                            #line 1296 "PrintCLike.cpp"
  append(L" ");
                                                            #line 995 "PrintCLike.cpp.template"
                                                              print(thiz());
                                                            #line 1300 "PrintCLike.cpp"
  append(L"end = e");
                                                            #line 996 "PrintCLike.cpp.template"
                                                              print(format.toString<wchar_t>(grammar->k));
                                                              print(L'A' + ncl);
                                                              print(semicolon());
                                                            #line 1306 "PrintCLike.cpp"
  append(L" ");
                                                            #line 999 "PrintCLike.cpp.template"
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
                                                            #line 1007 "PrintCLike.cpp.template"
                                                                }
                                                              }
                                                              if (grammar->noThrow)
                                                              {
                                                            #line 1324 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 1012 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 1328 "PrintCLike.cpp"
  append(L"viable = ");
                                                            #line 1013 "PrintCLike.cpp.template"
                                                                if (isPython())
                                                                {
                                                            #line 1333 "PrintCLike.cpp"
  append(L"T");
                                                            #line 1015 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1339 "PrintCLike.cpp"
  append(L"t");
                                                            #line 1018 "PrintCLike.cpp.template"
                                                                }
                                                            #line 1343 "PrintCLike.cpp"
  append(L"rue");
                                                            #line 1019 "PrintCLike.cpp.template"
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
                                                            #line 1079 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 1409 "PrintCLike.cpp"
  append(L"lk = ");
                                                            #line 1080 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 1413 "PrintCLike.cpp"
  append(L"memoized(");
                                                            #line 1081 "PrintCLike.cpp.template"
                                                                  print(format.toString<wchar_t>(conflictId));
                                                            #line 1417 "PrintCLike.cpp"
  append(L", ");
                                                            #line 1082 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 1421 "PrintCLike.cpp"
  append(L"e0)");
                                                            #line 1083 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                            #line 1425 "PrintCLike.cpp"
  append(L"\n");
  append(L"if ");
                                                            #line 1085 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                                  print(thiz());
                                                            #line 1431 "PrintCLike.cpp"
  append(L"lk == 0");
                                                            #line 1087 "PrintCLike.cpp.template"
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
                                                            #line 1122 "PrintCLike.cpp.template"
                                                                        print(thiz());
                                                            #line 1472 "PrintCLike.cpp"
  append(L"lk = -");
                                                            #line 1123 "PrintCLike.cpp.template"
                                                                        print(format.toString<wchar_t>(caseId));
                                                                        print(semicolon());
                                                                      }
                                                                      restoreContext(ncl);
                                                                      if (memoization)
                                                                      {
                                                            #line 1481 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 1130 "PrintCLike.cpp.template"
                                                                        print(thiz());
                                                            #line 1485 "PrintCLike.cpp"
  append(L"memoize(");
                                                            #line 1131 "PrintCLike.cpp.template"
                                                                        print(format.toString<wchar_t>(conflictId));
                                                            #line 1489 "PrintCLike.cpp"
  append(L", e0");
                                                            #line 1132 "PrintCLike.cpp.template"
                                                                        print(L'A' + ncl);
                                                            #line 1493 "PrintCLike.cpp"
  append(L", -");
                                                            #line 1133 "PrintCLike.cpp.template"
                                                                        print(format.toString<wchar_t>(caseId));
                                                            #line 1497 "PrintCLike.cpp"
  append(L")");
                                                            #line 1134 "PrintCLike.cpp.template"
                                                                        print(semicolon());
                                                                      }
                                                                      if (node->isZeroOrMore() || node->isOneOrMore())
                                                                      {
                                                                        if (isScala())
                                                                        {
                                                            #line 1506 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 1141 "PrintCLike.cpp.template"
                                                                          print(thiz());
                                                            #line 1510 "PrintCLike.cpp"
  append(L"lk = -");
                                                            #line 1142 "PrintCLike.cpp.template"
                                                                          print(format.toString<wchar_t>(caseId));
                                                                        }
                                                                        else
                                                                        {
                                                            #line 1517 "PrintCLike.cpp"
  append(L"\n");
  append(L"break");
                                                            #line 1147 "PrintCLike.cpp.template"
                                                                          print(semicolon());
                                                                        }
                                                                      }
                                                                    }
                                                                    else
                                                                    {
                                                            #line 1527 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 1154 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 1531 "PrintCLike.cpp"
  append(L"lk = -");
                                                            #line 1155 "PrintCLike.cpp.template"
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
                                                            #line 1168 "PrintCLike.cpp.template"
                                                                     if (isPython())
                                                                     {
                                                            #line 1552 "PrintCLike.cpp"
  append(L":");
                                                            #line 1170 "PrintCLike.cpp.template"
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
                                                            #line 1210 "PrintCLike.cpp.template"
                                                                      print(ifLeftParen());
                                                                      print(thiz());
                                                            #line 1600 "PrintCLike.cpp"
  append(L"viable");
                                                            #line 1212 "PrintCLike.cpp.template"
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
                                                            #line 1222 "PrintCLike.cpp.template"
                                                                        print(thiz());
                                                            #line 1616 "PrintCLike.cpp"
  append(L"memoize(");
                                                            #line 1223 "PrintCLike.cpp.template"
                                                                        print(format.toString<wchar_t>(conflictId));
                                                            #line 1620 "PrintCLike.cpp"
  append(L", e0");
                                                            #line 1224 "PrintCLike.cpp.template"
                                                                        print(L'A' + ncl);
                                                            #line 1624 "PrintCLike.cpp"
  append(L", -");
                                                            #line 1225 "PrintCLike.cpp.template"
                                                                        print(format.toString<wchar_t>(caseId));
                                                            #line 1628 "PrintCLike.cpp"
  append(L")");
                                                            #line 1226 "PrintCLike.cpp.template"
                                                                        print(semicolon());
                                                                      }
                                                                      if (node->isChoice())
                                                                      {
                                                            #line 1635 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 1231 "PrintCLike.cpp.template"
                                                                        print(thiz());
                                                            #line 1639 "PrintCLike.cpp"
  append(L"lk = -");
                                                            #line 1232 "PrintCLike.cpp.template"
                                                                        print(format.toString<wchar_t>(defaultLk));
                                                                        print(semicolon());
                                                                      }
                                                                      else if (node->isZeroOrMore() || node->isOneOrMore())
                                                                      {
                                                                        if (isScala())
                                                                        {
                                                            #line 1649 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 1240 "PrintCLike.cpp.template"
                                                                          print(thiz());
                                                            #line 1653 "PrintCLike.cpp"
  append(L"lk = -3");
                                                            #line 1241 "PrintCLike.cpp.template"
                                                                        }
                                                                        else
                                                                        {
                                                            #line 1659 "PrintCLike.cpp"
  append(L"\n");
  append(L"continue;");
                                                            #line 1245 "PrintCLike.cpp.template"
                                                                        }
                                                                      }
                                                                    }
                                                                    else
                                                                    {
                                                            #line 1668 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 1251 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 1672 "PrintCLike.cpp"
  append(L"lk = -");
                                                            #line 1252 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(caseId));
                                                                      print(semicolon());
                                                                    }

                                                                    decreaseIndent();
                                                                    if (grammar->noThrow)
                                                                    {
                                                            #line 1682 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 1260 "PrintCLike.cpp.template"
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
                                                            #line 1268 "PrintCLike.cpp.template"
                                                                        print(className.c_str());
                                                            #line 1697 "PrintCLike.cpp"
  append(L".ParseException:");
                                                            #line 1269 "PrintCLike.cpp.template"
                                                                      }
                                                                      else
                                                                      {
                                                            #line 1703 "PrintCLike.cpp"
  append(L"\n");
  append(L"catch ");
                                                            #line 1273 "PrintCLike.cpp.template"
                                                                        if (isScala())
                                                                        {
                                                            #line 1709 "PrintCLike.cpp"
  append(L"{\n");
  append(L"case _: ");
                                                            #line 1276 "PrintCLike.cpp.template"
                                                                          print(className.c_str());
                                                            #line 1714 "PrintCLike.cpp"
  append(L".ParseException =>");
                                                            #line 1277 "PrintCLike.cpp.template"
                                                                        }
                                                                        else
                                                                        {
                                                            #line 1720 "PrintCLike.cpp"
  append(L"(");
                                                            #line 1281 "PrintCLike.cpp.template"
                                                                          if (! isJavascript() && ! isTypescript() && ! isHaxe())
                                                                          {
                                                            #line 1725 "PrintCLike.cpp"
  append(L"ParseException");
                                                            #line 1283 "PrintCLike.cpp.template"
                                                                          }
                                                                          if (! isCSharp() && ! isJavascript() && ! isTypescript() && ! isHaxe())
                                                                          {
                                                            #line 1731 "PrintCLike.cpp"
  append(L" ");
                                                            #line 1286 "PrintCLike.cpp.template"
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
                                                            #line 1294 "PrintCLike.cpp.template"
                                                                            }
                                                                          }
                                                                          else if (isCpp())
                                                                          {
                                                            #line 1749 "PrintCLike.cpp"
  append(L"&");
                                                            #line 1298 "PrintCLike.cpp.template"
                                                                          }
                                                            #line 1753 "PrintCLike.cpp"
  append(L")");
                                                            #line 1299 "PrintCLike.cpp.template"
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
                                                            #line 1324 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 1784 "PrintCLike.cpp"
  append(L"memoize(");
                                                            #line 1325 "PrintCLike.cpp.template"
                                                                    print(format.toString<wchar_t>(conflictId));
                                                            #line 1788 "PrintCLike.cpp"
  append(L", ");
                                                            #line 1326 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 1792 "PrintCLike.cpp"
  append(L"e0, ");
                                                            #line 1327 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 1796 "PrintCLike.cpp"
  append(L"lk)");
                                                            #line 1328 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                  }
                                                                }
                                                                else if (node->isOptional())
                                                                {
                                                            #line 1804 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 1334 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 1808 "PrintCLike.cpp"
  append(L"lk = -2");
                                                            #line 1335 "PrintCLike.cpp.template"
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
                                                            #line 1352 "PrintCLike.cpp.template"
                                                                    print(elseWithBraces());
                                                            #line 1831 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 1354 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 1836 "PrintCLike.cpp"
  append(L"lk = ");
                                                            #line 1355 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 1840 "PrintCLike.cpp"
  append(L"l1");
                                                            #line 1356 "PrintCLike.cpp.template"
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
                                                            #line 1380 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1873 "PrintCLike.cpp"
  append(L"\n");
  append(L"lk match");
                                                            #line 1384 "PrintCLike.cpp.template"
                                                                }
                                                              }
                                                              else if (! isPython())
                                                              {
                                                            #line 1881 "PrintCLike.cpp"
  append(L"\n");
  append(L"switch ");
                                                            #line 1389 "PrintCLike.cpp.template"
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
                                                            #line 1428 "PrintCLike.cpp.template"
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
                                                            #line 1436 "PrintCLike.cpp.template"
                                                                  print(format.toString<wchar_t>(node->cases.size() + 1));
                                                            #line 1939 "PrintCLike.cpp"
  append(L":\n");
  append(L"  pass");
                                                            #line 1438 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1946 "PrintCLike.cpp"
  append(L"\n");
  append(L"case -");
                                                            #line 1442 "PrintCLike.cpp.template"
                                                                  print(format.toString<wchar_t>(node->cases.size() + 1));
                                                                  if (isScala())
                                                                  {
                                                            #line 1953 "PrintCLike.cpp"
  append(L" =>");
                                                            #line 1446 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isHaxe())
                                                                  {
                                                            #line 1959 "PrintCLike.cpp"
  append(L":");
                                                            #line 1450 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 1965 "PrintCLike.cpp"
  append(L":");
                                                            #line 1453 "PrintCLike.cpp.template"
                                                                    if (! isGo())
                                                                    {
                                                            #line 1970 "PrintCLike.cpp"
  append(L"\n");
  append(L"  break");
                                                            #line 1456 "PrintCLike.cpp.template"
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
                                                            #line 1469 "PrintCLike.cpp.template"
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
                                                            #line 1491 "PrintCLike.cpp.template"
                                                                print(className.c_str());
                                                            #line 2016 "PrintCLike.cpp"
  append(L") ");
                                                            #line 1492 "PrintCLike.cpp.template"
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
                                                            #line 1504 "PrintCLike.cpp.template"
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
                                                            #line 1515 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 2048 "PrintCLike.cpp"
  append(L"top = -1");
                                                            #line 1516 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                            #line 2053 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 1519 "PrintCLike.cpp.template"
                                                                if (useGlr && ! isCpp())
                                                                {
                                                                  print(thiz());
                                                            #line 2060 "PrintCLike.cpp"
  append(L"thread = ");
                                                            #line 1522 "PrintCLike.cpp.template"
                                                                }
                                                                print(thiz());
                                                            #line 2065 "PrintCLike.cpp"
  append(L"parse(");
                                                            #line 1524 "PrintCLike.cpp.template"
                                                                print(format.toString<wchar_t>(node->nonterminalCode));
                                                            #line 2069 "PrintCLike.cpp"
  append(L", ");
                                                            #line 1525 "PrintCLike.cpp.template"
                                                                print(format.toString<wchar_t>((*grammar->states)[node->state]->getStateId()));
                                                                if (tree)
                                                                {
                                                            #line 2075 "PrintCLike.cpp"
  append(L", ");
                                                            #line 1528 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 2079 "PrintCLike.cpp"
  append(L"eventHandler");
                                                            #line 1529 "PrintCLike.cpp.template"
                                                                }
                                                                if (useGlr)
                                                                {
                                                            #line 2085 "PrintCLike.cpp"
  append(L", ");
                                                            #line 1532 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 2089 "PrintCLike.cpp"
  append(L"thread");
                                                            #line 1533 "PrintCLike.cpp.template"
                                                                }
                                                            #line 2093 "PrintCLike.cpp"
  append(L")");
                                                            #line 1534 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                              }
                                                              else
                                                              {
                                                                if (trace)
                                                                {
                                                            #line 2102 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 1541 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 2107 "PrintCLike.cpp"
  append(L"traceNonterminal(");
                                                            #line 1542 "PrintCLike.cpp.template"
                                                                  print(stringIntroducer());
                                                            #line 2111 "PrintCLike.cpp"
  append(L"\"");
                                                            #line 1543 "PrintCLike.cpp.template"
                                                                  print(methodPrefix, wcslen(methodPrefix) - 1);
                                                            #line 2115 "PrintCLike.cpp"
  append(L"\", ");
                                                            #line 1544 "PrintCLike.cpp.template"
                                                                  print(stringIntroducer());
                                                            #line 2119 "PrintCLike.cpp"
  append(L"\"start\", ");
                                                            #line 1545 "PrintCLike.cpp.template"
                                                                  print(stringIntroducer());
                                                            #line 2123 "PrintCLike.cpp"
  append(L"\"");
                                                            #line 1546 "PrintCLike.cpp.template"
                                                                  print(node->name);
                                                            #line 2127 "PrintCLike.cpp"
  append(L"\")");
                                                            #line 1547 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                                if (tree && methodPrefix != methodPrefixTry)
                                                                {
                                                            #line 2134 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 1552 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 2139 "PrintCLike.cpp"
  append(L"eventHandler");
                                                            #line 1553 "PrintCLike.cpp.template"
                                                                  print(arrow());
                                                                  if (isGo())
                                                                  {
                                                            #line 2145 "PrintCLike.cpp"
  append(L"S");
                                                            #line 1556 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 2151 "PrintCLike.cpp"
  append(L"s");
                                                            #line 1559 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 2155 "PrintCLike.cpp"
  append(L"tartNonterminal(");
                                                            #line 1560 "PrintCLike.cpp.template"
                                                                  print(stringIntroducer());
                                                            #line 2159 "PrintCLike.cpp"
  append(L"\"");
                                                            #line 1561 "PrintCLike.cpp.template"
                                                                  print(node->name);
                                                            #line 2163 "PrintCLike.cpp"
  append(L"\", ");
                                                            #line 1562 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 2167 "PrintCLike.cpp"
  append(L"e0)");
                                                            #line 1563 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                                visitNodeList(node->firstChild);

                                                                if (tree && methodPrefix != methodPrefixTry)
                                                                {
                                                            #line 2176 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 1570 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 2181 "PrintCLike.cpp"
  append(L"eventHandler");
                                                            #line 1571 "PrintCLike.cpp.template"
                                                                  print(arrow());
                                                                  if (isGo())
                                                                  {
                                                            #line 2187 "PrintCLike.cpp"
  append(L"E");
                                                            #line 1574 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 2193 "PrintCLike.cpp"
  append(L"e");
                                                            #line 1577 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 2197 "PrintCLike.cpp"
  append(L"ndNonterminal(");
                                                            #line 1578 "PrintCLike.cpp.template"
                                                                  print(stringIntroducer());
                                                            #line 2201 "PrintCLike.cpp"
  append(L"\"");
                                                            #line 1579 "PrintCLike.cpp.template"
                                                                  print(node->name);
                                                            #line 2205 "PrintCLike.cpp"
  append(L"\", ");
                                                            #line 1580 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 2209 "PrintCLike.cpp"
  append(L"e0)");
                                                            #line 1581 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                                if (trace)
                                                                {
                                                            #line 2216 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 1586 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 2221 "PrintCLike.cpp"
  append(L"traceNonterminal(");
                                                            #line 1587 "PrintCLike.cpp.template"
                                                                  print(stringIntroducer());
                                                            #line 2225 "PrintCLike.cpp"
  append(L"\"");
                                                            #line 1588 "PrintCLike.cpp.template"
                                                                  print(methodPrefix, wcslen(methodPrefix) - 1);
                                                            #line 2229 "PrintCLike.cpp"
  append(L"\", ");
                                                            #line 1589 "PrintCLike.cpp.template"
                                                                  print(stringIntroducer());
                                                            #line 2233 "PrintCLike.cpp"
  append(L"\"end\", ");
                                                            #line 1590 "PrintCLike.cpp.template"
                                                                  print(stringIntroducer());
                                                            #line 2237 "PrintCLike.cpp"
  append(L"\"");
                                                            #line 1591 "PrintCLike.cpp.template"
                                                                  print(node->name);
                                                            #line 2241 "PrintCLike.cpp"
  append(L"\")");
                                                            #line 1592 "PrintCLike.cpp.template"
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
                                                            #line 1602 "PrintCLike.cpp.template"
                                                              }
                                                              print(rightBrace());
                                                              if ((isJavascript()  && ! isTypescript()) && node->isStartSymbol())
                                                              {
                                                            #line 2261 "PrintCLike.cpp"
  append(L";");
                                                            #line 1606 "PrintCLike.cpp.template"
                                                              }
                                                            #line 2265 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 1608 "PrintCLike.cpp.template"
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
                                                            #line 1629 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 2292 "PrintCLike.cpp"
  append(L"whitespace");
                                                            #line 1630 "PrintCLike.cpp.template"
                                                                  if (! isScala())
                                                                  {
                                                            #line 2297 "PrintCLike.cpp"
  append(L"()");
                                                            #line 1632 "PrintCLike.cpp.template"
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
                                                            #line 1640 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                                  print(thiz());
                                                            #line 2313 "PrintCLike.cpp"
  append(L"viable");
                                                            #line 1642 "PrintCLike.cpp.template"
                                                                  print(ifRightParen());
                                                                  print(leftBrace());
                                                                  increaseIndent();
                                                                }
                                                            #line 2320 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 1647 "PrintCLike.cpp.template"
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
                                                            #line 1669 "PrintCLike.cpp.template"
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
                                                            #line 1698 "PrintCLike.cpp.template"
                                                                int spaces = isPython() ? 0 : Math::max(0, static_cast<int>(piIndent) - getIndent());
                                                                print(spaces, L" ");
                                                                print(lineCommentPrefix());
                                                            #line 2381 "PrintCLike.cpp"
  append(L"line ");
                                                            #line 1701 "PrintCLike.cpp.template"
                                                                print(format.toString<wchar_t>(node->line));
                                                            #line 2385 "PrintCLike.cpp"
  append(L" \"");
                                                            #line 1702 "PrintCLike.cpp.template"
                                                                print(node->fileName);
                                                            #line 2389 "PrintCLike.cpp"
  append(L"\"\n");
                                                            #line 1704 "PrintCLike.cpp.template"
                                                                print(spaces, L" ");
                                                                wchar_t *reIndented = format.reIndent(node->content, spaces);
                                                                print(reIndented);
                                                            #line 2395 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 1708 "PrintCLike.cpp.template"
                                                                free(reIndented);
                                                                print(spaces, L" ");
                                                                print(lineCommentPrefix());
                                                            #line 2401 "PrintCLike.cpp"
  append(L"line ");
                                                            #line 1711 "PrintCLike.cpp.template"
                                                                print(format.toString<wchar_t>(lineNo + 1));
                                                            #line 2405 "PrintCLike.cpp"
  append(L" \"");
                                                            #line 1712 "PrintCLike.cpp.template"
                                                                print(wFileName.c_str());
                                                            #line 2409 "PrintCLike.cpp"
  append(L"\"");
                                                            #line 1713 "PrintCLike.cpp.template"
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
                                                            #line 1725 "PrintCLike.cpp.template"
                                                                if (noLexer)
                                                                {
                                                            #line 2429 "PrintCLike.cpp"
  append(L", l");
                                                            #line 1727 "PrintCLike.cpp.template"
                                                                }
                                                                if (tree)
                                                                {
                                                            #line 2435 "PrintCLike.cpp"
  append(L", parsingEventHandler");
                                                            #line 1730 "PrintCLike.cpp.template"
                                                                }
                                                            #line 2439 "PrintCLike.cpp"
  append(L")");
                                                            #line 1731 "PrintCLike.cpp.template"
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
                                                            #line 1762 "PrintCLike.cpp.template"
                                                                  if (tree)
                                                                  {
                                                            #line 2478 "PrintCLike.cpp"
  append(L", parsingEventHandler");
                                                            #line 1765 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 2482 "PrintCLike.cpp"
  append(L");");
                                                            #line 1766 "PrintCLike.cpp.template"
                                                                  print(rightBrace());
                                                            #line 2486 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 1768 "PrintCLike.cpp.template"
                                                                }
                                                                openMethod(voidType(), L"", L"initialize", args.c_str());
                                                              }
                                                              print(leftBrace());
                                                              if (tree)
                                                              {
                                                            #line 2495 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 1775 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 2500 "PrintCLike.cpp"
  append(L"eventHandler = parsingEventHandler");
                                                            #line 1776 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                              }
                                                            #line 2505 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 1779 "PrintCLike.cpp.template"
                                                              print(thiz());
                                                            #line 2510 "PrintCLike.cpp"
  append(L"input = ");
                                                            #line 1780 "PrintCLike.cpp.template"
                                                              if (isHaxe())
                                                              {
                                                            #line 2515 "PrintCLike.cpp"
  append(L"Bytes.ofString(source)");
                                                            #line 1782 "PrintCLike.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 2521 "PrintCLike.cpp"
  append(L"source");
                                                            #line 1785 "PrintCLike.cpp.template"
                                                              }
                                                              print(semicolon());
                                                              if (noLexer)
                                                              {
                                                            #line 2528 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 1790 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 2533 "PrintCLike.cpp"
  append(L"lexer = l");
                                                            #line 1791 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 2537 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 1793 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 2542 "PrintCLike.cpp"
  append(L"lexer.reset(input)");
                                                            #line 1794 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                              }
                                                              else if (isGo() || isPython())
                                                              {
                                                            #line 2549 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 1799 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 2554 "PrintCLike.cpp"
  append(L"size = len(source)");
                                                            #line 1800 "PrintCLike.cpp.template"
                                                              }
                                                              else if (! isCpp())
                                                              {
                                                            #line 2560 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 1804 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 2565 "PrintCLike.cpp"
  append(L"size = source.");
                                                            #line 1805 "PrintCLike.cpp.template"
                                                                print(isCSharp() ? L"L" : L"l");
                                                            #line 2569 "PrintCLike.cpp"
  append(L"ength");
                                                            #line 1806 "PrintCLike.cpp.template"
                                                                if (! isJavascript() && ! isTypescript() && ! isScala() && ! isHaxe() && ! isCSharp() && ! (isJava() && codepoints))
                                                                {
                                                            #line 2574 "PrintCLike.cpp"
  append(L"()");
                                                            #line 1808 "PrintCLike.cpp.template"
                                                                }
                                                                print(semicolon());
                                                              }
                                                              if (! interfaceName.empty() && useGlr)
                                                              {
                                                            #line 2582 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 1814 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                                print(isGo() ? L"R" : L"r");
                                                            #line 2588 "PrintCLike.cpp"
  append(L"eset()");
                                                            #line 1816 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                print(rightBrace());
                                                            #line 2593 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 1819 "PrintCLike.cpp.template"
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
                                                            #line 1827 "PrintCLike.cpp.template"
                                                                }
                                                                else if (isGo())
                                                                {
                                                            #line 2610 "PrintCLike.cpp"
  append(L"\n");
  append(L"  this.iStack = make([]int, 192)\n");
  append(L"  this.top = -1");
                                                            #line 1832 "PrintCLike.cpp.template"
                                                                }
                                                              }
                                                              if (useGlr)
                                                              {
                                                            #line 2619 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 1837 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 2624 "PrintCLike.cpp"
  append(L"maxId = 0");
                                                            #line 1838 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 2628 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 1840 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 2633 "PrintCLike.cpp"
  append(L"thread = ");
                                                            #line 1841 "PrintCLike.cpp.template"
                                                                if (isScala())
                                                                {
                                                            #line 2638 "PrintCLike.cpp"
  append(L"new ");
                                                            #line 1843 "PrintCLike.cpp.template"
                                                                  print(className.c_str());
                                                            #line 2642 "PrintCLike.cpp"
  append(L".ParsingThread");
                                                            #line 1844 "PrintCLike.cpp.template"
                                                                }
                                                                else if (isPython())
                                                                {
                                                                  print(className.c_str());
                                                            #line 2649 "PrintCLike.cpp"
  append(L".ParsingThread()");
                                                            #line 1848 "PrintCLike.cpp.template"
                                                                }
                                                                else if (isGo())
                                                                {
                                                            #line 2655 "PrintCLike.cpp"
  append(L"new(ParsingThread)");
                                                            #line 1851 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 2661 "PrintCLike.cpp"
  append(L"new ParsingThread()");
                                                            #line 1854 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                                if (isCSharp() || isCpp() || isHaxe() || isScala() || isTypescript() || isGo() || isPython())
                                                                {
                                                            #line 2668 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 1859 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 2673 "PrintCLike.cpp"
  append(L"thread");
                                                            #line 1860 "PrintCLike.cpp.template"
                                                                  print(arrow());
                                                            #line 2677 "PrintCLike.cpp"
  append(L"parser = ");
                                                            #line 1861 "PrintCLike.cpp.template"
                                                                  if (isPython())
                                                                  {
                                                            #line 2682 "PrintCLike.cpp"
  append(L"self");
                                                            #line 1863 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 2688 "PrintCLike.cpp"
  append(L"this");
                                                            #line 1866 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(semicolon());
                                                                }
                                                            #line 2694 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 1870 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 2699 "PrintCLike.cpp"
  append(L"thread");
                                                            #line 1871 "PrintCLike.cpp.template"
                                                                print(arrow());
                                                              }
                                                              else
                                                              {
                                                            #line 2706 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 1876 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                              }
                                                              print(isGo() ? L"R" : L"r");
                                                            #line 2713 "PrintCLike.cpp"
  append(L"eset(0, 0, 0)");
                                                            #line 1879 "PrintCLike.cpp.template"
                                                              print(semicolon());
                                                              print(rightBrace());
                                                            #line 2718 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 1882 "PrintCLike.cpp.template"
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
                                                            #line 1895 "PrintCLike.cpp.template"
                                                                if (useGlr)
                                                                {
                                                            #line 2739 "PrintCLike.cpp"
  append(L"thread.");
                                                            #line 1897 "PrintCLike.cpp.template"
                                                                }
                                                            #line 2743 "PrintCLike.cpp"
  append(L"reset(l, b, e);\n");
  append(L"};\n");
                                                            #line 1900 "PrintCLike.cpp.template"
                                                                openMethod(L"static ", stringType(), L"getOffendingToken", L"ParseException e");
                                                                print(leftBrace());
                                                            #line 2749 "PrintCLike.cpp"
  append(L"\n");
  append(L"  var o = e.getOffending();\n");
  append(L"  return o >= 0 ? ");
                                                            #line 1904 "PrintCLike.cpp.template"
                                                                print(staticPrefix());
                                                            #line 2755 "PrintCLike.cpp"
  append(L"TOKEN[o] : ");
                                                            #line 1905 "PrintCLike.cpp.template"
                                                                print(nullPtr());
                                                            #line 2759 "PrintCLike.cpp"
  append(L";\n");
  append(L"};\n");
                                                            #line 1908 "PrintCLike.cpp.template"
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
                                                            #line 1918 "PrintCLike.cpp.template"
                                                                }
                                                            #line 2776 "PrintCLike.cpp"
  append(L"\n");
  append(L"getOffendingToken(e: ParseException)\n");
  append(L"{");
  append(L"\n");
  append(L"  var o = e.getOffending();\n");
  append(L"  return o >= 0 ? Parser.TOKEN[o] : ");
                                                            #line 1924 "PrintCLike.cpp.template"
                                                                print(nullPtr());
                                                            #line 2785 "PrintCLike.cpp"
  append(L";\n");
  append(L"}\n");
                                                            #line 1927 "PrintCLike.cpp.template"
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
                                                            #line 1941 "PrintCLike.cpp.template"
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
                                                            #line 1950 "PrintCLike.cpp.template"
                                                                print(className.c_str());
                                                            #line 2818 "PrintCLike.cpp"
  append(L".TOKEN[e.getOffending()]\n");
                                                            #line 1952 "PrintCLike.cpp.template"
                                                              }
                                                              else
                                                              {
                                                                openMethod(stringType(), L"static ", L"getOffendingToken", L"ParseException e");
                                                                print(leftBrace());
                                                            #line 2826 "PrintCLike.cpp"
  append(L"\n");
  append(L"  return e.getOffending() < 0 ? ");
                                                            #line 1958 "PrintCLike.cpp.template"
                                                                print(nullPtr());
                                                            #line 2831 "PrintCLike.cpp"
  append(L" : TOKEN[e.getOffending()];");
                                                            #line 1960 "PrintCLike.cpp.template"
                                                                print(rightBrace());
                                                            #line 2835 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 1962 "PrintCLike.cpp.template"
                                                              }

                                                              if (isJavascript() || isTypescript() || isHaxe())
                                                              {
                                                                openMethod(L"", L"static ", L"getExpectedTokenSet", L"ParseException e");
                                                                print(leftBrace());
                                                            #line 2844 "PrintCLike.cpp"
  append(L"\n");
  append(L"  var expected");
                                                            #line 1969 "PrintCLike.cpp.template"
                                                                if (isTypescript())
                                                                {
                                                            #line 2850 "PrintCLike.cpp"
  append(L": string[]");
                                                            #line 1971 "PrintCLike.cpp.template"
                                                                }
                                                            #line 2854 "PrintCLike.cpp"
  append(L";\n");
  append(L"  if (e.getExpected() < 0)\n");
  append(L"  {\n");
  append(L"    expected = ");
                                                            #line 1975 "PrintCLike.cpp.template"
                                                                print(staticPrefix());
                                                            #line 2861 "PrintCLike.cpp"
  append(L"getTokenSet(- e.getState());\n");
  append(L"  }\n");
  append(L"  else\n");
  append(L"  {\n");
  append(L"    expected = [");
                                                            #line 1980 "PrintCLike.cpp.template"
                                                                print(staticPrefix());
                                                                print(isGo() ? L"token" : L"TOKEN");
                                                            #line 2870 "PrintCLike.cpp"
  append(L"[e.getExpected()]];\n");
  append(L"  }\n");
  append(L"  return expected;\n");
  append(L"}");
                                                            #line 1985 "PrintCLike.cpp.template"
                                                                if (! isTypescript())
                                                                {
                                                            #line 2878 "PrintCLike.cpp"
  append(L";");
                                                            #line 1987 "PrintCLike.cpp.template"
                                                                }
                                                            #line 2882 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 1989 "PrintCLike.cpp.template"
                                                                if (isHaxe())
                                                                {
                                                            #line 2887 "PrintCLike.cpp"
  append(L"\n");
  append(L"public function getErrorMessage(e: ParseException): String");
                                                            #line 1992 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                                  openMethod(stringType(), L"static ", L"getErrorMessage", L"ParseException e");
                                                                }
                                                                print(leftBrace());
                                                            #line 2897 "PrintCLike.cpp"
  append(L"\n");
  append(L"  var message = e.getMessage();");
                                                            #line 1999 "PrintCLike.cpp.template"
                                                                if (useGlr)
                                                                {
                                                                  increaseIndent();
                                                            #line 2904 "PrintCLike.cpp"
  append(L"\n");
  append(L"if ");
                                                            #line 2003 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                            #line 2909 "PrintCLike.cpp"
  append(L"e.isAmbiguousInput()");
                                                            #line 2004 "PrintCLike.cpp.template"
                                                                  print(ifRightParen());
                                                                  print(leftBrace());
                                                            #line 2914 "PrintCLike.cpp"
  append(L"\n");
  append(L"  message += \"\\n\"");
                                                            #line 2007 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                            #line 2919 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 2009 "PrintCLike.cpp.template"
                                                                  print(elseWithBraces());
                                                                }
                                                            #line 2924 "PrintCLike.cpp"
  append(L"\n");
  append(L"  var found = ");
                                                            #line 2012 "PrintCLike.cpp.template"
                                                                if (! isHaxe())
                                                                {
                                                                  print(L"this.");
                                                                }
                                                            #line 2932 "PrintCLike.cpp"
  append(L"getOffendingToken(e);\n");
  append(L"  var tokenSet = ");
                                                            #line 2017 "PrintCLike.cpp.template"
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
                                                            #line 2028 "PrintCLike.cpp.template"
                                                                if (useGlr)
                                                                {
                                                                  decreaseIndent();
                                                            #line 2952 "PrintCLike.cpp"
  append(L"\n");
  append(L"  }");
                                                            #line 2032 "PrintCLike.cpp.template"
                                                                }
                                                            #line 2957 "PrintCLike.cpp"
  append(L"\n");
  append(L"  var prefix = ");
                                                            #line 2034 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 2962 "PrintCLike.cpp"
  append(L"input.");
                                                            #line 2035 "PrintCLike.cpp.template"
                                                                if (isHaxe())
                                                                {
                                                            #line 2967 "PrintCLike.cpp"
  append(L"getS");
                                                            #line 2037 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 2973 "PrintCLike.cpp"
  append(L"subs");
                                                            #line 2040 "PrintCLike.cpp.template"
                                                                }
                                                            #line 2977 "PrintCLike.cpp"
  append(L"tring(0, e.getBegin());\n");
  append(L"  var lines = prefix.split(\"\\n\");\n");
  append(L"  var line = lines.length;\n");
  append(L"  var column = lines[line - 1].length + 1;\n");
  append(L"  return message\n");
  append(L"       + \"at line \" + line + \", column \" + column + \":\\n...\"\n");
  append(L"       + ");
                                                            #line 2047 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                                if (isHaxe())
                                                                {
                                                            #line 2989 "PrintCLike.cpp"
  append(L"input.getString(e.getBegin(), input.length < e.getBegin() + 64 ? input.length - e.getBegin() : 64");
                                                            #line 2051 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 2995 "PrintCLike.cpp"
  append(L"input.substring(e.getBegin(), Math.min(");
                                                            #line 2054 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 2999 "PrintCLike.cpp"
  append(L"input.length, e.getBegin() + 64)");
                                                            #line 2056 "PrintCLike.cpp.template"
                                                                }
                                                            #line 3003 "PrintCLike.cpp"
  append(L")\n");
  append(L"       + \"...\";\n");
  append(L"}");
                                                            #line 2059 "PrintCLike.cpp.template"
                                                                if (! isTypescript())
                                                                {
                                                            #line 3010 "PrintCLike.cpp"
  append(L";");
                                                            #line 2061 "PrintCLike.cpp.template"
                                                                }
                                                            #line 3014 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 2063 "PrintCLike.cpp.template"
                                                              }
                                                              else if (isJava())
                                                              {
                                                                openMethod(L"String[] ", L"static ", L"getExpectedTokenSet", L"ParseException e");
                                                                print(leftBrace());
                                                            #line 3022 "PrintCLike.cpp"
  append(L"\n");
  append(L"  String[] expected");
                                                            #line 2069 "PrintCLike.cpp.template"
                                                                if (useGlr)
                                                                {
                                                            #line 3028 "PrintCLike.cpp"
  append(L" = {}");
                                                            #line 2071 "PrintCLike.cpp.template"
                                                                }
                                                            #line 3032 "PrintCLike.cpp"
  append(L";\n");
  append(L"  if (e.getExpected() >= 0)\n");
  append(L"  {\n");
  append(L"    expected = new String[]{TOKEN[e.getExpected()]};\n");
  append(L"  }\n");
  append(L"  else");
                                                            #line 2077 "PrintCLike.cpp.template"
                                                                if (useGlr)
                                                                {
                                                            #line 3042 "PrintCLike.cpp"
  append(L" if (! e.isAmbiguousInput())");
                                                            #line 2079 "PrintCLike.cpp.template"
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
                                                            #line 2090 "PrintCLike.cpp.template"
                                                                if (useGlr)
                                                                {
                                                            #line 3060 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if ");
                                                            #line 2093 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                            #line 3065 "PrintCLike.cpp"
  append(L"e.isAmbiguousInput()");
                                                            #line 2094 "PrintCLike.cpp.template"
                                                                  print(ifRightParen());
                                                                  printIndented(1, leftBrace());
                                                            #line 3070 "PrintCLike.cpp"
  append(L"\n");
  append(L"    message += \"\\n\"");
                                                            #line 2097 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                            #line 3075 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 2099 "PrintCLike.cpp.template"
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
                                                            #line 2111 "PrintCLike.cpp.template"
                                                                if (useGlr)
                                                                {
                                                                  decreaseIndent();
                                                            #line 3096 "PrintCLike.cpp"
  append(L"\n");
  append(L"  }");
                                                            #line 2115 "PrintCLike.cpp.template"
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
                                                            #line 2127 "PrintCLike.cpp.template"
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
                                                            #line 2139 "PrintCLike.cpp.template"
                                                                }
                                                                if (! interfaceName.empty())
                                                                {
                                                            #line 3135 "PrintCLike.cpp"
  append(L"\n");
  append(L"public void parse()\n");
  append(L"{\n");
  append(L"  parse_");
                                                            #line 2145 "PrintCLike.cpp.template"
                                                                  print(Format::acceptableName<WString>(grammar->startSymbol()->name).c_str());
                                                            #line 3142 "PrintCLike.cpp"
  append(L"();\n");
  append(L"}\n");
                                                            #line 2148 "PrintCLike.cpp.template"
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
                                                            #line 2170 "PrintCLike.cpp.template"
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
                                                            #line 2178 "PrintCLike.cpp.template"
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
                                                            #line 2189 "PrintCLike.cpp.template"
                                                                if (useGlr)
                                                                {
                                                                  decreaseIndent();
                                                            #line 3197 "PrintCLike.cpp"
  append(L"\n");
  append(L"  }");
                                                            #line 2193 "PrintCLike.cpp.template"
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
                                                            #line 2203 "PrintCLike.cpp.template"
                                                                if (! interfaceName.empty())
                                                                {
                                                            #line 3215 "PrintCLike.cpp"
  append(L"\n");
  append(L"public void parse()\n");
  append(L"{\n");
  append(L"  parse_");
                                                            #line 2208 "PrintCLike.cpp.template"
                                                                  print(Format::acceptableName<WString>(grammar->startSymbol()->name).c_str());
                                                            #line 3222 "PrintCLike.cpp"
  append(L"();\n");
  append(L"}\n");
                                                            #line 2211 "PrintCLike.cpp.template"
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
                                                            #line 2225 "PrintCLike.cpp.template"
                                                                print(className.c_str());
                                                            #line 3244 "PrintCLike.cpp"
  append(L") GetErrorMessage(e ParseError) string {\n");
  append(L"  message := e.Error()");
                                                            #line 2228 "PrintCLike.cpp.template"
                                                                if (useGlr)
                                                                {
                                                            #line 3250 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if e.IsAmbiguousInput() {\n");
  append(L"    message += \"\\n\"\n");
  append(L"  } else {");
                                                            #line 2233 "PrintCLike.cpp.template"
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
                                                            #line 2261 "PrintCLike.cpp.template"
                                                                if (useGlr)
                                                                {
                                                                  decreaseIndent();
                                                            #line 3290 "PrintCLike.cpp"
  append(L"\n");
  append(L"  }");
                                                            #line 2265 "PrintCLike.cpp.template"
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
                                                            #line 2290 "PrintCLike.cpp.template"
                                                                if (! interfaceName.empty())
                                                                {
                                                            #line 3323 "PrintCLike.cpp"
  append(L"\n");
  append(L"public void parse()\n");
  append(L"{\n");
  append(L"  parse_");
                                                            #line 2295 "PrintCLike.cpp.template"
                                                                  print(Format::acceptableName<WString>(grammar->startSymbol()->name).c_str());
                                                            #line 3330 "PrintCLike.cpp"
  append(L"();\n");
  append(L"}\n");
                                                            #line 2298 "PrintCLike.cpp.template"
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
                                                            #line 2306 "PrintCLike.cpp.template"
                                                                print(className.c_str());
                                                            #line 3346 "PrintCLike.cpp"
  append(L".getTokenSet(- e.state)\n");
  append(L"  else:\n");
  append(L"    return [");
                                                            #line 2309 "PrintCLike.cpp.template"
                                                                print(className.c_str());
                                                            #line 3352 "PrintCLike.cpp"
  append(L".TOKEN[e.expected]]\n");
  append(L"\n");
  append(L"def getErrorMessage(self, e):\n");
  append(L"  message = e.error()");
                                                            #line 2313 "PrintCLike.cpp.template"
                                                                if (useGlr)
                                                                {
                                                            #line 3360 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if e.isAmbiguousInput():\n");
  append(L"    message += \"\\n\"\n");
  append(L"  else:");
                                                            #line 2318 "PrintCLike.cpp.template"
                                                                  increaseIndent();
                                                                }
                                                            #line 3368 "PrintCLike.cpp"
  append(L"\n");
  append(L"  found = ");
                                                            #line 2321 "PrintCLike.cpp.template"
                                                                print(className.c_str());
                                                            #line 3373 "PrintCLike.cpp"
  append(L".getOffendingToken(e)\n");
  append(L"  if found != \"\":\n");
  append(L"    message += \", found \"\n");
  append(L"    message += found\n");
  append(L"  expected = ");
                                                            #line 2326 "PrintCLike.cpp.template"
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
                                                            #line 2343 "PrintCLike.cpp.template"
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
                                                            #line 2367 "PrintCLike.cpp.template"
                                                                if (! interfaceName.empty())
                                                                {
                                                            #line 3428 "PrintCLike.cpp"
  append(L"\n");
  append(L"public void parse()\n");
  append(L"{\n");
  append(L"  parse_");
                                                            #line 2372 "PrintCLike.cpp.template"
                                                                  print(Format::acceptableName<WString>(grammar->startSymbol()->name).c_str());
                                                            #line 3435 "PrintCLike.cpp"
  append(L"();\n");
  append(L"}\n");
                                                            #line 2375 "PrintCLike.cpp.template"
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
                                                            #line 2398 "PrintCLike.cpp.template"
                                                                print(isGo() ? L"token" : L"TOKEN");
                                                            #line 3466 "PrintCLike.cpp"
  append(L"[e.expected];\n");
  append(L"    set[1] = 0;\n");
  append(L"  }\n");
  append(L"}\n");
  append(L"\n");
  append(L"static std::");
                                                            #line 2404 "PrintCLike.cpp.template"
                                                                if (stringIntroducer()[0]) append(L"w");
                                                            #line 3475 "PrintCLike.cpp"
  append(L"string to_");
                                                            #line 2405 "PrintCLike.cpp.template"
                                                                if (stringIntroducer()[0]) append(L"w");
                                                            #line 3479 "PrintCLike.cpp"
  append(L"string(int i)\n");
  append(L"{\n");
  append(L"  const ");
                                                            #line 2408 "PrintCLike.cpp.template"
                                                                if (stringIntroducer()[0]) append(L"w");
                                                            #line 3485 "PrintCLike.cpp"
  append(L"char");
                                                            #line 2409 "PrintCLike.cpp.template"
                                                                if (stringIntroducer()[0]) append(L"_t");
                                                            #line 3489 "PrintCLike.cpp"
  append(L" *sign = i < 0 ? ");
                                                            #line 2410 "PrintCLike.cpp.template"
                                                                append(stringIntroducer());
                                                            #line 3493 "PrintCLike.cpp"
  append(L"\"-\" : ");
                                                            #line 2411 "PrintCLike.cpp.template"
                                                                append(stringIntroducer());
                                                            #line 3497 "PrintCLike.cpp"
  append(L"\"\";\n");
  append(L"  std::");
                                                            #line 2413 "PrintCLike.cpp.template"
                                                                if (stringIntroducer()[0]) append(L"w");
                                                            #line 3502 "PrintCLike.cpp"
  append(L"string a;\n");
  append(L"  do\n");
  append(L"  {\n");
  append(L"    a += ");
                                                            #line 2417 "PrintCLike.cpp.template"
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
                                                            #line 2427 "PrintCLike.cpp.template"
                                                                if (stringIntroducer()[0]) append(L"w");
                                                            #line 3522 "PrintCLike.cpp"
  append(L"string getErrorMessage(const ParseException &e)\n");
  append(L"{\n");
  append(L"  std::");
                                                            #line 2430 "PrintCLike.cpp.template"
                                                                if (stringIntroducer()[0]) append(L"w");
                                                            #line 3528 "PrintCLike.cpp"
  append(L"string message(e.getMessage());");
                                                            #line 2431 "PrintCLike.cpp.template"
                                                                if (useGlr)
                                                                {
                                                            #line 3533 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if (e.isAmbiguousInput())\n");
  append(L"  {\n");
  append(L"    message += ");
                                                            #line 2436 "PrintCLike.cpp.template"
                                                                  print(stringIntroducer());
                                                            #line 3540 "PrintCLike.cpp"
  append(L"\"\\n\";\n");
  append(L"  }\n");
  append(L"  else\n");
  append(L"  {");
                                                            #line 2440 "PrintCLike.cpp.template"
                                                                  increaseIndent();
                                                                }
                                                            #line 3548 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 2443 "PrintCLike.cpp.template"
                                                                print(stringType());
                                                            #line 3553 "PrintCLike.cpp"
  append(L"found = getOffendingToken(e);\n");
  append(L"  if (found != 0)\n");
  append(L"  {\n");
  append(L"    message += ");
                                                            #line 2447 "PrintCLike.cpp.template"
                                                                print(stringIntroducer());
                                                            #line 3560 "PrintCLike.cpp"
  append(L"\", found \";\n");
  append(L"    message += found;\n");
  append(L"  }\n");
  append(L"  ");
                                                            #line 2451 "PrintCLike.cpp.template"
                                                                print(stringType());
                                                            #line 3567 "PrintCLike.cpp"
  append(L"expected[64];\n");
  append(L"  getExpectedTokenSet(e, expected, sizeof expected / sizeof *expected);\n");
  append(L"  message += ");
                                                            #line 2454 "PrintCLike.cpp.template"
                                                                print(stringIntroducer());
                                                            #line 3573 "PrintCLike.cpp"
  append(L"\"\\nwhile expecting \";\n");
  append(L"  ");
                                                            #line 2456 "PrintCLike.cpp.template"
                                                                print(stringType());
                                                            #line 3578 "PrintCLike.cpp"
  append(L"delimiter(expected[1] ? ");
                                                            #line 2457 "PrintCLike.cpp.template"
                                                                print(stringIntroducer());
                                                            #line 3582 "PrintCLike.cpp"
  append(L"\"[\" : ");
                                                            #line 2458 "PrintCLike.cpp.template"
                                                                print(stringIntroducer());
                                                            #line 3586 "PrintCLike.cpp"
  append(L"\"\");\n");
  append(L"  for (");
                                                            #line 2460 "PrintCLike.cpp.template"
                                                                print(stringType());
                                                            #line 3591 "PrintCLike.cpp"
  append(L"*x = expected; *x; ++x)\n");
  append(L"  {\n");
  append(L"    message += delimiter;\n");
  append(L"    message += *x;\n");
  append(L"    delimiter = ");
                                                            #line 2465 "PrintCLike.cpp.template"
                                                                print(stringIntroducer());
                                                            #line 3599 "PrintCLike.cpp"
  append(L"\", \";\n");
  append(L"  }\n");
  append(L"  message += expected[1] ? ");
                                                            #line 2468 "PrintCLike.cpp.template"
                                                                print(stringIntroducer());
                                                            #line 3605 "PrintCLike.cpp"
  append(L"\"]\\n\" : ");
                                                            #line 2469 "PrintCLike.cpp.template"
                                                                print(stringIntroducer());
                                                            #line 3609 "PrintCLike.cpp"
  append(L"\"\\n\";\n");
  append(L"  int size = e.getEnd() - e.getBegin();\n");
  append(L"  if (size != 0 && found == 0)\n");
  append(L"  {\n");
  append(L"    message += ");
                                                            #line 2474 "PrintCLike.cpp.template"
                                                                print(stringIntroducer());
                                                            #line 3617 "PrintCLike.cpp"
  append(L"\"after successfully scanning \";\n");
  append(L"    message += to_");
                                                            #line 2476 "PrintCLike.cpp.template"
                                                                if (stringIntroducer()[0]) append(L"w");
                                                            #line 3622 "PrintCLike.cpp"
  append(L"string(size);\n");
  append(L"    message += ");
                                                            #line 2478 "PrintCLike.cpp.template"
                                                                print(stringIntroducer());
                                                            #line 3627 "PrintCLike.cpp"
  append(L"\" characters beginning \";\n");
  append(L"  }");
                                                            #line 2480 "PrintCLike.cpp.template"
                                                                if (useGlr)
                                                                {
                                                                  decreaseIndent();
                                                            #line 3634 "PrintCLike.cpp"
  append(L"\n");
  append(L"  }");
                                                            #line 2484 "PrintCLike.cpp.template"
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
                                                            #line 2500 "PrintCLike.cpp.template"
                                                                print(stringIntroducer());
                                                            #line 3658 "PrintCLike.cpp"
  append(L"\"at line \";\n");
  append(L"  message += to_");
                                                            #line 2502 "PrintCLike.cpp.template"
                                                              if (stringIntroducer()[0]) append(L"w");
                                                            #line 3663 "PrintCLike.cpp"
  append(L"string(line);\n");
  append(L"  message += ");
                                                            #line 2504 "PrintCLike.cpp.template"
                                                              print(stringIntroducer());
                                                            #line 3668 "PrintCLike.cpp"
  append(L"\", column \";\n");
  append(L"  message += to_");
                                                            #line 2506 "PrintCLike.cpp.template"
                                                              if (stringIntroducer()[0]) append(L"w");
                                                            #line 3673 "PrintCLike.cpp"
  append(L"string(column);\n");
  append(L"  message += ");
                                                            #line 2508 "PrintCLike.cpp.template"
                                                                print(stringIntroducer());
                                                            #line 3678 "PrintCLike.cpp"
  append(L"\":\\n...\";\n");
  append(L"  ");
                                                            #line 2510 "PrintCLike.cpp.template"
                                                                print(stringType());
                                                            #line 3683 "PrintCLike.cpp"
  append(L"w = input + e.getBegin();\n");
  append(L"  for (int i = 0; i < 64 && *w; ++i)\n");
  append(L"  {\n");
  append(L"    message += *w++;\n");
  append(L"  }\n");
  append(L"  message += ");
                                                            #line 2516 "PrintCLike.cpp.template"
                                                                print(stringIntroducer());
                                                            #line 3692 "PrintCLike.cpp"
  append(L"\"...\";\n");
  append(L"  return message;\n");
  append(L"}\n");
                                                            #line 2520 "PrintCLike.cpp.template"
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
                                                            #line 2545 "PrintCLike.cpp.template"
                                                                  if (stringIntroducer()[0])
                                                                  {
                                                            #line 3727 "PrintCLike.cpp"
  append(L"Utf8Encoder::encode(");
                                                            #line 2547 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 3731 "PrintCLike.cpp"
  append(L"method");
                                                            #line 2548 "PrintCLike.cpp.template"
                                                                  if (stringIntroducer()[0])
                                                                  {
                                                            #line 3736 "PrintCLike.cpp"
  append(L").c_str()");
                                                            #line 2550 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 3740 "PrintCLike.cpp"
  append(L", ");
                                                            #line 2551 "PrintCLike.cpp.template"
                                                                  if (stringIntroducer()[0])
                                                                  {
                                                            #line 3745 "PrintCLike.cpp"
  append(L"Utf8Encoder::encode(");
                                                            #line 2553 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 3749 "PrintCLike.cpp"
  append(L"occasion");
                                                            #line 2554 "PrintCLike.cpp.template"
                                                                  if (stringIntroducer()[0])
                                                                  {
                                                            #line 3754 "PrintCLike.cpp"
  append(L").c_str()");
                                                            #line 2556 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 3758 "PrintCLike.cpp"
  append(L", ");
                                                            #line 2557 "PrintCLike.cpp.template"
                                                                  if (stringIntroducer()[0])
                                                                  {
                                                            #line 3763 "PrintCLike.cpp"
  append(L"Utf8Encoder::encode(");
                                                            #line 2559 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 3767 "PrintCLike.cpp"
  append(L"name");
                                                            #line 2560 "PrintCLike.cpp.template"
                                                                  if (stringIntroducer()[0])
                                                                  {
                                                            #line 3772 "PrintCLike.cpp"
  append(L").c_str()");
                                                            #line 2562 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 3776 "PrintCLike.cpp"
  append(L");\n");
  append(L"  if (l1 != 0)\n");
  append(L"    fprintf(stderr, \" input=\\\"%s\\\"\", ");
                                                            #line 2565 "PrintCLike.cpp.template"
                                                                  if (stringIntroducer()[0])
                                                                  {
                                                            #line 3783 "PrintCLike.cpp"
  append(L"Utf8Encoder::encode(");
                                                            #line 2567 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 3787 "PrintCLike.cpp"
  append(L"xmlEscape(lookaheadString().c_str(), 0).c_str()");
                                                            #line 2569 "PrintCLike.cpp.template"
                                                                  if (stringIntroducer()[0])
                                                                  {
                                                            #line 3792 "PrintCLike.cpp"
  append(L").c_str()");
                                                            #line 2571 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 3796 "PrintCLike.cpp"
  append(L");\n");
  append(L"  fprintf(stderr, \"/>\\n\");");
                                                            #line 2573 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                                  if (isHaxe())
                                                                  {
                                                            #line 3805 "PrintCLike.cpp"
  append(L"\n");
  append(L"  trace(");
                                                            #line 2579 "PrintCLike.cpp.template"
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
                                                            #line 2590 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 3824 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 2592 "PrintCLike.cpp.template"
                                                                    print(writeTrace());
                                                                  }
                                                            #line 3830 "PrintCLike.cpp"
  append(L"\"  <\" + method + \" \" + occasion + \"nonterminal=\\\"\" + name + \"\\\"\" + ");
                                                            #line 2595 "PrintCLike.cpp.template"
                                                                  if (isGo())
                                                                  {
                                                            #line 3835 "PrintCLike.cpp"
  append(L"inputAttr");
                                                            #line 2597 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 3841 "PrintCLike.cpp"
  append(L"(");
                                                            #line 2600 "PrintCLike.cpp.template"
                                                                    if (isScala())
                                                                    {
                                                            #line 3846 "PrintCLike.cpp"
  append(L"if (l1 == 0) \"\" else");
                                                            #line 2602 "PrintCLike.cpp.template"
                                                                    }
                                                                    else if (isPython())
                                                                    {
                                                            #line 3852 "PrintCLike.cpp"
  append(L"\"\" if self.l1 == 0 else");
                                                            #line 2605 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                                      print(thiz());
                                                            #line 3859 "PrintCLike.cpp"
  append(L"l1 == 0 ? \"\" :");
                                                            #line 2609 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 3863 "PrintCLike.cpp"
  append(L" \" input=\\\"\" + ");
                                                            #line 2610 "PrintCLike.cpp.template"
                                                                    print(staticPrefix());
                                                            #line 3867 "PrintCLike.cpp"
  append(L"xmlEscape(");
                                                            #line 2611 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 3871 "PrintCLike.cpp"
  append(L"lookaheadString");
                                                            #line 2612 "PrintCLike.cpp.template"
                                                                    if (! isScala()) print(L"()");
                                                            #line 3875 "PrintCLike.cpp"
  append(L") + \"\\\"\")");
                                                            #line 2613 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 3879 "PrintCLike.cpp"
  append(L" + \"/>");
                                                            #line 2614 "PrintCLike.cpp.template"
                                                                  if (isHaxe()) print(L"\")"); else print(L"\\n\"");
                                                                  print(endWriteTrace());
                                                                  print(semicolon());
                                                                }
                                                                print(rightBrace());
                                                            #line 3887 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 2620 "PrintCLike.cpp.template"
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
                                                            #line 2631 "PrintCLike.cpp.template"
                                                                print(intVar());
                                                            #line 3904 "PrintCLike.cpp"
  append(L"i");
                                                            #line 2632 "PrintCLike.cpp.template"
                                                                print(assign());
                                                                print(thiz());
                                                            #line 3909 "PrintCLike.cpp"
  append(L"e0");
                                                            #line 2634 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 3913 "PrintCLike.cpp"
  append(L"\n");
  append(L"if ");
                                                            #line 2636 "PrintCLike.cpp.template"
                                                                print(ifLeftParen());
                                                                print(thiz());
                                                            #line 3919 "PrintCLike.cpp"
  append(L"e0 == ");
                                                            #line 2638 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 3923 "PrintCLike.cpp"
  append(L"b1");
                                                            #line 2639 "PrintCLike.cpp.template"
                                                                print(ifRightParen());
                                                                print(leftBrace());
                                                            #line 3928 "PrintCLike.cpp"
  append(L"\n");
  append(L"  i = ");
                                                            #line 2642 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 3933 "PrintCLike.cpp"
  append(L"b0");
                                                            #line 2643 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                print(rightBrace());
                                                                if (isScala() || isHaxe() || isPython())
                                                                {
                                                            #line 3940 "PrintCLike.cpp"
  append(L"\n");
  append(L"while ");
                                                            #line 2648 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 3947 "PrintCLike.cpp"
  append(L"\n");
  append(L"for ");
                                                            #line 2652 "PrintCLike.cpp.template"
                                                                }
                                                                print(ifLeftParen());
                                                                if (! (isScala() || isHaxe() || isPython()))
                                                                {
                                                            #line 3955 "PrintCLike.cpp"
  append(L"; ");
                                                            #line 2656 "PrintCLike.cpp.template"
                                                                }
                                                            #line 3959 "PrintCLike.cpp"
  append(L"i < ");
                                                            #line 2657 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 3963 "PrintCLike.cpp"
  append(L"b1");
                                                            #line 2658 "PrintCLike.cpp.template"
                                                                if (! (isScala() || isHaxe() || isPython()))
                                                                {
                                                            #line 3968 "PrintCLike.cpp"
  append(L"; i++");
                                                            #line 2660 "PrintCLike.cpp.template"
                                                                }
                                                                print(ifRightParen());
                                                                print(leftBrace());
                                                                increaseIndent();
                                                                if (isGo())
                                                                {
                                                            #line 3977 "PrintCLike.cpp"
  append(L"\n");
  append(L"c, _ := utf8.DecodeRuneInString(this.input[i:])");
                                                            #line 2667 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 3984 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 2671 "PrintCLike.cpp.template"
                                                                  print(intVar());
                                                            #line 3988 "PrintCLike.cpp"
  append(L"c");
                                                            #line 2672 "PrintCLike.cpp.template"
                                                                  print(assign());
                                                                  if (isCpp() || isCSharp() || isPython() || (isJava() && codepoints))
                                                                  {
                                                                    if (isPython())
                                                                    {
                                                            #line 3996 "PrintCLike.cpp"
  append(L"ord(");
                                                            #line 2677 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(thiz());
                                                            #line 4001 "PrintCLike.cpp"
  append(L"input[i]");
                                                            #line 2679 "PrintCLike.cpp.template"
                                                                    if (isPython())
                                                                    {
                                                            #line 4006 "PrintCLike.cpp"
  append(L")");
                                                            #line 2681 "PrintCLike.cpp.template"
                                                                    }
                                                                  }
                                                                  else if (isHaxe())
                                                                  {
                                                            #line 4013 "PrintCLike.cpp"
  append(L"input.get(i)");
                                                            #line 2685 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                                    print(thiz());
                                                            #line 4020 "PrintCLike.cpp"
  append(L"input.char");
                                                            #line 2689 "PrintCLike.cpp.template"
                                                                    if (isTypescript() || isJavascript())
                                                                    {
                                                            #line 4025 "PrintCLike.cpp"
  append(L"Code");
                                                            #line 2691 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 4029 "PrintCLike.cpp"
  append(L"At(i)");
                                                            #line 2692 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(semicolon());
                                                                }
                                                            #line 4035 "PrintCLike.cpp"
  append(L"\n");
  append(L"if ");
                                                            #line 2696 "PrintCLike.cpp.template"
                                                                print(ifLeftParen());
                                                            #line 4040 "PrintCLike.cpp"
  append(L"c == 0xA ");
                                                            #line 2698 "PrintCLike.cpp.template"
                                                                if (isPython())
                                                                {
                                                            #line 4045 "PrintCLike.cpp"
  append(L"or");
                                                            #line 2700 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 4051 "PrintCLike.cpp"
  append(L"||");
                                                            #line 2703 "PrintCLike.cpp.template"
                                                                }
                                                            #line 4055 "PrintCLike.cpp"
  append(L" c == 0xD ");
                                                            #line 2705 "PrintCLike.cpp.template"
                                                                if (isPython())
                                                                {
                                                            #line 4060 "PrintCLike.cpp"
  append(L"or");
                                                            #line 2707 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 4066 "PrintCLike.cpp"
  append(L"||");
                                                            #line 2710 "PrintCLike.cpp.template"
                                                                }
                                                            #line 4070 "PrintCLike.cpp"
  append(L" c == 0x2028 ");
                                                            #line 2712 "PrintCLike.cpp.template"
                                                                if (isPython())
                                                                {
                                                            #line 4075 "PrintCLike.cpp"
  append(L"or");
                                                            #line 2714 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 4081 "PrintCLike.cpp"
  append(L"||");
                                                            #line 2717 "PrintCLike.cpp.template"
                                                                }
                                                            #line 4085 "PrintCLike.cpp"
  append(L" c == 0x2029");
                                                            #line 2718 "PrintCLike.cpp.template"
                                                                print(ifRightParen());
                                                                print(leftBrace());
                                                            #line 4090 "PrintCLike.cpp"
  append(L"\n");
  append(L"  return ");
                                                            #line 2721 "PrintCLike.cpp.template"
                                                                if (isPython())
                                                                {
                                                            #line 4096 "PrintCLike.cpp"
  append(L"T");
                                                            #line 2723 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 4102 "PrintCLike.cpp"
  append(L"t");
                                                            #line 2726 "PrintCLike.cpp.template"
                                                                }
                                                            #line 4106 "PrintCLike.cpp"
  append(L"rue");
                                                            #line 2727 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                print(rightBrace());
                                                                if (isScala() || isPython())
                                                                {
                                                            #line 4113 "PrintCLike.cpp"
  append(L"\n");
  append(L"i += 1");
                                                            #line 2733 "PrintCLike.cpp.template"
                                                                }
                                                                else if (isHaxe())
                                                                {
                                                            #line 4120 "PrintCLike.cpp"
  append(L"\n");
  append(L"++i;");
                                                            #line 2737 "PrintCLike.cpp.template"
                                                                }

                                                                decreaseIndent();
                                                                print(rightBrace());
                                                            #line 4128 "PrintCLike.cpp"
  append(L"\n");
  append(L"return ");
                                                            #line 2742 "PrintCLike.cpp.template"
                                                                if (isPython())
                                                                {
                                                            #line 4134 "PrintCLike.cpp"
  append(L"F");
                                                            #line 2744 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 4140 "PrintCLike.cpp"
  append(L"f");
                                                            #line 2747 "PrintCLike.cpp.template"
                                                                }
                                                            #line 4144 "PrintCLike.cpp"
  append(L"alse");
                                                            #line 2748 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                decreaseIndent();
                                                                print(rightBrace());
                                                            #line 4150 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 2752 "PrintCLike.cpp.template"
                                                                if (! isGo())
                                                                  decreaseIndent();
                                                              }

                                                              if (isScala())
                                                              {
                                                            #line 4159 "PrintCLike.cpp"
  append(L"\n");
  append(L"  def getErrorMessage(e: ");
                                                            #line 2759 "PrintCLike.cpp.template"
                                                                print(className.c_str());
                                                            #line 4164 "PrintCLike.cpp"
  append(L".ParseException) = {\n");
  append(L"    var message = e.getMessage");
                                                            #line 2761 "PrintCLike.cpp.template"
                                                                if (useGlr)
                                                                {
                                                            #line 4170 "PrintCLike.cpp"
  append(L"\n");
  append(L"    if (e.isAmbiguousInput)\n");
  append(L"      message += \"\\n\"\n");
  append(L"    else {");
                                                            #line 2766 "PrintCLike.cpp.template"
                                                                  increaseIndent();
                                                                }
                                                            #line 4178 "PrintCLike.cpp"
  append(L"\n");
  append(L"    val tokenSet = ");
                                                            #line 2769 "PrintCLike.cpp.template"
                                                                print(className.c_str());
                                                            #line 4183 "PrintCLike.cpp"
  append(L".getExpectedTokenSet(e)\n");
  append(L"    val found = ");
                                                            #line 2771 "PrintCLike.cpp.template"
                                                                print(className.c_str());
                                                            #line 4188 "PrintCLike.cpp"
  append(L".getOffendingToken(e)\n");
  append(L"    val size = e.end - e.begin\n");
  append(L"    message += (if (found == null) \"\" else \", found \" + found) + \"\\nwhile expecting \" +\n");
  append(L"      (if (tokenSet.length == 1) tokenSet(0) else \"[\" + (tokenSet mkString \", \") + \"]\") + \"\\n\" +\n");
  append(L"      (if (size == 0 || found != null) \"\" else \"after successfully scanning \" + size + \" characters beginning \")");
                                                            #line 2777 "PrintCLike.cpp.template"
                                                                if (useGlr)
                                                                {
                                                            #line 4197 "PrintCLike.cpp"
  append(L"\n");
  append(L"    }");
                                                            #line 2780 "PrintCLike.cpp.template"
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
                                                            #line 2790 "PrintCLike.cpp.template"
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
                                                            #line 2827 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 4256 "PrintCLike.cpp"
  append(L"top += ");
                                                            #line 2828 "PrintCLike.cpp.template"
                                                                  if (tree)
                                                                  {
                                                            #line 4261 "PrintCLike.cpp"
  append(L"3");
                                                            #line 2830 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 4267 "PrintCLike.cpp"
  append(L"2");
                                                            #line 2833 "PrintCLike.cpp.template"
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
                                                            #line 2841 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isCSharp())
                                                                  {
                                                            #line 4284 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if (top >= iStack.Length)\n");
  append(L"  {\n");
  append(L"    Array.Resize(ref iStack, iStack.Length << 1);\n");
  append(L"  }");
                                                            #line 2848 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isCpp())
                                                                  {
                                                            #line 4294 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if (top >= (int) iStack.size())\n");
  append(L"    iStack.resize(iStack.size() == 0 ? ");
                                                            #line 2853 "PrintCLike.cpp.template"
                                                                    print(tree ? L"192" : L"128");
                                                            #line 4300 "PrintCLike.cpp"
  append(L" : iStack.size() << 1);");
                                                            #line 2855 "PrintCLike.cpp.template"
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
                                                            #line 2863 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isGo())
                                                                  {
                                                            #line 4317 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if this.top >= len(this.iStack) {\n");
  append(L"    this.iStack = append(this.iStack, this.iStack...)\n");
  append(L"  }");
                                                            #line 2869 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isPython())
                                                                  {
                                                            #line 4326 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if self.top >= len(self.iStack):\n");
  append(L"    self.iStack.extend([0 for _ in range(len(self.iStack))])");
                                                            #line 2874 "PrintCLike.cpp.template"
                                                                  }
                                                                  if (tree)
                                                                  {
                                                            #line 4334 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 2878 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 4339 "PrintCLike.cpp"
  append(L"iStack");
                                                            #line 2879 "PrintCLike.cpp.template"
                                                                    print(leftbracket());
                                                                    print(thiz());
                                                            #line 4344 "PrintCLike.cpp"
  append(L"top - 2");
                                                            #line 2881 "PrintCLike.cpp.template"
                                                                    print(rightbracket());
                                                            #line 4348 "PrintCLike.cpp"
  append(L" = begin");
                                                            #line 2882 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                  }
                                                            #line 4353 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 2885 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 4358 "PrintCLike.cpp"
  append(L"iStack");
                                                            #line 2886 "PrintCLike.cpp.template"
                                                                  print(leftbracket());
                                                                  print(thiz());
                                                            #line 4363 "PrintCLike.cpp"
  append(L"top - 1");
                                                            #line 2888 "PrintCLike.cpp.template"
                                                                  print(rightbracket());
                                                            #line 4367 "PrintCLike.cpp"
  append(L" = state");
                                                            #line 2889 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                            #line 4371 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 2891 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 4376 "PrintCLike.cpp"
  append(L"iStack");
                                                            #line 2892 "PrintCLike.cpp.template"
                                                                  print(leftbracket());
                                                                  print(thiz());
                                                            #line 4381 "PrintCLike.cpp"
  append(L"top");
                                                            #line 2894 "PrintCLike.cpp.template"
                                                                  print(rightbracket());
                                                            #line 4385 "PrintCLike.cpp"
  append(L" = lookback");
                                                            #line 2895 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                  print(rightBrace());
                                                            #line 4390 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 2898 "PrintCLike.cpp.template"
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
                                                            #line 2915 "PrintCLike.cpp.template"
                                                                  print(intVar());
                                                            #line 4413 "PrintCLike.cpp"
  append(L"state");
                                                            #line 2916 "PrintCLike.cpp.template"
                                                                  print(assign());
                                                            #line 4417 "PrintCLike.cpp"
  append(L"initialState");
                                                            #line 2917 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                  if (tree || useGlr)
                                                                  {
                                                            #line 4423 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 2921 "PrintCLike.cpp.template"
                                                                    print(intVar());
                                                            #line 4427 "PrintCLike.cpp"
  append(L"bw");
                                                            #line 2922 "PrintCLike.cpp.template"
                                                                    print(assign());
                                                                    print(thiz());
                                                            #line 4432 "PrintCLike.cpp"
  append(L"e0");
                                                            #line 2924 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 4436 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 2926 "PrintCLike.cpp.template"
                                                                    print(intVar());
                                                            #line 4440 "PrintCLike.cpp"
  append(L"bs");
                                                            #line 2927 "PrintCLike.cpp.template"
                                                                    print(assign());
                                                                    print(thiz());
                                                            #line 4445 "PrintCLike.cpp"
  append(L"e0");
                                                            #line 2929 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                  }
                                                                  if (tree)
                                                                  {
                                                            #line 4452 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 2934 "PrintCLike.cpp.template"
                                                                    print(intVar());
                                                            #line 4456 "PrintCLike.cpp"
  append(L"es");
                                                            #line 2935 "PrintCLike.cpp.template"
                                                                    print(assign());
                                                                    print(thiz());
                                                            #line 4461 "PrintCLike.cpp"
  append(L"e0");
                                                            #line 2937 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 4465 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 2939 "PrintCLike.cpp.template"
                                                                    print(intVar());
                                                            #line 4469 "PrintCLike.cpp"
  append(L"t");
                                                            #line 2940 "PrintCLike.cpp.template"
                                                                    print(assign());
                                                                    print(thiz());
                                                            #line 4474 "PrintCLike.cpp"
  append(L"top");
                                                            #line 2942 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                  }
                                                            #line 4479 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 2945 "PrintCLike.cpp.template"
                                                                  print(intVar());
                                                            #line 4483 "PrintCLike.cpp"
  append(L"action");
                                                            #line 2946 "PrintCLike.cpp.template"
                                                                  print(assign());
                                                                  print(thiz());
                                                            #line 4488 "PrintCLike.cpp"
  append(L"predict(state)");
                                                            #line 2948 "PrintCLike.cpp.template"
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
                                                            #line 2972 "PrintCLike.cpp.template"
                                                                }
                                                                if (useGlr)
                                                                {
                                                            #line 4519 "PrintCLike.cpp"
  append(L"\n");
  append(L"  var thread: ");
                                                            #line 2976 "PrintCLike.cpp.template"
                                                                  print(className.c_str());
                                                            #line 4524 "PrintCLike.cpp"
  append(L".ParsingThread = null");
                                                            #line 2977 "PrintCLike.cpp.template"
                                                                }
                                                            #line 4528 "PrintCLike.cpp"
  append(L"\n");
  append(L"  var input: String = null");
                                                            #line 2979 "PrintCLike.cpp.template"
                                                                if (! noLexer)
                                                                {
                                                            #line 4534 "PrintCLike.cpp"
  append(L"\n");
  append(L"  var size = 0");
                                                            #line 2982 "PrintCLike.cpp.template"
                                                                }
                                                                if (tree && useGlr)
                                                                {
                                                            #line 4541 "PrintCLike.cpp"
  append(L"\n");
  append(L"  var eventHandler: ");
                                                            #line 2986 "PrintCLike.cpp.template"
                                                                  print(className.c_str());
                                                            #line 4546 "PrintCLike.cpp"
  append(L".BottomUpEventHandler = null");
                                                            #line 2987 "PrintCLike.cpp.template"
                                                                }
                                                                if (noLexer)
                                                                {
                                                            #line 4552 "PrintCLike.cpp"
  append(L"\n");
  append(L"  var lexer: Lexer = null\n");
  append(L"  var token = new Token");
                                                            #line 2992 "PrintCLike.cpp.template"
                                                                }
                                                                if (useGlr)
                                                                {
                                                            #line 4560 "PrintCLike.cpp"
  append(L"\n");
  append(L"  var maxId = 0");
                                                            #line 2996 "PrintCLike.cpp.template"
                                                                }
                                                                if (trace)
                                                                {
                                                            #line 4567 "PrintCLike.cpp"
  append(L"\n");
  append(L"  var err: Writer = new OutputStreamWriter(System.err, \"UTF-8\")");
                                                            #line 3001 "PrintCLike.cpp.template"
                                                                }
                                                            #line 4572 "PrintCLike.cpp"
  append(L"\n");
  append(L"}\n");
  append(L"\n");
  append(L"object ");
                                                            #line 3005 "PrintCLike.cpp.template"
                                                                print(className.c_str());
                                                            #line 4579 "PrintCLike.cpp"
  append(L" {\n");
  append(L"\n");
  append(L"  def getOffendingToken(e: ParseException) = {\n");
  append(L"    if (e.offending < 0) null else TOKEN(e.offending)\n");
  append(L"  }\n");
                                                            #line 3012 "PrintCLike.cpp.template"
                                                              }
                                                            }

                                                            void PrintCLike::printThreadBody1()
                                                            {
                                                              Trace("PrintCLike::printThreadBody1");

                                                              if (isLrParser)
                                                              {
                                                            #line 4595 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3022 "PrintCLike.cpp.template"
                                                                print(intVar());
                                                            #line 4599 "PrintCLike.cpp"
  append(L"nonterminalId");
                                                            #line 3023 "PrintCLike.cpp.template"
                                                                print(assign());
                                                            #line 4603 "PrintCLike.cpp"
  append(L"-1");
                                                            #line 3024 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                if (isHaxe() || isScala() || isPython())
                                                                {
                                                            #line 4609 "PrintCLike.cpp"
  append(L"\n");
  append(L"while ");
                                                            #line 3028 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                                  if (isPython())
                                                                  {
                                                            #line 4616 "PrintCLike.cpp"
  append(L"T");
                                                            #line 3031 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 4622 "PrintCLike.cpp"
  append(L"t");
                                                            #line 3034 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 4626 "PrintCLike.cpp"
  append(L"rue");
                                                            #line 3035 "PrintCLike.cpp.template"
                                                                  print(ifRightParen());
                                                                }
                                                                else if (isGo())
                                                                {
                                                            #line 4633 "PrintCLike.cpp"
  append(L"\n");
  append(L"for");
                                                            #line 3040 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 4640 "PrintCLike.cpp"
  append(L"\n");
  append(L"for (;;)");
                                                            #line 3044 "PrintCLike.cpp.template"
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
                                                            #line 3052 "PrintCLike.cpp.template"
                                                                    if (useGlr)
                                                                    {
                                                            #line 4657 "PrintCLike.cpp"
  append(L"thread=\\\"%d\\\" offset=\\\"%d\\\" ");
                                                            #line 3054 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 4661 "PrintCLike.cpp"
  append(L"state=\\\"%d\\\" input=\\\"%s%s%s\\\" action=\\\"\",");
                                                            #line 3056 "PrintCLike.cpp.template"
                                                                    if (useGlr)
                                                                    {
                                                            #line 4666 "PrintCLike.cpp"
  append(L"\n");
  append(L"  id,\n");
  append(L"  e0,");
                                                            #line 3060 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 4672 "PrintCLike.cpp"
  append(L"\n");
  append(L"  state,\n");
  append(L"  nonterminalId < 0 ? \"\" : ");
                                                            #line 3063 "PrintCLike.cpp.template"
                                                                    if (stringIntroducer()[0])
                                                                    {
                                                            #line 4679 "PrintCLike.cpp"
  append(L"Utf8Encoder::encode(");
                                                            #line 3065 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 4683 "PrintCLike.cpp"
  append(L"xmlEscape(");
                                                            #line 3066 "PrintCLike.cpp.template"
                                                                    print(isGo() ? L"nonterminal" : L"NONTERMINAL");
                                                            #line 4687 "PrintCLike.cpp"
  append(L"[nonterminalId], 0).c_str()");
                                                            #line 3068 "PrintCLike.cpp.template"
                                                                    if (stringIntroducer()[0])
                                                                    {
                                                            #line 4692 "PrintCLike.cpp"
  append(L").c_str()");
                                                            #line 3070 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 4696 "PrintCLike.cpp"
  append(L",\n");
  append(L"  nonterminalId < 0 || l1 <= 0 ? \"\" : \" \",\n");
  append(L"  l1 <= 0 ? \"\" : ");
                                                            #line 3073 "PrintCLike.cpp.template"
                                                                    if (stringIntroducer()[0])
                                                                    {
                                                            #line 4703 "PrintCLike.cpp"
  append(L"Utf8Encoder::encode(");
                                                            #line 3075 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 4707 "PrintCLike.cpp"
  append(L"xmlEscape(lookaheadString().c_str(), 0).c_str()");
                                                            #line 3076 "PrintCLike.cpp.template"
                                                                    if (stringIntroducer()[0])
                                                                    {
                                                            #line 4712 "PrintCLike.cpp"
  append(L").c_str()");
                                                            #line 3078 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 4716 "PrintCLike.cpp"
  append(L");\n");
                                                            #line 3080 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                                    if (isHaxe())
                                                                    {
                                                            #line 4724 "PrintCLike.cpp"
  append(L"\n");
  append(L"var traceLine = ");
                                                            #line 3086 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 4731 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3090 "PrintCLike.cpp.template"
                                                                      print(writeTrace());
                                                                    }
                                                            #line 4736 "PrintCLike.cpp"
  append(L"\"  <parse ");
                                                            #line 3092 "PrintCLike.cpp.template"
                                                                    if (useGlr)
                                                                    {
                                                            #line 4741 "PrintCLike.cpp"
  append(L"thread=\\\"\" + ");
                                                            #line 3094 "PrintCLike.cpp.template"
                                                                      if (isGo())
                                                                      {
                                                            #line 4746 "PrintCLike.cpp"
  append(L"strconv.Itoa(");
                                                            #line 3096 "PrintCLike.cpp.template"
                                                                      }
                                                                      else if (isPython())
                                                                      {
                                                            #line 4752 "PrintCLike.cpp"
  append(L"str(");
                                                            #line 3099 "PrintCLike.cpp.template"
                                                                      }
                                                                      print(thiz());
                                                            #line 4757 "PrintCLike.cpp"
  append(L"id");
                                                            #line 3101 "PrintCLike.cpp.template"
                                                                      if (isGo() || isPython())
                                                                      {
                                                            #line 4762 "PrintCLike.cpp"
  append(L")");
                                                            #line 3103 "PrintCLike.cpp.template"
                                                                      }
                                                            #line 4766 "PrintCLike.cpp"
  append(L" + \"\\\" offset=\\\"\" + ");
                                                            #line 3104 "PrintCLike.cpp.template"
                                                                      if (isGo())
                                                                      {
                                                            #line 4771 "PrintCLike.cpp"
  append(L"strconv.Itoa(");
                                                            #line 3106 "PrintCLike.cpp.template"
                                                                      }
                                                                      else if (isPython())
                                                                      {
                                                            #line 4777 "PrintCLike.cpp"
  append(L"str(");
                                                            #line 3109 "PrintCLike.cpp.template"
                                                                      }
                                                                      print(thiz());
                                                            #line 4782 "PrintCLike.cpp"
  append(L"e0");
                                                            #line 3111 "PrintCLike.cpp.template"
                                                                      if (isGo() || isPython())
                                                                      {
                                                            #line 4787 "PrintCLike.cpp"
  append(L")");
                                                            #line 3113 "PrintCLike.cpp.template"
                                                                      }
                                                            #line 4791 "PrintCLike.cpp"
  append(L" + \"\\\" ");
                                                            #line 3114 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 4795 "PrintCLike.cpp"
  append(L"state=\\\"\" + ");
                                                            #line 3115 "PrintCLike.cpp.template"
                                                                    if (isGo())
                                                                    {
                                                            #line 4800 "PrintCLike.cpp"
  append(L"strconv.Itoa(");
                                                            #line 3117 "PrintCLike.cpp.template"
                                                                    }
                                                                    else if (isPython())
                                                                    {
                                                            #line 4806 "PrintCLike.cpp"
  append(L"str(");
                                                            #line 3120 "PrintCLike.cpp.template"
                                                                    }
                                                                    if (useGlr) print(thiz());
                                                            #line 4811 "PrintCLike.cpp"
  append(L"state");
                                                            #line 3122 "PrintCLike.cpp.template"
                                                                    if (isGo() || isPython())
                                                                    {
                                                            #line 4816 "PrintCLike.cpp"
  append(L")");
                                                            #line 3124 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 4820 "PrintCLike.cpp"
  append(L" + \"\\\" input=\\\"\"");
                                                            #line 3125 "PrintCLike.cpp.template"
                                                                    print(endWriteTrace());
                                                                    print(semicolon());
                                                            #line 4825 "PrintCLike.cpp"
  append(L"\n");
  append(L"if ");
                                                            #line 3129 "PrintCLike.cpp.template"
                                                                    print(ifLeftParen());
                                                            #line 4830 "PrintCLike.cpp"
  append(L"nonterminalId >= 0");
                                                            #line 3130 "PrintCLike.cpp.template"
                                                                    print(ifRightParen());
                                                                    print(leftBrace());
                                                            #line 4835 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3133 "PrintCLike.cpp.template"
                                                                    print(writeTrace());
                                                                    print(staticPrefix());
                                                            #line 4841 "PrintCLike.cpp"
  append(L"xmlEscape(");
                                                            #line 3136 "PrintCLike.cpp.template"
                                                                    print(staticPrefix());
                                                                    print(isGo() ? L"nonterminal" : L"NONTERMINAL");
                                                                    print(leftbracket());
                                                            #line 4847 "PrintCLike.cpp"
  append(L"nonterminalId");
                                                            #line 3139 "PrintCLike.cpp.template"
                                                                    print(rightbracket());
                                                            #line 4851 "PrintCLike.cpp"
  append(L")");
                                                            #line 3140 "PrintCLike.cpp.template"
                                                                    print(endWriteTrace());
                                                                    print(semicolon());
                                                            #line 4856 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if ");
                                                            #line 3143 "PrintCLike.cpp.template"
                                                                    print(ifLeftParen());
                                                                    print(thiz());
                                                            #line 4862 "PrintCLike.cpp"
  append(L"l1 != 0");
                                                            #line 3145 "PrintCLike.cpp.template"
                                                                    print(ifRightParen());
                                                                    printIndented(1, leftBrace());
                                                            #line 4867 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 3148 "PrintCLike.cpp.template"
                                                                    print(writeTrace());
                                                            #line 4872 "PrintCLike.cpp"
  append(L"\" \"");
                                                            #line 3149 "PrintCLike.cpp.template"
                                                                    print(endWriteTrace());
                                                                    print(semicolon());
                                                                    increaseIndent();
                                                                    print(rightBrace());
                                                                    decreaseIndent();
                                                                    print(rightBrace());
                                                            #line 4881 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3156 "PrintCLike.cpp.template"
                                                                    print(writeTrace());
                                                                    print(staticPrefix());
                                                            #line 4886 "PrintCLike.cpp"
  append(L"xmlEscape(");
                                                            #line 3158 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 4890 "PrintCLike.cpp"
  append(L"lookaheadString");
                                                            #line 3159 "PrintCLike.cpp.template"
                                                                    if (! isScala()) print(L"()");
                                                            #line 4894 "PrintCLike.cpp"
  append(L") + \"\\\" action=\\\"\"");
                                                            #line 3160 "PrintCLike.cpp.template"
                                                                    print(endWriteTrace());
                                                                    print(semicolon());
                                                                  }
                                                                }
                                                            #line 4901 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3165 "PrintCLike.cpp.template"
                                                                print(intVal());
                                                            #line 4905 "PrintCLike.cpp"
  append(L"argument");
                                                            #line 3166 "PrintCLike.cpp.template"
                                                                print(assign());
                                                                if (useGlr) print(thiz());
                                                            #line 4910 "PrintCLike.cpp"
  append(L"action >> ");
                                                            #line 3168 "PrintCLike.cpp.template"
                                                                print(format.toString<wchar_t>(grammar->states->dominoBits + LrStates::actionBits));
                                                                print(semicolon());
                                                            #line 4915 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3171 "PrintCLike.cpp.template"
                                                                print(intVal());
                                                            #line 4919 "PrintCLike.cpp"
  append(L"lookback");
                                                            #line 3172 "PrintCLike.cpp.template"
                                                                print(assign());
                                                            #line 4923 "PrintCLike.cpp"
  append(L"(");
                                                            #line 3173 "PrintCLike.cpp.template"
                                                                if (useGlr) print(thiz());
                                                            #line 4927 "PrintCLike.cpp"
  append(L"action >> ");
                                                            #line 3174 "PrintCLike.cpp.template"
                                                                print(format.toString<wchar_t>((int) LrStates::actionBits));
                                                            #line 4931 "PrintCLike.cpp"
  append(L") & ");
                                                            #line 3175 "PrintCLike.cpp.template"
                                                                print(format.toString<wchar_t>((1 << grammar->states->dominoBits) -1));
                                                                print(semicolon());
                                                            #line 4936 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3178 "PrintCLike.cpp.template"
                                                                print(intVar());
                                                            #line 4940 "PrintCLike.cpp"
  append(L"shift");
                                                            #line 3179 "PrintCLike.cpp.template"
                                                                print(assign());
                                                            #line 4944 "PrintCLike.cpp"
  append(L"-1");
                                                            #line 3180 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 4948 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3182 "PrintCLike.cpp.template"
                                                                print(intVar());
                                                            #line 4952 "PrintCLike.cpp"
  append(L"reduce");
                                                            #line 3183 "PrintCLike.cpp.template"
                                                                print(assign());
                                                            #line 4956 "PrintCLike.cpp"
  append(L"-1");
                                                            #line 3184 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 4960 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3186 "PrintCLike.cpp.template"
                                                                print(intVar());
                                                            #line 4964 "PrintCLike.cpp"
  append(L"symbols");
                                                            #line 3187 "PrintCLike.cpp.template"
                                                                print(assign());
                                                            #line 4968 "PrintCLike.cpp"
  append(L"-1");
                                                            #line 3188 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                if (isPython())
                                                                {
                                                            #line 4974 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3193 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 4978 "PrintCLike.cpp"
  append(L"action &= ");
                                                            #line 3194 "PrintCLike.cpp.template"
                                                                  print(format.toString<wchar_t>((int) LrStates::actionMask));
                                                                }
                                                                else
                                                                {
                                                            #line 4985 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3199 "PrintCLike.cpp.template"
                                                                  if (! isScala())
                                                                  {
                                                            #line 4990 "PrintCLike.cpp"
  append(L"switch ");
                                                            #line 3201 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(ifLeftParen());
                                                                  if (useGlr) print(thiz());
                                                            #line 4996 "PrintCLike.cpp"
  append(L"action & ");
                                                            #line 3204 "PrintCLike.cpp.template"
                                                                  print(format.toString<wchar_t>((int) LrStates::actionMask));
                                                                  print(ifRightParen());
                                                                  if (isScala())
                                                                  {
                                                            #line 5003 "PrintCLike.cpp"
  append(L" match");
                                                            #line 3208 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(leftBrace());
                                                                }
                                                                if (isPython())
                                                                {
                                                            #line 5011 "PrintCLike.cpp"
  append(L"\n");
  append(L"if ");
                                                            #line 3214 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 5016 "PrintCLike.cpp"
  append(L"action == ");
                                                            #line 3215 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 5022 "PrintCLike.cpp"
  append(L"\n");
  append(L"case ");
                                                            #line 3219 "PrintCLike.cpp.template"
                                                                }
                                                                print(format.toString<wchar_t>((int) LrStates::SHIFT));
                                                                print(caseIntroducer());
                                                            #line 5029 "PrintCLike.cpp"
  append(L" ");
                                                            #line 3222 "PrintCLike.cpp.template"
                                                                print(inlineCommentIntroducer());
                                                            #line 5033 "PrintCLike.cpp"
  append(L"SHIFT\n");
  append(L"  shift = argument");
                                                            #line 3224 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                if (! isHaxe() && ! isScala() && ! isGo() && ! isPython())
                                                                {
                                                            #line 5040 "PrintCLike.cpp"
  append(L"\n");
  append(L"  break");
                                                            #line 3228 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                            #line 5046 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3231 "PrintCLike.cpp.template"
                                                                if (isPython())
                                                                {
                                                            #line 5051 "PrintCLike.cpp"
  append(L"\n");
  append(L"elif ");
                                                            #line 3234 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 5056 "PrintCLike.cpp"
  append(L"action == ");
                                                            #line 3235 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 5062 "PrintCLike.cpp"
  append(L"\n");
  append(L"case ");
                                                            #line 3239 "PrintCLike.cpp.template"
                                                                }
                                                                print(format.toString<wchar_t>((int) LrStates::REDUCE));
                                                                print(caseIntroducer());
                                                            #line 5069 "PrintCLike.cpp"
  append(L" ");
                                                            #line 3242 "PrintCLike.cpp.template"
                                                                print(inlineCommentIntroducer());
                                                            #line 5073 "PrintCLike.cpp"
  append(L"REDUCE\n");
  append(L"  reduce = argument");
                                                            #line 3244 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 5078 "PrintCLike.cpp"
  append(L"\n");
  append(L"  symbols = lookback");
                                                            #line 3246 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                if (! isHaxe() && ! isScala() && ! isGo() && ! isPython())
                                                                {
                                                            #line 5085 "PrintCLike.cpp"
  append(L"\n");
  append(L"  break");
                                                            #line 3250 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                                if (grammar->states->hasLookback)
                                                                {
                                                            #line 5093 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3255 "PrintCLike.cpp.template"
                                                                  if (isPython())
                                                                  {
                                                            #line 5098 "PrintCLike.cpp"
  append(L"\n");
  append(L"elif ");
                                                            #line 3258 "PrintCLike.cpp.template"
                                                                    if (useGlr) print(thiz());
                                                            #line 5103 "PrintCLike.cpp"
  append(L"action == ");
                                                            #line 3259 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 5109 "PrintCLike.cpp"
  append(L"\n");
  append(L"case ");
                                                            #line 3263 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(format.toString<wchar_t>((int) LrStates::REDUCE_LOOKBACK));
                                                                  print(caseIntroducer());
                                                            #line 5116 "PrintCLike.cpp"
  append(L" ");
                                                            #line 3266 "PrintCLike.cpp.template"
                                                                  print(inlineCommentIntroducer());
                                                            #line 5120 "PrintCLike.cpp"
  append(L"REDUCE+LOOKBACK\n");
  append(L"  reduce = argument");
                                                            #line 3268 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                            #line 5125 "PrintCLike.cpp"
  append(L"\n");
  append(L"  symbols = ");
                                                            #line 3270 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                                  if (useGlr)
                                                                  {
                                                            #line 5132 "PrintCLike.cpp"
  append(L"stack");
                                                            #line 3273 "PrintCLike.cpp.template"
                                                                    if (isTypescript()) print(L"!");
                                                                    print(arrow());
                                                                  }
                                                                  if (isGo() && useGlr)
                                                                  {
                                                            #line 5140 "PrintCLike.cpp"
  append(L"Count");
                                                            #line 3278 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 5146 "PrintCLike.cpp"
  append(L"count");
                                                            #line 3281 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 5150 "PrintCLike.cpp"
  append(L"(lookback)");
                                                            #line 3282 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                  if (! isHaxe() && ! isScala() && ! isGo() && ! isPython())
                                                                  {
                                                            #line 5156 "PrintCLike.cpp"
  append(L"\n");
  append(L"  break");
                                                            #line 3286 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                  }
                                                                }
                                                            #line 5163 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3290 "PrintCLike.cpp.template"
                                                                if (isPython())
                                                                {
                                                            #line 5168 "PrintCLike.cpp"
  append(L"\n");
  append(L"elif ");
                                                            #line 3293 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 5173 "PrintCLike.cpp"
  append(L"action == ");
                                                            #line 3294 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 5179 "PrintCLike.cpp"
  append(L"\n");
  append(L"case ");
                                                            #line 3298 "PrintCLike.cpp.template"
                                                                }
                                                                print(format.toString<wchar_t>((int) LrStates::SHIFT_REDUCE));
                                                                print(caseIntroducer());
                                                            #line 5186 "PrintCLike.cpp"
  append(L" ");
                                                            #line 3301 "PrintCLike.cpp.template"
                                                                print(inlineCommentIntroducer());
                                                            #line 5190 "PrintCLike.cpp"
  append(L"SHIFT+REDUCE\n");
  append(L"  shift = ");
                                                            #line 3303 "PrintCLike.cpp.template"
                                                                if (useGlr) print(thiz());
                                                            #line 5195 "PrintCLike.cpp"
  append(L"state");
                                                            #line 3304 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 5199 "PrintCLike.cpp"
  append(L"\n");
  append(L"  reduce = argument");
                                                            #line 3306 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 5204 "PrintCLike.cpp"
  append(L"\n");
  append(L"  symbols = lookback + 1");
                                                            #line 3308 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                if (! isHaxe() && ! isScala() && ! isGo() && ! isPython())
                                                                {
                                                            #line 5211 "PrintCLike.cpp"
  append(L"\n");
  append(L"  break");
                                                            #line 3312 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                                if (grammar->states->hasLookback)
                                                                {
                                                            #line 5219 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3317 "PrintCLike.cpp.template"
                                                                  if (isPython())
                                                                  {
                                                            #line 5224 "PrintCLike.cpp"
  append(L"\n");
  append(L"elif ");
                                                            #line 3320 "PrintCLike.cpp.template"
                                                                    if (useGlr) print(thiz());
                                                            #line 5229 "PrintCLike.cpp"
  append(L"action == ");
                                                            #line 3321 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 5235 "PrintCLike.cpp"
  append(L"\n");
  append(L"case ");
                                                            #line 3325 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(format.toString<wchar_t>((int) LrStates::SHIFT_REDUCE_LOOKBACK));
                                                                  print(caseIntroducer());
                                                            #line 5242 "PrintCLike.cpp"
  append(L" ");
                                                            #line 3328 "PrintCLike.cpp.template"
                                                                  print(inlineCommentIntroducer());
                                                            #line 5246 "PrintCLike.cpp"
  append(L"SHIFT+REDUCE+LOOKBACK\n");
  append(L"  shift = ");
                                                            #line 3330 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 5251 "PrintCLike.cpp"
  append(L"state");
                                                            #line 3331 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                            #line 5255 "PrintCLike.cpp"
  append(L"\n");
  append(L"  reduce = argument");
                                                            #line 3333 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                            #line 5260 "PrintCLike.cpp"
  append(L"\n");
  append(L"  symbols = ");
                                                            #line 3335 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                                  if (useGlr)
                                                                  {
                                                            #line 5267 "PrintCLike.cpp"
  append(L"stack");
                                                            #line 3338 "PrintCLike.cpp.template"
                                                                    if (isTypescript()) print(L"!");
                                                                    print(arrow());
                                                                  }
                                                                  if (isGo() && useGlr)
                                                                  {
                                                            #line 5275 "PrintCLike.cpp"
  append(L"Count");
                                                            #line 3343 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 5281 "PrintCLike.cpp"
  append(L"count");
                                                            #line 3346 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 5285 "PrintCLike.cpp"
  append(L"(lookback) + 1");
                                                            #line 3347 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                  if (! isHaxe() && ! isScala() && ! isGo() && ! isPython())
                                                                  {
                                                            #line 5291 "PrintCLike.cpp"
  append(L"\n");
  append(L"  break");
                                                            #line 3351 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                  }
                                                                }
                                                            #line 5298 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3355 "PrintCLike.cpp.template"
                                                                if (isPython())
                                                                {
                                                            #line 5303 "PrintCLike.cpp"
  append(L"\n");
  append(L"elif ");
                                                            #line 3358 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 5308 "PrintCLike.cpp"
  append(L"action == ");
                                                            #line 3359 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 5314 "PrintCLike.cpp"
  append(L"\n");
  append(L"case ");
                                                            #line 3363 "PrintCLike.cpp.template"
                                                                }
                                                                print(format.toString<wchar_t>((int) LrStates::SHIFT_ACCEPT));
                                                                print(caseIntroducer());
                                                            #line 5321 "PrintCLike.cpp"
  append(L" ");
                                                            #line 3366 "PrintCLike.cpp.template"
                                                                print(inlineCommentIntroducer());
                                                            #line 5325 "PrintCLike.cpp"
  append(L"ACCEPT");
                                                            #line 3367 "PrintCLike.cpp.template"
                                                                if (trace)
                                                                {
                                                                  if (isCpp())
                                                                  {
                                                            #line 5332 "PrintCLike.cpp"
  append(L"\n");
  append(L"  fprintf(stderr, ");
                                                            #line 3372 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 5339 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3376 "PrintCLike.cpp.template"
                                                                    print(writeTrace());
                                                                  }
                                                            #line 5345 "PrintCLike.cpp"
  append(L"\"accept\\\"/>");
                                                            #line 3378 "PrintCLike.cpp.template"
                                                                  if (! isHaxe())
                                                                  {
                                                            #line 5350 "PrintCLike.cpp"
  append(L"\\n");
                                                            #line 3380 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 5354 "PrintCLike.cpp"
  append(L"\"");
                                                            #line 3381 "PrintCLike.cpp.template"
                                                                  print(endWriteTrace());
                                                                  print(semicolon());
                                                                  if (isHaxe())
                                                                  {
                                                            #line 5361 "PrintCLike.cpp"
  append(L"\n");
  append(L"  trace(traceLine);");
                                                            #line 3386 "PrintCLike.cpp.template"
                                                                  }
                                                                }
                                                                if (useGlr)
                                                                {
                                                            #line 5369 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3391 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 5374 "PrintCLike.cpp"
  append(L"accepted = ");
                                                            #line 3392 "PrintCLike.cpp.template"
                                                                  if (isPython())
                                                                  {
                                                            #line 5379 "PrintCLike.cpp"
  append(L"T");
                                                            #line 3394 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 5385 "PrintCLike.cpp"
  append(L"t");
                                                            #line 3397 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 5389 "PrintCLike.cpp"
  append(L"rue");
                                                            #line 3398 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                            #line 5393 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3400 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 5398 "PrintCLike.cpp"
  append(L"action = 0");
                                                            #line 3401 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                            #line 5402 "PrintCLike.cpp"
  append(L"\n");
  append(L"  return ");
                                                            #line 3403 "PrintCLike.cpp.template"
                                                                  if (isHaxe() || isTypescript() || isPython()) print(staticPrefix());
                                                            #line 5407 "PrintCLike.cpp"
  append(L"ACCEPTED");
                                                            #line 3404 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                                else
                                                                {
                                                            #line 5414 "PrintCLike.cpp"
  append(L"\n");
  append(L"  return");
                                                            #line 3409 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }

                                                                if (useGlr)
                                                                {
                                                            #line 5423 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3415 "PrintCLike.cpp.template"
                                                                  if (isPython())
                                                                  {
                                                            #line 5428 "PrintCLike.cpp"
  append(L"\n");
  append(L"elif ");
                                                            #line 3418 "PrintCLike.cpp.template"
                                                                    if (useGlr) print(thiz());
                                                            #line 5433 "PrintCLike.cpp"
  append(L"action == ");
                                                            #line 3419 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 5439 "PrintCLike.cpp"
  append(L"\n");
  append(L"case ");
                                                            #line 3423 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(format.toString<wchar_t>((int) LrStates::FORK));
                                                                  print(caseIntroducer());
                                                            #line 5446 "PrintCLike.cpp"
  append(L" ");
                                                            #line 3426 "PrintCLike.cpp.template"
                                                                  print(inlineCommentIntroducer());
                                                            #line 5450 "PrintCLike.cpp"
  append(L"FORK");
                                                            #line 3427 "PrintCLike.cpp.template"
                                                                  if (trace)
                                                                  {
                                                                    if (isCpp())
                                                                    {
                                                            #line 5457 "PrintCLike.cpp"
  append(L"\n");
  append(L"  fprintf(stderr, \"fork\\\"/>\\n\");");
                                                            #line 3432 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 5464 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3436 "PrintCLike.cpp.template"
                                                                      print(writeTrace());
                                                            #line 5469 "PrintCLike.cpp"
  append(L"\"fork\\\"/>");
                                                            #line 3437 "PrintCLike.cpp.template"
                                                                      if (! isHaxe())
                                                                      {
                                                            #line 5474 "PrintCLike.cpp"
  append(L"\\n\"");
                                                            #line 3439 "PrintCLike.cpp.template"
                                                                        print(endWriteTrace());
                                                                        print(semicolon());
                                                                      }
                                                                      else
                                                                      {
                                                            #line 5482 "PrintCLike.cpp"
  append(L"\";\n");
  append(L"  trace(traceLine);");
                                                            #line 3445 "PrintCLike.cpp.template"
                                                                      }
                                                                    }
                                                                  }
                                                                  if (isGo())
                                                                  {
                                                            #line 5491 "PrintCLike.cpp"
  append(L"\n");
  append(L"  heap.Push(this.threads, new(ParsingThread).copy(this, appendix[argument]))");
                                                            #line 3452 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isPython())
                                                                  {
                                                            #line 5498 "PrintCLike.cpp"
  append(L"\n");
  append(L"  forked = ");
                                                            #line 3456 "PrintCLike.cpp.template"
                                                                    print(staticPrefix());
                                                            #line 5503 "PrintCLike.cpp"
  append(L"ParsingThread().copy(self, ");
                                                            #line 3457 "PrintCLike.cpp.template"
                                                                    print(staticPrefix());
                                                            #line 5507 "PrintCLike.cpp"
  append(L"APPENDIX[argument])\n");
  append(L"  heapq.heappush(self.threads, (False, forked.e0, forked.id, forked))");
                                                            #line 3460 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 5514 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3464 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 5519 "PrintCLike.cpp"
  append(L"threads");
                                                            #line 3465 "PrintCLike.cpp.template"
                                                                    if (isCpp())
                                                                    {
                                                            #line 5524 "PrintCLike.cpp"
  append(L"->push(");
                                                            #line 3467 "PrintCLike.cpp.template"
                                                                    }
                                                                    else if (isScala())
                                                                    {
                                                            #line 5530 "PrintCLike.cpp"
  append(L" += ");
                                                            #line 3470 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 5536 "PrintCLike.cpp"
  append(L".offer(");
                                                            #line 3473 "PrintCLike.cpp.template"
                                                                    }
                                                                    if (isCpp() || isScala()) print(L"(");
                                                            #line 5541 "PrintCLike.cpp"
  append(L"new ParsingThread");
                                                            #line 3475 "PrintCLike.cpp.template"
                                                                    if (! isScala()) print(L"()");
                                                                    if (isCpp() || isScala()) print(L")");
                                                                    print(arrow());
                                                            #line 5547 "PrintCLike.cpp"
  append(L"copy(this");
                                                            #line 3478 "PrintCLike.cpp.template"
                                                                    if (isJavascript())
                                                                    {
                                                            #line 5552 "PrintCLike.cpp"
  append(L"Thread");
                                                            #line 3480 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 5556 "PrintCLike.cpp"
  append(L", ");
                                                            #line 3481 "PrintCLike.cpp.template"
                                                                    print(staticPrefix());
                                                            #line 5560 "PrintCLike.cpp"
  append(L"APPENDIX");
                                                            #line 3482 "PrintCLike.cpp.template"
                                                                    print(leftbracket());
                                                            #line 5564 "PrintCLike.cpp"
  append(L"argument");
                                                            #line 3483 "PrintCLike.cpp.template"
                                                                    print(rightbracket());
                                                            #line 5568 "PrintCLike.cpp"
  append(L")");
                                                            #line 3484 "PrintCLike.cpp.template"
                                                                    if (! isScala()) print(L")");
                                                                    print(semicolon());
                                                                  }
                                                            #line 5574 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3488 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 5579 "PrintCLike.cpp"
  append(L"action = ");
                                                            #line 3489 "PrintCLike.cpp.template"
                                                                  print(staticPrefix());
                                                                  if (isGo())
                                                                  {
                                                            #line 5585 "PrintCLike.cpp"
  append(L"appendix");
                                                            #line 3492 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 5591 "PrintCLike.cpp"
  append(L"APPENDIX");
                                                            #line 3495 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(leftbracket());
                                                            #line 5596 "PrintCLike.cpp"
  append(L"argument + 1");
                                                            #line 3497 "PrintCLike.cpp.template"
                                                                  print(rightbracket());
                                                                  print(semicolon());
                                                            #line 5601 "PrintCLike.cpp"
  append(L"\n");
  append(L"  return ");
                                                            #line 3500 "PrintCLike.cpp.template"
                                                                  if (isHaxe() || isTypescript() || isPython()) print(staticPrefix());
                                                            #line 5606 "PrintCLike.cpp"
  append(L"PARSING");
                                                            #line 3501 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                            #line 5611 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3504 "PrintCLike.cpp.template"
                                                                if (isPython())
                                                                {
                                                            #line 5616 "PrintCLike.cpp"
  append(L"\n");
  append(L"else");
                                                            #line 3507 "PrintCLike.cpp.template"
                                                                }
                                                                else if (isScala())
                                                                {
                                                            #line 5623 "PrintCLike.cpp"
  append(L"\n");
  append(L"case _");
                                                            #line 3511 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 5630 "PrintCLike.cpp"
  append(L"\n");
  append(L"default");
                                                            #line 3515 "PrintCLike.cpp.template"
                                                                }
                                                                print(caseIntroducer());
                                                            #line 5636 "PrintCLike.cpp"
  append(L" ");
                                                            #line 3517 "PrintCLike.cpp.template"
                                                                print(inlineCommentIntroducer());
                                                            #line 5640 "PrintCLike.cpp"
  append(L"ERROR");
                                                            #line 3518 "PrintCLike.cpp.template"
                                                                if (useGlr)
                                                                {
                                                                  if (trace)
                                                                  {
                                                                    if (isCpp())
                                                                    {
                                                            #line 5649 "PrintCLike.cpp"
  append(L"\n");
  append(L"  fprintf(stderr, \"fail\\\"/>\\n\");");
                                                            #line 3525 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 5656 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3529 "PrintCLike.cpp.template"
                                                                      print(writeTrace());
                                                            #line 5661 "PrintCLike.cpp"
  append(L"\"fail\\\"/>");
                                                            #line 3530 "PrintCLike.cpp.template"
                                                                      if (! isHaxe())
                                                                      {
                                                            #line 5666 "PrintCLike.cpp"
  append(L"\\n\"");
                                                            #line 3532 "PrintCLike.cpp.template"
                                                                        print(endWriteTrace());
                                                                        print(semicolon());
                                                                      }
                                                                      else
                                                                      {
                                                            #line 5674 "PrintCLike.cpp"
  append(L"\";\n");
  append(L"  trace(traceLine);");
                                                            #line 3538 "PrintCLike.cpp.template"
                                                                      }
                                                                    }
                                                                  }
                                                            #line 5681 "PrintCLike.cpp"
  append(L"\n");
  append(L"  return ");
                                                            #line 3542 "PrintCLike.cpp.template"
                                                                  if (isHaxe() || isTypescript() || isPython()) print(staticPrefix());
                                                            #line 5686 "PrintCLike.cpp"
  append(L"ERROR");
                                                            #line 3543 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                                else
                                                                {
                                                            #line 5693 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3548 "PrintCLike.cpp.template"
                                                                  print(beginThrowStmt());
                                                                  print(thiz());
                                                            #line 5699 "PrintCLike.cpp"
  append(L"b1, ");
                                                            #line 3550 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 5703 "PrintCLike.cpp"
  append(L"e1, ");
                                                            #line 3551 "PrintCLike.cpp.template"
                                                                  print(staticPrefix());
                                                                  if (isGo())
                                                                  {
                                                            #line 5709 "PrintCLike.cpp"
  append(L"tokenset");
                                                            #line 3554 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 5715 "PrintCLike.cpp"
  append(L"TOKENSET");
                                                            #line 3557 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(leftbracket());
                                                            #line 5720 "PrintCLike.cpp"
  append(L"state");
                                                            #line 3559 "PrintCLike.cpp.template"
                                                                  print(rightbracket());
                                                            #line 5724 "PrintCLike.cpp"
  append(L" + 1, ");
                                                            #line 3560 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 5728 "PrintCLike.cpp"
  append(L"l1, -1");
                                                            #line 3561 "PrintCLike.cpp.template"
                                                                  print(endThrowStmt());
                                                                  print(semicolon());
                                                                }
                                                                print(rightBrace());
                                                            #line 5735 "PrintCLike.cpp"
  append(L"\n");
  append(L"\n");
  append(L"if ");
                                                            #line 3567 "PrintCLike.cpp.template"
                                                                print(ifLeftParen());
                                                            #line 5741 "PrintCLike.cpp"
  append(L"shift >= 0");
                                                            #line 3568 "PrintCLike.cpp.template"
                                                                print(ifRightParen());
                                                                print(leftBrace());
                                                                if (trace)
                                                                {
                                                                  if (isCpp())
                                                                  {
                                                            #line 5750 "PrintCLike.cpp"
  append(L"\n");
  append(L"  fprintf(stderr, ");
                                                            #line 3575 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 5757 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3579 "PrintCLike.cpp.template"
                                                                    print(writeTrace());
                                                                  }
                                                            #line 5763 "PrintCLike.cpp"
  append(L"\"shift\"");
                                                            #line 3581 "PrintCLike.cpp.template"
                                                                  print(endWriteTrace());
                                                                  print(semicolon());
                                                                }
                                                            #line 5769 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if ");
                                                            #line 3585 "PrintCLike.cpp.template"
                                                                print(ifLeftParen());
                                                            #line 5774 "PrintCLike.cpp"
  append(L"nonterminalId < 0");
                                                            #line 3586 "PrintCLike.cpp.template"
                                                                print(ifRightParen());
                                                                printIndented(1, leftBrace());
                                                                if (minimalAmbiguity)
                                                                {
                                                            #line 5781 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 3591 "PrintCLike.cpp.template"
                                                                   print(thiz());
                                                            #line 5786 "PrintCLike.cpp"
  append(L"eventCount");
                                                            #line 3592 "PrintCLike.cpp.template"
                                                                      print(incrementOp());
                                                                      print(semicolon());
                                                                }
                                                                if (tree)
                                                                {
                                                            #line 5794 "PrintCLike.cpp"
  append(L"\n");
  append(L"    if ");
                                                            #line 3598 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                                  if (useGlr) print(thiz());
                                                            #line 5800 "PrintCLike.cpp"
  append(L"eventHandler != ");
                                                            #line 3600 "PrintCLike.cpp.template"
                                                                  print(nullPtr());
                                                                  print(ifRightParen());
                                                                  printIndented(2, leftBrace());
                                                                  if (useGlr)
                                                                  {
                                                            #line 5808 "PrintCLike.cpp"
  append(L"\n");
  append(L"      if ");
                                                            #line 3606 "PrintCLike.cpp.template"
                                                                    print(ifLeftParen());
                                                                    print(thiz());
                                                                    if (isGo())
                                                                    {
                                                            #line 5816 "PrintCLike.cpp"
  append(L"IsUnambiguous");
                                                            #line 3610 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 5822 "PrintCLike.cpp"
  append(L"isUnambiguous");
                                                            #line 3613 "PrintCLike.cpp.template"
                                                                    }
                                                                    if (! isScala()) print(L"()");
                                                                    print(ifRightParen());
                                                                    printIndented(3, leftBrace());
                                                                    increaseIndent();
                                                                  }
                                                            #line 5831 "PrintCLike.cpp"
  append(L"\n");
  append(L"      ");
                                                            #line 3620 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 5836 "PrintCLike.cpp"
  append(L"eventHandler");
                                                            #line 3621 "PrintCLike.cpp.template"
                                                                  print(arrow());
                                                                  if (isGo())
                                                                  {
                                                            #line 5842 "PrintCLike.cpp"
  append(L"T");
                                                            #line 3624 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 5848 "PrintCLike.cpp"
  append(L"t");
                                                            #line 3627 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 5852 "PrintCLike.cpp"
  append(L"erminal(");
                                                            #line 3628 "PrintCLike.cpp.template"
                                                                  print(staticPrefix());
                                                                  print(isGo() ? L"token" : L"TOKEN");
                                                                  print(leftbracket());
                                                                  print(thiz());
                                                            #line 5859 "PrintCLike.cpp"
  append(L"l1");
                                                            #line 3632 "PrintCLike.cpp.template"
                                                                  print(rightbracket());
                                                            #line 5863 "PrintCLike.cpp"
  append(L", ");
                                                            #line 3633 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 5867 "PrintCLike.cpp"
  append(L"b1, ");
                                                            #line 3634 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 5871 "PrintCLike.cpp"
  append(L"e1)");
                                                            #line 3635 "PrintCLike.cpp.template"
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
                                                            #line 5884 "PrintCLike.cpp"
  append(L"\n");
  append(L"      ");
                                                            #line 3646 "PrintCLike.cpp.template"
                                                                    printIndented(3, elseWithBraces());
                                                            #line 5889 "PrintCLike.cpp"
  append(L"\n");
  append(L"        ");
                                                            #line 3648 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 5894 "PrintCLike.cpp"
  append(L"deferredEvent = ");
                                                            #line 3649 "PrintCLike.cpp.template"
                                                                    if (isGo())
                                                                    {
                                                            #line 5899 "PrintCLike.cpp"
  append(L"&TerminalEvent{&AbstractDeferredEvent{");
                                                            #line 3651 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                                      if (! isPython())
                                                                      {
                                                            #line 5907 "PrintCLike.cpp"
  append(L"new ");
                                                            #line 3656 "PrintCLike.cpp.template"
                                                                      }
                                                                      if (! isHaxe() && ! isTypescript()) print(staticPrefix());
                                                                      if (isJavascript() || isTypescript())
                                                                      {
                                                            #line 5914 "PrintCLike.cpp"
  append(L"DeferredEvent");
                                                            #line 3660 "PrintCLike.cpp.template"
                                                                      }
                                                                      else
                                                                      {
                                                            #line 5920 "PrintCLike.cpp"
  append(L"TerminalEvent");
                                                            #line 3663 "PrintCLike.cpp.template"
                                                                      }
                                                            #line 5924 "PrintCLike.cpp"
  append(L"(");
                                                            #line 3664 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(thiz());
                                                            #line 5929 "PrintCLike.cpp"
  append(L"deferredEvent, ");
                                                            #line 3666 "PrintCLike.cpp.template"
                                                                    print(staticPrefix());
                                                                    print(isGo() ? L"token" : L"TOKEN");
                                                                    print(leftbracket());
                                                                    print(thiz());
                                                            #line 5936 "PrintCLike.cpp"
  append(L"l1");
                                                            #line 3670 "PrintCLike.cpp.template"
                                                                    print(rightbracket());
                                                            #line 5940 "PrintCLike.cpp"
  append(L", ");
                                                            #line 3671 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 5944 "PrintCLike.cpp"
  append(L"b1, ");
                                                            #line 3672 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 5948 "PrintCLike.cpp"
  append(L"e1");
                                                            #line 3674 "PrintCLike.cpp.template"
                                                                    if (isTypescript())
                                                                    {
                                                            #line 5953 "PrintCLike.cpp"
  append(L", -1");
                                                            #line 3676 "PrintCLike.cpp.template"
                                                                    }
                                                                    if (isGo())
                                                                    {
                                                            #line 5959 "PrintCLike.cpp"
  append(L"}}");
                                                            #line 3680 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 5965 "PrintCLike.cpp"
  append(L")");
                                                            #line 3684 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                                    }
                                                                    increaseIndent(3);
                                                                    print(rightBrace());
                                                                    decreaseIndent();
                                                                    print(rightBrace());
                                                                    decreaseIndent(2);
                                                                  }
                                                            #line 5976 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 3693 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 5981 "PrintCLike.cpp"
  append(L"es = ");
                                                            #line 3694 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 5985 "PrintCLike.cpp"
  append(L"e1");
                                                            #line 3695 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                                if (useGlr)
                                                                {
                                                            #line 5992 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 3700 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 5997 "PrintCLike.cpp"
  append(L"stack = ");
                                                            #line 3701 "PrintCLike.cpp.template"
                                                                  if (isGo())
                                                                  {
                                                            #line 6002 "PrintCLike.cpp"
  append(L"&StackNode{");
                                                            #line 3703 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                                    if (! isPython())
                                                                    {
                                                            #line 6010 "PrintCLike.cpp"
  append(L"new ");
                                                            #line 3708 "PrintCLike.cpp.template"
                                                                    }
                                                                    if (! isHaxe() && ! isTypescript()) print(staticPrefix());
                                                            #line 6015 "PrintCLike.cpp"
  append(L"StackNode(");
                                                            #line 3710 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(thiz());
                                                            #line 6020 "PrintCLike.cpp"
  append(L"state, ");
                                                            #line 3712 "PrintCLike.cpp.template"
                                                                  if (grammar->states->hasLookback)
                                                                  {
                                                            #line 6025 "PrintCLike.cpp"
  append(L"lookback, ");
                                                            #line 3714 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(thiz());
                                                            #line 6030 "PrintCLike.cpp"
  append(L"b1, ");
                                                            #line 3716 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 6034 "PrintCLike.cpp"
  append(L"stack");
                                                            #line 3717 "PrintCLike.cpp.template"
                                                                  print(isGo() ? L"}" : L")");
                                                                  print(semicolon());
                                                                }
                                                                else
                                                                {
                                                            #line 6042 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 3723 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 6047 "PrintCLike.cpp"
  append(L"push(state, lookback");
                                                            #line 3724 "PrintCLike.cpp.template"
                                                                  if (tree)
                                                                  {
                                                            #line 6052 "PrintCLike.cpp"
  append(L", ");
                                                            #line 3726 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 6056 "PrintCLike.cpp"
  append(L"b1");
                                                            #line 3727 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 6060 "PrintCLike.cpp"
  append(L")");
                                                            #line 3728 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                            #line 6065 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 3731 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 6070 "PrintCLike.cpp"
  append(L"consume(");
                                                            #line 3732 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 6074 "PrintCLike.cpp"
  append(L"l1)");
                                                            #line 3733 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 6078 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3735 "PrintCLike.cpp.template"
                                                                printIndented(1, elseWithBraces());
                                                                if (useGlr)
                                                                {
                                                            #line 6085 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 3739 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 6090 "PrintCLike.cpp"
  append(L"stack = ");
                                                            #line 3740 "PrintCLike.cpp.template"
                                                                  if (isGo())
                                                                  {
                                                            #line 6095 "PrintCLike.cpp"
  append(L"&StackNode{");
                                                            #line 3742 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                                    if (! isPython())
                                                                    {
                                                            #line 6103 "PrintCLike.cpp"
  append(L"new ");
                                                            #line 3747 "PrintCLike.cpp.template"
                                                                    }
                                                                    if (! isHaxe() && ! isTypescript()) print(staticPrefix());
                                                            #line 6108 "PrintCLike.cpp"
  append(L"StackNode(");
                                                            #line 3749 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(thiz());
                                                            #line 6113 "PrintCLike.cpp"
  append(L"state, ");
                                                            #line 3751 "PrintCLike.cpp.template"
                                                                  if (grammar->states->hasLookback)
                                                                  {
                                                            #line 6118 "PrintCLike.cpp"
  append(L"lookback, ");
                                                            #line 3753 "PrintCLike.cpp.template"
                                                                  }
                                                                  if (tree)
                                                                  {
                                                                    print(thiz());
                                                            #line 6125 "PrintCLike.cpp"
  append(L"bs");
                                                            #line 3757 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 6131 "PrintCLike.cpp"
  append(L"0");
                                                            #line 3760 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 6135 "PrintCLike.cpp"
  append(L", ");
                                                            #line 3761 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 6139 "PrintCLike.cpp"
  append(L"stack");
                                                            #line 3762 "PrintCLike.cpp.template"
                                                                  print(isGo() ? L"}" : L")");
                                                                  print(semicolon());
                                                                }
                                                                else
                                                                {
                                                            #line 6147 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 3768 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 6152 "PrintCLike.cpp"
  append(L"push(state, lookback");
                                                            #line 3769 "PrintCLike.cpp.template"
                                                                  if (tree)
                                                                  {
                                                            #line 6157 "PrintCLike.cpp"
  append(L", bs");
                                                            #line 3771 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 6161 "PrintCLike.cpp"
  append(L")");
                                                            #line 3772 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                                increaseIndent();
                                                                print(rightBrace());
                                                                decreaseIndent();
                                                            #line 6169 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3778 "PrintCLike.cpp.template"
                                                                if (useGlr) print(thiz());
                                                            #line 6174 "PrintCLike.cpp"
  append(L"state = shift");
                                                            #line 3779 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                print(rightBrace());
                                                            #line 6179 "PrintCLike.cpp"
  append(L"\n");
  append(L"\n");
  append(L"if ");
                                                            #line 3783 "PrintCLike.cpp.template"
                                                                print(ifLeftParen());
                                                            #line 6185 "PrintCLike.cpp"
  append(L"reduce < 0");
                                                            #line 3784 "PrintCLike.cpp.template"
                                                                print(ifRightParen());
                                                                print(leftBrace());
                                                                if (trace)
                                                                {
                                                                  if (isCpp())
                                                                  {
                                                            #line 6194 "PrintCLike.cpp"
  append(L"\n");
  append(L"  fprintf(stderr, ");
                                                            #line 3791 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 6201 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3795 "PrintCLike.cpp.template"
                                                                    print(writeTrace());
                                                                  }
                                                            #line 6207 "PrintCLike.cpp"
  append(L"\"\\\"/>");
                                                            #line 3798 "PrintCLike.cpp.template"
                                                                  if (! isHaxe())
                                                                  {
                                                            #line 6212 "PrintCLike.cpp"
  append(L"\\n\"");
                                                            #line 3800 "PrintCLike.cpp.template"
                                                                    print(endWriteTrace());
                                                                    print(semicolon());
                                                                  }
                                                                  else
                                                                  {
                                                            #line 6220 "PrintCLike.cpp"
  append(L"\";\n");
  append(L"  trace(traceLine);");
                                                            #line 3806 "PrintCLike.cpp.template"
                                                                  }
                                                                }
                                                            #line 6226 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3809 "PrintCLike.cpp.template"
                                                                if (useGlr) print(thiz());
                                                            #line 6231 "PrintCLike.cpp"
  append(L"action = ");
                                                            #line 3810 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 6235 "PrintCLike.cpp"
  append(L"predict(");
                                                            #line 3811 "PrintCLike.cpp.template"
                                                                if (useGlr) print(thiz());
                                                            #line 6239 "PrintCLike.cpp"
  append(L"state)");
                                                            #line 3812 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                if (useGlr)
                                                                {
                                                                  if (isCpp())
                                                                  {
                                                            #line 6247 "PrintCLike.cpp"
  append(L"\n");
  append(L"  break");
                                                            #line 3818 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                  }
                                                                  else
                                                                  {
                                                            #line 6255 "PrintCLike.cpp"
  append(L"\n");
  append(L"  return ");
                                                            #line 3823 "PrintCLike.cpp.template"
                                                                    if (isHaxe() || isTypescript() || isPython()) print(staticPrefix());
                                                            #line 6260 "PrintCLike.cpp"
  append(L"PARSING");
                                                            #line 3824 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                  }
                                                                }
                                                                else
                                                                {
                                                            #line 6268 "PrintCLike.cpp"
  append(L"\n");
  append(L"  nonterminalId = -1");
                                                            #line 3830 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                            #line 6274 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3833 "PrintCLike.cpp.template"
                                                                print(elseWithBraces());
                                                                if (hasCustomCode)
                                                                {
                                                            #line 6280 "PrintCLike.cpp"
  append(L"\n");
  append(L"  nonterminalId = ");
                                                            #line 3837 "PrintCLike.cpp.template"
                                                                  print(staticPrefix());
                                                                  if (isGo())
                                                                  {
                                                            #line 6287 "PrintCLike.cpp"
  append(L"reduction");
                                                            #line 3840 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 6293 "PrintCLike.cpp"
  append(L"REDUCTION");
                                                            #line 3843 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(leftbracket());
                                                            #line 6298 "PrintCLike.cpp"
  append(L"reduce");
                                                            #line 3845 "PrintCLike.cpp.template"
                                                                  print(rightbracket());
                                                                  print(semicolon());
                                                            #line 6303 "PrintCLike.cpp"
  append(L"\n");
  append(L"  reduce = ");
                                                            #line 3848 "PrintCLike.cpp.template"
                                                                  print(staticPrefix());
                                                                  if (isGo())
                                                                  {
                                                            #line 6310 "PrintCLike.cpp"
  append(L"reduction");
                                                            #line 3851 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 6316 "PrintCLike.cpp"
  append(L"REDUCTION");
                                                            #line 3854 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(leftbracket());
                                                            #line 6321 "PrintCLike.cpp"
  append(L"reduce + 1");
                                                            #line 3856 "PrintCLike.cpp.template"
                                                                  print(rightbracket());
                                                                  print(semicolon());
                                                            #line 6326 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if ");
                                                            #line 3859 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                            #line 6331 "PrintCLike.cpp"
  append(L"reduce >= 0");
                                                            #line 3860 "PrintCLike.cpp.template"
                                                                  print(ifRightParen());
                                                                  increaseIndent();
                                                                  print(leftBrace());
                                                                  if (useGlr)
                                                                  {
                                                            #line 6339 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if ");
                                                            #line 3866 "PrintCLike.cpp.template"
                                                                    print(ifLeftParen());
                                                                    print(thiz());
                                                                    if (isGo())
                                                                    {
                                                            #line 6347 "PrintCLike.cpp"
  append(L"IsUnambiguous");
                                                            #line 3870 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 6353 "PrintCLike.cpp"
  append(L"isUnambiguous");
                                                            #line 3873 "PrintCLike.cpp.template"
                                                                    }
                                                                    if (! isScala()) print(L"()");
                                                                    print(ifRightParen());
                                                                    print(leftBrace());
                                                            #line 6360 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 3878 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                                    print(isGo() && useGlr ? L"E" : L"e");
                                                            #line 6366 "PrintCLike.cpp"
  append(L"xecute(reduce)");
                                                            #line 3880 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 6370 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3882 "PrintCLike.cpp.template"
                                                                    print(elseWithBraces());
                                                            #line 6375 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 3884 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 6380 "PrintCLike.cpp"
  append(L"deferredCode = ");
                                                            #line 3885 "PrintCLike.cpp.template"
                                                                    if (isGo())
                                                                    {
                                                            #line 6385 "PrintCLike.cpp"
  append(L"&DeferredCode{");
                                                            #line 3888 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                                      if (! isPython())
                                                                      {
                                                            #line 6393 "PrintCLike.cpp"
  append(L"new ");
                                                            #line 3893 "PrintCLike.cpp.template"
                                                                      }
                                                                      if (! isHaxe() && ! isTypescript()) print(staticPrefix());
                                                            #line 6398 "PrintCLike.cpp"
  append(L"DeferredCode(");
                                                            #line 3895 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(thiz());
                                                            #line 6403 "PrintCLike.cpp"
  append(L"deferredCode, reduce, ");
                                                            #line 3897 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 6407 "PrintCLike.cpp"
  append(L"b0, ");
                                                            #line 3898 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 6411 "PrintCLike.cpp"
  append(L"e0");
                                                            #line 3900 "PrintCLike.cpp.template"
                                                                    if (isGo())
                                                                    {
                                                            #line 6416 "PrintCLike.cpp"
  append(L"}");
                                                            #line 3903 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 6422 "PrintCLike.cpp"
  append(L")");
                                                            #line 3907 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(semicolon());
                                                                    increaseIndent();
                                                                    print(rightBrace());
                                                                    decreaseIndent();
                                                                  }
                                                                  else
                                                                  {
                                                            #line 6433 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3916 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                                    print(isGo() && useGlr ? L"E" : L"e");
                                                            #line 6439 "PrintCLike.cpp"
  append(L"xecute(reduce)");
                                                            #line 3918 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                  }
                                                                  print(rightBrace());
                                                                  decreaseIndent();
                                                                }
                                                                else
                                                                {
                                                            #line 6449 "PrintCLike.cpp"
  append(L"\n");
  append(L"  nonterminalId = reduce");
                                                            #line 3926 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                                if (minimalAmbiguity)
                                                                {
                                                            #line 6457 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3931 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 6462 "PrintCLike.cpp"
  append(L"eventCount");
                                                            #line 3932 "PrintCLike.cpp.template"
                                                                  print(incrementOp());
                                                                  print(semicolon());
                                                                }
                                                                if (trace)
                                                                {
                                                            #line 6470 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if ");
                                                            #line 3938 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                            #line 6475 "PrintCLike.cpp"
  append(L"shift >= 0");
                                                            #line 3939 "PrintCLike.cpp.template"
                                                                  print(ifRightParen());
                                                                  printIndented(1, leftBrace());
                                                                  if (isCpp())
                                                                  {
                                                            #line 6482 "PrintCLike.cpp"
  append(L"\n");
  append(L"    fprintf(stderr, ");
                                                            #line 3944 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 6489 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 3948 "PrintCLike.cpp.template"
                                                                    print(writeTrace());
                                                                  }
                                                            #line 6495 "PrintCLike.cpp"
  append(L"\" \"");
                                                            #line 3950 "PrintCLike.cpp.template"
                                                                  print(endWriteTrace());
                                                                  print(semicolon());
                                                                  increaseIndent();
                                                                  print(rightBrace());
                                                                  decreaseIndent();
                                                                  if (isCpp())
                                                                  {
                                                            #line 6505 "PrintCLike.cpp"
  append(L"\n");
  append(L"  fprintf(stderr, \"reduce\\\" nonterminal=\\\"%s\\\" count=\\\"%d\\\"/>\\n\", ");
                                                            #line 3958 "PrintCLike.cpp.template"
                                                                    if (stringIntroducer()[0])
                                                                    {
                                                            #line 6511 "PrintCLike.cpp"
  append(L"Utf8Encoder::encode(");
                                                            #line 3960 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 6515 "PrintCLike.cpp"
  append(L"xmlEscape(");
                                                            #line 3961 "PrintCLike.cpp.template"
                                                                    print(isGo() ? L"nonterminal" : L"NONTERMINAL");
                                                            #line 6519 "PrintCLike.cpp"
  append(L"[nonterminalId], 0).c_str()");
                                                            #line 3963 "PrintCLike.cpp.template"
                                                                    if (stringIntroducer()[0])
                                                                    {
                                                            #line 6524 "PrintCLike.cpp"
  append(L").c_str()");
                                                            #line 3965 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 6528 "PrintCLike.cpp"
  append(L", symbols);");
                                                            #line 3966 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 6534 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3970 "PrintCLike.cpp.template"
                                                                    print(writeTrace());
                                                            #line 6539 "PrintCLike.cpp"
  append(L"\"reduce\\\" nonterminal=\\\"\" + ");
                                                            #line 3972 "PrintCLike.cpp.template"
                                                                    print(staticPrefix());
                                                            #line 6543 "PrintCLike.cpp"
  append(L"xmlEscape(");
                                                            #line 3973 "PrintCLike.cpp.template"
                                                                    print(staticPrefix());
                                                                    print(isGo() ? L"nonterminal" : L"NONTERMINAL");
                                                                    print(leftbracket());
                                                            #line 6549 "PrintCLike.cpp"
  append(L"nonterminalId");
                                                            #line 3976 "PrintCLike.cpp.template"
                                                                    print(rightbracket());
                                                            #line 6553 "PrintCLike.cpp"
  append(L") + \"\\\" count=\\\"\" + ");
                                                            #line 3978 "PrintCLike.cpp.template"
                                                                    if (isPython())
                                                                    {
                                                            #line 6558 "PrintCLike.cpp"
  append(L"str(");
                                                            #line 3981 "PrintCLike.cpp.template"
                                                                    }
                                                                    else if (isGo())
                                                                    {
                                                            #line 6564 "PrintCLike.cpp"
  append(L"strconv.Itoa(");
                                                            #line 3985 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 6568 "PrintCLike.cpp"
  append(L"symbols");
                                                            #line 3987 "PrintCLike.cpp.template"
                                                                    if (isGo() || isPython())
                                                                    {
                                                            #line 6573 "PrintCLike.cpp"
  append(L")");
                                                            #line 3990 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 6577 "PrintCLike.cpp"
  append(L" + \"\\\"/>");
                                                            #line 3992 "PrintCLike.cpp.template"
                                                                    if (! isHaxe())
                                                                    {
                                                            #line 6582 "PrintCLike.cpp"
  append(L"\\n\"");
                                                            #line 3995 "PrintCLike.cpp.template"
                                                                      print(endWriteTrace());
                                                                      print(semicolon());
                                                                    }
                                                                    else
                                                                    {
                                                            #line 6590 "PrintCLike.cpp"
  append(L"\";\n");
  append(L"  trace(traceLine);");
                                                            #line 4001 "PrintCLike.cpp.template"
                                                                    }
                                                                  }
                                                                }
                                                                if (tree)
                                                                {
                                                            #line 6599 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if ");
                                                            #line 4007 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                            #line 6604 "PrintCLike.cpp"
  append(L"symbols > 0");
                                                            #line 4008 "PrintCLike.cpp.template"
                                                                  print(ifRightParen());
                                                                  printIndented(1, leftBrace());
                                                                  if (useGlr)
                                                                  {
                                                                    if (isCpp())
                                                                    {
                                                            #line 6613 "PrintCLike.cpp"
  append(L"\n");
  append(L"    stack = stack->pop(symbols - 1);");
                                                            #line 4015 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                                      increaseIndent(2);
                                                                      if (isHaxe())
                                                                      {
                                                            #line 6623 "PrintCLike.cpp"
  append(L"\n");
  append(L"for (i in 1...symbols)");
                                                            #line 4022 "PrintCLike.cpp.template"
                                                                      }
                                                                      else if (isScala())
                                                                      {
                                                            #line 6630 "PrintCLike.cpp"
  append(L"\n");
  append(L"var i = 0\n");
  append(L"for (i <- 2 to symbols)");
                                                            #line 4027 "PrintCLike.cpp.template"
                                                                      }
                                                                      else if (isPython())
                                                                      {
                                                            #line 6638 "PrintCLike.cpp"
  append(L"\n");
  append(L"for _ in range(symbols - 1):");
                                                            #line 4031 "PrintCLike.cpp.template"
                                                                      }
                                                                      else
                                                                      {
                                                            #line 6645 "PrintCLike.cpp"
  append(L"\n");
  append(L"for ");
                                                            #line 4035 "PrintCLike.cpp.template"
                                                                        print(ifLeftParen());
                                                                        print(intVar());
                                                            #line 6651 "PrintCLike.cpp"
  append(L"i");
                                                            #line 4037 "PrintCLike.cpp.template"
                                                                        print(assign());
                                                            #line 6655 "PrintCLike.cpp"
  append(L"1; i < symbols; i++");
                                                            #line 4038 "PrintCLike.cpp.template"
                                                                        print(ifRightParen());
                                                                      }
                                                                      print(leftBrace());
                                                            #line 6661 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4042 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 6666 "PrintCLike.cpp"
  append(L"stack = ");
                                                            #line 4043 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 6670 "PrintCLike.cpp"
  append(L"stack.link");
                                                            #line 4044 "PrintCLike.cpp.template"
                                                                      if (isTypescript()) print(L"!");
                                                                      print(semicolon());
                                                                      print(rightBrace());
                                                                      decreaseIndent(2);
                                                                    }
                                                            #line 6678 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4050 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 6683 "PrintCLike.cpp"
  append(L"state = ");
                                                            #line 4051 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 6687 "PrintCLike.cpp"
  append(L"stack");
                                                            #line 4052 "PrintCLike.cpp.template"
                                                                    print(arrow());
                                                            #line 6691 "PrintCLike.cpp"
  append(L"state");
                                                            #line 4053 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 6695 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4055 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 6700 "PrintCLike.cpp"
  append(L"bs = ");
                                                            #line 4056 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 6704 "PrintCLike.cpp"
  append(L"stack");
                                                            #line 4057 "PrintCLike.cpp.template"
                                                                    print(arrow());
                                                            #line 6708 "PrintCLike.cpp"
  append(L"pos");
                                                            #line 4058 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                    if (isCpp())
                                                                    {
                                                            #line 6714 "PrintCLike.cpp"
  append(L"\n");
  append(L"    stack = stack->pop(1);");
                                                            #line 4062 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 6721 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4066 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 6726 "PrintCLike.cpp"
  append(L"stack = ");
                                                            #line 4067 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 6730 "PrintCLike.cpp"
  append(L"stack.link");
                                                            #line 4068 "PrintCLike.cpp.template"
                                                                      if (isTypescript()) print(L"!");
                                                                      print(semicolon());
                                                                    }
                                                                  }
                                                                  else
                                                                  {
                                                            #line 6739 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4075 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 6744 "PrintCLike.cpp"
  append(L"top -= symbols * 3");
                                                            #line 4076 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 6748 "PrintCLike.cpp"
  append(L"\n");
  append(L"    state = ");
                                                            #line 4078 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 6753 "PrintCLike.cpp"
  append(L"iStack");
                                                            #line 4079 "PrintCLike.cpp.template"
                                                                    print(leftbracket());
                                                                    print(thiz());
                                                            #line 6758 "PrintCLike.cpp"
  append(L"top + 2");
                                                            #line 4081 "PrintCLike.cpp.template"
                                                                    print(rightbracket());
                                                                    print(semicolon());
                                                            #line 6763 "PrintCLike.cpp"
  append(L"\n");
  append(L"    bs = ");
                                                            #line 4084 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 6768 "PrintCLike.cpp"
  append(L"iStack");
                                                            #line 4085 "PrintCLike.cpp.template"
                                                                    print(leftbracket());
                                                                    print(thiz());
                                                            #line 6773 "PrintCLike.cpp"
  append(L"top + 1");
                                                            #line 4087 "PrintCLike.cpp.template"
                                                                    print(rightbracket());
                                                                    print(semicolon());
                                                                  }
                                                            #line 6779 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4091 "PrintCLike.cpp.template"
                                                                  printIndented(1, elseWithBraces());
                                                            #line 6784 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4093 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 6789 "PrintCLike.cpp"
  append(L"bs = ");
                                                            #line 4094 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 6793 "PrintCLike.cpp"
  append(L"b1");
                                                            #line 4095 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                            #line 6797 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4097 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 6802 "PrintCLike.cpp"
  append(L"es = ");
                                                            #line 4098 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 6806 "PrintCLike.cpp"
  append(L"b1");
                                                            #line 4099 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                  increaseIndent();
                                                                  print(rightBrace());
                                                                  decreaseIndent();
                                                            #line 6813 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if ");
                                                            #line 4104 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                            #line 6818 "PrintCLike.cpp"
  append(L"nonterminalId == ");
                                                            #line 4105 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 6822 "PrintCLike.cpp"
  append(L"target ");
                                                            #line 4106 "PrintCLike.cpp.template"
                                                                  if (isPython())
                                                                  {
                                                            #line 6827 "PrintCLike.cpp"
  append(L"and");
                                                            #line 4108 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 6833 "PrintCLike.cpp"
  append(L"&&");
                                                            #line 4111 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 6837 "PrintCLike.cpp"
  append(L" ");
                                                            #line 4112 "PrintCLike.cpp.template"
                                                                  if (useGlr)
                                                                  {
                                                                    print(thiz());
                                                            #line 6843 "PrintCLike.cpp"
  append(L"stack");
                                                            #line 4115 "PrintCLike.cpp.template"
                                                                    print(arrow());
                                                            #line 6847 "PrintCLike.cpp"
  append(L"link == ");
                                                            #line 4116 "PrintCLike.cpp.template"
                                                                    print(nullPtr());
                                                                  }
                                                                  else
                                                                  {
                                                            #line 6854 "PrintCLike.cpp"
  append(L"t == ");
                                                            #line 4120 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 6858 "PrintCLike.cpp"
  append(L"top");
                                                            #line 4121 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(ifRightParen());
                                                                  printIndented(1, leftBrace());
                                                            #line 6864 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4125 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 6869 "PrintCLike.cpp"
  append(L"bs = ");
                                                            #line 4126 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 6873 "PrintCLike.cpp"
  append(L"bw");
                                                            #line 4127 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                            #line 6877 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4129 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 6882 "PrintCLike.cpp"
  append(L"es = ");
                                                            #line 4130 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 6886 "PrintCLike.cpp"
  append(L"b1");
                                                            #line 4131 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                            #line 6890 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4133 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 6895 "PrintCLike.cpp"
  append(L"bw = ");
                                                            #line 4134 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 6899 "PrintCLike.cpp"
  append(L"b1");
                                                            #line 4135 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                  increaseIndent();
                                                                  print(rightBrace());
                                                                  decreaseIndent();
                                                            #line 6906 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if ");
                                                            #line 4140 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                                  if (useGlr) print(thiz());
                                                            #line 6912 "PrintCLike.cpp"
  append(L"eventHandler != ");
                                                            #line 4142 "PrintCLike.cpp.template"
                                                                  print(nullPtr());
                                                                  print(ifRightParen());
                                                                  printIndented(1, leftBrace());
                                                                  if (useGlr)
                                                                  {
                                                            #line 6920 "PrintCLike.cpp"
  append(L"\n");
  append(L"    if ");
                                                            #line 4148 "PrintCLike.cpp.template"
                                                                    print(ifLeftParen());
                                                                    print(thiz());
                                                                    if (isGo())
                                                                    {
                                                            #line 6928 "PrintCLike.cpp"
  append(L"IsUnambiguous");
                                                            #line 4152 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 6934 "PrintCLike.cpp"
  append(L"isUnambiguous");
                                                            #line 4155 "PrintCLike.cpp.template"
                                                                    }
                                                                    if (! isScala()) print(L"()");
                                                                    print(ifRightParen());
                                                                    printIndented(2, leftBrace());
                                                                    increaseIndent();
                                                                  }
                                                            #line 6943 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4162 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 6948 "PrintCLike.cpp"
  append(L"eventHandler");
                                                            #line 4163 "PrintCLike.cpp.template"
                                                                  print(arrow());
                                                                  if (isGo())
                                                                  {
                                                            #line 6954 "PrintCLike.cpp"
  append(L"N");
                                                            #line 4166 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 6960 "PrintCLike.cpp"
  append(L"n");
                                                            #line 4169 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 6964 "PrintCLike.cpp"
  append(L"onterminal(");
                                                            #line 4170 "PrintCLike.cpp.template"
                                                                  print(staticPrefix());
                                                                  print(isGo() ? L"nonterminal" : L"NONTERMINAL");
                                                                  print(leftbracket());
                                                            #line 6970 "PrintCLike.cpp"
  append(L"nonterminalId");
                                                            #line 4173 "PrintCLike.cpp.template"
                                                                  print(rightbracket());
                                                            #line 6974 "PrintCLike.cpp"
  append(L", ");
                                                            #line 4174 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 6978 "PrintCLike.cpp"
  append(L"bs, ");
                                                            #line 4175 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 6982 "PrintCLike.cpp"
  append(L"es, symbols)");
                                                            #line 4177 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                  if (useGlr)
                                                                  {
                                                                    decreaseIndent();
                                                            #line 6989 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4182 "PrintCLike.cpp.template"
                                                                    printIndented(2, elseWithBraces());
                                                            #line 6994 "PrintCLike.cpp"
  append(L"\n");
  append(L"      ");
                                                            #line 4184 "PrintCLike.cpp.template"
                                                                    if (useGlr) print(thiz());
                                                            #line 6999 "PrintCLike.cpp"
  append(L"deferredEvent = ");
                                                            #line 4185 "PrintCLike.cpp.template"
                                                                    if (isGo())
                                                                    {
                                                            #line 7004 "PrintCLike.cpp"
  append(L"&NonterminalEvent{&AbstractDeferredEvent{this.deferredEvent, nonterminal[nonterminalId], this.bs, this.es}, symbols}");
                                                            #line 4188 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                                      if (! isPython())
                                                                      {
                                                            #line 7012 "PrintCLike.cpp"
  append(L"new ");
                                                            #line 4193 "PrintCLike.cpp.template"
                                                                      }
                                                                      if (! isHaxe() && ! isTypescript()) print(staticPrefix());
                                                                      if (isJavascript() || isTypescript())
                                                                      {
                                                            #line 7019 "PrintCLike.cpp"
  append(L"DeferredEvent");
                                                            #line 4197 "PrintCLike.cpp.template"
                                                                      }
                                                                      else
                                                                      {
                                                            #line 7025 "PrintCLike.cpp"
  append(L"NonterminalEvent");
                                                            #line 4200 "PrintCLike.cpp.template"
                                                                      }
                                                            #line 7029 "PrintCLike.cpp"
  append(L"(");
                                                            #line 4201 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 7033 "PrintCLike.cpp"
  append(L"deferredEvent, ");
                                                            #line 4202 "PrintCLike.cpp.template"
                                                                      print(staticPrefix());
                                                            #line 7037 "PrintCLike.cpp"
  append(L"NONTERMINAL");
                                                            #line 4203 "PrintCLike.cpp.template"
                                                                      print(leftbracket());
                                                            #line 7041 "PrintCLike.cpp"
  append(L"nonterminalId");
                                                            #line 4204 "PrintCLike.cpp.template"
                                                                      print(rightbracket());
                                                            #line 7045 "PrintCLike.cpp"
  append(L", ");
                                                            #line 4205 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 7049 "PrintCLike.cpp"
  append(L"bs, ");
                                                            #line 4207 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 7053 "PrintCLike.cpp"
  append(L"es, symbols)");
                                                            #line 4209 "PrintCLike.cpp.template"
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
                                                            #line 7068 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if ");
                                                            #line 4222 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                            #line 7073 "PrintCLike.cpp"
  append(L"symbols > 0");
                                                            #line 4223 "PrintCLike.cpp.template"
                                                                  print(ifRightParen());
                                                                  printIndented(1, leftBrace());
                                                                  if (useGlr)
                                                                  {
                                                                    if (isCpp())
                                                                    {
                                                            #line 7082 "PrintCLike.cpp"
  append(L"\n");
  append(L"    stack = stack->pop(symbols - 1);");
                                                            #line 4230 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                                      increaseIndent(2);
                                                                      if (isHaxe())
                                                                      {
                                                            #line 7092 "PrintCLike.cpp"
  append(L"\n");
  append(L"for (i in 1...symbols)");
                                                            #line 4237 "PrintCLike.cpp.template"
                                                                      }
                                                                      else if (isScala())
                                                                      {
                                                            #line 7099 "PrintCLike.cpp"
  append(L"\n");
  append(L"var i = 0\n");
  append(L"for (i <- 2 to symbols)");
                                                            #line 4242 "PrintCLike.cpp.template"
                                                                      }
                                                                      else if (isPython())
                                                                      {
                                                            #line 7107 "PrintCLike.cpp"
  append(L"\n");
  append(L"for _ in range(symbols - 1):");
                                                            #line 4246 "PrintCLike.cpp.template"
                                                                      }
                                                                      else
                                                                      {
                                                            #line 7114 "PrintCLike.cpp"
  append(L"\n");
  append(L"for ");
                                                            #line 4250 "PrintCLike.cpp.template"
                                                                        print(ifLeftParen());
                                                                        print(intVar());
                                                            #line 7120 "PrintCLike.cpp"
  append(L"i");
                                                            #line 4252 "PrintCLike.cpp.template"
                                                                        print(assign());
                                                            #line 7124 "PrintCLike.cpp"
  append(L"1; i < symbols; i++");
                                                            #line 4253 "PrintCLike.cpp.template"
                                                                        print(ifRightParen());
                                                                      }
                                                                      print(leftBrace());
                                                            #line 7130 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4257 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 7135 "PrintCLike.cpp"
  append(L"stack = ");
                                                            #line 4258 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 7139 "PrintCLike.cpp"
  append(L"stack.link");
                                                            #line 4259 "PrintCLike.cpp.template"
                                                                      if (isTypescript()) print(L"!");
                                                                      print(semicolon());
                                                                      print(rightBrace());
                                                                      decreaseIndent(2);
                                                                    }
                                                            #line 7147 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4266 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7152 "PrintCLike.cpp"
  append(L"state = ");
                                                            #line 4267 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7156 "PrintCLike.cpp"
  append(L"stack");
                                                            #line 4268 "PrintCLike.cpp.template"
                                                                    print(arrow());
                                                            #line 7160 "PrintCLike.cpp"
  append(L"state");
                                                            #line 4269 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                    if (tree)
                                                                    {
                                                            #line 7166 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4273 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 7171 "PrintCLike.cpp"
  append(L"bs = ");
                                                            #line 4274 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 7175 "PrintCLike.cpp"
  append(L"stack");
                                                            #line 4275 "PrintCLike.cpp.template"
                                                                      print(arrow());
                                                            #line 7179 "PrintCLike.cpp"
  append(L"pos");
                                                            #line 4276 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                                    }
                                                                    if (isCpp())
                                                                    {
                                                            #line 7186 "PrintCLike.cpp"
  append(L"\n");
  append(L"    stack = stack->pop(1);");
                                                            #line 4281 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 7193 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4285 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 7198 "PrintCLike.cpp"
  append(L"stack = ");
                                                            #line 4286 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 7202 "PrintCLike.cpp"
  append(L"stack.link");
                                                            #line 4287 "PrintCLike.cpp.template"
                                                                      if (isTypescript()) print(L"!");
                                                                      print(semicolon());
                                                                    }
                                                                  }
                                                                  else
                                                                  {
                                                            #line 7211 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4294 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7216 "PrintCLike.cpp"
  append(L"top -= symbols << 1;\n");
  append(L"    state = ");
                                                            #line 4296 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7221 "PrintCLike.cpp"
  append(L"iStack");
                                                            #line 4297 "PrintCLike.cpp.template"
                                                                    print(leftbracket());
                                                                    print(thiz());
                                                            #line 7226 "PrintCLike.cpp"
  append(L"top + 1");
                                                            #line 4299 "PrintCLike.cpp.template"
                                                                    print(rightbracket());
                                                                    print(semicolon());
                                                                  }
                                                                  increaseIndent();
                                                                  print(rightBrace());
                                                                  decreaseIndent();
                                                                  if (useGlr && tree)
                                                                  {
                                                            #line 7237 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if ");
                                                            #line 4308 "PrintCLike.cpp.template"
                                                                    print(ifLeftParen());
                                                            #line 7242 "PrintCLike.cpp"
  append(L"nonterminalId == ");
                                                            #line 4309 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7246 "PrintCLike.cpp"
  append(L"target ");
                                                            #line 4310 "PrintCLike.cpp.template"
                                                                    if (isPython())
                                                                    {
                                                            #line 7251 "PrintCLike.cpp"
  append(L"and");
                                                            #line 4312 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 7257 "PrintCLike.cpp"
  append(L"&&");
                                                            #line 4315 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 7261 "PrintCLike.cpp"
  append(L" ");
                                                            #line 4316 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7265 "PrintCLike.cpp"
  append(L"stack");
                                                            #line 4317 "PrintCLike.cpp.template"
                                                                    print(arrow());
                                                            #line 7269 "PrintCLike.cpp"
  append(L"link == ");
                                                            #line 4318 "PrintCLike.cpp.template"
                                                                    print(nullPtr());
                                                                    print(ifRightParen());
                                                                    printIndented(1, leftBrace());
                                                            #line 7275 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4322 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7280 "PrintCLike.cpp"
  append(L"bs = ");
                                                            #line 4323 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7284 "PrintCLike.cpp"
  append(L"bw");
                                                            #line 4324 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 7288 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4326 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7293 "PrintCLike.cpp"
  append(L"bw = ");
                                                            #line 4327 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7297 "PrintCLike.cpp"
  append(L"b1");
                                                            #line 4328 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                    increaseIndent();
                                                                    print(rightBrace());
                                                                    decreaseIndent();
                                                                  }
                                                                }
                                                            #line 7306 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4335 "PrintCLike.cpp.template"
                                                                if (useGlr) print(thiz());
                                                            #line 7311 "PrintCLike.cpp"
  append(L"action = ");
                                                            #line 4336 "PrintCLike.cpp.template"
                                                                print(staticPrefix());
                                                                print(isGo() ? L"reduceAction" : L"goTo");
                                                            #line 7316 "PrintCLike.cpp"
  append(L"(nonterminalId, ");
                                                            #line 4338 "PrintCLike.cpp.template"
                                                                if (useGlr) print(thiz());
                                                            #line 7320 "PrintCLike.cpp"
  append(L"state)");
                                                            #line 4339 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                print(rightBrace());
                                                                decreaseIndent();
                                                                print(rightBrace());
                                                                decreaseIndent();
                                                                if (useGlr)
                                                                {
                                                                  if (isScala())
                                                                  {
                                                            #line 7332 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ERROR");
                                                            #line 4349 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isCpp())
                                                                  {
                                                            #line 7339 "PrintCLike.cpp"
  append(L"\n");
  append(L"  return PARSING;");
                                                            #line 4353 "PrintCLike.cpp.template"
                                                                  }
                                                                }
                                                                print(rightBrace());
                                                                if (isJavascript() && useGlr)
                                                                {
                                                            #line 7348 "PrintCLike.cpp"
  append(L";");
                                                            #line 4358 "PrintCLike.cpp.template"
                                                                }
                                                            #line 7352 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4360 "PrintCLike.cpp.template"
                                                                if ((tree || hasCustomCode) && useGlr)
                                                                {
                                                                  openMethod(boolType(), L"", L"isUnambiguous", L"", false, L"ParsingThread");
                                                                  print(leftBrace());
                                                            #line 7359 "PrintCLike.cpp"
  append(L"\n");
  append(L"  return ");
                                                            #line 4365 "PrintCLike.cpp.template"
                                                                  if (isPython())
                                                                  {
                                                            #line 7365 "PrintCLike.cpp"
  append(L"len(self.threads) == 0");
                                                            #line 4367 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                                    print(thiz());
                                                            #line 7372 "PrintCLike.cpp"
  append(L"threads");
                                                            #line 4371 "PrintCLike.cpp.template"
                                                                    print(arrow());
                                                                    if (isCpp())
                                                                    {
                                                            #line 7378 "PrintCLike.cpp"
  append(L"empty();");
                                                            #line 4374 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 7384 "PrintCLike.cpp"
  append(L"isEmpty");
                                                            #line 4377 "PrintCLike.cpp.template"
                                                                      if (! isScala()) print(L"()");
                                                                      print(semicolon());
                                                                    }
                                                                  }
                                                                  print(rightBrace());
                                                            #line 7392 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4383 "PrintCLike.cpp.template"
                                                                }
                                                                if (hasCustomCode)
                                                                {
                                                                  if (useGlr)
                                                                  {
                                                                    if (isJavascript())
                                                                    {
                                                            #line 7402 "PrintCLike.cpp"
  append(L"\n");
  append(L"this.executeDeferredCode = function()\n");
                                                            #line 4392 "PrintCLike.cpp.template"
                                                                    }
                                                                    else if (isTypescript())
                                                                    {
                                                            #line 7409 "PrintCLike.cpp"
  append(L"\n");
  append(L"executeDeferredCode()\n");
                                                            #line 4397 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                                      openMethod(voidType(), L"", L"executeDeferredCode", L"", false, L"ParsingThread");
                                                                    }
                                                                    print(leftBrace());
                                                                    increaseIndent();
                                                            #line 7420 "PrintCLike.cpp"
  append(L"\n");
  append(L"if ");
                                                            #line 4405 "PrintCLike.cpp.template"
                                                                    print(ifLeftParen());
                                                                    print(thiz());
                                                            #line 7426 "PrintCLike.cpp"
  append(L"deferredCode != ");
                                                            #line 4407 "PrintCLike.cpp.template"
                                                                    print(nullPtr());
                                                                    print(ifRightParen());
                                                                    print(leftBrace());
                                                                    increaseIndent();
                                                            #line 7433 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4412 "PrintCLike.cpp.template"
                                                                    if (isJavascript() || isHaxe() || isScala() || isTypescript())
                                                                    {
                                                            #line 7438 "PrintCLike.cpp"
  append(L"var ");
                                                            #line 4414 "PrintCLike.cpp.template"
                                                                    }
                                                                    else if (! isGo() && ! isPython())
                                                                    {
                                                            #line 7444 "PrintCLike.cpp"
  append(L"DeferredCode ");
                                                            #line 4417 "PrintCLike.cpp.template"
                                                                    }
                                                                    if (isCpp()) print(L"*");
                                                            #line 7449 "PrintCLike.cpp"
  append(L"predecessor");
                                                            #line 4419 "PrintCLike.cpp.template"
                                                                    print(assign());
                                                                    print(thiz());
                                                            #line 7454 "PrintCLike.cpp"
  append(L"deferredCode");
                                                            #line 4421 "PrintCLike.cpp.template"
                                                                    print(arrow());
                                                            #line 7458 "PrintCLike.cpp"
  append(L"link");
                                                            #line 4422 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 7462 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4424 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7466 "PrintCLike.cpp"
  append(L"deferredCode");
                                                            #line 4425 "PrintCLike.cpp.template"
                                                                    print(arrow());
                                                            #line 7470 "PrintCLike.cpp"
  append(L"link = ");
                                                            #line 4426 "PrintCLike.cpp.template"
                                                                    print(nullPtr());
                                                                    print(semicolon());
                                                                    if (isGo())
                                                                    {
                                                            #line 7477 "PrintCLike.cpp"
  append(L"\n");
  append(L"for ");
                                                            #line 4431 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 7484 "PrintCLike.cpp"
  append(L"\n");
  append(L"while ");
                                                            #line 4435 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(ifLeftParen());
                                                            #line 7490 "PrintCLike.cpp"
  append(L"predecessor != ");
                                                            #line 4437 "PrintCLike.cpp.template"
                                                                    print(nullPtr());
                                                                    print(ifRightParen());
                                                                    print(leftBrace());
                                                            #line 7496 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4441 "PrintCLike.cpp.template"
                                                                    if (isJavascript() || isHaxe() || isScala() || isTypescript())
                                                                    {
                                                            #line 7502 "PrintCLike.cpp"
  append(L"var ");
                                                            #line 4443 "PrintCLike.cpp.template"
                                                                    }
                                                                    else if (! isGo() && ! isPython())
                                                                    {
                                                            #line 7508 "PrintCLike.cpp"
  append(L"DeferredCode ");
                                                            #line 4446 "PrintCLike.cpp.template"
                                                                    }
                                                                    if (isCpp()) print(L"*");
                                                            #line 7513 "PrintCLike.cpp"
  append(L"nextCode");
                                                            #line 4448 "PrintCLike.cpp.template"
                                                                    print(assign());
                                                            #line 7517 "PrintCLike.cpp"
  append(L"predecessor");
                                                            #line 4449 "PrintCLike.cpp.template"
                                                                    print(arrow());
                                                            #line 7521 "PrintCLike.cpp"
  append(L"link");
                                                            #line 4450 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 7525 "PrintCLike.cpp"
  append(L"\n");
  append(L"  predecessor");
                                                            #line 4452 "PrintCLike.cpp.template"
                                                                    print(arrow());
                                                            #line 7530 "PrintCLike.cpp"
  append(L"link = ");
                                                            #line 4453 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7534 "PrintCLike.cpp"
  append(L"deferredCode");
                                                            #line 4454 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 7538 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4456 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7543 "PrintCLike.cpp"
  append(L"deferredCode = predecessor");
                                                            #line 4457 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 7547 "PrintCLike.cpp"
  append(L"\n");
  append(L"  predecessor = nextCode");
                                                            #line 4459 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                    print(rightBrace());
                                                            #line 7553 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4462 "PrintCLike.cpp.template"
                                                                    print(intVar());
                                                            #line 7557 "PrintCLike.cpp"
  append(L"b0t");
                                                            #line 4463 "PrintCLike.cpp.template"
                                                                    print(assign());
                                                                    print(thiz());
                                                            #line 7562 "PrintCLike.cpp"
  append(L"b0");
                                                            #line 4465 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 7566 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4467 "PrintCLike.cpp.template"
                                                                    print(intVar());
                                                            #line 7570 "PrintCLike.cpp"
  append(L"e0t");
                                                            #line 4468 "PrintCLike.cpp.template"
                                                                    print(assign());
                                                                    print(thiz());
                                                            #line 7575 "PrintCLike.cpp"
  append(L"e0");
                                                            #line 4470 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                    if (isGo())
                                                                    {
                                                            #line 7581 "PrintCLike.cpp"
  append(L"\n");
  append(L"for ");
                                                            #line 4474 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 7588 "PrintCLike.cpp"
  append(L"\n");
  append(L"while ");
                                                            #line 4478 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(ifLeftParen());
                                                                    print(thiz());
                                                            #line 7595 "PrintCLike.cpp"
  append(L"deferredCode != ");
                                                            #line 4481 "PrintCLike.cpp.template"
                                                                    print(nullPtr());
                                                                    print(ifRightParen());
                                                                    print(leftBrace());
                                                            #line 7601 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4485 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7606 "PrintCLike.cpp"
  append(L"b0 = ");
                                                            #line 4486 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7610 "PrintCLike.cpp"
  append(L"deferredCode");
                                                            #line 4487 "PrintCLike.cpp.template"
                                                                    print(arrow());
                                                            #line 7614 "PrintCLike.cpp"
  append(L"b0");
                                                            #line 4488 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 7618 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4490 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7623 "PrintCLike.cpp"
  append(L"e0 = ");
                                                            #line 4491 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7627 "PrintCLike.cpp"
  append(L"deferredCode");
                                                            #line 4492 "PrintCLike.cpp.template"
                                                                    print(arrow());
                                                            #line 7631 "PrintCLike.cpp"
  append(L"e0");
                                                            #line 4493 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 7635 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4495 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                                    print(isGo() ? L"E" : L"e");
                                                            #line 7641 "PrintCLike.cpp"
  append(L"xecute(");
                                                            #line 4497 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7645 "PrintCLike.cpp"
  append(L"deferredCode");
                                                            #line 4498 "PrintCLike.cpp.template"
                                                                    print(arrow());
                                                            #line 7649 "PrintCLike.cpp"
  append(L"codeId)");
                                                            #line 4499 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                    if (isCpp())
                                                                    {
                                                            #line 7655 "PrintCLike.cpp"
  append(L"\n");
  append(L"  DeferredCode *next = deferredCode->link;\n");
  append(L"  delete deferredCode;\n");
  append(L"  deferredCode = next;");
                                                            #line 4505 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 7664 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4509 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 7669 "PrintCLike.cpp"
  append(L"deferredCode = ");
                                                            #line 4510 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 7673 "PrintCLike.cpp"
  append(L"deferredCode");
                                                            #line 4511 "PrintCLike.cpp.template"
                                                                      print(arrow());
                                                            #line 7677 "PrintCLike.cpp"
  append(L"link");
                                                            #line 4512 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                                    }
                                                                    print(rightBrace());
                                                            #line 7683 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4516 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7687 "PrintCLike.cpp"
  append(L"b0 = b0t");
                                                            #line 4517 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 7691 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4519 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7695 "PrintCLike.cpp"
  append(L"e0 = e0t");
                                                            #line 4520 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                    decreaseIndent();
                                                                    print(rightBrace());
                                                                    decreaseIndent();
                                                                    print(rightBrace());
                                                            #line 7703 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4526 "PrintCLike.cpp.template"
                                                                  }
                                                                  openMethod(voidType(), L"", L"execute", L"int reduce", false, useGlr ? L"ParsingThread" : className.c_str());
                                                                  print(leftBrace());
                                                                  increaseIndent();
                                                                  if (! isPython())
                                                                  {
                                                            #line 7712 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4533 "PrintCLike.cpp.template"
                                                                    if (! isScala())
                                                                    {
                                                            #line 7717 "PrintCLike.cpp"
  append(L"switch ");
                                                            #line 4535 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(ifLeftParen());
                                                            #line 7722 "PrintCLike.cpp"
  append(L"reduce");
                                                            #line 4537 "PrintCLike.cpp.template"
                                                                    print(ifRightParen());
                                                                    if (isScala())
                                                                    {
                                                            #line 7728 "PrintCLike.cpp"
  append(L" match");
                                                            #line 4540 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(leftBrace());
                                                                  }
                                                                  int lastContentId = grammar->distinctCodeAnnotations.size() - 1;
                                                                  for (int contentId = 0; contentId <= lastContentId; ++contentId)
                                                                  {
                                                                    ProcessingInstruction *p = grammar->distinctCodeAnnotations[contentId];
                                                                    if (! isPython())
                                                                    {
                                                            #line 7740 "PrintCLike.cpp"
  append(L"\n");
  append(L"case ");
                                                            #line 4550 "PrintCLike.cpp.template"
                                                                    }
                                                                    else if (contentId == 0)
                                                                    {
                                                            #line 7747 "PrintCLike.cpp"
  append(L"\n");
  append(L"if reduce == ");
                                                            #line 4554 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 7754 "PrintCLike.cpp"
  append(L"\n");
  append(L"elif reduce == ");
                                                            #line 4558 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(format.toString<wchar_t>(contentId));
                                                                    print(caseIntroducer());
                                                                    increaseIndent();
                                                                    print(leftBrace());
                                                                    visitProcessingInstruction(p);
                                                                    print(rightBrace());
                                                                    if (! isScala() && ! isHaxe() && ! isGo() && ! isPython())
                                                                    {
                                                            #line 7767 "PrintCLike.cpp"
  append(L"\n");
  append(L"break");
                                                            #line 4568 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                                    }
                                                                    decreaseIndent();
                                                                  }
                                                                  if (isScala())
                                                                  {
                                                            #line 7777 "PrintCLike.cpp"
  append(L"\n");
  append(L"case _");
                                                            #line 4575 "PrintCLike.cpp.template"
                                                                    print(caseIntroducer());
                                                                  }
                                                                  else if (! isPython())
                                                                  {
                                                            #line 7785 "PrintCLike.cpp"
  append(L"\n");
  append(L"default");
                                                            #line 4580 "PrintCLike.cpp.template"
                                                                    print(caseIntroducer());
                                                                  }
                                                                  if (! isScala() && ! isHaxe() && ! isGo() && ! isPython())
                                                                  {
                                                            #line 7793 "PrintCLike.cpp"
  append(L"\n");
  append(L"  break");
                                                            #line 4585 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                  }
                                                                  print(rightBrace());
                                                                  decreaseIndent();
                                                                  print(rightBrace());
                                                            #line 7802 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4591 "PrintCLike.cpp.template"
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
                                                            #line 7828 "PrintCLike.cpp"
  append(L"\n");
  append(L"if ");
                                                            #line 4615 "PrintCLike.cpp.template"
                                                                print(ifLeftParen());
                                                                print(thiz());
                                                            #line 7834 "PrintCLike.cpp"
  append(L"l1 == t");
                                                            #line 4617 "PrintCLike.cpp.template"
                                                                print(ifRightParen());
                                                                print(leftBrace());
                                                                increaseIndent();
                                                                if (tree && i == 0 && ! isLrParser)
                                                                {
                                                                  if (anyWhitespace && ! isLrParser)
                                                                  {
                                                            #line 7844 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4625 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7848 "PrintCLike.cpp"
  append(L"whitespace");
                                                            #line 4626 "PrintCLike.cpp.template"
                                                                    print(isScala() ? L"" : L"()");
                                                                    print(semicolon());
                                                                  }
                                                            #line 7854 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4631 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 7858 "PrintCLike.cpp"
  append(L"eventHandler");
                                                            #line 4632 "PrintCLike.cpp.template"
                                                                  print(arrow());
                                                                  if (isGo())
                                                                  {
                                                            #line 7864 "PrintCLike.cpp"
  append(L"T");
                                                            #line 4635 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 7870 "PrintCLike.cpp"
  append(L"t");
                                                            #line 4638 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 7874 "PrintCLike.cpp"
  append(L"erminal(");
                                                            #line 4639 "PrintCLike.cpp.template"
                                                                  if (isJava() || isCSharp())
                                                                  {
                                                                    print(staticPrefix());
                                                            #line 7880 "PrintCLike.cpp"
  append(L"TOKEN[");
                                                            #line 4642 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7884 "PrintCLike.cpp"
  append(L"l1]");
                                                            #line 4643 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isTypescript())
                                                                  {
                                                                    print(staticPrefix());
                                                            #line 7891 "PrintCLike.cpp"
  append(L"TOKEN[");
                                                            #line 4647 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7895 "PrintCLike.cpp"
  append(L"l1]");
                                                            #line 4648 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isJavascript() || isHaxe())
                                                                  {
                                                                    print(staticPrefix());
                                                            #line 7902 "PrintCLike.cpp"
  append(L"TOKEN[");
                                                            #line 4652 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7906 "PrintCLike.cpp"
  append(L"l1]");
                                                            #line 4653 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isScala())
                                                                  {
                                                                    print(staticPrefix());
                                                            #line 7913 "PrintCLike.cpp"
  append(L"TOKEN(l1)");
                                                            #line 4657 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isGo())
                                                                  {
                                                            #line 7919 "PrintCLike.cpp"
  append(L"token[this.l1]");
                                                            #line 4660 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                                    print(staticPrefix());
                                                            #line 7926 "PrintCLike.cpp"
  append(L"TOKEN[");
                                                            #line 4664 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7930 "PrintCLike.cpp"
  append(L"l1]");
                                                            #line 4665 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 7934 "PrintCLike.cpp"
  append(L", ");
                                                            #line 4666 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 7938 "PrintCLike.cpp"
  append(L"b1, ");
                                                            #line 4667 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 7942 "PrintCLike.cpp"
  append(L"e1)");
                                                            #line 4668 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                            #line 7947 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4671 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 7951 "PrintCLike.cpp"
  append(L"b0 = ");
                                                            #line 4672 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 7955 "PrintCLike.cpp"
  append(L"b1; ");
                                                            #line 4673 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 7959 "PrintCLike.cpp"
  append(L"e0 = ");
                                                            #line 4674 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 7963 "PrintCLike.cpp"
  append(L"e1;");
                                                            #line 4675 "PrintCLike.cpp.template"
                                                                for (size_t k = 1; k < grammar->k; ++k)
                                                                {
                                                            #line 7968 "PrintCLike.cpp"
  append(L" ");
                                                            #line 4677 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 7972 "PrintCLike.cpp"
  append(L"l");
                                                            #line 4678 "PrintCLike.cpp.template"
                                                                  print(format.toString<wchar_t>(k));
                                                            #line 7976 "PrintCLike.cpp"
  append(L" = ");
                                                            #line 4679 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 7980 "PrintCLike.cpp"
  append(L"l");
                                                            #line 4680 "PrintCLike.cpp.template"
                                                                  print(format.toString<wchar_t>(k + 1));
                                                                  print(isPython() ? L"\n" : L"; ");
                                                            #line 7985 "PrintCLike.cpp"
  append(L"if ");
                                                            #line 4682 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                                  print(thiz());
                                                            #line 7990 "PrintCLike.cpp"
  append(L"l");
                                                            #line 4684 "PrintCLike.cpp.template"
                                                                  print(format.toString<wchar_t>(k));
                                                            #line 7994 "PrintCLike.cpp"
  append(L" != 0");
                                                            #line 4685 "PrintCLike.cpp.template"
                                                                  print(ifRightParen());
                                                                  if (isPython())
                                                                  {
                                                                    increaseIndent();
                                                                  }
                                                                  else
                                                                  {
                                                            #line 8004 "PrintCLike.cpp"
  append(L" {");
                                                            #line 4692 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 8008 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4694 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8012 "PrintCLike.cpp"
  append(L"b");
                                                            #line 4695 "PrintCLike.cpp.template"
                                                                  print(format.toString<wchar_t>(k));
                                                            #line 8016 "PrintCLike.cpp"
  append(L" = ");
                                                            #line 4696 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8020 "PrintCLike.cpp"
  append(L"b");
                                                            #line 4697 "PrintCLike.cpp.template"
                                                                  print(format.toString<wchar_t>(k + 1));
                                                            #line 8024 "PrintCLike.cpp"
  append(L"; ");
                                                            #line 4698 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8028 "PrintCLike.cpp"
  append(L"e");
                                                            #line 4699 "PrintCLike.cpp.template"
                                                                  print(format.toString<wchar_t>(k));
                                                            #line 8032 "PrintCLike.cpp"
  append(L" = ");
                                                            #line 4700 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8036 "PrintCLike.cpp"
  append(L"e");
                                                            #line 4701 "PrintCLike.cpp.template"
                                                                  print(format.toString<wchar_t>(k + 1));
                                                            #line 8040 "PrintCLike.cpp"
  append(L";");
                                                            #line 4702 "PrintCLike.cpp.template"
                                                                }
                                                            #line 8044 "PrintCLike.cpp"
  append(L" ");
                                                            #line 4703 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 8048 "PrintCLike.cpp"
  append(L"l");
                                                            #line 4704 "PrintCLike.cpp.template"
                                                                print(format.toString<wchar_t>(grammar->k));
                                                            #line 8052 "PrintCLike.cpp"
  append(L" = 0");
                                                            #line 4705 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                if (grammar->k > 1)
                                                                {
                                                            #line 8058 "PrintCLike.cpp"
  append(L" ");
                                                            #line 4708 "PrintCLike.cpp.template"
                                                                  for (size_t k = 1; k < grammar->k; ++k)
                                                                  {
                                                                    if (! isPython())
                                                                    {
                                                            #line 8065 "PrintCLike.cpp"
  append(L"}");
                                                            #line 4712 "PrintCLike.cpp.template"
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
                                                            #line 8080 "PrintCLike.cpp"
  append(L"\n");
  append(L"  fprintf(stderr, \"  <parse terminal=\\\"%s\\\"%s%s%s/>\\n\", ");
                                                            #line 4725 "PrintCLike.cpp.template"
                                                                    if (stringIntroducer()[0])
                                                                    {
                                                            #line 8086 "PrintCLike.cpp"
  append(L"Utf8Encoder::encode(");
                                                            #line 4728 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 8090 "PrintCLike.cpp"
  append(L"xmlEscape(TOKEN[t], 0).c_str()");
                                                            #line 4730 "PrintCLike.cpp.template"
                                                                    if (stringIntroducer()[0])
                                                                    {
                                                            #line 8095 "PrintCLike.cpp"
  append(L").c_str()");
                                                            #line 4732 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 8099 "PrintCLike.cpp"
  append(L", (l1 == 0 ? \"\" : \" input=\\\"\"),  (l1 == 0 ? \"\" : ");
                                                            #line 4734 "PrintCLike.cpp.template"
                                                                    if (stringIntroducer()[0])
                                                                    {
                                                            #line 8104 "PrintCLike.cpp"
  append(L"Utf8Encoder::encode(");
                                                            #line 4737 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 8108 "PrintCLike.cpp"
  append(L"xmlEscape(lookaheadString().c_str(), 0).c_str()");
                                                            #line 4739 "PrintCLike.cpp.template"
                                                                    if (stringIntroducer()[0])
                                                                    {
                                                            #line 8113 "PrintCLike.cpp"
  append(L").c_str()");
                                                            #line 4741 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 8117 "PrintCLike.cpp"
  append(L"), (l1 == 0 ? \"\" : \"\\\"\"));");
                                                            #line 4743 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                                    if (isGo())
                                                                    {
                                                            #line 8125 "PrintCLike.cpp"
  append(L"\n");
  append(L"  var inputAttr string\n");
  append(L"  if (this.l1 == 0) {\n");
  append(L"    inputAttr = \"\"\n");
  append(L"  } else {\n");
  append(L"    inputAttr = \" input=\\\"\" + xmlEscape(this.lookaheadString()) + \"\\\"\"\n");
  append(L"  }");
                                                            #line 4754 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 8135 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4756 "PrintCLike.cpp.template"
                                                                    if (isHaxe())
                                                                    {
                                                            #line 8141 "PrintCLike.cpp"
  append(L"trace(");
                                                            #line 4759 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                                      print(writeTrace());
                                                                    }
                                                            #line 8149 "PrintCLike.cpp"
  append(L"\"  <parse terminal=\\\"\" + ");
                                                            #line 4764 "PrintCLike.cpp.template"
                                                                    print(staticPrefix());
                                                            #line 8153 "PrintCLike.cpp"
  append(L"xmlEscape(");
                                                            #line 4765 "PrintCLike.cpp.template"
                                                                    print(staticPrefix());
                                                                    print(isGo() ? L"token" : L"TOKEN");
                                                                    print(leftbracket());
                                                            #line 8159 "PrintCLike.cpp"
  append(L"t");
                                                            #line 4768 "PrintCLike.cpp.template"
                                                                    print(rightbracket());
                                                            #line 8163 "PrintCLike.cpp"
  append(L") + \"\\\"\" + ");
                                                            #line 4769 "PrintCLike.cpp.template"
                                                                    if (isGo())
                                                                    {
                                                            #line 8168 "PrintCLike.cpp"
  append(L"inputAttr");
                                                            #line 4771 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 8174 "PrintCLike.cpp"
  append(L"(");
                                                            #line 4774 "PrintCLike.cpp.template"
                                                                      if (isScala())
                                                                      {
                                                            #line 8179 "PrintCLike.cpp"
  append(L"if (l1 == 0) \"\" else");
                                                            #line 4776 "PrintCLike.cpp.template"
                                                                      }
                                                                      else if (isPython())
                                                                      {
                                                            #line 8185 "PrintCLike.cpp"
  append(L"\"\" if self.l1 == 0 else");
                                                            #line 4779 "PrintCLike.cpp.template"
                                                                      }
                                                                      else
                                                                      {
                                                                        print(thiz());
                                                            #line 8192 "PrintCLike.cpp"
  append(L"l1 == 0 ? \"\" :");
                                                            #line 4783 "PrintCLike.cpp.template"
                                                                      }
                                                            #line 8196 "PrintCLike.cpp"
  append(L" \" input=\\\"\" + ");
                                                            #line 4784 "PrintCLike.cpp.template"
                                                                      print(staticPrefix());
                                                            #line 8200 "PrintCLike.cpp"
  append(L"xmlEscape(");
                                                            #line 4785 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 8204 "PrintCLike.cpp"
  append(L"lookaheadString");
                                                            #line 4786 "PrintCLike.cpp.template"
                                                                      if (! isScala()) print(L"()");
                                                            #line 8208 "PrintCLike.cpp"
  append(L") + \"\\\"\")");
                                                            #line 4787 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 8212 "PrintCLike.cpp"
  append(L" + \"/>");
                                                            #line 4788 "PrintCLike.cpp.template"
                                                                    if (isHaxe())
                                                                    {
                                                            #line 8217 "PrintCLike.cpp"
  append(L"\")");
                                                            #line 4790 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 8223 "PrintCLike.cpp"
  append(L"\\n\"");
                                                            #line 4793 "PrintCLike.cpp.template"
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
                                                            #line 8237 "PrintCLike.cpp"
  append(L"el");
                                                            #line 4804 "PrintCLike.cpp.template"
                                                                    if (! isPython())
                                                                    {
                                                            #line 8242 "PrintCLike.cpp"
  append(L"se ");
                                                            #line 4806 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 8246 "PrintCLike.cpp"
  append(L"if ");
                                                            #line 4807 "PrintCLike.cpp.template"
                                                                    print(ifLeftParen());
                                                                    print(thiz());
                                                                    print(token());
                                                            #line 8252 "PrintCLike.cpp"
  append(L" < 0");
                                                            #line 4810 "PrintCLike.cpp.template"
                                                                    print(ifRightParen());
                                                                    print(leftBrace());
                                                            #line 8257 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4813 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8262 "PrintCLike.cpp"
  append(L"error(");
                                                            #line 4814 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8266 "PrintCLike.cpp"
  append(L"b1, ");
                                                            #line 4815 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8270 "PrintCLike.cpp"
  append(L"e1, -");
                                                            #line 4816 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8274 "PrintCLike.cpp"
  append(L"l1, 0, 0)");
                                                            #line 4817 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                    if (i == 0)
                                                                    {
                                                            #line 8280 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4821 "PrintCLike.cpp.template"
                                                                      print(beginThrowStmt());
                                                                      print(thiz());
                                                            #line 8286 "PrintCLike.cpp"
  append(L"bx, ");
                                                            #line 4823 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 8290 "PrintCLike.cpp"
  append(L"ex, ");
                                                            #line 4824 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 8294 "PrintCLike.cpp"
  append(L"sx, ");
                                                            #line 4825 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 8298 "PrintCLike.cpp"
  append(L"lx, ");
                                                            #line 4826 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 8302 "PrintCLike.cpp"
  append(L"tx");
                                                            #line 4827 "PrintCLike.cpp.template"
                                                                      print(endThrowStmt());
                                                                      print(semicolon());
                                                                    }
                                                                    print(rightBrace());
                                                                  }
                                                                  print(isGo() ? L" " : L"\n");
                                                            #line 8311 "PrintCLike.cpp"
  append(L"else");
                                                            #line 4833 "PrintCLike.cpp.template"
                                                                  if (isPython()) print(L":");
                                                                  print(leftBrace());
                                                            #line 8316 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4836 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8321 "PrintCLike.cpp"
  append(L"error(");
                                                            #line 4837 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8325 "PrintCLike.cpp"
  append(L"b1, ");
                                                            #line 4838 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8329 "PrintCLike.cpp"
  append(L"e1, 0, ");
                                                            #line 4839 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8333 "PrintCLike.cpp"
  append(L"l1, t)");
                                                            #line 4840 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                  if (i == 0 && grammar->noThrow)
                                                                  {
                                                            #line 8339 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4844 "PrintCLike.cpp.template"
                                                                    print(beginThrowStmt());
                                                                    print(thiz());
                                                            #line 8345 "PrintCLike.cpp"
  append(L"bx, ");
                                                            #line 4846 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8349 "PrintCLike.cpp"
  append(L"ex, ");
                                                            #line 4847 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8353 "PrintCLike.cpp"
  append(L"sx, ");
                                                            #line 4848 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8357 "PrintCLike.cpp"
  append(L"lx, ");
                                                            #line 4849 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8361 "PrintCLike.cpp"
  append(L"tx");
                                                            #line 4850 "PrintCLike.cpp.template"
                                                                    print(endThrowStmt());
                                                                    print(semicolon());
                                                                  }
                                                                  print(rightBrace());
                                                                }
                                                                else
                                                                {
                                                                  print(isGo() ? L" " : L"\n");
                                                            #line 8372 "PrintCLike.cpp"
  append(L"else");
                                                            #line 4858 "PrintCLike.cpp.template"
                                                                  if (isPython()) print(L":");
                                                                  print(leftBrace());
                                                            #line 8377 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4861 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8382 "PrintCLike.cpp"
  append(L"error(");
                                                            #line 4862 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8386 "PrintCLike.cpp"
  append(L"b1, ");
                                                            #line 4863 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8390 "PrintCLike.cpp"
  append(L"e1, 0, ");
                                                            #line 4864 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8394 "PrintCLike.cpp"
  append(L"l1, t)");
                                                            #line 4865 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                  print(rightBrace());
                                                                }
                                                                decreaseIndent();
                                                                print(rightBrace());
                                                            #line 8402 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4871 "PrintCLike.cpp.template"
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
                                                            #line 8421 "PrintCLike.cpp"
  append(L"\n");
  append(L"  var thread = new ParsingThread().copy(thisThread, 0);\n");
  append(L"  thread.setL1(code);\n");
  append(L"  thread.setB1(begin);\n");
  append(L"  thread.setE1(end);");
                                                            #line 4891 "PrintCLike.cpp.template"
                                                                    }
                                                                    else if (isGo())
                                                                    {
                                                            #line 8431 "PrintCLike.cpp"
  append(L"\n");
  append(L"  thread := new(ParsingThread).copy(this, 0)\n");
  append(L"  thread.l1 = code\n");
  append(L"  thread.b1 = this.begin\n");
  append(L"  thread.e1 = this.end");
                                                            #line 4898 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 8441 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4902 "PrintCLike.cpp.template"
                                                                      if (isHaxe() || isScala() || isTypescript())
                                                                      {
                                                            #line 8447 "PrintCLike.cpp"
  append(L"var ");
                                                            #line 4904 "PrintCLike.cpp.template"
                                                                      }
                                                                      else if (! isPython())
                                                                      {
                                                            #line 8453 "PrintCLike.cpp"
  append(L"ParsingThread ");
                                                            #line 4907 "PrintCLike.cpp.template"
                                                                      }
                                                                      if (isCpp()) print(L"*");
                                                            #line 8458 "PrintCLike.cpp"
  append(L"thread = ");
                                                            #line 4909 "PrintCLike.cpp.template"
                                                                      if (isCpp()) print(L"(");
                                                                      if (! isPython())
                                                                      {
                                                            #line 8464 "PrintCLike.cpp"
  append(L"new ");
                                                            #line 4912 "PrintCLike.cpp.template"
                                                                      }
                                                                      if (isScala() || isPython())
                                                                      {
                                                                        print(className.c_str());
                                                            #line 8471 "PrintCLike.cpp"
  append(L".");
                                                            #line 4916 "PrintCLike.cpp.template"
                                                                      }
                                                            #line 8475 "PrintCLike.cpp"
  append(L"ParsingThread()");
                                                            #line 4917 "PrintCLike.cpp.template"
                                                                      if (isCpp()) print(L")");
                                                                      print(arrow());
                                                            #line 8480 "PrintCLike.cpp"
  append(L"copy(");
                                                            #line 4919 "PrintCLike.cpp.template"
                                                                      if (isPython())
                                                                      {
                                                            #line 8485 "PrintCLike.cpp"
  append(L"self");
                                                            #line 4921 "PrintCLike.cpp.template"
                                                                      }
                                                                      else
                                                                      {
                                                            #line 8491 "PrintCLike.cpp"
  append(L"this");
                                                            #line 4924 "PrintCLike.cpp.template"
                                                                      }
                                                            #line 8495 "PrintCLike.cpp"
  append(L", 0)");
                                                            #line 4925 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                                      if (isCpp())
                                                                      {
                                                            #line 8501 "PrintCLike.cpp"
  append(L"\n");
  append(L"  thread->stack->unshare();\n");
  append(L"  thread->stack = 0;");
                                                            #line 4930 "PrintCLike.cpp.template"
                                                                      }
                                                            #line 8507 "PrintCLike.cpp"
  append(L"\n");
  append(L"  thread");
                                                            #line 4932 "PrintCLike.cpp.template"
                                                                      print(arrow());
                                                            #line 8512 "PrintCLike.cpp"
  append(L"l1 = code");
                                                            #line 4933 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                            #line 8516 "PrintCLike.cpp"
  append(L"\n");
  append(L"  thread");
                                                            #line 4935 "PrintCLike.cpp.template"
                                                                      print(arrow());
                                                            #line 8521 "PrintCLike.cpp"
  append(L"b1 = ");
                                                            #line 4936 "PrintCLike.cpp.template"
                                                                      if (useGlr) print(thiz());
                                                            #line 8525 "PrintCLike.cpp"
  append(L"begin");
                                                            #line 4937 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                            #line 8529 "PrintCLike.cpp"
  append(L"\n");
  append(L"  thread");
                                                            #line 4939 "PrintCLike.cpp.template"
                                                                      print(arrow());
                                                            #line 8534 "PrintCLike.cpp"
  append(L"e1 = ");
                                                            #line 4940 "PrintCLike.cpp.template"
                                                                      if (useGlr) print(thiz());
                                                            #line 8538 "PrintCLike.cpp"
  append(L"end");
                                                            #line 4941 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                                    }
                                                                  }
                                                                  else
                                                                  {
                                                            #line 8546 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4947 "PrintCLike.cpp.template"
                                                                    print(intVal());
                                                            #line 8551 "PrintCLike.cpp"
  append(L"b0W");
                                                            #line 4948 "PrintCLike.cpp.template"
                                                                    print(assign());
                                                                    print(thiz());
                                                            #line 8556 "PrintCLike.cpp"
  append(L"b0; ");
                                                            #line 4950 "PrintCLike.cpp.template"
                                                                    print(intVal());
                                                            #line 8560 "PrintCLike.cpp"
  append(L"e0W");
                                                            #line 4951 "PrintCLike.cpp.template"
                                                                    print(assign());
                                                                    print(thiz());
                                                            #line 8565 "PrintCLike.cpp"
  append(L"e0");
                                                            #line 4954 "PrintCLike.cpp.template"
                                                                    for (size_t k = 1; k < grammar->k; ++k)
                                                                    {
                                                            #line 8570 "PrintCLike.cpp"
  append(L"; ");
                                                            #line 4956 "PrintCLike.cpp.template"
                                                                      print(intVal());
                                                            #line 8574 "PrintCLike.cpp"
  append(L"l");
                                                            #line 4957 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(k));
                                                            #line 8578 "PrintCLike.cpp"
  append(L"W");
                                                            #line 4958 "PrintCLike.cpp.template"
                                                                      print(assign());
                                                                      print(thiz());
                                                            #line 8583 "PrintCLike.cpp"
  append(L"l");
                                                            #line 4960 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(k));
                                                                      print(semicolon());
                                                            #line 8588 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4963 "PrintCLike.cpp.template"
                                                                      print(intVal());
                                                            #line 8593 "PrintCLike.cpp"
  append(L"b");
                                                            #line 4964 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(k));
                                                            #line 8597 "PrintCLike.cpp"
  append(L"W");
                                                            #line 4965 "PrintCLike.cpp.template"
                                                                      print(assign());
                                                                      print(thiz());
                                                            #line 8602 "PrintCLike.cpp"
  append(L"b");
                                                            #line 4967 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(k));
                                                            #line 8606 "PrintCLike.cpp"
  append(L"; ");
                                                            #line 4968 "PrintCLike.cpp.template"
                                                                      print(intVal());
                                                            #line 8610 "PrintCLike.cpp"
  append(L"e");
                                                            #line 4969 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(k));
                                                            #line 8614 "PrintCLike.cpp"
  append(L"W");
                                                            #line 4970 "PrintCLike.cpp.template"
                                                                      print(assign());
                                                                      print(thiz());
                                                            #line 8619 "PrintCLike.cpp"
  append(L"e");
                                                            #line 4972 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(k));
                                                                    }
                                                                    print(semicolon());
                                                            #line 8625 "PrintCLike.cpp"
  append(L"\n");
  append(L"\n");
  append(L"  ");
                                                            #line 4977 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8631 "PrintCLike.cpp"
  append(L"l1 = code; ");
                                                            #line 4978 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8635 "PrintCLike.cpp"
  append(L"b1 = ");
                                                            #line 4979 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8639 "PrintCLike.cpp"
  append(L"begin; ");
                                                            #line 4980 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8643 "PrintCLike.cpp"
  append(L"e1 = ");
                                                            #line 4981 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8647 "PrintCLike.cpp"
  append(L"end");
                                                            #line 4982 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                    for (size_t k = 2; k <= grammar->k; ++k)
                                                                    {
                                                            #line 8653 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4986 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 8658 "PrintCLike.cpp"
  append(L"l");
                                                            #line 4987 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(k));
                                                            #line 8662 "PrintCLike.cpp"
  append(L" = 0");
                                                            #line 4988 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                                    }
                                                                  }
                                                                  if (isLrParser)
                                                                  {
                                                            #line 8670 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4994 "PrintCLike.cpp.template"
                                                                    if (useGlr)
                                                                    {
                                                                      if (! isCpp())
                                                                      {
                                                            #line 8678 "PrintCLike.cpp"
  append(L"thread = ");
                                                            #line 4998 "PrintCLike.cpp.template"
                                                                      }
                                                                      if (isJava())
                                                                      {
                                                                        print(className.c_str());
                                                            #line 8685 "PrintCLike.cpp"
  append(L".this.");
                                                            #line 5002 "PrintCLike.cpp.template"
                                                                      }
                                                                      else if (isCSharp() || isCpp() || isHaxe() || isScala() || isTypescript() || isGo() || isPython())
                                                                      {
                                                                        print(thiz());
                                                            #line 8692 "PrintCLike.cpp"
  append(L"parser");
                                                            #line 5006 "PrintCLike.cpp.template"
                                                                        print(arrow());
                                                                      }
                                                                    }
                                                                    else
                                                                    {
                                                                      print(thiz());
                                                                    }
                                                            #line 8702 "PrintCLike.cpp"
  append(L"parse(-1, ");
                                                            #line 5013 "PrintCLike.cpp.template"
                                                                    print(format.toString<wchar_t>(grammar->whitespace->getStateId()));
                                                                    if (tree)
                                                                    {
                                                            #line 8708 "PrintCLike.cpp"
  append(L", ");
                                                            #line 5016 "PrintCLike.cpp.template"
                                                                      print(nullPtr());
                                                                    }
                                                                    if (useGlr)
                                                                    {
                                                            #line 8715 "PrintCLike.cpp"
  append(L", thread");
                                                            #line 5020 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 8719 "PrintCLike.cpp"
  append(L")");
                                                            #line 5021 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                  }
                                                                  else
                                                                  {
                                                            #line 8726 "PrintCLike.cpp"
  append(L"\n");
  append(L"\n");
  append(L"  ");
                                                            #line 5027 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8732 "PrintCLike.cpp"
  append(L"try_");
                                                            #line 5028 "PrintCLike.cpp.template"
                                                                    print(Format::acceptableName<WString>(grammar->whitespace->name).c_str());
                                                                    if (! isScala()) print(L"()");
                                                                    print(semicolon());
                                                                  }
                                                                  if (useGlr)
                                                                  {
                                                                    if (isJavascript())
                                                                    {
                                                            #line 8743 "PrintCLike.cpp"
  append(L"\n");
  append(L"  end = thread.getEnd();");
                                                            #line 5037 "PrintCLike.cpp.template"
                                                                    }
                                                                    else if (isCpp())
                                                                    {
                                                            #line 8750 "PrintCLike.cpp"
  append(L"\n");
  append(L"  end = thread->end;\n");
  append(L"  delete thread;");
                                                            #line 5042 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 8758 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5046 "PrintCLike.cpp.template"
                                                                      if (useGlr) print(thiz());
                                                            #line 8763 "PrintCLike.cpp"
  append(L"end = thread");
                                                            #line 5047 "PrintCLike.cpp.template"
                                                                      print(arrow());
                                                            #line 8767 "PrintCLike.cpp"
  append(L"end");
                                                            #line 5048 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                                    }
                                                                  }
                                                                  else
                                                                  {
                                                            #line 8775 "PrintCLike.cpp"
  append(L"\n");
  append(L"\n");
  append(L"  ");
                                                            #line 5055 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8781 "PrintCLike.cpp"
  append(L"b0 = b0W; ");
                                                            #line 5056 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8785 "PrintCLike.cpp"
  append(L"e0 = e0W");
                                                            #line 5057 "PrintCLike.cpp.template"
                                                                    for (size_t k = 1; k < grammar->k; ++k)
                                                                    {
                                                            #line 8790 "PrintCLike.cpp"
  append(L"; ");
                                                            #line 5059 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 8794 "PrintCLike.cpp"
  append(L"l");
                                                            #line 5060 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(k));
                                                            #line 8798 "PrintCLike.cpp"
  append(L" = l");
                                                            #line 5061 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(k));
                                                            #line 8802 "PrintCLike.cpp"
  append(L"W");
                                                            #line 5062 "PrintCLike.cpp.template"
                                                                      if (isPython())
                                                                      {
                                                            #line 8807 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5065 "PrintCLike.cpp.template"
                                                                      }
                                                                      else
                                                                      {
                                                            #line 8814 "PrintCLike.cpp"
  append(L"; ");
                                                            #line 5068 "PrintCLike.cpp.template"
                                                                      }
                                                            #line 8818 "PrintCLike.cpp"
  append(L"if ");
                                                            #line 5069 "PrintCLike.cpp.template"
                                                                      print(ifLeftParen());
                                                                      print(thiz());
                                                            #line 8823 "PrintCLike.cpp"
  append(L"l");
                                                            #line 5071 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(k));
                                                            #line 8827 "PrintCLike.cpp"
  append(L" != 0");
                                                            #line 5072 "PrintCLike.cpp.template"
                                                                      print(ifRightParen());
                                                                      if (isPython())
                                                                      {
                                                                        increaseIndent();
                                                                      }
                                                                      else
                                                                      {
                                                            #line 8837 "PrintCLike.cpp"
  append(L" {");
                                                            #line 5079 "PrintCLike.cpp.template"
                                                                      }
                                                            #line 8841 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5081 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 8846 "PrintCLike.cpp"
  append(L"b");
                                                            #line 5082 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(k));
                                                            #line 8850 "PrintCLike.cpp"
  append(L" = b");
                                                            #line 5083 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(k));
                                                            #line 8854 "PrintCLike.cpp"
  append(L"W; ");
                                                            #line 5084 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 8858 "PrintCLike.cpp"
  append(L"e");
                                                            #line 5085 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(k));
                                                            #line 8862 "PrintCLike.cpp"
  append(L" = e");
                                                            #line 5086 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(k));
                                                            #line 8866 "PrintCLike.cpp"
  append(L"W");
                                                            #line 5087 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(semicolon());
                                                                    if (isPython())
                                                                    {
                                                                      decreaseIndent(grammar->k - 1);
                                                                    }
                                                                    else
                                                                    {
                                                            #line 8877 "PrintCLike.cpp"
  append(L" ");
                                                            #line 5095 "PrintCLike.cpp.template"
                                                                      for (size_t k = 1; k < grammar->k; ++k)
                                                                      {
                                                            #line 8882 "PrintCLike.cpp"
  append(L"}");
                                                            #line 5097 "PrintCLike.cpp.template"
                                                                      }
                                                                    }
                                                                  }
                                                                  print(rightBrace());
                                                            #line 8889 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5102 "PrintCLike.cpp.template"
                                                                  if (! isGo())
                                                                    decreaseIndent();
                                                                }
                                                                if (tree && ! isLrParser)
                                                                {
                                                                  if (! isGo())
                                                                    increaseIndent();
                                                                  openMethod (voidType(), L"", L"whitespace", L"");
                                                                  print(leftBrace());
                                                            #line 8901 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if ");
                                                            #line 5112 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                                  print(thiz());
                                                            #line 8907 "PrintCLike.cpp"
  append(L"e0 != ");
                                                            #line 5114 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8911 "PrintCLike.cpp"
  append(L"b1");
                                                            #line 5115 "PrintCLike.cpp.template"
                                                                  print(ifRightParen());
                                                                  increaseIndent();
                                                                  print(leftBrace());
                                                                  decreaseIndent();
                                                            #line 8918 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 5120 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8923 "PrintCLike.cpp"
  append(L"eventHandler");
                                                            #line 5121 "PrintCLike.cpp.template"
                                                                  print(arrow());
                                                                  if (isGo())
                                                                  {
                                                            #line 8929 "PrintCLike.cpp"
  append(L"W");
                                                            #line 5124 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 8935 "PrintCLike.cpp"
  append(L"w");
                                                            #line 5127 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 8939 "PrintCLike.cpp"
  append(L"hitespace(");
                                                            #line 5128 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8943 "PrintCLike.cpp"
  append(L"e0, ");
                                                            #line 5129 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8947 "PrintCLike.cpp"
  append(L"b1)");
                                                            #line 5130 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                            #line 8951 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 5132 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8956 "PrintCLike.cpp"
  append(L"e0 = ");
                                                            #line 5133 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8960 "PrintCLike.cpp"
  append(L"b1");
                                                            #line 5134 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                  increaseIndent();
                                                                  print(rightBrace());
                                                                  decreaseIndent();
                                                                  print(rightBrace());
                                                                  if (! isGo())
                                                                    decreaseIndent();
                                                            #line 8970 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5142 "PrintCLike.cpp.template"
                                                                }
                                                                if (! isGo())
                                                                  increaseIndent();
                                                                openMethod(intType(), L"", L"matchW", L"int tokenSetId", false, useGlr ? L"ParsingThread" : className.c_str());
                                                                print(leftBrace());
                                                                if (isScala())
                                                                {
                                                            #line 8980 "PrintCLike.cpp"
  append(L"\n");
  append(L"  var continue = true\n");
  append(L"  var code = 0\n");
  append(L"  while (continue) {\n");
  append(L"    code = matcher(tokenSetId)");
                                                            #line 5153 "PrintCLike.cpp.template"
                                                                  increaseIndent(2);
                                                                }
                                                                else
                                                                {
                                                                  if (! isPython())
                                                                  {
                                                            #line 8993 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5160 "PrintCLike.cpp.template"
                                                                    print((isJavascript() || isTypescript() || isHaxe() || isGo()) ? L"var" : L"int");
                                                            #line 8998 "PrintCLike.cpp"
  append(L" code");
                                                            #line 5161 "PrintCLike.cpp.template"
                                                                    if (isTypescript())
                                                                    {
                                                            #line 9003 "PrintCLike.cpp"
  append(L": number");
                                                            #line 5163 "PrintCLike.cpp.template"
                                                                    }
                                                                    else if (isGo())
                                                                    {
                                                            #line 9009 "PrintCLike.cpp"
  append(L" int");
                                                            #line 5166 "PrintCLike.cpp.template"
                                                                    }
                                                                    if (isHaxe())
                                                                    {
                                                            #line 9015 "PrintCLike.cpp"
  append(L" = 0");
                                                            #line 5169 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(semicolon());
                                                                  }
                                                                  if (isHaxe() || isPython())
                                                                  {
                                                            #line 9023 "PrintCLike.cpp"
  append(L"\n");
  append(L"  while ");
                                                            #line 5175 "PrintCLike.cpp.template"
                                                                    print(ifLeftParen());
                                                                    print(isPython() ? L"T" : L"t");
                                                            #line 9029 "PrintCLike.cpp"
  append(L"rue");
                                                            #line 5177 "PrintCLike.cpp.template"
                                                                    print(ifRightParen());
                                                                  }
                                                                  else
                                                                  {
                                                            #line 9036 "PrintCLike.cpp"
  append(L"\n");
  append(L"  for");
                                                            #line 5182 "PrintCLike.cpp.template"
                                                                    if (! isGo())
                                                                    {
                                                            #line 9042 "PrintCLike.cpp"
  append(L" (;;)");
                                                            #line 5184 "PrintCLike.cpp.template"
                                                                    }
                                                                  }
                                                                  increaseIndent();
                                                                  print(leftBrace());
                                                                  increaseIndent();
                                                            #line 9050 "PrintCLike.cpp"
  append(L"\n");
  append(L"code = ");
                                                            #line 5190 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 9055 "PrintCLike.cpp"
  append(L"match(tokenSetId)");
                                                            #line 5191 "PrintCLike.cpp.template"
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
                                                            #line 9084 "PrintCLike.cpp"
  append(L"\n");
  append(L"  continue = false\n");
  append(L"}\n");
  append(L"else {\n");
  append(L"  ");
                                                            #line 5221 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 9092 "PrintCLike.cpp"
  append(L"skip(code)\n");
  append(L"}");
                                                            #line 5223 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 9099 "PrintCLike.cpp"
  append(L"\n");
  append(L"  break");
                                                            #line 5227 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                    print(rightBrace());
                                                            #line 9105 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5230 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 9109 "PrintCLike.cpp"
  append(L"skip(code);");
                                                            #line 5231 "PrintCLike.cpp.template"
                                                                  }
                                                                }
                                                                else if (isScala())
                                                                {
                                                            #line 9116 "PrintCLike.cpp"
  append(L"\n");
  append(L"continue = false");
                                                            #line 5236 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 9123 "PrintCLike.cpp"
  append(L"\n");
  append(L"break");
                                                            #line 5240 "PrintCLike.cpp.template"
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
                                                            #line 9137 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5251 "PrintCLike.cpp.template"
                                                                if (! isScala())
                                                                {
                                                            #line 9143 "PrintCLike.cpp"
  append(L"return ");
                                                            #line 5253 "PrintCLike.cpp.template"
                                                                }
                                                            #line 9147 "PrintCLike.cpp"
  append(L"code");
                                                            #line 5254 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                print(rightBrace());
                                                            #line 9152 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5257 "PrintCLike.cpp.template"
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
                                                            #line 9168 "PrintCLike.cpp"
  append(L"\n");
  append(L"def parse(): Unit = {\n");
  append(L"  parse_");
                                                            #line 5272 "PrintCLike.cpp.template"
                                                                  print(Format::acceptableName<WString>(grammar->startSymbol()->name).c_str());
                                                            #line 9174 "PrintCLike.cpp"
  append(L"()\n");
  append(L"}\n");
                                                            #line 5275 "PrintCLike.cpp.template"
                                                                }
                                                                if (memoization)
                                                                {
                                                                  int bits = Math::bits(grammar->conflictCount);
                                                            #line 9182 "PrintCLike.cpp"
  append(L"\n");
  append(L"private def memoize(i: Int, e: Int, v: Int): Unit = {\n");
  append(L"  memo.put((e << ");
                                                            #line 5281 "PrintCLike.cpp.template"
                                                                  print(format.toString<wchar_t>(bits));
                                                            #line 9188 "PrintCLike.cpp"
  append(L") + i, v)\n");
  append(L"}\n");
  append(L"\n");
  append(L"private def memoized(i: Int, e: Int) = {\n");
  append(L"  memo.getOrElse((e << ");
                                                            #line 5286 "PrintCLike.cpp.template"
                                                                  print(format.toString<wchar_t>(bits));
                                                            #line 9196 "PrintCLike.cpp"
  append(L") + i, 0)\n");
  append(L"}\n");
                                                            #line 5289 "PrintCLike.cpp.template"
                                                                }
                                                            #line 9201 "PrintCLike.cpp"
  append(L"\n");
  append(L"def error(b: Int, e: Int, s: Int, l: Int, t: Int): Int = {");
                                                            #line 5291 "PrintCLike.cpp.template"
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
                                                            #line 9215 "PrintCLike.cpp"
  append(L"\n");
  append(L"if ");
                                                            #line 5302 "PrintCLike.cpp.template"
                                                                print(ifLeftParen());
                                                                if (grammar->noThrow)
                                                                {
                                                                  print(thiz());
                                                            #line 9223 "PrintCLike.cpp"
  append(L"viable ");
                                                            #line 5306 "PrintCLike.cpp.template"
                                                                  if (isPython())
                                                                  {
                                                            #line 9228 "PrintCLike.cpp"
  append(L"and");
                                                            #line 5308 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 9234 "PrintCLike.cpp"
  append(L"&&");
                                                            #line 5311 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 9238 "PrintCLike.cpp"
  append(L" ");
                                                            #line 5312 "PrintCLike.cpp.template"
                                                                }
                                                            #line 9242 "PrintCLike.cpp"
  append(L"e >= ");
                                                            #line 5313 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 9246 "PrintCLike.cpp"
  append(L"ex");
                                                            #line 5314 "PrintCLike.cpp.template"
                                                                print(ifRightParen());
                                                                print(leftBrace());
                                                            #line 9251 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5317 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 9256 "PrintCLike.cpp"
  append(L"bx = b");
                                                            #line 5318 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 9260 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5320 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 9265 "PrintCLike.cpp"
  append(L"ex = e");
                                                            #line 5321 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 9269 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5323 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 9274 "PrintCLike.cpp"
  append(L"sx = s");
                                                            #line 5324 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 9278 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5326 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 9283 "PrintCLike.cpp"
  append(L"lx = l");
                                                            #line 5327 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 9287 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5329 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 9292 "PrintCLike.cpp"
  append(L"tx = t");
                                                            #line 5330 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                print(rightBrace());
                                                                decreaseIndent();
                                                                if (grammar->noThrow)
                                                                {
                                                            #line 9300 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5336 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 9305 "PrintCLike.cpp"
  append(L"viable = ");
                                                            #line 5337 "PrintCLike.cpp.template"
                                                                  if (isPython())
                                                                  {
                                                            #line 9310 "PrintCLike.cpp"
  append(L"F");
                                                            #line 5339 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 9316 "PrintCLike.cpp"
  append(L"f");
                                                            #line 5342 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 9320 "PrintCLike.cpp"
  append(L"alse");
                                                            #line 5343 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                            #line 9324 "PrintCLike.cpp"
  append(L"\n");
  append(L"  return -s");
                                                            #line 5345 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                                else
                                                                {
                                                                  printFlush(1, true);
                                                            #line 9333 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5351 "PrintCLike.cpp.template"
                                                                  print(beginThrowStmt());
                                                                  print(thiz());
                                                            #line 9339 "PrintCLike.cpp"
  append(L"bx, ");
                                                            #line 5353 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 9343 "PrintCLike.cpp"
  append(L"ex, ");
                                                            #line 5354 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 9347 "PrintCLike.cpp"
  append(L"sx, ");
                                                            #line 5355 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 9351 "PrintCLike.cpp"
  append(L"lx, ");
                                                            #line 5356 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 9355 "PrintCLike.cpp"
  append(L"tx");
                                                            #line 5357 "PrintCLike.cpp.template"
                                                                  print(endThrowStmt());
                                                                  print(semicolon());
                                                                }
                                                              }
                                                              else
                                                              {
                                                                printFlush(1, true);
                                                            #line 9365 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5365 "PrintCLike.cpp.template"
                                                                if (isGo())
                                                                {
                                                            #line 9371 "PrintCLike.cpp"
  append(L"panic(&ParseError{b, e, s, l, t");
                                                            #line 5367 "PrintCLike.cpp.template"
                                                                  if (rejectsAmbiguity())
                                                                  {
                                                            #line 9376 "PrintCLike.cpp"
  append(L", false");
                                                            #line 5369 "PrintCLike.cpp.template"
                                                                    if (tree)
                                                                    {
                                                            #line 9381 "PrintCLike.cpp"
  append(L", nil");
                                                            #line 5371 "PrintCLike.cpp.template"
                                                                    }
                                                                  }
                                                            #line 9386 "PrintCLike.cpp"
  append(L"})");
                                                            #line 5373 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                                  print(beginThrowStmt());
                                                            #line 9393 "PrintCLike.cpp"
  append(L"b, e, s, l, t");
                                                            #line 5377 "PrintCLike.cpp.template"
                                                                  print(endThrowStmt());
                                                                  print(semicolon());
                                                                }
                                                              }
                                                              print(rightBrace());
                                                            #line 9401 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5383 "PrintCLike.cpp.template"
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
                                                            #line 9420 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5400 "PrintCLike.cpp.template"
                                                                openMethod(intType(), L"", L"lookback", L"int x, int y", false, clazz);
                                                                const wchar_t *lookback = isGo() ? L"lookback" : L"LOOKBACK";
                                                                print(leftBrace());
                                                                increaseIndent();
                                                                if (isGo())
                                                                {
                                                            #line 9429 "PrintCLike.cpp"
  append(L"\n");
  append(L"i := lookback[y]\n");
  append(L"l := lookback[i]\n");
  append(L"for l > x {");
                                                            #line 5409 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 9438 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5413 "PrintCLike.cpp.template"
                                                                  print(intVar());
                                                            #line 9442 "PrintCLike.cpp"
  append(L"i");
                                                            #line 5414 "PrintCLike.cpp.template"
                                                                  print(assign());
                                                                  print(staticPrefix());
                                                                  print(lookback);
                                                                  print(leftbracket());
                                                            #line 9449 "PrintCLike.cpp"
  append(L"y");
                                                            #line 5418 "PrintCLike.cpp.template"
                                                                  print(rightbracket());
                                                                  print(semicolon());
                                                            #line 9454 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5421 "PrintCLike.cpp.template"
                                                                  print(intVar());
                                                            #line 9458 "PrintCLike.cpp"
  append(L"l");
                                                            #line 5422 "PrintCLike.cpp.template"
                                                                  print(assign());
                                                                  print(staticPrefix());
                                                                  print(lookback);
                                                                  print(leftbracket());
                                                            #line 9465 "PrintCLike.cpp"
  append(L"i");
                                                            #line 5426 "PrintCLike.cpp.template"
                                                                  print(rightbracket());
                                                                  print(semicolon());
                                                            #line 9470 "PrintCLike.cpp"
  append(L"\n");
  append(L"while ");
                                                            #line 5429 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                            #line 9475 "PrintCLike.cpp"
  append(L"l > x");
                                                            #line 5430 "PrintCLike.cpp.template"
                                                                  print(ifRightParen());
                                                                  print(leftBrace());
                                                                }
                                                            #line 9481 "PrintCLike.cpp"
  append(L"\n");
  append(L"  i += 2");
                                                            #line 5434 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 9486 "PrintCLike.cpp"
  append(L"\n");
  append(L"  l = ");
                                                            #line 5436 "PrintCLike.cpp.template"
                                                                print(staticPrefix());
                                                                print(lookback);
                                                                print(leftbracket());
                                                            #line 9493 "PrintCLike.cpp"
  append(L"i");
                                                            #line 5439 "PrintCLike.cpp.template"
                                                                print(rightbracket());
                                                                print(semicolon());
                                                                print(rightBrace());
                                                            #line 9499 "PrintCLike.cpp"
  append(L"\n");
  append(L"if ");
                                                            #line 5443 "PrintCLike.cpp.template"
                                                                print(ifLeftParen());
                                                            #line 9504 "PrintCLike.cpp"
  append(L"l < x");
                                                            #line 5444 "PrintCLike.cpp.template"
                                                                print(ifRightParen());
                                                                print(leftBrace());
                                                            #line 9509 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5447 "PrintCLike.cpp.template"
                                                                print(returnKeyword());
                                                            #line 9514 "PrintCLike.cpp"
  append(L"0");
                                                            #line 5448 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 9518 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5450 "PrintCLike.cpp.template"
                                                                print(elseWithBraces());
                                                            #line 9522 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5452 "PrintCLike.cpp.template"
                                                                print(returnKeyword());
                                                                print(staticPrefix());
                                                                print(lookback);
                                                                print(leftbracket());
                                                            #line 9530 "PrintCLike.cpp"
  append(L"i + 1");
                                                            #line 5456 "PrintCLike.cpp.template"
                                                                print(rightbracket());
                                                                print(semicolon());
                                                                print(rightBrace());
                                                                decreaseIndent();
                                                                print(rightBrace());
                                                            #line 9538 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5462 "PrintCLike.cpp.template"
                                                                if (isJavascript() && useGlr)
                                                                {
                                                            #line 9543 "PrintCLike.cpp"
  append(L"\n");
  append(L"this.count = function(code)\n");
                                                            #line 5466 "PrintCLike.cpp.template"
                                                                }
                                                                else if (isTypescript() && useGlr)
                                                                {
                                                            #line 9550 "PrintCLike.cpp"
  append(L"\n");
  append(L"public count(code: number)\n");
                                                            #line 5471 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                                  openMethod(intType(), L"", L"count", L"int code", false, clazz);
                                                                }
                                                                print(leftBrace());
                                                                increaseIndent();
                                                            #line 9561 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5479 "PrintCLike.cpp.template"
                                                                print(intVar());
                                                            #line 9565 "PrintCLike.cpp"
  append(L"count");
                                                            #line 5480 "PrintCLike.cpp.template"
                                                                print(assign());
                                                            #line 9569 "PrintCLike.cpp"
  append(L"0");
                                                            #line 5481 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                int stackElementSize = tree ? 3 : 2;
                                                                if (isHaxe() || isScala())
                                                                {
                                                                  if (useGlr)
                                                                  {
                                                            #line 9578 "PrintCLike.cpp"
  append(L"\n");
  append(L"var node = this");
                                                            #line 5488 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                    if (isScala())
                                                                    {
                                                            #line 9585 "PrintCLike.cpp"
  append(L"\n");
  append(L"var c = code");
                                                            #line 5492 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 9590 "PrintCLike.cpp"
  append(L"\n");
  append(L"while ");
                                                            #line 5494 "PrintCLike.cpp.template"
                                                                    print(ifLeftParen());
                                                            #line 9595 "PrintCLike.cpp"
  append(L"node.state >= 0");
                                                            #line 5495 "PrintCLike.cpp.template"
                                                                    print(ifRightParen());
                                                                    print(leftBrace());
                                                                    if (isScala())
                                                                    {
                                                            #line 9602 "PrintCLike.cpp"
  append(L"\n");
  append(L"  c = lookback(node.code, c)\n");
  append(L"  if (c == 0) return count\n");
  append(L"  count += 1");
                                                            #line 5502 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 9611 "PrintCLike.cpp"
  append(L"\n");
  append(L"  code = lookback(node.code, code);\n");
  append(L"  if ");
                                                            #line 5507 "PrintCLike.cpp.template"
                                                                      print(ifLeftParen());
                                                            #line 9617 "PrintCLike.cpp"
  append(L"code == 0");
                                                            #line 5508 "PrintCLike.cpp.template"
                                                                      print(ifRightParen());
                                                            #line 9621 "PrintCLike.cpp"
  append(L"\n");
  append(L"    break");
                                                            #line 5511 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                            #line 9626 "PrintCLike.cpp"
  append(L"\n");
  append(L"  count++");
                                                            #line 5513 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                                    }
                                                            #line 9632 "PrintCLike.cpp"
  append(L"\n");
  append(L"  node = node.link");
                                                            #line 5516 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                  }
                                                                  else
                                                                  {
                                                            #line 9640 "PrintCLike.cpp"
  append(L"\n");
  append(L"var t = top");
                                                            #line 5521 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 9645 "PrintCLike.cpp"
  append(L"\n");
  append(L"var c = code");
                                                            #line 5523 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 9650 "PrintCLike.cpp"
  append(L"\n");
  append(L"while (t >= 0)");
                                                            #line 5525 "PrintCLike.cpp.template"
                                                                    print(leftBrace());
                                                            #line 9655 "PrintCLike.cpp"
  append(L"\n");
  append(L"  c = lookback(iStack");
                                                            #line 5527 "PrintCLike.cpp.template"
                                                                    print(leftbracket());
                                                            #line 9660 "PrintCLike.cpp"
  append(L"t");
                                                            #line 5528 "PrintCLike.cpp.template"
                                                                    print(rightbracket());
                                                            #line 9664 "PrintCLike.cpp"
  append(L", c)");
                                                            #line 5529 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 9668 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if ");
                                                            #line 5531 "PrintCLike.cpp.template"
                                                                    print(ifLeftParen());
                                                            #line 9673 "PrintCLike.cpp"
  append(L"c == 0");
                                                            #line 5532 "PrintCLike.cpp.template"
                                                                    print(ifRightParen());
                                                            #line 9677 "PrintCLike.cpp"
  append(L" return count");
                                                            #line 5533 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 9681 "PrintCLike.cpp"
  append(L"\n");
  append(L"  count += 1");
                                                            #line 5535 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 9686 "PrintCLike.cpp"
  append(L"\n");
  append(L"  t -= ");
                                                            #line 5537 "PrintCLike.cpp.template"
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
                                                            #line 9700 "PrintCLike.cpp"
  append(L"\n");
  append(L"node = self\n");
  append(L"while ");
                                                            #line 5549 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 9708 "PrintCLike.cpp"
  append(L"\n");
  append(L"for ");
                                                            #line 5553 "PrintCLike.cpp.template"
                                                                      print(ifLeftParen());
                                                                      if (isJavascript() || isTypescript())
                                                                      {
                                                            #line 9715 "PrintCLike.cpp"
  append(L"var ");
                                                            #line 5556 "PrintCLike.cpp.template"
                                                                      }
                                                                      else if (!isGo())
                                                                      {
                                                            #line 9721 "PrintCLike.cpp"
  append(L"StackNode ");
                                                            #line 5559 "PrintCLike.cpp.template"
                                                                      }
                                                                      if (isCpp()) print(L"*");
                                                            #line 9726 "PrintCLike.cpp"
  append(L"node");
                                                            #line 5561 "PrintCLike.cpp.template"
                                                                      if (isTypescript())
                                                                      {
                                                            #line 9731 "PrintCLike.cpp"
  append(L": StackNode | null");
                                                            #line 5563 "PrintCLike.cpp.template"
                                                                      }
                                                                      print(assign());
                                                            #line 9736 "PrintCLike.cpp"
  append(L"this; ");
                                                            #line 5565 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 9740 "PrintCLike.cpp"
  append(L"node");
                                                            #line 5566 "PrintCLike.cpp.template"
                                                                    if (isTypescript()) print(L"!");
                                                                    print(arrow());
                                                            #line 9745 "PrintCLike.cpp"
  append(L"state >= 0");
                                                            #line 5568 "PrintCLike.cpp.template"
                                                                    if (isPython())
                                                                    {
                                                            #line 9750 "PrintCLike.cpp"
  append(L":");
                                                            #line 5570 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 9756 "PrintCLike.cpp"
  append(L"; node = node");
                                                            #line 5573 "PrintCLike.cpp.template"
                                                                      if (isTypescript()) print(L"!");
                                                                      print(arrow());
                                                            #line 9761 "PrintCLike.cpp"
  append(L"link");
                                                            #line 5575 "PrintCLike.cpp.template"
                                                                      print(ifRightParen());
                                                                    }
                                                                    print(leftBrace());
                                                            #line 9767 "PrintCLike.cpp"
  append(L"\n");
  append(L"  code = ");
                                                            #line 5579 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                                    print(isGo() ? L"L" : L"l");
                                                            #line 9773 "PrintCLike.cpp"
  append(L"ookback(node");
                                                            #line 5581 "PrintCLike.cpp.template"
                                                                    if (isTypescript()) print(L"!");
                                                                    print(arrow());
                                                            #line 9778 "PrintCLike.cpp"
  append(L"code, code)");
                                                            #line 5583 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                  }
                                                                  else
                                                                  {
                                                                    if (isPython())
                                                                    {
                                                            #line 9787 "PrintCLike.cpp"
  append(L"\n");
  append(L"t");
                                                            #line 5590 "PrintCLike.cpp.template"
                                                                      print(assign());
                                                                      print(thiz());
                                                            #line 9793 "PrintCLike.cpp"
  append(L"top");
                                                            #line 5592 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                            #line 9797 "PrintCLike.cpp"
  append(L"\n");
  append(L"while ");
                                                            #line 5594 "PrintCLike.cpp.template"
                                                                      print(ifLeftParen());
                                                                      print(intVar());
                                                            #line 9803 "PrintCLike.cpp"
  append(L"t >= 0");
                                                            #line 5596 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 9809 "PrintCLike.cpp"
  append(L"\n");
  append(L"for ");
                                                            #line 5600 "PrintCLike.cpp.template"
                                                                      print(ifLeftParen());
                                                                      print(intVar());
                                                            #line 9815 "PrintCLike.cpp"
  append(L"t");
                                                            #line 5602 "PrintCLike.cpp.template"
                                                                      print(assign());
                                                                      print(thiz());
                                                            #line 9820 "PrintCLike.cpp"
  append(L"top; t >= 0; t -= ");
                                                            #line 5604 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(stackElementSize));
                                                                    }
                                                                    print(ifRightParen());
                                                                    print(leftBrace());
                                                            #line 9827 "PrintCLike.cpp"
  append(L"\n");
  append(L"  code = ");
                                                            #line 5609 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 9832 "PrintCLike.cpp"
  append(L"lookback(");
                                                            #line 5610 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 9836 "PrintCLike.cpp"
  append(L"iStack[t], code)");
                                                            #line 5611 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                  }
                                                            #line 9841 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if ");
                                                            #line 5614 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                            #line 9846 "PrintCLike.cpp"
  append(L"code == 0");
                                                            #line 5615 "PrintCLike.cpp.template"
                                                                  print(ifRightParen());
                                                                  increaseIndent();
                                                                  print(leftBrace());
                                                            #line 9852 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5619 "PrintCLike.cpp.template"
                                                                  if (! isHaxe() && ! isScala())
                                                                  {
                                                            #line 9858 "PrintCLike.cpp"
  append(L"break");
                                                            #line 5621 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 9864 "PrintCLike.cpp"
  append(L"return count");
                                                            #line 5624 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(semicolon());
                                                                  print(rightBrace());
                                                                  decreaseIndent();
                                                            #line 9871 "PrintCLike.cpp"
  append(L"\n");
  append(L"  count += 1");
                                                            #line 5629 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                  if (isPython())
                                                                  {
                                                                    if (useGlr)
                                                                    {
                                                            #line 9880 "PrintCLike.cpp"
  append(L"\n");
  append(L"  node = node.link");
                                                            #line 5635 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 9887 "PrintCLike.cpp"
  append(L"\n");
  append(L"  t -= ");
                                                            #line 5639 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(stackElementSize));
                                                                    }
                                                                  }
                                                                }
                                                                print(rightBrace());
                                                            #line 9896 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5645 "PrintCLike.cpp.template"
                                                                print(returnKeyword());
                                                            #line 9900 "PrintCLike.cpp"
  append(L"count");
                                                            #line 5646 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                decreaseIndent();
                                                                print(rightBrace());
                                                                if (isJavascript() && useGlr)
                                                                {
                                                            #line 9908 "PrintCLike.cpp"
  append(L";");
                                                            #line 5651 "PrintCLike.cpp.template"
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
                                                            #line 9934 "PrintCLike.cpp"
  append(L"\n");
  append(L"if ");
                                                            #line 5675 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                                  print(thiz());
                                                            #line 9940 "PrintCLike.cpp"
  append(L"l");
                                                            #line 5677 "PrintCLike.cpp.template"
                                                                  print(kAsString);
                                                            #line 9944 "PrintCLike.cpp"
  append(L" == 0");
                                                            #line 5678 "PrintCLike.cpp.template"
                                                                  print(ifRightParen());
                                                                  print(leftBrace());
                                                            #line 9949 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5681 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 9954 "PrintCLike.cpp"
  append(L"l");
                                                            #line 5682 "PrintCLike.cpp.template"
                                                                  print(kAsString);
                                                            #line 9958 "PrintCLike.cpp"
  append(L" = ");
                                                            #line 5683 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 9962 "PrintCLike.cpp"
  append(L"match");
                                                            #line 5684 "PrintCLike.cpp.template"
                                                                  if (withWhitespace)
                                                                  {
                                                            #line 9967 "PrintCLike.cpp"
  append(L"W");
                                                            #line 5686 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isScala())
                                                                  {
                                                            #line 9973 "PrintCLike.cpp"
  append(L"er");
                                                            #line 5689 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 9977 "PrintCLike.cpp"
  append(L"(tokenSetId)");
                                                            #line 5690 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                            #line 9981 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5692 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 9986 "PrintCLike.cpp"
  append(L"b");
                                                            #line 5693 "PrintCLike.cpp.template"
                                                                  print(kAsString);
                                                            #line 9990 "PrintCLike.cpp"
  append(L" = ");
                                                            #line 5694 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 9994 "PrintCLike.cpp"
  append(L"begin");
                                                            #line 5695 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                            #line 9998 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5697 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 10003 "PrintCLike.cpp"
  append(L"e");
                                                            #line 5698 "PrintCLike.cpp.template"
                                                                  print(kAsString);
                                                            #line 10007 "PrintCLike.cpp"
  append(L" = ");
                                                            #line 5699 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 10011 "PrintCLike.cpp"
  append(L"end");
                                                            #line 5700 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                  print(rightBrace());
                                                                  if (unlimitedLookahead)
                                                                  {
                                                                    if (k >= 2)
                                                                    {
                                                            #line 10020 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5707 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 10024 "PrintCLike.cpp"
  append(L"lk = prefix + ");
                                                            #line 5708 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 10028 "PrintCLike.cpp"
  append(L"l");
                                                            #line 5709 "PrintCLike.cpp.template"
                                                                      print(kAsString);
                                                                      print(semicolon());
                                                                    }
                                                                  }
                                                                  else
                                                                  {
                                                                    if (k == 2)
                                                                    {
                                                            #line 10039 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5718 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 10043 "PrintCLike.cpp"
  append(L"lk = (");
                                                            #line 5719 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 10047 "PrintCLike.cpp"
  append(L"l2 << ");
                                                            #line 5720 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(grammar->tokenSequenceFactory->tokenBits()));
                                                            #line 10051 "PrintCLike.cpp"
  append(L") | ");
                                                            #line 5721 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 10055 "PrintCLike.cpp"
  append(L"l1");
                                                            #line 5722 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                                    }
                                                                    else if (k > 2)
                                                                    {
                                                            #line 10062 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5727 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 10066 "PrintCLike.cpp"
  append(L"lk |= ");
                                                            #line 5728 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 10070 "PrintCLike.cpp"
  append(L"l");
                                                            #line 5729 "PrintCLike.cpp.template"
                                                                      print(kAsString);
                                                            #line 10074 "PrintCLike.cpp"
  append(L" << ");
                                                            #line 5730 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>((k - 1) * grammar->tokenSequenceFactory->tokenBits()));
                                                                      print(semicolon());
                                                                    }
                                                                  }
                                                                  decreaseIndent();
                                                                  print(rightBrace());
                                                            #line 10083 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5737 "PrintCLike.cpp.template"
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
                                                            #line 10111 "PrintCLike.cpp"
  append(L"\n");
  append(L"  return ");
                                                            #line 5763 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                                if (useGlr && (isCSharp() || isCpp() || isHaxe() || isScala() || isTypescript()))
                                                                {
                                                            #line 10118 "PrintCLike.cpp"
  append(L"parser");
                                                            #line 5766 "PrintCLike.cpp.template"
                                                                  print(arrow());
                                                                }
                                                            #line 10123 "PrintCLike.cpp"
  append(L"input");
                                                            #line 5768 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                print(rightBrace());
                                                                if (isJavascript())
                                                                {
                                                            #line 10130 "PrintCLike.cpp"
  append(L";");
                                                            #line 5772 "PrintCLike.cpp.template"
                                                                }
                                                            #line 10134 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5774 "PrintCLike.cpp.template"
                                                                openMethod(intType(), L"", L"getTokenOffset", L"", true);
                                                                print(leftBrace());
                                                            #line 10139 "PrintCLike.cpp"
  append(L"\n");
  append(L"  return ");
                                                            #line 5777 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 10144 "PrintCLike.cpp"
  append(L"b0");
                                                            #line 5778 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                print(rightBrace());
                                                                if (isJavascript())
                                                                {
                                                            #line 10151 "PrintCLike.cpp"
  append(L";");
                                                            #line 5782 "PrintCLike.cpp.template"
                                                                }
                                                            #line 10155 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5784 "PrintCLike.cpp.template"
                                                                openMethod(intType(), L"", L"getTokenEnd", L"", true);
                                                                print(leftBrace());
                                                            #line 10160 "PrintCLike.cpp"
  append(L"\n");
  append(L"  return ");
                                                            #line 5787 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 10165 "PrintCLike.cpp"
  append(L"e0");
                                                            #line 5788 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                print(rightBrace());
                                                                if (isJavascript())
                                                                {
                                                            #line 10172 "PrintCLike.cpp"
  append(L";");
                                                            #line 5792 "PrintCLike.cpp.template"
                                                                }
                                                            #line 10176 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5794 "PrintCLike.cpp.template"
                                                              }
                                                              if (isJavascript())
                                                              {
                                                                if (useGlr)
                                                                {
                                                            #line 10184 "PrintCLike.cpp"
  append(L"\n");
  append(L"this.reset = function");
                                                            #line 5800 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 10191 "PrintCLike.cpp"
  append(L"\n");
  append(L"function reset");
                                                            #line 5804 "PrintCLike.cpp.template"
                                                                }
                                                            #line 10196 "PrintCLike.cpp"
  append(L"(l, b, e)\n");
  append(L"{");
                                                            #line 5806 "PrintCLike.cpp.template"
                                                              }
                                                              else if (isTypescript())
                                                              {
                                                            #line 10203 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5810 "PrintCLike.cpp.template"
                                                                if (! performanceTest && ! useGlr)
                                                                {
                                                            #line 10208 "PrintCLike.cpp"
  append(L"private ");
                                                            #line 5812 "PrintCLike.cpp.template"
                                                                }
                                                            #line 10212 "PrintCLike.cpp"
  append(L"reset(l: number, b: number, e: number)\n");
  append(L"{");
                                                            #line 5814 "PrintCLike.cpp.template"
                                                              }
                                                              else if (isHaxe())
                                                              {
                                                            #line 10219 "PrintCLike.cpp"
  append(L"\n");
  append(L"public function reset(l, b, e)\n");
  append(L"{");
                                                            #line 5819 "PrintCLike.cpp.template"
                                                              }
                                                              else
                                                              {
                                                                openMethod(voidType(), isJava() ? L"final " : L"", L"reset", L"int l, int b, int e", false, useGlr ? L"ParsingThread" : className.c_str());
                                                                print(leftBrace());
                                                              }
                                                            #line 10230 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5826 "PrintCLike.cpp.template"
                                                              if (! isPython() && ! isScala())
                                                              {
                                                            #line 10236 "PrintCLike.cpp"
  append(L"        ");
                                                            #line 5828 "PrintCLike.cpp.template"
                                                                print(wcslen(thiz()), L" ");
                                                              }
                                                              print(thiz());
                                                            #line 10242 "PrintCLike.cpp"
  append(L"b0 = b; ");
                                                            #line 5831 "PrintCLike.cpp.template"
                                                              print(thiz());
                                                            #line 10246 "PrintCLike.cpp"
  append(L"e0 = b");
                                                            #line 5832 "PrintCLike.cpp.template"
                                                              print(semicolon());
                                                            #line 10250 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5834 "PrintCLike.cpp.template"
                                                              print(thiz());
                                                            #line 10255 "PrintCLike.cpp"
  append(L"l1 = l; ");
                                                            #line 5835 "PrintCLike.cpp.template"
                                                              print(thiz());
                                                            #line 10259 "PrintCLike.cpp"
  append(L"b1 = b; ");
                                                            #line 5836 "PrintCLike.cpp.template"
                                                              print(thiz());
                                                            #line 10263 "PrintCLike.cpp"
  append(L"e1 = e");
                                                            #line 5837 "PrintCLike.cpp.template"
                                                              print(semicolon());
                                                              for (size_t k = 2; k <= grammar->k; ++k)
                                                              {
                                                            #line 10269 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5841 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 10274 "PrintCLike.cpp"
  append(L"l");
                                                            #line 5842 "PrintCLike.cpp.template"
                                                                print(format.toString<wchar_t>(k));
                                                            #line 10278 "PrintCLike.cpp"
  append(L" = 0; ");
                                                            #line 5843 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 10282 "PrintCLike.cpp"
  append(L"b");
                                                            #line 5844 "PrintCLike.cpp.template"
                                                                print(format.toString<wchar_t>(k));
                                                            #line 10286 "PrintCLike.cpp"
  append(L" = 0; ");
                                                            #line 5845 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 10290 "PrintCLike.cpp"
  append(L"e");
                                                            #line 5846 "PrintCLike.cpp.template"
                                                                print(format.toString<wchar_t>(k));
                                                            #line 10294 "PrintCLike.cpp"
  append(L" = 0");
                                                            #line 5847 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                              }
                                                            #line 10299 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5850 "PrintCLike.cpp.template"
                                                              print(thiz());
                                                            #line 10304 "PrintCLike.cpp"
  append(L"end = e");
                                                            #line 5851 "PrintCLike.cpp.template"
                                                              print(semicolon());
                                                              if (hasBacktracking)
                                                              {
                                                            #line 10310 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5855 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 10315 "PrintCLike.cpp"
  append(L"ex = -1");
                                                            #line 5856 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                if (memoization)
                                                                {
                                                                  if (isJavascript() || isTypescript())
                                                                  {
                                                            #line 10323 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5862 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 10328 "PrintCLike.cpp"
  append(L"memo = {};");
                                                            #line 5863 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isCSharp())
                                                                  {
                                                            #line 10334 "PrintCLike.cpp"
  append(L"\n");
  append(L"  memo.Clear();");
                                                            #line 5867 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isScala())
                                                                  {
                                                            #line 10341 "PrintCLike.cpp"
  append(L"\n");
  append(L"  memo.clear()");
                                                            #line 5871 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isHaxe())
                                                                  {
                                                            #line 10348 "PrintCLike.cpp"
  append(L"\n");
  append(L"  memo = new Map();");
                                                            #line 5875 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isGo())
                                                                  {
                                                            #line 10355 "PrintCLike.cpp"
  append(L"\n");
  append(L"  this.memo = make(map[int]int)");
                                                            #line 5879 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isPython())
                                                                  {
                                                            #line 10362 "PrintCLike.cpp"
  append(L"\n");
  append(L"  self.memo = {}");
                                                            #line 5883 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 10369 "PrintCLike.cpp"
  append(L"\n");
  append(L"  memo.clear();");
                                                            #line 5887 "PrintCLike.cpp.template"
                                                                  }
                                                                }
                                                                if (grammar->noThrow)
                                                                {
                                                            #line 10377 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5892 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 10382 "PrintCLike.cpp"
  append(L"viable = ");
                                                            #line 5893 "PrintCLike.cpp.template"
                                                                  if (isPython())
                                                                  {
                                                            #line 10387 "PrintCLike.cpp"
  append(L"T");
                                                            #line 5895 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 10393 "PrintCLike.cpp"
  append(L"t");
                                                            #line 5898 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 10397 "PrintCLike.cpp"
  append(L"rue");
                                                            #line 5899 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                              }
                                                              if (tree && ! useGlr)
                                                              {
                                                            #line 10405 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5905 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 10410 "PrintCLike.cpp"
  append(L"eventHandler");
                                                            #line 5906 "PrintCLike.cpp.template"
                                                                if (isTypescript() && isLrParser) print(L"!");
                                                                print(arrow());
                                                                if (isGo())
                                                                {
                                                            #line 10417 "PrintCLike.cpp"
  append(L"R");
                                                            #line 5910 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 10423 "PrintCLike.cpp"
  append(L"r");
                                                            #line 5913 "PrintCLike.cpp.template"
                                                                }
                                                            #line 10427 "PrintCLike.cpp"
  append(L"eset(");
                                                            #line 5914 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 10431 "PrintCLike.cpp"
  append(L"input)");
                                                            #line 5915 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                              }
                                                              if (useGlr)
                                                              {
                                                            #line 10438 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5920 "PrintCLike.cpp.template"
                                                                if (isCSharp() || isCpp() || isHaxe() || isScala() || isTypescript() || isGo())
                                                                {
                                                                  print(thiz());
                                                            #line 10445 "PrintCLike.cpp"
  append(L"parser");
                                                            #line 5923 "PrintCLike.cpp.template"
                                                                  print(arrow());
                                                                }
                                                            #line 10450 "PrintCLike.cpp"
  append(L"maxId = 0");
                                                            #line 5925 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 10454 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5927 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 10459 "PrintCLike.cpp"
  append(L"id = ");
                                                            #line 5928 "PrintCLike.cpp.template"
                                                                if (isCSharp() || isCpp() || isHaxe() || isScala() || isTypescript() || isGo())
                                                                {
                                                                  print(thiz());
                                                            #line 10465 "PrintCLike.cpp"
  append(L"parser");
                                                            #line 5931 "PrintCLike.cpp.template"
                                                                   print(arrow());
                                                                }
                                                            #line 10470 "PrintCLike.cpp"
  append(L"maxId");
                                                            #line 5933 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                              }
                                                              print(rightBrace());
                                                              if (isJavascript() && useGlr)
                                                              {
                                                            #line 10478 "PrintCLike.cpp"
  append(L";");
                                                            #line 5938 "PrintCLike.cpp.template"
                                                              }
                                                            #line 10482 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5940 "PrintCLike.cpp.template"
                                                              if (useGlr || isJavascript() || isTypescript() || isHaxe() || isGo() || isPython())
                                                              {
                                                              }
                                                              else
                                                              {
                                                                openMethod(voidType(), L"", L"reset", L"");
                                                                print(leftBrace());
                                                            #line 10492 "PrintCLike.cpp"
  append(L"\n");
  append(L"  reset(0, 0, 0)");
                                                            #line 5948 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                print(rightBrace());
                                                            #line 10498 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5951 "PrintCLike.cpp.template"
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
                                                            #line 10526 "PrintCLike.cpp"
  append(L"\n");
  append(L"if ");
                                                            #line 5977 "PrintCLike.cpp.template"
                                                                    print(ifLeftParen());
                                                            #line 10531 "PrintCLike.cpp"
  append(L"(");
                                                            #line 5978 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                                    print(token());
                                                            #line 10536 "PrintCLike.cpp"
  append(L" == ");
                                                            #line 5980 "PrintCLike.cpp.template"
                                                                    print(format.toString<wchar_t>(grammar->externalTokenCode[plusplus]));
                                                                    if (isPython())
                                                                    {
                                                            #line 10542 "PrintCLike.cpp"
  append(L" or ");
                                                            #line 5983 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 10548 "PrintCLike.cpp"
  append(L" || ");
                                                            #line 5986 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(thiz());
                                                                    print(token());
                                                            #line 10554 "PrintCLike.cpp"
  append(L" == ");
                                                            #line 5989 "PrintCLike.cpp.template"
                                                                    print(format.toString<wchar_t>(grammar->externalTokenCode[minusminus]));
                                                            #line 10558 "PrintCLike.cpp"
  append(L")");
                                                            #line 5991 "PrintCLike.cpp.template"
                                                                    if (isPython())
                                                                    {
                                                            #line 10563 "PrintCLike.cpp"
  append(L" and ");
                                                            #line 5993 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 10569 "PrintCLike.cpp"
  append(L" && ");
                                                            #line 5996 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(thiz());
                                                            #line 10574 "PrintCLike.cpp"
  append(L"followsLineTerminator");
                                                            #line 5998 "PrintCLike.cpp.template"
                                                                    if (! isScala())
                                                                    {
                                                            #line 10579 "PrintCLike.cpp"
  append(L"()");
                                                            #line 6000 "PrintCLike.cpp.template"
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
                                                            #line 10593 "PrintCLike.cpp"
  append(L"\n");
  append(L"if ");
                                                            #line 6012 "PrintCLike.cpp.template"
                                                                    print(ifLeftParen());
                                                                    print(thiz());
                                                                    print(token());
                                                            #line 10600 "PrintCLike.cpp"
  append(L" != ");
                                                            #line 6015 "PrintCLike.cpp.template"
                                                                    print(format.toString<wchar_t>(grammar->externalTokenCode[semicolonToken]));
                                                                    if (isPython())
                                                                    {
                                                            #line 10606 "PrintCLike.cpp"
  append(L" and ");
                                                            #line 6018 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 10612 "PrintCLike.cpp"
  append(L" && ");
                                                            #line 6021 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(thiz());
                                                                    print(token());
                                                            #line 10618 "PrintCLike.cpp"
  append(L" >= 0");
                                                            #line 6025 "PrintCLike.cpp.template"
                                                                    if (isPython())
                                                                    {
                                                            #line 10623 "PrintCLike.cpp"
  append(L" and ");
                                                            #line 6027 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 10629 "PrintCLike.cpp"
  append(L" && ");
                                                            #line 6030 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(thiz());
                                                            #line 10634 "PrintCLike.cpp"
  append(L"followsLineTerminator");
                                                            #line 6032 "PrintCLike.cpp.template"
                                                                    if (! isScala())
                                                                    {
                                                            #line 10639 "PrintCLike.cpp"
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
                                                            #line 10654 "PrintCLike.cpp"
  append(L"\n");
  append(L"if ");
                                                            #line 6047 "PrintCLike.cpp.template"
                                                                    print(isPython() ? L"(" : ifLeftParen());
                                                                    print(thiz());
                                                                    print(token());
                                                            #line 10661 "PrintCLike.cpp"
  append(L" == ");
                                                            #line 6050 "PrintCLike.cpp.template"
                                                                    print(format.toString<wchar_t>(grammar->externalTokenCode[rbrace]));
                                                                    if (isPython())
                                                                    {
                                                            #line 10667 "PrintCLike.cpp"
  append(L" or");
                                                            #line 6053 "PrintCLike.cpp.template"
                                                                    }
                                                                    else if (isGo())
                                                                    {
                                                            #line 10673 "PrintCLike.cpp"
  append(L" ||");
                                                            #line 6056 "PrintCLike.cpp.template"
                                                                    }
                                                                    printCodeSequenceAnnotation(grammar->tokenSequence(rbrace));
                                                                    if (isGo() || isPython())
                                                                    {
                                                            #line 10680 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 6061 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 10687 "PrintCLike.cpp"
  append(L"\n");
  append(L" || ");
                                                            #line 6065 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(thiz());
                                                                    print(token());
                                                            #line 10694 "PrintCLike.cpp"
  append(L" == ");
                                                            #line 6068 "PrintCLike.cpp.template"
                                                                    print(format.toString<wchar_t>(grammar->externalTokenCode[eof]));
                                                                    if (isPython())
                                                                    {
                                                            #line 10700 "PrintCLike.cpp"
  append(L" or");
                                                            #line 6071 "PrintCLike.cpp.template"
                                                                    }
                                                                    else if (isGo())
                                                                    {
                                                            #line 10706 "PrintCLike.cpp"
  append(L" ||");
                                                            #line 6074 "PrintCLike.cpp.template"
                                                                    }
                                                                    printCodeSequenceAnnotation(grammar->tokenSequence(eof));
                                                                    if (isGo() || isPython())
                                                                    {
                                                            #line 10713 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 6079 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 10720 "PrintCLike.cpp"
  append(L"\n");
  append(L" || ");
                                                            #line 6083 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(thiz());
                                                                    print(token());
                                                            #line 10727 "PrintCLike.cpp"
  append(L" != ");
                                                            #line 6086 "PrintCLike.cpp.template"
                                                                    print(format.toString<wchar_t>(grammar->externalTokenCode[semicolonToken]));
                                                                    if (isPython())
                                                                    {
                                                            #line 10733 "PrintCLike.cpp"
  append(L" and ");
                                                            #line 6089 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 10739 "PrintCLike.cpp"
  append(L" && ");
                                                            #line 6092 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(thiz());
                                                                    print(token());
                                                            #line 10745 "PrintCLike.cpp"
  append(L" >= 0");
                                                            #line 6096 "PrintCLike.cpp.template"
                                                                    if (isPython())
                                                                    {
                                                            #line 10750 "PrintCLike.cpp"
  append(L" and ");
                                                            #line 6098 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 10756 "PrintCLike.cpp"
  append(L" && ");
                                                            #line 6101 "PrintCLike.cpp.template"
                                                                    }
                                                                    if (afterRbrace)
                                                                    {
                                                            #line 10762 "PrintCLike.cpp"
  append(L"(");
                                                            #line 6104 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(thiz());
                                                            #line 10767 "PrintCLike.cpp"
  append(L"followsLineTerminator");
                                                            #line 6106 "PrintCLike.cpp.template"
                                                                    if (! isScala())
                                                                    {
                                                            #line 10772 "PrintCLike.cpp"
  append(L"()");
                                                            #line 6108 "PrintCLike.cpp.template"
                                                                    }
                                                                    if (afterRbrace)
                                                                    {
                                                                      if (isPython())
                                                                      {
                                                            #line 10780 "PrintCLike.cpp"
  append(L" || ");
                                                            #line 6113 "PrintCLike.cpp.template"
                                                                      }
                                                                      else
                                                                      {
                                                            #line 10786 "PrintCLike.cpp"
  append(L" or ");
                                                            #line 6116 "PrintCLike.cpp.template"
                                                                      }
                                                                      if (isCpp() || isCSharp() || isPython() || (isJava() && codepoints))
                                                                      {
                                                                        print(thiz());
                                                            #line 10793 "PrintCLike.cpp"
  append(L"input[");
                                                            #line 6120 "PrintCLike.cpp.template"
                                                                        print(thiz());
                                                            #line 10797 "PrintCLike.cpp"
  append(L"b0]");
                                                            #line 6121 "PrintCLike.cpp.template"
                                                                      }
                                                                      else
                                                                      {
                                                                        print(thiz());
                                                            #line 10804 "PrintCLike.cpp"
  append(L"input.char");
                                                            #line 6125 "PrintCLike.cpp.template"
                                                                        if (isTypescript() || isJavascript() || isHaxe())
                                                                        {
                                                            #line 10809 "PrintCLike.cpp"
  append(L"Code");
                                                            #line 6128 "PrintCLike.cpp.template"
                                                                        }
                                                            #line 10813 "PrintCLike.cpp"
  append(L"At(");
                                                            #line 6129 "PrintCLike.cpp.template"
                                                                       print(thiz());
                                                            #line 10817 "PrintCLike.cpp"
  append(L"b0)");
                                                            #line 6131 "PrintCLike.cpp.template"
                                                                      }
                                                            #line 10821 "PrintCLike.cpp"
  append(L" == 0x7D)");
                                                            #line 6132 "PrintCLike.cpp.template"
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
                                                            #line 10834 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 6143 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 10839 "PrintCLike.cpp"
  append(L"l1 = ");
                                                            #line 6144 "PrintCLike.cpp.template"
                                                                print(format.toString<wchar_t>(grammar->externalTokenCode[semicolonToken]));
                                                                print(semicolon());
                                                            #line 10844 "PrintCLike.cpp"
  append(L" ");
                                                            #line 6146 "PrintCLike.cpp.template"
                                                                printCodeSequenceAnnotation(grammar->tokenSequence(semicolonToken));
                                                            #line 10848 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 6148 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 10853 "PrintCLike.cpp"
  append(L"e1 = ");
                                                            #line 6149 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 10857 "PrintCLike.cpp"
  append(L"b1");
                                                            #line 6150 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 10861 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 6152 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 10866 "PrintCLike.cpp"
  append(L"end = ");
                                                            #line 6153 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 10870 "PrintCLike.cpp"
  append(L"e1");
                                                            #line 6154 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                print(rightBrace());
                                                              }
                                                            }

// End
