/*
 * PrintCpp.hpp
 *
 *  Created on: 03.10.2008
 *      Author: Gunther
 */

#ifndef PRINTCPP_HPP_
#define PRINTCPP_HPP_

#include "PrintCLike.hpp"

class PrintCpp : public PrintCLike
{
public:
  PrintCpp(char **argv,
           const wchar_t *aClassName,
           const wchar_t *anInterfaceName,
           const wchar_t *lexerInstanceCode,
           const wchar_t *lexerStaticCode,
           bool unlimited,
           bool printTree,
           bool omitPosition,
           bool printMain,
           bool performance,
           bool printTrace,
           bool charParser)
  : PrintCLike(argv,
               CPP,
               printMain || performance ? L".cpp" : L".hpp",
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
  , parseChars(charParser)
  {
  }

  virtual ~PrintCpp() {}

  virtual void openFile();
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
  virtual void beginNonpublic();
  virtual void beginPublic();
  virtual void privateVars();

  virtual void close(Grammar *node);

  virtual void printReadMethod();
  virtual void printFileProcessor();

  virtual bool isCpp() {return true;}

  virtual const wchar_t *deref() const {return L"->";}
  virtual const wchar_t *nullPtr() const {return L"0";}
  virtual const wchar_t *beginThrowStmt() const {return L"throw ParseException(";}
  virtual const wchar_t *endClass() const {return L"};";}
  virtual const wchar_t *lineCommentPrefix() const {return L"#";}
  virtual const wchar_t *stringType() const {return parseChars ? L"const char *" : L"const wchar_t *";}
  virtual const wchar_t *boolType() const {return L"bool ";}
  virtual const wchar_t *intType() const {return L"int ";}
  virtual const wchar_t *voidType() const {return L"void ";}
  virtual const wchar_t *intVar() const {return L"int ";}
  virtual const wchar_t *intVal() const {return L"int ";}
  virtual const wchar_t *boolVar() const {return L"bool";}
  virtual const wchar_t *stringIntroducer() const {return parseChars ? L"" : L"L";}
  virtual const wchar_t *arrow() const {return L"->";}

  void printInterface();

private:
  void printIfndef(bool define, const wchar_t *qualifier);
  void printEndif();
  void printSimpleMain();
  void printPerformanceMain();
  void printPerformanceCode();

  const wchar_t *lexerInstanceCode;
  const wchar_t *lexerStaticCode;
  bool parseChars;
};

#endif /* PRINTCPP_HPP_ */
