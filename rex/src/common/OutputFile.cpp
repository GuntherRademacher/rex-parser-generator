/*
 * OutputFile.cpp
 *
 *  Created on: Jan 19, 2019
 *      Author: Gunther
 */

#include "../common/Memory.hpp"
#include "../common/OutputFile.hpp"
#include "../common/Platforms.hpp"

OutputFile::OutputFile(const char *name, TargetLanguage l, char **argv, bool hf, bool versionDecl)
: file(fopen(name, "wb")), language(l), headerFooter(hf)
{
  if (file == 0)
  {
    perror(name);
    exit(1);
  }

  if (headerFooter)
  {
    printHeader(file, language, argv, versionDecl);
  }
}

const char *OutputFile::extension(TargetLanguage l)
{
  switch (l)
  {
  case C         : return "h";
  case CPP       : return "hpp";
  case CSHARP    : return "cs";
  case HAXE      : return "hx";
  case JAVA      : return "java";
  case JAVASCRIPT: return "js";
  case TYPESCRIPT: return "ts";
  case SCALA     : return "scala";
  case GO        : return "go";
  case PYTHON    : return "py";
  case XQUERY    : return "xquery";
  case REX       : return "rex";
  case XML       : return "xml";
  case XSLT      : return "xslt";
  case TXT       : return "txt";
  case EBNF      : break;
  }
  internalerr();
  return 0;
}

TargetLanguage OutputFile::targetLanguage(const char *extension)
{
  if (strcasecmp(extension, "c"     ) == 0) return C;          else
  if (strcasecmp(extension, "h"     ) == 0) return C;          else
  if (strcasecmp(extension, "cpp"   ) == 0) return CPP;        else
  if (strcasecmp(extension, "cs"    ) == 0) return CSHARP;     else
  if (strcasecmp(extension, "hpp"   ) == 0) return CPP;        else
  if (strcasecmp(extension, "java"  ) == 0) return JAVA;       else
  if (strcasecmp(extension, "js"    ) == 0) return JAVASCRIPT; else
  if (strcasecmp(extension, "ts"    ) == 0) return TYPESCRIPT; else
  if (strcasecmp(extension, "scala" ) == 0) return SCALA;      else
  if (strcasecmp(extension, "go"    ) == 0) return GO;         else
  if (strcasecmp(extension, "xq"    ) == 0) return XQUERY;     else
  if (strcasecmp(extension, "xqy"   ) == 0) return XQUERY;     else
  if (strcasecmp(extension, "xquery") == 0) return XQUERY;     else
  if (strcasecmp(extension, "rex"   ) == 0) return REX;        else
  if (strcasecmp(extension, "xml"   ) == 0) return XML;        else
  if (strcasecmp(extension, "xsl"   ) == 0) return XSLT;       else
  if (strcasecmp(extension, "xslt"  ) == 0) return XSLT;       else
  return TXT;
}

void OutputFile::flush()
{
  const wchar_t *unencoded = buffer.c_str();
  char *encoded = Encoder::encode(unencoded);
  buffer.clear();
  fputs(encoded, file);
  free(encoded);
}

void OutputFile::close()
{
  if (file)
  {
    flush();
    if (headerFooter)
    {
      printFooter(file, language);
    }
    fclose(file);
    file = 0;
  }
}

void OutputFile::printCopyright(FILE *f, const char *separator)
{
  fprintf(f, "REx v%s.%s%sCopyright ", REX_VMAJOR, REX_VMINOR, separator);
//    fprintf(f, "%c%c", 0xc2, 0xa9); // UTF-8 !!
  fprintf(f, "(c)");
  fprintf(f, " 1979-%d by Gunther Rademacher <grd@gmx.net>", REX_YEAR);
}

const char *OutputFile::commandLineIntroducer()
{
  return " REx command line: ";
}

