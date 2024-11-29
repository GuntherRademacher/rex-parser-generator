#!/bin/bash
#
# compiles with e.g.
#   - g++ (GCC) 8.5.0 20210514 (Red Hat 8.5.0-3)
#   - g++ (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0
#   - g++ (SUSE Linux) 11.2.1 20210816 [revision 056e324ce46a7924b5cf10f61010cf9dd2ca10e9]

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
  g++ -std=gnu++17 -O3 -Wall -c -o $OBJ $CPP
  set -e
done

mkdir -p build/bin
CMD="g++ -o build/bin/rex $OBJECTS"
echo $CMD
$CMD

echo
echo Successfully built executable build/bin/rex
