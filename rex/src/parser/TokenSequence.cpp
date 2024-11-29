/*
 * Token.cpp
 *
 *  Created on: 19.03.2009
 *      Author: Gunther
 */

#include "../common/Memory.hpp"
#include "TokenSequence.hpp"
#include "Grammar.hpp"

TokenSequence TokenSequence::VOID = 0;

WString TokenSequence::toString(Grammar *grammar) const
{
  WString string;

  for (int j = 0; ; ++j)
  {
    Token::Code t = operator[](j);
    if (t == 0)
    {
      break;
    }
    if (j > 0)
    {
      string += L" ";
    }
    string += grammar->naming.getName(grammar, t);
    if (t == Token::eEND)
    {
      break;
    }
  }

  return string;
}
