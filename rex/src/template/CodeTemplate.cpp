/*
 * CodeTemplate.cpp
 *
 *  Created on: 16.09.2009
 *      Author: Gunther
 */
#include "CodeTemplate.hpp"

#include "../common/Memory.hpp"
#include "../common/WString.hpp"
#include "../common/Decoder.hpp"
#include "../common/FileIO.hpp"
#include "../common/OutputFile.hpp"
#include "../common/Error.hpp"
#include "../common/Format.hpp"
#include "../common/Platforms.hpp"

#include <stdio.h>
#include <string.h>

bool endsWithI(const char *string, const char *pattern)
{
  size_t pSize = strlen(pattern);
  size_t sSize = strlen(string);
  if (sSize >= pSize)
  {
    return strcasecmp(string + sSize - pSize, pattern) == 0;
  }
  return false;
}

int codeTemplate(int argc, char **argv)
{
  CString inputFileName(argv[1]);

  char *content = FileIO::getContent(inputFileName.c_str());
  if (content == 0)
  {
    printf("file not found: %s\n", inputFileName.c_str());
    return 1;
  }

  wchar_t *wContent = Decoder::decode(content);
  free(content);

  if (wContent == 0)
  {
    printf("input encoding error - not UTF-8\n");
    return 1;
  }

  WString templat(wContent);
  free(wContent);

  WString out;
  bool nestedTemplate;
  bool anyNesting = false;

  CString outputFileName(inputFileName);
  TargetLanguage targetLanguage = C;

  do
  {
    nestedTemplate = false;

    char *temp = Format::newFileName(outputFileName.c_str(), "");
    outputFileName = CString(temp);
    free(temp);

    temp = Format::newFileName(outputFileName.c_str(), "");
    CString rawFileName = CString(temp);
    free(temp);

    const char *extension = outputFileName.c_str() + rawFileName.size() + 1;
    nestedTemplate = endsWithI(rawFileName.c_str(), ".template");

    //TODO : error checking

    targetLanguage = OutputFile::targetLanguage(extension);

    if (nestedTemplate)
    {
      outputFileName = rawFileName;
    }

//    printf("...extension: %s, language: %d, default extension: %s, raw file name: %s, nestedTemplate: %d, writing to: %s\n",
//           extension, targetLanguage, OutputFile::extension(targetLanguage), rawFileName.c_str(), nestedTemplate, outputFileName.c_str());

    anyNesting |= nestedTemplate;

    wchar_t *wInputFile = Format::char2wchar(inputFileName.c_str());
    wchar_t *wOutputFile = Format::char2wchar(outputFileName.c_str());
    CodeTemplate ct;
    int indent = -1;
    int outputLineNo = 3;

    try
    {
      CodeFragment::FragmentType type = CodeFragment::TARGET;
      CodeFragment *cf = ct.parse(templat.c_str());
      while (cf)
      {
        int indent1 = 0;
        int indent2 = 0;
        if (type != cf->type)
        {
          for (int i = cf->begin - 1; i >= 0 && templat[i] != L'\n'; --i)
          {
            ++indent1;
          }
          for (int i = cf->begin; i < cf->end && (templat[i] == L' ' || templat[i] == L'\t'); ++i)
          {
            ++indent2;
          }
          if (   cf->type == CodeFragment::HOST
              && cf->begin + indent2 < cf->end
              && templat[cf->begin + indent2] == L'\n')
          {
            cf = cf->next;
            continue;
          }

          if (indent < 0)
          {
            indent = indent1 + indent2;
          }

          if (! anyNesting && targetLanguage != TXT)
          {
            for (int i = indent; i > 0; --i)
            {
              out.append(L" ");
            }

            switch (targetLanguage)
            {
            case XQUERY: out.append(L"(: line "); break;
            case JAVA  : out.append(L"// line "); break;
            default    : out.append(L"#line ");   break;
            }

            Format format;

            if (cf->type == CodeFragment::HOST)
            {
              out.append(format.toString<wchar_t>(ct.lineNo(cf->begin)));
              out.append(L" \"");
              out.append(wInputFile);
            }
            else
            {
              out.append(format.toString<wchar_t>(outputLineNo + 1));
              out.append(L" \"");
              out.append(wOutputFile);
            }

            switch (targetLanguage)
            {
            case XQUERY: out.append(L"\" :)\n"); break;
            case TXT   : break;
            default    : out.append(L"\"\n"); break;
            }

            outputLineNo++;
          }
        }

        type = cf->type;
        switch (type)
        {
        case CodeFragment::VARIABLE:
          {
            WString wName(templat.data() + cf->begin, cf->end - cf->begin);
            cf = cf->next;
            char *name = Format::wchar2char(wName.c_str());
            Format f;
            const char *value = strcmp(name, "REX_VMAJOR") == 0
                              ?               REX_VMAJOR
                              : strcmp(name, "REX_VMINOR") == 0
                              ?               REX_VMINOR
                              : strcmp(name, "REX_YEAR") == 0
                              ?    f.toString(REX_YEAR, 0, 0, 0, (char *) 0)
                              : strcmp(name, "REX_MONTH") == 0
                              ?               REX_MONTH
                              : strcmp(name, "REX_DAY") == 0
                              ?    f.toString(REX_DAY, 0, 0, 0, (char *) 0)
                              : getenv(name);
            if (value == 0)
            {
              printf("undefined: %s\n", name);
              internalerr();
            }
            wchar_t *wValue = Format::char2wchar(value);
            free(name);
            out.append(wValue);
            delete wValue;
          }
          break;

        case CodeFragment::HOST:
          {
            WString hostCode;
            do
            {
              hostCode.append(templat.data() + cf->begin, cf->end - cf->begin);
              if (templat[cf->end - 1] == L'\n')
              {
                ++outputLineNo;
              }
              cf = cf->next;
            }
            while (cf && cf->type == CodeFragment::HOST);

            const wchar_t *string = hostCode.c_str();
            while (isWhiteSpace(*string))
            {
              if (*string == L'\n') --outputLineNo;
              ++string;
            }
            size_t size = wcslen(string);
            while (size > 0 && isWhiteSpace(string[size - 1]))
            {
              --size;
              if (string[size ] == L'\n') --outputLineNo;
            }
            for (int i = indent1 + indent2; i > 0; --i)
            {
              out.append(L" ");
            }
            out.append(string, size);
            out.append(L"\n");
            outputLineNo++;
          }
          break;

        case CodeFragment::TARGET:
          {
            switch (targetLanguage)
            {
            case XQUERY:
              {
                out.append(L"  \"");
                for (int i = cf->begin; i < cf->end; ++i)
                {
                  wchar_t c = templat[i];
                  switch (c)
                  {
                  case L'\n': out.append(L"&#10;"); break;
                  case L'\t': out.append(L"&#9;"); break;
                  case L'\r': out.append(L"&#13;"); break;
                  case L'"' : out.append(L"\"\""); break;
                  case L'&' : out.append(L"&amp;"); break;
                  default   : out.append(&c, 1);
                  }
                }
                out.append(L"\",\n");
              }
              break;

            case TXT:
              for (int i = cf->begin; i < cf->end; ++i)
              {
                wchar_t c = templat[i];
                out.append(&c, 1);
              }
              break;

            default:
              {
                out.append(L"  append(");
                if (targetLanguage != JAVA) out.append(L"L");
                out.append(L"\"");
                for (int i = cf->begin; i < cf->end; ++i)
                {
                  wchar_t c = templat[i];
                  switch (c)
                  {
                  case L'\n': out.append(L"\\n"); break;
                  case L'\t': out.append(L"\\t"); break;
                  case L'\r': out.append(L"\\r"); break;
                  case L'\\':
                  case L'\"': out.append(L"\\");
                  // fall through
                  default   : out.append(&c, 1);
                  }
                }
                out.append(L"\");\n");
              }
            }
            outputLineNo++;
            cf = cf->next;
          }
          break;

        default:
          internalerr();
          break;
        }
      }
    }
    catch (CodeTemplate::ParseException &)
    {
      // not supposed to happen - grammar covers all input

      printf("parsing exception\n");
      internalerr();
    }

    free(wInputFile);
    free(wOutputFile);

    if (nestedTemplate)
    {
      templat = out;
      out.clear();
    }
  }
  while (nestedTemplate);

  OutputFile outFile(outputFileName.c_str(), targetLanguage, argv, true, false);
  outFile.print(out.c_str());

  return 0;
}
