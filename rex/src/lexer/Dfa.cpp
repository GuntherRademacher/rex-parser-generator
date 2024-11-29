#include "../common/Memory.hpp"

#include "Dfa.hpp"

void TransitionMap::consolidate(CharSets<const ConstructionCharSet> &transitionSets)
{
  for (iterator i(begin()); i != end(); )
  {
    const ConstructionCharSet *old1(i->first);
    ConstructionCharSet sum(*old1);

    TransitionDescriptor td(i->second);
    td.shift = td.shift->group[0];

    bool doErase = false;

    TransitionMap::iterator j(i);
    for (++j; j != end(); )
    {
      if (j->second.shift->group[0] == td.shift)
      {
        const ConstructionCharSet *old2(j->first);
        sum += *old2;
        TransitionMap::iterator k(j);
        ++j;
        erase(k);
        doErase = true;
      }
      else
      {
        ++j;
      }
    }

    if (doErase)
    {
      j = i;
      ++i;
      erase(j);
      insert(TransitionMap::value_type(transitionSets.insert(sum), td));
    }
    else
    {
      i->second.shift = td.shift;
      ++i;
    }
  }
}

bool TransitionsByDfaGroup::operator<(const TransitionsByDfaGroup &rhs) const
{
  const_iterator li(begin());
  const_iterator ri(rhs.begin());
  for (;; ++li, ++ri)
  {
    if (li == end()) return ri != rhs.end();
    if (ri == rhs.end()) break;
    const value_type &lv(*li);
    const value_type &rv(*ri);
    if (*lv.second < *rv.second) return true;
    if (*rv.second < *lv.second) break;
    if (TransitionsByDfaGroupLess(dfaStates)(lv.first, rv.first)) return true;
    if (TransitionsByDfaGroupLess(dfaStates)(rv.first, lv.first)) break;
  }
  return false;
}

void TransitionsByDfaGroup::populate(DfaState *dfa, CharSets<const ConstructionCharSet> &transitionSets)
{
  for (TransitionMap::const_iterator i = dfa->tm.begin(); i != dfa->tm.end(); ++i)
  {
    TransitionsByDfaGroup::value_type v(i->second.shift, i->first);
    std::pair <iterator, bool> j(insert(v));
    if (! j.second)
    {
      ConstructionCharSet jcs(*j.first->second);
      jcs += *i->first;
      j.first->second = transitionSets.insert(jcs);
    }
  }
}

bool TransitionsByDfaGroupLess::operator()(const DfaState *lhs, const DfaState *rhs) const
{
  return lhs->group[1 - dfaStates->currentgroup] < rhs->group[1 - dfaStates->currentgroup];
}

