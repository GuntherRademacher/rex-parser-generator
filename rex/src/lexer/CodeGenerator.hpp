/*
 * codeGenerator.hpp
 *
 *  Created on: Sep 17, 2009
 *      Author: Gunther
 */

#ifndef CODEGENERATOR_HPP
#define CODEGENERATOR_HPP

#include "../common/CGVariable.hpp"
#include "../common/ItoA.hpp"
#include "../common/Error.hpp"
#include "../common/Math.hpp"
#include "../common/PtrLess.hpp"
#include "../common/WString.hpp"
#include "../common/Decoder.hpp"
#include "../common/Encoder.hpp"
#include "../common/Format.hpp"
#include "../common/OutputFile.hpp"

#include <map>
#include <stdio.h>
#include <string.h>

class VarsInAlphabeticalOrder : public std::map<const char *, CGVariable, PtrLess<char>, Alloc<std::pair<const char *, CGVariable> > >
{                              typedef std::map<const char *, CGVariable, PtrLess<char>, Alloc<std::pair<const char *, CGVariable> > >
                               super;
public:
  VarsInAlphabeticalOrder()
  : super(key_compare(), Alloc<std::pair<const char *, CGVariable> >(__FILE__, __LINE__))
  {}
};

class Size_tVector : public std::vector<size_t, Alloc<size_t> >
{                   typedef std::vector<size_t, Alloc<size_t> >
                    super;
public:
  Size_tVector()
  : super(Alloc<size_t>(__FILE__, __LINE__))
  {}
};

class CodeGenerator
{
protected:
  CodeGenerator(TargetLanguage targetLanguage, FILE *f)
  : targetLanguage(targetLanguage)
  , file(f)
  , encodedOutput(0)
  , indent(0)
  , isJavascript(false)
  , isTypescript(false)
  , isScala(false)
  , isHaxe(false)
  , isGo(false)
  , isPython(false)
  {}

public:

  static CodeGenerator *newInstance(TargetLanguage targetLanguage, FILE *outputFile);

  virtual ~CodeGenerator()
  {
    free(encodedOutput);
  }

  virtual void generateInstanceCode() {};
  virtual void generateStaticCode() = 0;
  virtual void generateCompressedMap() {}
  virtual void generateData() = 0;
  virtual void compressedMap2dAccessor(const char *x, const char *y, int xCount, size_t indent, const char *index, const char *result, const char *map, const int *bits) = 0;
  virtual void compressedMapAccessor(size_t indent, const char *index, const char *result, const char *map, const int *bits) = 0;

  void bind(CGVariable v)
  {
    varsInAlphabeticalOrder.insert(VarsInAlphabeticalOrder::value_type(v.name, v));
    varsInInsertionOrder.push_back(v);
  }

  const char *getEncodedOutput()
  {
    if (encodedOutput == 0)
    {
      encodedOutput = Encoder::encode(output.c_str());
    }
    return encodedOutput;
  }

  const wchar_t *getOutput()
  {
    return output.c_str();
  }

  void clearOutput()
  {
    output.clear();
  }

protected:
  bool defined(const char *name)
  {
    VarsInAlphabeticalOrder::iterator i(varsInAlphabeticalOrder.find(name));
    return i != varsInAlphabeticalOrder.end();
  }

  CGVariable const &variable(const char *name)
  {
    VarsInAlphabeticalOrder::iterator i(varsInAlphabeticalOrder.find(name));
    if (i == varsInAlphabeticalOrder.end())
    {
      fprintf(stderr, "variable %s not found\n", name);
      internalerr();
    }
    return i->second;
  }

  size_t lineLength() const
  {
    if (lfLocation.size() == 0)
    {
      return output.size();
    }
    else
    {
      return output.size() - 1 - lfLocation.back();
    }
  }

  void print(const wchar_t *string, size_t size)
  {
    for (; size;)
    {
      const wchar_t *eol = STRnCHR(string, size, L'\n');
      if (eol == 0)
      {
        output.append(string, size);
        size = 0;
      }
      else
      {
        size_t s = (eol - string) + 1;
        output.append(string, s);
        string += s;
        size -= s;
        lfLocation.push_back(output.size() - 1);
        print(2 * indent, " ");
      }
    }
  }

  void append(const wchar_t *string)
  {
    print(string);
  }

  void print(const wchar_t *string)
  {
    print(string, wcslen(string));
  }

  void print(int i)
  {
    wchar_t a[32];
    print(a, ItoA(i, 10, a, sizeof a * sizeof *a));
  }

  void print(size_t i)
  {
    wchar_t a[32];
    print(a, ItoA(i, 10, a, sizeof a * sizeof *a));
  }

  void print(size_t count, const char *string)
  {
    for (size_t i = 0; i < count; ++i)
    {
      print(string);
    }
  }

  void print(const char *encoded)
  {
    print(encoded, strlen(encoded));
  }

  void print(const char *encoded, size_t size)
  {
    wchar_t *unencoded = Decoder::decode(encoded, size);
    if (unencoded == 0)
    {
      internalerr();
    }
    print(unencoded);
    free(unencoded);
  }

  TargetLanguage targetLanguage;
  FILE *file;
  VarsInAlphabeticalOrder varsInAlphabeticalOrder;
  VarsInInsertionOrder varsInInsertionOrder;
  WString output;
  char *encodedOutput;
  Size_tVector lfLocation;
  size_t indent;
  Format format;
  bool isJavascript;
  bool isTypescript;
  bool isScala;
  bool isHaxe;
  bool isGo;
  bool isPython;
};

