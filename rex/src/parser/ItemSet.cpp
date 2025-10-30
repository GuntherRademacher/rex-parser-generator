/*
 * ItemSet.cpp
 *
 *  Created on: 28.07.2011
 *      Author: Gunther
 */

/*
 * TODO: - list passes over items
 *       - decide whether some can be done on kernel items
 *       - e.g. lookahead should be completely computable on kernel items
 *       - shift only is decidable by not having EPSILON in first sets
 *       - shift only consideration might prevent invocation of upsize
 *
 * Why are there two separate ItemSets per state for shift and reduce items?
 *
 * Why do we keep closed ItemSets, rather than just kernels? What does it cost to do so?
 *
 */

#include "../common/Memory.hpp"
#include "ItemSet.hpp"
#include "PredictionBuilder.hpp"
#include "LookaheadCompressor.hpp"
#include "PrintEbnf.hpp"
#include <vector>

bool ItemSet::addActionItems(Node *item, const TokenSequenceSetAccessor *lookahead)
{
  ActionItemCollector collector;
  collector.processActionItems(item);
  bool hasChanged = false;
  for (NodeSet::iterator i = collector.actionItems.begin(); i != collector.actionItems.end(); ++i)
  {
    if (addItem(*i, lookahead))
      hasChanged = true;
  }
  return hasChanged;
}

void LrState::buildLookahead(Grammar *grammar, const size_t k)
{
  if (reduceItems.size() == 1 && shiftItems.empty())
  {
    lr0ReduceItem = static_cast<Reduce *>(reduceItems.begin()->first);
  }
  else
  {
    TokenSequenceSets *tokenSequenceSets = grammar->tokenSequenceSets;

    // process shift items

    shiftLookahead = grammar->emptySet;
    bool shiftOnly = reduceItems.empty();

    for (ItemSet::const_iterator i = shiftItems.begin(); i != shiftItems.end(); ++i)
    {
      Node *fromItem = i->first;
      const TokenSequenceSetAccessor *itemLookahead = i->second;

      if (! fromItem->isTerminalShift())
      {
        isGotoState = true;
      }
      else if (k <= 1 || shiftOnly)
      {
        shiftLookahead = tokenSequenceSets->setUnion(shiftLookahead, &fromItem->first(1));
      }
      else
      {
        shiftLookahead = tokenSequenceSets->setUnion(shiftLookahead, &fromItem->first(k, *itemLookahead));
      }

      if (fromItem->whitespaceAllowance == IMPLICIT)
      {
        TokenSequenceSet tss(grammar->tokenSequence(Token::eWS));
        shiftLookahead = tokenSequenceSets->setUnion(shiftLookahead, tokenSequenceSets->resolve(&tss));
      }
    }

    if (shiftOnly)
    {
      lookahead = shiftLookahead;
      this->k = 0;
    }
    else if (k == 0)
    {
      this->k = reduceItems.size() > 1 || ! shiftItems.empty()
              ? 1
              : 0;
    }
    else
    {
      this->k = k;
      for (size_t i = 1; i <= k; ++i)
      {
        const TokenSequenceSet *conflicts = grammar->emptySet;
        const TokenSequenceSet *shiftLookaheadI = i == k ? shiftLookahead : tokenSequenceSets->firstK(shiftLookahead, i);
        lookahead = shiftLookaheadI;

        // process reduce items

        for (ItemSet::iterator j = reduceItems.begin(); j != reduceItems.end(); ++j)
        {
          const TokenSequenceSet *itemLookaheadI = i == k ? j->second->get() : tokenSequenceSets->firstK(j->second, i);
          const TokenSequenceSet *itemConflictsI = tokenSequenceSets->setIntersection(lookahead, itemLookaheadI);
          lookahead = tokenSequenceSets->setUnion(lookahead, itemLookaheadI);
          conflicts = tokenSequenceSets->setUnion(conflicts, itemConflictsI);
        }

        conflicts = tokenSequenceSets->eraseIfEndsWith(conflicts, Token::eWS);

        if (! conflicts->empty())
        {
          conflicts = resolve(grammar, conflicts, i);
        }

        if (conflicts->empty())
        {
          this->k = i;
          break;
        }

        conflictsK = REALLOCATE_ARRAY(const TokenSequenceSet *, conflictsK, i + 1);
        conflictsK[i - 1] = conflicts;
        conflictsK[i] = 0;
      }
    }

    if (hasConflicts(this->k))
    {
      while (this->k > 1)
      {
        // downgrade to k-1, if k-sized lookahead does not resolve any conflicts.
        // if resolves conflicts, if (lookahead - conflicts(k)), downsized to k-1, contains any token sequence in conflicts(k-1)

        const TokenSequenceSet *nonConflictingLookahead = grammar->tokenSequenceSets->setDifference(lookahead, getConflicts(this->k));
        nonConflictingLookahead = grammar->tokenSequenceSets->eraseIfEndsWith(nonConflictingLookahead, Token::eWS);

#define SHOWSETS 0
#if SHOWSETS
        fprintf(stderr, "state %d(%p), k %d, nonConflictingLookahead(%p): %ls\n", id, this, k, nonConflictingLookahead, nonConflictingLookahead->toString(grammar, L"", L" |", 32767, 0, false).c_str());
#endif

        const TokenSequenceSet *downSizedNonConflictingLookahead = grammar->tokenSequenceSets->firstK(nonConflictingLookahead, this->k - 1);
        if (! grammar->tokenSequenceSets->setIntersection(downSizedNonConflictingLookahead, getConflicts(this-> k - 1))->empty())
          break;

        this->k -= 1;

#if SHOWSETS
        fprintf(stderr, "state %d(%p), downgrading t0 k %d\n", id, this, k);
#endif

        conflictsK[this->k] = 0;
        lookahead = grammar->tokenSequenceSets->firstK(lookahead, this->k);
        shiftLookahead = grammar->tokenSequenceSets->firstK(shiftLookahead, this->k);
        for (ItemSet::iterator j = reduceItems.begin(); j != reduceItems.end(); ++j)
        {
          j->second = grammar->tokenSequenceSets->firstK(j->second, this->k);
        }
      }
      compressedConflictMatch =
        CompressedTokenSet::compressMatch(conflictsK, getConflicts(this->k), grammar->tokenSequenceFactory, grammar->tokenSequenceSets);
    }

    compressedLookahead = new CompressedTokenSet();
    compressedLookahead->populate(lookahead,
                                  grammar->whitespaceIntroducers,
                                  conflictsK,
                                  false,
                                  grammar->tokenSequenceFactory,
                                  grammar->lookaheadSets);

    compressedShiftMatch = shiftItems.empty()
                         ? 0
                         : CompressedTokenSet::compressMatch(conflictsK, shiftLookahead, grammar->tokenSequenceFactory, tokenSequenceSets);
    defaultMatch = compressedShiftMatch;

    for (ItemSet::const_iterator j = reduceItems.begin(); j != reduceItems.end(); ++j)
    {
      const TokenSequenceSetAccessor *itemLookahead = this->k == k ? j->second : tokenSequenceSets->firstK(j->second, this->k);
      const TokenSequenceSet *itemMatch = CompressedTokenSet::compressMatch(conflictsK, itemLookahead->get(), grammar->tokenSequenceFactory, tokenSequenceSets);
      if (defaultMatch == 0 || defaultMatch->size() < itemMatch->size())
        defaultMatch = itemMatch;
    }

    grammar->decisionPoints.insert(DecisionPoints::key_type(k, compressedLookahead, (int) grammar->decisionPoints.size()));

    publishMatchCodes(grammar);
  }
}

