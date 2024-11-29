/*
 * TokenSequence.hpp
 *
 *  Created on: Mar 19, 2009
 *      Author: Gunther
 */

#ifndef TOKENSEQUENCE_HPP_
#define TOKENSEQUENCE_HPP_

#include "Token.hpp"
#include "../common/Math.hpp"
#include "../common/WString.hpp"

class Grammar;

class TokenSequence
{
public:
  class TokenSequenceImpl
  {
  public:
    TokenSequenceImpl(short n, Token::Code c, TokenSequenceImpl *p)
    : predecessor(p), follower(0), k(n), code(c)
    {}

    ~TokenSequenceImpl()
    {
      if (follower)
      {
        for (int i = 0; i <= k; ++i)
        {
          if (follower[i].tsi)
          {
            follower[i].tsi->k = k;
            delete follower[i].tsi;
          }
        }
        free(follower);
      }
    }

    TokenSequenceImpl *predecessor;
    TokenSequence *follower;
    short k;
    Token::Code code;
  };

  class Order
  {
  public:
    bool operator()(const TokenSequence &lhs, const TokenSequence &rhs) const
    {
      const TokenSequenceImpl *l = lhs.tsi;
      const TokenSequenceImpl *r = rhs.tsi;

      if (l->k < r->k)
      {
        return true;
      }
      else if (l->k > r->k)
      {
        return false;
      }
      else while (l->code)
      {
        if (l->code < r->code) return true;
        if (l->code > r->code) return false;
        l = l->predecessor;
        r = r->predecessor;
      }
      return false;
    }
  };

  size_t size() const {return tsi->k;}
  bool empty() const {return tsi->k == 0;}
  bool operator==(const TokenSequence &rhs) const {return tsi == rhs.tsi;}
  bool operator<(const TokenSequence &rhs) const
  {
    return tsi < rhs.tsi;
  }

  Token::Code operator[](int i) const
  {
    if (i >= tsi->k)
    {
      return Token::eEPSILON;
    }
    else
    {
      const TokenSequenceImpl *t = tsi;
      while (t->k > i + 1) t = t->predecessor;
      return t->code;
    }
  }

  Token::Code first() const
  {
    const TokenSequenceImpl *t = tsi;
    while (t->k > 1) t = t->predecessor;
    return t->code;
  }

  TokenSequence first(size_t k) const
  {
    TokenSequenceImpl *t = tsi;
    while (t->k > static_cast<short>(k)) t = t->predecessor;
    return TokenSequence(t);
  }

  Token::Code last() const {return tsi->code;}

  WString toString(Grammar *grammar) const;

  static TokenSequence VOID;

private:
  friend class TokenSequenceFactory;

  TokenSequence(TokenSequenceImpl *t) : tsi(t) {}

  TokenSequenceImpl *tsi;
};

class TokenSequenceFactory
{
public:
  TokenSequenceFactory(Token::Code m)
  : maxTokenCode(m),
    bits(Math::log2(maxTokenCode) + 1),
    EPSILON(new TokenSequence::TokenSequenceImpl(0, Token::eEPSILON, 0)),
    code(0),
    codeSize(0)
  {
    const_cast<TokenSequence::TokenSequenceImpl *>(EPSILON.tsi)->follower =
      ALLOCATE_ARRAY(TokenSequence, maxTokenCode + 1);

    for (Token::Code t = 0; t <= maxTokenCode; ++t)
    {
      const_cast<TokenSequence::TokenSequenceImpl *>(EPSILON.tsi)->follower[t] =
          new TokenSequence::TokenSequenceImpl(1, t, const_cast<TokenSequence::TokenSequenceImpl *>(EPSILON.tsi));
    }
  }

  ~TokenSequenceFactory()
  {
    EPSILON.tsi->k = maxTokenCode;
    delete EPSILON.tsi;
    free(code);
  }

  int tokenBits() const {return bits;}

  const TokenSequence &emptySequence() const {return EPSILON;}

  /**
   * TokenSequence from Token::Code
   */
  const TokenSequence &tokenSequence(const Token::Code &code) const
  {
    return code
         ? EPSILON.tsi->follower[code]
         : EPSILON;
  }

  /**
   * Concatenated TokenSequence
   */
  const TokenSequence &tokenSequence(const TokenSequence &a, const TokenSequence &b)
  {
    return a == EPSILON
         ? b
         : b == EPSILON
         ? a
         : extend(a, b.tsi, b.tsi->k);
  }

  /**
   * TokenSequence subsequence starting at offset 'begin'.
   */
  const TokenSequence &tokenSequence(const TokenSequence &a, int begin)
  {
    return begin == 0
         ? a
         : begin >= a.tsi->k
         ? EPSILON
         : extend(EPSILON, a.tsi, a.tsi->k - begin);
  }

  /**
   * TokenSequence subsequence starting at offset 'begin', covering 'length' items
   * (or less, if the original sequence is shorter than 'length' - 'begin').
   */
  const TokenSequence tokenSequence(const TokenSequence &a, int begin, size_t k)
  {
    if (begin != 0)
    {
      return tokenSequence(tokenSequence(a, begin), 0, k);
    }
    else if ((short) k >= a.tsi->k)
    {
      return a;
    }
    else
    {
      TokenSequence::TokenSequenceImpl *api = const_cast<TokenSequence *> (&a)->tsi;
      while (api->k > (short) k)
      {
        api = api->predecessor;
      }
      return TokenSequence(api);
    }
  }

private:
  const TokenSequence &extend(const TokenSequence &a, const TokenSequence::TokenSequenceImpl *bi, int n)
  {
    if (codeSize < n)
    {
      codeSize = n;
      code = REALLOCATE_ARRAY(int, code, codeSize);
    }

    for (int i = n - 1; i >= 0; --i)
    {
      code[i] = bi->code;
      bi = bi->predecessor;
    }

    TokenSequence *ap = const_cast<TokenSequence *> (&a);
    for (int i = 0; i < n; ++i)
    {
      TokenSequence::TokenSequenceImpl *api = ap->tsi;
      if (api->follower == 0)
      {
        api->follower = ALLOCATE_ARRAY(TokenSequence, maxTokenCode + 1);
        for (int j = 0; j <= maxTokenCode; ++j) api->follower[j] = 0;
      }

      TokenSequence &apifci = api->follower[code[i]];
      if (apifci.tsi == 0)
      {
        apifci.tsi = new TokenSequence::TokenSequenceImpl(api->k + 1, code[i], api);
      }

      ap = &apifci;
    }

    return *ap;
  }

  int maxTokenCode;
  int bits;
  TokenSequence EPSILON;
  int *code;
  int codeSize;
};

#endif