void DfaStates::createLookaheadAnnotations()
{
  for (DfaState *current = first(); current; current = current->link)
  {
    // look at all states that can be reached in a single transition from current

    for (TransitionMap::const_iterator i = current->tm.begin(); i != current->tm.end(); ++i)
    {
      DfaState *next = i->second.shift;

      // look at next state's annotations
      for (AnnotationSet::const_iterator j = next->annotationSet.begin(); j != next->annotationSet.end(); ++j)
      {
        const Annotation &annotation = *j;

        if (   annotation.getAnnotationType() == TOKENCOMPLETED
            && annotation.getLookaheadType()  == FIXEDTOKENLENGTH
            && annotation.getFixedlength()    >  0)
        {
          current->annotationSet.insert(Annotation(annotation.getId(),
                                                   WITHINTOKEN,
                                                   annotation.getLookaheadType(),
                                                   annotation.getFixedlength() - 1));
        }
        else if (annotation.getAnnotationType() == FINAL)
        {
          switch (annotation.getLookaheadType())
          {
          case FIXEDLOOKAHEADLENGTH:
            if (annotation.getFixedlength()   >  0)
            {
              current->annotationSet.insert(Annotation(annotation.getId(),
                                                       WITHINLOOKAHEAD,
                                                       FIXEDLOOKAHEADLENGTH,
                                                       annotation.getFixedlength() - 1));
            }
            else
            {
              current->annotationSet.insert(Annotation(annotation.getId(),
                                                       WITHINTOKEN,
                                                       FIXEDLOOKAHEADLENGTH,
                                                       0));
            }
            break;
          case FIXEDTOKENLENGTH:
            current->annotationSet.insert(Annotation(annotation.getId(),
                                                     WITHINLOOKAHEAD,
                                                     FIXEDTOKENLENGTH,
                                                     0));
            break;
          case NOLOOKAHEAD:
            current->annotationSet.insert(Annotation(annotation.getId(),
                                                     WITHINTOKEN,
                                                     NOLOOKAHEAD,
                                                     0));
            break;
          }
        }
      }
    }
  }

  // propagate WITHIN tags to predecessor states

  for (bool changed = true; changed; )
  {
    changed = false;

    for (DfaState *current = first(); current; current = current->link)
    {
      // look at all states that can be reached in a single transition from current

      for (TransitionMap::const_iterator i = current->tm.begin(); i != current->tm.end(); ++i)
      {
        DfaState *next = i->second.shift;

        // look at next state's annotations
        for (AnnotationSet::const_iterator j = next->annotationSet.begin(); j != next->annotationSet.end(); ++j)
        {
          const Annotation &annotation = *j;

          switch (annotation.getAnnotationType())
          {
          case WITHINTOKEN:
            if (annotation.getLookaheadType() == FIXEDTOKENLENGTH)
            {
              if (annotation.getFixedlength() > 0)
              {
                if (current->annotationSet.insert(Annotation(annotation.getId(),
                                                             WITHINTOKEN,
                                                             FIXEDTOKENLENGTH,
                                                             annotation.getFixedlength() - 1)))
                {
                  changed = true;
                }
              }
            }
            else
            {
              if (current->annotationSet.insert(Annotation(annotation.getId(),
                                                           WITHINTOKEN,
                                                           annotation.getLookaheadType(),
                                                           0)))
              {
                changed = true;
              }
            }
            break;
          case WITHINLOOKAHEAD:
            if (annotation.getLookaheadType() == FIXEDTOKENLENGTH)
            {
              if (current->annotationSet.insert(annotation))
              {
                changed = true;
              }
            }
            else if (annotation.getFixedlength() > 0)
            {
              if (current->annotationSet.insert(Annotation(annotation.getId(),
                                                           WITHINLOOKAHEAD,
                                                           annotation.getLookaheadType(),
                                                           annotation.getFixedlength() - 1)))
              {
                changed = true;
              }
            }
            else
            {
              if (current->annotationSet.insert(Annotation(annotation.getId(),
                                                           WITHINTOKEN,
                                                           annotation.getLookaheadType(),
                                                           0)))
              {
                changed = true;
              }
            }
            break;

          case FINAL:
          case TOKENCOMPLETED:
          case NEGATING:
            break;

          default:
            internalerr();
            break;
          }
        }
      }
    }
  }

  for (DfaState *current = first(); current; current = current->link)
  {
    // look at current state's annotations
    for (AnnotationSet::const_iterator j = current->annotationSet.begin();
         j != current->annotationSet.end();
        )
    {
      const Annotation &annotation = *j;
      if (   annotation.getAnnotationType() != WITHINTOKEN
          || annotation.getLookaheadType() != FIXEDTOKENLENGTH)
      {
        ++j;
      }
      else
      {
        current->annotationSet.erase(Annotation(annotation.getId(),
                                     WITHINLOOKAHEAD,
                                     annotation.getLookaheadType(),
                                     0));
        ++j;
      }
    }
  }
}

