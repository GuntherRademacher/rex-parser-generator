# RExification of XQuery 4.0 Grammar

This folder contains the scripts used to adapt the grammar from the [XQuery 4.0 specification](https://qt4cg.org/specifications/xquery-40/xquery-40.html) to the grammar file [XQuery-40.ebnf](../XQuery-40.ebnf), from which an LALR(2) parser can be generated successfully using REx.

The transformation logic is implemented in XQuery and can be found in [rexify-xquery-40.xq](rexify-xquery-40.xq). It leverages an EBNF grammar and several XQuery modules from the [RR](https://github.com/GuntherRademacher/rr) project. 

The transformation process is automated via:

- [rexify-xquery-40.bat](rexify-xquery-40.bat) for Windows,
- [rexify-xquery-40.sh](rexify-xquery-40.sh) for Linux or macOS.

Additionally, the transformation is integrated into a GitHub workflow: [rexify-xquery-40.yml](https://github.com/GuntherRademacher/rex-parser-generator/actions/workflows/rexify-xquery-40.yml). This workflow currently runs daily because the XQuery 4.0 specification remains a moving target.

## Prerequisites

The prerequisites for running the transformation in the rexify script are:

 - Java 11 or higher
 - [BaseX 11.6](https://basex.org/download/) or higher
 - [REx 6.1](https://github.com/GuntherRademacher/rex-parser-generator/releases) or higher

## Transformation Logic

The original grammar from the spec is first transformed into an XML representation, which is then adapted through a rule-based tree transformation process. This involves traversing the tree in pre-order traversal and applying the first rule that matches from a predefined set of transformation rules. Each rule is composed of two components: a condition and an action. The condition is a predicate that determines whether the rule is applicable to a given node, and if satisfied, the action specifies the replacement for the node, which may be a single node or a sequence of nodes.

## Transformation Rules

The following rules are applied during the transformation: 

- restore the previous definition of `ValueExpr`, referencing `ValidateExpr` and `ExtensionExpr` which have been disconnected by changes made for [qt4cg/qtspecs#1732](https://github.com/qt4cg/qtspecs/pull/1732): 

- Add an `EOF` reference to the end of the `Module` production, to ensure that parsers will fully consume their input.

- Remove obsolete productions, which are present in the grammar without being used.

- Remove the "type" keyword from the `NamedRecordTypeDecl` production. It was inadvertently added by [3c4ddb0](https://github.com/qt4cg/qtspecs/commit/3c4ddb0d8e06321fabde5e5a6db97810d03a61a6).

- Reference `EQName^Token` instead of `EQName` in the `UnreservedName` production.  
  `EQName` will become a new nonterminal allowing both `EQName^Token` and keywords. This change allows unreserved keywords.

- Reference `NCName^Token` instead of `NCName` in the `UnreservedNCName` production.  
  `NCName` will become a new nonterminal allowing both `NCName^Token` and keywords. This change allows unreserved keywords.

- Prevent `$reserved-function-names` from being used as unqualified function names by replacing `EQName` with the new nonterminal `UnreservedFunctionName` in the following productions:
  - `FunctionCall`
  - `FunctionDecl`
  - `NamedFunctionRef`
  - `ArrowStaticFunction`  
  *(Note: The annotation is missing in the spec for `ArrowStaticFunction`, but this rule adds it to avoid unlimited lookahead, which REx cannot provide, at least not in a deterministic parser.)*

- Replace `RelativePathExpr?` in the `PathExpr` production with an ordered choice between `RelativePathExpr` and nothing.  
  *(Implements extra-grammatical constraint `xgc: leading-lone-slash`.)*

- Replace the `PositionalArguments` production from:
  - `PositionalArguments ::= (Argument ++ ',')`, or rather its resolved form, `PositionalArguments ::= Argument (',' Argument)*`, to a left-recursive variant:  `PositionalArguments ::= Argument | PositionalArguments ',' Argument`  
  *(This reduces the necessary lookahead from 3 to 2, which reduces parser construction time from more than half an hour to a few seconds.)*

- Replace `OccurrenceIndicator?` in the `SequenceType` production with an ordered choice between `OccurrenceIndicator` and nothing.  
  *(Implements extra-grammatical constraint `xgc: occurrence-indicators`.)*

- Remove productions containing an exclusion operator (`-`) and the `Wildcard` production from their original location in the syntax section of the grammar. These productions will be moved to the lexical section by the rule that processes the `<?TOKENS?>` separator. Also, remove the `Comment` production from the lexical section, to have it added to the syntax section.

- Process the `<?TOKENS?>` separator by adding or rearranging the following:

  - Syntax Section:

    - Add `QName` as a new nonterminal with a choice between `UnreservedFunctionName` and reserved function names.
    - Add `UnreservedFunctionName` as a new nonterminal with a choice between `QName^Token` and unreserved keywords.
    - Add `NCName` as a new nonterminal with a choice between `NCName^Token` and keywords.
    - Add a `Whitespace` production: `"Whitespace ::= S^WS | Comment /* ws: definition */"`.
    - Move the `Comment` production to the syntax section.

  - Lexical Section:

    - Move all productions containing an exclusion operator (except `CommentContents`).
    - Replace `CommentContents` with a new production that adds lexical lookahead to prevent the greedy lexer from consuming a comment terminator or a nested comment introducer.
    - Move the `Wildcard` production.
    - Add an `EOF` production: `EOF ::= $`.
    - Add a preference for `Wildcard` over `*`.
    - Add preferences for all keywords over `QName` and `NCName`.

For more information, inspect the XQuery code in [rexify-xquery-40.xq](rexify-xquery-40.xq).