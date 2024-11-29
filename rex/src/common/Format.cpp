/*
 * Format.cpp
 *
 *  Created on: 15.02.2014
 *      Author: Gunther
 */

#include "../common/Memory.hpp"
#include "../common/Strings.hpp"
#include "Format.hpp"

static void trim(WString &string)
{
  // trim trailing spaces
  size_t found = string.find_last_not_of(L' ');
  if (found != WString::npos)
  {
    string.erase(found + 1);
  }
  else
  {
    string.clear();
  }
}

int Format::indentation(const wchar_t *string)
{
  int indentation = INT_MAX;
  int spaces = -1;
  for (const wchar_t *input = string; *input; ++input)
  {
    switch (*input)
    {
    case L' ':
      if (spaces >= 0) spaces++;
      break;
    case L'\n':
      spaces = 0;
      break;
    default:
      if (spaces >= 0 && spaces < indentation) indentation = spaces;
      spaces = -1;
      break;
    }
  }
  return indentation == INT_MAX ? -1 : indentation;
}

wchar_t *Format::reIndent(const wchar_t *string, size_t newIndentation, bool incremental)
{
  WString wstring(string);
  return wcsdup(reIndent(wstring, newIndentation, incremental).c_str());
}

WString Format::reIndent(const WString string, size_t newIndentation, bool incremental)
{
  int oldIndentation = indentation(string.c_str());
  if (oldIndentation < 0)
  {
    return string;
  }
  else
  {
    WString result;
    for (const wchar_t *input = string.c_str(); ;++input)
    {
      size_t inputLength = Strings::lineLength(input);

      const wchar_t *output = input;
      int outputLength = inputLength;

      // skip old indentation, apply new indentation (except for first line)

      if (input != string)
      {
        result += '\n';

        // skip
        output += oldIndentation;
        outputLength -= oldIndentation;

        // indent
        if (outputLength > 0)
        {
          result.append(newIndentation, L' ');
        }
      }

      // copy

      if (outputLength > 0)
      {
        result.append(output, outputLength);
        trim(result);
      }

      input += inputLength;
      if (*input == 0)
      {
        break;
      }
    }
    return result;
  }
}