const TokenSequenceSet *LrState::resolve(Grammar *grammar,
                                         const TokenSequenceSet *conflicts,
                                         const size_t k)
{
  TokenSequenceSets *tokenSequenceSets = grammar->tokenSequenceSets;
  PrintEbnf pe(PrintEbnf::ACTIVE);

  ItemSet conflictItems;
  collectConflictItems(tokenSequenceSets, conflicts, k, conflictItems);

  RestrictionsByProduction restrictionsByProduction;

  TokenSequenceSet resolved;
  for (TokenSequenceSet::const_iterator i = conflicts->begin(); i != conflicts->end(); ++i)
  {
    const TokenSequence lookahead = *i;

    bool resolveByLookback = true;
    bool hasLookback = false;

    bool resolveByRestriction = true;
    Node *orderedChoice = 0;
    NodeMap resolution;

    for (ItemSet::iterator j = conflictItems.begin(); j != conflictItems.end(); ++j)
    {
      Node *item = j->first;
      if ((item->isTerminalShift() && item->first(k, *j->second).contains(lookahead))
       || (item->isReduce() && j->second->get()->contains(lookahead)))
      {
        if (resolveByLookback)
        {
          if (! item->isReduce())
          {
            resolveByLookback = false;
          }
          else
          {
            Reduce *reduceItem = static_cast<Reduce *>(item);
            hasLookback = hasLookback || reduceItem->getDistance() == VARIABLE;
            for (ItemSet::iterator k = conflictItems.begin();  k != j; ++k)
            {
              if (k->second->get()->contains(lookahead))
              {
                Reduce *r = static_cast<Reduce *>(k->first);
                if (reduceItem->nonterminalCode != r->nonterminalCode
                 || reduceItem->restrictedCase != r->restrictedCase
                 || (reduceItem->processingInstruction != 0) != (r->processingInstruction != 0))
                {
                  resolveByLookback = false;
                  break;
                }
                else if (reduceItem->processingInstruction != 0
                      && 0 != wcscmp(reduceItem->processingInstruction->content, r->processingInstruction->content))
                {
                  resolveByLookback = false;
                  break;
                }
              }
            }
          }
        }

        if (resolveByRestriction)
        {
          NodeSet restrictions;
          item->collectRestrictedCaseNodes(&shiftItems, restrictions, restrictionsByProduction);

          if (restrictions.size() != 1 || *restrictions.begin() == 0)
          {
            resolveByRestriction = false;
          }
          else
          {
            Node* const restrictedCase = *restrictions.begin();
            if (orderedChoice == 0)
            {
              orderedChoice = restrictedCase->getParent();
            }
            else if (orderedChoice != restrictedCase->getParent())
            {
              resolveByRestriction = false;
            }

            if (! resolution.insert(NodeMap::value_type(restrictedCase, item)).second)
            {
              resolveByRestriction = false;
            }
          }
        }
      }
    }

    if (resolveByLookback)
    {
      if (! hasLookback)
      {
        internalerr();
      }
      for (ItemSet::iterator j = conflictItems.begin(); j != conflictItems.end(); ++j)
      {
        if (j->second->get()->contains(lookahead))
        {
          Reduce *item = static_cast<Reduce *>(j->first);
          if (item->getDistance() != VARIABLE)
          {
            ItemSet::iterator actualItem = reduceItems.find(item);
            if (actualItem == reduceItems.end())
            {
              printf("failed to find this %ls item(%p):\n%ls\n", j->first->getNodeType(), item, pe.itemToString(item).c_str());
              printf("reduce items are:\n");
              int i = 0;
              for (ItemSet::iterator r = reduceItems.begin(); r != reduceItems.end(); ++r)
              {
                printf("  %ls item #%d:\n%ls\n", r->first->getNodeType(), i++, pe.itemToString(r->first).c_str());
              }

              internalerr();
            }
            const TokenSequenceSet *actualLookahead = actualItem->second->get();
            TokenSequenceSet *reducedLookahead = new TokenSequenceSet();
            for (TokenSequenceSet::const_iterator l = actualLookahead->begin(); l != actualLookahead->end(); ++l)
            {
              if (! (l->first(k) == lookahead))
              {
                reducedLookahead->insert(*l);
              }
            }
            actualItem->second = tokenSequenceSets->collect(reducedLookahead);
          }
        }
      }
      resolved.insert(lookahead);
    }
    else if (resolveByRestriction)
    {
      if (resolution.size() < 2)
      {
        internalerr();
      }
      TokenSequenceSet lookaheadAsSet(lookahead, __FILE__, __LINE__);
      for (NodeMap::const_iterator j = resolution.begin(); ++j != resolution.end(); )
      {
        Node *item = j->second;
        ItemSet &itemSet = item->isReduce() ? reduceItems : shiftItems;
        ItemSet::iterator actualItem = itemSet.find(item);
        if (actualItem == itemSet.end())
        {
          internalerr();
        }

        if (actualItem->first->isReduce())
        {
          const TokenSequenceSet *actualLookahead = actualItem->second->get();
          TokenSequenceSet *reducedLookahead = new TokenSequenceSet();
          for (TokenSequenceSet::const_iterator l = actualLookahead->begin(); l != actualLookahead->end(); ++l)
          {
            if (! (l->first(k) == lookahead))
            {
              reducedLookahead->insert(*l);
            }
          }
          actualItem->second = tokenSequenceSets->collect(reducedLookahead);
        }
        else
        {
          const TokenSequenceSet *actualLookahead = shiftLookahead;
          TokenSequenceSet *reducedLookahead = new TokenSequenceSet();
          for (TokenSequenceSet::const_iterator l = actualLookahead->begin(); l != actualLookahead->end(); ++l)
          {
            if (! (l->first(k) == lookahead))
            {
              reducedLookahead->insert(*l);
            }
          }
          shiftLookahead = tokenSequenceSets->collect(reducedLookahead);
        }
      }
      resolved.insert(lookahead);
    }
  }
  conflicts = tokenSequenceSets->setDifference(conflicts, &resolved);
  return conflicts;
}

