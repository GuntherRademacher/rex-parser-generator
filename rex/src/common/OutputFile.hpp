/*
 * OutputFile.hpp
 *
 *  Created on: Sep 17, 2009
 *      Author: Gunther
 */

#ifndef OUTPUTFILE_HPP_
#define OUTPUTFILE_HPP_

#include "WString.hpp"
#include "Encoder.hpp"
#include "RExVersion.hpp"
#include "Format.hpp"

#include <stdio.h>

#define pagehead  "REx Scanner Generator"

enum TargetLanguage
{
  C,
  CPP,
  CSHARP,
  HAXE,
  JAVA,
  JAVASCRIPT,
  TYPESCRIPT,
  SCALA,
  GO,
  PYTHON,
  XQUERY,
  XSLT,
  REX,
  XML,
  EBNF,
  TXT
};

class OutputFile
{
public:
  OutputFile(const char *name, TargetLanguage l, char **argv, bool hf = true, bool versionDecl = true);

  static const char *extension(TargetLanguage l);

  static TargetLanguage targetLanguage(const char *extension);

  virtual ~OutputFile()
  {
    close();
  }

  void print(const wchar_t *string, size_t size)
  {
    if (size)
    {
      buffer.append(string, size);
      if (buffer.size() > 100000)
      {
        flush();
      }
    }
  }

  void print(const wchar_t *string)
  {
    print(string, wcslen(string));
  }

  void flush();

  void close();

  static void printCopyright(FILE *f, const char *separator);

  static const char *commandLineIntroducer();

  static void printHeader(FILE *f, TargetLanguage l, char **argv, bool versionDecl = true, const char* version = "1.0");

  static void printFooter(FILE *f, TargetLanguage l, const char *end = "End");

private:
  FILE *file;
  TargetLanguage language;
  bool headerFooter;
  WString buffer;
};

#endif
