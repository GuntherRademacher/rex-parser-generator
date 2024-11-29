/*
 * Dfa.hpp
 *
 *  Created on: 09.04.2009
 *      Author: Gunther
 */

#ifndef DFA_HPP
#define DFA_HPP

#include "CharClasses.hpp"
#include "SymbolTable.hpp"
#include "Syntax.hpp"
#include "Nfa.hpp"

#include "../common/Error.hpp"
#include "../common/Math.hpp"

#include <set>
#include <map>

class DfaState;
class DfaStates;

class Transition
{
public:
  Transition *link;         /* pointer to other transitions     */
  DfaState *shift;          /* follower state                   */
  Character low,up;         /* character subrange bounds        */
};

#if 0
class NfaSet : private std::set<NfaState *, PtrLess<NfaState>, Alloc<NfaState *> >
{              typedef std::set<NfaState *, PtrLess<NfaState>, Alloc<NfaState *> >
               super;
public:
  NfaSet() : super(PtrLess<NfaState>(), Alloc<NfaState *>(__FILE__, __LINE__)) {}

  typedef super::const_iterator const_iterator;
  const_iterator begin() const {return super::begin();}
  const_iterator end() const {return super::end();}
  bool operator<(const NfaSet &rhs) {return *(super *) this < *(super *) &rhs;}

  NfaSet &operator+=(NfaSt
    ate *nfa)
  {
    switch (nfa->kind)
    {
    case settrans:
    case final:
      super::insert(nfa);
      break;

    case fork:
      {
        int newnfano = nfa->nfano;
        nfa->nfano= -newnfano;
        if (nfa->shift->nfano > 0) *this += nfa->shift;
        if (nfa->u.two->nfano > 0) *this += nfa->u.two;
        nfa->nfano = newnfano;
      }
      break;

    default:
      internalerr();
    }
    return *this;
  }

  NfaSet &operator+=(const NfaSet &set)
  {
    if (super::empty())
    {
      *(super *) this = set;
    }
    else
    {
      super::insert(set.begin(), set.end());
    }
    return *this;
  }

  bool empty() const {return super::empty();}

  int hash() const
  {
    int code = 1;
    for (NfaSet::const_iterator i = begin(); i != end(); ++i)
    {
      code = ((code * 3) ^ (*i)->nfano) & 0x7fffffff;
    }
    return code;
  }

private:
  NfaSet(const NfaSet &set) : super(PtrLess<NfaState>(), Alloc<NfaState *>(__FILE__, __LINE__)) {internalerr();}
  NfaSet &operator=(const NfaSet &set) {internalerr();}
};
#else
class NfaSet
{
public:
  NfaSet() : nfaset(0) {}

  ~NfaSet()
  {
    if (nfaset)
    {
      List *eol = nfaset;
      List *nfalist = eol->link;
      eol->link = 0;
      List::deletelist(nfalist);
    }
  }

  class const_iterator
  {
  public:
    const_iterator(List *n) : end(n), current(n ? n->link : 0) {}

    const_iterator &operator++()
    {
      if (current && current != end)
      {
        current = current->link;
      }
      else
      {
        current = 0;
      }
      return *this;
    }

    bool operator!=(const const_iterator &rhs)
    {
      return current != rhs.current;
    }

    NfaState *operator*() const {return current->u.nfa;}

  private:
    List *end;
    List *current;
  };

  const_iterator begin() const {return const_iterator(nfaset);}
  const_iterator end() const {return const_iterator(0);}

  bool operator<(const NfaSet &rhs) const
  {
    NfaSet::const_iterator la = begin();
    NfaSet::const_iterator lb = rhs.begin();
    do
    {
      if ((*la)->nfano > (*lb)->nfano)
        lb = rhs.end();
      else if ((*la)->nfano < (*lb)->nfano)
        la = end();
      else
      {
        ++la;
        ++lb;
      }
    }
    while (la != end() && lb != rhs.end());

    if (! (la != end() || lb != rhs.end()))
      return false;
    else
      return ! (lb != rhs.end());
  }

