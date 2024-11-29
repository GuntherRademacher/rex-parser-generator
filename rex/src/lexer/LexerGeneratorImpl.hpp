#ifndef LEXERGENERATORIMPL_HPP
#define LEXERGENERATORIMPL_HPP

#include "CharClasses.hpp"
#include "Dfa.hpp"

#include "../common/CGVariable.hpp"
#include "../common/Math.hpp"
#include "../common/Decoder.hpp"
#include "../common/OutputFile.hpp"
#include "../common/IntString.hpp"
#include "../common/Strings.hpp"
#include "../common/ErrorMessage.hpp"
#include "../common/FileIO.hpp"

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <time.h>
#include <map>
#include <list>
#include <string>
#include "LexerGenerator.hpp"

#define defaultprintwidth 79

#define RANGE_WIDTH 8
#define _127   ((1 << ((RANGE_WIDTH) - 1)) - 1)
#define _128   (1 << ((RANGE_WIDTH) - 1))
#define _256   (1 << (RANGE_WIDTH))
#define _32767 ((int)(((unsigned int) 1 << (((RANGE_WIDTH) << 1) - 1)) - 1))
#define RANGE(lo,hi) ((hi) > _127 ? (((hi) - _128) * _256 + (lo) - _32767 - 1) : (hi) * _256 + (lo))

#define maxint   INT_MAX

typedef char timestring[64 + 1];

enum messagetype {warning, errormessage};

class LexerGeneratorImpl : public LexerGenerator
{
public:
  LexerGeneratorImpl()
  : instanceCode(0),
    staticCode(0),
    targetLanguage(REX),
    verbose(0),
    quiet(0),
    so(0),
    prn(0),
    soopen(0),
    classify(0),
    embedded(0),
    symbols(0),
    minimize(0),
    selfTest(0),
    trace(0),
    tree(0),
    nolexer(0),
    casesensitive(0),
    faster(0),
    smaller(0),
    printwidth(0),
    append(0),
    stringPrefixDefined(0),
    stringSuffixDefined(0),
    grammar(0),
    showNfa(0),
    showDfa(0),
    abbreviations(0),
    ambiguities(0),
    full(0),
    minquantity(0),
    maxquantity(0),
    compression(0),
    noerrors(0),
    currentnonterminal(0),
    currentrule(0),
    printCount(0),
    indent(0),
    firstchar(0),
    lastchar(0),
    firstcharLhs(0),
    lastcharLhs(0),
    currentchar(0),
    defaultAlphabet(0),
    currentCharRangeList(0),
    currenttoken(0),
    hightoken(0),
    nofactions(0),
    ntlist(0),
    entries(0),
    entrycount(0),
    preferences(0),
    delimiters(0),
    tokenref(0),
    preferred(0),
    delimiter(0),
    nofnfas(0),
    initialtag(0),
    currenttag(0),
    freenfa(0),
    symbolTable(0),
    disambiguationDisabled(0),
    charFolder(0),
    argv(0)
  {
    const char *flags = getenv("FLAGS");
    disambiguationDisabled = flags && strchr(flags, 'D');
  }

  virtual ~LexerGeneratorImpl()
  {
    cleanup();
  }

  virtual void parse(CString input) = 0;
  virtual CString getToken() const = 0;
  virtual int getTokenEnd() const = 0;

  const wchar_t *getInstanceCode() const {return instanceCode;}
  const wchar_t *getStaticCode() const {return staticCode;}
  void setVerbose(bool v = true) {verbose = v;};
  void setQuiet(bool q = true) {quiet = q;};
  int run(int argc, char **argv);

protected:
  wchar_t *instanceCode;
  wchar_t *staticCode;

  void blanklines(int n)
  {
    for (int i = 0; i < n; i++)
    {
      fprintf(prn, "\n");
    }
  }

  void printfilename(const char *value, int lvalue)
  {
    const char quote = '\'';
    fprintf(prn, "%c", quote);
    for (int i = 0; i < lvalue; i++)
    {
      fprintf(prn, "%c", value[i]);
      if (value[i]==quote)
        fprintf(prn, "%c", value[i]);
    }
    fprintf(prn, "%c\n", quote);
  }

