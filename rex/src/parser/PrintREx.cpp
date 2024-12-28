#include "../common/Memory.hpp"
#include "../common/Format.hpp"
#include "../common/Encoder.hpp"
#include "../common/OutputFile.hpp"
#include "../common/CGVariable.hpp"
#include "../common/CompressedMap.hpp"
#include "PrintREx.hpp"
#include "ItemSet.hpp"

PrintREx::PrintREx(char **av,
                   const wchar_t *aClassName,
                   TargetLanguage aTargetLanguage,
                   bool charParser,
                   bool printTrace,
                   bool printTree,
                   bool aPrintREx,
                   bool unlimited,
                   bool v)
: argv(av),
  targetLanguage(aTargetLanguage),
  parseChars(charParser),
  trace(printTrace),
  tree(printTree),
  indent(0),
  width(0),
  printRex(aPrintREx),
  unlimitedLookahead(unlimited),
  verbose(v),
  rex(0)
{
  switch (targetLanguage)
  {
  case CPP:
  case CSHARP:
  case JAVASCRIPT:
  case TYPESCRIPT:
    className = wcsdup(Format::acceptableName<WString>(aClassName).c_str());
    break;
  case HAXE:
  case JAVA:
  case SCALA:
  case GO:
  case PYTHON:
    {
      const wchar_t *lastPeriod = wcsrchr(aClassName, L'.');
      if (lastPeriod)
        className = wcsdup(Format::acceptableName<WString>(lastPeriod + 1).c_str());
      else
        className = wcsdup(Format::acceptableName<WString>(aClassName).c_str());
    }
    if (targetLanguage == HAXE || targetLanguage == GO)
      className[0] = toupper(className[0]);
    break;
  case XQUERY:
  case XSLT:
    className = wcsdup(aClassName);
    break;
  case C:
  case EBNF:
  case REX:
  case TXT:
  case XML:
    className = wcsdup(aClassName);
    break;
  }
}

PrintREx::~PrintREx()
{
  delete rex;
  free(static_cast<void *>(className));
}

void PrintREx::write()
{
  const wchar_t *e = L".rex";
  wchar_t *wFileName = ALLOCATE_ARRAY(wchar_t, wcslen(className) + wcslen(e) + 1);
  wcscpy(wFileName, className);
  wcscat(wFileName, e);
  char *rexFileName = Format::wchar2char(wFileName);
  free(wFileName);

  FILE *rexFile = fopen(rexFileName, "wb");
  if (rexFile == 0)
  {
    perror(rexFileName);
    exit(1);
  }

#ifdef WIN32
  const char UTF8BOM[] = {(char) 0xef, (char) 0xbb, (char) 0xbf};
  fwrite(UTF8BOM, 1, sizeof UTF8BOM, rexFile);
#endif

  OutputFile::printHeader(rexFile, REX, argv);
  char *encoded = Encoder::encode(rexGrammar.c_str());

  fwrite("\n", 1, 1, rexFile);
  fwrite(encoded, 1, strlen(encoded), rexFile);

  OutputFile::printFooter(rexFile, REX);

  fclose(rexFile);
  free(encoded);
  free(rexFileName);
}

void PrintREx::printProlog(Grammar *grammar)
{
              print(L"#option nogrammar");
  lineFeed(); print(L"#option noabbreviations");
  lineFeed(); print(L"#option noambiguities");
  lineFeed(); print(L"#option classify");
  lineFeed(); print(L"#option case-sensitive");
  lineFeed(); print(L"#option nosymbols");
  if (parseChars)
  {
    lineFeed(); print(L"#option stringtype=\"char *\"");
    lineFeed(); print(L"#option stringprefix=\"\"");
  }
  if (trace)
  {
    lineFeed(); print(L"#option trace");
  }
  if (tree)
  {
    lineFeed(); print(L"#option tree");
  }
  if (grammar->noLexer)
  {
    lineFeed(); print(L"#option nolexer");
  }
  if (grammar->smaller)
  {
    lineFeed(); print(L"#option smaller");
  }
  if (grammar->faster)
  {
    lineFeed(); print(L"#option faster");
  }

  switch (targetLanguage)
  {
  case CPP:        lineFeed(); print(L"#option cpp");        break;
  case CSHARP:     lineFeed(); print(L"#option csharp");     break;
  case GO:         lineFeed(); print(L"#option go");         break;
  case PYTHON:     lineFeed(); print(L"#option python");     break;
  case HAXE:       lineFeed(); print(L"#option haxe");       break;
  case JAVA:       lineFeed(); print(L"#option java");       break;
  case JAVASCRIPT: lineFeed(); print(L"#option javascript"); break;
  case TYPESCRIPT: lineFeed(); print(L"#option typescript"); break;
  case XQUERY:     lineFeed(); print(L"#option xquery");     break;
  case XSLT:       lineFeed(); print(L"#option xslt");       break;
  case REX:        lineFeed(); print(L"#option rex");        break;
  case SCALA:      lineFeed(); print(L"#option scala");      break;
  default:         internalerr();                            break;
  }

  lineFeed(); print(L"#option class=\"");
              print(className);
              print(L"\"");
  lineFeed();
  lineFeed();
}

