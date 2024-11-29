#include "../common/Memory.hpp"
#include "../common/CompressedMap.hpp"

#include "LexerGeneratorImpl.hpp"
#include "CodeGenerator.hpp"
#include <memory>

void LexerGeneratorImpl::countchars(int n)
{
  if (n < 0)
  {
    indent = -n;
  }
  else if (n == 0)
  {
    if (printCount > indent)
    {
      printCount = printwidth;
    }
    else while (printCount != indent)
    {
      printCount++;
      fprintf(prn, " ");
    }
  }
  else
  {
    printCount += n;
    if (printCount >= printwidth - 1)
    {
      printCount = indent + n;
      fprintf(prn, "\n");
      if (indent > 0) fprintf(prn, "%*c", indent, ' ');
    }
  }
}

void LexerGeneratorImpl::printentries()
{
  entrylist *entryptr = entries;
  do
  {
    entryptr = entryptr->link;

    List *obj = entryptr->elist;
    if (obj)
    {
      printCount = printwidth;
      countchars(-10);
      char delimiter = '[';

      do
      {
        obj = obj->link;

        countchars(1);
        fprintf(prn, "%c", delimiter);

        if (obj->u.eptr->named)
        {
          countchars((int) strlen(obj->u.eptr->ntptr->name));
          fprintf(prn, "%s", obj->u.eptr->ntptr->name);
        }
        else
        {
          countchars((int) Format::width(obj->u.eptr->tokencode));
          fprintf(prn, "%d", obj->u.eptr->tokencode);
        }
        countchars(-11);
        delimiter = ',';

      }
      while (obj != entryptr->elist);

      countchars(2);
      fprintf(prn, "];");
      printCount = printwidth;
    }
  }
  while (entryptr != entries);
}

int LexerGeneratorImpl::countoperation(const Symbol *s)
{
  int count;
  if (s->operation == quantity)
  {
    count = 2 + (int) Format::width(s->min)
          + s->min == s->max ? 0 : 1
          + s->min <  s->max ? 0 : (int) Format::width(s->max);
  }
  else if (s->operation == none)
    count = 0;
  else
    count = 1;
  return count;
}

void LexerGeneratorImpl::printoperation(const Symbol *s)
{

  switch (s->operation)
  {
  case closure:         fprintf(prn, "*"); break;
  case positiveclosure: fprintf(prn, "+"); break;
  case optional:        fprintf(prn, "?"); break;
  case quantity:
    if (s->max <= s->min)
      fprintf(prn, "{%d}", s->min);
    else
      fprintf(prn, "{%d,%d}", s->min, s->max);
    break;
  case none:
    break;
  }
  fprintf(prn, " ");
}

void LexerGeneratorImpl::printname(const Symbol *s)
{
  int size = (int) strlen(s->u.name->name) + 1 + countoperation(s);
  countchars(size);
  fprintf(prn, "%s", s->u.name->name);
  printoperation(s);
}

void LexerGeneratorImpl::printchar(Character c)
{
  if (c <= 255 && isprint(c))
  {
    if (c == '\'')
    {
      countchars(4);
      fprintf(prn,"''''");
    }
    else
    {
      countchars(3);
      fprintf(prn,"'%c'", c);
    }
  }
  else
  {
    countchars((int) Format::width(c));
    fprintf(prn, "%d", (int) c);
  }
}

template<typename T>
void LexerGeneratorImpl::printCharSet(const T *set)
{
  char delimiter = '[';

  for (typename T::RangeIterator i(set->rangeBegin());
       i != set->rangeEnd();
       ++i)
  {
    CharacterRange cr(*i);
    Character c(cr.getLow());
    Character d(cr.getHigh());

    countchars(1);
    fprintf(prn, "%c", delimiter);
    delimiter = ',';
    printchar(c);

    if (c + 1 == d)
    {
      countchars(1);
      fprintf(prn, ",");
      printchar(d);
    }
    else if (c != d)
    {
      countchars(2);
      fprintf(prn, "..");
      printchar(d);
    }
  }

  if (delimiter == '[')
  {
    countchars(2);
    fprintf(prn, "[ ");
  }
  countchars(1);
  fprintf(prn, "]");
}

void LexerGeneratorImpl::printItem(const Symbol *s)
{
  switch (s->kind)
  {
  case nonterminal:
  case charstring:
    printname(s);
    break;

  case charset:
    printCharSet(s->u.specification);
    countchars(2 + countoperation(s));
    printoperation(s);
    break;

  case compound:
    countchars(2);
    fprintf(prn,"( ");
    printsubrule(s->u.subrule, true);
    countchars(2 + countoperation(s));
    fprintf(prn,")");
    printoperation(s);
    break;

  case exclusion:
  case slash:
    {
      for (Symbol *p = s->u.lhs; p; p = p->nextsymbol)
      {
        printItem(p);
      }

      countchars(2);
      fprintf(prn, s->kind == exclusion ? "- " : "/ ");

      for (Symbol *p = s->u.rhs; p; p = p->nextsymbol)
      {
        printItem(p);
      }

      countchars(countoperation(s));
      printoperation(s);
    }
    break;

  case dollar:
    countchars(2 + countoperation(s));
    fprintf(prn,"$");
    printoperation(s);
    break;
  }
}

void LexerGeneratorImpl::printsubrule(const Rule *r, bool list)
{
  do
  {
    for (Symbol *s = r->firstsymbol; s; s = s->nextsymbol)
    {
      printItem(s);
    }
    r = r->link;
    if (list && r)
    {
      countchars(2);
      fprintf(prn,"| ");
    }
  }
  while (r && list);
}

void LexerGeneratorImpl::printrules(const Rule *r)
{
  char c;

  if (r == 0)
  {
    countchars(-25);
    countchars(0);
    fprintf(prn, "...is undefined ");
  }
  else
  {
    c= '=';
    do
    {
      countchars(-25);
      countchars(0);
      countchars(2);
      fprintf(prn, "%c ", c);
      c = '|';

      countchars(-27);
      printsubrule(r, false);
      printCount = printwidth;
      r = r->link;
    }
    while (r);
  }
  fprintf(prn, ";");
}

void LexerGeneratorImpl::printcode(int n, SymbolTableEntry *lexaction)
{
  countchars ((int) Format::width(n) + 1);
  fprintf(prn, "(%d", n);
  if (lexaction)
  {
    countchars((int) strlen(lexaction->name) + 1);
    fprintf(prn,",%s", lexaction->name);
  }
  countchars(2);
  fprintf(prn,") ");
}

void LexerGeneratorImpl::printgrammar()
{
  List *obj;
  SymbolTableEntry *s;

  fprintf(prn,"          Input Grammar:\n");
  fprintf(prn,"          --------------\n");
  printentries();
  fprintf(prn, "\n");
  obj= ntlist;
  if (obj)
  {
    do
    {
      obj = obj->link;
      printCount = printwidth;
      countchars(-10);
      s= obj->u.ntptr;
      countchars((int) strlen(s->name) + 1);
      fprintf(prn,"%s ", s->name);
      if (s->code >= 0) printcode(s->code, tokenDescriptors.get(s->code).lexaction);
      printrules(s->rules);
    }
    while (obj != ntlist);
  }

  fprintf(prn, "\n");

  for (TokenDescriptors::const_iterator i = tokenDescriptors.begin(); i != tokenDescriptors.end(); ++i)
  {
    TokenId id(i->first);
    const TokenDescriptor &t(tokenDescriptors.get(id));
    if (t.definition == numbered)
    {
      printCount = printwidth;
      countchars(-10);
      printcode(id, t.lexaction);
      countchars(-25);
      countchars(0);
      printrules(t.u.rules);
    }
  }
  fprintf(prn, "\n");
  blanklines(1);
}

void LexerGeneratorImpl::printvalue(const char *name, const char *value, int lvalue)
{
  if (lvalue > 0)
  {
    fprintf(prn,"                      %s=", name);
    printfilename(value, lvalue);
  }
}

void LexerGeneratorImpl::outopen(const char *n)
{
  if (! soopen)
  {
    char *fileName;
    if (targetFile.size() > 0)
    {
      fileName = strdup(targetFile.c_str());
    }
    else
    {
      CString name = prefix;
      name += n;
      name += suffix;
      if (name.find('.') == CString::npos)
      {
        CString extension = ".";
        extension += OutputFile::extension(targetLanguage);
        fileName = Format::newFileName(name.c_str(), extension.c_str());
      }
      else
      {
        fileName = strdup(name.c_str());
      }
    }

    const char *mode = embedded || append ? "ab" : "wb";
    if ((so = fopen(fileName, mode)) == 0)
    {
      fprintf(prn, "open failed on file ");
      printfilename(fileName, strlen(fileName));
      free(fileName);
      exit(1);
    }
    else
    {
      soopen = true;

      if (! embedded)
      {
        fprintf(prn, "          ");
        if (append)
          fprintf(prn, "Appending output to ");
        else
          fprintf(prn, "Writing output file ");
        printfilename(fileName, strlen(fileName));
        OutputFile::printHeader(so, targetLanguage, argv);
      }
    }
  }
}

void LexerGeneratorImpl::p_outcls()
{
  if (! embedded)
  {
    OutputFile::printFooter(so, targetLanguage, "EoF");
  }

  fclose(so);
  soopen = false;
}

NfaState *LexerGeneratorImpl::createnfa(NfaType kind, NfaState *shift)
{
  NfaState *nfa;

  if (freenfa == 0)
  {
    nfa = ALLOCATE(NfaState);
  }
  else
  {
    nfa = freenfa;
    freenfa = nfa->shift;
  }

  nofnfas++;
  nfa->nfano = nofnfas;
  nfa->tag = initialtag;

  nfa->shift = shift;
  nfa->kind = kind;
  return nfa;
}

