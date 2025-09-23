import module namespace xquery-xquery = "de/bottlecaps/rex/XQuery-40" at "build/XQuery-40.xquery";
import module namespace xquery-java   = "java:de.bottlecaps.rex.XQuery_40";
import module namespace xquery-full-text-update-xquery
                                      = "de/bottlecaps/rex/XQuery-Full-Text-Update-40" at "build/XQuery-Full-Text-Update-40.xquery";
import module namespace xquery-full-text-update-java
                                      = "java:de.bottlecaps.rex.XQuery_Full_Text_Update_40";
import module namespace xpath-xquery  = "de/bottlecaps/rex/XPath-40" at "build/XPath-40.xquery";
import module namespace xpath-java    = "java:de.bottlecaps.rex.XPath_40";
import module namespace xpath-full-text-xquery
                                      = "de/bottlecaps/rex/XPath-Full-Text-40" at "build/XPath-Full-Text-40.xquery";
import module namespace xpath-full-text-java
                                      = "java:de.bottlecaps.rex.XPath_Full_Text_40";

declare namespace qtfc = "http://www.w3.org/2010/09/qt-fots-catalog";
declare namespace ftts = "http://www.w3.org/2005/02/query-test-full-text";

declare variable $root1 as xs:string external := ();
declare variable $root2 as xs:string external := ();
declare variable $language as xs:string external := "xquery";
declare variable $implementation as xs:string external := "java";
declare variable $skip as xs:string* external := ();
declare variable $verbose as xs:boolean external := false();

declare variable $xquery-known-failures as xs:string* :=
(
  "fo-test-fn-jnode-selector-002",         (: StringLiteral instead of NodeTest     :)
  "fo-test-fn-jnode-content-002",          (: missing parentheses around sequence   :)

  (: XQuery Update :)

  "stf-insert-002",                        (: uses reserved attribute name 'type'   :)
  "stf-insert-after-003",                  (: uses reserved attribute name 'type'   :)
  "stf-replace-node-005"                   (: uses reserved attribute name 'type'   :)
);

declare variable $xpath-known-failures as xs:string* :=
(
  "fo-test-fn-deep-equal-005",             (: missing XQ dependency in generated test :)
  "fo-test-fn-count-001",                  (: missing XQ dependency in generated test :)
  "fo-test-fn-serialize-004",              (: missing XQ dependency in generated test :)
  "fo-test-fn-function-annotations-002",   (: missing XQ dependency in generated test :)
  "fo-test-fn-function-annotations-003",   (: missing XQ dependency in generated test :)
  "fo-test-fn-sort-with-005",              (: missing XQ dependency in generated test :)
  "fo-test-fn-every-010",                  (: missing XQ dependency in generated test :)
  "fo-test-fn-hash-009",                   (: missing XQ dependency in generated test :)
  "fo-test-fn-hash-010",                   (: missing XQ dependency in generated test :)
  "fo-test-fn-jnode-selector-002",         (: StringLiteral instead of NodeTest       :)
  "fo-test-fn-jnode-content-002",          (: missing parentheses around sequence     :)
  
  (: XPath Full Text test suite :)

  "examples-364-5",                        (: direct element constructor              :)
  "examples-364-5a",                       (: direct element constructor              :)
  "ForScoreExpr-Var3",                     (:variable declaration                     :)
  "FTScope-q1",                            (: direct element constructor              :)
  "FTScope-q2",                            (: direct element constructor              :)
  "FTScope-q3",                            (: direct element constructor              :)
  "FTScope-q4",                            (: direct element constructor              :)
  "unconstrained-examples-364-5",          (: direct element constructor              :)
  "unconstrained-examples-364-5a",         (: direct element constructor              :)
  "FTScope-unconstrained-q1",              (: direct element constructor              :)
  "FTScope-unconstrained-q2",              (: direct element constructor              :)
  "FTScope-unconstrained-q3",              (: direct element constructor              :)
  "FTScope-unconstrained-q4",              (: direct element constructor              :)
  "ForScoreExpr-unconstrained-Var3",       (: variable declaration                    :)
  "Catalog001",                            (: direct element constructor              :)
  "Catalog002",                            (: direct element constructor              :)
  "Catalog003"                             (: direct element constructor              :)
);

