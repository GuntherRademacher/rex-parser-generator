import module namespace xquery-xquery = "de/bottlecaps/rex/XQuery-40" at "build/XQuery-40.xquery";
import module namespace xquery-java = "java:de.bottlecaps.rex.XQuery_40";
import module namespace xpath-xquery = "de/bottlecaps/rex/XPath-40" at "build/XPath-40.xquery";
import module namespace xpath-java = "java:de.bottlecaps.rex.XPath_40";

declare namespace qtfc = "http://www.w3.org/2010/09/qt-fots-catalog";

declare variable $root as xs:string external;
declare variable $language as xs:string external := "xquery";
declare variable $implementation as xs:string external := "java";
declare variable $skip as xs:string* external := ();
declare variable $verbose as xs:boolean external := false();

declare variable $xquery-known-failures as xs:string* :=
(
  "fo-test-map-of-pairs-008",            (: bad test - map entry syntax in map:pair function call :)
  "fo-test-map-of-pairs-009",            (: bad test - unexpected right parenthesis :)
  "fo-test-map-of-pairs-010",            (: bad test - map entry syntax in map:pair function call :)
  "fo-test-map-of-pairs-011"             (: bad test - map entry syntax in map:pair function call :)
);

declare variable $xpath-known-failures as xs:string* :=
(
  "fo-test-fn-hash-009",                 (: missing XQ40+ dependency in generated test :)
  "fo-test-fn-hash-010",                 (: missing XQ40+ dependency in generated test :)
  "fo-test-fn-deep-equal-005",           (: missing XQ40+ dependency in generated test :)
  "fo-test-fn-count-001",                (: missing XQ40+ dependency in generated test :)
  "fo-test-fn-serialize-004",            (: missing XQ40+ dependency in generated test :)
  "fo-test-fn-function-annotations-002", (: missing XQ40+ dependency in generated test :)
  "fo-test-fn-function-annotations-003", (: missing XQ40+ dependency in generated test :)
  "fo-test-fn-sort-with-005",            (: missing XQ40+ dependency in generated test :)
  "fo-test-map-of-pairs-008",            (: bad test - map entry syntax in map:pair function call :)
  "fo-test-map-of-pairs-009",            (: bad test - unexpected right parenthesis :)
  "fo-test-map-of-pairs-010",            (: bad test - map entry syntax in map:pair function call :)
  "fo-test-map-of-pairs-011",            (: bad test - map entry syntax in map:pair function call :)
  "fo-test-fn-every-010"                 (: missing XQ40+ dependency in generated test :)
);

declare variable $parse :=
  switch ($language)
  {
    case "xquery" return 
      switch ($implementation)
      {
        case "java" return xquery-java:parse-Module#1
        case "xquery" return xquery-xquery:parse-Module#1
        default return error(xs:QName("process-tests"), "unsupported parser implementation language: " || $implementation)
      }
    case "xpath" return 
      switch ($implementation)
      {
        case "java" return xpath-java:parse-XPath#1
        case "xquery" return xpath-xquery:parse-XPath#1
        default return error(xs:QName("process-tests"), "unsupported parser implementation language: " || $implementation)
      }
    default return
      error(xs:QName("process-tests"), "unsupported parser target language: " || $language)
  };

declare variable $filter := upper-case(substring($language, 1, 2)) || '(\d\d\+|40)';
declare variable $known-failures := if ($language eq "xquery") then $xquery-known-failures else $xpath-known-failures;

declare variable $expected-pass := 0;
declare variable $expected-fail := 1;
declare variable $unexpected-pass := 2;
declare variable $unexpected-fail := 3;
declare variable $skipped := 4;

declare function local:msg($indent, $content)
{
  let $prefix := string-join((1 to $indent * 4)!" ")
  return message(text{string-join(($prefix, replace($content, "&#xA;", "&#xA;" || $prefix)))})
};

