/*
 * CharSet.hpp
 *
 *  Created on: Apr 6, 2009
 *      Author: Gunther
 */
#ifndef CHARSET_HPP
#define CHARSET_HPP

#include "CharacterRange.hpp"

#include "../common/PtrLess.hpp"
#include "../common/Error.hpp"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <set>
#include <map>

class CharacterRangeSet : public std::set<CharacterRange, std::less<CharacterRange>, Alloc<CharacterRange> >
{                        typedef std::set<CharacterRange, std::less<CharacterRange>, Alloc<CharacterRange> >
                         super;
public:
  CharacterRangeSet()
  : super(key_compare(), Alloc<CharacterRange>(__FILE__, __LINE__))
  {}
};

template <class CHARSET>
class CharSetSet : public std::set<CHARSET *, PtrLess<CHARSET>, Alloc<CHARSET *> >
{                 typedef std::set<CHARSET *, PtrLess<CHARSET>, Alloc<CHARSET *> >
                          super;
public:
  CharSetSet()
  : super(PtrLess<CHARSET>(), Alloc<CHARSET *>(__FILE__, __LINE__))
  {}
};

class BitSet
{
public:

#define base_bits        (8 * sizeof(base_type))
#define base_items(bits) (((bits) + base_bits-1)/(base_bits))
#define base_size(type)  (sizeof(type) / sizeof(base_type))
#define base_word(bit)   ((bit)>>(5-(5-sizeof(base_type))/2))
#define base_bit(bit)    ((bit)&(base_bits-1))

  BitSet(size_t c) : card(c) {init();}
  BitSet(size_t c, const CharacterRange &cr) : card(c) {init(); *this += cr;}
  BitSet(const BitSet &other) : card(other.card) {init(); *this = other;}

  BitSet &operator=(const BitSet &rhs)
  {
    memcpy(data, rhs.data, baseSize * sizeof(base_type));
    return *this;
  }

  ~BitSet()
  {
    if (dynamic)
    {
      free(data);
    }
  }

  class CharIterator
  {
  public:
    CharIterator() : bcs(0), current(CNONE) {}

    CharIterator(const BitSet *b)
    : bcs(b),
      current(CNONE)
    {
      ++*this;
    }

    CharIterator &operator++()
    {
      current = bcs->cnxs(current);
      return *this;
    }

    bool operator==(const CharIterator &rhs) const
    {
      return current == rhs.current;
    }

    bool operator!=(const CharIterator &rhs) const
    {
      return current != rhs.current;
    }

    Character operator*() const
    {
      return current;
    }

  private:
    const BitSet *bcs;
    Character current;
  };

  CharIterator charBegin() const {return CharIterator(this);}
  CharIterator charEnd() const {return CharIterator();}

  enum {CNONE = -1};

  class RangeIterator
  {
  public:
    RangeIterator() : bcs(0), current(CNONE) {}

    RangeIterator(const BitSet *b)
    : bcs(b),
      current(CNONE)
    {
      ++*this;
    }

    RangeIterator &operator++()
    {
      Character low = bcs->cnxs(current.getHigh());
      Character high;
      if (low == CNONE)
      {
        high = CNONE;
      }
      else
      {
        high = bcs->cnxc(low);
        if (high == CNONE)
        {
          high = (Character) bcs->card;
        }
        --high;
      }
      current = CharacterRange(low, high);
      return *this;
    }

    bool operator==(const RangeIterator &rhs) const
    {
      return current == rhs.current;
    }

    bool operator!=(const RangeIterator &rhs) const
    {
      return current != rhs.current;
    }

    CharacterRange operator*() const
    {
      return current;
    }

    const CharacterRange *operator->() const
    {
      return &current;
    }

  private:
    const BitSet *bcs;
    CharacterRange current;
  };

  RangeIterator rangeBegin() const {return RangeIterator(this);}
  RangeIterator rangeEnd() const {return RangeIterator();}

  void clear()
  {
    memset(data, 0, baseSize * sizeof(base_type));
  }

  bool empty() const
  {
    for(size_t i = 0; i < baseSize; i++)
    {
      if (data[i]) return false;
    }
    return true;
  }

  typedef unsigned int base_type;

  bool operator==(const BitSet &rhs) const
  {
    return compare(*this, rhs) == 0;
  }

  bool operator!=(const BitSet &rhs) const
  {
    return compare(*this, rhs) != 0;
  }

  bool operator<(const BitSet &rhs) const
  {
    return compare(*this, rhs) < 0;
  }

