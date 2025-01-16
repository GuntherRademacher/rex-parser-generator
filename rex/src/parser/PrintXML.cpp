/*
 * Print.hpp
 *
 *  Created on: 31.07.2008
 *      Author: Gunther
 */

#include "../common/Memory.hpp"
#include "PrintXML.hpp"
#include "PrintEbnf.hpp"
#include "../common/Encoder.hpp"

PrintXML::PrintXML(char **argv, char *fileName, bool printFF)
: argv(argv),
  file(0),
  fileName(fileName),
  printFF(printFF),
  printID(false),
  indent(0),
  grammar(0)
{
}

PrintXML::~PrintXML()
{
  for (StringByCode::iterator i = tokenSequenceStringMap.begin();
       i != tokenSequenceStringMap.end();
       ++i)
  {
    free(i->second);
  }
}

void PrintXML::print(const wchar_t *string)
{
  xml += string;
  if (xml.size() > 100000)
  {
    flush();
  }
}

void PrintXML::flush()
{
  const wchar_t *unencoded = xml.c_str();
  char *encoded = Encoder::encode(unencoded);
  xml.clear();
  fputs(encoded, file);
  free(encoded);
}

wchar_t *PrintXML::tokenSequenceString(const TokenSequence &c)
{
  wchar_t *ts = tokenSequenceStringMap[c];
  if (ts == 0)
  {
    size_t size = c.size();
    if (size == 0)
    {
      ts = wcsdup(L"%EPSILON");
    }
    else
    {

      for (size_t i = 0; i < size; ++i)
      {
        if (i) wcscat(ts, L"~");
        Production *p = grammar->terminalProductionByCode[c[(int) i]];
        size_t tsSize = wcslen(p->name)
                      + (p->context ? 1 + wcslen(p->context) : 0)
                      + 2;
        if (ts == 0)
        {
          ts = ALLOCATE_ARRAY(wchar_t, tsSize);
          *ts = 0;
        }
        else
        {
          tsSize += wcslen(ts);
          ts = REALLOCATE_ARRAY(wchar_t, ts, tsSize);
        }
        wcscat(ts, p->name);
        if (p->context)
        {
          wcscat(ts, L"\\");
          wcscat(ts, p->context);
        }
      }
    }
    tokenSequenceStringMap[c] = ts;
  }
  return ts;
}

static int wcscompare(const void *lhs, const void *rhs)
{
  wchar_t *l = *(wchar_t **) lhs;
  wchar_t *r = *(wchar_t **) rhs;
  return wcscmp(l, r);
}

void PrintXML::printTokenSet(const wchar_t *name, const wchar_t *suffix, const TokenSequenceSetAccessor &tssa)
{
  print(L" ");
  print(name);
  print(suffix);
  print(L"=\"");

  const TokenSequenceSet &ts = *tssa.get();

  wchar_t **strings = ALLOCATE_ARRAY(wchar_t *, ts.size());
  size_t count = 0;

  for (TokenSequenceSet::const_iterator i = ts.begin(); i != ts.end(); ++i)
  {
    const TokenSequence &c(*i);
    strings[count++] = tokenSequenceString(c);
  }

  qsort(strings, count, sizeof(wchar_t *), &wcscompare);

  const wchar_t *delimiter = L"";
  for (size_t i = 0; i < count; i++)
  {
    print(delimiter);
    delimiter = L" ";
    printContent(strings[i]);
  }

  free(strings);

  print(L"\"");
}

void PrintXML::printSets(Grammar *grammar)
{
#if 0
  if (grammar->noLexer)
  {
    indent += 2;
    indentation();
    print(L"<g:lexer>\n");
    indent += 2;
    size_t tokenSetId = 0;
    for (Lookahead::const_iterator i(grammar->lookaheadSets.begin()); i != grammar->lookaheadSets.end(); ++i)
    {
      const OrderedTokenSequenceVector &cs(i->first);

      indentation();
      print(L"<g:tokenSet id=\"");
      print(format.toString<wchar_t>((int) tokenSetId++));
      print(L"\">\n");
      indent += 2;

      for (OrderedTokenSequenceVector::const_iterator j = cs.begin(); j != cs.end(); ++j)
      {
        const Token::Code code(j->first());
        const wchar_t *name = grammar->naming.getName(grammar, code, false);

        indentation();
        print(L"<g:token id=\"");
        print(format.toString<wchar_t>((int) code));
        print(L"\" name=\"");
        print(name);
        print(L"\"/>\n");
      }
      indent -= 2;
      indentation();
      print(L"<g:tokenSet>\n");
    }
    indent -= 2;
    indentation();
    print(L"</g:lexer>\n");
    indent -= 2;
  }
#endif
}