void PrintREx::printSets(Grammar *grammar)
{
  print(L"# lookahead sets");
  lineFeed();
  lineFeed();
  for (Lookahead::const_iterator i(grammar->lookaheadSets.begin()); i != grammar->lookaheadSets.end(); ++i)
  {
    print(L"# set ");
    print(format.toString<wchar_t>((int) i->second));
    lineFeed();

    WString string(i->first.toString(grammar, L"\n           ", L",", 69, 2, true));
    print(L"          [");
    print(string.c_str(), false);
    print(L"];");
    lineFeed();
  }
}

void PrintREx::claim(size_t n)
{
  if (width + n <= 80)
  {
    width += n;
  }
  else
  {
    lineFeed();
    print(L"          ");
    width += n;
  }
}

void PrintREx::print(const wchar_t *string, bool check)
{
  if (check)
  {
    claim(wcslen(string));
  }
  rexGrammar += string;
}

void PrintREx::lineFeed()
{
  width = 0;
  print(L"\n");
  width = 0;
}

void PrintREx::visitNodeList(Node *firstNode)
{
  const wchar_t *delimiter = L"";
  for (Node *n = firstNode; n; n = n->followingSibling)
  {
    print(delimiter);
    delimiter = L" ";
    n->accept(*this);
  }
}

void PrintREx::visitOptional(Optional *node)
{
  print(L"(");
  print(L" ");

  Visitor::visitOptional(node);

  print(L" ");
  print(L")");
  print(L" ");
  print(L"?");
}

void PrintREx::visitZeroOrMore(ZeroOrMore *node)
{
  print(L"(");
  print(L" ");

  Visitor::visitZeroOrMore(node);

  print(L" ");
  print(L")");
  print(L" ");
  print(L"*");
}

void PrintREx::visitOneOrMore(OneOrMore *node)
{
  print(L"(");
  print(L" ");

  Visitor::visitOneOrMore(node);

  print(L" ");
  print(L")");
  print(L" ");
  print(L"+");
}