  void initialize(int argc, char **argv)
  {
    this->argv = argv;
    const char *commandline = argc > 1 ? argv[1] : "";
    casesensitive = false;
    targetLanguage = C;
    so = 0;
    prn = 0;
    soopen = false;
    classify = false;
    embedded = false;
    symbols = false;
    minimize = false;
    selfTest = false;
    trace = false;
    tree = false;
    casesensitive = false;
    faster = false;
    smaller = false;

    printwidth = 0;
    append = false;
    stringPrefixDefined = false;
    stringSuffixDefined = false;

    grammar = false;
    showNfa = false;
    showDfa = false;
    abbreviations = false;
    ambiguities = false;
    full = false;

    minquantity = 0;
    maxquantity = 0;
    compression = 0;
    noerrors = 0;

    currentnonterminal = 0;
    currentrule = 0;

    printCount = 0;
    indent = 0;

    firstchar = 0;
    lastchar = 0;
    firstcharLhs = 0;
    lastcharLhs = 0;
    currentchar = 0;

    currentCharRangeList = 0;

    currenttoken = -1;
    hightoken = -1;
    nofactions = 0;

    ntlist = 0;
    entries = 0;
    entrycount = 0;
    preferences = 0;
    delimiters = 0;

    tokenref = 0;
    preferred = 0;
    delimiter = 0;
    nofnfas = 0;
    initialtag = 0;
    currenttag = 0;
    freenfa = 0;
    symbolTable = 0;
    tokenDescriptors.clear();

    currentCharRangeList = new GrammarCharSet();

    defaultAlphabet = new GrammarCharSet();
    *defaultAlphabet += CharacterRange(0x9);
    *defaultAlphabet += CharacterRange(0xA);
    *defaultAlphabet += CharacterRange(0xD);
    *defaultAlphabet += CharacterRange(0x20, 0xD7FF);
    *defaultAlphabet += CharacterRange(0xE000, 0xFFFD);
    *defaultAlphabet += CharacterRange(0x10000, 0x10FFFF);

    prn = stdout;
    printwidth = defaultprintwidth;
    noerrors = 0;

    tokenTableName = "token";

    showNfa = false;
    showDfa = false;
    grammar = false;
    abbreviations = false;
    ambiguities = true;
    full = false;
    classify = false;
    minimize = true;
    selfTest = false;
    trace = false;
    tree = false;
    nolexer = false;

    casesensitive = false;
    symbolTable = new SymbolTable(casesensitive);

    symbols = true;
    append = false;

    size_t clen = strlen(commandline);
    embedded = clen >= 2 && commandline[0] == '{' && commandline[clen - 1] == '}';
    if (embedded)
    {
      if (className.empty())
      {
        className = "Scanner";
      }
      outputFile = className;
      sourceGrammar = CString(commandline + 1, clen - 2);
      inputFile = "{}";
    }
    else
    {
      // create output file name from input file name, stripping ".rex"

      const char *lastPeriod = strrchr(commandline, '.');
      if (lastPeriod)
      {
        clen = lastPeriod - commandline;
      }

      outputFile = CString(commandline, clen);

      // calculate class name from file name

      const char *cp = strrchr(outputFile.c_str(), '/');
      if (cp)
      {
        className = cp + 1;
      }
      else
      {
        cp = strrchr(outputFile.c_str(), '\\');
        if (cp)
          className = cp + 1;
        else
          className = outputFile;
      }

      inputFile = commandline;
      blanklines(1);

      char *fileContent = FileIO::getContent(inputFile.c_str());
      if (fileContent == 0)
      {
        fprintf(stdout, "file not found: %s\n", inputFile.c_str());
        noerrors++;
      }
      else
      {
        if (((unsigned char *) fileContent)[0] == 0xef
         && ((unsigned char *) fileContent)[1] == 0xbb
         && ((unsigned char *) fileContent)[2] == 0xbf)
        {
          sourceGrammar = CString(fileContent + 3);
        }
        else
        {
          sourceGrammar = CString(fileContent);
        }
        free(fileContent);
      }
    }
  }

  void disposerule(Rule *thisrule)
  {
    Symbol *s, *sgarbage;
    Rule *r, *rgarbage;

    r= thisrule;
    while (r)
    {
      for (s = r->firstsymbol; s;)
      {
        if (s->kind == compound) disposerule(s->u.subrule);
        sgarbage= s;
        if (s->nextsymbol == r->firstsymbol) s = 0; else s = s->nextsymbol;
        delete sgarbage;
      }
      rgarbage= r;
      if (r->link == thisrule) r = 0; else r= r->link;
      free(rgarbage);
    }
  } /* DisposeRule */

