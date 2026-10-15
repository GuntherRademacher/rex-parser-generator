// This file was generated on Thu Oct 15, 2026 12:16 (UTC+02) by REx v6.3-SNAPSHOT which is Copyright (c) 1979-2026 by Gunther Rademacher <grd@gmx.net>
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
  append(L"input.substring(e.getBegin(), ");
                                                            #line 2055 "PrintCLike.cpp.template"
                                        
                                                            #line 2999 "PrintCLike.cpp"
  append(L"Math.min(");
                                                            #line 2055 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 3003 "PrintCLike.cpp"
  append(L"input.length, e.getBegin() + 64)");
                                                            #line 2057 "PrintCLike.cpp.template"
                                                                }
                                                            #line 3007 "PrintCLike.cpp"
  append(L")\n");
  append(L"       + \"...\";\n");
  append(L"}");
                                                            #line 2060 "PrintCLike.cpp.template"
                                                                if (! isTypescript())
                                                                {
                                                            #line 3014 "PrintCLike.cpp"
  append(L";");
                                                            #line 2062 "PrintCLike.cpp.template"
                                                                }
                                                            #line 3018 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 2064 "PrintCLike.cpp.template"
                                                              }
                                                              else if (isJava())
                                                              {
                                                                openMethod(L"String[] ", L"static ", L"getExpectedTokenSet", L"ParseException e");
                                                                print(leftBrace());
                                                            #line 3026 "PrintCLike.cpp"
  append(L"\n");
  append(L"  String[] expected");
                                                            #line 2070 "PrintCLike.cpp.template"
                                                                if (useGlr)
                                                                {
                                                            #line 3032 "PrintCLike.cpp"
  append(L" = {}");
                                                            #line 2072 "PrintCLike.cpp.template"
                                                                }
                                                            #line 3036 "PrintCLike.cpp"
  append(L";\n");
  append(L"  if (e.getExpected() >= 0)\n");
  append(L"  {\n");
  append(L"    expected = new String[]{TOKEN[e.getExpected()]};\n");
  append(L"  }\n");
  append(L"  else");
                                                            #line 2078 "PrintCLike.cpp.template"
                                                                if (useGlr)
                                                                {
                                                            #line 3046 "PrintCLike.cpp"
  append(L" if (! e.isAmbiguousInput())");
                                                            #line 2080 "PrintCLike.cpp.template"
                                                                }
                                                            #line 3050 "PrintCLike.cpp"
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
                                                            #line 2091 "PrintCLike.cpp.template"
                                                                if (useGlr)
                                                                {
                                                            #line 3064 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if ");
                                                            #line 2094 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                            #line 3069 "PrintCLike.cpp"
  append(L"e.isAmbiguousInput()");
                                                            #line 2095 "PrintCLike.cpp.template"
                                                                  print(ifRightParen());
                                                                  printIndented(1, leftBrace());
                                                            #line 3074 "PrintCLike.cpp"
  append(L"\n");
  append(L"    message += \"\\n\"");
                                                            #line 2098 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                            #line 3079 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 2100 "PrintCLike.cpp.template"
                                                                  printIndented(1, elseWithBraces());
                                                                  increaseIndent();
                                                                }
                                                            #line 3086 "PrintCLike.cpp"
  append(L"\n");
  append(L"  String[] tokenSet = getExpectedTokenSet(e);\n");
  append(L"  String found = getOffendingToken(e);\n");
  append(L"  int size = e.getEnd() - e.getBegin();\n");
  append(L"  message += (found == null ? \"\" : \", found \" + found)\n");
  append(L"          + \"\\nwhile expecting \"\n");
  append(L"          + (tokenSet.length == 1 ? tokenSet[0] : java.util.Arrays.toString(tokenSet))\n");
  append(L"          + \"\\n\"\n");
  append(L"          + (size == 0 || found != null ? \"\" : \"after successfully scanning \" + size + \" characters beginning \");");
                                                            #line 2112 "PrintCLike.cpp.template"
                                                                if (useGlr)
                                                                {
                                                                  decreaseIndent();
                                                            #line 3100 "PrintCLike.cpp"
  append(L"\n");
  append(L"  }");
                                                            #line 2116 "PrintCLike.cpp.template"
                                                                }
                                                                if (codepoints)
                                                                {
                                                            #line 3107 "PrintCLike.cpp"
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
                                                            #line 2128 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 3123 "PrintCLike.cpp"
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
                                                            #line 2140 "PrintCLike.cpp.template"
                                                                }
                                                                if (! interfaceName.empty())
                                                                {
                                                            #line 3139 "PrintCLike.cpp"
  append(L"\n");
  append(L"public void parse()\n");
  append(L"{\n");
  append(L"  parse_");
                                                            #line 2146 "PrintCLike.cpp.template"
                                                                  print(Format::acceptableName<WString>(grammar->startSymbol()->name).c_str());
                                                            #line 3146 "PrintCLike.cpp"
  append(L"();\n");
  append(L"}\n");
                                                            #line 2149 "PrintCLike.cpp.template"
                                                                }
                                                              }
                                                              else if (isCSharp())
                                                              {
                                                                openMethod(L"static String[] ", L"", L"getExpectedTokenSet", L"ParseException e");
                                                                print(leftBrace());
                                                            #line 3156 "PrintCLike.cpp"
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
                                                            #line 2171 "PrintCLike.cpp.template"
                                                                if (useGlr)
                                                                {
                                                            #line 3176 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if (e.isAmbiguousInput())\n");
  append(L"  {\n");
  append(L"    message += \"\\n\";\n");
  append(L"  }\n");
  append(L"  else\n");
  append(L"  {");
                                                            #line 2179 "PrintCLike.cpp.template"
                                                                  increaseIndent();
                                                                }
                                                            #line 3187 "PrintCLike.cpp"
  append(L"\n");
  append(L"  String[] tokenSet = getExpectedTokenSet(e);\n");
  append(L"  String found = getOffendingToken(e);\n");
  append(L"  int size = e.getEnd() - e.getBegin();\n");
  append(L"  message += (found == null ? \"\" : \", found \" + found)\n");
  append(L"          + \"\\nwhile expecting \"\n");
  append(L"          + (tokenSet.Length == 1 ? tokenSet[0] : (\"[\" + String.Join(\", \", tokenSet) + \"]\"))\n");
  append(L"          + \"\\n\"\n");
  append(L"          + (size == 0 || found != null ? \"\" : \"after successfully scanning \" + size + \" characters beginning \");");
                                                            #line 2190 "PrintCLike.cpp.template"
                                                                if (useGlr)
                                                                {
                                                                  decreaseIndent();
                                                            #line 3201 "PrintCLike.cpp"
  append(L"\n");
  append(L"  }");
                                                            #line 2194 "PrintCLike.cpp.template"
                                                                }
                                                            #line 3206 "PrintCLike.cpp"
  append(L"\n");
  append(L"  String prefix = input.Substring(0, e.getBegin());\n");
  append(L"  int line = prefix.Length - prefix.Replace(\"\\n\", \"\").Length + 1;\n");
  append(L"  int column = prefix.Length - prefix.LastIndexOf('\\n');\n");
  append(L"  return message\n");
  append(L"       + \"at line \" + line + \", column \" + column + \":\\n...\"\n");
  append(L"       + input.Substring(e.getBegin(), Math.Min(input.Length, e.getBegin() + 64) - e.getBegin())\n");
  append(L"       + \"...\";\n");
  append(L"}\n");
                                                            #line 2204 "PrintCLike.cpp.template"
                                                                if (! interfaceName.empty())
                                                                {
                                                            #line 3219 "PrintCLike.cpp"
  append(L"\n");
  append(L"public void parse()\n");
  append(L"{\n");
  append(L"  parse_");
                                                            #line 2209 "PrintCLike.cpp.template"
                                                                  print(Format::acceptableName<WString>(grammar->startSymbol()->name).c_str());
                                                            #line 3226 "PrintCLike.cpp"
  append(L"();\n");
  append(L"}\n");
                                                            #line 2212 "PrintCLike.cpp.template"
                                                                }
                                                              }
                                                              else if (isGo())
                                                              {
                                                            #line 3234 "PrintCLike.cpp"
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
                                                            #line 2226 "PrintCLike.cpp.template"
                                                                print(className.c_str());
                                                            #line 3248 "PrintCLike.cpp"
  append(L") GetErrorMessage(e ParseError) string {\n");
  append(L"  message := e.Error()");
                                                            #line 2229 "PrintCLike.cpp.template"
                                                                if (useGlr)
                                                                {
                                                            #line 3254 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if e.IsAmbiguousInput() {\n");
  append(L"    message += \"\\n\"\n");
  append(L"  } else {");
                                                            #line 2234 "PrintCLike.cpp.template"
                                                                  increaseIndent();
                                                                }
                                                            #line 3262 "PrintCLike.cpp"
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
                                                            #line 2262 "PrintCLike.cpp.template"
                                                                if (useGlr)
                                                                {
                                                                  decreaseIndent();
                                                            #line 3294 "PrintCLike.cpp"
  append(L"\n");
  append(L"  }");
                                                            #line 2266 "PrintCLike.cpp.template"
                                                                }
                                                            #line 3299 "PrintCLike.cpp"
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
                                                            #line 2291 "PrintCLike.cpp.template"
                                                                if (! interfaceName.empty())
                                                                {
                                                            #line 3327 "PrintCLike.cpp"
  append(L"\n");
  append(L"public void parse()\n");
  append(L"{\n");
  append(L"  parse_");
                                                            #line 2296 "PrintCLike.cpp.template"
                                                                  print(Format::acceptableName<WString>(grammar->startSymbol()->name).c_str());
                                                            #line 3334 "PrintCLike.cpp"
  append(L"();\n");
  append(L"}\n");
                                                            #line 2299 "PrintCLike.cpp.template"
                                                                }
                                                              }
                                                              else if (isPython())
                                                              {
                                                            #line 3342 "PrintCLike.cpp"
  append(L"\n");
  append(L"@staticmethod\n");
  append(L"def getExpectedTokenSet(e):\n");
  append(L"  if e.expected < 0:\n");
  append(L"    return ");
                                                            #line 2307 "PrintCLike.cpp.template"
                                                                print(className.c_str());
                                                            #line 3350 "PrintCLike.cpp"
  append(L".getTokenSet(- e.state)\n");
  append(L"  else:\n");
  append(L"    return [");
                                                            #line 2310 "PrintCLike.cpp.template"
                                                                print(className.c_str());
                                                            #line 3356 "PrintCLike.cpp"
  append(L".TOKEN[e.expected]]\n");
  append(L"\n");
  append(L"def getErrorMessage(self, e):\n");
  append(L"  message = e.error()");
                                                            #line 2314 "PrintCLike.cpp.template"
                                                                if (useGlr)
                                                                {
                                                            #line 3364 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if e.isAmbiguousInput():\n");
  append(L"    message += \"\\n\"\n");
  append(L"  else:");
                                                            #line 2319 "PrintCLike.cpp.template"
                                                                  increaseIndent();
                                                                }
                                                            #line 3372 "PrintCLike.cpp"
  append(L"\n");
  append(L"  found = ");
                                                            #line 2322 "PrintCLike.cpp.template"
                                                                print(className.c_str());
                                                            #line 3377 "PrintCLike.cpp"
  append(L".getOffendingToken(e)\n");
  append(L"  if found != \"\":\n");
  append(L"    message += \", found \"\n");
  append(L"    message += found\n");
  append(L"  expected = ");
                                                            #line 2327 "PrintCLike.cpp.template"
                                                                print(className.c_str());
                                                            #line 3385 "PrintCLike.cpp"
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
                                                            #line 2344 "PrintCLike.cpp.template"
                                                                if (useGlr)
                                                                {
                                                                  decreaseIndent();
                                                                }
                                                            #line 3408 "PrintCLike.cpp"
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
                                                            #line 2368 "PrintCLike.cpp.template"
                                                                if (! interfaceName.empty())
                                                                {
                                                            #line 3432 "PrintCLike.cpp"
  append(L"\n");
  append(L"public void parse()\n");
  append(L"{\n");
  append(L"  parse_");
                                                            #line 2373 "PrintCLike.cpp.template"
                                                                  print(Format::acceptableName<WString>(grammar->startSymbol()->name).c_str());
                                                            #line 3439 "PrintCLike.cpp"
  append(L"();\n");
  append(L"}\n");
                                                            #line 2376 "PrintCLike.cpp.template"
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
                                                            #line 3455 "PrintCLike.cpp"
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
                                                            #line 2399 "PrintCLike.cpp.template"
                                                                print(isGo() ? L"token" : L"TOKEN");
                                                            #line 3470 "PrintCLike.cpp"
  append(L"[e.expected];\n");
  append(L"    set[1] = 0;\n");
  append(L"  }\n");
  append(L"}\n");
  append(L"\n");
  append(L"static std::");
                                                            #line 2405 "PrintCLike.cpp.template"
                                                                if (stringIntroducer()[0]) append(L"w");
                                                            #line 3479 "PrintCLike.cpp"
  append(L"string to_");
                                                            #line 2406 "PrintCLike.cpp.template"
                                                                if (stringIntroducer()[0]) append(L"w");
                                                            #line 3483 "PrintCLike.cpp"
  append(L"string(int i)\n");
  append(L"{\n");
  append(L"  const ");
                                                            #line 2409 "PrintCLike.cpp.template"
                                                                if (stringIntroducer()[0]) append(L"w");
                                                            #line 3489 "PrintCLike.cpp"
  append(L"char");
                                                            #line 2410 "PrintCLike.cpp.template"
                                                                if (stringIntroducer()[0]) append(L"_t");
                                                            #line 3493 "PrintCLike.cpp"
  append(L" *sign = i < 0 ? ");
                                                            #line 2411 "PrintCLike.cpp.template"
                                                                append(stringIntroducer());
                                                            #line 3497 "PrintCLike.cpp"
  append(L"\"-\" : ");
                                                            #line 2412 "PrintCLike.cpp.template"
                                                                append(stringIntroducer());
                                                            #line 3501 "PrintCLike.cpp"
  append(L"\"\";\n");
  append(L"  std::");
                                                            #line 2414 "PrintCLike.cpp.template"
                                                                if (stringIntroducer()[0]) append(L"w");
                                                            #line 3506 "PrintCLike.cpp"
  append(L"string a;\n");
  append(L"  do\n");
  append(L"  {\n");
  append(L"    a += ");
                                                            #line 2418 "PrintCLike.cpp.template"
                                                                append(stringIntroducer());
                                                            #line 3513 "PrintCLike.cpp"
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
                                                            #line 2428 "PrintCLike.cpp.template"
                                                                if (stringIntroducer()[0]) append(L"w");
                                                            #line 3526 "PrintCLike.cpp"
  append(L"string getErrorMessage(const ParseException &e)\n");
  append(L"{\n");
  append(L"  std::");
                                                            #line 2431 "PrintCLike.cpp.template"
                                                                if (stringIntroducer()[0]) append(L"w");
                                                            #line 3532 "PrintCLike.cpp"
  append(L"string message(e.getMessage());");
                                                            #line 2432 "PrintCLike.cpp.template"
                                                                if (useGlr)
                                                                {
                                                            #line 3537 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if (e.isAmbiguousInput())\n");
  append(L"  {\n");
  append(L"    message += ");
                                                            #line 2437 "PrintCLike.cpp.template"
                                                                  print(stringIntroducer());
                                                            #line 3544 "PrintCLike.cpp"
  append(L"\"\\n\";\n");
  append(L"  }\n");
  append(L"  else\n");
  append(L"  {");
                                                            #line 2441 "PrintCLike.cpp.template"
                                                                  increaseIndent();
                                                                }
                                                            #line 3552 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 2444 "PrintCLike.cpp.template"
                                                                print(stringType());
                                                            #line 3557 "PrintCLike.cpp"
  append(L"found = getOffendingToken(e);\n");
  append(L"  if (found != 0)\n");
  append(L"  {\n");
  append(L"    message += ");
                                                            #line 2448 "PrintCLike.cpp.template"
                                                                print(stringIntroducer());
                                                            #line 3564 "PrintCLike.cpp"
  append(L"\", found \";\n");
  append(L"    message += found;\n");
  append(L"  }\n");
  append(L"  ");
                                                            #line 2452 "PrintCLike.cpp.template"
                                                                print(stringType());
                                                            #line 3571 "PrintCLike.cpp"
  append(L"expected[64];\n");
  append(L"  getExpectedTokenSet(e, expected, sizeof expected / sizeof *expected);\n");
  append(L"  message += ");
                                                            #line 2455 "PrintCLike.cpp.template"
                                                                print(stringIntroducer());
                                                            #line 3577 "PrintCLike.cpp"
  append(L"\"\\nwhile expecting \";\n");
  append(L"  ");
                                                            #line 2457 "PrintCLike.cpp.template"
                                                                print(stringType());
                                                            #line 3582 "PrintCLike.cpp"
  append(L"delimiter(expected[1] ? ");
                                                            #line 2458 "PrintCLike.cpp.template"
                                                                print(stringIntroducer());
                                                            #line 3586 "PrintCLike.cpp"
  append(L"\"[\" : ");
                                                            #line 2459 "PrintCLike.cpp.template"
                                                                print(stringIntroducer());
                                                            #line 3590 "PrintCLike.cpp"
  append(L"\"\");\n");
  append(L"  for (");
                                                            #line 2461 "PrintCLike.cpp.template"
                                                                print(stringType());
                                                            #line 3595 "PrintCLike.cpp"
  append(L"*x = expected; *x; ++x)\n");
  append(L"  {\n");
  append(L"    message += delimiter;\n");
  append(L"    message += *x;\n");
  append(L"    delimiter = ");
                                                            #line 2466 "PrintCLike.cpp.template"
                                                                print(stringIntroducer());
                                                            #line 3603 "PrintCLike.cpp"
  append(L"\", \";\n");
  append(L"  }\n");
  append(L"  message += expected[1] ? ");
                                                            #line 2469 "PrintCLike.cpp.template"
                                                                print(stringIntroducer());
                                                            #line 3609 "PrintCLike.cpp"
  append(L"\"]\\n\" : ");
                                                            #line 2470 "PrintCLike.cpp.template"
                                                                print(stringIntroducer());
                                                            #line 3613 "PrintCLike.cpp"
  append(L"\"\\n\";\n");
  append(L"  int size = e.getEnd() - e.getBegin();\n");
  append(L"  if (size != 0 && found == 0)\n");
  append(L"  {\n");
  append(L"    message += ");
                                                            #line 2475 "PrintCLike.cpp.template"
                                                                print(stringIntroducer());
                                                            #line 3621 "PrintCLike.cpp"
  append(L"\"after successfully scanning \";\n");
  append(L"    message += to_");
                                                            #line 2477 "PrintCLike.cpp.template"
                                                                if (stringIntroducer()[0]) append(L"w");
                                                            #line 3626 "PrintCLike.cpp"
  append(L"string(size);\n");
  append(L"    message += ");
                                                            #line 2479 "PrintCLike.cpp.template"
                                                                print(stringIntroducer());
                                                            #line 3631 "PrintCLike.cpp"
  append(L"\" characters beginning \";\n");
  append(L"  }");
                                                            #line 2481 "PrintCLike.cpp.template"
                                                                if (useGlr)
                                                                {
                                                                  decreaseIndent();
                                                            #line 3638 "PrintCLike.cpp"
  append(L"\n");
  append(L"  }");
                                                            #line 2485 "PrintCLike.cpp.template"
                                                                }
                                                            #line 3643 "PrintCLike.cpp"
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
                                                            #line 2501 "PrintCLike.cpp.template"
                                                                print(stringIntroducer());
                                                            #line 3662 "PrintCLike.cpp"
  append(L"\"at line \";\n");
  append(L"  message += to_");
                                                            #line 2503 "PrintCLike.cpp.template"
                                                              if (stringIntroducer()[0]) append(L"w");
                                                            #line 3667 "PrintCLike.cpp"
  append(L"string(line);\n");
  append(L"  message += ");
                                                            #line 2505 "PrintCLike.cpp.template"
                                                              print(stringIntroducer());
                                                            #line 3672 "PrintCLike.cpp"
  append(L"\", column \";\n");
  append(L"  message += to_");
                                                            #line 2507 "PrintCLike.cpp.template"
                                                              if (stringIntroducer()[0]) append(L"w");
                                                            #line 3677 "PrintCLike.cpp"
  append(L"string(column);\n");
  append(L"  message += ");
                                                            #line 2509 "PrintCLike.cpp.template"
                                                                print(stringIntroducer());
                                                            #line 3682 "PrintCLike.cpp"
  append(L"\":\\n...\";\n");
  append(L"  ");
                                                            #line 2511 "PrintCLike.cpp.template"
                                                                print(stringType());
                                                            #line 3687 "PrintCLike.cpp"
  append(L"w = input + e.getBegin();\n");
  append(L"  for (int i = 0; i < 64 && *w; ++i)\n");
  append(L"  {\n");
  append(L"    message += *w++;\n");
  append(L"  }\n");
  append(L"  message += ");
                                                            #line 2517 "PrintCLike.cpp.template"
                                                                print(stringIntroducer());
                                                            #line 3696 "PrintCLike.cpp"
  append(L"\"...\";\n");
  append(L"  return message;\n");
  append(L"}\n");
                                                            #line 2521 "PrintCLike.cpp.template"
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
                                                            #line 3725 "PrintCLike.cpp"
  append(L"\n");
  append(L"  fprintf(stderr, \"  <%s %snonterminal=\\\"%s\\\"\", ");
                                                            #line 2546 "PrintCLike.cpp.template"
                                                                  if (stringIntroducer()[0])
                                                                  {
                                                            #line 3731 "PrintCLike.cpp"
  append(L"Utf8Encoder::encode(");
                                                            #line 2548 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 3735 "PrintCLike.cpp"
  append(L"method");
                                                            #line 2549 "PrintCLike.cpp.template"
                                                                  if (stringIntroducer()[0])
                                                                  {
                                                            #line 3740 "PrintCLike.cpp"
  append(L").c_str()");
                                                            #line 2551 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 3744 "PrintCLike.cpp"
  append(L", ");
                                                            #line 2552 "PrintCLike.cpp.template"
                                                                  if (stringIntroducer()[0])
                                                                  {
                                                            #line 3749 "PrintCLike.cpp"
  append(L"Utf8Encoder::encode(");
                                                            #line 2554 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 3753 "PrintCLike.cpp"
  append(L"occasion");
                                                            #line 2555 "PrintCLike.cpp.template"
                                                                  if (stringIntroducer()[0])
                                                                  {
                                                            #line 3758 "PrintCLike.cpp"
  append(L").c_str()");
                                                            #line 2557 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 3762 "PrintCLike.cpp"
  append(L", ");
                                                            #line 2558 "PrintCLike.cpp.template"
                                                                  if (stringIntroducer()[0])
                                                                  {
                                                            #line 3767 "PrintCLike.cpp"
  append(L"Utf8Encoder::encode(");
                                                            #line 2560 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 3771 "PrintCLike.cpp"
  append(L"name");
                                                            #line 2561 "PrintCLike.cpp.template"
                                                                  if (stringIntroducer()[0])
                                                                  {
                                                            #line 3776 "PrintCLike.cpp"
  append(L").c_str()");
                                                            #line 2563 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 3780 "PrintCLike.cpp"
  append(L");\n");
  append(L"  if (l1 != 0)\n");
  append(L"    fprintf(stderr, \" input=\\\"%s\\\"\", ");
                                                            #line 2566 "PrintCLike.cpp.template"
                                                                  if (stringIntroducer()[0])
                                                                  {
                                                            #line 3787 "PrintCLike.cpp"
  append(L"Utf8Encoder::encode(");
                                                            #line 2568 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 3791 "PrintCLike.cpp"
  append(L"xmlEscape(lookaheadString().c_str(), 0).c_str()");
                                                            #line 2570 "PrintCLike.cpp.template"
                                                                  if (stringIntroducer()[0])
                                                                  {
                                                            #line 3796 "PrintCLike.cpp"
  append(L").c_str()");
                                                            #line 2572 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 3800 "PrintCLike.cpp"
  append(L");\n");
  append(L"  fprintf(stderr, \"/>\\n\");");
                                                            #line 2574 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                                  if (isHaxe())
                                                                  {
                                                            #line 3809 "PrintCLike.cpp"
  append(L"\n");
  append(L"  trace(");
                                                            #line 2580 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                                    if (isGo())
                                                                    {
                                                            #line 3818 "PrintCLike.cpp"
  append(L"\n");
  append(L"  var inputAttr string\n");
  append(L"  if (this.l1 == 0) {\n");
  append(L"    inputAttr = \"\"\n");
  append(L"  } else {\n");
  append(L"    inputAttr = \" input=\\\"\" + xmlEscape(this.lookaheadString()) + \"\\\"\"\n");
  append(L"  }");
                                                            #line 2591 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 3828 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 2593 "PrintCLike.cpp.template"
                                                                    print(writeTrace());
                                                                  }
                                                            #line 3834 "PrintCLike.cpp"
  append(L"\"  <\" + method + \" \" + occasion + \"nonterminal=\\\"\" + name + \"\\\"\" + ");
                                                            #line 2596 "PrintCLike.cpp.template"
                                                                  if (isGo())
                                                                  {
                                                            #line 3839 "PrintCLike.cpp"
  append(L"inputAttr");
                                                            #line 2598 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 3845 "PrintCLike.cpp"
  append(L"(");
                                                            #line 2601 "PrintCLike.cpp.template"
                                                                    if (isScala())
                                                                    {
                                                            #line 3850 "PrintCLike.cpp"
  append(L"if (l1 == 0) \"\" else");
                                                            #line 2603 "PrintCLike.cpp.template"
                                                                    }
                                                                    else if (isPython())
                                                                    {
                                                            #line 3856 "PrintCLike.cpp"
  append(L"\"\" if self.l1 == 0 else");
                                                            #line 2606 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                                      print(thiz());
                                                            #line 3863 "PrintCLike.cpp"
  append(L"l1 == 0 ? \"\" :");
                                                            #line 2610 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 3867 "PrintCLike.cpp"
  append(L" \" input=\\\"\" + ");
                                                            #line 2611 "PrintCLike.cpp.template"
                                                                    print(staticPrefix());
                                                            #line 3871 "PrintCLike.cpp"
  append(L"xmlEscape(");
                                                            #line 2612 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 3875 "PrintCLike.cpp"
  append(L"lookaheadString");
                                                            #line 2613 "PrintCLike.cpp.template"
                                                                    if (! isScala()) print(L"()");
                                                            #line 3879 "PrintCLike.cpp"
  append(L") + \"\\\"\")");
                                                            #line 2614 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 3883 "PrintCLike.cpp"
  append(L" + \"/>");
                                                            #line 2615 "PrintCLike.cpp.template"
                                                                  if (isHaxe()) print(L"\")"); else print(L"\\n\"");
                                                                  print(endWriteTrace());
                                                                  print(semicolon());
                                                                }
                                                                print(rightBrace());
                                                            #line 3891 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 2621 "PrintCLike.cpp.template"
                                                                decreaseIndent();
                                                              }

                                                              if (grammar->automaticSemicolonInsertion)
                                                              {
                                                                if (! isGo())
                                                                  increaseIndent();
                                                                openMethod(boolType(), L"", L"followsLineTerminator", L"");
                                                                print(leftBrace());
                                                                increaseIndent();
                                                            #line 3904 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 2632 "PrintCLike.cpp.template"
                                                                print(intVar());
                                                            #line 3908 "PrintCLike.cpp"
  append(L"i");
                                                            #line 2633 "PrintCLike.cpp.template"
                                                                print(assign());
                                                                print(thiz());
                                                            #line 3913 "PrintCLike.cpp"
  append(L"e0");
                                                            #line 2635 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 3917 "PrintCLike.cpp"
  append(L"\n");
  append(L"if ");
                                                            #line 2637 "PrintCLike.cpp.template"
                                                                print(ifLeftParen());
                                                                print(thiz());
                                                            #line 3923 "PrintCLike.cpp"
  append(L"e0 == ");
                                                            #line 2639 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 3927 "PrintCLike.cpp"
  append(L"b1");
                                                            #line 2640 "PrintCLike.cpp.template"
                                                                print(ifRightParen());
                                                                print(leftBrace());
                                                            #line 3932 "PrintCLike.cpp"
  append(L"\n");
  append(L"  i = ");
                                                            #line 2643 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 3937 "PrintCLike.cpp"
  append(L"b0");
                                                            #line 2644 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                print(rightBrace());
                                                                if (isScala() || isHaxe() || isPython())
                                                                {
                                                            #line 3944 "PrintCLike.cpp"
  append(L"\n");
  append(L"while ");
                                                            #line 2649 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 3951 "PrintCLike.cpp"
  append(L"\n");
  append(L"for ");
                                                            #line 2653 "PrintCLike.cpp.template"
                                                                }
                                                                print(ifLeftParen());
                                                                if (! (isScala() || isHaxe() || isPython()))
                                                                {
                                                            #line 3959 "PrintCLike.cpp"
  append(L"; ");
                                                            #line 2657 "PrintCLike.cpp.template"
                                                                }
                                                            #line 3963 "PrintCLike.cpp"
  append(L"i < ");
                                                            #line 2658 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 3967 "PrintCLike.cpp"
  append(L"b1");
                                                            #line 2659 "PrintCLike.cpp.template"
                                                                if (! (isScala() || isHaxe() || isPython()))
                                                                {
                                                            #line 3972 "PrintCLike.cpp"
  append(L"; i++");
                                                            #line 2661 "PrintCLike.cpp.template"
                                                                }
                                                                print(ifRightParen());
                                                                print(leftBrace());
                                                                increaseIndent();
                                                                if (isGo())
                                                                {
                                                            #line 3981 "PrintCLike.cpp"
  append(L"\n");
  append(L"c, _ := utf8.DecodeRuneInString(this.input[i:])");
                                                            #line 2668 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 3988 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 2672 "PrintCLike.cpp.template"
                                                                  print(intVar());
                                                            #line 3992 "PrintCLike.cpp"
  append(L"c");
                                                            #line 2673 "PrintCLike.cpp.template"
                                                                  print(assign());
                                                                  if (isCpp() || isCSharp() || isPython() || (isJava() && codepoints))
                                                                  {
                                                                    if (isPython())
                                                                    {
                                                            #line 4000 "PrintCLike.cpp"
  append(L"ord(");
                                                            #line 2678 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(thiz());
                                                            #line 4005 "PrintCLike.cpp"
  append(L"input[i]");
                                                            #line 2680 "PrintCLike.cpp.template"
                                                                    if (isPython())
                                                                    {
                                                            #line 4010 "PrintCLike.cpp"
  append(L")");
                                                            #line 2682 "PrintCLike.cpp.template"
                                                                    }
                                                                  }
                                                                  else if (isHaxe())
                                                                  {
                                                            #line 4017 "PrintCLike.cpp"
  append(L"input.get(i)");
                                                            #line 2686 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                                    print(thiz());
                                                            #line 4024 "PrintCLike.cpp"
  append(L"input.char");
                                                            #line 2690 "PrintCLike.cpp.template"
                                                                    if (isTypescript() || isJavascript())
                                                                    {
                                                            #line 4029 "PrintCLike.cpp"
  append(L"Code");
                                                            #line 2692 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 4033 "PrintCLike.cpp"
  append(L"At(i)");
                                                            #line 2693 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(semicolon());
                                                                }
                                                            #line 4039 "PrintCLike.cpp"
  append(L"\n");
  append(L"if ");
                                                            #line 2697 "PrintCLike.cpp.template"
                                                                print(ifLeftParen());
                                                            #line 4044 "PrintCLike.cpp"
  append(L"c == 0xA ");
                                                            #line 2699 "PrintCLike.cpp.template"
                                                                if (isPython())
                                                                {
                                                            #line 4049 "PrintCLike.cpp"
  append(L"or");
                                                            #line 2701 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 4055 "PrintCLike.cpp"
  append(L"||");
                                                            #line 2704 "PrintCLike.cpp.template"
                                                                }
                                                            #line 4059 "PrintCLike.cpp"
  append(L" c == 0xD ");
                                                            #line 2706 "PrintCLike.cpp.template"
                                                                if (isPython())
                                                                {
                                                            #line 4064 "PrintCLike.cpp"
  append(L"or");
                                                            #line 2708 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 4070 "PrintCLike.cpp"
  append(L"||");
                                                            #line 2711 "PrintCLike.cpp.template"
                                                                }
                                                            #line 4074 "PrintCLike.cpp"
  append(L" c == 0x2028 ");
                                                            #line 2713 "PrintCLike.cpp.template"
                                                                if (isPython())
                                                                {
                                                            #line 4079 "PrintCLike.cpp"
  append(L"or");
                                                            #line 2715 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 4085 "PrintCLike.cpp"
  append(L"||");
                                                            #line 2718 "PrintCLike.cpp.template"
                                                                }
                                                            #line 4089 "PrintCLike.cpp"
  append(L" c == 0x2029");
                                                            #line 2719 "PrintCLike.cpp.template"
                                                                print(ifRightParen());
                                                                print(leftBrace());
                                                            #line 4094 "PrintCLike.cpp"
  append(L"\n");
  append(L"  return ");
                                                            #line 2722 "PrintCLike.cpp.template"
                                                                if (isPython())
                                                                {
                                                            #line 4100 "PrintCLike.cpp"
  append(L"T");
                                                            #line 2724 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 4106 "PrintCLike.cpp"
  append(L"t");
                                                            #line 2727 "PrintCLike.cpp.template"
                                                                }
                                                            #line 4110 "PrintCLike.cpp"
  append(L"rue");
                                                            #line 2728 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                print(rightBrace());
                                                                if (isScala() || isPython())
                                                                {
                                                            #line 4117 "PrintCLike.cpp"
  append(L"\n");
  append(L"i += 1");
                                                            #line 2734 "PrintCLike.cpp.template"
                                                                }
                                                                else if (isHaxe())
                                                                {
                                                            #line 4124 "PrintCLike.cpp"
  append(L"\n");
  append(L"++i;");
                                                            #line 2738 "PrintCLike.cpp.template"
                                                                }

                                                                decreaseIndent();
                                                                print(rightBrace());
                                                            #line 4132 "PrintCLike.cpp"
  append(L"\n");
  append(L"return ");
                                                            #line 2743 "PrintCLike.cpp.template"
                                                                if (isPython())
                                                                {
                                                            #line 4138 "PrintCLike.cpp"
  append(L"F");
                                                            #line 2745 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 4144 "PrintCLike.cpp"
  append(L"f");
                                                            #line 2748 "PrintCLike.cpp.template"
                                                                }
                                                            #line 4148 "PrintCLike.cpp"
  append(L"alse");
                                                            #line 2749 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                decreaseIndent();
                                                                print(rightBrace());
                                                            #line 4154 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 2753 "PrintCLike.cpp.template"
                                                                if (! isGo())
                                                                  decreaseIndent();
                                                              }

                                                              if (isScala())
                                                              {
                                                            #line 4163 "PrintCLike.cpp"
  append(L"\n");
  append(L"  def getErrorMessage(e: ");
                                                            #line 2760 "PrintCLike.cpp.template"
                                                                print(className.c_str());
                                                            #line 4168 "PrintCLike.cpp"
  append(L".ParseException) = {\n");
  append(L"    var message = e.getMessage");
                                                            #line 2762 "PrintCLike.cpp.template"
                                                                if (useGlr)
                                                                {
                                                            #line 4174 "PrintCLike.cpp"
  append(L"\n");
  append(L"    if (e.isAmbiguousInput)\n");
  append(L"      message += \"\\n\"\n");
  append(L"    else {");
                                                            #line 2767 "PrintCLike.cpp.template"
                                                                  increaseIndent();
                                                                }
                                                            #line 4182 "PrintCLike.cpp"
  append(L"\n");
  append(L"    val tokenSet = ");
                                                            #line 2770 "PrintCLike.cpp.template"
                                                                print(className.c_str());
                                                            #line 4187 "PrintCLike.cpp"
  append(L".getExpectedTokenSet(e)\n");
  append(L"    val found = ");
                                                            #line 2772 "PrintCLike.cpp.template"
                                                                print(className.c_str());
                                                            #line 4192 "PrintCLike.cpp"
  append(L".getOffendingToken(e)\n");
  append(L"    val size = e.end - e.begin\n");
  append(L"    message += (if (found == null) \"\" else \", found \" + found) + \"\\nwhile expecting \" +\n");
  append(L"      (if (tokenSet.length == 1) tokenSet(0) else \"[\" + (tokenSet mkString \", \") + \"]\") + \"\\n\" +\n");
  append(L"      (if (size == 0 || found != null) \"\" else \"after successfully scanning \" + size + \" characters beginning \")");
                                                            #line 2778 "PrintCLike.cpp.template"
                                                                if (useGlr)
                                                                {
                                                            #line 4201 "PrintCLike.cpp"
  append(L"\n");
  append(L"    }");
                                                            #line 2781 "PrintCLike.cpp.template"
                                                                  decreaseIndent();
                                                                }
                                                            #line 4207 "PrintCLike.cpp"
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
                                                            #line 2791 "PrintCLike.cpp.template"
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
                                                            #line 4255 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 2828 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 4260 "PrintCLike.cpp"
  append(L"top += ");
                                                            #line 2829 "PrintCLike.cpp.template"
                                                                  if (tree)
                                                                  {
                                                            #line 4265 "PrintCLike.cpp"
  append(L"3");
                                                            #line 2831 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 4271 "PrintCLike.cpp"
  append(L"2");
                                                            #line 2834 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(semicolon());
                                                                  if (isJava())
                                                                  {
                                                            #line 4278 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if (top >= iStack.length)\n");
  append(L"  {\n");
  append(L"    iStack = Arrays.copyOf(iStack, iStack.length << 1);\n");
  append(L"  }");
                                                            #line 2842 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isCSharp())
                                                                  {
                                                            #line 4288 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if (top >= iStack.Length)\n");
  append(L"  {\n");
  append(L"    Array.Resize(ref iStack, iStack.Length << 1);\n");
  append(L"  }");
                                                            #line 2849 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isCpp())
                                                                  {
                                                            #line 4298 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if (top >= (int) iStack.size())\n");
  append(L"    iStack.resize(iStack.size() == 0 ? ");
                                                            #line 2854 "PrintCLike.cpp.template"
                                                                    print(tree ? L"192" : L"128");
                                                            #line 4304 "PrintCLike.cpp"
  append(L" : iStack.size() << 1);");
                                                            #line 2856 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isScala())
                                                                  {
                                                            #line 4310 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if (top >= iStack.size) {\n");
  append(L"    val newStack = new Array[Int](iStack.size << 1)\n");
  append(L"    Array.copy(iStack, 0, newStack, 0, iStack.size)\n");
  append(L"    iStack = newStack\n");
  append(L"  }");
                                                            #line 2864 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isGo())
                                                                  {
                                                            #line 4321 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if this.top >= len(this.iStack) {\n");
  append(L"    this.iStack = append(this.iStack, this.iStack...)\n");
  append(L"  }");
                                                            #line 2870 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isPython())
                                                                  {
                                                            #line 4330 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if self.top >= len(self.iStack):\n");
  append(L"    self.iStack.extend([0 for _ in range(len(self.iStack))])");
                                                            #line 2875 "PrintCLike.cpp.template"
                                                                  }
                                                                  if (tree)
                                                                  {
                                                            #line 4338 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 2879 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 4343 "PrintCLike.cpp"
  append(L"iStack");
                                                            #line 2880 "PrintCLike.cpp.template"
                                                                    print(leftbracket());
                                                                    print(thiz());
                                                            #line 4348 "PrintCLike.cpp"
  append(L"top - 2");
                                                            #line 2882 "PrintCLike.cpp.template"
                                                                    print(rightbracket());
                                                            #line 4352 "PrintCLike.cpp"
  append(L" = begin");
                                                            #line 2883 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                  }
                                                            #line 4357 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 2886 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 4362 "PrintCLike.cpp"
  append(L"iStack");
                                                            #line 2887 "PrintCLike.cpp.template"
                                                                  print(leftbracket());
                                                                  print(thiz());
                                                            #line 4367 "PrintCLike.cpp"
  append(L"top - 1");
                                                            #line 2889 "PrintCLike.cpp.template"
                                                                  print(rightbracket());
                                                            #line 4371 "PrintCLike.cpp"
  append(L" = state");
                                                            #line 2890 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                            #line 4375 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 2892 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 4380 "PrintCLike.cpp"
  append(L"iStack");
                                                            #line 2893 "PrintCLike.cpp.template"
                                                                  print(leftbracket());
                                                                  print(thiz());
                                                            #line 4385 "PrintCLike.cpp"
  append(L"top");
                                                            #line 2895 "PrintCLike.cpp.template"
                                                                  print(rightbracket());
                                                            #line 4389 "PrintCLike.cpp"
  append(L" = lookback");
                                                            #line 2896 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                  print(rightBrace());
                                                            #line 4394 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 2899 "PrintCLike.cpp.template"
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
                                                            #line 4413 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 2916 "PrintCLike.cpp.template"
                                                                  print(intVar());
                                                            #line 4417 "PrintCLike.cpp"
  append(L"state");
                                                            #line 2917 "PrintCLike.cpp.template"
                                                                  print(assign());
                                                            #line 4421 "PrintCLike.cpp"
  append(L"initialState");
                                                            #line 2918 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                  if (tree || useGlr)
                                                                  {
                                                            #line 4427 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 2922 "PrintCLike.cpp.template"
                                                                    print(intVar());
                                                            #line 4431 "PrintCLike.cpp"
  append(L"bw");
                                                            #line 2923 "PrintCLike.cpp.template"
                                                                    print(assign());
                                                                    print(thiz());
                                                            #line 4436 "PrintCLike.cpp"
  append(L"e0");
                                                            #line 2925 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 4440 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 2927 "PrintCLike.cpp.template"
                                                                    print(intVar());
                                                            #line 4444 "PrintCLike.cpp"
  append(L"bs");
                                                            #line 2928 "PrintCLike.cpp.template"
                                                                    print(assign());
                                                                    print(thiz());
                                                            #line 4449 "PrintCLike.cpp"
  append(L"e0");
                                                            #line 2930 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                  }
                                                                  if (tree)
                                                                  {
                                                            #line 4456 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 2935 "PrintCLike.cpp.template"
                                                                    print(intVar());
                                                            #line 4460 "PrintCLike.cpp"
  append(L"es");
                                                            #line 2936 "PrintCLike.cpp.template"
                                                                    print(assign());
                                                                    print(thiz());
                                                            #line 4465 "PrintCLike.cpp"
  append(L"e0");
                                                            #line 2938 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 4469 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 2940 "PrintCLike.cpp.template"
                                                                    print(intVar());
                                                            #line 4473 "PrintCLike.cpp"
  append(L"t");
                                                            #line 2941 "PrintCLike.cpp.template"
                                                                    print(assign());
                                                                    print(thiz());
                                                            #line 4478 "PrintCLike.cpp"
  append(L"top");
                                                            #line 2943 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                  }
                                                            #line 4483 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 2946 "PrintCLike.cpp.template"
                                                                  print(intVar());
                                                            #line 4487 "PrintCLike.cpp"
  append(L"action");
                                                            #line 2947 "PrintCLike.cpp.template"
                                                                  print(assign());
                                                                  print(thiz());
                                                            #line 4492 "PrintCLike.cpp"
  append(L"predict(state)");
                                                            #line 2949 "PrintCLike.cpp.template"
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
                                                            #line 4506 "PrintCLike.cpp"
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
                                                            #line 2973 "PrintCLike.cpp.template"
                                                                }
                                                                if (useGlr)
                                                                {
                                                            #line 4523 "PrintCLike.cpp"
  append(L"\n");
  append(L"  var thread: ");
                                                            #line 2977 "PrintCLike.cpp.template"
                                                                  print(className.c_str());
                                                            #line 4528 "PrintCLike.cpp"
  append(L".ParsingThread = null");
                                                            #line 2978 "PrintCLike.cpp.template"
                                                                }
                                                            #line 4532 "PrintCLike.cpp"
  append(L"\n");
  append(L"  var input: String = null");
                                                            #line 2980 "PrintCLike.cpp.template"
                                                                if (! noLexer)
                                                                {
                                                            #line 4538 "PrintCLike.cpp"
  append(L"\n");
  append(L"  var size = 0");
                                                            #line 2983 "PrintCLike.cpp.template"
                                                                }
                                                                if (tree && useGlr)
                                                                {
                                                            #line 4545 "PrintCLike.cpp"
  append(L"\n");
  append(L"  var eventHandler: ");
                                                            #line 2987 "PrintCLike.cpp.template"
                                                                  print(className.c_str());
                                                            #line 4550 "PrintCLike.cpp"
  append(L".BottomUpEventHandler = null");
                                                            #line 2988 "PrintCLike.cpp.template"
                                                                }
                                                                if (noLexer)
                                                                {
                                                            #line 4556 "PrintCLike.cpp"
  append(L"\n");
  append(L"  var lexer: Lexer = null\n");
  append(L"  var token = new Token");
                                                            #line 2993 "PrintCLike.cpp.template"
                                                                }
                                                                if (useGlr)
                                                                {
                                                            #line 4564 "PrintCLike.cpp"
  append(L"\n");
  append(L"  var maxId = 0");
                                                            #line 2997 "PrintCLike.cpp.template"
                                                                }
                                                                if (trace)
                                                                {
                                                            #line 4571 "PrintCLike.cpp"
  append(L"\n");
  append(L"  var err: Writer = new OutputStreamWriter(System.err, \"UTF-8\")");
                                                            #line 3002 "PrintCLike.cpp.template"
                                                                }
                                                            #line 4576 "PrintCLike.cpp"
  append(L"\n");
  append(L"}\n");
  append(L"\n");
  append(L"object ");
                                                            #line 3006 "PrintCLike.cpp.template"
                                                                print(className.c_str());
                                                            #line 4583 "PrintCLike.cpp"
  append(L" {\n");
  append(L"\n");
  append(L"  def getOffendingToken(e: ParseException) = {\n");
  append(L"    if (e.offending < 0) null else TOKEN(e.offending)\n");
  append(L"  }\n");
                                                            #line 3013 "PrintCLike.cpp.template"
                                                              }
                                                            }

                                                            void PrintCLike::printThreadBody1()
                                                            {
                                                              Trace("PrintCLike::printThreadBody1");

                                                              if (isLrParser)
                                                              {
                                                            #line 4599 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3023 "PrintCLike.cpp.template"
                                                                print(intVar());
                                                            #line 4603 "PrintCLike.cpp"
  append(L"nonterminalId");
                                                            #line 3024 "PrintCLike.cpp.template"
                                                                print(assign());
                                                            #line 4607 "PrintCLike.cpp"
  append(L"-1");
                                                            #line 3025 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                if (isHaxe() || isScala() || isPython())
                                                                {
                                                            #line 4613 "PrintCLike.cpp"
  append(L"\n");
  append(L"while ");
                                                            #line 3029 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                                  if (isPython())
                                                                  {
                                                            #line 4620 "PrintCLike.cpp"
  append(L"T");
                                                            #line 3032 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 4626 "PrintCLike.cpp"
  append(L"t");
                                                            #line 3035 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 4630 "PrintCLike.cpp"
  append(L"rue");
                                                            #line 3036 "PrintCLike.cpp.template"
                                                                  print(ifRightParen());
                                                                }
                                                                else if (isGo())
                                                                {
                                                            #line 4637 "PrintCLike.cpp"
  append(L"\n");
  append(L"for");
                                                            #line 3041 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 4644 "PrintCLike.cpp"
  append(L"\n");
  append(L"for (;;)");
                                                            #line 3045 "PrintCLike.cpp.template"
                                                                }
                                                                print(leftBrace());
                                                                increaseIndent();
                                                                if (trace)
                                                                {
                                                                  if (isCpp())
                                                                  {
                                                            #line 4655 "PrintCLike.cpp"
  append(L"\n");
  append(L"fprintf(stderr, \"  <parse ");
                                                            #line 3053 "PrintCLike.cpp.template"
                                                                    if (useGlr)
                                                                    {
                                                            #line 4661 "PrintCLike.cpp"
  append(L"thread=\\\"%d\\\" offset=\\\"%d\\\" ");
                                                            #line 3055 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 4665 "PrintCLike.cpp"
  append(L"state=\\\"%d\\\" input=\\\"%s%s%s\\\" action=\\\"\",");
                                                            #line 3057 "PrintCLike.cpp.template"
                                                                    if (useGlr)
                                                                    {
                                                            #line 4670 "PrintCLike.cpp"
  append(L"\n");
  append(L"  id,\n");
  append(L"  e0,");
                                                            #line 3061 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 4676 "PrintCLike.cpp"
  append(L"\n");
  append(L"  state,\n");
  append(L"  nonterminalId < 0 ? \"\" : ");
                                                            #line 3064 "PrintCLike.cpp.template"
                                                                    if (stringIntroducer()[0])
                                                                    {
                                                            #line 4683 "PrintCLike.cpp"
  append(L"Utf8Encoder::encode(");
                                                            #line 3066 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 4687 "PrintCLike.cpp"
  append(L"xmlEscape(");
                                                            #line 3067 "PrintCLike.cpp.template"
                                                                    print(isGo() ? L"nonterminal" : L"NONTERMINAL");
                                                            #line 4691 "PrintCLike.cpp"
  append(L"[nonterminalId], 0).c_str()");
                                                            #line 3069 "PrintCLike.cpp.template"
                                                                    if (stringIntroducer()[0])
                                                                    {
                                                            #line 4696 "PrintCLike.cpp"
  append(L").c_str()");
                                                            #line 3071 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 4700 "PrintCLike.cpp"
  append(L",\n");
  append(L"  nonterminalId < 0 || l1 <= 0 ? \"\" : \" \",\n");
  append(L"  l1 <= 0 ? \"\" : ");
                                                            #line 3074 "PrintCLike.cpp.template"
                                                                    if (stringIntroducer()[0])
                                                                    {
                                                            #line 4707 "PrintCLike.cpp"
  append(L"Utf8Encoder::encode(");
                                                            #line 3076 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 4711 "PrintCLike.cpp"
  append(L"xmlEscape(lookaheadString().c_str(), 0).c_str()");
                                                            #line 3077 "PrintCLike.cpp.template"
                                                                    if (stringIntroducer()[0])
                                                                    {
                                                            #line 4716 "PrintCLike.cpp"
  append(L").c_str()");
                                                            #line 3079 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 4720 "PrintCLike.cpp"
  append(L");\n");
                                                            #line 3081 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                                    if (isHaxe())
                                                                    {
                                                            #line 4728 "PrintCLike.cpp"
  append(L"\n");
  append(L"var traceLine = ");
                                                            #line 3087 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 4735 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3091 "PrintCLike.cpp.template"
                                                                      print(writeTrace());
                                                                    }
                                                            #line 4740 "PrintCLike.cpp"
  append(L"\"  <parse ");
                                                            #line 3093 "PrintCLike.cpp.template"
                                                                    if (useGlr)
                                                                    {
                                                            #line 4745 "PrintCLike.cpp"
  append(L"thread=\\\"\" + ");
                                                            #line 3095 "PrintCLike.cpp.template"
                                                                      if (isGo())
                                                                      {
                                                            #line 4750 "PrintCLike.cpp"
  append(L"strconv.Itoa(");
                                                            #line 3097 "PrintCLike.cpp.template"
                                                                      }
                                                                      else if (isPython())
                                                                      {
                                                            #line 4756 "PrintCLike.cpp"
  append(L"str(");
                                                            #line 3100 "PrintCLike.cpp.template"
                                                                      }
                                                                      print(thiz());
                                                            #line 4761 "PrintCLike.cpp"
  append(L"id");
                                                            #line 3102 "PrintCLike.cpp.template"
                                                                      if (isGo() || isPython())
                                                                      {
                                                            #line 4766 "PrintCLike.cpp"
  append(L")");
                                                            #line 3104 "PrintCLike.cpp.template"
                                                                      }
                                                            #line 4770 "PrintCLike.cpp"
  append(L" + \"\\\" offset=\\\"\" + ");
                                                            #line 3105 "PrintCLike.cpp.template"
                                                                      if (isGo())
                                                                      {
                                                            #line 4775 "PrintCLike.cpp"
  append(L"strconv.Itoa(");
                                                            #line 3107 "PrintCLike.cpp.template"
                                                                      }
                                                                      else if (isPython())
                                                                      {
                                                            #line 4781 "PrintCLike.cpp"
  append(L"str(");
                                                            #line 3110 "PrintCLike.cpp.template"
                                                                      }
                                                                      print(thiz());
                                                            #line 4786 "PrintCLike.cpp"
  append(L"e0");
                                                            #line 3112 "PrintCLike.cpp.template"
                                                                      if (isGo() || isPython())
                                                                      {
                                                            #line 4791 "PrintCLike.cpp"
  append(L")");
                                                            #line 3114 "PrintCLike.cpp.template"
                                                                      }
                                                            #line 4795 "PrintCLike.cpp"
  append(L" + \"\\\" ");
                                                            #line 3115 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 4799 "PrintCLike.cpp"
  append(L"state=\\\"\" + ");
                                                            #line 3116 "PrintCLike.cpp.template"
                                                                    if (isGo())
                                                                    {
                                                            #line 4804 "PrintCLike.cpp"
  append(L"strconv.Itoa(");
                                                            #line 3118 "PrintCLike.cpp.template"
                                                                    }
                                                                    else if (isPython())
                                                                    {
                                                            #line 4810 "PrintCLike.cpp"
  append(L"str(");
                                                            #line 3121 "PrintCLike.cpp.template"
                                                                    }
                                                                    if (useGlr) print(thiz());
                                                            #line 4815 "PrintCLike.cpp"
  append(L"state");
                                                            #line 3123 "PrintCLike.cpp.template"
                                                                    if (isGo() || isPython())
                                                                    {
                                                            #line 4820 "PrintCLike.cpp"
  append(L")");
                                                            #line 3125 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 4824 "PrintCLike.cpp"
  append(L" + \"\\\" input=\\\"\"");
                                                            #line 3126 "PrintCLike.cpp.template"
                                                                    print(endWriteTrace());
                                                                    print(semicolon());
                                                            #line 4829 "PrintCLike.cpp"
  append(L"\n");
  append(L"if ");
                                                            #line 3130 "PrintCLike.cpp.template"
                                                                    print(ifLeftParen());
                                                            #line 4834 "PrintCLike.cpp"
  append(L"nonterminalId >= 0");
                                                            #line 3131 "PrintCLike.cpp.template"
                                                                    print(ifRightParen());
                                                                    print(leftBrace());
                                                            #line 4839 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3134 "PrintCLike.cpp.template"
                                                                    print(writeTrace());
                                                                    print(staticPrefix());
                                                            #line 4845 "PrintCLike.cpp"
  append(L"xmlEscape(");
                                                            #line 3137 "PrintCLike.cpp.template"
                                                                    print(staticPrefix());
                                                                    print(isGo() ? L"nonterminal" : L"NONTERMINAL");
                                                                    print(leftbracket());
                                                            #line 4851 "PrintCLike.cpp"
  append(L"nonterminalId");
                                                            #line 3140 "PrintCLike.cpp.template"
                                                                    print(rightbracket());
                                                            #line 4855 "PrintCLike.cpp"
  append(L")");
                                                            #line 3141 "PrintCLike.cpp.template"
                                                                    print(endWriteTrace());
                                                                    print(semicolon());
                                                            #line 4860 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if ");
                                                            #line 3144 "PrintCLike.cpp.template"
                                                                    print(ifLeftParen());
                                                                    print(thiz());
                                                            #line 4866 "PrintCLike.cpp"
  append(L"l1 != 0");
                                                            #line 3146 "PrintCLike.cpp.template"
                                                                    print(ifRightParen());
                                                                    printIndented(1, leftBrace());
                                                            #line 4871 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 3149 "PrintCLike.cpp.template"
                                                                    print(writeTrace());
                                                            #line 4876 "PrintCLike.cpp"
  append(L"\" \"");
                                                            #line 3150 "PrintCLike.cpp.template"
                                                                    print(endWriteTrace());
                                                                    print(semicolon());
                                                                    increaseIndent();
                                                                    print(rightBrace());
                                                                    decreaseIndent();
                                                                    print(rightBrace());
                                                            #line 4885 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3157 "PrintCLike.cpp.template"
                                                                    print(writeTrace());
                                                                    print(staticPrefix());
                                                            #line 4890 "PrintCLike.cpp"
  append(L"xmlEscape(");
                                                            #line 3159 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 4894 "PrintCLike.cpp"
  append(L"lookaheadString");
                                                            #line 3160 "PrintCLike.cpp.template"
                                                                    if (! isScala()) print(L"()");
                                                            #line 4898 "PrintCLike.cpp"
  append(L") + \"\\\" action=\\\"\"");
                                                            #line 3161 "PrintCLike.cpp.template"
                                                                    print(endWriteTrace());
                                                                    print(semicolon());
                                                                  }
                                                                }
                                                            #line 4905 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3166 "PrintCLike.cpp.template"
                                                                print(intVal());
                                                            #line 4909 "PrintCLike.cpp"
  append(L"argument");
                                                            #line 3167 "PrintCLike.cpp.template"
                                                                print(assign());
                                                                if (useGlr) print(thiz());
                                                            #line 4914 "PrintCLike.cpp"
  append(L"action >> ");
                                                            #line 3169 "PrintCLike.cpp.template"
                                                                print(format.toString<wchar_t>(grammar->states->dominoBits + LrStates::actionBits));
                                                                print(semicolon());
                                                            #line 4919 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3172 "PrintCLike.cpp.template"
                                                                print(intVal());
                                                            #line 4923 "PrintCLike.cpp"
  append(L"lookback");
                                                            #line 3173 "PrintCLike.cpp.template"
                                                                print(assign());
                                                            #line 4927 "PrintCLike.cpp"
  append(L"(");
                                                            #line 3174 "PrintCLike.cpp.template"
                                                                if (useGlr) print(thiz());
                                                            #line 4931 "PrintCLike.cpp"
  append(L"action >> ");
                                                            #line 3175 "PrintCLike.cpp.template"
                                                                print(format.toString<wchar_t>((int) LrStates::actionBits));
                                                            #line 4935 "PrintCLike.cpp"
  append(L") & ");
                                                            #line 3176 "PrintCLike.cpp.template"
                                                                print(format.toString<wchar_t>((1 << grammar->states->dominoBits) -1));
                                                                print(semicolon());
                                                            #line 4940 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3179 "PrintCLike.cpp.template"
                                                                print(intVar());
                                                            #line 4944 "PrintCLike.cpp"
  append(L"shift");
                                                            #line 3180 "PrintCLike.cpp.template"
                                                                print(assign());
                                                            #line 4948 "PrintCLike.cpp"
  append(L"-1");
                                                            #line 3181 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 4952 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3183 "PrintCLike.cpp.template"
                                                                print(intVar());
                                                            #line 4956 "PrintCLike.cpp"
  append(L"reduce");
                                                            #line 3184 "PrintCLike.cpp.template"
                                                                print(assign());
                                                            #line 4960 "PrintCLike.cpp"
  append(L"-1");
                                                            #line 3185 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 4964 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3187 "PrintCLike.cpp.template"
                                                                print(intVar());
                                                            #line 4968 "PrintCLike.cpp"
  append(L"symbols");
                                                            #line 3188 "PrintCLike.cpp.template"
                                                                print(assign());
                                                            #line 4972 "PrintCLike.cpp"
  append(L"-1");
                                                            #line 3189 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                if (isPython())
                                                                {
                                                            #line 4978 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3194 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 4982 "PrintCLike.cpp"
  append(L"action &= ");
                                                            #line 3195 "PrintCLike.cpp.template"
                                                                  print(format.toString<wchar_t>((int) LrStates::actionMask));
                                                                }
                                                                else
                                                                {
                                                            #line 4989 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3200 "PrintCLike.cpp.template"
                                                                  if (! isScala())
                                                                  {
                                                            #line 4994 "PrintCLike.cpp"
  append(L"switch ");
                                                            #line 3202 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(ifLeftParen());
                                                                  if (useGlr) print(thiz());
                                                            #line 5000 "PrintCLike.cpp"
  append(L"action & ");
                                                            #line 3205 "PrintCLike.cpp.template"
                                                                  print(format.toString<wchar_t>((int) LrStates::actionMask));
                                                                  print(ifRightParen());
                                                                  if (isScala())
                                                                  {
                                                            #line 5007 "PrintCLike.cpp"
  append(L" match");
                                                            #line 3209 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(leftBrace());
                                                                }
                                                                if (isPython())
                                                                {
                                                            #line 5015 "PrintCLike.cpp"
  append(L"\n");
  append(L"if ");
                                                            #line 3215 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 5020 "PrintCLike.cpp"
  append(L"action == ");
                                                            #line 3216 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 5026 "PrintCLike.cpp"
  append(L"\n");
  append(L"case ");
                                                            #line 3220 "PrintCLike.cpp.template"
                                                                }
                                                                print(format.toString<wchar_t>((int) LrStates::SHIFT));
                                                                print(caseIntroducer());
                                                            #line 5033 "PrintCLike.cpp"
  append(L" ");
                                                            #line 3223 "PrintCLike.cpp.template"
                                                                print(inlineCommentIntroducer());
                                                            #line 5037 "PrintCLike.cpp"
  append(L"SHIFT\n");
  append(L"  shift = argument");
                                                            #line 3225 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                if (! isHaxe() && ! isScala() && ! isGo() && ! isPython())
                                                                {
                                                            #line 5044 "PrintCLike.cpp"
  append(L"\n");
  append(L"  break");
                                                            #line 3229 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                            #line 5050 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3232 "PrintCLike.cpp.template"
                                                                if (isPython())
                                                                {
                                                            #line 5055 "PrintCLike.cpp"
  append(L"\n");
  append(L"elif ");
                                                            #line 3235 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 5060 "PrintCLike.cpp"
  append(L"action == ");
                                                            #line 3236 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 5066 "PrintCLike.cpp"
  append(L"\n");
  append(L"case ");
                                                            #line 3240 "PrintCLike.cpp.template"
                                                                }
                                                                print(format.toString<wchar_t>((int) LrStates::REDUCE));
                                                                print(caseIntroducer());
                                                            #line 5073 "PrintCLike.cpp"
  append(L" ");
                                                            #line 3243 "PrintCLike.cpp.template"
                                                                print(inlineCommentIntroducer());
                                                            #line 5077 "PrintCLike.cpp"
  append(L"REDUCE\n");
  append(L"  reduce = argument");
                                                            #line 3245 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 5082 "PrintCLike.cpp"
  append(L"\n");
  append(L"  symbols = lookback");
                                                            #line 3247 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                if (! isHaxe() && ! isScala() && ! isGo() && ! isPython())
                                                                {
                                                            #line 5089 "PrintCLike.cpp"
  append(L"\n");
  append(L"  break");
                                                            #line 3251 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                                if (grammar->states->hasLookback)
                                                                {
                                                            #line 5097 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3256 "PrintCLike.cpp.template"
                                                                  if (isPython())
                                                                  {
                                                            #line 5102 "PrintCLike.cpp"
  append(L"\n");
  append(L"elif ");
                                                            #line 3259 "PrintCLike.cpp.template"
                                                                    if (useGlr) print(thiz());
                                                            #line 5107 "PrintCLike.cpp"
  append(L"action == ");
                                                            #line 3260 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 5113 "PrintCLike.cpp"
  append(L"\n");
  append(L"case ");
                                                            #line 3264 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(format.toString<wchar_t>((int) LrStates::REDUCE_LOOKBACK));
                                                                  print(caseIntroducer());
                                                            #line 5120 "PrintCLike.cpp"
  append(L" ");
                                                            #line 3267 "PrintCLike.cpp.template"
                                                                  print(inlineCommentIntroducer());
                                                            #line 5124 "PrintCLike.cpp"
  append(L"REDUCE+LOOKBACK\n");
  append(L"  reduce = argument");
                                                            #line 3269 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                            #line 5129 "PrintCLike.cpp"
  append(L"\n");
  append(L"  symbols = ");
                                                            #line 3271 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                                  if (useGlr)
                                                                  {
                                                            #line 5136 "PrintCLike.cpp"
  append(L"stack");
                                                            #line 3274 "PrintCLike.cpp.template"
                                                                    if (isTypescript()) print(L"!");
                                                                    print(arrow());
                                                                  }
                                                                  if (isGo() && useGlr)
                                                                  {
                                                            #line 5144 "PrintCLike.cpp"
  append(L"Count");
                                                            #line 3279 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 5150 "PrintCLike.cpp"
  append(L"count");
                                                            #line 3282 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 5154 "PrintCLike.cpp"
  append(L"(lookback)");
                                                            #line 3283 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                  if (! isHaxe() && ! isScala() && ! isGo() && ! isPython())
                                                                  {
                                                            #line 5160 "PrintCLike.cpp"
  append(L"\n");
  append(L"  break");
                                                            #line 3287 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                  }
                                                                }
                                                            #line 5167 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3291 "PrintCLike.cpp.template"
                                                                if (isPython())
                                                                {
                                                            #line 5172 "PrintCLike.cpp"
  append(L"\n");
  append(L"elif ");
                                                            #line 3294 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 5177 "PrintCLike.cpp"
  append(L"action == ");
                                                            #line 3295 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 5183 "PrintCLike.cpp"
  append(L"\n");
  append(L"case ");
                                                            #line 3299 "PrintCLike.cpp.template"
                                                                }
                                                                print(format.toString<wchar_t>((int) LrStates::SHIFT_REDUCE));
                                                                print(caseIntroducer());
                                                            #line 5190 "PrintCLike.cpp"
  append(L" ");
                                                            #line 3302 "PrintCLike.cpp.template"
                                                                print(inlineCommentIntroducer());
                                                            #line 5194 "PrintCLike.cpp"
  append(L"SHIFT+REDUCE\n");
  append(L"  shift = ");
                                                            #line 3304 "PrintCLike.cpp.template"
                                                                if (useGlr) print(thiz());
                                                            #line 5199 "PrintCLike.cpp"
  append(L"state");
                                                            #line 3305 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 5203 "PrintCLike.cpp"
  append(L"\n");
  append(L"  reduce = argument");
                                                            #line 3307 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 5208 "PrintCLike.cpp"
  append(L"\n");
  append(L"  symbols = lookback + 1");
                                                            #line 3309 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                if (! isHaxe() && ! isScala() && ! isGo() && ! isPython())
                                                                {
                                                            #line 5215 "PrintCLike.cpp"
  append(L"\n");
  append(L"  break");
                                                            #line 3313 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                                if (grammar->states->hasLookback)
                                                                {
                                                            #line 5223 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3318 "PrintCLike.cpp.template"
                                                                  if (isPython())
                                                                  {
                                                            #line 5228 "PrintCLike.cpp"
  append(L"\n");
  append(L"elif ");
                                                            #line 3321 "PrintCLike.cpp.template"
                                                                    if (useGlr) print(thiz());
                                                            #line 5233 "PrintCLike.cpp"
  append(L"action == ");
                                                            #line 3322 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 5239 "PrintCLike.cpp"
  append(L"\n");
  append(L"case ");
                                                            #line 3326 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(format.toString<wchar_t>((int) LrStates::SHIFT_REDUCE_LOOKBACK));
                                                                  print(caseIntroducer());
                                                            #line 5246 "PrintCLike.cpp"
  append(L" ");
                                                            #line 3329 "PrintCLike.cpp.template"
                                                                  print(inlineCommentIntroducer());
                                                            #line 5250 "PrintCLike.cpp"
  append(L"SHIFT+REDUCE+LOOKBACK\n");
  append(L"  shift = ");
                                                            #line 3331 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 5255 "PrintCLike.cpp"
  append(L"state");
                                                            #line 3332 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                            #line 5259 "PrintCLike.cpp"
  append(L"\n");
  append(L"  reduce = argument");
                                                            #line 3334 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                            #line 5264 "PrintCLike.cpp"
  append(L"\n");
  append(L"  symbols = ");
                                                            #line 3336 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                                  if (useGlr)
                                                                  {
                                                            #line 5271 "PrintCLike.cpp"
  append(L"stack");
                                                            #line 3339 "PrintCLike.cpp.template"
                                                                    if (isTypescript()) print(L"!");
                                                                    print(arrow());
                                                                  }
                                                                  if (isGo() && useGlr)
                                                                  {
                                                            #line 5279 "PrintCLike.cpp"
  append(L"Count");
                                                            #line 3344 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 5285 "PrintCLike.cpp"
  append(L"count");
                                                            #line 3347 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 5289 "PrintCLike.cpp"
  append(L"(lookback) + 1");
                                                            #line 3348 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                  if (! isHaxe() && ! isScala() && ! isGo() && ! isPython())
                                                                  {
                                                            #line 5295 "PrintCLike.cpp"
  append(L"\n");
  append(L"  break");
                                                            #line 3352 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                  }
                                                                }
                                                            #line 5302 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3356 "PrintCLike.cpp.template"
                                                                if (isPython())
                                                                {
                                                            #line 5307 "PrintCLike.cpp"
  append(L"\n");
  append(L"elif ");
                                                            #line 3359 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 5312 "PrintCLike.cpp"
  append(L"action == ");
                                                            #line 3360 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 5318 "PrintCLike.cpp"
  append(L"\n");
  append(L"case ");
                                                            #line 3364 "PrintCLike.cpp.template"
                                                                }
                                                                print(format.toString<wchar_t>((int) LrStates::SHIFT_ACCEPT));
                                                                print(caseIntroducer());
                                                            #line 5325 "PrintCLike.cpp"
  append(L" ");
                                                            #line 3367 "PrintCLike.cpp.template"
                                                                print(inlineCommentIntroducer());
                                                            #line 5329 "PrintCLike.cpp"
  append(L"ACCEPT");
                                                            #line 3368 "PrintCLike.cpp.template"
                                                                if (trace)
                                                                {
                                                                  if (isCpp())
                                                                  {
                                                            #line 5336 "PrintCLike.cpp"
  append(L"\n");
  append(L"  fprintf(stderr, ");
                                                            #line 3373 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 5343 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3377 "PrintCLike.cpp.template"
                                                                    print(writeTrace());
                                                                  }
                                                            #line 5349 "PrintCLike.cpp"
  append(L"\"accept\\\"/>");
                                                            #line 3379 "PrintCLike.cpp.template"
                                                                  if (! isHaxe())
                                                                  {
                                                            #line 5354 "PrintCLike.cpp"
  append(L"\\n");
                                                            #line 3381 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 5358 "PrintCLike.cpp"
  append(L"\"");
                                                            #line 3382 "PrintCLike.cpp.template"
                                                                  print(endWriteTrace());
                                                                  print(semicolon());
                                                                  if (isHaxe())
                                                                  {
                                                            #line 5365 "PrintCLike.cpp"
  append(L"\n");
  append(L"  trace(traceLine);");
                                                            #line 3387 "PrintCLike.cpp.template"
                                                                  }
                                                                }
                                                                if (useGlr)
                                                                {
                                                            #line 5373 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3392 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 5378 "PrintCLike.cpp"
  append(L"accepted = ");
                                                            #line 3393 "PrintCLike.cpp.template"
                                                                  if (isPython())
                                                                  {
                                                            #line 5383 "PrintCLike.cpp"
  append(L"T");
                                                            #line 3395 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 5389 "PrintCLike.cpp"
  append(L"t");
                                                            #line 3398 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 5393 "PrintCLike.cpp"
  append(L"rue");
                                                            #line 3399 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                            #line 5397 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3401 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 5402 "PrintCLike.cpp"
  append(L"action = 0");
                                                            #line 3402 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                            #line 5406 "PrintCLike.cpp"
  append(L"\n");
  append(L"  return ");
                                                            #line 3404 "PrintCLike.cpp.template"
                                                                  if (isHaxe() || isTypescript() || isPython()) print(staticPrefix());
                                                            #line 5411 "PrintCLike.cpp"
  append(L"ACCEPTED");
                                                            #line 3405 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                                else
                                                                {
                                                            #line 5418 "PrintCLike.cpp"
  append(L"\n");
  append(L"  return");
                                                            #line 3410 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }

                                                                if (useGlr)
                                                                {
                                                            #line 5427 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3416 "PrintCLike.cpp.template"
                                                                  if (isPython())
                                                                  {
                                                            #line 5432 "PrintCLike.cpp"
  append(L"\n");
  append(L"elif ");
                                                            #line 3419 "PrintCLike.cpp.template"
                                                                    if (useGlr) print(thiz());
                                                            #line 5437 "PrintCLike.cpp"
  append(L"action == ");
                                                            #line 3420 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 5443 "PrintCLike.cpp"
  append(L"\n");
  append(L"case ");
                                                            #line 3424 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(format.toString<wchar_t>((int) LrStates::FORK));
                                                                  print(caseIntroducer());
                                                            #line 5450 "PrintCLike.cpp"
  append(L" ");
                                                            #line 3427 "PrintCLike.cpp.template"
                                                                  print(inlineCommentIntroducer());
                                                            #line 5454 "PrintCLike.cpp"
  append(L"FORK");
                                                            #line 3428 "PrintCLike.cpp.template"
                                                                  if (trace)
                                                                  {
                                                                    if (isCpp())
                                                                    {
                                                            #line 5461 "PrintCLike.cpp"
  append(L"\n");
  append(L"  fprintf(stderr, \"fork\\\"/>\\n\");");
                                                            #line 3433 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 5468 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3437 "PrintCLike.cpp.template"
                                                                      print(writeTrace());
                                                            #line 5473 "PrintCLike.cpp"
  append(L"\"fork\\\"/>");
                                                            #line 3438 "PrintCLike.cpp.template"
                                                                      if (! isHaxe())
                                                                      {
                                                            #line 5478 "PrintCLike.cpp"
  append(L"\\n\"");
                                                            #line 3440 "PrintCLike.cpp.template"
                                                                        print(endWriteTrace());
                                                                        print(semicolon());
                                                                      }
                                                                      else
                                                                      {
                                                            #line 5486 "PrintCLike.cpp"
  append(L"\";\n");
  append(L"  trace(traceLine);");
                                                            #line 3446 "PrintCLike.cpp.template"
                                                                      }
                                                                    }
                                                                  }
                                                                  if (isGo())
                                                                  {
                                                            #line 5495 "PrintCLike.cpp"
  append(L"\n");
  append(L"  heap.Push(this.threads, new(ParsingThread).copy(this, appendix[argument]))");
                                                            #line 3453 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isPython())
                                                                  {
                                                            #line 5502 "PrintCLike.cpp"
  append(L"\n");
  append(L"  forked = ");
                                                            #line 3457 "PrintCLike.cpp.template"
                                                                    print(staticPrefix());
                                                            #line 5507 "PrintCLike.cpp"
  append(L"ParsingThread().copy(self, ");
                                                            #line 3458 "PrintCLike.cpp.template"
                                                                    print(staticPrefix());
                                                            #line 5511 "PrintCLike.cpp"
  append(L"APPENDIX[argument])\n");
  append(L"  heapq.heappush(self.threads, (False, forked.e0, forked.id, forked))");
                                                            #line 3461 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 5518 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3465 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 5523 "PrintCLike.cpp"
  append(L"threads");
                                                            #line 3466 "PrintCLike.cpp.template"
                                                                    if (isCpp())
                                                                    {
                                                            #line 5528 "PrintCLike.cpp"
  append(L"->push(");
                                                            #line 3468 "PrintCLike.cpp.template"
                                                                    }
                                                                    else if (isScala())
                                                                    {
                                                            #line 5534 "PrintCLike.cpp"
  append(L" += ");
                                                            #line 3471 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 5540 "PrintCLike.cpp"
  append(L".offer(");
                                                            #line 3474 "PrintCLike.cpp.template"
                                                                    }
                                                                    if (isCpp() || isScala()) print(L"(");
                                                            #line 5545 "PrintCLike.cpp"
  append(L"new ParsingThread");
                                                            #line 3476 "PrintCLike.cpp.template"
                                                                    if (! isScala()) print(L"()");
                                                                    if (isCpp() || isScala()) print(L")");
                                                                    print(arrow());
                                                            #line 5551 "PrintCLike.cpp"
  append(L"copy(this");
                                                            #line 3479 "PrintCLike.cpp.template"
                                                                    if (isJavascript())
                                                                    {
                                                            #line 5556 "PrintCLike.cpp"
  append(L"Thread");
                                                            #line 3481 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 5560 "PrintCLike.cpp"
  append(L", ");
                                                            #line 3482 "PrintCLike.cpp.template"
                                                                    print(staticPrefix());
                                                            #line 5564 "PrintCLike.cpp"
  append(L"APPENDIX");
                                                            #line 3483 "PrintCLike.cpp.template"
                                                                    print(leftbracket());
                                                            #line 5568 "PrintCLike.cpp"
  append(L"argument");
                                                            #line 3484 "PrintCLike.cpp.template"
                                                                    print(rightbracket());
                                                            #line 5572 "PrintCLike.cpp"
  append(L")");
                                                            #line 3485 "PrintCLike.cpp.template"
                                                                    if (! isScala()) print(L")");
                                                                    print(semicolon());
                                                                  }
                                                            #line 5578 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3489 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 5583 "PrintCLike.cpp"
  append(L"action = ");
                                                            #line 3490 "PrintCLike.cpp.template"
                                                                  print(staticPrefix());
                                                                  if (isGo())
                                                                  {
                                                            #line 5589 "PrintCLike.cpp"
  append(L"appendix");
                                                            #line 3493 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 5595 "PrintCLike.cpp"
  append(L"APPENDIX");
                                                            #line 3496 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(leftbracket());
                                                            #line 5600 "PrintCLike.cpp"
  append(L"argument + 1");
                                                            #line 3498 "PrintCLike.cpp.template"
                                                                  print(rightbracket());
                                                                  print(semicolon());
                                                            #line 5605 "PrintCLike.cpp"
  append(L"\n");
  append(L"  return ");
                                                            #line 3501 "PrintCLike.cpp.template"
                                                                  if (isHaxe() || isTypescript() || isPython()) print(staticPrefix());
                                                            #line 5610 "PrintCLike.cpp"
  append(L"PARSING");
                                                            #line 3502 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                            #line 5615 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3505 "PrintCLike.cpp.template"
                                                                if (isPython())
                                                                {
                                                            #line 5620 "PrintCLike.cpp"
  append(L"\n");
  append(L"else");
                                                            #line 3508 "PrintCLike.cpp.template"
                                                                }
                                                                else if (isScala())
                                                                {
                                                            #line 5627 "PrintCLike.cpp"
  append(L"\n");
  append(L"case _");
                                                            #line 3512 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 5634 "PrintCLike.cpp"
  append(L"\n");
  append(L"default");
                                                            #line 3516 "PrintCLike.cpp.template"
                                                                }
                                                                print(caseIntroducer());
                                                            #line 5640 "PrintCLike.cpp"
  append(L" ");
                                                            #line 3518 "PrintCLike.cpp.template"
                                                                print(inlineCommentIntroducer());
                                                            #line 5644 "PrintCLike.cpp"
  append(L"ERROR");
                                                            #line 3519 "PrintCLike.cpp.template"
                                                                if (useGlr)
                                                                {
                                                                  if (trace)
                                                                  {
                                                                    if (isCpp())
                                                                    {
                                                            #line 5653 "PrintCLike.cpp"
  append(L"\n");
  append(L"  fprintf(stderr, \"fail\\\"/>\\n\");");
                                                            #line 3526 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 5660 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3530 "PrintCLike.cpp.template"
                                                                      print(writeTrace());
                                                            #line 5665 "PrintCLike.cpp"
  append(L"\"fail\\\"/>");
                                                            #line 3531 "PrintCLike.cpp.template"
                                                                      if (! isHaxe())
                                                                      {
                                                            #line 5670 "PrintCLike.cpp"
  append(L"\\n\"");
                                                            #line 3533 "PrintCLike.cpp.template"
                                                                        print(endWriteTrace());
                                                                        print(semicolon());
                                                                      }
                                                                      else
                                                                      {
                                                            #line 5678 "PrintCLike.cpp"
  append(L"\";\n");
  append(L"  trace(traceLine);");
                                                            #line 3539 "PrintCLike.cpp.template"
                                                                      }
                                                                    }
                                                                  }
                                                            #line 5685 "PrintCLike.cpp"
  append(L"\n");
  append(L"  return ");
                                                            #line 3543 "PrintCLike.cpp.template"
                                                                  if (isHaxe() || isTypescript() || isPython()) print(staticPrefix());
                                                            #line 5690 "PrintCLike.cpp"
  append(L"ERROR");
                                                            #line 3544 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                                else
                                                                {
                                                            #line 5697 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3549 "PrintCLike.cpp.template"
                                                                  print(beginThrowStmt());
                                                                  print(thiz());
                                                            #line 5703 "PrintCLike.cpp"
  append(L"b1, ");
                                                            #line 3551 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 5707 "PrintCLike.cpp"
  append(L"e1, ");
                                                            #line 3552 "PrintCLike.cpp.template"
                                                                  print(staticPrefix());
                                                                  if (isGo())
                                                                  {
                                                            #line 5713 "PrintCLike.cpp"
  append(L"tokenset");
                                                            #line 3555 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 5719 "PrintCLike.cpp"
  append(L"TOKENSET");
                                                            #line 3558 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(leftbracket());
                                                            #line 5724 "PrintCLike.cpp"
  append(L"state");
                                                            #line 3560 "PrintCLike.cpp.template"
                                                                  print(rightbracket());
                                                            #line 5728 "PrintCLike.cpp"
  append(L" + 1, ");
                                                            #line 3561 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 5732 "PrintCLike.cpp"
  append(L"l1, -1");
                                                            #line 3562 "PrintCLike.cpp.template"
                                                                  print(endThrowStmt());
                                                                  print(semicolon());
                                                                }
                                                                print(rightBrace());
                                                            #line 5739 "PrintCLike.cpp"
  append(L"\n");
  append(L"\n");
  append(L"if ");
                                                            #line 3568 "PrintCLike.cpp.template"
                                                                print(ifLeftParen());
                                                            #line 5745 "PrintCLike.cpp"
  append(L"shift >= 0");
                                                            #line 3569 "PrintCLike.cpp.template"
                                                                print(ifRightParen());
                                                                print(leftBrace());
                                                                if (trace)
                                                                {
                                                                  if (isCpp())
                                                                  {
                                                            #line 5754 "PrintCLike.cpp"
  append(L"\n");
  append(L"  fprintf(stderr, ");
                                                            #line 3576 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 5761 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3580 "PrintCLike.cpp.template"
                                                                    print(writeTrace());
                                                                  }
                                                            #line 5767 "PrintCLike.cpp"
  append(L"\"shift\"");
                                                            #line 3582 "PrintCLike.cpp.template"
                                                                  print(endWriteTrace());
                                                                  print(semicolon());
                                                                }
                                                            #line 5773 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if ");
                                                            #line 3586 "PrintCLike.cpp.template"
                                                                print(ifLeftParen());
                                                            #line 5778 "PrintCLike.cpp"
  append(L"nonterminalId < 0");
                                                            #line 3587 "PrintCLike.cpp.template"
                                                                print(ifRightParen());
                                                                printIndented(1, leftBrace());
                                                                if (tree)
                                                                {
                                                            #line 5785 "PrintCLike.cpp"
  append(L"\n");
  append(L"    if ");
                                                            #line 3592 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                                  if (useGlr) print(thiz());
                                                            #line 5791 "PrintCLike.cpp"
  append(L"eventHandler != ");
                                                            #line 3594 "PrintCLike.cpp.template"
                                                                  print(nullPtr());
                                                                  print(ifRightParen());
                                                                  printIndented(2, leftBrace());
                                                                  if (useGlr)
                                                                  {
                                                            #line 5799 "PrintCLike.cpp"
  append(L"\n");
  append(L"      if ");
                                                            #line 3600 "PrintCLike.cpp.template"
                                                                    print(ifLeftParen());
                                                                    print(thiz());
                                                                    if (isGo())
                                                                    {
                                                            #line 5807 "PrintCLike.cpp"
  append(L"IsUnambiguous");
                                                            #line 3604 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 5813 "PrintCLike.cpp"
  append(L"isUnambiguous");
                                                            #line 3607 "PrintCLike.cpp.template"
                                                                    }
                                                                    if (! isScala()) print(L"()");
                                                                    print(ifRightParen());
                                                                    printIndented(3, leftBrace());
                                                                    increaseIndent();
                                                                  }
                                                            #line 5822 "PrintCLike.cpp"
  append(L"\n");
  append(L"      ");
                                                            #line 3614 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 5827 "PrintCLike.cpp"
  append(L"eventHandler");
                                                            #line 3615 "PrintCLike.cpp.template"
                                                                  print(arrow());
                                                                  if (isGo())
                                                                  {
                                                            #line 5833 "PrintCLike.cpp"
  append(L"T");
                                                            #line 3618 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 5839 "PrintCLike.cpp"
  append(L"t");
                                                            #line 3621 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 5843 "PrintCLike.cpp"
  append(L"erminal(");
                                                            #line 3622 "PrintCLike.cpp.template"
                                                                  print(staticPrefix());
                                                                  print(isGo() ? L"token" : L"TOKEN");
                                                                  print(leftbracket());
                                                                  print(thiz());
                                                            #line 5850 "PrintCLike.cpp"
  append(L"l1");
                                                            #line 3626 "PrintCLike.cpp.template"
                                                                  print(rightbracket());
                                                            #line 5854 "PrintCLike.cpp"
  append(L", ");
                                                            #line 3627 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 5858 "PrintCLike.cpp"
  append(L"b1, ");
                                                            #line 3628 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 5862 "PrintCLike.cpp"
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
                                                            #line 5875 "PrintCLike.cpp"
  append(L"\n");
  append(L"      ");
                                                            #line 3640 "PrintCLike.cpp.template"
                                                                    printIndented(3, elseWithBraces());
                                                            #line 5880 "PrintCLike.cpp"
  append(L"\n");
  append(L"        ");
                                                            #line 3642 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 5885 "PrintCLike.cpp"
  append(L"deferredEvent = ");
                                                            #line 3643 "PrintCLike.cpp.template"
                                                                    if (isGo())
                                                                    {
                                                            #line 5890 "PrintCLike.cpp"
  append(L"&TerminalEvent{&AbstractDeferredEvent{");
                                                            #line 3645 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                                      if (! isPython())
                                                                      {
                                                            #line 5898 "PrintCLike.cpp"
  append(L"new ");
                                                            #line 3650 "PrintCLike.cpp.template"
                                                                      }
                                                                      if (! isHaxe() && ! isTypescript()) print(staticPrefix());
                                                                      if (isJavascript() || isTypescript())
                                                                      {
                                                            #line 5905 "PrintCLike.cpp"
  append(L"DeferredEvent");
                                                            #line 3654 "PrintCLike.cpp.template"
                                                                      }
                                                                      else
                                                                      {
                                                            #line 5911 "PrintCLike.cpp"
  append(L"TerminalEvent");
                                                            #line 3657 "PrintCLike.cpp.template"
                                                                      }
                                                            #line 5915 "PrintCLike.cpp"
  append(L"(");
                                                            #line 3658 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(thiz());
                                                            #line 5920 "PrintCLike.cpp"
  append(L"deferredEvent, ");
                                                            #line 3660 "PrintCLike.cpp.template"
                                                                    print(staticPrefix());
                                                                    print(isGo() ? L"token" : L"TOKEN");
                                                                    print(leftbracket());
                                                                    print(thiz());
                                                            #line 5927 "PrintCLike.cpp"
  append(L"l1");
                                                            #line 3664 "PrintCLike.cpp.template"
                                                                    print(rightbracket());
                                                            #line 5931 "PrintCLike.cpp"
  append(L", ");
                                                            #line 3665 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 5935 "PrintCLike.cpp"
  append(L"b1, ");
                                                            #line 3666 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 5939 "PrintCLike.cpp"
  append(L"e1");
                                                            #line 3668 "PrintCLike.cpp.template"
                                                                    if (isTypescript())
                                                                    {
                                                            #line 5944 "PrintCLike.cpp"
  append(L", -1");
                                                            #line 3670 "PrintCLike.cpp.template"
                                                                    }
                                                                    if (isGo())
                                                                    {
                                                            #line 5950 "PrintCLike.cpp"
  append(L"}}");
                                                            #line 3674 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 5956 "PrintCLike.cpp"
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
                                                            #line 5967 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 3687 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 5972 "PrintCLike.cpp"
  append(L"es = ");
                                                            #line 3688 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 5976 "PrintCLike.cpp"
  append(L"e1");
                                                            #line 3689 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                                if (useGlr)
                                                                {
                                                            #line 5983 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 3694 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 5988 "PrintCLike.cpp"
  append(L"stack = ");
                                                            #line 3695 "PrintCLike.cpp.template"
                                                                  if (isGo())
                                                                  {
                                                            #line 5993 "PrintCLike.cpp"
  append(L"&StackNode{");
                                                            #line 3697 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                                    if (! isPython())
                                                                    {
                                                            #line 6001 "PrintCLike.cpp"
  append(L"new ");
                                                            #line 3702 "PrintCLike.cpp.template"
                                                                    }
                                                                    if (! isHaxe() && ! isTypescript()) print(staticPrefix());
                                                            #line 6006 "PrintCLike.cpp"
  append(L"StackNode(");
                                                            #line 3704 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(thiz());
                                                            #line 6011 "PrintCLike.cpp"
  append(L"state, ");
                                                            #line 3706 "PrintCLike.cpp.template"
                                                                  if (grammar->states->hasLookback)
                                                                  {
                                                            #line 6016 "PrintCLike.cpp"
  append(L"lookback, ");
                                                            #line 3708 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(thiz());
                                                            #line 6021 "PrintCLike.cpp"
  append(L"b1, ");
                                                            #line 3710 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 6025 "PrintCLike.cpp"
  append(L"stack");
                                                            #line 3711 "PrintCLike.cpp.template"
                                                                  print(isGo() ? L"}" : L")");
                                                                  print(semicolon());
                                                                }
                                                                else
                                                                {
                                                            #line 6033 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 3717 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 6038 "PrintCLike.cpp"
  append(L"push(state, lookback");
                                                            #line 3718 "PrintCLike.cpp.template"
                                                                  if (tree)
                                                                  {
                                                            #line 6043 "PrintCLike.cpp"
  append(L", ");
                                                            #line 3720 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 6047 "PrintCLike.cpp"
  append(L"b1");
                                                            #line 3721 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 6051 "PrintCLike.cpp"
  append(L")");
                                                            #line 3722 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                            #line 6056 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 3725 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 6061 "PrintCLike.cpp"
  append(L"consume(");
                                                            #line 3726 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 6065 "PrintCLike.cpp"
  append(L"l1)");
                                                            #line 3727 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 6069 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3729 "PrintCLike.cpp.template"
                                                                printIndented(1, elseWithBraces());
                                                                if (useGlr)
                                                                {
                                                            #line 6076 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 3733 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 6081 "PrintCLike.cpp"
  append(L"stack = ");
                                                            #line 3734 "PrintCLike.cpp.template"
                                                                  if (isGo())
                                                                  {
                                                            #line 6086 "PrintCLike.cpp"
  append(L"&StackNode{");
                                                            #line 3736 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                                    if (! isPython())
                                                                    {
                                                            #line 6094 "PrintCLike.cpp"
  append(L"new ");
                                                            #line 3741 "PrintCLike.cpp.template"
                                                                    }
                                                                    if (! isHaxe() && ! isTypescript()) print(staticPrefix());
                                                            #line 6099 "PrintCLike.cpp"
  append(L"StackNode(");
                                                            #line 3743 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(thiz());
                                                            #line 6104 "PrintCLike.cpp"
  append(L"state, ");
                                                            #line 3745 "PrintCLike.cpp.template"
                                                                  if (grammar->states->hasLookback)
                                                                  {
                                                            #line 6109 "PrintCLike.cpp"
  append(L"lookback, ");
                                                            #line 3747 "PrintCLike.cpp.template"
                                                                  }
                                                                  if (tree)
                                                                  {
                                                                    print(thiz());
                                                            #line 6116 "PrintCLike.cpp"
  append(L"bs");
                                                            #line 3751 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 6122 "PrintCLike.cpp"
  append(L"0");
                                                            #line 3754 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 6126 "PrintCLike.cpp"
  append(L", ");
                                                            #line 3755 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 6130 "PrintCLike.cpp"
  append(L"stack");
                                                            #line 3756 "PrintCLike.cpp.template"
                                                                  print(isGo() ? L"}" : L")");
                                                                  print(semicolon());
                                                                }
                                                                else
                                                                {
                                                            #line 6138 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 3762 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 6143 "PrintCLike.cpp"
  append(L"push(state, lookback");
                                                            #line 3763 "PrintCLike.cpp.template"
                                                                  if (tree)
                                                                  {
                                                            #line 6148 "PrintCLike.cpp"
  append(L", bs");
                                                            #line 3765 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 6152 "PrintCLike.cpp"
  append(L")");
                                                            #line 3766 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                                increaseIndent();
                                                                print(rightBrace());
                                                                decreaseIndent();
                                                            #line 6160 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3772 "PrintCLike.cpp.template"
                                                                if (useGlr) print(thiz());
                                                            #line 6165 "PrintCLike.cpp"
  append(L"state = shift");
                                                            #line 3773 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                print(rightBrace());
                                                            #line 6170 "PrintCLike.cpp"
  append(L"\n");
  append(L"\n");
  append(L"if ");
                                                            #line 3777 "PrintCLike.cpp.template"
                                                                print(ifLeftParen());
                                                            #line 6176 "PrintCLike.cpp"
  append(L"reduce < 0");
                                                            #line 3778 "PrintCLike.cpp.template"
                                                                print(ifRightParen());
                                                                print(leftBrace());
                                                                if (trace)
                                                                {
                                                                  if (isCpp())
                                                                  {
                                                            #line 6185 "PrintCLike.cpp"
  append(L"\n");
  append(L"  fprintf(stderr, ");
                                                            #line 3785 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 6192 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3789 "PrintCLike.cpp.template"
                                                                    print(writeTrace());
                                                                  }
                                                            #line 6198 "PrintCLike.cpp"
  append(L"\"\\\"/>");
                                                            #line 3792 "PrintCLike.cpp.template"
                                                                  if (! isHaxe())
                                                                  {
                                                            #line 6203 "PrintCLike.cpp"
  append(L"\\n\"");
                                                            #line 3794 "PrintCLike.cpp.template"
                                                                    print(endWriteTrace());
                                                                    print(semicolon());
                                                                  }
                                                                  else
                                                                  {
                                                            #line 6211 "PrintCLike.cpp"
  append(L"\";\n");
  append(L"  trace(traceLine);");
                                                            #line 3800 "PrintCLike.cpp.template"
                                                                  }
                                                                }
                                                            #line 6217 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3803 "PrintCLike.cpp.template"
                                                                if (useGlr) print(thiz());
                                                            #line 6222 "PrintCLike.cpp"
  append(L"action = ");
                                                            #line 3804 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 6226 "PrintCLike.cpp"
  append(L"predict(");
                                                            #line 3805 "PrintCLike.cpp.template"
                                                                if (useGlr) print(thiz());
                                                            #line 6230 "PrintCLike.cpp"
  append(L"state)");
                                                            #line 3806 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                if (useGlr)
                                                                {
                                                                  if (isCpp())
                                                                  {
                                                            #line 6238 "PrintCLike.cpp"
  append(L"\n");
  append(L"  break");
                                                            #line 3812 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                  }
                                                                  else
                                                                  {
                                                            #line 6246 "PrintCLike.cpp"
  append(L"\n");
  append(L"  return ");
                                                            #line 3817 "PrintCLike.cpp.template"
                                                                    if (isHaxe() || isTypescript() || isPython()) print(staticPrefix());
                                                            #line 6251 "PrintCLike.cpp"
  append(L"PARSING");
                                                            #line 3818 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                  }
                                                                }
                                                                else
                                                                {
                                                            #line 6259 "PrintCLike.cpp"
  append(L"\n");
  append(L"  nonterminalId = -1");
                                                            #line 3824 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                            #line 6265 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3827 "PrintCLike.cpp.template"
                                                                print(elseWithBraces());
                                                                if (hasCustomCode)
                                                                {
                                                            #line 6271 "PrintCLike.cpp"
  append(L"\n");
  append(L"  nonterminalId = ");
                                                            #line 3831 "PrintCLike.cpp.template"
                                                                  print(staticPrefix());
                                                                  if (isGo())
                                                                  {
                                                            #line 6278 "PrintCLike.cpp"
  append(L"reduction");
                                                            #line 3834 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 6284 "PrintCLike.cpp"
  append(L"REDUCTION");
                                                            #line 3837 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(leftbracket());
                                                            #line 6289 "PrintCLike.cpp"
  append(L"reduce");
                                                            #line 3839 "PrintCLike.cpp.template"
                                                                  print(rightbracket());
                                                                  print(semicolon());
                                                            #line 6294 "PrintCLike.cpp"
  append(L"\n");
  append(L"  reduce = ");
                                                            #line 3842 "PrintCLike.cpp.template"
                                                                  print(staticPrefix());
                                                                  if (isGo())
                                                                  {
                                                            #line 6301 "PrintCLike.cpp"
  append(L"reduction");
                                                            #line 3845 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 6307 "PrintCLike.cpp"
  append(L"REDUCTION");
                                                            #line 3848 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(leftbracket());
                                                            #line 6312 "PrintCLike.cpp"
  append(L"reduce + 1");
                                                            #line 3850 "PrintCLike.cpp.template"
                                                                  print(rightbracket());
                                                                  print(semicolon());
                                                            #line 6317 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if ");
                                                            #line 3853 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                            #line 6322 "PrintCLike.cpp"
  append(L"reduce >= 0");
                                                            #line 3854 "PrintCLike.cpp.template"
                                                                  print(ifRightParen());
                                                                  increaseIndent();
                                                                  print(leftBrace());
                                                                  if (useGlr)
                                                                  {
                                                            #line 6330 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if ");
                                                            #line 3860 "PrintCLike.cpp.template"
                                                                    print(ifLeftParen());
                                                                    print(thiz());
                                                                    if (isGo())
                                                                    {
                                                            #line 6338 "PrintCLike.cpp"
  append(L"IsUnambiguous");
                                                            #line 3864 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 6344 "PrintCLike.cpp"
  append(L"isUnambiguous");
                                                            #line 3867 "PrintCLike.cpp.template"
                                                                    }
                                                                    if (! isScala()) print(L"()");
                                                                    print(ifRightParen());
                                                                    print(leftBrace());
                                                            #line 6351 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 3872 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                                    print(isGo() && useGlr ? L"E" : L"e");
                                                            #line 6357 "PrintCLike.cpp"
  append(L"xecute(reduce)");
                                                            #line 3874 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 6361 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3876 "PrintCLike.cpp.template"
                                                                    print(elseWithBraces());
                                                            #line 6366 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 3878 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 6371 "PrintCLike.cpp"
  append(L"deferredCode = ");
                                                            #line 3879 "PrintCLike.cpp.template"
                                                                    if (isGo())
                                                                    {
                                                            #line 6376 "PrintCLike.cpp"
  append(L"&DeferredCode{");
                                                            #line 3882 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                                      if (! isPython())
                                                                      {
                                                            #line 6384 "PrintCLike.cpp"
  append(L"new ");
                                                            #line 3887 "PrintCLike.cpp.template"
                                                                      }
                                                                      if (! isHaxe() && ! isTypescript()) print(staticPrefix());
                                                            #line 6389 "PrintCLike.cpp"
  append(L"DeferredCode(");
                                                            #line 3889 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(thiz());
                                                            #line 6394 "PrintCLike.cpp"
  append(L"deferredCode, reduce, ");
                                                            #line 3891 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 6398 "PrintCLike.cpp"
  append(L"b0, ");
                                                            #line 3892 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 6402 "PrintCLike.cpp"
  append(L"e0");
                                                            #line 3894 "PrintCLike.cpp.template"
                                                                    if (isGo())
                                                                    {
                                                            #line 6407 "PrintCLike.cpp"
  append(L"}");
                                                            #line 3897 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 6413 "PrintCLike.cpp"
  append(L")");
                                                            #line 3901 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(semicolon());
                                                                    increaseIndent();
                                                                    print(rightBrace());
                                                                    decreaseIndent();
                                                                  }
                                                                  else
                                                                  {
                                                            #line 6424 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3910 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                                    print(isGo() && useGlr ? L"E" : L"e");
                                                            #line 6430 "PrintCLike.cpp"
  append(L"xecute(reduce)");
                                                            #line 3912 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                  }
                                                                  print(rightBrace());
                                                                  decreaseIndent();
                                                                }
                                                                else
                                                                {
                                                            #line 6440 "PrintCLike.cpp"
  append(L"\n");
  append(L"  nonterminalId = reduce");
                                                            #line 3920 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                                if (trace)
                                                                {
                                                            #line 6448 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if ");
                                                            #line 3925 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                            #line 6453 "PrintCLike.cpp"
  append(L"shift >= 0");
                                                            #line 3926 "PrintCLike.cpp.template"
                                                                  print(ifRightParen());
                                                                  printIndented(1, leftBrace());
                                                                  if (isCpp())
                                                                  {
                                                            #line 6460 "PrintCLike.cpp"
  append(L"\n");
  append(L"    fprintf(stderr, ");
                                                            #line 3931 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 6467 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 3935 "PrintCLike.cpp.template"
                                                                    print(writeTrace());
                                                                  }
                                                            #line 6473 "PrintCLike.cpp"
  append(L"\" \"");
                                                            #line 3937 "PrintCLike.cpp.template"
                                                                  print(endWriteTrace());
                                                                  print(semicolon());
                                                                  increaseIndent();
                                                                  print(rightBrace());
                                                                  decreaseIndent();
                                                                  if (isCpp())
                                                                  {
                                                            #line 6483 "PrintCLike.cpp"
  append(L"\n");
  append(L"  fprintf(stderr, \"reduce\\\" nonterminal=\\\"%s\\\" count=\\\"%d\\\"/>\\n\", ");
                                                            #line 3945 "PrintCLike.cpp.template"
                                                                    if (stringIntroducer()[0])
                                                                    {
                                                            #line 6489 "PrintCLike.cpp"
  append(L"Utf8Encoder::encode(");
                                                            #line 3947 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 6493 "PrintCLike.cpp"
  append(L"xmlEscape(");
                                                            #line 3948 "PrintCLike.cpp.template"
                                                                    print(isGo() ? L"nonterminal" : L"NONTERMINAL");
                                                            #line 6497 "PrintCLike.cpp"
  append(L"[nonterminalId], 0).c_str()");
                                                            #line 3950 "PrintCLike.cpp.template"
                                                                    if (stringIntroducer()[0])
                                                                    {
                                                            #line 6502 "PrintCLike.cpp"
  append(L").c_str()");
                                                            #line 3952 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 6506 "PrintCLike.cpp"
  append(L", symbols);");
                                                            #line 3953 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 6512 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3957 "PrintCLike.cpp.template"
                                                                    print(writeTrace());
                                                            #line 6517 "PrintCLike.cpp"
  append(L"\"reduce\\\" nonterminal=\\\"\" + ");
                                                            #line 3959 "PrintCLike.cpp.template"
                                                                    print(staticPrefix());
                                                            #line 6521 "PrintCLike.cpp"
  append(L"xmlEscape(");
                                                            #line 3960 "PrintCLike.cpp.template"
                                                                    print(staticPrefix());
                                                                    print(isGo() ? L"nonterminal" : L"NONTERMINAL");
                                                                    print(leftbracket());
                                                            #line 6527 "PrintCLike.cpp"
  append(L"nonterminalId");
                                                            #line 3963 "PrintCLike.cpp.template"
                                                                    print(rightbracket());
                                                            #line 6531 "PrintCLike.cpp"
  append(L") + \"\\\" count=\\\"\" + ");
                                                            #line 3965 "PrintCLike.cpp.template"
                                                                    if (isPython())
                                                                    {
                                                            #line 6536 "PrintCLike.cpp"
  append(L"str(");
                                                            #line 3968 "PrintCLike.cpp.template"
                                                                    }
                                                                    else if (isGo())
                                                                    {
                                                            #line 6542 "PrintCLike.cpp"
  append(L"strconv.Itoa(");
                                                            #line 3972 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 6546 "PrintCLike.cpp"
  append(L"symbols");
                                                            #line 3974 "PrintCLike.cpp.template"
                                                                    if (isGo() || isPython())
                                                                    {
                                                            #line 6551 "PrintCLike.cpp"
  append(L")");
                                                            #line 3977 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 6555 "PrintCLike.cpp"
  append(L" + \"\\\"/>");
                                                            #line 3979 "PrintCLike.cpp.template"
                                                                    if (! isHaxe())
                                                                    {
                                                            #line 6560 "PrintCLike.cpp"
  append(L"\\n\"");
                                                            #line 3982 "PrintCLike.cpp.template"
                                                                      print(endWriteTrace());
                                                                      print(semicolon());
                                                                    }
                                                                    else
                                                                    {
                                                            #line 6568 "PrintCLike.cpp"
  append(L"\";\n");
  append(L"  trace(traceLine);");
                                                            #line 3988 "PrintCLike.cpp.template"
                                                                    }
                                                                  }
                                                                }
                                                                if (tree)
                                                                {
                                                            #line 6577 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if ");
                                                            #line 3994 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                            #line 6582 "PrintCLike.cpp"
  append(L"symbols > 0");
                                                            #line 3995 "PrintCLike.cpp.template"
                                                                  print(ifRightParen());
                                                                  printIndented(1, leftBrace());
                                                                  if (useGlr)
                                                                  {
                                                                    if (isCpp())
                                                                    {
                                                            #line 6591 "PrintCLike.cpp"
  append(L"\n");
  append(L"    stack = stack->pop(symbols - 1);");
                                                            #line 4002 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                                      increaseIndent(2);
                                                                      if (isHaxe())
                                                                      {
                                                            #line 6601 "PrintCLike.cpp"
  append(L"\n");
  append(L"for (i in 1...symbols)");
                                                            #line 4009 "PrintCLike.cpp.template"
                                                                      }
                                                                      else if (isScala())
                                                                      {
                                                            #line 6608 "PrintCLike.cpp"
  append(L"\n");
  append(L"var i = 0\n");
  append(L"for (i <- 2 to symbols)");
                                                            #line 4014 "PrintCLike.cpp.template"
                                                                      }
                                                                      else if (isPython())
                                                                      {
                                                            #line 6616 "PrintCLike.cpp"
  append(L"\n");
  append(L"for _ in range(symbols - 1):");
                                                            #line 4018 "PrintCLike.cpp.template"
                                                                      }
                                                                      else
                                                                      {
                                                            #line 6623 "PrintCLike.cpp"
  append(L"\n");
  append(L"for ");
                                                            #line 4022 "PrintCLike.cpp.template"
                                                                        print(ifLeftParen());
                                                                        print(intVar());
                                                            #line 6629 "PrintCLike.cpp"
  append(L"i");
                                                            #line 4024 "PrintCLike.cpp.template"
                                                                        print(assign());
                                                            #line 6633 "PrintCLike.cpp"
  append(L"1; i < symbols; i++");
                                                            #line 4025 "PrintCLike.cpp.template"
                                                                        print(ifRightParen());
                                                                      }
                                                                      print(leftBrace());
                                                            #line 6639 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4029 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 6644 "PrintCLike.cpp"
  append(L"stack = ");
                                                            #line 4030 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 6648 "PrintCLike.cpp"
  append(L"stack.link");
                                                            #line 4031 "PrintCLike.cpp.template"
                                                                      if (isTypescript()) print(L"!");
                                                                      print(semicolon());
                                                                      print(rightBrace());
                                                                      decreaseIndent(2);
                                                                    }
                                                            #line 6656 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4037 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 6661 "PrintCLike.cpp"
  append(L"state = ");
                                                            #line 4038 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 6665 "PrintCLike.cpp"
  append(L"stack");
                                                            #line 4039 "PrintCLike.cpp.template"
                                                                    print(arrow());
                                                            #line 6669 "PrintCLike.cpp"
  append(L"state");
                                                            #line 4040 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 6673 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4042 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 6678 "PrintCLike.cpp"
  append(L"bs = ");
                                                            #line 4043 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 6682 "PrintCLike.cpp"
  append(L"stack");
                                                            #line 4044 "PrintCLike.cpp.template"
                                                                    print(arrow());
                                                            #line 6686 "PrintCLike.cpp"
  append(L"pos");
                                                            #line 4045 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                    if (isCpp())
                                                                    {
                                                            #line 6692 "PrintCLike.cpp"
  append(L"\n");
  append(L"    stack = stack->pop(1);");
                                                            #line 4049 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 6699 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4053 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 6704 "PrintCLike.cpp"
  append(L"stack = ");
                                                            #line 4054 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 6708 "PrintCLike.cpp"
  append(L"stack.link");
                                                            #line 4055 "PrintCLike.cpp.template"
                                                                      if (isTypescript()) print(L"!");
                                                                      print(semicolon());
                                                                    }
                                                                  }
                                                                  else
                                                                  {
                                                            #line 6717 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4062 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 6722 "PrintCLike.cpp"
  append(L"top -= symbols * 3");
                                                            #line 4063 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 6726 "PrintCLike.cpp"
  append(L"\n");
  append(L"    state = ");
                                                            #line 4065 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 6731 "PrintCLike.cpp"
  append(L"iStack");
                                                            #line 4066 "PrintCLike.cpp.template"
                                                                    print(leftbracket());
                                                                    print(thiz());
                                                            #line 6736 "PrintCLike.cpp"
  append(L"top + 2");
                                                            #line 4068 "PrintCLike.cpp.template"
                                                                    print(rightbracket());
                                                                    print(semicolon());
                                                            #line 6741 "PrintCLike.cpp"
  append(L"\n");
  append(L"    bs = ");
                                                            #line 4071 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 6746 "PrintCLike.cpp"
  append(L"iStack");
                                                            #line 4072 "PrintCLike.cpp.template"
                                                                    print(leftbracket());
                                                                    print(thiz());
                                                            #line 6751 "PrintCLike.cpp"
  append(L"top + 1");
                                                            #line 4074 "PrintCLike.cpp.template"
                                                                    print(rightbracket());
                                                                    print(semicolon());
                                                                  }
                                                            #line 6757 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4078 "PrintCLike.cpp.template"
                                                                  printIndented(1, elseWithBraces());
                                                            #line 6762 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4080 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 6767 "PrintCLike.cpp"
  append(L"bs = ");
                                                            #line 4081 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 6771 "PrintCLike.cpp"
  append(L"b1");
                                                            #line 4082 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                            #line 6775 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4084 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 6780 "PrintCLike.cpp"
  append(L"es = ");
                                                            #line 4085 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 6784 "PrintCLike.cpp"
  append(L"b1");
                                                            #line 4086 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                  increaseIndent();
                                                                  print(rightBrace());
                                                                  decreaseIndent();
                                                            #line 6791 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if ");
                                                            #line 4091 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                            #line 6796 "PrintCLike.cpp"
  append(L"nonterminalId == ");
                                                            #line 4092 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 6800 "PrintCLike.cpp"
  append(L"target ");
                                                            #line 4093 "PrintCLike.cpp.template"
                                                                  if (isPython())
                                                                  {
                                                            #line 6805 "PrintCLike.cpp"
  append(L"and");
                                                            #line 4095 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 6811 "PrintCLike.cpp"
  append(L"&&");
                                                            #line 4098 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 6815 "PrintCLike.cpp"
  append(L" ");
                                                            #line 4099 "PrintCLike.cpp.template"
                                                                  if (useGlr)
                                                                  {
                                                                    print(thiz());
                                                            #line 6821 "PrintCLike.cpp"
  append(L"stack");
                                                            #line 4102 "PrintCLike.cpp.template"
                                                                    print(arrow());
                                                            #line 6825 "PrintCLike.cpp"
  append(L"link == ");
                                                            #line 4103 "PrintCLike.cpp.template"
                                                                    print(nullPtr());
                                                                  }
                                                                  else
                                                                  {
                                                            #line 6832 "PrintCLike.cpp"
  append(L"t == ");
                                                            #line 4107 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 6836 "PrintCLike.cpp"
  append(L"top");
                                                            #line 4108 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(ifRightParen());
                                                                  printIndented(1, leftBrace());
                                                            #line 6842 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4112 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 6847 "PrintCLike.cpp"
  append(L"bs = ");
                                                            #line 4113 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 6851 "PrintCLike.cpp"
  append(L"bw");
                                                            #line 4114 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                            #line 6855 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4116 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 6860 "PrintCLike.cpp"
  append(L"es = ");
                                                            #line 4117 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 6864 "PrintCLike.cpp"
  append(L"b1");
                                                            #line 4118 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                            #line 6868 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4120 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 6873 "PrintCLike.cpp"
  append(L"bw = ");
                                                            #line 4121 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 6877 "PrintCLike.cpp"
  append(L"b1");
                                                            #line 4122 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                  increaseIndent();
                                                                  print(rightBrace());
                                                                  decreaseIndent();
                                                            #line 6884 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if ");
                                                            #line 4127 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                                  if (useGlr) print(thiz());
                                                            #line 6890 "PrintCLike.cpp"
  append(L"eventHandler != ");
                                                            #line 4129 "PrintCLike.cpp.template"
                                                                  print(nullPtr());
                                                                  print(ifRightParen());
                                                                  printIndented(1, leftBrace());
                                                                  if (useGlr)
                                                                  {
                                                            #line 6898 "PrintCLike.cpp"
  append(L"\n");
  append(L"    if ");
                                                            #line 4135 "PrintCLike.cpp.template"
                                                                    print(ifLeftParen());
                                                                    print(thiz());
                                                                    if (isGo())
                                                                    {
                                                            #line 6906 "PrintCLike.cpp"
  append(L"IsUnambiguous");
                                                            #line 4139 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 6912 "PrintCLike.cpp"
  append(L"isUnambiguous");
                                                            #line 4142 "PrintCLike.cpp.template"
                                                                    }
                                                                    if (! isScala()) print(L"()");
                                                                    print(ifRightParen());
                                                                    printIndented(2, leftBrace());
                                                                    increaseIndent();
                                                                  }
                                                            #line 6921 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4149 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 6926 "PrintCLike.cpp"
  append(L"eventHandler");
                                                            #line 4150 "PrintCLike.cpp.template"
                                                                  print(arrow());
                                                                  if (isGo())
                                                                  {
                                                            #line 6932 "PrintCLike.cpp"
  append(L"N");
                                                            #line 4153 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 6938 "PrintCLike.cpp"
  append(L"n");
                                                            #line 4156 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 6942 "PrintCLike.cpp"
  append(L"onterminal(");
                                                            #line 4157 "PrintCLike.cpp.template"
                                                                  print(staticPrefix());
                                                                  print(isGo() ? L"nonterminal" : L"NONTERMINAL");
                                                                  print(leftbracket());
                                                            #line 6948 "PrintCLike.cpp"
  append(L"nonterminalId");
                                                            #line 4160 "PrintCLike.cpp.template"
                                                                  print(rightbracket());
                                                            #line 6952 "PrintCLike.cpp"
  append(L", ");
                                                            #line 4161 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 6956 "PrintCLike.cpp"
  append(L"bs, ");
                                                            #line 4162 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 6960 "PrintCLike.cpp"
  append(L"es, symbols)");
                                                            #line 4164 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                  if (useGlr)
                                                                  {
                                                                    decreaseIndent();
                                                            #line 6967 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4169 "PrintCLike.cpp.template"
                                                                    printIndented(2, elseWithBraces());
                                                            #line 6972 "PrintCLike.cpp"
  append(L"\n");
  append(L"      ");
                                                            #line 4171 "PrintCLike.cpp.template"
                                                                    if (useGlr) print(thiz());
                                                            #line 6977 "PrintCLike.cpp"
  append(L"deferredEvent = ");
                                                            #line 4172 "PrintCLike.cpp.template"
                                                                    if (isGo())
                                                                    {
                                                            #line 6982 "PrintCLike.cpp"
  append(L"&NonterminalEvent{&AbstractDeferredEvent{this.deferredEvent, nonterminal[nonterminalId], this.bs, this.es}, symbols}");
                                                            #line 4175 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                                      if (! isPython())
                                                                      {
                                                            #line 6990 "PrintCLike.cpp"
  append(L"new ");
                                                            #line 4180 "PrintCLike.cpp.template"
                                                                      }
                                                                      if (! isHaxe() && ! isTypescript()) print(staticPrefix());
                                                                      if (isJavascript() || isTypescript())
                                                                      {
                                                            #line 6997 "PrintCLike.cpp"
  append(L"DeferredEvent");
                                                            #line 4184 "PrintCLike.cpp.template"
                                                                      }
                                                                      else
                                                                      {
                                                            #line 7003 "PrintCLike.cpp"
  append(L"NonterminalEvent");
                                                            #line 4187 "PrintCLike.cpp.template"
                                                                      }
                                                            #line 7007 "PrintCLike.cpp"
  append(L"(");
                                                            #line 4188 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 7011 "PrintCLike.cpp"
  append(L"deferredEvent, ");
                                                            #line 4189 "PrintCLike.cpp.template"
                                                                      print(staticPrefix());
                                                            #line 7015 "PrintCLike.cpp"
  append(L"NONTERMINAL");
                                                            #line 4190 "PrintCLike.cpp.template"
                                                                      print(leftbracket());
                                                            #line 7019 "PrintCLike.cpp"
  append(L"nonterminalId");
                                                            #line 4191 "PrintCLike.cpp.template"
                                                                      print(rightbracket());
                                                            #line 7023 "PrintCLike.cpp"
  append(L", ");
                                                            #line 4192 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 7027 "PrintCLike.cpp"
  append(L"bs, ");
                                                            #line 4194 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 7031 "PrintCLike.cpp"
  append(L"es, symbols)");
                                                            #line 4196 "PrintCLike.cpp.template"
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
                                                            #line 7046 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if ");
                                                            #line 4209 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                            #line 7051 "PrintCLike.cpp"
  append(L"symbols > 0");
                                                            #line 4210 "PrintCLike.cpp.template"
                                                                  print(ifRightParen());
                                                                  printIndented(1, leftBrace());
                                                                  if (useGlr)
                                                                  {
                                                                    if (isCpp())
                                                                    {
                                                            #line 7060 "PrintCLike.cpp"
  append(L"\n");
  append(L"    stack = stack->pop(symbols - 1);");
                                                            #line 4217 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                                      increaseIndent(2);
                                                                      if (isHaxe())
                                                                      {
                                                            #line 7070 "PrintCLike.cpp"
  append(L"\n");
  append(L"for (i in 1...symbols)");
                                                            #line 4224 "PrintCLike.cpp.template"
                                                                      }
                                                                      else if (isScala())
                                                                      {
                                                            #line 7077 "PrintCLike.cpp"
  append(L"\n");
  append(L"var i = 0\n");
  append(L"for (i <- 2 to symbols)");
                                                            #line 4229 "PrintCLike.cpp.template"
                                                                      }
                                                                      else if (isPython())
                                                                      {
                                                            #line 7085 "PrintCLike.cpp"
  append(L"\n");
  append(L"for _ in range(symbols - 1):");
                                                            #line 4233 "PrintCLike.cpp.template"
                                                                      }
                                                                      else
                                                                      {
                                                            #line 7092 "PrintCLike.cpp"
  append(L"\n");
  append(L"for ");
                                                            #line 4237 "PrintCLike.cpp.template"
                                                                        print(ifLeftParen());
                                                                        print(intVar());
                                                            #line 7098 "PrintCLike.cpp"
  append(L"i");
                                                            #line 4239 "PrintCLike.cpp.template"
                                                                        print(assign());
                                                            #line 7102 "PrintCLike.cpp"
  append(L"1; i < symbols; i++");
                                                            #line 4240 "PrintCLike.cpp.template"
                                                                        print(ifRightParen());
                                                                      }
                                                                      print(leftBrace());
                                                            #line 7108 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4244 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 7113 "PrintCLike.cpp"
  append(L"stack = ");
                                                            #line 4245 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 7117 "PrintCLike.cpp"
  append(L"stack.link");
                                                            #line 4246 "PrintCLike.cpp.template"
                                                                      if (isTypescript()) print(L"!");
                                                                      print(semicolon());
                                                                      print(rightBrace());
                                                                      decreaseIndent(2);
                                                                    }
                                                            #line 7125 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4253 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7130 "PrintCLike.cpp"
  append(L"state = ");
                                                            #line 4254 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7134 "PrintCLike.cpp"
  append(L"stack");
                                                            #line 4255 "PrintCLike.cpp.template"
                                                                    print(arrow());
                                                            #line 7138 "PrintCLike.cpp"
  append(L"state");
                                                            #line 4256 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                    if (tree)
                                                                    {
                                                            #line 7144 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4260 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 7149 "PrintCLike.cpp"
  append(L"bs = ");
                                                            #line 4261 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 7153 "PrintCLike.cpp"
  append(L"stack");
                                                            #line 4262 "PrintCLike.cpp.template"
                                                                      print(arrow());
                                                            #line 7157 "PrintCLike.cpp"
  append(L"pos");
                                                            #line 4263 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                                    }
                                                                    if (isCpp())
                                                                    {
                                                            #line 7164 "PrintCLike.cpp"
  append(L"\n");
  append(L"    stack = stack->pop(1);");
                                                            #line 4268 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 7171 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4272 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 7176 "PrintCLike.cpp"
  append(L"stack = ");
                                                            #line 4273 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 7180 "PrintCLike.cpp"
  append(L"stack.link");
                                                            #line 4274 "PrintCLike.cpp.template"
                                                                      if (isTypescript()) print(L"!");
                                                                      print(semicolon());
                                                                    }
                                                                  }
                                                                  else
                                                                  {
                                                            #line 7189 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4281 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7194 "PrintCLike.cpp"
  append(L"top -= symbols << 1;\n");
  append(L"    state = ");
                                                            #line 4283 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7199 "PrintCLike.cpp"
  append(L"iStack");
                                                            #line 4284 "PrintCLike.cpp.template"
                                                                    print(leftbracket());
                                                                    print(thiz());
                                                            #line 7204 "PrintCLike.cpp"
  append(L"top + 1");
                                                            #line 4286 "PrintCLike.cpp.template"
                                                                    print(rightbracket());
                                                                    print(semicolon());
                                                                  }
                                                                  increaseIndent();
                                                                  print(rightBrace());
                                                                  decreaseIndent();
                                                                  if (useGlr && tree)
                                                                  {
                                                            #line 7215 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if ");
                                                            #line 4295 "PrintCLike.cpp.template"
                                                                    print(ifLeftParen());
                                                            #line 7220 "PrintCLike.cpp"
  append(L"nonterminalId == ");
                                                            #line 4296 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7224 "PrintCLike.cpp"
  append(L"target ");
                                                            #line 4297 "PrintCLike.cpp.template"
                                                                    if (isPython())
                                                                    {
                                                            #line 7229 "PrintCLike.cpp"
  append(L"and");
                                                            #line 4299 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 7235 "PrintCLike.cpp"
  append(L"&&");
                                                            #line 4302 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 7239 "PrintCLike.cpp"
  append(L" ");
                                                            #line 4303 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7243 "PrintCLike.cpp"
  append(L"stack");
                                                            #line 4304 "PrintCLike.cpp.template"
                                                                    print(arrow());
                                                            #line 7247 "PrintCLike.cpp"
  append(L"link == ");
                                                            #line 4305 "PrintCLike.cpp.template"
                                                                    print(nullPtr());
                                                                    print(ifRightParen());
                                                                    printIndented(1, leftBrace());
                                                            #line 7253 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4309 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7258 "PrintCLike.cpp"
  append(L"bs = ");
                                                            #line 4310 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7262 "PrintCLike.cpp"
  append(L"bw");
                                                            #line 4311 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 7266 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4313 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7271 "PrintCLike.cpp"
  append(L"bw = ");
                                                            #line 4314 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7275 "PrintCLike.cpp"
  append(L"b1");
                                                            #line 4315 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                    increaseIndent();
                                                                    print(rightBrace());
                                                                    decreaseIndent();
                                                                  }
                                                                }
                                                            #line 7284 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4322 "PrintCLike.cpp.template"
                                                                if (useGlr) print(thiz());
                                                            #line 7289 "PrintCLike.cpp"
  append(L"action = ");
                                                            #line 4323 "PrintCLike.cpp.template"
                                                                print(staticPrefix());
                                                                print(isGo() ? L"reduceAction" : L"goTo");
                                                            #line 7294 "PrintCLike.cpp"
  append(L"(nonterminalId, ");
                                                            #line 4325 "PrintCLike.cpp.template"
                                                                if (useGlr) print(thiz());
                                                            #line 7298 "PrintCLike.cpp"
  append(L"state)");
                                                            #line 4326 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                print(rightBrace());
                                                                decreaseIndent();
                                                                print(rightBrace());
                                                                decreaseIndent();
                                                                if (useGlr)
                                                                {
                                                                  if (isScala())
                                                                  {
                                                            #line 7310 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ERROR");
                                                            #line 4336 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isCpp())
                                                                  {
                                                            #line 7317 "PrintCLike.cpp"
  append(L"\n");
  append(L"  return PARSING;");
                                                            #line 4340 "PrintCLike.cpp.template"
                                                                  }
                                                                }
                                                                print(rightBrace());
                                                                if (isJavascript() && useGlr)
                                                                {
                                                            #line 7326 "PrintCLike.cpp"
  append(L";");
                                                            #line 4345 "PrintCLike.cpp.template"
                                                                }
                                                            #line 7330 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4347 "PrintCLike.cpp.template"
                                                                if ((tree || hasCustomCode) && useGlr)
                                                                {
                                                                  openMethod(boolType(), L"", L"isUnambiguous", L"", false, L"ParsingThread");
                                                                  print(leftBrace());
                                                            #line 7337 "PrintCLike.cpp"
  append(L"\n");
  append(L"  return ");
                                                            #line 4352 "PrintCLike.cpp.template"
                                                                  if (isPython())
                                                                  {
                                                            #line 7343 "PrintCLike.cpp"
  append(L"len(self.threads) == 0");
                                                            #line 4354 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                                    print(thiz());
                                                            #line 7350 "PrintCLike.cpp"
  append(L"threads");
                                                            #line 4358 "PrintCLike.cpp.template"
                                                                    print(arrow());
                                                                    if (isCpp())
                                                                    {
                                                            #line 7356 "PrintCLike.cpp"
  append(L"empty();");
                                                            #line 4361 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 7362 "PrintCLike.cpp"
  append(L"isEmpty");
                                                            #line 4364 "PrintCLike.cpp.template"
                                                                      if (! isScala()) print(L"()");
                                                                      print(semicolon());
                                                                    }
                                                                  }
                                                                  print(rightBrace());
                                                            #line 7370 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4370 "PrintCLike.cpp.template"
                                                                }
                                                                if (hasCustomCode)
                                                                {
                                                                  if (useGlr)
                                                                  {
                                                                    if (isJavascript())
                                                                    {
                                                            #line 7380 "PrintCLike.cpp"
  append(L"\n");
  append(L"this.executeDeferredCode = function()\n");
                                                            #line 4379 "PrintCLike.cpp.template"
                                                                    }
                                                                    else if (isTypescript())
                                                                    {
                                                            #line 7387 "PrintCLike.cpp"
  append(L"\n");
  append(L"executeDeferredCode()\n");
                                                            #line 4384 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                                      openMethod(voidType(), L"", L"executeDeferredCode", L"", false, L"ParsingThread");
                                                                    }
                                                                    print(leftBrace());
                                                                    increaseIndent();
                                                            #line 7398 "PrintCLike.cpp"
  append(L"\n");
  append(L"if ");
                                                            #line 4392 "PrintCLike.cpp.template"
                                                                    print(ifLeftParen());
                                                                    print(thiz());
                                                            #line 7404 "PrintCLike.cpp"
  append(L"deferredCode != ");
                                                            #line 4394 "PrintCLike.cpp.template"
                                                                    print(nullPtr());
                                                                    print(ifRightParen());
                                                                    print(leftBrace());
                                                                    increaseIndent();
                                                            #line 7411 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4399 "PrintCLike.cpp.template"
                                                                    if (isJavascript() || isHaxe() || isScala() || isTypescript())
                                                                    {
                                                            #line 7416 "PrintCLike.cpp"
  append(L"var ");
                                                            #line 4401 "PrintCLike.cpp.template"
                                                                    }
                                                                    else if (! isGo() && ! isPython())
                                                                    {
                                                            #line 7422 "PrintCLike.cpp"
  append(L"DeferredCode ");
                                                            #line 4404 "PrintCLike.cpp.template"
                                                                    }
                                                                    if (isCpp()) print(L"*");
                                                            #line 7427 "PrintCLike.cpp"
  append(L"predecessor");
                                                            #line 4406 "PrintCLike.cpp.template"
                                                                    print(assign());
                                                                    print(thiz());
                                                            #line 7432 "PrintCLike.cpp"
  append(L"deferredCode");
                                                            #line 4408 "PrintCLike.cpp.template"
                                                                    print(arrow());
                                                            #line 7436 "PrintCLike.cpp"
  append(L"link");
                                                            #line 4409 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 7440 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4411 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7444 "PrintCLike.cpp"
  append(L"deferredCode");
                                                            #line 4412 "PrintCLike.cpp.template"
                                                                    print(arrow());
                                                            #line 7448 "PrintCLike.cpp"
  append(L"link = ");
                                                            #line 4413 "PrintCLike.cpp.template"
                                                                    print(nullPtr());
                                                                    print(semicolon());
                                                                    if (isGo())
                                                                    {
                                                            #line 7455 "PrintCLike.cpp"
  append(L"\n");
  append(L"for ");
                                                            #line 4418 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 7462 "PrintCLike.cpp"
  append(L"\n");
  append(L"while ");
                                                            #line 4422 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(ifLeftParen());
                                                            #line 7468 "PrintCLike.cpp"
  append(L"predecessor != ");
                                                            #line 4424 "PrintCLike.cpp.template"
                                                                    print(nullPtr());
                                                                    print(ifRightParen());
                                                                    print(leftBrace());
                                                            #line 7474 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4428 "PrintCLike.cpp.template"
                                                                    if (isJavascript() || isHaxe() || isScala() || isTypescript())
                                                                    {
                                                            #line 7480 "PrintCLike.cpp"
  append(L"var ");
                                                            #line 4430 "PrintCLike.cpp.template"
                                                                    }
                                                                    else if (! isGo() && ! isPython())
                                                                    {
                                                            #line 7486 "PrintCLike.cpp"
  append(L"DeferredCode ");
                                                            #line 4433 "PrintCLike.cpp.template"
                                                                    }
                                                                    if (isCpp()) print(L"*");
                                                            #line 7491 "PrintCLike.cpp"
  append(L"nextCode");
                                                            #line 4435 "PrintCLike.cpp.template"
                                                                    print(assign());
                                                            #line 7495 "PrintCLike.cpp"
  append(L"predecessor");
                                                            #line 4436 "PrintCLike.cpp.template"
                                                                    print(arrow());
                                                            #line 7499 "PrintCLike.cpp"
  append(L"link");
                                                            #line 4437 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 7503 "PrintCLike.cpp"
  append(L"\n");
  append(L"  predecessor");
                                                            #line 4439 "PrintCLike.cpp.template"
                                                                    print(arrow());
                                                            #line 7508 "PrintCLike.cpp"
  append(L"link = ");
                                                            #line 4440 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7512 "PrintCLike.cpp"
  append(L"deferredCode");
                                                            #line 4441 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 7516 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4443 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7521 "PrintCLike.cpp"
  append(L"deferredCode = predecessor");
                                                            #line 4444 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 7525 "PrintCLike.cpp"
  append(L"\n");
  append(L"  predecessor = nextCode");
                                                            #line 4446 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                    print(rightBrace());
                                                            #line 7531 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4449 "PrintCLike.cpp.template"
                                                                    print(intVar());
                                                            #line 7535 "PrintCLike.cpp"
  append(L"b0t");
                                                            #line 4450 "PrintCLike.cpp.template"
                                                                    print(assign());
                                                                    print(thiz());
                                                            #line 7540 "PrintCLike.cpp"
  append(L"b0");
                                                            #line 4452 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 7544 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4454 "PrintCLike.cpp.template"
                                                                    print(intVar());
                                                            #line 7548 "PrintCLike.cpp"
  append(L"e0t");
                                                            #line 4455 "PrintCLike.cpp.template"
                                                                    print(assign());
                                                                    print(thiz());
                                                            #line 7553 "PrintCLike.cpp"
  append(L"e0");
                                                            #line 4457 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                    if (isGo())
                                                                    {
                                                            #line 7559 "PrintCLike.cpp"
  append(L"\n");
  append(L"for ");
                                                            #line 4461 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 7566 "PrintCLike.cpp"
  append(L"\n");
  append(L"while ");
                                                            #line 4465 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(ifLeftParen());
                                                                    print(thiz());
                                                            #line 7573 "PrintCLike.cpp"
  append(L"deferredCode != ");
                                                            #line 4468 "PrintCLike.cpp.template"
                                                                    print(nullPtr());
                                                                    print(ifRightParen());
                                                                    print(leftBrace());
                                                            #line 7579 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4472 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7584 "PrintCLike.cpp"
  append(L"b0 = ");
                                                            #line 4473 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7588 "PrintCLike.cpp"
  append(L"deferredCode");
                                                            #line 4474 "PrintCLike.cpp.template"
                                                                    print(arrow());
                                                            #line 7592 "PrintCLike.cpp"
  append(L"b0");
                                                            #line 4475 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 7596 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4477 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7601 "PrintCLike.cpp"
  append(L"e0 = ");
                                                            #line 4478 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7605 "PrintCLike.cpp"
  append(L"deferredCode");
                                                            #line 4479 "PrintCLike.cpp.template"
                                                                    print(arrow());
                                                            #line 7609 "PrintCLike.cpp"
  append(L"e0");
                                                            #line 4480 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 7613 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4482 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                                    print(isGo() ? L"E" : L"e");
                                                            #line 7619 "PrintCLike.cpp"
  append(L"xecute(");
                                                            #line 4484 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7623 "PrintCLike.cpp"
  append(L"deferredCode");
                                                            #line 4485 "PrintCLike.cpp.template"
                                                                    print(arrow());
                                                            #line 7627 "PrintCLike.cpp"
  append(L"codeId)");
                                                            #line 4486 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                    if (isCpp())
                                                                    {
                                                            #line 7633 "PrintCLike.cpp"
  append(L"\n");
  append(L"  DeferredCode *next = deferredCode->link;\n");
  append(L"  delete deferredCode;\n");
  append(L"  deferredCode = next;");
                                                            #line 4492 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 7642 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4496 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 7647 "PrintCLike.cpp"
  append(L"deferredCode = ");
                                                            #line 4497 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 7651 "PrintCLike.cpp"
  append(L"deferredCode");
                                                            #line 4498 "PrintCLike.cpp.template"
                                                                      print(arrow());
                                                            #line 7655 "PrintCLike.cpp"
  append(L"link");
                                                            #line 4499 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                                    }
                                                                    print(rightBrace());
                                                            #line 7661 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4503 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7665 "PrintCLike.cpp"
  append(L"b0 = b0t");
                                                            #line 4504 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 7669 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4506 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7673 "PrintCLike.cpp"
  append(L"e0 = e0t");
                                                            #line 4507 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                    decreaseIndent();
                                                                    print(rightBrace());
                                                                    decreaseIndent();
                                                                    print(rightBrace());
                                                            #line 7681 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4513 "PrintCLike.cpp.template"
                                                                  }
                                                                  openMethod(voidType(), L"", L"execute", L"int reduce", false, useGlr ? L"ParsingThread" : className.c_str());
                                                                  print(leftBrace());
                                                                  increaseIndent();
                                                                  if (! isPython())
                                                                  {
                                                            #line 7690 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4520 "PrintCLike.cpp.template"
                                                                    if (! isScala())
                                                                    {
                                                            #line 7695 "PrintCLike.cpp"
  append(L"switch ");
                                                            #line 4522 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(ifLeftParen());
                                                            #line 7700 "PrintCLike.cpp"
  append(L"reduce");
                                                            #line 4524 "PrintCLike.cpp.template"
                                                                    print(ifRightParen());
                                                                    if (isScala())
                                                                    {
                                                            #line 7706 "PrintCLike.cpp"
  append(L" match");
                                                            #line 4527 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(leftBrace());
                                                                  }
                                                                  int lastContentId = grammar->distinctCodeAnnotations.size() - 1;
                                                                  for (int contentId = 0; contentId <= lastContentId; ++contentId)
                                                                  {
                                                                    ProcessingInstruction *p = grammar->distinctCodeAnnotations[contentId];
                                                                    if (! isPython())
                                                                    {
                                                            #line 7718 "PrintCLike.cpp"
  append(L"\n");
  append(L"case ");
                                                            #line 4537 "PrintCLike.cpp.template"
                                                                    }
                                                                    else if (contentId == 0)
                                                                    {
                                                            #line 7725 "PrintCLike.cpp"
  append(L"\n");
  append(L"if reduce == ");
                                                            #line 4541 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 7732 "PrintCLike.cpp"
  append(L"\n");
  append(L"elif reduce == ");
                                                            #line 4545 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(format.toString<wchar_t>(contentId));
                                                                    print(caseIntroducer());
                                                                    increaseIndent();
                                                                    print(leftBrace());
                                                                    visitProcessingInstruction(p);
                                                                    print(rightBrace());
                                                                    if (! isScala() && ! isHaxe() && ! isGo() && ! isPython())
                                                                    {
                                                            #line 7745 "PrintCLike.cpp"
  append(L"\n");
  append(L"break");
                                                            #line 4555 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                                    }
                                                                    decreaseIndent();
                                                                  }
                                                                  if (isScala())
                                                                  {
                                                            #line 7755 "PrintCLike.cpp"
  append(L"\n");
  append(L"case _");
                                                            #line 4562 "PrintCLike.cpp.template"
                                                                    print(caseIntroducer());
                                                                  }
                                                                  else if (! isPython())
                                                                  {
                                                            #line 7763 "PrintCLike.cpp"
  append(L"\n");
  append(L"default");
                                                            #line 4567 "PrintCLike.cpp.template"
                                                                    print(caseIntroducer());
                                                                  }
                                                                  if (! isScala() && ! isHaxe() && ! isGo() && ! isPython())
                                                                  {
                                                            #line 7771 "PrintCLike.cpp"
  append(L"\n");
  append(L"  break");
                                                            #line 4572 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                  }
                                                                  print(rightBrace());
                                                                  decreaseIndent();
                                                                  print(rightBrace());
                                                            #line 7780 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4578 "PrintCLike.cpp.template"
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
                                                            #line 7806 "PrintCLike.cpp"
  append(L"\n");
  append(L"if ");
                                                            #line 4602 "PrintCLike.cpp.template"
                                                                print(ifLeftParen());
                                                                print(thiz());
                                                            #line 7812 "PrintCLike.cpp"
  append(L"l1 == t");
                                                            #line 4604 "PrintCLike.cpp.template"
                                                                print(ifRightParen());
                                                                print(leftBrace());
                                                                increaseIndent();
                                                                if (tree && i == 0 && ! isLrParser)
                                                                {
                                                                  if (anyWhitespace && ! isLrParser)
                                                                  {
                                                            #line 7822 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4612 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7826 "PrintCLike.cpp"
  append(L"whitespace");
                                                            #line 4613 "PrintCLike.cpp.template"
                                                                    print(isScala() ? L"" : L"()");
                                                                    print(semicolon());
                                                                  }
                                                            #line 7832 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4618 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 7836 "PrintCLike.cpp"
  append(L"eventHandler");
                                                            #line 4619 "PrintCLike.cpp.template"
                                                                  print(arrow());
                                                                  if (isGo())
                                                                  {
                                                            #line 7842 "PrintCLike.cpp"
  append(L"T");
                                                            #line 4622 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 7848 "PrintCLike.cpp"
  append(L"t");
                                                            #line 4625 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 7852 "PrintCLike.cpp"
  append(L"erminal(");
                                                            #line 4626 "PrintCLike.cpp.template"
                                                                  if (isJava() || isCSharp())
                                                                  {
                                                                    print(staticPrefix());
                                                            #line 7858 "PrintCLike.cpp"
  append(L"TOKEN[");
                                                            #line 4629 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7862 "PrintCLike.cpp"
  append(L"l1]");
                                                            #line 4630 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isTypescript())
                                                                  {
                                                                    print(staticPrefix());
                                                            #line 7869 "PrintCLike.cpp"
  append(L"TOKEN[");
                                                            #line 4634 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7873 "PrintCLike.cpp"
  append(L"l1]");
                                                            #line 4635 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isJavascript() || isHaxe())
                                                                  {
                                                                    print(staticPrefix());
                                                            #line 7880 "PrintCLike.cpp"
  append(L"TOKEN[");
                                                            #line 4639 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7884 "PrintCLike.cpp"
  append(L"l1]");
                                                            #line 4640 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isScala())
                                                                  {
                                                                    print(staticPrefix());
                                                            #line 7891 "PrintCLike.cpp"
  append(L"TOKEN(l1)");
                                                            #line 4644 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isGo())
                                                                  {
                                                            #line 7897 "PrintCLike.cpp"
  append(L"token[this.l1]");
                                                            #line 4647 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                                    print(staticPrefix());
                                                            #line 7904 "PrintCLike.cpp"
  append(L"TOKEN[");
                                                            #line 4651 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7908 "PrintCLike.cpp"
  append(L"l1]");
                                                            #line 4652 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 7912 "PrintCLike.cpp"
  append(L", ");
                                                            #line 4653 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 7916 "PrintCLike.cpp"
  append(L"b1, ");
                                                            #line 4654 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 7920 "PrintCLike.cpp"
  append(L"e1)");
                                                            #line 4655 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                            #line 7925 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4658 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 7929 "PrintCLike.cpp"
  append(L"b0 = ");
                                                            #line 4659 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 7933 "PrintCLike.cpp"
  append(L"b1; ");
                                                            #line 4660 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 7937 "PrintCLike.cpp"
  append(L"e0 = ");
                                                            #line 4661 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 7941 "PrintCLike.cpp"
  append(L"e1;");
                                                            #line 4662 "PrintCLike.cpp.template"
                                                                for (size_t k = 1; k < grammar->k; ++k)
                                                                {
                                                            #line 7946 "PrintCLike.cpp"
  append(L" ");
                                                            #line 4664 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 7950 "PrintCLike.cpp"
  append(L"l");
                                                            #line 4665 "PrintCLike.cpp.template"
                                                                  print(format.toString<wchar_t>(k));
                                                            #line 7954 "PrintCLike.cpp"
  append(L" = ");
                                                            #line 4666 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 7958 "PrintCLike.cpp"
  append(L"l");
                                                            #line 4667 "PrintCLike.cpp.template"
                                                                  print(format.toString<wchar_t>(k + 1));
                                                                  print(isPython() ? L"\n" : L"; ");
                                                            #line 7963 "PrintCLike.cpp"
  append(L"if ");
                                                            #line 4669 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                                  print(thiz());
                                                            #line 7968 "PrintCLike.cpp"
  append(L"l");
                                                            #line 4671 "PrintCLike.cpp.template"
                                                                  print(format.toString<wchar_t>(k));
                                                            #line 7972 "PrintCLike.cpp"
  append(L" != 0");
                                                            #line 4672 "PrintCLike.cpp.template"
                                                                  print(ifRightParen());
                                                                  if (isPython())
                                                                  {
                                                                    increaseIndent();
                                                                  }
                                                                  else
                                                                  {
                                                            #line 7982 "PrintCLike.cpp"
  append(L" {");
                                                            #line 4679 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 7986 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4681 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 7990 "PrintCLike.cpp"
  append(L"b");
                                                            #line 4682 "PrintCLike.cpp.template"
                                                                  print(format.toString<wchar_t>(k));
                                                            #line 7994 "PrintCLike.cpp"
  append(L" = ");
                                                            #line 4683 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 7998 "PrintCLike.cpp"
  append(L"b");
                                                            #line 4684 "PrintCLike.cpp.template"
                                                                  print(format.toString<wchar_t>(k + 1));
                                                            #line 8002 "PrintCLike.cpp"
  append(L"; ");
                                                            #line 4685 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8006 "PrintCLike.cpp"
  append(L"e");
                                                            #line 4686 "PrintCLike.cpp.template"
                                                                  print(format.toString<wchar_t>(k));
                                                            #line 8010 "PrintCLike.cpp"
  append(L" = ");
                                                            #line 4687 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8014 "PrintCLike.cpp"
  append(L"e");
                                                            #line 4688 "PrintCLike.cpp.template"
                                                                  print(format.toString<wchar_t>(k + 1));
                                                            #line 8018 "PrintCLike.cpp"
  append(L";");
                                                            #line 4689 "PrintCLike.cpp.template"
                                                                }
                                                            #line 8022 "PrintCLike.cpp"
  append(L" ");
                                                            #line 4690 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 8026 "PrintCLike.cpp"
  append(L"l");
                                                            #line 4691 "PrintCLike.cpp.template"
                                                                print(format.toString<wchar_t>(grammar->k));
                                                            #line 8030 "PrintCLike.cpp"
  append(L" = 0");
                                                            #line 4692 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                if (grammar->k > 1)
                                                                {
                                                            #line 8036 "PrintCLike.cpp"
  append(L" ");
                                                            #line 4695 "PrintCLike.cpp.template"
                                                                  for (size_t k = 1; k < grammar->k; ++k)
                                                                  {
                                                                    if (! isPython())
                                                                    {
                                                            #line 8043 "PrintCLike.cpp"
  append(L"}");
                                                            #line 4699 "PrintCLike.cpp.template"
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
                                                            #line 8058 "PrintCLike.cpp"
  append(L"\n");
  append(L"  fprintf(stderr, \"  <parse terminal=\\\"%s\\\"%s%s%s/>\\n\", ");
                                                            #line 4712 "PrintCLike.cpp.template"
                                                                    if (stringIntroducer()[0])
                                                                    {
                                                            #line 8064 "PrintCLike.cpp"
  append(L"Utf8Encoder::encode(");
                                                            #line 4715 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 8068 "PrintCLike.cpp"
  append(L"xmlEscape(TOKEN[t], 0).c_str()");
                                                            #line 4717 "PrintCLike.cpp.template"
                                                                    if (stringIntroducer()[0])
                                                                    {
                                                            #line 8073 "PrintCLike.cpp"
  append(L").c_str()");
                                                            #line 4719 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 8077 "PrintCLike.cpp"
  append(L", (l1 == 0 ? \"\" : \" input=\\\"\"),  (l1 == 0 ? \"\" : ");
                                                            #line 4721 "PrintCLike.cpp.template"
                                                                    if (stringIntroducer()[0])
                                                                    {
                                                            #line 8082 "PrintCLike.cpp"
  append(L"Utf8Encoder::encode(");
                                                            #line 4724 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 8086 "PrintCLike.cpp"
  append(L"xmlEscape(lookaheadString().c_str(), 0).c_str()");
                                                            #line 4726 "PrintCLike.cpp.template"
                                                                    if (stringIntroducer()[0])
                                                                    {
                                                            #line 8091 "PrintCLike.cpp"
  append(L").c_str()");
                                                            #line 4728 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 8095 "PrintCLike.cpp"
  append(L"), (l1 == 0 ? \"\" : \"\\\"\"));");
                                                            #line 4730 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                                    if (isGo())
                                                                    {
                                                            #line 8103 "PrintCLike.cpp"
  append(L"\n");
  append(L"  var inputAttr string\n");
  append(L"  if (this.l1 == 0) {\n");
  append(L"    inputAttr = \"\"\n");
  append(L"  } else {\n");
  append(L"    inputAttr = \" input=\\\"\" + xmlEscape(this.lookaheadString()) + \"\\\"\"\n");
  append(L"  }");
                                                            #line 4741 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 8113 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4743 "PrintCLike.cpp.template"
                                                                    if (isHaxe())
                                                                    {
                                                            #line 8119 "PrintCLike.cpp"
  append(L"trace(");
                                                            #line 4746 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                                      print(writeTrace());
                                                                    }
                                                            #line 8127 "PrintCLike.cpp"
  append(L"\"  <parse terminal=\\\"\" + ");
                                                            #line 4751 "PrintCLike.cpp.template"
                                                                    print(staticPrefix());
                                                            #line 8131 "PrintCLike.cpp"
  append(L"xmlEscape(");
                                                            #line 4752 "PrintCLike.cpp.template"
                                                                    print(staticPrefix());
                                                                    print(isGo() ? L"token" : L"TOKEN");
                                                                    print(leftbracket());
                                                            #line 8137 "PrintCLike.cpp"
  append(L"t");
                                                            #line 4755 "PrintCLike.cpp.template"
                                                                    print(rightbracket());
                                                            #line 8141 "PrintCLike.cpp"
  append(L") + \"\\\"\" + ");
                                                            #line 4756 "PrintCLike.cpp.template"
                                                                    if (isGo())
                                                                    {
                                                            #line 8146 "PrintCLike.cpp"
  append(L"inputAttr");
                                                            #line 4758 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 8152 "PrintCLike.cpp"
  append(L"(");
                                                            #line 4761 "PrintCLike.cpp.template"
                                                                      if (isScala())
                                                                      {
                                                            #line 8157 "PrintCLike.cpp"
  append(L"if (l1 == 0) \"\" else");
                                                            #line 4763 "PrintCLike.cpp.template"
                                                                      }
                                                                      else if (isPython())
                                                                      {
                                                            #line 8163 "PrintCLike.cpp"
  append(L"\"\" if self.l1 == 0 else");
                                                            #line 4766 "PrintCLike.cpp.template"
                                                                      }
                                                                      else
                                                                      {
                                                                        print(thiz());
                                                            #line 8170 "PrintCLike.cpp"
  append(L"l1 == 0 ? \"\" :");
                                                            #line 4770 "PrintCLike.cpp.template"
                                                                      }
                                                            #line 8174 "PrintCLike.cpp"
  append(L" \" input=\\\"\" + ");
                                                            #line 4771 "PrintCLike.cpp.template"
                                                                      print(staticPrefix());
                                                            #line 8178 "PrintCLike.cpp"
  append(L"xmlEscape(");
                                                            #line 4772 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 8182 "PrintCLike.cpp"
  append(L"lookaheadString");
                                                            #line 4773 "PrintCLike.cpp.template"
                                                                      if (! isScala()) print(L"()");
                                                            #line 8186 "PrintCLike.cpp"
  append(L") + \"\\\"\")");
                                                            #line 4774 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 8190 "PrintCLike.cpp"
  append(L" + \"/>");
                                                            #line 4775 "PrintCLike.cpp.template"
                                                                    if (isHaxe())
                                                                    {
                                                            #line 8195 "PrintCLike.cpp"
  append(L"\")");
                                                            #line 4777 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 8201 "PrintCLike.cpp"
  append(L"\\n\"");
                                                            #line 4780 "PrintCLike.cpp.template"
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
                                                            #line 8215 "PrintCLike.cpp"
  append(L"el");
                                                            #line 4791 "PrintCLike.cpp.template"
                                                                    if (! isPython())
                                                                    {
                                                            #line 8220 "PrintCLike.cpp"
  append(L"se ");
                                                            #line 4793 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 8224 "PrintCLike.cpp"
  append(L"if ");
                                                            #line 4794 "PrintCLike.cpp.template"
                                                                    print(ifLeftParen());
                                                                    print(thiz());
                                                                    print(token());
                                                            #line 8230 "PrintCLike.cpp"
  append(L" < 0");
                                                            #line 4797 "PrintCLike.cpp.template"
                                                                    print(ifRightParen());
                                                                    print(leftBrace());
                                                            #line 8235 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4800 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8240 "PrintCLike.cpp"
  append(L"error(");
                                                            #line 4801 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8244 "PrintCLike.cpp"
  append(L"b1, ");
                                                            #line 4802 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8248 "PrintCLike.cpp"
  append(L"e1, -");
                                                            #line 4803 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8252 "PrintCLike.cpp"
  append(L"l1, 0, 0)");
                                                            #line 4804 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                    if (i == 0)
                                                                    {
                                                            #line 8258 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4808 "PrintCLike.cpp.template"
                                                                      print(beginThrowStmt());
                                                                      print(thiz());
                                                            #line 8264 "PrintCLike.cpp"
  append(L"bx, ");
                                                            #line 4810 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 8268 "PrintCLike.cpp"
  append(L"ex, ");
                                                            #line 4811 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 8272 "PrintCLike.cpp"
  append(L"sx, ");
                                                            #line 4812 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 8276 "PrintCLike.cpp"
  append(L"lx, ");
                                                            #line 4813 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 8280 "PrintCLike.cpp"
  append(L"tx");
                                                            #line 4814 "PrintCLike.cpp.template"
                                                                      print(endThrowStmt());
                                                                      print(semicolon());
                                                                    }
                                                                    print(rightBrace());
                                                                  }
                                                                  print(isGo() ? L" " : L"\n");
                                                            #line 8289 "PrintCLike.cpp"
  append(L"else");
                                                            #line 4820 "PrintCLike.cpp.template"
                                                                  if (isPython()) print(L":");
                                                                  print(leftBrace());
                                                            #line 8294 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4823 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8299 "PrintCLike.cpp"
  append(L"error(");
                                                            #line 4824 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8303 "PrintCLike.cpp"
  append(L"b1, ");
                                                            #line 4825 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8307 "PrintCLike.cpp"
  append(L"e1, 0, ");
                                                            #line 4826 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8311 "PrintCLike.cpp"
  append(L"l1, t)");
                                                            #line 4827 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                  if (i == 0 && grammar->noThrow)
                                                                  {
                                                            #line 8317 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4831 "PrintCLike.cpp.template"
                                                                    print(beginThrowStmt());
                                                                    print(thiz());
                                                            #line 8323 "PrintCLike.cpp"
  append(L"bx, ");
                                                            #line 4833 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8327 "PrintCLike.cpp"
  append(L"ex, ");
                                                            #line 4834 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8331 "PrintCLike.cpp"
  append(L"sx, ");
                                                            #line 4835 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8335 "PrintCLike.cpp"
  append(L"lx, ");
                                                            #line 4836 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8339 "PrintCLike.cpp"
  append(L"tx");
                                                            #line 4837 "PrintCLike.cpp.template"
                                                                    print(endThrowStmt());
                                                                    print(semicolon());
                                                                  }
                                                                  print(rightBrace());
                                                                }
                                                                else
                                                                {
                                                                  print(isGo() ? L" " : L"\n");
                                                            #line 8350 "PrintCLike.cpp"
  append(L"else");
                                                            #line 4845 "PrintCLike.cpp.template"
                                                                  if (isPython()) print(L":");
                                                                  print(leftBrace());
                                                            #line 8355 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4848 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8360 "PrintCLike.cpp"
  append(L"error(");
                                                            #line 4849 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8364 "PrintCLike.cpp"
  append(L"b1, ");
                                                            #line 4850 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8368 "PrintCLike.cpp"
  append(L"e1, 0, ");
                                                            #line 4851 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8372 "PrintCLike.cpp"
  append(L"l1, t)");
                                                            #line 4852 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                  print(rightBrace());
                                                                }
                                                                decreaseIndent();
                                                                print(rightBrace());
                                                            #line 8380 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4858 "PrintCLike.cpp.template"
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
                                                            #line 8399 "PrintCLike.cpp"
  append(L"\n");
  append(L"  var thread = new ParsingThread().copy(thisThread, 0);\n");
  append(L"  thread.setL1(code);\n");
  append(L"  thread.setB1(begin);\n");
  append(L"  thread.setE1(end);");
                                                            #line 4878 "PrintCLike.cpp.template"
                                                                    }
                                                                    else if (isGo())
                                                                    {
                                                            #line 8409 "PrintCLike.cpp"
  append(L"\n");
  append(L"  thread := new(ParsingThread).copy(this, 0)\n");
  append(L"  thread.l1 = code\n");
  append(L"  thread.b1 = this.begin\n");
  append(L"  thread.e1 = this.end");
                                                            #line 4885 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 8419 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4889 "PrintCLike.cpp.template"
                                                                      if (isHaxe() || isScala() || isTypescript())
                                                                      {
                                                            #line 8425 "PrintCLike.cpp"
  append(L"var ");
                                                            #line 4891 "PrintCLike.cpp.template"
                                                                      }
                                                                      else if (! isPython())
                                                                      {
                                                            #line 8431 "PrintCLike.cpp"
  append(L"ParsingThread ");
                                                            #line 4894 "PrintCLike.cpp.template"
                                                                      }
                                                                      if (isCpp()) print(L"*");
                                                            #line 8436 "PrintCLike.cpp"
  append(L"thread = ");
                                                            #line 4896 "PrintCLike.cpp.template"
                                                                      if (isCpp()) print(L"(");
                                                                      if (! isPython())
                                                                      {
                                                            #line 8442 "PrintCLike.cpp"
  append(L"new ");
                                                            #line 4899 "PrintCLike.cpp.template"
                                                                      }
                                                                      if (isScala() || isPython())
                                                                      {
                                                                        print(className.c_str());
                                                            #line 8449 "PrintCLike.cpp"
  append(L".");
                                                            #line 4903 "PrintCLike.cpp.template"
                                                                      }
                                                            #line 8453 "PrintCLike.cpp"
  append(L"ParsingThread()");
                                                            #line 4904 "PrintCLike.cpp.template"
                                                                      if (isCpp()) print(L")");
                                                                      print(arrow());
                                                            #line 8458 "PrintCLike.cpp"
  append(L"copy(");
                                                            #line 4906 "PrintCLike.cpp.template"
                                                                      if (isPython())
                                                                      {
                                                            #line 8463 "PrintCLike.cpp"
  append(L"self");
                                                            #line 4908 "PrintCLike.cpp.template"
                                                                      }
                                                                      else
                                                                      {
                                                            #line 8469 "PrintCLike.cpp"
  append(L"this");
                                                            #line 4911 "PrintCLike.cpp.template"
                                                                      }
                                                            #line 8473 "PrintCLike.cpp"
  append(L", 0)");
                                                            #line 4912 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                                      if (isCpp())
                                                                      {
                                                            #line 8479 "PrintCLike.cpp"
  append(L"\n");
  append(L"  thread->stack->unshare();\n");
  append(L"  thread->stack = 0;");
                                                            #line 4917 "PrintCLike.cpp.template"
                                                                      }
                                                            #line 8485 "PrintCLike.cpp"
  append(L"\n");
  append(L"  thread");
                                                            #line 4919 "PrintCLike.cpp.template"
                                                                      print(arrow());
                                                            #line 8490 "PrintCLike.cpp"
  append(L"l1 = code");
                                                            #line 4920 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                            #line 8494 "PrintCLike.cpp"
  append(L"\n");
  append(L"  thread");
                                                            #line 4922 "PrintCLike.cpp.template"
                                                                      print(arrow());
                                                            #line 8499 "PrintCLike.cpp"
  append(L"b1 = ");
                                                            #line 4923 "PrintCLike.cpp.template"
                                                                      if (useGlr) print(thiz());
                                                            #line 8503 "PrintCLike.cpp"
  append(L"begin");
                                                            #line 4924 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                            #line 8507 "PrintCLike.cpp"
  append(L"\n");
  append(L"  thread");
                                                            #line 4926 "PrintCLike.cpp.template"
                                                                      print(arrow());
                                                            #line 8512 "PrintCLike.cpp"
  append(L"e1 = ");
                                                            #line 4927 "PrintCLike.cpp.template"
                                                                      if (useGlr) print(thiz());
                                                            #line 8516 "PrintCLike.cpp"
  append(L"end");
                                                            #line 4928 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                                    }
                                                                  }
                                                                  else
                                                                  {
                                                            #line 8524 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4934 "PrintCLike.cpp.template"
                                                                    print(intVal());
                                                            #line 8529 "PrintCLike.cpp"
  append(L"b0W");
                                                            #line 4935 "PrintCLike.cpp.template"
                                                                    print(assign());
                                                                    print(thiz());
                                                            #line 8534 "PrintCLike.cpp"
  append(L"b0; ");
                                                            #line 4937 "PrintCLike.cpp.template"
                                                                    print(intVal());
                                                            #line 8538 "PrintCLike.cpp"
  append(L"e0W");
                                                            #line 4938 "PrintCLike.cpp.template"
                                                                    print(assign());
                                                                    print(thiz());
                                                            #line 8543 "PrintCLike.cpp"
  append(L"e0");
                                                            #line 4941 "PrintCLike.cpp.template"
                                                                    for (size_t k = 1; k < grammar->k; ++k)
                                                                    {
                                                            #line 8548 "PrintCLike.cpp"
  append(L"; ");
                                                            #line 4943 "PrintCLike.cpp.template"
                                                                      print(intVal());
                                                            #line 8552 "PrintCLike.cpp"
  append(L"l");
                                                            #line 4944 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(k));
                                                            #line 8556 "PrintCLike.cpp"
  append(L"W");
                                                            #line 4945 "PrintCLike.cpp.template"
                                                                      print(assign());
                                                                      print(thiz());
                                                            #line 8561 "PrintCLike.cpp"
  append(L"l");
                                                            #line 4947 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(k));
                                                                      print(semicolon());
                                                            #line 8566 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4950 "PrintCLike.cpp.template"
                                                                      print(intVal());
                                                            #line 8571 "PrintCLike.cpp"
  append(L"b");
                                                            #line 4951 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(k));
                                                            #line 8575 "PrintCLike.cpp"
  append(L"W");
                                                            #line 4952 "PrintCLike.cpp.template"
                                                                      print(assign());
                                                                      print(thiz());
                                                            #line 8580 "PrintCLike.cpp"
  append(L"b");
                                                            #line 4954 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(k));
                                                            #line 8584 "PrintCLike.cpp"
  append(L"; ");
                                                            #line 4955 "PrintCLike.cpp.template"
                                                                      print(intVal());
                                                            #line 8588 "PrintCLike.cpp"
  append(L"e");
                                                            #line 4956 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(k));
                                                            #line 8592 "PrintCLike.cpp"
  append(L"W");
                                                            #line 4957 "PrintCLike.cpp.template"
                                                                      print(assign());
                                                                      print(thiz());
                                                            #line 8597 "PrintCLike.cpp"
  append(L"e");
                                                            #line 4959 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(k));
                                                                    }
                                                                    print(semicolon());
                                                            #line 8603 "PrintCLike.cpp"
  append(L"\n");
  append(L"\n");
  append(L"  ");
                                                            #line 4964 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8609 "PrintCLike.cpp"
  append(L"l1 = code; ");
                                                            #line 4965 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8613 "PrintCLike.cpp"
  append(L"b1 = ");
                                                            #line 4966 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8617 "PrintCLike.cpp"
  append(L"begin; ");
                                                            #line 4967 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8621 "PrintCLike.cpp"
  append(L"e1 = ");
                                                            #line 4968 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8625 "PrintCLike.cpp"
  append(L"end");
                                                            #line 4969 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                    for (size_t k = 2; k <= grammar->k; ++k)
                                                                    {
                                                            #line 8631 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4973 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 8636 "PrintCLike.cpp"
  append(L"l");
                                                            #line 4974 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(k));
                                                            #line 8640 "PrintCLike.cpp"
  append(L" = 0");
                                                            #line 4975 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                                    }
                                                                  }
                                                                  if (isLrParser)
                                                                  {
                                                            #line 8648 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4981 "PrintCLike.cpp.template"
                                                                    if (useGlr)
                                                                    {
                                                                      if (! isCpp())
                                                                      {
                                                            #line 8656 "PrintCLike.cpp"
  append(L"thread = ");
                                                            #line 4985 "PrintCLike.cpp.template"
                                                                      }
                                                                      if (isJava())
                                                                      {
                                                                        print(className.c_str());
                                                            #line 8663 "PrintCLike.cpp"
  append(L".this.");
                                                            #line 4989 "PrintCLike.cpp.template"
                                                                      }
                                                                      else if (isCSharp() || isCpp() || isHaxe() || isScala() || isTypescript() || isGo() || isPython())
                                                                      {
                                                                        print(thiz());
                                                            #line 8670 "PrintCLike.cpp"
  append(L"parser");
                                                            #line 4993 "PrintCLike.cpp.template"
                                                                        print(arrow());
                                                                      }
                                                                    }
                                                                    else
                                                                    {
                                                                      print(thiz());
                                                                    }
                                                            #line 8680 "PrintCLike.cpp"
  append(L"parse(-1, ");
                                                            #line 5000 "PrintCLike.cpp.template"
                                                                    print(format.toString<wchar_t>(grammar->whitespace->getStateId()));
                                                                    if (tree)
                                                                    {
                                                            #line 8686 "PrintCLike.cpp"
  append(L", ");
                                                            #line 5003 "PrintCLike.cpp.template"
                                                                      print(nullPtr());
                                                                    }
                                                                    if (useGlr)
                                                                    {
                                                            #line 8693 "PrintCLike.cpp"
  append(L", thread");
                                                            #line 5007 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 8697 "PrintCLike.cpp"
  append(L")");
                                                            #line 5008 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                  }
                                                                  else
                                                                  {
                                                            #line 8704 "PrintCLike.cpp"
  append(L"\n");
  append(L"\n");
  append(L"  ");
                                                            #line 5014 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8710 "PrintCLike.cpp"
  append(L"try_");
                                                            #line 5015 "PrintCLike.cpp.template"
                                                                    print(Format::acceptableName<WString>(grammar->whitespace->name).c_str());
                                                                    if (! isScala()) print(L"()");
                                                                    print(semicolon());
                                                                  }
                                                                  if (useGlr)
                                                                  {
                                                                    if (isJavascript())
                                                                    {
                                                            #line 8721 "PrintCLike.cpp"
  append(L"\n");
  append(L"  end = thread.getEnd();");
                                                            #line 5024 "PrintCLike.cpp.template"
                                                                    }
                                                                    else if (isCpp())
                                                                    {
                                                            #line 8728 "PrintCLike.cpp"
  append(L"\n");
  append(L"  end = thread->end;\n");
  append(L"  delete thread;");
                                                            #line 5029 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 8736 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5033 "PrintCLike.cpp.template"
                                                                      if (useGlr) print(thiz());
                                                            #line 8741 "PrintCLike.cpp"
  append(L"end = thread");
                                                            #line 5034 "PrintCLike.cpp.template"
                                                                      print(arrow());
                                                            #line 8745 "PrintCLike.cpp"
  append(L"end");
                                                            #line 5035 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                                    }
                                                                  }
                                                                  else
                                                                  {
                                                            #line 8753 "PrintCLike.cpp"
  append(L"\n");
  append(L"\n");
  append(L"  ");
                                                            #line 5042 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8759 "PrintCLike.cpp"
  append(L"b0 = b0W; ");
                                                            #line 5043 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8763 "PrintCLike.cpp"
  append(L"e0 = e0W");
                                                            #line 5044 "PrintCLike.cpp.template"
                                                                    for (size_t k = 1; k < grammar->k; ++k)
                                                                    {
                                                            #line 8768 "PrintCLike.cpp"
  append(L"; ");
                                                            #line 5046 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 8772 "PrintCLike.cpp"
  append(L"l");
                                                            #line 5047 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(k));
                                                            #line 8776 "PrintCLike.cpp"
  append(L" = l");
                                                            #line 5048 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(k));
                                                            #line 8780 "PrintCLike.cpp"
  append(L"W");
                                                            #line 5049 "PrintCLike.cpp.template"
                                                                      if (isPython())
                                                                      {
                                                            #line 8785 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5052 "PrintCLike.cpp.template"
                                                                      }
                                                                      else
                                                                      {
                                                            #line 8792 "PrintCLike.cpp"
  append(L"; ");
                                                            #line 5055 "PrintCLike.cpp.template"
                                                                      }
                                                            #line 8796 "PrintCLike.cpp"
  append(L"if ");
                                                            #line 5056 "PrintCLike.cpp.template"
                                                                      print(ifLeftParen());
                                                                      print(thiz());
                                                            #line 8801 "PrintCLike.cpp"
  append(L"l");
                                                            #line 5058 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(k));
                                                            #line 8805 "PrintCLike.cpp"
  append(L" != 0");
                                                            #line 5059 "PrintCLike.cpp.template"
                                                                      print(ifRightParen());
                                                                      if (isPython())
                                                                      {
                                                                        increaseIndent();
                                                                      }
                                                                      else
                                                                      {
                                                            #line 8815 "PrintCLike.cpp"
  append(L" {");
                                                            #line 5066 "PrintCLike.cpp.template"
                                                                      }
                                                            #line 8819 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5068 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 8824 "PrintCLike.cpp"
  append(L"b");
                                                            #line 5069 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(k));
                                                            #line 8828 "PrintCLike.cpp"
  append(L" = b");
                                                            #line 5070 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(k));
                                                            #line 8832 "PrintCLike.cpp"
  append(L"W; ");
                                                            #line 5071 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 8836 "PrintCLike.cpp"
  append(L"e");
                                                            #line 5072 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(k));
                                                            #line 8840 "PrintCLike.cpp"
  append(L" = e");
                                                            #line 5073 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(k));
                                                            #line 8844 "PrintCLike.cpp"
  append(L"W");
                                                            #line 5074 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(semicolon());
                                                                    if (isPython())
                                                                    {
                                                                      decreaseIndent(grammar->k - 1);
                                                                    }
                                                                    else
                                                                    {
                                                            #line 8855 "PrintCLike.cpp"
  append(L" ");
                                                            #line 5082 "PrintCLike.cpp.template"
                                                                      for (size_t k = 1; k < grammar->k; ++k)
                                                                      {
                                                            #line 8860 "PrintCLike.cpp"
  append(L"}");
                                                            #line 5084 "PrintCLike.cpp.template"
                                                                      }
                                                                    }
                                                                  }
                                                                  print(rightBrace());
                                                            #line 8867 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5089 "PrintCLike.cpp.template"
                                                                  if (! isGo())
                                                                    decreaseIndent();
                                                                }
                                                                if (tree && ! isLrParser)
                                                                {
                                                                  if (! isGo())
                                                                    increaseIndent();
                                                                  openMethod (voidType(), L"", L"whitespace", L"");
                                                                  print(leftBrace());
                                                            #line 8879 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if ");
                                                            #line 5099 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                                  print(thiz());
                                                            #line 8885 "PrintCLike.cpp"
  append(L"e0 != ");
                                                            #line 5101 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8889 "PrintCLike.cpp"
  append(L"b1");
                                                            #line 5102 "PrintCLike.cpp.template"
                                                                  print(ifRightParen());
                                                                  increaseIndent();
                                                                  print(leftBrace());
                                                                  decreaseIndent();
                                                            #line 8896 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 5107 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8901 "PrintCLike.cpp"
  append(L"eventHandler");
                                                            #line 5108 "PrintCLike.cpp.template"
                                                                  print(arrow());
                                                                  if (isGo())
                                                                  {
                                                            #line 8907 "PrintCLike.cpp"
  append(L"W");
                                                            #line 5111 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 8913 "PrintCLike.cpp"
  append(L"w");
                                                            #line 5114 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 8917 "PrintCLike.cpp"
  append(L"hitespace(");
                                                            #line 5115 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8921 "PrintCLike.cpp"
  append(L"e0, ");
                                                            #line 5116 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8925 "PrintCLike.cpp"
  append(L"b1)");
                                                            #line 5117 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                            #line 8929 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 5119 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8934 "PrintCLike.cpp"
  append(L"e0 = ");
                                                            #line 5120 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8938 "PrintCLike.cpp"
  append(L"b1");
                                                            #line 5121 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                  increaseIndent();
                                                                  print(rightBrace());
                                                                  decreaseIndent();
                                                                  print(rightBrace());
                                                                  if (! isGo())
                                                                    decreaseIndent();
                                                            #line 8948 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5129 "PrintCLike.cpp.template"
                                                                }
                                                                if (! isGo())
                                                                  increaseIndent();
                                                                openMethod(intType(), L"", L"matchW", L"int tokenSetId", false, useGlr ? L"ParsingThread" : className.c_str());
                                                                print(leftBrace());
                                                                if (isScala())
                                                                {
                                                            #line 8958 "PrintCLike.cpp"
  append(L"\n");
  append(L"  var continue = true\n");
  append(L"  var code = 0\n");
  append(L"  while (continue) {\n");
  append(L"    code = matcher(tokenSetId)");
                                                            #line 5140 "PrintCLike.cpp.template"
                                                                  increaseIndent(2);
                                                                }
                                                                else
                                                                {
                                                                  if (! isPython())
                                                                  {
                                                            #line 8971 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5147 "PrintCLike.cpp.template"
                                                                    print((isJavascript() || isTypescript() || isHaxe() || isGo()) ? L"var" : L"int");
                                                            #line 8976 "PrintCLike.cpp"
  append(L" code");
                                                            #line 5148 "PrintCLike.cpp.template"
                                                                    if (isTypescript())
                                                                    {
                                                            #line 8981 "PrintCLike.cpp"
  append(L": number");
                                                            #line 5150 "PrintCLike.cpp.template"
                                                                    }
                                                                    else if (isGo())
                                                                    {
                                                            #line 8987 "PrintCLike.cpp"
  append(L" int");
                                                            #line 5153 "PrintCLike.cpp.template"
                                                                    }
                                                                    if (isHaxe())
                                                                    {
                                                            #line 8993 "PrintCLike.cpp"
  append(L" = 0");
                                                            #line 5156 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(semicolon());
                                                                  }
                                                                  if (isHaxe() || isPython())
                                                                  {
                                                            #line 9001 "PrintCLike.cpp"
  append(L"\n");
  append(L"  while ");
                                                            #line 5162 "PrintCLike.cpp.template"
                                                                    print(ifLeftParen());
                                                                    print(isPython() ? L"T" : L"t");
                                                            #line 9007 "PrintCLike.cpp"
  append(L"rue");
                                                            #line 5164 "PrintCLike.cpp.template"
                                                                    print(ifRightParen());
                                                                  }
                                                                  else
                                                                  {
                                                            #line 9014 "PrintCLike.cpp"
  append(L"\n");
  append(L"  for");
                                                            #line 5169 "PrintCLike.cpp.template"
                                                                    if (! isGo())
                                                                    {
                                                            #line 9020 "PrintCLike.cpp"
  append(L" (;;)");
                                                            #line 5171 "PrintCLike.cpp.template"
                                                                    }
                                                                  }
                                                                  increaseIndent();
                                                                  print(leftBrace());
                                                                  increaseIndent();
                                                            #line 9028 "PrintCLike.cpp"
  append(L"\n");
  append(L"code = ");
                                                            #line 5177 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 9033 "PrintCLike.cpp"
  append(L"match(tokenSetId)");
                                                            #line 5178 "PrintCLike.cpp.template"
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
                                                            #line 9062 "PrintCLike.cpp"
  append(L"\n");
  append(L"  continue = false\n");
  append(L"}\n");
  append(L"else {\n");
  append(L"  ");
                                                            #line 5208 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 9070 "PrintCLike.cpp"
  append(L"skip(code)\n");
  append(L"}");
                                                            #line 5210 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 9077 "PrintCLike.cpp"
  append(L"\n");
  append(L"  break");
                                                            #line 5214 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                    print(rightBrace());
                                                            #line 9083 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5217 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 9087 "PrintCLike.cpp"
  append(L"skip(code);");
                                                            #line 5218 "PrintCLike.cpp.template"
                                                                  }
                                                                }
                                                                else if (isScala())
                                                                {
                                                            #line 9094 "PrintCLike.cpp"
  append(L"\n");
  append(L"continue = false");
                                                            #line 5223 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 9101 "PrintCLike.cpp"
  append(L"\n");
  append(L"break");
                                                            #line 5227 "PrintCLike.cpp.template"
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
                                                            #line 9115 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5238 "PrintCLike.cpp.template"
                                                                if (! isScala())
                                                                {
                                                            #line 9121 "PrintCLike.cpp"
  append(L"return ");
                                                            #line 5240 "PrintCLike.cpp.template"
                                                                }
                                                            #line 9125 "PrintCLike.cpp"
  append(L"code");
                                                            #line 5241 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                print(rightBrace());
                                                            #line 9130 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5244 "PrintCLike.cpp.template"
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
                                                            #line 9146 "PrintCLike.cpp"
  append(L"\n");
  append(L"def parse(): Unit = {\n");
  append(L"  parse_");
                                                            #line 5259 "PrintCLike.cpp.template"
                                                                  print(Format::acceptableName<WString>(grammar->startSymbol()->name).c_str());
                                                            #line 9152 "PrintCLike.cpp"
  append(L"()\n");
  append(L"}\n");
                                                            #line 5262 "PrintCLike.cpp.template"
                                                                }
                                                                if (memoization)
                                                                {
                                                                  int bits = Math::bits(grammar->conflictCount);
                                                            #line 9160 "PrintCLike.cpp"
  append(L"\n");
  append(L"private def memoize(i: Int, e: Int, v: Int): Unit = {\n");
  append(L"  memo.put((e << ");
                                                            #line 5268 "PrintCLike.cpp.template"
                                                                  print(format.toString<wchar_t>(bits));
                                                            #line 9166 "PrintCLike.cpp"
  append(L") + i, v)\n");
  append(L"}\n");
  append(L"\n");
  append(L"private def memoized(i: Int, e: Int) = {\n");
  append(L"  memo.getOrElse((e << ");
                                                            #line 5273 "PrintCLike.cpp.template"
                                                                  print(format.toString<wchar_t>(bits));
                                                            #line 9174 "PrintCLike.cpp"
  append(L") + i, 0)\n");
  append(L"}\n");
                                                            #line 5276 "PrintCLike.cpp.template"
                                                                }
                                                            #line 9179 "PrintCLike.cpp"
  append(L"\n");
  append(L"def error(b: Int, e: Int, s: Int, l: Int, t: Int): Int = {");
                                                            #line 5278 "PrintCLike.cpp.template"
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
                                                            #line 9193 "PrintCLike.cpp"
  append(L"\n");
  append(L"if ");
                                                            #line 5289 "PrintCLike.cpp.template"
                                                                print(ifLeftParen());
                                                                if (grammar->noThrow)
                                                                {
                                                                  print(thiz());
                                                            #line 9201 "PrintCLike.cpp"
  append(L"viable ");
                                                            #line 5293 "PrintCLike.cpp.template"
                                                                  if (isPython())
                                                                  {
                                                            #line 9206 "PrintCLike.cpp"
  append(L"and");
                                                            #line 5295 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 9212 "PrintCLike.cpp"
  append(L"&&");
                                                            #line 5298 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 9216 "PrintCLike.cpp"
  append(L" ");
                                                            #line 5299 "PrintCLike.cpp.template"
                                                                }
                                                            #line 9220 "PrintCLike.cpp"
  append(L"e >= ");
                                                            #line 5300 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 9224 "PrintCLike.cpp"
  append(L"ex");
                                                            #line 5301 "PrintCLike.cpp.template"
                                                                print(ifRightParen());
                                                                print(leftBrace());
                                                            #line 9229 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5304 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 9234 "PrintCLike.cpp"
  append(L"bx = b");
                                                            #line 5305 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 9238 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5307 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 9243 "PrintCLike.cpp"
  append(L"ex = e");
                                                            #line 5308 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 9247 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5310 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 9252 "PrintCLike.cpp"
  append(L"sx = s");
                                                            #line 5311 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 9256 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5313 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 9261 "PrintCLike.cpp"
  append(L"lx = l");
                                                            #line 5314 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 9265 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5316 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 9270 "PrintCLike.cpp"
  append(L"tx = t");
                                                            #line 5317 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                print(rightBrace());
                                                                decreaseIndent();
                                                                if (grammar->noThrow)
                                                                {
                                                            #line 9278 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5323 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 9283 "PrintCLike.cpp"
  append(L"viable = ");
                                                            #line 5324 "PrintCLike.cpp.template"
                                                                  if (isPython())
                                                                  {
                                                            #line 9288 "PrintCLike.cpp"
  append(L"F");
                                                            #line 5326 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 9294 "PrintCLike.cpp"
  append(L"f");
                                                            #line 5329 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 9298 "PrintCLike.cpp"
  append(L"alse");
                                                            #line 5330 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                            #line 9302 "PrintCLike.cpp"
  append(L"\n");
  append(L"  return -s");
                                                            #line 5332 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                                else
                                                                {
                                                                  printFlush(1, true);
                                                            #line 9311 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5338 "PrintCLike.cpp.template"
                                                                  print(beginThrowStmt());
                                                                  print(thiz());
                                                            #line 9317 "PrintCLike.cpp"
  append(L"bx, ");
                                                            #line 5340 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 9321 "PrintCLike.cpp"
  append(L"ex, ");
                                                            #line 5341 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 9325 "PrintCLike.cpp"
  append(L"sx, ");
                                                            #line 5342 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 9329 "PrintCLike.cpp"
  append(L"lx, ");
                                                            #line 5343 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 9333 "PrintCLike.cpp"
  append(L"tx");
                                                            #line 5344 "PrintCLike.cpp.template"
                                                                  print(endThrowStmt());
                                                                  print(semicolon());
                                                                }
                                                              }
                                                              else
                                                              {
                                                                printFlush(1, true);
                                                            #line 9343 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5352 "PrintCLike.cpp.template"
                                                                if (isGo())
                                                                {
                                                            #line 9349 "PrintCLike.cpp"
  append(L"panic(&ParseError{b, e, s, l, t");
                                                            #line 5354 "PrintCLike.cpp.template"
                                                                  if (useGlr)
                                                                  {
                                                            #line 9354 "PrintCLike.cpp"
  append(L", false");
                                                            #line 5356 "PrintCLike.cpp.template"
                                                                    if (tree)
                                                                    {
                                                            #line 9359 "PrintCLike.cpp"
  append(L", nil");
                                                            #line 5358 "PrintCLike.cpp.template"
                                                                    }
                                                                  }
                                                            #line 9364 "PrintCLike.cpp"
  append(L"})");
                                                            #line 5360 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                                  print(beginThrowStmt());
                                                            #line 9371 "PrintCLike.cpp"
  append(L"b, e, s, l, t");
                                                            #line 5364 "PrintCLike.cpp.template"
                                                                  print(endThrowStmt());
                                                                  print(semicolon());
                                                                }
                                                              }
                                                              print(rightBrace());
                                                            #line 9379 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5370 "PrintCLike.cpp.template"
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
                                                                openMethod(intType(), L"", L"lookback", L"int x, int y", false, clazz);
                                                                const wchar_t *lookback = isGo() ? L"lookback" : L"LOOKBACK";
                                                                print(leftBrace());
                                                                increaseIndent();
                                                                if (isGo())
                                                                {
                                                            #line 9404 "PrintCLike.cpp"
  append(L"\n");
  append(L"i := lookback[y]\n");
  append(L"l := lookback[i]\n");
  append(L"for l > x {");
                                                            #line 5395 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 9413 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5399 "PrintCLike.cpp.template"
                                                                  print(intVar());
                                                            #line 9417 "PrintCLike.cpp"
  append(L"i");
                                                            #line 5400 "PrintCLike.cpp.template"
                                                                  print(assign());
                                                                  print(staticPrefix());
                                                                  print(lookback);
                                                                  print(leftbracket());
                                                            #line 9424 "PrintCLike.cpp"
  append(L"y");
                                                            #line 5404 "PrintCLike.cpp.template"
                                                                  print(rightbracket());
                                                                  print(semicolon());
                                                            #line 9429 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5407 "PrintCLike.cpp.template"
                                                                  print(intVar());
                                                            #line 9433 "PrintCLike.cpp"
  append(L"l");
                                                            #line 5408 "PrintCLike.cpp.template"
                                                                  print(assign());
                                                                  print(staticPrefix());
                                                                  print(lookback);
                                                                  print(leftbracket());
                                                            #line 9440 "PrintCLike.cpp"
  append(L"i");
                                                            #line 5412 "PrintCLike.cpp.template"
                                                                  print(rightbracket());
                                                                  print(semicolon());
                                                            #line 9445 "PrintCLike.cpp"
  append(L"\n");
  append(L"while ");
                                                            #line 5415 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                            #line 9450 "PrintCLike.cpp"
  append(L"l > x");
                                                            #line 5416 "PrintCLike.cpp.template"
                                                                  print(ifRightParen());
                                                                  print(leftBrace());
                                                                }
                                                            #line 9456 "PrintCLike.cpp"
  append(L"\n");
  append(L"  i += 2");
                                                            #line 5420 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 9461 "PrintCLike.cpp"
  append(L"\n");
  append(L"  l = ");
                                                            #line 5422 "PrintCLike.cpp.template"
                                                                print(staticPrefix());
                                                                print(lookback);
                                                                print(leftbracket());
                                                            #line 9468 "PrintCLike.cpp"
  append(L"i");
                                                            #line 5425 "PrintCLike.cpp.template"
                                                                print(rightbracket());
                                                                print(semicolon());
                                                                print(rightBrace());
                                                            #line 9474 "PrintCLike.cpp"
  append(L"\n");
  append(L"if ");
                                                            #line 5429 "PrintCLike.cpp.template"
                                                                print(ifLeftParen());
                                                            #line 9479 "PrintCLike.cpp"
  append(L"l < x");
                                                            #line 5430 "PrintCLike.cpp.template"
                                                                print(ifRightParen());
                                                                print(leftBrace());
                                                            #line 9484 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5433 "PrintCLike.cpp.template"
                                                                print(returnKeyword());
                                                            #line 9489 "PrintCLike.cpp"
  append(L"0");
                                                            #line 5434 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 9493 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5436 "PrintCLike.cpp.template"
                                                                print(elseWithBraces());
                                                            #line 9497 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5438 "PrintCLike.cpp.template"
                                                                print(returnKeyword());
                                                                print(staticPrefix());
                                                                print(lookback);
                                                                print(leftbracket());
                                                            #line 9505 "PrintCLike.cpp"
  append(L"i + 1");
                                                            #line 5442 "PrintCLike.cpp.template"
                                                                print(rightbracket());
                                                                print(semicolon());
                                                                print(rightBrace());
                                                                decreaseIndent();
                                                                print(rightBrace());
                                                            #line 9513 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5448 "PrintCLike.cpp.template"
                                                                if (isJavascript() && useGlr)
                                                                {
                                                            #line 9518 "PrintCLike.cpp"
  append(L"\n");
  append(L"this.count = function(code)\n");
                                                            #line 5452 "PrintCLike.cpp.template"
                                                                }
                                                                else if (isTypescript() && useGlr)
                                                                {
                                                            #line 9525 "PrintCLike.cpp"
  append(L"\n");
  append(L"public count(code: number)\n");
                                                            #line 5457 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                                  openMethod(intType(), L"", L"count", L"int code", false, clazz);
                                                                }
                                                                print(leftBrace());
                                                                increaseIndent();
                                                            #line 9536 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5465 "PrintCLike.cpp.template"
                                                                print(intVar());
                                                            #line 9540 "PrintCLike.cpp"
  append(L"count");
                                                            #line 5466 "PrintCLike.cpp.template"
                                                                print(assign());
                                                            #line 9544 "PrintCLike.cpp"
  append(L"0");
                                                            #line 5467 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                int stackElementSize = tree ? 3 : 2;
                                                                if (isHaxe() || isScala())
                                                                {
                                                                  if (useGlr)
                                                                  {
                                                            #line 9553 "PrintCLike.cpp"
  append(L"\n");
  append(L"var node = this");
                                                            #line 5474 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                    if (isScala())
                                                                    {
                                                            #line 9560 "PrintCLike.cpp"
  append(L"\n");
  append(L"var c = code");
                                                            #line 5478 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 9565 "PrintCLike.cpp"
  append(L"\n");
  append(L"while ");
                                                            #line 5480 "PrintCLike.cpp.template"
                                                                    print(ifLeftParen());
                                                            #line 9570 "PrintCLike.cpp"
  append(L"node.state >= 0");
                                                            #line 5481 "PrintCLike.cpp.template"
                                                                    print(ifRightParen());
                                                                    print(leftBrace());
                                                                    if (isScala())
                                                                    {
                                                            #line 9577 "PrintCLike.cpp"
  append(L"\n");
  append(L"  c = lookback(node.code, c)\n");
  append(L"  if (c == 0) return count\n");
  append(L"  count += 1");
                                                            #line 5488 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 9586 "PrintCLike.cpp"
  append(L"\n");
  append(L"  code = lookback(node.code, code);\n");
  append(L"  if ");
                                                            #line 5493 "PrintCLike.cpp.template"
                                                                      print(ifLeftParen());
                                                            #line 9592 "PrintCLike.cpp"
  append(L"code == 0");
                                                            #line 5494 "PrintCLike.cpp.template"
                                                                      print(ifRightParen());
                                                            #line 9596 "PrintCLike.cpp"
  append(L"\n");
  append(L"    break");
                                                            #line 5497 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                            #line 9601 "PrintCLike.cpp"
  append(L"\n");
  append(L"  count++");
                                                            #line 5499 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                                    }
                                                            #line 9607 "PrintCLike.cpp"
  append(L"\n");
  append(L"  node = node.link");
                                                            #line 5502 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                  }
                                                                  else
                                                                  {
                                                            #line 9615 "PrintCLike.cpp"
  append(L"\n");
  append(L"var t = top");
                                                            #line 5507 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 9620 "PrintCLike.cpp"
  append(L"\n");
  append(L"var c = code");
                                                            #line 5509 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 9625 "PrintCLike.cpp"
  append(L"\n");
  append(L"while (t >= 0)");
                                                            #line 5511 "PrintCLike.cpp.template"
                                                                    print(leftBrace());
                                                            #line 9630 "PrintCLike.cpp"
  append(L"\n");
  append(L"  c = lookback(iStack");
                                                            #line 5513 "PrintCLike.cpp.template"
                                                                    print(leftbracket());
                                                            #line 9635 "PrintCLike.cpp"
  append(L"t");
                                                            #line 5514 "PrintCLike.cpp.template"
                                                                    print(rightbracket());
                                                            #line 9639 "PrintCLike.cpp"
  append(L", c)");
                                                            #line 5515 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 9643 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if ");
                                                            #line 5517 "PrintCLike.cpp.template"
                                                                    print(ifLeftParen());
                                                            #line 9648 "PrintCLike.cpp"
  append(L"c == 0");
                                                            #line 5518 "PrintCLike.cpp.template"
                                                                    print(ifRightParen());
                                                            #line 9652 "PrintCLike.cpp"
  append(L" return count");
                                                            #line 5519 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 9656 "PrintCLike.cpp"
  append(L"\n");
  append(L"  count += 1");
                                                            #line 5521 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 9661 "PrintCLike.cpp"
  append(L"\n");
  append(L"  t -= ");
                                                            #line 5523 "PrintCLike.cpp.template"
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
                                                            #line 9675 "PrintCLike.cpp"
  append(L"\n");
  append(L"node = self\n");
  append(L"while ");
                                                            #line 5535 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 9683 "PrintCLike.cpp"
  append(L"\n");
  append(L"for ");
                                                            #line 5539 "PrintCLike.cpp.template"
                                                                      print(ifLeftParen());
                                                                      if (isJavascript() || isTypescript())
                                                                      {
                                                            #line 9690 "PrintCLike.cpp"
  append(L"var ");
                                                            #line 5542 "PrintCLike.cpp.template"
                                                                      }
                                                                      else if (!isGo())
                                                                      {
                                                            #line 9696 "PrintCLike.cpp"
  append(L"StackNode ");
                                                            #line 5545 "PrintCLike.cpp.template"
                                                                      }
                                                                      if (isCpp()) print(L"*");
                                                            #line 9701 "PrintCLike.cpp"
  append(L"node");
                                                            #line 5547 "PrintCLike.cpp.template"
                                                                      if (isTypescript())
                                                                      {
                                                            #line 9706 "PrintCLike.cpp"
  append(L": StackNode | null");
                                                            #line 5549 "PrintCLike.cpp.template"
                                                                      }
                                                                      print(assign());
                                                            #line 9711 "PrintCLike.cpp"
  append(L"this; ");
                                                            #line 5551 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 9715 "PrintCLike.cpp"
  append(L"node");
                                                            #line 5552 "PrintCLike.cpp.template"
                                                                    if (isTypescript()) print(L"!");
                                                                    print(arrow());
                                                            #line 9720 "PrintCLike.cpp"
  append(L"state >= 0");
                                                            #line 5554 "PrintCLike.cpp.template"
                                                                    if (isPython())
                                                                    {
                                                            #line 9725 "PrintCLike.cpp"
  append(L":");
                                                            #line 5556 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 9731 "PrintCLike.cpp"
  append(L"; node = node");
                                                            #line 5559 "PrintCLike.cpp.template"
                                                                      if (isTypescript()) print(L"!");
                                                                      print(arrow());
                                                            #line 9736 "PrintCLike.cpp"
  append(L"link");
                                                            #line 5561 "PrintCLike.cpp.template"
                                                                      print(ifRightParen());
                                                                    }
                                                                    print(leftBrace());
                                                            #line 9742 "PrintCLike.cpp"
  append(L"\n");
  append(L"  code = ");
                                                            #line 5565 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                                    print(isGo() ? L"L" : L"l");
                                                            #line 9748 "PrintCLike.cpp"
  append(L"ookback(node");
                                                            #line 5567 "PrintCLike.cpp.template"
                                                                    if (isTypescript()) print(L"!");
                                                                    print(arrow());
                                                            #line 9753 "PrintCLike.cpp"
  append(L"code, code)");
                                                            #line 5569 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                  }
                                                                  else
                                                                  {
                                                                    if (isPython())
                                                                    {
                                                            #line 9762 "PrintCLike.cpp"
  append(L"\n");
  append(L"t");
                                                            #line 5576 "PrintCLike.cpp.template"
                                                                      print(assign());
                                                                      print(thiz());
                                                            #line 9768 "PrintCLike.cpp"
  append(L"top");
                                                            #line 5578 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                            #line 9772 "PrintCLike.cpp"
  append(L"\n");
  append(L"while ");
                                                            #line 5580 "PrintCLike.cpp.template"
                                                                      print(ifLeftParen());
                                                                      print(intVar());
                                                            #line 9778 "PrintCLike.cpp"
  append(L"t >= 0");
                                                            #line 5582 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 9784 "PrintCLike.cpp"
  append(L"\n");
  append(L"for ");
                                                            #line 5586 "PrintCLike.cpp.template"
                                                                      print(ifLeftParen());
                                                                      print(intVar());
                                                            #line 9790 "PrintCLike.cpp"
  append(L"t");
                                                            #line 5588 "PrintCLike.cpp.template"
                                                                      print(assign());
                                                                      print(thiz());
                                                            #line 9795 "PrintCLike.cpp"
  append(L"top; t >= 0; t -= ");
                                                            #line 5590 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(stackElementSize));
                                                                    }
                                                                    print(ifRightParen());
                                                                    print(leftBrace());
                                                            #line 9802 "PrintCLike.cpp"
  append(L"\n");
  append(L"  code = ");
                                                            #line 5595 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 9807 "PrintCLike.cpp"
  append(L"lookback(");
                                                            #line 5596 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 9811 "PrintCLike.cpp"
  append(L"iStack[t], code)");
                                                            #line 5597 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                  }
                                                            #line 9816 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if ");
                                                            #line 5600 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                            #line 9821 "PrintCLike.cpp"
  append(L"code == 0");
                                                            #line 5601 "PrintCLike.cpp.template"
                                                                  print(ifRightParen());
                                                                  increaseIndent();
                                                                  print(leftBrace());
                                                            #line 9827 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5605 "PrintCLike.cpp.template"
                                                                  if (! isHaxe() && ! isScala())
                                                                  {
                                                            #line 9833 "PrintCLike.cpp"
  append(L"break");
                                                            #line 5607 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 9839 "PrintCLike.cpp"
  append(L"return count");
                                                            #line 5610 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(semicolon());
                                                                  print(rightBrace());
                                                                  decreaseIndent();
                                                            #line 9846 "PrintCLike.cpp"
  append(L"\n");
  append(L"  count += 1");
                                                            #line 5615 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                  if (isPython())
                                                                  {
                                                                    if (useGlr)
                                                                    {
                                                            #line 9855 "PrintCLike.cpp"
  append(L"\n");
  append(L"  node = node.link");
                                                            #line 5621 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 9862 "PrintCLike.cpp"
  append(L"\n");
  append(L"  t -= ");
                                                            #line 5625 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(stackElementSize));
                                                                    }
                                                                  }
                                                                }
                                                                print(rightBrace());
                                                            #line 9871 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5631 "PrintCLike.cpp.template"
                                                                print(returnKeyword());
                                                            #line 9875 "PrintCLike.cpp"
  append(L"count");
                                                            #line 5632 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                decreaseIndent();
                                                                print(rightBrace());
                                                                if (isJavascript() && useGlr)
                                                                {
                                                            #line 9883 "PrintCLike.cpp"
  append(L";");
                                                            #line 5637 "PrintCLike.cpp.template"
                                                                }
                                                            #line 9887 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5639 "PrintCLike.cpp.template"
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
                                                            #line 9912 "PrintCLike.cpp"
  append(L"\n");
  append(L"if ");
                                                            #line 5662 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                                  print(thiz());
                                                            #line 9918 "PrintCLike.cpp"
  append(L"l");
                                                            #line 5664 "PrintCLike.cpp.template"
                                                                  print(kAsString);
                                                            #line 9922 "PrintCLike.cpp"
  append(L" == 0");
                                                            #line 5665 "PrintCLike.cpp.template"
                                                                  print(ifRightParen());
                                                                  print(leftBrace());
                                                            #line 9927 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5668 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 9932 "PrintCLike.cpp"
  append(L"l");
                                                            #line 5669 "PrintCLike.cpp.template"
                                                                  print(kAsString);
                                                            #line 9936 "PrintCLike.cpp"
  append(L" = ");
                                                            #line 5670 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 9940 "PrintCLike.cpp"
  append(L"match");
                                                            #line 5671 "PrintCLike.cpp.template"
                                                                  if (withWhitespace)
                                                                  {
                                                            #line 9945 "PrintCLike.cpp"
  append(L"W");
                                                            #line 5673 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isScala())
                                                                  {
                                                            #line 9951 "PrintCLike.cpp"
  append(L"er");
                                                            #line 5676 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 9955 "PrintCLike.cpp"
  append(L"(tokenSetId)");
                                                            #line 5677 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                            #line 9959 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5679 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 9964 "PrintCLike.cpp"
  append(L"b");
                                                            #line 5680 "PrintCLike.cpp.template"
                                                                  print(kAsString);
                                                            #line 9968 "PrintCLike.cpp"
  append(L" = ");
                                                            #line 5681 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 9972 "PrintCLike.cpp"
  append(L"begin");
                                                            #line 5682 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                            #line 9976 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5684 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 9981 "PrintCLike.cpp"
  append(L"e");
                                                            #line 5685 "PrintCLike.cpp.template"
                                                                  print(kAsString);
                                                            #line 9985 "PrintCLike.cpp"
  append(L" = ");
                                                            #line 5686 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 9989 "PrintCLike.cpp"
  append(L"end");
                                                            #line 5687 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                  print(rightBrace());
                                                                  if (unlimitedLookahead)
                                                                  {
                                                                    if (k >= 2)
                                                                    {
                                                            #line 9998 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5694 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 10002 "PrintCLike.cpp"
  append(L"lk = prefix + ");
                                                            #line 5695 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 10006 "PrintCLike.cpp"
  append(L"l");
                                                            #line 5696 "PrintCLike.cpp.template"
                                                                      print(kAsString);
                                                                      print(semicolon());
                                                                    }
                                                                  }
                                                                  else
                                                                  {
                                                                    if (k == 2)
                                                                    {
                                                            #line 10017 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5705 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 10021 "PrintCLike.cpp"
  append(L"lk = (");
                                                            #line 5706 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 10025 "PrintCLike.cpp"
  append(L"l2 << ");
                                                            #line 5707 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(grammar->tokenSequenceFactory->tokenBits()));
                                                            #line 10029 "PrintCLike.cpp"
  append(L") | ");
                                                            #line 5708 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 10033 "PrintCLike.cpp"
  append(L"l1");
                                                            #line 5709 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                                    }
                                                                    else if (k > 2)
                                                                    {
                                                            #line 10040 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5714 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 10044 "PrintCLike.cpp"
  append(L"lk |= ");
                                                            #line 5715 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 10048 "PrintCLike.cpp"
  append(L"l");
                                                            #line 5716 "PrintCLike.cpp.template"
                                                                      print(kAsString);
                                                            #line 10052 "PrintCLike.cpp"
  append(L" << ");
                                                            #line 5717 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>((k - 1) * grammar->tokenSequenceFactory->tokenBits()));
                                                                      print(semicolon());
                                                                    }
                                                                  }
                                                                  decreaseIndent();
                                                                  print(rightBrace());
                                                            #line 10061 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5724 "PrintCLike.cpp.template"
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
                                                            #line 10089 "PrintCLike.cpp"
  append(L"\n");
  append(L"  return ");
                                                            #line 5750 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                                if (useGlr && (isCSharp() || isCpp() || isHaxe() || isScala() || isTypescript()))
                                                                {
                                                            #line 10096 "PrintCLike.cpp"
  append(L"parser");
                                                            #line 5753 "PrintCLike.cpp.template"
                                                                  print(arrow());
                                                                }
                                                            #line 10101 "PrintCLike.cpp"
  append(L"input");
                                                            #line 5755 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                print(rightBrace());
                                                                if (isJavascript())
                                                                {
                                                            #line 10108 "PrintCLike.cpp"
  append(L";");
                                                            #line 5759 "PrintCLike.cpp.template"
                                                                }
                                                            #line 10112 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5761 "PrintCLike.cpp.template"
                                                                openMethod(intType(), L"", L"getTokenOffset", L"", true);
                                                                print(leftBrace());
                                                            #line 10117 "PrintCLike.cpp"
  append(L"\n");
  append(L"  return ");
                                                            #line 5764 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 10122 "PrintCLike.cpp"
  append(L"b0");
                                                            #line 5765 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                print(rightBrace());
                                                                if (isJavascript())
                                                                {
                                                            #line 10129 "PrintCLike.cpp"
  append(L";");
                                                            #line 5769 "PrintCLike.cpp.template"
                                                                }
                                                            #line 10133 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5771 "PrintCLike.cpp.template"
                                                                openMethod(intType(), L"", L"getTokenEnd", L"", true);
                                                                print(leftBrace());
                                                            #line 10138 "PrintCLike.cpp"
  append(L"\n");
  append(L"  return ");
                                                            #line 5774 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 10143 "PrintCLike.cpp"
  append(L"e0");
                                                            #line 5775 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                print(rightBrace());
                                                                if (isJavascript())
                                                                {
                                                            #line 10150 "PrintCLike.cpp"
  append(L";");
                                                            #line 5779 "PrintCLike.cpp.template"
                                                                }
                                                            #line 10154 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5781 "PrintCLike.cpp.template"
                                                              }
                                                              if (isJavascript())
                                                              {
                                                                if (useGlr)
                                                                {
                                                            #line 10162 "PrintCLike.cpp"
  append(L"\n");
  append(L"this.reset = function");
                                                            #line 5787 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 10169 "PrintCLike.cpp"
  append(L"\n");
  append(L"function reset");
                                                            #line 5791 "PrintCLike.cpp.template"
                                                                }
                                                            #line 10174 "PrintCLike.cpp"
  append(L"(l, b, e)\n");
  append(L"{");
                                                            #line 5793 "PrintCLike.cpp.template"
                                                              }
                                                              else if (isTypescript())
                                                              {
                                                            #line 10181 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5797 "PrintCLike.cpp.template"
                                                                if (! performanceTest && ! useGlr)
                                                                {
                                                            #line 10186 "PrintCLike.cpp"
  append(L"private ");
                                                            #line 5799 "PrintCLike.cpp.template"
                                                                }
                                                            #line 10190 "PrintCLike.cpp"
  append(L"reset(l: number, b: number, e: number)\n");
  append(L"{");
                                                            #line 5801 "PrintCLike.cpp.template"
                                                              }
                                                              else if (isHaxe())
                                                              {
                                                            #line 10197 "PrintCLike.cpp"
  append(L"\n");
  append(L"public function reset(l, b, e)\n");
  append(L"{");
                                                            #line 5806 "PrintCLike.cpp.template"
                                                              }
                                                              else
                                                              {
                                                                openMethod(voidType(), isJava() ? L"final " : L"", L"reset", L"int l, int b, int e", false, useGlr ? L"ParsingThread" : className.c_str());
                                                                print(leftBrace());
                                                              }
                                                            #line 10208 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5813 "PrintCLike.cpp.template"
                                                              if (! isPython() && ! isScala())
                                                              {
                                                            #line 10214 "PrintCLike.cpp"
  append(L"        ");
                                                            #line 5815 "PrintCLike.cpp.template"
                                                                print(wcslen(thiz()), L" ");
                                                              }
                                                              print(thiz());
                                                            #line 10220 "PrintCLike.cpp"
  append(L"b0 = b; ");
                                                            #line 5818 "PrintCLike.cpp.template"
                                                              print(thiz());
                                                            #line 10224 "PrintCLike.cpp"
  append(L"e0 = b");
                                                            #line 5819 "PrintCLike.cpp.template"
                                                              print(semicolon());
                                                            #line 10228 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5821 "PrintCLike.cpp.template"
                                                              print(thiz());
                                                            #line 10233 "PrintCLike.cpp"
  append(L"l1 = l; ");
                                                            #line 5822 "PrintCLike.cpp.template"
                                                              print(thiz());
                                                            #line 10237 "PrintCLike.cpp"
  append(L"b1 = b; ");
                                                            #line 5823 "PrintCLike.cpp.template"
                                                              print(thiz());
                                                            #line 10241 "PrintCLike.cpp"
  append(L"e1 = e");
                                                            #line 5824 "PrintCLike.cpp.template"
                                                              print(semicolon());
                                                              for (size_t k = 2; k <= grammar->k; ++k)
                                                              {
                                                            #line 10247 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5828 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 10252 "PrintCLike.cpp"
  append(L"l");
                                                            #line 5829 "PrintCLike.cpp.template"
                                                                print(format.toString<wchar_t>(k));
                                                            #line 10256 "PrintCLike.cpp"
  append(L" = 0; ");
                                                            #line 5830 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 10260 "PrintCLike.cpp"
  append(L"b");
                                                            #line 5831 "PrintCLike.cpp.template"
                                                                print(format.toString<wchar_t>(k));
                                                            #line 10264 "PrintCLike.cpp"
  append(L" = 0; ");
                                                            #line 5832 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 10268 "PrintCLike.cpp"
  append(L"e");
                                                            #line 5833 "PrintCLike.cpp.template"
                                                                print(format.toString<wchar_t>(k));
                                                            #line 10272 "PrintCLike.cpp"
  append(L" = 0");
                                                            #line 5834 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                              }
                                                            #line 10277 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5837 "PrintCLike.cpp.template"
                                                              print(thiz());
                                                            #line 10282 "PrintCLike.cpp"
  append(L"end = e");
                                                            #line 5838 "PrintCLike.cpp.template"
                                                              print(semicolon());
                                                              if (hasBacktracking)
                                                              {
                                                            #line 10288 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5842 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 10293 "PrintCLike.cpp"
  append(L"ex = -1");
                                                            #line 5843 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                if (memoization)
                                                                {
                                                                  if (isJavascript() || isTypescript())
                                                                  {
                                                            #line 10301 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5849 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 10306 "PrintCLike.cpp"
  append(L"memo = {};");
                                                            #line 5850 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isCSharp())
                                                                  {
                                                            #line 10312 "PrintCLike.cpp"
  append(L"\n");
  append(L"  memo.Clear();");
                                                            #line 5854 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isScala())
                                                                  {
                                                            #line 10319 "PrintCLike.cpp"
  append(L"\n");
  append(L"  memo.clear()");
                                                            #line 5858 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isHaxe())
                                                                  {
                                                            #line 10326 "PrintCLike.cpp"
  append(L"\n");
  append(L"  memo = new Map();");
                                                            #line 5862 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isGo())
                                                                  {
                                                            #line 10333 "PrintCLike.cpp"
  append(L"\n");
  append(L"  this.memo = make(map[int]int)");
                                                            #line 5866 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isPython())
                                                                  {
                                                            #line 10340 "PrintCLike.cpp"
  append(L"\n");
  append(L"  self.memo = {}");
                                                            #line 5870 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 10347 "PrintCLike.cpp"
  append(L"\n");
  append(L"  memo.clear();");
                                                            #line 5874 "PrintCLike.cpp.template"
                                                                  }
                                                                }
                                                                if (grammar->noThrow)
                                                                {
                                                            #line 10355 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5879 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 10360 "PrintCLike.cpp"
  append(L"viable = ");
                                                            #line 5880 "PrintCLike.cpp.template"
                                                                  if (isPython())
                                                                  {
                                                            #line 10365 "PrintCLike.cpp"
  append(L"T");
                                                            #line 5882 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 10371 "PrintCLike.cpp"
  append(L"t");
                                                            #line 5885 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 10375 "PrintCLike.cpp"
  append(L"rue");
                                                            #line 5886 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                              }
                                                              if (tree && ! useGlr)
                                                              {
                                                            #line 10383 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5892 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 10388 "PrintCLike.cpp"
  append(L"eventHandler");
                                                            #line 5893 "PrintCLike.cpp.template"
                                                                if (isTypescript() && isLrParser) print(L"!");
                                                                print(arrow());
                                                                if (isGo())
                                                                {
                                                            #line 10395 "PrintCLike.cpp"
  append(L"R");
                                                            #line 5897 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 10401 "PrintCLike.cpp"
  append(L"r");
                                                            #line 5900 "PrintCLike.cpp.template"
                                                                }
                                                            #line 10405 "PrintCLike.cpp"
  append(L"eset(");
                                                            #line 5901 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 10409 "PrintCLike.cpp"
  append(L"input)");
                                                            #line 5902 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                              }
                                                              if (useGlr)
                                                              {
                                                            #line 10416 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5907 "PrintCLike.cpp.template"
                                                                if (isCSharp() || isCpp() || isHaxe() || isScala() || isTypescript() || isGo())
                                                                {
                                                                  print(thiz());
                                                            #line 10423 "PrintCLike.cpp"
  append(L"parser");
                                                            #line 5910 "PrintCLike.cpp.template"
                                                                  print(arrow());
                                                                }
                                                            #line 10428 "PrintCLike.cpp"
  append(L"maxId = 0");
                                                            #line 5912 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 10432 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5914 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 10437 "PrintCLike.cpp"
  append(L"id = ");
                                                            #line 5915 "PrintCLike.cpp.template"
                                                                if (isCSharp() || isCpp() || isHaxe() || isScala() || isTypescript() || isGo())
                                                                {
                                                                  print(thiz());
                                                            #line 10443 "PrintCLike.cpp"
  append(L"parser");
                                                            #line 5918 "PrintCLike.cpp.template"
                                                                   print(arrow());
                                                                }
                                                            #line 10448 "PrintCLike.cpp"
  append(L"maxId");
                                                            #line 5920 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                              }
                                                              print(rightBrace());
                                                              if (isJavascript() && useGlr)
                                                              {
                                                            #line 10456 "PrintCLike.cpp"
  append(L";");
                                                            #line 5925 "PrintCLike.cpp.template"
                                                              }
                                                            #line 10460 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5927 "PrintCLike.cpp.template"
                                                              if (useGlr || isJavascript() || isTypescript() || isHaxe() || isGo() || isPython())
                                                              {
                                                              }
                                                              else
                                                              {
                                                                openMethod(voidType(), L"", L"reset", L"");
                                                                print(leftBrace());
                                                            #line 10470 "PrintCLike.cpp"
  append(L"\n");
  append(L"  reset(0, 0, 0)");
                                                            #line 5935 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                print(rightBrace());
                                                            #line 10476 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5938 "PrintCLike.cpp.template"
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
                                                            #line 10504 "PrintCLike.cpp"
  append(L"\n");
  append(L"if ");
                                                            #line 5964 "PrintCLike.cpp.template"
                                                                    print(ifLeftParen());
                                                            #line 10509 "PrintCLike.cpp"
  append(L"(");
                                                            #line 5965 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                                    print(token());
                                                            #line 10514 "PrintCLike.cpp"
  append(L" == ");
                                                            #line 5967 "PrintCLike.cpp.template"
                                                                    print(format.toString<wchar_t>(grammar->externalTokenCode[plusplus]));
                                                                    if (isPython())
                                                                    {
                                                            #line 10520 "PrintCLike.cpp"
  append(L" or ");
                                                            #line 5970 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 10526 "PrintCLike.cpp"
  append(L" || ");
                                                            #line 5973 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(thiz());
                                                                    print(token());
                                                            #line 10532 "PrintCLike.cpp"
  append(L" == ");
                                                            #line 5976 "PrintCLike.cpp.template"
                                                                    print(format.toString<wchar_t>(grammar->externalTokenCode[minusminus]));
                                                            #line 10536 "PrintCLike.cpp"
  append(L")");
                                                            #line 5978 "PrintCLike.cpp.template"
                                                                    if (isPython())
                                                                    {
                                                            #line 10541 "PrintCLike.cpp"
  append(L" and ");
                                                            #line 5980 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 10547 "PrintCLike.cpp"
  append(L" && ");
                                                            #line 5983 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(thiz());
                                                            #line 10552 "PrintCLike.cpp"
  append(L"followsLineTerminator");
                                                            #line 5985 "PrintCLike.cpp.template"
                                                                    if (! isScala())
                                                                    {
                                                            #line 10557 "PrintCLike.cpp"
  append(L"()");
                                                            #line 5987 "PrintCLike.cpp.template"
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
                                                            #line 10571 "PrintCLike.cpp"
  append(L"\n");
  append(L"if ");
                                                            #line 5999 "PrintCLike.cpp.template"
                                                                    print(ifLeftParen());
                                                                    print(thiz());
                                                                    print(token());
                                                            #line 10578 "PrintCLike.cpp"
  append(L" != ");
                                                            #line 6002 "PrintCLike.cpp.template"
                                                                    print(format.toString<wchar_t>(grammar->externalTokenCode[semicolonToken]));
                                                                    if (isPython())
                                                                    {
                                                            #line 10584 "PrintCLike.cpp"
  append(L" and ");
                                                            #line 6005 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 10590 "PrintCLike.cpp"
  append(L" && ");
                                                            #line 6008 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(thiz());
                                                                    print(token());
                                                            #line 10596 "PrintCLike.cpp"
  append(L" >= 0");
                                                            #line 6012 "PrintCLike.cpp.template"
                                                                    if (isPython())
                                                                    {
                                                            #line 10601 "PrintCLike.cpp"
  append(L" and ");
                                                            #line 6014 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 10607 "PrintCLike.cpp"
  append(L" && ");
                                                            #line 6017 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(thiz());
                                                            #line 10612 "PrintCLike.cpp"
  append(L"followsLineTerminator");
                                                            #line 6019 "PrintCLike.cpp.template"
                                                                    if (! isScala())
                                                                    {
                                                            #line 10617 "PrintCLike.cpp"
  append(L"()");
                                                            #line 6021 "PrintCLike.cpp.template"
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
                                                            #line 10632 "PrintCLike.cpp"
  append(L"\n");
  append(L"if ");
                                                            #line 6034 "PrintCLike.cpp.template"
                                                                    print(isPython() ? L"(" : ifLeftParen());
                                                                    print(thiz());
                                                                    print(token());
                                                            #line 10639 "PrintCLike.cpp"
  append(L" == ");
                                                            #line 6037 "PrintCLike.cpp.template"
                                                                    print(format.toString<wchar_t>(grammar->externalTokenCode[rbrace]));
                                                                    if (isPython())
                                                                    {
                                                            #line 10645 "PrintCLike.cpp"
  append(L" or");
                                                            #line 6040 "PrintCLike.cpp.template"
                                                                    }
                                                                    else if (isGo())
                                                                    {
                                                            #line 10651 "PrintCLike.cpp"
  append(L" ||");
                                                            #line 6043 "PrintCLike.cpp.template"
                                                                    }
                                                                    printCodeSequenceAnnotation(grammar->tokenSequence(rbrace));
                                                                    if (isGo() || isPython())
                                                                    {
                                                            #line 10658 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 6048 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 10665 "PrintCLike.cpp"
  append(L"\n");
  append(L" || ");
                                                            #line 6052 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(thiz());
                                                                    print(token());
                                                            #line 10672 "PrintCLike.cpp"
  append(L" == ");
                                                            #line 6055 "PrintCLike.cpp.template"
                                                                    print(format.toString<wchar_t>(grammar->externalTokenCode[eof]));
                                                                    if (isPython())
                                                                    {
                                                            #line 10678 "PrintCLike.cpp"
  append(L" or");
                                                            #line 6058 "PrintCLike.cpp.template"
                                                                    }
                                                                    else if (isGo())
                                                                    {
                                                            #line 10684 "PrintCLike.cpp"
  append(L" ||");
                                                            #line 6061 "PrintCLike.cpp.template"
                                                                    }
                                                                    printCodeSequenceAnnotation(grammar->tokenSequence(eof));
                                                                    if (isGo() || isPython())
                                                                    {
                                                            #line 10691 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 6066 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 10698 "PrintCLike.cpp"
  append(L"\n");
  append(L" || ");
                                                            #line 6070 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(thiz());
                                                                    print(token());
                                                            #line 10705 "PrintCLike.cpp"
  append(L" != ");
                                                            #line 6073 "PrintCLike.cpp.template"
                                                                    print(format.toString<wchar_t>(grammar->externalTokenCode[semicolonToken]));
                                                                    if (isPython())
                                                                    {
                                                            #line 10711 "PrintCLike.cpp"
  append(L" and ");
                                                            #line 6076 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 10717 "PrintCLike.cpp"
  append(L" && ");
                                                            #line 6079 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(thiz());
                                                                    print(token());
                                                            #line 10723 "PrintCLike.cpp"
  append(L" >= 0");
                                                            #line 6083 "PrintCLike.cpp.template"
                                                                    if (isPython())
                                                                    {
                                                            #line 10728 "PrintCLike.cpp"
  append(L" and ");
                                                            #line 6085 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 10734 "PrintCLike.cpp"
  append(L" && ");
                                                            #line 6088 "PrintCLike.cpp.template"
                                                                    }
                                                                    if (afterRbrace)
                                                                    {
                                                            #line 10740 "PrintCLike.cpp"
  append(L"(");
                                                            #line 6091 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(thiz());
                                                            #line 10745 "PrintCLike.cpp"
  append(L"followsLineTerminator");
                                                            #line 6093 "PrintCLike.cpp.template"
                                                                    if (! isScala())
                                                                    {
                                                            #line 10750 "PrintCLike.cpp"
  append(L"()");
                                                            #line 6095 "PrintCLike.cpp.template"
                                                                    }
                                                                    if (afterRbrace)
                                                                    {
                                                                      if (isPython())
                                                                      {
                                                            #line 10758 "PrintCLike.cpp"
  append(L" || ");
                                                            #line 6100 "PrintCLike.cpp.template"
                                                                      }
                                                                      else
                                                                      {
                                                            #line 10764 "PrintCLike.cpp"
  append(L" or ");
                                                            #line 6103 "PrintCLike.cpp.template"
                                                                      }
                                                                      if (isCpp() || isCSharp() || isPython() || (isJava() && codepoints))
                                                                      {
                                                                        print(thiz());
                                                            #line 10771 "PrintCLike.cpp"
  append(L"input");
                                                            #line 6108 "PrintCLike.cpp.template"
                                                            
                                                            #line 10775 "PrintCLike.cpp"
  append(L"[");
                                                            #line 6108 "PrintCLike.cpp.template"
                                                                        print(thiz());
                                                            #line 10779 "PrintCLike.cpp"
  append(L"b0]");
                                                            #line 6109 "PrintCLike.cpp.template"
                                                                      }
                                                                      else
                                                                      {
                                                                        print(thiz());
                                                            #line 10786 "PrintCLike.cpp"
  append(L"input.char");
                                                            #line 6113 "PrintCLike.cpp.template"
                                                                        if (isTypescript() || isJavascript() || isHaxe())
                                                                        {
                                                            #line 10791 "PrintCLike.cpp"
  append(L"Code");
                                                            #line 6116 "PrintCLike.cpp.template"
                                                                        }
                                                            #line 10795 "PrintCLike.cpp"
  append(L"At(");
                                                            #line 6117 "PrintCLike.cpp.template"
                                                                       print(thiz());
                                                            #line 10799 "PrintCLike.cpp"
  append(L"b0)");
                                                            #line 6119 "PrintCLike.cpp.template"
                                                                      }
                                                            #line 10803 "PrintCLike.cpp"
  append(L" == 0x7D)");
                                                            #line 6120 "PrintCLike.cpp.template"
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
                                                            #line 10816 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 6131 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 10821 "PrintCLike.cpp"
  append(L"l1 = ");
                                                            #line 6132 "PrintCLike.cpp.template"
                                                                print(format.toString<wchar_t>(grammar->externalTokenCode[semicolonToken]));
                                                                print(semicolon());
                                                            #line 10826 "PrintCLike.cpp"
  append(L" ");
                                                            #line 6134 "PrintCLike.cpp.template"
                                                                printCodeSequenceAnnotation(grammar->tokenSequence(semicolonToken));
                                                            #line 10830 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 6136 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 10835 "PrintCLike.cpp"
  append(L"e1 = ");
                                                            #line 6137 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 10839 "PrintCLike.cpp"
  append(L"b1");
                                                            #line 6138 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 10843 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 6140 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 10848 "PrintCLike.cpp"
  append(L"end = ");
                                                            #line 6141 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 10852 "PrintCLike.cpp"
  append(L"e1");
                                                            #line 6142 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                print(rightBrace());
                                                              }
                                                            }

// End
