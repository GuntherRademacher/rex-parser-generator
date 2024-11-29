/*
 * PrintPython.hpp
 *
 *  Created on: 06.01.2020
 *      Author: Gunther
 */

#ifndef PRINTPYTHON_HPP_
#define PRINTPYTHON_HPP_

#include "PrintCLike.hpp"
#include "../common/Platforms.hpp"

class PrintPython : public PrintCLike
{
public:
  PrintPython(char **argv,
              const wchar_t *aClassName,
              const wchar_t *anInterfaceName,
              const wchar_t *anEmbeddedOutputString,
              bool unlimited,
              bool printTree,
              bool omitPosition,
              bool printMain,
              bool performance,
              bool printTrace)
  : PrintCLike(argv,
               PYTHON,
               L".py",
               aClassName,
               anInterfaceName,
               unlimited,
               printTree,
               omitPosition,
               printMain,
               performance,
               printTrace)
  , embeddedOutputString(anEmbeddedOutputString)
  , visibility(L"public")
  , wcstokContext(0)
  {
    toBeEscaped = new WcsSet();
    toBeEscaped->insert(wcsdup(L"\\u"));
    staticPrefixString = className;
    staticPrefixString += L".";
    throwStmtPrefix = L"raise ";
    throwStmtPrefix += staticPrefixString;
    throwStmtPrefix += L"ParseException(";
    writeTracePrefix = staticPrefixString;
    writeTracePrefix += L"writeTrace(";
  }

  virtual ~PrintPython()
  {
    delete toBeEscaped;
  };

  virtual void openFile() {}
  virtual void openClass();
  virtual void openStackNode();
  virtual void closeStackNode();
  virtual void openThread();

  virtual void openMethod(const wchar_t *type,
                          const wchar_t *prefix,
                          const wchar_t *name,
                          const wchar_t *args,
                          bool constant = false,
                          const wchar_t *clazz = 0);
  const wchar_t *publ() const {return L"public";}
  virtual void beginNonpublic() {visibility = L"private";}
  virtual void beginPublic() {visibility = publ();}

  virtual void privateVars();

  const wchar_t *visibilityMethodPrefix() const {
    return wcscmp(visibility, publ()) == 0 && methodPrefix == methodPrefixParse
         ? L"Parse_"
         : methodPrefix;
  }

  void printArgs(const wchar_t *args)
  {
    wchar_t *str = wcsdup(args);
    const wchar_t *delim = L" ,";
    const wchar_t *comma = L"";
    wcstokContext = 0;
    for (wchar_t *type = wcstoken(str, delim, &wcstokContext); type; type = wcstoken(NULL, L" ", &wcstokContext))
    {
      wchar_t *name = wcstoken(NULL, L",", &wcstokContext);
      print(comma);
      print(name);
      print(L" ");
      print(type);
      comma = L", ";
    }
    free(str);
  }

  virtual void close(Grammar *node)
  {
    if (embeddedOutputString == 0)
    {
      internalerr();
    }
    else
    {
      print(embeddedOutputString);
    }
    if (main || performanceTest)
    {
      printReadMethod();
    }
    if (performanceTest)
    {
      printFileProcessor();
    }
    if (main)
    {
      printSimpleMain();
    }
    visitEpilog();
  }

  virtual void printReadMethod();
  virtual void printSimpleMain();
  virtual void printFileProcessor();

  virtual bool isPython() {return true;}

  virtual const wchar_t *deref() const {return L".";}
  virtual const wchar_t *nullPtr() const {return L"None";}
  virtual const wchar_t *beginThrowStmt() const {return throwStmtPrefix.c_str();}
  virtual const wchar_t *endThrowStmt() const {return L")";}
  virtual const wchar_t *endClass() const {return L"";}
  virtual const wchar_t *lineCommentPrefix() const {return L"# ";}
  virtual const wchar_t *inlineCommentIntroducer() const {return L"# ";}
  virtual const wchar_t *stringType() const {return L"string ";}
  virtual const wchar_t *boolType() const {return L"bool ";}
  virtual const wchar_t *intType() const {return L"int ";}
  virtual const wchar_t *voidType() const {return L"void ";}
  virtual const wchar_t *intVar() const {return L"";}
  virtual const wchar_t *intVal() const {return L"";}
  virtual const wchar_t *boolVar() const {return L"bool";}
  virtual const wchar_t *stringIntroducer() const {return L"";}
  virtual const wchar_t *semicolon() const {return L"";}
  virtual const wchar_t *ifLeftParen() const {return L"";}
  virtual const wchar_t *ifRightParen() const {return L":";}
  virtual const wchar_t *elseWithBraces() const {return L"else:";}
  virtual const wchar_t *leftBrace() const {return L"";}
  virtual const wchar_t *rightBrace() const {return L"";}
  virtual const wchar_t *thiz() const {return L"self.";}
  virtual const wchar_t *staticPrefix() const {return staticPrefixString.c_str();}
  virtual const wchar_t *writeTrace() const {return writeTracePrefix.c_str();}

  virtual void printFlush(int i, bool withinThread = false);

  void printInterface();
  void printParseException();
  void printEventHandlerImplementation();
  void printTokenVars();

private:
  const wchar_t *embeddedOutputString;
  const wchar_t *visibility;
  WString staticPrefixString;
  WString throwStmtPrefix;
  WString writeTracePrefix;
  wchar_t *wcstokContext;
};

#endif /* PRINTPYTHON_HPP_ */