void PrintXML::printContent(const wchar_t c)
{
  switch (c)
  {
  case L'"': print(L"&quot;"); break;
  case L'<': print(L"&lt;");   break;
  case L'>': print(L"&gt;");   break;
  case L'&': print(L"&amp;");  break;
  default:
    {
      wchar_t s[] = {c, 0};
      print(s);
    }
  }
}

void PrintXML::printContent(const wchar_t *value)
{
  for (wchar_t c = *value; c; c = *++value)
  {
    printContent(c);
  }
}

void PrintXML::printNumberedTokenSetAttribute(const wchar_t *name,
                                              const wchar_t *suffix,
                                              size_t k,
                                              bool suppress,
                                              const TokenSequenceSet &ts)
{
  if (suppress)
  {
    printTokenSet(name, suffix, ts);
  }
  else
  {
    WString nameK(name);
    nameK += Format().toString<wchar_t>(k);
    printTokenSet(nameK.c_str(), suffix, ts);
  }
}

void PrintXML::openTag(Node *node, bool tagOpen, const wchar_t *nodeType, const CompressedTokenSet *lookahead)
{
  indentation();
  print(L"<g:");
  if (nodeType)
  {
    print(nodeType);
  }
  else
  {
    print(node->getNodeType());
  }

  if (printID)
  {
    if (node->id >= 0)
    {
      print(L" id=\"");
      print(format.toString<wchar_t>(node->id));
      print(L"\"");
    }

    if (node->reduceItem)
    {
      print(L" reduce-id=\"");
      print(format.toString<wchar_t>(node->reduceItem->id));
      print(L"\"");
    }
  }

  if (node->reduceItem)
  {
    print(L" reduce-count=\"");
    print(format.toString<wchar_t>(node->reduceItem->getDistance()));
    print(L"\"");
  }

  if (section == NONTERMINALS)
  {
    size_t kMax = 1;
    for (Node *n = node; n; n = n->getParent())
    {
      if (n->k > kMax)
      {
        kMax = n->k;
      }
      if (n->kConflicts > kMax)
      {
        kMax = n->kConflicts;
      }
    }

    for (size_t k = 1; k <= node->kConflicts; ++k)
    {
      if (node->conflictsK[k - 1])
      {
        printNumberedTokenSetAttribute(L"LL", L"-conflict", k, false, *node->conflicts(k));
      }
    }

    if (printFF)
    {
/*
      for (size_t k = 1; k <= kMax; ++k)
      {
        printNumberedTokenSetAttribute(L"first", L"", k, k == 1, node->first(k));
      }
      for (size_t k = 1; k <= kMax; ++k)
      {
        printNumberedTokenSetAttribute(L"follow", L"", k, k == 1, node->follow(k));
      }
*/
      for (size_t k = 1; k <= kMax; ++k)
      {
        if (k <= node->kFirst && node->firstK[k - 1])
        {
          printNumberedTokenSetAttribute(L"first", L"", k, k == 1, *node->firstK[k - 1]);
        }
      }
      for (size_t k = 1; k <= kMax; ++k)
      {
        if (k <= node->kFollow && node->followK[k - 1])
        {
          printNumberedTokenSetAttribute(L"follow", L"", k, k == 1, *node->followK[k - 1]);
        }
      }
    }

    MatchType matchType;
    const TokenSequenceSet &match = node->getMatch(matchType);
    switch (matchType)
    {
    case IF:
      printTokenSet(L"if", L"", match);
      break;
    case IFNOT:
      printTokenSet(L"ifnot", L"", match);
      break;
    case CASE:
      printTokenSet(L"if", L"", match);
      break;
    case DEFAULT:
      print(L" default=\"\"");
      break;
    case NOMATCH:
      break;
    }
  }

  if (lookahead && lookahead->getDpi() >= 0)
  {
    print(L" dpi=\"");
    print(format.toString<wchar_t>(lookahead->getDpi()));
    print(L"\"");

    printTokenSet(L"lookahead", L"", lookahead->getMatchSet());
  }

#if 0
  if (node->isNodeWithContext())
  {
    print(L" distance=\"");
    print(format.toString<wchar_t>(static_cast<NodeWithContext *>(node)->getDistance()));
    print(L"\"");
    print(L" active=\"");
    print(format.toString<wchar_t>(node->isActive()));
    print(L"\"");
  }
#endif

  if (! tagOpen)
  {
    print(L">\n");
  }
}

