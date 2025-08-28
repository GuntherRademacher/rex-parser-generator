(:~
 : Functions to
 : - extract EBNF grammars from the specifications of XQuery 4.0, XPath 4.0
 : - extract EBNF from specifications referred to by the above XML 1.0, XML Names 1.0
 : - extract EBNF from specifications that define extensions to XQuery and XPath:
 :     XQuery Update 3.0, XQuery and XPath Full Text 3.0
 : - in the XQuery and XPath 4.0 grammars, resolve the references to grammar rules that are
 :     defined in XML or XML Names
 : - extend the XQuery and XPath 4.0 grammars by grammar rules from the Update and Full Text
 :     extensions
 :)
module namespace u = 'unify-grammar.xq';

declare namespace g = 'http://www.w3.org/2001/03/XPath/grammar';
declare namespace xhtml = 'http://www.w3.org/1999/xhtml';

import module namespace a = 'de/bottlecaps/railroad/xq/cst-to-ast.xq' at
                            'https://raw.githubusercontent.com/GuntherRademacher/rr/refs/heads/basex/src/main/resources/de/bottlecaps/railroad/xq/cst-to-ast.xq';
import module namespace b = 'de/bottlecaps/railroad/xq/ast-to-ebnf.xq' at
                            'https://raw.githubusercontent.com/GuntherRademacher/rr/refs/heads/basex/src/main/resources/de/bottlecaps/railroad/xq/ast-to-ebnf.xq';
import module namespace e = 'de/bottlecaps/railroad/xq/html-to-ebnf.xq' at
                            'https://raw.githubusercontent.com/GuntherRademacher/rr/refs/heads/basex/src/main/resources/de/bottlecaps/railroad/xq/html-to-ebnf.xq';
import module namespace p = 'de/bottlecaps/railroad/xq/ebnf-parser.xquery' at
                            'https://raw.githubusercontent.com/GuntherRademacher/rr/refs/heads/basex/src/main/resources/de/bottlecaps/railroad/xq/ebnf-parser.xquery';

(:~ External specs that contain productions referenced by the specification grammar. :)
declare variable $u:external-specs :=
(
  'https://www.w3.org/TR/REC-xml/',
  'https://www.w3.org/TR/REC-xml-names/'
);

(:~ External grammars that contain productions referenced by the specification grammar. :)
declare variable $u:external-grammars := $u:external-specs ! u:extract-grammar(.);

(:~ The XQuery Update 3.0 specification URL :)
declare variable $u:xquery-update-spec := 'https://www.w3.org/TR/xquery-update-30/';

(:~ The XQuery and XPath Full Text 3.0 specification URL :)
declare variable $u:xquery-and-xpath-full-text-spec := 'https://www.w3.org/TR/xpath-full-text-30/';

(:~ The runtime environment time zone offset. :)
declare variable $u:tz-offset := - xs:integer(timezone-from-dateTime(current-dateTime()) div xs:dayTimeDuration('PT1M'));

(:~
 : Extract an EBNF grammar from a W3 document, or appendix of a document, parse it, and transform
 : the parse tree to the grammar's XML representation.
 :
 : @param $uri the URI of the spec containing the spec
 : @param $appendix the appendix from the document where to get the EBNF from
 : @return the grammar
 :)
