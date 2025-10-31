declare namespace g = 'http://www.w3.org/2001/03/XPath/grammar';
declare namespace xhtml = 'http://www.w3.org/1999/xhtml';

import module namespace u = 'unify-grammar.xq' at 'unify-grammar.xq';
import module namespace b = 'de/bottlecaps/railroad/xq/ast-to-ebnf.xq' at
                            'https://raw.githubusercontent.com/GuntherRademacher/rr/refs/heads/basex/src/main/resources/de/bottlecaps/railroad/xq/ast-to-ebnf.xq';

(:~ The specification URL. :)
declare variable $specification-url external;

(:~ Whether to include XQuery Update Facility 3.0 :)
declare variable $with-update as xs:boolean external := false();

(:~ Whether to include XQuery and XPath Full Text 3.0 :)
declare variable $with-full-text as xs:boolean external := false();

(:~ Whether to include BaseX specialties :)
declare variable $with-basex as xs:boolean external := false();

(:~ Reserved function names. :)
declare variable $reserved-function-names :=
  let $names := html-doc($specification-url)
    //@id[. = 'id-reserved-fn-names']
    /ancestor-or-self::xhtml:div[1]
    //xhtml:blockquote
    /xhtml:p
    /text()
    /string()
  return
    if (exists($names)) then
      $names
    else
      error(xs:QName('reserved-function-names'), 'failed to retrieve reserved function names');

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
  (: Add context 'DirElemConstructor' to '<' introducing a direct element constructor. This serves
   : for distinguishing it from a '<' operator in a general comparison.
   :)
  local:rule
  (
    function($node) {$node/self::g:string[ancestor::g:production/@name eq 'DirElemConstructor'] = '<'},
    function($node) {<g:string context='DirElemConstructor'>&lt;</g:string>}
  ),
  
  (: Add context 'GeneralComp' to '<' in a general comparison. This serves for distinguishing it
   : from a '<' operator introducing a direct element constructor.
   :)
  local:rule
  (
    function($node) {$node/self::g:string[ancestor::g:production/@name eq 'GeneralComp'] = '<' and root($node)//g:production/@name = 'DirElemConstructor'},
    function($node) {<g:string context='GeneralComp'>&lt;</g:string>}
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
      $node/self::g:ref[@name eq 'EQName']/ancestor::g:production
      /@name = ('FunctionCall', 'FunctionDecl', 'NamedFunctionRef')
    },
    function($node) {<g:ref name='UnreservedFunctionEQName'/>}
  ),

  (: Replace 'UnreservedName ::= EQName' by 'UnreservedName ::= UnreservedQName | URIQualifiedName'.
   : UnreservedQName will be added as a new token that disallows reserved names.
   :)
  local:rule
  (
    function($node) {$node/self::g:ref[@name eq 'EQName']/parent::g:production/@name = 'UnreservedName'},
    function($node) {u:ast('_ ::= UnreservedQName | URIQualifiedName')/g:choice}
  ),

  (: Remove production UnreservedNCName. This is done because the NCName token will be renamed to
   : UnreservedNCName, and an NCName production will be added that combines UnreservedNCName with
   : the keywords.
   :)
  local:rule
  (
    function($node) {$node/self::g:production/@name = 'UnreservedNCName'},
    function($node) {text {''}}
  ),

  (: Replace RelativePathExpr? in production AbsolutePathExpr by an ordered choice between RelativePathExpr
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
      /ancestor::g:production/@name = 'AbsolutePathExpr'
    },
    function($node) {u:ast('_ ::= RelativePathExpr /')/g:orderedChoice}
  ),

  (: Replace the production "PositionalArguments ::= (Argument ++ ',')", or rather
   : "PositionalArguments ::= Argument (',' Argument)*" (after resolution of the '++' operator),
   : by the left-recursive variant
   : "PositionalArguments ::= Argument | PositionalArguments ',' Argument".
   : This reduces the necessary lookahead from 3 to 2. The original requires a reduction to
   : PositionalArguments when moving on from positional to keyword arguments, which cannot be done
   : without looking ahead at least 3 tokens, the comma, a QName, and a ':=' operator. With the
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
       and *[1]/self::g:ref/@name eq 'Argument'
       and *[2]/self::g:zeroOrMore[count(*) eq 2
                                   and *[1]/self::g:string eq ','
                                   and *[2]/self::g:ref/@name eq 'Argument']
      ]/@name = 'PositionalArguments'
    },
    function($node) {u:ast("PositionalArguments ::= Argument | PositionalArguments ',' Argument")}
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
      /ancestor::g:production/@name = 'SequenceType'
    },
    function($node) {u:ast('_ ::= OccurrenceIndicator /')/g:orderedChoice}
  ),

  (: Remove productions containing an exclusion operator '-', and Wildcard, from their original
   : lcoation in the syntax section of the grammar. The will be placed in the lexical section by
   : the rule that processes the <?TOKENS?> separator. Also remove Comment from the its original
   : location in the lexical section, the <?TOKENS?> rule will add it to the syntax section.
   :)
  local:rule
  (
    function($node) {exists($node/self::g:production[@name = ('Wildcard', 'Comment') or .//g:subtract])},
    function($node) {text {''}}
  ),

  (: Rewrite StringInterpolation to use EnclosedExpr rather than Expr with tokens '`{' and '}`'. :)
  local:rule
  (
    function($node)
    {
      $node/self::g:production/@name = 'StringInterpolation'
      and empty($node/@whitespace-spec)
      and count($node/*) eq 3
      and $node/g:string = '`{'
      and $node/g:string = '}`'
      and $node/g:optional[count(*) eq 1]/g:ref/@name = 'Expr'
    },
    function($node) {u:ast("StringInterpolation ::= '`' EnclosedExpr '`' /*ws: explicit*/")}
  ),

  (: Replace choice by orderedChoice for BaseX' else-less if :)
  local:rule(
    function($node) {$node/self::g:choice/ancestor::g:production/@name = ("UnbracedActions", "BracedActions")},
    function($node) {element g:orderedChoice {$node/*}}
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
      let $grammar := root($node)/g:grammar
      let $keywords := local:keywords($grammar)
      return
      (
        (: Add new production UnreservedFunctionEQName for restricting valid function names. :)
        u:ast('UnreservedFunctionEQName ::= UnreservedFunctionQName | URIQualifiedName'),

        (: Add a QName production providing a choice of unreserved and reserved function names. :)
        <g:production name='QName'>
          <g:choice>
            <g:ref name='UnreservedFunctionQName'/>
            {$reserved-function-names!element g:string {.}}
          </g:choice>
        </g:production>,

        (: Add an UnreservedFunctionQName production providing a choice of unreserved QNames
         : and keywords.
         :)
        <g:production name='UnreservedFunctionQName'>
          <g:choice>
            <g:ref name='UnreservedQName'/>
            {$keywords[not(. = $reserved-function-names)]!element g:string {.}}
          </g:choice>
        </g:production>,

        (: Add an NCQName production providing a choice of unreserved NCNames and keywords. :)
        <g:production name='NCName'>
          <g:choice>
            <g:ref name='UnreservedNCName'/>
            {$keywords!element g:string {.}}
          </g:choice>
        </g:production>,

        (: Add the Whitespace production. :)
        u:ast('Whitespace ::= S^WS | Comment /* ws: definition */'),

        (: Move the Comment production from the lexical section. :)
        $grammar/g:production[@name = 'Comment'],

        (: The <?TOKENS?> separator, the lexical section begins here. :)
        $node,

        (: Introduce the UnreservedQName token, excluding keywords from the QName fragment. :)
        u:ast('UnreservedQName ::= QName - ReservedName'),

        (: Introduce the UnreservedNCName token, excluding keywords from the NCName fragment. :)
        u:ast('UnreservedNCName ::= NCName - ReservedName'),

        (: Add the ReservedName fragment, enumerating the keywords in a choice operator. :)
        element g:production
        {
          attribute name {'ReservedName'}, element g:choice {$keywords!element g:string {.}}
        },

        (: Move Wildcard from the syntax section. :)
        $grammar/g:production[@name = 'Wildcard'],

        (: Move all production using an exclusion operator from the syntax section, except for those
         : that need additional changes.
         :)
        $grammar/g:production[exists(.//g:subtract) and not(@name = ('CDataSectionContents', 'DirPIContents', 'PragmaContents', 'StringConstructorChars', 'CommentContents',
        'PITarget'))],

        (: Add lexical lookahead to CDataSectionContents. :)
        local:lookahead($grammar, 'CDataSectionContents', element g:string {']]'}),

        (: Add lexical lookahead to DirPIContents. :)
        local:lookahead($grammar, 'DirPIContents', element g:string {'?'}),

        (: Add lexical lookahead to PragmaContents. :)
        local:lookahead($grammar, 'PragmaContents', element g:string {'#'}),

        (: Add lexical lookahead to StringConstructorChars. :)
        local:lookahead
        (
          $grammar,
          'StringConstructorChars',
          element g:choice {element g:string {'`{'}, element g:string {']`'}}
        ),

        (: In PITarget, if present, replace Name by NCName. :)
        let $pi-target := $grammar/g:production[@name eq 'PITarget']
        where $pi-target
        return u:ast(replace(b:render($pi-target), 'Name', 'NCName')),

        (: Rewrite CommentContents to use the necessary lexical lookahead. :)
        let $comment-contents := $grammar/g:production[@name = 'CommentContents']
        let $nodes := $comment-contents/node()
        return
          element g:production
          {
            $comment-contents/@*,
            element g:choice
            {
              element g:context {element g:subtract {$nodes, element g:sequence { element g:zeroOrMore { element g:ref {attribute name {'Char'}}}, element g:string {'('}}}, element g:string {':'}},
              element g:context {$nodes, element g:string {'('}}
            }
          },

        (: Add an EOF production. :)
        u:ast('EOF ::= $'),

        (: Add fragment QNameOrKeywordDelimiter for being used as lexical lookahead. :)
        u:ast("QNameOrKeywordDelimiter ::= $ | ':' | Char - NameChar"),

        (: Add fragment NCNameDelimiter for being used as lexical lookahead. :)
        u:ast("NCNameDelimiter ::= $ $ | ( Char - NameChar ) ( $ | Char ) | ':' ( Char - NameStartChar )"),

        (: Add fragment NumericLiteralDelimiter for being used as lexical lookahead. :)
        u:ast("NumericLiteralDelimiter ::= QNameOrKeywordDelimiter | '-'"),

        (: Add a lexer preference for Wildcard over '*'. :)
        element g:preference {element g:string{'*'}, <g:ref name='Wildcard'/>},

        (: Add lexical lookahead for QNames. :)
        ('UnreservedQName')                                       !element g:delimiter {<g:ref name='QNameOrKeywordDelimiter'/>, <g:ref name='{.}'/>},

        (: Add lexical lookahead for operators starting with '<'. :)
        ('</', '<<', '<=')[contains($grammar, .)]                 !element g:delimiter {<g:ref name='Char'/>,                    element g:string {.}},

        (: Add lexical lookahead for NCNames. :)
        ('UnreservedNCName')                                      !element g:delimiter {<g:ref name='NCNameDelimiter'/>,         <g:ref name='{.}'/>},

        (: Add lexical lookahead for numeric literals. :)
        ('DecimalLiteral', 'DoubleLiteral', 'IntegerLiteral')     !element g:delimiter {<g:ref name='NumericLiteralDelimiter'/>, <g:ref name='{.}'/>},

        (: Add lexical lookahead for keywords. :)
        $keywords                                                 !element g:delimiter {<g:ref name='QNameOrKeywordDelimiter'/>, element g:string {.}},

        (: Add lexical lookahead for '<'. :)
        if (not($grammar//g:production/@name = 'DirElemConstructor')) then
          element g:delimiter {<g:ref name='Char'/>, element g:string {'<'}}
        else
        (
          u:ast('GeneralCompDelimiter ::= [^?]'),
          u:ast("DirElemConstructorDelimiter ::= QName ( S QName S? '=' | S? [/>] )"),
          element g:delimiter {<g:ref name='GeneralCompDelimiter'/>, <g:string context='GeneralComp'>&lt;</g:string>},
          element g:delimiter {<g:ref name='DirElemConstructorDelimiter'/>, <g:string context='DirElemConstructor'>&lt;</g:string>}
        ),

        (: Add lexical lookahead for '(#'. :)
        element g:delimiter {<g:ref name='S'/>, element g:string {'(#'}}[$grammar//g:string = '(#']
      )
    }
  ),

  (: Add EOF to the end of the Module or XPath production. :)
  local:rule
  (
    function($node) {$node/self::g:production/@name = ('Module', 'XPath')},
    function($node) {element g:production {$node/@*, $node/node(), <g:ref name='EOF'/>}}
  ),

  (: Remove MarkedNCName production where it is unused. :)
  local:rule
  (
    function($node) {$node/self::g:production/@name = 'MarkedNCName'},
    function($node) {($node[@name = root(.)//g:ref/@name], text {''})[1]}
  )
);

(:~
 : Add lexical lookahead to a production.
 :
 : @param $grammar the grammar
 : @param $name production name
 : @param $lookahead lexical lookahead
 :)
declare function local:lookahead($grammar as element(g:grammar), $name as xs:string, $lookahead as node()) as element(g:production)?
{
  let $nodes := $grammar//g:production[@name eq $name]/*
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
 : Find the first rule from a sequence of rules that mathches with a given node and apply its
 : action to the node.
 :
 : @param $node the node
 : @param $todo the rules
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
      $syntax//g:string[matches(., '^[a-zA-Z].*$')],
      $reserved-function-names
    ))
  order by $keyword
  return $keyword
};

concat
(
  let $grammar := u:unify($specification-url, $with-update, $with-full-text, $with-basex)
    => local:rewrite()
    => u:depth-first()
  return
  (
    replace($grammar/comment(), '\*/', '* adapted for REx by ' || replace(static-base-uri(), '.*/', '') || '&#xA; */'),
    b:render($grammar)
  )
)