void PrintXML::closeTag(Node *node, bool tagOpen, const wchar_t *nodeType)
{
  if (tagOpen)
    print(L"/>\n");
  else
  {
    indentation();
    print(L"</g:");
    print(nodeType ? nodeType : node->getNodeType());
    print(L">\n");
  }
}

void PrintXML::visitNode(Node *node)
{
  openTag(node, true);
  closeTag(node, true);
}

void PrintXML::visitNodeList(Node *node)
{
  indent += 2;
  Visitor::visitNodeList(node);
  indent -= 2;
}

void PrintXML::visitNodeWithChildren(NodeWithChildren *node)
{
  openTag(node);
  Visitor::visitNodeWithChildren(node);
  closeTag(node);
}

void PrintXML::visitSequence(Sequence *node)
{
  visitNodeWithChildren(node);
}

void PrintXML::visitOptional(Optional *node)
{
  openTag(node, false, 0, node->getLookahead());
  Visitor::visitNodeWithChildren(node);
  closeTag(node);
}

void PrintXML::visitZeroOrMore(ZeroOrMore *node)
{
  openTag(node, false, 0, node->getLookahead());
  Visitor::visitNodeWithChildren(node);
  closeTag(node);
}

void PrintXML::visitOneOrMore(OneOrMore *node)
{
  openTag(node, false, 0, node->getLookahead());
  Visitor::visitNodeWithChildren(node);
  closeTag(node);
}

void PrintXML::visitGrammar(Grammar *node)
{
  section = PROLOG;
  visitNodeList(node->prolog);

  section = NONTERMINALS;
  visitNodeList(node->nonTerminals);

  indent += 2;
  indentation();
  indent -= 2;

  if (node->terminals)
  {
    print(L"<?TOKENS?>\n");
    section = TERMINALS;
    visitNodeList(node->terminals);
  }

  if (node->epilog)
  {
    print(L"<?ENCORE?>\n");
    section = EPILOG;
    visitNodeList(node->epilog);
  }

  printSets(node);
}

void PrintXML::visitChoice(Choice *node)
{
  openTag(node, false, node->ordered ? L"orderedChoice" : 0, node->getLookahead());
  indent += 2;
  Visitor::visitChoice(node);
  indent -= 2;
  closeTag(node, false, node->ordered ? L"orderedChoice" : 0);
}

void PrintXML::visitExclusion(Exclusion *node)
{
  openTag(node);
  indent += 2;
  Visitor::visitExclusion(node);
  indent -= 2;
  closeTag(node);
}

void PrintXML::visitPredicate(Predicate *node)
{
  openTag(node);
  indent += 2;
  Visitor::visitPredicate(node);
  indent -= 2;
  closeTag(node);
}

void PrintXML::visitContext(Context *node)
{
  openTag(node);
  indent += 2;
  Visitor::visitContext(node);
  indent -= 2;
  closeTag(node);
}

void PrintXML::visitPreference(Preference *node)
{
  for (NodeList::iterator l = node->lhs.begin(); l != node->lhs.end(); ++l)
    for (NodeList::iterator r = node->rhs.begin(); r != node->rhs.end(); ++r)
  {
    openTag(node);
    indent += 2;
    (*l)->accept(*this);
    (*r)->accept(*this);
    indent -= 2;
    closeTag(node);
  }
}

void PrintXML::visitDelimiter(Delimiter *node)
{
  for (NodeList::iterator r = node->rhs.begin(); r != node->rhs.end(); ++r)
  {
    openTag(node);
    indent += 2;
    node->lhs->accept(*this);
    (*r)->accept(*this);
    indent -= 2;
    closeTag(node);
  }
}

