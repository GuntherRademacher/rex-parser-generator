#include "ParserGenerator.hpp"

#include "../common/Memory.hpp"

#include <stdlib.h>
#include <wchar.h>
#include <time.h>

#include "../common/FileIO.hpp"
#include "../common/Decoder.hpp"
#include "../common/Encoder.hpp"
#include "../common/Format.hpp"
#include "../common/Error.hpp"
#include "../common/ErrorMessage.hpp"
#include "../common/Strings.hpp"
#include "AutomaticSemicolonInsertion.hpp"
#include "EbnfParser.hpp"
#include "Grammar.hpp"
#include "ItemSet.hpp"
#include "LookaheadCompressor.hpp"
#include "PostProcess.hpp"
#include "PrintCpp.hpp"
#include "PrintCSharp.hpp"
#include "PrintEbnf.hpp"
#include "PrintGo.hpp"
#include "PrintPython.hpp"
#include "PrintHaxe.hpp"
#include "PrintJava.hpp"
#include "PrintJavascript.hpp"
#include "PrintREx.hpp"
#include "PrintScala.hpp"
#include "PrintTypescript.hpp"
#include "PrintXML.hpp"
#include "PrintXQuery.hpp"
#include "PrintXSLT.hpp"
#include "ReportConflicts.hpp"

static void usage()
{
  fprintf(stdout, "Usage: REx [OPTION]... [INPUT-FILE]\n");
  fprintf(stdout, "\n");
  fprintf(stdout, "  -ll NUM         use strong-LL(K) algorithm up to K=NUM (default: -ll 3)\n");
  fprintf(stdout, "  -lalr NUM       use LALR(K) algorithm up to K=NUM\n");
  fprintf(stdout, "  -lr NUM         use LR(K) algorithm up to K=NUM\n");
  fprintf(stdout, "  -glalr NUM      use GLR, based on LALR(K) up to K=NUM\n");
  fprintf(stdout, "  -glr NUM        use GLR, based on LR(K) up to K=NUM\n");
  fprintf(stdout, "\n");
  fprintf(stdout, "  -backtrack      allow PEG-style backtracking for LL-conflicts\n");
  fprintf(stdout, "  -asi            handle EcmaScript automatic semicolon insertion (LL(1) only)\n");
  fprintf(stdout, "\n");
  fprintf(stdout, "  -cpp            generate parser in C++\n");
  fprintf(stdout, "  -csharp         generate parser in C#\n");
  fprintf(stdout, "  -go             generate parser in Go\n");
  fprintf(stdout, "  -haxe           generate parser in Haxe\n");
  fprintf(stdout, "  -java           generate parser in Java\n");
  fprintf(stdout, "  -javascript     generate parser in JavaScript\n");
  fprintf(stdout, "  -python         generate parser in Python\n");
  fprintf(stdout, "  -scala          generate parser in Scala\n");
  fprintf(stdout, "  -typescript     generate parser in TypeScript\n");
  fprintf(stdout, "  -xquery         generate parser in XQuery\n");
  fprintf(stdout, "  -xslt           generate parser in XSLT\n");
  fprintf(stdout, "\n");
  fprintf(stdout, "  -char           generate C++ code using UTF-8 char rather than wchar_t\n");
  fprintf(stdout, "  -nolexer        generate code for using an external lexer (Java only)\n");
  fprintf(stdout, "  -saxon          generate Saxon extension function (Java only)\n");
  fprintf(stdout, "  -basex          generate BaseX extension function (Java only)\n");
  fprintf(stdout, "  -interface NAME use interface NAME, or generate it (Java only)\n");
  fprintf(stdout, "\n");
  fprintf(stdout, "  -xml            create XML representation of grammar\n");
  fprintf(stdout, "  -ff             add first and follow sets to XML representation of grammar\n");
  fprintf(stdout, "\n");
  fprintf(stdout, "  -tree           generate code for parse tree or parsing event handler\n");
  fprintf(stdout, "  -trace          generate code for parser and tokenizer trace\n");
  fprintf(stdout, "  -main           generate simple main program\n");
  fprintf(stdout, "  -name NAME      use non-default class name, or module namespace\n");
  fprintf(stdout, "  -performance    generate performance test program\n");
  fprintf(stdout, "  -faster         optimize speed\n");
  fprintf(stdout, "  -smaller        optimize memory consumption\n");
  fprintf(stdout, "\n");
  fprintf(stdout, "  -remake FILE    read command line from generated file and do it again\n");
  fprintf(stdout, "  -version        show REx version\n");
}

