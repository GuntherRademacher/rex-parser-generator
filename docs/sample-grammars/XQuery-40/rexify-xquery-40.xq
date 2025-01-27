declare namespace g = "http://www.w3.org/2001/03/XPath/grammar";

import module namespace a = "de/bottlecaps/railroad/xq/cst-to-ast.xq" at
                            "https://raw.githubusercontent.com/GuntherRademacher/rr/refs/heads/basex/src/main/resources/de/bottlecaps/railroad/xq/cst-to-ast.xq";
import module namespace b = "de/bottlecaps/railroad/xq/ast-to-ebnf.xq" at
                            "https://raw.githubusercontent.com/GuntherRademacher/rr/refs/heads/basex/src/main/resources/de/bottlecaps/railroad/xq/ast-to-ebnf.xq";
import module namespace e = "de/bottlecaps/railroad/xq/html-to-ebnf.xq" at
                            "https://raw.githubusercontent.com/GuntherRademacher/rr/refs/heads/basex/src/main/resources/de/bottlecaps/railroad/xq/html-to-ebnf.xq";
import module namespace p = "Parser" at
                            "build/Parser.xquery";

(:~ The runtime environment time zone offset. :)
declare variable $tz-offset := - xs:integer(timezone-from-dateTime(current-dateTime()) div xs:dayTimeDuration('PT1M'));

(:~ The XQuery 4.0 grammar. :)
declare variable $xquery-grammar :=
  local:extract-grammar("https://qt4cg.org/specifications/xquery-40/xquery-40.html");

(:~ External grammars that contain productions referenced by the XQuery 4.0 grammar. :)
declare variable $external-grammars :=
(
  local:extract-grammar("https://www.w3.org/TR/REC-xml/"),
  local:extract-grammar("https://www.w3.org/TR/REC-xml-names/")
);

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

