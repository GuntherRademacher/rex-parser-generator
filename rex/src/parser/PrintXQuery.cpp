// This file was generated on Sun Jan 26, 2025 19:55 (UTC+01) by REx v6.1 which is Copyright (c) 1979-2025 by Gunther Rademacher <grd@gmx.net>
// REx command line: PrintXQuery.cpp.template
                                                            #line 1 "PrintXQuery.cpp.template"
                                                            /*
                                                             * PrintXQuery.hpp
                                                             *
                                                             *  Created on: 31.07.2008
                                                             *      Author: Gunther
                                                             */

                                                            #include "../common/Memory.hpp"

                                                            #include "PrintXQuery.hpp"
                                                            #include "OrderedTokenSequenceVector.hpp"
                                                            #include "ItemSet.hpp"

                                                            #include "../common/PtrLess.hpp"
                                                            #include "../common/Format.hpp"
                                                            #include "../common/Encoder.hpp"
                                                            #include "../common/Math.hpp"

                                                            void PrintXQuery::printCodeSequenceAnnotation(const TokenSequenceSet &t)
                                                            {
                                                              const size_t align = 60;
                                                              lineBuffer += L" ";
                                                              print(lineBuffer.c_str());
                                                              size_t lsize = column();
                                                              size_t filler = lsize > align ? 0 : align - lsize;
                                                              int spaces = lsize + filler + 3;
                                                              size_t width = spaces > 120 ? 0 : 120 - spaces;
                                                              if (width < (120 - align) / 2) width = (120 - align) / 2;

                                                              WString annotation(t.toString(grammar, L"\n", L" |", width, 0, false, toBeEscaped));
                                                              invalidateCommentTokens(annotation);
                                                              wchar_t *indentedAnnotation = Format::reIndent(annotation.c_str(), Math::max(0, static_cast<int>(spaces) - getIndent()));
                                                              print(filler, L" ");
                                                            #line 38 "PrintXQuery.cpp"
  append(L"(: ");
                                                            #line 34 "PrintXQuery.cpp.template"
                                                              print(indentedAnnotation);
                                                            #line 42 "PrintXQuery.cpp"
  append(L" :)");
                                                            #line 35 "PrintXQuery.cpp.template"
                                                              free(indentedAnnotation);
                                                            }

                                                            bool PrintXQuery::printLookahead(size_t k,
                                                                                             const TokenSequenceSet &prefix,
                                                                                             size_t level,
                                                                                             const CompressedTokenSet *lookahead,
                                                                                             bool findsLookahead)
                                                            {
                                                              bool empty = true;
                                                              if (lookahead != 0 && ! lookahead->empty())
                                                              {
                                                                if (level > 1 || ! findsLookahead)
                                                                {
                                                                  empty = false;
                                                                  const wchar_t *lookaheadType;
                                                                  if (lookahead->hasImplicitWhitespace())
                                                                  {
                                                                    lookaheadType = L"W";
                                                                  }
                                                                  else
                                                                  {
                                                                    lookaheadType = L"";
                                                                  }

                                                                  lineBuffer.clear();
                                                                  lineBuffer += L"let $state := p:lookahead";
                                                                  lineBuffer += format.toString<wchar_t>(level);
                                                                  lineBuffer += lookaheadType;
                                                                  lineBuffer += L"(";
                                                                  lineBuffer += level == 1 || ! unlimitedLookahead ? L"" : format.toString<wchar_t>(lookahead->prefixCode(grammar->tokenSequenceFactory->tokenBits()));
                                                                  lineBuffer += level == 1 || ! unlimitedLookahead ? L"" : L", ";
                                                                  lineBuffer += grammar->singleLexer ? L"0" : format.toString<wchar_t>(lookahead->getSetNo(grammar->lookaheadSets));
                                                                  lineBuffer += L", $input, $state)";
                                                            #line 79 "PrintXQuery.cpp"
  append(L"\n");
                                                            #line 70 "PrintXQuery.cpp.template"
                                                                  printCodeSequenceAnnotation(lookahead->getInitials());
                                                                }

                                                                if (lookahead->getDpi() >= 0)
                                                                {
                                                                  empty = false;
                                                            #line 88 "PrintXQuery.cpp"
  append(L"\n");
  append(L"let $state := p:predict($input, $state, ");
                                                            #line 77 "PrintXQuery.cpp.template"
                                                                  print(format.toString<wchar_t>(lookahead->getDpi()));
                                                            #line 93 "PrintXQuery.cpp"
  append(L")");
                                                            #line 78 "PrintXQuery.cpp.template"
                                                                }
                                                                else if (level < k)
                                                                {
                                                                  // this block will be obsolete when "tables" proves to be successful

                                                                  const CompressedTokenSet::CompressedTokenSetByTokenSet &chol(lookahead->getCombinedHigherOrderLookahead());
                                                                  if (! chol.empty())
                                                                  {
                                                                    empty = false;
                                                                    ++level;
                                                            #line 106 "PrintXQuery.cpp"
  append(L"\n");
  append(L"let $state :=");
                                                            #line 89 "PrintXQuery.cpp.template"
                                                                    increaseIndent();
                                                                    OrderedTokenSequenceVector orderedPrefix(prefix, __FILE__, __LINE__);
                                                                    if (unlimitedLookahead)
                                                                    {
                                                                      const CompressedTokenSet::HigherOrderLookahead &hol(lookahead->getHigherOrderLookahead());
                                                                      const wchar_t *delimiter = L"";
                                                                      for (CompressedTokenSet::HigherOrderLookahead::const_iterator i(hol.begin());
                                                                           i != hol.end();
                                                                           ++i)
                                                                      {
                                                                        Token::Code token = i->first;
                                                                        for (OrderedTokenSequenceVector::const_iterator p = orderedPrefix.begin(); p != orderedPrefix.end(); ++p)
                                                                        {
                                                                          TokenSequence nextPrefix(grammar->tokenSequenceFactory->tokenSequence(*p, grammar->tokenSequence(token)));

                                                                          lineBuffer = delimiter;
                                                                          lineBuffer += L"if ($state[$p:l";
                                                                          lineBuffer += level == 2 ? L"1" : L"k";
                                                                          lineBuffer += L"] = ";
                                                                          lineBuffer += format.toString<wchar_t>(lookahead->localSequenceCode(grammar->tokenSequenceFactory, grammar->tokenSequence(token), grammar->externalTokenCode));
                                                                          lineBuffer += L") then";
                                                            #line 131 "PrintXQuery.cpp"
  append(L"\n");
                                                            #line 111 "PrintXQuery.cpp.template"
                                                                          printCodeSequenceAnnotation(nextPrefix);
                                                                          increaseIndent();

                                                                          TokenSequenceSet singleNextPrefixSet;
                                                                          singleNextPrefixSet.insert(nextPrefix);
                                                                          printLookahead(k, singleNextPrefixSet, level, i->second, findsLookahead);
                                                            #line 140 "PrintXQuery.cpp"
  append(L"\n");
  append(L"return $state");
                                                            #line 118 "PrintXQuery.cpp.template"
                                                                          decreaseIndent();
                                                                          delimiter = L"else ";
                                                                        }
                                                                      }
                                                                    }
                                                                    else
                                                                    {
                                                                      const CompressedTokenSet::CompressedTokenSetByTokenSet &chol = lookahead->getCombinedHigherOrderLookahead();
                                                                      const wchar_t *delimiter = L"";
                                                                      for (CompressedTokenSet::CompressedTokenSetByTokenSet::const_iterator i = chol.begin();
                                                                           i != chol.end();
                                                                           ++i)
                                                                      {
                                                                        const CompressedTokenSet *cts = i->second;
                                                                        TokenSequenceSet nextPrefixSet;
                                                                        const OrderedTokenSequenceVector &ots(i->first);
                                                                        TokenSequence nextPrefix(grammar->tokenSequenceFactory->emptySequence());
                                                                        size_t size = orderedPrefix.size() * ots.size();
                                                                        int seqNo = 0;
                                                                        for (OrderedTokenSequenceVector::const_iterator p = orderedPrefix.begin(); p != orderedPrefix.end(); ++p)
                                                                          for (OrderedTokenSequenceVector::const_iterator j = ots.begin(); j != ots.end(); ++j)
                                                                        {
                                                                          if (seqNo != 0)
                                                                          {
                                                                            lineBuffer += L",";
                                                            #line 169 "PrintXQuery.cpp"
  append(L"\n");
                                                            #line 144 "PrintXQuery.cpp.template"
                                                                            printCodeSequenceAnnotation(nextPrefix);
                                                                          }

                                                                          nextPrefix = grammar->tokenSequenceFactory->tokenSequence(*p, *j);
                                                                          nextPrefixSet.insert(nextPrefix);

                                                                          if (seqNo == 0)
                                                                          {
                                                                            lineBuffer = delimiter;
                                                                            lineBuffer += L"if ($state[$p:l";
                                                                            lineBuffer += level == 2 ? L"1" : L"k";
                                                                            lineBuffer += L"] ";
                                                                            lineBuffer += size == 1 ? L"eq " : L"= (";
                                                                          }
                                                                          else
                                                                          {
                                                                            lineBuffer.assign(wcslen(delimiter), L' ');
                                                                            lineBuffer += L"               ";
                                                                            lineBuffer += L"      ";
                                                                          }
                                                                          lineBuffer += format.toString<wchar_t>(CompressedTokenSet::uniqueSequenceCode(grammar->tokenSequenceFactory, nextPrefix, grammar->externalTokenCode));
                                                                          ++seqNo;
                                                                        }
                                                                        lineBuffer += size == 1 ? L"" : L")";
                                                                        lineBuffer += L") then";
                                                            #line 197 "PrintXQuery.cpp"
  append(L"\n");
                                                            #line 170 "PrintXQuery.cpp.template"
                                                                        printCodeSequenceAnnotation(nextPrefix);

                                                                        increaseIndent();
                                                                        printLookahead(k, nextPrefixSet, level, cts, findsLookahead);
                                                            #line 204 "PrintXQuery.cpp"
  append(L"\n");
  append(L"return $state");
                                                            #line 175 "PrintXQuery.cpp.template"
                                                                        decreaseIndent();
                                                                        delimiter = L"else ";
                                                                      }
                                                                    }
                                                                    --level;
                                                            #line 213 "PrintXQuery.cpp"
  append(L"\n");
  append(L"else");
                                                            #line 181 "PrintXQuery.cpp.template"
                                                                    increaseIndent();
                                                                    if (level == 1)
                                                                    {
                                                            #line 220 "PrintXQuery.cpp"
  append(L"\n");
  append(L"($state[$p:l1], subsequence($state, $p:lk + 1))");
                                                            #line 185 "PrintXQuery.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 227 "PrintXQuery.cpp"
  append(L"\n");
  append(L"$state");
                                                            #line 189 "PrintXQuery.cpp.template"
                                                                    }
                                                                    decreaseIndent(2);
                                                                  }
                                                                }
                                                              }
                                                              return ! empty;
                                                            }

                                                            void PrintXQuery::printMatch(const CompressedTokenSet *lookahead,
                                                                                         size_t k,
                                                                                         int backtrackedCaseId,
                                                                                         const TokenSequenceSet &ts,
                                                                                         MatchType matchType,
                                                                                         int caseId,
                                                                                         const wchar_t *prefix,
                                                                                         const wchar_t *suffix)
                                                            {
                                                              if (matchType == DEFAULT)
                                                              {
                                                            #line 250 "PrintXQuery.cpp"
  append(L"\n");
  append(L"else");
                                                            #line 209 "PrintXQuery.cpp.template"
                                                                return;
                                                              }
                                                              size_t prefixSize = wcslen(prefix);
                                                              if (prefixSize)
                                                              {
                                                                lineBuffer = prefix;
                                                              }

                                                              const wchar_t *comparison = matchType == IFNOT ? L" != " : L" = ";
                                                              const wchar_t *connector  = matchType == IFNOT ? L"and " : L" or ";

                                                              const TokenSequence *previousCodeSequence = 0;
                                                              const TokenSequence *codeSequence = 0;

                                                              const wchar_t *matchVariable = k == 0
                                                                                           ? L"$match[1]"
                                                                                           : k == 1 && backtrackedCaseId == 0 && (lookahead == 0 || lookahead->getDpi() < 0)
                                                                                           ? L"$state[$p:l1]"
                                                                                           : L"$state[$p:lk]";
                                                              bool first = true;

                                                              OrderedTokenSequenceVector v(ts, __FILE__, __LINE__);
                                                              for (OrderedTokenSequenceVector::const_iterator i = v.begin(); ; )
                                                              {
                                                                const wchar_t *matchCode;
                                                                if (backtrackedCaseId)
                                                                {
                                                                  matchCode = format.toString<wchar_t>(- backtrackedCaseId);
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
                                                                case CASE:
                                                                  if (! first)
                                                                  {
                                                                    if (previousCodeSequence)
                                                                    {
                                                            #line 313 "PrintXQuery.cpp"
  append(L"\n");
                                                            #line 269 "PrintXQuery.cpp.template"
                                                                      printCodeSequenceAnnotation(*previousCodeSequence);
                                                                    }
                                                                    else
                                                                    {
                                                            #line 320 "PrintXQuery.cpp"
  append(L"\n");
                                                            #line 274 "PrintXQuery.cpp.template"
                                                                      print(lineBuffer.c_str());
                                                                    }
                                                                    lineBuffer.assign(prefixSize - 4, L' ');
                                                                    lineBuffer += connector;
                                                                  }
                                                                  lineBuffer += matchVariable;
                                                                  lineBuffer += comparison;
                                                                  lineBuffer += matchCode;
                                                                  break;

                                                                default:
                                                                  break;
                                                                }
                                                                previousCodeSequence = codeSequence;
                                                                first = false;
                                                              }

                                                              if (! first && *suffix)
                                                              {
                                                                lineBuffer += suffix;
                                                                if (previousCodeSequence)
                                                                {
                                                            #line 345 "PrintXQuery.cpp"
  append(L"\n");
                                                            #line 297 "PrintXQuery.cpp.template"
                                                                  printCodeSequenceAnnotation(*previousCodeSequence);
                                                                }
                                                                else
                                                                {
                                                            #line 352 "PrintXQuery.cpp"
  append(L"\n");
                                                            #line 302 "PrintXQuery.cpp.template"
                                                                  print(lineBuffer.c_str());
                                                                }
                                                              }
                                                            }

                                                            void PrintXQuery::printConsume(Token::Code code)
                                                            {
                                                              lineBuffer = L"let $state := p:consume";
                                                              if (tree && methodPrefix == methodPrefixTry)
                                                              {
                                                                lineBuffer += L"T";
                                                                consumeMethods = 2;
                                                              }
                                                              lineBuffer += L"(";
                                                              lineBuffer += Format().toString<wchar_t>(grammar->externalTokenCode[code]);
                                                              lineBuffer += L", $input, $state)";
                                                            #line 371 "PrintXQuery.cpp"
  append(L"\n");
                                                            #line 319 "PrintXQuery.cpp.template"
                                                              printCodeSequenceAnnotation(grammar->tokenSequence(code));
                                                            }

                                                            void PrintXQuery::visitNodeList(Node *firstNode)
                                                            {
                                                              if (firstNode)
                                                              {
                                                                bool doIndent = firstNode->getParent() && ! firstNode->getParent()->isSequence();
                                                                if (doIndent) increaseIndent();
                                                                for (Node *node = firstNode; node; node = node->followingSibling)
                                                                {
                                                                  node->accept(*this);
                                                                }
                                                                if (doIndent) decreaseIndent();
                                                              }
                                                            }

                                                            void PrintXQuery::visitOptional(Optional *node)
                                                            {
                                                              printLookahead(node->k, *grammar->epsilon, 1, node->getLookahead(), node->findsLookahead);
                                                              automaticSemicolonInsertion(node);
                                                              printBacktracking(node,
                                                                                node->getLookahead(),
                                                                                node->conflictCaseId,
                                                                                node->conflictId,
                                                                                node->firstElementChild);
                                                            #line 400 "PrintXQuery.cpp"
  append(L"\n");
  append(L"let $state :=\n");
  append(L"  if ($state[$p:error]) then\n");
  append(L"    $state");
                                                            #line 348 "PrintXQuery.cpp.template"
                                                              increaseIndent();
                                                              MatchType matchType;
                                                              const TokenSequenceSet &match = node->firstElementChild->getMatch(matchType);
                                                              printMatch(node->getLookahead(),
                                                                         node->k,
                                                                           node->conflicts(node->k) == 0
                                                                         ? 0
                                                                         : matchType == IF
                                                                         ? 1
                                                                         : 2,
                                                                         match,
                                                                         matchType,
                                                                         1,
                                                                         L"else if (",
                                                                         L") then");
                                                              Visitor::visitNodeWithChildren(node);
                                                              decreaseIndent();
                                                            #line 423 "PrintXQuery.cpp"
  append(L"\n");
  append(L"    return $state\n");
  append(L"  else\n");
  append(L"    $state");
                                                            #line 368 "PrintXQuery.cpp.template"
                                                            }

                                                            void PrintXQuery::visitZeroOrMore(ZeroOrMore *node)
                                                            {
                                                            #line 433 "PrintXQuery.cpp"
  append(L"\n");
  append(L"let $state := p:");
                                                            #line 373 "PrintXQuery.cpp.template"
                                                              print(methodPrefix);
                                                            #line 438 "PrintXQuery.cpp"
  append(L"-");
                                                            #line 374 "PrintXQuery.cpp.template"
                                                              print(node->production->name);
                                                            #line 442 "PrintXQuery.cpp"
  append(L"-");
                                                            #line 375 "PrintXQuery.cpp.template"
                                                              print(format.toString<wchar_t>(node->loopId));
                                                            #line 446 "PrintXQuery.cpp"
  append(L"($input, $state)");
                                                            #line 376 "PrintXQuery.cpp.template"
                                                            }

                                                            void PrintXQuery::visitOneOrMore(OneOrMore *node)
                                                            {
                                                            #line 453 "PrintXQuery.cpp"
  append(L"\n");
  append(L"let $state := p:");
                                                            #line 381 "PrintXQuery.cpp.template"
                                                              print(methodPrefix);
                                                            #line 458 "PrintXQuery.cpp"
  append(L"-");
                                                            #line 382 "PrintXQuery.cpp.template"
                                                              print(node->production->name);
                                                            #line 462 "PrintXQuery.cpp"
  append(L"-");
                                                            #line 383 "PrintXQuery.cpp.template"
                                                              print(format.toString<wchar_t>(node->loopId));
                                                            #line 466 "PrintXQuery.cpp"
  append(L"($input, $state)");
                                                            #line 384 "PrintXQuery.cpp.template"
                                                            }

                                                            void PrintXQuery::printCase(const CompressedTokenSet *lookahead, size_t k, Node *c, const wchar_t *prefix)
                                                            {
                                                              Node *e = c->element();
                                                              MatchType matchType;
                                                              const TokenSequenceSet &match = e->getMatch(matchType);
                                                              printMatch(lookahead,
                                                                         k,
                                                                         0,
                                                                         match,
                                                                         matchType,
                                                                         e->caseId,
                                                                         prefix,
                                                                         L") then");
                                                              increaseIndent();
                                                              size_t outputSize1 = size();

                                                              c->accept(*this);

                                                              size_t outputSize2 = size();
                                                              if (outputSize1 != outputSize2)
                                                              {
                                                            #line 492 "PrintXQuery.cpp"
  append(L"\n");
  append(L"return $state");
                                                            #line 408 "PrintXQuery.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 499 "PrintXQuery.cpp"
  append(L"\n");
  append(L"$state");
                                                            #line 412 "PrintXQuery.cpp.template"
                                                              }
                                                              decreaseIndent();
                                                            }

                                                            bool PrintXQuery::printBacktracking(Node *node,
                                                                                                const CompressedTokenSet *lookahead,
                                                                                                int conflictCaseId,
                                                                                                int conflictId,
                                                                                                Node *predicate)
                                                            {
                                                              bool hasBacktracking = node->conflicts(node->k) != 0;
                                                              if (hasBacktracking)
                                                              {
                                                                NodeList cases(false);
                                                                cases.push_back(predicate);
                                                                cases.push_back(predicate);
                                                                hasBacktracking = printBacktracking(node,
                                                                                                    lookahead,
                                                                                                    conflictCaseId,
                                                                                                    conflictId,
                                                                                                    cases);

                                                              }
                                                              return hasBacktracking;
                                                            }

                                                            bool PrintXQuery::printBacktracking(Node *node,
                                                                                                const CompressedTokenSet *lookahead,
                                                                                                int conflictCaseId,
                                                                                                int conflictId,
                                                                                                const NodeList &cases)
                                                            {
                                                              bool hasBacktracking = node->conflicts(node->k) != 0;
                                                              if (hasBacktracking)
                                                              {
                                                            #line 538 "PrintXQuery.cpp"
  append(L"\n");
  append(L"let $state :=");
                                                            #line 448 "PrintXQuery.cpp.template"
                                                                increaseIndent();
                                                                MatchType conflictMatchType;
                                                                const TokenSequenceSet &conflictMatch = node->getConflictMatch(conflictMatchType);
                                                                if (! conflictMatch.empty())
                                                                {
                                                            #line 547 "PrintXQuery.cpp"
  append(L"\n");
  append(L"if ($state[$p:error]) then\n");
  append(L"  $state");
                                                            #line 456 "PrintXQuery.cpp.template"
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
                                                                             conflictCaseId,
                                                                             L"else if (",
                                                                             L") then");
                                                                  increaseIndent();
                                                                }
                                                            #line 567 "PrintXQuery.cpp"
  append(L"\n");
  append(L"let $state :=");
                                                            #line 472 "PrintXQuery.cpp.template"
                                                                if (memoization)
                                                                {
                                                            #line 573 "PrintXQuery.cpp"
  append(L" p:memoized($state, ");
                                                            #line 474 "PrintXQuery.cpp.template"
                                                                  print(format.toString<wchar_t>(conflictId));
                                                            #line 577 "PrintXQuery.cpp"
  append(L")\n");
  append(L"return\n");
  append(L"  if ($state[$p:lk] != 0) then\n");
  append(L"    $state\n");
  append(L"  else");
                                                            #line 479 "PrintXQuery.cpp.template"
                                                                  increaseIndent();
                                                                }
                                                                increaseIndent();
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
                                                                caseId = 0;
                                                                for (NodeList::const_iterator i = cases.begin(); i != cases.end(); ++i)
                                                                {
                                                                  Node *c = *i;
                                                                  ++caseId;
                                                                  if (caseId == lastConflictCaseId)
                                                                  {
                                                            #line 612 "PrintXQuery.cpp"
  append(L"\n");
  append(L"p:memoize($backtrack, $state, ");
                                                            #line 508 "PrintXQuery.cpp.template"
                                                                    print(format.toString<wchar_t>(conflictId));
                                                            #line 617 "PrintXQuery.cpp"
  append(L", $backtrack[$p:e0], -");
                                                            #line 509 "PrintXQuery.cpp.template"
                                                                    print(format.toString<wchar_t>(caseId));
                                                            #line 621 "PrintXQuery.cpp"
  append(L", -");
                                                            #line 510 "PrintXQuery.cpp.template"
                                                                    print(format.toString<wchar_t>(caseId));
                                                            #line 625 "PrintXQuery.cpp"
  append(L")");
                                                            #line 511 "PrintXQuery.cpp.template"
                                                                  }
                                                                  else if (c->involvedInConflict)
                                                                  {
                                                                    if (caseId == firstConflictCaseId)
                                                                    {
                                                            #line 633 "PrintXQuery.cpp"
  append(L"\n");
  append(L"let $backtrack := $state\n");
  append(L"let $state := p:strip-result($state)");
                                                            #line 518 "PrintXQuery.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 641 "PrintXQuery.cpp"
  append(L"\n");
  append(L"let $state := p:restore($backtrack, $state)");
                                                            #line 522 "PrintXQuery.cpp.template"
                                                                      restoreCalled = true;
                                                                    }
                                                                    const wchar_t *v = variant;
                                                                    const wchar_t *m = methodPrefix;
                                                                    variant = L"";
                                                                    methodPrefix = methodPrefixTry;
                                                                    if (node->isChoice())
                                                                    {
                                                                      c->accept(*this);
                                                                    }
                                                                    else
                                                                    {
                                                                      decreaseIndent();
                                                                      visitNodeList(c);
                                                                      increaseIndent();
                                                                    }
                                                                    variant = v;
                                                                    methodPrefix = m;
                                                            #line 663 "PrintXQuery.cpp"
  append(L"\n");
  append(L"return\n");
  append(L"  if (not($state[$p:error])) then");
                                                            #line 542 "PrintXQuery.cpp.template"
                                                                    if (nestedTry && (node->isZeroOrMore() || node->isOneOrMore()))
                                                                    {
                                                            #line 670 "PrintXQuery.cpp"
  append(L"\n");
  append(L"    p:memoize($state, $state, ");
                                                            #line 545 "PrintXQuery.cpp.template"
                                                                      print(format.toString<wchar_t>(conflictId));
                                                            #line 675 "PrintXQuery.cpp"
  append(L", $backtrack[$p:e0], -");
                                                            #line 546 "PrintXQuery.cpp.template"
                                                                      print(format.toString<wchar_t>(caseId));
                                                            #line 679 "PrintXQuery.cpp"
  append(L", -3)");
                                                            #line 547 "PrintXQuery.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 685 "PrintXQuery.cpp"
  append(L"\n");
  append(L"    p:memoize($backtrack, $state, ");
                                                            #line 551 "PrintXQuery.cpp.template"
                                                                      print(format.toString<wchar_t>(conflictId));
                                                            #line 690 "PrintXQuery.cpp"
  append(L", $backtrack[$p:e0], -");
                                                            #line 552 "PrintXQuery.cpp.template"
                                                                      print(format.toString<wchar_t>(caseId));
                                                            #line 694 "PrintXQuery.cpp"
  append(L", -");
                                                            #line 553 "PrintXQuery.cpp.template"
                                                                      print(format.toString<wchar_t>(caseId));
                                                            #line 698 "PrintXQuery.cpp"
  append(L")");
                                                            #line 554 "PrintXQuery.cpp.template"
                                                                    }
                                                            #line 702 "PrintXQuery.cpp"
  append(L"\n");
  append(L"  else");
                                                            #line 556 "PrintXQuery.cpp.template"
                                                                    increaseIndent(2);
                                                                  }
                                                                }
                                                                caseId = 0;
                                                                for (NodeList::const_iterator i = cases.begin(); i != cases.end(); ++i)
                                                                {
                                                                  Node *c = *i;
                                                                  ++caseId;
                                                                  if (c->involvedInConflict && caseId != lastConflictCaseId)
                                                                  {
                                                                    decreaseIndent(2);
                                                                  }
                                                                }
                                                                decreaseIndent();
                                                                if (memoization)
                                                                {
                                                                  decreaseIndent();
                                                                }
                                                                if (! conflictMatch.empty())
                                                                {
                                                                  decreaseIndent();
                                                            #line 727 "PrintXQuery.cpp"
  append(L"\n");
  append(L"else");
                                                            #line 578 "PrintXQuery.cpp.template"
                                                                  if (node->k > 1)
                                                                  {
                                                            #line 733 "PrintXQuery.cpp"
  append(L"\n");
  append(L"  $state");
                                                            #line 581 "PrintXQuery.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 740 "PrintXQuery.cpp"
  append(L"\n");
  append(L"  ($state[$p:l1], subsequence($state, $p:lk + 1))");
                                                            #line 585 "PrintXQuery.cpp.template"
                                                                  }
                                                                }
                                                                decreaseIndent();
                                                              }
                                                              return hasBacktracking;
                                                            }

                                                            void PrintXQuery::visitChoice(Choice *node)
                                                            {
                                                              printLookahead(node->k, *grammar->epsilon, 1, node->getLookahead(), node->findsLookahead);
                                                              automaticSemicolonInsertion(node);
                                                              printBacktracking(node,
                                                                                node->getLookahead(),
                                                                                node->conflictCaseId,
                                                                                node->conflictId,
                                                                                node->cases);
                                                            #line 760 "PrintXQuery.cpp"
  append(L"\n");
  append(L"let $state :=\n");
  append(L"  if ($state[$p:error]) then\n");
  append(L"    $state");
                                                            #line 604 "PrintXQuery.cpp.template"
                                                              increaseIndent();
                                                              Node *defaultCase = 0;
                                                              const wchar_t *prefix = L"else if (";
                                                              size_t caseId = 0;
                                                              for (NodeList::iterator i = node->cases.begin(); i != node->cases.end(); ++i)
                                                              {
                                                                Node *c = *i;
                                                                ++caseId;
                                                                MatchType matchType;
                                                                const TokenSequenceSet &match = c->element()->getMatch(matchType);
                                                                if (matchType == DEFAULT)
                                                                {
                                                                  defaultCase = c;
                                                                }
                                                                else
                                                                {
                                                                  if (c->involvedInConflict)
                                                                  {
                                                            #line 784 "PrintXQuery.cpp"
  append(L"\n");
                                                            #line 623 "PrintXQuery.cpp.template"
                                                                    print(prefix);
                                                                    prefix = L" or ";
                                                            #line 789 "PrintXQuery.cpp"
  append(L"$state[$p:lk] = -");
                                                            #line 625 "PrintXQuery.cpp.template"
                                                                    print(format.toString<wchar_t>(caseId));
                                                                    if (match.empty())
                                                                    {
                                                            #line 795 "PrintXQuery.cpp"
  append(L") then");
                                                            #line 628 "PrintXQuery.cpp.template"
                                                                    }
                                                                  }
                                                                  printCase(node->getLookahead(), node->k, c, prefix);
                                                                  prefix = L"else if (";
                                                                }
                                                              }
                                                              printCase(node->getLookahead(), node->k, defaultCase, L"");
                                                              decreaseIndent();
                                                            }

                                                            void PrintXQuery::visitProduction(Production *node)
                                                            {
                                                              setIndent(0);
                                                            #line 811 "PrintXQuery.cpp"
  append(L"\n");
  append(L"(:");
  append(L"~");
  append(L"\n");
  append(L" : ");
                                                            #line 643 "PrintXQuery.cpp.template"
                                                              if (methodPrefix != methodPrefixTry)
                                                              {
                                                            #line 820 "PrintXQuery.cpp"
  append(L"Parse");
                                                            #line 645 "PrintXQuery.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 826 "PrintXQuery.cpp"
  append(L"Try parsing");
                                                            #line 648 "PrintXQuery.cpp.template"
                                                              }
                                                            #line 830 "PrintXQuery.cpp"
  append(L" ");
                                                            #line 649 "PrintXQuery.cpp.template"
                                                              print(node->name);
                                                            #line 834 "PrintXQuery.cpp"
  append(L".\n");
  append(L" :\n");
  append(L" : @param $input the input string.\n");
  append(L" : @param $state lexer state, error indicator, and result stack.\n");
  append(L" : @return the updated state.\n");
  append(L" :)\n");
  append(L"declare function p:");
                                                            #line 656 "PrintXQuery.cpp.template"
                                                              print(methodPrefix);
                                                            #line 844 "PrintXQuery.cpp"
  append(L"-");
                                                            #line 657 "PrintXQuery.cpp.template"
                                                              print(node->name);
                                                            #line 848 "PrintXQuery.cpp"
  append(L"($input as xs:string, $state as item()+) as item()+\n");
  append(L"{");
                                                            #line 659 "PrintXQuery.cpp.template"
                                                              if (debug)
                                                              {
                                                            #line 854 "PrintXQuery.cpp"
  append(L"\n");
  append(L"  debug:enter('");
                                                            #line 662 "PrintXQuery.cpp.template"
                                                                print(methodPrefix);
                                                            #line 859 "PrintXQuery.cpp"
  append(L"-");
                                                            #line 663 "PrintXQuery.cpp.template"
                                                                print(node->name);
                                                            #line 863 "PrintXQuery.cpp"
  append(L"', $state),");
                                                            #line 664 "PrintXQuery.cpp.template"
                                                              }
                                                              if (trace)
                                                              {
                                                            #line 869 "PrintXQuery.cpp"
  append(L"\n");
  append(L"  p:trace-nonterminal($state, \"");
                                                            #line 668 "PrintXQuery.cpp.template"
                                                                print(methodPrefix);
                                                            #line 874 "PrintXQuery.cpp"
  append(L"\", \"start\", \"");
                                                            #line 669 "PrintXQuery.cpp.template"
                                                                print(node->name);
                                                            #line 878 "PrintXQuery.cpp"
  append(L"\"),\n");
  append(L"  let $state :=");
                                                            #line 671 "PrintXQuery.cpp.template"
                                                                increaseIndent();
                                                              }
                                                              if (tree && methodPrefix != methodPrefixTry)
                                                              {
                                                            #line 886 "PrintXQuery.cpp"
  append(L"\n");
  append(L"  let $count := count($state)");
                                                            #line 676 "PrintXQuery.cpp.template"
                                                                if (! noPosition)
                                                                {
                                                            #line 892 "PrintXQuery.cpp"
  append(L"\n");
  append(L"  let $begin := $state[$p:e0]");
                                                            #line 679 "PrintXQuery.cpp.template"
                                                                }
                                                              }
                                                              visitNodeList(node->firstChild);
                                                              if (tree && methodPrefix != methodPrefixTry)
                                                              {
                                                                if (! noPosition)
                                                                {
                                                            #line 903 "PrintXQuery.cpp"
  append(L"\n");
  append(L"  let $end := $state[$p:e0]");
                                                            #line 687 "PrintXQuery.cpp.template"
                                                                }
                                                                if (debug)
                                                                {
                                                            #line 910 "PrintXQuery.cpp"
  append(L"\n");
  append(L"  let $state := ");
                                                            #line 691 "PrintXQuery.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 917 "PrintXQuery.cpp"
  append(L"\n");
  append(L"  return ");
                                                            #line 695 "PrintXQuery.cpp.template"
                                                                }
                                                            #line 922 "PrintXQuery.cpp"
  append(L"p:reduce($state, \"");
                                                            #line 697 "PrintXQuery.cpp.template"
                                                                print(node->name);
                                                            #line 926 "PrintXQuery.cpp"
  append(L"\", $count");
                                                            #line 698 "PrintXQuery.cpp.template"
                                                                if (! noPosition)
                                                                {
                                                            #line 931 "PrintXQuery.cpp"
  append(L", $begin, $end");
                                                            #line 700 "PrintXQuery.cpp.template"
                                                                }
                                                            #line 935 "PrintXQuery.cpp"
  append(L")");
                                                            #line 701 "PrintXQuery.cpp.template"
                                                                if (debug)
                                                                {
                                                            #line 940 "PrintXQuery.cpp"
  append(L"\n");
  append(L"  return ($state, debug:leave('");
                                                            #line 704 "PrintXQuery.cpp.template"
                                                                  print(methodPrefix);
                                                            #line 945 "PrintXQuery.cpp"
  append(L"-");
                                                            #line 705 "PrintXQuery.cpp.template"
                                                                  print(node->name);
                                                            #line 949 "PrintXQuery.cpp"
  append(L"', $state))");
                                                            #line 706 "PrintXQuery.cpp.template"
                                                                }
                                                              }
                                                              else if (debug)
                                                              {
                                                            #line 956 "PrintXQuery.cpp"
  append(L"\n");
  append(L"  return ($state, debug:leave('");
                                                            #line 711 "PrintXQuery.cpp.template"
                                                                print(methodPrefix);
                                                            #line 961 "PrintXQuery.cpp"
  append(L"-");
                                                            #line 712 "PrintXQuery.cpp.template"
                                                                print(node->name);
                                                            #line 965 "PrintXQuery.cpp"
  append(L"', $state))");
                                                            #line 713 "PrintXQuery.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 971 "PrintXQuery.cpp"
  append(L"\n");
  append(L"  return $state");
                                                            #line 717 "PrintXQuery.cpp.template"
                                                              }
                                                              if (trace)
                                                              {
                                                            #line 978 "PrintXQuery.cpp"
  append(L"\n");
  append(L"return\n");
  append(L"(\n");
  append(L"  p:trace-nonterminal($state, \"");
                                                            #line 723 "PrintXQuery.cpp.template"
                                                                print(methodPrefix);
                                                            #line 985 "PrintXQuery.cpp"
  append(L"\", \"end\", \"");
                                                            #line 724 "PrintXQuery.cpp.template"
                                                                print(node->name);
                                                            #line 989 "PrintXQuery.cpp"
  append(L"\"),\n");
  append(L"  $state\n");
  append(L")");
                                                            #line 728 "PrintXQuery.cpp.template"
                                                                decreaseIndent();
                                                              }
                                                            #line 996 "PrintXQuery.cpp"
  append(L"\n");
  append(L"};\n");
                                                            #line 732 "PrintXQuery.cpp.template"
                                                            }

                                                            void PrintXQuery::visitRef(Ref *node)
                                                            {
                                                              printLookahead(1, *grammar->epsilon, 1, node->getLookahead(), node->findsLookahead);
                                                              automaticSemicolonInsertion(node);
                                                              if (node->lexical)
                                                              {
                                                                printConsume(node->lexical->tokenCode);
                                                              }
                                                              else
                                                              {
                                                                if (   node->whitespaceAllowance == IMPLICIT
                                                                    && tree
                                                                    && methodPrefix != methodPrefixTry)
                                                                {
                                                            #line 1016 "PrintXQuery.cpp"
  append(L"\n");
  append(L"let $state := p:whitespace($input, $state)");
                                                            #line 749 "PrintXQuery.cpp.template"
                                                                  whitespaceCalled = true;
                                                                }
                                                            #line 1022 "PrintXQuery.cpp"
  append(L"\n");
  append(L"let $state :=\n");
  append(L"  if ($state[$p:error]) then\n");
  append(L"    $state\n");
  append(L"  else\n");
  append(L"    p:");
                                                            #line 756 "PrintXQuery.cpp.template"
                                                                print(methodPrefix);
                                                            #line 1031 "PrintXQuery.cpp"
  append(L"-");
                                                            #line 757 "PrintXQuery.cpp.template"
                                                                print(node->name);
                                                            #line 1035 "PrintXQuery.cpp"
  append(L"($input, $state)");
                                                            #line 758 "PrintXQuery.cpp.template"
                                                              }
                                                            }

                                                            void PrintXQuery::visitString(String *node)
                                                            {
                                                              printLookahead(1, *grammar->epsilon, 1, node->getLookahead(), node->findsLookahead);
                                                              automaticSemicolonInsertion(node);
                                                              printConsume(node->lexical->tokenCode);
                                                            }

                                                            void PrintXQuery::visitProcessingInstruction(ProcessingInstruction *node)
                                                            {
                                                              int spaces = Math::max(0, static_cast<int>(piIndent) - getIndent());
                                                              if (variant != 0 && wcscmp(node->target, variant) == 0)
                                                              {
                                                            #line 1053 "PrintXQuery.cpp"
  append(L"\n");
                                                            #line 774 "PrintXQuery.cpp.template"
                                                                print(spaces, L" ");
                                                            #line 1057 "PrintXQuery.cpp"
  append(L"(: line ");
                                                            #line 775 "PrintXQuery.cpp.template"
                                                                print(format.toString<wchar_t>(node->line));
                                                            #line 1061 "PrintXQuery.cpp"
  append(L" \"");
                                                            #line 776 "PrintXQuery.cpp.template"
                                                                print(node->fileName);
                                                            #line 1065 "PrintXQuery.cpp"
  append(L"\" :)\n");
                                                            #line 778 "PrintXQuery.cpp.template"
                                                                print(spaces, L" ");
                                                                wchar_t *reIndented = Format::reIndent(node->content, spaces);
                                                                print(reIndented);
                                                                free(reIndented);
                                                            #line 1072 "PrintXQuery.cpp"
  append(L"\n");
                                                            #line 783 "PrintXQuery.cpp.template"
                                                                print(spaces, L" ");
                                                            #line 1076 "PrintXQuery.cpp"
  append(L"(: line ");
                                                            #line 784 "PrintXQuery.cpp.template"
                                                                print(format.toString<wchar_t>(lineNo + 1));
                                                            #line 1080 "PrintXQuery.cpp"
  append(L" \"");
                                                            #line 785 "PrintXQuery.cpp.template"
                                                                print(wFileName);
                                                            #line 1084 "PrintXQuery.cpp"
  append(L"\" :)");
                                                            #line 786 "PrintXQuery.cpp.template"
                                                              }
                                                            }

                                                            void PrintXQuery::printUtilities()
                                                            {
                                                              if (isLrParser)
                                                              {
                                                                if (grammar->states->hasLookback)
                                                                {
                                                            #line 1096 "PrintXQuery.cpp"
  append(L"\n");
  append(L"(:");
  append(L"~");
  append(L"\n");
  append(L" : Compare a lookback code to a sorted, zero-terminated list of pairs at\n");
  append(L" : the given index into the LOOKBACK table. A matching first code in a\n");
  append(L" : pair will cause its second code to be returned. The list is sorted in\n");
  append(L" : descending order of first codes, so it is safe to stop when the first\n");
  append(L" : code is less than what is searched for.\n");
  append(L" :\n");
  append(L" : @param $x the lookback code to search for.\n");
  append(L" : @param $i the index into the LOOKBACK table.\n");
  append(L" : @return the new lookback code as the second code from a pair with a\n");
  append(L" : matching first code.\n");
  append(L" :)\n");
  append(L"declare function p:lookback($x as xs:integer, $i as xs:integer)\n");
  append(L"{\n");
  append(L"  let $l := $p:LOOKBACK[$i + 1]\n");
  append(L"  return\n");
  append(L"    if ($l gt $x) then\n");
  append(L"      p:lookback($x, $i + 2)\n");
  append(L"    else if ($l eq $x) then\n");
  append(L"      $p:LOOKBACK[$i + 2]\n");
  append(L"    else\n");
  append(L"      0\n");
  append(L"};\n");
  append(L"\n");
  append(L"(:");
  append(L"~");
  append(L"\n");
  append(L" : Calculate number of symbols to remove from LR stack for reduction by\n");
  append(L" : walking through lookback codes of reduction and stack entries. A single\n");
  append(L" : invocation combines two of those, more are handled in tail recursion.\n");
  append(L" :\n");
  append(L" : @param $code the reduction lookback code.\n");
  append(L" : @param $count the initial count value.\n");
  append(L" : @param $stack the LR stack.\n");
  append(L" : @param $t the stack running index.\n");
  append(L" : @return the initial count value, increased by the number of calculations\n");
  append(L" : yielding a non-zero lookback code.\n");
  append(L" :)\n");
  append(L"declare function p:count($code as xs:integer, $count as xs:integer, $stack as xs:integer*, $t as xs:integer)\n");
  append(L"{\n");
  append(L"  if ($stack[$t] lt 0) then\n");
  append(L"    $count\n");
  append(L"  else\n");
  append(L"    let $code := p:lookback($stack[$t + 1], $p:LOOKBACK[$code + 1])\n");
  append(L"    return\n");
  append(L"      if ($code eq 0) then\n");
  append(L"        $count\n");
  append(L"      else\n");
  append(L"        p:count($code, $count + 1, $stack, $t - 3)\n");
  append(L"};\n");
                                                            #line 844 "PrintXQuery.cpp.template"
                                                                }
                                                                if (grammar->useGlr)
                                                                {
                                                            #line 1154 "PrintXQuery.cpp"
  append(L"\n");
  append(L"(:");
  append(L"~");
  append(L"\n");
  append(L" : Determine index of the next thread that must be parsed, by comparing\n");
  append(L" : threads in $threads starting at $i with the candidate at $thread.\n");
  append(L" :\n");
  append(L" : @param $threads the sequence of all current threads.\n");
  append(L" : @param $thread the index of the next thread candidate.\n");
  append(L" : @param $i the index where to start searching.\n");
  append(L" : @return the index of the next thread.\n");
  append(L" :)\n");
  append(L"declare function p:next-thread($threads as map(*)*, $thread as xs:integer, $i as xs:integer)\n");
  append(L"{\n");
  append(L"  if ($i gt count($threads)) then\n");
  append(L"    $thread\n");
  append(L"  else\n");
  append(L"    let $thread :=\n");
  append(L"      if ($threads[$thread]?accepted ne $threads[$i]?accepted) then\n");
  append(L"        if ($threads[$thread]?accepted) then $i else $thread\n");
  append(L"      else\n");
  append(L"        let $comp := $threads[$thread]?lexer-state[$p:e0] - $threads[$i]?lexer-state[$p:e0]\n");
  append(L"        return\n");
  append(L"          if ($comp ne 0) then\n");
  append(L"            if ($comp lt 0) then $thread else $i\n");
  append(L"          else\n");
  append(L"            let $comp := $threads[$thread]?id - $threads[$i]?id\n");
  append(L"            return if ($comp le 0) then $thread else $i\n");
  append(L"    return p:next-thread($threads, $thread, $i + 1)\n");
  append(L"};\n");
  append(L"\n");
  append(L"(:");
  append(L"~");
  append(L"\n");
  append(L" : Compare two parsing threads for equality. A result of false indicates an\n");
  append(L" : ambiguity.\n");
  append(L" :\n");
  append(L" : @param $t1 the first thread data.\n");
  append(L" : @param $t2 the second thread data.\n");
  append(L" : @return true(), if threads are equal.\n");
  append(L" :)\n");
  append(L"declare function p:thread-equals($t1 as map(*), $t2 as map(*)) as xs:boolean\n");
  append(L"{\n");
  append(L"  if ($t1?accepted ne $t2?accepted) then false() else\n");
  append(L"  if ($t1?lexer-state[$p:b1] ne $t2?lexer-state[$p:b1]) then false() else\n");
  append(L"  if ($t1?lexer-state[$p:e1] ne $t2?lexer-state[$p:e1]) then false() else\n");
  append(L"  if ($t1?lexer-state[$p:l1] ne $t2?lexer-state[$p:l1]) then false() else\n");
  append(L"  if ($t1?state ne $t2?state) then false() else\n");
  append(L"  if ($t1?action ne $t2?action) then false() else deep-equal($t1?stack, $t2?stack)\n");
  append(L"};\n");
  append(L"\n");
  append(L"(:");
  append(L"~");
  append(L"\n");
  append(L" : Perform GLR parsing by selecting a thread and invoke the LR parse function\n");
  append(L" : on it for a single token. Process result with respect to thread management.\n");
  append(L" :\n");
  append(L" : @param $input the input string.\n");
  append(L" : @param $target the target symbol code.\n");
  append(L" : @param $max-id the maximum thread id.\n");
  append(L" : @param $threads the sequence of all current threads.\n");
  append(L" : @return the lexer state of the accepting (or error) thread.\n");
  append(L" :)\n");
  append(L"declare function p:parse-glr($input as xs:string,\n");
  append(L"                             $target as xs:integer,\n");
  append(L"                             $max-id as xs:integer,\n");
  append(L"                             $threads as map(*)+)\n");
  append(L"{\n");
  append(L"  let $i := p:next-thread($threads, 1, 2)\n");
  append(L"  let $thread := $threads[$i]\n");
  append(L"  let $lexer-state := $thread?lexer-state\n");
  append(L"  return\n");
  append(L"    if ($thread?accepted) then\n");
  append(L"      let $max-e0 := max($threads!?lexer-state[$p:e0])\n");
  append(L"      let $longest-accept := $threads[?lexer-state[$p:e0] eq $max-e0]\n");
  append(L"      return\n");
  append(L"        if (count($longest-accept) eq 1) then\n");
  append(L"          $longest-accept?lexer-state\n");
  append(L"        else\n");
  append(L"          p:reject-ambiguity($longest-accept[1]");
                                                            #line 920 "PrintXQuery.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 1238 "PrintXQuery.cpp"
  append(L", $longest-accept[2]");
                                                            #line 923 "PrintXQuery.cpp.template"
                                                                }
                                                            #line 1242 "PrintXQuery.cpp"
  append(L")\n");
  append(L"    else\n");
  append(L"      let $threads := (subsequence($threads, 1, $i - 1), subsequence($threads, $i + 1))\n");
  append(L"      let $other := if (exists($threads)) then $threads[p:next-thread($threads, 1, 2)] else ()\n");
  append(L"      return\n");
  append(L"        if (exists($other) and p:thread-equals($thread, $other)) then\n");
  append(L"          p:reject-ambiguity($thread");
                                                            #line 930 "PrintXQuery.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 1253 "PrintXQuery.cpp"
  append(L", $other");
                                                            #line 932 "PrintXQuery.cpp.template"
                                                                }
                                                            #line 1257 "PrintXQuery.cpp"
  append(L")\n");
  append(L"        else\n");
  append(L"          let $thread := p:parse($input, $target, $max-id, $thread)\n");
  append(L"          let $lexer-state := $thread?lexer-state\n");
  append(L"          return\n");
  append(L"            if (count($thread) gt 1) then\n");
  append(L"              p:parse-glr($input, $target, $max-id + 1, ($threads, $thread))\n");
  append(L"            else if (not($lexer-state[$p:error])) then\n");
  append(L"              p:parse-glr($input, $target, $max-id, ($threads, $thread))\n");
  append(L"            else if (exists($threads)) then\n");
  append(L"              p:parse-glr($input, $target, $max-id, $threads)\n");
  append(L"            else\n");
  append(L"              $lexer-state\n");
  append(L"};\n");
  append(L"\n");
  append(L"(:");
  append(L"~");
  append(L"\n");
  append(L" : Raise an error for ambiguous input.\n");
  append(L" :\n");
  append(L" : @param $thread the parsing thread data.");
                                                            #line 951 "PrintXQuery.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 1282 "PrintXQuery.cpp"
  append(L"\n");
  append(L" : @param $other the parsing thread data of the other thread.");
                                                            #line 954 "PrintXQuery.cpp.template"
                                                                }
                                                            #line 1287 "PrintXQuery.cpp"
  append(L"\n");
  append(L" : @return a lexer state containing an error element describing the ambiguity.\n");
  append(L" :)\n");
  append(L"declare function p:reject-ambiguity($thread as map(*)");
                                                            #line 958 "PrintXQuery.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 1295 "PrintXQuery.cpp"
  append(L", $other as map(*)");
                                                            #line 961 "PrintXQuery.cpp.template"
                                                                }
                                                            #line 1299 "PrintXQuery.cpp"
  append(L") as item()+\n");
  append(L"{\n");
  append(L"  let $lexer-state := $thread?lexer-state\n");
  append(L"  return\n");
  append(L"  (\n");
  append(L"    subsequence($lexer-state, 1, $p:error - 1),\n");
  append(L"    element error\n");
  append(L"    {\n");
  append(L"      attribute b {$thread?stack[last() - 2]},\n");
  append(L"      attribute e {$lexer-state[$p:e0]},\n");
  append(L"      attribute ambiguous-input {true()}");
                                                            #line 972 "PrintXQuery.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 1314 "PrintXQuery.cpp"
  append(L",\n");
  append(L"      let $first-tree := $lexer-state[last()]\n");
  append(L"      let $second-tree := $other?lexer-state[last()]\n");
  append(L"      return\n");
  append(L"        <AMBIGUOUS>\n");
  append(L"          <ALTERNATIVE>{p:rewrite-ambiguity($first-tree, $second-tree, true())}</ALTERNATIVE>\n");
  append(L"          <ALTERNATIVE>{p:rewrite-ambiguity($second-tree, $first-tree, true())}</ALTERNATIVE>\n");
  append(L"        </AMBIGUOUS>");
                                                            #line 981 "PrintXQuery.cpp.template"
                                                                }
                                                            #line 1325 "PrintXQuery.cpp"
  append(L"\n");
  append(L"    },\n");
  append(L"    subsequence($lexer-state, $p:error + 1)\n");
  append(L"  )\n");
  append(L"};\n");
                                                            #line 987 "PrintXQuery.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 1334 "PrintXQuery.cpp"
  append(L"\n");
  append(L"(:");
  append(L"~");
  append(L"\n");
  append(L" : Rewrite a parse tree fragment $first, combining elements into an \"UNAMBIGUOUS\"\n");
  append(L" : element as long as they match elements in $second, in node order.\n");
  append(L" :\n");
  append(L" : @param $first the first node.\n");
  append(L" : @param $second the second node.\n");
  append(L" : @return $first rewritten, with initial element nodes possibly combined.\n");
  append(L" :)\n");
  append(L"declare function p:rewrite-ambiguity($first as node(), $second as node()?, $unambiguous as xs:boolean)\n");
  append(L"{\n");
  append(L"  typeswitch ($first)\n");
  append(L"  case element() return\n");
  append(L"    if ($unambiguous and deep-equal($first, $second)) then\n");
  append(L"      <UNAMBIGUOUS>{string($first)}</UNAMBIGUOUS>\n");
  append(L"    else\n");
  append(L"      element {node-name($first)}\n");
  append(L"      {\n");
  append(L"        for $node at $i in $first/node()\n");
  append(L"        let $unambiguous :=\n");
  append(L"          $unambiguous and\n");
  append(L"          (every $j in 1 to $i - 1 satisfies deep-equal($first/node()[$j], $second/node()[$j]))\n");
  append(L"        return p:rewrite-ambiguity($node, $second/node()[$i], $unambiguous)\n");
  append(L"      }\n");
  append(L"  default return\n");
  append(L"    $first\n");
  append(L"};\n");
                                                            #line 1016 "PrintXQuery.cpp.template"
                                                                }
                                                            #line 1366 "PrintXQuery.cpp"
  append(L"\n");
  append(L"(:");
  append(L"~");
  append(L"\n");
  append(L" : Construct a new map containing data for one parsing thread.\n");
  append(L" :\n");
  append(L" : @param $id the parsing thread id.\n");
  append(L" : @param $accepted true(), if this thread has accepted.\n");
  append(L" : @param $state the LR parser state number.\n");
  append(L" : @param $action the action code.\n");
  append(L" : @param $nonterminal current nonterminal, -1 if processing a terminal.\n");
  append(L" : @param $bw the whitespace begin input index.\n");
  append(L" : @param $bs the symbol begin input index.\n");
  append(L" : @param $es the symbol end input index.\n");
  append(L" : @param $stack the LR stack.\n");
  append(L" : @param $lexer-state lexer state, error indicator, and result stack.\n");
  append(L" : @return the thread data map.\n");
  append(L" :)\n");
  append(L"declare function p:thread($id as xs:integer,\n");
  append(L"                          $accepted as xs:boolean,\n");
  append(L"                          $state as xs:integer,\n");
  append(L"                          $action as xs:integer,\n");
  append(L"                          $nonterminal as xs:integer,\n");
  append(L"                          $bw as xs:integer,\n");
  append(L"                          $bs as xs:integer,\n");
  append(L"                          $es as xs:integer,\n");
  append(L"                          $stack as xs:integer*,\n");
  append(L"                          $lexer-state as item()+) as map(*)\n");
  append(L"{\n");
  append(L"  map\n");
  append(L"  {\n");
  append(L"    \"id\": $id,\n");
  append(L"    \"accepted\": $accepted,\n");
  append(L"    \"state\": $state,\n");
  append(L"    \"action\": $action,\n");
  append(L"    \"nonterminal\": $nonterminal,\n");
  append(L"    \"bw\": $bw,\n");
  append(L"    \"bs\": $bs,\n");
  append(L"    \"es\": $es,\n");
  append(L"    \"stack\": $stack,\n");
  append(L"    \"lexer-state\": $lexer-state\n");
  append(L"  }\n");
  append(L"};\n");
                                                            #line 1058 "PrintXQuery.cpp.template"
                                                                }
                                                            #line 1412 "PrintXQuery.cpp"
  append(L"\n");
  append(L"(:");
  append(L"~");
  append(L"\n");
  append(L" : Parse input for given target symbol using LR tables. Each invocation\n");
  append(L" : handles one parsing action (shift, reduce, shift+reduce, accept).\n");
  append(L" : Subsequent actions are handled by tail-recursion.\n");
  append(L" :\n");
  append(L" : @param $input the input string.\n");
  append(L" : @param $target the target symbol code.");
                                                            #line 1066 "PrintXQuery.cpp.template"
                                                                if (grammar->useGlr)
                                                                {
                                                            #line 1426 "PrintXQuery.cpp"
  append(L"\n");
  append(L" : @param $max-id the maximum thread id.\n");
  append(L" : @param $thread the parsing thread data.");
                                                            #line 1070 "PrintXQuery.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1434 "PrintXQuery.cpp"
  append(L"\n");
  append(L" : @param $state the LR parser state number.\n");
  append(L" : @param $action the action code.\n");
  append(L" : @param $nonterminal current nonterminal, -1 if processing a terminal.\n");
  append(L" : @param $bw the whitespace begin input index.\n");
  append(L" : @param $bs the symbol begin input index.\n");
  append(L" : @param $es the symbol end input index.\n");
  append(L" : @param $stack the LR stack.\n");
  append(L" : @param $lexer-state lexer state, error indicator, and result stack.");
                                                            #line 1082 "PrintXQuery.cpp.template"
                                                                }
                                                            #line 1446 "PrintXQuery.cpp"
  append(L"\n");
  append(L" : @return the updated state.\n");
  append(L" :)\n");
  append(L"declare function p:parse($input as xs:string,\n");
  append(L"                         $target as xs:integer,");
                                                            #line 1087 "PrintXQuery.cpp.template"
                                                                if (grammar->useGlr)
                                                                {
                                                            #line 1455 "PrintXQuery.cpp"
  append(L"\n");
  append(L"                         $max-id as xs:integer,\n");
  append(L"                         $thread as map(*))\n");
  append(L"{\n");
  append(L"  let $lexer-state := $thread?lexer-state\n");
  append(L"  return\n");
  append(L"    if ($lexer-state[$p:error]) then\n");
  append(L"      $thread\n");
  append(L"    else\n");
  append(L"      let $state := $thread?state\n");
  append(L"      let $action := $thread?action\n");
  append(L"      let $nonterminal := $thread?nonterminal\n");
  append(L"      let $bw := $thread?bw\n");
  append(L"      let $bs := $thread?bs\n");
  append(L"      let $es := $thread?es\n");
  append(L"      let $stack := $thread?stack");
                                                            #line 1104 "PrintXQuery.cpp.template"
                                                                  increaseIndent();
                                                                }
                                                                else
                                                                {
                                                            #line 1477 "PrintXQuery.cpp"
  append(L"\n");
  append(L"                         $state as xs:integer,\n");
  append(L"                         $action as xs:integer,\n");
  append(L"                         $nonterminal as xs:integer,\n");
  append(L"                         $bw as xs:integer,\n");
  append(L"                         $bs as xs:integer,\n");
  append(L"                         $es as xs:integer,\n");
  append(L"                         $stack as xs:integer*,\n");
  append(L"                         $lexer-state as item()+)\n");
  append(L"{\n");
  append(L"  if ($lexer-state[$p:error]) then\n");
  append(L"    $lexer-state\n");
  append(L"  else");
                                                            #line 1120 "PrintXQuery.cpp.template"
                                                                }
                                                                /*
                                                            #line 1494 "PrintXQuery.cpp"
  append(L"\n");
  append(L"    trace((), concat(\"compound action: \", string($action), \", action: \", string($action mod ");
                                                            #line 1124 "PrintXQuery.cpp.template"
                                                                print(format.toString<wchar_t>(1 << (int) LrStates::actionBits));
                                                            #line 1499 "PrintXQuery.cpp"
  append(L"), \", lookback: \", string(($action idiv ");
                                                            #line 1125 "PrintXQuery.cpp.template"
                                                                print(format.toString<wchar_t>(1 << (int) LrStates::actionBits));
                                                            #line 1503 "PrintXQuery.cpp"
  append(L") mod ");
                                                            #line 1126 "PrintXQuery.cpp.template"
                                                                print(format.toString<wchar_t>(1 << grammar->states->dominoBits));
                                                            #line 1507 "PrintXQuery.cpp"
  append(L"),  \", argument: \", string($action idiv ");
                                                            #line 1127 "PrintXQuery.cpp.template"
                                                                print(format.toString<wchar_t>(1 << (grammar->states->dominoBits + LrStates::actionBits)));
                                                            #line 1511 "PrintXQuery.cpp"
  append(L")");
                                                            #line 1129 "PrintXQuery.cpp.template"
    
                                                            #line 1515 "PrintXQuery.cpp"
  append(L")),");
                                                            #line 1130 "PrintXQuery.cpp.template"
                                                                */
                                                                if (trace)
                                                                {
                                                            #line 1521 "PrintXQuery.cpp"
  append(L"\n");
  append(L"    let $trace :=\n");
  append(L"      string-join\n");
  append(L"      (\n");
  append(L"        (\n");
  append(L"          \"  <parse ");
                                                            #line 1138 "PrintXQuery.cpp.template"
                                                                  if (grammar->useGlr)
                                                                  {
                                                            #line 1531 "PrintXQuery.cpp"
  append(L"thread=\"\"\", $thread?id, \"\"\" offset=\"\"\", $lexer-state[$p:e0], \"\"\" ");
                                                            #line 1141 "PrintXQuery.cpp.template"
                                                                  }
                                                            #line 1535 "PrintXQuery.cpp"
  append(L"state=\"\"\", string($state), \"\"\" input=\"\"\",\n");
  append(L"          $p:NONTERMINAL[$nonterminal + 1],\n");
  append(L"          \" \"[$nonterminal ge 0 and $lexer-state[$p:l1] gt 0],\n");
  append(L"          p:xml-escape(p:lookahead-string($lexer-state)),\n");
  append(L"          \"\"\" action=\"\"\"\n");
  append(L"        ),\n");
  append(L"        \"\"\n");
  append(L"      )");
                                                            #line 1149 "PrintXQuery.cpp.template"
                                                                }
                                                            #line 1546 "PrintXQuery.cpp"
  append(L"\n");
  append(L"    let $argument := $action idiv ");
                                                            #line 1151 "PrintXQuery.cpp.template"
                                                                print(format.toString<wchar_t>(1 << (grammar->states->dominoBits + LrStates::actionBits)));
                                                            #line 1551 "PrintXQuery.cpp"
  append(L"\n");
  append(L"    let $lookback := ($action idiv ");
                                                            #line 1153 "PrintXQuery.cpp.template"
                                                                print(format.toString<wchar_t>(1 << (int) LrStates::actionBits));
                                                            #line 1556 "PrintXQuery.cpp"
  append(L") mod ");
                                                            #line 1154 "PrintXQuery.cpp.template"
                                                                print(format.toString<wchar_t>(1 << grammar->states->dominoBits));
                                                            #line 1560 "PrintXQuery.cpp"
  append(L"\n");
  append(L"    let $action := $action mod ");
                                                            #line 1156 "PrintXQuery.cpp.template"
                                                                print(format.toString<wchar_t>(1 << (int) LrStates::actionBits));
                                                            #line 1565 "PrintXQuery.cpp"
  append(L"\n");
  append(L"    return\n");
  append(L"      if ($action eq 6) then (: SHIFT+ACCEPT :)");
                                                            #line 1159 "PrintXQuery.cpp.template"
                                                                if (trace)
                                                                {
                                                            #line 1572 "PrintXQuery.cpp"
  append(L"\n");
  append(L"      (\n");
  append(L"        p:trace(concat($trace, \"accept\"\"/>\")),");
                                                            #line 1163 "PrintXQuery.cpp.template"
                                                                }
                                                                if (grammar->useGlr)
                                                                {
                                                            #line 1580 "PrintXQuery.cpp"
  append(L"\n");
  append(L"        p:thread($thread?id, true(), $state, $action, $nonterminal, $bw, $bs, $es, $stack, $lexer-state)");
                                                            #line 1168 "PrintXQuery.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1587 "PrintXQuery.cpp"
  append(L"\n");
  append(L"        $lexer-state");
                                                            #line 1172 "PrintXQuery.cpp.template"
                                                                }
                                                                if (trace)
                                                                {
                                                            #line 1594 "PrintXQuery.cpp"
  append(L"\n");
  append(L"      )");
                                                            #line 1176 "PrintXQuery.cpp.template"
                                                                }
                                                                if (grammar->useGlr)
                                                                {
                                                            #line 1601 "PrintXQuery.cpp"
  append(L"\n");
  append(L"      else if ($action eq 7) then (: FORK :)");
                                                            #line 1180 "PrintXQuery.cpp.template"
                                                                  if (trace)
                                                                  {
                                                            #line 1607 "PrintXQuery.cpp"
  append(L"\n");
  append(L"      (\n");
  append(L"        p:trace(concat($trace, \"fork\"\"/>\")),");
                                                            #line 1184 "PrintXQuery.cpp.template"
                                                                  }
                                                            #line 1613 "PrintXQuery.cpp"
  append(L"\n");
  append(L"        for $i in (1, 2)\n");
  append(L"        return p:thread(($max-id + 1, $thread?id)[$i], false(), $state, $p:APPENDIX[$argument + $i], -1, $bw, $bs, $es, $stack, $lexer-state)");
                                                            #line 1188 "PrintXQuery.cpp.template"
                                                                  if (trace)
                                                                  {
                                                            #line 1620 "PrintXQuery.cpp"
  append(L"\n");
  append(L"      )");
                                                            #line 1191 "PrintXQuery.cpp.template"
                                                                  }
                                                                }
                                                            #line 1626 "PrintXQuery.cpp"
  append(L"\n");
  append(L"      else\n");
  append(L"        let $shift-reduce-symbols :=\n");
  append(L"          if ($action eq 1) then (: SHIFT :)\n");
  append(L"            ($argument, -1, -1)\n");
  append(L"          else if ($action eq 2) then (: REDUCE :)\n");
  append(L"            (-1, $argument, $lookback)");
                                                            #line 1199 "PrintXQuery.cpp.template"
                                                                if (grammar->states->hasLookback)
                                                                {
                                                            #line 1637 "PrintXQuery.cpp"
  append(L"\n");
  append(L"          else if ($action eq 3) then (: REDUCE+LOOKBACK :)\n");
  append(L"            (-1, $argument, p:count($lookback, 0, $stack, count($stack) - 1))");
                                                            #line 1204 "PrintXQuery.cpp.template"
                                                                }
                                                            #line 1643 "PrintXQuery.cpp"
  append(L"\n");
  append(L"          else if ($action eq 4) then (: SHIFT+REDUCE :)\n");
  append(L"            ($state, $argument, $lookback + 1)");
                                                            #line 1207 "PrintXQuery.cpp.template"
                                                                if (grammar->states->hasLookback)
                                                                {
                                                            #line 1650 "PrintXQuery.cpp"
  append(L"\n");
  append(L"          else if ($action eq 5) then (: SHIFT+REDUCE+LOOKBACK :)\n");
  append(L"            ($state, $argument, p:count($lookback, 1, $stack, count($stack) - 1))");
                                                            #line 1212 "PrintXQuery.cpp.template"
                                                                }
                                                            #line 1656 "PrintXQuery.cpp"
  append(L"\n");
  append(L"          else (: ERROR :)\n");
  append(L"            (-1, -1, -1)\n");
  append(L"        let $shift := $shift-reduce-symbols[1]\n");
  append(L"        let $reduce := $shift-reduce-symbols[2]\n");
  append(L"        let $symbols := $shift-reduce-symbols[3]\n");
  append(L"        let $es := if ($shift lt 0 or $nonterminal ge 0) then $es else $lexer-state[$p:e1]");
                                                            #line 1220 "PrintXQuery.cpp.template"
                                                                if (trace)
                                                                {
                                                            #line 1667 "PrintXQuery.cpp"
  append(L"\n");
  append(L"        let $trace := if ($shift lt 0) then $trace else concat($trace, \"shift\")");
                                                            #line 1224 "PrintXQuery.cpp.template"
                                                                }
                                                            #line 1672 "PrintXQuery.cpp"
  append(L"\n");
  append(L"        let $lexer-state :=\n");
  append(L"          if ($shift lt 0 or $nonterminal ge 0) then\n");
  append(L"            $lexer-state\n");
  append(L"          else\n");
  append(L"            p:consume\n");
  append(L"            (\n");
  append(L"              $lexer-state[$p:l1],\n");
  append(L"              $input,\n");
  append(L"              $lexer-state\n");
  append(L"            )\n");
  append(L"        let $stack :=\n");
  append(L"          if ($shift lt 0) then\n");
  append(L"            $stack\n");
  append(L"          else\n");
  append(L"            ($stack, if ($nonterminal lt 0) then $lexer-state[$p:b0] else $bs, $state, $lookback)\n");
  append(L"        let $state := if ($shift lt 0) then $state else $shift\n");
  append(L"        return\n");
  append(L"          if ($reduce lt 0) then\n");
  append(L"            if ($shift lt 0) then\n");
  append(L"            (");
                                                            #line 1245 "PrintXQuery.cpp.template"
                                                                if (trace)
                                                                {
                                                            #line 1697 "PrintXQuery.cpp"
  append(L"\n");
  append(L"              p:trace(concat($trace, \"fail\"\"/>\")),");
                                                            #line 1248 "PrintXQuery.cpp.template"
                                                                }
                                                                if (grammar->useGlr)
                                                                {
                                                            #line 1704 "PrintXQuery.cpp"
  append(L"\n");
  append(L"              p:thread\n");
  append(L"              (\n");
  append(L"                $thread?id, false(), $state, 0, -1, $bw, $bs, $es, $stack,\n");
  append(L"                (");
                                                            #line 1255 "PrintXQuery.cpp.template"
                                                                  increaseIndent(2);
                                                                }
                                                            #line 1713 "PrintXQuery.cpp"
  append(L"\n");
  append(L"              subsequence($lexer-state, 1, $p:error - 1),\n");
  append(L"              element error\n");
  append(L"              {\n");
  append(L"                attribute b {$lexer-state[$p:b1]},\n");
  append(L"                attribute e {$lexer-state[$p:e1]},\n");
  append(L"                attribute o {$lexer-state[$p:l1]}[. > 0],\n");
  append(L"                attribute s {$p:TOKENSET[$state + 1] + 1}\n");
  append(L"              },\n");
  append(L"              subsequence($lexer-state, $p:error + 1)");
                                                            #line 1266 "PrintXQuery.cpp.template"
                                                                if (grammar->useGlr)
                                                                {
                                                                  decreaseIndent(2);
                                                            #line 1728 "PrintXQuery.cpp"
  append(L"\n");
  append(L"                )\n");
  append(L"              )");
                                                            #line 1271 "PrintXQuery.cpp.template"
                                                                }
                                                            #line 1734 "PrintXQuery.cpp"
  append(L"\n");
  append(L"            )\n");
  append(L"            else\n");
  append(L"              let $lexer-state := p:predict($input, $lexer-state, $state");
                                                            #line 1276 "PrintXQuery.cpp.template"
                                                                if (grammar->useGlr)
                                                                {
                                                            #line 1742 "PrintXQuery.cpp"
  append(L", $thread?id");
                                                            #line 1278 "PrintXQuery.cpp.template"
                                                                }
                                                            #line 1746 "PrintXQuery.cpp"
  append(L")\n");
  append(L"              return");
                                                            #line 1280 "PrintXQuery.cpp.template"
                                                                if (trace)
                                                                {
                                                            #line 1752 "PrintXQuery.cpp"
  append(L"\n");
  append(L"              (\n");
  append(L"                p:trace(concat($trace, \"\"\"/>\")),\n");
  append(L"                ");
                                                            #line 1285 "PrintXQuery.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1761 "PrintXQuery.cpp"
  append(L" ");
                                                            #line 1288 "PrintXQuery.cpp.template"
                                                                }
                                                                if (grammar->useGlr)
                                                                {
                                                            #line 1767 "PrintXQuery.cpp"
  append(L"p:thread($thread?id, false(), $state, $lexer-state[$p:lk], -1, $bw, $bs, $es, $stack, $lexer-state)");
                                                            #line 1292 "PrintXQuery.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1773 "PrintXQuery.cpp"
  append(L"p:parse($input, $target, $state, $lexer-state[$p:lk], -1, $bw, $bs, $es, $stack, $lexer-state)");
                                                            #line 1296 "PrintXQuery.cpp.template"
                                                                }
                                                                if (trace)
                                                                {
                                                            #line 1779 "PrintXQuery.cpp"
  append(L"\n");
  append(L"              )");
                                                            #line 1300 "PrintXQuery.cpp.template"
                                                                }
                                                            #line 1784 "PrintXQuery.cpp"
  append(L"\n");
  append(L"          else");
                                                            #line 1302 "PrintXQuery.cpp.template"
                                                                if (trace)
                                                                {
                                                            #line 1790 "PrintXQuery.cpp"
  append(L"\n");
  append(L"            let $trace := concat($trace, if ($shift lt 0) then \"\" else \" \", \"reduce\"\" nonterminal=\"\"\", $p:NONTERMINAL[$reduce + 1], \"\"\" count=\"\"\", $symbols, \"\"\"/>\")");
                                                            #line 1306 "PrintXQuery.cpp.template"
                                                                }
                                                            #line 1795 "PrintXQuery.cpp"
  append(L"\n");
  append(L"            let $state := if ($symbols gt 0) then $stack[last() - 3 * $symbols + 2] else $state\n");
  append(L"            let $bs := if ($symbols gt 0) then $stack[last() - 3 * $symbols + 1] else $lexer-state[$p:b1]\n");
  append(L"            let $es := if ($symbols gt 0) then $es else $bs\n");
  append(L"            let $stack := if ($symbols gt 0) then subsequence($stack, 1, count($stack) - 3 * $symbols) else $stack");
                                                            #line 1312 "PrintXQuery.cpp.template"
                                                                if (tree && anyWhitespace)
                                                                {
                                                            #line 1804 "PrintXQuery.cpp"
  append(L"\n");
  append(L"            let $lexer-state := if ($symbols gt 0) then $lexer-state else p:whitespace($input, $lexer-state)");
                                                            #line 1316 "PrintXQuery.cpp.template"
                                                                  whitespaceCalled = true;
                                                                }
                                                            #line 1810 "PrintXQuery.cpp"
  append(L"\n");
  append(L"            let $accept := $reduce eq $target and count($stack) eq 3\n");
  append(L"            let $bs := if ($accept) then $bw else $bs\n");
  append(L"            let $es := if ($accept) then $lexer-state[$p:b1] else $es\n");
  append(L"            let $bw := if ($accept) then $es else $bw");
                                                            #line 1322 "PrintXQuery.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 1819 "PrintXQuery.cpp"
  append(L"\n");
  append(L"            let $index := if ($accept) then $p:result else p:first-child-node-index($lexer-state, count($lexer-state) + 1, $symbols)\n");
  append(L"            let $lexer-state :=\n");
  append(L"            (\n");
  append(L"              subsequence($lexer-state, 1, $index - 1),\n");
  append(L"              element {$p:NONTERMINAL[$reduce + 1]}\n");
  append(L"              {\n");
  append(L"                (: bs, es :)\n");
  append(L"                subsequence($lexer-state, $index)\n");
  append(L"              }\n");
  append(L"            )");
                                                            #line 1334 "PrintXQuery.cpp.template"
                                                                }
                                                                if (hasCustomCode)
                                                                {
                                                            #line 1835 "PrintXQuery.cpp"
  append(L"\n");
  append(L"            let $nonterminal := $p:REDUCTION[$reduce + 1]\n");
  append(L"            let $reduce := $p:REDUCTION[$reduce + 2]\n");
  append(L"            let $lexer-state := if ($reduce lt 0) then $lexer-state else p:execute($input, $lexer-state, $reduce)");
                                                            #line 1341 "PrintXQuery.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1844 "PrintXQuery.cpp"
  append(L"\n");
  append(L"            let $nonterminal := $reduce");
                                                            #line 1345 "PrintXQuery.cpp.template"
                                                                }
                                                                if (grammar->useGlr)
                                                                {
                                                            #line 1851 "PrintXQuery.cpp"
  append(L"\n");
  append(L"            let $thread := p:thread($thread?id, false(), $state, p:goto($nonterminal, $state), $nonterminal, $bw, $bs, $es, $stack, $lexer-state)");
                                                            #line 1350 "PrintXQuery.cpp.template"
                                                                }
                                                            #line 1856 "PrintXQuery.cpp"
  append(L"\n");
  append(L"            return");
                                                            #line 1352 "PrintXQuery.cpp.template"
                                                                if (trace)
                                                                {
                                                            #line 1862 "PrintXQuery.cpp"
  append(L"\n");
  append(L"            (\n");
  append(L"              p:trace($trace),\n");
  append(L"              ");
                                                            #line 1357 "PrintXQuery.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1871 "PrintXQuery.cpp"
  append(L" ");
                                                            #line 1360 "PrintXQuery.cpp.template"
                                                                }
                                                            #line 1875 "PrintXQuery.cpp"
  append(L"p:parse($input, $target, ");
                                                            #line 1361 "PrintXQuery.cpp.template"
                                                                if (grammar->useGlr)
                                                                {
                                                            #line 1880 "PrintXQuery.cpp"
  append(L"$max-id, $thread)");
                                                            #line 1363 "PrintXQuery.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1886 "PrintXQuery.cpp"
  append(L"$state, p:goto($nonterminal, $state), $nonterminal, $bw, $bs, $es, $stack, $lexer-state)");
                                                            #line 1367 "PrintXQuery.cpp.template"
                                                                }
                                                                if (trace)
                                                                {
                                                            #line 1892 "PrintXQuery.cpp"
  append(L"\n");
  append(L"            )");
                                                            #line 1371 "PrintXQuery.cpp.template"
                                                                }
                                                                if (grammar->useGlr)
                                                                  decreaseIndent();
                                                            #line 1899 "PrintXQuery.cpp"
  append(L"\n");
  append(L"};\n");
                                                            #line 1377 "PrintXQuery.cpp.template"
                                                                if (hasCustomCode)
                                                                {
                                                            #line 1905 "PrintXQuery.cpp"
  append(L"\n");
  append(L"(:");
  append(L"~");
  append(L"\n");
  append(L" : Update state with code annotation results.\n");
  append(L" :\n");
  append(L" : @param $input the input string.\n");
  append(L" : @param $state lexer state, error indicator, and result stack.\n");
  append(L" : @param $reduce the reduce case id.\n");
  append(L" : @return the updated state.\n");
  append(L" :)\n");
  append(L"declare function p:execute($input as xs:string,\n");
  append(L"                           $state as item()+,\n");
  append(L"                           $reduce as xs:integer) as item()+\n");
  append(L"{");
                                                            #line 1391 "PrintXQuery.cpp.template"
                                                                  increaseIndent();
                                                                  int lastContentId = grammar->distinctCodeAnnotations.size() - 1;
                                                                  for (int contentId = 0; contentId <= lastContentId; ++contentId)
                                                                  {
                                                                    ProcessingInstruction *p = grammar->distinctCodeAnnotations[contentId];
                                                            #line 1927 "PrintXQuery.cpp"
  append(L"\n");
                                                            #line 1397 "PrintXQuery.cpp.template"
                                                                    if (contentId > 0)
                                                                    {
                                                            #line 1932 "PrintXQuery.cpp"
  append(L"else ");
                                                            #line 1399 "PrintXQuery.cpp.template"
                                                                    }
                                                            #line 1936 "PrintXQuery.cpp"
  append(L"if ($reduce eq ");
                                                            #line 1400 "PrintXQuery.cpp.template"
                                                                    print(format.toString<wchar_t>(contentId));
                                                            #line 1940 "PrintXQuery.cpp"
  append(L") then\n");
  append(L"(");
                                                            #line 1402 "PrintXQuery.cpp.template"
                                                                    visitProcessingInstruction(p);
                                                            #line 1945 "PrintXQuery.cpp"
  append(L"\n");
  append(L"  return $state\n");
  append(L")");
                                                            #line 1405 "PrintXQuery.cpp.template"
                                                                  }
                                                            #line 1951 "PrintXQuery.cpp"
  append(L"\n");
  append(L"else\n");
  append(L"  $state");
                                                            #line 1408 "PrintXQuery.cpp.template"
                                                                  increaseIndent();
                                                            #line 1957 "PrintXQuery.cpp"
  append(L"\n");
  append(L"};\n");
                                                            #line 1411 "PrintXQuery.cpp.template"
                                                                }

                                                                if (tree)
                                                                {
                                                            #line 1965 "PrintXQuery.cpp"
  append(L"\n");
  append(L"(:");
  append(L"~");
  append(L"\n");
  append(L" : Decrement given index by the given number of elements on the result\n");
  append(L" : stack, skipping any non-element nodes.\n");
  append(L" :\n");
  append(L" : @param $state lexer state, error indicator, and result stack.\n");
  append(L" : @param $index the index into the result stack.\n");
  append(L" : @param $element-count the number of elements to be handled.\n");
  append(L" : @return the decremented index.\n");
  append(L" :)\n");
  append(L"declare function p:first-child-node-index($state as item()+,\n");
  append(L"                                          $index as xs:integer,\n");
  append(L"                                          $element-count as xs:integer)\n");
  append(L"{\n");
  append(L"  if ($element-count eq 0) then\n");
  append(L"    $index\n");
  append(L"  else\n");
  append(L"    let $index := $index - 1\n");
  append(L"    let $element-count := $element-count - (if ($state[$index] instance of element()) then 1 else 0)\n");
  append(L"    return p:first-child-node-index($state, $index, $element-count)\n");
  append(L"};\n");
                                                            #line 1436 "PrintXQuery.cpp.template"
                                                                }
                                                              }
                                                              if (trace)
                                                              {
                                                            #line 1994 "PrintXQuery.cpp"
  append(L"\n");
  append(L"(:");
  append(L"~");
  append(L"\n");
  append(L" : Assemble a string showing current lookahead tokens, as far as they have\n");
  append(L" : been tokenized.\n");
  append(L" :\n");
  append(L" : @param $state lexer state, error indicator, and result stack.\n");
  append(L" : @return a string containing the space-separated list of lookahead tokens.\n");
  append(L" :)\n");
  append(L"declare function p:lookahead-string($state as item()+) as xs:string\n");
  append(L"{\n");
  append(L"  string-join\n");
  append(L"  (\n");
  append(L"    (\n");
  append(L"      if ($state[$p:l1] le 0) then\n");
  append(L"        ()\n");
  append(L"      else\n");
  append(L"      (\n");
  append(L"        $p:TOKEN[$state[$p:l1] + 1]");
                                                            #line 1457 "PrintXQuery.cpp.template"
                                                                for (size_t i = 2; i <= grammar->k; ++i)
                                                                {
                                                                  increaseIndent();
                                                            #line 2019 "PrintXQuery.cpp"
  append(L",\n");
  append(L"      if ($state[$p:l");
                                                            #line 1461 "PrintXQuery.cpp.template"
                                                                  print(format.toString<wchar_t>(i));
                                                            #line 2024 "PrintXQuery.cpp"
  append(L"] le 0) then\n");
  append(L"        ()\n");
  append(L"      else\n");
  append(L"      (\n");
  append(L"        $p:TOKEN[$state[$p:l");
                                                            #line 1466 "PrintXQuery.cpp.template"
                                                                  print(format.toString<wchar_t>(i));
                                                            #line 2032 "PrintXQuery.cpp"
  append(L"] + 1]");
                                                            #line 1467 "PrintXQuery.cpp.template"
                                                                }
                                                                for (size_t i = 2; i <= grammar->k; ++i)
                                                                {
                                                            #line 2038 "PrintXQuery.cpp"
  append(L"\n");
  append(L"      )");
                                                            #line 1471 "PrintXQuery.cpp.template"
                                                                  decreaseIndent();
                                                                }
                                                            #line 2044 "PrintXQuery.cpp"
  append(L"\n");
  append(L"      )\n");
  append(L"    ),\n");
  append(L"    \" \"\n");
  append(L"  )\n");
  append(L"};\n");
                                                            #line 1479 "PrintXQuery.cpp.template"
                                                              }
                                                            #line 2053 "PrintXQuery.cpp"
  append(L"\n");
  append(L"(:");
  append(L"~");
  append(L"\n");
  append(L" : Create a textual error message from a parsing error.\n");
  append(L" :\n");
  append(L" : @param $input the input string.\n");
  append(L" : @param $error the parsing error descriptor.\n");
  append(L" : @return the error message.\n");
  append(L" :)\n");
  append(L"declare function p:error-message($input as xs:string, $error as element(error)) as xs:string\n");
  append(L"{\n");
  append(L"  let $begin := xs:integer($error/@b)\n");
  append(L"  let $context := string-to-codepoints(substring($input, 1, $begin - 1))\n");
  append(L"  let $linefeeds := index-of($context, 10)\n");
  append(L"  let $line := count($linefeeds) + 1\n");
  append(L"  let $column := ($begin - $linefeeds[last()], $begin)[1]\n");
  append(L"  return\n");
  append(L"    string-join\n");
  append(L"    (\n");
  append(L"      (\n");
  append(L"        ");
                                                            #line 1499 "PrintXQuery.cpp.template"
                                                              if (grammar->useGlr)
                                                              {
                                                            #line 2079 "PrintXQuery.cpp"
  append(L"if ($error/@ambiguous-input) then\n");
  append(L"          \"ambiguous input\"\n");
  append(L"        else ");
                                                            #line 1503 "PrintXQuery.cpp.template"
                                                              }
                                                            #line 2085 "PrintXQuery.cpp"
  append(L"if ($error/@o) then\n");
  append(L"          (\"syntax error, found \", $p:TOKEN[$error/@o + 1])\n");
  append(L"        else\n");
  append(L"          \"lexical analysis failed\",\n");
  append(L"        \"&#10;\",");
                                                            #line 1508 "PrintXQuery.cpp.template"
                                                              if (grammar->useGlr)
                                                              {
                                                            #line 2094 "PrintXQuery.cpp"
  append(L"\n");
  append(L"        if ($error/@ambiguous-input) then\n");
  append(L"          ()\n");
  append(L"        else\n");
  append(L"        (");
                                                            #line 1514 "PrintXQuery.cpp.template"
                                                                increaseIndent();
                                                              }
                                                            #line 2103 "PrintXQuery.cpp"
  append(L"\n");
  append(L"        \"while expecting \",\n");
  append(L"        if ($error/@x) then\n");
  append(L"          $p:TOKEN[$error/@x + 1]\n");
  append(L"        else\n");
  append(L"          let $expected := p:expected-token-set($error/@s)\n");
  append(L"          return\n");
  append(L"          (\n");
  append(L"            \"[\"[exists($expected[2])],\n");
  append(L"            string-join($expected, \", \"),\n");
  append(L"            \"]\"[exists($expected[2])]\n");
  append(L"          ),\n");
  append(L"        \"&#10;\",\n");
  append(L"        if ($error/@o or $error/@e = $begin) then\n");
  append(L"          ()\n");
  append(L"        else\n");
  append(L"          (\"after successfully scanning \", string($error/@e - $begin), \" characters beginning \")");
                                                            #line 1533 "PrintXQuery.cpp.template"
                                                              if (grammar->useGlr)
                                                              {
                                                                decreaseIndent();
                                                            #line 2125 "PrintXQuery.cpp"
  append(L"\n");
  append(L"        )");
                                                            #line 1537 "PrintXQuery.cpp.template"
                                                              }
                                                            #line 2130 "PrintXQuery.cpp"
  append(L",\n");
  append(L"        \"at line \", string($line), \", column \", string($column), \":&#10;\",\n");
  append(L"        \"...\", substring($input, $begin, 64), \"...\"\n");
  append(L"      ),\n");
  append(L"      \"\"\n");
  append(L"    )\n");
  append(L"};\n");
                                                            #line 1546 "PrintXQuery.cpp.template"
                                                              const wchar_t *name[2] = {L"consume", L"consumeT"};
                                                              for (int i = 0; i < consumeMethods; ++i)
                                                              {
                                                            #line 2142 "PrintXQuery.cpp"
  append(L"\n");
  append(L"(:");
  append(L"~");
  append(L"\n");
  append(L" : Consume one token, i.e. compare lookahead token 1 with expected\n");
  append(L" : token and in case of a match, shift lookahead tokens down such that\n");
  append(L" : l1 becomes the current token, and higher lookahead tokens move down.\n");
  append(L" : When lookahead token 1 does not match the expected token, raise an\n");
  append(L" : error by saving the expected token code in the error field of the\n");
  append(L" : lexer state.");
                                                            #line 1556 "PrintXQuery.cpp.template"
                                                                if (i)
                                                                {
                                                            #line 2156 "PrintXQuery.cpp"
  append(L" In contrast to p:consume, do not create any output.");
                                                            #line 1559 "PrintXQuery.cpp.template"
                                                                }
                                                            #line 2160 "PrintXQuery.cpp"
  append(L"\n");
  append(L" :\n");
  append(L" : @param $code the expected token.\n");
  append(L" : @param $input the input string.\n");
  append(L" : @param $state lexer state, error indicator, and result stack.\n");
  append(L" : @return the updated state.\n");
  append(L" :)\n");
  append(L"declare function p:");
                                                            #line 1567 "PrintXQuery.cpp.template"
                                                                print(name[i]);
                                                            #line 2171 "PrintXQuery.cpp"
  append(L"($code as xs:integer, $input as xs:string, $state as item()+) as item()+\n");
  append(L"{\n");
  append(L"  if ($state[$p:error]) then\n");
  append(L"    $state\n");
  append(L"  else if ($state[$p:l1] eq $code) then");
                                                            #line 1572 "PrintXQuery.cpp.template"
                                                                if (trace && ! isLrParser)
                                                                {
                                                            #line 2180 "PrintXQuery.cpp"
  append(L"\n");
  append(L"    let $state :=");
                                                            #line 1575 "PrintXQuery.cpp.template"
                                                                  increaseIndent();
                                                                }
                                                            #line 2186 "PrintXQuery.cpp"
  append(L"\n");
  append(L"  (\n");
  append(L"    subsequence($state, $p:l1, ");
                                                            #line 1579 "PrintXQuery.cpp.template"
                                                                print(format.toString<wchar_t>(grammar->k * 3));
                                                            #line 2192 "PrintXQuery.cpp"
  append(L"),\n");
  append(L"    0, 0, 0,\n");
  append(L"    subsequence($state, ");
                                                            #line 1582 "PrintXQuery.cpp.template"
                                                                print(format.toString<wchar_t>((grammar->k + 1) * 3 + 1));
                                                            #line 2198 "PrintXQuery.cpp"
  append(L")");
                                                            #line 1583 "PrintXQuery.cpp.template"
                                                                if (tree && i == 0)
                                                                {
                                                            #line 2203 "PrintXQuery.cpp"
  append(L",\n");
  append(L"    let $begin := $state[$p:e0]\n");
  append(L"    let $end := $state[$p:b1]\n");
  append(L"    where $begin ne $end\n");
  append(L"    return\n");
  append(L"      text\n");
  append(L"      {\n");
  append(L"        substring($input, $begin, $end - $begin)\n");
  append(L"      },\n");
  append(L"    let $token := $p:TOKEN[1 + $state[$p:l1]]\n");
  append(L"    let $name := if (starts-with($token, \"'\")) then \"TOKEN\" else $token\n");
  append(L"    let $begin := $state[$p:b1]\n");
  append(L"    let $end := $state[$p:e1]\n");
  append(L"    return\n");
  append(L"      element {$name}\n");
  append(L"      {\n");
  append(L"        substring($input, $begin, $end - $begin)\n");
  append(L"      }");
                                                            #line 1602 "PrintXQuery.cpp.template"
                                                                }
                                                            #line 2224 "PrintXQuery.cpp"
  append(L"\n");
  append(L"  )");
                                                            #line 1604 "PrintXQuery.cpp.template"
                                                                if (trace && ! isLrParser)
                                                                {
                                                                  decreaseIndent();
                                                            #line 2231 "PrintXQuery.cpp"
  append(L"\n");
  append(L"    return\n");
  append(L"    (\n");
  append(L"      p:trace\n");
  append(L"      (\n");
  append(L"        string-join\n");
  append(L"        (\n");
  append(L"          (\n");
  append(L"            \"  <");
                                                            #line 1615 "PrintXQuery.cpp.template"
                                                                  print(i == 0 ? methodPrefixParse : methodPrefixTry);
                                                            #line 2243 "PrintXQuery.cpp"
  append(L" terminal=\"\"\", p:xml-escape($p:TOKEN[$code + 1]), \"\"\"\",\n");
  append(L"            if ($state[$p:l1] le 0) then () else (\" input=\"\"\", p:xml-escape(p:lookahead-string($state)), \"\"\"\"),\n");
  append(L"            \"/>\"\n");
  append(L"          ),\n");
  append(L"          \"\"\n");
  append(L"        )\n");
  append(L"      ),\n");
  append(L"      $state\n");
  append(L"    )");
                                                            #line 1624 "PrintXQuery.cpp.template"
                                                                }
                                                            #line 2255 "PrintXQuery.cpp"
  append(L"\n");
  append(L"  else\n");
  append(L"  (\n");
  append(L"    subsequence($state, 1, $p:error - 1),\n");
  append(L"    element error\n");
  append(L"    {");
                                                            #line 1630 "PrintXQuery.cpp.template"
                                                                if (memoization)
                                                                {
                                                            #line 2265 "PrintXQuery.cpp"
  append(L"\n");
  append(L"      if ($state[$p:e1] < $state[$p:memo]/@e) then\n");
  append(L"        $state[$p:memo]/@*\n");
  append(L"      else\n");
  append(L"      (");
                                                            #line 1636 "PrintXQuery.cpp.template"
                                                                  increaseIndent();
                                                                }
                                                            #line 2274 "PrintXQuery.cpp"
  append(L"\n");
  append(L"      attribute b {$state[$p:b1]},\n");
  append(L"      attribute e {$state[$p:e1]},\n");
  append(L"      if ($state[$p:l1] lt 0) then\n");
  append(L"        attribute s {- $state[$p:l1]}\n");
  append(L"      else\n");
  append(L"        (attribute o {$state[$p:l1]}, attribute x {$code})");
                                                            #line 1644 "PrintXQuery.cpp.template"
                                                                if (memoization)
                                                                {
                                                                  decreaseIndent();
                                                            #line 2286 "PrintXQuery.cpp"
  append(L"\n");
  append(L"      )");
                                                            #line 1648 "PrintXQuery.cpp.template"
                                                                }
                                                            #line 2291 "PrintXQuery.cpp"
  append(L"\n");
  append(L"    },\n");
  append(L"    subsequence($state, $p:error + 1)\n");
  append(L"  )\n");
  append(L"};\n");
                                                            #line 1654 "PrintXQuery.cpp.template"
                                                              }
                                                              if (anyWhitespace)
                                                              {
                                                                if (whitespaceCalled)
                                                                {
                                                            #line 2303 "PrintXQuery.cpp"
  append(L"\n");
  append(L"(:");
  append(L"~");
  append(L"\n");
  append(L" : Consume whitespace.\n");
  append(L" :\n");
  append(L" : @param $input the input string.\n");
  append(L" : @param $state lexer state, error indicator, and result stack.\n");
  append(L" : @return the updated state.\n");
  append(L" :)\n");
  append(L"declare function p:whitespace($input as xs:string,\n");
  append(L"                              $state as item()+) as item()+\n");
  append(L"{\n");
  append(L"  if ($state[$p:e0] = $state[$p:b1]) then\n");
  append(L"    $state\n");
  append(L"  else\n");
  append(L"    let $begin := $state[$p:e0]\n");
  append(L"    let $end := $state[$p:b1]\n");
  append(L"    return\n");
  append(L"    (\n");
  append(L"      0,\n");
  append(L"      $state[$p:b0],\n");
  append(L"      $end,\n");
  append(L"      subsequence($state, $p:e0 + 1),\n");
  append(L"      text\n");
  append(L"      {\n");
  append(L"        substring($input, $begin, $end - $begin)\n");
  append(L"      }\n");
  append(L"    )\n");
  append(L"};\n");
                                                            #line 1688 "PrintXQuery.cpp.template"
                                                                }
                                                            #line 2336 "PrintXQuery.cpp"
  append(L"\n");
  append(L"(:");
  append(L"~");
  append(L"\n");
  append(L" : Use p:match to fetch the next token, but skip any leading\n");
  append(L" : whitespace.\n");
  append(L" :\n");
  append(L" : @param $input the input string.\n");
  append(L" : @param $begin the index where to start.\n");
  append(L" : @param $token-set the valid token set id.");
                                                            #line 1696 "PrintXQuery.cpp.template"
                                                                if (grammar->useGlr)
                                                                {
                                                            #line 2350 "PrintXQuery.cpp"
  append(L"\n");
  append(L" : @param $id the parsing thread id.");
                                                            #line 1699 "PrintXQuery.cpp.template"
                                                                }
                                                            #line 2355 "PrintXQuery.cpp"
  append(L"\n");
  append(L" : @return a sequence of three values: the token code of the result\n");
  append(L" : token, with input string positions of token begin and end.\n");
  append(L" :)\n");
  append(L"declare function p:matchW($input as xs:string,\n");
  append(L"                          $begin as xs:integer,\n");
  append(L"                          $token-set as xs:integer");
                                                            #line 1706 "PrintXQuery.cpp.template"
                                                                if (grammar->useGlr)
                                                                {
                                                            #line 2366 "PrintXQuery.cpp"
  append(L",\n");
  append(L"                          $id as xs:integer");
                                                            #line 1709 "PrintXQuery.cpp.template"
                                                                }
                                                            #line 2371 "PrintXQuery.cpp"
  append(L")\n");
  append(L"{\n");
  append(L"  let $match := p:match($input, $begin, $token-set");
                                                            #line 1712 "PrintXQuery.cpp.template"
                                                                if (grammar->useGlr)
                                                                {
                                                            #line 2378 "PrintXQuery.cpp"
  append(L", $id");
                                                            #line 1714 "PrintXQuery.cpp.template"
                                                                }
                                                            #line 2382 "PrintXQuery.cpp"
  append(L")\n");
  append(L"  return");
                                                            #line 1716 "PrintXQuery.cpp.template"
                                                                setIndent(2);
                                                                const wchar_t *condition = L"if (";
                                                                if (simpleWhitespace)
                                                                {
                                                                  condition = L"else if (";
                                                                  printMatch(0, 0, 0, grammar->simpleWhitespaceIntroducers, IF, 0, L"if (", L") then");
                                                            #line 2392 "PrintXQuery.cpp"
  append(L"\n");
  append(L"  p:matchW($input, $match[3], $token-set");
                                                            #line 1723 "PrintXQuery.cpp.template"
                                                                  if (grammar->useGlr)
                                                                  {
                                                            #line 2398 "PrintXQuery.cpp"
  append(L", $id");
                                                            #line 1725 "PrintXQuery.cpp.template"
                                                                  }
                                                            #line 2402 "PrintXQuery.cpp"
  append(L")");
                                                            #line 1726 "PrintXQuery.cpp.template"
                                                                }
                                                                if (complexWhitespace)
                                                                {
                                                                  printMatch(0, 0, 0, grammar->complexWhitespaceIntroducers, IF, 0, condition, L") then");
                                                                  if (isLrParser)
                                                                  {
                                                            #line 2411 "PrintXQuery.cpp"
  append(L"\n");
  append(L"  let $state := (0, $begin, $begin, $match, 0, 0");
                                                            #line 1733 "PrintXQuery.cpp.template"
                                                                    for (size_t k = 2; k <= grammar->k; ++k)
                                                                    {
                                                            #line 2417 "PrintXQuery.cpp"
  append(L", 0, 0, 0");
                                                            #line 1735 "PrintXQuery.cpp.template"
                                                                    }
                                                            #line 2421 "PrintXQuery.cpp"
  append(L", false()");
                                                            #line 1736 "PrintXQuery.cpp.template"
                                                                    if (memoization)
                                                                    {
                                                            #line 2426 "PrintXQuery.cpp"
  append(L", <memo/>");
                                                            #line 1738 "PrintXQuery.cpp.template"
                                                                    }
                                                            #line 2430 "PrintXQuery.cpp"
  append(L")\n");
  append(L"  let $state := p:predict($input, $state, ");
                                                            #line 1740 "PrintXQuery.cpp.template"
                                                                    print(format.toString<wchar_t>((*grammar->states)[grammar->whitespace->state]->getStateId()));
                                                                    if (grammar->useGlr)
                                                                    {
                                                            #line 2437 "PrintXQuery.cpp"
  append(L", $id");
                                                            #line 1743 "PrintXQuery.cpp.template"
                                                                    }
                                                            #line 2441 "PrintXQuery.cpp"
  append(L")\n");
  append(L"  let $e0 := $state[$p:e0]\n");
  append(L"  let $state := p:parse");
                                                            #line 1746 "PrintXQuery.cpp.template"
                                                                    if (grammar->useGlr)
                                                                    {
                                                            #line 2448 "PrintXQuery.cpp"
  append(L"-glr");
                                                            #line 1748 "PrintXQuery.cpp.template"
                                                                    }
                                                            #line 2452 "PrintXQuery.cpp"
  append(L"($input, -1");
                                                            #line 1749 "PrintXQuery.cpp.template"
                                                                    if (grammar->useGlr)
                                                                    {
                                                            #line 2457 "PrintXQuery.cpp"
  append(L", 0, p:thread(0, false()");
                                                            #line 1751 "PrintXQuery.cpp.template"
                                                                    }
                                                            #line 2461 "PrintXQuery.cpp"
  append(L", ");
                                                            #line 1752 "PrintXQuery.cpp.template"
                                                                    print(format.toString<wchar_t>((*grammar->states)[grammar->whitespace->state]->getStateId()));
                                                            #line 2465 "PrintXQuery.cpp"
  append(L", $state[$p:lk], -1, $e0, $e0, $e0, (1, -1, 0), $state");
                                                            #line 1754 "PrintXQuery.cpp.template"
                                                                    if (grammar->useGlr)
                                                                    {
                                                            #line 2470 "PrintXQuery.cpp"
  append(L")");
                                                            #line 1756 "PrintXQuery.cpp.template"
                                                                    }
                                                            #line 2474 "PrintXQuery.cpp"
  append(L")");
                                                            #line 1758 "PrintXQuery.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 2480 "PrintXQuery.cpp"
  append(L"\n");
  append(L"  let $state := p:try-");
                                                            #line 1762 "PrintXQuery.cpp.template"
                                                                    print(grammar->whitespace->name);
                                                            #line 2485 "PrintXQuery.cpp"
  append(L"($input, (0, $begin, $begin, $match");
                                                            #line 1763 "PrintXQuery.cpp.template"
                                                                    for (size_t k = 2; k <= grammar->k; ++k)
                                                                    {
                                                            #line 2490 "PrintXQuery.cpp"
  append(L", 0, 0, 0");
                                                            #line 1765 "PrintXQuery.cpp.template"
                                                                    }
                                                            #line 2494 "PrintXQuery.cpp"
  append(L", false()");
                                                            #line 1766 "PrintXQuery.cpp.template"
                                                                    if (memoization)
                                                                    {
                                                            #line 2499 "PrintXQuery.cpp"
  append(L", <memo/>");
                                                            #line 1769 "PrintXQuery.cpp.template"
                                                                    }
                                                            #line 2503 "PrintXQuery.cpp"
  append(L"))");
                                                            #line 1771 "PrintXQuery.cpp.template"
                                                                  }
                                                            #line 2507 "PrintXQuery.cpp"
  append(L"\n");
  append(L"  return p:matchW($input, $state[$p:e0], $token-set");
                                                            #line 1774 "PrintXQuery.cpp.template"
                                                                    if (grammar->useGlr)
                                                                    {
                                                            #line 2513 "PrintXQuery.cpp"
  append(L", $id");
                                                            #line 1776 "PrintXQuery.cpp.template"
                                                                    }
                                                            #line 2517 "PrintXQuery.cpp"
  append(L")");
                                                            #line 1777 "PrintXQuery.cpp.template"
                                                                }
                                                            #line 2521 "PrintXQuery.cpp"
  append(L"\n");
  append(L"else\n");
  append(L"  $match");
                                                            #line 1780 "PrintXQuery.cpp.template"
                                                                setIndent(0);
                                                            #line 2527 "PrintXQuery.cpp"
  append(L"\n");
  append(L"};\n");
                                                            #line 1783 "PrintXQuery.cpp.template"
                                                                size_t lwc = grammar->tables && grammar->k >= grammar->tables && anyWhitespace
                                                                           ? grammar->k
                                                                           : grammar->lookaheadSets.lookaheadWCount;
                                                                printLookaheadMethods(lwc, true);
                                                              }
                                                              size_t lc = isLrParser && anyWhitespace
                                                                        ? 0
                                                                        : grammar->tables && grammar->k >= grammar->tables && ! anyWhitespace
                                                                        ? grammar->k
                                                                        : grammar->lookaheadSets.lookaheadCount;
                                                              printLookaheadMethods(lc, false);
                                                              if (tree && ! isLrParser)
                                                              {
                                                            #line 2544 "PrintXQuery.cpp"
  append(L"\n");
  append(L"(:");
  append(L"~");
  append(L"\n");
  append(L" : Reduce the result stack, creating a nonterminal element. Pop\n");
  append(L" : $count elements off the stack, wrap them in a new element\n");
  append(L" : named $name, and push the new element.\n");
  append(L" :\n");
  append(L" : @param $state lexer state, error indicator, and result stack.\n");
  append(L" : @param $name the name of the result node.\n");
  append(L" : @param $count the number of child nodes.");
                                                            #line 1804 "PrintXQuery.cpp.template"
                                                                if (! noPosition)
                                                                {
                                                            #line 2559 "PrintXQuery.cpp"
  append(L"\n");
  append(L" : @param $begin the input index where the nonterminal begins.\n");
  append(L" : @param $end the input index where the nonterminal ends.");
                                                            #line 1808 "PrintXQuery.cpp.template"
                                                                }
                                                            #line 2565 "PrintXQuery.cpp"
  append(L"\n");
  append(L" : @return the updated state.\n");
  append(L" :)\n");
  append(L"declare function p:reduce($state as item()+, $name as xs:string, $count as xs:integer");
                                                            #line 1813 "PrintXQuery.cpp.template"
                                                                if (! noPosition)
                                                                {
                                                            #line 2573 "PrintXQuery.cpp"
  append(L", $begin as xs:integer, $end as xs:integer");
                                                            #line 1816 "PrintXQuery.cpp.template"
                                                                }
                                                            #line 2577 "PrintXQuery.cpp"
  append(L") as item()+\n");
  append(L"{\n");
  append(L"  subsequence($state, 1, $count),\n");
  append(L"  element {$name}\n");
  append(L"  {\n");
  append(L"    subsequence($state, $count + 1)\n");
  append(L"  }\n");
  append(L"};\n");
                                                            #line 1825 "PrintXQuery.cpp.template"
                                                              }
                                                              if (memoization)
                                                              {
                                                                const wchar_t *factor = format.toString<wchar_t>(Math::powerof(2, Math::bits(grammar->conflictCount)));
                                                            #line 2591 "PrintXQuery.cpp"
  append(L"\n");
  append(L"(:");
  append(L"~");
  append(L"\n");
  append(L" : Strip result from lexer state, in order to avoid carrying it while\n");
  append(L" : backtracking.\n");
  append(L" :\n");
  append(L" : @param $state the lexer state after an alternative failed.\n");
  append(L" : @return the updated state.\n");
  append(L" :)\n");
  append(L"declare function p:strip-result($state as item()+) as item()+\n");
  append(L"{\n");
  append(L"  subsequence($state, 1, $p:memo)\n");
  append(L"};\n");
                                                            #line 1841 "PrintXQuery.cpp.template"
                                                                if (restoreCalled)
                                                                {
                                                            #line 2609 "PrintXQuery.cpp"
  append(L"\n");
  append(L"(:");
  append(L"~");
  append(L"\n");
  append(L" : Restore lexer state after unsuccessfully trying an alternative,\n");
  append(L" : merging any memoization that was collected on the way.\n");
  append(L" :\n");
  append(L" : @param $backtrack the lexer state before backtracking started.\n");
  append(L" : @param $state the lexer state after an alternative failed.\n");
  append(L" : @return the updated state.\n");
  append(L" :)\n");
  append(L"declare function p:restore($backtrack as item()+,\n");
  append(L"                           $state as item()+) as item()+\n");
  append(L"{\n");
  append(L"  subsequence($backtrack, 1, $p:memo - 1),\n");
  append(L"  element memo\n");
  append(L"  {\n");
  append(L"    let $errors := ($state[$p:memo], $state[$p:error])[.]\n");
  append(L"    return $errors[@e = max($errors/xs:integer(@e))][last()]/@*,\n");
  append(L"    $state[$p:memo]/value\n");
  append(L"  }\n");
  append(L"};\n");
                                                            #line 1863 "PrintXQuery.cpp.template"
                                                                }
                                                            #line 2634 "PrintXQuery.cpp"
  append(L"\n");
  append(L"(:");
  append(L"~");
  append(L"\n");
  append(L" : Memoize the backtracking result that was computed at decision point\n");
  append(L" : $dpi for input position $e0. Reconstruct state from the parameters.\n");
  append(L" :\n");
  append(L" : @param $state the lexer state to be restored.\n");
  append(L" : @param $update the lexer state containing updates.\n");
  append(L" : @param $dpi the decision point id.\n");
  append(L" : @param $e0 the input position.\n");
  append(L" : @param $v the id of the successful alternative.\n");
  append(L" : @param $lk the new lookahead code.\n");
  append(L" : @return the reconstructed state.\n");
  append(L" :)\n");
  append(L"declare function p:memoize($state as item()+,\n");
  append(L"                           $update as item()+,\n");
  append(L"                           $dpi as xs:integer,\n");
  append(L"                           $e0 as xs:integer,\n");
  append(L"                           $v as xs:integer,\n");
  append(L"                           $lk as xs:integer) as item()+\n");
  append(L"{\n");
  append(L"  $lk,\n");
  append(L"  subsequence($state, $p:b0, $p:memo - $p:b0),\n");
  append(L"  let $memo := $update[$p:memo]\n");
  append(L"  let $errors := ($memo, $update[$p:error])[.]\n");
  append(L"  return\n");
  append(L"    element memo\n");
  append(L"    {\n");
  append(L"      $errors[@e = max($errors/xs:integer(@e))][last()]/@*,\n");
  append(L"      $memo/value,\n");
  append(L"      element value {attribute key {$e0 * ");
                                                            #line 1893 "PrintXQuery.cpp.template"
                                                                print(factor);
                                                            #line 2669 "PrintXQuery.cpp"
  append(L" + $dpi}, $v}\n");
  append(L"    },\n");
  append(L"  subsequence($state, $p:memo + 1)\n");
  append(L"};\n");
  append(L"\n");
  append(L"(:");
  append(L"~");
  append(L"\n");
  append(L" : Retrieve memoized backtracking result for decision point $dpi\n");
  append(L" : and input position $state[$p:e0] into $state[$p:lk].\n");
  append(L" :\n");
  append(L" : @param $state lexer state, error indicator, and result stack.\n");
  append(L" : @param $dpi the decision point id.\n");
  append(L" : @return the updated state.\n");
  append(L" :)\n");
  append(L"declare function p:memoized($state as item()+, $dpi as xs:integer) as item()+\n");
  append(L"{\n");
  append(L"  let $value := data($state[$p:memo]/value[@key = $state[$p:e0] * ");
                                                            #line 1910 "PrintXQuery.cpp.template"
                                                                print(factor);
                                                            #line 2690 "PrintXQuery.cpp"
  append(L" + $dpi])\n");
  append(L"  return\n");
  append(L"  (\n");
  append(L"    if ($value) then $value else 0,\n");
  append(L"    subsequence($state, $p:lk + 1)\n");
  append(L"  )\n");
  append(L"};\n");
                                                            #line 1918 "PrintXQuery.cpp.template"
                                                              }
                                                            }

                                                            void PrintXQuery::printLookaheadMethods(size_t lookaheadMethods, bool withWhitespace)
                                                            {
                                                              for (size_t k = 1; k <= lookaheadMethods; ++k)
                                                              {
                                                            #line 2706 "PrintXQuery.cpp"
  append(L"\n");
  append(L"(:");
  append(L"~");
  append(L"\n");
  append(L" : Lookahead one token on level ");
                                                            #line 1927 "PrintXQuery.cpp.template"
                                                                print(format.toString<wchar_t>(k));
                                                                if (withWhitespace)
                                                                {
                                                            #line 2716 "PrintXQuery.cpp"
  append(L" with whitespace skipping");
                                                            #line 1930 "PrintXQuery.cpp.template"
                                                                }
                                                            #line 2720 "PrintXQuery.cpp"
  append(L".\n");
  append(L" :");
                                                            #line 1932 "PrintXQuery.cpp.template"
                                                                if (k != 1 && unlimitedLookahead)
                                                                {
                                                            #line 2726 "PrintXQuery.cpp"
  append(L"\n");
  append(L" : @param $prefix the prefix code representing lower level lookahead.");
                                                            #line 1936 "PrintXQuery.cpp.template"
                                                                }
                                                            #line 2731 "PrintXQuery.cpp"
  append(L"\n");
  append(L" : @param $set the code of the DFA entry state for the set of valid tokens.\n");
  append(L" : @param $input the input string.\n");
  append(L" : @param $state lexer state, error indicator, and result stack.");
                                                            #line 1941 "PrintXQuery.cpp.template"
                                                                if (grammar->useGlr)
                                                                {
                                                            #line 2739 "PrintXQuery.cpp"
  append(L"\n");
  append(L" : @param $id the parsing thread id.");
                                                            #line 1944 "PrintXQuery.cpp.template"
                                                                }
                                                            #line 2744 "PrintXQuery.cpp"
  append(L"\n");
  append(L" : @return the updated state.\n");
  append(L" :)\n");
  append(L"declare function p:lookahead");
                                                            #line 1948 "PrintXQuery.cpp.template"
                                                                print(format.toString<wchar_t>(k));
                                                                if (withWhitespace)
                                                                {
                                                            #line 2753 "PrintXQuery.cpp"
  append(L"W");
                                                            #line 1952 "PrintXQuery.cpp.template"
                                                                }
                                                            #line 2757 "PrintXQuery.cpp"
  append(L"(");
                                                            #line 1953 "PrintXQuery.cpp.template"
                                                                if (k != 1 && unlimitedLookahead)
                                                                {
                                                            #line 2762 "PrintXQuery.cpp"
  append(L"$prefix as xs:integer, ");
                                                            #line 1955 "PrintXQuery.cpp.template"
                                                                }
                                                            #line 2766 "PrintXQuery.cpp"
  append(L"$set as xs:integer, $input as xs:string, $state as item()+");
                                                            #line 1957 "PrintXQuery.cpp.template"
                                                                if (grammar->useGlr)
                                                                {
                                                            #line 2771 "PrintXQuery.cpp"
  append(L", $id as xs:integer");
                                                            #line 1960 "PrintXQuery.cpp.template"
                                                                }
                                                            #line 2775 "PrintXQuery.cpp"
  append(L") as item()+\n");
  append(L"{");
                                                            #line 1962 "PrintXQuery.cpp.template"
                                                                if (k == 1)
                                                                {
                                                            #line 2781 "PrintXQuery.cpp"
  append(L"\n");
  append(L"  if ($state[$p:l1] ne 0) then\n");
  append(L"    $state\n");
  append(L"  else\n");
  append(L"    let $match :=");
                                                            #line 1968 "PrintXQuery.cpp.template"
                                                                  increaseIndent();
                                                                }
                                                                else
                                                                {
                                                            #line 2792 "PrintXQuery.cpp"
  append(L"\n");
  append(L"  let $match :=\n");
  append(L"    if ($state[$p:l");
                                                            #line 1974 "PrintXQuery.cpp.template"
                                                                  print(format.toString<wchar_t>(k));
                                                            #line 2798 "PrintXQuery.cpp"
  append(L"] ne 0) then\n");
  append(L"      subsequence($state, $p:l");
                                                            #line 1976 "PrintXQuery.cpp.template"
                                                                  print(format.toString<wchar_t>(k));
                                                            #line 2803 "PrintXQuery.cpp"
  append(L", ");
                                                            #line 1977 "PrintXQuery.cpp.template"
                                                                  print(format.toString<wchar_t>(k < grammar->k ? 6 : 3));
                                                            #line 2807 "PrintXQuery.cpp"
  append(L")\n");
  append(L"    else");
                                                            #line 1979 "PrintXQuery.cpp.template"
                                                                }
                                                                if (k < grammar->k)
                                                                {
                                                            #line 2814 "PrintXQuery.cpp"
  append(L"\n");
  append(L"    (");
                                                            #line 1983 "PrintXQuery.cpp.template"
                                                                }
                                                            #line 2819 "PrintXQuery.cpp"
  append(L"\n");
  append(L"      p:match");
                                                            #line 1985 "PrintXQuery.cpp.template"
                                                                if (withWhitespace)
                                                                {
                                                            #line 2825 "PrintXQuery.cpp"
  append(L"W");
                                                            #line 1988 "PrintXQuery.cpp.template"
                                                                }
                                                            #line 2829 "PrintXQuery.cpp"
  append(L"($input, $state[$p:e");
                                                            #line 1989 "PrintXQuery.cpp.template"
                                                                print(format.toString<wchar_t>(k - 1));
                                                            #line 2833 "PrintXQuery.cpp"
  append(L"], $set");
                                                            #line 1990 "PrintXQuery.cpp.template"
                                                                if (grammar->useGlr)
                                                                {
                                                            #line 2838 "PrintXQuery.cpp"
  append(L", $id");
                                                            #line 1992 "PrintXQuery.cpp.template"
                                                                }
                                                            #line 2842 "PrintXQuery.cpp"
  append(L")");
                                                            #line 1993 "PrintXQuery.cpp.template"
                                                                if (k < grammar->k)
                                                                {
                                                            #line 2847 "PrintXQuery.cpp"
  append(L",\n");
  append(L"      0, 0, 0\n");
  append(L"    )");
                                                            #line 1997 "PrintXQuery.cpp.template"
                                                                }
                                                            #line 2853 "PrintXQuery.cpp"
  append(L"\n");
  append(L"  return\n");
  append(L"  (\n");
  append(L"    ");
                                                            #line 2001 "PrintXQuery.cpp.template"
                                                                if (grammar->tables && k >= grammar->tables)
                                                                {
                                                            #line 2861 "PrintXQuery.cpp"
  append(L"subsequence($state, 1, ");
                                                            #line 2004 "PrintXQuery.cpp.template"
                                                                  print(format.toString<wchar_t>(k * 3));
                                                            #line 2865 "PrintXQuery.cpp"
  append(L"),");
                                                            #line 2005 "PrintXQuery.cpp.template"
                                                                }
                                                                else
                                                                {
                                                                  if (k != 1 && unlimitedLookahead)
                                                                  {
                                                            #line 2873 "PrintXQuery.cpp"
  append(L"$match[1] + $prefix");
                                                            #line 2010 "PrintXQuery.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 2879 "PrintXQuery.cpp"
  append(L"$match[1]");
                                                            #line 2013 "PrintXQuery.cpp.template"
                                                                    switch (k)
                                                                    {
                                                                    case 1: break;
                                                                    case 2:
                                                            #line 2886 "PrintXQuery.cpp"
  append(L" * ");
                                                            #line 2017 "PrintXQuery.cpp.template"
                                                                      print(format.toString<wchar_t>(Math::powerof(2, ((int) k - 1) * grammar->tokenSequenceFactory->tokenBits())));
                                                            #line 2890 "PrintXQuery.cpp"
  append(L" + $state[$p:l1]");
                                                            #line 2018 "PrintXQuery.cpp.template"
                                                                      break;
                                                                    default:
                                                            #line 2895 "PrintXQuery.cpp"
  append(L" * ");
                                                            #line 2020 "PrintXQuery.cpp.template"
                                                                      print(format.toString<wchar_t>(Math::powerof(2, ((int) k - 1) * grammar->tokenSequenceFactory->tokenBits())));
                                                            #line 2899 "PrintXQuery.cpp"
  append(L" + $state[$p:lk]");
                                                            #line 2021 "PrintXQuery.cpp.template"
                                                                      break;
                                                                    }
                                                                  }
                                                            #line 2905 "PrintXQuery.cpp"
  append(L",\n");
  append(L"    subsequence($state, $p:b0, ");
                                                            #line 2025 "PrintXQuery.cpp.template"
                                                                  print(format.toString<wchar_t>(k * 3 - 1));
                                                            #line 2910 "PrintXQuery.cpp"
  append(L"),");
                                                            #line 2026 "PrintXQuery.cpp.template"
                                                                }
                                                            #line 2914 "PrintXQuery.cpp"
  append(L"\n");
  append(L"    $match,\n");
  append(L"    subsequence($state, ");
                                                            #line 2029 "PrintXQuery.cpp.template"
                                                                print(format.toString<wchar_t>(k * 3 + (grammar->k > k ? 7 : 4)));
                                                            #line 2920 "PrintXQuery.cpp"
  append(L")\n");
  append(L"  )");
                                                            #line 2031 "PrintXQuery.cpp.template"
                                                                if (k == 1) decreaseIndent();
                                                            #line 2925 "PrintXQuery.cpp"
  append(L"\n");
  append(L"};\n");
                                                            #line 2035 "PrintXQuery.cpp.template"
                                                              }
                                                              setIndent(0);
                                                            }

                                                            void PrintXQuery::printEpilog(Grammar *node)
                                                            {
                                                              if (node->automaticSemicolonInsertion)
                                                              {
                                                            #line 2937 "PrintXQuery.cpp"
  append(L"\n");
  append(L"(:");
  append(L"~");
  append(L"\n");
  append(L" : Check whether the lookahead token is preceded by a line terminator.\n");
  append(L" :\n");
  append(L" : @param $input the input string.\n");
  append(L" : @param $state lexer state, error indicator, and result stack.\n");
  append(L" : @return the updated state.\n");
  append(L" :)\n");
  append(L"declare function p:follows-line-terminator($input as xs:string,\n");
  append(L"                                           $state as item()+\n");
  append(L"                                          ) as item()+\n");
  append(L"{\n");
  append(L"  let $begin := if ($state[$p:e0] eq $state[$p:b1]) then $state[$p:b0] else $state[$p:e0]\n");
  append(L"  let $preceding-whitespace := substring($input, $begin, $state[$p:b1] - $begin)\n");
  append(L"  return string-to-codepoints($preceding-whitespace) = (10, 13, 8232, 8233)\n");
  append(L"};\n");
                                                            #line 2059 "PrintXQuery.cpp.template"
                                                              }
                                                              for (Node *n = node->nonTerminals; n; n = n->followingSibling)
                                                              {
                                                                Production *p = static_cast <Production *> (n);
                                                                if (p->isStartSymbol())
                                                                {
                                                            #line 2963 "PrintXQuery.cpp"
  append(L"\n");
  append(L"(:");
  append(L"~");
  append(L"\n");
  append(L" : Parse start symbol ");
                                                            #line 2067 "PrintXQuery.cpp.template"
                                                                  print(p->name);
                                                            #line 2971 "PrintXQuery.cpp"
  append(L" from given string.\n");
  append(L" :\n");
  append(L" : @param $s the string to be parsed.\n");
  append(L" : @return the result as generated by parser actions.\n");
  append(L" :)\n");
  append(L"declare function p:");
                                                            #line 2073 "PrintXQuery.cpp.template"
                                                                  print(methodPrefix);
                                                            #line 2980 "PrintXQuery.cpp"
  append(L"-");
                                                            #line 2074 "PrintXQuery.cpp.template"
                                                                  print(p->name);
                                                            #line 2984 "PrintXQuery.cpp"
  append(L"($s as xs:string) as item()*\n");
  append(L"{\n");
  append(L"  let $state := (0, 1, 1");
                                                            #line 2077 "PrintXQuery.cpp.template"
                                                                  for (size_t k = 1; k <= grammar->k; ++k)
                                                                  {
                                                            #line 2991 "PrintXQuery.cpp"
  append(L", 0, 0, 0");
                                                            #line 2079 "PrintXQuery.cpp.template"
                                                                  }
                                                            #line 2995 "PrintXQuery.cpp"
  append(L", false()");
                                                            #line 2080 "PrintXQuery.cpp.template"
                                                                  if (memoization)
                                                                  {
                                                            #line 3000 "PrintXQuery.cpp"
  append(L", <memo/>");
                                                            #line 2082 "PrintXQuery.cpp.template"
                                                                  }
                                                            #line 3004 "PrintXQuery.cpp"
  append(L")");
                                                            #line 2083 "PrintXQuery.cpp.template"
                                                                  if (isLrParser)
                                                                  {
                                                            #line 3009 "PrintXQuery.cpp"
  append(L"\n");
  append(L"  let $state := p:predict($s, $state, ");
                                                            #line 2086 "PrintXQuery.cpp.template"
                                                                    print(format.toString<wchar_t>((*grammar->states)[p->state]->getStateId()));
                                                                    if (grammar->useGlr)
                                                                    {
                                                            #line 3016 "PrintXQuery.cpp"
  append(L", 0");
                                                            #line 2089 "PrintXQuery.cpp.template"
                                                                    }
                                                            #line 3020 "PrintXQuery.cpp"
  append(L")\n");
  append(L"  let $state := p:parse");
                                                            #line 2091 "PrintXQuery.cpp.template"
                                                                    if (grammar->useGlr)
                                                                    {
                                                            #line 3026 "PrintXQuery.cpp"
  append(L"-glr");
                                                            #line 2093 "PrintXQuery.cpp.template"
                                                                    }
                                                            #line 3030 "PrintXQuery.cpp"
  append(L"($s, ");
                                                            #line 2094 "PrintXQuery.cpp.template"
                                                                    print(format.toString<wchar_t>(p->nonterminalCode));
                                                                    if (grammar->useGlr)
                                                                    {
                                                            #line 3036 "PrintXQuery.cpp"
  append(L", 0, p:thread(0, false()");
                                                            #line 2097 "PrintXQuery.cpp.template"
                                                                    }
                                                            #line 3040 "PrintXQuery.cpp"
  append(L", ");
                                                            #line 2098 "PrintXQuery.cpp.template"
                                                                    print(format.toString<wchar_t>((*grammar->states)[p->state]->getStateId()));
                                                            #line 3044 "PrintXQuery.cpp"
  append(L", $state[$p:lk], -1, 1, 1, 1, (1, -1, 0), $state");
                                                            #line 2100 "PrintXQuery.cpp.template"
                                                                    if (grammar->useGlr)
                                                                    {
                                                            #line 3049 "PrintXQuery.cpp"
  append(L")");
                                                            #line 2102 "PrintXQuery.cpp.template"
                                                                    }
                                                            #line 3053 "PrintXQuery.cpp"
  append(L")");
                                                            #line 2104 "PrintXQuery.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 3059 "PrintXQuery.cpp"
  append(L"\n");
  append(L"  let $state := p:parse-");
                                                            #line 2108 "PrintXQuery.cpp.template"
                                                                    print(p->name);
                                                            #line 3064 "PrintXQuery.cpp"
  append(L"($s, $state)");
                                                            #line 2109 "PrintXQuery.cpp.template"
                                                                  }
                                                            #line 3068 "PrintXQuery.cpp"
  append(L"\n");
  append(L"  let $error := $state[$p:error]\n");
  append(L"  return\n");
  append(L"    if ($error) then");
                                                            #line 2113 "PrintXQuery.cpp.template"
                                                                  if (tree && grammar->useGlr)
                                                                  {
                                                            #line 3076 "PrintXQuery.cpp"
  append(L"\n");
  append(L"    (\n");
  append(L"      $error/AMBIGUOUS,");
                                                            #line 2117 "PrintXQuery.cpp.template"
                                                                  }
                                                            #line 3082 "PrintXQuery.cpp"
  append(L"\n");
  append(L"      element ERROR {$error/@*, p:error-message($s, $error)}");
                                                            #line 2119 "PrintXQuery.cpp.template"
                                                                  if (tree && grammar->useGlr)
                                                                  {
                                                            #line 3088 "PrintXQuery.cpp"
  append(L"\n");
  append(L"    )");
                                                            #line 2123 "PrintXQuery.cpp.template"
                                                                  }
                                                            #line 3093 "PrintXQuery.cpp"
  append(L"\n");
  append(L"    else\n");
  append(L"      subsequence($state, $p:result)\n");
  append(L"};\n");
                                                            #line 2128 "PrintXQuery.cpp.template"
                                                                }
                                                              }
                                                              if (debug)
                                                              {
                                                            #line 3103 "PrintXQuery.cpp"
  append(L"\n");
  append(L"declare function debug:enter($name, $state)\n");
  append(L"{\n");
  append(L"  p:trace(concat(\"enter \", $name, \" l1=\", $state[$p:l1], \" e1=\", $state[$p:e1], \" memo/e=\", $state[$p:memo]/@e, \" error/e=\", if ($state[$p:error] instance of xs:boolean) then $state[$p:error] else $state[$p:error]/@e))\n");
  append(L"};\n");
  append(L"\n");
  append(L"declare function debug:leave($name, $state)\n");
  append(L"{\n");
  append(L"  p:trace(concat(\"leave \", $name, \" l1=\", $state[$p:l1], \" e1=\", $state[$p:e1], \" memo/e=\", $state[$p:memo]/@e, \" error/e=\", if ($state[$p:error] instance of xs:boolean) then $state[$p:error] else $state[$p:error]/@e))\n");
  append(L"};\n");
                                                            #line 2142 "PrintXQuery.cpp.template"
                                                              }
                                                              if (trace && ! isLrParser)
                                                              {
                                                            #line 3118 "PrintXQuery.cpp"
  append(L"\n");
  append(L"(:");
  append(L"~");
  append(L"\n");
  append(L" : Trace LL processing of a nonterminal.\n");
  append(L" :\n");
  append(L" : @param $state lexer state, error indicator, and result stack.\n");
  append(L" : @param $method processing method type.\n");
  append(L" : @param $occasion the current step.\n");
  append(L" : @param $name the nonterminal name.\n");
  append(L" : @return the empty sequence.\n");
  append(L" :)\n");
  append(L"declare function p:trace-nonterminal($state as item()+,\n");
  append(L"                                     $method as xs:string,\n");
  append(L"                                     $occasion as xs:string,\n");
  append(L"                                     $name as xs:string) as xs:string?\n");
  append(L"{\n");
  append(L"  p:trace\n");
  append(L"  (\n");
  append(L"    string-join\n");
  append(L"    (\n");
  append(L"      (\n");
  append(L"        \"  <\",\n");
  append(L"        $method,\n");
  append(L"        \" \",\n");
  append(L"        $occasion,\n");
  append(L"        \"nonterminal=\"\"\",\n");
  append(L"        $name,\n");
  append(L"        \"\"\"\",\n");
  append(L"        if ($state[$p:l1] le 0) then () else (\" input=\"\"\", p:xml-escape(p:lookahead-string($state)), \"\"\"\"),\n");
  append(L"        \"/>\"\n");
  append(L"      ),\n");
  append(L"      \"\"\n");
  append(L"    )\n");
  append(L"  )\n");
  append(L"};\n");
                                                            #line 2179 "PrintXQuery.cpp.template"
                                                              }
                                                              if (main)
                                                              {
                                                            #line 3159 "PrintXQuery.cpp"
  append(L"\n");
  append(L"(:");
  append(L"~");
  append(L"\n");
  append(L" : The input filename, or string, if surrounded by curly braces.\n");
  append(L" :)\n");
  append(L"declare variable $input as xs:string external;\n");
  append(L"\n");
  append(L"let $result :=");
                                                            #line 2189 "PrintXQuery.cpp.template"
                                                                if (trace)
                                                                {
                                                            #line 3172 "PrintXQuery.cpp"
  append(L"\n");
  append(L"(\n");
  append(L"  p:trace(\"<trace>\"),");
                                                            #line 2193 "PrintXQuery.cpp.template"
                                                                }
                                                            #line 3178 "PrintXQuery.cpp"
  append(L"\n");
  append(L"  if (matches($input, \"");
  append(L"^");
  append(L"\\{.*\\}$\")) then\n");
  append(L"    p:");
                                                            #line 2196 "PrintXQuery.cpp.template"
                                                                print(methodPrefix);
                                                            #line 3186 "PrintXQuery.cpp"
  append(L"-");
                                                            #line 2197 "PrintXQuery.cpp.template"
                                                                print(grammar->startSymbol()->name);
                                                            #line 3190 "PrintXQuery.cpp"
  append(L"(substring($input, 2, string-length($input) - 2))\n");
  append(L"  else\n");
  append(L"    p:");
                                                            #line 2200 "PrintXQuery.cpp.template"
                                                                print(methodPrefix);
                                                            #line 3196 "PrintXQuery.cpp"
  append(L"-");
                                                            #line 2201 "PrintXQuery.cpp.template"
                                                                print(grammar->startSymbol()->name);
                                                            #line 3200 "PrintXQuery.cpp"
  append(L"(unparsed-text($input, \"utf-8\"))");
                                                            #line 2202 "PrintXQuery.cpp.template"
                                                                if (trace)
                                                                {
                                                            #line 3205 "PrintXQuery.cpp"
  append(L",\n");
  append(L"  p:trace(\"</trace>\")\n");
  append(L")");
                                                            #line 2206 "PrintXQuery.cpp.template"
                                                                }
                                                            #line 3211 "PrintXQuery.cpp"
  append(L"\n");
  append(L"return\n");
  append(L"  if (empty($result/self::ERROR)) then\n");
  append(L"    $result\n");
  append(L"  else");
                                                            #line 2211 "PrintXQuery.cpp.template"
                                                                if (tree && grammar->useGlr)
                                                                {
                                                            #line 3220 "PrintXQuery.cpp"
  append(L"\n");
  append(L"  (\n");
  append(L"    $result[not(self::ERROR)],\n");
  append(L"    \"&#xA;\",");
                                                            #line 2216 "PrintXQuery.cpp.template"
                                                                }
                                                            #line 3227 "PrintXQuery.cpp"
  append(L"\n");
  append(L"    error(xs:QName(\"p:");
                                                            #line 2218 "PrintXQuery.cpp.template"
                                                                print(methodPrefix);
                                                            #line 3232 "PrintXQuery.cpp"
  append(L"-");
                                                            #line 2219 "PrintXQuery.cpp.template"
                                                                print(grammar->startSymbol()->name);
                                                            #line 3236 "PrintXQuery.cpp"
  append(L"\"), concat(\"&#10;    \", replace($result");
                                                            #line 2221 "PrintXQuery.cpp.template"
                                                                if (tree && grammar->useGlr)
                                                                {
                                                            #line 3241 "PrintXQuery.cpp"
  append(L"[self::ERROR]");
                                                            #line 2224 "PrintXQuery.cpp.template"
                                                                }
                                                            #line 3245 "PrintXQuery.cpp"
  append(L", \"&#10;\", \"&#10;    \")))");
                                                            #line 2226 "PrintXQuery.cpp.template"
                                                                if (tree && grammar->useGlr)
                                                                {
                                                            #line 3250 "PrintXQuery.cpp"
  append(L"\n");
  append(L"  )");
                                                            #line 2229 "PrintXQuery.cpp.template"
                                                                }
                                                            #line 3255 "PrintXQuery.cpp"
  append(L"\n");
                                                            #line 2231 "PrintXQuery.cpp.template"
                                                              }
                                                            }

                                                            void PrintXQuery::printVariables()
                                                            {
                                                            #line 3263 "PrintXQuery.cpp"
  append(L"\n");
  append(L"(:");
  append(L"~");
  append(L"\n");
  append(L" : The index of the lexer state for accessing the combined\n");
  append(L" : (i.e. level > 1) lookahead code.\n");
  append(L" :)\n");
  append(L"declare variable $p:lk as xs:integer := 1;\n");
  append(L"\n");
  append(L"(:");
  append(L"~");
  append(L"\n");
  append(L" : The index of the lexer state for accessing the position in the\n");
  append(L" : input string of the begin of the token that has been consumed.\n");
  append(L" :)\n");
  append(L"declare variable $p:b0 as xs:integer := 2;\n");
  append(L"\n");
  append(L"(:");
  append(L"~");
  append(L"\n");
  append(L" : The index of the lexer state for accessing the position in the\n");
  append(L" : input string of the end of the token that has been consumed.\n");
  append(L" :)\n");
  append(L"declare variable $p:e0 as xs:integer := 3;");
                                                            #line 2253 "PrintXQuery.cpp.template"
                                                              int stateIndex = 3;
                                                              for (size_t k = 1; k <= grammar->k; ++k)
                                                              {
                                                            #line 3292 "PrintXQuery.cpp"
  append(L"\n");
  append(L"\n");
  append(L"(:");
  append(L"~");
  append(L"\n");
  append(L" : The index of the lexer state for accessing the code of the\n");
  append(L" : level-");
                                                            #line 2260 "PrintXQuery.cpp.template"
                                                                print(format.toString<wchar_t>(k));
                                                            #line 3302 "PrintXQuery.cpp"
  append(L"-lookahead token.\n");
  append(L" :)\n");
  append(L"declare variable $p:l");
                                                            #line 2263 "PrintXQuery.cpp.template"
                                                                print(format.toString<wchar_t>(k));
                                                            #line 3308 "PrintXQuery.cpp"
  append(L" as xs:integer := ");
                                                            #line 2264 "PrintXQuery.cpp.template"
                                                                print(format.toString<wchar_t>(++stateIndex));
                                                            #line 3312 "PrintXQuery.cpp"
  append(L";\n");
  append(L"\n");
  append(L"(:");
  append(L"~");
  append(L"\n");
  append(L" : The index of the lexer state for accessing the position in the\n");
  append(L" : input string of the begin of the level-");
                                                            #line 2269 "PrintXQuery.cpp.template"
                                                                print(format.toString<wchar_t>(k));
                                                            #line 3322 "PrintXQuery.cpp"
  append(L"-lookahead token.\n");
  append(L" :)\n");
  append(L"declare variable $p:b");
                                                            #line 2272 "PrintXQuery.cpp.template"
                                                                print(format.toString<wchar_t>(k));
                                                            #line 3328 "PrintXQuery.cpp"
  append(L" as xs:integer := ");
                                                            #line 2273 "PrintXQuery.cpp.template"
                                                                print(format.toString<wchar_t>(++stateIndex));
                                                            #line 3332 "PrintXQuery.cpp"
  append(L";\n");
  append(L"\n");
  append(L"(:");
  append(L"~");
  append(L"\n");
  append(L" : The index of the lexer state for accessing the position in the\n");
  append(L" : input string of the end of the level-");
                                                            #line 2278 "PrintXQuery.cpp.template"
                                                                print(format.toString<wchar_t>(k));
                                                            #line 3342 "PrintXQuery.cpp"
  append(L"-lookahead token.\n");
  append(L" :)\n");
  append(L"declare variable $p:e");
                                                            #line 2281 "PrintXQuery.cpp.template"
                                                                print(format.toString<wchar_t>(k));
                                                            #line 3348 "PrintXQuery.cpp"
  append(L" as xs:integer := ");
                                                            #line 2282 "PrintXQuery.cpp.template"
                                                                print(format.toString<wchar_t>(++stateIndex));
                                                            #line 3352 "PrintXQuery.cpp"
  append(L";");
                                                            #line 2283 "PrintXQuery.cpp.template"
                                                              }
                                                            #line 3356 "PrintXQuery.cpp"
  append(L"\n");
  append(L"\n");
  append(L"(:");
  append(L"~");
  append(L"\n");
  append(L" : The index of the lexer state for accessing the token code that\n");
  append(L" : was expected when an error was found.\n");
  append(L" :)\n");
  append(L"declare variable $p:error as xs:integer := ");
                                                            #line 2290 "PrintXQuery.cpp.template"
                                                              print(format.toString<wchar_t>(++stateIndex));
                                                            #line 3368 "PrintXQuery.cpp"
  append(L";\n");
                                                            #line 2292 "PrintXQuery.cpp.template"
                                                              if (memoization)
                                                              {
                                                            #line 3373 "PrintXQuery.cpp"
  append(L"\n");
  append(L"(:");
  append(L"~");
  append(L"\n");
  append(L" : The index of the lexer state for accessing the memoization\n");
  append(L" : of backtracking results.\n");
  append(L" :)\n");
  append(L"declare variable $p:memo as xs:integer := ");
                                                            #line 2299 "PrintXQuery.cpp.template"
                                                                print(format.toString<wchar_t>(++stateIndex));
                                                            #line 3384 "PrintXQuery.cpp"
  append(L";\n");
                                                            #line 2301 "PrintXQuery.cpp.template"
                                                              }
                                                            #line 3388 "PrintXQuery.cpp"
  append(L"\n");
  append(L"(:");
  append(L"~");
  append(L"\n");
  append(L" : The index of the lexer state that points to the first entry\n");
  append(L" : used for collecting action results.\n");
  append(L" :)\n");
  append(L"declare variable $p:result as xs:integer := ");
                                                            #line 2307 "PrintXQuery.cpp.template"
                                                              print(format.toString<wchar_t>(++stateIndex));
                                                            #line 3399 "PrintXQuery.cpp"
  append(L";");
                                                            #line 2309 "PrintXQuery.cpp.template"
                                                            }

                                                            void PrintXQuery::printProlog(Grammar *aNode)
                                                            {
                                                              if (! hasProlog)
                                                              {
                                                                if (main)
                                                                {
                                                            #line 3410 "PrintXQuery.cpp"
  append(L"\n");
  append(L"declare namespace p=\"");
                                                            #line 2318 "PrintXQuery.cpp.template"
                                                                  print(className);
                                                            #line 3415 "PrintXQuery.cpp"
  append(L"\";");
                                                            #line 2319 "PrintXQuery.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 3421 "PrintXQuery.cpp"
  append(L"\n");
  append(L"(:");
  append(L"~");
  append(L"\n");
  append(L" : The parser that was generated for the ");
                                                            #line 2324 "PrintXQuery.cpp.template"
                                                                  print(className);
                                                            #line 3429 "PrintXQuery.cpp"
  append(L" grammar.\n");
  append(L" :)\n");
  append(L"module namespace p=\"");
                                                            #line 2327 "PrintXQuery.cpp.template"
                                                                  print(className);
                                                            #line 3435 "PrintXQuery.cpp"
  append(L"\";");
                                                            #line 2328 "PrintXQuery.cpp.template"
                                                                }
                                                            #line 3439 "PrintXQuery.cpp"
  append(L"\n");
  append(L"declare default function namespace \"http://www.w3.org/2005/xpath-functions\";\n");
                                                            #line 2332 "PrintXQuery.cpp.template"
                                                                if (debug)
                                                                {
                                                            #line 3445 "PrintXQuery.cpp"
  append(L"declare namespace debug=\"DEBUG\";\n");
                                                            #line 2335 "PrintXQuery.cpp.template"
                                                                }
                                                              }
                                                            }

                                                            void PrintXQuery::PrintLoops::visitZeroOrMore(ZeroOrMore *node)
                                                            {
                                                              if (node->loopId == 0)
                                                              {
                                                                node->loopId = ++loopId;
                                                                Visitor::visitZeroOrMore(node);
                                                              }
                                                              if (px->methodPrefix == px->methodPrefixTry || node->production->runPayload)
                                                              {
                                                            #line 3461 "PrintXQuery.cpp"
  append(L"\n");
  append(L"(:");
  append(L"~");
  append(L"\n");
  append(L" : ");
                                                            #line 2350 "PrintXQuery.cpp.template"
                                                              if (px->methodPrefix != px->methodPrefixTry)
                                                              {
                                                            #line 3470 "PrintXQuery.cpp"
  append(L"Parse");
                                                            #line 2352 "PrintXQuery.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 3476 "PrintXQuery.cpp"
  append(L"Try parsing");
                                                            #line 2355 "PrintXQuery.cpp.template"
                                                              }
                                                            #line 3480 "PrintXQuery.cpp"
  append(L" the ");
                                                            #line 2356 "PrintXQuery.cpp.template"
                                                              px->print(px->format.toString<wchar_t>(node->loopId));
                                                              switch (node->loopId)
                                                              {
                                                              case 1:  append(L"st"); break;
                                                              case 2:  append(L"nd"); break;
                                                              case 3:  append(L"rd"); break;
                                                              default: append(L"th"); break;
                                                              }
                                                            #line 3491 "PrintXQuery.cpp"
  append(L" loop of production ");
                                                            #line 2364 "PrintXQuery.cpp.template"
                                                              px->print(node->production->name);
                                                            #line 3495 "PrintXQuery.cpp"
  append(L" (zero or more). Use\n");
  append(L" : tail recursion for iteratively updating the lexer state.\n");
  append(L" :\n");
  append(L" : @param $input the input string.\n");
  append(L" : @param $state lexer state, error indicator, and result stack.\n");
  append(L" : @return the updated state.\n");
  append(L" :)\n");
  append(L"declare function p:");
                                                            #line 2372 "PrintXQuery.cpp.template"
                                                              px->print(px->methodPrefix);
                                                            #line 3506 "PrintXQuery.cpp"
  append(L"-");
                                                            #line 2373 "PrintXQuery.cpp.template"
                                                              px->print(node->production->name);
                                                            #line 3510 "PrintXQuery.cpp"
  append(L"-");
                                                            #line 2374 "PrintXQuery.cpp.template"
                                                              px->print(px->format.toString<wchar_t>(node->loopId));
                                                            #line 3514 "PrintXQuery.cpp"
  append(L"($input as xs:string, $state as item()+)\n");
  append(L"{\n");
  append(L"  if ($state[$p:error]) then\n");
  append(L"    $state\n");
  append(L"  else");
                                                            #line 2379 "PrintXQuery.cpp.template"
                                                              px->increaseIndent(2);
                                                              bool hasLookahead =
                                                                px->printLookahead(node->k, *px->grammar->epsilon, 1, node->getLookahead(), node->findsLookahead);
                                                              px->automaticSemicolonInsertion(node);
                                                              bool nestedTry = px->methodPrefix == px->methodPrefixTry;
                                                              bool hasBacktracking =
                                                                px->printBacktracking(node,
                                                                                      node->getLookahead(),
                                                                                      node->conflictCaseId,
                                                                                      node->conflictId,
                                                                                      node->firstElementChild);
                                                              if (hasLookahead || hasBacktracking)
                                                              {
                                                            #line 3534 "PrintXQuery.cpp"
  append(L"\n");
  append(L"return");
                                                            #line 2393 "PrintXQuery.cpp.template"
                                                                px->increaseIndent();
                                                              }
                                                              const wchar_t *prefix = L"if (";
                                                              if (hasBacktracking && nestedTry)
                                                              {
                                                            #line 3543 "PrintXQuery.cpp"
  append(L"\n");
  append(L"if ($state[$p:lk] = -3) then\n");
  append(L"  p:");
                                                            #line 2400 "PrintXQuery.cpp.template"
                                                                px->print(px->methodPrefix);
                                                            #line 3549 "PrintXQuery.cpp"
  append(L"-");
                                                            #line 2401 "PrintXQuery.cpp.template"
                                                                px->print(node->production->name);
                                                            #line 3553 "PrintXQuery.cpp"
  append(L"-");
                                                            #line 2402 "PrintXQuery.cpp.template"
                                                                px->print(px->format.toString<wchar_t>(node->loopId));
                                                            #line 3557 "PrintXQuery.cpp"
  append(L"($input, $state)");
                                                            #line 2403 "PrintXQuery.cpp.template"
                                                                prefix = L"else if (";
                                                              }
                                                              MatchType matchType;
                                                              const TokenSequenceSet &match = node->firstElementChild->getMatch(matchType);
                                                              px->printMatch(node->getLookahead(),
                                                                             node->k,
                                                                             node->conflicts(node->k) == 0 ? 0 : matchType == IF ? 1 : 2,
                                                                             match,
                                                                             matchType == IF ? IFNOT : IF,
                                                                             1,
                                                                             prefix,
                                                                             L") then");
                                                            #line 3572 "PrintXQuery.cpp"
  append(L"\n");
  append(L"  $state\n");
  append(L"else");
                                                            #line 2417 "PrintXQuery.cpp.template"
                                                              px->Visitor::visitNodeWithChildren(node);
                                                            #line 3578 "PrintXQuery.cpp"
  append(L"\n");
  append(L"  return p:");
                                                            #line 2419 "PrintXQuery.cpp.template"
                                                              px->print(px->methodPrefix);
                                                            #line 3583 "PrintXQuery.cpp"
  append(L"-");
                                                            #line 2420 "PrintXQuery.cpp.template"
                                                              px->print(node->production->name);
                                                            #line 3587 "PrintXQuery.cpp"
  append(L"-");
                                                            #line 2421 "PrintXQuery.cpp.template"
                                                              px->print(px->format.toString<wchar_t>(node->loopId));
                                                            #line 3591 "PrintXQuery.cpp"
  append(L"($input, $state)");
                                                            #line 2422 "PrintXQuery.cpp.template"
                                                              px->decreaseIndent(2);
                                                              if (hasLookahead || hasBacktracking)
                                                              {
                                                                px->decreaseIndent();
                                                              }
                                                            #line 3599 "PrintXQuery.cpp"
  append(L"\n");
  append(L"};\n");
                                                            #line 2430 "PrintXQuery.cpp.template"
                                                              }
                                                              if (px->methodPrefix != px->methodPrefixTry && node->runOffLoad)
                                                              {
                                                                px->methodPrefix = px->methodPrefixTry;
                                                                visitZeroOrMore(node);
                                                                px->methodPrefix = px->methodPrefixParse;
                                                              }
                                                            }

                                                            void PrintXQuery::PrintLoops::visitOneOrMore(OneOrMore *node)
                                                            {
                                                              if (node->loopId == 0)
                                                              {
                                                                node->loopId = ++loopId;
                                                                Visitor::visitOneOrMore(node);
                                                              }
                                                              if (px->methodPrefix == px->methodPrefixTry || node->production->runPayload)
                                                              {
                                                            #line 3621 "PrintXQuery.cpp"
  append(L"\n");
  append(L"(:");
  append(L"~");
  append(L"\n");
  append(L" : ");
                                                            #line 2450 "PrintXQuery.cpp.template"
                                                                if (px->methodPrefix != px->methodPrefixTry)
                                                                {
                                                            #line 3630 "PrintXQuery.cpp"
  append(L"Parse");
                                                            #line 2452 "PrintXQuery.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 3636 "PrintXQuery.cpp"
  append(L"Try parsing");
                                                            #line 2455 "PrintXQuery.cpp.template"
                                                                }
                                                            #line 3640 "PrintXQuery.cpp"
  append(L" the ");
                                                            #line 2456 "PrintXQuery.cpp.template"
                                                                px->print(px->format.toString<wchar_t>(node->loopId));
                                                                switch (node->loopId)
                                                                {
                                                                case 1:  append(L"st"); break;
                                                                case 2:  append(L"nd"); break;
                                                                case 3:  append(L"rd"); break;
                                                                default: append(L"th"); break;
                                                                }
                                                            #line 3651 "PrintXQuery.cpp"
  append(L" loop of production ");
                                                            #line 2464 "PrintXQuery.cpp.template"
                                                                px->print(node->production->name);
                                                            #line 3655 "PrintXQuery.cpp"
  append(L" (one or more). Use\n");
  append(L" : tail recursion for iteratively updating the lexer state.\n");
  append(L" :\n");
  append(L" : @param $input the input string.\n");
  append(L" : @param $state lexer state, error indicator, and result stack.\n");
  append(L" : @return the updated state.\n");
  append(L" :)\n");
  append(L"declare function p:");
                                                            #line 2472 "PrintXQuery.cpp.template"
                                                                px->print(px->methodPrefix);
                                                            #line 3666 "PrintXQuery.cpp"
  append(L"-");
                                                            #line 2473 "PrintXQuery.cpp.template"
                                                                px->print(node->production->name);
                                                            #line 3670 "PrintXQuery.cpp"
  append(L"-");
                                                            #line 2474 "PrintXQuery.cpp.template"
                                                                px->print(px->format.toString<wchar_t>(node->loopId));
                                                            #line 3674 "PrintXQuery.cpp"
  append(L"($input as xs:string, $state as item()+)\n");
  append(L"{\n");
  append(L"  if ($state[$p:error]) then\n");
  append(L"    $state\n");
  append(L"  else");
                                                            #line 2479 "PrintXQuery.cpp.template"
                                                                px->increaseIndent();
                                                                px->visitNodeList(node->firstChild);
                                                                px->increaseIndent();
                                                                px->printLookahead(node->k, *px->grammar->epsilon, 1, node->getLookahead(), node->findsLookahead);
                                                                px->automaticSemicolonInsertion(node);
                                                                bool nestedTry = px->methodPrefix == px->methodPrefixTry;
                                                                bool hasBacktracking =
                                                                  px->printBacktracking(node,
                                                                                        node->getLookahead(),
                                                                                        node->conflictCaseId,
                                                                                        node->conflictId,
                                                                                        node->firstElementChild);
                                                            #line 3693 "PrintXQuery.cpp"
  append(L"\n");
  append(L"return");
                                                            #line 2492 "PrintXQuery.cpp.template"
                                                                const wchar_t *prefix = L"if (";
                                                                if (hasBacktracking && nestedTry)
                                                                {
                                                            #line 3700 "PrintXQuery.cpp"
  append(L"\n");
  append(L"  if ($state[$p:lk] = -3) then\n");
  append(L"    p:");
                                                            #line 2497 "PrintXQuery.cpp.template"
                                                                  px->print(px->methodPrefix);
                                                            #line 3706 "PrintXQuery.cpp"
  append(L"-");
                                                            #line 2498 "PrintXQuery.cpp.template"
                                                                  px->print(node->production->name);
                                                            #line 3710 "PrintXQuery.cpp"
  append(L"-");
                                                            #line 2499 "PrintXQuery.cpp.template"
                                                                  px->print(px->format.toString<wchar_t>(node->loopId));
                                                            #line 3714 "PrintXQuery.cpp"
  append(L"($input, $state)");
                                                            #line 2500 "PrintXQuery.cpp.template"
                                                                  prefix = L"else if (";
                                                                }
                                                                px->increaseIndent();
                                                                MatchType matchType;
                                                                const TokenSequenceSet &match = node->firstElementChild->getMatch(matchType);
                                                                px->printMatch(node->getLookahead(),
                                                                               node->k,
                                                                               node->conflicts(node->k) == 0 ? 0 : matchType == IF ? 1 : 2,
                                                                               match,
                                                                               matchType == IF ? IFNOT : IF,
                                                                               1,
                                                                               prefix,
                                                                               L") then");
                                                            #line 3730 "PrintXQuery.cpp"
  append(L"\n");
  append(L"  $state\n");
  append(L"else\n");
  append(L"  p:");
                                                            #line 2516 "PrintXQuery.cpp.template"
                                                                px->print(px->methodPrefix);
                                                            #line 3737 "PrintXQuery.cpp"
  append(L"-");
                                                            #line 2517 "PrintXQuery.cpp.template"
                                                                px->print(node->production->name);
                                                            #line 3741 "PrintXQuery.cpp"
  append(L"-");
                                                            #line 2518 "PrintXQuery.cpp.template"
                                                                px->print(px->format.toString<wchar_t>(node->loopId));
                                                            #line 3745 "PrintXQuery.cpp"
  append(L"($input, $state)");
                                                            #line 2519 "PrintXQuery.cpp.template"
                                                                px->decreaseIndent(3);
                                                            #line 3749 "PrintXQuery.cpp"
  append(L"\n");
  append(L"};\n");
                                                            #line 2522 "PrintXQuery.cpp.template"
                                                              }
                                                              if (px->methodPrefix != px->methodPrefixTry && node->runOffLoad)
                                                              {
                                                                px->methodPrefix = px->methodPrefixTry;
                                                                visitOneOrMore(node);
                                                                px->methodPrefix = px->methodPrefixParse;
                                                              }
                                                            }

                                                            void PrintXQuery::automaticSemicolonInsertion(Node *node)
                                                            {
                                                              if (node->automaticSemicolonInsertion)
                                                              {
                                                                const bool afterRbrace = false;
                                                                Production *p;
                                                                p = grammar->stringByName.byStringValue(L";");
                                                                Token::Code semicolon = p == 0 ? -1 : p->tokenCode;
                                                                lineBuffer.clear();
                                                                TokenSequenceSet tss;
                                                            #line 3772 "PrintXQuery.cpp"
  append(L"\n");
  append(L"let $state :=");
                                                            #line 2542 "PrintXQuery.cpp.template"
                                                                switch (node->automaticSemicolonInsertion)
                                                                {
                                                                case PLUSPLUS:
                                                                case MINUSMINUS:
                                                                  {
                                                                    p = grammar->stringByName.byStringValue(L"++");
                                                                    Token::Code plusplus = p == 0 ? -1 : p->tokenCode;
                                                                    p = grammar->stringByName.byStringValue(L"--");
                                                                    Token::Code minusminus = p == 0 ? -1 : p->tokenCode;
                                                            #line 3785 "PrintXQuery.cpp"
  append(L"\n");
  append(L"  if ($state[$p:l1] = (");
                                                            #line 2552 "PrintXQuery.cpp.template"
                                                                    print(format.toString<wchar_t>(grammar->externalTokenCode[plusplus]));
                                                            #line 3790 "PrintXQuery.cpp"
  append(L", ");
                                                            #line 2553 "PrintXQuery.cpp.template"
                                                                    print(format.toString<wchar_t>(grammar->externalTokenCode[minusminus]));
                                                            #line 3794 "PrintXQuery.cpp"
  append(L") and p:follows-line-terminator($input, $state)) then");
                                                            #line 2554 "PrintXQuery.cpp.template"
                                                                                  tss.insert(grammar->tokenSequence(plusplus));
                                                                    tss.insert(grammar->tokenSequence(minusminus));
                                                                    printCodeSequenceAnnotation(tss);
                                                                  }
                                                                  break;
                                                                case CONTINUE:
                                                                case BREAK:
                                                                case RETURN:
                                                                case THROW:
                                                                  {
                                                            #line 3807 "PrintXQuery.cpp"
  append(L"\n");
  append(L"  if ($state[$p:l1] ne ");
                                                            #line 2565 "PrintXQuery.cpp.template"
                                                                    print(format.toString<wchar_t>(grammar->externalTokenCode[semicolon]));
                                                            #line 3812 "PrintXQuery.cpp"
  append(L" and $state[$p:l1] ge 0 and p:follows-line-terminator($input, $state)) then");
                                                            #line 2567 "PrintXQuery.cpp.template"
                                                                    tss.insert(grammar->tokenSequence(semicolon));
                                                                    printCodeSequenceAnnotation(tss);
                                                                  }
                                                                  break;
                                                                case SEMICOLON:
                                                                  {
                                                                    p = grammar->terminalByName.byNodeType(EndOfFile().getNodeType());
                                                                    Token::Code eof = p == 0 ? -1 : p->tokenCode;
                                                                    p = grammar->stringByName.byStringValue(L"}");
                                                                    Token::Code rbrace = p == 0 ? -1 : p->tokenCode;
                                                            #line 3825 "PrintXQuery.cpp"
  append(L"\n");
  append(L"  if ($state[$p:l1] eq ");
                                                            #line 2578 "PrintXQuery.cpp.template"
                                                                    print(format.toString<wchar_t>(grammar->externalTokenCode[rbrace]));
                                                                    printCodeSequenceAnnotation(grammar->tokenSequence(rbrace));
                                                            #line 3831 "PrintXQuery.cpp"
  append(L"\n");
  append(L"   or $state[$p:l1] eq ");
                                                            #line 2581 "PrintXQuery.cpp.template"
                                                                    print(format.toString<wchar_t>(grammar->externalTokenCode[eof]));
                                                                    printCodeSequenceAnnotation(grammar->tokenSequence(eof));
                                                            #line 3837 "PrintXQuery.cpp"
  append(L"\n");
  append(L"   or $state[$p:l1] ne ");
                                                            #line 2584 "PrintXQuery.cpp.template"
                                                                    print(format.toString<wchar_t>(grammar->externalTokenCode[semicolon]));
                                                            #line 3842 "PrintXQuery.cpp"
  append(L" and $state[$p:l1] ge 0 and ");
                                                            #line 2585 "PrintXQuery.cpp.template"
                                                                    if (afterRbrace)
                                                                    {
                                                            #line 3847 "PrintXQuery.cpp"
  append(L"(");
                                                            #line 2587 "PrintXQuery.cpp.template"
                                                                    }
                                                            #line 3851 "PrintXQuery.cpp"
  append(L"p:follows-line-terminator($input, $state)");
                                                            #line 2589 "PrintXQuery.cpp.template"
                                                                    if (afterRbrace)
                                                                    {
                                                            #line 3856 "PrintXQuery.cpp"
  append(L" or substring($input, $state[$p:b0], 1) eq \"}\")");
                                                            #line 2592 "PrintXQuery.cpp.template"
                                                                    }
                                                            #line 3860 "PrintXQuery.cpp"
  append(L") then");
                                                            #line 2593 "PrintXQuery.cpp.template"
                                                                    printCodeSequenceAnnotation(grammar->tokenSequence(semicolon));
                                                                  }
                                                                  break;
                                                                default:
                                                                  {
                                                                    internalerr();
                                                                  }
                                                                }
                                                            #line 3871 "PrintXQuery.cpp"
  append(L"\n");
  append(L"  (\n");
  append(L"    subsequence($state, 1, $p:l1 - 1),\n");
  append(L"    ");
                                                            #line 2604 "PrintXQuery.cpp.template"
                                                                print(format.toString<wchar_t>(grammar->externalTokenCode[semicolon]));
                                                            #line 3878 "PrintXQuery.cpp"
  append(L",");
                                                            #line 2605 "PrintXQuery.cpp.template"
                                                                printCodeSequenceAnnotation(grammar->tokenSequence(semicolon));
                                                            #line 3882 "PrintXQuery.cpp"
  append(L"\n");
  append(L"    $state[$p:b1],\n");
  append(L"    $state[$p:b1],\n");
  append(L"    subsequence($state, $p:e1 + 1)\n");
  append(L"  )\n");
  append(L"  else\n");
  append(L"    $state");
                                                            #line 2612 "PrintXQuery.cpp.template"
                                                              }
                                                            }

// End
