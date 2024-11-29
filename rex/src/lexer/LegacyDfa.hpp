/*
 * LegafyDfa.hpp
 *
 *  Created on: Dec 9, 2009
 *      Author: Gunther
 */

#ifndef LEGAFYDFA_HPP
#define LEGAFYDFA_HPP

#include "Dfa.hpp"
#include <string>

class LegacyDfa
{
public:
  LegacyDfa(const LexerGeneratorImpl &r, DfaStates &d, const GrammarCharClasses &g)
  : rex(r),
    dfaStates(d),
    gcc(g),
    legacyDfa(0),
    legacyDfaSize(0)
  {
    buildTransitions();
    getLegacyDfa();
  }

  ~LegacyDfa()
  {
    free(legacyDfa);
  }

  size_t size() const {return legacyDfaSize;}
  const int *data() const {return legacyDfa;}

  bool equals(const int *other) const
  {
    for (size_t i = 0; i < legacyDfaSize; ++i)
    {
      if (legacyDfa[i] != other[i]) return false;
    }
    return true;
  }

private:
  class TransitionList : public std::list <std::pair <GrammarCharSet *, DfaState *>, Alloc<std::pair <GrammarCharSet *, DfaState *> > >
  {                     typedef std::list <std::pair <GrammarCharSet *, DfaState *>, Alloc<std::pair <GrammarCharSet *, DfaState *> > >
                        super;
  public:
    TransitionList()
    : super(Alloc<std::pair <GrammarCharSet *, DfaState *> >(__FILE__, __LINE__))
    {}
  };

  void buildTransitions(DfaState *dfa)
  {
    Transition *t1 = 0;

    if (rex.classify)
    {
      for (Character c1 = dfa->alltransitions.cnxs();
           c1 != ConstructionCharSet::CNONE;
           c1 = dfa->alltransitions.cnxs(c1))
      {
        for (TransitionMap::iterator i(dfa->tm.begin()); i != dfa->tm.end(); ++i)
        {
          if (i->first->ctst(c1))
          {
            Character c2 = i->first->cnxc(c1);
            if (c2 == ConstructionCharSet::CNONE)
            {
              c2 = (Character) i->first->cardinality();
            }
            --c2;

            if (t1 == 0)
            {
              t1 = ALLOCATE(Transition);
              dfa->transitions = t1;
            }
            else
            {
              t1->link = ALLOCATE(Transition);
              t1 = t1->link;
            }

            t1->shift = i->second.shift;
            t1->low = (int) c1;
            t1->up = (int) c2;

            c1 = c2;
            break;
          }
        }
      }
    }
    else
    {
      GrammarCharSet gcsAll;
      gcc.declassify(dfa->alltransitions, gcsAll);

      TransitionList transitionList;
      for (TransitionMap::iterator i(dfa->tm.begin()); i != dfa->tm.end(); ++i)
      {
        GrammarCharSet *gcs = new GrammarCharSet();
        gcc.declassify(*i->first, *gcs);
        transitionList.push_back(TransitionList::value_type(gcs, i->second.shift));
      }

      while (! gcsAll.empty())
      {
        Character c1(*gcsAll.charBegin());
        for (TransitionList::iterator i(transitionList.begin()); i != transitionList.end(); ++i)
        {
          GrammarCharSet *gcs(i->first);
          bool next = false;
          for (GrammarCharSet::RangeIterator j(gcs->rangeBegin()); j != gcs->rangeEnd(); ++j)
          {
            Character c2 = j->getHigh();
            if (j->getLow() <= c1 && c1 <= c2)
            {
              if (t1 == 0)
              {
                t1 = ALLOCATE(Transition);
                dfa->transitions = t1;
              }
              else
              {
                t1->link = ALLOCATE(Transition);
                t1 = t1->link;
              }

              t1->shift = i->second;
              t1->low = (int) c1;
              t1->up = (int) c2;

              gcsAll -= CharacterRange(*j);

              next = true;
              break;
            }
          }

          if (next)
          {
            break;
          }
        }
      }

      for (TransitionList::iterator i(transitionList.begin()); i != transitionList.end(); ++i)
      {
        delete i->first;
      }
    }

    if (t1)
    {
      t1->link = 0;
    }
  }

