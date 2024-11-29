/*
 * ItemSet.h
 *
 *  Created on: 28.07.2011
 *      Author: Gunther
 */

#ifndef ITEMSET_HPP
#define ITEMSET_HPP

#include "../common/CompressedMap.hpp"
#include "../common/WString.hpp"
#include "../common/Format.hpp"
#include "../common/Platforms.hpp"

#include <map>
#include "Grammar.hpp"

class Domino
{
public:
  Domino(Node *fromItem, Node *toItem)
  : fromItem(fromItem)
  , toItem(toItem)
  {}

  bool operator<(const Domino &rhs) const
  {
    const Domino &lhs(*this);

    int lf = lhs.fromItem->id;
    int rf = rhs.fromItem->id;
    if (lf < rf) return true;
    if (lf > rf) return false;
    int lt = lhs.toItem == 0 ? -1 : lhs.toItem->id;
    int rt = rhs.toItem == 0 ? -1 : rhs.toItem->id;
    return lt < rt;
  }

  WString toString() const
  {
    Format format;
    WString result;
    result.append(format.toString<wchar_t>(fromItem->id));
    if (toItem != 0)
    {
      result.append(L"-");
      result.append(format.toString<wchar_t>(toItem->id));
    }
    return result;
  }

  Node *fromItem;
  Node *toItem;
};

class Dominoes : public std::set<Domino, std::less<Domino>, Alloc<Domino> >
{               typedef std::set<Domino, std::less<Domino>, Alloc<Domino> >
                        super;
public:
  Dominoes()
  : super(std::less<Domino>(), Alloc<Domino>(__FILE__, __LINE__))
  {}

  WString toString() const
  {
    WString result;
    const wchar_t *delimiter = L"";
    for (const_iterator i = begin(); i != end(); ++i)
    {
      result.append(delimiter);
      delimiter = L" ";
      result.append(i->toString());
    }
    return result;
  }

  bool isEssential() const
  {
    bool isEssential = false;
    for (const_iterator i = begin(); i != end(); ++i)
    {
      Node *fromItem = i->fromItem;
      Node *toItem = i->toItem;
      if (! (fromItem->isNodeWithContext() && (toItem == 0 || toItem->isNodeWithContext())))
      {
        internalerr();
      }

      if (static_cast<NodeWithContext *>(fromItem)->reduceType == reduceByLookback)
      {
        if (toItem == 0)
          isEssential = true;
        else if (static_cast<NodeWithContext *>(toItem)->reduceType == reduceByLookback)
          isEssential = true;
      }
      else if (toItem != 0 && static_cast<NodeWithContext *>(toItem)->reduceType == reduceByLookback)
      {
        wchar_t s[128];
        swprintf(s, sizeof s/sizeof s[0], L"fromItem: %d, toItem %d, this %p\n", fromItem->id, toItem->id, this);
        throw Complaint(L"inconsistent reduce type, ", s);
      }
    }
    return isEssential;
  }
};

class DominoSetLess
{
public:
  bool operator()(const Dominoes *lhs, const Dominoes *rhs) const
  {
    return *lhs < *rhs;
  }
};

typedef std::pair<Dominoes *, Dominoes *> DominoesPair;

class DominoesPairLess
{
public:
  bool operator()(const DominoesPair &lhs, const DominoesPair &rhs) const
  {
    if (*lhs.first < *rhs.first) return true;
    if (*lhs.first > *rhs.first) return false;
    return *lhs.second < *rhs.second;
  }
};

class DominoSets : public std::map<Dominoes *, int, DominoSetLess, Alloc<std::pair<const Dominoes *, int> > >
{                 typedef std::map<Dominoes *, int, DominoSetLess, Alloc<std::pair<const Dominoes *, int> > >
                          super;
public:
  DominoSets()
  : super(DominoSetLess(), Alloc<Dominoes *>(__FILE__, __LINE__))
  {}

  ~DominoSets()
  {}

  void deleteSets()
  {
    for (iterator i = begin(); i != end(); ++i)
    {
      Dominoes* const j = i->first;
      delete j;
    }
  }