  NfaSet &operator+=(NfaState *nfa)
  {
    List *last;
    List *current;
    List *next;
    int newnfano;
    int nxtnfano;

    newnfano = nfa->nfano;
    switch (nfa->kind)
    {
    case fork:
      nfa->nfano= -newnfano;
      if (nfa->shift->nfano > 0) *this += nfa->shift;
      if (nfa->u.two->nfano > 0) *this += nfa->u.two;
      nfa->nfano = newnfano;
      break;

    case settrans:
    case final:
      if (nfaset == 0)
      {
        nfaset = ALLOCATE(List);
        nfaset->u.nfa = nfa;
        nfaset->link = nfaset;
      }
      else
      {
        last = nfaset;
        do
        {
          next = last->link;
          nxtnfano = next->u.nfa->nfano;
          if (nxtnfano < newnfano)
          {
            last = next;
          }
          else
          {
            if (nxtnfano != newnfano)
            {
              current = ALLOCATE(List);
              current->u.nfa = nfa;
              current->link = next;
              last->link = current;
            }
            nfa = 0;
            last = nfaset;
          }
        }
        while (last != nfaset);

        if (nfa)
        {
          nfaset = ALLOCATE(List);
          nfaset->u.nfa = nfa;
          nfaset->link = last->link;
          last->link = nfaset;
        }
      }
      break;
    }
    return *this;
  }

  NfaSet &operator+=(const NfaSet &set)
  {
    List *ptr = set.nfaset;
    do
    {
      ptr = ptr->link;
      *this += ptr->u.nfa;
    }
    while (ptr != set.nfaset);

    return *this;
  }

  bool empty() const {return nfaset == 0;}

  int hash() const
  {
    int code = 1;
    for (NfaSet::const_iterator i = begin(); i != end(); ++i)
    {
      code = ((code * 3) ^ (*i)->nfano) & 0x7fffffff;
    }
    return code;
  }

private:
  NfaSet(const NfaSet &set) : nfaset(0) {internalerr();}
  NfaSet &operator=(const NfaSet &set) {internalerr(); return *this;}

  List *nfaset;
};
#endif

class TransitionDescriptor
{
public:
  TransitionDescriptor(NfaSet *n) : nfaset(n), shift(0) {}

  NfaSet *nfaset;
  DfaState *shift;
};

class TransitionMap : public std::map<const ConstructionCharSet *, TransitionDescriptor, PtrLess<const ConstructionCharSet>, Alloc<std::pair<const ConstructionCharSet *, TransitionDescriptor> > >
{                    typedef std::map<const ConstructionCharSet *, TransitionDescriptor, PtrLess<const ConstructionCharSet>, Alloc<std::pair<const ConstructionCharSet *, TransitionDescriptor> > >
                     super;
public:
  TransitionMap()
  : super(key_compare(), Alloc<std::pair<const ConstructionCharSet *, TransitionDescriptor> >(__FILE__, __LINE__))
  {}

  void consolidate(CharSets<const ConstructionCharSet> &transitionSets);
};

class TransitionsByDfaGroupLess
{
public:
  TransitionsByDfaGroupLess(DfaStates *d) : dfaStates(d) {}

  bool operator()(const DfaState *lhs, const DfaState *rhs) const;

private:
  DfaStates *dfaStates;
};

class TransitionsByDfaGroup : public std::map<const DfaState *, const ConstructionCharSet *, TransitionsByDfaGroupLess, Alloc<std::pair<const DfaState *, const ConstructionCharSet *> > >
{                            typedef std::map<const DfaState *, const ConstructionCharSet *, TransitionsByDfaGroupLess, Alloc<std::pair<const DfaState *, const ConstructionCharSet *> > >
                             super;
public:
  TransitionsByDfaGroup(DfaStates *d)
  : super(TransitionsByDfaGroupLess(d), Alloc<std::pair<const DfaState *, const ConstructionCharSet *> >(__FILE__, __LINE__))
  , dfaStates(d)
  {}

