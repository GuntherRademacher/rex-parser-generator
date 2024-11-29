<link rel="stylesheet" href="markdown.css">

[⇦ Previous page](sample-grammars/README.md) &nbsp;&nbsp;│&nbsp;&nbsp; [⇧ Back to index](../README.md#-rex-parser-generator)

&nbsp;
# History of Development

As of today, REx is a parser generator supporting different parsing algorithms, with integrated lexer construction, for various host languages, implemented in C++. But the setup, focus, and implementation of the product have changed significantly over time, since the development of this line of parsing tools originally started in 1979.

## The Name "REx"

Originally, the name "REx" was meant to emphasize the use of REgular Expressions, which the generator converted into a set of deterministic finite automata, implementing the lexer. The name was first used when the lexer generator component was added and initially referred only to that component. Later, it was extended to designate the full set of components, including the parser generator.

The full product name is "REx Parser Generator", and the correct spelling of "REx" is with two capital letters. There is other software using names containing the word "rex", in various cases, sometimes also alluding to regular expressions. No other product is known to be a parser generator, and none is related to this product, which is "REx Parser Generator", or short "REx".

## 1979

The first component developed was a basic LR parser generator, with no support yet for automated lexer generation. The parsing algorithms supported were SLR(1), LALR(1), and LR(1). Besides being self-hosting, the initial use case was generating Fortran parsers for a set of tools supporting the porting of large Fortran software suites between different dialects of the language. The grammar could be annotated with target language code, that was executed when the LR parser performed a reduction.

At that time, the yacc parser generator and the lex lexer generator already existed, but they were restricted to Unix. Conversely, many brands of minicomputers with proprietary operating systems existed, most of which supported Fortran, sometimes Pascal, while C was not very common. This is why the parser generator was written in Fortran, running on 16-bit minicomputers.

## 1981

The next component added was the lexer generator, implemented in Pascal. The lexer generator originally was a separate program, which was not integrated with the parser generator. They cooperated by the parser generator providing information about token codes and names, which was taken by the lexer generator, along with a separate specification of the token structure. The specification, in sets of regular expressions, was transformed into sets of deterministic finite automata for runtime evaluation. The runtime component then combined the results of lexer and parser generators into a working parser.

## 1982

In order to handle lexical ambiguities, as occurring in the Fortran language, a technique was developed to dynamically resolve decision problems when the lexer cannot unambiguously identify the next token. This approach exploits the parser's knowledge by using parallel evaluation of all alternatives and terminating invalid ones while maintaining multiple parser states in a tree-structured stack. This mechanism was very similar to the GLR algorithm used for handling parsing conflicts, but it was applied to lexical ambiguities rather than to LR conflicts. The development and implementation of this idea formed the central part of the 1982 Diplomarbeit (master's thesis) "Scannergenerierung f&uuml;r lexikalisch mehrdeutige Sprachkonstrukte" ("Scanner Generation for Lexically Ambiguous Language Constructs") by Gunther Rademacher at Universit&auml;t Dortmund.

## 1987

The original implementations of the generators, especially of the lexer generator, were comparably slow, and as more complex grammars emerged, proved to be inconvenient in that they caused fairly long turnaround times during grammar development. Thus an optimization effort was started that resulted in a major rewrite of the generator internals, eventually providing it with excellent generation time performance. REx was then used in a SQL implementation, and for various small languages, as one would call domain-specific languages (DSLs) today.

## 1994

During the transition to new host operating systems, the requirement to use both Fortran and Pascal as implementation languages became increasingly cumbersome. Consequently, both the parser generator and the lexer generator were converted into C programs. To facilitate this conversion, REx was used to create Fortran and Pascal parsers, which formed the basis for tools that enabled a semi-automatic transformation into C code. Subsequently, most of that C code was rewritten step by step to become native C. 

## 2002

Up to this point, the lexer generator only supported ASCII as the input alphabet for generated lexers. However, the need to support Unicode input arose. This was addressed by developing character classification logic based on the usage of characters in the grammar. This approach exploited the fact that, although there are hundreds of thousands of Unicode code points, a grammar typically partitions them into a fairly limited number of classes that need to be treated differently during the parsing process. With this classification as the first step, all subsequent processing could proceed as before, without significantly increasing the size of the data structures. In order to avoid excessive memory consumption by code point mapping, a compressed table representation was developed.

## 2006

