/*
 * PrintXSLT.hpp
 *
 *  Created on: 23.10.2009
 *      Author: Gunther
 */

#ifndef PRINTXSLT_HPP_
#define PRINTXSLT_HPP_

#include "Grammar.hpp"
#include "PrintVisitor.hpp"
#include "TokenSequenceSet.hpp"

#include "../common/Format.hpp"
#include "../common/OutputFile.hpp"

#include <set>
#include <list>
#include <string>

class PrintXSLT : public PrintVisitor
{
public:
  PrintXSLT(char **av,
            const wchar_t *aClassName,
            const wchar_t *anEmbeddedOutputString,
            bool unlimited,
            bool printTree,
            bool omitPosition,
            bool printMain,
            bool printTrace)
  : argv(av),
    className(aClassName),
    variant(0),
    embeddedOutputString(anEmbeddedOutputString),
    unlimitedLookahead(unlimited),
    file(0),
    simpleWhitespace(true),
    complexWhitespace(true),
    anyWhitespace(true),
    hasProlog(false),
    hasBacktracking(false),
    memoization(false),
    tree(printTree),
    hasCustomCode(false),
    noPosition(omitPosition),
    main(printMain),
    trace(printTrace),
    grammar(0),
    methodPrefixParse(L"parse"),
    methodPrefixTry(L"try"),
    methodPrefix(methodPrefixParse),
    consumeMethods(1),
    toBeEscaped(0),
    isLrParser(false),
    restoreCalled(false),
    whitespaceCalled(false)
  {
    toBeEscaped = new WcsSet();
    toBeEscaped->insert(wcsdup(L"(:"));
    toBeEscaped->insert(wcsdup(L":)"));

    char *fName = Format::wchar2char(aClassName);
    fileName = Format::newFileName(fName, ".xslt");
    free(fName);
    wFileName = Format::char2wchar(fileName);
  }

  virtual ~PrintXSLT()
  {
    free(fileName);
    free(wFileName);
    delete toBeEscaped;
  }

  class PrintLoops : public Visitor
  {
  public:
    PrintLoops(PrintXSLT *p) : px(p), loopId(0) {}
    void visitZeroOrMore(ZeroOrMore *node);
    void visitOneOrMore(OneOrMore *node);
    void print(const wchar_t *string) {px->print(string);}
    void append(const wchar_t *string) {print(string);}

  private:
    PrintXSLT *px;
    int loopId;
  };

  class Reorder : public Visitor
  {
  public:
    Reorder(ProductionList &pl) : productionList(pl) {}
    virtual ~Reorder() {}
    void visitProduction(Production *node) {process(node);}
    void visitRef(Ref *node) {process(node->nonTerminal);}

  private:
    void process(Production *p)
    {
      if (p && p->tokenCode < 0 && productionSet.find(p) == productionSet.end())
      {
        productionSet.insert(p);
        productionList.push_front(p);
        visitNodeList(p->firstChild);
      }
    }

    ProductionList &productionList;
    ProductionSet productionSet;
  };

  void visitNodeList(Node *node);
  void visitOptional(Optional *node);
  void visitZeroOrMore(ZeroOrMore *node);
  void visitOneOrMore(OneOrMore *node);
  void visitChoice(Choice *node);
  void visitProduction(Production *node);
  void visitRef(Ref *node);
  void visitString(String *node);
  void visitProcessingInstruction(ProcessingInstruction *node);

  const wchar_t *extension() const {return L".xslt";}
  const wchar_t *getFileName() const {return wFileName;}

protected:
  void automaticSemicolonInsertion(Node *node);
  void printCase(const CompressedTokenSet *lookahead, size_t k, Node *c, const wchar_t *prefix);
  void printConsume(Token::Code code);
  bool printLookahead(size_t k, const TokenSequenceSet &, size_t level, const CompressedTokenSet *lookahead, bool findsLookahead);
  void printMatch(const CompressedTokenSet *lookahead,
                  size_t k,
                  int conflictCaseId,
                  const TokenSequenceSet &ts,
                  MatchType matchType,
                  int caseId,
                  const wchar_t *prefix,
                  const wchar_t *suffix);
  void printCodeSequenceAnnotation(const TokenSequenceSet &t);
  void printLookaheadMethods(size_t lookaheadMethods, bool withWhitespace);

  void printVariables();
  void printProlog(Grammar *node);
  void printUtilities();
  void printEpilog(Grammar *node);

  bool printBacktracking(Node *node,
                         const CompressedTokenSet *lookahead,
                         int conflictCaseId,
                         int conflictId,
                         Node *predicate);
  bool printBacktracking(Node *node,
                         const CompressedTokenSet *lookahead,
                         int conflictCaseId,
                         int conflictId,
                         const NodeList &cases);

