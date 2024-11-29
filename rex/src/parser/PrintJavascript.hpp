/*
 * PrintJavascript.hpp
 *
 *  Created on: 03.10.2008
 *      Author: Gunther
 */

#ifndef PRINTJAVASCRIPT_HPP_
#define PRINTJAVASCRIPT_HPP_

#include "PrintCLike.hpp"

class PrintJavascript : public PrintCLike
{
public:
  PrintJavascript(char **argv,
                  const wchar_t *aClassName,
                  const wchar_t *lexerInstanceCode,
                  const wchar_t *lexerStaticCode,
                  bool unlimited,
                  bool printTree,
                  bool omitPosition,
                  bool printMain,
                  bool performance,
                  bool printTrace)
  : PrintCLike(argv,
               JAVASCRIPT,
               L".js",
               aClassName,
               0,
               unlimited,
               printTree,
               omitPosition,
               printMain,
               performance,
               printTrace)
  , lexerInstanceCode(lexerInstanceCode)
  , lexerStaticCode(lexerStaticCode)
  , isPublic(true)
  {
    staticPrefixString = className;
    staticPrefixString += L".";
  }

  virtual ~PrintJavascript() {};
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
  virtual void beginNonpublic() {isPublic = false;}
  virtual void beginPublic() {isPublic = true;}

  virtual void privateVars();
  virtual void close(Grammar *node);

  virtual void printReadMethod();
  virtual void printFileProcessor();
  virtual void printXmlSerializer();

  virtual bool isJavascript() {return true;}

  virtual const wchar_t *deref() const {return L".";}
  virtual const wchar_t *nullPtr() const {return L"null";}
  virtual const wchar_t *beginThrowStmt() const {return L"throw new thisParser.ParseException(";}
  virtual const wchar_t *endClass() const {return L"";}
  virtual const wchar_t *lineCommentPrefix() const {return L"// ";}
  virtual const wchar_t *stringType() const {return L"";}
  virtual const wchar_t *boolType() const  {return L"";}
  virtual const wchar_t *intType() const {return L"";}
  virtual const wchar_t *voidType() const {return L"";}
  virtual const wchar_t *intVar() const {return L"var ";}
  virtual const wchar_t *intVal() const {return L"var ";}
  virtual const wchar_t *boolVar() const {return L"var";}
  virtual const wchar_t *stringIntroducer() const {return L"";}
  virtual const wchar_t *staticPrefix() const {return staticPrefixString.c_str();}

  virtual void printFlush(int i, bool withinThread = false);

private:
  void printPlatformSpecific();

  const wchar_t *lexerInstanceCode;
  const wchar_t *lexerStaticCode;
  bool isPublic;
  WString staticPrefixString;
};

#endif /* PRINTJAVASCRIPT_HPP_ */
