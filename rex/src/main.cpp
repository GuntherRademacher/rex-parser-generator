#include "common/Memory.hpp"

#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <string>

#include "common/CommandLineParser.hpp"
#include "common/Error.hpp"
#include "lexer/LexerGenerator.hpp"
#include "parser/ParserGenerator.hpp"

int codeTemplate(int argc, char **argv);
int compress(int argc, char **argv);

int main(int argc, char *argv[])
{
again:

  int result = 0;
  CommandLineParser::Arguments args;

  try
  {
    setlocale(LC_CTYPE, "en_US.UTF-8");

    args = CommandLineParser::rewriteCommandLine(argc, argv, result);
    if (result == 0)
    {
      argc = args.size();
      argv = (char **) args.c_str();

      if (argc != 2)
      {
        result = generateParser(argc, argv);
      }
      else
      {
        size_t length = strlen(argv[1]);
        if (   (length >= 4 && strcmp(argv[1] + length - 4, ".rex") == 0)
            || (length >= 2 && argv[1][0] == '{' && argv[1][length - 1] == '}'))
        {
          result = LexerGenerator::main(2, argv);
        }
        else if (length >= 9 && strcmp(argv[1] + length - 9, ".template") == 0
                             && strchr(argv[1], '.') - argv[1] < (int) (length - 9))
        {
          result = codeTemplate(2, argv);
        }
        else if (length >= 14 && strcmp(argv[1] + length - 14, ".java.compress") == 0
                              && strchr(argv[1], '.') - argv[1] < (int) (length - 14))
        {
          result = compress(2, argv);
        }
        else
        {
          result = generateParser(argc, argv);
        }
      }

      const char *flags = getenv("FLAGS");
      if (flags && strchr(flags, 'A'))
      {
        if (strchr(flags, 'P'))
        {
          fprintf(stderr, "again? ");
          fflush(stderr);
          for (;;) if ('\n' == getchar()) break;
        }
        goto again;
      }
    }
  }
  catch (std::bad_alloc &)
  {
    outofmemory();
  }

  CommandLineParser::clearArguments(args);
  return result;
}
