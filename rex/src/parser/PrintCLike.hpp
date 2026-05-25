/*
 * PrintCLike.hpp
 *
 *  Created on: 03.10.2008
 *      Author: Gunther
 */

#ifndef PRINTCLIKE_HPP_
#define PRINTCLIKE_HPP_

#include "Grammar.hpp"
#include "PrintVisitor.hpp"
#include "TokenSequenceSet.hpp"

#include "../common/Format.hpp"
#include "../common/OutputFile.hpp"

#include <map>
#include <string>

//#define TRACE
#ifndef TRACE
#define Trace(method)
#else
#define Trace(method) Tracer tracer(method, __FILE__, __LINE__)

class Tracer
{
public:
  Tracer(const char *method, const char *file, int line)
  : method(method), file(file), line(line)
  {
    fprintf(stderr, "%*s{// enter %ls(%ls:%d)\n", level++, "", method, file, line);
  }

  virtual ~Tracer()
  {
    fprintf(stderr, "%*s}// leave %ls(%ls:%d)\n", --level, "", method, file, line);
  }

private:
  static int level;

  const char *method;
  const char *file;
  int line;
};
#endif

class PrintCLike : public PrintVisitor
{
public:
  PrintCLike(char **av,
             TargetLanguage l,
             const wchar_t *anExtension,
             const wchar_t *aClassName,
             const wchar_t *anInterfaceName,
             bool unlimited,
             bool printTree,
             bool omitPosition,
             bool printMain,
             bool performance,
             bool printTrace)
  : argv(av),
    targetLanguage(l),
    extension(anExtension),
    fileName(0),
    variant(0),
    unlimitedLookahead(unlimited),
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
    performanceTest(performance),
    trace(printTrace),
    grammar(0),
    methodPrefixParse(L"parse_"),
    methodPrefixTry(L"try_"),
    methodPrefix(methodPrefixParse),
    consumeMethods(1),
    toBeEscaped(0),
    loopId(0),
    noLexer(false),
    isLrParser(false),
    useGlr(false)
  {
    wFileName = aClassName;
    className = aClassName;
    interfaceName = Format::acceptableName<WString>(anInterfaceName, true);

    className = Format::acceptableName<WString>(aClassName, true);

    if (targetLanguage == JAVA || targetLanguage == SCALA || targetLanguage == GO || targetLanguage == CSHARP )
    {
      const wchar_t *cn = aClassName;
      const wchar_t *lastPeriod = wcsrchr(cn, L'.');
      if (lastPeriod)
      {
        packageName = WString(cn, lastPeriod - cn).c_str();
        className = WString(lastPeriod + 1).c_str();
        wFileName = className;
      }
      if (targetLanguage == JAVA || targetLanguage == SCALA)
      {
        packageName = Format::acceptableName<WString>(packageName.c_str(), true);
        className = Format::acceptableName<WString>(className.c_str(), true);
        wFileName = className;
      }
    }
    else if (targetLanguage == HAXE)
    {
      wFileName = className;
    }

    if (targetLanguage == HAXE || targetLanguage == GO)
    {
      if (! iswupper(className[0]))
      {
        className[0] = towupper(className[0]);
        if (targetLanguage == HAXE) wFileName = className;
      }
    }

    wFileName += extension;

    fileName = Format::wchar2char(wFileName.c_str());

    file = fopen(fileName, "wb");
    if (file == 0)
    {
      perror(fileName);
      exit(1);
    }

    OutputFile::printHeader(file, targetLanguage, argv);
    lineNo += 2;
  }

  virtual ~PrintCLike()
  {
    char *encoded = Encoder::encode(content());
    fputs(encoded, file);
    free(encoded);

    OutputFile::printFooter(file, targetLanguage);
    fclose(file);

    free(fileName);
  }

  void visitNodeList(Node *node);
  void visitOptional(Optional *node);
  void visitZeroOrMore(ZeroOrMore *node);
  void visitOneOrMore(OneOrMore *node);
  void visitChoice(Choice *node);
  void visitProduction(Production *node);
  void visitRef(Ref *node);
  void visitString(String *node);
  void visitProcessingInstruction(ProcessingInstruction *node);