  void semantic(messagetype m, int n)
  {
    if (n != 0)
    {
      const char *text;
      switch (n)
      {
      case 1: text = "invalid character range - lower bound exceeds upper";
        break;
      case 2: text = "character out of range";
        break;
      case 3: text = "multiple nonterminal definition";
        break;
      case 4: text = "token code out of range";
        break;
      case 5: text = "multiple token code definition";
        break;
      case 6: text = "multiple token code assignment";
        break;
      case 7: text = "multiple action assignment";
        break;
      case 8: text = "no token code assigned";
        break;
      case 9: text = "undefined nonterminal";
        break;
      case 10: text = "cannot change CASE SENSITIVITY because symbol table is not empty";
        break;
      case 11: text = "empty character set";
        break;
      case 12: text = "invalid quantity range";
        break;
      case 13: text = "invalid character folding - ranges must have the same size";
        break;
      default:
        internalerr();
        break;
      }

      CString message;
      if (m == warning)
      {
        message += "warning: ";
      }
      else
      {
        message += "error: ";
        noerrors++;
      }
      message += text;

      showErrorContext(sourceGrammar.c_str(), inputFile.c_str(), getTokenEnd(), message.c_str());
    }
  }

  void enqu(List **q, List *e)
  {
    if (*q == 0)
    {
      e->link = e;
    }
    else
    {
      e->link = (*q)->link;
      (*q)->link= e;
    }
    *q = e;
  }

  void setnt(int n)
  {
    currenttoken = -1;
    if (n == 0)
    {
      currentnonterminal = 0;
    }
    else
    {
      CString token = getToken();
      currentnonterminal = symbolTable->insertSymbol(token.c_str(), token.size());
      if (currentnonterminal->rules != 0)
      {
        semantic(errormessage, 3);
      }
      else if (currentnonterminal->code < 0)
      {
        List *obj;
        obj = ALLOCATE(List);
        obj->u.ntptr = currentnonterminal;
        enqu(&ntlist, obj);
      }
    }
  }

  void exopen()
  {
    Rule *r;

    r = new Rule();
    r->firstsymbol = 0;
    r->link = 0;
    if (currentrule == 0)
    {
      r->rule = mainrule;
      r->main = 0;
    }
    else
    {
      r->rule = subrule;
      r->main = currentrule;
    }
    currentrule = r;
  }

  void chclos(int n)
  {
    GrammarCharSet *gcs = new GrammarCharSet(*currentCharRangeList);
    if (n > 0)
    {
      currentrule->firstsymbol->u.specification = gcs;
      if (gcs->empty()) semantic(errormessage, 11);
    }
    else if (currentrule->firstsymbol->nextsymbol == currentrule->firstsymbol)
    {
      currentrule->firstsymbol->u.specification = gcs;
      createExclusion();
    }
    else
    {
      currentrule->firstsymbol->kind = compound;
      currentrule->firstsymbol->u.subrule = 0;

      exopen();
      define(charset);
      currentrule->firstsymbol->u.specification = gcs;
      syclos(none);
      createExclusion();
      exclos();
    }
  }

  void define(SymbolType k, const char *value = 0)
  {
    Symbol *s;
    s = new Symbol();
    s->kind = k;
    s->operation = none;
    s->min = 1;
    s->max = 1;

    if (k == slash)
    {
      if (currentnonterminal)
      {
        currentnonterminal->istoken = true;
      }

      if (currentrule->firstsymbol)
      {
        Symbol *f = currentrule->firstsymbol;
        s->u.lhs = f->nextsymbol;
        f->nextsymbol = 0;
      }
      else
      {
        s->u.lhs = 0;
      }

      s->nextsymbol = s;
      currentrule->firstsymbol = s;
    }
    else
    {
      if (currentrule->firstsymbol == 0)
      {
        s->nextsymbol = s;
      }
      else
      {
        s->nextsymbol = currentrule->firstsymbol->nextsymbol;
        currentrule->firstsymbol->nextsymbol = s;
      }
      currentrule->firstsymbol = s;

      switch (k)
      {
      case nonterminal:
      case charstring:
        if (value)
        {
          s->u.name = symbolTable->insertSymbol(value, strlen(value));
        }
        else
        {
          CString token = getToken();
          s->u.name = symbolTable->insertSymbol(token.c_str(), token.size());
        }
        break;

      case charset:
        s->u.specification = 0;
        currentCharRangeList->clear();
        break;

      case compound:
        s->u.subrule = 0;
        break;

      case dollar:
        break;                                   // no parameters, all done

      case slash:
      case exclusion:
        internalerr();
        break;
      }
    }
  }

