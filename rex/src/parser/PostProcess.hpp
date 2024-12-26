/*
 * PostProcess.hpp
 *
 *  Created on: 01.08.2008
 *      Author: Gunther
 */

#ifndef POSTPROCESS_HPP
#define POSTPROCESS_HPP

#include "Grammar.hpp"
#include "Naming.hpp"

class Relink : public Visitor
{             typedef Visitor super;
public:
  Relink() : grammar(0), production(0) {}

  virtual ~Relink() {}

  void visitGrammar(Grammar *node)
  {
    grammar = node;
    super::visitGrammar(node);
    grammar = 0;
  }

  void visitProduction(Production *node)
  {
    production = node;
    super::visitProduction(node);
    production = 0;
  }

  void visitNodePreOrder(Node *node)
  {
    node->grammar = grammar;
    node->production = production;
  }

  void visitProcessingInstruction(ProcessingInstruction *node)
  {
    super::visitProcessingInstruction(node);
    node->active = node->grammar->variant && 0 == wcscmp(node->target, node->grammar->variant);
    if (node->isActive() && section == NONTERMINALS)
    {
      IdByContent::iterator i = idByContent.find(node->content);
      if (i == idByContent.end())
      {
        node->contentId = idByContent.size();
        idByContent.insert(IdByContent::value_type(node->content, node));
        grammar->distinctCodeAnnotations.push_back(node);
      }
      else
      {
        node->contentId = i->second->contentId;
      }
    }
  }

  void visitNodeWithChildren(NodeWithChildren *node)
  {
    super::visitNodeWithChildren(node);

    for (Node *child = node->firstChild; child; child = child->followingSibling)
    {
      if (child->isElement())
      {
        if (node->firstElementChild == 0)
        {
          node->firstElementChild = child;
          node->lastElementChild = child;
          for (Node *i = node->firstChild; i != child; i = i->followingSibling)
          {
            i->followingElementSibling = child;
          }
        }
        else
        {
          child->precedingElementSibling = node->lastElementChild;
          child->precedingElementSibling->followingElementSibling = child;
          for (Node *i = node->lastElementChild->followingSibling; i != child; i = i->followingSibling)
          {
            i->precedingElementSibling = node->lastElementChild;
            i->followingElementSibling = child;
          }
          node->lastElementChild = child;
        }
      }
    }
    if (node->lastElementChild)
    {
      for (Node *i = node->lastElementChild->followingSibling; i; i = i->followingSibling)
      {
        i->precedingElementSibling = node->lastElementChild;
      }
    }
  }

private:
  Grammar *grammar;
  Production *production;
  typedef std::map<const wchar_t *, ProcessingInstruction *, PtrLess<wchar_t> > IdByContent;
  IdByContent idByContent;
};

class MarkReduceByCount : public ReverseVisitor
{                        typedef ReverseVisitor
                                 super;
public:
  MarkReduceByCount() : reduceType(reduceUnknown) {}

  void visitProduction(Production *node)
  {
    reduceType = reduceUnknown;
    super::visitProduction(node);
  }

  void visitNodePreOrder(Node * node)
  {
    if (node->reduceItem != 0 && ! node->reduceItem->isImplicit)
    {
      node->reduceItem->reduceType = node->reduceItem->getDistance() >= 0 ? reduceByCount : reduceByLookback;
      reduceType = node->reduceItem->reduceType;
    }
  }

  void visitNodeWithContext(NodeWithContext *node)
  {
    if (node->isActive())
    {
      visitNodePreOrder(node);
      if (reduceType == reduceUnknown)
      {
        const wchar_t *name = node->isRef() ? static_cast<Ref *>(node)->name
                            : node->isString() ? static_cast<String *>(node)->value
                            : L"";
        fprintf(stderr, "reduceType unknown in production %ls, node type %ls(%ls)\n", node->production->name, node->getNodeType(), name);
        internalerr();
      }
      if (reduceType == reduceByCount && node->getDistance() < 0)
      {
        reduceType = reduceByLookback;
      }
      node->reduceType = reduceType;
    }
  }

  void visitChoice(Choice *node)
  {
    visitNodePreOrder(node);
    ReduceType rhsReduceType = reduceType;
    ReduceType lhsReduceType = reduceUnknown;
    for (NodeList::iterator i = node->cases.begin(); i != node->cases.end(); ++i)
    {
      reduceType = rhsReduceType;
      (*i)->accept(*this);
      if (lhsReduceType == reduceUnknown || reduceType == reduceByLookback)
      {
        lhsReduceType = reduceType;
      }
    }
    reduceType = lhsReduceType;
  }

private:
  ReduceType reduceType;
};

