<link rel="stylesheet" href="markdown.css">

[⇦ Previous page](quickstart-xslt.md) &nbsp;&nbsp;│&nbsp;&nbsp; [⇧ Back to index](../README.md#-rex-parser-generator) &nbsp;&nbsp;│&nbsp;&nbsp; [Next page ⇨ ](supported-algorithms.md)

&nbsp;
# REx Command Line

REx supports multiple parsing algorithms and generates code in multiple programming languages. It is invoked from a command line, takes some input file, and generates some output file. This section covers the command line options available for REx.

## Usage

```
rex [OPTION]... [input-file]
```

## Parsing Algorithms

Specify the parsing algorithm and its parameters with the following options:

| Option        | Description                                                     |
|---------------|-----------------------------------------------------------------|
| `-ll NUM`     | Use strong-LL(k) algorithm up to k=NUM (default: `-ll 3`).      |
| `-lalr NUM`   | Use LALR(K) algorithm up to K=NUM.                              |
| `-lr NUM`     | Use LR(K) algorithm up to K=NUM.                                |
| `-glalr NUM`  | Use GLR, based on LALR(K) up to K=NUM.                          |
| `-glr NUM`    | Use GLR, based on LR(K) up to K=NUM.                            |

See the section on [supported algorithms](supported-algorithms.md) for more details.

## Additional Parsing Options

Enhance or modify the parsing behavior with these options:

| Option        | Description                                                     |
|---------------|-----------------------------------------------------------------|
| `-backtrack`  | Allow PEG-style backtracking for LL-conflicts.                  |
| `-asi`        | Handle EcmaScript automatic semicolon insertion (LL(1) only).   |

## Target Languages

REx can generate the parser in multiple programming languages. Unless the `-name` option is used (see below), an output file will be written that has the same name as the input grammar, but a file extension suitable for the target language. In some cases the name is capitalized to meet the requirements of the target language.

| Option        | Description                   | Output file extension                        |
|---------------|-------------------------------|----------------------------------------------|
| `-cpp`        | Generate parser in C++.       | `.hpp`<br>`.cpp` when `-main` option is used |
| `-csharp`     | Generate parser in C#.        | `.cs`                                        |
| `-go`         | Generate parser in Go.        | `.go`                                        |
| `-haxe`       | Generate parser in Haxe.      | `.hx`                                        |
| `-java`       | Generate parser in Java.      | `.java`                                      |
| `-javascript` | Generate parser in JavaScript.| `.js`                                        |
| `-python`     | Generate parser in Python.    | `.py`                                        |
| `-scala`      | Generate parser in Scala.     | `.scala`                                     |
| `-typescript` | Generate parser in TypeScript.| `.ts`                                        |
| `-xquery`     | Generate parser in XQuery.    | `.xquery`                                    |
| `-xslt`       | Generate parser in XSLT.      | `.xslt`                                      |

## C++-Specific Option

Option specific to C++ code generation:

| Option            | Description                                                 |
|-------------------|-------------------------------------------------------------|
| `-char`           | Generate C++ code using UTF-8 char rather than wchar_t.     |

## Java-Specific Options

Options specific to Java code generation:

| Option            | Description                                                 |
|-------------------|-------------------------------------------------------------|
| `-nolexer`        | Generate code for using an external lexer.                  |
| `-interface NAME` | Use interface NAME, or generate it, when there is no input. |
| `-saxon`          | Generate Saxon extension function.                          |
| `-basex`          | Generate BaseX extension function.                          |

## XML Representation

Create XML representation of the grammar:

| Option            | Description                                                 |
|-------------------|-------------------------------------------------------------|
| `-xml`            | Create XML representation of grammar.                       |
| `-ff`             | Add first and follow sets to XML representation of grammar. |

## Code Generation Features

Additional features for the generated code:

| Option            | Description                                                 |
|-------------------|-------------------------------------------------------------|
| `-tree`           | Generate code for parse tree or parsing event handler.      |
| `-trace`          | Generate code for parser and tokenizer trace.               |
| `-main`           | Generate simple main program.                               |
| `-name NAME`      | Use non-default class name, or module namespace.            |
| `-performance`    | Generate performance test program.                          |

## Optimization

Optimize the generated parser for different aspects:

| Option            | Description                                                 |
|-------------------|-------------------------------------------------------------|
| `-faster`         | Optimize speed.                                             |
| `-smaller`        | Optimize memory consumption.                                |

## Miscellaneous

Other options:

| Option            | Description                                                 |
|-------------------|-------------------------------------------------------------|
| `-remake FILE`    | read command line from generated file and do it again.      |
| `-version`        | Show REx version.                                           |

## Input File Names

The recommended extension of input file names is `.ebnf`.

The following extensions **should be avoided**, as they trigger different functionality, however only when the command line consists of a single argument.

  - `.rex` causes lexer construction based on an undocumented legacy grammar notation.
  - `.template` causes template processing that is used internally for generating parts of REx source code.
  - `.java.compress` applies REx's table compression logic to a comma-separated list of integers, creating a Java class.

## Input and Output File Encoding

REx expects input files in UTF-8 encoding, and all output will be written in UTF-8. There is no support for other encodings.

&nbsp;
---
[⇦ Previous page](quickstart-xslt.md) &nbsp;&nbsp;│&nbsp;&nbsp; [⇧ Back to index](../README.md#-rex-parser-generator) &nbsp;&nbsp;│&nbsp;&nbsp; [Next page ⇨ ](supported-algorithms.md)