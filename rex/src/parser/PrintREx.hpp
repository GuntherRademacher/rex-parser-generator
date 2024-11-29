/*
 * PrintC.hpp
 *
 *  Created on: 03.10.2008
 *      Author: Gunther
 */

#ifndef PRINTREX_HPP_
#define PRINTREX_HPP_

#include "../common/OutputFile.hpp"

#include <map>

#include "../lexer/LexerGenerator.hpp"
#include "Grammar.hpp"

class PrintREx : public Visitor
{
public:
  PrintREx(char **av,
           const wchar_t *aClassName,
           TargetLanguage aTargetLanguage,
           bool charParser,
           bool printTrace,
           bool printTree,
           bool aPrintREx,
           bool unlimited,
           bool v);
  virtual ~PrintREx();

  void write();

  void visitNodeList(Node *node);
  void visitOptional(Optional *node);
  void visitZeroOrMore(ZeroOrMore *node);
  void visitOneOrMore(OneOrMore *node);
  void visitGrammar(Grammar *node);
  void visitChoice(Choice *node);
  void visitProduction(Production *node);
  void visitRef(Ref *node);
  void visitString(String *node);
  void visitPreference(Preference *node);
  void visitDelimiter(Delimiter *node);
  void visitEquivalence(Equivalence *node);
  void visitEndOfFile(EndOfFile *node);
  void visitChar(Char *node);
  void visitCharCode(CharCode *node);
  void visitCharRange(CharRange *node);
  void visitCharCodeRange(CharCodeRange *node);
  void visitCharClass(CharClass *node);
  void visitExclusion(Exclusion *node);
  void visitContext(Context *node);
  void visitComplement(Complement *node);
  void visitSequence(Sequence *node);

  const wchar_t *getInstanceCode() const {return rex ? rex->getInstanceCode() : 0;}
  const wchar_t *getStaticCode() const {return rex ? rex->getStaticCode() : 0;}

private:
  inline void claim(size_t n);
  inline void print(const wchar_t *string, bool check = true);
  inline void lineFeed();
  inline void printProlog(Grammar *grammar);
  inline void printPreferences();
  inline void printSets(Grammar *grammar);
  inline void printCharacter(wchar_t c);
  inline void printCharCode(int c);

  char **argv;
  wchar_t *className;
  TargetLanguage targetLanguage;
  const bool parseChars;
  const bool trace;
  const bool tree;
  size_t indent;
  size_t width;
  WString rexGrammar;
  const bool printRex;
  const bool unlimitedLookahead;
  const bool verbose;

  LexerGenerator *rex;

  Format format;
};

#endif