class AddReduceItems : public Visitor
{                     typedef Visitor
                              super;
public:
  AddReduceItems()
  : reduceCase(0)
  {}

  void visitProduction(Production *node)
  {
    super::visitProduction(node);
    node->accept(addImplicitReduceItems);

    int nonProcessingReduceCase = -1;
    for (ReduceItems::reverse_iterator i = node->reduceItems.rbegin(); i != node->reduceItems.rend(); ++i)
    {
      Reduce *r = i->second;
      if (r->reduceCase < 0)
      {
        if (r->processingInstruction)
        {
          r->reduceCase = reduceCase;
          reduceCase += 2;
        }
        else
        {
          if (nonProcessingReduceCase < 0)
          {
            nonProcessingReduceCase = reduceCase;
            reduceCase += 2;
          }
          r->reduceCase = nonProcessingReduceCase;
        }
      }
    }
  }

  void visitNodeWithChildren(NodeWithChildren *node)
  {
    for (Node *child = node->lastChild; child; child = child->precedingSibling)
    {
      if (child->isElement())
      {
        child->accept(*this);
        return;
      }
      else if (child->isActive())
      {
        addReduceItem(child);
        return;
      }
    }
    addReduceItem(node);
  }

  void visitNode(Node *node)
  {
    addReduceItem(node);
  }

  void visitOptional(Optional *node)
  {
    addReduceItem(node);
    super::visitOptional(node);
  }

  void visitOneOrMore(OneOrMore *node)
  {
    addReduceItem(node);
  }

  void visitZeroOrMore(ZeroOrMore *node)
  {
    addReduceItem(node);
  }

private:
  class AddImplicitReduceItems : public Visitor
  {                              typedef Visitor
                                 super;
  public:
    void visitProcessingInstruction(ProcessingInstruction *node)
    {
      if (node->isActive() && node->reduceItem == 0)
      {
        Reduce *&reduceItem = node->grammar->embeddedReduceItems[node->content];
        if (reduceItem == 0)
        {
          if (node->grammar->maxImplicitNonterminalCode < 0)
          {
            node->grammar->maxImplicitNonterminalCode = node->grammar->maxNonterminalCode;
          }
          ++node->grammar->maxImplicitNonterminalCode;
          reduceItem = new Reduce(node->grammar->maxImplicitNonterminalCode, 0, node, true, 0, node->grammar);
          node->production->reduceItems[ReduceArguments(node->grammar->maxImplicitNonterminalCode, 0, node->getContentId(), 0)] = reduceItem;
        }
        node->reduceItem = reduceItem;
      }
    }
  };

  void addReduceItem(Node *node)
  {
    int count = reduceCount(node);
    Node *restrictedCase = node->closestRestrictedCaseAncestorOrSelf();

    ProcessingInstruction *processingInstruction = node->isProcessingInstruction() ? static_cast<ProcessingInstruction *>(node) : 0;
    int targetCodeId = processingInstruction == 0 ? -1 : processingInstruction->getContentId();
    ReduceArguments reduceArguments(node->production->nonterminalCode, count, targetCodeId, restrictedCase);
    Reduce *&reduceItem = node->production->reduceItems[reduceArguments];
    if (reduceItem == 0)
    {
      reduceItem = new Reduce(node->production->nonterminalCode, count, processingInstruction, false, restrictedCase, node->grammar);
    }
    node->reduceItem = reduceItem;
  }

  static Node *predecessor(Node *node)
  {
    if (node->precedingSibling)
      return node->precedingSibling;
    else if (node->getParent()->isProduction())
      return 0;
    else
      return predecessor(node->getParent());
  }

