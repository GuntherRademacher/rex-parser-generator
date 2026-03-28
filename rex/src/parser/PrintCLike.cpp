// This file was generated on Sat Mar 28, 2026 21:32 (UTC+01) by REx v6.2-SNAPSHOT which is Copyright (c) 1979-2025 by Gunther Rademacher <grd@gmx.net>
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
                                                                WString args(isJava() ? L"CharSequence " : isTypescript() ? L"string " : stringType());
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
                                                                openMethod(voidType(), L"", L"initialize", args.c_str());
                                                              }
                                                              print(leftBrace());
                                                              if (tree)
                                                              {
                                                            #line 2466 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 1756 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 2471 "PrintCLike.cpp"
  append(L"eventHandler = parsingEventHandler");
                                                            #line 1757 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                              }
                                                            #line 2476 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 1760 "PrintCLike.cpp.template"
                                                              print(thiz());
                                                            #line 2481 "PrintCLike.cpp"
  append(L"input = ");
                                                            #line 1761 "PrintCLike.cpp.template"
                                                              if (isHaxe())
                                                              {
                                                            #line 2486 "PrintCLike.cpp"
  append(L"Bytes.ofString(source)");
                                                            #line 1763 "PrintCLike.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 2492 "PrintCLike.cpp"
  append(L"source");
                                                            #line 1766 "PrintCLike.cpp.template"
                                                              }
                                                              print(semicolon());
                                                              if (noLexer)
                                                              {
                                                            #line 2499 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 1771 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 2504 "PrintCLike.cpp"
  append(L"lexer = l");
                                                            #line 1772 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 2508 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 1774 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 2513 "PrintCLike.cpp"
  append(L"lexer.reset(input)");
                                                            #line 1775 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                              }
                                                              else if (isGo() || isPython())
                                                              {
                                                            #line 2520 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 1780 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 2525 "PrintCLike.cpp"
  append(L"size = len(source)");
                                                            #line 1781 "PrintCLike.cpp.template"
                                                              }
                                                              else if (! isCpp())
                                                              {
                                                            #line 2531 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 1785 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 2536 "PrintCLike.cpp"
  append(L"size = source.");
                                                            #line 1786 "PrintCLike.cpp.template"
                                                                print(isCSharp() ? L"L" : L"l");
                                                            #line 2540 "PrintCLike.cpp"
  append(L"ength");
                                                            #line 1787 "PrintCLike.cpp.template"
                                                                if (! isJavascript() && ! isTypescript() && ! isScala() && ! isHaxe() && ! isCSharp())
                                                                {
                                                            #line 2545 "PrintCLike.cpp"
  append(L"()");
                                                            #line 1789 "PrintCLike.cpp.template"
                                                                }
                                                                print(semicolon());
                                                              }
                                                              if (! interfaceName.empty() && useGlr)
                                                              {
                                                            #line 2553 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 1795 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                                print(isGo() ? L"R" : L"r");
                                                            #line 2559 "PrintCLike.cpp"
  append(L"eset()");
                                                            #line 1797 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                print(rightBrace());
                                                            #line 2564 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 1800 "PrintCLike.cpp.template"
                                                                openMethod(voidType(), L"", L"reset", L"");
                                                                print(leftBrace());
                                                              }
                                                              if (isLrParser && ! useGlr)
                                                              {
                                                                if (isPython())
                                                                {
                                                            #line 2574 "PrintCLike.cpp"
  append(L"\n");
  append(L"  self.iStack = [0 for _ in range(192)]");
                                                            #line 1808 "PrintCLike.cpp.template"
                                                                }
                                                                else if (isGo())
                                                                {
                                                            #line 2581 "PrintCLike.cpp"
  append(L"\n");
  append(L"  this.iStack = make([]int, 192)\n");
  append(L"  this.top = -1");
                                                            #line 1813 "PrintCLike.cpp.template"
                                                                }
                                                              }
                                                              if (useGlr)
                                                              {
                                                            #line 2590 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 1818 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 2595 "PrintCLike.cpp"
  append(L"maxId = 0");
                                                            #line 1819 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 2599 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 1821 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 2604 "PrintCLike.cpp"
  append(L"thread = ");
                                                            #line 1822 "PrintCLike.cpp.template"
                                                                if (isScala())
                                                                {
                                                            #line 2609 "PrintCLike.cpp"
  append(L"new ");
                                                            #line 1824 "PrintCLike.cpp.template"
                                                                  print(className.c_str());
                                                            #line 2613 "PrintCLike.cpp"
  append(L".ParsingThread");
                                                            #line 1825 "PrintCLike.cpp.template"
                                                                }
                                                                else if (isPython())
                                                                {
                                                                  print(className.c_str());
                                                            #line 2620 "PrintCLike.cpp"
  append(L".ParsingThread()");
                                                            #line 1829 "PrintCLike.cpp.template"
                                                                }
                                                                else if (isGo())
                                                                {
                                                            #line 2626 "PrintCLike.cpp"
  append(L"new(ParsingThread)");
                                                            #line 1832 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 2632 "PrintCLike.cpp"
  append(L"new ParsingThread()");
                                                            #line 1835 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                                if (isCSharp() || isCpp() || isHaxe() || isScala() || isTypescript() || isGo() || isPython())
                                                                {
                                                            #line 2639 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 1840 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 2644 "PrintCLike.cpp"
  append(L"thread");
                                                            #line 1841 "PrintCLike.cpp.template"
                                                                  print(arrow());
                                                            #line 2648 "PrintCLike.cpp"
  append(L"parser = ");
                                                            #line 1842 "PrintCLike.cpp.template"
                                                                  if (isPython())
                                                                  {
                                                            #line 2653 "PrintCLike.cpp"
  append(L"self");
                                                            #line 1844 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 2659 "PrintCLike.cpp"
  append(L"this");
                                                            #line 1847 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(semicolon());
                                                                }
                                                            #line 2665 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 1851 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 2670 "PrintCLike.cpp"
  append(L"thread");
                                                            #line 1852 "PrintCLike.cpp.template"
                                                                print(arrow());
                                                              }
                                                              else
                                                              {
                                                            #line 2677 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 1857 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                              }
                                                              print(isGo() ? L"R" : L"r");
                                                            #line 2684 "PrintCLike.cpp"
  append(L"eset(0, 0, 0)");
                                                            #line 1860 "PrintCLike.cpp.template"
                                                              print(semicolon());
                                                              print(rightBrace());
                                                            #line 2689 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 1863 "PrintCLike.cpp.template"
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
                                                            #line 2702 "PrintCLike.cpp"
  append(L"\n");
  append(L"this.reset = function(l, b, e)\n");
  append(L"{\n");
  append(L"  ");
                                                            #line 1876 "PrintCLike.cpp.template"
                                                                if (useGlr)
                                                                {
                                                            #line 2710 "PrintCLike.cpp"
  append(L"thread.");
                                                            #line 1878 "PrintCLike.cpp.template"
                                                                }
                                                            #line 2714 "PrintCLike.cpp"
  append(L"reset(l, b, e);\n");
  append(L"};\n");
                                                            #line 1881 "PrintCLike.cpp.template"
                                                                openMethod(L"static ", stringType(), L"getOffendingToken", L"ParseException e");
                                                                print(leftBrace());
                                                            #line 2720 "PrintCLike.cpp"
  append(L"\n");
  append(L"  var o = e.getOffending();\n");
  append(L"  return o >= 0 ? ");
                                                            #line 1885 "PrintCLike.cpp.template"
                                                                print(staticPrefix());
                                                            #line 2726 "PrintCLike.cpp"
  append(L"TOKEN[o] : ");
                                                            #line 1886 "PrintCLike.cpp.template"
                                                                print(nullPtr());
                                                            #line 2730 "PrintCLike.cpp"
  append(L";\n");
  append(L"};\n");
                                                            #line 1889 "PrintCLike.cpp.template"
                                                              }
                                                              else if (isTypescript())
                                                              {
                                                                if (performanceTest && useGlr)
                                                                {
                                                            #line 2739 "PrintCLike.cpp"
  append(L"\n");
  append(L"public reset(l: number, b: number, e: number)\n");
  append(L"{\n");
  append(L"  this.thread.reset(l, b, e);\n");
  append(L"}\n");
                                                            #line 1899 "PrintCLike.cpp.template"
                                                                }
                                                            #line 2747 "PrintCLike.cpp"
  append(L"\n");
  append(L"getOffendingToken(e: ParseException)\n");
  append(L"{");
  append(L"\n");
  append(L"  var o = e.getOffending();\n");
  append(L"  return o >= 0 ? Parser.TOKEN[o] : ");
                                                            #line 1905 "PrintCLike.cpp.template"
                                                                print(nullPtr());
                                                            #line 2756 "PrintCLike.cpp"
  append(L";\n");
  append(L"}\n");
                                                            #line 1908 "PrintCLike.cpp.template"
                                                              }
                                                              else if (isScala())
                                                              {
                                                              }
                                                              else if (isGo())
                                                              {
                                                            #line 2766 "PrintCLike.cpp"
  append(L"\n");
  append(L"func GetOffendingToken(e ParseError) string {\n");
  append(L"  if e.GetOffending() < 0 {\n");
  append(L"    return \"\"\n");
  append(L"  } else {\n");
  append(L"    return token[e.GetOffending()]\n");
  append(L"  }\n");
  append(L"}\n");
                                                            #line 1922 "PrintCLike.cpp.template"
                                                              }
                                                              else if (isPython())
                                                              {
                                                            #line 2779 "PrintCLike.cpp"
  append(L"\n");
  append(L"@staticmethod\n");
  append(L"def getOffendingToken(e):\n");
  append(L"  if e.getOffending() < 0:\n");
  append(L"    return \"\"\n");
  append(L"  else:\n");
  append(L"    return ");
                                                            #line 1931 "PrintCLike.cpp.template"
                                                                print(className.c_str());
                                                            #line 2789 "PrintCLike.cpp"
  append(L".TOKEN[e.getOffending()]\n");
                                                            #line 1933 "PrintCLike.cpp.template"
                                                              }
                                                              else
                                                              {
                                                                openMethod(stringType(), L"static ", L"getOffendingToken", L"ParseException e");
                                                                print(leftBrace());
                                                            #line 2797 "PrintCLike.cpp"
  append(L"\n");
  append(L"  return e.getOffending() < 0 ? ");
                                                            #line 1939 "PrintCLike.cpp.template"
                                                                print(nullPtr());
                                                            #line 2802 "PrintCLike.cpp"
  append(L" : TOKEN[e.getOffending()];");
                                                            #line 1941 "PrintCLike.cpp.template"
                                                                print(rightBrace());
                                                            #line 2806 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 1943 "PrintCLike.cpp.template"
                                                              }

                                                              if (isJavascript() || isTypescript() || isHaxe())
                                                              {
                                                                openMethod(L"", L"static ", L"getExpectedTokenSet", L"ParseException e");
                                                                print(leftBrace());
                                                            #line 2815 "PrintCLike.cpp"
  append(L"\n");
  append(L"  var expected");
                                                            #line 1950 "PrintCLike.cpp.template"
                                                                if (isTypescript())
                                                                {
                                                            #line 2821 "PrintCLike.cpp"
  append(L": string[]");
                                                            #line 1952 "PrintCLike.cpp.template"
                                                                }
                                                            #line 2825 "PrintCLike.cpp"
  append(L";\n");
  append(L"  if (e.getExpected() < 0)\n");
  append(L"  {\n");
  append(L"    expected = ");
                                                            #line 1956 "PrintCLike.cpp.template"
                                                                print(staticPrefix());
                                                            #line 2832 "PrintCLike.cpp"
  append(L"getTokenSet(- e.getState());\n");
  append(L"  }\n");
  append(L"  else\n");
  append(L"  {\n");
  append(L"    expected = [");
                                                            #line 1961 "PrintCLike.cpp.template"
                                                                print(staticPrefix());
                                                                print(isGo() ? L"token" : L"TOKEN");
                                                            #line 2841 "PrintCLike.cpp"
  append(L"[e.getExpected()]];\n");
  append(L"  }\n");
  append(L"  return expected;\n");
  append(L"}");
                                                            #line 1966 "PrintCLike.cpp.template"
                                                                if (! isTypescript())
                                                                {
                                                            #line 2849 "PrintCLike.cpp"
  append(L";");
                                                            #line 1968 "PrintCLike.cpp.template"
                                                                }
                                                            #line 2853 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 1970 "PrintCLike.cpp.template"
                                                                if (isHaxe())
                                                                {
                                                            #line 2858 "PrintCLike.cpp"
  append(L"\n");
  append(L"public function getErrorMessage(e: ParseException): String");
                                                            #line 1973 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                                  openMethod(stringType(), L"static ", L"getErrorMessage", L"ParseException e");
                                                                }
                                                                print(leftBrace());
                                                            #line 2868 "PrintCLike.cpp"
  append(L"\n");
  append(L"  var message = e.getMessage();");
                                                            #line 1980 "PrintCLike.cpp.template"
                                                                if (useGlr)
                                                                {
                                                                  increaseIndent();
                                                            #line 2875 "PrintCLike.cpp"
  append(L"\n");
  append(L"if ");
                                                            #line 1984 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                            #line 2880 "PrintCLike.cpp"
  append(L"e.isAmbiguousInput()");
                                                            #line 1985 "PrintCLike.cpp.template"
                                                                  print(ifRightParen());
                                                                  print(leftBrace());
                                                            #line 2885 "PrintCLike.cpp"
  append(L"\n");
  append(L"  message += \"\\n\"");
                                                            #line 1988 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                            #line 2890 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 1990 "PrintCLike.cpp.template"
                                                                  print(elseWithBraces());
                                                                }
                                                            #line 2895 "PrintCLike.cpp"
  append(L"\n");
  append(L"  var found = ");
                                                            #line 1993 "PrintCLike.cpp.template"
                                                                if (! isHaxe())
                                                                {
                                                                  print(L"this.");
                                                                }
                                                            #line 2903 "PrintCLike.cpp"
  append(L"getOffendingToken(e);\n");
  append(L"  var tokenSet = ");
                                                            #line 1998 "PrintCLike.cpp.template"
                                                                if (! isHaxe())
                                                                {
                                                                  print(L"this.");
                                                                }
                                                            #line 2911 "PrintCLike.cpp"
  append(L"getExpectedTokenSet(e);\n");
  append(L"  var size = e.getEnd() - e.getBegin();\n");
  append(L"  message += (found == null ? \"\" : \", found \" + found)\n");
  append(L"          + \"\\nwhile expecting \"\n");
  append(L"          + (tokenSet.length == 1 ? tokenSet[0] : (\"[\" + tokenSet.join(\", \") + \"]\"))\n");
  append(L"          + \"\\n\"\n");
  append(L"          + (size == 0 || found != null ? \"\" : \"after successfully scanning \" + size + \" characters beginning \");");
                                                            #line 2009 "PrintCLike.cpp.template"
                                                                if (useGlr)
                                                                {
                                                                  decreaseIndent();
                                                            #line 2923 "PrintCLike.cpp"
  append(L"\n");
  append(L"  }");
                                                            #line 2013 "PrintCLike.cpp.template"
                                                                }
                                                            #line 2928 "PrintCLike.cpp"
  append(L"\n");
  append(L"  var prefix = ");
                                                            #line 2015 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 2933 "PrintCLike.cpp"
  append(L"input.");
                                                            #line 2016 "PrintCLike.cpp.template"
                                                                if (isHaxe())
                                                                {
                                                            #line 2938 "PrintCLike.cpp"
  append(L"getS");
                                                            #line 2018 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 2944 "PrintCLike.cpp"
  append(L"subs");
                                                            #line 2021 "PrintCLike.cpp.template"
                                                                }
                                                            #line 2948 "PrintCLike.cpp"
  append(L"tring(0, e.getBegin());\n");
  append(L"  var lines = prefix.split(\"\\n\");\n");
  append(L"  var line = lines.length;\n");
  append(L"  var column = lines[line - 1].length + 1;\n");
  append(L"  return message\n");
  append(L"       + \"at line \" + line + \", column \" + column + \":\\n...\"\n");
  append(L"       + ");
                                                            #line 2028 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                                if (isHaxe())
                                                                {
                                                            #line 2960 "PrintCLike.cpp"
  append(L"input.getString(e.getBegin(), input.length < e.getBegin() + 64 ? input.length - e.getBegin() : 64");
                                                            #line 2032 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 2966 "PrintCLike.cpp"
  append(L"input.substring(e.getBegin(), ");
                                                            #line 2036 "PrintCLike.cpp.template"
                                        
                                                            #line 2970 "PrintCLike.cpp"
  append(L"Math.min(");
                                                            #line 2036 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 2974 "PrintCLike.cpp"
  append(L"input.length, e.getBegin() + 64)");
                                                            #line 2038 "PrintCLike.cpp.template"
                                                                }
                                                            #line 2978 "PrintCLike.cpp"
  append(L")\n");
  append(L"       + \"...\";\n");
  append(L"}");
                                                            #line 2041 "PrintCLike.cpp.template"
                                                                if (! isTypescript())
                                                                {
                                                            #line 2985 "PrintCLike.cpp"
  append(L";");
                                                            #line 2043 "PrintCLike.cpp.template"
                                                                }
                                                            #line 2989 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 2045 "PrintCLike.cpp.template"
                                                              }
                                                              else if (isJava())
                                                              {
                                                                openMethod(L"String[] ", L"static ", L"getExpectedTokenSet", L"ParseException e");
                                                                print(leftBrace());
                                                            #line 2997 "PrintCLike.cpp"
  append(L"\n");
  append(L"  String[] expected");
                                                            #line 2051 "PrintCLike.cpp.template"
                                                                if (useGlr)
                                                                {
                                                            #line 3003 "PrintCLike.cpp"
  append(L" = {}");
                                                            #line 2053 "PrintCLike.cpp.template"
                                                                }
                                                            #line 3007 "PrintCLike.cpp"
  append(L";\n");
  append(L"  if (e.getExpected() >= 0)\n");
  append(L"  {\n");
  append(L"    expected = new String[]{TOKEN[e.getExpected()]};\n");
  append(L"  }\n");
  append(L"  else");
                                                            #line 2059 "PrintCLike.cpp.template"
                                                                if (useGlr)
                                                                {
                                                            #line 3017 "PrintCLike.cpp"
  append(L" if (! e.isAmbiguousInput())");
                                                            #line 2061 "PrintCLike.cpp.template"
                                                                }
                                                            #line 3021 "PrintCLike.cpp"
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
                                                            #line 2072 "PrintCLike.cpp.template"
                                                                if (useGlr)
                                                                {
                                                            #line 3035 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if ");
                                                            #line 2075 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                            #line 3040 "PrintCLike.cpp"
  append(L"e.isAmbiguousInput()");
                                                            #line 2076 "PrintCLike.cpp.template"
                                                                  print(ifRightParen());
                                                                  printIndented(1, leftBrace());
                                                            #line 3045 "PrintCLike.cpp"
  append(L"\n");
  append(L"    message += \"\\n\"");
                                                            #line 2079 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                            #line 3050 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 2081 "PrintCLike.cpp.template"
                                                                  printIndented(1, elseWithBraces());
                                                                  increaseIndent();
                                                                }
                                                            #line 3057 "PrintCLike.cpp"
  append(L"\n");
  append(L"  String[] tokenSet = getExpectedTokenSet(e);\n");
  append(L"  String found = getOffendingToken(e);\n");
  append(L"  int size = e.getEnd() - e.getBegin();\n");
  append(L"  message += (found == null ? \"\" : \", found \" + found)\n");
  append(L"          + \"\\nwhile expecting \"\n");
  append(L"          + (tokenSet.length == 1 ? tokenSet[0] : java.util.Arrays.toString(tokenSet))\n");
  append(L"          + \"\\n\"\n");
  append(L"          + (size == 0 || found != null ? \"\" : \"after successfully scanning \" + size + \" characters beginning \");");
                                                            #line 2093 "PrintCLike.cpp.template"
                                                                if (useGlr)
                                                                {
                                                                  decreaseIndent();
                                                            #line 3071 "PrintCLike.cpp"
  append(L"\n");
  append(L"  }");
                                                            #line 2097 "PrintCLike.cpp.template"
                                                                }
                                                            #line 3076 "PrintCLike.cpp"
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
                                                            #line 2107 "PrintCLike.cpp.template"
                                                                if (! interfaceName.empty())
                                                                {
                                                            #line 3091 "PrintCLike.cpp"
  append(L"\n");
  append(L"public void parse()\n");
  append(L"{\n");
  append(L"  parse_");
                                                            #line 2112 "PrintCLike.cpp.template"
                                                                  print(Format::acceptableName<WString>(grammar->startSymbol()->name).c_str());
                                                            #line 3098 "PrintCLike.cpp"
  append(L"();\n");
  append(L"}\n");
                                                            #line 2115 "PrintCLike.cpp.template"
                                                                }
                                                              }
                                                              else if (isCSharp())
                                                              {
                                                                openMethod(L"static String[] ", L"", L"getExpectedTokenSet", L"ParseException e");
                                                                print(leftBrace());
                                                            #line 3108 "PrintCLike.cpp"
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
                                                            #line 2137 "PrintCLike.cpp.template"
                                                                if (useGlr)
                                                                {
                                                            #line 3128 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if (e.isAmbiguousInput())\n");
  append(L"  {\n");
  append(L"    message += \"\\n\";\n");
  append(L"  }\n");
  append(L"  else\n");
  append(L"  {");
                                                            #line 2145 "PrintCLike.cpp.template"
                                                                  increaseIndent();
                                                                }
                                                            #line 3139 "PrintCLike.cpp"
  append(L"\n");
  append(L"  String[] tokenSet = getExpectedTokenSet(e);\n");
  append(L"  String found = getOffendingToken(e);\n");
  append(L"  int size = e.getEnd() - e.getBegin();\n");
  append(L"  message += (found == null ? \"\" : \", found \" + found)\n");
  append(L"          + \"\\nwhile expecting \"\n");
  append(L"          + (tokenSet.Length == 1 ? tokenSet[0] : (\"[\" + String.Join(\", \", tokenSet) + \"]\"))\n");
  append(L"          + \"\\n\"\n");
  append(L"          + (size == 0 || found != null ? \"\" : \"after successfully scanning \" + size + \" characters beginning \");");
                                                            #line 2156 "PrintCLike.cpp.template"
                                                                if (useGlr)
                                                                {
                                                                  decreaseIndent();
                                                            #line 3153 "PrintCLike.cpp"
  append(L"\n");
  append(L"  }");
                                                            #line 2160 "PrintCLike.cpp.template"
                                                                }
                                                            #line 3158 "PrintCLike.cpp"
  append(L"\n");
  append(L"  String prefix = input.Substring(0, e.getBegin());\n");
  append(L"  int line = prefix.Length - prefix.Replace(\"\\n\", \"\").Length + 1;\n");
  append(L"  int column = prefix.Length - prefix.LastIndexOf('\\n');\n");
  append(L"  return message\n");
  append(L"       + \"at line \" + line + \", column \" + column + \":\\n...\"\n");
  append(L"       + input.Substring(e.getBegin(), Math.Min(input.Length, e.getBegin() + 64) - e.getBegin())\n");
  append(L"       + \"...\";\n");
  append(L"}\n");
                                                            #line 2170 "PrintCLike.cpp.template"
                                                                if (! interfaceName.empty())
                                                                {
                                                            #line 3171 "PrintCLike.cpp"
  append(L"\n");
  append(L"public void parse()\n");
  append(L"{\n");
  append(L"  parse_");
                                                            #line 2175 "PrintCLike.cpp.template"
                                                                  print(Format::acceptableName<WString>(grammar->startSymbol()->name).c_str());
                                                            #line 3178 "PrintCLike.cpp"
  append(L"();\n");
  append(L"}\n");
                                                            #line 2178 "PrintCLike.cpp.template"
                                                                }
                                                              }
                                                              else if (isGo())
                                                              {
                                                            #line 3186 "PrintCLike.cpp"
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
                                                            #line 2192 "PrintCLike.cpp.template"
                                                                print(className.c_str());
                                                            #line 3200 "PrintCLike.cpp"
  append(L") GetErrorMessage(e ParseError) string {\n");
  append(L"  message := e.Error()");
                                                            #line 2195 "PrintCLike.cpp.template"
                                                                if (useGlr)
                                                                {
                                                            #line 3206 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if e.IsAmbiguousInput() {\n");
  append(L"    message += \"\\n\"\n");
  append(L"  } else {");
                                                            #line 2200 "PrintCLike.cpp.template"
                                                                  increaseIndent();
                                                                }
                                                            #line 3214 "PrintCLike.cpp"
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
                                                            #line 2228 "PrintCLike.cpp.template"
                                                                if (useGlr)
                                                                {
                                                                  decreaseIndent();
                                                            #line 3246 "PrintCLike.cpp"
  append(L"\n");
  append(L"  }");
                                                            #line 2232 "PrintCLike.cpp.template"
                                                                }
                                                            #line 3251 "PrintCLike.cpp"
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
                                                            #line 2257 "PrintCLike.cpp.template"
                                                                if (! interfaceName.empty())
                                                                {
                                                            #line 3279 "PrintCLike.cpp"
  append(L"\n");
  append(L"public void parse()\n");
  append(L"{\n");
  append(L"  parse_");
                                                            #line 2262 "PrintCLike.cpp.template"
                                                                  print(Format::acceptableName<WString>(grammar->startSymbol()->name).c_str());
                                                            #line 3286 "PrintCLike.cpp"
  append(L"();\n");
  append(L"}\n");
                                                            #line 2265 "PrintCLike.cpp.template"
                                                                }
                                                              }
                                                              else if (isPython())
                                                              {
                                                            #line 3294 "PrintCLike.cpp"
  append(L"\n");
  append(L"@staticmethod\n");
  append(L"def getExpectedTokenSet(e):\n");
  append(L"  if e.expected < 0:\n");
  append(L"    return ");
                                                            #line 2273 "PrintCLike.cpp.template"
                                                                print(className.c_str());
                                                            #line 3302 "PrintCLike.cpp"
  append(L".getTokenSet(- e.state)\n");
  append(L"  else:\n");
  append(L"    return [");
                                                            #line 2276 "PrintCLike.cpp.template"
                                                                print(className.c_str());
                                                            #line 3308 "PrintCLike.cpp"
  append(L".TOKEN[e.expected]]\n");
  append(L"\n");
  append(L"def getErrorMessage(self, e):\n");
  append(L"  message = e.error()");
                                                            #line 2280 "PrintCLike.cpp.template"
                                                                if (useGlr)
                                                                {
                                                            #line 3316 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if e.isAmbiguousInput():\n");
  append(L"    message += \"\\n\"\n");
  append(L"  else:");
                                                            #line 2285 "PrintCLike.cpp.template"
                                                                  increaseIndent();
                                                                }
                                                            #line 3324 "PrintCLike.cpp"
  append(L"\n");
  append(L"  found = ");
                                                            #line 2288 "PrintCLike.cpp.template"
                                                                print(className.c_str());
                                                            #line 3329 "PrintCLike.cpp"
  append(L".getOffendingToken(e)\n");
  append(L"  if found != \"\":\n");
  append(L"    message += \", found \"\n");
  append(L"    message += found\n");
  append(L"  expected = ");
                                                            #line 2293 "PrintCLike.cpp.template"
                                                                print(className.c_str());
                                                            #line 3337 "PrintCLike.cpp"
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
                                                            #line 2310 "PrintCLike.cpp.template"
                                                                if (useGlr)
                                                                {
                                                                  decreaseIndent();
                                                                }
                                                            #line 3360 "PrintCLike.cpp"
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
                                                            #line 2334 "PrintCLike.cpp.template"
                                                                if (! interfaceName.empty())
                                                                {
                                                            #line 3384 "PrintCLike.cpp"
  append(L"\n");
  append(L"public void parse()\n");
  append(L"{\n");
  append(L"  parse_");
                                                            #line 2339 "PrintCLike.cpp.template"
                                                                  print(Format::acceptableName<WString>(grammar->startSymbol()->name).c_str());
                                                            #line 3391 "PrintCLike.cpp"
  append(L"();\n");
  append(L"}\n");
                                                            #line 2342 "PrintCLike.cpp.template"
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
                                                            #line 3407 "PrintCLike.cpp"
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
                                                            #line 2365 "PrintCLike.cpp.template"
                                                                print(isGo() ? L"token" : L"TOKEN");
                                                            #line 3422 "PrintCLike.cpp"
  append(L"[e.expected];\n");
  append(L"    set[1] = 0;\n");
  append(L"  }\n");
  append(L"}\n");
  append(L"\n");
  append(L"static std::");
                                                            #line 2371 "PrintCLike.cpp.template"
                                                                if (stringIntroducer()[0]) append(L"w");
                                                            #line 3431 "PrintCLike.cpp"
  append(L"string to_");
                                                            #line 2372 "PrintCLike.cpp.template"
                                                                if (stringIntroducer()[0]) append(L"w");
                                                            #line 3435 "PrintCLike.cpp"
  append(L"string(int i)\n");
  append(L"{\n");
  append(L"  const ");
                                                            #line 2375 "PrintCLike.cpp.template"
                                                                if (stringIntroducer()[0]) append(L"w");
                                                            #line 3441 "PrintCLike.cpp"
  append(L"char");
                                                            #line 2376 "PrintCLike.cpp.template"
                                                                if (stringIntroducer()[0]) append(L"_t");
                                                            #line 3445 "PrintCLike.cpp"
  append(L" *sign = i < 0 ? ");
                                                            #line 2377 "PrintCLike.cpp.template"
                                                                append(stringIntroducer());
                                                            #line 3449 "PrintCLike.cpp"
  append(L"\"-\" : ");
                                                            #line 2378 "PrintCLike.cpp.template"
                                                                append(stringIntroducer());
                                                            #line 3453 "PrintCLike.cpp"
  append(L"\"\";\n");
  append(L"  std::");
                                                            #line 2380 "PrintCLike.cpp.template"
                                                                if (stringIntroducer()[0]) append(L"w");
                                                            #line 3458 "PrintCLike.cpp"
  append(L"string a;\n");
  append(L"  do\n");
  append(L"  {\n");
  append(L"    a += ");
                                                            #line 2384 "PrintCLike.cpp.template"
                                                                append(stringIntroducer());
                                                            #line 3465 "PrintCLike.cpp"
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
                                                            #line 2394 "PrintCLike.cpp.template"
                                                                if (stringIntroducer()[0]) append(L"w");
                                                            #line 3478 "PrintCLike.cpp"
  append(L"string getErrorMessage(const ParseException &e)\n");
  append(L"{\n");
  append(L"  std::");
                                                            #line 2397 "PrintCLike.cpp.template"
                                                                if (stringIntroducer()[0]) append(L"w");
                                                            #line 3484 "PrintCLike.cpp"
  append(L"string message(e.getMessage());");
                                                            #line 2398 "PrintCLike.cpp.template"
                                                                if (useGlr)
                                                                {
                                                            #line 3489 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if (e.isAmbiguousInput())\n");
  append(L"  {\n");
  append(L"    message += ");
                                                            #line 2403 "PrintCLike.cpp.template"
                                                                  print(stringIntroducer());
                                                            #line 3496 "PrintCLike.cpp"
  append(L"\"\\n\";\n");
  append(L"  }\n");
  append(L"  else\n");
  append(L"  {");
                                                            #line 2407 "PrintCLike.cpp.template"
                                                                  increaseIndent();
                                                                }
                                                            #line 3504 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 2410 "PrintCLike.cpp.template"
                                                                print(stringType());
                                                            #line 3509 "PrintCLike.cpp"
  append(L"found = getOffendingToken(e);\n");
  append(L"  if (found != 0)\n");
  append(L"  {\n");
  append(L"    message += ");
                                                            #line 2414 "PrintCLike.cpp.template"
                                                                print(stringIntroducer());
                                                            #line 3516 "PrintCLike.cpp"
  append(L"\", found \";\n");
  append(L"    message += found;\n");
  append(L"  }\n");
  append(L"  ");
                                                            #line 2418 "PrintCLike.cpp.template"
                                                                print(stringType());
                                                            #line 3523 "PrintCLike.cpp"
  append(L"expected[64];\n");
  append(L"  getExpectedTokenSet(e, expected, sizeof expected / sizeof *expected);\n");
  append(L"  message += ");
                                                            #line 2421 "PrintCLike.cpp.template"
                                                                print(stringIntroducer());
                                                            #line 3529 "PrintCLike.cpp"
  append(L"\"\\nwhile expecting \";\n");
  append(L"  ");
                                                            #line 2423 "PrintCLike.cpp.template"
                                                                print(stringType());
                                                            #line 3534 "PrintCLike.cpp"
  append(L"delimiter(expected[1] ? ");
                                                            #line 2424 "PrintCLike.cpp.template"
                                                                print(stringIntroducer());
                                                            #line 3538 "PrintCLike.cpp"
  append(L"\"[\" : ");
                                                            #line 2425 "PrintCLike.cpp.template"
                                                                print(stringIntroducer());
                                                            #line 3542 "PrintCLike.cpp"
  append(L"\"\");\n");
  append(L"  for (");
                                                            #line 2427 "PrintCLike.cpp.template"
                                                                print(stringType());
                                                            #line 3547 "PrintCLike.cpp"
  append(L"*x = expected; *x; ++x)\n");
  append(L"  {\n");
  append(L"    message += delimiter;\n");
  append(L"    message += *x;\n");
  append(L"    delimiter = ");
                                                            #line 2432 "PrintCLike.cpp.template"
                                                                print(stringIntroducer());
                                                            #line 3555 "PrintCLike.cpp"
  append(L"\", \";\n");
  append(L"  }\n");
  append(L"  message += expected[1] ? ");
                                                            #line 2435 "PrintCLike.cpp.template"
                                                                print(stringIntroducer());
                                                            #line 3561 "PrintCLike.cpp"
  append(L"\"]\\n\" : ");
                                                            #line 2436 "PrintCLike.cpp.template"
                                                                print(stringIntroducer());
                                                            #line 3565 "PrintCLike.cpp"
  append(L"\"\\n\";\n");
  append(L"  int size = e.getEnd() - e.getBegin();\n");
  append(L"  if (size != 0 && found == 0)\n");
  append(L"  {\n");
  append(L"    message += ");
                                                            #line 2441 "PrintCLike.cpp.template"
                                                                print(stringIntroducer());
                                                            #line 3573 "PrintCLike.cpp"
  append(L"\"after successfully scanning \";\n");
  append(L"    message += to_");
                                                            #line 2443 "PrintCLike.cpp.template"
                                                                if (stringIntroducer()[0]) append(L"w");
                                                            #line 3578 "PrintCLike.cpp"
  append(L"string(size);\n");
  append(L"    message += ");
                                                            #line 2445 "PrintCLike.cpp.template"
                                                                print(stringIntroducer());
                                                            #line 3583 "PrintCLike.cpp"
  append(L"\" characters beginning \";\n");
  append(L"  }");
                                                            #line 2447 "PrintCLike.cpp.template"
                                                                if (useGlr)
                                                                {
                                                                  decreaseIndent();
                                                            #line 3590 "PrintCLike.cpp"
  append(L"\n");
  append(L"  }");
                                                            #line 2451 "PrintCLike.cpp.template"
                                                                }
                                                            #line 3595 "PrintCLike.cpp"
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
                                                            #line 2467 "PrintCLike.cpp.template"
                                                                print(stringIntroducer());
                                                            #line 3614 "PrintCLike.cpp"
  append(L"\"at line \";\n");
  append(L"  message += to_");
                                                            #line 2469 "PrintCLike.cpp.template"
                                                              if (stringIntroducer()[0]) append(L"w");
                                                            #line 3619 "PrintCLike.cpp"
  append(L"string(line);\n");
  append(L"  message += ");
                                                            #line 2471 "PrintCLike.cpp.template"
                                                              print(stringIntroducer());
                                                            #line 3624 "PrintCLike.cpp"
  append(L"\", column \";\n");
  append(L"  message += to_");
                                                            #line 2473 "PrintCLike.cpp.template"
                                                              if (stringIntroducer()[0]) append(L"w");
                                                            #line 3629 "PrintCLike.cpp"
  append(L"string(column);\n");
  append(L"  message += ");
                                                            #line 2475 "PrintCLike.cpp.template"
                                                                print(stringIntroducer());
                                                            #line 3634 "PrintCLike.cpp"
  append(L"\":\\n...\";\n");
  append(L"  ");
                                                            #line 2477 "PrintCLike.cpp.template"
                                                                print(stringType());
                                                            #line 3639 "PrintCLike.cpp"
  append(L"w = input + e.getBegin();\n");
  append(L"  for (int i = 0; i < 64 && *w; ++i)\n");
  append(L"  {\n");
  append(L"    message += *w++;\n");
  append(L"  }\n");
  append(L"  message += ");
                                                            #line 2483 "PrintCLike.cpp.template"
                                                                print(stringIntroducer());
                                                            #line 3648 "PrintCLike.cpp"
  append(L"\"...\";\n");
  append(L"  return message;\n");
  append(L"}\n");
                                                            #line 2487 "PrintCLike.cpp.template"
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
                                                            #line 3677 "PrintCLike.cpp"
  append(L"\n");
  append(L"  fprintf(stderr, \"  <%s %snonterminal=\\\"%s\\\"\", ");
                                                            #line 2512 "PrintCLike.cpp.template"
                                                                  if (stringIntroducer()[0])
                                                                  {
                                                            #line 3683 "PrintCLike.cpp"
  append(L"Utf8Encoder::encode(");
                                                            #line 2514 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 3687 "PrintCLike.cpp"
  append(L"method");
                                                            #line 2515 "PrintCLike.cpp.template"
                                                                  if (stringIntroducer()[0])
                                                                  {
                                                            #line 3692 "PrintCLike.cpp"
  append(L").c_str()");
                                                            #line 2517 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 3696 "PrintCLike.cpp"
  append(L", ");
                                                            #line 2518 "PrintCLike.cpp.template"
                                                                  if (stringIntroducer()[0])
                                                                  {
                                                            #line 3701 "PrintCLike.cpp"
  append(L"Utf8Encoder::encode(");
                                                            #line 2520 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 3705 "PrintCLike.cpp"
  append(L"occasion");
                                                            #line 2521 "PrintCLike.cpp.template"
                                                                  if (stringIntroducer()[0])
                                                                  {
                                                            #line 3710 "PrintCLike.cpp"
  append(L").c_str()");
                                                            #line 2523 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 3714 "PrintCLike.cpp"
  append(L", ");
                                                            #line 2524 "PrintCLike.cpp.template"
                                                                  if (stringIntroducer()[0])
                                                                  {
                                                            #line 3719 "PrintCLike.cpp"
  append(L"Utf8Encoder::encode(");
                                                            #line 2526 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 3723 "PrintCLike.cpp"
  append(L"name");
                                                            #line 2527 "PrintCLike.cpp.template"
                                                                  if (stringIntroducer()[0])
                                                                  {
                                                            #line 3728 "PrintCLike.cpp"
  append(L").c_str()");
                                                            #line 2529 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 3732 "PrintCLike.cpp"
  append(L");\n");
  append(L"  if (l1 != 0)\n");
  append(L"    fprintf(stderr, \" input=\\\"%s\\\"\", ");
                                                            #line 2532 "PrintCLike.cpp.template"
                                                                  if (stringIntroducer()[0])
                                                                  {
                                                            #line 3739 "PrintCLike.cpp"
  append(L"Utf8Encoder::encode(");
                                                            #line 2534 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 3743 "PrintCLike.cpp"
  append(L"xmlEscape(lookaheadString().c_str(), 0).c_str()");
                                                            #line 2536 "PrintCLike.cpp.template"
                                                                  if (stringIntroducer()[0])
                                                                  {
                                                            #line 3748 "PrintCLike.cpp"
  append(L").c_str()");
                                                            #line 2538 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 3752 "PrintCLike.cpp"
  append(L");\n");
  append(L"  fprintf(stderr, \"/>\\n\");");
                                                            #line 2540 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                                  if (isHaxe())
                                                                  {
                                                            #line 3761 "PrintCLike.cpp"
  append(L"\n");
  append(L"  trace(");
                                                            #line 2546 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                                    if (isGo())
                                                                    {
                                                            #line 3770 "PrintCLike.cpp"
  append(L"\n");
  append(L"  var inputAttr string\n");
  append(L"  if (this.l1 == 0) {\n");
  append(L"    inputAttr = \"\"\n");
  append(L"  } else {\n");
  append(L"    inputAttr = \" input=\\\"\" + xmlEscape(this.lookaheadString()) + \"\\\"\"\n");
  append(L"  }");
                                                            #line 2557 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 3780 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 2559 "PrintCLike.cpp.template"
                                                                    print(writeTrace());
                                                                  }
                                                            #line 3786 "PrintCLike.cpp"
  append(L"\"  <\" + method + \" \" + occasion + \"nonterminal=\\\"\" + name + \"\\\"\" + ");
                                                            #line 2562 "PrintCLike.cpp.template"
                                                                  if (isGo())
                                                                  {
                                                            #line 3791 "PrintCLike.cpp"
  append(L"inputAttr");
                                                            #line 2564 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 3797 "PrintCLike.cpp"
  append(L"(");
                                                            #line 2567 "PrintCLike.cpp.template"
                                                                    if (isScala())
                                                                    {
                                                            #line 3802 "PrintCLike.cpp"
  append(L"if (l1 == 0) \"\" else");
                                                            #line 2569 "PrintCLike.cpp.template"
                                                                    }
                                                                    else if (isPython())
                                                                    {
                                                            #line 3808 "PrintCLike.cpp"
  append(L"\"\" if self.l1 == 0 else");
                                                            #line 2572 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                                      print(thiz());
                                                            #line 3815 "PrintCLike.cpp"
  append(L"l1 == 0 ? \"\" :");
                                                            #line 2576 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 3819 "PrintCLike.cpp"
  append(L" \" input=\\\"\" + ");
                                                            #line 2577 "PrintCLike.cpp.template"
                                                                    print(staticPrefix());
                                                            #line 3823 "PrintCLike.cpp"
  append(L"xmlEscape(");
                                                            #line 2578 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 3827 "PrintCLike.cpp"
  append(L"lookaheadString");
                                                            #line 2579 "PrintCLike.cpp.template"
                                                                    if (! isScala()) print(L"()");
                                                            #line 3831 "PrintCLike.cpp"
  append(L") + \"\\\"\")");
                                                            #line 2580 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 3835 "PrintCLike.cpp"
  append(L" + \"/>");
                                                            #line 2581 "PrintCLike.cpp.template"
                                                                  if (isHaxe()) print(L"\")"); else print(L"\\n\"");
                                                                  print(endWriteTrace());
                                                                  print(semicolon());
                                                                }
                                                                print(rightBrace());
                                                            #line 3843 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 2587 "PrintCLike.cpp.template"
                                                                decreaseIndent();
                                                              }

                                                              if (grammar->automaticSemicolonInsertion)
                                                              {
                                                                if (! isGo())
                                                                  increaseIndent();
                                                                openMethod(boolType(), L"", L"followsLineTerminator", L"");
                                                                print(leftBrace());
                                                                increaseIndent();
                                                            #line 3856 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 2598 "PrintCLike.cpp.template"
                                                                print(intVar());
                                                            #line 3860 "PrintCLike.cpp"
  append(L"i");
                                                            #line 2599 "PrintCLike.cpp.template"
                                                                print(assign());
                                                                print(thiz());
                                                            #line 3865 "PrintCLike.cpp"
  append(L"e0");
                                                            #line 2601 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 3869 "PrintCLike.cpp"
  append(L"\n");
  append(L"if ");
                                                            #line 2603 "PrintCLike.cpp.template"
                                                                print(ifLeftParen());
                                                                print(thiz());
                                                            #line 3875 "PrintCLike.cpp"
  append(L"e0 == ");
                                                            #line 2605 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 3879 "PrintCLike.cpp"
  append(L"b1");
                                                            #line 2606 "PrintCLike.cpp.template"
                                                                print(ifRightParen());
                                                                print(leftBrace());
                                                            #line 3884 "PrintCLike.cpp"
  append(L"\n");
  append(L"  i = ");
                                                            #line 2609 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 3889 "PrintCLike.cpp"
  append(L"b0");
                                                            #line 2610 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                print(rightBrace());
                                                                if (isScala() || isHaxe() || isPython())
                                                                {
                                                            #line 3896 "PrintCLike.cpp"
  append(L"\n");
  append(L"while ");
                                                            #line 2615 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 3903 "PrintCLike.cpp"
  append(L"\n");
  append(L"for ");
                                                            #line 2619 "PrintCLike.cpp.template"
                                                                }
                                                                print(ifLeftParen());
                                                                if (! (isScala() || isHaxe() || isPython()))
                                                                {
                                                            #line 3911 "PrintCLike.cpp"
  append(L"; ");
                                                            #line 2623 "PrintCLike.cpp.template"
                                                                }
                                                            #line 3915 "PrintCLike.cpp"
  append(L"i < ");
                                                            #line 2624 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 3919 "PrintCLike.cpp"
  append(L"b1");
                                                            #line 2625 "PrintCLike.cpp.template"
                                                                if (! (isScala() || isHaxe() || isPython()))
                                                                {
                                                            #line 3924 "PrintCLike.cpp"
  append(L"; i++");
                                                            #line 2627 "PrintCLike.cpp.template"
                                                                }
                                                                print(ifRightParen());
                                                                print(leftBrace());
                                                                increaseIndent();
                                                                if (isGo())
                                                                {
                                                            #line 3933 "PrintCLike.cpp"
  append(L"\n");
  append(L"c, _ := utf8.DecodeRuneInString(this.input[i:])");
                                                            #line 2634 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 3940 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 2638 "PrintCLike.cpp.template"
                                                                  print(intVar());
                                                            #line 3944 "PrintCLike.cpp"
  append(L"c");
                                                            #line 2639 "PrintCLike.cpp.template"
                                                                  print(assign());
                                                                  if (isCpp() || isCSharp() || isPython())
                                                                  {
                                                                    if (isPython())
                                                                    {
                                                            #line 3952 "PrintCLike.cpp"
  append(L"ord(");
                                                            #line 2644 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(thiz());
                                                            #line 3957 "PrintCLike.cpp"
  append(L"input[i]");
                                                            #line 2646 "PrintCLike.cpp.template"
                                                                    if (isPython())
                                                                    {
                                                            #line 3962 "PrintCLike.cpp"
  append(L")");
                                                            #line 2648 "PrintCLike.cpp.template"
                                                                    }
                                                                  }
                                                                  else if (isHaxe())
                                                                  {
                                                            #line 3969 "PrintCLike.cpp"
  append(L"input.get(i)");
                                                            #line 2652 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                                    print(thiz());
                                                            #line 3976 "PrintCLike.cpp"
  append(L"input.char");
                                                            #line 2656 "PrintCLike.cpp.template"
                                                                    if (isTypescript() || isJavascript())
                                                                    {
                                                            #line 3981 "PrintCLike.cpp"
  append(L"Code");
                                                            #line 2658 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 3985 "PrintCLike.cpp"
  append(L"At(i)");
                                                            #line 2659 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(semicolon());
                                                                }
                                                            #line 3991 "PrintCLike.cpp"
  append(L"\n");
  append(L"if ");
                                                            #line 2663 "PrintCLike.cpp.template"
                                                                print(ifLeftParen());
                                                            #line 3996 "PrintCLike.cpp"
  append(L"c == 0xA ");
                                                            #line 2665 "PrintCLike.cpp.template"
                                                                if (isPython())
                                                                {
                                                            #line 4001 "PrintCLike.cpp"
  append(L"or");
                                                            #line 2667 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 4007 "PrintCLike.cpp"
  append(L"||");
                                                            #line 2670 "PrintCLike.cpp.template"
                                                                }
                                                            #line 4011 "PrintCLike.cpp"
  append(L" c == 0xD ");
                                                            #line 2672 "PrintCLike.cpp.template"
                                                                if (isPython())
                                                                {
                                                            #line 4016 "PrintCLike.cpp"
  append(L"or");
                                                            #line 2674 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 4022 "PrintCLike.cpp"
  append(L"||");
                                                            #line 2677 "PrintCLike.cpp.template"
                                                                }
                                                            #line 4026 "PrintCLike.cpp"
  append(L" c == 0x2028 ");
                                                            #line 2679 "PrintCLike.cpp.template"
                                                                if (isPython())
                                                                {
                                                            #line 4031 "PrintCLike.cpp"
  append(L"or");
                                                            #line 2681 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 4037 "PrintCLike.cpp"
  append(L"||");
                                                            #line 2684 "PrintCLike.cpp.template"
                                                                }
                                                            #line 4041 "PrintCLike.cpp"
  append(L" c == 0x2029");
                                                            #line 2685 "PrintCLike.cpp.template"
                                                                print(ifRightParen());
                                                                print(leftBrace());
                                                            #line 4046 "PrintCLike.cpp"
  append(L"\n");
  append(L"  return ");
                                                            #line 2688 "PrintCLike.cpp.template"
                                                                if (isPython())
                                                                {
                                                            #line 4052 "PrintCLike.cpp"
  append(L"T");
                                                            #line 2690 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 4058 "PrintCLike.cpp"
  append(L"t");
                                                            #line 2693 "PrintCLike.cpp.template"
                                                                }
                                                            #line 4062 "PrintCLike.cpp"
  append(L"rue");
                                                            #line 2694 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                print(rightBrace());
                                                                if (isScala() || isPython())
                                                                {
                                                            #line 4069 "PrintCLike.cpp"
  append(L"\n");
  append(L"i += 1");
                                                            #line 2700 "PrintCLike.cpp.template"
                                                                }
                                                                else if (isHaxe())
                                                                {
                                                            #line 4076 "PrintCLike.cpp"
  append(L"\n");
  append(L"++i;");
                                                            #line 2704 "PrintCLike.cpp.template"
                                                                }

                                                                decreaseIndent();
                                                                print(rightBrace());
                                                            #line 4084 "PrintCLike.cpp"
  append(L"\n");
  append(L"return ");
                                                            #line 2709 "PrintCLike.cpp.template"
                                                                if (isPython())
                                                                {
                                                            #line 4090 "PrintCLike.cpp"
  append(L"F");
                                                            #line 2711 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 4096 "PrintCLike.cpp"
  append(L"f");
                                                            #line 2714 "PrintCLike.cpp.template"
                                                                }
                                                            #line 4100 "PrintCLike.cpp"
  append(L"alse");
                                                            #line 2715 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                decreaseIndent();
                                                                print(rightBrace());
                                                            #line 4106 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 2719 "PrintCLike.cpp.template"
                                                                if (! isGo())
                                                                  decreaseIndent();
                                                              }

                                                              if (isScala())
                                                              {
                                                            #line 4115 "PrintCLike.cpp"
  append(L"\n");
  append(L"  def getErrorMessage(e: ");
                                                            #line 2726 "PrintCLike.cpp.template"
                                                                print(className.c_str());
                                                            #line 4120 "PrintCLike.cpp"
  append(L".ParseException) = {\n");
  append(L"    var message = e.getMessage");
                                                            #line 2728 "PrintCLike.cpp.template"
                                                                if (useGlr)
                                                                {
                                                            #line 4126 "PrintCLike.cpp"
  append(L"\n");
  append(L"    if (e.isAmbiguousInput)\n");
  append(L"      message += \"\\n\"\n");
  append(L"    else {");
                                                            #line 2733 "PrintCLike.cpp.template"
                                                                  increaseIndent();
                                                                }
                                                            #line 4134 "PrintCLike.cpp"
  append(L"\n");
  append(L"    val tokenSet = ");
                                                            #line 2736 "PrintCLike.cpp.template"
                                                                print(className.c_str());
                                                            #line 4139 "PrintCLike.cpp"
  append(L".getExpectedTokenSet(e)\n");
  append(L"    val found = ");
                                                            #line 2738 "PrintCLike.cpp.template"
                                                                print(className.c_str());
                                                            #line 4144 "PrintCLike.cpp"
  append(L".getOffendingToken(e)\n");
  append(L"    val size = e.end - e.begin\n");
  append(L"    message += (if (found == null) \"\" else \", found \" + found) + \"\\nwhile expecting \" +\n");
  append(L"      (if (tokenSet.length == 1) tokenSet(0) else \"[\" + (tokenSet mkString \", \") + \"]\") + \"\\n\" +\n");
  append(L"      (if (size == 0 || found != null) \"\" else \"after successfully scanning \" + size + \" characters beginning \")");
                                                            #line 2744 "PrintCLike.cpp.template"
                                                                if (useGlr)
                                                                {
                                                            #line 4153 "PrintCLike.cpp"
  append(L"\n");
  append(L"    }");
                                                            #line 2747 "PrintCLike.cpp.template"
                                                                  decreaseIndent();
                                                                }
                                                            #line 4159 "PrintCLike.cpp"
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
                                                            #line 2757 "PrintCLike.cpp.template"
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
                                                            #line 4207 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 2794 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 4212 "PrintCLike.cpp"
  append(L"top += ");
                                                            #line 2795 "PrintCLike.cpp.template"
                                                                  if (tree)
                                                                  {
                                                            #line 4217 "PrintCLike.cpp"
  append(L"3");
                                                            #line 2797 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 4223 "PrintCLike.cpp"
  append(L"2");
                                                            #line 2800 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(semicolon());
                                                                  if (isJava())
                                                                  {
                                                            #line 4230 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if (top >= iStack.length)\n");
  append(L"  {\n");
  append(L"    iStack = Arrays.copyOf(iStack, iStack.length << 1);\n");
  append(L"  }");
                                                            #line 2808 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isCSharp())
                                                                  {
                                                            #line 4240 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if (top >= iStack.Length)\n");
  append(L"  {\n");
  append(L"    Array.Resize(ref iStack, iStack.Length << 1);\n");
  append(L"  }");
                                                            #line 2815 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isCpp())
                                                                  {
                                                            #line 4250 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if (top >= (int) iStack.size())\n");
  append(L"    iStack.resize(iStack.size() == 0 ? ");
                                                            #line 2820 "PrintCLike.cpp.template"
                                                                    print(tree ? L"192" : L"128");
                                                            #line 4256 "PrintCLike.cpp"
  append(L" : iStack.size() << 1);");
                                                            #line 2822 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isScala())
                                                                  {
                                                            #line 4262 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if (top >= iStack.size) {\n");
  append(L"    val newStack = new Array[Int](iStack.size << 1)\n");
  append(L"    Array.copy(iStack, 0, newStack, 0, iStack.size)\n");
  append(L"    iStack = newStack\n");
  append(L"  }");
                                                            #line 2830 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isGo())
                                                                  {
                                                            #line 4273 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if this.top >= len(this.iStack) {\n");
  append(L"    this.iStack = append(this.iStack, this.iStack...)\n");
  append(L"  }");
                                                            #line 2836 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isPython())
                                                                  {
                                                            #line 4282 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if self.top >= len(self.iStack):\n");
  append(L"    self.iStack.extend([0 for _ in range(len(self.iStack))])");
                                                            #line 2841 "PrintCLike.cpp.template"
                                                                  }
                                                                  if (tree)
                                                                  {
                                                            #line 4290 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 2845 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 4295 "PrintCLike.cpp"
  append(L"iStack");
                                                            #line 2846 "PrintCLike.cpp.template"
                                                                    print(leftbracket());
                                                                    print(thiz());
                                                            #line 4300 "PrintCLike.cpp"
  append(L"top - 2");
                                                            #line 2848 "PrintCLike.cpp.template"
                                                                    print(rightbracket());
                                                            #line 4304 "PrintCLike.cpp"
  append(L" = begin");
                                                            #line 2849 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                  }
                                                            #line 4309 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 2852 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 4314 "PrintCLike.cpp"
  append(L"iStack");
                                                            #line 2853 "PrintCLike.cpp.template"
                                                                  print(leftbracket());
                                                                  print(thiz());
                                                            #line 4319 "PrintCLike.cpp"
  append(L"top - 1");
                                                            #line 2855 "PrintCLike.cpp.template"
                                                                  print(rightbracket());
                                                            #line 4323 "PrintCLike.cpp"
  append(L" = state");
                                                            #line 2856 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                            #line 4327 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 2858 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 4332 "PrintCLike.cpp"
  append(L"iStack");
                                                            #line 2859 "PrintCLike.cpp.template"
                                                                  print(leftbracket());
                                                                  print(thiz());
                                                            #line 4337 "PrintCLike.cpp"
  append(L"top");
                                                            #line 2861 "PrintCLike.cpp.template"
                                                                  print(rightbracket());
                                                            #line 4341 "PrintCLike.cpp"
  append(L" = lookback");
                                                            #line 2862 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                  print(rightBrace());
                                                            #line 4346 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 2865 "PrintCLike.cpp.template"
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
                                                            #line 4365 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 2882 "PrintCLike.cpp.template"
                                                                  print(intVar());
                                                            #line 4369 "PrintCLike.cpp"
  append(L"state");
                                                            #line 2883 "PrintCLike.cpp.template"
                                                                  print(assign());
                                                            #line 4373 "PrintCLike.cpp"
  append(L"initialState");
                                                            #line 2884 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                  if (tree || useGlr)
                                                                  {
                                                            #line 4379 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 2888 "PrintCLike.cpp.template"
                                                                    print(intVar());
                                                            #line 4383 "PrintCLike.cpp"
  append(L"bw");
                                                            #line 2889 "PrintCLike.cpp.template"
                                                                    print(assign());
                                                                    print(thiz());
                                                            #line 4388 "PrintCLike.cpp"
  append(L"e0");
                                                            #line 2891 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 4392 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 2893 "PrintCLike.cpp.template"
                                                                    print(intVar());
                                                            #line 4396 "PrintCLike.cpp"
  append(L"bs");
                                                            #line 2894 "PrintCLike.cpp.template"
                                                                    print(assign());
                                                                    print(thiz());
                                                            #line 4401 "PrintCLike.cpp"
  append(L"e0");
                                                            #line 2896 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                  }
                                                                  if (tree)
                                                                  {
                                                            #line 4408 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 2901 "PrintCLike.cpp.template"
                                                                    print(intVar());
                                                            #line 4412 "PrintCLike.cpp"
  append(L"es");
                                                            #line 2902 "PrintCLike.cpp.template"
                                                                    print(assign());
                                                                    print(thiz());
                                                            #line 4417 "PrintCLike.cpp"
  append(L"e0");
                                                            #line 2904 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 4421 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 2906 "PrintCLike.cpp.template"
                                                                    print(intVar());
                                                            #line 4425 "PrintCLike.cpp"
  append(L"t");
                                                            #line 2907 "PrintCLike.cpp.template"
                                                                    print(assign());
                                                                    print(thiz());
                                                            #line 4430 "PrintCLike.cpp"
  append(L"top");
                                                            #line 2909 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                  }
                                                            #line 4435 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 2912 "PrintCLike.cpp.template"
                                                                  print(intVar());
                                                            #line 4439 "PrintCLike.cpp"
  append(L"action");
                                                            #line 2913 "PrintCLike.cpp.template"
                                                                  print(assign());
                                                                  print(thiz());
                                                            #line 4444 "PrintCLike.cpp"
  append(L"predict(state)");
                                                            #line 2915 "PrintCLike.cpp.template"
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
                                                            #line 4458 "PrintCLike.cpp"
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
                                                            #line 2939 "PrintCLike.cpp.template"
                                                                }
                                                                if (useGlr)
                                                                {
                                                            #line 4475 "PrintCLike.cpp"
  append(L"\n");
  append(L"  var thread: ");
                                                            #line 2943 "PrintCLike.cpp.template"
                                                                  print(className.c_str());
                                                            #line 4480 "PrintCLike.cpp"
  append(L".ParsingThread = null");
                                                            #line 2944 "PrintCLike.cpp.template"
                                                                }
                                                            #line 4484 "PrintCLike.cpp"
  append(L"\n");
  append(L"  var input: String = null");
                                                            #line 2946 "PrintCLike.cpp.template"
                                                                if (! noLexer)
                                                                {
                                                            #line 4490 "PrintCLike.cpp"
  append(L"\n");
  append(L"  var size = 0");
                                                            #line 2949 "PrintCLike.cpp.template"
                                                                }
                                                                if (tree && useGlr)
                                                                {
                                                            #line 4497 "PrintCLike.cpp"
  append(L"\n");
  append(L"  var eventHandler: ");
                                                            #line 2953 "PrintCLike.cpp.template"
                                                                  print(className.c_str());
                                                            #line 4502 "PrintCLike.cpp"
  append(L".BottomUpEventHandler = null");
                                                            #line 2954 "PrintCLike.cpp.template"
                                                                }
                                                                if (noLexer)
                                                                {
                                                            #line 4508 "PrintCLike.cpp"
  append(L"\n");
  append(L"  var lexer: Lexer = null\n");
  append(L"  var token = new Token");
                                                            #line 2959 "PrintCLike.cpp.template"
                                                                }
                                                                if (useGlr)
                                                                {
                                                            #line 4516 "PrintCLike.cpp"
  append(L"\n");
  append(L"  var maxId = 0");
                                                            #line 2963 "PrintCLike.cpp.template"
                                                                }
                                                                if (trace)
                                                                {
                                                            #line 4523 "PrintCLike.cpp"
  append(L"\n");
  append(L"  var err: Writer = new OutputStreamWriter(System.err, \"UTF-8\")");
                                                            #line 2968 "PrintCLike.cpp.template"
                                                                }
                                                            #line 4528 "PrintCLike.cpp"
  append(L"\n");
  append(L"}\n");
  append(L"\n");
  append(L"object ");
                                                            #line 2972 "PrintCLike.cpp.template"
                                                                print(className.c_str());
                                                            #line 4535 "PrintCLike.cpp"
  append(L" {\n");
  append(L"\n");
  append(L"  def getOffendingToken(e: ParseException) = {\n");
  append(L"    if (e.offending < 0) null else TOKEN(e.offending)\n");
  append(L"  }\n");
                                                            #line 2979 "PrintCLike.cpp.template"
                                                              }
                                                            }

                                                            void PrintCLike::printThreadBody1()
                                                            {
                                                              Trace("PrintCLike::printThreadBody1");

                                                              if (isLrParser)
                                                              {
                                                            #line 4551 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 2989 "PrintCLike.cpp.template"
                                                                print(intVar());
                                                            #line 4555 "PrintCLike.cpp"
  append(L"nonterminalId");
                                                            #line 2990 "PrintCLike.cpp.template"
                                                                print(assign());
                                                            #line 4559 "PrintCLike.cpp"
  append(L"-1");
                                                            #line 2991 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                if (isHaxe() || isScala() || isPython())
                                                                {
                                                            #line 4565 "PrintCLike.cpp"
  append(L"\n");
  append(L"while ");
                                                            #line 2995 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                                  if (isPython())
                                                                  {
                                                            #line 4572 "PrintCLike.cpp"
  append(L"T");
                                                            #line 2998 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 4578 "PrintCLike.cpp"
  append(L"t");
                                                            #line 3001 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 4582 "PrintCLike.cpp"
  append(L"rue");
                                                            #line 3002 "PrintCLike.cpp.template"
                                                                  print(ifRightParen());
                                                                }
                                                                else if (isGo())
                                                                {
                                                            #line 4589 "PrintCLike.cpp"
  append(L"\n");
  append(L"for");
                                                            #line 3007 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 4596 "PrintCLike.cpp"
  append(L"\n");
  append(L"for (;;)");
                                                            #line 3011 "PrintCLike.cpp.template"
                                                                }
                                                                print(leftBrace());
                                                                increaseIndent();
                                                                if (trace)
                                                                {
                                                                  if (isCpp())
                                                                  {
                                                            #line 4607 "PrintCLike.cpp"
  append(L"\n");
  append(L"fprintf(stderr, \"  <parse ");
                                                            #line 3019 "PrintCLike.cpp.template"
                                                                    if (useGlr)
                                                                    {
                                                            #line 4613 "PrintCLike.cpp"
  append(L"thread=\\\"%d\\\" offset=\\\"%d\\\" ");
                                                            #line 3021 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 4617 "PrintCLike.cpp"
  append(L"state=\\\"%d\\\" input=\\\"%s%s%s\\\" action=\\\"\",");
                                                            #line 3023 "PrintCLike.cpp.template"
                                                                    if (useGlr)
                                                                    {
                                                            #line 4622 "PrintCLike.cpp"
  append(L"\n");
  append(L"  id,\n");
  append(L"  e0,");
                                                            #line 3027 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 4628 "PrintCLike.cpp"
  append(L"\n");
  append(L"  state,\n");
  append(L"  nonterminalId < 0 ? \"\" : ");
                                                            #line 3030 "PrintCLike.cpp.template"
                                                                    if (stringIntroducer()[0])
                                                                    {
                                                            #line 4635 "PrintCLike.cpp"
  append(L"Utf8Encoder::encode(");
                                                            #line 3032 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 4639 "PrintCLike.cpp"
  append(L"xmlEscape(");
                                                            #line 3033 "PrintCLike.cpp.template"
                                                                    print(isGo() ? L"nonterminal" : L"NONTERMINAL");
                                                            #line 4643 "PrintCLike.cpp"
  append(L"[nonterminalId], 0).c_str()");
                                                            #line 3035 "PrintCLike.cpp.template"
                                                                    if (stringIntroducer()[0])
                                                                    {
                                                            #line 4648 "PrintCLike.cpp"
  append(L").c_str()");
                                                            #line 3037 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 4652 "PrintCLike.cpp"
  append(L",\n");
  append(L"  nonterminalId < 0 || l1 <= 0 ? \"\" : \" \",\n");
  append(L"  l1 <= 0 ? \"\" : ");
                                                            #line 3040 "PrintCLike.cpp.template"
                                                                    if (stringIntroducer()[0])
                                                                    {
                                                            #line 4659 "PrintCLike.cpp"
  append(L"Utf8Encoder::encode(");
                                                            #line 3042 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 4663 "PrintCLike.cpp"
  append(L"xmlEscape(lookaheadString().c_str(), 0).c_str()");
                                                            #line 3043 "PrintCLike.cpp.template"
                                                                    if (stringIntroducer()[0])
                                                                    {
                                                            #line 4668 "PrintCLike.cpp"
  append(L").c_str()");
                                                            #line 3045 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 4672 "PrintCLike.cpp"
  append(L");\n");
                                                            #line 3047 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                                    if (isHaxe())
                                                                    {
                                                            #line 4680 "PrintCLike.cpp"
  append(L"\n");
  append(L"var traceLine = ");
                                                            #line 3053 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 4687 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3057 "PrintCLike.cpp.template"
                                                                      print(writeTrace());
                                                                    }
                                                            #line 4692 "PrintCLike.cpp"
  append(L"\"  <parse ");
                                                            #line 3059 "PrintCLike.cpp.template"
                                                                    if (useGlr)
                                                                    {
                                                            #line 4697 "PrintCLike.cpp"
  append(L"thread=\\\"\" + ");
                                                            #line 3061 "PrintCLike.cpp.template"
                                                                      if (isGo())
                                                                      {
                                                            #line 4702 "PrintCLike.cpp"
  append(L"strconv.Itoa(");
                                                            #line 3063 "PrintCLike.cpp.template"
                                                                      }
                                                                      else if (isPython())
                                                                      {
                                                            #line 4708 "PrintCLike.cpp"
  append(L"str(");
                                                            #line 3066 "PrintCLike.cpp.template"
                                                                      }
                                                                      print(thiz());
                                                            #line 4713 "PrintCLike.cpp"
  append(L"id");
                                                            #line 3068 "PrintCLike.cpp.template"
                                                                      if (isGo() || isPython())
                                                                      {
                                                            #line 4718 "PrintCLike.cpp"
  append(L")");
                                                            #line 3070 "PrintCLike.cpp.template"
                                                                      }
                                                            #line 4722 "PrintCLike.cpp"
  append(L" + \"\\\" offset=\\\"\" + ");
                                                            #line 3071 "PrintCLike.cpp.template"
                                                                      if (isGo())
                                                                      {
                                                            #line 4727 "PrintCLike.cpp"
  append(L"strconv.Itoa(");
                                                            #line 3073 "PrintCLike.cpp.template"
                                                                      }
                                                                      else if (isPython())
                                                                      {
                                                            #line 4733 "PrintCLike.cpp"
  append(L"str(");
                                                            #line 3076 "PrintCLike.cpp.template"
                                                                      }
                                                                      print(thiz());
                                                            #line 4738 "PrintCLike.cpp"
  append(L"e0");
                                                            #line 3078 "PrintCLike.cpp.template"
                                                                      if (isGo() || isPython())
                                                                      {
                                                            #line 4743 "PrintCLike.cpp"
  append(L")");
                                                            #line 3080 "PrintCLike.cpp.template"
                                                                      }
                                                            #line 4747 "PrintCLike.cpp"
  append(L" + \"\\\" ");
                                                            #line 3081 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 4751 "PrintCLike.cpp"
  append(L"state=\\\"\" + ");
                                                            #line 3082 "PrintCLike.cpp.template"
                                                                    if (isGo())
                                                                    {
                                                            #line 4756 "PrintCLike.cpp"
  append(L"strconv.Itoa(");
                                                            #line 3084 "PrintCLike.cpp.template"
                                                                    }
                                                                    else if (isPython())
                                                                    {
                                                            #line 4762 "PrintCLike.cpp"
  append(L"str(");
                                                            #line 3087 "PrintCLike.cpp.template"
                                                                    }
                                                                    if (useGlr) print(thiz());
                                                            #line 4767 "PrintCLike.cpp"
  append(L"state");
                                                            #line 3089 "PrintCLike.cpp.template"
                                                                    if (isGo() || isPython())
                                                                    {
                                                            #line 4772 "PrintCLike.cpp"
  append(L")");
                                                            #line 3091 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 4776 "PrintCLike.cpp"
  append(L" + \"\\\" input=\\\"\"");
                                                            #line 3092 "PrintCLike.cpp.template"
                                                                    print(endWriteTrace());
                                                                    print(semicolon());
                                                            #line 4781 "PrintCLike.cpp"
  append(L"\n");
  append(L"if ");
                                                            #line 3096 "PrintCLike.cpp.template"
                                                                    print(ifLeftParen());
                                                            #line 4786 "PrintCLike.cpp"
  append(L"nonterminalId >= 0");
                                                            #line 3097 "PrintCLike.cpp.template"
                                                                    print(ifRightParen());
                                                                    print(leftBrace());
                                                            #line 4791 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3100 "PrintCLike.cpp.template"
                                                                    print(writeTrace());
                                                                    print(staticPrefix());
                                                            #line 4797 "PrintCLike.cpp"
  append(L"xmlEscape(");
                                                            #line 3103 "PrintCLike.cpp.template"
                                                                    print(staticPrefix());
                                                                    print(isGo() ? L"nonterminal" : L"NONTERMINAL");
                                                                    print(leftbracket());
                                                            #line 4803 "PrintCLike.cpp"
  append(L"nonterminalId");
                                                            #line 3106 "PrintCLike.cpp.template"
                                                                    print(rightbracket());
                                                            #line 4807 "PrintCLike.cpp"
  append(L")");
                                                            #line 3107 "PrintCLike.cpp.template"
                                                                    print(endWriteTrace());
                                                                    print(semicolon());
                                                            #line 4812 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if ");
                                                            #line 3110 "PrintCLike.cpp.template"
                                                                    print(ifLeftParen());
                                                                    print(thiz());
                                                            #line 4818 "PrintCLike.cpp"
  append(L"l1 != 0");
                                                            #line 3112 "PrintCLike.cpp.template"
                                                                    print(ifRightParen());
                                                                    printIndented(1, leftBrace());
                                                            #line 4823 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 3115 "PrintCLike.cpp.template"
                                                                    print(writeTrace());
                                                            #line 4828 "PrintCLike.cpp"
  append(L"\" \"");
                                                            #line 3116 "PrintCLike.cpp.template"
                                                                    print(endWriteTrace());
                                                                    print(semicolon());
                                                                    increaseIndent();
                                                                    print(rightBrace());
                                                                    decreaseIndent();
                                                                    print(rightBrace());
                                                            #line 4837 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3123 "PrintCLike.cpp.template"
                                                                    print(writeTrace());
                                                                    print(staticPrefix());
                                                            #line 4842 "PrintCLike.cpp"
  append(L"xmlEscape(");
                                                            #line 3125 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 4846 "PrintCLike.cpp"
  append(L"lookaheadString");
                                                            #line 3126 "PrintCLike.cpp.template"
                                                                    if (! isScala()) print(L"()");
                                                            #line 4850 "PrintCLike.cpp"
  append(L") + \"\\\" action=\\\"\"");
                                                            #line 3127 "PrintCLike.cpp.template"
                                                                    print(endWriteTrace());
                                                                    print(semicolon());
                                                                  }
                                                                }
                                                            #line 4857 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3132 "PrintCLike.cpp.template"
                                                                print(intVal());
                                                            #line 4861 "PrintCLike.cpp"
  append(L"argument");
                                                            #line 3133 "PrintCLike.cpp.template"
                                                                print(assign());
                                                                if (useGlr) print(thiz());
                                                            #line 4866 "PrintCLike.cpp"
  append(L"action >> ");
                                                            #line 3135 "PrintCLike.cpp.template"
                                                                print(format.toString<wchar_t>(grammar->states->dominoBits + LrStates::actionBits));
                                                                print(semicolon());
                                                            #line 4871 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3138 "PrintCLike.cpp.template"
                                                                print(intVal());
                                                            #line 4875 "PrintCLike.cpp"
  append(L"lookback");
                                                            #line 3139 "PrintCLike.cpp.template"
                                                                print(assign());
                                                            #line 4879 "PrintCLike.cpp"
  append(L"(");
                                                            #line 3140 "PrintCLike.cpp.template"
                                                                if (useGlr) print(thiz());
                                                            #line 4883 "PrintCLike.cpp"
  append(L"action >> ");
                                                            #line 3141 "PrintCLike.cpp.template"
                                                                print(format.toString<wchar_t>((int) LrStates::actionBits));
                                                            #line 4887 "PrintCLike.cpp"
  append(L") & ");
                                                            #line 3142 "PrintCLike.cpp.template"
                                                                print(format.toString<wchar_t>((1 << grammar->states->dominoBits) -1));
                                                                print(semicolon());
                                                            #line 4892 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3145 "PrintCLike.cpp.template"
                                                                print(intVar());
                                                            #line 4896 "PrintCLike.cpp"
  append(L"shift");
                                                            #line 3146 "PrintCLike.cpp.template"
                                                                print(assign());
                                                            #line 4900 "PrintCLike.cpp"
  append(L"-1");
                                                            #line 3147 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 4904 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3149 "PrintCLike.cpp.template"
                                                                print(intVar());
                                                            #line 4908 "PrintCLike.cpp"
  append(L"reduce");
                                                            #line 3150 "PrintCLike.cpp.template"
                                                                print(assign());
                                                            #line 4912 "PrintCLike.cpp"
  append(L"-1");
                                                            #line 3151 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 4916 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3153 "PrintCLike.cpp.template"
                                                                print(intVar());
                                                            #line 4920 "PrintCLike.cpp"
  append(L"symbols");
                                                            #line 3154 "PrintCLike.cpp.template"
                                                                print(assign());
                                                            #line 4924 "PrintCLike.cpp"
  append(L"-1");
                                                            #line 3155 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                if (isPython())
                                                                {
                                                            #line 4930 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3160 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 4934 "PrintCLike.cpp"
  append(L"action &= ");
                                                            #line 3161 "PrintCLike.cpp.template"
                                                                  print(format.toString<wchar_t>((int) LrStates::actionMask));
                                                                }
                                                                else
                                                                {
                                                            #line 4941 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3166 "PrintCLike.cpp.template"
                                                                  if (! isScala())
                                                                  {
                                                            #line 4946 "PrintCLike.cpp"
  append(L"switch ");
                                                            #line 3168 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(ifLeftParen());
                                                                  if (useGlr) print(thiz());
                                                            #line 4952 "PrintCLike.cpp"
  append(L"action & ");
                                                            #line 3171 "PrintCLike.cpp.template"
                                                                  print(format.toString<wchar_t>((int) LrStates::actionMask));
                                                                  print(ifRightParen());
                                                                  if (isScala())
                                                                  {
                                                            #line 4959 "PrintCLike.cpp"
  append(L" match");
                                                            #line 3175 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(leftBrace());
                                                                }
                                                                if (isPython())
                                                                {
                                                            #line 4967 "PrintCLike.cpp"
  append(L"\n");
  append(L"if ");
                                                            #line 3181 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 4972 "PrintCLike.cpp"
  append(L"action == ");
                                                            #line 3182 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 4978 "PrintCLike.cpp"
  append(L"\n");
  append(L"case ");
                                                            #line 3186 "PrintCLike.cpp.template"
                                                                }
                                                                print(format.toString<wchar_t>((int) LrStates::SHIFT));
                                                                print(caseIntroducer());
                                                            #line 4985 "PrintCLike.cpp"
  append(L" ");
                                                            #line 3189 "PrintCLike.cpp.template"
                                                                print(inlineCommentIntroducer());
                                                            #line 4989 "PrintCLike.cpp"
  append(L"SHIFT\n");
  append(L"  shift = argument");
                                                            #line 3191 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                if (! isHaxe() && ! isScala() && ! isGo() && ! isPython())
                                                                {
                                                            #line 4996 "PrintCLike.cpp"
  append(L"\n");
  append(L"  break");
                                                            #line 3195 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                            #line 5002 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3198 "PrintCLike.cpp.template"
                                                                if (isPython())
                                                                {
                                                            #line 5007 "PrintCLike.cpp"
  append(L"\n");
  append(L"elif ");
                                                            #line 3201 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 5012 "PrintCLike.cpp"
  append(L"action == ");
                                                            #line 3202 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 5018 "PrintCLike.cpp"
  append(L"\n");
  append(L"case ");
                                                            #line 3206 "PrintCLike.cpp.template"
                                                                }
                                                                print(format.toString<wchar_t>((int) LrStates::REDUCE));
                                                                print(caseIntroducer());
                                                            #line 5025 "PrintCLike.cpp"
  append(L" ");
                                                            #line 3209 "PrintCLike.cpp.template"
                                                                print(inlineCommentIntroducer());
                                                            #line 5029 "PrintCLike.cpp"
  append(L"REDUCE\n");
  append(L"  reduce = argument");
                                                            #line 3211 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 5034 "PrintCLike.cpp"
  append(L"\n");
  append(L"  symbols = lookback");
                                                            #line 3213 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                if (! isHaxe() && ! isScala() && ! isGo() && ! isPython())
                                                                {
                                                            #line 5041 "PrintCLike.cpp"
  append(L"\n");
  append(L"  break");
                                                            #line 3217 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                                if (grammar->states->hasLookback)
                                                                {
                                                            #line 5049 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3222 "PrintCLike.cpp.template"
                                                                  if (isPython())
                                                                  {
                                                            #line 5054 "PrintCLike.cpp"
  append(L"\n");
  append(L"elif ");
                                                            #line 3225 "PrintCLike.cpp.template"
                                                                    if (useGlr) print(thiz());
                                                            #line 5059 "PrintCLike.cpp"
  append(L"action == ");
                                                            #line 3226 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 5065 "PrintCLike.cpp"
  append(L"\n");
  append(L"case ");
                                                            #line 3230 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(format.toString<wchar_t>((int) LrStates::REDUCE_LOOKBACK));
                                                                  print(caseIntroducer());
                                                            #line 5072 "PrintCLike.cpp"
  append(L" ");
                                                            #line 3233 "PrintCLike.cpp.template"
                                                                  print(inlineCommentIntroducer());
                                                            #line 5076 "PrintCLike.cpp"
  append(L"REDUCE+LOOKBACK\n");
  append(L"  reduce = argument");
                                                            #line 3235 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                            #line 5081 "PrintCLike.cpp"
  append(L"\n");
  append(L"  symbols = ");
                                                            #line 3237 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                                  if (useGlr)
                                                                  {
                                                            #line 5088 "PrintCLike.cpp"
  append(L"stack");
                                                            #line 3240 "PrintCLike.cpp.template"
                                                                    if (isTypescript()) print(L"!");
                                                                    print(arrow());
                                                                  }
                                                                  if (isGo() && useGlr)
                                                                  {
                                                            #line 5096 "PrintCLike.cpp"
  append(L"Count");
                                                            #line 3245 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 5102 "PrintCLike.cpp"
  append(L"count");
                                                            #line 3248 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 5106 "PrintCLike.cpp"
  append(L"(lookback)");
                                                            #line 3249 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                  if (! isHaxe() && ! isScala() && ! isGo() && ! isPython())
                                                                  {
                                                            #line 5112 "PrintCLike.cpp"
  append(L"\n");
  append(L"  break");
                                                            #line 3253 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                  }
                                                                }
                                                            #line 5119 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3257 "PrintCLike.cpp.template"
                                                                if (isPython())
                                                                {
                                                            #line 5124 "PrintCLike.cpp"
  append(L"\n");
  append(L"elif ");
                                                            #line 3260 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 5129 "PrintCLike.cpp"
  append(L"action == ");
                                                            #line 3261 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 5135 "PrintCLike.cpp"
  append(L"\n");
  append(L"case ");
                                                            #line 3265 "PrintCLike.cpp.template"
                                                                }
                                                                print(format.toString<wchar_t>((int) LrStates::SHIFT_REDUCE));
                                                                print(caseIntroducer());
                                                            #line 5142 "PrintCLike.cpp"
  append(L" ");
                                                            #line 3268 "PrintCLike.cpp.template"
                                                                print(inlineCommentIntroducer());
                                                            #line 5146 "PrintCLike.cpp"
  append(L"SHIFT+REDUCE\n");
  append(L"  shift = ");
                                                            #line 3270 "PrintCLike.cpp.template"
                                                                if (useGlr) print(thiz());
                                                            #line 5151 "PrintCLike.cpp"
  append(L"state");
                                                            #line 3271 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 5155 "PrintCLike.cpp"
  append(L"\n");
  append(L"  reduce = argument");
                                                            #line 3273 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 5160 "PrintCLike.cpp"
  append(L"\n");
  append(L"  symbols = lookback + 1");
                                                            #line 3275 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                if (! isHaxe() && ! isScala() && ! isGo() && ! isPython())
                                                                {
                                                            #line 5167 "PrintCLike.cpp"
  append(L"\n");
  append(L"  break");
                                                            #line 3279 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                                if (grammar->states->hasLookback)
                                                                {
                                                            #line 5175 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3284 "PrintCLike.cpp.template"
                                                                  if (isPython())
                                                                  {
                                                            #line 5180 "PrintCLike.cpp"
  append(L"\n");
  append(L"elif ");
                                                            #line 3287 "PrintCLike.cpp.template"
                                                                    if (useGlr) print(thiz());
                                                            #line 5185 "PrintCLike.cpp"
  append(L"action == ");
                                                            #line 3288 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 5191 "PrintCLike.cpp"
  append(L"\n");
  append(L"case ");
                                                            #line 3292 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(format.toString<wchar_t>((int) LrStates::SHIFT_REDUCE_LOOKBACK));
                                                                  print(caseIntroducer());
                                                            #line 5198 "PrintCLike.cpp"
  append(L" ");
                                                            #line 3295 "PrintCLike.cpp.template"
                                                                  print(inlineCommentIntroducer());
                                                            #line 5202 "PrintCLike.cpp"
  append(L"SHIFT+REDUCE+LOOKBACK\n");
  append(L"  shift = ");
                                                            #line 3297 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 5207 "PrintCLike.cpp"
  append(L"state");
                                                            #line 3298 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                            #line 5211 "PrintCLike.cpp"
  append(L"\n");
  append(L"  reduce = argument");
                                                            #line 3300 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                            #line 5216 "PrintCLike.cpp"
  append(L"\n");
  append(L"  symbols = ");
                                                            #line 3302 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                                  if (useGlr)
                                                                  {
                                                            #line 5223 "PrintCLike.cpp"
  append(L"stack");
                                                            #line 3305 "PrintCLike.cpp.template"
                                                                    if (isTypescript()) print(L"!");
                                                                    print(arrow());
                                                                  }
                                                                  if (isGo() && useGlr)
                                                                  {
                                                            #line 5231 "PrintCLike.cpp"
  append(L"Count");
                                                            #line 3310 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 5237 "PrintCLike.cpp"
  append(L"count");
                                                            #line 3313 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 5241 "PrintCLike.cpp"
  append(L"(lookback) + 1");
                                                            #line 3314 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                  if (! isHaxe() && ! isScala() && ! isGo() && ! isPython())
                                                                  {
                                                            #line 5247 "PrintCLike.cpp"
  append(L"\n");
  append(L"  break");
                                                            #line 3318 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                  }
                                                                }
                                                            #line 5254 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3322 "PrintCLike.cpp.template"
                                                                if (isPython())
                                                                {
                                                            #line 5259 "PrintCLike.cpp"
  append(L"\n");
  append(L"elif ");
                                                            #line 3325 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 5264 "PrintCLike.cpp"
  append(L"action == ");
                                                            #line 3326 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 5270 "PrintCLike.cpp"
  append(L"\n");
  append(L"case ");
                                                            #line 3330 "PrintCLike.cpp.template"
                                                                }
                                                                print(format.toString<wchar_t>((int) LrStates::SHIFT_ACCEPT));
                                                                print(caseIntroducer());
                                                            #line 5277 "PrintCLike.cpp"
  append(L" ");
                                                            #line 3333 "PrintCLike.cpp.template"
                                                                print(inlineCommentIntroducer());
                                                            #line 5281 "PrintCLike.cpp"
  append(L"ACCEPT");
                                                            #line 3334 "PrintCLike.cpp.template"
                                                                if (trace)
                                                                {
                                                                  if (isCpp())
                                                                  {
                                                            #line 5288 "PrintCLike.cpp"
  append(L"\n");
  append(L"  fprintf(stderr, ");
                                                            #line 3339 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 5295 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3343 "PrintCLike.cpp.template"
                                                                    print(writeTrace());
                                                                  }
                                                            #line 5301 "PrintCLike.cpp"
  append(L"\"accept\\\"/>");
                                                            #line 3345 "PrintCLike.cpp.template"
                                                                  if (! isHaxe())
                                                                  {
                                                            #line 5306 "PrintCLike.cpp"
  append(L"\\n");
                                                            #line 3347 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 5310 "PrintCLike.cpp"
  append(L"\"");
                                                            #line 3348 "PrintCLike.cpp.template"
                                                                  print(endWriteTrace());
                                                                  print(semicolon());
                                                                  if (isHaxe())
                                                                  {
                                                            #line 5317 "PrintCLike.cpp"
  append(L"\n");
  append(L"  trace(traceLine);");
                                                            #line 3353 "PrintCLike.cpp.template"
                                                                  }
                                                                }
                                                                if (useGlr)
                                                                {
                                                            #line 5325 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3358 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 5330 "PrintCLike.cpp"
  append(L"accepted = ");
                                                            #line 3359 "PrintCLike.cpp.template"
                                                                  if (isPython())
                                                                  {
                                                            #line 5335 "PrintCLike.cpp"
  append(L"T");
                                                            #line 3361 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 5341 "PrintCLike.cpp"
  append(L"t");
                                                            #line 3364 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 5345 "PrintCLike.cpp"
  append(L"rue");
                                                            #line 3365 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                            #line 5349 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3367 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 5354 "PrintCLike.cpp"
  append(L"action = 0");
                                                            #line 3368 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                            #line 5358 "PrintCLike.cpp"
  append(L"\n");
  append(L"  return ");
                                                            #line 3370 "PrintCLike.cpp.template"
                                                                  if (isHaxe() || isTypescript() || isPython()) print(staticPrefix());
                                                            #line 5363 "PrintCLike.cpp"
  append(L"ACCEPTED");
                                                            #line 3371 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                                else
                                                                {
                                                            #line 5370 "PrintCLike.cpp"
  append(L"\n");
  append(L"  return");
                                                            #line 3376 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }

                                                                if (useGlr)
                                                                {
                                                            #line 5379 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3382 "PrintCLike.cpp.template"
                                                                  if (isPython())
                                                                  {
                                                            #line 5384 "PrintCLike.cpp"
  append(L"\n");
  append(L"elif ");
                                                            #line 3385 "PrintCLike.cpp.template"
                                                                    if (useGlr) print(thiz());
                                                            #line 5389 "PrintCLike.cpp"
  append(L"action == ");
                                                            #line 3386 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 5395 "PrintCLike.cpp"
  append(L"\n");
  append(L"case ");
                                                            #line 3390 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(format.toString<wchar_t>((int) LrStates::FORK));
                                                                  print(caseIntroducer());
                                                            #line 5402 "PrintCLike.cpp"
  append(L" ");
                                                            #line 3393 "PrintCLike.cpp.template"
                                                                  print(inlineCommentIntroducer());
                                                            #line 5406 "PrintCLike.cpp"
  append(L"FORK");
                                                            #line 3394 "PrintCLike.cpp.template"
                                                                  if (trace)
                                                                  {
                                                                    if (isCpp())
                                                                    {
                                                            #line 5413 "PrintCLike.cpp"
  append(L"\n");
  append(L"  fprintf(stderr, \"fork\\\"/>\\n\");");
                                                            #line 3399 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 5420 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3403 "PrintCLike.cpp.template"
                                                                      print(writeTrace());
                                                            #line 5425 "PrintCLike.cpp"
  append(L"\"fork\\\"/>");
                                                            #line 3404 "PrintCLike.cpp.template"
                                                                      if (! isHaxe())
                                                                      {
                                                            #line 5430 "PrintCLike.cpp"
  append(L"\\n\"");
                                                            #line 3406 "PrintCLike.cpp.template"
                                                                        print(endWriteTrace());
                                                                        print(semicolon());
                                                                      }
                                                                      else
                                                                      {
                                                            #line 5438 "PrintCLike.cpp"
  append(L"\";\n");
  append(L"  trace(traceLine);");
                                                            #line 3412 "PrintCLike.cpp.template"
                                                                      }
                                                                    }
                                                                  }
                                                                  if (isGo())
                                                                  {
                                                            #line 5447 "PrintCLike.cpp"
  append(L"\n");
  append(L"  heap.Push(this.threads, new(ParsingThread).copy(this, appendix[argument]))");
                                                            #line 3419 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isPython())
                                                                  {
                                                            #line 5454 "PrintCLike.cpp"
  append(L"\n");
  append(L"  forked = ");
                                                            #line 3423 "PrintCLike.cpp.template"
                                                                    print(staticPrefix());
                                                            #line 5459 "PrintCLike.cpp"
  append(L"ParsingThread().copy(self, ");
                                                            #line 3424 "PrintCLike.cpp.template"
                                                                    print(staticPrefix());
                                                            #line 5463 "PrintCLike.cpp"
  append(L"APPENDIX[argument])\n");
  append(L"  heapq.heappush(self.threads, (False, forked.e0, forked.id, forked))");
                                                            #line 3427 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 5470 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3431 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 5475 "PrintCLike.cpp"
  append(L"threads");
                                                            #line 3432 "PrintCLike.cpp.template"
                                                                    if (isCpp())
                                                                    {
                                                            #line 5480 "PrintCLike.cpp"
  append(L"->push(");
                                                            #line 3434 "PrintCLike.cpp.template"
                                                                    }
                                                                    else if (isScala())
                                                                    {
                                                            #line 5486 "PrintCLike.cpp"
  append(L" += ");
                                                            #line 3437 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 5492 "PrintCLike.cpp"
  append(L".offer(");
                                                            #line 3440 "PrintCLike.cpp.template"
                                                                    }
                                                                    if (isCpp() || isScala()) print(L"(");
                                                            #line 5497 "PrintCLike.cpp"
  append(L"new ParsingThread");
                                                            #line 3442 "PrintCLike.cpp.template"
                                                                    if (! isScala()) print(L"()");
                                                                    if (isCpp() || isScala()) print(L")");
                                                                    print(arrow());
                                                            #line 5503 "PrintCLike.cpp"
  append(L"copy(this");
                                                            #line 3445 "PrintCLike.cpp.template"
                                                                    if (isJavascript())
                                                                    {
                                                            #line 5508 "PrintCLike.cpp"
  append(L"Thread");
                                                            #line 3447 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 5512 "PrintCLike.cpp"
  append(L", ");
                                                            #line 3448 "PrintCLike.cpp.template"
                                                                    print(staticPrefix());
                                                            #line 5516 "PrintCLike.cpp"
  append(L"APPENDIX");
                                                            #line 3449 "PrintCLike.cpp.template"
                                                                    print(leftbracket());
                                                            #line 5520 "PrintCLike.cpp"
  append(L"argument");
                                                            #line 3450 "PrintCLike.cpp.template"
                                                                    print(rightbracket());
                                                            #line 5524 "PrintCLike.cpp"
  append(L")");
                                                            #line 3451 "PrintCLike.cpp.template"
                                                                    if (! isScala()) print(L")");
                                                                    print(semicolon());
                                                                  }
                                                            #line 5530 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3455 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 5535 "PrintCLike.cpp"
  append(L"action = ");
                                                            #line 3456 "PrintCLike.cpp.template"
                                                                  print(staticPrefix());
                                                                  if (isGo())
                                                                  {
                                                            #line 5541 "PrintCLike.cpp"
  append(L"appendix");
                                                            #line 3459 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 5547 "PrintCLike.cpp"
  append(L"APPENDIX");
                                                            #line 3462 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(leftbracket());
                                                            #line 5552 "PrintCLike.cpp"
  append(L"argument + 1");
                                                            #line 3464 "PrintCLike.cpp.template"
                                                                  print(rightbracket());
                                                                  print(semicolon());
                                                            #line 5557 "PrintCLike.cpp"
  append(L"\n");
  append(L"  return ");
                                                            #line 3467 "PrintCLike.cpp.template"
                                                                  if (isHaxe() || isTypescript() || isPython()) print(staticPrefix());
                                                            #line 5562 "PrintCLike.cpp"
  append(L"PARSING");
                                                            #line 3468 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                            #line 5567 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3471 "PrintCLike.cpp.template"
                                                                if (isPython())
                                                                {
                                                            #line 5572 "PrintCLike.cpp"
  append(L"\n");
  append(L"else");
                                                            #line 3474 "PrintCLike.cpp.template"
                                                                }
                                                                else if (isScala())
                                                                {
                                                            #line 5579 "PrintCLike.cpp"
  append(L"\n");
  append(L"case _");
                                                            #line 3478 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 5586 "PrintCLike.cpp"
  append(L"\n");
  append(L"default");
                                                            #line 3482 "PrintCLike.cpp.template"
                                                                }
                                                                print(caseIntroducer());
                                                            #line 5592 "PrintCLike.cpp"
  append(L" ");
                                                            #line 3484 "PrintCLike.cpp.template"
                                                                print(inlineCommentIntroducer());
                                                            #line 5596 "PrintCLike.cpp"
  append(L"ERROR");
                                                            #line 3485 "PrintCLike.cpp.template"
                                                                if (useGlr)
                                                                {
                                                                  if (trace)
                                                                  {
                                                                    if (isCpp())
                                                                    {
                                                            #line 5605 "PrintCLike.cpp"
  append(L"\n");
  append(L"  fprintf(stderr, \"fail\\\"/>\\n\");");
                                                            #line 3492 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 5612 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3496 "PrintCLike.cpp.template"
                                                                      print(writeTrace());
                                                            #line 5617 "PrintCLike.cpp"
  append(L"\"fail\\\"/>");
                                                            #line 3497 "PrintCLike.cpp.template"
                                                                      if (! isHaxe())
                                                                      {
                                                            #line 5622 "PrintCLike.cpp"
  append(L"\\n\"");
                                                            #line 3499 "PrintCLike.cpp.template"
                                                                        print(endWriteTrace());
                                                                        print(semicolon());
                                                                      }
                                                                      else
                                                                      {
                                                            #line 5630 "PrintCLike.cpp"
  append(L"\";\n");
  append(L"  trace(traceLine);");
                                                            #line 3505 "PrintCLike.cpp.template"
                                                                      }
                                                                    }
                                                                  }
                                                            #line 5637 "PrintCLike.cpp"
  append(L"\n");
  append(L"  return ");
                                                            #line 3509 "PrintCLike.cpp.template"
                                                                  if (isHaxe() || isTypescript() || isPython()) print(staticPrefix());
                                                            #line 5642 "PrintCLike.cpp"
  append(L"ERROR");
                                                            #line 3510 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                                else
                                                                {
                                                            #line 5649 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3515 "PrintCLike.cpp.template"
                                                                  print(beginThrowStmt());
                                                                  print(thiz());
                                                            #line 5655 "PrintCLike.cpp"
  append(L"b1, ");
                                                            #line 3517 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 5659 "PrintCLike.cpp"
  append(L"e1, ");
                                                            #line 3518 "PrintCLike.cpp.template"
                                                                  print(staticPrefix());
                                                                  if (isGo())
                                                                  {
                                                            #line 5665 "PrintCLike.cpp"
  append(L"tokenset");
                                                            #line 3521 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 5671 "PrintCLike.cpp"
  append(L"TOKENSET");
                                                            #line 3524 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(leftbracket());
                                                            #line 5676 "PrintCLike.cpp"
  append(L"state");
                                                            #line 3526 "PrintCLike.cpp.template"
                                                                  print(rightbracket());
                                                            #line 5680 "PrintCLike.cpp"
  append(L" + 1, ");
                                                            #line 3527 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 5684 "PrintCLike.cpp"
  append(L"l1, -1");
                                                            #line 3528 "PrintCLike.cpp.template"
                                                                  print(endThrowStmt());
                                                                  print(semicolon());
                                                                }
                                                                print(rightBrace());
                                                            #line 5691 "PrintCLike.cpp"
  append(L"\n");
  append(L"\n");
  append(L"if ");
                                                            #line 3534 "PrintCLike.cpp.template"
                                                                print(ifLeftParen());
                                                            #line 5697 "PrintCLike.cpp"
  append(L"shift >= 0");
                                                            #line 3535 "PrintCLike.cpp.template"
                                                                print(ifRightParen());
                                                                print(leftBrace());
                                                                if (trace)
                                                                {
                                                                  if (isCpp())
                                                                  {
                                                            #line 5706 "PrintCLike.cpp"
  append(L"\n");
  append(L"  fprintf(stderr, ");
                                                            #line 3542 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 5713 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3546 "PrintCLike.cpp.template"
                                                                    print(writeTrace());
                                                                  }
                                                            #line 5719 "PrintCLike.cpp"
  append(L"\"shift\"");
                                                            #line 3548 "PrintCLike.cpp.template"
                                                                  print(endWriteTrace());
                                                                  print(semicolon());
                                                                }
                                                            #line 5725 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if ");
                                                            #line 3552 "PrintCLike.cpp.template"
                                                                print(ifLeftParen());
                                                            #line 5730 "PrintCLike.cpp"
  append(L"nonterminalId < 0");
                                                            #line 3553 "PrintCLike.cpp.template"
                                                                print(ifRightParen());
                                                                printIndented(1, leftBrace());
                                                                if (tree)
                                                                {
                                                            #line 5737 "PrintCLike.cpp"
  append(L"\n");
  append(L"    if ");
                                                            #line 3558 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                                  if (useGlr) print(thiz());
                                                            #line 5743 "PrintCLike.cpp"
  append(L"eventHandler != ");
                                                            #line 3560 "PrintCLike.cpp.template"
                                                                  print(nullPtr());
                                                                  print(ifRightParen());
                                                                  printIndented(2, leftBrace());
                                                                  if (useGlr)
                                                                  {
                                                            #line 5751 "PrintCLike.cpp"
  append(L"\n");
  append(L"      if ");
                                                            #line 3566 "PrintCLike.cpp.template"
                                                                    print(ifLeftParen());
                                                                    print(thiz());
                                                                    if (isGo())
                                                                    {
                                                            #line 5759 "PrintCLike.cpp"
  append(L"IsUnambiguous");
                                                            #line 3570 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 5765 "PrintCLike.cpp"
  append(L"isUnambiguous");
                                                            #line 3573 "PrintCLike.cpp.template"
                                                                    }
                                                                    if (! isScala()) print(L"()");
                                                                    print(ifRightParen());
                                                                    printIndented(3, leftBrace());
                                                                    increaseIndent();
                                                                  }
                                                            #line 5774 "PrintCLike.cpp"
  append(L"\n");
  append(L"      ");
                                                            #line 3580 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 5779 "PrintCLike.cpp"
  append(L"eventHandler");
                                                            #line 3581 "PrintCLike.cpp.template"
                                                                  print(arrow());
                                                                  if (isGo())
                                                                  {
                                                            #line 5785 "PrintCLike.cpp"
  append(L"T");
                                                            #line 3584 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 5791 "PrintCLike.cpp"
  append(L"t");
                                                            #line 3587 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 5795 "PrintCLike.cpp"
  append(L"erminal(");
                                                            #line 3588 "PrintCLike.cpp.template"
                                                                  print(staticPrefix());
                                                                  print(isGo() ? L"token" : L"TOKEN");
                                                                  print(leftbracket());
                                                                  print(thiz());
                                                            #line 5802 "PrintCLike.cpp"
  append(L"l1");
                                                            #line 3592 "PrintCLike.cpp.template"
                                                                  print(rightbracket());
                                                            #line 5806 "PrintCLike.cpp"
  append(L", ");
                                                            #line 3593 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 5810 "PrintCLike.cpp"
  append(L"b1, ");
                                                            #line 3594 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 5814 "PrintCLike.cpp"
  append(L"e1)");
                                                            #line 3595 "PrintCLike.cpp.template"
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
                                                            #line 5827 "PrintCLike.cpp"
  append(L"\n");
  append(L"      ");
                                                            #line 3606 "PrintCLike.cpp.template"
                                                                    printIndented(3, elseWithBraces());
                                                            #line 5832 "PrintCLike.cpp"
  append(L"\n");
  append(L"        ");
                                                            #line 3608 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 5837 "PrintCLike.cpp"
  append(L"deferredEvent = ");
                                                            #line 3609 "PrintCLike.cpp.template"
                                                                    if (isGo())
                                                                    {
                                                            #line 5842 "PrintCLike.cpp"
  append(L"&TerminalEvent{&AbstractDeferredEvent{");
                                                            #line 3611 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                                      if (! isPython())
                                                                      {
                                                            #line 5850 "PrintCLike.cpp"
  append(L"new ");
                                                            #line 3616 "PrintCLike.cpp.template"
                                                                      }
                                                                      if (! isHaxe() && ! isTypescript()) print(staticPrefix());
                                                                      if (isJavascript() || isTypescript())
                                                                      {
                                                            #line 5857 "PrintCLike.cpp"
  append(L"DeferredEvent");
                                                            #line 3620 "PrintCLike.cpp.template"
                                                                      }
                                                                      else
                                                                      {
                                                            #line 5863 "PrintCLike.cpp"
  append(L"TerminalEvent");
                                                            #line 3623 "PrintCLike.cpp.template"
                                                                      }
                                                            #line 5867 "PrintCLike.cpp"
  append(L"(");
                                                            #line 3624 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(thiz());
                                                            #line 5872 "PrintCLike.cpp"
  append(L"deferredEvent, ");
                                                            #line 3626 "PrintCLike.cpp.template"
                                                                    print(staticPrefix());
                                                                    print(isGo() ? L"token" : L"TOKEN");
                                                                    print(leftbracket());
                                                                    print(thiz());
                                                            #line 5879 "PrintCLike.cpp"
  append(L"l1");
                                                            #line 3630 "PrintCLike.cpp.template"
                                                                    print(rightbracket());
                                                            #line 5883 "PrintCLike.cpp"
  append(L", ");
                                                            #line 3631 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 5887 "PrintCLike.cpp"
  append(L"b1, ");
                                                            #line 3632 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 5891 "PrintCLike.cpp"
  append(L"e1");
                                                            #line 3634 "PrintCLike.cpp.template"
                                                                    if (isTypescript())
                                                                    {
                                                            #line 5896 "PrintCLike.cpp"
  append(L", -1");
                                                            #line 3636 "PrintCLike.cpp.template"
                                                                    }
                                                                    if (isGo())
                                                                    {
                                                            #line 5902 "PrintCLike.cpp"
  append(L"}}");
                                                            #line 3640 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 5908 "PrintCLike.cpp"
  append(L")");
                                                            #line 3644 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                                    }
                                                                    increaseIndent(3);
                                                                    print(rightBrace());
                                                                    decreaseIndent();
                                                                    print(rightBrace());
                                                                    decreaseIndent(2);
                                                                  }
                                                            #line 5919 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 3653 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 5924 "PrintCLike.cpp"
  append(L"es = ");
                                                            #line 3654 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 5928 "PrintCLike.cpp"
  append(L"e1");
                                                            #line 3655 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                                if (useGlr)
                                                                {
                                                            #line 5935 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 3660 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 5940 "PrintCLike.cpp"
  append(L"stack = ");
                                                            #line 3661 "PrintCLike.cpp.template"
                                                                  if (isGo())
                                                                  {
                                                            #line 5945 "PrintCLike.cpp"
  append(L"&StackNode{");
                                                            #line 3663 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                                    if (! isPython())
                                                                    {
                                                            #line 5953 "PrintCLike.cpp"
  append(L"new ");
                                                            #line 3668 "PrintCLike.cpp.template"
                                                                    }
                                                                    if (! isHaxe() && ! isTypescript()) print(staticPrefix());
                                                            #line 5958 "PrintCLike.cpp"
  append(L"StackNode(");
                                                            #line 3670 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(thiz());
                                                            #line 5963 "PrintCLike.cpp"
  append(L"state, ");
                                                            #line 3672 "PrintCLike.cpp.template"
                                                                  if (grammar->states->hasLookback)
                                                                  {
                                                            #line 5968 "PrintCLike.cpp"
  append(L"lookback, ");
                                                            #line 3674 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(thiz());
                                                            #line 5973 "PrintCLike.cpp"
  append(L"b1, ");
                                                            #line 3676 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 5977 "PrintCLike.cpp"
  append(L"stack");
                                                            #line 3677 "PrintCLike.cpp.template"
                                                                  print(isGo() ? L"}" : L")");
                                                                  print(semicolon());
                                                                }
                                                                else
                                                                {
                                                            #line 5985 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 3683 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 5990 "PrintCLike.cpp"
  append(L"push(state, lookback");
                                                            #line 3684 "PrintCLike.cpp.template"
                                                                  if (tree)
                                                                  {
                                                            #line 5995 "PrintCLike.cpp"
  append(L", ");
                                                            #line 3686 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 5999 "PrintCLike.cpp"
  append(L"b1");
                                                            #line 3687 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 6003 "PrintCLike.cpp"
  append(L")");
                                                            #line 3688 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                            #line 6008 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 3691 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 6013 "PrintCLike.cpp"
  append(L"consume(");
                                                            #line 3692 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 6017 "PrintCLike.cpp"
  append(L"l1)");
                                                            #line 3693 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 6021 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3695 "PrintCLike.cpp.template"
                                                                printIndented(1, elseWithBraces());
                                                                if (useGlr)
                                                                {
                                                            #line 6028 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 3699 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 6033 "PrintCLike.cpp"
  append(L"stack = ");
                                                            #line 3700 "PrintCLike.cpp.template"
                                                                  if (isGo())
                                                                  {
                                                            #line 6038 "PrintCLike.cpp"
  append(L"&StackNode{");
                                                            #line 3702 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                                    if (! isPython())
                                                                    {
                                                            #line 6046 "PrintCLike.cpp"
  append(L"new ");
                                                            #line 3707 "PrintCLike.cpp.template"
                                                                    }
                                                                    if (! isHaxe() && ! isTypescript()) print(staticPrefix());
                                                            #line 6051 "PrintCLike.cpp"
  append(L"StackNode(");
                                                            #line 3709 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(thiz());
                                                            #line 6056 "PrintCLike.cpp"
  append(L"state, ");
                                                            #line 3711 "PrintCLike.cpp.template"
                                                                  if (grammar->states->hasLookback)
                                                                  {
                                                            #line 6061 "PrintCLike.cpp"
  append(L"lookback, ");
                                                            #line 3713 "PrintCLike.cpp.template"
                                                                  }
                                                                  if (tree)
                                                                  {
                                                                    print(thiz());
                                                            #line 6068 "PrintCLike.cpp"
  append(L"bs");
                                                            #line 3717 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 6074 "PrintCLike.cpp"
  append(L"0");
                                                            #line 3720 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 6078 "PrintCLike.cpp"
  append(L", ");
                                                            #line 3721 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 6082 "PrintCLike.cpp"
  append(L"stack");
                                                            #line 3722 "PrintCLike.cpp.template"
                                                                  print(isGo() ? L"}" : L")");
                                                                  print(semicolon());
                                                                }
                                                                else
                                                                {
                                                            #line 6090 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 3728 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 6095 "PrintCLike.cpp"
  append(L"push(state, lookback");
                                                            #line 3729 "PrintCLike.cpp.template"
                                                                  if (tree)
                                                                  {
                                                            #line 6100 "PrintCLike.cpp"
  append(L", bs");
                                                            #line 3731 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 6104 "PrintCLike.cpp"
  append(L")");
                                                            #line 3732 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                                increaseIndent();
                                                                print(rightBrace());
                                                                decreaseIndent();
                                                            #line 6112 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3738 "PrintCLike.cpp.template"
                                                                if (useGlr) print(thiz());
                                                            #line 6117 "PrintCLike.cpp"
  append(L"state = shift");
                                                            #line 3739 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                print(rightBrace());
                                                            #line 6122 "PrintCLike.cpp"
  append(L"\n");
  append(L"\n");
  append(L"if ");
                                                            #line 3743 "PrintCLike.cpp.template"
                                                                print(ifLeftParen());
                                                            #line 6128 "PrintCLike.cpp"
  append(L"reduce < 0");
                                                            #line 3744 "PrintCLike.cpp.template"
                                                                print(ifRightParen());
                                                                print(leftBrace());
                                                                if (trace)
                                                                {
                                                                  if (isCpp())
                                                                  {
                                                            #line 6137 "PrintCLike.cpp"
  append(L"\n");
  append(L"  fprintf(stderr, ");
                                                            #line 3751 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 6144 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3755 "PrintCLike.cpp.template"
                                                                    print(writeTrace());
                                                                  }
                                                            #line 6150 "PrintCLike.cpp"
  append(L"\"\\\"/>");
                                                            #line 3758 "PrintCLike.cpp.template"
                                                                  if (! isHaxe())
                                                                  {
                                                            #line 6155 "PrintCLike.cpp"
  append(L"\\n\"");
                                                            #line 3760 "PrintCLike.cpp.template"
                                                                    print(endWriteTrace());
                                                                    print(semicolon());
                                                                  }
                                                                  else
                                                                  {
                                                            #line 6163 "PrintCLike.cpp"
  append(L"\";\n");
  append(L"  trace(traceLine);");
                                                            #line 3766 "PrintCLike.cpp.template"
                                                                  }
                                                                }
                                                            #line 6169 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3769 "PrintCLike.cpp.template"
                                                                if (useGlr) print(thiz());
                                                            #line 6174 "PrintCLike.cpp"
  append(L"action = ");
                                                            #line 3770 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 6178 "PrintCLike.cpp"
  append(L"predict(");
                                                            #line 3771 "PrintCLike.cpp.template"
                                                                if (useGlr) print(thiz());
                                                            #line 6182 "PrintCLike.cpp"
  append(L"state)");
                                                            #line 3772 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                if (useGlr)
                                                                {
                                                                  if (isCpp())
                                                                  {
                                                            #line 6190 "PrintCLike.cpp"
  append(L"\n");
  append(L"  break");
                                                            #line 3778 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                  }
                                                                  else
                                                                  {
                                                            #line 6198 "PrintCLike.cpp"
  append(L"\n");
  append(L"  return ");
                                                            #line 3783 "PrintCLike.cpp.template"
                                                                    if (isHaxe() || isTypescript() || isPython()) print(staticPrefix());
                                                            #line 6203 "PrintCLike.cpp"
  append(L"PARSING");
                                                            #line 3784 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                  }
                                                                }
                                                                else
                                                                {
                                                            #line 6211 "PrintCLike.cpp"
  append(L"\n");
  append(L"  nonterminalId = -1");
                                                            #line 3790 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                            #line 6217 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3793 "PrintCLike.cpp.template"
                                                                print(elseWithBraces());
                                                                if (hasCustomCode)
                                                                {
                                                            #line 6223 "PrintCLike.cpp"
  append(L"\n");
  append(L"  nonterminalId = ");
                                                            #line 3797 "PrintCLike.cpp.template"
                                                                  print(staticPrefix());
                                                                  if (isGo())
                                                                  {
                                                            #line 6230 "PrintCLike.cpp"
  append(L"reduction");
                                                            #line 3800 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 6236 "PrintCLike.cpp"
  append(L"REDUCTION");
                                                            #line 3803 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(leftbracket());
                                                            #line 6241 "PrintCLike.cpp"
  append(L"reduce");
                                                            #line 3805 "PrintCLike.cpp.template"
                                                                  print(rightbracket());
                                                                  print(semicolon());
                                                            #line 6246 "PrintCLike.cpp"
  append(L"\n");
  append(L"  reduce = ");
                                                            #line 3808 "PrintCLike.cpp.template"
                                                                  print(staticPrefix());
                                                                  if (isGo())
                                                                  {
                                                            #line 6253 "PrintCLike.cpp"
  append(L"reduction");
                                                            #line 3811 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 6259 "PrintCLike.cpp"
  append(L"REDUCTION");
                                                            #line 3814 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(leftbracket());
                                                            #line 6264 "PrintCLike.cpp"
  append(L"reduce + 1");
                                                            #line 3816 "PrintCLike.cpp.template"
                                                                  print(rightbracket());
                                                                  print(semicolon());
                                                            #line 6269 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if ");
                                                            #line 3819 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                            #line 6274 "PrintCLike.cpp"
  append(L"reduce >= 0");
                                                            #line 3820 "PrintCLike.cpp.template"
                                                                  print(ifRightParen());
                                                                  increaseIndent();
                                                                  print(leftBrace());
                                                                  if (useGlr)
                                                                  {
                                                            #line 6282 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if ");
                                                            #line 3826 "PrintCLike.cpp.template"
                                                                    print(ifLeftParen());
                                                                    print(thiz());
                                                                    if (isGo())
                                                                    {
                                                            #line 6290 "PrintCLike.cpp"
  append(L"IsUnambiguous");
                                                            #line 3830 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 6296 "PrintCLike.cpp"
  append(L"isUnambiguous");
                                                            #line 3833 "PrintCLike.cpp.template"
                                                                    }
                                                                    if (! isScala()) print(L"()");
                                                                    print(ifRightParen());
                                                                    print(leftBrace());
                                                            #line 6303 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 3838 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                                    print(isGo() && useGlr ? L"E" : L"e");
                                                            #line 6309 "PrintCLike.cpp"
  append(L"xecute(reduce)");
                                                            #line 3840 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 6313 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3842 "PrintCLike.cpp.template"
                                                                    print(elseWithBraces());
                                                            #line 6318 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 3844 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 6323 "PrintCLike.cpp"
  append(L"deferredCode = ");
                                                            #line 3845 "PrintCLike.cpp.template"
                                                                    if (isGo())
                                                                    {
                                                            #line 6328 "PrintCLike.cpp"
  append(L"&DeferredCode{");
                                                            #line 3848 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                                      if (! isPython())
                                                                      {
                                                            #line 6336 "PrintCLike.cpp"
  append(L"new ");
                                                            #line 3853 "PrintCLike.cpp.template"
                                                                      }
                                                                      if (! isHaxe() && ! isTypescript()) print(staticPrefix());
                                                            #line 6341 "PrintCLike.cpp"
  append(L"DeferredCode(");
                                                            #line 3855 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(thiz());
                                                            #line 6346 "PrintCLike.cpp"
  append(L"deferredCode, reduce, ");
                                                            #line 3857 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 6350 "PrintCLike.cpp"
  append(L"b0, ");
                                                            #line 3858 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 6354 "PrintCLike.cpp"
  append(L"e0");
                                                            #line 3860 "PrintCLike.cpp.template"
                                                                    if (isGo())
                                                                    {
                                                            #line 6359 "PrintCLike.cpp"
  append(L"}");
                                                            #line 3863 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 6365 "PrintCLike.cpp"
  append(L")");
                                                            #line 3867 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(semicolon());
                                                                    increaseIndent();
                                                                    print(rightBrace());
                                                                    decreaseIndent();
                                                                  }
                                                                  else
                                                                  {
                                                            #line 6376 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3876 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                                    print(isGo() && useGlr ? L"E" : L"e");
                                                            #line 6382 "PrintCLike.cpp"
  append(L"xecute(reduce)");
                                                            #line 3878 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                  }
                                                                  print(rightBrace());
                                                                  decreaseIndent();
                                                                }
                                                                else
                                                                {
                                                            #line 6392 "PrintCLike.cpp"
  append(L"\n");
  append(L"  nonterminalId = reduce");
                                                            #line 3886 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                                if (trace)
                                                                {
                                                            #line 6400 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if ");
                                                            #line 3891 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                            #line 6405 "PrintCLike.cpp"
  append(L"shift >= 0");
                                                            #line 3892 "PrintCLike.cpp.template"
                                                                  print(ifRightParen());
                                                                  printIndented(1, leftBrace());
                                                                  if (isCpp())
                                                                  {
                                                            #line 6412 "PrintCLike.cpp"
  append(L"\n");
  append(L"    fprintf(stderr, ");
                                                            #line 3897 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 6419 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 3901 "PrintCLike.cpp.template"
                                                                    print(writeTrace());
                                                                  }
                                                            #line 6425 "PrintCLike.cpp"
  append(L"\" \"");
                                                            #line 3903 "PrintCLike.cpp.template"
                                                                  print(endWriteTrace());
                                                                  print(semicolon());
                                                                  increaseIndent();
                                                                  print(rightBrace());
                                                                  decreaseIndent();
                                                                  if (isCpp())
                                                                  {
                                                            #line 6435 "PrintCLike.cpp"
  append(L"\n");
  append(L"  fprintf(stderr, \"reduce\\\" nonterminal=\\\"%s\\\" count=\\\"%d\\\"/>\\n\", ");
                                                            #line 3911 "PrintCLike.cpp.template"
                                                                    if (stringIntroducer()[0])
                                                                    {
                                                            #line 6441 "PrintCLike.cpp"
  append(L"Utf8Encoder::encode(");
                                                            #line 3913 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 6445 "PrintCLike.cpp"
  append(L"xmlEscape(");
                                                            #line 3914 "PrintCLike.cpp.template"
                                                                    print(isGo() ? L"nonterminal" : L"NONTERMINAL");
                                                            #line 6449 "PrintCLike.cpp"
  append(L"[nonterminalId], 0).c_str()");
                                                            #line 3916 "PrintCLike.cpp.template"
                                                                    if (stringIntroducer()[0])
                                                                    {
                                                            #line 6454 "PrintCLike.cpp"
  append(L").c_str()");
                                                            #line 3918 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 6458 "PrintCLike.cpp"
  append(L", symbols);");
                                                            #line 3919 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 6464 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3923 "PrintCLike.cpp.template"
                                                                    print(writeTrace());
                                                            #line 6469 "PrintCLike.cpp"
  append(L"\"reduce\\\" nonterminal=\\\"\" + ");
                                                            #line 3925 "PrintCLike.cpp.template"
                                                                    print(staticPrefix());
                                                            #line 6473 "PrintCLike.cpp"
  append(L"xmlEscape(");
                                                            #line 3926 "PrintCLike.cpp.template"
                                                                    print(staticPrefix());
                                                                    print(isGo() ? L"nonterminal" : L"NONTERMINAL");
                                                                    print(leftbracket());
                                                            #line 6479 "PrintCLike.cpp"
  append(L"nonterminalId");
                                                            #line 3929 "PrintCLike.cpp.template"
                                                                    print(rightbracket());
                                                            #line 6483 "PrintCLike.cpp"
  append(L") + \"\\\" count=\\\"\" + ");
                                                            #line 3931 "PrintCLike.cpp.template"
                                                                    if (isPython())
                                                                    {
                                                            #line 6488 "PrintCLike.cpp"
  append(L"str(");
                                                            #line 3934 "PrintCLike.cpp.template"
                                                                    }
                                                                    else if (isGo())
                                                                    {
                                                            #line 6494 "PrintCLike.cpp"
  append(L"strconv.Itoa(");
                                                            #line 3938 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 6498 "PrintCLike.cpp"
  append(L"symbols");
                                                            #line 3940 "PrintCLike.cpp.template"
                                                                    if (isGo() || isPython())
                                                                    {
                                                            #line 6503 "PrintCLike.cpp"
  append(L")");
                                                            #line 3943 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 6507 "PrintCLike.cpp"
  append(L" + \"\\\"/>");
                                                            #line 3945 "PrintCLike.cpp.template"
                                                                    if (! isHaxe())
                                                                    {
                                                            #line 6512 "PrintCLike.cpp"
  append(L"\\n\"");
                                                            #line 3948 "PrintCLike.cpp.template"
                                                                      print(endWriteTrace());
                                                                      print(semicolon());
                                                                    }
                                                                    else
                                                                    {
                                                            #line 6520 "PrintCLike.cpp"
  append(L"\";\n");
  append(L"  trace(traceLine);");
                                                            #line 3954 "PrintCLike.cpp.template"
                                                                    }
                                                                  }
                                                                }
                                                                if (tree)
                                                                {
                                                            #line 6529 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if ");
                                                            #line 3960 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                            #line 6534 "PrintCLike.cpp"
  append(L"symbols > 0");
                                                            #line 3961 "PrintCLike.cpp.template"
                                                                  print(ifRightParen());
                                                                  printIndented(1, leftBrace());
                                                                  if (useGlr)
                                                                  {
                                                                    if (isCpp())
                                                                    {
                                                            #line 6543 "PrintCLike.cpp"
  append(L"\n");
  append(L"    stack = stack->pop(symbols - 1);");
                                                            #line 3968 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                                      increaseIndent(2);
                                                                      if (isHaxe())
                                                                      {
                                                            #line 6553 "PrintCLike.cpp"
  append(L"\n");
  append(L"for (i in 1...symbols)");
                                                            #line 3975 "PrintCLike.cpp.template"
                                                                      }
                                                                      else if (isScala())
                                                                      {
                                                            #line 6560 "PrintCLike.cpp"
  append(L"\n");
  append(L"var i = 0\n");
  append(L"for (i <- 2 to symbols)");
                                                            #line 3980 "PrintCLike.cpp.template"
                                                                      }
                                                                      else if (isPython())
                                                                      {
                                                            #line 6568 "PrintCLike.cpp"
  append(L"\n");
  append(L"for _ in range(symbols - 1):");
                                                            #line 3984 "PrintCLike.cpp.template"
                                                                      }
                                                                      else
                                                                      {
                                                            #line 6575 "PrintCLike.cpp"
  append(L"\n");
  append(L"for ");
                                                            #line 3988 "PrintCLike.cpp.template"
                                                                        print(ifLeftParen());
                                                                        print(intVar());
                                                            #line 6581 "PrintCLike.cpp"
  append(L"i");
                                                            #line 3990 "PrintCLike.cpp.template"
                                                                        print(assign());
                                                            #line 6585 "PrintCLike.cpp"
  append(L"1; i < symbols; i++");
                                                            #line 3991 "PrintCLike.cpp.template"
                                                                        print(ifRightParen());
                                                                      }
                                                                      print(leftBrace());
                                                            #line 6591 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3995 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 6596 "PrintCLike.cpp"
  append(L"stack = ");
                                                            #line 3996 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 6600 "PrintCLike.cpp"
  append(L"stack.link");
                                                            #line 3997 "PrintCLike.cpp.template"
                                                                      if (isTypescript()) print(L"!");
                                                                      print(semicolon());
                                                                      print(rightBrace());
                                                                      decreaseIndent(2);
                                                                    }
                                                            #line 6608 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4003 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 6613 "PrintCLike.cpp"
  append(L"state = ");
                                                            #line 4004 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 6617 "PrintCLike.cpp"
  append(L"stack");
                                                            #line 4005 "PrintCLike.cpp.template"
                                                                    print(arrow());
                                                            #line 6621 "PrintCLike.cpp"
  append(L"state");
                                                            #line 4006 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 6625 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4008 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 6630 "PrintCLike.cpp"
  append(L"bs = ");
                                                            #line 4009 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 6634 "PrintCLike.cpp"
  append(L"stack");
                                                            #line 4010 "PrintCLike.cpp.template"
                                                                    print(arrow());
                                                            #line 6638 "PrintCLike.cpp"
  append(L"pos");
                                                            #line 4011 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                    if (isCpp())
                                                                    {
                                                            #line 6644 "PrintCLike.cpp"
  append(L"\n");
  append(L"    stack = stack->pop(1);");
                                                            #line 4015 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 6651 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4019 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 6656 "PrintCLike.cpp"
  append(L"stack = ");
                                                            #line 4020 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 6660 "PrintCLike.cpp"
  append(L"stack.link");
                                                            #line 4021 "PrintCLike.cpp.template"
                                                                      if (isTypescript()) print(L"!");
                                                                      print(semicolon());
                                                                    }
                                                                  }
                                                                  else
                                                                  {
                                                            #line 6669 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4028 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 6674 "PrintCLike.cpp"
  append(L"top -= symbols * 3");
                                                            #line 4029 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 6678 "PrintCLike.cpp"
  append(L"\n");
  append(L"    state = ");
                                                            #line 4031 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 6683 "PrintCLike.cpp"
  append(L"iStack");
                                                            #line 4032 "PrintCLike.cpp.template"
                                                                    print(leftbracket());
                                                                    print(thiz());
                                                            #line 6688 "PrintCLike.cpp"
  append(L"top + 2");
                                                            #line 4034 "PrintCLike.cpp.template"
                                                                    print(rightbracket());
                                                                    print(semicolon());
                                                            #line 6693 "PrintCLike.cpp"
  append(L"\n");
  append(L"    bs = ");
                                                            #line 4037 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 6698 "PrintCLike.cpp"
  append(L"iStack");
                                                            #line 4038 "PrintCLike.cpp.template"
                                                                    print(leftbracket());
                                                                    print(thiz());
                                                            #line 6703 "PrintCLike.cpp"
  append(L"top + 1");
                                                            #line 4040 "PrintCLike.cpp.template"
                                                                    print(rightbracket());
                                                                    print(semicolon());
                                                                  }
                                                            #line 6709 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4044 "PrintCLike.cpp.template"
                                                                  printIndented(1, elseWithBraces());
                                                            #line 6714 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4046 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 6719 "PrintCLike.cpp"
  append(L"bs = ");
                                                            #line 4047 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 6723 "PrintCLike.cpp"
  append(L"b1");
                                                            #line 4048 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                            #line 6727 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4050 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 6732 "PrintCLike.cpp"
  append(L"es = ");
                                                            #line 4051 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 6736 "PrintCLike.cpp"
  append(L"b1");
                                                            #line 4052 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                  increaseIndent();
                                                                  print(rightBrace());
                                                                  decreaseIndent();
                                                            #line 6743 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if ");
                                                            #line 4057 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                            #line 6748 "PrintCLike.cpp"
  append(L"nonterminalId == ");
                                                            #line 4058 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 6752 "PrintCLike.cpp"
  append(L"target ");
                                                            #line 4059 "PrintCLike.cpp.template"
                                                                  if (isPython())
                                                                  {
                                                            #line 6757 "PrintCLike.cpp"
  append(L"and");
                                                            #line 4061 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 6763 "PrintCLike.cpp"
  append(L"&&");
                                                            #line 4064 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 6767 "PrintCLike.cpp"
  append(L" ");
                                                            #line 4065 "PrintCLike.cpp.template"
                                                                  if (useGlr)
                                                                  {
                                                                    print(thiz());
                                                            #line 6773 "PrintCLike.cpp"
  append(L"stack");
                                                            #line 4068 "PrintCLike.cpp.template"
                                                                    print(arrow());
                                                            #line 6777 "PrintCLike.cpp"
  append(L"link == ");
                                                            #line 4069 "PrintCLike.cpp.template"
                                                                    print(nullPtr());
                                                                  }
                                                                  else
                                                                  {
                                                            #line 6784 "PrintCLike.cpp"
  append(L"t == ");
                                                            #line 4073 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 6788 "PrintCLike.cpp"
  append(L"top");
                                                            #line 4074 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(ifRightParen());
                                                                  printIndented(1, leftBrace());
                                                            #line 6794 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4078 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 6799 "PrintCLike.cpp"
  append(L"bs = ");
                                                            #line 4079 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 6803 "PrintCLike.cpp"
  append(L"bw");
                                                            #line 4080 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                            #line 6807 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4082 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 6812 "PrintCLike.cpp"
  append(L"es = ");
                                                            #line 4083 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 6816 "PrintCLike.cpp"
  append(L"b1");
                                                            #line 4084 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                            #line 6820 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4086 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 6825 "PrintCLike.cpp"
  append(L"bw = ");
                                                            #line 4087 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 6829 "PrintCLike.cpp"
  append(L"b1");
                                                            #line 4088 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                  increaseIndent();
                                                                  print(rightBrace());
                                                                  decreaseIndent();
                                                            #line 6836 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if ");
                                                            #line 4093 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                                  if (useGlr) print(thiz());
                                                            #line 6842 "PrintCLike.cpp"
  append(L"eventHandler != ");
                                                            #line 4095 "PrintCLike.cpp.template"
                                                                  print(nullPtr());
                                                                  print(ifRightParen());
                                                                  printIndented(1, leftBrace());
                                                                  if (useGlr)
                                                                  {
                                                            #line 6850 "PrintCLike.cpp"
  append(L"\n");
  append(L"    if ");
                                                            #line 4101 "PrintCLike.cpp.template"
                                                                    print(ifLeftParen());
                                                                    print(thiz());
                                                                    if (isGo())
                                                                    {
                                                            #line 6858 "PrintCLike.cpp"
  append(L"IsUnambiguous");
                                                            #line 4105 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 6864 "PrintCLike.cpp"
  append(L"isUnambiguous");
                                                            #line 4108 "PrintCLike.cpp.template"
                                                                    }
                                                                    if (! isScala()) print(L"()");
                                                                    print(ifRightParen());
                                                                    printIndented(2, leftBrace());
                                                                    increaseIndent();
                                                                  }
                                                            #line 6873 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4115 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 6878 "PrintCLike.cpp"
  append(L"eventHandler");
                                                            #line 4116 "PrintCLike.cpp.template"
                                                                  print(arrow());
                                                                  if (isGo())
                                                                  {
                                                            #line 6884 "PrintCLike.cpp"
  append(L"N");
                                                            #line 4119 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 6890 "PrintCLike.cpp"
  append(L"n");
                                                            #line 4122 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 6894 "PrintCLike.cpp"
  append(L"onterminal(");
                                                            #line 4123 "PrintCLike.cpp.template"
                                                                  print(staticPrefix());
                                                                  print(isGo() ? L"nonterminal" : L"NONTERMINAL");
                                                                  print(leftbracket());
                                                            #line 6900 "PrintCLike.cpp"
  append(L"nonterminalId");
                                                            #line 4126 "PrintCLike.cpp.template"
                                                                  print(rightbracket());
                                                            #line 6904 "PrintCLike.cpp"
  append(L", ");
                                                            #line 4127 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 6908 "PrintCLike.cpp"
  append(L"bs, ");
                                                            #line 4128 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 6912 "PrintCLike.cpp"
  append(L"es, symbols)");
                                                            #line 4130 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                  if (useGlr)
                                                                  {
                                                                    decreaseIndent();
                                                            #line 6919 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4135 "PrintCLike.cpp.template"
                                                                    printIndented(2, elseWithBraces());
                                                            #line 6924 "PrintCLike.cpp"
  append(L"\n");
  append(L"      ");
                                                            #line 4137 "PrintCLike.cpp.template"
                                                                    if (useGlr) print(thiz());
                                                            #line 6929 "PrintCLike.cpp"
  append(L"deferredEvent = ");
                                                            #line 4138 "PrintCLike.cpp.template"
                                                                    if (isGo())
                                                                    {
                                                            #line 6934 "PrintCLike.cpp"
  append(L"&NonterminalEvent{&AbstractDeferredEvent{this.deferredEvent, nonterminal[nonterminalId], this.bs, this.es}, symbols}");
                                                            #line 4141 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                                      if (! isPython())
                                                                      {
                                                            #line 6942 "PrintCLike.cpp"
  append(L"new ");
                                                            #line 4146 "PrintCLike.cpp.template"
                                                                      }
                                                                      if (! isHaxe() && ! isTypescript()) print(staticPrefix());
                                                                      if (isJavascript() || isTypescript())
                                                                      {
                                                            #line 6949 "PrintCLike.cpp"
  append(L"DeferredEvent");
                                                            #line 4150 "PrintCLike.cpp.template"
                                                                      }
                                                                      else
                                                                      {
                                                            #line 6955 "PrintCLike.cpp"
  append(L"NonterminalEvent");
                                                            #line 4153 "PrintCLike.cpp.template"
                                                                      }
                                                            #line 6959 "PrintCLike.cpp"
  append(L"(");
                                                            #line 4154 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 6963 "PrintCLike.cpp"
  append(L"deferredEvent, ");
                                                            #line 4155 "PrintCLike.cpp.template"
                                                                      print(staticPrefix());
                                                            #line 6967 "PrintCLike.cpp"
  append(L"NONTERMINAL");
                                                            #line 4156 "PrintCLike.cpp.template"
                                                                      print(leftbracket());
                                                            #line 6971 "PrintCLike.cpp"
  append(L"nonterminalId");
                                                            #line 4157 "PrintCLike.cpp.template"
                                                                      print(rightbracket());
                                                            #line 6975 "PrintCLike.cpp"
  append(L", ");
                                                            #line 4158 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 6979 "PrintCLike.cpp"
  append(L"bs, ");
                                                            #line 4160 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 6983 "PrintCLike.cpp"
  append(L"es, symbols)");
                                                            #line 4162 "PrintCLike.cpp.template"
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
                                                            #line 6998 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if ");
                                                            #line 4175 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                            #line 7003 "PrintCLike.cpp"
  append(L"symbols > 0");
                                                            #line 4176 "PrintCLike.cpp.template"
                                                                  print(ifRightParen());
                                                                  printIndented(1, leftBrace());
                                                                  if (useGlr)
                                                                  {
                                                                    if (isCpp())
                                                                    {
                                                            #line 7012 "PrintCLike.cpp"
  append(L"\n");
  append(L"    stack = stack->pop(symbols - 1);");
                                                            #line 4183 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                                      increaseIndent(2);
                                                                      if (isHaxe())
                                                                      {
                                                            #line 7022 "PrintCLike.cpp"
  append(L"\n");
  append(L"for (i in 1...symbols)");
                                                            #line 4190 "PrintCLike.cpp.template"
                                                                      }
                                                                      else if (isScala())
                                                                      {
                                                            #line 7029 "PrintCLike.cpp"
  append(L"\n");
  append(L"var i = 0\n");
  append(L"for (i <- 2 to symbols)");
                                                            #line 4195 "PrintCLike.cpp.template"
                                                                      }
                                                                      else if (isPython())
                                                                      {
                                                            #line 7037 "PrintCLike.cpp"
  append(L"\n");
  append(L"for _ in range(symbols - 1):");
                                                            #line 4199 "PrintCLike.cpp.template"
                                                                      }
                                                                      else
                                                                      {
                                                            #line 7044 "PrintCLike.cpp"
  append(L"\n");
  append(L"for ");
                                                            #line 4203 "PrintCLike.cpp.template"
                                                                        print(ifLeftParen());
                                                                        print(intVar());
                                                            #line 7050 "PrintCLike.cpp"
  append(L"i");
                                                            #line 4205 "PrintCLike.cpp.template"
                                                                        print(assign());
                                                            #line 7054 "PrintCLike.cpp"
  append(L"1; i < symbols; i++");
                                                            #line 4206 "PrintCLike.cpp.template"
                                                                        print(ifRightParen());
                                                                      }
                                                                      print(leftBrace());
                                                            #line 7060 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4210 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 7065 "PrintCLike.cpp"
  append(L"stack = ");
                                                            #line 4211 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 7069 "PrintCLike.cpp"
  append(L"stack.link");
                                                            #line 4212 "PrintCLike.cpp.template"
                                                                      if (isTypescript()) print(L"!");
                                                                      print(semicolon());
                                                                      print(rightBrace());
                                                                      decreaseIndent(2);
                                                                    }
                                                            #line 7077 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4219 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7082 "PrintCLike.cpp"
  append(L"state = ");
                                                            #line 4220 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7086 "PrintCLike.cpp"
  append(L"stack");
                                                            #line 4221 "PrintCLike.cpp.template"
                                                                    print(arrow());
                                                            #line 7090 "PrintCLike.cpp"
  append(L"state");
                                                            #line 4222 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                    if (tree)
                                                                    {
                                                            #line 7096 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4226 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 7101 "PrintCLike.cpp"
  append(L"bs = ");
                                                            #line 4227 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 7105 "PrintCLike.cpp"
  append(L"stack");
                                                            #line 4228 "PrintCLike.cpp.template"
                                                                      print(arrow());
                                                            #line 7109 "PrintCLike.cpp"
  append(L"pos");
                                                            #line 4229 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                                    }
                                                                    if (isCpp())
                                                                    {
                                                            #line 7116 "PrintCLike.cpp"
  append(L"\n");
  append(L"    stack = stack->pop(1);");
                                                            #line 4234 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 7123 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4238 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 7128 "PrintCLike.cpp"
  append(L"stack = ");
                                                            #line 4239 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 7132 "PrintCLike.cpp"
  append(L"stack.link");
                                                            #line 4240 "PrintCLike.cpp.template"
                                                                      if (isTypescript()) print(L"!");
                                                                      print(semicolon());
                                                                    }
                                                                  }
                                                                  else
                                                                  {
                                                            #line 7141 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4247 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7146 "PrintCLike.cpp"
  append(L"top -= symbols << 1;\n");
  append(L"    state = ");
                                                            #line 4249 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7151 "PrintCLike.cpp"
  append(L"iStack");
                                                            #line 4250 "PrintCLike.cpp.template"
                                                                    print(leftbracket());
                                                                    print(thiz());
                                                            #line 7156 "PrintCLike.cpp"
  append(L"top + 1");
                                                            #line 4252 "PrintCLike.cpp.template"
                                                                    print(rightbracket());
                                                                    print(semicolon());
                                                                  }
                                                                  if (! useGlr)
                                                                  {
                                                                    increaseIndent();
                                                                    print(rightBrace());
                                                                    decreaseIndent();
                                                                  }
                                                                  else
                                                                  {
                                                            #line 7170 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4264 "PrintCLike.cpp.template"
                                                                    printIndented(1, elseWithBraces());
                                                            #line 7175 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4266 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7180 "PrintCLike.cpp"
  append(L"bs = ");
                                                            #line 4267 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7184 "PrintCLike.cpp"
  append(L"b1");
                                                            #line 4268 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                    increaseIndent();
                                                                    print(rightBrace());
                                                                    decreaseIndent();
                                                                    if (tree)
                                                                    {
                                                            #line 7193 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if ");
                                                            #line 4275 "PrintCLike.cpp.template"
                                                                      print(ifLeftParen());
                                                            #line 7198 "PrintCLike.cpp"
  append(L"nonterminalId == ");
                                                            #line 4276 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 7202 "PrintCLike.cpp"
  append(L"target ");
                                                            #line 4277 "PrintCLike.cpp.template"
                                                                      if (isPython())
                                                                      {
                                                            #line 7207 "PrintCLike.cpp"
  append(L"and");
                                                            #line 4279 "PrintCLike.cpp.template"
                                                                      }
                                                                      else
                                                                      {
                                                            #line 7213 "PrintCLike.cpp"
  append(L"&&");
                                                            #line 4282 "PrintCLike.cpp.template"
                                                                      }
                                                            #line 7217 "PrintCLike.cpp"
  append(L" ");
                                                            #line 4283 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 7221 "PrintCLike.cpp"
  append(L"stack");
                                                            #line 4284 "PrintCLike.cpp.template"
                                                                      print(arrow());
                                                            #line 7225 "PrintCLike.cpp"
  append(L"link == ");
                                                            #line 4285 "PrintCLike.cpp.template"
                                                                      print(nullPtr());
                                                                      print(ifRightParen());
                                                                      printIndented(1, leftBrace());
                                                            #line 7231 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4289 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 7236 "PrintCLike.cpp"
  append(L"bs = ");
                                                            #line 4290 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 7240 "PrintCLike.cpp"
  append(L"bw");
                                                            #line 4291 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                            #line 7244 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4293 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 7249 "PrintCLike.cpp"
  append(L"bw = ");
                                                            #line 4294 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 7253 "PrintCLike.cpp"
  append(L"b1");
                                                            #line 4295 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                                      increaseIndent();
                                                                      print(rightBrace());
                                                                      decreaseIndent();
                                                                    }
                                                                  }
                                                                }
                                                            #line 7263 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4303 "PrintCLike.cpp.template"
                                                                if (useGlr) print(thiz());
                                                            #line 7268 "PrintCLike.cpp"
  append(L"action = ");
                                                            #line 4304 "PrintCLike.cpp.template"
                                                                print(staticPrefix());
                                                                print(isGo() ? L"reduceAction" : L"goTo");
                                                            #line 7273 "PrintCLike.cpp"
  append(L"(nonterminalId, ");
                                                            #line 4306 "PrintCLike.cpp.template"
                                                                if (useGlr) print(thiz());
                                                            #line 7277 "PrintCLike.cpp"
  append(L"state)");
                                                            #line 4307 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                print(rightBrace());
                                                                decreaseIndent();
                                                                print(rightBrace());
                                                                decreaseIndent();
                                                                if (useGlr)
                                                                {
                                                                  if (isScala())
                                                                  {
                                                            #line 7289 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ERROR");
                                                            #line 4317 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isCpp())
                                                                  {
                                                            #line 7296 "PrintCLike.cpp"
  append(L"\n");
  append(L"  return PARSING;");
                                                            #line 4321 "PrintCLike.cpp.template"
                                                                  }
                                                                }
                                                                print(rightBrace());
                                                                if (isJavascript() && useGlr)
                                                                {
                                                            #line 7305 "PrintCLike.cpp"
  append(L";");
                                                            #line 4326 "PrintCLike.cpp.template"
                                                                }
                                                            #line 7309 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4328 "PrintCLike.cpp.template"
                                                                if ((tree || hasCustomCode) && useGlr)
                                                                {
                                                                  openMethod(boolType(), L"", L"isUnambiguous", L"", false, L"ParsingThread");
                                                                  print(leftBrace());
                                                            #line 7316 "PrintCLike.cpp"
  append(L"\n");
  append(L"  return ");
                                                            #line 4333 "PrintCLike.cpp.template"
                                                                  if (isPython())
                                                                  {
                                                            #line 7322 "PrintCLike.cpp"
  append(L"len(self.threads) == 0");
                                                            #line 4335 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                                    print(thiz());
                                                            #line 7329 "PrintCLike.cpp"
  append(L"threads");
                                                            #line 4339 "PrintCLike.cpp.template"
                                                                    print(arrow());
                                                                    if (isCpp())
                                                                    {
                                                            #line 7335 "PrintCLike.cpp"
  append(L"empty();");
                                                            #line 4342 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 7341 "PrintCLike.cpp"
  append(L"isEmpty");
                                                            #line 4345 "PrintCLike.cpp.template"
                                                                      if (! isScala()) print(L"()");
                                                                      print(semicolon());
                                                                    }
                                                                  }
                                                                  print(rightBrace());
                                                            #line 7349 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4351 "PrintCLike.cpp.template"
                                                                }
                                                                if (hasCustomCode)
                                                                {
                                                                  if (useGlr)
                                                                  {
                                                                    if (isJavascript())
                                                                    {
                                                            #line 7359 "PrintCLike.cpp"
  append(L"\n");
  append(L"this.executeDeferredCode = function()\n");
                                                            #line 4360 "PrintCLike.cpp.template"
                                                                    }
                                                                    else if (isTypescript())
                                                                    {
                                                            #line 7366 "PrintCLike.cpp"
  append(L"\n");
  append(L"executeDeferredCode()\n");
                                                            #line 4365 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                                      openMethod(voidType(), L"", L"executeDeferredCode", L"", false, L"ParsingThread");
                                                                    }
                                                                    print(leftBrace());
                                                                    increaseIndent();
                                                            #line 7377 "PrintCLike.cpp"
  append(L"\n");
  append(L"if ");
                                                            #line 4373 "PrintCLike.cpp.template"
                                                                    print(ifLeftParen());
                                                                    print(thiz());
                                                            #line 7383 "PrintCLike.cpp"
  append(L"deferredCode != ");
                                                            #line 4375 "PrintCLike.cpp.template"
                                                                    print(nullPtr());
                                                                    print(ifRightParen());
                                                                    print(leftBrace());
                                                                    increaseIndent();
                                                            #line 7390 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4380 "PrintCLike.cpp.template"
                                                                    if (isJavascript() || isHaxe() || isScala() || isTypescript())
                                                                    {
                                                            #line 7395 "PrintCLike.cpp"
  append(L"var ");
                                                            #line 4382 "PrintCLike.cpp.template"
                                                                    }
                                                                    else if (! isGo() && ! isPython())
                                                                    {
                                                            #line 7401 "PrintCLike.cpp"
  append(L"DeferredCode ");
                                                            #line 4385 "PrintCLike.cpp.template"
                                                                    }
                                                                    if (isCpp()) print(L"*");
                                                            #line 7406 "PrintCLike.cpp"
  append(L"predecessor");
                                                            #line 4387 "PrintCLike.cpp.template"
                                                                    print(assign());
                                                                    print(thiz());
                                                            #line 7411 "PrintCLike.cpp"
  append(L"deferredCode");
                                                            #line 4389 "PrintCLike.cpp.template"
                                                                    print(arrow());
                                                            #line 7415 "PrintCLike.cpp"
  append(L"link");
                                                            #line 4390 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 7419 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4392 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7423 "PrintCLike.cpp"
  append(L"deferredCode");
                                                            #line 4393 "PrintCLike.cpp.template"
                                                                    print(arrow());
                                                            #line 7427 "PrintCLike.cpp"
  append(L"link = ");
                                                            #line 4394 "PrintCLike.cpp.template"
                                                                    print(nullPtr());
                                                                    print(semicolon());
                                                                    if (isGo())
                                                                    {
                                                            #line 7434 "PrintCLike.cpp"
  append(L"\n");
  append(L"for ");
                                                            #line 4399 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 7441 "PrintCLike.cpp"
  append(L"\n");
  append(L"while ");
                                                            #line 4403 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(ifLeftParen());
                                                            #line 7447 "PrintCLike.cpp"
  append(L"predecessor != ");
                                                            #line 4405 "PrintCLike.cpp.template"
                                                                    print(nullPtr());
                                                                    print(ifRightParen());
                                                                    print(leftBrace());
                                                            #line 7453 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4409 "PrintCLike.cpp.template"
                                                                    if (isJavascript() || isHaxe() || isScala() || isTypescript())
                                                                    {
                                                            #line 7459 "PrintCLike.cpp"
  append(L"var ");
                                                            #line 4411 "PrintCLike.cpp.template"
                                                                    }
                                                                    else if (! isGo() && ! isPython())
                                                                    {
                                                            #line 7465 "PrintCLike.cpp"
  append(L"DeferredCode ");
                                                            #line 4414 "PrintCLike.cpp.template"
                                                                    }
                                                                    if (isCpp()) print(L"*");
                                                            #line 7470 "PrintCLike.cpp"
  append(L"nextCode");
                                                            #line 4416 "PrintCLike.cpp.template"
                                                                    print(assign());
                                                            #line 7474 "PrintCLike.cpp"
  append(L"predecessor");
                                                            #line 4417 "PrintCLike.cpp.template"
                                                                    print(arrow());
                                                            #line 7478 "PrintCLike.cpp"
  append(L"link");
                                                            #line 4418 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 7482 "PrintCLike.cpp"
  append(L"\n");
  append(L"  predecessor");
                                                            #line 4420 "PrintCLike.cpp.template"
                                                                    print(arrow());
                                                            #line 7487 "PrintCLike.cpp"
  append(L"link = ");
                                                            #line 4421 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7491 "PrintCLike.cpp"
  append(L"deferredCode");
                                                            #line 4422 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 7495 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4424 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7500 "PrintCLike.cpp"
  append(L"deferredCode = predecessor");
                                                            #line 4425 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 7504 "PrintCLike.cpp"
  append(L"\n");
  append(L"  predecessor = nextCode");
                                                            #line 4427 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                    print(rightBrace());
                                                            #line 7510 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4430 "PrintCLike.cpp.template"
                                                                    print(intVar());
                                                            #line 7514 "PrintCLike.cpp"
  append(L"b0t");
                                                            #line 4431 "PrintCLike.cpp.template"
                                                                    print(assign());
                                                                    print(thiz());
                                                            #line 7519 "PrintCLike.cpp"
  append(L"b0");
                                                            #line 4433 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 7523 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4435 "PrintCLike.cpp.template"
                                                                    print(intVar());
                                                            #line 7527 "PrintCLike.cpp"
  append(L"e0t");
                                                            #line 4436 "PrintCLike.cpp.template"
                                                                    print(assign());
                                                                    print(thiz());
                                                            #line 7532 "PrintCLike.cpp"
  append(L"e0");
                                                            #line 4438 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                    if (isGo())
                                                                    {
                                                            #line 7538 "PrintCLike.cpp"
  append(L"\n");
  append(L"for ");
                                                            #line 4442 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 7545 "PrintCLike.cpp"
  append(L"\n");
  append(L"while ");
                                                            #line 4446 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(ifLeftParen());
                                                                    print(thiz());
                                                            #line 7552 "PrintCLike.cpp"
  append(L"deferredCode != ");
                                                            #line 4449 "PrintCLike.cpp.template"
                                                                    print(nullPtr());
                                                                    print(ifRightParen());
                                                                    print(leftBrace());
                                                            #line 7558 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4453 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7563 "PrintCLike.cpp"
  append(L"b0 = ");
                                                            #line 4454 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7567 "PrintCLike.cpp"
  append(L"deferredCode");
                                                            #line 4455 "PrintCLike.cpp.template"
                                                                    print(arrow());
                                                            #line 7571 "PrintCLike.cpp"
  append(L"b0");
                                                            #line 4456 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 7575 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4458 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7580 "PrintCLike.cpp"
  append(L"e0 = ");
                                                            #line 4459 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7584 "PrintCLike.cpp"
  append(L"deferredCode");
                                                            #line 4460 "PrintCLike.cpp.template"
                                                                    print(arrow());
                                                            #line 7588 "PrintCLike.cpp"
  append(L"e0");
                                                            #line 4461 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 7592 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4463 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                                    print(isGo() ? L"E" : L"e");
                                                            #line 7598 "PrintCLike.cpp"
  append(L"xecute(");
                                                            #line 4465 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7602 "PrintCLike.cpp"
  append(L"deferredCode");
                                                            #line 4466 "PrintCLike.cpp.template"
                                                                    print(arrow());
                                                            #line 7606 "PrintCLike.cpp"
  append(L"codeId)");
                                                            #line 4467 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                    if (isCpp())
                                                                    {
                                                            #line 7612 "PrintCLike.cpp"
  append(L"\n");
  append(L"  DeferredCode *next = deferredCode->link;\n");
  append(L"  delete deferredCode;\n");
  append(L"  deferredCode = next;");
                                                            #line 4473 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 7621 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4477 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 7626 "PrintCLike.cpp"
  append(L"deferredCode = ");
                                                            #line 4478 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 7630 "PrintCLike.cpp"
  append(L"deferredCode");
                                                            #line 4479 "PrintCLike.cpp.template"
                                                                      print(arrow());
                                                            #line 7634 "PrintCLike.cpp"
  append(L"link");
                                                            #line 4480 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                                    }
                                                                    print(rightBrace());
                                                            #line 7640 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4484 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7644 "PrintCLike.cpp"
  append(L"b0 = b0t");
                                                            #line 4485 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 7648 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4487 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7652 "PrintCLike.cpp"
  append(L"e0 = e0t");
                                                            #line 4488 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                    decreaseIndent();
                                                                    print(rightBrace());
                                                                    decreaseIndent();
                                                                    print(rightBrace());
                                                            #line 7660 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4494 "PrintCLike.cpp.template"
                                                                  }
                                                                  openMethod(voidType(), L"", L"execute", L"int reduce", false, useGlr ? L"ParsingThread" : className.c_str());
                                                                  print(leftBrace());
                                                                  increaseIndent();
                                                                  if (! isPython())
                                                                  {
                                                            #line 7669 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4501 "PrintCLike.cpp.template"
                                                                    if (! isScala())
                                                                    {
                                                            #line 7674 "PrintCLike.cpp"
  append(L"switch ");
                                                            #line 4503 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(ifLeftParen());
                                                            #line 7679 "PrintCLike.cpp"
  append(L"reduce");
                                                            #line 4505 "PrintCLike.cpp.template"
                                                                    print(ifRightParen());
                                                                    if (isScala())
                                                                    {
                                                            #line 7685 "PrintCLike.cpp"
  append(L" match");
                                                            #line 4508 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(leftBrace());
                                                                  }
                                                                  int lastContentId = grammar->distinctCodeAnnotations.size() - 1;
                                                                  for (int contentId = 0; contentId <= lastContentId; ++contentId)
                                                                  {
                                                                    ProcessingInstruction *p = grammar->distinctCodeAnnotations[contentId];
                                                                    if (! isPython())
                                                                    {
                                                            #line 7697 "PrintCLike.cpp"
  append(L"\n");
  append(L"case ");
                                                            #line 4518 "PrintCLike.cpp.template"
                                                                    }
                                                                    else if (contentId == 0)
                                                                    {
                                                            #line 7704 "PrintCLike.cpp"
  append(L"\n");
  append(L"if reduce == ");
                                                            #line 4522 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 7711 "PrintCLike.cpp"
  append(L"\n");
  append(L"elif reduce == ");
                                                            #line 4526 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(format.toString<wchar_t>(contentId));
                                                                    print(caseIntroducer());
                                                                    increaseIndent();
                                                                    print(leftBrace());
                                                                    visitProcessingInstruction(p);
                                                                    print(rightBrace());
                                                                    if (! isScala() && ! isHaxe() && ! isGo() && ! isPython())
                                                                    {
                                                            #line 7724 "PrintCLike.cpp"
  append(L"\n");
  append(L"break");
                                                            #line 4536 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                                    }
                                                                    decreaseIndent();
                                                                  }
                                                                  if (isScala())
                                                                  {
                                                            #line 7734 "PrintCLike.cpp"
  append(L"\n");
  append(L"case _");
                                                            #line 4543 "PrintCLike.cpp.template"
                                                                    print(caseIntroducer());
                                                                  }
                                                                  else if (! isPython())
                                                                  {
                                                            #line 7742 "PrintCLike.cpp"
  append(L"\n");
  append(L"default");
                                                            #line 4548 "PrintCLike.cpp.template"
                                                                    print(caseIntroducer());
                                                                  }
                                                                  if (! isScala() && ! isHaxe() && ! isGo() && ! isPython())
                                                                  {
                                                            #line 7750 "PrintCLike.cpp"
  append(L"\n");
  append(L"  break");
                                                            #line 4553 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                  }
                                                                  print(rightBrace());
                                                                  decreaseIndent();
                                                                  print(rightBrace());
                                                            #line 7759 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4559 "PrintCLike.cpp.template"
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
                                                            #line 7785 "PrintCLike.cpp"
  append(L"\n");
  append(L"if ");
                                                            #line 4583 "PrintCLike.cpp.template"
                                                                print(ifLeftParen());
                                                                print(thiz());
                                                            #line 7791 "PrintCLike.cpp"
  append(L"l1 == t");
                                                            #line 4585 "PrintCLike.cpp.template"
                                                                print(ifRightParen());
                                                                print(leftBrace());
                                                                increaseIndent();
                                                                if (tree && i == 0 && ! isLrParser)
                                                                {
                                                                  if (anyWhitespace && ! isLrParser)
                                                                  {
                                                            #line 7801 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4593 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7805 "PrintCLike.cpp"
  append(L"whitespace");
                                                            #line 4594 "PrintCLike.cpp.template"
                                                                    print(isScala() ? L"" : L"()");
                                                                    print(semicolon());
                                                                  }
                                                            #line 7811 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4599 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 7815 "PrintCLike.cpp"
  append(L"eventHandler");
                                                            #line 4600 "PrintCLike.cpp.template"
                                                                  print(arrow());
                                                                  if (isGo())
                                                                  {
                                                            #line 7821 "PrintCLike.cpp"
  append(L"T");
                                                            #line 4603 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 7827 "PrintCLike.cpp"
  append(L"t");
                                                            #line 4606 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 7831 "PrintCLike.cpp"
  append(L"erminal(");
                                                            #line 4607 "PrintCLike.cpp.template"
                                                                  if (isJava() || isCSharp())
                                                                  {
                                                                    print(staticPrefix());
                                                            #line 7837 "PrintCLike.cpp"
  append(L"TOKEN[");
                                                            #line 4610 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7841 "PrintCLike.cpp"
  append(L"l1]");
                                                            #line 4611 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isTypescript())
                                                                  {
                                                                    print(staticPrefix());
                                                            #line 7848 "PrintCLike.cpp"
  append(L"TOKEN[");
                                                            #line 4615 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7852 "PrintCLike.cpp"
  append(L"l1]");
                                                            #line 4616 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isJavascript() || isHaxe())
                                                                  {
                                                                    print(staticPrefix());
                                                            #line 7859 "PrintCLike.cpp"
  append(L"TOKEN[");
                                                            #line 4620 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7863 "PrintCLike.cpp"
  append(L"l1]");
                                                            #line 4621 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isScala())
                                                                  {
                                                                    print(staticPrefix());
                                                            #line 7870 "PrintCLike.cpp"
  append(L"TOKEN(l1)");
                                                            #line 4625 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isGo())
                                                                  {
                                                            #line 7876 "PrintCLike.cpp"
  append(L"token[this.l1]");
                                                            #line 4628 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                                    print(staticPrefix());
                                                            #line 7883 "PrintCLike.cpp"
  append(L"TOKEN[");
                                                            #line 4632 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7887 "PrintCLike.cpp"
  append(L"l1]");
                                                            #line 4633 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 7891 "PrintCLike.cpp"
  append(L", ");
                                                            #line 4634 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 7895 "PrintCLike.cpp"
  append(L"b1, ");
                                                            #line 4635 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 7899 "PrintCLike.cpp"
  append(L"e1)");
                                                            #line 4636 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                            #line 7904 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4639 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 7908 "PrintCLike.cpp"
  append(L"b0 = ");
                                                            #line 4640 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 7912 "PrintCLike.cpp"
  append(L"b1; ");
                                                            #line 4641 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 7916 "PrintCLike.cpp"
  append(L"e0 = ");
                                                            #line 4642 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 7920 "PrintCLike.cpp"
  append(L"e1;");
                                                            #line 4643 "PrintCLike.cpp.template"
                                                                for (size_t k = 1; k < grammar->k; ++k)
                                                                {
                                                            #line 7925 "PrintCLike.cpp"
  append(L" ");
                                                            #line 4645 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 7929 "PrintCLike.cpp"
  append(L"l");
                                                            #line 4646 "PrintCLike.cpp.template"
                                                                  print(format.toString<wchar_t>(k));
                                                            #line 7933 "PrintCLike.cpp"
  append(L" = ");
                                                            #line 4647 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 7937 "PrintCLike.cpp"
  append(L"l");
                                                            #line 4648 "PrintCLike.cpp.template"
                                                                  print(format.toString<wchar_t>(k + 1));
                                                                  print(isPython() ? L"\n" : L"; ");
                                                            #line 7942 "PrintCLike.cpp"
  append(L"if ");
                                                            #line 4650 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                                  print(thiz());
                                                            #line 7947 "PrintCLike.cpp"
  append(L"l");
                                                            #line 4652 "PrintCLike.cpp.template"
                                                                  print(format.toString<wchar_t>(k));
                                                            #line 7951 "PrintCLike.cpp"
  append(L" != 0");
                                                            #line 4653 "PrintCLike.cpp.template"
                                                                  print(ifRightParen());
                                                                  if (isPython())
                                                                  {
                                                                    increaseIndent();
                                                                  }
                                                                  else
                                                                  {
                                                            #line 7961 "PrintCLike.cpp"
  append(L" {");
                                                            #line 4660 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 7965 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4662 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 7969 "PrintCLike.cpp"
  append(L"b");
                                                            #line 4663 "PrintCLike.cpp.template"
                                                                  print(format.toString<wchar_t>(k));
                                                            #line 7973 "PrintCLike.cpp"
  append(L" = ");
                                                            #line 4664 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 7977 "PrintCLike.cpp"
  append(L"b");
                                                            #line 4665 "PrintCLike.cpp.template"
                                                                  print(format.toString<wchar_t>(k + 1));
                                                            #line 7981 "PrintCLike.cpp"
  append(L"; ");
                                                            #line 4666 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 7985 "PrintCLike.cpp"
  append(L"e");
                                                            #line 4667 "PrintCLike.cpp.template"
                                                                  print(format.toString<wchar_t>(k));
                                                            #line 7989 "PrintCLike.cpp"
  append(L" = ");
                                                            #line 4668 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 7993 "PrintCLike.cpp"
  append(L"e");
                                                            #line 4669 "PrintCLike.cpp.template"
                                                                  print(format.toString<wchar_t>(k + 1));
                                                            #line 7997 "PrintCLike.cpp"
  append(L";");
                                                            #line 4670 "PrintCLike.cpp.template"
                                                                }
                                                            #line 8001 "PrintCLike.cpp"
  append(L" ");
                                                            #line 4671 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 8005 "PrintCLike.cpp"
  append(L"l");
                                                            #line 4672 "PrintCLike.cpp.template"
                                                                print(format.toString<wchar_t>(grammar->k));
                                                            #line 8009 "PrintCLike.cpp"
  append(L" = 0");
                                                            #line 4673 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                if (grammar->k > 1)
                                                                {
                                                            #line 8015 "PrintCLike.cpp"
  append(L" ");
                                                            #line 4676 "PrintCLike.cpp.template"
                                                                  for (size_t k = 1; k < grammar->k; ++k)
                                                                  {
                                                                    if (! isPython())
                                                                    {
                                                            #line 8022 "PrintCLike.cpp"
  append(L"}");
                                                            #line 4680 "PrintCLike.cpp.template"
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
                                                            #line 8037 "PrintCLike.cpp"
  append(L"\n");
  append(L"  fprintf(stderr, \"  <parse terminal=\\\"%s\\\"%s%s%s/>\\n\", ");
                                                            #line 4693 "PrintCLike.cpp.template"
                                                                    if (stringIntroducer()[0])
                                                                    {
                                                            #line 8043 "PrintCLike.cpp"
  append(L"Utf8Encoder::encode(");
                                                            #line 4696 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 8047 "PrintCLike.cpp"
  append(L"xmlEscape(TOKEN[t], 0).c_str()");
                                                            #line 4698 "PrintCLike.cpp.template"
                                                                    if (stringIntroducer()[0])
                                                                    {
                                                            #line 8052 "PrintCLike.cpp"
  append(L").c_str()");
                                                            #line 4700 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 8056 "PrintCLike.cpp"
  append(L", (l1 == 0 ? \"\" : \" input=\\\"\"),  (l1 == 0 ? \"\" : ");
                                                            #line 4702 "PrintCLike.cpp.template"
                                                                    if (stringIntroducer()[0])
                                                                    {
                                                            #line 8061 "PrintCLike.cpp"
  append(L"Utf8Encoder::encode(");
                                                            #line 4705 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 8065 "PrintCLike.cpp"
  append(L"xmlEscape(lookaheadString().c_str(), 0).c_str()");
                                                            #line 4707 "PrintCLike.cpp.template"
                                                                    if (stringIntroducer()[0])
                                                                    {
                                                            #line 8070 "PrintCLike.cpp"
  append(L").c_str()");
                                                            #line 4709 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 8074 "PrintCLike.cpp"
  append(L"), (l1 == 0 ? \"\" : \"\\\"\"));");
                                                            #line 4711 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                                    if (isGo())
                                                                    {
                                                            #line 8082 "PrintCLike.cpp"
  append(L"\n");
  append(L"  var inputAttr string\n");
  append(L"  if (this.l1 == 0) {\n");
  append(L"    inputAttr = \"\"\n");
  append(L"  } else {\n");
  append(L"    inputAttr = \" input=\\\"\" + xmlEscape(this.lookaheadString()) + \"\\\"\"\n");
  append(L"  }");
                                                            #line 4722 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 8092 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4724 "PrintCLike.cpp.template"
                                                                    if (isHaxe())
                                                                    {
                                                            #line 8098 "PrintCLike.cpp"
  append(L"trace(");
                                                            #line 4727 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                                      print(writeTrace());
                                                                    }
                                                            #line 8106 "PrintCLike.cpp"
  append(L"\"  <parse terminal=\\\"\" + ");
                                                            #line 4732 "PrintCLike.cpp.template"
                                                                    print(staticPrefix());
                                                            #line 8110 "PrintCLike.cpp"
  append(L"xmlEscape(");
                                                            #line 4733 "PrintCLike.cpp.template"
                                                                    print(staticPrefix());
                                                                    print(isGo() ? L"token" : L"TOKEN");
                                                                    print(leftbracket());
                                                            #line 8116 "PrintCLike.cpp"
  append(L"t");
                                                            #line 4736 "PrintCLike.cpp.template"
                                                                    print(rightbracket());
                                                            #line 8120 "PrintCLike.cpp"
  append(L") + \"\\\"\" + ");
                                                            #line 4737 "PrintCLike.cpp.template"
                                                                    if (isGo())
                                                                    {
                                                            #line 8125 "PrintCLike.cpp"
  append(L"inputAttr");
                                                            #line 4739 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 8131 "PrintCLike.cpp"
  append(L"(");
                                                            #line 4742 "PrintCLike.cpp.template"
                                                                      if (isScala())
                                                                      {
                                                            #line 8136 "PrintCLike.cpp"
  append(L"if (l1 == 0) \"\" else");
                                                            #line 4744 "PrintCLike.cpp.template"
                                                                      }
                                                                      else if (isPython())
                                                                      {
                                                            #line 8142 "PrintCLike.cpp"
  append(L"\"\" if self.l1 == 0 else");
                                                            #line 4747 "PrintCLike.cpp.template"
                                                                      }
                                                                      else
                                                                      {
                                                                        print(thiz());
                                                            #line 8149 "PrintCLike.cpp"
  append(L"l1 == 0 ? \"\" :");
                                                            #line 4751 "PrintCLike.cpp.template"
                                                                      }
                                                            #line 8153 "PrintCLike.cpp"
  append(L" \" input=\\\"\" + ");
                                                            #line 4752 "PrintCLike.cpp.template"
                                                                      print(staticPrefix());
                                                            #line 8157 "PrintCLike.cpp"
  append(L"xmlEscape(");
                                                            #line 4753 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 8161 "PrintCLike.cpp"
  append(L"lookaheadString");
                                                            #line 4754 "PrintCLike.cpp.template"
                                                                      if (! isScala()) print(L"()");
                                                            #line 8165 "PrintCLike.cpp"
  append(L") + \"\\\"\")");
                                                            #line 4755 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 8169 "PrintCLike.cpp"
  append(L" + \"/>");
                                                            #line 4756 "PrintCLike.cpp.template"
                                                                    if (isHaxe())
                                                                    {
                                                            #line 8174 "PrintCLike.cpp"
  append(L"\")");
                                                            #line 4758 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 8180 "PrintCLike.cpp"
  append(L"\\n\"");
                                                            #line 4761 "PrintCLike.cpp.template"
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
                                                            #line 8194 "PrintCLike.cpp"
  append(L"el");
                                                            #line 4772 "PrintCLike.cpp.template"
                                                                    if (! isPython())
                                                                    {
                                                            #line 8199 "PrintCLike.cpp"
  append(L"se ");
                                                            #line 4774 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 8203 "PrintCLike.cpp"
  append(L"if ");
                                                            #line 4775 "PrintCLike.cpp.template"
                                                                    print(ifLeftParen());
                                                                    print(thiz());
                                                                    print(token());
                                                            #line 8209 "PrintCLike.cpp"
  append(L" < 0");
                                                            #line 4778 "PrintCLike.cpp.template"
                                                                    print(ifRightParen());
                                                                    print(leftBrace());
                                                            #line 8214 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4781 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8219 "PrintCLike.cpp"
  append(L"error(");
                                                            #line 4782 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8223 "PrintCLike.cpp"
  append(L"b1, ");
                                                            #line 4783 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8227 "PrintCLike.cpp"
  append(L"e1, -");
                                                            #line 4784 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8231 "PrintCLike.cpp"
  append(L"l1, 0, 0)");
                                                            #line 4785 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                    if (i == 0)
                                                                    {
                                                            #line 8237 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4789 "PrintCLike.cpp.template"
                                                                      print(beginThrowStmt());
                                                                      print(thiz());
                                                            #line 8243 "PrintCLike.cpp"
  append(L"bx, ");
                                                            #line 4791 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 8247 "PrintCLike.cpp"
  append(L"ex, ");
                                                            #line 4792 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 8251 "PrintCLike.cpp"
  append(L"sx, ");
                                                            #line 4793 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 8255 "PrintCLike.cpp"
  append(L"lx, ");
                                                            #line 4794 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 8259 "PrintCLike.cpp"
  append(L"tx");
                                                            #line 4795 "PrintCLike.cpp.template"
                                                                      print(endThrowStmt());
                                                                      print(semicolon());
                                                                    }
                                                                    print(rightBrace());
                                                                  }
                                                                  print(isGo() ? L" " : L"\n");
                                                            #line 8268 "PrintCLike.cpp"
  append(L"else");
                                                            #line 4801 "PrintCLike.cpp.template"
                                                                  if (isPython()) print(L":");
                                                                  print(leftBrace());
                                                            #line 8273 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4804 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8278 "PrintCLike.cpp"
  append(L"error(");
                                                            #line 4805 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8282 "PrintCLike.cpp"
  append(L"b1, ");
                                                            #line 4806 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8286 "PrintCLike.cpp"
  append(L"e1, 0, ");
                                                            #line 4807 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8290 "PrintCLike.cpp"
  append(L"l1, t)");
                                                            #line 4808 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                  if (i == 0 && grammar->noThrow)
                                                                  {
                                                            #line 8296 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4812 "PrintCLike.cpp.template"
                                                                    print(beginThrowStmt());
                                                                    print(thiz());
                                                            #line 8302 "PrintCLike.cpp"
  append(L"bx, ");
                                                            #line 4814 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8306 "PrintCLike.cpp"
  append(L"ex, ");
                                                            #line 4815 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8310 "PrintCLike.cpp"
  append(L"sx, ");
                                                            #line 4816 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8314 "PrintCLike.cpp"
  append(L"lx, ");
                                                            #line 4817 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8318 "PrintCLike.cpp"
  append(L"tx");
                                                            #line 4818 "PrintCLike.cpp.template"
                                                                    print(endThrowStmt());
                                                                    print(semicolon());
                                                                  }
                                                                  print(rightBrace());
                                                                }
                                                                else
                                                                {
                                                                  print(isGo() ? L" " : L"\n");
                                                            #line 8329 "PrintCLike.cpp"
  append(L"else");
                                                            #line 4826 "PrintCLike.cpp.template"
                                                                  if (isPython()) print(L":");
                                                                  print(leftBrace());
                                                            #line 8334 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4829 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8339 "PrintCLike.cpp"
  append(L"error(");
                                                            #line 4830 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8343 "PrintCLike.cpp"
  append(L"b1, ");
                                                            #line 4831 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8347 "PrintCLike.cpp"
  append(L"e1, 0, ");
                                                            #line 4832 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8351 "PrintCLike.cpp"
  append(L"l1, t)");
                                                            #line 4833 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                  print(rightBrace());
                                                                }
                                                                decreaseIndent();
                                                                print(rightBrace());
                                                            #line 8359 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4839 "PrintCLike.cpp.template"
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
                                                            #line 8378 "PrintCLike.cpp"
  append(L"\n");
  append(L"  var thread = new ParsingThread().copy(thisThread, 0);\n");
  append(L"  thread.setL1(code);\n");
  append(L"  thread.setB1(begin);\n");
  append(L"  thread.setE1(end);");
                                                            #line 4859 "PrintCLike.cpp.template"
                                                                    }
                                                                    else if (isGo())
                                                                    {
                                                            #line 8388 "PrintCLike.cpp"
  append(L"\n");
  append(L"  thread := new(ParsingThread).copy(this, 0)\n");
  append(L"  thread.l1 = code\n");
  append(L"  thread.b1 = this.begin\n");
  append(L"  thread.e1 = this.end");
                                                            #line 4866 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 8398 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4870 "PrintCLike.cpp.template"
                                                                      if (isHaxe() || isScala() || isTypescript())
                                                                      {
                                                            #line 8404 "PrintCLike.cpp"
  append(L"var ");
                                                            #line 4872 "PrintCLike.cpp.template"
                                                                      }
                                                                      else if (! isPython())
                                                                      {
                                                            #line 8410 "PrintCLike.cpp"
  append(L"ParsingThread ");
                                                            #line 4875 "PrintCLike.cpp.template"
                                                                      }
                                                                      if (isCpp()) print(L"*");
                                                            #line 8415 "PrintCLike.cpp"
  append(L"thread = ");
                                                            #line 4877 "PrintCLike.cpp.template"
                                                                      if (isCpp()) print(L"(");
                                                                      if (! isPython())
                                                                      {
                                                            #line 8421 "PrintCLike.cpp"
  append(L"new ");
                                                            #line 4880 "PrintCLike.cpp.template"
                                                                      }
                                                                      if (isScala() || isPython())
                                                                      {
                                                                        print(className.c_str());
                                                            #line 8428 "PrintCLike.cpp"
  append(L".");
                                                            #line 4884 "PrintCLike.cpp.template"
                                                                      }
                                                            #line 8432 "PrintCLike.cpp"
  append(L"ParsingThread()");
                                                            #line 4885 "PrintCLike.cpp.template"
                                                                      if (isCpp()) print(L")");
                                                                      print(arrow());
                                                            #line 8437 "PrintCLike.cpp"
  append(L"copy(");
                                                            #line 4887 "PrintCLike.cpp.template"
                                                                      if (isPython())
                                                                      {
                                                            #line 8442 "PrintCLike.cpp"
  append(L"self");
                                                            #line 4889 "PrintCLike.cpp.template"
                                                                      }
                                                                      else
                                                                      {
                                                            #line 8448 "PrintCLike.cpp"
  append(L"this");
                                                            #line 4892 "PrintCLike.cpp.template"
                                                                      }
                                                            #line 8452 "PrintCLike.cpp"
  append(L", 0)");
                                                            #line 4893 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                                      if (isCpp())
                                                                      {
                                                            #line 8458 "PrintCLike.cpp"
  append(L"\n");
  append(L"  thread->stack->unshare();\n");
  append(L"  thread->stack = 0;");
                                                            #line 4898 "PrintCLike.cpp.template"
                                                                      }
                                                            #line 8464 "PrintCLike.cpp"
  append(L"\n");
  append(L"  thread");
                                                            #line 4900 "PrintCLike.cpp.template"
                                                                      print(arrow());
                                                            #line 8469 "PrintCLike.cpp"
  append(L"l1 = code");
                                                            #line 4901 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                            #line 8473 "PrintCLike.cpp"
  append(L"\n");
  append(L"  thread");
                                                            #line 4903 "PrintCLike.cpp.template"
                                                                      print(arrow());
                                                            #line 8478 "PrintCLike.cpp"
  append(L"b1 = ");
                                                            #line 4904 "PrintCLike.cpp.template"
                                                                      if (useGlr) print(thiz());
                                                            #line 8482 "PrintCLike.cpp"
  append(L"begin");
                                                            #line 4905 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                            #line 8486 "PrintCLike.cpp"
  append(L"\n");
  append(L"  thread");
                                                            #line 4907 "PrintCLike.cpp.template"
                                                                      print(arrow());
                                                            #line 8491 "PrintCLike.cpp"
  append(L"e1 = ");
                                                            #line 4908 "PrintCLike.cpp.template"
                                                                      if (useGlr) print(thiz());
                                                            #line 8495 "PrintCLike.cpp"
  append(L"end");
                                                            #line 4909 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                                    }
                                                                  }
                                                                  else
                                                                  {
                                                            #line 8503 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4915 "PrintCLike.cpp.template"
                                                                    print(intVal());
                                                            #line 8508 "PrintCLike.cpp"
  append(L"b0W");
                                                            #line 4916 "PrintCLike.cpp.template"
                                                                    print(assign());
                                                                    print(thiz());
                                                            #line 8513 "PrintCLike.cpp"
  append(L"b0; ");
                                                            #line 4918 "PrintCLike.cpp.template"
                                                                    print(intVal());
                                                            #line 8517 "PrintCLike.cpp"
  append(L"e0W");
                                                            #line 4919 "PrintCLike.cpp.template"
                                                                    print(assign());
                                                                    print(thiz());
                                                            #line 8522 "PrintCLike.cpp"
  append(L"e0");
                                                            #line 4922 "PrintCLike.cpp.template"
                                                                    for (size_t k = 1; k < grammar->k; ++k)
                                                                    {
                                                            #line 8527 "PrintCLike.cpp"
  append(L"; ");
                                                            #line 4924 "PrintCLike.cpp.template"
                                                                      print(intVal());
                                                            #line 8531 "PrintCLike.cpp"
  append(L"l");
                                                            #line 4925 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(k));
                                                            #line 8535 "PrintCLike.cpp"
  append(L"W");
                                                            #line 4926 "PrintCLike.cpp.template"
                                                                      print(assign());
                                                                      print(thiz());
                                                            #line 8540 "PrintCLike.cpp"
  append(L"l");
                                                            #line 4928 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(k));
                                                                      print(semicolon());
                                                            #line 8545 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4931 "PrintCLike.cpp.template"
                                                                      print(intVal());
                                                            #line 8550 "PrintCLike.cpp"
  append(L"b");
                                                            #line 4932 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(k));
                                                            #line 8554 "PrintCLike.cpp"
  append(L"W");
                                                            #line 4933 "PrintCLike.cpp.template"
                                                                      print(assign());
                                                                      print(thiz());
                                                            #line 8559 "PrintCLike.cpp"
  append(L"b");
                                                            #line 4935 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(k));
                                                            #line 8563 "PrintCLike.cpp"
  append(L"; ");
                                                            #line 4936 "PrintCLike.cpp.template"
                                                                      print(intVal());
                                                            #line 8567 "PrintCLike.cpp"
  append(L"e");
                                                            #line 4937 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(k));
                                                            #line 8571 "PrintCLike.cpp"
  append(L"W");
                                                            #line 4938 "PrintCLike.cpp.template"
                                                                      print(assign());
                                                                      print(thiz());
                                                            #line 8576 "PrintCLike.cpp"
  append(L"e");
                                                            #line 4940 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(k));
                                                                    }
                                                                    print(semicolon());
                                                            #line 8582 "PrintCLike.cpp"
  append(L"\n");
  append(L"\n");
  append(L"  ");
                                                            #line 4945 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8588 "PrintCLike.cpp"
  append(L"l1 = code; ");
                                                            #line 4946 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8592 "PrintCLike.cpp"
  append(L"b1 = ");
                                                            #line 4947 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8596 "PrintCLike.cpp"
  append(L"begin; ");
                                                            #line 4948 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8600 "PrintCLike.cpp"
  append(L"e1 = ");
                                                            #line 4949 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8604 "PrintCLike.cpp"
  append(L"end");
                                                            #line 4950 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                    for (size_t k = 2; k <= grammar->k; ++k)
                                                                    {
                                                            #line 8610 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4954 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 8615 "PrintCLike.cpp"
  append(L"l");
                                                            #line 4955 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(k));
                                                            #line 8619 "PrintCLike.cpp"
  append(L" = 0");
                                                            #line 4956 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                                    }
                                                                  }
                                                                  if (isLrParser)
                                                                  {
                                                            #line 8627 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4962 "PrintCLike.cpp.template"
                                                                    if (useGlr)
                                                                    {
                                                                      if (! isCpp())
                                                                      {
                                                            #line 8635 "PrintCLike.cpp"
  append(L"thread = ");
                                                            #line 4966 "PrintCLike.cpp.template"
                                                                      }
                                                                      if (isJava())
                                                                      {
                                                                        print(className.c_str());
                                                            #line 8642 "PrintCLike.cpp"
  append(L".this.");
                                                            #line 4970 "PrintCLike.cpp.template"
                                                                      }
                                                                      else if (isCSharp() || isCpp() || isHaxe() || isScala() || isTypescript() || isGo() || isPython())
                                                                      {
                                                                        print(thiz());
                                                            #line 8649 "PrintCLike.cpp"
  append(L"parser");
                                                            #line 4974 "PrintCLike.cpp.template"
                                                                        print(arrow());
                                                                      }
                                                                    }
                                                                    else
                                                                    {
                                                                      print(thiz());
                                                                    }
                                                            #line 8659 "PrintCLike.cpp"
  append(L"parse(-1, ");
                                                            #line 4981 "PrintCLike.cpp.template"
                                                                    print(format.toString<wchar_t>(grammar->whitespace->getStateId()));
                                                                    if (tree)
                                                                    {
                                                            #line 8665 "PrintCLike.cpp"
  append(L", ");
                                                            #line 4984 "PrintCLike.cpp.template"
                                                                      print(nullPtr());
                                                                    }
                                                                    if (useGlr)
                                                                    {
                                                            #line 8672 "PrintCLike.cpp"
  append(L", thread");
                                                            #line 4988 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 8676 "PrintCLike.cpp"
  append(L")");
                                                            #line 4989 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                  }
                                                                  else
                                                                  {
                                                            #line 8683 "PrintCLike.cpp"
  append(L"\n");
  append(L"\n");
  append(L"  ");
                                                            #line 4995 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8689 "PrintCLike.cpp"
  append(L"try_");
                                                            #line 4996 "PrintCLike.cpp.template"
                                                                    print(Format::acceptableName<WString>(grammar->whitespace->name).c_str());
                                                                    if (! isScala()) print(L"()");
                                                                    print(semicolon());
                                                                  }
                                                                  if (useGlr)
                                                                  {
                                                                    if (isJavascript())
                                                                    {
                                                            #line 8700 "PrintCLike.cpp"
  append(L"\n");
  append(L"  end = thread.getEnd();");
                                                            #line 5005 "PrintCLike.cpp.template"
                                                                    }
                                                                    else if (isCpp())
                                                                    {
                                                            #line 8707 "PrintCLike.cpp"
  append(L"\n");
  append(L"  end = thread->end;\n");
  append(L"  delete thread;");
                                                            #line 5010 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 8715 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5014 "PrintCLike.cpp.template"
                                                                      if (useGlr) print(thiz());
                                                            #line 8720 "PrintCLike.cpp"
  append(L"end = thread");
                                                            #line 5015 "PrintCLike.cpp.template"
                                                                      print(arrow());
                                                            #line 8724 "PrintCLike.cpp"
  append(L"end");
                                                            #line 5016 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                                    }
                                                                  }
                                                                  else
                                                                  {
                                                            #line 8732 "PrintCLike.cpp"
  append(L"\n");
  append(L"\n");
  append(L"  ");
                                                            #line 5023 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8738 "PrintCLike.cpp"
  append(L"b0 = b0W; ");
                                                            #line 5024 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8742 "PrintCLike.cpp"
  append(L"e0 = e0W");
                                                            #line 5025 "PrintCLike.cpp.template"
                                                                    for (size_t k = 1; k < grammar->k; ++k)
                                                                    {
                                                            #line 8747 "PrintCLike.cpp"
  append(L"; ");
                                                            #line 5027 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 8751 "PrintCLike.cpp"
  append(L"l");
                                                            #line 5028 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(k));
                                                            #line 8755 "PrintCLike.cpp"
  append(L" = l");
                                                            #line 5029 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(k));
                                                            #line 8759 "PrintCLike.cpp"
  append(L"W");
                                                            #line 5030 "PrintCLike.cpp.template"
                                                                      if (isPython())
                                                                      {
                                                            #line 8764 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5033 "PrintCLike.cpp.template"
                                                                      }
                                                                      else
                                                                      {
                                                            #line 8771 "PrintCLike.cpp"
  append(L"; ");
                                                            #line 5036 "PrintCLike.cpp.template"
                                                                      }
                                                            #line 8775 "PrintCLike.cpp"
  append(L"if ");
                                                            #line 5037 "PrintCLike.cpp.template"
                                                                      print(ifLeftParen());
                                                                      print(thiz());
                                                            #line 8780 "PrintCLike.cpp"
  append(L"l");
                                                            #line 5039 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(k));
                                                            #line 8784 "PrintCLike.cpp"
  append(L" != 0");
                                                            #line 5040 "PrintCLike.cpp.template"
                                                                      print(ifRightParen());
                                                                      if (isPython())
                                                                      {
                                                                        increaseIndent();
                                                                      }
                                                                      else
                                                                      {
                                                            #line 8794 "PrintCLike.cpp"
  append(L" {");
                                                            #line 5047 "PrintCLike.cpp.template"
                                                                      }
                                                            #line 8798 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5049 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 8803 "PrintCLike.cpp"
  append(L"b");
                                                            #line 5050 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(k));
                                                            #line 8807 "PrintCLike.cpp"
  append(L" = b");
                                                            #line 5051 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(k));
                                                            #line 8811 "PrintCLike.cpp"
  append(L"W; ");
                                                            #line 5052 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 8815 "PrintCLike.cpp"
  append(L"e");
                                                            #line 5053 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(k));
                                                            #line 8819 "PrintCLike.cpp"
  append(L" = e");
                                                            #line 5054 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(k));
                                                            #line 8823 "PrintCLike.cpp"
  append(L"W");
                                                            #line 5055 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(semicolon());
                                                                    if (isPython())
                                                                    {
                                                                      decreaseIndent(grammar->k - 1);
                                                                    }
                                                                    else
                                                                    {
                                                            #line 8834 "PrintCLike.cpp"
  append(L" ");
                                                            #line 5063 "PrintCLike.cpp.template"
                                                                      for (size_t k = 1; k < grammar->k; ++k)
                                                                      {
                                                            #line 8839 "PrintCLike.cpp"
  append(L"}");
                                                            #line 5065 "PrintCLike.cpp.template"
                                                                      }
                                                                    }
                                                                  }
                                                                  print(rightBrace());
                                                            #line 8846 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5070 "PrintCLike.cpp.template"
                                                                  if (! isGo())
                                                                    decreaseIndent();
                                                                }
                                                                if (tree && ! isLrParser)
                                                                {
                                                                  if (! isGo())
                                                                    increaseIndent();
                                                                  openMethod (voidType(), L"", L"whitespace", L"");
                                                                  print(leftBrace());
                                                            #line 8858 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if ");
                                                            #line 5080 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                                  print(thiz());
                                                            #line 8864 "PrintCLike.cpp"
  append(L"e0 != ");
                                                            #line 5082 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8868 "PrintCLike.cpp"
  append(L"b1");
                                                            #line 5083 "PrintCLike.cpp.template"
                                                                  print(ifRightParen());
                                                                  increaseIndent();
                                                                  print(leftBrace());
                                                                  decreaseIndent();
                                                            #line 8875 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 5088 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8880 "PrintCLike.cpp"
  append(L"eventHandler");
                                                            #line 5089 "PrintCLike.cpp.template"
                                                                  print(arrow());
                                                                  if (isGo())
                                                                  {
                                                            #line 8886 "PrintCLike.cpp"
  append(L"W");
                                                            #line 5092 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 8892 "PrintCLike.cpp"
  append(L"w");
                                                            #line 5095 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 8896 "PrintCLike.cpp"
  append(L"hitespace(");
                                                            #line 5096 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8900 "PrintCLike.cpp"
  append(L"e0, ");
                                                            #line 5097 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8904 "PrintCLike.cpp"
  append(L"b1)");
                                                            #line 5098 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                            #line 8908 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 5100 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8913 "PrintCLike.cpp"
  append(L"e0 = ");
                                                            #line 5101 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8917 "PrintCLike.cpp"
  append(L"b1");
                                                            #line 5102 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                  increaseIndent();
                                                                  print(rightBrace());
                                                                  decreaseIndent();
                                                                  print(rightBrace());
                                                                  if (! isGo())
                                                                    decreaseIndent();
                                                            #line 8927 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5110 "PrintCLike.cpp.template"
                                                                }
                                                                if (! isGo())
                                                                  increaseIndent();
                                                                openMethod(intType(), L"", L"matchW", L"int tokenSetId", false, useGlr ? L"ParsingThread" : className.c_str());
                                                                print(leftBrace());
                                                                if (isScala())
                                                                {
                                                            #line 8937 "PrintCLike.cpp"
  append(L"\n");
  append(L"  var continue = true\n");
  append(L"  var code = 0\n");
  append(L"  while (continue) {\n");
  append(L"    code = matcher(tokenSetId)");
                                                            #line 5121 "PrintCLike.cpp.template"
                                                                  increaseIndent(2);
                                                                }
                                                                else
                                                                {
                                                                  if (! isPython())
                                                                  {
                                                            #line 8950 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5128 "PrintCLike.cpp.template"
                                                                    print((isJavascript() || isTypescript() || isHaxe() || isGo()) ? L"var" : L"int");
                                                            #line 8955 "PrintCLike.cpp"
  append(L" code");
                                                            #line 5129 "PrintCLike.cpp.template"
                                                                    if (isTypescript())
                                                                    {
                                                            #line 8960 "PrintCLike.cpp"
  append(L": number");
                                                            #line 5131 "PrintCLike.cpp.template"
                                                                    }
                                                                    else if (isGo())
                                                                    {
                                                            #line 8966 "PrintCLike.cpp"
  append(L" int");
                                                            #line 5134 "PrintCLike.cpp.template"
                                                                    }
                                                                    if (isHaxe())
                                                                    {
                                                            #line 8972 "PrintCLike.cpp"
  append(L" = 0");
                                                            #line 5137 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(semicolon());
                                                                  }
                                                                  if (isHaxe() || isPython())
                                                                  {
                                                            #line 8980 "PrintCLike.cpp"
  append(L"\n");
  append(L"  while ");
                                                            #line 5143 "PrintCLike.cpp.template"
                                                                    print(ifLeftParen());
                                                                    print(isPython() ? L"T" : L"t");
                                                            #line 8986 "PrintCLike.cpp"
  append(L"rue");
                                                            #line 5145 "PrintCLike.cpp.template"
                                                                    print(ifRightParen());
                                                                  }
                                                                  else
                                                                  {
                                                            #line 8993 "PrintCLike.cpp"
  append(L"\n");
  append(L"  for");
                                                            #line 5150 "PrintCLike.cpp.template"
                                                                    if (! isGo())
                                                                    {
                                                            #line 8999 "PrintCLike.cpp"
  append(L" (;;)");
                                                            #line 5152 "PrintCLike.cpp.template"
                                                                    }
                                                                  }
                                                                  increaseIndent();
                                                                  print(leftBrace());
                                                                  increaseIndent();
                                                            #line 9007 "PrintCLike.cpp"
  append(L"\n");
  append(L"code = ");
                                                            #line 5158 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 9012 "PrintCLike.cpp"
  append(L"match(tokenSetId)");
                                                            #line 5159 "PrintCLike.cpp.template"
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
                                                            #line 9041 "PrintCLike.cpp"
  append(L"\n");
  append(L"  continue = false\n");
  append(L"}\n");
  append(L"else {\n");
  append(L"  ");
                                                            #line 5189 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 9049 "PrintCLike.cpp"
  append(L"skip(code)\n");
  append(L"}");
                                                            #line 5191 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 9056 "PrintCLike.cpp"
  append(L"\n");
  append(L"  break");
                                                            #line 5195 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                    print(rightBrace());
                                                            #line 9062 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5198 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 9066 "PrintCLike.cpp"
  append(L"skip(code);");
                                                            #line 5199 "PrintCLike.cpp.template"
                                                                  }
                                                                }
                                                                else if (isScala())
                                                                {
                                                            #line 9073 "PrintCLike.cpp"
  append(L"\n");
  append(L"continue = false");
                                                            #line 5204 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 9080 "PrintCLike.cpp"
  append(L"\n");
  append(L"break");
                                                            #line 5208 "PrintCLike.cpp.template"
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
                                                            #line 9094 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5219 "PrintCLike.cpp.template"
                                                                if (! isScala())
                                                                {
                                                            #line 9100 "PrintCLike.cpp"
  append(L"return ");
                                                            #line 5221 "PrintCLike.cpp.template"
                                                                }
                                                            #line 9104 "PrintCLike.cpp"
  append(L"code");
                                                            #line 5222 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                print(rightBrace());
                                                            #line 9109 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5225 "PrintCLike.cpp.template"
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
                                                            #line 9125 "PrintCLike.cpp"
  append(L"\n");
  append(L"def parse(): Unit = {\n");
  append(L"  parse_");
                                                            #line 5240 "PrintCLike.cpp.template"
                                                                  print(Format::acceptableName<WString>(grammar->startSymbol()->name).c_str());
                                                            #line 9131 "PrintCLike.cpp"
  append(L"()\n");
  append(L"}\n");
                                                            #line 5243 "PrintCLike.cpp.template"
                                                                }
                                                                if (memoization)
                                                                {
                                                                  int bits = Math::bits(grammar->conflictCount);
                                                            #line 9139 "PrintCLike.cpp"
  append(L"\n");
  append(L"private def memoize(i: Int, e: Int, v: Int): Unit = {\n");
  append(L"  memo.put((e << ");
                                                            #line 5249 "PrintCLike.cpp.template"
                                                                  print(format.toString<wchar_t>(bits));
                                                            #line 9145 "PrintCLike.cpp"
  append(L") + i, v)\n");
  append(L"}\n");
  append(L"\n");
  append(L"private def memoized(i: Int, e: Int) = {\n");
  append(L"  memo.getOrElse((e << ");
                                                            #line 5254 "PrintCLike.cpp.template"
                                                                  print(format.toString<wchar_t>(bits));
                                                            #line 9153 "PrintCLike.cpp"
  append(L") + i, 0)\n");
  append(L"}\n");
                                                            #line 5257 "PrintCLike.cpp.template"
                                                                }
                                                            #line 9158 "PrintCLike.cpp"
  append(L"\n");
  append(L"def error(b: Int, e: Int, s: Int, l: Int, t: Int): Int = {");
                                                            #line 5259 "PrintCLike.cpp.template"
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
                                                            #line 9172 "PrintCLike.cpp"
  append(L"\n");
  append(L"if ");
                                                            #line 5270 "PrintCLike.cpp.template"
                                                                print(ifLeftParen());
                                                                if (grammar->noThrow)
                                                                {
                                                                  print(thiz());
                                                            #line 9180 "PrintCLike.cpp"
  append(L"viable ");
                                                            #line 5274 "PrintCLike.cpp.template"
                                                                  if (isPython())
                                                                  {
                                                            #line 9185 "PrintCLike.cpp"
  append(L"and");
                                                            #line 5276 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 9191 "PrintCLike.cpp"
  append(L"&&");
                                                            #line 5279 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 9195 "PrintCLike.cpp"
  append(L" ");
                                                            #line 5280 "PrintCLike.cpp.template"
                                                                }
                                                            #line 9199 "PrintCLike.cpp"
  append(L"e >= ");
                                                            #line 5281 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 9203 "PrintCLike.cpp"
  append(L"ex");
                                                            #line 5282 "PrintCLike.cpp.template"
                                                                print(ifRightParen());
                                                                print(leftBrace());
                                                            #line 9208 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5285 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 9213 "PrintCLike.cpp"
  append(L"bx = b");
                                                            #line 5286 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 9217 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5288 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 9222 "PrintCLike.cpp"
  append(L"ex = e");
                                                            #line 5289 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 9226 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5291 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 9231 "PrintCLike.cpp"
  append(L"sx = s");
                                                            #line 5292 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 9235 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5294 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 9240 "PrintCLike.cpp"
  append(L"lx = l");
                                                            #line 5295 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 9244 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5297 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 9249 "PrintCLike.cpp"
  append(L"tx = t");
                                                            #line 5298 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                print(rightBrace());
                                                                decreaseIndent();
                                                                if (grammar->noThrow)
                                                                {
                                                            #line 9257 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5304 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 9262 "PrintCLike.cpp"
  append(L"viable = ");
                                                            #line 5305 "PrintCLike.cpp.template"
                                                                  if (isPython())
                                                                  {
                                                            #line 9267 "PrintCLike.cpp"
  append(L"F");
                                                            #line 5307 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 9273 "PrintCLike.cpp"
  append(L"f");
                                                            #line 5310 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 9277 "PrintCLike.cpp"
  append(L"alse");
                                                            #line 5311 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                            #line 9281 "PrintCLike.cpp"
  append(L"\n");
  append(L"  return -s");
                                                            #line 5313 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                                else
                                                                {
                                                                  printFlush(1, true);
                                                            #line 9290 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5319 "PrintCLike.cpp.template"
                                                                  print(beginThrowStmt());
                                                                  print(thiz());
                                                            #line 9296 "PrintCLike.cpp"
  append(L"bx, ");
                                                            #line 5321 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 9300 "PrintCLike.cpp"
  append(L"ex, ");
                                                            #line 5322 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 9304 "PrintCLike.cpp"
  append(L"sx, ");
                                                            #line 5323 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 9308 "PrintCLike.cpp"
  append(L"lx, ");
                                                            #line 5324 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 9312 "PrintCLike.cpp"
  append(L"tx");
                                                            #line 5325 "PrintCLike.cpp.template"
                                                                  print(endThrowStmt());
                                                                  print(semicolon());
                                                                }
                                                              }
                                                              else
                                                              {
                                                                printFlush(1, true);
                                                            #line 9322 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5333 "PrintCLike.cpp.template"
                                                                if (isGo())
                                                                {
                                                            #line 9328 "PrintCLike.cpp"
  append(L"panic(&ParseError{b, e, s, l, t");
                                                            #line 5335 "PrintCLike.cpp.template"
                                                                  if (useGlr)
                                                                  {
                                                            #line 9333 "PrintCLike.cpp"
  append(L", false");
                                                            #line 5337 "PrintCLike.cpp.template"
                                                                    if (tree)
                                                                    {
                                                            #line 9338 "PrintCLike.cpp"
  append(L", nil");
                                                            #line 5339 "PrintCLike.cpp.template"
                                                                    }
                                                                  }
                                                            #line 9343 "PrintCLike.cpp"
  append(L"})");
                                                            #line 5341 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                                  print(beginThrowStmt());
                                                            #line 9350 "PrintCLike.cpp"
  append(L"b, e, s, l, t");
                                                            #line 5345 "PrintCLike.cpp.template"
                                                                  print(endThrowStmt());
                                                                  print(semicolon());
                                                                }
                                                              }
                                                              print(rightBrace());
                                                            #line 9358 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5351 "PrintCLike.cpp.template"
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
                                                            #line 9383 "PrintCLike.cpp"
  append(L"\n");
  append(L"i := lookback[y]\n");
  append(L"l := lookback[i]\n");
  append(L"for l > x {");
                                                            #line 5376 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 9392 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5380 "PrintCLike.cpp.template"
                                                                  print(intVar());
                                                            #line 9396 "PrintCLike.cpp"
  append(L"i");
                                                            #line 5381 "PrintCLike.cpp.template"
                                                                  print(assign());
                                                                  print(staticPrefix());
                                                                  print(lookback);
                                                                  print(leftbracket());
                                                            #line 9403 "PrintCLike.cpp"
  append(L"y");
                                                            #line 5385 "PrintCLike.cpp.template"
                                                                  print(rightbracket());
                                                                  print(semicolon());
                                                            #line 9408 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5388 "PrintCLike.cpp.template"
                                                                  print(intVar());
                                                            #line 9412 "PrintCLike.cpp"
  append(L"l");
                                                            #line 5389 "PrintCLike.cpp.template"
                                                                  print(assign());
                                                                  print(staticPrefix());
                                                                  print(lookback);
                                                                  print(leftbracket());
                                                            #line 9419 "PrintCLike.cpp"
  append(L"i");
                                                            #line 5393 "PrintCLike.cpp.template"
                                                                  print(rightbracket());
                                                                  print(semicolon());
                                                            #line 9424 "PrintCLike.cpp"
  append(L"\n");
  append(L"while ");
                                                            #line 5396 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                            #line 9429 "PrintCLike.cpp"
  append(L"l > x");
                                                            #line 5397 "PrintCLike.cpp.template"
                                                                  print(ifRightParen());
                                                                  print(leftBrace());
                                                                }
                                                            #line 9435 "PrintCLike.cpp"
  append(L"\n");
  append(L"  i += 2");
                                                            #line 5401 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 9440 "PrintCLike.cpp"
  append(L"\n");
  append(L"  l = ");
                                                            #line 5403 "PrintCLike.cpp.template"
                                                                print(staticPrefix());
                                                                print(lookback);
                                                                print(leftbracket());
                                                            #line 9447 "PrintCLike.cpp"
  append(L"i");
                                                            #line 5406 "PrintCLike.cpp.template"
                                                                print(rightbracket());
                                                                print(semicolon());
                                                                print(rightBrace());
                                                            #line 9453 "PrintCLike.cpp"
  append(L"\n");
  append(L"if ");
                                                            #line 5410 "PrintCLike.cpp.template"
                                                                print(ifLeftParen());
                                                            #line 9458 "PrintCLike.cpp"
  append(L"l < x");
                                                            #line 5411 "PrintCLike.cpp.template"
                                                                print(ifRightParen());
                                                                print(leftBrace());
                                                            #line 9463 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5414 "PrintCLike.cpp.template"
                                                                print(returnKeyword());
                                                            #line 9468 "PrintCLike.cpp"
  append(L"0");
                                                            #line 5415 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 9472 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5417 "PrintCLike.cpp.template"
                                                                print(elseWithBraces());
                                                            #line 9476 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5419 "PrintCLike.cpp.template"
                                                                print(returnKeyword());
                                                                print(staticPrefix());
                                                                print(lookback);
                                                                print(leftbracket());
                                                            #line 9484 "PrintCLike.cpp"
  append(L"i + 1");
                                                            #line 5423 "PrintCLike.cpp.template"
                                                                print(rightbracket());
                                                                print(semicolon());
                                                                print(rightBrace());
                                                                decreaseIndent();
                                                                print(rightBrace());
                                                            #line 9492 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5429 "PrintCLike.cpp.template"
                                                                if (isJavascript() && useGlr)
                                                                {
                                                            #line 9497 "PrintCLike.cpp"
  append(L"\n");
  append(L"this.count = function(code)\n");
                                                            #line 5433 "PrintCLike.cpp.template"
                                                                }
                                                                else if (isTypescript() && useGlr)
                                                                {
                                                            #line 9504 "PrintCLike.cpp"
  append(L"\n");
  append(L"public count(code: number)\n");
                                                            #line 5438 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                                  openMethod(intType(), L"", L"count", L"int code", false, clazz);
                                                                }
                                                                print(leftBrace());
                                                                increaseIndent();
                                                            #line 9515 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5446 "PrintCLike.cpp.template"
                                                                print(intVar());
                                                            #line 9519 "PrintCLike.cpp"
  append(L"count");
                                                            #line 5447 "PrintCLike.cpp.template"
                                                                print(assign());
                                                            #line 9523 "PrintCLike.cpp"
  append(L"0");
                                                            #line 5448 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                int stackElementSize = tree ? 3 : 2;
                                                                if (isHaxe() || isScala())
                                                                {
                                                                  if (useGlr)
                                                                  {
                                                            #line 9532 "PrintCLike.cpp"
  append(L"\n");
  append(L"var node = this");
                                                            #line 5455 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                    if (isScala())
                                                                    {
                                                            #line 9539 "PrintCLike.cpp"
  append(L"\n");
  append(L"var c = code");
                                                            #line 5459 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 9544 "PrintCLike.cpp"
  append(L"\n");
  append(L"while ");
                                                            #line 5461 "PrintCLike.cpp.template"
                                                                    print(ifLeftParen());
                                                            #line 9549 "PrintCLike.cpp"
  append(L"node.state >= 0");
                                                            #line 5462 "PrintCLike.cpp.template"
                                                                    print(ifRightParen());
                                                                    print(leftBrace());
                                                                    if (isScala())
                                                                    {
                                                            #line 9556 "PrintCLike.cpp"
  append(L"\n");
  append(L"  c = lookback(node.code, c)\n");
  append(L"  if (c == 0) return count\n");
  append(L"  count += 1");
                                                            #line 5469 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 9565 "PrintCLike.cpp"
  append(L"\n");
  append(L"  code = lookback(node.code, code);\n");
  append(L"  if ");
                                                            #line 5474 "PrintCLike.cpp.template"
                                                                      print(ifLeftParen());
                                                            #line 9571 "PrintCLike.cpp"
  append(L"code == 0");
                                                            #line 5475 "PrintCLike.cpp.template"
                                                                      print(ifRightParen());
                                                            #line 9575 "PrintCLike.cpp"
  append(L"\n");
  append(L"    break");
                                                            #line 5478 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                            #line 9580 "PrintCLike.cpp"
  append(L"\n");
  append(L"  count++");
                                                            #line 5480 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                                    }
                                                            #line 9586 "PrintCLike.cpp"
  append(L"\n");
  append(L"  node = node.link");
                                                            #line 5483 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                  }
                                                                  else
                                                                  {
                                                            #line 9594 "PrintCLike.cpp"
  append(L"\n");
  append(L"var t = top");
                                                            #line 5488 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 9599 "PrintCLike.cpp"
  append(L"\n");
  append(L"var c = code");
                                                            #line 5490 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 9604 "PrintCLike.cpp"
  append(L"\n");
  append(L"while (t >= 0)");
                                                            #line 5492 "PrintCLike.cpp.template"
                                                                    print(leftBrace());
                                                            #line 9609 "PrintCLike.cpp"
  append(L"\n");
  append(L"  c = lookback(iStack");
                                                            #line 5494 "PrintCLike.cpp.template"
                                                                    print(leftbracket());
                                                            #line 9614 "PrintCLike.cpp"
  append(L"t");
                                                            #line 5495 "PrintCLike.cpp.template"
                                                                    print(rightbracket());
                                                            #line 9618 "PrintCLike.cpp"
  append(L", c)");
                                                            #line 5496 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 9622 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if ");
                                                            #line 5498 "PrintCLike.cpp.template"
                                                                    print(ifLeftParen());
                                                            #line 9627 "PrintCLike.cpp"
  append(L"c == 0");
                                                            #line 5499 "PrintCLike.cpp.template"
                                                                    print(ifRightParen());
                                                            #line 9631 "PrintCLike.cpp"
  append(L" return count");
                                                            #line 5500 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 9635 "PrintCLike.cpp"
  append(L"\n");
  append(L"  count += 1");
                                                            #line 5502 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 9640 "PrintCLike.cpp"
  append(L"\n");
  append(L"  t -= ");
                                                            #line 5504 "PrintCLike.cpp.template"
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
                                                            #line 9654 "PrintCLike.cpp"
  append(L"\n");
  append(L"node = self\n");
  append(L"while ");
                                                            #line 5516 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 9662 "PrintCLike.cpp"
  append(L"\n");
  append(L"for ");
                                                            #line 5520 "PrintCLike.cpp.template"
                                                                      print(ifLeftParen());
                                                                      if (isJavascript() || isTypescript())
                                                                      {
                                                            #line 9669 "PrintCLike.cpp"
  append(L"var ");
                                                            #line 5523 "PrintCLike.cpp.template"
                                                                      }
                                                                      else if (!isGo())
                                                                      {
                                                            #line 9675 "PrintCLike.cpp"
  append(L"StackNode ");
                                                            #line 5526 "PrintCLike.cpp.template"
                                                                      }
                                                                      if (isCpp()) print(L"*");
                                                            #line 9680 "PrintCLike.cpp"
  append(L"node");
                                                            #line 5528 "PrintCLike.cpp.template"
                                                                      if (isTypescript())
                                                                      {
                                                            #line 9685 "PrintCLike.cpp"
  append(L": StackNode | null");
                                                            #line 5530 "PrintCLike.cpp.template"
                                                                      }
                                                                      print(assign());
                                                            #line 9690 "PrintCLike.cpp"
  append(L"this; ");
                                                            #line 5532 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 9694 "PrintCLike.cpp"
  append(L"node");
                                                            #line 5533 "PrintCLike.cpp.template"
                                                                    if (isTypescript()) print(L"!");
                                                                    print(arrow());
                                                            #line 9699 "PrintCLike.cpp"
  append(L"state >= 0");
                                                            #line 5535 "PrintCLike.cpp.template"
                                                                    if (isPython())
                                                                    {
                                                            #line 9704 "PrintCLike.cpp"
  append(L":");
                                                            #line 5537 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 9710 "PrintCLike.cpp"
  append(L"; node = node");
                                                            #line 5540 "PrintCLike.cpp.template"
                                                                      if (isTypescript()) print(L"!");
                                                                      print(arrow());
                                                            #line 9715 "PrintCLike.cpp"
  append(L"link");
                                                            #line 5542 "PrintCLike.cpp.template"
                                                                      print(ifRightParen());
                                                                    }
                                                                    print(leftBrace());
                                                            #line 9721 "PrintCLike.cpp"
  append(L"\n");
  append(L"  code = ");
                                                            #line 5546 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                                    print(isGo() ? L"L" : L"l");
                                                            #line 9727 "PrintCLike.cpp"
  append(L"ookback(node");
                                                            #line 5548 "PrintCLike.cpp.template"
                                                                    if (isTypescript()) print(L"!");
                                                                    print(arrow());
                                                            #line 9732 "PrintCLike.cpp"
  append(L"code, code)");
                                                            #line 5550 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                  }
                                                                  else
                                                                  {
                                                                    if (isPython())
                                                                    {
                                                            #line 9741 "PrintCLike.cpp"
  append(L"\n");
  append(L"t");
                                                            #line 5557 "PrintCLike.cpp.template"
                                                                      print(assign());
                                                                      print(thiz());
                                                            #line 9747 "PrintCLike.cpp"
  append(L"top");
                                                            #line 5559 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                            #line 9751 "PrintCLike.cpp"
  append(L"\n");
  append(L"while ");
                                                            #line 5561 "PrintCLike.cpp.template"
                                                                      print(ifLeftParen());
                                                                      print(intVar());
                                                            #line 9757 "PrintCLike.cpp"
  append(L"t >= 0");
                                                            #line 5563 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 9763 "PrintCLike.cpp"
  append(L"\n");
  append(L"for ");
                                                            #line 5567 "PrintCLike.cpp.template"
                                                                      print(ifLeftParen());
                                                                      print(intVar());
                                                            #line 9769 "PrintCLike.cpp"
  append(L"t");
                                                            #line 5569 "PrintCLike.cpp.template"
                                                                      print(assign());
                                                                      print(thiz());
                                                            #line 9774 "PrintCLike.cpp"
  append(L"top; t >= 0; t -= ");
                                                            #line 5571 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(stackElementSize));
                                                                    }
                                                                    print(ifRightParen());
                                                                    print(leftBrace());
                                                            #line 9781 "PrintCLike.cpp"
  append(L"\n");
  append(L"  code = ");
                                                            #line 5576 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 9786 "PrintCLike.cpp"
  append(L"lookback(");
                                                            #line 5577 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 9790 "PrintCLike.cpp"
  append(L"iStack[t], code)");
                                                            #line 5578 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                  }
                                                            #line 9795 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if ");
                                                            #line 5581 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                            #line 9800 "PrintCLike.cpp"
  append(L"code == 0");
                                                            #line 5582 "PrintCLike.cpp.template"
                                                                  print(ifRightParen());
                                                                  increaseIndent();
                                                                  print(leftBrace());
                                                            #line 9806 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5586 "PrintCLike.cpp.template"
                                                                  if (! isHaxe() && ! isScala())
                                                                  {
                                                            #line 9812 "PrintCLike.cpp"
  append(L"break");
                                                            #line 5588 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 9818 "PrintCLike.cpp"
  append(L"return count");
                                                            #line 5591 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(semicolon());
                                                                  print(rightBrace());
                                                                  decreaseIndent();
                                                            #line 9825 "PrintCLike.cpp"
  append(L"\n");
  append(L"  count += 1");
                                                            #line 5596 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                  if (isPython())
                                                                  {
                                                                    if (useGlr)
                                                                    {
                                                            #line 9834 "PrintCLike.cpp"
  append(L"\n");
  append(L"  node = node.link");
                                                            #line 5602 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 9841 "PrintCLike.cpp"
  append(L"\n");
  append(L"  t -= ");
                                                            #line 5606 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(stackElementSize));
                                                                    }
                                                                  }
                                                                }
                                                                print(rightBrace());
                                                            #line 9850 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5612 "PrintCLike.cpp.template"
                                                                print(returnKeyword());
                                                            #line 9854 "PrintCLike.cpp"
  append(L"count");
                                                            #line 5613 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                decreaseIndent();
                                                                print(rightBrace());
                                                                if (isJavascript() && useGlr)
                                                                {
                                                            #line 9862 "PrintCLike.cpp"
  append(L";");
                                                            #line 5618 "PrintCLike.cpp.template"
                                                                }
                                                            #line 9866 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5620 "PrintCLike.cpp.template"
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
                                                            #line 9891 "PrintCLike.cpp"
  append(L"\n");
  append(L"if ");
                                                            #line 5643 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                                  print(thiz());
                                                            #line 9897 "PrintCLike.cpp"
  append(L"l");
                                                            #line 5645 "PrintCLike.cpp.template"
                                                                  print(kAsString);
                                                            #line 9901 "PrintCLike.cpp"
  append(L" == 0");
                                                            #line 5646 "PrintCLike.cpp.template"
                                                                  print(ifRightParen());
                                                                  print(leftBrace());
                                                            #line 9906 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5649 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 9911 "PrintCLike.cpp"
  append(L"l");
                                                            #line 5650 "PrintCLike.cpp.template"
                                                                  print(kAsString);
                                                            #line 9915 "PrintCLike.cpp"
  append(L" = ");
                                                            #line 5651 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 9919 "PrintCLike.cpp"
  append(L"match");
                                                            #line 5652 "PrintCLike.cpp.template"
                                                                  if (withWhitespace)
                                                                  {
                                                            #line 9924 "PrintCLike.cpp"
  append(L"W");
                                                            #line 5654 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isScala())
                                                                  {
                                                            #line 9930 "PrintCLike.cpp"
  append(L"er");
                                                            #line 5657 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 9934 "PrintCLike.cpp"
  append(L"(tokenSetId)");
                                                            #line 5658 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                            #line 9938 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5660 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 9943 "PrintCLike.cpp"
  append(L"b");
                                                            #line 5661 "PrintCLike.cpp.template"
                                                                  print(kAsString);
                                                            #line 9947 "PrintCLike.cpp"
  append(L" = ");
                                                            #line 5662 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 9951 "PrintCLike.cpp"
  append(L"begin");
                                                            #line 5663 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                            #line 9955 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5665 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 9960 "PrintCLike.cpp"
  append(L"e");
                                                            #line 5666 "PrintCLike.cpp.template"
                                                                  print(kAsString);
                                                            #line 9964 "PrintCLike.cpp"
  append(L" = ");
                                                            #line 5667 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 9968 "PrintCLike.cpp"
  append(L"end");
                                                            #line 5668 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                  print(rightBrace());
                                                                  if (unlimitedLookahead)
                                                                  {
                                                                    if (k >= 2)
                                                                    {
                                                            #line 9977 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5675 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 9981 "PrintCLike.cpp"
  append(L"lk = prefix + ");
                                                            #line 5676 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 9985 "PrintCLike.cpp"
  append(L"l");
                                                            #line 5677 "PrintCLike.cpp.template"
                                                                      print(kAsString);
                                                                      print(semicolon());
                                                                    }
                                                                  }
                                                                  else
                                                                  {
                                                                    if (k == 2)
                                                                    {
                                                            #line 9996 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5686 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 10000 "PrintCLike.cpp"
  append(L"lk = (");
                                                            #line 5687 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 10004 "PrintCLike.cpp"
  append(L"l2 << ");
                                                            #line 5688 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(grammar->tokenSequenceFactory->tokenBits()));
                                                            #line 10008 "PrintCLike.cpp"
  append(L") | ");
                                                            #line 5689 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 10012 "PrintCLike.cpp"
  append(L"l1");
                                                            #line 5690 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                                    }
                                                                    else if (k > 2)
                                                                    {
                                                            #line 10019 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5695 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 10023 "PrintCLike.cpp"
  append(L"lk |= ");
                                                            #line 5696 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 10027 "PrintCLike.cpp"
  append(L"l");
                                                            #line 5697 "PrintCLike.cpp.template"
                                                                      print(kAsString);
                                                            #line 10031 "PrintCLike.cpp"
  append(L" << ");
                                                            #line 5698 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>((k - 1) * grammar->tokenSequenceFactory->tokenBits()));
                                                                      print(semicolon());
                                                                    }
                                                                  }
                                                                  decreaseIndent();
                                                                  print(rightBrace());
                                                            #line 10040 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5705 "PrintCLike.cpp.template"
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
                                                                                    ? L"CharSequence "
                                                                                    : isHaxe()
                                                                                    ? L"Bytes "
                                                                                    : stringType();
                                                                openMethod(type, L"", L"getInput", L"", true);
                                                                print(leftBrace());
                                                            #line 10068 "PrintCLike.cpp"
  append(L"\n");
  append(L"  return ");
                                                            #line 5731 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                                if (useGlr && (isCSharp() || isCpp() || isHaxe() || isScala() || isTypescript()))
                                                                {
                                                            #line 10075 "PrintCLike.cpp"
  append(L"parser");
                                                            #line 5734 "PrintCLike.cpp.template"
                                                                  print(arrow());
                                                                }
                                                            #line 10080 "PrintCLike.cpp"
  append(L"input");
                                                            #line 5736 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                print(rightBrace());
                                                                if (isJavascript())
                                                                {
                                                            #line 10087 "PrintCLike.cpp"
  append(L";");
                                                            #line 5740 "PrintCLike.cpp.template"
                                                                }
                                                            #line 10091 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5742 "PrintCLike.cpp.template"
                                                                openMethod(intType(), L"", L"getTokenOffset", L"", true);
                                                                print(leftBrace());
                                                            #line 10096 "PrintCLike.cpp"
  append(L"\n");
  append(L"  return ");
                                                            #line 5745 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 10101 "PrintCLike.cpp"
  append(L"b0");
                                                            #line 5746 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                print(rightBrace());
                                                                if (isJavascript())
                                                                {
                                                            #line 10108 "PrintCLike.cpp"
  append(L";");
                                                            #line 5750 "PrintCLike.cpp.template"
                                                                }
                                                            #line 10112 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5752 "PrintCLike.cpp.template"
                                                                openMethod(intType(), L"", L"getTokenEnd", L"", true);
                                                                print(leftBrace());
                                                            #line 10117 "PrintCLike.cpp"
  append(L"\n");
  append(L"  return ");
                                                            #line 5755 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 10122 "PrintCLike.cpp"
  append(L"e0");
                                                            #line 5756 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                print(rightBrace());
                                                                if (isJavascript())
                                                                {
                                                            #line 10129 "PrintCLike.cpp"
  append(L";");
                                                            #line 5760 "PrintCLike.cpp.template"
                                                                }
                                                            #line 10133 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5762 "PrintCLike.cpp.template"
                                                              }
                                                              if (isJavascript())
                                                              {
                                                                if (useGlr)
                                                                {
                                                            #line 10141 "PrintCLike.cpp"
  append(L"\n");
  append(L"this.reset = function");
                                                            #line 5768 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 10148 "PrintCLike.cpp"
  append(L"\n");
  append(L"function reset");
                                                            #line 5772 "PrintCLike.cpp.template"
                                                                }
                                                            #line 10153 "PrintCLike.cpp"
  append(L"(l, b, e)\n");
  append(L"{");
                                                            #line 5774 "PrintCLike.cpp.template"
                                                              }
                                                              else if (isTypescript())
                                                              {
                                                            #line 10160 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5778 "PrintCLike.cpp.template"
                                                                if (! performanceTest && ! useGlr)
                                                                {
                                                            #line 10165 "PrintCLike.cpp"
  append(L"private ");
                                                            #line 5780 "PrintCLike.cpp.template"
                                                                }
                                                            #line 10169 "PrintCLike.cpp"
  append(L"reset(l: number, b: number, e: number)\n");
  append(L"{");
                                                            #line 5782 "PrintCLike.cpp.template"
                                                              }
                                                              else if (isHaxe())
                                                              {
                                                            #line 10176 "PrintCLike.cpp"
  append(L"\n");
  append(L"public function reset(l, b, e)\n");
  append(L"{");
                                                            #line 5787 "PrintCLike.cpp.template"
                                                              }
                                                              else
                                                              {
                                                                openMethod(voidType(), isJava() ? L"final " : L"", L"reset", L"int l, int b, int e", false, useGlr ? L"ParsingThread" : className.c_str());
                                                                print(leftBrace());
                                                              }
                                                            #line 10187 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5794 "PrintCLike.cpp.template"
                                                              if (! isPython() && ! isScala())
                                                              {
                                                            #line 10193 "PrintCLike.cpp"
  append(L"        ");
                                                            #line 5796 "PrintCLike.cpp.template"
                                                                print(wcslen(thiz()), L" ");
                                                              }
                                                              print(thiz());
                                                            #line 10199 "PrintCLike.cpp"
  append(L"b0 = b; ");
                                                            #line 5799 "PrintCLike.cpp.template"
                                                              print(thiz());
                                                            #line 10203 "PrintCLike.cpp"
  append(L"e0 = b");
                                                            #line 5800 "PrintCLike.cpp.template"
                                                              print(semicolon());
                                                            #line 10207 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5802 "PrintCLike.cpp.template"
                                                              print(thiz());
                                                            #line 10212 "PrintCLike.cpp"
  append(L"l1 = l; ");
                                                            #line 5803 "PrintCLike.cpp.template"
                                                              print(thiz());
                                                            #line 10216 "PrintCLike.cpp"
  append(L"b1 = b; ");
                                                            #line 5804 "PrintCLike.cpp.template"
                                                              print(thiz());
                                                            #line 10220 "PrintCLike.cpp"
  append(L"e1 = e");
                                                            #line 5805 "PrintCLike.cpp.template"
                                                              print(semicolon());
                                                              for (size_t k = 2; k <= grammar->k; ++k)
                                                              {
                                                            #line 10226 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5809 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 10231 "PrintCLike.cpp"
  append(L"l");
                                                            #line 5810 "PrintCLike.cpp.template"
                                                                print(format.toString<wchar_t>(k));
                                                            #line 10235 "PrintCLike.cpp"
  append(L" = 0; ");
                                                            #line 5811 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 10239 "PrintCLike.cpp"
  append(L"b");
                                                            #line 5812 "PrintCLike.cpp.template"
                                                                print(format.toString<wchar_t>(k));
                                                            #line 10243 "PrintCLike.cpp"
  append(L" = 0; ");
                                                            #line 5813 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 10247 "PrintCLike.cpp"
  append(L"e");
                                                            #line 5814 "PrintCLike.cpp.template"
                                                                print(format.toString<wchar_t>(k));
                                                            #line 10251 "PrintCLike.cpp"
  append(L" = 0");
                                                            #line 5815 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                              }
                                                            #line 10256 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5818 "PrintCLike.cpp.template"
                                                              print(thiz());
                                                            #line 10261 "PrintCLike.cpp"
  append(L"end = e");
                                                            #line 5819 "PrintCLike.cpp.template"
                                                              print(semicolon());
                                                              if (hasBacktracking)
                                                              {
                                                            #line 10267 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5823 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 10272 "PrintCLike.cpp"
  append(L"ex = -1");
                                                            #line 5824 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                if (memoization)
                                                                {
                                                                  if (isJavascript() || isTypescript())
                                                                  {
                                                            #line 10280 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5830 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 10285 "PrintCLike.cpp"
  append(L"memo = {};");
                                                            #line 5831 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isCSharp())
                                                                  {
                                                            #line 10291 "PrintCLike.cpp"
  append(L"\n");
  append(L"  memo.Clear();");
                                                            #line 5835 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isScala())
                                                                  {
                                                            #line 10298 "PrintCLike.cpp"
  append(L"\n");
  append(L"  memo.clear");
                                                            #line 5839 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isHaxe())
                                                                  {
                                                            #line 10305 "PrintCLike.cpp"
  append(L"\n");
  append(L"  memo = new Map();");
                                                            #line 5843 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isGo())
                                                                  {
                                                            #line 10312 "PrintCLike.cpp"
  append(L"\n");
  append(L"  this.memo = make(map[int]int)");
                                                            #line 5847 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isPython())
                                                                  {
                                                            #line 10319 "PrintCLike.cpp"
  append(L"\n");
  append(L"  self.memo = {}");
                                                            #line 5851 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 10326 "PrintCLike.cpp"
  append(L"\n");
  append(L"  memo.clear();");
                                                            #line 5855 "PrintCLike.cpp.template"
                                                                  }
                                                                }
                                                                if (grammar->noThrow)
                                                                {
                                                            #line 10334 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5860 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 10339 "PrintCLike.cpp"
  append(L"viable = ");
                                                            #line 5861 "PrintCLike.cpp.template"
                                                                  if (isPython())
                                                                  {
                                                            #line 10344 "PrintCLike.cpp"
  append(L"T");
                                                            #line 5863 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 10350 "PrintCLike.cpp"
  append(L"t");
                                                            #line 5866 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 10354 "PrintCLike.cpp"
  append(L"rue");
                                                            #line 5867 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                              }
                                                              if (tree && ! useGlr)
                                                              {
                                                            #line 10362 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5873 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 10367 "PrintCLike.cpp"
  append(L"eventHandler");
                                                            #line 5874 "PrintCLike.cpp.template"
                                                                if (isTypescript() && isLrParser) print(L"!");
                                                                print(arrow());
                                                                if (isGo())
                                                                {
                                                            #line 10374 "PrintCLike.cpp"
  append(L"R");
                                                            #line 5878 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 10380 "PrintCLike.cpp"
  append(L"r");
                                                            #line 5881 "PrintCLike.cpp.template"
                                                                }
                                                            #line 10384 "PrintCLike.cpp"
  append(L"eset(");
                                                            #line 5882 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 10388 "PrintCLike.cpp"
  append(L"input)");
                                                            #line 5883 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                              }
                                                              if (useGlr)
                                                              {
                                                            #line 10395 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5888 "PrintCLike.cpp.template"
                                                                if (isCSharp() || isCpp() || isHaxe() || isScala() || isTypescript() || isGo())
                                                                {
                                                                  print(thiz());
                                                            #line 10402 "PrintCLike.cpp"
  append(L"parser");
                                                            #line 5891 "PrintCLike.cpp.template"
                                                                  print(arrow());
                                                                }
                                                            #line 10407 "PrintCLike.cpp"
  append(L"maxId = 0");
                                                            #line 5893 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 10411 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5895 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 10416 "PrintCLike.cpp"
  append(L"id = ");
                                                            #line 5896 "PrintCLike.cpp.template"
                                                                if (isCSharp() || isCpp() || isHaxe() || isScala() || isTypescript() || isGo())
                                                                {
                                                                  print(thiz());
                                                            #line 10422 "PrintCLike.cpp"
  append(L"parser");
                                                            #line 5899 "PrintCLike.cpp.template"
                                                                   print(arrow());
                                                                }
                                                            #line 10427 "PrintCLike.cpp"
  append(L"maxId");
                                                            #line 5901 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                              }
                                                              print(rightBrace());
                                                              if (isJavascript() && useGlr)
                                                              {
                                                            #line 10435 "PrintCLike.cpp"
  append(L";");
                                                            #line 5906 "PrintCLike.cpp.template"
                                                              }
                                                            #line 10439 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5908 "PrintCLike.cpp.template"
                                                              if (useGlr || isJavascript() || isTypescript() || isHaxe() || isGo() || isPython())
                                                              {
                                                              }
                                                              else
                                                              {
                                                                openMethod(voidType(), L"", L"reset", L"");
                                                                print(leftBrace());
                                                            #line 10449 "PrintCLike.cpp"
  append(L"\n");
  append(L"  reset(0, 0, 0)");
                                                            #line 5916 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                print(rightBrace());
                                                            #line 10455 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5919 "PrintCLike.cpp.template"
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
                                                            #line 10483 "PrintCLike.cpp"
  append(L"\n");
  append(L"if ");
                                                            #line 5945 "PrintCLike.cpp.template"
                                                                    print(ifLeftParen());
                                                            #line 10488 "PrintCLike.cpp"
  append(L"(");
                                                            #line 5946 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                                    print(token());
                                                            #line 10493 "PrintCLike.cpp"
  append(L" == ");
                                                            #line 5948 "PrintCLike.cpp.template"
                                                                    print(format.toString<wchar_t>(grammar->externalTokenCode[plusplus]));
                                                                    if (isPython())
                                                                    {
                                                            #line 10499 "PrintCLike.cpp"
  append(L" or ");
                                                            #line 5951 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 10505 "PrintCLike.cpp"
  append(L" || ");
                                                            #line 5954 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(thiz());
                                                                    print(token());
                                                            #line 10511 "PrintCLike.cpp"
  append(L" == ");
                                                            #line 5957 "PrintCLike.cpp.template"
                                                                    print(format.toString<wchar_t>(grammar->externalTokenCode[minusminus]));
                                                            #line 10515 "PrintCLike.cpp"
  append(L")");
                                                            #line 5959 "PrintCLike.cpp.template"
                                                                    if (isPython())
                                                                    {
                                                            #line 10520 "PrintCLike.cpp"
  append(L" and ");
                                                            #line 5961 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 10526 "PrintCLike.cpp"
  append(L" && ");
                                                            #line 5964 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(thiz());
                                                            #line 10531 "PrintCLike.cpp"
  append(L"followsLineTerminator");
                                                            #line 5966 "PrintCLike.cpp.template"
                                                                    if (! isScala())
                                                                    {
                                                            #line 10536 "PrintCLike.cpp"
  append(L"()");
                                                            #line 5968 "PrintCLike.cpp.template"
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
                                                            #line 10550 "PrintCLike.cpp"
  append(L"\n");
  append(L"if ");
                                                            #line 5980 "PrintCLike.cpp.template"
                                                                    print(ifLeftParen());
                                                                    print(thiz());
                                                                    print(token());
                                                            #line 10557 "PrintCLike.cpp"
  append(L" != ");
                                                            #line 5983 "PrintCLike.cpp.template"
                                                                    print(format.toString<wchar_t>(grammar->externalTokenCode[semicolonToken]));
                                                                    if (isPython())
                                                                    {
                                                            #line 10563 "PrintCLike.cpp"
  append(L" and ");
                                                            #line 5986 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 10569 "PrintCLike.cpp"
  append(L" && ");
                                                            #line 5989 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(thiz());
                                                                    print(token());
                                                            #line 10575 "PrintCLike.cpp"
  append(L" >= 0");
                                                            #line 5993 "PrintCLike.cpp.template"
                                                                    if (isPython())
                                                                    {
                                                            #line 10580 "PrintCLike.cpp"
  append(L" and ");
                                                            #line 5995 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 10586 "PrintCLike.cpp"
  append(L" && ");
                                                            #line 5998 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(thiz());
                                                            #line 10591 "PrintCLike.cpp"
  append(L"followsLineTerminator");
                                                            #line 6000 "PrintCLike.cpp.template"
                                                                    if (! isScala())
                                                                    {
                                                            #line 10596 "PrintCLike.cpp"
  append(L"()");
                                                            #line 6002 "PrintCLike.cpp.template"
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
                                                            #line 10611 "PrintCLike.cpp"
  append(L"\n");
  append(L"if ");
                                                            #line 6015 "PrintCLike.cpp.template"
                                                                    print(isPython() ? L"(" : ifLeftParen());
                                                                    print(thiz());
                                                                    print(token());
                                                            #line 10618 "PrintCLike.cpp"
  append(L" == ");
                                                            #line 6018 "PrintCLike.cpp.template"
                                                                    print(format.toString<wchar_t>(grammar->externalTokenCode[rbrace]));
                                                                    if (isPython())
                                                                    {
                                                            #line 10624 "PrintCLike.cpp"
  append(L" or");
                                                            #line 6021 "PrintCLike.cpp.template"
                                                                    }
                                                                    else if (isGo())
                                                                    {
                                                            #line 10630 "PrintCLike.cpp"
  append(L" ||");
                                                            #line 6024 "PrintCLike.cpp.template"
                                                                    }
                                                                    printCodeSequenceAnnotation(grammar->tokenSequence(rbrace));
                                                                    if (isGo() || isPython())
                                                                    {
                                                            #line 10637 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 6029 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 10644 "PrintCLike.cpp"
  append(L"\n");
  append(L" || ");
                                                            #line 6033 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(thiz());
                                                                    print(token());
                                                            #line 10651 "PrintCLike.cpp"
  append(L" == ");
                                                            #line 6036 "PrintCLike.cpp.template"
                                                                    print(format.toString<wchar_t>(grammar->externalTokenCode[eof]));
                                                                    if (isPython())
                                                                    {
                                                            #line 10657 "PrintCLike.cpp"
  append(L" or");
                                                            #line 6039 "PrintCLike.cpp.template"
                                                                    }
                                                                    else if (isGo())
                                                                    {
                                                            #line 10663 "PrintCLike.cpp"
  append(L" ||");
                                                            #line 6042 "PrintCLike.cpp.template"
                                                                    }
                                                                    printCodeSequenceAnnotation(grammar->tokenSequence(eof));
                                                                    if (isGo() || isPython())
                                                                    {
                                                            #line 10670 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 6047 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 10677 "PrintCLike.cpp"
  append(L"\n");
  append(L" || ");
                                                            #line 6051 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(thiz());
                                                                    print(token());
                                                            #line 10684 "PrintCLike.cpp"
  append(L" != ");
                                                            #line 6054 "PrintCLike.cpp.template"
                                                                    print(format.toString<wchar_t>(grammar->externalTokenCode[semicolonToken]));
                                                                    if (isPython())
                                                                    {
                                                            #line 10690 "PrintCLike.cpp"
  append(L" and ");
                                                            #line 6057 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 10696 "PrintCLike.cpp"
  append(L" && ");
                                                            #line 6060 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(thiz());
                                                                    print(token());
                                                            #line 10702 "PrintCLike.cpp"
  append(L" >= 0");
                                                            #line 6064 "PrintCLike.cpp.template"
                                                                    if (isPython())
                                                                    {
                                                            #line 10707 "PrintCLike.cpp"
  append(L" and ");
                                                            #line 6066 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 10713 "PrintCLike.cpp"
  append(L" && ");
                                                            #line 6069 "PrintCLike.cpp.template"
                                                                    }
                                                                    if (afterRbrace)
                                                                    {
                                                            #line 10719 "PrintCLike.cpp"
  append(L"(");
                                                            #line 6072 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(thiz());
                                                            #line 10724 "PrintCLike.cpp"
  append(L"followsLineTerminator");
                                                            #line 6074 "PrintCLike.cpp.template"
                                                                    if (! isScala())
                                                                    {
                                                            #line 10729 "PrintCLike.cpp"
  append(L"()");
                                                            #line 6076 "PrintCLike.cpp.template"
                                                                    }
                                                                    if (afterRbrace)
                                                                    {
                                                                      if (isPython())
                                                                      {
                                                            #line 10737 "PrintCLike.cpp"
  append(L" || ");
                                                            #line 6081 "PrintCLike.cpp.template"
                                                                      }
                                                                      else
                                                                      {
                                                            #line 10743 "PrintCLike.cpp"
  append(L" or ");
                                                            #line 6084 "PrintCLike.cpp.template"
                                                                      }
                                                                      if (isCpp() || isCSharp() || isPython())
                                                                      {
                                                                        print(thiz());
                                                            #line 10750 "PrintCLike.cpp"
  append(L"input");
                                                            #line 6089 "PrintCLike.cpp.template"
                                                            
                                                            #line 10754 "PrintCLike.cpp"
  append(L"[");
                                                            #line 6089 "PrintCLike.cpp.template"
                                                                        print(thiz());
                                                            #line 10758 "PrintCLike.cpp"
  append(L"b0]");
                                                            #line 6090 "PrintCLike.cpp.template"
                                                                      }
                                                                      else
                                                                      {
                                                                        print(thiz());
                                                            #line 10765 "PrintCLike.cpp"
  append(L"input.char");
                                                            #line 6094 "PrintCLike.cpp.template"
                                                                        if (isTypescript() || isJavascript() || isHaxe())
                                                                        {
                                                            #line 10770 "PrintCLike.cpp"
  append(L"Code");
                                                            #line 6097 "PrintCLike.cpp.template"
                                                                        }
                                                            #line 10774 "PrintCLike.cpp"
  append(L"At(");
                                                            #line 6098 "PrintCLike.cpp.template"
                                                                       print(thiz());
                                                            #line 10778 "PrintCLike.cpp"
  append(L"b0)");
                                                            #line 6100 "PrintCLike.cpp.template"
                                                                      }
                                                            #line 10782 "PrintCLike.cpp"
  append(L" == 0x7D)");
                                                            #line 6101 "PrintCLike.cpp.template"
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
                                                            #line 10795 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 6112 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 10800 "PrintCLike.cpp"
  append(L"l1 = ");
                                                            #line 6113 "PrintCLike.cpp.template"
                                                                print(format.toString<wchar_t>(grammar->externalTokenCode[semicolonToken]));
                                                                print(semicolon());
                                                            #line 10805 "PrintCLike.cpp"
  append(L" ");
                                                            #line 6115 "PrintCLike.cpp.template"
                                                                printCodeSequenceAnnotation(grammar->tokenSequence(semicolonToken));
                                                            #line 10809 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 6117 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 10814 "PrintCLike.cpp"
  append(L"e1 = ");
                                                            #line 6118 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 10818 "PrintCLike.cpp"
  append(L"b1");
                                                            #line 6119 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 10822 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 6121 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 10827 "PrintCLike.cpp"
  append(L"end = ");
                                                            #line 6122 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 10831 "PrintCLike.cpp"
  append(L"e1");
                                                            #line 6123 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                print(rightBrace());
                                                              }
                                                            }

// End
