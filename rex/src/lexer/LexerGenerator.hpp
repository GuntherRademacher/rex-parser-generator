/*
 * REx.hpp
 *
 *  Created on: Jul 27, 2009
 *      Author: Gunther
 */

#ifndef LEXERGENERATOR_HPP
#define LEXERGENERATOR_HPP

#include "../common/CGVariable.hpp"

class LexerGenerator
{
public:
  virtual ~LexerGenerator() {};
  virtual const wchar_t *getInstanceCode() const = 0;
  virtual const wchar_t *getStaticCode() const = 0;
  virtual int run(int argc, char **argv) = 0;
  virtual void setVerbose(bool v = true) = 0;
  virtual void setQuiet(bool q = true) = 0;
  virtual void bind(CGVariable v) = 0;

  static LexerGenerator *newInstance();

  static int main(int c, char **v)
  {
    LexerGenerator *generator = newInstance();
    int response = generator->run(c, v);
    delete generator;
    return response;
  }

protected:
  LexerGenerator() {};

private:
  LexerGenerator(const LexerGenerator &);
  LexerGenerator &operator=(const LexerGenerator &);
};

#endif