  int getInteger()
  {
    CString token = getToken();
    if (          token.size()  >  2
      &&          token[0]     == '0'
      && tolower (token[1])    == 'x')
    {
      return strtol(token.c_str() + 2, 0, 16);
    }
    else
    {
      return strtol(token.c_str(), 0, 10);
    }
  }

  void addRange()
  {
    if (lastchar >= CHARACTER_MAX)
    {
      semantic(errormessage, 2);
      lastchar = CHARACTER_MAX - 1;
    }
    if (firstchar > lastchar)
    {
      semantic(errormessage, 1);
    }
    else
    {
      *currentCharRangeList += CharacterRange(firstchar, lastchar);
    }
  }

  void equivalence()
  {
    int sizeLhs = lastcharLhs - firstcharLhs + 1;
    int sizeRhs = lastchar - firstchar + 1;
    if (sizeLhs < 0 || sizeRhs < 0)
    {
      semantic(errormessage, 1);
    }
    else if (sizeLhs != sizeRhs)
    {
      semantic(errormessage, 13);
    }
    else
    {
      if (charFolder == 0)
      {
        charFolder = new CharFolder();
      }
      charFolder->add(CharacterRange(firstcharLhs, lastcharLhs), CharacterRange(firstchar, lastchar));
    }
  }

  void syclos(ClosureType c)
  {
    Symbol *s = currentrule->firstsymbol;
    s->operation = c;
    if (c == quantity)
    {
      s->min = minquantity;
      s->max = maxquantity;
      if (maxquantity >0 && maxquantity < minquantity)
      {
        semantic(errormessage, 12);
      }
    }

    if (s->kind == compound)
    {
      Rule *r = s->u.subrule;
      if (r != 0)
      {
        s->u.subrule = r->link;
        r->link = 0;
      }
    }
  }

  void createExclusion()
  {
    // note that parentheses are mandatory when combining a sequence
    // with an exclusion, because there is no precedence defined,
    // i.e.
    //      A B - C
    // is invalid syntactically, so it must be written as either
    //     (A B) - C
    // or
    //      A (B - C)

    Symbol *exclude;
    exclude = new Symbol();
    exclude->kind = exclusion;
    exclude->operation = none;
    exclude->min = 1;
    exclude->max = 1;

    exclude->u.rhs = currentrule->firstsymbol;
    currentrule->firstsymbol = exclude;

    Symbol *predecessor = exclude->u.rhs->nextsymbol;
    exclude->u.rhs->nextsymbol = 0;

    if (predecessor == exclude->u.rhs) // single item - supply default lhs
    {
      Symbol *any;
      any = new Symbol();
      any->nextsymbol = 0;
      any->kind = nonterminal;
      any->operation = none;
      any->min = 1;
      any->max = 1;
      any->u.name = symbolTable->insertSymbol(".", 1);

      exclude->nextsymbol = exclude;
      exclude->u.lhs = any;
    }
    else if (predecessor->nextsymbol == exclude->u.rhs) // two items - lhs and rhs
    {
      exclude->nextsymbol = exclude;
      exclude->u.lhs = predecessor;
      exclude->u.lhs->nextsymbol = 0;
    }
    else // more than two items
    {
      exclude->nextsymbol = predecessor;
      while (predecessor->nextsymbol->nextsymbol != exclude->u.rhs)
      {
        predecessor = predecessor->nextsymbol;
      }
      exclude->u.lhs = predecessor->nextsymbol;
      exclude->u.lhs->nextsymbol = 0;
      predecessor->nextsymbol = exclude;
    }
  }