  void visitGrammar(Grammar *node)
  {
    grammar = node;
    isLrParser = grammar->states != 0;
    hasCustomCode = ! grammar->distinctCodeAnnotations.empty();

    simpleWhitespace = ! grammar->simpleWhitespaceIntroducers.empty();
    complexWhitespace = ! grammar->complexWhitespaceIntroducers.empty();
    anyWhitespace = simpleWhitespace || complexWhitespace;
    hasBacktracking = grammar->hasBacktracking;
    memoization = hasBacktracking;
    variant = grammar->variant;

    file = fopen(fileName, "wb");
    if (file == 0)
    {
      perror(fileName);
      exit(1);
    }

    OutputFile::printHeader(file, XSLT, argv);
    lineNo += 4;

    if (grammar->prolog)
    {
      for (Node *n = grammar->prolog; n; n = n->followingSibling)
      {
        if (n->hasActiveProcessingInstruction())
        {
          section = PROLOG;
          visitNodeList(grammar->prolog);

          hasProlog = true;
          break;
        }
      }
    }

    printProlog(grammar);

    printVariables();

    if (embeddedOutputString == 0)
    {
      internalerr();
    }
    print(embeddedOutputString);

    section = NONTERMINALS;

    ProductionList productionList;
    Reorder r(productionList);

    if (! isLrParser)
    {
      for (Node *n = node->nonTerminals; n; n = n->followingSibling)
      {
        Production *p = static_cast <Production *> (n);
        if (   p->isStartSymbol()
            || (p == node->whitespace && complexWhitespace))
        {
          p->accept(r);
        }
      }

      for (ProductionList::iterator i = productionList.begin(); i != productionList.end(); ++i)
      {
        Production *p = *i;

        PrintLoops pl(this);
        p->accept(pl);

        if (p->runPayload)
        {
          p->accept(*this);
        }

        if (p->runOffLoad)
        {
          const wchar_t *v = variant;
          const wchar_t *m = methodPrefix;
          variant = L"";
          methodPrefix = methodPrefixTry;

          p->accept(*this);

          variant = v;
          methodPrefix = m;
        }
      }
    }

    printUtilities();
    printEpilog(node);

    char *encoded = Encoder::encode(content());
    fputs(encoded, file);
    free(encoded);
    OutputFile::printFooter(file, XSLT);
    fclose(file);
  }

  bool visitEpilog()
  {
    if (grammar->epilog)
    {
      for (Node *n = grammar->epilog; n; n = n->followingSibling)
      {
        if (n->hasActiveProcessingInstruction())
        {
          section = EPILOG;
          visitNodeList(grammar->epilog);
          return true;
        }
      }
    }
    return false;
  }

  void invalidateXmlCommentTokens(WString &w)
  {
    for (size_t found; WString::npos != (found = w.find(L"--"));) w.replace(found, 2, L"-' '-");
  }

  void invalidateXPathCommentTokens(WString &w)
  {
    for (size_t found; WString::npos != (found = w.find(L"(:"));) w.replace(found, 2, L"(' '.");
    for (size_t found; WString::npos != (found = w.find(L":)"));) w.replace(found, 2, L":' ')");
    for (size_t found; WString::npos != (found = w.find(L"&" ));) w.replace(found, 1, L":)");
    for (size_t found; WString::npos != (found = w.find(L":)"));) w.replace(found, 2, L"&amp;");
    for (size_t found; WString::npos != (found = w.find(L"<" ));) w.replace(found, 1, L"&lt;" );
    for (size_t found; WString::npos != (found = w.find(L"\"" ));) w.replace(found, 1, L"&quot;" );
  }

  char **argv;
  const wchar_t *className;
  char *fileName;
  wchar_t *wFileName;
  const wchar_t *variant;
  const wchar_t *embeddedOutputString;
  bool unlimitedLookahead;

  FILE *file;

  WString lineBuffer;

  bool simpleWhitespace;
  bool complexWhitespace;
  bool anyWhitespace;
  bool hasProlog;
  bool hasBacktracking;
  bool memoization;

  enum {piIndent = 70};

  const bool tree;
  bool hasCustomCode;
  const bool noPosition;
  const bool main;
  const bool trace;

  Grammar *grammar;

  Format format;

  const wchar_t *methodPrefixParse;
  const wchar_t *methodPrefixTry;
  const wchar_t *methodPrefix;
  int consumeMethods;
  WcsSet *toBeEscaped;
  bool isLrParser;
  bool restoreCalled;
  bool whitespaceCalled;
};

#endif
