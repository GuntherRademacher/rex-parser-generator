/*
 * ReportConficts.cpp
 *
 *  Created on: 13.02.2014
 *      Author: Gunther
 */

#include "../common/Memory.hpp"
#include "ReportConflicts.hpp"
#include "PrintEbnf.hpp"

void ReportConflicts::recordConflictingItems(ItemSet &conflictingItems, const TokenSequenceSet *conflictingTokens, const ItemSet &items)
{
  for (ItemSet::const_iterator i = items.begin(); i != items.end(); ++i)
  {
    Node *item = i->first;
    const TokenSequenceSetAccessor *lookahead = i->second;
    const TokenSequenceSetAccessor *expected = item->isReduce() ? lookahead : &item->first(k, *lookahead);
    const TokenSequenceSet *intersection = item->grammar->tokenSequenceSets->setIntersection(conflictingTokens, expected);
    if (! intersection->empty())
    {
      conflictingItems.addItem(item, lookahead);
    }
  }
}

void ReportConflicts::report(const LrStates::Conflicts *conflicts, Grammar *grammar)
{
  PrintEbnf pe(PrintEbnf::ACTIVE);
  for (LrStates::Conflicts::const_iterator i = conflicts->begin(); i != conflicts->end(); ++i)
  {
    const ItemSet* conflictingItems = i->first;
    const TokenSequenceSet* const conflictingTokens = i->second;

    size_t shift = 0;
    size_t reduce = 0;

    for (ItemSet::const_iterator j = conflictingItems->begin(); j != conflictingItems->end(); ++j)
    {
      Node* const item = j->first;
      if (item->isReduce())
        ++reduce;
      else if (item->isString())
        ++shift;
      else if (item->isRef() && static_cast<Ref *>(item)->lexical)
        ++shift;
    }

    printf("%ls(%d) conflict #%d (%lsreduce%ls):\n", label, (int) k, (int) ++count, shift > 0 ? L"shift-" : L"", reduce > 1 ? L"-reduce" : L"");

    //  const wchar_t *zNotationSpot = L"&#10625;";
    //  const wchar_t *bullet = L"&#8226;";

    for (ItemSet::const_iterator j = conflictingItems->begin(); j != conflictingItems->end(); ++j)
    {
      Node* const item = j->first;
      printf("    %ls", Format::reIndent(pe.itemToString(item, L"."), 4, true).c_str());
    }

    if (k)
    {
      reportConflictingTokenSequences(*conflictingTokens, grammar);
    }

    printf("\n");
  }
}