NfaState *LexerGeneratorImpl::recomputednfa(Symbol *s, GrammarCharClasses &outergcc)
{
  GrammarCharClasses innergcc(charFolder);

  NfaState *nfa = 0;
  bool hasUnsupportedLookahead = false;
  bool nongreedy = false;

  if (s->kind == exclusion)
  {
    nfa = tokennfa(currenttoken, NEGATING, s->u.rhs, 0, false, nfa, hasUnsupportedLookahead, innergcc);
    nfa = tokennfa(currenttoken, FINAL,    s->u.lhs, 0, false, nfa, hasUnsupportedLookahead, innergcc);
  }
  else if (s->kind == nonterminal && s->u.name->ungreedy)
  {
    s->u.name->ungreedy = false;

    nfa = tokennfa(currenttoken, FINAL, s, 0, false, nfa, hasUnsupportedLookahead, innergcc);

    s->u.name->ungreedy = true;
    nongreedy = true;
  }
  else
  {
    internalerr();
  }

  innergcc.arrange(false);

  entrylist entryptr;
  entryptr.elist = 0;
  entryptr.dfa = 0;
  entryptr.link = &entryptr;

  entryrec eptr;
  eptr.named = false;
  eptr.ntptr = 0;
  eptr.tokencode = currenttoken;

  List obj;
  obj.u.eptr = &eptr;
  enqu(&entryptr.elist, &obj);

  TokenDescriptors td;
  TokenDescriptor &t(td[currenttoken]);
  t.nfa = nfa->shift;
  t.definition = numbered;
  t.used = true;
  t.nongreedy = nongreedy;

  if (showNfa)
  {
    printNfa(td);
  }

  DfaStates dfa(&entryptr, minimize, false, td, currenttoken, &innergcc, disambiguationDisabled);
  deletenfa(nfa);

  if (entryptr.dfa == 0)
  {
    internalerr();
  }

  if (showDfa)
  {
    printDfa(dfa.first());
  }

  NfaState *finalState = createnfa(final, 0);

  DfaState *first = dfa.first();
  if (first->tm.empty() && first->annotationSet.empty())
  {
    finalState->shift = finalState;
    noerrors++;
    if (currentnonterminal)
      fprintf(prn, "--Error-- Exclusion with empty result in nonterminal %s\n", currentnonterminal->name);
    else
      fprintf(prn, "--Error-- Exclusion with empty result in token %s\n", tokenDescriptors.tokenDescription(currenttoken).c_str());
  }
  else
  {
    for (DfaState *d = first; d; d = d->link)
    {
      if (d->tm.empty())
      {
        if (d->annotationSet.empty())
        {
          internalerr();
        }
        d->nfa = finalState;
      }
      else
      {
        d->nfa = createnfa(fork, 0);
        if (! d->annotationSet.empty())
        {
          d->nfa->shift = finalState;
        }
        d->nfa->u.two = 0;
      }
    }

    finalState->shift = entryptr.dfa->nfa;
    t.nfa = entryptr.dfa->nfa;

    for (DfaState *d = dfa.first(); d; d = d->link)
    {
      NfaState *last = d->nfa;

      for (TransitionMap::iterator i = d->tm.begin(); i != d->tm.end(); )
      {
        GrammarCharSet gcs;
        innergcc.declassify(*i->first, gcs);
        const GrammarCharSet *on = outergcc.submit(gcs);

        NfaState *to = i->second.shift->nfa;

        ++i;
        if (i == d->tm.end())
        {
          if(last->shift == 0)
          {
            last->kind = settrans;
            last->u.on = on;
            last->shift = to;
          }
          else
          {
            last->u.two = createnfa(settrans, to);
            last->u.two->u.on = on;
          }
        }
        else
        {
          if(last->shift == 0)
          {
            last->shift = createnfa(settrans, to);
            last->shift->u.on = on;
          }
          else
          {
            last->u.two = createnfa(settrans, to);
            last->u.two->u.on = on;

            last->u.two = createnfa(fork, last->u.two);
            last->u.two->u.two = 0;

            last = last->u.two;
          }
        }
      }
    }
  }

  return finalState;
}

NfaState *LexerGeneratorImpl::charsetnfa(const GrammarCharSet &gcs, GrammarCharClasses &gcc)
{
  NfaState *nfa = createnfa(final, createnfa(settrans, 0));
  nfa->shift->shift = nfa;
  nfa->shift->u.on = gcc.submit(gcs);
  return nfa;
}

NfaState *LexerGeneratorImpl::atomicnfa(Symbol *s, GrammarCharClasses &gcc)
{
  NfaState *nfa;

  /* construct atomic nfa */

#define CHARSETOPTIMIZATION 1
#if CHARSETOPTIMIZATION
  if (! s->effectiveCharSet->empty())
  {
    nfa = charsetnfa(*s->effectiveCharSet, gcc);
  }
  else
#endif
  switch (s->kind)
  {
  case compound:
    nfa = exprnfa(s->u.subrule, gcc);
    break;

  case nonterminal:
    s->u.name->used = true;

    if (s->u.name->ungreedy && noerrors == 0)
    {
      nfa = recomputednfa(s, gcc);
    }
    else if (s->u.name->rules && s->u.name->stack == 0)
    {
      s->u.name->stack = currentnonterminal;
      currentnonterminal = s->u.name;
      nfa = exprnfa(s->u.name->rules, gcc);
      currentnonterminal = s->u.name->stack;
      s->u.name->stack = 0;
    }
    else
    {
      nfa = createnfa(final, 0);
      nfa->shift = nfa;

      if (! s->u.name->complained)
      {
        s->u.name->complained = true;
        noerrors++;
        if (s->u.name->stack)
        {
          fprintf(prn, "--Error-- Nonterminal %s defined recursively\n", s->u.name->name);
        }
        else
        {
          fprintf(prn, "--Error-- Nonterminal %s not defined\n", s->u.name->name);
        }
      }
    }
    break;

  case exclusion:
    {
      GrammarCharSet cs;
      if (charFolder == 0 && tokenDescriptors.getcharset(currenttoken, currentnonterminal, s, cs))
      {
        nfa = createnfa(final, createnfa(settrans, 0));
        nfa->shift->shift = nfa;
        nfa->shift->u.on = gcc.submit(cs);
      }
      else
      {
        nfa = recomputednfa(s, gcc);
      }
    }
    break;

  case charset:
    nfa = charsetnfa(*s->u.specification, gcc);
    break;

  case charstring:
    {
      nfa = createnfa(final, 0);
      nfa->shift = nfa;

      const char *string = s->u.name->name;
      size_t stringSize = strlen(string) - 2;

      Character quote = (Character) (*string++);

      do
      {
        size_t encodedSize;
        Character codepoint = Decoder::decode_utf8_char(string, &encodedSize);

        string += encodedSize;
        stringSize -= encodedSize;

        if (codepoint == quote)
        {
          string++;
          stringSize--;
        }

        nfa->shift = createnfa(settrans, nfa->shift);
        nfa = nfa->shift;
        nfa->u.on = gcc.submit(GrammarCharSet(codepoint));
      }
      while (stringSize > 0);

      nfa = nfa->shift;
    }
    break;

  case dollar:
    {
      nfa = createnfa(final, createnfa(settrans, 0));
      nfa->shift->shift = nfa;
      nfa->shift->u.on = gcc.submit(GrammarCharSet(0));
    }
    break;

  default:
    internalerr();
    break;
  }

  return nfa;
}

void LexerGeneratorImpl::replace(NfaState *oldnfa, NfaState *newnfa, NfaState *nfa)
{
  nfa->tag = currenttag;
  if (nfa->shift->tag != currenttag) replace(oldnfa, newnfa, nfa->shift);
  if (nfa->shift == oldnfa) nfa->shift = newnfa;
  if (nfa->kind == fork)
  {
    if (nfa->u.two->tag != currenttag) replace(oldnfa, newnfa, nfa->u.two);
    if (nfa->u.two == oldnfa) nfa->u.two = newnfa;
  }
}

NfaState *LexerGeneratorImpl::nfalink(NfaState *nfa, NfaState *current)
{
  if (nfa == 0)
    nfa = current;
  else if (current)
  {
    NfaState *oldnfa = current->shift;
    currenttag++;
    replace(oldnfa, nfa, current);
    current->shift = nfa->shift;
    nfa->shift = oldnfa->shift;
    nfa->kind = oldnfa->kind;

    switch (nfa->kind)
    {
    case fork:     nfa->u.two = oldnfa->u.two; break;
    case settrans: nfa->u.on  = oldnfa->u.on;  break;
    case final:                                break;
    }

    if (current != oldnfa) nfa = current;
    oldnfa->shift = freenfa;
    freenfa = oldnfa;
  }
  return nfa;
}

NfaState *LexerGeneratorImpl::factornfa(Symbol *s, ClosureType c, GrammarCharClasses &gcc)
{
  NfaState *nfa = 0;

  switch (c)
  {
  case closure:
    nfa = atomicnfa(s, gcc);
    nfa->kind = fork;
    nfa->u.two = createnfa(final, nfa);
    nfa = nfa->u.two;
    break;

  case positiveclosure:
    nfa = atomicnfa(s, gcc);
    nfa->kind = fork;
    nfa->u.two = createnfa(final, nfa->shift);
    nfa = nfa->u.two;
    break;

  case optional:
    nfa = atomicnfa(s, gcc);
    nfa->shift = createnfa(fork, nfa->shift);
    nfa->shift->u.two = nfa;
    break;

  case quantity:
    {
      if (s->max >= 0)
      {
        for (int i = 0; i < s->min; ++i)
        {
          nfa = nfalink(nfa, atomicnfa(s, gcc));
        }
        for (int i = s->min; i < s->max; ++i)
        {
          nfa = nfalink(nfa, factornfa(s, optional, gcc));
        }
      }
      else if (s->min == 0)
      {
        nfa = factornfa(s, closure, gcc);
      }
      else
      {
        for (int i = 0; i < s->min - 1; ++i)
        {
          nfa = nfalink(nfa, atomicnfa(s, gcc));
        }
        nfa = nfalink(nfa, factornfa(s, positiveclosure, gcc));
      }
    }
    break;

  case none:
    nfa = atomicnfa(s, gcc);
    break;
  }
  return nfa;
}

NfaState *LexerGeneratorImpl::termnfa(Symbol *s, GrammarCharClasses &gcc)
{
  if (s && s->kind == slash)
  {
    s = s->u.lhs;
  }

  NfaState *nfa = 0;
  while (s)
  {
    nfa = nfalink(nfa, factornfa(s, s->operation, gcc));
    s = s->nextsymbol;
  }

  if (nfa == 0)
  {
    nfa = createnfa(final, 0);
    nfa->shift = nfa;
  }

  return nfa;
}

NfaState *LexerGeneratorImpl::exprnfa(Rule *r, GrammarCharClasses &gcc)
{
  NfaState *nfa = 0;

  do
  {
    NfaState *oldnfa = termnfa(r->firstsymbol, gcc);
    if (nfa == 0)
    {
      nfa = oldnfa;
    }
    else if (oldnfa)
    {
      currenttag++;
      replace(oldnfa, nfa, oldnfa);
      nfa->shift = createnfa(fork, nfa->shift);
      nfa->shift->u.two = oldnfa->shift;

      oldnfa->shift = freenfa;
      freenfa = oldnfa;
    }
    r = r->link;
  }
  while (r);

  if (nfa == 0)
  {
    nfa = createnfa(final, 0);
    nfa->shift = nfa;
  }
  return nfa;
}

NfaState *LexerGeneratorImpl::tokennfa(TokenId t, AnnotationType annotationType,
                                       Symbol *lhs, Symbol *rhs,
                                       bool rhsHasVariableLength,
                                       NfaState *nfa, bool &hasUnsupportedLookahead,
                                       GrammarCharClasses &gcc)
{
  if (disambiguationDisabled)
  {
    rhs = 0;
  }

  int min;
  int max;
  LookaheadType lookaheadType;

  if (rhsHasVariableLength)
  {
    getLength(lhs, min, max);
    lookaheadType = FIXEDTOKENLENGTH;
  }
  else if (rhs == 0)
  {
    min = 0;
    max = 0;
    lookaheadType = NOLOOKAHEAD;
  }
  else
  {
    getLength(rhs, min, max);
    lookaheadType = FIXEDLOOKAHEADLENGTH;
  }

  hasUnsupportedLookahead |= min != max;

  NfaState *rulenfa = termnfa(lhs, gcc);

  if (rhs != 0)
  {
    NfaState *context = termnfa(rhs, gcc);
    NfaState *begin = rulenfa->shift;

    rulenfa->kind = fork;
    rulenfa->shift = context->shift;

    rulenfa->u.two = createnfa(final, begin);
    rulenfa->u.two->annotation = Annotation(t, TOKENCOMPLETED, lookaheadType, max);

    context->shift = begin;
    rulenfa = context;
  }
  else if (annotationType == FINAL)
  {
    rulenfa->kind = fork;
    rulenfa->u.two = createnfa(final, rulenfa->shift);
    rulenfa->shift = createnfa(final, rulenfa->shift);
    rulenfa->u.two->annotation = Annotation(t, TOKENCOMPLETED, lookaheadType, max);
    rulenfa = rulenfa->shift;
  }

  rulenfa->annotation = Annotation(t, annotationType, lookaheadType, max);

  if (nfa == 0)
  {
    nfa = rulenfa;
  }
  else
  {
    nfa->shift = createnfa(fork, nfa->shift);
    nfa->shift->u.two = rulenfa->shift;
    rulenfa->shift = nfa->shift;
  }

  return nfa;
}