  void exclos()
  {
    if (currentrule->firstsymbol != 0)
    {
      Symbol *s = currentrule->firstsymbol;
      currentrule->firstsymbol = s->nextsymbol;
      s->nextsymbol = 0;
    }

    if (currentrule->firstsymbol && currentrule->firstsymbol->kind == slash)
    {
      currentrule->firstsymbol->u.rhs = currentrule->firstsymbol->nextsymbol;
      currentrule->firstsymbol->nextsymbol = 0;
    }

    switch (currentrule->rule)
    {
    case mainrule:
      if (currentnonterminal != 0)
      {
        if (currentnonterminal->rules == 0)
          currentrule->link = currentrule;
        else
        {
          currentrule->link = currentnonterminal->rules->link;
          currentnonterminal->rules->link = currentrule;
        }
        currentnonterminal->rules = currentrule;
      }
      else if (currenttoken < 0)
      {
        internalerr();
      }
      else
      {
        if (tokenDescriptors.get(currenttoken).u.rules == 0)
          currentrule->link = currentrule;
        else
        {
          currentrule->link = tokenDescriptors.get(currenttoken).u.rules->link;
          tokenDescriptors.get(currenttoken).u.rules->link = currentrule;
        }
        tokenDescriptors.get(currenttoken).u.rules = currentrule;
      }
      currentrule = 0;
      break;

    case subrule:
      if (currentrule->main->firstsymbol->u.subrule == 0)
      {
        currentrule->link = currentrule;
      }
      else
      {
        currentrule->link = currentrule->main->firstsymbol->u.subrule->link;
        currentrule->main->firstsymbol->u.subrule->link = currentrule;
      }
      currentrule->main->firstsymbol->u.subrule = currentrule;
      currentrule= currentrule->main;
      break;
    }
  }

  void rbegin()
  {
    while (currentrule)
    {
      if (currentrule->firstsymbol) syclos(none);
      exclos();
    }
  }

  bool checktoken()
  {
    if (currenttoken < 0)
    {
      semantic(errormessage, 4);
      currenttoken = -1;
      return false;
    }
    else
    {
      if (hightoken < currenttoken) hightoken = currenttoken;
      return true;
    }
  }

  void newentry()
  {
    entrylist *entryptr;

    entryptr = ALLOCATE(entrylist);
    entryptr->elist = 0;
    entryptr->dfa = 0;
    if (entries == 0) entryptr->link = entryptr;
    else
    {
      entryptr->link= entries->link;
      entries->link= entryptr;
    }
    entries= entryptr;
    ++entrycount;
  }

  entryrec *ref(entrytype e, bool used)
  {
    entryrec *eptr;
    eptr = ALLOCATE(entryrec);

    switch (e)
    {
    case tokencode:
      checktoken();
      tokenDescriptors[currenttoken].used |= used;
      eptr->named = false;
      eptr->ntptr = 0;
      eptr->tokencode = currenttoken;
      break;
    case tokenname:
      {
        CString token = getToken();
        SymbolTableEntry *s = symbolTable->insertSymbol(token.c_str(), token.size());
        s->used |= used;
        s->istoken = true;
        eptr->named = true;
        eptr->ntptr = s;
        eptr->tokencode = -1;
      }
      break;
    }
    return eptr;
  }

  void collectentry(entryrec *eptr)
  {
    List *obj;
    obj = ALLOCATE(List);
    obj->u.eptr = eptr;
    enqu(&entries->elist,obj);
  }

  void preference(entryrec *preferred, entryrec *nonpreferred)
  {
    preferencerec *p;
    p = ALLOCATE(preferencerec);
    p->preferred = preferred;
    p->nonpreferred = nonpreferred;

    List *obj;
    obj = ALLOCATE(List);
    obj->u.pptr = p;
    enqu(&preferences, obj);
  }

  void delimited(SymbolTableEntry *delimiter, entryrec *tokenref)
  {
    delimiterrec *d;
    d = ALLOCATE(delimiterrec);
    d->delimiter = delimiter;
    d->delimited = tokenref;

    List *l;
    l = ALLOCATE(List);
    l->u.dptr = d;
    enqu(&delimiters, l);
  }

  void closeallrules()
  {
    for (SymbolTable::iterator i(symbolTable->begin()); i != symbolTable->end(); ++i)
    {
      SymbolTableEntry *s(i->second);
      if (s->rules)
      {
        s->rules = Rule::close(s->rules);
      }
    }
  }

  void closetokens()
  {
    for (TokenDescriptors::const_iterator i = tokenDescriptors.begin(); i != tokenDescriptors.end(); ++i)
    {
      TokenDescriptor &t(tokenDescriptors.get(i->first));
      if (   t.definition == numbered
          && t.u.rules != 0)
      {
        t.u.rules = Rule::close(t.u.rules);
      }
    }

    if (delimiters)
    {
      List *l = delimiters;
      do
      {
        delimiterrec *d = l->u.dptr;
        TokenId t = d->delimited->named
                  ? d->delimited->ntptr->code
                  : d->delimited->tokencode;
        if (t >= 0)
        {
          if (tokenDescriptors.get(t).definition == named)
          {
            tokenDescriptors.get(t).u.nonterminal->trailingcontext = d->delimiter;
          }
          else
          {
            tokenDescriptors.get(t).u.trailingcontext = d->delimiter;
          }
        }
        l = l->link;
      }
      while (l != delimiters);
    }
  }

