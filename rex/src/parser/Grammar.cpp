#include "../common/Memory.hpp"
#include "../common/CompressedMap.hpp"

#include "Grammar.hpp"
#include "ItemSet.hpp"

void Visitor::visitNode(Node *node)
{
  visitNodePreOrder(node);
  visitNodePostOrder(node);
}

void Visitor::visitNodeList(Node *firstNode)
{
  for (Node *node = firstNode; node; node = node->followingSibling)
  {
    node->accept(*this);
  }
}

void Visitor::visitNodeWithChildren(NodeWithChildren *node)
{
  visitNodePreOrder(node);
  visitNodeList(node->firstChild);
  visitNodePostOrder(node);
}

void Visitor::visitGrammar(Grammar *node)
{
  section = GRAMMAR;
  visitNodePreOrder(node);
  section = PROLOG;
  if (node->prolog) visitNodeList(node->prolog);
  section = NONTERMINALS;
  if (node->nonTerminals) visitNodeList(node->nonTerminals);
  section = TERMINALS;
  if (node->terminals) visitNodeList(node->terminals);
  section = AUTOMATIC;
  if (node->firstChild) visitNodeList(node->firstChild);
  section = EPILOG;
  if (node->epilog) visitNodeList(node->epilog);
  section = GRAMMAR;
  visitNodePostOrder(node);
}

void Visitor::visitChoice(Choice *node)
{
  visitNodePreOrder(node);
  for (NodeList::iterator i = node->cases.begin(); i != node->cases.end(); ++i)
  {
    (*i)->accept(*this);
  }
  visitNodePostOrder(node);
}

void Visitor::visitExclusion(Exclusion *node)
{
  visitNodePreOrder(node);
  node->lhs->accept(*this);
  node->rhs->accept(*this);
  visitNodePostOrder(node);
}

void Visitor::visitPredicate(Predicate *node)
{
  visitNodePreOrder(node);
  node->lhs->accept(*this);
  node->rhs->accept(*this);
  visitNodePostOrder(node);
}

void Visitor::visitContext(Context *node)
{
  visitNodePreOrder(node);
  node->expr->accept(*this);
  node->context->accept(*this);
  visitNodePostOrder(node);
}

void Visitor::visitComplement(Complement *node)
{
  visitNodePreOrder(node);
  node->charClass->accept(*this);
  visitNodePostOrder(node);
}

void Visitor::visitPreference(Preference *node)
{
  visitNodePreOrder(node);
  for (NodeList::iterator i = node->lhs.begin(); i != node->lhs.end(); ++i)
  {
    (*i)->accept(*this);
  }
  for (NodeList::iterator i = node->rhs.begin(); i != node->rhs.end(); ++i)
  {
    (*i)->accept(*this);
  }
  visitNodePostOrder(node);
}

void Visitor::visitDelimiter(Delimiter *node)
{
  visitNodePreOrder(node);
  node->lhs->accept(*this);
  for (NodeList::iterator i = node->rhs.begin(); i != node->rhs.end(); ++i)
  {
    (*i)->accept(*this);
  }
  visitNodePostOrder(node);
}

void Visitor::visitEquivalence(Equivalence *node)
{
  visitNodePreOrder(node);
  node->lhs->accept(*this);
  node->rhs->accept(*this);
  visitNodePostOrder(node);
}

void Visitor::visitProcessingInstruction(ProcessingInstruction *node) {visitNodeWithContext(node);}
void Visitor::visitEndOfFile(EndOfFile *node) {visitNode(node);}
void Visitor::visitChar(Char *node) {visitNode(node);}
void Visitor::visitCharCode(CharCode *node) {visitNode(node);}
void Visitor::visitCharRange(CharRange *node) {visitNode(node);}
void Visitor::visitCharCodeRange(CharCodeRange *node) {visitNode(node);}

void Visitor::visitNodeWithContext(NodeWithContext *node) {visitNode(node);}
void Visitor::visitRef(Ref *node) {visitNodeWithContext(node);}
void Visitor::visitString(String *node) {visitNodeWithContext(node);}