declare function local:parse($path, $name, $query as fn() as xs:string, $expect-error)
{
    let $error :=
      try
      {
        $parse($query())
      }
      catch err:FOUT1190
      {
        <ERROR>{local-name-from-QName($err:code), $err:description}</ERROR>
      }
    let $msg := fn() {local:msg(0, "...processing " || $path || (", test-case: " || $name || ", expect-error: " || $expect-error)[exists($name)])}
    return
      if (empty($error)) then
        if ($expect-error) then
          if ($name = $known-failures) then
            (if ($verbose) {$msg()}, $expected-fail)
          else
            ($msg(), local:msg(1, "expected syntax error has not occured"), $unexpected-fail)
        else 
          if ($name = $known-failures) then
            ($msg(), local:msg(1, "test passed unexpectedly"), $unexpected-pass)
          else
            (if ($verbose) {$msg()}, $expected-pass)
      else
        if ($expect-error) then
          if ($name = $known-failures) then
            ($msg(), local:msg(1, "test passed unexpectedly"), $unexpected-pass)
          else
            (if ($verbose) {$msg()}, $expected-pass)
        else
          if ($name = $known-failures) then
            (if ($verbose) {$msg()}, $expected-fail)
          else
            ($msg(), local:msg(1, $error), $unexpected-fail)
};

declare function local:supported($node)
{
  empty($node/qtfc:dependency[
    @type = 'spec' and not(matches(@value, $filter)) or
    @type = ('xml-version', 'xsd-version') and @value = ('1.1', '1.0:4-') or
    @type = "feature" and @value = "XQUpdate" and string(@satisfied) = ("", "true") or
    @type = "feature" and not(@value = "XQUpdate") and string(@satisfied) = 'false'
  ])
};

declare function local:test-set($path, $test-set)
{
  let $file := $test-set/@file
  return
    if (exists($file)) then
      local:process(resolve-uri($test-set/@file, base-uri($test-set)))
    else if (local:supported($test-set)) then
      for $test-case in $test-set/qtfc:test-case
      return local:test-case($path, $test-case)
    else
      $test-set/qtfc:test-case/$skipped
};

declare function local:test-case($path, $test-case)
{
  if (not(local:supported($test-case))) then
    $skipped
  else
    let $test := $test-case/qtfc:test
    let $file := $test/@file
    let $expect-error := $test-case/qtfc:result//qtfc:error/@code = "XPST0003"
    let $query :=
      if ($file) then
        fn() {unparsed-text(resolve-uri($file, base-uri($test-case)))}
      else
        fn() {string($test)}
    return local:parse($path, $test-case/@name, $query, $expect-error)
};

declare function local:process($path)
{
  if (matches($path, "\.xml$", "i")) then
    let $doc := 
      try
      {
        doc($path)/*
      }
      catch err:FODC0002
      {
        <ERROR>{local-name-from-QName($err:code), $err:description}</ERROR>
      }
    return
      typeswitch ($doc)
      case $error as element(ERROR) return
        (local:msg(0, "...processing " || $path), local:msg(1, $error), $unexpected-fail)
      case $catalog as element(qtfc:catalog) return
        for $test-set in $catalog/qtfc:test-set
        return local:test-set($path, $test-set)
      case $test-set as element(qtfc:test-set) return
        local:test-set($path, $test-set)
      default return
        ()
    else if ($language eq "xquery" and matches($path, "\.xq[^.]*$", "i")) then
      let $query := fn() {unparsed-text($path)}
      return local:parse($path, (), $query, false())
    else if ($language eq "xpath" and matches($path, "\.xp[^.]*$", "i")) then
      let $query := fn() {unparsed-text($path)}
      return local:parse($path, (), $query, false())
    else 
      ()
};

declare function local:traverse($path as xs:string)
{
  if (not(file:is-dir($path))) then
    local:process(replace($path, "^\./", ""))
  else
    let $path := replace($path || "/", "[\\/][\\/]?", "/")
    for $entry in file:list($path)
      let $entry := $path || $entry
      where matches($entry, "([\\/]|\.(xml|xq.*))$", "i")
      return local:traverse($entry)
};

let $result := local:traverse($root)
return
  "Test results for " || $language || " parser in " || $implementation || ":&#xA;" ||
  "&#xA;" ||
  "|             Status | Test count&#xA;" ||
  "|-------------------:|-----------:&#xA;" ||
  "|            skipped | "   || count($result[. = $skipped        ]) || "&#xA;" ||
  "|   expected success | "   || count($result[. = $expected-pass  ]) || "&#xA;" ||
  "|   expected failure | "   || count($result[. = $expected-fail  ]) || "&#xA;" ||
  "| unexpected success | "   || count($result[. = $unexpected-pass]) || "&#xA;" ||
  "| unexpected failure | "   || count($result[. = $unexpected-fail]) || "&#xA;" ||
  "|          **total** | **" || count($result                      ) || "**&#xA;"