  BitSet &operator+=(const BitSet &rhs)
  {
    for(size_t i = 0; i < baseSize; ++i)
    {
      data[i] |= rhs.data[i];
    }
    return *this;
  }

  BitSet &operator+=(const CharacterRange &rhs)
  {
#if ASSERTIONS
    if (rhs.getHigh() >= (int) card)
    {
      internalerr();
    }
#endif

    for (Character c = rhs.getLow(); c <= rhs.getHigh(); ++c)
    {
      data[base_word(c)] |= 1 << base_bit(c);
    }
    return *this;
  }

  BitSet &operator-=(const BitSet &rhs)
  {
    for(size_t i = 0; i < baseSize; ++i)
    {
      data[i] &= ~ rhs.data[i];
    }
    return *this;
  }

  BitSet &operator-=(const CharacterRange &rhs)
  {
    for (Character c = rhs.getLow(); c <= rhs.getHigh(); ++c)
    {
      data[base_word(c)] &= ~ (base_type) (1 << base_bit(c));
    }
    return *this;
  }

  bool ctst(Character c) const
  {
#if ASSERTIONS
    if (c >= (int) card)
    {
      internalerr();
    }
#endif

    return (data[base_word(c)] & (1 << base_bit(c))) != 0;
  }

  Character cnxc(Character c) const
  {
    for (++c; c < (Character) card; ++c)
    {
/*
      if ((c & (base_bits - 1)) == 0 && data[base_word(c)] == ~ (base_type) 0)
      {
        c += base_bits - 1;
      }
*/
      if ((data[base_word(c)] & (1 << base_bit(c))) == 0)
      {
        return c;
      }
    }
    return CNONE;
  }

  Character cnxs(Character c = CNONE) const
  {
#if 1
    ++c;
    base_type b(1 << base_bit(c));
    for (size_t w(base_word(c));  c < (Character) card; ++w)
    {
      if ((data[w] & ~ (b - 1)) == 0)
      {
        c = (Character) ((w + 1) * base_bits);
      }
      else
      {
        do
        {
          if (data[w] & b) return c;
          ++c;
          b <<= 1;
        }
        while (b);
      }
      b = 1;
    }
    return CNONE;

#else
    for (++c; c < (Character) card; ++c)
    {
/*
      if ((c & (base_bits - 1)) == 0 && data[base_word(c)] == 0)
      {
        c += base_bits - 1;
      }
*/
      if ((data[base_word(c)] & (1 << base_bit(c))) != 0)
      {
        return c;
      }
    }
    return CNONE;
#endif
  }

  void cand(const BitSet &s)
  {
    for(size_t _i = 0; _i < baseSize; _i++)
    {
      data[_i] &= s.data[_i];
    }
  }

  static int compare(const BitSet &lhs, const BitSet &rhs)
  {
#if 1
    // TODO: this code puts the set containing 0 last, which might not be necessary

    Character c1(lhs.cnxs());
    Character c2(rhs.cnxs());

    if (c1 == 0) c1 = CHARACTER_MAX;
    if (c2 == 0) c2 = CHARACTER_MAX;

    if (c1 < c2)
    {
      return -1;
    }
    else if (c2 < c1)
    {
      return 1;
    }
    else
#endif
    {
      return memcmp(lhs.data, rhs.data, lhs.baseSize * sizeof(base_type));
    }
  }

  static int csub(const BitSet &a, const BitSet &b)
  {
    size_t i = a.baseSize;
    do
    {
      if (! i)
        return 3;
      --i;
    }
    while (a.data[i] == b.data[i]);

    if (a.data[i] < b.data[i])
      while ((a.data[i] | b.data[i]) == b.data[i])
        do
        {
          if (! i)
            return 2;
          --i;
        }
        while (a.data[i] == b.data[i]);
    else
      while ((a.data[i] | b.data[i]) == a.data[i])
        do
        {
          if (! i)
            return 1;
          --i;
        }
        while (a.data[i] == b.data[i]);
    return 0;
  }

  int getHashCode() const
  {
    int hashCode = 0;
    for(size_t i = 0; i < baseSize; i++)
    {
      hashCode ^= data[i];
    }
    return hashCode;
  }

  size_t getBaseSize() const {return baseSize;}
  const base_type *getData() const {return data;}
  size_t cardinality() const {return card;}