void PrintXML::visitEquivalence(Equivalence *node)
{
  openTag(node);
  indent += 2;
  node->lhs->accept(*this);
  node->rhs->accept(*this);
  indent -= 2;
  closeTag(node);
}

void PrintXML::visitComplement(Complement *node)
{
  openTag(node);
  indent += 2;
  Visitor::visitComplement(node);
  indent -= 2;
  closeTag(node);
}

void PrintXML::visitProduction(Production *node)
{
  openTag(node, true);
//  if (node->number)
//  {
//    print(L" number=\"");
//    print(format.toString<wchar_t>(node->number));
//    print(L"\"");
//  }
  print(L" name=\"");
  printContent(node->name);
  print(L"\"");

  if (node->nonGreedy)
  {
    print(L" nongreedy=\"true\"");
  }

  if (node == grammar->whitespace)
  {
    print(L" whitespace-spec=\"definition\"");
  }
  else if (node->wsExplicit)
  {
    print(L" whitespace-spec=\"explicit\"");
  }

  print(L">\n");
  visitNodeList(node->firstChild);
  closeTag(node);
}

void PrintXML::visitRef(Ref *node)
{
  openTag(node, true, 0, node->getLookahead());
  print(L" name=\"");
  printContent(node->name);
  print(L"\"");
  if (node->context)
  {
    print(L" context=\"");
    printContent(node->context);
    print(L"\"");
  }

//  if (node->reduceType != reduceUnknown)
//  {
//    print(L" reduce-by=\"");
//    printContent(node->reduceType == reduceByCount ? L"count" :  L"lookback");
//    print(L"\"");
//  }

  closeTag(node, true);
}

void PrintXML::visitString(String *node)
{
  openTag(node, true, 0, node->getLookahead());
  if (node->context)
  {
    print(L" context=\"");
    printContent(node->context);
    print(L"\"");
  }

//  if (node->reduceType != reduceUnknown)
//  {
//    print(L" reduce-by=\"");
//    printContent(node->reduceType == reduceByCount ? L"count" :  L"lookback");
//    print(L"\"");
//  }

  print(L">");
  printContent(node->value);
  print(L"</g:string>\n");
}

void PrintXML::visitProcessingInstruction(ProcessingInstruction *node)
{
  openTag(node, true, L"sequence");

  print(L" line=\"");
  print(format.toString<wchar_t>(node->line));
  print(L"\" file=\"");
  print(node->fileName);
  print(L"\"");
  print(L">\n");
  indent += 2;

  indentation();

  print(L"<?");
  print(node->target);
  print(L" ");
  print(node->content);
  print(L"?>\n");

  indent -= 2;
  closeTag(node, false, L"sequence");
}

void PrintXML::visitEndOfFile(EndOfFile *node)
{
  indentation();
  print(L"<g:endOfFile/>\n");
}

void PrintXML::visitChar(Char *node)
{
  indentation();
  print(L"<g:char>");
  printContent(node->character);
  print(L"</g:char>\n");
}

void PrintXML::visitCharCode(CharCode *node)
{
  indentation();
  print(L"<g:charCode value=\"");
  print(format.toString<wchar_t>(node->value, 16));
  print(L"\"/>\n");
}

void PrintXML::visitCharRange(CharRange *node)
{
  indentation();
  print(L"<g:charRange minChar=\"");
  printContent(node->minChar);
  print(L"\" maxChar=\"");
  printContent(node->maxChar);
  print(L"\"/>\n");
}

void PrintXML::visitCharCodeRange(CharCodeRange *node)
{
  indentation();
  print(L"<g:charCodeRange minValue=\"");
  print(format.toString<wchar_t>(node->minValue, 16));
  print(L"\" maxValue=\"");
  print(format.toString<wchar_t>(node->maxValue, 16));
  print(L"\"/>\n");
}

