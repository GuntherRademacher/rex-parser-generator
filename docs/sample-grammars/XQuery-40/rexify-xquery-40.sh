#!/bin/bash
set -e

SCRIPT_DIR="$(dirname "$(realpath "$0")")"
BUILD_DIR="$SCRIPT_DIR/build"
CACHE="$BUILD_DIR/cache"
CATALOG="$CACHE/catalog.xml"
BASEX=$(dirname $(dirname $(command -v basex)))
export CLASSPATH=".:$BASEX/BaseX.jar:$BASEX/lib/*"
BASEX_JVM="-Dorg.basex.catalog=file:///$CATALOG"

[ ! -d "$BUILD_DIR" ] && { echo "...creating build directory: $BUILD_DIR"; mkdir "$BUILD_DIR"; }
[ ! -d "$CACHE" ] && { echo "...creating cache directory: $CACHE"; mkdir "$CACHE"; }

cd "$CACHE"

download() {
    local file="$1"
    local url="$2"
    if [[ ! -f "$file" ]]; then
        echo "...downloading $file"
        curl -sS -o "$file" "$url"
    else
        echo "...$file is already present in cache"
    fi
    local uri="$(realpath "$file")"
    echo "  <uri name=\"$file\" uri=\"file:///$uri\"/>" >> catalog.xml
    echo "  <uri name=\"$url\" uri=\"file:///$uri\"/>" >> catalog.xml
}

cat > catalog.xml <<EOF
<?xml version="1.0"?>
<catalog xmlns="urn:oasis:names:tc:entity:xmlns:xml:catalog">
EOF

download xquery-40.html     https://qt4cg.org/specifications/xquery-40/xquery-40.html
download xpath-40.html      https://qt4cg.org/specifications/xquery-40/xpath-40.html
download xml.html           https://www.w3.org/TR/REC-xml/
download xml-names.html     https://www.w3.org/TR/REC-xml-names/
download cst-to-ast.xq      https://raw.githubusercontent.com/GuntherRademacher/rr/refs/heads/basex/src/main/resources/de/bottlecaps/railroad/xq/cst-to-ast.xq
download ast-to-ebnf.xq     https://raw.githubusercontent.com/GuntherRademacher/rr/refs/heads/basex/src/main/resources/de/bottlecaps/railroad/xq/ast-to-ebnf.xq
download html-to-ebnf.xq    https://raw.githubusercontent.com/GuntherRademacher/rr/refs/heads/basex/src/main/resources/de/bottlecaps/railroad/xq/html-to-ebnf.xq
download ebnf-parser.xquery https://raw.githubusercontent.com/GuntherRademacher/rr/refs/heads/basex/src/main/resources/de/bottlecaps/railroad/xq/ebnf-parser.xquery

echo "</catalog>" >> catalog.xml

cd "$BUILD_DIR"

rexify() {
    local html="$1"
    local ebnf="$2"
    local name="$(basename "$ebnf" .ebnf)"
    local class="${name//-/_}"
    
    echo "...RExifying $html into $ebnf"
    java $BASEX_JVM org.basex.BaseX -bspecification-url="$html" -smethod=text "../$(basename "$0" .sh).xq" > "$ebnf"
    
    echo "...generating parser for $ebnf in XQuery"
    rex -lalr 2 -xquery -name "de/bottlecaps/rex/$name" "$ebnf"
    echo "...generating parser for $ebnf in Java"
    rex -lalr 2 -java -basex -name "de.bottlecaps.rex.$class" "$ebnf"
    echo "...compiling $class"
    javac -d . "$class.java"
}

rexify https://qt4cg.org/specifications/xquery-40/xquery-40.html XQuery-40.ebnf
rexify https://qt4cg.org/specifications/xquery-40/xpath-40.html XPath-40.ebnf

echo "...done"
