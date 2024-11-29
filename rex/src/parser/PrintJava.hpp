/*
 * PrintJava.hpp
 *
 *  Created on: 03.10.2008
 *      Author: Gunther
 */

#ifndef PRINTJAVA_HPP_
#define PRINTJAVA_HPP_

#include "PrintCLike.hpp"

class PrintJava : public PrintCLike
{
public:
  PrintJava(char **argv,
            const wchar_t *aClassName,
            const wchar_t *anInterfaceName,
            const wchar_t *anEmbeddedOutputString,
            bool unlimited,
            bool printTree,
            bool omitPosition,
            bool printMain,
            bool performance,
            bool printTrace,
            int printSaxon)
  : PrintCLike(argv,
               JAVA,
               L".java",
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
  , saxon(printSaxon)
  {
    toBeEscaped = new WcsSet();
    toBeEscaped->insert(wcsdup(L"\\u"));
  }

  virtual ~PrintJava()
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
  virtual void beginNonpublic() {visibility = L"private";}
  virtual void beginPublic() {visibility = L"public";}

  virtual void privateVars();
  virtual void close(Grammar *node)
  {
    if (embeddedOutputString == 0)
    {
      internalerr();
    }
    else
    {
      print(L"\n");
      print(embeddedOutputString);
    }

    if (! visitEpilog())
    {
      print(endClass());
      print(L"\n");
    }
  }

  virtual void printReadMethod();
  virtual void printFileProcessor();

  virtual bool isJava() {return true;}

  virtual const wchar_t *deref() const {return L".";}
  virtual const wchar_t *nullPtr() const {return L"null";}
  virtual const wchar_t *beginThrowStmt() const {return L"throw new ParseException(";}
  virtual const wchar_t *endClass() const {return L"}";}
  virtual const wchar_t *lineCommentPrefix() const {return L"// ";}
  virtual const wchar_t *stringType() const {return L"String ";}
  virtual const wchar_t *boolType() const {return L"boolean ";}
  virtual const wchar_t *intType() const {return L"int ";}
  virtual const wchar_t *voidType() const {return L"void ";}
  virtual const wchar_t *intVar() const {return L"int ";}
  virtual const wchar_t *intVal() const {return L"int ";}
  virtual const wchar_t *boolVar() const {return L"boolean";}
  virtual const wchar_t *stringIntroducer() const {return L"";}

  virtual void printFlush(int i, bool withinThread = false);

  void printInterface();
  void printParseException();
  void printEventHandlerImplementation();

private:
  const wchar_t *embeddedOutputString;
  const wchar_t *visibility;
  int saxon;
};

#endif /* PRINTJAVA_HPP_ */