  int getId(const Dominoes *dominoes) const
  {
    const_iterator i = find(const_cast<Dominoes *>(dominoes));
    if (i == end())
    {
      internalerr();
    }
    int id = i->second;
    if (id == 0)
    {
      internalerr();
    }
    return id;
  }

  int getLookbackCode(const Dominoes *dominoes, Reduce *reduceItem, int offset) const
  {
    int count = reduceItem->getDistance();
    if (count >= 0)
    {
      return (Math::max(0, count  - offset) << 1) + 1;
    }
    else
    {
      if (dominoes->size() != 1)
      {
        internalerr();
      }
      return getId(dominoes) << 1;
    }
  }
};

class ItemSet : private std::map<Node *, const TokenSequenceSetAccessor *, NodeIdLess, Alloc<std::pair<const Node *, const TokenSequenceSetAccessor *> > >
{               typedef std::map<Node *, const TokenSequenceSetAccessor *, NodeIdLess, Alloc<std::pair<const Node *, const TokenSequenceSetAccessor *> > >
                        super;
                typedef super::value_type
                        value_type;
public:
  ItemSet(const char *file = __FILE__, size_t line = __LINE__)
  : super(NodeIdLess(), Alloc<std::pair<const Node *, const TokenSequenceSetAccessor *> >(file, line))
  {}

  typedef super::const_iterator const_iterator;
  const_iterator begin() const {return super::begin();}
  const_iterator end() const {return super::end();}
  const_iterator find(Node *position) const {return super::find(position);}

  bool contains(Node *position) const {return find(position) != end();}

  typedef super::iterator iterator;
  iterator begin() {return super::begin();}
  iterator end() {return super::end();}
  iterator find(Node *position) {return super::find(position);}

  size_t size() const {return super::size();}
  bool empty() const {return super::empty();}
  void clear() {super::clear();}

  bool operator<(const ItemSet &rhs) const {return *(super *) this < *(super *) &rhs;}

  bool addActionItems(Node *item, const TokenSequenceSetAccessor *lookahead);

  bool addItem(Node *item, const TokenSequenceSetAccessor *lookahead)
  {
    iterator found = find(item);
    if (found == end())
    {
      insert(value_type(item, lookahead));
      return true;
    }
    else
    {
      const TokenSequenceSetAccessor* mergedLookahead = item->grammar->tokenSequenceSets->setUnion(found->second, lookahead);
      if (found->second != mergedLookahead)
      {
        found->second = mergedLookahead;
        return true;
      }
      else
      {
        return false;
      }
    }
  }
};

class ActionItemProcessor : protected Visitor
{
public:
  void processActionItems(Node *node)
  {
    if (node->isReduce())
    {
      processItem(node);
    }
    else
    {
      node->accept(*this);
    }
  }

protected:
  virtual void processItem(Node *node) = 0;

private:
  void processShiftItems(Node *node)
  {
    for (Node *parent; node; node = parent)
    {
      parent = node->getParent();
      if (node->followingActiveSibling())
      {
        node->followingActiveSibling()->accept(*this);
        break;
      }
      else if (node->reduceItem)
      {
        processItem(node->reduceItem);
        break;
      }
      else if (parent->isProduction())
      {
        if (parent->reduceItem)
        {
          internalerr();
        }
        break;
      }
      else if (parent->isZeroOrMore() || parent->isOneOrMore())
      {
        static_cast<NodeWithChildren *>(parent)->firstActiveChild()->accept(*this);
      }
    }
  }

  void visitProcessingInstruction(ProcessingInstruction *node)
  {
    if (node->reduceItem && node->reduceItem->isImplicit)
    {
      processItem(node);
    }
    else
    {
      processShiftItems(node);
    }
  }

  void visitProduction(Production *node)
  {
    processChildItem(node);
  }

  void visitNode(Node *node)
  {
    fwprintf(stderr, L"unsupported node type: %s", node->getNodeType());
    fflush(stderr);
    internalerr();
  }

  void visitSequence(Sequence *node)
  {
    processChildItem(node);
  }

  void visitString(String *node)
  {
    processItem(node);
  }

  void visitRef(Ref *node)
  {
    processItem(node);
  }

  void visitOptional(Optional *node)
  {
    processChildItem(node);
    processShiftItems(node);
  }

  void visitOneOrMore(OneOrMore *node)
  {
    processChildItem(node);
  }

