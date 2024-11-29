/*
 * Nfa.hpp
 *
 *  Created on: 09.04.2009
 *      Author: Gunther
 */

#ifndef NFA_HPP
#define NFA_HPP

#include "CharSet.hpp"
#include "SymbolTable.hpp"
#include "Syntax.hpp"

#include "../common/Error.hpp"
#include "../common/Math.hpp"

enum NfaType                      /* determines the kind of NFA state */
{
  fork,                           /* alternative epsilon transitions  */
  settrans,                       /* one non-epsilon set transition   */
  final                           /* final state                      */
};

enum LookaheadType {NOLOOKAHEAD, FIXEDTOKENLENGTH, FIXEDLOOKAHEADLENGTH};
enum AnnotationType {FINAL, NEGATING, WITHINTOKEN, TOKENCOMPLETED, WITHINLOOKAHEAD};

class Annotation
{
public:
  Annotation(TokenId i, AnnotationType s, LookaheadType l, int f = 0)
  : id(i), fixedlength(f), annotationType(s), lookaheadtype(l)
  {}

  bool operator>(const Annotation &rhs) const
  {
    if (id > rhs.id) return true;
    if (rhs.id > id) return false;
    if (fixedlength > rhs.fixedlength) return true;
    if (rhs.fixedlength > fixedlength) return false;
    if (annotationType > rhs.annotationType) return true;
    if (rhs.annotationType > annotationType) return false;
    return lookaheadtype > rhs.lookaheadtype;
  }

  bool operator!=(const Annotation &rhs) const
  {
    return *this > rhs || rhs > *this;
  }

  TokenId getId() const {return id;}
  AnnotationType getAnnotationType() const {return annotationType;}
  LookaheadType getLookaheadType() const {return lookaheadtype;}
  int getFixedlength() const {return fixedlength;}

private:
  TokenId id;                           /*   assigned token code          */
  int fixedlength;                      /*   length of token or lookahead */
  AnnotationType annotationType;
  LookaheadType lookaheadtype;          /*   true if token has lookahead  */
};

class NfaState
{
public:
  bool operator<(const NfaState &rhs) const
  {
    return nfano < rhs.nfano;
  }

  int nfano;                      /* ordinal of this object         */
  int tag;                        /* graph visiting tag             */
  NfaState *shift;                /* state reached or initial state */
  NfaType kind;
  union
  {
                                  /* case Fork                      */
    NfaState *two;                /*   alternate follower state     */
                                  /* case SetTrans                  */
    const GrammarCharSet *on;     /*   character set for transition */
                                  /* case CharTrans                 */
  } u;
  Annotation annotation;
};

#endif