NfaState *LexerGeneratorImpl::tokennfa(TokenId t, Rule *rules, SymbolTableEntry *trailingcontext, GrammarCharClasses &gcc)
{
  currenttoken = t;

  bool rhsHasVariableLength = false;
  bool lhsHasVariableLength = false;
  bool hasLookaheadOperator = false;
  bool hasUnsupportedLookahead = false;
  int min, max;

  Symbol s;
  Symbol *tc = 0;
  if (trailingcontext)
  {
    tc = &s;
    tc->kind = nonterminal;
    tc->operation = none;
    tc->min = 1;
    tc->max = 1;
    tc->u.name = trailingcontext;
    tc->effectiveCharSet = &gcc.EMPTY;
    tc->nextsymbol = 0;

    getLength(tc, min, max);
    rhsHasVariableLength |= min != max;
  }

  for (Rule *expr = rules; expr; expr = expr->link)
  {
    if (expr->firstsymbol && expr->firstsymbol->kind == slash)
    {
      hasLookaheadOperator = true;

      getLength(expr->firstsymbol->u.rhs, min, max);
      rhsHasVariableLength |= min != max;

      getLength(expr->firstsymbol->u.lhs, min, max);
      lhsHasVariableLength |= min != max;
    }
    else
    {
      getLength(expr->firstsymbol, min, max);
      lhsHasVariableLength |= min != max;
    }

    TokenDescriptor &td = tokenDescriptors.get(t);
    if (td.minlength <  0 || td.minlength > min) td.minlength = min;
    if (td.maxlength >= 0 && td.maxlength < max) td.maxlength = max;
  }

  if (   (lhsHasVariableLength && rhsHasVariableLength)
      || (hasLookaheadOperator && trailingcontext))
  {
    hasUnsupportedLookahead = true;
    trailingcontext = 0;
  }

  NfaState *nfa = 0;

  for (Rule *expr = rules; expr; expr = expr->link)
  {
    Symbol *lhs;
    Symbol *rhs;

    if (expr->firstsymbol == 0 || expr->firstsymbol->kind != slash)
    {
      lhs = expr->firstsymbol;
      rhs = tc;
    }
    else
    {
      lhs = expr->firstsymbol->u.lhs;
      rhs = expr->firstsymbol->u.rhs;
    }

    nfa = tokennfa(t, FINAL, lhs, rhs, rhsHasVariableLength, nfa, hasUnsupportedLookahead, gcc);
  }

  if (! disambiguationDisabled)
  {
    if (hasUnsupportedLookahead || (hasLookaheadOperator && ! tokenDescriptors.getSelfContained()))
    {
      noerrors++;
      fprintf(prn, "--Error-- Token %s has unsupported lookahead operator\n", tokenDescriptors.tokenDescription(t).c_str());
    }
  }

  return nfa->shift;
}

void LexerGeneratorImpl::clearnfano(NfaState *nfa)
{
  nfa->tag = currenttag;
  nfa->nfano = 0;
  if (nfa->shift->tag != currenttag) clearnfano(nfa->shift);
  if (nfa->kind == fork)
  {
    if (nfa->u.two->tag != currenttag) clearnfano(nfa->u.two);
  }
}

void LexerGeneratorImpl::countnfareferences(NfaState *nfa)
{
  nfa->tag = currenttag;
  if (nfa->shift->tag != currenttag) countnfareferences(nfa->shift);
    else ++nfa->shift->nfano;
  if (nfa->kind == fork)
  {
    if (nfa->u.two->tag != currenttag) countnfareferences(nfa->u.two);
      else ++nfa->u.two->nfano;
  }
  ++nfa->nfano;
}

void LexerGeneratorImpl::deleteunreferencednfa(NfaState *nfa)
{
  nfa->tag = currenttag;
  if (nfa->shift->tag != currenttag) deleteunreferencednfa(nfa->shift);
    else if (--nfa->shift->nfano == 0)
  {
    free(nfa->shift);
    --nofnfas;
  }
  if (nfa->kind == fork)
  {
    if (nfa->u.two->tag != currenttag) deleteunreferencednfa(nfa->u.two);
      else if (--nfa->u.two->nfano == 0)
    {
      free(nfa->u.two);
      --nofnfas;
    }
  }
  if (--nfa->nfano == 0)
  {
    free(nfa);
    --nofnfas;
  }
}

void LexerGeneratorImpl::deletenfa(NfaState *&nfa)
{
  if (nfa)
  {
    ++currenttag; clearnfano(nfa);
    ++currenttag; countnfareferences(nfa);
    ++currenttag; deleteunreferencednfa(nfa);
    nfa = 0;
  }
}

void LexerGeneratorImpl::dumpMap(const char *prefix, const char *name, const int *map, size_t mapSize)
{
  outopen(prefix);

  size_t wid = Format::width(mapSize);

  fprintf(so, "int ");
  fprintf(so,  "%s", name);
  fprintf(so, "[%d] =\n", (int) mapSize);

  const size_t lineLimit = 120;
  size_t lineWidth = lineLimit;
  const size_t terminator = 1;

  for (size_t itemCount = 0; itemCount < mapSize; itemCount++)
  {
    int n = map[itemCount];
    char *s = n != (int) 0x80000000
            ? format.toString<char>(n)
            : format.toString<char>(n, 16, 0, 0, "0x");
    size_t l = strlen(s);
    if (lineWidth + 2 + l + terminator <= lineLimit)
    {
      lineWidth += fprintf(so, ", ");
    }
    else
    {
      if (itemCount == 0)
        lineWidth += fprintf(so, "{\n");
      else
        lineWidth += fprintf(so, ",\n");
      lineWidth = fprintf(so, "/* %*d */ ", (int) wid, (int) itemCount);
    }
    lineWidth += fprintf(so, "%s", s);
  }

  fprintf(so,"\n};\n");
  p_outcls();
}

void LexerGeneratorImpl::dumpactions()
{
  int j;
  int w = 0;
  const char *string;
  char delim;

  outopen("sds");
  fprintf(so, "{\n");

  if (nofactions)
  {
    if (nofactions != 1)
    {
      fprintf(so,"   switch (action) {\n");
      w = (int) Format::width(nofactions);
    }

    for (j = 0; j < nofactions; ++j)
    {
      const TokenDescriptor *t = 0;
      for (TokenDescriptors::const_reverse_iterator i = tokenDescriptors.rbegin();
           i != tokenDescriptors.rend();
           ++i)
      {
        t = &tokenDescriptors.get(i->first);
        if (t->lexaction == 0)
          t = 0;
        else if (t->lexaction->code != j)
          t = 0;
        else
          break;
      }

      if (t)
      {
        if (nofactions == 1)
        {
          fprintf(so, "   ");
        }
        else
        {
          fprintf(so,"   case %*d:", w, t->lexaction->code + 1);
        }
        string = t->lexaction->name;
        for (size_t k = strlen(string++); k >= 3; k--)
        {
          delim= *string++;
          if (delim!=';') fprintf(so, "%c", delim); else
          {
            fprintf(so, "%c\n", delim);
            if (nofactions == 1) fprintf(so, "   "); else fprintf(so, "%*c", w+1, ' ');
          }
        }
        fprintf(so, ";\n");
        if (t->lexaction->code + 1 != nofactions)
        {
          fprintf(so, "      %*c break;\n", w, ' ');
        }
      }
    }
    if (nofactions != 1)
    {
      fprintf(so,"   }\n");
    }
  }

  fprintf(so,"}\n");
  p_outcls ();
}

void LexerGeneratorImpl::getTokenNames(CharPtrString &tokenNames)
{
  for (TokenId id = 0; id <= hightoken; ++id)
  {
    tokenNames += strdup(tokenDescriptors.tokenName(id).c_str());
  }
}

void LexerGeneratorImpl::dumpTokenNames()
{
  if (tokenDescriptors.getTokenPrefix().size() == 0)
  {
    tokenDescriptors.setTokenPrefix(CString("SYMBOL_"));
  }

  outopen("tdc");

  for (TokenId id = 0; id <= hightoken; ++id)
  {
    TokenDescriptors::const_iterator i = tokenDescriptors.find(id);
    if (i != tokenDescriptors.end())
    {
      const TokenDescriptor &t(i->second);
      if (t.definition==named)
      {
        fprintf(so, "#define %s", tokenDescriptors.getTokenPrefix().c_str());
        for (const char *cp = t.u.nonterminal->name; *cp; ++cp)
        {
          fprintf (so, "%c", toupper(*cp));
        }
        fprintf (so, " %d\n", id);
      }
    }
  }

  fprintf(so,"#define %s_END %d\n", tokenDescriptors.getTokenPrefix().c_str(), hightoken + 1);

  p_outcls();
}

void LexerGeneratorImpl::dumpconflicts()
{
  for (TokenDescriptors::const_iterator i = tokenDescriptors.begin(); i != tokenDescriptors.end(); ++i)
  {
    TokenId c1(i->first);
    TokenDescriptor &t1(tokenDescriptors.get(c1));
    if (t1.conflicts)
    {
      for (ConflictSet::const_iterator j = t1.conflicts->begin(); j != t1.conflicts->end(); )
      {
        TokenId c2(*j);
        TokenDescriptor &t2(tokenDescriptors.get(c2));
        ++j;

        if (t2.conflicts->find(c1) != t2.conflicts->end())
        {
          const TokenDescriptor *tConflict = t1.conflicts->size() > t2.conflicts->size()
                                     ? &t1
                                     : t2.conflicts->size() > t1.conflicts->size()
                                     ? &t2
                                     : t1.minlength != t1.maxlength && t2.minlength == t2.maxlength
                                     ? &t1
                                     : t2.minlength != t2.maxlength && t1.minlength == t1.maxlength
                                     ? &t2
                                     : t1.definition == named && t2.definition != named
                                     ? &t1
                                     : t2.definition == named && t1.definition != named
                                     ? &t2
                                     : c1 < c2
                                     ? &t1
                                     : &t2;
          if (tConflict == &t1)
          {
            t2.conflicts->erase(c1);
          }
          else
          {
            t1.conflicts->erase(c2);
          }
        }
      }
    }
  }

  for (TokenDescriptors::const_iterator i = tokenDescriptors.begin(); i != tokenDescriptors.end(); ++i)
  {
    TokenId id(i->first);
    const TokenDescriptor &t(tokenDescriptors.get(id));
    if (t.conflicts && ! t.conflicts->empty())
    {
      const char *name = "";

      switch (t.definition)
      {
      case named:
        name = t.u.nonterminal->name;
        break;
      case numbered:
        if (   t.u.rules
            && t.u.rules->link == 0
            && t.u.rules->firstsymbol
            && t.u.rules->firstsymbol->nextsymbol == 0
            && t.u.rules->firstsymbol->kind == charstring)
        {
          name = t.u.rules->firstsymbol->u.name->name;
        }
        break;
      case undefined:
        break;
      }

      noerrors++;
      fprintf(prn, "--Error-- Lexical ambiguities for %s(%d):", name, id);

      char delimiter = ' ';
      for (ConflictSet::const_iterator l = t.conflicts->begin();
           l != t.conflicts->end();
           ++l)
      {
        TokenId c = *l;
        const TokenDescriptor &u(tokenDescriptors.get(c));

        if (u.definition == named)
        {
          name = u.u.nonterminal->name;
        }
        else if (   u.u.rules
                 && u.u.rules->link == 0
                 && u.u.rules->firstsymbol
                 && u.u.rules->firstsymbol->nextsymbol == 0
                 && u.u.rules->firstsymbol->kind == charstring
                 )
        {
          name = u.u.rules->firstsymbol->u.name->name;
        }
        else
        {
          name = "";
        }

        fprintf(prn, "%c%s", delimiter, name);
        delimiter = ' ';
      }

      fprintf(prn, "\n");
    }
  }
}