(:~ Productions in the grammar that are unused. :)
declare variable $obsolete-production-names :=
(
  "StringConstructorStart",
  "StringInterpolationStart",
  "StringInterpolationEnd",
  "StringConstructorEnd",
  "TagQName",
  "EndTagQName",
  "ProcessingInstructionStart",
  "ProcessingInstructionEnd",
  "DirCommentContentChar",
  "DirCommentContentDashChar"
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
  (: Add EOF to the end of the Module production. :)
  local:rule
  (
    function($node) {$node/self::g:production/@name = "Module"},
	function($node) {element g:production {$node/@*, $node/node(), <g:ref name="EOF"/>}}
  ),

  (: Remove obsolete productions, which are left over in the grammar, but not used any more. :)
  local:rule
  (
    function($node) {$node/self::g:production/@name = $obsolete-production-names},
	function($node) {text {"/*", $node/@name, "*/"}}
  ),
  
  (: Remove the "type" keyword from the NamedRecordTypeDecl production. It was inadvertently added
   : by https://github.com/qt4cg/qtspecs/commit/3c4ddb0d8e06321fabde5e5a6db97810d03a61a6
   :)
  local:rule
  (
    function($node) {$node/self::g:string[. eq "type"]/parent::g:production/@name = "NamedRecordTypeDecl"},
    function($node) {text {"/* type */"}}
  ),
  
  (: Rather than EQName, refer to token EQName^Token in production UnreservedName. EQName will be a
   : new nonterminal allowing EQName^Token as well as keywords. This is for allowing unreserved
   : keywords.
   :)
  local:rule
  (
    function($node) {$node/self::g:ref[@name eq "EQName"]/parent::g:production/@name = "UnreservedName"},
	function($node) {local:ast("_ ::= QName^Token | URIQualifiedName")/g:choice}
  ),
  
  (: Rather than NCName, refer to token NCName^Token in production UnreservedNCName. NCName will be a
   : new nonterminal allowing NCName^Token as well as keywords. This is for allowing unreserved
   : keywords.
   :)
  local:rule
  (
    function($node) {$node/self::g:ref[@name eq "NCName"]/parent::g:production/@name = "UnreservedNCName"},
	function($node) {<g:ref name="NCName" context="Token"/>}
  ),
  
  (: Prevent $reserved-function-names to be used as unqualified function names by replacing EQName
   : by new nonterminal UnreservedFunctionName in productions FunctionCall, FunctionDecl,
   : NamedFunctionRef, and ArrowStaticFunction. This basically implements extra-grammatical
   : constraint /* xgc: reserved-function-names */
   : (see https://qt4cg.org/specifications/xquery-40/xquery-40.html#extra-grammatical-constraints).
   : In ArrowStaticFunction, the annotation is missing in the spec, as pointed out in
   : https://github.com/qt4cg/qtspecs/issues/1716, but we still add it here to avoid the necessity
   : for unlimited lookahead, which REx cannot provide.
   :)   
  local:rule
  (
    function($node)
	{
	  $node/self::g:ref[@name eq "EQName"]/ancestor::g:production
	  /@name = ("FunctionCall", "FunctionDecl", "NamedFunctionRef", "ArrowStaticFunction")
	},
	function($node) {<g:ref name="UnreservedFunctionName"/>}
  ),
  
  (: Replace RelativePathExpr? in production PathExpr by an ordered choice between RelativePathExpr
   : and nothing. This implements extra-grammatical constraint /* xgc: leading-lone-slash */
   : (see https://qt4cg.org/specifications/xquery-40/xquery-40.html#extra-grammatical-constraints).
   :)
  local:rule
  (
    function($node) {$node/self::g:optional[count(*) eq 1 and g:ref/@name eq 'RelativePathExpr']/ancestor::g:production/@name = "PathExpr"},
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
   : can do LALR(2) in a matter of seconds, while LALR(3) takes more than half an hour.
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
    function($node) {$node/self::g:optional[count(*) eq 1 and g:ref/@name eq 'OccurrenceIndicator']/ancestor::g:production/@name = "SequenceType"},
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
	function($node) {text {"/*", $node/@name, "*/"}}
  ),

  (: Process the <?TOKENS?> separator, by adding some prodcutions to the syntax section preceding it,
   : and some more to the lexical section following it. This is addressing these problems:
   :  - whitespace and comment processing need to go to the syntax section, because the nested
   :    comments are non-regular and thus cannot be handled by the lexer generator, which is based
   :    on deterministic finite automata.   
   :  - non-reserved keywords are handled by preferring keywords over names in the lexer, but adding
   :    syntax level nonterminals for the names, providing alternatives over the tokenized names and
   :    keywords. These nonterminals have the same names as the tokens, so explicit token refrences
   :    are marked with the ^Token context in the syntax section.
   : In particular, the following is added to the syntax section:
   :  - nonterminal QName, with a choice between UnreservedFunctionName and reserved function names.
   :  - nonterminal UnreservedFunctionName, with a choice between QName^Token and keywords that are
   :    not reserved function names.
   :  - nonterminal NCName, with a choice between NCName^Token and keywords.
   :  - the Whitespace production: Whitespace ::= S^WS | Comment /* ws: definition */
   :  - the Comment production that originally was in the lexical section.
   : The following is added to the lexical section:
   :  - all productions containing an exclusion operator, some of which originally occured in the 
   :    syntax section, except for CommentContents, which needs a replacement.
   :  - the replacement for CommentContents, that adds lexical lookahead in order to prevent the
   :    greedy lexer from comsuming a comment terminator or a nested comment introducer.
   :  - the Wildcard production from the syntax section
   :  - an EOF production
   :  - a preference for Wildcard over "*" for parser states where both are expected. This has been
   :    taken over from the XQuery 3.1 grammar and might need to be re-checked.
   :  - preferences for all keywords over QName and NCName.
   :)
  local:rule
  (
    function($node) {$node instance of processing-instruction(TOKENS)},
	function($node as node())
	{
	  let $grammar := root($node)
	  let $keywords := local:keywords($grammar)
	  return
	  (
        <g:production name="QName">
          <g:choice>
            <g:ref name="UnreservedFunctionName"/>
            {$reserved-function-names!element g:string {.}}
          </g:choice>
        </g:production>,
        <g:production name="UnreservedFunctionName">
          <g:choice>
            <g:ref name="QName" context="Token"/>
            {$keywords[not(. = $reserved-function-names)]!element g:string {.}}
          </g:choice>
        </g:production>,
        <g:production name="NCName">
          <g:choice>
            <g:ref name="NCName" context="Token"/>
            {$keywords!element g:string {.}}
          </g:choice>
        </g:production>,
		local:ast("Whitespace ::= S^WS | Comment /* ws: definition */"),
		$grammar/g:production[@name = "Comment"],
		
        $node, (: i.e. the <?TOKENS?> separator:)
		
		$grammar/g:production[exists(.//g:subtract) and not(@name = ("CommentContents", $obsolete-production-names))],
	    local:ast("CommentContents
			::= ( ( Char+ - ( Char* ( '(:' | ':)' ) Char* ) ) - ( Char* '(' ) ) &amp;':'
			  | ( Char+ - ( Char* ( '(:' | ':)' ) Char* ) ) &amp;'('"),
		$grammar/g:production[@name = "Wildcard"],
		local:ast("EOF ::= $"),
        element g:preference {element g:string{'*'}, <g:ref name="Wildcard"/>},
		let $keywords := local:keywords($grammar)
    	return
	    (
          $keywords!element g:preference {<g:ref name="QName" context="Token"/>, element g:string{.}},
          $keywords!element g:preference {<g:ref name="NCName" context="Token"/>, element g:string{.}}
        )
	  )
	}
  )
);

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
      let $nodes := local:include-external-productions($node/node())
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
declare function local:ast($ebnf as xs:string) as element(g:production)*
{
  a:ast(p:parse-Grammar($ebnf))/g:production
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

(:~ Collect the sequence of keywords of a grammar.
 :
 : @param $grammar the grammar
 : @return the sequence of keywords
 :)
declare function local:keywords($grammar as element(g:grammar)) as xs:string*
{
  let $tokens-separator := $grammar//processing-instruction(TOKENS)
  let $syntax := $grammar/*[. << $tokens-separator]
  for $keyword in distinct-values($syntax//g:string[matches(., "^[a-zA-Z].*$")])
  order by $keyword
  return $keyword
};

concat
(
  $xquery-grammar/comment()
  => replace("\*/", "* and transformed by " || resolve-uri("") => replace(".*/", "") || "&#xA; */"), 

  $xquery-grammar/g:grammar
  => local:include-external-productions()
  => local:rewrite()
  => local:depth-first()
  => b:render()
)