void LrState::addTransition(Node *fromItem,
                            Node *symbol,
                            Node *toItem,
                            const TokenSequenceSetAccessor *lookahead,
                            bool firstPass)
{
  if (toItem == 0)
  {
    internalerr();
  }

  iterator found = stateBySymbol.insert(StateBySymbol::value_type(symbol, Transition(0, 0))).first;
  Transition &transition = found->second;
  if (transition.toState == 0)
  {
    transition = Transition(new ItemSet(), new Dominoes());
  }

  ItemSet *toState = transition.toState;
  if (toState->addActionItems(toItem, lookahead))
  {
    fromItem->grammar->states->setChanged(toState);
  }

  if (firstPass)
  {
    transition.dominoes->insert(Domino(fromItem, toItem));
  }
}

void LrState::publishMatchCodes(Grammar *grammar)
{
  /* defaultMatch entries need not be published, because they will
   * be downgraded to k=1, and all tokenCodes are matchCodes anyway
   */

  if (compressedShiftMatch != 0 && compressedShiftMatch != defaultMatch)
  {
    grammar->matchCode.add(compressedShiftMatch, grammar->tokenSequenceFactory);
  }

  for (ItemSet::const_iterator j = reduceItems.begin(); j != reduceItems.end(); ++j)
  {
    const TokenSequenceSet *itemLookahead = grammar->tokenSequenceSets->firstK(j->second, this->k);
    const TokenSequenceSet *itemMatch = CompressedTokenSet::compressMatch(conflictsK, itemLookahead, grammar->tokenSequenceFactory, grammar->tokenSequenceSets);
    if (itemMatch != defaultMatch)
    {
      grammar->matchCode.add(itemMatch, grammar->tokenSequenceFactory);
    }
  }
}

int LrState::shiftEntry(Grammar *grammar, const TokenSequence &ts)
{
  Production *symbol = grammar->terminalProductionByCode[ts.first()];
  StateBySymbol::const_iterator to = stateBySymbol.find(symbol);
  if (to == stateBySymbol.end())
  {
    printf("no target found for shift on %ls in state %d\n", symbol->name, id);
    internalerr();
  }

  const Transition &transition = to->second;
  ItemSet* toState = transition.toState;

  LrState* toStateTransitions = (*grammar->states)[toState];
  int targetStateId = toStateTransitions->getStateId();

  DominoSets &dominoSets = grammar->states->dominoSets;

  int entry;
  if (! toStateTransitions->isLr0ReduceState())
  {
    int lookback = dominoSets.getId(transition.dominoes);
//          if (log) printf("   add \"shift %d\" with lookback %d for matchCode %d (%ls) and source state %d\n", targetStateId, lookback, code, ts.toString(grammar).c_str(), sourceStateId);
    entry = grammar->states->entry(LrStates::SHIFT, targetStateId, lookback);
  }
  else
  {
    Reduce* reduceItem = toStateTransitions->getLr0ReduceItem();
    int lookback = dominoSets.getLookbackCode(transition.dominoes, reduceItem, 1);
//    Production* nonterminal = reduceItem->production;
//          if (log) printf("   add \"shift+reduce %ls\" with lookback %d for matchCode %d (%ls) and source state %d\n", nonterminal->name, lookback, code, ts.toString(grammar).c_str(), sourceStateId);
    LrStates::ActionType actionType = (lookback & 1) != 0 ? LrStates::SHIFT_REDUCE : LrStates::SHIFT_REDUCE_LOOKBACK;
    entry = grammar->states->entry(actionType, reduceCode(reduceItem), lookback >> 1);
  }
  return entry;
}