void LexerGeneratorImpl::getLength(const Rule *r, int &min, int &max)
{
  min = 2147483647;
  max = 0;

  if (r == 0)
  {
    min = 0;
  }
  else for (; r; r = r->link)
  {

    int i, a;
    getLength(r->firstsymbol, i, a);

    if (min > i)
    {
      min = i;
    }

    if (a < 0 || (max >= 0 && max < a))
    {
      max = a;
    }
  }
}

void LexerGeneratorImpl::getLength(const Symbol *s, int &min, int &max)
{
  min = 0;
  max = 0;

  if (s && s->kind == slash)
  {
    s = s->u.lhs;
  }

  for (; s; s = s->nextsymbol)
  {
    int i = 0;
    int a = 0;

    switch (s->kind)
    {
    case nonterminal:
      if (s->u.name->rules && s->u.name->stack == 0)
      {
        s->u.name->stack = currentnonterminal;
        currentnonterminal = s->u.name;
        getLength(s->u.name->rules, i, a);
        currentnonterminal = s->u.name->stack;
        s->u.name->stack = 0;
      }
      else if (! s->u.name->complained)
      {
        s->u.name->complained = true;
        noerrors++;
        if (s->u.name->stack)
        {
          fprintf(prn, "--Error-- Nonterminal %s defined recursively\n", s->u.name->name);
        }
        else
        {
          fprintf(prn, "--Error-- Nonterminal %s not defined\n", s->u.name->name);
        }
      }
      break;

    case compound:
      getLength(s->u.subrule, i, a);
      break;

    case charstring:
      {
        const char *string = s->u.name->name;
        size_t stringSize = strlen (string) - 2;
        Character quote = (Character) *string++;

        while (stringSize > 0)
        {
          size_t encodedSize;
          Character codepoint = Decoder::decode_utf8_char(string, &encodedSize);
          ++i;
          ++a;
          if (quote == codepoint)
          {
            encodedSize = 2;
          }
          stringSize -= encodedSize;
          string += encodedSize;
        }
      }
      break;

    case exclusion:
      getLength(s->u.rhs, i, a); // just go through error checking
      getLength(s->u.lhs, i, a);
      break;

    case charset:
    case dollar:
      i = 1;
      a = 1;
      break;

    case slash:
      internalerr();
      break;
    }

    switch (s->operation)
    {
    case closure:
      a = -1;
      break;

    case positiveclosure:
      min += i;
      a = -1;
      break;

    case none:
      min += i;
      break;

    case optional:
      break;

    case quantity:
      min += i * s->min;
      if (s->max < 0) a = -1; else a *= s->max;
      break;

    default:
      internalerr();
      break;
    }
    if (a < 0)
    {
      max = -1;
    }
    else if (max >= 0)
    {
      max += a;
    }
  }
}

void LexerGeneratorImpl::getTokenStrings(CharPtrString &tokenStrings)
{
  for (TokenId id = 0; id <= hightoken; ++id)
  {
    tokenStrings += strdup(tokenDescriptors.tokenString(id).c_str());
  }
}

void LexerGeneratorImpl::dumpTokenStrings(CharPtrString &tokenStrings)
{
  if (targetLanguage == JAVA)
  {
    if (stringType.empty()) stringType = "protected static final String";
    fprintf (so, "  %s %s[] =\n  {\n", stringType.c_str(), "t1");
  }
  else if (targetLanguage == CPP)
  {
    if (stringType.empty()) stringType = "const wchar_t";
    if (stringPrefix.empty()) stringPrefix = "L";
    fprintf (so, "%s *%s::%s[] =\n{\n", stringType.c_str(), className.c_str(), "t1");
  }
  else
  {
    outopen("tda");
    if (stringType.empty()) stringType = "char *";
    fprintf(so, "%s %s[%d] =\n{\n", stringType.c_str(), tokenTableName.c_str(), hightoken + 1);
  }

  for (size_t i = 0; i < tokenStrings.size(); ++i)
  {
    if (targetLanguage == JAVA) fprintf(so,"  ");
    fprintf(so, "  %s\"", stringPrefix.c_str());
    for (const char *c = tokenStrings[i]; *c; ++c)
    {
      switch (*c)
      {
      case '"':
      case '\\':
        fprintf(so, "\\%c", *c);
        break;
      default:
        fprintf(so, "%c", *c);
        break;
      }
    }
    fprintf(so, "\"%s", stringSuffix.c_str());
    fprintf(so, "%s\n", i + 1 == tokenStrings.size() ? "" : ",");
  }

  fprintf (so, "};\n");

  p_outcls();
}

template <class CHARSET>
void LexerGeneratorImpl::printClasses(const CharClasses<CHARSET> &classes, const GrammarCharClasses *gcc)
{
  fprintf(prn,"          Character Classes:\n");
  fprintf(prn,"          ------------------\n");

  for (typename CharClasses<CHARSET>::const_iterator c = classes.begin();
       classes.end() != c;
       ++c)
  {
    typename CharClasses<CHARSET>::Clazz clazz(*c);

    printCount = printwidth;
    countchars(-10);
    countchars(1);
    countchars(fprintf(prn, "%d", clazz.id) - 1);
    countchars(-25);
    countchars(0);
    countchars(2);
    fprintf(prn, "= ");

    if (gcc)
    {
      GrammarCharSet gcs;
      gcc->declassify(*clazz.characters, gcs);
      printCharSet(&gcs);
    }
    else
    {
      printCharSet(clazz.characters);
    }
    fprintf(prn, ";");
  }
  blanklines(3);
}

void LexerGeneratorImpl::printDfaState(DfaState *dfa)
{
  printCount = printwidth;
  countchars(-10);
  printcode(dfa->dfano);
  countchars(-25);
  countchars(0);
  countchars(6);
  fprintf(prn, ": all ");
  countchars(-37);
  countchars(0);
  printCharSet(&dfa->alltransitions);

  if (! dfa->annotationSet.empty())
  {
    countchars(-27);
    countchars(0);
    countchars(7);
    fprintf(prn, "annotation");
    const char *delimiter = "";
    for (AnnotationSet::const_iterator t = dfa->annotationSet.begin();
         t != dfa->annotationSet.end();
         ++t)
    {
      const Annotation &annotation(*t);
      fprintf(prn, "%s", delimiter);
      delimiter = ",";
      printAnnotation(annotation);
    }
  }

  for (TransitionMap::iterator i = dfa->tm.begin(); i != dfa->tm.end(); ++i)
  {
    countchars(-27);
    countchars(0);
    printcode(i->second.shift->dfano);
    countchars(-37);
    countchars(0);
    printCharSet(i->first);
  }

  for (Transition *t1 = dfa->transitions; t1; t1 = t1->link)
  {
    countchars(-27);
    countchars(0);
    printcode(t1->shift->dfano);
    countchars(-37);
    countchars(0);
    countchars(5);
    fprintf(prn, "%d-%d", t1->low, t1->up);
  }

  fprintf(prn, "\n");
  printCount = 0;
}

void LexerGeneratorImpl::printDfa(DfaState *dfa, const char *when)
{
  fprintf(prn, "          DFA");
  if (when) fprintf(prn, " %s", when);
  fprintf(prn, "\n");
  fprintf(prn, "          ---");
  if (when) for (int i = (int) strlen(when); i >= 0; --i) fprintf(prn, "-");
  fprintf(prn, "\n");

  for (; dfa; dfa = dfa->link)
  {
    printDfaState(dfa);
  }

  fprintf(prn, "\n");
  blanklines(1);
}

void LexerGeneratorImpl::printAnnotation(const Annotation &annotation)
{
  fprintf(prn, " id %d", annotation.getId());
  if (annotation.getId() >= 0)
  {
    switch (annotation.getAnnotationType())
    {
    case FINAL:
      fprintf(prn, " final");
      break;
    case NEGATING:
      fprintf(prn, " negating");
      break;
    case WITHINTOKEN:
      fprintf(prn, " withintoken");
      break;
    case TOKENCOMPLETED:
      fprintf(prn, " tokencompleted");
      break;
    case WITHINLOOKAHEAD:
      fprintf(prn, " withinlookahead");
      break;
    default:
      internalerr();
      break;
    }
    switch (annotation.getLookaheadType())
    {
    case FIXEDLOOKAHEADLENGTH:
      fprintf(prn, " (*/%d)", annotation.getFixedlength());
      break;
    case FIXEDTOKENLENGTH:
      fprintf(prn, " (%d/*)", annotation.getFixedlength());
      break;
    case NOLOOKAHEAD:
      break;
    }
  }
}

void LexerGeneratorImpl::printNfaState(NfaState *nfa)
{
  printCount = printwidth;
  countchars(-10);

  printcode(nfa->nfano);
  countchars(-25);
  countchars(0);
  countchars(2);
  fprintf(prn, ": ");
  countchars(-37);

  fprintf(prn, "%d ", nfa->shift->nfano);
  switch (nfa->kind)
  {
  case fork:
    fprintf(prn, "fork %d", nfa->u.two->nfano);
    break;

  case settrans:
    fprintf(prn, "settrans ");
    printCharSet(nfa->u.on);
    break;

  case final:
    fprintf(prn, "annotation");
    printAnnotation(nfa->annotation);
    break;

  default:
    internalerr();
    break;
  }

  countchars(0);

  // recurse

  nfa->tag = currenttag;
  if (nfa->shift->tag != currenttag) printNfaState(nfa->shift);
  if (nfa->kind == fork)
  {
    if (nfa->u.two->tag != currenttag) printNfaState(nfa->u.two);
  }
}