void Visitor::visitProduction(Production *node) {visitNodeWithChildren(node);}
void Visitor::visitCharClass(CharClass *node) {visitNodeWithChildren(node);}
void Visitor::visitSequence(Sequence *node) {visitNodeWithChildren(node);}
void Visitor::visitOptional(Optional *node) {visitNodeWithChildren(node);}
void Visitor::visitZeroOrMore(ZeroOrMore *node) {visitNodeWithChildren(node);}
void Visitor::visitOneOrMore(OneOrMore *node) {visitNodeWithChildren(node);}

void ReverseVisitor::visitNode(Node *node)
{
  visitNodePreOrder(node);
  visitNodePostOrder(node);
}

void ReverseVisitor::visitNodeList(Node *lastNode)
{
  for (Node *node = lastNode; node; node = node->precedingSibling)
  {
    node->accept(*this);
  }
}

void ReverseVisitor::visitNodeWithChildren(NodeWithChildren *node)
{
  visitNodePreOrder(node);
  visitNodeList(node->lastChild);
  visitNodePostOrder(node);
}

void ReverseVisitor::visitGrammar(Grammar *node)
{
  section = NONTERMINALS;
  if (node->nonTerminals) Visitor::visitNodeList(node->nonTerminals);
}

bool NodeIdLess::operator()(const Node *lhs, const Node *rhs) const
{
  if (lhs->id < 0 || rhs->id < 0)
  {
    internalerr();
  }
  return lhs->id < rhs->id;
}

const TokenSequenceSet *Node::conflicts(size_t k) const
{
  return k <= kConflicts
       ? conflictsK[k - 1]
       : 0;
}

bool Node::setConflicts(size_t k, TokenSequenceSet *conflicts)
{
  bool empty = true;

  for (TokenSequenceSet::iterator i = conflicts->begin(); i != conflicts->end(); ++i)
  {
    const TokenSequence &l(*i);
    if (l.last() != Token::eWS)
    {
      empty = false;
      break;
    }
  }

  if (empty)
  {
    delete conflicts;
    if (this->k == 0 || this->k > k)
    {
      this->k = k;
    }
  }
  else
  {
    if (kConflicts < k)
    {
      conflictsK = REALLOCATE_ARRAY(TokenSequenceSet *, conflictsK, k + 1);
      for (size_t i = kConflicts; i <= k; ++i)
      {
        conflictsK[i] = 0;
      }
      kConflicts = k;
    }

    if (conflictsK[k - 1] == 0)
    {
      conflictsK[k - 1] = conflicts;
    }
    else
    {
      conflictsK[k - 1]->insertAll(*conflicts);
      delete conflicts;
    }

    for (TokenSequenceSet::iterator i = conflictsK[k - 1]->begin(); i != conflictsK[k - 1]->end(); )
    {
      const TokenSequence &l(*i);
      if (l.last() == Token::eWS)
      {
        TokenSequenceSet::iterator j(i);
        ++j;
        conflictsK[k - 1]->erase(i);
        i = j;
      }
      else
      {
        ++i;
      }
    }
  }
  return empty;
}

void Node::saturatePass(size_t k, TokenSequenceSet &result, void (*callee)(Node*, size_t, TokenSequenceSet&))
{
  if (result.getPass() < grammar->currentPass)
  {
    result.setPass(grammar->currentPass);
    result.setInProgress(true);

    // perform set specific calculation

    callee(this, k, result);

    result.setInProgress(false);
    if (! result.contains(grammar->cyclic))
    {
      result.setPass(Grammar::FINALPASS);
    }
    else if (grammar->currentPass == Grammar::FINALPASS)
    {
      result.erase(grammar->cyclic);
    }
    else
    {
      grammar->cyclicSetSize += result.size();
    }
  }
  else if (result.isInProgress())
  {
    result.insert(grammar->cyclic);
  }
}

/**
 * Iteratively saturate calculation of result set, until there is no
 * further increase in sets with cyclic dependencies.
 */