int LrState::reduceEntry(Grammar *grammar, Reduce *reduceItem)
{
  Dominoes dominoes;
  dominoes.insert(Domino(reduceItem, 0));
  int lookback = grammar->states->dominoSets.getLookbackCode(&dominoes, reduceItem, 0);
  int action = (lookback & 1) != 0
             ? LrStates::REDUCE
             : LrStates::REDUCE_LOOKBACK;
  return grammar->states->entry(action, reduceCode(reduceItem), lookback >> 1);
}

int LrState::forkEntry(Grammar *grammar, int appendixOffset)
{
  return grammar->states->entry(LrStates::FORK, appendixOffset, 0);
}

void LrState::buildAppendixes(Grammar *grammar)
{
  if (hasConflicts(k))
  {
    typedef std::set<int> IntSet;
    typedef std::map<TokenSequence, std::pair<IntSet, int> > IntSetByTokenSequence;
    IntSetByTokenSequence appendixByTokenSequence;

    if (compressedShiftMatch != 0)
    {
      for (TokenSequenceSet::const_iterator l = compressedShiftMatch->begin(); l != compressedShiftMatch->end(); ++l)
      {
        const TokenSequence &ts(*l);
        if (compressedConflictMatch->contains(ts))
        {
          int entry = shiftEntry(grammar, ts);
          appendixByTokenSequence[ts].first.insert(entry);

//          printf("state id %d, shift on %ls\n", id, ts.toString(grammar).c_str()); //(grammar, L"", L"~", 132, 0, false, 0).c_str());
        }
      }
    }

    for (ItemSet::const_iterator j = reduceItems.begin(); j != reduceItems.end(); ++j)
    {
      Reduce *reduceItem = static_cast<Reduce *>(j->first);
      int entry = reduceEntry(grammar, reduceItem);

      const TokenSequenceSet *itemLookahead = grammar->tokenSequenceSets->firstK(j->second, this->k);
      const TokenSequenceSet *compressedItemMatch =
        CompressedTokenSet::compressMatch(conflictsK, itemLookahead, grammar->tokenSequenceFactory, grammar->tokenSequenceSets);

      for (TokenSequenceSet::const_iterator l = compressedItemMatch->begin(); l != compressedItemMatch->end(); ++l)
      {
        const TokenSequence &ts(*l);
        if (compressedConflictMatch->contains(ts))
        {
          appendixByTokenSequence[ts].first.insert(entry);

//          printf("state id %d, reduce on  %ls\n", id, ts.toString(grammar).c_str()); //(grammar, L"", L"~", 132, 0, false, 0).c_str());
        }
      }
    }

    TokenSequenceSet tokenSequences;
    for (IntSetByTokenSequence::const_iterator i = appendixByTokenSequence.begin(); i != appendixByTokenSequence.end(); ++i)
    {
      tokenSequences.insert(i->first);
    }

    if (tokenSequences.empty())
    {
      internalerr();
    }
    appendixOffsetByTokenSequence = new IntByTokenSequence();
    OrderedTokenSequenceVector orderedTokenSequences(tokenSequences);
    for (OrderedTokenSequenceVector::const_iterator i = orderedTokenSequences.begin(); i != orderedTokenSequences.end(); ++i)
    {
      const TokenSequence &ts = *i;
      IntSet appendix = appendixByTokenSequence[ts].first;

      int entry = 0;
      int offset = -1;
      for (IntSet::const_iterator j = appendix.begin(); j != appendix.end(); ++j)
      {
        if (entry == 0)
        {
          entry = *j;
        }
        else
        {
          offset = grammar->states->appendixOffset(AppendixEntry(entry, *j));
          entry = forkEntry(grammar, offset);
        }
      }
      appendixOffsetByTokenSequence->insert(IntByTokenSequence::value_type(ts, offset));
    }
  }
}