void LexerGeneratorImpl::printNfa(const TokenDescriptors &td)
{
  for (TokenDescriptors::const_iterator i = td.begin(); i != td.end(); ++i)
  {
    TokenId id(i->first);
    const TokenDescriptor &t(td.get(id));

    if (t.nfa)
    {
      fprintf(prn, "          NFA(%d):\n", id);
      fprintf(prn, "          ------");

      for (size_t j = Format::width(id); j > 0; --j)
      {
        fprintf(prn, "-");
      }

      fprintf(prn, "\n");

      ++currenttag;
      printNfaState(t.nfa);

      fprintf(prn, "\n");
      blanklines(1);
    }
  }
}

void LexerGeneratorImpl::charSetOptimization(Symbol *s, GrammarCharSets &ccs)
{
  if (s && s->effectiveCharSet == 0)
  {
    for (; s; s = s->nextsymbol)
    {
      switch (s->kind)
      {
      case nonterminal:
        if (s->u.name->rules && s->u.name->stack == 0)
        {
          s->u.name->stack = s->u.name;

          charSetOptimization(&s->u.name->rules, &s->effectiveCharSet, ccs);

          s->u.name->stack = 0;
        }
        break;

      case charset:
        s->effectiveCharSet = s->u.specification;
        break;

      case charstring:
        {
          const char *string = s->u.name->name;
          size_t stringSize = strlen (string) - 2;
          Character quote = (Character) *string++;

          if (stringSize > 0)
          {
            size_t encodedSize;
            Character codepoint = Decoder::decode_utf8_char(string, &encodedSize);
            if (quote == codepoint)
            {
              encodedSize = 2;
            }
            if (stringSize == encodedSize)
            {
              s->effectiveCharSet = ccs.insert(GrammarCharSet(codepoint));
            }
          }
        }
        break;

      case compound:
        {
          charSetOptimization(&s->u.subrule, &s->effectiveCharSet, ccs);
        }
        break;

      case exclusion:
        charSetOptimization(s->u.lhs, ccs);
        charSetOptimization(s->u.rhs, ccs);
        if (s->u.lhs && s->u.lhs->nextsymbol == 0  &&
            s->u.rhs && s->u.rhs->nextsymbol == 0  &&
            ! s->u.lhs->effectiveCharSet->empty() &&
            ! s->u.rhs->effectiveCharSet->empty())
        {
          GrammarCharSet gcs(*s->u.lhs->effectiveCharSet);
          gcs -= *s->u.rhs->effectiveCharSet;
          s->effectiveCharSet = ccs.insert(gcs);
        }
        break;

      case slash:
        charSetOptimization(s->u.lhs, ccs);
        charSetOptimization(s->u.rhs, ccs);
        if (s->u.lhs && s->u.lhs->nextsymbol == 0) s->effectiveCharSet = s->u.lhs->effectiveCharSet;
        break;

      case dollar:
        s->effectiveCharSet = ccs.insert(GrammarCharSet(0));
        break;

      default:
        internalerr();
        break;
      }

      if (s->effectiveCharSet == 0)
      {
        s->effectiveCharSet = &ccs.EMPTY;
      }
    }
  }
}

void LexerGeneratorImpl::charSetOptimization(Rule **ruleList, const GrammarCharSet **ecs, GrammarCharSets &ccs)
{
  Rule *separateRules = 0;
  Rule *combinedRules = 0;

  Rule *next = 0;
  Rule *r;

  for (r = *ruleList; r; r = next)
  {
    next = r->link;
    r->link = r;

    charSetOptimization(r->firstsymbol, ccs);

    if (r->firstsymbol && r->firstsymbol->nextsymbol == 0 && ! r->firstsymbol->effectiveCharSet->empty())
    {
      r->effectiveCharSet = r->firstsymbol->effectiveCharSet;
    }

    if (r->effectiveCharSet && ! r->effectiveCharSet->empty() && r->firstsymbol->kind != slash)
    {
      if (combinedRules)
      {
        r->link = combinedRules->link;
        combinedRules->link = r;
      }
      combinedRules = r;
    }
    else
    {
      if (separateRules)
      {
        r->link = separateRules->link;
        separateRules->link = r;
      }
      separateRules = r;
    }
  }

  if (combinedRules)
  {
    if (combinedRules != combinedRules->link)
    {
      Symbol *s = new Symbol();
      s->kind = compound;
      s->operation = none;
      s->min = 1;
      s->max = 1;
      s->nextsymbol = 0;
      s->u.subrule = Rule::close(combinedRules);

      Rule *newRule = new Rule();
      newRule->firstsymbol = s;
      newRule->rule = combinedRules->rule;
      newRule->main = combinedRules->main;
      newRule->link = newRule;

      GrammarCharSet gcs;
      for (r = s->u.subrule; r; r = r->link)
      {
        gcs += *r->effectiveCharSet;
        r->rule = subrule;
        r->main = newRule;
      }

      s->effectiveCharSet = ccs.insert(gcs);
      newRule->effectiveCharSet = s->effectiveCharSet;
      combinedRules = newRule;
    }

    if (separateRules)
    {
      combinedRules->link = separateRules->link;
      separateRules->link = combinedRules;
    }
    separateRules = combinedRules;
  }

  *ruleList = Rule::close(separateRules);
}

void LexerGeneratorImpl::charSetOptimization(GrammarCharSets &ccs)
{
  for (TokenDescriptors::const_iterator i = tokenDescriptors.begin(); i != tokenDescriptors.end(); ++i)
  {
    TokenDescriptor &t(tokenDescriptors.get(i->first));
    Rule **r;
    const GrammarCharSet **cc;
    SymbolTableEntry *trailingContext;

    switch (t.definition)
    {
    case named:
      currentnonterminal = t.u.nonterminal;
      currentnonterminal->stack = currentnonterminal;
      r = &currentnonterminal->rules;
      cc = &currentnonterminal->effectiveCharSet;
      trailingContext = currentnonterminal->trailingcontext;
      break;
    case numbered:
      currentnonterminal = 0;
      r = &t.u.rules;
      cc = &t.u.effectiveCharSet;
      trailingContext = t.u.trailingcontext;
      break;
    default:
      currentnonterminal = 0;
      r = 0;
      cc = 0;
      trailingContext = 0;
      break;
    }

    if (r)
    {
      charSetOptimization(r, cc, ccs);
    }

    if (trailingContext)
    {
      charSetOptimization(&trailingContext->rules, cc, ccs);
    }

    if (currentnonterminal)
    {
      currentnonterminal->stack = 0;
    }
  }
  currentnonterminal = 0;
}

void LexerGeneratorImpl::nfaconstruction(GrammarCharClasses &gcc)
{
  /* compute initial state of DFA by entering all non-epsilon */
  /* entry states of all token NFAs into the initial NFA set  */

  nofnfas = 0;
  freenfa = 0;
  initialtag = -maxint - 1;
  currenttag = initialtag;

  for (TokenDescriptors::const_iterator i = tokenDescriptors.begin(); i != tokenDescriptors.end(); ++i)
  {
    TokenId id(i->first);
    TokenDescriptor &t(tokenDescriptors.get(id));
    if (t.definition == undefined)
    {
      t.nfa = 0;
    }
    else
    {
      Rule *r;
      SymbolTableEntry *trailingcontext;

      if (t.definition != named)
      {
        r = t.u.rules;
        trailingcontext = t.u.trailingcontext;
      }
      else
      {
        r = t.u.nonterminal->rules;
        trailingcontext = t.u.nonterminal->trailingcontext;
        t.u.nonterminal->used = true;
      }

      if (r == 0)
      {
        t.nfa = 0;
      }
      else
      {
        t.nfa = tokennfa(id, r, trailingcontext, gcc);
      }
    }
  }

  // get rid of excess nfa nodes

  while (freenfa)
  {
    NfaState *newnfa = freenfa;
    freenfa = freenfa->shift;
    free(newnfa);
  }

  // set "used" for named tokens

  entrylist *entryptr = entries;
  do
  {
    entryptr = entryptr->link;
    List *obj = entryptr->elist;
    if (obj)
    {
      do
      {
        obj= obj->link;

        if (obj->u.eptr->named)
        {
          obj->u.eptr->tokencode = obj->u.eptr->ntptr->code;
          if (obj->u.eptr->tokencode >= 0)
          {
            tokenDescriptors.get(obj->u.eptr->tokencode).used = true;
          }
        }
      }
      while (obj != entryptr->elist);
    }
  }
  while (entryptr != entries);

  // calculate character classes based on grammar

  gcc.arrange(false);

  if (grammar)
  {
    printClasses(gcc);
  }
}

void LexerGeneratorImpl::statistics(DfaStates &dfaStates)
{
  int nStates = 0;
  int nStatesR0 = 0;
  int nStatesT0 = 0;

  int transitions = 0;
  int transitionsS = 0;
  int transitionsR = 0;

  for (DfaState *dfa = dfaStates.first(); dfa; dfa = dfa->link)
  {
    ++nStates;
    if (dfa->annotationSet.empty()) ++nStatesR0;
    if (dfa->tm.empty()) ++nStatesT0;

    for (TransitionMap::iterator i = dfa->tm.begin(); i != dfa->tm.end(); ++i)
    {
      ++transitions;

      DfaState *shift = i->second.shift;
      if (shift == dfa) ++transitionsS;
      if (! shift->annotationSet.empty()) ++transitionsR;
    }
  }

  fprintf(stderr, "total number of NFA states: %d\n", nofnfas);
  fprintf(stderr, "total number of DFA states: %d\n", nStates);
  fprintf(stderr, "number of non-final DFA states: %d\n", nStatesR0);
  fprintf(stderr, "number of DFA states without transitions: %d\n", nStatesT0);
  fprintf(stderr, "total number of transitions: %d\n", transitions);
  fprintf(stderr, "number of transitions to same state: %d\n", transitionsS);
  fprintf(stderr, "number of transitions to final states: %d\n", transitionsR);
}

