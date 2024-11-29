/*
 * LookaheadCompressor.hpp
 *
 *  Created on: 10.11.2012
 *      Author: Gunther
 */

#ifndef LOOKAHEADCOMPRESSOR_HPP_
#define LOOKAHEADCOMPRESSOR_HPP_

#include "Grammar.hpp"
#include "ItemSet.hpp"

class MarkLookaheadAvailability : public Visitor
{                                typedef Visitor
                                   super;
public:
  MarkLookaheadAvailability() : again(false) {}

  void visitGrammar(Grammar *node)
  {
    section = NONTERMINALS;
    do
    {
      again = false;
      visitNodeList(node->nonTerminals);
    }
    while (again);
  }

  virtual void visitProduction(Production *node)
  {
    if (node->isStartSymbol())
    {
      clear(node->findsLookahead);
    }
    else
    {
      for (NodePointerSet::iterator i = node->references.begin();
           i != node->references.end();
           ++i)
      {
        Node *reference = *i;
        if (   ! reference->findsLookahead
            && reference->whitespaceAllowance == EXPLICIT)
        {
          clear(node->findsLookahead);
          break;
        }
      }
    }

    super::visitProduction(node);

    if (! lastElementChildLeaves(node)) clear(node->leavesLookahead);
  }

  virtual void visitChoice(Choice *node)
  {
    if (! predecessorLeavesOrParentFinds(node)) clear(node->findsLookahead);

    super::visitChoice(node);

    for (NodeList::iterator i = node->cases.begin(); i != node->cases.end(); ++i)
    {
      Node *c = (*i)->element();
      if (! c->leavesLookahead)
      {
        clear(node->leavesLookahead);
        break;
      }
    }
  }

  virtual void visitOptional(Optional *node)
  {
    if (! predecessorLeavesOrParentFinds(node)) clear(node->findsLookahead);
    super::visitOptional(node);
    if (! lastElementChildLeaves(node)) clear(node->leavesLookahead);
  }

  virtual void visitZeroOrMore(ZeroOrMore *node)
  {
    if (   ! predecessorLeavesOrParentFinds(node)
        || ! lastElementChildLeaves(node))
    {
      clear(node->findsLookahead);
    }
    super::visitZeroOrMore(node);
    // set(node->leavesLookahead);
  }

  virtual void visitOneOrMore(OneOrMore *node)
  {
    if (! lastElementChildLeaves(node)) clear(node->findsLookahead);
    super::visitOneOrMore(node);
    // set(node->leavesLookahead);
  }

  virtual void visitSequence(Sequence *node)
  {
    if (! predecessorLeavesOrParentFinds(node)) clear(node->findsLookahead);
    super::visitSequence(node);
    if (! lastElementChildLeaves(node)) clear(node->leavesLookahead);
  }

  virtual void visitString(String *node)
  {
    if (! predecessorLeavesOrParentFinds(node)) clear(node->findsLookahead);
    super::visitString(node);
    clear(node->leavesLookahead);
  }

  virtual void visitRef(Ref *node)
  {
    if (! predecessorLeavesOrParentFinds(node)) clear(node->findsLookahead);
    super::visitRef(node);
    if (! node->nonTerminal || ! node->nonTerminal->leavesLookahead) clear(node->leavesLookahead);
  }

private:
  void clear(bool &flag)
  {
    if (flag)
    {
      flag = false;
      again = true;
    }
  }

  bool predecessorLeavesOrParentFinds(Node *node)
  {
    if (node->precedingElementSibling)
    {
      return node->precedingElementSibling->leavesLookahead;
    }
    else if (   node->getParent()->isChoice()
             || node->getParent()->isOptional()
             || node->getParent()->isZeroOrMore())
    {
      return true;
    }
    else if (node->getParent()->isOneOrMore())
    {
      return predecessorLeavesOrParentFinds(node->getParent());
    }
    else
    {
      return node->getParent()->findsLookahead;
    }
  }

  bool lastElementChildLeaves(NodeWithChildren *node)
  {
    if (node->lastElementChild)
    {
      return node->lastElementChild->leavesLookahead;
    }
    else
    {
      return node->findsLookahead;
    }
  }

  bool again;
};

class LookaheadCompressor : public Visitor
{                          typedef Visitor
                             super;
public:
  LookaheadCompressor() : grammar(0) {}

  void processStates(Grammar *node);
  void visitGrammar(Grammar *node);