void LrState::publishActionCodes(Grammar *grammar)
{
  if (lr0ReduceItem == 0)
  {
//    const bool log = 0 != strstr(getenv("FLAGS"), "L");

    DominoSets &dominoSets = grammar->states->dominoSets;

    for (StateBySymbol::const_iterator i = stateBySymbol.begin(); i != stateBySymbol.end(); ++i)
    {
      Node *symbol = i->first;
      if (symbol->isReduce()
       || (symbol->isProduction() && static_cast<Production *>(symbol)->tokenCode < 0))
      {
        const Transition &transition = i->second;
        ItemSet* toState = transition.toState;
        LrState* toStateTransitions = (*grammar->states)[toState];

        int entry;
        if (! toStateTransitions->isLr0ReduceState())
        {
          int lookback = dominoSets.getId(transition.dominoes);
          int targetStateId = toStateTransitions->getStateId();

//          if (log)
//          {
//            if (symbol->isProduction())
//            {
//              Production *p = static_cast<Production *>(symbol);
//              printf("   add \"shift %d\" with lookback %d for nonterminal %d (%ls) and source state %d\n", targetStateId, lookback, p->nonterminalCode, p->name, id);
//            }
//            else
//            {
//              Reduce *r = static_cast<Reduce *>(symbol);
//              printf("   add \"shift %d\" with lookback %d for nonterminal %d (EMBEDDED-%d) and source state %d\n", targetStateId, lookback, r->nonterminalCode, r->nonterminalCode, id);
//            }
//          }

          entry = grammar->states->entry(LrStates::SHIFT, targetStateId, lookback);
        }
        else
        {
          Reduce* reduceItem = toStateTransitions->getLr0ReduceItem();
          int lookback = dominoSets.getLookbackCode(transition.dominoes, reduceItem, 1);

//          if (log)
//          {
//            Production* nonterminal = reduceItem->production;
//            if (symbol->isProduction())
//            {
//              Production *p = static_cast<Production *>(symbol);
//              printf("   add \"shift+reduce %ls\" with lookback %d for nonterminal %d (%ls) and source state %d\n", nonterminal->name, lookback, p->nonterminalCode, p->name, id);
//            }
//            else
//            {
//              Reduce *r = static_cast<Reduce *>(symbol);
//              printf("   add \"shift+reduce %ls\" with lookback %d for nonterminal %d (EMBEDDED-%d) and source state %d\n", nonterminal->name, lookback, r->nonterminalCode, r->nonterminalCode, id);
//            }
//          }

          LrStates::ActionType actionType = (lookback & 1) != 0 ? LrStates::SHIFT_REDUCE : LrStates::SHIFT_REDUCE_LOOKBACK;
          entry = grammar->states->entry(actionType, reduceCode(reduceItem), lookback >> 1);
        }
        int nonterminalCode = symbol->isProduction()
                            ? static_cast<Production *>(symbol)->nonterminalCode
                            : static_cast<Reduce *>(symbol)->nonterminalCode;
        grammar->states->setGoto(nonterminalCode, id, entry);
      }
    }

    /*
     * nonterminal shifts always go to #0
     *
     * If defaultMatch==compressedShiftMatch Then
     *    all reductions go to #0
     *    all k=1 terminal shifts go to #0
     *    downgraded (to k=1) terminal shifts go to #1
     * Else
     *    all terminal shifts go to #0
     *    non-default reductions go to #0
     *    k=1 default reductions go to #0
     *    downgraded (to k=1) reductions go to #1
     *
     * all #1 transitions must be downgraded to k=1 (for proper predict termination)
     */

#if SHOWSETS
      fprintf(stderr, "state %d(%p), k %d,            defaultMatch(%p): %ls\n", id, this, k, defaultMatch, defaultMatch->toString(grammar, L"", L" |", 32767, 0, false).c_str());
    if (compressedConflictMatch != 0)
      fprintf(stderr, "state %d(%p), k %d, compressedConflictMatch(%p): %ls\n", id, this, k, compressedConflictMatch, compressedConflictMatch->toString(grammar, L"", L" |", 32767, 0, false).c_str());
#endif

    if (compressedShiftMatch != 0)
    {
#if SHOWSETS
      fprintf(stderr, "state %d(%p), k %d,    compressedShiftMatch(%p): %ls\n", id, this, k, compressedShiftMatch, compressedShiftMatch->toString(grammar, L"", L" |", 32767, 0, false).c_str());
#endif

      if (compressedConflictMatch != 0)
      {
        for (TokenSequenceSet::const_iterator l = compressedShiftMatch->begin(); l != compressedShiftMatch->end(); ++l)
        {
          const TokenSequence &ts(*l);
          if (compressedConflictMatch->contains(ts))
          {
            IntByTokenSequence::iterator it = appendixOffsetByTokenSequence->find(ts);
            if (it == appendixOffsetByTokenSequence->end())
            {
              fprintf(stderr, "failed to find appendix offset for: %ls\n", ts.toString(grammar).c_str());
              internalerr();
            }
            int sourceStateId = compressedShiftMatch->contains(ts)
                              ? id
                              : id + 1;
            int entry = forkEntry(grammar, it->second);
            grammar->states->setAction(ts, sourceStateId, entry);
          }
        }
      }

      const TokenSequenceSet *match = compressedShiftMatch == defaultMatch && k > 1
                                    ? grammar->tokenSequenceSets->firstK(compressedShiftMatch, 1)
                                    : compressedShiftMatch;
      for (TokenSequenceSet::const_iterator l = match->begin(); l != match->end(); ++l)
      {
        const TokenSequence &ts(*l);
        if (compressedConflictMatch == 0 || ! compressedConflictMatch->contains(ts))
        {
          int sourceStateId = compressedShiftMatch->contains(ts)
                            ? id
                            : id + 1;
          int entry = shiftEntry(grammar, ts);
          grammar->states->setAction(ts, sourceStateId, entry);
        }
      }
    }

    for (ItemSet::const_iterator j = reduceItems.begin(); j != reduceItems.end(); ++j)
    {
      Reduce *reduceItem = static_cast<Reduce *>(j->first);
      int commonEntry = reduceEntry(grammar, reduceItem);

      const TokenSequenceSet *itemLookahead = grammar->tokenSequenceSets->firstK(j->second, this->k);
      const TokenSequenceSet *compressedItemMatch =
        CompressedTokenSet::compressMatch(conflictsK, itemLookahead, grammar->tokenSequenceFactory, grammar->tokenSequenceSets);

#if SHOWSETS
      fprintf(stderr, "state %d(%p), k %d,     compressedItemMatch(%p): %ls\n", id, this, k, compressedItemMatch, compressedItemMatch->toString(grammar, L"", L" |", 32767, 0, false).c_str());
#endif

      if (compressedConflictMatch != 0)
      {
        for (TokenSequenceSet::const_iterator l = compressedItemMatch->begin(); l != compressedItemMatch->end(); ++l)
        {
          const TokenSequence &ts(*l);
          if (compressedConflictMatch->contains(ts))
          {
            IntByTokenSequence::iterator it = appendixOffsetByTokenSequence->find(ts);
            if (it == appendixOffsetByTokenSequence->end())
            {
              fprintf(stderr, "failed to find appendix offset for: %ls\n", ts.toString(grammar).c_str());
              internalerr();
            }
            int entry = forkEntry(grammar, it->second);
            int sourceStateId = compressedItemMatch->contains(ts)
                              ? id
                              : id + 1;
            grammar->states->setAction(ts, sourceStateId, entry);
          }
        }
      }

      const TokenSequenceSet *match = compressedItemMatch == defaultMatch && k > 1
                                    ? grammar->tokenSequenceSets->firstK(compressedItemMatch, 1)
                                    : compressedItemMatch;
      for (TokenSequenceSet::const_iterator l = match->begin(); l != match->end(); ++l)
      {
        const TokenSequence &ts(*l);
        if (compressedConflictMatch == 0 || ! compressedConflictMatch->contains(ts))
        {
          int sourceStateId = compressedItemMatch->contains(ts)
                            ? id
                            : id + 1;
          grammar->states->setAction(ts, sourceStateId, commonEntry);
        }
      }
    }
  }
}