void LexerGeneratorImpl::dfaConstruction(const GrammarCharClasses &gcc, DfaStates &dfaStates)
{
  int *entryTable = 0;
  int stateCodeBits = 0;
  int tokencodeBits = 0;
  size_t stateAddressBits = 0;
  size_t transitionStateCount = 0;

  LegacyDfa *legacyDfa = 0;

  IntString highRangeMap;

  CharPtrString tokenStrings;
  CharPtrString tokenNames;

  const TiledMap *transitionTable = 0;
  TiledMap2D *transitionMap = 0;

  int *uncompressedExpectedTokenTable = 0;
  TiledMap *expectedTokenTable = 0;

  int *uncompressedMap = 0;
  size_t uncompressedMapSize = 0;
  TiledMap *charMap = 0;

  CharClasses<ConstructionCharSet> charClasses;

  bool hasfixedtokenlength = false;
  int maxcontextlength = 0;

  const size_t simplifiedCodeMap = 128;

  size_t expectedTokenTableSize = 0;

  if (nolexer)
  {
    BitSet tokenSet(hightoken);
    size_t expectedSetSize = tokenSet.getBaseSize();
    expectedTokenTableSize = expectedSetSize * entrycount;

    transitionStateCount = entrycount; // TODO: use different variable for transporting expected token table dimensions

    if (verbose)
    {
      printf("expectedSetSize: %d\n", (int) expectedSetSize);
      printf("entryCount: %d\n", (int) entrycount);
      printf("expectedTokenTableSize: %d\n", (int) expectedTokenTableSize);
    }

    uncompressedExpectedTokenTable = new int[expectedTokenTableSize];
    memset(uncompressedExpectedTokenTable, 0, expectedTokenTableSize * sizeof(int));

    entrylist *entryptr = entries;
    size_t entry = 0;
    do
    {
      entryptr = entryptr->link;
      tokenSet.clear();

      List *obj = entryptr->elist;
      if (obj)
      {
        do
        {
          obj= obj->link;

          if (obj->u.eptr->tokencode >= 0)
          {
            tokenSet += CharacterRange(obj->u.eptr->tokencode);
          }
        }
        while (obj != entryptr->elist);
      }

      const int *data = (const int *) tokenSet.getData();
      for (size_t i = 0; i < expectedSetSize; ++i)
      {
        uncompressedExpectedTokenTable[(i * entrycount) + entry] = data[i];
      }

      ++entry;
    }
    while (entryptr != entries);
  }
  else
  {
    if (ntlist)
    {
      List *obj = ntlist;
      do
      {
        obj= obj->link;
        if (obj->u.ntptr->istoken && obj->u.ntptr->code < 0)
        {
          noerrors++;
          fprintf(prn, "--Error-- No token code defined for %s\n", obj->u.ntptr->name);
        }

        if (obj->u.ntptr->recursive)
        {
          noerrors++;
          fprintf(prn, "--Error-- Nonterminal %s defined recursively\n", obj->u.ntptr->name);
        }

        if (obj->u.ntptr->exclusionError)
        {
          noerrors++;
          fprintf(prn, "--Error-- Exclusion with empty result in nonterminal %s\n", obj->u.ntptr->name);
        }

        if (! obj->u.ntptr->used)
        {
          fprintf(prn, "-Warning- Nonterminal %s not used\n", obj->u.ntptr->name);
        }
      }
      while (obj != ntlist);
    }

    for (TokenDescriptors::const_iterator i = tokenDescriptors.begin(); i != tokenDescriptors.end(); ++i)
    {
      if (i->second.exclusionError)
      {
        fprintf(prn, "--Error-- Exclusion with empty result in token %s\n",
            tokenDescriptors.tokenDescription(currenttoken).c_str());
      }
    }

    if (noerrors)
    {
      return;
    }

    if (dfaStates.first())
    {
      if (verbose)
      {
        statistics(dfaStates);
      }

      if (! classify)
      {
        uncompressedMapSize = 0;
      }
      else
      {
        // calculate character classes based on minimal automaton

        for (DfaState *dfa = dfaStates.first(); dfa; dfa = dfa->link)
        {
          for (TransitionMap::iterator i = dfa->tm.begin(); i != dfa->tm.end(); ++i)
          {
            charClasses.submit(*i->first);
          }
        }

        charClasses.arrange(true);

        if (grammar)
        {
          printClasses(charClasses, &gcc);
        }

        const size_t uncompressedMapLimit = 0xd800; // do not push beyond 0xd800 without adapting UTF-16 decoder code generation

        uncompressedMapSize = tokenDescriptors.getSelfContained()
                            ? uncompressedMapLimit
                            : 0x10000;

        uncompressedMap = new int[uncompressedMapSize];
        int defaultValue = charClasses.nonCharacterId();
        for (size_t i = 0; i < uncompressedMapSize; ++i)
        {
          uncompressedMap[i] = defaultValue;
        }

        Classifier highRanges;

        for (CharClasses<ConstructionCharSet>::const_iterator c = charClasses.begin();
             charClasses.end() != c;
             ++c)
        {
          const CharClasses<ConstructionCharSet>::Clazz &clazz(*c);
          GrammarCharSet gcs;
          gcc.declassify(*clazz.characters, gcs);

          for (GrammarCharSet::RangeIterator i = gcs.rangeBegin();
               i != gcs.rangeEnd();
               ++i)
          {
            CharacterRange cr(*i);
            for (Character c = cr.getLow(); c <= cr.getHigh(); ++c)
            {
              if (c >= (int) uncompressedMapSize)
              {
                highRanges.insert(Classifier::value_type(CharacterRange(c, cr.getHigh()), clazz.id));
                break;
              }
              uncompressedMap[c] = clazz.id;
            }
          }
        }

        for (Classifier::const_iterator i = highRanges.begin(); i != highRanges.end(); ++i)
        {
          CharacterRange cr(i->first);
          highRangeMap.push_back(cr.getLow());
        }
        for (Classifier::const_iterator i = highRanges.begin(); i != highRanges.end(); ++i)
        {
          CharacterRange cr(i->first);
          highRangeMap.push_back(cr.getHigh());
        }
        for (Classifier::const_iterator i = highRanges.begin(); i != highRanges.end(); ++i)
        {
          CharacterRange cr(i->first);
          if (cr.getHigh() > 0)
          {
            highRangeMap.push_back(i->second);
          }
        }

  /*
        const int *highRangeData = highRangeMap.data();
        for (size_t i = 0; i < highRangeMap.size(); ++i)
          switch (i % 3)
          {
          case 0: fprintf(stderr, "---- highRange(%d", highRangeData[i]); break;
          case 1: fprintf(stderr, ", %d", highRangeData[i]); break;
          case 2: fprintf(stderr, ") => %d\n", highRangeData[i]); break;
          default: internalerr();
        }
  */


  #if 0
        int test0[] = {33, 33, 35, 35, // 37, 37, 39, 39,
  //                     33, 33, 35, 35, 37, 37, 39, 39,
  //                     33, 33, 35, 35, 37, 37, 39, 39,
                       33, 33, 35, 35  // , 37, 37, 39, 39
                       };
        int size0 = sizeof test0 / sizeof *test0;
        TiledMap *cm0 = new TiledMap(test0, size0, 2, TiledMap::NONE);
        printf("uncompressedMapSize %d, compressedMapSize %d, depth %d\n",
               size0, cm0->size(), cm0->getDepth());

        printf("\n\ntest 1\n\n");

        int test[] = {1,1,1,1,2,2,2,2,3,3,3,3,4,4,4,4,
                      1,1,1,1,2,2,2,2,3,3,3,3,4,4,4,4,
                      1,1,1,1,2,2,2,2,3,3,3,3,4,4,4,4,
                      1,1,1,1,2,2,2,2,3,3,3,3,4,4,4,4
                     };
        int size = sizeof test / sizeof *test;
        TiledMap *cm1 = new TiledMap(test, size, 2, TiledMap::NONE);
        printf("uncompressedMapSize %d, compressedMapSize %d, depth %d\n",
               size, cm1->size(), cm1->getDepth());
        exit(0);
  #endif

  #if 0
        TiledMap *cm = new TiledMap(uncompressedMap, uncompressedMapSize, 3, TiledMap::NONE);
        printf("uncompressedMapSize %d, compressedMapSize %d, depth %d, overlap %d, compressed to %.1f %%\n",
            uncompressedMapSize, cm->size(), cm->getDepth(), cm->getOverlap(),
               cm->size() * 100e0 / uncompressedMapSize);
        cm = new TiledMap(uncompressedMap, uncompressedMapSize, 2, TiledMap::NONE);
        printf("uncompressedMapSize %d, compressedMapSize %d, depth %d, overlap %d, compressed to %.1f %%\n",
            uncompressedMapSize, cm->size(), cm->getDepth(), cm->getOverlap(),
               cm->size() * 100e0 / uncompressedMapSize);
        cm = new TiledMap(uncompressedMap, uncompressedMapSize, 1, TiledMap::NONE);
        printf("uncompressedMapSize %d, compressedMapSize %d, depth %d, overlap %d, compressed to %.1f %%\n",
            uncompressedMapSize, cm->size(), cm->getDepth(), cm->getOverlap(),
               cm->size() * 100e0 / uncompressedMapSize);
        cm = new TiledMap(&(*cm)[0], cm->size(), 1, TiledMap::NONE);
        printf("uncompressedMapSize %d, compressedMapSize %d, depth %d, overlap %d, compressed to %.1f %%\n",
            uncompressedMapSize, cm->size(), cm->getDepth(), cm->getOverlap(),
               cm->size() * 100e0 / uncompressedMapSize);
  #endif

        charMap = new TiledMap(uncompressedMap,
                                    uncompressedMapSize,
                                    tokenDescriptors.getSelfContained() ? 2 : 1,
                                    tokenDescriptors.getSelfContained() ? false : true);
        if (verbose)
        {
          printf("character map: uncompressedSize %d, compressedSize %d, depth %d, overlap %d, compressed to %.1f %%\n",
              (int) uncompressedMapSize, (int) charMap->size(), (int) charMap->getDepth(), (int) charMap->getOverlap(),
              charMap->size() * 100e0 / uncompressedMapSize);
        }

        /* translate from character based transitions to class based transitions */

        for (DfaState *dfa = dfaStates.first(); dfa; dfa = dfa->link)
        {
          dfa->alltransitions.clear();

          TransitionMap tm(dfa->tm);
          dfa->tm.clear();
          for (TransitionMap::iterator i = tm.begin(); i != tm.end(); ++i)
          {
            const ConstructionCharSet *classified = charClasses.classify(i->first);
            dfa->tm.insert(TransitionMap::value_type(classified, i->second));
            dfa->alltransitions += *classified;
          }
        }

        transitionStateCount = DfaByTransitionSet::process(dfaStates);

        if (verbose)
        {
          printf("number of distinct transition sets: %d\n", (int) transitionStateCount);
        }
      }

      /* handle abbreviations */

      if (abbreviations)
      {

        internalerr();

//      installabbreviations(dfaStates);
      }

      if (! tokenDescriptors.getSelfContained())
      {
        legacyDfa = new LegacyDfa(*this, dfaStates, gcc);
      }
      else
      {
        //   input codes: 0 .. charClasses.size()
        //   dfa states: 0 .. dfaStates::nofdfas

        size_t distinctInputCount = charClasses.maxId() + 1;
        int inputAddressBits = Math::log2((int) distinctInputCount - 1) + 1;

        stateAddressBits = transitionStateCount == 0 ? 0 : Math::log2((int) transitionStateCount - 1) + 1;

        stateCodeBits = Math::log2((int) transitionStateCount) + 1;
        tokencodeBits = Math::log2(hightoken + 1) + 1;

        if (verbose)
        {
          printf("input addressing: 0..%d (%d bits)\n", (int) distinctInputCount - 1, inputAddressBits);
          printf("state addressing: 0..%d (%d bits)\n", (int) transitionStateCount - 1, (int) stateAddressBits);
          printf("state codes: 0..%d (%d bits)\n", (int) transitionStateCount, stateCodeBits);
          printf("token codes: 0..%d (%d bits)\n", hightoken + 1, tokencodeBits);
        }

        // recalculate maxcontextlength and hasfixedtokenlength
        // for code generation purposes

        hasfixedtokenlength = false;
        for (DfaState *dfa = dfaStates.first(); dfa; dfa = dfa->link)
        {
          switch (dfa->annotationSet.size())
          {
          case 1:
            {
              const Annotation &r(*dfa->annotationSet.begin());
              maxcontextlength = Math::max(maxcontextlength, r.getFixedlength());
              hasfixedtokenlength |= r.getLookaheadType() == FIXEDTOKENLENGTH;
            }
            break;

          case 0:
            break;

          default:
            fprintf(stderr, "\ninvalid annotation set of size %d:\n", (int) dfa->annotationSet.size());
            for (AnnotationSet::const_iterator i = dfa->annotationSet.begin();
                 i != dfa->annotationSet.end();
                 ++i)
            {
              fprintf(stdout, "  token %s ", tokenDescriptors.tokenDescription(i->getId()).c_str());
              printAnnotation(*i);
              fprintf(stdout, "\n");
            }
            internalerr();
            break;
          }
        }

        if (verbose)
        {
          printf("hasfixedtokenlength: %d\n", hasfixedtokenlength);
        }

        int lookaheadbits = hasfixedtokenlength
                          ? tokencodeBits + 1
                          : tokencodeBits;

        for (DfaState *dfa = dfaStates.first(); dfa; dfa = dfa->link)
        {
          size_t combinedTransitionCode = dfa->transitionSetCode;
          if (! dfa->annotationSet.empty())
          {
            const Annotation &r(*dfa->annotationSet.begin());
            combinedTransitionCode += (  r.getId() + 1
                                       + ((r.getLookaheadType() == FIXEDTOKENLENGTH ? 1 : 0) << tokencodeBits)
                                       + (r.getFixedlength() << lookaheadbits)
                                      )
                                   << stateCodeBits;

//          printf("recognition %d, contextsize %d, code %d, transitionSet %d\n", combinedTransitionCode,
//                 r.fixedlength, r.id, dfa->transitionSetCode);
          }
          dfa->combinedTransitionCode = combinedTransitionCode;
        }

//      printf("there are %d entries\n", entrycount);

        entryTable = new int[entrycount];

        entrylist *entryptr = entries;
        size_t entry = 0;
        do
        {
          entryptr = entryptr->link;
          entryTable[entry++] = entryptr->dfa
                              ? (int) entryptr->dfa->combinedTransitionCode
                              : 0;
        }
        while (entryptr != entries);

        int transitionMapCompression = 1;
        int transitionMapAlignment = 0;

        if (smaller)
        {
          transitionMapCompression = 2;
          transitionMapAlignment = 1;
        }

        transitionMap = new TiledMap2D(transitionMapCompression, transitionMapAlignment);
        transitionMap->setMaxIndex(transitionStateCount - 1, distinctInputCount - 1);

//      transitionMap->setXY(Math::powerof(2, stateAddressBits) - 1, Math::powerof(2, inputAddressBits) - 1);
//      printf("setXY(%d, %d)\n", transitionStateCount - 1, distinctInputCount - 1);

        for (DfaState *dfa = dfaStates.first(); dfa; dfa = dfa->link)
        {
          size_t sourceState = dfa->transitionSetCode;
          if (sourceState)
          {
            for (TransitionMap::iterator i(dfa->tm.begin()); i != dfa->tm.end(); ++i)
            {
              DfaState *targetDfa = i->second.shift;
              const ConstructionCharSet &ccs(*i->first);
              for (ConstructionCharSet::CharIterator j(ccs.charBegin());
                   j != ccs.charEnd();
                   ++j)
              {
                Character sourceInput = *j;
                transitionMap->set(sourceState - 1, sourceInput, (int) targetDfa->combinedTransitionCode);
              }
            }
          }
        }

        transitionTable = transitionMap->getMap();

//      printf("transitionTableSize %d, %d * %d = %d\n", transitionMap->getRows() * transitionMap->getCols(), transitionMap->getRows(), transitionMap->getCols(), transitionMap->getRows() * transitionMap->getCols());

        if (verbose)
        {
          printf("transition table: uncompressedMapSize %d, compressedMapSize %d, depth %d, overlap %d, compressed to %.1f %%\n",
                 transitionMap->getMaxY() * transitionMap->getMaxX(),
                 (int) transitionTable->size(), (int) transitionTable->getDepth(), (int) transitionTable->getOverlap(),
                 transitionTable->size() * 100e0 / (transitionMap->getMaxY() * transitionMap->getMaxX()));
        }

        size_t expectedSetSize = dfaStates.first()->expectedTokenSet->getBaseSize();
        size_t roundedExpectedSetSize = expectedSetSize;

        size_t roundedtransitionStateCount = transitionStateCount;

        expectedTokenTableSize = roundedExpectedSetSize * roundedtransitionStateCount;

        if (verbose)
        {
          printf("expectedSetSize: %d\n", (int) expectedSetSize);
          printf("roundedExpectedSetSize: %d\n", (int) roundedExpectedSetSize);
          printf("transitionStateCount: %d\n", (int) transitionStateCount);
          printf("roundedtransitionStateCount: %d\n", (int) roundedtransitionStateCount);
          printf("expectedTokenTableSize: %d\n", (int) expectedTokenTableSize);
        }

        uncompressedExpectedTokenTable = new int[expectedTokenTableSize];
        memset(uncompressedExpectedTokenTable, 0, expectedTokenTableSize * sizeof(int));

        for (DfaState *dfa = dfaStates.first(); dfa; dfa = dfa->link)
        {
          size_t sourceState = dfa->transitionSetCode;
          if (sourceState)
          {
            const int *data = (const int *) dfa->expectedTokenSet->getData();
            for (size_t i = 0; i < expectedSetSize; ++i)
            {
              uncompressedExpectedTokenTable[(i * roundedtransitionStateCount) + sourceState - 1] = data[i];
  //          uncompressedExpectedTokenTable[i + roundedExpectedSetSize * (sourceState - 1)] = data[i];
            }
  //        size_t offset = (sourceState - 1) * roundedExpectedSetSize;
  //        memcpy(uncompressedExpectedTokenTable + offset,
  //               dfa->expectedTokenSet->getData(),
  //               expectedSetSize * sizeof(int));

          }
        }
      }
    }

    for (TokenDescriptors::const_iterator i = tokenDescriptors.begin(); i != tokenDescriptors.end(); ++i)
    {
      TokenId id(i->first);
      const TokenDescriptor &t(tokenDescriptors.get(id));
      if (t.nfa && ! t.used)
      {
        fprintf(prn, "-Warning- Token ");
//      if (t.definition == named) fprintf(prn, "%s", t.u.nonterminal->name);
        fprintf(prn, "%s not used\n", tokenDescriptors.tokenDescription(id).c_str());
      }
      else if (id > 1 && t.nfa == 0 && (t.used || (t.definition != undefined)))
      {
        fprintf(prn, "-Warning- Token ");
        if (t.definition == named) fprintf(prn, "%s", t.u.nonterminal->name);
        fprintf(prn, "( not defined\n");
      }
      else if (t.minlength == 0 && t.maxlength != 0 && ! quiet)
      {
        fprintf(prn, "-Warning- Token ");
//      if (t.definition == named) fprintf(prn, "%s", t.u.nonterminal->name);
        fprintf(prn, "%s matches zero length input\n", tokenDescriptors.tokenDescription(id).c_str());
      }
    }

    if (dfaStates.first())
    {
      if (showDfa)
      {
        printDfa(dfaStates.first());
      }

      /* now dump results */

      if (! ambiguities)
      {
        dumpconflicts();
      }
    }
  }

  if (dfaStates.first() || nolexer)
  {
    if (noerrors == 0)
    {
      expectedTokenTable = new TiledMap(uncompressedExpectedTokenTable,
                                             expectedTokenTableSize,
                                             3,
                                             false);
      if (verbose)
      {
        printf("expected token table: uncompressedSize %d, compressedSize %d, depth %d, overlap %d, compressed to %.1f %%\n",
            (int) expectedTokenTableSize, (int) expectedTokenTable->size(), (int) expectedTokenTable->getDepth(), (int) expectedTokenTable->getOverlap(),
            expectedTokenTable->size() * 100e0 / expectedTokenTableSize);
      }

      size_t scannerSize = (legacyDfa == 0 ? 0 : legacyDfa->size())
                         + (charMap == 0 ? 0 : charMap->size())
                         + (! tokenDescriptors.getSelfContained() ? 0 : highRangeMap.size() + (uncompressedMapSize < simplifiedCodeMap ? uncompressedMapSize : simplifiedCodeMap))
                         + (transitionTable == 0 ? 0 : entrycount + transitionTable->size())
                         + (expectedTokenTable == 0 ? 0 : expectedTokenTable->size());
      if (! embedded)
      {
        blanklines(1);
        fprintf(prn,"          Scanner size: %d\n", (int) scannerSize);
      }

      getTokenStrings(tokenStrings);
      getTokenNames(tokenNames);

      if (targetLanguage == REX)
      {
        instanceCode = wcsdup(L"");
        staticCode = wcsdup(L"");
      }
      else if (tokenDescriptors.getSelfContained())
      {
        CodeGenerator *cg = CodeGenerator::newInstance(targetLanguage, so);

        cg->bind(CGVariable("dispatchlanguage", targetLanguage));
        cg->bind(CGVariable("classname", className.c_str()));
        cg->bind(CGVariable("append", append));
        cg->bind(CGVariable("embedded", embedded));
        if (! embedded)
        {
          cg->bind(CGVariable("useGlr", false));
        }
        cg->bind(CGVariable("package", packageName.c_str()));
        cg->bind(CGVariable("selfTest", selfTest));
        cg->bind(CGVariable("trace", trace));
        cg->bind(CGVariable("tree", tree));
        cg->bind(CGVariable("nolexer", nolexer));
        cg->bind(CGVariable("entrycount", (int) entrycount));
        cg->bind(CGVariable("transitionStateCount", (int) transitionStateCount));
        cg->bind(CGVariable("maxcontextlength", maxcontextlength));
        cg->bind(CGVariable("hasfixedtokenlength", hasfixedtokenlength));

        cg->bind(CGVariable("stringType", stringType.c_str()));
        cg->bind(CGVariable("stringPrefix", stringPrefix.c_str()));
        cg->bind(CGVariable("stringSuffix", stringSuffix.c_str()));

        cg->bind(CGVariable("simplifiedCodeMap", (int) simplifiedCodeMap));
        cg->bind(CGVariable("uncompressedMapSize", (int) uncompressedMapSize));
        cg->bind(CGVariable("stateCodeBits", stateCodeBits));
        cg->bind(CGVariable("tokencodeBits", tokencodeBits));
        cg->bind(CGVariable("a1cols", transitionMap == 0 ? 0 : transitionMap->getMaxX()));

        cg->bind(CGVariable("m0", uncompressedMap,
                                 uncompressedMapSize < simplifiedCodeMap
                               ? uncompressedMapSize
                               : simplifiedCodeMap, "MAP0", "The codepoint to charclass mapping for 7 bit codepoints."));
        cg->bind(CGVariable("m1", charMap == 0 ? 0 : charMap->getRepresentation(),
                                 charMap == 0 ? 0 : charMap->size(), "MAP1", "The codepoint to charclass mapping for codepoints below the surrogate block."));
        cg->bind(CGVariable("m2", highRangeMap.data(),
                                 highRangeMap.size(), "MAP2", "The codepoint to charclass mapping for codepoints above the surrogate block."));
        cg->bind(CGVariable("a0", entryTable,
                                 entrycount, "INITIAL", "The token-set-id to DFA-initial-state mapping."));
        cg->bind(CGVariable("a1", transitionTable == 0 ? 0 : transitionTable->getRepresentation(),
                                 transitionTable == 0 ? 0 : transitionTable->size(), "TRANSITION", "The DFA transition table."));
        if (targetLanguage == CSHARP)
        {
          cg->bind(CGVariable("t0", (const unsigned int *) (expectedTokenTable == 0 ? 0 : expectedTokenTable->getRepresentation()),
                                   expectedTokenTable == 0 ? 0 : expectedTokenTable->size(), "EXPECTED", "The DFA-state to expected-token-set mapping."));
        }
        else
        {
          cg->bind(CGVariable("t0", expectedTokenTable == 0 ? 0 : expectedTokenTable->getRepresentation(),
                                   expectedTokenTable == 0 ? 0 : expectedTokenTable->size(), "EXPECTED", "The DFA-state to expected-token-set mapping."));
        }
        cg->bind(CGVariable("t1", tokenStrings.data(),
                                 tokenStrings.size(), "TOKEN", "The token-string table."));
        cg->bind(CGVariable("token", tokenNames.data(),
                                    tokenNames.size(), 0, 0));
        cg->bind(CGVariable("m1bits", charMap == 0 ? 0 : charMap->getBits(),
                                     charMap == 0 ? 0 : charMap->getDepth() + 1, 0, 0));
        cg->bind(CGVariable("a1bits", transitionTable == 0 ? 0 : transitionTable->getBits(),
                                     transitionTable == 0 ? 0 : transitionTable->getDepth() + 1, 0, 0));
        cg->bind(CGVariable("t0bits", expectedTokenTable == 0 ? 0 : expectedTokenTable->getBits(),
                                     expectedTokenTable == 0 ? 0 : expectedTokenTable->getDepth() + 1, 0, 0));

        for (VarsInInsertionOrder::const_iterator i = extraVars.begin(); i != extraVars.end(); ++i)
        {
          cg->bind(*i);
        }

        cg->generateInstanceCode();
        if (embedded)
        {
          instanceCode = wcsdup(cg->getOutput());
          cg->clearOutput();
          cg->generateStaticCode();

          staticCode = wcsdup(cg->getOutput());
        }
        else
        {
          cg->generateStaticCode();

          outopen(outputFile.c_str());
          fwrite(cg->getEncodedOutput(), 1, strlen(cg->getEncodedOutput()), so);
          p_outcls();
        }

        delete cg;
      }
      else
      {
        dumpMap("sda", tableName.c_str(), legacyDfa->data(), legacyDfa->size());

        if (classify)
        {
          dumpMap("cda",
                  "charclass",
                  charMap->getRepresentation(),
                  charMap->size());
        }

        if (nofactions)
        {
          dumpactions();
        }

        dumpTokenStrings(tokenStrings);

        if (symbols)
        {
          dumpTokenNames();
        }
      }
    }
  }

  // cleanup

  delete legacyDfa;
  legacyDfa = 0;

  for (size_t i = 0; i < tokenStrings.size(); ++i) {delete tokenStrings[i];}
  tokenStrings.clear();

  for (size_t i = 0; i < tokenNames.size(); ++i) {delete tokenNames[i];}
  tokenNames.clear();

  delete charMap;
  charMap = 0;

  delete transitionMap;
  transitionMap = 0;
  transitionTable = 0;

  delete expectedTokenTable;
  expectedTokenTable = 0;

  delete[] uncompressedMap;
  uncompressedMap = 0;

  delete[] uncompressedExpectedTokenTable;
  uncompressedExpectedTokenTable = 0;

  delete[] entryTable;
  entryTable = 0;
}