int generateParser(int argc, char **argv)
{
  clock_t c0 = clock();

  int status = 1;
  TargetLanguage targetLanguage = REX;

  bool printXML = false;
  bool printREx = false;
  bool printFF = false;
  bool unlimited = false;
  bool printTree = false;
  bool omitPosition = false;
  bool printMain = false;
  bool performance = false;
  bool automaticSemicolonInsertion = false;
  bool printTrace = false;
  bool singleLexer = false;
  bool charParser = false;
  bool quiet = false;
  bool verbose = false;
  bool version = false;
  bool backtrack = false;
  bool smaller = false;
  bool faster = false;
  int saxon = 0;
  bool basex = false;
  bool noThrow = false;
  bool noLexer = false;

  int maxLL = -1;
  int maxLR = -1;
  bool lalr = false;
  bool generalized = false;
  size_t tables = 0;

  wchar_t *variant = 0;

  char *className = 0;
  wchar_t *wClassName = 0;
  wchar_t *wInterfaceName = 0;
  const char *grammarOutputFile = 0;

  char *file = 0;

  size_t count = 0;

  for (char **arguments = argv + 1; *arguments; ++arguments)
  {
    TargetLanguage newTarget = REX;
    const char *flags = "R"; // getenv("FLAGS");

    if (strcmp(*arguments, "-ll") == 0)
    {
      if (*(arguments + 1))
      {
        maxLL = atoi(*++arguments);
      }
    }
    else if (strcmp(*arguments, "-lr") == 0 && flags && strchr(flags, 'R'))
    {
      lalr = false;
      maxLR = 0;
      if (*(arguments + 1) && isdigit(**(arguments + 1)))
      {
        maxLR = atoi(*++arguments);
      }
    }
    else if (strcmp(*arguments, "-glr") == 0 && flags && strchr(flags, 'R'))
    {
      lalr = false;
      generalized = true;
      maxLR = 0;
      if (*(arguments + 1) && isdigit(**(arguments + 1)))
      {
        maxLR = atoi(*++arguments);
      }
    }
    else if (strcmp(*arguments, "-lalr") == 0 && flags && strchr(flags, 'R'))
    {
      lalr = true;
      maxLR = 0;
      if (*(arguments + 1) && isdigit(**(arguments + 1)))
      {
        maxLR = atoi(*++arguments);
      }
    }
    else if (strcmp(*arguments, "-glalr") == 0 && flags && strchr(flags, 'R'))
    {
      lalr = true;
      generalized = true;
      maxLR = 0;
      if (*(arguments + 1) && isdigit(**(arguments + 1)))
      {
        maxLR = atoi(*++arguments);
      }
    }
    else if (strcmp(*arguments, "-backtrack") == 0)
    {
      backtrack = true;
    }
    else if (strcmp(*arguments, "-a") == 0)
    {
      if (*(arguments + 1))
      {
        variant = Format::char2wchar(*++arguments);
      }
    }
    else if (strcmp(*arguments, "-q") == 0)
    {
      quiet = true;
      verbose = false;
    }
    else if (strcmp(*arguments, "-verbose") == 0)
    {
      verbose = true;
      quiet = false;
    }
    else if (strcmp(*arguments, "-version") == 0)
    {
      version = true;

      OutputFile::printCopyright(stdout, "\n");
      fprintf(stdout, "\n");
    }
    else if (strcmp(*arguments, "-u") == 0)
    {
      unlimited = true;
    }
    else if (strcmp(*arguments, "-cpp") == 0)
    {
      newTarget = CPP;
    }
    else if (strcmp(*arguments, "-csharp") == 0)
    {
      newTarget = CSHARP;
    }
    else if (strcmp(*arguments, "-go") == 0)
    {
      newTarget = GO;
    }
    else if (strcmp(*arguments, "-python") == 0)
    {
      newTarget = PYTHON;
    }
    else if (strcmp(*arguments, "-char") == 0)
    {
      charParser = true;
    }
    else if (strcmp(*arguments, "-haxe") == 0)
    {
      newTarget = HAXE;
    }
    else if (strcmp(*arguments, "-java") == 0)
    {
      newTarget = JAVA;
    }
    else if (strcmp(*arguments, "-javascript") == 0)
    {
      newTarget = JAVASCRIPT;
    }
    else if (strcmp(*arguments, "-typescript") == 0)
    {
      newTarget = TYPESCRIPT;
    }
    else if (strcmp(*arguments, "-scala") == 0)
    {
      newTarget = SCALA;
    }
    else if (strcmp(*arguments, "-xquery") == 0)
    {
      newTarget = XQUERY;
    }
    else if (strcmp(*arguments, "-xslt") == 0)
    {
      newTarget = XSLT;
    }
    else if (strcmp(*arguments, "-xml") == 0)
    {
      printXML = true;
    }
    else if (strcmp(*arguments, "-rex") == 0)
    {
      printREx = true;
    }
    else if (strcmp(*arguments, "-ff") == 0)
    {
      printFF = true;
    }
    else if (strcmp(*arguments, "-tree") == 0)
    {
      printTree = true;
    }
    else if (strcmp(*arguments, "-noposition") == 0)
    {
      omitPosition = true;
    }
    else if (strcmp(*arguments, "-main") == 0)
    {
      printMain = true;
    }
    else if (strcmp(*arguments, "-trace") == 0)
    {
      printTrace = true;
    }
    else if (strcmp(*arguments, "-faster") == 0 && ! smaller)
    {
      faster = true;
    }
    else if (strcmp(*arguments, "-smaller") == 0 && ! faster)
    {
      smaller = true;
    }
    else if (strcmp(*arguments, "-performance") == 0)
    {
      performance = true;
    }
    else if (strcmp(*arguments, "-asi") == 0)
    {
      automaticSemicolonInsertion = true;
    }
    else if (strcmp(*arguments, "-name") == 0 && *(arguments + 1))
    {
      className = strdup(*++arguments);
    }
    else if (strcmp(*arguments, "-interface") == 0 && *(arguments + 1))
    {
      wInterfaceName = Format::char2wchar(*++arguments);
    }
    else if (strcmp(*arguments, "-saxon") == 0)
    {
      saxon = 110;
    }
    else if (strcmp(*arguments, "-saxon99") == 0)
    {
      saxon = 99;
    }
    else if (strcmp(*arguments, "-saxon10") == 0)
    {
      saxon = 100;
    }
    else if (strcmp(*arguments, "-saxon11") == 0)
    {
      saxon = 110;
    }
    else if (strcmp(*arguments, "-basex") == 0)
    {
      basex = true;
    }
    else if (strncmp(*arguments, "-t", 2) == 0 && strlen(*arguments) == 2)
    {
      tables = 2;
    }
    else if (strncmp(*arguments, "-t", 2) == 0 && atoi(*arguments + 2) > 0)
    {
      tables = atoi(*arguments + 2);
    }
    else if (strcmp(*arguments, "-nothrow") == 0)
    {
      noThrow = true;
    }
    else if (strcmp(*arguments, "-nolexer") == 0)
    {
      noLexer = true;
    }
    else if (strcmp(*arguments, "-contextindependentlexer") == 0)
    {
      singleLexer = true;
    }
    else if (strcmp(*arguments, "-grammar") == 0 && *(arguments + 1))
    {
      grammarOutputFile = *++arguments;
    }
    else if (**arguments == '-')
    {
      fprintf(stdout, "unknown option: %s\n", *arguments);
      fflush(stdout);
      status = -1;
      break;
    }
    else
    {
      count++;
      file = *arguments;
    }

    if (maxLR == 0)
    {
      fprintf(stdout, "lookahead size must be at least 1\n");
      fflush(stdout);
      status = -1;
      break;
    }

    if (newTarget != REX)
    {
      if (targetLanguage != REX)
      {
        fprintf(stdout, "more than one target language specification\n");
        fflush(stdout);
        status = -1;
        break;
      }
      else
      {
        targetLanguage = newTarget;
      }
    }

    if (backtrack && targetLanguage == GO)
    {
      noThrow = true;
    }
  }

  if (status < 0)
  {
    status = 1;
  }
  else if (count > 1)
  {
    fprintf(stdout, "more than one input file specification\n");
    fflush(stdout);
  }
  else if (performance && targetLanguage != CPP
                       && targetLanguage != CSHARP
                       && targetLanguage != GO
                       && targetLanguage != PYTHON
                       && targetLanguage != HAXE
                       && targetLanguage != JAVA
                       && targetLanguage != JAVASCRIPT
                       && targetLanguage != SCALA
                       && targetLanguage != TYPESCRIPT)
  {
    fprintf(stdout, "missing option: -performance also requires -cpp, -csharp, -go, -haxe, -java, -javascript, -python, -scala, or -typescript\n");
    fflush(stdout);
  }
  else if (performance && printMain)
  {
    fprintf(stdout, "can only generate code for either -main or -performance, not for both\n");
    fflush(stdout);
  }
  else if (noThrow && ! backtrack)
  {
    fprintf(stdout, "missing option: -nothrow also requires -backtrack\n");
    fflush(stdout);
  }
  else if (backtrack && maxLR >= 0)
  {
    fprintf(stdout, "option -backtrack can be used with -ll only\n");
    fflush(stdout);
  }
  else if (noThrow && targetLanguage != CPP
                   && targetLanguage != CSHARP
                   && targetLanguage != GO
                   && targetLanguage != PYTHON
                   && targetLanguage != HAXE
                   && targetLanguage != JAVA
                   && targetLanguage != JAVASCRIPT
                   && targetLanguage != SCALA
                   && targetLanguage != TYPESCRIPT)
  {
    fprintf(stdout, "missing option: -nothrow also requires -cpp, -haxe, -java, -scala, -python, -csharp, -javascript, or typescript\n");
    fflush(stdout);
  }
  else if (saxon && targetLanguage != JAVA)
  {
    fprintf(stdout, "missing option: -saxon also requires -java\n");
    fflush(stdout);
  }
  else if (basex && targetLanguage != JAVA)
  {
    fprintf(stdout, "missing option: -basex also requires -java\n");
    fflush(stdout);
  }
  else if (wInterfaceName && targetLanguage != JAVA)
  {
    fprintf(stdout, "missing option: -interface also requires -java\n");
    fflush(stdout);
  }
  else if (noLexer && targetLanguage != JAVA && targetLanguage != REX)
  {
    fprintf(stdout, "missing option: -nolexer only supported for -java or -javascript\n");
    fflush(stdout);
  }
  else if (automaticSemicolonInsertion && ! (maxLL == 1 && backtrack))
  {
    fprintf(stdout, "missing option: -asi only supported for -ll 1 with -backtrack\n");
    fflush(stdout);
  }
  else if (count == 0 && wInterfaceName)
  {
    switch (targetLanguage)
    {
    case HAXE:
      {
        PrintHaxe ph(argv, wInterfaceName, wInterfaceName, 0, 0, unlimited, printTree, omitPosition, printMain, performance, printTrace);
        ph.setNoLexer(noLexer);
        ph.setLrParser(maxLR >= 0);
        ph.setUseGlr(generalized);
        ph.printInterface();
      }
      break;

    case JAVA:
      {
        PrintJava pj(argv, wInterfaceName, wInterfaceName, 0, unlimited, printTree, omitPosition, printMain, performance, printTrace, saxon);
        pj.setNoLexer(noLexer);
        pj.setLrParser(maxLR >= 0);
        pj.setUseGlr(generalized);
        pj.printInterface();
      }
      break;

    case GO:
      {
        PrintGo pg(argv, wInterfaceName, wInterfaceName, 0, unlimited, printTree, omitPosition, printMain, performance, printTrace);
        pg.setNoLexer(noLexer);
        pg.setLrParser(maxLR >= 0);
        pg.setUseGlr(generalized);
        pg.printInterface();
      }
      break;

    case PYTHON:
      {
        PrintPython pp(argv, wInterfaceName, wInterfaceName, 0, unlimited, printTree, omitPosition, printMain, performance, printTrace);
        pp.setNoLexer(noLexer);
        pp.setLrParser(maxLR >= 0);
        pp.setUseGlr(generalized);
        pp.printInterface();
      }
      break;

    case SCALA:
      {
        PrintScala ps(argv, wInterfaceName, wInterfaceName, 0, 0, unlimited, printTree, omitPosition, printMain, performance, printTrace);
        ps.setNoLexer(noLexer);
        ps.setLrParser(maxLR >= 0);
        ps.setUseGlr(generalized);
        ps.printInterface();
      }
      break;

    case CPP:
      {
        PrintCpp pc(argv, wInterfaceName, wInterfaceName, 0, 0, unlimited, printTree, omitPosition, printMain, performance, printTrace, charParser);
        pc.setNoLexer(noLexer);
        pc.setLrParser(maxLR >= 0);
        pc.setUseGlr(generalized);
        pc.printInterface();
      }
      break;

    case CSHARP:
      {
        PrintCSharp ps(argv, wInterfaceName, wInterfaceName, 0, unlimited, printTree, omitPosition, printMain, performance, printTrace);
        ps.setNoLexer(noLexer);
        ps.setLrParser(maxLR >= 0);
        ps.setUseGlr(generalized);
        ps.printInterface();
      }
      break;

    default:
      internalerr();
      break;
    }
    status = 0;
  }
  else if (count < 1)
  {
    if (! version)
    {
      usage();
    }
    fflush(stdout);
  }
  else if (maxLL > 0 && maxLR >= 0)
  {
    printf("not prepared to create LL and LR parsers in a single run");
  }
  else
  {
    if (maxLL < 0 && maxLR < 0)
    {
      maxLL = CheckLL::DEFAULTMAXLL;
    }
    else if (maxLL < 0)
    {
      maxLL = 0;
    }

    char *query = 0;
    query = FileIO::getContent(file);

    if (query == 0)
    {
      fprintf(stdout, "file not found: %s\n", file);
      fflush(stdout);
    }
    else
    {
      wchar_t *wquery = 0;
      wquery = Decoder::decode(query);

#if SELFTEST
      char *testQuery = Encoder::encode(wquery);
      char *originalQuery = query;
      if (   ((const unsigned char *) query)[0] == 0xef
          && ((const unsigned char *) query)[1] == 0xbb
          && ((const unsigned char *) query)[2] == 0xbf)
      {
        originalQuery += 3;
      }
      if (strcmp(originalQuery, testQuery))
      {
        printf("input file encoding error - input is not UTF-8\n");
#if 0
        printf("strcmp %d\n", strcmp(query, testQuery));
        printf("wcslen(wquery) %d\n", wcslen(wquery));
        printf("strlen(testQuery) %d\n", strlen(testQuery));
        printf("strlen(query) %d\n", strlen(query));

        printf("t: %s\n", testQuery);
        printf("q: %s\n", query);
#endif
        exit(1);
      }
      free(testQuery);
#endif

      if (wquery == 0)
      {
        fprintf(stdout, "invalid encoding: %s\n", file);
        fflush(stdout);
      }
      else
      {
        wchar_t *wFileName = 0;
        wFileName = Format::char2wchar(file);
        Grammar *grammar = 0;

        try
        {
          EbnfParser p;

          grammar = p.parse(wquery, wFileName);

          if (className == 0)
          {
            className = Format::newFileName(file, "");
          }
          wClassName = Format::char2wchar(className);

          try
          {
            grammar->faster = faster;
            grammar->smaller = smaller;
            grammar->noLexer = noLexer;
            grammar->singleLexer = singleLexer;
            grammar->basex = basex;
            grammar->noThrow = noThrow;
            grammar->tables = tables;
            grammar->verbose = verbose;
            grammar->quiet = quiet;
            grammar->variant = variant;

            PostProcess pp(maxLL, maxLR);
            grammar->accept(pp);

//          for (int i = 0; i <= grammar->maxNonterminalCode; ++i)
//          {
//            wprintf(L"  %3d %ls\n", i, grammar->nonterminalProductionByCode[i]->name);
//          }

            if (automaticSemicolonInsertion)
            {
              AutomaticSemicolonInsertion asi;
              grammar->accept(asi);
            }

            if (grammarOutputFile != 0)
            {
              PrintEbnf pe(PrintEbnf::ALL);
              pe.print(grammarOutputFile, argv, className, grammar);
            }

            if (maxLR >= 0 || maxLL)
            {
              if (maxLR >= 0)
              {
                if (printTree && grammar->maxImplicitNonterminalCode > grammar->maxNonterminalCode)
                {
                  throw Complaint(L"Code annotations only supported at end of production", L" when combined with tree generation for LR");
                }

                grammar->maxK = maxLR;
                grammar->states = new LrStates(grammar, lalr);
                grammar->states->generate();

                const wchar_t *parserType = lalr ? L"LALR" : L"LR";

                if (grammar->states->getConflicts()->empty())
                {
                  if (! quiet) fwprintf(stdout, L"grammar is %ls(%d)\n", parserType, (int) grammar->k);
                }
                else if (generalized)
                {
                  grammar->useGlr = true;
                  if (! quiet)
                  {
                    int conflictCount = grammar->states->getConflicts()->size();
                    fwprintf(stdout, L"%d %ls(%d)-conflict%ls handled by G%ls processing\n", conflictCount, parserType, (int) grammar->k, conflictCount == 1 ? L"" : L"s", parserType);
                    if ((int) grammar->k < maxLR)
                    {
                      fwprintf(stdout, L"used lookahead %d, because extending to %d did not resolve any %ls(%d) conflicts\n", (int) grammar->k, maxLR, parserType, (int) grammar->k);
                    }
                  }
                }
                else
                {
                  ReportConflicts rc(parserType, grammar->k, false);
                  rc.report(grammar->states->getConflicts(), grammar);

                  int conflictCount = grammar->states->getConflicts()->size();
                  fwprintf(stdout, L"%d %ls(%d)-conflict%ls\n", conflictCount, parserType, (int) grammar->k, conflictCount == 1 ? L"" : L"s");
                  if ((int) grammar->k < maxLR)
                  {
                    fwprintf(stdout, L"extending lookahead to %d did not resolve any %ls(%d) conflicts\n", maxLR, parserType, (int) grammar->k);
                  }

                  WString label(parserType);
                  label += L"(";
                  label += Format().toString<wchar_t>(maxLR);
                  label += L")";

//                  wprintf(L"number of LR(%d) states: %d", lalr ? 0 : grammar->k, grammar->states->size());
//                  wprintf(L", %d with %d conflicts", grammar->states->getConflictingStates(), conflictCount, label.c_str());
//                  wprintf(L"\n");

                  throw Complaint(L"grammar fails to be ", label);
                }
              }
              else // maxLL
              {
                grammar->maxK = maxLL;
                CheckLL checkLL;
                grammar->accept(checkLL);

                const wchar_t *parserType = grammar->k == 1 ? L"LL" : L"strong-LL";

                LookaheadCompressor lc;

                if (grammar->conflictCount == 0)
                {
                  grammar->accept(lc);

                  if (! quiet) fwprintf(stdout, L"grammar is %ls(%d)\n", parserType, (int) grammar->k);
                  fflush(stdout);
                }
                else if (backtrack)
                {
                  grammar->accept(lc);
                  if (! quiet) fwprintf(stdout, L"%d %ls(%d)-conflict%ls handled by backtracking\n", grammar->conflictCount, parserType, (int) grammar->k, grammar->conflictCount == 1 ? L"" : L"s");
                }
                else
                {
                  ReportConflicts rc(parserType, grammar->k, printFF);
                  grammar->accept(rc);

                  WString label(parserType);
                  label += L"(";
                  label += Format().toString<wchar_t>(grammar->k);
                  label += L")";
                  throw Complaint(L"grammar fails to be ", label);
                }
              }
            }
          }
          catch (Complaint)
          {
            if (printXML)
            {
              PrintXML pxml(argv, className, printFF);
              pxml.dump(grammar, grammar->k);
            }

            throw;
          }

          if (printXML)
          {
            PrintXML pxml(argv, className, printFF);
            pxml.dump(grammar, grammar->k);
          }

          unlimited = unlimited || grammar->k * grammar->tokenSequenceFactory->tokenBits() > static_cast<int>(sizeof(int) * 8 - 1);

          PrintREx pr(argv, wClassName, targetLanguage, charParser, printTrace, printTree, printREx, unlimited, verbose);
          if (maxLL || maxLR >= 0)
          {
            grammar->accept(pr);

            switch (targetLanguage)
            {
            case HAXE:
              {
                PrintHaxe ph(argv, wClassName, wInterfaceName, pr.getInstanceCode(), pr.getStaticCode(), unlimited, printTree, omitPosition, printMain, performance, printTrace);
                grammar->accept(ph);
              }
              break;
            case JAVA:
              {
                PrintJava pj(argv, wClassName, wInterfaceName, pr.getStaticCode(), unlimited, printTree, omitPosition, printMain, performance, printTrace, saxon);
                grammar->accept(pj);
              }
              break;
            case GO:
              {
                PrintGo pg(argv, wClassName, wInterfaceName, pr.getStaticCode(), unlimited, printTree, omitPosition, printMain, performance, printTrace);
                grammar->accept(pg);
              }
              break;
            case PYTHON:
              {
                PrintPython pg(argv, wClassName, wInterfaceName, pr.getStaticCode(), unlimited, printTree, omitPosition, printMain, performance, printTrace);
                grammar->accept(pg);
              }
              break;
            case SCALA:
              {
                PrintScala ps(argv, wClassName, wInterfaceName, pr.getInstanceCode(), pr.getStaticCode(), unlimited, printTree, omitPosition, printMain, performance, printTrace);
                grammar->accept(ps);
              }
              break;
            case JAVASCRIPT:
              {
                PrintJavascript pjs(argv, wClassName, pr.getInstanceCode(), pr.getStaticCode(), unlimited, printTree, omitPosition, printMain, performance, printTrace);
                grammar->accept(pjs);
              }
              break;
            case TYPESCRIPT:
              {
                PrintTypescript pts(argv, wClassName, pr.getInstanceCode(), pr.getStaticCode(), unlimited, printTree, omitPosition, printMain, performance, printTrace);
                grammar->accept(pts);
              }
              break;
            case CPP:
              {
                PrintCpp pc(argv, wClassName, wInterfaceName, pr.getInstanceCode(), pr.getStaticCode(), unlimited, printTree, omitPosition, printMain, performance, printTrace, charParser);
                grammar->accept(pc);
              }
              break;
            case CSHARP:
              {
                PrintCSharp ps(argv, wClassName, wInterfaceName, pr.getStaticCode(), unlimited, printTree, omitPosition, printMain, performance, printTrace);
                grammar->accept(ps);
              }
              break;
            case XQUERY:
              {
                PrintXQuery px(argv, wClassName, pr.getStaticCode(), unlimited, printTree, omitPosition, printMain, printTrace);
                grammar->accept(px);
              }
              break;
            case XSLT:
              {
                PrintXSLT px(argv, wClassName, pr.getStaticCode(), unlimited, printTree, omitPosition, printMain, printTrace);
                grammar->accept(px);
              }
              break;
            case REX:
              {
              }
              break;
            default:
              internalerr();
              break;
            }
          }

          status = 0;
        }
        catch (Complaint &c)
        {
          if (c.offset >= 0)
          {
            showErrorContext(wquery, file, c.offset, "error");
            fwprintf(stdout, L"  ");
          }
          if (c.msg.c_str())
          {
            fwprintf(stdout, L"%ls%ls\n", c.msg.c_str(), c.name.c_str());
          }
        }
        catch (EbnfParser::ParseException &pe)
        {
          showErrorContext(wquery, file, pe.getEnd(), "syntax error");
          const wchar_t *token = EbnfParser::getOffendingToken(pe);
          if (token)
          {
            fwprintf(stdout, L"  found:\n");
            fwprintf(stdout, L"    %ls\n", token);
          }
          fwprintf(stdout, L"  expected:\n");

          const wchar_t *expected[64];
          EbnfParser::getExpectedTokenSet(pe, expected, sizeof expected / sizeof *expected);

          int limit = 16;
          for (const wchar_t **e = expected; *e; ++e)
          {
            if (--limit)
            {
              fwprintf(stdout, L"    %ls\n", *e);
            }
            else
            {
              fwprintf(stdout, L"    ...\n");
              break;
            }
          }
          fflush(stdout);
        }

        delete grammar;

        free(wFileName);
        free(wquery);
      }
      free(query);
    }
  }

  free(variant);
  free(wClassName);
  free(className);
  free(wInterfaceName);

  if (verbose)
  {
    double elapsed = (double) (clock() - c0) / CLOCKS_PER_SEC;
    fwprintf(stdout, L"completed in %.0f msec\n", elapsed * 1000.0);
  }

  return status;
}