void Node::saturate(size_t k, TokenSequenceSet *&result, void (*callee)(Node*, size_t, TokenSequenceSet&))
{
  if (grammar->currentPass)
  {
    // saturation in progress, just join it

    saturatePass(k, *result, callee);
    if (! result->isCollected() && ! result->isInProgress() && result->getPass() == Grammar::FINALPASS)
    {
      result = const_cast<TokenSequenceSet *>(grammar->tokenSequenceSets->collect(result));
    }
  }
  else for (size_t oldSize = 0; ; oldSize = grammar->cyclicSetSize)
  {
    grammar->cyclicSetSize = 0;

    ++grammar->currentPass;
    saturatePass(k, *result, callee);

    if (oldSize == grammar->cyclicSetSize)
    {
      // no increase in sets with cyclic dependencies. Further passes
      // would not provide a change.

      if (oldSize)
      {
        // if any cyclic dependencies were found, the sets must be
        // finalized by marking them complete (i.e. FINALPASS)

        grammar->currentPass = Grammar::FINALPASS;
        saturatePass(k, *result, callee);
      }
      grammar->currentPass = 0;
      result = const_cast<TokenSequenceSet *>(grammar->tokenSequenceSets->collect(result));
      return;
    }

    // here, result contains token eCYCLIC, which also may be contained
    // in some of the sets that result depends on. Thus we run another
    // pass of the same calculation.
  }
}

static TokenSequenceSet *&getResultSet(size_t k, size_t &kResultSets, TokenSequenceSet **&resultSetPerK)
{
  if (kResultSets < k)
  {
    resultSetPerK = REALLOCATE_ARRAY(TokenSequenceSet *, resultSetPerK, k);
    for (size_t i = kResultSets; i < k; ++i)
    {
      resultSetPerK[i] = 0;
    }
    kResultSets = k;
  }
  if (resultSetPerK[k - 1] == 0)
  {
    resultSetPerK[k - 1] = new TokenSequenceSet(__FILE__, __LINE__);
  }
  return resultSetPerK[k - 1];
}

static void shieldedFirst(Node *node, size_t k, TokenSequenceSet& result)
{
  if (node->followingElementSibling && ! node->isProduction())
  {
    TokenSequenceSet f;
    node->calculateFirst(k, f);
//    node->upsize(f, &node->followingElementSibling->firstAccessor, k, result);
    result.insertUpsized(f, node->followingElementSibling->firstAccessor, k, node->grammar->tokenSequenceFactory);
  }
  else
  {
    node->calculateFirst(k, result);
  }

  if (node->whitespaceAllowance == IMPLICIT)
  {
    result.insert(node->grammar->tokenSequence(Token::eWS));
  }

  if (node->automaticSemicolonInsertion == SEMICOLON)
  {
    Production *rBrace = node->grammar->stringByName.byStringValue(L"}");
    if (rBrace != 0)
    {
      result.insert(node->grammar->tokenSequence(rBrace->tokenCode));
    }

    Production *eof = node->grammar->terminalByName.byNodeType(EndOfFile().getNodeType());
    if (eof != 0)
    {
      result.insert(node->grammar->tokenSequence(eof->tokenCode));
    }

    result.insert(node->grammar->tokenSequence(Token::eOTHER));
  }

#define EXPERIMENTAL 0
#if EXPERIMENTAL
  if (node->getParent()->isChoice())
  {
    Choice *choice = static_cast<Choice *>(node->getParent());
    if (choice->getOrdered())
    {
      TokenSequenceSet resolved;
      for (NodeList::const_iterator i = choice->cases.begin(); *i != node; ++i)
      {
        Node *element = (*i)->element();
        if (element)
        {
          resolved.insertAll(element->first(k));
        }
      }

      resolved.erase(node->grammar->tokenSequence(Token::eEPSILON));
      resolved.erase(node->grammar->tokenSequence(Token::eWS));
      resolved.erase(node->grammar->tokenSequence(Token::eCYCLIC));
      TokenSequenceSet difference;
      difference.insertDifferenceOf(result, resolved);
      result.clear();
      result.insertAll(difference);
    }
  }
#endif
}

static void shieldedFollow(Node *node, size_t k, TokenSequenceSet& result)
{
  NodePointerSet transitive;
  node->fastFollow(k, result, transitive);

  if (! transitive.empty())
  {
    for (NodePointerSet::iterator i = transitive.begin(); i != transitive.end(); ++i)
    {
      Node *node = *i;
      result.insertAll(node->follow(k));
    }
  }
}

static void shieldedFollowItem(Node *node, size_t k, TokenSequenceSet& result)
{
  NodePointerSet transitive;
  node->fastFollowItem(k, result, transitive);

  if (! transitive.empty())
  {
    for (NodePointerSet::iterator i = transitive.begin(); i != transitive.end(); ++i)
    {
      Node *node = *i;
      result.insertAll(node->followItem(k));
    }
  }
}

