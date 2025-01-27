# RExification of XQuery 4.0 Grammar

This folder contains the scripts used to adapt the grammar from the [XQuery 4.0 specification](https://qt4cg.org/specifications/xquery-40/xquery-40.html) to the grammar file [XQuery-40.ebnf](../XQuery-40.ebnf), from which an LALR(2) parser can be generated successfully using REx.

The transformation logic is implemented in XQuery and can be found in [rexify-xquery-40.xq](rexify-xquery-40.xq). It leverages an EBNF grammar and several XQuery modules from the [RR](https://github.com/GuntherRademacher/rr) project. 

The transformation process is automated via:
- [rexify-xquery-40.bat](rexify-xquery-40.bat) for Windows,
- [rexify-xquery-40.sh](rexify-xquery-40.sh) for Linux or macOS.

Additionally, the transformation is integrated into a GitHub workflow: [rexify-xquery-40.yml](https://github.com/GuntherRademacher/rex-parser-generator/actions/workflows/rexify-xquery-40.yml). This workflow currently runs daily because the XQuery 4.0 specification remains a moving target.

## Prerequisites

The prerequisites for running the transformation in the rexify-xquery-40 script are:

 - curl
 - Java 11 or higher
 - BaseX 11.6 or higher
 - a REx executable

## Transformation Logic

The grammar is adapted through a rule-based tree transformation process. This involves traversing the tree in pre-order traversal and applying the first rule that matches from a predefined set of transformation rules. Each rule is composed of two components: a condition and an action. The condition is a predicate that determines whether the rule is applicable to a given node, and if satisfied, the action specifies the replacement for the node, which may be a single node or a sequence of nodes.

## Transformation Rules

The following rules are applied during the transformation: 

- Add EOF to the end of the `Module` production.

- Remove obsolete productions, which are left over in the grammar but not used anymore.

- Remove the "type" keyword from the `NamedRecordTypeDecl` production. It was inadvertently added by [this commit](https://github.com/qt4cg/qtspecs/commit/3c4ddb0d8e06321fabde5e5a6db97810d03a61a6).

- Refer to `EQName^Token` instead of `EQName` in the `UnreservedName` production.  
  `EQName` will become a new nonterminal allowing both `EQName^Token` and keywords. This change allows unreserved keywords.

- Refer to `NCName^Token` instead of `NCName` in the `UnreservedNCName` production.  
  `NCName` will become a new nonterminal allowing both `NCName^Token` and keywords. This change allows unreserved keywords.

- Prevent `$reserved-function-names` from being used as unqualified function names by replacing `EQName` with the new nonterminal `UnreservedFunctionName` in the following productions:
  - `FunctionCall`
  - `FunctionDecl`
  - `NamedFunctionRef`
  - `ArrowStaticFunction`  
  *(Note: The annotation is missing in the spec for `ArrowStaticFunction`, but this rule adds it to avoid unlimited lookahead, which REx cannot provide.)*

- Replace `RelativePathExpr?` in the `PathExpr` production with an ordered choice between `RelativePathExpr` and nothing.  
  *(Implements extra-grammatical constraint `xgc: leading-lone-slash`.)*

- Replace the `PositionalArguments` production from:
  - `PositionalArguments ::= (Argument ++ ',')`, or rather its resolved form, `PositionalArguments ::= Argument (',' Argument)*`, to a left-recursive variant:  `PositionalArguments ::= Argument | PositionalArguments ',' Argument`  
  *(This reduces the necessary lookahead from 3 to 2 and improves parser performance.)*

- Replace `OccurrenceIndicator?` in the `SequenceType` production with an ordered choice between `OccurrenceIndicator` and nothing.  
  *(Implements extra-grammatical constraint `xgc: occurrence-indicators`.)*

- Remove productions containing an exclusion operator (`-`) and the `Wildcard` production from their original location in the syntax section of the grammar. These productions will be moved to the lexical section by the rule that processes the `<?TOKENS?>` separator. Also, move the `Comment` production from the lexical section to the syntax section.

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