  void collect(List **tokenset, int newtoken, int contextsize)
  {
    List *last;
    List *current;
    List *next;

    if (*tokenset == 0)
    {
      *tokenset = ALLOCATE(List);
      (*tokenset)->u.code = newtoken;
      (*tokenset)->u.contextsize = contextsize;
      (*tokenset)->link = *tokenset;
    }
    else
    {
      last = *tokenset;
      do
      {
        next = last->link;
        if (next->u.code > newtoken)
          last = next;
        else
        {
          if (next->u.code != newtoken)
          {
            current = ALLOCATE(List);
            current->u.code = newtoken;
            current->u.contextsize = contextsize;
            current->link = next;
            last->link = current;
          }
          else if (next->u.contextsize > contextsize)
          {
            next->u.contextsize = contextsize;
          }
          newtoken = -1;
          last = *tokenset;
        }
      }
      while (last!=*tokenset);

      if (newtoken >= 0)
      {
        *tokenset = ALLOCATE(List);
        (*tokenset)->u.code = newtoken;
        (*tokenset)->u.contextsize = contextsize;
        (*tokenset)->link = last->link;
        last->link = *tokenset;
      }
    }
  }

  bool contains(List *tokenset, int token)
  {
    if (tokenset)
    {
      List *t = tokenset;
      do
      {
        t = t->link;
        if (t->u.code <= token)
        {
          return t->u.code == token;
        }
      }
      while (t != tokenset);
    }
    return false;
  }

  void finish()
  {
    currentnonterminal = symbolTable->find(".");
    if (currentnonterminal && currentnonterminal->rules == 0)
    {
      currentnonterminal->used = true;  // avoid "unused" complaint, when defined implicitly

      List *obj;
      obj = ALLOCATE(List);
      obj->u.ntptr = currentnonterminal;
      enqu(&ntlist, obj);

      exopen();

      define(charset);

      currentrule->firstsymbol->u.specification = new GrammarCharSet(*defaultAlphabet);

      syclos(none);
      exclos();
    }

    rbegin();
    if (entries == 0)
    {
      newentry();

      for (TokenDescriptors::const_iterator i = tokenDescriptors.begin(); i != tokenDescriptors.end(); ++i)
      {
        const TokenDescriptor &t(tokenDescriptors.get(i->first));
        if (t.definition != undefined)
        {
          currenttoken = i->first;
          collectentry(ref(tokencode, true));
        }
      }
    }

    if (preferences)
    {
      List *l = preferences;

      do
      {
        preferencerec *p = l->u.pptr;
        int n;
        for (n = 0; n < 2; ++n)
        {
          entryrec *pref = n
                         ? p->nonpreferred
                         : p->preferred;
          if (pref->named)
          {
            if (pref->ntptr->code >= 0)
            {
              pref->tokencode = pref->ntptr->code;
            }
            else
            {
              noerrors++;
              fprintf(prn, "--Error-- No token code defined for %s\n", pref->ntptr->name);
              pref->ntptr->code = 0;
            }
          }
        }

        if (noerrors == 0)
        {
          TokenDescriptor &t(tokenDescriptors.get(p->preferred->tokencode));
          if (t.overrules == 0)
          {
            t.overrules = new OverruleSet();
          }
          t.overrules->insert(p->nonpreferred->tokencode);
        }

        l = l->link;
      }
      while (l != preferences);
    }

    tokenDescriptors.setEmbedded(embedded);

    switch (targetLanguage)
    {
    case HAXE:
    case JAVA:
    case JAVASCRIPT:
    case TYPESCRIPT:
    case SCALA:
    case GO:
    case PYTHON:
    case CPP:
    case CSHARP:
    case XQUERY:
    case XSLT:
    case REX:
      tokenDescriptors.setSelfContained(true);
      break;

    case C:
      tokenDescriptors.setSelfContained(false);
      break;

    case XML:
    case EBNF:
    case TXT:
      internalerr();
      break;
    }

    if (tokenDescriptors.getSelfContained())
    {
      classify = true;

      if (targetLanguage == CPP)
      {
        if (stringType.empty())
        {
          stringType = "wchar_t *";
        }
        if (! stringPrefixDefined)
        {
          stringPrefix = "L";
        }
      }
    }

    if (   tokenDescriptors.getErrorCode() >= 0
        && tokenDescriptors.getErrorCode() <= hightoken
        && tokenDescriptors.find(tokenDescriptors.getErrorCode()) != tokenDescriptors.end())
    {
      noerrors++;
      fprintf(prn, "--Error-- Error code also defined as token code\n");
    }

    if (tableName.empty()) switch (targetLanguage)
    {
    case C:
      tableName = "scanner";
      break;

    case CPP:
    case CSHARP:
    case HAXE:
    case JAVA:
    case JAVASCRIPT:
    case TYPESCRIPT:
    case SCALA:
    case GO:
    case PYTHON:
    case XQUERY:
    case XSLT:
      tableName = "tx";
      break;

    case REX:
      break;

    case EBNF:
    case XML:
    case TXT:
      internalerr();
      break;
    }
  }