void LexerGeneratorImpl::testCharSets(int c)
{
/*
  GrammarCharSet gcs(CharacterRange(0, 2));
  gcs += CharacterRange(1, 1);
  printf("gcs.ctst(0): %d\n", gcs.ctst(0));
  printf("gcs.ctst(1): %d\n", gcs.ctst(1));
  printf("gcs.ctst(2): %d\n", gcs.ctst(2));
*/

  printf("testing charsets...\n\n");

  for (int power = 0; 1 << (3 * power) <= c; ++power)
    for (int n  = (1 << (3 * power)) - 1;
             n <= (1 << (3 * power)) + 1;
           ++n)
  {
    for (int l = 0; l < n; ++l)
    {
      printf("l = %d\n", l);

      for (int r = 0; r < n; ++r)
      {
//      printf("r = %d\n", r);

        ConstructionCharSet lcs(n);
        GrammarCharSet lcrs(n);
        for (int i = 0, v = l; v; ++i, v >>= 1)
        {
          if (v % 2)
          {
            lcs += CharacterRange(i);
            lcrs += CharacterRange(i, i);
          }
        }

        ConstructionCharSet rcs(n);
        GrammarCharSet rcrs(n);
        for (int i = 0, v = r; v; ++i, v >>= 1)
        {
          if (v % 2)
          {
            rcs += CharacterRange(i);
            rcrs += CharacterRange(i, i);
          }
        }

        int lics = 0;
        for (ConstructionCharSet::CharIterator i = lcs.charBegin();
             i != lcs.charEnd();
             ++i)
        {
          lics |= 1 << *i;
        }

        int rics = 0;
        for (ConstructionCharSet::CharIterator i = rcs.charBegin();
             i != rcs.charEnd();
             ++i)
        {
          rics |= 1 << *i;
        }

        int licsct = 0;
        for (Character c = 0; (1 << c) < n; ++c)
        {
          if (lcs.ctst(c)) licsct |= (1 << c);
        }

        int ricsct = 0;
        for (Character c = 0; (1 << c) < n; ++c)
        {
          if (rcs.ctst(c)) ricsct |= (1 << c);
        }

        for (int pass = 0; pass < 3; ++pass)
        {
          ConstructionCharSet dcs(lcs);
          GrammarCharSet dcrs(lcrs);
          int d = l;

          switch (pass)
          {
          case 0:
            d &= ~r;
            dcs -= rcs;
            dcrs -= rcrs;
            break;
          case 1:
            d |= r;
            dcs += rcs;
            dcrs += rcrs;
            break;
          case 2:
            d &= r;
            dcs.cand(rcs);
            dcrs.cand(rcrs);
            break;
          }

          int idcs = 0;
          for (ConstructionCharSet::CharIterator i = dcs.charBegin();
               i != dcs.charEnd();
               ++i)
          {
            idcs |= 1 << *i;
          }

          int idrs = 0;
          for (GrammarCharSet::CharIterator i = dcrs.charBegin();
               i != dcrs.charEnd();
               ++i)
          {
            idrs |= 1 << *i;
          }

          int idrsct = 0;
          for (Character c = 0; (1 << c) < n; ++c)
          {
            if (dcrs.ctst(c)) idrsct |= (1 << c);
          }

          int idcsct = 0;
          for (Character c = 0; (1 << c) < n; ++c)
          {
            if (dcs.ctst(c)) idcsct |= (1 << c);
          }

          if (   lics   != l
              || licsct != l
              || rics   != r
              || ricsct != r
              || idcs   != d
              || idrs   != d
              || idcsct != d
              || idrsct != d
             )
          {
            printf("pass = %d\n", pass);
            printf("l = %d, lics = %d, licsct = %d\n", l, lics, licsct);
            printf("lcs: "); printCharSet(&lcs); printf("\n");
            printf("lcrs: "); printCharSet(&lcrs); printf("\n");
            printf("\n");

            printf("r = %d, rics = %d, ricsct = %d\n\n", r, rics, ricsct);
            printf("rcs: "); printCharSet(&rcs); printf("\n");
            printf("rcrs: "); printCharSet(&rcrs); printf("\n");
            printf("\n");

            printf("d = %d, idcs = %d, idcsct = %d, idrsct = %d\n\n", d, idcs, idcsct, idrsct);
            printf("dcs: "); printCharSet(&dcs); printf("\n");
            printf("dcrs: "); printCharSet(&dcrs); printf("\n");
            printf("\n");

            exit(1);
          }
        }
      }
    }
  }
  printf("passed.\n\n");
}