void PrintXML::showItem(const wchar_t *role, Node *item, const TokenSequenceSetAccessor *lookahead)
{
/*

  <parser type="lr" k="1">
    <state id="2">
      <item lookahead="EOF" shift="7" first="'+'">Expression ::= Term ( ( <dot>.</dot> '+' | '-' ) Term )*</item>
      <item lookahead="EOF" shift="7" first="'-'">Expression ::= Term ( ( '+' | <dot>.</dot> '-' ) Term )*</item>
      <item lookahead="EOF" reduce="Expression">Expression ::= Term ( ( '+' | '-' ) Term )* <dot>.</dot></item>
    </state>
  </parser>

*/

  indent += 2;
  indentation();

  print(L"<item");

  print(L" id=\"");
  print(format.toString<wchar_t>(item->id));
  print(L"\"");

  if (lookahead && printFF)
  {
    printTokenSet(L"lookahead", L"", *lookahead);
  }

  print(L">");

  const wchar_t *placeholder = L"\u001A";
  //  const wchar_t *zNotationSpot = L"&#10625;";
  //  const wchar_t *bullet = L"&#8226;";

  PrintEbnf pe(PrintEbnf::ACTIVE);
  WString itemString = pe.itemToString(item, placeholder);
  itemString.erase(itemString.length() - 1);
  for (;;)
  {
    size_t placeholderOffset = itemString.find(placeholder);
    if (placeholderOffset == itemString.npos)
    {
      break;
    }
    printContent(itemString.substr(0, placeholderOffset).c_str());
    print(L"<dot>.</dot>");
    itemString.erase(0, placeholderOffset + 1);
  }
  printContent(itemString.c_str());

  print(L"</item>\n");

  indent -= 2;
}

void PrintXML::showItemSet(const ItemSet &items, const wchar_t *name)
{
  for (ItemSet::const_iterator i = items.begin(); i != items.end(); ++i)
  {
    const std::pair<Node *, const TokenSequenceSetAccessor *> item = *i;
    showItem(name, item.first, item.second);
  }
}

void PrintXML::showState(Grammar *grammar, size_t k, LrStates &states, ItemSet *kernel, const LrState *transitions)
{
  int id = transitions == 0 ? -1 : transitions->getStateId();

  indent += 2;
  indentation();

  print(L"<state id=\"");
  print(format.toString<wchar_t>(id));
  print(L"\">\n");

  if (transitions)
  {
    showItemSet(transitions->shiftItems, L"shiftItems");
    showItemSet(transitions->reduceItems, L"reduceItems");
    for (LrState::const_iterator i = transitions->begin(); i != transitions->end(); ++i)
    {
      ItemSet *toState = i->second.toState;
      const Dominoes *dominoes = i->second.dominoes;

      LrState *toStateTransitions = states[toState];
      int toStateId = toStateTransitions->getStateId();
      Node *nonterminal = i->first;

      if (nonterminal->isReduce())
      {
        indent += 2;
        indentation();

        print(L"<goto on=\"EMBEDDED-");
        printContent(format.toString<wchar_t>(static_cast<Reduce *>(nonterminal)->nonterminalCode));
        print(L"\"");
      }
      else
      {
        Production *symbol = static_cast<Production *>(nonterminal);

        if (symbol->tokenCode >= 0)
        {
          const TokenSequence ts = grammar->tokenSequence(symbol->tokenCode);
          if (grammar->tokenSequenceSets->firstK(transitions->shiftLookahead, 1)->contains(ts))
          {
            indent += 2;
            indentation();
            print(L"<shift");
            TokenSequenceSet tss(ts);
            printTokenSet(L"on", L"", tss);
          }
          else
          {
            continue;
          }
        }
        else
        {
          indent += 2;
          indentation();

          print(L"<goto on=\"");
          print(symbol->name);
          print(L"\"");
        }
      }

      print(L" to=\"");
      print(format.toString<wchar_t>(toStateId));
      print(L"\"");

      if (true)
      {
        if (dominoes != 0 && dominoes->isEssential() && states.getDominoSets()->find(const_cast<Dominoes *>(dominoes)) != states.getDominoSets()->end())
        {
          print(L" domino=\"");
          print(format.toString<wchar_t>(states.getDominoSets()->getId(dominoes)));
          print(L"\"");

          print(L" dominoes=\"");
          const wchar_t *delimiter = L"";
          for (Dominoes::const_iterator d = dominoes->begin(); d != dominoes->end(); ++d)
          {
            const Domino &domino = *d;

            print(delimiter);
            delimiter = L" ";
            print(domino.toString().c_str());
          }
          print(L"\"");
        }
      }

      print(L"/>\n");

      indent -= 2;
    }

    for (ItemSet::const_iterator i = transitions->reduceItems.begin(); i != transitions->reduceItems.end(); ++i)
    {
      const std::pair<Node *, const TokenSequenceSetAccessor *> item = *i;
      Reduce* const reduce = static_cast<Reduce *>(item.first);
      if (! reduce->isReduce())
      {
        internalerr();
      }

      indent += 2;
      indentation();

      print(L"<reduce");

      const TokenSequenceSet *itemLookahead = grammar->tokenSequenceSets->firstK(item.second, transitions->getK());
      const TokenSequenceSet *itemMatch = CompressedTokenSet::compressMatch(transitions->getConflictsK(), itemLookahead, grammar->tokenSequenceFactory, grammar->tokenSequenceSets);
//      if (itemMatch != transitions->getDefaultMatch())
      {
        printTokenSet(L"on", L"", *itemMatch);
      }

      print(L" symbol=\"");
      if (reduce->isImplicit)
      {
        print(L"EMBEDDED-");
        print(format.toString<wchar_t>(reduce->nonterminalCode));
      }
      else
      {
        printContent(grammar->nonterminalProductionByCode[reduce->nonterminalCode]->name);
      }
      print(L"\"");

      if (true)
      {
        Dominoes dominoes;
        dominoes.insert(Domino(reduce, 0));
        if (dominoes.isEssential())
        {
          print(L" domino=\"");
          print(format.toString<wchar_t>(states.getDominoSets()->getId(&dominoes)));
          print(L"\"");

          print(L" dominoes=\"");
          print(format.toString<wchar_t>(reduce->id));
          print(L"\"");
        }
      }

      print(L"/>\n");

      indent -= 2;
    }

    if (id == 0)
    {
      indent += 2;
      indentation();

      print(L"<accept on=\"");
      print(grammar->startSymbol()->name);
      print(L"\"/>\n");

      indent -= 2;
    }
  }

  indentation();
  print(L"</state>\n");
  indent -= 2;
}