void PrintREx::visitGrammar(Grammar *node)
{
  printProlog(node);

  if (! node->singleLexer)
  {
    printSets(node);
    lineFeed();
  }

  section = TERMINALS;
  for (Token::Code token = 0; token <= node->maxTokenCode; ++token)
  {
    if (token != Token::eWS)
    {
      Production *p = node->terminalProductionByCode[token];
      if (p)
      {
        p->accept(*this);
      }
    }
  }

  for (Node *n = node->terminals; n; n = n->followingSibling)
  {
    if (n->isProduction())
    {
      Production *p = static_cast <Production *> (n);
      if (p->tokenCode < 0)
      {
        p->accept(*this);
      }
    }
  }

  for (Node *n = node->terminals; n; n = n->followingSibling)
  {
    if (! n->isProduction())
    {
      n->accept(*this);
    }
  }

  if (printRex)
  {
    write();
  }

  WString wrapped(L"{");
  wrapped += rexGrammar;
  wrapped += L"}";
  char *encoded = Encoder::encode(wrapped.c_str());
  char *argv[] = {0, encoded};
  rex = LexerGenerator::newInstance();
  rex->setVerbose(verbose);
  rex->setQuiet(node->quiet);

  bool tables = ! node->decisionPoints.empty();
  rex->bind(CGVariable("lrparser", node->states != 0));
  rex->bind(CGVariable("useGlr", node->useGlr));
  rex->bind(CGVariable("anywhitespace", ! node->whitespaceIntroducers.empty()));
  rex->bind(CGVariable("tables", tables));
  rex->bind(CGVariable("nothrow", node->noThrow));
  rex->bind(CGVariable("unlimitedLookahead", unlimitedLookahead));

  if (tables)
  {
    bool simpleWhitespace = ! node->simpleWhitespaceIntroducers.empty();
    bool complexWhitespace = ! node->complexWhitespaceIntroducers.empty();
    bool anyWhitespace = simpleWhitespace || complexWhitespace;

    rex->bind(CGVariable("anyWhitespace", anyWhitespace));
    rex->bind(CGVariable("k", (int) node->k));

    const TiledMap &m1(*node->matchcodeTable->getMap());

    if (node->k > 1)
    {
      rex->bind(CGVariable("lx", m1.getRepresentation(), m1.size(),
                           "LOOKAHEAD",
                           "The lookahead enlargement map. Maps lookahead and token to new lookahead code."));
    }

    rex->bind(CGVariable("lxbits", m1.getBits(), m1.getDepth() + 1, 0, 0));
    rex->bind(CGVariable("lxcols", node->matchcodeTable->getMaxX()));
    rex->bind(CGVariable("lxrows", node->matchcodeTable->getMaxY()));

    const TiledMap &m2(*node->caseidTable->getMap());
    rex->bind(CGVariable("ci", m2.getRepresentation(), m2.size(),
                         "CASEID",
                         "The match-code to case-id map. Maps decision point and lookahead to next action code."));
    rex->bind(CGVariable("cibits", m2.getBits(), m2.getDepth() + 1, 0, 0));
    rex->bind(CGVariable("cicols", node->caseidTable->getMaxX()));
    rex->bind(CGVariable("cirows", node->caseidTable->getMaxY()));
  }

  char **nonterminals = 0;
  int maxNonterminal = node->maxImplicitNonterminalCode > node->maxNonterminalCode
                     ? node->maxImplicitNonterminalCode : node->maxNonterminalCode;
  int *reduce = 0;

  if (node->states && node->states->gotoTable)
  {
    rex->bind(CGVariable("ts", node->states->tokenSet, node->states->lookaheadStates,
                         "TOKENSET",
                         "The parser tokenset table. Maps state to lookahead tokenset code."));
    rex->bind(CGVariable("ax", node->states->appendix, node->states->appendixEnd,
                         "APPENDIX",
                         "The conflict action list table. Contains list of conflicting actions."));
    if (node->states->hasLookback)
    {
      const EntryListMap2D &lookback(node->states->lookbackTable);
      rex->bind(CGVariable("lb", lookback.getRepresentation(), lookback.size(),
                           "LOOKBACK",
                           "The parser lookback table. Maps lookback code and itemset id to next lookback code."));
    }
    const TiledMap &m4(*node->states->gotoTable->getMap());
    rex->bind(CGVariable("gt", m4.getRepresentation(), m4.size(),
                         "GOTO",
                         "The parser goto table. Maps state and nonterminal to next action code."));
    rex->bind(CGVariable("gtbits", m4.getBits(), m4.getDepth() + 1, 0, 0));
    rex->bind(CGVariable("gtcols", node->states->gotoTable->getMaxX()));
    rex->bind(CGVariable("gtrows", node->states->gotoTable->getMaxY()));

    nonterminals = ALLOCATE_ARRAY(char *, maxNonterminal + 1);
    for (int i = 0; i <= node->maxNonterminalCode; ++i)
    {
      nonterminals[i] = Encoder::encode(node->nonterminalProductionByCode[i]->name);
    }
    if (node->maxImplicitNonterminalCode > node->maxNonterminalCode)
    {
      Format format;
      for (int i = node->maxNonterminalCode + 1; i <= node->maxImplicitNonterminalCode; ++i)
      {
        WString implicitName(L"IMPLICIT-");
        implicitName += format.toString<wchar_t>(i, 10);
        nonterminals[i] = Encoder::encode(implicitName.c_str());
      }
    }
    rex->bind(CGVariable("nt", nonterminals, maxNonterminal + 1,
                         "NONTERMINAL",
                         "The nonterminal name table."));
    if (node->states && ! node->distinctCodeAnnotations.empty())
    {
      int reduceEnd = -1;
      int reduceSize = 64;
      reduce = ALLOCATE_ARRAY(int, reduceSize);
      for (Node *n = node->nonTerminals; n; n = n->followingSibling)
      {
        Production *p = static_cast<Production *>(n);
        for (ReduceItems::const_iterator i = p->reduceItems.begin(); i != p->reduceItems.end(); ++i)
        {
          ReduceArguments a = i->first;
          Reduce *r = i->second;
          while (r->reduceCase + 2 >= reduceSize)
          {
            reduceSize <<= 1;
            reduce = REALLOCATE_ARRAY(int, reduce, reduceSize);
          }
          reduce[r->reduceCase] = a.getNonterminalCode();
          reduce[r->reduceCase + 1] = a.getTargetCodeId();
          reduceEnd = Math::max(reduceEnd, r->reduceCase + 2);
        }
      }
      rex->bind(CGVariable("re", reduce, reduceEnd,
                           "REDUCTION",
                           "The reduction code table."));
    }
  }

  rex->run(2, argv);
  free(encoded);
  free(reduce);

  if (nonterminals)
  {
    for (int i = 0; i <= maxNonterminal; ++i)
    {
      free(nonterminals[i]);
    }
    free(nonterminals);
  }

  if (getStaticCode() == 0)
  {
    throw Complaint(L"scanner construction ", L"failed");
  }
}