void Node::fastFollowers(size_t k,
                         const TokenSequenceSet *firstSet,
                         Node *origin,
                         TokenSequenceSet &result,
                         NodePointerSet &transitive)
{
  firstSet = grammar->tokenSequenceSets->resolve(firstSet);

  if (firstSet != grammar->epsilon && ! origin->production->wsExplicit)
  {
    result.insert(grammar->tokenSequence(Token::eWS));
  }

  if (firstSet->contains(grammar->tokenSequenceFactory->emptySequence()))
  {
    if (origin->parent && (origin->parent->isOneOrMore() || origin->parent->isZeroOrMore()))
    {
      fastFollowers(k, &origin->parent->first(k), origin->parent, result, transitive);
    }
    transitive.insert(origin->parent);
    firstSet = grammar->tokenSequenceSets->eraseIfEndsWith(firstSet, Token::eEPSILON);
  }

  result.insertUpsized(*firstSet, origin->parent->followAccessor, k, grammar->tokenSequenceFactory);
}

void Node::fastFollow(size_t k, TokenSequenceSet &result, NodePointerSet &transitive)
{
  if (followingElementSibling)
  {
    fastFollowers(k, &followingElementSibling->first(k), this, result, transitive);
  }
  else
  {
    fastFollowers(k, grammar->epsilon, this, result, transitive);
  }
}

void Node::fastFollowItem(size_t k, TokenSequenceSet &result, NodePointerSet &transitive)
{
  if (followingElementSibling)
  {
    fastFollowers(k, &followingElementSibling->first(k), this, result, transitive);
  }
  else
  {
    fastFollowers(k, grammar->epsilon, this, result, transitive);
  }
}

bool NodeWithChildren::isLLOptionalOrMultiple(size_t k)
{
  if (this->k > 0)
  {
    return this->k <= k;
  }

  if (firstElementChild)
  {
    TokenSequenceSet *conflicts = new TokenSequenceSet(__FILE__, __LINE__);
    conflicts->insertIntersectionOf(firstElementChild->expect(k), follow(k));

    if (k > 1 || ! firstElementChild->first(1).contains(grammar->tokenSequenceFactory->emptySequence()))
    {
      return setConflicts(k, conflicts);
    }
  }

  internalerr();
  return false;
}

void NodeWithContext::setDistance(int d)
{
  distance = d;
  grammar->maxDistance = Math::max(grammar->maxDistance, d);
}

Grammar::~Grammar()
{
  fflush(stdout);

  for (EmbeddedReduceItems::iterator i = embeddedReduceItems.begin(); i != embeddedReduceItems.end(); ++i)
  {
    Reduce *reduce = i->second;
    delete reduce;
  }

  freeNodeList(prolog);
  freeNodeList(nonTerminals);
  freeNodeList(terminals);
  freeNodeList(epilog);

  free(externalTokenCode);

  delete tokenSequenceSets;
  delete tokenSequenceFactory;
  delete matchcodeTable;
  delete caseidTable;
  delete states;
}

Production::~Production()
{
  free(context);
  free(name);

  for (ReduceItems::iterator i = reduceItems.begin(); i != reduceItems.end(); ++i)
  {
    Reduce *reduce = static_cast<Reduce *>(i->second);
    if (! reduce->isImplicit)
    {
      delete reduce;
    }
  }
}

void Production::fastFollow(size_t k, TokenSequenceSet &result, NodePointerSet &transitive)
{
  if (isStartSymbol() || this == grammar->whitespace)
  {
    result.insert(grammar->tokenSequence(Token::eOTHER));
  }
  for (NodePointerSet::iterator j = references.begin();
       j != references.end();
       ++j)
  {
    (*j)->Node::fastFollow(k, result, transitive);
  }
}

void Production::fastFollowItem(size_t k, TokenSequenceSet &result, NodePointerSet &transitive)
{
  result.insert(grammar->tokenSequenceFactory->emptySequence());
}