LrStates::~LrStates()
{
  clear();
  delete gotoTable;
  free(tokenSet);
  free(appendix);
}

void LrStates::generate()
{
  size_t maxK = grammar->maxK;

  TokenSequence end1(grammar->tokenSequence(Token::eOTHER));
  std::vector<ItemSet *> states;

  // k == 0 ?

  if (grammar->whitespace)
  {
    LookaheadCompressor::determineWhitespaceIntroducers(grammar);
  }

  for (size_t k = 1; k <= maxK; ++k)
  {
    for (size_t s = 0; s < states.size(); ++s)
    {
      ItemSet *state = states[s];
      LrState *transitions = (*this)[state];
      for (LrState::iterator i = transitions->begin(); i != transitions->end(); ++i)
      {
        Dominoes *dominoes = i->second.dominoes;
        delete dominoes;
      }
    }

    grammar->matchCode.clear();
    grammar->decisionPoints.clear();
    states.clear();
    this->clear();

    conflicting = 0;

    TokenSequence endK(grammar->tokenSequence(Token::eEPSILON));
    for (size_t i = 0; i < k; ++i)
    {
      endK = grammar->tokenSequenceFactory->tokenSequence(endK, end1);
    }
    const TokenSequenceSet *endLookahead = tokenSequenceSets->collect(new TokenSequenceSet(endK));

    // set up start states from start symbols

    for (Node *n = grammar->nonTerminals; n; n = n->followingSibling)
    {
      Production *p = static_cast <Production *> (n);
      if (p->isStartSymbol() || p == grammar->whitespace)
      {
        ItemSet *startState = new ItemSet();
        startState->addActionItems(p, endLookahead);
        (*this)[startState] = 0;
        states.push_back(startState);
        p->state = startState;
      }
    }

    for (changed = true; changed; )
    {
      changed = false;

      for (size_t s = 0; s < states.size(); ++s)
      {
        ItemSet *state = states[s];
        LrState *transitions = (*this)[state];

        bool firstPass = transitions == 0;
        if (firstPass)
        {
          transitions = new LrState();
          (*this)[state] = transitions;
        }

        if (transitions->changed)
        {
          transitions->changed = false;
          transitions->closure(state, k, tokenSequenceSets);
          transitions->buildTransitions(firstPass);

          if (firstPass)
          {
            for (LrState::iterator i = transitions->begin(); i != transitions->end(); ++i)
            {
              ItemSet *&target = i->second.toState;

              super::iterator found = find(target);
              if (found == end()) // first pass
              {
                insert(value_type(target, static_cast<LrState *>(0)));
                states.push_back(target);
              }
              else
              {
                ItemSet *knownState = found->first;
                if (knownState == target)
                {
                  internalerr();
                }

                if (super::key_comp().merge(tokenSequenceSets, knownState, target))
                {
                  setChanged(found->second);
                }

                delete target;
                target = knownState;
              }
            }
          }
        }
      }
    }

    conflicting = 0;
    grammar->k = 1;
    for (size_t s = 0; s < states.size(); ++s)
    {
      ItemSet *state = states[s];

      LrState *transitions = (*this)[state];
      transitions->buildLookahead(grammar, k);

      size_t stateK = transitions->getK();
      grammar->k = Math::max(grammar->k, stateK);

      if (transitions->hasConflicts(stateK))
      {
        ++conflicting;
        if (k < maxK)
          break;
      }
    }

    if (conflicting == 0)
    {
      break;
    }
  }

  // assign state ids

  size_t stateId = 0;

  // (1) complex lookahead states, reserve an extra state id for default processing

  for (size_t s = 0; s < states.size(); ++s)
  {
    LrState* transitions = (*this)[states[s]];
    if (transitions->getStateId() < 0 && transitions->getK() > 1)
    {
      transitions->setStateId(stateId++);
      stateId++;
    }
  }

  complexLookaheadStates = stateId;

  // (2) goto states

  for (size_t s = 0; s < states.size(); ++s)
  {
    LrState* transitions = (*this)[states[s]];
    if (transitions->getStateId() < 0 && transitions->hasGoto())
    {
      transitions->setStateId(stateId++);
    }
  }

  gotoStates = stateId;

  // (3) states that cause shifts or need lookahead for reduction

  for (size_t s = 0; s < states.size(); ++s)
  {
    LrState* transitions = (*this)[states[s]];
    if (transitions->getStateId() < 0 && ! transitions->isLr0ReduceState())
    {
      transitions->setStateId(stateId++);
    }
  }

  lookaheadStates = stateId;

  // (4) other states (LR(0) reduce states)

  for (size_t s = 0; s < states.size(); ++s)
  {
    LrState* transitions = (*this)[states[s]];
    if (transitions->getStateId() < 0)
    {
      transitions->setStateId(stateId++);
    }
  }

  // allocate tables

  const int compression = grammar->smaller ? 3 : grammar->faster ? 1 : 2;
  const int align = 8;

  gotoTable = new TiledMap2D(compression, align);
  gotoTable->setMaxIndex(grammar->maxNonterminalCode, gotoStates - 1);

//  printf("gotoTable.setMaxIndex %d %d\n", grammar->maxNonterminalCode - 1, gotoStates - 1);

  // wrap up
  conflicts = new Conflicts();

  grammar->renumber();

  PredictionBuilder pb(grammar);
  pb.build();

  for (size_t s = 0; s < states.size(); ++s)
  {
    ItemSet *state = states[s];

    LrState *transitions = (*this)[state];
    for (ItemSet::iterator i = transitions->reduceItems.begin(); i != transitions->reduceItems.end(); ++i)
    {
      Reduce* reduceItem = static_cast<Reduce *>(i->first);
      if (reduceItem->reduceType == reduceByLookback)
      {
        Dominoes *dominoes = new Dominoes();
        dominoes->insert(Domino(reduceItem, 0));
        if (! dominoSets.insert(DominoSets::value_type(dominoes, 0)).second)
        {
          delete dominoes;
        }
      }
    }

    for (LrState::iterator i = transitions->begin(); i != transitions->end(); ++i)
    {
      Dominoes *&dominoes = i->second.dominoes;

      Dominoes *allDominoes = new Dominoes();
      for (Dominoes::const_iterator d = dominoes->begin(); d != dominoes->end(); ++d)
      {
        const Domino &domino = *d;
        ActionItemCollector aic;
        aic.processActionItems(domino.toItem);

        for (NodeSet::const_iterator a = aic.actionItems.begin(); a != aic.actionItems.end(); ++a)
        {
          Node *actionItem = *a;
          allDominoes->insert(Domino(domino.fromItem, actionItem));
        }
      }
      delete dominoes;
      dominoes = 0;

      if (! allDominoes->isEssential())
      {
        allDominoes->clear();
      }

      dominoes = allDominoes;
      std::pair<DominoSets::iterator, bool> inserted = dominoSets.insert(DominoSets::value_type(dominoes, 0));
      if (! inserted.second)
      {
        delete dominoes;
        dominoes = inserted.first->first;
      }
    }

    if (transitions->hasConflicts(transitions->getK()))
    {
      ItemSet* conflictItems = new ItemSet(__FILE__, __LINE__);
      const TokenSequenceSet* conflictingTokenSequences = transitions->getConflicts(transitions->getK());
      transitions->collectConflictItems(tokenSequenceSets, conflictingTokenSequences, transitions->getK(), *conflictItems);
      if (! conflicts->insert(Conflicts::value_type(conflictItems, conflictingTokenSequences)).second)
      {
        delete conflictItems;
      }
    }
  }

  DominoSets stateHands(dominoSets);
  DominoSets oldHands;
  DominoSets newHands(stateHands);
  Dominoes *validHand = new Dominoes();
  do
  {
    oldHands = newHands;
    newHands.clear();
    for (DominoSets::iterator fromState = stateHands.begin(); fromState != stateHands.end(); ++fromState)
      for (DominoSets::iterator toState = oldHands.begin(); toState != oldHands.end(); ++toState)
    {
      for (Dominoes::iterator leftDomino = fromState->first->begin(); leftDomino != fromState->first->end(); ++leftDomino)
        if (leftDomino->toItem != 0)
          for (Dominoes::iterator rightDomino = toState->first->begin(); rightDomino != toState->first->end(); ++rightDomino)
            if (rightDomino->fromItem == leftDomino->toItem)
              validHand->insert(*leftDomino);
      if (! validHand->empty())
      {
        if (! validHand->isEssential())
        {
          delete validHand;
        }
        else
        {
          DominoSets::iterator found = dominoSets.find(validHand);
          if (found == dominoSets.end())
          {
            std::pair<DominoSets::iterator, bool> inserted = newHands.insert(DominoSets::value_type(validHand, 0));
            if (! inserted.second)
            {
              delete validHand;
              validHand = inserted.first->first;
            }
          }
          else
          {
            delete validHand;
            validHand = found->first;
          }
          triples.insert(Triples::value_type(DominoesPair(fromState->first, toState->first), validHand));
        }
        validHand = new Dominoes();
      }
    }
    dominoSets.insert(newHands.begin(), newHands.end());

//    printf("distinct hands: %d, triples %d\n", dominoSets.size(), triples.size());
  }
  while (! newHands.empty());

  delete validHand;
  validHand = 0;

  int dominoId = 1;
  for (DominoSets::iterator i = dominoSets.begin(); i != dominoSets.end(); ++i)
  {
    Dominoes *dominoes = i->first;
    if (dominoes->isEssential())
    {
      i->second = ++dominoId;
    }
    else
    {
      i->second = 1;
    }
  }
  dominoBits = Math::max(1, Math::bits(dominoId + 1));
                      // 1 for accept distinction
  dominoBits = Math::max(dominoBits, Math::bits(grammar->maxDistance + 1));
  dominoBits += 1;
          // +  1 for count/lookback distinction

  if (conflicting)
  {
//    printf("grammar->states->getConflicts()->size(): %d, conflicting: %d\n", grammar->states->getConflicts()->size(), conflicting);

    for (size_t s = 0; s < states.size(); ++s)
    {
      ItemSet *state = states[s];
      LrState *transitions = (*this)[state];
      transitions->buildAppendixes(grammar);
    }
  }

  for (size_t s = 0; s < states.size(); ++s)
  {
    ItemSet *state = states[s];
    LrState *transitions = (*this)[state];
    transitions->publishActionCodes(grammar);
  }

  // Augment tables with accept entries. It is necessary to do it here because we have not
  // augmented the grammar before.

  // still debatable whether we need the start symbol code as an accept argument

  for (Node *n = grammar->nonTerminals; n; n = n->followingSibling)
  {
    Production *p = static_cast <Production *> (n);
    if (p->isStartSymbol() || p == grammar->whitespace)
    {
      int startStateId = (*this)[p->state]->getStateId();
      int startSymbolShiftState = grammar->states->getGotoState(p->nonterminalCode, startStateId);

      if (startSymbolShiftState < 0)
      {
        grammar->states->setGoto(p->nonterminalCode, startStateId, entry(LrStates::SHIFT_ACCEPT, p->nonterminalCode, 0));
      }
      else
      {
        internalerr(); // TODO: take care of plain accept handling
        // grammar->states->setAction(*, startSymbolShiftState, LrStates::ACCEPT, p->nonterminalCode, LrStates::ACCEPT);
      }
    }
  }

  prepareTable();

  int count = 0;
  for (Triples::const_iterator j = getTriples()->begin(); j != getTriples()->end(); ++j)
  {
    const Triples::value_type &triple = *j;

    Dominoes* const fromDominoes = triple.first.first;
    Dominoes* const toDominoes = triple.first.second;
    const Dominoes *validDominoes = triple.second;

    int fromId = dominoSets.getId(fromDominoes);
    int toId = dominoSets.getId(toDominoes);
    int lookback = dominoSets.getId(validDominoes);

    lookbackTable.set(fromId, toId, lookback);
    ++count;
  }

  lookbackTable.getMap();

  if (grammar->verbose)
  {
    fprintf(stderr, "lookback map entry count: %d\n", count);
  }

  /*
    Actions
      shiftTerminal          state
      shiftNonTerminal       state
      reduce                 nonterminal [, count]
      shiftTerminalReduce    nonterminal [, count]
      shiftNonTerminalReduce nonterminal [, count]

    ActionT: States x Token -> Actions
      - shift only states, or xLR(1) reduce states

    ActionL: States x Lookahead -> Actions
      - xLR(2) reduce states

    Goto: States x Nonterminals -> Actions (shiftNonterminal or shiftNonterminalReduce)
      - reason for not using a combined table: only this one addressed by Nonterminals
      - thus can be encoded differently

    State renumbering
      - initial states first
      - non-xLR(1) states
      - states with nonterminal shifts, i.e. Goto relevance
      - other states
   */
}

