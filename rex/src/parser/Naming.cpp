/*
 * Naming.cpp
 *
 *  Created on: 05.10.2008
 *      Author: Gunther
 */

#include "../common/Memory.hpp"
#include "../common/Format.hpp"
#include "Naming.hpp"
#include "Grammar.hpp"

const wchar_t *Naming::getName(Grammar *grammar, Token::Code code, bool showCode)
{
  Naming &naming = grammar->naming;
  const wchar_t *name = naming[std::pair<Token::Code, bool>(code, showCode)];
  if (name == 0)
  {
    Production *p = grammar->terminalProductionByCode[code];
    wchar_t *newName;
    Format format;

    if (! p->constant)
    {
      if (p->context)
      {
        newName = ALLOCATE_ARRAY(wchar_t, wcslen(p->name) + 1 + wcslen(p->context) + 1);
        wcscpy(newName, p->name);
        wcscat(newName, L"^");
        wcscat(newName, p->context);
      }
      else
      {
        newName = wcsdup(p->name);
      }
    }
    else if (showCode)
    {
      newName = wcsdup(format.toString<wchar_t>(grammar->externalTokenCode[code]));
    }
    else
    {
      wchar_t quote = wcsstr(p->name, L"\'") ? '"' : '\'';
      newName = ALLOCATE_ARRAY(wchar_t, 1 + wcslen(p->name) + format.countOccurrences(p->name, quote) + 2);
      wchar_t *i = p->name;
      wchar_t *o = newName;

      for (wchar_t c = quote; c; )
      {
        *o++ = c;
        c = *i++;
        if (c == quote) *o++ = quote;
      }

      *o++ = quote;
      *o++ = 0;
    }
    name = newName;
    naming[std::pair<Token::Code, bool>(code, showCode)] = name;
  }
  return name;
}
