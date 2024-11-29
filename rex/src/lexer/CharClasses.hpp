
/*
 * CharClasses.h
 *
 *  Created on: 19.04.2009
 *      Author: Gunther
 */

#ifndef CHARCLASSES_HPP
#define CHARCLASSES_HPP

#include <stdlib.h>
#include <stdio.h>
#include <map>
#include "CharSet.hpp"

class Classifier : public std::map<CharacterRange, Character, std::less<CharacterRange>, Alloc<std::pair<const CharacterRange, Character> > >
{                 typedef std::map<CharacterRange, Character, std::less<CharacterRange>, Alloc<std::pair<const CharacterRange, Character> > >
                  super;
public:
  Classifier()
  : super(key_compare(), Alloc<std::pair<const CharacterRange, Character> >(__FILE__, __LINE__))
  {}
};

template <class CHARSET>
class Classification : public std::map<const CHARSET *, CHARSET *, std::less<const CHARSET *>, Alloc<std::pair<const CHARSET *, CHARSET *> > >
{                     typedef std::map<const CHARSET *, CHARSET *, std::less<const CHARSET *>, Alloc<std::pair<const CHARSET *, CHARSET *> > >
                      super;
public:
  Classification()
  : super(std::less<const CHARSET *>(), Alloc<std::pair<const CHARSET *, CHARSET *> >(__FILE__, __LINE__))
  {}
};

template <class CHARSET>
class CharClasses : private CharSets<const CHARSET>
{                   typedef CharSets<const CHARSET>
                            super;
public:
  CharClasses() : classes(0), nclasses(0) {clear();}
  virtual ~CharClasses() {clear();}

  void clear()
  {
    for (size_t i = 0; i < nclasses; ++i)
    {
      delete classes[i].characters;
    }

    free(classes);
    classes = 0;
    nclasses = 0;

    allocatedclasses = 0;
    maxClassId = -1;
    classifier.clear();

    for (typename Classification<CHARSET>::iterator i = classification.begin(); i != classification.end(); ++i)
    {
      delete i->second;
    }
    classification.clear();

    super::clear();
  }

  const CHARSET *submit(const CHARSET &ccs) {return super::insert(ccs);}

  class Clazz
  {
  public:
    CHARSET *characters;
    int id;
  };

  class const_iterator
  {
  public:
    const Clazz &operator*() const {return cc->classes[ii];}
    const_iterator operator++() {++ii; return *this;}
    bool operator!=(const_iterator &rhs) const {return ii != rhs.ii;}
    const_iterator(const CharClasses *c, size_t i) : cc(c), ii(i) {}
  private:
    const CharClasses *cc;
    size_t ii;
  };

  const_iterator begin() const {return const_iterator(this, 0);}
  const_iterator end() const {return const_iterator(this, nclasses);}

  size_t count() const {return nclasses;}

  int nonCharacterId() const {return 0;}
  int maxId() const {return maxClassId;}

  /*
  * compute equivalence classes
  *
  * the relation between a transition set and an equivalence class
  * must be such that a class is either fully contained in a set
  * or it is disjoint from the set. Calculate the classes as follows:
  *
  * (0) initialize classes to a single class containing all characters
  * (1) repeat steps (2) thru (8) for all dfa states
  * (2)   repeat steps (3) thru (8) for all transition sets of dfa
  * (3)     copy transition set into divisor
  * (4)     repeat steps (5) thru (8) for all classes
  * (5)       if intersection of class and divisor is empty, proceed to next class
  * (6)       if intersection is different from class, create a new class for
  *           intersection and remove intersection from class
  * (7)       remove intersection from divisor
  * (8)       if divisor is empty, proceed to next set (step (3))
  *
  */

  void arrange(bool representEmptySet)
  {
    for (typename super::const_iterator i = super::begin();
         i != super::end();
         ++i)
    {
      CHARSET divisor(**i);
      fold(divisor);

      for (size_t j = 0; j < nclasses; j++)
      {
        CHARSET intersection(*classes[j].characters);
        intersection.cand(divisor);

        if (! intersection.empty()) /* some common elements */
        {
          fold(intersection);
          if (intersection != *classes[j].characters)
          {
            moreClasses(intersection);

            CHARSET remainder(*classes[j].characters);
            remainder -= intersection;
            *classes[j].characters = remainder;
          }
          divisor -= intersection;
          if (divisor.empty()) /* all done */
          {
            break;
          }
        }
      }

      if (! divisor.empty())
      {
        // enlarge alphabet

        fold(divisor);
        moreClasses(divisor);
      }

      if (representEmptySet)
      {
        divisor.clear();
        moreClasses(divisor);
        representEmptySet = false;
      }
    }

//  printf("          Number of character classes: %d\n", nclasses);

    qsort(classes, nclasses, sizeof classes[0], compareClasses);

    for (Character i = 0; i < (Character) nclasses; ++i)
    {
      const CHARSET *set = classes[i].characters;
      for (typename CHARSET::RangeIterator j = set->rangeBegin(); j != set->rangeEnd(); ++j)
      {
        classifier.insert(Classifier::value_type(*j, i));
      }
    }

//  printf("          Number of distinct character ranges: %d\n", classifier.size());

    maxClassId = -1;

    for (size_t i = 0; i < nclasses; ++i)
    {
        classes[i].id = ++maxClassId;
    }
  }

