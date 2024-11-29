/*
 * PrintVisitor.h
 *
 *  Created on: 30.11.2014
 *      Author: Gunther
 */

#ifndef SRC_PARSER_PRINTVISITOR_HPP_
#define SRC_PARSER_PRINTVISITOR_HPP_

#include "Grammar.hpp"

class PrintVisitor : public Visitor
{
public:
  PrintVisitor() : lineNo(1), indent(0) {}
  virtual ~PrintVisitor() {}

  size_t size() const
  {
    return output.size();
  }

  const wchar_t *content() const
  {
    return output.c_str();
  }

  void print(const wchar_t *string, size_t size)
  {
    while (size)
    {
      const wchar_t *eol = STRnCHR(string, size, L'\n');
      if (eol == 0)
      {
        output.append(string, size);
        size = 0;
      }
      else
      {
        size_t s = eol - string;
        if (s) output.append(string, s);
        output.rtrim().append(L"\n", 1);
        ++s;
        string += s;
        size -= s;
        ++lineNo;
        print(getIndent(), L" ", 1);
      }
    }
  }

  void append(const wchar_t *string)
  {
    print(string);
  }

  void print(const wchar_t *string)
  {
    print(string, wcslen(string));
  }

  void print(size_t count, const wchar_t *string, size_t size)
  {
    for (size_t i = 0; i < count; ++i)
    {
      print(string, size);
    }
  }

  void print(size_t count, const wchar_t *string)
  {
    print(count, string, wcslen(string));
  }

  void printIndented(int offset, const wchar_t *string)
  {
    increaseIndent(offset);
    print(string);
    decreaseIndent(offset);
  }

  void print(const wchar_t chr)
  {
    print(&chr, 1);
  }

  size_t column()
  {
    size_t pos = output.find_last_of(L"\n");
    if (pos == WString::npos)
    {
      pos = -1;
    }
    return output.size() - pos - 1;
  }

  void unprint(size_t n)
  {
    output.resize(output.size() - n);
  }

protected:
  int getIndent() const
  {
    return indent * 2;
  }

  void setIndent(int width)
  {
    indent = width;

    if (indent < 0)
    {
      internalerr();
    }
  }

  void increaseIndent(int width = 1)
  {
    setIndent(indent + width);
  }

  void decreaseIndent(int width = 1)
  {
    setIndent(indent - width);
  }

  size_t lineNo;

private:
  int indent;
  WString output;
};

#endif /* SRC_PARSER_PRINTVISITOR_HPP_ */
