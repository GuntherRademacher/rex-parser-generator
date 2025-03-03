#!/bin/bash
set -e

SCRIPT_DIR="$(dirname "$(realpath "$0")")"
BUILD_DIR="$SCRIPT_DIR/build"

BASEX=$(dirname $(dirname "$(command -v basex)"))
export CLASSPATH=".:$BASEX/BaseX.jar:$BASEX/lib/*"
BASEX_JVM="-Dorg.basex.catalog=file:///C:/Users/Gunther/git/rex-parser-generator/docs/sample-grammars/XQuery-40/catalog.xml"
ROOT=$(realpath $SCRIPT_DIR/../../../../qt4tests/catalog.xml)

cd "$BUILD_DIR"

LANGUAGE=${1:-xquery}
IMPLEMENTATION=${2:-java}
VERBOSE=${3:-false}

java org.basex.BaseX \
    "-blanguage=$LANGUAGE" \
    "-bimplementation=$IMPLEMENTATION" \
    "-bverbose=$VERBOSE" \
    "-broot=$ROOT" \
    ../process-tests.xq