  enum {STATIC_BASE_SIZE = 4};

private:
  void init()
  {
    baseSize = base_items(card);

    if (baseSize <= STATIC_BASE_SIZE)
    {
      data = baseData;
      dynamic = false;
    }
    else
    {
      data = ALLOCATE_ARRAY(base_type, baseSize);
      dynamic = true;
    }
    clear();
  }

  const size_t card;
  size_t baseSize;
  bool dynamic;
  base_type baseData[STATIC_BASE_SIZE];
  base_type *data;
};

class RangeCharSet : private CharacterRangeSet
{                    typedef CharacterRangeSet
                             super;
public:
  RangeCharSet() : converted(0) {}
  RangeCharSet(const CharacterRange &cr) : converted(0) {*this += cr;}
  RangeCharSet(const RangeCharSet &other) : super(other), converted(0) {}

  ~RangeCharSet()
  {
    clear();
    delete converted;
  }

  RangeCharSet &operator=(const RangeCharSet &rhs)
  {
    super::operator=(rhs);
    converted = 0;
    return *this;
  }

  typedef const_iterator RangeIterator;
  RangeIterator rangeBegin() const {return begin();}
  RangeIterator rangeEnd() const {return end();}

  class CharIterator
  {
  public:
    CharIterator(const RangeIterator &c, const RangeIterator &e)
    : currentIterator(c),
      endIterator(e),
      currentRange(0)
    {
      if (currentIterator != endIterator)
      {
        currentRange = *currentIterator;
      }
      current = currentRange.getLow();
    }

    CharIterator &operator++()
    {
      if (current != currentRange.getHigh())
      {
        ++current;
      }
      else
      {
        ++currentIterator;
        if (currentIterator != endIterator)
        {
          currentRange = *currentIterator;
          current = currentRange.getLow();
        }
        else
        {
          current = 0;
        }
      }
      return *this;
    }

    bool operator==(const CharIterator &rhs) const
    {
      return current == rhs.current && currentIterator == rhs.currentIterator;
    }

    bool operator!=(const CharIterator &rhs) const
    {
      return current != rhs.current || currentIterator != rhs.currentIterator;
    }

    Character operator*() const
    {
      return current;
    }

  private:
    RangeIterator currentIterator;
    RangeIterator endIterator;
    CharacterRange currentRange;
    Character current;
  };

  CharIterator charBegin() const {return CharIterator(rangeBegin(), rangeEnd());}
  CharIterator charEnd() const {return CharIterator(rangeEnd(), rangeEnd());}

  void clear()
  {
    super::clear();
  }

  bool empty() const
  {
    return super::empty();
  }

  RangeCharSet &operator+=(const RangeCharSet &rhs)
  {
    for (RangeIterator i = rhs.rangeBegin(); i != rhs.rangeEnd(); ++i)
    {
      *this += *i;
    }
    return *this;
  }

  RangeCharSet &operator+=(const CharacterRange &cr)
  {
    std::pair<iterator, bool> i = insert(cr);
    if (i.second)
    {
      CharacterRange adjusted(cr);

      iterator left(i.first);
      if (   i.first != begin()
          && (cr.overlaps(*--left) || left->adjacent(cr)))
      {
        adjusted = CharacterRange(left->getLow(),
                               left->getHigh() > adjusted.getHigh()
                             ? left->getHigh()
                             : adjusted.getHigh()
                            );
        erase(left);
      }

      iterator right(i.first);
      for (++right;
              right != end()
           && (cr.overlaps(*right) || cr.adjacent(*right));
          )
      {
        iterator next(right);
        ++next;
        adjusted = CharacterRange(adjusted.getLow(),
                               right->getHigh() > adjusted.getHigh()
                             ? right->getHigh()
                             : adjusted.getHigh()
                            );
        erase(right);
        right = next;
      }

      if (adjusted != cr)
      {
        erase(i.first);
        insert(adjusted);
      }
    }
    return *this;
  }

  RangeCharSet &operator-=(const RangeCharSet &rhs)
  {
    iterator l(begin());
    const_iterator r(rhs.begin());
    while (l != end() && r != rhs.end())
    {
      if (l->overlaps(*r))
      {
        Character low(l->getLow());
        Character high(l->getHigh());
        iterator next(l);
        ++next;
        erase(l);
        l = next;
        if (low < r->getLow())
        {
          l = insert(CharacterRange(low, r->getLow() - 1)).first;
          ++l;
        }
        if (r->getHigh() < high)
        {
          l = insert(CharacterRange(r->getHigh() + 1, high)).first;
          ++r;
        }
      }
      else if (*l < *r)
      {
        ++l;
      }
      else
      {
        ++r;
      }
    }
    return *this;
  }

