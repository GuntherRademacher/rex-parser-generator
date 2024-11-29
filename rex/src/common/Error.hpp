/*
 * Error.hpp
 *
 *  Created on: 08.06.2009
 *      Author: Gunther
 */

#ifndef ERROR_HPP
#define ERROR_HPP

#include <stdio.h>
#include <stdlib.h>

#define ASSERTIONS 0
#define SELFTEST 0
#define internalerr() {fprintf(stderr, "\n\n<< internal error %s:%d >>\n\n", __FILE__, __LINE__); exit(1);}
#define outofmemory() {fprintf(stderr, "\n\n<< out of memory >>\n\n"); exit(1);}

#endif
