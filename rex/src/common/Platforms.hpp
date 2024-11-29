/*
 * Platforms.hpp
 *
 *  Created on: 20.10.2021
 *      Author: Gunther
 */

#ifndef SRC_COMMON_PLATFORMS_HPP_
#define SRC_COMMON_PLATFORMS_HPP_


#if defined(_WIN32) || defined(_MSC_VER)

  #define strcasecmp _stricmp
  #define strncasecmp _strnicmp
  #define wcsncasecmp _wcsnicmp

  #ifdef __GNUG__
    #define swprintf snwprintf
    #define wcstoken(strToken, strDelimit, context) wcstok(strToken, strDelimit)
  #else
    #define wcstoken(strToken, strDelimit, context) wcstok(strToken, strDelimit, context)
  #endif

#else
  #define wcstoken(strToken, strDelimit, context) wcstok(strToken, strDelimit, context)
#endif

#endif