void PrintREx::visitChoice(Choice *node)
{
  bool root = node->getParent()->isProduction()
           && node->precedingSibling == 0
           && node->followingSibling == 0;
  const wchar_t *open = root ? L"" : L"(";
  const wchar_t *close = root ? L"" : L")";
  const wchar_t *delimiter = open;
  for (NodeList::iterator i = node->cases.begin(); i != node->cases.end(); ++i)
  {
    print(delimiter);
    delimiter = L" | ";
    (*i)->accept(*this);
  }
  if (delimiter == open)
  {
    print(delimiter);
  }
  print(close);
}

void PrintREx::visitProduction(Production *node)
{
  if (! Token::valid(node->tokenCode))
  {
    print(node->name);
    if (node->nonGreedy)
    {
      print(L"?");
    }
    lineFeed();
    print(L"        : ");

    visitNodeList(node->firstChild);

    print(L" ");
    print(L";");
    lineFeed();
  }
  else if (   node->tokenCode >= Token::eFIRST
           || node->grammar->lookaheadAll.contains(node->grammar->tokenSequence(node->tokenCode)))
  {
    if (! node->constant)
    {
      if (node->context)
      {
        claim(wcslen(node->name) + 1 + wcslen(node->context));
        print(node->name, false);
        print(L"^", false);
        print(node->context, false);
      }
      else
      {
        print(node->name);
      }
      print(L" ");
    }
    print(L"(");
    print(format.toString<wchar_t>(node->grammar->externalTokenCode[node->tokenCode]));
    print(L")");
    if (node->nonGreedy)
    {
      print(L"?");
    }
    lineFeed();
    print(L"        : ");

    visitNodeList(node->firstChild);

    print(L" ");
    print(L";");
    lineFeed();
  }
}

void PrintREx::visitRef(Ref *node)
{
  if (node->lexical && node->lexical->context)
  {
    claim(wcslen(node->name) + 1 + wcslen(node->context));
    print(node->name, false);
    print(L"^", false);
    print(node->context, false);
  }
  else
  {
    print(node->name);
  }
}

void PrintREx::visitString(String *node)
{
  if (node->lexical)
  {
    print(format.toString<wchar_t>(node->grammar->externalTokenCode[node->lexical->tokenCode]));
  }
  else
  {
    const wchar_t *quote = L"\"";

    claim(2 + wcslen(node->value) + format.countOccurrences(node->value, *quote));
    print(quote, false);
    for (const wchar_t *v = node->value; *v; ++v)
    {
      if (*v == *quote)
      {
        print(quote, false);
        print(quote, false);
      }
      else
      {
        wchar_t c[] = {*v, 0};
        print(c, false);
      }
    }
    print(quote, false);
  }
}

