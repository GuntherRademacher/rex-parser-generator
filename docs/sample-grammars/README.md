<link rel="stylesheet" href="../markdown.css">

[⇦ Previous page](../grammar-tools.md) &nbsp;&nbsp;│&nbsp;&nbsp; [⇧ Back to index](../../README.md#-rex-parser-generator) &nbsp;&nbsp;│&nbsp;&nbsp; [Next page ⇨ ](../history.md)

&nbsp;
# Sample Grammars

These sample grammars demonstrate how to create functional REx parsers. The links below are sorted alphabetically, while the detailed sections are arranged by ascending grammar size.

 - [CSS-Selectors-3.ebnf](#sample-grammar-css-selectors-3ebnf)
 - [EcmaScript-5.ebnf](#sample-grammar-ecmascript-5ebnf)
 - [Java-7.ebnf](#sample-grammar-java-7ebnf)
 - [JSON.ebnf](#sample-grammar-jsonebnf)
 - [RELAX-NG-Compact.ebnf](#sample-grammar-relax-ng-compactebnf)
 - [REx.ebnf](#sample-grammar-rexebnf)
 - [RFC-7159.ebnf](#sample-grammar-rfc-7159ebnf)
 - [SPARQL.ebnf](#sample-grammar-sparqlebnf)
 - [Turtle.ebnf](#sample-grammar-turtleebnf)
 - [XML.ebnf](#sample-grammar-xmlebnf)
 - [XmlXl.ebnf](#sample-grammar-xmlxlebnf)
 - [XPath-20.ebnf](#sample-grammar-xpath-20ebnf)
 - [XPath-30.ebnf](#sample-grammar-xpath-30ebnf)
 - [XPath-31.ebnf](#sample-grammar-xpath-31ebnf)
 - [XQuery-Update-10.ebnf](#sample-grammar-xquery-update-10ebnf)
 - [XQuery-Update-30.ebnf](#sample-grammar-xquery-update-30ebnf)
 - [XQuery-10.ebnf](#sample-grammar-xquery-10ebnf)
 - [XQuery-30.ebnf](#sample-grammar-xquery-30ebnf)
 - [XQuery-40.ebnf](#sample-grammar-xquery-40ebnf)
 - [XQuery-31.ebnf](#sample-grammar-xquery-31ebnf)

## Sample Grammar: [JSON.ebnf](JSON.ebnf)

This is an LL(1) grammar for JSON, taken from [json.org](https://www.json.org/), manually adapted to the REx EBNF format.

## Sample Grammar: [RFC-7159.ebnf](RFC-7159.ebnf)

This JSON grammar was created by extracting the ABNF grammar out of [RFC 7159](https://datatracker.ietf.org/doc/html/rfc7159), then running it through [ebnf-convert][ebnf-convert], and tweaking it for REx parsing. It is sLL(2).

## Sample Grammar: [CSS-Selectors-3.ebnf](CSS-Selectors-3.ebnf)

This grammar for CSS Selectors Level 3 was created by taking the grammar from W3C Recommendation [Selectors Level 3](https://www.w3.org/TR/selectors-3/#grammar), converting it to REx EBNF, and tweaking it for REx LL(3) parsing. Although this was primarily a manual process, some aspects could have been partially automated using [ebnf-convert][ebnf-convert].

## Sample Grammar: [XmlXl.ebnf](XmlXl.ebnf)

This sLL(3) grammar, together with the Java source file [XmlXlLexer.java](XmlXlLexer.java), is used in the demonstration of how to use REx with an external lexer. It lacks a built-in lexer specification, but a parser generated from it, using the `-nolexer` command line option, requires an external lexer being supplied. For more information, see [Using an External Lexer](../using-an-external-lexer.md).

## Sample Grammar: [REx.ebnf](REx.ebnf)

This is the grammar that REx itself uses for parsing its input grammars, however all C++ code annotations have been stripped. The version with C++ code annotations can be found in REx's source code ([EbnfParser.ebnf](../../rex/src/parser/EbnfParser.ebnf)). The grammar is sLL(3).

## Sample Grammar: [Turtle.ebnf](Turtle.ebnf)

This grammar was extracted by [RR][rr] from W3C Recommendation [RDF 1.1. Turtle](https://www.w3.org/TR/2014/REC-turtle-20140225/). The `Whitespace` and `EOF` rules have been added manually. The grammar is LL(1).

## Sample Grammar: [XML.ebnf](XML.ebnf)

This XML grammar is based on a grammar extracted by [RR][rr] from W3C Recommendation [Extensible Markup Language (XML) 1.0](https://www.w3.org/TR/xml/). The grammar is sLL(3).
 
## Sample Grammar: [XPath-20.ebnf](XPath-20.ebnf)

This grammar was extracted by [RR][rr] from W3C Recommendation [XML Path Language (XPath) 2.0](https://www.w3.org/TR/2010/REC-xpath20-20101214/), and tweaked for working with REx. It is sLL(2).

## Sample Grammar: [RELAX-NG-Compact.ebnf](RELAX-NG-Compact.ebnf)

This grammar is a transcription of the grammar given in OASIS [RELAX NG Compact Syntax](https://relaxng.org/compact-20021121.html). The grammar has unresolved conflicts that occur in both LL and LR constructions, and these have not been further investigated. Still parsers can be constructed from it when using backtracking (`-ll 2 -backtrack`) or GLR parsing (`-glalr 3`). The backtracking sLL(2) parser will, in case of doubt, select the first conflicting alternative, if successful, while the GLR parser will potentially report an ambiguity, should there be one.

## Sample Grammar: [XPath-30.ebnf](XPath-30.ebnf)

This grammar was extracted by [RR][rr] from W3C Recommendation [XML Path Language (XPath) 3.0](https://www.w3.org/TR/2014/REC-xpath-30-20140408/), and tweaked for working with REx. It is sLL(3).

## Sample Grammar: [XPath-31.ebnf](XPath-31.ebnf)

This grammar was extracted by [RR][rr] from W3C Recommendation [XML Path Language (XPath) 3.1](https://www.w3.org/TR/2017/REC-xpath-31-20170321/), and tweaked for working with REx. It is sLL(3).

## Sample Grammar: [SPARQL.ebnf](SPARQL.ebnf)

This grammar has been extracted by [RR][rr] from W3C Recommendation [SPARQL Query Language for RDF](https://www.w3.org/TR/2008/REC-rdf-sparql-query-20080115/), and tweaked for working with REx. It is LL(1).

## Sample Grammar: [XQuery-Update-10.ebnf](XQuery-Update-10.ebnf)

This grammar was extracted by [RR][rr] from W3C Recommendation [XQuery Update Facility 1.0](https://www.w3.org/TR/2011/REC-xquery-update-10-20110317/), and tweaked to fit REx LL(3) parsing. 

## Sample Grammar: [EcmaScript-5.ebnf](EcmaScript-5.ebnf)

This grammar is a transcription of the grammar given in the 5th edition of the [ECMAScript® Language Specification](https://ecma-international.org/wp-content/uploads/ECMA-262_5th_edition_december_2009.pdf). The grammar has unresolved conflicts that occur in both LL and LR constructions, those have not been investigated in more detail. A parser can be constructed from it when using backtracking (`-ll 1 -backtrack -asi`). It will in doubt select the first conflicting alternative, if successful. Note that the grammar by itself does not handle EcmaScript's "Automatic Semicolon Insertion". REx however has special logic for this, activated by the `-asi` command line option, based on these rules in the grammar:

 - `EmptyStatement`
 - `IterationStatement`
 - `PostfixExpression`
 - `ContinueStatement`
 - `BreakStatement`
 - `ReturnStatement`
 - `ThrowStatement`

## Sample Grammar: [XQuery-30.ebnf](XQuery-30.ebnf)

This grammar was extracted by [RR][rr] from W3C Recommendation [XQuery 3.0: An XML Query Language](https://www.w3.org/TR/2014/REC-xquery-30-20140408/), and tweaked for working with REx. It is sLL(3).

## Sample Grammar: [XQuery-40.ebnf](XQuery-40.ebnf)

This grammar was created from W3C Recommendation [XQuery 4.0: An XML Query Language](https://qt4cg.org/specifications/xquery-40/xquery-40.html) by applying the transformation scripts in folder [XQuery-40](XQuery-40/). It is LALR(2).

## Sample Grammar: [XQuery-Update-30.ebnf](XQuery-Update-30.ebnf)

This grammar was extracted by [RR][rr] from [XQuery Update Facility 3.0
W3C Working Group Note 24 January 2017](https://www.w3.org/TR/2017/NOTE-xquery-update-30-20170124/), and tweaked to fit REx LL(3) parsing.

## Sample Grammar: [XQuery-31.ebnf](XQuery-31.ebnf)

This grammar was extracted by [RR][rr] from W3C Recommendation [XQuery 3.1: An XML Query Language](https://www.w3.org/TR/2017/REC-xquery-31-20170321/), and tweaked for working with REx. It is sLL(3).

## Sample Grammar: [XQuery-10.ebnf](XQuery-10.ebnf)

This grammar was extracted by [RR][rr] from W3C Recommendation [XQuery 1.0: An XML Query Language](https://www.w3.org/TR/2010/REC-xquery-20101214/), and tweaked for working with REx. It is sLL(3).

## Sample Grammar: [Java-7.ebnf](Java-7.ebnf)

This grammar is a transcription of the Java 7 grammar found in [The Java® Language Specification](https://docs.oracle.com/javase/specs/jls/se7/html/) documents on [Syntax](https://docs.oracle.com/javase/specs/jls/se7/html/jls-18.html) and [Lexical Structure](https://docs.oracle.com/javase/specs/jls/se7/html/jls-3.html). It has subsequently been tweaked for working with REx, but there are still unresolved conflicts for both LL and LR constructions. Still parsers can be constructed from it when using backtracking (`-ll 2 -backtrack`) or GLR parsing (`-glalr 2`). The backtracking sLL(2) parser will in doubt select the first conflicting alternative, if successful, while the GLR parser will potentially report an ambiguity, should there be one.

&nbsp;
---
[⇦ Previous page](../grammar-tools.md) &nbsp;&nbsp;│&nbsp;&nbsp; [⇧ Back to index](../../README.md#-rex-parser-generator) &nbsp;&nbsp;│&nbsp;&nbsp; [Next page ⇨ ](../history.md)

[ebnf-convert]: https://github.com/GuntherRademacher/ebnf-convert
[rr]: https://github.com/GuntherRademacher/rr