  virtual void openFile() = 0;

  virtual void openClass() = 0;
  virtual void openStackNode() {}
  virtual void closeStackNode() {}
  virtual void openThread() {}

  virtual void openMethod(const wchar_t *type,
                          const wchar_t *prefix,
                          const wchar_t *name,
                          const wchar_t *args,
                          bool constant = false,
                          const wchar_t *clazz = 0) = 0;
  virtual void beginNonpublic() = 0;
  virtual void beginPublic() = 0;
  virtual void privateVars() = 0;
  virtual void close(Grammar *node) = 0;

  virtual bool isCpp() {return false;}
  virtual bool isCSharp() {return false;}
  virtual bool isJava() {return false;}
  virtual bool isJavascript() {return false;}
  virtual bool isTypescript() {return false;}
  virtual bool isScala() {return false;}
  virtual bool isHaxe() {return false;}
  virtual bool isGo() {return false;}
  virtual bool isPython() {return false;}

  virtual const wchar_t *nullPtr() const = 0;
  virtual const wchar_t *deref() const = 0;
  virtual const wchar_t *beginThrowStmt() const = 0;
  virtual const wchar_t *endThrowStmt() const {return L")";}
  virtual const wchar_t *endClass() const = 0;
  virtual const wchar_t *lineCommentPrefix() const = 0;
  virtual const wchar_t *inlineCommentIntroducer() const {return L"// ";}
  virtual const wchar_t *stringType() const = 0;
  virtual const wchar_t *boolType() const = 0;
  virtual const wchar_t *intType() const = 0;
  virtual const wchar_t *voidType() const = 0;
  virtual const wchar_t *assign() const {return L" = ";}
  virtual const wchar_t *intVar() const = 0;
  virtual const wchar_t *intVal() const = 0;
  virtual const wchar_t *boolVar() const = 0;
  virtual const wchar_t *stringIntroducer() const = 0;
  virtual const wchar_t *semicolon() const {return L";";}
  virtual const wchar_t *ifLeftParen() const {return L"(";}
  virtual const wchar_t *ifRightParen() const {return L")";}
  virtual const wchar_t *elseWithBraces() const {return L"}\nelse\n{";}
  virtual const wchar_t *leftBrace() const {return L"\n{";}
  virtual const wchar_t *rightBrace() const {return L"\n}";}
  virtual const wchar_t *thiz() const {return L"";}
  virtual const wchar_t *staticPrefix() const {return L"";}
  virtual const wchar_t *leftbracket() const {return L"[";}
  virtual const wchar_t *rightbracket() const {return L"]";}
  virtual const wchar_t *returnKeyword() const {return L"return ";}
  virtual const wchar_t *caseIntroducer() const {return L":";}
  virtual const wchar_t *arrow() const {return L".";}
  virtual const wchar_t *writeTrace() const {return L"writeTrace(";}
  virtual const wchar_t *endWriteTrace() const {return L")";}

  virtual const wchar_t *token() {return L"l1";}
  virtual const wchar_t *tokenSequence() {return L"lk";}

  virtual void printFlush(int indentation, bool withinThread = false) {}

  const wchar_t *getFileName() const {return wFileName.c_str();}

  void setNoLexer(bool n) {noLexer = n;}
  void setLrParser(bool l) {isLrParser = l;}
  void setUseGlr(bool l) {useGlr = l;}

protected:
  void printCase(const CompressedTokenSet *lookahead, size_t k, Node *c, int backtrackedCaseId);
  void printConsume(Token::Code code);

  void printLookahead(size_t k, const TokenSequenceSet &, size_t level, const CompressedTokenSet *lookahead, bool findsLookahead);

  void printMatch(const CompressedTokenSet *lookahead,
                  size_t k,
                  int backtrackedCaseId,
                  const TokenSequenceSet &ts,
                  MatchType matchType,
                  bool invert,
                  int caseId,
                  const wchar_t *prefix);
  void printCodeSequenceAnnotation(const TokenSequenceSet &t);
  void printCountMethod();
  void printThreadBody1();

