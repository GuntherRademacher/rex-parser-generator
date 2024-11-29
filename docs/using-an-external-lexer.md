<link rel="stylesheet" href="markdown.css">

[⇦ Previous page](performance-considerations.md) &nbsp;&nbsp;│&nbsp;&nbsp; [⇧ Back to index](../README.md#-rex-parser-generator) &nbsp;&nbsp;│&nbsp;&nbsp; [Next page ⇨ ](grammar-tools.md)

&nbsp;
# Using an External Lexer

Using an external lexer can be useful in special cases, such as reusing an existing lexer or integrating with custom input handling. However, the built-in lexer is generally sufficient for most scenarios.

Using this command line option, REx can be instructed to make the generated parser use an external lexer:

```sh
-nolexer
```

Note: this is currently only supported for Java as the target language.

When the option is used, generation of the integrated lexer will be suppressed. In this case the grammar is not required to contain a lexical section. When token definitions are present, they are ignored at generation time. They are still required to be syntactically correct, though.

As usual, all names in the syntax section, that do not refer to nonterminal definitions, are considered as token references, together with all literals occurring in the syntax section. 

With `-nolexer` in effect, the generated Java parser includes

 - `Token`: a class holding token code and positions,
 - `Lexer`: the external lexer interface,
 - `getTokenCount`, `getTokenName`: static methods for getting token information,
 - `getTokenSetCount`, `getTokenSet`: static methods for getting token set information.

## Token

This is for exchanging information about tokens between the parser and the external lexer:

```java
  public static class Token {
    public int code;
    public int begin;
    public int end;
  }
```

Class `Token` has three public members:

 - `code`: the token code. It can be resolved to the corresponding token name by calling the parser's (static) `getTokenName` method. The value is filled by the lexer. A negative code is typically used when no token can be identified.
 - `begin`: the input position where the token begins.
 - `end`: the input position where the token ends, i.e. the first position following the token - the beginning of the next token. In case of error, this should be the position of the first character that did not match an expected token.

## Lexer

The methods of this interface are called by the parser:

```java
  public interface Lexer {
    void reset(CharSequence input);
    void match(int tokenset, Token token);
  }
```

The parser's constructor and `initialize` method will accept an extra parameter of type `Lexer`.

Method `Lexer.reset` will be called by `initialize` with a single argument:

 - `input`: the parser's input.

Method `Lexer.match` will be called successively for fetching one token at a time. It has two arguments:

 - `tokenSetId`: the id of the set of valid tokens, i.e. the set of tokens that are currently expected and can be processed by the parser. The `tokenSetid` can be resolved to the actual token set by calling the parser's (static) `getTokenSet` method.

 - `token`: the token information. Upon entry of `match`, `token.begin` is prefilled with the input position where the token begins, while `token.code` and `token.end` must be determined by the implementation of `match`.

Non-backtracking, non-GLR parsers fetch each token just once in input order. In contrast, backtracking or GLR parsers may invoke `match` multiple times for the same position. The parser may provide different `tokenSetId` values for the same position in multiple calls, and while backtracking, it may even retract to positions that were already processed earlier.

Only tokens in the set identified by `tokenSetId` are expected by the parser in any given situation. The lexer is free to ignore this information, or to use it in order to generate only expected tokens. This is useful in situations where there are multiple conflicting tokens in the language, though at any one time only one of them is in the expected set. In case there are no such ambiguities, or the lexer has its own strategy for resolving them, `tokenSetId` can be safely ignored.

## Getting Token Information

There are two static methods in the parser class that provide information on tokens:

```java
  public static int getTokenCount();
  public static String getTokenName(int code);
```

Method `getTokenCount` returns the number of tokens. Tokens are numbered with token codes from `0` to `getTokenCount() - 1`. The name of a token can be determined by passing its token code to `getTokenName`.

Method `getTokenName` has one argument:

 - `code`: the token code, a value in the range `0` to `getTokenCount() - 1`.

It returns the name of the token that is identified by `code`, as a string. Token names of literal tokens are composed by the literal value, surrounded by apostrophe characters, where apostrophe characters inside of the literal value are represented by a double apostrophe. For non-literal tokens, the token name is the same as the nonterminal name. `null` is returned, if the value of `code` is outside of the acceptable range.

## Getting Token Set Information

There are two static methods in the parser that provide information on token sets:

```java
  public static int getTokenSetCount();
  public static String[] getTokenSet(int tokenSetId);
```

Method `getTokenSetCount` returns the number of distinct token sets that are used by the parser. Token sets are numbered from `0` to  `getTokenSetCount() - 1`. A token set can be retrieved by passing its id to `getTokenSet`.

Method `getTokenSet` has one argument:

 - `tokenSetId`: the token set id, a value in the range `0` to `getTokenSetCount() - 1`.

It returns the token set, that is identified by `tokenSetId`, as an array of strings. The strings are token names as returned by `getTokenName`.

## External Lexer Sample Code

The following sample demonstrates how to use an external lexer with a REx parser for XML:

 - [`XmlXl.ebnf`](sample-grammars/XmlXl.ebnf): an XML grammar without a lexical section,
 - [`XmlXlLexer.java`](sample-grammars/XmlXlLexer.java): an external lexer implementation for tokens of the XML grammar, based on Java regular expressions.

Proceed as follows for running the sample:

 - generate a parser with a performance test main program using this command line:

   ```sh
   rex -java -nolexer -a java-regex -performance XmlXl.ebnf
   ```

 - compile the Java code:

   ```sh
   javac XmlXl.java XmlXlLexer.java
   ```

 - run the parser on all XML files in the current directory and below.

   ```sh
   java XmlXl .xml
   ```

 - in case of stack overflows, increase the Java stack size. This might become necessary, because complex Java regular expressions require a considerable amount of stack space. Here we use 4 times as much as the standard stack size of 1MB:

   ```sh
   java -Xss4m XmlXl .xml
   ```

 - for getting performance figures, run it repeatedly for 10 seconds:

   ```sh
   java XmlXl -q -t 10 .xml
   ```

While the provided implementation of the sample external lexer is fairly straightforward, its performance is significantly lower than REx's internal lexer, which is approximately 10 times faster. For testing this as well, generate a parser from the XML grammar that includes a lexical section, [XML.ebnf](sample-grammars/XML.ebnf), and run it on the same data:

```sh
  rex XML.ebnf -java -performance
  javac XML.java
  java XML -q -t 10 .xml
```

&nbsp;
---
[⇦ Previous page](performance-considerations.md) &nbsp;&nbsp;│&nbsp;&nbsp; [⇧ Back to index](../README.md#-rex-parser-generator) &nbsp;&nbsp;│&nbsp;&nbsp; [Next page ⇨ ](grammar-tools.md)