#!/bin/bash
#
# compiles with
#   - clang version 10.0.0-4ubuntu1
#   - clang version 12.0.1 (Red Hat 12.0.1-2.module_el8.6.0+937+1cafe22c)
#   - clang version 13.0.0 (openSUSE Tumbleweed 20211019
#   - clang version 14.0.6 (Centos Stream 8)
#   - clang version 15.0.7 (Centos Stream 8)
#   - Apple clang version 16.0.0 (clang-1600.0.26.6)

set -e
cd "$(dirname "$0")/.."
rm -f -r build

OBJECTS=
for CPP in $(find src -name '*.cpp'); do
  OBJ=build/obj/${CPP%.*}.o
  OBJECTS="$OBJECTS $OBJ"
  mkdir -p build/obj/${CPP%/*}
  echo $CPP
  set +e
  clang++ -std=gnu++17 -c -o $OBJ $CPP
  set -e
done

mkdir -p build/bin
CMD="clang++ -o build/bin/rex $OBJECTS"
echo $CMD
$CMD

echo
echo Successfully built executable build/bin/rex
