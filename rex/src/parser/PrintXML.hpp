/*
 * Print.hpp
 *
 *  Created on: 31.07.2008
 *      Author: Gunther
 */

#ifndef PRINTXML_HPP_
#define PRINTXML_HPP_

#include "Grammar.hpp"
#include "ItemSet.hpp"

#include "../common/Format.hpp"
#include "../common/OutputFile.hpp"

#include <map>

class PrintXML : private Visitor
{
public:
  PrintXML(char **av, char *fileName, bool printFF);
  virtual ~PrintXML();

  void print(const wchar_t *string);
  void flush();

  void showTokenSequenceSet(Grammar *grammar, const TokenSequenceSet *tss);
  void showItem(const wchar_t *role, Node *item, const TokenSequenceSetAccessor *lookahead);
  void showItemSet(const ItemSet &items, const wchar_t *name);
  void showState(Grammar *grammar, size_t k, LrStates &states, ItemSet *kernel, const LrState *transitions);
  void dump(Grammar *grammar, size_t k);

  void indentation()
  {
    for (size_t i = 0; i < indent; ++i)
    {
      print(L" ");
    }
  }

  void visitNode(Node *node);
  void visitNodeList(Node *node);
  void visitNodeWithChildren(NodeWithChildren *node);
  void visitSequence(Sequence *node);
  void visitOptional(Optional *node);
  void visitZeroOrMore(ZeroOrMore *node);
  void visitOneOrMore(OneOrMore *node);
  void visitGrammar(Grammar *node);
  void visitChoice(Choice *node);
  void visitExclusion(Exclusion *node);
  void visitPredicate(Predicate *node);
  void visitContext(Context *node);
  void visitPreference(Preference *node);
  void visitDelimiter(Delimiter *node);
  void visitEquivalence(Equivalence *node);
  void visitComplement(Complement *node);
  void visitProduction(Production *node);
  void visitRef(Ref *node);
  void visitString(String *node);
  void visitProcessingInstruction(ProcessingInstruction *node);
  void visitEndOfFile(EndOfFile *node);
  void visitChar(Char *node);
  void visitCharCode(CharCode *node);
  void visitCharRange(CharRange *node);
  void visitCharCodeRange(CharCodeRange *node);

private:
  inline wchar_t *tokenSequenceString(const TokenSequence &c);

  void printTokenSet(const wchar_t *name, const wchar_t *suffix, const TokenSequenceSetAccessor &ts);
  void printSets(Grammar *grammar);

  inline void printContent(const wchar_t c);
  inline void printContent(const wchar_t *value);
  inline void printNumberedTokenSetAttribute(const wchar_t *name,
                                      const wchar_t *suffix,
                                      size_t k,
                                      bool suppress,
                                      const TokenSequenceSet &ts);
  inline void openTag(Node *node, bool tagOpen = false, const wchar_t *nodeType = 0, const CompressedTokenSet *lookahead = 0);
  inline void closeTag(Node *node, bool tagOpen = false, const wchar_t *nodeType = 0);

  char **argv;
  FILE *file;
  char *fileName;
  bool printFF;
  bool printID;
  size_t indent;
  typedef std::map<TokenSequence, wchar_t *> StringByCode;
  StringByCode tokenSequenceStringMap;

  WString xml;

  Grammar *grammar;

  Format format;
};

#endif
