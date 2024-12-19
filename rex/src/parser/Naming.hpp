/*
 * Naming.hpp
 *
 *  Created on: 05.10.2008
 *      Author: Gunther
 */

#ifndef NAMING_HPP_
#define NAMING_HPP_

#include "Token.hpp"
#include <map>

class Grammar;

class Naming : private std::map<std::pair<Token::Code, bool>, const wchar_t *>
{
public:
  ~Naming()
  {
    for (iterator i(begin()); i != end(); ++i)
    {
      free(const_cast<wchar_t *>(i->second));
    }
  }

  static const wchar_t *getName(Grammar *grammar, Token::Code code, bool showCode = false);
};

#endif
