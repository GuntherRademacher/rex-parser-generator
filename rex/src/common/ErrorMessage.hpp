/*
 * ErrorMessage.hpp
 *
 *  Created on: 15.04.2018
 *      Author: Gunther
 */

#ifndef ERRORMESSAGE_HPP
#define ERRORMESSAGE_HPP

#include "Strings.hpp"

#include <stdio.h>

template<class CHAR>
void showErrorContext(const CHAR *wquery, const char *file, int offset, const char *error)
{
  int line;
  int column;
  Strings::getLineAndColumn(wquery, offset, &line, &column);
  if (file && file[0] != '{')
  {
    fprintf(stdout, "%s: ", file);
  }
  fprintf(stdout, "%s: line %d, column %d:\n", error, line, column);
  Format format;
  int width = (int) (Format::width(line + 1));
  const int indent = 4;
  for (int j = 0; j < 3; j++)
  {
    if (j == 2)
    {
      for (int c = 0; c < indent; c++)
        fprintf(stdout, " ");
      for (int c = 0; c < column + width; c++)
        fprintf(stdout, "-");
      fprintf(stdout, "^\n");
    }
    WString l = Strings::getLine(wquery, line - 1 + j);
    int size = l.size();
    if (size > 0 && l[0] != '\x1A')
    {
      fprintf(stdout, "%s ", format.toString<char>(line - 1 + j, 10, width + indent));
      for (int j = 0; j < size; j++)
      {
        int c = l[j];
        fprintf(stdout, "%lc", c == 9 ? 32 : c);
      }
      fprintf(stdout, "\n");
    }
  }
}

#endif /* ERRORMESSAGE_HPP */