  bool operator<(const TransitionsByDfaGroup &rhs) const;
  void populate(DfaState *dfa, CharSets<const ConstructionCharSet> &transitionSets);

private:
  DfaStates *dfaStates;
};

struct AnnotationGreater
{
  bool operator()(const Annotation& lhs, const Annotation& rhs) const {return lhs > rhs;}
};

class AnnotationSet : private std::set<Annotation, AnnotationGreater, Alloc<Annotation> >
{                     typedef std::set<Annotation, AnnotationGreater, Alloc<Annotation> >
                      super;
public:
  AnnotationSet() : super(AnnotationGreater(), Alloc<Annotation>(__FILE__, __LINE__)) {}
  size_t size() const {return super::size();}
  bool empty() const {return super::empty();}
  typedef super::const_iterator const_iterator;
  const_iterator begin() const {return super::begin();}
  const_iterator end() const {return super::end();}
  size_t erase(const Annotation &a) {return super::erase(a);}
  bool insert(const Annotation &a) {return super::insert(a).second;}
  bool contains(const Annotation &a) const {return super::find(a) != super::end();}
};

class DfaState
{
  friend class DfaStates;

public:
                                /* character set having transitions */
                                /*    out of this state             */
  ConstructionCharSet alltransitions;

  BitSet *expectedTokenSet;

  Transition *transitions;      /* the list of transitions and      */
                                /*    final state marks             */
  AnnotationSet annotationSet;  /* the set of annotations (e.g.     */
                                /*    result descriptors of this    */
                                /*    state                         */
  DfaState *link;               /* state list links                 */

  TransitionMap tm;

  TransitionsByDfaGroup tb;

  NfaSet *nfaset;               /* the set of NFA states as created */
                                /*    by subset construction        */
  DfaState *group[2];           /* DFA group representatives for    */
                                /*    minimization algorithm        */
  bool regrouped;

  union
  {
    int location;               /* the position of this state in    */
                                /*    the table                     */
    NfaState *nfa;
  };

  int dfano;                    /* DFA state sequence no (start 1)  */
  size_t transitionSetCode;     /* transition code: made up of      */
                                /*    (single!) token code and      */
                                /*    context size recognized here  */
                                /*    (0 if none)                   */
                                /*    and the ordinal of the        */
                                /*    transition set (0 if none)    */
  size_t combinedTransitionCode;
  bool reachable;

  ~DfaState()
  {
    delete expectedTokenSet;

    Transition *t2 = 0;
    for (Transition *t1 = transitions; t1; t1 = t2)
    {
      t2 = t1->link;
      free(t1);
    }
    transitions = 0;
  }

private:
  DfaState(const DfaState &);
  const DfaState &operator=(const DfaState &);

  DfaState(DfaStates *s, int n, size_t cardinality, NfaSet *ns)
  : alltransitions(cardinality),
    expectedTokenSet(0),
    link(0),
    tb(s),
    regrouped(false),
    location(0),
    dfano(n),
    transitionSetCode(0),
    combinedTransitionCode(0),
    reachable(false)
  {
    transitions = 0;
    nfaset = ns;
    group[0] = this;
    group[1] = this;
  }
};

class DfaStateKey
{
public:
  DfaStateKey(NfaSet *s) : hash(s->hash()), nfaset(s) {}

  bool operator<(const DfaStateKey &rhs) const
  {
    if (hash < rhs.hash) return true;
    if (hash > rhs.hash) return false;
    return *nfaset < *rhs.nfaset;
  }

private:
  int hash;
  NfaSet *nfaset;
};

