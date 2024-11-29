/*
 * EbnfParserBase.hpp
 *
 *  Created on: 03.01.2010
 *      Author: Gunther
 */

#ifndef EBNFPARSERBASE_HPP
#define EBNFPARSERBASE_HPP

class EbnfParserBase
{
public:
  EbnfParserBase() : currentNode(0), grammar(0), fileName(0), section(GRAMMAR) {}
  virtual ~EbnfParserBase() {delete grammar;}

protected:
  virtual const wchar_t *currentChar() = 0;
  virtual const int currentLength() = 0;

  static wchar_t *trim(wchar_t *value)
  {
    size_t s = wcslen(value);
    while (s > 0 && (value[s - 1] == 9 ||
                     value[s - 1] == 10 ||
                     value[s - 1] == 13 ||
                     value[s - 1] == 32))
    {
      --s;
    }
    value[s] = 0;
    return value;
  }

  WStringRef currentToken()
  {
    const wchar_t *c = currentChar();
    if (*c == L'"' || *c == '\'')
    {
      return WStringRef(c + 1, currentLength() - 2);
    }
    else
    {
      return WStringRef(c, currentLength());
    }
  }

  void descend(NodeWithChildren *aNode)
  {
    currentNode->addChild(aNode);
    currentNode = aNode;
  }

  void setWhitespaceDefinition(Production *p)
  {
    if (grammar->whitespace)
    {
      throw Complaint(L"duplicate definition of whitespace: ", p->name);
    }
    grammar->whitespace = p;
  }

  void ascend()
  {
    // flatten nested sequences

    if (currentNode->isNodeWithChildren())
    {
      for (Node *child = currentNode->firstChild; child; child = child->followingSibling)
      {
        if (child->isSequence())
        {
          Sequence helper;
          helper.firstChild = currentNode->firstChild;
          helper.lastChild = currentNode->lastChild;
          currentNode->firstChild = 0;
          currentNode->lastChild = 0;

          while (helper.firstChild)
          {
            child = helper.isolateFirstChild();
            if (child->isSequence())
            {
              Sequence *s = static_cast<Sequence *>(child);
              while (s->firstChild)
              {
                currentNode->addChild(s->isolateFirstChild());
              }
              delete s;
            }
            else
            {
              currentNode->addChild(child);
            }
          }
          break;
        }
      }
    }

    Node *complexNode = currentNode;
    Node *simplified = complexNode->simplified();
    currentNode = static_cast<NodeWithChildren *>(currentNode->getParent());
    if (complexNode != simplified)
    {
      complexNode = currentNode->isolateLastChild();
      currentNode->addChild(simplified);
      delete complexNode;
    }
  }

  void wrap(NodeWithChildren *node)
  {
    Node *wrappee = currentNode->isolateLastChild();
    currentNode->addChild(node);
    if (! wrappee->isSequence() || (! node->isSequence() && 0 == static_cast<Sequence *>(wrappee)->firstChild))
    {
      node->addChild(wrappee);
    }
    else
    {
      node->firstChild = static_cast<Sequence *>(wrappee)->firstChild;
      node->lastChild = static_cast<Sequence *>(wrappee)->lastChild;
      for (Node *n = node->firstChild; n; n = n->followingSibling)
      {
        n->setParent(node);
      }
      static_cast<Sequence *>(wrappee)->firstChild = 0;
      static_cast<Sequence *>(wrappee)->lastChild = 0;
      delete wrappee;
    }
  }

  static int charCodeValue(const wchar_t *string)
  {
    if (*string == L'x')
    {
      return (int) wcstol(string + 1, 0, 16);
    }
    else
    {
      return (int) wcstol(string, 0, 10);
    }
  }

  NodeWithChildren *currentNode;
  Grammar *grammar;
  const wchar_t *fileName;
  GrammarSection section;
};

#endif
