/*
 * OrderedTokenSequenceVector.cpp
 *
 *  Created on: 03.02.2014
 *      Author: Gunther
 */

#include "../common/Memory.hpp"
#include "OrderedTokenSequenceVector.hpp"
#include "Naming.hpp"
#include "WcsSet.hpp"

WString OrderedTokenSequenceVector::toString(Grammar *grammar,
                                             const wchar_t *linePrefix,
                                             const wchar_t *setSeparator,
                                             size_t width,
                                             size_t trailerWidth,
                                             bool showCodes,
                                             WcsSet *toBeEscaped) const
{
  size_t setSeparatorSize = wcslen(setSeparator);
  WString string;
  size_t l = 0;

  for (OrderedTokenSequenceVector::const_iterator i = begin(); i != end(); )
  {
    const TokenSequence &cs(*i);
    ++i;
    bool last = i == end();

    size_t sequenceSize = cs.size();
    for (size_t j = 0; j == 0 || j < sequenceSize; ++j)
    {
      const Token::Code c(cs[(int) j]);

      const wchar_t *name = Naming::getName(grammar, c, showCodes);

      WString escapedName;
      if (toBeEscaped && (*name == '\'' || *name == '"'))
      {
        bool doEscape = false;
        for (WcsSet::const_iterator k = toBeEscaped->begin(); k != toBeEscaped->end(); ++k)
        {
          if (wcsstr(name, *k))
          {
            doEscape = true;
            break;
          }
        }

        if (doEscape)
        {
          escapedName.append(L"(", 1);
          escapedName.append(name);
          escapedName.append(L")", 1);
          const wchar_t *quote = name;
          for (WcsSet::const_iterator k = toBeEscaped->begin(); k != toBeEscaped->end(); ++k)
          {
            size_t pos = escapedName.find(*k);
            if (pos != WString::npos)
            {
              size_t len = wcslen(*k);
              WString replacement;
              replacement.append(*k, 1);
              replacement.append(quote, 1);
              replacement.append(L" ", 1);
              replacement.append(quote, 1);
              replacement.append(*k + 1);
              escapedName.replace(pos, len, replacement);
            }
          }
          name = escapedName.c_str();
        }
      }
      size_t nameSize = wcslen(name);

      if (l)
      {
        if (j == 0)
        {
          string += setSeparator;
          l += setSeparatorSize;
        }

        size_t suffixSize = (j + 1 >= sequenceSize && last)
                          ? trailerWidth
                          : setSeparatorSize;
        if (l + 1 + nameSize + suffixSize <= width)
        {
          string += L' ';
          l++;
        }
        else
        {
          string += linePrefix;
          l = 0;
        }
      }

      string += name;
      l += nameSize;
    }
  }
  return string;
}
