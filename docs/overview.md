<link rel="stylesheet" href="markdown.css">

[⇧ Back to index](../README.md#-rex-parser-generator) &nbsp;&nbsp;│&nbsp;&nbsp; [Next page ⇨ ](project-structure.md)

&nbsp;
# REx Parser Generator Overview

REx is a parser generator that can generate a program in one of various target programming languages from a grammar provided to it in EBNF. The generated program implements a parser and lexer for the language described by the EBNF grammar.

REx itself is implemented in C++ and can be built using C++ compilers on at least Windows, Linux, or macOS. Building it results in the REx executable, which is needed for parser generation. REx’s source code is open source.

During generation, the user-provided grammar is translated into a parser and lexer for the specified language. The grammar itself is represented in EBNF, specifically the dialect used by the W3C in specifications such as XML and XQuery.

REx employs the following algorithms for grammar processing:

- LL(1)
- sLL(k)
- LALR(k)
- LR(k)
- GLR
- PEG-style backtracking
- DFA construction
- Context-dependent lexing

The result of generation is program code in one of the following languages:

- C++
- C#
- Go
- Haxe
- Java
- JavaScript
- Python
- Scala
- TypeScript
- XQuery
- XSLT

The generated code is self-contained and has no dependencies beyond the standard runtime libraries of the respective programming language. Besides the code that results from translating REx's input grammar, the generated program code includes pre-made components as well.

The generated code, once compiled, is typically integrated into programs that depend on it for parsing and are delivered to customers. Only the generated code is required in the application context; REx, the generator, is needed only at generation time and does not need to be passed on.

Both the generation process and the generated parsers and lexers are characterized by high performance. REx parsers often outperform parsers from other generators by factors of two or more.

With the help of the [ebnf-convert](https://github.com/GuntherRademacher/ebnf-convert) tool, available on GitHub, many common grammar notations can be converted into REx grammars. The notation used by REx is also compatible with the syntax diagram generator [RR](https://github.com/GuntherRademacher/rr), also available on GitHub, which is often used for formal language documentation purposes.

REx has been in development since 1979.

&nbsp;
---
[⇧ Back to index](../README.md#-rex-parser-generator) &nbsp;&nbsp;│&nbsp;&nbsp; [Next page ⇨ ](project-structure.md)