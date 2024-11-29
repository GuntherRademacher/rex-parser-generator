/*
 * Token.hpp
 *
 *  Created on: Sep 8, 2008
 *      Author: Gunther
 */

#ifndef TOKEN_HPP_
#define TOKEN_HPP_

#include <stdlib.h>

class Token
{
public:
  typedef short Code;

  static bool valid(Code c)
  {
    return c >= 0;
  }

  enum
  {
    eEPSILON = 0,
    eCYCLIC = 1,
    eIMPLICIT = 2,
    eEND = 3,
    eFIRST = 4
  };
};

#endif
