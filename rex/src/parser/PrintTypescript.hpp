/*
 * PrintTypescript.hpp
 *
 *  Created on: 21.08.2014
 *      Author: Gunther
 */

#ifndef PRINTTYPESCRIPT_HPP_
#define PRINTTYPESCRIPT_HPP_

#include "PrintCLike.hpp"

class PrintTypescript : public PrintCLike
{
public:
  PrintTypescript(char **argv,
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
               TYPESCRIPT,
               L".ts",
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
  , needTokenFunction(false)
  , needTokenSequenceFunction(false)
  {
  }

  virtual ~PrintTypescript() {};
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
  virtual void printGlrParseMethod();

  virtual void privateVars();
  virtual void close(Grammar *node);

  virtual void printReadMethod();
  virtual void printFileProcessor();

  virtual bool isTypescript() {return true;}

  virtual const wchar_t *deref() const {return L".";}
  virtual const wchar_t *nullPtr() const {return L"null";}
  virtual const wchar_t *beginThrowStmt() const {return L"throw new ParseException(";}
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
  virtual const wchar_t *thiz() const {return L"this.";}
  virtual const wchar_t *staticPrefix() const {return L"Parser.";}
  virtual const wchar_t *writeTrace() const {return useGlr ? L"parser.writeTrace(" : L"this.writeTrace(";}

  virtual const wchar_t *token()
  {
    needTokenFunction = true;
    return L"token()";
  }

  virtual const wchar_t *tokenSequence()
  {
    needTokenSequenceFunction = true;
    return L"tokenSequence()";
  }

  virtual void printFlush(int i, bool withinThread = false);

private:
  void printPlatformSpecific();

  const wchar_t *lexerInstanceCode;
  const wchar_t *lexerStaticCode;
  bool isPublic;
  bool needTokenFunction;
  bool needTokenSequenceFunction;
};

#endif /* PRINTTYPESCRIPT_HPP_ */
