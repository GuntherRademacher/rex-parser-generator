/*
 * TokenSet.hpp
 *
 *  Created on: 18.08.2008
 *      Author: Gunther
 */

#ifndef TOKENSET_HPP_
#define TOKENSET_HPP_

#include "Exceptions.hpp"
#include "TokenSequence.hpp"

#include "../common/PtrLess.hpp"
#include "../common/Error.hpp"

#include <map>
#include <set>
#include <iterator>
#include <algorithm>
#include <stdlib.h>

class Grammar;
class WcsSet;
class TokenSequenceSet;

class TokenSequenceSetAccessor
{
public:
  virtual ~TokenSequenceSetAccessor() {}
  virtual const TokenSequenceSet *get() const = 0;
  virtual const TokenSequenceSet *get(size_t k) const = 0;
};

class TokenSequenceSet : public TokenSequenceSetAccessor
{
private:
  typedef std::set<TokenSequence, std::less<TokenSequence>, Alloc<TokenSequence> > Set;
  Set *dynamic;

public:
  TokenSequenceSet(const char *file = __FILE__, int line = __LINE__);
  TokenSequenceSet(const TokenSequence &cs, const char *file = __FILE__, int line = __LINE__);
  TokenSequenceSet(const TokenSequenceSet &tss, const char *file = __FILE__, int line = __LINE__);
  TokenSequenceSet(const TokenSequenceSet *tss, const char *file = __FILE__, int line = __LINE__);

  bool empty() const;
  size_t size() const;
  bool contains(const TokenSequence &token) const;
  void insertAll(const TokenSequenceSet &ts);
  void insertIntersectionOf(const TokenSequenceSet &ts1, const TokenSequenceSet &ts2);
  void insertDifferenceOf(const TokenSequenceSet &ts1, const TokenSequenceSet &ts2);
  void insertFirstKOf(const TokenSequenceSet &tss, const size_t &k);
  void insertIfNotEndsWith(const TokenSequenceSet &tss, Token::Code code);
  void insertUpsized(const TokenSequenceSet &lhs, const TokenSequenceSetAccessor &rhs, size_t k, TokenSequenceFactory *tokenSequenceFactory);
  bool operator!=(const TokenSequenceSet &rhs) const;
  bool operator<(const TokenSequenceSet &rhs) const;
  const TokenSequenceSet *get() const {return this;}
  const TokenSequenceSet *get(size_t k) const {return this;}
  WString toString(Grammar *grammar,
                   const wchar_t *linePrefix,
                   const wchar_t *separator,
                   size_t width,
                   size_t trailerWidth,
                   bool showCodes,
                   WcsSet *toBeEscaped = 0) const;

  size_t getPass() const {return pass;}
  void setPass(size_t pass) {this->pass = pass;}
  bool isInProgress() const {return inProgress;}
  void setInProgress(bool inProgress) {this->inProgress = inProgress;}
  bool isCollected() const {return collected;}

  class iterator
  {
  public:
    bool operator==(const iterator& rhs) const;
    bool operator!=(const iterator& rhs) const;
    const TokenSequence &operator*() const;
    const TokenSequence *operator->() const;
    iterator &operator++();
    iterator operator++(int);

    typedef std::forward_iterator_tag iterator_category;
    typedef TokenSequence value_type;
    typedef size_t difference_type;
    typedef TokenSequence &reference;
    typedef TokenSequence *pointer;

  private:
    friend class TokenSequenceSet;
    iterator(Set::const_iterator aDynamicI) : dynamicI(aDynamicI), staticI(0) {}
    iterator(TokenSequence *staticI) : staticI(staticI) {}

    Set::const_iterator dynamicI;
    TokenSequence *staticI;
  };

  typedef iterator const_iterator;
  iterator begin() const;
  iterator end() const;
  std::pair<iterator, bool> insert(const TokenSequence &ts);

  virtual ~TokenSequenceSet()
  {
    delete dynamic;
    free(staticBegin);
  }

  void clear()
  {
    dynamic->clear();
  }

  size_t erase(const TokenSequence& ts)
  {
    return dynamic->erase(ts);
  }

  void erase(iterator i)
  {
    dynamic->erase(i.dynamicI);
  }

private:
  friend class TokenSequenceSets;
  TokenSequenceSet &operator=(const TokenSequenceSet &rhs) {internalerr(); return *this;}

  TokenSequence *staticBegin;
  TokenSequence *staticEnd;

  size_t pass;
  bool inProgress;
  bool collected;
};

#endif
