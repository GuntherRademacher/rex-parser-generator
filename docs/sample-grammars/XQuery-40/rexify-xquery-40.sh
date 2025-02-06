#!/bin/bash
set -e

BUILD_DIR="$(realpath --relative-to="$(pwd)" "$(dirname "$0")")/build"

echo "...creating build directory: $BUILD_DIR"
mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"

rexify() {
    local INPUT="$1"
    local OUTPUT="$2"

    echo "...RExifying $INPUT into $OUTPUT"
    basex -bspecification-url="$INPUT" -smethod=text "../$(basename "$0" .sh).xq" > "$OUTPUT"

    echo "...running LALR(2) construction on $OUTPUT"
    rex -lalr 2 "$OUTPUT"
}

rexify "https://qt4cg.org/specifications/xquery-40/xquery-40.html" "XQuery-40.ebnf"
rexify "https://qt4cg.org/specifications/xquery-40/xpath-40.html" "XPath-40.ebnf"

echo "...done"