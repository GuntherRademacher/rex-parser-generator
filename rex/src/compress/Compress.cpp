/*
 * Compress.cpp
 *
 *  Created on: 24.06.2012
 *      Author: Gunther
 */
#include "../common/Memory.hpp"

#include "Compress.hpp"

#include "../lexer/CodeGenerator.hpp"

#include "../common/CGVariable.hpp"
#include "../common/OutputFile.hpp"
#include "../common/IntString.hpp"
#include "../common/WString.hpp"
#include "../common/Decoder.hpp"
#include "../common/FileIO.hpp"
#include "../common/OutputFile.hpp"
#include "../common/Error.hpp"
#include "../common/Format.hpp"
#include "../common/CompressedMap.hpp"

#include <stdio.h>
#include <string.h>
#include <memory>

static void computeRanges(const int *codes, size_t offset, size_t size, IntString &rangeMap)
{
  IntString ranges;
  size_t rangeStart = offset;
  size_t rangeEnd = offset;
  int rangeValue = codes[offset];
  for (size_t i = offset + 1; i < size; ++i)
  {
    int code = codes[i];
    if (code != rangeValue)
    {
      if (rangeValue != 0)
      {
        ranges.push_back(rangeStart);
        ranges.push_back(rangeEnd);
        ranges.push_back(rangeValue);
      }
      rangeStart = i;
      rangeValue = code;
    }
    rangeEnd = i;
  }
  if (rangeValue != 0)
  {
    ranges.push_back(rangeStart);
    ranges.push_back(rangeEnd);
    ranges.push_back(rangeValue);
  }
  rangeMap.append(ranges.size(), 0);
  int rangeCount = ranges.size() / 3;
  for (int i = 0; i < rangeCount; ++i)
  {
    rangeMap[i                 ] = ranges[3 * i    ];
    rangeMap[i + rangeCount    ] = ranges[3 * i + 1];
    rangeMap[i + rangeCount * 2] = ranges[3 * i + 2];
  }
}

int compress(int argc, char **argv)
{
  CString inputFileName(argv[1]);

  char *content = FileIO::getContent(inputFileName.c_str());
  if (content == 0)
  {
    printf("file not found: %s\n", inputFileName.c_str());
    return 1;
  }

  Compress parser(content);
  try
  {
    parser.parse_IntegerList();
    free(content);
  }
  catch (Compress::ParseException &e)
  {
    fputs(parser.getErrorMessage(e).c_str(), stderr);
    free(content);
    return 1;
  }

  IntString &integers = parser.getIntegers();

  size_t divider = Math::min(integers.size(), (size_t) 0x30000);
  TiledMap tiledMap(integers.c_str(), divider, 16, false);
  IntString rangeMap;
  computeRanges(integers.c_str(), divider, integers.size(), rangeMap);

  CString outputFileName(inputFileName);
  char *temp = Format::newFileName(outputFileName.c_str(), "");
  outputFileName = CString(temp);
  free(temp);

  temp = Format::newFileName(outputFileName.c_str(), "");
  CString rawFileName = CString(temp);
  free(temp);

  temp = Format::newFileName(rawFileName.c_str(), "");
  CString className = CString(temp);
  free(temp);

  const char *extension = outputFileName.c_str() + rawFileName.size() + 1;
  TargetLanguage targetLanguage = OutputFile::targetLanguage(extension);

//  printf("output: %s, size: %d, sample: %d %d %d\n", outputFileName.c_str(), integers.size(), integers[0], integers[1], integers[2]);
//  printf("compressedSize: %d, depth: %d\n", tiledMap.size(), tiledMap.getDepth());

  FILE *outputFile = fopen(outputFileName.c_str(), "wb");
  OutputFile::printHeader(outputFile, targetLanguage, argv);

  CodeGenerator *codeGenerator = CodeGenerator::newInstance(targetLanguage, outputFile);
  codeGenerator->bind(CGVariable("size", (int) integers.size()));
  codeGenerator->bind(CGVariable("rm", rangeMap.c_str(), rangeMap.size(), "HIGH", "The high value map."));
  codeGenerator->bind(CGVariable("dt", tiledMap.getRepresentation(), tiledMap.size(), "LOW", "The low value map."));

  printf("tiledMap.getDepth() = %d\n", (int) tiledMap.getDepth());

  codeGenerator->bind(CGVariable("dtbits", tiledMap.getBits(), tiledMap.getDepth(), 0, 0));
  codeGenerator->bind(CGVariable("classname", className.c_str()));

  codeGenerator->generateCompressedMap();
  fwrite(codeGenerator->getEncodedOutput(), 1, strlen(codeGenerator->getEncodedOutput()), outputFile);
  delete codeGenerator;

  OutputFile::printFooter(outputFile, targetLanguage);

  return 0;
}