declare variable $parse :=
  switch ()
  case $implementation eq "java" return
    switch ($language)
    case "xquery" return xquery-java:parse-Module#1
    case "xquery-full-text-update" return xquery-full-text-update-java:parse-Module#1
    case "xpath" return xpath-java:parse-XPath#1
    case "xpath-full-text" return xpath-full-text-java:parse-XPath#1
    default return error(xs:QName("process-tests"), "unsupported parser target language: " || $language)
  case $implementation eq "xquery" return
    switch ($language)
    case "xquery" return xquery-xquery:parse-Module#1
    case "xquery-full-text-update" return xquery-full-text-update-xquery:parse-Module#1
    case "xpath" return xpath-xquery:parse-XPath#1
    case "xpath-full-text" return xpath-full-text-xquery:parse-XPath#1
    default return error(xs:QName("process-tests"), "unsupported parser target language: " || $language)
  case matches($implementation, "^https?://") return local:parse#1
  default return error(xs:QName("process-tests"), "unsupported parser implementation: " || $implementation);

declare variable $filter := upper-case(substring($language, 1, 2)) || '(\d\d\+|40)';
declare variable $known-failures := if (contains($language, "xpath")) then $xpath-known-failures else $xquery-known-failures;

declare variable $expected-pass := 0;
declare variable $expected-fail := 1;
declare variable $unexpected-pass := 2;
declare variable $unexpected-fail := 3;
declare variable $skipped := 4;

declare function local:parse($input) {
  let $request :=
    <http:request method="POST">
      <http:header name="Accept" value="application/json"/>
      <http:body method="text" media-type="application/json">{json:serialize({"input": $input, "errorsOnly": true()})}</http:body>
    </http:request>
  let $response := http:send-request($request, $implementation)
  return
    if ($response[1]/@status = '200') then
      let $json := parse-json(json:serialize($response[2]))
      return
        if ($json?success) then
          ()
        else
          <ERROR>{json:serialize({"errors": $json?errors, "input": $json?input})}</ERROR>
    else
      error(xs:QName("local:parse"), json:serialize({
        'status': $response[1]/@status/string(),
        'message': $response[1]/@message/string(),
        'response': $response[2]
      }))
};

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
    catch *
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
    not(contains($language, "update")) and @type = "feature" and @value = "XQUpdate" and string(@satisfied) = ("", "true") or
    not(contains($language, "update")) and @type = "feature" and not(@value = "XQUpdate") and string(@satisfied) = 'false'
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
      $test-set/qtfc:test-case/qtfc:test/$skipped
};

declare function local:test-case($path, $test-case)
{
  if (not(local:supported($test-case))) then
    $test-case/qtfc:test/$skipped
  else
    let $expect-error := $test-case/qtfc:result//qtfc:error/@code = "XPST0003"
    for $test in $test-case/qtfc:test
    let $file := $test/@file
    let $query :=
      if ($file) then
        fn() {unparsed-text(resolve-uri($file, base-uri($test-case)))}
      else
        fn() {string($test)}
    return local:parse($path, $test-case/@name, $query, $expect-error)
};

declare function local:ftts-test($path, $test-case)
{
  if (contains($language, "xpath") and not(xs:boolean($test-case/@is-XPath2))) then
    $skipped
  else
    let $name := $test-case/@name
    let $test-suite := $test-case/ancestor::ftts:test-suite
    let $offset-path := $test-suite/@XQueryQueryOffsetPath
    let $extension := $test-suite/@XQueryFileExtension
    let $file := resolve-uri(concat($offset-path, $test-case/@FilePath, $test-case/ftts:query/@name, $extension), base-uri($test-case))
    let $query := fn() {
      let $query := unparsed-text($file)
      return
        if (contains($language, "xpath")) then
          replace($query, "^.*\(: insert-end :\)", "", "s")
        else
          $query
    }
    return
      local:parse($file, $name, $query, $test-case/@scenario eq "parse-error" or $test-case/ftts:expected-error = "XPST0003")  
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
      case $catalog as element(ftts:test-suite) return
        for $test-case in $catalog//ftts:test-case
        return
          if (contains($language, "full-text")) then
            local:ftts-test($path, $test-case)
          else
            $skipped
      case $test-set as element(qtfc:test-set) return
        local:test-set($path, $test-set)
      default return
        ()
    else if (contains($language, "xquery") and matches($path, "\.xq[^.]*$", "i")) then
      let $query := fn() {unparsed-text($path)}
      return local:parse($path, (), $query, false())
    else if (contains($language, "xpath") and matches($path, "\.xp[^.]*$", "i")) then
      let $query := fn() {unparsed-text($path)}
      return local:parse($path, (), $query, false())
    else 
      ()
};

declare function local:traverse($paths as xs:string*)
{
  for $path in $paths
  return
    if (not(file:is-dir($path))) then
      local:process(replace($path, "^\./", ""))
    else
      let $path := replace($path || "/", "[\\/][\\/]?", "/")
      for $entry in file:list($path)
        let $entry := $path || $entry
        where matches($entry, "([\\/]|\.(xml|xq.*))$", "i")
        return local:traverse($entry)
};

let $result := local:traverse(($root1, $root2))
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
