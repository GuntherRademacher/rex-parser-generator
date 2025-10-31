#!/bin/bash
set -e

SCRIPT_DIR="$(dirname "$(realpath "$0")")"
BUILD_DIR="$SCRIPT_DIR/build"
CACHE="$BUILD_DIR/cache"
CATALOG="$CACHE/catalog.xml"
BASEX=$(dirname $(dirname $(command -v basex)))
export CLASSPATH=".:$BASEX/BaseX.jar:$BASEX/lib/*"
BASEX_JVM="-Dorg.basex.catalog=file:///$CATALOG"

SPEC_PATH_SEGMENT="${1:-specifications}"
XQUERY_SPEC="https://qt4cg.org/$SPEC_PATH_SEGMENT/xquery-40/xquery-40.html"
XPATH_SPEC="https://qt4cg.org/$SPEC_PATH_SEGMENT/xquery-40/xpath-40.html"

[ ! -d "$BUILD_DIR" ] && { echo "...creating build directory: $BUILD_DIR"; mkdir "$BUILD_DIR"; }
[ ! -d "$CACHE" ] && { echo "...creating cache directory: $CACHE"; mkdir "$CACHE"; }

cd "$CACHE"

download() {
    local file="$1"
    local url="$2"
    if [[ ! -f "$file" ]]; then
        echo "...downloading $file"
        curl -fsS -o "$file" "$url"
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
  <uri name="unify-grammar.xq" uri="file://$(pwd)/../../unify-grammar.xq"/>
EOF

download xquery-40.html          $XQUERY_SPEC
download xpath-40.html           $XPATH_SPEC
download xquery-update-30.html   https://www.w3.org/TR/xquery-update-30/
download xpath-full-text-30.html https://www.w3.org/TR/xpath-full-text-30/
download xml.html                https://www.w3.org/TR/REC-xml/
download xml-names.html          https://www.w3.org/TR/REC-xml-names/
download cst-to-ast.xq           https://raw.githubusercontent.com/GuntherRademacher/rr/refs/heads/basex/src/main/resources/de/bottlecaps/railroad/xq/cst-to-ast.xq
download ast-to-ebnf.xq          https://raw.githubusercontent.com/GuntherRademacher/rr/refs/heads/basex/src/main/resources/de/bottlecaps/railroad/xq/ast-to-ebnf.xq
download html-to-ebnf.xq         https://raw.githubusercontent.com/GuntherRademacher/rr/refs/heads/basex/src/main/resources/de/bottlecaps/railroad/xq/html-to-ebnf.xq
download ebnf-parser.xquery      https://raw.githubusercontent.com/GuntherRademacher/rr/refs/heads/basex/src/main/resources/de/bottlecaps/railroad/xq/ebnf-parser.xquery

echo "</catalog>" >> catalog.xml

cd "$BUILD_DIR"

rexify() {
    local html="$1"
    local ebnf="$2"
    local algorithm="$3"
    local lookahead="$4"
    local with_update="$5"
    local with_full_text="$6"
    local with_basex="$7"
    local name="$(basename "$ebnf" .ebnf)"
    local class="${name//-/_}"
    
    echo "...RExifying $html into $ebnf"
    java $BASEX_JVM org.basex.BaseX -bwith-update="$with_update" -bwith-full-text="$with_full_text" -bwith-basex="$with_basex" -bspecification-url="$html" -smethod=text "../$(basename "$0" .sh).xq" > "$ebnf"
    
    echo "...generating parser for $ebnf in XQuery"
    rex $algorithm $lookahead -xquery -name "de/bottlecaps/rex/$name" "$ebnf"
    echo "...generating parser for $ebnf in Java"
    rex $algorithm $lookahead -java -basex -name "de.bottlecaps.rex.$class" "$ebnf"
    echo "...compiling $class"
    javac -d . "$class.java"
}

rexify $XQUERY_SPEC XQuery-40.ebnf                         -lalr 2 false false false
rexify $XQUERY_SPEC XQuery-Full-Text-Update-40.ebnf        -lalr 2 true  true  false
rexify $XQUERY_SPEC XQuery-Full-Text-Update-BaseX-40.ebnf -glalr 1 true  true  true
rexify $XPATH_SPEC  XPath-40.ebnf                          -lalr 1 false false false
rexify $XPATH_SPEC  XPath-Full-Text-40.ebnf                -lalr 2 false true  false

echo "...done"
