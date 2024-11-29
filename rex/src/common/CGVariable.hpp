/*
 * CGVariable.hpp
 *
 *  Created on: 30.10.2010
 *      Author: Gunther
 */

#ifndef CGVARIABLE_HPP
#define CGVARIABLE_HPP

#include "Error.hpp"

#include <vector>

class CGVariable
{
public:
  enum Type {INTEGER, UNSIGNED, STRING, BOOLEAN};

  CGVariable(const char *n, bool v)
  : name(n), longName(0), description(0), type(BOOLEAN), address(0), intValue(0), stringValue(0), boolValue(v), size(1), flags(0)
  {}

  CGVariable(const char *n, int v)
  : name(n), longName(0), description(0), type(INTEGER), address(0), intValue(v), stringValue(0), boolValue(false), size(1), flags(0)
  {}

  CGVariable(const char *n, const int *a, size_t s, const char *l, const char *d, int f = 0)
  : name(n), longName(l), description(d), type(INTEGER), address(a), intValue(0), stringValue(0), boolValue(false), size(s), flags(f)
  {}

  CGVariable(const char *n, const unsigned int *a, size_t s, const char *l, const char *d, int f = 0)
  : name(n), longName(l), description(d), type(UNSIGNED), address(a), intValue(0), stringValue(0), boolValue(false), size(s), flags(f)
  {}

  CGVariable(const char *n, const char *v)
  : name(n), longName(0), description(0), type(STRING), address(0), intValue(0), stringValue(v), boolValue(false), size(1), flags(0)
  {}

  CGVariable(const char *n, const char *const *a, size_t s, const char *l, const char *d)
  : name(n), longName(l), description(d), type(STRING), address(a), intValue(0), stringValue(0), boolValue(false), size(s), flags(0)
  {}

  bool isArray() const {return address != 0;}
  bool hasType(Type t) const {return type == t;}

  bool const &boolean(size_t i = 0) const
  {
    assertType(BOOLEAN, i);
    return isArray() ? ((const bool *) address)[i] : boolValue;
  }

  int const &integer(size_t i = 0) const
  {
    if (type == UNSIGNED)
    {
      assertType(UNSIGNED, i);
    }
    else
    {
      assertType(INTEGER, i);
    }
    return isArray() ? ((const int *) address)[i] : intValue;
  }

  const char *const &string(size_t i = 0) const
  {
    assertType(STRING, i);
    if (isArray())
      return ((const char **) address)[i];
    else
      return stringValue;
  }

  const char *getDescription()
  {
    return description;
  }

  const char *getLongName()
  {
    return longName ? longName : name;
  }

  const char *name;
  const char *longName;
  const char *description;
  Type type;
  const void *address;
  int intValue;
  const char *stringValue;
  bool boolValue;
  size_t size;
  unsigned int flags;

private:
  void assertType(Type t, size_t i = 0) const
  {
    if (type != t || i >= size)
    {
      fprintf(stderr, "\ncannot access index %d, type %d in variable %s, size %d, type %d",
              (int) i, (int) t, name, (int) size, (int) type);
      internalerr();
    }
  }
};

class VarsInInsertionOrder : public std::vector<CGVariable, Alloc<CGVariable> >
{                           typedef std::vector<CGVariable, Alloc<CGVariable> >
                            super;
public:
  VarsInInsertionOrder()
  : super(Alloc<CGVariable>(__FILE__, __LINE__))
  {}
};

#endif /* CGVARIABLE_HPP */
