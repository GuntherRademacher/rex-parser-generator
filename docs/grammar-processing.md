<link rel="stylesheet" href="markdown.css">

[⇦ Previous page](grammar-for-parsing-ebnf.md) &nbsp;&nbsp;│&nbsp;&nbsp; [⇧ Back to index](../README.md#-rex-parser-generator) &nbsp;&nbsp;│&nbsp;&nbsp; [Next page ⇨ ](parse-tree-generation.md)

&nbsp;
# Grammar Processing

This document explains how REx processes its input grammars.

## Grammar Structure

The grammar structure in REx consists of a syntax section, followed by an optional lexical definition and additional target language code:

```
// syntax rules

<?TOKENS?>

// lexical definition (optional)

<?ENCORE?>

// additional target language code (optional)
```

The separation between syntax definiton and lexical definiton serves several purposes:

- **Simplicity**: Lexical rules are generally simpler and more repetitive. Isolating them reduces the complexity of the syntax rules.
- **Efficiency**: Lexical analysis can be performed faster by closely concentrating on the task to identify tokens in the input character stream. By doing it separated from syntax analysis, we optimize the processing speed.
- **Disambiguation**: The separation offers a chance of establishing additional regulation for handling local ambiguities. With REx this can done by defining token preference rules.
- **Whitespace accommodation**: Implicit whitespace usually is allowed between tokens, but not inside of tokens. The separation thus provides the basis for handling whitespace without having to explicitly specify every single location where it is allowed.

## Start Symbols

A grammar may have multiple start symbols, which are the symbols that constitute the expected results of the parser. These symbols determine the entry points of the parser. The start symbols are determined implicitly by finding all symbols without explicit references. If there are no such symbols, the first non-whitespace nonterminal in the grammar will be the start symbol.

**Example:**

```
Expression ::= Term (('+' | '-') Term)*
Term       ::= Factor (('*' | '/') Factor)*
Factor     ::= ('+' | '-')? Primary
Primary    ::= Number | '(' Expression ')'

<?TOKENS?>

Number     ::= Digit Digit*
Whitespace ::= [ #x9#xA]+ /*ws: definition*/
Digit      ::= '0' | '1' | '2' | '3' | '4' | '5' | '6' | '7' | '8' | '9'
```

In the above example, as `Expression` is not referenced by any other rule, it will be considered a start symbol.

For each start symbol, the parser generates a method or function named after the symbol, to be called by the application. Depending on the target language and the context, this method may have different formats, such as:

 - `parseExpression`
 - `parse_Expression`
 - `parse-Expression`

These methods allow the user to parse input. If the target language provides a class for the generated parser, the method can be called without parameters on a parser instance, after instantiating it with the input string. Otherwise, if it is a standalone function, it needs to be called passing the input string as an argument.

## Whitespace and Comment Processing

Whitespace and comments often can occur between any two tokens of the language to be parsed. While it may be possible to explicitly specify whitespace occurrence within syntax rules, it is often much simpler to make use of REx's implicit whitespace handling.

This is based on a `/*ws: definition*/` annotation that is added to the end of a single rule in the grammar, a lexical rule, or even a syntax rule. This rule describes the structure of ignorable whitespace and comments. Any input sequence that matches the whitespace-definition rule once or more is allowed and skipped by the parser

 - between any two symbols of any syntax rule of the grammar, unless that rule is annotated `/*ws: explicit*/`,
 - at the very beginning of the input,
 - before the end of input.

The whitespace-definition rule should be a lexical rule, but in case that recursion is needed, e.g. for specifying nested comments, it can also be a syntax rule. However in this case any tokens that it may start with must be distinct from all tokens used in non whitespace-definition rules.

When defining a lexical whitespace-definition rule, care should be taken to describe as much as possible as a single whitespace token, rather than defining smaller entities, such as single characters. This improves parser performance, by avoiding whitespace characters passed to the parser one by one. This is especially important when handling larger inputs.

## Implementing Reserved Words

Some languages restict the set of allowable identifiers by excluding the keywords of the language. For example, the words `package`, `class`, `interface` cannot be used as identifiers in Java, because they are reserved for those keywords.

An identifier is usually defined as a letter, followed by more letters or other allowed characters. A simple definition might allow an initial upper or lower case letter, followed by any number of letters or digits:

```
Identifier ::= [a-zA-Z] [a-zA-Z0-9]*
```

This already collides with `package`, `class`, `interface`, because these are sequences of letters. 

For allowing the lexer to return a unique response, the keywords thus must be excluded from the identifier token. This can be accomplished by using the exclusion operator:

```
Identifier ::= ( [a-zA-Z] [a-zA-Z0-9]* ) - ( 'package' | 'class' | 'interface' )
```

Using the exclusion operator here prevents keywords from being matched as identifiers, ensuring unique tokenization.

## Implementing Non-Reserved Keywords

The definition of an identifier often collides with the keywords of the language. In some languages, keywords are not reserved, so some given input may be a keyword or an identifier - from the lexer's point of view. But when invoked to get the next token, the lexer must present a unique response - there is no option to present a choice of multiple solutions to the parser. *(Note that this is applies to the current implementation. In theory, the GLR approach to parsing could well be used to allow a multitude of lexer results.)*

The lexer's knowledge of the greater context is limited to having the set of valid tokens at the current parser state. This may still include keywords and identifiers.

However the parser's knowledge can be used to solve the problem as follows:

 - add a lexer preference rule that prefers keywords over identifiers,
 - add an extra syntax rule for identifiers, that allows both the identifier token and the conflicting keywords.

The duplication of names can be used here to avoid having to invent an extra name.

**Example:**

```
...
Identifier ::= Identifier^Token | 'and' | 'begin' | 'end' | 'for' | 'or' | 'while' | 'until'

<?TOKENS?>
...
Identifier  << 'and' 'begin' 'end' 'for' 'or' 'while' 'until'
```

With this specification, the lexer prioritizes keywords over identifiers. Due to the additional syntax rule, the parser still allows the keywords as an identifier (the nonterminal, in this case), and from its context, it can decide whether to use that the identifier rule or use the keyword, as a keyword.

Use REx's "lexical ambiguities" error messages to know the actual keywords, that need be included in these rules.

As a consequence of this approach, the parse tree may contain extra `Identifier` nonterminal nodes with a substructure, and any logic processing the parse tree must be aware of this.

For a more extensive example, see the [sample grammars](sample-grammars/README.md) for XQuery.

## End-of-Input Handling

A REx grammar by default is not expected to cover input up to the very end. Rather a REx parser will accept, when the input that has been processed conforms to the grammar, and no more input is expected or the next token is not a valid continuation. So it may parse only a prefix of the input and accept that, ignoring the remaining input.

While there are cases where exactly this behavior is desired, more often it is necessary to parse all of the input, reporting an error in case there is any remaining input behind a valid acceptable prefix. In these cases the end-of-input should be explicitly added to the syntax rule for the start symbol.

REx only provides a notation for the end-of-input on the lexical level. But it can be made a token by adding a lexical rule, and that token could be used to terminate the start symbol rule.

**Example:**

A parser for the following grammar will accept input that consists of exactly one `a` character, and report an error for anything else:

```
S   ::= 'a' EOF

<?TOKENS?>

EOF ::= $
```

Without the end-of-input handling, the parser for the grammar below would accept any input that starts with an `a` character, and ignore anything that follows it:

```
S   ::= 'a'
```

&nbsp;
---
[⇦ Previous page](grammar-for-parsing-ebnf.md) &nbsp;&nbsp;│&nbsp;&nbsp; [⇧ Back to index](../README.md#-rex-parser-generator) &nbsp;&nbsp;│&nbsp;&nbsp; [Next page ⇨ ](parse-tree-generation.md)