  void buildTransitions()
  {
    for (DfaState *dfa = dfaStates.first(); dfa; dfa = dfa->link)
    {
      /* build transition list */
      buildTransitions(dfa);
      for (Transition *t1 = dfa->transitions; t1; t1 = t1->link)
      {
        Character c(t1->up);
        DfaState *shift = t1->shift;

        for (Transition *t2 = t1->link; t2;)
        {
          if (t2->low != c + 1)
          {
            t2 = 0;
          }
          else if (t2->shift == shift)
          {
            t2->low = t1->low;
            t2 = t1->link;
            memcpy(t1, t2, sizeof *t1);
            free(t2);
            t2 = 0;
          }
          else
          {
            c = t2->up;
            t2 = t2->link;
          }
        }
      }
    }
  }

  void appendToLegacyDfa(int pass, int n)
  {
    if (pass == 2)
    {
      legacyDfa[legacyDfaSize] = n;
    }
    legacyDfaSize++;
  }

  void getLegacyDfa()
  {
    for (int pass = 1; pass <= 2; ++pass)
    {
      legacyDfaSize = 0;

      entrylist *entryptr = rex.entries;
      do
      {
        entryptr = entryptr->link;
        if (pass == 1)
        {
          legacyDfaSize++;
        }
        else
        {
          int k = entryptr->dfa == 0
                ? dfaStates.first()->location          /* map empty entries to first */
                : entryptr->dfa->location;

  // #option noambiguities used to be marked by a negative link to
  // the whitespace automaton. This feature has been discontinued
  // to avoid special case at runtime.
  //
  //      if ((legacyDfaSize == 0) && ! ambiguities) k = -k;

          appendToLegacyDfa(pass, k);
        }
      }
      while (entryptr != rex.entries);

      for (TokenId id = rex.hightoken; id >= 0; --id)
      {
        TokenDescriptors::const_iterator i(rex.tokenDescriptors.find(id));
        if (i == rex.tokenDescriptors.end() || i->second.lexaction == 0)
        {
          appendToLegacyDfa(pass, 0);
        }
        else
        {
          appendToLegacyDfa(pass, i->second.lexaction->code + 1);
        }
      }

      for (DfaState *dfa = dfaStates.first(); dfa; dfa= dfa->link)
      {
        dfa->location = (int) legacyDfaSize + 1;

        for (AnnotationSet::const_iterator t = dfa->annotationSet.begin(); t != dfa->annotationSet.end(); )
        {
          int code = t->getId() + 1;
          if (t->getLookaheadType() != NOLOOKAHEAD)
          {
            internalerr();
          }
          ++t;
          if (rex.ambiguities || t == dfa->annotationSet.end()) appendToLegacyDfa(pass, - code);
        }

        bool markzero = true;

        for (Transition *trans = dfa->transitions; trans; trans = trans->link)
        {
          int k = pass == 1 ? 0 : trans->shift->location;
          if (trans->link)
          {
            markzero = false;
          }
          else if (! markzero)
          {
            k = - k;
          }
          appendToLegacyDfa(pass, k);

          if (rex.compression == 0)
          {
            appendToLegacyDfa(pass, trans->low);
            appendToLegacyDfa(pass, trans->up);
          }
          else
          {
            appendToLegacyDfa(pass, RANGE(trans->low, trans->up));
          }
        }

        if (markzero)
        {
          appendToLegacyDfa(pass, 0);
        }
      }

      if (pass == 1)
      {
        legacyDfa = ALLOCATE_ARRAY(int, legacyDfaSize);
      }
    }
  }

  const LexerGeneratorImpl &rex;
  const DfaStates &dfaStates;
  const GrammarCharClasses &gcc;
  int *legacyDfa;
  size_t legacyDfaSize;
};

#endif