  void assignTokenId(int id)
  {
    currenttoken = id;
    if (checktoken())
    {
      TokenDescriptor &t(tokenDescriptors[currenttoken]);
      if (t.definition != undefined)
      {
        semantic(errormessage, 5);
        currenttoken = -1;
      }
      else if (currentnonterminal != 0)
      {
        if (currentnonterminal->code < 0)
        {
          currentnonterminal->code = currenttoken;
          t.definition = named;
          t.u.nonterminal = currentnonterminal;
        }
        else
        {
          semantic(errormessage, 6);
          currenttoken = -1;
        }
      }
      else
      {
        t.definition = numbered;
        t.u.rules = 0;
        t.u.effectiveCharSet = 0;
        t.u.trailingcontext = 0;
      }
    }
  }

  void assact()
  {
    if (currentnonterminal != 0)
    {
      currenttoken = currentnonterminal->code;
    }

    if (currenttoken < 0)
    {
      semantic(errormessage, 8);
    }
    else if (tokenDescriptors.get(currenttoken).lexaction != 0)
    {
      semantic(errormessage, 7);
    }
    else
    {
      CString token = getToken();
      SymbolTableEntry *s = symbolTable->insertSymbol(token.c_str(), token.size());
      tokenDescriptors.get(currenttoken).lexaction = s;
      if (tokenDescriptors.get(currenttoken).lexaction->code < 0)
      {
        nofactions++;
        tokenDescriptors.get(currenttoken).lexaction->code = nofactions - 1;
      }
    }
  }

  void assngr()
  {
    if (currentnonterminal != 0)
    {
      currentnonterminal->ungreedy = true;
      currenttoken = currentnonterminal->code;
    }

    if (currenttoken >= 0)
    {
      tokenDescriptors.get(currenttoken).nongreedy = true;
    }
  }

  CString getString()
  {
    CString token = getToken();
    char doubledQuote[] = {token[0], token[0], 0};
    token = token.substr(1, token.size() - 2);
    for (size_t index = 0; CString::npos != (index = token.find(doubledQuote, index)); ++index)
    {
      token.erase(index, 1);
    }
    return token;
  }

  void setCaseSensitive(bool cs)
  {
    if (casesensitive != cs)
    {
      if (! symbolTable->empty())
      {
        semantic(errormessage, 10);
      }
      else
      {
        delete symbolTable;

        casesensitive = cs;
        symbolTable = new SymbolTable(cs);
      }
    }
  }

#include "LegacyDfa.hpp"

  class CharPtrString : public std::basic_string<const char *>
  {
  public:
    CharPtrString() = default;
  };

  void countchars(int n);
  void printentries();
  int countoperation(const Symbol *s);
  void printoperation(const Symbol *s);
  void printname(const Symbol *s);
  void printchar(Character c);
  template<typename T> void printCharSet(const T *set);
  void printItem(const Symbol *s);
  void printsubrule(const Rule *r, bool list);
  void printrules(const Rule *r);
  void printcode(int n, SymbolTableEntry *lexaction = 0);
  void printgrammar();
  void printvalue(const char *name, const char *value, int lvalue);
  void printoptions();
  void outopen(const char *n);
  void p_outcls();