  static int reduceCount(Node* node, bool hideOptional = false)
  {
    if (node == 0 || node->isProduction())
    {
      return 0;
    }
    else if (node->isRef() || node->isString())
    {
      int predecessorReduceCount = static_cast<NodeWithContext *>(node)->getDistance();
      return predecessorReduceCount >= 0 ? 1 + predecessorReduceCount : predecessorReduceCount;
    }
    else if (node->isProcessingInstruction())
    {
      return node->isActive()
           ? hideOptional + static_cast<NodeWithContext *>(node)->getDistance()
           : reduceCount(predecessor(node), hideOptional);
    }
    else if (node->isSequence())
    {
      Node *lastChild = static_cast<Sequence *>(node)->lastChild;
      return lastChild == 0
           ? reduceCount(predecessor(node), hideOptional)
           : reduceCount(lastChild, hideOptional);
    }
    else if (node->isOptional())
    {
      return hideOptional ? VARIABLE : reduceCount(predecessor(node), true);
    }
    else if (node->isChoice())
    {
      Choice *choice = static_cast<Choice *>(node);
      int choiceReduceCount = UNKNOWN;
      for (NodeList::iterator i = choice->cases.begin(); i != choice->cases.end(); ++i)
      {
        Node *caze = *i;
        int caseReduceCount = reduceCount(caze, hideOptional);
        if (caseReduceCount < 0)
        {
          return caseReduceCount;
        }
        if (choiceReduceCount == UNKNOWN)
        {
          choiceReduceCount = caseReduceCount;
        }
        else if (choiceReduceCount != caseReduceCount)
        {
          return VARIABLE;
        }
      }
      return choiceReduceCount;
    }
    else if (! node->isZeroOrMore() && ! node->isOneOrMore())
    {
      fprintf(stderr, "invalid node type: %ls\n", node->getNodeType());
      internalerr();
    }
    return VARIABLE;
  }

  int reduceCase;
  AddImplicitReduceItems addImplicitReduceItems;
};

class SetDistance : public Visitor
{                  typedef Visitor
                           super;
public:
  SetDistance()
  : distance(0)
  {}

  void visitGrammar(Grammar *node)
  {
    section = NONTERMINALS;
    if (node->nonTerminals) visitNodeList(node->nonTerminals);
  }

  void visitProduction(Production *node)
  {
    distance = 0;
    super::visitProduction(node);
    node->accept(addReduceItems);
    node->accept(markReduceByCount);
  }

  void visitOneOrMore(OneOrMore *node)
  {
    distance = VARIABLE;
    super::visitOneOrMore(node);
  }

  void visitZeroOrMore(ZeroOrMore *node)
  {
    distance = VARIABLE;
    super::visitZeroOrMore(node);
  }

  void visitChoice(Choice *node)
  {
    int d1 = distance;
    int d2 = UNKNOWN;
    for (NodeList::iterator i = node->cases.begin(); i != node->cases.end(); ++i)
    {
      Node *caze = *i;
      distance = d1;
      caze->accept(*this);
      if (d2 == UNKNOWN)
        d2 = distance;
      else if (d2 != distance)
        d2 = VARIABLE;
    }
    distance = d2;
  }

  void visitOptional(Optional *node)
  {
    int d = distance;
    visitNodeList(node->firstChild);

    if (d != distance)
    {
      bool isRepeated = false;
      bool hasFollowers = false;
      for (Node *n = node; n != node->production; n = n->getParent())
      {
        if (hasLrFollowingSiblings(n))
        {
          hasFollowers = true;
          break;
        }
        if (n->isOneOrMore() || n->isZeroOrMore())
        {
          isRepeated = true;
          break;
        }
      }

      Node *child = node->lastElementChild;

//      fprintf(stderr, "--- optional candidate: %ls ---\n", node->production->name);
//      fprintf(stderr, "   hasFollowers: %d\n", hasFollowers);
//      fprintf(stderr, "     isRepeated: %d\n", isRepeated);
//      fprintf(stderr, "      rc(child): %d\n", reduceCount(child));
//      fprintf(stderr, "       rc(node): %d\n", reduceCount(node));

      if (child != 0 &&
          ! isRepeated &&
          ! hasFollowers)
      {
        distance = d;
      }
      else
      {
        distance = VARIABLE;
      }
    }
  }

  void visitNodeWithContext(NodeWithContext *node)
  {
    node->setDistance(distance);
    if (distance >= 0 && node->isActive())
    {
      ++distance;
    }
  }

private:
  static bool hasLrFollowingSiblings(Node *node)
  {
    if (node->followingSibling)
      for (Node *n = node->followingSibling; n; n = n->followingSibling)
        if (n->isActive())
          return true;
    return false;
  }

  AddReduceItems addReduceItems;
  MarkReduceByCount markReduceByCount;
  int distance;
};

class Renumber : public Visitor
{               typedef Visitor
                        super;
public:
  Renumber() : id(0) {}
  void visitNodePreOrder(Node *node)
  {
    node->id = ++id;
    if (node->reduceItem && node->reduceItem->id < 0)
    {
      node->reduceItem->id = ++id;
    }
  }

private:
  int id;
};