void DfaStates::incorporatepreferences()
{
  for (DfaState *dfa = first(); dfa; dfa = dfa->link)
  {
    for (AnnotationSet::const_iterator i = dfa->annotationSet.begin(); i != dfa->annotationSet.end(); )
    {
      const Annotation &a1 = *i;
      ++i;
      TokenId c1 = a1.getId();

      TokenDescriptor *t1 = &tokenDescriptors.get(c1);

      for (AnnotationSet::const_iterator j = dfa->annotationSet.begin(); j != dfa->annotationSet.end(); )
      {
        bool eraseA2 = false;
        const Annotation &a2(*j);
        ++j;
        TokenId c2 = a2.getId();

        if (c1 == c2)
        {
          if (a1 != a2)
          {
            fprintf(stderr, "token %d a.l %d a.f %d r.l %d r.f %d\n", a1.getId(),
                a2.getLookaheadType(), a2.getFixedlength(),
                a1.getLookaheadType(), a1.getFixedlength());

            if (a2.getLookaheadType() == FIXEDTOKENLENGTH)
            {
              if (a1.getLookaheadType() != FIXEDTOKENLENGTH)
              {
                internalerr(); // should have been detected by tokennfa()
              }

              if (t1->nongreedy)
              {
                if (a1.getFixedlength() < a2.getFixedlength())
                {
                  eraseA2 = true;
                }
                else
                {
                  dfa->annotationSet.erase(a1);
                  break;
                }
              }
              else
              {
                if (a1.getFixedlength() > a2.getFixedlength())
                {
                  eraseA2 = true;
                }
                else
                {
                  dfa->annotationSet.erase(a1);
                  break;
                }
              }
            }
            else
            {
              if (a1.getLookaheadType() == FIXEDTOKENLENGTH)
              {
                internalerr(); // should have been detected by tokennfa()
              }

              if (t1->nongreedy)
              {
                if (a1.getFixedlength() > a2.getFixedlength())
                {
                  eraseA2 = true;
                }
                else
                {
                  dfa->annotationSet.erase(a1);
                  break;
                }
              }
              else
              {
                if (a1.getFixedlength() < a2.getFixedlength())
                {
                  eraseA2 = true;
                }
                else
                {
                  dfa->annotationSet.erase(a1);
                  break;
                }
              }
            }
          }
        }
        // c1 != c2
        else
        {
          if (! disambiguationDisabled && t1->overrules && t1->overrules->contains(c2))
          {
            eraseA2 = true;
          }
          else
          {
            TokenDescriptor *t2 = &tokenDescriptors.get(c2);
            if (! disambiguationDisabled && t2->overrules && t2->overrules->contains(c1))
            {
              dfa->annotationSet.erase(a1);
              break;
            }
            else if (! ambiguities)
            {
              if (t1->conflicts == 0) t1->conflicts = new ConflictSet();
              t1->conflicts->insert(c2);
              if (t2->conflicts == 0) t2->conflicts = new ConflictSet();
              t2->conflicts->insert(c1);

              eraseA2 = true;
            }
          }
        }

        if (eraseA2)
        {
          if (! (*i != a2)) ++i;
          dfa->annotationSet.erase(a2);
        }
      }
    }
  }
}

void DfaStates::dropNonResultAnnotations()
{
  for (DfaState *dfa = first(); dfa; dfa = dfa->link)
  {
    for (AnnotationSet::const_iterator current = dfa->annotationSet.begin(); current != dfa->annotationSet.end(); )
    {
      switch (current->getAnnotationType())
      {
      case WITHINTOKEN:
        {
          Annotation operand(*current);
//          fprintf(stderr, "removing WITHINTOKEN annotation for %d\n", operand.getId());
          ++current;
          dfa->annotationSet.erase(operand);
        }
        break;

      case TOKENCOMPLETED:
        {
          Annotation operand(*current);
//          fprintf(stderr, "removing TOKENCOMPLETED annotation for %d\n", operand.getId());
          ++current;
          dfa->annotationSet.erase(operand);
        }
        break;

      case WITHINLOOKAHEAD:
        {
          Annotation operand(*current);
//          fprintf(stderr, "removing WITHINLOOKAHEAD annotation for %d\n", operand.getId());
          ++current;
          dfa->annotationSet.erase(operand);
        }
        break;

      case FINAL:
        ++current;
        break;

      case NEGATING:
        {
  //      fprintf(stderr, "found SUBTRAHEND %d\n", current->second.getId() - 1);

          Annotation operand(current->getId(),
                             FINAL,
                             current->getLookaheadType(),
                             current->getFixedlength());

          if (dfa->annotationSet.contains(operand))
          {
  //        fprintf(stderr, "    and MINUEND\n");

            dfa->annotationSet.erase(operand);
          }

          dfa->annotationSet.erase(*current);

          current = dfa->annotationSet.begin(); // restart loop after deleting up to 2 result entries
        }
        break;

      default:
        internalerr();
        break;
      }
    }
  }
}

