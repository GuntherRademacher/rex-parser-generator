/*
 * PrintEbnf.hpp
 *
 *  Created on: 18.06.2012
 *      Author: Gunther
 */

#ifndef PRINTEBNF_HPP_
#define PRINTEBNF_HPP_

#include "Grammar.hpp"

#include "../common/Format.hpp"
#include "../common/OutputFile.hpp"

#include <map>

class PrintEbnf : private Visitor
{
public:
  enum ShowPI {NONE, ACTIVE, ALL};

  PrintEbnf(ShowPI showPI);
  virtual ~PrintEbnf() {};
  void print(const char * outputFileName, char **av, char *className, Grammar *node);
  WString itemToString(Node *node, const wchar_t *aDot = L".");

//  static void print(FILE *file, Node *node)
//  {
//    PrintEbnf pe(av, className);
//    node->accept(pe);
//  }

private:
  void print(const wchar_t *string);
  size_t column();

  void flush();

  void indentation()
  {
    for (size_t i = 0; i < indent; ++i)
    {
      print(L" ");
    }
  }

  bool isCharClassLiteral(wchar_t character);
  bool isCharClassLiteral(Node *node);
  void printCodePoint(unsigned int codePoint);

  void visitNodePreOrder(Node *node);
  void visitNodePostOrder(Node *node);
  void visitNodeWithChildren(NodeWithChildren *node);
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
  void visitCharClass(CharClass *node);

  inline void printContent(const wchar_t c);
  inline void printContent(const wchar_t *value);

  FILE *file;
  size_t indent;
  Grammar *grammar;
  Node *item;
  const wchar_t *dot;

  WString ebnf;
  Format format;

private:
  ShowPI showPI;
};

#endif