class MarkReachable : public Visitor
{
public:
  void visitProduction(Production *node)
  {
    if (! node->runPayload)
    {
      node->runPayload = true;
      Visitor::visitProduction(node);
    }
  }

  void visitRef(Ref *node)
  {
    if (node->lexical)
    {
//    node->lexical->accept(this);
    }
    else if (node->nonTerminal)
    {
      node->nonTerminal->accept(*this);
    }
    else
    {
      internalerr();
    }
  }
};

class MarkWhitespaceAllowance : public Visitor
{                              typedef Visitor
                                 super;
public:
  void visitGrammar(Grammar *node)
  {
    if (node->whitespace)
    {
      section = NONTERMINALS;
      visitNodeList(node->nonTerminals);
    }
  }

  void visitProduction(Production *node)
  {
    if (! node->wsExplicit)
    {
      if (node->isStartSymbol() && node->firstElementChild)
      {
        node->firstElementChild->whitespaceAllowance = IMPLICIT;
      }
      super::visitProduction(node);
    }
  }

  void visitRef(Ref *node)
  {
    mark(node);
  }

  void visitString(String *node)
  {
    mark(node);
  }

private:
  void mark(Node *node)
  {
    for (Node *n = node; n != node->production; n = n->getParent())
    {
      if (   n->isOneOrMore()
          || n->isZeroOrMore()
          || n->isOptional())
      {
        node->whitespaceAllowance = IMPLICIT;
        break;
      }
      if (   n->precedingElementSibling
          && n->precedingElementSibling->followingElementSibling == n)
      {
        node->whitespaceAllowance = IMPLICIT;
        break;
      }
    }
  }
};

class VerifyNonEmpty : public Visitor
{                     typedef Visitor super;
public:
  void visitGrammar(Grammar *node)
  {
    section = NONTERMINALS;
    if (node->nonTerminals) visitNodeList(node->nonTerminals);
  }

  void visitZeroOrMore(ZeroOrMore *node)
  {
    super::visitZeroOrMore(node);
    verifyNonEmpty(node);
  }

  void visitOneOrMore(OneOrMore *node)
  {
    super::visitOneOrMore(node);
    verifyNonEmpty(node);
  }

  void visitOptional(Optional *node)
  {
    super::visitOptional(node);
    verifyNonEmpty(node);
  }

private:
  void verifyNonEmpty(NodeWithChildren *node)
  {
    if (node->firstElementChild == 0 || node->firstElementChild->first(1).contains(node->grammar->tokenSequenceFactory->emptySequence()))
    {
      WString msg(L"ambiguous: ");
      msg += node->isOptional() ? L"optional" : L"repeated";
      msg += L" sequence ";
      if (node->firstElementChild == 0 || (node->firstElementChild->isSequence() && ((Sequence *) node->firstElementChild)->firstElementChild == 0))
        msg += L"is";
      else
        msg += L"derives to";
      msg += L" empty in production ";
      throw Complaint(msg, node->production->name);
    }
  }
};

class PostProcess : public Visitor
{                  typedef Visitor super;
private:
  void assign(Production *production, Token::Code tokenCode)
  {
    production->tokenCode = tokenCode;
    grammar->terminalProductionByCode[tokenCode] = production;
  }

  class PopulateTables : public Visitor
  {                     typedef Visitor super;
  public:
    PopulateTables() : grammar(0) {}

    void visitGrammar(Grammar *node)
    {
      grammar = node;
      super::visitGrammar(node);
    }

    void visitProduction(Production *node)
    {
      ProductionTable *st = 0;
      switch (node->section)
      {
      case NONTERMINALS:
        st = &grammar->nonTerminalByName;
        break;
      case TERMINALS:
        st = &grammar->lexicalByName;
        break;
      default:
        st = &grammar->stringByName;
        break;
      }
      if (node->context == 0 && st->find(node->name) != st->end())
      {
        throw Complaint(L"duplicate definition: ", node->name);
      }
      st->insert(ProductionTable::value_type(node->name, node));
      if (section == NONTERMINALS && node->nonterminalCode < 0)
      {
        node->nonterminalCode = ++grammar->maxNonterminalCode;
        grammar->nonterminalProductionByCode[grammar->maxNonterminalCode] = node;
      }
      super::visitProduction(node);
    }

  private:
    Grammar *grammar;
  };

public:
  PostProcess(int maxLL, int maxLR) : grammar(0), errors(0), maxLL(maxLL), maxLR(maxLR) {}