  NfaState *createnfa(NfaType kind, NfaState *shift);
  NfaState *charsetnfa(const GrammarCharSet &cs, GrammarCharClasses &gcc);
  NfaState *atomicnfa(Symbol *s, GrammarCharClasses &gcc);
  void replace(NfaState *oldnfa, NfaState *newnfa, NfaState *nfa);
  NfaState *nfalink(NfaState *nfa, NfaState *current);
  NfaState *factornfa(Symbol *s, ClosureType c, GrammarCharClasses &gcc);
  NfaState *termnfa(Symbol *s, GrammarCharClasses &gcc);
  NfaState *exprnfa(Rule *r, GrammarCharClasses &gcc);
  NfaState *recomputednfa(Symbol *s, GrammarCharClasses &outergcc);
  NfaState *tokennfa(TokenId t, AnnotationType annotationType,
                     Symbol *lhs, Symbol *rhs,
                     bool rhsHasVariableLength,
                     NfaState *nfa, bool &hasUnsupportedLookahead,
                     GrammarCharClasses &gcc);
  NfaState *tokennfa(TokenId t, Rule *rules, SymbolTableEntry *trailingcontext, GrammarCharClasses &gcc);
  void clearnfano(NfaState *nfa);
  void countnfareferences(NfaState *nfa);
  void deleteunreferencednfa(NfaState *nfa);
  void deletenfa(NfaState *&nfa);
  void dumpMap(const char *prefix, const char *name, const int *map, size_t mapSize);
  void dumpactions();
  void getTokenNames(CharPtrString &tokenNames);
  void dumpTokenNames();
  void dumpconflicts();
  void getLength(const Rule *r, int &min, int &max);
  void getLength(const Symbol *s, int &min, int &max);
  void getTokenStrings(CharPtrString &tokenStrings);
  void dumpTokenStrings(CharPtrString &tokenStrings);
  template <class CHARSET> void printClasses(const CharClasses<CHARSET> &classes, const GrammarCharClasses *gcc = 0);
  void printDfaState(DfaState *dfa);
  void printDfa(DfaState *dfa, const char *when = 0);
  void printAnnotation(const Annotation &annotation);
  void printNfaState(NfaState *nfa);
  void printNfa(const TokenDescriptors &tokenDescriptors);
  void charSetOptimization(Symbol *s, GrammarCharSets &ccs);
  void charSetOptimization(Rule **r, const GrammarCharSet **ecs, GrammarCharSets &ccs);
  void charSetOptimization(GrammarCharSets &ccs);
  void nfaconstruction(GrammarCharClasses &gcc);
  void statistics(DfaStates &dfaStates);
  void dfaConstruction(const GrammarCharClasses &gcc, DfaStates &dfaStates);
  void testCharSets(int c);
  void cleanup();
  void bind(CGVariable v) {extraVars.push_back(v);}

  TargetLanguage targetLanguage;

  bool verbose;
  bool quiet;

  CString sourceGrammar;

  FILE *so;
  FILE *prn;
  bool soopen;

  bool classify;
  bool embedded;
  bool symbols;
  bool minimize;
  bool selfTest;
  bool trace;
  bool tree;
  bool nolexer;
  bool casesensitive;
  bool faster;
  bool smaller;

  CString inputFile;

  int printwidth;

  bool append;
  CString prefix;
  CString suffix;
  CString tableName;
  CString packageName;
  CString targetFile;
  CString outputFile;
  CString className;
  CString stringPrefix;
  CString stringSuffix;
  CString stringType;
  CString tokenTableName;
  bool stringPrefixDefined;
  bool stringSuffixDefined;

  bool grammar;
  bool showNfa;
  bool showDfa;
  bool abbreviations;
  bool ambiguities;
  bool full;

  int minquantity;
  int maxquantity;
  int compression;
  int noerrors;

  SymbolTableEntry *currentnonterminal;
  Rule *currentrule;

  int printCount;
  int indent;

  Character firstchar;
  Character lastchar;
  Character firstcharLhs;
  Character lastcharLhs;
  Character currentchar;

  GrammarCharSet    *defaultAlphabet;
  GrammarCharSet    *currentCharRangeList;

  int currenttoken;
  int hightoken;
  int nofactions;

  List *ntlist;
  entrylist *entries;
  size_t entrycount;
  List *preferences;
  List *delimiters;

  entryrec *tokenref;
  entryrec *preferred;
  SymbolTableEntry *delimiter;

  int nofnfas;
  int initialtag;
  int currenttag;
  NfaState *freenfa;

  SymbolTable *symbolTable;

  TokenDescriptors tokenDescriptors;

  Format format;
  bool disambiguationDisabled;

  VarsInInsertionOrder extraVars;
  CharFolder *charFolder;

  char **argv;
};

#endif
