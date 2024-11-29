/*
 * PrintCSharp.hpp
 *
 *  Created on: 18.12.2012
 *      Author: Gunther
 */

#ifndef PRINTCSHARP_HPP_
#define PRINTCSHARP_HPP_

#include "PrintCLike.hpp"

class PrintCSharp : public PrintCLike
{
public:
  PrintCSharp(char **argv,
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
               CSHARP,
               L".cs",
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
  {
    toBeEscaped = new WcsSet();
    toBeEscaped->insert(wcsdup(L"\\u"));
  }

  virtual ~PrintCSharp()
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
  virtual void close(Grammar *node);

  virtual void printReadMethod();
  virtual void printFileProcessor();

  virtual bool isCSharp() {return true;}

  virtual const wchar_t *deref() const {return L".";}
  virtual const wchar_t *nullPtr() const {return L"null";}
  virtual const wchar_t *beginThrowStmt() const {return L"throw new ParseException(";}
  virtual const wchar_t *endClass() const {return L"}";}
  virtual const wchar_t *lineCommentPrefix() const {return L"// ";}
  virtual const wchar_t *stringType() const {return L"String ";}
  virtual const wchar_t *intType() const {return L"int ";}
  virtual const wchar_t *boolType() const {return L"bool ";}
  virtual const wchar_t *voidType() const {return L"void ";}
  virtual const wchar_t *intVar() const {return L"int ";}
  virtual const wchar_t *intVal() const {return L"int ";}
  virtual const wchar_t *boolVar() const {return L"bool";}
  virtual const wchar_t *stringIntroducer() const {return L"";}
  virtual const wchar_t *writeTrace() const {return useGlr ? L"parser.writeTrace(" : L"writeTrace(";}

  virtual void printFlush(int i, bool withinThread = false);

  void printInterface();
  void printParseException();

private:
  const wchar_t *embeddedOutputString;
  const wchar_t *visibility;
};

#endif /* PRINTCSHARP_HPP_ */