  void visitGrammar(Grammar *node)
  {
    grammar = node;

    pt.visitGrammar(grammar);

    super::visitGrammar(grammar);

    if (errors)
    {
      grammar->accept(relink);
      throw Complaint();
    }

    // set up TERMINALS

    // assign whitespace token code

    if (   grammar->whitespace
        && grammar->whitespace->section == TERMINALS)
    {
      assign(grammar->whitespace, ++grammar->maxTokenCode);
    }

    // create production for implicit whitespace

    Production *implicitWs = new Production(TERMINALS, 0, wcsdup(L"%WS"));
    grammar->addChild(implicitWs);
    implicitWs->accept(pt);
    assign(implicitWs, Token::eWS);

    // create production for %OTHER token

    Production *other = new Production(TERMINALS, 0, wcsdup(L"%OTHER"));
    grammar->addChild(other);
    other->accept(pt);
    assign(other, Token::eOTHER);

    // accept string productions

    grammar->terminalByName.insert(grammar->stringByName.begin(), grammar->stringByName.end());

    for (Node *n = grammar->terminals; n; n = n->followingSibling)
    {
      if (n->isProduction())
      {
        Production *t = static_cast <Production *> (n);
/*
        if (t->tokenCode > -2)
        {
          if (grammar->terminalByName.find(t->name) != grammar->terminalByName.end())
          {
            throw Complaint(L"string/lexical name clash: ", t->name);
          }
        }
*/
        for (ProductionTable::iterator i = grammar->lexicalByName.find(t->name);
             i != grammar->lexicalByName.end() && wcscmp(t->name, (*i).first) == 0;
             ++i)
        {
          Production *p = (*i).second;
          if (p->tokenCode > -2)
          {
            if (p->tokenCode == -1)
            {
              assign(p, ++grammar->maxTokenCode);
            }
            grammar->terminalByName.insert(ProductionTable::value_type(p->name, p));
          }
        }
      }
    }

    for (ProductionTable::iterator i = grammar->terminalByName.begin();
         i != grammar->terminalByName.end();
         ++i)
    {
      if (i->second->tokenCode < 0)
      {
        assign(i->second, ++grammar->maxTokenCode);
      }
    }

    grammar->tokenSequenceFactory = new TokenSequenceFactory(grammar->maxTokenCode);
    grammar->tokenSequenceSets = new TokenSequenceSets(grammar->tokenSequenceFactory);

    grammar->emptySet = grammar->tokenSequenceSets->collect(new TokenSequenceSet(__FILE__, __LINE__));
    grammar->epsilon = grammar->tokenSequenceSets->collect(new TokenSequenceSet(grammar->tokenSequenceFactory->emptySequence(), __FILE__, __LINE__));
    grammar->cyclic = grammar->tokenSequence(Token::eCYCLIC);

    grammar->accept(relink);

    if (maxLR >= 0)
    {
      SetDistance sd;
      grammar->accept(sd);
    }

    Renumber renumber;
    grammar->accept(renumber);

    for (ProductionTable::iterator i = grammar->nonTerminalByName.begin();
         i != grammar->nonTerminalByName.end();
         ++i)
    {
      i->second->calculateUniqueRoot();
    }

    for (ProductionTable::iterator i = grammar->terminalByName.begin();
         i != grammar->terminalByName.end();
         ++i)
    {
      i->second->calculateUniqueRoot();
    }

    size_t nStartSymbols = 0;
    Production *startSymbol = 0;
    Production *firstNonWhitespace = 0;
    MarkReachable markReachable;

    for (Node *n = grammar->nonTerminals; n; n = n->followingSibling)
    {
      Production *p = static_cast <Production *> (n);
      if (p != grammar->whitespace)
      {
        if (firstNonWhitespace == 0)
        {
          firstNonWhitespace = p;
        }

        if (p->references.empty())
        {
          ++nStartSymbols;
          p->startSym = true;
          p->accept(markReachable);

          if (startSymbol == 0)
          {
            startSymbol = p;
          }
          else if (! grammar->quiet)
          {
            if (nStartSymbols == 2)
            {
              printf("start symbol: %ls\n", startSymbol->name);
            }
            printf("start symbol: %ls\n", p->name);
          }
        }
      }
    }

    if (startSymbol == 0)
    {
      if (firstNonWhitespace != 0)
      {
        startSymbol = firstNonWhitespace;
        startSymbol->startSym = true;
        startSymbol->accept(markReachable);

        printf("start symbol: %ls\n", startSymbol->name);
      }
      else
      {
        throw Complaint(L"could not identify start symbol", L"");
      }
    }

    if (node->whitespace && node->whitespace->section != TERMINALS)
    {
//    node->whitespace->accept(markReachable);
    }

    if (maxLL)
    {
      Production *leftRecursiveProduction = 0;
      for (Node *n = grammar->nonTerminals; n; n = n->followingSibling)
      {
        Production *p = static_cast <Production *> (n);
        if (p->isLeftRecursive())
        {
          if (leftRecursiveProduction)
          {
            printf("left-recursive production: %ls\n", leftRecursiveProduction->name);
          }
          leftRecursiveProduction = p;
        }
      }

      if (leftRecursiveProduction)
      {
        throw Complaint(L"left-recursive production: ", leftRecursiveProduction->name);
      }
    }

    MarkWhitespaceAllowance mw;
    grammar->accept(mw);

    VerifyNonEmpty vne;
    grammar->accept(vne);
  }