void Production::calculateUniqueRoot()
{
  uniqueRoot = 0;
  ProductionSet referencingProductionsTC;
  ProductionList toBeDone(1, this);

  for (ProductionList::iterator i = toBeDone.begin(); i != toBeDone.end(); ++i)
  {
    const Production *target = *i;
    referencingProductionsTC.insert(target);
    for (NodePointerSet::const_iterator j = target->references.begin();
         j != target->references.end();
         ++j)
    {
      Production *source = (*j)->production;
      if (source == 0)
        throw Complaint(L"internal error: reference from nowhere to: ", target->name);
      else if (referencingProductionsTC.insert(source).second)
      {
        toBeDone.push_back(source);
      }
    }
  }

  for (ProductionSet::iterator i = referencingProductionsTC.begin();
       i != referencingProductionsTC.end();
       ++i)
  {
    const Production *source = (*i)->production;
    if (source->references.empty() || (source->references.size() == 1 && (*source->references.begin())->production == source))
    {
      if (uniqueRoot == 0)
      {
        uniqueRoot = source;
      }
      else
      {
        uniqueRoot = 0;
        break;
      }
    }
  }
}

int Production::getStateId() const
{
  return (*grammar->states)[state]->getStateId();
}

const TokenSequenceSet *Node::blackList(size_t k)
{
  const TokenSequenceSet *precedingCasesLookahead = grammar->emptySet;

  if (isRestrictedCase() && this != static_cast<Choice *>(parent)->cases.front())
  {
    Choice *choice = static_cast<Choice *>(parent);
    for (NodeList::const_iterator i = choice->cases.begin(); *i != this; ++i)
    {
      Node *element = (*i)->element();
      if (element)
      {
        precedingCasesLookahead = grammar->tokenSequenceSets->setUnion(precedingCasesLookahead, &element->expect(k));
      }
      else
      {
        precedingCasesLookahead = grammar->tokenSequenceSets->setUnion(precedingCasesLookahead, &choice->follow(k));
      }
    }
  }
  return precedingCasesLookahead;
}

const TokenSequenceSet &Node::first(size_t k)
{
  TokenSequenceSet *&result = getResultSet(k, kFirst, firstK);
  if (! result->isCollected()) saturate(k, result, shieldedFirst);
  return *result;
}

const TokenSequenceSet &Node::follow(size_t k)
{
  TokenSequenceSet *&result = getResultSet(k, kFollow, followK);
  if (! result->isCollected()) saturate(k, result, shieldedFollow);
  return *result;
}

const TokenSequenceSet &Node::followItem(size_t k)
{
  TokenSequenceSet *&result = getResultSet(k, kFollowItem, followItemK);
  if (! result->isCollected()) saturate(k, result, shieldedFollowItem);
  return *result;
}

const TokenSequenceSet &Node::expect(size_t k)
{
  Node *last = getParent()->isNodeWithChildren()
             ? static_cast <NodeWithChildren *> (getParent())->lastElementChild
             : this;
  const TokenSequenceSet *result = grammar->tokenSequenceSets->upsize(&first(k), k, &last->followAccessor);
//  if (k == grammar->maxK)
  {
    const TokenSequenceSet* bl = blackList(k);
    if (! bl->empty())
    {
      result = grammar->tokenSequenceSets->setDifference(result, bl);
    }
  }
  return *result;
}

const TokenSequenceSet &Node::first(size_t k, const TokenSequenceSetAccessor &lookaheadAccessor)
{
  Node *last = getParent()->isNodeWithChildren()
             ? static_cast <NodeWithChildren *> (getParent())->lastElementChild
             : this;
  const TokenSequenceSet *localFirstK = grammar->tokenSequenceSets->upsize(&first(k), k, &last->followItemAccessor);
  return *grammar->tokenSequenceSets->upsize(localFirstK, k, &lookaheadAccessor);
}

const TokenSequenceSet &Node::follow(size_t k, const TokenSequenceSetAccessor &lookaheadAccessor)
{
  return *grammar->tokenSequenceSets->upsize(&followItem(k), k, &lookaheadAccessor);
}

const TokenSequenceSet &Node::getMatch() const
{
  return match
       ? *match
       : *grammar->emptySet;
}

