<link rel="stylesheet" href="markdown.css">

[⇦ Previous page](parser-debugging.md) &nbsp;&nbsp;│&nbsp;&nbsp; [⇧ Back to index](../README.md#-rex-parser-generator) &nbsp;&nbsp;│&nbsp;&nbsp; [Next page ⇨ ](using-an-external-lexer.md)

&nbsp;
# Performance Considerations

Here are some general rules of thumb regarding REx parser performance:

 - The lexer can  assemble tokens faster than the parser can identify nonterminals,
 - LL parsing is faster than LR parsing,
 - Deterministic parsing methods are faster than nondeterminstic methods.

## Generator Performance

The runtime of the parser generator primarily depends on the lookahead length. For simple grammars, using long lookahead does not present a problem, but as the complexity of the grammar increases, enlarging the lookahead an causes an exponential increase in the number of lookahead sequences that need to be considered. This in turn causes an exponential increase of the runtime.

Lookahead sizes of up to 3 are often feasible, even for larger grammars. For smaller grammars, it may be possible to use longer lookahead, but also it may happen that the space requirement exhausts the available resources, or the generation time grows over an acceptable limit.

## Parser Performance

The parser's performance is also influenced by the lookahead length, though to a lesser extent than the generator.

Parser speed can be improved by avoiding nondeterministic methods, which require additional runtime processing for dynamic conflict resolution.

Wherever possible, a REx LL-Parser should be used, because its logic is largely implemented using the control flow of the target language, making it subject to the compiler's optimization capabilities in that language.

## Generating a Performance Test Program

REx provides the -performance command-line option to generate a main program alongside the parser, which can create throughput figures by running the parser over a set of files in the file system.

The following example generates a performance test program in Javascript for the XML grammar in [`XML.ebnf`](sample-grammars/XML.ebnf):

```
rex -performance -javascript XML.ebnf
```

The generated program includes usage instructions:

```
Usage: node XML.js [-q] [-r N] [-t N] ENDING...

  parse all files that have names ending with ENDING, in current dir and below,
  and display performance summary.

  -q     do not show file names
  -r N   repeat N times
  -t N   repeat until N seconds have elapsed
```

For example, to parse all `.xml` files in the current directory and its subdirectories:

```
node XML.js -q .xml
```

The result will look like this:

```
loaded 153 files in 237 msec
parsed 770410968 bytes in 10019 msec (73.33 MB/sec)
0 errors
```

The above was using an sLL(3) Parser (the default selection of algorithm is `-ll 3`). For comparing it to an LALR parser, we could do the following:

```
rex -performance -javascript -lalr 3 XML.ebnf
node XML.js -q .xml
```

This provides us with an LALR(2) parser (lookahead length 2 is sufficient for LALR here) and these results measured over the same input data:

```
loaded 153 files in 229 msec
parsed 595978296 bytes in 10035 msec (56.64 MB/sec)
0 errors
```

So the LALR parser indeed is slightly slower than the LL parser.

## Parser Benchmark

There is a project available on GitHub that compares REx-generated parsers to parsers from other generators: [rex-parser-benchmark](https://github.com/GuntherRademacher/rex-parser-benchmark). It uses a fairly simple grammar for JSON and executes parsers generated for it in Java and XQuery, measuring their time and memory consumption. The project also creates graphical views of the results.

&nbsp;
---
[⇦ Previous page](parser-debugging.md) &nbsp;&nbsp;│&nbsp;&nbsp; [⇧ Back to index](../README.md#-rex-parser-generator) &nbsp;&nbsp;│&nbsp;&nbsp; [Next page ⇨ ](using-an-external-lexer.md)