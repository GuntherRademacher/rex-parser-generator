/*
 * PrintEbnf.hpp
 *
 *  Created on: 18.06.2012
 *      Author: Gunther
 */

#include "../common/Memory.hpp"
#include "../common/Encoder.hpp"
#include "PrintEbnf.hpp"

PrintEbnf::PrintEbnf(ShowPI showPI)
: file(0), indent(0), grammar(0), item(0), dot(L"."), showPI(showPI)
{
}

void PrintEbnf::print(const char *outputFileName, char **argv, char *className, Grammar *node)
{
  ebnf.clear();

  file = fopen(outputFileName, "wb");
  if (file == 0)
  {
    perror(outputFileName);
    exit(1);
  }

  OutputFile::printHeader(file, EBNF, argv);

  node->accept(*this);

  flush();
  fclose(file);

  file = 0;
  indent = 0;
  grammar = 0;
  item = 0;
}

WString PrintEbnf::itemToString(Node *node, const wchar_t *aDot)
{
  ebnf.clear();

  file = 0;
  indent = 0;
  grammar = node->grammar;
  item = node;
  dot = aDot;

  if (node->isReduce())
  {
    Reduce *reduce = static_cast<Reduce *>(node);
    if (reduce->isImplicit)
    {
      WString name(L"EMBEDDED-");
      name += format.toString<wchar_t>(reduce->nonterminalCode);
      print(name.c_str());
      print(L" ::=");
      reduce->processingInstruction->accept(*this);
      print(L"\n");
    }
    else
    {
      grammar->nonterminalProductionByCode[reduce->nonterminalCode]->accept(*this);
    }
  }
  else
  {
    node->production->accept(*this);
  }

  file = 0;
  indent = 0;
  grammar = 0;
  item = 0;
  dot = L".";

  return ebnf;
}

void PrintEbnf::print(const wchar_t *string)
{
  ebnf += string;
}

size_t PrintEbnf::column()
{
  size_t pos = ebnf.find_last_of(L"\n");
  if (pos == WString::npos)
  {
    pos = -1;
  }
  return ebnf.size() - pos - 1;
}

void PrintEbnf::flush()
{
  const wchar_t *unencoded = ebnf.c_str();
  char *encoded = Encoder::encode(unencoded);
  ebnf.clear();
  fputs(encoded, file);
  free(encoded);
}

void PrintEbnf::printContent(const wchar_t c)
{
  wchar_t s[] = {c, 0};
  print(s);
}

void PrintEbnf::printContent(const wchar_t *value)
{
  for (wchar_t c = *value; c; c = *++value)
  {
    printContent(c);
  }
}

void PrintEbnf::visitNodePreOrder(Node *node)
{
  if (item == node)
  {
    print(L" ");
    print(dot);
  }
}

void PrintEbnf::visitNodePostOrder(Node *node)
{
  if (item && item == node->reduceItem)
  {
    print(L" ");
    print(dot);
  }
}

void PrintEbnf::visitNodeWithChildren(NodeWithChildren *node)
{
  visitNodePreOrder(node);
  visitNodeList(node->firstChild);
  visitNodePostOrder(node);
}

void PrintEbnf::visitOptional(Optional *node)
{
  visitNodePreOrder(node);
  print(L" (");
  visitNodeList(node->firstChild);
  print(L" )?");
  visitNodePostOrder(node);
}

void PrintEbnf::visitZeroOrMore(ZeroOrMore *node)
{
  visitNodePreOrder(node);
  print(L" (");
  visitNodeList(node->firstChild);
  print(L" )*");
  visitNodePostOrder(node);
}

void PrintEbnf::visitOneOrMore(OneOrMore *node)
{
  visitNodePreOrder(node);
  print(L" (");
  visitNodeList(node->firstChild);
  print(L" )+");
  visitNodePostOrder(node);
}