const TokenSequenceSet &Node::getMatch(MatchType &m)
{
  if (match == 0)
  {
    m = NOMATCH;
    return *grammar->emptySet;
  }
  else if (parent->isChoice())
  {
    m = this == static_cast<const Choice *>(parent)->defaultCase
      ? DEFAULT
      : CASE;
    return *match;
  }
  else if (match->size() <= matchComplement->size())
  {
    m = IF;
    return *match;
  }
  else
  {
#if 0
    wchar_t *ls = parent->getLookahead()->getMatchSet().toString(grammar, L"\n[lookahead] ", L" |", 100, 0, false, 0);
    wchar_t *ms = match->toString(grammar, L"\n[match] ", L" |", 100, 0, false, 0);
    wchar_t *cs = matchComplement->toString(grammar, L"\n[matchComplement]", L" |", 100, 0, false, 0);
    printf("[lookahead size=%d] %ls\n[match size=%d] %ls\n[matchComplement size=%d] %ls\n\n",
            parent->getLookahead()->getMatchSet().size(), ls,
            match->size(), ms,
            matchComplement->size(), cs);
    free(ls);
    free(ms);
    free(cs);
#endif

    m = IFNOT;
    return *matchComplement;
  }
}

const TokenSequenceSet &Node::getConflictMatch() const
{
  return conflictMatch
       ? *conflictMatch
       : *grammar->emptySet;
}

const TokenSequenceSet &Node::getConflictMatch(MatchType &m)
{
  if (conflictMatch == 0)
  {
    m = NOMATCH;
    return *grammar->emptySet;
  }
  else if (conflictMatch->size() <= conflictMatchComplement->size())
  {
    m = IF;
    return *conflictMatch;
  }
  else
  {
    m = IFNOT;
    return *conflictMatchComplement;
  }
}

bool Node::isRestrictedCase() const
{
  return ! getParent()->isChoice()
       ? false
       : static_cast<Choice *>(getParent())->getOrdered();
}

Node *Node::closestRestrictedCaseAncestorOrSelf()
{
  for (Node *node = this; ! node->isProduction(); node = node->getParent())
  {
    if (node->isRestrictedCase())
    {
      return node;
    }
  }
  return 0;
}

void Node::collectRestrictedCaseNodes(const ItemSet* shiftItems, NodeSet &restrictions, RestrictionsByProduction &restrictionsByProduction)
{
  if (getParent() != 0)
  {
    for (Node *node = this; ! node->isProduction(); node = node->getParent())
    {
      if (node->isRestrictedCase())
      {
        restrictions.insert(node);
      }
    }
  }

  bool unknown = restrictionsByProduction.find(production) == restrictionsByProduction.end();
  NodeSet &shiftRestrictions = restrictionsByProduction[production];
  if (unknown)
  {
    for (ItemSet::const_iterator i = shiftItems->begin(); i != shiftItems->end(); ++i)
    {
      Node *node = i->first;
      if (node->shiftSymbol() == production)
      {
        node->collectRestrictedCaseNodes(shiftItems, shiftRestrictions, restrictionsByProduction);
      }
    }
  }
  if (restrictions != shiftRestrictions)
  {
    restrictions.insert(shiftRestrictions.begin(), shiftRestrictions.end());
  }

  if (restrictions.empty())
  {
    restrictions.insert(0);
  }
}

Production *Grammar::startSymbol() const
{
  for (Node *n = nonTerminals; n; n = n->followingSibling)
  {
    Production *p = static_cast <Production *> (n);
    if (p->isStartSymbol())
    {
      return p;
    }
  }
  return 0;
}

bool Grammar::derivesToEmptySequence() const
{
  return startSymbol()->derivesToEmptySequence();
}

Production *ProductionTable::byStringValue(const wchar_t *value) const
{
  for (const_iterator i = begin(); i != end(); ++i)
  {
    Production *p = i->second;
    if (p->firstChild == p->lastChild &&
        p->firstElementChild &&
        p->firstElementChild->isString())
    {
      if (wcscmp(static_cast<String *>(p->firstElementChild)->value, value) == 0)
      {
        return p;
      }
    }
  }
  return 0;
}

Production *ProductionTable::byNodeType(const wchar_t *nodeType) const
{
  for (const_iterator i = begin(); i != end(); ++i)
  {
    Production *p = i->second;
    if (p->firstChild == p->lastChild &&
        p->firstElementChild &&
        wcscmp(p->firstElementChild->getNodeType(), nodeType) == 0)
    {
      return p;
    }
  }
  return 0;
}