  RangeCharSet &operator-=(const CharacterRange &cr)
  {
    iterator l(begin());
    while (l != end())
    {
      if (l->overlaps(cr))
      {
        Character low(l->getLow());
        Character high(l->getHigh());
        iterator next(l);
        ++next;
        erase(l);
        l = next;
        if (low < cr.getLow())
        {
          l = insert(CharacterRange(low, cr.getLow() - 1)).first;
          ++l;
        }
        if (cr.getHigh() < high)
        {
          l = insert(CharacterRange(cr.getHigh() + 1, high)).first;
          break;
        }
      }
      else if (*l < cr)
      {
        ++l;
      }
      else
      {
        break;
      }
    }
    return *this;
  }

  bool operator<(const RangeCharSet &rhs) const
  {
    return compare(*this, rhs) < 0;
  }

  bool operator!=(const RangeCharSet &rhs) const
  {
    return compare(*this, rhs) != 0;
  }

  bool operator==(const RangeCharSet &rhs) const
  {
    return compare(*this, rhs) == 0;
  }

  bool ctst(Character c) const
  {
    if (empty()) return false;
    for (const_iterator i(begin()); i != end(); ++i)
    {
      if (c <= i->getHigh())
      {
        return i->getLow() <= c;
      }
    }
    return false;
  }

  void cand(const RangeCharSet &rhs)
  {
    iterator l(begin());
    const_iterator r(rhs.begin());
    while (l != end() && r != rhs.end())
    {
      if (*l == *r)
      {
        ++l;
        ++r;
      }
      else if (l->overlaps(*r))
      {
        Character low(l->getLow());
        Character high(l->getHigh());
        iterator next(l);
        ++next;
        erase(l);
        l = next;

        if (low < r->getLow())
        {
          low = r->getLow();
        }
        if (high <= r->getHigh())
        {
          l = insert(CharacterRange(low, high)).first;
          ++l;
        }
        else
        {
          insert(CharacterRange(low, r->getHigh()));
          l = insert(CharacterRange(r->getHigh() + 1, high)).first;
          ++r;
        }
      }
      else if (*l < *r)
      {
        iterator next(l);
        ++next;
        erase(l);
        l = next;
      }
      else
      {
        ++r;
      }
    }
    while (l != end())
    {
      iterator next(l);
      ++next;
      erase(l);
      l = next;
    }
  }

  static int compare(const RangeCharSet &lhs, const RangeCharSet &rhs)
  {
    RangeIterator r(rhs.rangeBegin());
    for (RangeIterator l(lhs.rangeBegin()); l != lhs.rangeEnd(); ++l)
    {
      if (r == rhs.rangeEnd())
      {
        return 1;
      }
      const CharacterRange &lr(*l);
      const CharacterRange &rr(*r);
      if (lr.getLow() < rr.getLow()) return -1;
      if (lr.getLow() > rr.getLow()) return 1;
      if (lr.getHigh() < rr.getHigh()) return -1;
      if (lr.getHigh() > rr.getHigh()) return 1;
      ++r;
    }
    return r == rhs.rangeEnd() ? 0 : -1;
  }

  const BitSet *getConverted() const {return converted;}
  void setConverted(const BitSet &b) {converted = new BitSet(b);}

private:
  BitSet *converted;
};

typedef RangeCharSet GrammarCharSet;
typedef BitSet ConstructionCharSet;

template <class CHARSET>
class CharSets : private CharSetSet<CHARSET>
{                typedef CharSetSet<CHARSET>
                         super;
public:
  ~CharSets()
  {
    clear();
  }

  typedef typename super::const_iterator const_iterator;
  const_iterator begin() const {return super::begin();}
  const_iterator end() const {return super::end();}

  void clear()
  {
    for (typename super::iterator i(super::begin()); i != super::end(); ++i)
    {
      delete *i;
    }
    super::clear();
  }

  size_t size() const {return super::size();}

  CHARSET *insert(CHARSET &ccs)
  {
    typename super::iterator i(super::find(&ccs));
    if (i != super::end())
    {
      return *i;
    }
    else
    {
      CHARSET *p = new CHARSET(ccs);
      super::insert(p);
      return p;
    }
  }
};

class GrammarCharSets : public CharSets<const GrammarCharSet>
{
public:
  GrammarCharSet EMPTY;
};

#endif