As an additional parsing algorithm, REx introduced an LL parser by adding a new parser generator implementation. The design goal was to ensure fast parser execution by implementing recursive descent in host language code rather than using a table-driven approach. Another goal was to support lookaheads longer than 1. This resulted in the LL support available today, which includes LL(1) and strong-LL(k) parsing, with no hard limit on k, limitations arising only from time and space constraints. Many practical parsers used strong-LL(3), with some employing even longer lookaheads. The new parser generator was implemented in C++, and the host languages were Java and C++. The old implementation of LR(1) parsing and related algorithms remained available but was used less frequently, as the aged implementation was not flexible enough to be adapted to newly arising requirements.

To replace the old proprietary EBNF for the input grammar, the grammar notation used by the W3C in the XML and XQuery recommendations was adopted. This choice aligned well with the task of generating XML and XQuery parsers at the time. The lexer generator continued to use its own grammar notation. However, the lexical part of the W3C-style input grammar was extracted and converted into the lexer generator's notation.

## 2007

Parser generator and lexer generator were integrated into a single program. This involved a major rewrite of the lexer generator for making it native C++. Code generators for target language code were added to the lexer generator as well. The goal was to produce a single self-contained program that could be compiled without additional dependencies.

## 2008

Lexer operations are driven by transition tables that represent deterministic finite automata. These tables are two-dimensional, mapping a state and an input character class to a subsequent state or an error. Because these tables are typically large but sparsely populated, compressing them is necessary to maintain moderate space requirements. Previously, this involved using lists that had to be searched sequentially during the lexer's runtime. However, this was changed to use the same table compression method already employed for the character classification map, thereby completely eliminating the need for sequential list processing.

## 2009

Up to this point, REx only supported annotating the grammar with target language code for creating results from the parse, such as building result trees or extracting relevant information from the input. Subsequently, additional infrastructure was added to the generated parsers to automatically build the concrete parse tree.

REx was equipped with an XQuery code generator. Initially, this was intended solely to explore the feasibility of implementing heavy character processing code in XQuery and to conduct performance testing of XQuery implementations. However, it proved to be useful and eventually gained attention in the XML community, demonstrating the need for a parser generator in that environment. 

## 2010

As an additional tool supporting REx applications, the [RR Railroad Diagram Generator][RR] was developed. This tool takes a REx grammar and transforms it into an HTML page with syntax diagrams in SVG or PNG formats, after also slightly optimizing it for achieving compact and expressive diagrams. [RR][RR] was implemented in XQuery and won a prize in an XQuery programming contest. It is often used today for documenting formal languages. 

## 2011

Accompanying [RR][RR], the [ebnf-convert][ebnf-convert] grammar converter was developed. This tool can take grammars in various forms of EBNF, such as the input languages of other parser generators, and convert them to the W3C style used by REx and [RR][RR]. The arrival of this tool facilitated the quick adoption of REx, as it allowed initial grammars for projects to be based on pre-existing sources, even if those sources were created for different environments. Partly utilizing [RR][RR] infrastructure, [ebnf-convert][ebnf-convert] was also implemented in XQuery.

## 2012 

A code generator for C# as a target language was added.

## 2013 

Code generators for using XSLT and TypeScript as target languages were added.

## 2017

The old LR parser generator implementation was dropped and replaced by a completely new implementation, which had been under development for several years. The design goals for the new implementation included: direct supporting EBNF for LR without transforming to BNF, lookaheads longer than one with no hard limit, support for LR(k) and LALR(k), support for GLR, shared conventions with the LL generator to allow switching parsing algorithms with existing grammars, and support for the same set of target languages.

## 2019 

A code generator for Go as a target language was added.

## 2020 

A code generator for Python as a target language was added.

## 2023

The [Markup Blitz][Markup Blitz] project was spawned from REx. After a performance study using a REx GLR parser indicated its viability, [Markup Blitz][Markup Blitz] was created as a new implementation in Java, incorporating many concepts employed by REx, e.g. character classification, table compression, and the GLR runtime infrastructure. The goal was to provide a conforming implementation of the upcoming Invisible XML standard with good performance that could be integrated into XML processing toolchains for the JVM. Though related to REx, [Markup Blitz][Markup Blitz] is a separate project with a completely new implementation in Java. It is now used to provide Invisible XML functionality in BaseX and MorganaXProc.

## 2024

Previously being proprietary software, REx was published as open source for the first time under the Apache 2 license.

&nbsp;
---
[⇦ Previous page](sample-grammars/README.md) &nbsp;&nbsp;│&nbsp;&nbsp; [⇧ Back to index](../README.md#-rex-parser-generator)

[ebnf-convert]: https://github.com/GuntherRademacher/ebnf-convert
[Markup Blitz]: https://github.com/GuntherRademacher/markup-blitz
[RR]: https://github.com/GuntherRademacher/rr