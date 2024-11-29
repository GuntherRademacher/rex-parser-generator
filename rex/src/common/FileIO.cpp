/*
 * getContent.cpp
 *
 *  Created on: Aug 26, 2009
 *      Author: Gunther
 */

#include "../common/Memory.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <new>
#include "../common/FileIO.hpp"

char *FileIO::getContent(const char *name)
{
  size_t size = strlen(name);
  if (name[0] == '{' && name[size - 1] == '}')
  {
    size -= 2;
    char *content = ALLOCATE_ARRAY(char, size + 1);

    strncpy(content, name + 1, size);
    content[size] = 0;
    return content;
  }
  else
  {
    FILE *file = fopen(name, "rb");
    if (file == 0)
    {
      return 0;
    }
    else
    {
      size_t size = 0;
      size_t contentSize = 1024;
      char *content = ALLOCATE_ARRAY(char, contentSize);

      for (;;)
      {
        size_t wanted = contentSize - size - 1;
        size_t got = fread(content + size, 1, wanted, file);
        size += got;
        if (got < wanted)
        {
          break;
        }
        else
        {
          contentSize <<= 1;
          content = REALLOCATE_ARRAY(char, content, contentSize);
        }
      }

      content[size++] = 0;
      fclose(file);

      const char *i = content;
      char *o = content;
      char c;

      do
      {
        c = *i++;
        if (c == '\r')
        {
          *o++ = '\n';
          if (*i == '\n')
          {
            ++i;
          }
        }
        else
        {
          *o++ = c;
        }
      }
      while (c);

      return content;
    }
  }
}