void PrintXML::dump(Grammar *node, size_t k)
{
  grammar = node;

  LrStates *parser = grammar->states;
  bool printParser = parser != 0;
  printID = printParser;

  CString xmlFileName(fileName);
  xmlFileName += ".xml";

  file = fopen(xmlFileName.c_str(), "wb");
  if (file == 0)
  {
    perror(xmlFileName.c_str());
    exit(1);
  }

  OutputFile::printHeader(file, XML, argv);

  openTag(node, true);
  print(L" xmlns:g=\"http://www.w3.org/2001/03/XPath/grammar\">\n");

  grammar->accept(*this);
  if (printParser)
  {
    typedef std::map<int, ItemSet *> StateById;
    StateById stateById;
    for (LrStates::const_iterator j = parser->begin(); j != parser->end(); ++j)
    {
      stateById[j->second->getStateId()] = j->first;
    }

    indent += 2;
    indentation();
    print(L"<parser>\n");
    for (StateById::const_iterator j = stateById.begin(); j != stateById.end(); ++j)
    {
      ItemSet *kernel = j->second;
      const LrState *transitions = (*parser)[kernel];
      showState(grammar, k, *parser, kernel, transitions);
    }
    indentation();
    print(L"</parser>\n");

    indentation();
    print(L"<triples>\n");
    indent += 2;
    for (LrStates::Triples::const_iterator j = parser->getTriples()->begin(); j != parser->getTriples()->end(); ++j)
    {
      const LrStates::Triples::value_type &triple = *j;
      indentation();
      print(L"<triple from=\"");

      print(format.toString<wchar_t>(parser->getDominoSets()->getId(triple.first.first)));
      print(L"\" to=\"");
      print(format.toString<wchar_t>(parser->getDominoSets()->getId(triple.first.second)));
      print(L"\" valid=\"");
      print(format.toString<wchar_t>(parser->getDominoSets()->getId(triple.second)));

//      print(triple.first.first->toString().c_str());
//      print(L"\" to=\"");
//      print(triple.first.second->toString().c_str());
//      print(L"\" valid=\"");
//      print(triple.second->toString().c_str());

      print(L"\"/>\n");
    }
    indent -= 2;
    indentation();
    print(L"</triples>\n");

    indent -=2;
  }

  closeTag(node);
  flush();
  fclose(file);
}