  void visitZeroOrMore(ZeroOrMore *node)
  {
    processChildItem(node);
    processShiftItems(node);
  }

  void processChildItem(NodeWithChildren *node)
  {
    if (node->firstActiveChild())
      node->firstActiveChild()->accept(*this);
    else if (node->isProduction())
      processItem(node->reduceItem);
    else
      processShiftItems(node);
  }
};

class ActionItemCollector : public ActionItemProcessor
{
protected:
  void processItem(Node *node) {actionItems.insert(node);}

public:
  NodeSet actionItems;
};

class Close : private ActionItemProcessor
{             typedef ActionItemProcessor
                      super;
public:
  Close(TokenSequenceSets *tokenSequenceSets, ItemSet &shiftItems, ItemSet &reduceItems, size_t k)
  : tokenSequenceSets(tokenSequenceSets)
  , k(k)
  , shiftItems(shiftItems)
  , reduceItems(reduceItems)
  , lookahead(0)
  {}

  void process(Node *position, const TokenSequenceSetAccessor *aLookahead)
  {
    lookahead = aLookahead;
    super::processActionItems(position);
  }

  void wrapUp()
  {
    while (! unprocessedItems.empty())
    {
      Node *position = unprocessedItems.front();
      unprocessedItems.pop_front();

      process(position, productionItems.find(position)->second);
    }
  }

private:
  void processItem(Node *node)
  {
    if (node->isReduce())
    {
      reduceItems.addItem(node, lookahead);
    }
    else
    {
      shiftItems.addItem(node, lookahead);

      if (node->reduceItem && node->reduceItem->isImplicit)
      {
        if (! node->reduceItem->isReduce())
        {
          internalerr();
        }
        reduceItems.addItem(node->reduceItem, &node->follow(k, *lookahead));
      }
      else if (node->isRef())
      {
        Ref *ref = static_cast<Ref *>(node);
        if (ref->lexical == 0)
        {
          const TokenSequenceSetAccessor *follow = k == 0 ? ref->grammar->emptySet : &ref->follow(k, *lookahead);
          ItemSet::iterator found = productionItems.find(ref->nonTerminal);
          if (found == productionItems.end())
          {
            productionItems.addItem(ref->nonTerminal, follow);
            unprocessedItems.push_back(ref->nonTerminal);
          }
          else
          {
            const TokenSequenceSet *intersection = tokenSequenceSets->setIntersection(found->second, follow);
            if (intersection != follow->get())
            {
              // actually only need to insert (followers - intersection)
              found->second = tokenSequenceSets->setUnion(found->second, follow);
              // think of pushing an item rather than a node, where the item contains only (followers - intersection)
              unprocessedItems.push_back(ref->nonTerminal);
            }
          }
        }
      }
    }
  }

  NodeQueue unprocessedItems;
  ItemSet productionItems;

  TokenSequenceSets *tokenSequenceSets;
  size_t k;
  ItemSet &shiftItems;
  ItemSet &reduceItems;

  const TokenSequenceSetAccessor *lookahead;
};

class ItemSetLess
{
public:
  bool operator()(const ItemSet *lhs, const ItemSet *rhs) const
  {
    ItemSet::const_iterator li = lhs->begin();
    ItemSet::const_iterator ri = rhs->begin();
    ItemSet::const_iterator lend = lhs->end();
    ItemSet::const_iterator rend = rhs->end();
    while (li != lend && ri != rend)
    {
      if (li->first->id < ri->first->id) return true;
      if (ri->first->id < li->first->id) return false;
      ++li;
      ++ri;
    }
    return ri != rend;
  }
};

class KernelItemSetLess
{
public:
  KernelItemSetLess(bool lalr) : lalr(lalr) {}

  bool operator()(const ItemSet *lhs, const ItemSet *rhs) const
  {
    if (lalr)
    {
      size_t lSize = lhs->size();
      size_t rSize = rhs->size();
      if (lSize < rSize) return false;
      if (rSize < lSize) return true;
      ItemSet::const_iterator li = lhs->begin();
      ItemSet::const_iterator ri = rhs->begin();
      ItemSet::const_iterator lend = lhs->end();
      while (li != lend)
      {
        if (li->first < ri->first) return true;
        if (ri->first < li->first) return false;
        ++li;
        ++ri;
      }
      return false;
    }
    else
    {
      return *lhs < *rhs;
    }
  }