  virtual void printProlog();
  virtual void printEpilog();
  virtual void printInstanceCode() {}
  virtual void printXmlSerializer() {}
  virtual void printGlrParseMethod() {}

  void printBacktracking(Node *node,
                         const CompressedTokenSet *lookahead,
                         int conflictCaseId,
                         int conflictId,
                         Node *predicate);
  void printBacktracking(Node *node,
                         const CompressedTokenSet *lookahead,
                         int conflictCaseId,
                         int conflictId,
                         const NodeList &cases);
  void printLookaheadMethods(size_t lookaheadMethods, bool withWhitespace);
  int nestedConflictLevel(Node *node);
  void saveContext(int ncl);
  void restoreContext(int ncl);
  virtual void printReadMethod() = 0;
  virtual void printFileProcessor() = 0;
  void printASICall(Node *node);
  void printInitializer();

  void printArgNamesOnly(const wchar_t *args)
  {
    bool ignore = true;
    for (const wchar_t *a = args; *a; ++a)
    {
      if (! ignore)
      {
        print(*a);
      }
      if (*a == ' ')
      {
        ignore = ! ignore;
      }
    }
  }

  void visitGrammar(Grammar *node)
  {
    grammar = node;
    isLrParser = grammar->states != 0;
    useGlr = grammar->useGlr;
    hasCustomCode = ! grammar->distinctCodeAnnotations.empty();

    setNoLexer(grammar->noLexer);

    simpleWhitespace = ! grammar->simpleWhitespaceIntroducers.empty();
    complexWhitespace = ! grammar->complexWhitespaceIntroducers.empty();
    anyWhitespace = simpleWhitespace || complexWhitespace;
    hasBacktracking = grammar->hasBacktracking;
    memoization = hasBacktracking;
    variant = grammar->variant;

    openFile();
    hasProlog = visitProlog();
    openClass();

    printProlog();

    section = NONTERMINALS;

    for (Node *n = node->nonTerminals; n; n = n->followingSibling)
    {
      Production *p = static_cast <Production *> (n);
      if (p->isStartSymbol())
      {
        p->accept(*this);
      }
    }

    beginNonpublic();

    if (! isLrParser)
    {
      for (Node *n = node->nonTerminals; n; n = n->followingSibling)
      {
        Production *p = static_cast <Production *> (n);
        if (   ! p->isStartSymbol()
            && p->runPayload
           )
        {
          p->accept(*this);
        }

        if (p->runOffLoad)
        {
          const wchar_t *v = variant;
          const wchar_t *m = methodPrefix;
          const char *flags = getenv("FLAGS");

          bool hack = flags && strchr(flags, 'H');

          if (! hack)
          {
            variant = L"";
          }

          methodPrefix = methodPrefixTry;
          p->accept(*this);
          variant = v;
          methodPrefix = m;
        }
      }
    }

    printEpilog();
    close(node);
  }

  bool visitProlog()
  {
    if (grammar->prolog)
    {
      for (Node *n = grammar->prolog; n; n = n->followingSibling)
      {
        if (n->hasActiveProcessingInstruction())
        {
          section = PROLOG;
          visitNodeList(grammar->prolog);
          return true;
        }
      }
    }
    return false;
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

  char **argv;
  TargetLanguage targetLanguage;
  const wchar_t *extension;
  WString wFileName;
  WString packageName;
  WString className;
  WString interfaceName;
  char *fileName;
  const wchar_t *variant;
  bool unlimitedLookahead;

  FILE *file;

  WString lineBuffer;

  bool simpleWhitespace;
  bool complexWhitespace;
  bool anyWhitespace;
  bool hasProlog;
  bool hasBacktracking;
  bool memoization;

  enum {piIndent = 60};

  const bool tree;
  bool hasCustomCode;
  const bool noPosition;
  const bool main;
  const bool performanceTest;
  const bool trace;

  Grammar *grammar;

  Format format;

  const wchar_t *methodPrefixParse;
  const wchar_t *methodPrefixTry;
  const wchar_t *methodPrefix;

  int consumeMethods;
  WcsSet *toBeEscaped;
  int loopId;

  bool noLexer;
  bool isLrParser;
  bool useGlr;
};

#endif