  void visitProduction(Production *node)
  {
    if (   node != grammar->whitespace
        || ! grammar->complexWhitespaceIntroducers.empty())
    {
      super::visitProduction(node);
    }
  }

  void visitOptional(Optional *node) {visitNonChoice(node);}
  void visitZeroOrMore(ZeroOrMore *node) {visitNonChoice(node);}
  void visitOneOrMore(OneOrMore *node) {visitNonChoice(node);}

  void visitChoice(Choice *node)
  {
    compressLookahead(node, node->expect(node->k));

    Node *maxMatch = 0;
    size_t maxCount = 0;
    Node *previousConflictCase = 0;
    const TokenSequenceSet *conflicts(node->conflicts(node->k));

    for (NodeList::iterator i = node->cases.begin(); i != node->cases.end(); ++i)
    {
      Node *caze = (*i)->element();

      if (conflicts)
      {
        TokenSequenceSet expect(caze->expect(node->k));
        for (TokenSequenceSet::const_iterator j = conflicts->begin(); j != conflicts->end(); ++j)
        {
          if (expect.erase(*j))
          {
            caze->involvedInConflict = true;
            caze->grammar->hasBacktracking = true;
          }
        }

        if (caze->involvedInConflict)
        {
          if (previousConflictCase)
          {
            previousConflictCase->accept(rop);
          }
          previousConflictCase = caze;
        }

        caze->setMatch(CompressedTokenSet::compressMatch(node->conflictsK, expect, grammar->tokenSequenceFactory, grammar->tokenSequenceSets));
      }
      else
      {
        caze->setMatch(CompressedTokenSet::compressMatch(node->conflictsK, caze->expect(node->k), grammar->tokenSequenceFactory, grammar->tokenSequenceSets));
      }

      size_t count = caze->getMatch().size();
      if (count >= maxCount)
      {
        maxMatch = caze;
        maxCount = count;
      }
    }
    node->defaultCase = maxMatch;

    int caseId = 0;
    for (NodeList::iterator i = node->cases.begin(); i != node->cases.end(); ++i)
    {
      Node *c = (*i)->element();
      c->caseId = c == maxMatch
                ? node->cases.size()
                : ++caseId;

      (*i)->accept(*this);
    }
  }

  void visitRef(Ref *node)
  {
    if (   node->whitespaceAllowance == IMPLICIT
        || node->lexical)
    {
      node->k = 1;
      compressLookahead(node, node->expect(1));
    }
  }

  void visitString(String *node)
  {
    node->k = 1;
    compressLookahead(node, node->expect(1));
  }

  static void determineWhitespaceIntroducers(Grammar *node)
  {
    Production *ws = node->whitespace;

    const TokenSequenceSet wf1(ws->section == TERMINALS ? node->tokenSequence(ws->tokenCode) : ws->first(1));
    const TokenSequenceSet wf2(ws->section == TERMINALS ? node->tokenSequence(ws->tokenCode) : ws->first(2));

    if (node->verbose)
    {
      wprintf(L"using whitespace production %ls\n", ws->name);
#if SELFTEST
      wprintf(L"   first (%ls): %ls\n", ws->name, wf1.toString(L"", L" |", 120, 0, false));
      wprintf(L"   first2(%ls): %ls\n", ws->name, wf2.toString(L"", L" |", 120, 0, false));
#endif
    }

    for (TokenSequenceSet::const_iterator i = wf1.begin(); i != wf1.end(); ++i)
    {
      const Token::Code t(i->first());
      if (   t != Token::eEPSILON
          && t != Token::eEND)
      {
        const Production *root = node->terminalProductionByCode[t]->uniqueRoot;
        if (root == 0)
        {
          if (node->verbose)
          {
            wprintf(L"whitespace introducer %ls is referenced elsewhere\n", node->naming.getName(node, t));
          }
          throw Complaint(L"non-whitespace token occurs in first1(<whitespace>): ", node->naming.getName(node, t));
        }

        bool simple = wf2.contains(node->tokenSequence(t));

#if SELFTEST
        if (node->verbose)
        {
          wprintf(L"first2(%ls).contains(%ls): %ls\n", ws->name, node->naming.getName(node, t), simple ? L"yes" : L"no");
        }
#endif

        for (TokenSequenceSet::const_iterator j = wf2.begin();
             simple && j != wf2.end();
             ++j)
        {
          const TokenSequence &t2(*j);
#if SELFTEST
          if (node->verbose)
          {
            wprintf(L"t2.first: %ls\n", node->naming.getName(node, t2.first()));
            wprintf(L"t2.size: %d\n", t2.size());
            wprintf(L"t2.last: %ls\n", node->naming.getName(node, t2.last()));
          }
#endif
          if (t == t2.first() && t2.size() > 1 && ! wf1.contains(node->tokenSequence(t2.last())))
          {
            simple = false;
          }
          // TODO: verify that Whitespace does not define any actions around t
        }
        if (simple)
        {
          node->simpleWhitespaceIntroducers.insert(node->tokenSequence(t));
          if (node->verbose)
          {
            wprintf(L"simple whitespace introducer: %ls\n", node->naming.getName(node, t));
          }
        }
        else
        {
          node->complexWhitespaceIntroducers.insert(node->tokenSequence(t));
          if (node->verbose)
          {
            wprintf(L"complex whitespace introducer: %ls\n", node->naming.getName(node, t));
          }
        }
      }
    }

    node->whitespaceIntroducers.insertAll(node->simpleWhitespaceIntroducers);
    node->whitespaceIntroducers.insertAll(node->complexWhitespaceIntroducers);
  }

private:
  class RunOffLoadPropagator : public Visitor
  {                           typedef Visitor super;
    public:
    void visitZeroOrMore(ZeroOrMore *node)
    {
      node->runOffLoad = true;
      super::visitZeroOrMore(node);
    }