  bool merge(TokenSequenceSets *tokenSequenceSets, ItemSet *oldKernel, const ItemSet *newKernel) const
  {
    bool changed = false;
    if (lalr)
    {
      for (ItemSet::iterator j = oldKernel->begin(); j != oldKernel->end(); ++j)
      {
        const TokenSequenceSetAccessor* newLookahead = newKernel->find(j->first)->second;
        const TokenSequenceSet* mergedLookahead = tokenSequenceSets->setUnion(j->second, newLookahead);
        if (j->second != mergedLookahead)
        {
          j->second = mergedLookahead;
          changed = true;
        }
      }
    }
    return changed;
  }

private:
  const bool lalr;
};

class Transition
{
public:
  Transition(ItemSet *toState, Dominoes *dominoes)
  : toState(toState)
  , dominoes(dominoes)
  {}

  ItemSet *toState;
  Dominoes *dominoes;
};

class LrState
{
private:
  typedef std::map<Node *, Transition, NodeIdLess, Alloc<std::pair<const Node *, Transition> > > StateBySymbol;

public:
  LrState()
  : stateBySymbol(StateBySymbol::key_compare(), Alloc<std::pair<Node *, Transition> >(__FILE__, __LINE__))
  , id(-1)
  , lookahead(0)
  , compressedShiftMatch(0)
  , compressedConflictMatch(0)
  , defaultMatch(0)
  , conflictsK(0)
  , k(0)
  , isGotoState(false)
  , lr0ReduceItem(0)
  , compressedLookahead(0)
  , appendixOffsetByTokenSequence(0)
  , shiftLookahead(0)
  , changed(true)
  {}

  ~LrState()
  {
    delete compressedLookahead;
    delete appendixOffsetByTokenSequence;
    free(conflictsK);
  }

  typedef StateBySymbol::const_iterator const_iterator;
  typedef StateBySymbol::iterator iterator;

  void closure(const ItemSet *kernelItems, size_t k, TokenSequenceSets *tokenSequenceSets)
  {
    Close close(tokenSequenceSets, shiftItems, reduceItems, k);

    for (ItemSet::const_iterator i = kernelItems->begin(); i != kernelItems->end(); ++i)
    {
      Node *item = i->first;
      const TokenSequenceSetAccessor *lookahead = i->second;
      close.process(item, lookahead);
    }

    close.wrapUp();
  }

  void buildLookahead(Grammar *grammar, const size_t k);
  void buildAppendixes(Grammar *grammar);
  void publishActionCodes(Grammar *grammar);

  void buildTransitions(bool firstPass)
  {
    // process shift items

    for (ItemSet::const_iterator i = shiftItems.begin(); i != shiftItems.end(); ++i)
    {
      Node *fromItem = i->first;
      const TokenSequenceSetAccessor *itemLookahead = i->second;

      Node *symbol;
      if (fromItem->isString())
      {
        symbol = static_cast<String *>(fromItem)->lexical;
      }
      else if (fromItem->isRef())
      {
        Ref *ref = static_cast<Ref *>(fromItem);
        symbol = ref->lexical ? ref->lexical : ref->nonTerminal;
      }
      else if (fromItem->isProcessingInstruction())
      {
        symbol = fromItem->reduceItem;
      }
      else
      {
        internalerr();
      }

      for (Node *parent, *item = fromItem; item; item = parent)
      {
        parent = item->getParent();
        if (item->followingActiveSibling())
        {
          addTransition(fromItem, symbol, item->followingActiveSibling(), itemLookahead, firstPass);
          break;
        }
        else if (item->reduceItem && ! item->reduceItem->isImplicit)
        {
          addTransition(fromItem, symbol, item->reduceItem, itemLookahead, firstPass);
          break;
        }
        else if (parent->isZeroOrMore() || parent->isOneOrMore())
        {
          addTransition(fromItem, symbol, ((NodeWithChildren *) parent)->firstActiveChild(), itemLookahead, firstPass);
        }
        else if (parent->isProduction())
        {
          internalerr();
        }
      }
    }
  }

