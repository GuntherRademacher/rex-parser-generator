#include "../common/Memory.hpp"

#include "LexerGenerator.hpp"
#include "RExParser.hpp"

LexerGenerator *LexerGenerator::newInstance()
{
  return new RExParser();
}