    void visitOneOrMore(OneOrMore *node)
    {
      node->runOffLoad = true;
      super::visitOneOrMore(node);
    }

    void visitRef(Ref *node)
    {
      Production *p = node->nonTerminal;
      if (p && p->tokenCode < 0 && ! p->runOffLoad)
      {
        p->runOffLoad = true;
        p->accept(*this);
      }
    }
  };

  void visitNonChoice(NodeWithChildren *node)
  {
    if (node->isOneOrMore())
    {
      TokenSequenceSet lookahead(node->expect(node->k));
      lookahead.insertAll(node->follow(node->k));
      compressLookahead(node, lookahead);
    }
    else
    {
      compressLookahead(node, node->expect(node->k));
    }

    const TokenSequenceSet *conflicts(node->conflicts(node->k));
    Node *c = node->firstElementChild;
    if (conflicts)
    {
      rop.visitNodeList(c);
      c->involvedInConflict = true;
      c->grammar->hasBacktracking = true;

      TokenSequenceSet expect(c->expect(node->k));
      for (TokenSequenceSet::const_iterator j = conflicts->begin(); j != conflicts->end(); ++j)
      {
        expect.erase(*j);
      }
      c->setMatch(CompressedTokenSet::compressMatch(node->conflictsK, expect, grammar->tokenSequenceFactory, grammar->tokenSequenceSets));

    }
    else
    {
      c->setMatch(CompressedTokenSet::compressMatch(node->conflictsK, c->expect(node->k), grammar->tokenSequenceFactory, grammar->tokenSequenceSets));
    }
    c->setMatchComplement(matchSetComplement(node, &c->getMatch()));

    visitNodeList(node->firstChild);
  }

  const TokenSequenceSet *matchSetComplement(Node *lookaheadNode,
                                             const TokenSequenceSet *compressed)
  {
    const TokenSequenceSet *parentLookahead = grammar->tokenSequenceSets->resolve(&lookaheadNode->getLookahead()->getMatchSet());
    const TokenSequenceSet *parentConflicts = &lookaheadNode->getConflictMatch();
    return grammar->tokenSequenceSets->setDifference(parentLookahead, grammar->tokenSequenceSets->setUnion(compressed, parentConflicts));
  }

  void compressLookahead(Node *node, const TokenSequenceSet &tokenSet)
  {
    CompressedTokenSet *lookahead = new CompressedTokenSet();
    lookahead->populate(tokenSet,
                        grammar->whitespaceIntroducers,
                        node->conflictsK,
                        node->findsLookahead,
                        grammar->tokenSequenceFactory,
                        grammar->lookaheadSets);
    node->setLookahead(lookahead);

    const TokenSequenceSet *conflicts(node->conflicts(node->k));
    if (conflicts)
    {
      node->setConflictMatch(CompressedTokenSet::compressMatch(node->conflictsK, *conflicts, grammar->tokenSequenceFactory, grammar->tokenSequenceSets));
      node->setConflictMatchComplement(matchSetComplement(node, &node->getConflictMatch()));
    }

    if (grammar->k < node->k)
    {
      grammar->k = node->k;
    }
  }

  Grammar *grammar;
  RunOffLoadPropagator rop;
};

#endif