void PrintEbnf::visitGrammar(Grammar *node)
{
  grammar = node;

  section = PROLOG;
  visitNodeList(node->prolog);

  section = NONTERMINALS;
  visitNodeList(node->nonTerminals);

  indent += 2;
  indentation();
  indent -= 2;

  if (node->terminals)
  {
    print(L"\n<?TOKENS?>\n\n");
    section = TERMINALS;
    visitNodeList(node->terminals);
  }

  if (node->epilog)
  {
    print(L"\n<?ENCORE?>\n\n");
    section = EPILOG;
    visitNodeList(node->epilog);
  }
}

void PrintEbnf::visitChoice(Choice *node)
{
  visitNodePreOrder(node);
  size_t col = node->getParent()->isProduction() ? column() : 0;
  WString linefeed;
  const wchar_t * op = L" (";
  for (NodeList::iterator i = node->cases.begin(); i != node->cases.end(); ++i)
  {
    print(linefeed.c_str());
    print(op);
    if (col)
    {
      linefeed = L"\n";
      linefeed.append(col, L' ');
      col = 0;
    }
    op = node->ordered ? L" /" : L" |";
    (*i)->accept(*this);
  }
  print(linefeed.c_str());
  print(L" )");
  visitNodePostOrder(node);
}

void PrintEbnf::visitExclusion(Exclusion *node)
{
  print(L" ( (");
  node->lhs->accept(*this);
  print(L") - (");
  node->rhs->accept(*this);
  print(L" ) )");
}

void PrintEbnf::visitPredicate(Predicate *node)
{
  indent += 2;
  Visitor::visitPredicate(node);
  indent -= 2;
}

void PrintEbnf::visitContext(Context *node)
{
  visitNodePreOrder(node);
  node->expr->accept(*this);
  print(L" &(");
  node->context->accept(*this);
  print(L" )");
  visitNodePostOrder(node);
}

void PrintEbnf::visitPreference(Preference *node)
{
  visitNodePreOrder(node);
  for (NodeList::iterator l = node->rhs.begin(); l != node->rhs.end(); ++l)
  {
    (*l)->accept(*this);
    size_t space = ebnf.find_last_of(L" ");
    ebnf.erase(space, 1);
    print(L" <<");
    for (NodeList::iterator r = node->lhs.begin(); r != node->lhs.end(); ++r)
    {
      (*r)->accept(*this);
    }
    print(L"\n");
  }
  visitNodePostOrder(node);
}

void PrintEbnf::visitDelimiter(Delimiter *node)
{
  visitNodePreOrder(node);
  node->lhs->accept(*this);
  size_t space = ebnf.find_last_of(L" ");
  ebnf.erase(space, 1);
  print(L" \\\\");
  for (NodeList::iterator l = node->rhs.begin(); l != node->rhs.end(); ++l)
  {
    (*l)->accept(*this);
  }
  print(L"\n");
  visitNodePostOrder(node);
}

void PrintEbnf::visitEquivalence(Equivalence *node)
{
  node->lhs->accept(*this);
  print(L" == ");
  node->rhs->accept(*this);
}

void PrintEbnf::printCodePoint(unsigned int codePoint)
{
  print(L"#x");
  print(format.toString<wchar_t>(codePoint, 16));
}

bool PrintEbnf::isCharClassLiteral(wchar_t character)
{
  return wcschr(L"[^-#]", character) == 0;
}

bool PrintEbnf::isCharClassLiteral(Node *node)
{
  return ! (node->isCharCode()
         || node->isCharCodeRange()
         || (node->isChar() && ! isCharClassLiteral(static_cast<Char *>(node)->character))
         || (node->isCharRange() && ! isCharClassLiteral(static_cast<CharRange *>(node)->minChar))
         || (node->isCharRange() && ! isCharClassLiteral(static_cast<CharRange *>(node)->maxChar)));
}

void PrintEbnf::visitCharClass(CharClass *node)
{
  visitNodePreOrder(node);
  print(L" [");
  for (Node *child = node->firstChild; child; child = child->followingSibling)
  {
    if (isCharClassLiteral(child))
    {
      child->accept(*this);
    }
  }
  for (Node *child = node->firstChild; child; child = child->followingSibling)
  {
    if (! isCharClassLiteral(child))
    {
      child->accept(*this);
    }
  }
  print(L"]");
  visitNodePostOrder(node);
}