void LrStates::prepareTable()
{
  tokenSet = ALLOCATE_ARRAY(int, lookaheadStates);
  memset(static_cast<void *>(tokenSet), 0, lookaheadStates * sizeof(int));
  for (const_iterator i = begin(); i != end(); ++i)
  {
    LrState *transitions = i->second;
    if (transitions->getStateId() < (int) lookaheadStates)
    {
      tokenSet[transitions->getStateId()] = CompressedTokenSet::getSetNo(transitions->getInitials(), grammar->lookaheadSets);
    }
  }

//  printf("goto table size: %d\n", gotoTable->getMap()->size());
}

#define SHOW_SETTINGS 0

void LrStates::setAction(const TokenSequence &ts, int stateId, int entry) const
{
#if SHOW_SETTINGS
  int argument = entry >> (dominoBits + actionBits);
  int lookback = (entry >> actionBits) & ((1 << dominoBits) - 1);
  int action = entry & actionMask;
  WString matchCodeDescription = ts.toString(grammar);
  fprintf(stderr, "setAction state=%d tokenSequence=(%ls) argument=%d lookback=%d action=%d (%d/%d)",
      stateId, matchCodeDescription.c_str(),
      argument, lookback, action, dominoBits, actionBits);
#endif

  int code = grammar->matchCode.get(ts);

#if SHOW_SETTINGS
  fprintf(stderr, " code=%d\n", code);
#endif

  grammar->caseidTable->set(code, stateId, entry << 1); // << 1 indicates result
}