  template <class INPUTCHARSET>
  void declassify(const INPUTCHARSET &inputCharset, CHARSET &outputCharset) const
  {
    for (typename INPUTCHARSET::CharIterator i = inputCharset.charBegin();
         i != inputCharset.charEnd();
         ++i)
    {
      Character clas(*i);
      const CHARSET *cs(classes[clas].characters);
      for (typename CHARSET::RangeIterator j(cs->rangeBegin());
           j != cs->rangeEnd();
           ++j)
      {
        outputCharset += *j;
      }
    }
  }

  template <class OUTPUTCHARSET>
  void classify(const CHARSET &inputCharset, OUTPUTCHARSET &outputCharset) const
  {
    Character lastClass = -1;

    for (typename CHARSET::RangeIterator i = inputCharset.rangeBegin();
         i != inputCharset.rangeEnd();
         ++i)
    {
      CharacterRange cr(*i);

      for (Character c = cr.getLow(); c <= cr.getHigh(); )
      {
        Character clas;

        Classifier::const_iterator j(classifier.lower_bound(c));
        if (j == classifier.end())
        {
          Classifier::const_reverse_iterator k(classifier.rbegin());
          c = k->first.getHigh() + 1;
          clas = k->second;
        }
        else
        {
          if (c < j->first.getLow())
          {
            --j;
          }
          c = j->first.getHigh() + 1;
          clas = j->second;
        }

        if (clas != lastClass)
        {
          outputCharset += CharacterRange(clas);
          lastClass = clas;
        }
      }
    }
  }

  const CHARSET *classify(const CHARSET *unclassified)
  {
    typename Classification<CHARSET>::iterator i(classification.find(unclassified));
    if (i != classification.end())
    {
      return i->second;
    }
    else
    {
      CHARSET classified(unclassified->cardinality());
      classify(*unclassified, classified);
      typename Classification<CHARSET>::value_type v(unclassified, new CHARSET(classified));
      classification.insert(v);
      return v.second;
    }
  }

private:
  void moreClasses(const CHARSET &characters)
  {
    if (nclasses == allocatedclasses)
    {
      allocatedclasses = allocatedclasses ? allocatedclasses * 2 : 64;
      classes = REALLOCATE_ARRAY(Clazz, classes, allocatedclasses);
    }

    classes[nclasses].characters = new CHARSET(characters);
    nclasses++;
  }

  static int compareClasses(const void *v1, const void *v2)
  {
    const CHARSET &cs1(*static_cast<const Clazz *> (v1)->characters);
    const CHARSET &cs2(*static_cast<const Clazz *> (v2)->characters);
    return CHARSET::compare(cs1, cs2);
  }

  virtual void fold(CHARSET &characters) {}

  Clazz *classes;
  size_t nclasses;
  size_t allocatedclasses;

  Classifier classifier;

  Classification<CHARSET> classification;

  int maxClassId;
};

class CharFolder
{
public:
  CharFolder() {}
  CharFolder(const CharacterRange &a, const CharacterRange &b) {add(a, b);}
  CharFolder(const Character &c, const Character &d) {add(c, d);}

  void add(const CharacterRange &a, const CharacterRange &b)
  {
    if (a.size() != b.size())
    {
      internalerr();
    }

    for (size_t i = 0; i < a.size(); ++i)
    {
      add(a.getLow() + i, b.getLow() + i);
    }
  }

  void add(const Character &c, const Character &d)
  {
    foldingMap.insert(std::pair<Character, Character>(c, d));
    foldingMap.insert(std::pair<Character, Character>(d, c));
    foldingChars += CharacterRange(c);
    foldingChars += CharacterRange(d);
  }

  void fold(GrammarCharSet &characters)
  {
    if (! foldingChars.empty())
    {
      GrammarCharSet foldedChars(foldingChars);
      foldedChars.cand(characters);
      if (! foldedChars.empty())
      {
        for (GrammarCharSet::CharIterator i = foldedChars.charBegin(); i != foldedChars.charEnd(); ++i)
        {
          for (FoldingMap::iterator j = foldingMap.find(*i);
               j != foldingMap.end() && j->first == *i;
               ++j)
          {
            characters += CharacterRange(j->second);

//          wprintf(L" - augmenting %c with %c\n", *i, j->second);
          }
        }
      }
    }
  }

  GrammarCharSet foldingChars;
  typedef std::multimap<Character, Character> FoldingMap;
  FoldingMap foldingMap;
};

class GrammarCharClasses : public CharClasses<GrammarCharSet>
{
public:
  GrammarCharClasses(CharFolder *f) : folder(f) {}

  const GrammarCharSet EMPTY;

private:
  void fold(GrammarCharSet &characters)
  {
    if (folder)
    {
      folder->fold(characters);
    }
  }

  CharFolder *folder;
};

#endif