void PrintREx::visitPreference(Preference *node)
{
  for (NodeList::iterator l = node->lhs.begin(); l != node->lhs.end(); ++l)
    for (NodeList::iterator r = node->rhs.begin(); r != node->rhs.end(); ++r)
  {
    (*l)->accept(*this);
    int spaces = 31 - (int) width;
    if (spaces < 0)
    {
      lineFeed();
      spaces = 31;
    }
    for (int i = 1; i < spaces; ++i)
    {
      print(L" ");
    }
    print(L" > ");
    (*r)->accept(*this);
    print(L";");
    lineFeed();
  }
}

void PrintREx::visitDelimiter(Delimiter *node)
{
  for (NodeList::iterator r = node->rhs.begin(); r != node->rhs.end(); ++r)
  {
    node->lhs->accept(*this);
    int spaces = 31 - (int) width;
    if (spaces < 0)
    {
      lineFeed();
      spaces = 31;
    }
    for (int j = 1; j < spaces; ++j)
    {
      print(L" ");
    }
    print(L" \\ ");
    (*r)->accept(*this);
    print(L";");
    lineFeed();
  }
}

void PrintREx::visitEquivalence(Equivalence *node)
{
  node->lhs->accept(*this);
  int spaces = 31 - (int) width;
  if (spaces < 0)
  {
    lineFeed();
    spaces = 31;
  }
  for (int j = 1; j < spaces; ++j)
  {
    print(L" ");
  }
  print(L" == ");
  node->rhs->accept(*this);
  print(L";");
  lineFeed();
}

void PrintREx::printCharacter(wchar_t c)
{
  if (c == '\'')
  {
    print(L"''''");
  }
  else
  {
    wchar_t quoted[] = {'\'', c, '\'', 0};
    print(quoted);
  }
}

void PrintREx::printCharCode(int c)
{
  if (c == 0x20)
  {
    print(L"\" \"");
  }
  else
  {
    const wchar_t *hex = format.toString<wchar_t>(c, 16);
    claim(wcslen(hex) + 2);
    print(L"0x", false);
    print(hex, false);
  }
}

void PrintREx::visitEndOfFile(EndOfFile *node)
{
  print(L"$");
}

void PrintREx::visitChar(Char *node)
{
  printCharacter(node->character);
}

void PrintREx::visitCharCode(CharCode *node)
{
  printCharCode(node->value);
}

void PrintREx::visitCharRange(CharRange *node)
{
  printCharacter(node->minChar);
  print(L"..");
  printCharacter(node->maxChar);
}

void PrintREx::visitCharCodeRange(CharCodeRange *node)
{
  printCharCode(node->minValue);
  print(L"..");
  printCharCode(node->maxValue);
}

void PrintREx::visitCharClass(CharClass *node)
{
  const wchar_t *open = L"[";
  const wchar_t *delimiter = open;
  for (Node *n = node->firstChild; n != 0 && n->isElement(); n = n->followingSibling)
  {
    print(delimiter);
    delimiter = L", ";
    n->accept(*this);
  }
  if (delimiter == open)
  {
    print(delimiter);
  }
  print(L"]");
}

void PrintREx::visitExclusion(Exclusion *node)
{
  print(L"(");
  node->lhs->accept(*this);
  print(L" ");
  print(L"-");
  print(L" ");
  node->rhs->accept(*this);
  print(L")");
}

void PrintREx::visitContext(Context *node)
{
  node->expr->accept(*this);
  print(L" ");
  print(L"/");
  print(L" ");
  node->context->accept(*this);
}

void PrintREx::visitComplement(Complement *node)
{
  print(L"(. - ");
  Visitor::visitComplement(node);
  print(L")");
}

void PrintREx::visitSequence(Sequence *node)
{
  const wchar_t *open = L"(";
  const wchar_t *delimiter = open;
  for (Node *n = node->firstChild; n; n = n->followingSibling)
  {
    print(delimiter);
    delimiter = L" ";
    n->accept(*this);
  }
  if (delimiter == open)
  {
    print(delimiter);
  }
  print(L")");
}
