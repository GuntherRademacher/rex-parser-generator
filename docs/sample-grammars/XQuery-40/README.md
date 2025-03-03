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

For more information, inspect the XQuery code in [rexify-xquery-40.xq](rexify-xquery-40.xq), in particular the sequence of transformation rules in `$rules`.

## Test Execution

These scripts run the tests from [qt4cq/qt4tests](https://github.com/qt4cg/qt4tests) on the generated parsers:

- [process-tests.bat](process-tests.bat) for Windows,
- [process-tests.sh](process-tests.sh) for Linux or macOS.