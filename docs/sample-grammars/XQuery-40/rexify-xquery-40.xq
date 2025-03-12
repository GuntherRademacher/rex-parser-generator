declare namespace g = "http://www.w3.org/2001/03/XPath/grammar";

import module namespace a = "de/bottlecaps/railroad/xq/cst-to-ast.xq" at
                            "https://raw.githubusercontent.com/GuntherRademacher/rr/refs/heads/basex/src/main/resources/de/bottlecaps/railroad/xq/cst-to-ast.xq";
import module namespace b = "de/bottlecaps/railroad/xq/ast-to-ebnf.xq" at
                            "https://raw.githubusercontent.com/GuntherRademacher/rr/refs/heads/basex/src/main/resources/de/bottlecaps/railroad/xq/ast-to-ebnf.xq";
import module namespace e = "de/bottlecaps/railroad/xq/html-to-ebnf.xq" at
                            "https://raw.githubusercontent.com/GuntherRademacher/rr/refs/heads/basex/src/main/resources/de/bottlecaps/railroad/xq/html-to-ebnf.xq";
import module namespace p = "de/bottlecaps/railroad/xq/ebnf-parser.xquery" at
                            "https://raw.githubusercontent.com/GuntherRademacher/rr/refs/heads/basex/src/main/resources/de/bottlecaps/railroad/xq/ebnf-parser.xquery";

(:~ The specification URL. :)
declare variable $specification-url external;

(:~ The specification grammar. :)
declare variable $specification-grammar := local:extract-grammar($specification-url);

(:~ External grammars that contain productions referenced by the specification grammar. :)
declare variable $external-grammars :=
(
  local:extract-grammar("https://www.w3.org/TR/REC-xml/"),
  local:extract-grammar("https://www.w3.org/TR/REC-xml-names/")
);

(:~ The runtime environment time zone offset. :)
declare variable $tz-offset := - xs:integer(timezone-from-dateTime(current-dateTime()) div xs:dayTimeDuration('PT1M'));

(:~ Reserved function names. :)
declare variable $reserved-function-names :=
(
  'attribute',
  'comment',
  'document-node',
  'element',
  'namespace-node',
  'node',
  'schema-attribute',
  'schema-element',
  'processing-instruction',
  'text',
  'fn',
  'function',
  'if',
  'switch',
  'typeswitch'
);

(:~
 : This is the structure of a rewriting rule:
 : - condition: a condition that tells whether this rule applies to some node
 : - action: the action that calculates the replacement for the node
 :)
declare record local:rule
(
  condition as fn(node()) as xs:boolean,
  action as fn(node()) as node()+
);