void LrStates::setGoto(int nonterminalCode, int stateId, int entry) const
{
#if SHOW_SETTINGS
  int argument = entry >> (dominoBits + actionBits);
  int lookback = (entry >> actionBits) & ((1 << dominoBits) - 1);
  int action = entry & actionMask;
  const wchar_t *nonterminalName = nonterminalCode > grammar->maxNonterminalCode
                                 ? L"<implicit>"
                                 : grammar->nonterminalProductionByCode[nonterminalCode]->name;
  fprintf(stderr, "setGoto state=%d nonterminal=%d(%ls) argument=%d lookback=%d action=%d (%d/%d)\n",
      stateId, nonterminalCode, nonterminalName,
      argument, lookback, action, dominoBits, actionBits);
#endif

  gotoTable->set(nonterminalCode, stateId, entry);
}

int LrStates::entry(int action, int argument, int lookback)
{
  if (lookback >= (1 << dominoBits))
  {
    fprintf(stderr, "failed to set lookback code %d in %d-bit field (action %d, argument %d)\n", lookback, dominoBits, action, argument);
    internalerr();
  }
  if (action == SHIFT_REDUCE_LOOKBACK || action == REDUCE_LOOKBACK)
  {
    hasLookback = true;
  }
  return (((argument << dominoBits) + lookback) << actionBits) + action;
}

int LrStates::getGotoState(int nonterminalCode, int stateId) const
{
  int entry = gotoTable->get(nonterminalCode, stateId);
  if (entry == 0)
  {
    return -1;
  }
  else if ((entry & actionMask) != SHIFT)
  {
    internalerr();
  }
  return entry >> (dominoBits + actionBits);
}

int LrStates::appendixOffset(AppendixEntry pair)
{
  std::map<AppendixEntry, int>::iterator i = appendixes.find(pair);
  int offset;
  if (i != appendixes.end())
  {
    offset = i->second;
  }
  else
  {
    offset = appendixEnd;
    appendixEnd += 2;
    if (appendixEnd > appendixMax)
    {
      appendixMax = Math::max(appendixMax <<= 1, 64);
      appendix = REALLOCATE_ARRAY(int, appendix, appendixMax);
    }
    appendix[offset] = pair.first;
    appendix[offset + 1] = pair.second;
    appendixes.insert(std::pair<AppendixEntry, int>(pair, offset));
  }
  return offset;
}