  const_iterator begin() const {return stateBySymbol.begin();}
  const_iterator end() const {return stateBySymbol.end();}

  iterator begin() {return stateBySymbol.begin();}
  iterator end() {return stateBySymbol.end();}

  const TokenSequenceSet *getConflicts(size_t k) const
  {
    if (! hasConflicts(k))
      return 0;
    return conflictsK[k - 1];
  }

  bool hasConflicts(size_t k) const
  {
    if (conflictsK == 0)
      return false;
    for (size_t i = 0; i < k; ++i)
      if (conflictsK[i] == 0)
        return false;
    return true;
  }

  bool hasGoto() const {return isGotoState;}
  bool isLr0ReduceState() const {return lr0ReduceItem != 0;}
  Reduce *getLr0ReduceItem() const {return lr0ReduceItem;}

  int getStateId() const {return id;}

  void setStateId(int id)
  {
    this->id = id;
    if (compressedLookahead) compressedLookahead->setDpiIfAbsent(id);
  }

  void collectConflictItems(TokenSequenceSets *tokenSequenceSets,
                            const TokenSequenceSet* conflictingTokenSequences,
                            size_t k,
                            ItemSet &conflictItems) const
  {
    const ItemSet *itemSets[] = {&reduceItems, &shiftItems, 0};
    for (const ItemSet **i = itemSets; *i; ++i)
    {
      const ItemSet *itemSet = *i;
      for (ItemSet::const_iterator i = itemSet->begin(); i != itemSet->end(); ++i)
      {
        Node* item = i->first;
        const TokenSequenceSetAccessor* itemLookahead = tokenSequenceSets->firstK(i->second, k);
        if (k != 0)
        {
          TokenSequenceSet itemConflictLookahead = item->isReduce()
              ? tokenSequenceSets->setIntersection(conflictingTokenSequences, tokenSequenceSets->firstK(itemLookahead->get(), k))
              : tokenSequenceSets->setIntersection(conflictingTokenSequences, &item->first(k, *itemLookahead->get()));
          if (! itemConflictLookahead.empty())
          {
            conflictItems.addItem(item, itemLookahead);
          }
        }
        else if (item->isReduce())
        {
          if (! shiftItems.empty() || reduceItems.size() > 1)
          {
            conflictItems.addItem(item, itemLookahead);
          }
        }
        else
        {
          if (! reduceItems.empty())
          {
            conflictItems.addItem(item, itemLookahead);
          }
        }
      }
    }
  }

  const TokenSequenceSet **getConflictsK() const {return conflictsK;}
  const TokenSequenceSet *getExpect() const {return lookahead;}
  size_t getK() const {return k;}

  const TokenSequenceSet *getDefaultMatch() const {return defaultMatch;}

  const TokenSequenceSet *getInitials() const {return compressedLookahead == 0 ? 0 : &compressedLookahead->getInitials();}

private:
  void addTransition(Node *fromItem, Node *symbol, Node *toItem, const TokenSequenceSetAccessor *lookahead, bool firstPass);
  void publishMatchCodes(Grammar *grammar);
  int shiftEntry(Grammar *grammar, const TokenSequence &ts);
  int reduceEntry(Grammar *grammar, Reduce *reduceItem);

  static int reduceCode(Reduce *reduceItem)
  {
    return reduceItem->grammar->distinctCodeAnnotations.empty()
         ? reduceItem->nonterminalCode
         : reduceItem->reduceCase;
  }

  int forkEntry(Grammar *grammar, int appendixOffset);
  const TokenSequenceSet *resolve(Grammar *grammar,
                                  const TokenSequenceSet *conflicts,
                                  const size_t k);

  StateBySymbol stateBySymbol;
  int id;
  const TokenSequenceSet *lookahead;
  const TokenSequenceSet *compressedShiftMatch;
  const TokenSequenceSet *compressedConflictMatch;
  const TokenSequenceSet *defaultMatch;
  const TokenSequenceSet **conflictsK;
  size_t k;
  bool isGotoState;
  Reduce *lr0ReduceItem;
  CompressedTokenSet *compressedLookahead;
  typedef std::map<const TokenSequence, int> IntByTokenSequence;
  IntByTokenSequence *appendixOffsetByTokenSequence;

public:
  const TokenSequenceSet *shiftLookahead;
  ItemSet shiftItems;
  ItemSet reduceItems;
  bool changed;
};