declare function u:extract-grammar($uri as xs:string, $appendix := ()) as document-node()
{
  let $html := html:parse(unparsed-text($uri))
  let $fragment :=
    if (exists($appendix)) then
      $html//*:h2[normalize-space(.) eq $appendix]/parent::*:div
    else
      $html
  let $extract := e:extract($uri, $fragment, $u:tz-offset)
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
declare function u:collect-external-productions(
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
        u:collect-external-productions($done, $todo)
      else
        let $p := $u:external-grammars/g:grammar/g:production[@name eq $name]
        return
          if (empty($p)) then
            error(xs:QName('u:collect-external-productions'), concat('missing nonterminal: ', $name))
          else if (count($p) gt 1) then
            error(xs:QName('u:collect-external-productions'), concat('multiple definitions found for: ', $name))
          else
            u:collect-external-productions(($done, $p), ($p//g:ref/@name, $todo))
};

(:~
 : Rewrite a sequence of nodes, including any referenced external productions in place of
 : g:production[@xhref].
 :
 : @param $nodes the input node sequence
 : @return a sequence of nodes made up of the rewritten node and the possibly inlined
 :         productions from external grammars
 :)
declare function u:include-external-productions($nodes as node()*) as node()*
{
  for $node in $nodes
  return
    typeswitch ($node)
    case document-node() return
      document
      {
        comment {replace($node/comment(), ' \*/', string-join($u:external-specs ! ` * with references to {.} resolved and inlined{char(10)}`) || ' */')},
        u:include-external-productions($node/*)
      }
    case element(g:grammar) return
      let $nodes :=
        u:include-external-productions
        ((
          $node/node(),
          (: the following is needed, but possibly only referenced in extra-grammatical text :)
          $u:external-grammars//g:production[@name eq 'S']
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
        else if (starts-with($xhref, 'http://www.w3.org/TR/REC-xml#NT-')) then
          u:collect-external-productions((), $node/@name)
        else if (starts-with($xhref, 'http://www.w3.org/TR/REC-xml-names/#NT-')) then
          u:collect-external-productions((), $node/@name)
        else
          error(xs:QName('u:include-external-productions'), concat('unexpected xhref attribute: ', $xhref))
      for $e in $elements
      return element {node-name($e)} {$e/@*, u:include-external-productions($e/node())}
    default
      return $node
};

(:~
 : Extend grammar fragments with XQuery Update 3.0 specification.
 :
 : @param $nodes the nodes to be extended
 : @param $xquery-update-30-grammar the XQuery Update 3.0 grammar
 : @return the nodes with XQuery Update 3.0 extensions applied
 :)
declare function u:include-xquery-update($nodes as node()*, $xquery-update-30-grammar as document-node()) as node()*
{
  for $node in $nodes
  return
    typeswitch ($node)
    case document-node() return
      document
      {
        comment {replace($node/comment(), ' \*/', ` * with productions from {$u:xquery-update-spec} added{char(10)} */`)},
        u:include-xquery-update($node/*, $xquery-update-30-grammar)
      }
    case element(g:ref) return
      if ($node/@name eq 'UnaryExpr') then
        <g:ref name='TransformWithExpr'/>
      else if ($node[@name eq 'Annotation']/parent::g:zeroOrMore/parent::g:production/@name eq 'FunctionDecl') then
        <g:choice>{$node}<g:ref name='CompatibilityAnnotation'/></g:choice>
      else if ($node[@name eq 'CopyNamespacesDecl']/parent::g:choice) then
        (<g:ref name='RevalidationDecl'/>, $node)
      else if ($node[@name eq 'OrExpr']/parent::g:choice/parent::g:production/@name eq 'ExprSingle') then
        (
          $node,
          <g:ref name='InsertExpr'/>,
          <g:ref name='DeleteExpr'/>,
          <g:ref name='RenameExpr'/>,
          <g:ref name='ReplaceExpr'/>,
          <g:ref name='UpdatingFunctionCall'/>,
          <g:ref name='CopyModifyExpr'/>
        )
      else
        $node
    case element() return
      element {node-name($node)} {u:include-xquery-update(($node/@*, $node/node()), $xquery-update-30-grammar)}
    case processing-instruction(TOKENS) return
    (
      for $p in $xquery-update-30-grammar//g:production[@name =
        (
          'CompatibilityAnnotation',
          'TransformWithExpr',
          'RevalidationDecl',
          'InsertExprTargetChoice',
          'InsertExpr',
          'DeleteExpr',
          'ReplaceExpr',
          'RenameExpr',
          'SourceExpr',
          'TargetExpr',
          'NewNameExpr',
          'UpdatingFunctionCall',
          'CopyModifyExpr'
        )
      ]
      return u:ast(b:render($p) => replace("'\$' VarName", 'VarName')),
      $node
    )
    default return
      $node
};

(:~
 : Extend grammar fragments with XPath and XQuery Full Text 3.0 specification.
 :
 : @param $nodes the nodes to be extended
 : @param $xquery-update-30-grammar the XPath or XQuery Full Text 3.0 grammar
 : @return the nodes with XPath and XQuery Full Text 3.0 extensions applied
 :)
declare function u:include-full-text($nodes as node()*, $full-text-30-grammar) as node()*
{
  for $node in $nodes
  return
    typeswitch ($node)
    case document-node() return
      document
      {
        comment {replace($node/comment(), ' \*/', ` * augmented with productions from {$u:xquery-and-xpath-full-text-spec}{char(10)} */`)},
        u:include-full-text($node/*, $full-text-30-grammar)
      }
    case element(g:string) return
      if ($node[ancestor::g:production/@name eq 'ForItemBinding'] eq 'in') then
        (<g:optional><g:ref name='FTScoreVar'/></g:optional>, $node)
      else
        $node
    case element(g:ref) return
      if ($node[@name eq 'Import']/parent::g:choice/ancestor::g:production/@name eq 'Prolog') then
        ($node, <g:ref name='FTOptionDecl'/>)
      else if ($node[@name eq 'StringConcatExpr']/ancestor::g:production/@name eq 'OtherwiseExpr') then
        <g:ref name='FTContainsExpr'/>
      else if ($node[@name eq 'VarNameAndType']/parent::g:production/@name eq 'LetValueBinding') then
        <g:choice>{$node}<g:ref name='FTScoreVar'/></g:choice>
      else
        $node
    case element() return
      element {node-name($node)} {u:include-full-text(($node/@*, $node/node()), $full-text-30-grammar)}
    case processing-instruction(TOKENS) return
    (
      for $p in $full-text-30-grammar//g:production[
        starts-with(@name, 'FT') and (@name ne 'FTOptionDecl' or u:is-xquery($node))
        or not(u:is-xquery($node)) and @name = ('Pragma', 'PragmaContents', 'URILiteral')
      ]
      return u:ast(b:render($p) => replace("'\$' VarName", 'VarName')),
      $node
    )
    default return
      $node
};

(:~ Parse an EBNF grammar fragment and return its XML representation.
 :
 : @param $ebnf the grammar fragment
 : @return the XML representation
 :)
declare function u:ast($ebnf as xs:string) as element(g:*)*
{
  a:ast(p:parse-Grammar($ebnf))/g:*
};

(:~ Establish depth first order of a sequence of productions.
 :
 : @param $done a partial result, empty on the intial call
 : @param $todo the productions to be ordered
 : @return the ordered sequence of productions
 :)
declare function u:depth-first(
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
      u:depth-first
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
declare function u:depth-first($grammar as document-node()) as document-node()
{
   let $separator := $grammar/g:grammar/processing-instruction(TOKENS)
   let $syntax := $grammar/g:grammar/g:production[not(. >> $separator)]
   let $tokens := $grammar/g:grammar/g:production[. >> $separator]
   let $start :=
     for $production in $syntax
     let $refs := $syntax//g:ref[@name eq $production/@name and empty(@context)]
     where empty($refs)
     return $production
   let $syntax := u:depth-first((), ($start, $syntax[not(@name = $start/@name)]))
   let $used-tokens :=
     for $name in distinct-values
     (
       for $ref in $syntax//g:ref
       let $name := string($ref/@name)
       where exists($ref/@context) or empty($syntax[@name = $name])
       return $name
     )
     return $tokens[@name = $name]
   let $tokens := u:depth-first((), ($used-tokens, $tokens[not(@name = $used-tokens/@name)]))
   return
     document {
       comment {replace($grammar/comment(), ' \*/', ` * reordered into depth-first order{char(10)} */`)},
       element g:grammar {
         $syntax,
         $separator,
         $tokens,
         $grammar/g:grammar/*[not(self::g:production)]
       }
     }
};

(:~
 : Check whether we are processing XQuery, i.e. not XPath.
 :
 : @param $node node to be checked
 : @return true, if $node is part of an XQuery grammar
 :)
declare function u:is-xquery($node as node()) as xs:boolean
{
  if (root($node)//g:production/@name = 'Module') then
    true()
  else if (root($node)//g:production/@name = 'XPath') then
    false()
  else
    error(xs:QName('u:is-xquery'), 'grammar is neither XQuery nor XPath')
};

(:~
 : Unify a specification grammar, by resolving references to external grammars and extending it with
 :
 : rules from Update or Full Text specifications.
 : @param $specification-url specification URL
 : @param $with-update whether to extend with Update rules
 : @param $with-full-text whether to extend with Full Text rules
 : @return unified grammar
 :)
declare function u:unify($specification-url, $with-update, $with-full-text) as document-node()
{
  let $specification-grammar := u:extract-grammar($specification-url)
  let $grammar :=
    u:include-external-productions($specification-grammar)
  let $grammar :=
    if ($with-update and u:is-xquery($grammar)) then
      u:include-xquery-update($grammar, u:extract-grammar($u:xquery-update-spec))
    else
      $grammar
  let $grammar :=
    if ($with-full-text) then
      let $appendix :=
        if (u:is-xquery($specification-grammar)) then
          'A EBNF for XQuery 3.0 Grammar with Full Text extensions'
        else
          'B EBNF for XPath 3.0 Grammar with Full-Text extensions'
      return u:include-full-text($grammar, u:extract-grammar($u:xquery-and-xpath-full-text-spec, $appendix))
    else
      $grammar
  return $grammar
};