void LexerGeneratorImpl::cleanup()
{
  free(instanceCode);
  instanceCode = 0;
  free(staticCode);
  staticCode = 0;
  delete charFolder;
  charFolder = 0;
}

int LexerGeneratorImpl::run(int argc, char **argv)
{
  clock_t cpu = clock();
  time_t timer;
  time(&timer);

  cleanup();
  initialize(argc, argv);

  int exitstatus = 0;

#if SELFTEST
//  testCharSets(1024);
#endif

  if (noerrors == 0)
  {
    parse(sourceGrammar);

    // fix rule links
    closeallrules();
    closetokens();

    if (noerrors == 0)
    {
      if (grammar)
      {
        printgrammar();
      }

#if CHARSETOPTIMIZATION
      GrammarCharSets combinedCharSets;
      charSetOptimization(combinedCharSets);
#endif

      GrammarCharClasses grammarCharClasses(charFolder);
      nfaconstruction(grammarCharClasses);

      if (noerrors == 0)
      {
        if (showNfa)
        {
          printNfa(tokenDescriptors);
        }

        DfaStates dfaStates(entries, minimize, ambiguities, tokenDescriptors, hightoken, &grammarCharClasses, disambiguationDisabled);
        dfaConstruction(grammarCharClasses, dfaStates);
      }
    }

    if (noerrors)
    {
      exitstatus= 1;
      blanklines(1);
      if (noerrors < 0)
      {
        fprintf(prn, "          Ambiguous.\n");
      }
      else if (! embedded)
      {
        fprintf(prn, "          %d syntactic/semantic error%s\n", noerrors, noerrors > 1 ? "s" : "");
      }
    }
  }

  // cleanup

  for (TokenDescriptors::const_iterator i = tokenDescriptors.begin(); i != tokenDescriptors.end(); ++i)
  {
    TokenDescriptor &t = tokenDescriptors.get(i->first);
    if (t.definition != undefined)
    {
      if (t.definition == numbered)
      {
        Rule::deleterules(t.u.rules);
      }
    }
    delete t.overrules;
    delete t.conflicts;

    deletenfa(t.nfa);
  }

  tokenDescriptors.clear();

  delete symbolTable;
  symbolTable = 0;

  delete defaultAlphabet;
  defaultAlphabet = 0;

  delete currentCharRangeList;
  currentCharRangeList = 0;

  List *p = preferences;
  for (List *n; p; p = n == preferences ? 0 : n)
  {
    n = p->link;
    free(p->u.pptr->preferred);
    free(p->u.pptr->nonpreferred);
    free(p->u.pptr);
    free(p);
  }
  preferences = 0;

  List *d = delimiters;
  for (List *n; d; d = n == delimiters ? 0 : n)
  {
    n = d->link;
    free(d->u.dptr->delimited);
    free(d->u.dptr);
    free(d);
  }
  delimiters = 0;

  List::deletelist(ntlist);
  entrylist::deletelist(entries);

  if (! embedded)
  {
    clock_t c = clock();
    time_t t;
    time(&t);
    blanklines(1);
    fprintf(prn, "          CPU Time%16.2f seconds\n", (double) (c - cpu) / CLOCKS_PER_SEC);
    fprintf(prn, "          Execution Time%10.2f seconds\n", difftime(t, timer));
    blanklines(1);
    fprintf(prn, "          Thank you for using REx.\n");
    if (prn != stdout) fclose(prn);
  }

  return exitstatus;
}