void DfaStates::cutTransitionsFromNongreedy()
{
  // remove transitions from nongreedy final states

  for (DfaState *dfa = first(); dfa; dfa = dfa->link)
  {
    for (AnnotationSet::const_iterator current = dfa->annotationSet.begin(); current != dfa->annotationSet.end(); ++current)
    {
      const TokenDescriptor &t(tokenDescriptors.get(current->getId()));

      if (t.nongreedy && dfa->tm.size())
      {
        dfa->tm.clear();
        dfa->tb.clear();
        dfa->alltransitions.clear();
      }
    }
  }
}

void DfaStates::reach(DfaState *dfa)
{
  dfa->reachable = true;
  for (TransitionMap::iterator i(dfa->tm.begin()); i != dfa->tm.end(); ++i)
  {
    DfaState *shift = i->second.shift;
    if (! shift->reachable)
    {
      reach(shift);
    }
  }
}

void DfaStates::propagateExpectedTokenSets()
{
  /* initial step: set token codes as expected by each state */

  for (DfaState *dfa = first(); dfa; dfa = dfa->link)
  {
    if (dfa->expectedTokenSet) delete dfa->expectedTokenSet;
    dfa->expectedTokenSet = new BitSet(hightoken + 1);

    for (TransitionMap::iterator i(dfa->tm.begin()); i != dfa->tm.end(); ++i)
    {
      const AnnotationSet &expected(i->second.shift->annotationSet);
      for (AnnotationSet::const_iterator j = expected.begin(); j != expected.end(); ++j)
      {
        if (j->getAnnotationType() == FINAL)
        {
          *dfa->expectedTokenSet += CharacterRange(j->getId());
        }
      }
    }
  }

  /* induction: while any changes, propagate shift state's token sets */

  for (bool again = true; again; )
  {
    again = false;
    for (DfaState *dfa = first(); dfa; dfa = dfa->link)
    {
      for (TransitionMap::iterator i(dfa->tm.begin()); i != dfa->tm.end(); ++i)
      {
        DfaState *shift = i->second.shift;
        if (ConstructionCharSet::csub(*shift->expectedTokenSet, *dfa->expectedTokenSet) < 2)
        {
          *dfa->expectedTokenSet += *shift->expectedTokenSet;
          again = true;
        }
      }
    }
  }
}

void DfaStates::removeDeadStates()
{
  DfaState *dfa;

  // remove transitions to states with an empty expected-token set

  for (dfa = first(); dfa; dfa = dfa->link)
  {
    dfa->alltransitions.clear();

    for (TransitionMap::iterator i = dfa->tm.begin(); i != dfa->tm.end(); )
    {
      if (i->second.shift->expectedTokenSet->empty() && i->second.shift->annotationSet.empty())
      {
        TransitionMap::iterator j(i);
        ++i;
        dfa->tm.erase(j);
      }
      else
      {
        const ConstructionCharSet *cs = i->first;

        dfa->alltransitions += *cs;

        ++i;
      }
    }
  }

  // mark reachable states

  const entrylist *entryptr = entries;
  do
  {
    entryptr = entryptr->link;
    if (entryptr->dfa)
    {
      reach(entryptr->dfa);
    }
  }
  while (entryptr != entries);

  // remove unreachable states

  dfa = first();
  if (! dfa->reachable)
  {
    internalerr();
  }

  while (dfa->link)
  {
    if (dfa->link->reachable)
    {
      dfa = dfa->link;
    }
    else
    {
      DfaState *d = dfa->link;
      dfa->link = d->link;
      delete d;
    }
  }

  // verify

  if (0)
  {
    for (dfa = first(); dfa; dfa = dfa->link)
    {
      dfa->reachable = false;
    }

    const entrylist *entryptr = entries;
    do
    {
      entryptr = entryptr->link;
      if (entryptr->dfa)
      {
        reach(entryptr->dfa);
      }
    }
    while (entryptr != entries);

    for (dfa = first(); dfa; dfa = dfa->link)
    {
      if (! dfa->reachable)
      {
        fprintf(stderr, "unreachable state was not deleted");
        internalerr();
      }

      if (dfa->expectedTokenSet->empty() && dfa->annotationSet.empty())
      {
        fprintf(stderr, "found dfa state with empty expectedTokenSet\n");
        internalerr();
      }

      if (dfa->annotationSet.empty() && dfa->tm.empty())
      {
        fprintf(stderr, "found dfa state with neither transitions nor results\n");
        internalerr();
      }
    }
  }
}

