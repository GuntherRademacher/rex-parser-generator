// This file was generated on Sun Nov 24, 2024 16:09 (UTC+01) by REx v6.0 which is Copyright (c) 1979-2024 by Gunther Rademacher <grd@gmx.net>
// REx command line: PrintXSLT.cpp.template
                                                            #line 1 "PrintXSLT.cpp.template"
                                                            /*
                                                             * PrintXSLT.cpp
                                                             *
                                                             *  Created on: 31.07.2008
                                                             *      Author: Gunther
                                                             */

                                                            #include "../common/Memory.hpp"

                                                            #include "PrintXSLT.hpp"
                                                            #include "OrderedTokenSequenceVector.hpp"
                                                            #include "ItemSet.hpp"

                                                            #include "../common/PtrLess.hpp"
                                                            #include "../common/Format.hpp"
                                                            #include "../common/Encoder.hpp"
                                                            #include "../common/Math.hpp"

                                                            void PrintXSLT::printCodeSequenceAnnotation(const TokenSequenceSet &t)
                                                            {
                                                              lineBuffer += L" ";
                                                              print(lineBuffer.c_str());
                                                              bool xml = content()[size() - 2] == L'>';

                                                              const size_t align = xml ? 84 : 86;
                                                              const size_t linelength = 160;
                                                              const size_t headerWidth = xml ? 5 : 3; // "<!-- "
                                                              const size_t trailerWidth = xml ? 4 : 3; // " -->"
                                                              const wchar_t *header = xml ? L"<!-- " : L"(: ";
                                                              const wchar_t *trailer = xml ? L" -->" : L" :)";

                                                              size_t lsize = column();
                                                              size_t filler = lsize > align ? 0 : align - lsize;
                                                              size_t spaces = lsize + filler + headerWidth;
                                                              size_t width = spaces > linelength ? 0 : linelength - spaces;
                                                              if (width < (linelength - align) / 2) width = (linelength - align) / 2;

                                                              WString annotation(t.toString(grammar, L"\n", L" |", width, trailerWidth, false, toBeEscaped));
                                                              if (xml)
                                                                invalidateXmlCommentTokens(annotation);
                                                              else
                                                                invalidateXPathCommentTokens(annotation);
                                                              wchar_t *indentedAnnotation = Format::reIndent(annotation.c_str(), Math::max(0, static_cast<int>(spaces) - getIndent()));

                                                              print(filler, L" ");
                                                              print(header);
                                                              print(indentedAnnotation);
                                                              print(trailer);
                                                              free(indentedAnnotation);
                                                            }

                                                            bool PrintXSLT::printLookahead(size_t k,
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
                                                                  lineBuffer += L"<xsl:variable name=\"state\" select=\"p:lookahead";
                                                                  lineBuffer += format.toString<wchar_t>(level);
                                                                  lineBuffer += lookaheadType;
                                                                  lineBuffer += L"(";
                                                                  lineBuffer += level == 1 || ! unlimitedLookahead ? L"" : format.toString<wchar_t>(lookahead->prefixCode(grammar->tokenSequenceFactory->tokenBits()));
                                                                  lineBuffer += level == 1 || ! unlimitedLookahead ? L"" : L", ";
                                                                  lineBuffer += grammar->singleLexer ? L"0" : format.toString<wchar_t>(lookahead->getSetNo(grammar->lookaheadSets));
                                                                  lineBuffer += L", $input, $state)\"/>";
                                                            #line 87 "PrintXSLT.cpp"
  append(L"\n");
                                                            #line 84 "PrintXSLT.cpp.template"
                                                                  printCodeSequenceAnnotation(lookahead->getInitials());
                                                                }

                                                                if (lookahead->getDpi() >= 0)
                                                                {
                                                                  empty = false;
                                                            #line 96 "PrintXSLT.cpp"
  append(L"\n");
  append(L"<xsl:variable name=\"state\" select=\"p:predict($input, $state, ");
                                                            #line 91 "PrintXSLT.cpp.template"
                                                                  print(format.toString<wchar_t>(lookahead->getDpi()));
                                                            #line 101 "PrintXSLT.cpp"
  append(L")\"/>");
                                                            #line 93 "PrintXSLT.cpp.template"
                                                                }
                                                                else if (level < k)
                                                                {
                                                                  // this block will be obsolete when "tables" proves to be successful

                                                                  const CompressedTokenSet::CompressedTokenSetByTokenSet &chol(lookahead->getCombinedHigherOrderLookahead());
                                                                  if (! chol.empty())
                                                                  {
                                                                    empty = false;
                                                                    ++level;
                                                            #line 114 "PrintXSLT.cpp"
  append(L"\n");
  append(L"<xsl:variable name=\"state\" as=\"item()+\">\n");
  append(L"  <xsl:choose>");
                                                            #line 105 "PrintXSLT.cpp.template"
                                                                    increaseIndent(2);
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

                                                                          lineBuffer.clear();
                                                                          lineBuffer += L"<xsl:when test=\"$state[$p:l";
                                                                          lineBuffer += level == 2 ? L"1" : L"k";
                                                                          lineBuffer += L"] = ";
                                                                          lineBuffer += format.toString<wchar_t>(lookahead->localSequenceCode(grammar->tokenSequenceFactory, grammar->tokenSequence(token), grammar->externalTokenCode));
                                                                          lineBuffer += L"\">";
                                                            #line 139 "PrintXSLT.cpp"
  append(L"\n");
                                                            #line 126 "PrintXSLT.cpp.template"
                                                                          printCodeSequenceAnnotation(nextPrefix);
                                                                          increaseIndent();

                                                                          TokenSequenceSet singleNextPrefixSet;
                                                                          singleNextPrefixSet.insert(nextPrefix);
                                                                          printLookahead(k, singleNextPrefixSet, level, i->second, findsLookahead);
                                                            #line 148 "PrintXSLT.cpp"
  append(L"\n");
  append(L"<xsl:sequence select=\"$state\"/>");
                                                            #line 133 "PrintXSLT.cpp.template"
                                                                          decreaseIndent();
                                                            #line 153 "PrintXSLT.cpp"
  append(L"\n");
  append(L"</xsl:when>");
                                                            #line 135 "PrintXSLT.cpp.template"
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
                                                            #line 179 "PrintXSLT.cpp"
  append(L"\n");
                                                            #line 158 "PrintXSLT.cpp.template"
                                                                            printCodeSequenceAnnotation(nextPrefix);
                                                                          }

                                                                          nextPrefix = grammar->tokenSequenceFactory->tokenSequence(*p, *j);
                                                                          nextPrefixSet.insert(nextPrefix);

                                                                          lineBuffer.clear();
                                                                          if (seqNo == 0)
                                                                          {
                                                                            lineBuffer += L"<xsl:when test=\"$state[$p:l";
                                                                            lineBuffer += level == 2 ? L"1" : L"k";
                                                                            lineBuffer += L"] ";
                                                                            lineBuffer += size == 1 ? L"eq " : L"= (";
                                                                          }
                                                                          else
                                                                          {
                                                                            lineBuffer += L"               ";
                                                                            lineBuffer += L"      ";
                                                                            lineBuffer += L"            ";
                                                                          }

                                                                          lineBuffer += format.toString<wchar_t>(CompressedTokenSet::uniqueSequenceCode(grammar->tokenSequenceFactory, nextPrefix, grammar->externalTokenCode));
                                                                          ++seqNo;
                                                                        }
                                                                        lineBuffer += size == 1 ? L"" : L")";
                                                                        lineBuffer += L"\">";
                                                            #line 208 "PrintXSLT.cpp"
  append(L"\n");
                                                            #line 185 "PrintXSLT.cpp.template"
                                                                        printCodeSequenceAnnotation(nextPrefix);

                                                                        increaseIndent();
                                                                        printLookahead(k, nextPrefixSet, level, cts, findsLookahead);
                                                            #line 215 "PrintXSLT.cpp"
  append(L"\n");
  append(L"<xsl:sequence select=\"$state\"/>");
                                                            #line 190 "PrintXSLT.cpp.template"
                                                                        decreaseIndent();
                                                            #line 220 "PrintXSLT.cpp"
  append(L"\n");
  append(L"</xsl:when>");
                                                            #line 192 "PrintXSLT.cpp.template"
                                                                      }
                                                                    }
                                                                    --level;
                                                            #line 227 "PrintXSLT.cpp"
  append(L"\n");
  append(L"<xsl:otherwise>");
                                                            #line 196 "PrintXSLT.cpp.template"
                                                                    increaseIndent();
                                                                    if (level == 1)
                                                                    {
                                                            #line 234 "PrintXSLT.cpp"
  append(L"\n");
  append(L"<xsl:sequence select=\"$state[$p:l1], subsequence($state, $p:lk + 1)\"/>");
                                                            #line 201 "PrintXSLT.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 241 "PrintXSLT.cpp"
  append(L"\n");
  append(L"<xsl:sequence select=\"$state\"/>");
                                                            #line 205 "PrintXSLT.cpp.template"
                                                                    }
                                                                    decreaseIndent(3);
                                                            #line 247 "PrintXSLT.cpp"
  append(L"\n");
  append(L"    </xsl:otherwise>\n");
  append(L"  </xsl:choose>\n");
  append(L"</xsl:variable>");
                                                            #line 210 "PrintXSLT.cpp.template"
                                                                  }
                                                                }
                                                              }
                                                              return ! empty;
                                                            }

                                                            void PrintXSLT::printMatch(const CompressedTokenSet *lookahead,
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
                                                            #line 270 "PrintXSLT.cpp"
  append(L"\n");
  append(L"<xsl:otherwise>");
                                                            #line 228 "PrintXSLT.cpp.template"
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
                                                            #line 333 "PrintXSLT.cpp"
  append(L"\n");
                                                            #line 288 "PrintXSLT.cpp.template"
                                                                      printCodeSequenceAnnotation(*previousCodeSequence);
                                                                    }
                                                                    else
                                                                    {
                                                            #line 340 "PrintXSLT.cpp"
  append(L"\n");
                                                            #line 293 "PrintXSLT.cpp.template"
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
                                                            #line 365 "PrintXSLT.cpp"
  append(L"\n");
                                                            #line 316 "PrintXSLT.cpp.template"
                                                                   printCodeSequenceAnnotation(*previousCodeSequence);
                                                                }
                                                                else
                                                                {
                                                            #line 372 "PrintXSLT.cpp"
  append(L"\n");
                                                            #line 321 "PrintXSLT.cpp.template"
                                                                  print(lineBuffer.c_str());
                                                                }
                                                              }
                                                            }

                                                            void PrintXSLT::printConsume(Token::Code code)
                                                            {
                                                              lineBuffer = L"<xsl:variable name=\"state\" select=\"p:consume";
                                                              if (tree && methodPrefix == methodPrefixTry)
                                                              {
                                                                lineBuffer += L"T";
                                                                consumeMethods = 2;
                                                              }
                                                              lineBuffer += L"(";
                                                              lineBuffer += Format().toString<wchar_t>(grammar->externalTokenCode[code]);
                                                              lineBuffer += L", $input, $state)\"/>";
                                                            #line 391 "PrintXSLT.cpp"
  append(L"\n");
                                                            #line 338 "PrintXSLT.cpp.template"
                                                               printCodeSequenceAnnotation(grammar->tokenSequence(code));
                                                            }

                                                            void PrintXSLT::visitNodeList(Node *firstNode)
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

                                                            void PrintXSLT::visitOptional(Optional *node)
                                                            {
                                                              printLookahead(node->k, *grammar->epsilon, 1, node->getLookahead(), node->findsLookahead);
                                                              automaticSemicolonInsertion(node);
                                                              printBacktracking(node,
                                                                                node->getLookahead(),
                                                                                node->conflictCaseId,
                                                                                node->conflictId,
                                                                                node->firstElementChild);
                                                            #line 420 "PrintXSLT.cpp"
  append(L"\n");
  append(L"<xsl:variable name=\"state\" as=\"item()+\">\n");
  append(L"  <xsl:choose>\n");
  append(L"    <xsl:when test=\"$state[$p:error]\">\n");
  append(L"      <xsl:sequence select=\"$state\"/>\n");
  append(L"    </xsl:when>");
                                                            #line 369 "PrintXSLT.cpp.template"
                                                              increaseIndent(2);
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
                                                                         L"<xsl:when test=\"",
                                                                         L"\">");
                                                              Visitor::visitNodeWithChildren(node);
                                                              decreaseIndent(2);
                                                            #line 445 "PrintXSLT.cpp"
  append(L"\n");
  append(L"      <xsl:sequence select=\"$state\"/>\n");
  append(L"    </xsl:when>\n");
  append(L"    <xsl:otherwise>\n");
  append(L"      <xsl:sequence select=\"$state\"/>\n");
  append(L"    </xsl:otherwise>\n");
  append(L"  </xsl:choose>\n");
  append(L"</xsl:variable>");
                                                            #line 393 "PrintXSLT.cpp.template"
                                                            }

                                                            void PrintXSLT::visitZeroOrMore(ZeroOrMore *node)
                                                            {
                                                            #line 459 "PrintXSLT.cpp"
  append(L"\n");
  append(L"<xsl:variable name=\"state\" select=\"p:");
                                                            #line 398 "PrintXSLT.cpp.template"
                                                              print(methodPrefix);
                                                            #line 464 "PrintXSLT.cpp"
  append(L"-");
                                                            #line 399 "PrintXSLT.cpp.template"
                                                              print(node->production->name);
                                                            #line 468 "PrintXSLT.cpp"
  append(L"-");
                                                            #line 400 "PrintXSLT.cpp.template"
                                                              print(format.toString<wchar_t>(node->loopId));
                                                            #line 472 "PrintXSLT.cpp"
  append(L"($input, $state)\"/>");
                                                            #line 402 "PrintXSLT.cpp.template"
                                                            }

                                                            void PrintXSLT::visitOneOrMore(OneOrMore *node)
                                                            {
                                                            #line 479 "PrintXSLT.cpp"
  append(L"\n");
  append(L"<xsl:variable name=\"state\" select=\"p:");
                                                            #line 407 "PrintXSLT.cpp.template"
                                                              print(methodPrefix);
                                                            #line 484 "PrintXSLT.cpp"
  append(L"-");
                                                            #line 408 "PrintXSLT.cpp.template"
                                                              print(node->production->name);
                                                            #line 488 "PrintXSLT.cpp"
  append(L"-");
                                                            #line 409 "PrintXSLT.cpp.template"
                                                              print(format.toString<wchar_t>(node->loopId));
                                                            #line 492 "PrintXSLT.cpp"
  append(L"($input, $state)\"/>");
                                                            #line 411 "PrintXSLT.cpp.template"
                                                            }

                                                            void PrintXSLT::printCase(const CompressedTokenSet *lookahead, size_t k, Node *c, const wchar_t *prefix)
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
                                                                         L"\">");
                                                              increaseIndent();
                                                              size_t outputSize1 = size();

                                                              c->accept(*this);

                                                              size_t outputSize2 = size();
                                                              if (outputSize1 != outputSize2)
                                                              {
                                                            #line 518 "PrintXSLT.cpp"
  append(L"\n");
  append(L"<xsl:sequence select=\"$state\"/>");
                                                            #line 435 "PrintXSLT.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 525 "PrintXSLT.cpp"
  append(L"\n");
  append(L"<xsl:sequence select=\"$state\"/>");
                                                            #line 439 "PrintXSLT.cpp.template"
                                                              }
                                                              decreaseIndent();
                                                            }

                                                            bool PrintXSLT::printBacktracking(Node *node,
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

                                                            bool PrintXSLT::printBacktracking(Node *node,
                                                                                              const CompressedTokenSet *lookahead,
                                                                                              int conflictCaseId,
                                                                                              int conflictId,
                                                                                              const NodeList &cases)
                                                            {
                                                              bool hasBacktracking = node->conflicts(node->k) != 0;
                                                              if (hasBacktracking)
                                                              {
                                                            #line 564 "PrintXSLT.cpp"
  append(L"\n");
  append(L"<xsl:variable name=\"state\" as=\"item()+\">");
                                                            #line 475 "PrintXSLT.cpp.template"
                                                                increaseIndent();
                                                                MatchType conflictMatchType;
                                                                const TokenSequenceSet &conflictMatch = node->getConflictMatch(conflictMatchType);
                                                                if (! conflictMatch.empty())
                                                                {
                                                            #line 573 "PrintXSLT.cpp"
  append(L"\n");
  append(L"<xsl:choose>\n");
  append(L"  <xsl:when test=\"$state[$p:error]\">\n");
  append(L"    <xsl:sequence select=\"$state\"/>\n");
  append(L"  </xsl:when>");
                                                            #line 485 "PrintXSLT.cpp.template"
                                                                  if (lookahead && lookahead->getDpi() >= 0 && conflictMatchType == IFNOT)
                                                                  {
                                                                    conflictMatchType = IF;
                                                                    conflictCaseId = 0;
                                                                  }
                                                                  increaseIndent();
                                                                  printMatch(lookahead,
                                                                             node->k,
                                                                             0,
                                                                             conflictMatch,
                                                                             conflictMatchType,
                                                                             conflictCaseId,
                                                                             L"<xsl:when test=\"",
                                                                             L"\">");
                                                                  increaseIndent();
                                                                }
                                                            #line 596 "PrintXSLT.cpp"
  append(L"\n");
  append(L"<xsl:variable name=\"state\"");
                                                            #line 502 "PrintXSLT.cpp.template"
                                                                if (memoization)
                                                                {
                                                            #line 602 "PrintXSLT.cpp"
  append(L" select=\"p:memoized($state, ");
                                                            #line 504 "PrintXSLT.cpp.template"
                                                                  print(format.toString<wchar_t>(conflictId));
                                                            #line 606 "PrintXSLT.cpp"
  append(L")\"/>\n");
  append(L"<xsl:choose>\n");
  append(L"  <xsl:when test=\"$state[$p:lk] != 0\">\n");
  append(L"    <xsl:sequence select=\"$state\"/>\n");
  append(L"  </xsl:when>\n");
  append(L"  <xsl:otherwise");
                                                            #line 510 "PrintXSLT.cpp.template"
                                                                  increaseIndent();
                                                                }
                                                            #line 616 "PrintXSLT.cpp"
  append(L">");
                                                            #line 512 "PrintXSLT.cpp.template"
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
                                                            #line 645 "PrintXSLT.cpp"
  append(L"\n");
  append(L"<xsl:sequence select=\"p:memoize($backtrack, $state, ");
                                                            #line 539 "PrintXSLT.cpp.template"
                                                                    print(format.toString<wchar_t>(conflictId));
                                                            #line 650 "PrintXSLT.cpp"
  append(L", $backtrack[$p:e0], -");
                                                            #line 540 "PrintXSLT.cpp.template"
                                                                    print(format.toString<wchar_t>(caseId));
                                                            #line 654 "PrintXSLT.cpp"
  append(L", -");
                                                            #line 541 "PrintXSLT.cpp.template"
                                                                    print(format.toString<wchar_t>(caseId));
                                                            #line 658 "PrintXSLT.cpp"
  append(L")\"/>");
                                                            #line 542 "PrintXSLT.cpp.template"
                                                                  }
                                                                  else if (c->involvedInConflict)
                                                                  {
                                                                    if (caseId == firstConflictCaseId)
                                                                    {
                                                            #line 666 "PrintXSLT.cpp"
  append(L"\n");
  append(L"<xsl:variable name=\"backtrack\" select=\"$state\"/>\n");
  append(L"<xsl:variable name=\"state\" select=\"p:strip-result($state)\"/>");
                                                            #line 549 "PrintXSLT.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 674 "PrintXSLT.cpp"
  append(L"\n");
  append(L"<xsl:variable name=\"state\" select=\"p:restore($backtrack, $state)\"/>");
                                                            #line 553 "PrintXSLT.cpp.template"
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
                                                            #line 696 "PrintXSLT.cpp"
  append(L"\n");
  append(L"<xsl:choose>\n");
  append(L"  <xsl:when test=\"not($state[$p:error])\">");
                                                            #line 573 "PrintXSLT.cpp.template"
                                                                    if (nestedTry && (node->isZeroOrMore() || node->isOneOrMore()))
                                                                    {
                                                            #line 703 "PrintXSLT.cpp"
  append(L"\n");
  append(L"    <xsl:sequence select=\"p:memoize($state, $state, ");
                                                            #line 576 "PrintXSLT.cpp.template"
                                                                      print(format.toString<wchar_t>(conflictId));
                                                            #line 708 "PrintXSLT.cpp"
  append(L", $backtrack[$p:e0], -");
                                                            #line 577 "PrintXSLT.cpp.template"
                                                                      print(format.toString<wchar_t>(caseId));
                                                            #line 712 "PrintXSLT.cpp"
  append(L", -3)\"/>");
                                                            #line 578 "PrintXSLT.cpp.template"
                                                                    }
                                                                    else
                                                                    {
                                                            #line 718 "PrintXSLT.cpp"
  append(L"\n");
  append(L"    <xsl:sequence select=\"p:memoize($backtrack, $state, ");
                                                            #line 582 "PrintXSLT.cpp.template"
                                                                      print(format.toString<wchar_t>(conflictId));
                                                            #line 723 "PrintXSLT.cpp"
  append(L", $backtrack[$p:e0], -");
                                                            #line 583 "PrintXSLT.cpp.template"
                                                                      print(format.toString<wchar_t>(caseId));
                                                            #line 727 "PrintXSLT.cpp"
  append(L", -");
                                                            #line 584 "PrintXSLT.cpp.template"
                                                                      print(format.toString<wchar_t>(caseId));
                                                            #line 731 "PrintXSLT.cpp"
  append(L")\"/>");
                                                            #line 585 "PrintXSLT.cpp.template"
                                                                    }
                                                            #line 735 "PrintXSLT.cpp"
  append(L"\n");
  append(L"  </xsl:when>\n");
  append(L"  <xsl:otherwise>");
                                                            #line 588 "PrintXSLT.cpp.template"
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
                                                            #line 751 "PrintXSLT.cpp"
  append(L"\n");
  append(L"  </xsl:otherwise>\n");
  append(L"</xsl:choose>");
                                                            #line 601 "PrintXSLT.cpp.template"
                                                                  }
                                                                }
                                                                decreaseIndent();
                                                                if (memoization)
                                                                {
                                                                  decreaseIndent();
                                                            #line 762 "PrintXSLT.cpp"
  append(L"\n");
  append(L"  </xsl:otherwise>\n");
  append(L"</xsl:choose>");
                                                            #line 609 "PrintXSLT.cpp.template"
                                                                }
                                                                if (! conflictMatch.empty())
                                                                {
                                                                  decreaseIndent(2);
                                                            #line 771 "PrintXSLT.cpp"
  append(L"\n");
  append(L"  </xsl:when>\n");
  append(L"  <xsl:otherwise>");
                                                            #line 615 "PrintXSLT.cpp.template"
                                                                  if (node->k > 1)
                                                                  {
                                                            #line 778 "PrintXSLT.cpp"
  append(L"\n");
  append(L"    <xsl:sequence select=\"$state\"/>");
                                                            #line 618 "PrintXSLT.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 785 "PrintXSLT.cpp"
  append(L"\n");
  append(L"    <xsl:sequence select=\"$state[$p:l1], subsequence($state, $p:lk + 1)\"/>");
                                                            #line 623 "PrintXSLT.cpp.template"
                                                                  }
                                                            #line 790 "PrintXSLT.cpp"
  append(L"\n");
  append(L"  </xsl:otherwise>\n");
  append(L"</xsl:choose>");
                                                            #line 626 "PrintXSLT.cpp.template"
                                                                }
                                                                decreaseIndent();
                                                            #line 797 "PrintXSLT.cpp"
  append(L"\n");
  append(L"</xsl:variable>");
                                                            #line 629 "PrintXSLT.cpp.template"
                                                              }
                                                              return hasBacktracking;
                                                            }

                                                            void PrintXSLT::visitChoice(Choice *node)
                                                            {
                                                              printLookahead(node->k, *grammar->epsilon, 1, node->getLookahead(), node->findsLookahead);
                                                              automaticSemicolonInsertion(node);
                                                              printBacktracking(node,
                                                                                node->getLookahead(),
                                                                                node->conflictCaseId,
                                                                                node->conflictId,
                                                                                node->cases);
                                                            #line 814 "PrintXSLT.cpp"
  append(L"\n");
  append(L"<xsl:variable name=\"state\" as=\"item()+\">\n");
  append(L"  <xsl:choose>\n");
  append(L"    <xsl:when test=\"$state[$p:error]\">\n");
  append(L"      <xsl:sequence select=\"$state\"/>\n");
  append(L"    </xsl:when>");
                                                            #line 647 "PrintXSLT.cpp.template"
                                                              increaseIndent(2);
                                                              Node *defaultCase = 0;
                                                              const wchar_t *prefix = L"<xsl:when test=\"";
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
                                                            #line 840 "PrintXSLT.cpp"
  append(L"\n");
                                                            #line 666 "PrintXSLT.cpp.template"
                                                                    print(prefix);
                                                                    prefix = L"             or ";
                                                            #line 845 "PrintXSLT.cpp"
  append(L"$state[$p:lk] = -");
                                                            #line 668 "PrintXSLT.cpp.template"
                                                                    print(format.toString<wchar_t>(caseId));
                                                                    if (match.empty())
                                                                    {
                                                            #line 851 "PrintXSLT.cpp"
  append(L"\">");
                                                            #line 671 "PrintXSLT.cpp.template"
                                                                    }
                                                                  }
                                                                  printCase(node->getLookahead(), node->k, c, prefix);
                                                                  prefix = L"<xsl:when test=\"";
                                                            #line 858 "PrintXSLT.cpp"
  append(L"\n");
  append(L"</xsl:when>");
                                                            #line 676 "PrintXSLT.cpp.template"
                                                                }
                                                              }
                                                              printCase(node->getLookahead(), node->k, defaultCase, L"");
                                                              decreaseIndent(2);
                                                            #line 866 "PrintXSLT.cpp"
  append(L"\n");
  append(L"    </xsl:otherwise>\n");
  append(L"  </xsl:choose>\n");
  append(L"</xsl:variable>");
                                                            #line 683 "PrintXSLT.cpp.template"
                                                            }

                                                            void PrintXSLT::visitProduction(Production *node)
                                                            {
                                                              setIndent(1);
                                                            #line 877 "PrintXSLT.cpp"
  append(L"\n");
  append(L"<!--");
  append(L"~");
  append(L"\n");
  append(L" ! ");
                                                            #line 690 "PrintXSLT.cpp.template"
                                                              if (methodPrefix != methodPrefixTry)
                                                              {
                                                            #line 886 "PrintXSLT.cpp"
  append(L"Parse");
                                                            #line 692 "PrintXSLT.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 892 "PrintXSLT.cpp"
  append(L"Try parsing");
                                                            #line 695 "PrintXSLT.cpp.template"
                                                              }
                                                            #line 896 "PrintXSLT.cpp"
  append(L" ");
                                                            #line 696 "PrintXSLT.cpp.template"
                                                              print(node->name);
                                                            #line 900 "PrintXSLT.cpp"
  append(L".\n");
  append(L" !\n");
  append(L" ! @param $input the input string.\n");
  append(L" ! @param $state lexer state, error indicator, and result.\n");
  append(L" ! @return the updated state.\n");
  append(L"-->\n");
  append(L"<xsl:function name=\"p:");
                                                            #line 703 "PrintXSLT.cpp.template"
                                                              print(methodPrefix);
                                                            #line 910 "PrintXSLT.cpp"
  append(L"-");
                                                            #line 704 "PrintXSLT.cpp.template"
                                                              print(node->name);
                                                            #line 914 "PrintXSLT.cpp"
  append(L"\" as=\"item()+\">\n");
  append(L"  <xsl:param name=\"input\" as=\"xs:string\"/>\n");
  append(L"  <xsl:param name=\"state\" as=\"item()+\"/>\n");
                                                            #line 708 "PrintXSLT.cpp.template"
                                                              if (trace)
                                                              {
                                                            #line 921 "PrintXSLT.cpp"
  append(L"\n");
  append(L"  <xsl:sequence select=\"p:trace-nonterminal($state, &quot;");
                                                            #line 711 "PrintXSLT.cpp.template"
                                                                print(methodPrefix);
                                                            #line 926 "PrintXSLT.cpp"
  append(L"&quot;, &quot;start&quot;, &quot;");
                                                            #line 713 "PrintXSLT.cpp.template"
                                                                print(node->name);
                                                            #line 930 "PrintXSLT.cpp"
  append(L"&quot;)\"/>\n");
  append(L"  <xsl:variable name=\"state\" as=\"item()+\">");
                                                            #line 715 "PrintXSLT.cpp.template"
                                                                increaseIndent();
                                                              }
                                                              if (tree && methodPrefix != methodPrefixTry)
                                                              {
                                                            #line 938 "PrintXSLT.cpp"
  append(L"\n");
  append(L"  <xsl:variable name=\"count\" select=\"count($state)\"/>");
                                                            #line 720 "PrintXSLT.cpp.template"
                                                                if (! noPosition)
                                                                {
                                                            #line 944 "PrintXSLT.cpp"
  append(L"\n");
  append(L"  <xsl:variable name=\"begin\" select=\"$state[$p:e0]\"/>");
                                                            #line 723 "PrintXSLT.cpp.template"
                                                                }
                                                              }
                                                              visitNodeList(node->firstChild);
                                                              if (tree && methodPrefix != methodPrefixTry)
                                                              {
                                                                if (! noPosition)
                                                                {
                                                            #line 955 "PrintXSLT.cpp"
  append(L"\n");
  append(L"  <xsl:variable name=\"end\" select=\"$state[$p:e0]\"/>");
                                                            #line 731 "PrintXSLT.cpp.template"
                                                                }
                                                            #line 960 "PrintXSLT.cpp"
  append(L"\n");
  append(L"  <xsl:sequence select=\"p:reduce($state, '");
                                                            #line 733 "PrintXSLT.cpp.template"
                                                                print(node->name);
                                                            #line 965 "PrintXSLT.cpp"
  append(L"', $count");
                                                            #line 734 "PrintXSLT.cpp.template"
                                                                if (! noPosition)
                                                                {
                                                            #line 970 "PrintXSLT.cpp"
  append(L", $begin, $end");
                                                            #line 737 "PrintXSLT.cpp.template"
                                                                }
                                                            #line 974 "PrintXSLT.cpp"
  append(L")\"/>");
                                                            #line 738 "PrintXSLT.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 980 "PrintXSLT.cpp"
  append(L"\n");
  append(L"  <xsl:sequence select=\"$state\"/>");
                                                            #line 742 "PrintXSLT.cpp.template"
                                                              }
                                                              if (trace)
                                                              {
                                                            #line 987 "PrintXSLT.cpp"
  append(L"\n");
  append(L"</xsl:variable>\n");
  append(L"<xsl:sequence select=\"p:trace-nonterminal($state, &quot;");
                                                            #line 747 "PrintXSLT.cpp.template"
                                                                print(methodPrefix);
                                                            #line 993 "PrintXSLT.cpp"
  append(L"&quot;, &quot;end&quot;, &quot;");
                                                            #line 749 "PrintXSLT.cpp.template"
                                                                print(node->name);
                                                            #line 997 "PrintXSLT.cpp"
  append(L"&quot;), $state\"/>");
                                                            #line 751 "PrintXSLT.cpp.template"
                                                                decreaseIndent();
                                                              }
                                                            #line 1002 "PrintXSLT.cpp"
  append(L"\n");
  append(L"</xsl:function>\n");
                                                            #line 755 "PrintXSLT.cpp.template"
                                                              setIndent(0);
                                                            }

                                                            void PrintXSLT::visitRef(Ref *node)
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
                                                            #line 1023 "PrintXSLT.cpp"
  append(L"\n");
  append(L"<xsl:variable name=\"state\" select=\"p:whitespace($input, $state)\"/>");
                                                            #line 774 "PrintXSLT.cpp.template"
                                                                  whitespaceCalled = true;
                                                                }
                                                            #line 1029 "PrintXSLT.cpp"
  append(L"\n");
  append(L"<xsl:variable name=\"state\" select=\"\n");
  append(L"  if ($state[$p:error]) then\n");
  append(L"    $state\n");
  append(L"  else\n");
  append(L"    p:");
                                                            #line 781 "PrintXSLT.cpp.template"
                                                                print(methodPrefix);
                                                            #line 1038 "PrintXSLT.cpp"
  append(L"-");
                                                            #line 782 "PrintXSLT.cpp.template"
                                                                print(node->name);
                                                            #line 1042 "PrintXSLT.cpp"
  append(L"($input, $state)\n");
  append(L"\"/>");
                                                            #line 784 "PrintXSLT.cpp.template"
                                                              }
                                                            }

                                                            void PrintXSLT::visitString(String *node)
                                                            {
                                                              printLookahead(1, *grammar->epsilon, 1, node->getLookahead(), node->findsLookahead);
                                                              automaticSemicolonInsertion(node);
                                                              printConsume(node->lexical->tokenCode);
                                                            }

                                                            void PrintXSLT::visitProcessingInstruction(ProcessingInstruction *node)
                                                            {
                                                              int spaces = Math::max(0, static_cast<int>(piIndent) - getIndent());
                                                              if (variant != 0 && wcscmp(node->target, variant) == 0)
                                                              {
                                                            #line 1061 "PrintXSLT.cpp"
  append(L"\n");
                                                            #line 800 "PrintXSLT.cpp.template"
                                                                print(spaces, L" ");
                                                            #line 1065 "PrintXSLT.cpp"
  append(L"<!-- line ");
                                                            #line 801 "PrintXSLT.cpp.template"
                                                                  print(format.toString<wchar_t>(node->line));
                                                            #line 1069 "PrintXSLT.cpp"
  append(L" \"");
                                                            #line 802 "PrintXSLT.cpp.template"
                                                                print(node->fileName);
                                                            #line 1073 "PrintXSLT.cpp"
  append(L"\" -->\n");
                                                            #line 804 "PrintXSLT.cpp.template"
                                                                print(spaces, L" ");
                                                                wchar_t *reIndented = Format::reIndent(node->content, spaces);
                                                                print(reIndented);
                                                                free(reIndented);
                                                            #line 1080 "PrintXSLT.cpp"
  append(L"\n");
                                                            #line 809 "PrintXSLT.cpp.template"
                                                                print(spaces, L" ");
                                                            #line 1084 "PrintXSLT.cpp"
  append(L"<!-- line ");
                                                            #line 810 "PrintXSLT.cpp.template"
                                                                  print(format.toString<wchar_t>(lineNo + 1));
                                                            #line 1088 "PrintXSLT.cpp"
  append(L" \"");
                                                            #line 811 "PrintXSLT.cpp.template"
                                                                print(wFileName);
                                                            #line 1092 "PrintXSLT.cpp"
  append(L"\" -->");
                                                            #line 812 "PrintXSLT.cpp.template"
                                                               }
                                                            }

                                                            void PrintXSLT::printUtilities()
                                                            {
                                                              setIndent(1);
                                                              if (isLrParser)
                                                              {
                                                                if (grammar->states->hasLookback)
                                                                {
                                                            #line 1105 "PrintXSLT.cpp"
  append(L"\n");
  append(L"<!--");
  append(L"~");
  append(L"\n");
  append(L" ! Compare a lookback code to a sorted, zero-terminated list of pairs at\n");
  append(L" ! the given index into the LOOKBACK table. A matching first code in a\n");
  append(L" ! pair will cause its second code to be returned. The list is sorted in\n");
  append(L" ! descending order of first codes, so it is safe to stop when the first\n");
  append(L" ! code is less than what is searched for.\n");
  append(L" !\n");
  append(L" ! @param $x the lookback code to search for.\n");
  append(L" ! @param $i the index into the LOOKBACK table.\n");
  append(L" ! @return the new lookback code as the second code from a pair with a\n");
  append(L" ! matching first code.\n");
  append(L"-->\n");
  append(L"<xsl:function name=\"p:lookback\">\n");
  append(L"  <xsl:param name=\"x\" as=\"xs:integer\"/>\n");
  append(L"  <xsl:param name=\"i\" as=\"xs:integer\"/>\n");
  append(L"\n");
  append(L"  <xsl:variable name=\"l\" select=\"$p:LOOKBACK[$i + 1]\"/>\n");
  append(L"  <xsl:sequence select=\"\n");
  append(L"    if ($l gt $x) then\n");
  append(L"      p:lookback($x, $i + 2)\n");
  append(L"    else if ($l eq $x) then\n");
  append(L"      $p:LOOKBACK[$i + 2]\n");
  append(L"    else\n");
  append(L"      0\n");
  append(L"  \"/>\n");
  append(L"</xsl:function>\n");
  append(L"\n");
  append(L"<!--");
  append(L"~");
  append(L"\n");
  append(L" ! Calculate number of symbols to remove from LR stack for reduction by\n");
  append(L" ! walking through lookback codes of reduction and stack entries. A single\n");
  append(L" ! invocation combines two of those, more are handled in tail recursion.\n");
  append(L" !\n");
  append(L" ! @param $code the reduction lookback code.\n");
  append(L" ! @param $count the initial count value.\n");
  append(L" ! @param $stack the LR stack.\n");
  append(L" ! @param $t the stack running index.\n");
  append(L" ! @return the initial count value, increased by the number of calculations\n");
  append(L" ! yielding a non-zero lookback code.\n");
  append(L"-->\n");
  append(L"<xsl:function name=\"p:count\">\n");
  append(L"  <xsl:param name=\"code\" as=\"xs:integer\"/>\n");
  append(L"  <xsl:param name=\"count\" as=\"xs:integer\"/>\n");
  append(L"  <xsl:param name=\"stack\" as=\"xs:integer*\"/>\n");
  append(L"  <xsl:param name=\"t\" as=\"xs:integer\"/>\n");
  append(L"\n");
  append(L"  <xsl:choose>\n");
  append(L"    <xsl:when test=\"$stack[$t] lt 0\">\n");
  append(L"      <xsl:sequence select=\"$count\"/>\n");
  append(L"    </xsl:when>\n");
  append(L"    <xsl:otherwise>\n");
  append(L"      <xsl:variable name=\"code\" select=\"p:lookback($stack[$t + 1], $p:LOOKBACK[$code + 1])\"/>\n");
  append(L"      <xsl:sequence select=\"\n");
  append(L"        if ($code eq 0) then\n");
  append(L"          $count\n");
  append(L"        else\n");
  append(L"          p:count($code, $count + 1, $stack, $t - 3)\n");
  append(L"      \"/>\n");
  append(L"    </xsl:otherwise>\n");
  append(L"  </xsl:choose>\n");
  append(L"</xsl:function>\n");
                                                            #line 883 "PrintXSLT.cpp.template"
                                                                }
                                                                if (grammar->useGlr)
                                                                {
                                                            #line 1175 "PrintXSLT.cpp"
  append(L"\n");
  append(L"<!--");
  append(L"~");
  append(L"\n");
  append(L" ! Determine index of the next thread that must be parsed, by comparing\n");
  append(L" ! threads in $threads starting at $i with the candidate at $thread.\n");
  append(L" !\n");
  append(L" ! @param $threads the sequence of all current threads.\n");
  append(L" ! @param $thread the index of the next thread candidate.\n");
  append(L" ! @param $i the index where to start searching.\n");
  append(L" ! @return the index of the next thread.\n");
  append(L"-->\n");
  append(L"<xsl:function name=\"p:next-thread\">\n");
  append(L"  <xsl:param name=\"threads\" as=\"map(*)*\"/>\n");
  append(L"  <xsl:param name=\"thread\" as=\"xs:integer\"/>\n");
  append(L"  <xsl:param name=\"i\" as=\"xs:integer\"/>\n");
  append(L"\n");
  append(L"  <xsl:choose>\n");
  append(L"    <xsl:when test=\"$i gt count($threads)\">\n");
  append(L"      <xsl:sequence select=\"$thread\"/>\n");
  append(L"    </xsl:when>\n");
  append(L"    <xsl:otherwise>\n");
  append(L"      <xsl:variable name=\"thread\">\n");
  append(L"        <xsl:choose>\n");
  append(L"          <xsl:when test=\"$threads[$thread]?accepted ne $threads[$i]?accepted\">\n");
  append(L"            <xsl:sequence select=\"if ($threads[$thread]?accepted) then $i else $thread\"/>\n");
  append(L"          </xsl:when>\n");
  append(L"          <xsl:when test=\"$threads[$thread]?lexer-state[$p:e0] ne $threads[$i]?lexer-state[$p:e0]\">\n");
  append(L"            <xsl:sequence select=\"if ($threads[$thread]?lexer-state[$p:e0] lt $threads[$i]?lexer-state[$p:e0]) then $thread else $i\"/>\n");
  append(L"          </xsl:when>\n");
  append(L"          <xsl:otherwise>\n");
  append(L"            <xsl:sequence select=\"if ($threads[$thread]?id le $threads[$i]?id) then $thread else $i\"/>\n");
  append(L"          </xsl:otherwise>\n");
  append(L"        </xsl:choose>\n");
  append(L"      </xsl:variable>\n");
  append(L"      <xsl:sequence select=\"p:next-thread($threads, $thread, $i + 1)\"/>\n");
  append(L"    </xsl:otherwise>\n");
  append(L"  </xsl:choose>\n");
  append(L"</xsl:function>\n");
  append(L"\n");
  append(L"<!--");
  append(L"~");
  append(L"\n");
  append(L" ! Compare two parsing threads for equality. A result of false indicates an\n");
  append(L" ! ambiguity.\n");
  append(L" !\n");
  append(L" ! @param $t1 the first thread data.\n");
  append(L" ! @param $t2 the second thread data.\n");
  append(L" ! @return true(), if threads are equal.\n");
  append(L"-->\n");
  append(L"<xsl:function name=\"p:thread-equals\" as=\"xs:boolean\">\n");
  append(L"  <xsl:param name=\"t1\" as=\"map(*)\"/>\n");
  append(L"  <xsl:param name=\"t2\" as=\"map(*)\"/>\n");
  append(L"\n");
  append(L"  <xsl:sequence select=\"\n");
  append(L"    if ($t1?accepted ne $t2?accepted) then false() else\n");
  append(L"    if ($t1?b1 ne $t2?lexer-state[$p:b1]) then false() else\n");
  append(L"    if ($t1?e1 ne $t2?lexer-state[$p:e1]) then false() else\n");
  append(L"    if ($t1?l1 ne $t2?lexer-state[$p:l1]) then false() else\n");
  append(L"    if ($t1?state ne $t2?state) then false() else\n");
  append(L"    if ($t1?action ne $t2?action) then false() else deep-equal($t1?stack, $t2?stack)\n");
  append(L"  \"/>\n");
  append(L"</xsl:function>\n");
  append(L"\n");
  append(L"<!--");
  append(L"~");
  append(L"\n");
  append(L" ! Perform GLR parsing by selecting a thread and invoke the LR parse function\n");
  append(L" ! on it for a single token. Process result with respect to thread management.\n");
  append(L" !\n");
  append(L" ! @param $input the input string.\n");
  append(L" ! @param $target the target symbol code.\n");
  append(L" ! @param $max-id the maximum thread id.\n");
  append(L" ! @param $threads the sequence of all current threads.\n");
  append(L" ! @return the lexer state of the accepting (or error) thread.\n");
  append(L"-->\n");
  append(L"<xsl:function name=\"p:parse-glr\">\n");
  append(L"  <xsl:param name=\"input\" as=\"xs:string\"/>\n");
  append(L"  <xsl:param name=\"target\" as=\"xs:integer\"/>\n");
  append(L"  <xsl:param name=\"max-id\" as=\"xs:integer\"/>\n");
  append(L"  <xsl:param name=\"threads\" as=\"map(*)+\"/>\n");
  append(L"\n");
  append(L"  <xsl:variable name=\"i\" select=\"p:next-thread($threads, 1, 2)\"/>\n");
  append(L"  <xsl:variable name=\"thread\" select=\"$threads[$i]\"/>\n");
  append(L"  <xsl:variable name=\"lexer-state\" select=\"$thread?lexer-state\"/>\n");
  append(L"  <xsl:choose>\n");
  append(L"    <xsl:when test=\"$thread?accepted\">\n");
  append(L"      <xsl:variable name=\"max-e0\" select=\"max($threads!?lexer-state[$p:e0])\"/>\n");
  append(L"      <xsl:variable name=\"longest-accept\" select=\"$threads[?lexer-state[$p:e0] eq $max-e0]\"/>\n");
  append(L"      <xsl:choose>\n");
  append(L"        <xsl:when test=\"count($longest-accept) eq 1\">\n");
  append(L"          <xsl:sequence select=\"$longest-accept?lexer-state\"/>\n");
  append(L"        </xsl:when>\n");
  append(L"        <xsl:otherwise>\n");
  append(L"          <xsl:sequence select=\"p:reject-ambiguity($longest-accept[1]");
                                                            #line 975 "PrintXSLT.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 1274 "PrintXSLT.cpp"
  append(L", $longest-accept[2]");
                                                            #line 978 "PrintXSLT.cpp.template"
                                                                }
                                                            #line 1278 "PrintXSLT.cpp"
  append(L")\"/>\n");
  append(L"        </xsl:otherwise>\n");
  append(L"      </xsl:choose>\n");
  append(L"    </xsl:when>\n");
  append(L"    <xsl:otherwise>\n");
  append(L"      <xsl:variable name=\"threads\" select=\"(subsequence($threads, 1, $i - 1), subsequence($threads, $i + 1))\"/>\n");
  append(L"      <xsl:variable name=\"other\" select=\"if (exists($threads)) then $threads[p:next-thread($threads, 1, 2)] else ()\"/>\n");
  append(L"      <xsl:choose>\n");
  append(L"        <xsl:when test=\"exists($other) and p:thread-equals($thread, $other)\">\n");
  append(L"          <xsl:sequence select=\"p:reject-ambiguity($thread");
                                                            #line 989 "PrintXSLT.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 1292 "PrintXSLT.cpp"
  append(L", $other");
                                                            #line 992 "PrintXSLT.cpp.template"
                                                                }
                                                            #line 1296 "PrintXSLT.cpp"
  append(L")\"/>\n");
  append(L"        </xsl:when>\n");
  append(L"        <xsl:otherwise>\n");
  append(L"          <xsl:variable name=\"thread\" select=\"p:parse($input, $target, $max-id, $thread)\"/>\n");
  append(L"          <xsl:variable name=\"lexer-state\" select=\"$thread?lexer-state\"/>\n");
  append(L"          <xsl:sequence select=\"\n");
  append(L"            if (count($thread) gt 1) then\n");
  append(L"              p:parse-glr($input, $target, $max-id + 1, ($threads, $thread))\n");
  append(L"            else if (not($lexer-state[$p:error])) then\n");
  append(L"              p:parse-glr($input, $target, $max-id, ($threads, $thread))\n");
  append(L"            else if (exists($threads)) then\n");
  append(L"              p:parse-glr($input, $target, $max-id, $threads)\n");
  append(L"            else\n");
  append(L"              $lexer-state\n");
  append(L"          \"/>\n");
  append(L"        </xsl:otherwise>\n");
  append(L"      </xsl:choose>\n");
  append(L"    </xsl:otherwise>\n");
  append(L"  </xsl:choose>\n");
  append(L"</xsl:function>\n");
  append(L"\n");
  append(L"<!--");
  append(L"~");
  append(L"\n");
  append(L" ! Raise an error for ambiguous input.\n");
  append(L" !\n");
  append(L" ! @param $thread the parsing thread data.");
                                                            #line 1017 "PrintXSLT.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 1327 "PrintXSLT.cpp"
  append(L"\n");
  append(L" ! @param $other the parsing thread data of the other thread.");
                                                            #line 1020 "PrintXSLT.cpp.template"
                                                                }
                                                            #line 1332 "PrintXSLT.cpp"
  append(L"\n");
  append(L" ! @return a lexer state containing an error element describing the ambiguity.\n");
  append(L"-->\n");
  append(L"<xsl:function name=\"p:reject-ambiguity\" as=\"item()+\">\n");
  append(L"  <xsl:param name=\"thread\" as=\"map(*)\"/>");
                                                            #line 1025 "PrintXSLT.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 1341 "PrintXSLT.cpp"
  append(L"\n");
  append(L"  <xsl:param name=\"other\" as=\"map(*)\"/>");
                                                            #line 1028 "PrintXSLT.cpp.template"
                                                                }
                                                            #line 1346 "PrintXSLT.cpp"
  append(L"\n");
  append(L"\n");
  append(L"  <xsl:variable name=\"lexer-state\" select=\"$thread?lexer-state\"/>");
                                                            #line 1032 "PrintXSLT.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 1353 "PrintXSLT.cpp"
  append(L"\n");
  append(L"  <xsl:variable name=\"first-tree\" select=\"$lexer-state[last()]\"/>\n");
  append(L"  <xsl:variable name=\"second-tree\" select=\"$other?lexer-state[last()]\"/>");
                                                            #line 1037 "PrintXSLT.cpp.template"
                                                                }
                                                            #line 1359 "PrintXSLT.cpp"
  append(L"\n");
  append(L"  <xsl:variable name=\"node\">\n");
  append(L"    <xsl:element name=\"error\">\n");
  append(L"      <xsl:attribute name=\"b\" select=\"$thread?stack[last() - 2]\"/>\n");
  append(L"      <xsl:attribute name=\"e\" select=\"$lexer-state[$p:e0]\"/>\n");
  append(L"      <xsl:attribute name=\"ambiguous-input\" select=\"true()\"/>");
                                                            #line 1043 "PrintXSLT.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 1369 "PrintXSLT.cpp"
  append(L"\n");
  append(L"      <xsl:element name=\"AMBIGUOUS\">\n");
  append(L"        <xsl:element name=\"ALTERNATIVE\">\n");
  append(L"          <xsl:sequence select=\"p:rewrite-ambiguity($first-tree, $second-tree, true())\"/>\n");
  append(L"        </xsl:element>\n");
  append(L"        <xsl:element name=\"ALTERNATIVE\">\n");
  append(L"          <xsl:sequence select=\"p:rewrite-ambiguity($second-tree, $first-tree, true())\"/>\n");
  append(L"        </xsl:element>\n");
  append(L"      </xsl:element>");
                                                            #line 1053 "PrintXSLT.cpp.template"
                                                                }
                                                            #line 1381 "PrintXSLT.cpp"
  append(L"\n");
  append(L"    </xsl:element>\n");
  append(L"  </xsl:variable>\n");
  append(L"  <xsl:sequence select=\"\n");
  append(L"    subsequence($lexer-state, 1, $p:error - 1),\n");
  append(L"    $node/node(),\n");
  append(L"    subsequence($lexer-state, $p:error + 1)\n");
  append(L"  \"/>\n");
  append(L"</xsl:function>\n");
                                                            #line 1063 "PrintXSLT.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 1394 "PrintXSLT.cpp"
  append(L"\n");
  append(L"<!--");
  append(L"~");
  append(L"\n");
  append(L" ! Rewrite a parse tree fragment $first, combining elements into an \"UNAMBIGUOUS\"\n");
  append(L" ! element as long as they match elements in $second, in node order.\n");
  append(L" !\n");
  append(L" ! @param $first the first node.\n");
  append(L" ! @param $second the second node.\n");
  append(L" ! @return $first rewritten, with initial element nodes possibly combined.\n");
  append(L"-->\n");
  append(L"<xsl:function name=\"p:rewrite-ambiguity\">\n");
  append(L"  <xsl:param name=\"first\" as=\"node()\"/>\n");
  append(L"  <xsl:param name=\"second\" as=\"node()?\"/>\n");
  append(L"  <xsl:param name=\"unambiguous\" as=\"xs:boolean\"/>\n");
  append(L"\n");
  append(L"  <xsl:choose>\n");
  append(L"    <xsl:when test=\"$first instance of element()\">\n");
  append(L"      <xsl:choose>\n");
  append(L"        <xsl:when test=\"$unambiguous and deep-equal($first, $second)\">\n");
  append(L"          <xsl:variable name=\"node\">\n");
  append(L"            <xsl:element name=\"UNAMBIGUOUS\">\n");
  append(L"              <xsl:sequence select=\"string($first)\"/>\n");
  append(L"            </xsl:element>\n");
  append(L"          </xsl:variable>\n");
  append(L"          <xsl:sequence select=\"$node/node()\"/>\n");
  append(L"        </xsl:when>\n");
  append(L"        <xsl:otherwise>\n");
  append(L"          <xsl:variable name=\"node\">\n");
  append(L"            <xsl:element name=\"{node-name($first)}\">\n");
  append(L"              <xsl:for-each select=\"1 to count($first/node())\">\n");
  append(L"                <xsl:variable name=\"i\" select=\".\"/>\n");
  append(L"                <xsl:sequence select=\"\n");
  append(L"                  p:rewrite-ambiguity\n");
  append(L"                  (\n");
  append(L"                    $first/node()[$i], $second/node()[$i],\n");
  append(L"                    $unambiguous and (every $j in 1 to $i - 1 satisfies deep-equal($first/node()[$j], $second/node()[$j]))\n");
  append(L"                  )\n");
  append(L"                \"/>\n");
  append(L"              </xsl:for-each>\n");
  append(L"            </xsl:element>\n");
  append(L"          </xsl:variable>\n");
  append(L"          <xsl:sequence select=\"$node/node()\"/>\n");
  append(L"        </xsl:otherwise>\n");
  append(L"      </xsl:choose>\n");
  append(L"    </xsl:when>\n");
  append(L"    <xsl:otherwise>\n");
  append(L"      <xsl:sequence select=\"$first\"/>\n");
  append(L"    </xsl:otherwise>\n");
  append(L"  </xsl:choose>\n");
  append(L"</xsl:function>\n");
                                                            #line 1114 "PrintXSLT.cpp.template"
                                                                }
                                                            #line 1448 "PrintXSLT.cpp"
  append(L"\n");
  append(L"<!--");
  append(L"~");
  append(L"\n");
  append(L" ! Construct a new map containing data for one parsing thread.\n");
  append(L" !\n");
  append(L" ! @param $id the parsing thread id.\n");
  append(L" ! @param $accepted true(), if this thread has accepted.\n");
  append(L" ! @param $state the LR parser state number.\n");
  append(L" ! @param $action the action code.\n");
  append(L" ! @param $nonterminal current nonterminal, -1 if processing a terminal.\n");
  append(L" ! @param $bw the whitespace begin input index.\n");
  append(L" ! @param $bs the symbol begin input index.\n");
  append(L" ! @param $es the symbol end input index.\n");
  append(L" ! @param $stack the LR stack.\n");
  append(L" ! @param $lexer-state lexer state, error indicator, and result stack.\n");
  append(L" ! @return the thread data map.\n");
  append(L"-->\n");
  append(L"<xsl:function name=\"p:thread\" as=\"map(*)\">\n");
  append(L"  <xsl:param name=\"id\" as=\"xs:integer\"/>\n");
  append(L"  <xsl:param name=\"accepted\" as=\"xs:boolean\"/>\n");
  append(L"  <xsl:param name=\"state\" as=\"xs:integer\"/>\n");
  append(L"  <xsl:param name=\"action\" as=\"xs:integer\"/>\n");
  append(L"  <xsl:param name=\"nonterminal\" as=\"xs:integer\"/>\n");
  append(L"  <xsl:param name=\"bw\" as=\"xs:integer\"/>\n");
  append(L"  <xsl:param name=\"bs\" as=\"xs:integer\"/>\n");
  append(L"  <xsl:param name=\"es\" as=\"xs:integer\"/>\n");
  append(L"  <xsl:param name=\"stack\" as=\"xs:integer*\"/>\n");
  append(L"  <xsl:param name=\"lexer-state\" as=\"item()+\"/>\n");
  append(L"\n");
  append(L"  <xsl:sequence select=\"\n");
  append(L"    map\n");
  append(L"    {\n");
  append(L"      'id': $id,\n");
  append(L"      'accepted': $accepted,\n");
  append(L"      'state': $state,\n");
  append(L"      'action': $action,\n");
  append(L"      'nonterminal': $nonterminal,\n");
  append(L"      'bw': $bw,\n");
  append(L"      'bs': $bs,\n");
  append(L"      'es': $es,\n");
  append(L"      'stack': $stack,\n");
  append(L"      'lexer-state': $lexer-state\n");
  append(L"    }\n");
  append(L"  \"/>\n");
  append(L"</xsl:function>\n");
                                                            #line 1159 "PrintXSLT.cpp.template"
                                                                }
                                                            #line 1497 "PrintXSLT.cpp"
  append(L"\n");
  append(L"<!--");
  append(L"~");
  append(L"\n");
  append(L" ! Parse input for given target symbol using LR tables. Each invocation\n");
  append(L" ! handles one parsing action (shift, reduce, shift+reduce, accept).\n");
  append(L" ! Subsequent actions are handled by tail-recursion.\n");
  append(L" !\n");
  append(L" ! @param $input the input string.\n");
  append(L" ! @param $target the target symbol code.");
                                                            #line 1167 "PrintXSLT.cpp.template"
                                                                if (grammar->useGlr)
                                                                {
                                                            #line 1511 "PrintXSLT.cpp"
  append(L"\n");
  append(L" ! @param $max-id the maximum thread id.\n");
  append(L" ! @param $thread the parsing thread data.");
                                                            #line 1171 "PrintXSLT.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1519 "PrintXSLT.cpp"
  append(L"\n");
  append(L" ! @param $state the LR parser state number.\n");
  append(L" ! @param $action the action code.\n");
  append(L" ! @param $nonterminal current nonterminal, -1 if processing a terminal.\n");
  append(L" ! @param $bw the whitespace begin input index.\n");
  append(L" ! @param $bs the symbol begin input index.\n");
  append(L" ! @param $es the symbol end input index.\n");
  append(L" ! @param $stack the LR stack.\n");
  append(L" ! @param $lexer-state lexer state, error indicator, and result stack.");
                                                            #line 1183 "PrintXSLT.cpp.template"
                                                                }
                                                            #line 1531 "PrintXSLT.cpp"
  append(L"\n");
  append(L" ! @return the updated state.\n");
  append(L"-->\n");
  append(L"<xsl:function name=\"p:parse\">\n");
  append(L"  <xsl:param name=\"input\" as=\"xs:string\"/>\n");
  append(L"  <xsl:param name=\"target\" as=\"xs:integer\"/>");
                                                            #line 1189 "PrintXSLT.cpp.template"
                                                                if (grammar->useGlr)
                                                                {
                                                            #line 1541 "PrintXSLT.cpp"
  append(L"\n");
  append(L"  <xsl:param name=\"max-id\" as=\"xs:integer\"/>\n");
  append(L"  <xsl:param name=\"thread\" as=\"map(*)\"/>\n");
  append(L"\n");
  append(L"  <xsl:variable name=\"lexer-state\" select=\"$thread?lexer-state\"/>\n");
  append(L"  <xsl:choose>\n");
  append(L"    <xsl:when test=\"$lexer-state[$p:error]\">\n");
  append(L"      <xsl:sequence select=\"$thread\"/>\n");
  append(L"    </xsl:when>\n");
  append(L"    <xsl:otherwise>\n");
  append(L"      <xsl:variable name=\"state\" select=\"$thread?state\"/>\n");
  append(L"      <xsl:variable name=\"action\" select=\"$thread?action\"/>\n");
  append(L"      <xsl:variable name=\"nonterminal\" select=\"$thread?nonterminal\"/>\n");
  append(L"      <xsl:variable name=\"bw\" select=\"$thread?bw\"/>\n");
  append(L"      <xsl:variable name=\"bs\" select=\"$thread?bs\"/>\n");
  append(L"      <xsl:variable name=\"es\" select=\"$thread?es\"/>\n");
  append(L"      <xsl:variable name=\"stack\" select=\"$thread?stack\"/>");
                                                            #line 1207 "PrintXSLT.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1563 "PrintXSLT.cpp"
  append(L"\n");
  append(L"  <xsl:param name=\"state\" as=\"xs:integer\"/>\n");
  append(L"  <xsl:param name=\"action\" as=\"xs:integer\"/>\n");
  append(L"  <xsl:param name=\"nonterminal\" as=\"xs:integer\"/>\n");
  append(L"  <xsl:param name=\"bw\" as=\"xs:integer\"/>\n");
  append(L"  <xsl:param name=\"bs\" as=\"xs:integer\"/>\n");
  append(L"  <xsl:param name=\"es\" as=\"xs:integer\"/>\n");
  append(L"  <xsl:param name=\"stack\" as=\"xs:integer*\"/>\n");
  append(L"  <xsl:param name=\"lexer-state\" as=\"item()+\"/>\n");
  append(L"\n");
  append(L"  <xsl:choose>\n");
  append(L"    <xsl:when test=\"$lexer-state[$p:error]\">\n");
  append(L"      <xsl:sequence select=\"$lexer-state\"/>\n");
  append(L"    </xsl:when>\n");
  append(L"    <xsl:otherwise>");
                                                            #line 1224 "PrintXSLT.cpp.template"
                                                                }
                                                                /*
                                                            #line 1582 "PrintXSLT.cpp"
  append(L"\n");
  append(L"      <xsl:sequence select=\"trace((), concat('compound action: ', string($action), ', action: ', string($action mod ");
                                                            #line 1228 "PrintXSLT.cpp.template"
                                                                print(format.toString<wchar_t>(1 << (int) LrStates::actionBits));
                                                            #line 1587 "PrintXSLT.cpp"
  append(L"), ', lookback: ', string(($action idiv ");
                                                            #line 1229 "PrintXSLT.cpp.template"
                                                                print(format.toString<wchar_t>(1 << (int) LrStates::actionBits));
                                                            #line 1591 "PrintXSLT.cpp"
  append(L") mod ");
                                                            #line 1230 "PrintXSLT.cpp.template"
                                                                print(format.toString<wchar_t>(1 << grammar->states->dominoBits));
                                                            #line 1595 "PrintXSLT.cpp"
  append(L"),  ', argument: ', string($action idiv ");
                                                            #line 1231 "PrintXSLT.cpp.template"
                                                                print(format.toString<wchar_t>(1 << (grammar->states->dominoBits + LrStates::actionBits)));
                                                            #line 1599 "PrintXSLT.cpp"
  append(L")");
                                                            #line 1233 "PrintXSLT.cpp.template"
      
                                                            #line 1603 "PrintXSLT.cpp"
  append(L"))\"/>");
                                                            #line 1234 "PrintXSLT.cpp.template"
                                                                */
                                                                if (trace)
                                                                {
                                                            #line 1609 "PrintXSLT.cpp"
  append(L"\n");
  append(L"      <xsl:variable name=\"trace\" select=\"\n");
  append(L"        string-join\n");
  append(L"        (\n");
  append(L"          (\n");
  append(L"            '  &lt;parse ");
                                                            #line 1242 "PrintXSLT.cpp.template"
                                                                  if (grammar->useGlr)
                                                                  {
                                                            #line 1619 "PrintXSLT.cpp"
  append(L"thread=&quot;', $thread?id, '&quot; offset=&quot;', $lexer-state[$p:e0], '&quot; ");
                                                            #line 1245 "PrintXSLT.cpp.template"
                                                                  }
                                                            #line 1623 "PrintXSLT.cpp"
  append(L"state=&quot;', string($state), '&quot; input=&quot;',\n");
  append(L"            $p:NONTERMINAL[$nonterminal + 1],\n");
  append(L"            ' '[$nonterminal ge 0 and $lexer-state[$p:l1] gt 0],\n");
  append(L"            p:xml-escape(p:lookahead-string($lexer-state)),\n");
  append(L"            '&quot; action=&quot;'\n");
  append(L"          ),\n");
  append(L"          ''\n");
  append(L"        )\n");
  append(L"      \"/>");
                                                            #line 1255 "PrintXSLT.cpp.template"
                                                                }
                                                            #line 1635 "PrintXSLT.cpp"
  append(L"\n");
  append(L"      <xsl:variable name=\"argument\" select=\"$action idiv ");
                                                            #line 1257 "PrintXSLT.cpp.template"
                                                                print(format.toString<wchar_t>(1 << (grammar->states->dominoBits + LrStates::actionBits)));
                                                            #line 1640 "PrintXSLT.cpp"
  append(L"\"/>\n");
  append(L"      <xsl:variable name=\"lookback\" select=\"($action idiv ");
                                                            #line 1259 "PrintXSLT.cpp.template"
                                                                print(format.toString<wchar_t>(1 << (int) LrStates::actionBits));
                                                            #line 1645 "PrintXSLT.cpp"
  append(L") mod ");
                                                            #line 1261 "PrintXSLT.cpp.template"
                                                                print(format.toString<wchar_t>(1 << grammar->states->dominoBits));
                                                            #line 1649 "PrintXSLT.cpp"
  append(L"\"/>\n");
  append(L"      <xsl:variable name=\"action\" select=\"$action mod ");
                                                            #line 1263 "PrintXSLT.cpp.template"
                                                                print(format.toString<wchar_t>(1 << (int) LrStates::actionBits));
                                                            #line 1654 "PrintXSLT.cpp"
  append(L"\"/>\n");
  append(L"      <xsl:choose>\n");
  append(L"        <xsl:when test=\"$action eq 6\"> <!-- SHIFT+ACCEPT -->\n");
  append(L"          <xsl:sequence select=\"");
                                                            #line 1267 "PrintXSLT.cpp.template"
                                                                if (trace)
                                                                {
                                                            #line 1662 "PrintXSLT.cpp"
  append(L"\n");
  append(L"            p:trace(concat($trace, 'accept&quot;/>')),\n");
  append(L"            ");
                                                            #line 1271 "PrintXSLT.cpp.template"
                                                                }
                                                                if (grammar->useGlr)
                                                                {
                                                            #line 1670 "PrintXSLT.cpp"
  append(L"p:thread($thread?id, true(), $state, $action, $nonterminal, $bw, $bs, $es, $stack, $lexer-state)");
                                                            #line 1275 "PrintXSLT.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1676 "PrintXSLT.cpp"
  append(L"$lexer-state");
                                                            #line 1278 "PrintXSLT.cpp.template"
                                                                }
                                                                if (trace)
                                                                {
                                                            #line 1682 "PrintXSLT.cpp"
  append(L"\n");
  append(L"          ");
                                                            #line 1282 "PrintXSLT.cpp.template"
                                                                }
                                                            #line 1687 "PrintXSLT.cpp"
  append(L"\"/>\n");
  append(L"        </xsl:when>");
                                                            #line 1284 "PrintXSLT.cpp.template"
                                                                if (grammar->useGlr)
                                                                {
                                                            #line 1693 "PrintXSLT.cpp"
  append(L"\n");
  append(L"        <xsl:when test=\"$action eq 7\"> <!-- FORK -->\n");
  append(L"          <xsl:sequence select=\"");
                                                            #line 1288 "PrintXSLT.cpp.template"
                                                                  if (trace)
                                                                  {
                                                            #line 1700 "PrintXSLT.cpp"
  append(L"\n");
  append(L"            p:trace(concat($trace, 'fork&quot;/>')),");
                                                            #line 1291 "PrintXSLT.cpp.template"
                                                                  }
                                                            #line 1705 "PrintXSLT.cpp"
  append(L"\n");
  append(L"            for $i in (1, 2)\n");
  append(L"            return p:thread(($max-id + 1, $thread?id)[$i], false(), $state, $p:APPENDIX[$argument + $i], -1, $bw, $bs, $es, $stack, $lexer-state)");
  append(L"\n");
  append(L"          \"/>\n");
  append(L"        </xsl:when>");
                                                            #line 1297 "PrintXSLT.cpp.template"
                                                                }
                                                            #line 1714 "PrintXSLT.cpp"
  append(L"\n");
  append(L"        <xsl:otherwise>\n");
  append(L"          <xsl:variable name=\"shift-reduce-symbols\" select=\"\n");
  append(L"            if ($action eq 1) then (: SHIFT :)\n");
  append(L"              ($argument, -1, -1)\n");
  append(L"            else if ($action eq 2) then (: REDUCE :)\n");
  append(L"              (-1, $argument, $lookback)");
                                                            #line 1304 "PrintXSLT.cpp.template"
                                                                if (grammar->states->hasLookback)
                                                                {
                                                            #line 1725 "PrintXSLT.cpp"
  append(L"\n");
  append(L"            else if ($action eq 3) then (: REDUCE+LOOKBACK :)\n");
  append(L"              (-1, $argument, p:count($lookback, 0, $stack, count($stack) - 1))");
                                                            #line 1309 "PrintXSLT.cpp.template"
                                                                }
                                                            #line 1731 "PrintXSLT.cpp"
  append(L"\n");
  append(L"            else if ($action eq 4) then (: SHIFT+REDUCE :)\n");
  append(L"              ($state, $argument, $lookback + 1)");
                                                            #line 1312 "PrintXSLT.cpp.template"
                                                                if (grammar->states->hasLookback)
                                                                {
                                                            #line 1738 "PrintXSLT.cpp"
  append(L"\n");
  append(L"            else if ($action eq 5) then (: SHIFT+REDUCE+LOOKBACK :)\n");
  append(L"              ($state, $argument, p:count($lookback, 1, $stack, count($stack) - 1))");
                                                            #line 1317 "PrintXSLT.cpp.template"
                                                                }
                                                            #line 1744 "PrintXSLT.cpp"
  append(L"\n");
  append(L"            else (: ERROR :)\n");
  append(L"              (-1, -1, -1)\n");
  append(L"          \"/>\n");
  append(L"          <xsl:variable name=\"shift\" select=\"$shift-reduce-symbols[1]\"/>\n");
  append(L"          <xsl:variable name=\"reduce\" select=\"$shift-reduce-symbols[2]\"/>\n");
  append(L"          <xsl:variable name=\"symbols\" select=\"$shift-reduce-symbols[3]\"/>\n");
  append(L"          <xsl:variable name=\"es\" select=\"if ($shift lt 0 or $nonterminal ge 0) then $es else $lexer-state[$p:e1]\"/>");
                                                            #line 1326 "PrintXSLT.cpp.template"
                                                                if (trace)
                                                                {
                                                            #line 1756 "PrintXSLT.cpp"
  append(L"\n");
  append(L"          <xsl:variable name=\"trace\" select=\"if ($shift lt 0) then $trace else concat($trace, 'shift')\"/>");
                                                            #line 1330 "PrintXSLT.cpp.template"
                                                                }
                                                            #line 1761 "PrintXSLT.cpp"
  append(L"\n");
  append(L"          <xsl:variable name=\"lexer-state\" select=\"\n");
  append(L"            if ($shift lt 0 or $nonterminal ge 0) then\n");
  append(L"              $lexer-state\n");
  append(L"            else\n");
  append(L"              p:consume\n");
  append(L"              (\n");
  append(L"                $lexer-state[$p:l1],\n");
  append(L"                $input,\n");
  append(L"                $lexer-state\n");
  append(L"              )\n");
  append(L"          \"/>\n");
  append(L"          <xsl:variable name=\"stack\" select=\"\n");
  append(L"            if ($shift lt 0) then\n");
  append(L"              $stack\n");
  append(L"            else\n");
  append(L"              ($stack, if ($nonterminal lt 0) then $lexer-state[$p:b0] else $bs, $state, $lookback)\n");
  append(L"          \"/>\n");
  append(L"          <xsl:variable name=\"state\" select=\"if ($shift lt 0) then $state else $shift\"/>\n");
  append(L"          <xsl:choose>\n");
  append(L"            <xsl:when test=\"$reduce lt 0\">\n");
  append(L"              <xsl:choose>\n");
  append(L"                <xsl:when test=\"$shift lt 0\">\n");
  append(L"                  <xsl:variable name=\"node\">\n");
  append(L"                    <xsl:element name=\"error\">\n");
  append(L"                      <xsl:attribute name=\"b\" select=\"$lexer-state[$p:b1]\"/>\n");
  append(L"                      <xsl:attribute name=\"e\" select=\"$lexer-state[$p:e1]\"/>\n");
  append(L"                      <xsl:if test=\"$lexer-state[$p:l1] gt 0\">\n");
  append(L"                        <xsl:attribute name=\"o\" select=\"$lexer-state[$p:l1]\"/>\n");
  append(L"                      </xsl:if>\n");
  append(L"                      <xsl:attribute name=\"s\" select=\"$p:TOKENSET[$state + 1] + 1\"/>\n");
  append(L"                    </xsl:element>\n");
  append(L"                  </xsl:variable>\n");
  append(L"                  <xsl:sequence select=\"");
                                                            #line 1364 "PrintXSLT.cpp.template"
                                                                if (trace)
                                                                {
                                                            #line 1799 "PrintXSLT.cpp"
  append(L"\n");
  append(L"                    p:trace(concat($trace, 'fail&quot;/>')),");
                                                            #line 1367 "PrintXSLT.cpp.template"
                                                                }
                                                                if (grammar->useGlr)
                                                                {
                                                            #line 1806 "PrintXSLT.cpp"
  append(L"\n");
  append(L"                    p:thread\n");
  append(L"                    (\n");
  append(L"                      $thread?id, false(), $state, 0, -1, $bw, $bs, $es, $stack,\n");
  append(L"                      (");
                                                            #line 1374 "PrintXSLT.cpp.template"
                                                                  increaseIndent(2);
                                                                }
                                                            #line 1815 "PrintXSLT.cpp"
  append(L"\n");
  append(L"                    subsequence($lexer-state, 1, $p:error - 1),\n");
  append(L"                    $node/node(),\n");
  append(L"                    subsequence($lexer-state, $p:error + 1)");
                                                            #line 1379 "PrintXSLT.cpp.template"
                                                                if (grammar->useGlr)
                                                                {
                                                                  decreaseIndent(2);
                                                            #line 1824 "PrintXSLT.cpp"
  append(L"\n");
  append(L"                      )\n");
  append(L"                    )");
                                                            #line 1385 "PrintXSLT.cpp.template"
                                                                }
                                                            #line 1830 "PrintXSLT.cpp"
  append(L"\n");
  append(L"                  \"/>\n");
  append(L"                </xsl:when>\n");
  append(L"                <xsl:otherwise>\n");
  append(L"                  <xsl:variable name=\"lexer-state\" select=\"p:predict($input, $lexer-state, $state");
                                                            #line 1391 "PrintXSLT.cpp.template"
                                                                if (grammar->useGlr)
                                                                {
                                                            #line 1839 "PrintXSLT.cpp"
  append(L", $thread?id");
                                                            #line 1393 "PrintXSLT.cpp.template"
                                                                }
                                                            #line 1843 "PrintXSLT.cpp"
  append(L")\"/>");
  append(L"\n");
  append(L"                  <xsl:sequence select=\"");
                                                            #line 1397 "PrintXSLT.cpp.template"
                                                                if (trace)
                                                                {
                                                            #line 1850 "PrintXSLT.cpp"
  append(L"\n");
  append(L"                    p:trace(concat($trace, '&quot;/&gt;')),\n");
  append(L"                    ");
                                                            #line 1401 "PrintXSLT.cpp.template"
                                                                }
                                                                if (grammar->useGlr)
                                                                {
                                                            #line 1858 "PrintXSLT.cpp"
  append(L"p:thread($thread?id, false(), $state, $lexer-state[$p:lk], -1, $bw, $bs, $es, $stack, $lexer-state)");
                                                            #line 1405 "PrintXSLT.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1864 "PrintXSLT.cpp"
  append(L"p:parse($input, $target, $state, $lexer-state[$p:lk], -1, $bw, $bs, $es, $stack, $lexer-state)");
                                                            #line 1409 "PrintXSLT.cpp.template"
                                                                }
                                                                if (trace)
                                                                {
                                                            #line 1870 "PrintXSLT.cpp"
  append(L"\n");
  append(L"                  ");
                                                            #line 1414 "PrintXSLT.cpp.template"
                                                                }
                                                            #line 1875 "PrintXSLT.cpp"
  append(L"\"/>\n");
  append(L"                </xsl:otherwise>\n");
  append(L"              </xsl:choose>\n");
  append(L"            </xsl:when>\n");
  append(L"            <xsl:otherwise>");
                                                            #line 1419 "PrintXSLT.cpp.template"
                                                                if (trace)
                                                                {
                                                            #line 1884 "PrintXSLT.cpp"
  append(L"\n");
  append(L"              <xsl:variable name=\"trace\" select=\"concat($trace, if ($shift lt 0) then '' else ' ', 'reduce&quot; nonterminal=&quot;', $p:NONTERMINAL[$reduce + 1], '&quot; count=&quot;', $symbols, '&quot;/>')\"/>");
                                                            #line 1423 "PrintXSLT.cpp.template"
                                                                }
                                                            #line 1889 "PrintXSLT.cpp"
  append(L"\n");
  append(L"              <xsl:variable name=\"state\" select=\"if ($symbols gt 0) then $stack[last() - 3 * $symbols + 2] else $state\"/>\n");
  append(L"              <xsl:variable name=\"bs\" select=\"if ($symbols gt 0) then $stack[last() - 3 * $symbols + 1] else $lexer-state[$p:b1]\"/>\n");
  append(L"              <xsl:variable name=\"es\" select=\"if ($symbols gt 0) then $es else $bs\"/>\n");
  append(L"              <xsl:variable name=\"stack\" select=\"if ($symbols gt 0) then subsequence($stack, 1, count($stack) - 3 * $symbols) else $stack\"/>");
                                                            #line 1428 "PrintXSLT.cpp.template"
                                                                if (tree && anyWhitespace)
                                                                {
                                                            #line 1898 "PrintXSLT.cpp"
  append(L"\n");
  append(L"              <xsl:variable name=\"lexer-state\" select=\"if ($symbols gt 0) then $lexer-state else p:whitespace($input, $lexer-state)\"/>");
                                                            #line 1432 "PrintXSLT.cpp.template"
                                                                  whitespaceCalled = true;
                                                                }
                                                            #line 1904 "PrintXSLT.cpp"
  append(L"\n");
  append(L"              <xsl:variable name=\"accept\" select=\"$reduce eq $target and count($stack) eq 3\"/>\n");
  append(L"              <xsl:variable name=\"bs\" select=\"if ($accept) then $bw else $bs\"/>\n");
  append(L"              <xsl:variable name=\"es\" select=\"if ($accept) then $lexer-state[$p:b1] else $es\"/>\n");
  append(L"              <xsl:variable name=\"bw\" select=\"if ($accept) then $es else $bw\"/>");
                                                            #line 1439 "PrintXSLT.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 1913 "PrintXSLT.cpp"
  append(L"\n");
  append(L"              <xsl:variable name=\"index\" select=\"if ($accept) then $p:result else p:first-child-node-index($lexer-state, count($lexer-state) + 1, $symbols)\"/>\n");
  append(L"              <xsl:variable name=\"node\">\n");
  append(L"                <xsl:element name=\"{$p:NONTERMINAL[$reduce + 1]}\">\n");
  append(L"                  <xsl:sequence select=\"subsequence($lexer-state, $index)\"/>\n");
  append(L"                </xsl:element>\n");
  append(L"              </xsl:variable>\n");
  append(L"              <xsl:variable name=\"lexer-state\" select=\"subsequence($lexer-state, 1, $index - 1), $node/node()\"/>");
                                                            #line 1449 "PrintXSLT.cpp.template"
                                                                }
                                                                if (hasCustomCode)
                                                                {
                                                            #line 1926 "PrintXSLT.cpp"
  append(L"\n");
  append(L"              <xsl:variable name=\"nonterminal\" select=\"$p:REDUCTION[$reduce + 1]\"/>\n");
  append(L"              <xsl:variable name=\"reduce\" select=\"$p:REDUCTION[$reduce + 2]\"/>\n");
  append(L"              <xsl:variable name=\"lexer-state\" select=\"if ($reduce lt 0) then $lexer-state else p:execute($input, $lexer-state, $reduce)\"/>");
                                                            #line 1456 "PrintXSLT.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1935 "PrintXSLT.cpp"
  append(L"\n");
  append(L"              <xsl:variable name=\"nonterminal\" select=\"$reduce\"/>");
                                                            #line 1461 "PrintXSLT.cpp.template"
                                                                }
                                                                if (grammar->useGlr)
                                                                {
                                                            #line 1942 "PrintXSLT.cpp"
  append(L"\n");
  append(L"              <xsl:variable name=\"thread\" select=\"p:thread($thread?id, false(), $state, p:goto($nonterminal, $state), $nonterminal, $bw, $bs, $es, $stack, $lexer-state)\"/>");
                                                            #line 1466 "PrintXSLT.cpp.template"
                                                                }
                                                            #line 1947 "PrintXSLT.cpp"
  append(L"\n");
  append(L"              <xsl:sequence select=\"");
                                                            #line 1468 "PrintXSLT.cpp.template"
                                                                if (trace)
                                                                {
                                                            #line 1953 "PrintXSLT.cpp"
  append(L"p:trace($trace), ");
                                                            #line 1470 "PrintXSLT.cpp.template"
                                                                }
                                                            #line 1957 "PrintXSLT.cpp"
  append(L"p:parse($input, $target, ");
                                                            #line 1471 "PrintXSLT.cpp.template"
                                                                if (grammar->useGlr)
                                                                {
                                                            #line 1962 "PrintXSLT.cpp"
  append(L"$max-id, $thread)\"/>");
                                                            #line 1473 "PrintXSLT.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1968 "PrintXSLT.cpp"
  append(L"$state, p:goto($nonterminal, $state), $nonterminal, $bw, $bs, $es, $stack, $lexer-state)\"/>");
                                                            #line 1477 "PrintXSLT.cpp.template"
                                                                }
                                                            #line 1972 "PrintXSLT.cpp"
  append(L"\n");
  append(L"            </xsl:otherwise>\n");
  append(L"          </xsl:choose>\n");
  append(L"        </xsl:otherwise>\n");
  append(L"      </xsl:choose>\n");
  append(L"    </xsl:otherwise>\n");
  append(L"  </xsl:choose>\n");
  append(L"</xsl:function>\n");
                                                            #line 1486 "PrintXSLT.cpp.template"
                                                                if (hasCustomCode)
                                                                {
                                                            #line 1984 "PrintXSLT.cpp"
  append(L"\n");
  append(L"<!--");
  append(L"~");
  append(L"\n");
  append(L" ! Update state with code annotation results.\n");
  append(L" !\n");
  append(L" ! @param $input the input string.\n");
  append(L" ! @param $state lexer state, error indicator, and result stack.\n");
  append(L" ! @param $reduce the reduce case id.\n");
  append(L" ! @return the updated state.\n");
  append(L"-->\n");
  append(L"<xsl:function name=\"p:execute\" as=\"item()+\">\n");
  append(L"  <xsl:param name=\"input\" as=\"xs:string\"/>\n");
  append(L"  <xsl:param name=\"state\" as=\"item()+\"/>\n");
  append(L"  <xsl:param name=\"reduce\" as=\"xs:integer\"/>\n");
  append(L"\n");
  append(L"  <xsl:choose>");
                                                            #line 1502 "PrintXSLT.cpp.template"
                                                                  increaseIndent(2);
                                                                  int lastContentId = grammar->distinctCodeAnnotations.size() - 1;
                                                                  for (int contentId = 0; contentId <= lastContentId; ++contentId)
                                                                  {
                                                                    ProcessingInstruction *p = grammar->distinctCodeAnnotations[contentId];
                                                            #line 2008 "PrintXSLT.cpp"
  append(L"\n");
  append(L"<xsl:when test=\"$reduce eq ");
                                                            #line 1508 "PrintXSLT.cpp.template"
                                                                    print(format.toString<wchar_t>(contentId));
                                                            #line 2013 "PrintXSLT.cpp"
  append(L"\">");
                                                            #line 1509 "PrintXSLT.cpp.template"
                                                                    visitProcessingInstruction(p);
                                                            #line 2017 "PrintXSLT.cpp"
  append(L"\n");
  append(L"  <xsl:sequence select=\"$state\"/>\n");
  append(L"</xsl:when>");
                                                            #line 1512 "PrintXSLT.cpp.template"
                                                                  }
                                                            #line 2023 "PrintXSLT.cpp"
  append(L"\n");
  append(L"<xsl:otherwise>\n");
  append(L"  <xsl:sequence select=\"$state\"/>\n");
  append(L"</xsl:otherwise>");
                                                            #line 1516 "PrintXSLT.cpp.template"
                                                                  decreaseIndent(2);
                                                            #line 2030 "PrintXSLT.cpp"
  append(L"\n");
  append(L"  </xsl:choose>\n");
  append(L"</xsl:function>\n");
                                                            #line 1520 "PrintXSLT.cpp.template"
                                                                }

                                                                if (tree)
                                                                {
                                                            #line 2039 "PrintXSLT.cpp"
  append(L"\n");
  append(L"<!--");
  append(L"~");
  append(L"\n");
  append(L" ! Decrement given index by the given number of elements on the result\n");
  append(L" ! stack, skipping any non-element nodes.\n");
  append(L" !\n");
  append(L" ! @param $state lexer state, error indicator, and result stack.\n");
  append(L" ! @param $index the index into the result stack.\n");
  append(L" ! @param $element-count the number of elements to be handled.\n");
  append(L" ! @return the decremented index.\n");
  append(L"-->\n");
  append(L"<xsl:function name=\"p:first-child-node-index\">\n");
  append(L"  <xsl:param name=\"state\" as=\"item()+\"/>\n");
  append(L"  <xsl:param name=\"index\" as=\"xs:integer\"/>\n");
  append(L"  <xsl:param name=\"element-count\" as=\"xs:integer\"/>\n");
  append(L"\n");
  append(L"  <xsl:choose>\n");
  append(L"    <xsl:when test=\"$element-count eq 0\">\n");
  append(L"      <xsl:sequence select=\"$index\"/>\n");
  append(L"    </xsl:when>\n");
  append(L"    <xsl:otherwise>\n");
  append(L"      <xsl:variable name=\"index\" select=\"$index - 1\"/>\n");
  append(L"      <xsl:variable name=\"element-count\" select=\"$element-count - (if ($state[$index] instance of element()) then 1 else 0)\"/>\n");
  append(L"      <xsl:sequence select=\"p:first-child-node-index($state, $index, $element-count)\"/>\n");
  append(L"    </xsl:otherwise>\n");
  append(L"  </xsl:choose>\n");
  append(L"</xsl:function>\n");
                                                            #line 1550 "PrintXSLT.cpp.template"
                                                                }
                                                              }
                                                              if (trace)
                                                              {
                                                            #line 2073 "PrintXSLT.cpp"
  append(L"\n");
  append(L"<!--");
  append(L"~");
  append(L"\n");
  append(L" ! Assemble a string showing current lookahead tokens, as far as they have\n");
  append(L" ! been tokenized.\n");
  append(L" !\n");
  append(L" ! @param $state lexer state, error indicator, and result stack.\n");
  append(L" ! @return a string containing the space-separated list of lookahead tokens.\n");
  append(L" -->\n");
  append(L"<xsl:function name=\"p:lookahead-string\" as=\"xs:string\">\n");
  append(L"  <xsl:param name=\"state\" as=\"item()+\"/>\n");
  append(L"\n");
  append(L"  <xsl:sequence select=\"\n");
  append(L"    string-join\n");
  append(L"    (\n");
  append(L"      (\n");
  append(L"        if ($state[$p:l1] le 0) then\n");
  append(L"          ()\n");
  append(L"        else\n");
  append(L"        (\n");
  append(L"          $p:TOKEN[$state[$p:l1] + 1]");
                                                            #line 1573 "PrintXSLT.cpp.template"
                                                                for (size_t i = 2; i <= grammar->k; ++i)
                                                                {
                                                                  increaseIndent();
                                                            #line 2100 "PrintXSLT.cpp"
  append(L",\n");
  append(L"        if ($state[$p:l");
                                                            #line 1577 "PrintXSLT.cpp.template"
                                                                  print(format.toString<wchar_t>(i));
                                                            #line 2105 "PrintXSLT.cpp"
  append(L"] le 0) then\n");
  append(L"          ()\n");
  append(L"        else\n");
  append(L"        (\n");
  append(L"          $p:TOKEN[$state[$p:l");
                                                            #line 1582 "PrintXSLT.cpp.template"
                                                                  print(format.toString<wchar_t>(i));
                                                            #line 2113 "PrintXSLT.cpp"
  append(L"] + 1]");
                                                            #line 1583 "PrintXSLT.cpp.template"
                                                                }
                                                                for (size_t i = 2; i <= grammar->k; ++i)
                                                                {
                                                            #line 2119 "PrintXSLT.cpp"
  append(L"\n");
  append(L"        )");
                                                            #line 1587 "PrintXSLT.cpp.template"
                                                                  decreaseIndent();
                                                                }
                                                            #line 2125 "PrintXSLT.cpp"
  append(L"\n");
  append(L"        )\n");
  append(L"      ),\n");
  append(L"      ' '\n");
  append(L"    )\n");
  append(L"  \"/>\n");
  append(L"</xsl:function>\n");
                                                            #line 1596 "PrintXSLT.cpp.template"
                                                              }
                                                            #line 2135 "PrintXSLT.cpp"
  append(L"\n");
  append(L"<!--");
  append(L"~");
  append(L"\n");
  append(L" ! Create a textual error message from a parsing error.\n");
  append(L" !\n");
  append(L" ! @param $input the input string.\n");
  append(L" ! @param $error the parsing error descriptor.\n");
  append(L" ! @return the error message.\n");
  append(L"-->\n");
  append(L"<xsl:function name=\"p:error-message\" as=\"xs:string\">\n");
  append(L"  <xsl:param name=\"input\" as=\"xs:string\"/>\n");
  append(L"  <xsl:param name=\"error\" as=\"element(error)\"/>\n");
  append(L"\n");
  append(L"  <xsl:variable name=\"begin\" select=\"xs:integer($error/@b)\"/>\n");
  append(L"  <xsl:variable name=\"context\" select=\"string-to-codepoints(substring($input, 1, $begin - 1))\"/>\n");
  append(L"  <xsl:variable name=\"linefeeds\" select=\"index-of($context, 10)\"/>\n");
  append(L"  <xsl:variable name=\"line\" select=\"count($linefeeds) + 1\"/>\n");
  append(L"  <xsl:variable name=\"column\" select=\"($begin - $linefeeds[last()], $begin)[1]\"/>\n");
  append(L"  <xsl:variable name=\"expected\" select=\"if ($error/@x or $error/@ambiguous-input) then () else p:expected-token-set($error/@s)\"/>\n");
  append(L"  <xsl:sequence select=\"\n");
  append(L"    string-join\n");
  append(L"    (\n");
  append(L"      (\n");
  append(L"        ");
                                                            #line 1619 "PrintXSLT.cpp.template"
                                                              if (grammar->useGlr)
                                                              {
                                                            #line 2164 "PrintXSLT.cpp"
  append(L"if ($error/@ambiguous-input) then\n");
  append(L"          'ambiguous input'\n");
  append(L"        else ");
                                                            #line 1623 "PrintXSLT.cpp.template"
                                                              }
                                                            #line 2170 "PrintXSLT.cpp"
  append(L"if ($error/@o) then\n");
  append(L"          ('syntax error, found ', $p:TOKEN[$error/@o + 1])\n");
  append(L"        else\n");
  append(L"          'lexical analysis failed',\n");
  append(L"        '&#10;',");
                                                            #line 1628 "PrintXSLT.cpp.template"
                                                              if (grammar->useGlr)
                                                              {
                                                            #line 2179 "PrintXSLT.cpp"
  append(L"\n");
  append(L"        if ($error/@ambiguous-input) then\n");
  append(L"          ()\n");
  append(L"        else\n");
  append(L"        (");
                                                            #line 1634 "PrintXSLT.cpp.template"
                                                                increaseIndent();
                                                              }
                                                            #line 2188 "PrintXSLT.cpp"
  append(L"\n");
  append(L"        'while expecting ',\n");
  append(L"        if ($error/@x) then\n");
  append(L"          $p:TOKEN[$error/@x + 1]\n");
  append(L"        else\n");
  append(L"        (\n");
  append(L"          '['[exists($expected[2])],\n");
  append(L"          string-join($expected, ', '),\n");
  append(L"          ']'[exists($expected[2])]\n");
  append(L"        ),\n");
  append(L"        '&#10;',\n");
  append(L"        if ($error/@o or $error/@e = $begin) then\n");
  append(L"          ()\n");
  append(L"        else\n");
  append(L"          ('after successfully scanning ', string($error/@e - $begin), ' characters beginning ')");
                                                            #line 1651 "PrintXSLT.cpp.template"
                                                              if (grammar->useGlr)
                                                              {
                                                                decreaseIndent();
                                                            #line 2208 "PrintXSLT.cpp"
  append(L"\n");
  append(L"        )");
                                                            #line 1655 "PrintXSLT.cpp.template"
                                                              }
                                                            #line 2213 "PrintXSLT.cpp"
  append(L",\n");
  append(L"        'at line ', string($line), ', column ', string($column), ':&#10;',\n");
  append(L"        '...', substring($input, $begin, 64), '...'\n");
  append(L"      ),\n");
  append(L"      ''\n");
  append(L"    )\n");
  append(L"  \"/>\n");
  append(L"</xsl:function>\n");
                                                            #line 1665 "PrintXSLT.cpp.template"
                                                              for (int i = 0; i < consumeMethods; ++i)
                                                              {
                                                                const wchar_t *name[2] = {L"consume", L"consumeT"};
                                                            #line 2226 "PrintXSLT.cpp"
  append(L"\n");
  append(L"<!--");
  append(L"~");
  append(L"\n");
  append(L" ! Consume one token, i.e. compare lookahead token 1 with expected\n");
  append(L" ! token and in case of a match, shift lookahead tokens down such that\n");
  append(L" ! l1 becomes the current token, and higher lookahead tokens move down.\n");
  append(L" ! When lookahead token 1 does not match the expected token, raise an\n");
  append(L" ! error by saving the expected token code in the error field of the\n");
  append(L" ! lexer state.");
                                                            #line 1675 "PrintXSLT.cpp.template"
                                                                if (i)
                                                                {
                                                            #line 2240 "PrintXSLT.cpp"
  append(L" In contrast to p:consume, do not create any output.");
                                                            #line 1678 "PrintXSLT.cpp.template"
                                                                }
                                                            #line 2244 "PrintXSLT.cpp"
  append(L"\n");
  append(L" !\n");
  append(L" ! @param $code the expected token.\n");
  append(L" ! @param $input the input string.\n");
  append(L" ! @param $state lexer state, error indicator, and result.\n");
  append(L" ! @return the updated state.\n");
  append(L"-->\n");
  append(L"<xsl:function name=\"p:");
                                                            #line 1686 "PrintXSLT.cpp.template"
                                                                print(name[i]);
                                                            #line 2255 "PrintXSLT.cpp"
  append(L"\" as=\"item()+\">\n");
  append(L"  <xsl:param name=\"code\" as=\"xs:integer\"/>\n");
  append(L"  <xsl:param name=\"input\" as=\"xs:string\"/>\n");
  append(L"  <xsl:param name=\"state\" as=\"item()+\"/>\n");
  append(L"\n");
  append(L"  <xsl:choose>\n");
  append(L"    <xsl:when test=\"$state[$p:error]\">\n");
  append(L"      <xsl:sequence select=\"$state\"/>\n");
  append(L"    </xsl:when>\n");
  append(L"    <xsl:when test=\"$state[$p:l1] eq $code\">");
                                                            #line 1696 "PrintXSLT.cpp.template"
                                                                if (trace && ! isLrParser)
                                                                {
                                                            #line 2269 "PrintXSLT.cpp"
  append(L"\n");
  append(L"      <xsl:variable name=\"state\" as=\"item()+\">");
                                                            #line 1699 "PrintXSLT.cpp.template"
                                                                  increaseIndent();
                                                                }
                                                                if (tree && i == 0)
                                                                {
                                                            #line 2277 "PrintXSLT.cpp"
  append(L"\n");
  append(L"      <xsl:variable name=\"begin\" select=\"$state[$p:e0]\"/>\n");
  append(L"      <xsl:variable name=\"end\" select=\"$state[$p:b1]\"/>\n");
  append(L"      <xsl:variable name=\"whitespace\">\n");
  append(L"        <xsl:if test=\"$begin ne $end\">\n");
  append(L"          <xsl:value-of select=\"substring($input, $begin, $end - $begin)\"/>\n");
  append(L"        </xsl:if>\n");
  append(L"      </xsl:variable>\n");
  append(L"      <xsl:variable name=\"token\" select=\"$p:TOKEN[1 + $state[$p:l1]]\"/>\n");
  append(L"      <xsl:variable name=\"name\" select=\"if (starts-with($token, &quot;'&quot;)) then 'TOKEN' else $token\"/>\n");
  append(L"      <xsl:variable name=\"begin\" select=\"$state[$p:b1]\"/>\n");
  append(L"      <xsl:variable name=\"end\" select=\"$state[$p:e1]\"/>\n");
  append(L"      <xsl:variable name=\"node\">\n");
  append(L"        <xsl:element name=\"{$name}\">\n");
  append(L"          <xsl:sequence select=\"substring($input, $begin, $end - $begin)\"/>\n");
  append(L"        </xsl:element>\n");
  append(L"      </xsl:variable>");
                                                            #line 1719 "PrintXSLT.cpp.template"
                                                                }
                                                            #line 2297 "PrintXSLT.cpp"
  append(L"\n");
  append(L"      <xsl:sequence select=\"\n");
  append(L"        subsequence($state, $p:l1, ");
                                                            #line 1722 "PrintXSLT.cpp.template"
                                                                print(format.toString<wchar_t>(grammar->k * 3));
                                                            #line 2303 "PrintXSLT.cpp"
  append(L"),\n");
  append(L"        0, 0, 0,\n");
  append(L"        subsequence($state, ");
                                                            #line 1725 "PrintXSLT.cpp.template"
                                                                print(format.toString<wchar_t>((grammar->k + 1) * 3 + 1));
                                                            #line 2309 "PrintXSLT.cpp"
  append(L")");
                                                            #line 1726 "PrintXSLT.cpp.template"
                                                                if (tree && i == 0)
                                                                {
                                                            #line 2314 "PrintXSLT.cpp"
  append(L",\n");
  append(L"        $whitespace/node(),\n");
  append(L"        $node/node()");
                                                            #line 1730 "PrintXSLT.cpp.template"
                                                                }
                                                            #line 2320 "PrintXSLT.cpp"
  append(L"\n");
  append(L"      \"/>");
                                                            #line 1732 "PrintXSLT.cpp.template"
                                                                if (trace && ! isLrParser)
                                                                {
                                                                  decreaseIndent();
                                                            #line 2327 "PrintXSLT.cpp"
  append(L"\n");
  append(L"      </xsl:variable>\n");
  append(L"      <xsl:sequence select=\"\n");
  append(L"        p:trace\n");
  append(L"        (\n");
  append(L"          string-join\n");
  append(L"          (\n");
  append(L"            (\n");
  append(L"              '  &lt;");
                                                            #line 1743 "PrintXSLT.cpp.template"
                                                                  print(i == 0 ? methodPrefixParse : methodPrefixTry);
                                                            #line 2339 "PrintXSLT.cpp"
  append(L" terminal=&quot;', p:xml-escape($p:TOKEN[$code + 1]), '&quot;',\n");
  append(L"              if ($state[$p:l1] le 0) then () else (' input=&quot;', p:xml-escape(p:lookahead-string($state)), '&quot;'),\n");
  append(L"              '/>'\n");
  append(L"            ),\n");
  append(L"            ''\n");
  append(L"          )\n");
  append(L"        ),\n");
  append(L"        $state\n");
  append(L"      \"/>");
                                                            #line 1752 "PrintXSLT.cpp.template"
                                                                }
                                                            #line 2351 "PrintXSLT.cpp"
  append(L"\n");
  append(L"    </xsl:when>\n");
  append(L"    <xsl:otherwise>\n");
  append(L"      <xsl:variable name=\"error\">\n");
  append(L"        <xsl:element name=\"error\">");
                                                            #line 1757 "PrintXSLT.cpp.template"
                                                                if (memoization)
                                                                {
                                                            #line 2360 "PrintXSLT.cpp"
  append(L"\n");
  append(L"          <xsl:choose>\n");
  append(L"            <xsl:when test=\"$state[$p:e1] &lt; $state[$p:memo]/@e\">\n");
  append(L"              <xsl:sequence select=\"$state[$p:memo]/@*\"/>\n");
  append(L"            </xsl:when>\n");
  append(L"            <xsl:otherwise>");
                                                            #line 1764 "PrintXSLT.cpp.template"
                                                                  increaseIndent();
                                                                }
                                                            #line 2370 "PrintXSLT.cpp"
  append(L"\n");
  append(L"          <xsl:attribute name=\"b\" select=\"$state[$p:b1]\"/>\n");
  append(L"          <xsl:attribute name=\"e\" select=\"$state[$p:e1]\"/>\n");
  append(L"          <xsl:choose>\n");
  append(L"            <xsl:when test=\"$state[$p:l1] lt 0\">\n");
  append(L"              <xsl:attribute name=\"s\" select=\"- $state[$p:l1]\"/>\n");
  append(L"            </xsl:when>\n");
  append(L"            <xsl:otherwise>\n");
  append(L"              <xsl:attribute name=\"o\" select=\"$state[$p:l1]\"/>\n");
  append(L"              <xsl:attribute name=\"x\" select=\"$code\"/>\n");
  append(L"            </xsl:otherwise>\n");
  append(L"          </xsl:choose>");
                                                            #line 1777 "PrintXSLT.cpp.template"
                                                                if (memoization)
                                                                {
                                                                  decreaseIndent();
                                                            #line 2387 "PrintXSLT.cpp"
  append(L"\n");
  append(L"            </xsl:otherwise>\n");
  append(L"          </xsl:choose>");
                                                            #line 1782 "PrintXSLT.cpp.template"
                                                                }
                                                            #line 2393 "PrintXSLT.cpp"
  append(L"\n");
  append(L"        </xsl:element>\n");
  append(L"      </xsl:variable>\n");
  append(L"      <xsl:sequence select=\"\n");
  append(L"        subsequence($state, 1, $p:error - 1),\n");
  append(L"        $error/node(),\n");
  append(L"        subsequence($state, $p:error + 1)\n");
  append(L"      \"/>\n");
  append(L"    </xsl:otherwise>\n");
  append(L"  </xsl:choose>\n");
  append(L"</xsl:function>\n");
                                                            #line 1794 "PrintXSLT.cpp.template"
                                                              }
                                                              if (anyWhitespace)
                                                              {
                                                                if (whitespaceCalled)
                                                                {
                                                            #line 2411 "PrintXSLT.cpp"
  append(L"\n");
  append(L"<!--");
  append(L"~");
  append(L"\n");
  append(L" ! Consume whitespace.\n");
  append(L" !\n");
  append(L" ! @param $input the input string.\n");
  append(L" ! @param $state lexer state, error indicator, and result.\n");
  append(L" ! @return the updated state.\n");
  append(L"-->\n");
  append(L"<xsl:function name=\"p:whitespace\" as=\"item()+\">\n");
  append(L"  <xsl:param name=\"input\" as=\"xs:string\"/>\n");
  append(L"  <xsl:param name=\"state\" as=\"item()+\"/>\n");
  append(L"\n");
  append(L"  <xsl:variable name=\"begin\" select=\"$state[$p:e0]\"/>\n");
  append(L"  <xsl:variable name=\"end\" select=\"$state[$p:b1]\"/>\n");
  append(L"  <xsl:choose>\n");
  append(L"    <xsl:when test=\"$begin eq $end\">\n");
  append(L"      <xsl:sequence select=\"$state\"/>\n");
  append(L"    </xsl:when>\n");
  append(L"    <xsl:otherwise>\n");
  append(L"      <xsl:variable name=\"whitespace\">\n");
  append(L"        <xsl:value-of select=\"substring($input, $begin, $end - $begin)\"/>\n");
  append(L"      </xsl:variable>\n");
  append(L"      <xsl:sequence select=\"\n");
  append(L"        0,\n");
  append(L"        $state[$p:b0],\n");
  append(L"        $end,\n");
  append(L"        subsequence($state, $p:e0 + 1),\n");
  append(L"        $whitespace/node()\n");
  append(L"      \"/>\n");
  append(L"    </xsl:otherwise>\n");
  append(L"  </xsl:choose>\n");
  append(L"</xsl:function>\n");
                                                            #line 1831 "PrintXSLT.cpp.template"
                                                                }
                                                            #line 2448 "PrintXSLT.cpp"
  append(L"\n");
  append(L"<!--");
  append(L"~");
  append(L"\n");
  append(L" ! Use p:match to fetch the next token, but skip any leading\n");
  append(L" ! whitespace.\n");
  append(L" !\n");
  append(L" ! @param $input the input string.\n");
  append(L" ! @param $begin the index where to start.\n");
  append(L" ! @param $token-set the valid token set id.");
                                                            #line 1839 "PrintXSLT.cpp.template"
                                                                if (grammar->useGlr)
                                                                {
                                                            #line 2462 "PrintXSLT.cpp"
  append(L"\n");
  append(L" ! @param $id the parsing thread id.");
                                                            #line 1842 "PrintXSLT.cpp.template"
                                                                }
                                                            #line 2467 "PrintXSLT.cpp"
  append(L"\n");
  append(L" ! @return a sequence of three values: the token code of the result\n");
  append(L" ! token, with input string positions of token begin and end.\n");
  append(L"-->\n");
  append(L"<xsl:function name=\"p:matchW\">\n");
  append(L"  <xsl:param name=\"input\" as=\"xs:string\"/>\n");
  append(L"  <xsl:param name=\"begin\" as=\"xs:integer\"/>\n");
  append(L"  <xsl:param name=\"token-set\" as=\"xs:integer\"/>");
                                                            #line 1850 "PrintXSLT.cpp.template"
                                                                if (grammar->useGlr)
                                                                {
                                                            #line 2479 "PrintXSLT.cpp"
  append(L"\n");
  append(L"  <xsl:param name=\"id\" as=\"xs:integer\"/>");
                                                            #line 1853 "PrintXSLT.cpp.template"
                                                                }
                                                            #line 2484 "PrintXSLT.cpp"
  append(L"\n");
  append(L"\n");
  append(L"  <xsl:variable name=\"match\" select=\"p:match($input, $begin, $token-set");
                                                            #line 1857 "PrintXSLT.cpp.template"
                                                                if (grammar->useGlr)
                                                                {
                                                            #line 2491 "PrintXSLT.cpp"
  append(L", $id");
                                                            #line 1859 "PrintXSLT.cpp.template"
                                                                }
                                                            #line 2495 "PrintXSLT.cpp"
  append(L")\"/>\n");
  append(L"  <xsl:choose>");
                                                            #line 1861 "PrintXSLT.cpp.template"
                                                                increaseIndent(2);
                                                                if (simpleWhitespace)
                                                                {
                                                                  printMatch(0, 0, 0, grammar->simpleWhitespaceIntroducers, IF, 0, L"<xsl:when test=\"", L"\">");
                                                            #line 2503 "PrintXSLT.cpp"
  append(L"\n");
  append(L"  <xsl:sequence select=\"p:matchW($input, $match[3], $token-set");
                                                            #line 1866 "PrintXSLT.cpp.template"
                                                                  if (grammar->useGlr)
                                                                  {
                                                            #line 2509 "PrintXSLT.cpp"
  append(L", $id");
                                                            #line 1868 "PrintXSLT.cpp.template"
                                                                  }
                                                            #line 2513 "PrintXSLT.cpp"
  append(L")\"/>\n");
  append(L"</xsl:when>");
                                                            #line 1870 "PrintXSLT.cpp.template"
                                                                }
                                                                if (complexWhitespace)
                                                                {
                                                                  printMatch(0, 0, 0, grammar->complexWhitespaceIntroducers, IF, 0, L"<xsl:when test=\"", L"\">");
                                                                  if (memoization)
                                                                  {
                                                            #line 2523 "PrintXSLT.cpp"
  append(L"\n");
  append(L"  <xsl:variable name=\"memo\">\n");
  append(L"    <xsl:element name=\"memo\"/>\n");
  append(L"  </xsl:variable>");
                                                            #line 1879 "PrintXSLT.cpp.template"
                                                                  }
                                                                  if (isLrParser)
                                                                  {
                                                            #line 2532 "PrintXSLT.cpp"
  append(L"\n");
  append(L"  <xsl:variable name=\"state\" select=\"0, $begin, $begin, $match, 0, 0");
                                                            #line 1884 "PrintXSLT.cpp.template"
                                                                    for (size_t k = 2; k <= grammar->k; ++k)
                                                                    {
                                                            #line 2538 "PrintXSLT.cpp"
  append(L", 0, 0, 0");
                                                            #line 1886 "PrintXSLT.cpp.template"
                                                                    }
                                                            #line 2542 "PrintXSLT.cpp"
  append(L", false()");
                                                            #line 1887 "PrintXSLT.cpp.template"
                                                                    if (memoization)
                                                                    {
                                                            #line 2547 "PrintXSLT.cpp"
  append(L", $memo/node()");
                                                            #line 1889 "PrintXSLT.cpp.template"
                                                                    }
                                                            #line 2551 "PrintXSLT.cpp"
  append(L"\"/>\n");
  append(L"  <xsl:variable name=\"state\" select=\"p:predict($input, $state, ");
                                                            #line 1891 "PrintXSLT.cpp.template"
                                                                    print(format.toString<wchar_t>((*grammar->states)[grammar->whitespace->state]->getStateId()));
                                                                    if (grammar->useGlr)
                                                                    {
                                                            #line 2558 "PrintXSLT.cpp"
  append(L", $id");
                                                            #line 1894 "PrintXSLT.cpp.template"
                                                                    }
                                                            #line 2562 "PrintXSLT.cpp"
  append(L")\"/>\n");
  append(L"  <xsl:variable name=\"e0\" select=\"$state[$p:e0]\"/>\n");
  append(L"  <xsl:variable name=\"state\" select=\"p:parse");
                                                            #line 1897 "PrintXSLT.cpp.template"
                                                                    if (grammar->useGlr)
                                                                    {
                                                            #line 2569 "PrintXSLT.cpp"
  append(L"-glr");
                                                            #line 1899 "PrintXSLT.cpp.template"
                                                                    }
                                                            #line 2573 "PrintXSLT.cpp"
  append(L"($input, -1");
                                                            #line 1900 "PrintXSLT.cpp.template"
                                                                    if (grammar->useGlr)
                                                                    {
                                                            #line 2578 "PrintXSLT.cpp"
  append(L", 0, p:thread(0, false()");
                                                            #line 1902 "PrintXSLT.cpp.template"
                                                                    }
                                                            #line 2582 "PrintXSLT.cpp"
  append(L", ");
                                                            #line 1903 "PrintXSLT.cpp.template"
                                                                    print(format.toString<wchar_t>((*grammar->states)[grammar->whitespace->state]->getStateId()));
                                                            #line 2586 "PrintXSLT.cpp"
  append(L", $state[$p:lk], -1, $e0, $e0, $e0, (1, -1, 0), $state");
                                                            #line 1905 "PrintXSLT.cpp.template"
                                                                    if (grammar->useGlr)
                                                                    {
                                                            #line 2591 "PrintXSLT.cpp"
  append(L")");
                                                            #line 1907 "PrintXSLT.cpp.template"
                                                                    }
                                                            #line 2595 "PrintXSLT.cpp"
  append(L")\"/>");
                                                            #line 1909 "PrintXSLT.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 2601 "PrintXSLT.cpp"
  append(L"\n");
  append(L"  <xsl:variable name=\"state\" select=\"p:try-");
                                                            #line 1913 "PrintXSLT.cpp.template"
                                                                    print(grammar->whitespace->name);
                                                            #line 2606 "PrintXSLT.cpp"
  append(L"($input, (0, $begin, $begin, $match");
                                                            #line 1915 "PrintXSLT.cpp.template"
                                                                    for (size_t k = 2; k <= grammar->k; ++k)
                                                                    {
                                                            #line 2611 "PrintXSLT.cpp"
  append(L", 0, 0, 0");
                                                            #line 1917 "PrintXSLT.cpp.template"
                                                                    }
                                                            #line 2615 "PrintXSLT.cpp"
  append(L", false()");
                                                            #line 1918 "PrintXSLT.cpp.template"
                                                                    if (memoization)
                                                                    {
                                                            #line 2620 "PrintXSLT.cpp"
  append(L", $memo/node()");
                                                            #line 1920 "PrintXSLT.cpp.template"
                                                                    }
                                                            #line 2624 "PrintXSLT.cpp"
  append(L"))\"/>");
                                                            #line 1922 "PrintXSLT.cpp.template"
                                                                  }
                                                            #line 2628 "PrintXSLT.cpp"
  append(L"\n");
  append(L"  <xsl:sequence select=\"p:matchW($input, $state[$p:e0], $token-set");
                                                            #line 1925 "PrintXSLT.cpp.template"
                                                                  if (grammar->useGlr)
                                                                  {
                                                            #line 2634 "PrintXSLT.cpp"
  append(L", $id");
                                                            #line 1927 "PrintXSLT.cpp.template"
                                                                  }
                                                            #line 2638 "PrintXSLT.cpp"
  append(L")\"/>\n");
  append(L"</xsl:when>");
                                                            #line 1929 "PrintXSLT.cpp.template"
                                                                }
                                                            #line 2643 "PrintXSLT.cpp"
  append(L"\n");
  append(L"<xsl:otherwise>\n");
  append(L"  <xsl:sequence select=\"$match\"/>");
                                                            #line 1932 "PrintXSLT.cpp.template"
                                                                decreaseIndent(2);
                                                            #line 2649 "PrintXSLT.cpp"
  append(L"\n");
  append(L"    </xsl:otherwise>\n");
  append(L"  </xsl:choose>\n");
  append(L"</xsl:function>\n");
                                                            #line 1937 "PrintXSLT.cpp.template"
                                                                size_t lwc = grammar->tables && grammar->k >= grammar->tables && anyWhitespace
                                                                           ? grammar->k
                                                                           : grammar->lookaheadSets.lookaheadWCount;
                                                                printLookaheadMethods(lwc, true);
                                                              }
                                                              size_t lc = grammar->tables && grammar->k >= grammar->tables && ! anyWhitespace
                                                                        ? grammar->k
                                                                        : grammar->lookaheadSets.lookaheadCount;
                                                              printLookaheadMethods(lc, false);
                                                              if (tree && ! isLrParser)
                                                              {
                                                            #line 2666 "PrintXSLT.cpp"
  append(L"\n");
  append(L"<!--");
  append(L"~");
  append(L"\n");
  append(L" ! Reduce the result stack, creating a nonterminal element. Pop\n");
  append(L" ! $count elements off the stack, wrap them in a new element\n");
  append(L" ! named $name, and push the new element.\n");
  append(L" !\n");
  append(L" ! @param $state lexer state, error indicator, and result.\n");
  append(L" ! @param $name the name of the result node.\n");
  append(L" ! @param $count the number of child nodes.");
                                                            #line 1956 "PrintXSLT.cpp.template"
                                                                if (! noPosition)
                                                                {
                                                            #line 2681 "PrintXSLT.cpp"
  append(L"\n");
  append(L" ! @param $begin the input index where the nonterminal begins.\n");
  append(L" ! @param $end the input index where the nonterminal ends.");
                                                            #line 1960 "PrintXSLT.cpp.template"
                                                                }
                                                            #line 2687 "PrintXSLT.cpp"
  append(L"\n");
  append(L" ! @return the updated state.\n");
  append(L"-->\n");
  append(L"<xsl:function name=\"p:reduce\" as=\"item()+\">\n");
  append(L"  <xsl:param name=\"state\" as=\"item()+\"/>\n");
  append(L"  <xsl:param name=\"name\" as=\"xs:string\"/>\n");
  append(L"  <xsl:param name=\"count\" as=\"xs:integer\"/>\n");
  append(L"  <xsl:param name=\"begin\" as=\"xs:integer\"/>\n");
  append(L"  <xsl:param name=\"end\" as=\"xs:integer\"/>\n");
  append(L"\n");
  append(L"  <xsl:variable name=\"node\">\n");
  append(L"    <xsl:element name=\"{$name}\">\n");
  append(L"      <xsl:sequence select=\"subsequence($state, $count + 1)\"/>\n");
  append(L"    </xsl:element>\n");
  append(L"  </xsl:variable>\n");
  append(L"  <xsl:sequence select=\"subsequence($state, 1, $count), $node/node()\"/>\n");
  append(L"</xsl:function>\n");
                                                            #line 1978 "PrintXSLT.cpp.template"
                                                              }
                                                              if (memoization)
                                                              {
                                                                const wchar_t *factor = format.toString<wchar_t>(Math::powerof(2, Math::bits(grammar->conflictCount)));
                                                            #line 2710 "PrintXSLT.cpp"
  append(L"\n");
  append(L"<!--");
  append(L"~");
  append(L"\n");
  append(L" ! Strip result from lexer state, in order to avoid carrying it while\n");
  append(L" ! backtracking.\n");
  append(L" !\n");
  append(L" ! @param $state the lexer state after an alternative failed.\n");
  append(L" ! @return the updated state.\n");
  append(L"-->\n");
  append(L"<xsl:function name=\"p:strip-result\" as=\"item()+\">\n");
  append(L"  <xsl:param name=\"state\" as=\"item()+\"/>\n");
  append(L"\n");
  append(L"  <xsl:sequence select=\"subsequence($state, 1, $p:memo)\"/>\n");
  append(L"</xsl:function>\n");
                                                            #line 1995 "PrintXSLT.cpp.template"
                                                                if (restoreCalled)
                                                                {
                                                            #line 2729 "PrintXSLT.cpp"
  append(L"\n");
  append(L"<!--");
  append(L"~");
  append(L"\n");
  append(L" ! Restore lexer state after unsuccessfully trying an alternative,\n");
  append(L" ! merging any memoization that was collected on the way.\n");
  append(L" !\n");
  append(L" ! @param $backtrack the lexer state before backtracking started.\n");
  append(L" ! @param $state the lexer state after an alternative failed.\n");
  append(L" ! @return the updated state.\n");
  append(L"-->\n");
  append(L"<xsl:function name=\"p:restore\" as=\"item()+\">\n");
  append(L"  <xsl:param name=\"backtrack\" as=\"item()+\"/>\n");
  append(L"  <xsl:param name=\"state\" as=\"item()+\"/>\n");
  append(L"\n");
  append(L"  <xsl:variable name=\"memo\">\n");
  append(L"    <xsl:element name=\"memo\">\n");
  append(L"      <xsl:variable name=\"errors\" select=\"($state[$p:memo], $state[$p:error])[.]\"/>\n");
  append(L"      <xsl:sequence select=\"$errors[@e = max($errors/xs:integer(@e))][last()]/@*, $state[$p:memo]/value\"/>\n");
  append(L"    </xsl:element>\n");
  append(L"  </xsl:variable>\n");
  append(L"  <xsl:sequence select=\"subsequence($backtrack, 1, $p:memo - 1), $memo/node()\"/>\n");
  append(L"</xsl:function>\n");
                                                            #line 2018 "PrintXSLT.cpp.template"
                                                                }
                                                            #line 2755 "PrintXSLT.cpp"
  append(L"\n");
  append(L"<!--");
  append(L"~");
  append(L"\n");
  append(L" ! Memoize the backtracking result that was computed at decision point\n");
  append(L" ! $dpi for input position $e0. Reconstruct state from the parameters.\n");
  append(L" !\n");
  append(L" ! @param $state the lexer state to be restored.\n");
  append(L" ! @param $update the lexer state containing updates.\n");
  append(L" ! @param $dpi the decision point id.\n");
  append(L" ! @param $e0 the input position.\n");
  append(L" ! @param $v the id of the successful alternative.\n");
  append(L" ! @param $lk the new lookahead code.\n");
  append(L" ! @return the reconstructed state.\n");
  append(L"-->\n");
  append(L"<xsl:function name=\"p:memoize\" as=\"item()+\">\n");
  append(L"  <xsl:param name=\"state\" as=\"item()+\"/>\n");
  append(L"  <xsl:param name=\"update\" as=\"item()+\"/>\n");
  append(L"  <xsl:param name=\"dpi\" as=\"xs:integer\"/>\n");
  append(L"  <xsl:param name=\"e0\" as=\"xs:integer\"/>\n");
  append(L"  <xsl:param name=\"v\" as=\"xs:integer\"/>\n");
  append(L"  <xsl:param name=\"lk\" as=\"xs:integer\"/>\n");
  append(L"\n");
  append(L"  <xsl:variable name=\"memo\" select=\"$update[$p:memo]\"/>\n");
  append(L"  <xsl:variable name=\"errors\" select=\"($memo, $update[$p:error])[.]\"/>\n");
  append(L"  <xsl:variable name=\"memo\">\n");
  append(L"    <xsl:element name=\"memo\">\n");
  append(L"      <xsl:sequence select=\"$errors[@e = max($errors/xs:integer(@e))][last()]/@*, $memo/value\"/>\n");
  append(L"      <xsl:element name=\"value\">\n");
  append(L"        <xsl:attribute name=\"key\" select=\"$e0 * ");
                                                            #line 2046 "PrintXSLT.cpp.template"
                                                                print(factor);
                                                            #line 2788 "PrintXSLT.cpp"
  append(L" + $dpi\"/>\n");
  append(L"        <xsl:sequence select=\"$v\"/>\n");
  append(L"      </xsl:element>\n");
  append(L"    </xsl:element>\n");
  append(L"  </xsl:variable>\n");
  append(L"  <xsl:sequence select=\"\n");
  append(L"    $lk,\n");
  append(L"    subsequence($state, $p:b0, $p:memo - $p:b0),\n");
  append(L"    $memo/node(),\n");
  append(L"    subsequence($state, $p:memo + 1)\n");
  append(L"  \"/>\n");
  append(L"</xsl:function>\n");
  append(L"\n");
  append(L"<!--");
  append(L"~");
  append(L"\n");
  append(L" ! Retrieve memoized backtracking result for decision point $dpi\n");
  append(L" ! and input position $state[$p:e0] into $state[$p:lk].\n");
  append(L" !\n");
  append(L" ! @param $state lexer state, error indicator, and result.\n");
  append(L" ! @param $dpi the decision point id.\n");
  append(L" ! @return the updated state.\n");
  append(L"-->\n");
  append(L"<xsl:function name=\"p:memoized\" as=\"item()+\">\n");
  append(L"  <xsl:param name=\"state\" as=\"item()+\"/>\n");
  append(L"  <xsl:param name=\"dpi\" as=\"xs:integer\"/>\n");
  append(L"\n");
  append(L"  <xsl:variable name=\"value\" select=\"data($state[$p:memo]/value[@key = $state[$p:e0] * ");
                                                            #line 2073 "PrintXSLT.cpp.template"
                                                                print(factor);
                                                            #line 2819 "PrintXSLT.cpp"
  append(L" + $dpi])\"/>\n");
  append(L"  <xsl:sequence select=\"\n");
  append(L"    if ($value) then $value else 0,\n");
  append(L"    subsequence($state, $p:lk + 1)\n");
  append(L"  \"/>\n");
  append(L"</xsl:function>\n");
                                                            #line 2080 "PrintXSLT.cpp.template"
                                                              }
                                                            }

                                                            void PrintXSLT::printLookaheadMethods(size_t lookaheadMethods, bool withWhitespace)
                                                            {
                                                              for (size_t k = 1; k <= lookaheadMethods; ++k)
                                                              {
                                                            #line 2834 "PrintXSLT.cpp"
  append(L"\n");
  append(L"<!--");
  append(L"~");
  append(L"\n");
  append(L" ! Lookahead one token on level ");
                                                            #line 2089 "PrintXSLT.cpp.template"
                                                                print(format.toString<wchar_t>(k));
                                                                if (withWhitespace)
                                                                {
                                                            #line 2844 "PrintXSLT.cpp"
  append(L" with whitespace skipping");
                                                            #line 2092 "PrintXSLT.cpp.template"
                                                                }
                                                            #line 2848 "PrintXSLT.cpp"
  append(L".\n");
  append(L" !");
                                                            #line 2094 "PrintXSLT.cpp.template"
                                                                if (k != 1 && unlimitedLookahead)
                                                                {
                                                            #line 2854 "PrintXSLT.cpp"
  append(L"\n");
  append(L" ! @param $prefix the prefix code representing lower level lookahead.");
                                                            #line 2098 "PrintXSLT.cpp.template"
                                                                }
                                                            #line 2859 "PrintXSLT.cpp"
  append(L"\n");
  append(L" ! @param $set the code of the DFA entry state for the set of valid tokens.\n");
  append(L" ! @param $input the input string.\n");
  append(L" ! @param $state lexer state, error indicator, and result stack.");
                                                            #line 2103 "PrintXSLT.cpp.template"
                                                                if (grammar->useGlr)
                                                                {
                                                            #line 2867 "PrintXSLT.cpp"
  append(L"\n");
  append(L" ! @param $id the parsing thread id.");
                                                            #line 2106 "PrintXSLT.cpp.template"
                                                                }
                                                            #line 2872 "PrintXSLT.cpp"
  append(L"\n");
  append(L" ! @return the updated state.\n");
  append(L"-->\n");
  append(L"<xsl:function name=\"p:lookahead");
                                                            #line 2110 "PrintXSLT.cpp.template"
                                                                print(format.toString<wchar_t>(k));
                                                                if (withWhitespace)
                                                                {
                                                            #line 2881 "PrintXSLT.cpp"
  append(L"W");
                                                            #line 2114 "PrintXSLT.cpp.template"
                                                                }
                                                            #line 2885 "PrintXSLT.cpp"
  append(L"\" as=\"item()+\">");
                                                            #line 2115 "PrintXSLT.cpp.template"
                                                                if (k != 1 && unlimitedLookahead)
                                                                {
                                                            #line 2890 "PrintXSLT.cpp"
  append(L"\n");
  append(L"  <xsl:param name=\"prefix\" as=\"xs:integer\"/>");
                                                            #line 2118 "PrintXSLT.cpp.template"
                                                                }
                                                            #line 2895 "PrintXSLT.cpp"
  append(L"\n");
  append(L"  <xsl:param name=\"set\" as=\"xs:integer\"/>\n");
  append(L"  <xsl:param name=\"input\" as=\"xs:string\"/>\n");
  append(L"  <xsl:param name=\"state\" as=\"item()+\"/>");
                                                            #line 2122 "PrintXSLT.cpp.template"
                                                                if (grammar->useGlr)
                                                                {
                                                            #line 2903 "PrintXSLT.cpp"
  append(L"\n");
  append(L"  <xsl:param name=\"id\" as=\"xs:integer\"/>");
                                                            #line 2125 "PrintXSLT.cpp.template"
                                                                }
                                                            #line 2908 "PrintXSLT.cpp"
  append(L"\n");
                                                            #line 2127 "PrintXSLT.cpp.template"
                                                                if (k == 1)
                                                                {
                                                            #line 2913 "PrintXSLT.cpp"
  append(L"\n");
  append(L"  <xsl:choose>\n");
  append(L"    <xsl:when test=\"$state[$p:l1] ne 0\">\n");
  append(L"      <xsl:sequence select=\"$state\"/>\n");
  append(L"    </xsl:when>\n");
  append(L"    <xsl:otherwise>\n");
  append(L"      <xsl:variable name=\"match\" select=\"");
                                                            #line 2135 "PrintXSLT.cpp.template"
                                                                  increaseIndent();
                                                                }
                                                                else
                                                                {
                                                            #line 2926 "PrintXSLT.cpp"
  append(L"\n");
  append(L"  <xsl:variable name=\"match\" select=\"\n");
  append(L"    if ($state[$p:l");
                                                            #line 2141 "PrintXSLT.cpp.template"
                                                                  print(format.toString<wchar_t>(k));
                                                            #line 2932 "PrintXSLT.cpp"
  append(L"] ne 0) then\n");
  append(L"      subsequence($state, $p:l");
                                                            #line 2143 "PrintXSLT.cpp.template"
                                                                  print(format.toString<wchar_t>(k));
                                                            #line 2937 "PrintXSLT.cpp"
  append(L", ");
                                                            #line 2144 "PrintXSLT.cpp.template"
                                                                  print(format.toString<wchar_t>(k < grammar->k ? 6 : 3));
                                                            #line 2941 "PrintXSLT.cpp"
  append(L")\n");
  append(L"    else");
                                                            #line 2146 "PrintXSLT.cpp.template"
                                                                }
                                                                if (k > 1 && k < grammar->k)
                                                                {
                                                            #line 2948 "PrintXSLT.cpp"
  append(L"\n");
  append(L"    (");
                                                            #line 2150 "PrintXSLT.cpp.template"
                                                                }
                                                            #line 2953 "PrintXSLT.cpp"
  append(L"\n");
  append(L"      p:match");
                                                            #line 2152 "PrintXSLT.cpp.template"
                                                                if (withWhitespace)
                                                                {
                                                            #line 2959 "PrintXSLT.cpp"
  append(L"W");
                                                            #line 2155 "PrintXSLT.cpp.template"
                                                                }
                                                            #line 2963 "PrintXSLT.cpp"
  append(L"($input, $state[$p:e");
                                                            #line 2156 "PrintXSLT.cpp.template"
                                                                print(format.toString<wchar_t>(k - 1));
                                                            #line 2967 "PrintXSLT.cpp"
  append(L"], $set");
                                                            #line 2157 "PrintXSLT.cpp.template"
                                                                if (grammar->useGlr)
                                                                {
                                                            #line 2972 "PrintXSLT.cpp"
  append(L", $id");
                                                            #line 2159 "PrintXSLT.cpp.template"
                                                                }
                                                            #line 2976 "PrintXSLT.cpp"
  append(L")");
                                                            #line 2160 "PrintXSLT.cpp.template"
                                                                if (k < grammar->k)
                                                                {
                                                            #line 2981 "PrintXSLT.cpp"
  append(L",\n");
  append(L"      0, 0, 0");
                                                            #line 2163 "PrintXSLT.cpp.template"
                                                                  if (k > 1)
                                                                  {
                                                            #line 2987 "PrintXSLT.cpp"
  append(L"\n");
  append(L"    )");
                                                            #line 2166 "PrintXSLT.cpp.template"
                                                                  }
                                                                }
                                                                if (k == 1)
                                                                {
                                                                  increaseIndent();
                                                                }
                                                            #line 2997 "PrintXSLT.cpp"
  append(L"\n");
  append(L"  \"/>\n");
  append(L"  <xsl:sequence select=\"\n");
  append(L"    ");
                                                            #line 2175 "PrintXSLT.cpp.template"
                                                                if (grammar->tables && k >= grammar->tables)
                                                                {
                                                            #line 3005 "PrintXSLT.cpp"
  append(L"subsequence($state, 1, ");
                                                            #line 2178 "PrintXSLT.cpp.template"
                                                                  print(format.toString<wchar_t>(k * 3));
                                                            #line 3009 "PrintXSLT.cpp"
  append(L"),");
                                                            #line 2179 "PrintXSLT.cpp.template"
                                                                }
                                                                else
                                                                {
                                                                  if (k != 1 && unlimitedLookahead)
                                                                  {
                                                            #line 3017 "PrintXSLT.cpp"
  append(L"$match[1] + $prefix");
                                                            #line 2184 "PrintXSLT.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 3023 "PrintXSLT.cpp"
  append(L"$match[1]");
                                                            #line 2187 "PrintXSLT.cpp.template"
                                                                    switch (k)
                                                                    {
                                                                    case 1: break;
                                                                    case 2:
                                                            #line 3030 "PrintXSLT.cpp"
  append(L" * ");
                                                            #line 2191 "PrintXSLT.cpp.template"
                                                                      print(format.toString<wchar_t>(Math::powerof(2, ((int) k - 1) * grammar->tokenSequenceFactory->tokenBits())));
                                                            #line 3034 "PrintXSLT.cpp"
  append(L" + $state[$p:l1]");
                                                            #line 2192 "PrintXSLT.cpp.template"
                                                                      break;
                                                                    default:
                                                            #line 3039 "PrintXSLT.cpp"
  append(L" * ");
                                                            #line 2194 "PrintXSLT.cpp.template"
                                                                      print(format.toString<wchar_t>(Math::powerof(2, ((int) k - 1) * grammar->tokenSequenceFactory->tokenBits())));
                                                            #line 3043 "PrintXSLT.cpp"
  append(L" + $state[$p:lk]");
                                                            #line 2195 "PrintXSLT.cpp.template"
                                                                      break;
                                                                    }
                                                                  }
                                                            #line 3049 "PrintXSLT.cpp"
  append(L",\n");
  append(L"    subsequence($state, $p:b0, ");
                                                            #line 2199 "PrintXSLT.cpp.template"
                                                                  print(format.toString<wchar_t>(k * 3 - 1));
                                                            #line 3054 "PrintXSLT.cpp"
  append(L"),");
                                                            #line 2200 "PrintXSLT.cpp.template"
                                                                }
                                                            #line 3058 "PrintXSLT.cpp"
  append(L"\n");
  append(L"    $match,\n");
  append(L"    subsequence($state, ");
                                                            #line 2203 "PrintXSLT.cpp.template"
                                                                  print(format.toString<wchar_t>(k * 3 + (grammar->k > k ? 7 : 4)));
                                                            #line 3064 "PrintXSLT.cpp"
  append(L")\n");
  append(L"  \"/>");
                                                            #line 2205 "PrintXSLT.cpp.template"
                                                                if (k == 1)
                                                                {
                                                                  decreaseIndent(2);
                                                            #line 3071 "PrintXSLT.cpp"
  append(L"\n");
  append(L"    </xsl:otherwise>\n");
  append(L"  </xsl:choose>");
                                                            #line 2210 "PrintXSLT.cpp.template"
                                                                }
                                                            #line 3077 "PrintXSLT.cpp"
  append(L"\n");
  append(L"</xsl:function>\n");
                                                            #line 2214 "PrintXSLT.cpp.template"
                                                              }
                                                            }

                                                            void PrintXSLT::printEpilog(Grammar *node)
                                                            {
                                                              setIndent(1);
                                                              if (node->automaticSemicolonInsertion)
                                                              {
                                                            #line 3089 "PrintXSLT.cpp"
  append(L"\n");
  append(L"<!--");
  append(L"~");
  append(L"\n");
  append(L" ! Check whether the lookahead token is preceded by a line terminator.\n");
  append(L" !\n");
  append(L" ! @param $input the input string.\n");
  append(L" ! @param $state lexer state, error indicator, and result.\n");
  append(L" ! @return the updated state.\n");
  append(L"-->\n");
  append(L"<xsl:function name=\"p:follows-line-terminator\" as=\"item()+\">\n");
  append(L"  <xsl:param name=\"input\" as=\"xs:string\"/>\n");
  append(L"  <xsl:param name=\"state\" as=\"item()+\"/>\n");
  append(L"\n");
  append(L"  <xsl:variable name=\"begin\" select=\"if ($state[$p:e0] eq $state[$p:b1]) then $state[$p:b0] else $state[$p:e0]\"/>\n");
  append(L"  <xsl:variable name=\"preceding-whitespace\" select=\"substring($input, $begin, $state[$p:b1] - $begin)\"/>\n");
  append(L"  <xsl:sequence select=\"string-to-codepoints($preceding-whitespace) = (10, 13, 8232, 8233)\"/>\n");
  append(L"</xsl:function>\n");
                                                            #line 2238 "PrintXSLT.cpp.template"
                                                              }
                                                              for (Node *n = node->nonTerminals; n; n = n->followingSibling)
                                                              {
                                                                Production *p = static_cast <Production *> (n);
                                                                if (p->isStartSymbol())
                                                                {
                                                            #line 3115 "PrintXSLT.cpp"
  append(L"\n");
  append(L"<!--");
  append(L"~");
  append(L"\n");
  append(L" ! Parse start symbol ");
                                                            #line 2246 "PrintXSLT.cpp.template"
                                                                  print(p->name);
                                                            #line 3123 "PrintXSLT.cpp"
  append(L" from given string.\n");
  append(L" !\n");
  append(L" ! @param $s the string to be parsed.\n");
  append(L" ! @return the result as generated by parser actions.\n");
  append(L"-->\n");
  append(L"<xsl:function name=\"p:");
                                                            #line 2252 "PrintXSLT.cpp.template"
                                                                  print(methodPrefix);
                                                            #line 3132 "PrintXSLT.cpp"
  append(L"-");
                                                            #line 2253 "PrintXSLT.cpp.template"
                                                                  print(p->name);
                                                            #line 3136 "PrintXSLT.cpp"
  append(L"\" as=\"item()*\">\n");
  append(L"  <xsl:param name=\"s\" as=\"xs:string\"/>\n");
                                                            #line 2256 "PrintXSLT.cpp.template"
                                                                  if (memoization)
                                                                  {
                                                            #line 3142 "PrintXSLT.cpp"
  append(L"\n");
  append(L"  <xsl:variable name=\"memo\">\n");
  append(L"    <xsl:element name=\"memo\"/>\n");
  append(L"  </xsl:variable>");
                                                            #line 2261 "PrintXSLT.cpp.template"
                                                                  }
                                                            #line 3149 "PrintXSLT.cpp"
  append(L"\n");
  append(L"  <xsl:variable name=\"state\" select=\"0, 1, 1");
                                                            #line 2263 "PrintXSLT.cpp.template"
                                                                  for (size_t k = 1; k <= grammar->k; ++k)
                                                                  {
                                                            #line 3155 "PrintXSLT.cpp"
  append(L", 0, 0, 0");
                                                            #line 2265 "PrintXSLT.cpp.template"
                                                                  }
                                                            #line 3159 "PrintXSLT.cpp"
  append(L", false()");
                                                            #line 2266 "PrintXSLT.cpp.template"
                                                                  if (memoization)
                                                                  {
                                                            #line 3164 "PrintXSLT.cpp"
  append(L", $memo/node()");
                                                            #line 2268 "PrintXSLT.cpp.template"
                                                                  }
                                                            #line 3168 "PrintXSLT.cpp"
  append(L"\"/>");
                                                            #line 2269 "PrintXSLT.cpp.template"
                                                                  if (isLrParser)
                                                                  {
                                                            #line 3173 "PrintXSLT.cpp"
  append(L"\n");
  append(L"  <xsl:variable name=\"state\" select=\"p:predict($s, $state, ");
                                                            #line 2272 "PrintXSLT.cpp.template"
                                                                    print(format.toString<wchar_t>((*grammar->states)[p->state]->getStateId()));
                                                                    if (grammar->useGlr)
                                                                    {
                                                            #line 3180 "PrintXSLT.cpp"
  append(L", 0");
                                                            #line 2275 "PrintXSLT.cpp.template"
                                                                    }
                                                            #line 3184 "PrintXSLT.cpp"
  append(L")\"/>\n");
  append(L"  <xsl:variable name=\"state\" select=\"p:parse");
                                                            #line 2277 "PrintXSLT.cpp.template"
                                                                    if (grammar->useGlr)
                                                                    {
                                                            #line 3190 "PrintXSLT.cpp"
  append(L"-glr");
                                                            #line 2279 "PrintXSLT.cpp.template"
                                                                    }
                                                            #line 3194 "PrintXSLT.cpp"
  append(L"($s, ");
                                                            #line 2280 "PrintXSLT.cpp.template"
                                                                    print(format.toString<wchar_t>(p->nonterminalCode));
                                                                    if (grammar->useGlr)
                                                                    {
                                                            #line 3200 "PrintXSLT.cpp"
  append(L", 0, p:thread(0, false()");
                                                            #line 2283 "PrintXSLT.cpp.template"
                                                                    }
                                                            #line 3204 "PrintXSLT.cpp"
  append(L", ");
                                                            #line 2284 "PrintXSLT.cpp.template"
                                                                    print(format.toString<wchar_t>((*grammar->states)[p->state]->getStateId()));
                                                            #line 3208 "PrintXSLT.cpp"
  append(L", $state[$p:lk], -1, 1, 1, 1, (1, -1, 0), $state");
                                                            #line 2286 "PrintXSLT.cpp.template"
                                                                    if (grammar->useGlr)
                                                                    {
                                                            #line 3213 "PrintXSLT.cpp"
  append(L")");
                                                            #line 2288 "PrintXSLT.cpp.template"
                                                                    }
                                                            #line 3217 "PrintXSLT.cpp"
  append(L")\"/>");
                                                            #line 2290 "PrintXSLT.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 3223 "PrintXSLT.cpp"
  append(L"\n");
  append(L"  <xsl:variable name=\"state\" select=\"p:");
                                                            #line 2294 "PrintXSLT.cpp.template"
                                                                    print(methodPrefix);
                                                            #line 3228 "PrintXSLT.cpp"
  append(L"-");
                                                            #line 2295 "PrintXSLT.cpp.template"
                                                                    print(p->name);
                                                            #line 3232 "PrintXSLT.cpp"
  append(L"($s, $state)\"/>");
                                                            #line 2296 "PrintXSLT.cpp.template"
                                                                  }
                                                            #line 3236 "PrintXSLT.cpp"
  append(L"\n");
  append(L"  <xsl:variable name=\"error\" select=\"$state[$p:error]\"/>\n");
  append(L"  <xsl:choose>\n");
  append(L"    <xsl:when test=\"$error\">\n");
  append(L"      <xsl:variable name=\"ERROR\">\n");
  append(L"        <xsl:element name=\"ERROR\">\n");
  append(L"          <xsl:sequence select=\"$error/@*, p:error-message($s, $error)\"/>\n");
  append(L"        </xsl:element>\n");
  append(L"      </xsl:variable>\n");
  append(L"      <xsl:sequence select=\"");
                                                            #line 2306 "PrintXSLT.cpp.template"
                                                                  if (tree && grammar->useGlr)
                                                                  {
                                                            #line 3250 "PrintXSLT.cpp"
  append(L"$error/AMBIGUOUS, ");
                                                            #line 2308 "PrintXSLT.cpp.template"
                                                                  }
                                                            #line 3254 "PrintXSLT.cpp"
  append(L"$ERROR/node()\"/>\n");
  append(L"    </xsl:when>\n");
  append(L"    <xsl:otherwise>\n");
  append(L"      <xsl:sequence select=\"subsequence($state, $p:result)\"/>\n");
  append(L"    </xsl:otherwise>\n");
  append(L"  </xsl:choose>\n");
  append(L"</xsl:function>\n");
                                                            #line 2316 "PrintXSLT.cpp.template"
                                                                }
                                                              }
                                                              if (trace && ! isLrParser)
                                                              {
                                                            #line 3267 "PrintXSLT.cpp"
  append(L"\n");
  append(L"<!--");
  append(L"~");
  append(L"\n");
  append(L" ! Trace LL processing of a nonterminal.\n");
  append(L" !\n");
  append(L" ! @param $state lexer state, error indicator, and result stack.\n");
  append(L" ! @param $method processing method type.\n");
  append(L" ! @param $occasion the current step.\n");
  append(L" ! @param $name the nonterminal name.\n");
  append(L" ! @return the empty sequence.\n");
  append(L"-->\n");
  append(L"<xsl:function name=\"p:trace-nonterminal\" as=\"xs:string?\">\n");
  append(L"  <xsl:param name=\"state\" as=\"item()+\"/>\n");
  append(L"  <xsl:param name=\"method\" as=\"xs:string\"/>\n");
  append(L"  <xsl:param name=\"occasion\" as=\"xs:string\"/>\n");
  append(L"  <xsl:param name=\"name\" as=\"xs:string\"/>\n");
  append(L"\n");
  append(L"  <xsl:sequence select=\"\n");
  append(L"    p:trace\n");
  append(L"    (\n");
  append(L"      string-join\n");
  append(L"      (\n");
  append(L"        (\n");
  append(L"          '  &lt;',\n");
  append(L"          $method,\n");
  append(L"          ' ',\n");
  append(L"          $occasion,\n");
  append(L"          'nonterminal=&quot;',\n");
  append(L"          $name,\n");
  append(L"          '&quot;',\n");
  append(L"          if ($state[$p:l1] le 0) then () else (' input=&quot;', p:xml-escape(p:lookahead-string($state)), '&quot;'),\n");
  append(L"          '/>'\n");
  append(L"        ),\n");
  append(L"        ''\n");
  append(L"      )\n");
  append(L"    )\n");
  append(L"  \"/>\n");
  append(L"</xsl:function>\n");
                                                            #line 2357 "PrintXSLT.cpp.template"
                                                              }
                                                              if (main)
                                                              {
                                                            #line 3311 "PrintXSLT.cpp"
  append(L"\n");
  append(L"<!--");
  append(L"~");
  append(L"\n");
  append(L" ! The input filename, or string, if surrounded by curly braces.\n");
  append(L"-->\n");
  append(L"<xsl:param name=\"input\" as=\"xs:string?\" select=\"()\"/>\n");
  append(L"\n");
  append(L"<!--");
  append(L"~");
  append(L"\n");
  append(L" ! The (simple) main program.\n");
  append(L"-->\n");
  append(L"<xsl:template name=\"main\" match=\"/\">\n");
  append(L"  <xsl:param name=\"input\" as=\"xs:string?\" select=\"$input\"/>\n");
  append(L"\n");
  append(L"  <xsl:choose>\n");
  append(L"    <xsl:when test=\"empty($input)\">\n");
  append(L"      <xsl:sequence select=\"error(xs:QName('main'), '&#xA;    Usage: java net.sf.saxon.Transform -xsl:");
                                                            #line 2375 "PrintXSLT.cpp.template"
                                                                print(wFileName);
                                                            #line 3333 "PrintXSLT.cpp"
  append(L" -it:main input=INPUT&#xA;&#xA;      parse INPUT, which is either a filename or literal text enclosed in curly braces')\"/>\n");
  append(L"    </xsl:when>\n");
  append(L"    <xsl:otherwise>\n");
  append(L"      <xsl:variable name=\"result\" select=\"");
                                                            #line 2380 "PrintXSLT.cpp.template"
                                                                if (trace)
                                                                {
                                                            #line 3341 "PrintXSLT.cpp"
  append(L"\n");
  append(L"        p:trace('&lt;trace&gt;'),");
                                                            #line 2383 "PrintXSLT.cpp.template"
                                                                }
                                                            #line 3346 "PrintXSLT.cpp"
  append(L"\n");
  append(L"        if (matches($input, '");
  append(L"^");
  append(L"\\{.*\\}$')) then\n");
  append(L"          p:");
                                                            #line 2386 "PrintXSLT.cpp.template"
                                                                print(methodPrefix);
                                                            #line 3354 "PrintXSLT.cpp"
  append(L"-");
                                                            #line 2387 "PrintXSLT.cpp.template"
                                                                print(grammar->startSymbol()->name);
                                                            #line 3358 "PrintXSLT.cpp"
  append(L"(substring($input, 2, string-length($input) - 2))\n");
  append(L"        else\n");
  append(L"          p:");
                                                            #line 2390 "PrintXSLT.cpp.template"
                                                                print(methodPrefix);
                                                            #line 3364 "PrintXSLT.cpp"
  append(L"-");
                                                            #line 2391 "PrintXSLT.cpp.template"
                                                                print(grammar->startSymbol()->name);
                                                            #line 3368 "PrintXSLT.cpp"
  append(L"(unparsed-text($input, 'utf-8'))");
                                                            #line 2392 "PrintXSLT.cpp.template"
                                                                if (trace)
                                                                {
                                                            #line 3373 "PrintXSLT.cpp"
  append(L",\n");
  append(L"        p:trace('&lt;/trace&gt;')");
                                                            #line 2395 "PrintXSLT.cpp.template"
                                                                }
                                                            #line 3378 "PrintXSLT.cpp"
  append(L"\n");
  append(L"      \"/>\n");
  append(L"      <xsl:choose>\n");
  append(L"        <xsl:when test=\"empty($result/self::ERROR)\">\n");
  append(L"          <xsl:sequence select=\"$result\"/>\n");
  append(L"        </xsl:when>\n");
  append(L"        <xsl:otherwise>");
                                                            #line 2402 "PrintXSLT.cpp.template"
                                                                if (tree && grammar->useGlr)
                                                                {
                                                            #line 3389 "PrintXSLT.cpp"
  append(L"\n");
  append(L"          <xsl:result-document>\n");
  append(L"            <xsl:sequence select=\"$result[not(self::ERROR)], '&#10;'\"/>\n");
  append(L"          </xsl:result-document>");
                                                            #line 2407 "PrintXSLT.cpp.template"
                                                                }
                                                            #line 3396 "PrintXSLT.cpp"
  append(L"\n");
  append(L"          <xsl:sequence select=\"error(xs:QName('p:");
                                                            #line 2409 "PrintXSLT.cpp.template"
                                                                print(methodPrefix);
                                                            #line 3401 "PrintXSLT.cpp"
  append(L"-");
                                                            #line 2410 "PrintXSLT.cpp.template"
                                                                print(grammar->startSymbol()->name);
                                                            #line 3405 "PrintXSLT.cpp"
  append(L"'), concat('&#10;    ', replace($result");
                                                            #line 2412 "PrintXSLT.cpp.template"
                                                                if (tree && grammar->useGlr)
                                                                {
                                                            #line 3410 "PrintXSLT.cpp"
  append(L"[self::ERROR]");
                                                            #line 2415 "PrintXSLT.cpp.template"
                                                                }
                                                            #line 3414 "PrintXSLT.cpp"
  append(L", '&#10;', '&#10;    ')))\"/>\n");
  append(L"        </xsl:otherwise>\n");
  append(L"      </xsl:choose>\n");
  append(L"    </xsl:otherwise>\n");
  append(L"  </xsl:choose>\n");
  append(L"</xsl:template>\n");
                                                            #line 2422 "PrintXSLT.cpp.template"
                                                              }
                                                              setIndent(0);
                                                              if (! visitEpilog())
                                                              {
                                                            #line 3426 "PrintXSLT.cpp"
  append(L"\n");
  append(L"</xsl:stylesheet>");
                                                            #line 2427 "PrintXSLT.cpp.template"
                                                              }
                                                            }

                                                            void PrintXSLT::printVariables()
                                                            {
                                                              setIndent(1);
                                                            #line 3436 "PrintXSLT.cpp"
  append(L"\n");
  append(L"<!--");
  append(L"~");
  append(L"\n");
  append(L" ! The index of the lexer state for accessing the combined\n");
  append(L" ! (i.e. level > 1) lookahead code.\n");
  append(L"-->\n");
  append(L"<xsl:variable name=\"p:lk\" as=\"xs:integer\" select=\"1\"/>\n");
  append(L"\n");
  append(L"<!--");
  append(L"~");
  append(L"\n");
  append(L" ! The index of the lexer state for accessing the position in the\n");
  append(L" ! input string of the begin of the token that has been consumed.\n");
  append(L"-->\n");
  append(L"<xsl:variable name=\"p:b0\" as=\"xs:integer\" select=\"2\"/>\n");
  append(L"\n");
  append(L"<!--");
  append(L"~");
  append(L"\n");
  append(L" ! The index of the lexer state for accessing the position in the\n");
  append(L" ! input string of the end of the token that has been consumed.\n");
  append(L"-->\n");
  append(L"<xsl:variable name=\"p:e0\" as=\"xs:integer\" select=\"3\"/>");
                                                            #line 2450 "PrintXSLT.cpp.template"
                                                              int stateIndex = 3;
                                                              for (size_t k = 1; k <= grammar->k; ++k)
                                                              {
                                                            #line 3465 "PrintXSLT.cpp"
  append(L"\n");
  append(L"\n");
  append(L"<!--");
  append(L"~");
  append(L"\n");
  append(L" ! The index of the lexer state for accessing the code of the\n");
  append(L" ! level-");
                                                            #line 2457 "PrintXSLT.cpp.template"
                                                                print(format.toString<wchar_t>(k));
                                                            #line 3475 "PrintXSLT.cpp"
  append(L"-lookahead token.\n");
  append(L"-->\n");
  append(L"<xsl:variable name=\"p:l");
                                                            #line 2460 "PrintXSLT.cpp.template"
                                                                print(format.toString<wchar_t>(k));
                                                            #line 3481 "PrintXSLT.cpp"
  append(L"\" as=\"xs:integer\" select=\"");
                                                            #line 2461 "PrintXSLT.cpp.template"
                                                                print(format.toString<wchar_t>(++stateIndex));
                                                            #line 3485 "PrintXSLT.cpp"
  append(L"\"/>\n");
  append(L"\n");
  append(L"<!--");
  append(L"~");
  append(L"\n");
  append(L" ! The index of the lexer state for accessing the position in the\n");
  append(L" ! input string of the begin of the level-");
                                                            #line 2466 "PrintXSLT.cpp.template"
                                                                print(format.toString<wchar_t>(k));
                                                            #line 3495 "PrintXSLT.cpp"
  append(L"-lookahead token.\n");
  append(L"-->\n");
  append(L"<xsl:variable name=\"p:b");
                                                            #line 2469 "PrintXSLT.cpp.template"
                                                                print(format.toString<wchar_t>(k));
                                                            #line 3501 "PrintXSLT.cpp"
  append(L"\" as=\"xs:integer\" select=\"");
                                                            #line 2470 "PrintXSLT.cpp.template"
                                                                print(format.toString<wchar_t>(++stateIndex));
                                                            #line 3505 "PrintXSLT.cpp"
  append(L"\"/>\n");
  append(L"\n");
  append(L"<!--");
  append(L"~");
  append(L"\n");
  append(L" ! The index of the lexer state for accessing the position in the\n");
  append(L" ! input string of the end of the level-");
                                                            #line 2475 "PrintXSLT.cpp.template"
                                                                print(format.toString<wchar_t>(k));
                                                            #line 3515 "PrintXSLT.cpp"
  append(L"-lookahead token.\n");
  append(L"-->\n");
  append(L"<xsl:variable name=\"p:e");
                                                            #line 2478 "PrintXSLT.cpp.template"
                                                                print(format.toString<wchar_t>(k));
                                                            #line 3521 "PrintXSLT.cpp"
  append(L"\" as=\"xs:integer\" select=\"");
                                                            #line 2479 "PrintXSLT.cpp.template"
                                                                print(format.toString<wchar_t>(++stateIndex));
                                                            #line 3525 "PrintXSLT.cpp"
  append(L"\"/>");
                                                            #line 2480 "PrintXSLT.cpp.template"
                                                              }
                                                            #line 3529 "PrintXSLT.cpp"
  append(L"\n");
  append(L"\n");
  append(L"<!--");
  append(L"~");
  append(L"\n");
  append(L" ! The index of the lexer state for accessing the token code that\n");
  append(L" ! was expected when an error was found.\n");
  append(L"-->\n");
  append(L"<xsl:variable name=\"p:error\" as=\"xs:integer\" select=\"");
                                                            #line 2487 "PrintXSLT.cpp.template"
                                                              print(format.toString<wchar_t>(++stateIndex));
                                                            #line 3541 "PrintXSLT.cpp"
  append(L"\"/>\n");
                                                            #line 2489 "PrintXSLT.cpp.template"
                                                              if (memoization)
                                                              {
                                                            #line 3546 "PrintXSLT.cpp"
  append(L"\n");
  append(L"<!--");
  append(L"~");
  append(L"\n");
  append(L" ! The index of the lexer state for accessing the memoization\n");
  append(L" ! of backtracking results.\n");
  append(L"-->\n");
  append(L"<xsl:variable name=\"p:memo\" as=\"xs:integer\" select=\"");
                                                            #line 2496 "PrintXSLT.cpp.template"
                                                                print(format.toString<wchar_t>(++stateIndex));
                                                            #line 3557 "PrintXSLT.cpp"
  append(L"\"/>\n");
                                                            #line 2498 "PrintXSLT.cpp.template"
                                                              }
                                                            #line 3561 "PrintXSLT.cpp"
  append(L"\n");
  append(L"<!--");
  append(L"~");
  append(L"\n");
  append(L" ! The index of the lexer state that points to the first entry\n");
  append(L" ! used for collecting action results.\n");
  append(L"-->\n");
  append(L"<xsl:variable name=\"p:result\" as=\"xs:integer\" select=\"");
                                                            #line 2504 "PrintXSLT.cpp.template"
                                                              print(format.toString<wchar_t>(++stateIndex));
                                                            #line 3572 "PrintXSLT.cpp"
  append(L"\"/>");
                                                            #line 2505 "PrintXSLT.cpp.template"
                                                              setIndent(0);
                                                            }

                                                            void PrintXSLT::printProlog(Grammar *aNode)
                                                            {
                                                              if (! hasProlog)
                                                              {
                                                            #line 3582 "PrintXSLT.cpp"
  append(L"\n");
  append(L"<xsl:stylesheet version=\"");
                                                            #line 2513 "PrintXSLT.cpp.template"
                                                                if (grammar->useGlr)
                                                                {
                                                            #line 3588 "PrintXSLT.cpp"
  append(L"3.0");
                                                            #line 2515 "PrintXSLT.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 3594 "PrintXSLT.cpp"
  append(L"2.0");
                                                            #line 2518 "PrintXSLT.cpp.template"
                                                                }
                                                            #line 3598 "PrintXSLT.cpp"
  append(L"\"\n");
  append(L"                xmlns:xs=\"http://www.w3.org/2001/XMLSchema\"\n");
  append(L"                xmlns:xsl=\"http://www.w3.org/1999/XSL/Transform\"\n");
  append(L"                xmlns:p=\"");
                                                            #line 2522 "PrintXSLT.cpp.template"
                                                                print(className);
                                                            #line 3605 "PrintXSLT.cpp"
  append(L"\">");
                                                            #line 2523 "PrintXSLT.cpp.template"
                                                              }
                                                            }

                                                            void PrintXSLT::PrintLoops::visitZeroOrMore(ZeroOrMore *node)
                                                            {
                                                              px->setIndent(1);
                                                              if (node->loopId == 0)
                                                              {
                                                                node->loopId = ++loopId;
                                                                Visitor::visitZeroOrMore(node);
                                                              }
                                                              if (px->methodPrefix == px->methodPrefixTry || node->production->runPayload)
                                                              {
                                                            #line 3621 "PrintXSLT.cpp"
  append(L"\n");
  append(L"<!--");
  append(L"~");
  append(L"\n");
  append(L" ! ");
                                                            #line 2538 "PrintXSLT.cpp.template"
                                                              if (px->methodPrefix != px->methodPrefixTry)
                                                              {
                                                            #line 3630 "PrintXSLT.cpp"
  append(L"Parse");
                                                            #line 2540 "PrintXSLT.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 3636 "PrintXSLT.cpp"
  append(L"Try parsing");
                                                            #line 2543 "PrintXSLT.cpp.template"
                                                              }
                                                            #line 3640 "PrintXSLT.cpp"
  append(L" the ");
                                                            #line 2544 "PrintXSLT.cpp.template"
                                                              px->print(px->format.toString<wchar_t>(node->loopId));
                                                              switch (node->loopId)
                                                              {
                                                              case 1:  append(L"st"); break;
                                                              case 2:  append(L"nd"); break;
                                                              case 3:  append(L"rd"); break;
                                                              default: append(L"th"); break;
                                                              }
                                                            #line 3651 "PrintXSLT.cpp"
  append(L" loop of production ");
                                                            #line 2552 "PrintXSLT.cpp.template"
                                                              px->print(node->production->name);
                                                            #line 3655 "PrintXSLT.cpp"
  append(L" (zero or more). Use\n");
  append(L" ! tail recursion for iteratively updating the lexer state.\n");
  append(L" !\n");
  append(L" ! @param $input the input string.\n");
  append(L" ! @param $state lexer state, error indicator, and result.\n");
  append(L" ! @return the updated state.\n");
  append(L"-->\n");
  append(L"<xsl:function name=\"p:");
                                                            #line 2560 "PrintXSLT.cpp.template"
                                                              px->print(px->methodPrefix);
                                                            #line 3666 "PrintXSLT.cpp"
  append(L"-");
                                                            #line 2561 "PrintXSLT.cpp.template"
                                                              px->print(node->production->name);
                                                            #line 3670 "PrintXSLT.cpp"
  append(L"-");
                                                            #line 2562 "PrintXSLT.cpp.template"
                                                              px->print(px->format.toString<wchar_t>(node->loopId));
                                                            #line 3674 "PrintXSLT.cpp"
  append(L"\">\n");
  append(L"  <xsl:param name=\"input\" as=\"xs:string\"/>\n");
  append(L"  <xsl:param name=\"state\" as=\"item()+\"/>\n");
  append(L"\n");
  append(L"  <xsl:choose>\n");
  append(L"    <xsl:when test=\"$state[$p:error]\">\n");
  append(L"      <xsl:sequence select=\"$state\"/>\n");
  append(L"    </xsl:when>\n");
  append(L"    <xsl:otherwise>");
                                                            #line 2571 "PrintXSLT.cpp.template"
                                                              px->increaseIndent(3);
                                                              px->printLookahead(node->k, *px->grammar->epsilon, 1, node->getLookahead(), node->findsLookahead);
                                                              px->automaticSemicolonInsertion(node);
                                                              bool nestedTry = px->methodPrefix == px->methodPrefixTry;
                                                              bool hasBacktracking =
                                                                px->printBacktracking(node,
                                                                                      node->getLookahead(),
                                                                                      node->conflictCaseId,
                                                                                      node->conflictId,
                                                                                      node->firstElementChild);
                                                              MatchType matchType;
                                                              const TokenSequenceSet &match = node->firstElementChild->getMatch(matchType);
                                                            #line 3697 "PrintXSLT.cpp"
  append(L"\n");
  append(L"<xsl:choose>");
                                                            #line 2584 "PrintXSLT.cpp.template"
                                                              px->increaseIndent();
                                                              if (hasBacktracking && nestedTry)
                                                              {
                                                            #line 3704 "PrintXSLT.cpp"
  append(L"\n");
  append(L"<xsl:when test=\"$state[$p:lk] = -3\">\n");
  append(L"  <xsl:sequence select=\"p:");
                                                            #line 2589 "PrintXSLT.cpp.template"
                                                                px->print(px->methodPrefix);
                                                            #line 3710 "PrintXSLT.cpp"
  append(L"-");
                                                            #line 2590 "PrintXSLT.cpp.template"
                                                                px->print(node->production->name);
                                                            #line 3714 "PrintXSLT.cpp"
  append(L"-");
                                                            #line 2591 "PrintXSLT.cpp.template"
                                                                px->print(px->format.toString<wchar_t>(node->loopId));
                                                            #line 3718 "PrintXSLT.cpp"
  append(L"($input, $state)\"/>\n");
  append(L"</xsl:when>");
                                                            #line 2593 "PrintXSLT.cpp.template"
                                                              }
                                                              px->printMatch(node->getLookahead(),
                                                                             node->k,
                                                                             node->conflicts(node->k) == 0 ? 0 : matchType == IF ? 1 : 2,
                                                                             match,
                                                                             matchType == IF ? IFNOT : IF,
                                                                             1,
                                                                             L"<xsl:when test=\"",
                                                                             L"\">");
                                                            #line 3731 "PrintXSLT.cpp"
  append(L"\n");
  append(L"  <xsl:sequence select=\"$state\"/>\n");
  append(L"</xsl:when>\n");
  append(L"<xsl:otherwise>");
                                                            #line 2605 "PrintXSLT.cpp.template"
                                                              px->Visitor::visitNodeWithChildren(node);
                                                            #line 3738 "PrintXSLT.cpp"
  append(L"\n");
  append(L"  <xsl:sequence select=\"p:");
                                                            #line 2607 "PrintXSLT.cpp.template"
                                                              px->print(px->methodPrefix);
                                                            #line 3743 "PrintXSLT.cpp"
  append(L"-");
                                                            #line 2608 "PrintXSLT.cpp.template"
                                                              px->print(node->production->name);
                                                            #line 3747 "PrintXSLT.cpp"
  append(L"-");
                                                            #line 2609 "PrintXSLT.cpp.template"
                                                              px->print(px->format.toString<wchar_t>(node->loopId));
                                                            #line 3751 "PrintXSLT.cpp"
  append(L"($input, $state)\"/>");
                                                            #line 2610 "PrintXSLT.cpp.template"
                                                              px->decreaseIndent();
//                                                              if (hasLookahead || hasBacktracking)
//                                                              {
//                                                                px->decreaseIndent();
//                                                              }
                                                              px->decreaseIndent(3);
                                                            #line 3760 "PrintXSLT.cpp"
  append(L"\n");
  append(L"        </xsl:otherwise>\n");
  append(L"      </xsl:choose>\n");
  append(L"    </xsl:otherwise>\n");
  append(L"  </xsl:choose>\n");
  append(L"</xsl:function>\n");
                                                            #line 2623 "PrintXSLT.cpp.template"
                                                              }
                                                              px->setIndent(0);

                                                              if (px->methodPrefix != px->methodPrefixTry && node->runOffLoad)
                                                              {
                                                                px->methodPrefix = px->methodPrefixTry;
                                                                visitZeroOrMore(node);
                                                                px->methodPrefix = px->methodPrefixParse;
                                                              }
                                                            }

                                                            void PrintXSLT::PrintLoops::visitOneOrMore(OneOrMore *node)
                                                            {
                                                              px->setIndent(1);
                                                              if (node->loopId == 0)
                                                              {
                                                                node->loopId = ++loopId;
                                                                Visitor::visitOneOrMore(node);
                                                              }
                                                              if (px->methodPrefix == px->methodPrefixTry || node->production->runPayload)
                                                              {
                                                            #line 3789 "PrintXSLT.cpp"
  append(L"\n");
  append(L"<!--");
  append(L"~");
  append(L"\n");
  append(L" ! ");
                                                            #line 2646 "PrintXSLT.cpp.template"
                                                                if (px->methodPrefix != px->methodPrefixTry)
                                                                {
                                                            #line 3798 "PrintXSLT.cpp"
  append(L"Parse");
                                                            #line 2648 "PrintXSLT.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 3804 "PrintXSLT.cpp"
  append(L"Try parsing");
                                                            #line 2651 "PrintXSLT.cpp.template"
                                                                }
                                                            #line 3808 "PrintXSLT.cpp"
  append(L" the ");
                                                            #line 2652 "PrintXSLT.cpp.template"
                                                                px->print(px->format.toString<wchar_t>(node->loopId));
                                                                switch (node->loopId)
                                                                {
                                                                case 1:  append(L"st"); break;
                                                                case 2:  append(L"nd"); break;
                                                                case 3:  append(L"rd"); break;
                                                                default: append(L"th"); break;
                                                                }
                                                            #line 3819 "PrintXSLT.cpp"
  append(L" loop of production ");
                                                            #line 2660 "PrintXSLT.cpp.template"
                                                                px->print(node->production->name);
                                                            #line 3823 "PrintXSLT.cpp"
  append(L" (one or more). Use\n");
  append(L" ! tail recursion for iteratively updating the lexer state.\n");
  append(L" !\n");
  append(L" ! @param $input the input string.\n");
  append(L" ! @param $state lexer state, error indicator, and result.\n");
  append(L" ! @return the updated state.\n");
  append(L"-->\n");
  append(L"<xsl:function name=\"p:");
                                                            #line 2668 "PrintXSLT.cpp.template"
                                                                px->print(px->methodPrefix);
                                                            #line 3834 "PrintXSLT.cpp"
  append(L"-");
                                                            #line 2669 "PrintXSLT.cpp.template"
                                                                px->print(node->production->name);
                                                            #line 3838 "PrintXSLT.cpp"
  append(L"-");
                                                            #line 2670 "PrintXSLT.cpp.template"
                                                                px->print(px->format.toString<wchar_t>(node->loopId));
                                                            #line 3842 "PrintXSLT.cpp"
  append(L"\">\n");
  append(L"  <xsl:param name=\"input\" as=\"xs:string\"/>\n");
  append(L"  <xsl:param name=\"state\" as=\"item()+\"/>\n");
  append(L"\n");
  append(L"  <xsl:choose>\n");
  append(L"    <xsl:when test=\"$state[$p:error]\">\n");
  append(L"      <xsl:sequence select=\"$state\"/>\n");
  append(L"    </xsl:when>\n");
  append(L"    <xsl:otherwise>");
                                                            #line 2679 "PrintXSLT.cpp.template"
                                                                px->increaseIndent(2);
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
                                                            #line 3865 "PrintXSLT.cpp"
  append(L"\n");
  append(L"<xsl:choose>");
                                                            #line 2692 "PrintXSLT.cpp.template"
                                                                px->increaseIndent();
                                                                if (hasBacktracking && nestedTry)
                                                                {
                                                            #line 3872 "PrintXSLT.cpp"
  append(L"\n");
  append(L"<xsl:when test=\"$state[$p:lk] = -3\">\n");
  append(L"  <xsl:sequence select=\"p:");
                                                            #line 2697 "PrintXSLT.cpp.template"
                                                                  px->print(px->methodPrefix);
                                                            #line 3878 "PrintXSLT.cpp"
  append(L"-");
                                                            #line 2698 "PrintXSLT.cpp.template"
                                                                  px->print(node->production->name);
                                                            #line 3882 "PrintXSLT.cpp"
  append(L"-");
                                                            #line 2699 "PrintXSLT.cpp.template"
                                                                  px->print(px->format.toString<wchar_t>(node->loopId));
                                                            #line 3886 "PrintXSLT.cpp"
  append(L"($input, $state)\"/>\n");
  append(L"</xsl:when>");
                                                            #line 2701 "PrintXSLT.cpp.template"
                                                                }
                                                                MatchType matchType;
                                                                const TokenSequenceSet &match = node->firstElementChild->getMatch(matchType);
                                                                px->printMatch(node->getLookahead(),
                                                                               node->k,
                                                                               node->conflicts(node->k) == 0 ? 0 : matchType == IF ? 1 : 2,
                                                                               match,
                                                                               matchType == IF ? IFNOT : IF,
                                                                               1,
                                                                               L"<xsl:when test=\"",
                                                                               L"\">");
                                                            #line 3901 "PrintXSLT.cpp"
  append(L"\n");
  append(L"  <xsl:sequence select=\"$state\"/>\n");
  append(L"</xsl:when>\n");
  append(L"<xsl:otherwise>\n");
  append(L"  <xsl:sequence select=\"p:");
                                                            #line 2716 "PrintXSLT.cpp.template"
                                                                px->print(px->methodPrefix);
                                                            #line 3909 "PrintXSLT.cpp"
  append(L"-");
                                                            #line 2717 "PrintXSLT.cpp.template"
                                                                px->print(node->production->name);
                                                            #line 3913 "PrintXSLT.cpp"
  append(L"-");
                                                            #line 2718 "PrintXSLT.cpp.template"
                                                                px->print(px->format.toString<wchar_t>(node->loopId));
                                                            #line 3917 "PrintXSLT.cpp"
  append(L"($input, $state)\"/>");
                                                            #line 2719 "PrintXSLT.cpp.template"
                                                                px->decreaseIndent(4);
                                                            #line 3921 "PrintXSLT.cpp"
  append(L"\n");
  append(L"        </xsl:otherwise>\n");
  append(L"      </xsl:choose>\n");
  append(L"    </xsl:otherwise>\n");
  append(L"  </xsl:choose>\n");
  append(L"</xsl:function>\n");
                                                            #line 2726 "PrintXSLT.cpp.template"
                                                              }
                                                              px->setIndent(0);
                                                              if (px->methodPrefix != px->methodPrefixTry && node->runOffLoad)
                                                              {
                                                                px->methodPrefix = px->methodPrefixTry;
                                                                visitOneOrMore(node);
                                                                px->methodPrefix = px->methodPrefixParse;
                                                              }
                                                            }

                                                            void PrintXSLT::automaticSemicolonInsertion(Node *node)
                                                            {
                                                              if (node->automaticSemicolonInsertion)
                                                              {
                                                                const bool afterRbrace = false;
                                                                Production *p;
                                                                p = grammar->stringByName.byStringValue(L";");
                                                                Token::Code semicolon = p == 0 ? -1 : p->tokenCode;
                                                                lineBuffer.clear();
                                                                TokenSequenceSet tss;
                                                            #line 3949 "PrintXSLT.cpp"
  append(L"\n");
  append(L"<xsl:variable name=\"state\" select=\"");
                                                            #line 2747 "PrintXSLT.cpp.template"
                                                                switch (node->automaticSemicolonInsertion)
                                                                {
                                                                case PLUSPLUS:
                                                                case MINUSMINUS:
                                                                  {
                                                                    p = grammar->stringByName.byStringValue(L"++");
                                                                    Token::Code plusplus = p == 0 ? -1 : p->tokenCode;
                                                                    p = grammar->stringByName.byStringValue(L"--");
                                                                    Token::Code minusminus = p == 0 ? -1 : p->tokenCode;
                                                            #line 3962 "PrintXSLT.cpp"
  append(L"\n");
  append(L"  if ($state[$p:l1] = (");
                                                            #line 2757 "PrintXSLT.cpp.template"
                                                                    print(format.toString<wchar_t>(grammar->externalTokenCode[plusplus]));
                                                            #line 3967 "PrintXSLT.cpp"
  append(L", ");
                                                            #line 2758 "PrintXSLT.cpp.template"
                                                                    print(format.toString<wchar_t>(grammar->externalTokenCode[minusminus]));
                                                            #line 3971 "PrintXSLT.cpp"
  append(L") and p:follows-line-terminator($input, $state)) then");
                                                            #line 2759 "PrintXSLT.cpp.template"
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
                                                            #line 3984 "PrintXSLT.cpp"
  append(L"\n");
  append(L"  if ($state[$p:l1] ne ");
                                                            #line 2770 "PrintXSLT.cpp.template"
                                                                    print(format.toString<wchar_t>(grammar->externalTokenCode[semicolon]));
                                                            #line 3989 "PrintXSLT.cpp"
  append(L" and $state[$p:l1] ge 0 and p:follows-line-terminator($input, $state)) then");
                                                            #line 2772 "PrintXSLT.cpp.template"
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
                                                            #line 4002 "PrintXSLT.cpp"
  append(L"\n");
  append(L"  if ($state[$p:l1] eq ");
                                                            #line 2783 "PrintXSLT.cpp.template"
                                                                    print(format.toString<wchar_t>(grammar->externalTokenCode[rbrace]));
                                                                    printCodeSequenceAnnotation(grammar->tokenSequence(rbrace));
                                                            #line 4008 "PrintXSLT.cpp"
  append(L"\n");
  append(L"   or $state[$p:l1] eq ");
                                                            #line 2786 "PrintXSLT.cpp.template"
                                                                    print(format.toString<wchar_t>(grammar->externalTokenCode[eof]));
                                                                    printCodeSequenceAnnotation(grammar->tokenSequence(eof));
                                                            #line 4014 "PrintXSLT.cpp"
  append(L"\n");
  append(L"   or $state[$p:l1] ne ");
                                                            #line 2789 "PrintXSLT.cpp.template"
                                                                    print(format.toString<wchar_t>(grammar->externalTokenCode[semicolon]));
                                                            #line 4019 "PrintXSLT.cpp"
  append(L" and $state[$p:l1] ge 0 and ");
                                                            #line 2790 "PrintXSLT.cpp.template"
                                                                    if (afterRbrace)
                                                                    {
                                                            #line 4024 "PrintXSLT.cpp"
  append(L"(");
                                                            #line 2792 "PrintXSLT.cpp.template"
                                                                    }
                                                            #line 4028 "PrintXSLT.cpp"
  append(L"p:follows-line-terminator($input, $state)");
                                                            #line 2794 "PrintXSLT.cpp.template"
                                                                    if (afterRbrace)
                                                                    {
                                                            #line 4033 "PrintXSLT.cpp"
  append(L" or substring($input, $state[$p:b0], 1) eq '}')");
                                                            #line 2797 "PrintXSLT.cpp.template"
                                                                    }
                                                            #line 4037 "PrintXSLT.cpp"
  append(L") then");
                                                            #line 2798 "PrintXSLT.cpp.template"
                                                                    printCodeSequenceAnnotation(grammar->tokenSequence(semicolon));
                                                                  }
                                                                  break;
                                                                default:
                                                                  {
                                                                    internalerr();
                                                                  }
                                                                }
                                                            #line 4048 "PrintXSLT.cpp"
  append(L"\n");
  append(L"  (\n");
  append(L"    subsequence($state, 1, $p:l1 - 1),\n");
  append(L"    ");
                                                            #line 2809 "PrintXSLT.cpp.template"
                                                                    print(format.toString<wchar_t>(grammar->externalTokenCode[semicolon]));
                                                            #line 4055 "PrintXSLT.cpp"
  append(L",");
                                                            #line 2810 "PrintXSLT.cpp.template"
                                                                    printCodeSequenceAnnotation(grammar->tokenSequence(semicolon));
                                                            #line 4059 "PrintXSLT.cpp"
  append(L"\n");
  append(L"    $state[$p:b1],\n");
  append(L"    $state[$p:b1],\n");
  append(L"    subsequence($state, $p:e1 + 1)\n");
  append(L"  )\n");
  append(L"  else\n");
  append(L"    $state\"/>");
                                                            #line 2817 "PrintXSLT.cpp.template"
                                                              }
                                                            }

// End