class DfaStates
{
public:
  DfaStates(entrylist *entries,
            bool minimize,
            bool ambiguities,
            TokenDescriptors &tokenDescriptors,
            int hightoken,
            const GrammarCharClasses *g,
            bool disambiguationDisabled);

  ~DfaStates()
  {
    for (DfaState *dfa = dfalist; dfa; )
    {
      DfaState *d = dfa->link;
      delete dfa;
      dfa = d;
    }
  }

  DfaState *first() const {return dfalist;}


  void renumber()
  {
    nofdfas = 0;

    for (DfaState *dfa = dfalist; dfa; dfa = dfa->link)
    {
      dfa->dfano = ++nofdfas;
    }
  }

  CharSets<const ConstructionCharSet> transitionSets;
  size_t currentgroup;

private:
  void subsetConstruction();
  void propagateExpectedTokenSets();
  void incorporatepreferences();
  void createLookaheadAnnotations();
  void dropNonResultAnnotations();
  void cutTransitionsFromNongreedy();
  void reach(DfaState *dfa);
  void removeDeadStates();
  void minimizeDfa();

  DfaState *insert(size_t cardinality, NfaSet *nfaset)
  {
    DfaStateKey k(nfaset);

    DfaByNfaSet::iterator i(states.find(k));
    if (i != states.end())
    {
      delete nfaset;
      return i->second;
    }
    else
    {
      DfaState *s = new DfaState(this, ++nofdfas, cardinality, nfaset);
      states.insert(DfaByNfaSet::value_type(k, s));
      if (dfaend == 0)
      {
        dfalist = s;
      }
      else
      {
        dfaend->link = s;
      }
      dfaend = s;
      dfaend->link = 0;

      return s;
    }
  }

  typedef std::map<DfaStateKey, DfaState *, std::less<DfaStateKey>, Alloc<std::pair<const DfaStateKey, DfaState *> > >
          DfaByNfaSet;

  DfaByNfaSet states;
  int nofdfas;
  DfaState *dfalist;
  DfaState *dfaend;
  bool ambiguities;
  entrylist *entries;
  bool minimize;
  const GrammarCharClasses &gcc;
  int maxfixedlength;
  TokenDescriptors &tokenDescriptors;
  int hightoken;
  bool disambiguationDisabled;
};

// DfaByAcceptanceBehavior

class DfaByAcceptanceBehavior
{
public:
  static void process(DfaStates &dfaStates, size_t currentgroup)
  {
    DfaByAcceptanceBehaviorKeySet dbab;

    for (DfaState *dfa = dfaStates.first(); dfa; dfa = dfa->link)
    {
      std::pair<DfaByAcceptanceBehaviorKeySet::iterator, bool> i(dbab.insert(DfaByAcceptanceBehaviorKey(dfa)));
      dfa->group[currentgroup] = i.first->dfa;
      dfa->group[1 - currentgroup] = 0;
    }
  }

private:
  class DfaByAcceptanceBehaviorKey
  {
  public:
    DfaByAcceptanceBehaviorKey(DfaState *d) : dfa(d) {}

    bool operator<(const DfaByAcceptanceBehaviorKey &rhs) const
    {
      AnnotationSet::const_iterator la =     dfa->annotationSet.begin();
      AnnotationSet::const_iterator lb = rhs.dfa->annotationSet.begin();

      while (   la !=     dfa->annotationSet.end()
             && lb != rhs.dfa->annotationSet.end())
      {
             if (*la > *lb) return true;
        else if (*lb > *la) return false;
        ++la;
        ++lb;
      }

      if (   la ==     dfa->annotationSet.end()
          && lb == rhs.dfa->annotationSet.end())
      {
        return ConstructionCharSet::compare(dfa->alltransitions, rhs.dfa->alltransitions) < 0;
      }
      else
      {
        return lb == rhs.dfa->annotationSet.end();
      }
    }

    DfaState *dfa;
  };

