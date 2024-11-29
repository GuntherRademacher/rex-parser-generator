/*
 * PrintScala.hpp
 *
 *  Created on: 03.10.2008
 *      Author: Gunther
 */

#ifndef PRINTSCALA_HPP_
#define PRINTSCALA_HPP_

#include "PrintCLike.hpp"
#include "../common/Platforms.hpp"

#include <string.h>
#include <ctype.h>
#include <stdlib.h>

class PrintScala : public PrintCLike
{                 typedef PrintCLike super;
public:
  PrintScala(char **argv,
             const wchar_t *aClassName,
             const wchar_t *anInterfaceName,
             const wchar_t *someInstanceCode,
             const wchar_t *someStaticCode,
             bool unlimited,
             bool printTree,
             bool omitPosition,
             bool printMain,
             bool performance,
             bool printTrace)
  : PrintCLike(argv,
               JAVA,
               L".scala",
               aClassName,
               anInterfaceName,
               unlimited,
               printTree,
               omitPosition,
               printMain,
               performance,
               printTrace)
  , instanceCode(someInstanceCode)
  , staticCode(someStaticCode)
  , visibility(L"")
  , wcstokContext(0)
  {
    toBeEscaped = new WcsSet();
    toBeEscaped->insert(wcsdup(L"\\u"));
    staticPrefixString = className;
    staticPrefixString += L".";
    throwStatement = L"throw new ";
    throwStatement += staticPrefixString;
    throwStatement += L"ParseException(";
  }

  virtual ~PrintScala()
  {
    delete toBeEscaped;
  };

  virtual void openFile() {}
  virtual void openClass();
  virtual void openStackNode();
  virtual void closeStackNode();
  virtual void openThread();
  virtual void printGlrParseMethod();

  virtual void openMethod(const wchar_t *type,
                          const wchar_t *prefix,
                          const wchar_t *name,
                          const wchar_t *args,
                          bool constant = false,
                          const wchar_t *clazz = 0);
  virtual void beginNonpublic() {visibility = L"private ";}
  virtual void beginPublic() {visibility = L"";}
  virtual const wchar_t *writeTrace() const {return useGlr ? L"parser.writeTrace(" : L"writeTrace(";}

  virtual void privateVars();

  void printArgs(const wchar_t *args)
  {
    wchar_t *str = wcsdup(args);
    const wchar_t *delim = L" ,";
    const wchar_t *comma = L"";
    wcstokContext = 0;
    for (wchar_t *type = wcstoken(str, delim, &wcstokContext); type; type = wcstoken(NULL, L" ", &wcstokContext))
    {
      wchar_t *name = wcstoken(NULL, L",", &wcstokContext);
      wchar_t initial[2] = {type[0], 0};
      if (wcsncmp(type, staticPrefixString.c_str(), staticPrefixString.size())) initial[0] = towupper(initial[0]);
      print(comma);
      print(name);
      print(L": ");
      print(initial);
      print(type + 1);
      comma = L", ";
    }
    free(str);
  }

  virtual void printInstanceCode()
  {
    if (instanceCode == 0)
    {
      internalerr();
    }
    else
    {
      print(instanceCode);
    }
  }

  virtual void close(Grammar *node)
  {
    if (interfaceName.empty())
    {
      printParseException();
    }
    if (main)
    {
      printSimpleMain();
    }
    if (performanceTest)
    {
      printFileProcessor();
    }
    if (main || performanceTest)
    {
      printReadMethod();
    }

    if (staticCode == 0)
    {
      internalerr();
    }
    else
    {
      print(staticCode);
    }

    if (! visitEpilog())
    {
      print(endClass());
      print(L"\n");
    }
  }

  virtual void printReadMethod();
  virtual void printSimpleMain();
  virtual void printFileProcessor();

  virtual bool isScala() {return true;}

  virtual const wchar_t *deref() const {return L".";}
  virtual const wchar_t *nullPtr() const {return L"null";}
  virtual const wchar_t *beginThrowStmt() const {return throwStatement.c_str();}
  virtual const wchar_t *endClass() const {return L"}";}
  virtual const wchar_t *lineCommentPrefix() const {return L"// ";}
  virtual const wchar_t *stringType() const {return L"String ";}
  virtual const wchar_t *boolType() const  {return L"Boolean ";}
  virtual const wchar_t *intType() const {return L"Int ";}
  virtual const wchar_t *voidType() const {return L"";}
  virtual const wchar_t *intVar() const {return L"var ";}
  virtual const wchar_t *intVal() const {return L"val ";}
  virtual const wchar_t *boolVar() const {return L"var";}
  virtual const wchar_t *stringIntroducer() const {return L"";}
  virtual const wchar_t *staticPrefix() const {return staticPrefixString.c_str();}
  virtual const wchar_t *semicolon() const {return L"";}
  virtual const wchar_t *leftBrace() const {return L" {";}
  virtual const wchar_t *leftbracket() const {return L"(";}
  virtual const wchar_t *rightbracket() const {return L")";}
  virtual const wchar_t *returnKeyword() const {return L"";}
  virtual const wchar_t *caseIntroducer() const {return L" =>";}

  virtual void printFlush(int i, bool withinThread = false);

  void printInterface();
  void printParseException();

private:
  const wchar_t *instanceCode;
  const wchar_t *staticCode;
  const wchar_t *visibility;
  WString staticPrefixString;
  WString throwStatement;
  wchar_t *wcstokContext;
};

#endif /* PRINTSCALA_HPP_ */
