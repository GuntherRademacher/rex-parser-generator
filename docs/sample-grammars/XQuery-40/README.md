<link rel="stylesheet" href="../../markdown.css">

# RExification of XQuery and XPath 4.0 Grammars

This folder contains the script used to adapt the grammars

 - from the [XQuery 4.0 specification](https://qt4cg.org/specifications/xquery-40/xquery-40.html) to the grammar file [XQuery-40.ebnf](../XQuery-40.ebnf) for creating an LALR(2) parser,
 - from the [XPath 4.0 specification](https://qt4cg.org/specifications/xquery-40/xpath-40.html) to the grammar file [XPath-40.ebnf](../XPath-40.ebnf) for creating an LALR(1) parser.

The transformation logic is implemented in XQuery and can be found in [rexify-xquery-40.xq](rexify-xquery-40.xq). It leverages several XQuery modules from the [RR](https://github.com/GuntherRademacher/rr) project. 

The transformation process is automated via:

- [rexify-xquery-40.bat](rexify-xquery-40.bat) for Windows,
- [rexify-xquery-40.sh](rexify-xquery-40.sh) for Linux or macOS.

Additionally, the transformation is integrated into a GitHub workflow: [rexify-xquery-40.yml](https://github.com/GuntherRademacher/rex-parser-generator/actions/workflows/rexify-xquery-40.yml). This workflow currently runs daily because the XQuery 4.0 specification remains a moving target.

## Prerequisites

The prerequisites for running the transformation in the rexify script are:

 - Java 11 or higher,
 - [BaseX 11.6](https://basex.org/download/) or higher,
 - [REx 6.1](https://github.com/GuntherRademacher/rex-parser-generator/releases) or higher.

## Transformation Logic

The original grammar from the specification is first transformed into an XML representation, which is then adapted through a rule-based tree transformation process. This process involves traversing the tree using pre-order traversal and applying predefined transformation rules to each node.

Each rule consists of two components: a condition and an action. The condition is a predicate that determines whether the rule applies to a given node, while the action specifies the replacement for the node. This replacement may be a single node or a sequence of nodes.

## Transformation Rules

The following rules are applied during the transformation: 

- add missing preceding-sibling axis ([qt4cg/qtspecs/issues#1785](https://github.com/qt4cg/qtspecs/issues/1785))

- allow zero or more arrow target expressions (see [qt4cg/qtspecs/issues/1785](https://github.com/qt4cg/qtspecs/issues/1785))

-  prevent reserved function names to be used as unqualified function names by replacing `EQName` by new nonterminal `UnreservedFunctionName` in productions `FunctionCall`, `FunctionDecl`, `NamedFunctionRef`, and `ArrowStaticFunction`. This basically implements extra-grammatical constraint _`/* xgc: reserved-function-names */`_ (see [extra grammatical constraints](https://qt4cg.org/specifications/xquery-40/xquery-40.html#extra-grammatical-constraints)). In `ArrowStaticFunction`, the annotation is missing in the spec, as pointed out in [qt4cg/qtspecs/1716](https://github.com/qt4cg/qtspecs/issues/1716), but it needs to be added here to avoid the necessity for unlimited lookahead.

- Add an `EOF` reference to the end of the `Module` production, to ensure that parsers will fully consume their input.

- Reference `EQName^Token` instead of `EQName` in the `UnreservedName` production.  
  `EQName` will become a new nonterminal allowing both `EQName^Token` and keywords. This change allows unreserved keywords.

- Reference `NCName^Token` instead of `NCName` in the `UnreservedNCName` production.  
  `NCName` will become a new nonterminal allowing both `NCName^Token` and keywords. This change allows unreserved keywords.

- Replace `RelativePathExpr?` in the `PathExpr` production with an ordered choice between `RelativePathExpr` and nothing. This implements extra-grammatical constraint _`/* xgc: leading-lone-slash */`_ (see [extra grammatical constraints](https://qt4cg.org/specifications/xquery-40/xquery-40.html#extra-grammatical-constraints)).

- Replace the `PositionalArguments` production from  `PositionalArguments ::= (Argument ++ ',')`, or rather its resolved form, `PositionalArguments ::= Argument (',' Argument)*`, to a left-recursive variant:
   `PositionalArguments ::= Argument | PositionalArguments ',' Argument`. This reduces the necessary lookahead from 3 to 2, which reduces parser construction time from more than half an hour to a few seconds.

- Replace `OccurrenceIndicator?` in the `SequenceType` production with an ordered choice between `OccurrenceIndicator` and nothing. Implements extra-grammatical constraint _`/* xgc: occurrence-indicators */`_ (see [extra grammatical constraints](https://qt4cg.org/specifications/xquery-40/xquery-40.html#extra-grammatical-constraints)).

- Remove productions containing an exclusion operator (`-`) and the `Wildcard` production from their original location in the syntax section of the grammar. These productions will be moved to the lexical section by the rule that processes the `<?TOKENS?>` separator. Also, remove the `Comment` production from the lexical section, to have it added to the syntax section.

- Process the `<?TOKENS?>` separator by adding or rearranging the following:

  - Syntax Section:

    - Add `QName` as a new nonterminal with a choice between `UnreservedFunctionName` and reserved function names.
    - Add `UnreservedFunctionName` as a new nonterminal with a choice between `QName^Token` and unreserved keywords.
    - Add `NCName` as a new nonterminal with a choice between `NCName^Token` and keywords.
    - Add a `Whitespace` production: `Whitespace ::= S^WS | Comment /* ws: definition */`.
    - Move the `Comment` production to the syntax section.

  - Lexical Section:

    - Move all productions containing an exclusion operator (except for `CommentContents` and others, needing lexical lookahead).
    - Rewrite `CommentContents` and others, adding lexical lookahead to prevent the greedy lexer from consuming parts of the terminating character sequence.
    - Move the `Wildcard` production to the lexical section+.
    - Add an `EOF` production: `EOF ::= $`.
    - Add a preference for `Wildcard` over `*`.
    - Add preferences for all keywords over `QName` and `NCName`.

For more information, inspect the XQuery code in [rexify-xquery-40.xq](rexify-xquery-40.xq).