  class DfaByAcceptanceBehaviorKeySet : public std::set<DfaByAcceptanceBehaviorKey, std::less<DfaByAcceptanceBehaviorKey>, Alloc<DfaByAcceptanceBehaviorKey> >
  {                                    typedef std::set<DfaByAcceptanceBehaviorKey, std::less<DfaByAcceptanceBehaviorKey>, Alloc<DfaByAcceptanceBehaviorKey> >
                                       super;
  public:
    DfaByAcceptanceBehaviorKeySet()
    : super(std::less<DfaByAcceptanceBehaviorKey>(), Alloc<DfaByAcceptanceBehaviorKey>(__FILE__, __LINE__))
    {}
  };
};

// DfaByTransitionBehavior

class DfaByTransitionBehavior
{
public:
  static size_t process(DfaStates &dfaStates, size_t currentgroup)
  {
    DfaByTransitionBehaviorSet set(currentgroup);

    for (DfaState *dfa = dfaStates.first(); dfa; dfa = dfa->link)
    {
      if (dfa->tm.size() > 1)
      {
        for (TransitionMap::iterator i = dfa->tm.begin(); i != dfa->tm.end(); ++i)
        {
          DfaState *shift(i->second.shift);
          if (shift->regrouped)
          {
            dfa->tb.clear();
            dfa->tb.populate(dfa, dfaStates.transitionSets);
            break;
          }
        }
      }

      dfa->group[currentgroup] = *set.insert(dfa).first;
    }

    return set.size();
  }

private:
  class DfaByTransitionBehaviorLess
  {
  public:
    DfaByTransitionBehaviorLess(size_t g) : currentgroup(g) {}

    bool operator()(const DfaState *lhs, const DfaState *rhs) const
    {
      if (lhs->group[1 - currentgroup] < rhs->group[1 - currentgroup]) return true;
      if (lhs->group[1 - currentgroup] > rhs->group[1 - currentgroup]) return false;
      return lhs->tb < rhs->tb;
    }

  private:
    size_t currentgroup;
  };

  class DfaByTransitionBehaviorSet : public std::set<DfaState *, DfaByTransitionBehaviorLess, Alloc<DfaState *> >
  {                                 typedef std::set<DfaState *, DfaByTransitionBehaviorLess, Alloc<DfaState *> >
                                    super;
  public:
    DfaByTransitionBehaviorSet(size_t currentgroup)
    : super(DfaByTransitionBehaviorLess(currentgroup), Alloc<DfaState *>(__FILE__, __LINE__))
    {}
  };
};

// DfaByTransitionSet

//   this one is needed for reducing states to transition sets, i.e. neglecting
//   acceptance behaviour (which will be moved on to transition pointers by
//   table construction

class DfaByTransitionSet
{
public:
  static size_t process(DfaStates &dfaStates)
  {
    DfaByTransitionSetSet set;

    for (DfaState *dfa = dfaStates.first(); dfa; dfa = dfa->link)
    {
      if (! dfa->tb.empty())
      {
        std::pair<DfaByTransitionSetSet::iterator, bool> p(set.insert(dfa));
        if (p.second)
        {
          dfa->transitionSetCode = set.size();
        }
        else
        {
          dfa->transitionSetCode = (*p.first)->transitionSetCode;
        }
      }
    }

    return set.size();
  }

private:
  class DfaByTransitionSetLess
  {
  public:
    bool operator()(const DfaState *lhs, const DfaState *rhs) const
    {
      return lhs->tb < rhs->tb;
    }
  };

  class DfaByTransitionSetSet : public std::set<DfaState *, DfaByTransitionSetLess, Alloc<DfaState *> >
  {                            typedef std::set<DfaState *, DfaByTransitionSetLess, Alloc<DfaState *> >
                               super;
  public:
    DfaByTransitionSetSet()
    : super(DfaByTransitionSetLess(), Alloc<DfaState *>(__FILE__, __LINE__))
    {}
  };
};

#endif
