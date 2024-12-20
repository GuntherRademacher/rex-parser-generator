/*
 * SymbolTable.hpp
 *
 *  Created on: 23.04.2009
 *      Author: Gunther
 */

#ifndef SYMBOLTABLE_HPP
#define SYMBOLTABLE_HPP

#include "../common/Platforms.hpp"
#include "stddef.h"
#include <map>

class Rule;
class RangeCharSet;

class SymbolTableEntry
{
public:
  SymbolTableEntry(const char *key, size_t size)
  : size(size),
	rules(0),
    effectiveCharSet(0),
    trailingcontext(0),
    code(-1),
    used(false),
    recursive(false),
    exclusionError(false),
    stack(0),
    complained(false),
    istoken(false),
    ungreedy(false)
  {
    name = Alloc<char>(__FILE__, __LINE__).allocate(size + 1);
    memcpy(name, key, size);
    name[size] = 0;
  }

  char *name;
  size_t size;
  Rule *rules;
  const RangeCharSet *effectiveCharSet;
  SymbolTableEntry *trailingcontext;
  int code;
  bool used;
  bool recursive;
  bool exclusionError;
  SymbolTableEntry *stack;
  bool complained;
  bool istoken;
  bool ungreedy;
};

class SymbolTableKey
{
public:
  SymbolTableKey(const char *p, size_t s) : ptr(p), size(s) {}

private:
  friend class SymbolTableKeyLess;
  const char *ptr;
  size_t size;
};

class SymbolTableKeyLess
{
public:
  SymbolTableKeyLess(bool c) : casesensitive(c) {}

  bool operator()(const SymbolTableKey &lhs, const SymbolTableKey &rhs) const
  {
    if (lhs.size < rhs.size) return true;
    if (lhs.size > rhs.size) return false;
    return casesensitive
         ? strncmp(lhs.ptr, rhs.ptr, lhs.size) < 0
         : strncasecmp(lhs.ptr, rhs.ptr, lhs.size) < 0;
  }

private:
  bool casesensitive;
};

class SymbolTable : private std::map<SymbolTableKey, SymbolTableEntry *, SymbolTableKeyLess, Alloc<std::pair<const SymbolTableKey, SymbolTableEntry *> > >
{                   typedef std::map<SymbolTableKey, SymbolTableEntry *, SymbolTableKeyLess, Alloc<std::pair<const SymbolTableKey, SymbolTableEntry *> > >
                    super;
public:
  SymbolTable(bool casesensitive)
  : super(SymbolTableKeyLess(casesensitive), Alloc<std::pair<const SymbolTableKey, SymbolTableEntry *> >(__FILE__, __LINE__))
  {}

  typedef super::iterator iterator;
  iterator begin() {return super::begin();}
  iterator end() {return super::end();}
  bool empty() {return super::empty();}

  ~SymbolTable();

  SymbolTableEntry *find(const char *key, size_t size = 0)
  {
    iterator i(super::find(SymbolTableKey(key, size ? size : strlen(key))));
    if (i != end())
    {
      return i->second;
    }
    else
    {
      return 0;
    }
  }

  SymbolTableEntry *insertSymbol(const char *key, size_t size)
  {
    iterator i(super::find(SymbolTableKey(key, size)));
    if (i != end())
    {
      return i->second;
    }
    else
    {
      SymbolTableEntry *s = new SymbolTableEntry(key, size);
      insert(value_type(SymbolTableKey(s->name, size), s));
      return s;
    }
  }
};

#endif
