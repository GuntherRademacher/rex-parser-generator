/*
 * PredictionBuilder.hpp
 *
 *  Created on: 05.11.2012
 *      Author: Gunther
 */

#ifndef PREDICTIONBUILDER_HPP_
#define PREDICTIONBUILDER_HPP_

#include "Grammar.hpp"

class MatchCodeVisitor : public Visitor
{                       typedef Visitor
                          super;
public:
  MatchCodeVisitor(Grammar *node) : grammar(node) {}
  virtual ~MatchCodeVisitor() {}

  virtual void processDecisionPoint(size_t k, const CompressedTokenSet &lookahead) = 0;
  virtual void processMatchCodes(int dpi, const TokenSequenceSet *match, int caseId) = 0;

  void visitOptional(Optional *node) {visitNonChoice(node, node->conflictCaseId);}
  void visitZeroOrMore(ZeroOrMore *node) {visitNonChoice(node, node->conflictCaseId);}
  void visitOneOrMore(OneOrMore *node) {visitNonChoice(node, node->conflictCaseId);}

  void visitChoice(Choice *node)
  {
    if (isDecisionPoint(node))
    {
      processDecisionPoint(node->k, *node->getLookahead());

      MatchType conflictMatchType;
      node->getConflictMatch(conflictMatchType);

      int caseId = 0;

      for (NodeList::iterator i = node->cases.begin(); i != node->cases.end(); ++i)
      {
        Node *c = (*i)->element();
        MatchType matchType;
        c->getMatch(matchType);

        switch (matchType)
        {
        case CASE:
          c->caseId = ++caseId;
          processMatchCodes(node->getLookahead()->getDpi(), c->match, c->caseId);
          break;
        case DEFAULT:
          c->caseId = 0;
          break;
        default:
          internalerr();
        }
      }

      if (conflictMatchType == IF)
      {
        node->conflictCaseId = ++caseId;
        processMatchCodes(node->getLookahead()->getDpi(), node->conflictMatch, node->conflictCaseId);
      }
    }
    super::visitChoice(node);
  }

private:
  void visitNonChoice(NodeWithChildren *node, int &conflictCaseId)
  {
    if (isDecisionPoint(node))
    {
      processDecisionPoint(node->k, *node->getLookahead());

      MatchType matchType;
      node->firstElementChild->getMatch(matchType);

      MatchType conflictMatchType;
      node->getConflictMatch(conflictMatchType);

      int caseId = 0;

      if (matchType == IF || conflictMatchType == IFNOT)
      {
        processMatchCodes(node->getLookahead()->getDpi(), node->firstElementChild->match, ++caseId);
      }

      if (matchType == IFNOT || conflictMatchType == IFNOT)
      {
        processMatchCodes(node->getLookahead()->getDpi(), node->firstElementChild->matchComplement, ++caseId);
      }

      if (conflictMatchType == IF)
      {
        conflictCaseId = ++caseId;
        processMatchCodes(node->getLookahead()->getDpi(), node->conflictMatch, conflictCaseId);
      }
    }
    visitNodeList(node->firstChild);
  }

  bool isDecisionPoint(Node *node)
  {
    return grammar->tables > 0
        && node->k >= grammar->tables
        && node->getLookahead() != 0
        && ! node->getLookahead()->empty();
  }

protected:
  Grammar *grammar;
};

class PredictionBuilder : private MatchCodeVisitor
{                         typedef MatchCodeVisitor
                                  super;
public:
  PredictionBuilder(Grammar *node) : super(node) {}
  virtual ~PredictionBuilder() {}

  void collectInput()
  {
    if (grammar->tables && grammar->k >= grammar->tables)
    {
      section = NONTERMINALS;
      visitNodeList(grammar->nonTerminals);
    }
  }

  void build();

private:
  virtual void processDecisionPoint(size_t k, const CompressedTokenSet &lookahead)
  {
    grammar->decisionPoints.insert(DecisionPoints::key_type(k, &lookahead, (int) grammar->decisionPoints.size()));
  }

  void processMatchCodes(int dpi, const TokenSequenceSet *match, int caseId)
  {
    grammar->matchCode.add(match, grammar->tokenSequenceFactory);
  }

  void setTokensetByDpiAndMatchcode(TiledMap2D *map,
                                    int dpi,
                                    const CompressedTokenSet &cts,
                                    const TokenSequence &prefix);
};

class PrepareCaseIdTable : public MatchCodeVisitor
{                         typedef MatchCodeVisitor
                                  super;
public:
  PrepareCaseIdTable(TiledMap2D *m) : super(0), map(m) {}
  virtual ~PrepareCaseIdTable() {};

  void visitGrammar(Grammar *node)
  {
    grammar = node;
    section = NONTERMINALS;
    visitNodeList(node->nonTerminals);
  }

  void process(Grammar *node)
  {
  }

  void processDecisionPoint(size_t k, const CompressedTokenSet &) {}

  void processMatchCodes(int dpi, const TokenSequenceSet *match, int caseId)
  {
    if (dpi >= 0)
    {
      for (TokenSequenceSet::const_iterator i = match->begin(); i != match->end(); ++i)
      {
        const TokenSequence &t1(*i);
        const MatchCode::const_iterator j(grammar->matchCode.find(t1));
        if (j == grammar->matchCode.end())
        {
          internalerr();
        }
        else
        {
          map->set(j->second.getCode(), dpi, caseId << 1);
        }
      }
    }
  }

private:
  TiledMap2D *map;
};

#endif /* PREDICTIONBUILDER_HPP_ */
