/*
 * SymbolTable.cpp
 *
 *  Created on: 24.04.2010
 *      Author: Gunther
 */

#include "../common/Memory.hpp"

#include "SymbolTable.hpp"
#include "Syntax.hpp"

SymbolTable::~SymbolTable()
{
  for (iterator i = begin(); i != end(); )
  {
    iterator j(i);
    ++i;
    SymbolTableEntry *s = j->second;
    Rule::deleterules(s->rules);
    char *name = s->name;
    delete s;
    free(name);
  }
  clear();
}