  void visitProduction(Production *node)
  {
    if (section == NONTERMINALS)
    {
      super::visitProduction(node);
    }
  }

  void visitEquivalence(Equivalence *node)
  {
  }

  void visitString(String *node)
  {
    for (ProductionTable::iterator i = grammar->stringByName.find(node->value);
          ;
          ++i)
    {
      if (i == grammar->stringByName.end() || wcscmp(node->value, (*i).first) != 0)
      {
        const wchar_t *context = node->context;
        node->lexical = new Production(AUTOMATIC, 0, wcsdup(node->value), context ? wcsdup(context) : 0);
        node->lexical->constant = true;
        grammar->addChild(node->lexical);
        node->lexical->accept(pt);
        node->lexical->addChild(new String(wcsdup(node->value)));
        break;
      }
      else
      {
        Production *p = (*i).second;
        if (    p->context == node->context
            || (p->context && node->context && wcscmp(p->context, node->context) == 0))
        {
          node->lexical = (*i).second;
          break;
        }
      }
    }
    if (section == NONTERMINALS)
    {
      node->lexical->references.insert(node);
    }
  }

  void visitRef(Ref *node)
  {
    if (section == NONTERMINALS && node->context == 0)
    {
      ProductionTable::iterator i = grammar->nonTerminalByName.find(node->name);
      if (i != grammar->nonTerminalByName.end())
      {
        node->nonTerminal = (*i).second;
        node->nonTerminal->references.insert(node);

        if (node->nonTerminal->nonterminalCode < 0)
        {
          node->nonTerminal->nonterminalCode = ++grammar->maxNonterminalCode;
          grammar->nonterminalProductionByCode[grammar->maxNonterminalCode] = node->lexical;
        }
      }
    }

    if (node->nonTerminal == 0)
    {
      ProductionTable::iterator i = grammar->lexicalByName.find(node->name);
      if (i == grammar->lexicalByName.end())
      {
        if (! grammar->noLexer)
        {
          ++errors;
          printf("undefined symbol: %ls\n", node->name);
        }
        node->lexical = new Production(AUTOMATIC, false, wcsdup(node->name), node->context ? wcsdup(node->context) : 0);
        grammar->addChild(node->lexical);
        grammar->lexicalByName.insert(ProductionTable::value_type(node->name, node->lexical));
        node->lexical->accept(pt);
      }
      else
      {
        for (Production *generic = 0; ; ++i)
        {
          if (i == grammar->lexicalByName.end() || wcscmp(i->first, node->name) != 0)
          {
            const wchar_t *context = node->context;
            node->lexical = new Production(TERMINALS, generic->nonGreedy, wcsdup(node->name), context ? wcsdup(context) : 0);
            grammar->addChild(node->lexical);
            node->lexical->accept(pt);

            Ref *genericRef = new Ref(wcsdup(node->name));
            genericRef->lexical = generic;
            node->lexical->addChild(genericRef);
            break;
          }
          else
          {
            Production *p = (*i).second;
            if (p->context == 0)
            {
              generic = p;
            }

            if (    p->context == node->context
                || (p->context && node->context && wcscmp(p->context, node->context) == 0))
            {
              node->lexical = p;
              break;
            }
          }
        }
      }
      if (section == NONTERMINALS)
      {
        node->lexical->tokenCode = -1;
        node->lexical->references.insert(node);
      }
    }
  }

private:
  PopulateTables pt;
  Relink relink;

  Grammar *grammar;
  int errors;
  int maxLL;
  int maxLR;
};

#endif /* POSTPROCESS_HPP */