class CodeGeneratorCLike : public CodeGenerator
{                         typedef CodeGenerator super;
public:
  CodeGeneratorCLike(TargetLanguage targetLanguage, FILE *f) : super(targetLanguage, f) {}
  virtual ~CodeGeneratorCLike() {}
  void predict();
  void compressedMapAccessor(size_t indent, const char *index, const char *result, const char *map, const int *bits);
  void compressedMap2dAccessor(const char *x, const char *y, int xCount, size_t indent, const char *index, const char *result, const char *map, const int *bits);
};

class CodeGeneratorCpp : public CodeGeneratorCLike
{                       typedef CodeGeneratorCLike super;
public:
  CodeGeneratorCpp(FILE *f) : super(CPP, f) {}
  ~CodeGeneratorCpp() {}
  void generateInstanceCode();
  void generateStaticCode();
  void generateData();
};

class CodeGeneratorHaxe : public CodeGeneratorCLike
{                        typedef CodeGeneratorCLike super;
public:
  CodeGeneratorHaxe(FILE *f) : super(HAXE, f) {}
  ~CodeGeneratorHaxe() {}
  void generateInstanceCode();
  void generateStaticCode();
  void generateData();
};

class CodeGeneratorJava : public CodeGeneratorCLike
{                        typedef CodeGeneratorCLike super;
public:
  CodeGeneratorJava(TargetLanguage targetLanguage, FILE *f) : super(targetLanguage, f) {}
  ~CodeGeneratorJava() {}
  void generateStaticCode();
  void generateCompressedMap();
  void generateData();
  void generateBinarySearch(const char *input, const char *outputPrefix, const char *outputSuffix, const char *map, size_t size);
};

class CodeGeneratorGo : public CodeGeneratorCLike
{                      typedef CodeGeneratorCLike super;
public:
  CodeGeneratorGo(FILE *f) : super(GO, f) {}
  ~CodeGeneratorGo() {}
  void generateStaticCode();
  void generateCompressedMap();
  void generateData();
  void generateBinarySearch(const char *input, const char *outputPrefix, const char *outputSuffix, const char *map, size_t size);
};

class CodeGeneratorPython : public CodeGeneratorCLike
{                          typedef CodeGeneratorCLike super;
public:
  CodeGeneratorPython(FILE *f) : super(PYTHON, f) {}
  ~CodeGeneratorPython() {}
  void generateStaticCode();
  void generateCompressedMap();
  void generateData();
  void generateBinarySearch(const char *input, const char *outputPrefix, const char *outputSuffix, const char *map, size_t size);
};

class CodeGeneratorJavascript : public CodeGeneratorCLike
{                              typedef CodeGeneratorCLike super;
public:
  CodeGeneratorJavascript(FILE *f) : super(JAVASCRIPT, f) {}
  ~CodeGeneratorJavascript() {}
  void generateInstanceCode();
  void generateStaticCode();
  void generateData();
};

class CodeGeneratorScala : public CodeGeneratorCLike
{                         typedef CodeGeneratorCLike super;
public:
  CodeGeneratorScala(FILE *f) : super(SCALA, f) {}
  ~CodeGeneratorScala() {}
  void generateInstanceCode();
  void generateStaticCode();
  void generateData();
};

class CodeGeneratorTypescript : public CodeGeneratorCLike
{                              typedef CodeGeneratorCLike super;
public:
  CodeGeneratorTypescript(FILE *f) : super(TYPESCRIPT, f) {}
  ~CodeGeneratorTypescript() {}
  void generateInstanceCode();
  void generateStaticCode();
  void generateData();
};

class CodeGeneratorXQuery : public CodeGenerator
{                          typedef CodeGenerator super;
public:
  CodeGeneratorXQuery(FILE *f) : super(XQUERY, f) {}
  ~CodeGeneratorXQuery() {}
  void generateStaticCode();
  void compressedMapAccessor(size_t indent, const char *index, const char *result, const char *map, const int *bits);
  void compressedMap2dAccessor(const char *x, const char *y, int xCount, size_t indent, const char *index, const char *result, const char *map, const int *bits);
  void generateData();
};

class CodeGeneratorXSLT : public CodeGenerator
{                        typedef CodeGenerator super;
public:
  CodeGeneratorXSLT(FILE *f) : super(XSLT, f) {}
  ~CodeGeneratorXSLT() {}
  void generateStaticCode();
  void compressedMapAccessor(size_t indent, const char *index, const char *result, const char *map, const int *bits);
  void compressedMap2dAccessor(const char *x, const char *y, int xCount, size_t indent, const char *index, const char *result, const char *map, const int *bits);
  void generateData();
};

inline CodeGenerator *CodeGenerator::newInstance(TargetLanguage targetLanguage, FILE *outputFile)
{
  switch (targetLanguage)
  {
  case XQUERY:     return new CodeGeneratorXQuery    (outputFile); break;
  case HAXE:       return new CodeGeneratorHaxe      (outputFile); break;
  case CSHARP:
  case JAVA:       return new CodeGeneratorJava      (targetLanguage, outputFile); break;
  case JAVASCRIPT: return new CodeGeneratorJavascript(outputFile); break;
  case TYPESCRIPT: return new CodeGeneratorTypescript(outputFile); break;
  case SCALA:      return new CodeGeneratorScala     (outputFile); break;
  case CPP:        return new CodeGeneratorCpp       (outputFile); break;
  case GO:         return new CodeGeneratorGo        (outputFile); break;
  case PYTHON:     return new CodeGeneratorPython    (outputFile); break;
  case XSLT:       return new CodeGeneratorXSLT      (outputFile); break;
  default:
    internalerr();
  }
  return 0;
}

#endif