void PrintEbnf::visitComplement(Complement *node)
{
  print(L" [^");
  Visitor::visitCharClass(node->charClass);
  print(L"]");
}

static bool contains(Node *subtree, Node *node)
{
  class Contains : public Visitor
  {
  public:
    Contains(Node *searchee) : searchee(searchee), result(false) {}
    void visitNodePreOrder(Node *node)
    {
      result = result || node == searchee || node->reduceItem == searchee;
    }

    bool operator()()
    {
      return result;
    }

  private:
    Node *searchee;
    bool result;
  }
  contains(node);

  subtree->accept(contains);
  return contains();
}

void PrintEbnf::visitProduction(Production *node)
{
  printContent(node->name);

  if (node->nonGreedy)
  {
    print(L"?");
  }
  print(L" ::=");

  if (node->firstElementChild &&
      node->firstElementChild == node->lastElementChild &&
      node->firstElementChild->isChoice() &&
      (item == 0 || contains(node->firstElementChild, item)) &&
      node->firstElementChild != item &&
      (node->firstElementChild->reduceItem == 0 || node->firstElementChild->reduceItem != item))
  {
    Choice *choice = static_cast<Choice *> (node->firstElementChild);
    const wchar_t *op = L"";
    for (NodeList::iterator i = choice->cases.begin(); i != choice->cases.end(); ++i)
    {
      Node* caze = *i;
      if (item == 0 || contains(caze, item))
      {
        print(op);
        op = choice->ordered ? L" /" : L" |";
        visitNodePreOrder(node);
        caze->accept(*this);
      }
    }
    if (item && *op == 0)
    {
      internalerr();
    }
  }
  else
  {
    visitNodePreOrder(node);
    visitNodeList(node->firstChild);
  }

  if (node == grammar->whitespace)
  {
    print(L"\n          /* ws:definition */");
  }
  else if (node->wsExplicit)
  {
    print(L"\n          /* ws:explicit */");
  }

  visitNodePostOrder(node);
  print(L"\n");
}

void PrintEbnf::visitRef(Ref *node)
{
  visitNodePreOrder(node);
  print(L" ");
  printContent(node->name);
  if (node->context)
  {
    print(L"^");
    printContent(node->context);
  }
  visitNodePostOrder(node);
}

void PrintEbnf::visitString(String *node)
{
  visitNodePreOrder(node);
  const wchar_t *quote = wcsstr(node->value, L"'") ? L"\"" : L"'";
  print(L" ");
  print(quote);
  printContent(node->value);
  print(quote);
  if (node->context)
  {
    print(L"^");
    printContent(node->context);
  }
  visitNodePostOrder(node);
}

void PrintEbnf::visitProcessingInstruction(ProcessingInstruction *node)
{
  if (showPI == ALL || (showPI == ACTIVE && node->isActive()))
  {
    visitNodePreOrder(node);
    if (showPI == ACTIVE)
      print(L" ");
    print(L"<?");
    print(node->target);
    print(L" ");
    print(node->content);
    print(L"?>");
    if (showPI == ALL)
      print(L"\n");
    visitNodePostOrder(node);
  }
}

void PrintEbnf::visitEndOfFile(EndOfFile *node)
{
  print(L" $");
}

void PrintEbnf::visitChar(Char *node)
{
  if (isCharClassLiteral(node))
  {
    printContent(node->character);
  }
  else
  {
    printCodePoint((unsigned int) node->character);
  }
}

void PrintEbnf::visitCharCode(CharCode *node)
{
  indentation();
  printCodePoint(node->value);
}

void PrintEbnf::visitCharRange(CharRange *node)
{
  if (isCharClassLiteral(node))
  {
    printContent(node->minChar);
    print(L"-");
    printContent(node->maxChar);
  }
  else
  {
    printCodePoint((unsigned int) node->minChar);
    print(L"-");
    printCodePoint((unsigned int) node->maxChar);
  }
}

void PrintEbnf::visitCharCodeRange(CharCodeRange *node)
{
  indentation();
  printCodePoint(node->minValue);
  print(L"-");
  printCodePoint(node->maxValue);
}
