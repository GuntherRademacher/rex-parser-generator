/*
 * ReportConflicts.hpp
 *
 *  Created on: 13.02.2014
 *      Author: Gunther
 */

#ifndef REPORTCONFLICTS_HPP_
#define REPORTCONFLICTS_HPP_

#include "Grammar.hpp"
#include "ItemSet.hpp"

class ReportConflicts : public Visitor
{                      typedef Visitor super;
public:
  ReportConflicts(const wchar_t *l, size_t n, bool printFF) : label(l), k(n), count(0), ff(printFF) {}

  void report(const LrStates::Conflicts *conflicts, Grammar *grammar);

  void visitChoice(Choice *node)
  {
    if (hasConflict(node)) reportConflict(node);
    super::visitChoice(node);
  }

  virtual void visitOptional(Optional *node)
  {
    if (hasConflict(node)) reportConflict(node);
    super::visitOptional(node);
  }

  virtual void visitZeroOrMore(ZeroOrMore *node)
  {
    if (hasConflict(node)) reportConflict(node);
    super::visitZeroOrMore(node);
  }

  virtual void visitOneOrMore(OneOrMore *node)
  {
    if (hasConflict(node)) reportConflict(node);
    super::visitOneOrMore(node);
  }

private:
  void recordConflictingItems(ItemSet &conflictingItems, const TokenSequenceSet *conflictingTokens, const ItemSet &items);

  bool hasConflict(Node *node) {return node->conflicts(k) != 0;}

  void reportConflict(Choice *node)
  {
    ++count;
    bool reported = false;

//    fprintf(stdout, "reported A: %d %d %ls\n", reported, k, node->production->name);

    size_t alternative = 0;
    for (NodeList::iterator i(node->cases.begin()); i != node->cases.end(); ++i)
    {
      ++alternative;
      Node *element = (*i)->element();
      if (element->first(1) != *node->grammar->epsilon)
      {
        TokenSequenceSet conflicts;
        conflicts.insertIntersectionOf(*node->conflicts(k), element->expect(k));

//        wchar_t *w = (*node->conflicts(k)).toString(node->grammar, L"", L"", 96, 0, false);
//        printf("    lhs      %ls\n", w ? w : L"null pointer...");

//        w = element->expect(k).toString(node->grammar, L"", L"", 96, 0, false);
//        printf("    rhs      %ls\n", w ? w : L"null pointer...");

//        w = conflicts.toString(node->grammar, L"", L"", 96, 0, false);
//        printf("    res      %ls\n", w ? w : L"null pointer...");

        if (! conflicts.empty())
        {
          reportConflict(node, conflicts, alternative);
          reported = true;
//          fprintf(stdout, "reported B: %d\n", reported);
        }
      }
    }
//    fprintf(stdout, "reported C: %d\n", reported);
    fflush(stdout);
    if (! reported) internalerr();
  }

  void reportConflict(NodeWithChildren *node)
  {
    ++count;
    reportConflict(node, *node->conflicts(k));
  }

  enum {LIMIT = 16};

  void reportConflict(Node *node, const TokenSequenceSet &conflicts, size_t alternative = 0)
  {
    fprintf(stdout, "%ls(%d) conflict #%d in ", label, (int) k, (int) count);
    if (alternative)
    {
      fprintf(stdout, "%ls alternative of ", Format().toString<wchar_t>(alternative, 10, 0, 0, 0, 0, true));
    }
    fprintf(stdout, "%ls operator of ", node->getNodeType());
    fprintf(stdout, "production %ls:\n", node->production->name);
    reportConflictingTokenSequences(conflicts, node->grammar);
  }

  void reportConflictingTokenSequences(const TokenSequenceSet &conflicts, Grammar *grammar)
  {
    fprintf(stdout, "  conflicting lookahead token%ls%ls:\n", k == 1 ? L"" : L" sequence", conflicts.size() == 1 ? L"" : L"s");
    int count = 0;
    OrderedTokenSequenceVector orderedConflicts(conflicts, __FILE__, __LINE__);
    for (OrderedTokenSequenceVector::const_iterator i(orderedConflicts.begin()); i != orderedConflicts.end(); ++i)
    {
      if (++count <= LIMIT || ff)
      {
        fprintf(stdout, "    %ls\n", i->toString(grammar).c_str());
      }
    }
    if (count > LIMIT && ! ff)
    {
      fprintf(stdout, "    ... %ls more\n", Format().toString<wchar_t>(count - LIMIT));
    }
  }

  const wchar_t *label;
  size_t k;
  size_t count;
  bool ff;
};

#endif /* REPORTCONFLICTS_HPP_ */