typedef std::pair<int, int> AppendixEntry;

// map kernel items to transition set

class LrStates : private std::map<ItemSet *, LrState *, KernelItemSetLess, Alloc<std::pair<const ItemSet *, LrState *> > >
{                typedef std::map<ItemSet *, LrState *, KernelItemSetLess, Alloc<std::pair<const ItemSet *, LrState *> > >
                         super;
public:
  enum ActionType
  {
    ERROR = 0,
    SHIFT = 1,
    REDUCE = 2,
    REDUCE_LOOKBACK = 3,
    SHIFT_REDUCE = 4,
    SHIFT_REDUCE_LOOKBACK = 5,
    SHIFT_ACCEPT = 6,
    FORK = 7,
    actionBits = 3,
    actionMask = 7
  };

  typedef std::map<DominoesPair, Dominoes *, DominoesPairLess> Triples;
  typedef std::map<ItemSet *, const TokenSequenceSet *, ItemSetLess> Conflicts;

  LrStates (Grammar *grammar, bool lalr)
  : super(KernelItemSetLess(lalr), Alloc<std::pair<const ItemSet *, LrState *> >(__FILE__, __LINE__))
  , grammar(grammar)
  , tokenSequenceSets(grammar->tokenSequenceSets)
  , conflicts(0)
  , conflicting(0)
  , changed(true)
  , lookaheadStates(0)
  , gotoStates(0)
  , gotoTable(0)
  , tokenSet(0)
  , appendix(0)
  , appendixEnd(0)
  , appendixMax(0)
  , dominoBits(0)
  , complexLookaheadStates(0)
  , hasLookback(false)
  {}

  ~LrStates();

  typedef super::const_iterator const_iterator;
  const_iterator begin() const {return super::begin();}
  const_iterator end() const {return super::end();}
  size_t size() const {return super::size();}

  LrState *&operator[](ItemSet *state) {return super::operator[](state);}

  const Triples *getTriples() const {return &triples;}
  const DominoSets *getDominoSets() const {return &dominoSets;}
  const Conflicts *getConflicts() const {return conflicts;}
  size_t getConflictingStates() const {return conflicting;}

  void generate();
  void prepareTable();

  void clear()
  {
    for (/*typename*/ super::iterator i = super::begin(); i != super::end(); ++i)
    {
      delete i->first;
      delete i->second;
    }

    dominoSets.deleteSets();

    if (conflicts != 0)
    {
      for (Conflicts::const_iterator i = conflicts->begin(); i != conflicts->end(); ++i)
      {
        ItemSet *conflict = i->first;
        delete conflict;
      }
      delete conflicts;
      conflicts = 0;
    }

    super::clear();
  }

  void setChanged(LrState *lrState)
  {
    if (lrState != 0)
    {
      lrState->changed = true;
    }
    changed = true;
  }

  void setChanged(ItemSet *state)
  {
    iterator found = find(state);
    if (found != end())
    {
      LrState *toStateTransitions = found->second;
      setChanged(toStateTransitions);
    }
    else
    {
      changed = true;
    }
  }

  void setAction(const TokenSequence &ts, int stateId, int entry) const;
  void setGoto(int nonterminalCode, int stateId, int entry) const;
  int getGotoState(int nonterminalCode, int stateId) const;
  int entry(int action, int argument, int lookback);

  int appendixOffset(AppendixEntry pair);

private:
  Grammar *grammar;
  TokenSequenceSets *tokenSequenceSets;
  Triples triples;
  Conflicts *conflicts;
  size_t conflicting;
  bool changed;

public:
  DominoSets dominoSets;
  size_t lookaheadStates;
  size_t gotoStates;

  TiledMap2D *gotoTable;
  int *tokenSet;
  EntryListMap2D lookbackTable;

  std::map<AppendixEntry, int> appendixes;
  int *appendix;
  int appendixEnd;
  int appendixMax;

  int dominoBits;
  int complexLookaheadStates;
  bool hasLookback;
};

#endif
