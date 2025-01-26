// This file was generated on Sun Jan 26, 2025 19:55 (UTC+01) by REx v6.1 which is Copyright (c) 1979-2025 by Gunther Rademacher <grd@gmx.net>
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
                                                                        ? L"BottomUpEventHandler "
                                                                        : isTypescript()
                                                                        ? L"ParsingEventHandler "
                                                                        : L"EventHandler ";
                                                                  if (isCpp()) args += L"*";
                                                                  args += L"parsingEventHandler";
                                                                }
                                                                openMethod(voidType(), L"", L"initialize", args.c_str());
                                                              }
                                                              print(leftBrace());
                                                              if (tree)
                                                              {
                                                            #line 2465 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 1755 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 2470 "PrintCLike.cpp"
  append(L"eventHandler = parsingEventHandler");
                                                            #line 1756 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                              }
                                                            #line 2475 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 1759 "PrintCLike.cpp.template"
                                                              print(thiz());
                                                            #line 2480 "PrintCLike.cpp"
  append(L"input = ");
                                                            #line 1760 "PrintCLike.cpp.template"
                                                              if (isHaxe())
                                                              {
                                                            #line 2485 "PrintCLike.cpp"
  append(L"Bytes.ofString(source)");
                                                            #line 1762 "PrintCLike.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 2491 "PrintCLike.cpp"
  append(L"source");
                                                            #line 1765 "PrintCLike.cpp.template"
                                                              }
                                                              print(semicolon());
                                                              if (noLexer)
                                                              {
                                                            #line 2498 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 1770 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 2503 "PrintCLike.cpp"
  append(L"lexer = l");
                                                            #line 1771 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 2507 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 1773 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 2512 "PrintCLike.cpp"
  append(L"lexer.reset(input)");
                                                            #line 1774 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                              }
                                                              else if (isGo() || isPython())
                                                              {
                                                            #line 2519 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 1779 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 2524 "PrintCLike.cpp"
  append(L"size = len(source)");
                                                            #line 1780 "PrintCLike.cpp.template"
                                                              }
                                                              else if (! isCpp())
                                                              {
                                                            #line 2530 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 1784 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 2535 "PrintCLike.cpp"
  append(L"size = source.");
                                                            #line 1785 "PrintCLike.cpp.template"
                                                                print(isCSharp() ? L"L" : L"l");
                                                            #line 2539 "PrintCLike.cpp"
  append(L"ength");
                                                            #line 1786 "PrintCLike.cpp.template"
                                                                if (! isJavascript() && ! isTypescript() && ! isScala() && ! isHaxe() && ! isCSharp())
                                                                {
                                                            #line 2544 "PrintCLike.cpp"
  append(L"()");
                                                            #line 1788 "PrintCLike.cpp.template"
                                                                }
                                                                print(semicolon());
                                                              }
                                                              if (! interfaceName.empty() && useGlr)
                                                              {
                                                            #line 2552 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 1794 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                                print(isGo() ? L"R" : L"r");
                                                            #line 2558 "PrintCLike.cpp"
  append(L"eset()");
                                                            #line 1796 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                print(rightBrace());
                                                            #line 2563 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 1799 "PrintCLike.cpp.template"
                                                                openMethod(voidType(), L"", L"reset", L"");
                                                                print(leftBrace());
                                                              }
                                                              if (isLrParser && ! useGlr)
                                                              {
                                                                if (isPython())
                                                                {
                                                            #line 2573 "PrintCLike.cpp"
  append(L"\n");
  append(L"  self.iStack = [0 for _ in range(192)]");
                                                            #line 1807 "PrintCLike.cpp.template"
                                                                }
                                                                else if (isGo())
                                                                {
                                                            #line 2580 "PrintCLike.cpp"
  append(L"\n");
  append(L"  this.iStack = make([]int, 192)\n");
  append(L"  this.top = -1");
                                                            #line 1812 "PrintCLike.cpp.template"
                                                                }
                                                              }
                                                              if (useGlr)
                                                              {
                                                            #line 2589 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 1817 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 2594 "PrintCLike.cpp"
  append(L"maxId = 0");
                                                            #line 1818 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 2598 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 1820 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 2603 "PrintCLike.cpp"
  append(L"thread = ");
                                                            #line 1821 "PrintCLike.cpp.template"
                                                                if (isScala())
                                                                {
                                                            #line 2608 "PrintCLike.cpp"
  append(L"new ");
                                                            #line 1823 "PrintCLike.cpp.template"
                                                                  print(className.c_str());
                                                            #line 2612 "PrintCLike.cpp"
  append(L".ParsingThread");
                                                            #line 1824 "PrintCLike.cpp.template"
                                                                }
                                                                else if (isPython())
                                                                {
                                                                  print(className.c_str());
                                                            #line 2619 "PrintCLike.cpp"
  append(L".ParsingThread()");
                                                            #line 1828 "PrintCLike.cpp.template"
                                                                }
                                                                else if (isGo())
                                                                {
                                                            #line 2625 "PrintCLike.cpp"
  append(L"new(ParsingThread)");
                                                            #line 1831 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 2631 "PrintCLike.cpp"
  append(L"new ParsingThread()");
                                                            #line 1834 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                                if (isCSharp() || isCpp() || isHaxe() || isScala() || isTypescript() || isGo() || isPython())
                                                                {
                                                            #line 2638 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 1839 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 2643 "PrintCLike.cpp"
  append(L"thread");
                                                            #line 1840 "PrintCLike.cpp.template"
                                                                  print(arrow());
                                                            #line 2647 "PrintCLike.cpp"
  append(L"parser = ");
                                                            #line 1841 "PrintCLike.cpp.template"
                                                                  if (isPython())
                                                                  {
                                                            #line 2652 "PrintCLike.cpp"
  append(L"self");
                                                            #line 1843 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 2658 "PrintCLike.cpp"
  append(L"this");
                                                            #line 1846 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(semicolon());
                                                                }
                                                            #line 2664 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 1850 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 2669 "PrintCLike.cpp"
  append(L"thread");
                                                            #line 1851 "PrintCLike.cpp.template"
                                                                print(arrow());
                                                              }
                                                              else
                                                              {
                                                            #line 2676 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 1856 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                              }
                                                              print(isGo() ? L"R" : L"r");
                                                            #line 2683 "PrintCLike.cpp"
  append(L"eset(0, 0, 0)");
                                                            #line 1859 "PrintCLike.cpp.template"
                                                              print(semicolon());
                                                              print(rightBrace());
                                                            #line 2688 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 1862 "PrintCLike.cpp.template"
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
                                                            #line 2701 "PrintCLike.cpp"
  append(L"\n");
  append(L"this.reset = function(l, b, e)\n");
  append(L"{\n");
  append(L"  ");
                                                            #line 1875 "PrintCLike.cpp.template"
                                                                if (useGlr)
                                                                {
                                                            #line 2709 "PrintCLike.cpp"
  append(L"thread.");
                                                            #line 1877 "PrintCLike.cpp.template"
                                                                }
                                                            #line 2713 "PrintCLike.cpp"
  append(L"reset(l, b, e);\n");
  append(L"};\n");
                                                            #line 1880 "PrintCLike.cpp.template"
                                                                openMethod(L"static ", stringType(), L"getOffendingToken", L"ParseException e");
                                                                print(leftBrace());
                                                            #line 2719 "PrintCLike.cpp"
  append(L"\n");
  append(L"  var o = e.getOffending();\n");
  append(L"  return o >= 0 ? ");
                                                            #line 1884 "PrintCLike.cpp.template"
                                                                print(staticPrefix());
                                                            #line 2725 "PrintCLike.cpp"
  append(L"TOKEN[o] : ");
                                                            #line 1885 "PrintCLike.cpp.template"
                                                                print(nullPtr());
                                                            #line 2729 "PrintCLike.cpp"
  append(L";\n");
  append(L"};\n");
                                                            #line 1888 "PrintCLike.cpp.template"
                                                              }
                                                              else if (isTypescript())
                                                              {
                                                                if (performanceTest && useGlr)
                                                                {
                                                            #line 2738 "PrintCLike.cpp"
  append(L"\n");
  append(L"public reset(l: number, b: number, e: number)\n");
  append(L"{\n");
  append(L"  this.thread.reset(l, b, e);\n");
  append(L"}\n");
                                                            #line 1898 "PrintCLike.cpp.template"
                                                                }
                                                            #line 2746 "PrintCLike.cpp"
  append(L"\n");
  append(L"getOffendingToken(e: ParseException)\n");
  append(L"{");
  append(L"\n");
  append(L"  var o = e.getOffending();\n");
  append(L"  return o >= 0 ? Parser.TOKEN[o] : ");
                                                            #line 1904 "PrintCLike.cpp.template"
                                                                print(nullPtr());
                                                            #line 2755 "PrintCLike.cpp"
  append(L";\n");
  append(L"}\n");
                                                            #line 1907 "PrintCLike.cpp.template"
                                                              }
                                                              else if (isScala())
                                                              {
                                                              }
                                                              else if (isGo())
                                                              {
                                                            #line 2765 "PrintCLike.cpp"
  append(L"\n");
  append(L"func GetOffendingToken(e ParseError) string {\n");
  append(L"  if e.GetOffending() < 0 {\n");
  append(L"    return \"\"\n");
  append(L"  } else {\n");
  append(L"    return token[e.GetOffending()]\n");
  append(L"  }\n");
  append(L"}\n");
                                                            #line 1921 "PrintCLike.cpp.template"
                                                              }
                                                              else if (isPython())
                                                              {
                                                            #line 2778 "PrintCLike.cpp"
  append(L"\n");
  append(L"@staticmethod\n");
  append(L"def getOffendingToken(e):\n");
  append(L"  if e.getOffending() < 0:\n");
  append(L"    return \"\"\n");
  append(L"  else:\n");
  append(L"    return ");
                                                            #line 1930 "PrintCLike.cpp.template"
                                                                print(className.c_str());
                                                            #line 2788 "PrintCLike.cpp"
  append(L".TOKEN[e.getOffending()]\n");
                                                            #line 1932 "PrintCLike.cpp.template"
                                                              }
                                                              else
                                                              {
                                                                openMethod(stringType(), L"static ", L"getOffendingToken", L"ParseException e");
                                                                print(leftBrace());
                                                            #line 2796 "PrintCLike.cpp"
  append(L"\n");
  append(L"  return e.getOffending() < 0 ? ");
                                                            #line 1938 "PrintCLike.cpp.template"
                                                                print(nullPtr());
                                                            #line 2801 "PrintCLike.cpp"
  append(L" : TOKEN[e.getOffending()];");
                                                            #line 1940 "PrintCLike.cpp.template"
                                                                print(rightBrace());
                                                            #line 2805 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 1942 "PrintCLike.cpp.template"
                                                              }

                                                              if (isJavascript() || isTypescript() || isHaxe())
                                                              {
                                                                openMethod(L"", L"static ", L"getExpectedTokenSet", L"ParseException e");
                                                                print(leftBrace());
                                                            #line 2814 "PrintCLike.cpp"
  append(L"\n");
  append(L"  var expected");
                                                            #line 1949 "PrintCLike.cpp.template"
                                                                if (isTypescript())
                                                                {
                                                            #line 2820 "PrintCLike.cpp"
  append(L": string[]");
                                                            #line 1951 "PrintCLike.cpp.template"
                                                                }
                                                            #line 2824 "PrintCLike.cpp"
  append(L";\n");
  append(L"  if (e.getExpected() < 0)\n");
  append(L"  {\n");
  append(L"    expected = ");
                                                            #line 1955 "PrintCLike.cpp.template"
                                                                print(staticPrefix());
                                                            #line 2831 "PrintCLike.cpp"
  append(L"getTokenSet(- e.getState());\n");
  append(L"  }\n");
  append(L"  else\n");
  append(L"  {\n");
  append(L"    expected = [");
                                                            #line 1960 "PrintCLike.cpp.template"
                                                                print(staticPrefix());
                                                                print(isGo() ? L"token" : L"TOKEN");
                                                            #line 2840 "PrintCLike.cpp"
  append(L"[e.getExpected()]];\n");
  append(L"  }\n");
  append(L"  return expected;\n");
  append(L"}");
                                                            #line 1965 "PrintCLike.cpp.template"
                                                                if (! isTypescript())
                                                                {
                                                            #line 2848 "PrintCLike.cpp"
  append(L";");
                                                            #line 1967 "PrintCLike.cpp.template"
                                                                }
                                                            #line 2852 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 1969 "PrintCLike.cpp.template"
                                                                if (isHaxe())
                                                                {
                                                            #line 2857 "PrintCLike.cpp"
  append(L"\n");
  append(L"public function getErrorMessage(e: ParseException): String");
                                                            #line 1972 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                                  openMethod(stringType(), L"static ", L"getErrorMessage", L"ParseException e");
                                                                }
                                                                print(leftBrace());
                                                            #line 2867 "PrintCLike.cpp"
  append(L"\n");
  append(L"  var message = e.getMessage();");
                                                            #line 1979 "PrintCLike.cpp.template"
                                                                if (useGlr)
                                                                {
                                                                  increaseIndent();
                                                            #line 2874 "PrintCLike.cpp"
  append(L"\n");
  append(L"if ");
                                                            #line 1983 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                            #line 2879 "PrintCLike.cpp"
  append(L"e.isAmbiguousInput()");
                                                            #line 1984 "PrintCLike.cpp.template"
                                                                  print(ifRightParen());
                                                                  print(leftBrace());
                                                            #line 2884 "PrintCLike.cpp"
  append(L"\n");
  append(L"  message += \"\\n\"");
                                                            #line 1987 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                            #line 2889 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 1989 "PrintCLike.cpp.template"
                                                                  print(elseWithBraces());
                                                                }
                                                            #line 2894 "PrintCLike.cpp"
  append(L"\n");
  append(L"  var found = ");
                                                            #line 1992 "PrintCLike.cpp.template"
                                                                if (! isHaxe())
                                                                {
                                                                  print(L"this.");
                                                                }
                                                            #line 2902 "PrintCLike.cpp"
  append(L"getOffendingToken(e);\n");
  append(L"  var tokenSet = ");
                                                            #line 1997 "PrintCLike.cpp.template"
                                                                if (! isHaxe())
                                                                {
                                                                  print(L"this.");
                                                                }
                                                            #line 2910 "PrintCLike.cpp"
  append(L"getExpectedTokenSet(e);\n");
  append(L"  var size = e.getEnd() - e.getBegin();\n");
  append(L"  message += (found == null ? \"\" : \", found \" + found)\n");
  append(L"          + \"\\nwhile expecting \"\n");
  append(L"          + (tokenSet.length == 1 ? tokenSet[0] : (\"[\" + tokenSet.join(\", \") + \"]\"))\n");
  append(L"          + \"\\n\"\n");
  append(L"          + (size == 0 || found != null ? \"\" : \"after successfully scanning \" + size + \" characters beginning \");");
                                                            #line 2008 "PrintCLike.cpp.template"
                                                                if (useGlr)
                                                                {
                                                                  decreaseIndent();
                                                            #line 2922 "PrintCLike.cpp"
  append(L"\n");
  append(L"  }");
                                                            #line 2012 "PrintCLike.cpp.template"
                                                                }
                                                            #line 2927 "PrintCLike.cpp"
  append(L"\n");
  append(L"  var prefix = ");
                                                            #line 2014 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 2932 "PrintCLike.cpp"
  append(L"input.");
                                                            #line 2015 "PrintCLike.cpp.template"
                                                                if (isHaxe())
                                                                {
                                                            #line 2937 "PrintCLike.cpp"
  append(L"getS");
                                                            #line 2017 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 2943 "PrintCLike.cpp"
  append(L"subs");
                                                            #line 2020 "PrintCLike.cpp.template"
                                                                }
                                                            #line 2947 "PrintCLike.cpp"
  append(L"tring(0, e.getBegin());\n");
  append(L"  var lines = prefix.split(\"\\n\");\n");
  append(L"  var line = lines.length;\n");
  append(L"  var column = lines[line - 1].length + 1;\n");
  append(L"  return message\n");
  append(L"       + \"at line \" + line + \", column \" + column + \":\\n...\"\n");
  append(L"       + ");
                                                            #line 2027 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                                if (isHaxe())
                                                                {
                                                            #line 2959 "PrintCLike.cpp"
  append(L"input.getString(e.getBegin(), input.length < e.getBegin() + 64 ? input.length - e.getBegin() : 64");
                                                            #line 2031 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 2965 "PrintCLike.cpp"
  append(L"input.substring(e.getBegin(), ");
                                                            #line 2035 "PrintCLike.cpp.template"
                                        
                                                            #line 2969 "PrintCLike.cpp"
  append(L"Math.min(");
                                                            #line 2035 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 2973 "PrintCLike.cpp"
  append(L"input.length, e.getBegin() + 64)");
                                                            #line 2037 "PrintCLike.cpp.template"
                                                                }
                                                            #line 2977 "PrintCLike.cpp"
  append(L")\n");
  append(L"       + \"...\";\n");
  append(L"}");
                                                            #line 2040 "PrintCLike.cpp.template"
                                                                if (! isTypescript())
                                                                {
                                                            #line 2984 "PrintCLike.cpp"
  append(L";");
                                                            #line 2042 "PrintCLike.cpp.template"
                                                                }
                                                            #line 2988 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 2044 "PrintCLike.cpp.template"
                                                              }
                                                              else if (isJava())
                                                              {
                                                                openMethod(L"String[] ", L"static ", L"getExpectedTokenSet", L"ParseException e");
                                                                print(leftBrace());
                                                            #line 2996 "PrintCLike.cpp"
  append(L"\n");
  append(L"  String[] expected");
                                                            #line 2050 "PrintCLike.cpp.template"
                                                                if (useGlr)
                                                                {
                                                            #line 3002 "PrintCLike.cpp"
  append(L" = {}");
                                                            #line 2052 "PrintCLike.cpp.template"
                                                                }
                                                            #line 3006 "PrintCLike.cpp"
  append(L";\n");
  append(L"  if (e.getExpected() >= 0)\n");
  append(L"  {\n");
  append(L"    expected = new String[]{TOKEN[e.getExpected()]};\n");
  append(L"  }\n");
  append(L"  else");
                                                            #line 2058 "PrintCLike.cpp.template"
                                                                if (useGlr)
                                                                {
                                                            #line 3016 "PrintCLike.cpp"
  append(L" if (! e.isAmbiguousInput())");
                                                            #line 2060 "PrintCLike.cpp.template"
                                                                }
                                                            #line 3020 "PrintCLike.cpp"
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
                                                            #line 2071 "PrintCLike.cpp.template"
                                                                if (useGlr)
                                                                {
                                                            #line 3034 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if ");
                                                            #line 2074 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                            #line 3039 "PrintCLike.cpp"
  append(L"e.isAmbiguousInput()");
                                                            #line 2075 "PrintCLike.cpp.template"
                                                                  print(ifRightParen());
                                                                  printIndented(1, leftBrace());
                                                            #line 3044 "PrintCLike.cpp"
  append(L"\n");
  append(L"    message += \"\\n\"");
                                                            #line 2078 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                            #line 3049 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 2080 "PrintCLike.cpp.template"
                                                                  printIndented(1, elseWithBraces());
                                                                  increaseIndent();
                                                                }
                                                            #line 3056 "PrintCLike.cpp"
  append(L"\n");
  append(L"  String[] tokenSet = getExpectedTokenSet(e);\n");
  append(L"  String found = getOffendingToken(e);\n");
  append(L"  int size = e.getEnd() - e.getBegin();\n");
  append(L"  message += (found == null ? \"\" : \", found \" + found)\n");
  append(L"          + \"\\nwhile expecting \"\n");
  append(L"          + (tokenSet.length == 1 ? tokenSet[0] : java.util.Arrays.toString(tokenSet))\n");
  append(L"          + \"\\n\"\n");
  append(L"          + (size == 0 || found != null ? \"\" : \"after successfully scanning \" + size + \" characters beginning \");");
                                                            #line 2092 "PrintCLike.cpp.template"
                                                                if (useGlr)
                                                                {
                                                                  decreaseIndent();
                                                            #line 3070 "PrintCLike.cpp"
  append(L"\n");
  append(L"  }");
                                                            #line 2096 "PrintCLike.cpp.template"
                                                                }
                                                            #line 3075 "PrintCLike.cpp"
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
                                                            #line 2106 "PrintCLike.cpp.template"
                                                                if (! interfaceName.empty())
                                                                {
                                                            #line 3090 "PrintCLike.cpp"
  append(L"\n");
  append(L"public void parse()\n");
  append(L"{\n");
  append(L"  parse_");
                                                            #line 2111 "PrintCLike.cpp.template"
                                                                  print(Format::acceptableName<WString>(grammar->startSymbol()->name).c_str());
                                                            #line 3097 "PrintCLike.cpp"
  append(L"();\n");
  append(L"}\n");
                                                            #line 2114 "PrintCLike.cpp.template"
                                                                }
                                                              }
                                                              else if (isCSharp())
                                                              {
                                                                openMethod(L"static String[] ", L"", L"getExpectedTokenSet", L"ParseException e");
                                                                print(leftBrace());
                                                            #line 3107 "PrintCLike.cpp"
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
                                                            #line 2136 "PrintCLike.cpp.template"
                                                                if (useGlr)
                                                                {
                                                            #line 3127 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if (e.isAmbiguousInput())\n");
  append(L"  {\n");
  append(L"    message += \"\\n\";\n");
  append(L"  }\n");
  append(L"  else\n");
  append(L"  {");
                                                            #line 2144 "PrintCLike.cpp.template"
                                                                  increaseIndent();
                                                                }
                                                            #line 3138 "PrintCLike.cpp"
  append(L"\n");
  append(L"  String[] tokenSet = getExpectedTokenSet(e);\n");
  append(L"  String found = getOffendingToken(e);\n");
  append(L"  int size = e.getEnd() - e.getBegin();\n");
  append(L"  message += (found == null ? \"\" : \", found \" + found)\n");
  append(L"          + \"\\nwhile expecting \"\n");
  append(L"          + (tokenSet.Length == 1 ? tokenSet[0] : (\"[\" + String.Join(\", \", tokenSet) + \"]\"))\n");
  append(L"          + \"\\n\"\n");
  append(L"          + (size == 0 || found != null ? \"\" : \"after successfully scanning \" + size + \" characters beginning \");");
                                                            #line 2155 "PrintCLike.cpp.template"
                                                                if (useGlr)
                                                                {
                                                                  decreaseIndent();
                                                            #line 3152 "PrintCLike.cpp"
  append(L"\n");
  append(L"  }");
                                                            #line 2159 "PrintCLike.cpp.template"
                                                                }
                                                            #line 3157 "PrintCLike.cpp"
  append(L"\n");
  append(L"  String prefix = input.Substring(0, e.getBegin());\n");
  append(L"  int line = prefix.Length - prefix.Replace(\"\\n\", \"\").Length + 1;\n");
  append(L"  int column = prefix.Length - prefix.LastIndexOf('\\n');\n");
  append(L"  return message\n");
  append(L"       + \"at line \" + line + \", column \" + column + \":\\n...\"\n");
  append(L"       + input.Substring(e.getBegin(), Math.Min(input.Length, e.getBegin() + 64) - e.getBegin())\n");
  append(L"       + \"...\";\n");
  append(L"}\n");
                                                            #line 2169 "PrintCLike.cpp.template"
                                                                if (! interfaceName.empty())
                                                                {
                                                            #line 3170 "PrintCLike.cpp"
  append(L"\n");
  append(L"public void parse()\n");
  append(L"{\n");
  append(L"  parse_");
                                                            #line 2174 "PrintCLike.cpp.template"
                                                                  print(Format::acceptableName<WString>(grammar->startSymbol()->name).c_str());
                                                            #line 3177 "PrintCLike.cpp"
  append(L"();\n");
  append(L"}\n");
                                                            #line 2177 "PrintCLike.cpp.template"
                                                                }
                                                              }
                                                              else if (isGo())
                                                              {
                                                            #line 3185 "PrintCLike.cpp"
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
                                                            #line 2191 "PrintCLike.cpp.template"
                                                                print(className.c_str());
                                                            #line 3199 "PrintCLike.cpp"
  append(L") GetErrorMessage(e ParseError) string {\n");
  append(L"  message := e.Error()");
                                                            #line 2194 "PrintCLike.cpp.template"
                                                                if (useGlr)
                                                                {
                                                            #line 3205 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if e.IsAmbiguousInput() {\n");
  append(L"    message += \"\\n\"\n");
  append(L"  } else {");
                                                            #line 2199 "PrintCLike.cpp.template"
                                                                  increaseIndent();
                                                                }
                                                            #line 3213 "PrintCLike.cpp"
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
                                                            #line 2227 "PrintCLike.cpp.template"
                                                                if (useGlr)
                                                                {
                                                                  decreaseIndent();
                                                            #line 3245 "PrintCLike.cpp"
  append(L"\n");
  append(L"  }");
                                                            #line 2231 "PrintCLike.cpp.template"
                                                                }
                                                            #line 3250 "PrintCLike.cpp"
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
                                                            #line 2256 "PrintCLike.cpp.template"
                                                                if (! interfaceName.empty())
                                                                {
                                                            #line 3278 "PrintCLike.cpp"
  append(L"\n");
  append(L"public void parse()\n");
  append(L"{\n");
  append(L"  parse_");
                                                            #line 2261 "PrintCLike.cpp.template"
                                                                  print(Format::acceptableName<WString>(grammar->startSymbol()->name).c_str());
                                                            #line 3285 "PrintCLike.cpp"
  append(L"();\n");
  append(L"}\n");
                                                            #line 2264 "PrintCLike.cpp.template"
                                                                }
                                                              }
                                                              else if (isPython())
                                                              {
                                                            #line 3293 "PrintCLike.cpp"
  append(L"\n");
  append(L"@staticmethod\n");
  append(L"def getExpectedTokenSet(e):\n");
  append(L"  if e.expected < 0:\n");
  append(L"    return ");
                                                            #line 2272 "PrintCLike.cpp.template"
                                                                print(className.c_str());
                                                            #line 3301 "PrintCLike.cpp"
  append(L".getTokenSet(- e.state)\n");
  append(L"  else:\n");
  append(L"    return [");
                                                            #line 2275 "PrintCLike.cpp.template"
                                                                print(className.c_str());
                                                            #line 3307 "PrintCLike.cpp"
  append(L".TOKEN[e.expected]]\n");
  append(L"\n");
  append(L"def getErrorMessage(self, e):\n");
  append(L"  message = e.error()");
                                                            #line 2279 "PrintCLike.cpp.template"
                                                                if (useGlr)
                                                                {
                                                            #line 3315 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if e.isAmbiguousInput():\n");
  append(L"    message += \"\\n\"\n");
  append(L"  else:");
                                                            #line 2284 "PrintCLike.cpp.template"
                                                                  increaseIndent();
                                                                }
                                                            #line 3323 "PrintCLike.cpp"
  append(L"\n");
  append(L"  found = ");
                                                            #line 2287 "PrintCLike.cpp.template"
                                                                print(className.c_str());
                                                            #line 3328 "PrintCLike.cpp"
  append(L".getOffendingToken(e)\n");
  append(L"  if found != \"\":\n");
  append(L"    message += \", found \"\n");
  append(L"    message += found\n");
  append(L"  expected = ");
                                                            #line 2292 "PrintCLike.cpp.template"
                                                                print(className.c_str());
                                                            #line 3336 "PrintCLike.cpp"
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
                                                            #line 2309 "PrintCLike.cpp.template"
                                                                if (useGlr)
                                                                {
                                                                  decreaseIndent();
                                                                }
                                                            #line 3359 "PrintCLike.cpp"
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
                                                            #line 2333 "PrintCLike.cpp.template"
                                                                if (! interfaceName.empty())
                                                                {
                                                            #line 3383 "PrintCLike.cpp"
  append(L"\n");
  append(L"public void parse()\n");
  append(L"{\n");
  append(L"  parse_");
                                                            #line 2338 "PrintCLike.cpp.template"
                                                                  print(Format::acceptableName<WString>(grammar->startSymbol()->name).c_str());
                                                            #line 3390 "PrintCLike.cpp"
  append(L"();\n");
  append(L"}\n");
                                                            #line 2341 "PrintCLike.cpp.template"
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
                                                            #line 3406 "PrintCLike.cpp"
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
                                                            #line 2364 "PrintCLike.cpp.template"
                                                                print(isGo() ? L"token" : L"TOKEN");
                                                            #line 3421 "PrintCLike.cpp"
  append(L"[e.expected];\n");
  append(L"    set[1] = 0;\n");
  append(L"  }\n");
  append(L"}\n");
  append(L"\n");
  append(L"static std::");
                                                            #line 2370 "PrintCLike.cpp.template"
                                                                if (stringIntroducer()[0]) append(L"w");
                                                            #line 3430 "PrintCLike.cpp"
  append(L"string to_");
                                                            #line 2371 "PrintCLike.cpp.template"
                                                                if (stringIntroducer()[0]) append(L"w");
                                                            #line 3434 "PrintCLike.cpp"
  append(L"string(int i)\n");
  append(L"{\n");
  append(L"  const ");
                                                            #line 2374 "PrintCLike.cpp.template"
                                                                if (stringIntroducer()[0]) append(L"w");
                                                            #line 3440 "PrintCLike.cpp"
  append(L"char");
                                                            #line 2375 "PrintCLike.cpp.template"
                                                                if (stringIntroducer()[0]) append(L"_t");
                                                            #line 3444 "PrintCLike.cpp"
  append(L" *sign = i < 0 ? ");
                                                            #line 2376 "PrintCLike.cpp.template"
                                                                append(stringIntroducer());
                                                            #line 3448 "PrintCLike.cpp"
  append(L"\"-\" : ");
                                                            #line 2377 "PrintCLike.cpp.template"
                                                                append(stringIntroducer());
                                                            #line 3452 "PrintCLike.cpp"
  append(L"\"\";\n");
  append(L"  std::");
                                                            #line 2379 "PrintCLike.cpp.template"
                                                                if (stringIntroducer()[0]) append(L"w");
                                                            #line 3457 "PrintCLike.cpp"
  append(L"string a;\n");
  append(L"  do\n");
  append(L"  {\n");
  append(L"    a += ");
                                                            #line 2383 "PrintCLike.cpp.template"
                                                                append(stringIntroducer());
                                                            #line 3464 "PrintCLike.cpp"
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
                                                            #line 2393 "PrintCLike.cpp.template"
                                                                if (stringIntroducer()[0]) append(L"w");
                                                            #line 3477 "PrintCLike.cpp"
  append(L"string getErrorMessage(const ParseException &e)\n");
  append(L"{\n");
  append(L"  std::");
                                                            #line 2396 "PrintCLike.cpp.template"
                                                                if (stringIntroducer()[0]) append(L"w");
                                                            #line 3483 "PrintCLike.cpp"
  append(L"string message(e.getMessage());");
                                                            #line 2397 "PrintCLike.cpp.template"
                                                                if (useGlr)
                                                                {
                                                            #line 3488 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if (e.isAmbiguousInput())\n");
  append(L"  {\n");
  append(L"    message += ");
                                                            #line 2402 "PrintCLike.cpp.template"
                                                                  print(stringIntroducer());
                                                            #line 3495 "PrintCLike.cpp"
  append(L"\"\\n\";\n");
  append(L"  }\n");
  append(L"  else\n");
  append(L"  {");
                                                            #line 2406 "PrintCLike.cpp.template"
                                                                  increaseIndent();
                                                                }
                                                            #line 3503 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 2409 "PrintCLike.cpp.template"
                                                                print(stringType());
                                                            #line 3508 "PrintCLike.cpp"
  append(L"found = getOffendingToken(e);\n");
  append(L"  if (found != 0)\n");
  append(L"  {\n");
  append(L"    message += ");
                                                            #line 2413 "PrintCLike.cpp.template"
                                                                print(stringIntroducer());
                                                            #line 3515 "PrintCLike.cpp"
  append(L"\", found \";\n");
  append(L"    message += found;\n");
  append(L"  }\n");
  append(L"  ");
                                                            #line 2417 "PrintCLike.cpp.template"
                                                                print(stringType());
                                                            #line 3522 "PrintCLike.cpp"
  append(L"expected[64];\n");
  append(L"  getExpectedTokenSet(e, expected, sizeof expected / sizeof *expected);\n");
  append(L"  message += ");
                                                            #line 2420 "PrintCLike.cpp.template"
                                                                print(stringIntroducer());
                                                            #line 3528 "PrintCLike.cpp"
  append(L"\"\\nwhile expecting \";\n");
  append(L"  ");
                                                            #line 2422 "PrintCLike.cpp.template"
                                                                print(stringType());
                                                            #line 3533 "PrintCLike.cpp"
  append(L"delimiter(expected[1] ? ");
                                                            #line 2423 "PrintCLike.cpp.template"
                                                                print(stringIntroducer());
                                                            #line 3537 "PrintCLike.cpp"
  append(L"\"[\" : ");
                                                            #line 2424 "PrintCLike.cpp.template"
                                                                print(stringIntroducer());
                                                            #line 3541 "PrintCLike.cpp"
  append(L"\"\");\n");
  append(L"  for (");
                                                            #line 2426 "PrintCLike.cpp.template"
                                                                print(stringType());
                                                            #line 3546 "PrintCLike.cpp"
  append(L"*x = expected; *x; ++x)\n");
  append(L"  {\n");
  append(L"    message += delimiter;\n");
  append(L"    message += *x;\n");
  append(L"    delimiter = ");
                                                            #line 2431 "PrintCLike.cpp.template"
                                                                print(stringIntroducer());
                                                            #line 3554 "PrintCLike.cpp"
  append(L"\", \";\n");
  append(L"  }\n");
  append(L"  message += expected[1] ? ");
                                                            #line 2434 "PrintCLike.cpp.template"
                                                                print(stringIntroducer());
                                                            #line 3560 "PrintCLike.cpp"
  append(L"\"]\\n\" : ");
                                                            #line 2435 "PrintCLike.cpp.template"
                                                                print(stringIntroducer());
                                                            #line 3564 "PrintCLike.cpp"
  append(L"\"\\n\";\n");
  append(L"  int size = e.getEnd() - e.getBegin();\n");
  append(L"  if (size != 0 && found == 0)\n");
  append(L"  {\n");
  append(L"    message += ");
                                                            #line 2440 "PrintCLike.cpp.template"
                                                                print(stringIntroducer());
                                                            #line 3572 "PrintCLike.cpp"
  append(L"\"after successfully scanning \";\n");
  append(L"    message += to_");
                                                            #line 2442 "PrintCLike.cpp.template"
                                                                if (stringIntroducer()[0]) append(L"w");
                                                            #line 3577 "PrintCLike.cpp"
  append(L"string(size);\n");
  append(L"    message += ");
                                                            #line 2444 "PrintCLike.cpp.template"
                                                                print(stringIntroducer());
                                                            #line 3582 "PrintCLike.cpp"
  append(L"\" characters beginning \";\n");
  append(L"  }");
                                                            #line 2446 "PrintCLike.cpp.template"
                                                                if (useGlr)
                                                                {
                                                                  decreaseIndent();
                                                            #line 3589 "PrintCLike.cpp"
  append(L"\n");
  append(L"  }");
                                                            #line 2450 "PrintCLike.cpp.template"
                                                                }
                                                            #line 3594 "PrintCLike.cpp"
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
                                                            #line 2466 "PrintCLike.cpp.template"
                                                                print(stringIntroducer());
                                                            #line 3613 "PrintCLike.cpp"
  append(L"\"at line \";\n");
  append(L"  message += to_");
                                                            #line 2468 "PrintCLike.cpp.template"
                                                              if (stringIntroducer()[0]) append(L"w");
                                                            #line 3618 "PrintCLike.cpp"
  append(L"string(line);\n");
  append(L"  message += ");
                                                            #line 2470 "PrintCLike.cpp.template"
                                                              print(stringIntroducer());
                                                            #line 3623 "PrintCLike.cpp"
  append(L"\", column \";\n");
  append(L"  message += to_");
                                                            #line 2472 "PrintCLike.cpp.template"
                                                              if (stringIntroducer()[0]) append(L"w");
                                                            #line 3628 "PrintCLike.cpp"
  append(L"string(column);\n");
  append(L"  message += ");
                                                            #line 2474 "PrintCLike.cpp.template"
                                                                print(stringIntroducer());
                                                            #line 3633 "PrintCLike.cpp"
  append(L"\":\\n...\";\n");
  append(L"  ");
                                                            #line 2476 "PrintCLike.cpp.template"
                                                                print(stringType());
                                                            #line 3638 "PrintCLike.cpp"
  append(L"w = input + e.getBegin();\n");
  append(L"  for (int i = 0; i < 64 && *w; ++i)\n");
  append(L"  {\n");
  append(L"    message += *w++;\n");
  append(L"  }\n");
  append(L"  message += ");
                                                            #line 2482 "PrintCLike.cpp.template"
                                                                print(stringIntroducer());
                                                            #line 3647 "PrintCLike.cpp"
  append(L"\"...\";\n");
  append(L"  return message;\n");
  append(L"}\n");
                                                            #line 2486 "PrintCLike.cpp.template"
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
                                                            #line 3676 "PrintCLike.cpp"
  append(L"\n");
  append(L"  fprintf(stderr, \"  <%s %snonterminal=\\\"%s\\\"\", ");
                                                            #line 2511 "PrintCLike.cpp.template"
                                                                  if (stringIntroducer()[0])
                                                                  {
                                                            #line 3682 "PrintCLike.cpp"
  append(L"Utf8Encoder::encode(");
                                                            #line 2513 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 3686 "PrintCLike.cpp"
  append(L"method");
                                                            #line 2514 "PrintCLike.cpp.template"
                                                                  if (stringIntroducer()[0])
                                                                  {
                                                            #line 3691 "PrintCLike.cpp"
  append(L").c_str()");
                                                            #line 2516 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 3695 "PrintCLike.cpp"
  append(L", ");
                                                            #line 2517 "PrintCLike.cpp.template"
                                                                  if (stringIntroducer()[0])
                                                                  {
                                                            #line 3700 "PrintCLike.cpp"
  append(L"Utf8Encoder::encode(");
                                                            #line 2519 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 3704 "PrintCLike.cpp"
  append(L"occasion");
                                                            #line 2520 "PrintCLike.cpp.template"
                                                                  if (stringIntroducer()[0])
                                                                  {
                                                            #line 3709 "PrintCLike.cpp"
  append(L").c_str()");
                                                            #line 2522 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 3713 "PrintCLike.cpp"
  append(L", ");
                                                            #line 2523 "PrintCLike.cpp.template"
                                                                  if (stringIntroducer()[0])
                                                                  {
                                                            #line 3718 "PrintCLike.cpp"
  append(L"Utf8Encoder::encode(");
                                                            #line 2525 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 3722 "PrintCLike.cpp"
  append(L"name");
                                                            #line 2526 "PrintCLike.cpp.template"
                                                                  if (stringIntroducer()[0])
                                                                  {
                                                            #line 3727 "PrintCLike.cpp"
  append(L").c_str()");
                                                            #line 2528 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 3731 "PrintCLike.cpp"
  append(L");\n");
  append(L"  if (l1 != 0)\n");
  append(L"    fprintf(stderr, \" input=\\\"%s\\\"\", ");
                                                            #line 2531 "PrintCLike.cpp.template"
                                                                  if (stringIntroducer()[0])
                                                                  {
                                                            #line 3738 "PrintCLike.cpp"
  append(L"Utf8Encoder::encode(");
                                                            #line 2533 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 3742 "PrintCLike.cpp"
  append(L"xmlEscape(lookaheadString().c_str(), 0).c_str()");
                                                            #line 2535 "PrintCLike.cpp.template"
                                                                  if (stringIntroducer()[0])
                                                                  {
                                                            #line 3747 "PrintCLike.cpp"
  append(L").c_str()");
                                                            #line 2537 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 3751 "PrintCLike.cpp"
  append(L");\n");
  append(L"  fprintf(stderr, \"/>\\n\");");
                                                            #line 2539 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                                  if (isHaxe())
                                                                  {
                                                            #line 3760 "PrintCLike.cpp"
  append(L"\n");
  append(L"  trace(");
                                                            #line 2545 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                                    if (isGo())
                                                                    {
                                                            #line 3769 "PrintCLike.cpp"
  append(L"\n");
  append(L"  var inputAttr string\n");
  append(L"  if (this.l1 == 0) {\n");
  append(L"    inputAttr = \"\"\n");
  append(L"  } else {\n");
  append(L"    inputAttr = \" input=\\\"\" + xmlEscape(this.lookaheadString()) + \"\\\"\"\n");
  append(L"  }");
                                                            #line 2556 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 3779 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 2558 "PrintCLike.cpp.template"
                                                                    print(writeTrace());
                                                                  }
                                                            #line 3785 "PrintCLike.cpp"
  append(L"\"  <\" + method + \" \" + occasion + \"nonterminal=\\\"\" + name + \"\\\"\" + ");
                                                            #line 2561 "PrintCLike.cpp.template"
                                                                  if (isGo())
                                                                  {
                                                            #line 3790 "PrintCLike.cpp"
  append(L"inputAttr");
                                                            #line 2563 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 3796 "PrintCLike.cpp"
  append(L"(");
                                                            #line 2566 "PrintCLike.cpp.template"
                                                                    if (isScala())
                                                                    {
                                                            #line 3801 "PrintCLike.cpp"
  append(L"if (l1 == 0) \"\" else");
                                                            #line 2568 "PrintCLike.cpp.template"
                                                                    }
                                                                    else if (isPython())
                                                                    {
                                                            #line 3807 "PrintCLike.cpp"
  append(L"\"\" if self.l1 == 0 else");
                                                            #line 2571 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                                      print(thiz());
                                                            #line 3814 "PrintCLike.cpp"
  append(L"l1 == 0 ? \"\" :");
                                                            #line 2575 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 3818 "PrintCLike.cpp"
  append(L" \" input=\\\"\" + ");
                                                            #line 2576 "PrintCLike.cpp.template"
                                                                    print(staticPrefix());
                                                            #line 3822 "PrintCLike.cpp"
  append(L"xmlEscape(");
                                                            #line 2577 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 3826 "PrintCLike.cpp"
  append(L"lookaheadString");
                                                            #line 2578 "PrintCLike.cpp.template"
                                                                    if (! isScala()) print(L"()");
                                                            #line 3830 "PrintCLike.cpp"
  append(L") + \"\\\"\")");
                                                            #line 2579 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 3834 "PrintCLike.cpp"
  append(L" + \"/>");
                                                            #line 2580 "PrintCLike.cpp.template"
                                                                  if (isHaxe()) print(L"\")"); else print(L"\\n\"");
                                                                  print(endWriteTrace());
                                                                  print(semicolon());
                                                                }
                                                                print(rightBrace());
                                                            #line 3842 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 2586 "PrintCLike.cpp.template"
                                                                decreaseIndent();
                                                              }

                                                              if (grammar->automaticSemicolonInsertion)
                                                              {
                                                                if (! isGo())
                                                                  increaseIndent();
                                                                openMethod(boolType(), L"", L"followsLineTerminator", L"");
                                                                print(leftBrace());
                                                                increaseIndent();
                                                            #line 3855 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 2597 "PrintCLike.cpp.template"
                                                                print(intVar());
                                                            #line 3859 "PrintCLike.cpp"
  append(L"i");
                                                            #line 2598 "PrintCLike.cpp.template"
                                                                print(assign());
                                                                print(thiz());
                                                            #line 3864 "PrintCLike.cpp"
  append(L"e0");
                                                            #line 2600 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 3868 "PrintCLike.cpp"
  append(L"\n");
  append(L"if ");
                                                            #line 2602 "PrintCLike.cpp.template"
                                                                print(ifLeftParen());
                                                                print(thiz());
                                                            #line 3874 "PrintCLike.cpp"
  append(L"e0 == ");
                                                            #line 2604 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 3878 "PrintCLike.cpp"
  append(L"b1");
                                                            #line 2605 "PrintCLike.cpp.template"
                                                                print(ifRightParen());
                                                                print(leftBrace());
                                                            #line 3883 "PrintCLike.cpp"
  append(L"\n");
  append(L"  i = ");
                                                            #line 2608 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 3888 "PrintCLike.cpp"
  append(L"b0");
                                                            #line 2609 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                print(rightBrace());
                                                                if (isScala() || isHaxe() || isPython())
                                                                {
                                                            #line 3895 "PrintCLike.cpp"
  append(L"\n");
  append(L"while ");
                                                            #line 2614 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 3902 "PrintCLike.cpp"
  append(L"\n");
  append(L"for ");
                                                            #line 2618 "PrintCLike.cpp.template"
                                                                }
                                                                print(ifLeftParen());
                                                                if (! (isScala() || isHaxe() || isPython()))
                                                                {
                                                            #line 3910 "PrintCLike.cpp"
  append(L"; ");
                                                            #line 2622 "PrintCLike.cpp.template"
                                                                }
                                                            #line 3914 "PrintCLike.cpp"
  append(L"i < ");
                                                            #line 2623 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 3918 "PrintCLike.cpp"
  append(L"b1");
                                                            #line 2624 "PrintCLike.cpp.template"
                                                                if (! (isScala() || isHaxe() || isPython()))
                                                                {
                                                            #line 3923 "PrintCLike.cpp"
  append(L"; i++");
                                                            #line 2626 "PrintCLike.cpp.template"
                                                                }
                                                                print(ifRightParen());
                                                                print(leftBrace());
                                                                increaseIndent();
                                                                if (isGo())
                                                                {
                                                            #line 3932 "PrintCLike.cpp"
  append(L"\n");
  append(L"c, _ := utf8.DecodeRuneInString(this.input[i:])");
                                                            #line 2633 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 3939 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 2637 "PrintCLike.cpp.template"
                                                                  print(intVar());
                                                            #line 3943 "PrintCLike.cpp"
  append(L"c");
                                                            #line 2638 "PrintCLike.cpp.template"
                                                                  print(assign());
                                                                  if (isCpp() || isCSharp() || isPython())
                                                                  {
                                                                    if (isPython())
                                                                    {
                                                            #line 3951 "PrintCLike.cpp"
  append(L"ord(");
                                                            #line 2643 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(thiz());
                                                            #line 3956 "PrintCLike.cpp"
  append(L"input[i]");
                                                            #line 2645 "PrintCLike.cpp.template"
                                                                    if (isPython())
                                                                    {
                                                            #line 3961 "PrintCLike.cpp"
  append(L")");
                                                            #line 2647 "PrintCLike.cpp.template"
                                                                    }
                                                                  }
                                                                  else if (isHaxe())
                                                                  {
                                                            #line 3968 "PrintCLike.cpp"
  append(L"input.get(i)");
                                                            #line 2651 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                                    print(thiz());
                                                            #line 3975 "PrintCLike.cpp"
  append(L"input.char");
                                                            #line 2655 "PrintCLike.cpp.template"
                                                                    if (isTypescript() || isJavascript())
                                                                    {
                                                            #line 3980 "PrintCLike.cpp"
  append(L"Code");
                                                            #line 2657 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 3984 "PrintCLike.cpp"
  append(L"At(i)");
                                                            #line 2658 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(semicolon());
                                                                }
                                                            #line 3990 "PrintCLike.cpp"
  append(L"\n");
  append(L"if ");
                                                            #line 2662 "PrintCLike.cpp.template"
                                                                print(ifLeftParen());
                                                            #line 3995 "PrintCLike.cpp"
  append(L"c == 0xA ");
                                                            #line 2664 "PrintCLike.cpp.template"
                                                                if (isPython())
                                                                {
                                                            #line 4000 "PrintCLike.cpp"
  append(L"or");
                                                            #line 2666 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 4006 "PrintCLike.cpp"
  append(L"||");
                                                            #line 2669 "PrintCLike.cpp.template"
                                                                }
                                                            #line 4010 "PrintCLike.cpp"
  append(L" c == 0xD ");
                                                            #line 2671 "PrintCLike.cpp.template"
                                                                if (isPython())
                                                                {
                                                            #line 4015 "PrintCLike.cpp"
  append(L"or");
                                                            #line 2673 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 4021 "PrintCLike.cpp"
  append(L"||");
                                                            #line 2676 "PrintCLike.cpp.template"
                                                                }
                                                            #line 4025 "PrintCLike.cpp"
  append(L" c == 0x2028 ");
                                                            #line 2678 "PrintCLike.cpp.template"
                                                                if (isPython())
                                                                {
                                                            #line 4030 "PrintCLike.cpp"
  append(L"or");
                                                            #line 2680 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 4036 "PrintCLike.cpp"
  append(L"||");
                                                            #line 2683 "PrintCLike.cpp.template"
                                                                }
                                                            #line 4040 "PrintCLike.cpp"
  append(L" c == 0x2029");
                                                            #line 2684 "PrintCLike.cpp.template"
                                                                print(ifRightParen());
                                                                print(leftBrace());
                                                            #line 4045 "PrintCLike.cpp"
  append(L"\n");
  append(L"  return ");
                                                            #line 2687 "PrintCLike.cpp.template"
                                                                if (isPython())
                                                                {
                                                            #line 4051 "PrintCLike.cpp"
  append(L"T");
                                                            #line 2689 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 4057 "PrintCLike.cpp"
  append(L"t");
                                                            #line 2692 "PrintCLike.cpp.template"
                                                                }
                                                            #line 4061 "PrintCLike.cpp"
  append(L"rue");
                                                            #line 2693 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                print(rightBrace());
                                                                if (isScala() || isPython())
                                                                {
                                                            #line 4068 "PrintCLike.cpp"
  append(L"\n");
  append(L"i += 1");
                                                            #line 2699 "PrintCLike.cpp.template"
                                                                }
                                                                else if (isHaxe())
                                                                {
                                                            #line 4075 "PrintCLike.cpp"
  append(L"\n");
  append(L"++i;");
                                                            #line 2703 "PrintCLike.cpp.template"
                                                                }

                                                                decreaseIndent();
                                                                print(rightBrace());
                                                            #line 4083 "PrintCLike.cpp"
  append(L"\n");
  append(L"return ");
                                                            #line 2708 "PrintCLike.cpp.template"
                                                                if (isPython())
                                                                {
                                                            #line 4089 "PrintCLike.cpp"
  append(L"F");
                                                            #line 2710 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 4095 "PrintCLike.cpp"
  append(L"f");
                                                            #line 2713 "PrintCLike.cpp.template"
                                                                }
                                                            #line 4099 "PrintCLike.cpp"
  append(L"alse");
                                                            #line 2714 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                decreaseIndent();
                                                                print(rightBrace());
                                                            #line 4105 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 2718 "PrintCLike.cpp.template"
                                                                if (! isGo())
                                                                  decreaseIndent();
                                                              }

                                                              if (isScala())
                                                              {
                                                            #line 4114 "PrintCLike.cpp"
  append(L"\n");
  append(L"  def getErrorMessage(e: ");
                                                            #line 2725 "PrintCLike.cpp.template"
                                                                print(className.c_str());
                                                            #line 4119 "PrintCLike.cpp"
  append(L".ParseException) = {\n");
  append(L"    var message = e.getMessage");
                                                            #line 2727 "PrintCLike.cpp.template"
                                                                if (useGlr)
                                                                {
                                                            #line 4125 "PrintCLike.cpp"
  append(L"\n");
  append(L"    if (e.isAmbiguousInput)\n");
  append(L"      message += \"\\n\"\n");
  append(L"    else {");
                                                            #line 2732 "PrintCLike.cpp.template"
                                                                  increaseIndent();
                                                                }
                                                            #line 4133 "PrintCLike.cpp"
  append(L"\n");
  append(L"    val tokenSet = ");
                                                            #line 2735 "PrintCLike.cpp.template"
                                                                print(className.c_str());
                                                            #line 4138 "PrintCLike.cpp"
  append(L".getExpectedTokenSet(e)\n");
  append(L"    val found = ");
                                                            #line 2737 "PrintCLike.cpp.template"
                                                                print(className.c_str());
                                                            #line 4143 "PrintCLike.cpp"
  append(L".getOffendingToken(e)\n");
  append(L"    val size = e.end - e.begin\n");
  append(L"    message += (if (found == null) \"\" else \", found \" + found) + \"\\nwhile expecting \" +\n");
  append(L"      (if (tokenSet.length == 1) tokenSet(0) else \"[\" + (tokenSet mkString \", \") + \"]\") + \"\\n\" +\n");
  append(L"      (if (size == 0 || found != null) \"\" else \"after successfully scanning \" + size + \" characters beginning \")");
                                                            #line 2743 "PrintCLike.cpp.template"
                                                                if (useGlr)
                                                                {
                                                            #line 4152 "PrintCLike.cpp"
  append(L"\n");
  append(L"    }");
                                                            #line 2746 "PrintCLike.cpp.template"
                                                                  decreaseIndent();
                                                                }
                                                            #line 4158 "PrintCLike.cpp"
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
                                                            #line 2756 "PrintCLike.cpp.template"
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
                                                            #line 4206 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 2793 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 4211 "PrintCLike.cpp"
  append(L"top += ");
                                                            #line 2794 "PrintCLike.cpp.template"
                                                                  if (tree)
                                                                  {
                                                            #line 4216 "PrintCLike.cpp"
  append(L"3");
                                                            #line 2796 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 4222 "PrintCLike.cpp"
  append(L"2");
                                                            #line 2799 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(semicolon());
                                                                  if (isJava())
                                                                  {
                                                            #line 4229 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if (top >= iStack.length)\n");
  append(L"  {\n");
  append(L"    iStack = Arrays.copyOf(iStack, iStack.length << 1);\n");
  append(L"  }");
                                                            #line 2807 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isCSharp())
                                                                  {
                                                            #line 4239 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if (top >= iStack.Length)\n");
  append(L"  {\n");
  append(L"    Array.Resize(ref iStack, iStack.Length << 1);\n");
  append(L"  }");
                                                            #line 2814 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isCpp())
                                                                  {
                                                            #line 4249 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if (top >= (int) iStack.size())\n");
  append(L"    iStack.resize(iStack.size() == 0 ? ");
                                                            #line 2819 "PrintCLike.cpp.template"
                                                                    print(tree ? L"192" : L"128");
                                                            #line 4255 "PrintCLike.cpp"
  append(L" : iStack.size() << 1);");
                                                            #line 2821 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isScala())
                                                                  {
                                                            #line 4261 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if (top >= iStack.size) {\n");
  append(L"    val newStack = new Array[Int](iStack.size << 1)\n");
  append(L"    Array.copy(iStack, 0, newStack, 0, iStack.size)\n");
  append(L"    iStack = newStack\n");
  append(L"  }");
                                                            #line 2829 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isGo())
                                                                  {
                                                            #line 4272 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if this.top >= len(this.iStack) {\n");
  append(L"    this.iStack = append(this.iStack, this.iStack...)\n");
  append(L"  }");
                                                            #line 2835 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isPython())
                                                                  {
                                                            #line 4281 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if self.top >= len(self.iStack):\n");
  append(L"    self.iStack.extend([0 for _ in range(len(self.iStack))])");
                                                            #line 2840 "PrintCLike.cpp.template"
                                                                  }
                                                                  if (tree)
                                                                  {
                                                            #line 4289 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 2844 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 4294 "PrintCLike.cpp"
  append(L"iStack");
                                                            #line 2845 "PrintCLike.cpp.template"
                                                                    print(leftbracket());
                                                                    print(thiz());
                                                            #line 4299 "PrintCLike.cpp"
  append(L"top - 2");
                                                            #line 2847 "PrintCLike.cpp.template"
                                                                    print(rightbracket());
                                                            #line 4303 "PrintCLike.cpp"
  append(L" = begin");
                                                            #line 2848 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                  }
                                                            #line 4308 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 2851 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 4313 "PrintCLike.cpp"
  append(L"iStack");
                                                            #line 2852 "PrintCLike.cpp.template"
                                                                  print(leftbracket());
                                                                  print(thiz());
                                                            #line 4318 "PrintCLike.cpp"
  append(L"top - 1");
                                                            #line 2854 "PrintCLike.cpp.template"
                                                                  print(rightbracket());
                                                            #line 4322 "PrintCLike.cpp"
  append(L" = state");
                                                            #line 2855 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                            #line 4326 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 2857 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 4331 "PrintCLike.cpp"
  append(L"iStack");
                                                            #line 2858 "PrintCLike.cpp.template"
                                                                  print(leftbracket());
                                                                  print(thiz());
                                                            #line 4336 "PrintCLike.cpp"
  append(L"top");
                                                            #line 2860 "PrintCLike.cpp.template"
                                                                  print(rightbracket());
                                                            #line 4340 "PrintCLike.cpp"
  append(L" = lookback");
                                                            #line 2861 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                  print(rightBrace());
                                                            #line 4345 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 2864 "PrintCLike.cpp.template"
                                                                  printCountMethod();

                                                                  WString args(L"int target, int initialState");
                                                                  if (tree)
                                                                  {
                                                                    args += L", ";
                                                                    if (! isTypescript()) args += staticPrefix();
                                                                    args += L"BottomUpEventHandler ";
                                                                    if (isCpp()) args += L"*";
                                                                    args += L"eventHandler";
                                                                  }
                                                                  openMethod(voidType(), L"", L"parse", args.c_str());
                                                                  print(leftBrace());
                                                                  increaseIndent();
                                                            #line 4362 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 2879 "PrintCLike.cpp.template"
                                                                  print(intVar());
                                                            #line 4366 "PrintCLike.cpp"
  append(L"state");
                                                            #line 2880 "PrintCLike.cpp.template"
                                                                  print(assign());
                                                            #line 4370 "PrintCLike.cpp"
  append(L"initialState");
                                                            #line 2881 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                  if (tree || useGlr)
                                                                  {
                                                            #line 4376 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 2885 "PrintCLike.cpp.template"
                                                                    print(intVar());
                                                            #line 4380 "PrintCLike.cpp"
  append(L"bw");
                                                            #line 2886 "PrintCLike.cpp.template"
                                                                    print(assign());
                                                                    print(thiz());
                                                            #line 4385 "PrintCLike.cpp"
  append(L"e0");
                                                            #line 2888 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 4389 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 2890 "PrintCLike.cpp.template"
                                                                    print(intVar());
                                                            #line 4393 "PrintCLike.cpp"
  append(L"bs");
                                                            #line 2891 "PrintCLike.cpp.template"
                                                                    print(assign());
                                                                    print(thiz());
                                                            #line 4398 "PrintCLike.cpp"
  append(L"e0");
                                                            #line 2893 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                  }
                                                                  if (tree)
                                                                  {
                                                            #line 4405 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 2898 "PrintCLike.cpp.template"
                                                                    print(intVar());
                                                            #line 4409 "PrintCLike.cpp"
  append(L"es");
                                                            #line 2899 "PrintCLike.cpp.template"
                                                                    print(assign());
                                                                    print(thiz());
                                                            #line 4414 "PrintCLike.cpp"
  append(L"e0");
                                                            #line 2901 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 4418 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 2903 "PrintCLike.cpp.template"
                                                                    print(intVar());
                                                            #line 4422 "PrintCLike.cpp"
  append(L"t");
                                                            #line 2904 "PrintCLike.cpp.template"
                                                                    print(assign());
                                                                    print(thiz());
                                                            #line 4427 "PrintCLike.cpp"
  append(L"top");
                                                            #line 2906 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                  }
                                                            #line 4432 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 2909 "PrintCLike.cpp.template"
                                                                  print(intVar());
                                                            #line 4436 "PrintCLike.cpp"
  append(L"action");
                                                            #line 2910 "PrintCLike.cpp.template"
                                                                  print(assign());
                                                                  print(thiz());
                                                            #line 4441 "PrintCLike.cpp"
  append(L"predict(state)");
                                                            #line 2912 "PrintCLike.cpp.template"
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
                                                            #line 4455 "PrintCLike.cpp"
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
                                                            #line 2936 "PrintCLike.cpp.template"
                                                                }
                                                                if (useGlr)
                                                                {
                                                            #line 4472 "PrintCLike.cpp"
  append(L"\n");
  append(L"  var thread: ");
                                                            #line 2940 "PrintCLike.cpp.template"
                                                                  print(className.c_str());
                                                            #line 4477 "PrintCLike.cpp"
  append(L".ParsingThread = null");
                                                            #line 2941 "PrintCLike.cpp.template"
                                                                }
                                                            #line 4481 "PrintCLike.cpp"
  append(L"\n");
  append(L"  var input: String = null");
                                                            #line 2943 "PrintCLike.cpp.template"
                                                                if (! noLexer)
                                                                {
                                                            #line 4487 "PrintCLike.cpp"
  append(L"\n");
  append(L"  var size = 0");
                                                            #line 2946 "PrintCLike.cpp.template"
                                                                }
                                                                if (tree && useGlr)
                                                                {
                                                            #line 4494 "PrintCLike.cpp"
  append(L"\n");
  append(L"  var eventHandler: ");
                                                            #line 2950 "PrintCLike.cpp.template"
                                                                  print(className.c_str());
                                                            #line 4499 "PrintCLike.cpp"
  append(L".BottomUpEventHandler = null");
                                                            #line 2951 "PrintCLike.cpp.template"
                                                                }
                                                                if (noLexer)
                                                                {
                                                            #line 4505 "PrintCLike.cpp"
  append(L"\n");
  append(L"  var lexer: Lexer = null\n");
  append(L"  var token = new Token");
                                                            #line 2956 "PrintCLike.cpp.template"
                                                                }
                                                                if (useGlr)
                                                                {
                                                            #line 4513 "PrintCLike.cpp"
  append(L"\n");
  append(L"  var maxId = 0");
                                                            #line 2960 "PrintCLike.cpp.template"
                                                                }
                                                                if (trace)
                                                                {
                                                            #line 4520 "PrintCLike.cpp"
  append(L"\n");
  append(L"  var err: Writer = new OutputStreamWriter(System.err, \"UTF-8\")");
                                                            #line 2965 "PrintCLike.cpp.template"
                                                                }
                                                            #line 4525 "PrintCLike.cpp"
  append(L"\n");
  append(L"}\n");
  append(L"\n");
  append(L"object ");
                                                            #line 2969 "PrintCLike.cpp.template"
                                                                print(className.c_str());
                                                            #line 4532 "PrintCLike.cpp"
  append(L" {\n");
  append(L"\n");
  append(L"  def getOffendingToken(e: ParseException) = {\n");
  append(L"    if (e.offending < 0) null else TOKEN(e.offending)\n");
  append(L"  }\n");
                                                            #line 2976 "PrintCLike.cpp.template"
                                                              }
                                                            }

                                                            void PrintCLike::printThreadBody1()
                                                            {
                                                              Trace("PrintCLike::printThreadBody1");

                                                              if (isLrParser)
                                                              {
                                                            #line 4548 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 2986 "PrintCLike.cpp.template"
                                                                print(intVar());
                                                            #line 4552 "PrintCLike.cpp"
  append(L"nonterminalId");
                                                            #line 2987 "PrintCLike.cpp.template"
                                                                print(assign());
                                                            #line 4556 "PrintCLike.cpp"
  append(L"-1");
                                                            #line 2988 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                if (isHaxe() || isScala() || isPython())
                                                                {
                                                            #line 4562 "PrintCLike.cpp"
  append(L"\n");
  append(L"while ");
                                                            #line 2992 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                                  if (isPython())
                                                                  {
                                                            #line 4569 "PrintCLike.cpp"
  append(L"T");
                                                            #line 2995 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 4575 "PrintCLike.cpp"
  append(L"t");
                                                            #line 2998 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 4579 "PrintCLike.cpp"
  append(L"rue");
                                                            #line 2999 "PrintCLike.cpp.template"
                                                                  print(ifRightParen());
                                                                }
                                                                else if (isGo())
                                                                {
                                                            #line 4586 "PrintCLike.cpp"
  append(L"\n");
  append(L"for");
                                                            #line 3004 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 4593 "PrintCLike.cpp"
  append(L"\n");
  append(L"for (;;)");
                                                            #line 3008 "PrintCLike.cpp.template"
                                                                }
                                                                print(leftBrace());
                                                                increaseIndent();
                                                                if (trace)
                                                                {
                                                                  if (isCpp())
                                                                  {
                                                            #line 4604 "PrintCLike.cpp"
  append(L"\n");
  append(L"fprintf(stderr, \"  <parse ");
                                                            #line 3016 "PrintCLike.cpp.template"
                                                                    if (useGlr)
                                                                    {
                                                            #line 4610 "PrintCLike.cpp"
  append(L"thread=\\\"%d\\\" offset=\\\"%d\\\" ");
                                                            #line 3018 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 4614 "PrintCLike.cpp"
  append(L"state=\\\"%d\\\" input=\\\"%s%s%s\\\" action=\\\"\",");
                                                            #line 3020 "PrintCLike.cpp.template"
                                                                    if (useGlr)
                                                                    {
                                                            #line 4619 "PrintCLike.cpp"
  append(L"\n");
  append(L"  id,\n");
  append(L"  e0,");
                                                            #line 3024 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 4625 "PrintCLike.cpp"
  append(L"\n");
  append(L"  state,\n");
  append(L"  nonterminalId < 0 ? \"\" : ");
                                                            #line 3027 "PrintCLike.cpp.template"
                                                                    if (stringIntroducer()[0])
                                                                    {
                                                            #line 4632 "PrintCLike.cpp"
  append(L"Utf8Encoder::encode(");
                                                            #line 3029 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 4636 "PrintCLike.cpp"
  append(L"xmlEscape(");
                                                            #line 3030 "PrintCLike.cpp.template"
                                                                    print(isGo() ? L"nonterminal" : L"NONTERMINAL");
                                                            #line 4640 "PrintCLike.cpp"
  append(L"[nonterminalId], 0).c_str()");
                                                            #line 3032 "PrintCLike.cpp.template"
                                                                    if (stringIntroducer()[0])
                                                                    {
                                                            #line 4645 "PrintCLike.cpp"
  append(L").c_str()");
                                                            #line 3034 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 4649 "PrintCLike.cpp"
  append(L",\n");
  append(L"  nonterminalId < 0 || l1 <= 0 ? \"\" : \" \",\n");
  append(L"  l1 <= 0 ? \"\" : ");
                                                            #line 3037 "PrintCLike.cpp.template"
                                                                    if (stringIntroducer()[0])
                                                                    {
                                                            #line 4656 "PrintCLike.cpp"
  append(L"Utf8Encoder::encode(");
                                                            #line 3039 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 4660 "PrintCLike.cpp"
  append(L"xmlEscape(lookaheadString().c_str(), 0).c_str()");
                                                            #line 3040 "PrintCLike.cpp.template"
                                                                    if (stringIntroducer()[0])
                                                                    {
                                                            #line 4665 "PrintCLike.cpp"
  append(L").c_str()");
                                                            #line 3042 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 4669 "PrintCLike.cpp"
  append(L");\n");
                                                            #line 3044 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                                    if (isHaxe())
                                                                    {
                                                            #line 4677 "PrintCLike.cpp"
  append(L"\n");
  append(L"var traceLine = ");
                                                            #line 3050 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 4684 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3054 "PrintCLike.cpp.template"
                                                                      print(writeTrace());
                                                                    }
                                                            #line 4689 "PrintCLike.cpp"
  append(L"\"  <parse ");
                                                            #line 3056 "PrintCLike.cpp.template"
                                                                    if (useGlr)
                                                                    {
                                                            #line 4694 "PrintCLike.cpp"
  append(L"thread=\\\"\" + ");
                                                            #line 3058 "PrintCLike.cpp.template"
                                                                      if (isGo())
                                                                      {
                                                            #line 4699 "PrintCLike.cpp"
  append(L"strconv.Itoa(");
                                                            #line 3060 "PrintCLike.cpp.template"
                                                                      }
                                                                      else if (isPython())
                                                                      {
                                                            #line 4705 "PrintCLike.cpp"
  append(L"str(");
                                                            #line 3063 "PrintCLike.cpp.template"
                                                                      }
                                                                      print(thiz());
                                                            #line 4710 "PrintCLike.cpp"
  append(L"id");
                                                            #line 3065 "PrintCLike.cpp.template"
                                                                      if (isGo() || isPython())
                                                                      {
                                                            #line 4715 "PrintCLike.cpp"
  append(L")");
                                                            #line 3067 "PrintCLike.cpp.template"
                                                                      }
                                                            #line 4719 "PrintCLike.cpp"
  append(L" + \"\\\" offset=\\\"\" + ");
                                                            #line 3068 "PrintCLike.cpp.template"
                                                                      if (isGo())
                                                                      {
                                                            #line 4724 "PrintCLike.cpp"
  append(L"strconv.Itoa(");
                                                            #line 3070 "PrintCLike.cpp.template"
                                                                      }
                                                                      else if (isPython())
                                                                      {
                                                            #line 4730 "PrintCLike.cpp"
  append(L"str(");
                                                            #line 3073 "PrintCLike.cpp.template"
                                                                      }
                                                                      print(thiz());
                                                            #line 4735 "PrintCLike.cpp"
  append(L"e0");
                                                            #line 3075 "PrintCLike.cpp.template"
                                                                      if (isGo() || isPython())
                                                                      {
                                                            #line 4740 "PrintCLike.cpp"
  append(L")");
                                                            #line 3077 "PrintCLike.cpp.template"
                                                                      }
                                                            #line 4744 "PrintCLike.cpp"
  append(L" + \"\\\" ");
                                                            #line 3078 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 4748 "PrintCLike.cpp"
  append(L"state=\\\"\" + ");
                                                            #line 3079 "PrintCLike.cpp.template"
                                                                    if (isGo())
                                                                    {
                                                            #line 4753 "PrintCLike.cpp"
  append(L"strconv.Itoa(");
                                                            #line 3081 "PrintCLike.cpp.template"
                                                                    }
                                                                    else if (isPython())
                                                                    {
                                                            #line 4759 "PrintCLike.cpp"
  append(L"str(");
                                                            #line 3084 "PrintCLike.cpp.template"
                                                                    }
                                                                    if (useGlr) print(thiz());
                                                            #line 4764 "PrintCLike.cpp"
  append(L"state");
                                                            #line 3086 "PrintCLike.cpp.template"
                                                                    if (isGo() || isPython())
                                                                    {
                                                            #line 4769 "PrintCLike.cpp"
  append(L")");
                                                            #line 3088 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 4773 "PrintCLike.cpp"
  append(L" + \"\\\" input=\\\"\"");
                                                            #line 3089 "PrintCLike.cpp.template"
                                                                    print(endWriteTrace());
                                                                    print(semicolon());
                                                            #line 4778 "PrintCLike.cpp"
  append(L"\n");
  append(L"if ");
                                                            #line 3093 "PrintCLike.cpp.template"
                                                                    print(ifLeftParen());
                                                            #line 4783 "PrintCLike.cpp"
  append(L"nonterminalId >= 0");
                                                            #line 3094 "PrintCLike.cpp.template"
                                                                    print(ifRightParen());
                                                                    print(leftBrace());
                                                            #line 4788 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3097 "PrintCLike.cpp.template"
                                                                    print(writeTrace());
                                                                    print(staticPrefix());
                                                            #line 4794 "PrintCLike.cpp"
  append(L"xmlEscape(");
                                                            #line 3100 "PrintCLike.cpp.template"
                                                                    print(staticPrefix());
                                                                    print(isGo() ? L"nonterminal" : L"NONTERMINAL");
                                                                    print(leftbracket());
                                                            #line 4800 "PrintCLike.cpp"
  append(L"nonterminalId");
                                                            #line 3103 "PrintCLike.cpp.template"
                                                                    print(rightbracket());
                                                            #line 4804 "PrintCLike.cpp"
  append(L")");
                                                            #line 3104 "PrintCLike.cpp.template"
                                                                    print(endWriteTrace());
                                                                    print(semicolon());
                                                            #line 4809 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if ");
                                                            #line 3107 "PrintCLike.cpp.template"
                                                                    print(ifLeftParen());
                                                                    print(thiz());
                                                            #line 4815 "PrintCLike.cpp"
  append(L"l1 != 0");
                                                            #line 3109 "PrintCLike.cpp.template"
                                                                    print(ifRightParen());
                                                                    printIndented(1, leftBrace());
                                                            #line 4820 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 3112 "PrintCLike.cpp.template"
                                                                    print(writeTrace());
                                                            #line 4825 "PrintCLike.cpp"
  append(L"\" \"");
                                                            #line 3113 "PrintCLike.cpp.template"
                                                                    print(endWriteTrace());
                                                                    print(semicolon());
                                                                    increaseIndent();
                                                                    print(rightBrace());
                                                                    decreaseIndent();
                                                                    print(rightBrace());
                                                            #line 4834 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3120 "PrintCLike.cpp.template"
                                                                    print(writeTrace());
                                                                    print(staticPrefix());
                                                            #line 4839 "PrintCLike.cpp"
  append(L"xmlEscape(");
                                                            #line 3122 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 4843 "PrintCLike.cpp"
  append(L"lookaheadString");
                                                            #line 3123 "PrintCLike.cpp.template"
                                                                    if (! isScala()) print(L"()");
                                                            #line 4847 "PrintCLike.cpp"
  append(L") + \"\\\" action=\\\"\"");
                                                            #line 3124 "PrintCLike.cpp.template"
                                                                    print(endWriteTrace());
                                                                    print(semicolon());
                                                                  }
                                                                }
                                                            #line 4854 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3129 "PrintCLike.cpp.template"
                                                                print(intVal());
                                                            #line 4858 "PrintCLike.cpp"
  append(L"argument");
                                                            #line 3130 "PrintCLike.cpp.template"
                                                                print(assign());
                                                                if (useGlr) print(thiz());
                                                            #line 4863 "PrintCLike.cpp"
  append(L"action >> ");
                                                            #line 3132 "PrintCLike.cpp.template"
                                                                print(format.toString<wchar_t>(grammar->states->dominoBits + LrStates::actionBits));
                                                                print(semicolon());
                                                            #line 4868 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3135 "PrintCLike.cpp.template"
                                                                print(intVal());
                                                            #line 4872 "PrintCLike.cpp"
  append(L"lookback");
                                                            #line 3136 "PrintCLike.cpp.template"
                                                                print(assign());
                                                            #line 4876 "PrintCLike.cpp"
  append(L"(");
                                                            #line 3137 "PrintCLike.cpp.template"
                                                                if (useGlr) print(thiz());
                                                            #line 4880 "PrintCLike.cpp"
  append(L"action >> ");
                                                            #line 3138 "PrintCLike.cpp.template"
                                                                print(format.toString<wchar_t>((int) LrStates::actionBits));
                                                            #line 4884 "PrintCLike.cpp"
  append(L") & ");
                                                            #line 3139 "PrintCLike.cpp.template"
                                                                print(format.toString<wchar_t>((1 << grammar->states->dominoBits) -1));
                                                                print(semicolon());
                                                            #line 4889 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3142 "PrintCLike.cpp.template"
                                                                print(intVar());
                                                            #line 4893 "PrintCLike.cpp"
  append(L"shift");
                                                            #line 3143 "PrintCLike.cpp.template"
                                                                print(assign());
                                                            #line 4897 "PrintCLike.cpp"
  append(L"-1");
                                                            #line 3144 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 4901 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3146 "PrintCLike.cpp.template"
                                                                print(intVar());
                                                            #line 4905 "PrintCLike.cpp"
  append(L"reduce");
                                                            #line 3147 "PrintCLike.cpp.template"
                                                                print(assign());
                                                            #line 4909 "PrintCLike.cpp"
  append(L"-1");
                                                            #line 3148 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 4913 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3150 "PrintCLike.cpp.template"
                                                                print(intVar());
                                                            #line 4917 "PrintCLike.cpp"
  append(L"symbols");
                                                            #line 3151 "PrintCLike.cpp.template"
                                                                print(assign());
                                                            #line 4921 "PrintCLike.cpp"
  append(L"-1");
                                                            #line 3152 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                if (isPython())
                                                                {
                                                            #line 4927 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3157 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 4931 "PrintCLike.cpp"
  append(L"action &= ");
                                                            #line 3158 "PrintCLike.cpp.template"
                                                                  print(format.toString<wchar_t>((int) LrStates::actionMask));
                                                                }
                                                                else
                                                                {
                                                            #line 4938 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3163 "PrintCLike.cpp.template"
                                                                  if (! isScala())
                                                                  {
                                                            #line 4943 "PrintCLike.cpp"
  append(L"switch ");
                                                            #line 3165 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(ifLeftParen());
                                                                  if (useGlr) print(thiz());
                                                            #line 4949 "PrintCLike.cpp"
  append(L"action & ");
                                                            #line 3168 "PrintCLike.cpp.template"
                                                                  print(format.toString<wchar_t>((int) LrStates::actionMask));
                                                                  print(ifRightParen());
                                                                  if (isScala())
                                                                  {
                                                            #line 4956 "PrintCLike.cpp"
  append(L" match");
                                                            #line 3172 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(leftBrace());
                                                                }
                                                                if (isPython())
                                                                {
                                                            #line 4964 "PrintCLike.cpp"
  append(L"\n");
  append(L"if ");
                                                            #line 3178 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 4969 "PrintCLike.cpp"
  append(L"action == ");
                                                            #line 3179 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 4975 "PrintCLike.cpp"
  append(L"\n");
  append(L"case ");
                                                            #line 3183 "PrintCLike.cpp.template"
                                                                }
                                                                print(format.toString<wchar_t>((int) LrStates::SHIFT));
                                                                print(caseIntroducer());
                                                            #line 4982 "PrintCLike.cpp"
  append(L" ");
                                                            #line 3186 "PrintCLike.cpp.template"
                                                                print(inlineCommentIntroducer());
                                                            #line 4986 "PrintCLike.cpp"
  append(L"SHIFT\n");
  append(L"  shift = argument");
                                                            #line 3188 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                if (! isHaxe() && ! isScala() && ! isGo() && ! isPython())
                                                                {
                                                            #line 4993 "PrintCLike.cpp"
  append(L"\n");
  append(L"  break");
                                                            #line 3192 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                            #line 4999 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3195 "PrintCLike.cpp.template"
                                                                if (isPython())
                                                                {
                                                            #line 5004 "PrintCLike.cpp"
  append(L"\n");
  append(L"elif ");
                                                            #line 3198 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 5009 "PrintCLike.cpp"
  append(L"action == ");
                                                            #line 3199 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 5015 "PrintCLike.cpp"
  append(L"\n");
  append(L"case ");
                                                            #line 3203 "PrintCLike.cpp.template"
                                                                }
                                                                print(format.toString<wchar_t>((int) LrStates::REDUCE));
                                                                print(caseIntroducer());
                                                            #line 5022 "PrintCLike.cpp"
  append(L" ");
                                                            #line 3206 "PrintCLike.cpp.template"
                                                                print(inlineCommentIntroducer());
                                                            #line 5026 "PrintCLike.cpp"
  append(L"REDUCE\n");
  append(L"  reduce = argument");
                                                            #line 3208 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 5031 "PrintCLike.cpp"
  append(L"\n");
  append(L"  symbols = lookback");
                                                            #line 3210 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                if (! isHaxe() && ! isScala() && ! isGo() && ! isPython())
                                                                {
                                                            #line 5038 "PrintCLike.cpp"
  append(L"\n");
  append(L"  break");
                                                            #line 3214 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                                if (grammar->states->hasLookback)
                                                                {
                                                            #line 5046 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3219 "PrintCLike.cpp.template"
                                                                  if (isPython())
                                                                  {
                                                            #line 5051 "PrintCLike.cpp"
  append(L"\n");
  append(L"elif ");
                                                            #line 3222 "PrintCLike.cpp.template"
                                                                    if (useGlr) print(thiz());
                                                            #line 5056 "PrintCLike.cpp"
  append(L"action == ");
                                                            #line 3223 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 5062 "PrintCLike.cpp"
  append(L"\n");
  append(L"case ");
                                                            #line 3227 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(format.toString<wchar_t>((int) LrStates::REDUCE_LOOKBACK));
                                                                  print(caseIntroducer());
                                                            #line 5069 "PrintCLike.cpp"
  append(L" ");
                                                            #line 3230 "PrintCLike.cpp.template"
                                                                  print(inlineCommentIntroducer());
                                                            #line 5073 "PrintCLike.cpp"
  append(L"REDUCE+LOOKBACK\n");
  append(L"  reduce = argument");
                                                            #line 3232 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                            #line 5078 "PrintCLike.cpp"
  append(L"\n");
  append(L"  symbols = ");
                                                            #line 3234 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                                  if (useGlr)
                                                                  {
                                                            #line 5085 "PrintCLike.cpp"
  append(L"stack");
                                                            #line 3237 "PrintCLike.cpp.template"
                                                                    print(arrow());
                                                                  }
                                                                  if (isGo() && useGlr)
                                                                  {
                                                            #line 5092 "PrintCLike.cpp"
  append(L"Count");
                                                            #line 3241 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 5098 "PrintCLike.cpp"
  append(L"count");
                                                            #line 3244 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 5102 "PrintCLike.cpp"
  append(L"(lookback)");
                                                            #line 3245 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                  if (! isHaxe() && ! isScala() && ! isGo() && ! isPython())
                                                                  {
                                                            #line 5108 "PrintCLike.cpp"
  append(L"\n");
  append(L"  break");
                                                            #line 3249 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                  }
                                                                }
                                                            #line 5115 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3253 "PrintCLike.cpp.template"
                                                                if (isPython())
                                                                {
                                                            #line 5120 "PrintCLike.cpp"
  append(L"\n");
  append(L"elif ");
                                                            #line 3256 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 5125 "PrintCLike.cpp"
  append(L"action == ");
                                                            #line 3257 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 5131 "PrintCLike.cpp"
  append(L"\n");
  append(L"case ");
                                                            #line 3261 "PrintCLike.cpp.template"
                                                                }
                                                                print(format.toString<wchar_t>((int) LrStates::SHIFT_REDUCE));
                                                                print(caseIntroducer());
                                                            #line 5138 "PrintCLike.cpp"
  append(L" ");
                                                            #line 3264 "PrintCLike.cpp.template"
                                                                print(inlineCommentIntroducer());
                                                            #line 5142 "PrintCLike.cpp"
  append(L"SHIFT+REDUCE\n");
  append(L"  shift = ");
                                                            #line 3266 "PrintCLike.cpp.template"
                                                                if (useGlr) print(thiz());
                                                            #line 5147 "PrintCLike.cpp"
  append(L"state");
                                                            #line 3267 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 5151 "PrintCLike.cpp"
  append(L"\n");
  append(L"  reduce = argument");
                                                            #line 3269 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 5156 "PrintCLike.cpp"
  append(L"\n");
  append(L"  symbols = lookback + 1");
                                                            #line 3271 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                if (! isHaxe() && ! isScala() && ! isGo() && ! isPython())
                                                                {
                                                            #line 5163 "PrintCLike.cpp"
  append(L"\n");
  append(L"  break");
                                                            #line 3275 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                                if (grammar->states->hasLookback)
                                                                {
                                                            #line 5171 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3280 "PrintCLike.cpp.template"
                                                                  if (isPython())
                                                                  {
                                                            #line 5176 "PrintCLike.cpp"
  append(L"\n");
  append(L"elif ");
                                                            #line 3283 "PrintCLike.cpp.template"
                                                                    if (useGlr) print(thiz());
                                                            #line 5181 "PrintCLike.cpp"
  append(L"action == ");
                                                            #line 3284 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 5187 "PrintCLike.cpp"
  append(L"\n");
  append(L"case ");
                                                            #line 3288 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(format.toString<wchar_t>((int) LrStates::SHIFT_REDUCE_LOOKBACK));
                                                                  print(caseIntroducer());
                                                            #line 5194 "PrintCLike.cpp"
  append(L" ");
                                                            #line 3291 "PrintCLike.cpp.template"
                                                                  print(inlineCommentIntroducer());
                                                            #line 5198 "PrintCLike.cpp"
  append(L"SHIFT+REDUCE+LOOKBACK\n");
  append(L"  shift = ");
                                                            #line 3293 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 5203 "PrintCLike.cpp"
  append(L"state");
                                                            #line 3294 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                            #line 5207 "PrintCLike.cpp"
  append(L"\n");
  append(L"  reduce = argument");
                                                            #line 3296 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                            #line 5212 "PrintCLike.cpp"
  append(L"\n");
  append(L"  symbols = ");
                                                            #line 3298 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                                  if (useGlr)
                                                                  {
                                                            #line 5219 "PrintCLike.cpp"
  append(L"stack");
                                                            #line 3301 "PrintCLike.cpp.template"
                                                                    print(arrow());
                                                                  }
                                                                  if (isGo() && useGlr)
                                                                  {
                                                            #line 5226 "PrintCLike.cpp"
  append(L"Count");
                                                            #line 3305 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 5232 "PrintCLike.cpp"
  append(L"count");
                                                            #line 3308 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 5236 "PrintCLike.cpp"
  append(L"(lookback) + 1");
                                                            #line 3309 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                  if (! isHaxe() && ! isScala() && ! isGo() && ! isPython())
                                                                  {
                                                            #line 5242 "PrintCLike.cpp"
  append(L"\n");
  append(L"  break");
                                                            #line 3313 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                  }
                                                                }
                                                            #line 5249 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3317 "PrintCLike.cpp.template"
                                                                if (isPython())
                                                                {
                                                            #line 5254 "PrintCLike.cpp"
  append(L"\n");
  append(L"elif ");
                                                            #line 3320 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 5259 "PrintCLike.cpp"
  append(L"action == ");
                                                            #line 3321 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 5265 "PrintCLike.cpp"
  append(L"\n");
  append(L"case ");
                                                            #line 3325 "PrintCLike.cpp.template"
                                                                }
                                                                print(format.toString<wchar_t>((int) LrStates::SHIFT_ACCEPT));
                                                                print(caseIntroducer());
                                                            #line 5272 "PrintCLike.cpp"
  append(L" ");
                                                            #line 3328 "PrintCLike.cpp.template"
                                                                print(inlineCommentIntroducer());
                                                            #line 5276 "PrintCLike.cpp"
  append(L"ACCEPT");
                                                            #line 3329 "PrintCLike.cpp.template"
                                                                if (trace)
                                                                {
                                                                  if (isCpp())
                                                                  {
                                                            #line 5283 "PrintCLike.cpp"
  append(L"\n");
  append(L"  fprintf(stderr, ");
                                                            #line 3334 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 5290 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3338 "PrintCLike.cpp.template"
                                                                    print(writeTrace());
                                                                  }
                                                            #line 5296 "PrintCLike.cpp"
  append(L"\"accept\\\"/>");
                                                            #line 3340 "PrintCLike.cpp.template"
                                                                  if (! isHaxe())
                                                                  {
                                                            #line 5301 "PrintCLike.cpp"
  append(L"\\n");
                                                            #line 3342 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 5305 "PrintCLike.cpp"
  append(L"\"");
                                                            #line 3343 "PrintCLike.cpp.template"
                                                                  print(endWriteTrace());
                                                                  print(semicolon());
                                                                  if (isHaxe())
                                                                  {
                                                            #line 5312 "PrintCLike.cpp"
  append(L"\n");
  append(L"  trace(traceLine);");
                                                            #line 3348 "PrintCLike.cpp.template"
                                                                  }
                                                                }
                                                                if (useGlr)
                                                                {
                                                            #line 5320 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3353 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 5325 "PrintCLike.cpp"
  append(L"accepted = ");
                                                            #line 3354 "PrintCLike.cpp.template"
                                                                  if (isPython())
                                                                  {
                                                            #line 5330 "PrintCLike.cpp"
  append(L"T");
                                                            #line 3356 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 5336 "PrintCLike.cpp"
  append(L"t");
                                                            #line 3359 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 5340 "PrintCLike.cpp"
  append(L"rue");
                                                            #line 3360 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                            #line 5344 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3362 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 5349 "PrintCLike.cpp"
  append(L"action = 0");
                                                            #line 3363 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                            #line 5353 "PrintCLike.cpp"
  append(L"\n");
  append(L"  return ");
                                                            #line 3365 "PrintCLike.cpp.template"
                                                                  if (isHaxe() || isTypescript() || isPython()) print(staticPrefix());
                                                            #line 5358 "PrintCLike.cpp"
  append(L"ACCEPTED");
                                                            #line 3366 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                                else
                                                                {
                                                            #line 5365 "PrintCLike.cpp"
  append(L"\n");
  append(L"  return");
                                                            #line 3371 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }

                                                                if (useGlr)
                                                                {
                                                            #line 5374 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3377 "PrintCLike.cpp.template"
                                                                  if (isPython())
                                                                  {
                                                            #line 5379 "PrintCLike.cpp"
  append(L"\n");
  append(L"elif ");
                                                            #line 3380 "PrintCLike.cpp.template"
                                                                    if (useGlr) print(thiz());
                                                            #line 5384 "PrintCLike.cpp"
  append(L"action == ");
                                                            #line 3381 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 5390 "PrintCLike.cpp"
  append(L"\n");
  append(L"case ");
                                                            #line 3385 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(format.toString<wchar_t>((int) LrStates::FORK));
                                                                  print(caseIntroducer());
                                                            #line 5397 "PrintCLike.cpp"
  append(L" ");
                                                            #line 3388 "PrintCLike.cpp.template"
                                                                  print(inlineCommentIntroducer());
                                                            #line 5401 "PrintCLike.cpp"
  append(L"FORK");
                                                            #line 3389 "PrintCLike.cpp.template"
                                                                  if (trace)
                                                                  {
                                                                    if (isCpp())
                                                                    {
                                                            #line 5408 "PrintCLike.cpp"
  append(L"\n");
  append(L"  fprintf(stderr, \"fork\\\"/>\\n\");");
                                                            #line 3394 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 5415 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3398 "PrintCLike.cpp.template"
                                                                      print(writeTrace());
                                                            #line 5420 "PrintCLike.cpp"
  append(L"\"fork\\\"/>");
                                                            #line 3399 "PrintCLike.cpp.template"
                                                                      if (! isHaxe())
                                                                      {
                                                            #line 5425 "PrintCLike.cpp"
  append(L"\\n\"");
                                                            #line 3401 "PrintCLike.cpp.template"
                                                                        print(endWriteTrace());
                                                                        print(semicolon());
                                                                      }
                                                                      else
                                                                      {
                                                            #line 5433 "PrintCLike.cpp"
  append(L"\";\n");
  append(L"  trace(traceLine);");
                                                            #line 3407 "PrintCLike.cpp.template"
                                                                      }
                                                                    }
                                                                  }
                                                                  if (isGo())
                                                                  {
                                                            #line 5442 "PrintCLike.cpp"
  append(L"\n");
  append(L"  heap.Push(this.threads, new(ParsingThread).copy(this, appendix[argument]))");
                                                            #line 3414 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isPython())
                                                                  {
                                                            #line 5449 "PrintCLike.cpp"
  append(L"\n");
  append(L"  forked = ");
                                                            #line 3418 "PrintCLike.cpp.template"
                                                                    print(staticPrefix());
                                                            #line 5454 "PrintCLike.cpp"
  append(L"ParsingThread().copy(self, ");
                                                            #line 3419 "PrintCLike.cpp.template"
                                                                    print(staticPrefix());
                                                            #line 5458 "PrintCLike.cpp"
  append(L"APPENDIX[argument])\n");
  append(L"  heapq.heappush(self.threads, (False, forked.e0, forked.id, forked))");
                                                            #line 3422 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 5465 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3426 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 5470 "PrintCLike.cpp"
  append(L"threads");
                                                            #line 3427 "PrintCLike.cpp.template"
                                                                    if (isCpp())
                                                                    {
                                                            #line 5475 "PrintCLike.cpp"
  append(L"->push(");
                                                            #line 3429 "PrintCLike.cpp.template"
                                                                    }
                                                                    else if (isScala())
                                                                    {
                                                            #line 5481 "PrintCLike.cpp"
  append(L" += ");
                                                            #line 3432 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 5487 "PrintCLike.cpp"
  append(L".offer(");
                                                            #line 3435 "PrintCLike.cpp.template"
                                                                    }
                                                                    if (isCpp() || isScala()) print(L"(");
                                                            #line 5492 "PrintCLike.cpp"
  append(L"new ParsingThread");
                                                            #line 3437 "PrintCLike.cpp.template"
                                                                    if (! isScala()) print(L"()");
                                                                    if (isCpp() || isScala()) print(L")");
                                                                    print(arrow());
                                                            #line 5498 "PrintCLike.cpp"
  append(L"copy(this");
                                                            #line 3440 "PrintCLike.cpp.template"
                                                                    if (isJavascript())
                                                                    {
                                                            #line 5503 "PrintCLike.cpp"
  append(L"Thread");
                                                            #line 3442 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 5507 "PrintCLike.cpp"
  append(L", ");
                                                            #line 3443 "PrintCLike.cpp.template"
                                                                    print(staticPrefix());
                                                            #line 5511 "PrintCLike.cpp"
  append(L"APPENDIX");
                                                            #line 3444 "PrintCLike.cpp.template"
                                                                    print(leftbracket());
                                                            #line 5515 "PrintCLike.cpp"
  append(L"argument");
                                                            #line 3445 "PrintCLike.cpp.template"
                                                                    print(rightbracket());
                                                            #line 5519 "PrintCLike.cpp"
  append(L")");
                                                            #line 3446 "PrintCLike.cpp.template"
                                                                    if (! isScala()) print(L")");
                                                                    print(semicolon());
                                                                  }
                                                            #line 5525 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3450 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 5530 "PrintCLike.cpp"
  append(L"action = ");
                                                            #line 3451 "PrintCLike.cpp.template"
                                                                  print(staticPrefix());
                                                                  if (isGo())
                                                                  {
                                                            #line 5536 "PrintCLike.cpp"
  append(L"appendix");
                                                            #line 3454 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 5542 "PrintCLike.cpp"
  append(L"APPENDIX");
                                                            #line 3457 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(leftbracket());
                                                            #line 5547 "PrintCLike.cpp"
  append(L"argument + 1");
                                                            #line 3459 "PrintCLike.cpp.template"
                                                                  print(rightbracket());
                                                                  print(semicolon());
                                                            #line 5552 "PrintCLike.cpp"
  append(L"\n");
  append(L"  return ");
                                                            #line 3462 "PrintCLike.cpp.template"
                                                                  if (isHaxe() || isTypescript() || isPython()) print(staticPrefix());
                                                            #line 5557 "PrintCLike.cpp"
  append(L"PARSING");
                                                            #line 3463 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                            #line 5562 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3466 "PrintCLike.cpp.template"
                                                                if (isPython())
                                                                {
                                                            #line 5567 "PrintCLike.cpp"
  append(L"\n");
  append(L"else");
                                                            #line 3469 "PrintCLike.cpp.template"
                                                                }
                                                                else if (isScala())
                                                                {
                                                            #line 5574 "PrintCLike.cpp"
  append(L"\n");
  append(L"case _");
                                                            #line 3473 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 5581 "PrintCLike.cpp"
  append(L"\n");
  append(L"default");
                                                            #line 3477 "PrintCLike.cpp.template"
                                                                }
                                                                print(caseIntroducer());
                                                            #line 5587 "PrintCLike.cpp"
  append(L" ");
                                                            #line 3479 "PrintCLike.cpp.template"
                                                                print(inlineCommentIntroducer());
                                                            #line 5591 "PrintCLike.cpp"
  append(L"ERROR");
                                                            #line 3480 "PrintCLike.cpp.template"
                                                                if (useGlr)
                                                                {
                                                                  if (trace)
                                                                  {
                                                                    if (isCpp())
                                                                    {
                                                            #line 5600 "PrintCLike.cpp"
  append(L"\n");
  append(L"  fprintf(stderr, \"fail\\\"/>\\n\");");
                                                            #line 3487 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 5607 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3491 "PrintCLike.cpp.template"
                                                                      print(writeTrace());
                                                            #line 5612 "PrintCLike.cpp"
  append(L"\"fail\\\"/>");
                                                            #line 3492 "PrintCLike.cpp.template"
                                                                      if (! isHaxe())
                                                                      {
                                                            #line 5617 "PrintCLike.cpp"
  append(L"\\n\"");
                                                            #line 3494 "PrintCLike.cpp.template"
                                                                        print(endWriteTrace());
                                                                        print(semicolon());
                                                                      }
                                                                      else
                                                                      {
                                                            #line 5625 "PrintCLike.cpp"
  append(L"\";\n");
  append(L"  trace(traceLine);");
                                                            #line 3500 "PrintCLike.cpp.template"
                                                                      }
                                                                    }
                                                                  }
                                                            #line 5632 "PrintCLike.cpp"
  append(L"\n");
  append(L"  return ");
                                                            #line 3504 "PrintCLike.cpp.template"
                                                                  if (isHaxe() || isTypescript() || isPython()) print(staticPrefix());
                                                            #line 5637 "PrintCLike.cpp"
  append(L"ERROR");
                                                            #line 3505 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                                else
                                                                {
                                                            #line 5644 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3510 "PrintCLike.cpp.template"
                                                                  print(beginThrowStmt());
                                                                  print(thiz());
                                                            #line 5650 "PrintCLike.cpp"
  append(L"b1, ");
                                                            #line 3512 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 5654 "PrintCLike.cpp"
  append(L"e1, ");
                                                            #line 3513 "PrintCLike.cpp.template"
                                                                  print(staticPrefix());
                                                                  if (isGo())
                                                                  {
                                                            #line 5660 "PrintCLike.cpp"
  append(L"tokenset");
                                                            #line 3516 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 5666 "PrintCLike.cpp"
  append(L"TOKENSET");
                                                            #line 3519 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(leftbracket());
                                                            #line 5671 "PrintCLike.cpp"
  append(L"state");
                                                            #line 3521 "PrintCLike.cpp.template"
                                                                  print(rightbracket());
                                                            #line 5675 "PrintCLike.cpp"
  append(L" + 1, ");
                                                            #line 3522 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 5679 "PrintCLike.cpp"
  append(L"l1, -1");
                                                            #line 3523 "PrintCLike.cpp.template"
                                                                  print(endThrowStmt());
                                                                  print(semicolon());
                                                                }
                                                                print(rightBrace());
                                                            #line 5686 "PrintCLike.cpp"
  append(L"\n");
  append(L"\n");
  append(L"if ");
                                                            #line 3529 "PrintCLike.cpp.template"
                                                                print(ifLeftParen());
                                                            #line 5692 "PrintCLike.cpp"
  append(L"shift >= 0");
                                                            #line 3530 "PrintCLike.cpp.template"
                                                                print(ifRightParen());
                                                                print(leftBrace());
                                                                if (trace)
                                                                {
                                                                  if (isCpp())
                                                                  {
                                                            #line 5701 "PrintCLike.cpp"
  append(L"\n");
  append(L"  fprintf(stderr, ");
                                                            #line 3537 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 5708 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3541 "PrintCLike.cpp.template"
                                                                    print(writeTrace());
                                                                  }
                                                            #line 5714 "PrintCLike.cpp"
  append(L"\"shift\"");
                                                            #line 3543 "PrintCLike.cpp.template"
                                                                  print(endWriteTrace());
                                                                  print(semicolon());
                                                                }
                                                            #line 5720 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if ");
                                                            #line 3547 "PrintCLike.cpp.template"
                                                                print(ifLeftParen());
                                                            #line 5725 "PrintCLike.cpp"
  append(L"nonterminalId < 0");
                                                            #line 3548 "PrintCLike.cpp.template"
                                                                print(ifRightParen());
                                                                printIndented(1, leftBrace());
                                                                if (tree)
                                                                {
                                                            #line 5732 "PrintCLike.cpp"
  append(L"\n");
  append(L"    if ");
                                                            #line 3553 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                                  if (useGlr) print(thiz());
                                                            #line 5738 "PrintCLike.cpp"
  append(L"eventHandler != ");
                                                            #line 3555 "PrintCLike.cpp.template"
                                                                  print(nullPtr());
                                                                  print(ifRightParen());
                                                                  printIndented(2, leftBrace());
                                                                  if (useGlr)
                                                                  {
                                                            #line 5746 "PrintCLike.cpp"
  append(L"\n");
  append(L"      if ");
                                                            #line 3561 "PrintCLike.cpp.template"
                                                                    print(ifLeftParen());
                                                                    print(thiz());
                                                                    if (isGo())
                                                                    {
                                                            #line 5754 "PrintCLike.cpp"
  append(L"IsUnambiguous");
                                                            #line 3565 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 5760 "PrintCLike.cpp"
  append(L"isUnambiguous");
                                                            #line 3568 "PrintCLike.cpp.template"
                                                                    }
                                                                    if (! isScala()) print(L"()");
                                                                    print(ifRightParen());
                                                                    printIndented(3, leftBrace());
                                                                    increaseIndent();
                                                                  }
                                                            #line 5769 "PrintCLike.cpp"
  append(L"\n");
  append(L"      ");
                                                            #line 3575 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 5774 "PrintCLike.cpp"
  append(L"eventHandler");
                                                            #line 3576 "PrintCLike.cpp.template"
                                                                  print(arrow());
                                                                  if (isGo())
                                                                  {
                                                            #line 5780 "PrintCLike.cpp"
  append(L"T");
                                                            #line 3579 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 5786 "PrintCLike.cpp"
  append(L"t");
                                                            #line 3582 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 5790 "PrintCLike.cpp"
  append(L"erminal(");
                                                            #line 3583 "PrintCLike.cpp.template"
                                                                  print(staticPrefix());
                                                                  print(isGo() ? L"token" : L"TOKEN");
                                                                  print(leftbracket());
                                                                  print(thiz());
                                                            #line 5797 "PrintCLike.cpp"
  append(L"l1");
                                                            #line 3587 "PrintCLike.cpp.template"
                                                                  print(rightbracket());
                                                            #line 5801 "PrintCLike.cpp"
  append(L", ");
                                                            #line 3588 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 5805 "PrintCLike.cpp"
  append(L"b1, ");
                                                            #line 3589 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 5809 "PrintCLike.cpp"
  append(L"e1)");
                                                            #line 3590 "PrintCLike.cpp.template"
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
                                                            #line 5822 "PrintCLike.cpp"
  append(L"\n");
  append(L"      ");
                                                            #line 3601 "PrintCLike.cpp.template"
                                                                    printIndented(3, elseWithBraces());
                                                            #line 5827 "PrintCLike.cpp"
  append(L"\n");
  append(L"        ");
                                                            #line 3603 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 5832 "PrintCLike.cpp"
  append(L"deferredEvent = ");
                                                            #line 3604 "PrintCLike.cpp.template"
                                                                    if (isGo())
                                                                    {
                                                            #line 5837 "PrintCLike.cpp"
  append(L"&TerminalEvent{&AbstractDeferredEvent{");
                                                            #line 3606 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                                      if (! isPython())
                                                                      {
                                                            #line 5845 "PrintCLike.cpp"
  append(L"new ");
                                                            #line 3611 "PrintCLike.cpp.template"
                                                                      }
                                                                      if (! isHaxe() && ! isTypescript()) print(staticPrefix());
                                                                      if (isJavascript() || isTypescript())
                                                                      {
                                                            #line 5852 "PrintCLike.cpp"
  append(L"DeferredEvent");
                                                            #line 3615 "PrintCLike.cpp.template"
                                                                      }
                                                                      else
                                                                      {
                                                            #line 5858 "PrintCLike.cpp"
  append(L"TerminalEvent");
                                                            #line 3618 "PrintCLike.cpp.template"
                                                                      }
                                                            #line 5862 "PrintCLike.cpp"
  append(L"(");
                                                            #line 3619 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(thiz());
                                                            #line 5867 "PrintCLike.cpp"
  append(L"deferredEvent, ");
                                                            #line 3621 "PrintCLike.cpp.template"
                                                                    print(staticPrefix());
                                                                    print(isGo() ? L"token" : L"TOKEN");
                                                                    print(leftbracket());
                                                                    print(thiz());
                                                            #line 5874 "PrintCLike.cpp"
  append(L"l1");
                                                            #line 3625 "PrintCLike.cpp.template"
                                                                    print(rightbracket());
                                                            #line 5878 "PrintCLike.cpp"
  append(L", ");
                                                            #line 3626 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 5882 "PrintCLike.cpp"
  append(L"b1, ");
                                                            #line 3627 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 5886 "PrintCLike.cpp"
  append(L"e1");
                                                            #line 3629 "PrintCLike.cpp.template"
                                                                    if (isTypescript())
                                                                    {
                                                            #line 5891 "PrintCLike.cpp"
  append(L", null");
                                                            #line 3632 "PrintCLike.cpp.template"
                                                                    }
                                                                    if (isGo())
                                                                    {
                                                            #line 5897 "PrintCLike.cpp"
  append(L"}}");
                                                            #line 3636 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 5903 "PrintCLike.cpp"
  append(L")");
                                                            #line 3640 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                                    }
                                                                    increaseIndent(3);
                                                                    print(rightBrace());
                                                                    decreaseIndent();
                                                                    print(rightBrace());
                                                                    decreaseIndent(2);
                                                                  }
                                                            #line 5914 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 3649 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 5919 "PrintCLike.cpp"
  append(L"es = ");
                                                            #line 3650 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 5923 "PrintCLike.cpp"
  append(L"e1");
                                                            #line 3651 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                                if (useGlr)
                                                                {
                                                            #line 5930 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 3656 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 5935 "PrintCLike.cpp"
  append(L"stack = ");
                                                            #line 3657 "PrintCLike.cpp.template"
                                                                  if (isGo())
                                                                  {
                                                            #line 5940 "PrintCLike.cpp"
  append(L"&StackNode{");
                                                            #line 3659 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                                    if (! isPython())
                                                                    {
                                                            #line 5948 "PrintCLike.cpp"
  append(L"new ");
                                                            #line 3664 "PrintCLike.cpp.template"
                                                                    }
                                                                    if (! isHaxe() && ! isTypescript()) print(staticPrefix());
                                                            #line 5953 "PrintCLike.cpp"
  append(L"StackNode(");
                                                            #line 3666 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(thiz());
                                                            #line 5958 "PrintCLike.cpp"
  append(L"state, ");
                                                            #line 3668 "PrintCLike.cpp.template"
                                                                  if (grammar->states->hasLookback)
                                                                  {
                                                            #line 5963 "PrintCLike.cpp"
  append(L"lookback, ");
                                                            #line 3670 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(thiz());
                                                            #line 5968 "PrintCLike.cpp"
  append(L"b1, ");
                                                            #line 3672 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 5972 "PrintCLike.cpp"
  append(L"stack");
                                                            #line 3673 "PrintCLike.cpp.template"
                                                                  print(isGo() ? L"}" : L")");
                                                                  print(semicolon());
                                                                }
                                                                else
                                                                {
                                                            #line 5980 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 3679 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 5985 "PrintCLike.cpp"
  append(L"push(state, lookback");
                                                            #line 3680 "PrintCLike.cpp.template"
                                                                  if (tree)
                                                                  {
                                                            #line 5990 "PrintCLike.cpp"
  append(L", ");
                                                            #line 3682 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 5994 "PrintCLike.cpp"
  append(L"b1");
                                                            #line 3683 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 5998 "PrintCLike.cpp"
  append(L")");
                                                            #line 3684 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                            #line 6003 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 3687 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 6008 "PrintCLike.cpp"
  append(L"consume(");
                                                            #line 3688 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 6012 "PrintCLike.cpp"
  append(L"l1)");
                                                            #line 3689 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 6016 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3691 "PrintCLike.cpp.template"
                                                                printIndented(1, elseWithBraces());
                                                                if (useGlr)
                                                                {
                                                            #line 6023 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 3695 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 6028 "PrintCLike.cpp"
  append(L"stack = ");
                                                            #line 3696 "PrintCLike.cpp.template"
                                                                  if (isGo())
                                                                  {
                                                            #line 6033 "PrintCLike.cpp"
  append(L"&StackNode{");
                                                            #line 3698 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                                    if (! isPython())
                                                                    {
                                                            #line 6041 "PrintCLike.cpp"
  append(L"new ");
                                                            #line 3703 "PrintCLike.cpp.template"
                                                                    }
                                                                    if (! isHaxe() && ! isTypescript()) print(staticPrefix());
                                                            #line 6046 "PrintCLike.cpp"
  append(L"StackNode(");
                                                            #line 3705 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(thiz());
                                                            #line 6051 "PrintCLike.cpp"
  append(L"state, ");
                                                            #line 3707 "PrintCLike.cpp.template"
                                                                  if (grammar->states->hasLookback)
                                                                  {
                                                            #line 6056 "PrintCLike.cpp"
  append(L"lookback, ");
                                                            #line 3709 "PrintCLike.cpp.template"
                                                                  }
                                                                  if (tree)
                                                                  {
                                                                    print(thiz());
                                                            #line 6063 "PrintCLike.cpp"
  append(L"bs");
                                                            #line 3713 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 6069 "PrintCLike.cpp"
  append(L"0");
                                                            #line 3716 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 6073 "PrintCLike.cpp"
  append(L", ");
                                                            #line 3717 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 6077 "PrintCLike.cpp"
  append(L"stack");
                                                            #line 3718 "PrintCLike.cpp.template"
                                                                  print(isGo() ? L"}" : L")");
                                                                  print(semicolon());
                                                                }
                                                                else
                                                                {
                                                            #line 6085 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 3724 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 6090 "PrintCLike.cpp"
  append(L"push(state, lookback");
                                                            #line 3725 "PrintCLike.cpp.template"
                                                                  if (tree)
                                                                  {
                                                            #line 6095 "PrintCLike.cpp"
  append(L", bs");
                                                            #line 3727 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 6099 "PrintCLike.cpp"
  append(L")");
                                                            #line 3728 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                                increaseIndent();
                                                                print(rightBrace());
                                                                decreaseIndent();
                                                            #line 6107 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3734 "PrintCLike.cpp.template"
                                                                if (useGlr) print(thiz());
                                                            #line 6112 "PrintCLike.cpp"
  append(L"state = shift");
                                                            #line 3735 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                print(rightBrace());
                                                            #line 6117 "PrintCLike.cpp"
  append(L"\n");
  append(L"\n");
  append(L"if ");
                                                            #line 3739 "PrintCLike.cpp.template"
                                                                print(ifLeftParen());
                                                            #line 6123 "PrintCLike.cpp"
  append(L"reduce < 0");
                                                            #line 3740 "PrintCLike.cpp.template"
                                                                print(ifRightParen());
                                                                print(leftBrace());
                                                                if (trace)
                                                                {
                                                                  if (isCpp())
                                                                  {
                                                            #line 6132 "PrintCLike.cpp"
  append(L"\n");
  append(L"  fprintf(stderr, ");
                                                            #line 3747 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 6139 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3751 "PrintCLike.cpp.template"
                                                                    print(writeTrace());
                                                                  }
                                                            #line 6145 "PrintCLike.cpp"
  append(L"\"\\\"/>");
                                                            #line 3754 "PrintCLike.cpp.template"
                                                                  if (! isHaxe())
                                                                  {
                                                            #line 6150 "PrintCLike.cpp"
  append(L"\\n\"");
                                                            #line 3756 "PrintCLike.cpp.template"
                                                                    print(endWriteTrace());
                                                                    print(semicolon());
                                                                  }
                                                                  else
                                                                  {
                                                            #line 6158 "PrintCLike.cpp"
  append(L"\";\n");
  append(L"  trace(traceLine);");
                                                            #line 3762 "PrintCLike.cpp.template"
                                                                  }
                                                                }
                                                            #line 6164 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3765 "PrintCLike.cpp.template"
                                                                if (useGlr) print(thiz());
                                                            #line 6169 "PrintCLike.cpp"
  append(L"action = ");
                                                            #line 3766 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 6173 "PrintCLike.cpp"
  append(L"predict(");
                                                            #line 3767 "PrintCLike.cpp.template"
                                                                if (useGlr) print(thiz());
                                                            #line 6177 "PrintCLike.cpp"
  append(L"state)");
                                                            #line 3768 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                if (useGlr)
                                                                {
                                                                  if (isCpp())
                                                                  {
                                                            #line 6185 "PrintCLike.cpp"
  append(L"\n");
  append(L"  break");
                                                            #line 3774 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                  }
                                                                  else
                                                                  {
                                                            #line 6193 "PrintCLike.cpp"
  append(L"\n");
  append(L"  return ");
                                                            #line 3779 "PrintCLike.cpp.template"
                                                                    if (isHaxe() || isTypescript() || isPython()) print(staticPrefix());
                                                            #line 6198 "PrintCLike.cpp"
  append(L"PARSING");
                                                            #line 3780 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                  }
                                                                }
                                                                else
                                                                {
                                                            #line 6206 "PrintCLike.cpp"
  append(L"\n");
  append(L"  nonterminalId = -1");
                                                            #line 3786 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                            #line 6212 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 3789 "PrintCLike.cpp.template"
                                                                print(elseWithBraces());
                                                                if (hasCustomCode)
                                                                {
                                                            #line 6218 "PrintCLike.cpp"
  append(L"\n");
  append(L"  nonterminalId = ");
                                                            #line 3793 "PrintCLike.cpp.template"
                                                                  print(staticPrefix());
                                                                  if (isGo())
                                                                  {
                                                            #line 6225 "PrintCLike.cpp"
  append(L"reduction");
                                                            #line 3796 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 6231 "PrintCLike.cpp"
  append(L"REDUCTION");
                                                            #line 3799 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(leftbracket());
                                                            #line 6236 "PrintCLike.cpp"
  append(L"reduce");
                                                            #line 3801 "PrintCLike.cpp.template"
                                                                  print(rightbracket());
                                                                  print(semicolon());
                                                            #line 6241 "PrintCLike.cpp"
  append(L"\n");
  append(L"  reduce = ");
                                                            #line 3804 "PrintCLike.cpp.template"
                                                                  print(staticPrefix());
                                                                  if (isGo())
                                                                  {
                                                            #line 6248 "PrintCLike.cpp"
  append(L"reduction");
                                                            #line 3807 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 6254 "PrintCLike.cpp"
  append(L"REDUCTION");
                                                            #line 3810 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(leftbracket());
                                                            #line 6259 "PrintCLike.cpp"
  append(L"reduce + 1");
                                                            #line 3812 "PrintCLike.cpp.template"
                                                                  print(rightbracket());
                                                                  print(semicolon());
                                                            #line 6264 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if ");
                                                            #line 3815 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                            #line 6269 "PrintCLike.cpp"
  append(L"reduce >= 0");
                                                            #line 3816 "PrintCLike.cpp.template"
                                                                  print(ifRightParen());
                                                                  increaseIndent();
                                                                  print(leftBrace());
                                                                  if (useGlr)
                                                                  {
                                                            #line 6277 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if ");
                                                            #line 3822 "PrintCLike.cpp.template"
                                                                    print(ifLeftParen());
                                                                    print(thiz());
                                                                    if (isGo())
                                                                    {
                                                            #line 6285 "PrintCLike.cpp"
  append(L"IsUnambiguous");
                                                            #line 3826 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 6291 "PrintCLike.cpp"
  append(L"isUnambiguous");
                                                            #line 3829 "PrintCLike.cpp.template"
                                                                    }
                                                                    if (! isScala()) print(L"()");
                                                                    print(ifRightParen());
                                                                    print(leftBrace());
                                                            #line 6298 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 3834 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                                    print(isGo() && useGlr ? L"E" : L"e");
                                                            #line 6304 "PrintCLike.cpp"
  append(L"xecute(reduce)");
                                                            #line 3836 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 6308 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3838 "PrintCLike.cpp.template"
                                                                    print(elseWithBraces());
                                                            #line 6313 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 3840 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 6318 "PrintCLike.cpp"
  append(L"deferredCode = ");
                                                            #line 3841 "PrintCLike.cpp.template"
                                                                    if (isGo())
                                                                    {
                                                            #line 6323 "PrintCLike.cpp"
  append(L"&DeferredCode{");
                                                            #line 3844 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                                      if (! isPython())
                                                                      {
                                                            #line 6331 "PrintCLike.cpp"
  append(L"new ");
                                                            #line 3849 "PrintCLike.cpp.template"
                                                                      }
                                                                      if (! isHaxe() && ! isTypescript()) print(staticPrefix());
                                                            #line 6336 "PrintCLike.cpp"
  append(L"DeferredCode(");
                                                            #line 3851 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(thiz());
                                                            #line 6341 "PrintCLike.cpp"
  append(L"deferredCode, reduce, ");
                                                            #line 3853 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 6345 "PrintCLike.cpp"
  append(L"b0, ");
                                                            #line 3854 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 6349 "PrintCLike.cpp"
  append(L"e0");
                                                            #line 3856 "PrintCLike.cpp.template"
                                                                    if (isGo())
                                                                    {
                                                            #line 6354 "PrintCLike.cpp"
  append(L"}");
                                                            #line 3859 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 6360 "PrintCLike.cpp"
  append(L")");
                                                            #line 3863 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(semicolon());
                                                                    increaseIndent();
                                                                    print(rightBrace());
                                                                    decreaseIndent();
                                                                  }
                                                                  else
                                                                  {
                                                            #line 6371 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3872 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                                    print(isGo() && useGlr ? L"E" : L"e");
                                                            #line 6377 "PrintCLike.cpp"
  append(L"xecute(reduce)");
                                                            #line 3874 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                  }
                                                                  print(rightBrace());
                                                                  decreaseIndent();
                                                                }
                                                                else
                                                                {
                                                            #line 6387 "PrintCLike.cpp"
  append(L"\n");
  append(L"  nonterminalId = reduce");
                                                            #line 3882 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                                if (trace)
                                                                {
                                                            #line 6395 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if ");
                                                            #line 3887 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                            #line 6400 "PrintCLike.cpp"
  append(L"shift >= 0");
                                                            #line 3888 "PrintCLike.cpp.template"
                                                                  print(ifRightParen());
                                                                  printIndented(1, leftBrace());
                                                                  if (isCpp())
                                                                  {
                                                            #line 6407 "PrintCLike.cpp"
  append(L"\n");
  append(L"    fprintf(stderr, ");
                                                            #line 3893 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 6414 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 3897 "PrintCLike.cpp.template"
                                                                    print(writeTrace());
                                                                  }
                                                            #line 6420 "PrintCLike.cpp"
  append(L"\" \"");
                                                            #line 3899 "PrintCLike.cpp.template"
                                                                  print(endWriteTrace());
                                                                  print(semicolon());
                                                                  increaseIndent();
                                                                  print(rightBrace());
                                                                  decreaseIndent();
                                                                  if (isCpp())
                                                                  {
                                                            #line 6430 "PrintCLike.cpp"
  append(L"\n");
  append(L"  fprintf(stderr, \"reduce\\\" nonterminal=\\\"%s\\\" count=\\\"%d\\\"/>\\n\", ");
                                                            #line 3907 "PrintCLike.cpp.template"
                                                                    if (stringIntroducer()[0])
                                                                    {
                                                            #line 6436 "PrintCLike.cpp"
  append(L"Utf8Encoder::encode(");
                                                            #line 3909 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 6440 "PrintCLike.cpp"
  append(L"xmlEscape(");
                                                            #line 3910 "PrintCLike.cpp.template"
                                                                    print(isGo() ? L"nonterminal" : L"NONTERMINAL");
                                                            #line 6444 "PrintCLike.cpp"
  append(L"[nonterminalId], 0).c_str()");
                                                            #line 3912 "PrintCLike.cpp.template"
                                                                    if (stringIntroducer()[0])
                                                                    {
                                                            #line 6449 "PrintCLike.cpp"
  append(L").c_str()");
                                                            #line 3914 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 6453 "PrintCLike.cpp"
  append(L", symbols);");
                                                            #line 3915 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 6459 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3919 "PrintCLike.cpp.template"
                                                                    print(writeTrace());
                                                            #line 6464 "PrintCLike.cpp"
  append(L"\"reduce\\\" nonterminal=\\\"\" + ");
                                                            #line 3921 "PrintCLike.cpp.template"
                                                                    print(staticPrefix());
                                                            #line 6468 "PrintCLike.cpp"
  append(L"xmlEscape(");
                                                            #line 3922 "PrintCLike.cpp.template"
                                                                    print(staticPrefix());
                                                                    print(isGo() ? L"nonterminal" : L"NONTERMINAL");
                                                                    print(leftbracket());
                                                            #line 6474 "PrintCLike.cpp"
  append(L"nonterminalId");
                                                            #line 3925 "PrintCLike.cpp.template"
                                                                    print(rightbracket());
                                                            #line 6478 "PrintCLike.cpp"
  append(L") + \"\\\" count=\\\"\" + ");
                                                            #line 3927 "PrintCLike.cpp.template"
                                                                    if (isPython())
                                                                    {
                                                            #line 6483 "PrintCLike.cpp"
  append(L"str(");
                                                            #line 3930 "PrintCLike.cpp.template"
                                                                    }
                                                                    else if (isGo())
                                                                    {
                                                            #line 6489 "PrintCLike.cpp"
  append(L"strconv.Itoa(");
                                                            #line 3934 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 6493 "PrintCLike.cpp"
  append(L"symbols");
                                                            #line 3936 "PrintCLike.cpp.template"
                                                                    if (isGo() || isPython())
                                                                    {
                                                            #line 6498 "PrintCLike.cpp"
  append(L")");
                                                            #line 3939 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 6502 "PrintCLike.cpp"
  append(L" + \"\\\"/>");
                                                            #line 3941 "PrintCLike.cpp.template"
                                                                    if (! isHaxe())
                                                                    {
                                                            #line 6507 "PrintCLike.cpp"
  append(L"\\n\"");
                                                            #line 3944 "PrintCLike.cpp.template"
                                                                      print(endWriteTrace());
                                                                      print(semicolon());
                                                                    }
                                                                    else
                                                                    {
                                                            #line 6515 "PrintCLike.cpp"
  append(L"\";\n");
  append(L"  trace(traceLine);");
                                                            #line 3950 "PrintCLike.cpp.template"
                                                                    }
                                                                  }
                                                                }
                                                                if (tree)
                                                                {
                                                            #line 6524 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if ");
                                                            #line 3956 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                            #line 6529 "PrintCLike.cpp"
  append(L"symbols > 0");
                                                            #line 3957 "PrintCLike.cpp.template"
                                                                  print(ifRightParen());
                                                                  printIndented(1, leftBrace());
                                                                  if (useGlr)
                                                                  {
                                                                    if (isCpp())
                                                                    {
                                                            #line 6538 "PrintCLike.cpp"
  append(L"\n");
  append(L"    stack = stack->pop(symbols - 1);");
                                                            #line 3964 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                                      increaseIndent(2);
                                                                      if (isHaxe())
                                                                      {
                                                            #line 6548 "PrintCLike.cpp"
  append(L"\n");
  append(L"for (i in 1...symbols)");
                                                            #line 3971 "PrintCLike.cpp.template"
                                                                      }
                                                                      else if (isScala())
                                                                      {
                                                            #line 6555 "PrintCLike.cpp"
  append(L"\n");
  append(L"var i = 0\n");
  append(L"for (i <- 2 to symbols)");
                                                            #line 3976 "PrintCLike.cpp.template"
                                                                      }
                                                                      else if (isPython())
                                                                      {
                                                            #line 6563 "PrintCLike.cpp"
  append(L"\n");
  append(L"for _ in range(symbols - 1):");
                                                            #line 3980 "PrintCLike.cpp.template"
                                                                      }
                                                                      else
                                                                      {
                                                            #line 6570 "PrintCLike.cpp"
  append(L"\n");
  append(L"for ");
                                                            #line 3984 "PrintCLike.cpp.template"
                                                                        print(ifLeftParen());
                                                                        print(intVar());
                                                            #line 6576 "PrintCLike.cpp"
  append(L"i");
                                                            #line 3986 "PrintCLike.cpp.template"
                                                                        print(assign());
                                                            #line 6580 "PrintCLike.cpp"
  append(L"1; i < symbols; i++");
                                                            #line 3987 "PrintCLike.cpp.template"
                                                                        print(ifRightParen());
                                                                      }
                                                                      print(leftBrace());
                                                            #line 6586 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 3991 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 6591 "PrintCLike.cpp"
  append(L"stack = ");
                                                            #line 3992 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 6595 "PrintCLike.cpp"
  append(L"stack.link");
                                                            #line 3993 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                                      print(rightBrace());
                                                                      decreaseIndent(2);
                                                                    }
                                                            #line 6602 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 3998 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 6607 "PrintCLike.cpp"
  append(L"state = ");
                                                            #line 3999 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 6611 "PrintCLike.cpp"
  append(L"stack");
                                                            #line 4000 "PrintCLike.cpp.template"
                                                                    print(arrow());
                                                            #line 6615 "PrintCLike.cpp"
  append(L"state");
                                                            #line 4001 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 6619 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4003 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 6624 "PrintCLike.cpp"
  append(L"bs = ");
                                                            #line 4004 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 6628 "PrintCLike.cpp"
  append(L"stack");
                                                            #line 4005 "PrintCLike.cpp.template"
                                                                    print(arrow());
                                                            #line 6632 "PrintCLike.cpp"
  append(L"pos");
                                                            #line 4006 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                    if (isCpp())
                                                                    {
                                                            #line 6638 "PrintCLike.cpp"
  append(L"\n");
  append(L"    stack = stack->pop(1);");
                                                            #line 4010 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 6645 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4014 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 6650 "PrintCLike.cpp"
  append(L"stack = ");
                                                            #line 4015 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 6654 "PrintCLike.cpp"
  append(L"stack.link");
                                                            #line 4016 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                                    }
                                                                  }
                                                                  else
                                                                  {
                                                            #line 6662 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4022 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 6667 "PrintCLike.cpp"
  append(L"top -= symbols * 3");
                                                            #line 4023 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 6671 "PrintCLike.cpp"
  append(L"\n");
  append(L"    state = ");
                                                            #line 4025 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 6676 "PrintCLike.cpp"
  append(L"iStack");
                                                            #line 4026 "PrintCLike.cpp.template"
                                                                    print(leftbracket());
                                                                    print(thiz());
                                                            #line 6681 "PrintCLike.cpp"
  append(L"top + 2");
                                                            #line 4028 "PrintCLike.cpp.template"
                                                                    print(rightbracket());
                                                                    print(semicolon());
                                                            #line 6686 "PrintCLike.cpp"
  append(L"\n");
  append(L"    bs = ");
                                                            #line 4031 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 6691 "PrintCLike.cpp"
  append(L"iStack");
                                                            #line 4032 "PrintCLike.cpp.template"
                                                                    print(leftbracket());
                                                                    print(thiz());
                                                            #line 6696 "PrintCLike.cpp"
  append(L"top + 1");
                                                            #line 4034 "PrintCLike.cpp.template"
                                                                    print(rightbracket());
                                                                    print(semicolon());
                                                                  }
                                                            #line 6702 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4038 "PrintCLike.cpp.template"
                                                                  printIndented(1, elseWithBraces());
                                                            #line 6707 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4040 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 6712 "PrintCLike.cpp"
  append(L"bs = ");
                                                            #line 4041 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 6716 "PrintCLike.cpp"
  append(L"b1");
                                                            #line 4042 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                            #line 6720 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4044 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 6725 "PrintCLike.cpp"
  append(L"es = ");
                                                            #line 4045 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 6729 "PrintCLike.cpp"
  append(L"b1");
                                                            #line 4046 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                  increaseIndent();
                                                                  print(rightBrace());
                                                                  decreaseIndent();
                                                            #line 6736 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if ");
                                                            #line 4051 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                            #line 6741 "PrintCLike.cpp"
  append(L"nonterminalId == ");
                                                            #line 4052 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 6745 "PrintCLike.cpp"
  append(L"target ");
                                                            #line 4053 "PrintCLike.cpp.template"
                                                                  if (isPython())
                                                                  {
                                                            #line 6750 "PrintCLike.cpp"
  append(L"and");
                                                            #line 4055 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 6756 "PrintCLike.cpp"
  append(L"&&");
                                                            #line 4058 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 6760 "PrintCLike.cpp"
  append(L" ");
                                                            #line 4059 "PrintCLike.cpp.template"
                                                                  if (useGlr)
                                                                  {
                                                                    print(thiz());
                                                            #line 6766 "PrintCLike.cpp"
  append(L"stack");
                                                            #line 4062 "PrintCLike.cpp.template"
                                                                    print(arrow());
                                                            #line 6770 "PrintCLike.cpp"
  append(L"link == ");
                                                            #line 4063 "PrintCLike.cpp.template"
                                                                    print(nullPtr());
                                                                  }
                                                                  else
                                                                  {
                                                            #line 6777 "PrintCLike.cpp"
  append(L"t == ");
                                                            #line 4067 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 6781 "PrintCLike.cpp"
  append(L"top");
                                                            #line 4068 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(ifRightParen());
                                                                  printIndented(1, leftBrace());
                                                            #line 6787 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4072 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 6792 "PrintCLike.cpp"
  append(L"bs = ");
                                                            #line 4073 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 6796 "PrintCLike.cpp"
  append(L"bw");
                                                            #line 4074 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                            #line 6800 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4076 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 6805 "PrintCLike.cpp"
  append(L"es = ");
                                                            #line 4077 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 6809 "PrintCLike.cpp"
  append(L"b1");
                                                            #line 4078 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                            #line 6813 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4080 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 6818 "PrintCLike.cpp"
  append(L"bw = ");
                                                            #line 4081 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 6822 "PrintCLike.cpp"
  append(L"b1");
                                                            #line 4082 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                  increaseIndent();
                                                                  print(rightBrace());
                                                                  decreaseIndent();
                                                            #line 6829 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if ");
                                                            #line 4087 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                                  if (useGlr) print(thiz());
                                                            #line 6835 "PrintCLike.cpp"
  append(L"eventHandler != ");
                                                            #line 4089 "PrintCLike.cpp.template"
                                                                  print(nullPtr());
                                                                  print(ifRightParen());
                                                                  printIndented(1, leftBrace());
                                                                  if (useGlr)
                                                                  {
                                                            #line 6843 "PrintCLike.cpp"
  append(L"\n");
  append(L"    if ");
                                                            #line 4095 "PrintCLike.cpp.template"
                                                                    print(ifLeftParen());
                                                                    print(thiz());
                                                                    if (isGo())
                                                                    {
                                                            #line 6851 "PrintCLike.cpp"
  append(L"IsUnambiguous");
                                                            #line 4099 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 6857 "PrintCLike.cpp"
  append(L"isUnambiguous");
                                                            #line 4102 "PrintCLike.cpp.template"
                                                                    }
                                                                    if (! isScala()) print(L"()");
                                                                    print(ifRightParen());
                                                                    printIndented(2, leftBrace());
                                                                    increaseIndent();
                                                                  }
                                                            #line 6866 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4109 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 6871 "PrintCLike.cpp"
  append(L"eventHandler");
                                                            #line 4110 "PrintCLike.cpp.template"
                                                                  print(arrow());
                                                                  if (isGo())
                                                                  {
                                                            #line 6877 "PrintCLike.cpp"
  append(L"N");
                                                            #line 4113 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 6883 "PrintCLike.cpp"
  append(L"n");
                                                            #line 4116 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 6887 "PrintCLike.cpp"
  append(L"onterminal(");
                                                            #line 4117 "PrintCLike.cpp.template"
                                                                  print(staticPrefix());
                                                                  print(isGo() ? L"nonterminal" : L"NONTERMINAL");
                                                                  print(leftbracket());
                                                            #line 6893 "PrintCLike.cpp"
  append(L"nonterminalId");
                                                            #line 4120 "PrintCLike.cpp.template"
                                                                  print(rightbracket());
                                                            #line 6897 "PrintCLike.cpp"
  append(L", ");
                                                            #line 4121 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 6901 "PrintCLike.cpp"
  append(L"bs, ");
                                                            #line 4122 "PrintCLike.cpp.template"
                                                                  if (useGlr) print(thiz());
                                                            #line 6905 "PrintCLike.cpp"
  append(L"es, symbols)");
                                                            #line 4124 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                  if (useGlr)
                                                                  {
                                                                    decreaseIndent();
                                                            #line 6912 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4129 "PrintCLike.cpp.template"
                                                                    printIndented(2, elseWithBraces());
                                                            #line 6917 "PrintCLike.cpp"
  append(L"\n");
  append(L"      ");
                                                            #line 4131 "PrintCLike.cpp.template"
                                                                    if (useGlr) print(thiz());
                                                            #line 6922 "PrintCLike.cpp"
  append(L"deferredEvent = ");
                                                            #line 4132 "PrintCLike.cpp.template"
                                                                    if (isGo())
                                                                    {
                                                            #line 6927 "PrintCLike.cpp"
  append(L"&NonterminalEvent{&AbstractDeferredEvent{this.deferredEvent, nonterminal[nonterminalId], this.bs, this.es}, symbols}");
                                                            #line 4135 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                                      if (! isPython())
                                                                      {
                                                            #line 6935 "PrintCLike.cpp"
  append(L"new ");
                                                            #line 4140 "PrintCLike.cpp.template"
                                                                      }
                                                                      if (! isHaxe() && ! isTypescript()) print(staticPrefix());
                                                                      if (isJavascript() || isTypescript())
                                                                      {
                                                            #line 6942 "PrintCLike.cpp"
  append(L"DeferredEvent");
                                                            #line 4144 "PrintCLike.cpp.template"
                                                                      }
                                                                      else
                                                                      {
                                                            #line 6948 "PrintCLike.cpp"
  append(L"NonterminalEvent");
                                                            #line 4147 "PrintCLike.cpp.template"
                                                                      }
                                                            #line 6952 "PrintCLike.cpp"
  append(L"(");
                                                            #line 4148 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 6956 "PrintCLike.cpp"
  append(L"deferredEvent, ");
                                                            #line 4149 "PrintCLike.cpp.template"
                                                                      print(staticPrefix());
                                                            #line 6960 "PrintCLike.cpp"
  append(L"NONTERMINAL");
                                                            #line 4150 "PrintCLike.cpp.template"
                                                                      print(leftbracket());
                                                            #line 6964 "PrintCLike.cpp"
  append(L"nonterminalId");
                                                            #line 4151 "PrintCLike.cpp.template"
                                                                      print(rightbracket());
                                                            #line 6968 "PrintCLike.cpp"
  append(L", ");
                                                            #line 4152 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 6972 "PrintCLike.cpp"
  append(L"bs, ");
                                                            #line 4154 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 6976 "PrintCLike.cpp"
  append(L"es, symbols)");
                                                            #line 4156 "PrintCLike.cpp.template"
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
                                                            #line 6991 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if ");
                                                            #line 4169 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                            #line 6996 "PrintCLike.cpp"
  append(L"symbols > 0");
                                                            #line 4170 "PrintCLike.cpp.template"
                                                                  print(ifRightParen());
                                                                  printIndented(1, leftBrace());
                                                                  if (useGlr)
                                                                  {
                                                                    if (isCpp())
                                                                    {
                                                            #line 7005 "PrintCLike.cpp"
  append(L"\n");
  append(L"    stack = stack->pop(symbols - 1);");
                                                            #line 4177 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                                      increaseIndent(2);
                                                                      if (isHaxe())
                                                                      {
                                                            #line 7015 "PrintCLike.cpp"
  append(L"\n");
  append(L"for (i in 1...symbols)");
                                                            #line 4184 "PrintCLike.cpp.template"
                                                                      }
                                                                      else if (isScala())
                                                                      {
                                                            #line 7022 "PrintCLike.cpp"
  append(L"\n");
  append(L"var i = 0\n");
  append(L"for (i <- 2 to symbols)");
                                                            #line 4189 "PrintCLike.cpp.template"
                                                                      }
                                                                      else if (isPython())
                                                                      {
                                                            #line 7030 "PrintCLike.cpp"
  append(L"\n");
  append(L"for _ in range(symbols - 1):");
                                                            #line 4193 "PrintCLike.cpp.template"
                                                                      }
                                                                      else
                                                                      {
                                                            #line 7037 "PrintCLike.cpp"
  append(L"\n");
  append(L"for ");
                                                            #line 4197 "PrintCLike.cpp.template"
                                                                        print(ifLeftParen());
                                                                        print(intVar());
                                                            #line 7043 "PrintCLike.cpp"
  append(L"i");
                                                            #line 4199 "PrintCLike.cpp.template"
                                                                        print(assign());
                                                            #line 7047 "PrintCLike.cpp"
  append(L"1; i < symbols; i++");
                                                            #line 4200 "PrintCLike.cpp.template"
                                                                        print(ifRightParen());
                                                                      }
                                                                      print(leftBrace());
                                                            #line 7053 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4204 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 7058 "PrintCLike.cpp"
  append(L"stack = ");
                                                            #line 4205 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 7062 "PrintCLike.cpp"
  append(L"stack.link");
                                                            #line 4206 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                                      print(rightBrace());
                                                                      decreaseIndent(2);
                                                                    }
                                                            #line 7069 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4212 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7074 "PrintCLike.cpp"
  append(L"state = ");
                                                            #line 4213 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7078 "PrintCLike.cpp"
  append(L"stack");
                                                            #line 4214 "PrintCLike.cpp.template"
                                                                    print(arrow());
                                                            #line 7082 "PrintCLike.cpp"
  append(L"state");
                                                            #line 4215 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                    if (tree)
                                                                    {
                                                            #line 7088 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4219 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 7093 "PrintCLike.cpp"
  append(L"bs = ");
                                                            #line 4220 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 7097 "PrintCLike.cpp"
  append(L"stack");
                                                            #line 4221 "PrintCLike.cpp.template"
                                                                      print(arrow());
                                                            #line 7101 "PrintCLike.cpp"
  append(L"pos");
                                                            #line 4222 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                                    }
                                                                    if (isCpp())
                                                                    {
                                                            #line 7108 "PrintCLike.cpp"
  append(L"\n");
  append(L"    stack = stack->pop(1);");
                                                            #line 4227 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 7115 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4231 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 7120 "PrintCLike.cpp"
  append(L"stack = ");
                                                            #line 4232 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 7124 "PrintCLike.cpp"
  append(L"stack.link");
                                                            #line 4233 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                                    }
                                                                  }
                                                                  else
                                                                  {
                                                            #line 7132 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4239 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7137 "PrintCLike.cpp"
  append(L"top -= symbols << 1;\n");
  append(L"    state = ");
                                                            #line 4241 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7142 "PrintCLike.cpp"
  append(L"iStack");
                                                            #line 4242 "PrintCLike.cpp.template"
                                                                    print(leftbracket());
                                                                    print(thiz());
                                                            #line 7147 "PrintCLike.cpp"
  append(L"top + 1");
                                                            #line 4244 "PrintCLike.cpp.template"
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
                                                            #line 7161 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4256 "PrintCLike.cpp.template"
                                                                    printIndented(1, elseWithBraces());
                                                            #line 7166 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4258 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7171 "PrintCLike.cpp"
  append(L"bs = ");
                                                            #line 4259 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7175 "PrintCLike.cpp"
  append(L"b1");
                                                            #line 4260 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                    increaseIndent();
                                                                    print(rightBrace());
                                                                    decreaseIndent();
                                                                    if (tree)
                                                                    {
                                                            #line 7184 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if ");
                                                            #line 4267 "PrintCLike.cpp.template"
                                                                      print(ifLeftParen());
                                                            #line 7189 "PrintCLike.cpp"
  append(L"nonterminalId == ");
                                                            #line 4268 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 7193 "PrintCLike.cpp"
  append(L"target ");
                                                            #line 4269 "PrintCLike.cpp.template"
                                                                      if (isPython())
                                                                      {
                                                            #line 7198 "PrintCLike.cpp"
  append(L"and");
                                                            #line 4271 "PrintCLike.cpp.template"
                                                                      }
                                                                      else
                                                                      {
                                                            #line 7204 "PrintCLike.cpp"
  append(L"&&");
                                                            #line 4274 "PrintCLike.cpp.template"
                                                                      }
                                                            #line 7208 "PrintCLike.cpp"
  append(L" ");
                                                            #line 4275 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 7212 "PrintCLike.cpp"
  append(L"stack");
                                                            #line 4276 "PrintCLike.cpp.template"
                                                                      print(arrow());
                                                            #line 7216 "PrintCLike.cpp"
  append(L"link == ");
                                                            #line 4277 "PrintCLike.cpp.template"
                                                                      print(nullPtr());
                                                                      print(ifRightParen());
                                                                      printIndented(1, leftBrace());
                                                            #line 7222 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4281 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 7227 "PrintCLike.cpp"
  append(L"bs = ");
                                                            #line 4282 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 7231 "PrintCLike.cpp"
  append(L"bw");
                                                            #line 4283 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                            #line 7235 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 4285 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 7240 "PrintCLike.cpp"
  append(L"bw = ");
                                                            #line 4286 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 7244 "PrintCLike.cpp"
  append(L"b1");
                                                            #line 4287 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                                      increaseIndent();
                                                                      print(rightBrace());
                                                                      decreaseIndent();
                                                                    }
                                                                  }
                                                                }
                                                            #line 7254 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4295 "PrintCLike.cpp.template"
                                                                if (useGlr) print(thiz());
                                                            #line 7259 "PrintCLike.cpp"
  append(L"action = ");
                                                            #line 4296 "PrintCLike.cpp.template"
                                                                print(staticPrefix());
                                                                print(isGo() ? L"reduceAction" : L"goTo");
                                                            #line 7264 "PrintCLike.cpp"
  append(L"(nonterminalId, ");
                                                            #line 4298 "PrintCLike.cpp.template"
                                                                if (useGlr) print(thiz());
                                                            #line 7268 "PrintCLike.cpp"
  append(L"state)");
                                                            #line 4299 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                print(rightBrace());
                                                                decreaseIndent();
                                                                print(rightBrace());
                                                                decreaseIndent();
                                                                if (useGlr)
                                                                {
                                                                  if (isScala())
                                                                  {
                                                            #line 7280 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ERROR");
                                                            #line 4309 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isCpp())
                                                                  {
                                                            #line 7287 "PrintCLike.cpp"
  append(L"\n");
  append(L"  return PARSING;");
                                                            #line 4313 "PrintCLike.cpp.template"
                                                                  }
                                                                }
                                                                print(rightBrace());
                                                                if (isJavascript() && useGlr)
                                                                {
                                                            #line 7296 "PrintCLike.cpp"
  append(L";");
                                                            #line 4318 "PrintCLike.cpp.template"
                                                                }
                                                            #line 7300 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4320 "PrintCLike.cpp.template"
                                                                if ((tree || hasCustomCode) && useGlr)
                                                                {
                                                                  openMethod(boolType(), L"", L"isUnambiguous", L"", false, L"ParsingThread");
                                                                  print(leftBrace());
                                                            #line 7307 "PrintCLike.cpp"
  append(L"\n");
  append(L"  return ");
                                                            #line 4325 "PrintCLike.cpp.template"
                                                                  if (isPython())
                                                                  {
                                                            #line 7313 "PrintCLike.cpp"
  append(L"len(self.threads) == 0");
                                                            #line 4327 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                                    print(thiz());
                                                            #line 7320 "PrintCLike.cpp"
  append(L"threads");
                                                            #line 4331 "PrintCLike.cpp.template"
                                                                    print(arrow());
                                                                    if (isCpp())
                                                                    {
                                                            #line 7326 "PrintCLike.cpp"
  append(L"empty();");
                                                            #line 4334 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 7332 "PrintCLike.cpp"
  append(L"isEmpty");
                                                            #line 4337 "PrintCLike.cpp.template"
                                                                      if (! isScala()) print(L"()");
                                                                      print(semicolon());
                                                                    }
                                                                  }
                                                                  print(rightBrace());
                                                            #line 7340 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4343 "PrintCLike.cpp.template"
                                                                }
                                                                if (hasCustomCode)
                                                                {
                                                                  if (useGlr)
                                                                  {
                                                                    if (isJavascript())
                                                                    {
                                                            #line 7350 "PrintCLike.cpp"
  append(L"\n");
  append(L"this.executeDeferredCode = function()\n");
                                                            #line 4352 "PrintCLike.cpp.template"
                                                                    }
                                                                    else if (isTypescript())
                                                                    {
                                                            #line 7357 "PrintCLike.cpp"
  append(L"\n");
  append(L"executeDeferredCode()\n");
                                                            #line 4357 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                                      openMethod(voidType(), L"", L"executeDeferredCode", L"", false, L"ParsingThread");
                                                                    }
                                                                    print(leftBrace());
                                                                    increaseIndent();
                                                            #line 7368 "PrintCLike.cpp"
  append(L"\n");
  append(L"if ");
                                                            #line 4365 "PrintCLike.cpp.template"
                                                                    print(ifLeftParen());
                                                                    print(thiz());
                                                            #line 7374 "PrintCLike.cpp"
  append(L"deferredCode != ");
                                                            #line 4367 "PrintCLike.cpp.template"
                                                                    print(nullPtr());
                                                                    print(ifRightParen());
                                                                    print(leftBrace());
                                                                    increaseIndent();
                                                            #line 7381 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4372 "PrintCLike.cpp.template"
                                                                    if (isJavascript() || isHaxe() || isScala() || isTypescript())
                                                                    {
                                                            #line 7386 "PrintCLike.cpp"
  append(L"var ");
                                                            #line 4374 "PrintCLike.cpp.template"
                                                                    }
                                                                    else if (! isGo() && ! isPython())
                                                                    {
                                                            #line 7392 "PrintCLike.cpp"
  append(L"DeferredCode ");
                                                            #line 4377 "PrintCLike.cpp.template"
                                                                    }
                                                                    if (isCpp()) print(L"*");
                                                            #line 7397 "PrintCLike.cpp"
  append(L"predecessor");
                                                            #line 4379 "PrintCLike.cpp.template"
                                                                    print(assign());
                                                                    print(thiz());
                                                            #line 7402 "PrintCLike.cpp"
  append(L"deferredCode");
                                                            #line 4381 "PrintCLike.cpp.template"
                                                                    print(arrow());
                                                            #line 7406 "PrintCLike.cpp"
  append(L"link");
                                                            #line 4382 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 7410 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4384 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7414 "PrintCLike.cpp"
  append(L"deferredCode");
                                                            #line 4385 "PrintCLike.cpp.template"
                                                                    print(arrow());
                                                            #line 7418 "PrintCLike.cpp"
  append(L"link = ");
                                                            #line 4386 "PrintCLike.cpp.template"
                                                                    print(nullPtr());
                                                                    print(semicolon());
                                                                    if (isGo())
                                                                    {
                                                            #line 7425 "PrintCLike.cpp"
  append(L"\n");
  append(L"for ");
                                                            #line 4391 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 7432 "PrintCLike.cpp"
  append(L"\n");
  append(L"while ");
                                                            #line 4395 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(ifLeftParen());
                                                            #line 7438 "PrintCLike.cpp"
  append(L"predecessor != ");
                                                            #line 4397 "PrintCLike.cpp.template"
                                                                    print(nullPtr());
                                                                    print(ifRightParen());
                                                                    print(leftBrace());
                                                            #line 7444 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4401 "PrintCLike.cpp.template"
                                                                    if (isJavascript() || isHaxe() || isScala() || isTypescript())
                                                                    {
                                                            #line 7450 "PrintCLike.cpp"
  append(L"var ");
                                                            #line 4403 "PrintCLike.cpp.template"
                                                                    }
                                                                    else if (! isGo() && ! isPython())
                                                                    {
                                                            #line 7456 "PrintCLike.cpp"
  append(L"DeferredCode ");
                                                            #line 4406 "PrintCLike.cpp.template"
                                                                    }
                                                                    if (isCpp()) print(L"*");
                                                            #line 7461 "PrintCLike.cpp"
  append(L"nextCode");
                                                            #line 4408 "PrintCLike.cpp.template"
                                                                    print(assign());
                                                            #line 7465 "PrintCLike.cpp"
  append(L"predecessor");
                                                            #line 4409 "PrintCLike.cpp.template"
                                                                    print(arrow());
                                                            #line 7469 "PrintCLike.cpp"
  append(L"link");
                                                            #line 4410 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 7473 "PrintCLike.cpp"
  append(L"\n");
  append(L"  predecessor");
                                                            #line 4412 "PrintCLike.cpp.template"
                                                                    print(arrow());
                                                            #line 7478 "PrintCLike.cpp"
  append(L"link = ");
                                                            #line 4413 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7482 "PrintCLike.cpp"
  append(L"deferredCode");
                                                            #line 4414 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 7486 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4416 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7491 "PrintCLike.cpp"
  append(L"deferredCode = predecessor");
                                                            #line 4417 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 7495 "PrintCLike.cpp"
  append(L"\n");
  append(L"  predecessor = nextCode");
                                                            #line 4419 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                    print(rightBrace());
                                                            #line 7501 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4422 "PrintCLike.cpp.template"
                                                                    print(intVar());
                                                            #line 7505 "PrintCLike.cpp"
  append(L"b0t");
                                                            #line 4423 "PrintCLike.cpp.template"
                                                                    print(assign());
                                                                    print(thiz());
                                                            #line 7510 "PrintCLike.cpp"
  append(L"b0");
                                                            #line 4425 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 7514 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4427 "PrintCLike.cpp.template"
                                                                    print(intVar());
                                                            #line 7518 "PrintCLike.cpp"
  append(L"e0t");
                                                            #line 4428 "PrintCLike.cpp.template"
                                                                    print(assign());
                                                                    print(thiz());
                                                            #line 7523 "PrintCLike.cpp"
  append(L"e0");
                                                            #line 4430 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                    if (isGo())
                                                                    {
                                                            #line 7529 "PrintCLike.cpp"
  append(L"\n");
  append(L"for ");
                                                            #line 4434 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 7536 "PrintCLike.cpp"
  append(L"\n");
  append(L"while ");
                                                            #line 4438 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(ifLeftParen());
                                                                    print(thiz());
                                                            #line 7543 "PrintCLike.cpp"
  append(L"deferredCode != ");
                                                            #line 4441 "PrintCLike.cpp.template"
                                                                    print(nullPtr());
                                                                    print(ifRightParen());
                                                                    print(leftBrace());
                                                            #line 7549 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4445 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7554 "PrintCLike.cpp"
  append(L"b0 = ");
                                                            #line 4446 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7558 "PrintCLike.cpp"
  append(L"deferredCode");
                                                            #line 4447 "PrintCLike.cpp.template"
                                                                    print(arrow());
                                                            #line 7562 "PrintCLike.cpp"
  append(L"b0");
                                                            #line 4448 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 7566 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4450 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7571 "PrintCLike.cpp"
  append(L"e0 = ");
                                                            #line 4451 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7575 "PrintCLike.cpp"
  append(L"deferredCode");
                                                            #line 4452 "PrintCLike.cpp.template"
                                                                    print(arrow());
                                                            #line 7579 "PrintCLike.cpp"
  append(L"e0");
                                                            #line 4453 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 7583 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4455 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                                    print(isGo() ? L"E" : L"e");
                                                            #line 7589 "PrintCLike.cpp"
  append(L"xecute(");
                                                            #line 4457 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7593 "PrintCLike.cpp"
  append(L"deferredCode");
                                                            #line 4458 "PrintCLike.cpp.template"
                                                                    print(arrow());
                                                            #line 7597 "PrintCLike.cpp"
  append(L"codeId)");
                                                            #line 4459 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                    if (isCpp())
                                                                    {
                                                            #line 7603 "PrintCLike.cpp"
  append(L"\n");
  append(L"  DeferredCode *next = deferredCode->link;\n");
  append(L"  delete deferredCode;\n");
  append(L"  deferredCode = next;");
                                                            #line 4465 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 7612 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4469 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 7617 "PrintCLike.cpp"
  append(L"deferredCode = ");
                                                            #line 4470 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 7621 "PrintCLike.cpp"
  append(L"deferredCode");
                                                            #line 4471 "PrintCLike.cpp.template"
                                                                      print(arrow());
                                                            #line 7625 "PrintCLike.cpp"
  append(L"link");
                                                            #line 4472 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                                    }
                                                                    print(rightBrace());
                                                            #line 7631 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4476 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7635 "PrintCLike.cpp"
  append(L"b0 = b0t");
                                                            #line 4477 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 7639 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4479 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7643 "PrintCLike.cpp"
  append(L"e0 = e0t");
                                                            #line 4480 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                    decreaseIndent();
                                                                    print(rightBrace());
                                                                    decreaseIndent();
                                                                    print(rightBrace());
                                                            #line 7651 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4486 "PrintCLike.cpp.template"
                                                                  }
                                                                  openMethod(voidType(), L"", L"execute", L"int reduce", false, useGlr ? L"ParsingThread" : className.c_str());
                                                                  print(leftBrace());
                                                                  increaseIndent();
                                                                  if (! isPython())
                                                                  {
                                                            #line 7660 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4493 "PrintCLike.cpp.template"
                                                                    if (! isScala())
                                                                    {
                                                            #line 7665 "PrintCLike.cpp"
  append(L"switch ");
                                                            #line 4495 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(ifLeftParen());
                                                            #line 7670 "PrintCLike.cpp"
  append(L"reduce");
                                                            #line 4497 "PrintCLike.cpp.template"
                                                                    print(ifRightParen());
                                                                    if (isScala())
                                                                    {
                                                            #line 7676 "PrintCLike.cpp"
  append(L" match");
                                                            #line 4500 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(leftBrace());
                                                                  }
                                                                  int lastContentId = grammar->distinctCodeAnnotations.size() - 1;
                                                                  for (int contentId = 0; contentId <= lastContentId; ++contentId)
                                                                  {
                                                                    ProcessingInstruction *p = grammar->distinctCodeAnnotations[contentId];
                                                                    if (! isPython())
                                                                    {
                                                            #line 7688 "PrintCLike.cpp"
  append(L"\n");
  append(L"case ");
                                                            #line 4510 "PrintCLike.cpp.template"
                                                                    }
                                                                    else if (contentId == 0)
                                                                    {
                                                            #line 7695 "PrintCLike.cpp"
  append(L"\n");
  append(L"if reduce == ");
                                                            #line 4514 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 7702 "PrintCLike.cpp"
  append(L"\n");
  append(L"elif reduce == ");
                                                            #line 4518 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(format.toString<wchar_t>(contentId));
                                                                    print(caseIntroducer());
                                                                    increaseIndent();
                                                                    print(leftBrace());
                                                                    visitProcessingInstruction(p);
                                                                    print(rightBrace());
                                                                    if (! isScala() && ! isHaxe() && ! isGo() && ! isPython())
                                                                    {
                                                            #line 7715 "PrintCLike.cpp"
  append(L"\n");
  append(L"break");
                                                            #line 4528 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                                    }
                                                                    decreaseIndent();
                                                                  }
                                                                  if (isScala())
                                                                  {
                                                            #line 7725 "PrintCLike.cpp"
  append(L"\n");
  append(L"case _");
                                                            #line 4535 "PrintCLike.cpp.template"
                                                                    print(caseIntroducer());
                                                                  }
                                                                  else if (! isPython())
                                                                  {
                                                            #line 7733 "PrintCLike.cpp"
  append(L"\n");
  append(L"default");
                                                            #line 4540 "PrintCLike.cpp.template"
                                                                    print(caseIntroducer());
                                                                  }
                                                                  if (! isScala() && ! isHaxe() && ! isGo() && ! isPython())
                                                                  {
                                                            #line 7741 "PrintCLike.cpp"
  append(L"\n");
  append(L"  break");
                                                            #line 4545 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                  }
                                                                  print(rightBrace());
                                                                  decreaseIndent();
                                                                  print(rightBrace());
                                                            #line 7750 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4551 "PrintCLike.cpp.template"
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
                                                            #line 7776 "PrintCLike.cpp"
  append(L"\n");
  append(L"if ");
                                                            #line 4575 "PrintCLike.cpp.template"
                                                                print(ifLeftParen());
                                                                print(thiz());
                                                            #line 7782 "PrintCLike.cpp"
  append(L"l1 == t");
                                                            #line 4577 "PrintCLike.cpp.template"
                                                                print(ifRightParen());
                                                                print(leftBrace());
                                                                increaseIndent();
                                                                if (tree && i == 0 && ! isLrParser)
                                                                {
                                                                  if (anyWhitespace && ! isLrParser)
                                                                  {
                                                            #line 7792 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4585 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7796 "PrintCLike.cpp"
  append(L"whitespace");
                                                            #line 4586 "PrintCLike.cpp.template"
                                                                    print(isScala() ? L"" : L"()");
                                                                    print(semicolon());
                                                                  }
                                                            #line 7802 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4591 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 7806 "PrintCLike.cpp"
  append(L"eventHandler");
                                                            #line 4592 "PrintCLike.cpp.template"
                                                                  print(arrow());
                                                                  if (isGo())
                                                                  {
                                                            #line 7812 "PrintCLike.cpp"
  append(L"T");
                                                            #line 4595 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 7818 "PrintCLike.cpp"
  append(L"t");
                                                            #line 4598 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 7822 "PrintCLike.cpp"
  append(L"erminal(");
                                                            #line 4599 "PrintCLike.cpp.template"
                                                                  if (isJava() || isCSharp())
                                                                  {
                                                                    print(staticPrefix());
                                                            #line 7828 "PrintCLike.cpp"
  append(L"TOKEN[");
                                                            #line 4602 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7832 "PrintCLike.cpp"
  append(L"l1]");
                                                            #line 4603 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isTypescript())
                                                                  {
                                                                    print(staticPrefix());
                                                            #line 7839 "PrintCLike.cpp"
  append(L"TOKEN[");
                                                            #line 4607 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7843 "PrintCLike.cpp"
  append(L"l1]");
                                                            #line 4608 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isJavascript() || isHaxe())
                                                                  {
                                                                    print(staticPrefix());
                                                            #line 7850 "PrintCLike.cpp"
  append(L"TOKEN[");
                                                            #line 4612 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7854 "PrintCLike.cpp"
  append(L"l1]");
                                                            #line 4613 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isScala())
                                                                  {
                                                                    print(staticPrefix());
                                                            #line 7861 "PrintCLike.cpp"
  append(L"TOKEN(l1)");
                                                            #line 4617 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isGo())
                                                                  {
                                                            #line 7867 "PrintCLike.cpp"
  append(L"token[this.l1]");
                                                            #line 4620 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                                    print(staticPrefix());
                                                            #line 7874 "PrintCLike.cpp"
  append(L"TOKEN[");
                                                            #line 4624 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 7878 "PrintCLike.cpp"
  append(L"l1]");
                                                            #line 4625 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 7882 "PrintCLike.cpp"
  append(L", ");
                                                            #line 4626 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 7886 "PrintCLike.cpp"
  append(L"b1, ");
                                                            #line 4627 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 7890 "PrintCLike.cpp"
  append(L"e1)");
                                                            #line 4628 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                            #line 7895 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4631 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 7899 "PrintCLike.cpp"
  append(L"b0 = ");
                                                            #line 4632 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 7903 "PrintCLike.cpp"
  append(L"b1; ");
                                                            #line 4633 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 7907 "PrintCLike.cpp"
  append(L"e0 = ");
                                                            #line 4634 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 7911 "PrintCLike.cpp"
  append(L"e1;");
                                                            #line 4635 "PrintCLike.cpp.template"
                                                                for (size_t k = 1; k < grammar->k; ++k)
                                                                {
                                                            #line 7916 "PrintCLike.cpp"
  append(L" ");
                                                            #line 4637 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 7920 "PrintCLike.cpp"
  append(L"l");
                                                            #line 4638 "PrintCLike.cpp.template"
                                                                  print(format.toString<wchar_t>(k));
                                                            #line 7924 "PrintCLike.cpp"
  append(L" = ");
                                                            #line 4639 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 7928 "PrintCLike.cpp"
  append(L"l");
                                                            #line 4640 "PrintCLike.cpp.template"
                                                                  print(format.toString<wchar_t>(k + 1));
                                                                  print(isPython() ? L"\n" : L"; ");
                                                            #line 7933 "PrintCLike.cpp"
  append(L"if ");
                                                            #line 4642 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                                  print(thiz());
                                                            #line 7938 "PrintCLike.cpp"
  append(L"l");
                                                            #line 4644 "PrintCLike.cpp.template"
                                                                  print(format.toString<wchar_t>(k));
                                                            #line 7942 "PrintCLike.cpp"
  append(L" != 0");
                                                            #line 4645 "PrintCLike.cpp.template"
                                                                  print(ifRightParen());
                                                                  if (isPython())
                                                                  {
                                                                    increaseIndent();
                                                                  }
                                                                  else
                                                                  {
                                                            #line 7952 "PrintCLike.cpp"
  append(L" {");
                                                            #line 4652 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 7956 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4654 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 7960 "PrintCLike.cpp"
  append(L"b");
                                                            #line 4655 "PrintCLike.cpp.template"
                                                                  print(format.toString<wchar_t>(k));
                                                            #line 7964 "PrintCLike.cpp"
  append(L" = ");
                                                            #line 4656 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 7968 "PrintCLike.cpp"
  append(L"b");
                                                            #line 4657 "PrintCLike.cpp.template"
                                                                  print(format.toString<wchar_t>(k + 1));
                                                            #line 7972 "PrintCLike.cpp"
  append(L"; ");
                                                            #line 4658 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 7976 "PrintCLike.cpp"
  append(L"e");
                                                            #line 4659 "PrintCLike.cpp.template"
                                                                  print(format.toString<wchar_t>(k));
                                                            #line 7980 "PrintCLike.cpp"
  append(L" = ");
                                                            #line 4660 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 7984 "PrintCLike.cpp"
  append(L"e");
                                                            #line 4661 "PrintCLike.cpp.template"
                                                                  print(format.toString<wchar_t>(k + 1));
                                                            #line 7988 "PrintCLike.cpp"
  append(L";");
                                                            #line 4662 "PrintCLike.cpp.template"
                                                                }
                                                            #line 7992 "PrintCLike.cpp"
  append(L" ");
                                                            #line 4663 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 7996 "PrintCLike.cpp"
  append(L"l");
                                                            #line 4664 "PrintCLike.cpp.template"
                                                                print(format.toString<wchar_t>(grammar->k));
                                                            #line 8000 "PrintCLike.cpp"
  append(L" = 0");
                                                            #line 4665 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                if (grammar->k > 1)
                                                                {
                                                            #line 8006 "PrintCLike.cpp"
  append(L" ");
                                                            #line 4668 "PrintCLike.cpp.template"
                                                                  for (size_t k = 1; k < grammar->k; ++k)
                                                                  {
                                                                    if (! isPython())
                                                                    {
                                                            #line 8013 "PrintCLike.cpp"
  append(L"}");
                                                            #line 4672 "PrintCLike.cpp.template"
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
                                                            #line 8028 "PrintCLike.cpp"
  append(L"\n");
  append(L"  fprintf(stderr, \"  <parse terminal=\\\"%s\\\"%s%s%s/>\\n\", ");
                                                            #line 4685 "PrintCLike.cpp.template"
                                                                    if (stringIntroducer()[0])
                                                                    {
                                                            #line 8034 "PrintCLike.cpp"
  append(L"Utf8Encoder::encode(");
                                                            #line 4688 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 8038 "PrintCLike.cpp"
  append(L"xmlEscape(TOKEN[t], 0).c_str()");
                                                            #line 4690 "PrintCLike.cpp.template"
                                                                    if (stringIntroducer()[0])
                                                                    {
                                                            #line 8043 "PrintCLike.cpp"
  append(L").c_str()");
                                                            #line 4692 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 8047 "PrintCLike.cpp"
  append(L", (l1 == 0 ? \"\" : \" input=\\\"\"),  (l1 == 0 ? \"\" : ");
                                                            #line 4694 "PrintCLike.cpp.template"
                                                                    if (stringIntroducer()[0])
                                                                    {
                                                            #line 8052 "PrintCLike.cpp"
  append(L"Utf8Encoder::encode(");
                                                            #line 4697 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 8056 "PrintCLike.cpp"
  append(L"xmlEscape(lookaheadString().c_str(), 0).c_str()");
                                                            #line 4699 "PrintCLike.cpp.template"
                                                                    if (stringIntroducer()[0])
                                                                    {
                                                            #line 8061 "PrintCLike.cpp"
  append(L").c_str()");
                                                            #line 4701 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 8065 "PrintCLike.cpp"
  append(L"), (l1 == 0 ? \"\" : \"\\\"\"));");
                                                            #line 4703 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                                    if (isGo())
                                                                    {
                                                            #line 8073 "PrintCLike.cpp"
  append(L"\n");
  append(L"  var inputAttr string\n");
  append(L"  if (this.l1 == 0) {\n");
  append(L"    inputAttr = \"\"\n");
  append(L"  } else {\n");
  append(L"    inputAttr = \" input=\\\"\" + xmlEscape(this.lookaheadString()) + \"\\\"\"\n");
  append(L"  }");
                                                            #line 4714 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 8083 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4716 "PrintCLike.cpp.template"
                                                                    if (isHaxe())
                                                                    {
                                                            #line 8089 "PrintCLike.cpp"
  append(L"trace(");
                                                            #line 4719 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                                      print(writeTrace());
                                                                    }
                                                            #line 8097 "PrintCLike.cpp"
  append(L"\"  <parse terminal=\\\"\" + ");
                                                            #line 4724 "PrintCLike.cpp.template"
                                                                    print(staticPrefix());
                                                            #line 8101 "PrintCLike.cpp"
  append(L"xmlEscape(");
                                                            #line 4725 "PrintCLike.cpp.template"
                                                                    print(staticPrefix());
                                                                    print(isGo() ? L"token" : L"TOKEN");
                                                                    print(leftbracket());
                                                            #line 8107 "PrintCLike.cpp"
  append(L"t");
                                                            #line 4728 "PrintCLike.cpp.template"
                                                                    print(rightbracket());
                                                            #line 8111 "PrintCLike.cpp"
  append(L") + \"\\\"\" + ");
                                                            #line 4729 "PrintCLike.cpp.template"
                                                                    if (isGo())
                                                                    {
                                                            #line 8116 "PrintCLike.cpp"
  append(L"inputAttr");
                                                            #line 4731 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 8122 "PrintCLike.cpp"
  append(L"(");
                                                            #line 4734 "PrintCLike.cpp.template"
                                                                      if (isScala())
                                                                      {
                                                            #line 8127 "PrintCLike.cpp"
  append(L"if (l1 == 0) \"\" else");
                                                            #line 4736 "PrintCLike.cpp.template"
                                                                      }
                                                                      else if (isPython())
                                                                      {
                                                            #line 8133 "PrintCLike.cpp"
  append(L"\"\" if self.l1 == 0 else");
                                                            #line 4739 "PrintCLike.cpp.template"
                                                                      }
                                                                      else
                                                                      {
                                                                        print(thiz());
                                                            #line 8140 "PrintCLike.cpp"
  append(L"l1 == 0 ? \"\" :");
                                                            #line 4743 "PrintCLike.cpp.template"
                                                                      }
                                                            #line 8144 "PrintCLike.cpp"
  append(L" \" input=\\\"\" + ");
                                                            #line 4744 "PrintCLike.cpp.template"
                                                                      print(staticPrefix());
                                                            #line 8148 "PrintCLike.cpp"
  append(L"xmlEscape(");
                                                            #line 4745 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 8152 "PrintCLike.cpp"
  append(L"lookaheadString");
                                                            #line 4746 "PrintCLike.cpp.template"
                                                                      if (! isScala()) print(L"()");
                                                            #line 8156 "PrintCLike.cpp"
  append(L") + \"\\\"\")");
                                                            #line 4747 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 8160 "PrintCLike.cpp"
  append(L" + \"/>");
                                                            #line 4748 "PrintCLike.cpp.template"
                                                                    if (isHaxe())
                                                                    {
                                                            #line 8165 "PrintCLike.cpp"
  append(L"\")");
                                                            #line 4750 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 8171 "PrintCLike.cpp"
  append(L"\\n\"");
                                                            #line 4753 "PrintCLike.cpp.template"
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
                                                            #line 8185 "PrintCLike.cpp"
  append(L"el");
                                                            #line 4764 "PrintCLike.cpp.template"
                                                                    if (! isPython())
                                                                    {
                                                            #line 8190 "PrintCLike.cpp"
  append(L"se ");
                                                            #line 4766 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 8194 "PrintCLike.cpp"
  append(L"if ");
                                                            #line 4767 "PrintCLike.cpp.template"
                                                                    print(ifLeftParen());
                                                                    print(thiz());
                                                                    print(token());
                                                            #line 8200 "PrintCLike.cpp"
  append(L" < 0");
                                                            #line 4770 "PrintCLike.cpp.template"
                                                                    print(ifRightParen());
                                                                    print(leftBrace());
                                                            #line 8205 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4773 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8210 "PrintCLike.cpp"
  append(L"error(");
                                                            #line 4774 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8214 "PrintCLike.cpp"
  append(L"b1, ");
                                                            #line 4775 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8218 "PrintCLike.cpp"
  append(L"e1, -");
                                                            #line 4776 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8222 "PrintCLike.cpp"
  append(L"l1, 0, 0)");
                                                            #line 4777 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                    if (i == 0)
                                                                    {
                                                            #line 8228 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4781 "PrintCLike.cpp.template"
                                                                      print(beginThrowStmt());
                                                                      print(thiz());
                                                            #line 8234 "PrintCLike.cpp"
  append(L"bx, ");
                                                            #line 4783 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 8238 "PrintCLike.cpp"
  append(L"ex, ");
                                                            #line 4784 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 8242 "PrintCLike.cpp"
  append(L"sx, ");
                                                            #line 4785 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 8246 "PrintCLike.cpp"
  append(L"lx, ");
                                                            #line 4786 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 8250 "PrintCLike.cpp"
  append(L"tx");
                                                            #line 4787 "PrintCLike.cpp.template"
                                                                      print(endThrowStmt());
                                                                      print(semicolon());
                                                                    }
                                                                    print(rightBrace());
                                                                  }
                                                                  print(isGo() ? L" " : L"\n");
                                                            #line 8259 "PrintCLike.cpp"
  append(L"else");
                                                            #line 4793 "PrintCLike.cpp.template"
                                                                  if (isPython()) print(L":");
                                                                  print(leftBrace());
                                                            #line 8264 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4796 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8269 "PrintCLike.cpp"
  append(L"error(");
                                                            #line 4797 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8273 "PrintCLike.cpp"
  append(L"b1, ");
                                                            #line 4798 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8277 "PrintCLike.cpp"
  append(L"e1, 0, ");
                                                            #line 4799 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8281 "PrintCLike.cpp"
  append(L"l1, t)");
                                                            #line 4800 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                  if (i == 0 && grammar->noThrow)
                                                                  {
                                                            #line 8287 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4804 "PrintCLike.cpp.template"
                                                                    print(beginThrowStmt());
                                                                    print(thiz());
                                                            #line 8293 "PrintCLike.cpp"
  append(L"bx, ");
                                                            #line 4806 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8297 "PrintCLike.cpp"
  append(L"ex, ");
                                                            #line 4807 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8301 "PrintCLike.cpp"
  append(L"sx, ");
                                                            #line 4808 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8305 "PrintCLike.cpp"
  append(L"lx, ");
                                                            #line 4809 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8309 "PrintCLike.cpp"
  append(L"tx");
                                                            #line 4810 "PrintCLike.cpp.template"
                                                                    print(endThrowStmt());
                                                                    print(semicolon());
                                                                  }
                                                                  print(rightBrace());
                                                                }
                                                                else
                                                                {
                                                                  print(isGo() ? L" " : L"\n");
                                                            #line 8320 "PrintCLike.cpp"
  append(L"else");
                                                            #line 4818 "PrintCLike.cpp.template"
                                                                  if (isPython()) print(L":");
                                                                  print(leftBrace());
                                                            #line 8325 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4821 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8330 "PrintCLike.cpp"
  append(L"error(");
                                                            #line 4822 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8334 "PrintCLike.cpp"
  append(L"b1, ");
                                                            #line 4823 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8338 "PrintCLike.cpp"
  append(L"e1, 0, ");
                                                            #line 4824 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8342 "PrintCLike.cpp"
  append(L"l1, t)");
                                                            #line 4825 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                  print(rightBrace());
                                                                }
                                                                decreaseIndent();
                                                                print(rightBrace());
                                                            #line 8350 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 4831 "PrintCLike.cpp.template"
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
                                                            #line 8369 "PrintCLike.cpp"
  append(L"\n");
  append(L"  var thread = new ParsingThread().copy(thisThread, 0);\n");
  append(L"  thread.setL1(code);\n");
  append(L"  thread.setB1(begin);\n");
  append(L"  thread.setE1(end);");
                                                            #line 4851 "PrintCLike.cpp.template"
                                                                    }
                                                                    else if (isGo())
                                                                    {
                                                            #line 8379 "PrintCLike.cpp"
  append(L"\n");
  append(L"  thread := new(ParsingThread).copy(this, 0)\n");
  append(L"  thread.l1 = code\n");
  append(L"  thread.b1 = this.begin\n");
  append(L"  thread.e1 = this.end");
                                                            #line 4858 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 8389 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4862 "PrintCLike.cpp.template"
                                                                      if (isHaxe() || isScala() || isTypescript())
                                                                      {
                                                            #line 8395 "PrintCLike.cpp"
  append(L"var ");
                                                            #line 4864 "PrintCLike.cpp.template"
                                                                      }
                                                                      else if (! isPython())
                                                                      {
                                                            #line 8401 "PrintCLike.cpp"
  append(L"ParsingThread ");
                                                            #line 4867 "PrintCLike.cpp.template"
                                                                      }
                                                                      if (isCpp()) print(L"*");
                                                            #line 8406 "PrintCLike.cpp"
  append(L"thread = ");
                                                            #line 4869 "PrintCLike.cpp.template"
                                                                      if (isCpp()) print(L"(");
                                                                      if (! isPython())
                                                                      {
                                                            #line 8412 "PrintCLike.cpp"
  append(L"new ");
                                                            #line 4872 "PrintCLike.cpp.template"
                                                                      }
                                                                      if (isScala() || isPython())
                                                                      {
                                                                        print(className.c_str());
                                                            #line 8419 "PrintCLike.cpp"
  append(L".");
                                                            #line 4876 "PrintCLike.cpp.template"
                                                                      }
                                                            #line 8423 "PrintCLike.cpp"
  append(L"ParsingThread()");
                                                            #line 4877 "PrintCLike.cpp.template"
                                                                      if (isCpp()) print(L")");
                                                                      print(arrow());
                                                            #line 8428 "PrintCLike.cpp"
  append(L"copy(");
                                                            #line 4879 "PrintCLike.cpp.template"
                                                                      if (isPython())
                                                                      {
                                                            #line 8433 "PrintCLike.cpp"
  append(L"self");
                                                            #line 4881 "PrintCLike.cpp.template"
                                                                      }
                                                                      else
                                                                      {
                                                            #line 8439 "PrintCLike.cpp"
  append(L"this");
                                                            #line 4884 "PrintCLike.cpp.template"
                                                                      }
                                                            #line 8443 "PrintCLike.cpp"
  append(L", 0)");
                                                            #line 4885 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                                      if (isCpp())
                                                                      {
                                                            #line 8449 "PrintCLike.cpp"
  append(L"\n");
  append(L"  thread->stack->unshare();\n");
  append(L"  thread->stack = 0;");
                                                            #line 4890 "PrintCLike.cpp.template"
                                                                      }
                                                            #line 8455 "PrintCLike.cpp"
  append(L"\n");
  append(L"  thread");
                                                            #line 4892 "PrintCLike.cpp.template"
                                                                      print(arrow());
                                                            #line 8460 "PrintCLike.cpp"
  append(L"l1 = code");
                                                            #line 4893 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                            #line 8464 "PrintCLike.cpp"
  append(L"\n");
  append(L"  thread");
                                                            #line 4895 "PrintCLike.cpp.template"
                                                                      print(arrow());
                                                            #line 8469 "PrintCLike.cpp"
  append(L"b1 = ");
                                                            #line 4896 "PrintCLike.cpp.template"
                                                                      if (useGlr) print(thiz());
                                                            #line 8473 "PrintCLike.cpp"
  append(L"begin");
                                                            #line 4897 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                            #line 8477 "PrintCLike.cpp"
  append(L"\n");
  append(L"  thread");
                                                            #line 4899 "PrintCLike.cpp.template"
                                                                      print(arrow());
                                                            #line 8482 "PrintCLike.cpp"
  append(L"e1 = ");
                                                            #line 4900 "PrintCLike.cpp.template"
                                                                      if (useGlr) print(thiz());
                                                            #line 8486 "PrintCLike.cpp"
  append(L"end");
                                                            #line 4901 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                                    }
                                                                  }
                                                                  else
                                                                  {
                                                            #line 8494 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4907 "PrintCLike.cpp.template"
                                                                    print(intVal());
                                                            #line 8499 "PrintCLike.cpp"
  append(L"b0W");
                                                            #line 4908 "PrintCLike.cpp.template"
                                                                    print(assign());
                                                                    print(thiz());
                                                            #line 8504 "PrintCLike.cpp"
  append(L"b0; ");
                                                            #line 4910 "PrintCLike.cpp.template"
                                                                    print(intVal());
                                                            #line 8508 "PrintCLike.cpp"
  append(L"e0W");
                                                            #line 4911 "PrintCLike.cpp.template"
                                                                    print(assign());
                                                                    print(thiz());
                                                            #line 8513 "PrintCLike.cpp"
  append(L"e0");
                                                            #line 4914 "PrintCLike.cpp.template"
                                                                    for (size_t k = 1; k < grammar->k; ++k)
                                                                    {
                                                            #line 8518 "PrintCLike.cpp"
  append(L"; ");
                                                            #line 4916 "PrintCLike.cpp.template"
                                                                      print(intVal());
                                                            #line 8522 "PrintCLike.cpp"
  append(L"l");
                                                            #line 4917 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(k));
                                                            #line 8526 "PrintCLike.cpp"
  append(L"W");
                                                            #line 4918 "PrintCLike.cpp.template"
                                                                      print(assign());
                                                                      print(thiz());
                                                            #line 8531 "PrintCLike.cpp"
  append(L"l");
                                                            #line 4920 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(k));
                                                                      print(semicolon());
                                                            #line 8536 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4923 "PrintCLike.cpp.template"
                                                                      print(intVal());
                                                            #line 8541 "PrintCLike.cpp"
  append(L"b");
                                                            #line 4924 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(k));
                                                            #line 8545 "PrintCLike.cpp"
  append(L"W");
                                                            #line 4925 "PrintCLike.cpp.template"
                                                                      print(assign());
                                                                      print(thiz());
                                                            #line 8550 "PrintCLike.cpp"
  append(L"b");
                                                            #line 4927 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(k));
                                                            #line 8554 "PrintCLike.cpp"
  append(L"; ");
                                                            #line 4928 "PrintCLike.cpp.template"
                                                                      print(intVal());
                                                            #line 8558 "PrintCLike.cpp"
  append(L"e");
                                                            #line 4929 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(k));
                                                            #line 8562 "PrintCLike.cpp"
  append(L"W");
                                                            #line 4930 "PrintCLike.cpp.template"
                                                                      print(assign());
                                                                      print(thiz());
                                                            #line 8567 "PrintCLike.cpp"
  append(L"e");
                                                            #line 4932 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(k));
                                                                    }
                                                                    print(semicolon());
                                                            #line 8573 "PrintCLike.cpp"
  append(L"\n");
  append(L"\n");
  append(L"  ");
                                                            #line 4937 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8579 "PrintCLike.cpp"
  append(L"l1 = code; ");
                                                            #line 4938 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8583 "PrintCLike.cpp"
  append(L"b1 = ");
                                                            #line 4939 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8587 "PrintCLike.cpp"
  append(L"begin; ");
                                                            #line 4940 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8591 "PrintCLike.cpp"
  append(L"e1 = ");
                                                            #line 4941 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8595 "PrintCLike.cpp"
  append(L"end");
                                                            #line 4942 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                    for (size_t k = 2; k <= grammar->k; ++k)
                                                                    {
                                                            #line 8601 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4946 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 8606 "PrintCLike.cpp"
  append(L"l");
                                                            #line 4947 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(k));
                                                            #line 8610 "PrintCLike.cpp"
  append(L" = 0");
                                                            #line 4948 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                                    }
                                                                  }
                                                                  if (isLrParser)
                                                                  {
                                                            #line 8618 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 4954 "PrintCLike.cpp.template"
                                                                    if (useGlr)
                                                                    {
                                                                      if (! isCpp())
                                                                      {
                                                            #line 8626 "PrintCLike.cpp"
  append(L"thread = ");
                                                            #line 4958 "PrintCLike.cpp.template"
                                                                      }
                                                                      if (isJava())
                                                                      {
                                                                        print(className.c_str());
                                                            #line 8633 "PrintCLike.cpp"
  append(L".this.");
                                                            #line 4962 "PrintCLike.cpp.template"
                                                                      }
                                                                      else if (isCSharp() || isCpp() || isHaxe() || isScala() || isTypescript() || isGo() || isPython())
                                                                      {
                                                                        print(thiz());
                                                            #line 8640 "PrintCLike.cpp"
  append(L"parser");
                                                            #line 4966 "PrintCLike.cpp.template"
                                                                        print(arrow());
                                                                      }
                                                                    }
                                                                    else
                                                                    {
                                                                      print(thiz());
                                                                    }
                                                            #line 8650 "PrintCLike.cpp"
  append(L"parse(-1, ");
                                                            #line 4973 "PrintCLike.cpp.template"
                                                                    print(format.toString<wchar_t>(grammar->whitespace->getStateId()));
                                                                    if (tree)
                                                                    {
                                                            #line 8656 "PrintCLike.cpp"
  append(L", ");
                                                            #line 4976 "PrintCLike.cpp.template"
                                                                      print(nullPtr());
                                                                    }
                                                                    if (useGlr)
                                                                    {
                                                            #line 8663 "PrintCLike.cpp"
  append(L", thread");
                                                            #line 4980 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 8667 "PrintCLike.cpp"
  append(L")");
                                                            #line 4981 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                  }
                                                                  else
                                                                  {
                                                            #line 8674 "PrintCLike.cpp"
  append(L"\n");
  append(L"\n");
  append(L"  ");
                                                            #line 4987 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8680 "PrintCLike.cpp"
  append(L"try_");
                                                            #line 4988 "PrintCLike.cpp.template"
                                                                    print(Format::acceptableName<WString>(grammar->whitespace->name).c_str());
                                                                    if (! isScala()) print(L"()");
                                                                    print(semicolon());
                                                                  }
                                                                  if (useGlr)
                                                                  {
                                                                    if (isJavascript())
                                                                    {
                                                            #line 8691 "PrintCLike.cpp"
  append(L"\n");
  append(L"  end = thread.getEnd();");
                                                            #line 4997 "PrintCLike.cpp.template"
                                                                    }
                                                                    else if (isCpp())
                                                                    {
                                                            #line 8698 "PrintCLike.cpp"
  append(L"\n");
  append(L"  end = thread->end;\n");
  append(L"  delete thread;");
                                                            #line 5002 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 8706 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5006 "PrintCLike.cpp.template"
                                                                      if (useGlr) print(thiz());
                                                            #line 8711 "PrintCLike.cpp"
  append(L"end = thread");
                                                            #line 5007 "PrintCLike.cpp.template"
                                                                      print(arrow());
                                                            #line 8715 "PrintCLike.cpp"
  append(L"end");
                                                            #line 5008 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                                    }
                                                                  }
                                                                  else
                                                                  {
                                                            #line 8723 "PrintCLike.cpp"
  append(L"\n");
  append(L"\n");
  append(L"  ");
                                                            #line 5015 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8729 "PrintCLike.cpp"
  append(L"b0 = b0W; ");
                                                            #line 5016 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 8733 "PrintCLike.cpp"
  append(L"e0 = e0W");
                                                            #line 5017 "PrintCLike.cpp.template"
                                                                    for (size_t k = 1; k < grammar->k; ++k)
                                                                    {
                                                            #line 8738 "PrintCLike.cpp"
  append(L"; ");
                                                            #line 5019 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 8742 "PrintCLike.cpp"
  append(L"l");
                                                            #line 5020 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(k));
                                                            #line 8746 "PrintCLike.cpp"
  append(L" = l");
                                                            #line 5021 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(k));
                                                            #line 8750 "PrintCLike.cpp"
  append(L"W");
                                                            #line 5022 "PrintCLike.cpp.template"
                                                                      if (isPython())
                                                                      {
                                                            #line 8755 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5025 "PrintCLike.cpp.template"
                                                                      }
                                                                      else
                                                                      {
                                                            #line 8762 "PrintCLike.cpp"
  append(L"; ");
                                                            #line 5028 "PrintCLike.cpp.template"
                                                                      }
                                                            #line 8766 "PrintCLike.cpp"
  append(L"if ");
                                                            #line 5029 "PrintCLike.cpp.template"
                                                                      print(ifLeftParen());
                                                                      print(thiz());
                                                            #line 8771 "PrintCLike.cpp"
  append(L"l");
                                                            #line 5031 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(k));
                                                            #line 8775 "PrintCLike.cpp"
  append(L" != 0");
                                                            #line 5032 "PrintCLike.cpp.template"
                                                                      print(ifRightParen());
                                                                      if (isPython())
                                                                      {
                                                                        increaseIndent();
                                                                      }
                                                                      else
                                                                      {
                                                            #line 8785 "PrintCLike.cpp"
  append(L" {");
                                                            #line 5039 "PrintCLike.cpp.template"
                                                                      }
                                                            #line 8789 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5041 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 8794 "PrintCLike.cpp"
  append(L"b");
                                                            #line 5042 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(k));
                                                            #line 8798 "PrintCLike.cpp"
  append(L" = b");
                                                            #line 5043 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(k));
                                                            #line 8802 "PrintCLike.cpp"
  append(L"W; ");
                                                            #line 5044 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 8806 "PrintCLike.cpp"
  append(L"e");
                                                            #line 5045 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(k));
                                                            #line 8810 "PrintCLike.cpp"
  append(L" = e");
                                                            #line 5046 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(k));
                                                            #line 8814 "PrintCLike.cpp"
  append(L"W");
                                                            #line 5047 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(semicolon());
                                                                    if (isPython())
                                                                    {
                                                                      decreaseIndent(grammar->k - 1);
                                                                    }
                                                                    else
                                                                    {
                                                            #line 8825 "PrintCLike.cpp"
  append(L" ");
                                                            #line 5055 "PrintCLike.cpp.template"
                                                                      for (size_t k = 1; k < grammar->k; ++k)
                                                                      {
                                                            #line 8830 "PrintCLike.cpp"
  append(L"}");
                                                            #line 5057 "PrintCLike.cpp.template"
                                                                      }
                                                                    }
                                                                  }
                                                                  print(rightBrace());
                                                            #line 8837 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5062 "PrintCLike.cpp.template"
                                                                  if (! isGo())
                                                                    decreaseIndent();
                                                                }
                                                                if (tree && ! isLrParser)
                                                                {
                                                                  if (! isGo())
                                                                    increaseIndent();
                                                                  openMethod (voidType(), L"", L"whitespace", L"");
                                                                  print(leftBrace());
                                                            #line 8849 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if ");
                                                            #line 5072 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                                  print(thiz());
                                                            #line 8855 "PrintCLike.cpp"
  append(L"e0 != ");
                                                            #line 5074 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8859 "PrintCLike.cpp"
  append(L"b1");
                                                            #line 5075 "PrintCLike.cpp.template"
                                                                  print(ifRightParen());
                                                                  increaseIndent();
                                                                  print(leftBrace());
                                                                  decreaseIndent();
                                                            #line 8866 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 5080 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8871 "PrintCLike.cpp"
  append(L"eventHandler");
                                                            #line 5081 "PrintCLike.cpp.template"
                                                                  print(arrow());
                                                                  if (isGo())
                                                                  {
                                                            #line 8877 "PrintCLike.cpp"
  append(L"W");
                                                            #line 5084 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 8883 "PrintCLike.cpp"
  append(L"w");
                                                            #line 5087 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 8887 "PrintCLike.cpp"
  append(L"hitespace(");
                                                            #line 5088 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8891 "PrintCLike.cpp"
  append(L"e0, ");
                                                            #line 5089 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8895 "PrintCLike.cpp"
  append(L"b1)");
                                                            #line 5090 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                            #line 8899 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 5092 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8904 "PrintCLike.cpp"
  append(L"e0 = ");
                                                            #line 5093 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 8908 "PrintCLike.cpp"
  append(L"b1");
                                                            #line 5094 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                  increaseIndent();
                                                                  print(rightBrace());
                                                                  decreaseIndent();
                                                                  print(rightBrace());
                                                                  if (! isGo())
                                                                    decreaseIndent();
                                                            #line 8918 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5102 "PrintCLike.cpp.template"
                                                                }
                                                                if (! isGo())
                                                                  increaseIndent();
                                                                openMethod(intType(), L"", L"matchW", L"int tokenSetId", false, useGlr ? L"ParsingThread" : className.c_str());
                                                                print(leftBrace());
                                                                if (isScala())
                                                                {
                                                            #line 8928 "PrintCLike.cpp"
  append(L"\n");
  append(L"  var continue = true\n");
  append(L"  var code = 0\n");
  append(L"  while (continue) {\n");
  append(L"    code = matcher(tokenSetId)");
                                                            #line 5113 "PrintCLike.cpp.template"
                                                                  increaseIndent(2);
                                                                }
                                                                else
                                                                {
                                                                  if (! isPython())
                                                                  {
                                                            #line 8941 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5120 "PrintCLike.cpp.template"
                                                                    print((isJavascript() || isTypescript() || isHaxe() || isGo()) ? L"var" : L"int");
                                                            #line 8946 "PrintCLike.cpp"
  append(L" code");
                                                            #line 5121 "PrintCLike.cpp.template"
                                                                    if (isTypescript())
                                                                    {
                                                            #line 8951 "PrintCLike.cpp"
  append(L": number");
                                                            #line 5123 "PrintCLike.cpp.template"
                                                                    }
                                                                    else if (isGo())
                                                                    {
                                                            #line 8957 "PrintCLike.cpp"
  append(L" int");
                                                            #line 5126 "PrintCLike.cpp.template"
                                                                    }
                                                                    if (isHaxe())
                                                                    {
                                                            #line 8963 "PrintCLike.cpp"
  append(L" = 0");
                                                            #line 5129 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(semicolon());
                                                                  }
                                                                  if (isHaxe() || isPython())
                                                                  {
                                                            #line 8971 "PrintCLike.cpp"
  append(L"\n");
  append(L"  while ");
                                                            #line 5135 "PrintCLike.cpp.template"
                                                                    print(ifLeftParen());
                                                                    print(isPython() ? L"T" : L"t");
                                                            #line 8977 "PrintCLike.cpp"
  append(L"rue");
                                                            #line 5137 "PrintCLike.cpp.template"
                                                                    print(ifRightParen());
                                                                  }
                                                                  else
                                                                  {
                                                            #line 8984 "PrintCLike.cpp"
  append(L"\n");
  append(L"  for");
                                                            #line 5142 "PrintCLike.cpp.template"
                                                                    if (! isGo())
                                                                    {
                                                            #line 8990 "PrintCLike.cpp"
  append(L" (;;)");
                                                            #line 5144 "PrintCLike.cpp.template"
                                                                    }
                                                                  }
                                                                  increaseIndent();
                                                                  print(leftBrace());
                                                                  increaseIndent();
                                                            #line 8998 "PrintCLike.cpp"
  append(L"\n");
  append(L"code = ");
                                                            #line 5150 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 9003 "PrintCLike.cpp"
  append(L"match(tokenSetId)");
                                                            #line 5151 "PrintCLike.cpp.template"
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
                                                            #line 9032 "PrintCLike.cpp"
  append(L"\n");
  append(L"  continue = false\n");
  append(L"}\n");
  append(L"else {\n");
  append(L"  ");
                                                            #line 5181 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 9040 "PrintCLike.cpp"
  append(L"skip(code)\n");
  append(L"}");
                                                            #line 5183 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 9047 "PrintCLike.cpp"
  append(L"\n");
  append(L"  break");
                                                            #line 5187 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                    print(rightBrace());
                                                            #line 9053 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5190 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 9057 "PrintCLike.cpp"
  append(L"skip(code);");
                                                            #line 5191 "PrintCLike.cpp.template"
                                                                  }
                                                                }
                                                                else if (isScala())
                                                                {
                                                            #line 9064 "PrintCLike.cpp"
  append(L"\n");
  append(L"continue = false");
                                                            #line 5196 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 9071 "PrintCLike.cpp"
  append(L"\n");
  append(L"break");
                                                            #line 5200 "PrintCLike.cpp.template"
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
                                                            #line 9085 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5211 "PrintCLike.cpp.template"
                                                                if (! isScala())
                                                                {
                                                            #line 9091 "PrintCLike.cpp"
  append(L"return ");
                                                            #line 5213 "PrintCLike.cpp.template"
                                                                }
                                                            #line 9095 "PrintCLike.cpp"
  append(L"code");
                                                            #line 5214 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                print(rightBrace());
                                                            #line 9100 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5217 "PrintCLike.cpp.template"
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
                                                            #line 9116 "PrintCLike.cpp"
  append(L"\n");
  append(L"def parse(): Unit = {\n");
  append(L"  parse_");
                                                            #line 5232 "PrintCLike.cpp.template"
                                                                  print(Format::acceptableName<WString>(grammar->startSymbol()->name).c_str());
                                                            #line 9122 "PrintCLike.cpp"
  append(L"()\n");
  append(L"}\n");
                                                            #line 5235 "PrintCLike.cpp.template"
                                                                }
                                                                if (memoization)
                                                                {
                                                                  int bits = Math::bits(grammar->conflictCount);
                                                            #line 9130 "PrintCLike.cpp"
  append(L"\n");
  append(L"private def memoize(i: Int, e: Int, v: Int): Unit = {\n");
  append(L"  memo.put((e << ");
                                                            #line 5241 "PrintCLike.cpp.template"
                                                                  print(format.toString<wchar_t>(bits));
                                                            #line 9136 "PrintCLike.cpp"
  append(L") + i, v)\n");
  append(L"}\n");
  append(L"\n");
  append(L"private def memoized(i: Int, e: Int) = {\n");
  append(L"  memo.getOrElse((e << ");
                                                            #line 5246 "PrintCLike.cpp.template"
                                                                  print(format.toString<wchar_t>(bits));
                                                            #line 9144 "PrintCLike.cpp"
  append(L") + i, 0)\n");
  append(L"}\n");
                                                            #line 5249 "PrintCLike.cpp.template"
                                                                }
                                                            #line 9149 "PrintCLike.cpp"
  append(L"\n");
  append(L"def error(b: Int, e: Int, s: Int, l: Int, t: Int): Int = {");
                                                            #line 5251 "PrintCLike.cpp.template"
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
                                                            #line 9163 "PrintCLike.cpp"
  append(L"\n");
  append(L"if ");
                                                            #line 5262 "PrintCLike.cpp.template"
                                                                print(ifLeftParen());
                                                                if (grammar->noThrow)
                                                                {
                                                                  print(thiz());
                                                            #line 9171 "PrintCLike.cpp"
  append(L"viable ");
                                                            #line 5266 "PrintCLike.cpp.template"
                                                                  if (isPython())
                                                                  {
                                                            #line 9176 "PrintCLike.cpp"
  append(L"and");
                                                            #line 5268 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 9182 "PrintCLike.cpp"
  append(L"&&");
                                                            #line 5271 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 9186 "PrintCLike.cpp"
  append(L" ");
                                                            #line 5272 "PrintCLike.cpp.template"
                                                                }
                                                            #line 9190 "PrintCLike.cpp"
  append(L"e >= ");
                                                            #line 5273 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 9194 "PrintCLike.cpp"
  append(L"ex");
                                                            #line 5274 "PrintCLike.cpp.template"
                                                                print(ifRightParen());
                                                                print(leftBrace());
                                                            #line 9199 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5277 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 9204 "PrintCLike.cpp"
  append(L"bx = b");
                                                            #line 5278 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 9208 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5280 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 9213 "PrintCLike.cpp"
  append(L"ex = e");
                                                            #line 5281 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 9217 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5283 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 9222 "PrintCLike.cpp"
  append(L"sx = s");
                                                            #line 5284 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 9226 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5286 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 9231 "PrintCLike.cpp"
  append(L"lx = l");
                                                            #line 5287 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 9235 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5289 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 9240 "PrintCLike.cpp"
  append(L"tx = t");
                                                            #line 5290 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                print(rightBrace());
                                                                decreaseIndent();
                                                                if (grammar->noThrow)
                                                                {
                                                            #line 9248 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5296 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 9253 "PrintCLike.cpp"
  append(L"viable = ");
                                                            #line 5297 "PrintCLike.cpp.template"
                                                                  if (isPython())
                                                                  {
                                                            #line 9258 "PrintCLike.cpp"
  append(L"F");
                                                            #line 5299 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 9264 "PrintCLike.cpp"
  append(L"f");
                                                            #line 5302 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 9268 "PrintCLike.cpp"
  append(L"alse");
                                                            #line 5303 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                            #line 9272 "PrintCLike.cpp"
  append(L"\n");
  append(L"  return -s");
                                                            #line 5305 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                                else
                                                                {
                                                                  printFlush(1, true);
                                                            #line 9281 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5311 "PrintCLike.cpp.template"
                                                                  print(beginThrowStmt());
                                                                  print(thiz());
                                                            #line 9287 "PrintCLike.cpp"
  append(L"bx, ");
                                                            #line 5313 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 9291 "PrintCLike.cpp"
  append(L"ex, ");
                                                            #line 5314 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 9295 "PrintCLike.cpp"
  append(L"sx, ");
                                                            #line 5315 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 9299 "PrintCLike.cpp"
  append(L"lx, ");
                                                            #line 5316 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 9303 "PrintCLike.cpp"
  append(L"tx");
                                                            #line 5317 "PrintCLike.cpp.template"
                                                                  print(endThrowStmt());
                                                                  print(semicolon());
                                                                }
                                                              }
                                                              else
                                                              {
                                                                printFlush(1, true);
                                                            #line 9313 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5325 "PrintCLike.cpp.template"
                                                                if (isGo())
                                                                {
                                                            #line 9319 "PrintCLike.cpp"
  append(L"panic(&ParseError{b, e, s, l, t");
                                                            #line 5327 "PrintCLike.cpp.template"
                                                                  if (useGlr)
                                                                  {
                                                            #line 9324 "PrintCLike.cpp"
  append(L", false");
                                                            #line 5329 "PrintCLike.cpp.template"
                                                                    if (tree)
                                                                    {
                                                            #line 9329 "PrintCLike.cpp"
  append(L", nil");
                                                            #line 5331 "PrintCLike.cpp.template"
                                                                    }
                                                                  }
                                                            #line 9334 "PrintCLike.cpp"
  append(L"})");
                                                            #line 5333 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                                  print(beginThrowStmt());
                                                            #line 9341 "PrintCLike.cpp"
  append(L"b, e, s, l, t");
                                                            #line 5337 "PrintCLike.cpp.template"
                                                                  print(endThrowStmt());
                                                                  print(semicolon());
                                                                }
                                                              }
                                                              print(rightBrace());
                                                            #line 9349 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5343 "PrintCLike.cpp.template"
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
                                                            #line 9374 "PrintCLike.cpp"
  append(L"\n");
  append(L"i := lookback[y]\n");
  append(L"l := lookback[i]\n");
  append(L"for l > x {");
                                                            #line 5368 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 9383 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5372 "PrintCLike.cpp.template"
                                                                  print(intVar());
                                                            #line 9387 "PrintCLike.cpp"
  append(L"i");
                                                            #line 5373 "PrintCLike.cpp.template"
                                                                  print(assign());
                                                                  print(staticPrefix());
                                                                  print(lookback);
                                                                  print(leftbracket());
                                                            #line 9394 "PrintCLike.cpp"
  append(L"y");
                                                            #line 5377 "PrintCLike.cpp.template"
                                                                  print(rightbracket());
                                                                  print(semicolon());
                                                            #line 9399 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5380 "PrintCLike.cpp.template"
                                                                  print(intVar());
                                                            #line 9403 "PrintCLike.cpp"
  append(L"l");
                                                            #line 5381 "PrintCLike.cpp.template"
                                                                  print(assign());
                                                                  print(staticPrefix());
                                                                  print(lookback);
                                                                  print(leftbracket());
                                                            #line 9410 "PrintCLike.cpp"
  append(L"i");
                                                            #line 5385 "PrintCLike.cpp.template"
                                                                  print(rightbracket());
                                                                  print(semicolon());
                                                            #line 9415 "PrintCLike.cpp"
  append(L"\n");
  append(L"while ");
                                                            #line 5388 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                            #line 9420 "PrintCLike.cpp"
  append(L"l > x");
                                                            #line 5389 "PrintCLike.cpp.template"
                                                                  print(ifRightParen());
                                                                  print(leftBrace());
                                                                }
                                                            #line 9426 "PrintCLike.cpp"
  append(L"\n");
  append(L"  i += 2");
                                                            #line 5393 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 9431 "PrintCLike.cpp"
  append(L"\n");
  append(L"  l = ");
                                                            #line 5395 "PrintCLike.cpp.template"
                                                                print(staticPrefix());
                                                                print(lookback);
                                                                print(leftbracket());
                                                            #line 9438 "PrintCLike.cpp"
  append(L"i");
                                                            #line 5398 "PrintCLike.cpp.template"
                                                                print(rightbracket());
                                                                print(semicolon());
                                                                print(rightBrace());
                                                            #line 9444 "PrintCLike.cpp"
  append(L"\n");
  append(L"if ");
                                                            #line 5402 "PrintCLike.cpp.template"
                                                                print(ifLeftParen());
                                                            #line 9449 "PrintCLike.cpp"
  append(L"l < x");
                                                            #line 5403 "PrintCLike.cpp.template"
                                                                print(ifRightParen());
                                                                print(leftBrace());
                                                            #line 9454 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5406 "PrintCLike.cpp.template"
                                                                print(returnKeyword());
                                                            #line 9459 "PrintCLike.cpp"
  append(L"0");
                                                            #line 5407 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 9463 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5409 "PrintCLike.cpp.template"
                                                                print(elseWithBraces());
                                                            #line 9467 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5411 "PrintCLike.cpp.template"
                                                                print(returnKeyword());
                                                                print(staticPrefix());
                                                                print(lookback);
                                                                print(leftbracket());
                                                            #line 9475 "PrintCLike.cpp"
  append(L"i + 1");
                                                            #line 5415 "PrintCLike.cpp.template"
                                                                print(rightbracket());
                                                                print(semicolon());
                                                                print(rightBrace());
                                                                decreaseIndent();
                                                                print(rightBrace());
                                                            #line 9483 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5421 "PrintCLike.cpp.template"
                                                                if (isJavascript() && useGlr)
                                                                {
                                                            #line 9488 "PrintCLike.cpp"
  append(L"\n");
  append(L"this.count = function(code)\n");
                                                            #line 5425 "PrintCLike.cpp.template"
                                                                }
                                                                else if (isTypescript() && useGlr)
                                                                {
                                                            #line 9495 "PrintCLike.cpp"
  append(L"\n");
  append(L"public count(code: number)\n");
                                                            #line 5430 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                                  openMethod(intType(), L"", L"count", L"int code", false, clazz);
                                                                }
                                                                print(leftBrace());
                                                                increaseIndent();
                                                            #line 9506 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5438 "PrintCLike.cpp.template"
                                                                print(intVar());
                                                            #line 9510 "PrintCLike.cpp"
  append(L"count");
                                                            #line 5439 "PrintCLike.cpp.template"
                                                                print(assign());
                                                            #line 9514 "PrintCLike.cpp"
  append(L"0");
                                                            #line 5440 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                int stackElementSize = tree ? 3 : 2;
                                                                if (isHaxe() || isScala())
                                                                {
                                                                  if (useGlr)
                                                                  {
                                                            #line 9523 "PrintCLike.cpp"
  append(L"\n");
  append(L"var node = this");
                                                            #line 5447 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                    if (isScala())
                                                                    {
                                                            #line 9530 "PrintCLike.cpp"
  append(L"\n");
  append(L"var c = code");
                                                            #line 5451 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 9535 "PrintCLike.cpp"
  append(L"\n");
  append(L"while ");
                                                            #line 5453 "PrintCLike.cpp.template"
                                                                    print(ifLeftParen());
                                                            #line 9540 "PrintCLike.cpp"
  append(L"node.state >= 0");
                                                            #line 5454 "PrintCLike.cpp.template"
                                                                    print(ifRightParen());
                                                                    print(leftBrace());
                                                                    if (isScala())
                                                                    {
                                                            #line 9547 "PrintCLike.cpp"
  append(L"\n");
  append(L"  c = lookback(node.code, c)\n");
  append(L"  if (c == 0) return count\n");
  append(L"  count += 1");
                                                            #line 5461 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 9556 "PrintCLike.cpp"
  append(L"\n");
  append(L"  code = lookback(node.code, code);\n");
  append(L"  if ");
                                                            #line 5466 "PrintCLike.cpp.template"
                                                                      print(ifLeftParen());
                                                            #line 9562 "PrintCLike.cpp"
  append(L"code == 0");
                                                            #line 5467 "PrintCLike.cpp.template"
                                                                      print(ifRightParen());
                                                            #line 9566 "PrintCLike.cpp"
  append(L"\n");
  append(L"    break");
                                                            #line 5470 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                            #line 9571 "PrintCLike.cpp"
  append(L"\n");
  append(L"  count++");
                                                            #line 5472 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                                    }
                                                            #line 9577 "PrintCLike.cpp"
  append(L"\n");
  append(L"  node = node.link");
                                                            #line 5475 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                  }
                                                                  else
                                                                  {
                                                            #line 9585 "PrintCLike.cpp"
  append(L"\n");
  append(L"var t = top");
                                                            #line 5480 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 9590 "PrintCLike.cpp"
  append(L"\n");
  append(L"var c = code");
                                                            #line 5482 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 9595 "PrintCLike.cpp"
  append(L"\n");
  append(L"while (t >= 0)");
                                                            #line 5484 "PrintCLike.cpp.template"
                                                                    print(leftBrace());
                                                            #line 9600 "PrintCLike.cpp"
  append(L"\n");
  append(L"  c = lookback(iStack");
                                                            #line 5486 "PrintCLike.cpp.template"
                                                                    print(leftbracket());
                                                            #line 9605 "PrintCLike.cpp"
  append(L"t");
                                                            #line 5487 "PrintCLike.cpp.template"
                                                                    print(rightbracket());
                                                            #line 9609 "PrintCLike.cpp"
  append(L", c)");
                                                            #line 5488 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 9613 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if ");
                                                            #line 5490 "PrintCLike.cpp.template"
                                                                    print(ifLeftParen());
                                                            #line 9618 "PrintCLike.cpp"
  append(L"c == 0");
                                                            #line 5491 "PrintCLike.cpp.template"
                                                                    print(ifRightParen());
                                                            #line 9622 "PrintCLike.cpp"
  append(L" return count");
                                                            #line 5492 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 9626 "PrintCLike.cpp"
  append(L"\n");
  append(L"  count += 1");
                                                            #line 5494 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                            #line 9631 "PrintCLike.cpp"
  append(L"\n");
  append(L"  t -= ");
                                                            #line 5496 "PrintCLike.cpp.template"
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
                                                            #line 9645 "PrintCLike.cpp"
  append(L"\n");
  append(L"node = self\n");
  append(L"while ");
                                                            #line 5508 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 9653 "PrintCLike.cpp"
  append(L"\n");
  append(L"for ");
                                                            #line 5512 "PrintCLike.cpp.template"
                                                                      print(ifLeftParen());
                                                                      if (isJavascript() || isTypescript())
                                                                      {
                                                            #line 9660 "PrintCLike.cpp"
  append(L"var ");
                                                            #line 5515 "PrintCLike.cpp.template"
                                                                      }
                                                                      else if (!isGo())
                                                                      {
                                                            #line 9666 "PrintCLike.cpp"
  append(L"StackNode ");
                                                            #line 5518 "PrintCLike.cpp.template"
                                                                      }
                                                                      if (isCpp()) print(L"*");
                                                            #line 9671 "PrintCLike.cpp"
  append(L"node");
                                                            #line 5520 "PrintCLike.cpp.template"
                                                                      if (isTypescript())
                                                                      {
                                                            #line 9676 "PrintCLike.cpp"
  append(L": StackNode");
                                                            #line 5522 "PrintCLike.cpp.template"
                                                                      }
                                                                      print(assign());
                                                            #line 9681 "PrintCLike.cpp"
  append(L"this; ");
                                                            #line 5524 "PrintCLike.cpp.template"
                                                                    }
                                                            #line 9685 "PrintCLike.cpp"
  append(L"node");
                                                            #line 5525 "PrintCLike.cpp.template"
                                                                    print(arrow());
                                                            #line 9689 "PrintCLike.cpp"
  append(L"state >= 0");
                                                            #line 5526 "PrintCLike.cpp.template"
                                                                    if (isPython())
                                                                    {
                                                            #line 9694 "PrintCLike.cpp"
  append(L":");
                                                            #line 5528 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 9700 "PrintCLike.cpp"
  append(L"; node = node");
                                                            #line 5531 "PrintCLike.cpp.template"
                                                                      print(arrow());
                                                            #line 9704 "PrintCLike.cpp"
  append(L"link");
                                                            #line 5532 "PrintCLike.cpp.template"
                                                                      print(ifRightParen());
                                                                    }
                                                                    print(leftBrace());
                                                            #line 9710 "PrintCLike.cpp"
  append(L"\n");
  append(L"  code = ");
                                                            #line 5536 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                                    print(isGo() ? L"L" : L"l");
                                                            #line 9716 "PrintCLike.cpp"
  append(L"ookback(node");
                                                            #line 5538 "PrintCLike.cpp.template"
                                                                    print(arrow());
                                                            #line 9720 "PrintCLike.cpp"
  append(L"code, code)");
                                                            #line 5539 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                  }
                                                                  else
                                                                  {
                                                                    if (isPython())
                                                                    {
                                                            #line 9729 "PrintCLike.cpp"
  append(L"\n");
  append(L"t");
                                                            #line 5546 "PrintCLike.cpp.template"
                                                                      print(assign());
                                                                      print(thiz());
                                                            #line 9735 "PrintCLike.cpp"
  append(L"top");
                                                            #line 5548 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                            #line 9739 "PrintCLike.cpp"
  append(L"\n");
  append(L"while ");
                                                            #line 5550 "PrintCLike.cpp.template"
                                                                      print(ifLeftParen());
                                                                      print(intVar());
                                                            #line 9745 "PrintCLike.cpp"
  append(L"t >= 0");
                                                            #line 5552 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 9751 "PrintCLike.cpp"
  append(L"\n");
  append(L"for ");
                                                            #line 5556 "PrintCLike.cpp.template"
                                                                      print(ifLeftParen());
                                                                      print(intVar());
                                                            #line 9757 "PrintCLike.cpp"
  append(L"t");
                                                            #line 5558 "PrintCLike.cpp.template"
                                                                      print(assign());
                                                                      print(thiz());
                                                            #line 9762 "PrintCLike.cpp"
  append(L"top; t >= 0; t -= ");
                                                            #line 5560 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(stackElementSize));
                                                                    }
                                                                    print(ifRightParen());
                                                                    print(leftBrace());
                                                            #line 9769 "PrintCLike.cpp"
  append(L"\n");
  append(L"  code = ");
                                                            #line 5565 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 9774 "PrintCLike.cpp"
  append(L"lookback(");
                                                            #line 5566 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 9778 "PrintCLike.cpp"
  append(L"iStack[t], code)");
                                                            #line 5567 "PrintCLike.cpp.template"
                                                                    print(semicolon());
                                                                  }
                                                            #line 9783 "PrintCLike.cpp"
  append(L"\n");
  append(L"  if ");
                                                            #line 5570 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                            #line 9788 "PrintCLike.cpp"
  append(L"code == 0");
                                                            #line 5571 "PrintCLike.cpp.template"
                                                                  print(ifRightParen());
                                                                  increaseIndent();
                                                                  print(leftBrace());
                                                            #line 9794 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5575 "PrintCLike.cpp.template"
                                                                  if (! isHaxe() && ! isScala())
                                                                  {
                                                            #line 9800 "PrintCLike.cpp"
  append(L"break");
                                                            #line 5577 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 9806 "PrintCLike.cpp"
  append(L"return count");
                                                            #line 5580 "PrintCLike.cpp.template"
                                                                  }
                                                                  print(semicolon());
                                                                  print(rightBrace());
                                                                  decreaseIndent();
                                                            #line 9813 "PrintCLike.cpp"
  append(L"\n");
  append(L"  count += 1");
                                                            #line 5585 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                  if (isPython())
                                                                  {
                                                                    if (useGlr)
                                                                    {
                                                            #line 9822 "PrintCLike.cpp"
  append(L"\n");
  append(L"  node = node.link");
                                                            #line 5591 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 9829 "PrintCLike.cpp"
  append(L"\n");
  append(L"  t -= ");
                                                            #line 5595 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(stackElementSize));
                                                                    }
                                                                  }
                                                                }
                                                                print(rightBrace());
                                                            #line 9838 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5601 "PrintCLike.cpp.template"
                                                                print(returnKeyword());
                                                            #line 9842 "PrintCLike.cpp"
  append(L"count");
                                                            #line 5602 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                decreaseIndent();
                                                                print(rightBrace());
                                                                if (isJavascript() && useGlr)
                                                                {
                                                            #line 9850 "PrintCLike.cpp"
  append(L";");
                                                            #line 5607 "PrintCLike.cpp.template"
                                                                }
                                                            #line 9854 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5609 "PrintCLike.cpp.template"
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
                                                            #line 9879 "PrintCLike.cpp"
  append(L"\n");
  append(L"if ");
                                                            #line 5632 "PrintCLike.cpp.template"
                                                                  print(ifLeftParen());
                                                                  print(thiz());
                                                            #line 9885 "PrintCLike.cpp"
  append(L"l");
                                                            #line 5634 "PrintCLike.cpp.template"
                                                                  print(kAsString);
                                                            #line 9889 "PrintCLike.cpp"
  append(L" == 0");
                                                            #line 5635 "PrintCLike.cpp.template"
                                                                  print(ifRightParen());
                                                                  print(leftBrace());
                                                            #line 9894 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5638 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 9899 "PrintCLike.cpp"
  append(L"l");
                                                            #line 5639 "PrintCLike.cpp.template"
                                                                  print(kAsString);
                                                            #line 9903 "PrintCLike.cpp"
  append(L" = ");
                                                            #line 5640 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 9907 "PrintCLike.cpp"
  append(L"match");
                                                            #line 5641 "PrintCLike.cpp.template"
                                                                  if (withWhitespace)
                                                                  {
                                                            #line 9912 "PrintCLike.cpp"
  append(L"W");
                                                            #line 5643 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isScala())
                                                                  {
                                                            #line 9918 "PrintCLike.cpp"
  append(L"er");
                                                            #line 5646 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 9922 "PrintCLike.cpp"
  append(L"(tokenSetId)");
                                                            #line 5647 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                            #line 9926 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5649 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 9931 "PrintCLike.cpp"
  append(L"b");
                                                            #line 5650 "PrintCLike.cpp.template"
                                                                  print(kAsString);
                                                            #line 9935 "PrintCLike.cpp"
  append(L" = ");
                                                            #line 5651 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 9939 "PrintCLike.cpp"
  append(L"begin");
                                                            #line 5652 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                            #line 9943 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5654 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 9948 "PrintCLike.cpp"
  append(L"e");
                                                            #line 5655 "PrintCLike.cpp.template"
                                                                  print(kAsString);
                                                            #line 9952 "PrintCLike.cpp"
  append(L" = ");
                                                            #line 5656 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 9956 "PrintCLike.cpp"
  append(L"end");
                                                            #line 5657 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                  print(rightBrace());
                                                                  if (unlimitedLookahead)
                                                                  {
                                                                    if (k >= 2)
                                                                    {
                                                            #line 9965 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5664 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 9969 "PrintCLike.cpp"
  append(L"lk = prefix + ");
                                                            #line 5665 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 9973 "PrintCLike.cpp"
  append(L"l");
                                                            #line 5666 "PrintCLike.cpp.template"
                                                                      print(kAsString);
                                                                      print(semicolon());
                                                                    }
                                                                  }
                                                                  else
                                                                  {
                                                                    if (k == 2)
                                                                    {
                                                            #line 9984 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5675 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 9988 "PrintCLike.cpp"
  append(L"lk = (");
                                                            #line 5676 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 9992 "PrintCLike.cpp"
  append(L"l2 << ");
                                                            #line 5677 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>(grammar->tokenSequenceFactory->tokenBits()));
                                                            #line 9996 "PrintCLike.cpp"
  append(L") | ");
                                                            #line 5678 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 10000 "PrintCLike.cpp"
  append(L"l1");
                                                            #line 5679 "PrintCLike.cpp.template"
                                                                      print(semicolon());
                                                                    }
                                                                    else if (k > 2)
                                                                    {
                                                            #line 10007 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5684 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 10011 "PrintCLike.cpp"
  append(L"lk |= ");
                                                            #line 5685 "PrintCLike.cpp.template"
                                                                      print(thiz());
                                                            #line 10015 "PrintCLike.cpp"
  append(L"l");
                                                            #line 5686 "PrintCLike.cpp.template"
                                                                      print(kAsString);
                                                            #line 10019 "PrintCLike.cpp"
  append(L" << ");
                                                            #line 5687 "PrintCLike.cpp.template"
                                                                      print(format.toString<wchar_t>((k - 1) * grammar->tokenSequenceFactory->tokenBits()));
                                                                      print(semicolon());
                                                                    }
                                                                  }
                                                                  decreaseIndent();
                                                                  print(rightBrace());
                                                            #line 10028 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5694 "PrintCLike.cpp.template"
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
                                                            #line 10056 "PrintCLike.cpp"
  append(L"\n");
  append(L"  return ");
                                                            #line 5720 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                                if (useGlr && (isCSharp() || isCpp() || isHaxe() || isScala() || isTypescript()))
                                                                {
                                                            #line 10063 "PrintCLike.cpp"
  append(L"parser");
                                                            #line 5723 "PrintCLike.cpp.template"
                                                                  print(arrow());
                                                                }
                                                            #line 10068 "PrintCLike.cpp"
  append(L"input");
                                                            #line 5725 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                print(rightBrace());
                                                                if (isJavascript())
                                                                {
                                                            #line 10075 "PrintCLike.cpp"
  append(L";");
                                                            #line 5729 "PrintCLike.cpp.template"
                                                                }
                                                            #line 10079 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5731 "PrintCLike.cpp.template"
                                                                openMethod(intType(), L"", L"getTokenOffset", L"", true);
                                                                print(leftBrace());
                                                            #line 10084 "PrintCLike.cpp"
  append(L"\n");
  append(L"  return ");
                                                            #line 5734 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 10089 "PrintCLike.cpp"
  append(L"b0");
                                                            #line 5735 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                print(rightBrace());
                                                                if (isJavascript())
                                                                {
                                                            #line 10096 "PrintCLike.cpp"
  append(L";");
                                                            #line 5739 "PrintCLike.cpp.template"
                                                                }
                                                            #line 10100 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5741 "PrintCLike.cpp.template"
                                                                openMethod(intType(), L"", L"getTokenEnd", L"", true);
                                                                print(leftBrace());
                                                            #line 10105 "PrintCLike.cpp"
  append(L"\n");
  append(L"  return ");
                                                            #line 5744 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 10110 "PrintCLike.cpp"
  append(L"e0");
                                                            #line 5745 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                print(rightBrace());
                                                                if (isJavascript())
                                                                {
                                                            #line 10117 "PrintCLike.cpp"
  append(L";");
                                                            #line 5749 "PrintCLike.cpp.template"
                                                                }
                                                            #line 10121 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5751 "PrintCLike.cpp.template"
                                                              }
                                                              if (isJavascript())
                                                              {
                                                                if (useGlr)
                                                                {
                                                            #line 10129 "PrintCLike.cpp"
  append(L"\n");
  append(L"this.reset = function");
                                                            #line 5757 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 10136 "PrintCLike.cpp"
  append(L"\n");
  append(L"function reset");
                                                            #line 5761 "PrintCLike.cpp.template"
                                                                }
                                                            #line 10141 "PrintCLike.cpp"
  append(L"(l, b, e)\n");
  append(L"{");
                                                            #line 5763 "PrintCLike.cpp.template"
                                                              }
                                                              else if (isTypescript())
                                                              {
                                                            #line 10148 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5767 "PrintCLike.cpp.template"
                                                                if (! performanceTest && ! useGlr)
                                                                {
                                                            #line 10153 "PrintCLike.cpp"
  append(L"private ");
                                                            #line 5769 "PrintCLike.cpp.template"
                                                                }
                                                            #line 10157 "PrintCLike.cpp"
  append(L"reset(l: number, b: number, e: number)\n");
  append(L"{");
                                                            #line 5771 "PrintCLike.cpp.template"
                                                              }
                                                              else if (isHaxe())
                                                              {
                                                            #line 10164 "PrintCLike.cpp"
  append(L"\n");
  append(L"public function reset(l, b, e)\n");
  append(L"{");
                                                            #line 5776 "PrintCLike.cpp.template"
                                                              }
                                                              else
                                                              {
                                                                openMethod(voidType(), isJava() ? L"final " : L"", L"reset", L"int l, int b, int e", false, useGlr ? L"ParsingThread" : className.c_str());
                                                                print(leftBrace());
                                                              }
                                                            #line 10175 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5783 "PrintCLike.cpp.template"
                                                              if (! isPython() && ! isScala())
                                                              {
                                                            #line 10181 "PrintCLike.cpp"
  append(L"        ");
                                                            #line 5785 "PrintCLike.cpp.template"
                                                                print(wcslen(thiz()), L" ");
                                                              }
                                                              print(thiz());
                                                            #line 10187 "PrintCLike.cpp"
  append(L"b0 = b; ");
                                                            #line 5788 "PrintCLike.cpp.template"
                                                              print(thiz());
                                                            #line 10191 "PrintCLike.cpp"
  append(L"e0 = b");
                                                            #line 5789 "PrintCLike.cpp.template"
                                                              print(semicolon());
                                                            #line 10195 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5791 "PrintCLike.cpp.template"
                                                              print(thiz());
                                                            #line 10200 "PrintCLike.cpp"
  append(L"l1 = l; ");
                                                            #line 5792 "PrintCLike.cpp.template"
                                                              print(thiz());
                                                            #line 10204 "PrintCLike.cpp"
  append(L"b1 = b; ");
                                                            #line 5793 "PrintCLike.cpp.template"
                                                              print(thiz());
                                                            #line 10208 "PrintCLike.cpp"
  append(L"e1 = e");
                                                            #line 5794 "PrintCLike.cpp.template"
                                                              print(semicolon());
                                                              for (size_t k = 2; k <= grammar->k; ++k)
                                                              {
                                                            #line 10214 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5798 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 10219 "PrintCLike.cpp"
  append(L"l");
                                                            #line 5799 "PrintCLike.cpp.template"
                                                                print(format.toString<wchar_t>(k));
                                                            #line 10223 "PrintCLike.cpp"
  append(L" = 0; ");
                                                            #line 5800 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 10227 "PrintCLike.cpp"
  append(L"b");
                                                            #line 5801 "PrintCLike.cpp.template"
                                                                print(format.toString<wchar_t>(k));
                                                            #line 10231 "PrintCLike.cpp"
  append(L" = 0; ");
                                                            #line 5802 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 10235 "PrintCLike.cpp"
  append(L"e");
                                                            #line 5803 "PrintCLike.cpp.template"
                                                                print(format.toString<wchar_t>(k));
                                                            #line 10239 "PrintCLike.cpp"
  append(L" = 0");
                                                            #line 5804 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                              }
                                                            #line 10244 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5807 "PrintCLike.cpp.template"
                                                              print(thiz());
                                                            #line 10249 "PrintCLike.cpp"
  append(L"end = e");
                                                            #line 5808 "PrintCLike.cpp.template"
                                                              print(semicolon());
                                                              if (hasBacktracking)
                                                              {
                                                            #line 10255 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5812 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 10260 "PrintCLike.cpp"
  append(L"ex = -1");
                                                            #line 5813 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                if (memoization)
                                                                {
                                                                  if (isJavascript() || isTypescript())
                                                                  {
                                                            #line 10268 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5819 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                            #line 10273 "PrintCLike.cpp"
  append(L"memo = {};");
                                                            #line 5820 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isCSharp())
                                                                  {
                                                            #line 10279 "PrintCLike.cpp"
  append(L"\n");
  append(L"  memo.Clear();");
                                                            #line 5824 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isScala())
                                                                  {
                                                            #line 10286 "PrintCLike.cpp"
  append(L"\n");
  append(L"  memo.clear");
                                                            #line 5828 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isHaxe())
                                                                  {
                                                            #line 10293 "PrintCLike.cpp"
  append(L"\n");
  append(L"  memo = new Map();");
                                                            #line 5832 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isGo())
                                                                  {
                                                            #line 10300 "PrintCLike.cpp"
  append(L"\n");
  append(L"  this.memo = make(map[int]int)");
                                                            #line 5836 "PrintCLike.cpp.template"
                                                                  }
                                                                  else if (isPython())
                                                                  {
                                                            #line 10307 "PrintCLike.cpp"
  append(L"\n");
  append(L"  self.memo = {}");
                                                            #line 5840 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 10314 "PrintCLike.cpp"
  append(L"\n");
  append(L"  memo.clear();");
                                                            #line 5844 "PrintCLike.cpp.template"
                                                                  }
                                                                }
                                                                if (grammar->noThrow)
                                                                {
                                                            #line 10322 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5849 "PrintCLike.cpp.template"
                                                                  print(thiz());
                                                            #line 10327 "PrintCLike.cpp"
  append(L"viable = ");
                                                            #line 5850 "PrintCLike.cpp.template"
                                                                  if (isPython())
                                                                  {
                                                            #line 10332 "PrintCLike.cpp"
  append(L"T");
                                                            #line 5852 "PrintCLike.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 10338 "PrintCLike.cpp"
  append(L"t");
                                                            #line 5855 "PrintCLike.cpp.template"
                                                                  }
                                                            #line 10342 "PrintCLike.cpp"
  append(L"rue");
                                                            #line 5856 "PrintCLike.cpp.template"
                                                                  print(semicolon());
                                                                }
                                                              }
                                                              if (tree && ! useGlr)
                                                              {
                                                            #line 10350 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5862 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 10355 "PrintCLike.cpp"
  append(L"eventHandler");
                                                            #line 5863 "PrintCLike.cpp.template"
                                                                print(arrow());
                                                                if (isGo())
                                                                {
                                                            #line 10361 "PrintCLike.cpp"
  append(L"R");
                                                            #line 5866 "PrintCLike.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 10367 "PrintCLike.cpp"
  append(L"r");
                                                            #line 5869 "PrintCLike.cpp.template"
                                                                }
                                                            #line 10371 "PrintCLike.cpp"
  append(L"eset(");
                                                            #line 5870 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 10375 "PrintCLike.cpp"
  append(L"input)");
                                                            #line 5871 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                              }
                                                              if (useGlr)
                                                              {
                                                            #line 10382 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5876 "PrintCLike.cpp.template"
                                                                if (isCSharp() || isCpp() || isHaxe() || isScala() || isTypescript() || isGo())
                                                                {
                                                                  print(thiz());
                                                            #line 10389 "PrintCLike.cpp"
  append(L"parser");
                                                            #line 5879 "PrintCLike.cpp.template"
                                                                  print(arrow());
                                                                }
                                                            #line 10394 "PrintCLike.cpp"
  append(L"maxId = 0");
                                                            #line 5881 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 10398 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 5883 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 10403 "PrintCLike.cpp"
  append(L"id = ");
                                                            #line 5884 "PrintCLike.cpp.template"
                                                                if (isCSharp() || isCpp() || isHaxe() || isScala() || isTypescript() || isGo())
                                                                {
                                                                  print(thiz());
                                                            #line 10409 "PrintCLike.cpp"
  append(L"parser");
                                                            #line 5887 "PrintCLike.cpp.template"
                                                                   print(arrow());
                                                                }
                                                            #line 10414 "PrintCLike.cpp"
  append(L"maxId");
                                                            #line 5889 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                              }
                                                              print(rightBrace());
                                                              if (isJavascript() && useGlr)
                                                              {
                                                            #line 10422 "PrintCLike.cpp"
  append(L";");
                                                            #line 5894 "PrintCLike.cpp.template"
                                                              }
                                                            #line 10426 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5896 "PrintCLike.cpp.template"
                                                              if (useGlr || isJavascript() || isTypescript() || isHaxe() || isGo() || isPython())
                                                              {
                                                              }
                                                              else
                                                              {
                                                                openMethod(voidType(), L"", L"reset", L"");
                                                                print(leftBrace());
                                                            #line 10436 "PrintCLike.cpp"
  append(L"\n");
  append(L"  reset(0, 0, 0)");
                                                            #line 5904 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                print(rightBrace());
                                                            #line 10442 "PrintCLike.cpp"
  append(L"\n");
                                                            #line 5907 "PrintCLike.cpp.template"
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
                                                            #line 10470 "PrintCLike.cpp"
  append(L"\n");
  append(L"if ");
                                                            #line 5933 "PrintCLike.cpp.template"
                                                                    print(ifLeftParen());
                                                            #line 10475 "PrintCLike.cpp"
  append(L"(");
                                                            #line 5934 "PrintCLike.cpp.template"
                                                                    print(thiz());
                                                                    print(token());
                                                            #line 10480 "PrintCLike.cpp"
  append(L" == ");
                                                            #line 5936 "PrintCLike.cpp.template"
                                                                    print(format.toString<wchar_t>(grammar->externalTokenCode[plusplus]));
                                                                    if (isPython())
                                                                    {
                                                            #line 10486 "PrintCLike.cpp"
  append(L" or ");
                                                            #line 5939 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 10492 "PrintCLike.cpp"
  append(L" || ");
                                                            #line 5942 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(thiz());
                                                                    print(token());
                                                            #line 10498 "PrintCLike.cpp"
  append(L" == ");
                                                            #line 5945 "PrintCLike.cpp.template"
                                                                    print(format.toString<wchar_t>(grammar->externalTokenCode[minusminus]));
                                                            #line 10502 "PrintCLike.cpp"
  append(L")");
                                                            #line 5947 "PrintCLike.cpp.template"
                                                                    if (isPython())
                                                                    {
                                                            #line 10507 "PrintCLike.cpp"
  append(L" and ");
                                                            #line 5949 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 10513 "PrintCLike.cpp"
  append(L" && ");
                                                            #line 5952 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(thiz());
                                                            #line 10518 "PrintCLike.cpp"
  append(L"followsLineTerminator");
                                                            #line 5954 "PrintCLike.cpp.template"
                                                                    if (! isScala())
                                                                    {
                                                            #line 10523 "PrintCLike.cpp"
  append(L"()");
                                                            #line 5956 "PrintCLike.cpp.template"
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
                                                            #line 10537 "PrintCLike.cpp"
  append(L"\n");
  append(L"if ");
                                                            #line 5968 "PrintCLike.cpp.template"
                                                                    print(ifLeftParen());
                                                                    print(thiz());
                                                                    print(token());
                                                            #line 10544 "PrintCLike.cpp"
  append(L" != ");
                                                            #line 5971 "PrintCLike.cpp.template"
                                                                    print(format.toString<wchar_t>(grammar->externalTokenCode[semicolonToken]));
                                                                    if (isPython())
                                                                    {
                                                            #line 10550 "PrintCLike.cpp"
  append(L" and ");
                                                            #line 5974 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 10556 "PrintCLike.cpp"
  append(L" && ");
                                                            #line 5977 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(thiz());
                                                                    print(token());
                                                            #line 10562 "PrintCLike.cpp"
  append(L" >= 0");
                                                            #line 5981 "PrintCLike.cpp.template"
                                                                    if (isPython())
                                                                    {
                                                            #line 10567 "PrintCLike.cpp"
  append(L" and ");
                                                            #line 5983 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 10573 "PrintCLike.cpp"
  append(L" && ");
                                                            #line 5986 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(thiz());
                                                            #line 10578 "PrintCLike.cpp"
  append(L"followsLineTerminator");
                                                            #line 5988 "PrintCLike.cpp.template"
                                                                    if (! isScala())
                                                                    {
                                                            #line 10583 "PrintCLike.cpp"
  append(L"()");
                                                            #line 5990 "PrintCLike.cpp.template"
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
                                                            #line 10598 "PrintCLike.cpp"
  append(L"\n");
  append(L"if ");
                                                            #line 6003 "PrintCLike.cpp.template"
                                                                    print(isPython() ? L"(" : ifLeftParen());
                                                                    print(thiz());
                                                                    print(token());
                                                            #line 10605 "PrintCLike.cpp"
  append(L" == ");
                                                            #line 6006 "PrintCLike.cpp.template"
                                                                    print(format.toString<wchar_t>(grammar->externalTokenCode[rbrace]));
                                                                    if (isPython())
                                                                    {
                                                            #line 10611 "PrintCLike.cpp"
  append(L" or");
                                                            #line 6009 "PrintCLike.cpp.template"
                                                                    }
                                                                    else if (isGo())
                                                                    {
                                                            #line 10617 "PrintCLike.cpp"
  append(L" ||");
                                                            #line 6012 "PrintCLike.cpp.template"
                                                                    }
                                                                    printCodeSequenceAnnotation(grammar->tokenSequence(rbrace));
                                                                    if (isGo() || isPython())
                                                                    {
                                                            #line 10624 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 6017 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 10631 "PrintCLike.cpp"
  append(L"\n");
  append(L" || ");
                                                            #line 6021 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(thiz());
                                                                    print(token());
                                                            #line 10638 "PrintCLike.cpp"
  append(L" == ");
                                                            #line 6024 "PrintCLike.cpp.template"
                                                                    print(format.toString<wchar_t>(grammar->externalTokenCode[eof]));
                                                                    if (isPython())
                                                                    {
                                                            #line 10644 "PrintCLike.cpp"
  append(L" or");
                                                            #line 6027 "PrintCLike.cpp.template"
                                                                    }
                                                                    else if (isGo())
                                                                    {
                                                            #line 10650 "PrintCLike.cpp"
  append(L" ||");
                                                            #line 6030 "PrintCLike.cpp.template"
                                                                    }
                                                                    printCodeSequenceAnnotation(grammar->tokenSequence(eof));
                                                                    if (isGo() || isPython())
                                                                    {
                                                            #line 10657 "PrintCLike.cpp"
  append(L"\n");
  append(L"    ");
                                                            #line 6035 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 10664 "PrintCLike.cpp"
  append(L"\n");
  append(L" || ");
                                                            #line 6039 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(thiz());
                                                                    print(token());
                                                            #line 10671 "PrintCLike.cpp"
  append(L" != ");
                                                            #line 6042 "PrintCLike.cpp.template"
                                                                    print(format.toString<wchar_t>(grammar->externalTokenCode[semicolonToken]));
                                                                    if (isPython())
                                                                    {
                                                            #line 10677 "PrintCLike.cpp"
  append(L" and ");
                                                            #line 6045 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 10683 "PrintCLike.cpp"
  append(L" && ");
                                                            #line 6048 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(thiz());
                                                                    print(token());
                                                            #line 10689 "PrintCLike.cpp"
  append(L" >= 0");
                                                            #line 6052 "PrintCLike.cpp.template"
                                                                    if (isPython())
                                                                    {
                                                            #line 10694 "PrintCLike.cpp"
  append(L" and ");
                                                            #line 6054 "PrintCLike.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 10700 "PrintCLike.cpp"
  append(L" && ");
                                                            #line 6057 "PrintCLike.cpp.template"
                                                                    }
                                                                    if (afterRbrace)
                                                                    {
                                                            #line 10706 "PrintCLike.cpp"
  append(L"(");
                                                            #line 6060 "PrintCLike.cpp.template"
                                                                    }
                                                                    print(thiz());
                                                            #line 10711 "PrintCLike.cpp"
  append(L"followsLineTerminator");
                                                            #line 6062 "PrintCLike.cpp.template"
                                                                    if (! isScala())
                                                                    {
                                                            #line 10716 "PrintCLike.cpp"
  append(L"()");
                                                            #line 6064 "PrintCLike.cpp.template"
                                                                    }
                                                                    if (afterRbrace)
                                                                    {
                                                                      if (isPython())
                                                                      {
                                                            #line 10724 "PrintCLike.cpp"
  append(L" || ");
                                                            #line 6069 "PrintCLike.cpp.template"
                                                                      }
                                                                      else
                                                                      {
                                                            #line 10730 "PrintCLike.cpp"
  append(L" or ");
                                                            #line 6072 "PrintCLike.cpp.template"
                                                                      }
                                                                      if (isCpp() || isCSharp() || isPython())
                                                                      {
                                                                        print(thiz());
                                                            #line 10737 "PrintCLike.cpp"
  append(L"input");
                                                            #line 6077 "PrintCLike.cpp.template"
                                                            
                                                            #line 10741 "PrintCLike.cpp"
  append(L"[");
                                                            #line 6077 "PrintCLike.cpp.template"
                                                                        print(thiz());
                                                            #line 10745 "PrintCLike.cpp"
  append(L"b0]");
                                                            #line 6078 "PrintCLike.cpp.template"
                                                                      }
                                                                      else
                                                                      {
                                                                        print(thiz());
                                                            #line 10752 "PrintCLike.cpp"
  append(L"input.char");
                                                            #line 6082 "PrintCLike.cpp.template"
                                                                        if (isTypescript() || isJavascript() || isHaxe())
                                                                        {
                                                            #line 10757 "PrintCLike.cpp"
  append(L"Code");
                                                            #line 6085 "PrintCLike.cpp.template"
                                                                        }
                                                            #line 10761 "PrintCLike.cpp"
  append(L"At(");
                                                            #line 6086 "PrintCLike.cpp.template"
                                                                       print(thiz());
                                                            #line 10765 "PrintCLike.cpp"
  append(L"b0)");
                                                            #line 6088 "PrintCLike.cpp.template"
                                                                      }
                                                            #line 10769 "PrintCLike.cpp"
  append(L" == 0x7D)");
                                                            #line 6089 "PrintCLike.cpp.template"
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
                                                            #line 10782 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 6100 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 10787 "PrintCLike.cpp"
  append(L"l1 = ");
                                                            #line 6101 "PrintCLike.cpp.template"
                                                                print(format.toString<wchar_t>(grammar->externalTokenCode[semicolonToken]));
                                                                print(semicolon());
                                                            #line 10792 "PrintCLike.cpp"
  append(L" ");
                                                            #line 6103 "PrintCLike.cpp.template"
                                                                printCodeSequenceAnnotation(grammar->tokenSequence(semicolonToken));
                                                            #line 10796 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 6105 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 10801 "PrintCLike.cpp"
  append(L"e1 = ");
                                                            #line 6106 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 10805 "PrintCLike.cpp"
  append(L"b1");
                                                            #line 6107 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                            #line 10809 "PrintCLike.cpp"
  append(L"\n");
  append(L"  ");
                                                            #line 6109 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 10814 "PrintCLike.cpp"
  append(L"end = ");
                                                            #line 6110 "PrintCLike.cpp.template"
                                                                print(thiz());
                                                            #line 10818 "PrintCLike.cpp"
  append(L"e1");
                                                            #line 6111 "PrintCLike.cpp.template"
                                                                print(semicolon());
                                                                print(rightBrace());
                                                              }
                                                            }

// End
