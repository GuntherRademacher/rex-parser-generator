/*
 * PrintHaxe.hpp
 *
 *  Created on: 09.07.2015
 *      Author: Gunther
 */

#ifndef PRINTHAXE_HPP_
#define PRINTHAXE_HPP_

#include "PrintCLike.hpp"

class PrintHaxe : public PrintCLike
{
public:
  PrintHaxe(char **argv,
            const wchar_t *aClassName,
            const wchar_t *anInterfaceName,
            const wchar_t *lexerInstanceCode,
            const wchar_t *lexerStaticCode,
            bool unlimited,
            bool printTree,
            bool omitPosition,
            bool printMain,
            bool performance,
            bool printTrace)
  : PrintCLike(argv,
               HAXE,
               L".hx",
               aClassName,
               anInterfaceName,
               unlimited,
               printTree,
               omitPosition,
               printMain,
               performance,
               printTrace)
  , lexerInstanceCode(lexerInstanceCode)
  , lexerStaticCode(lexerStaticCode)
  , visibility(L"public")
  , currentStaticPrefix(L"")
  , classNamePrefix(0)
  {
    toBeEscaped = new WcsSet();
    toBeEscaped->insert(wcsdup(L"\\u"));
    WString prefix(className);
    prefix += L".";
    classNamePrefix = wcsdup(prefix.c_str());
  }

  virtual ~PrintHaxe()
  {
    delete toBeEscaped;
    delete classNamePrefix;
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
  virtual void beginNonpublic() {visibility = L"private";}
  virtual void beginPublic() {visibility = L"public";}

  virtual void privateVars();
  virtual void close(Grammar *node)
  {
    if (! useGlr)
    {
      if (lexerInstanceCode == 0)
      {
        internalerr();
      }
      else
      {
        print(L"\n");
        print(lexerInstanceCode);
      }
    }

    if (lexerStaticCode == 0)
    {
      internalerr();
    }
    else
    {
      print(L"\n");
      print(lexerStaticCode);
    }

    print(endClass());
    print(L"\n");

    if (interfaceName.empty())
    {
      printParseException();
      printEventHandlerImplementation();
    }

    visitEpilog();
  }

  virtual void printReadMethod();
  virtual void printFileProcessor();

  virtual bool isHaxe() {return true;}

  virtual const wchar_t *deref() const {return L".";}
  virtual const wchar_t *nullPtr() const {return L"null";}
  virtual const wchar_t *beginThrowStmt() const {return L"throw new ParseException(";}
  virtual const wchar_t *endClass() const {return L"}";}
  virtual const wchar_t *lineCommentPrefix() const {return L"// ";}
  virtual const wchar_t *stringType() const {return L"String ";}
  virtual const wchar_t *boolType() const  {return L"Bool ";}
  virtual const wchar_t *intType() const {return L"Int ";}
  virtual const wchar_t *voidType() const {return L"Void ";}
  virtual const wchar_t *intVar() const {return L"var ";}
  virtual const wchar_t *intVal() const {return L"var ";}
  virtual const wchar_t *boolVar() const {return L"var";}
  virtual const wchar_t *stringIntroducer() const {return L"";}
  virtual const wchar_t *writeTrace() const {return L"traceLine += ";}
  virtual const wchar_t *endWriteTrace() const {return L"";}

  virtual const wchar_t *staticPrefix() const {return currentStaticPrefix;}

  void printInterface();
  void printParseException();
  void printEventHandlerImplementation();
  virtual void printGlrParseMethod();

private:
  const wchar_t *lexerInstanceCode;
  const wchar_t *lexerStaticCode;
  const wchar_t *visibility;
  const wchar_t *currentStaticPrefix;
  const wchar_t *classNamePrefix;
};

#endif /* PRINTHAXE_HPP_ */