void OutputFile::printHeader(FILE *f, TargetLanguage l, char **argv, bool versionDecl, const char* version)
{
  switch (l)
  {
  case C:
    fprintf(f, "/*");
    break;

  case CPP:
  case CSHARP:
  case HAXE:
  case JAVA:
  case JAVASCRIPT:
  case TYPESCRIPT:
  case SCALA:
  case GO:
  case EBNF:
    fprintf(f, "//");
    break;

  case PYTHON:
  case REX:
    fprintf(f, "#");
    break;

  case XML:
  case XSLT:
    fprintf(f, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
    fprintf(f, "<!--");
    break;

  case XQUERY :
    if (versionDecl)
    {
      fprintf(f, "xquery version \"%s\" encoding \"UTF-8\";\n\n", version);
    }
    fprintf(f, "(:");
    break;

  case TXT:
    break;
  }

  if (l != TXT)
  {
    char date[64];
    Format::dateString(date, sizeof date);
    fprintf(f, " This file");
    fprintf(f, " was generated on %s by ", date);

    printCopyright(f, " which is ");

    switch (l)
    {
    case C:
      fprintf(f, " */\n");
      break;

    case REX:
    case CPP:
    case CSHARP:
    case HAXE:
    case JAVA:
    case JAVASCRIPT:
    case TYPESCRIPT:
    case SCALA:
    case GO:
    case PYTHON:
    case EBNF:
      fprintf(f, "\n");
      break;

    case XML:
    case XSLT:
      fprintf(f, " -->");
      break;

    case XQUERY:
      fprintf(f, " :)\n");
      break;

    case TXT:
      internalerr();
      break;
    }
  }

  if (argv)
  {
    switch (l)
    {
    case C:
      fprintf(f, "/*");
      break;

    case PYTHON:
    case REX:
      fprintf(f, "#");
      break;

    case CPP:
    case CSHARP:
    case HAXE:
    case JAVA:
    case JAVASCRIPT:
    case TYPESCRIPT:
    case SCALA:
    case GO:
    case EBNF:
      fprintf(f, "//");
      break;

    case XML:
    case XSLT:
      fprintf(f, "\n<!--");
      break;

    case XQUERY:
      fprintf(f, "(:");
      break;

    case TXT:
      break;
    }

    if (l != TXT)
    {
      char *commandLine = Format::commandLine(argv + 1);
      fprintf(f, "%s%s", commandLineIntroducer(), commandLine);
      free(commandLine);
    }

    switch (l)
    {
    case C:
      fprintf(f, " */\n");
      break;

    case REX:
    case CPP:
    case CSHARP:
    case HAXE:
    case JAVA:
    case JAVASCRIPT:
    case TYPESCRIPT:
    case SCALA:
    case GO:
    case PYTHON:
    case EBNF:
      break;

    case XML:
    case XSLT:
      fprintf(f, " -->");
      break;

    case XQUERY:
      fprintf(f, " :)");
      break;

    case TXT:
      break;
    }
  }

  if (l != TXT)
  {
    fprintf(f, "\n");
  }
}

void OutputFile::printFooter(FILE *f, TargetLanguage l, const char *end)
{
  switch (l)
  {
  case C:
    fprintf(f,  "\n");
    fprintf(f,  "/*");
    break;

  case CPP:
  case CSHARP:
  case HAXE:
  case JAVA:
  case JAVASCRIPT:
  case TYPESCRIPT:
  case SCALA:
  case GO:
  case EBNF:
    fprintf(f,  "\n");
    fprintf(f,  "//");
    break;

  case XML:
  case XSLT:
    break;

  case XQUERY:
    fprintf(f,  "\n(:");
    break;

  case PYTHON:
  case REX:
    fprintf(f,  "\n#");
    break;
  case TXT:
    break;
  }

  switch (l)
  {
  case XML:
  case XSLT:
    break;
  case C:
  case REX:
  case CPP:
  case CSHARP:
  case HAXE:
  case JAVA:
  case JAVASCRIPT:
  case TYPESCRIPT:
  case SCALA:
  case GO:
  case PYTHON:
  case XQUERY:
  case EBNF:
    fprintf(f, " %s", end);
    break;
  case TXT:
    break;
  }

  switch (l)
  {
  case C:
    fprintf(f, " */");
    break;

  case REX:
  case CPP:
  case CSHARP:
  case HAXE:
  case JAVA:
  case JAVASCRIPT:
  case TYPESCRIPT:
  case SCALA:
  case GO:
  case PYTHON:
  case EBNF:
    break;

  case XML:
  case XSLT:
    break;

  case XQUERY:
    fprintf(f,  " :)");
    break;
  case TXT:
    break;
  }

  switch (l)
  {
  case XML:
  case XSLT:
    break;

  case C:
  case REX:
  case CPP:
  case CSHARP:
  case HAXE:
  case JAVA:
  case JAVASCRIPT:
  case TYPESCRIPT:
  case SCALA:
  case GO:
  case PYTHON:
  case XQUERY:
  case EBNF:
    fprintf(f,  "\n");
    break;
  case TXT:
    break;
  }
}
