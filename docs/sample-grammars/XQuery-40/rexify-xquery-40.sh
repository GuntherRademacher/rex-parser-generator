#!/bin/bash
set -e

BUILD_DIR="$(realpath --relative-to="$(pwd)" "$(dirname "$0")")/build"

echo "...creating build directory: $BUILD_DIR"
mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"

echo "...fetching EBNF grammar"
curl --silent -O https://raw.githubusercontent.com/GuntherRademacher/rr/refs/heads/basex/src/main/java/de/bottlecaps/railroad/core/Parser.ebnf

echo "...generating EBNF parser"
rex -q -xquery -tree Parser.ebnf

echo "...RExifying XQuery 4.0 grammar"
basex -smethod=text ../$(basename "$0" .sh).xq > XQuery-40.ebnf

echo "...running LALR(2) construction on XQuery 4.0 grammar"
rex -lalr 2 XQuery-40.ebnf

echo "...done"
