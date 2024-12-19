/*
 * AutomaticSemicolonInsertion.hpp
 *
 *  Created on: 27-Nov-2014
 *      Author: Gunther
 */

#ifndef AUTOMATICSEMICOLONINSERTION_HPP
#define AUTOMATICSEMICOLONINSERTION_HPP

#include "Grammar.hpp"

class AutomaticSemicolonInsertion : public Visitor
{
public:
  AutomaticSemicolonInsertion() : asiKinds(0) {}

  unsigned int getAsiKinds() const {return asiKinds;}

  void visitGrammar(Grammar *node)
  {
    visitNodeList(node->nonTerminals);
    node->automaticSemicolonInsertion = ALL;

    size_t found = Math::bitSum(asiKinds);
    size_t expected = Math::bitSum(ALL);
    if (found != expected)
    {
      WString msg(L"found ");
      if (found == 0)
      {
        msg += L"none";
      }
      else
      {
        msg += L"only ";
        msg += Format().toString<wchar_t>(found);
      }
      msg += L" of ";
      msg += Format().toString<wchar_t>(expected);
      msg += L" expected grammar items for applying automatic semicolon insertion";
      if (found == 0)
        throw Complaint(msg.c_str(), L"");
      else
        printf("%ls\n", msg.c_str());
    }
  }

  void visitString(String *node)
  {
    if (wcscmp(node->value, L";") == 0 &&
        wcscmp(node->production->name, L"EmptyStatement") &&
        wcscmp(node->production->name, L"IterationStatement"))
    {
      setAsi(node, SEMICOLON);
    }
    else if (wcscmp(node->value, L"++") == 0 && wcscmp(node->production->name, L"PostfixExpression") == 0)
    {
      for (Node *parent = node->getParent(); parent; parent = parent->getParent())
      {
        if (parent->derivesToEmptySequence())
        {
          setAsi(parent, PLUSPLUS);
          break;
        }
      }
    }
    else if (wcscmp(node->value, L"--") == 0 && wcscmp(node->production->name, L"PostfixExpression") == 0)
    {
      for (Node *parent = node->getParent(); parent; parent = parent->getParent())
      {
        if (parent->derivesToEmptySequence())
        {
          setAsi(parent, MINUSMINUS);
          break;
        }
      }
    }
    else if (wcscmp(node->value, L"continue") == 0 && wcscmp(node->production->name, L"ContinueStatement") == 0)
    {
      setAsi(node->followingElementSibling, CONTINUE);
    }
    else if (wcscmp(node->value, L"break") == 0 && wcscmp(node->production->name, L"BreakStatement") == 0)
    {
      setAsi(node->followingElementSibling, BREAK);
    }
    else if (wcscmp(node->value, L"return") == 0 && wcscmp(node->production->name, L"ReturnStatement") == 0)
    {
      setAsi(node->followingElementSibling, RETURN);
    }
    else if (wcscmp(node->value, L"throw") == 0 && wcscmp(node->production->name, L"ThrowStatement") == 0)
    {
      setAsi(node->followingElementSibling, THROW);
    }
  }

private:
  void setAsi(Node *node, ASIKind kind)
  {
    if (node)
    {
      node->automaticSemicolonInsertion = kind;
      asiKinds |= kind;
    }
  }

  unsigned int asiKinds;
};

#endif /* AUTOMATICSEMICOLONINSERTION_HPP */