DfaStates::DfaStates(entrylist *e,
                     bool m,
                     bool a,
                     TokenDescriptors &t,
                     int h,
                     const GrammarCharClasses *g,
                     bool d)
: currentgroup(0),
  states(DfaByNfaSet::key_compare(), Alloc<std::pair<const DfaStateKey, DfaState *> >(__FILE__, __LINE__)),
  nofdfas(0),
  dfalist(0),
  dfaend(0),
  ambiguities(a),
  entries(e),
  minimize(m),
  gcc(*g),
  maxfixedlength(0),
  tokenDescriptors(t),
  hightoken(h),
  disambiguationDisabled(d)
{
  subsetConstruction();

  if (first() == 0)
  {

  }
  else
  {
#if 0
    createLookaheadAnnotations();
#endif

    dropNonResultAnnotations();
    incorporatepreferences();

    // TODO: report conflict between greedy/nongreedy tokens
    cutTransitionsFromNongreedy();

    propagateExpectedTokenSets();
    removeDeadStates();

    minimizeDfa();
  }
}

void DfaStates::subsetConstruction()
{
  // establish construction set cardinality:
  // number of classes + 1 (for the empty class)

  size_t cardinality = gcc.count() + 1;

  entrylist *entryptr = entries;
  do
  {
    entryptr = entryptr->link;
    NfaSet *nfaset = new NfaSet();

    List *obj = entryptr->elist;

    if (obj)
    {
      do
      {
        obj = obj->link;
        TokenId t = obj->u.eptr->tokencode;
        if (t >= 0)
        {
          NfaState *newnfa = tokenDescriptors.get(t).nfa;
          if (newnfa) *nfaset += newnfa;
        }
        else
        {
          obj->u.eptr->ntptr->istoken = true;
        }
      }
      while (obj != entryptr->elist);
    }

    if (nfaset->empty())
    {
      delete nfaset;
      entryptr->dfa = 0;
    }
    else
    {
      entryptr->dfa = insert(cardinality, nfaset);
    }
  }
  while (entryptr != entries);

  /* DFA initial state computation done; enter subset construction */

  maxfixedlength = 0;

  for (DfaState *dfa = first(); dfa; dfa = dfa->link)
  {
    for (NfaSet::const_iterator nfalist = dfa->nfaset->begin(); nfalist != dfa->nfaset->end(); ++nfalist)
    {
      const NfaState *newnfa= *nfalist;
      switch (newnfa->kind)
      {
      case final:
        dfa->annotationSet.insert(newnfa->annotation);

        if (maxfixedlength < newnfa->annotation.getFixedlength())
        {
          maxfixedlength = newnfa->annotation.getFixedlength();
        }
        break;

      case settrans:
        {
          ConstructionCharSet shiftset(cardinality);
          const ConstructionCharSet *converted = newnfa->u.on->getConverted();
          if (converted)
          {
            shiftset = *converted;
          }
          else
          {
            gcc.classify(*newnfa->u.on, shiftset);
            const_cast<GrammarCharSet *>(newnfa->u.on)->setConverted(shiftset);
          }

          do
          {
            ConstructionCharSet intersection(dfa->alltransitions);
            intersection.cand(shiftset);
            if (intersection.empty())
            {
              /* different from all previous; make new transition */
              dfa->alltransitions += shiftset;

              TransitionDescriptor td(new NfaSet());
              *td.nfaset += newnfa->shift;
              dfa->tm.insert(TransitionMap::value_type(transitionSets.insert(shiftset), td));
              break;
            }
            else
            {
              for (TransitionMap::iterator i(dfa->tm.begin()); i != dfa->tm.end(); ++i)
              {
                const ConstructionCharSet *old(i->first);

                intersection = *old;
                intersection.cand(shiftset);
                if (! intersection.empty())
                {
                  shiftset -= intersection;

                  if (*old == intersection)  /* state covers proper subset */
                  {
                    *i->second.nfaset += newnfa->shift;
                  }
                  else
                  {
                    dfa->alltransitions += intersection;

                    ConstructionCharSet difference(*old);
                    difference -= intersection;

                    TransitionDescriptor td1(i->second);
                    dfa->tm.erase(i);
                    dfa->tm.insert(TransitionMap::value_type(transitionSets.insert(difference), td1));

                    TransitionDescriptor td2(new NfaSet());
                    *td2.nfaset += *td1.nfaset;
                    *td2.nfaset += newnfa->shift;
                    dfa->tm.insert(TransitionMap::value_type(transitionSets.insert(intersection), td2));
                  }
                  break;
                }
              }
            }
          }
          while (! shiftset.empty());
        }
        break;

      default:
        internalerr();
        break;
      }
    }

    for (TransitionMap::iterator i = dfa->tm.begin(); i != dfa->tm.end(); ++i)
    {
      TransitionDescriptor &td(i->second);
      td.shift = insert(cardinality, td.nfaset);
      td.nfaset = 0;
    }

    dfa->tm.consolidate(transitionSets);
  }

  // drop nfa sets

  states.clear();
  for (DfaState *dfa = first(); dfa; dfa = dfa->link)
  {
    delete dfa->nfaset;
    dfa->nfaset = 0;
  }
}

