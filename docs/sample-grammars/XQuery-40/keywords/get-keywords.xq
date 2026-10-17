import module namespace p = 'de/bottlecaps/railroad/xq/ebnf-parser.xquery' at 'cache/ebnf-parser.xquery';
import module namespace a = 'de/bottlecaps/railroad/xq/cst-to-ast.xq' at 'cache/cst-to-ast.xq';
declare namespace g = 'http://www.w3.org/2001/03/XPath/grammar';

declare variable $name-start-char := "A-Z_a-z&#xC0;-&#xD6;&#xD8;-&#xF6;&#xF8;-&#x2FF;&#x370;-&#x37D;&#x37F;-&#x1FFF;&#x200C;-&#x200D;&#x2070;-&#x218F;&#x2C00;-&#x2FEF;&#x3001;-&#xD7FF;&#xF900;-&#xFDCF;&#xFDF0;-&#xFFFD;&#x10000;-&#xEFFFF;";
declare variable $name-char := $name-start-char || "\-\.0-9&#xB7;&#x0300;-&#x036F;&#x203F;-&#x2040;";
declare variable $name-pattern := `^[{$name-start-char}][{$name-char}]*$`;

let $g := a:ast(p:parse-Grammar(unparsed-text("XQuery-40.ebnf")))
let $t := $g//processing-instruction(TOKENS)
for $k in distinct-values($g//g:string[. << $t])
where matches($k, $name-pattern)
order by $k
return $k