(:~ The actual rewriting rules. :)
declare variable $rules as local:rule+ :=
(
  (: Remove "ItemType" from "TypeSpecifier" in order to avoid ambiguities as reported in
   : https://github.com/qt4cg/qtspecs/issues/1866
   :)
  local:rule
  (
    function($node)
    {
      $node/self::g:production/@name = "TypeSpecifier" and
      deep-equal($node, local:ast("TypeSpecifier ::= '~' ( ItemType | '(' SequenceType ')' )"))
    },
    function($node) {local:ast("TypeSpecifier ::= '~' '(' SequenceType ')'")}
  ),
  
  (: Add context "DirElemConstructor" to "<" introducing a direct element constructor. This serves
   : for distinguishing it from a "<" operator in a general comparison.
   :)
  local:rule
  (
    function($node) {$node/self::g:string[ancestor::g:production/@name eq "DirElemConstructor"] = "<"},
    function($node) {<g:string context="DirElemConstructor">&lt;</g:string>}
  ),
  
  (: Add context "GeneralComp" to "<" in a general comparison. This serves for distinguishing it
   : from a "<" operator introducing a direct element constructor.
   :)
  local:rule
  (
    function($node) {$node/self::g:string[ancestor::g:production/@name eq "GeneralComp"] = "<" and root($node)//g:production/@name = "DirElemConstructor"},
    function($node) {element g:choice {<g:string context="GeneralComp">&lt;</g:string>, element g:string {"&#xFF1C;"}}}
  ),
  
  (: Prevent $reserved-function-names to be used as unqualified function names by replacing EQName
   : by new nonterminal UnreservedFunctionEQName in productions FunctionCall, FunctionDecl, and
   : NamedFunctionRef. This basically implements extra-grammatical constraint
   : /* xgc: reserved-function-names */
   : (see https://qt4cg.org/specifications/xquery-40/xquery-40.html#extra-grammatical-constraints).
   :)
  local:rule
  (
    function($node)
    {
      $node/self::g:ref[@name eq "EQName"]/ancestor::g:production
      /@name = ("FunctionCall", "FunctionDecl", "NamedFunctionRef")
    },
    function($node) {<g:ref name="UnreservedFunctionEQName"/>}
  ),

  (: Replae "UnreservedName ::= EQName" by "UnreservedName ::= UnreservedQName | URIQualifiedName".
   : UnreservedQName will be added as a new token that disallows reserved names.
   :)
  local:rule
  (
    function($node) {$node/self::g:ref[@name eq "EQName"]/parent::g:production/@name = "UnreservedName"},
    function($node) {local:ast("_ ::= UnreservedQName | URIQualifiedName")/g:choice}
  ),

  (: Remove production UnreservedNCName. This is done because the NCName token will be renamed to
   : UnreservedNCName, and an NCName production will be added that combines UnreservedNCName with
   : the keywords.
   :)
  local:rule
  (
    function($node) {$node/self::g:production/@name = "UnreservedNCName"},
    function($node) {text {""}}
  ),

  (: Replace RelativePathExpr? in production PathExpr by an ordered choice between RelativePathExpr
   : and nothing. This implements extra-grammatical constraint /* xgc: leading-lone-slash */
   : (see https://qt4cg.org/specifications/xquery-40/xquery-40.html#extra-grammatical-constraints).
   :
   : The changes made in
   :)
  local:rule
  (
    function($node)
    {
      $node/self::g:optional[count(*) eq 1 and g:ref/@name eq 'RelativePathExpr']
      /ancestor::g:production/@name = "PathExpr"
    },
    function($node) {local:ast("_ ::= RelativePathExpr /")/g:orderedChoice}
  ),

  (: Replace the production "PositionalArguments ::= (Argument ++ ',')", or rather
   : "PositionalArguments ::= Argument (',' Argument)*" (after resolution of the "++" operator),
   : by the left-recursive variant
   : "PositionalArguments ::= Argument | PositionalArguments ',' Argument".
   : This reduces the necessary lookahead from 3 to 2. The original requires a reduction to
   : PositionalArguments when moving on from positional to keyword arguments, which cannot be done
   : without looking ahead at least 3 tokens, the comma, a QName, and a ":=" operator. With the
   : replacement, there is a different distribution over parser states, and we can get away with
   : a lookahead of 2. This is important because on this grammar, with keywords not reserved, REx
   : can do LALR(2) in a matter of seconds, while LALR(3) takes about half an hour.
   :)
  local:rule
  (
    function($node)
    {
      $node/self::g:production
      [count(*) eq 2
       and *[1]/self::g:ref/@name eq "Argument"
       and *[2]/self::g:zeroOrMore[count(*) eq 2
                                   and *[1]/self::g:string eq ","
                                   and *[2]/self::g:ref/@name eq "Argument"]
      ]/@name = "PositionalArguments"
    },
    function($node) {local:ast("PositionalArguments ::= Argument | PositionalArguments ',' Argument")}
  ),

  (: Replace OccurrenceIndicator? in production SequenceType by an ordered choice between
   : OccurrenceIndicator and nothing. This implements extra-grammatical constraint
   : /* xgc: occurrence-indicators */
   : (see https://qt4cg.org/specifications/xquery-40/xquery-40.html#extra-grammatical-constraints).
   :)
  local:rule
  (
    function($node)
    {
      $node/self::g:optional[count(*) eq 1 and g:ref/@name eq 'OccurrenceIndicator']
      /ancestor::g:production/@name = "SequenceType"
    },
    function($node) {local:ast("_ ::= OccurrenceIndicator /")/g:orderedChoice}
  ),

  (: Remove productions containing an exclusion operator "-", and Wildcard, from their original
   : lcoation in the syntax section of the grammar. The will be placed in the lexical section by
   : the rule that processes the <?TOKENS?> separator. Also remove Comment from the its original
   : location in the lexical section, the <?TOKENS?> rule will add it to the syntax section.
   :)
  local:rule
  (
    function($node) {exists($node/self::g:production[@name = ("Wildcard", "Comment") or .//g:subtract])},
    function($node) {text {""}}
  ),

  (: Rewrite StringInterpolation to use EnclosedExpr rather than Expr with tokens '`{' and '}`'. :)
  local:rule
  (
    function($node)
    {
      $node/self::g:production/@name = "StringInterpolation"
      and count($node/*) eq 3
      and $node/g:string = '`{'
      and $node/g:string = '}`'
      and $node/g:optional[count(*) eq 1]/g:ref/@name = "Expr"
    },
    function($node) {local:ast("StringInterpolation ::= '`' EnclosedExpr '`'")}
  ),

  (: Add alternative representation of operators containing "<" or ">" using the full-width versions
   : of these characters.
   :)
  local:rule
  (
    function($node) {$node/self::g:string and exists(local:full-width-operators($node))},
    function($node) {element g:choice {$node, local:full-width-operators($node)!element g:string {.}}}
  ),

  (: Process the <?TOKENS?> separator, by adding some prodcutions to the syntax section preceding
   : it, and some more to the lexical section following it. Whitespace and comment processing need
   : to go to the syntax section, because the nested comments are non-regular and thus cannot be
   : handled by the lexer generator, which is based on deterministic finite automata. For allowing
   : keywords as names, productions are added to the syntax section, providing a choice over the
   : non-reserved name tokens and the keywords. In the lexical section, the name productions are
   : modified to exclude keywords.
   :)
  local:rule
  (
    function($node) {$node instance of processing-instruction(TOKENS)},
    function($node as node())
    {
      let $grammar := root($node)
      let $keywords := local:keywords($grammar)
      let $full-width-operators := local:full-width-operators($grammar)
      return
      (
        (: Add new production UnreservedFunctionEQName for restricting valid function names. :)
        local:ast("UnreservedFunctionEQName ::= UnreservedFunctionQName | URIQualifiedName"),

        (: Add a QName production providing a choice of unreserved and reserved function names. :)
        <g:production name="QName">
          <g:choice>
            <g:ref name="UnreservedFunctionQName"/>
            {$reserved-function-names!element g:string {.}}
          </g:choice>
        </g:production>,

        (: Add an UnreservedFunctionQName production providing a choice of unreserved QNames
         : and keywords.
         :)
        <g:production name="UnreservedFunctionQName">
          <g:choice>
            <g:ref name="UnreservedQName"/>
            {$keywords[not(. = $reserved-function-names)]!element g:string {.}}
          </g:choice>
        </g:production>,

        (: Add an NCQName production providing a choice of unreserved NCNames and keywords. :)
        <g:production name="NCName">
          <g:choice>
            <g:ref name="UnreservedNCName"/>
            {$keywords!element g:string {.}}
          </g:choice>
        </g:production>,

        (: Add the Whitespace production. :)
        local:ast("Whitespace ::= S^WS | Comment /* ws: definition */"),

        (: Move the Comment production from the lexical section. :)
        $grammar/g:production[@name = "Comment"],

        (: The <?TOKENS?> separator, the lexical section begins here. :)
        $node,

        (: Introduce the UnreservedQName token, excluding keywords from the QName fragment. :)
        local:ast("UnreservedQName ::= QName - ReservedName"),

        (: Introduce the UnreservedNCName token, excluding keywords from the NCName fragment. :)
        local:ast("UnreservedNCName ::= NCName - ReservedName"),

        (: Add the ReservedName fragment, enumerating the keywords in a choice operator. :)
        element g:production
        {
          attribute name {"ReservedName"}, element g:choice {$keywords!element g:string {.}}
        },

        (: Move Wildcard from the syntax section. :)
        $grammar/g:production[@name = "Wildcard"],

        (: Move all production using an exclusion operator from the syntax section, except for those
         : that need additional changes.
         :)
        $grammar/g:production[exists(.//g:subtract) and not(@name = ("CDataSectionContents", "DirPIContents", "PragmaContents", "StringConstructorChars", "CommentContents", "StringTemplateFixedPart", "PITarget"))],

        (: Add lexical lookahead to CDataSectionContents. :)
        local:lookahead("CDataSectionContents", element g:string {"]]"}),

        (: Add lexical lookahead to DirPIContents. :)
        local:lookahead("DirPIContents", element g:string {"?"}),

        (: Add lexical lookahead to PragmaContents. :)
        local:lookahead("PragmaContents", element g:string {"#"}),

        (: Add lexical lookahead to StringConstructorChars. :)
        local:lookahead
        (
          "StringConstructorChars",
          element g:choice {element g:string {"`{"}, element g:string {"]`"}}
        ),

        (: In PITarget, if present, replace Name by NCName. :)
        let $pi-target := $grammar/g:production[@name eq "PITarget"]
        where $pi-target
        return local:ast(replace(b:render($pi-target), "Name", "NCName")),

        (: Avoid the "`{" and "}`" operators in StringTemplateFixedPart by using EnclosedExpr. :)
        let $string-template-fixed-art := $grammar/g:production[@name = "StringTemplateFixedPart"]
        return element g:production {$string-template-fixed-art/@*, element g:oneOrMore {$string-template-fixed-art/g:zeroOrMore/node()}},

        (: Rewrite CommentContents to use the necessary lexical lookahead. :)
        let $comment-contents := $grammar/g:production[@name = "CommentContents"]
        let $nodes := $comment-contents/node()
        return
          element g:production
          {
            $comment-contents/@*,
            element g:choice
            {
              element g:context {element g:subtract {$nodes, element g:sequence { element g:zeroOrMore { element g:ref {attribute name {"Char"}}}, element g:string {"("}}}, element g:string {':'}},
              element g:context {$nodes, element g:string {'('}}
            }
          },

        (: Add an EOF production. :)
        local:ast("EOF ::= $"),

        (: Add fragment QNameOrKeywordDelimiter for being used as lexical lookahead. :)
        local:ast("QNameOrKeywordDelimiter ::= $ | ':' | Char - NameChar"),

        (: Add fragment NCNameDelimiter for being used as lexical lookahead. :)
        local:ast("NCNameDelimiter ::= $ $ | ( Char - NameChar ) ( $ | Char ) | ':' ( Char - NameStartChar )"),

        (: Add fragment NumericLiteralDelimiter for being used as lexical lookahead. :)
        local:ast("NumericLiteralDelimiter ::= QNameOrKeywordDelimiter | '-'"),

        (: Add a lexer preference for Wildcard over "*". :)
        element g:preference {element g:string{'*'}, <g:ref name="Wildcard"/>},

        (: Add lexical lookahead for QNames. :)
        ("UnreservedQName")                                       !element g:delimiter {<g:ref name="QNameOrKeywordDelimiter"/>, <g:ref name="{.}"/>},

        (: Add lexical lookahead for full-width operators. :)
        ($full-width-operators[matches(., "^[&#xFF1C;&#xFF1E;]")])!element g:delimiter {<g:ref name="Char"/>,                    element g:string {.}},

        (: Add lexical lookahead for operators starting with "<". :)
        ("</", "<<", "<=")[contains($grammar, .)]                 !element g:delimiter {<g:ref name="Char"/>,                    element g:string {.}},

        (: Add lexical lookahead for NCNames. :)
        ("UnreservedNCName")                                      !element g:delimiter {<g:ref name="NCNameDelimiter"/>,         <g:ref name="{.}"/>},

        (: Add lexical lookahead for numeric literals. :)
        ("DecimalLiteral", "DoubleLiteral", "IntegerLiteral")     !element g:delimiter {<g:ref name="NumericLiteralDelimiter"/>, <g:ref name="{.}"/>},

        (: Add lexical lookahead for keywords. :)
        ($keywords[not(matches(., "^[&#xFF1C;&#xFF1E;]"))])       !element g:delimiter {<g:ref name="QNameOrKeywordDelimiter"/>, element g:string {.}},

        (: Add lexical lookahead for "<". :)
        if (not($grammar//g:production/@name = "DirElemConstructor")) then
          element g:delimiter {<g:ref name="Char"/>, element g:string {"<"}}
        else
        (
          local:ast("GeneralCompDelimiter ::= [^?]"),
          local:ast("DirElemConstructorDelimiter ::= QName ( S QName S? '=' | S? [/>] )"),
          element g:delimiter {<g:ref name="GeneralCompDelimiter"/>, <g:string context="GeneralComp">&lt;</g:string>},
          element g:delimiter {<g:ref name="DirElemConstructorDelimiter"/>, <g:string context="DirElemConstructor">&lt;</g:string>}
        )
      )
    }
  ),

  (: Add EOF to the end of the Module or XPath production. :)
  local:rule
  (
    function($node) {$node/self::g:production/@name = ("Module", "XPath")},
    function($node) {element g:production {$node/@*, $node/node(), <g:ref name="EOF"/>}}
  )

);

(:~
 : Add lexical lookahead to a production.
 : @param $name production name
 : @param $lookahead lexical lookahead
 :)
declare function local:lookahead($name as xs:string, $lookahead as node()) as element(g:production)?
{
  let $nodes := $specification-grammar//g:production[@name eq $name]/*
  where $nodes
  return
    element g:production
    {
      attribute name {$name},
      element g:context
      {
        if (count($nodes) eq 1) then $nodes else element g:sequence {$nodes},
        $lookahead
      }
    }
};

(:~
 : Find the first matching one in a sequence of rules to a given node and apply its action to the
 : node.
 :
 : @param $node the node
 : @param $the rules#
 : @return the node, or the replacement, if any
 :)
declare function local:rewrite($node as node(), $todo as local:rule*) as node()*
{
  if (empty($todo)) then
    ()
  else
    let $rule := $todo[1]
    return
      if ($rule?condition($node)) then
        $rule?action($node)
      else
        local:rewrite($node, subsequence($todo, 2))
};

(:~
 : Traverse a the subtrees spanned by a sequence of nodes, applying the rewriting rules to each
 : node.
 :
 : @param $nodes the node sequence
 : @return $the rewritten nodes
 :)
declare function local:rewrite($nodes as node()*) as node()*
{
  for $node in $nodes
  let $replacement := local:rewrite($node, $rules)
  return
    if (exists($replacement)) then
      $replacement
    else
      typeswitch ($node)
      case document-node() return document {local:rewrite($node/node())}
      case element() return element {node-name($node)} {local:rewrite(($node/@*, $node/node()))}
      default return $node
};

(:~
 : Extract an EBNF grammar from a W3 document, parse it, and transform the parse tree to the
 : grammar's XML representation.
 :
 : @param $uri the URI of the spec containing the spec
 : @return the grammar
 :)
declare function local:extract-grammar($uri as xs:string) as document-node()
{
  let $extract := e:extract($uri, html:parse(unparsed-text($uri)), $tz-offset)
  let $parse := p:parse-Grammar(string($extract))
  return document {comment {$extract/text()[1]}, a:ast($parse)}
};

(:~
 : For a given sequence of production names, collect the corresponding productions
 : from $external-grammars, along with all referenced productions.
 :
 : @param $done the partial result, empty in the initial call, but used in tail calls
 : @param $todo the sequence of names of production to be collected
 : @return the collected sequence production elements
 :)
declare function local:collect-external-productions(
    $done as element(g:production)*,
    $todo as xs:string*) as element(g:production)*
{
  if (empty($todo)) then
    $done
  else
    let $name := $todo[1]
    let $todo := subsequence($todo, 2)
    return
      if ($done/self::g:production[@name eq $name]) then
        local:collect-external-productions($done, $todo)
      else
        let $p := $external-grammars/g:grammar/g:production[@name eq $name]
        return
          if (empty($p)) then
            error(xs:QName("local:collect-external-productions"), concat("missing nonterminal: ", $name))
          else if (count($p) gt 1) then
            error(xs:QName("local:collect-external-productions"), concat("multiple definitions found for: ", $name))
          else
            local:collect-external-productions(($done, $p), ($p//g:ref/@name, $todo))
};

(:~
 : Rewrite a sequence of nodes, including any referenced external productions in place of
 : g:production[@xhref].
 :
 : @param $nodes the input node sequence
 : @return a sequence of nodes made up of the rewritten node and the possibly inlined
 :         productions from external grammars
 :)
declare function local:include-external-productions($nodes as node()*) as node()*
{
  for $node in $nodes
  return
    typeswitch ($node)
    case document-node() return
      error()
    case element(g:grammar) return
      let $nodes :=
        local:include-external-productions
        ((
          $node/node(),
          (: the following is needed, but possibly only referenced in extra-grammatical text :)
          $external-grammars//g:production[@name eq "S"]
        ))
      return
        element g:grammar
        {
          for $node in $nodes
          where not($node/self::g:production) or empty($nodes[. << $node and @name eq $node/@name and deep-equal(., $node)])
          return $node
        }
    case element() return
      let $xhref := $node/@xhref
      let $elements :=
        if (empty($xhref)) then
          $node
        else if (starts-with($xhref, "http://www.w3.org/TR/REC-xml#NT-")) then
          local:collect-external-productions((), $node/@name)
        else if (starts-with($xhref, "http://www.w3.org/TR/REC-xml-names/#NT-")) then
          local:collect-external-productions((), $node/@name)
        else
          error(xs:QName("local:include-external-productions"), concat("unexpected xhref attribute: ", $xhref))
      for $e in $elements
      return element {node-name($e)} {$e/@*, local:include-external-productions($e/node())}
    default
      return $node
};

(:~ Parse an EBNF grammar fragment and return its XML representation.
 :
 : @param $ebnf the grammar fragment
 : @return the XML representation
 :)
declare function local:ast($ebnf as xs:string) as element(g:*)*
{
  a:ast(p:parse-Grammar($ebnf))/g:*
};

(:~ Establish depth first order of a sequence of productions.
 :
 : @param $done a partial result, empty on the intial call
 : @param $todo the productions to be ordered
 : @return the ordered sequence of productions
 :)
declare function local:depth-first(
    $done as element(g:production)*,
    $todo as element(g:production)*) as element(g:production)*
{
  if (empty($todo)) then
    $done
  else
    let $production := $todo[1]
    let $others := subsequence($todo, 2)
    let $refs := distinct-values($production//g:ref[empty(@context)]/string(@name))
    return
      local:depth-first
      (
        ($done, $production),
        (
          for $ref in $refs return $others[@name eq $ref],
          $others[not(@name = $refs)]
        )
      )
};

(:~ Transform a grammar such that its productions occur in depth-first order.
 :
 : @param $grammar the grammar
 : @return the transformed grammar with productions in depth first order
 :)
declare function local:depth-first($grammar as element(g:grammar))
{
   let $separator := $grammar//processing-instruction(TOKENS)
   let $syntax := $grammar/g:production[not(. >> $separator)]
   let $tokens := $grammar/g:production[. >> $separator]
   let $start :=
     for $production in $syntax
     let $refs := $syntax//g:ref[@name eq $production/@name and empty(@context)]
     where empty($refs)
     return $production
   let $syntax := local:depth-first((), ($start, $syntax[not(@name = $start/@name)]))
   let $used-tokens :=
     for $name in distinct-values
     (
       for $ref in $syntax//g:ref
       let $name := string($ref/@name)
       where exists($ref/@context) or empty($syntax[@name = $name])
       return $name
     )
     return $tokens[@name = $name]
   let $tokens := local:depth-first((), ($used-tokens, $tokens[not(@name = $used-tokens/@name)]))
   return
     <g:grammar>{
       $syntax,
       $separator,
       $tokens,
       $grammar/*[not(self::g:production)]
     }</g:grammar>
};

(:~
 : Calculate additional full-width operators for operators containing a less-than or greater-than
 : character.
 :
 : @param nodes the grammar fragment where to search for original operators
 : @return the corresponding full-width operators
 :)
declare function local:full-width-operators($nodes as element()+) as xs:string*
{
  distinct-values
  (
    $nodes/descendant-or-self::g:string
    [ancestor::g:production/@name ne "DirElemConstructor" and . = ("<", "<=", ">", ">=", "<<", ">>", "=>", "->", "=!>", "=?>")]
  )
  !replace(replace(., "<", "&#xFF1C;"), ">", "&#xFF1E;")
};

(:~ Collect the sequence of keywords of a grammar.
 :
 : @param $grammar the grammar
 : @return the sequence of keywords
 :)
declare function local:keywords($grammar as element(g:grammar)) as xs:string*
{
  let $tokens-separator := $grammar//processing-instruction(TOKENS)
  let $syntax := $grammar/*[. << $tokens-separator]
  for $keyword in
    distinct-values((
      $syntax//g:string[matches(., "^[a-zA-Z].*$")],
      $reserved-function-names,
      local:full-width-operators($grammar)[matches(., "^[&#xFF1C;&#xFF1E;]+$")]
    ))
  order by $keyword
  return $keyword
};

concat
(
  $specification-grammar/comment()
  => replace("\*/", "* and transformed by " || resolve-uri("") => replace(".*/", "") || "&#xA; */"),

  $specification-grammar/g:grammar
  => local:include-external-productions()
  => local:rewrite()
  => local:depth-first()
  => b:render()
)