void DfaStates::minimizeDfa()
{
  if (minimize)
  {
    DfaByAcceptanceBehavior::process(*this, currentgroup);

    currentgroup = 1 - currentgroup;    /* toggle group selector           */

    for (DfaState *dfa = first(); dfa; dfa = dfa->link)
    {
      dfa->tb.populate(dfa, transitionSets);
    }

//    printf("currentgroupcount after inititial pass %d\n", DfaByAcceptanceBehavior::size());

    for (;;)
    {                                /* loop while group grows          */
      bool isMinimal = true;

      for (DfaState *dfa = first(); dfa; dfa = dfa->link)
      {
        dfa->regrouped = dfa->group[1 - currentgroup] != dfa->group[currentgroup];
        isMinimal = isMinimal && ! dfa->regrouped;
      }

      if (isMinimal)
      {
        break;
      }

      DfaByTransitionBehavior::process(*this, currentgroup);

      currentgroup = 1 - currentgroup;    /* toggle group selector           */
    }

    // got the minimized DFA; link shift states to group representatives

    for (DfaState *dfa = first(); dfa; dfa = dfa->link)
    {
      if (dfa->group[0] == dfa)
      {
        dfa->tm.consolidate(transitionSets);
      }
    }

    // adjust entry pointers

    entrylist *entryptr = entries;
    do
    {
      entryptr = entryptr->link;
      if (entryptr->dfa)
      {
        entryptr->dfa = entryptr->dfa->group[0];
      }
    }
    while (entryptr != entries);

    // delete duplicate states

    for (DfaState *dfa = first(); dfa->link; )
    {
      if (dfa->link->group[0] == dfa->link)
      {
        dfa = dfa->link;
      }
      else
      {
        DfaState *d = dfa->link;
        dfa->link = d->link;
        delete d;
      }
    }

    // renumber (starting with 1)

    renumber();

    for (DfaState *dfa = first(); dfa; dfa = dfa->link)
    {
      dfa->tb.clear();
      dfa->tb.populate(dfa, transitionSets);
    }

    // minimization done
  }
}
